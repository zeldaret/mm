#include "global.h"
#include "z64shrink_window.h"
#include "z64view.h"
#include "message_data_static.h"
#include "interface/parameter_static/parameter_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

u8 D_801C6A70 = 0;
s16 sOcarinaButtonIndexBufPos = 0;
s16 sOcarinaButtonIndexBufLen = 0;
s16 sLastPlayedSong = 0xFF;
s16 sOcarinaButtonStepR = 0;
s16 sOcarinaButtonStepG = 0;
s16 sOcarinaButtonStepB = 0;
s16 sOcarinaButtonFlashTimer = 12;
s16 sOcarinaButtonFlashColorIndex = 1;
s16 D_801C6A94 = 0;

u8 D_801C6A98[][5] = {
    { BTN_ENABLED, BTN_ENABLED, BTN_DISABLED, BTN_ENABLED, BTN_ENABLED },
    { BTN_ENABLED, BTN_ENABLED, BTN_DISABLED, BTN_ENABLED, BTN_ENABLED },
    { BTN_ENABLED, BTN_DISABLED, BTN_DISABLED, BTN_ENABLED, BTN_ENABLED },
    { BTN_ENABLED, BTN_DISABLED, BTN_DISABLED, BTN_ENABLED, BTN_ENABLED },
    { BTN_ENABLED, BTN_ENABLED, BTN_DISABLED, BTN_ENABLED, BTN_ENABLED },
    { BTN_ENABLED, BTN_ENABLED, BTN_DISABLED, BTN_ENABLED, BTN_ENABLED },
};

u16 D_801C6AB8[] = {
    0x2147, 0x2134, 0x2135, 0x2136, 0x2137, 0x2138, 0x2139, 0x213A, 0x213B, 0x213C, 0x213D, 0x213E, 0x213F, 0x2140,
    0x2141, 0x2142, 0x2143, 0x2144, 0x2145, 0x2146, 0x2152, 0x2153, 0x2154, 0,      0x2156, 0x2157, 0x2158, 0x2159,
    0x215A, 0x215B, 0,      0x215D, 0,      0x215F, 0x2160, 0x2161, 0,      0x2163, 0x2164, 0x2165, 0x2166, 0x2167,
    0x2168, 0x2169, 0x216A, 0x216B, 0x216C, 0x216D, 0x216E, 0x216F, 0x2170, 0x2171, 0x2172, 0x2173, 0x2174, 0,
};
u16 D_801C6B28[] = {
    0x4408, 0x4201, 0x4202, 0x4204, 0x4208, 0x4210, 0x4220, 0x4240, 0x4280, 0x4301, 0x4302, 0x4304, 0x4308, 0x4310,
    0x4320, 0x4340, 0x4380, 0x4401, 0x4402, 0x4404, 0x4410, 0x4420, 0x4440, 0x4480, 0x4501, 0x4502, 0x4504, 0x4508,
    0x4510, 0x4520, 0x4540, 0x4580, 0x4601, 0x4602, 0x4604, 0x4608, 0x4610, 0x4620, 0x4640, 0x4680, 0x4701, 0x4702,
    0x4704, 0x4708, 0x4710, 0x4720, 0x4740, 0x4780, 0x4801, 0x4802, 0x4804, 0x4808, 0x4810, 0x4820, 0x4840, 0,
};

// TODO: Scripts
// Include message tables D_801C6B98 and D_801CFB08
#include "src/code/z_message_tables.inc.c"

s16 D_801CFC78[] = { 0, 1, 3, 2, 14, 14, 0, 14, 0, 0, 0, 14, 14, 4, 14 };
u8 sOcarinaButtonIndexBuf[12] = { 0 };
s16 sOcarinaButtonAlphaValues[9] = { 0 };
s16 gOcarinaSongItemMap[] = {
    OCARINA_SONG_SONATA,        OCARINA_SONG_GORON_LULLABY, OCARINA_SONG_NEW_WAVE,
    OCARINA_SONG_ELEGY,         OCARINA_SONG_OATH,          OCARINA_SONG_SARIAS,
    OCARINA_SONG_TIME,          OCARINA_SONG_HEALING,       OCARINA_SONG_EPONAS,
    OCARINA_SONG_SOARING,       OCARINA_SONG_STORMS,        OCARINA_SONG_SUNS,
    OCARINA_SONG_INVERTED_TIME, OCARINA_SONG_DOUBLE_TIME,   OCARINA_SONG_GORON_LULLABY_INTRO,
};

// bss

s32 sCharTexSize;
s32 sCharTexScale;
s32 D_801F6B08;

s16 sOcarinaButtonAPrimR;
s16 sOcarinaButtonAPrimB;
s16 sOcarinaButtonAPrimG;
s16 sOcarinaButtonAEnvR;
s16 sOcarinaButtonAEnvB;
s16 sOcarinaButtonAEnvG;
s16 sOcarinaButtonCPrimR;
s16 sOcarinaButtonCPrimB;
s16 sOcarinaButtonCPrimG;
s16 sOcarinaButtonCEnvR;
s16 sOcarinaButtonCEnvB;
s16 sOcarinaButtonCEnvG;

void Message_ResetOcarinaButtonAlphas(void) {
    sOcarinaButtonIndexBuf[0] = OCARINA_BTN_INVALID;
    sOcarinaButtonAlphaValues[0] = sOcarinaButtonAlphaValues[1] = sOcarinaButtonAlphaValues[2] =
        sOcarinaButtonAlphaValues[3] = sOcarinaButtonAlphaValues[4] = sOcarinaButtonAlphaValues[5] =
            sOcarinaButtonAlphaValues[6] = sOcarinaButtonAlphaValues[7] = sOcarinaButtonAlphaValues[8] = 0;
}

void Message_ResetOcarinaButtonState(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->ocarinaButtonsPosY[0] = 189;
    msgCtx->ocarinaButtonsPosY[1] = 184;
    msgCtx->ocarinaButtonsPosY[2] = 179;
    msgCtx->ocarinaButtonsPosY[3] = 174;
    msgCtx->ocarinaButtonsPosY[4] = 169;

    Message_ResetOcarinaButtonAlphas();

    sOcarinaButtonAPrimR = 80;
    sOcarinaButtonAPrimG = 150;
    sOcarinaButtonAPrimB = 255;
    sOcarinaButtonAEnvR = 10;
    sOcarinaButtonAEnvG = 10;
    sOcarinaButtonAEnvB = 10;
    sOcarinaButtonCPrimR = 255;
    sOcarinaButtonCPrimG = 255;
    sOcarinaButtonCPrimB = 50;
    sOcarinaButtonCEnvR = 10;
    sOcarinaButtonCEnvG = 10;
    sOcarinaButtonCEnvB = 10;
}

s32 Message_ShouldAdvance(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->textboxEndType == 0x10) || (msgCtx->textboxEndType == 0x11)) {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
            CHECK_BTN_ALL(controller->press.button, BTN_CUP)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

s32 Message_ShouldAdvanceSilent(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->textboxEndType == 0x10) || (msgCtx->textboxEndType == 0x11)) {
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

void Message_CloseTextbox(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (play->msgCtx.msgLength != 0) {
        msgCtx->stateTimer = 2;
        msgCtx->msgMode = MSGMODE_TEXT_CLOSING;
        msgCtx->textboxEndType = 0;
        play_sound(NA_SE_PL_WALK_GROUND - SFX_FLAG);
    }
}

void Message_DrawTextboxIcon(PlayState* play, Gfx** gfxP, s16 x, s16 y) {
    static s16 sIconPrimColors[][3] = {
        { 0, 80, 200 },
        { 50, 130, 255 },
    };
    static s16 sIconEnvColors[][3] = {
        { 0, 0, 0 },
        { 0, 130, 255 },
    };
    static s16 sIconPrimR = 0;
    static s16 sIconPrimG = 80;
    static s16 sIconPrimB = 200;
    static s16 sIconFlashTimer = 12;
    static s16 sIconFlashColorIndex = 0;
    static s16 sIconEnvR = 0;
    static s16 sIconEnvG = 0;
    static s16 sIconEnvB = 0;
    Gfx* gfx;
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    s16 primR;
    s16 primG;
    s16 primB;
    s16 envR;
    s16 envG;
    s16 envB;
    u8* iconTexture = msgCtx->font.iconBuf;

    gfx = *gfxP;

    if (!msgCtx->textIsCredits) {
        primR = ABS_ALT(sIconPrimR - sIconPrimColors[sIconFlashColorIndex][0]) / sIconFlashTimer;
        primG = ABS_ALT(sIconPrimG - sIconPrimColors[sIconFlashColorIndex][1]) / sIconFlashTimer;
        primB = ABS_ALT(sIconPrimB - sIconPrimColors[sIconFlashColorIndex][2]) / sIconFlashTimer;

        if (sIconPrimR >= sIconPrimColors[sIconFlashColorIndex][0]) {
            sIconPrimR -= primR;
        } else {
            sIconPrimR += primR;
        }

        if (sIconPrimG >= sIconPrimColors[sIconFlashColorIndex][1]) {
            sIconPrimG -= primG;
        } else {
            sIconPrimG += primG;
        }

        if (sIconPrimB >= sIconPrimColors[sIconFlashColorIndex][2]) {
            sIconPrimB -= primB;
        } else {
            sIconPrimB += primB;
        }

        envR = ABS_ALT(sIconEnvR - sIconEnvColors[sIconFlashColorIndex][0]) / sIconFlashTimer;
        envG = ABS_ALT(sIconEnvG - sIconEnvColors[sIconFlashColorIndex][1]) / sIconFlashTimer;
        envB = ABS_ALT(sIconEnvB - sIconEnvColors[sIconFlashColorIndex][2]) / sIconFlashTimer;

        if (sIconEnvR >= sIconEnvColors[sIconFlashColorIndex][0]) {
            sIconEnvR -= envR;
        } else {
            sIconEnvR += envR;
        }

        if (sIconEnvG >= sIconEnvColors[sIconFlashColorIndex][1]) {
            sIconEnvG -= envG;
        } else {
            sIconEnvG += envG;
        }

        if (sIconEnvB >= sIconEnvColors[sIconFlashColorIndex][2]) {
            sIconEnvB -= envB;
        } else {
            sIconEnvB += envB;
        }

        sIconFlashTimer--;
        if (sIconFlashTimer == 0) {
            sIconPrimR = sIconPrimColors[sIconFlashColorIndex][0];
            sIconPrimG = sIconPrimColors[sIconFlashColorIndex][1];
            sIconPrimB = sIconPrimColors[sIconFlashColorIndex][2];
            sIconEnvR = sIconEnvColors[sIconFlashColorIndex][0];
            sIconEnvG = sIconEnvColors[sIconFlashColorIndex][1];
            sIconEnvB = sIconEnvColors[sIconFlashColorIndex][2];
            sIconFlashTimer = 12;
            sIconFlashColorIndex ^= 1;
        }

        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, sIconPrimR, sIconPrimG, sIconPrimB, 255);
        gDPSetEnvColor(gfx++, sIconEnvR, sIconEnvG, sIconEnvB, 255);

        if (!play->pauseCtx.bombersNotebookOpen) {
            gDPLoadTextureBlock_4b(gfx++, iconTexture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, x << 2, y << 2, (x + sCharTexSize) << 2, (y + sCharTexSize) << 2,
                                G_TX_RENDERTILE, 0, 0, sCharTexScale, sCharTexScale);
        }

        msgCtx->stateTimer++;
        *gfxP = gfx;
    }
}

void func_80147F18(PlayState* play, Gfx** gfxP, s16 arg2, s16 arg3) {
    static s16 D_801CFD10[][3] = {
        { 0, 80, 200 },
        { 50, 130, 255 },
    };
    static s16 D_801CFD1C[][3] = {
        { 0, 0, 0 },
        { 0, 130, 255 },
    };
    static s16 D_801CFD28 = 0;
    static s16 D_801CFD2C = 80;
    static s16 D_801CFD30 = 200;
    static s16 D_801CFD34 = 12;
    static s16 D_801CFD38 = 0;
    static s16 D_801CFD3C = 0;
    static s16 D_801CFD40 = 0;
    static s16 D_801CFD44 = 0;
    Gfx* gfx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 primR;
    s16 primG;
    s16 primB;
    s16 envR;
    s16 envG;
    s16 envB;

    gfx = *gfxP;

    if (!msgCtx->textIsCredits) {
        primR = ABS_ALT(D_801CFD28 - D_801CFD10[D_801CFD38][0]) / D_801CFD34;
        primG = ABS_ALT(D_801CFD2C - D_801CFD10[D_801CFD38][1]) / D_801CFD34;
        primB = ABS_ALT(D_801CFD30 - D_801CFD10[D_801CFD38][2]) / D_801CFD34;

        if (D_801CFD28 >= D_801CFD10[D_801CFD38][0]) {
            D_801CFD28 -= primR;
        } else {
            D_801CFD28 += primR;
        }

        if (D_801CFD2C >= D_801CFD10[D_801CFD38][1]) {
            D_801CFD2C -= primG;
        } else {
            D_801CFD2C += primG;
        }

        if (D_801CFD30 >= D_801CFD10[D_801CFD38][2]) {
            D_801CFD30 -= primB;
        } else {
            D_801CFD30 += primB;
        }

        envR = ABS_ALT(D_801CFD3C - D_801CFD1C[D_801CFD38][0]) / D_801CFD34;
        envG = ABS_ALT(D_801CFD40 - D_801CFD1C[D_801CFD38][1]) / D_801CFD34;
        envB = ABS_ALT(D_801CFD44 - D_801CFD1C[D_801CFD38][2]) / D_801CFD34;

        if (D_801CFD3C >= D_801CFD1C[D_801CFD38][0]) {
            D_801CFD3C -= envR;
        } else {
            D_801CFD3C += envR;
        }

        if (D_801CFD40 >= D_801CFD1C[D_801CFD38][1]) {
            D_801CFD40 -= envG;
        } else {
            D_801CFD40 += envG;
        }

        if (D_801CFD44 >= D_801CFD1C[D_801CFD38][2]) {
            D_801CFD44 -= envB;
        } else {
            D_801CFD44 += envB;
        }

        D_801CFD34--;
        if (D_801CFD34 == 0) {
            D_801CFD28 = D_801CFD10[D_801CFD38][0];
            D_801CFD2C = D_801CFD10[D_801CFD38][1];
            D_801CFD30 = D_801CFD10[D_801CFD38][2];
            D_801CFD3C = D_801CFD1C[D_801CFD38][0];
            D_801CFD40 = D_801CFD1C[D_801CFD38][1];
            D_801CFD44 = D_801CFD1C[D_801CFD38][2];
            D_801CFD34 = 12;
            D_801CFD38 ^= 1;
        }

        gDPPipeSync(gfx++);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(gfx++, 0, 0, D_801CFD28, D_801CFD2C, D_801CFD30, 120);
        gDPFillRectangle(gfx++, (arg2 + 3), arg3, arg2 + 0x11, arg3 + 0xB);
        gDPFillRectangle(gfx++, arg2 + 6, arg3 - 2, arg2 + 0xE, arg3 + 0xD);
        gDPPipeSync(gfx++);

        msgCtx->stateTimer++;
        *gfxP = gfx++;
    }
}

void func_80148558(PlayState* play, Gfx** gfxP, s16 arg2, s16 arg3) {
    static s16 D_801CFD48[][3] = {
        { 0, 80, 200 },
        { 50, 130, 255 },
    };
    static s16 D_801CFD54[][3] = {
        { 0, 0, 0 },
        { 0, 130, 255 },
    };
    static s16 D_801CFD60 = 0;
    static s16 D_801CFD64 = 80;
    static s16 D_801CFD68 = 200;
    static s16 D_801CFD6C = 12;
    static s16 D_801CFD70 = 0;
    static s16 D_801CFD74 = 0;
    static s16 D_801CFD78 = 0;
    static s16 D_801CFD7C = 0;
    Gfx* gfx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 primR;
    s16 primG;
    s16 primB;
    s16 envR;
    s16 envG;
    s16 envB;

    gfx = *gfxP;

    if (!msgCtx->textIsCredits) {
        primR = ABS_ALT(D_801CFD60 - D_801CFD48[D_801CFD70][0]) / D_801CFD6C;
        primG = ABS_ALT(D_801CFD64 - D_801CFD48[D_801CFD70][1]) / D_801CFD6C;
        primB = ABS_ALT(D_801CFD68 - D_801CFD48[D_801CFD70][2]) / D_801CFD6C;

        if (D_801CFD60 >= D_801CFD48[D_801CFD70][0]) {
            D_801CFD60 -= primR;
        } else {
            D_801CFD60 += primR;
        }

        if (D_801CFD64 >= D_801CFD48[D_801CFD70][1]) {
            D_801CFD64 -= primG;
        } else {
            D_801CFD64 += primG;
        }

        if (D_801CFD68 >= D_801CFD48[D_801CFD70][2]) {
            D_801CFD68 -= primB;
        } else {
            D_801CFD68 += primB;
        }

        envR = ABS_ALT(D_801CFD74 - D_801CFD54[D_801CFD70][0]) / D_801CFD6C;
        envG = ABS_ALT(D_801CFD78 - D_801CFD54[D_801CFD70][1]) / D_801CFD6C;
        envB = ABS_ALT(D_801CFD7C - D_801CFD54[D_801CFD70][2]) / D_801CFD6C;

        if (D_801CFD74 >= D_801CFD54[D_801CFD70][0]) {
            D_801CFD74 -= envR;
        } else {
            D_801CFD74 += envR;
        }

        if (D_801CFD78 >= D_801CFD54[D_801CFD70][1]) {
            D_801CFD78 -= envG;
        } else {
            D_801CFD78 += envG;
        }

        if (D_801CFD7C >= D_801CFD54[D_801CFD70][2]) {
            D_801CFD7C -= envB;
        } else {
            D_801CFD7C += envB;
        }

        D_801CFD6C--;
        if (D_801CFD6C == 0) {
            D_801CFD60 = D_801CFD48[D_801CFD70][0];
            D_801CFD64 = D_801CFD48[D_801CFD70][1];
            D_801CFD68 = D_801CFD48[D_801CFD70][2];
            D_801CFD74 = D_801CFD54[D_801CFD70][0];
            D_801CFD78 = D_801CFD54[D_801CFD70][1];
            D_801CFD7C = D_801CFD54[D_801CFD70][2];
            D_801CFD6C = 12;
            D_801CFD70 ^= 1;
        }

        gDPPipeSync(gfx++);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(gfx++, 0, 0, D_801CFD60, D_801CFD64, D_801CFD68, 120);
        gDPFillRectangle(gfx++, (arg2 + 3), arg3, arg2 + 0x1D, arg3 + 0xB);
        gDPFillRectangle(gfx++, arg2 + 6, arg3 - 2, arg2 + 0x1A, arg3 + 0xD);
        gDPPipeSync(gfx++);

        msgCtx->stateTimer++;
        *gfxP = gfx++;
    }
}

void Message_HandleChoiceSelection(PlayState* play, u8 numChoices) {
    static s16 D_801CFD80 = false; // sAnalogStickHeld
    MessageContext* msgCtx = &play->msgCtx;
    Input* input = CONTROLLER1(&play->state);

    if ((input->rel.stick_y >= 30) && !D_801CFD80) {
        D_801CFD80 = true;
        msgCtx->choiceIndex--;
        if (msgCtx->choiceIndex > 128) {
            msgCtx->choiceIndex = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((input->rel.stick_y <= -30) && !D_801CFD80) {
        D_801CFD80 = true;
        msgCtx->choiceIndex++;
        if (msgCtx->choiceIndex > numChoices) {
            msgCtx->choiceIndex = numChoices;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if (ABS_ALT(input->rel.stick_y) < 30) {
        D_801CFD80 = false;
    }
}

void func_80148CBC(PlayState* play, Gfx** gfxP, u8 arg2) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->textPosX = 0x30;
    if (arg2 == 1) {
        msgCtx->textPosY = msgCtx->unk11FFE[1 + msgCtx->choiceIndex];
    } else {
        msgCtx->textPosY = msgCtx->unk11FFE[msgCtx->choiceIndex];
    }
    Message_DrawTextboxIcon(play, gfxP, msgCtx->textPosX, msgCtx->textPosY);
}

void func_80148D64(PlayState* play) {
    static s16 D_801CFD84 = false; // sAnalogStickHeld
    MessageContext* msgCtx = &play->msgCtx;

    if (play->msgCtx.stickAdjY <= -30) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]--;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] < '0') {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = '9';
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->stickAdjY >= 30) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]++;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] > '9') {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = '0';
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if ((msgCtx->stickAdjX >= 30) && !D_801CFD84) {
        D_801CFD84 = true;
        msgCtx->unk120C2++;
        if (msgCtx->unk120C2 > 2) {
            msgCtx->unk120C2 = 2;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((msgCtx->stickAdjX <= -30) && !D_801CFD84) {
        D_801CFD84 = true;
        msgCtx->unk120C2--;
        if (msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else {
        D_801CFD84 = false;
    }

    msgCtx->bankRupeesSelected = (msgCtx->decodedBuffer.schar[msgCtx->unk120C0] * 100) - ('0' * 100);
    msgCtx->bankRupeesSelected += (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + 1] * 10) - ('0' * 10);
    msgCtx->bankRupeesSelected += (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + 2]) - '0';
}

void func_80149048(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->stickAdjY <= -30) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]--;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] < 0x30) {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = 0x39;
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->stickAdjY >= 30) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]++;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] >= 0x3A) {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = 0x30;
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    }

    msgCtx->bankRupeesSelected = (msgCtx->decodedBuffer.schar[msgCtx->unk120C0] * 10) - 0x1E0U;
}

