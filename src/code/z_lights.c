#include <ultra64.h>
#include <global.h>

LightsBindFunc1 bindPositionalFuncs[] = { Lights_MapPositional, Lights_MapDirectional, Lights_MapPositional };
LightsBindFunc2 bindDirectionalFuncs[] = { Lights_MapPositionalWithReference, Lights_MapDirectional, Lights_MapPositionalWithReference };

#define LIGHTS_BUFFER_SIZE 32

typedef struct {
    /* 0x000 */ s32 numOccupied;
    /* 0x004 */ s32 searchIndex;
    /* 0x008 */ LightNode buf[LIGHTS_BUFFER_SIZE];
} LightsBuffer; // size = 0x188

LightsBuffer sLightsBuffer;


void Lights_InitPositionalLight(LightInfo* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius, u32 type) {
    info->type = type;
    info->params.point.x = posX;
    info->params.point.y = posY;
    info->params.point.z = posZ;
    Lights_SetPositionalLightColorAndRadius(info, red, green, blue, radius);
}

void Lights_InitType0PositionalLight(LightInfo* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius) {
    Lights_InitPositionalLight(info, posX, posY, posZ, red, green, blue, radius, LIGHT_POINT_NOGLOW);
}

void Lights_InitType2PositionalLight(LightInfo* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius) {
    Lights_InitPositionalLight(info, posX, posY, posZ, red, green, blue, radius, LIGHT_POINT_GLOW);
}

void Lights_SetPositionalLightColorAndRadius(LightInfo* info, u8 red, u8 green, u8 blue, s16 radius) {
    info->params.point.color[0] = red;
    info->params.point.color[1] = green;
    info->params.point.color[2] = blue;
    info->params.point.radius = radius;
}

void Lights_SetPositionalLightPosition(LightInfo* info, s16 posX, s16 posY, s16 posZ) {
    info->params.point.x = posX;
    info->params.point.y = posY;
    info->params.point.z = posZ;
}

void Lights_InitDirectional(LightInfo* info, s8 dirX, s8 dirY, s8 dirZ, u8 red, u8 green, u8 blue) {
    info->type = 1;
    info->params.dir.x = dirX;
    info->params.dir.y = dirY;
    info->params.dir.z = dirZ;
    info->params.dir.color[0] = red;
    info->params.dir.color[1] = green;
    info->params.dir.color[2] = blue;
}

void Lights_MapperInit(Lights* lights, u8 red, u8 green, u8 blue) {
    lights->l.a.l.col[0] = lights->l.a.l.colc[0] = red;
    lights->l.a.l.col[1] = lights->l.a.l.colc[1] = green;
    lights->l.a.l.col[2] = lights->l.a.l.colc[2] = blue;
    lights->numLights = 0;
}

void Lights_UploadLights(Lights* lights, GraphicsContext* gfxCtx) {
    Light* light;
    s32 i;
    GraphicsContext* oGfxCtx = gfxCtx;

    gSPNumLights(oGfxCtx->polyOpa.p++, lights->numLights);
    gSPNumLights(oGfxCtx->polyXlu.p++, lights->numLights);

    light = &lights->l.l[0];
    i = 0;
    while (i < lights->numLights) {
        gSPLight(oGfxCtx->polyOpa.p++, light, ++i);
        gSPLight(oGfxCtx->polyXlu.p++, light++, i);
    }

    gSPLight(oGfxCtx->polyOpa.p++, &lights->l.a, ++i);
    gSPLight(oGfxCtx->polyXlu.p++, &lights->l.a, i);
}

Light* Lights_MapperGetNextFreeSlot(Lights* lights) {
    if (lights->numLights >= 7) {
        return NULL;
    }
    return &lights->l.l[lights->numLights++];
}

