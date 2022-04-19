/*
 * File: z_en_dg.c
 * Overlay: ovl_En_Dg
 * Description: Dog
 */

#include "z_en_dg.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_800000)

#define THIS ((EnDg*)thisx)

void EnDg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8098A468(EnDg* this, GlobalContext* globalCtx);
void func_8098A55C(EnDg* this, GlobalContext* globalCtx);
void func_8098A618(EnDg* this, GlobalContext* globalCtx);
void func_8098A70C(EnDg* this, GlobalContext* globalCtx);
void func_8098A89C(EnDg* this, GlobalContext* globalCtx);
void func_8098A938(EnDg* this, GlobalContext* globalCtx);
void func_8098AB48(EnDg* this, GlobalContext* globalCtx);
void func_8098AC34(EnDg* this, GlobalContext* globalCtx);
void func_8098AF44(EnDg* this, GlobalContext* globalCtx);
void func_8098AF98(EnDg* this, GlobalContext* globalCtx);
void func_8098B004(EnDg* this, GlobalContext* globalCtx);
void func_8098B198(EnDg* this, GlobalContext* globalCtx);
void func_8098B28C(EnDg* this, GlobalContext* globalCtx);
void func_8098B390(EnDg* this, GlobalContext* globalCtx);
void func_8098B560(EnDg* this, GlobalContext* globalCtx);
void func_8098B88C(EnDg* this, GlobalContext* globalCtx);
void func_8098BA64(EnDg* this, GlobalContext* globalCtx);
void func_8098BB10(EnDg* this, GlobalContext* globalCtx);
void func_8098BBEC(EnDg* this, GlobalContext* globalCtx);
void func_8098BC54(EnDg* this, GlobalContext* globalCtx);

const ActorInit En_Dg_InitVars = {
    ACTOR_EN_DG,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnDg),
    (ActorFunc)EnDg_Init,
    (ActorFunc)EnDg_Destroy,
    (ActorFunc)EnDg_Update,
    (ActorFunc)EnDg_Draw,
};

static u8 D_8098C2A0 = 0;

typedef struct {
    s16 unk_00;
    s16 unk_02;
} D_8098C2A4_s;

static D_8098C2A4_s D_8098C2A4 = { 0x0063, 0x0000 };

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} D_8098C2A8_s;

static D_8098C2A8_s D_8098C2A8[] = {
    { 3, 0, 0x3539 },  { 1, 1, 0x353A },  { 5, 2, 0x353B },  { 2, 3, 0x353C },  { 4, 4, 0x3538 },
    { 2, 5, 0x353E },  { 3, 6, 0x353F },  { 1, 7, 0x3540 },  { 1, 8, 0x3541 },  { 6, 9, 0x3542 },
    { 2, 10, 0x3543 }, { 3, 11, 0x3544 }, { 1, 12, 0x3545 }, { 4, 13, 0x3546 },
};

static D_8098C2A8_s D_8098C2FC = { 0, -1, 0x353E };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x04, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
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

static AnimationInfoS sAnimations[] = {
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

void func_80989140(SkelAnime* skelAnime, AnimationInfoS arg1[], s32 arg2) {
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

void func_80989204(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    if ((player->transformation == PLAYER_FORM_DEKU) && (this->actionFunc == func_8098AC34)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        Collider_ResetCylinderAT(globalCtx, &this->collider.base);
    }

    if ((this->unk_290 != 1) && !(this->unk_280 & 2)) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        Collider_ResetCylinderOC(globalCtx, &this->collider.base);
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 26.0f, 10.0f, 0.0f, 5);
}

void func_8098933C(EnDg* this, Vec3f* arg1) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    if (this->actor.floorPoly != NULL) {
        sp24 = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.x);
        sp20 = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.y);
        sp1C = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.z);

        __sinf(0.0f);
        __cosf(0.0f);
        arg1->x = -Math_Acot2F(1.0f, -sp1C * sp20);
        arg1->z = Math_Acot2F(1.0f, -sp24 * sp20);
    }
}

s32 func_80989418(EnDg* this, Path* arg1, s32 arg2) {
    Vec3s* sp5C = Lib_SegmentedToVirtual(arg1->points);
    s32 count = arg1->count;
    s32 idx = arg2;
    s32 sp50 = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[idx]);
    if (idx == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if (idx == count - 1) {
        phi_f12 = sp5C[count - 1].x - sp5C[count - 2].x;
        phi_f14 = sp5C[count - 1].z - sp5C[count - 2].z;
    } else {
        phi_f12 = sp5C[idx + 1].x - sp5C[idx - 1].x;
        phi_f14 = sp5C[idx + 1].z - sp5C[idx - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);
    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = true;
    }

    return sp50;
}

