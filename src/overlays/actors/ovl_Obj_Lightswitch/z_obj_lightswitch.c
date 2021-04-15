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

void func_80960088(ObjLightswitch *this);
void func_80960224(ObjLightswitch *this);
void func_80960088(ObjLightswitch *this);
void func_80960424(ObjLightswitch *this);
void func_8096012C(ObjLightswitch *this);
void func_8096034C(ObjLightswitch *this);


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

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00202000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 19 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, sJntSphElementsInit,
};

// segmented addresses for poly opa func
void* D_80960BC4[] = {
    0x06000C20,
    0x06000420,
    0x06001420,
};

s32 D_80960BD0 = 0xFFFFA0A0;

s32 D_80960BD4 = 0xFF000000;

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

void func_8095FBF0(ObjLightswitch* this, GlobalContext *arg1) {
    s8 pad;

    Collider_InitJntSph(arg1, &this->collider);
    Collider_SetJntSph(arg1, &this->collider, &this->actor, &sJntSphInit, this->unk164);
    this->actor.colChkInfo.mass = 0xFF;
    SysMatrix_SetStateRotationAndTranslation(this->actor.world.pos.x, 
        this->actor.world.pos.y + (this->actor.shape.yOffset * this->actor.scale.y),
        this->actor.world.pos.z, &this->actor.shape);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
    Collider_UpdateSpheres(0, &this->collider);
}

// set params based switch flag
void func_8095FC94(ObjLightswitch *this, GlobalContext *globalCtx, s32 set) {
    if (this){} // likely optimized out

    if (set) {
        Actor_SetSwitchFlag(globalCtx, (this->actor.params >> 8) & 0x7F);
    } else {
        Actor_UnsetSwitchFlag(globalCtx, (this->actor.params >> 8) & 0x7F);
    }
}

// issue: mips2c misunderstand the whole function because of non-existent vec3f detection
/*
void func_8095FCEC(ObjLightswitch *this, GlobalContext *globalCtx) {
    Vec3f tempVec3f;
    //f32 sp60;
    //f32 sp5C;
    f32 sinResult;
    f32 cosResult;
    //f32 sp40;
    f32 *temp_a1;
    f32 tempResult;
    f32 temp_f12;
    f32 randomOutput;
    f32 fabsResult;
    f32 tempResult3;
    f32 temp_f2_2;
    f32 tempResult5;
    s16 temp_v0;
    f32 tempResult2;
    f32 tempResult4;
    s16 phi_return;
    f32 phi_f2_2;

    sinResult = Math_SinS(this->actor.shape.rot.y);
    cosResult = Math_CosS(this->actor.shape.rot.y);
    temp_v0 = this->unk1AE;
    phi_return = temp_v0;
    if ((s32) temp_v0 >= 0x1900) {
        tempResult = (1.0f - ((f32) temp_v0 * D_80960BF0)) * 400.0f;
        if (tempResult > 60.0f) {
            tempResult2 = 60.0f;
        } else {
            tempResult2 = tempResult;
        }
        //sp40 = tempResult2;
        tempResult3 = Rand_ZeroOne() * ((tempResult2 - 30.0f) + 30.0f);
        temp_f12 = tempResult3 - 30.0f;

        if (tempResult3 > 30.0f) {
            tempResult4 = 30.0f;
        } else {
            tempResult3 = 900.0f - (temp_f12 * temp_f12);
            if (tempResult3 < 100.0f) {
                tempResult3 = 100.0f;
            }
            tempResult4 = sqrtf(tempResult3);
        }

        tempResult5 = 2.0f * ((Rand_ZeroOne() - 0.5f) * tempResult4);
        fabsResult = fabsf(tempResult5);
        //sp40 = fabsResult;
        randomOutput = (Rand_ZeroOne() * 10.0f) + ((30.0f - fabsResult) * 0.5f);
        //temp_a1 = &sp5C;
        tempVec3f.x = this->actor.world.pos.x + ((randomOutput * sinResult) + (tempResult5 * cosResult));
        tempVec3f.y = this->actor.world.pos.y + temp_f12 + 10.0f;
        tempVec3f.z = this->actor.world.pos.z + ((randomOutput * cosResult) - (tempResult5 * sinResult));
        //EffectSsDeadDb_Spawn(randomOutput, fabsResult, globalCtx,
             //&tempVec3f, &D_801D15B0, &D_801D15B0, 
             //&D_80960BD0, &D_80960BD4, 0x64, 0, 9);
        // issue: where the hell did velocity and acc go?
        EffectSsDeadDb_Spawn(globalCtx, &tempVec3f, NULL, NULL,
             &D_801D15B0, &D_801D15B0, 
             &D_80960BD0, &D_80960BD4, 100, 0, 9);

    }
}
// */
//s16 func_8095FCEC(ObjLightswitch *this, GlobalContext *globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Lightswitch_0x8095FBF0/func_8095FCEC.asm")

void ObjLightswitch_Init(Actor* thisx, GlobalContext *globalCtx) {
    ObjLightswitch* this = THIS;
    s8 pad[4];
    u32 switchFlagResult;
    s32 previouslyTriggered;

    switchFlagResult = Actor_GetSwitchFlag(globalCtx, (this->actor.params >> 8) & 0x7F);
    previouslyTriggered = 0;
    Actor_ProcessInitChain(&this->actor, &sInitChain);
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
