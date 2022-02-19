/*
 * File: z_en_fish.c
 * Overlay: ovl_En_Fish
 * Description: Fish
 */

#include "z_en_fish.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000000

#define THIS ((EnFish*)thisx)

void EnFish_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8091DF68(Actor* thisx, GlobalContext* globalCtx);
void func_8091E070(EnFish* this);
void func_8091E128(Actor* thisx, GlobalContext* globalCtx);
void func_8091E2E0(EnFish* this);
void func_8091E34C(Actor* thisx, GlobalContext* globalCtx2);
void func_8091E5EC(EnFish* this);
void func_8091E658(Actor* thisx, GlobalContext* globalCtx);
void func_8091E810(EnFish* this);
void func_8091E880(Actor* thisx, GlobalContext* globalCtx);
void func_8091E9A4(EnFish* this);
void func_8091EAF0(Actor* thisx, GlobalContext* globalCtx);
void func_8091ECF4(EnFish* this);
void func_8091ED70(Actor* thisx, GlobalContext* globalCtx);
void func_8091EF30(EnFish* this);
void func_8091EFE8(Actor* thisx, GlobalContext* globalCtx);
void func_8091F344(EnFish* this);
void func_8091F3BC(Actor* thisx, GlobalContext* globalCtx);
void func_8091F994(Actor* thisx, GlobalContext* globalCtx);

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static Color_RGB8 D_8091FA94[] = {
    { 255, 155, 55 },
    { 255, 47, 157 },
    { 215, 97, 7 },
};

const ActorInit En_Fish_InitVars = {
    ACTOR_EN_FISH,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFish),
    (ActorFunc)EnFish_Init,
    (ActorFunc)EnFish_Destroy,
    (ActorFunc)EnFish_Update,
    (ActorFunc)EnFish_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 720, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_STOP),
};

f32 func_8091D630(Vec3f* arg0, Vec3f* arg1) {
    return SQ(arg0->x - arg1->x) + SQ(arg0->z - arg1->z);
}

void func_8091D660(EnFish* this) {
    Animation_Change(&this->skelAnime, &gameplay_keep_Anim_02F0EC, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gameplay_keep_Anim_02F0EC), 1, 2.0f);
}

void func_8091D6C4(EnFish* this) {
    Animation_Change(&this->skelAnime, &gameplay_keep_Anim_02E65C, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gameplay_keep_Anim_02E65C), 1, 2.0f);
}

void func_8091D728(EnFish* this) {
    f32 phi_f0;

    this->actor.scale.x = this->unk_250 * this->unk_25C;
    this->actor.scale.y = this->unk_254 * this->unk_25C;
    this->actor.scale.z = this->unk_258 * this->unk_25C;

    if (this->actor.scale.z > 0.00001f) {
        phi_f0 = 1.0f / this->actor.scale.z;
    } else {
        phi_f0 = 0.0f;
    }
    this->unk_264 = 16.0f * phi_f0;
    this->unk_266 = 12.0f * phi_f0;
}

void func_8091D7C4(EnFish* this) {
    s32 pad;

    Math_ScaledStepToS(&this->actor.world.rot.x, this->unk_268, this->unk_26E);
    Math_ScaledStepToS(&this->actor.world.rot.y, this->unk_26A, this->unk_270);
    if (this->actor.world.rot.z != this->unk_26C) {
        Math_ScaledStepToS(&this->actor.world.rot.z, this->unk_26C, this->unk_272);
    }
    this->actor.shape.rot = this->actor.world.rot;
}

void func_8091D840(Actor* thisx, GlobalContext* globalCtx, s32 arg2, f32 arg3) {
    EnFish* this = THIS;
    s32 i;

    for (i = 0; i < arg2; i++) {
        EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 0.0f, arg3, arg3, (Rand_ZeroOne() * 0.09f) + 0.06f);
    }
}

void func_8091D904(EnFish* this) {
    this->unk_242 = 400;
    this->unk_25C = this->unk_260 * 0.1f;
    func_8091D728(this);
    this->actor.draw = NULL;
}