void Lights_MapPositionalWithReference(Lights* lights, LightParams* params, Vec3f* pos) {
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 dist;
    f32 scale;
    Light* light;

    if (pos == NULL) 
        return;

    if (params->point.radius < 1) 
        return;

    xDiff = params->point.x - pos->x;
    yDiff = params->point.y - pos->y;
    zDiff = params->point.z - pos->z;
    scale = params->point.radius;
    dist = SQ(xDiff) + SQ(yDiff) + SQ(zDiff);

    if (dist < SQ(scale)) {
        light = Lights_MapperGetNextFreeSlot(lights);
        if (light != NULL) {
            dist = sqrtf(dist);
            scale = dist / scale;
            scale = 1 - SQ(scale);

            light->lDir.col[0] = params->point.color[0] * scale;
            light->lDir.colc[0] = light->lDir.col[0];

            light->lDir.col[1] = params->point.color[1] * scale;
            light->lDir.colc[1] = light->lDir.col[1];

            light->lDir.col[2] = params->point.color[2] * scale;
            light->lDir.colc[2] = light->lDir.col[2];

            scale = (dist < 1.0f) ? 120.0f : 120.0f / dist;

            light->lDir.dir[0] = xDiff * scale;
            light->lDir.dir[1] = yDiff * scale;
            light->lDir.dir[2] = zDiff * scale;
        }
    }
}

void Lights_MapPositional(Lights* lights, LightParams* params, GlobalContext* globalCtx) {
    Light* light;
    f32 radiusF = params->point.radius;
    Vec3f posF;
    Vec3f adjustedPos;
    s32 pad;

    if (radiusF > 0.0f) {
        posF.x = params->point.x;
        posF.y = params->point.y;
        posF.z = params->point.z;
        Matrix_MultiplyByVectorXYZ(&globalCtx->unk187B0,&posF,&adjustedPos);
        if ((adjustedPos.z > -radiusF) &&
            (600.0f + radiusF > adjustedPos.z) &&
            (400.0f > fabsf(adjustedPos.x) - radiusF) &&
            (400.0f > fabsf(adjustedPos.y) - radiusF)) {
            light = Lights_MapperGetNextFreeSlot(lights);
            if (light == NULL)
                return;

            radiusF = 4500000.0f / SQ(radiusF);
            if (radiusF > 255.0f) {
                radiusF = 255.0f;
            } else if (radiusF < 20.0f) {
                radiusF = 20.0f;
            }

            light->lPos.col[0] = params->point.color[0];
            light->lPos.colc[0] = light->lPos.col[0];
            light->lPos.col[1] = params->point.color[1];
            light->lPos.colc[1] = light->lPos.col[1];
            light->lPos.col[2] = params->point.color[2];
            light->lPos.colc[2] = light->lPos.col[2];

            light->lPos.pos[0] = params->point.x;
            light->lPos.pos[1] = params->point.y;
            light->lPos.pos[2] = params->point.z;

            light->lPos.pad1 = 0x8;
            light->lPos.pad2 = 0xFF;
            light->lPos.pad3 = (s8)radiusF;
        }
    }
}

void Lights_MapDirectional(Lights* lights, LightParams* params, GlobalContext* globalCtx) {
    Light* light = Lights_MapperGetNextFreeSlot(lights);

    if (light != NULL) {
        light->lDir.col[0] = params->dir.color[0];
        light->lDir.colc[0] = light->lDir.col[0];
        light->lDir.col[1] = params->dir.color[1];
        light->lDir.colc[1] = light->lDir.col[1];
        light->lDir.col[2] = params->dir.color[2];
        light->lDir.colc[2] = light->lDir.col[2];
        light->lDir.dir[0] = params->dir.x;
        light->lDir.dir[1] = params->dir.y;
        light->lDir.dir[2] = params->dir.z;
        light->lDir.pad1 = 0;
    }
}

void Lights_MapLights(Lights* lights, LightNode* listHead, Vec3f* refPos, GlobalContext* globalCtx) {
    if (listHead != NULL) {
        if ((refPos == NULL) && (lights->enablePosLights == true)) {
            do {
                bindPositionalFuncs[listHead->info->type](lights, &listHead->info->params, globalCtx);
                listHead = listHead->next;
            } while (listHead != NULL);
        } else {
            do {
                bindDirectionalFuncs[listHead->info->type](lights, &listHead->info->params, refPos);
                listHead = listHead->next;
            } while (listHead != NULL);
        }
    }
}

