/*
 * File: z_en_dt.c
 * Overlay: ovl_En_Dt
 * Description: Mayor Dotour
 */

#include "z_en_dt.h"

#include "objects/object_dt/object_dt.h"
#include "overlays/actors/ovl_En_Baisen/z_en_baisen.h"
#include "overlays/actors/ovl_En_Muto/z_en_muto.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnDt*)thisx)

void EnDt_Init(Actor* thisx, PlayState* play);
void EnDt_Destroy(Actor* thisx, PlayState* play);
void EnDt_Update(Actor* thisx, PlayState* play);
void EnDt_Draw(Actor* thisx, PlayState* play);

void func_80BE9CE8(EnDt *this, s32 animIndex);
void func_80BE9EF8(EnDt *this, PlayState* play);
void func_80BE9E94(EnDt *this, PlayState* play);
void func_80BEA088(EnDt *this, PlayState* play);
void func_80BEA254(EnDt *this, PlayState* play);
void func_80BEA394(EnDt *this, PlayState* play);
void func_80BEA8F0(EnDt *this, PlayState* play);
void func_80BEAAF8(EnDt *this, PlayState* play);
void func_80BEAD2C(EnDt *this, PlayState* play);
void func_80BEADD4(EnDt *this, PlayState* play);
void func_80BEAB44(EnDt *this, PlayState* play);
void func_80BEABF8(EnDt *this, PlayState* play);
void func_80BEAC84(EnDt *this, PlayState* play);
void func_80BE9D9C(EnDt *this);
void func_80BEADB8(EnDt *this);
void func_80BE9DF8(EnDt *this);

#if 0
ActorInit En_Dt_InitVars = {
    /**/ ACTOR_EN_DT,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_DT,
    /**/ sizeof(EnDt),
    /**/ EnDt_Init,
    /**/ EnDt_Destroy,
    /**/ EnDt_Update,
    /**/ EnDt_Draw,
};

static u16 sTextIds[] = { // D_80BEB1D0
    0x2ABD, 0x2ABE, 0x2ABF, 0x2AC0, 
    0x2ABE, 0x2AC1, 0x2AC2, 0x2AC3, 
    0x2AC4, 0x2ABB, 0x2ABC, 0x2AC6, 
    0x2AC7, 0x2AC8, 0x2AC9, 0x2ACA, 
    0x2ACB, 0x2ACC, 0x2ACD, 0x2ACE,
    0x2ACF, 0x2AD0, 0x2AD1, 0x2AC5, 
    0x2AD3, 0x2AD4, 0x2AD2, 0x0000 
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BEB29C = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 25, 70, 0, { 0, 0, 0 } },
};

#endif

typedef struct {
    s32 unk0;
    s32 npcVisualState[3];
} UnkStruct1;

typedef struct {
    s16 unk0;
    u16 textId;
} DialogSequenceEntry;

extern ColliderCylinderInit D_80BEB29C;

extern u16 D_80BEB1D0[24];  //sTextIds
extern s32 D_80BEB208[24];  //sDialogFocusStates?
extern s16 D_80BEB268[24];  // sTextId?
extern s16 D_80BEB26A[24];  // DialogSequenceEntries?

typedef enum {
    /* 0 */ EN_DT_ANIMATION_0,
    /* 1 */ EN_DT_ANIMATION_1,
    /* 2 */ EN_DT_ANIMATION_2,
    /* 3 */ EN_DT_ANIMATION_3,
    /* 4 */ EN_DT_ANIMATION_4,
    /* 5 */ EN_DT_ANIMATION_5,
    /* 6 */ EN_DT_ANIMATION_MAX
} EnDtAnimation;

extern AnimationHeader* D_80BEB2C8[EN_DT_ANIMATION_MAX]; // sEnDtAnimations[EN_DT_ANIMATION_MAX] = { &object_dt_Anim_00112C, &object_dt_Anim_0005A4, &object_dt_Anim_000854, &object_dt_Anim_000DA8, &object_dt_Anim_000BE0, &object_dt_Anim_00B500 };
extern u8 D_80BEB2E0[EN_DT_ANIMATION_MAX]; // sEnDtAnimationModes[EN_DT_ANIMATION_MAX] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE };
extern u8 D_80BEB2E8;

