/*
 * File: z_en_hint_skb.c
 * Overlay: ovl_En_Hint_Skb
 * Description: Stalchild that gives hints in Oceanside Spider House
 */

#include "z_en_hint_skb.h"
#include "objects/object_skb/object_skb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnHintSkb*)thisx)

void EnHintSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C1FE0C(EnHintSkb* this);
void func_80C1FE20(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C1FE80(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C1FF30(EnHintSkb* this);
void func_80C1FF88(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2003C(EnHintSkb* this);
void func_80C200B8(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2016C(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20334(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20484(EnHintSkb* this);
void func_80C204F0(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20590(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2069C(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C2077C(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C208BC(EnHintSkb* this);
void func_80C208D0(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20B88(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C20C24(EnHintSkb* this, GlobalContext* globalCtx);
s32 func_80C21414(EnHintSkb* this);
void func_80C21468(EnHintSkb* this, GlobalContext* globalCtx);
void func_80C215E4(GlobalContext* globalCtx, EnHintSkb* this, Vec3f* arg2);

const ActorInit En_Hint_Skb_InitVars = {
    ACTOR_EN_HINT_SKB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnHintSkb),
    (ActorFunc)EnHintSkb_Init,
    (ActorFunc)EnHintSkb_Destroy,
    (ActorFunc)EnHintSkb_Update,
    (ActorFunc)EnHintSkb_Draw,
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

static CollisionCheckInfoInit2 sColChkInfoInit = { 2, 0, 0, 0, MASS_IMMOVABLE };

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

static AnimationInfo sAnimations[] = {
    { &object_skb_Anim_0064E0, 0.96f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_skb_Anim_003584, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_skb_Anim_002190, 0.6f, 0.0f, 0.0f, ANIMMODE_ONCE_INTERP, 4.0f },
    { &object_skb_Anim_002AC8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_skb_Anim_00270C, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_skb_Anim_00697C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_skb_Anim_006D90, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_skb_Anim_001D1C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_skb_Anim_003584, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &object_skb_Anim_003584, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -16.0f },
    { &object_skb_Anim_002AC8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &object_skb_Anim_0015EC, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -8.0f },
    { &object_skb_Anim_0009E4, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -8.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

void EnHintSkb_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnHintSkb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_skb_Skel_005EF8, &object_skb_Anim_00697C, this->jointTable,
                   this->morphtable, 20);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElement);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.hintId = 0x55;
    this->unk_3E4 = 0;
    this->unk_3DE = 0;
    this->unk_3E0 = 0;
    this->unk_3DC = 0;
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    func_80C1FE0C(this);
}

void EnHintSkb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHintSkb* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80C1FE0C(EnHintSkb* this) {
    this->actionFunc = func_80C1FE20;
}

void func_80C1FE20(EnHintSkb* this, GlobalContext* globalCtx) {
}

void func_80C1FE30(EnHintSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actor.speedXZ = 1.6f;
    this->actionFunc = func_80C1FE80;
}

void func_80C1FE80(EnHintSkb* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_WALK);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 750, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_IsFacingPlayer(&this->actor, 0x11C7) && (this->actor.xzDistToPlayer < 60.0f)) {
        func_80C1FF30(this);
    }
}

void func_80C1FF30(EnHintSkb* this) {
    this->collider.base.atFlags &= ~AT_BOUNCED;
    this->actor.speedXZ = 0.0f;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->actionFunc = func_80C1FF88;
}

void func_80C1FF88(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->collider.base.atFlags & AT_BOUNCED) {
        this->collider.base.atFlags &= ~(AT_BOUNCED | AT_HIT);
        func_80C2003C(this);
    }

    if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (func_80C21414(this) && (Player_GetMask(globalCtx) != PLAYER_MASK_CAPTAIN)) {
            func_80C1FF30(this);
        } else {
            func_80C1FE30(this);
        }
    }
}

void func_80C2003C(EnHintSkb* this) {
    Animation_Change(&this->skelAnime, &object_skb_Anim_002190, -0.4f, this->skelAnime.curFrame - 1.0f, 0.0f, 3, 0.0f);
    this->collider.base.atFlags &= ~AT_BOUNCED;
    this->actionFunc = func_80C200B8;
}

void func_80C200B8(EnHintSkb* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (func_80C21414(this)) {
            func_80C1FF30(this);
        } else {
            func_80C1FE30(this);
        }
    }
}

void func_80C2011C(EnHintSkb* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80C2016C;
}

void func_80C2016C(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        this->actor.speedXZ = 0.0f;
    } else if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        }
    }

    if ((this->actor.colorFilterTimer == 0) && (this->actor.bgCheckFlags & 1)) {
        if (this->actor.colChkInfo.health == 0) {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
            func_80C20484(this);
        } else if (this->skelAnime.animation == &object_skb_Anim_00697C) {
            func_80C1FE0C(this);
        } else if (func_80C21414(this)) {
            func_80C1FF30(this);
        } else {
            func_80C1FE30(this);
        }
    }
}

void func_80C20274(EnHintSkb* this) {
    if (this->skelAnime.animation == &object_skb_Anim_00697C) {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 8);
        this->actor.gravity = -1.0f;
        this->actor.speedXZ = 1.0f;
    } else {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
        if (this->actor.bgCheckFlags & 1) {
            this->actor.speedXZ = -4.0f;
        }
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
    this->actionFunc = func_80C20334;
}

void func_80C20334(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 2) {
        s32 i;

        for (i = 0; i < 10; i++) {
            func_80C215E4(globalCtx, this, &this->actor.world.pos);
        }
        this->actor.speedXZ = 0.0f;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.speedXZ < 0.0f) {
            this->actor.speedXZ += 0.05f;
        } else if (this->actor.speedXZ != 0.0f) {
            this->actor.speedXZ -= 0.05f;
        }
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 2500, 0);
    }

    Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 16, 2000, 100);

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) && (this->actor.bgCheckFlags & 1)) {
        this->actor.world.rot = this->actor.shape.rot;
        func_80C1FE30(this);
    }
}

