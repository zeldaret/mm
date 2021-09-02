/*
 * File: z_en_railgibud.c
 * Overlay: ovl_En_Railgibud
 * Description: Music Box House - Patrolling Gibdos
 */

#include "z_en_railgibud.h"

#define FLAGS 0x00000415

#define THIS ((EnRailgibud*)thisx)

void EnRailgibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRailgibud_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BA57A8(EnRailgibud* this);
void func_80BA57F8(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA59F0(EnRailgibud* this);
void func_80BA5A34(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA5AF0(EnRailgibud* this);
void func_80BA5B64(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA5DBC(EnRailgibud* this);
void func_80BA5E18(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA6054(EnRailgibud* this);
void func_80BA60B0(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA6158(EnRailgibud* this);
void func_80BA61A0(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA6284(EnRailgibud* this);
void func_80BA62D4(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA64AC(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA6604(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA6664(EnRailgibud* this);
void func_80BA66C8(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA6974(GlobalContext* globalCtx, Vec3f* vec, f32 arg2, s32 arg3, s16 arg4, s16 arg5);
void func_80BA6B9C(EnRailgibud* this, GlobalContext* globalCtx);
s32 func_80BA6D10(EnRailgibud* this, GlobalContext* globalCtx);
s32 func_80BA6DAC(EnRailgibud* this, GlobalContext* globalCtx);
s32 func_80BA7088(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA7578(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA7878(Actor* thisx, GlobalContext* globalCtx);
void func_80BA7B6C(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA7C78(EnRailgibud* this);
void func_80BA7CF0(EnRailgibud* this);
void func_80BA7D04(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA7D30(EnRailgibud* this, GlobalContext* globalCtx);
void func_80BA8050(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_060009C4;
extern AnimationHeader D_06000F1C;
extern AnimationHeader D_06001600;
extern FlexSkeletonHeader D_060053E8;
extern AnimationHeader D_06005DF4;
extern AnimationHeader D_060061E4;
extern AnimationHeader D_06006678;
extern AnimationHeader D_06006B08;
extern AnimationHeader D_06006EEC;
extern AnimationHeader D_060073A4;
extern AnimationHeader D_06007BBC;
extern AnimationHeader D_060081A8;
extern AnimationHeader D_06009298;
extern AnimationHeader D_06009900;
extern AnimationHeader D_0600A450;
extern AnimationHeader D_0600ABE0;
extern FlexSkeletonHeader D_06010B88;
extern AnimationHeader D_060113EC;
extern AnimationHeader D_060118D8;
extern AnimationHeader D_06011DB8;
extern AnimationHeader D_0601216C;

const ActorInit En_Railgibud_InitVars = {
    ACTOR_EN_RAILGIBUD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRailgibud),
    (ActorFunc)EnRailgibud_Init,
    (ActorFunc)EnRailgibud_Destroy,
    (ActorFunc)EnRailgibud_Update,
    (ActorFunc)EnRailgibud_Draw,
};

static ActorAnimationEntry sAnimations[] = {
    { &D_06006678, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06006B08, 0.5f, 0.0f, 0.0f, 3, 0.0f },
    { &D_06006EEC, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_060073A4, 0.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_06007BBC, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_060081A8, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_06009298, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_06009900, 1.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_0600A450, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_0600ABE0, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060113EC, 0.4f, 0.0f, 0.0f, 1, -8.0f }, { &D_0601216C, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060118D8, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06011DB8, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_0600A450, 3.0f, 0.0f, 0.0f, 2, -6.0f }, { &D_06005DF4, 1.0f, 0.0f, 0.0f, 2, -8.0f },
    { &D_060061E4, 1.0f, 0.0f, 0.0f, 0, -8.0f }, { &D_06001600, 1.0f, 0.0f, 0.0f, 0, -8.0f },
    { &D_060009C4, 1.0f, 0.0f, 0.0f, 2, -8.0f }, { &D_06000F1C, 1.0f, 0.0f, 0.0f, 0, -8.0f },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7EFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xD),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0xD),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xC),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 8, 0, 0, 0, MASS_IMMOVABLE };

void func_80BA5400(EnRailgibud* this, GlobalContext* globalCtx) {
    static s32 D_80BA82F8 = 0;
    s32 phi_a3;
    Vec3f sp70;
    Path* path = &globalCtx->setupPathList[ENRAILGIBUD_GET_FF00(&this->actor)];

    this->unk_294 = Lib_SegmentedToVirtual(path->points);
    this->unk_298 = D_80BA82F8;
    this->unk_29C = path->count;
    if (D_80BA82F8 == 0) {
        s32 i;

        for (i = 1; i < this->unk_29C && i < 10; i++) {
            D_80BA82F8++;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_RAILGIBUD, 0.0f, 0.0f, 0.0f, 0,
                               0, 0, this->actor.params);
        }
        D_80BA82F8 = 0;
    }

    this->actor.world.pos.x = this->unk_294[this->unk_298].x;
    this->actor.world.pos.y = this->unk_294[this->unk_298].y;
    this->actor.world.pos.z = this->unk_294[this->unk_298].z;
    if (this->unk_298 < (this->unk_29C - 1)) {
        phi_a3 = this->unk_298 + 1;
    } else {
        phi_a3 = 0;
    }

    sp70.x = this->unk_294[phi_a3].x;
    sp70.y = this->unk_294[phi_a3].y;
    sp70.z = this->unk_294[phi_a3].z;
    this->actor.world.rot.y = this->actor.shape.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &sp70);

    this->actor.home = this->actor.world;
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

void EnRailgibud_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRailgibud* this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.targetMode = 0;
    this->actor.hintId = 0x2D;
    this->actor.textId = 0;
    if (ENRAILGIBUD_GET_80(&this->actor)) {
        func_80BA7B6C(this, globalCtx);
        return;
    }

    func_80BA5400(this, globalCtx);
    this->unk_3F2 = 0;
    this->unk_402 = gSaveContext.time;
    this->unk_404 = 0;
    this->unk_3F8 = 0;
    this->unk_400 = 0;
    this->unk_3FA = 0;
    if (this->actor.parent == NULL) {
        this->unk_3EC = 1;
        this->unk_3EE = 1;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 28.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060053E8, &D_0600ABE0, this->jointTable, this->morphTable, 26);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    if (gSaveContext.weekEventReg[14] & 4) {
        Actor_MarkForDeath(&this->actor);
    }

    func_80BA57A8(this);
}

void EnRailgibud_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRailgibud* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BA57A8(EnRailgibud* this) {
    this->actor.speedXZ = 0.6f;
    func_800BDC5C(&this->skelAnime, sAnimations, 10);
    this->actionFunc = func_80BA57F8;
}

void func_80BA57F8(EnRailgibud* this, GlobalContext* globalCtx) {
    Vec3f sp3C;
    s32 pad;
    s16 sp36;

    sp3C.x = this->unk_294[this->unk_298].x;
    sp3C.y = this->unk_294[this->unk_298].y;
    sp3C.z = this->unk_294[this->unk_298].z;

    if ((this->actor.xzDistToPlayer <= 100.0f) && func_800B715C(globalCtx) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_GIBDO_MASK)) {
        this->actor.home = this->actor.world;
        func_80BA59F0(this);
    }

    Math_SmoothStepToS(&this->unk_3E2, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->unk_3E8, 0, 1, 0x64, 0);

    if (this->actor.parent == NULL) {
        if (this->unk_3EC != 0) {
        } else {
            return;
        }
    } else {
        EnRailgibud* parent = (EnRailgibud*)this->actor.parent;

        if (parent->unk_3EC == 0) {
            return;
        }
    }

    sp36 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp3C);
    if (Math_Vec3f_DistXZ(&this->actor.world.pos, &sp3C) > 60.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, sp36, 1, 0x190, 0xA);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    } else if (this->unk_298 < (this->unk_29C - 1)) {
        this->unk_298++;
    } else {
        this->unk_298 = 0;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80BA59F0(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 9);
    this->actionFunc = func_80BA5A34;
}

void func_80BA5A34(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 rot = this->actor.shape.rot.y + this->unk_3E2 + this->unk_3E8;
    s16 yaw = BINANG_SUB(this->actor.yawTowardsPlayer, rot);

    if (ABS_ALT(yaw) < 0x2008) {
        player->actor.freezeTimer = 60;
        func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
        func_80123E90(globalCtx, &this->actor);
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
        func_80BA5AF0(this);
    }
    func_80BA6B9C(this, globalCtx);
}

void func_80BA5AF0(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 10);
    this->actor.speedXZ = 0.4f;
    if (this->actionFunc == func_80BA5A34) {
        this->unk_3F2 = 80;
    } else {
        this->unk_3F2 = 20;
    }
    this->actionFunc = func_80BA5B64;
}

void func_80BA5B64(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 pad;

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xFA);
    this->actor.world.rot = this->actor.shape.rot;
    Math_SmoothStepToS(&this->unk_3E2, 0, 1, 0x64, 0);
    Math_SmoothStepToS(&this->unk_3E8, 0, 1, 0x64, 0);
    if (func_80BA6D10(this, globalCtx) && Actor_IsActorFacingLink(&this->actor, 0x38E3)) {
        if ((this->unk_3F4 == 0) && (this->actor.xzDistToPlayer <= 45.0f)) {
            player->actor.freezeTimer = 0;
            if ((gSaveContext.playerForm == PLAYER_FORM_GORON) || (gSaveContext.playerForm == PLAYER_FORM_DEKU)) {
                func_80BA6054(this);
            } else if (globalCtx->grabPlayer(globalCtx, player)) {
                func_80BA5DBC(this);
            }
        } else {
            if (this->unk_3F2 == 0) {
                player->actor.freezeTimer = 40;
                this->unk_3F2 = 60;
                func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
                func_80123E90(globalCtx, &this->actor);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
            } else {
                this->unk_3F2--;
            }
        }
    } else if ((this->unk_3F4 == 0) && (this->actor.xzDistToPlayer <= 45.0f)) {
        func_80BA6284(this);
    } else if (func_80BA6DAC(this, globalCtx)) {
        func_80BA6284(this);
    }

    if (this->unk_3F4 > 0) {
        this->unk_3F4--;
    }

    if (func_801378B8(&this->skelAnime, 10.0f) || func_801378B8(&this->skelAnime, 22.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 95) == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_80BA5DBC(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 2);
    this->actor.flags &= ~1;
    this->unk_3F2 = 0;
    this->unk_3F0 = 0;
    this->actionFunc = func_80BA5E18;
}

void func_80BA5E18(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player2 = PLAYER;
    Player* player = player2;
    s32 sp34;
    u16 sp32;

    switch (this->unk_3F0) {
        case 0:
            sp34 = func_80BA7088(this, globalCtx);
            if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) && (sp34 == 1)) {
                this->unk_3F0 = 1;
                func_800BDC5C(&this->skelAnime, sAnimations, 0);
            } else if (!(player->stateFlags2 & 0x80)) {
                func_800BDC5C(&this->skelAnime, sAnimations, 1);
                this->actor.flags |= 1;
                this->unk_3F0 = 2;
                this->unk_3F2 = 0;
            }
            break;

        case 1:
            if (this->unk_3F2 == 20) {
                sp32 = player->ageProperties->unk_92 + 0x6805;
                globalCtx->damagePlayer(globalCtx, -8);
                func_800B8E58(&player->actor, sp32);
                func_8013ECE0(this->actor.xzDistToPlayer, 240, 1, 12);
                this->unk_3F2 = 0;
            label:;
            } else {
                this->unk_3F2++;
            }

            if (func_801378B8(&this->skelAnime, 0.0f)) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_ATTACK);
            }

            if (!(player->stateFlags2 & 0x80) || (player->unk_B62 != 0)) {
                if ((player->unk_B62 != 0) && (player->stateFlags2 & 0x80)) {
                    player->stateFlags2 &= ~0x80;
                    player->unk_AE8 = 100;
                }
                func_800BDC5C(&this->skelAnime, sAnimations, 1);
                this->actor.flags |= 1;
                this->unk_3F0 = 2;
                this->unk_3F2 = 0;
            }
            break;

        case 2:
            if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
                this->unk_3F4 = 40;
                this->actor.shape.yOffset = 0.0f;
                func_80BA5AF0(this);
            } else {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            break;
    }
}

void func_80BA6054(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 7);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->actor.speedXZ = -2.0f;
    this->actionFunc = func_80BA60B0;
}

void func_80BA60B0(EnRailgibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->unk_3E2, 0, 1, 0x12C, 0);
    Math_SmoothStepToS(&this->unk_3E8, 0, 1, 0x12C, 0);
    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80BA6158(this);
    }
}

