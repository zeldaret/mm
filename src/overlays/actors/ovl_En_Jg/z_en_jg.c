/*
 * File: z_en_jg.c
 * Overlay: ovl_En_Jg
 * Description: Goron Elder
 */

#include "z_en_jg.h"
#include "objects/object_jg/object_jg.h"
#include "overlays/actors/ovl_En_S_Goro/z_en_s_goro.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnJg_FrozenTalking(EnJg* this, GlobalContext* globalCtx);
void func_80B74134(EnJg* this, GlobalContext* globalCtx);
s32 func_80B750A0(EnJg* this, GlobalContext* globalCtx);
void func_80B751F8(EnJg* this, GlobalContext* globalCtx);
void func_80B74550(EnJg* this, GlobalContext* globalCtx);
void func_80B742F8(EnJg* this, GlobalContext* globalCtx);
void func_80B747C8(EnJg* this, GlobalContext* globalCtx);
void func_80B74B54(EnJg* this, GlobalContext* globalCtx);
s32 func_80B74E5C(EnJg* this);
void func_80B74BC8(EnJg* this, GlobalContext* globalCtx);
void func_80B74440(EnJg* this, GlobalContext* globalCtx);
void func_80B741F8(EnJg* this, GlobalContext* globalCtx);
void EnJg_FrozenIdle(EnJg* this, GlobalContext* globalCtx);

const ActorInit En_Jg_InitVars = {
    ACTOR_EN_JG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JG,
    sizeof(EnJg),
    (ActorFunc)EnJg_Init,
    (ActorFunc)EnJg_Destroy,
    (ActorFunc)EnJg_Update,
    (ActorFunc)EnJg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
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
    { 60, 80, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 50, 80, 0, MASS_IMMOVABLE };

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

static ActorAnimationEntryS sAnimations[] = {
    { &gGoronElderIdleAnim, 1.0f, 0, -1, 0, -10 },          { &gGoronElderWalkAnim, 1.0f, 0, -1, 0, -10 },
    { &gGoronElderWavingAnim, 1.0f, 0, -1, 0, -10 },        { &gGoronElderHeadShakeAnim, 1.0f, 0, -1, 0, -10 },
    { &gGoronElderSurpriseStartAnim, 1.0f, 0, -1, 2, -10 }, { &gGoronElderSurpriseLoopAnim, 1.0f, 0, -1, 0, -10 },
    { &gGoronElderAngryAnim, 1.0f, 0, -1, 0, -10 },         { &gGoronElderSurpriseStartAnim, 2.0f, 0, -1, 2, 0 },
    { &gGoronElderSurpriseStartAnim, -2.0f, 0, -1, 2, 0 },  { &gGoronElderWalkAnim, -1.0f, 0, -1, 0, -10 },
    { &gGoronElderTakeOutDrumAnim, 1.0f, 0, -1, 2, 0 },     { &gGoronElderDrumIdleAnim, 1.0f, 0, -1, 0, 0 },
    { &gGoronElderPlayingDrumAnim, 1.0f, 1, 44, 2, 0 },     { &gGoronElderThinkingAnim, 1.0f, 0, -1, 0, 0 },
    { &gGoronElderRememberingAnim, 1.0f, 0, -1, 2, 0 },     { &gGoronElderStrongRememberingAnim, 1.0f, 0, -1, 2, 0 },
    { &gGoronElderDepressedAnim, 1.0f, 0, -1, 0, 0 },       { &gGoronElderIdleAnim, 1.0f, 0, -1, 0, 0 },
    { &gGoronElderCradleAnim, 1.0f, 0, -1, 0, 0 },
};

static Vec3f sSfxPos = { 0.0f, 0.0f, 0.0f };

static Vec3f sFocusOffset = { 0.0f, 0.0f, 0.0f };

static Vec3f sBreathPosOffset = { 1000.0f, -500.0f, 0.0f };

static Vec3f sBreathVelOffset = { 0.0f, 0.0f, 0.75f };

static Vec3f sBreathAccelOffset = { 0.0f, 0.0f, -0.070000000298f };

Actor* func_80B73A90(GlobalContext* globalCtx, u8 arg1) {
    Actor* actorIterator = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;

    while (actorIterator != NULL) {
        if ((actorIterator->id == ACTOR_EN_S_GORO) && (EN_S_GORO_GET_PARAM_F(actorIterator) == arg1)) {
            return actorIterator;
        }
        actorIterator = actorIterator->next;
    }
    return NULL;
}

void EnJg_CheckCollision(EnJg* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 30.0f, 30.0f, 7);
}

