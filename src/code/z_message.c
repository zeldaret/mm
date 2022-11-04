#include "global.h"
#include "z64shrink_window.h"
#include "z64view.h"
#include "message_data_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

#if 0

s16 D_801D02D8[15] = {
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE,  ACTOR_OCEFF_WIPE7, // Song of Time Effect, Song of Healing Effect
    ACTOR_OCEFF_WIPE2, ACTOR_OCEFF_WIPE6, // Epona's Song Effect, Song of Soaring Effect
    ACTOR_OCEFF_STORM, ACTOR_OCEFF_SPOT,  // Song of Storms Effect II [?], Sun's Song Effect
    ACTOR_OCEFF_WIPE, ACTOR_OCEFF_WIPE,   // Song of Time Effect, Song of Time Effect
    ACTOR_OCEFF_WIPE4                     // Scarecrow's Song Effect 
};
s32 D_801D02F8[15] = { 0,1,2,3,4,0,1,0,0,0,0,0,1,1,0 };

#endif

extern u16 D_801C6AB8[];
extern u16 D_801C6B28[];
extern s16 D_801D02D8[];
extern s32 D_801D02F8[];
extern s16 D_801F6B0C;
extern s16 D_801F6B0E;
extern s16 D_801F6B10;
extern s16 D_801F6B12;
extern s16 D_801F6B14;
extern s16 D_801F6B16;
extern s16 D_801F6B18;
extern s16 D_801F6B1A;
extern s16 D_801F6B1C;
extern s16 D_801F6B1E;
extern s16 D_801F6B20;
extern s16 D_801F6B22;
extern MessageTableEntry D_801C6B98[];
extern MessageTableEntry D_801CFB08[];
extern s16 D_801CFC78[15];

void func_80147520(void) {
    D_801CFC98 = 0xFF;
    D_801CFCA4[0] = D_801CFCA4[1] = D_801CFCA4[2] = D_801CFCA4[3] = D_801CFCA4[4] = D_801CFCA4[5] = D_801CFCA4[6] =
        D_801CFCA4[7] = D_801CFCA4[8] = 0;
}

void func_80147564(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->unk1204A[0] = 0xBD;
    msgCtx->unk1204A[1] = 0xB8;
    msgCtx->unk1204A[2] = 0xB3;
    msgCtx->unk1204A[3] = 0xAE;
    msgCtx->unk1204A[4] = 0xA9;
    func_80147520();
    D_801F6B0C = 0x50;
    D_801F6B10 = 0x96;
    D_801F6B0E = 0xFF;
    D_801F6B12 = 0xA;
    D_801F6B16 = 0xA;
    D_801F6B14 = 0xA;
    D_801F6B18 = 0xFF;
    D_801F6B1C = 0xFF;
    D_801F6B1A = 0x32;
    D_801F6B1E = 0xA;
    D_801F6B22 = 0xA;
    D_801F6B20 = 0xA;
}

