#include <ultra64.h>
#include <global.h>

#define LIGHTS_BUFFER_SIZE 32

typedef struct {
    /* 0x000 */ s32 numOccupied;
    /* 0x004 */ s32 searchIndex;
    /* 0x008 */ LightNode buf[LIGHTS_BUFFER_SIZE];
} LightsBuffer; // size = 0x188

LightsBuffer sLightsBuffer;


void Lights_PointSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 red, u8 green, u8 blue, s16 radius, u32 type) {
    info->type = type;
    info->params.point.x = x;
    info->params.point.y = y;
    info->params.point.z = z;
    Lights_PointSetColorAndRadius(info, red, green, blue, radius);
}

void Lights_PointNoGlowSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 red, u8 green, u8 blue, s16 radius) {
    Lights_PointSetInfo(info, x, y, z, red, green, blue, radius, LIGHT_POINT_NOGLOW);
}

void Lights_PointGlowSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 red, u8 green, u8 blue, s16 radius) {
    Lights_PointSetInfo(info, x, y, z, red, green, blue, radius, LIGHT_POINT_GLOW);
}

void Lights_PointSetColorAndRadius(LightInfo* info, u8 red, u8 green, u8 blue, s16 radius) {
    info->params.point.color[0] = red;
    info->params.point.color[1] = green;
    info->params.point.color[2] = blue;
    info->params.point.radius = radius;
}

void Lights_SetPositionalLightPosition(LightInfo* info, s16 x, s16 y, s16 z) {
    info->params.point.x = x;
    info->params.point.y = y;
    info->params.point.z = z;
}

void Lights_DirectionalSetInfo(LightInfo* info, s8 x, s8 y, s8 z, u8 red, u8 green, u8 blue) {
    info->type = LIGHT_DIRECTIONAL;
    info->params.dir.x = x;
    info->params.dir.y = y;
    info->params.dir.z = z;
    info->params.dir.color[0] = red;
    info->params.dir.color[1] = green;
    info->params.dir.color[2] = blue;
}

// unused
void Lights_Reset(Lights* lights, u8 red, u8 green, u8 blue) {
    lights->l.a.l.col[0] = lights->l.a.l.colc[0] = red;
    lights->l.a.l.col[1] = lights->l.a.l.colc[1] = green;
    lights->l.a.l.col[2] = lights->l.a.l.colc[2] = blue;
    lights->numLights = 0;
}

/*
 * Draws every light in the provided Lights group
 */
void Lights_Draw(Lights* lights, GraphicsContext* gfxCtx) {
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

    // Ambient light is total lights + 1
    gSPLight(oGfxCtx->polyOpa.p++, &lights->l.a, ++i);
    gSPLight(oGfxCtx->polyXlu.p++, &lights->l.a, i);
}

Light* Lights_FindSlot(Lights* lights) {
    if (lights->numLights >= 7) {
        return NULL;
    }
    return &lights->l.l[lights->numLights++];
}

