/*
 * File: z_en_jg.c
 * Overlay: ovl_En_Jg
 * Description: Goron Elder
 */

#include "z_en_jg.h"
#include "overlays/actors/ovl_En_S_Goro/z_en_s_goro.h"
#include "overlays/actors/ovl_Obj_Ice_Poly/z_obj_ice_poly.h"
#include "overlays/actors/ovl_Obj_Jg_Gakki/z_obj_jg_gakki.h"
#include "objects/object_jg/object_jg.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B73F1C(EnJg* this, GlobalContext* globalCtx);
void func_80B7406C(EnJg* this, GlobalContext* globalCtx);
void func_80B7408C(EnJg* this, GlobalContext* globalCtx);
void func_80B74134(EnJg* this, GlobalContext* globalCtx);
void func_80B741F8(EnJg* this, GlobalContext* globalCtx);
void func_80B742F8(EnJg* this, GlobalContext* globalCtx);
void func_80B74440(EnJg* this, GlobalContext* globalCtx);
void func_80B74550(EnJg* this, GlobalContext* globalCtx);
void func_80B747C8(EnJg* this, GlobalContext* globalCtx);
void func_80B74840(EnJg* this, GlobalContext* globalCtx);
void func_80B749D0(EnJg* this, GlobalContext* globalCtx);
void func_80B74AD8(EnJg* this, GlobalContext* globalCtx);
void func_80B74B54(EnJg* this, GlobalContext* globalCtx);
void func_80B74BC8(EnJg* this, GlobalContext* globalCtx);
u16 func_80B74E5C(EnJg* this);
u16 func_80B750A0(EnJg* this, GlobalContext* globalCtx);
void func_80B751F8(EnJg* this, GlobalContext* globalCtx);

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
    { &object_jg_Anim_01ADC0, 1.0f, 0, -1, 0, -10 }, { &object_jg_Anim_009440, 1.0f, 0, -1, 0, -10 },
    { &object_jg_Anim_00BDD8, 1.0f, 0, -1, 0, -10 }, { &object_jg_Anim_00C7A8, 1.0f, 0, -1, 0, -10 },
    { &object_jg_Anim_00DB54, 1.0f, 0, -1, 2, -10 }, { &object_jg_Anim_00E8FC, 1.0f, 0, -1, 0, -10 },
    { &object_jg_Anim_01436C, 1.0f, 0, -1, 0, -10 }, { &object_jg_Anim_00DB54, 2.0f, 0, -1, 2, 0 },
    { &object_jg_Anim_00DB54, -2.0f, 0, -1, 2, 0 },  { &object_jg_Anim_009440, -1.0f, 0, -1, 0, -10 },
    { &object_jg_Anim_011F50, 1.0f, 0, -1, 2, 0 },   { &object_jg_Anim_0129F4, 1.0f, 0, -1, 0, 0 },
    { &object_jg_Anim_013DD8, 1.0f, 1, 44, 2, 0 },   { &object_jg_Anim_0077CC, 1.0f, 0, -1, 0, 0 },
    { &object_jg_Anim_00D630, 1.0f, 0, -1, 2, 0 },   { &object_jg_Anim_00FE48, 1.0f, 0, -1, 2, 0 },
    { &object_jg_Anim_018CE4, 1.0f, 0, -1, 0, 0 },   { &object_jg_Anim_01ADC0, 1.0f, 0, -1, 0, 0 },
    { &object_jg_Anim_00A07C, 1.0f, 0, -1, 0, 0 },
};

static Vec3f D_80B759A8 = { 0.0f, 0.0f, 0.0f };

EnSGoro* func_80B73A90(GlobalContext* globalCtx, u8 arg1) {
    Actor* actor = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_EN_S_GORO) && (ENSGORO_GET_F(actor) == arg1)) {
            return (EnSGoro*)actor;
        }
        actor = actor->next;
    }
    return NULL;
}

void func_80B73AE4(EnJg* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 30.0f, 30.0f, 7);
}

