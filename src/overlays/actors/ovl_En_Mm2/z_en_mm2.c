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

#include "overlays/ovl_En_Mm2/ovl_En_Mm2.c"

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
    gSPDisplayList(gfxCtx->polyOpa.p++, &sEnMm2DL);
}
