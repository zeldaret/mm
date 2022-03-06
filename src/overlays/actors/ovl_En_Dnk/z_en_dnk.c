/*
 * File: z_en_dnk.c
 * Overlay: ovl_En_Dnk
 * Description: Hallucinatory Mad Scrubs (Deku curse and healing cutscenes)
 */

#include "z_en_dnk.h"
#include "objects/object_dnk/object_dnk.h"
#include "objects/object_hintnuts/object_hintnuts.h"
#include "objects/object_dekunuts/object_dekunuts.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDnk*)thisx)

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A51890(EnDnk* this, GlobalContext* globalCtx);
void EnDnk_DoNothing(EnDnk* this, GlobalContext* globalCtx);
void func_80A52018(Actor* thisx, GlobalContext* globalCtx);
void func_80A52134(EnDnk* this, GlobalContext* globalCtx);

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

static AnimationInfoS sAnimations[] = {
    { &gDekuPalaceGuardStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuPalaceGuardStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPalaceGuardWaitAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPalaceGuardAttackAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPalaceGuardDigAnim, 1.0f, -1, -1, ANIMMODE_ONCE, 0 },
    { &gDekuPalaceGuardDigAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPalaceGuardJumpAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPalaceGuardWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gDekuPalaceGuardWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPalaceGuardHappyAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_hintnuts_Anim_000168, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_hintnuts_Anim_0024CC, 1.0f, -1, -1, ANIMMODE_ONCE, 0 },
    { &object_hintnuts_Anim_0024CC, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_hintnuts_Anim_0026C4, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_hintnuts_Anim_002894, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_hintnuts_Anim_002B90, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_hintnuts_Anim_002F7C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_hintnuts_Anim_002F7C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_hintnuts_Anim_003128, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_hintnuts_Anim_003128, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_hintnuts_Anim_0029BC, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_hintnuts_Anim_002E84, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dekunuts_Anim_000168, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dekunuts_Anim_00259C, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dekunuts_Anim_002A5C, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dekunuts_Anim_002A5C, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dekunuts_Anim_002BD4, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dekunuts_Anim_002DD4, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dekunuts_Anim_002FA4, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dekunuts_Anim_003180, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &object_dekunuts_Anim_00326C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dekunuts_Anim_00326C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dekunuts_Anim_0033E4, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dekunuts_Anim_003780, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dekunuts_Anim_003780, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dekunuts_Anim_002950, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

s32 func_80A514F0(SkelAnime* skelAnime, s16 animIndex) {
    s16 frame;
    s16 frameCount;
    s32 sp30 = false;

    if (animIndex >= 0) {
        if (animIndex < ARRAY_COUNT(sAnimations)) {
            sp30 = true;
            frameCount = sAnimations[animIndex].frameCount;
            if (frameCount < 0) {
                frameCount = Animation_GetLastFrame(sAnimations[animIndex].animation);
            }
            frame = sAnimations[animIndex].startFrame;
            if (frame < 0) {
                frame = frameCount;
            }
            Animation_Change(skelAnime, sAnimations[animIndex].animation, sAnimations[animIndex].playSpeed, frame,
                             frameCount, sAnimations[animIndex].mode, sAnimations[animIndex].morphFrames);
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
    if (SubS_IsObjectLoaded(this->unk_28E, globalCtx) == true) {
        gSegments[0x06] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk_28E].segment);
        this->actor.draw = func_80A52018;
        this->actor.objBankIndex = this->unk_28E;
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 18.0f);

        switch (ENDNK_GET_3(&this->actor)) {
            case ENDNK_GET_3_0:
                SkelAnime_Init(globalCtx, &this->skelAnime, &gDekuPalaceGuardSkel, NULL, this->jointTable,
                               this->morphTable, 11);
                func_80A514F0(&this->skelAnime, 7);
                break;

            case ENDNK_GET_3_1:
                SkelAnime_Init(globalCtx, &this->skelAnime, &object_hintnuts_Skel_0023B8.sh, NULL, this->jointTable,
                               this->morphTable, 10);
                func_80A514F0(&this->skelAnime, 18);
                break;

            case ENDNK_GET_3_2:
                SkelAnime_Init(globalCtx, &this->skelAnime, &object_dekunuts_Skel_002468, NULL, this->jointTable,
                               this->morphTable, 10);
                func_80A514F0(&this->skelAnime, 35);
                break;
        }

        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        if (ENDNK_GET_3C(&this->actor) == 4) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->actor.flags |= (ACTOR_FLAG_10 | ACTOR_FLAG_20);
            this->actionFunc = func_80A51890;
            Actor_SetScale(&this->actor, 0.1f);
        } else {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->actionFunc = EnDnk_DoNothing;
            Actor_SetScale(&this->actor, 0.01f);
        }
    }
}