extern TexturePtr D_80BEB348[5]; // sEnDtEyeTextures[5] = { gDotourEyeShockTex, gDotourEyeOpenTex, gDotourEyeClosedTex, gDotourEyeLookDownTex, gDotourEyeSquintTex };
extern TexturePtr D_80BEB35C[3]; // sEnDtBrowTextyres[3] = { gDotourEyebrowHighTex, gDotourEyebrowMidTex, gDotourEyebrowLowTex };

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Init.s")
void EnDt_Init(Actor *thisx, PlayState *play) {
    EnDt* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_dt_Skel_00B0CC, &object_dt_Anim_00112C, this->jointTable, this->morphTable, OBJECT_DT_LIMB_MAX);

    this->actor.targetMode = 6;
    this->npcEnMuto = 0;
    this->npcEnBaisen = 0;
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &D_80BEB29C);

    if ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight)) {
        func_80BEAC84(this, play);
    } else {
        s32 csId = this->actor.csId;
        s32 i = 0;
        
        // clang-format off
        while (csId != CS_ID_NONE) { this->csIds[i] = csId; csId = CutsceneManager_GetAdditionalCsId(csId); i++; }
        // clang-format on
    }
    this->actionFunc = func_80BE9E94;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Destroy.s")
void EnDt_Destroy(Actor *thisx, PlayState *play) {
    EnDt *this = THIS;
    Collider_DestroyCylinder(play, &this->collider);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9C74.s")
// EnDt_UpdateHeadRotate?
void func_80BE9C74(EnDt *this) {
    s32 deltaAngle = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y);
    s32 absDeltaAngle = ABS_ALT(deltaAngle);

    this->headRotTarget.y = 0;
    if (absDeltaAngle < 20000) {
        this->headRotTarget.y = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y);

        if (this->headRotTarget.y > 10000) {
            this->headRotTarget.y = 10000;
        } else if (this->headRotTarget.y < -10000) {
            this->headRotTarget.y = -10000;
        }
    }
}

// EnDt_ChangeAnim?
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9CE8.s")
void func_80BE9CE8(EnDt *this, s32 animIndex) {
    f32 morphFrames;

    this->animIndex = animIndex;

    morphFrames = -4.0f;
    if (this->animIndex == 2 || this->animIndex == 5) {
        morphFrames = 0.0f;
    }

    this->animEndFrame = (f32) Animation_GetLastFrame(D_80BEB2C8[this->animIndex]);
    Animation_Change(&this->skelAnime, D_80BEB2C8[this->animIndex], 1.0f, 0.0f, this->animEndFrame, D_80BEB2E0[this->animIndex], morphFrames);
}

// EnDt_UpdateNpcState?
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9D9C.s")
// void func_80BE9D9C(EnDt *this) {
//     /*
//     s32* p = &D_80BEB2E8[this->unk280].npcVisualState;

//     func_80BE9CE8(this, *p);

//     this->eyeTexIndex = *(++p);
//     this->unk248 = *(++p);
//     */

//     s32 index = this->unk280;
//     s32* p;

//     index *= 4;
//     index++;
    
//     p = (s32*)(&D_80BEB2E8 + index * 4); // &4 &20 &36

//     index = *p;
//     func_80BE9CE8(this, *p); // 1 2 3 

//     ++p;
//     this->eyeTexIndex = *p; // 3 3 3
    
//     ++p;
//     this->unk248 = *p;  // 1 1 1
// }

