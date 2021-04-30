/*
 * File: z_bg_keikoku_spr.c
 * Overlay: ovl_Bg_Keikoku_Spr
 * Description: Termina Field Fountain Water
 */

#include "z_bg_keikoku_spr.h"

#define FLAGS 0x00000000

#define THIS ((BgKeikokuSpr*)thisx)

void BgKeikokuSpr_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSpr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSpr_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKeikokuSpr_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Keikoku_Spr_InitVars = {
    ACTOR_BG_KEIKOKU_SPR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KEIKOKU_OBJ,
    sizeof(BgKeikokuSpr),
    (ActorFunc)BgKeikokuSpr_Init,
    (ActorFunc)BgKeikokuSpr_Destroy,
    (ActorFunc)BgKeikokuSpr_Update,
    (ActorFunc)BgKeikokuSpr_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 20, ICHAIN_STOP),
};

extern Gfx D_06000100[];
extern MaterialAnimation D_060001F8;
extern Gfx D_06000300[];
extern MaterialAnimation D_060003F8;
extern Gfx D_06000500[];
extern MaterialAnimation D_060005F8;

void BgKeikokuSpr_Init(Actor* thisx, GlobalContext* globalCtx) {
    Actor_ProcessInitChain(thisx, sInitChain);
}

void BgKeikokuSpr_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void BgKeikokuSpr_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void BgKeikokuSpr_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Scene_DrawMaterialAnim(globalCtx, Lib_SegmentedToVirtual(&D_060001F8));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06000100);
    Scene_DrawMaterialAnim(globalCtx, Lib_SegmentedToVirtual(&D_060003F8));
    gSPDisplayList(POLY_XLU_DISP++, D_06000300);
    Scene_DrawMaterialAnim(globalCtx, Lib_SegmentedToVirtual(&D_060005F8));
    gSPDisplayList(POLY_XLU_DISP++, D_06000500);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
