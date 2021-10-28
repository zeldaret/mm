#include "global.h"

DebugDispObject* sDebugObjectListHead;

typedef struct {
    /* 0x00 */ s16 drawType;  // indicates which draw function to use when displaying the object
    /* 0x04 */ void* drawArg; // segment address (display list or texture) passed to the draw funciton when called
} DebugDispObjectInfo;        // size = 0x8

typedef void (*DebugDispObject_DrawFunc)(DebugDispObject*, void*, GlobalContext*);

#include "code/debug_display/code.c"

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

void func_800E95F4(DebugDispObject* dispObj, void* texture, GlobalContext* globalCtx) {

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C6FC(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);
    Matrix_InsertTranslation(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, 0);
    Matrix_Scale(dispObj->scale.x, dispObj->scale.y, dispObj->scale.z, 1);
    Matrix_InsertMatrix(&globalCtx->mf_187FC, 1);
    Matrix_InsertRotation(dispObj->rot.x, dispObj->rot.y, dispObj->rot.z, 1);
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

    gSPDisplayList(POLY_XLU_DISP++, sDebugDisplaySpriteDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

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


void func_800E97D8(DebugDispObject* dispObj, void* arg1, GlobalContext* globalCtx) {

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C588(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, dispObj->color.r, dispObj->color.g, dispObj->color.b, dispObj->color.a);

    gSPNumLights(POLY_XLU_DISP++, 1);

    gSPLight(POLY_XLU_DISP++, sDebugDisplayLight2, 1);
    gSPLight(POLY_XLU_DISP++, sDebugDisplayLight1, 2);

    Matrix_SetStateRotationAndTranslation(dispObj->pos.x, dispObj->pos.y, dispObj->pos.z, &dispObj->rot);
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
