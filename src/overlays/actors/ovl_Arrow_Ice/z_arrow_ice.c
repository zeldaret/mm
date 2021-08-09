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

void func_809225D0(Vec3f* unkPos, Vec3f* icePos, f32 scale) {
    unkPos->x += ((icePos->x - unkPos->x) * scale);
    unkPos->y += ((icePos->y - unkPos->y) * scale);
    unkPos->z += ((icePos->z - unkPos->z) * scale);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/func_80922628.s")

void func_809227F4(ArrowIce* this, GlobalContext* globalCtx) {
    EnArrow* arrow;
    f32 distanceScaled;
    s32 pad;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;
    distanceScaled = Math_Vec3f_DistXYZ(&this->unk_14C, &this->actor.world.pos) * (1.0f / 24.0f);
    this->unk_158 = distanceScaled;
    if (distanceScaled < 1.0f) {
        this->unk_158 = 1.0f;
    }
    func_809225D0(&this->unk_14C, &this->actor.world.pos, 0.05f);

    if (arrow->unk_261 & 1) {
        Audio_PlayActorSound2(&this->actor, NA_SE_IT_EXPLOSION_ICE);
        ArrowIce_SetupAction(this, func_80922628);
        this->unk_146 = 32;
        this->unk_148 = 255;
    } else if (arrow->unk_260 < 34) {
        if (this->unk_148 < 35) {
            Actor_MarkForDeath(&this->actor);
        } else {
            this->unk_148 -= 25;
        }
    }
}

void ArrowIce_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArrowIce* this = THIS;

    if ((globalCtx->msgCtx.unk11F22 == 0xE) || (globalCtx->msgCtx.unk11F22 == 0x12)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actionFunc(this, globalCtx);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Ice/ArrowIce_Draw.s")
