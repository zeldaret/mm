/*
 * File: z_en_racedog.c
 * Overlay: ovl_En_Racedog
 * Description: The dogs that run around the racetrack during the dog race.
 *
 * Note that the dogs milling about the Doggy Racetrack prior to and after the
 * race are actually En_Dg. This actor is solely concerned with the dogs that
 * actually perform the race by running around the track.
 */

#include "z_en_racedog.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnRacedog*)thisx)

void EnRacedog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B24C14(EnRacedog* this, GlobalContext* globalCtx);
void func_80B24CB4(EnRacedog* this, GlobalContext* globalCtx);
void func_80B24E14(EnRacedog* this);
void func_80B24F08(EnRacedog* this);
void func_80B251EC(EnRacedog* this);
void func_80B252F8(EnRacedog* this);
void func_80B2538C(EnRacedog* this);
void func_80B25448(EnRacedog* this);
s32 func_80B25490(EnRacedog* this, Vec2f* arg1);
void func_80B255AC(EnRacedog* this, GlobalContext* globalCtx);
void func_80B256BC(EnRacedog* this);

typedef struct {
    f32 unk_00;
    f32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} UnkRacedogStruct;

const ActorInit En_Racedog_InitVars = {
    ACTOR_EN_RACEDOG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnRacedog),
    (ActorFunc)EnRacedog_Init,
    (ActorFunc)EnRacedog_Destroy,
    (ActorFunc)EnRacedog_Update,
    (ActorFunc)EnRacedog_Draw,
};

static s16 D_80B25D40 = 0;

static s16 D_80B25D44 = -1;

static s16 D_80B25D48 = 0;

static s16 D_80B25D4C = -1;

static f32 D_80B25D50[][2] = {
    { 0.0f, 0.0f }, { 5.0f, 5.5f }, { 5.0f, 5.0f }, { 5.5f, 5.0f }, { 4.5f, 5.5f }, { 6.0f, 4.0f }, { 4.0f, 6.0f },
};

static UnkRacedogStruct D_80B25D88[] = {
    { -1.0f, 1.20000004768f, 3, 0, 9, 0x3539 },  { -1.0f, 1.20000004768f, 1, 1, 9, 0x353A },
    { -1.0f, 1.20000004768f, 5, 2, 10, 0x353B }, { -1.0f, 1.20000004768f, 2, 3, 9, 0x353C },
    { -1.0f, 1.20000004768f, 4, 4, 8, 0x353D },  { -1.0f, 1.20000004768f, 2, 5, 9, 0x353E },
    { -1.0f, 1.20000004768f, 3, 6, 9, 0x353F },  { -1.0f, 1.20000004768f, 1, 7, 9, 0x3540 },
    { -1.0f, 1.20000004768f, 1, 8, 9, 0x3541 },  { -1.0f, 1.20000004768f, 6, 9, 8, 0x3542 },
    { -1.0f, 1.20000004768f, 2, 10, 9, 0x3543 }, { -1.0f, 1.20000004768f, 3, 11, 9, 0x3544 },
    { -1.0f, 1.20000004768f, 1, 12, 9, 0x3545 }, { -1.0f, 1.20000004768f, 4, 13, 8, 0x3546 },
};

static UnkRacedogStruct D_80B25E68 = { -1.0f, 1.0, 0, -1, 0, 0x353E };

