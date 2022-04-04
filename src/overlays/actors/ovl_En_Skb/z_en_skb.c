/*
 * File: z_en_skb.c
 * Overlay: ovl_En_Skb
 * Description: Stalchild
 */

#include "z_en_skb.h"
#include "overlays/effects/ovl_Effect_Ss_Hahen/z_eff_ss_hahen.h"
#include "overlays/actors/ovl_En_Encount4/z_en_encount4.h"
#include "objects/object_skb/object_skb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnSkb*)thisx)

void EnSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80994E2C(EnSkb* this);
void func_80994E94(EnSkb* this, GlobalContext* globalCtx);
void func_80995068(EnSkb* this, GlobalContext* globalCtx);
void func_80995190(EnSkb* this, GlobalContext* globalCtx);
void func_80995244(EnSkb* this, GlobalContext* globalCtx);
void func_809952D8(EnSkb* this);
void func_8099533C(EnSkb* this, GlobalContext* globalCtx);
void func_809953E8(EnSkb* this);
void func_8099544C(EnSkb* this, GlobalContext* globalCtx);
void func_809954F8(EnSkb* this);
void func_8099556C(EnSkb* this, GlobalContext* globalCtx);
void func_8099571C(EnSkb* this);
void func_80995818(EnSkb* this, GlobalContext* globalCtx);
void func_8099599C(EnSkb* this, GlobalContext* globalCtx);
void func_80995A30(EnSkb* this);
void func_80995A8C(EnSkb* this, GlobalContext* globalCtx);
void func_80995C24(EnSkb* this);
void func_80995C84(EnSkb* this, GlobalContext* globalCtx);
void func_80995D3C(EnSkb* this);
void func_80995DC4(EnSkb* this, GlobalContext* globalCtx);
void func_80995E64(EnSkb* this, GlobalContext* globalCtx);
void func_809960AC(EnSkb* this, GlobalContext* globalCtx);
void func_809961E4(EnSkb* this, GlobalContext* globalCtx);
void func_80996284(EnSkb* this, GlobalContext* globalCtx);
void func_8099630C(EnSkb* this, GlobalContext* globalCtx);
void func_809963D8(EnSkb* this, GlobalContext* globalCtx);
void func_80996474(EnSkb* this);
void func_809964A0(EnSkb* this, GlobalContext* globalCtx);
s32 func_80996594(EnSkb* this, GlobalContext* globalCtx);
void func_80996BEC(EnSkb* this, GlobalContext* globalCtx);

static AnimationInfo sAnimations[] = {
    { &object_skb_Anim_0064E0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0 },
    { &object_skb_Anim_003584, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_skb_Anim_002190, 0.6f, 0.0f, 0.0f, ANIMMODE_ONCE_INTERP, 4.0f },
    { &object_skb_Anim_002AC8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0 },
    { &object_skb_Anim_00270C, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0 },
    { &object_skb_Anim_00697C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0 },
    { &object_skb_Anim_006D90, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0 },
    { &object_skb_Anim_001D1C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0 },
    { &object_skb_Anim_003584, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &object_skb_Anim_003584, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -16.0f },
    { &object_skb_Anim_002AC8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &object_skb_Anim_0015EC, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0 },
    { &object_skb_Anim_0009E4, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0 },
};

static Vec3f D_80997468[] = {
    { -534.0f, 80.0, -1277.0f },
    { 113.0f, 80.0, -1359.0f },
    { 100.0f, 80.0, -770.0f },
    { -334.0f, 80.0, -720.0f },
};

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 15, { { 0, 0, 0 }, 10 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    sJntSphElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(3, 0xC),
    /* Normal arrow   */ DMG_ENTRY(3, 0xC),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(3, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0xB),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0x0),
    /* Normal Roll    */ DMG_ENTRY(4, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit En_Skb_InitVars = {
    ACTOR_EN_SKB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnSkb),
    (ActorFunc)EnSkb_Init,
    (ActorFunc)EnSkb_Destroy,
    (ActorFunc)EnSkb_Update,
    (ActorFunc)EnSkb_Draw,
};