s16 func_80B73B98(Path* path, s32 arg1, Vec3f* arg2, f32* arg3) {
    f32 phi_f14;
    f32 phi_f12;
    Vec3s* points;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        phi_f14 = points[0].x - arg2->x;
        phi_f12 = points[0].z - arg2->z;
    } else {
        phi_f14 = 0.0f;
        phi_f12 = 0.0f;
    }

    *arg3 = SQ(phi_f14) + SQ(phi_f12);

    return RADF_TO_BINANG(Math_Acot2F(phi_f12, phi_f14));
}

s32 func_80B73C58(EnJg* this, Path* path, s32 arg2_) {
    Vec3s* sp5C = Lib_SegmentedToVirtual(path->points);
    s32 sp58 = path->count;
    s32 arg2 = arg2_;
    s32 ret = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);
    if (arg2 == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if ((sp58 - 1) == arg2) {
        phi_f12 = sp5C[sp58 - 1].x - sp5C[sp58 - 2].x;
        phi_f14 = sp5C[sp58 - 1].z - sp5C[sp58 - 2].z;
    } else {
        phi_f12 = sp5C[arg2 + 1].x - sp5C[arg2 - 1].x;
        phi_f14 = sp5C[arg2 + 1].z - sp5C[arg2 - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        ret = true;
    }
    return ret;
}

s16 func_80B73DF4(EnJg* this) {
    s16 temp = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    if (temp > 0) {
        return this->actor.cutscene;
    }
    return ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
}

void func_80B73E3C(EnJg* this) {
    ActorCutscene_Stop(this->unk_3C8);
    if (this->unk_3D0 == 10) {
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
            return;

        default:
            this->unk_3CC &= ~1;
            return;
    }
}

void func_80B73F1C(EnJg* this, GlobalContext* globalCtx) {
    switch (this->unk_3CE) {
        case 0xDAC:
            this->unk_39E = 3;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74550;
            break;

        case 0xDAD:
            this->unk_39E = 4;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B742F8;
            break;

        case 0xDB7:
            this->unk_39E = 4;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74550;
            break;

        case 0xDAE:
        case 0xDB3:
        case 0xDB6:
        case 0xDBA:
        case 0xDBD:
        case 0xDC4:
            this->unk_39E = 0;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74550;
            break;

        case 0xDB0:
        case 0xDBB:
        case 0xDBC:
        case 0xDC6:
            this->unk_39E = 6;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74550;
            break;

        case 0xDB4:
        case 0xDB5:
            this->unk_39E = 2;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
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
    } else if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
        func_800B863C(&this->actor, globalCtx);
        this->unk_3CE = func_80B750A0(this, globalCtx);
    }
}

void func_80B74134(EnJg* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        if ((this->unk_3CE == 0xDCC) || (this->unk_3CE == 0xDDD) || (this->unk_3CE == 0xDE0)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3CC &= ~4;
            this->actionFunc = func_80B7408C;
        } else {
            this->unk_3CE = func_80B74E5C(this);
            func_801518B0(globalCtx, this->unk_3CE, &this->actor);
        }
    }
}

void func_80B741F8(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_3C8)) {
        switch (this->unk_3CE) {
            case 0xDD0:
            case 0xDD2:
            case 0xDD3:
            case 0xDD4:
            case 0xDD6:
                this->unk_144 = func_80B73A90(globalCtx, this->unk_3D0);
                ActorCutscene_Start(this->unk_3C8, &this->unk_144->actor);
                func_800E0308(globalCtx->cameraPtrs[MAIN_CAM], &this->unk_144->actor);
                break;

            default:
                ActorCutscene_Start(this->unk_3C8, &this->actor);
                func_800E0308(globalCtx->cameraPtrs[MAIN_CAM], &this->unk_144->actor);
                break;
        }
        this->actionFunc = func_80B74134;
        return;
    }

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        if (this->unk_3D0 == 10) {
            this->actionFunc = func_80B74134;
        } else {
            ActorCutscene_Stop(0x7C);
        }
    }
    ActorCutscene_SetIntentToPlay(this->unk_3C8);
}