s16 func_809895B4(Path* path, s32 idx, Vec3f* pos, f32* distSQ) {
    Vec3s* points;
    f32 diffX;
    f32 diffZ;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[idx];
        diffX = points->x - pos->x;
        diffZ = points->z - pos->z;
    } else {
        diffX = 0.0f;
        diffZ = 0.0f;
    }

    *distSQ = SQ(diffX) + SQ(diffZ);

    return RADF_TO_BINANG(Math_Acot2F(diffZ, diffX));
}

void func_80989674(EnDg* this, GlobalContext* globalCtx) {
    s16 phi_a1;
    f32 sp30;

    if (this->unk_1DC != NULL) {
        phi_a1 = func_809895B4(this->unk_1DC, this->unk_1E0, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            phi_a1 = this->actor.wallYaw;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, phi_a1, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        if (func_80989418(this, this->unk_1DC, this->unk_1E0)) {
            if (this->unk_1E0 >= (this->unk_1DC->count - 1)) {
                this->unk_1E0 = 0;
            } else {
                this->unk_1E0++;
            }
        }

        if ((this->unk_286 == 21) || ((this->unk_286 == 20) && (globalCtx->sceneNum == SCENE_OMOYA))) {
            Math_ApproachF(&this->actor.speedXZ, 1.0f, 0.2f, 1.0f);
        } else if (this->unk_286 == 20) {
            Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
        } else if (globalCtx->sceneNum == SCENE_CLOCKTOWER) {
            Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
        } else if (D_8098C2A8[this->unk_286].unk_04 & 0x11) {
            Math_ApproachF(&this->actor.speedXZ, 1.0f, 0.2f, 1.0f);
        } else {
            Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80989864(EnDg* this, GlobalContext* globalCtx) {
    s16 frame = this->skelAnime.curFrame;
    s16 mod = (this->actor.speedXZ > 6.0f) ? 2 : 3;
    Vec3f sp38;

    if (((this->unk_286 + frame) % mod) == 0) {
        sp38.x = randPlusMinusPoint5Scaled(15.0f) + this->actor.world.pos.x;
        sp38.y = this->actor.world.pos.y;
        sp38.z = randPlusMinusPoint5Scaled(15.0f) + this->actor.world.pos.z;
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &sp38, 10.0f, 0, 2.0f, 300, 0, 1);
    }
}

void func_80989974(EnDg* this) {
    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 7.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void func_809899C8(EnDg* this, f32 arg1) {
    if (Animation_OnFrame(&this->skelAnime, arg1)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_BARK);
    }
}

void func_80989A08(EnDg* this, f32 arg1) {
    if (Animation_OnFrame(&this->skelAnime, arg1)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_ANG_BARK);
    }
}

void func_80989A48(EnDg* this) {
    if (Animation_OnFrame(&this->skelAnime, 23.0f) || Animation_OnFrame(&this->skelAnime, 28.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_WHINE);
    }
}

void func_80989A9C(EnDg* this, f32 arg1) {
    if (Animation_OnFrame(&this->skelAnime, arg1)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_GROAN);
    }
}

void func_80989ADC(EnDg* this, GlobalContext* globalCtx) {
    if (!(this->actor.bgCheckFlags & 0x20)) {
        if ((this->unk_286 == 21) || ((this->unk_286 == 20) && (globalCtx->sceneNum == SCENE_OMOYA))) {
            func_80989140(&this->skelAnime, sAnimations, 1);
        } else if (this->unk_286 == 20) {
            func_80989140(&this->skelAnime, sAnimations, 2);
        } else if (globalCtx->sceneNum == SCENE_CLOCKTOWER) {
            func_80989140(&this->skelAnime, sAnimations, 2);
        } else if (D_8098C2A8[this->unk_286].unk_04 & 0x11) {
            func_80989140(&this->skelAnime, sAnimations, 1);
        } else {
            func_80989140(&this->skelAnime, sAnimations, 2);
        }
        this->actionFunc = func_8098A468;
    }
}

void func_80989BF8(EnDg* this) {
    if (this->unk_286 < 14) {
        if (this->unk_286 % 2) {
            D_8098C2A8[this->unk_286].unk_04 =
                0x3538 +
                ((gSaveContext.save.weekEventReg[42 + (this->unk_286 / 2)] & (0x10 | 0x20 | 0x40 | 0x80)) >> 4);
        } else {
            D_8098C2A8[this->unk_286].unk_04 =
                0x3538 + (gSaveContext.save.weekEventReg[42 + (this->unk_286 / 2)] & (1 | 2 | 4 | 8));
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }

    if ((D_8098C2A8[this->unk_286].unk_04 >= 0x3547) || (D_8098C2A8[this->unk_286].unk_04 < 0x3538)) {
        D_8098C2A8[this->unk_286].unk_04 = 0x353E;
    }

    if (D_8098C2A8[this->unk_286].unk_04 == 0x353D) {
        D_8098C2A8[this->unk_286].unk_04 = 0x3538;
    }
}

void func_80989D38(EnDg* this, GlobalContext* globalCtx) {
    if (this->unk_286 == 21) {
        if (CURRENT_DAY == 1) {
            Message_StartTextbox(globalCtx, 0x91C, NULL);
        } else {
            Message_StartTextbox(globalCtx, 0x91E, NULL);
        }
    } else if ((this->unk_286 >= 0) && (this->unk_286 < 14)) {
        Message_StartTextbox(globalCtx, D_8098C2A8[this->unk_286].unk_04, NULL);
    } else if (this->unk_286 == 20) {
        Message_StartTextbox(globalCtx, 0x353D, NULL);
    } else {
        Message_StartTextbox(globalCtx, 0x627, NULL);
    }
}

void func_80989E18(EnDg* this, GlobalContext* globalCtx) {
    D_8098C2A8_s* temp;

    if ((D_8098C2A0 != 0) && !(this->unk_280 & 1)) {
        this->actor.flags |= ACTOR_FLAG_8000000;
        this->unk_280 |= 1;
    } else if ((D_8098C2A0 == 0) && (this->unk_280 & 1)) {
        this->actor.flags &= ~ACTOR_FLAG_8000000;
        this->unk_280 &= ~1;
    }

    if (Actor_HasParent(&this->actor, globalCtx)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_BARK);
        this->unk_290 = 1;
        D_8098C2FC = D_8098C2A8[this->unk_286];
        if (D_8098C2A0 == 0) {
            this->actor.flags |= ACTOR_FLAG_8000000;
            D_8098C2A0 = 1;
            this->unk_280 |= 1;
        }

        func_80989140(&this->skelAnime, sAnimations, 5);
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->actor.speedXZ = 0.0f;
        if (Player_GetMask(globalCtx) == PLAYER_MASK_TRUTH) {
            this->actor.flags |= ACTOR_FLAG_10000;
            func_800B8614(&this->actor, globalCtx, 100.0f);
            this->actionFunc = func_8098BBEC;
        } else {
            this->actionFunc = func_8098BA64;
        }
    } else {
        Actor_LiftActor(&this->actor, globalCtx);
    }
}

s32 func_80989FC8(GlobalContext* globalCtx) {
    EnDg* enemy = (EnDg*)globalCtx->actorCtx.actorLists[ACTORCAT_ENEMY].first;
    f32 minDist = 9999.0f;
    f32 dist;

    while (enemy != NULL) {
        if (enemy->actor.id == ACTOR_EN_DG) {
            if (enemy->actor.isTargeted) {
                D_8098C2A4.unk_00 = enemy->unk_286;
                return true;
            }

            dist = enemy->actor.xzDistToPlayer;
            if (dist < minDist) {
                D_8098C2A4.unk_00 = enemy->unk_286;
                minDist = dist;
            }
        }
        enemy = (EnDg*)enemy->actor.next;
    }

    if (D_8098C2A4.unk_00 != 99) {
        return true;
    }

    return false;
}

void func_8098A064(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags3 & 0x20000000) {
        if (D_8098C2A4.unk_00 == 99) {
            func_80989FC8(globalCtx);
        }

        if (this->unk_286 == D_8098C2A4.unk_00) {
            if (!(this->unk_280 & 0x20)) {
                this->unk_280 |= 0x20;
                func_80989140(&this->skelAnime, sAnimations, 1);
                this->actionFunc = func_8098AF44;
            } else if ((this->actionFunc == func_8098B004) || (this->actionFunc == func_8098AB48)) {
                if (DECR(this->unk_292) == 0) {
                    this->unk_292 = 10;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_BARK);
                }
            }
        }
    } else if (this->unk_286 == D_8098C2A4.unk_00) {
        this->unk_280 &= ~0x20;
        D_8098C2A4.unk_00 = 99;
        func_80989ADC(this, globalCtx);
        this->actionFunc = func_8098A468;
    }
}