LightNode* Lights_FindFreeSlot(void) {
    LightNode* ret;

    if (sLightsBuffer.numOccupied >= LIGHTS_BUFFER_SIZE) {
        return NULL;
    }

    ret = &sLightsBuffer.buf[sLightsBuffer.searchIndex];
    while (ret->info != NULL) {
        sLightsBuffer.searchIndex++;
        if (sLightsBuffer.searchIndex < 0x20) {
            ret++;
        } else {
            sLightsBuffer.searchIndex = 0;
            ret = &sLightsBuffer.buf[0];
        }
    }

    sLightsBuffer.numOccupied++;
    return ret;
}

void Lights_Free(LightNode* light) {
    if (light != NULL) {
        sLightsBuffer.numOccupied--;
        light->info = NULL;
        sLightsBuffer.searchIndex = (light - sLightsBuffer.buf) / (s32)sizeof(LightNode); //! @bug Due to pointer arithmetic, the division is unnecessary
    }
}

void Lights_Init(GlobalContext* globalCtx, LightContext* lightCtx) {
    Lights_ClearHead(globalCtx, lightCtx);
    Lights_SetAmbientColor(lightCtx, 80, 80, 80);
    func_80102544(lightCtx, 0, 0, 0, 0x3E4, 0x3200);
    bzero(&sLightsBuffer, sizeof(LightsBuffer));
}

void Lights_SetAmbientColor(LightContext* lightCtx, u8 red, u8 green, u8 blue) {
    lightCtx->ambient.red = red;
    lightCtx->ambient.green = green;
    lightCtx->ambient.blue = blue;
}

void func_80102544(LightContext* lightCtx, u8 a1, u8 a2, u8 a3, s16 numLights, s16 arg5) {
    lightCtx->unk07 = a1;
    lightCtx->unk08 = a2;
    lightCtx->unk09 = a3;
    lightCtx->unk0A = numLights;
    lightCtx->unk0C = arg5;
}

Lights* Lights_CreateMapper(LightContext* lightCtx, GraphicsContext* gfxCtx) {
   return Lights_MapperAllocateAndInit(gfxCtx, lightCtx->ambient.red, lightCtx->ambient.green, lightCtx->ambient.blue);
}

void Lights_ClearHead(GlobalContext* globalCtx, LightContext* lightCtx) {
    lightCtx->listHead = NULL;
}

void Lights_RemoveAll(GlobalContext* globalCtx, LightContext* lightCtx) {
    while (lightCtx->listHead != NULL) {
        Lights_Remove(globalCtx, lightCtx, lightCtx->listHead);
        lightCtx->listHead = lightCtx->listHead->next;
    }
}

LightNode* Lights_Insert(GlobalContext* globalCtx, LightContext* lightCtx, LightInfo* info) {
    LightNode* light = Lights_FindFreeSlot();

    if (light != NULL) {
        light->info = info;
        light->prev = NULL;
        light->next = lightCtx->listHead;

        if (lightCtx->listHead != NULL) {
            lightCtx->listHead->prev = light;
        }

        lightCtx->listHead = light;
    }

    return light;
}

void Lights_Remove(GlobalContext* globalCtx, LightContext* lightCtx, LightNode* light) {
    if (light != NULL) {
        if (light->prev != NULL) {
            light->prev->next = light->next;
        } else {
            lightCtx->listHead = light->next;
        }

        if (light->next != NULL) {
            light->next->prev = light->prev;
        }

        Lights_Free(light);
    }
}

