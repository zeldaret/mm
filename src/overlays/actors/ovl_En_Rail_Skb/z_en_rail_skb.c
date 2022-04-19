/*
 * File: z_en_rail_skb.c
 * Overlay: ovl_En_Rail_Skb
 * Description: Ikana Graveyard - Circle of Stalchildren
 */

#include "overlays/actors/ovl_Obj_Hakaisi/z_obj_hakaisi.h"
#include "z_en_rail_skb.h"
#include "objects/object_skb/object_skb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10)

#define THIS ((EnRailSkb*)thisx)

void EnRailSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B70FA0(EnRailSkb* this);
void func_80B70FF8(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B710E4(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B7114C(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B7123C(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B712FC(EnRailSkb* this);
void func_80B71314(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71354(EnRailSkb* this);
void func_80B713A4(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71488(EnRailSkb* this);
void func_80B714D8(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B7151C(EnRailSkb* this);
void func_80B715AC(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B716A8(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B717C8(EnRailSkb* this);
void func_80B717E0(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B718C4(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71910(EnRailSkb* this);
void func_80B71954(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71A08(EnRailSkb* this);
void func_80B71A58(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71B6C(EnRailSkb* this);
void func_80B71BB8(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71D8C(EnRailSkb* this, GlobalContext* globalCtx, EnRailSkbUnkFunc unkFunc);
void func_80B71EA8(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B71F3C(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B72100(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B723F8(EnRailSkb* this);
void func_80B72430(EnRailSkb* this, GlobalContext* globalCtx, s32 arg2);
void func_80B726B4(EnRailSkb* this, GlobalContext* globalCtx);
void func_80B72830(EnRailSkb* this, s16 arg1);
s32 func_80B7285C(EnRailSkb* this);

const ActorInit En_Rail_Skb_InitVars = {
    ACTOR_EN_RAIL_SKB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnRailSkb),
    (ActorFunc)EnRailSkb_Init,
    (ActorFunc)EnRailSkb_Destroy,
    (ActorFunc)EnRailSkb_Update,
    (ActorFunc)EnRailSkb_Draw,
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

void func_80B708C0(EnRailSkb* this, GlobalContext* globalCtx) {
    static s32 D_80B7348C = 0;
    Path* path = &globalCtx->setupPathList[ENRAILSKB_GET_FF00(&this->actor)];
    Vec3f sp70;
    s32 phi_a3;

    this->unk_230 = Lib_SegmentedToVirtual(path->points);
    this->unk_2E0 = D_80B7348C;
    this->unk_2E8 = path->count;

    if (D_80B7348C == 0) {
        s32 i;

        for (i = 1; (i < this->unk_2E8) && (i < 10); i++) {
            D_80B7348C++;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_RAIL_SKB, 0.0f, 0.0f, 0.0f, 0, 0,
                               0, this->actor.params);
        }
        D_80B7348C = 0;
    }

    this->actor.world.pos.x = this->unk_230[this->unk_2E0].x;
    this->actor.world.pos.y = this->unk_230[this->unk_2E0].y;
    this->actor.world.pos.z = this->unk_230[this->unk_2E0].z;

    if (this->unk_2E0 < (this->unk_2E8 - 1)) {
        phi_a3 = this->unk_2E0 + 1;
    } else {
        phi_a3 = 0;
    }

    sp70.x = this->unk_230[phi_a3].x;
    sp70.y = this->unk_230[phi_a3].y;
    sp70.z = this->unk_230[phi_a3].z;

    this->actor.world.rot.y = this->actor.shape.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &sp70);
}

s32 func_80B70AB4(Vec2f arg0, Vec2f arg1) {
    s32 phi_v1;

    if ((arg1.x * arg0.z) < (arg0.x * arg1.z)) {
        phi_v1 = 1;
    } else {
        phi_v1 = -1;
    }
    return phi_v1;
}

s32 func_80B70B04(EnRailSkb* this, Vec3f pos) {
    s32 pad;
    s32 temp_s3;
    Vec2f sp60;
    Vec2f sp58;
    s32 ret = true;
    s32 pad2;
    s32 i = 0;
    s32 j;

    sp60.x = this->unk_230[0].z - pos.z;
    sp60.z = this->unk_230[0].x - pos.x;
    sp58.x = this->unk_230[1].z - pos.z;
    sp58.z = this->unk_230[1].x - pos.x;
    j = 1;
    temp_s3 = func_80B70AB4(sp60, sp58);

    while (j != 0) {
        i++;

        if (j < (this->unk_2E8 - 1)) {
            j++;
        } else {
            j = 0;
        }

        sp60.x = this->unk_230[i].z - pos.z;
        sp60.z = this->unk_230[i].x - pos.x;
        sp58.x = this->unk_230[j].z - pos.z;
        sp58.z = this->unk_230[j].x - pos.x;

        if (func_80B70AB4(sp60, sp58) != temp_s3) {
            ret = false;
            break;
        }
    }

    return ret;
}

void func_80B70D24(EnRailSkb* this, GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_OBJ_HAKAISI) && func_80B70B04(this, actor->world.pos)) {
            if (Flags_GetSwitch(globalCtx, (actor->params & 0xFF00) >> 8)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->unk_22C = (ObjHakaisi*)actor;
            return;
        }
        actor = actor->next;
    }
    Actor_MarkForDeath(&this->actor);
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

void EnRailSkb_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRailSkb* this = THIS;

    func_80B708C0(this, globalCtx);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_skb_Skel_005EF8, &object_skb_Anim_0064E0, this->jointTable,
                   this->morphTable, 20);
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    if (Flags_GetSwitch(globalCtx, ENRAILSKB_GET_FF(&this->actor))) {
        Actor_MarkForDeath(&this->actor);
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.speedXZ = 1.6f;
    this->actor.hintId = 0x55;
    this->unk_3F2 = 0;
    this->unk_2E4 = -1;
    this->unk_3FC = 0;
    this->unk_3FA = 0;
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    this->unk_3FE = 0;

    if (this->actor.parent == NULL) {
        this->unk_3F4 = 1;
        this->unk_3F6 = 1;
        this->unk_3F8 = 0;
    }

    if ((globalCtx->sceneNum == SCENE_BOTI) && (gSaveContext.sceneSetupIndex == 1) &&
        (globalCtx->csCtx.currentCsIndex == 0)) {
        this->actor.flags |= ACTOR_FLAG_100000;
    }

    func_80B70FA0(this);
}

void EnRailSkb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRailSkb* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80B70FA0(EnRailSkb* this) {
    this->unk_3F2 = 0;
    if (this->actionFunc != func_80B716A8) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    }
    this->actionFunc = func_80B70FF8;
}

void func_80B70FF8(EnRailSkb* this, GlobalContext* globalCtx) {
    s16 temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (this->actor.xzDistToPlayer < 65.0f) {
        if ((ABS_ALT(temp_v0) < 0x2AAA) && (this->unk_3F2 >= 6)) {
            func_80B71354(this);
        }
    }

    if (this->unk_3F2 < 6) {
        this->unk_3F2++;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x71C, 0xB6);
}

void func_80B710AC(EnRailSkb* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80B710E4;
}

void func_80B710E4(EnRailSkb* this, GlobalContext* globalCtx) {
    if (this->actor.colorFilterTimer == 0) {
        func_80B70FA0(this);
    }
}

void func_80B71114(EnRailSkb* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80B7114C;
}

void func_80B7114C(EnRailSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer == 0) {
        this->drawDmgEffTimer = 0;
        this->drawDmgEffScale = 0.0f;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
            this->unk_402 |= 1;
            func_80B712FC(this);
        } else {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
            func_80B71488(this);
        }
    } else if (this->drawDmgEffTimer == 1) {
        func_80B726B4(this, globalCtx);
    }
}

void func_80B71228(EnRailSkb* this) {
    this->actionFunc = func_80B7123C;
}

void func_80B7123C(EnRailSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer == 0) {
        this->drawDmgEffTimer = 0;
        this->drawDmgEffScale = 0.0f;
        this->drawDmgEffAlpha = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
            this->unk_402 |= 1;
            func_80B712FC(this);
        } else {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
            func_80B71488(this);
        }
    }
}

void func_80B712FC(EnRailSkb* this) {
    this->unk_3F2 = 0;
    this->actionFunc = func_80B71314;
}

void func_80B71314(EnRailSkb* this, GlobalContext* globalCtx) {
    if (this->unk_3F2 >= 6) {
        func_80B70FA0(this);
    } else {
        this->unk_3F2++;
    }
}

void func_80B71354(EnRailSkb* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->actionFunc = func_80B713A4;
}

void func_80B713A4(EnRailSkb* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if ((this->actor.xzDistToPlayer > 65.0f) || (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN)) {
            func_80B70FA0(this);
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
        }
    }

    if (this->actor.xzDistToPlayer > 65.0f) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x71C, 0xB6);
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xAAA, 0xB6);
    }
}

void func_80B71488(EnRailSkb* this) {
    this->unk_402 |= 0x40;
    this->actor.flags &= ~ACTOR_FLAG_1;
    if (this->unk_2E0 != 0) {
        this->unk_2E4 = this->unk_2E0 - 1;
    } else {
        this->unk_2E4 = this->unk_2E8 - 1;
    }
    this->actionFunc = func_80B714D8;
}

void func_80B714D8(EnRailSkb* this, GlobalContext* globalCtx) {
    if (this->actor.draw != NULL) {
        this->actor.draw = NULL;
    }

    if (this->unk_2E0 == this->unk_2E4) {
        func_80B7151C(this);
    }
}

void func_80B7151C(EnRailSkb* this) {
    this->actor.shape.yOffset = -5000.0f;
    this->actor.colChkInfo.health = 2;
    this->unk_402 = 0;
    this->actor.flags |= ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_APPEAR);
    this->actor.draw = EnRailSkb_Draw;
    this->actor.shape.shadowAlpha = 0;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80B715AC;
}

void func_80B715AC(EnRailSkb* this, GlobalContext* globalCtx) {
    if (Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 0.5f, 500.0f, 10.0f) == 0.0f) {
        func_80B70FA0(this);
    } else {
        func_80B72430(this, globalCtx, 1);
    }

    if (this->actor.shape.shadowAlpha != 255) {
        if (this->actor.shape.shadowAlpha >= 235) {
            this->actor.shape.shadowAlpha = 255;
        } else {
            this->actor.shape.shadowAlpha += 20;
        }
    }
}

void func_80B71650(EnRailSkb* this) {
    this->unk_3FE = 0;
    if (this->actionFunc != func_80B70FF8) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    }
    this->actionFunc = func_80B716A8;
}

void func_80B716A8(EnRailSkb* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_3FE = 1;
        func_80B71D8C(this, globalCtx, func_80B723F8);
        if (!func_80B7285C(this)) {
            Message_StartTextbox(globalCtx, 0x13EC, &this->actor);
            this->unk_400 = 0x13EC;
            func_80B72830(this, 1);
        } else {
            Message_StartTextbox(globalCtx, 0x13F5, &this->actor);
            this->unk_400 = 0x13F5;
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 12);
        func_80B717C8(this);
    } else if ((this->actor.xzDistToPlayer < 100.0f) && !(this->collider.base.acFlags & AC_HIT)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x71C, 0xB6);
}

