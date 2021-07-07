/*
 * File: z_en_niw.c
 * Overlay: ovl_En_Niw
 * Description: Cucco (Chicken) (Japanese: Niwatori)
 */

#include "z_en_niw.h"

#define FLAGS 0x00800010

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_SetupIdle(EnNiw* this);
void func_808919E8(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Thrown(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_SetupRunning(EnNiw* this);
void func_808924B0(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Swimming(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Trigger(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Upset(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_SetupCuccoStorm(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_CuccoStorm(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_SpawnAttackNiw(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Held(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_UpdateFeather(EnNiw* this, GlobalContext* globalCtx);
void func_808932B0(EnNiw* this, GlobalContext* globalCtx); // draw feather
void EnNiw_CheckRage(EnNiw* this, GlobalContext* globalCtx);
void func_80891320(EnNiw* this, GlobalContext* globalCtx, s16 arg2);
s32 EnNiw_LimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, struct Actor* actor);
void EnNiw_SpawnFeather(EnNiw* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale);

// turned on during cucco storm, but not read by anything?
// maybe read by En_Attack_Niw
s16 D_80893460 = false;

const ActorInit En_Niw_InitVars = {
    ACTOR_EN_NIW,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnNiw),
    (ActorFunc)EnNiw_Init,
    (ActorFunc)EnNiw_Destroy,
    (ActorFunc)EnNiw_Update,
    (ActorFunc)EnNiw_Draw,
};

static f32 D_80893484[] = {
    5000.0f,
    -5000.0f,
};
static f32 D_80893486[] = {
    5000.0f,
    3000.0f,
    4000.0f,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT5,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_NO_PUSH | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 15, 25, 4, { 0, 0, 0 } },
};

static Vec3f D_808934C4 = {
    90000.0f,
    90000.0f,
    90000.0f,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
};

static Vec3f D_808934DC = {
    90000.0f,
    90000.0f,
    90000.0f,
};

static Vec3f D_808934E8 = {
    90000.0f,
    90000.0f,
    90000.0f,
};

static s32 pad = 0;

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = (EnNiw*)thisx;
    Vec3f dTemp = D_808934C4;

    if (this->actor.params < 0) { // all neg values become zero
        this->actor.params = ENNIW_TYPE_REGULAR;
    }

    Math_Vec3f_Copy(&this->unk2BC, &dTemp);

    this->niwType = this->actor.params;
    Actor_ProcessInitChain(&this->actor, sInitChain);

    this->actor.flags |= 0x1; // targetable ON

    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 25.0f);

    SkelAnime_InitSV(globalCtx, &this->skelanime, &D_06002530, &D_060000E8, this->limbDrawTbl,
                     this->transitionDrawtable, ENNIW_LIMBCOUNT);
    Math_Vec3f_Copy(&this->unk2A4, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->unk2B0, &this->actor.world.pos);

    this->unk308 = 10.0f;
    Actor_SetScale(&this->actor, 0.01f);

    if (this->niwType == ENNIW_TYPE_UNK1) {
        Actor_SetScale(&this->actor, (BREG(86) / 10000.0f) + 0.004f);
    }

    // random health between 10-20
    this->actor.colChkInfo.health = Rand_ZeroFloat(9.99f) + 10.0f;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    if (this->niwType == ENNIW_TYPE_REGULAR) {
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    }

    if (this->niwType == ENNIW_TYPE_UNK2) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
        this->sfxTimer1 = 30;
        this->unkTimer250 = 30;
        this->actor.flags &= ~0x1; // targetable OFF
        this->unknownState28E = 4;
        this->actionFunc = EnNiw_Held;
        this->actor.speedXZ = 0.0f;
        this->unk2BC.z = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
    } else {
        EnNiw_SetupIdle(this);
    }
}

void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = (EnNiw*)thisx;

    if (this->niwType == ENNIW_TYPE_REGULAR) {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

void func_80891320(EnNiw* this, GlobalContext* globalCtx, s16 arg2) {
    f32 tempOne = 1.0f;

    if (this->unkTimer24C == 0) {
        if (arg2 == 0) {
            this->unk264[0] = 0.0f;
        } else {
            this->unk264[0] = (-10000.0f) * tempOne;
        }
        this->unk292 += 1;
        this->unkTimer24C = 3;
        if ((this->unk292 % 2) == 0) {
            this->unk264[0] = 0.0f;
            if (arg2 == 0) {
                this->unkTimer24C = Rand_ZeroFloat(30.0f);
            }
        }
    }
    if (this->unkTimer24E == 0) {
        this->unk296++;
        this->unk296 &= 1;
        switch (arg2) {
            case 0:
                this->unk264[2] = 0.0f;
                this->unk264[1] = 0.0f;
                break;
            case 1:
                this->unkTimer24E = 3;
                this->unk264[2] = 7000.0f * tempOne;
                this->unk264[1] = 7000.0f * tempOne;
                if (this->unk296 == 0) {
                    this->unk264[2] = 0.0f;
                    this->unk264[1] = 0.0f;
                }
                break;
            case 2:
                this->unkTimer24E = 2;
                this->unk264[2] = -10000.0f;
                this->unk264[1] = -10000.0f;
                this->unk264[7] = 25000.0f;
                this->unk264[5] = 25000.0f;
                this->unk264[8] = 6000.0f;
                this->unk264[6] = 6000.0f;
                if (this->unk296 == 0) {
                    this->unk264[7] = 8000.0f;
                    this->unk264[5] = 8000.0f;
                }
                break;
            case 3:
                this->unkTimer24E = 2;
                this->unk264[5] = 10000.0f;
                this->unk264[7] = 10000.0f;
                if (this->unk296 == 0) {
                    this->unk264[5] = 3000.0f;
                    this->unk264[7] = 3000.0f;
                }
                break;
            case 4:
                this->unkTimer24C = 5;
                break;
            case 5:
                this->unkTimer24E = 5;
                this->unk264[5] = 14000.0f;
                this->unk264[7] = 14000.0f;
                if (this->unk296 == 0) {
                    this->unk264[5] = 10000.0f;
                    this->unk264[7] = 10000.0f;
                }
                break;
        }
    }
    if (this->unk264[9] != this->limbFRot) {
        Math_ApproachF(&this->limbFRot, this->unk264[9], 0.5f, 4000.0f);
    }
    if (this->unk264[0] != this->limbDRot) {
        Math_ApproachF(&this->limbDRot, this->unk264[0], 0.5f, 4000.0f);
    }
    if (this->unk264[2] != this->limb7Rotz) {
        Math_ApproachF(&this->limb7Rotz, this->unk264[2], 0.8f, 7000.0f);
    }
    if (this->unk264[7] != this->limb7Roty) {
        Math_ApproachF(&this->limb7Roty, this->unk264[7], 0.8f, 7000.0f);
    }
    if (this->unk264[8] != this->limb7Rotx) {
        Math_ApproachF(&this->limb7Rotx, this->unk264[8], 0.8f, 7000.0f);
    }
    if (this->unk264[1] != this->limbBRotz) {
        Math_ApproachF(&this->limbBRotz, this->unk264[1], 0.8f, 7000.0f);
    }
    if (this->unk264[5] != this->limbBRoty) {
        Math_ApproachF(&this->limbBRoty, this->unk264[5], 0.8f, 7000.0f);
    }
    if (this->unk264[6] != this->limbBRotx) {
        Math_ApproachF(&this->limbBRotx, this->unk264[6], 0.8f, 7000.0f);
    }
}

void EnNiw_SpawnAttackNiw(EnNiw* this, GlobalContext* globalCtx) {
    f32 xView;
    f32 yView;
    f32 zView;
    Vec3f newNiwPos;
    Actor* attackNiw;

    if ((this->unkTimer252 == 0) && (this->unk290 < 7)) {
        xView = globalCtx->view.focalPoint.x - globalCtx->view.eye.x;
        yView = globalCtx->view.focalPoint.y - globalCtx->view.eye.y;
        zView = globalCtx->view.focalPoint.z - globalCtx->view.eye.z;
        newNiwPos.x = ((Rand_ZeroOne() - 0.5f) * xView) + globalCtx->view.eye.x;
        newNiwPos.y = randPlusMinusPoint5Scaled(0.3f) + (globalCtx->view.eye.y + 50.0f + (yView * 0.5f));
        newNiwPos.z = ((Rand_ZeroOne() - 0.5f) * zView) + globalCtx->view.eye.z;
        attackNiw = Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_ATTACK_NIW,
                                          newNiwPos.x, newNiwPos.y, newNiwPos.z, 0, 0, 0, 0);

        if (attackNiw) {
            this->unk290++;
            this->unkTimer252 = 10;
        }
    }
}

void func_808917F8(EnNiw* this, GlobalContext* globalCtx, s32 arg2) {
    f32 phi_f2;
    f32 targetRotY;
    f32* D_8089348CPtr = D_80893486;

    if (this->unkTimer250 == 0) {
        this->unkTimer250 = 3;
        if (this->actor.bgCheckFlags & 1) {
            // hit floor
            this->actor.velocity.y = 3.5f; // hop up?
        }
    }
    if (this->unkTimer252 == 0) {
        this->unk29A++;
        this->unk29A &= 1;
        this->unkTimer252 = 5;
    }
    if (this->unk29A == 0) {
        phi_f2 = D_8089348CPtr[arg2];
    } else {
        phi_f2 = -D_8089348CPtr[arg2];
    }
    if (arg2 == 1 && (this->unkTimer254 == 0 || (this->actor.bgCheckFlags & 8))) {
        this->unkTimer254 = 150;
        if (this->yawTimer == 0) {
            this->yawTimer = 70;
            this->yawTowardsPlayer = this->actor.yawTowardsPlayer;
        }
    }
    targetRotY = this->yawTowardsPlayer + phi_f2;
    Math_SmoothStepToS(&this->actor.world.rot.y, targetRotY, 3, this->unk300, 0);
    Math_ApproachF(&this->unk300, 3000.0f, 1.0f, 500.0f);
    func_80891320(this, globalCtx, 5);
}

void EnNiw_SetupIdle(EnNiw* this) {
    SkelAnime_ChangeAnim(&this->skelanime, &D_060000E8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060000E8.common), 0,
                         -10.0f);
    this->unknownState28E = 0;
    this->actionFunc = func_808919E8;
}

#ifdef NON_MATCHING
// non-matching: stack offset and regalloc
// EnNiw_Idle
void func_808919E8(EnNiw* this, GlobalContext* globalCtx) {
    s16 s16tmp;
    Vec3f newPos;

    newPos.y = randPlusMinusPoint5Scaled(100.0f);
    newPos.z = randPlusMinusPoint5Scaled(100.0f);
    if (this->niwType == ENNIW_TYPE_REGULAR) {
        if (Actor_HasParent(&this->actor, globalCtx)) {
            // picked up
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
            this->sfxTimer1 = 30;
            this->unkTimer250 = 30;
            this->actor.flags &= ~0x1; // targetable OFF
            this->unknownState28E = 4;
            this->actor.speedXZ = 0.0f;
            this->actionFunc = EnNiw_Held;
            return;
        } else {
            func_800B8BB0(&this->actor, globalCtx);
        }
    } else {
        this->unkTimer252 = 10;
    }

    s16tmp = 0;
    if (this->unkTimer252 != 0) {
        if (Rand_ZeroFloat(3.99f) < 1.0f) {
            this->unk2EA++;
            this->unk2EA &= 1;
        }
        Math_ApproachF(&this->unk264[9], D_80893484[this->unk2EA], 0.5f, 4000.0f);
    }

    if ((this->unkTimer252 == 0) && (this->unkTimer250 == 0)) {
        this->unk298++;

        if (this->unk298 > 7) {
            this->unkTimer252 = Rand_ZeroFloat(30.0f);
            this->unk298 = Rand_ZeroFloat(3.99f);
            // (3.99..) is loaded into f12 for rand_zero, but f12 never released
            // b18:    jal     Rand_ZeroFloat              b18:    jal     Rand_ZeroFloat
            // b1c:    lwc1    $f12,%lo(D_80893554)(at)  i b1c:    lwc1    $f12,%lo(.rodata+0x54)(at)
            // b20:    lwc1    $f12,0x34(sp)             r b20:    lwc1    $f2,0x2c(sp)

            if (newPos.y < 0.0f) {
                newPos.y -= 100.0f;
            } else {
                newPos.y += 100.0f;
            }
            if (newPos.z < 0.0f) {
                newPos.z -= 100.0f;
            } else {
                newPos.z += 100.0f;
            }

            this->unk2B0.x = this->unk2A4.x + newPos.y;
            this->unk2B0.z = this->unk2A4.z + newPos.z;

        } else {
            this->unkTimer250 = 4;
            if (this->actor.bgCheckFlags & 1) {
                this->actor.speedXZ = 0.0f;
                this->actor.velocity.y = 3.5f;
            }
        }
    }

    if (this->unkTimer250 != 0) {
        Math_ApproachZeroF(&this->unk264[9], 0.5f, 4000.0f);
        s16tmp = 1;
        Math_ApproachF(&this->actor.world.pos.x, this->unk2B0.x, 1.0f, this->unk300);
        Math_ApproachF(&this->actor.world.pos.z, this->unk2B0.z, 1.0f, this->unk300);
        Math_ApproachF(&this->unk300, 3.0f, 1.0f, 0.3f);

        newPos.x = this->unk2B0.x - this->actor.world.pos.x;
        newPos.z = this->unk2B0.z - this->actor.world.pos.z;

        if (fabsf(newPos.x) < 10.0f) {
            newPos.x = 0.0;
        }
        if (fabsf(newPos.z) < 10.0f) {
            newPos.z = 0.0;
        }

        if ((newPos.x == 0.0f) && (newPos.z == 0.0f)) {
            this->unkTimer250 = 0;
            this->unk298 = 7;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, Math_Atan2S(newPos.x, newPos.z), 3, this->unk304, 0);
        Math_ApproachF(&this->unk304, 10000.0f, 1.0f, 1000.0f);
    }
    func_80891320(this, globalCtx, s16tmp);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Niw_0x80891060/func_808919E8.asm")
#endif

void EnNiw_Held(EnNiw* this, GlobalContext* globalCtx) {
    Vec3f vec3fcopy;
    s16 rotZ;

    vec3fcopy = D_808934DC;
    if (this->unkTimer250 == 0) {
        this->unk29E = 2;
        this->unkTimer250 = (s32)(Rand_ZeroFloat(1.0f) * 10.0f) + 10;
    }

    this->actor.shape.rot.x = (s16)randPlusMinusPoint5Scaled(5000.0f) + this->actor.world.rot.x;
    this->actor.shape.rot.y = (s16)randPlusMinusPoint5Scaled(5000.0f) + this->actor.world.rot.y;
    this->actor.shape.rot.z = (s16)randPlusMinusPoint5Scaled(5000.0f) + this->actor.world.rot.z;
    if (this->niwType == ENNIW_TYPE_REGULAR) {
        if (Actor_HasNoParent(&this->actor, globalCtx)) {
            this->actor.shape.rot.z = 0;
            rotZ = this->actor.shape.rot.z;
            this->unknownState28E = 5;
            this->actor.flags |= 0x1; // targetable ON
            this->actionFunc = EnNiw_Thrown;
            this->actor.shape.rot.y = rotZ;
            this->actor.shape.rot.x = rotZ;
        }
    } else if (this->unk2BC.z != 0.0f) {
        this->actor.shape.rot.z = 0;
        rotZ = this->actor.shape.rot.z;
        this->actor.velocity.y = 8.0f;
        this->actor.speedXZ = 4.0f;
        this->actor.gravity = -2.0f;
        this->unknownState28E = 5;
        this->unk2EC = 0;
        this->niwType = ENNIW_TYPE_REGULAR;
        this->actor.shape.rot.y = rotZ;
        this->actor.shape.rot.x = rotZ;
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        Math_Vec3f_Copy(&this->unk2BC, &vec3fcopy);
        this->actor.flags |= 0x1; // targetable ON
        this->actionFunc = EnNiw_Thrown;
    }
    func_80891320(this, globalCtx, 2);
}

// action function: recently thrown, and also hopping on the floor
void EnNiw_Thrown(EnNiw* this, GlobalContext* globalCtx) {
    if (this->unk2EC == 0) {
        if (this->actor.bgCheckFlags & 1) {
            this->unk2EC = 1;
            this->unkTimer252 = 80; // hop timer
            this->actor.speedXZ = 0.0f;
            this->actor.velocity.y = 4.0f;
        } else {
            return; // wait until back on floor
        }
    } else {
        if (this->actor.bgCheckFlags & 1) {
            this->sfxTimer1 = 0;
            this->actor.velocity.y = 4.0f; // vertical hop
            this->unk29E = 1;
        }
        if (this->unkTimer252 == 0) {
            this->unkTimer254 = 100;
            this->unkTimer250 = 0;
            this->unk2EC = 0;
            EnNiw_SetupRunning(this);
            return;
        }
    }

    if (Actor_HasParent(&this->actor, globalCtx)) {
        // picked up again before could run off
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
        this->sfxTimer1 = 30;
        this->unk2EC = 0;
        this->unkTimer250 = 30;
        this->actor.flags &= ~0x1; // targetable OFF
        this->unknownState28E = 4;
        this->actionFunc = EnNiw_Held;
        this->actor.speedXZ = 0.0f;
    } else {
        if (this->unkTimer252 > 5) {
            func_800B8BB0(&this->actor, globalCtx);
        }
        func_80891320(this, globalCtx, 2);
    }
}

// action func: swimming and flying away after swimming
void EnNiw_Swimming(EnNiw* this, GlobalContext* globalCtx) {
    Vec3f ripplePos;

    // even if hitting water, keep calling for reinforcements
    // this should just be in update
    if (this->isStormActive) {
        EnNiw_SpawnAttackNiw(this, globalCtx); // spawn attack niw
    }

    this->actor.speedXZ = 2.0f;
    if (this->actor.bgCheckFlags & 0x20) {
        // still touching water
        this->actor.gravity = 0.0f;
        if (this->actor.yDistToWater > 15.0f) {
            this->actor.world.pos.y += 2.0f;
        }
        if (this->unkTimer250 == 0) {
            this->unkTimer250 = 30;
            Math_Vec3f_Copy(&ripplePos, &this->actor.world.pos);
            ripplePos.y += this->actor.yDistToWater;

            EffectSsGRipple_Spawn(globalCtx, &ripplePos, 100, 500, 30);
        }
        if (this->actor.bgCheckFlags & 8) {
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 1.0f;
        }
    } else {
        this->actor.gravity = -2.0f;
        if (this->actor.bgCheckFlags & 8) {
            // has hit a wall
            this->actor.velocity.y = 10.0f; // to the moon
            this->actor.speedXZ = 1.0f;
            this->actor.gravity = 0.0f;
        } else {
            this->actor.speedXZ = 4.0f;
        }

        if (this->actor.bgCheckFlags & 1) {
            this->actor.gravity = -2.0f;
            this->unkTimer254 = 100;
            this->unkTimer250 = 0;
            this->actor.velocity.y = 0.0f;
            if (!this->isStormActive) {
                EnNiw_SetupRunning(this);
            } else {
                this->unknownState28E = 3;
                this->actionFunc = EnNiw_CuccoStorm;
            }
        }
    }
    func_80891320(this, globalCtx, 2);
}

void EnNiw_Trigger(EnNiw* this, GlobalContext* globalCtx) {
    s32 value;
    if (1) {
        value = 1;
    }

    this->unkTimer252 = 10;
    this->unknownState28E = this->unk29C = value;
    this->actionFunc = EnNiw_Upset;
}

void EnNiw_Upset(EnNiw* this, GlobalContext* globalCtx) {
    // assumption: CuccoStorm is split into smaller parts because it used to be a cutscene in OOT
    this->sfxTimer1 = 100;
    if (this->unkTimer252 == 0) {
        this->unkTimer252 = 60;
        this->unkTimer24C = 10;
        this->unk29C = 4;
        this->unknownState28E = 2;
        this->actionFunc = EnNiw_SetupCuccoStorm;
    }

    func_80891320(this, globalCtx, this->unk29C);
}

// the long crow with head back before they descend
void EnNiw_SetupCuccoStorm(EnNiw* this, GlobalContext* globalCtx) {
    f32 viewY;

    this->sfxTimer1 = 100;
    if (this->unkTimer252 == 40) {
        viewY = 14000.0f;
        this->unk264[0] = 10000.0f;
        this->unk264[7] = this->unk264[5] = viewY;
        this->unk264[6] = 0.0f;
        this->unk264[8] = 0.0f;
        this->unk264[1] = 0.0f;
        this->unk264[2] = 0.0f;
        this->unkTimer24C = 10;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
    }
    if (this->unkTimer252 == 0) {
        this->unkTimer252 = 10;
        this->yawTowardsPlayer = this->actor.yawTowardsPlayer;
        this->actor.flags &= ~0x1; // targetable OFF
        this->unknownState28E = 3;
        this->actionFunc = EnNiw_CuccoStorm;
    }
    func_80891320(this, globalCtx, this->unk29C);
}

void EnNiw_CuccoStorm(EnNiw* this, GlobalContext* globalCtx) {
    EnNiw_SpawnAttackNiw(this, globalCtx);
    if (this->unkTimer252 == 1) {
        this->actor.speedXZ = 3.0f;
        this->unk29A = Rand_ZeroFloat(1.99f);
        this->unkTimer250 = 0;
        this->unkTimer24E = this->unkTimer250;
        this->unkTimer24C = this->unkTimer250;
    } else {
        func_808917F8(this, globalCtx, 1);
    }
}

void EnNiw_SetupRunning(EnNiw* this) {
    SkelAnime_ChangeAnim(&this->skelanime, &D_060000E8, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060000E8.common), 0,
                         -10.0f);
    this->unk29A = Rand_ZeroFloat(1.99f);
    this->unknownState28E = 7;
    this->actionFunc = func_808924B0; // running away
    this->actor.speedXZ = 4.0f;
}

#ifdef NON_MATCHING
// bad regalloc, center of first if block
// actionfunc: running away from link
void func_808924B0(EnNiw* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f tempVec3f;
    s16 temp298;
    f32 dX;
    f32 dZ;

    // it actually wants to copy to stack... not modify, then pass to veccopy
    // and it does it BEFORE the if block, this is just unoptimized.
    tempVec3f = D_808934E8;
    if (this->unkTimer254 == 0) {
        // the assignements in this block never want to align properly
        // its not lineswap, as 800k permuter with only lineswap didn't find a solution
        this->unk298 = 0;

        this->unk2A4.x = this->actor.world.pos.x;
        this->unk2A4.y = this->actor.world.pos.y;
        this->unk2A4.z = this->actor.world.pos.z;
        this->unk2B0.x = this->actor.world.pos.x;
        this->unk2B0.y = this->actor.world.pos.y;
        this->unk2B0.z = this->actor.world.pos.z;

        this->unkTimer252 = this->unkTimer250 = this->unk298;
        this->unk264[8] = 0;
        this->unk264[6] = 0;
        this->unk264[5] = 0;
        this->unk264[7] = 0;
        this->unk304 = 0;
        this->unk300 = 0;
        this->actor.speedXZ = 0;
        Math_Vec3f_Copy(&this->unk2BC, &tempVec3f);
        EnNiw_SetupIdle(&this->actor);
    } else {
        if (this->unk2BC.x != 90000.0f) {
            dX = this->actor.world.pos.x - this->unk2BC.x;
            dZ = this->actor.world.pos.z - this->unk2BC.z;
        } else {
            dX = this->actor.world.pos.x - player->actor.world.pos.x;
            dZ = this->actor.world.pos.z - player->actor.world.pos.z;
        }
        this->yawTowardsPlayer = Math_Atan2S(dX, dZ);
        func_808917F8(this, globalCtx, 0);
        func_80891320(this, globalCtx, 2);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Niw_0x80891060/func_808924B0.asm")
#endif

// check if on the ground after running, once on the ground, start idling
void EnNiw_LandBeforeIdle(EnNiw* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        EnNiw_SetupIdle(this);
    }
}

void EnNiw_CheckRage(EnNiw* this, GlobalContext* globalCtx) {
    if ((!this->isStormActive) && (this->unkTimer260 == 0) && (this->niwType == ENNIW_TYPE_REGULAR)) {
        if ((this->unknownState28E != 7) && (this->unk2BC.x != 90000.0f)) {
            this->unkTimer260 = 10;
            this->sfxTimer1 = 30;
            this->unk29E = 1;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
            this->unkTimer254 = 100;
            this->unk2EC = 0;
            EnNiw_SetupRunning(this);
        }

        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            // health gets used as a hit counter until cucco storm
            if (this->actor.colChkInfo.health > 0) {
                this->actor.colChkInfo.health--;
            }

            if ((!D_80893460) && (this->actor.colChkInfo.health == 0)) {
                // now you've done it
                this->unkTimer254 = 100;
                D_80893460 = true;
                this->unk298 = 0;
                this->sfxTimer1 = 10000;
                this->unk2A4.x = this->unk2B0.x = this->actor.world.pos.x;
                this->unk2A4.y = this->unk2B0.y = this->actor.world.pos.y;
                this->unk2A4.z = this->unk2B0.z = this->actor.world.pos.z;
                this->unkTimer252 = this->unkTimer250 = this->unk298;

                this->unk264[8] = 0.0f;
                this->unk264[6] = 0.0f;
                this->unk264[5] = 0.0f;
                this->unk264[7] = 0.0f;
                this->isStormActive = true;
                this->actionFunc = EnNiw_Trigger;
                this->unk304 = 0.0f;
                this->unk300 = 0.0f;
                this->actor.speedXZ = 0.0f;
            } else {
                this->unkTimer260 = 10;
                this->sfxTimer1 = 30;
                this->unk29E = 1;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
                this->unkTimer254 = 100;
                this->unk2EC = 0;
                EnNiw_SetupRunning(this);
            }
        }
    }
}

void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = (EnNiw*)thisx;
    s8 pad0;
    s16 i;
    Player* player = PLAYER;
    s16 pad1;
    s16 featherCount;
    Vec3f pos;
    Vec3f spB8;
    Vec3f spAC;
    s32 pad2[9];
    s16 temp29C;
    f32 featherScale;
    f32 camResult;
    f32 floorHeight;
    f32 dist = 20.0f;
    s32 pad3;

    this->unusedCounter28C++;

    if (this->niwType == ENNIW_TYPE_UNK1) {
        this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.parent->shape.rot.y;
    }

    if (this->unknownState28E != 0) {
        this->unk264[9] = 0.0f;
    }

    if (this->unk29E != 0) {
        featherCount = ENNIW_FEATHERCOUNT;
        if (this->unk29E == 2) {
            featherCount = 4;
        }
        for (i = 0; i < featherCount; i++) {
            pos.x = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.x;
            pos.y = randPlusMinusPoint5Scaled(10.0f) + (this->actor.world.pos.y + this->unk308);
            pos.z = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.z;
            featherScale = Rand_ZeroFloat(6.0f) + 6.0f;

            if ((this->unk29E == 2) && (this->unk308 != 0)) {
                pos.y += 10.0f;
            }

            if (this->unk308 == 0) {
                featherScale = Rand_ZeroFloat(2.0f) + 2.0f;
            }
            spB8.x = randPlusMinusPoint5Scaled(3.0f);
            spB8.y = (Rand_ZeroFloat(2.0f) * 0.5f) + 2.0f;
            spB8.z = randPlusMinusPoint5Scaled(3.0f);
            spAC.z = spAC.x = 0.0f;
            spAC.y = -0.15000000596f;

            EnNiw_SpawnFeather(this, &pos, &spB8, &spAC, featherScale);
        }
        this->unk29E = 0;
    }

    EnNiw_UpdateFeather(this, globalCtx);

    DECR(this->unkTimer24C);
    DECR(this->unkTimer24E);
    DECR(this->unkTimer250);
    DECR(this->unkTimer252);
    DECR(this->unkTimer254);
    DECR(this->sfxTimer1);
    DECR(this->flutterSfxTimer);
    DECR(this->unusedTimer25A);
    DECR(this->yawTimer);
    DECR(this->unusedTimer25E);
    DECR(this->unkTimer260);

    this->actor.shape.rot = this->actor.world.rot;
    this->actor.shape.shadowScale = 15.0f;
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, this->unk308);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1F);

    if ((this->actor.floorHeight <= BGCHECK_Y_MIN) || (this->actor.floorHeight >= 32000.0f)) {
        // if cucco is off the map?
        Vec3f camera;
        camera.x = globalCtx->view.focalPoint.x - globalCtx->view.eye.x;
        camera.y = globalCtx->view.focalPoint.y - globalCtx->view.eye.y;
        camera.z = globalCtx->view.focalPoint.z - globalCtx->view.eye.z;
        camResult = camera.y / sqrtf(SQXYZ(camera));

        this->actor.world.pos.x = this->actor.home.pos.x;
        this->actor.world.pos.z = this->actor.home.pos.z;
        this->actor.world.pos.y = (this->actor.home.pos.y + globalCtx->view.eye.y) + (camResult * 160.0f);

        if (this->actor.world.pos.y < this->actor.home.pos.y) {
            this->actor.world.pos.y = this->actor.home.pos.y + 300.0f;
        }

        this->actor.speedXZ = 0.0f;
        this->actor.gravity = -2.0f;
        Math_Vec3f_Copy(&this->unk2A4, &this->actor.home.pos);
        Math_Vec3f_Copy(&this->unk2B0, &this->actor.home.pos);

        this->unk304 = 0.0f;
        this->unk300 = 0.0f;
        this->unusedFloat2FC = 0.0f;
        this->unusedFloat2F8 = 0.0f;
        this->unusedFloat2F4 = 0.0f;
        this->limbBRotx = 0.0f;
        this->limbBRoty = 0.0f;
        this->limbBRotz = 0.0f;
        this->limb7Rotx = 0.0f;
        this->limb7Roty = 0.0f;
        this->limb7Rotz = 0.0f;
        this->limbDRot = 0.0f;
        this->limbFRot = 0.0f;

        // clang-format off
        this->isStormActive = this->unusedCounter28C = this->unk292 = this->unk29E = this->unk298 = this->unk29A = this->unk29C = 0;
        // clang-format on

        for (i = 0; i < 10; i++) {
            this->unk264[i] = 0.0f;
        }

        this->unknownState28E = 8;
        this->isStormActive = false;
        this->actionFunc = EnNiw_LandBeforeIdle;
        return; // still required even with the else/else

    } else if ((this->actor.bgCheckFlags & 0x20) && (this->actor.yDistToWater > 15.0f) &&
               (this->unknownState28E != 6)) {
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        pos.y += this->actor.yDistToWater;
        this->unkTimer250 = 30;
        EffectSsGSplash_Spawn(globalCtx, &pos, 0, 0, 0, 400);
        this->unkTimer252 = 0;
        this->unknownState28E = 6;
        this->actionFunc = EnNiw_Swimming;

    } else {
        if (this->isStormActive && (this->actor.xyzDistToPlayerSq < (SQ(dist))) && (player->invincibilityTimer == 0)) {
            func_800B8D50(globalCtx, &this->actor, 2.0f, this->actor.world.rot.y, 0.0f, 0x10);
        }

        EnNiw_CheckRage(this, globalCtx);
        if ((this->flutterSfxTimer == 0) && (this->unknownState28E == 4)) {
            this->flutterSfxTimer = 7;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_CHICKEN_FLUTTER);
        }

        if (this->sfxTimer1 == 0) {
            if (this->unknownState28E != 0) {
                this->sfxTimer1 = 30;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_A); // attack cluck
            } else {
                this->sfxTimer1 = 300;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_N); // cluck
            }
        }

        if (!this->isStormActive) {
            if (this->niwType == ENNIW_TYPE_REGULAR) {
                Collider_UpdateCylinder(&this->actor, &this->collider);
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

                if (globalCtx) {}

                if ((this->unknownState28E != 4) && (this->unknownState28E != 5)) {
                    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
                }
            }
        }
    }
}