void func_801491DC(PlayState* play) {
    static s16 D_801CFD88 = false; // sAnalogStickHeld
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->stickAdjY <= -30) {
        msgCtx->unk12054[msgCtx->unk120C2]--;
        if (msgCtx->unk12054[msgCtx->unk120C2] <= 0) {
            msgCtx->unk12054[msgCtx->unk120C2] = 5;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->stickAdjY >= 30) {
        msgCtx->unk12054[msgCtx->unk120C2]++;
        if (msgCtx->unk12054[msgCtx->unk120C2] > 5) {
            msgCtx->unk12054[msgCtx->unk120C2] = 1;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if ((msgCtx->stickAdjX >= 30) && !D_801CFD88) {
        D_801CFD88 = true;
        msgCtx->unk120C2++;
        if (msgCtx->unk120C2 > 4) {
            msgCtx->unk120C2 = 4;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((msgCtx->stickAdjX <= -30) && !D_801CFD88) {
        D_801CFD88 = true;
        msgCtx->unk120C2--;
        if (msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else {
        D_801CFD88 = false;
    }
}

void func_80149454(PlayState* play) {
    static s16 D_801CFD8C = false; // sAnalogStickHeld
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->stickAdjY <= -30) {
        msgCtx->unk12054[msgCtx->unk120C2]--;
        if (msgCtx->unk12054[msgCtx->unk120C2] < 0) {
            msgCtx->unk12054[msgCtx->unk120C2] = 9;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->stickAdjY >= 30) {
        msgCtx->unk12054[msgCtx->unk120C2]++;
        if (msgCtx->unk12054[msgCtx->unk120C2] > 9) {
            msgCtx->unk12054[msgCtx->unk120C2] = 0;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if ((msgCtx->stickAdjX >= 30) && !D_801CFD8C) {
        D_801CFD8C = true;
        msgCtx->unk120C2++;
        if (msgCtx->unk120C2 > 2) {
            msgCtx->unk120C2 = 2;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((msgCtx->stickAdjX <= -30) && !D_801CFD8C) {
        D_801CFD8C = true;
        msgCtx->unk120C2--;
        if (msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else {
        D_801CFD8C = false;
    }
}

void func_801496C8(PlayState* play) {
    static s16 D_801CFD90 = false; // sAnalogStickHeld
    MessageContext* msgCtx = &play->msgCtx;

    if (play->msgCtx.stickAdjY <= -30) {
        msgCtx->unk12054[msgCtx->unk120C2]--;
        if (msgCtx->unk12054[msgCtx->unk120C2] < 0) {
            msgCtx->unk12054[msgCtx->unk120C2] = 3;
        }
        msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x824F;
        Font_LoadChar(play, msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2],
                      msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->stickAdjY >= 30) {
        msgCtx->unk12054[msgCtx->unk120C2]++;
        if (msgCtx->unk12054[msgCtx->unk120C2] >= 4) {
            msgCtx->unk12054[msgCtx->unk120C2] = 0;
        }
        msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x824F;
        Font_LoadChar(play, msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2],
                      msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if ((msgCtx->stickAdjX >= 30) && !D_801CFD90) {
        D_801CFD90 = true;
        msgCtx->unk120C2++;
        if (msgCtx->unk120C2 > 5) {
            msgCtx->unk120C2 = 5;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((msgCtx->stickAdjX <= -30) && !D_801CFD90) {
        D_801CFD90 = true;
        msgCtx->unk120C2--;
        if (msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else {
        D_801CFD90 = false;
    }
}

void Message_DrawTextChar(PlayState* play, TexturePtr texture, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx = *gfxP;
    s16 x = msgCtx->textPosX;
    s16 y = msgCtx->textPosY;

    gDPPipeSync(gfx++);

    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    if ((msgCtx->textBoxType != 5) && (msgCtx->textBoxType != 0xD) && !play->pauseCtx.bombersNotebookOpen) {
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textColorAlpha);
        gSPTextureRectangle(gfx++, (x + 1) << 2, (y + 1) << 2, ((x + sCharTexSize + 1)) << 2,
                            ((y + sCharTexSize + 1)) << 2, G_TX_RENDERTILE, 0, 0, sCharTexScale, sCharTexScale);
        gDPPipeSync(gfx++);
    }

    gDPSetPrimColor(gfx++, 0, 0, msgCtx->textColorR, msgCtx->textColorG, msgCtx->textColorB, msgCtx->textColorAlpha);
    gSPTextureRectangle(gfx++, (x) << 2, (y) << 2, ((x + sCharTexSize)) << 2, ((y + sCharTexSize)) << 2,
                        G_TX_RENDERTILE, 0, 0, sCharTexScale, sCharTexScale);
    *gfxP = gfx++;
}

s16 sTextboxWidth = 0x100;
s16 sTextboxHeight = 0x40;
s16 sTextboxTexWidth = 0x400;
s16 sTextboxTexHeight = 0x400;

f32 D_801CFDA4[] = { 0.6f, 0.75f, 0.9f, 1.0f, 1.05f, 1.1f, 1.05f, 1.0f, 1.0f };
f32 D_801CFDC8[] = { 0.6f, 0.75f, 0.9f, 1.0f, 1.05f, 1.1f, 1.05f, 1.0f, 1.0f };

// resizes textboxes when opening them
void Message_GrowTextbox(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (!play->pauseCtx.bombersNotebookOpen) {
        sTextboxWidth = D_801CFDA4[msgCtx->stateTimer] * 256.0f;
        sTextboxTexWidth = 1024.0f / D_801CFDA4[msgCtx->stateTimer];
        sTextboxHeight = D_801CFDC8[msgCtx->stateTimer] * 64.0f;
        sTextboxTexHeight = 1024.0f / D_801CFDC8[msgCtx->stateTimer];
        msgCtx->textboxY = msgCtx->textboxYTarget + ((0x40 - sTextboxHeight) / 2);
        msgCtx->textboxColorAlphaCurrent += msgCtx->textboxColorAlphaTarget / 8;
        msgCtx->stateTimer++;
    } else {
        msgCtx->stateTimer = 8;
        sTextboxWidth = 0x200;
        sTextboxTexWidth = 0x200;
        sTextboxHeight = 0x59;
        sTextboxTexHeight = 0x2DB;
        msgCtx->textboxY = msgCtx->textboxYTarget + ((0x5A - sTextboxHeight) / 2);
    }

    if (msgCtx->stateTimer == 8) {
        // Reached the end
        msgCtx->textboxX = msgCtx->textboxXTarget;
        msgCtx->textboxY = msgCtx->textboxYTarget;
        msgCtx->msgMode = MSGMODE_TEXT_STARTING;
        msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget;
    }

    if (!play->pauseCtx.bombersNotebookOpen) {
        msgCtx->textboxX = msgCtx->textboxXTarget + ((0x100 - sTextboxWidth) / 2);
        return;
    }

    msgCtx->textboxX = msgCtx->textboxXTarget + ((0x200 - sTextboxWidth) / 2);
}

void Message_FindMessage(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = msgCtx->messageEntryTable;
    const char* segment = msgEntry->segment;
    const char* foundSegment;
    const char* nextSegment;

    while (msgEntry->textId != 0xFFFF) {
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd = nextSegment - foundSegment;
            return;
        }
        msgEntry++;
    }

    msgEntry = msgCtx->messageEntryTable;
    foundSegment = msgEntry->segment;
    msgEntry++;
    nextSegment = msgEntry->segment;
    font->messageStart = foundSegment - segment;
    font->messageEnd = nextSegment - foundSegment;
}

u8 D_801CFDEC[][3] = {
    { 0, 255, 0 },   { 0, 0, 255 },     { 255, 255, 255 }, { 255, 0, 0 },
    { 255, 0, 255 }, { 255, 255, 255 }, { 255, 100, 0 },   { 0, 0, 0 },
};
s16 D_801CFE04[] = { 150, 255, 100, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
s16 D_801CFE1C[] = { 255, 80, 150, 160, 100, 240, 255, 255, 255, 255, 255, 255 };
s16 D_801CFE34[] = { 100, 40, 255, 0, 255, 100, 255, 255, 255, 255, 255, 255 };

TexturePtr D_801CFE4C[] = { 0x02008998, 0x02009598, 0x0200A198, 0x0200AD98 };

u8 D_801CFE5C[][3] = {
    { 255, 110, 160 },
    { 90, 255, 100 },
    { 120, 255, 255 },
    { 245, 245, 90 },
};
u8 D_801CFE68[][3] = {
    { 255, 255, 255 },
    { 255, 255, 255 },
    { 255, 255, 255 },
    { 225, 170, 0 },
};

void Message_DrawItemIcon(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx = *gfxP;
    s32 index;

    msgCtx->unk12016 = msgCtx->unk12014;

    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
        play_sound(0);
    }

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, msgCtx->textColorAlpha);

    if (msgCtx->itemId == ITEM_RECOVERY_HEART) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 255, 0, 0, msgCtx->textColorAlpha);
        gDPSetEnvColor(gfx++, 0, 80, 0, 255);
        gDPLoadTextureBlock(gfx++, gHeartFullTex, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else if ((msgCtx->itemId >= ITEM_RUPEE_GREEN) && (msgCtx->itemId <= ITEM_RUPEE_HUGE)) {
        index = msgCtx->itemId - ITEM_RUPEE_GREEN;
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, D_801CFDEC[index][0], D_801CFDEC[index][1], D_801CFDEC[index][2],
                        msgCtx->textColorAlpha);
        gDPSetEnvColor(gfx++, 0, 80, 0, 255);
        gDPLoadTextureBlock(gfx++, gRupeeCounterIconTex, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else if (msgCtx->itemId == ITEM_STRAY_FAIRIES) {
        msgCtx->unk12016 = 0x18;
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, D_801CFE5C[((void)0, gSaveContext.dungeonIndex)][0],
                        D_801CFE5C[((void)0, gSaveContext.dungeonIndex)][1],
                        D_801CFE5C[((void)0, gSaveContext.dungeonIndex)][2], msgCtx->textColorAlpha);
        gDPSetEnvColor(gfx++, D_801CFE68[((void)0, gSaveContext.dungeonIndex)][0],
                       D_801CFE68[((void)0, gSaveContext.dungeonIndex)][1],
                       D_801CFE68[((void)0, gSaveContext.dungeonIndex)][2], 0);
        gDPLoadTextureBlock_4b(gfx++, gStrayFairyGlowingCircleIconTex, G_IM_FMT_I, 32, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, msgCtx->unk12010 << 2, msgCtx->unk12012 << 2,
                            (msgCtx->unk12010 + msgCtx->unk12014) << 2, (msgCtx->unk12012 + msgCtx->unk12016) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, msgCtx->textColorAlpha);
        gDPLoadTextureBlock(gfx++, D_801CFE4C[((void)0, gSaveContext.dungeonIndex)], G_IM_FMT_RGBA, G_IM_SIZ_32b, 32,
                            24, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
    } else if ((msgCtx->itemId >= ITEM_SONG_SONATA) && (msgCtx->itemId <= ITEM_SONG_SUN)) {
        index = msgCtx->itemId - ITEM_SONG_SONATA;
        gDPSetPrimColor(gfx++, 0, 0, D_801CFE04[index], D_801CFE1C[index], D_801CFE34[index], msgCtx->textColorAlpha);
        gDPLoadTextureBlock(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 24, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        msgCtx->unk12016 = 0x18;
    } else if (msgCtx->itemId == ITEM_CC) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 0, msgCtx->textColorAlpha);
        gDPSetEnvColor(gfx++, 0, 0, 0, 255);
        gDPLoadTextureBlock(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
    } else if (msgCtx->itemId >= ITEM_B8) {
        gDPLoadTextureBlock(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
    } else if (msgCtx->itemId >= ITEM_SKULL_TOKEN) {
        gDPLoadTextureBlock(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_32b, 24, 24, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
    } else {
        msgCtx->unk12016 = msgCtx->unk12014;
        gDPLoadTextureBlock(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
    }

    gSPTextureRectangle(gfx++, msgCtx->unk12010 << 2, msgCtx->unk12012 << 2, (msgCtx->unk12010 + msgCtx->unk12014) << 2,
                        (msgCtx->unk12012 + msgCtx->unk12016) << 2, G_TX_RENDERTILE, 0, 0, D_801F6B08, D_801F6B08);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);

    if (!play->pauseCtx.bombersNotebookOpen) {
        msgCtx->textPosX += 0x10;
    } else {
        msgCtx->textPosX += 0x32;
    }
    *gfxP = gfx;
}

void Message_HandleOcarina(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
        play->msgCtx.ocarinaMode = OCARINA_MODE_ACTIVE;
        if (msgCtx->ocarinaAction == OCARINA_ACTION_SCARECROW_LONG_RECORDING) {
            msgCtx->msgMode = MSGMODE_SCARECROW_LONG_RECORDING_START;
        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_SCARECROW_LONG_DEMONSTRATION) {
            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            msgCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
            msgCtx->ocarinaStaff->pos = 0;
            sOcarinaButtonIndexBufPos = sOcarinaButtonIndexBufLen = 0;
            Message_ResetOcarinaButtonState(play);
            msgCtx->stateTimer = 3;
            msgCtx->msgMode = MSGMODE_SCARECROW_LONG_DEMONSTRATION;
            AudioOcarina_SetPlaybackSong(OCARINA_SONG_SCARECROW_LONG + 1, 1);
        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_SCARECROW_SPAWN_RECORDING) {
            msgCtx->msgMode = MSGMODE_SCARECROW_SPAWN_RECORDING_START;
        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_SCARECROW_SPAWN_DEMONSTRATION) {
            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            msgCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
            msgCtx->ocarinaStaff->pos = 0;
            sOcarinaButtonIndexBufPos = sOcarinaButtonIndexBufLen = 0;
            Message_ResetOcarinaButtonState(play);
            msgCtx->stateTimer = 3;
            msgCtx->msgMode = MSGMODE_SCARECROW_SPAWN_DEMONSTRATION;
            AudioOcarina_SetPlaybackSong(OCARINA_SONG_SCARECROW_SPAWN + 1, 1);
        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_37) {
            msgCtx->msgMode = MSGMODE_2F;
        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_3A) {
            msgCtx->msgMode = MSGMODE_32;
        } else if ((msgCtx->ocarinaAction >= OCARINA_ACTION_TIMED_PROMPT_SONATA) &&
                   (msgCtx->ocarinaAction <= OCARINA_ACTION_TIMED_PROMPT_STORMS)) {
            msgCtx->msgMode = MSGMODE_35;
        } else if (((msgCtx->ocarinaAction >= OCARINA_ACTION_DEMONSTRATE_SONATA) &&
                    (msgCtx->ocarinaAction <= OCARINA_ACTION_DEMONSTRATE_GORON_LULLABY_INTRO)) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_3B) || (msgCtx->ocarinaAction == OCARINA_ACTION_3C) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_FIRST_HALF) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_FIRST_HALF) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_SECOND_HALF) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_SECOND_HALF)) {
            msgCtx->msgMode = MSGMODE_SONG_DEMONSTRATION_STARTING;
        } else if ((msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_WIND_FISH_GORON) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_WIND_FISH_ZORA) ||
                   (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) {
            msgCtx->msgMode = MSGMODE_SONG_PROMPT_STARTING;
        } else if ((msgCtx->ocarinaAction == OCARINA_ACTION_0) || (msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY) ||
                   (msgCtx->ocarinaAction >= OCARINA_ACTION_CHECK_TIME)) {
            msgCtx->msgMode = MSGMODE_OCARINA_STARTING;
        } else {
            msgCtx->msgMode = MSGMODE_SONG_PROMPT_STARTING;
        }
    }
}

s16 D_801CFE74[][3] = {
    { 255, 120, 0 },  { 70, 255, 80 },   { 80, 110, 255 },  { 255, 255, 30 },
    { 90, 180, 255 }, { 210, 100, 255 }, { 170, 170, 170 }, { 255, 130, 30 },
};
s16 D_801CFEA4[][3] = {
    { 255, 60, 60 },  { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};
s16 D_801CFED4[][3] = {
    { 255, 60, 60 },  { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 180, 180, 200 }, { 255, 130, 30 },
};
s16 D_801CFF04[][3] = {
    { 195, 0, 0 },    { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};
s16 D_801CFF34[][3] = {
    { 255, 60, 60 },  { 110, 170, 255 }, { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};
u8 D_801CFF64[] = { 2, 1, 3, 6, 6, 6, 3, 3, 3, 3, 1, 6 };

#ifdef NON_EQUIVALENT
void Message_DrawTextDefault(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &play->msgCtx.font;
    u16 j;
    u16 i;
    u16 charTexIndex;
    Gfx* gfx;
    s16 sp130;
    s16 sp12E;
    s16 sp12C;
    s16 sp12A;
    u16 character;
    u16 lookAheadCharacter;

    gfx = *gfxP;

    play->msgCtx.textPosX = play->msgCtx.unk11F1A[0] + play->msgCtx.unk11FF8;
    play->msgCtx.textPosY = play->msgCtx.unk11FFA;

    sp130 = 0;
    if (play->msgCtx.itemId != 0x270F) {
        Message_DrawItemIcon(play, &gfx);
    }
    msgCtx->textColorR = msgCtx->unk120C8;
    msgCtx->textColorG = msgCtx->unk120CA;
    msgCtx->textColorB = msgCtx->unk120CC;

    charTexIndex = 0;

    for (i = 0; i < msgCtx->textDrawPos; i++) {
        character = msgCtx->decodedBuffer.wchar[i];

        switch (character) {
            case 0x2000:
                if (play->pauseCtx.bombersNotebookOpen || (msgCtx->textBoxType == 0xD)) {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
                } else if (msgCtx->textBoxType == 5) {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
                } else {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0xFF;
                }
                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos++;
                }
                break;

            case 0x2001:
            case 0x2002:
            case 0x2003:
            case 0x2004:
            case 0x2005:
            case 0x2006:
            case 0x2007:
            case 0x2008:
                if ((msgCtx->msgMode >= MSGMODE_NEW_CYCLE_0) && (msgCtx->msgMode <= MSGMODE_NEW_CYCLE_2) &&
                    (character == 0x2002)) {
                    msgCtx->textDrawPos = msgCtx->decodedTextLen;
                    if (msgCtx->unk120D6) {
                        msgCtx->unk120D4 += 0x19;
                        if (msgCtx->unk120D4 >= 0x64) {
                            msgCtx->unk120D6 = false;
                        }
                    } else {
                        msgCtx->unk120D4 -= 0x19;
                        if (msgCtx->unk120D4 < -0x63) {
                            msgCtx->unk120D6 = true;
                        }
                    }

                    if (D_801CFE74[character - 0x2001][0] + msgCtx->unk120D4 < 0) {
                        msgCtx->textColorR = 0;
                    } else {
                        msgCtx->textColorR = D_801CFE74[character - 0x2001][0] + msgCtx->unk120D4;
                    }
                    if (D_801CFE74[character - 0x2001][1] + msgCtx->unk120D4 >= 0xFF) {
                        msgCtx->textColorG = D_801CFE74[character - 0x2001][1];
                    } else {
                        msgCtx->textColorG = D_801CFE74[character - 0x2001][1] + msgCtx->unk120D4;
                    }
                    if (D_801CFE74[character - 0x2001][2] + msgCtx->unk120D4 < 0) {
                        msgCtx->textColorB = 0;
                    } else {
                        msgCtx->textColorB = D_801CFE74[character - 0x2001][2] + msgCtx->unk120D4;
                    }
                } else if (play->pauseCtx.bombersNotebookOpen) {
                    msgCtx->textColorR = D_801CFF34[character - 0x2001][0];
                    msgCtx->textColorG = D_801CFF34[character - 0x2001][1];
                    msgCtx->textColorB = D_801CFF34[character - 0x2001][2];
                } else if (msgCtx->textBoxType == 1) {
                    msgCtx->textColorR = D_801CFE74[character - 0x2001][0];
                    msgCtx->textColorG = D_801CFE74[character - 0x2001][1];
                    msgCtx->textColorB = D_801CFE74[character - 0x2001][2];
                } else if (msgCtx->textBoxType == 0xD) {
                    msgCtx->textColorR = D_801CFF04[character - 0x2001][0];
                    msgCtx->textColorG = D_801CFF04[character - 0x2001][1];
                    msgCtx->textColorB = D_801CFF04[character - 0x2001][2];
                } else {
                    msgCtx->textColorR = D_801CFEA4[character - 0x2001][0];
                    msgCtx->textColorG = D_801CFEA4[character - 0x2001][1];
                    msgCtx->textColorB = D_801CFEA4[character - 0x2001][2];
                }

                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos++;
                }
                break;
            case 0x20: // ` `
                msgCtx->textPosX += 6;
                break;
            case 0xA:
                msgCtx->textPosY += msgCtx->unk11FFC;
                // fallthrough
            case 0xC:
                sp130++;
                msgCtx->textPosX = msgCtx->unk11F1A[sp130] + msgCtx->unk11FF8;
                if (msgCtx->choiceNum == 1) {
                    if (!play->pauseCtx.bombersNotebookOpen) {
                        msgCtx->textPosX += 32;
                    } else {
                        msgCtx->textPosX += 57;
                    }
                } else if (msgCtx->choiceNum == 2) {
                    if (!play->pauseCtx.bombersNotebookOpen) {
                        msgCtx->textPosX += 22;
                    } else {
                        msgCtx->textPosX += 57;
                    }
                }
                break;

            case 0x9:
            case 0xB:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    if (!msgCtx->textboxSkipped) {
                        play_sound(0);
                        msgCtx->msgMode = MSGMODE_TEXT_AWAIT_NEXT;
                        Font_LoadMessageBoxEndIcon(font, 0);
                    } else {
                        msgCtx->msgMode = MSGMODE_TEXT_NEXT_MSG;
                        msgCtx->textUnskippable = 0;
                        msgCtx->msgBufPos++;
                    }
                    msgCtx->unk120CE = msgCtx->textColorR;
                    msgCtx->unk120D0 = msgCtx->textColorG;
                    msgCtx->unk120D2 = msgCtx->textColorB;
                }
                *gfxP = gfx;
                return;

            case 0x101: // MESSAGE_QUICKTEXT_ENABLE
                if (((i + 1) == msgCtx->textDrawPos) &&
                    ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) ||
                     ((msgCtx->msgMode >= MSGMODE_OCARINA_STARTING) && (msgCtx->msgMode <= MSGMODE_26)))) {

                    j = i;
                    while (true) {
                        lookAheadCharacter = msgCtx->decodedBuffer.wchar[j];
                        if ((lookAheadCharacter != 0x102) && (lookAheadCharacter != 0x104) &&
                            (lookAheadCharacter != 0x103) && (lookAheadCharacter != 0x230) &&
                            (lookAheadCharacter != 9) && (lookAheadCharacter != 0xB)) {
                            j++;
                        } else {
                            break;
                        }
                    }
                    i = j - 1;
                    msgCtx->textDrawPos = i + 1;
                }
                break;

            case 0x102: // MESSAGE_QUICKTEXT_DISABLE
                break;

            case 0x110: // MESSAGE_BOX_BREAK_DELAYED
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->stateTimer = msgCtx->decodedBuffer.wchar[++i];
                    msgCtx->msgMode = MSGMODE_TEXT_DELAYED_BREAK;
                }
                *gfxP = gfx;
                return;

            case 0x111:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    if (msgCtx->unk11F0C == 3) {
                        msgCtx->textboxEndType = 0x55;
                    } else {
                        msgCtx->textboxEndType = 0x50;
                    }
                    msgCtx->stateTimer = msgCtx->decodedBuffer.wchar[++i];
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                    if (play->csCtx.state == 0) {
                        func_8011552C(play, 3);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x112:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x52;
                    msgCtx->stateTimer = msgCtx->decodedBuffer.wchar[++i];
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                    if (play->csCtx.state == 0) {
                        func_8011552C(play, 3);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x120: // MESSAGE_SFX
                if (((i + 1) == msgCtx->textDrawPos) && (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING)) {
                    play_sound(msgCtx->decodedBuffer.wchar[i + 1]);
                }
                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos++;
                }
                i++;
                break;

            case 0x128:
                if (((i + 1) == msgCtx->textDrawPos) && (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING)) {
                    msgCtx->msgMode = MSGMODE_9;
                    msgCtx->textDelayTimer = msgCtx->decodedBuffer.wchar[i + 1];
                }
                i++;
                break;

            case 0x130:
            case 0x131:
            case 0x132:
            case 0x133:
            case 0x134:
            case 0x135:
            case 0x136:
                msgCtx->textDelay = character - 0x130;
                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos++;
                }
                break;

            case 0x201: // MESSAGE_BACKGROUND
                msgCtx->textPosX = 0x2D;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    play_sound(0);
                }

                gDPPipeSync(gfx++);
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textColorAlpha);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, msgCtx->textPosX * 4, (msgCtx->unk12012 + 1) * 4,
                                    (msgCtx->textPosX + 0x60) * 4, (msgCtx->unk12012 + 0x31) * 4, G_TX_RENDERTILE, 0, 0,
                                    0x0400, 0x0400);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) * 4, (msgCtx->unk12012 + 1) * 4,
                                    (msgCtx->textPosX + 0xC1) * 4, (msgCtx->unk12012 + 0x31) * 4, G_TX_RENDERTILE, 0, 0,
                                    0x0400, 0x0400);

                gDPPipeSync(gfx++);
                gDPSetPrimColor(gfx++, 0, 0, 255, 60, 0, msgCtx->textColorAlpha);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, msgCtx->textPosX * 4, msgCtx->unk12012 * 4, (msgCtx->textPosX + 0x60) * 4,
                                    (msgCtx->unk12012 + 0x30) * 4, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) * 4, msgCtx->unk12012 * 4,
                                    (msgCtx->textPosX + 0xC0) * 4, (msgCtx->unk12012 + 0x30) * 4, G_TX_RENDERTILE, 0, 0,
                                    0x0400, 0x0400);
                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                                  PRIMITIVE, 0);

                msgCtx->textPosX += 32;
                break;

            case 0x202:
                msgCtx->textboxEndType = 0x10;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 2);
                }
                break;

            case 0x203:
                msgCtx->textboxEndType = 0x11;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 2);
                }
                break;

            case 0x20C:
                msgCtx->textboxEndType = 0x60;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                }
                break;

            case 0x220:
                msgCtx->textboxEndType = 0x61;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                }
                break;

            case 0x221:
                msgCtx->textboxEndType = 0x62;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                }
                break;

            case 0x222:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x41;
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0);
                    play_sound(NA_SE_SY_MESSAGE_END);
                }
                break;

            case 0x225:
                msgCtx->textboxEndType = 0x63;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                }
                break;

            case 0x240:
            case 0x500:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    if (msgCtx->textBoxType == 3) {
                        Message_HandleOcarina(play);
                        *gfxP = gfx;
                        return;
                    }
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    if (msgCtx->textboxEndType == 0) {
                        play_sound(NA_SE_SY_MESSAGE_END);
                        if (character == 0x500) {
                            Font_LoadMessageBoxEndIcon(font, 1);
                        } else {
                            Font_LoadMessageBoxEndIcon(font, 0);
                        }
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    } else {
                        play_sound(0);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x104:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    play_sound(0);
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x30;
                }
                *gfxP = gfx;
                return;

            case 0x103:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x40;
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0);
                    play_sound(NA_SE_SY_MESSAGE_END);
                }
                *gfxP = gfx;
                return;

            case 0x230:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x42;
                    Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1);
                    play_sound(NA_SE_SY_MESSAGE_END);
                }
                *gfxP = gfx;
                return;

            default:
                switch (character) {
                    case 0x8169:
                    case 0x8175:
                        msgCtx->textPosX -= (s32)(6.0f * msgCtx->textCharScale);
                        break;

                    case 0x8145:
                        msgCtx->textPosX -= (s32)(3.0f * msgCtx->textCharScale);
                        break;

                    case 0x8148:
                    case 0x8149:
                        msgCtx->textPosX -= (s32)(2.0f * msgCtx->textCharScale);
                        break;

                    default:
                        break;
                }

                if ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) && ((i + 1) == msgCtx->textDrawPos)) {
                    play_sound(0);
                }

                if ((character >= 0x839F) && (character < 0x83AB)) {
                    sp12E = msgCtx->textColorR;
                    sp12C = msgCtx->textColorG;
                    sp12A = msgCtx->textColorB;
                    msgCtx->textColorR = D_801CFED4[D_801CFF64[character - 0x839F]][0];
                    msgCtx->textColorG = D_801CFED4[D_801CFF64[character - 0x839F]][1];
                    msgCtx->textColorB = D_801CFED4[D_801CFF64[character - 0x839F]][2];
                    Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                    msgCtx->textColorR = sp12E;
                    msgCtx->textColorG = sp12C;
                    msgCtx->textColorB = sp12A;
                } else {
                    Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                }
                charTexIndex += 0x80;
                switch (character) {
                    case 0x8144:
                        msgCtx->textPosX += (s32)(8.0f * msgCtx->textCharScale);
                        break;

                    case 0x816A:
                    case 0x8176:
                        msgCtx->textPosX += (s32)(10.0f * msgCtx->textCharScale);
                        break;

                    case 0x8141:
                    case 0x8142:
                    case 0x8168:
                        msgCtx->textPosX += (s32)(12.0f * msgCtx->textCharScale);
                        break;

                    case 0x8194:
                        msgCtx->textPosX += (s32)(14.0f * msgCtx->textCharScale);
                        break;

                    case 0x8145:
                        msgCtx->textPosX += (s32)(15.0f * msgCtx->textCharScale);
                        break;

                    default:
                        if ((msgCtx->msgMode >= MSGMODE_SCENE_TITLE_CARD_FADE_IN_BACKGROUND) &&
                            (msgCtx->msgMode <= MSGMODE_SCENE_TITLE_CARD_FADE_OUT_BACKGROUND)) {
                            msgCtx->textPosX += (s32)((16.0f * msgCtx->textCharScale) - 1.0f);
                        } else {
                            msgCtx->textPosX += (s32)(16.0f * msgCtx->textCharScale);
                        }
                        break;
                }
                break;
        }
    }

    if (msgCtx->textDelayTimer == 0) {
        msgCtx->textDrawPos = i + 1;
        msgCtx->textDelayTimer = 0;
        if (msgCtx->msgMode == MSGMODE_9) {
            msgCtx->msgMode = MSGMODE_TEXT_DISPLAYING;
        }
    } else {
        msgCtx->textDelayTimer--;
    }
    *gfxP = gfx;
}
#else
void Message_DrawTextDefault(PlayState* play, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_DrawTextDefault.s")
#endif

s16 D_801CFF70[LANGUAGE_MAX] = {
    4,    // LANGUAGE_JAP
    0x12, // LANGUAGE_ENG
    0x12, // LANGUAGE_GER
    0x12, // LANGUAGE_FRE
    0x12, // LANGUAGE_SPA
};
s16 D_801CFF7C[LANGUAGE_MAX] = {
    0,   // LANGUAGE_JAP
    0xE, // LANGUAGE_ENG
    0xE, // LANGUAGE_GER
    0xE, // LANGUAGE_FRE
    0xE, // LANGUAGE_SPA
};
s16 D_801CFF88[LANGUAGE_MAX] = {
    0,    // LANGUAGE_JAP
    0x16, // LANGUAGE_ENG
    0x16, // LANGUAGE_GER
    0x16, // LANGUAGE_FRE
    0x16, // LANGUAGE_SPA
};

s16 D_801CFF94[] = {
    0x270F,
    ITEM_RUPEE_GREEN,
    ITEM_RUPEE_BLUE,
    ITEM_RUPEE_10,
    ITEM_RUPEE_RED,
    ITEM_RUPEE_PURPLE,
    ITEM_RUPEE_SILVER,
    ITEM_RUPEE_HUGE,
    ITEM_WALLET_ADULT,
    ITEM_WALLET_GIANT,
    ITEM_RECOVERY_HEART,
    ITEM_RECOVERY_HEART,
    ITEM_HEART_PIECE,
    ITEM_HEART_CONTAINER,
    ITEM_MAGIC_SMALL,
    ITEM_MAGIC_LARGE,
    ITEM_RECOVERY_HEART,
    ITEM_STRAY_FAIRIES,
    ITEM_RECOVERY_HEART,
    ITEM_RECOVERY_HEART,
    ITEM_BOMB,
    ITEM_BOMB,
    ITEM_BOMB,
    ITEM_BOMB,
    ITEM_BOMB,
    ITEM_STICK,
    ITEM_BOMBCHU,
    ITEM_BOMB_BAG_20,
    ITEM_BOMB_BAG_30,
    ITEM_BOMB_BAG_40,
    ITEM_BOW,
    ITEM_BOW,
    ITEM_BOW,
    ITEM_BOW,
    ITEM_QUIVER_30,
    ITEM_QUIVER_40,
    ITEM_QUIVER_50,
    ITEM_ARROW_FIRE,
    ITEM_ARROW_ICE,
    ITEM_ARROW_LIGHT,
    ITEM_NUT,
    ITEM_NUT,
    ITEM_NUT,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_STICK_UPGRADE_20,
    0x270F,
    0x270F,
    ITEM_SHIELD_HERO,
    ITEM_SHIELD_MIRROR,
    ITEM_POWDER_KEG,
    ITEM_MAGIC_BEANS,
    ITEM_PICTO_BOX,
    ITEM_SWORD_KOKIRI,
    ITEM_SWORD_RAZOR,
    ITEM_SWORD_GILDED,
    ITEM_SWORD_DEITY,
    ITEM_SWORD_GREAT_FAIRY,
    ITEM_KEY_SMALL,
    ITEM_KEY_BOSS,
    ITEM_DUNGEON_MAP,
    ITEM_COMPASS,
    ITEM_POWDER_KEG,
    ITEM_HOOKSHOT,
    ITEM_LENS,
    ITEM_PICTO_BOX,
    ITEM_FISHING_ROD,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_OCARINA,
    0x270F,
    0x270F,
    0x270F,
    ITEM_BOMBERS_NOTEBOOK,
    0x270F,
    ITEM_SKULL_TOKEN,
    0x270F,
    0x270F,
    ITEM_REMAINS_ODOLWA,
    ITEM_REMAINS_GOHT,
    ITEM_REMAINS_GYORG,
    ITEM_REMAINS_TWINMOLD,
    ITEM_POTION_RED,
    ITEM_BOTTLE,
    ITEM_POTION_RED,
    ITEM_POTION_GREEN,
    ITEM_POTION_BLUE,
    ITEM_FAIRY,
    ITEM_DEKU_PRINCESS,
    ITEM_MILK_BOTTLE,
    ITEM_MILK_HALF,
    ITEM_FISH,
    ITEM_BUG,
    ITEM_BLUE_FIRE,
    ITEM_POE,
    ITEM_BIG_POE,
    ITEM_SPRING_WATER,
    ITEM_HOT_SPRING_WATER,
    ITEM_ZORA_EGG,
    ITEM_GOLD_DUST,
    ITEM_MUSHROOM,
    0x270F,
    0x270F,
    ITEM_SEAHORSE,
    ITEM_CHATEAU,
    ITEM_HYLIAN_LOACH,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_MASK_DEKU,
    ITEM_MASK_GORON,
    ITEM_MASK_ZORA,
    ITEM_MASK_FIERCE_DEITY,
    ITEM_MASK_TRUTH,
    ITEM_MASK_KAFEIS_MASK,
    ITEM_MASK_ALL_NIGHT,
    ITEM_MASK_BUNNY,
    ITEM_MASK_KEATON,
    ITEM_MASK_GARO,
    ITEM_MASK_ROMANI,
    ITEM_MASK_CIRCUS_LEADER,
    ITEM_MASK_POSTMAN,
    ITEM_MASK_COUPLE,
    ITEM_MASK_GREAT_FAIRY,
    ITEM_MASK_GIBDO,
    ITEM_MASK_DON_GERO,
    ITEM_MASK_KAMARO,
    ITEM_MASK_CAPTAIN,
    ITEM_MASK_STONE,
    ITEM_MASK_BREMEN,
    ITEM_MASK_BLAST,
    ITEM_MASK_SCENTS,
    ITEM_MASK_GIANT,
    0x270F,
    ITEM_CHATEAU,
    ITEM_MILK_BOTTLE,
    ITEM_GOLD_DUST,
    ITEM_HYLIAN_LOACH,
    ITEM_SEAHORSE,
    ITEM_MOON_TEAR,
    ITEM_DEED_LAND,
    ITEM_DEED_SWAMP,
    ITEM_DEED_MOUNTAIN,
    ITEM_DEED_OCEAN,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_ROOM_KEY,
    ITEM_LETTER_MAMA,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_LETTER_TO_KAFEI,
    ITEM_PENDANT_OF_MEMORIES,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_TINGLE_MAP,
    ITEM_TINGLE_MAP,
    ITEM_TINGLE_MAP,
    ITEM_TINGLE_MAP,
    ITEM_TINGLE_MAP,
    ITEM_TINGLE_MAP,
    ITEM_TINGLE_MAP,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    ITEM_SONG_SONATA,
    ITEM_SONG_SONATA,
    ITEM_SONG_SONATA,
    ITEM_SONG_LULLABY,
    ITEM_SONG_NOVA,
    ITEM_SONG_ELEGY,
    ITEM_SONG_OATH,
    ITEM_SONG_SARIA,
    ITEM_SONG_TIME,
    ITEM_SONG_HEALING,
    ITEM_SONG_EPONA,
    ITEM_SONG_SOARING,
    ITEM_SONG_STORMS,
    ITEM_SONG_SUN,
    ITEM_SONG_LULLABY,
    ITEM_SONG_SONATA,
    ITEM_SONG_SONATA,
    ITEM_SONG_SONATA,
    ITEM_SONG_LULLABY,
    ITEM_SONG_NOVA,
    0xB8,
    0xB9,
    0xBA,
    0xBB,
    0xBC,
    0xBD,
    0xBE,
    0xBF,
    0xC0,
    0xC1,
    0xC2,
    0xC3,
    0xC4,
    0xC5,
    0xC6,
    0xC7,
    0xC8,
    0xC9,
    0xCA,
    0xCB,
    0xCC,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
    0x270F,
};

void Message_LoadItemIcon(PlayState* play, u16 itemId, s16 arg2) {
    MessageContext* msgCtx = &play->msgCtx;
    u16* new_var2 = &itemId;

    if (itemId == ITEM_RECOVERY_HEART) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF88[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x10;
    } else if ((itemId >= ITEM_RUPEE_GREEN) && (itemId <= ITEM_RUPEE_HUGE)) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF88[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x10;
    } else if (itemId == ITEM_STRAY_FAIRIES) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x20;
    } else if ((itemId >= ITEM_SONG_SONATA) && (itemId <= ITEM_SONG_SUN)) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF88[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x10;
        CmpDma_LoadFile(SEGMENT_ROM_START(icon_item_static_test), ITEM_SONG_SONATA, msgCtx->textboxSegment + 0x1000,
                        0x180);
    } else if (itemId == ITEM_BOMBERS_NOTEBOOK) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 6);
        msgCtx->unk12014 = 0x20;
        CmpDma_LoadFile(SEGMENT_ROM_START(icon_item_static_test), ITEM_SONG_SONATA, msgCtx->textboxSegment + 0x1000,
                        0x1000);
    } else if (itemId <= ITEM_REMAINS_TWINMOLD) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 6);
        msgCtx->unk12014 = 0x20;
        CmpDma_LoadFile(SEGMENT_ROM_START(icon_item_static_test), itemId, msgCtx->textboxSegment + 0x1000, 0x1000);
    } else if (itemId == ITEM_CC) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 8);
        msgCtx->unk12014 = 0x20;
        CmpDma_LoadFile(SEGMENT_ROM_START(schedule_dma_static_test), ITEM_POTION_BLUE, msgCtx->textboxSegment + 0x1000,
                        0x400);
    } else if (itemId >= ITEM_B8) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 8);
        msgCtx->unk12014 = 0x20;
        CmpDma_LoadFile(SEGMENT_ROM_START(schedule_dma_static_test), (itemId - ITEM_B8),
                        msgCtx->textboxSegment + 0x1000, 0x800);
    } else if (itemId >= ITEM_SKULL_TOKEN) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF7C[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x18;
        CmpDma_LoadFile(SEGMENT_ROM_START(icon_item_24_static_test), (itemId - ITEM_SKULL_TOKEN),
                        msgCtx->textboxSegment + 0x1000, 0x900);
    }

    if (play->pauseCtx.bombersNotebookOpen) {
        msgCtx->unk12010 = ((msgCtx->unk12010 * 1.4f) + 2.0f);
        msgCtx->unk12014 = (msgCtx->unk12014 * 1.4f);
    }

    msgCtx->choiceNum = 1;
}