Actor* func_8091D944(EnFish* this, GlobalContext* globalCtx) {
    f32 distSq;
    Actor* retActor = NULL;
    f32 minDistSq = FLT_MAX;
    Actor* foundActor = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (foundActor != NULL) {
        if ((foundActor->id == ACTOR_EN_FISH) && (foundActor->params == ENFISH_2) &&
            (foundActor->room == this->actor.room)) {
            distSq = Math3D_Vec3fDistSq(&foundActor->world.pos, &this->actor.world.pos);
            if (retActor == NULL) {
                retActor = foundActor;
                minDistSq = distSq;
            } else if (distSq < minDistSq) {
                minDistSq = distSq;
            }
        }
        foundActor = foundActor->next;
    }

    return retActor;
}

s32 func_8091DA14(EnFish* this, GlobalContext* globalCtx) {
    return globalCtx->sceneNum == SCENE_LABO && func_8091D944(this, globalCtx);
}

void EnFish_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFish* this = THIS;
    s16 sp36 = this->actor.params;

    Collider_InitJntSph(globalCtx, &this->collider);
    if (sp36 == ENFISH_2) {
        this->actor.draw = NULL;
        this->actor.update = func_8091F994;
        return;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_250 = 1.0f;
    this->unk_254 = 1.0f;

    if (sp36 == ENFISH_MINUS1) {
        this->unk_258 = (Rand_ZeroOne() * 0.9f) + 0.6f;
        this->unk_25C = ((Rand_ZeroOne() * 1.2f) + 0.6f) * 0.01f;
    } else {
        this->unk_258 = 1.0f;
        this->unk_25C = 0.01f;
    }

    this->unk_260 = this->unk_25C;
    func_8091D728(this);

    if ((this->unk_258 * this->unk_25C * 100.0f) < 1.02f) {
        this->unk_278 = 2;
    } else if ((this->unk_258 * this->unk_25C * 100.0f) < 2.0f) {
        this->unk_278 = 1;
    } else {
        this->unk_278 = 0;
    }

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gameplay_keep_Skel_02F028, &gameplay_keep_Anim_02F0EC,
                       this->jointTable, this->morphTable, 7);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);

    this->actor.colChkInfo.mass = this->unk_25C * 30.0f;
    this->unk_244 = (u32)Rand_Next() >> 0x10;
    this->unk_246 = (u32)Rand_Next() >> 0x10;

    if (sp36 == ENFISH_0) {
        this->actor.flags |= ACTOR_FLAG_10;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 8.0f);
        func_8091E810(this);
    } else if (sp36 == ENFISH_1) {
        func_8091F344(this);
    } else {
        func_8091E070(this);
    }
}

void EnFish_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnFish* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_8091DD48(EnFish* this) {
    this->actor.shape.yOffset += (Math_SinS(this->unk_246) * 5.0f) + (Math_SinS(this->unk_244) * 10.0f);

    if (this->actor.shape.yOffset < -200.0f) {
        this->actor.shape.yOffset = -200.0f;
    } else if (this->actor.shape.yOffset > 200.0f) {
        this->actor.shape.yOffset = 200.0f;
    }
}

s32 func_8091DDF4(EnFish* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp1C;

    if (this->actor.xzDistToPlayer < 50.0f) {
        sp1C.x = (Math_SinS(BINANG_ROT180(this->actor.yawTowardsPlayer)) * 30.0f) + player->actor.world.pos.x;
        sp1C.y = player->actor.world.pos.y;
        sp1C.z = (Math_CosS(BINANG_ROT180(this->actor.yawTowardsPlayer)) * 30.0f) + player->actor.world.pos.z;

        if (func_8091D630(&sp1C, &this->actor.world.pos) <= SQ(30.0f)) {
            return true;
        }
    }
    return false;
}

void func_8091DEE4(EnFish* this) {
    static s16 D_8091FACC[] = { 85, 60, 45 };

    this->actor.gravity = 0.0f;
    this->actor.terminalVelocity = 0.0f;
    this->unk_240 = Rand_S16Offset(5, D_8091FACC[this->unk_278]);
    this->unk_248 = 0;
    this->unk_26E = 400;
    this->unk_272 = 400;
    this->unk_268 = 0;
    this->unk_26C = 0;
    func_8091D660(this);
    this->unk_24C = 0.0f;
    this->unkFunc = func_8091DF68;
}

