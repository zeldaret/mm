#include "global.h"

void func_800EE364(GameState* gameState, s16 index);
void func_800EE400(GameState* gameState, s16 index);
void func_800EE5FC(GameState* gameState, s16 index);
void func_800EE7D8(GameState* gameState, s16 index);
void func_800EE940(GameState* gameState, s16 index);
void func_800EEA48(GameState* gameState, s16 index);
void func_800EEC18(GameState* gameState, s16 index);
void func_800EED20(GameState* gameState, s16 index);
void func_800EEE34(GameState* gameState, s16 index);
void func_800EEF4C(GameState* gameState, s16 index);
void func_800EF054(GameState* gameState, s16 index);
void func_800EF0F0(GameState* gameState, s16 index);
void func_800EF1F4(GameState* gameState, s16 index);
void func_800EF2AC(GameState* gameState, s16 index);
void func_800EF364(GameState* gameState, s16 index);
void func_800EF4D4(GameState* gameState, s16 index);
void func_800EF65C(GameState* gameState, s16 index);
void func_800EF780(GameState* gameState, s16 index);
void func_800EF89C(GameState* gameState, s16 index);
void func_800EF984(GameState* gameState, s16 index);
void func_800EFAB8(GameState* gameState, s16 index);
void func_800EFBFC(GameState* gameState, s16 index);
void func_800EFD44(GameState* gameState, s16 index);

