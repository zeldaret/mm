#include "global.h"

DebugDispObject* sDebugObjectListHead;

typedef struct {
    /* 0x00 */ s16 drawType;  // indicates which draw function to use when displaying the object
    /* 0x04 */ void* drawArg; // segment address (display list or texture) passed to the draw funciton when called
} DebugDispObjectInfo;        // size = 0x8

typedef void (*DebugDispObject_DrawFunc)(DebugDispObject*, void*, GlobalContext*);

Vtx D_801BA550[] = {
    VTX(3, -2, 8, 0, 0, 0x7E, 0x0E, 0x04, 0xFF),   VTX(3, 3, -7, 0, 0, 0x7E, 0x0E, 0x04, 0xFF),
    VTX(3, 3, 8, 0, 0, 0x7E, 0x0E, 0x04, 0xFF),    VTX(3, -2, -7, 0, 0, 0x7E, 0x0E, 0x04, 0xFF),
    VTX(3, -2, -7, 0, 0, 0x00, 0x00, 0x82, 0xFF),  VTX(-2, 3, -7, 0, 0, 0x00, 0x00, 0x82, 0xFF),
    VTX(3, 3, -7, 0, 0, 0x00, 0x00, 0x82, 0xFF),   VTX(-2, -2, -7, 0, 0, 0x00, 0x00, 0x82, 0xFF),
    VTX(-2, 3, -7, 0, 0, 0x00, 0x7F, 0x00, 0xFF),  VTX(3, 3, 8, 0, 0, 0x00, 0x7F, 0x00, 0xFF),
    VTX(3, 3, -7, 0, 0, 0x00, 0x7F, 0x00, 0xFF),   VTX(-2, 3, 8, 0, 0, 0x00, 0x7F, 0x00, 0xFF),
    VTX(3, -2, -7, 0, 0, 0x00, 0x83, 0x03, 0xFF),  VTX(3, -2, 8, 0, 0, 0x00, 0x83, 0x03, 0xFF),
    VTX(-2, -2, 8, 0, 0, 0x00, 0x83, 0x03, 0xFF),  VTX(-2, -2, -7, 0, 0, 0x00, 0x83, 0x03, 0xFF),
    VTX(-2, -2, 8, 0, 0, 0x00, 0x00, 0x7F, 0xFF),  VTX(3, -2, 8, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(3, 3, 8, 0, 0, 0x00, 0x00, 0x7F, 0xFF),    VTX(-2, 3, 8, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(-10, -2, 7, 0, 0, 0x00, 0x83, 0x03, 0xFF), VTX(11, -2, 7, 0, 0, 0x00, 0x84, 0x12, 0xFF),
    VTX(0, 0, 28, 0, 0, 0x00, 0x84, 0x12, 0xFF),   VTX(11, -2, 7, 0, 0, 0x00, 0x00, 0x82, 0xFF),
    VTX(-10, -2, 7, 0, 0, 0x00, 0x00, 0x82, 0xFF), VTX(0, 0, 7, 0, 0, 0x00, 0x00, 0x82, 0xFF),
    VTX(0, 6, 7, 0, 0, 0x00, 0x00, 0x82, 0xFF),    VTX(0, 6, 7, 0, 0, 0x85, 0x19, 0x07, 0xFF),
    VTX(-10, -2, 7, 0, 0, 0x85, 0x19, 0x07, 0xFF), VTX(0, 0, 28, 0, 0, 0x00, 0x7A, 0x23, 0xFF),
    VTX(11, -2, 7, 0, 0, 0x50, 0x5E, 0x1B, 0xFF),  VTX(0, 6, 7, 0, 0, 0x7E, 0x0E, 0x04, 0xFF),
};

Vtx D_801BA750[] = {
    VTX(-2, -2, -7, 0, 0, 0x85, 0x19, 0x07, 0xFF),
    VTX(-2, -2, 8, 0, 0, 0x85, 0x19, 0x07, 0xFF),
    VTX(-2, 3, 8, 0, 0, 0x85, 0x19, 0x07, 0xFF),
    VTX(-2, 3, -7, 0, 0, 0x85, 0x19, 0x07, 0xFF),
};

Gfx sDebugDisplay1DL[] = {
    gsSPVertex(&D_801BA550, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 23, 24, 25, 0),
    gsSP2Triangles(26, 23, 25, 0, 24, 26, 25, 0),
    gsSP2Triangles(27, 28, 29, 0, 30, 31, 29, 0),
    gsSPVertex(&D_801BA750, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Vtx D_801BA7F0[] = {
    VTX(-20, -20, -20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF), VTX(20, -20, -20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-20, -20, 20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(20, -20, 20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-20, 20, -20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(20, 20, -20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-20, 20, 20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(20, 20, 20, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Gfx sDebugDisplay2DL[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(&D_801BA7F0, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSP2Triangles(4, 6, 5, 0, 7, 5, 6, 0),
    gsSP2Triangles(7, 3, 5, 0, 1, 5, 3, 0),
    gsSP2Triangles(6, 4, 2, 0, 0, 2, 4, 0),
    gsSP2Triangles(6, 2, 7, 0, 3, 7, 2, 0),
    gsSP2Triangles(5, 1, 4, 0, 0, 4, 1, 0),
    gsSPEndDisplayList(),
};

Vtx D_801BA8C0[] = {
    VTX(-3, 10, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),  VTX(-7, 4, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(0, 4, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),    VTX(-3, -2, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(4, -2, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),   VTX(4, 10, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(8, 4, 25, 0, 0, 0x00, 0x00, 0x7F, 0xFF),    VTX(-5, -9, 12, 0, 0, 0xF1, 0x89, 0xDC, 0xFF),
    VTX(6, -4, -11, 0, 0, 0x19, 0xD4, 0x8D, 0xFF),  VTX(6, -9, 12, 0, 0, 0xF1, 0x89, 0xDC, 0xFF),
    VTX(-5, -4, -11, 0, 0, 0x19, 0xD4, 0x8D, 0xFF), VTX(-5, 10, -11, 0, 0, 0x19, 0xD4, 0x8D, 0xFF),
    VTX(6, 10, -11, 0, 0, 0x19, 0xD4, 0x8D, 0xFF),  VTX(-5, -9, 12, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(6, -9, 12, 0, 0, 0x00, 0x00, 0x7F, 0xFF),   VTX(6, 10, 12, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(-5, 10, 12, 0, 0, 0x00, 0x00, 0x7F, 0xFF),  VTX(6, 10, 12, 0, 0, 0x22, 0x78, 0xEA, 0xFF),
    VTX(-5, 10, -11, 0, 0, 0x00, 0x7F, 0x00, 0xFF), VTX(-5, 10, 12, 0, 0, 0x22, 0x78, 0xEA, 0xFF),
    VTX(6, 10, -11, 0, 0, 0x00, 0x7F, 0x00, 0xFF),  VTX(-3, 10, 25, 0, 0, 0x22, 0x78, 0xEA, 0xFF),
    VTX(4, 10, 25, 0, 0, 0x22, 0x78, 0xEA, 0xFF),   VTX(0, 3, 1, 0, 0, 0x19, 0xD4, 0x8D, 0xFF),
    VTX(8, 4, 25, 0, 0, 0x22, 0x78, 0xEA, 0xFF),    VTX(8, 4, 25, 0, 0, 0x79, 0xE1, 0xEF, 0xFF),
    VTX(4, -2, 25, 0, 0, 0xF1, 0x89, 0xDC, 0xFF),   VTX(-3, -2, 25, 0, 0, 0xF1, 0x89, 0xDC, 0xFF),
    VTX(-7, 4, 25, 0, 0, 0xF1, 0x89, 0xDC, 0xFF),   VTX(0, 3, 1, 0, 0, 0x83, 0x00, 0xF2, 0xFF),
    VTX(-7, 4, 25, 0, 0, 0x88, 0x20, 0xEF, 0xFF),   VTX(-3, 10, 25, 0, 0, 0x85, 0x15, 0xF5, 0xFF),
};

Vtx D_801BAAC0[] = {
    VTX(6, -9, 12, -2115, -1279, 0x7F, 0x00, 0x00, 0xFF), VTX(6, -4, -11, 2093, -656, 0x7F, 0x00, 0x00, 0xFF),
    VTX(6, 10, -11, 2116, 1280, 0x7F, 0x00, 0x00, 0xFF),  VTX(6, 10, 12, -2115, 1280, 0x79, 0xE1, 0xEF, 0xFF),
    VTX(-5, -4, -11, -33, -656, 0x83, 0x00, 0xF2, 0xFF),  VTX(-5, -9, 12, 3123, -1279, 0x88, 0x20, 0xEF, 0xFF),
    VTX(-5, 10, 12, 3123, 1280, 0x85, 0x15, 0xF5, 0xFF),  VTX(-5, 10, -11, -50, 1280, 0x83, 0x00, 0xF2, 0xFF),
};

Gfx sDebugDisplay3DL[] = {
    gsSPVertex(&D_801BA8C0, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 5, 0, 2, 0),
    gsSP2Triangles(4, 6, 2, 0, 6, 5, 2, 0),
    gsSP2Triangles(7, 8, 9, 0, 8, 10, 11, 0),
    gsSP2Triangles(8, 11, 12, 0, 7, 10, 8, 0),
    gsSP2Triangles(13, 14, 15, 0, 13, 15, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 20, 18, 0),
    gsSP2Triangles(21, 22, 23, 0, 22, 24, 23, 0),
    gsSP2Triangles(25, 26, 23, 0, 26, 27, 23, 0),
    gsSP2Triangles(27, 28, 29, 0, 30, 31, 29, 0),
    gsSPVertex(&D_801BAAC0, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

#include "z_debug_display_gfx"

Vtx D_801BAFB8[] = {
    VTX(-32, 32, 0, 0, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(32, 32, 0, 1023, 0, 0x00, 0x00, 0x7F, 0xFF),
    VTX(-32, -32, 0, 0, 1023, 0x00, 0x00, 0x7F, 0xFF),
    VTX(32, -32, 0, 1023, 1023, 0x00, 0x00, 0x7F, 0xFF),
};
Gfx gDebugSpriteDL[] = {
    gsSPVertex(&D_801BAFB8, 4, 0),
    gsSP2Triangles(0, 2, 1, 0, 1, 2, 3, 0),
    gsSPEndDisplayList(),
};

void func_800E95F4(DebugDispObject*, void*, GlobalContext*);
void func_800E97D8(DebugDispObject*, void*, GlobalContext*);

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

DebugDispObject_DrawFunc sDebugObjectDrawFuncTable[] = { func_800E95F4, func_800E97D8 };
DebugDispObjectInfo sDebugObjectInfoTable[] = {
    { 0, D_801BABB8 },        { 0, D_801BAEB8 },        { 0, D_801BACB8 },        { 0, D_801BADB8 },
    { 1, &sDebugDisplay1DL }, { 1, &sDebugDisplay3DL }, { 1, &sDebugDisplay2DL },
};

void DebugDisplay_DrawObjects(GlobalContext* globalCtx) {
    DebugDispObject* dispObj = sDebugObjectListHead;
    DebugDispObjectInfo* objInfo;

    while (dispObj != NULL) {
        objInfo = &sDebugObjectInfoTable[dispObj->type];
        sDebugObjectDrawFuncTable[objInfo->drawType](dispObj, objInfo->drawArg, globalCtx);
        dispObj = dispObj->next;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_display/func_800E95F4.s")

void func_800E95F4(DebugDispObject* dispObj, void* texture, GlobalContext* globalCtx) {

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C6FC(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);
    SysMatrix_InsertTranslation(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, 0);
    Matrix_Scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, 1);
    SysMatrix_InsertMatrix(&globalCtx->mf_187FC, 1);
    SysMatrix_InsertRotation(dispObj->rot.x, dispObj->rot.y, dispObj->rot.z, 1);
    gDPSetTextureImage(POLY_XLU_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture);
    gDPSetTile(POLY_XLU_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(POLY_XLU_DISP++);

    gDPLoadBlock(POLY_XLU_DISP++, G_TX_LOADTILE, 0, 0, 127, 1024);

    gDPPipeSync(POLY_XLU_DISP++);

    gDPSetTile(POLY_XLU_DISP++, G_IM_FMT_I, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

    gDPSetTileSize(POLY_XLU_DISP++, G_TX_RENDERTILE, 0, 0, 0x003C, 0x003C);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, gDebugSpriteDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// static Lights1 sDebugObjectLights = gdSPDefLights1(0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0x49, 0x49, 0x49);

s32 sDebugDisplayLight1[] = {
    0x80808000,
    0x80808000,
};

s32 sDebugDisplayLight2[] = {
    0xFFFFFF00,
    0xFFFFFF00,
    0x49494900,
    0x00000000,
};

// extern Light sDebugDisplayLight1[];
// extern Light sDebugDisplayLight2[];

void func_800E97D8(DebugDispObject* dispObj, void* arg1, GlobalContext* globalCtx) {

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C588(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);

    gSPNumLights(POLY_XLU_DISP++, 1);

    gSPLight(POLY_XLU_DISP++, sDebugDisplayLight2, 1);
    gSPLight(POLY_XLU_DISP++, sDebugDisplayLight1, 2);

    SysMatrix_SetStateRotationAndTranslation(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, &dispObj->rot);
    Matrix_Scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, 1);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, arg1);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 D_801BB068[] = {
    0x00140000, 0x0000FFEC, 0x00000000, 0x00000014, 0x00000000, 0xFFEC0000, 0x00000000, 0x00140000, 0x0000FFEC,
};

s32 D_801BB08C = 0;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_display/func_800E992C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_debug_display/func_800E99B0.s")