void func_80C20484(EnHintSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
    this->unk_3E8 |= 4;
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = -6.0f;
    }
    this->actionFunc = func_80C204F0;
}

void func_80C204F0(EnHintSkb* this, GlobalContext* globalCtx) {
    if (!(this->unk_3E8 & 8)) {
        return;
    }

    Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x10);
    Actor_MarkForDeath(&this->actor);
}

void func_80C20540(EnHintSkb* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80C20590;
}

void func_80C20590(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer == 0) {
        this->drawDmgEffTimer = 0;
        this->drawDmgEffScale = 0.0f;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
            this->unk_3E8 |= 1;
            func_80C20274(this);
        } else {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
            func_80C20484(this);
        }
    } else if (this->drawDmgEffTimer == 1) {
        func_80C21468(this, globalCtx);
    }
}

void func_80C2066C(EnHintSkb* this) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = 0.0f;
    }
    this->actionFunc = func_80C2069C;
}

void func_80C2069C(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer == 0) {
        this->drawDmgEffTimer = 0;
        this->drawDmgEffScale = 0.0f;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
            this->unk_3E8 |= 1;
            func_80C20274(this);
        } else {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
            func_80C20484(this);
        }
    }
}

void func_80C2075C(EnHintSkb* this) {
    this->unk_3E0 = 0;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80C2077C;
}

void func_80C2077C(EnHintSkb* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_3E0 = 1;
        if (this->unk_3DC == 0) {
            this->unk_3DC = 1;
            Message_StartTextbox(globalCtx, 0x1147, &this->actor);
            this->unk_3E6 = 0x1147;
            if (this->skelAnime.animation == &object_skb_Anim_00697C) {
                globalCtx->msgCtx.msgMode = 0x44;
                this->actor.speedXZ = 2.4f;
                this->actor.gravity = -1.0f;
                this->actor.velocity.y = 3.0f;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 8);
            }
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
            Message_StartTextbox(globalCtx, 0x1148, &this->actor);
            this->unk_3E6 = 0x1148;
        }
        func_80C208BC(this);
    } else if ((this->actor.xzDistToPlayer < 100.0f) && !(this->collider.base.acFlags & AC_HIT)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80C208BC(EnHintSkb* this) {
    this->actionFunc = func_80C208D0;
}

void func_80C208D0(EnHintSkb* this, GlobalContext* globalCtx) {
    this->unk_3DE = 0;

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 3:
            if ((globalCtx->gameplayFrames % 2) != 0) {
                this->unk_3DE = 1;
            }
            break;

        case 4:
            func_80C20B88(this, globalCtx);
            break;

        case 5:
            func_80C20C24(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                func_80C2075C(this);
            }
            break;

        case 0:
        case 1:
        case 2:
            break;
    }

    if (this->unk_3E6 == 0x1147) {
        if (this->actor.bgCheckFlags & 2) {
            s32 i;

            this->actor.speedXZ = 0.0f;

            for (i = 0; i < 10; i++) {
                func_80C215E4(globalCtx, this, &this->actor.world.pos);
            }
        }

        if ((this->skelAnime.animation == &object_skb_Anim_003584) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            Message_StartTextbox(globalCtx, 0x1147, &this->actor);
            this->unk_3E6 = 0x1147;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
        }
    }

    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 5, 0x71C, 0xB6);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