void func_8091DF68(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;

    func_8091DD48(this);
    Math_SmoothStepToF(&thisx->speedXZ, 0.0f, 0.05f, 0.3f, 0.0f);

    if ((thisx->speedXZ * 1.4f) + 0.8f > 2.0f) {
        this->skelAnime.playSpeed = 2.0f;
    } else {
        this->skelAnime.playSpeed = (thisx->speedXZ * 1.4f) + 0.8f;
    }

    this->unk_270 >>= 1;

    if (this->unk_240 <= 0) {
        func_8091E070(this);
    } else if (thisx == thisx->child) {
        func_8091E5EC(this);
    } else if ((thisx->xzDistToPlayer < 60.0f) || (this->unk_276 > 0)) {
        func_8091E2E0(this);
    }
}

void func_8091E070(EnFish* this) {
    static s16 D_8091FAD4[] = { 20, 30, 40 };
    s16 phi_a1;

    this->actor.gravity = 0.0f;
    this->actor.terminalVelocity = 0.0f;

    if ((Rand_Next() & 3) == 0) {
        if (((Rand_Next() & 7) == 0) && (this->unk_278 != 0)) {
            phi_a1 = 80;
        } else {
            phi_a1 = 45;
        }
    } else {
        phi_a1 = D_8091FAD4[this->unk_278];
    }
    this->unk_240 = Rand_S16Offset(15, phi_a1);
    this->unk_248 = 0;
    this->unk_26E = 400;
    this->unk_272 = 400;
    this->unk_26C = 0;
    func_8091D660(this);
    this->unkFunc = func_8091E128;
}

void func_8091E128(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFish* this = THIS;

    func_8091DD48(this);
    Math_SmoothStepToF(&thisx->speedXZ, 1.8f, 0.08f, 0.4f, 0.0f);

    if ((func_8091D630(&thisx->world.pos, &thisx->home.pos) > SQ(80.0f)) || (this->unk_240 < 4)) {
        this->unk_270 = this->unk_264;
        this->unk_26A = Math_Vec3f_Yaw(&thisx->world.pos, &thisx->home.pos);
        this->unk_24C = 1.0f;
    } else if ((thisx->child != NULL) && (thisx != thisx->child)) {
        this->unk_270 = this->unk_264;
        this->unk_26A = Math_Vec3f_Yaw(&thisx->world.pos, &thisx->child->world.pos);
        this->unk_24C = 1.2f;
    } else {
        this->unk_270 >>= 2;
        this->unk_24C = 0.0f;
    }

    if ((thisx->speedXZ * 1.5f) + 0.8f > 4.0f) {
        this->skelAnime.playSpeed = 4.0f;
    } else {
        this->skelAnime.playSpeed = (thisx->speedXZ * 1.5f) + 0.8f;
    }

    if (this->unk_240 <= 0) {
        func_8091DEE4(this);
    } else if (thisx == thisx->child) {
        func_8091E5EC(this);
    } else if ((thisx->xzDistToPlayer < 60.0f) || (this->unk_276 > 0)) {
        func_8091E2E0(this);
    }
}

void func_8091E2E0(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.terminalVelocity = 0.0f;
    this->unk_240 = Rand_S16Offset(10, 40);
    this->unk_248 = 0;
    this->unk_26E = 400;
    this->unk_272 = 400;
    this->unk_268 = 0;
    this->unk_26C = 0;
    func_8091D660(this);
    this->unkFunc = func_8091E34C;
}