s32 Message_ShouldAdvance(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->unk12020 == 0x10) || (msgCtx->unk12020 == 0x11)) {
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

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

void func_801477B4(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (play->msgCtx.msgLength != 0) {
        msgCtx->stateTimer = 2;
        msgCtx->msgMode = 0x43;
        msgCtx->unk12020 = 0;
        play_sound(NA_SE_PL_WALK_GROUND - SFX_FLAG);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147818.s")

#ifdef NON_MATCHING

extern s16 D_801CFD10[][3];
extern s16 D_801CFD1C[][3];
extern s16 D_801CFD28;
extern s16 D_801CFD2C;
extern s16 D_801CFD30;
extern s16 D_801CFD34;
extern s16 D_801CFD38;
extern s16 D_801CFD3C;
extern s16 D_801CFD40;
extern s16 D_801CFD44;

void func_80147F18(PlayState *play, Gfx **gfxp, s16 arg2, s16 arg3) {
    s16 sp44;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 sp4;
    Gfx *gfx;
    MessageContext *msgCtx = &play->msgCtx;
    s16 temp_a0;
    s16 temp_a2_3;
    s16 temp_a3;
    s16 temp_a3_2;
    s16 temp_t1;
    s16 temp_t1_3;
    s16 temp_t2;
    s16 temp_t2_2;
    s16 temp_t3;
    s16 temp_t3_2;
    s16 temp_t4;
    s16 temp_t4_2;
    s16 temp_t5;
    s16 temp_t6;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_t1_2;
    s32 temp_t7;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    void *temp_a0_3;
    void *temp_v1;
    s32 phi_v0;
    s32 phi_a0;
    s16 phi_a2;
    s32 phi_t1;
    s16 phi_t3;
    s16 phi_t4;
    s16 phi_t5;
    s32 phi_v0_2;
    s32 phi_v0_3;
    s32 phi_v0_4;
    s32 phi_v0_5;
    s32 phi_v0_6;

    gfx = *gfxp;
    if (msgCtx->unk12090 == 0) {
        temp_a0 = D_801CFD28;
        temp_t3 = D_801CFD10[D_801CFD38][0];
        temp_a2 = temp_a0 - temp_t3;

        temp_a2 = D_801CFD28 - D_801CFD10[D_801CFD38][0];
        if (temp_a2 < 0) {
            phi_v0_2 = -temp_a2;
        } else {
            phi_v0_2 = temp_a2;
        }
        temp_a3 = D_801CFD34;
        temp_t1 = D_801CFD2C;
        temp_t4 = D_801CFD10[D_801CFD38][1];
        temp_lo = phi_v0_2 / temp_a3;
        temp_a2_2 = temp_t1 - temp_t4;
        if (temp_a2_2 < 0) {
            phi_v0 = -temp_a2_2;
        } else {
            phi_v0 = temp_a2_2;
        }
        temp_a2_3 = D_801CFD30;
        temp_t2 = D_801CFD10[D_801CFD38][2];
        temp_t7 = temp_a2_3 - temp_t2;
        sp44 = (s16) (phi_v0 / (s32) temp_a3);
        if (temp_t7 < 0) {
            phi_v0_3 = -temp_t7;
        } else {
            phi_v0_3 = temp_t7;
        }
        if ((s32) temp_a0 >= (s32) temp_t3) {
            phi_a0 = (temp_a0 - (s16) temp_lo) << 0x10;
        } else {
            phi_a0 = (temp_a0 + (s16) temp_lo) << 0x10;
        }
        temp_a0_2 = phi_a0 >> 0x10;
        if ((s32) temp_t1 >= (s32) temp_t4) {
            phi_t1 = (temp_t1 - sp44) << 0x10;
        } else {
            phi_t1 = (temp_t1 + sp44) << 0x10;
        }
        temp_t1_2 = phi_t1 >> 0x10;
        if ((s32) temp_a2_3 >= (s32) temp_t2) {
            D_801CFD28 = (s16) temp_a0_2;
            phi_a2 = (s16) (temp_a2_3 - (s16) (phi_v0_3 / (s32) temp_a3));
        } else {
            D_801CFD28 = (s16) temp_a0_2;
            phi_a2 = (s16) (temp_a2_3 + (s16) (phi_v0_3 / (s32) temp_a3));
        }
        sp10 = (s32) temp_t3;
        temp_a0_3 = D_801CFD1C[D_801CFD38];
        temp_t3_2 = D_801CFD3C;
        temp_t6 = D_801CFD1C[D_801CFD38][0];
        temp_v1_2 = temp_t3_2 - temp_t6;
        sp4 = (s32) temp_t6;
        if (temp_v1_2 < 0) {
            D_801CFD30 = phi_a2;
            D_801CFD2C = (s16) temp_t1_2;
            sp8 = (s32) temp_t2;
            phi_v0_4 = -temp_v1_2;
        } else {
            D_801CFD30 = phi_a2;
            D_801CFD2C = (s16) temp_t1_2;
            sp8 = (s32) temp_t2;
            phi_v0_4 = temp_v1_2;
        }
        spC = (s32) temp_t4;
        temp_lo_2 = phi_v0_4 / (s32) temp_a3;
        temp_t4_2 = D_801CFD40;
        temp_t1_3 = D_801CFD1C[D_801CFD38][1];
        temp_v1_3 = temp_t4_2 - temp_t1_3;
        if (temp_v1_3 < 0) {
            phi_v0_5 = -temp_v1_3;
        } else {
            phi_v0_5 = temp_v1_3;
        }
        temp_lo_3 = phi_v0_5 / (s32) temp_a3;
        temp_t5 = D_801CFD44;
        temp_t2_2 = D_801CFD1C[D_801CFD38][2];
        temp_v1_4 = temp_t5 - temp_t2_2;
        if (temp_v1_4 < 0) {
            phi_v0_6 = -temp_v1_4;
        } else {
            phi_v0_6 = temp_v1_4;
        }
        if ((s32) temp_t3_2 >= sp4) {
            phi_t3 = (s16) (temp_t3_2 - (s16) temp_lo_2);
        } else {
            phi_t3 = (s16) (temp_t3_2 + (s16) temp_lo_2);
        }
        D_801CFD3C = phi_t3;
        if ((s32) temp_t4_2 >= (s32) temp_t1_3) {
            phi_t4 = (s16) (temp_t4_2 - (s16) temp_lo_3);
        } else {
            phi_t4 = (s16) (temp_t4_2 + (s16) temp_lo_3);
        }
        D_801CFD40 = phi_t4;
        if ((s32) temp_t5 >= (s32) temp_t2_2) {
            phi_t5 = (s16) (temp_t5 - (s16) (phi_v0_6 / (s32) temp_a3));
        } else {
            phi_t5 = (s16) (temp_t5 + (s16) (phi_v0_6 / (s32) temp_a3));
        }
        D_801CFD44 = phi_t5;
        temp_a3_2 = temp_a3 - 1;
        D_801CFD34 = temp_a3_2;
        if (temp_a3_2 == 0) {
            D_801CFD28 = (s16) sp10;
            D_801CFD2C = (s16) spC;
            D_801CFD30 = (s16) sp8;
            D_801CFD38 = D_801CFD38 ^ 1;
            D_801CFD34 = 0xC;
            D_801CFD3C = (s16) sp4;
            D_801CFD40 = temp_t1_3;
            D_801CFD44 = temp_t2_2;
        }

        gDPPipeSync(gfx++);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(gfx++, 0, 0, D_801CFD28, D_801CFD2C, D_801CFD30, 0x78);
        gDPFillRectangle(gfx++, (arg2 + 3), arg3, arg2 + 0x11, arg3 + 0xB);
        gDPFillRectangle(gfx++, arg2 + 6, arg3 - 2, arg2 + 0xE, arg3 + 0xD);
        gDPPipeSync(gfx++);
        *gfxp = gfx++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147F18.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148558.s")

// Function is actually matching
// but the static variable create a bss shift
// this variable seem to be part of sram_data.
// I'll try to decomp all equivalent functions
// before trying to prevent this bss reorder.
#ifdef NON_MATCHING
void func_80148B98(PlayState* play, u8 arg1) {
    static s16 held = 0;
    MessageContext* msgCtx = &play->msgCtx;
    Input* curInput = CONTROLLER1(&play->state);

    if ((curInput->rel.stick_y > 29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex--;
        if (msgCtx->choiceIndex > 128) {
            msgCtx->choiceIndex = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
        return;
    } else if ((curInput->rel.stick_y < -29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex++;
        if (msgCtx->choiceIndex > arg1) {
            msgCtx->choiceIndex = arg1;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
        return;
    } else {
        if (ABS_ALT(curInput->rel.stick_y) < 30) {
            held = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148B98.s")
#endif

void func_80148CBC(PlayState* play, UNK_PTR puParm2, u8 arg2) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->unk11FF4 = 0x30;
    if (arg2 == 1) {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[1 + msgCtx->choiceIndex];
    } else {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[msgCtx->choiceIndex];
    }
    func_80147818(play, puParm2, msgCtx->unk11FF4, msgCtx->unk11FF6);
}

// Function is actually matching
// but the static variable create a bss shift
// this variable seem to be part of sram_data.
// I'll try to decomp all equivalent functions
// before trying to prevent this bss reorder.
#ifdef NON_MATCHING
void func_80148D64(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    static s16 D_801CFD84;

    if (play->msgCtx.unk120A4[1] < -0x1D) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]--;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] < '0') {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = '9';
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->unk120A4[1] >= 0x1E) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]++;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] > '9') {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = '0';
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else {
        if ((msgCtx->unk120A4[0] >= 0x1E) && (D_801CFD84 == 0)) {
            D_801CFD84 = 1;
            msgCtx->unk120C2++;
            if (msgCtx->unk120C2 >= 3) {
                msgCtx->unk120C2 = 2;
            } else {
                play_sound(NA_SE_SY_CURSOR);
            }
        } else if ((msgCtx->unk120A4[0] < -0x1D) && (D_801CFD84 == 0)) {
            D_801CFD84 = 1;
            msgCtx->unk120C2--;
            if (msgCtx->unk120C2 < 0) {
                msgCtx->unk120C2 = 0;
            } else {
                play_sound(NA_SE_SY_CURSOR);
            }
        } else {
            D_801CFD84 = 0;
        }
    }
    msgCtx->bankRupeesSelected = (msgCtx->decodedBuffer.schar[msgCtx->unk120C0] * 100) - ('0' * 100);
    msgCtx->bankRupeesSelected += (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + 1] * 10) - ('0' * 10);
    msgCtx->bankRupeesSelected += (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + 2]) - '0';
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148D64.s")
#endif

void func_80149048(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->unk120A4[1] < -29) {
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2]--;
        if (msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] < 0x30) {
            msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = 0x39;
        }
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
    } else if (msgCtx->unk120A4[1] > 29) {
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

extern s16 D_801CFD88;

// Function is actually matching
// but the static variable create a bss shift
// this variable seem to be part of sram_data.
// I'll try to decomp all equivalent functions
// before trying to prevent this bss reorder.
#ifdef NON_MATCHING
void func_801491DC(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    static s16 D_801CFD88;

    if (msgCtx->unk120A4[1] < -29) {
        msgCtx->unk12054[msgCtx->unk120C2]--;
        if (msgCtx->unk12054[msgCtx->unk120C2] <= 0) {
            msgCtx->unk12054[msgCtx->unk120C2] = 5;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
        return;
    }
    if ((s32)msgCtx->unk120A4[1] > 29) {
        msgCtx->unk12054[msgCtx->unk120C2]++;
        if (msgCtx->unk12054[msgCtx->unk120C2] > 5) {
            msgCtx->unk12054[msgCtx->unk120C2] = 1;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
        return;
    }
    if (((s32)msgCtx->unk120A4[0] > 29) && (D_801CFD88 == 0)) {
        D_801CFD88 = 1;
        msgCtx->unk120C2 += 1;
        if ((s32)msgCtx->unk120C2 > 4) {
            msgCtx->unk120C2 = 4;
            return;
        }
        play_sound(NA_SE_SY_CURSOR);
        return;
    }
    if (((s32)msgCtx->unk120A4[0] < -29) && (D_801CFD88 == 0)) {
        D_801CFD88 = 1;
        msgCtx->unk120C2 += -1;
        if ((s32)msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
            return;
        }
        play_sound(NA_SE_SY_CURSOR);
        return;
    }
    D_801CFD88 = 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801491DC.s")
#endif

// Function is actually matching
// but the static variable create a bss shift
// this variable seem to be part of sram_data.
// I'll try to decomp all equivalent functions
// before trying to prevent this bss reorder.
#ifdef NON_MATCHING
void func_80149454(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    static s16 D_801CFD8C;

    if (msgCtx->unk120A4[1] < -29) {
        msgCtx->unk12054[msgCtx->unk120C2]--;
        if (msgCtx->unk12054[msgCtx->unk120C2] < 0) {
            msgCtx->unk12054[msgCtx->unk120C2] = 9;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
        return;
    }
    if ((s32)msgCtx->unk120A4[1] > 29) {
        msgCtx->unk12054[msgCtx->unk120C2]++;
        if (msgCtx->unk12054[msgCtx->unk120C2] > 9) {
            msgCtx->unk12054[msgCtx->unk120C2] = 0;
        }
        msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x30;
        Font_LoadCharNES(play, msgCtx->decodedBuffer.schar[msgCtx->unk120C0 + msgCtx->unk120C2],
                         msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
        return;
    }
    if (((s32)msgCtx->unk120A4[0] > 29) && (D_801CFD8C == 0)) {
        D_801CFD8C = 1;
        msgCtx->unk120C2 += 1;
        if ((s32)msgCtx->unk120C2 > 2) {
            msgCtx->unk120C2 = 2;
            return;
        }
        play_sound(NA_SE_SY_CURSOR);
        return;
    }
    if (((s32)msgCtx->unk120A4[0] < -29) && (D_801CFD8C == 0)) {
        D_801CFD8C = 1;
        msgCtx->unk120C2 += -1;
        if ((s32)msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
            return;
        }
        play_sound(NA_SE_SY_CURSOR);
        return;
    }
    D_801CFD8C = 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149454.s")
#endif

// Function is actually matching
// but the static variable create a bss shift
// this variable seem to be part of sram_data.
// I'll try to decomp all equivalent functions
// before trying to prevent this bss reorder.
#ifdef NON_MATCHING
void func_801496C8(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    static s16 D_801CFD90; // held

    if (play->msgCtx.unk120A4[1] < -0x1D) {
        msgCtx->unk12054[msgCtx->unk120C2]--;
        if (msgCtx->unk12054[msgCtx->unk120C2] < 0) {
            msgCtx->unk12054[msgCtx->unk120C2] = 3;
        }
        msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x824F;
        Font_LoadChar(play, msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2],
                      msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
        return;
    }
    if (msgCtx->unk120A4[1] >= 0x1E) {
        msgCtx->unk12054[msgCtx->unk120C2]++;
        if (msgCtx->unk12054[msgCtx->unk120C2] >= 4) {
            msgCtx->unk12054[msgCtx->unk120C2] = 0;
        }
        msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2] = msgCtx->unk12054[msgCtx->unk120C2] + 0x824F;
        Font_LoadChar(play, msgCtx->decodedBuffer.wchar[msgCtx->unk120C0 + msgCtx->unk120C2],
                      msgCtx->unk120C4 + (msgCtx->unk120C2 << 7));
        play_sound(NA_SE_SY_RUPY_COUNT);
        return;
    }
    if ((msgCtx->unk120A4[0] >= 0x1E) && (D_801CFD90 == 0)) {
        D_801CFD90 = 1;
        msgCtx->unk120C2++;
        if (msgCtx->unk120C2 >= 6) {
            msgCtx->unk120C2 = 5;
            return;
        }
        play_sound(NA_SE_SY_CURSOR);
        return;
    }
    if ((msgCtx->unk120A4[0] < -0x1D) && (D_801CFD90 == 0)) {
        D_801CFD90 = 1;
        msgCtx->unk120C2--;
        if (msgCtx->unk120C2 < 0) {
            msgCtx->unk120C2 = 0;
            return;
        }
        play_sound(NA_SE_SY_CURSOR);
        return;
    }
    D_801CFD90 = 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801496C8.s")
#endif

extern s32 D_801F6B00;
extern s32 D_801F6B04;

void func_8014995C(PlayState* play, TexturePtr arg1, Gfx** gfxp) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx = *gfxp;
    s16 temp_t0 = msgCtx->unk11FF4;
    s16 temp_t1 = msgCtx->unk11FF6;

    gDPPipeSync(gfx++);
    gDPLoadTextureBlock_4b(gfx++, arg1, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    if ((msgCtx->unk11F0A != 5) && (msgCtx->unk11F0A != 0xD) && (play->pauseCtx.bombersNotebookOpen == 0)) {
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->unk1201E);
        gSPTextureRectangle(gfx++, (temp_t0 + 1) << 2, (temp_t1 + 1) << 2, ((temp_t0 + D_801F6B00 + 1)) << 2,
                            ((temp_t1 + D_801F6B00 + 1)) << 2, G_TX_RENDERTILE, 0, 0, D_801F6B04, D_801F6B04);
        gDPPipeSync(gfx++);
    }
    gDPSetPrimColor(gfx++, 0, 0, msgCtx->unk12018, msgCtx->unk1201A, msgCtx->unk1201C, msgCtx->unk1201E);
    gSPTextureRectangle(gfx++, (temp_t0) << 2, (temp_t1) << 2, ((temp_t0 + D_801F6B00)) << 2,
                        ((temp_t1 + D_801F6B00)) << 2, G_TX_RENDERTILE, 0, 0, D_801F6B04, D_801F6B04);
    *gfxp = gfx++;
}

extern s16 D_801CFD98;
extern s16 D_801CFD9C;
extern s16 D_801CFDA0;
extern f32 D_801CFDA4[];
extern f32 D_801CFDC8[];
extern s16 D_801CFD94;

void func_80149C18(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (play->pauseCtx.bombersNotebookOpen == 0) {
        D_801CFD94 = (s16)(s32)(D_801CFDA4[msgCtx->stateTimer] * 256.0f);
        D_801CFD9C = (s16)(s32)(1024.0f / D_801CFDA4[msgCtx->stateTimer]);
        D_801CFD98 = (s16)(s32)(D_801CFDC8[msgCtx->stateTimer] * 64.0f);
        D_801CFDA0 = (s16)(s32)(1024.0f / D_801CFDC8[msgCtx->stateTimer]);
        msgCtx->unk1206A = msgCtx->unk12006 + ((0x40 - D_801CFD98) / 2);
        msgCtx->unk1203C += msgCtx->unk1203A / 8;
        msgCtx->stateTimer++;
    } else {
        msgCtx->stateTimer = 8;
        D_801CFD94 = 0x200;
        D_801CFD9C = 0x200;
        D_801CFD98 = 0x59;
        D_801CFDA0 = 0x2DB;
        msgCtx->unk1206A = msgCtx->unk12006 + ((0x5A - D_801CFD98) / 2);
    }
    if (msgCtx->stateTimer == 8) {
        msgCtx->unk12068 = msgCtx->unk12004;
        msgCtx->unk1206A = msgCtx->unk12006;
        msgCtx->msgMode = 3;
        msgCtx->unk1203C = msgCtx->unk1203A;
    }
    if (play->pauseCtx.bombersNotebookOpen == 0) {
        msgCtx->unk12068 = msgCtx->unk12004 + ((0x100 - D_801CFD94) / 2);
        return;
    }
    msgCtx->unk12068 = msgCtx->unk12004 + ((0x200 - D_801CFD94) / 2);
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149F74.s")

extern s16 D_801C6A74;
extern s16 D_801C6A78;

void func_8014AAD0(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->msgMode == 6) {
        play->msgCtx.ocarinaMode = 1;
        if (msgCtx->ocarinaAction == 0x33) {
            msgCtx->msgMode = 0x27;
            return;
        } else if (msgCtx->ocarinaAction == 0x34) {
            AudioOcarina_SetInstrumentId(1);
            AudioOcarina_SetInstrumentId(1);
            msgCtx->unk11F00 = AudioOcarina_GetPlaybackStaff();
            msgCtx->unk11F00->pos = 0;
            D_801C6A74 = D_801C6A78 = 0;
            func_80147564(play);
            msgCtx->stateTimer = 3;
            msgCtx->msgMode = 0x29;
            func_8019C398(0x19, 1);
            return;
        }
        if (msgCtx->ocarinaAction == 0x35) {
            msgCtx->msgMode = 0x2A;
            return;
        }
        if (msgCtx->ocarinaAction == 0x36) {
            AudioOcarina_SetInstrumentId(1);
            AudioOcarina_SetInstrumentId(1);
            msgCtx->unk11F00 = AudioOcarina_GetPlaybackStaff();
            msgCtx->unk11F00->pos = 0;
            D_801C6A74 = D_801C6A78 = 0;
            func_80147564(play);
            msgCtx->stateTimer = 3;
            msgCtx->msgMode = 0x2E;
            func_8019C398(0x17, 1);
            return;
        }
        if (msgCtx->ocarinaAction == 0x37) {
            msgCtx->msgMode = 0x2F;
            return;
        }
        if (msgCtx->ocarinaAction == 0x3A) {
            msgCtx->msgMode = 0x32;
            return;
        }
        if ((msgCtx->ocarinaAction >= 0x47) && (msgCtx->ocarinaAction < 0x52)) {
            msgCtx->msgMode = 0x35;
            return;
        }
        if (((msgCtx->ocarinaAction >= 2) && (msgCtx->ocarinaAction < 0x11)) || (msgCtx->ocarinaAction == 0x3B) ||
            (msgCtx->ocarinaAction == 0x3C) || (msgCtx->ocarinaAction == 0x3D) || (msgCtx->ocarinaAction == 0x3E) ||
            (msgCtx->ocarinaAction == 0x3F) || (msgCtx->ocarinaAction == 0x40)) {
            msgCtx->msgMode = 0xB;
            return;
        }
        if ((msgCtx->ocarinaAction == 0x41) || (msgCtx->ocarinaAction == 0x42) || (msgCtx->ocarinaAction == 0x43) ||
            (msgCtx->ocarinaAction == 0x44) || (msgCtx->ocarinaAction == 0x45) || (msgCtx->ocarinaAction == 0x46)) {
            msgCtx->msgMode = 0xC;
            return;
        }
        if ((msgCtx->ocarinaAction == 0) || (msgCtx->ocarinaAction == 1) || (msgCtx->ocarinaAction >= 0x28)) {
            msgCtx->msgMode = 0xA;
            return;
        }
        msgCtx->msgMode = 0xC;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014ADBC.s")

extern s16 D_801CFF70[];
extern s16 D_801CFF7C[];
extern s16 D_801CFF88[];

void func_8014C70C(PlayState* play, u16 arg1, s16 arg2) {
    MessageContext* msgCtx = &play->msgCtx;
    u16 *new_var2 = &arg1;
    
    if (arg1 == 0x83) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF88[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x10;
    } else  if ((arg1 >= 0x84) && (arg1 < 0x8B)) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF88[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x10;
    } else if (arg1 == 0x77) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x20;
    } else if ((arg1 >= 0x61) && (arg1 < 0x6D)) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF88[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x10;
        func_80178E3C(SEGMENT_ROM_START(icon_item_static_test), 0x61, (u8*)msgCtx->unk11EF8 + 0x1000, 0x180U);
    } else if (arg1 == 0x6D) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 6);
        msgCtx->unk12014 = 0x20;
        func_80178E3C(SEGMENT_ROM_START(icon_item_static_test), 0x61, (u8*)msgCtx->unk11EF8 + 0x1000, 0x1000U);
    } else if (arg1 < 0x61) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 6);
        msgCtx->unk12014 = 0x20;
        func_80178E3C(SEGMENT_ROM_START(icon_item_static_test), arg1, (u8*)msgCtx->unk11EF8 + 0x1000, 0x1000U);
    } else if (arg1 == 0xCC) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 8);
        msgCtx->unk12014 = 0x20;
        func_80178E3C(SEGMENT_ROM_START(schedule_dma_static_test), 0x15, (u8*)msgCtx->unk11EF8 + 0x1000, 0x400U);
    } else if (arg1 >= 0xB8) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF70[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 8);
        msgCtx->unk12014 = 0x20;
        func_80178E3C(SEGMENT_ROM_START(schedule_dma_static_test), (arg1 - 0xB8), (u8*)msgCtx->unk11EF8 + 0x1000,
                      0x800U);
    } else if (arg1 >= 0x6E) {
        msgCtx->unk12010 = (msgCtx->unk11FF8 - D_801CFF7C[gSaveContext.options.language]);
        msgCtx->unk12012 = (arg2 + 0xA);
        msgCtx->unk12014 = 0x18;
        func_80178E3C(SEGMENT_ROM_START(icon_item_24_static_test), (arg1 - 0x6E), (u8*)msgCtx->unk11EF8 + 0x1000,
                      0x900U);
    }

    if(1){}
    if (play->pauseCtx.bombersNotebookOpen != 0) {
        msgCtx->unk12010 = ((msgCtx->unk12010 * 1.4f) + 2.0f);
        msgCtx->unk12014 = (msgCtx->unk12014 * 1.4f);
    }
    msgCtx->unk12022 = 1;
}

void Message_LoadChar(PlayState* play, u16 codePointIndex, s32* offset, f32* arg3, s16 decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    Font_LoadChar(play, codePointIndex, temp1);
    msgCtx->decodedBuffer.wchar[decodedBufPos] = codePointIndex;
    temp1 += FONT_CHAR_TEX_SIZE;
    temp2 += (16.0f * msgCtx->unk12098);
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
    t += 1;
    Font_LoadChar(play, 0x8373, k); // 0x8373 = ピ in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x8373;
    t += 1;
    Font_LoadChar(play, 0x815C, k); // Ox815C = ― in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x815C;

    f += 16.0f * msgCtx->unk12098 * 3.0f;
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

extern s16 D_801CFF94[];

void func_8014CFDC(PlayState* play) {
    Font* font;
    MessageContext* msgCtx = &play->msgCtx;

    font = &msgCtx->font;
    if (msgCtx->msgBufPos == 0) {
        if (font->msgBuf.schar[msgCtx->msgBufPos + 2] != 0xFE) {
            msgCtx->unk11F18 = 0;
            if ((msgCtx->currentTextId == 0x176F) || (msgCtx->currentTextId == 0x1770) ||
                (msgCtx->currentTextId == 0x1771)) {
                msgCtx->unk11F16 = 0;
                msgCtx->msgBufPos += 2;
            } else {
                msgCtx->msgBufPos += 2;
                if ((font->msgBuf.schar[msgCtx->msgBufPos] < 0xC8) || (font->msgBuf.schar[msgCtx->msgBufPos] >= 0xD8)) {
                    msgCtx->unk11F16 = D_801CFF94[font->msgBuf.schar[msgCtx->msgBufPos]];
                } else {
                    msgCtx->unk11F16 = 0xFE;
                }
            }
        } else {
            msgCtx->msgBufPos += 2;
            msgCtx->unk11F16 = font->msgBuf.schar[msgCtx->msgBufPos];
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
        if (msgCtx->unk11F16 != 0xFE) {
            func_8014C70C(play, msgCtx->unk11F16, (msgCtx->unk1206A + 0xA));
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
    f += 7.0f * (16.0f * msgCtx->unk12098);
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

// JPN Area names
extern u16 D_801D0188[OWL_WARP_MAX][9];
// Area Names lengths
extern s16 D_801D0250[OWL_WARP_MAX];

// Message_LoadAreaText
void func_8014D62C(PlayState* play, s32* offset, f32* arg2, s16* decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stringLimit;
    s16 temp_s1 = *decodedBufPos;
    s32 temp_s2 = *offset;
    f32 sp3C = *arg2;
    s16 owlWarpId;
    s16 i;

    if (func_8010A0A4(play) || (play->sceneId == SCENE_SECOM)) {
        owlWarpId = OWL_WARP_ENTRANCE;
    } else {
        owlWarpId = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
    }
    stringLimit = D_801D0250[owlWarpId];

    for (i = 0; i < stringLimit; i++, temp_s1++, temp_s2 += FONT_CHAR_TEX_SIZE) {
        msgCtx->decodedBuffer.wchar[temp_s1] = D_801D0188[owlWarpId][i];
        Font_LoadChar(play, D_801D0188[owlWarpId][i], temp_s2);
    }

    temp_s1--;
    sp3C += (stringLimit - 1) * (16.0f * msgCtx->unk12098);

    *decodedBufPos = temp_s1;
    *offset = temp_s2;
    *arg2 = sp3C;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D7B4.s")

void func_80150A84(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    u8 offset = msgCtx->unk11F0A;
    u8 t;
    if (D_801CFC78[offset] != 0xE) {
        DmaMgr_SendRequest0(msgCtx->unk11EF8, &((u8*)SEGMENT_ROM_START(message_static))[D_801CFC78[offset] * 0x1000],
                            0x1000);
        if (play->pauseCtx.bombersNotebookOpen == 0) {
            if ((&D_801CFC78[offset] == &D_801CFC78[t = 0]) || (&D_801CFC78[offset] == &D_801CFC78[t = 6]) ||
                (&D_801CFC78[offset] == &D_801CFC78[t = 10]) || (&D_801CFC78[offset] == &D_801CFC78[t = 11])) {
                msgCtx->unk12034 = 0;
                msgCtx->unk12036 = 0;
                msgCtx->unk12038 = 0;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 1]) {
                msgCtx->unk12034 = 0x46;
                msgCtx->unk12036 = 0x32;
                msgCtx->unk12038 = 0x1E;
            } else if ((&D_801CFC78[offset] == &D_801CFC78[t = 2]) || (&D_801CFC78[offset] == &D_801CFC78[t = 8])) {
                msgCtx->unk12034 = 0;
                msgCtx->unk12036 = 0xA;
                msgCtx->unk12038 = 0x32;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 13]) {
                msgCtx->unk12034 = 0xFF;
                msgCtx->unk12036 = 0xFF;
                msgCtx->unk12038 = 0xC3;
            } else {
                msgCtx->unk12034 = 0xFF;
                msgCtx->unk12036 = 0;
                msgCtx->unk12038 = 0;
            }
            if (&D_801CFC78[offset] == &D_801CFC78[t = 1]) {
                msgCtx->unk1203A = 0xE6;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 3]) {
                msgCtx->unk1203A = 0xB4;
            } else if (&D_801CFC78[offset] == &D_801CFC78[t = 13]) {
                msgCtx->unk1203A = 0xDC;
            } else {
                msgCtx->unk1203A = 0xAA;
            }
        } else {
            msgCtx->unk12034 = 0xFF;
            msgCtx->unk12036 = 0xFF;
            msgCtx->unk12038 = 0xFF;
            msgCtx->unk1203A = 0xFF;
        }
        msgCtx->unk1203C = 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150D08.s")

extern s8 D_801C6A70;
extern s32 D_801F6B08;

void func_801514B0(PlayState* play, u16 arg1, u8 arg2) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    Player* player = GET_PLAYER(play);
    f32 temp = 1024.0f;

    msgCtx->ocarinaAction = 0xFFFF;

    if (msgCtx->msgMode == 0) {
        gSaveContext.prevHudVisibility = gSaveContext.hudVisibility;
    }
    msgCtx->unk12092 = 0;
    D_801C6A70 = 0;
    msgCtx->unk12094 = 0;
    msgCtx->unk12090 = 0;
    if (gSaveContext.options.language == 0) {
        msgCtx->unk12098 = 0.88f;
        msgCtx->unk11FFC = 0x12;
        msgCtx->unk11FF8 = 0x32;
    } else {
        msgCtx->unk12098 = 0.75f;
        msgCtx->unk11FFC = 0xC;
        msgCtx->unk11FF8 = 0x41;
    }
    D_801F6B00 = (msgCtx->unk12098 * 16.0f);
    D_801F6B04 = (temp / msgCtx->unk12098);
    D_801F6B08 = (temp / 1);
    if ((arg1 == 0x1709) && (player->transformation == 3)) {
        arg1 = 0x1705;
    }
    msgCtx->currentTextId = arg1;
    if (gSaveContext.options.language == 0) {
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
    msgCtx->unk12022 = 0;
    msgCtx->unk11FF2 = 0;
    msgCtx->unk12020 = 0;
    msgCtx->unk11FEE = 0;
    msgCtx->msgBufPos = 0;
    msgCtx->unk11FF0 = 0;
    msgCtx->unk11F08 = (u16)font->msgBuf.wchar[msgCtx->msgBufPos];
    msgCtx->unk11F18 = (s8)((s32)(msgCtx->unk11F08 & 0xF000) >> 0xC);
    msgCtx->unk11F0A = 9;
    msgCtx->unk11F0B = arg2;
    msgCtx->unk11F0C = msgCtx->unk11F08 & 0xF;
    msgCtx->unk11FF2 = 1;
    DmaMgr_SendRequest0(msgCtx->unk11EF8, &SEGMENT_ROM_START(message_static)[D_801CFC78[0] << 0xC], 0x1000U);
    msgCtx->unk12034 = 0;
    msgCtx->unk12036 = 0;
    msgCtx->unk12038 = 0;
    msgCtx->unk1203A = 0xE6;
    msgCtx->unk1203C = 0;
    msgCtx->unk1201E = 0xFF;
    msgCtx->unkActor = NULL;
    msgCtx->msgMode = 1;
    msgCtx->stateTimer = 0;
    msgCtx->unk12024 = 0;
    play->msgCtx.ocarinaMode = 0;
    msgCtx->unk120D2 = 0xFF;
    msgCtx->unk120CE = msgCtx->unk120D0 = msgCtx->unk120D2;
}

void Message_StartTextbox(PlayState* play, u16 textId, Actor* Actor) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->ocarinaAction = 0xFFFF;
    func_80150D08(play, textId);
    msgCtx->unkActor = Actor;
    msgCtx->msgMode = 1;
    msgCtx->stateTimer = 0;
    msgCtx->unk12024 = 0;
    play->msgCtx.ocarinaMode = 0;
}

void func_80151938(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    msgCtx->msgLength = 0;
    func_80150D08(play, textId);
    func_80150A84(play);
    msgCtx->msgMode = 5;
    msgCtx->stateTimer = 8;
    msgCtx->unk12024 = 0;

    if (interfaceCtx->unk_222 == 0) {
        if (textId != 0x1B93) {
            func_8011552C(play, 0x10);
        } else if (textId != 0xF8) {
            func_8011552C(play, 6);
        }
    }
    msgCtx->unk1203C = msgCtx->unk1203A;

    if (play->pauseCtx.bombersNotebookOpen) {
        msgCtx->unk12004 = 0x22;
        msgCtx->unk12006 = 0x15E;
        func_80149C18(play);
        msgCtx->stateTimer = 1;
    }
}

void func_80151A68(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->msgLength = 0;
    func_80150D08(play, textId);
    func_80150A84(play);
    func_8015B198(play);
    msgCtx->msgMode = 0x45;
    msgCtx->unk12024 = 0;
    msgCtx->unk1203C = msgCtx->unk1203A = msgCtx->unk1201E = 0;
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
    u8 temp = arg1;

    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        if ((gSaveContext.save.weekEventReg[D_801C6B28[arg1] >> 8] & (u8)D_801C6B28[arg1]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    } else if (arg1 >= 20) {
        if ((gSaveContext.save.weekEventReg[D_801C6B28[arg1] >> 8] & (u8)D_801C6B28[arg1]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    }
}

u32 func_80151C9C(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    while (true) {
        if (msgCtx->unk120B1 == 0) {
            return false;
        }
        msgCtx->unk120B1--;

        if ((gSaveContext.save.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]] >> 8] &
             (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]) == 0) {
            gSaveContext.save.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]] >> 8] =
                ((void)0, gSaveContext.save.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]] >> 8]) |
                (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]];

            if ((D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]] != 0) && CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                func_80151938(play, D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]]);
                play_sound(NA_SE_SY_SCHEDULE_WRITE);
                return true;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151DA4.s")