void func_80C20A74(EnHintSkb* this, GlobalContext* globalCtx) {
    s32 params = ENHINTSKB_GET_FF(&this->actor);

    switch (params) {
        case 1:
            Message_StartTextbox(globalCtx, 0x1149, &this->actor);
            this->unk_3E6 = 0x1149;
            break;

        case 2:
            Message_StartTextbox(globalCtx, 0x114A, &this->actor);
            this->unk_3E6 = 0x114A;
            break;

        case 3:
            Message_StartTextbox(globalCtx, 0x114B, &this->actor);
            this->unk_3E6 = 0x114B;
            break;

        case 4:
            Message_StartTextbox(globalCtx, 0x114C, &this->actor);
            this->unk_3E6 = 0x114C;
            break;

        case 5:
            Message_StartTextbox(globalCtx, 0x114D, &this->actor);
            this->unk_3E6 = 0x114D;
            break;

        case 6:
            Message_StartTextbox(globalCtx, 0x114E, &this->actor);
            this->unk_3E6 = 0x114E;
            break;

        default:
            Message_StartTextbox(globalCtx, 0x1149, &this->actor);
            this->unk_3E6 = 0x1149;
            break;
    }
}

void func_80C20B88(EnHintSkb* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex == 0) {
            func_8019F208();
            this->unk_3E8 |= 0x10;
            Message_StartTextbox(globalCtx, 0x1150, &this->actor);
            this->unk_3E6 = 0x1150;
        } else {
            func_8019F230();
            Message_StartTextbox(globalCtx, 0x1152, &this->actor);
            this->unk_3E6 = 0x1152;
        }
    }
}

void func_80C20C24(EnHintSkb* this, GlobalContext* globalCtx) {
    if (!Message_ShouldAdvance(globalCtx)) {
        return;
    }

    switch (this->unk_3E6) {
        case 0x1147:
            Message_StartTextbox(globalCtx, 0x1148, &this->actor);
            this->unk_3E6 = 0x1148;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
            break;

        case 0x1148:
            func_80C20A74(this, globalCtx);
            break;

        case 0x1149:
        case 0x114A:
        case 0x114B:
        case 0x114C:
        case 0x114D:
        case 0x114E:
            Message_StartTextbox(globalCtx, 0x114F, &this->actor);
            this->unk_3E6 = 0x114F;
            break;

        case 0x1152:
            Message_StartTextbox(globalCtx, 0x1151, &this->actor);
            this->unk_3E6 = 0x1151;
            break;

        case 0x1150:
            Message_StartTextbox(globalCtx, 0x1151, &this->actor);
            this->unk_3E6 = 0x1151;
            break;

        case 0x1151:
            func_801477B4(globalCtx);
            if (this->unk_3E8 & 0x10) {
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
                func_80C20484(this);
            } else {
                func_80C2075C(this);
            }
            break;
    }
}

void func_80C20D64(EnHintSkb* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80C1FE20) || (this->actionFunc == func_80C2077C) ||
        (this->actionFunc == func_80C1FE80)) {
        if (this->actionFunc != func_80C2077C) {
            if (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) {
                this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
                this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
                this->actor.hintId = 255;
                this->actor.textId = 0;
                if (this->actionFunc == func_80C1FE80) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 12);
                }
                func_80C2075C(this);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_CAPTAIN) {
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
            this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
            this->actor.hintId = 0x55;
            this->actor.textId = 0;
            if (this->skelAnime.animation == &object_skb_Anim_00697C) {
                func_80C1FE0C(this);
            } else {
                func_80C1FE30(this);
            }
        }
    }
}