void func_809947B0(GlobalContext* globalCtx, EnSkb* this, Vec3f* inPos) {
    Vec3f pos;
    Vec3f velocity = { 0.0f, 8.0f, 0.0f };
    Vec3f accel = { 0.0f, -1.5f, 0.0f };
    f32 sp40 = (Rand_ZeroOne() - 0.5f) * 6.28f;
    s32 pad;

    pos.y = this->actor.floorHeight;
    pos.x = (sin_rad(sp40) * 15.0f) + inPos->x;
    pos.z = (cos_rad(sp40) * 15.0f) + inPos->z;
    accel.x = randPlusMinusPoint5Scaled(1.0f);
    accel.z = randPlusMinusPoint5Scaled(1.0f);
    velocity.y += (Rand_ZeroOne() - 0.5f) * 4.0f;
    EffectSsHahen_Spawn(globalCtx, &pos, &velocity, &accel, 0, ((Rand_ZeroOne() * 5.0f) + 12.0f) * 0.8f,
                        HAHEN_OBJECT_DEFAULT, 10, NULL);
    func_800BBFB0(globalCtx, &pos, 10.0f, 1, 150, 0, 1);
}

void func_8099495C(EnSkb* this, GlobalContext* globalCtx) {
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_skb_Skel_005EF8, &object_skb_Anim_003584, this->jointTable,
                   this->morphTable, 20);
    this->unk_3DC = 0;
    func_80994E2C(this);
}

void func_809949C4(EnSkb* this, GlobalContext* globalCtx) {
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_skb_Skel_005EF8, &object_skb_Anim_00697C, this->jointTable,
                   this->morphTable, 20);
    this->unk_3DC = 1;
    func_809952D8(this);
}

void func_80994A30(EnSkb* this, GlobalContext* globalCtx) {
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_skb_Skel_005EF8, &object_skb_Anim_006D90, this->jointTable,
                   this->morphTable, 20);
    this->unk_3DC = 1;
    func_809953E8(this);
}

void func_80994A9C(EnSkb* this, GlobalContext* globalCtx) {
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_skb_Skel_005EF8, &object_skb_Anim_001D1C, this->jointTable,
                   this->morphTable, 20);
    this->unk_3DC = 1;
    func_809954F8(this);
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

void EnSkb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSkb* this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.colChkInfo.damageTable = &sDamageTable;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    this->unk_3E0 = 0;
    this->unk_3E2 = 0;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.colChkInfo.mass = 70;
    this->actor.colChkInfo.health = 2;
    this->actor.shape.yOffset = -8000.0f;
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    this->collider.elements[0].dim.modelSphere.radius = this->collider.elements[0].dim.worldSphere.radius = 10;
    this->collider.elements[1].dim.modelSphere.radius = this->collider.elements[1].dim.worldSphere.radius = 20;
    this->actor.home.pos = this->actor.world.pos;
    this->unk_3D6 = ENSKB_GET_F0(&this->actor);
    this->actor.floorHeight = this->actor.world.pos.y;

    if ((globalCtx->sceneNum == SCENE_BOTI) && (gSaveContext.sceneSetupIndex == 1) &&
        (globalCtx->csCtx.currentCsIndex == 0)) {
        this->actor.flags |= ACTOR_FLAG_100000;
    }

    switch (this->unk_3D6) {
        case 2:
            func_809949C4(this, globalCtx);
            break;

        case 3:
            func_80994A30(this, globalCtx);
            break;

        case 4:
            func_80994A9C(this, globalCtx);
            break;

        default:
            this->actor.flags &= ~ACTOR_FLAG_100000;
            this->actor.hintId = 0x55;
            func_8099495C(this, globalCtx);
            break;
    }
}

