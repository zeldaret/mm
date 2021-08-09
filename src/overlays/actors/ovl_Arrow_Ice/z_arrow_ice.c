#include "z_arrow_ice.h"

#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"

#define FLAGS 0x02000010

#define THIS ((ArrowIce*)thisx)

void ArrowIce_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowIce_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowIce_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowIce_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809224DC(ArrowIce* this, GlobalContext* globalCtx);
void func_80922628(ArrowIce* this, GlobalContext* globalCtx);
void func_809227F4(ArrowIce* this, GlobalContext* globalCtx);

void ArrowIce_SetupAction(ArrowIce* this, ArrowIceActionFunc actionFunc);

#include "z_arrow_ice_gfx.c"

const ActorInit Arrow_Ice_InitVars = {
    ACTOR_ARROW_ICE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowIce),
    (ActorFunc)ArrowIce_Init,
    (ActorFunc)ArrowIce_Destroy,
    (ActorFunc)ArrowIce_Update,
    (ActorFunc)ArrowIce_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

extern UNK_TYPE D_0E0002E0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/D_80924200.s")

void ArrowIce_SetupAction(ArrowIce* this, ArrowIceActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArrowIce_Init(Actor* thisx, GlobalContext* globalCtx) {
    ArrowIce* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_144 = 0;
    this->unk_158 = 1.0f;
    ArrowIce_SetupAction(this, func_809224DC);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_148 = 0x64;
    this->unk_146 = 0;
    this->unk_15C = 0.0f;
}

void ArrowIce_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    func_80115D5C(globalCtx);
}

void func_809224DC(ArrowIce* this, GlobalContext* globalCtx) {
    EnArrow* arrow;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->unk_144 < 10) {
        this->unk_144 += 1;
    }
    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    func_800B9010(&this->actor, NA_SE_PL_ARROW_CHARGE_ICE - SFX_FLAG);

    // if arrow has no parent, player has fired the arrow
    if (arrow->actor.parent == NULL) {
        this->unk_14C = this->actor.world.pos;
        this->unk_144 = 10;
        ArrowIce_SetupAction(this, func_809227F4);
        this->unk_148 = 255;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_809225D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_80922628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_809227F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Draw.s")