extern UNK_TYPE D_06001254;
extern UNK_TYPE D_06001C60;
extern Gfx D_060000E0[];
extern Gfx D_06000330[];
extern Gfx D_06000340[];
extern Gfx D_060003C0[];
extern Gfx D_06000438[];
extern Gfx D_060004A0[];
extern Gfx D_060004B0[];
extern Gfx D_060004C0[];
extern Gfx D_060004D0[];
extern Gfx D_060004E0[];
extern Gfx D_06000500[];
extern Gfx D_06000520[];
extern Gfx D_06000540[];
extern Gfx D_06000560[];
extern Gfx D_06000570[];
extern Gfx D_06000580[];
extern Gfx D_060005A0[];
extern Gfx D_060005C0[];
extern Gfx D_060005E0[];
extern Gfx D_060005F0[];
extern Gfx D_06000600[];
extern Gfx D_06000608[];
extern Gfx D_06000620[];
extern Gfx D_06000640[];
extern Gfx D_06000670[];
extern Gfx D_06000690[];
extern Gfx D_060006A0[];
extern Gfx D_060006C0[];
extern Gfx D_060006E0[];
extern Gfx D_060006E8[];
extern Gfx D_060006F0[];
extern Gfx D_06000730[];
extern Gfx D_06000750[];
extern Gfx D_06000770[];
extern Gfx D_060007A0[];
extern Gfx D_060007B0[];
extern Gfx D_060007D0[];
extern Gfx D_060007F0[];
extern Gfx D_06000800[];
extern Gfx D_06000808[];
extern Gfx D_06000820[];
extern Gfx D_06000830[];
extern Gfx D_06000850[];
extern Gfx D_06000880[];
extern Gfx D_06000888[];
extern Gfx D_060008B8[];
extern Gfx D_060008C0[];
extern Gfx D_060008D0[];
extern Gfx D_060008F0[];
extern Gfx D_06000910[];
extern Gfx D_06000918[];
extern Gfx D_06000930[];
extern Gfx D_06000940[];
extern Gfx D_06000948[];
extern Gfx D_06000950[];
extern Gfx D_06000958[];
extern Gfx D_06000960[];
extern Gfx D_06000968[];
extern Gfx D_06000970[];
extern Gfx D_06000990[];
extern Gfx D_06000998[];
extern Gfx D_060009A0[];
extern Gfx D_060009B0[];
extern Gfx D_060009B8[];
extern Gfx D_060009E0[];
extern Gfx D_060009E8[];
extern Gfx D_060009F0[];
extern Gfx D_06000A08[];
extern Gfx D_06000A10[];
extern Gfx D_06000A30[];
extern Gfx D_06000A50[];
extern Gfx D_06000A80[];
extern Gfx D_06000A90[];
extern Gfx D_06000AA0[];
extern Gfx D_06000AA8[];
extern Gfx D_06000AB0[];
extern Gfx D_06000AC0[];
extern Gfx D_06000AD0[];
extern Gfx D_06000AD8[];
extern Gfx D_06000AE0[];
extern Gfx D_06000AF0[];
extern Gfx D_06000AF8[];
extern Gfx D_06000B10[];
extern Gfx D_06000B20[];
extern Gfx D_06000B30[];
extern Gfx D_06000B50[];
extern Gfx D_06000B60[];
extern Gfx D_06000B70[];
extern Gfx D_06000B78[];
extern Gfx D_06000B90[];
extern Gfx D_06000BA0[];
extern Gfx D_06000BC0[];
extern Gfx D_06000BD0[];
extern Gfx D_06000BE0[];
extern Gfx D_06000BF8[];
extern Gfx D_06000C00[];
extern Gfx D_06000C08[];
extern Gfx D_06000C10[];
extern Gfx D_06000C20[];
extern Gfx D_06000C50[];
extern Gfx D_06000C78[];
extern Gfx D_06000C80[];
extern Gfx D_06000C90[];
extern Gfx D_06000CA0[];
extern Gfx D_06000CC0[];
extern Gfx D_06000CE0[];
extern Gfx D_06000CF0[];
extern Gfx D_06000D00[];
extern Gfx D_06000D18[];
extern Gfx D_06000D28[];
extern Gfx D_06000D30[];
extern Gfx D_06000D50[];
extern Gfx D_06000D78[];
extern Gfx D_06000D80[];
extern Gfx D_06000D98[];
extern Gfx D_06000DA0[];
extern Gfx D_06000DB8[];
extern Gfx D_06000DF0[];
extern Gfx D_06000E48[];
extern Gfx D_06000E58[];
extern Gfx D_06000E90[];
extern Gfx D_06000EC8[];
extern Gfx D_06000ED0[];
extern Gfx D_06000EE0[];
extern Gfx D_06000EF0[];
extern Gfx D_06000F08[];
extern Gfx D_06000F20[];
extern Gfx D_06000F40[];
extern Gfx D_06000F58[];
extern Gfx D_06000FA0[];
extern Gfx D_06000FB8[];
extern Gfx D_06000FD0[];
extern Gfx D_06000FD8[];
extern Gfx D_06001000[];
extern Gfx D_06001010[];
extern Gfx D_06001040[];
extern Gfx D_06001048[];
extern Gfx D_06001060[];
extern Gfx D_060010D0[];
extern Gfx D_06001270[];
extern Gfx D_06001288[];
extern Gfx D_06001290[];
extern Gfx D_060012B0[];
extern Gfx D_060012D0[];
extern Gfx D_060012F0[];
extern Gfx D_06001310[];
extern Gfx D_06001330[];
extern Gfx D_06001388[];
extern Gfx D_060013D0[];
extern Gfx D_060013E0[];
extern Gfx D_06001438[];
extern Gfx D_06001470[];
extern Gfx D_06001590[];
extern Gfx D_060016B0[];
extern Gfx D_06001750[];
extern Gfx D_06001770[];
extern Gfx D_06001790[];
extern Gfx D_060017B0[];
extern Gfx D_060017D0[];
extern Gfx D_060017F0[];
extern Gfx D_06001810[];
extern Gfx D_06001830[];
extern Gfx D_06001848[];
extern Gfx D_06001850[];
extern Gfx D_060019A0[];
extern Gfx D_06001A28[];
extern Gfx D_06001AD8[];
extern Gfx D_06001D80[];
extern Gfx D_06003AD0[];
extern Gfx D_06004DB0[];
extern Gfx D_06004EB8[];
extern Gfx D_06005020[];

