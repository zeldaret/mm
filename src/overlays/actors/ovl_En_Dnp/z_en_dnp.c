/*
 * File: z_en_dnp.c
 * Overlay: ovl_En_Dnp
 * Description: Deku Princess
 */

#include "z_en_dnp.h"

#define FLAGS 0x00000019

#define THIS ((EnDnp*)thisx)

void EnDnp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnp_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B3D11C(EnDnp* this, GlobalContext* globalCtx);
void func_80B3D2D4(EnDnp* this, GlobalContext* globalCtx);
void func_80B3D338(EnDnp* this, GlobalContext* globalCtx);
void func_80B3D3F8(EnDnp* this, GlobalContext* globalCtx);
void func_80B3D558(EnDnp* this, GlobalContext* globalCtx);

extern AnimationHeader D_060007D8;
extern AnimationHeader D_0600125C;
extern AnimationHeader D_060017F8;
extern AnimationHeader D_06001C1C;
extern AnimationHeader D_060021DC;
extern AnimationHeader D_060026B8;
extern AnimationHeader D_06004D08;
extern AnimationHeader D_060057AC;
extern AnimationHeader D_0600625C;
extern AnimationHeader D_0600674C;
extern AnimationHeader D_06006B74;
extern AnimationHeader D_060071F4;
extern AnimationHeader D_06007960;
extern AnimationHeader D_06008588;
extern AnimationHeader D_0600923C;
extern AnimationHeader D_06009AA0;
extern AnimationHeader D_0600A900;
extern AnimationHeader D_0600AEB8;
extern AnimationHeader D_0600B324;
extern AnimationHeader D_0600B754;
extern AnimationHeader D_0600BAD8;
extern Gfx D_060103D0[];
extern Gfx D_060105D0[];
extern Gfx D_060107D0[];
extern Gfx D_060109D0[];
extern FlexSkeletonHeader D_06010D60;
extern AnimationHeader D_060115B8;
extern AnimationHeader D_06012428;