s32 func_8098A1B4(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (player->transformation) {
        case PLAYER_FORM_GORON:
        case PLAYER_FORM_ZORA:
            if (this->actor.xzDistToPlayer < 300.0f) {
                return true;
            }

        case PLAYER_FORM_DEKU:
            if (this->actor.xzDistToPlayer < 250.0f) {
                return true;
            }
            break;
    }

    return false;
}

void func_8098A234(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(this->actor.bgCheckFlags & 0x20)) {
        switch (player->transformation) {
            case PLAYER_FORM_HUMAN:
                if (this->unk_28C != 1) {
                    this->unk_28C = 1;
                    this->unk_280 &= ~2;
                    func_80989ADC(this, globalCtx);
                }
                break;

            case PLAYER_FORM_ZORA:
                this->unk_280 &= ~2;
                if ((this->unk_28C != 4) && (player->actor.speedXZ > 1.0f)) {
                    this->unk_28C = 4;
                    func_80989140(&this->skelAnime, sAnimations, 2);
                    this->actionFunc = func_8098B004;
                }

                if ((this->unk_28C != 5) && (this->unk_28C != 4)) {
                    this->unk_28C = 5;
                    func_80989ADC(this, globalCtx);
                }
                break;

            case PLAYER_FORM_GORON:
                this->unk_280 &= ~2;
                if ((this->unk_28C != 2) && (player->actor.speedXZ > 1.0f)) {
                    this->unk_28C = 2;
                    func_80989140(&this->skelAnime, sAnimations, 11);
                    this->unk_282 = 50;
                    this->actionFunc = func_8098A618;
                }

                if ((this->unk_28C != 3) && (this->unk_28C != 2)) {
                    this->unk_28C = 3;
                    func_80989ADC(this, globalCtx);
                }
                break;

            case PLAYER_FORM_DEKU:
                this->unk_280 &= ~2;
                if ((this->unk_28C != 6) && (player->actor.speedXZ > 1.0f)) {
                    this->unk_28C = 6;
                    func_80989140(&this->skelAnime, sAnimations, 2);
                    this->actionFunc = func_8098A938;
                }

                if ((this->unk_28C != 7) && (this->unk_28C != 6)) {
                    this->unk_28C = 7;
                    func_80989ADC(this, globalCtx);
                }
                break;
        }
    }
}