void Message_LoadChar(PlayState* play, u16 codePointIndex, s32* offset, f32* arg3, s16 decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    Font_LoadChar(play, codePointIndex, temp1);
    msgCtx->decodedBuffer.wchar[decodedBufPos] = codePointIndex;
    temp1 += FONT_CHAR_TEX_SIZE;
    temp2 += (16.0f * msgCtx->textCharScale);
    *offset = temp1;
    *arg3 = temp2;
}

// Message_LoadRupees JPN ?
void func_8014CCB4(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 t = *decodedBufPos;
    s32 k = *offset;
    f32 f = *arg3;

    Font_LoadChar(play, 0x838B, k); // 0x838B = ル in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x838B;
    t++;
    Font_LoadChar(play, 0x8373, k); // 0x8373 = ピ in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x8373;
    t++;
    Font_LoadChar(play, 0x815C, k); // Ox815C = ― in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x815C;

    f += 16.0f * msgCtx->textCharScale * 3.0f;
    *decodedBufPos = t;
    *offset = k;
    *arg3 = f;
}

void func_8014CDF0(OSTime time, s16* digits) {
    // offsetting to actual codepoints is done outside this function
    // every digits will be added 0x824F to get an actual S-JIS
    // printable character.
    OSTime temp_t2 = time;

    digits[0] = temp_t2 / 36000;
    temp_t2 -= digits[0] * 36000;

    digits[1] = temp_t2 / 6000;
    temp_t2 -= digits[1] * 6000;

    digits[2] = 0x135B; // 0x135B + 0x824F = 分 (minutes) in S-JIS

    digits[3] = temp_t2 / 1000;
    temp_t2 -= digits[3] * 1000;

    digits[4] = temp_t2 / 100;
    temp_t2 -= digits[4] * 100;

    digits[5] = 0x1313; // 0x1313 + 0x824F = 秒 (seconds) in S-JIS

    digits[6] = temp_t2 / 10;
    temp_t2 -= digits[6] * 10;

    digits[7] = temp_t2;
}

void Message_SetupLoadItemIcon(PlayState* play) {
    Font* font;
    MessageContext* msgCtx = &play->msgCtx;

    font = &msgCtx->font;
    if (msgCtx->msgBufPos == 0) {
        if (font->msgBuf.schar[msgCtx->msgBufPos + 2] != 0xFE) {
            msgCtx->unk11F18 = 0;
            if ((msgCtx->currentTextId == 0x176F) || (msgCtx->currentTextId == 0x1770) ||
                (msgCtx->currentTextId == 0x1771)) {
                msgCtx->itemId = ITEM_OCARINA;
                msgCtx->msgBufPos += 2;
            } else {
                msgCtx->msgBufPos += 2;
                if ((font->msgBuf.schar[msgCtx->msgBufPos] < 0xC8) || (font->msgBuf.schar[msgCtx->msgBufPos] >= 0xD8)) {
                    msgCtx->itemId = D_801CFF94[(u8)font->msgBuf.schar[msgCtx->msgBufPos]];
                } else {
                    msgCtx->itemId = 0xFE;
                }
            }
        } else {
            msgCtx->msgBufPos += 2;
            msgCtx->itemId = font->msgBuf.schar[msgCtx->msgBufPos];
        }
        msgCtx->unk11F14 = font->msgBuf.schar[++msgCtx->msgBufPos] << 8;
        msgCtx->unk11F14 |= font->msgBuf.schar[++msgCtx->msgBufPos];

        msgCtx->unk1206C = font->msgBuf.schar[++msgCtx->msgBufPos] << 8;
        msgCtx->unk1206C |= font->msgBuf.schar[++msgCtx->msgBufPos];

        msgCtx->unk12070 = font->msgBuf.schar[++msgCtx->msgBufPos] << 8;
        msgCtx->unk12070 |= font->msgBuf.schar[++msgCtx->msgBufPos];

        msgCtx->unk12074 = font->msgBuf.schar[++msgCtx->msgBufPos] << 8;
        msgCtx->unk12074 |= font->msgBuf.schar[++msgCtx->msgBufPos];

        msgCtx->msgBufPos++;
        if (msgCtx->itemId != 0xFE) {
            Message_LoadItemIcon(play, msgCtx->itemId, msgCtx->textboxY + 10);
        }
    }
}

// Message_LoadTimeBeforeMoonCrash
void func_8014D304(PlayState* play, u16 arg1, s32* offset, f32* arg3, s16* decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 i;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u32 dayTime;
    s16 digits[4];
    s32 day;
    f32 timeInMinutes;

    if (arg1 == 0x20F) {
        day = gSaveContext.save.day;
        dayTime = 0x40000 - ((day % 5) << 16) - (u16)(-0x4000 + gSaveContext.save.time);
    } else {
        dayTime = 0x10000 - (u16)(-0x4000 + gSaveContext.save.time);
    }
    timeInMinutes = TIME_TO_MINUTES_F(dayTime);

    digits[0] = 0;
    digits[1] = (timeInMinutes / 60.0f);
    while (digits[1] >= 10) {
        digits[0]++;
        digits[1] -= 10;
    }

    digits[2] = 0;
    digits[3] = (s32)timeInMinutes % 60;
    while (digits[3] >= 10) {
        digits[2]++;
        digits[3] -= 10;
    }

    for (i = 0; i < 4; i++) {
        Font_LoadChar(play, digits[i] + 0x824F, o); // 0x824F = ０ in S-JIS
        o += FONT_CHAR_TEX_SIZE;
        msgCtx->decodedBuffer.wchar[p] = digits[i] + 0x824F;
        p++;
        if (i == 1) {
            // Hours (時間)
            Font_LoadChar(play, 0x8E9E, o);
            o += FONT_CHAR_TEX_SIZE;
            msgCtx->decodedBuffer.wchar[p] = 0x8E9E;
            p++;
            Font_LoadChar(play, 0x8AD4, o);
            o += FONT_CHAR_TEX_SIZE;
            msgCtx->decodedBuffer.wchar[p] = 0x8E9E;
            p++;
        } else if (i == 3) {
            // Minutes (分)
            Font_LoadChar(play, 0x95AA, o);
            o += FONT_CHAR_TEX_SIZE;
            msgCtx->decodedBuffer.wchar[p] = 0x95AA;
        }
    }
    f += 7.0f * (16.0f * msgCtx->textCharScale);
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

// JPN Area names
u16 D_801D0188[OWL_WARP_MAX][9] = {
    { 0x834F, 0x838C, 0x815B, 0x8367, 0x8378, 0x8343, 0x82CC, 0x8A43, 0x8ADD },
    { 0x835D, 0x815B, 0x8389, 0x82CC, 0x82DD, 0x82B3, 0x82AB, 0, 0 },
    { 0x8358, 0x836D, 0x815B, 0x8377, 0x8362, 0x8368, 0, 0, 0 },
    { 0x8E52, 0x97A2, 0, 0, 0, 0, 0, 0, 0 },
    { 0x834E, 0x838D, 0x8362, 0x834E, 0x835E, 0x8345, 0x8393, 0, 0 },
    { 0x837E, 0x838B, 0x834E, 0x838D, 0x815B, 0x8368, 0, 0, 0 },
    { 0x8345, 0x8362, 0x8368, 0x8374, 0x8348, 0x815B, 0x838B, 0, 0 },
    { 0x8FC0, 0x926E, 0, 0, 0, 0, 0, 0, 0 },
    { 0x8343, 0x834A, 0x815B, 0x8369, 0x8C6B, 0x924A, 0, 0, 0 },
    { 0x838D, 0x8362, 0x834E, 0x8372, 0x838B, 0, 0, 0, 0 },
    { 0x93FC, 0x82E8, 0x8CFB, 0, 0, 0, 0, 0, 0 },
};

// Area Names lengths
s16 D_801D0250[OWL_WARP_MAX] = { 9, 7, 6, 2, 7, 6, 7, 2, 6, 5, 3 };

void func_8014D62C(PlayState* play, s32* offset, f32* arg2, s16* decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stringLimit;
    s16 temp_s1 = *decodedBufPos;
    s32 temp_s2 = *offset;
    f32 sp3C = *arg2;
    s16 owlWarpId;
    s16 phi_s0;

    if (func_8010A0A4(play) || (play->sceneId == SCENE_SECOM)) {
        owlWarpId = OWL_WARP_ENTRANCE;
    } else {
        owlWarpId = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
    }
    stringLimit = D_801D0250[owlWarpId];

    for (phi_s0 = 0; phi_s0 < stringLimit; phi_s0++, temp_s1++, temp_s2 += 0x80) {
        msgCtx->decodedBuffer.wchar[temp_s1] = D_801D0188[owlWarpId][phi_s0];
        Font_LoadChar(play, D_801D0188[owlWarpId][phi_s0], temp_s2);
    }

    temp_s1--;
    sp3C += (stringLimit - 1) * (16.0f * msgCtx->textCharScale);

    *decodedBufPos = temp_s1;
    *offset = temp_s2;
    *arg2 = sp3C;
}

s16 D_801D0268[][3] = {
    { 0x82CD, 0x82E2, 0x82A2 },
    { 0x82D3, 0x82C2, 0x82A4 },
    { 0x82A8, 0x82BB, 0x82A2 },
};
s16 D_801D027C[] = { 0x2001, 0x2003, 0x2004, 0x2002 };
s16 D_801D0284[] = { 0x90D4, 0x90C2, 0x89A9, 0x97CE };

void Message_Decode(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_Decode.s")

void func_80150A84(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    u8 offset = msgCtx->textBoxType;
    u8 t;

    if (D_801CFC78[offset] != 14) {
        DmaMgr_SendRequest0(msgCtx->textboxSegment,
                            &((u8*)SEGMENT_ROM_START(message_static))[D_801CFC78[offset] * 0x1000], 0x1000);

        // TODO: I think there's an optimization here:
        // `(offset == 0)` instead of `(&D_801CFC78[offset] == &D_801CFC78[t = 0])`
        if (!play->pauseCtx.bombersNotebookOpen) {
            if ((&D_801CFC78[offset] == &D_801CFC78[t = 0]) || (&D_801CFC78[offset] == &D_801CFC78[t = 6]) ||
                (&D_801CFC78[offset] == &D_801CFC78[t = 10]) || (&D_801CFC78[offset] == &D_801CFC78[t = 11])) {
                msgCtx->textboxColorRed = 0;
                msgCtx->textboxColorGreen = 0;
                msgCtx->textboxColorBlue = 0;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 1]) {
                msgCtx->textboxColorRed = 70;
                msgCtx->textboxColorGreen = 50;
                msgCtx->textboxColorBlue = 30;
            } else if ((&D_801CFC78[offset] == &D_801CFC78[t = 2]) || (&D_801CFC78[offset] == &D_801CFC78[t = 8])) {
                msgCtx->textboxColorRed = 0;
                msgCtx->textboxColorGreen = 10;
                msgCtx->textboxColorBlue = 50;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 13]) {
                msgCtx->textboxColorRed = 255;
                msgCtx->textboxColorGreen = 255;
                msgCtx->textboxColorBlue = 195;
            } else {
                msgCtx->textboxColorRed = 255;
                msgCtx->textboxColorGreen = 0;
                msgCtx->textboxColorBlue = 0;
            }
            if (&D_801CFC78[offset] == &D_801CFC78[t = 1]) {
                msgCtx->textboxColorAlphaTarget = 230;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 3]) {
                msgCtx->textboxColorAlphaTarget = 180;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 13]) {
                msgCtx->textboxColorAlphaTarget = 220;
            } else {
                msgCtx->textboxColorAlphaTarget = 170;
            }
        } else {
            msgCtx->textboxColorRed = 255;
            msgCtx->textboxColorGreen = 255;
            msgCtx->textboxColorBlue = 255;
            msgCtx->textboxColorAlphaTarget = 255;
        }
        msgCtx->textboxColorAlphaCurrent = 0;
    }
}

