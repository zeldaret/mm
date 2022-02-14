/*
 * File: z_en_gakufu.c
 * Overlay: ovl_En_Gakufu
 * Description: Termina Field - 2D Song Buttons Appearing on Wall
 */

#include "z_en_gakufu.h"
#include "interface/parameter_static/parameter_static.h"

#define FLAGS 0x02000010

#define THIS ((EnGakufu*)thisx)

extern OcarinaSongButtons gOcarinaSongButtons[24];

void EnGakufu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGakufu_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnGakufu_ProcessNotes(EnGakufu* this);
s32 EnGakufu_IsWithinRange(EnGakufu* this, GlobalContext* globalCtx);
void EnGakufu_DisplayOnTimer(EnGakufu* this, GlobalContext* globalCtx);
void EnGakufu_WaitForTimer(EnGakufu* this, GlobalContext* globalCtx);
void EnGakufu_DoNothing(EnGakufu* this, GlobalContext* globalCtx);
void EnGakufu_GiveReward(EnGakufu* this, GlobalContext* globalCtx);
void EnGakufu_PlayRewardCutscene(EnGakufu* this, GlobalContext* globalCtx);
void EnGakufu_WaitForSong(EnGakufu* this, GlobalContext* globalCtx);

const ActorInit En_Gakufu_InitVars = {
    ACTOR_EN_GAKUFU,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGakufu),
    (ActorFunc)EnGakufu_Init,
    (ActorFunc)EnGakufu_Destroy,
    (ActorFunc)EnGakufu_Update,
    (ActorFunc)EnGakufu_Draw,
};

Vec3f sRewardDropsSpawnPos = {
    -710.0f,
    -123.0f,
    -3528.0f,
};

u8 sRewardDropsIndex[] = {
    3,  // CLOCK_TIME(0, 0) - CLOCKTIME(1, 0)
    12, // CLOCK_TIME(1, 0) - CLOCKTIME(2, 0)
    6,  // CLOCK_TIME(2, 0) - CLOCKTIME(3, 0)
    12, // CLOCK_TIME(3, 0) - CLOCKTIME(4, 0)
    9,  // CLOCK_TIME(4, 0) - CLOCKTIME(5, 0)
    12, // CLOCK_TIME(5, 0) - CLOCKTIME(6, 0)
    0,  // CLOCK_TIME(6, 0) - CLOCKTIME(7, 0)
    12, // CLOCK_TIME(7, 0) - CLOCKTIME(8, 0)
    3,  // CLOCK_TIME(8, 0) - CLOCKTIME(9, 0)
    12, // CLOCK_TIME(9, 0) - CLOCKTIME(10, 0)
    6,  // CLOCK_TIME(10, 0) - CLOCKTIME(11, 0)
    12, // CLOCK_TIME(11, 0) - CLOCKTIME(12, 0)
    3,  // CLOCK_TIME(12, 0) - CLOCKTIME(13, 0)
    12, // CLOCK_TIME(13, 0) - CLOCKTIME(14, 0)
    6,  // CLOCK_TIME(14, 0) - CLOCKTIME(15, 0)
    12, // CLOCK_TIME(15, 0) - CLOCKTIME(16, 0)
    3,  // CLOCK_TIME(16, 0) - CLOCKTIME(17, 0)
    12, // CLOCK_TIME(17, 0) - CLOCKTIME(18, 0)
    6,  // CLOCK_TIME(18, 0) - CLOCKTIME(19, 0)
    12, // CLOCK_TIME(19, 0) - CLOCKTIME(20, 0)
    9,  // CLOCK_TIME(20, 0) - CLOCKTIME(21, 0)
    12, // CLOCK_TIME(21, 0) - CLOCKTIME(22, 0)
    6,  // CLOCK_TIME(22, 0) - CLOCKTIME(23, 0)
    12, // CLOCK_TIME(23, 0) - CLOCKTIME(0, 0)
};