void func_80B717C8(EnRailSkb* this) {
    this->unk_3F2 = 0;
    this->actionFunc = func_80B717E0;
}

void func_80B717E0(EnRailSkb* this, GlobalContext* globalCtx) {
    this->unk_3FA = 0;

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
            break;

        case 3:
            if ((globalCtx->gameplayFrames % 2) != 0) {
                this->unk_3FA = 1;
            }
            break;

        case 4:
            func_80B72100(this, globalCtx);
            break;

        case 5:
            func_80B71F3C(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                func_80B71650(this);
            }
            break;
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0x71C, 0xB6);
}

void func_80B718B0(EnRailSkb* this) {
    this->actionFunc = func_80B718C4;
}

void func_80B718C4(EnRailSkb* this, GlobalContext* globalCtx) {
    func_80B70D24(this, globalCtx);
    if (this->actor.parent == NULL) {
        if (this->unk_22C != NULL) {
            ObjHakaisi* hakasi = this->unk_22C;

            hakasi->unk_198 = 1;
        }
    }
    func_80B71910(this);
}

void func_80B71910(EnRailSkb* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80B71954;
}

void func_80B71954(EnRailSkb* this, GlobalContext* globalCtx) {
    s16 sp36 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_22C->dyna.actor.world.pos);
    f32 sp30 = Math_Vec3f_DistXZ(&this->actor.world.pos, &this->unk_22C->dyna.actor.world.pos);

    Math_SmoothStepToS(&this->actor.shape.rot.y, sp36, 1, 0x71C, 0xB6);
    this->actor.world.rot = this->actor.shape.rot;
    if (sp30 < 80.0f) {
        func_80B71A08(this);
    }
    Actor_MoveWithGravity(&this->actor);
}