s16 func_80B73B98(Path* path, s32 idx, Vec3f* pos, f32* distSQ) {
    Vec3s* points;
    f32 diffX;
    f32 diffZ;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[idx];
        diffX = points[0].x - pos->x;
        diffZ = points[0].z - pos->z;
    } else {
        diffX = 0.0f;
        diffZ = 0.0f;
    }

    *distSQ = SQ(diffX) + SQ(diffZ);

    return RADF_TO_BINANG(Math_Acot2F(diffZ, diffX));
}

s32 func_80B73C58(EnJg* this, Path* path, s32 arg2) {
    Vec3s* sp5C = (Vec3s*)Lib_SegmentedToVirtual(path->points);
    s32 count = path->count;
    s32 idx = arg2;
    s32 ret = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);
    if (idx == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if ((count - 1) == idx) {
        phi_f12 = sp5C[count - 1].x - sp5C[count - 2].x;
        phi_f14 = sp5C[count - 1].z - sp5C[count - 2].z;
    } else {
        phi_f12 = sp5C[idx + 1].x - sp5C[idx - 1].x;
        phi_f14 = sp5C[idx + 1].z - sp5C[idx - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        ret = true;
    }

    return ret;
}

s16 func_80B73DF4(EnJg* this) {
    s16 temp = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (temp > 0) {
        return this->actor.cutscene;
    }

    return ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
}

void func_80B73E3C(EnJg* this) {
    ActorCutscene_Stop(this->cutscene);
    if (this->unk_3D0 == 0xA) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            this->actionFunc = func_80B74134;
        } else {
            this->cutscene = 0x7C;
        }
    } else {
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
    }

    ActorCutscene_SetIntentToPlay(this->cutscene);
    this->actionFunc = func_80B741F8;

    switch (this->textId) {
        case 0xDD0:
        case 0xDD2:
        case 0xDD3:
        case 0xDD4:
        case 0xDD6:
            this->flags |= EN_JG_FLAG_1;
            break;

        default:
            this->flags &= ~EN_JG_FLAG_1;
            break;
    }
}

void func_80B73F1C(EnJg* this, GlobalContext* globalCtx) {
    switch (this->textId) {
        case 0xDAC:
            this->animationIndex = EN_JG_ANIMATION_SHAKING_HEAD;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;

        case 0xDAD:
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_START;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B742F8;
            break;

        case 0xDB7:
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_START;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;

        case 0xDAE:
        case 0xDB3:
        case 0xDB6:
        case 0xDBA:
        case 0xDBD:
        case 0xDC4:
            this->animationIndex = EN_JG_ANIMATION_IDLE;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;

        case 0xDB0:
        case 0xDBB:
        case 0xDBC:
        case 0xDC6:
            this->animationIndex = EN_JG_ANIMATION_ANGRY;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;

        case 0xDB4:
        case 0xDB5:
            this->animationIndex = EN_JG_ANIMATION_WAVING;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;
    }
}

void func_80B7406C(EnJg* this, GlobalContext* globalCtx) {
    func_80B751F8(this, globalCtx);
}

void func_80B7408C(EnJg* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->flags |= EN_JG_FLAG_4;
        func_801518B0(globalCtx, this->textId, &this->actor);
        this->actionFunc = func_80B74134;
    } else if (this->actor.xzDistToPlayer < 100.0f || this->actor.isTargeted) {
        func_800B863C(&this->actor, globalCtx);
        this->textId = func_80B750A0(this, globalCtx);
    }
}

void func_80B74134(EnJg* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        if ((this->textId == 0xDCC) || (this->textId == 0xDDD) || (this->textId == 0xDE0)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->flags &= ~EN_JG_FLAG_4;
            this->actionFunc = func_80B7408C;
        } else {
            this->textId = func_80B74E5C(this);
            func_801518B0(globalCtx, this->textId, &this->actor);
        }
    }
}

