#include "z_bg_iknin_susceil.h"

#define FLAGS 0x00000030

#define THIS ((BgIkninSusceil*)thisx)

void BgIkninSusceil_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkninSusceil_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkninSusceil_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkninSusceil_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C0AB44(BgIkninSusceil* this, GlobalContext* globalCtx);
void func_80C0AB88(BgIkninSusceil* this);
void func_80C0ABA8(BgIkninSusceil* this, GlobalContext* globalCtx);
void func_80C0AC74(BgIkninSusceil* this);
void func_80C0AC90(BgIkninSusceil* this, GlobalContext* globalCtx);
void func_80C0ACD4(BgIkninSusceil* this);
void func_80C0ACE8(BgIkninSusceil* this, GlobalContext* globalCtx);
void func_80C0AD44(BgIkninSusceil* this);
void func_80C0AD64(BgIkninSusceil* this, GlobalContext* globalCtx);
void func_80C0AE5C(BgIkninSusceil* this, GlobalContext* globalCtx);

/*
const ActorInit Bg_Iknin_Susceil_InitVars = {
    ACTOR_BG_IKNIN_SUSCEIL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNINSIDE_OBJ,
    sizeof(BgIkninSusceil),
    (ActorFunc)BgIkninSusceil_Init,
    (ActorFunc)BgIkninSusceil_Destroy,
    (ActorFunc)BgIkninSusceil_Update,
    (ActorFunc)BgIkninSusceil_Draw,
};
*/

extern InitChainEntry D_80C0B100;
extern CollisionHeader D_0600CBAC;
extern AnimatedMaterial D_0600C670;
extern Gfx D_0600C308[];

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil_0x80C0A740/func_80C0A740.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil_0x80C0A740/func_80C0A804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil_0x80C0A740/func_80C0A838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil_0x80C0A740/func_80C0A86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil_0x80C0A740/func_80C0A95C.asm")

void BgIkninSusceil_Init(Actor *thisx, GlobalContext *globalCtx) {
    BgIkninSusceil* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, &D_80C0B100);
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_0600CBAC);
    this->unk15C = Lib_SegmentedToVirtual(&D_0600C670);
    func_80C0AC74(this);
}

void BgIkninSusceil_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    BgIkninSusceil* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80C0AB14(BgIkninSusceil* this) {
    this->unk164 = 0x6E;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 365.0f;
    this->actionFunc = func_80C0AB44;
}

void func_80C0AB44(BgIkninSusceil* this, GlobalContext* globalCtx) {
    if (this->unk164 > 0) {
        this->unk164 -= 1;
        return;
    }

    if (func_80C0A740(this, globalCtx) != 0) {
        func_80C0AB88(this);
    }
}

void func_80C0AB88(BgIkninSusceil* this) {
    this->actionFunc = func_80C0ABA8;
    this->dyna.actor.velocity.y = -10.0f;
}

void func_80C0ABA8(BgIkninSusceil* this, GlobalContext* globalCtx) {
    this->dyna.actor.velocity.y += -0.7f;
    this->dyna.actor.velocity.y *= 0.93f;
    this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
    if (this->dyna.actor.world.pos.y <= this->dyna.actor.home.pos.y) {
        func_80C0A86C(this, globalCtx, 4, 0xE, 1);
        Actor_UnsetSwitchFlag(globalCtx, this->dyna.actor.params & 0x7F);
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_BIGWALL_BOUND);
        func_80C0AC74(this);
        return;
    }
    func_800B9010(&this->dyna.actor, NA_SE_EV_ICE_PILLAR_FALL - SFX_FLAG);
}

void func_80C0AC74(BgIkninSusceil* this) {
    this->actionFunc = func_80C0AC90;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
}

void func_80C0AC90(BgIkninSusceil* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->dyna.actor.params & 0x7F)) {
        func_80C0ACD4(this);
    }
}

void func_80C0ACD4(BgIkninSusceil* this) {
    this->actionFunc = func_80C0ACE8;
}

void func_80C0ACE8(BgIkninSusceil* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        func_80C0AD44(this);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
}

void func_80C0AD44(BgIkninSusceil* this) {
    this->actionFunc = func_80C0AD64;
    this->dyna.actor.velocity.y = 5.0f;
}

void func_80C0AD64(BgIkninSusceil* this, GlobalContext* globalCtx) {
    this->dyna.actor.velocity.y += 0.46f;
    this->dyna.actor.velocity.y *= 0.98f;
    if (Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 365.0f, 0.5f, this->dyna.actor.velocity.y, 1.0f) < 0.1f) {
        func_80C0A86C(this, globalCtx, 1, 0xE, 3);
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        func_80C0AB14(this);
        return;
    }
    func_800B9010(&this->dyna.actor, NA_SE_EV_ICE_PILLAR_RISING - SFX_FLAG);
}

void func_80C0AE3C(BgIkninSusceil* this) {
    this->actionFunc = func_80C0AE5C;
    this->dyna.actor.velocity.y = 30.0f;
}

void func_80C0AE5C(BgIkninSusceil* this, GlobalContext* globalCtx) {
    this->dyna.actor.velocity.y += -0.1f;
    this->dyna.actor.velocity.y *= 0.95f;
    if (this->dyna.actor.velocity.y < 1.0f) {
        this->dyna.actor.velocity.y = 1.0f;
    } else {
        this->dyna.actor.velocity.y = this->dyna.actor.velocity.y;
    }
    this->dyna.actor.world.pos.y = this->dyna.actor.world.pos.y + this->dyna.actor.velocity.y;
    if ((this->dyna.actor.home.pos.y + 365.0f) < this->dyna.actor.world.pos.y) {
        func_80C0A86C(this, globalCtx, 3, 0xE, 2);
        func_80C0AB14(this);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil_0x80C0A740/BgIkninSusceil_Update.asm")

void BgIkninSusceil_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIkninSusceil* this = THIS;

    AnimatedMat_Draw(globalCtx, this->unk15C);
    func_800BDFC0(globalCtx, D_0600C308);
}