static s801BB170 D_801BB170[] = {
    { func_800EF0F0, D_06000670, D_06000750, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000800, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000FD8, D_06000FD0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_060006A0, D_060005A0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF2AC, D_06000AA0, D_06000AE0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF2AC, D_06000AB0, D_06000AE0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF2AC, D_06000AC0, D_06000AE0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF2AC, D_06000AD0, D_06000AE0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EEE34, D_060000E0, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000CA0, D_06000F08, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EE940, D_06000960, D_06000C50, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000B78, D_060006C0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000E48, D_06000A10, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06001048, D_06001040, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000C00, D_06000B50, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000808, D_06000800, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000968, D_060006F0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EED20, D_06000E90, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF2AC, D_06001290, D_06001470, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF2AC, D_06001290, D_06001590, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF89C, D_06000990, D_060008D0, D_06000930, D_06000A80, NULL, NULL, NULL, NULL },
    { func_800EF89C, D_06000990, D_060008F0, D_06000950, D_06000A80, NULL, NULL, NULL, NULL },
    { func_800EF89C, D_06000990, D_06000910, D_06000970, D_06000A80, NULL, NULL, NULL, NULL },
    { func_800EF89C, D_06000B90, D_06000AD0, D_06000B30, D_06000D98, NULL, NULL, NULL, NULL },
    { func_800EF89C, D_06000B90, D_06000AF0, D_06000B50, D_06000D98, NULL, NULL, NULL, NULL },
    { func_800EF89C, D_06000B90, D_06000B10, D_06000B70, D_06000D98, NULL, NULL, NULL, NULL },
    { func_800EF054, D_060004D0, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_060003C0, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000580, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000EE0, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_060009A0, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000B70, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EFBFC, D_06001850, D_06001750, D_06001790, D_060019A0, D_060017B0, D_06001A28, D_060017D0, D_06001AD8 },
    { func_800EFBFC, D_06001850, D_06001770, D_060017F0, D_060019A0, D_06001810, D_06001A28, D_06001830, D_06001AD8 },
    { func_800EF0F0, D_06001438, D_06001040, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000340, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000B90, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06001830, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EE364, D_060004B0, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000D28, D_060009F0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000E48, D_06000A10, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000E48, D_06000A10, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_060008C0, D_06000AF8, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06001060, D_06001288, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000AC0, D_06000D50, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_060006E8, D_060006E0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000C80, D_06000F40, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000D80, D_06001010, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EEA48, D_06001438, D_06001270, D_060012D0, D_06001790, D_06001330, D_06001848, NULL, NULL },
    { func_800EEA48, D_06001438, D_06001290, D_060012F0, D_06001790, D_06001388, D_06001848, NULL, NULL },
    { func_800EEA48, D_06001438, D_060012B0, D_06001310, D_06001790, D_060013E0, D_06001848, NULL, NULL },
    { func_800EF0F0, D_06000BF8, D_06000770, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, D_06000580, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EEF4C, D_06000600, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000948, D_06000820, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF054, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EEC18, D_06000600, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000DF0, D_06000C00, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000AA8, D_06000830, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF4D4, D_06000B10, D_060008B8, D_060007F0, D_060007B0, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000918, D_06000880, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000FA0, D_06000CF0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000BC0, D_06000E58, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_060013D0, D_060016B0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000A08, D_06000990, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000A08, D_060009B8, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF984, D_06000620, D_06000540, D_06000730, D_06000600, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000A08, D_060009E0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_060010D0, D_06000BA0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000C10, D_060007D0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EE364, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF780, D_06000AE0, D_06000CA0, D_06000D00, NULL, NULL, NULL, NULL, NULL },
    { func_800EF780, D_06000AE0, D_06000CC0, D_06000D00, NULL, NULL, NULL, NULL, NULL },
    { func_800EF780, D_06000AE0, D_06000CE0, D_06000D00, NULL, NULL, NULL, NULL, NULL },
    { func_800EE7D8, D_06000330, D_06000438, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000830, D_06000B20, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EE400, D_06000990, D_06000BE0, D_06000CF0, D_06000950, NULL, NULL, NULL, NULL },
    { func_800EE5FC, D_06000BD0, D_06000DB8, D_06000EF0, NULL, NULL, NULL, NULL, NULL },
    { func_800EFAB8, D_06000620, D_060004A0, D_06000730, D_06000560, NULL, NULL, NULL, NULL },
    { func_800EFAB8, D_06000620, D_060004C0, D_06000730, D_06000580, NULL, NULL, NULL, NULL },
    { func_800EFAB8, D_06000620, D_060004E0, D_06000730, D_060005A0, NULL, NULL, NULL, NULL },
    { func_800EE400, D_06000990, D_06000BE0, D_06000CF0, D_06000970, NULL, NULL, NULL, NULL },
    { func_800EF984, D_06000620, D_06000500, D_06000730, D_060005C0, NULL, NULL, NULL, NULL },
    { func_800EF984, D_06000620, D_06000520, D_06000730, D_060005E0, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000998, D_06000850, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EE7D8, D_06004DB0, D_06004EB8, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000CC0, D_060009B0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06001010, D_06000CF0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF65C, D_06000D78, D_06000C80, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000A08, D_06000968, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000F20, D_06000B50, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EFD44, D_06000690, D_06000690, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000DA0, D_06000BC0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000888, D_06000880, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000D18, D_060009A0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000FB8, D_06000C90, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000D30, D_060007F0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF364, D_06000F08, D_06000B20, D_06000A90, D_06000A50, NULL, NULL, NULL, NULL },
    { func_800EFD44, D_06003AD0, D_06003AD0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EFD44, D_06001D80, D_06001D80, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EFD44, D_06005020, D_06005020, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000C08, D_06000C00, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_060009E8, D_060009E0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000AD8, D_06000940, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_060008F0, D_060007A0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06001000, D_06000ED0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000F58, D_06000B30, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000C20, D_060007D0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_060005F0, D_060004A0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000C78, D_06000750, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000958, D_06000640, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000B60, D_06000A30, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000608, D_06000570, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000C00, D_060008C0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000E90, D_06000A50, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF0F0, D_06000EC8, D_06000BC0, NULL, NULL, NULL, NULL, NULL, NULL },
    { func_800EF1F4, D_06000B90, D_060009B0, NULL, NULL, NULL, NULL, NULL, NULL },
};