const ActorInit En_Dnp_InitVars = {
    ACTOR_EN_DNP,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNP,
    sizeof(EnDnp),
    (ActorFunc)EnDnp_Init,
    (ActorFunc)EnDnp_Destroy,
    (ActorFunc)EnDnp_Update,
    (ActorFunc)EnDnp_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 38, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static ActorAnimationEntryS sAnimations[] = {
    { &D_060007D8, 1.0f, 0, -1, 2, -4 }, { &D_060021DC, 1.0f, 0, -1, 0, 0 },  { &D_060021DC, 1.0f, 0, -1, 0, -4 },
    { &D_060026B8, 1.0f, 0, -1, 2, -4 }, { &D_06004D08, 1.0f, 0, -1, 2, -4 }, { &D_060071F4, 1.0f, 0, -1, 2, -4 },
    { &D_06007960, 1.0f, 0, -1, 0, -4 }, { &D_06008588, 1.0f, 0, -1, 2, 0 },  { &D_0600A900, 1.0f, 0, -1, 0, -4 },
    { &D_0600AEB8, 1.0f, 0, -1, 0, -4 }, { &D_0600B754, 1.0f, 0, -1, 2, -4 }, { &D_0600674C, 1.0f, 0, -1, 0, -4 },
    { &D_0600BAD8, 1.0f, 0, -1, 2, -4 }, { &D_06006B74, 1.0f, 0, -1, 0, -4 }, { &D_06012428, 1.0f, 0, -1, 0, -4 },
    { &D_0600B324, 1.0f, 0, -1, 0, 0 },  { &D_0600B324, 1.0f, 0, -1, 0, -4 }, { &D_060115B8, 1.0f, 0, -1, 0, -4 },
    { &D_060115B8, 1.0f, 0, -1, 0, 0 },  { &D_0600923C, 1.0f, 0, -1, 2, -4 }, { &D_06009AA0, 1.0f, 0, -1, 0, -4 },
    { &D_0600125C, 1.0f, 0, -1, 2, -4 }, { &D_060017F8, 1.0f, 0, -1, 2, 0 },  { &D_06001C1C, 1.0f, 0, -1, 0, -4 },
    { &D_060057AC, 1.0f, 0, -1, 2, 0 },  { &D_0600625C, 1.0f, 0, -1, 0, -4 },
};

static s32 D_80B3DE58[] = {
    0x00172000, 0x0D040005, 0x0E09670C, 0x100E0968, 0x0C100E09, 0x6F0C0F09, 0x700C1000,
};

s32 func_80B3CA20(EnDnp* this) {
    if ((this->unk_340 == 2) || (this->unk_340 == 9)) {
        if (func_801378B8(&this->skelAnime, 1.0f) || func_801378B8(&this->skelAnime, 5.0f) ||
            func_801378B8(&this->skelAnime, 9.0f) || func_801378B8(&this->skelAnime, 13.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_TURN);
        }
    } else if ((this->unk_340 == 24) || (this->unk_340 == 7)) {
        if (func_801378B8(&this->skelAnime, 1.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_TURN);
        }
    } else if (this->unk_340 == 14) {
        if (func_801378B8(&this->skelAnime, 7.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_GREET);
        }
        if (func_801378B8(&this->skelAnime, 22.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_GREET2);
        }
    } else if (this->unk_340 == 8) {
        if (func_801378B8(&this->skelAnime, 9.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_GREET);
        }
        if (func_801378B8(&this->skelAnime, 18.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_GREET2);
        }
    } else if ((this->unk_340 == 17) && (this->unk_340 == 18)) {
        if (func_801378B8(&this->skelAnime, 7.0f) || func_801378B8(&this->skelAnime, 15.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_WALK);
        }
    } else if (this->unk_340 == 21) {
        if (func_801378B8(&this->skelAnime, 17.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_WALK);
        }
    } else if (this->unk_340 == 23) {
        if (func_801378B8(&this->skelAnime, 3.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKUHIME_WALK);
        }
    }

    return 0;
}

s32 func_80B3CC38(EnDnp* this, s32 arg1) {
    s32 ret = false;

    if (arg1 != this->unk_340) {
        this->unk_340 = arg1;
        ret = func_8013BC6C(&this->skelAnime, sAnimations, arg1);
    }

    return ret;
}

void func_80B3CC80(EnDnp* this, GlobalContext* globalCtx) {
    f32 temp_f0 = this->actor.scale.x / 0.0085f;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->collider.dim.radius = 14.0f * temp_f0;
    this->collider.dim.height = 38.0f * temp_f0;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80B3CD1C(EnDnp* this) {
    if ((this->unk_322 & 0x80) && (DECR(this->unk_334) == 0)) {
        this->unk_336++;
        if (this->unk_336 >= 4) {
            this->unk_334 = Rand_S16Offset(30, 30);
            this->unk_336 = 0;
        }
    }
}

s32 func_80B3CDA4(EnDnp* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 temp_s0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    Vec3f sp3C;
    Vec3f sp30;
    s16 pitch;

    temp_s0 = CLAMP(temp_s0, -0x3FFC, 0x3FFC);

    Math_SmoothStepToS(&this->unk_332, temp_s0, 3, 0x2AA8, 0x1);
    sp30 = player->actor.world.pos;
    sp30.y = player->bodyPartsPos[7].y + 3.0f;
    sp3C = this->actor.world.pos;
    sp3C.y += 10.0f;
    pitch = Math_Vec3f_Pitch(&sp3C, &sp30);
    if (1) {};
    Math_SmoothStepToS(&this->unk_330, pitch, 3, 0x2AA8, 0x1);

    return 1;
}

s32 func_80B3CEC0(EnDnp* this, GlobalContext* globalCtx) {
    if (this->unk_322 & 8) {
        func_80B3CDA4(this, globalCtx);
        this->unk_322 &= ~0x10;
        this->unk_322 |= 64;
    } else if (this->unk_322 & 0x40) {
        this->unk_322 &= ~0x40;
        this->unk_330 = 0;
        this->unk_332 = 0;
        this->unk_338 = 20;
    } else if (DECR(this->unk_338) == 0) {
        this->unk_322 |= 0x10;
    }

    return 1;
}

s32 func_80B3CF60(EnDnp* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk_322 & 7) && Actor_IsTalking(&this->actor, globalCtx)) {
        func_8013AED4(&this->unk_322, 0, 7);
        this->unk_322 |= 8;
        this->actionFunc = func_80B3D3F8;
        ret = true;
    } else if (!(gSaveContext.weekEventReg[23] & 0x20) && Actor_HasParent(&this->actor, globalCtx)) {
        func_8013AED4(&this->unk_322, 0, 7);
        this->unk_322 &= ~0x500;
        this->actor.parent = NULL;
        this->unk_32E = 0;
        this->actionFunc = func_80B3D338;
        ret = true;
    }

    return ret;
}