void func_80152434(PlayState* play, u16 arg2) {
    play->msgCtx.unk12046 = 0;
    func_80151DA4(play, arg2);
}

void func_80152464(PlayState* play, u16 arg1) {
    play->msgCtx.unk12046 = 1;
    func_80151DA4(play, arg1);
}

/**
 * @return u8 A value of the TextState enum representing the current state of the on-screen message
 */
u8 Message_GetState(MessageContext* msgCtx) {
    if (msgCtx->msgLength == 0) {
        return TEXT_STATE_NONE;
    }

    if (msgCtx->msgMode == 0x42) {
        if (msgCtx->unk11F14 != 0xFFFF) {
            return TEXT_STATE_1;
        }

        if ((msgCtx->unk12020 == 0x10) || (msgCtx->unk12020 == 0x11)) {
            return TEXT_STATE_CHOICE;
        }
        if ((msgCtx->unk12020 == 0x40) || (msgCtx->unk12020 == 0x42) || (msgCtx->unk12020 == 0x30)) {
            return TEXT_STATE_5;
        }
        if (msgCtx->unk12020 == 0x41) {
            return TEXT_STATE_16;
        }
        if ((msgCtx->unk12020 >= 0x50) && (msgCtx->unk12020 < 0x58)) {
            return TEXT_STATE_3;
        }
        if ((msgCtx->unk12020 == 0x60) || (msgCtx->unk12020 == 0x61)) {
            return TEXT_STATE_14;
        }
        if (msgCtx->unk12020 == 0x62) {
            return TEXT_STATE_15;
        }
        if (msgCtx->unk12020 == 0x63) {
            return TEXT_STATE_17;
        }
        if (msgCtx->unk12020 == 0x12) {
            return TEXT_STATE_18;
        }
        return TEXT_STATE_DONE;
    }

    if (msgCtx->msgMode == 0x41) {
        return TEXT_STATE_10;
    }
    if (msgCtx->msgMode == 0x1B) {
        return TEXT_STATE_7;
    }
    if ((msgCtx->ocarinaMode == 3) || (msgCtx->msgMode == 0x37)) {
        return TEXT_STATE_8;
    }
    if (msgCtx->msgMode == 0x20) {
        return TEXT_STATE_9;
    }
    if ((msgCtx->msgMode == 0x21) || (msgCtx->msgMode == 0x3A)) {
        return TEXT_STATE_11;
    }
    if (msgCtx->msgMode == 0x3D) {
        return TEXT_STATE_12;
    }
    if (msgCtx->msgMode == 0x40) {
        return TEXT_STATE_13;
    }
    if ((msgCtx->msgMode == 0x43) && (msgCtx->stateTimer == 1) && (msgCtx->unk120B1 == 0)) {
        return TEXT_STATE_CLOSING;
    }

    return TEXT_STATE_3;
}