void func_80C20E90(EnHintSkb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actor.bgCheckFlags & 0x60) && (this->actor.depthInWater >= 40.0f)) {
        this->actor.colChkInfo.health = 0;
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
        func_80C20484(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if (this->actionFunc == func_80C20590) {
            switch (this->actor.colChkInfo.damageEffect) {
                case 1:
                case 3:
                case 4:
                case 12:
                case 13:
                    return;

                default:
                case 2:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    if (this->drawDmgEffTimer > 1) {
                        func_80C21468(this, globalCtx);
                    }
                    this->drawDmgEffTimer = 0;
                    break;
            }
        }

        if (!Actor_ApplyDamage(&this->actor)) {
            if ((this->actor.colChkInfo.damageEffect != 3) && (this->actor.colChkInfo.damageEffect != 4)) {
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
                this->unk_3E8 |= 4;
                func_80C20484(this);
                return;
            }
        }

        switch (this->actor.colChkInfo.damageEffect) {
            case 11:
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                this->drawDmgEffTimer = 40;
                this->drawDmgEffAlpha = 1.0f;
                this->drawDmgEffScale = 0.0f;
                Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
                func_80C2011C(this);
                break;

            case 1:
                Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
                func_80C2011C(this);
                break;

            case 2:
                this->drawDmgEffTimer = 80;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                this->drawDmgEffAlpha = 1.0f;
                this->drawDmgEffScale = 0.0f;
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                this->unk_3E8 |= 1;
                func_80C20274(this);
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
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                func_80C20540(this);
                break;
            case 4:
                this->drawDmgEffTimer = 40;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                this->drawDmgEffAlpha = 1.0f;
                this->drawDmgEffScale = 0.5f;
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                func_80C2066C(this);
                break;

            case 12:
            case 14:
                this->unk_3E8 |= 1;

            case 15:
                if ((player->swordAnimation == 4) || (player->swordAnimation == 11) || (player->swordAnimation == 22) ||
                    (player->swordAnimation == 23)) {
                    this->unk_3E8 |= 1;
                }

            case 13:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                func_80C20274(this);
                break;

            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                break;
        }
    }
}

void func_80C21250(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->unk_3E0 != 1) {
        func_80C20E90(this, globalCtx);
        if (this->actionFunc == func_80C1FF88) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        if ((this->actionFunc != func_80C200B8) && (this->actionFunc != func_80C20334) &&
            (this->actionFunc != func_80C204F0)) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }

        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80C21320(EnHintSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer > 0) {
        this->drawDmgEffTimer--;
    }

    if (this->actionFunc != func_80C20590) {
        if (this->drawDmgEffTimer < 20) {
            if (this->actionFunc == func_80C2069C) {
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

s32 func_80C21414(EnHintSkb* this) {
    if (Actor_IsFacingPlayer(&this->actor, 0x11C7) && (this->actor.xzDistToPlayer < 60.0f)) {
        return true;
    }
    return false;
}

void func_80C21468(EnHintSkb* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80C21E44 = { 170, 255, 255, 255 };
    static Color_RGBA8 D_80C21E48 = { 200, 200, 255, 255 };
    static Vec3f D_80C21E4C = { 0.0f, -1.0f, 0.0f };
    Vec3f sp84;
    s32 phi_s4;
    s16 temp_s1;
    s32 i;

    if (this->unk_3E8 & 2) {
        phi_s4 = ARRAY_COUNT(this->limbPos) - 1;
    } else {
        phi_s4 = ARRAY_COUNT(this->limbPos);
    }

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < phi_s4; i++) {
        temp_s1 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->limbPos[i]);

        sp84.x = Math_SinS(temp_s1) * 3.0f;
        sp84.z = Math_CosS(temp_s1) * 3.0f;
        sp84.y = (Rand_ZeroOne() * 4.0f) + 4.0f;

        EffectSsEnIce_Spawn(globalCtx, &this->limbPos[i], 0.6f, &sp84, &D_80C21E4C, &D_80C21E44, &D_80C21E48, 30);
    }
}

void func_80C215E4(GlobalContext* globalCtx, EnHintSkb* this, Vec3f* arg2) {
    Vec3f sp5C;
    Vec3f sp50 = { 0.0f, 8.0f, 0.0f };
    Vec3f sp44 = { 0.0f, -1.5f, 0.0f };
    f32 sp40 = (Rand_ZeroOne() - 0.5f) * 6.28f;
    s32 pad;

    sp5C.y = this->actor.floorHeight;
    sp5C.x = (sin_rad(sp40) * 15.0f) + arg2->x;
    sp5C.z = (cos_rad(sp40) * 15.0f) + arg2->z;

    sp44.x = randPlusMinusPoint5Scaled(1.0f);
    sp44.z = randPlusMinusPoint5Scaled(1.0f);

    sp50.y += (Rand_ZeroOne() - 0.5f) * 4.0f;

    EffectSsHahen_Spawn(globalCtx, &sp5C, &sp50, &sp44, 0, ((Rand_ZeroOne() * 5.0f) + 12.0f) * 0.8f, -1, 10, NULL);
    func_800BBFB0(globalCtx, &sp5C, 10.0f, 1, 150, 0, 1);
}

void EnHintSkb_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHintSkb* this = THIS;

    this->actionFunc(this, globalCtx);

    if ((this->actionFunc != func_80C2016C) && (this->actionFunc != func_80C20590) &&
        (this->actionFunc != func_80C2069C)) {
        SkelAnime_Update(&this->skelAnime);
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 30.0f, 60.0f, 0x1D);
    func_80C21250(this, globalCtx);
    func_80C20D64(this, globalCtx);
    func_80C21320(this, globalCtx);
}

