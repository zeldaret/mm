/*
 * File: z_en_takaraya.c
 * Overlay: ovl_En_Takaraya
 * Description: Treasure Chest Shop Gal
 */

#include "z_en_takaraya.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnTakaraya*)thisx)

void EnTakaraya_Init(Actor* thisx, PlayState* play);
void EnTakaraya_Destroy(Actor* thisx, PlayState* play);
void EnTakaraya_Update(Actor* thisx, PlayState* play);
void EnTakaraya_Draw(Actor* thisx, PlayState* play);

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
void func_80ADEDF8(EnTakaraya* this);

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

extern UNK_TYPE D_06001384;
extern UNK_TYPE D_06009890;
extern UNK_TYPE D_0600A280;
extern UNK_TYPE D_0600AD98;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Init.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Destroy.s") 0xBF 0x40
void EnTakaraya_Destroy(Actor* thisx, PlayState* play) {
    EnTakaraya* this = THIS;
    Flags_UnsetSwitch(play, 5);
    if (!this->unk2AD) {
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_WAIT);
        gSaveContext.timerStates[4] = 5;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADED8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADEE4C.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF050.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF2D4.s")
void func_80ADF2D4(EnTakaraya* this) {
    Actor_PlaySfx_FlaggedCentered2(&this->actor, 0x482CU);
    Audio_PlaySubBgm(0x25U);
    this->unk2AE = 0x91;
    SET_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_WAIT);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_KICKOUT_TIME_PASSED);
    this->actionFunc = &func_80ADF338;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF338.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF4E0.s")
void func_80ADF4E0(EnTakaraya* this) {
    Interface_StartTimer(4, 0x2D);
    this->unk2AE = 1;
    this->actionFunc = &func_80ADF520;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF520.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF608.s")
void func_80ADF608(EnTakaraya* this, PlayState* play) {
    func_800B7298(play, &this->actor, 7U);
    this->unk2AD = 1;
    this->actionFunc = &func_80ADF654;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF654.s")
void func_80ADF654(EnTakaraya* this, PlayState* play) {
    if (this->unk2AE > 0) {
        this->unk2AE--;
        return;
    }
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

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF6DC.s")
void func_80ADF6DC(EnTakaraya* this) {
    Animation_PlayLoop(&this->unk144, (AnimationHeader*)&D_06001384);
    this->unk2AC = 0;
    this->actor.flags |= ACTOR_FLAG_10000;
    this->actionFunc = &func_80ADF730;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF730.s")
void func_80ADF730(EnTakaraya* this, PlayState* play) {
    SkelAnime_Update(&this->unk144);
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF94C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/func_80ADF984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Takaraya/EnTakaraya_Draw.s")