static Vec2f D_80B25E78[] = {
    { -3914.0f, 1283.0f },
    { -3747.0f, 1104.0f },
    { -3717.0f, 1169.0f },
    { -3897.0f, 1308.0f },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
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
    { 13, 19, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, 1 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static AnimationInfoS D_80B25EF0[] = {
    { &gDogWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },        { &gDogWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },
    { &gDogRunAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },         { &gDogBarkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },
    { &gDogSitAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -6 },        { &gDogSitAnim, 1.0f, 0, -1, ANIMMODE_LOOP_PARTIAL, -6 },
    { &gDogLyingDownAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -6 },  { &gDogLyingDownLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },
    { &gDogLyingDownAnim, 1.0f, 0, 27, ANIMMODE_ONCE, -6 },  { &gDogLyingDownAnim, 1.0f, 28, -1, ANIMMODE_ONCE, -6 },
    { &gDogLyingDownAnim, 1.0f, 54, 54, ANIMMODE_ONCE, -6 }, { &gDogWalkAnim, -1.5f, -1, 0, ANIMMODE_LOOP, -6 },
    { &gDogJumpAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },        { &gDogLongJumpAnim, 1.2f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDogJump2Anim, 1.2f, 0, -1, ANIMMODE_ONCE, 0 },       { &gDogWalkAnim, 0.5f, 0, -1, ANIMMODE_LOOP, 0 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

void func_80B24630(SkelAnime* skelAnime, AnimationInfoS arg1[], s32 arg2) {
    f32 frameCount;

    arg1 += arg2;
    if (arg1->frameCount < 0) {
        frameCount = Animation_GetLastFrame(arg1->animation);
    } else {
        frameCount = arg1->frameCount;
    }

    Animation_Change(skelAnime, arg1->animation, arg1->playSpeed + (BREG(88) * 0.1f), arg1->startFrame, frameCount,
                     arg1->mode, arg1->morphFrames);
}

void func_80B246F4(EnRacedog* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 26.0f, 10.0f, 0.0f, 5);
}

s16 func_80B2478C(Path* path, s32 arg1, Vec3f* pos, f32* arg3) {
    Vec3s* point;
    f32 phi_f14;
    f32 sp1C;
    f32 xDiff;
    f32 zDiff;

    if (path != NULL) {
        point = Lib_SegmentedToVirtual(path->points);
        point = &point[arg1];
        phi_f14 = (randPlusMinusPoint5Scaled(100.0f) + point->x) - pos->x;
        sp1C = (randPlusMinusPoint5Scaled(100.0f) + point->z) - pos->z;
        xDiff = point->x - pos->x;
        zDiff = point->z - pos->z;
    } else {
        phi_f14 = 0.0f;
        sp1C = 0.0f;
        xDiff = 0.0f;
        zDiff = 0.0f;
    }

    *arg3 = SQ(xDiff) + SQ(zDiff);
    return RADF_TO_BINANG(Math_Acot2F(sp1C, phi_f14));
}

void func_80B248B8(EnRacedog* this, Vec3f* arg1) {
    f32 sp20;
    f32 sp1C;

    if (this->actor.floorPoly != NULL) {
        sp20 = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.y);
        sp1C = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.z);

        arg1->x = -Math_Acot2F(1.0f, -sp1C * sp20);
    }
}

void EnRacedog_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRacedog* this = THIS;
    ColliderCylinder* collider = &this->collider;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gDogSkel, NULL, this->jointTable, this->morphTable, DOG_LIMB_MAX);
    Collider_InitCylinder(globalCtx, collider);
    Collider_SetCylinder(globalCtx, collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_1E0 = SubS_GetPathByIndex(globalCtx, ENRACEDOG_GET_PATH(&this->actor), 0x3F);
    Actor_SetScale(&this->actor, 0.0075f);
    this->actor.gravity = -3.0f;
    if (ENRACEDOG_GET_3E0(&this->actor) < 14) {
        this->unk_290 = ENRACEDOG_GET_3E0(&this->actor);
    } else {
        Actor_MarkForDeath(&this->actor);
    }

    this->unk_2BC = 0xFF;
    this->unk_2C0 = 0x32;
    this->unk_288 = 0xC;
    this->unk_2A0.x = 0.0f;
    this->unk_2A0.y = 0.0f;
    this->unk_2A0.z = 0.0f;
    this->unk_2C4 = 1.0f;

    if ((D_80B25D88[this->unk_290].unk_0E >= 0x353F) && (this->unk_290 == (s16)Rand_ZeroFloat(20.0f))) {
        this->unk_28C = 5;
    } else {
        this->unk_28C = 0;
    }

    this->unk_28A = 60;
    this->unk_28A += this->unk_28C;
    this->unk_298 = D_80B25D50[D_80B25D88[this->unk_290].unk_08][0];
    this->unk_29C = 0;
    this->unk_2B8 = -1;

    func_80B24E14(this);
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.flags |= ACTOR_FLAG_20;
    D_80B25E68 = D_80B25D88[(s16)((gSaveContext.eventInf[0] & 0xF8) >> 3)];
    this->unk_292 = D_80B25E68.unk_0A;
    func_80B24630(&this->skelAnime, D_80B25EF0, 0);
    D_80B25EF0->playSpeed = Rand_ZeroFloat(0.5f) + 1.0f;
    this->actionFunc = func_80B24C14;
}