void Message_OpenText(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    Player* player = GET_PLAYER(play);
    f32 var_fv0;

    if (play->msgCtx.msgMode == MSGMODE_NONE) {
        gSaveContext.prevHudVisibility = gSaveContext.hudVisibility;
    }

    if (textId == 0xFF) {
        func_80115844(play, 0x12);
        play->msgCtx.unk_120BC = gSaveContext.hudVisibility;
        Interface_SetHudVisibility(HUD_VISIBILITY_A_B_C);
        gSaveContext.save.unk_06 = 20;
    } else if ((textId == 0x579) || (textId == 0x8D8)) {
        Interface_SetHudVisibility(HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE);
    } else if (((textId == 0x28) || (textId == 0x29) || (textId == 0x2A)) && (player->transformation == 3)) {
        //! FAKE:
        if (msgCtx) {}
        textId = 0xC9;
    } else if (textId == 0x11) {
        if (gSaveContext.save.inventory.strayFairies[((void)0, gSaveContext.dungeonIndex)] == 0xF) {
            textId = 0xF3;
        }
    } else if ((textId == 0x92) && (play->sceneId == SCENE_KOEPONARACE)) {
        textId = 0xCD;
    }

    if ((textId == 0xC) && (GET_QUEST_HEART_PIECE_COUNT != 0)) {
        textId = GET_QUEST_HEART_PIECE_COUNT;
        textId += 0xC4;
    }

    msgCtx->currentTextId = textId;

    if ((msgCtx->currentTextId == 0xC) || (msgCtx->currentTextId == 0xD) || (msgCtx->currentTextId == 0xC5) ||
        (msgCtx->currentTextId == 0xC6) || (msgCtx->currentTextId == 0xC7)) {
        Interface_SetHudVisibility(HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE);
    }

    msgCtx->messageHasSetSfx = false;
    D_801C6A70 = 0;
    msgCtx->textboxSkipped = false;
    msgCtx->textIsCredits = false;
    var_fv0 = 1.0f;

    if (play->pauseCtx.bombersNotebookOpen) {
        if (gSaveContext.options.language == LANGUAGE_JAP) {
            msgCtx->textCharScale = 1.4f;
            msgCtx->unk11FFC = 0x1E;
            msgCtx->unk11FF8 = 0x32;
            var_fv0 = 1.4;
        } else {
            msgCtx->textCharScale = 1.4f;
            msgCtx->unk11FFC = 0x16;
            msgCtx->unk11FF8 = 0x32;
            var_fv0 = 1.4;
        }
    } else if (textId >= 0x4E20) {
        msgCtx->textIsCredits = true;
        msgCtx->textCharScale = 0.85f;
        msgCtx->unk11FFC = 6;
        msgCtx->unk11FF8 = 0x14;
    } else if (gSaveContext.options.language == LANGUAGE_JAP) {
        msgCtx->textCharScale = 0.88f;
        msgCtx->unk11FFC = 0x12;
        msgCtx->unk11FF8 = 0x32;
    } else {
        msgCtx->textCharScale = 0.75f;
        msgCtx->unk11FFC = 0xC;
        msgCtx->unk11FF8 = 0x41;
    }

    sCharTexSize = msgCtx->textCharScale * 16.0f;
    sCharTexScale = 1024.0f / msgCtx->textCharScale;
    D_801F6B08 = 1024.0f / var_fv0;

    if (msgCtx->textIsCredits) {
        Message_FindCreditsMessage(play, textId);
        msgCtx->msgLength = font->messageEnd;
        DmaMgr_SendRequest0(&font->msgBuf, &_staff_message_data_staticSegmentRomStart[font->messageStart],
                            font->messageEnd);
    } else if (gSaveContext.options.language == LANGUAGE_JAP) {
        Message_FindMessage(play, textId);
        msgCtx->msgLength = font->messageEnd;
        DmaMgr_SendRequest0(&font->msgBuf, &_message_data_staticSegmentRomStart[font->messageStart], font->messageEnd);
    } else {
        Message_FindMessageNES(play, textId);
        msgCtx->msgLength = font->messageEnd;
        DmaMgr_SendRequest0(&font->msgBuf, &_message_data_staticSegmentRomStart[font->messageStart], font->messageEnd);
    }

    msgCtx->choiceNum = 0;
    msgCtx->textUnskippable = 0;
    msgCtx->textboxEndType = 0;
    msgCtx->textDrawPos = 0;
    msgCtx->msgBufPos = 0;
    msgCtx->decodedTextLen = 0;

    msgCtx->unk11F08 = font->msgBuf.schar[msgCtx->msgBufPos] << 8;
    msgCtx->unk11F08 |= font->msgBuf.schar[msgCtx->msgBufPos + 1];

    msgCtx->unk11F18 = (msgCtx->unk11F08 & 0xF000) >> 0xC;
    msgCtx->textBoxType = (msgCtx->unk11F08 & 0xF00) >> 8;
    msgCtx->textBoxPos = (msgCtx->unk11F08 & 0xF0) >> 4;
    msgCtx->unk11F0C = msgCtx->unk11F08 & 0xF;

    if ((msgCtx->unk11F0C == 1) || (msgCtx->unk11F0C == 3)) {
        msgCtx->textUnskippable = 1;
    }
    msgCtx->itemId = 0xFE;

    if ((msgCtx->textBoxType == 5) || (msgCtx->textBoxType == 0xD) || (play->pauseCtx.bombersNotebookOpen)) {
        msgCtx->unk120CE = msgCtx->unk120D0 = msgCtx->unk120D2 = 0;
    } else {
        msgCtx->unk120CE = msgCtx->unk120D0 = msgCtx->unk120D2 = 0xFF;
    }

    msgCtx->choiceIndex = 0;

    if (msgCtx->unk11F0C != 3) {
        msgCtx->textColorAlpha = 0xFF;
    } else {
        msgCtx->textColorAlpha = 0;
    }

    if (textId == 0x1467) {
        func_80151BB4(play, 2);
    }

    if (textId == 0x2955) {
        func_80151BB4(play, 1);
        func_80151BB4(play, 2);
        func_80151BB4(play, 0x32);
    }
}

void func_801514B0(PlayState* play, u16 arg1, u8 arg2) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    Player* player = GET_PLAYER(play);
    f32 temp = 1024.0f;

    msgCtx->ocarinaAction = 0xFFFF;

    if (msgCtx->msgMode == MSGMODE_NONE) {
        gSaveContext.prevHudVisibility = gSaveContext.hudVisibility;
    }
    msgCtx->messageHasSetSfx = false;
    D_801C6A70 = 0;
    msgCtx->textboxSkipped = false;
    msgCtx->textIsCredits = false;

    if (gSaveContext.options.language == LANGUAGE_JAP) {
        msgCtx->textCharScale = 0.88f;
        msgCtx->unk11FFC = 0x12;
        msgCtx->unk11FF8 = 0x32;
    } else {
        msgCtx->textCharScale = 0.75f;
        msgCtx->unk11FFC = 0xC;
        msgCtx->unk11FF8 = 0x41;
    }

    sCharTexSize = msgCtx->textCharScale * 16.0f;
    sCharTexScale = temp / msgCtx->textCharScale;
    D_801F6B08 = temp / 1;

    if ((arg1 == 0x1709) && (player->transformation == 3)) {
        arg1 = 0x1705;
    }

    msgCtx->currentTextId = arg1;

    if (gSaveContext.options.language == LANGUAGE_JAP) {
        Message_FindMessage(play, arg1);
        msgCtx->msgLength = font->messageEnd;
        DmaMgr_SendRequest0(&font->msgBuf, &SEGMENT_ROM_START(message_data_static)[font->messageStart],
                            font->messageEnd);
    } else {
        Message_FindMessageNES(play, arg1);
        msgCtx->msgLength = font->messageEnd;
        DmaMgr_SendRequest0(&font->msgBuf, &SEGMENT_ROM_START(message_data_static)[font->messageStart],
                            font->messageEnd);
    }
    msgCtx->choiceNum = 0;
    msgCtx->textUnskippable = 0;
    msgCtx->textboxEndType = 0;
    msgCtx->textDrawPos = 0;
    msgCtx->msgBufPos = 0;
    msgCtx->decodedTextLen = 0;
    msgCtx->unk11F08 = font->msgBuf.wchar[msgCtx->msgBufPos];
    msgCtx->unk11F18 = (msgCtx->unk11F08 & 0xF000) >> 0xC;
    msgCtx->textBoxType = 9;
    msgCtx->textBoxPos = arg2;
    msgCtx->unk11F0C = msgCtx->unk11F08 & 0xF;
    msgCtx->textUnskippable = 1;
    DmaMgr_SendRequest0(msgCtx->textboxSegment, &SEGMENT_ROM_START(message_static)[D_801CFC78[0] << 0xC], 0x1000);
    msgCtx->textboxColorRed = 0;
    msgCtx->textboxColorGreen = 0;
    msgCtx->textboxColorBlue = 0;
    msgCtx->textboxColorAlphaTarget = 0xE6;
    msgCtx->textboxColorAlphaCurrent = 0;
    msgCtx->textColorAlpha = 0xFF;
    msgCtx->talkActor = NULL;
    msgCtx->msgMode = MSGMODE_TEXT_START;
    msgCtx->stateTimer = 0;
    msgCtx->textDelayTimer = 0;
    play->msgCtx.ocarinaMode = OCARINA_MODE_NONE;
    msgCtx->unk120D2 = 0xFF;
    msgCtx->unk120CE = msgCtx->unk120D0 = msgCtx->unk120D2;
}

void Message_StartTextbox(PlayState* play, u16 textId, Actor* Actor) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->ocarinaAction = 0xFFFF;
    Message_OpenText(play, textId);
    msgCtx->talkActor = Actor;
    msgCtx->msgMode = MSGMODE_TEXT_START;
    msgCtx->stateTimer = 0;
    msgCtx->textDelayTimer = 0;
    play->msgCtx.ocarinaMode = OCARINA_MODE_NONE;
}

void Message_ContinueTextbox(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    msgCtx->msgLength = 0;
    Message_OpenText(play, textId);
    func_80150A84(play);
    msgCtx->msgMode = MSGMODE_TEXT_CONTINUING;
    msgCtx->stateTimer = 8;
    msgCtx->textDelayTimer = 0;

    if (interfaceCtx->unk_222 == 0) {
        if (textId != 0x1B93) {
            func_8011552C(play, DO_ACTION_NEXT);
        } else if (textId != 0xF8) {
            func_8011552C(play, DO_ACTION_DECIDE);
        }
    }
    msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget;

    if (play->pauseCtx.bombersNotebookOpen) {
        msgCtx->textboxXTarget = 0x22;
        msgCtx->textboxYTarget = 0x15E;
        Message_GrowTextbox(play);
        msgCtx->stateTimer = 1;
    }
}

void Message_DisplaySceneTitleCard(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->msgLength = 0;
    Message_OpenText(play, textId);
    func_80150A84(play);
    Message_DecodeNES(play);
    msgCtx->msgMode = MSGMODE_SCENE_TITLE_CARD_FADE_IN_BACKGROUND;
    msgCtx->textDelayTimer = 0;
    msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget = msgCtx->textColorAlpha = 0;
    msgCtx->stateTimer = 30;

    // Day/Dawn/Night.. Messages
    if ((msgCtx->currentTextId >= 0x1BB2) && (msgCtx->currentTextId <= 0x1BB6)) {
        XREG(74) = 0x6A;
        XREG(75) = 0;
        XREG(77) = 0x58;
        XREG(76) = 0x44;
    } else {
        XREG(74) = 0x42;
        XREG(75) = 0x1E;
        XREG(77) = 0x3C;
        XREG(76) = 0x1C;
        msgCtx->unk11F1A[0] = msgCtx->unk11F1A[1] = msgCtx->unk11F1A[2] = 0;
        Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    }
}

void func_80151BB4(PlayState* play, u8 arg1) {
    MessageContext* msgCtx = &play->msgCtx;

    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        if (!CHECK_WEEKEVENTREG(D_801C6B28[arg1])) {
            msgCtx->unk120B2[msgCtx->unk120B1] = arg1;
            msgCtx->unk120B1++;
        }
    } else if (arg1 >= 20) {
        if (!CHECK_WEEKEVENTREG(D_801C6B28[arg1])) {
            msgCtx->unk120B2[msgCtx->unk120B1] = arg1;
            msgCtx->unk120B1++;
        }
    }
}

s32 func_80151C9C(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    while (true) {
        if (msgCtx->unk120B1 == 0) {
            return false;
        }
        msgCtx->unk120B1--;

        if (!CHECK_WEEKEVENTREG(D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]])) {
            SET_WEEKEVENTREG(D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]);

            if ((D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]] != 0) && CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                Message_ContinueTextbox(play, D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]]);
                play_sound(NA_SE_SY_SCHEDULE_WRITE);
                return true;
            }
        }
    }
}

u16 D_801D028C[] = {
    0x1B5A, 0x1B5B, 0x1B5C, 0x1B5D, 0x1B5E, 0x1B5F, 0x1B60, 0x1B61, 0x1B62, 0x1B63, 0x1B64, 0x1B65, 0x1B66,
    0x1B67, 0x1B68, 0x1B69, 0x1B6A, 0,      0xDC7,  0xDC9,  0x120A, 0x120B, 0x122C, 0x122F, 0x120A, 0x120B,
};
u16 sOcarinaSongFlagsMap[] = { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800 };

void Message_DisplayOcarinaStaffImpl(PlayState* play, u16 ocarinaAction) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 j;
    s16 noStop;
    s32 k;
    u32 i;

    msgCtx->ocarinaAvailableSongs = 0;

    for (i = msgCtx->ocarinaAvailableSongs; i <= (QUEST_SONG_SUN - QUEST_SONG_SONATA); i++) {
        if (CHECK_QUEST_ITEM(QUEST_SONG_SONATA + i)) {
            msgCtx->ocarinaAvailableSongs = msgCtx->ocarinaAvailableSongs | sOcarinaSongFlagsMap[i];
        }
    }

    if (CHECK_QUEST_ITEM(QUEST_SONG_TIME)) {
        msgCtx->ocarinaAvailableSongs |= 0x3000;
    }
    if (CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
        msgCtx->ocarinaAvailableSongs |= 0x4000;
    }
    if (CHECK_QUEST_ITEM(QUEST_SONG_LULLABY)) {
        msgCtx->ocarinaAvailableSongs &= (u16)~0x4000;
    }
    if (gSaveContext.save.scarecrowSpawnSongSet) {
        msgCtx->ocarinaAvailableSongs |= 0x400000;
    }
    if (CHECK_EVENTINF(EVENTINF_31)) {
        msgCtx->ocarinaAvailableSongs |= 0x800000;
    }

    msgCtx->ocarinaStaff = AudioOcarina_GetRecordingStaff();

    if ((ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) ||
        (ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
        sOcarinaButtonAlphaValues[0] = sOcarinaButtonAlphaValues[1] = sOcarinaButtonAlphaValues[2] =
            sOcarinaButtonAlphaValues[3] = 255;
    } else {
        msgCtx->ocarinaStaff->pos = 0;
        sOcarinaButtonIndexBufPos = 0;
        sOcarinaButtonIndexBufLen = 0;
        Message_ResetOcarinaButtonState(play);
    }

    sLastPlayedSong = 0xFF;
    msgCtx->lastPlayedSong = 0xFF;
    msgCtx->lastOcarinaButtonIndex = 0xFF;
    noStop = false;
    msgCtx->ocarinaAction = ocarinaAction;

    if ((ocarinaAction >= OCARINA_ACTION_TIMED_PROMPT_SONATA) &&
        (ocarinaAction <= OCARINA_ACTION_TIMED_PROMPT_STORMS)) {
        Message_OpenText(play, 0x1B59);
        func_80150A84(play);
    } else if ((ocarinaAction == OCARINA_ACTION_3B) || (ocarinaAction == OCARINA_ACTION_3C)) {
        noStop = true;
        Message_OpenText(play, D_801D028C[ocarinaAction - 0x29]);
        func_80150A84(play);
    } else if ((ocarinaAction >= OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_FIRST_HALF) &&
               (ocarinaAction <= OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
        noStop = true;
        Message_OpenText(play, D_801D028C[ocarinaAction - 0x29]);
        func_80150A84(play);
    } else if ((ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
               (ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) {
        noStop = true;
        Message_OpenText(play, 0x1B59);
        func_80150A84(play);
    } else if ((ocarinaAction == OCARINA_ACTION_FREE_PLAY) || (ocarinaAction >= OCARINA_ACTION_CHECK_TIME)) {
        if ((ocarinaAction >= OCARINA_ACTION_CHECK_TIME) && (ocarinaAction <= OCARINA_ACTION_CHECK_STORMS)) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
        }
        if (ocarinaAction == OCARINA_ACTION_SCARECROW_SPAWN_DEMONSTRATION) {
            Message_OpenText(play, 0x1B5B);
            func_80150A84(play);
        } else {
            Message_OpenText(play, 0x1B5A);
            func_80150A84(play);
        }
    } else {
        noStop = true;
        if (ocarinaAction >= OCARINA_ACTION_PROMPT_SONATA) {
            Message_OpenText(play, 0x1B59);
            func_80150A84(play);
        } else {
            Message_OpenText(play, D_801D028C[ocarinaAction]);
            func_80150A84(play);
        }
    }

    msgCtx->talkActor = NULL;
    msgCtx->textDelayTimer = 0;
    play->msgCtx.ocarinaMode = OCARINA_MODE_NONE;
    msgCtx->textboxXTarget = 0x22;
    msgCtx->textboxYTarget = 0x8E;
    msgCtx->stateTimer = 8;
    Message_GrowTextbox(play);
    msgCtx->textboxX = 0x22;
    msgCtx->textboxY = 0x8E;
    msgCtx->unk1200C = 0x200;
    msgCtx->unk1200E = 0x200;
    msgCtx->unk12008 = 0x100;
    msgCtx->unk1200A = 0x40;
    msgCtx->msgMode = MSGMODE_TEXT_CONTINUING;
    msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget;
    msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget;

    if (!noStop) {
        func_80115844(play, 0x12);
        noStop = gSaveContext.hudVisibility;
        Interface_SetHudVisibility(HUD_VISIBILITY_B_ALT);
        gSaveContext.hudVisibility = noStop;
    }

    if ((ocarinaAction == OCARINA_ACTION_FREE_PLAY) || (ocarinaAction == OCARINA_ACTION_CHECK_NOTIME)) {
        msgCtx->msgMode = MSGMODE_OCARINA_STARTING;
        msgCtx->textBoxType = 0xE;
    } else if (ocarinaAction == OCARINA_ACTION_3A) {
        msgCtx->msgMode = MSGMODE_32;
    } else if (ocarinaAction == OCARINA_ACTION_37) {
        msgCtx->msgMode = MSGMODE_2F;
        msgCtx->textBoxType = 2;
    } else if (ocarinaAction == OCARINA_ACTION_SCARECROW_LONG_DEMONSTRATION) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
        msgCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
        msgCtx->ocarinaStaff->pos = 0;
        sOcarinaButtonIndexBufLen = 0;
        sOcarinaButtonIndexBufPos = sOcarinaButtonIndexBufLen;
        Message_ResetOcarinaButtonState(play);
        msgCtx->msgMode = MSGMODE_SCARECROW_LONG_DEMONSTRATION;
        AudioOcarina_SetPlaybackSong(OCARINA_SONG_SCARECROW_LONG + 1, 1);
        gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
        Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    }

    for (j = 0, k = 0; j < 48; j++, k += 0x80) {
        Font_LoadChar(play, 0x8140, k);
    };

    msgCtx->stateTimer = 3;
}

void Message_DisplayOcarinaStaff(PlayState* play, u16 ocarinaAction) {
    play->msgCtx.blockSunsSong = false;
    Message_DisplayOcarinaStaffImpl(play, ocarinaAction);
}

void Message_DisplayOcarinaStaffBlockSunsSong(PlayState* play, u16 ocarinaAction) {
    play->msgCtx.blockSunsSong = true;
    Message_DisplayOcarinaStaffImpl(play, ocarinaAction);
}

/**
 * @return u8 A value of the TextState enum representing the current state of the on-screen message
 */
u8 Message_GetState(MessageContext* msgCtx) {
    if (msgCtx->msgLength == 0) {
        return TEXT_STATE_NONE;
    }

    if (msgCtx->msgMode == MSGMODE_TEXT_DONE) {
        if (msgCtx->unk11F14 != 0xFFFF) {
            return TEXT_STATE_1;
        }

        if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_11)) {
            return TEXT_STATE_CHOICE;
        }
        if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_40) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_42) ||
            (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_30)) {
            return TEXT_STATE_5;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_41) {
            return TEXT_STATE_16;
        }
        if ((msgCtx->textboxEndType >= TEXTBOX_ENDTYPE_50) && (msgCtx->textboxEndType <= TEXTBOX_ENDTYPE_57)) {
            return TEXT_STATE_3;
        }
        if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_60) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_61)) {
            return TEXT_STATE_14;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_62) {
            return TEXT_STATE_15;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_63) {
            return TEXT_STATE_17;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_12) {
            return TEXT_STATE_18;
        }
        return TEXT_STATE_DONE;
    }

    if (msgCtx->msgMode == MSGMODE_TEXT_AWAIT_NEXT) {
        return TEXT_STATE_10;
    }
    if (msgCtx->msgMode == MSGMODE_SONG_DEMONSTRATION_DONE) {
        return TEXT_STATE_7;
    }
    if ((msgCtx->ocarinaMode == OCARINA_MODE_EVENT) || (msgCtx->msgMode == MSGMODE_37)) {
        return TEXT_STATE_8;
    }
    if (msgCtx->msgMode == MSGMODE_OCARINA_AWAIT_INPUT) {
        return TEXT_STATE_9;
    }
    if ((msgCtx->msgMode == MSGMODE_21) || (msgCtx->msgMode == MSGMODE_3A)) {
        return TEXT_STATE_11;
    }
    if (msgCtx->msgMode == MSGMODE_3D) {
        return TEXT_STATE_12;
    }
    if (msgCtx->msgMode == MSGMODE_40) {
        return TEXT_STATE_13;
    }
    if ((msgCtx->msgMode == MSGMODE_TEXT_CLOSING) && (msgCtx->stateTimer == 1) && (msgCtx->unk120B1 == 0)) {
        return TEXT_STATE_CLOSING;
    }

    return TEXT_STATE_3;
}