void func_80A51890(EnDnk* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 126)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, 126));
    }
}

void EnDnk_DoNothing(EnDnk* this, GlobalContext* globalCtx) {
}

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDnk* this = THIS;

    this->unk_28E = -1;
    switch (ENDNK_GET_3(&this->actor)) {
        case ENDNK_GET_3_1:
            this->unk_28E = SubS_GetObjectIndex(OBJECT_HINTNUTS, globalCtx);
            break;

        case ENDNK_GET_3_0:
            this->unk_28E = SubS_GetObjectIndex(OBJECT_DNK, globalCtx);
            break;

        case ENDNK_GET_3_2:
            this->unk_28E = SubS_GetObjectIndex(OBJECT_DEKUNUTS, globalCtx);
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
    SkelAnime_Update(&this->skelAnime);
    func_80A515C4(this);
    Actor_SetFocus(&this->actor, 34.0f);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    func_80A52134(this, globalCtx);
}

s32 func_80A51A78(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;

    this->unk_260[limbIndex] = *dList;
    *dList = NULL;
    return false;
}

void func_80A51AA4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;
    MtxF sp5C;
    Vec3f sp50 = gZeroVec3f;
    Vec3f sp44;
    Vec3s sp3C;

    if (limbIndex == 2) {
        Matrix_MultiplyVector3fByState(&sp50, &sp44);
        Matrix_CopyCurrentState(&sp5C);
        func_8018219C(&sp5C, &sp3C, 0);
        Matrix_InsertTranslation(sp44.x, sp44.y, sp44.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        if (this->unk_28C & 0x10) {
            if (this->unk_28C & 0x20) {
                sp3C.x = this->unk_296;
                sp3C.y = this->unk_298;
                sp3C.y += this->actor.shape.rot.y;
                sp3C.z = 0;
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
        Matrix_InsertXRotation_s(this->unk_290, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_294, MTXMODE_APPLY);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_260[limbIndex]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A51CB8(EnDnk* this, GlobalContext* globalCtx) {
    static TexturePtr D_80A5245C[] = {
        gDekuPalaceGuardEyeOpenTex,
        gDekuPalaceGuardEyeHalfTex,
        gDekuPalaceGuardEyeClosedTex,
    };
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A5245C[this->unk_2A0]));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80A51A78, func_80A51AA4,
                      &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80A51D78(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;

    this->unk_260[limbIndex] = *dList;
    *dList = NULL;
    return false;
}

void func_80A51DA4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDnk* this = THIS;
    MtxF sp5C;
    Vec3f sp50 = gZeroVec3f;
    Vec3f sp44;
    Vec3s sp3C;

    if (limbIndex == 2) {
        Matrix_MultiplyVector3fByState(&sp50, &sp44);
        Matrix_CopyCurrentState(&sp5C);
        func_8018219C(&sp5C, &sp3C, 0);
        Matrix_InsertTranslation(sp44.x, sp44.y, sp44.z, MTXMODE_NEW);
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
        Matrix_InsertXRotation_s(this->unk_290, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_294, MTXMODE_APPLY);
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_260[limbIndex]);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A51FC0(EnDnk* this, GlobalContext* globalCtx) {
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80A51D78, func_80A51DA4,
                      &this->actor);
}

void func_80A52018(Actor* thisx, GlobalContext* globalCtx) {
    EnDnk* this = THIS;

    switch (ENDNK_GET_3(thisx)) {
        case ENDNK_GET_3_0:
            func_80A51CB8(this, globalCtx);
            break;

        case ENDNK_GET_3_1:
        case ENDNK_GET_3_2:
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
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_DEKNUTS_DANCE_BIG);
            break;

        case 493:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
            break;
    }

    if ((globalCtx->csCtx.frames >= 198) && (globalCtx->csCtx.frames < 438)) {
        func_8019F128(NA_SE_EN_DEKNUTS_DANCE - SFX_FLAG);
    }
}

void func_80A52134(EnDnk* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.state != 0) && (ENDNK_GET_3C(&this->actor) == 4) && (globalCtx->sceneNum == SCENE_SPOT00) &&
        (gSaveContext.sceneSetupIndex == 2)) {
        func_80A52074(this, globalCtx);
    }
}