// EnDt_UpdateTargetActors? or EnDt_MainAction?
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9DF8.s")
void func_80BE9DF8(EnDt* this) {
    if (this->npcEnMuto != NULL && this->npcEnBaisen != NULL) {
        EnMuto* npcEnMuto = (EnMuto*)this->npcEnMuto; 
        EnBaisen* npcEnBaisen = (EnBaisen*)this->npcEnBaisen;

        switch (D_80BEB208[this->textIdIndex]) {
            case 0:
                npcEnMuto->targetActor = this->npcEnMuto;
                npcEnBaisen->unk2A4 = this->npcEnMuto;
                this->targetActor = this->npcEnMuto;
                break;
            case 1:
                npcEnMuto->targetActor = this->npcEnBaisen;
                npcEnBaisen->unk2A4 = this->npcEnBaisen;
                this->targetActor = this->npcEnBaisen;
                break;
            case 2:
                npcEnMuto->targetActor = &this->actor;
                npcEnBaisen->unk2A4 = &this->actor;
                this->targetActor = &this->actor;
                break;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9E94.s")
// EnDt_SetupCutsceneNpcs?
void func_80BE9E94(EnDt* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if (npc->id == ACTOR_EN_MUTO) {
            this->npcEnMuto = npc;
        } else if (npc->id == ACTOR_EN_BAISEN) {
            this->npcEnBaisen = npc;
        }
        npc = npc->next;
    }
    
    func_80BE9EF8(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BE9EF8.s")
void func_80BE9EF8(EnDt* this, PlayState* play) {
    EnDtActionFunc actionFn;
    u32 textId;

    this->textIdIndex = 0;

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_60_10)) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
            this->textIdIndex = 0x15;
            this->unk280 = 5;
            func_80BE9D9C(this);

            this->actor.textId = D_80BEB1D0[this->textIdIndex];
            Message_StartTextbox(play, this->actor.textId, &this->actor);
            Player_SetCsActionWithHaltedActors(play, &this->actor, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);

            actionFn = func_80BEA394;
            this->unk254 = 1;
            this->actionFunc = actionFn;
            return;
        }
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        this->textIdIndex = 0x17;
        this->unk280 = 5;
        this->unk290 = 1;
        func_80BE9D9C(this);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);
    }

    if (this->unk280 == 0) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
            this->textIdIndex = 9;
            this->unk280 = 2;
        }

        func_80BE9D9C(this);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
            this->unk280 = 1;
        }
    }

    this->actor.textId = D_80BEB1D0[this->textIdIndex];
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        func_80BE9DF8(this);
    }

    actionFn = func_80BEA088;
    this->unk254 = 1;
    this->actionFunc = actionFn;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA088.s")
void func_80BEA088(EnDt* this, PlayState* play) {
    EnMuto* npcMuto = NULL;
    EnBaisen* npcBaisen = NULL;

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        func_80BEA254(this, play);
        return;
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        if (this->npcEnMuto != NULL && this->npcEnBaisen) {
            npcMuto = (EnMuto*)this->npcEnMuto;
            npcBaisen = (EnBaisen*)this->npcEnBaisen;
        }

        this->unk240 = 0;
        this->textIdIndex = 0;

        if (Player_GetMask(play) == PLAYER_MASK_COUPLE) {
            this->textIdIndex = 11; // "Ah!"
            this->unk240 = 1;

            if (this->npcEnMuto && this->npcEnBaisen) {
                npcMuto->textIdIndex = 4; // "Ah!"
                npcBaisen->textIdIndex = 6; // "Ah!"
            }
        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
            this->textIdIndex = 9;
        }
    }

    this->actor.textId = D_80BEB1D0[this->textIdIndex];
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && this->npcEnMuto != NULL && this->npcEnBaisen != NULL && (npcMuto->cutsceneState == 1 || npcBaisen->unk2AC == 1)) {
        func_80BEA254(this, play);
    }

    // After completing Couple's Mask event and wearing Kafeis Mask
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK)) {
        this->actor.textId = 0x2368; // "My wife hired you? Go ask the Curiosity Shop"
    }

    Actor_OfferTalk(&this->actor, play, 150.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA254.s")
void func_80BEA254(EnDt* this, PlayState* play) {
    EnMuto* npcMuto;
    EnBaisen* npcBaisen;
    s32 index;
    s16* pTextData;

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
        if (this->npcEnMuto != NULL) {
            if (this->npcEnBaisen != NULL) {
                npcMuto = (EnMuto*)this->npcEnMuto;
                npcBaisen = (EnBaisen*)this->npcEnBaisen;
            }
        }
        if ((this->npcEnMuto != NULL) && (this->npcEnBaisen != NULL)) {
            npcMuto->cutsceneState = 1;
            npcBaisen->unk2AC = 1;
            if (Player_GetMask(play) == PLAYER_MASK_COUPLE) {
                npcMuto->textIdIndex = 4;
                npcBaisen->textIdIndex = 6;
                this->unk280 = 5;
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
                    this->unk280 = 4;
                }
                func_80BE9D9C(this);
            }
        }
    }

    this->cutsceneState = 0;
    for (index = 0; index < 24; index += 2) {
        if ((play->msgCtx.currentTextId == D_80BEB268[index]) || (this->actor.textId == D_80BEB268[index])) {
            this->cutsceneState = 1;
            this->csIdIndex = index;
            break;
        }
    }

    this->unk254 = 2;
    this->actionFunc = func_80BEA394;
}