extern u64 D_020029A0[];

void func_8015268C(PlayState* play, Gfx** gfxp) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx = *gfxp;

    gDPPipeSync(gfx++);
    if (((u32)msgCtx->unk11F0A == 0) || (msgCtx->unk11F0A == 2) || (msgCtx->unk11F0A == 9) || (msgCtx->unk11F0A == 0xA)) {
        gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    } else if (msgCtx->unk11F0A == 3) {
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    gDPSetPrimColor(gfx++, 0, 0, msgCtx->unk12034, msgCtx->unk12036, msgCtx->unk12038, msgCtx->unk1203C);
    if (((u32)msgCtx->unk11F0A == 0) || (msgCtx->unk11F0A == 2) || (msgCtx->unk11F0A == 6) || (msgCtx->unk11F0A == 8) ||
        (msgCtx->unk11F0A == 9) || (msgCtx->unk11F0A == 0xA)) {
        gDPLoadTextureBlock_4b(gfx++, msgCtx->unk11EF8, G_IM_FMT_I, 128, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPPipeSync(gfx++);
        if (msgCtx->unk11F0A == 3) {
            gDPSetEnvColor(gfx++, 0x00, 0x00, 0x00, 0xFF);
        } else if (msgCtx->unk11F0A == 0xD) {
            gDPSetEnvColor(gfx++, 0x14, 0x00, 0x0A, 0xFF);
        } else {
            gDPSetEnvColor(gfx++, 0x32, 0x14, 0x00, 0xFF);
        }
        gDPLoadTextureBlock_4b(gfx++, msgCtx->unk11EF8, G_IM_FMT_IA, 128, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    if (msgCtx->unk11F0A == 0xA) {
        gSPTextureRectangle(gfx++, (msgCtx->unk12068 << 2), ((msgCtx->unk1206A + 0x16) << 2),
                            ((msgCtx->unk12068 + msgCtx->unk12008) << 2), ((msgCtx->unk1206A + 0x36) << 2),
                            G_TX_RENDERTILE, 0, 0x0006, msgCtx->unk1200C << 1, 0x800);
    } else {
        gSPTextureRectangle(gfx++, (msgCtx->unk12068 << 2), ((msgCtx->unk1206A) << 2),
                            ((msgCtx->unk12068 + D_801CFD94) << 2), ((msgCtx->unk1206A + D_801CFD98) << 2),
                            G_TX_RENDERTILE, 0, 0, D_801CFD9C, D_801CFDA0);
    }
    if (msgCtx->unk11F0A == 3) {
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0x64, 0x00, 0xFF);
        gDPLoadTextureBlock_4b(gfx++, D_020029A0, G_IM_FMT_I, 16, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, 0x0138, 0x0298, 0x0178, 0x0318, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    }
    
    *gfxp = gfx++;
}

void func_80152C64(View* view) {
    SET_FULLSCREEN_VIEWPORT(view);
    View_ApplyOrthoToOverlay(view);
}

void func_80152CAC(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (msgCtx->ocarinaAction == 2) {
        AudioOcarina_SetInstrumentId(0xA);
    } else {
        if (msgCtx->ocarinaAction == 9) {
            AudioOcarina_SetInstrumentId(0xD);
        } else if (msgCtx->ocarinaAction == 7) {
            AudioOcarina_SetInstrumentId(6);
        } else if (msgCtx->ocarinaAction == 0xA) {
            AudioOcarina_SetInstrumentId(2);
        } else if (msgCtx->ocarinaAction == 0xC) {
            AudioOcarina_SetInstrumentId(1);
        } else if (msgCtx->ocarinaAction == 3) {
            AudioOcarina_SetInstrumentId(0xF);
        } else if (msgCtx->ocarinaAction == 0x10) {
            AudioOcarina_SetInstrumentId(0xC);
        } else if (msgCtx->ocarinaAction == 6) {
            AudioOcarina_SetInstrumentId(6);
        } else if (msgCtx->ocarinaAction == 5) {
            AudioOcarina_SetInstrumentId(5);
        } else {
            AudioOcarina_SetInstrumentId(1);
        }
    }
    if ((msgCtx->ocarinaAction == 0x3B) || (msgCtx->ocarinaAction == 0x3C)) {
        AudioOcarina_SetInstrumentId(0xC);
        func_8019C398(0xF, 0x83);
        return;
    }
    if ((msgCtx->ocarinaAction == 0x3D) || (msgCtx->ocarinaAction == 0x3E)) {
        AudioOcarina_SetInstrumentId(0xE);
        func_8019C398((msgCtx->ocarinaAction - 0x29), 0x84);
        return;
    }
    if ((msgCtx->ocarinaAction == 0x3F) || (msgCtx->ocarinaAction == 0x40)) {
        AudioOcarina_SetInstrumentId(8);
        func_8019C398((msgCtx->ocarinaAction - 0x2B), 0x44);
        return;
    }
    func_8019C398((msgCtx->ocarinaAction - 1), 2);
}

// Spawn song effect?
void func_80152EC0(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);

    if (1) {}
    if ((msgCtx->songPlayed < 0x17) && (msgCtx->songPlayed != 0xE) &&
        ((msgCtx->ocarinaAction < 0x43) || (msgCtx->ocarinaAction >= 0x47))) {
        msgCtx->unk120B0 = 1;
        if (msgCtx->songPlayed != 0x16) {
            Actor_Spawn(&play->actorCtx, play, D_801D02D8[msgCtx->songPlayed], player->actor.world.pos.x,
                        player->actor.world.pos.y, player->actor.world.pos.z, 0, 0, 0, D_801D02F8[msgCtx->songPlayed]);
            return;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_OCEFF_WIPE4, player->actor.world.pos.x, player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 0);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152FB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153750.s")

void func_80153E7C(PlayState* play, void* arg1) {
    if ((gSaveContext.options.language == 0) && (play->msgCtx.unk12090 == 0)) {
        func_8014ADBC(play, arg1);
        return;
    }
    if (play->msgCtx.unk12090 != 0) {
        func_8015E7EC(play, arg1);
        return;
    }
    func_8015966C(play, arg1, 0);
}

extern u64 D_02002AA0[];

void func_80153EF0(PlayState* play, Gfx** gfxp) {
    MessageContext* msgCtx = &play->msgCtx;
    Gfx* gfx;

    gfx = *gfxp;
    func_8012C680(&gfx);

    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetAlphaDither(gfx++, G_AD_NOTPATTERN);
    gDPSetPrimColor(gfx++, 0, 0, 0x00, 0x00, 0x00, msgCtx->unk1203C);
    gDPSetEnvColor(gfx++, 0x8C, 0x28, 0xA0, 0xFF);
    gDPLoadTextureBlock(gfx++, &D_02002AA0, G_IM_FMT_I, G_IM_SIZ_8b, 64, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gfx++, 0, (XREG(77) * 4), 0x0500, ((XREG(77) + XREG(76)) * 4), G_TX_RENDERTILE, 0, 0, 0x00CC,
                        0x0400);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetEnvColor(gfx++, 0x00, 0x00, 0x00, 0xFF);

    if ((msgCtx->currentTextId < 0x1BB2) || (msgCtx->currentTextId >= 0x1BB7)) {
        msgCtx->unk11FF8 = XREG(75);
    }
    msgCtx->unk11FFA = XREG(74);
    func_8015966C(play, &gfx, 0);
    *gfxp = gfx++;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801541D4.s")

void func_80156758(PlayState* play) {
    Gfx* nextDisplayList;
    Gfx* polyOpa;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    polyOpa = POLY_OPA_DISP;
    nextDisplayList = Graph_GfxPlusOne(polyOpa);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);

    if ((play->msgCtx.currentTextId != 0x5E6) || !Play_InCsMode(play)) {
        func_801541D4(play, &nextDisplayList);
    }

    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(polyOpa, nextDisplayList);
    POLY_OPA_DISP = nextDisplayList;
    CLOSE_DISPS(gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015680C.s")

void func_801586A4(PlayState* play) {
    play->msgCtx.messageEntryTableNes = D_801C6B98;
    play->msgCtx.messageTableStaff = D_801CFB08;
}

void Message_Init(PlayState* play) {
    Font* font;
    MessageContext* messageCtx = &play->msgCtx;

    func_801586A4(play);
    play->msgCtx.ocarinaMode = 0;
    messageCtx->msgMode = 0;
    messageCtx->msgLength = 0;
    messageCtx->currentTextId = 0;
    messageCtx->unk12020 = 0;
    messageCtx->choiceIndex = 0;
    messageCtx->ocarinaAction = messageCtx->unk11FF2 = 0;
    messageCtx->unk1201E = 0xFF;
    View_Init(&messageCtx->view, play->state.gfxCtx);
    messageCtx->unk11EF8 = THA_AllocEndAlign16(&play->state.heap, 0x13C00);
    font = &play->msgCtx.font;
    Font_LoadOrderedFont(&play->msgCtx.font);
    font->unk_11D88 = 0;
    messageCtx->unk12090 = messageCtx->unk12092 = 0;
    messageCtx->unk12094 = 0;
    messageCtx->unk1209C = 0;
    messageCtx->unk120A0 = 0;
    messageCtx->unk12068 = 0x34;
    messageCtx->unk1206A = 0x24;
    messageCtx->unk120B0 = 0;
    messageCtx->unk120BE = 0;
    messageCtx->unk120C0 = 0;
    messageCtx->unk120C2 = 0;
    messageCtx->unk120C4 = 0;
    messageCtx->unk120C8 = 0;
    messageCtx->unk120CA = 0;
    messageCtx->unk120CC = 0;
    messageCtx->unk120CE = 0;
    messageCtx->unk120D0 = 0;
    messageCtx->unk120D2 = 0;
    messageCtx->unk120D4 = 0;
    messageCtx->unk120D6 = 0;
}