void func_80BA6158(EnRailgibud* this) {
    this->unk_3F2 = 0;
    func_800BDC5C(&this->skelAnime, sAnimations, 10);
    this->actionFunc = func_80BA61A0;
}

void func_80BA61A0(EnRailgibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 5, 3500, 200);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->unk_3F2 > 60) {
        func_80BA6284(this);
        this->unk_3F2 = 0;
    } else {
        this->unk_3E2 = Math_SinS(this->unk_3F2 * 0xFA0) * (0x256F * ((60 - this->unk_3F2) / 60.0f));
        this->unk_3F2++;
    }
}

void func_80BA6284(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 10);
    this->actor.speedXZ = 0.4f;
    this->actionFunc = func_80BA62D4;
}

void func_80BA62D4(EnRailgibud* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->unk_3E2, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3E8, 0, 1, 100, 0);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) < 5.0f) {
        if (this->actor.speedXZ > 0.2f) {
            this->actor.speedXZ -= 0.2f;
        } else {
            this->actor.speedXZ = 0.0f;
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 200, 10);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.world.rot.y == this->actor.home.rot.y) {
            func_80BA57A8(this);
        }
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 450);
        this->actor.world.rot = this->actor.shape.rot;
    }
    if (func_80BA6D10(this, globalCtx)) {
        if ((gSaveContext.playerForm != PLAYER_FORM_GORON) && (gSaveContext.playerForm != PLAYER_FORM_DEKU) &&
            Actor_IsActorFacingLink(&this->actor, 0x38E3)) {
            func_80BA5AF0(this);
        }
    }
}