// EnDt_UpdateCutscene?
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA394.s")
void func_80BEA394(EnDt* this, PlayState* play)  {
    EnMuto* sp3C = NULL;
    EnBaisen* sp38 = NULL;
    s32 index = D_80BEB26A[this->csIdIndex];
    s32 unk30 = D_80BEB26A[this->csIdIndex];

    if (this->cutsceneState == 1) {
        if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
            CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
            CutsceneManager_Queue(this->csIds[index]);
            return;
        }

        if (!CutsceneManager_IsNext(this->csIds[index])) {
            CutsceneManager_Queue(this->csIds[index]);
            return;
        }

        CutsceneManager_StartWithPlayerCs(this->csIds[index], this->targetActor);
        Actor_ChangeFocus(&this->actor, play, this->targetActor);
        this->cutsceneState = 2;
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && (this->npcEnMuto != NULL || this->npcEnBaisen != NULL)) {
        sp3C = (EnMuto*)this->npcEnMuto;
        sp38 = (EnBaisen*)this->npcEnBaisen;
    }

    if (this->timer == 0 && Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT && Message_ShouldAdvance((play))) {
        if (this->textIdIndex == 0x15) {
            Player_SetCsActionWithHaltedActors(play, &this->actor, PLAYER_CSACTION_END);
            if (this->cutsceneState == 2) {
                CutsceneManager_Stop(this->csIds[index]);
                this->cutsceneState = 0;
            }
            func_80BEAAF8(this, play);
            return;
        }
        
        if (this->textIdIndex == 0x14) {
            Message_CloseTextbox(play);
            play->nextEntrance = ENTRANCE(MAYORS_RESIDENCE, 1);
            Scene_SetExitFade(play);
            play->transitionTrigger = TRANS_TRIGGER_START;

            SET_WEEKEVENTREG(WEEKEVENTREG_63_80);
            this->unk290 = 1;

            if (this->cutsceneState == 2) {
                CutsceneManager_Stop(this->csIds[index]);
                this->cutsceneState = 0;
            }
        } else {
            if ((this->textIdIndex == 8) || (this->textIdIndex == 0xA) || (this->textIdIndex == 0x16) || (this->textIdIndex == 0x17)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_60_08);
                Message_CloseTextbox(play);

                if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80)) {
                    if ((this->npcEnMuto != NULL) && (this->npcEnBaisen != NULL)) {
                        sp3C->cutsceneState = 2;
                        sp38->unk2AC = 2;
                        sp3C->targetActor = this->npcEnMuto;
                        sp38->unk2A4 = this->npcEnBaisen;
                    }
                    this->targetActor = &this->actor;
                }
                if (this->cutsceneState == 2) {
                    CutsceneManager_Stop(this->csIds[index]);
                    this->cutsceneState = 0;
                }
                func_80BE9EF8(this, play);
                return;
            }

            this->textIdIndex++;

            // Mayor: "Let's not bring my wife into this..." - end of cutscene
            if (this->textIdIndex == 8) {
                play->msgCtx.msgLength = 0;
                func_80BE9DF8(this);
                Actor_ChangeFocus(&this->actor, play, this->targetActor);
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csIds[index])), this->targetActor);
                
                this->timer = 2;
                this->actionFunc = func_80BEA8F0;
                return;
            }

            if (this->textIdIndex == 0xC) {
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_08)) {
                    func_80BE9D9C(this);
                    this->timer = 0x19;
                } else {
                    func_80BE9CE8(this, 4);
                    SkelAnime_Update(&this->skelAnime);
                }
            }

            if (this->textIdIndex == 0xD) {
                func_80BE9CE8(this, 4);
                SkelAnime_Update(&this->skelAnime);
            }

            func_80BE9DF8(this);
            Actor_ChangeFocus(&this->actor, play, this->targetActor);
            Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csIds[index])), this->targetActor);
            
            this->actor.textId = D_80BEB1D0[this->textIdIndex];
            Message_CloseTextbox(play);
            Message_StartTextbox(play, this->actor.textId, &this->actor);

            // Sets the cutscene ID index based off the current textId
            for (index = 0; index < 24; index += 2) {
                if (play->msgCtx.currentTextId == D_80BEB268[index] || this->actor.textId == D_80BEB268[index]) {
                    this->csIdIndex = index;
                    break;
                }
            }

            index = D_80BEB26A[this->csIdIndex];
            if (this->cutsceneState == 2 && (index != unk30)) {
                this->cutsceneState = 1;
                CutsceneManager_Stop(this->csIds[unk30]);
                CutsceneManager_Queue(this->csIds[index]);
            }

            // Mutoh turns his head to focus on the Mayor after saying "Isn't that right Mayor?"
            if (this->textIdIndex == 3 && this->npcEnMuto != NULL && this->npcEnBaisen != NULL) {
                sp3C->targetActor = &this->actor;
            }
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEA8F0.s")
void func_80BEA8F0(EnDt* this, PlayState* play) {
    f32 currFrame = this->skelAnime.curFrame;

    if (this->timer != 0) {
        if (this->timer == 1) {
            if ((this->textIdIndex == 8) || (this->unk280 == 4)) {
                func_80BE9D9C(this);
            }

            this->unk280++;
            if (this->unk280 > 5) {
                this->unk280 = 5;
            }
        }
    } else if (this->animEndFrame <= currFrame) {
        Camera* pCamera;
        s32 index;
        s32 currTextId = D_80BEB26A[this->csIdIndex];

        func_80BE9D9C(this);

        Message_CloseTextbox(play);
        this->actor.textId = D_80BEB1D0[this->textIdIndex];
        Message_StartTextbox(play, this->actor.textId, &this->actor);

        if (this->textIdIndex == 8) {
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);
        }

        // Loop through the text id array and set the index if it matches the current text id
        for (index = 0; index < 24; index++) {
            if ((play->msgCtx.currentTextId == D_80BEB268[index]) || (this->actor.textId == D_80BEB268[index])) {
                this->csIdIndex = index;
            }
        }

        index = D_80BEB26A[this->csIdIndex];
        if ((this->cutsceneState == 2) && (index != currTextId)) {
            this->cutsceneState = 1;
            CutsceneManager_Stop(this->csIds[currTextId]);
            CutsceneManager_Queue(this->csIds[index]);
        }
        
        func_80BE9DF8(this);
        Actor_ChangeFocus(&this->actor, play, this->targetActor);

        pCamera = Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(this->csIds[index]));
        Camera_SetTargetActor(pCamera, this->targetActor);
        
        this->actionFunc = func_80BEA394;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAAF8.s")