void func_80B71A08(EnRailSkb* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->actionFunc = func_80B71A58;
}

void func_80B71A58(EnRailSkb* this, GlobalContext* globalCtx) {
    s16 sp36 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_22C->dyna.actor.world.pos);

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
        if (this->unk_2E8 < this->unk_22C->dyna.actor.colChkInfo.health) {
            this->unk_22C->dyna.actor.colChkInfo.health--;
        } else {
            this->unk_22C->dyna.actor.colChkInfo.health--;
            func_80B71B6C(this);
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        if (this->unk_2E8 < this->unk_22C->dyna.actor.colChkInfo.health) {
            this->unk_22C->dyna.actor.colChkInfo.health--;
        } else {
            this->unk_22C->dyna.actor.colChkInfo.health--;
            func_80B71B6C(this);
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, sp36, 1, 0x71C, 0xB6);
    this->actor.world.rot = this->actor.shape.rot;
}

void func_80B71B6C(EnRailSkb* this) {
    this->unk_3F2 = 10;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80B71BB8;
}

void func_80B71BB8(EnRailSkb* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    f32 sp34 = Math_Vec3f_DistXZ(&this->actor.world.pos, &this->unk_22C->dyna.actor.world.pos);

    if (this->unk_3F2 > 0) {
        this->unk_3F2--;
        return;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y,
                       Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_22C->dyna.actor.world.pos), 1, 0x71C, 0xB6);

    if ((this->actor.bgCheckFlags & 1) && (this->unk_22C->dyna.actor.colChkInfo.health == 0)) {
        Actor_MoveWithGravity(&this->actor);
    } else {
        this->actor.velocity.y += this->actor.gravity;
        this->actor.world.pos.y += this->actor.velocity.y;
        Math_SmoothStepToF(&this->actor.world.pos.x, this->unk_22C->dyna.actor.world.pos.x, 0.6f, 1.6f, 0.1f);
        Math_SmoothStepToF(&this->actor.world.pos.z, this->unk_22C->dyna.actor.world.pos.z, 0.6f, 1.6f, 0.1f);
    }

    if (this->actor.bgCheckFlags & 2) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if ((sp34 < 50.0f) && (this->actor.bgCheckFlags & 1)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_ATTACK);
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 9);
        this->actor.velocity.y = 10.0f;

        for (i = 0; i < 4; i++) {
            func_80B72430(this, globalCtx, 0);
        }
    }
}