void func_80BA6440(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 7);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->unk_3F2 = 0;
    this->unk_3F4 = 0;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.speedXZ = -2.0f;
    this->actionFunc = func_80BA64AC;
}

void func_80BA64AC(EnRailgibud* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
        this->unk_405 = -1;
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if ((this->unk_3F6 > 0) && (this->unk_404 == 0) && (this->unk_3F8 == 0)) {
            this->actor.hintId = 0x2A;
            SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06010B88, NULL, this->jointTable, this->morphTable, 26);
            this->unk_3F8 = 1;
        }
        func_80BA6284(this);
    }
}

void func_80BA6584(EnRailgibud* this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk_3F2 = 10;
    if (this->unk_3F6 != 0) {
        func_800BCB70(&this->actor, 0, 0xC8, 0, 0x28);
    } else {
        func_800BCB70(&this->actor, 0, 0xC8, 0, 0x28);
    }
    this->actionFunc = func_80BA6604;
}

void func_80BA6604(EnRailgibud* this, GlobalContext* globalCtx) {
    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_80BA6664(this);
        } else {
            func_80BA6440(this);
        }
    }

    if (this->unk_3F2 != 0) {
        this->unk_3F2--;
    }
}

void func_80BA6664(EnRailgibud* this) {
    func_800BDC5C(&this->skelAnime, sAnimations, 6);
    this->actor.flags &= ~1;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_DEAD);
    this->unk_3F2 = 0;
    this->actionFunc = func_80BA66C8;
}

