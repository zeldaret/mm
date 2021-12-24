/*
 * File: z_en_jg.c
 * Overlay: ovl_En_Jg
 * Description: Goron Elder
 */

#include "z_en_jg.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B74AD8(EnJg* this, GlobalContext* globalCtx);
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
void func_80B749D0(EnJg* this, GlobalContext* globalCtx);

extern AnimationHeader D_060077CC;
extern AnimationHeader D_06009440;
extern AnimationHeader D_0600A07C;
extern AnimationHeader D_0600BDD8;
extern AnimationHeader D_0600C7A8;
extern AnimationHeader D_0600D630;
extern AnimationHeader D_0600DB54;
extern AnimationHeader D_0600E8FC;
extern AnimationHeader D_0600FE48;
extern AnimationHeader D_06011F50;
extern AnimationHeader D_060129F4;
extern AnimationHeader D_06013DD8;
extern AnimationHeader D_0601436C;
extern AnimationHeader D_06018CE4;
extern AnimationHeader D_0601ADC0;
extern FlexSkeletonHeader D_0601AFF0;

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
    { &D_0601ADC0, 1.0f, 0, -1, 0, -10 },  { &D_06009440, 1.0f, 0, -1, 0, -10 }, { &D_0600BDD8, 1.0f, 0, -1, 0, -10 },
    { &D_0600C7A8, 1.0f, 0, -1, 0, -10 },  { &D_0600DB54, 1.0f, 0, -1, 2, -10 }, { &D_0600E8FC, 1.0f, 0, -1, 0, -10 },
    { &D_0601436C, 1.0f, 0, -1, 0, -10 },  { &D_0600DB54, 2.0f, 0, -1, 2, 0 },   { &D_0600DB54, -2.0f, 0, -1, 2, 0 },
    { &D_06009440, -1.0f, 0, -1, 0, -10 }, { &D_06011F50, 1.0f, 0, -1, 2, 0 },   { &D_060129F4, 1.0f, 0, -1, 0, 0 },
    { &D_06013DD8, 1.0f, 1, 44, 2, 0 },    { &D_060077CC, 1.0f, 0, -1, 0, 0 },   { &D_0600D630, 1.0f, 0, -1, 2, 0 },
    { &D_0600FE48, 1.0f, 0, -1, 2, 0 },    { &D_06018CE4, 1.0f, 0, -1, 0, 0 },   { &D_0601ADC0, 1.0f, 0, -1, 0, 0 },
    { &D_0600A07C, 1.0f, 0, -1, 0, 0 },
};

static Vec3f D_80B759A8 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80B759B4 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80B759C0 = { 1000.0f, -500.0f, 0.0f };

static Vec3f D_80B759CC = { 0.0f, 0.0f, 0.75f };

static Vec3f D_80B759D8 = { 0.0f, 0.0f, -0.070000000298f };

Actor* func_80B73A90(GlobalContext* globalCtx, u8 arg1) {
    Actor* actorIterator;

    actorIterator = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;
    while (actorIterator != NULL) {
        if ((actorIterator->id == ACTOR_EN_S_GORO) && ((actorIterator->params & 0xF) == arg1)) {
            return actorIterator;
        }
        actorIterator = actorIterator->next;
    }
    return NULL;
}

void func_80B73AE4(EnJg* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 30.0f, 30.0f, 7U);
}

s16 func_80B73B98(Path* path, s32 idx, Vec3f* pos, f32* distSQ) {
    Vec3s* points;
    f32 diffX;
    f32 diffZ;

    if (path != NULL) {
        points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
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

s32 func_80B73C58(EnJg* this, Path* path, s32 arg2) {
    Vec3s* sp5C = (Vec3s*)Lib_SegmentedToVirtual(path->points);
    s32 count = path->count;
    s32 idx = arg2;
    s32 sp50 = false;
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
    } else if ((idx + 1) == ((void)0, count)) {
        phi_f12 = sp5C[count - 1].x - sp5C[count - 2].x;
        phi_f14 = sp5C[count - 1].z - sp5C[count - 2].z;
    } else {
        phi_f12 = sp5C[idx + 1].x - sp5C[idx - 1].x;
        phi_f14 = sp5C[idx + 1].z - sp5C[idx - 1].z;
    }

    func_8017B7F8(&sp30, func_80086B30(phi_f12, phi_f14) * 10430.378f, &sp44, &sp40, &sp3C);
    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = true;
    }

    return sp50;
}

s16 func_80B73DF4(EnJg* this) {
    s16 temp = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (temp > 0) {
        return this->actor.cutscene;
    }
    return ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
}