void func_80B741F8(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene) != 0) {
        switch (this->textId) {
            case 0xDD0:
            case 0xDD2:
            case 0xDD3:
            case 0xDD4:
            case 0xDD6:
                this->shrineGoron = func_80B73A90(globalCtx, this->unk_3D0);
                ActorCutscene_Start(this->cutscene, this->shrineGoron);
                func_800E0308(globalCtx->cameraPtrs[0], this->shrineGoron);
                break;

            default:
                ActorCutscene_Start(this->cutscene, &this->actor);
                func_800E0308(globalCtx->cameraPtrs[0], this->shrineGoron);
                break;
        }
        this->actionFunc = func_80B74134;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            if (this->unk_3D0 == 0xA) {
                this->actionFunc = func_80B74134;
            } else {
                ActorCutscene_Stop(0x7C);
            }
        }
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void func_80B742F8(EnJg* this, GlobalContext* globalCtx) {
    u8 sp27 = func_80152498(&globalCtx->msgCtx);
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);

    if (this->animationIndex == EN_JG_ANIMATION_SURPRISE_START) {
        if (currentFrame == lastFrame) {
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_LOOP;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        }
    } else if (this->animationIndex == EN_JG_ANIMATION_SURPRISE_LOOP) {
        if ((sp27 == 5) && (func_80147624(globalCtx) != 0)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->flags &= ~EN_JG_FLAG_4;
            this->animationIndex = EN_JG_ANIMATION_WALK;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74440;
        }
    } else if (this->animationIndex == EN_JG_ANIMATION_WALK) {
        Math_ApproachF(&this->actor.speedXZ, 0.0f, 0.2f, 1.0f);
        func_80B751F8(this, globalCtx);
    }
}

void func_80B74440(EnJg* this, GlobalContext* globalCtx) {
    s16 phi_a1;
    f32 sp30;

    if (this->path != NULL) {
        phi_a1 = func_80B73B98(this->path, this->unk_1E4, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            phi_a1 = this->actor.wallYaw;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, phi_a1, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (func_80B73C58(this, this->path, this->unk_1E4)) {
            if (this->unk_1E4 >= (this->path->count - 1)) {
                this->animationIndex = EN_JG_ANIMATION_WALK;
                this->actionFunc = func_80B742F8;
            } else {
                this->unk_1E4++;
                Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
            }
        } else {
            Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
        }
    }

    func_80B751F8(this, globalCtx);
}

void func_80B74550(EnJg* this, GlobalContext* globalCtx) {
    u8 sp27 = func_80152498(&globalCtx->msgCtx);
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);
    u16 temp;

    if ((this->animationIndex == EN_JG_ANIMATION_SURPRISE_START) && (currentFrame == lastFrame)) {
        this->animationIndex = EN_JG_ANIMATION_SURPRISE_LOOP;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
    }

    if ((sp27 == 5) && (func_80147624(globalCtx))) {
        temp = this->textId;
        if ((temp == 0xDB4) || (temp == 0xDB5) || (temp == 0xDC4) || (temp == 0xDC6)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->flags &= ~EN_JG_FLAG_4;
            this->actionFunc = func_80B747C8;
            return;
        }

        temp = this->textId;
        if ((temp == 0xDBB) || (temp == 0xDBC)) {
            if (!(gSaveContext.weekEventReg[0x18] & 0x80)) {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->flags &= ~EN_JG_FLAG_4;
                this->actionFunc = func_80B747C8;
            } else if (((gSaveContext.weekEventReg[0x18] & 0x40) != 0) ||
                       (CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO))) {
                this->textId = func_80B74E5C(this);
                func_801518B0(globalCtx, this->textId, &this->actor);
                this->actionFunc = func_80B73F1C;
            } else {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->flags &= ~EN_JG_FLAG_4;
                this->cutscene = func_80B73DF4(this);
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                }
                ActorCutscene_SetIntentToPlay(this->cutscene);
                this->actionFunc = func_80B74B54;
            }
        } else {
            this->textId = func_80B74E5C(this);
            func_801518B0(globalCtx, this->textId, &this->actor);
            this->actionFunc = func_80B73F1C;
        }
    }
}

void func_80B747C8(EnJg* this, GlobalContext* globalCtx) {
    if (this->animationIndex != EN_JG_ANIMATION_WALK) {
        this->animationIndex = EN_JG_ANIMATION_WALK;
        this->freezeTimer = 1000;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = func_80B74440;
    } else {
        this->freezeTimer = 1000;
        this->actionFunc = func_80B74440;
    }
}

