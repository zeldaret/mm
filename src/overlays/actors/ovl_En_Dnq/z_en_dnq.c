/*
 * File: z_en_dnq.c
 * Overlay: ovl_En_Dnq
 * Description: Deku King
 */

#include "z_en_dnq.h"
#include "objects/object_dnq/object_dnq.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDnq*)thisx)

void EnDnq_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A52FB8(EnDnq* this, GlobalContext* globalCtx);

static s32 D_80A53400[] = {
    0x00120100, 0x150E0899, 0x0C120F08, 0x9A0C0F08, 0x9B0C0F08, 0x9C0C1112, 0x01100E08, 0x980C1000, 0x00120200,
    0x0C0E089D, 0x0C0F089E, 0x0C111202, 0x100E089F, 0x0C100000, 0x0E08A10C, 0x0F08A20C, 0x10000000,
};

const ActorInit En_Dnq_InitVars = {
    ACTOR_EN_DNQ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNQ,
    sizeof(EnDnq),
    (ActorFunc)EnDnq_Init,
    (ActorFunc)EnDnq_Destroy,
    (ActorFunc)EnDnq_Update,
    (ActorFunc)EnDnq_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 34, 80, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS D_80A5349C[] = {
    { &object_dnq_Anim_008328, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnq_Anim_008328, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_007528, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_0006F0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnq_Anim_000BF8, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_002690, 0.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnq_Anim_002690, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_003408, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_006984, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_005E18, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_005A14, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_005284, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_001AEC, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnq_Anim_001100, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnq_Anim_004EA0, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_00F504, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_0047B8, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_003DBC, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dnq_Anim_005A14, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnq_Anim_003DBC, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

void func_80A52530(GlobalContext* globalCtx, EnDnq* this) {
    func_8013A530(globalCtx, &this->actor, 10, &this->actor.focus.pos, &this->actor.world.rot, 120.0f, 480.0f, 0x38E3);
}

s32 func_80A5257C(EnDnq* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    if ((arg1 == 0) || (arg1 == 1)) {
        switch (this->unk_398) {
            case 0:
            case 1:
                break;

            default:
                phi_v1 = true;
                break;
        }
    } else if (arg1 != this->unk_398) {
        phi_v1 = true;
    }

    if (phi_v1) {
        this->unk_398 = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80A5349C, arg1);
    }

    return ret;
}

void func_80A52604(EnDnq* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80A52648(EnDnq* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (globalCtx->csCtx.state != 0) {
        if (!(this->unk_37C & 0x20)) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_1DC = 0xFF;
            this->unk_37C |= 0x20;
        }
        SubS_UpdateFlags(&this->unk_37C, 0, 7);
        ret = true;
    } else {
        if (this->unk_37C & 0x20) {
            this->actor.flags |= ACTOR_FLAG_1;
            this->unk_1DC = 0xFF;
            this->unk_37C &= ~0x20;
            SubS_UpdateFlags(&this->unk_37C, 3, 7);
        }
    }

    return ret;
}

s32 func_80A526F8(EnDnq* this) {
    if (this->unk_386 == 0) {
        func_80A5257C(this, 8);
        this->unk_38C = ((s32)(Rand_ZeroOne() * 100.0f) % 4) + 3;
        this->unk_388 = 0;
        this->unk_386 = 1;
    } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->unk_398) {
            case 8:
                if (DECR(this->unk_38C) == 0) {
                    func_80A5257C(this, 9);
                }
                break;

            case 9:
                func_80A5257C(this, 10);
                this->unk_38C = ((s32)(Rand_ZeroOne() * 100.0f) % 3) + 2;
                break;

            case 10:
                if (DECR(this->unk_38C) == 0) {
                    this->unk_388++;
                    if ((this->unk_38C != 0) || (this->unk_388 < 2)) {
                        func_80A5257C(this, 11);
                    } else {
                        func_80A5257C(this, 17);
                        this->unk_38C = 4;
                    }
                }
                break;

            case 11:
                func_80A5257C(this, 8);
                this->unk_38C = ((s32)(Rand_ZeroOne() * 100.0f) % 4) + 3;
                break;

            case 17:
                if (DECR(this->unk_38C) == 0) {
                    this->unk_386 = 0;
                }
                break;
        }

        if (this->unk_386 != 0) {
            this->skelAnime.curFrame = 0.0f;
        }
    }

    this->unk_38A = 0;
    return 0;
}