void func_80B73E3C(EnJg* this) {
    ActorCutscene_Stop(this->unk_3C8);
    if (this->unk_3D0 == 0xA) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            this->actionFunc = func_80B74134;
        } else {
            this->unk_3C8 = 0x7C;
        }
    } else {
        this->unk_3C8 = ActorCutscene_GetAdditionalCutscene(this->unk_3C8);
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
    }
    ActorCutscene_SetIntentToPlay(this->unk_3C8);
    this->actionFunc = func_80B741F8;
    switch (this->unk_3CE) {
        case 0xDD0:
        case 0xDD2:
        case 0xDD3:
        case 0xDD4:
        case 0xDD6:
            this->unk_3CC |= 1;
            break;
        default:
            this->unk_3CC &= 0xFFFE;
            break;
    }
}

void func_80B73F1C(EnJg* this, GlobalContext* globalCtx) {
    switch (this->unk_3CE) {
        case 0xDAC:
            this->animationIndex = 3;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;
        case 0xDAD:
            this->animationIndex = 4;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B742F8;
            break;
        case 0xDB7:
            this->animationIndex = 4;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;
        case 0xDAE:
        case 0xDB3:
        case 0xDB6:
        case 0xDBA:
        case 0xDBD:
        case 0xDC4:
            this->animationIndex = 0;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;
        case 0xDB0:
        case 0xDBB:
        case 0xDBC:
        case 0xDC6:
            this->animationIndex = 6;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74550;
            break;
        case 0xDB4:
        case 0xDB5:
            this->animationIndex = 2;
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
        this->unk_3CC |= 4;
        func_801518B0(globalCtx, this->unk_3CE, &this->actor);
        this->actionFunc = func_80B74134;
    } else if (this->actor.xzDistToPlayer < 100.0f || this->actor.isTargeted) {
        func_800B863C(&this->actor, globalCtx);
        this->unk_3CE = func_80B750A0(this, globalCtx);
    }
}

void func_80B74134(EnJg* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        if ((this->unk_3CE == 0xDCC) || (this->unk_3CE == 0xDDD) || (this->unk_3CE == 0xDE0)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3CC &= 0xFFFB;
            this->actionFunc = func_80B7408C;
        } else {
            this->unk_3CE = func_80B74E5C(this);
            func_801518B0(globalCtx, this->unk_3CE, &this->actor);
        }
    }
}

void func_80B741F8(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_3C8) != 0) {
        switch (this->unk_3CE) {
            case 0xDD0:
            case 0xDD2:
            case 0xDD3:
            case 0xDD4:
            case 0xDD6:
                this->unk_144 = func_80B73A90(globalCtx, this->unk_3D0);
                ActorCutscene_Start(this->unk_3C8, this->unk_144);
                func_800E0308(globalCtx->cameraPtrs[0], this->unk_144);
                break;
            default:
                ActorCutscene_Start(this->unk_3C8, &this->actor);
                func_800E0308(globalCtx->cameraPtrs[0], this->unk_144);
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
        ActorCutscene_SetIntentToPlay(this->unk_3C8);
    }
}

void func_80B742F8(EnJg* this, GlobalContext* globalCtx) {
    u8 sp27;
    s16 currentFrame;
    s16 lastFrame;

    sp27 = func_80152498(&globalCtx->msgCtx);
    currentFrame = this->skelAnime.curFrame;
    lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);
    if (this->animationIndex == 4) {
        if (currentFrame == lastFrame) {
            this->animationIndex = 5;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        }
    } else if (this->animationIndex == 5) {
        if ((sp27 == 5) && (func_80147624(globalCtx) != 0)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3CC &= 0xFFFB;
            this->animationIndex = 1;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74440;
        }
    } else if (this->animationIndex == 1) {
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
                this->animationIndex = 1;
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
    u8 sp27;
    s16 currentFrame;
    s16 lastFrame;
    s32 temp;

    sp27 = func_80152498(&globalCtx->msgCtx);
    currentFrame = this->skelAnime.curFrame;
    lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);
    if ((this->animationIndex == 4) && (currentFrame == lastFrame)) {
        this->animationIndex = 5;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
    }
    if ((sp27 == 5) && (func_80147624(globalCtx))) {
        temp = this->unk_3CE;
        if ((temp == 0xDB4) || (temp == 0xDB5) || (temp == 0xDC4) || (temp == 0xDC6)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3CC &= ~0x4;
            this->actionFunc = func_80B747C8;
        } else if ((this->unk_3CE == 0xDBB) || (this->unk_3CE == 0xDBC)) {
            if ((gSaveContext.weekEventReg[0x18] & 0x80) == 0) {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_3CC &= ~0x4;
                this->actionFunc = func_80B747C8;
            } else if (((gSaveContext.weekEventReg[0x18] & 0x40) != 0) ||
                       (CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO))) {
                this->unk_3CE = func_80B74E5C(this);
                func_801518B0(globalCtx, this->unk_3CE, &this->actor);
                this->actionFunc = func_80B73F1C;
            } else {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_3CC &= ~0x4;
                this->unk_3C8 = func_80B73DF4(this);
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                }
                ActorCutscene_SetIntentToPlay(this->unk_3C8);
                this->actionFunc = func_80B74B54;
            }
        } else {
            this->unk_3CE = func_80B74E5C(this);
            func_801518B0(globalCtx, this->unk_3CE, &this->actor);
            this->actionFunc = func_80B73F1C;
        }
    }
}

