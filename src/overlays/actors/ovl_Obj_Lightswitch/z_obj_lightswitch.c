#include "z_obj_lightswitch.h"

#define FLAGS 0x00000010

#define THIS ((ObjLightswitch*)thisx)

void ObjLightswitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLightswitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLightswitch_Update(Actor* thisx, GlobalContext* globalCtx);
//#void ObjLightswitch_Update(ObjLightswitch* this, GlobalContext* globalCtx);
void ObjLightswitch_Draw(Actor* thisx, GlobalContext* globalCtx);

// action func
void func_809600BC(ObjLightswitch* this, GlobalContext* globalCtx);
void func_80960014(ObjLightswitch* this, GlobalContext* globalCtx);
void func_80960148(ObjLightswitch* this, GlobalContext* globalCtx);
void func_80960260(ObjLightswitch* this, GlobalContext* globalCtx);
void func_80960370(ObjLightswitch* this, GlobalContext* globalCtx);
void func_80960440(ObjLightswitch* this, GlobalContext* globalCtx);

// other func
void func_80960088(ObjLightswitch *this);
void func_80960224(ObjLightswitch *this);

// unk func
void func_80960088(ObjLightswitch *this);
void func_80960424(ObjLightswitch *this);
void func_8096012C(ObjLightswitch *this);
void func_8096034C(ObjLightswitch *this);