// Unused
Lights* func_801026E8(GraphicsContext* gfxCtx, u8 ambientRed, u8 ambientGreen, u8 ambientBlue, u8 numLights, u8 red, u8 green, u8 blue, s8 dirX, s8 dirY, s8 dirZ) {
    Lights* lights;
    s32 i;

    lights = GRAPH_ALLOC(gfxCtx, sizeof(Lights));

    lights->l.a.l.col[0] = lights->l.a.l.colc[0] = ambientRed;
    lights->l.a.l.col[1] = lights->l.a.l.colc[1] = ambientGreen;
    lights->l.a.l.col[2] = lights->l.a.l.colc[2] = ambientBlue;
    lights->enablePosLights = false;
    lights->numLights = numLights;

    for (i = 0; i < numLights; i++) {
        lights->l.l[i].lDir.col[0] = lights->l.l[i].lDir.colc[0] = red;
        lights->l.l[i].lDir.col[1] = lights->l.l[i].lDir.colc[1] = green;
        lights->l.l[i].lDir.col[2] = lights->l.l[i].lDir.colc[2] = blue;
        lights->l.l[i].lDir.dir[0] = dirX;
        lights->l.l[i].lDir.dir[1] = dirY;
        lights->l.l[i].lDir.dir[2] = dirZ;
    }

    Lights_UploadLights(lights, gfxCtx);

    return lights;
}

Lights* Lights_MapperAllocateAndInit(GraphicsContext* gfxCtx, u8 red, u8 green, u8 blue) {
    Lights* lights;

    lights = GRAPH_ALLOC(gfxCtx, sizeof(Lights));

    lights->l.a.l.col[0] = lights->l.a.l.colc[0] = red;
    lights->l.a.l.col[1] = lights->l.a.l.colc[1] = green;
    lights->l.a.l.col[2] = lights->l.a.l.colc[2] = blue;
    lights->enablePosLights = false;
    lights->numLights = 0;

    return lights;
}

void func_80102880(GlobalContext* globalCtx) {
    LightNode* light = globalCtx->lightCtx.listHead;
    LightPoint* point;
    Vec3f pos;
    Vec3f multDest;
    f32 wDest;
    s32 wZ;
    s32 pad[3];

    while (light != NULL) {
        point = &light->info->params.point;

        if (light->info->type == LIGHT_POINT_GLOW) {
            pos.x = point->x;
            pos.y = point->y;
            pos.z = point->z;
            func_800B4EDC(globalCtx, &pos, &multDest, &wDest);
            point->drawGlow = 0;

            if ((multDest.z > 1.0f) &&
                (fabsf(multDest.x * wDest) < 1.0f) &&
                (fabsf(multDest.y * wDest) < 1.0f)) {
                wZ = (s32)((multDest.z * wDest) * 16352) + 16352;

                // Required to match
                if (0) {};

                if (wZ < func_80178A94(multDest.x * wDest * 160.0f + 160.0f, ((multDest.y * wDest) * -120.0f) + 120.0f)) {
                    point->drawGlow = 1;
                }
            }
        }

        light = light->next;
    }
}

void func_80102A64(GlobalContext* globalCtx) {
    LightPoint* point;
    f32 scale;
    LightNode* light = globalCtx->lightCtx.listHead;

    if (light != NULL) {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        Gfx* dl = func_8012C7FC(gfxCtx->polyXlu.p);

        // Required to match
        if (0){};

        gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 4, 4, 0x00000080); //! This doesn't resolve to any of the macros in gdi.h

        gDPSetCombineLERP(dl++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0,
                                0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);

        gSPDisplayList(dl++, &D_04029CB0);

        do {
            point = &light->info->params.point;
            if ((light->info->type == LIGHT_POINT_GLOW) && point->drawGlow) {
                scale = SQ((f32)point->radius) * 0.000002f;

                gDPSetPrimColor(dl++, 0, 0, point->color[0], point->color[1], point->color[2], 50);

                SysMatrix_InsertTranslation(point->x, point->y, point->z, MTXMODE_NEW);
                SysMatrix_InsertScale(scale, scale, scale, MTXMODE_APPLY);

                gSPMatrix(dl++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                gSPDisplayList(dl++, &D_04029CF0);
            }

            light = light->next;
        } while (light != NULL);

        gfxCtx->polyXlu.p = dl;
    }
}