s32 EnHintSkb_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnHintSkb* this = THIS;
    f32 temp_f10;

    if (limbIndex == 11) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        temp_f10 = fabsf(Math_SinS(globalCtx->state.frames * 6000) * 95.0f) + 160.0f;

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, (s16)temp_f10, (s16)temp_f10, (s16)temp_f10, 255);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else if (limbIndex == 10) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
    } else if ((limbIndex == 12) && (this->unk_3DE == 1)) {
        Matrix_InsertZRotation_s(0x71C, MTXMODE_APPLY);
    }

    if (((limbIndex == 11) || (limbIndex == 12)) && (this->unk_3E8 & 2)) {
        *dList = NULL;
    }

    return false;
}

void EnHintSkb_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80C21E70 = { 800.0f, 1200.0f, 0.0f };
    EnHintSkb* this = THIS;

    if (!(this->unk_3E8 & 8)) {
        Collider_UpdateSpheres(limbIndex, &this->collider);

        if ((limbIndex == 11) && (this->unk_3E8 & 1) && !(this->unk_3E8 & 2)) {
            Actor_SpawnBodyParts(&this->actor, globalCtx, 1, dList);
            this->unk_3E8 |= 2;
        } else if ((this->unk_3E8 & 4) && !(this->unk_3E8 & 8) && ((limbIndex != 11) || !(this->unk_3E8 & 1)) &&
                   (limbIndex != 12)) {
            Actor_SpawnBodyParts(&this->actor, globalCtx, 1, dList);
        }

        if (this->drawDmgEffTimer != 0) {
            if ((limbIndex == 2) || (limbIndex == 4) || (limbIndex == 5) || (limbIndex == 6) || (limbIndex == 7) ||
                (limbIndex == 8) || (limbIndex == 9) || (limbIndex == 13) || (limbIndex == 14) || (limbIndex == 15) ||
                (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18)) {
                Matrix_GetStateTranslation(&this->limbPos[this->limbCount]);
                this->limbCount++;
            } else if ((limbIndex == 11) && !(this->unk_3E8 & 2)) {
                Matrix_MultiplyVector3fByState(&D_80C21E70, &this->limbPos[this->limbCount]);
                this->limbCount++;
            }
        }
    }
}

void EnHintSkb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHintSkb* this = THIS;

    this->limbCount = 0;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnHintSkb_OverrideLimbDraw,
                      EnHintSkb_PostLimbDraw, &this->actor);
    if (this->drawDmgEffTimer > 0) {
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, this->limbCount, this->drawDmgEffScale, 0.5f,
                                this->drawDmgEffAlpha, this->drawDmgEffType);
    }

    if (this->unk_3E8 & 4) {
        this->unk_3E8 |= 8;
    }
}