s32 func_80A52944(EnDnq* this) {
    s16 phi_v1 = 0;

    if (this->unk_386 == 0) {
        func_80A5257C(this, 12);
        this->unk_38C = 1;
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_386 = 1;
        phi_v1 = this->unk_38C * 0x2000;
        this->actor.shape.rot.y += phi_v1;
    } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_386++;
        if (this->unk_386 >= 6) {
            func_80A5257C(this, 12);
            this->unk_386 = 1;
            phi_v1 = this->unk_38C * 0x2000;
        } else if (this->unk_386 <= 3) {
            this->unk_38C = -this->unk_38C;
            this->skelAnime.curFrame = 0.0f;
            phi_v1 = this->unk_38C * 0x2000;
        } else {
            func_80A5257C(this, 13);
            this->skelAnime.curFrame = 0.0f;
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actor.shape.rot.y += phi_v1;
    }

    this->unk_38A = 0;
    return 0;
}

s32 func_80A52A78(EnDnq* this, GlobalContext* globalCtx) {
    static s32 D_80A535DC[] = {
        17, 12, 14, 13, 16,
    };

    if (this->unk_38A == 0) {
        this->unk_38C = 0;
        this->unk_38A = 1;
        this->unk_388 = globalCtx->state.frames % 5;
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->unk_38C != 0) {
        this->unk_38C--;
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->unk_38C == 0) {
            this->unk_38C = Rand_S16Offset(20, 20);
            this->unk_388 += 3;
            this->unk_388 %= 5;
        }
        func_80A5257C(this, D_80A535DC[this->unk_388]);
        this->skelAnime.curFrame = 0.0f;
    }

    this->unk_386 = 0;
    return 0;
}

s32 func_80A52B68(EnDnq* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 temp = globalCtx->msgCtx.currentTextId;

    if ((player->stateFlags1 & 0x40) && (player->targetActor == &this->actor)) {
        switch (temp) {
            case 0x89B:
                func_80A5257C(this, 18);
                break;

            case 0x89E:
                func_80A5257C(this, 19);
                break;

            case 0x898:
            case 0x89F:
                func_80A5257C(this, 16);
                break;

            case 0x899:
            case 0x89D:
                func_80A5257C(this, 14);
                break;

            case 0x89A:
            case 0x89C:
                func_80A5257C(this, 15);
                break;
        }
        this->unk_39C = 1;
    } else if (this->unk_39C != 0) {
        func_80A5257C(this, 0);
        this->unk_39C = 0;
        this->unk_37E = 0;
        this->unk_386 = 0;
    }

    return 0;
}

void func_80A52C6C(EnDnq* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    Vec3f sp34 = { 0.0f, 0.0f, 110.0f };
    Vec3f sp28;
    Vec3f sp1C;

    Math_Vec3f_Copy(&sp1C, &player->actor.world.pos);
    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.world.rot.y, &sp34, &sp28);
    Math_Vec3f_Copy(&this->unk_370, &sp28);
    this->actor.xzDistToPlayer = Math_Vec3f_DistXZ(&sp28, &sp1C);
}

s32* func_80A52CF8(EnDnq* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.weekEventReg[23] & 0x20) {
        return &D_80A53400[14];
    }

    if (this->unk_3A4 != 0) {
        return &D_80A53400[8];
    }

    return &D_80A53400[0];
}

s32 func_80A52D44(EnDnq* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk_37C & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        SubS_UpdateFlags(&this->unk_37C, 0, 7);
        this->unk_380 = func_80A52CF8(this, globalCtx);
        this->actionFunc = func_80A52FB8;
        ret = true;
    }

    return ret;
}