void EnSkb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSkb* this = THIS;

    if ((this->actor.parent != NULL) && (this->actor.parent->update != NULL) &&
        (this->actor.parent->id == ACTOR_EN_ENCOUNT4)) {
        EnEncount4* encount = (EnEncount4*)this->actor.parent;

        if (encount->unk_14C > 0) {
            encount->unk_14C--;
        }

        if (this->actor.colChkInfo.health == 0) {
            encount->unk_14E++;
        } else {
            encount->unk_14C = 0;
            encount->unk_14E = encount->unk_14C;
        }
    }

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80994DA8(EnSkb* this, GlobalContext* globalCtx) {
    if (Actor_IsFacingPlayer(&this->actor, 0x11C7) && (this->actor.xzDistToPlayer < 60.0f) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_CAPTAIN)) {
        func_80995C24(this);
    } else {
        func_80995A30(this);
    }
}

void func_80994E2C(EnSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_APPEAR);
    this->unk_3D0 = 0;
    this->unk_3DE = 0;
    this->actionFunc = func_80994E94;
}

void func_80994E94(EnSkb* this, GlobalContext* globalCtx) {
    if (this->skelAnime.curFrame < 4.0f) {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    } else {
        this->actor.flags |= ACTOR_FLAG_1;
    }

    Math_ApproachZeroF(&this->actor.shape.yOffset, 1.0f, 800.0f);
    Math_ApproachF(&this->actor.shape.shadowScale, 25.0f, 1.0f, 2.5f);
    if ((globalCtx->gameplayFrames % 2) == 0) {
        func_809947B0(globalCtx, this, &this->actor.world.pos);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && (this->actor.shape.yOffset == 0.0f)) {
        func_80995A30(this);
    }
    this->unk_3D0++;
}

void func_80994F7C(EnSkb* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_3E2 = 1;
        if (this->unk_3E0 == 1) {
            Message_StartTextbox(globalCtx, 0x13F8, &this->actor);
        } else {
            Message_StartTextbox(globalCtx, 0x13F6, &this->actor);
            this->unk_3E0 = 1;
        }
        this->actionFunc = func_80995190;
        this->actor.speedXZ = 0.0f;
    } else if (Actor_IsFacingPlayer(&this->actor, 0x2AAA) && !(this->collider.base.acFlags & AC_HIT)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_8099504C(EnSkb* this) {
    this->actionFunc = func_80995068;
    this->actor.speedXZ = 0.0f;
}

void func_80995068(EnSkb* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_3E2 = 1;
        if (this->unk_3E0 == 1) {
            Message_StartTextbox(globalCtx, 0x13F8, &this->actor);
            if (this->unk_3DE == 2) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
            }
        } else {
            Message_StartTextbox(globalCtx, 0x13F6, &this->actor);
            this->unk_3E0 = 1;
        }
        this->actionFunc = func_80995190;
        this->actor.speedXZ = 0.0f;
    } else if (Player_GetMask(globalCtx) != PLAYER_MASK_CAPTAIN) {
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        this->actor.hintId = 0x55;
        this->actor.colChkInfo.mass = MASS_HEAVY;
        func_80995A30(this);
    } else if (!(this->collider.base.acFlags & AC_HIT)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80995190(EnSkb* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;

        case 5:
            if (Message_ShouldAdvance(globalCtx)) {
                Message_StartTextbox(globalCtx, 0x13F7, &this->actor);
                if (this->unk_3DE == 2) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
                }
            }
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                this->actionFunc = func_80995244;
            }
            break;
    }
}

void func_80995244(EnSkb* this, GlobalContext* globalCtx) {
    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
    this->unk_3E2 = 0;

    switch (this->unk_3DE) {
        case 9:
            this->actionFunc = func_8099533C;
            break;

        case 10:
            this->actionFunc = func_8099544C;
            break;

        case 11:
            this->actionFunc = func_8099556C;
            break;

        default:
            func_8099504C(this);
            break;
    }
}

void func_809952D8(EnSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_3DE = 9;
    this->actionFunc = func_8099533C;
    this->actor.shape.shadowScale = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.shape.yOffset = 0.0f;
}