s32 EnNiw_LimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    EnNiw* this = (EnNiw*)actor;

    if (limbIndex == 13) {
        rot->y += (s16)this->limbDRot;
    }
    if (limbIndex == 15) {
        rot->y += (s16)this->limbFRot;
    }
    if (limbIndex == 11) {
        rot->x += (s16)this->limbBRotx;
        rot->y += (s16)this->limbBRoty;
        rot->z += (s16)this->limbBRotz;
    }
    if (limbIndex == 7) {
        rot->x += (s16)this->limb7Rotx;
        rot->y += (s16)this->limb7Roty;
        rot->z += (s16)this->limb7Rotz;
    }
    return 0;
}

void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = (EnNiw*)thisx;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelanime.skeleton, this->skelanime.limbDrawTbl, this->skelanime.dListCount,
                     EnNiw_LimbDraw, NULL, &this->actor);
    func_808932B0(this, globalCtx);
}

void EnNiw_SpawnFeather(EnNiw* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale) {
    s16 i;
    EnNiwFeather* feather = this->feathers;

    for (i = 0; i < ARRAY_COUNT(this->feathers); i++, feather++) {
        if (feather->isEnabled == false) {
            feather->isEnabled = true;
            feather->pos = *pos;
            feather->vel = *vel;
            feather->accel = *accel;
            feather->timer = 0;
            feather->scale = scale / 1000.0f;
            feather->life = Rand_ZeroFloat(20.0f) + 40.0f;
            feather->zRotStart = Rand_ZeroFloat(1000.0f);
            break;
        }
    }
}

