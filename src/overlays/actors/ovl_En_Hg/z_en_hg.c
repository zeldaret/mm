/*
 * File: z_en_hg.c
 * Overlay: ovl_En_Hg
 * Description: Pamela's Father (Human)
 */

#include "z_en_hg.h"
#include "objects/object_harfgibud/object_harfgibud.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnHg*)thisx)

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BCF354(EnHg* this);
void func_80BCF398(EnHg* this, GlobalContext* globalCtx);
void func_80BCF468(EnHg* this);
void func_80BCF468(EnHg* this);
void func_80BCF4AC(EnHg* this, GlobalContext* globalCtx);
void func_80BCF5F0(EnHg* this);
void func_80BCF634(EnHg* this, GlobalContext* globalCtx);
void func_80BCF68C(EnHg* this);
void func_80BCF6D0(EnHg* this, GlobalContext* globalCtx);
void func_80BCF8A0(EnHg* this, GlobalContext* globalCtx);
void func_80BCF93C(EnHg* this);
void func_80BCF95C(EnHg* this, GlobalContext* globalCtx);
s32 EnHg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnHg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

const ActorInit En_Hg_InitVars = {
    ACTOR_EN_HG,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHg),
    (ActorFunc)EnHg_Init,
    (ActorFunc)EnHg_Destroy,
    (ActorFunc)EnHg_Update,
    (ActorFunc)EnHg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
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
    { 18, 46, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(3, 0xC),
    /* Normal arrow   */ DMG_ENTRY(3, 0xC),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(3, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, 0x80,
};

static AnimationInfo sAnimations[] = {
    { &object_harfgibud_Anim_00260C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_harfgibud_Anim_009D44, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_harfgibud_Anim_00A164, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_harfgibud_Anim_000370, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &object_harfgibud_Anim_001138, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_harfgibud_Anim_0015D4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &object_harfgibud_Anim_001960, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &object_harfgibud_Anim_00AE1C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
};

static u32 D_80BD00C8 = false;

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;
    s16 currentCutscene = this->actor.cutscene;
    s32 i;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 36.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_harfgibud_Skel_008580, &object_harfgibud_Anim_00260C,
                       this->jointTable, this->morphTable, HG_LIMB_MAX);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
    if ((gSaveContext.save.weekEventReg[75] & 0x20) || (gSaveContext.save.weekEventReg[52] & 0x20)) {
        Actor_MarkForDeath(&this->actor);
    }
    this->actor.targetMode = 1;
    this->actor.colChkInfo.health = 0;
    this->actor.gravity = -1.0f;
    for (i = 0; i < ARRAY_COUNT(this->cutscenes); i++) {
        if (currentCutscene == -1) {
            break;
        }
        this->cutscenes[i] = currentCutscene;
        currentCutscene = ActorCutscene_GetAdditionalCutscene(currentCutscene);
    }
    func_80BCF354(this);
}

void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BCF354(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80BCF398;
}

void func_80BCF398(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 1) {
        if ((this->actor.xzDistToPlayer < 200.0f && this->actor.playerHeightRel < 40.0f) &&
            !Cutscene_CheckActorAction(globalCtx, 0x1E3)) {
            func_80BCF468(this);
        }
        if ((gSaveContext.sceneSetupIndex == 0 && globalCtx->csCtx.currentCsIndex == 0) &&
            (globalCtx->csCtx.frames == 20 || globalCtx->csCtx.frames == 60)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_HALF_REDEAD_SURPRISE);
        }
    }
}

void func_80BCF468(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    this->actionFunc = func_80BCF4AC;
}

void func_80BCF4AC(EnHg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    this->actor.speedXZ = 1.6f;
    if (!(player->stateFlags2 & 0x08000000) && Message_GetState(&globalCtx->msgCtx) == 0) {
        if (((this->skelAnime.curFrame > 9.0f) && (this->skelAnime.curFrame < 16.0f)) ||
            ((this->skelAnime.curFrame > 44.0f) && (this->skelAnime.curFrame < 51.0f))) {
            Actor_MoveWithGravity(&this->actor);
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0x14);
            this->actor.world.rot.y = this->actor.shape.rot.y;
        }
        if ((Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 200.0f) &&
            (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) > 200.0f)) {
            func_80BCF5F0(this);
        }
    }
}

void func_80BCF5F0(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80BCF634;
}

void func_80BCF634(EnHg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) < 200.0f) {
        func_80BCF468(this);
    }
}

void func_80BCF68C(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
    this->actionFunc = func_80BCF6D0;
}

void func_80BCF6D0(EnHg* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80BCF5F0(this);
    }
}

void func_80BCF710(EnHg* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 0) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            Message_StartTextbox(globalCtx, 0x24F, &this->actor);
        } else {
            func_800B8614(&this->actor, globalCtx, 80.0f);
        }
    }
}

void func_80BCF778(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 1) {
        if (this->actionFunc == func_80BCF4AC || this->actionFunc == func_80BCF6D0 ||
            this->actionFunc == func_80BCF634) {
            func_800B9010(&this->actor, NA_SE_EN_HALF_REDEAD_LOOP - SFX_FLAG);
        }
    }
}