void EnJg_Freeze(EnJg* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);

    if (this->action == EN_JG_ACTION_SPAWNING) {
        this->action = EN_JG_ACTION_UNK2;
        this->freezeTimer = 1000;
        this->skelAnime.curFrame = lastFrame;
        this->icePoly = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                    this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                    this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
        this->animationIndex = EN_JG_ANIMATION_FROZEN_LOOP;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = EnJg_FrozenIdle;
    } else if (this->animationIndex == EN_JG_ANIMATION_FROZEN_START) {
        this->action = EN_JG_ACTION_UNK2;
        if (currentFrame == lastFrame) {
            this->freezeTimer = 1000;
            this->icePoly = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                        this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
            this->animationIndex = EN_JG_ANIMATION_FROZEN_LOOP;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_FrozenIdle;
        }
    }
}

void EnJg_FrozenIdle(EnJg* this, GlobalContext* globalCtx) {
    if (this->icePoly->update == NULL) {
        this->icePoly = NULL;
        if (this->animationIndex == EN_JG_ANIMATION_FROZEN_LOOP) {
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                this->animationIndex = EN_JG_ANIMATION_IDLE;
                if (this->textId == 0xDAC) {
                    func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
                    this->actionFunc = func_80B7406C;
                } else {
                    this->freezeTimer = 1000;
                    func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
                    this->actionFunc = func_80B74440;
                }
            }
        }
    } else {
        if (func_800B84D0(&this->actor, globalCtx)) {
            // Tatl tells you he's frozen solid
            func_801518B0(globalCtx, 0x236, &this->actor);
            this->actionFunc = EnJg_FrozenTalking;
        } else if (this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
}

void EnJg_FrozenTalking(EnJg* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx) != 0) {
        globalCtx->msgCtx.unk11F22 = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = EnJg_FrozenIdle;
    }
}

void func_80B74B54(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->actionFunc = func_80B74BC8;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void func_80B74BC8(EnJg* this, GlobalContext* globalCtx) {
    s32 pad;

    if (func_800EE29C(globalCtx, 0x1D6)) {
        u32 temp_v0 = func_800EE200(globalCtx, 0x1D6);

        if (this->csAction != globalCtx->csCtx.npcActions[temp_v0]->unk0) {
            this->csAction = globalCtx->csCtx.npcActions[temp_v0]->unk0;

            switch (globalCtx->csCtx.npcActions[temp_v0]->unk0) {
                case 1:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_IDLE_2;
                    if (this->drum != NULL) {
                        Actor_MarkForDeath(this->drum);
                        this->drum = NULL;
                    }
                    break;

                case 2:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_TAKING_OUT_DRUM;
                    break;

                case 3:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_DRUM_IDLE;
                    break;

                case 4:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_PLAYING_DRUM;
                    break;

                case 5:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_THINKING;
                    break;

                case 6:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_REMEMBERING;
                    break;

                case 7:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_STRONG_REMEMBERING;
                    break;

                case 8:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_DEPRESSED;
                    break;

                case 9:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_CRADLE;
                    break;

                default:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_IDLE;
                    break;
            }
            func_8013BC6C(&this->skelAnime, sAnimations, this->cutsceneAnimationIndex);
        }

        if ((!(this->flags & EN_JG_FLAG_DRUM_SPAWNED)) &&
            (((this->cutsceneAnimationIndex == EN_JG_ANIMATION_TAKING_OUT_DRUM) &&
              (Animation_OnFrame(&this->skelAnime, 14.0f)) && (this->action != EN_JG_ACTION_LULLABY_INTRO_CS)) ||
             (((this->cutsceneAnimationIndex == EN_JG_ANIMATION_DRUM_IDLE) ||
               (this->cutsceneAnimationIndex == EN_JG_ANIMATION_PLAYING_DRUM)) &&
              (this->action == EN_JG_ACTION_LULLABY_INTRO_CS)))) {
            this->flags |= EN_JG_FLAG_DRUM_SPAWNED;
            this->drum = Actor_SpawnAsChildAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_OBJ_JG_GAKKI, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                this->actor.params, this->actor.cutscene, this->actor.unk20, NULL);
        }

        if (this->cutsceneAnimationIndex == EN_JG_ANIMATION_TAKING_OUT_DRUM) {
            if (Animation_OnFrame(&this->skelAnime, 23.0f)) {
                func_8019F1C0(&sSfxPos, NA_SE_EV_WOOD_BOUND_S);
            } else if (Animation_OnFrame(&this->skelAnime, 38.0f)) {
                func_8019F1C0(&sSfxPos, NA_SE_EV_OBJECT_SLIDE);
            }
        }
    } else {
        this->csAction = 99;
        this->freezeTimer = 1000;
        gSaveContext.weekEventReg[0x18] |= 0x40;
        this->actionFunc = func_80B7406C;
    }
}