void func_8098A468(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -3.0f;
    func_80989674(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    if (player->transformation == PLAYER_FORM_HUMAN) {
        func_80989E18(this, globalCtx);
    }

    func_8098A064(this, globalCtx);
    func_80989974(this);
    if (!(this->actor.bgCheckFlags & 1)) {
        this->actionFunc = func_8098AF98;
    }

    if (DECR(this->unk_282) == 0) {
        this->unk_282 = Rand_S16Offset(20, 20);
        func_80989140(&this->skelAnime, sAnimations, 3);
        this->actionFunc = func_8098A55C;
    }
}

void func_8098A55C(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->transformation == PLAYER_FORM_HUMAN) {
        func_80989E18(this, globalCtx);
    }

    func_809899C8(this, 13.0f);
    func_809899C8(this, 19.0f);
    if (!(this->actor.bgCheckFlags & 1)) {
        this->actionFunc = func_8098AF98;
    }

    if (DECR(this->unk_282) == 0) {
        this->unk_282 = Rand_S16Offset(60, 60);
        func_80989ADC(this, globalCtx);
    }
}

void func_8098A618(EnDg* this, GlobalContext* globalCtx) {
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -3.0f;

    if (DECR(this->unk_282) == 0) {
        this->unk_282 = 50;
        func_80989140(&this->skelAnime, sAnimations, 2);
        this->actionFunc = func_8098A70C;
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x3E8, 1);
        if (this->actor.bgCheckFlags & 8) {
            this->actor.shape.rot.y = this->actor.wallYaw;
        }
        this->actor.world.rot.y = this->actor.shape.rot.y;
        Math_ApproachF(&this->actor.speedXZ, -1.5f, 0.2f, 1.0f);
        Actor_MoveWithGravity(&this->actor);
    }

    func_80989974(this);
    func_80989A9C(this, 0);
}