u8 sRewardDrops[] = {
    ITEM00_RUPEE_RED,   ITEM00_RUPEE_RED,   ITEM00_RUPEE_RED,   // Set 1 (index 0)
    ITEM00_RUPEE_RED,   ITEM00_RUPEE_GREEN, ITEM00_RUPEE_GREEN, // Set 2 (index 3)
    ITEM00_RUPEE_BLUE,  ITEM00_RUPEE_BLUE,  ITEM00_RUPEE_BLUE,  // Set 3 (index 6)
    ITEM00_RUPEE_RED,   ITEM00_RUPEE_BLUE,  ITEM00_RUPEE_BLUE,  // Set 4 (index 9)
    ITEM00_RUPEE_GREEN, ITEM00_RUPEE_GREEN, ITEM00_RUPEE_GREEN, // Set 5 (index 12)
};

// y-offset of ocarina buttons drawn on wall
f32 sOcarinaBtnWallYOffset[] = {
    -4.0f, -2.0f, 0.0f, 1.0f, 3.0f,
};

// Segment addresses for ocarina notes
TexturePtr sOcarinaBtnWallTextures[] = {
    gOcarinaATex, gOcarinaCDownTex, gOcarinaCRightTex, gOcarinaCLeftTex, gOcarinaCUpTex,
};

#include "overlays/ovl_En_Gakufu/ovl_En_Gakufu.c"

void EnGakufu_ProcessNotes(EnGakufu* this) {
    OcarinaStaff* playbackStaff;
    OcarinaSongButtons* ocarinaSongButtons;
    s32 songNumButtons;
    s32 i;
    s32 songIndex;

    AudioOcarina_TerminaWallGenerateNotes();
    AudioOcarina_SetInstrumentId(1);
    AudioOcarina_StartDefault((1 << this->songIndex) | 0x80000000);
    playbackStaff = AudioOcarina_GetPlaybackStaff();
    playbackStaff->pos = 0;
    playbackStaff->state = 0xFF;
    AudioOcarina_SetInstrumentId(0);

    songIndex = this->songIndex;
    ocarinaSongButtons = &gOcarinaSongButtons[songIndex];
    songNumButtons = gOcarinaSongButtons[this->songIndex].numButtons;

    for (i = 0; i < songNumButtons; i++) {
        this->buttonIdx[i] = ocarinaSongButtons->buttonIdx[i];
    }

    for (; i < ARRAY_COUNT(this->buttonIdx); i++) {
        this->buttonIdx[i] = OCARINA_BTN_INVALID;
    }
}

void EnGakufu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGakufu* this = THIS;

    this->songIndex = OCARINA_SONG_TERMINA_WALL;
    EnGakufu_ProcessNotes(this);
    Actor_SetScale(&this->actor, 1.0f);

    if (GAKUFU_GET_TYPE(&this->actor) == GAKUFU_MILK_BAR) {
        this->actor.draw = NULL;
        this->actionFunc = EnGakufu_WaitForTimer;
        return;
    }

    this->actor.flags &= ~0x2000000;

    if (EnGakufu_IsWithinRange(this, globalCtx)) {
        gSaveContext.eventInf[3] |= 2;
    } else {
        gSaveContext.eventInf[3] &= (u8)~2;
    }

    this->actionFunc = EnGakufu_WaitForSong;
    gSaveContext.eventInf[3] &= (u8)~4;
}

void EnGakufu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGakufu* this = THIS;

    if (GAKUFU_GET_TYPE(&this->actor) != GAKUFU_MILK_BAR) {
        gSaveContext.eventInf[3] &= (u8)~2;
    }
}

/**
 * Special behaviour for the Milk Bar:
 * this->actor.home.rot.x acts as a timer. Draws the notes on the back of the stage
 * until the timer runs out
 */
void EnGakufu_DisplayOnTimer(EnGakufu* this, GlobalContext* globalCtx) {
    if (this->actor.home.rot.x > 0) {
        this->actor.draw = EnGakufu_Draw;
        this->actor.home.rot.x--;
    } else {
        this->actor.draw = NULL;
        this->actor.home.rot.x = 0;
        this->actionFunc = EnGakufu_WaitForTimer;
    }
}

