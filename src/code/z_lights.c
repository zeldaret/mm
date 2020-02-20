#include <ultra64.h>
#include <global.h>

#pragma intrinsic (sqrtf)
extern float fabsf(float);
#pragma intrinsic (fabsf)

void Lights_InitPositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius, u32 type) {
    info->type = type;
    info->params.posX = posX;
    info->params.posY = posY;
    info->params.posZ = posZ;
    Lights_SetPositionalLightColorAndRadius(info, red, green, blue, radius);
}

void Lights_InitType0PositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius) {
    Lights_InitPositionalLight(info, posX, posY, posZ, red, green, blue, radius, 0);
}

void Lights_InitType2PositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius) {
    Lights_InitPositionalLight(info, posX, posY, posZ, red, green, blue, radius, 2);
}

void Lights_SetPositionalLightColorAndRadius(LightInfoPositional* info, u8 red, u8 green, u8 blue, s16 radius) {
    info->params.red = red;
    info->params.green = green;
    info->params.blue = blue;
    info->params.radius = radius;
}

void Lights_SetPositionalLightPosition(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ) {
    info->params.posX = posX;
    info->params.posY = posY;
    info->params.posZ = posZ;
}

void Lights_InitDirectional(LightInfoDirectional* info, s8 dirX, s8 dirY, s8 dirZ, u8 red, u8 green, u8 blue) {
    info->type = 1;
    info->params.dirX = dirX;
    info->params.dirY = dirY;
    info->params.dirZ = dirZ;
    info->params.red = red;
    info->params.green = green;
    info->params.blue = blue;
}

void Lights_MapperInit(LightMapper* mapper, u8 red, u8 green, u8 blue) {
    mapper->lights.a.l.colc[0] = red;
    mapper->lights.a.l.col[0] = red;
    mapper->lights.a.l.colc[1] = green;
    mapper->lights.a.l.col[1] = green;
    mapper->lights.a.l.colc[2] = blue;
    mapper->lights.a.l.col[2] = blue;
    mapper->numLights = 0;
}

// XXX regalloc
#ifdef NON_MATCHING
void Lights_UploadLights(LightMapper* mapper, GraphicsContext* gCtxt) {
    Light* l;
    s32 i;

    gSPNumLights(gCtxt->polyOpa.append++, mapper->numLights);
    gSPNumLights(gCtxt->polyXlu.append++, mapper->numLights);

    l = &mapper->lights.l[0];

    for (i = 0; i < mapper->numLights;) {
        gSPLight(gCtxt->polyOpa.append++, l, ++i);
        gSPLight(gCtxt->polyXlu.append++, l++, i);
    }

    gSPLight(gCtxt->polyOpa.append++, &mapper->lights.a, ++i);
    gSPLight(gCtxt->polyXlu.append++, &mapper->lights.a, i);
}
#else
GLOBAL_ASM("asm/non_matchings/z_lights/Lights_UploadLights.asm")
#endif

Light* Lights_MapperGetNextFreeSlot(LightMapper* mapper) {
    if (6 < mapper->numLights) {
        return NULL;
    }
    return &mapper->lights.l[mapper->numLights++];
}