void func_8098A70C(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 phi_a1;

    if (this->actor.xzDistToPlayer < 250.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, -this->actor.yawTowardsPlayer, 4, 0xC00);

        if (this->actor.bgCheckFlags & 8) {
            phi_a1 = this->actor.wallYaw;
        } else {
            phi_a1 = 0;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, phi_a1, 4, 0x3E8, 1);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (player->actor.speedXZ != 0.0f) {
            Math_ApproachF(&this->actor.speedXZ, player->actor.speedXZ, 0.2f, 1.0f);
        } else {
            Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
        }
    } else {
        func_80989140(&this->skelAnime, sAnimations, 3);
        this->actionFunc = func_8098A89C;
    }

    if (this->actor.speedXZ > 7.0f) {
        this->actor.speedXZ = 7.0f;
    }

    Actor_MoveWithGravity(&this->actor);
    func_80989974(this);
    if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_CRY);
    } else if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void func_8098A89C(EnDg* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xC00);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->actor.xzDistToPlayer < 250.0f) {
        func_80989140(&this->skelAnime, sAnimations, 11);
        this->unk_282 = 50;
        this->actionFunc = func_8098A618;
    }

    func_80989A08(this, 13.0f);
    func_80989A08(this, 19.0f);
}

void func_8098A938(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -3.0f;
    if (this->actor.bgCheckFlags & 8) {
        this->actor.shape.rot.y = this->actor.wallYaw;
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->actor.xzDistToPlayer < 70.0f) {
        Math_ApproachZeroF(&this->actor.speedXZ, 0.2f, 1.0f);
        if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
            s16 y = ABS_ALT(player->actor.shape.rot.y - this->actor.shape.rot.y);

            this->unk_28E = 20;
            if (y < 0x4000) {
                func_80989140(&this->skelAnime, sAnimations, 14);
                this->actionFunc = func_8098AC34;
            } else {
                func_80989140(&this->skelAnime, sAnimations, 11);
                sAnimations[11].playSpeed = -1.0f;
                this->actionFunc = func_8098B198;
            }
        }
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xC00);
        Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 1.0f);
    }

    Actor_MoveWithGravity(&this->actor);
    func_80989974(this);
    func_80989A08(this, 5.0f);
}

void func_8098AAAC(EnDg* this, GlobalContext* globalCtx) {
    this->unk_280 &= ~8;
    Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.1f, 0.5f);
    Actor_MoveWithGravity(&this->actor);
    if (DECR(this->unk_28E) == 0) {
        this->unk_28E = 20;
        this->actionFunc = func_8098A938;
    }

    func_80989974(this);
    func_80989A08(this, 3.0f);
}

void func_8098AB48(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(this->actor.bgCheckFlags & 1)) {
        this->actionFunc = func_8098AF98;
    }

    if (this->actor.xzDistToPlayer < 50.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xC00);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else {
        if (player->stateFlags3 & 0x20000000) {
            func_80989140(&this->skelAnime, sAnimations, 1);
        } else {
            func_80989140(&this->skelAnime, sAnimations, 2);
        }
        this->actionFunc = func_8098B004;
    }

    func_8098A064(this, globalCtx);
    if (!(this->unk_280 & 0x20)) {
        func_80989A48(this);
    }
}

void func_8098AC34(EnDg* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.curFrame;

    if ((this->actor.xyzDistToPlayerSq < 800.0f) && (this->collider.base.atFlags & AT_BOUNCED)) {
        this->unk_28E = 60;
        this->unk_280 &= ~2;
        this->unk_280 |= 8;
        this->collider.base.atFlags &= ~AT_BOUNCED;
        this->actor.speedXZ *= -1.0f;
        func_80989140(&this->skelAnime, sAnimations, 2);
        this->actionFunc = func_8098AAAC;
        return;
    }

    if (DECR(this->unk_28E) == 0) {
        this->unk_28E = 60;
        this->unk_280 &= ~2;
        func_80989140(&this->skelAnime, sAnimations, 2);
        this->actionFunc = func_8098AAAC;
    }

    if (sp26 < 9) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
            sAnimations[14].playSpeed = randPlusMinusPoint5Scaled(1.0f) + 3.0f;
        }
        func_80989864(this, globalCtx);
    } else {
        this->unk_280 |= 2;
        if (Animation_OnFrame(&this->skelAnime, 9.0f)) {
            f32 rand = randPlusMinusPoint5Scaled(1.5f);

            sAnimations[14].playSpeed = 1.2f;
            this->actor.velocity.y = 2.0f * rand + 3.0f;
            this->actor.speedXZ = 8.0f + rand;
        } else if (sp26 >= 0x15) {
            Math_ApproachF(&this->actor.speedXZ, 2.5f, 0.2f, 1.0f);
        }
        if (sp26 >= 0x18) {
            func_80989864(this, globalCtx);
        }
        Actor_MoveWithGravity(&this->actor);
    }

    func_80989A9C(this, 10.0f);
}