/**
 * Special behaviour for the Milk Bar:
 * this->actor.home.rot.x acts as a timer. Waits for this timer to be set,
 * then rerolls the notes and start displaying the notes
 */
void EnGakufu_WaitForTimer(EnGakufu* this, GlobalContext* globalCtx) {
    if (this->actor.home.rot.x > 0) {
        EnGakufu_ProcessNotes(this);
        this->actionFunc = EnGakufu_DisplayOnTimer;
    }
}

void EnGakufu_DoNothing(EnGakufu* this, GlobalContext* globalCtx) {
}

s32 EnGakufu_IsWithinRange(EnGakufu* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 600.0f) {
        return true;
    } else {
        return false;
    }
}

/**
 * Reward the player with three item drops depending on the time of day
 */
void EnGakufu_GiveReward(EnGakufu* this, GlobalContext* globalCtx) {
    s32 index;
    s32 i;

    play_sound(NA_SE_SY_CORRECT_CHIME);

    // 24 hours / The total time in a day
    index = gSaveContext.time * (24.0f / 0x10000);
    for (i = 0; i < 3; i++) {
        Item_DropCollectible(globalCtx, &sRewardDropsSpawnPos, sRewardDrops[i + sRewardDropsIndex[index]]);
    }

    this->actionFunc = EnGakufu_DoNothing;
}

void EnGakufu_PlayRewardCutscene(EnGakufu* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene == -1) {
        EnGakufu_GiveReward(this, globalCtx);
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        EnGakufu_GiveReward(this, globalCtx);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnGakufu_WaitForSong(EnGakufu* this, GlobalContext* globalCtx) {
    if (gSaveContext.eventInf[3] & 2) {
        if (gSaveContext.eventInf[3] & 4) {
            gSaveContext.eventInf[3] &= (u8)~2;
            gSaveContext.eventInf[3] &= (u8)~4;

            this->actionFunc = EnGakufu_PlayRewardCutscene;
            EnGakufu_PlayRewardCutscene(this, globalCtx);
            this->actor.draw = NULL;
        } else if (!EnGakufu_IsWithinRange(this, globalCtx)) {
            gSaveContext.eventInf[3] &= (u8)~2;
        }
    } else if (EnGakufu_IsWithinRange(this, globalCtx)) {
        gSaveContext.eventInf[3] |= 2;
    }
}

void EnGakufu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGakufu* this = THIS;

    this->actionFunc(this, globalCtx);
}

void EnGakufu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;
    EnGakufu* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_XLU_DISP++);
    gSPSegment(POLY_XLU_DISP++, 0x02, globalCtx->interfaceCtx.parameterSegment);

    for (i = 0; (i < 8) && (this->buttonIdx[i] != OCARINA_BTN_INVALID); i++) {
        Matrix_StatePush();
        Matrix_InsertTranslation(30 * i - 105, sOcarinaBtnWallYOffset[this->buttonIdx[i]] * 7.5f, 1.0f, MTXMODE_APPLY);
        Matrix_Scale(0.6f, 0.6f, 0.6f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetTextureLUT(POLY_XLU_DISP++, G_TT_NONE);
        gDPSetTextureImage(POLY_XLU_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, sOcarinaBtnWallTextures[this->buttonIdx[i]]);

        // clang-format off
        gDPSetTile(POLY_XLU_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD); \
        gDPLoadSync(POLY_XLU_DISP++); \
        gDPLoadBlock(POLY_XLU_DISP++, G_TX_LOADTILE, 0, 0, 127, 1024);
        // clang-format on

        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetTile(POLY_XLU_DISP++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 4,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD);
        gDPSetTileSize(POLY_XLU_DISP++, G_TX_RENDERTILE, 0, 0, 0x3C, 0x3C);

        if (this->buttonIdx[i] == 0) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 80, 150, 255, 200);
        } else {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 50, 200);
        }

        gSPDisplayList(POLY_XLU_DISP++, gGakufuButtonIdxDL);

        Matrix_StatePop();
    }

    gSPSegment(POLY_XLU_DISP++, 0x02, globalCtx->sceneSegment);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