void func_80A52DC8(EnDnq* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yaw = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    if (yaw <= 0x3800) {
        SubS_UpdateFlags(&this->unk_37C, 3, 7);
    } else {
        SubS_UpdateFlags(&this->unk_37C, 0, 7);
    }

    if (!(gSaveContext.save.weekEventReg[23] & 0x20)) {
        this->unk_390 = 70.0f;
        if (Interface_HasItemInBottle(ITEM_DEKU_PRINCESS) && !Play_InCsMode(globalCtx) &&
            (Message_GetState(&globalCtx->msgCtx) == 0) && (ActorCutscene_GetCurrentIndex() == -1)) {
            if ((DECR(this->unk_384) == 0) && (gSaveContext.save.weekEventReg[29] & 0x40)) {
                Message_StartTextbox(globalCtx, 0x969, NULL);
                this->unk_384 = 200;
            }
        }

        this->unk_394 = this->actor.xzDistToPlayer;
        func_80A52C6C(this, globalCtx);
        if (this->actor.xzDistToPlayer < this->unk_390) {
            player->unk_B2B = 0x1A;
        }

        this->actor.xzDistToPlayer = this->unk_394;

        if (gSaveContext.save.weekEventReg[83] & 8) {
            func_80A52A78(this, globalCtx);
        } else if (this->unk_3A4 == 0) {
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
            func_80A526F8(this);
        } else {
            func_80A52944(this);
        }
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
        this->unk_390 = 70.0f;
    }
}

void func_80A52FB8(EnDnq* this, GlobalContext* globalCtx) {
    s16 sp2E = this->actor.yawTowardsPlayer;

    if (func_8010BF58(&this->actor, globalCtx, this->unk_380, NULL, &this->unk_1E0)) {
        SubS_UpdateFlags(&this->unk_37C, 3, 7);
        this->unk_386 = 0;
        this->actionFunc = func_80A52DC8;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, sp2E, 3, 0x2AA8);
    }
}

void func_80A53038(EnDnq* this, GlobalContext* globalCtx) {
    static s32 D_80A535FC[] = {
        0, 1, 2, 3, 5, 6,
    };
    s32 temp_v0;
    u32 temp_v1;

    if (Cutscene_CheckActorAction(globalCtx, 105)) {
        temp_v0 = Cutscene_GetActorActionIndex(globalCtx, 105);
        temp_v1 = globalCtx->csCtx.actorActions[temp_v0]->action;
        if (this->unk_1DC != (u8)temp_v1) {
            func_80A5257C(this, D_80A535FC[temp_v1]);
            this->unk_1DC = temp_v1;
        }

        if ((this->unk_398 == 4) && Animation_OnFrame(&this->skelAnime, 2.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KINGNUTS_DAMAGE);
        }

        if (((this->unk_398 == 3) || (this->unk_398 == 6)) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            func_80A5257C(this, this->unk_398 + 1);
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, temp_v0);
    }
}

void EnDnq_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDnq* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dnq_Skel_00EB48, NULL, this->jointTable, this->morphTable,
                       33);
    this->unk_398 = -1;
    func_80A5257C(this, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.02f);
    this->actor.targetMode = 1;
    this->unk_386 = 0;
    this->unk_37C = 0;
    SubS_UpdateFlags(&this->unk_37C, 3, 7);
    if (gSaveContext.save.weekEventReg[9] & 0x80) {
        this->unk_3A4 = 1;
    } else {
        this->unk_3A4 = 0;
    }
    this->unk_144 = func_80A52530;
    this->actionFunc = func_80A52DC8;
}

void EnDnq_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDnq* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDnq_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDnq* this = THIS;

    if (!func_80A52D44(this, globalCtx) && func_80A52648(this, globalCtx)) {
        func_80A53038(this, globalCtx);
        SkelAnime_Update(&this->skelAnime);
    } else {
        this->actionFunc(this, globalCtx);
        func_80A52B68(this, globalCtx);
        SkelAnime_Update(&this->skelAnime);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        this->unk_394 = this->actor.xzDistToPlayer;
        func_80A52C6C(this, globalCtx);
        func_8013C964(&this->actor, globalCtx, this->unk_390, fabsf(this->actor.playerHeightRel) + 1.0f, 0,
                      this->unk_37C & 7);
        this->actor.xzDistToPlayer = this->unk_394;
        Actor_SetFocus(&this->actor, 46.0f);
        func_80A52604(this, globalCtx);
    }
}

void EnDnq_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDnq* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);
}