void func_80B71D8C(EnRailSkb* this, GlobalContext* globalCtx, EnRailSkbUnkFunc unkFunc) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_ENEMY].first;

    while (actor != NULL) {
        if (actor->id == ACTOR_EN_RAIL_SKB) {
            unkFunc((EnRailSkb*)actor);
        }
        actor = actor->next;
    }
}

void func_80B71DF0(EnRailSkb* this) {
    if (this->actionFunc == func_80B714D8) {
        this->actor.shape.yOffset = -5000.0f;
        this->actor.colChkInfo.health = 2;
        this->unk_402 = 0;
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.draw = EnRailSkb_Draw;
        this->actor.shape.shadowAlpha = 0;
        this->actor.shape.rot.y = this->actor.world.rot.y;
    } else if ((this->actionFunc == func_80B7114C) && (this->drawDmgEffTimer > 1)) {
        this->drawDmgEffTimer = 0;
    }

    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
    this->actionFunc = func_80B71EA8;
}

void func_80B71EA8(EnRailSkb* this, GlobalContext* globalCtx) {
    if (Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 0.5f, 500.0f, 10.0f) != 0.0f) {
        func_80B72430(this, globalCtx, 1);
    }

    if (this->actor.shape.shadowAlpha != 255) {
        if (this->actor.shape.shadowAlpha >= 235) {
            this->actor.shape.shadowAlpha = 255;
        } else {
            this->actor.shape.shadowAlpha += 20;
        }
    }
}