// Unused?
void func_8098AE58(EnDg* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 150.0f) {
        func_80989140(&this->skelAnime, sAnimations, 11);
        this->actionFunc = func_8098B28C;
    } else if (this->actor.xzDistToPlayer < 200.0f) {
        func_80989140(&this->skelAnime, sAnimations, 3);
        this->actionFunc = func_8098B390;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xC00);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        Math_ApproachF(&this->actor.speedXZ, 2.0f, 0.2f, 1.0f);
        Actor_MoveWithGravity(&this->actor);
    }

    func_80989974(this);
    func_809899C8(this, 5.0f);
}

void func_8098AF44(EnDg* this, GlobalContext* globalCtx) {
    if (func_801A46F8() == 1) {
        this->unk_292 = 10;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_BARK);
        this->actionFunc = func_8098B004;
    }
}

void func_8098AF98(EnDg* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        func_80989140(&this->skelAnime, sAnimations, 2);
        this->actionFunc = func_8098A468;
    }

    Actor_MoveWithGravity(&this->actor);
    func_809899C8(this, 3.0f);
}

void func_8098B004(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -3.0f;
    if ((this->actor.xzDistToPlayer < 60.0f) && (this->collider.base.ocFlags1 & OC1_HIT)) {
        this->actor.shape.rot.y += 0x71C;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xC00);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->actor.xzDistToPlayer < 40.0f) {
        func_80989140(&this->skelAnime, sAnimations, 5);
        this->actionFunc = func_8098AB48;
    } else if (player->stateFlags3 & 0x20000000) {
        if ((this->actor.xzDistToPlayer > 40.0f) && (player->linearVelocity == 0.0f)) {
            Math_ApproachF(&this->actor.speedXZ, 1.5f, 0.2f, 1.0f);
        } else {
            Math_ApproachF(&this->actor.speedXZ, player->actor.speedXZ, 0.2f, 1.0f);
        }
    } else {
        Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
    }

    func_8098A064(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    func_80989974(this);
    if (!(this->unk_280 & 0x20)) {
        func_809899C8(this, 3.0f);
    }
}

void func_8098B198(EnDg* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer > 72.0f) {
        func_80989140(&this->skelAnime, sAnimations, 14);
        this->actionFunc = func_8098AC34;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x3E8, 1);
    if (this->actor.bgCheckFlags & 8) {
        this->actor.shape.rot.y = this->actor.wallYaw;
        func_80989140(&this->skelAnime, sAnimations, 14);
        this->actionFunc = func_8098AC34;
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    Math_ApproachF(&this->actor.speedXZ, -1.0f, 0.2f, 1.0f);
    Actor_MoveWithGravity(&this->actor);
    func_80989974(this);
    func_80989A9C(this, 4.0f);
}

void func_8098B28C(EnDg* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer > 200.0f) {
        func_80989140(&this->skelAnime, sAnimations, 1);
        this->actionFunc = func_8098AE58;
    } else if (this->actor.xzDistToPlayer > 150.0f) {
        func_80989140(&this->skelAnime, sAnimations, 3);
        this->actionFunc = func_8098B390;
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x3E8, 1);
        if (this->actor.bgCheckFlags & 8) {
            this->actor.shape.rot.y = this->actor.wallYaw;
        }

        this->actor.world.rot.y = this->actor.shape.rot.y;
        Math_ApproachF(&this->actor.speedXZ, -2.0f, 0.2f, 1.0f);
        Actor_MoveWithGravity(&this->actor);
    }

    func_80989974(this);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SMALL_DOG_GROAN);
}

void func_8098B390(EnDg* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 150.0f) {
        func_80989140(&this->skelAnime, sAnimations, 11);
        this->actionFunc = func_8098B28C;
    } else if (this->actor.xzDistToPlayer > 200.0f) {
        func_80989140(&this->skelAnime, sAnimations, 1);
        this->actionFunc = func_8098AE58;
    }

    func_80989A9C(this, 0.0f);
    func_80989A9C(this, 1.0f);
    func_80989A9C(this, 2.0f);
    func_80989A9C(this, 3.0f);
    func_809899C8(this, 5.0f);
}