void func_8099533C(EnSkb* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) {
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        func_80994F7C(this, globalCtx);
    } else if (Actor_IsFacingPlayer(&this->actor, 0x2AAA) && (this->actor.xzDistToPlayer < 200.0f)) {
        this->actor.hintId = 0x55;
        this->actor.colChkInfo.mass = MASS_HEAVY;
        func_8099571C(this);
    }
}

void func_809953E8(EnSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 6);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_3DE = 10;
    this->actionFunc = func_8099544C;
    this->actor.shape.shadowScale = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.shape.yOffset = 0.0f;
}

void func_8099544C(EnSkb* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) {
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        func_80994F7C(this, globalCtx);
    } else if (Actor_IsFacingPlayer(&this->actor, 0x2AAA) && (this->actor.xzDistToPlayer < 200.0f)) {
        this->actor.hintId = 0x55;
        this->actor.colChkInfo.mass = MASS_HEAVY;
        func_8099571C(this);
    }
}

void func_809954F8(EnSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 7);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_3DE = 11;
    this->actionFunc = func_8099556C;
    this->actor.gravity = 0.0f;
    this->actor.shape.shadowScale = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.shape.yOffset = 0.0f;
    this->actor.targetArrowOffset = 4000.0f;
}

void func_8099556C(EnSkb* this, GlobalContext* globalCtx) {
    s16 sp26;

    if (this->skelAnime.curFrame < 15.0f) {
        sp26 = this->skelAnime.curFrame - 7.5f;
    } else {
        sp26 = 22.5f - this->skelAnime.curFrame;
    }

    if (Animation_OnFrame(&this->skelAnime, 22.5f)) {
        this->unk_3D4 = (u32)Rand_Next() % 0x7D0;
    }

    this->actor.shape.rot.x = Math_SinS(this->unk_3D4 * sp26) * 20000.0f;
    if (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) {
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        func_80994F7C(this, globalCtx);
    } else if (Actor_IsFacingPlayer(&this->actor, 0x2AAA) && (this->actor.xzDistToPlayer < 200.0f) &&
               (this->skelAnime.curFrame > 24.0f) && (this->skelAnime.curFrame < 28.0f)) {
        this->actor.hintId = 0x55;
        this->actor.colChkInfo.mass = MASS_HEAVY;
        this->actor.targetArrowOffset = 2000.0f;
        func_8099571C(this);
    }
}

void func_8099571C(EnSkb* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
    this->unk_3DC = 0;
    this->actor.shape.shadowScale = 0.0f;
    if (this->unk_3DE == 9) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 8);
        this->actor.speedXZ = 2.4f;
        this->actor.gravity = -1.0f;
        this->actor.velocity.y = 3.0f;
    } else if (this->unk_3DE == 0xA) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 8);
    } else if (this->unk_3DE == 0xB) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 9);
        this->actor.speedXZ = 3.2f;
        this->actor.gravity = -1.0f;
        this->actor.velocity.y = 2.0f;
    }
    this->unk_3DE = 13;
    this->actionFunc = func_80995818;
}

void func_80995818(EnSkb* this, GlobalContext* globalCtx) {
    s32 i;

    Math_ApproachF(&this->actor.shape.shadowScale, 25.0f, 1.0f, 2.5f);
    Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 0x10, 0x7D0, 0x64);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->actor.shape.rot.x = 0;
        this->actor.gravity = -2.0f;
        func_80995A30(this);
    }

    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
        for (i = 0; i < 10; i++) {
            func_809947B0(globalCtx, this, &this->actor.world.pos);
        }
    }
}

void func_809958F4(EnSkb* this) {
    Animation_Change(&this->skelAnime, &object_skb_Anim_003584, -1.0f, Animation_GetLastFrame(&object_skb_Anim_003584),
                     0.0f, 2, -4.0f);
    this->unk_3E4 = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
    this->unk_3DE = 1;
    this->actionFunc = func_8099599C;
}

