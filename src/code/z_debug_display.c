#include "global.h"

DebugDispObject* sDebugObjectListHead;

typedef struct {
    /* 0x00 */ s16 drawType;  // indicates which draw function to use when displaying the object
    /* 0x04 */ void* drawArg; // segment address (display list or texture) passed to the draw funciton when called
} DebugDispObjectInfo;        // size = 0x8

typedef void (*DebugDispObject_DrawFunc)(DebugDispObject*, void*, PlayState*);

void DebugDisplay_DrawSpriteI8(DebugDispObject*, void*, PlayState*);
void DebugDisplay_DrawPolygon(DebugDispObject*, void*, PlayState*);
Gfx* func_800E99B0(GraphicsContext* gfxCtx, Path* path);

DebugDispObject* DebugDisplay_Init(void) {
    sDebugObjectListHead = NULL;
    return sDebugObjectListHead;
}

DebugDispObject* DebugDisplay_AddObject(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX,
                                        f32 scaleY, f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type,
                                        GraphicsContext* gfxCtx) {
    DebugDispObject* oldHead = sDebugObjectListHead;

    sDebugObjectListHead = GRAPH_ALLOC(gfxCtx, sizeof(DebugDispObject));
    sDebugObjectListHead->pos.x = posX;
    sDebugObjectListHead->pos.y = posY;
    sDebugObjectListHead->pos.z = posZ;
    sDebugObjectListHead->rot.x = rotX;
    sDebugObjectListHead->rot.y = rotY;
    sDebugObjectListHead->rot.z = rotZ;
    sDebugObjectListHead->scale.x = scaleX;
    sDebugObjectListHead->scale.y = scaleY;
    sDebugObjectListHead->scale.z = scaleZ;
    sDebugObjectListHead->color.r = red;
    sDebugObjectListHead->color.g = green;
    sDebugObjectListHead->color.b = blue;
    sDebugObjectListHead->color.a = alpha;
    sDebugObjectListHead->type = type;
    sDebugObjectListHead->next = oldHead;
    return sDebugObjectListHead;
}

#include "code/debug_display/debug_display.c"

DebugDispObject_DrawFunc sDebugObjectDrawFuncTable[] = { DebugDisplay_DrawSpriteI8, DebugDisplay_DrawPolygon };

DebugDispObjectInfo sDebugObjectInfoTable[] = {
    { 0, sDebugDisplayCircleTex }, { 0, sDebugDisplayCrossTex }, { 0, sDebugDisplayBallTex },
    { 0, sDebugDisplayCursorTex }, { 1, &sDebugDisplay1DL },     { 1, &sDebugDisplay3DL },
    { 1, &sDebugDisplay2DL },
};

void DebugDisplay_DrawObjects(PlayState* play) {
    DebugDispObject* dispObj = sDebugObjectListHead;
    DebugDispObjectInfo* objInfo;

    while (dispObj != NULL) {
        objInfo = &sDebugObjectInfoTable[dispObj->type];
        sDebugObjectDrawFuncTable[objInfo->drawType](dispObj, objInfo->drawArg, play);
        dispObj = dispObj->next;
    }
}

void DebugDisplay_DrawSpriteI8(DebugDispObject* dispObj, void* texture, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    func_8012C6FC(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);
    Matrix_Translate(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, MTXMODE_NEW);
    Matrix_Scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, MTXMODE_APPLY);
    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    Matrix_RotateZYX(dispObj->rot.x, dispObj->rot.y, dispObj->rot.z, MTXMODE_APPLY);

    gDPLoadTextureBlock(POLY_XLU_DISP++, texture, G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, sDebugDisplaySpriteDL);

    CLOSE_DISPS(play->state.gfxCtx);
}

Lights1 sDebugDisplayLight1 = gdSPDefLights1(128, 128, 128, 255, 255, 255, 73, 73, 73);

void DebugDisplay_DrawPolygon(DebugDispObject* dispObj, void* arg1, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    func_8012C588(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);

    gSPSetLights1(POLY_XLU_DISP++, sDebugDisplayLight1);

    Matrix_SetTranslateRotateYXZ(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, &dispObj->rot);
    Matrix_Scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, arg1);
    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800E992C(PlayState* play, Path* path) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C560(play->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, func_800E99B0(play->state.gfxCtx, path));

    CLOSE_DISPS(play->state.gfxCtx);
}