void Message_DrawTextBox(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx = *gfxP;

    gDPPipeSync(gfx++);

    if (((u32)msgCtx->textBoxType == 0) || (msgCtx->textBoxType == 2) || (msgCtx->textBoxType == 9) ||
        (msgCtx->textBoxType == 0xA)) {
        gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    } else if (msgCtx->textBoxType == 3) {
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetPrimColor(gfx++, 0, 0, msgCtx->textboxColorRed, msgCtx->textboxColorGreen, msgCtx->textboxColorBlue,
                    msgCtx->textboxColorAlphaCurrent);

    if (((u32)msgCtx->textBoxType == 0) || (msgCtx->textBoxType == 2) || (msgCtx->textBoxType == 6) ||
        (msgCtx->textBoxType == 8) || (msgCtx->textBoxType == 9) || (msgCtx->textBoxType == 0xA)) {
        gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment, G_IM_FMT_I, 128, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPPipeSync(gfx++);

        if (msgCtx->textBoxType == 3) {
            gDPSetEnvColor(gfx++, 0, 0, 0, 255);
        } else if (msgCtx->textBoxType == 0xD) {
            gDPSetEnvColor(gfx++, 20, 0, 10, 255);
        } else {
            gDPSetEnvColor(gfx++, 50, 20, 0, 255);
        }
        gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment, G_IM_FMT_IA, 128, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    if (msgCtx->textBoxType == 0xA) {
        gSPTextureRectangle(gfx++, (msgCtx->textboxX << 2), ((msgCtx->textboxY + 22) << 2),
                            ((msgCtx->textboxX + msgCtx->unk12008) << 2), ((msgCtx->textboxY + 0x36) << 2),
                            G_TX_RENDERTILE, 0, 0x0006, msgCtx->unk1200C << 1, 0x800);
    } else {
        gSPTextureRectangle(gfx++, (msgCtx->textboxX << 2), ((msgCtx->textboxY) << 2),
                            ((msgCtx->textboxX + sTextboxWidth) << 2), ((msgCtx->textboxY + sTextboxHeight) << 2),
                            G_TX_RENDERTILE, 0, 0, sTextboxTexWidth, sTextboxTexHeight);
    }

    // Draw treble clef
    if (msgCtx->textBoxType == 3) {
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 255, 100, 0, 255);
        gDPLoadTextureBlock_4b(gfx++, gOcarinaTrebleClefTex, G_IM_FMT_I, 16, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, 0x0138, 0x0298, 0x0178, 0x0318, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    }

    *gfxP = gfx++;
}

void Message_SetView(View* view) {
    SET_FULLSCREEN_VIEWPORT(view);
    View_ApplyOrthoToOverlay(view);
}

void func_80152CAC(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_SONATA) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_MONKEY);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_HEALING) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_PIANO);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_SARIAS) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_TATL);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EPONAS) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_FEMALE_VOICE);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_STORMS) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_GORON_LULLABY) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_BABY_SINGING);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_GORON_LULLABY_INTRO) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_ELDER_GORON_DRUMS);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_OATH) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_TATL);
    } else if (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_ELEGY) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_IKANA_KING);
    } else {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
    }

    if ((msgCtx->ocarinaAction == OCARINA_ACTION_3B) || (msgCtx->ocarinaAction == OCARINA_ACTION_3C)) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_ELDER_GORON_DRUMS);
        AudioOcarina_SetPlaybackSong(OCARINA_SONG_GORON_LULLABY_INTRO + 1, 0x83);
        return;
    }
    if ((msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_FIRST_HALF) ||
        (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_FIRST_HALF)) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_BASS_GUITAR);
        AudioOcarina_SetPlaybackSong(
            ((msgCtx->ocarinaAction - OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_FIRST_HALF) + OCARINA_SONG_EVAN_PART1 + 1),
            0x84);
        return;
    }
    if ((msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_SECOND_HALF) ||
        (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_SECOND_HALF)) {
        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_ZORA_GUITAR);
        AudioOcarina_SetPlaybackSong(
            ((msgCtx->ocarinaAction - OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_SECOND_HALF) + OCARINA_SONG_EVAN_PART1 + 1),
            0x44);
        return;
    }
    AudioOcarina_SetPlaybackSong((msgCtx->ocarinaAction - OCARINA_ACTION_FREE_PLAY), 2);
}

s16 sOcarinaEffectActorIds[] = {
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE,  ACTOR_OCEFF_WIPE7, // Song of Time Effect, Song of Healing Effect
    ACTOR_OCEFF_WIPE2, ACTOR_OCEFF_WIPE6, // Epona's Song Effect, Song of Soaring Effect
    ACTOR_OCEFF_STORM, ACTOR_OCEFF_SPOT,  // Song of Storms Effect II [?], Sun's Song Effect
    ACTOR_OCEFF_WIPE,  ACTOR_OCEFF_WIPE,  // Song of Time Effect, Song of Time Effect
    ACTOR_OCEFF_WIPE4                     // Scarecrow's Song Effect
};
s32 sOcarinaEffectActorParams[] = { 0, 1, 2, 3, 4, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0 };

void Message_SpawnSongEffect(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);

    if (1) {}
    if ((msgCtx->songPlayed <= OCARINA_SONG_SCARECROW_SPAWN) &&
        (msgCtx->songPlayed != OCARINA_SONG_GORON_LULLABY_INTRO) &&
        !((msgCtx->ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
          (msgCtx->ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU))) {
        msgCtx->ocarinaSongEffectActive = true;
        if (msgCtx->songPlayed != OCARINA_SONG_SCARECROW_SPAWN) {
            Actor_Spawn(&play->actorCtx, play, sOcarinaEffectActorIds[msgCtx->songPlayed], player->actor.world.pos.x,
                        player->actor.world.pos.y, player->actor.world.pos.z, 0, 0, 0,
                        sOcarinaEffectActorParams[msgCtx->songPlayed]);
            return;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_OCEFF_WIPE4, player->actor.world.pos.x, player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 0);
    }
}

s16 sOcarinaButtonAPrimColors[][3] = {
    { 80, 150, 255 },
    { 100, 200, 255 },
};
s16 sOcarinaButtonAEnvColors[][3] = {
    { 10, 10, 10 },
    { 50, 50, 255 },
};
s16 sOcarinaButtonCPrimColors[][3] = {
    { 255, 255, 50 },
    { 255, 255, 180 },
};
s16 sOcarinaButtonCEnvColors[][3] = {
    { 10, 10, 10 },
    { 110, 110, 50 },
};

void Message_FlashOcarinaButtons(void) {
    sOcarinaButtonStepR = ABS_ALT(sOcarinaButtonAPrimR - sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][0]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepG = ABS_ALT(sOcarinaButtonAPrimG - sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][1]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepB = ABS_ALT(sOcarinaButtonAPrimB - sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][2]) /
                          sOcarinaButtonFlashTimer;

    if (sOcarinaButtonAPrimR >= sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][0]) {
        sOcarinaButtonAPrimR -= sOcarinaButtonStepR;
    } else {
        sOcarinaButtonAPrimR += sOcarinaButtonStepR;
    }
    if (sOcarinaButtonAPrimG >= sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][1]) {
        sOcarinaButtonAPrimG -= sOcarinaButtonStepG;
    } else {
        sOcarinaButtonAPrimG += sOcarinaButtonStepG;
    }
    if (sOcarinaButtonAPrimB >= sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][2]) {
        sOcarinaButtonAPrimB -= sOcarinaButtonStepB;
    } else {
        sOcarinaButtonAPrimB += sOcarinaButtonStepB;
    }

    sOcarinaButtonStepR = ABS_ALT(sOcarinaButtonAEnvR - sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][0]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepG = ABS_ALT(sOcarinaButtonAEnvG - sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][1]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepB = ABS_ALT(sOcarinaButtonAEnvB - sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][2]) /
                          sOcarinaButtonFlashTimer;

    if (sOcarinaButtonCEnvR >= sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][0]) {
        sOcarinaButtonAEnvR -= sOcarinaButtonStepR;
    } else {
        sOcarinaButtonAEnvR += sOcarinaButtonStepR;
    }
    if (sOcarinaButtonCEnvG >= sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][1]) {
        sOcarinaButtonAEnvG -= sOcarinaButtonStepG;
    } else {
        sOcarinaButtonAEnvG += sOcarinaButtonStepG;
    }
    if (sOcarinaButtonCEnvB >= sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][2]) {
        sOcarinaButtonAEnvB -= sOcarinaButtonStepB;
    } else {
        sOcarinaButtonAEnvB += sOcarinaButtonStepB;
    }

    sOcarinaButtonStepR = ABS_ALT(sOcarinaButtonCPrimR - sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][0]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepG = ABS_ALT(sOcarinaButtonCPrimG - sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][1]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepB = ABS_ALT(sOcarinaButtonCPrimB - sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][2]) /
                          sOcarinaButtonFlashTimer;

    if (sOcarinaButtonCPrimR >= sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][0]) {
        sOcarinaButtonCPrimR -= sOcarinaButtonStepR;
    } else {
        sOcarinaButtonCPrimR += sOcarinaButtonStepR;
    }
    if (sOcarinaButtonCPrimG >= sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][1]) {
        sOcarinaButtonCPrimG -= sOcarinaButtonStepG;
    } else {
        sOcarinaButtonCPrimG += sOcarinaButtonStepG;
    }
    if (sOcarinaButtonCPrimB >= sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][2]) {
        sOcarinaButtonCPrimB -= sOcarinaButtonStepB;
    } else {
        sOcarinaButtonCPrimB += sOcarinaButtonStepB;
    }

    sOcarinaButtonStepR = ABS_ALT(sOcarinaButtonCEnvR - sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][0]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepG = ABS_ALT(sOcarinaButtonCEnvG - sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][1]) /
                          sOcarinaButtonFlashTimer;
    sOcarinaButtonStepB = ABS_ALT(sOcarinaButtonCEnvB - sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][2]) /
                          sOcarinaButtonFlashTimer;

    if (sOcarinaButtonCEnvR >= sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][0]) {
        sOcarinaButtonCEnvR -= sOcarinaButtonStepR;
    } else {
        sOcarinaButtonCEnvR += sOcarinaButtonStepR;
    }
    if (sOcarinaButtonCEnvG >= sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][1]) {
        sOcarinaButtonCEnvG -= sOcarinaButtonStepG;
    } else {
        sOcarinaButtonCEnvG += sOcarinaButtonStepG;
    }
    if (sOcarinaButtonCEnvB >= sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][2]) {
        sOcarinaButtonCEnvB -= sOcarinaButtonStepB;
    } else {
        sOcarinaButtonCEnvB += sOcarinaButtonStepB;
    }

    sOcarinaButtonFlashTimer--;
    if (sOcarinaButtonFlashTimer == 0) {
        sOcarinaButtonAPrimR = sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][0];
        sOcarinaButtonAPrimG = sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][1];
        sOcarinaButtonAPrimB = sOcarinaButtonAPrimColors[sOcarinaButtonFlashColorIndex][2];
        sOcarinaButtonAEnvR = sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][0];
        sOcarinaButtonAEnvG = sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][1];
        sOcarinaButtonAEnvB = sOcarinaButtonAEnvColors[sOcarinaButtonFlashColorIndex][2];
        sOcarinaButtonCPrimR = sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][0];
        sOcarinaButtonCPrimG = sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][1];
        sOcarinaButtonCPrimB = sOcarinaButtonCPrimColors[sOcarinaButtonFlashColorIndex][2];
        sOcarinaButtonCEnvR = sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][0];
        sOcarinaButtonCEnvG = sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][1];
        sOcarinaButtonCEnvB = sOcarinaButtonCEnvColors[sOcarinaButtonFlashColorIndex][2];
        sOcarinaButtonFlashTimer = 3;
        sOcarinaButtonFlashColorIndex ^= 1;
    }
}

TexturePtr sOcarinaButtonTextures[] = {
    gOcarinaATex, gOcarinaCDownTex, gOcarinaCRightTex, gOcarinaCLeftTex, gOcarinaCUpTex,
};