void func_8099599C(EnSkb* this, GlobalContext* globalCtx) {
    Math_ApproachF(&this->actor.shape.yOffset, -8000.0f, 1.0f, 500.0f);

    if ((globalCtx->gameplayFrames % 2) != 0) {
        func_809947B0(globalCtx, this, &this->actor.world.pos);
    }

    Math_ApproachF(&this->actor.shape.shadowScale, 0.0f, 1.0f, 2.5f);

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80995A30(EnSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actor.speedXZ = 1.6f;
    this->unk_3DA = 0;
    this->unk_3DE = 2;
    this->actionFunc = func_80995A8C;
}

void func_80995A8C(EnSkb* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) {
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        this->actor.hintId = 0xFF;
        this->actor.colChkInfo.mass = MASS_HEAVY;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 12);
        func_8099504C(this);
        return;
    }

    if ((this->unk_3D8 != 0) && ((globalCtx->gameplayFrames % 16) == 0)) {
        this->unk_3DA = randPlusMinusPoint5Scaled(50000.0f);
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer + this->unk_3DA, 1, 0x2EE, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_WALK);
    }

    if ((this->actor.xzDistToPlayer > 800.0f) || func_80996594(this, globalCtx)) {
        func_809958F4(this);
    } else if (Actor_IsFacingPlayer(&this->actor, 0x11C7) && (this->actor.xzDistToPlayer < 60.0f)) {
        func_80995C24(this);
    }
}

void func_80995C24(EnSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->collider.base.atFlags &= ~AT_BOUNCED;
    this->actor.speedXZ = 0.0f;
    this->unk_3DE = 3;
    this->actionFunc = func_80995C84;
}

void func_80995C84(EnSkb* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, 3.0f) && (this->unk_3E4 == 0)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
        this->unk_3E4 = 1;
    } else if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
        this->unk_3E4 = 0;
    }

    if (this->collider.base.atFlags & AT_BOUNCED) {
        this->collider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
        func_80995D3C(this);
    } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80994DA8(this, globalCtx);
    }
}

void func_80995D3C(EnSkb* this) {
    Animation_Change(&this->skelAnime, &object_skb_Anim_002190, -0.4f, this->skelAnime.curFrame - 1.0f, 0.0f, 3, 0.0f);
    this->collider.base.atFlags &= ~AT_BOUNCED;
    this->unk_3DE = 4;
    this->unk_3E4 = 0;
    this->actionFunc = func_80995DC4;
}

void func_80995DC4(EnSkb* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80994DA8(this, globalCtx);
    }
}

void func_80995E08(EnSkb* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->unk_3E4 = 0;
    this->unk_3DE = 5;
    this->actionFunc = func_80995E64;
}

void func_80995E64(EnSkb* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        }
    }

    if ((this->actor.colorFilterTimer == 0) && (this->actor.bgCheckFlags & 1)) {
        if (this->unk_3DC == 0) {
            if (this->actor.colChkInfo.health == 0) {
                func_809961E4(this, globalCtx);
            } else {
                func_80994DA8(this, globalCtx);
            }
        } else {
            switch (this->unk_3D6) {
                case 2:
                    func_809952D8(this);
                    break;

                case 3:
                    func_809953E8(this);
                    break;
            }
        }
    } else if ((this->actor.colorFilterTimer == 0) && (this->unk_3DC == 1) && (this->unk_3D6 == 4)) {
        this->unk_3DE = 11;
        this->actionFunc = func_8099556C;
    }
}

void func_80995F98(EnSkb* this) {
    if ((this->unk_3DE == 9) || (this->unk_3DE == 0xA)) {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 8);
        this->actor.gravity = -1.0f;
        this->actor.speedXZ = 1.0f;
    } else if (this->unk_3DE == 0xB) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 9);
        this->actor.speedXZ = 3.2f;
        this->actor.velocity.y = 2.0f;
        this->actor.gravity = -1.0f;
    } else {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
        if (this->actor.bgCheckFlags & 1) {
            this->actor.speedXZ = -4.0f;
        }
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
    this->unk_3DE = 6;
    this->actionFunc = func_809960AC;
}