void func_80B742F8(EnJg* this, GlobalContext* globalCtx) {
    u8 sp27 = func_80152498(&globalCtx->msgCtx);
    s16 sp24 = this->skelAnime.curFrame;
    s16 frame = Animation_GetLastFrame(sAnimations[this->unk_39E].animationSeg);

    if (this->unk_39E == 4) {
        if (sp24 == frame) {
            this->unk_39E = 5;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
        }
    } else if (this->unk_39E == 5) {
        if ((sp27 == 5) && func_80147624(globalCtx)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3CC &= ~4;
            this->unk_39E = 1;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74440;
        }
    } else if (this->unk_39E == 1) {
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

        Math_SmoothStepToS(&this->actor.world.rot.y, phi_a1, 4, 1000, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (func_80B73C58(this, this->path, this->unk_1E4)) {
            if (this->unk_1E4 >= (this->path->count - 1)) {
                this->unk_39E = 1;
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
    s16 sp24 = this->skelAnime.curFrame;
    s16 frame = Animation_GetLastFrame(sAnimations[this->unk_39E].animationSeg);
    u16 temp;

    if ((this->unk_39E == 4) && (sp24 == frame)) {
        this->unk_39E = 5;
        func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
    }

    if ((sp27 == 5) && func_80147624(globalCtx)) {
        temp = this->unk_3CE;

        if ((temp == 0xDB4) || (temp == 0xDB5) || (temp == 0xDC4) || (temp == 0xDC6)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3CC &= ~4;
            this->actionFunc = func_80B747C8;
            return;
        }

        temp = this->unk_3CE;
        if ((temp == 0xDBB) || (temp == 0xDBC)) {
            if (!(gSaveContext.weekEventReg[24] & 0x80)) {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_3CC &= ~4;
                this->actionFunc = func_80B747C8;
            } else if ((gSaveContext.weekEventReg[24] & 0x40) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) ||
                       CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
                this->unk_3CE = func_80B74E5C(this);
                func_801518B0(globalCtx, this->unk_3CE, &this->actor);
                this->actionFunc = func_80B73F1C;
            } else {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_3CC &= ~4;
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
    if (this->unk_39E != 1) {
        this->unk_39E = 1;
        this->unk_3A2 = 1000;
        func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
        this->actionFunc = func_80B74440;
    } else {
        this->unk_3A2 = 1000;
        this->actionFunc = func_80B74440;
    }
}

void func_80B74840(EnJg* this, GlobalContext* globalCtx) {
    s16 sp3E = this->skelAnime.curFrame;
    s16 frame = Animation_GetLastFrame(sAnimations[this->unk_39E].animationSeg);

    if (this->unk_3A0 == 1) {
        this->unk_3A0 = 2;
        this->unk_3A2 = 1000;
        this->skelAnime.curFrame = frame;
        this->unk_148 = (ObjIcePoly*)Actor_Spawn(
            &globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x, this->actor.world.pos.y,
            this->actor.world.pos.z, this->actor.world.rot.x, this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
        this->unk_39E = 8;
        func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
        this->actionFunc = func_80B749D0;
    } else if (this->unk_39E == 7) {
        this->unk_3A0 = 2;
        if (sp3E == frame) {
            this->unk_3A2 = 1000;
            this->unk_148 =
                (ObjIcePoly*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                         this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                         this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
            this->unk_39E = 8;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B749D0;
        }
    }
}

void func_80B749D0(EnJg* this, GlobalContext* globalCtx) {
    if (this->unk_148->actor.update == NULL) {
        this->unk_148 = NULL;
        if (this->unk_39E == 8) {
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                this->unk_39E = 0;
                if (this->unk_3CE == 0xDAC) {
                    func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
                    this->actionFunc = func_80B7406C;
                } else {
                    this->unk_3A2 = 1000;
                    func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
                    this->actionFunc = func_80B74440;
                }
            }
        }
    } else if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, 0x236, &this->actor);
        this->actionFunc = func_80B74AD8;
    } else if (this->actor.isTargeted) {
        func_800B863C(&this->actor, globalCtx);
    }
}

void func_80B74AD8(EnJg* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 6) && func_80147624(globalCtx)) {
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

    if (func_800EE29C(globalCtx, 0x1D6)) {
        u32 temp_v0 = func_800EE200(globalCtx, 0x1D6);

        if (globalCtx->csCtx.npcActions[temp_v0]->unk0 != this->unk_3CB) {
            this->unk_3CB = globalCtx->csCtx.npcActions[temp_v0]->unk0;

            switch (globalCtx->csCtx.npcActions[temp_v0]->unk0) {
                case 1:
                    this->unk_3CA = 17;
                    if (this->unk_1E8 != NULL) {
                        Actor_MarkForDeath(&this->unk_1E8->actor);
                        this->unk_1E8 = NULL;
                    }
                    break;

                case 2:
                    this->unk_3CA = 10;
                    break;

                case 3:
                    this->unk_3CA = 11;
                    break;

                case 4:
                    this->unk_3CA = 12;
                    break;

                case 5:
                    this->unk_3CA = 13;
                    break;

                case 6:
                    this->unk_3CA = 14;
                    break;

                case 7:
                    this->unk_3CA = 15;
                    break;

                case 8:
                    this->unk_3CA = 16;
                    break;

                case 9:
                    this->unk_3CA = 18;
                    break;

                default:
                    this->unk_3CA = 0;
                    break;
            }
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_3CA);
        }

        if (!(this->unk_3CC & 8) &&
            (((this->unk_3CA == 10) && Animation_OnFrame(&this->skelAnime, 14.0f) && (this->unk_3A0 != 3)) ||
             (((this->unk_3CA == 11) || (this->unk_3CA == 12)) && (this->unk_3A0 == 3)))) {
            this->unk_3CC |= 8;
            this->unk_1E8 = (ObjJgGakki*)Actor_SpawnAsChildAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_OBJ_JG_GAKKI, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                this->actor.params, this->actor.cutscene, this->actor.unk20, NULL);
        }

        if (this->unk_3CA == 10) {
            if (Animation_OnFrame(&this->skelAnime, 23.0f)) {
                func_8019F1C0(&D_80B759A8, NA_SE_EV_WOOD_BOUND_S);
            } else if (Animation_OnFrame(&this->skelAnime, 38.0f)) {
                func_8019F1C0(&D_80B759A8, NA_SE_EV_OBJECT_SLIDE);
            }
        }
        return;
    }

    this->unk_3CB = 99;
    this->unk_3A2 = 1000;
    gSaveContext.weekEventReg[24] |= 0x40;
    this->actionFunc = func_80B7406C;
}

u16 func_80B74E5C(EnJg* this) {
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
            this->unk_3D0 = 10;
            func_80B73E3C(this);
            this->unk_3CC &= ~1;
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
            gSaveContext.weekEventReg[77] |= 0x80;
            return 0xDDD;
    }
    return 0;
}

u16 func_80B750A0(EnJg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!ENSGORO_GET_1(&this->actor)) {
        if (player->transformation == PLAYER_FORM_GORON) {
            if ((gSaveContext.weekEventReg[24] & 0x10) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) ||
                CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
                return 0xDBC;
            }
            return 0xDB6;
        }

        if (gSaveContext.weekEventReg[24] & 0x20) {
            return 0xDB5;
        }
        return 0xDAE;
    }

    if (player->transformation == PLAYER_FORM_GORON) {
        if (gSaveContext.weekEventReg[77] & 0x80) {
            return 0xDDE;
        }
        return 0xDCD;
    }
    return 0xDCB;
}