#define R_DRAW_PATH_POINT (bREG(82))
#define R_DRAW_PATH_SCALE (1.0f + 0.1f * bREG(83))
#define R_DRAW_PATH_RED (bREG(84))
#define R_DRAW_PATH_GREEN (bREG(85))
#define R_DRAW_PATH_BLUE (bREG(86))
#define R_DRAW_PATH_ALPHA (bREG(87))

Vec3s D_801BB068[3][2] = {
    { { 20, 0, 0 }, { -20, 0, 0 } },
    { { 0, 20, 0 }, { 0, -20, 0 } },
    { { 0, 0, 20 }, { 0, 0, -20 } },
};

Gfx* func_800E99B0(GraphicsContext* gfxCtx, Path* path) {
    Gfx* sp2C;
    Gfx* var_t2;
    Vtx* var_v1;
    Vtx* sp20;
    Vec3s* var_a2;
    s32 var_t4;
    Vtx* temp;
    s32 i;
    s32 j;

    if (path != NULL) {
        var_t2 = GRAPH_ALLOC(gfxCtx, ALIGN16(((path->count - 1) * 4 + 1) * sizeof(Gfx))); // Gfx
        var_v1 = GRAPH_ALLOC(gfxCtx, ALIGN16(path->count * 6 * sizeof(Vtx)));             // Vtx

        sp2C = var_t2;
        sp20 = var_v1;
        var_a2 = Lib_SegmentedToVirtual(path->points);

        for (var_t4 = 0; var_t4 < path->count; var_t4++, var_a2++) {
            temp = sp20;
            sp20 = var_v1;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 2; j++) {
                    var_v1->v.ob[0] = var_a2->x + (s32)(D_801BB068[i][j].x * R_DRAW_PATH_SCALE);
                    var_v1->v.ob[1] = var_a2->y + (s32)(D_801BB068[i][j].y * R_DRAW_PATH_SCALE);
                    var_v1->v.ob[2] = var_a2->z + (s32)(D_801BB068[i][j].z * R_DRAW_PATH_SCALE);
                    var_v1->v.flag = 0;
                    var_v1->v.tc[0] = 0;
                    var_v1->v.tc[1] = 0;
                    var_v1->v.cn[0] = 0x80 + R_DRAW_PATH_RED;
                    var_v1->v.cn[1] = 0x80 + R_DRAW_PATH_GREEN;
                    var_v1->v.cn[2] = 0x80 + R_DRAW_PATH_BLUE;
                    var_v1->v.cn[3] = 0x80 + R_DRAW_PATH_ALPHA;
                    var_v1++;
                }
            }

            if (R_DRAW_PATH_POINT == 0) {
                if (var_t4 > 0) {
                    gSPVertex(var_t2++, temp, 12, 0);
                    gSP2Triangles(var_t2++, 0, 7, 1, 0, 0, 6, 7, 0);
                    gSP2Triangles(var_t2++, 2, 3, 8, 0, 3, 9, 8, 0);
                    gSP2Triangles(var_t2++, 4, 11, 10, 0, 4, 5, 11, 0);
                }
            } else {
                if ((var_t4 > 0) && (var_t4 == R_DRAW_PATH_POINT)) {
                    gSPVertex(var_t2++, temp, 12, 0);
                    gSP2Triangles(var_t2++, 0, 7, 1, 0, 0, 6, 7, 0);
                    gSP2Triangles(var_t2++, 2, 3, 8, 0, 3, 9, 8, 0);
                    gSP2Triangles(var_t2++, 4, 11, 10, 0, 4, 5, 11, 0);
                }
            }
        }
        gSPEndDisplayList(var_t2++);
    } else {
        sp2C = var_t2 = GRAPH_ALLOC(gfxCtx, ALIGN16(sizeof(Gfx)));
        gSPEndDisplayList(var_t2++);
    }
    return sp2C;
}