void func_8091E34C(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnFish* this = THIS;
    s32 sp3C = thisx->xzDistToPlayer < 60.0f;
    s32 sp38 = this->unk_276 > 0;
    s32 pad;

    func_8091DD48(this);
    Math_SmoothStepToF(&thisx->speedXZ, 4.2f, 0.08f, 1.4f, 0.0f);

    if (func_8091D630(&thisx->world.pos, &thisx->home.pos) > SQ(160.0f)) {
        this->unk_270 = this->unk_264;
        this->unk_26A = Math_Vec3f_Yaw(&thisx->world.pos, &thisx->home.pos);
        this->unk_24C = 0.8f;
    } else if ((thisx->child != NULL) && (thisx != thisx->child)) {
        this->unk_270 = this->unk_266;
        this->unk_26A = Math_Vec3f_Yaw(&thisx->world.pos, &thisx->child->world.pos);
        this->unk_24C = 1.0f;
    } else if (sp3C) {
        this->unk_26A = BINANG_ROT180(thisx->yawTowardsPlayer);
        if ((globalCtx->state.frames & 0x10) == 0) {
            if ((globalCtx->state.frames & 0x20) == 0) {
                this->unk_26A += 0x2000;
            }
        } else if ((globalCtx->state.frames & 0x20) == 0) {
            this->unk_26A -= 0x2000;
        }
        this->unk_270 = this->unk_266;
        this->unk_24C = 1.2f;
    } else if (sp38 != 0) {
        if ((globalCtx->state.frames & 0x10) == 0) {
            s16 temp = BINANG_SUB(thisx->shape.rot.y, this->unk_274);

            if (temp < 0) {
                this->unk_26A = BINANG_SUB(this->unk_274, 0x4000);
            } else {
                this->unk_26A = BINANG_ADD(this->unk_274, 0x4000);
            }
        } else {
            this->unk_26A = BINANG_ROT180(this->unk_274);
        }
        this->unk_24C = 1.2f;
        this->unk_270 = this->unk_266;
    } else {
        this->unk_270 >>= 2;
        this->unk_24C = 0.0f;
    }

    if ((thisx->speedXZ * 1.5f) + 0.8f > 4.0f) {
        this->skelAnime.playSpeed = 4.0f;
    } else {
        this->skelAnime.playSpeed = (thisx->speedXZ * 1.5f) + 0.8f;
    }

    if ((this->unk_240 <= 0) || (!sp3C && (sp38 == 0))) {
        func_8091DEE4(this);
    } else if (thisx == thisx->child) {
        func_8091E5EC(this);
    }
}

void func_8091E5EC(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.terminalVelocity = 0.0f;
    this->unk_26E = 400;
    this->unk_272 = 400;
    this->unk_268 = 0;
    this->unk_26C = 0;
    func_8091D660(this);
    this->unk_240 = Rand_S16Offset(10, 30);
    this->unk_248 = 0;
    this->unkFunc = func_8091E658;
}

void func_8091E658(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    Vec3f sp38;
    s32 pad2;
    s16 sp32;

    func_8091DD48(this);
    Math_SmoothStepToF(&thisx->speedXZ, 1.8f, 0.1f, 0.5f, 0.0f);

    if (func_8091D630(&thisx->world.pos, &thisx->home.pos) > SQ(80.0f)) {
        this->unk_270 = this->unk_264;
        this->unk_26A = Math_Vec3f_Yaw(&thisx->world.pos, &thisx->home.pos);
        this->unk_24C = 1.0f;
    } else {
        if ((globalCtx->state.frames & 0x40) == 0) {
            sp32 = BINANG_ADD(thisx->yawTowardsPlayer, 0x9000);
        } else {
            sp32 = BINANG_ADD(thisx->yawTowardsPlayer, 0x7000);
        }

        sp38.x = (Math_SinS(sp32) * 20.0f) + player->actor.world.pos.x;
        sp38.y = player->actor.world.pos.y;
        sp38.z = (Math_CosS(sp32) * 20.0f) + player->actor.world.pos.z;

        this->unk_270 = this->unk_264;
        this->unk_26A = Math_Vec3f_Yaw(&thisx->world.pos, &sp38);
        this->unk_24C = 1.2f;
    }

    if ((thisx->speedXZ * 1.5f) + 0.8f > 4.0f) {
        this->skelAnime.playSpeed = 4.0f;
    } else {
        this->skelAnime.playSpeed = (thisx->speedXZ * 1.5f) + 0.8f;
    }

    if (this->unk_240 <= 0) {
        func_8091DEE4(this);
    }
}