s32 func_80B74E5C(EnJg* this) {
    switch (this->textId) {
        case 0xDAC:
            return 0xDAD;

        case 0xDAE:
            return 0xDB0;

        case 0xDB0:
            return 0xDB3;

        case 0xDB3:
            return 0xDB4;

        case 0xDB6:
            return 0xDB7;

        case 0xDB7:
            return 0xDBA;

        case 0xDBA:
            return 0xDBB;

        case 0xDBB:
        case 0xDBC:
            return 0xDC6;

        case 0xDCB:
            return 0xDCC;

        case 0xDDE:
            return 0xDDF;

        case 0xDDF:
            return 0xDE0;

        case 0xDCD:
            return 0xDCE;

        case 0xDCE:
            return 0xDCF;

        case 0xDCF:
            this->unk_3D0 = 3;
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->actionFunc = func_80B741F8;
            return 0xDD0;

        case 0xDD0:
            func_80B73E3C(this);
            return 0xDD1;

        case 0xDD1:
            switch (this->unk_3D0) {
                case 3:
                    this->unk_3D0 = 4;
                    func_80B73E3C(this);
                    return 0xDD2;

                case 4:
                    this->unk_3D0 = 5;
                    func_80B73E3C(this);
                    return 0xDD3;

                case 5:
                    this->unk_3D0 = 6;
                    func_80B73E3C(this);
                    return 0xDD4;

                default:
                    return 0xDD4;
            }
            break;

        case 0xDD2:
            func_80B73E3C(this);
            return 0xDD1;

        case 0xDD3:
            func_80B73E3C(this);
            return 0xDD1;

        case 0xDD4:
            func_80B73E3C(this);
            return 0xDD5;

        case 0xDD5:
            this->unk_3D0 = 7;
            func_80B73E3C(this);
            return 0xDD6;

        case 0xDD6:
            func_80B73E3C(this);
            return 0xDD7;

        case 0xDD7:
            this->unk_3D0 = 0xA;
            func_80B73E3C(this);
            this->flags &= ~EN_JG_FLAG_1;
            return 0xDD8;

        case 0xDD8:
            return 0xDD9;

        case 0xDD9:
            return 0xDDA;

        case 0xDDA:
            return 0xDDB;

        case 0xDDB:
            return 0xDDC;

        case 0xDDC:
            gSaveContext.weekEventReg[0x4D] |= 0x80;
            return 0xDDD;

        default:
            return 0;
    }
}

s32 func_80B750A0(EnJg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actor.params & 1) == 0) {
        if (player->transformation == PLAYER_FORM_GORON) {
            if ((gSaveContext.weekEventReg[0x18] & 0x10) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) ||
                CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
                return 0xDBC;
            }
            return 0xDB6;
        }
        if (gSaveContext.weekEventReg[0x18] & 0x20) {
            return 0xDB5;
        }
        return 0xDAE;
    }

    if (player->transformation == PLAYER_FORM_GORON) {
        if (gSaveContext.weekEventReg[0x4D] & 0x80) {
            return 0xDDE;
        }
        return 0xDCD;
    }

    return 0xDCB;
}

void EnJg_SpawnBreath(EnJg* this, GlobalContext* globalCtx) {
    s16 scale = (Rand_ZeroOne() * 20.0f) + 30.0f;

    if (globalCtx->state.frames % 8 == 0) {
        EffectSsIceSmoke_Spawn(globalCtx, &this->breathPos, &this->breathVelocity, &this->breathAccel, scale);
    }
}