void func_80BA66C8(EnRailgibud* this, GlobalContext* globalCtx) {
    if (this->unk_3F2 > 300) {
        if (this->actor.shape.shadowAlpha == 0) {
            if (this->actor.parent != NULL) {
                Actor_MarkForDeath(&this->actor);
            } else {
                this->actor.draw = NULL;
                this->actor.flags &= ~1;
                this->actor.update = func_80BA7878;
            }
        } else {
            this->actor.shape.shadowAlpha -= 5;
            if (this->actor.shape.shadowAlpha < 5) {
                this->actor.shape.shadowAlpha = 0;
            }
        }
    } else {
        Math_SmoothStepToS(&this->unk_3E2, 0, 1, 250, 0);
        Math_SmoothStepToS(&this->unk_3E8, 0, 1, 250, 0);
        this->unk_3F2++;
    }

    if ((this->unk_3F2 == 20) && (this->unk_3F6 > 0) && (this->unk_404 == 0) && (this->unk_3F8 == 0)) {
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06010B88, NULL, this->jointTable, this->morphTable, 26);
        this->unk_3F8 = 1;
    }
}

void func_80BA6800(EnRailgibud* this, GlobalContext* globalCtx, s32 arg2) {
    Vec3f sp5C = this->actor.world.pos;
    Vec3f sp50 = { 0.0f, 8.0f, 0.0f };
    Vec3f sp44 = { 0.0f, -1.5f, 0.0f };
    s16 rand;
    s32 pad;

    if ((globalCtx->gameplayFrames & arg2) == 0) {
        rand = Rand_Next();
        sp5C.x += 15.0f * Math_SinS(rand);
        sp5C.z += 15.0f * Math_CosS(rand);
        sp44.x = Rand_Centered();
        sp44.z = Rand_Centered();
        sp50.y += Rand_Centered() * 4.0f;
        EffectSsHahen_Spawn(globalCtx, &sp5C, &sp50, &sp44, 0, (Rand_Next() & 7) + 10, -1, 10, NULL);
        func_80BA6974(globalCtx, &sp5C, 10.0f, 10, 150, 0);
    }
}