void func_80B71F3C(EnRailSkb* this, GlobalContext* globalCtx) {
    if (((this->unk_400 == 0x13ED) || (this->unk_400 == 0x13F5)) && (this->unk_3F2 != 1)) {
        func_80B71D8C(this, globalCtx, func_80B71DF0);
        func_80B717C8(this);
        this->unk_3F2 = 1;
    }

    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_400) {
            case 0x13EC:
                Message_StartTextbox(globalCtx, 0x13ED, &this->actor);
                this->unk_400 = 0x13ED;
                break;

            case 0x13ED:
                Message_StartTextbox(globalCtx, 0x13EE, &this->actor);
                this->unk_400 = 0x13EE;
                break;

            case 0x13EE:
                Message_StartTextbox(globalCtx, 0x13EF, &this->actor);
                this->unk_400 = 0x13EF;
                break;

            case 0x13EF:
            case 0x13F5:
                Message_StartTextbox(globalCtx, 0x13F0, &this->actor);
                this->unk_400 = 0x13F0;
                break;

            case 0x13F1:
                Message_StartTextbox(globalCtx, 0x13F2, &this->actor);
                this->unk_400 = 0x13F2;
                break;

            case 0x13F2:
                if (this->unk_3FC == 1) {
                    Message_StartTextbox(globalCtx, 0x13F4, &this->actor);
                    this->unk_400 = 0x13F4;
                } else {
                    func_801477B4(globalCtx);
                    func_80B71D8C(this, globalCtx, func_80B71650);
                }
                break;

            case 0x13F3:
                Message_StartTextbox(globalCtx, 0x13F2, &this->actor);
                this->unk_400 = 0x13F2;
                this->unk_3FC = 1;
                break;

            case 0x13F4:
                func_801477B4(globalCtx);
                func_80B71D8C(this, globalCtx, func_80B718B0);
                break;
        }
    }
}

void func_80B72100(EnRailSkb* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex == 0) {
            func_8019F208();
            Message_StartTextbox(globalCtx, 0x13F1, &this->actor);
            this->unk_400 = 0x13F1;
        } else {
            func_8019F208();
            Message_StartTextbox(globalCtx, 0x13F3, &this->actor);
            this->unk_400 = 0x13F3;
        }
    }
}

