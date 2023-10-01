/*
 * File: z_en_takaraya.c
 * Overlay: ovl_En_Takaraya
 * Description: Treasure Chest Shop Gal
 */

#include "z_en_takaraya.h"
#include "objects/object_bg/object_bg.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnTakaraya*)thisx)

void EnTakaraya_Init(Actor* thisx, PlayState* play);
void EnTakaraya_Destroy(Actor* thisx, PlayState* play);
void EnTakaraya_Update(Actor* thisx, PlayState* play);
void EnTakaraya_Draw(Actor* thisx, PlayState* play);

void func_80ADED8C(EnTakaraya* this);
void func_80ADEDF8(EnTakaraya* this);
void func_80ADF2D4(EnTakaraya* this);
void func_80ADEE4C(EnTakaraya* this, PlayState* play);
void func_80ADF03C(EnTakaraya* this);
void func_80ADF050(EnTakaraya* this, PlayState* play);
void func_80ADF338(EnTakaraya* this, PlayState* play);
void func_80ADF4E0(EnTakaraya* this);
void func_80ADF520(EnTakaraya* this, PlayState* play);
void func_80ADF608(EnTakaraya* this, PlayState* play);
void func_80ADF654(EnTakaraya* this, PlayState* play);
void func_80ADF6DC(EnTakaraya* this);
void func_80ADF730(EnTakaraya* this, PlayState* play);
void func_80ADF7B8(EnTakaraya* this);
void func_80ADF7CC(EnTakaraya* this, PlayState* play);

s32 EnTakaraya_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnTakaraya_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx);