void Message_DrawOcarinaButtons(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx = *gfxP;
    u16 i;
    u16 notePosX;

    if ((play->msgCtx.msgMode >= MSGMODE_OCARINA_PLAYING) && (msgCtx->msgMode <= MSGMODE_40)) {
        if ((msgCtx->ocarinaAction != OCARINA_ACTION_FREE_PLAY) &&
            (msgCtx->ocarinaAction != OCARINA_ACTION_CHECK_NOTIME)) {
            func_8012C680(&gfx);

            gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                              ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

            if ((msgCtx->msgMode == MSGMODE_SONG_PROMPT) || (msgCtx->msgMode == MSGMODE_36)) {
                if ((msgCtx->ocarinaAction != OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) &&
                    (msgCtx->ocarinaAction != OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                    if (msgCtx->ocarinaAction >= OCARINA_ACTION_TIMED_PROMPT_SONATA) {
                        sOcarinaButtonStepG = msgCtx->ocarinaAction - OCARINA_ACTION_TIMED_PROMPT_SONATA;
                    } else if ((msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) ||
                               (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                        // Can never pass as the conditional is opposite to one scope higher
                        sOcarinaButtonStepG = (msgCtx->ocarinaAction - OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) +
                                              OCARINA_SONG_EVAN_PART1;
                    } else if ((msgCtx->ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
                               (msgCtx->ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) {
                        sOcarinaButtonStepG = msgCtx->ocarinaAction - OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN +
                                              OCARINA_SONG_WIND_FISH_HUMAN;
                    } else {
                        sOcarinaButtonStepG = msgCtx->ocarinaAction - OCARINA_ACTION_PROMPT_SONATA;
                    }
                    sOcarinaButtonStepR = gOcarinaSongButtons[sOcarinaButtonStepG].numButtons;

                    for (notePosX = 98, i = 0; i < sOcarinaButtonStepR; notePosX += 18, i++) {
                        gDPPipeSync(gfx++);
                        gDPSetPrimColor(gfx++, 0, 0, 150, 150, 150, 150);
                        gDPSetEnvColor(gfx++, 10, 10, 10, 0);

                        gDPLoadTextureBlock(
                            gfx++, sOcarinaButtonTextures[gOcarinaSongButtons[sOcarinaButtonStepG].buttonIndex[i]],
                            G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                        gSPTextureRectangle(
                            gfx++, notePosX << 2,
                            msgCtx->ocarinaButtonsPosY[gOcarinaSongButtons[sOcarinaButtonStepG].buttonIndex[i]] << 2,
                            (notePosX + 16) << 2,
                            (msgCtx->ocarinaButtonsPosY[gOcarinaSongButtons[sOcarinaButtonStepG].buttonIndex[i]] + 16)
                                << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                    }
                }
            }

            if (msgCtx->msgMode != MSGMODE_SCARECROW_LONG_RECORDING_START) {
                for (notePosX = 98, i = 0; i < 8; notePosX += 18, i++) {
                    if (sOcarinaButtonIndexBuf[i] == OCARINA_BTN_INVALID) {
                        break;
                    }

                    if (sOcarinaButtonAlphaValues[i] != 255) {
                        sOcarinaButtonAlphaValues[i] += 50;
                        if (sOcarinaButtonAlphaValues[i] >= 255) {
                            sOcarinaButtonAlphaValues[i] = 255;
                        }
                    }

                    gDPPipeSync(gfx++);
                    if (sOcarinaButtonIndexBuf[i] == OCARINA_BTN_A) {
                        gDPSetPrimColor(gfx++, 0, 0, sOcarinaButtonAPrimR, sOcarinaButtonAPrimG, sOcarinaButtonAPrimB,
                                        sOcarinaButtonAlphaValues[i]);
                        gDPSetEnvColor(gfx++, sOcarinaButtonAEnvR, sOcarinaButtonAEnvG, sOcarinaButtonAEnvB, 0);
                    } else {
                        gDPSetPrimColor(gfx++, 0, 0, sOcarinaButtonCPrimR, sOcarinaButtonCPrimG, sOcarinaButtonCPrimB,
                                        sOcarinaButtonAlphaValues[i]);
                        gDPSetEnvColor(gfx++, sOcarinaButtonCEnvR, sOcarinaButtonCEnvG, sOcarinaButtonCEnvB, 0);
                    }

                    gDPLoadTextureBlock(gfx++, sOcarinaButtonTextures[sOcarinaButtonIndexBuf[i]], G_IM_FMT_IA,
                                        G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                    gSPTextureRectangle(
                        gfx++, notePosX << 2, msgCtx->ocarinaButtonsPosY[sOcarinaButtonIndexBuf[i]] << 2,
                        (notePosX + 16) << 2, (msgCtx->ocarinaButtonsPosY[sOcarinaButtonIndexBuf[i]] + 16) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                }
            }
        }
    }
    *gfxP = gfx;
}

void Message_DrawText(PlayState* play, Gfx** gfxP) {
    if ((gSaveContext.options.language == LANGUAGE_JAP) && !play->msgCtx.textIsCredits) {
        Message_DrawTextDefault(play, gfxP);
    } else if (play->msgCtx.textIsCredits) {
        Message_DrawTextCredits(play, gfxP);
    } else {
        Message_DrawTextNES(play, gfxP, 0);
    }
}

void Message_DrawSceneTitleCard(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx;

    gfx = *gfxP;
    func_8012C680(&gfx);

    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetAlphaDither(gfx++, G_AD_NOTPATTERN);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textboxColorAlphaCurrent);
    gDPSetEnvColor(gfx++, 140, 40, 160, 255);
    gDPLoadTextureBlock(gfx++, gSceneTitleCardGradientTex, G_IM_FMT_I, G_IM_SIZ_8b, 64, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gfx++, 0, XREG(77) << 2, 0x0500, (XREG(77) + XREG(76)) << 2, G_TX_RENDERTILE, 0, 0, 0x00CC,
                        0x0400);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);

    if ((msgCtx->currentTextId < 0x1BB2) || (msgCtx->currentTextId >= 0x1BB7)) {
        msgCtx->unk11FF8 = XREG(75);
    }
    msgCtx->unk11FFA = XREG(74);
    Message_DrawTextNES(play, &gfx, 0);
    *gfxP = gfx++;
}

s16 sOcarinaSongFanfares[] = {
    NA_BGM_OCA_SONATA,
    NA_BGM_OCA_LULLABY,
    NA_BGM_OCA_NEW_WAVE,
    NA_BGM_OCA_ELEGY,
    NA_BGM_OCA_OATH,
    NA_BGM_MAJORAS_LAIR,
    NA_BGM_OCA_TIME,
    NA_BGM_OCA_HEALING,
    NA_BGM_OCA_EPONA,
    NA_BGM_OCA_SOARING,
    NA_BGM_OCA_STORM,
    NA_BGM_OCA_SUNS,
    NA_BGM_INVERTED_SONG_OF_TIME,
    NA_BGM_SONG_OF_DOUBLE_TIME,
    NA_BGM_OCA_LULLABY_INTRO,
    NA_BGM_OCA_LULLABY_INTRO,
    NA_BGM_OCA_LULLABY_INTRO,
};

s8 sOcarinaSongFanfareIoData[] = {
    0x35, 0x5C, 0x5D, 0x5E, 0x35,
};

u8 sPlayerFormOcarinaInstruments[] = {
    OCARINA_INSTRUMENT_DEFAULT,
    OCARINA_INSTRUMENT_GORON_DRUMS,
    OCARINA_INSTRUMENT_ZORA_GUITAR,
    OCARINA_INSTRUMENT_DEKU_PIPES,
};

s16 D_801D03A8[] = {
    0x3B, 0x3B, 0x3B, 0x3B, 0x22, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B, 0x3B,
};

void Message_DrawMain(PlayState* play, Gfx** gfxP) {
    s32 pad;
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx;
    u16 i;
    u16 buttonIndexPos;
    u8 ocarinaError;
    s32 j;
    s16 temp_v0_33;
    s16 temp;

    gfx = *gfxP;

    gSPSegment(gfx++, 0x02, play->interfaceCtx.parameterSegment);
    gSPSegment(gfx++, 0x07, msgCtx->textboxSegment);

    if (msgCtx->msgLength != 0) {
        if (!msgCtx->textIsCredits) {
            Message_SetView(&msgCtx->view);
            func_8012C680(&gfx);
            if (msgCtx->ocarinaAction != OCARINA_ACTION_37) {
                if ((msgCtx->msgMode != MSGMODE_18) && (msgCtx->msgMode != MSGMODE_39) &&
                    (msgCtx->msgMode != MSGMODE_3C) && (msgCtx->msgMode != MSGMODE_3F) &&
                    (msgCtx->msgMode != MSGMODE_3A) && (msgCtx->msgMode != MSGMODE_3D) &&
                    (msgCtx->msgMode != MSGMODE_40) &&
                    (((msgCtx->msgMode >= MSGMODE_TEXT_BOX_GROWING) && (msgCtx->msgMode <= MSGMODE_TEXT_DONE)) ||
                     ((msgCtx->msgMode >= MSGMODE_NEW_CYCLE_0) && (msgCtx->msgMode <= MSGMODE_OWL_SAVE_2))) &&
                    (D_801CFC78[msgCtx->textBoxType] != 0xE)) {
                    Message_DrawTextBox(play, &gfx);
                }
            }
        }
        func_8012C680(&gfx);
        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);

        if (YREG(0) != msgCtx->msgMode) {
            YREG(0) = msgCtx->msgMode;
            YREG(1) = msgCtx->ocarinaAction;
        }

        switch (msgCtx->msgMode) {
            case MSGMODE_TEXT_START:
            case MSGMODE_TEXT_BOX_GROWING:
            case MSGMODE_TEXT_STARTING:
            case MSGMODE_TEXT_NEXT_MSG:
                break;

            case MSGMODE_TEXT_CONTINUING:
                if (msgCtx->stateTimer == 1) {
                    for (i = 0, j = 0; i < 48; i++, j += 0x80) {
                        Font_LoadChar(play, 0x8140, j);
                    }
                    Message_DrawText(play, &gfx);
                } else {
                    gDPPipeSync(gfx++);
                    gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0);
                    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
                }
                break;

            case MSGMODE_TEXT_DISPLAYING:
            case MSGMODE_TEXT_DELAYED_BREAK:
            case MSGMODE_9:
                if ((gSaveContext.options.language == LANGUAGE_JAP) && !msgCtx->textIsCredits) {
                    if (msgCtx->textDelay != 0) {
                        msgCtx->textDrawPos += msgCtx->textDelay;
                    }
                    Message_DrawTextNES(play, &gfx, 0);
                    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                        Message_DrawTextNES(play, &gfx, (s32)msgCtx->textDrawPos);
                    }
                } else if (msgCtx->textIsCredits) {
                    Message_DrawTextCredits(play, &gfx);
                } else {
                    if (msgCtx->textDelay != 0) {
                        msgCtx->textDrawPos += msgCtx->textDelay;
                    }
                    Message_DrawTextNES(play, &gfx, 0);
                    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                        Message_DrawTextNES(play, &gfx, (s32)msgCtx->textDrawPos);
                    }
                }
                break;

            case MSGMODE_NEW_CYCLE_0:
            case MSGMODE_NEW_CYCLE_1:
            case MSGMODE_NEW_CYCLE_2:
            case MSGMODE_OWL_SAVE_0:
            case MSGMODE_OWL_SAVE_1:
            case MSGMODE_OWL_SAVE_2:
                Message_DrawTextNES(play, &gfx, 0);
                break;

            case MSGMODE_TEXT_AWAIT_INPUT:
            case MSGMODE_TEXT_AWAIT_NEXT:
                Message_DrawText(play, &gfx);
                Message_DrawTextboxIcon(play, &gfx, 0x9E,
                                        (s16)(D_801D03A8[msgCtx->textBoxType] + msgCtx->textboxYTarget));
                break;

            case MSGMODE_OCARINA_STARTING:
            case MSGMODE_SONG_DEMONSTRATION_STARTING:
            case MSGMODE_SONG_PROMPT_STARTING:
            case MSGMODE_32:
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();
                play->msgCtx.ocarinaMode = OCARINA_MODE_ACTIVE;
                if ((msgCtx->ocarinaAction != OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) &&
                    (msgCtx->ocarinaAction != OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                    msgCtx->ocarinaStaff->pos = 0;
                    sOcarinaButtonIndexBufPos = 0;
                    Message_ResetOcarinaButtonState(play);
                }
                sOcarinaButtonFlashColorIndex = 1;
                sOcarinaButtonFlashTimer = 3;
                if (msgCtx->msgMode == MSGMODE_OCARINA_STARTING) {
                    if ((msgCtx->ocarinaAction == OCARINA_ACTION_0) ||
                        (msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY) ||
                        (msgCtx->ocarinaAction == OCARINA_ACTION_SCARECROW_SPAWN_RECORDING) ||
                        (msgCtx->ocarinaAction == OCARINA_ACTION_CHECK_NOTIME) ||
                        (msgCtx->ocarinaAction >= OCARINA_ACTION_CHECK_TIME)) {
                        if ((msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY) ||
                            (msgCtx->ocarinaAction == OCARINA_ACTION_CHECK_NOTIME)) {
                            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_52_10)) {
                                AudioOcarina_StartDefault(msgCtx->ocarinaAvailableSongs | 0xC0000000);
                            } else if (CHECK_EVENTINF(EVENTINF_31)) {
                                AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                                AudioOcarina_StartDefault(0x80800000);
                            } else {
                                AudioOcarina_StartAtSongStartingPos((msgCtx->ocarinaAvailableSongs + 0x80000) |
                                                                    0xC0000000);
                                AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                            }
                        } else {
                            AudioOcarina_StartDefault(msgCtx->ocarinaAvailableSongs);
                        }
                    } else {
                        AudioOcarina_StartDefault((1 << msgCtx->ocarinaAction) | 0x80000000);
                    }
                    msgCtx->msgMode = MSGMODE_OCARINA_PLAYING;
                    if (CHECK_EVENTINF(EVENTINF_24)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEKU_TRUMPET);
                    } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_41_20)) {
                        AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                        //! FAKE:
                        (void)CUR_FORM;
                        if (gSaveContext.save.playerForm == 4) {}
                    } else {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_AMPLIFIED_GUITAR);
                    }
                } else if (msgCtx->msgMode == MSGMODE_SONG_DEMONSTRATION_STARTING) {
                    msgCtx->stateTimer = 20;
                    msgCtx->msgMode = MSGMODE_19;
                } else if (msgCtx->msgMode == MSGMODE_32) {
                    AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                    AudioOcarina_StartDefault(0x80800000);
                    msgCtx->msgMode = MSGMODE_33;
                } else { // MSGMODE_SONG_PROMPT_STARTING
                    if (CHECK_EVENTINF(EVENTINF_24)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEKU_TRUMPET);
                    } else {
                        AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                    }

                    if ((msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) ||
                        (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                        AudioOcarina_StartForSongCheck(
                            (1 << (OCARINA_ACTION_PROMPT_SONATA + msgCtx->ocarinaAction)) | 0x80000000, 4);
                        msgCtx->msgMode = MSGMODE_SONG_PROMPT;
                    } else {
                        if ((msgCtx->ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
                            (msgCtx->ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) {
                            AudioOcarina_StartDefault(
                                (1 << ((msgCtx->ocarinaAction - OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) +
                                       OCARINA_SONG_WIND_FISH_HUMAN)) |
                                0x80000000);
                        } else {
                            AudioOcarina_StartDefault(
                                (1 << ((msgCtx->ocarinaAction - OCARINA_ACTION_PROMPT_SONATA) + OCARINA_SONG_SONATA)) |
                                0x80000000);
                        }
                        msgCtx->msgMode = MSGMODE_SONG_PROMPT;
                    }
                }

                if ((msgCtx->ocarinaAction != OCARINA_ACTION_FREE_PLAY) &&
                    (msgCtx->ocarinaAction != OCARINA_ACTION_CHECK_NOTIME)) {
                    Message_DrawText(play, &gfx);
                }
                break;

            case MSGMODE_OCARINA_PLAYING:
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();

                if ((u32)msgCtx->ocarinaStaff->pos != 0) {
                    if ((msgCtx->ocarinaStaff->pos == 1) && (sOcarinaButtonIndexBufPos == 8)) {
                        sOcarinaButtonIndexBufPos = 0;
                    }

                    if (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1)) {
                        msgCtx->lastOcarinaButtonIndex = sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos - 1] =
                            msgCtx->ocarinaStaff->buttonIndex;
                        sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos] = OCARINA_BTN_INVALID;
                        sOcarinaButtonIndexBufPos++;
                    }
                }

                msgCtx->songPlayed = msgCtx->ocarinaStaff->state;

                if (msgCtx->ocarinaStaff->state <= OCARINA_SONG_SCARECROW_SPAWN) {
                    if (msgCtx->ocarinaStaff->state == OCARINA_SONG_EVAN_PART1) {
                        AudioOcarina_ResetAndReadInput();
                        AudioOcarina_StartDefault(0x80100000);
                    } else if (msgCtx->ocarinaStaff->state == OCARINA_SONG_EVAN_PART2) {
                        play_sound(NA_SE_SY_CORRECT_CHIME);
                        AudioOcarina_SetOcarinaDisableTimer(0, 20);
                        Message_CloseTextbox(play);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_PLAYED_FULL_EVAN_SONG;
                    } else if ((msgCtx->ocarinaStaff->state == OCARINA_SONG_SCARECROW_SPAWN) ||
                               (msgCtx->ocarinaStaff->state == OCARINA_SONG_INVERTED_TIME) ||
                               (msgCtx->ocarinaStaff->state == OCARINA_SONG_DOUBLE_TIME) ||
                               (msgCtx->ocarinaStaff->state == OCARINA_SONG_GORON_LULLABY_INTRO) ||
                               CHECK_QUEST_ITEM(QUEST_SONG_SONATA + msgCtx->ocarinaStaff->state)) {
                        sLastPlayedSong = msgCtx->ocarinaStaff->state;
                        msgCtx->lastPlayedSong = msgCtx->ocarinaStaff->state;
                        msgCtx->songPlayed = msgCtx->ocarinaStaff->state;
                        msgCtx->msgMode = MSGMODE_E;
                        msgCtx->stateTimer = 20;

                        if (msgCtx->ocarinaAction == OCARINA_ACTION_CHECK_NOTIME) {
                            if ((msgCtx->ocarinaStaff->state <= OCARINA_SONG_SARIAS) ||
                                (msgCtx->ocarinaStaff->state == OCARINA_SONG_SCARECROW_SPAWN)) {
                                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                                play_sound(NA_SE_SY_OCARINA_ERROR);
                                msgCtx->msgMode = MSGMODE_OCARINA_STARTING;
                            } else {
                                Message_ContinueTextbox(play, 0x1B5B);
                                msgCtx->msgMode = MSGMODE_SONG_PLAYED;
                                msgCtx->textBoxType = 3;
                                msgCtx->stateTimer = 10;
                                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                                Interface_SetHudVisibility(1);
                            }
                        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_CHECK_SCARECROW_SPAWN) {
                            if (msgCtx->ocarinaStaff->state <= OCARINA_SONG_STORMS) {
                                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                                play_sound(NA_SE_SY_OCARINA_ERROR);
                                msgCtx->stateTimer = 10;
                                msgCtx->msgMode = MSGMODE_OCARINA_FAIL;
                            } else {
                                Message_ContinueTextbox(play, 0x1B5B);
                                msgCtx->msgMode = MSGMODE_SONG_PLAYED;
                                msgCtx->textBoxType = 3;
                                msgCtx->stateTimer = 10;
                                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                                Interface_SetHudVisibility(1);
                            }
                        } else if (msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY) {
                            Message_ContinueTextbox(play, 0x1B5B);
                            msgCtx->msgMode = MSGMODE_SONG_PLAYED;
                            msgCtx->textBoxType = 3;
                            msgCtx->stateTimer = 10;
                            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                        } else {
                            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                        }
                        Interface_SetHudVisibility(1);
                    } else {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        msgCtx->msgMode = MSGMODE_OCARINA_STARTING;
                    }
                } else if (msgCtx->ocarinaStaff->state == OCARINA_SONG_TERMINA_WALL) {
                    Message_CloseTextbox(play);
                    play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                    SET_EVENTINF(EVENTINF_32);
                    play_sound(NA_SE_SY_CORRECT_CHIME);
                    AudioOcarina_SetOcarinaDisableTimer(0, 20);
                } else if (msgCtx->ocarinaStaff->state == 0xFF) {
                    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_52_10)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        msgCtx->stateTimer = 10;
                        msgCtx->msgMode = MSGMODE_OCARINA_FAIL;
                    } else {
                        AudioOcarina_SetSongStartingPos();
                        AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                        AudioOcarina_StartAtSongStartingPos((msgCtx->ocarinaAvailableSongs + 0x80000) | 0xC0000000);
                    }
                }
                if ((msgCtx->ocarinaAction != OCARINA_ACTION_FREE_PLAY) &&
                    (msgCtx->ocarinaAction != OCARINA_ACTION_CHECK_NOTIME)) {
                    Message_DrawText(play, &gfx);
                }
                break;

            case MSGMODE_E:
            case MSGMODE_SONG_PROMPT_SUCCESS:
            case MSGMODE_22:
            case MSGMODE_SCARECROW_SPAWN_RECORDING_DONE:
            case MSGMODE_34:
                Message_FlashOcarinaButtons();
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);

                    if (msgCtx->msgMode == MSGMODE_E) {
                        Message_ContinueTextbox(play, 0x1B5B);
                        msgCtx->msgMode = MSGMODE_SONG_PLAYED;
                        msgCtx->textBoxType = 3;
                        msgCtx->stateTimer = 1;
                    } else if (msgCtx->msgMode == MSGMODE_SONG_PROMPT_SUCCESS) {
                        Message_ContinueTextbox(play, 0x1B5B);
                        msgCtx->msgMode = MSGMODE_SONG_PLAYED;
                        msgCtx->textBoxType = 3;
                        msgCtx->stateTimer = 1;
                    } else if (msgCtx->msgMode == MSGMODE_22) {
                        msgCtx->msgMode = MSGMODE_23;
                        play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                        msgCtx->textBoxType = 0;
                    } else if (msgCtx->msgMode == MSGMODE_34) {
                        if (msgCtx->songPlayed == OCARINA_SONG_TERMINA_WALL) {
                            Message_CloseTextbox(play);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                            play_sound(NA_SE_SY_CORRECT_CHIME);
                        } else {
                            Message_CloseTextbox(play);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                        }
                    } else {
                        Message_CloseTextbox(play);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                    }
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_OCARINA_FAIL:
            case MSGMODE_SONG_PROMPT_FAIL:
                Message_DrawText(play, &gfx);
                // fallthrough
            case MSGMODE_OCARINA_FAIL_NO_TEXT:
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    D_801C6A94 = 1;
                    if (msgCtx->msgMode == MSGMODE_SONG_PROMPT_FAIL) {
                        Message_ContinueTextbox(play, 0x1B89);
                        Message_Decode(play);
                        msgCtx->msgMode = MSGMODE_SONG_PROMPT_NOTES_DROP;
                    } else {
                        msgCtx->msgMode = MSGMODE_OCARINA_NOTES_DROP;
                    }
                }
                break;

            case MSGMODE_OCARINA_NOTES_DROP:
            case MSGMODE_SONG_PROMPT_NOTES_DROP:
                for (i = 0; i < 5; i++) {
                    msgCtx->ocarinaButtonsPosY[i] += D_801C6A94;
                }
                D_801C6A94 += D_801C6A94;
                if (D_801C6A94 >= 0x226) {
                    Message_ResetOcarinaButtonAlphas();
                    if (msgCtx->msgMode == MSGMODE_SONG_PROMPT_NOTES_DROP) {
                        msgCtx->msgMode = MSGMODE_OCARINA_AWAIT_INPUT;
                        msgCtx->stateTimer = 10;
                    } else {
                        msgCtx->msgMode = MSGMODE_OCARINA_STARTING;
                    }
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                break;

            case MSGMODE_SONG_PLAYED:
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                    Message_Decode(play);
                    msgCtx->msgMode = MSGMODE_SETUP_DISPLAY_SONG_PLAYED;
                    msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();
                    msgCtx->ocarinaStaff->pos = 0;
                    sOcarinaButtonIndexBufPos = 0;
                    Message_ResetOcarinaButtonState(play);
                    Message_SpawnSongEffect(play);
                }
                break;

            case MSGMODE_SETUP_DISPLAY_SONG_PLAYED:
                Message_DrawText(play, &gfx);
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);

                if ((msgCtx->ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
                    (msgCtx->ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) {
                    AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                    AudioOcarina_SetPlaybackSong(msgCtx->ocarinaAction - OCARINA_ACTION_SCARECROW_LONG_RECORDING, 1);
                } else {
                    AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                    AudioOcarina_SetPlaybackSong((u8)msgCtx->songPlayed + 1, 1);
                    if (msgCtx->songPlayed != OCARINA_SONG_SCARECROW_SPAWN) {
                        func_801A3000((u16)sOcarinaSongFanfares[msgCtx->songPlayed],
                                      (u8)sOcarinaSongFanfareIoData[CUR_FORM]);
                        AudioSfx_MuteBanks(0x20);
                    }
                }
                play->msgCtx.ocarinaMode = OCARINA_MODE_ACTIVE;
                if (msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY) {
                    msgCtx->ocarinaAction = OCARINA_ACTION_FREE_PLAY_DONE;
                }
                if (msgCtx->ocarinaAction == OCARINA_ACTION_CHECK_NOTIME) {
                    msgCtx->ocarinaAction = OCARINA_ACTION_CHECK_NOTIME_DONE;
                }
                sOcarinaButtonIndexBufPos = 0;
                msgCtx->msgMode = MSGMODE_DISPLAY_SONG_PLAYED;
                break;

            case MSGMODE_DISPLAY_SONG_PLAYED_TEXT_BEGIN:
                if (msgCtx->songPlayed == OCARINA_SONG_SCARECROW_SPAWN) {
                    Message_ContinueTextbox(play, 0x1B6B);
                } else {
                    Message_ContinueTextbox(play, 0x1B72 + msgCtx->songPlayed);
                }
                Message_Decode(play);
                msgCtx->msgMode = MSGMODE_16;
                msgCtx->stateTimer = 20;
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_16:
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    msgCtx->msgMode = MSGMODE_17;
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_17:
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                Message_ResetOcarinaButtonState(play);
                msgCtx->msgMode = MSGMODE_18;
                msgCtx->stateTimer = 2;
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_18:
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    Message_CloseTextbox(play);
                    if (msgCtx->songPlayed == OCARINA_SONG_EPONAS) {
                        D_801BDAA4 = 1;
                    }

                    if (msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY_DONE) {
                        if (sLastPlayedSong == OCARINA_SONG_ELEGY) {
                            if ((play->sceneId == SCENE_F40) || (play->sceneId == SCENE_F41) ||
                                (play->sceneId == SCENE_IKANAMAE) || (play->sceneId == SCENE_CASTLE) ||
                                (play->sceneId == SCENE_IKNINSIDE) || (play->sceneId == SCENE_IKANA) ||
                                (play->sceneId == SCENE_INISIE_N) || (play->sceneId == SCENE_INISIE_R) ||
                                (play->sceneId == SCENE_INISIE_BS) || (play->sceneId == SCENE_RANDOM) ||
                                (play->sceneId == SCENE_REDEAD) || (play->sceneId == SCENE_TOUGITES)) {
                                play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                            } else {
                                sLastPlayedSong = 0xFF;
                                Message_StartTextbox(play, 0x1B95, NULL);
                                play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_RESTRICTED_SONG;
                            }
                        } else {
                            play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                            if (msgCtx->songPlayed == OCARINA_SONG_SCARECROW_SPAWN) {
                                play->msgCtx.ocarinaMode = OCARINA_MODE_PLAYED_SCARECROW_SPAWN;
                            }
                        }
                    } else if (msgCtx->ocarinaAction >= OCARINA_ACTION_CHECK_SONATA) {
                        if ((OCARINA_ACTION_CHECK_SONATA + msgCtx->songPlayed) == msgCtx->ocarinaAction) {
                            play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                        } else {
                            play->msgCtx.ocarinaMode = msgCtx->songPlayed - 1;
                        }
                    } else if ((OCARINA_ACTION_PROMPT_SONATA + msgCtx->songPlayed) == msgCtx->ocarinaAction) {
                        play->msgCtx.ocarinaMode = OCARINA_MODE_EVENT;
                    } else {
                        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                    }
                }
                break;

            case MSGMODE_19:
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    func_80152CAC(play);
                    sOcarinaButtonIndexBufPos = 0;
                    msgCtx->msgMode = MSGMODE_SONG_DEMONSTRATION;
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_DISPLAY_SONG_PLAYED:
            case MSGMODE_SONG_DEMONSTRATION:
                msgCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                if (msgCtx->ocarinaStaff->state == 0) {
                    if ((msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART1_SECOND_HALF) ||
                        (msgCtx->ocarinaAction == OCARINA_ACTION_DEMONSTRATE_EVAN_PART2_SECOND_HALF)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                    }
                    if ((msgCtx->ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
                        (msgCtx->ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        Message_CloseTextbox(play);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                    } else if (msgCtx->msgMode == MSGMODE_DISPLAY_SONG_PLAYED) {
                        msgCtx->msgMode = MSGMODE_DISPLAY_SONG_PLAYED_TEXT_BEGIN;
                    } else {
                        msgCtx->msgMode = MSGMODE_SONG_DEMONSTRATION_DONE;
                    }
                } else {
                    if ((sOcarinaButtonIndexBufPos != 0) && (msgCtx->ocarinaStaff->pos == 1)) {
                        sOcarinaButtonIndexBufPos = 0;
                    }

                    if (((u32)msgCtx->ocarinaStaff->pos != 0) &&
                        (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1))) {
                        msgCtx->lastOcarinaButtonIndex = sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos - 1] =
                            msgCtx->ocarinaStaff->buttonIndex;
                        sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos] = OCARINA_BTN_INVALID;
                        sOcarinaButtonIndexBufPos++;
                    }
                }
                // fallthrough
            case MSGMODE_SONG_DEMONSTRATION_DONE:
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_SONG_PROMPT:
            case MSGMODE_33:
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();

                if (((u32)msgCtx->ocarinaStaff->pos != 0) &&
                    (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1))) {
                    msgCtx->lastOcarinaButtonIndex = sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos - 1] =
                        msgCtx->ocarinaStaff->buttonIndex;
                    sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos] = OCARINA_BTN_INVALID;
                    sOcarinaButtonIndexBufPos++;
                }

                if (msgCtx->ocarinaStaff->state <= OCARINA_SONG_SCARECROW_SPAWN) {
                    if ((msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) ||
                        (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                        msgCtx->songPlayed = msgCtx->ocarinaStaff->state;
                        msgCtx->msgMode = MSGMODE_22;
                    } else {
                        msgCtx->songPlayed = msgCtx->ocarinaStaff->state;
                        msgCtx->msgMode = MSGMODE_SONG_PROMPT_SUCCESS;
                        if (msgCtx->ocarinaStaff->state == OCARINA_SONG_GORON_LULLABY_INTRO) {
                            Item_Give(play, ITEM_SONG_LULLABY_INTRO);
                        } else if (!((msgCtx->ocarinaAction >= OCARINA_ACTION_PROMPT_WIND_FISH_HUMAN) &&
                                     (msgCtx->ocarinaAction <= OCARINA_ACTION_PROMPT_WIND_FISH_DEKU)) &&
                                   (msgCtx->ocarinaStaff->state != OCARINA_SONG_NEW_WAVE)) {
                            Item_Give(play,
                                      (gOcarinaSongItemMap[msgCtx->ocarinaStaff->state] + ITEM_SONG_SONATA) & 0xFF);
                        }
                    }
                    msgCtx->stateTimer = 20;
                    play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                } else if (msgCtx->ocarinaStaff->state == OCARINA_SONG_TERMINA_WALL) {
                    msgCtx->songPlayed = msgCtx->ocarinaStaff->state;
                    msgCtx->msgMode = MSGMODE_34;
                    Item_Give(play, (gOcarinaSongItemMap[msgCtx->ocarinaStaff->state] + ITEM_SONG_SONATA) & 0xFF);
                    msgCtx->stateTimer = 20;
                    AudioOcarina_SetOcarinaDisableTimer(0, 20);
                    play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                } else if (msgCtx->ocarinaStaff->state == 0xFF) {
                    play_sound(NA_SE_SY_OCARINA_ERROR);
                    msgCtx->stateTimer = 10;
                    if (msgCtx->msgMode == MSGMODE_SONG_PROMPT) {
                        msgCtx->msgMode = MSGMODE_SONG_PROMPT_FAIL;
                    } else {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                        Message_CloseTextbox(play);
                    }
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_OCARINA_AWAIT_INPUT:
                Message_DrawText(play, &gfx);
                if ((msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) ||
                    (msgCtx->ocarinaAction == OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                    msgCtx->stateTimer--;
                    if (msgCtx->stateTimer == 0) {
                        msgCtx->msgMode = MSGMODE_21;
                        msgCtx->textBoxType = 0;
                    }
                }
                break;

            case MSGMODE_SCARECROW_LONG_RECORDING_START:
                AudioOcarina_SetRecordingState(OCARINA_RECORD_SCARECROW_LONG);
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
                msgCtx->ocarinaStaff = AudioOcarina_GetRecordingStaff();
                msgCtx->ocarinaStaff->pos = 0;
                sOcarinaButtonIndexBufPos = 0;
                sOcarinaButtonIndexBufLen = 0;
                Message_ResetOcarinaButtonState(play);
                msgCtx->msgMode = MSGMODE_SCARECROW_LONG_RECORDING_ONGOING;
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_SCARECROW_LONG_RECORDING_ONGOING:
                msgCtx->ocarinaStaff = AudioOcarina_GetRecordingStaff();

                if (((u32)msgCtx->ocarinaStaff->pos != 0) &&
                    (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1))) {

                    if (sOcarinaButtonIndexBufLen >= 8) {
                        for (buttonIndexPos = sOcarinaButtonIndexBufLen - 8, i = 0; i < 8; i++, buttonIndexPos++) {
                            sOcarinaButtonIndexBuf[buttonIndexPos] = sOcarinaButtonIndexBuf[buttonIndexPos + 1];
                        }
                        sOcarinaButtonIndexBufLen--;
                    }

                    msgCtx->lastOcarinaButtonIndex = sOcarinaButtonIndexBuf[sOcarinaButtonIndexBufLen] =
                        msgCtx->ocarinaStaff->buttonIndex;
                    sOcarinaButtonIndexBufLen++;
                    sOcarinaButtonIndexBuf[sOcarinaButtonIndexBufLen] = OCARINA_BTN_INVALID;
                    sOcarinaButtonIndexBufPos++;
                    if (msgCtx->ocarinaStaff) {}
                    if (msgCtx->ocarinaStaff->pos == 8) {
                        sOcarinaButtonIndexBufPos = 0;
                    }
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_SCARECROW_LONG_DEMONSTRATION:
            case MSGMODE_SCARECROW_SPAWN_DEMONSTRATION:
                msgCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();

                if (((u32)msgCtx->ocarinaStaff->pos != 0) &&
                    (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1))) {
                    if (sOcarinaButtonIndexBufLen >= 8) {
                        for (buttonIndexPos = sOcarinaButtonIndexBufLen - 8, i = 0; i < 8; i++, buttonIndexPos++) {
                            sOcarinaButtonIndexBuf[buttonIndexPos] = sOcarinaButtonIndexBuf[buttonIndexPos + 1];
                        }
                        sOcarinaButtonIndexBufLen--;
                    }
                    sOcarinaButtonIndexBuf[sOcarinaButtonIndexBufLen] = msgCtx->ocarinaStaff->buttonIndex;
                    sOcarinaButtonIndexBufLen++;
                    sOcarinaButtonIndexBuf[sOcarinaButtonIndexBufLen] = OCARINA_BTN_INVALID;
                    sOcarinaButtonIndexBufPos++;
                    if (msgCtx->ocarinaStaff->pos == 8) {
                        sOcarinaButtonIndexBufLen = sOcarinaButtonIndexBufPos = 0;
                    }
                }

                if (msgCtx->stateTimer == 0) {
                    if (msgCtx->ocarinaStaff->state == 0) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_11;
                        Message_CloseTextbox(play);
                    }
                } else {
                    msgCtx->stateTimer--;
                }
                break;

            case MSGMODE_SCARECROW_SPAWN_RECORDING_START:
                AudioOcarina_SetRecordingState(OCARINA_RECORD_SCARECROW_SPAWN);
                AudioOcarina_SetInstrument(sPlayerFormOcarinaInstruments[CUR_FORM]);
                msgCtx->msgMode = MSGMODE_SCARECROW_SPAWN_RECORDING_ONGOING;
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_SCARECROW_SPAWN_RECORDING_ONGOING:
                msgCtx->ocarinaStaff = AudioOcarina_GetRecordingStaff();
                if ((u32)msgCtx->ocarinaStaff->pos != 0) {
                    if (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1)) {
                        msgCtx->lastOcarinaButtonIndex = sOcarinaButtonIndexBuf[sOcarinaButtonIndexBufPos] =
                            msgCtx->ocarinaStaff->buttonIndex;
                        sOcarinaButtonIndexBufPos++;
                        sOcarinaButtonIndexBuf[sOcarinaButtonIndexBufPos] = OCARINA_BTN_INVALID;
                    }
                }

                if (msgCtx->ocarinaStaff->state == 0) {
                    msgCtx->stateTimer = 20;
                    gSaveContext.save.scarecrowSpawnSongSet = true;
                    msgCtx->msgMode = MSGMODE_SCARECROW_SPAWN_RECORDING_DONE;
                    play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                    Lib_MemCpy(gSaveContext.save.scarecrowSpawnSong, gScarecrowSpawnSongPtr,
                               sizeof(gSaveContext.save.scarecrowSpawnSong));
                    for (i = 0; i < ARRAY_COUNT(gSaveContext.save.scarecrowSpawnSong); i++) {
                        // osSyncPrintf("%d, ", gSaveContext.scarecrowSpawnSong[i]);
                    }
                } else if (msgCtx->ocarinaStaff->state == 0xFF) {
                    AudioOcarina_SetRecordingState(OCARINA_RECORD_OFF);
                    play_sound(NA_SE_SY_OCARINA_ERROR);
                    Message_CloseTextbox(play);
                    msgCtx->msgMode = MSGMODE_SCARECROW_SPAWN_RECORDING_FAILED;
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_SCARECROW_SPAWN_RECORDING_FAILED:
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                Message_StartTextbox(play, 0x1647, NULL);
                play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                break;

            case MSGMODE_2F:
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();
                msgCtx->ocarinaStaff->pos = 0;
                sOcarinaButtonIndexBufPos = 0;
                play->msgCtx.ocarinaMode = OCARINA_MODE_ACTIVE;
                Message_ResetOcarinaButtonState(play);
                AudioOcarina_StartDefault(msgCtx->ocarinaAvailableSongs | 0xC0000000);
                msgCtx->msgMode = MSGMODE_30;
                break;

            case MSGMODE_30:
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();
                if (((u32)msgCtx->ocarinaStaff->pos != 0) &&
                    (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1))) {
                    msgCtx->lastOcarinaButtonIndex = msgCtx->ocarinaStaff->buttonIndex;
                    msgCtx->ocarinaStaff->pos = 0;
                    sOcarinaButtonIndexBufPos = 0;
                    Message_ResetOcarinaButtonState(play);
                    msgCtx->msgMode = MSGMODE_31;
                }
                break;

            case MSGMODE_35:
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();
                msgCtx->ocarinaStaff->pos = 0;
                sOcarinaButtonIndexBufPos = 0;
                play->msgCtx.ocarinaMode = OCARINA_MODE_ACTIVE;
                Message_ResetOcarinaButtonState(play);
                sOcarinaButtonFlashColorIndex = 1;
                sOcarinaButtonFlashTimer = 3;
                AudioOcarina_StartWithSongNoteLengths(
                    (1 << ((msgCtx->ocarinaAction - OCARINA_ACTION_TIMED_PROMPT_SONATA) & 0xFFFF)) | 0x80000000);
                msgCtx->msgMode = MSGMODE_36;
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_36:
                msgCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();

                if ((u32)msgCtx->ocarinaStaff->pos != 0) {
                    if (sOcarinaButtonIndexBufPos == (msgCtx->ocarinaStaff->pos - 1)) {
                        sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos - 1] = msgCtx->ocarinaStaff->buttonIndex;
                        sOcarinaButtonIndexBuf[msgCtx->ocarinaStaff->pos] = OCARINA_BTN_INVALID;
                        sOcarinaButtonIndexBufPos++;
                    }
                }

                if (msgCtx->ocarinaStaff->state <= OCARINA_SONG_SCARECROW_SPAWN) {
                    msgCtx->songPlayed = msgCtx->ocarinaStaff->state;
                    msgCtx->msgMode = MSGMODE_37;
                    Item_Give(play, (gOcarinaSongItemMap[msgCtx->ocarinaStaff->state] + ITEM_SONG_SONATA) & 0xFF);
                    msgCtx->stateTimer = 20;
                    play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                } else if (msgCtx->ocarinaStaff->state == 0xFF) {
                    ocarinaError = func_8019B5AC();
                    if (ocarinaError == OCARINA_ERROR_2) {
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        D_801C6A94 = 1;
                        msgCtx->msgMode = MSGMODE_3B;
                    } else if (ocarinaError == OCARINA_ERROR_3) {
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        D_801C6A94 = 1;
                        msgCtx->msgMode = MSGMODE_3E;
                    } else {
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        D_801C6A94 = 1;
                        msgCtx->msgMode = MSGMODE_38;
                    }
                }
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_37:
                Message_FlashOcarinaButtons();
                Message_DrawText(play, &gfx);
                break;

            case MSGMODE_38:
            case MSGMODE_3B:
            case MSGMODE_3E:
                // notes drop
                for (i = 0; i < 5; i++) {
                    msgCtx->ocarinaButtonsPosY[i] += D_801C6A94;
                }

                D_801C6A94 += D_801C6A94;
                if (D_801C6A94 >= 0x226) {
                    Message_ResetOcarinaButtonAlphas();
                    msgCtx->textBoxType = 0;
                    msgCtx->textboxColorRed = msgCtx->textboxColorGreen = msgCtx->textboxColorBlue = 0;
                    msgCtx->stateTimer = 3;
                    msgCtx->msgMode++;
                }
                break;

            case MSGMODE_39:
            case MSGMODE_3C:
            case MSGMODE_3F:
                msgCtx->stateTimer--;
                if (msgCtx->stateTimer == 0) {
                    msgCtx->msgMode++;
                }
                break;

            case MSGMODE_TEXT_DONE:
                switch (msgCtx->textboxEndType) {
                    case TEXTBOX_ENDTYPE_60:
                        temp_v0_33 = msgCtx->unk120BE;
                        temp = msgCtx->unk11FFA + (msgCtx->unk11FFC * temp_v0_33);
                        func_80147F18(play, &gfx,
                                      msgCtx->unk11F1A[temp_v0_33] +
                                          (s32)(16.0f * msgCtx->textCharScale * (msgCtx->unk120C2 + 5)) - 1,
                                      temp);
                        func_80148D64(play);
                        break;

                    case TEXTBOX_ENDTYPE_61:
                        temp_v0_33 = msgCtx->unk120BE;
                        temp = msgCtx->unk11FFA + (msgCtx->unk11FFC * temp_v0_33);
                        func_80148558(play, &gfx,
                                      msgCtx->unk11F1A[temp_v0_33] + (s32)(16.0f * msgCtx->textCharScale * 5.0f) - 1,
                                      temp);
                        func_80149048(play);
                        break;

                    case TEXTBOX_ENDTYPE_62:
                        temp_v0_33 = msgCtx->unk120BE;
                        temp = msgCtx->unk11FFA + (msgCtx->unk11FFC * temp_v0_33);
                        func_80147F18(play, &gfx,
                                      msgCtx->unk11F1A[temp_v0_33] +
                                          (s32)(16.0f * msgCtx->textCharScale * (msgCtx->unk120C2 + 5)) - 1,
                                      temp);
                        func_801491DC(play);
                        break;

                    case TEXTBOX_ENDTYPE_63:
                        temp_v0_33 = msgCtx->unk120BE;
                        temp = msgCtx->unk11FFA + (msgCtx->unk11FFC * temp_v0_33);
                        func_80147F18(play, &gfx,
                                      msgCtx->unk11F1A[temp_v0_33] +
                                          (s32)(16.0f * msgCtx->textCharScale * (msgCtx->unk120C2 + 5)) - 1,
                                      temp);
                        func_80149454(play);
                        break;

                    case TEXTBOX_ENDTYPE_64:
                        temp_v0_33 = msgCtx->unk120BE;
                        temp = msgCtx->unk11FFA + (msgCtx->unk11FFC * temp_v0_33);
                        func_80147F18(play, &gfx,
                                      msgCtx->unk11F1A[temp_v0_33] +
                                          (s32)(16.0f * msgCtx->textCharScale * (msgCtx->unk120C2 + 4)) - 6,
                                      temp);
                        func_801496C8(play);
                        break;

                    default:
                        break;
                }

                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                                  PRIMITIVE, 0);
                gDPSetEnvColor(gfx++, 0, 0, 0, 255);
                Message_DrawText(play, &gfx);

                switch (msgCtx->textboxEndType) {
                    case TEXTBOX_ENDTYPE_10:
                        func_80148CBC(play, &gfx, 1);
                        break;

                    case TEXTBOX_ENDTYPE_11:
                        func_80148CBC(play, &gfx, 2);
                        break;

                    case TEXTBOX_ENDTYPE_12:
                        func_80148CBC(play, &gfx, 1);
                        break;

                    case TEXTBOX_ENDTYPE_30:
                    case TEXTBOX_ENDTYPE_41:
                    case TEXTBOX_ENDTYPE_50:
                    case TEXTBOX_ENDTYPE_52:
                    case TEXTBOX_ENDTYPE_55:
                    case TEXTBOX_ENDTYPE_56:
                    case TEXTBOX_ENDTYPE_57:
                    case TEXTBOX_ENDTYPE_62:
                        break;

                    case TEXTBOX_ENDTYPE_40:
                    case TEXTBOX_ENDTYPE_60:
                    case TEXTBOX_ENDTYPE_61:
                    default:
                        Message_DrawTextboxIcon(play, &gfx, 0x9E,
                                                (s16)(D_801D03A8[msgCtx->textBoxType] + msgCtx->textboxYTarget));
                        break;

                    case TEXTBOX_ENDTYPE_42:
                        Message_DrawTextboxIcon(play, &gfx, 0x9E,
                                                (s16)(D_801D03A8[msgCtx->textBoxType] + msgCtx->textboxYTarget));
                        break;
                }
                break;

            case MSGMODE_SCENE_TITLE_CARD_FADE_IN_BACKGROUND:
            case MSGMODE_SCENE_TITLE_CARD_FADE_IN_TEXT:
            case MSGMODE_SCENE_TITLE_CARD_DISPLAYING:
            case MSGMODE_SCENE_TITLE_CARD_FADE_OUT_TEXT:
            case MSGMODE_SCENE_TITLE_CARD_FADE_OUT_BACKGROUND:
                Message_DrawSceneTitleCard(play, &gfx);
                break;

            case MSGMODE_21:
            case MSGMODE_23:
            case MSGMODE_31:
            case MSGMODE_3A:
            case MSGMODE_3D:
            case MSGMODE_40:
            case MSGMODE_TEXT_CLOSING:
            case MSGMODE_PAUSED:
                break;

            case MSGMODE_24:
            case MSGMODE_25:
            case MSGMODE_26:
            default:
                msgCtx->msgMode = MSGMODE_TEXT_DISPLAYING;
                break;
        }
    }
    Message_DrawOcarinaButtons(play, &gfx);
    *gfxP = gfx;
}