void EnRacedog_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRacedog* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B24C14(EnRacedog* this, GlobalContext* globalCtx) {
    s16 phi_v1;

    if (this->unk_28A == 0) {
        phi_v1 = 0;
    } else {
        this->unk_28A--;
        phi_v1 = this->unk_28A;
    }

    if (phi_v1 == 0) {
        this->unk_28A = Rand_S16Offset(50, 50);
        if (this->unk_28C == 0) {
            play_sound(NA_SE_SY_START_SHOT);
        }

        func_80B24630(&this->skelAnime, D_80B25EF0, 2);
        this->actionFunc = func_80B24CB4;
    }
}

void func_80B24CB4(EnRacedog* this, GlobalContext* globalCtx) {
    s16 phi_a1;
    f32 sp30;

    this->collider.dim.radius = 15;
    if (this->unk_1E0 != 0) {
        phi_a1 = func_80B2478C(this->unk_1E0, this->unk_1E8, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            phi_a1 = this->actor.wallYaw;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, phi_a1, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (sp30 <= 2500.0f) {
            this->unk_1E8++;
            if (this->unk_1E8 >= (this->unk_1E0->count - 1)) {
                this->unk_1E8 = 0;
            }
        }

        func_80B24F08(this);
        if ((this->unk_1E8 >= ((this->unk_1E0->count / 4) * 3)) && (this->unk_290 == D_80B25D4C)) {
            D_80B25D48++;
        }

        func_80B252F8(this);
        func_80B2538C(this);
        Actor_MoveWithGravity(&this->actor);
    }

    func_80B25448(this);
    func_80B256BC(this);
    func_80B255AC(this, globalCtx);
}

void func_80B24E14(EnRacedog* this) {
    if (this->unk_290 % 2) {
        D_80B25D88[this->unk_290].unk_0E =
            (((gSaveContext.save.weekEventReg[42 + (this->unk_290 / 2)]) & (0x10 | 0x20 | 0x40 | 0x80)) >> 4) + 0x3539;
    } else {
        D_80B25D88[this->unk_290].unk_0E =
            ((gSaveContext.save.weekEventReg[42 + (this->unk_290 / 2)]) & (1 | 2 | 4 | 8)) + 0x3539;
    }

    if ((D_80B25D88[this->unk_290].unk_0E >= 0x3547) || (D_80B25D88[this->unk_290].unk_0E < 0x3539)) {
        D_80B25D88[this->unk_290].unk_0E = 0x353E;
    }
    if (D_80B25D88[this->unk_290].unk_0E == 0x3547) {
        D_80B25D88[this->unk_290].unk_0E = 0x3538;
    }
}

void func_80B24F08(EnRacedog* this) {
    s32 temp_a0;
    s32 temp_v1 = this->unk_1E0->count;

    if (this->unk_2B8 < this->unk_1E8) {
        this->unk_2B8 = this->unk_1E8;
        if (this->unk_1E8 == 0) {
            this->unk_298 = D_80B25D50[D_80B25D88[this->unk_290].unk_08][0];
        } else {
            temp_a0 = temp_v1 / 4;
            if (this->unk_1E8 < temp_a0) {
                if (D_80B25D88[this->unk_290].unk_08 == 5) {
                    this->unk_298 = D_80B25D50[D_80B25D88[this->unk_290].unk_08][0] + randPlusMinusPoint5Scaled(1.0f);
                } else {
                    this->unk_298 = 5.0f + randPlusMinusPoint5Scaled(1.0f);
                }

                if ((D_80B25D88[this->unk_290].unk_0E < 0x353E) && (this->unk_290 != D_80B25D4C)) {
                    this->unk_298 *= D_80B25D88[this->unk_290].unk_04;
                }
            } else if (this->unk_1E8 < (temp_a0 * 3)) {
                if (this->unk_1E8 < D_80B25D88[this->unk_290].unk_0C) {
                    this->unk_298 = 5.0f + randPlusMinusPoint5Scaled(1.0f);
                } else {
                    this->unk_298 = D_80B25D50[D_80B25D88[this->unk_290].unk_08][1] + randPlusMinusPoint5Scaled(1.0f);

                    if ((D_80B25D88[this->unk_290].unk_0E < 0x353E) && (this->unk_290 != D_80B25D4C)) {
                        this->unk_298 *= D_80B25D88[this->unk_290].unk_04;
                    }
                }
            } else if (this->unk_1E8 < temp_v1) {
                func_80B251EC(this);
            } else {
                this->unk_298 = randPlusMinusPoint5Scaled(1.0f) + 5.0f;
            }
        }
    }

    if ((this->unk_1E8 != 0) || (this->unk_29C != 0)) {
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    Math_ApproachF(&this->actor.speedXZ, this->unk_298, 0.5f, 3.0f);

    if (this->unk_290 == this->unk_292) {
        if (this->actor.speedXZ > 7.5f) {
            this->actor.speedXZ = 7.5f;
        }
    } else {
        if (this->actor.speedXZ > 7.0f) {
            this->actor.speedXZ = 7.0f;
        }
    }
}

void func_80B251EC(EnRacedog* this) {
    f32 temp;

    if (D_80B25D88[this->unk_290].unk_00 == -1.0f) {
        if (D_80B25D48 < 100.0f) {
            D_80B25D88[this->unk_290].unk_00 = 200.0f / (200.0f - D_80B25D48);
        } else {
            D_80B25D88[this->unk_290].unk_00 = 2.0f;
        }
    }

    if (D_80B25D88[this->unk_290].unk_0E < 0x3542) {
        temp = D_80B25D88[this->unk_290].unk_00;
        this->unk_298 = temp * D_80B25D50[D_80B25D88[this->unk_290].unk_08][1];
    }

    if ((D_80B25D88[this->unk_290].unk_0E < 0x353E) && (this->unk_290 != D_80B25D4C)) {
        this->unk_298 *= D_80B25D88[this->unk_290].unk_04;
    }
}

void func_80B252F8(EnRacedog* this) {
    if ((this->unk_1E8 >= 9) && (this->unk_29C == 0)) {
        this->unk_29C = 1;
    }

    if ((this->unk_1E8 >= 0xB) && (this->unk_29C == 1)) {
        this->unk_29C = 2;
    }

    if (((this->unk_1E8 >= D_80B25D44) || (this->unk_29C <= 0)) && (this->unk_1E8 > D_80B25D44)) {
        D_80B25D44 = this->unk_1E8;
        D_80B25D4C = this->unk_290;
    }
}

void func_80B2538C(EnRacedog* this) {
    if (func_80B25490(this, D_80B25E78) && this->unk_29C == 2) {
        D_80B25D40++;
        if (D_80B25D40 == 1) {
            Audio_QueueSeqCmd(NA_BGM_HORSE_GOAL | 0x8000);
            play_sound(NA_SE_SY_START_SHOT);
        }

        this->unk_29C = 3;
        if (this->unk_290 == this->unk_292) {
            gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & 7) | (D_80B25D40 * 8);
        }
    }
}

void func_80B25448(EnRacedog* this) {
    if (this->actor.speedXZ < 3.0f) {
        D_80B25EF0[2].playSpeed = 0.9f;
    } else {
        D_80B25EF0[2].playSpeed = 1.0f;
    }
}

s32 func_80B25490(EnRacedog* this, Vec2f* arg1) {
    f32 xDistToTopFront;
    f32 zDistToTopFront;
    f32 xDistToBottomFront;
    f32 xDistToBottomBack;
    f32 zDistToBottomBack;
    f32 zDistToBottomFront;
    f32 zDistToTopBack;
    f32 xDistToTopBack;
    f32 temp_f0;
    f32 temp;

    xDistToTopFront = this->actor.world.pos.x - arg1[0].x;
    zDistToTopFront = this->actor.world.pos.z - arg1[0].z;
    xDistToBottomFront = this->actor.world.pos.x - arg1[1].x;
    zDistToBottomFront = this->actor.world.pos.z - arg1[1].z;
    xDistToBottomBack = this->actor.world.pos.x - arg1[2].x;
    zDistToBottomBack = this->actor.world.pos.z - arg1[2].z;
    xDistToTopBack = this->actor.world.pos.x - arg1[3].x;
    zDistToTopBack = this->actor.world.pos.z - arg1[3].z;

    temp_f0 = ((xDistToTopFront * zDistToBottomFront) - (xDistToBottomFront * zDistToTopFront));
    temp = (((xDistToBottomFront * zDistToBottomBack) - (xDistToBottomBack * zDistToBottomFront)));
    if (temp_f0 * temp < 0.0f) {
        return false;
    }

    temp_f0 = ((xDistToTopFront * zDistToBottomFront) - (xDistToBottomFront * zDistToTopFront));
    temp = ((xDistToBottomBack * zDistToTopBack) - (xDistToTopBack * zDistToBottomBack));
    if (temp_f0 * temp < 0.0f) {
        return false;
    }

    temp_f0 = ((xDistToTopFront * zDistToBottomFront) - (xDistToBottomFront * zDistToTopFront));
    temp = ((xDistToTopBack * zDistToTopFront) - (xDistToTopFront * zDistToTopBack));
    if (temp_f0 * temp < 0.0f) {
        return false;
    }

    return true;
}

void func_80B255AC(EnRacedog* this, GlobalContext* globalCtx) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 mod = (this->actor.speedXZ > 6.0f) ? 2 : 3;
    Vec3f sp38;

    if (((this->unk_290 + curFrame) % mod) == 0) {
        sp38.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(15.0f);
        sp38.y = this->actor.world.pos.y;
        sp38.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(15.0f);
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &sp38, 10.0f, 0, 2.0f, 300, 0, true);
    }
}

