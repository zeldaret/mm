/*
 * File: z_en_hg.c
 * Overlay: En_Hg
 * Description: Pamela's Father (Normal)
 */

#include "z_en_hg.h"

#define FLAGS 0x02100019

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

extern FlexSkeletonHeader D_06008580;
extern AnimationHeader D_0600260C;
extern AnimationHeader D_06009D44;
extern AnimationHeader D_0600A164;
extern AnimationHeader D_06000370;
extern AnimationHeader D_06001138;
extern AnimationHeader D_060015D4;
extern AnimationHeader D_06001960;
extern AnimationHeader D_0600AE1C;
extern Gfx D_06005E28[];

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

static ActorAnimationEntry animations[] = {
    { &D_0600260C, 1.0f, 0.0f, 0.0f, 0x00, -4.0f }, { &D_06009D44, 1.0f, 0.0f, 0.0f, 0x00, -4.0f },
    { &D_0600A164, 1.0f, 0.0f, 0.0f, 0x00, -4.0f }, { &D_06000370, 1.0f, 0.0f, 0.0f, 0x02, 0.0f },
    { &D_06001138, 1.0f, 0.0f, 0.0f, 0x00, 0.0f },  { &D_060015D4, 1.0f, 0.0f, 0.0f, 0x02, 0.0f },
    { &D_06001960, 1.0f, 0.0f, 0.0f, 0x00, 0.0f },  { &D_0600AE1C, 1.0f, 0.0f, 0.0f, 0x00, 0.0f },
};

u32 D_80BD00C8 = 0;

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;
    s16 phi_s1;
    s32 i;

    phi_s1 = this->actor.cutscene;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 36.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06008580, &D_0600260C, this->limbDrawTbl, this->transitionDrawTbl,
                     0x13);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
    if ((gSaveContext.weekEventReg[0x4B] & 0x20) || (gSaveContext.weekEventReg[0x34] & 0x20)) {
        Actor_MarkForDeath(&this->actor);
    }
    this->actor.targetMode = 1;
    this->actor.colChkInfo.health = 0;
    this->actor.gravity = -1.0f;
    for (i = 0; i < 4; i++) {
        if (phi_s1 == -1) {
            break;
        }
        this->cutscenes[i] = phi_s1;
        phi_s1 = ActorCutscene_GetAdditionalCutscene(phi_s1);
    }
    func_80BCF354(this);
}

void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BCF354(EnHg* this) {
    func_800BDC5C(&this->skelAnime, animations, 0);
    this->actionFunc = func_80BCF398;
}

void func_80BCF398(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 1) {
        if ((this->actor.xzDistToPlayer < 200.0f && this->actor.yDistToPlayer < 40.0f) &&
            (func_800EE29C(globalCtx, 0x1E3U) == 0)) {
            func_80BCF468(this);
        }
        if ((gSaveContext.sceneSetupIndex == 0 && globalCtx->csCtx.unk_12 == 0) &&
            (globalCtx->csCtx.frames == 0x14 || globalCtx->csCtx.frames == 0x3C)) {
            Audio_PlayActorSound2(&this->actor, 0x3AB8);
        }
    }
}

void func_80BCF468(EnHg* this) {
    func_800BDC5C(&this->skelAnime, animations, 1);
    this->actionFunc = func_80BCF4AC;
}

void func_80BCF4AC(EnHg* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 pad;

    this->actor.speedXZ = 1.6f;
    if (!(player->stateFlags2 & 0x08000000)) {
        if (func_80152498(&globalCtx->msgCtx) == 0) {
            if (((this->skelAnime.animCurrentFrame > 9.0f) && (this->skelAnime.animCurrentFrame < 16.0f)) ||
                (this->skelAnime.animCurrentFrame > 44.0f) && (this->skelAnime.animCurrentFrame < 51.0f)) {
                Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
                Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0x14);
                this->actor.world.rot.y = this->actor.shape.rot.y;
            }
            if ((Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 200.0f) &&
                (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) > 200.0f)) {
                func_80BCF5F0(this);
            }
        }
    }
}

void func_80BCF5F0(EnHg* this) {
    func_800BDC5C(&this->skelAnime, animations, 0);
    this->actionFunc = func_80BCF634;
}

void func_80BCF634(EnHg* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) < 200.0f) {
        func_80BCF468(this);
    }
}

void func_80BCF68C(EnHg* this) {
    func_800BDC5C(&this->skelAnime, animations, 2);
    this->actionFunc = func_80BCF6D0;
}

void func_80BCF6D0(EnHg* this, GlobalContext* globalCtx) {
    if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
        func_80BCF5F0(this);
    }
}

