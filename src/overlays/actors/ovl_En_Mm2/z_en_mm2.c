/*
 * File: z_en_mm2.c
 * Overlay: ovl_En_Mm2
 * Description: Postman's Letter to Himself
 */

#include "z_en_mm2.h"

#define FLAGS 0x00000010

#define THIS ((EnMm2*)thisx)

void EnMm2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809A2080(EnMm2* this, GlobalContext* globalCtx);
void func_809A20FC(EnMm2* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Mm2_InitVars = {
    ACTOR_EN_MM2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMm2),
    (ActorFunc)EnMm2_Init,
    (ActorFunc)EnMm2_Destroy,
    (ActorFunc)EnMm2_Update,
    (ActorFunc)EnMm2_Draw,
};

#endif

extern Gfx* D_809A29D8;
/*static Gfx sDisplayList[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, SHADE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0xFF, 0xFF, 0xFF, 0x9B, 0xFF),
    gsDPSetEnvColor(0x87, 0x00, 0x00, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(0x809A2270, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(0x809A2870, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 6, 0),
    gsSP2Triangles(6, 5, 7, 0, 6, 9, 4, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(0x809A2670, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 0xFF, 0xFF, 0xFF, 0xFF),
    gsSPVertex(0x809A2910, 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 5, 4, 0),
    gsSP2Triangles(0, 8, 3, 0, 6, 9, 4, 0),
    gsSP2Triangles(2, 10, 0, 0, 4, 11, 7, 0),
    gsSPEndDisplayList(),
};*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm2/EnMm2_Init.s")
void EnMm2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMm2* this = (EnMm2*)thisx;
    Actor_SetScale(&this->actor, 0.015f);
    this->actionFunc = func_809A20FC;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm2/EnMm2_Destroy.s")
void EnMm2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm2/func_809A2080.s")
void func_809A2080(EnMm2* this, GlobalContext* globalCtx) {
    u8 temp_v0;

    temp_v0 = func_80152498(&globalCtx->msgCtx);

    if (temp_v0 != 2) {
        if (temp_v0 == 5 && func_80147624(globalCtx)) {
            func_801477B4(globalCtx);
            this->actionFunc = func_809A20FC;
        }
    } else {
        this->actionFunc = func_809A20FC;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm2/func_809A20FC.s")
void func_809A20FC(EnMm2* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, 0x277BU, &this->actor);
        this->actionFunc = func_809A2080;
    } else if ((this->actor.xzDistToPlayer < 60.0f) && (Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx))) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm2/EnMm2_Update.s")
void EnMm2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMm2* this = (EnMm2*)thisx;
    this->actionFunc(this, globalCtx);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm2/EnMm2_Draw.s")
void EnMm2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx;
    EnMm2* this = (EnMm2*)thisx;

    gfxCtx = globalCtx->state.gfxCtx;
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
    gSPDisplayList(gfxCtx->polyOpa.p++, (u32)(&D_809A29D8));
}