// EnDt_OfferReward?
void func_80BEAAF8(EnDt* this, PlayState* play) {
    Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 300.0f, 300.0f);
    this->unk254 = 3;
    this->actionFunc = func_80BEAB44;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAB44.s")
void func_80BEAB44(EnDt* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->textIdIndex = 0x16;
        this->actor.parent = NULL;
        this->actor.textId = D_80BEB1D0[this->textIdIndex];

        Actor_OfferTalkExchange(&this->actor, play, 400.0f, 400.0f, PLAYER_IA_MINUS1);

        SET_WEEKEVENTREG(WEEKEVENTREG_60_10);
        this->actionFunc = func_80BEABF8;
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 300.0f, 300.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEABF8.s")
void func_80BEABF8(EnDt* this, PlayState *play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        Message_BombersNotebookQueueEvent(play, 38);
        Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);
        this->actionFunc = func_80BEA394;
    } else {
        Actor_OfferTalkExchange(&this->actor, play, 400.0f, 400.0f, PLAYER_IA_MINUS1);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAC84.s")
void func_80BEAC84(EnDt* this, PlayState* play) {
    func_80BE9CE8(this, 3);

    this->unk248 = 1;
    this->textIdIndex = 0x18;
    Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_PERSON_MAYOR_DOTOUR);

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_60_40)) {
        this->textIdIndex = 0x1A;
    }

    this->actor.textId = D_80BEB1D0[this->textIdIndex];
    this->eyeTexIndex = 3;
    this->unk248 = 1;
    this->unk254 = 4;
    this->actionFunc = func_80BEAD2C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEAD2C.s")