void func_8091E810(EnFish* this) {
    this->unk_270 = 0;
    this->unk_26A = 0;
    this->actor.gravity = -1.0f;
    this->actor.terminalVelocity = -10.0f;
    this->actor.shape.yOffset = 0.0f;
    func_8091D6C4(this);
    this->unk_248 = 5;
    this->unkFunc = func_8091E880;
    this->unk_24C = 0.0f;
    this->unk_240 = 300;
}

void func_8091E880(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;

    Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 0.1f, 0.1f, 0.0f);
    this->unk_26E = 0x43;
    this->unk_272 = 0x43;
    this->unk_268 = 0x4000;
    this->unk_26C = -0x4000;
    if (this->actor.bgCheckFlags & 1) {
        this->unk_240 = 400;
        func_8091E9A4(this);
    } else if (this->actor.bgCheckFlags & 0x20) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIVE_INTO_WATER_L);
        func_8091D840(thisx, globalCtx, 10, 15.0f);
        if (func_8091DA14(this, globalCtx)) {
            func_8091EF30(this);
        } else {
            func_8091ECF4(this);
        }
    } else if ((this->unk_240 <= 0) && (this->actor.params == ENFISH_0) &&
               (this->actor.floorHeight < BGCHECK_Y_MIN + 10)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_8091E9A4(EnFish* this) {
    s32 pad[2];
    s32 sp24;
    f32 temp_f0;

    this->actor.gravity = -1.0f;
    this->actor.terminalVelocity = -10.0f;

    temp_f0 = Rand_ZeroOne();
    if (temp_f0 < 0.1f) {
        this->actor.velocity.y = (Rand_ZeroOne() * 3.0f) + 2.5f;
        sp24 = true;
    } else if (temp_f0 < 0.2f) {
        this->actor.velocity.y = (Rand_ZeroOne() * 1.2f) + 0.2f;
        sp24 = true;
    } else {
        this->actor.velocity.y = 0.0f;
        if (Rand_ZeroOne() < 0.2f) {
            sp24 = true;
        } else {
            sp24 = false;
        }
    }

    this->actor.shape.yOffset = 300.0f;
    func_8091D6C4(this);
    this->unkFunc = func_8091EAF0;
    this->unk_248 = 5;
    this->unk_24C = 0.0f;
    if (sp24 && (this->actor.draw != NULL)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FISH_LEAP);
    }
}

void func_8091EAF0(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    s32 sp40 = globalCtx->state.frames;
    s16 phi_v1;

    Math_SmoothStepToF(&this->actor.speedXZ, Rand_ZeroOne() * 0.2f, 0.1f, 0.1f, 0.0f);
    phi_v1 = (s16)((((sp40 >> 5) & 2) | ((sp40 >> 2) & 1)) << 0xB) * 0.3f;
    if (sp40 & 4) {
        phi_v1 *= -1;
    }
    this->unk_268 = phi_v1;
    this->unk_26E = 0xA6B;
    this->unk_26C = 0x4000;
    this->unk_272 = 0x29B;
    this->unk_270 = ((Math_SinS(this->unk_244) * 1333.0f) + (Math_SinS(this->unk_246) * 667.0f)) * Rand_ZeroOne();

    if (this->unk_270 >= 0) {
        this->unk_26A = BINANG_ADD(this->actor.world.rot.y, 0x4000);
    } else {
        this->unk_26A = BINANG_SUB(this->actor.world.rot.y, 0x4000);
        this->unk_270 = -this->unk_270;
    }

    if (this->unk_240 <= 0) {
        Actor_MarkForDeath(&this->actor);
    } else if (this->unk_240 <= 60) {
        if (sp40 & 4) {
            this->actor.draw = EnFish_Draw;
        } else {
            this->actor.draw = NULL;
        }
    } else if (this->actor.bgCheckFlags & 0x20) {
        if (func_8091DA14(this, globalCtx)) {
            func_8091EF30(this);
        } else {
            func_8091ECF4(this);
        }
    } else if (this->actor.bgCheckFlags & 1) {
        func_8091E9A4(this);
    }
}