void func_80B747C8(EnJg* this, GlobalContext* globalCtx) {
    if (this->animationIndex != 1) {
        this->animationIndex = 1;
        this->unk_3A2 = 0x3E8;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = func_80B74440;
    } else {
        this->unk_3A2 = 0x3E8;
        this->actionFunc = func_80B74440;
    }
}

void func_80B74840(EnJg* this, GlobalContext* globalCtx) {
    s16 currentFrame;
    s16 lastFrame;

    currentFrame = this->skelAnime.curFrame;
    lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);
    if (this->unk_3A0 == 1) {
        this->unk_3A0 = 2;
        this->unk_3A2 = 0x3E8;
        this->skelAnime.curFrame = lastFrame;
        this->icePoly = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                    this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                    this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
        this->animationIndex = 8;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = func_80B749D0;
    } else if (this->animationIndex == 7) {
        this->unk_3A0 = 2;
        if (currentFrame == lastFrame) {
            this->unk_3A2 = 0x3E8;
            this->icePoly = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                        this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
            this->animationIndex = 8;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B749D0;
        }
    }
}

void func_80B749D0(EnJg* this, GlobalContext* globalCtx) {
    if (this->icePoly->update == NULL) {
        this->icePoly = NULL;
        if (this->animationIndex == 8) {
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                this->animationIndex = 0;
                if (this->unk_3CE == 0xDAC) {
                    func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
                    this->actionFunc = func_80B7406C;
                } else {
                    this->unk_3A2 = 0x3E8;
                    func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
                    this->actionFunc = func_80B74440;
                }
            }
        }
    } else {
        if (func_800B84D0(&this->actor, globalCtx)) {
            func_801518B0(globalCtx, 0x236, &this->actor);
            this->actionFunc = func_80B74AD8;
        } else if (this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
}

void func_80B74AD8(EnJg* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx) != 0) {
        globalCtx->msgCtx.unk11F22 = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = func_80B749D0;
    }
}

void func_80B74B54(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_3C8)) {
        ActorCutscene_Start(this->unk_3C8, &this->actor);
        this->actionFunc = func_80B74BC8;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->unk_3C8);
    }
}

void func_80B74BC8(EnJg* this, GlobalContext* globalCtx) {
    s32 pad;
    u32 temp_v0;

    if (func_800EE29C(globalCtx, 0x1D6)) {
        temp_v0 = func_800EE200(globalCtx, 0x1D6);
        if (this->unk_3CB != globalCtx->csCtx.npcActions[temp_v0]->unk0) {
            this->unk_3CB = globalCtx->csCtx.npcActions[temp_v0]->unk0;
            switch (globalCtx->csCtx.npcActions[temp_v0]->unk0) {
                case 1:
                    this->unk_3CA = 0x11;
                    if (this->drum != NULL) {
                        Actor_MarkForDeath(this->drum);
                        this->drum = NULL;
                    }
                    break;
                case 2:
                    this->unk_3CA = 0xA;
                    break;
                case 3:
                    this->unk_3CA = 0xB;
                    break;
                case 4:
                    this->unk_3CA = 0xC;
                    break;
                case 5:
                    this->unk_3CA = 0xD;
                    break;
                case 6:
                    this->unk_3CA = 0xE;
                    break;
                case 7:
                    this->unk_3CA = 0xF;
                    break;
                case 8:
                    this->unk_3CA = 0x10;
                    break;
                case 9:
                    this->unk_3CA = 0x12;
                    break;
                default:
                    this->unk_3CA = 0;
                    break;
            }
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_3CA);
        }
        if ((!(this->unk_3CC & 8)) &&
            (((this->unk_3CA == 0xA) && (Animation_OnFrame(&this->skelAnime, 14.0f)) && (this->unk_3A0 != 3)) ||
             (((this->unk_3CA == 0xB) || (this->unk_3CA == 0xC)) && (this->unk_3A0 == 3)))) {
            this->unk_3CC |= 8;
            this->drum = Actor_SpawnAsChildAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_OBJ_JG_GAKKI, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                this->actor.params, this->actor.cutscene, this->actor.unk20, NULL);
        }
        if (this->unk_3CA == 0xA) {
            if (Animation_OnFrame(&this->skelAnime, 23.0f)) {
                func_8019F1C0(&D_80B759A8, 0x295D);
            } else if (Animation_OnFrame(&this->skelAnime, 38.0f)) {
                func_8019F1C0(&D_80B759A8, 0x295F);
            }
        }
    } else {
        this->unk_3CB = 0x63;
        this->unk_3A2 = 0x3E8;
        gSaveContext.weekEventReg[0x18] |= 0x40;
        this->actionFunc = func_80B7406C;
    }
}