s32 func_80B3D044(EnDnp* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if (globalCtx->csCtx.state != 0) {
        if (!(this->unk_322 & 0x200)) {
            this->unk_322 |= (0x200 | 0x10);
            this->actor.flags &= ~1;
            this->unk_324 = 0xFF;
        }
        func_8013AED4(&this->unk_322, 0, 7);
        this->actionFunc = func_80B3D11C;
        ret = true;
    } else if (this->unk_322 & 0x200) {
        this->actor.flags |= 1;
        func_8013AED4(&this->unk_322, 3, 7);
        this->unk_322 &= ~(0x200 | 0x10);
        this->actionFunc = func_80B3D2D4;
    }

    return ret;
}

void func_80B3D11C(EnDnp* this, GlobalContext* globalCtx) {
    static s32 D_80B3DE74[] = {
        0, 16, 14, 10, 18, 12, 5, 7, 2, 19, 21, 22, 24, 8,
    };
    u32 temp_v0;
    s32 val;

    if (!(gSaveContext.weekEventReg[29] & 0x40) && (globalCtx->sceneNum == SCENE_MITURIN) &&
        (globalCtx->csCtx.unk_12 == 0)) {
        this->unk_322 |= 0x20;
        gSaveContext.weekEventReg[29] |= 0x40;
    }

    if (func_800EE29C(globalCtx, 0x65)) {
        temp_v0 = func_800EE200(globalCtx, 0x65);
        val = globalCtx->csCtx.npcActions[temp_v0]->unk0;
        if (this->unk_324 != (u8)val) {
            func_80B3CC38(this, D_80B3DE74[val]);
            if (this->unk_340 == 16) {
                this->unk_322 |= 8;
            } else {
                this->unk_322 &= ~8;
            }

            if (this->unk_340 == 19) {
                Audio_PlayActorSound2(&this->actor, NA_SE_VO_DHVO04);
            }

            if (this->unk_340 == 24) {
                this->unk_322 &= ~0x80;
                this->unk_336 = 3;
                this->unk_334 = 0;
            }
        }

        this->unk_324 = val;
        if (((this->unk_340 == 10) || (this->unk_340 == 12) || (this->unk_340 == 5) || (this->unk_340 == 19) ||
             (this->unk_340 == 22) || (this->unk_340 == 24)) &&
            func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount)) {
            func_80B3CC38(this, this->unk_340 + 1);
        }
        func_800EDF24(&this->actor, globalCtx, temp_v0);
    }
}

void func_80B3D2D4(EnDnp* this, GlobalContext* globalCtx) {
    if (this->unk_322 & 0x20) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x3, 0x2AA8);
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 0x3, 0x2AA8);
    }
}

void func_80B3D338(EnDnp* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((this->unk_32E != 0) && (func_80152498(&globalCtx->msgCtx) == 2)) {
        Actor_MarkForDeath(&this->actor);
    } else if (this->unk_32E == 0) {
        if (Actor_IsTalking(&this->actor, globalCtx)) {
            this->unk_32E = 1;
        } else {
            this->actor.textId = 0x971;
            player->actor.textId = this->actor.textId;
            func_800B8500(&this->actor, globalCtx, 9999.9f, 9999.9f, -1);
        }
    }
}

void func_80B3D3F8(EnDnp* this, GlobalContext* globalCtx) {
    if (func_8010BF58(&this->actor, globalCtx, D_80B3DE58, NULL, &this->unk_328)) {
        func_8013AED4(&this->unk_322, 3, 7);
        this->unk_322 &= ~8;
        this->actionFunc = func_80B3D2D4;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x3, 0x2AA8);
    }
}