/*
const ActorInit Obj_Lightswitch_InitVars = {
    ACTOR_OBJ_LIGHTSWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_LIGHTSWITCH,
    sizeof(ObjLightswitch),
    (ActorFunc)ObjLightswitch_Init,
    (ActorFunc)ObjLightswitch_Destroy,
    (ActorFunc)ObjLightswitch_Update,
    (ActorFunc)ObjLightswitch_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FBF0.asm")

//what
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FC94.asm")

/*
// what a fucking stack vomit exhibit
s16 func_8095FCEC(ObjLightswitch *this, GlobalContext *globalCtx) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sinResult;
    f32 cosResult;
    f32 sp4C;
    f32 sp40;
    f32 *temp_a1;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    s16 temp_v0;
    f32 phi_f14;
    f32 phi_f2;
    s16 phi_return;
    f32 phi_f2_2;

    sinResult = Math_SinS(this->actor.shape.rot.y);
    cosResult = Math_CosS(this->actor.shape.rot.y);
    temp_v0 = this->unk1AE;
    phi_return = temp_v0;
    if ((s32) temp_v0 >= 0x1900) {
        temp_f0 = (1.0f - ((f32) temp_v0 * D_80960BF0)) * 400.0f;
        if (temp_f0 > 60.0f) {
            phi_f14 = 60.0f;
        } else {
            phi_f14 = temp_f0;
        }
        sp40 = phi_f14;
        temp_f2 = Rand_ZeroOne() * ((phi_f14 - 30.0f) + 30.0f);
        temp_f12 = temp_f2 - 30.0f;
        sp4C = temp_f12;

        if (temp_f2 > 30.0f) {
            phi_f2 = 30.0f;
        } else {
            temp_f2_2 = 900.0f - (temp_f12 * temp_f12);
            phi_f2_2 = temp_f2_2;
            if (temp_f2_2 < 100.0f) {
                phi_f2_2 = 100.0f;
            }
            phi_f2 = sqrtf(phi_f2_2);
        }

        temp_f2_3 = 2.0f * ((Rand_ZeroOne() - 0.5f) * phi_f2);
        temp_f14 = fabsf(temp_f2_3);
        sp40 = temp_f14;
        temp_f12_2 = (Rand_ZeroOne() * 10.0f) + ((30.0f - temp_f14) * 0.5f);
        temp_a1 = &sp5C;
        sp5C = this->actor.world.pos.x + ((temp_f12_2 * sinResult) + (temp_f2_3 * cosResult));
        sp60 = this->actor.world.pos.y + sp4C + 10.0f;
        sp64 = this->actor.world.pos.z + ((temp_f12_2 * cosResult) - (temp_f2_3 * sinResult));
        phi_return = EffectSsDeadDb_Spawn(temp_f12_2, temp_f14, globalCtx, temp_a1, &D_801D15B0, &D_801D15B0, &D_80960BD0, &D_80960BD4, 0x64, 0, 9);
    }
    return phi_return;
}
*/
s16 func_8095FCEC(ObjLightswitch *this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FCEC.asm")

void ObjLightswitch_Init(Actor* thisx, GlobalContext *globalCtx) {
    ObjLightswitch* this = THIS;
    s8 pad[4];
    u32 switchFlagResult;
    s32 previouslyTriggered;

    switchFlagResult = Actor_GetSwitchFlag(globalCtx, (this->actor.params >> 8) & 0x7F);
    previouslyTriggered = 0;
    Actor_ProcessInitChain(&this->actor, &D_80960BD8);
    Actor_SetHeight(&this->actor, 0.0f);

    if (switchFlagResult != 0) {
        if (((this->actor.params >> 4) & 3) == 3) {
            previouslyTriggered = 1;
        } else {
            func_80960224(this);
        }
    } else {
        func_80960088(this);
    }

    func_8095FBF0(this, globalCtx);

    // maybe.. light switch placed on a location where the background has its own visual that isn't part of the actor?
    if (((this->actor.params >> 3) & 1) != 0) {
        this->actor.draw = NULL;
    }

    if (previouslyTriggered) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjLightswitch_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    ObjLightswitch* this = THIS;
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_8095FFF8(ObjLightswitch* this, ObjLightswitchSetupFunc setupFunc, u32 arg2) {
    this->setupFunc = setupFunc;
    this->unk1BC = arg2;
    this->actionFunc = func_80960014;
}

void func_80960014(ObjLightswitch *this, GlobalContext *globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) this->actor.cutscene, &this->actor);
        func_8095FC94(this, globalCtx, this->unk1BC);
        this->unk1BD = 50;
        this->setupFunc(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80960088(ObjLightswitch *this) {
    this->unk1B6 = 0;
    this->unk1A8 = 0x26C0;
    this->unk1AA = 0x1F40;
    this->unk1AC = 0x3FC0;
    this->unk1AE = 0x3FC0;
    this->actionFunc = func_809600BC;
}

// action func
void func_809600BC(ObjLightswitch *this, GlobalContext *globalCtx) {
    s32 paramValue;

    paramValue = (this->actor.params >> 4) & 3;
    if (this->unk1B5 >= 10) {
        if (paramValue == 3) {
            func_8095FFF8(this, func_80960424, 1);
            return;
        }
        if (paramValue == 1) {
            this->unk1B5 = 0;
        }
        func_8095FFF8(this, func_8096012C, 1);
    }
}

// unk func ptr
void func_8096012C(ObjLightswitch *this) {
    this->unk1B6 = 0;
    this->unk1B4 = 0;
    this->actionFunc = func_80960148;
}

//action func
void func_80960148(ObjLightswitch *this, GlobalContext *globalCtx) { 
    if (this->unk1B4 == 0) {
        Audio_PlayActorSound2(&this->actor, 0x286F);
    }
    this->unk1B4++;

    //Math_StepToS(&this->unk1B2, (u16)-0xAA, 0xA);
    Math_StepToS(&this->unk1B2, -170, 10);
    this->unk1B0 += this->unk1B2;
    this->unk1A8 = (this->unk1B4 * 0x140) + 0x26C0;
    this->unk1AA = (this->unk1B4 * 0x1A0) + 0x1F40;

    if (this->unk1B4 >= 20) {
        func_80960224(this);
    } else if (this->unk1B4 == 15) {
        this->unk1B6 = 1; // enable?
        Audio_PlayActorSound2(this, 0x2815);
    }
}

void func_80960224(ObjLightswitch *this) {
    this->unk1B6 = 2;
    this->unk1A8 = 0x3FC0;
    this->unk1AA = 0x3FC0;
    this->unk1AC = 0x3FC0;
    this->unk1AE = 0x3FC0;
    this->unk1B2 = -0xAA;
    this->unk1B4 = 0;
    this->actionFunc = func_80960260;
}

//action func
void func_80960260(ObjLightswitch *this, GlobalContext *globalCtx) {
    s32 paramType = ((s32) this->actor.params >> 4) & 3;

    if (paramType == 0) {
        if (Actor_GetSwitchFlag(globalCtx, ((s32) this->actor.params >> 8) & 0x7F) == 0) {
            func_8096034C(this);
        }
    } else if (paramType == 1) {
        if ((s32) this->unk1B5 >= 0xA) {
            this->unk1B5 = 0;
            func_8095FFF8(this, func_8096034C, 0);
        }
    } else if (this->unk1B5 == 0) {
        if ((s32) this->unk1B4 >= 0xD) {
            func_8095FC94(this, globalCtx, 0);
            func_8096034C(this);
        } else {
            this->unk1B4 += 1;
        }
    } else {
        this->unk1B4 = 0;
    }
    this->unk1B0 += this->unk1B2;
}

// unk func ptr
void func_8096034C(ObjLightswitch *this) {
    this->unk1B4 = 0x14;
    this->unk1B6 = 1;
    this->actionFunc = func_80960370;
}

void func_80960370(ObjLightswitch *this, GlobalContext *globalCtx) {
    this->unk1B4--;
    Math_StepToS(&this->unk1B2, 0, 10);
    this->unk1B0 += this->unk1B2;
    this->unk1A8 = (this->unk1B4 * 0x140) + 0x26C0;
    this->unk1AA = (this->unk1B4 * 0x1A0) + 0x1F40;

    if (this->unk1B4 <= 0) {
        func_80960088(this);
    } else if (this->unk1B4 == 0xF) {
        this->unk1B6 = 0;
        Audio_PlayActorSound2(&this->actor, 0x2815);
    }
}

// unk func ptr
void func_80960424(ObjLightswitch *this) {
    this->unk1AE = 0x3FC0;
    this->actionFunc = func_80960440;
}

// action func
void func_80960440(ObjLightswitch* this, GlobalContext* globalCtx) {
    this->unk1AE -= 0xC8;
    func_8095FCEC(this, globalCtx);
    if (this->unk1AE < 0) {
        Actor_MarkForDeath((Actor *) this);
    } else {
        func_800B9010(&this->actor, 0x321F);
    }
} 


void ObjLightswitch_Update(Actor* thisx, GlobalContext *globalCtx) {
    ObjLightswitch* this = THIS;
    s8 pad;

    if ((this->collider.base.acFlags & AC_HIT) != 0) {
        if ((this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0x2000) != 0) {
            this->unk1B5 = 10;
        } else if (((this->actor.params >> 4) & 3) == 1) {
            if (this->unk1B5 == 0) {
                if ((this->pad1B7 & 2) == 0) {
                    this->unk1B5 = 1;
                }
            } else if (this->unk1B5 < 10) {
                this->unk1B5++;
            }
        } else {
            if (this->unk1B5 < 10) { 
                this->unk1B5++;
            }
        }
    } else {
        this->unk1B5 = 0;
    }

    if ((this->unk1BD > 0) && ( (s32) this->actionFunc !=  (s32) func_80960014 )) {
        this->unk1BD--;
        if (this->unk1BD == 0) {
            ActorCutscene_Stop( this->actor.cutscene);
        }
    }

    this->actionFunc(this, globalCtx);
    if (this->actor.update != 0) {
        this->pad1B7 = this->collider.base.acFlags;
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}

// opa func
void func_809605F4(ObjLightswitch* this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightswitch_0x8095FBF0/func_809605F4.asm")

// xlu func
void func_80960880(ObjLightswitch* this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightswitch_0x8095FBF0/func_80960880.asm")

void ObjLightswitch_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjLightswitch* this = THIS;
    s32 result;

    result = (this->unk1AE >> 6) & 0xFF;
    if (((( this->actor.params >> 4) & 3) == 3) && (result > 0) && (result < 0xFF)) {
        func_80960880(this, globalCtx);
    } else { 
        func_809605F4(this, globalCtx);
    }
}