void func_80BA6974(GlobalContext* globalCtx, Vec3f* vec, f32 arg2, s32 arg3, s16 arg4, s16 arg5) {
    Vec3f sp8C;
    Vec3f sp80 = { 0.0f, 0.3f, 0.0f };
    Vec3f sp74 = D_801D15B0;
    s32 i;
    s32 pad;

    sp74.y = 2.5f;

    for (i = arg3; i >= 0; i--) {
        sp74.x = (Rand_ZeroOne() - 0.5f) * arg2;
        sp74.z = (Rand_ZeroOne() - 0.5f) * arg2;

        sp8C.x = vec->x + sp74.x;
        sp8C.y = ((Rand_ZeroOne() - 0.5f) * arg2) + vec->y;
        sp8C.z = vec->z + sp74.z;

        sp74.x *= 0.5f;
        sp74.z *= 0.5f;
        func_800B1210(globalCtx, &sp8C, &sp74, &sp80, (s16)(Rand_ZeroOne() * arg4 * 0.2f) + arg4, arg5);
    }
}

void func_80BA6B30(EnRailgibud* this) {
    if (this->actor.parent == NULL) {
        this->unk_3EC = this->unk_3EE;
        this->unk_3EE = 1;
        if ((this->actionFunc != func_80BA57F8) && (this->actionFunc != func_80BA66C8)) {
            this->unk_3EE = 0;
        }
    } else if ((this->actionFunc != func_80BA57F8) && (this->actionFunc != func_80BA66C8)) {
        ((EnRailgibud*)this->actor.parent)->unk_3EE = 0;
    }
}

void func_80BA6B9C(EnRailgibud* this, GlobalContext* globalCtx) {
    s16 temp_v0 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_3E8;
    s16 phi_a2 = CLAMP(temp_v0, -500, 500);

    temp_v0 -= this->unk_3E2;
    temp_v0 = CLAMP(temp_v0, -500, 500);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->unk_3E8 += ABS_ALT(phi_a2);
        this->unk_3E2 += ABS_ALT(temp_v0);
    } else {
        this->unk_3E8 -= ABS_ALT(phi_a2);
        this->unk_3E2 -= ABS_ALT(temp_v0);
    }

    this->unk_3E8 = CLAMP(this->unk_3E8, -0x495F, 0x495F);
    this->unk_3E2 = CLAMP(this->unk_3E2, -0x256F, 0x256F);
}

s32 func_80BA6D10(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO_MASK) {
        return false;
    }

    if ((Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) < 100.0f) && !(player->stateFlags1 & 0x2C6080) &&
        !(player->stateFlags2 & 0x4080)) {
        return true;
    }

    return false;
}

s32 func_80BA6DAC(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 100.0f) {
        return true;
    }

    return false;
}