void EnNiw_UpdateFeather(EnNiw* this, GlobalContext* globalCtx) {
    EnNiwFeather* feather = this->feathers;
    f32 featherVelocityGoal = 0.05f;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->feathers); i++, feather++) {
        if (feather->isEnabled) {
            feather->timer++;
            feather->pos.x += feather->vel.x;
            feather->pos.y += feather->vel.y;
            feather->pos.z += feather->vel.z;
            feather->vel.x += feather->accel.x;
            feather->vel.y += feather->accel.y;
            feather->vel.z += feather->accel.z;
            if (feather->isEnabled == true) {
                feather->zRotStart++;
                Math_ApproachF(&feather->vel.x, 0.0f, 1.0f, featherVelocityGoal);
                Math_ApproachF(&feather->vel.z, 0.0f, 1.0f, featherVelocityGoal);
                if (feather->vel.y < -0.5f) {
                    feather->vel.y = -0.5f;
                }

                feather->zRot = Math_SinS(feather->zRotStart * 0xBB8) * M_PI * 0.2f;

                if (feather->life < feather->timer) {
                    feather->isEnabled = false;
                }
            }
        }
    }
}

#ifdef NON_EQUIVALENT
// non-equiv: not even close
// feather draw function
void func_808932B0(EnNiw* this, GlobalContext* globalCtx) {
    // vanilla wants to load this early (and other values)
    //  but it needs to be stored in a s register not v/a
    // EnNiwFeather* feathers = &this->feathers;
    u8 flag = 0;

    // permuter thinks this might be int which makes sense...
    // but the end of the loop converts type, int reemoves it
    // s16 i;
    s32 i;

    if (globalCtx->state.gfxCtx) {}
    if (this->feathers) {}

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(this->feathers); i++) {
        if (this->feathers[i].isEnabled == true) {
            if (flag == 0) {
                gSPDisplayList(POLY_XLU_DISP++, D_060023B0);

                flag++;
            }

            SysMatrix_InsertTranslation(this->feathers[i].pos.x, this->feathers[i].pos.y, this->feathers[i].pos.z,
                                        MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(this->feathers[i].scale, this->feathers[i].scale, 1.0f, MTXMODE_APPLY);
            SysMatrix_InsertZRotation_f(this->feathers[i].zRot, MTXMODE_APPLY);
            SysMatrix_InsertTranslation(0.0f, -1000.0f, 0.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPDisplayList(POLY_XLU_DISP++, D_06002428);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Niw_0x80891060/func_808932B0.asm")
#endif