void func_80B256BC(EnRacedog* this) {
    s16 curFrame = this->skelAnime.curFrame;

    if ((curFrame == 1) || (curFrame == 7)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRacedog* this = THIS;
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };

    this->unk_292 = D_80B25E68.unk_0A;

    this->actionFunc(this, globalCtx);

    func_80B246F4(this, globalCtx);
    func_80B248B8(this, &sp2C);
    Math_ApproachF(&this->unk_2AC.x, sp2C.x, 0.2f, 0.1f);

    if (this->unk_2A0.x > 0.0f) {
        if ((this->unk_2AC.x < 0.0f) && (this->unk_2AC.x > -0.1f)) {
            this->skelAnime.curFrame = 4.0f;
            this->actor.velocity.y = 5.5f;
        }
    }

    if (!(this->actor.bgCheckFlags & 1)) {
        this->skelAnime.curFrame = 0.0f;
    }

    this->unk_2A0 = this->unk_2AC;
    SkelAnime_Update(&this->skelAnime);
}

void func_80B2583C(EnRacedog* this) {
    s16 phi_v1;

    if (this->unk_288 >= 7) {
        this->unk_2BC -= 0x10;
        this->unk_2C0 += 8;
        this->unk_2C4 += 0.05f;
    } else {
        this->unk_2BC += 0x10;
        this->unk_2C0 -= 8;
        this->unk_2C4 -= 0.05f;
    }

    if (this->unk_288 == 0) {
        phi_v1 = 0;
    } else {
        this->unk_288--;
        phi_v1 = this->unk_288;
    }

    if (phi_v1 == 0) {
        this->unk_288 = 0xC;
    }
}