void func_809960AC(EnSkb* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        s32 i;

        for (i = 0; i < 10; i++) {
            func_809947B0(globalCtx, this, &this->actor.world.pos);
        }
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0x9C4, 0);
    }

    Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 0x10, 0x7D0, 0x64);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && (this->actor.bgCheckFlags & 1)) {
        this->actor.shape.rot.x = 0;
        this->actor.world.rot = this->actor.shape.rot;
        func_80994DA8(this, globalCtx);
    }
}

void func_809961E4(EnSkb* this, GlobalContext* globalCtx) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
    this->unk_3D8 |= 0x40;
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = -6.0f;
    }
    this->unk_3E4 = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
    this->unk_3DE = 7;
    this->actionFunc = func_80996284;
}

void func_80996284(EnSkb* this, GlobalContext* globalCtx) {
    if (this->unk_3D8 & 0x80) {
        if (1) {}
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x10);
        func_80996474(this);
    }
}

void func_809962D4(EnSkb* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_8099630C;
}

void func_8099630C(EnSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer == 0) {
        this->drawDmgEffTimer = 0;
        this->drawDmgEffScale = 0.0f;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            this->unk_3D8 |= 1;
            func_80995F98(this);
        } else {
            func_809961E4(this, globalCtx);
        }
    } else if (this->drawDmgEffTimer == 1) {
        func_80996BEC(this, globalCtx);
    }
}

void func_809963C4(EnSkb* this) {
    this->actionFunc = func_809963D8;
}

void func_809963D8(EnSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer == 0) {
        this->drawDmgEffTimer = 0;
        this->drawDmgEffScale = 0.0f;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            this->unk_3D8 |= 1;
            func_80995F98(this);
        } else {
            func_809961E4(this, globalCtx);
        }
    }
}

void func_80996474(EnSkb* this) {
    this->unk_3D0 = 0;
    this->actor.draw = NULL;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_809964A0;
}