void func_80B751F8(EnJg* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);

    if (func_800B84D0(&this->actor, globalCtx)) {
        this->flags |= EN_JG_FLAG_4;
        this->actor.speedXZ = 0.0f;

        if (this->textId == 0xDAC) {
            this->action = EN_JG_ACTION_UNK0;
        } else if (this->textId == 0xDAE) {
            gSaveContext.weekEventReg[0x18] |= 0x20;
        } else if (this->textId == 0xDB6) {
            gSaveContext.weekEventReg[0x18] |= 0x10;
        }

        func_801518B0(globalCtx, this->textId, &this->actor);
        this->actionFunc = func_80B73F1C;
    } else {
        if ((this->actor.xzDistToPlayer < 100.0f) || (this->actor.isTargeted)) {
            func_800B863C(&this->actor, globalCtx);
            if (this->action == EN_JG_ACTION_UNK0) {
                this->textId = func_80B750A0(this, globalCtx);
            }
        }

        this->freezeTimer--;
        if ((this->freezeTimer <= 0) && (currentFrame == lastFrame)) {
            this->animationIndex = EN_JG_ANIMATION_FROZEN_START;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            func_8019F1C0(&sSfxPos, NA_SE_EV_FREEZE_S);
            this->actionFunc = EnJg_Freeze;
        }
    }
}

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnJg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGoronElderSkel, &gGoronElderIdleAnim, this->jointTable,
                       this->morphTable, EN_JG_LIMB_MAX);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    Actor_SetScale(&this->actor, 0.01f);

    if ((thisx->params & 1) == 0) {
        if (globalCtx->sceneNum == SCENE_SPOT00 && gSaveContext.sceneSetupIndex == 7 && globalCtx->csCtx.unk_12 == 0) {
            this->animationIndex = EN_JG_ANIMATION_IDLE;
            this->action = EN_JG_ACTION_LULLABY_INTRO_CS;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74BC8;
        } else {
            this->path = func_8013D648(globalCtx, EN_JG_GET_PATH(thisx), 0x3F);
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_START;
            this->action = EN_JG_ACTION_SPAWNING;
            this->freezeTimer = 1000;
            this->textId = 0xDAC;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Freeze;
        }
    } else {
        this->animationIndex = EN_JG_ANIMATION_IDLE;
        this->cutscene = this->actor.cutscene;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = func_80B7408C;
    }
}

void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnJg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    if (this->actionFunc != EnJg_FrozenIdle && this->actionFunc != EnJg_FrozenTalking) {
        EnJg_CheckCollision(this, globalCtx);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        SkelAnime_Update(&this->skelAnime);

        if (this->action != EN_JG_ACTION_LULLABY_INTRO_CS && ((this->actor.params & 1) == 0)) {
            EnJg_SpawnBreath(this, globalCtx);
        }

        func_800E9250(globalCtx, &this->actor, &this->unusedRotation1, &this->unusedRotation2, this->actor.focus.pos);
    }
    this->actionFunc(this, globalCtx);
}

s32 EnJg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnJg* this = THIS;

    if (limbIndex == EN_JG_LIMB_ROOT) {
        if (this->flags & EN_JG_FLAG_4) {
            Math_SmoothStepToS(&this->rootRotationWhenTalking, this->actor.yawTowardsPlayer - this->actor.shape.rot.y,
                               5, 0x1000, 0x100);
            Matrix_RotateY(this->rootRotationWhenTalking, MTXMODE_APPLY);
        } else {
            Math_SmoothStepToS(&this->rootRotationWhenTalking, 0, 5, 0x1000, 0x100);
            Matrix_RotateY(this->rootRotationWhenTalking, MTXMODE_APPLY);
        }
    }
    return false;
}

void EnJg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnJg* this = THIS;

    if (limbIndex == EN_JG_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&sFocusOffset, &this->actor.focus.pos);
    }

    if (limbIndex == EN_JG_LIMB_LOWER_LIP) {
        Matrix_MultiplyVector3fByState(&sBreathPosOffset, &this->breathPos);
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_MultiplyVector3fByState(&sBreathVelOffset, &this->breathVelocity);
        Matrix_MultiplyVector3fByState(&sBreathAccelOffset, &this->breathAccel);
    }
}

void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnJg_OverrideLimbDraw, EnJg_PostLimbDraw, &this->actor);
}