void GetItem_Draw(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    D_801BB170[index].unk0(gameState, index);
}

void func_800EE364(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C214(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EE400(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 0, globalCtx->state.frames * 0,
                                0x10, 0x20, 1, globalCtx->state.frames, -(globalCtx->state.frames * 6), 0x10, 0x20));

    Matrix_StatePush();
    Matrix_NormalizeXYZ(&globalCtx->mf_187FC);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk10);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EE5FC(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 0, globalCtx->state.frames * 0,
                                0x20, 0x20, 1, globalCtx->state.frames, -(globalCtx->state.frames * 6), 0x20, 0x20));

    Matrix_StatePush();
    Matrix_NormalizeXYZ(&globalCtx->mf_187FC);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EE7D8(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 0, -(globalCtx->state.frames * 5),
                                0x20, 0x20, 1, globalCtx->state.frames * 0, globalCtx->state.frames * 0, 0x20, 0x40));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EE940(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 5);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EEA48(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, -globalCtx->state.frames, globalCtx->state.frames, 0x20,
                                0x20, 1, -globalCtx->state.frames, globalCtx->state.frames, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk8);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unkC);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk10);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk14);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk18);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EEC18(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 1, globalCtx->state.frames * 0,
                                0x20, 0x20, 1, globalCtx->state.frames * 0, globalCtx->state.frames * 0, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EED20(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 6, globalCtx->state.frames * 6,
                                0x20, 0x20, 1, globalCtx->state.frames * 6, globalCtx->state.frames * 6, 0x20, 0x20));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EEE34(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 0, -(globalCtx->state.frames * 3),
                                0x20, 0x20, 1, globalCtx->state.frames * 0, -(globalCtx->state.frames * 2), 0x20,
                                0x20));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk4);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EEF4C(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames * 0, globalCtx->state.frames * 1,
                                0x20, 0x20, 1, globalCtx->state.frames * 0, globalCtx->state.frames * 1, 0x20, 0x20));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk4);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF054(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF0F0(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF1F4(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF2AC(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk4);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF364(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    MtxF sp4C;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    Matrix_FromRSPMatrix(Lib_SegmentedToVirtual(D_801BB170[index].unk10), &sp4C);
    Matrix_InsertMatrix(&sp4C, MTXMODE_APPLY);
    Matrix_NormalizeXYZ(&globalCtx->mf_187FC);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF4D4(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    MtxF sp4C;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06001254));

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    Matrix_FromRSPMatrix(Lib_SegmentedToVirtual(D_801BB170[index].unk10), &sp4C);
    Matrix_InsertMatrix(&sp4C, MTXMODE_APPLY);
    Matrix_NormalizeXYZ(&globalCtx->mf_187FC);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF65C(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06001C60));

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    Matrix_NormalizeXYZ(&globalCtx->mf_187FC);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF780(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk8);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF89C(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk8);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unkC);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk10);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EF984(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk8);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk10);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EFAB8(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Scale(0.7f, 0.7f, 0.7f, MTXMODE_APPLY);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk8);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unk10);
    gSPDisplayList(POLY_XLU_DISP++, D_801BB170[index].unkC);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EFBFC(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk8);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unkC);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk10);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk14);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk18);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk1C);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk20);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800EFD44(GameState* gameState, s16 index) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    s8 objectIdx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    objectIdx = Object_GetIndex(&globalCtx->objectCtx, OBJECT_BSMASK);

    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[objectIdx].segment);

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_801BB170[index].unk4);

    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