void func_80BCF710(EnHg* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 0) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            func_801518B0(globalCtx, 0x24FU, &this->actor);
        } else {
            func_800B8614(&this->actor, globalCtx, 80.0f);
        }
    }
}

void func_80BCF778(EnHg* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 1) {
        if (this->actionFunc == func_80BCF4AC || this->actionFunc == func_80BCF6D0 ||
            this->actionFunc == func_80BCF634) {
            func_800B9010(&this->actor, 0x32B7);
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
    if (ActorCutscene_GetCanPlayNext(this->cutscenes[this->unk218]) != 0) {
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
    if (func_800EE29C(globalCtx, 0x1E4U) != 0) {
        u32 actionIndex = func_800EE200(globalCtx, 0x1E4U);
        if (this->cutscenes[3] != globalCtx->csCtx.npcActions[actionIndex]->unk0) {
            this->cutscenes[3] = globalCtx->csCtx.npcActions[actionIndex]->unk0;
            switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
                case 1:
                    this->currentAnimation = NULL;
                    func_800BDC5C(&this->skelAnime, animations, 0);
                    break;
                case 2:
                    this->cutscenes[2] = 0;
                    this->currentAnimation = 3;
                    func_800BDC5C(&this->skelAnime, animations, 3);
                    break;
                case 3:
                    this->cutscenes[2] = 0;
                    this->currentAnimation = 5;
                    func_800BDC5C(&this->skelAnime, animations, 5);
                    break;
                case 4:
                    this->cutscenes[2] = 0;
                    this->currentAnimation = 7;
                    if ((this->unk218 == 1) || (this->unk218 == 3)) {
                        func_8019F128(0x3ABA);
                    }
                    func_800BDC5C(&this->skelAnime, animations, 7);
                    break;
                case 5:
                    this->currentAnimation = 1;
                    func_800BDC5C(&this->skelAnime, animations, 1);
                    break;
                case 6:
                    gSaveContext.weekEventReg[0x4B] |= 0x20;
                    Actor_MarkForDeath(&this->actor);
                    break;
            }
        } else {
            if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
                switch (this->currentAnimation) {
                    case 3:
                        this->currentAnimation = 4;
                        func_800BDC5C(&this->skelAnime, animations, 4);
                        break;
                    case 5:
                        this->currentAnimation = 6;
                        func_800BDC5C(&this->skelAnime, animations, 6);
                        break;
                }
            }
        }
        switch (this->currentAnimation) {
            case 3:
            case 4:
                func_800B9010(&this->actor, 0x32B7);
                break;
            case 5:
            case 6:
                func_800B9010(&this->actor, 0x32B9);
                break;
            case 7:
                if ((this->unk218 == 0) || (this->unk218 == 2)) {
                    func_800B9010(&this->actor, 0x32B9);
                }
                break;
        }
        func_800EDF24(&this->actor, globalCtx, actionIndex);
        return;
    } else if (globalCtx->csCtx.state == 0) {
        func_80BCF354(this);
    }
    this->cutscenes[3] = 0x63;
}

void func_80BCFC0C(EnHg* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->actor.colChkInfo.health == 1 && !(fabsf(this->actor.yDistToPlayer) >= 80.0f)) {
        if (player->stateFlags2 & 0x08000000) {
            if (D_80BD00C8 == 0) {
                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            }
            D_80BD00C8 = 1;
        } else {
            D_80BD00C8 = 0;
        }
        if (globalCtx->msgCtx.unk1202A == 3) {
            if (globalCtx->msgCtx.unk1202E == 7 && gSaveContext.playerForm == PLAYER_FORM_HUMAN) {
                if (INV_CONTENT(0x41) == 0x41) {
                    this->unk218 = 3;
                } else {
                    this->unk218 = 1;
                }
                func_80BCF88C(this);
            }
        } else {
            if (this->actor.xzDistToPlayer < 60.0f && fabsf(this->actor.yDistToPlayer) < 40.0f) {
                if ((this->actionFunc != func_80BCF8A0) && (this->actionFunc != func_80BCF95C)) {
                    if ((gSaveContext.weekEventReg[0x3D] & 2) == 0) {
                        gSaveContext.weekEventReg[0x3D] |= 2;
                        this->unk218 = NULL;
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
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80BCF7D8(this, globalCtx);
    func_80BCFC0C(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 25.0f, 0.0f, 5);
    func_80BCF778(this, globalCtx);
}

// override limb
s32 EnHg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

// post limb
void EnHg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnHg* this = THIS;
    if (limbIndex == 10) {
        SysMatrix_CopyCurrentState(&this->unk1D8);
    } else if (limbIndex == 11) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
    }
}

void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnHg_OverrideLimbDraw, EnHg_PostLimbDraw, &this->actor);
    SysMatrix_SetCurrentState(&this->unk1D8);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06005E28);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