void func_80B72190(EnRailSkb* this, GlobalContext* globalCtx) {
    EnRailSkb* parent;
    Vec3f sp38;
    s32 pad;
    s16 sp32;

    if ((this->actionFunc != func_80B714D8) &&
        (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 15.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_WALK);
    }

    if (this->actor.parent == NULL) {
        this->unk_3F4 = this->unk_3F6;
        this->unk_3F6 = 1;

        if ((this->actionFunc == func_80B713A4) || (this->actionFunc == func_80B710E4) ||
            (this->actionFunc == func_80B7114C) || (this->actionFunc == func_80B7123C) ||
            (this->actionFunc == func_80B717E0)) {
            this->unk_3F6 = 0;
        }

        if (this->unk_3F4 == 0) {
            return;
        }
    } else {
        parent = (EnRailSkb*)this->actor.parent;

        if ((this->actionFunc == func_80B713A4) || (this->actionFunc == func_80B710E4) ||
            (this->actionFunc == func_80B7114C) || (this->actionFunc == func_80B7123C) ||
            (this->actionFunc == func_80B717E0)) {
            parent->unk_3F6 = 0;
        }

        if (parent->unk_3F4 == 0) {
            return;
        }
    }

    if ((this->actionFunc != func_80B71EA8) && (this->actionFunc != func_80B71954) &&
        (this->actionFunc != func_80B71A58) && (this->actionFunc != func_80B71BB8)) {
        sp38.x = this->unk_230[this->unk_2E0].x;
        sp38.y = this->unk_230[this->unk_2E0].y;
        sp38.z = this->unk_230[this->unk_2E0].z;
        sp32 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp38);

        if (Math_Vec3f_DistXZ(&this->actor.world.pos, &sp38) > 100.0f) {
            Math_SmoothStepToS(&this->actor.world.rot.y, sp32, 10, 0x3000, 0x100);
        } else if (this->unk_2E0 < (this->unk_2E8 - 1)) {
            this->unk_2E0++;
        } else {
            this->unk_2E0 = 0;
        }
        Actor_MoveWithGravity(&this->actor);
    }
}

void func_80B723F8(EnRailSkb* this) {
    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actor.flags |= ACTOR_FLAG_100000;
    this->actor.hintId = 0xFF;
    this->actor.textId = 0;
}

void func_80B72430(EnRailSkb* this, GlobalContext* globalCtx, s32 arg2) {
    Vec3f sp5C = this->actor.world.pos;
    Vec3f sp50 = { 0.0f, 8.0f, 0.0f };
    Vec3f sp44 = { 0.0f, -1.5f, 0.0f };
    s16 sp42;
    s32 pad;

    if ((globalCtx->gameplayFrames & arg2) == 0) {
        sp42 = Rand_Next();

        sp5C.x += 15.0f * Math_SinS(sp42);
        sp5C.y = this->actor.floorHeight;
        sp5C.z += 15.0f * Math_CosS(sp42);

        sp44.x = Rand_Centered();
        sp44.z = Rand_Centered();

        sp50.y += Rand_Centered() * 4.0f;

        EffectSsHahen_Spawn(globalCtx, &sp5C, &sp50, &sp44, 0, (Rand_Next() & 7) + 10, -1, 10, NULL);
        func_800BBFB0(globalCtx, &sp5C, 10.0f, 1, 150, 0, 1);
    }
}