void func_8091ECF4(EnFish* this) {
    this->actor.home.pos = this->actor.world.pos;
    this->actor.gravity = 0.0f;
    this->actor.terminalVelocity = 0.0f;
    this->actor.shape.yOffset = 0.0f;
    this->actor.flags |= ACTOR_FLAG_10;
    this->unk_240 = 200;
    func_8091D660(this);
    this->unkFunc = func_8091ED70;
    this->unk_248 = 5;
    this->unk_24C = 0.0f;
}

void func_8091ED70(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    s32 pad;
    s16 sp2E;

    if (this->unk_240 >= 0xBF) {
        func_8091D840(thisx, globalCtx, 2, 25.0f);
    }

    Math_SmoothStepToF(&thisx->speedXZ, 2.8f, 0.1f, 0.4f, 0.0f);

    if ((thisx->bgCheckFlags & 8) || !(thisx->bgCheckFlags & 0x20)) {
        sp2E = Math_Vec3f_Yaw(&thisx->world.pos, &thisx->home.pos);
        thisx->home.rot.y = Rand_S16Offset(-100, 100) + sp2E;
        thisx->speedXZ *= 0.5f;
    }

    this->unk_268 = 0;
    this->unk_26A = thisx->home.rot.y;
    this->unk_26C = 0;
    this->unk_26E = 1000;
    this->unk_270 = 2000;
    this->unk_272 = 0x29B;

    if (thisx->bgCheckFlags & 1) {
        Math_StepToF(&thisx->world.pos.y, thisx->home.pos.y - 4.0f, 2.0f);
    } else {
        Math_StepToF(&thisx->world.pos.y, thisx->home.pos.y - 10.0f, 2.0f);
    }

    if (this->unk_240 < 100) {
        this->unk_25C *= 0.982f;
        func_8091D728(this);
    }

    if ((thisx->speedXZ * 1.5f) + 1.0f > 4.8f) {
        this->skelAnime.playSpeed = 4.8f;
    } else {
        this->skelAnime.playSpeed = (thisx->speedXZ * 1.5f) + 1.0f;
    }

    if (this->unk_240 <= 0) {
        Actor_MarkForDeath(thisx);
    }
}

void func_8091EF30(EnFish* this) {
    this->actor.gravity = -2.0f;
    this->actor.terminalVelocity = -10.0f;
    this->actor.shape.yOffset = 0.0f;
    if (this->actor.velocity.y < -1.0f) {
        this->actor.velocity.y = -1.0f;
    }
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.home.pos.x = this->actor.world.pos.x;
    this->actor.home.pos.y = this->actor.world.pos.y - 20.0f;
    this->actor.home.pos.z = this->actor.world.pos.z;
    func_8091D660(this);
    this->unk_240 = 15;
    this->unk_279 = 10;
    this->unkFunc = func_8091EFE8;
    this->unk_248 = 5;
    this->unk_24C = 0.0f;
}