void func_809964A0(EnSkb* this, GlobalContext* globalCtx) {
    if ((this->unk_3D0++ < 19) ^ 1) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_809964DC(EnSkb* this, GlobalContext* globalCtx) {
    if (this->unk_3D6 == 0) {
        if ((this->actionFunc != func_80994E94) && (this->actionFunc != func_80996284) &&
            (this->actionFunc != func_809964A0) && (gSaveContext.save.weekEventReg[85] & 0x40)) {
            this->actor.colChkInfo.health = 0;
            func_809961E4(this, globalCtx);
        }
    }
}

s32 func_80996544(Vec2f arg0, Vec2f arg1) {
    s32 ret;

    if ((arg1.x * arg0.z) < (arg0.x * arg1.z)) {
        ret = 1;
    } else {
        ret = -1;
    }

    return ret;
}

s32 func_80996594(EnSkb* this, GlobalContext* globalCtx) {
    s32 temp_s2;
    s32 j;
    Vec2f sp60;
    Vec2f sp58;
    s32 sp54 = true;
    f32 worldZ;
    s32 i = 0;
    f32 worldX;

    worldZ = this->actor.world.pos.z;
    worldX = this->actor.world.pos.x;

    sp60.x = D_80997468[0].z - worldZ;
    sp60.z = D_80997468[0].x - worldX;
    sp58.x = D_80997468[1].z - worldZ;
    sp58.z = D_80997468[1].x - worldX;
    j = 1;
    temp_s2 = func_80996544(sp60, sp58);

    if (1) {}

    do {
        i++;
        if (j < 3) {
            j++;
        } else {
            j = 0;
        }
        sp60.x = D_80997468[i].z - worldZ;
        sp60.z = D_80997468[i].x - worldX;
        sp58.x = D_80997468[j].z - worldZ;
        sp58.z = D_80997468[j].x - worldX;
        if (func_80996544(sp60, sp58) != temp_s2) {
            sp54 = false;
            break;
        }
    } while (j != 0);

    return sp54;
}

void func_8099672C(EnSkb* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if ((this->unk_3DE != 6) && (this->unk_3DE != 7)) {
        if ((this->actor.bgCheckFlags & 0x60) && (this->actor.depthInWater >= 40.0f)) {
            this->actor.colChkInfo.health = 0;
            this->unk_3E4 = 0;
            func_809961E4(this, globalCtx);
            return;
        }

        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->actionFunc == func_8099630C) {
                switch (this->actor.colChkInfo.damageEffect) {
                    default:
                        if (this->drawDmgEffTimer > 1) {
                            func_80996BEC(this, globalCtx);
                        }
                        this->drawDmgEffTimer = 0;
                        break;

                    case 1:
                    case 3:
                    case 4:
                    case 12:
                    case 13:
                        return;
                }
            }

            if (!Actor_ApplyDamage(&this->actor) && (this->actor.colChkInfo.damageEffect != 3) &&
                (this->actor.colChkInfo.damageEffect != 4)) {
                this->unk_3D8 |= 0x40;
                func_809961E4(this, globalCtx);
                return;
            }

            switch (this->actor.colChkInfo.damageEffect) {
                case 11:
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffAlpha = 1.0f;
                    this->drawDmgEffScale = 0.0f;
                    Actor_SetColorFilter(&this->actor, 0, 0x78, 0, 40);
                    func_80995E08(this);
                    break;

                case 1:
                    Actor_SetColorFilter(&this->actor, 0, 0x78, 0, 40);
                    func_80995E08(this);
                    break;

                case 2:
                    this->drawDmgEffTimer = 80;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                    this->drawDmgEffAlpha = 1.0f;
                    this->drawDmgEffScale = 0.0f;
                    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
                    this->unk_3D8 |= 1;
                    func_80995F98(this);
                    break;

                case 3:
                    if (this->actor.colChkInfo.health != 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                        this->drawDmgEffTimer = 80;
                    } else {
                        this->drawDmgEffTimer = 3;
                    }
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_SFX;
                    this->drawDmgEffAlpha = 1.0f;
                    this->drawDmgEffScale = 0.5f;
                    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
                    func_809962D4(this);
                    break;

                case 4:
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    this->drawDmgEffAlpha = 1.0f;
                    this->drawDmgEffScale = 0.5f;
                    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                    func_809963C4(this);
                    break;

                case 12:
                case 14:
                    this->unk_3D8 |= 1;

                case 15:
                    if ((player->swordAnimation == 4) || (player->swordAnimation == 11) ||
                        (player->swordAnimation == 22) || (player->swordAnimation == 23)) {
                        this->unk_3D8 |= 1;
                    }

                case 13:
                    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 8);
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                    func_80995F98(this);
                    break;
            }
        }
    }
}

void func_80996AD0(EnSkb* this, GlobalContext* globalCtx) {
    if (1) {}

    if ((this->actionFunc != func_80996284) && (this->unk_3E2 != 1)) {
        if (this->unk_3E4 != 0) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if (((this->unk_3DE != 0) || (this->unk_3D0 >= 11)) && (this->unk_3DE != 1) && (this->unk_3DE != 4) &&
            (this->unk_3DE != 6) && (this->unk_3DE != 7) &&
            ((this->actor.colorFilterTimer == 0) || !(this->actor.colorFilterParams & 0x4000))) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if ((this->actionFunc != func_80996284) && (this->actionFunc != func_809964A0)) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80996BEC(EnSkb* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80997550 = { 170, 255, 255, 255 };
    static Color_RGBA8 D_80997554 = { 200, 200, 255, 255 };
    static Vec3f D_80997558 = { 0.0f, -1.0, 0.0f };
    Vec3f sp84;
    s32 i;
    s16 yaw;
    s32 end;

    if (this->unk_3D8 & 2) {
        end = 13;
    } else {
        end = 14;
    }

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < end; i++) {
        yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->limbPos[i]);
        sp84.x = Math_SinS(yaw) * 3.0f;
        sp84.z = Math_CosS(yaw) * 3.0f;
        sp84.y = (Rand_ZeroOne() * 4.0f) + 4.0f;
        EffectSsEnIce_Spawn(globalCtx, &this->limbPos[i], 0.6f, &sp84, &D_80997558, &D_80997550, &D_80997554, 30);
    }
}