void Message_Draw(PlayState* play) {
    Gfx* nextDisplayList;
    Gfx* polyOpa;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    polyOpa = POLY_OPA_DISP;
    nextDisplayList = Graph_GfxPlusOne(polyOpa);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);

    if ((play->msgCtx.currentTextId != 0x5E6) || !Play_InCsMode(play)) {
        Message_DrawMain(play, &nextDisplayList);
    }

    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(polyOpa, nextDisplayList);
    POLY_OPA_DISP = nextDisplayList;
    CLOSE_DISPS(gfxCtx);
}

s16 sTextboxXPositions[] = {
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
};
s16 sTextboxLowerYPositions[] = {
    0x8E, 0x8E, 0x8E, 0x8E, 0xAE, 0x8E, 0x8E, 0x8E, 0x8E, 0x82, 0xAE, 0, 0x8E, 0x8E, 0x8E, 0x8E,
};
s16 sTextboxUpperYPositions[] = {
    0x26, 0x26, 0x26, 0x26, 0xAE, 0x26, 0x26, 0x26, 0x26, 0x3C, 0xAE, 0, 0x26, 0x26, 0x26, 0x26,
};
s16 sTextboxMidYPositions[] = {
    0x5A, 0x5A, 0x5A, 0x5A, 0xAE, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0xAE, 0, 0x5A, 0x5A, 0x5A, 0x5A,
};
s16 D_801D0448[] = { 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25 };
s16 D_801D045C[] = {
    0x1B91,
    0x1B90,
    0x1B8F,
};
s16 D_801D0464[] = {
    0x1B92,
    0x1B8E,
};