void func_8091EFE8(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    s32 temp_v0_2;
    Actor* sp3C = func_8091D944(this, globalCtx);
    f32 temp_f0;
    f32 sp34;
    f32 sp30;
    s16 sp2E;

    if (sp3C == 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->unk_240 <= 0) {
        this->unk_240 = Rand_S16Offset(5, 35);
    }

    if (this->unk_277 == 0) {
        Math_SmoothStepToF(&this->actor.speedXZ, 2.8f, 0.1f, 0.4f, 0.0f);
        if (this->unk_240 < 6) {
            this->actor.speedXZ *= 0.75f;
        }
    }

    if ((this->actor.bgCheckFlags & 8) && !(this->actor.bgCheckFlags & 0x20)) {
        this->actor.speedXZ *= 0.5f;
    }

    if (!((u32)Rand_Next() >> 0x1B) || ((this->actor.bgCheckFlags & 8) && !((u32)Rand_Next() >> 0x1E)) ||
        !(this->actor.bgCheckFlags & 0x20)) {
        temp_f0 = Rand_ZeroOne();
        sp34 = (1.0f - SQ(temp_f0)) * sp3C->home.rot.x;
        sp30 = Rand_ZeroOne() * sp3C->home.rot.z;
        sp2E = (u32)Rand_Next() >> 0x10;
        this->actor.home.pos.x = (Math_SinS(sp2E) * sp34) + sp3C->world.pos.x;
        this->actor.home.pos.y = sp3C->world.pos.y + sp30;
        this->actor.home.pos.z = (Math_CosS(sp2E) * sp34) + sp3C->world.pos.z;
        this->actor.home.rot.y =
            Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos) + Rand_S16Offset(-100, 100);
    }

    this->unk_268 = Math_Vec3f_Pitch(&this->actor.world.pos, &this->actor.home.pos);
    this->unk_26C = 0;
    this->unk_26A = this->actor.home.rot.y;

    temp_v0_2 = BINANG_SUB(this->unk_268, this->actor.shape.rot.x);
    temp_v0_2 = ABS_ALT(temp_v0_2);

    temp_v0_2 = temp_v0_2 / 11;
    if (temp_v0_2 > 800) {
        temp_v0_2 = 800;
    } else if (temp_v0_2 < 100) {
        temp_v0_2 = 100;
    }

    if (this->unk_279 > 0) {
        this->unk_279--;
        this->unk_26E = 1000;
    } else {
        this->unk_26E = temp_v0_2;
    }

    if (this->unk_240 < 10) {
        this->unk_270 = 400;
    } else {
        this->unk_270 = 2000;
    }

    this->unk_272 = 0x29B;
    if (fabsf(this->actor.world.pos.y - this->actor.home.pos.y) < 2.0f) {
        this->actor.gravity = 0.0f;
    } else if (this->actor.home.pos.y < this->actor.world.pos.y) {
        this->actor.gravity = -0.15f;
    } else {
        this->actor.gravity = 0.15f;
    }

    this->actor.velocity.y *= 0.8f;
    if ((this->actor.speedXZ * 1.5f) + 1.0f > 4.8f) {
        this->skelAnime.playSpeed = 4.8f;
    } else {
        this->skelAnime.playSpeed = (this->actor.speedXZ * 1.5f) + 1.0f;
    }
}

void func_8091F344(EnFish* this) {
    this->actor.gravity = 0.0f;
    this->actor.terminalVelocity = 0.0f;
    this->unk_240 = Rand_S16Offset(5, 35);
    this->unk_248 = 1;
    this->unk_268 = 0;
    this->unk_26C = 0;
    this->unk_26E = 1500;
    this->unk_272 = 0;
    func_8091D660(this);
    this->unkFunc = func_8091F3BC;
    this->unk_24C = 0.0f;
}

void func_8091F3BC(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_8091FADC = { 0.0f, 0.04f, 0.09f };
    static Vec3f D_8091FAE8 = { 0.5f, 0.1f, 0.15f };
    EnFish* this = THIS;
    s32 sp40 = globalCtx->gameplayFrames;
    Vec3f* sp3C;
    f32 phi_f0;
    f32 temp_f2;

    if ((this->actor.xzDistToPlayer < 60.0f) || ((sp40 & 0x1FF) < 20)) {
        if (this->unk_240 < 12) {
            sp3C = &D_8091FAE8;
        } else {
            sp3C = &D_8091FADC;
        }
    } else if (this->unk_240 < 4) {
        sp3C = &D_8091FAE8;
    } else {
        sp3C = &D_8091FADC;
    }

    func_8091DD48(this);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 2.0f);
    Math_SmoothStepToF(&this->actor.speedXZ, sp3C->x, sp3C->y, sp3C->z, 0.0f);
    this->unk_24C = 0.0f;

    if (func_8091D630(&this->actor.world.pos, &this->actor.home.pos) > SQ(15.0f)) {
        this->unk_26A = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos);
        this->unk_270 = 0x85;
        phi_f0 = 0.4f;
    } else if (this->unk_240 < 4) {
        this->unk_26A = sp40 << 7;
        this->unk_270 = 0x43;
        phi_f0 = 0.4f;
    } else {
        this->unk_270 = 0;
        phi_f0 = 0.0f;
    }

    temp_f2 = this->actor.speedXZ + 0.4f + phi_f0;
    this->skelAnime.playSpeed = CLAMP(temp_f2, 0.5f, 1.6f);

    if (this->unk_240 <= 0) {
        this->unk_240 = Rand_S16Offset(5, 80);
    }
}