s32 func_80B74E5C(EnJg* this) {
    switch (this->unk_3CE) {
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
            ActorCutscene_SetIntentToPlay(this->unk_3C8);
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
            this->unk_3CC &= 0xFFFE;
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

void func_80B7517C(EnJg* this, GlobalContext* globalCtx) {
    s16 scale = (Rand_ZeroOne() * 20.0f) + 30.0f;

    if (globalCtx->state.frames % 8 == 0) {
        EffectSsIceSmoke_Spawn(globalCtx, &this->unk_3A4, &this->unk_3B0, &this->unk_3BC, scale);
    }
}

void func_80B751F8(EnJg* this, GlobalContext* globalCtx) {
    s16 currentFrame;
    s16 lastFrame;

    currentFrame = this->skelAnime.curFrame;
    lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->unk_3CC |= 4;
        this->actor.speedXZ = 0.0f;
        if (this->unk_3CE == 0xDAC) {
            this->unk_3A0 = 0;
        } else if (this->unk_3CE == 0xDAE) {
            gSaveContext.weekEventReg[0x18] |= 0x20;
        } else if (this->unk_3CE == 0xDB6) {
            gSaveContext.weekEventReg[0x18] |= 0x10;
        }
        func_801518B0(globalCtx, this->unk_3CE, &this->actor);
        this->actionFunc = func_80B73F1C;
    } else {
        if ((this->actor.xzDistToPlayer < 100.0f) || (this->actor.isTargeted)) {
            func_800B863C(&this->actor, globalCtx);
            if (this->unk_3A0 == 0) {
                this->unk_3CE = func_80B750A0(this, globalCtx);
            }
        }
        this->unk_3A2--;
        if ((this->unk_3A2 <= 0) && (currentFrame == lastFrame)) {
            this->animationIndex = 7;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            func_8019F1C0(&D_80B759A8, 0x295C);
            this->actionFunc = func_80B74840;
        }
    }
}

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnJg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0601AFF0, &D_0601ADC0, this->jointTable, this->morphTable,
                       EN_JG_LIMB_MAX);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    if ((thisx->params & 1) == 0) {
        if (globalCtx->sceneNum == SCENE_SPOT00 && gSaveContext.sceneSetupIndex == 7 && globalCtx->csCtx.unk_12 == 0) {
            this->animationIndex = 0;
            this->unk_3A0 = 3;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74BC8;
        } else {
            this->path = func_8013D648(globalCtx, ((thisx->params & 0xFC00) >> 0xA), 0x3F);
            this->animationIndex = 4;
            this->unk_3A0 = 1;
            this->unk_3A2 = 1000;
            this->unk_3CE = 3500;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = func_80B74840;
        }
    } else {
        this->animationIndex = 0;
        this->unk_3C8 = this->actor.cutscene;
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

    if (this->actionFunc != func_80B749D0 && this->actionFunc != func_80B74AD8) {
        func_80B73AE4(this, globalCtx);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        SkelAnime_Update(&this->skelAnime);
        if (this->unk_3A0 != 3 && ((this->actor.params & 1) == 0)) {
            func_80B7517C(this, globalCtx);
        }
        func_800E9250(globalCtx, &this->actor, &this->unk_1EC, &this->unk_1F2, this->actor.focus.pos);
    }
    this->actionFunc(this, globalCtx);
}

s32 func_80B75658(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnJg* this = THIS;

    if (limbIndex == 1) {
        if (this->unk_3CC & 4) {
            Math_SmoothStepToS(&this->unk_39C, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 5, 0x1000,
                               0x100);
            Matrix_RotateY(this->unk_39C, 1);
        } else {
            Math_SmoothStepToS(&this->unk_39C, 0, 5, 0x1000, 0x100);
            Matrix_RotateY(this->unk_39C, 1);
        }
    }
    return false;
}

void func_80B75708(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnJg* this = THIS;

    if (limbIndex == EN_JG_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&D_80B759B4, &this->actor.focus.pos);
    }
    if (limbIndex == EN_JG_LIMB_LOWER_LIP) {
        Matrix_MultiplyVector3fByState(&D_80B759C0, &this->unk_3A4);
        Matrix_RotateY(this->actor.shape.rot.y, 0);
        Matrix_MultiplyVector3fByState(&D_80B759CC, &this->unk_3B0);
        Matrix_MultiplyVector3fByState(&D_80B759D8, &this->unk_3BC);
    }
}

void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B75658, func_80B75708, &this->actor);
}