void func_8098B464(EnDg* this, GlobalContext* globalCtx) {
    Vec3f sp2C;

    sp2C.x = this->actor.world.pos.x;
    sp2C.y = this->actor.world.pos.y + this->actor.depthInWater;
    sp2C.z = this->actor.world.pos.z + 20.0f;
    EffectSsGSplash_Spawn(globalCtx, &sp2C, NULL, NULL, 0, 800);
    EffectSsGRipple_Spawn(globalCtx, &sp2C, 100, 500, 30);
    if (this->actor.depthInWater > 0.0f) {
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = -3.0f;
        this->unk_284 = 10;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMB_DROP_WATER);
        this->actionFunc = func_8098B560;
    }

    Math_ApproachF(&this->actor.speedXZ, 1.0f, 0.2f, 1.0f);
    Actor_MoveWithGravity(&this->actor);
}

void func_8098B560(EnDg* this, GlobalContext* globalCtx) {
    Vec3f sp54;
    Vec3f pos;
    s16 sp46 = 0;
    WaterBox* waterBox;
    f32 waterSurface;
    CollisionPoly* poly;
    f32 sp34;

    sp54.x = this->actor.world.pos.x;
    sp54.y = this->actor.world.pos.y + this->actor.depthInWater;
    sp54.z = this->actor.world.pos.z + 20.0f;
    pos.x = (Math_SinS(this->actor.world.rot.y) * 50.0f) + this->actor.world.pos.x;
    pos.y = this->actor.home.pos.y + 100.0f;
    pos.z = (Math_CosS(this->actor.world.rot.y) * 50.0f) + this->actor.world.pos.z;

    if (DECR(this->unk_284) == 0) {
        if (!(this->unk_280 & 4)) {
            this->unk_280 |= 4;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OUT_OF_WATER);
        }
        this->unk_284 = 5;
        EffectSsGRipple_Spawn(globalCtx, &sp54, 100, 500, 30);
    }

    if (this->actor.depthInWater > 15.0f) {
        this->actor.velocity.y = 0.5f;
    } else if (this->actor.depthInWater < 10.0f) {
        this->actor.velocity.y = -0.5f;
    }

    sp34 = BgCheck_EntityRaycastFloor2(globalCtx, &globalCtx->colCtx, &poly, &pos);
    if (this->actor.bgCheckFlags & 8) {
        if (!WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, pos.x, pos.z, &waterSurface, &waterBox)) {
            if (sp34 > -100.0f) {
                this->unk_280 &= ~4;
                this->actionFunc = func_8098B88C;
            } else {
                sp46 = this->actor.wallYaw;
            }
        } else if (sp34 > -100.0f) {
            if (waterSurface < sp34) {
                this->unk_280 &= ~4;
                this->actionFunc = func_8098B88C;
            } else {
                sp46 = this->actor.wallYaw;
            }
        } else {
            sp46 = this->actor.wallYaw;
        }
    } else if ((this->actor.bgCheckFlags & 1) && !(this->actor.bgCheckFlags & 0x20)) {
        this->actor.gravity = -3.0f;
        this->unk_280 &= ~4;
        this->unk_28C = 8;
        this->unk_282 = Rand_S16Offset(60, 60);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OUT_OF_WATER);
        func_80989140(&this->skelAnime, sAnimations, 2);
        Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
        this->actionFunc = func_8098A468;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, sp46, 4, 0x3E8, 1);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
    Actor_MoveWithGravity(&this->actor);
}

void func_8098B88C(EnDg* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    sp34.x = this->actor.world.pos.x;
    sp34.y = this->actor.world.pos.y + this->actor.depthInWater;
    sp34.z = this->actor.world.pos.z + 20.0f;

    if (DECR(this->unk_284) == 0) {
        this->unk_284 = 5;
        EffectSsGRipple_Spawn(globalCtx, &sp34, 100, 500, 30);
    }

    if (this->actor.depthInWater > 15.0f) {
        this->actor.velocity.y = 1.0f;
    } else if (this->actor.depthInWater < 10.0f) {
        this->actor.velocity.y = -1.0f;
    }

    if (this->actor.bgCheckFlags & 8) {
        this->actor.world.pos.y = sp34.y;
        this->actor.velocity.y = 10.0f;
        EffectSsGSplash_Spawn(globalCtx, &sp34, NULL, NULL, 0, 800);
    }

    if (!(this->actor.bgCheckFlags & 0x20)) {
        this->unk_28C = 8;
        this->actor.velocity.y = 10.0f;
        this->actor.gravity = -3.0f;
        this->unk_282 = Rand_S16Offset(60, 60);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_OUT_OF_WATER);
        func_80989140(&this->skelAnime, sAnimations, 2);
        this->actionFunc = func_8098A468;
        Math_ApproachF(&this->actor.speedXZ, 3.5f, 0.2f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
    }

    Actor_MoveWithGravity(&this->actor);
}

