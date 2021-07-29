/*
 * File: z_en_dnk.c
 * Overlay: ovl_En_Dnk
 * Description: Hallucinatory Mad Scrubs
 */

#include "z_en_dnk.h"

#define FLAGS 0x00000009

#define THIS ((EnDnk*)thisx)

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A52018(Actor* thisx, GlobalContext* globalCtx);
void func_80A51890(EnDnk* this, GlobalContext* globalCtx);
void func_80A518DC(EnDnk* this, GlobalContext* globalCtx);
void func_80A52134(EnDnk* this, GlobalContext* globalCtx);

extern SkeletonHeader D_06002848;
extern SkeletonHeader D_060023B8;
extern SkeletonHeader D_06002468;
extern AnimationHeader D_06000B70;
extern AnimationHeader D_06000B70;
extern AnimationHeader D_06002A08;
extern AnimationHeader D_0600031C;
extern AnimationHeader D_06000430;
extern AnimationHeader D_06000430;
extern AnimationHeader D_06000894;
extern AnimationHeader D_06002B6C;
extern AnimationHeader D_06002B6C;
extern AnimationHeader D_060006CC;
extern AnimationHeader D_06000168;
extern AnimationHeader D_060024CC;
extern AnimationHeader D_060024CC;
extern AnimationHeader D_060026C4;
extern AnimationHeader D_06002894;
extern AnimationHeader D_06002B90;
extern AnimationHeader D_06002F7C;
extern AnimationHeader D_06002F7C;
extern AnimationHeader D_06003128;
extern AnimationHeader D_06003128;
extern AnimationHeader D_060029BC;
extern AnimationHeader D_06002E84;
extern AnimationHeader D_06000168;
extern AnimationHeader D_0600259C;
extern AnimationHeader D_06002A5C;
extern AnimationHeader D_06002A5C;
extern AnimationHeader D_06002BD4;
extern AnimationHeader D_06002DD4;
extern AnimationHeader D_06002FA4;
extern AnimationHeader D_06003180;
extern AnimationHeader D_0600326C;
extern AnimationHeader D_0600326C;
extern AnimationHeader D_060033E4;
extern AnimationHeader D_06003780;
extern AnimationHeader D_06003780;
extern AnimationHeader D_06002950;

static s16 D_80A521A0 = 0;

const ActorInit En_Dnk_InitVars = {
    ACTOR_EN_DNK,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDnk),
    (ActorFunc)EnDnk_Init,
    (ActorFunc)EnDnk_Destroy,
    (ActorFunc)EnDnk_Update,
    (ActorFunc)NULL,
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
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static ActorAnimationEntryS D_80A5221C[] = {
    { &D_06000B70, 1.0f, 0, -1, 2, 0 },  { &D_06000B70, 1.0f, 0, -1, 2, -4 }, { &D_06002A08, 1.0f, 0, -1, 0, -4 },
    { &D_0600031C, 1.0f, 0, -1, 0, -4 }, { &D_06000430, 1.0f, -1, -1, 2, 0 }, { &D_06000430, 1.0f, 0, -1, 2, -4 },
    { &D_06000894, 1.0f, 0, -1, 2, -4 }, { &D_06002B6C, 1.0f, 0, -1, 0, 0 },  { &D_06002B6C, 1.0f, 0, -1, 0, -4 },
    { &D_060006CC, 1.0f, 0, -1, 0, -4 }, { &D_06000168, 1.0f, 0, -1, 2, -4 }, { &D_060024CC, 1.0f, -1, -1, 2, 0 },
    { &D_060024CC, 1.0f, 0, -1, 2, -4 }, { &D_060026C4, 1.0f, 0, -1, 2, -4 }, { &D_06002894, 1.0f, 0, -1, 2, -4 },
    { &D_06002B90, 1.0f, 0, -1, 2, -4 }, { &D_06002F7C, 1.0f, 0, -1, 0, 0 },  { &D_06002F7C, 1.0f, 0, -1, 0, -4 },
    { &D_06003128, 1.0f, 0, -1, 0, 0 },  { &D_06003128, 1.0f, 0, -1, 0, -4 }, { &D_060029BC, 1.0f, 0, -1, 0, -4 },
    { &D_06002E84, 1.0f, 0, -1, 0, -4 }, { &D_06000168, 1.0f, 0, -1, 0, -4 }, { &D_0600259C, 1.0f, 0, -1, 2, -4 },
    { &D_06002A5C, 1.0f, 0, -1, 2, 0 },  { &D_06002A5C, 1.0f, 0, -1, 2, -4 }, { &D_06002BD4, 1.0f, 0, -1, 2, -4 },
    { &D_06002DD4, 1.0f, 0, -1, 2, -4 }, { &D_06002FA4, 1.0f, 0, -1, 0, -4 }, { &D_06003180, 1.0f, 0, -1, 2, -4 },
    { &D_0600326C, 1.0f, 0, -1, 0, 0 },  { &D_0600326C, 1.0f, 0, -1, 0, -4 }, { &D_060033E4, 1.0f, 0, -1, 0, -4 },
    { &D_06003780, 1.0f, 0, -1, 0, 0 },  { &D_06003780, 1.0f, 0, -1, 0, -4 }, { &D_06002950, 1.0f, 0, -1, 0, 0 },
};