void func_80B725C0(EnRailSkb* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer > 0) {
        this->drawDmgEffTimer--;
    }

    if (this->actionFunc != func_80B7114C) {
        if (this->drawDmgEffTimer < 20) {
            if (this->actionFunc == func_80B7123C) {
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

void func_80B726B4(EnRailSkb* this, GlobalContext* globalCtx) {
    static Color_RGBA8 D_80B734B0 = { 170, 255, 255, 255 };
    static Color_RGBA8 D_80B734B4 = { 200, 200, 255, 255 };
    static Vec3f D_80B734B8 = { 0.0f, -1.0f, 0.0f };
    Vec3f sp84;
    s32 i;
    s32 end;
    s16 yaw;

    if (this->unk_402 & 2) {
        end = ARRAY_COUNT(this->limbPos) - 1;
    } else {
        end = ARRAY_COUNT(this->limbPos);
    }

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < end; i++) {
        yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->limbPos[i]);

        sp84.x = Math_SinS(yaw) * 3.0f;
        sp84.z = Math_CosS(yaw) * 3.0f;
        sp84.y = (Rand_ZeroOne() * 4.0f) + 4.0f;

        EffectSsEnIce_Spawn(globalCtx, &this->limbPos[i], 0.6f, &sp84, &D_80B734B8, &D_80B734B0, &D_80B734B4, 30);
    }
}

void func_80B72830(EnRailSkb* this, s16 arg1) {
    if (this->actor.parent == NULL) {
        this->unk_3F8 = arg1;
    } else {
        ((EnRailSkb*)this->actor.parent)->unk_3F8 = arg1;
    }
}

s32 func_80B7285C(EnRailSkb* this) {
    s32 phi_v1;

    if (this->actor.parent == NULL) {
        phi_v1 = this->unk_3F8;
    } else {
        phi_v1 = ((EnRailSkb*)this->actor.parent)->unk_3F8;
    }
    return phi_v1;
}

void func_80B72880(EnRailSkb* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80B70FF8) || (this->actionFunc == func_80B716A8)) {
        if (this->actionFunc != func_80B716A8) {
            if (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) {
                this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
                this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
                this->actor.flags |= ACTOR_FLAG_100000;
                this->actor.hintId = 0xFF;
                this->actor.textId = 0;
                func_80B71650(this);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_CAPTAIN) {
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
            this->actor.flags &= ~ACTOR_FLAG_100000;
            this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
            this->actor.hintId = 0x55;
            this->actor.textId = 0;
            func_80B70FA0(this);
        }
    }
}

void func_80B72970(EnRailSkb* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    if ((this->actionFunc == func_80B714D8) || (this->actionFunc == func_80B7123C) ||
        (this->actionFunc == func_80B715AC) || (this->actionFunc == func_80B71954) ||
        (this->actionFunc == func_80B71A58) || (this->actionFunc == func_80B71BB8) || (this->unk_3FE == 1)) {
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if (this->actionFunc == func_80B7114C) {
            switch (this->actor.colChkInfo.damageEffect) {
                case 1:
                case 3:
                case 4:
                case 12:
                case 13:
                    return;

                default:
                    if (this->drawDmgEffTimer >= 2) {
                        func_80B726B4(this, globalCtx);
                    }
                    this->drawDmgEffTimer = 0;
                    break;
            }
        }

        if ((Actor_ApplyDamage(&this->actor) == 0) && (this->actor.colChkInfo.damageEffect != 3) &&
            (this->actor.colChkInfo.damageEffect != 4)) {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_STALKID_DEAD);
            func_80B71488(this);
            return;
        }

        switch (this->actor.colChkInfo.damageEffect) {
            case 11:
                this->drawDmgEffTimer = 40;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                this->drawDmgEffAlpha = 1.0f;
                this->drawDmgEffScale = 0.0f;
                Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
                func_80B710AC(this);
                break;

            case 1:
                Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
                func_80B710AC(this);
                break;

            case 2:
                this->drawDmgEffTimer = 80;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                this->drawDmgEffAlpha = 1.0f;
                this->drawDmgEffScale = 0.0f;
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                this->unk_402 |= 1;
                func_80B712FC(this);
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
                func_80B71114(this);
                break;

            case 4:
                this->drawDmgEffTimer = 40;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                this->drawDmgEffAlpha = 1.0f;
                this->drawDmgEffScale = 0.5f;
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                func_80B71228(this);
                break;

            case 12:
            case 14:
                this->unk_402 |= 1;

            case 15:
                if ((player->swordAnimation == 4) || (player->swordAnimation == 11) || (player->swordAnimation == 22) ||
                    (player->swordAnimation == 23)) {
                    this->unk_402 |= 1;
                }

            case 13:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_DAMAGE);
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                func_80B712FC(this);
                break;

            default:
                break;
        }
    }

    if (this->actionFunc == func_80B713A4) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->actionFunc != func_80B71314) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnRailSkb_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRailSkb* this = THIS;

    this->actionFunc(this, globalCtx);

    func_80B72190(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 15.0f, 30.0f, 60.0f, 5);
    func_80B72970(this, globalCtx);

    if ((this->actionFunc != func_80B710E4) && (this->actionFunc != func_80B7114C) &&
        (this->actionFunc != func_80B7123C)) {
        SkelAnime_Update(&this->skelAnime);
    }

    func_80B72880(this, globalCtx);
    func_80B725C0(this, globalCtx);
}