void func_80B258D8(EnRacedog* this, GlobalContext* globalCtx) {
    Vec3s sp48 = gZeroVec3s;
    s32 phi_v0 = (this->unk_290 == this->unk_292) ? true : false;

    if (phi_v0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        func_80B2583C(this);
        Matrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y + 40.0f,
                                              this->actor.world.pos.z, &sp48);

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, this->unk_2BC, 0, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, this->unk_2C0, 0, 255);
        Matrix_Scale(this->unk_2C4 * 2.0f, this->unk_2C4 * 2.0f, this->unk_2C4 * 2.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gDogSelectionArrowEmptyDL);
        gSPDisplayList(POLY_OPA_DISP++, gDogSelectionArrowDL);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

s32 EnRacedog_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    return false;
}

void EnRacedog_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnRacedog* this = THIS;
    Vec3f sp1C = { 0.0f, 20.0f, 0.0f };

    if (limbIndex == DOG_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&sp1C, &this->actor.focus.pos);
    }

    if (limbIndex == DOG_LIMB_TAIL) {
        func_80B258D8(this, globalCtx);
    }
}

void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRacedog* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    switch (D_80B25D88[this->unk_290].unk_08) {
        case 3:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
            break;
        case 1:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 0);
            break;
        case 5:
            gDPSetEnvColor(POLY_OPA_DISP++, 79, 79, 143, 0);
            break;
        case 6:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 207, 47, 0);
            break;
        case 4:
            gDPSetEnvColor(POLY_OPA_DISP++, 143, 79, 47, 0);
            break;
        case 2:
            gDPSetEnvColor(POLY_OPA_DISP++, 143, 143, 143, 0);
            break;
        default:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
            break;
    }

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateStateAroundXAxis(this->unk_2AC.x);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnRacedog_OverrideLimbDraw, EnRacedog_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