#if 0
ActorInit En_Takaraya_InitVars = {
    ACTOR_EN_TAKARAYA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnTakaraya),
    (ActorFunc)EnTakaraya_Init,
    (ActorFunc)EnTakaraya_Destroy,
    (ActorFunc)EnTakaraya_Update,
    (ActorFunc)EnTakaraya_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ADFB20[] = {
    ICHAIN_U8(targetMode, TARGET_MODE_6, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80ADFB20[];

extern void* D_80ADFB00[4];
extern void* D_80ADFB10[4];
extern u32 D_80ADFB28;
extern u16 D_80ADFB2C[6];

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Init.s")
void EnTakaraya_Init(Actor* thisx, PlayState* play) {
    EnTakaraya* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80ADFB20);
    ActorShape_Init(&this->actor.shape, -60.0f, ((void*)0), 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_bg_Skel_008FC8, &object_bg_Anim_009890, this->jointTable,
                       this->morphTable, 24);
    this->unk2B2 = (this->actor.params >> 8) & 0xFF;
    thisx->params &= 0xFF;
    if (!D_80ADFB28) {
        for (i = 0; i < (s32)(sizeof(D_80ADFB10) / sizeof(D_80ADFB10[0])); i++) {
            D_80ADFB00[i] = Lib_SegmentedToVirtual(D_80ADFB00[i]);
            D_80ADFB10[i] = Lib_SegmentedToVirtual(D_80ADFB10[i]);
        }
        D_80ADFB28 = 1;
    }
    this->unk2AC = 2;
    if (gSaveContext.save.entrance == 0x2810) {
        Audio_StopSubBgm();
        if (gSaveContext.timerStates[4] == TIMER_STATE_6) {
            this->actor.textId = 0x77A;
            gSaveContext.timerStates[4] = TIMER_STATE_STOP;
            func_80ADF6DC(this);
        } else {
            this->actor.textId = 0x77C;
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_TIME_PASSED)) {
                CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_WAIT);
                CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_TIME_PASSED);
                func_80ADEDF8(this);
            } else {
                func_80ADF6DC(this);
            }
        }
    } else {
        func_80ADEDF8(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Destroy.s") 0xBF 0x40
void EnTakaraya_Destroy(Actor* thisx, PlayState* play) {
    EnTakaraya* this = THIS;

    Flags_UnsetSwitch(play, 5);
    if (!this->unk2AD) {
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_WAIT);
        gSaveContext.timerStates[4] = 5;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADED8C.s")
void func_80ADED8C(EnTakaraya* this) {
    if (this->unk2AC != 0) {
        this->unk2AC++;
        if (this->unk2AC == 4) {
            this->unk2AC = 0;
        }
    } else if (Rand_ZeroOne() < 0.02f) {
        this->unk2AC++;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEDF8.s")
void func_80ADEDF8(EnTakaraya* this) {
    if (this->skelAnime.animation == &object_bg_Anim_001384) {
        Animation_MorphToPlayOnce(&this->skelAnime, &object_bg_Anim_00AD98, 5.0f);
    }
    this->actionFunc = func_80ADEE4C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEE4C.s")
void func_80ADEE4C(EnTakaraya* this, PlayState* play) {
    u16 temp_v0;
    s16 new_var;

    if (SkelAnime_Update(&this->skelAnime) != 0) {
        if ((&object_bg_Anim_00A280) == (*this).skelAnime.animation) {
            Animation_MorphToPlayOnce(&this->skelAnime, &object_bg_Anim_00AD98, 5.0f);
        } else {
            Animation_MorphToLoop(&this->skelAnime, &object_bg_Anim_009890, -4.0f);
        }
    }
    if (Actor_ProcessTalkRequest(&this->actor, &play->state) != 0) {
        if (Text_GetFaceReaction(play, FACE_REACTION_SET_TREASURE_CHEST_SHOP_GAL) == 0) {
            Animation_MorphToPlayOnce(&this->skelAnime, &object_bg_Anim_00A280, -4.0f);
        }
        func_80ADF03C(this);
    } else if (Actor_IsFacingPlayer(&this->actor, 0x2000) != 0) {
        temp_v0 = Text_GetFaceReaction(play, FACE_REACTION_SET_TREASURE_CHEST_SHOP_GAL);
        this->actor.textId = temp_v0;
        if (!(temp_v0 & 0xFFFF)) {
            new_var = gSaveContext.save.playerForm;
            this->actor.textId = D_80ADFB2C[new_var];
        }
        this->unk2B0 = gSaveContext.save.playerForm + this->unk2B2;
        Actor_OfferTalk(&this->actor, play, 120.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEF74.s")
extern UNK_TYPE1 D_80ADFB39;
extern UNK_TYPE1 D_80ADFB38;

void func_80ADEF74(Actor* thisx, PlayState* play) {
    EnTakaraya* this = THIS;
    u8 var_v1;

    if (Flags_GetSwitch(play, this->unk2B0) != 0) {
        var_v1 = *((&D_80ADFB39) + (gSaveContext.save.playerForm * 2));
    } else {
        var_v1 = *((&D_80ADFB38) + (gSaveContext.save.playerForm * 2));
    }
    if (gSaveContext.save.playerForm) {}
    Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, 0x1BB, 0.0f, 0.0f, 0.0f, 0, 0, 5,
                                  ((var_v1 << 5) + thisx->params) + 0xB000, thisx->csId, 0x3FFU, NULL);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF03C.s")
void func_80ADF03C(EnTakaraya* this) {
    this->actionFunc = &func_80ADF050;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF050.s")
extern u16 D_80ADFB44[];

void func_80ADF050(EnTakaraya* this, PlayState* play) {
    u8 talkState;

    if (SkelAnime_Update(&this->skelAnime) != 0) {
        if (this->skelAnime.animation == &object_bg_Anim_00AD98) {
            Animation_PlayOnce(&this->skelAnime, &object_bg_Anim_000968);
        } else if (this->skelAnime.animation == &object_bg_Anim_00A280) {
            Animation_PlayLoop(&this->skelAnime, (AnimationHeader*)&object_bg_Anim_001384);
        } else {
            Animation_PlayLoop(&this->skelAnime, &object_bg_Anim_009890);
        }
    }
    talkState = Message_GetState(&play->msgCtx);
    if ((talkState == TEXT_STATE_CLOSING) || (talkState == TEXT_STATE_DONE)) {
        if (this->actor.textId == 0x778) {
            func_80ADF2D4(this);
        } else {
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_WAIT);
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_TIME_PASSED);
            func_80ADEDF8(this);
        }
    } else if ((talkState == TEXT_STATE_1) && (this->actor.textId != 0x778)) {
        if (Message_ShouldAdvance(play) != 0) {
            Animation_MorphToPlayOnce(&this->skelAnime, &object_bg_Anim_00AD98, 5.0f);
        }
    } else if ((talkState == TEXT_STATE_CHOICE) && (Message_ShouldAdvance(play) != 0)) {
        if (play->msgCtx.choiceIndex == 0) {
            if (gSaveContext.save.saveInfo.playerData.rupees < play->msgCtx.unk1206C) {
                this->actor.textId = 0x77B;
                if (this->skelAnime.animation == &object_bg_Anim_009890) {
                    Animation_MorphToPlayOnce(&this->skelAnime, &object_bg_Anim_000968, 5.0f);
                }
                Audio_PlaySfx(NA_SE_SY_ERROR);
            } else {
                Audio_PlaySfx_MessageDecide();
                Rupees_ChangeBy(play->msgCtx.unk1206C * -1);
                func_80ADEF74(&this->actor, play);
                this->actor.textId = 0x778;
                if (this->skelAnime.animation != &object_bg_Anim_009890) {
                    Animation_MorphToLoop(&this->skelAnime, &object_bg_Anim_009890, 5.0f);
                }
            }
        } else {
            Audio_PlaySfx_MessageCancel();
            this->actor.textId = D_80ADFB44[(void)0, gSaveContext.save.playerForm];
            if (this->skelAnime.animation == &object_bg_Anim_009890) {
                Animation_MorphToPlayOnce(&this->skelAnime, &object_bg_Anim_000968, 5.0f);
            }
        }
        Message_ContinueTextbox(play, this->actor.textId);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF2D4.s")
void func_80ADF2D4(EnTakaraya* this) {
    Actor_PlaySfx_FlaggedCentered2(&this->actor, 0x482CU);
    Audio_PlaySubBgm(0x25U);
    this->unk2AE = 0x91;
    SET_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_WAIT);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_TIME_PASSED);
    this->actionFunc = &func_80ADF338;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF338.s")
void func_80ADF338(EnTakaraya* this, PlayState* play) {
    Actor* chest = play->actorCtx.actorLists[ACTORCAT_CHEST].first;
    Actor* player = play->actorCtx.actorLists[ACTORCAT_PLAYER].first;
    Vec3f sp3C;
    Vec3f sp30;
    f32 sp2C;
    s16 sp2A;

    SkelAnime_Update(&this->skelAnime);
    if ((CutsceneManager_GetCurrentCsId() == this->actor.csId) && (chest != NULL)) {
        this->unk2AE--;
        sp2A = CutsceneManager_GetCurrentSubCamId((s16)this->actor.csId);
        if (this->unk2AE >= 0x1A) {
            sp2C = 250.0f;
        } else {
            sp2C = ((chest->xzDistToPlayer - 250.0f) * (f32)(0x19 - this->unk2AE) * 0.04f) + 250.0f;
        }
        sp3C.x = (Math_SinS(chest->yawTowardsPlayer) * sp2C) + chest->world.pos.x;
        sp3C.y = player->world.pos.y + 120.0f;
        sp3C.z = (Math_CosS(chest->yawTowardsPlayer) * sp2C) + chest->world.pos.z;
        sp30.x = sp3C.x - (Math_SinS(chest->yawTowardsPlayer) * 250.0f);
        sp30.y = sp3C.y - 90.0f;
        sp30.z = sp3C.z - (Math_CosS(chest->yawTowardsPlayer) * 250.0f);
        Play_SetCameraAtEye(play, sp2A, &sp30, &sp3C);
    } else if (this->unk2AE < 0x91) {
        func_80ADF4E0(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF4E0.s")
void func_80ADF4E0(EnTakaraya* this) {
    Interface_StartTimer(4, 0x2D);
    this->unk2AE = 1;
    this->actionFunc = &func_80ADF520;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF520.s")
void func_80ADF520(EnTakaraya* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Play_InCsMode(play) == 0) {
        if (Flags_GetTreasure(play, this->actor.params) != 0) {
            Flags_SetSwitch(play, this->unk2B0);
            play->actorCtx.sceneFlags.chest &= ~(1 << this->actor.params);
            this->unk2AE = 0;
            gSaveContext.timerStates[4] = 6;
            func_80ADF608(this, play);
        } else if (gSaveContext.timerCurTimes[4] == 0) {
            this->unk2AE = 0x32;
            Message_StartTextbox(play, 0x77D, &this->actor);
            gSaveContext.timerStates[4] = 5;
            func_80ADF608(this, play);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF608.s")
void func_80ADF608(EnTakaraya* this, PlayState* play) {
    func_800B7298(play, &this->actor, 7);
    this->unk2AD = 1;
    this->actionFunc = &func_80ADF654;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF654.s")
void func_80ADF654(EnTakaraya* this, PlayState* play) {
    if (this->unk2AE > 0) {
        this->unk2AE--;
    } else {
        if (gSaveContext.timerStates[4] == 6) {
            play->transitionType = 0x50;
            gSaveContext.nextTransitionType = 3;
        } else {
            play->transitionType = 0x40;
            gSaveContext.nextTransitionType = 2;
        }
        gSaveContext.nextCutsceneIndex = 0;
        play->nextEntrance = 0x2810;
        play->transitionTrigger = 0x14;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF6DC.s")
void func_80ADF6DC(EnTakaraya* this) {
    Animation_PlayLoop(&this->skelAnime, (AnimationHeader*)&object_bg_Anim_001384);
    this->unk2AC = 0;
    this->actor.flags |= ACTOR_FLAG_10000;
    this->actionFunc = &func_80ADF730;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF730.s")
void func_80ADF730(EnTakaraya* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Actor_ProcessTalkRequest(&this->actor, &play->state) != 0) {
        this->actor.flags &= 0xFFFEFFFF;
        func_80ADF7B8(this);
    } else {
        this->unk2B0 = gSaveContext.save.playerForm + this->unk2B2;
        Actor_OfferTalk(&this->actor, play, 120.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF7B8.s")
void func_80ADF7B8(EnTakaraya* this) {
    this->actionFunc = &func_80ADF7CC;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF7CC.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Update.s")
void EnTakaraya_Update(Actor* thisx, PlayState* play) {
    EnTakaraya* this = THIS;
    s32 pad;
    Vec3s torsoRot;

    this->actionFunc(this, play);
    Actor_TrackPlayer(play, &this->actor, &this->headRot, &torsoRot, this->actor.focus.pos);
    func_80ADED8C(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF94C.s")
s32 EnTakaraya_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTakaraya* this = THIS;

    if (limbIndex == 5) {
        rot->x += this->headRot.y;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF984.s")
void EnTakaraya_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnTakaraya* this = THIS;

    if (limbIndex == 5) {
        Matrix_RotateYS((s16)(0x400 - this->headRot.x), MTXMODE_APPLY);
        Matrix_MultVecX(500.0f, &thisx->focus.pos);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Draw.s")
void EnTakaraya_Draw(Actor* thisx, PlayState* play) {
    EnTakaraya* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    if ((gSaveContext.save.playerForm == PLAYER_FORM_DEKU) || (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
        gSPSegment(POLY_OPA_DISP++, 0x08, D_80ADFB10[this->unk2AC]);
    } else {
        gSPSegment(POLY_OPA_DISP++, 0x08, D_80ADFB00[this->unk2AC]);
    }
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnTakaraya_OverrideLimbDraw, NULL,
                                   EnTakaraya_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