void func_80BEAD2C(EnDt* this, PlayState *play) {
    func_80BE9C74(this);

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        func_80BEADB8(this);
        return;
    }

    // After completing Couple's Mask event and wearing Kafeis Mask
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        this->actor.textId = 0x2368; // "My wife hired you? Go ask the Curiosity Shop"
    }

    Actor_OfferTalk(&this->actor, play, 150.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEADB8.s")
void func_80BEADB8(EnDt* this) {
    this->unk254 = 5;
    this->actionFunc = func_80BEADD4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEADD4.s")
// EnDt_InDialogue?
void func_80BEADD4(EnDt* this, PlayState* play) {
    func_80BE9C74(this);

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && (Message_ShouldAdvance(play) != 0)) {
        Message_CloseTextbox(play);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_60_40)) {
            this->textIdIndex = 0x19;
            Message_ContinueTextbox(play, D_80BEB1D0[this->textIdIndex]);
            SET_WEEKEVENTREG(WEEKEVENTREG_60_40);
            return;
        }
        func_80BEAC84(this, play);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Update.s")
void EnDt_Update(Actor* thisx, PlayState* play) {
    EnDt* this = THIS;
    ColliderCylinder* collider;

    SkelAnime_Update(&this->skelAnime);
    Actor_SetScale(&this->actor, 0.01f);

    if ((this->unk254 != 4) && (this->unk254 != 5) && (gSaveContext.save.day == 3) && (gSaveContext.save.isNight != 0)) {
        func_80BEAC84(this, play);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_63_80) && ((gSaveContext.save.day != 3) || ((gSaveContext.save.day == 3) && (gSaveContext.save.isNight == 0)))) {
        Audio_PlaySequenceAtPos(SEQ_PLAYER_BGM_SUB, &gSfxDefaultPos, NA_BGM_MAYORS_OFFICE, 1000.0f);
        Actor_PlaySfx(&this->actor, 0x205DU);
    }

    DECR(this->unk24A);
    DECR(this->timer);

    if (this->unk290 != 0) {
        func_80BE9C74(this);
    }

    // Blinking update?
    if ((this->unk248 == 0) && (this->unk24A == 0)) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 3) {
            this->eyeTexIndex = 0;
            this->unk24A = (s32) Rand_ZeroFloat(60.0f) + 20;
        }
    }

    this->actionFunc(this, play);

    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_SmoothStepToS(&this->headRotValue.y, this->headRotTarget.y, 1, 3000, 0);
    
    Actor_SetFocus(&this->actor, 60.0f);
    Actor_MoveWithGravity(&this->actor);

    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &collider->base);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/func_80BEB06C.s")
// EnDt_OverrideLimbDraw
s32 func_80BEB06C(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDt* this = THIS;

    if (limbIndex == OBJECT_DT_LIMB_0C) {
        rot->y += -1 * this->headRotValue.y;
    }
    
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dt/EnDt_Draw.s")
void EnDt_Draw(Actor* thisx, PlayState* play) {
    EnDt* this = THIS;
    s32 eyebrowIndex = 0;

    OPEN_DISPS(play->state.gfxCtx);
    
    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BEB348[this->eyeTexIndex]));

    if (this->eyeTexIndex < 3) {
        eyebrowIndex = this->eyeTexIndex;
    }

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80BEB35C[eyebrowIndex]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, func_80BEB06C, NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