void func_80BA6DF8(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((this->unk_3FA != 1) && (this->collider.base.acFlags & AC_HIT)) {
        if (this->actionFunc == func_80BA57F8) {
            this->actor.home = this->actor.world;
        }
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_ApplyDamage(&this->actor);

        switch (this->actor.colChkInfo.damageEffect) {
            case 15:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (player->unk_ADC != 0) {
                    this->unk_405 = player->unk_ADD;
                }
                this->actor.shape.yOffset = 0.0f;
                if (this->actor.colChkInfo.health == 0) {
                    func_80BA6664(this);
                } else {
                    func_80BA6440(this);
                }
                break;

            case 14:
                if (this->unk_3F8 == 1) {
                    this->actor.colChkInfo.health = 0;
                    this->actor.shape.yOffset = 0.0f;
                    func_80BA6664(this);
                }
                break;

            case 2:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    func_80BA6664(this);
                } else {
                    func_80BA6440(this);
                }
                this->unk_404 = 0;
                this->unk_3F6 = 180;
                this->unk_2A0 = 1.0f;
                break;

            case 4:
                func_800BCB70(&this->actor, 0x4000, 255, 0, 8);
                if (this->actor.colChkInfo.health == 0) {
                    func_80BA6664(this);
                } else {
                    func_80BA6440(this);
                }
                this->unk_404 = 20;
                this->unk_3F6 = 60;
                this->unk_2A0 = 1.0f;
                break;

            case 12:
                if ((this->actionFunc != func_80BA5E18) &&
                    ((this->actionFunc != func_80BA6604) || (this->unk_3F2 == 0))) {
                    this->unk_404 = 30;
                    this->unk_3F6 = 40;
                    this->unk_2A0 = 1.0f;
                    func_80BA6584(this);
                }
                break;

            case 1:
                if ((this->actionFunc != func_80BA6604) || (this->unk_3F2 == 0)) {
                    func_80BA6584(this);
                }
                break;
        }
    }
}

s32 func_80BA7088(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp40;
    f32 sp3C;
    f32 sp38 = 0.0f;
    s16 temp_s0_2;

    sp40 = player->actor.world.pos;

    sp40.x -= 25.0f * Math_SinS(player->actor.shape.rot.y);
    sp40.z -= 25.0f * Math_CosS(player->actor.shape.rot.y);
    sp3C = Math_Vec3f_StepTo(&this->actor.world.pos, &sp40, 10.0f);
    temp_s0_2 = Math_SmoothStepToS(&this->actor.shape.rot.y, player->actor.shape.rot.y, 1, 0x1770, 0x64);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (gSaveContext.playerForm == PLAYER_FORM_HUMAN) {
        sp38 = Math_SmoothStepToF(&this->actor.shape.yOffset, -1500.0f, 1.0f, 150.0f, 0.0f);
    }

    if ((sp3C == 0.0f) && (ABS_ALT(temp_s0_2) < 100) && (sp38 == 0.0f)) {
        return true;
    }

    return false;
}

void func_80BA71E4(EnRailgibud* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80BA5B64) || (this->actionFunc == func_80BA62D4) ||
        (this->actionFunc == func_80BA64AC)) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
}

void func_80BA7234(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp30;

    if ((this->actionFunc == func_80BA5E18) && (this->unk_3F0 != 2)) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 35.0f, 1);
    } else {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 35.0f, 0x1D);
    }

    if ((this->actionFunc == func_80BA5E18) && (this->unk_3F0 == 0) && (this->actor.bgCheckFlags & 8)) {
        sp30 = player->actor.world.pos;
        sp30.x += 10.0f * Math_SinS(this->actor.wallYaw);
        sp30.z += 10.0f * Math_CosS(this->actor.wallYaw);
        Math_Vec3f_StepTo(&player->actor.world.pos, &sp30, 5.0f);
    }
}

void func_80BA7388(EnRailgibud* this, GlobalContext* globalCtx) {
    if (this->unk_3F6 > 0) {
        this->unk_3F6--;
    }

    if (this->unk_3F6 < 20) {
        Math_SmoothStepToF(&this->unk_2A4, 0.0f, 0.5f, 0.03f, 0.0f);
        this->unk_2A0 = this->unk_3F6 * 0.05f;
    } else {
        Math_SmoothStepToF(&this->unk_2A4, 0.5f, 0.1f, 0.02f, 0.0f);
    }
}