// XXX regalloc, some reorderings
#ifdef NON_MATCHING
void Lights_MapPositionalWithReference(LightMapper* mapper, LightInfoPositionalParams* params, Vector3f* pos) {
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 dist;
    f32 radiusF;
    Light* light;

    if (pos == NULL) return;

    if (params->radius < 1) return;

    xDiff = params->posX - pos->x;
    yDiff = params->posY - pos->y;
    zDiff = params->posZ - pos->z;
    radiusF = params->radius;
    dist = xDiff * xDiff + yDiff * yDiff + zDiff * zDiff;

    if (radiusF * radiusF > dist) {
        light = Lights_MapperGetNextFreeSlot(mapper);
        if (light == NULL) return;

        dist = sqrtf(dist);

        light->l.colc[0] = light->l.col[0] = params->red * (1 - (dist / radiusF) * (dist / radiusF));
        light->l.colc[1] = light->l.col[1] = params->green * (1 - (dist / radiusF) * (dist / radiusF));
        light->l.colc[2] = light->l.col[2] = params->blue * (1 - (dist / radiusF) * (dist / radiusF));

        if (dist < 1) {
            dist = 120;
        } else {
            dist = 120 / dist;
        }

        xDiff *= dist;
        yDiff *= dist;
        zDiff *= dist;

        light->l.dir[0] = xDiff;
        light->l.dir[1] = yDiff;
        light->l.dir[2] = zDiff;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/z_lights/Lights_MapPositionalWithReference.asm")
#endif

// This function matches, but uses .rodata. We don't have a good way to match partial .rodata for a file yet.
#ifdef NON_MATCHING
void Lights_MapPositional(LightMapper* mapper, LightInfoPositionalParams* params, GlobalContext* ctxt) {
    Light* light;
    f32 radiusF = params->radius;
    Vector3f posF;
    Vector3f adjustedPos;
    u32 pad;
    if (radiusF > 0) {
        posF.x = params->posX;
        posF.y = params->posY;
        posF.z = params->posZ;
        Matrix_MultiplyByVectorXYZ(&ctxt->unk187B0,&posF,&adjustedPos);
        if ((adjustedPos.z > -radiusF) &&
            (600 + radiusF > adjustedPos.z) &&
            (400 > fabsf(adjustedPos.x) - radiusF) &&
            (400 > fabsf(adjustedPos.y) - radiusF)) {
            light = Lights_MapperGetNextFreeSlot(mapper);
            if (light != NULL) {
                radiusF = 4500000.0f / (radiusF * radiusF);
                if (radiusF > 255) {
                    radiusF = 255;
                } else if (20 > radiusF) {
                    radiusF = 20;
                }

                light->lPos.col[0] = params->red;
                light->lPos.colc[0] = light->lPos.col[0];
                light->lPos.col[1] = params->green;
                light->lPos.colc[1] = light->lPos.col[1];
                light->lPos.col[2] = params->blue;
                light->lPos.colc[2] = light->lPos.col[2];
                light->lPos.pos[0] = params->posX;
                light->lPos.pos[1] = params->posY;
                light->lPos.pos[2] = params->posZ;
                light->lPos.pad1 = 0x8;
                light->lPos.pad2 = 0xFF;
                light->lPos.unkE = (s8)radiusF;
            }
        }
    }
}
#else
GLOBAL_ASM("asm/non_matchings/z_lights/Lights_MapPositional.asm")
#endif

void Lights_MapDirectional(LightMapper* mapper, LightInfoDirectionalParams* params, GlobalContext* ctxt) {
    Light* light = Lights_MapperGetNextFreeSlot(mapper);

    if (light != NULL) {
        light->l.col[0] = params->red;
        light->l.colc[0] = light->l.col[0];
        light->l.col[1] = params->green;
        light->l.colc[1] = light->l.col[1];
        light->l.col[2] = params->blue;
        light->l.colc[2] = light->l.col[2];
        light->l.dir[0] = params->dirX;
        light->l.dir[1] = params->dirY;
        light->l.dir[2] = params->dirZ;
        light->l.pad1 = 0;
    }
}

void Lights_MapLights(LightMapper* mapper, z_Light* lights, Vector3f* refPos, GlobalContext* ctxt) {
    if (lights != NULL) {
        if ((refPos == NULL) && (mapper->enablePosLights == 1)) {
            do {
                lightPositionalMapFuncs[lights->info->type](mapper, &lights->info->params, ctxt);
                lights = lights->next;
            } while (lights != NULL);
        } else {
            do {
                lightDirectionalMapFuncs[lights->info->type](mapper, &lights->info->params, refPos);
                lights = lights->next;
            } while (lights != NULL);
        }
    }
}

z_Light* Lights_FindFreeSlot(void) {
    z_Light* ret;

    if (0x1f < lightsList.numOccupied) {
        return NULL;
    }

    ret = &lightsList.lights[lightsList.nextFree];
    while (ret->info != NULL) {
        lightsList.nextFree++;
        if (lightsList.nextFree < 0x20) {
            ret++;
        } else {
            lightsList.nextFree = 0;
            ret = &lightsList.lights[0];
        }
    }

    lightsList.numOccupied++;
    return ret;
}

void Lights_Free(z_Light* light) {
    if (light != NULL) {
        lightsList.numOccupied--;
        light->info = NULL;
        lightsList.nextFree = (light - lightsList.lights) / (s32)sizeof(z_Light); //! @bug Due to pointer arithmetic, the division is unnecessary
    }
}

void Lights_Init(GlobalContext* ctxt, LightingContext* lCtxt) {
    Lights_ClearHead(ctxt, lCtxt);
    Lights_SetAmbientColor(lCtxt, 80, 80, 80);
    func_80102544(lCtxt, 0, 0, 0, 0x3e4, 0x3200);
    bzero(&lightsList, sizeof(LightsList));
}

void Lights_SetAmbientColor(LightingContext* lCtxt, u8 red, u8 green, u8 blue) {
    lCtxt->ambientRed = red;
    lCtxt->ambientGreen = green;
    lCtxt->ambientBlue = blue;
}

void func_80102544(LightingContext* lCtxt, u8 a1, u8 a2, u8 a3, s16 sp12, s16 sp16) {
    lCtxt->unk7 = a1;
    lCtxt->unk8 = a2;
    lCtxt->unk9 = a3;
    lCtxt->unkA = sp12;
    lCtxt->unkC = sp16;
}

LightMapper* Lights_CreateMapper(LightingContext* lCtxt, GraphicsContext* gCtxt) {
   return Lights_MapperAllocateAndInit(gCtxt, lCtxt->ambientRed, lCtxt->ambientGreen, lCtxt->ambientBlue);
}

void Lights_ClearHead(GlobalContext* ctxt, LightingContext* lCtxt) {
    lCtxt->lightsHead = NULL;
}

void Lights_RemoveAll(GlobalContext* ctxt, LightingContext* lCtxt) {
    while (lCtxt->lightsHead != NULL) {
        Lights_Remove(ctxt, lCtxt, lCtxt->lightsHead);
        lCtxt->lightsHead = lCtxt->lightsHead->next;
    }
}

z_Light* Lights_Insert(GlobalContext* ctxt, LightingContext* lCtxt, LightInfo* info) {
    z_Light* light;

    light = Lights_FindFreeSlot();
    if (light != NULL) {
        light->info = info;
        light->prev = NULL;
        light->next = lCtxt->lightsHead;

        if (lCtxt->lightsHead != NULL) {
            lCtxt->lightsHead->prev = light;
        }

        lCtxt->lightsHead = light;
    }

    return light;
}

void Lights_Remove(GlobalContext* ctxt, LightingContext* lCtxt, z_Light* light) {
    if (light != NULL) {
        if (light->prev != NULL) {
            light->prev->next = light->next;
        } else {
            lCtxt->lightsHead = light->next;
        }

        if (light->next != NULL) {
            light->next->prev = light->prev;
        }

        Lights_Free(light);
    }
}

LightMapper* func_801026E8(GraphicsContext* gCtxt, u8 ambientRed, u8 ambientGreen, u8 ambientBlue, u8 numLights, u8 red, u8 green, u8 blue, s8 dirX, s8 dirY, s8 dirZ) {
    LightMapper* mapper;
    s32 i;

    // TODO allocation should be a macro
    mapper = (LightMapper *)((int)gCtxt->polyOpa.appendEnd - sizeof(LightMapper));
    gCtxt->polyOpa.appendEnd = (void*)mapper;

    mapper->lights.a.l.col[0] = mapper->lights.a.l.colc[0] = ambientRed;
    mapper->lights.a.l.col[1] = mapper->lights.a.l.colc[1] = ambientGreen;
    mapper->lights.a.l.col[2] = mapper->lights.a.l.colc[2] = ambientBlue;
    mapper->enablePosLights = 0;
    mapper->numLights = numLights;

    for (i = 0; i < numLights; i++) {
        mapper->lights.l[i].l.col[0] = mapper->lights.l[i].l.colc[0] = red;
        mapper->lights.l[i].l.col[1] = mapper->lights.l[i].l.colc[1] = green;
        mapper->lights.l[i].l.col[2] = mapper->lights.l[i].l.colc[2] = blue;
        mapper->lights.l[i].l.dir[0] = dirX;
        mapper->lights.l[i].l.dir[1] = dirY;
        mapper->lights.l[i].l.dir[2] = dirZ;
    }

    Lights_UploadLights(mapper,gCtxt);

    return mapper;
}

LightMapper* Lights_MapperAllocateAndInit(GraphicsContext* gCtxt, u8 red, u8 green, u8 blue) {
    LightMapper* mapper;

    // TODO allocation should be a macro
    mapper = (LightMapper *)((int)gCtxt->polyOpa.appendEnd - sizeof(LightMapper));
    gCtxt->polyOpa.appendEnd = (void*)mapper;

    mapper->lights.a.l.col[0] = red;
    mapper->lights.a.l.colc[0] = red;
    mapper->lights.a.l.col[1] = green;
    mapper->lights.a.l.colc[1] = green;
    mapper->lights.a.l.col[2] = blue;
    mapper->lights.a.l.colc[2] = blue;
    mapper->enablePosLights = 0;
    mapper->numLights = 0;

    return mapper;
}

// XXX regalloc
#ifdef NON_MATCHING
void func_80102880(GlobalContext* ctxt) {
    z_Light* light = ctxt->lightsContext.lightsHead;
    LightInfoPositionalParams* params;
    Vector3f local_14;
    Vector3f local_20;
    f32 local_24;
    f32 fVar4;
    s32 s2;
    u32 pad[2];

    while (light != NULL) {
        if (light->info->type == 2) {
            params = (LightInfoPositionalParams*)&light->info->params;
            local_14.x = params->posX;
            local_14.y = params->posY;
            local_14.z = params->posZ;
            func_800B4EDC(ctxt, &local_14, &local_20, &local_24);

            params->unk9 = 0;

            if ((local_20.z > 1) &&
                (fabsf(local_20.x * local_24) < 1) &&
                (fabsf(local_20.y * local_24) < 1)) {
                fVar4 = local_20.z * local_24;
                s2 = (s32)(fVar4 * 16352) + 16352;
                if (s2 < func_80178A94(local_20.x * local_24 * 160 + 160, local_20.y * local_24 * -120 + 120)) {
                    params->unk9 = 1;
                }
            }
        }

        light = light->next;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/z_lights/func_80102880.asm")
#endif

// XXX regalloc
#ifdef NON_MATCHING
void func_80102A64(GlobalContext* ctxt) {
    Gfx* dl;
    LightInfoPositionalParams* params;
    f32 scale;
    GraphicsContext* gCtxt;
    z_Light* light = ctxt->lightsContext.lightsHead;

    if (light != NULL) {
        gCtxt = ctxt->common.gCtxt;
        dl = func_8012C7FC(gCtxt->polyXlu.append);

        gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 4, 4, 0x00000080); //! This doesn't resolve to any of the macros in gdi.h

        gDPSetCombineLERP(dl++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0,
                                0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);

        gSPDisplayList(dl++, &D_04029CB0);

        do {
            if (light->info->type == 2) {
                params = (LightInfoPositionalParams*)&light->info->params;
                if (params->unk9 != 0) {
                    scale = (f32)params->radius * (f32)params->radius * 2e-6f;

                    gDPSetPrimColor(dl++, 0, 0, params->red, params->green, params->blue, 50);

                    SysMatrix_InsertTranslation(params->posX, params->posY, params->posZ, 0);
                    SysMatrix_InsertScale(scale,scale,scale,1);

                    gSPMatrix(dl++, SysMatrix_AppendStateToPolyOpaDisp((ctxt->common).gCtxt), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(dl++, &D_04029CF0);
                }
            }

            light = light->next;
        } while (light != NULL);

        gCtxt->polyXlu.append = dl;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/z_lights/func_80102A64.asm")
#endif