void func_80B3D47C(EnDnp* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        Math_SmoothStepToF(&this->actor.scale.x, 0.0085f, 0.1f, 0.01f, 0.001f);
        if ((s32)(this->actor.scale.x * 10000.0f) >= 85) {
            this->actor.flags |= 1;
            func_8013AED4(&this->unk_322, 3, 7);
            this->unk_322 &= ~0x10;
            this->unk_322 |= 0x400;
            this->actor.scale.x = 0.0085f;
            this->actionFunc = func_80B3D558;
        }
    }
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void func_80B3D558(EnDnp* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        gSaveContext.weekEventReg[23] |= 0x20;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnDnp_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDnp* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 16.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06010D60, NULL, this->jointTable, this->morphTable, 26);
    this->unk_340 = -1;
    func_80B3CC38(this, 15);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    this->unk_322 = 0;
    this->actor.targetMode = 0;
    this->unk_322 |= (0x100 | 0x80 | 0x10);
    this->actor.gravity = -1.0f;
    if (ENDNP_GET_7(&this->actor) == ENDNP_GET_7_1) {
        this->actor.flags &= ~1;
        Actor_SetScale(&this->actor, 0.00085000007f);
        func_8013AED4(&this->unk_322, 0, 7);
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        this->actor.cutscene = 0x10;
        this->actionFunc = func_80B3D47C;
    } else if (((ENDNP_GET_7(&this->actor) == ENDNP_GET_7_0) && !func_80114F2C(0x17) &&
                !(gSaveContext.weekEventReg[23] & 0x20)) ||
               ((ENDNP_GET_7(&this->actor) == ENDNP_GET_7_2) && (gSaveContext.weekEventReg[23] & 0x20))) {
        Actor_SetScale(&this->actor, 0.0085f);
        func_8013AED4(&this->unk_322, 3, 7);
        this->unk_322 |= 0x400;
        if ((globalCtx->sceneNum == SCENE_MITURIN) && (gSaveContext.weekEventReg[29] & 0x40)) {
            this->unk_322 |= 0x20;
            func_80B3CC38(this, 1);
        }
        this->actionFunc = func_80B3D2D4;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnDnp_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDnp* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDnp_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDnp* this = THIS;
    s32 pad;
    f32 sp2C;
    f32 sp28;

    if (!func_80B3CF60(this, globalCtx) && func_80B3D044(this, globalCtx)) {
        func_80B3D11C(this, globalCtx);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80B3CD1C(this);
        func_80B3CEC0(this, globalCtx);
    } else {
        this->actionFunc(this, globalCtx);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80B3CD1C(this);
        func_80B3CEC0(this, globalCtx);
        Actor_MoveForward(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        sp2C = this->collider.dim.radius + 50;
        sp28 = this->collider.dim.height + 30;
        if ((this->unk_322 & 0x400) && !(gSaveContext.weekEventReg[23] & 0x20)) {
            func_800B8A1C(&this->actor, globalCtx, 0xBA, sp2C, sp28);
        }
        func_8013C964(&this->actor, globalCtx, sp2C, sp28, 0, this->unk_322 & 7);
        Actor_SetFocus(&this->actor, 30.0f);
        func_80B3CC80(this, globalCtx);
    }

    if (this->unk_322 & 0x100) {
        func_80B3CA20(this);
    }
}

s32 func_80B3D974(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4, s32 arg5) {
    Vec3f sp74;
    Vec3s sp6C;
    MtxF sp2C;

    SysMatrix_MultiplyVector3fByState(&D_801D15B0, &sp74);
    SysMatrix_CopyCurrentState(&sp2C);
    func_8018219C(&sp2C, &sp6C, 0);
    *arg2 = sp74;
    if (arg4 == 0) {
        if (arg5 != 0) {
            sp6C.z = arg0;
            sp6C.y = arg1;
        }
        Math_SmoothStepToS(&arg3->x, sp6C.x, 3, 0x2AA8, 0xB6);
        Math_SmoothStepToS(&arg3->y, sp6C.y, 3, 0x2AA8, 0xB6);
        Math_SmoothStepToS(&arg3->z, sp6C.z, 3, 0x2AA8, 0xB6);
    } else {
        arg3->x = sp6C.x;
        arg3->y = sp6C.y;
        arg3->z = sp6C.z;
    }

    return 1;
}

void func_80B3DA88(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void func_80B3DAA0(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnDnp* this = THIS;
    s32 phi_v1 = 1;
    s32 phi_v0;

    if (this->unk_322 & 0x10) {
        phi_v0 = 0;
    } else {
        phi_v1 = 0;
        if (this->unk_322 & 0x40) {
            phi_v0 = 1;
        } else {
            phi_v0 = 0;
        }
    }

    if (limbIndex == 12) {
        func_80B3D974(this->unk_330 + 0x4000, this->unk_332 + this->actor.shape.rot.y + 0x4000, &this->unk_1D8,
                      &this->unk_1E4, phi_v1, phi_v0);
        SysMatrix_StatePop();
        SysMatrix_InsertTranslation(this->unk_1D8.x, this->unk_1D8.y, this->unk_1D8.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_1E4.y, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk_1E4.x, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->unk_1E4.z, MTXMODE_APPLY);
        SysMatrix_StatePush();
    }
}

void EnDnp_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* D_80B3DEAC[] = {
        D_060103D0,
        D_060105D0,
        D_060107D0,
        D_060109D0,
    };
    EnDnp* this = THIS;

    if (this->unk_322 & 0x100) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B3DEAC[this->unk_336]));

        func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                      NULL, func_80B3DA88, func_80B3DAA0, &this->actor);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