void func_8098BA64(EnDg* this, GlobalContext* globalCtx) {
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        this->unk_290 = 2;
        this->actor.flags |= ACTOR_FLAG_1;
        if (D_8098C2A0 != 0) {
            this->actor.flags &= ~ACTOR_FLAG_8000000;
            D_8098C2A0 = 0;
            this->unk_280 &= ~1;
        }
        this->unk_288 = -1;
        D_8098C2FC.unk_02 = this->unk_288;
        this->unk_28A = 100;
        Actor_MoveWithGravity(&this->actor);
        this->unk_280 |= 0x10;
        this->actionFunc = func_8098BB10;
    }
}

void func_8098BB10(EnDg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.bgCheckFlags & 1) {
        if (this->unk_280 & 0x10) {
            this->unk_280 &= ~0x10;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONKEY_WALK);
        }

        this->actor.speedXZ = 0.0f;
        this->actor.gravity = -3.0f;
        if (player->transformation == PLAYER_FORM_HUMAN) {
            func_80989E18(this, globalCtx);
        }
    }

    if (DECR(this->unk_28A) == 0) {
        this->unk_290 = 0;
        func_80989ADC(this, globalCtx);
        this->actionFunc = func_8098A468;
    }

    Actor_MoveWithGravity(&this->actor);
}

void func_8098BBEC(EnDg* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80989D38(this, globalCtx);
        this->actionFunc = func_8098BC54;
    } else {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_8098BC54(EnDg* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 2) {
        func_80989140(&this->skelAnime, sAnimations, 0);
        this->actionFunc = func_8098BA64;
    }
}

void EnDg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDg* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gDogSkel, NULL, this->jointTable, this->morphTable, DOG_LIMB_MAX);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk_1DC = SubS_GetPathByIndex(globalCtx, ENDG_GET_FC00(&this->actor), 0x3F);
    Actor_SetScale(&this->actor, 0.0075f);
    this->actor.targetMode = 1;
    this->actor.gravity = -3.0f;
    this->unk_282 = Rand_S16Offset(60, 60);
    this->unk_280 = 0;
    this->unk_28E = 20;
    this->unk_284 = 10;
    this->unk_286 = ENDG_GET_3E0(&this->actor);
    this->unk_28C = 0;
    this->unk_290 = 0;
    if (globalCtx->sceneNum == SCENE_F01_B) {
        this->unk_28A = 100;
        func_80989BF8(this);
    }
    func_80989ADC(this, globalCtx);
}

void EnDg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDg* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    Vec3f sp28 = { 0.0f, 0.0f, 0.0f };

    this->unk_288 = D_8098C2FC.unk_02;
    if (!(player->stateFlags1 & 0x20) || (globalCtx->sceneNum != SCENE_CLOCKTOWER)) {
        if (func_8098A1B4(this, globalCtx)) {
            func_8098A234(this, globalCtx);
        } else if (this->unk_28C != 8) {
            this->unk_28C = 8;
            func_80989ADC(this, globalCtx);
        }

        if ((this->actor.bgCheckFlags & 0x40) && Actor_HasNoParent(&this->actor, globalCtx)) {
            func_80989140(&this->skelAnime, sAnimations, 15);
            this->actionFunc = func_8098B464;
        }

        this->actionFunc(this, globalCtx);
        func_80989204(this, globalCtx);
        func_8098933C(this, &sp28);
        Math_ApproachF(&this->unk_294.x, sp28.x, 0.2f, 0.1f);
        Math_ApproachF(&this->unk_294.z, sp28.z, 0.2f, 0.1f);
        SkelAnime_Update(&this->skelAnime);
    }
}

s32 EnDg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void EnDg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDg* this = THIS;
    Vec3f sp20 = { 0.0f, 20.0f, 0.0f };

    if (limbIndex == DOG_LIMB_HEAD) {
        if (this->actionFunc == func_8098BBEC) {
            sp20.x = 5000.0f;
            Matrix_MultiplyVector3fByState(&sp20, &this->actor.focus.pos);
        } else if (this->actionFunc != func_8098BC54) {
            Matrix_MultiplyVector3fByState(&sp20, &this->actor.focus.pos);
        }
    }
}

void EnDg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    switch (D_8098C2A8[this->unk_286].unk_00) {
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
    Matrix_RotateStateAroundXAxis(this->unk_294.x);
    Matrix_InsertZRotation_f(this->unk_294.z, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDg_OverrideLimbDraw, EnDg_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
