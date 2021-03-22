#include <ultra64.h>
#include <global.h>

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
    info->params.color[0] = red;
    info->params.color[1] = green;
    info->params.color[2] = blue;
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

void Lights_UploadLights(LightMapper* mapper, GraphicsContext* gfxCtx) {
    Light* l;
    s32 i;

    OPEN_DISPS(gfxCtx);

    gSPNumLights(POLY_OPA_DISP++, mapper->numLights);
    gSPNumLights(POLY_XLU_DISP++, mapper->numLights);

    l = mapper->lights.l;

    for (i = 0; i < mapper->numLights;) {
        gSPLight(POLY_OPA_DISP++, l, ++i);
        gSPLight(POLY_XLU_DISP++, l++, i);
    }

    gSPLight(POLY_OPA_DISP++, &mapper->lights.a, ++i);
    gSPLight(POLY_XLU_DISP++, &mapper->lights.a, i);

    CLOSE_DISPS(gfxCtx);
}

Light* Lights_MapperGetNextFreeSlot(LightMapper* mapper) {
    if (6 < mapper->numLights) {
        return NULL;
    }
    return &mapper->lights.l[mapper->numLights++];
}

void Lights_MapPositionalWithReference(LightMapper* mapper, LightInfoPositionalParams* params, Vec3f* pos) {
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 posDiff;
    f32 scale;
    Light* light;

    if ((pos != NULL) && (params->radius >= 1)) {
        xDiff = params->posX - pos->x;
        yDiff = params->posY - pos->y;
        zDiff = params->posZ - pos->z;
        scale = params->radius;
        posDiff = SQ(xDiff) + SQ(yDiff) + SQ(zDiff);

        if (SQ(scale) > posDiff) {
            light = Lights_MapperGetNextFreeSlot(mapper);

            if (light != NULL) {
                posDiff = sqrtf(posDiff);
                scale = posDiff / scale;
                scale = 1 - SQ(scale);

                light->l.col[0] = params->color[0] * scale;
                light->l.colc[0] = light->l.col[0];
                light->l.col[1] = params->color[1] * scale;
                light->l.colc[1] = light->l.col[1];
                light->l.col[2] = params->color[2] * scale;
                light->l.colc[2] = light->l.col[2];

                scale = (posDiff < 1) ? 120 : 120 / posDiff;

                light->l.dir[0] = xDiff * scale;
                light->l.dir[1] = yDiff * scale;
                light->l.dir[2] = zDiff * scale;
            }
        }
    }
}

void Lights_MapPositional(LightMapper* mapper, LightInfoPositionalParams* params, GlobalContext* ctxt) {
    PosLight* light;
    f32 radiusF = params->radius;
    Vec3f posF;
    Vec3f adjustedPos;
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
            light = (PosLight*)Lights_MapperGetNextFreeSlot(mapper);
            if (light != NULL) {
                radiusF = 4500000.0f / (radiusF * radiusF);
                if (radiusF > 255) {
                    radiusF = 255;
                } else if (20 > radiusF) {
                    radiusF = 20;
                }

                light->col[0] = params->color[0];
                light->colc[0] = light->col[0];
                light->col[1] = params->color[1];
                light->colc[1] = light->col[1];
                light->col[2] = params->color[2];
                light->colc[2] = light->col[2];
                light->pos[0] = params->posX;
                light->pos[1] = params->posY;
                light->pos[2] = params->posZ;
                light->unk3 = 0x8;
                light->unk7 = 0xFF;
                light->unkE = (s32)radiusF;
            }
        }
    }
}

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

void Lights_MapLights(LightMapper* mapper, z_Light* lights, Vec3f* refPos, GlobalContext* ctxt) {
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
    mapper = (LightMapper *)((int)gCtxt->polyOpa.d - sizeof(LightMapper));
    gCtxt->polyOpa.d = (void*)mapper;

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
    mapper = (LightMapper *)((int)gCtxt->polyOpa.d - sizeof(LightMapper));
    gCtxt->polyOpa.d = (void*)mapper;

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

void func_80102880(GlobalContext* ctxt) {
    z_Light* light = ctxt->lightCtx.lightsHead;

    while (light != NULL) {
        LightInfoPositionalParams* params = (LightInfoPositionalParams*)&light->info->params;

        if (light->info->type == 2) {
            Vec3f pos;
            Vec3f multDest;
            f32 wDest;

            pos.x = params->posX;
            pos.y = params->posY;
            pos.z = params->posZ;
            func_800B4EDC(ctxt, &pos, &multDest, &wDest);

            params->unk9 = 0;

            if ((multDest.z > 1) && (fabsf(multDest.x * wDest) < 1) && (fabsf(multDest.y * wDest) < 1)) {
                s32 wX = multDest.x * wDest * 160 + 160;
                s32 wY = multDest.y * wDest * -120 + 120;
                s32 wZ = (s32)((multDest.z * wDest) * 16352) + 16352;
                s32 zBuf = func_80178A94(wX, wY);

                if (wZ < zBuf) {
                    params->unk9 = 1;
                }
            }
        }

        light = light->next;
    }
}

void func_80102A64(GlobalContext* ctxt) {
    Gfx* dl;
    LightInfoPositionalParams* params;
    z_Light* light = ctxt->lightCtx.lightsHead;

    if (light != NULL) {
        OPEN_DISPS(ctxt->state.gfxCtx);

        dl = func_8012C7FC(POLY_XLU_DISP);

        gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 4, 4, 0x00000080); //! This doesn't resolve to any of the macros in gdi.h

        gDPSetCombineLERP(dl++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0,
                                0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);

        gSPDisplayList(dl++, &D_04029CB0);

        do {
            if (light->info->type == 2) {
                params = (LightInfoPositionalParams*)&light->info->params;
                if (params->unk9 != 0) {
                    f32 scale = SQ((f32)params->radius) * 2e-6f;

                    gDPSetPrimColor(dl++, 0, 0, params->color[0], params->color[1], params->color[2], 50);

                    SysMatrix_InsertTranslation(params->posX, params->posY, params->posZ, 0);
                    SysMatrix_InsertScale(scale,scale,scale,1);

                    gSPMatrix(dl++, SysMatrix_AppendStateToPolyOpaDisp(ctxt->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(dl++, &D_04029CF0);
                }
            }

            light = light->next;
        } while (light != NULL);

        POLY_XLU_DISP = dl;

        CLOSE_DISPS(ctxt->state.gfxCtx);
    }
}