s32 EnRailSkb_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnRailSkb* this = THIS;
    s16 abs;

    if (limbIndex == 11) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        abs = fabsf(Math_SinS(globalCtx->state.frames * 6000) * 95.0f) + 160.0f;

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, abs, abs, abs, 255);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else if (limbIndex == 10) {
        Vec3f sp24 = { 0.0f, 1000.0f, 0.0f };

        Matrix_MultiplyVector3fByState(&sp24, &this->actor.focus.pos);
    } else if ((limbIndex == 12) && (this->unk_3FA == 1)) {
        Matrix_InsertZRotation_s(1820, MTXMODE_APPLY);
    }

    if (((limbIndex == 11) || (limbIndex == 12)) && (this->unk_402 & 2)) {
        *dList = NULL;
    }

    return false;
}

void EnRailSkb_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80B734D0 = { 800.0f, 1200.0f, 0.0f };
    EnRailSkb* this = THIS;

    if (!(this->unk_402 & 0x80)) {
        Collider_UpdateSpheres(limbIndex, &this->collider);

        if ((limbIndex == 11) && (this->unk_402 & 1) && !(this->unk_402 & 2)) {
            Actor_SpawnBodyParts(&this->actor, globalCtx, 1, dList);
            this->unk_402 |= 2;
        } else if ((this->unk_402 & 0x40) && ((limbIndex != 11) || !(this->unk_402 & 1)) && (limbIndex != 12)) {
            Actor_SpawnBodyParts(&this->actor, globalCtx, 1, dList);
        }

        if (this->drawDmgEffTimer != 0) {
            if ((limbIndex == 2) || (limbIndex == 4) || (limbIndex == 5) || (limbIndex == 6) || (limbIndex == 7) ||
                (limbIndex == 8) || (limbIndex == 9) || (limbIndex == 13) || (limbIndex == 14) || (limbIndex == 15) ||
                (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18)) {
                Matrix_GetStateTranslation(&this->limbPos[this->limbCount]);
                this->limbCount++;
            } else if ((limbIndex == 11) && !(this->unk_402 & 2)) {
                Matrix_MultiplyVector3fByState(&D_80B734D0, &this->limbPos[this->limbCount]);
                this->limbCount++;
            }
        }
    }
}

void EnRailSkb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRailSkb* this = THIS;

    this->limbCount = 0;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnRailSkb_OverrideLimbDraw,
                      EnRailSkb_PostLimbDraw, &this->actor);
    if (this->drawDmgEffTimer > 0) {
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, this->limbCount, this->drawDmgEffScale, 0.5f,
                                this->drawDmgEffAlpha, this->drawDmgEffType);
    }

    if ((this->unk_402 & 0x40) && !(this->unk_402 & 0x80)) {
        this->unk_402 |= 0x80;
    }
}