void func_8091F5A4(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    Actor* temp_v0_2;
    s16 temp_v0;
    s16 temp_v0_4;
    s32 temp_v1;
    s32 phi_v1;
    f32 phi_f0;

    if (this->unk_240 > 0) {
        this->unk_240--;
    }

    this->unk_244 += 0x111;
    this->unk_246 += 0x500;

    if ((this->actor.child != NULL) && (this->actor.child->update == NULL) && (thisx != this->actor.child)) {
        this->actor.child = NULL;
    }

    if ((this->unkFunc == NULL) || (this->unkFunc(&this->actor, globalCtx), (this->actor.update != NULL))) {
        if ((ABS_ALT(BINANG_SUB(this->unk_26A, this->actor.shape.rot.y)) > 0x3000) && (this->unk_270 > 1000)) {
            this->skelAnime.playSpeed += this->unk_24C;
        }
        SkelAnime_Update(&this->skelAnime);
        func_8091D7C4(this);
        Actor_MoveWithGravity(&this->actor);
        if (this->unk_248 != 0) {
            u32 temp = (globalCtx->sceneNum ^ SCENE_LABO) != 0;
            phi_f0 = BREG(1) + 10.0f;

            if (temp) {
                phi_f0 = 6.0f;
            }
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 17.5f, phi_f0, 0.0f, this->unk_248);
        }

        if ((this->actor.xzDistToPlayer < 70.0f) && (this->unkFunc != func_8091EFE8)) {
            ColliderJntSphElement* element = &this->collider.elements[0];

            element->dim.worldSphere.center.x = this->actor.world.pos.x;
            element->dim.worldSphere.center.y = this->actor.world.pos.y;
            element->dim.worldSphere.center.z = this->actor.world.pos.z;
            element->dim.worldSphere.radius = this->unk_25C * 500.0f;
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        Actor_SetFocus(&this->actor, this->actor.shape.yOffset * 0.01f);

        if (Actor_HasParent(&this->actor, globalCtx)) {
            this->actor.parent = NULL;
            if (this->actor.params == ENFISH_0) {
                Actor_MarkForDeath(&this->actor);
            } else {
                func_8091D904(this);
            }
        } else if (func_8091DDF4(this, globalCtx)) {
            Actor_PickUp(&this->actor, globalCtx, GI_MAX, 80.0f, 25.0f);
        }
    }
}

void func_8091F830(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;

    if (this->actor.params == ENFISH_1) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if ((this->actor.child != NULL) && (this->actor.child->update == NULL) && (thisx != this->actor.child)) {
        this->actor.child = NULL;
    }

    if ((this->unkFunc == NULL) || (this->unkFunc(&this->actor, globalCtx), (this->actor.update != NULL))) {
        func_8091D7C4(this);
        Actor_MoveWithGravity(&this->actor);

        if (this->unk_242 == 20) {
            this->actor.draw = EnFish_Draw;
        } else if (this->unk_242 == 0) {
            this->unk_25C = this->unk_260;
            func_8091D728(this);
        } else if (this->unk_242 < 20) {
            this->unk_25C += 0.1f * this->unk_260;
            if (this->unk_260 < this->unk_25C) {
                this->unk_25C = this->unk_260;
            }
            func_8091D728(this);
        }
    }
}

void EnFish_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;

    if (this->unk_242 > 0) {
        this->unk_242--;
        func_8091F830(thisx, globalCtx);
    } else {
        func_8091F5A4(thisx, globalCtx);
    }

    if (this->unk_276 > 0) {
        this->unk_276--;
    }
}

void func_8091F994(Actor* thisx, GlobalContext* globalCtx) {
}

void EnFish_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFish* this = THIS;
    Color_RGB8* colour = &D_8091FA94[this->unk_278];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, colour->r, colour->g, colour->b, 255);

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, NULL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