void func_80BA7434(EnRailgibud* this, GlobalContext* globalCtx) {
    if ((this->actionFunc != func_80BA5E18) && (this->actionFunc != func_80BA64AC) &&
        (this->actionFunc != func_80BA60B0) && (this->actionFunc != func_80BA61A0) &&
        (this->actionFunc != func_80BA66C8)) {
        if ((this->actor.flags & 5) == 5) {
            if (Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO_MASK) {
                this->actor.flags &= ~5;
                this->actor.flags |= 9;
                this->actor.hintId = 0xFF;
                this->actor.textId = 0;
                if ((this->actionFunc != func_80BA57F8) && (this->actionFunc != func_80BA62D4)) {
                    func_80BA6284(this);
                }
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_GIBDO_MASK) {
            this->actor.flags &= ~(0x8 | 0x1);
            this->actor.flags |= (0x4 | 0x1);
            if (this->unk_3F8 == 1) {
                this->actor.hintId = 0x2A;
            } else {
                this->actor.hintId = 0x2D;
            }
            this->actor.textId = 0;
        }
        func_80BA7578(this, globalCtx);
    }
}

void func_80BA7578(EnRailgibud* this, GlobalContext* globalCtx) {
    if ((this->unk_400 == 0) && (this->unk_3F8 == 0)) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            this->unk_3FA = 1;
            func_801518B0(globalCtx, 0x13B2, &this->actor);
            this->unk_400 = 0x13B2;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
            this->actor.speedXZ = 0.0f;
        } else if (((this->actor.flags & 9) == 9) && !(this->collider.base.acFlags & AC_HIT)) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    } else {
        switch (func_80152498(&globalCtx->msgCtx)) {
            case 5:
                if (func_80147624(globalCtx)) {
                    func_801518B0(globalCtx, 0x13B3, &this->actor);
                    this->unk_400 = 0x13B3;
                }
                break;

            case 6:
                if (func_80147624(globalCtx)) {
                    this->unk_400 = 0;
                    this->unk_3FA = 0;
                    this->actor.speedXZ = 0.6f;
                }
                break;

            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                break;
        }
    }
}

void func_80BA76C4(EnRailgibud* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((this->actionFunc != func_80BA66C8) && ((this->actionFunc != func_80BA5E18) || (this->unk_3F0 == 2))) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (((this->actionFunc != func_80BA64AC) || ((player->unk_ADC != 0) && (player->unk_ADD != this->unk_405))) &&
            ((this->actionFunc != func_80BA6604) || (this->unk_3F2 == 0))) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void EnRailgibud_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRailgibud* this = THIS;

    func_80BA6B30(this);
    func_80BA7434(this, globalCtx);
    func_80BA6DF8(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->actionFunc != func_80BA6604) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }
    func_80BA71E4(this, globalCtx);
    func_80BA76C4(this, globalCtx);
    func_80BA7234(this, globalCtx);
    func_80BA7388(this, globalCtx);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
}

void func_80BA7878(Actor* thisx, GlobalContext* globalCtx) {
    EnRailgibud* this = THIS;

    func_80BA6B30(this);
}

s32 EnRailgibud_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx, Gfx** gfx) {
    EnRailgibud* this = THIS;

    if (limbIndex == 12) {
        rot->y += this->unk_3E8;
    } else if (limbIndex == 23) {
        rot->y += this->unk_3E2;
    }

    return false;
}

void EnRailgibud_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    EnRailgibud* this = THIS;

    if ((this->unk_3F6 != 0) &&
        ((limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 8) || (limbIndex == 9) ||
         (limbIndex == 11) || (limbIndex == 14) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
         (limbIndex == 20) || (limbIndex == 21) || (limbIndex == 22) || (limbIndex == 24) || (limbIndex == 25))) {
        SysMatrix_GetStateTranslation(&this->unk_1D8[this->unk_28C]);
        this->unk_28C++;
    }
}

void EnRailgibud_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRailgibud* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    this->unk_28C = 0;
    if (this->actor.shape.shadowAlpha == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->actor.shape.shadowAlpha);
        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);

        POLY_OPA_DISP = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                          this->skelAnime.dListCount, EnRailgibud_OverrideLimbDraw,
                                          EnRailgibud_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->actor.shape.shadowAlpha);
        gSPSegment(POLY_XLU_DISP++, 0x08, D_801AEF88);

        POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                          this->skelAnime.dListCount, EnRailgibud_OverrideLimbDraw,
                                          EnRailgibud_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    }

    if (this->unk_3F6 > 0) {
        func_800BE680(globalCtx, &this->actor, this->unk_1D8, ARRAY_COUNT(this->unk_1D8), this->unk_2A4, 0.5f,
                      this->unk_2A0, this->unk_404);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80BA7B6C(EnRailgibud* this, GlobalContext* globalCtx) {
    s32 pad[2];

    func_80BA7C78(this);
    this->unk_3FE = 99;
    this->actor.flags |= 0x100000;
    this->actor.flags |= 0x10;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 28.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060053E8, &D_0600ABE0, this->jointTable, this->morphTable, 26);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    if (gSaveContext.entranceIndex != 0x2090) { // NOT Cutscene: Music Box House Opens
        Actor_MarkForDeath(&this->actor);
    }
    func_80BA7CF0(this);
    this->actor.update = func_80BA8050;
}