void Lights_BindDirection(Lights* lights, LightParams* params, Vec3f* pos) {
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
        light = Lights_FindSlot(lights);
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

void Lights_BindPoint(Lights* lights, LightParams* params, GlobalContext* globalCtx) {
    Light* light;
    f32 radius = params->point.radius;
    Vec3f pos;
    Vec3f adjustedPos;
    s32 pad;

    if (radius > 0.0f) {
        pos.x = params->point.x;
        pos.y = params->point.y;
        pos.z = params->point.z;
        Matrix_MultiplyByVectorXYZ(&globalCtx->unk187B0, &pos, &adjustedPos);
        if ((adjustedPos.z > -radius) &&
            (600.0f + radius > adjustedPos.z) &&
            (400.0f > fabsf(adjustedPos.x) - radius) &&
            (400.0f > fabsf(adjustedPos.y) - radius)) {
            light = Lights_FindSlot(lights);
            if (light == NULL)
                return;

            radius = 4500000.0f / SQ(radius);
            if (radius > 255.0f) {
                radius = 255.0f;
            } else if (radius < 20.0f) {
                radius = 20.0f;
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
            light->lPos.pad3 = (s8)radius;
        }
    }
}

void Lights_BindDirectional(Lights* lights, LightParams* params, GlobalContext* globalCtx) {
    Light* light = Lights_FindSlot(lights);

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

/*
 * For every light in a provided list, try to find a free slot in the provided Lights group and bind
 * a light to it. Then apply color and positional/directional info for each light
 * based on the parameters supplied by the node.
 *
 * Note: Lights in a given list can only be binded to however many free slots are
 * available in the Lights group. This is at most 7 slots for a new group, but could be less.
 */

LightsBindFunc1 bindPositionalFuncs[] = { Lights_BindPoint, Lights_BindDirectional, Lights_BindPoint };
LightsBindFunc2 bindDirectionalFuncs[] = { Lights_BindDirection, Lights_BindDirectional, Lights_BindDirection };

void Lights_BindAll(Lights* lights, LightNode* listHead, Vec3f* refPos, GlobalContext* globalCtx) {
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

LightNode* Lights_FindBufSlot(void) {
    LightNode* light;

    if (sLightsBuffer.numOccupied >= LIGHTS_BUFFER_SIZE) {
        return NULL;
    }

    light = &sLightsBuffer.buf[sLightsBuffer.searchIndex];
    while (light->info != NULL) {
        sLightsBuffer.searchIndex++;
        if (sLightsBuffer.searchIndex < 0x20) {
            light++;
        } else {
            sLightsBuffer.searchIndex = 0;
            light = &sLightsBuffer.buf[0];
        }
    }

    sLightsBuffer.numOccupied++;
    return light;
}

void Lights_FreeNode(LightNode* light) {
    if (light != NULL) {
        sLightsBuffer.numOccupied--;
        light->info = NULL;
        sLightsBuffer.searchIndex = (light - sLightsBuffer.buf) / (s32)sizeof(LightNode); //! @bug Due to pointer arithmetic, the division is unnecessary
    }
}

void LightContext_Init(GlobalContext* globalCtx, LightContext* lightCtx) {
    LightContext_InitList(globalCtx, lightCtx);
    LightContext_SetAmbientColor(lightCtx, 80, 80, 80);
    func_80102544(lightCtx, 0, 0, 0, 0x3E4, 0x3200);
    bzero(&sLightsBuffer, sizeof(LightsBuffer));
}

void LightContext_SetAmbientColor(LightContext* lightCtx, u8 red, u8 green, u8 blue) {
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

Lights* LightContext_NewLights(LightContext* lightCtx, GraphicsContext* gfxCtx) {
    return Lights_New(gfxCtx, lightCtx->ambient.red, lightCtx->ambient.green, lightCtx->ambient.blue);
}

void LightContext_InitList(GlobalContext* globalCtx, LightContext* lightCtx) {
    lightCtx->listHead = NULL;
}

void LightContext_DestroyList(GlobalContext* globalCtx, LightContext* lightCtx) {
    while (lightCtx->listHead != NULL) {
        LightContext_RemoveLight(globalCtx, lightCtx, lightCtx->listHead);
        lightCtx->listHead = lightCtx->listHead->next;
    }
}

/*
 * Insert a new light into the list pointed to by LightContext
 *
 * Note: Due to the limited number of slots in a Lights group, inserting too many lights in the
 * list may result in older entries not being bound to a Light when calling Lights_BindAll
 */
LightNode* LightContext_InsertLight(GlobalContext* globalCtx, LightContext* lightCtx, LightInfo* info) {
    LightNode* light = Lights_FindBufSlot();

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

void LightContext_RemoveLight(GlobalContext* globalCtx, LightContext* lightCtx, LightNode* light) {
    if (light != NULL) {
        if (light->prev != NULL) {
            light->prev->next = light->next;
        } else {
            lightCtx->listHead = light->next;
        }

        if (light->next != NULL) {
            light->next->prev = light->prev;
        }

        Lights_FreeNode(light);
    }
}

// Unused
Lights* Lights_NewAndDraw(GraphicsContext* gfxCtx, u8 ambientRed, u8 ambientGreen, u8 ambientBlue, u8 numLights, u8 red, u8 green, u8 blue, s8 x, s8 y, s8 z) {
    Lights* lights = GRAPH_ALLOC(gfxCtx, sizeof(Lights));
    s32 i;

    lights->l.a.l.col[0] = lights->l.a.l.colc[0] = ambientRed;
    lights->l.a.l.col[1] = lights->l.a.l.colc[1] = ambientGreen;
    lights->l.a.l.col[2] = lights->l.a.l.colc[2] = ambientBlue;
    lights->enablePosLights = false;
    lights->numLights = numLights;

    for (i = 0; i < numLights; i++) {
        lights->l.l[i].lDir.col[0] = lights->l.l[i].lDir.colc[0] = red;
        lights->l.l[i].lDir.col[1] = lights->l.l[i].lDir.colc[1] = green;
        lights->l.l[i].lDir.col[2] = lights->l.l[i].lDir.colc[2] = blue;
        lights->l.l[i].lDir.dir[0] = x;
        lights->l.l[i].lDir.dir[1] = y;
        lights->l.l[i].lDir.dir[2] = z;
    }

    Lights_Draw(lights, gfxCtx);

    return lights;
}

Lights* Lights_New(GraphicsContext* gfxCtx, u8 red, u8 green, u8 blue) {
    Lights* lights = GRAPH_ALLOC(gfxCtx, sizeof(Lights));

    lights->l.a.l.col[0] = lights->l.a.l.colc[0] = red;
    lights->l.a.l.col[1] = lights->l.a.l.colc[1] = green;
    lights->l.a.l.col[2] = lights->l.a.l.colc[2] = blue;
    lights->enablePosLights = false;
    lights->numLights = 0;

    return lights;
}

void Lights_GlowCheck(GlobalContext* globalCtx) {
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
            point->drawGlow = false;

            if ((multDest.z > 1.0f) &&
                (fabsf(multDest.x * wDest) < 1.0f) &&
                (fabsf(multDest.y * wDest) < 1.0f)) {
                wZ = (s32)((multDest.z * wDest) * 16352) + 16352;

                // Required to match
                if (0) {};

                if (wZ < func_80178A94(multDest.x * wDest * 160.0f + 160.0f, ((multDest.y * wDest) * -120.0f) + 120.0f)) {
                    point->drawGlow = true;
                }
            }
        }

        light = light->next;
    }
}

void Lights_DrawGlow(GlobalContext* globalCtx) {
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