s32 func_80A514F0(SkelAnime* skelAnime, s16 arg1) {
    s16 frame;
    s16 frameCount;
    s32 sp30 = 0;

    if (arg1 >= 0) {
        if (arg1 < 36) {
            sp30 = 1;
            frameCount = D_80A5221C[arg1].frameCount;
            if (frameCount < 0) {
                frameCount = SkelAnime_GetFrameCount(&(D_80A5221C[arg1].animationSeg)->common);
            }
            frame = D_80A5221C[arg1].frame;
            if (frame < 0) {
                frame = frameCount;
            }
            SkelAnime_ChangeAnim(skelAnime, D_80A5221C[arg1].animationSeg, D_80A5221C[arg1].playbackSpeed, frame,
                                 frameCount, D_80A5221C[arg1].mode, D_80A5221C[arg1].transitionRate);
        }
    }
    return sp30;
}

s32 func_80A515C4(EnDnk* this) {
    s32 ret = false;

    if (DECR(this->unk_29E) == 0) {
        this->unk_2A0++;
        if (this->unk_2A0 >= 3) {
            this->unk_29E = Rand_S16Offset(20, 20);
            this->unk_2A0 = 0;
        }
        ret = true;
    }
    return ret;
}

void func_80A51648(EnDnk* this, GlobalContext* globalCtx) {
    if (func_8013D8DC(this->unk_28E, globalCtx) == 1) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_28E].segment);
        this->actor.draw = func_80A52018;
        this->actor.objBankIndex = this->unk_28E;
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 18.0f);

        switch (ENDNK_PARAMS_3(&this->actor)) {
            case ENDNK_PARAMS_3_0:
                SkelAnime_Init(globalCtx, &this->skelAnime, &D_06002848, NULL, this->jointTable, this->morphTable, 11);
                func_80A514F0(&this->skelAnime, 7);
                break;

            case ENDNK_PARAMS_3_1:
                SkelAnime_Init(globalCtx, &this->skelAnime, &D_060023B8, NULL, this->jointTable, this->morphTable, 10);
                func_80A514F0(&this->skelAnime, 18);
                break;

            case ENDNK_PARAMS_3_2:
                SkelAnime_Init(globalCtx, &this->skelAnime, &D_06002468, NULL, this->jointTable, this->morphTable, 10);
                func_80A514F0(&this->skelAnime, 35);
                break;
        }

        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        if (ENDNK_PARAMS_3C(&this->actor) == ENDNK_PARAMS_3C_4) {
            this->actor.flags &= ~1;
            this->actor.flags |= 0x30;
            this->actionFunc = func_80A51890;
            Actor_SetScale(&this->actor, 0.1f);
        } else {
            this->actor.flags &= ~1;
            this->actionFunc = func_80A518DC;
            Actor_SetScale(&this->actor, 0.01f);
        }
    }
}

void func_80A51890(EnDnk* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x7E)) {
        func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x7E));
    }
}

void func_80A518DC(EnDnk* this, GlobalContext* globalCtx) {
}

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDnk* this = THIS;

    this->unk_28E = -1;
    switch (ENDNK_PARAMS_3(&this->actor)) {
        case ENDNK_PARAMS_3_1:
            this->unk_28E = func_8013D924(0x12B, globalCtx);
            break;

        case ENDNK_PARAMS_3_0:
            this->unk_28E = func_8013D924(0x135, globalCtx);
            break;

        case ENDNK_PARAMS_3_2:
            this->unk_28E = func_8013D924(0x40, globalCtx);
            break;
    }

    if (this->unk_28E >= 0) {
        this->actionFunc = func_80A51648;
    } else {
        Actor_MarkForDeath(&this->actor);
    }

    this->unk_2A2 = D_80A521A0;
    D_80A521A0++;
}

void EnDnk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDnk* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDnk_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDnk* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80A515C4(this);
    Actor_SetHeight(&this->actor, 34.0f);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    func_80A52134(this, globalCtx);
}

s32 func_80A51A78(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;

    this->unk_260[limbIndex] = *dList;
    *dList = NULL;
    return 0;
}