void func_80996D68(EnSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer > 0) {
        this->drawDmgEffTimer--;
    }

    if (this->actionFunc != func_8099630C) {
        if (this->drawDmgEffTimer < 20) {
            if (this->actionFunc == func_809963D8) {
                Math_SmoothStepToF(&this->drawDmgEffScale, 0.0f, 0.5f, 0.03f, 0.0f);
            } else {
                Math_SmoothStepToF(&this->drawDmgEffScale, 0.0f, 0.5f, 0.01f, 0.0f);
            }
            this->drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;
        } else {
            Math_SmoothStepToF(&this->drawDmgEffScale, 0.5f, 0.1f, 0.02f, 0.0f);
        }
    }
}

void EnSkb_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSkb* this = THIS;

    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != func_80995E64) && (this->actionFunc != func_80996284) &&
        (this->actionFunc != func_8099630C) && (this->actionFunc != func_809963D8)) {
        SkelAnime_Update(&this->skelAnime);
    }

    func_8099672C(this, globalCtx);
    if ((this->actionFunc != func_8099630C) && (this->actionFunc != func_809963D8) &&
        (this->actionFunc != func_80995E64)) {
        Actor_MoveWithGravity(&this->actor);
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 30.0f, 60.0f, 0x1D);
    func_809964DC(this, globalCtx);
    func_80996AD0(this, globalCtx);
    func_80996D68(this, globalCtx);
}

s32 EnSkb_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnSkb* this = THIS;
    s32 pad;
    s16 sins;

    if (limbIndex == 11) {
        if (!(this->unk_3D8 & 2)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            sins = fabsf(Math_SinS(globalCtx->gameplayFrames * 6000) * 95.0f) + 160.0f;

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, sins, sins, sins, 255);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        } else {
            *dList = NULL;
        }
    } else if ((limbIndex == 12) && (this->unk_3D8 & 2)) {
        *dList = NULL;
    }

    if (limbIndex == 10) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
    }

    return false;
}

void EnSkb_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80997564 = { 800.0f, 1200.0f, 0.0f };
    EnSkb* this = THIS;

    Collider_UpdateSpheres(limbIndex, &this->collider);
    if ((this->unk_3D8 & 1) && !(this->unk_3D8 & 2)) {
        if (limbIndex == 11) {
            Actor_SpawnBodyParts(&this->actor, globalCtx, 1, dList);
            this->unk_3D8 |= 2;
        }
    } else if ((this->unk_3D8 & 0x40) && !(this->unk_3D8 & 0x80) && ((limbIndex != 11) || !(this->unk_3D8 & 1)) &&
               (limbIndex != 12)) {
        Actor_SpawnBodyParts(&this->actor, globalCtx, 1, dList);
    }

    if (this->drawDmgEffTimer != 0) {
        if ((limbIndex == 2) || (limbIndex == 4) || (limbIndex == 5) || (limbIndex == 6) || (limbIndex == 7) ||
            (limbIndex == 8) || (limbIndex == 9) || (limbIndex == 13) || (limbIndex == 14) || (limbIndex == 15) ||
            (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18)) {
            Matrix_GetStateTranslation(&this->limbPos[this->limbCount]);
            this->limbCount++;
        } else if ((limbIndex == 11) && !(this->unk_3D8 & 2)) {
            Matrix_MultiplyVector3fByState(&D_80997564, &this->limbPos[this->limbCount]);
            this->limbCount++;
        }
    }
}

void EnSkb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSkb* this = THIS;

    this->limbCount = 0;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnSkb_OverrideLimbDraw,
                      EnSkb_PostLimbDraw, &this->actor);
    if (this->drawDmgEffTimer > 0) {
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, this->limbCount, this->drawDmgEffScale, 0.5f,
                                this->drawDmgEffAlpha, this->drawDmgEffType);
    }

    if (this->unk_3D8 & 0x40) {
        this->unk_3D8 |= 0x80;
    }
}