#ifdef NON_EQUIVALENT
// Down to a single compiler-managed stack variable
// Also need to verify the giant msgMode switch jump tables is correct
// i.e. some may need to break instead of going to default
// Also contains in-function data
void Message_Update(PlayState* play) {
    static u8 D_801D0468 = 0;
    MessageContext* msgCtx = &play->msgCtx;
    SramContext* sramCtx = &play->sramCtx; // Optional
    PauseContext* pauseCtx = &play->pauseCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Input* input = CONTROLLER1(&play->state);
    s16 var_v1;
    s16 sp50;
    u16 temp_v1_2;
    s16 sp4C;
    s16 sp4A;
    s16 sp48;
    s32 sp44;
    s32 sp40;
    u16 sp3E;
    s16 averageY;
    s32 pad;

    msgCtx->stickAdjX = input->rel.stick_x;
    msgCtx->stickAdjY = input->rel.stick_y;

    averageY = 0;

    // If stickAdj is held, set a delay to allow the cursor to read the next input.
    // The first delay is given a longer time than all subsequent delays.
    if (msgCtx->stickAdjX < -30) {
        if (msgCtx->stickXRepeatState == -1) {
            msgCtx->stickXRepeatTimer--;
            if (msgCtx->stickXRepeatTimer < 0) {
                // Allow the input to register and apply the delay for all subsequent repeated inputs
                msgCtx->stickXRepeatTimer = 2;
            } else {
                // Cancel the current input
                msgCtx->stickAdjX = 0;
            }
        } else {
            // Allow the input to register and apply the delay for the first repeated input
            msgCtx->stickXRepeatTimer = 10;
            msgCtx->stickXRepeatState = -1;
        }
    } else if (msgCtx->stickAdjX > 30) {
        if (msgCtx->stickXRepeatState == 1) {
            msgCtx->stickXRepeatTimer--;
            if (msgCtx->stickXRepeatTimer < 0) {
                // Allow the input to register and apply the delay for all subsequent repeated inputs
                msgCtx->stickXRepeatTimer = 2;
            } else {
                // Cancel the current input
                msgCtx->stickAdjX = 0;
            }
        } else {
            // Allow the input to register and apply the delay for the first repeated input
            msgCtx->stickXRepeatTimer = 10;
            msgCtx->stickXRepeatState = 1;
        }
    } else {
        msgCtx->stickXRepeatState = 0;
    }

    if (msgCtx->stickAdjY < -30) {
        if (msgCtx->stickYRepeatState == -1) {
            msgCtx->stickYRepeatTimer--;
            if (msgCtx->stickYRepeatTimer < 0) {
                // Allow the input to register and apply the delay for all subsequent repeated inputs
                msgCtx->stickYRepeatTimer = 2;
            } else {
                // Cancel the current input
                msgCtx->stickAdjY = 0;
            }
        } else {
            // Allow the input to register and apply the delay for the first repeated input
            msgCtx->stickYRepeatTimer = 10;
            msgCtx->stickYRepeatState = -1;
        }
    } else if (msgCtx->stickAdjY > 30) {
        if (msgCtx->stickYRepeatState == 1) {
            msgCtx->stickYRepeatTimer--;
            if (msgCtx->stickYRepeatTimer < 0) {
                // Allow the input to register and apply the delay for all subsequent repeated inputs
                msgCtx->stickYRepeatTimer = 2;
            } else {
                // Cancel the current input
                msgCtx->stickAdjY = 0;
            }
        } else {
            // Allow the input to register and apply the delay for the first repeated input
            msgCtx->stickYRepeatTimer = 10;
            msgCtx->stickYRepeatState = 1;
        }
    } else {
        msgCtx->stickYRepeatState = 0;
    }

    if (msgCtx->msgLength == 0) {
        return;
    }

    switch (msgCtx->msgMode) {
        case MSGMODE_TEXT_START:
            D_801C6A70++;

            var_v1 = 0;
            if ((D_801C6A70 >= 4) || ((msgCtx->talkActor == NULL) && (D_801C6A70 >= 2))) {
                var_v1 = 1;
            }
            if (var_v1) {
                if (msgCtx->talkActor != NULL) {
                    Actor_GetScreenPos(play, &GET_PLAYER(play)->actor, &sp50, &sp4C);
                    Actor_GetScreenPos(play, msgCtx->talkActor, &sp50, &sp4A);
                    if (sp4C >= sp4A) {
                        averageY = ((sp4C - sp4A) / 2) + sp4A;
                    } else {
                        averageY = ((sp4A - sp4C) / 2) + sp4C;
                    }
                } else {
                    msgCtx->textboxX = msgCtx->textboxXTarget;
                    msgCtx->textboxY = msgCtx->textboxYTarget;
                }

                var_v1 = msgCtx->textBoxType;

                if ((u32)msgCtx->textBoxPos == 0) {
                    if ((play->sceneId == SCENE_UNSET_4) || (play->sceneId == SCENE_UNSET_5) ||
                        (play->sceneId == SCENE_UNSET_6)) {
                        if (averageY < 0x64) {
                            msgCtx->textboxYTarget = sTextboxLowerYPositions[var_v1];
                        } else {
                            msgCtx->textboxYTarget = sTextboxUpperYPositions[var_v1];
                        }
                    } else {
                        if (averageY < 0xA0) {
                            msgCtx->textboxYTarget = sTextboxLowerYPositions[var_v1];
                        } else {
                            msgCtx->textboxYTarget = sTextboxUpperYPositions[var_v1];
                        }
                    }
                } else if (msgCtx->textBoxPos == 1) {
                    msgCtx->textboxYTarget = sTextboxUpperYPositions[var_v1];
                } else if (msgCtx->textBoxPos == 2) {
                    msgCtx->textboxYTarget = sTextboxMidYPositions[var_v1];
                } else if (msgCtx->textBoxPos == 7) {
                    msgCtx->textboxYTarget = 0x9E;
                } else {
                    msgCtx->textboxYTarget = sTextboxLowerYPositions[var_v1];
                }

                msgCtx->textboxXTarget = sTextboxXPositions[var_v1];

                if ((gSaveContext.options.language == LANGUAGE_JAP) && !msgCtx->textIsCredits) {
                    msgCtx->unk11FFE[0] = (s16)(msgCtx->textboxYTarget + 7);
                    msgCtx->unk11FFE[1] = (s16)(msgCtx->textboxYTarget + 0x19);
                    msgCtx->unk11FFE[2] = (s16)(msgCtx->textboxYTarget + 0x2B);
                } else {
                    msgCtx->unk11FFE[0] = (s16)(msgCtx->textboxYTarget + 0x14);
                    msgCtx->unk11FFE[1] = (s16)(msgCtx->textboxYTarget + 0x20);
                    msgCtx->unk11FFE[2] = (s16)(msgCtx->textboxYTarget + 0x2C);
                }

                if ((msgCtx->textBoxType == TEXTBOX_TYPE_4) || (msgCtx->textBoxType == TEXTBOX_TYPE_5)) {
                    msgCtx->msgMode = MSGMODE_TEXT_STARTING;
                    msgCtx->textboxX = msgCtx->textboxXTarget;
                    msgCtx->textboxY = msgCtx->textboxYTarget;
                    msgCtx->unk12008 = 0x100;
                    msgCtx->unk1200A = 0x40;
                    msgCtx->unk1200C = 0x200;
                    msgCtx->unk1200E = 0x200;
                    break;
                }

                Message_GrowTextbox(play);
                func_801A3FB4(0);
                msgCtx->stateTimer = 0;
                msgCtx->msgMode = MSGMODE_TEXT_BOX_GROWING;

                if (!pauseCtx->itemDescriptionOn) {
                    func_80150A84(play);
                }
            }
            break;

        case MSGMODE_TEXT_BOX_GROWING:
            Message_GrowTextbox(play);
            break;

        case MSGMODE_TEXT_STARTING:
            msgCtx->msgMode = MSGMODE_TEXT_NEXT_MSG;
            if (!pauseCtx->itemDescriptionOn) {
                if (msgCtx->currentTextId == 0xFF) {
                    func_8011552C(play, 0x12);
                } else if (msgCtx->currentTextId != 0xF8) {
                    func_8011552C(play, 0x10);
                }
            }
            break;

        case MSGMODE_TEXT_NEXT_MSG:
            Message_Decode(play);
            if (msgCtx->textFade) {
                Interface_SetHudVisibility(1);
            }
            if (D_801D0468 != 0) {
                msgCtx->textDrawPos = msgCtx->decodedTextLen;
                D_801D0468 = 0;
            }
            break;

        case MSGMODE_TEXT_CONTINUING:
            msgCtx->stateTimer--;
            if (msgCtx->stateTimer == 0) {
                Message_Decode(play);
            }
            break;

        case MSGMODE_TEXT_DISPLAYING:
            if (msgCtx->textBoxType != TEXTBOX_TYPE_4) {
                if (CHECK_BTN_ALL(input->press.button, BTN_B) && !msgCtx->textUnskippable) {
                    msgCtx->textboxSkipped = true;
                    msgCtx->textDrawPos = msgCtx->decodedTextLen;
                } else if (CHECK_BTN_ALL(input->press.button, BTN_A) && !msgCtx->textUnskippable) {

                    while (true) {
                        temp_v1_2 = msgCtx->decodedBuffer.wchar[msgCtx->textDrawPos];
                        if ((temp_v1_2 == 0x10) || (temp_v1_2 == 0x12) || (temp_v1_2 == 0x1B) || (temp_v1_2 == 0x1C) ||
                            (temp_v1_2 == 0x1D) || (temp_v1_2 == 0x19) || (temp_v1_2 == 0xE0) || (temp_v1_2 == 0xBF) ||
                            (temp_v1_2 == 0x15) || (temp_v1_2 == 0x1A)) {
                            break;
                        }
                        msgCtx->textDrawPos++;
                    }
                }
            } else if (CHECK_BTN_ALL(input->press.button, BTN_A) && (msgCtx->textUnskippable == 0)) {
                while (true) {
                    temp_v1_2 = msgCtx->decodedBuffer.wchar[msgCtx->textDrawPos];
                    if ((temp_v1_2 == 0x10) || (temp_v1_2 == 0x12) || (temp_v1_2 == 0x1B) || (temp_v1_2 == 0x1C) ||
                        (temp_v1_2 == 0x1D) || (temp_v1_2 == 0x19) || (temp_v1_2 == 0xE0) || (temp_v1_2 == 0xBF) ||
                        (temp_v1_2 == 0x15) || (temp_v1_2 == 0x1A)) {
                        break;
                    }
                    msgCtx->textDrawPos++;
                }
            }
            break;

        case MSGMODE_TEXT_AWAIT_INPUT:
            if (Message_ShouldAdvance(play)) {
                msgCtx->msgMode = MSGMODE_TEXT_DISPLAYING;
                msgCtx->textDrawPos++;
            }
            break;

        case MSGMODE_TEXT_DELAYED_BREAK:
            msgCtx->stateTimer--;
            if (msgCtx->stateTimer == 0) {
                msgCtx->msgMode = MSGMODE_TEXT_NEXT_MSG;
            }
            break;

        case MSGMODE_TEXT_AWAIT_NEXT:
            if (Message_ShouldAdvance(play)) {
                msgCtx->msgMode = MSGMODE_TEXT_NEXT_MSG;
                msgCtx->msgBufPos++;
            }
            break;

        case MSGMODE_TEXT_DONE:
            if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_50) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_52)) {
                msgCtx->stateTimer--;
                if ((msgCtx->stateTimer == 0) ||
                    ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_52) && Message_ShouldAdvance(play))) {
                    if (msgCtx->unk11F14 != 0xFFFF) {
                        play_sound(NA_SE_SY_MESSAGE_PASS);
                        Message_ContinueTextbox(play, msgCtx->unk11F14);
                    } else if (msgCtx->unk120B1 != 0) {
                        if (func_80151C9C(play) == 0) {
                            Message_CloseTextbox(play);
                        }
                    } else {
                        Message_CloseTextbox(play);
                    }
                }
            } else {
                if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_30) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_40) ||
                    (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_42) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_41)) {
                    return;
                }

                switch (msgCtx->textboxEndType) {
                    case TEXTBOX_ENDTYPE_55:
                        msgCtx->textColorAlpha += 20;
                        if (msgCtx->textColorAlpha >= 255) {
                            msgCtx->textColorAlpha = 255;
                            msgCtx->textboxEndType = TEXTBOX_ENDTYPE_56;
                        }
                        break;

                    case TEXTBOX_ENDTYPE_56:
                        msgCtx->stateTimer--;
                        if (msgCtx->stateTimer == 0) {
                            msgCtx->textboxEndType = TEXTBOX_ENDTYPE_57;
                        }
                        break;

                    case TEXTBOX_ENDTYPE_57:
                        msgCtx->textColorAlpha -= 20;
                        if (msgCtx->textColorAlpha <= 0) {
                            msgCtx->textColorAlpha = 0;
                            if (msgCtx->unk11F14 != 0xFFFF) {
                                play_sound(NA_SE_SY_MESSAGE_PASS);
                                Message_ContinueTextbox(play, msgCtx->unk11F14);
                                return;
                            }
                            if (msgCtx->unk120B1 != 0) {
                                if (func_80151C9C(play) == 0) {
                                    Message_CloseTextbox(play);
                                    return;
                                }
                            } else {
                                Message_CloseTextbox(play);
                                return;
                            }
                        }
                        break;

                    case TEXTBOX_ENDTYPE_10:
                        Message_HandleChoiceSelection(play, 1);
                        break;

                    case TEXTBOX_ENDTYPE_11:
                        Message_HandleChoiceSelection(play, 2);
                        break;

                    case TEXTBOX_ENDTYPE_12:
                        Message_HandleChoiceSelection(play, 1);
                        break;

                    default:
                        break;
                }

                if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) &&
                    (play->msgCtx.ocarinaMode == OCARINA_MODE_ACTIVE)) {
                    if (Message_ShouldAdvance(play)) {
                        if (msgCtx->choiceIndex == 0) {
                            play->msgCtx.ocarinaMode = OCARINA_MODE_WARP;
                        } else {
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                        }
                        Message_CloseTextbox(play);
                    }
                } else if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) &&
                           (play->msgCtx.ocarinaMode == OCARINA_MODE_PROCESS_SOT)) {
                    if (Message_ShouldAdvance(play)) {
                        if (msgCtx->choiceIndex == 0) {
                            func_8019F208();
                            msgCtx->msgMode = MSGMODE_NEW_CYCLE_0;
                            msgCtx->decodedTextLen -= 3;
                            msgCtx->unk120D6 = 0;
                            msgCtx->unk120D4 = 0;
                        } else {
                            func_8019F230();
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                            Message_CloseTextbox(play);
                        }
                    }
                } else if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) &&
                           (play->msgCtx.ocarinaMode == OCARINA_MODE_PROCESS_INVERTED_TIME)) {
                    if (Message_ShouldAdvance(play)) {
                        if (msgCtx->choiceIndex == 0) {
                            func_8019F208();
                            if (gSaveContext.save.daySpeed == 0) {
                                play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_INV_SOT_SLOW;
                                gSaveContext.save.daySpeed = -2;
                            } else {
                                play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_INV_SOT_FAST;
                                gSaveContext.save.daySpeed = 0;
                            }
                            Message_CloseTextbox(play);
                        } else {
                            func_8019F230();
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                            Message_CloseTextbox(play);
                        }
                    }
                } else if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) &&
                           (play->msgCtx.ocarinaMode == OCARINA_MODE_PROCESS_DOUBLE_TIME)) {
                    if (Message_ShouldAdvance(play)) {
                        if (msgCtx->choiceIndex == 0) {
                            func_8019F208();
                            if (gSaveContext.save.isNight != 0) {
                                gSaveContext.save.time = CLOCK_TIME(6, 0);
                            } else {
                                gSaveContext.save.time = CLOCK_TIME(18, 0);
                            }
                            play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_DOUBLE_SOT;
                            gSaveContext.timerStates[3] = 0;
                        } else {
                            func_8019F230();
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                        }
                        Message_CloseTextbox(play);
                    }
                } else if ((msgCtx->textboxEndType != TEXTBOX_ENDTYPE_10) || (pauseCtx->state != 0x18)) {
                    if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) &&
                        (play->msgCtx.ocarinaMode == OCARINA_MODE_1B)) {
                        if (Message_ShouldAdvance(play)) {
                            if (msgCtx->choiceIndex == 0) {
                                func_8019F208();
                                play->msgCtx.ocarinaMode = OCARINA_MODE_WARP_TO_ENTRANCE;
                            } else {
                                func_8019F230();
                                play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                            }
                            Message_CloseTextbox(play);
                        }
                    } else if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_60) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_61) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_11) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_50) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_52) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_55) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_56) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_57) ||
                               (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_62)) {
                        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_50) {}
                    } else if (pauseCtx->itemDescriptionOn) {
                        if ((input->rel.stick_x != 0) || (input->rel.stick_y != 0) ||
                            CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_B) ||
                            CHECK_BTN_ALL(input->press.button, BTN_START)) {
                            play_sound(NA_SE_SY_DECIDE);
                            Message_CloseTextbox(play);
                        }
                    } else if (play->msgCtx.ocarinaMode == OCARINA_MODE_PROCESS_RESTRICTED_SONG) {
                        if (Message_ShouldAdvanceSilent(play)) {
                            play_sound(NA_SE_SY_DECIDE);
                            Message_CloseTextbox(play);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                        }
                    } else if ((msgCtx->currentTextId != 0x2790) && Message_ShouldAdvanceSilent(play)) {
                        if (msgCtx->unk11F14 != 0xFFFF) {
                            play_sound(NA_SE_SY_MESSAGE_PASS);
                            Message_ContinueTextbox(play, msgCtx->unk11F14);
                        } else if ((msgCtx->unk120B1 == 0) || (func_80151C9C(play) != 1)) {
                            if (msgCtx->currentTextId == 0x579) {
                                gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                            }
                            play_sound(NA_SE_SY_DECIDE);
                            Message_CloseTextbox(play);
                        }
                    }
                }
            }
            break;

        case MSGMODE_TEXT_CLOSING:
            msgCtx->stateTimer--;
            if (msgCtx->stateTimer != 0) {
                break;
            }

            if (sLastPlayedSong == OCARINA_SONG_SOARING) {
                if (interfaceCtx->restrictions.songOfSoaring == 0) {
                    if ((func_8010A0A4(play) != 0) || (play->sceneId == SCENE_SECOM)) {
                        Message_StartTextbox(play, 0x1B93, NULL);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_1B;
                        sLastPlayedSong = 0xFF;
                    } else if (!msgCtx->ocarinaSongEffectActive) {
                        if (gSaveContext.save.playerData.owlActivationFlags != 0) {
                            pauseCtx->unk_2C8 = pauseCtx->pageIndex;
                            pauseCtx->unk_2CA = pauseCtx->cursorPoint[4];
                            pauseCtx->pageIndex = 0;
                            pauseCtx->state = 0x13;
                            func_800F4A10(play);
                            pauseCtx->pageIndex = 1;
                            sLastPlayedSong = 0xFF;
                            Message_CloseTextbox(play);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                            gSaveContext.prevHudVisibility = HUD_VISIBILITY_A_B;
                            func_80115844(play, 0x12);
                            Game_SetFramerateDivisor(&play->state, 2);
                            if (ShrinkWindow_Letterbox_GetSizeTarget() != 0) {
                                ShrinkWindow_Letterbox_SetSizeTarget(0);
                            }
                            func_801A3AEC(1);
                            break;
                        }
                        sLastPlayedSong = 0xFF;
                        Message_StartTextbox(play, 0xFB, NULL);
                        play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_RESTRICTED_SONG;
                    } else {
                        msgCtx->stateTimer = 1;
                    }
                } else {
                    sLastPlayedSong = 0xFF;
                    Message_StartTextbox(play, 0x1B95, NULL);
                    play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_RESTRICTED_SONG;
                }
                break;
            }

            if ((msgCtx->currentTextId == 0xC) || (msgCtx->currentTextId == 0xD) || (msgCtx->currentTextId == 0xC5) ||
                (msgCtx->currentTextId == 0xC6) || (msgCtx->currentTextId == 0xC7) ||
                (msgCtx->currentTextId == 0x2165) || (msgCtx->currentTextId == 0x2166) ||
                (msgCtx->currentTextId == 0x2167) || (msgCtx->currentTextId == 0x2168)) {
                gSaveContext.healthAccumulator = 20 * 0x10; // Refill 20 hearts
            }

            if ((play->csCtx.state == 0) && (gSaveContext.save.cutscene < 0xFFF0) &&
                ((play->activeCamId == 0) || ((play->transitionTrigger == 0) && (play->transitionMode == 0))) &&
                (play->msgCtx.ocarinaMode == OCARINA_MODE_END)) {
                if ((gSaveContext.prevHudVisibility == HUD_VISIBILITY_IDLE) ||
                    (gSaveContext.prevHudVisibility == HUD_VISIBILITY_NONE) ||
                    (gSaveContext.prevHudVisibility == HUD_VISIBILITY_NONE_ALT)) {
                    gSaveContext.prevHudVisibility = HUD_VISIBILITY_ALL;
                }
                gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            }

            if ((msgCtx->currentTextId >= 0x1BB2) && (msgCtx->currentTextId < 0x1BB7) && (play->actorCtx.flags & 2)) {
                Message_StartTextbox(play, 0x5E6, NULL);
            } else if (msgCtx->unk120B1 != 0) {
                if (func_80151C9C(play) == 0) {
                    msgCtx->stateTimer = 1;
                }
            } else {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = MSGMODE_NONE;
                msgCtx->currentTextId = 0;
                msgCtx->stateTimer = 0;
                gGameInfo->data[0x55F] = 0;
                if (pauseCtx->itemDescriptionOn) {
                    func_8011552C(play, 0x15);
                    pauseCtx->itemDescriptionOn = false;
                }
                if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_30) {
                    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_00;
                    play->msgCtx.ocarinaMode = OCARINA_MODE_WARP;
                } else {
                    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_00;
                }

                if (EQ_MAX_QUEST_HEART_PIECE_COUNT) {
                    RESET_HEART_PIECE_COUNT;
                    gSaveContext.save.playerData.healthCapacity += 0x10;
                    gSaveContext.save.playerData.health += 0x10;
                }

                if (msgCtx->ocarinaAction != OCARINA_ACTION_CHECK_NOTIME_DONE) {
                    if (sLastPlayedSong == OCARINA_SONG_TIME) {
                        if (interfaceCtx->restrictions.unk_312 == 0) {
                            Message_StartTextbox(play, 0x1B8A, NULL);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_SOT;
                        } else {
                            sLastPlayedSong = 0xFF;
                            Message_StartTextbox(play, 0x1B95, NULL);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_RESTRICTED_SONG;
                        }
                    } else if (sLastPlayedSong == OCARINA_SONG_INVERTED_TIME) {
                        if (interfaceCtx->restrictions.unk_314 == 0) {
                            if (gGameInfo->data[0xF] != 0) {
                                if (gSaveContext.save.daySpeed == 0) {
                                    Message_StartTextbox(play, 0x1B8C, NULL);
                                } else {
                                    Message_StartTextbox(play, 0x1B8D, NULL);
                                }
                                play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_INVERTED_TIME;
                            } else {
                                Message_StartTextbox(play, 0x1B8B, NULL);
                                play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                            }
                        } else {
                            sLastPlayedSong = 0xFF;
                            Message_StartTextbox(play, 0x1B95, NULL);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_RESTRICTED_SONG;
                        }
                    } else if (sLastPlayedSong == OCARINA_SONG_DOUBLE_TIME) {
                        if (interfaceCtx->restrictions.unk_313 == 0) {
                            if ((CURRENT_DAY != 3) || (gSaveContext.save.isNight == 0)) {
                                if (gSaveContext.save.isNight) {
                                    Message_StartTextbox(play, D_801D0464[CURRENT_DAY - 1], NULL);
                                } else {
                                    Message_StartTextbox(play, D_801D045C[CURRENT_DAY - 1], NULL);
                                }
                                play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_DOUBLE_TIME;
                            } else {
                                Message_StartTextbox(play, 0x1B94, NULL);
                                play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                            }
                        } else {
                            sLastPlayedSong = 0xFF;
                            Message_StartTextbox(play, 0x1B95, NULL);
                            play->msgCtx.ocarinaMode = OCARINA_MODE_PROCESS_RESTRICTED_SONG;
                        }
                    } else if ((msgCtx->ocarinaAction == OCARINA_ACTION_FREE_PLAY_DONE) &&
                               ((play->msgCtx.ocarinaMode == OCARINA_MODE_ACTIVE) ||
                                (play->msgCtx.ocarinaMode == OCARINA_MODE_EVENT) ||
                                (play->msgCtx.ocarinaMode == OCARINA_MODE_PLAYED_SCARECROW_SPAWN) ||
                                (play->msgCtx.ocarinaMode == OCARINA_MODE_PLAYED_FULL_EVAN_SONG))) {
                        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                        if (msgCtx->lastPlayedSong == 9) {
                            play->msgCtx.ocarinaMode = OCARINA_MODE_ACTIVE;
                        }
                    }
                    sLastPlayedSong = 0xFF;
                //! Fake
                dummy:;
                }
            }
            break;

        case MSGMODE_OCARINA_PLAYING:
            if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                Message_CloseTextbox(play);
            } else {
                msgCtx->lastOcarinaButtonIndex = OCARINA_BTN_INVALID;
            }
            break;

        case MSGMODE_OCARINA_AWAIT_INPUT:
            if ((msgCtx->ocarinaAction != OCARINA_ACTION_PROMPT_EVAN_PART1_SECOND_HALF) &&
                (msgCtx->ocarinaAction != OCARINA_ACTION_PROMPT_EVAN_PART2_SECOND_HALF)) {
                if (Message_ShouldAdvance(play)) {
                    Message_DisplayOcarinaStaff(play, msgCtx->ocarinaAction);
                }
            }
            break;

        case MSGMODE_SCARECROW_SPAWN_RECORDING_ONGOING:
            if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
                AudioOcarina_SetRecordingState(OCARINA_RECORD_OFF);
                play_sound(NA_SE_SY_OCARINA_ERROR);
                Message_CloseTextbox(play);
                msgCtx->msgMode = MSGMODE_SCARECROW_SPAWN_RECORDING_FAILED;
            } else {
                msgCtx->lastOcarinaButtonIndex = 0xFF;
            }
            break;

        case MSGMODE_SCENE_TITLE_CARD_FADE_IN_BACKGROUND:
            msgCtx->textboxColorAlphaCurrent += gGameInfo->data[0x589];
            if (msgCtx->textboxColorAlphaCurrent >= 255) {
                msgCtx->textboxColorAlphaCurrent = 255;
                msgCtx->msgMode = MSGMODE_SCENE_TITLE_CARD_FADE_IN_TEXT;
            }
            break;

        case MSGMODE_SCENE_TITLE_CARD_FADE_IN_TEXT:
            msgCtx->textColorAlpha += gGameInfo->data[0x589];
            if (msgCtx->textColorAlpha >= 255) {
                msgCtx->textColorAlpha = 255;
                msgCtx->msgMode = MSGMODE_SCENE_TITLE_CARD_DISPLAYING;
            }
            break;

        case MSGMODE_SCENE_TITLE_CARD_DISPLAYING:
            msgCtx->stateTimer--;
            if (msgCtx->stateTimer == 0) {
                msgCtx->msgMode = MSGMODE_SCENE_TITLE_CARD_FADE_OUT_TEXT;
            }
            break;

        case MSGMODE_SCENE_TITLE_CARD_FADE_OUT_TEXT:
            msgCtx->textColorAlpha -= gGameInfo->data[0x586];
            if (msgCtx->textColorAlpha <= 0) {
                msgCtx->textColorAlpha = 0;
                msgCtx->msgMode = MSGMODE_SCENE_TITLE_CARD_FADE_OUT_BACKGROUND;
            }
            break;

        case MSGMODE_SCENE_TITLE_CARD_FADE_OUT_BACKGROUND:
            msgCtx->textboxColorAlphaCurrent -= gGameInfo->data[0x586];
            if (msgCtx->textboxColorAlphaCurrent <= 0) {
                if ((msgCtx->currentTextId >= 0x1BB2) && (msgCtx->currentTextId < 0x1BB7) &&
                    (play->actorCtx.flags & 2)) {
                    Message_StartTextbox(play, 0x5E6, NULL);
                    Interface_SetHudVisibility(2);
                } else {
                    if (msgCtx->currentTextId >= 0x100) {
                        if (msgCtx && msgCtx && msgCtx) {}
                    }
                    msgCtx->textboxColorAlphaCurrent = 0;
                    msgCtx->msgLength = 0;
                    msgCtx->msgMode = MSGMODE_NONE;
                    msgCtx->currentTextId = 0;
                    msgCtx->stateTimer = 0;
                }
            }
            break;

        case MSGMODE_NEW_CYCLE_0:
            play->state.unk_A3 = 1;
            sp44 = gSaveContext.save.cutscene;
            sp3E = gSaveContext.save.time;
            sp40 = gSaveContext.save.day;

            Sram_SaveEndOfCycle(play);
            gSaveContext.timerStates[3] = 0;
            func_8014546C(sramCtx);

            gSaveContext.save.day = sp40;
            gSaveContext.save.time = sp3E;
            gSaveContext.save.cutscene = sp44;

            if (gSaveContext.fileNum != 0xFF) {
                func_80147008(sramCtx, D_801C67C8[gSaveContext.fileNum * 2], D_801C6818[gSaveContext.fileNum * 2]);
                func_80147020(sramCtx);
            }
            msgCtx->msgMode = MSGMODE_NEW_CYCLE_1;
            break;

        case MSGMODE_NEW_CYCLE_1:
            if (gSaveContext.fileNum != 0xFF) {
                play->state.unk_A3 = 1;
                if (sramCtx->status == 0) {
                    play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_SOT;
                    msgCtx->msgMode = MSGMODE_NEW_CYCLE_2;
                }
            } else {
                play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_SOT;
                msgCtx->msgMode = MSGMODE_NEW_CYCLE_2;
            }
            break;

        case MSGMODE_OWL_SAVE_0:
            play->state.unk_A3 = 1;
            gSaveContext.save.isOwlSave = true;
            Play_SaveCycleSceneFlags(&play->state);
            func_8014546C(sramCtx);

            if (gSaveContext.fileNum != 0xFF) {
                func_80147138(sramCtx, D_801C6840[gSaveContext.fileNum * 2], D_801C6850[gSaveContext.fileNum * 2]);
                func_80147150(sramCtx);
            }
            msgCtx->msgMode = MSGMODE_OWL_SAVE_1;
            break;

        case MSGMODE_OWL_SAVE_1:
            if (gSaveContext.fileNum != 0xFF) {
                play->state.unk_A3 = 1;
                if (sramCtx->status == 0) {
                    play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_SOT;
                    msgCtx->msgMode = MSGMODE_OWL_SAVE_2;
                }
            } else {
                play->msgCtx.ocarinaMode = OCARINA_MODE_APPLY_SOT;
                msgCtx->msgMode = MSGMODE_OWL_SAVE_2;
            }

            if (msgCtx->msgMode == MSGMODE_OWL_SAVE_2) {
                gSaveContext.gameMode = 4;
                play->transitionTrigger = TRANS_TRIGGER_START;
                play->transitionType = TRANS_TYPE_02;
                play->nextEntrance = ENTRANCE(CUTSCENE, 0);
                gSaveContext.save.cutscene = 0;
                gSaveContext.sceneLayer = 0;
            }
            break;

        case MSGMODE_9:
        case MSGMODE_PAUSED:
        case MSGMODE_NEW_CYCLE_2:
        case MSGMODE_OWL_SAVE_2:
            break;

        default:
            msgCtx->lastOcarinaButtonIndex = OCARINA_BTN_INVALID;
            break;
    }
}
#else
u8 D_801D0468 = 0;
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_Update.s")
#endif

void Message_SetTables(PlayState* play) {
    play->msgCtx.messageEntryTableNes = D_801C6B98;
    play->msgCtx.messageTableStaff = D_801CFB08;
}

void Message_Init(PlayState* play) {
    Font* font;
    MessageContext* msgCtx = &play->msgCtx;

    Message_SetTables(play);

    play->msgCtx.ocarinaMode = OCARINA_MODE_NONE;

    msgCtx->msgMode = MSGMODE_NONE;
    msgCtx->msgLength = 0;
    msgCtx->currentTextId = 0;
    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_00;
    msgCtx->choiceIndex = 0;
    msgCtx->ocarinaAction = msgCtx->textUnskippable = 0;
    msgCtx->textColorAlpha = 0xFF;

    View_Init(&msgCtx->view, play->state.gfxCtx);

    msgCtx->textboxSegment = THA_AllocEndAlign16(&play->state.heap, 0x13C00);

    font = &play->msgCtx.font;
    Font_LoadOrderedFont(&play->msgCtx.font);
    font->unk_11D88 = 0;

    msgCtx->textIsCredits = msgCtx->messageHasSetSfx = false;
    msgCtx->textboxSkipped = false;
    msgCtx->textFade = false;
    msgCtx->ocarinaAvailableSongs = 0;
    msgCtx->textboxX = 52;
    msgCtx->textboxY = 36;
    msgCtx->ocarinaSongEffectActive = false;
    msgCtx->unk120BE = 0;
    msgCtx->unk120C0 = 0;
    msgCtx->unk120C2 = 0;
    msgCtx->unk120C4 = 0;
    msgCtx->unk120C8 = 0;
    msgCtx->unk120CA = 0;
    msgCtx->unk120CC = 0;
    msgCtx->unk120CE = 0;
    msgCtx->unk120D0 = 0;
    msgCtx->unk120D2 = 0;
    msgCtx->unk120D4 = 0;
    msgCtx->unk120D6 = 0;
}