void func_80B7517C(EnJg* this, GlobalContext* globalCtx) {
    s16 rand = (Rand_ZeroOne() * 20.0f) + 30.0f;

    if ((globalCtx->state.frames % 8) == 0) {
        EffectSsIceSmoke_Spawn(globalCtx, &this->unk_3A4, &this->unk_3B0, &this->unk_3BC, rand);
    }
}

void func_80B751F8(EnJg* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 sp24 = Animation_GetLastFrame(sAnimations[this->unk_39E].animationSeg);

    if (func_800B84D0(&this->actor, globalCtx)) {
        this->unk_3CC |= 4;
        this->actor.speedXZ = 0.0f;

        if (this->unk_3CE == 0xDAC) {
            this->unk_3A0 = 0;
        } else if (this->unk_3CE == 0xDAE) {
            gSaveContext.weekEventReg[24] |= 0x20;
        } else if (this->unk_3CE == 0xDB6) {
            gSaveContext.weekEventReg[24] |= 0x10;
        }

        func_801518B0(globalCtx, this->unk_3CE, &this->actor);
        this->actionFunc = func_80B73F1C;
    } else {
        if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
            if (this->unk_3A0 == 0) {
                this->unk_3CE = func_80B750A0(this, globalCtx);
            }
        }

        this->unk_3A2--;
        if ((this->unk_3A2 <= 0) && (sp26 == sp24)) {
            this->unk_39E = 7;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            func_8019F1C0(&D_80B759A8, NA_SE_EV_FREEZE_S);
            this->actionFunc = func_80B74840;
        }
    }
}

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnJg* this = THIS;

    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_jg_Skel_01AFF0, &object_jg_Anim_01ADC0, this->jointTable,
                       this->morphTable, 35);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);
    CollisionCheck_SetInfo2(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);

    Actor_SetScale(thisx, 0.01f);

    if (!ENSGORO_GET_1(thisx)) {
        if ((globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 7) &&
            (globalCtx->csCtx.unk_12 == 0)) {
            this->unk_39E = 0;
            this->unk_3A0 = 3;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74BC8;
        } else {
            this->path = func_8013D648(globalCtx, ENSGORO_GET_FC00(thisx), 0x3F);
            this->unk_39E = 4;
            this->unk_3A0 = 1;
            this->unk_3A2 = 1000;
            this->unk_3CE = 0xDAC;
            func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
            this->actionFunc = func_80B74840;
        }
    } else {
        this->unk_39E = 0;
        this->unk_3C8 = thisx->cutscene;
        func_8013BC6C(&this->skelAnime, sAnimations, this->unk_39E);
        this->actionFunc = func_80B7408C;
    }
}