void func_80A51AA4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;
    MtxF sp5C;
    Vec3f sp50 = D_801D15B0;
    Vec3f sp44;
    Vec3s sp3C;

    if (limbIndex == 2) {
        SysMatrix_MultiplyVector3fByState(&sp50, &sp44);
        SysMatrix_CopyCurrentState(&sp5C);
        func_8018219C(&sp5C, &sp3C, 0);
        SysMatrix_InsertTranslation(sp44.x, sp44.y, sp44.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        if (this->unk_28C & 0x10) {
            if (this->unk_28C & 0x20) {
                sp3C.x = this->unk_296;
                sp3C.y = this->unk_298;
                sp3C.y += this->actor.shape.rot.y;
                sp3C.z = 0;
                Math_SmoothStepToS(&this->unk_290, sp3C.x, 4, 8190, 1);
                Math_SmoothStepToS(&this->unk_292, sp3C.y, 4, 8190, 1);
                Math_SmoothStepToS(&this->unk_294, sp3C.z, 4, 8190, 1);
            } else {
                this->unk_290 = sp3C.x;
                this->unk_292 = sp3C.y;
                this->unk_294 = sp3C.z;
            }
        } else {
            this->unk_28C |= 0x10;
            this->unk_290 = sp3C.x;
            this->unk_292 = sp3C.y;
            this->unk_294 = sp3C.z;
        }
        Matrix_RotateY(this->unk_292, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk_290, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->unk_294, MTXMODE_APPLY);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_260[limbIndex]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A51CB8(EnDnk* this, GlobalContext* globalCtx) {
    static Gfx* D_80A5245C[] = {
        0x06001680,
        0x06001700,
        0x06001780,
    };

    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A5245C[this->unk_2A0]));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80A51A78, func_80A51AA4,
                   &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80A51D78(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;

    this->unk_260[limbIndex] = *dList;
    *dList = NULL;
    return 0;
}

void func_80A51DA4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;
    MtxF sp5C;
    Vec3f sp50 = D_801D15B0;
    Vec3f sp44;
    Vec3s sp3C;

    if (limbIndex == 2) {
        SysMatrix_MultiplyVector3fByState(&sp50, &sp44);
        SysMatrix_CopyCurrentState(&sp5C);
        func_8018219C(&sp5C, &sp3C, 0);
        SysMatrix_InsertTranslation(sp44.x, sp44.y, sp44.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        if (this->unk_28C & 0x10) {
            if (this->unk_28C & 0x20) {
                sp3C.z = this->unk_296 + 0x4000;
                sp3C.y = this->unk_298 + 0x4000;
                sp3C.y += this->actor.shape.rot.y;
                sp3C.x = 0;
                Math_SmoothStepToS(&this->unk_290, sp3C.x, 4, 0x1FFE, 1);
                Math_SmoothStepToS(&this->unk_292, sp3C.y, 4, 0x1FFE, 1);
                Math_SmoothStepToS(&this->unk_294, sp3C.z, 4, 0x1FFE, 1);
            } else {
                this->unk_290 = sp3C.x;
                this->unk_292 = sp3C.y;
                this->unk_294 = sp3C.z;
            }
        } else {
            this->unk_28C |= 0x10;
            this->unk_290 = sp3C.x;
            this->unk_292 = sp3C.y;
            this->unk_294 = sp3C.z;
        }
        Matrix_RotateY(this->unk_292, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk_290, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->unk_294, MTXMODE_APPLY);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_260[limbIndex]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A51FC0(EnDnk* this, GlobalContext* globalCtx) {
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_80A51D78, func_80A51DA4,
                   &this->actor);
}

void func_80A52018(Actor* thisx, GlobalContext* globalCtx) {
    EnDnk* this = THIS;

    switch (ENDNK_PARAMS_3(thisx)) {
        case ENDNK_PARAMS_3_0:
            func_80A51CB8(this, globalCtx);
            break;

        case ENDNK_PARAMS_3_1:
        case ENDNK_PARAMS_3_2:
            func_80A51FC0(this, globalCtx);
            break;
    }
}

void func_80A52074(EnDnk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 80:
            func_8019F128(NA_SE_EN_DEKNUTS_DANCE1);
            break;

        case 123:
            func_8019F128(NA_SE_EN_DEKNUTS_DANCE2);
            break;

        case 438:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DEKNUTS_DANCE_BIG);
            break;

        case 493:
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
            break;
    }

    if ((globalCtx->csCtx.frames >= 198) && (globalCtx->csCtx.frames < 438)) {
        func_8019F128(NA_SE_EN_DEKNUTS_DANCE - SFX_FLAG);
    }
}

void func_80A52134(EnDnk* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.state != 0) && (ENDNK_PARAMS_3C(&this->actor) == ENDNK_PARAMS_3C_4) &&
        (globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 2)) {
        func_80A52074(this, globalCtx);
    }
}