void func_80BCF7D8(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health) {
        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            func_80BCF68C(this);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (this->actionFunc != func_80BCF6D0 && this->actionFunc != func_80BCF8A0 &&
            this->actionFunc != func_80BCF95C) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80BCF88C(EnHg* this) {
    this->actionFunc = func_80BCF8A0;
}

void func_80BCF8A0(EnHg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscenes[this->unk218])) {
        ActorCutscene_Start(this->cutscenes[this->unk218], &this->actor);
        func_80BCF93C(this);
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->cutscenes[this->unk218]);
    }
}

void func_80BCF93C(EnHg* this) {
    this->cutscenes[3] = 0x63;
    this->cutscenes[2] = 0;
    this->actionFunc = func_80BCF95C;
}

void func_80BCF95C(EnHg* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 484)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(globalCtx, 484);

        if (this->cutscenes[3] != globalCtx->csCtx.actorActions[actionIndex]->action) {
            this->cutscenes[3] = globalCtx->csCtx.actorActions[actionIndex]->action;
            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                case 1:
                    this->currentAnimation = 0;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
                    break;
                case 2:
                    this->cutscenes[2] = 0;
                    this->currentAnimation = 3;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
                    break;
                case 3:
                    this->cutscenes[2] = 0;
                    this->currentAnimation = 5;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 5);
                    break;
                case 4:
                    this->cutscenes[2] = 0;
                    this->currentAnimation = 7;
                    if ((this->unk218 == 1) || (this->unk218 == 3)) {
                        func_8019F128(NA_SE_EN_HALF_REDEAD_TRANS);
                    }
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 7);
                    break;
                case 5:
                    this->currentAnimation = 1;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                    break;
                case 6:
                    gSaveContext.save.weekEventReg[75] |= 0x20;
                    Actor_MarkForDeath(&this->actor);
                    break;
            }
        } else {
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                switch (this->currentAnimation) {
                    case 3:
                        this->currentAnimation = 4;
                        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 4);
                        break;
                    case 5:
                        this->currentAnimation = 6;
                        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 6);
                        break;
                }
            }
        }
        switch (this->currentAnimation) {
            case 3:
            case 4:
                func_800B9010(&this->actor, NA_SE_EN_HALF_REDEAD_LOOP - SFX_FLAG);
                break;
            case 5:
            case 6:
                func_800B9010(&this->actor, NA_SE_EN_HALF_REDEAD_SCREAME - SFX_FLAG);
                break;
            case 7:
                if ((this->unk218 == 0) || (this->unk218 == 2)) {
                    func_800B9010(&this->actor, NA_SE_EN_HALF_REDEAD_SCREAME - SFX_FLAG);
                }
                break;
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
        return;
    } else if (globalCtx->csCtx.state == 0) {
        func_80BCF354(this);
    }
    this->cutscenes[3] = 0x63;
}

void func_80BCFC0C(EnHg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.colChkInfo.health == 1 && !(fabsf(this->actor.playerHeightRel) >= 80.0f)) {
        if (player->stateFlags2 & 0x08000000) {
            if (!D_80BD00C8) {
                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            }
            D_80BD00C8 = true;
        } else {
            D_80BD00C8 = false;
        }
        if (globalCtx->msgCtx.ocarinaMode == 3) {
            if (globalCtx->msgCtx.unk1202E == 7 && gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
                if (INV_CONTENT(ITEM_MASK_GIBDO) == ITEM_MASK_GIBDO) {
                    this->unk218 = 3;
                } else {
                    this->unk218 = 1;
                }
                func_80BCF88C(this);
            }
        } else {
            if (this->actor.xzDistToPlayer < 60.0f && fabsf(this->actor.playerHeightRel) < 40.0f) {
                if ((this->actionFunc != func_80BCF8A0) && (this->actionFunc != func_80BCF95C)) {
                    if (!(gSaveContext.save.weekEventReg[61] & 2)) {
                        gSaveContext.save.weekEventReg[61] |= 2;
                        this->unk218 = 0;
                    } else {
                        this->unk218 = 2;
                    }
                    func_80BCF88C(this);
                    return;
                }
            }
            func_80BCF710(this, globalCtx);
        }
    }
}

void EnHg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    this->actionFunc(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);
    func_80BCF7D8(this, globalCtx);
    func_80BCFC0C(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 25.0f, 0.0f, 5);
    func_80BCF778(this, globalCtx);
}

s32 EnHg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void EnHg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnHg* this = THIS;
    if (limbIndex == HG_LIMB_HEAD) {
        Matrix_CopyCurrentState(&this->unk1D8);
    } else if (limbIndex == HG_LIMB_PELVIS) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
    }
}

void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnHg_OverrideLimbDraw, EnHg_PostLimbDraw, &this->actor);
    Matrix_SetCurrentState(&this->unk1D8);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_harfgibud_DL_005E28);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