void func_80BA7C78(EnRailgibud* this) {
    switch (ENRAILGIBUD_GET_7F(&this->actor)) {
        case 1:
            this->unk_3FC = 0x207;
            break;

        case 2:
            this->unk_3FC = 0x208;
            break;

        case 3:
            this->unk_3FC = 0x209;
            break;

        case 4:
            this->unk_3FC = 0x20A;
            break;

        case 5:
            this->unk_3FC = 0x20B;
            break;

        default:
            this->unk_3FC = 0x207;
            break;
    }
}

void func_80BA7CF0(EnRailgibud* this) {
    this->actionFunc = func_80BA7D04;
}

void func_80BA7D04(EnRailgibud* this, GlobalContext* globalCtx) {
}

void func_80BA7D14(EnRailgibud* this) {
    this->unk_3F2 = 30;
    this->actionFunc = func_80BA7D30;
}

void func_80BA7D30(EnRailgibud* this, GlobalContext* globalCtx) {
    if (this->unk_3F2 != 0) {
        this->unk_3F2--;
    } else if (Math_SmoothStepToF(&this->actor.shape.yOffset, -9500.0f, 0.5f, 200.0f, 10.0f) < 10.0f) {
        Actor_MarkForDeath(&this->actor);
    } else {
        func_80BA6800(this, globalCtx, 0);
    }
}

s32 func_80BA7DC8(EnRailgibud* this, GlobalContext* globalCtx) {
    u32 sp2C;

    if (func_800EE29C(globalCtx, this->unk_3FC)) {
        sp2C = func_800EE200(globalCtx, this->unk_3FC);
        if (this->unk_3FE != globalCtx->csCtx.npcActions[sp2C]->unk0) {
            this->unk_3FE = globalCtx->csCtx.npcActions[sp2C]->unk0;
            switch (globalCtx->csCtx.npcActions[sp2C]->unk0) {
                case 1:
                    this->unk_3F0 = 9;
                    func_800BDC5C(&this->skelAnime, sAnimations, 9);
                    break;

                case 2:
                    this->unk_3F0 = 15;
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_WEAKENED2);
                    func_800BDC5C(&this->skelAnime, sAnimations, 15);
                    break;

                case 3:
                    this->unk_3F0 = 17;
                    func_800BDC5C(&this->skelAnime, sAnimations, 17);
                    break;

                case 4:
                    this->unk_3F0 = 18;
                    func_800BDC5C(&this->skelAnime, sAnimations, 18);
                    break;

                case 5:
                    this->unk_3F0 = 10;
                    func_800BDC5C(&this->skelAnime, sAnimations, 10);
                    break;
            }
        } else if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            if (this->unk_3F0 == 15) {
                this->unk_3F0 = 16;
                func_800BDC5C(&this->skelAnime, sAnimations, 16);
            } else if (this->unk_3F0 == 18) {
                this->unk_3F0 = 19;
                func_800BDC5C(&this->skelAnime, sAnimations, 19);
                func_80BA7D14(this);
            }
        }

        switch (this->unk_3FE) {
            case 3:
            case 4:
                if (this->actionFunc == func_80BA7D30) {
                    func_800B9010(&this->actor, NA_SE_EN_REDEAD_WEAKENED_L2 - SFX_FLAG);
                } else {
                    func_800B9010(&this->actor, NA_SE_EN_REDEAD_WEAKENED_L1 - SFX_FLAG);
                }
                break;

            case 5:
                if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
                    if (globalCtx->csCtx.frames < 280) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_CRY);
                    } else {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_WEAKENED1);
                    }
                }
                break;
        }

        func_800EDF24(&this->actor, globalCtx, sp2C);
        return true;
    }

    this->unk_3FE = 99;
    return false;
}

void func_80BA8050(Actor* thisx, GlobalContext* globalCtx) {
    EnRailgibud* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80BA7DC8(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}