void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnJg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    if ((this->actionFunc != func_80B749D0) && (this->actionFunc != func_80B74AD8)) {
        func_80B73AE4(this, globalCtx);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        SkelAnime_Update(&this->skelAnime);

        if ((this->unk_3A0 != 3) && !ENSGORO_GET_1(&this->actor)) {
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
            Math_SmoothStepToS(&this->unk_39C, BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y), 5,
                               0x1000, 0x100);
            Matrix_RotateY(this->unk_39C, 1);
        } else {
            Math_SmoothStepToS(&this->unk_39C, 0, 5, 0x1000, 0x100);
            Matrix_RotateY(this->unk_39C, 1);
        }
    }
    return false;
}

void func_80B75708(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80B759B4 = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_80B759C0 = { 1000.0f, -500.0f, 0.0f };
    static Vec3f D_80B759CC = { 0.0f, 0.0f, 0.75f };
    static Vec3f D_80B759D8 = { 0.0f, 0.0f, -0.07f };
    EnJg* this = THIS;

    if (limbIndex == 21) {
        Matrix_MultiplyVector3fByState(&D_80B759B4, &this->actor.focus.pos);
    }

    if (limbIndex == 22) {
        Matrix_MultiplyVector3fByState(&D_80B759C0, &this->unk_3A4);
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_MultiplyVector3fByState(&D_80B759CC, &this->unk_3B0);
        Matrix_MultiplyVector3fByState(&D_80B759D8, &this->unk_3BC);
    }
}

void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B75658, func_80B75708, &this->actor);
}
