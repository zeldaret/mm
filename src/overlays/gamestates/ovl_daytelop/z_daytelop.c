/*
 * File: z_daytelop.c
 * Overlay: ovl_daytelop
 * Description:
 */

#include "z_daytelop.h"
#include "static/daytelop_static/daytelop_static.h"
#include "static/icon_item_gameover_static/icon_item_gameover_static.h"


// unused
UNK_TYPE D_808158E0[] = {
    0x00000C00,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000C04,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00100000,
    0x00000000,
    0x00000000,
    0x40000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x04000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x04000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0000000F,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0070B000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x01A00020,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00001000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000010,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000003,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00100400,
    0x00000000,
    0x00000000,
    0x00000022,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000080,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000C00,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000102,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000070,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x40000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00100000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00100000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000100,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000080,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000080,
    0x00000000,
    0x00000000,
    0x00000000,
    0x80000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000001,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000002,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000001,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00100000,
    0x00000000,
    0x00000000,
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000001,
    0x00000000,
};

u8 D_80815FF0 = 0;

TexturePtr D_80815FF4[] = {
    gDaytelopFirstDayLeftNESTex,
    gDaytelopSecondDayLeftNESTex,
    gDaytelopFinalDayLeftNESTex,
};

TexturePtr D_80816000 = {
    gDaytelopNewDayLeftNESTex
};

TexturePtr D_80816004[] = {
    gDaytelopFirstDayRightNESTex,
    gDaytelopSecondDayRightNESTex,
    gDaytelopFinalDayRightNESTex,
};

TexturePtr D_80816010 = {
    gDaytelopNewDayRightNESTex
};

TexturePtr D_80816014[] = {
    gDaytelop72HoursNESTex,
    gDaytelop48HoursNESTex,
    gDaytelop24HoursNESTex,
};

#ifdef NON_EQUIVALENT
void Daytelop_Update(DaytelopContext* this, GameState* gameState) {
    s16 temp_v0;
    s32 temp_a1;
    u8 temp_v0_3;
    s32 phi_a2;
    s32 aux_var;

    this->transitionCountdown--;

    if (this->transitionCountdown == 0) {
        if (gSaveContext.day < 9) {
            gSaveContext.gameMode = 0;
        } else {
            gSaveContext.unk_3F4A = 0xFFF6;
            gSaveContext.day = 1;
        }
        this->common.running = false;
        if (1) {}
        this->common.nextGameStateInit = Play_Init;
        this->common.nextGameStateSize = sizeof(GlobalContext); // 0x19258;
        gSaveContext.time = CLOCK_TIME(6, 0);
        D_801BDBC8 = 0xFE;
    } else if (this->transitionCountdown == 0x5A) {
        this->unk_242 = 1;
        this->alpha = 0;
        if (1) {}
        D_80815FF0 = 0x1E;
    }

    if (this->unk_242 == 1) {
    aux_var = D_80815FF0;
        /*
        temp_a1 = this->alpha - 0xFF;
        phi_a2 = temp_a1;
        if (temp_a1 < 0) {
            phi_a2 = 0xFF - this->alpha;
        }
        this->alpha = this->alpha + (s16) (phi_a2 / D_80815FF0);
        */

        
        phi_a2 = ABS_ALT((this->alpha - 0xFF));
        //phi_a2 /= D_80815FF0;
        //this->alpha += phi_a2;
        //this->alpha += (phi_a2 / D_80815FF0--);
        //aux_var = D_80815FF0;
        //aux_var = this->alpha + (phi_a2 / (aux_var));
        aux_var = phi_a2 / aux_var;
        aux_var = this->alpha + aux_var;
        this->alpha = (s16)aux_var;
        

        /*
        phi_a2 =  (ABS_ALT(this->alpha - 0xFF) / D_80815FF0);
        this->alpha += phi_a2;
        */
        
        /*
        temp_v0_3 = (D_80815FF0 - 1) & 0xFF;
        D_80815FF0 = temp_v0_3;
        if (temp_v0_3 == 0) {
            this->unk_242 = 2;
            this->alpha = 0xFF;
        }
        */
        D_80815FF0--;
        if (D_80815FF0 == 0) {
            this->unk_242 = 2;
            this->alpha = 0xFF;
        }

    }
}
#else
void Daytelop_Update(DaytelopContext* this, GameState* gameState);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Update.s")
#endif

//#ifdef NON_EQUIVALENT
void Daytelop_Draw(DaytelopContext* this) {
    //DaytelopContext* this = (DaytelopContext*)thisx;
    /*
    GraphicsContext* sp1C;
    Gfx* temp_v0;
    Gfx* temp_v0_10;
    Gfx* temp_v0_11;
    Gfx* temp_v0_12;
    Gfx* temp_v0_13;
    Gfx* temp_v0_14;
    Gfx* temp_v0_15;
    Gfx* temp_v0_16;
    Gfx* temp_v0_17;
    Gfx* temp_v0_18;
    Gfx* temp_v0_19;
    Gfx* temp_v0_20;
    Gfx* temp_v0_21;
    Gfx* temp_v0_22;
    Gfx* temp_v0_23;
    Gfx* temp_v0_24;
    Gfx* temp_v0_25;
    Gfx* temp_v0_26;
    Gfx* temp_v0_27;
    Gfx* temp_v0_28;
    Gfx* temp_v0_29;
    Gfx* temp_v0_2;
    Gfx* temp_v0_30;
    Gfx* temp_v0_31;
    Gfx* temp_v0_32;
    Gfx* temp_v0_33;
    Gfx* temp_v0_34;
    Gfx* temp_v0_35;
    Gfx* temp_v0_36;
    Gfx* temp_v0_37;
    Gfx* temp_v0_38;
    Gfx* temp_v0_39;
    Gfx* temp_v0_3;
    Gfx* temp_v0_40;
    Gfx* temp_v0_41;
    Gfx* temp_v0_42;
    Gfx* temp_v0_43;
    Gfx* temp_v0_44;
    Gfx* temp_v0_45;
    Gfx* temp_v0_46;
    Gfx* temp_v0_47;
    Gfx* temp_v0_48;
    Gfx* temp_v0_49;
    Gfx* temp_v0_4;
    Gfx* temp_v0_50;
    Gfx* temp_v0_51;
    Gfx* temp_v0_52;
    Gfx* temp_v0_53;
    Gfx* temp_v0_54;
    Gfx* temp_v0_5;
    Gfx* temp_v0_6;
    Gfx* temp_v0_7;
    Gfx* temp_v0_8;
    Gfx* temp_v0_9;
    GraphicsContext* temp_a0;
    */

    GraphicsContext* sp1C = this->common.gfxCtx;
    OPEN_DISPS(sp1C);
    //temp_a0 = this->common.gfxCtx;

    //sp1C = this->common.gfxCtx;
    func_8012C628(this->common.gfxCtx);
    if (gSaveContext.day >= 9) {
        /*
        temp_v0 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0 + 8;
        temp_v0->words.w0 = 0xE200001C;
        temp_v0->words.w1 = 0x00504240;
        */
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

        /*
        temp_v0_2 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_2 + 8;
        temp_v0_2->words.w0 = 0xFCFFFFFF;
        temp_v0_2->words.w1 = 0xFFFDF6FB;
        */
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

        /*
        temp_v0_3 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_3 + 8;
        temp_v0_3->words.w1 = 0xFFFFFFFF;
        temp_v0_3->words.w0 = 0xFA000000;
        */
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

        /*
        temp_v0_4 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_4 + 8;
        temp_v0_4->words.w1 = 0;
        temp_v0_4->words.w0 = 0xF65003C0;
        */
        gDPFillRectangle(POLY_OPA_DISP++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    //sp1C = temp_a0;
    func_8012C628(this->common.gfxCtx);

    /*
    temp_v0_5 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_5 + 8;
    temp_v0_5->words.w0 = 0xE200001C;
    temp_v0_5->words.w1 = 0x0F0A4000;
    */
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    /*
    temp_v0_6 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_6 + 8;
    temp_v0_6->words.w1 = 0xFFFFFFFF;
    temp_v0_6->words.w0 = 0xFA000000;
    */
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);


    if (gSaveContext.day >= 9) {
        /*
        temp_v0_7 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_7 + 8;
        temp_v0_7->words.w1 = 0;
        temp_v0_7->words.w0 = 0xE2001E01;
        */
        gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
    }

    if (gSaveContext.day < 9) {
        #if 0
        /*
        temp_v0_8 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_8 + 8;
        temp_v0_8->words.w0 = 0xFD900000;
        temp_v0_8->words.w1 = *(&D_80815FF0 + (((s32) gSaveContext.day % 5) * 4));
        */
        gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, D_80815FF0[CURRENT_DAY]);

        /*
        temp_v0_9 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_9 + 8;
        temp_v0_9->words.w1 = 0x07000000;
        temp_v0_9->words.w0 = 0xF5900000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);


        /*
        temp_v0_10 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_10 + 8;
        temp_v0_10->words.w1 = 0;
        temp_v0_10->words.w0 = 0xE6000000;
        */
        gDPLoadSync(POLY_OPA_DISP++);

        /*
        temp_v0_11 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_11 + 8;
        temp_v0_11->words.w1 = 0x077FF100;
        temp_v0_11->words.w0 = 0xF3000000;
        */
        gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 2047, 256);

        /*
        temp_v0_12 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_12 + 8;
        temp_v0_12->words.w1 = 0;
        temp_v0_12->words.w0 = 0xE7000000;
        */
        gDPPipeSync(POLY_OPA_DISP++);


        /*
        temp_v0_13 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_13 + 8;
        temp_v0_13->words.w1 = 0;
        temp_v0_13->words.w0 = 0xF5801000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_4b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_14 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_14 + 8;
        temp_v0_14->words.w1 = 0x001FC0FC;
        temp_v0_14->words.w0 = 0xF2000000;
        */
        gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x01FC, 0x00FC);
        #endif
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80815FF4[CURRENT_DAY-1], G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    } else {
        #if 0
        /*
        temp_v0_15 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_15 + 8;
        temp_v0_15->words.w0 = 0xFD900000;
        temp_v0_15->words.w1 = D_80816000;
        */
        gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, D_80816000[0]);
    
        /*
        temp_v0_16 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_16 + 8;
        temp_v0_16->words.w1 = 0x07000000;
        temp_v0_16->words.w0 = 0xF5900000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    
        /*
        temp_v0_17 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_17 + 8;
        temp_v0_17->words.w1 = 0;
        temp_v0_17->words.w0 = 0xE6000000;
        */
        gDPLoadSync(POLY_OPA_DISP++);
    
        /*
        temp_v0_18 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_18 + 8;
        temp_v0_18->words.w1 = 0x077FF100;
        temp_v0_18->words.w0 = 0xF3000000;
        */
        gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 2047, 256);
    
        /*
        temp_v0_19 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_19 + 8;
        temp_v0_19->words.w1 = 0;
        temp_v0_19->words.w0 = 0xE7000000;
        */
        gDPPipeSync(POLY_OPA_DISP++);
    
        /*
        temp_v0_20 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_20 + 8;
        temp_v0_20->words.w1 = 0;
        temp_v0_20->words.w0 = 0xF5801000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_4b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    
        /*
        temp_v0_21 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_21 + 8;
        temp_v0_21->words.w1 = 0x001FC0FC;
        temp_v0_21->words.w0 = 0xF2000000;
        */
        gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x01FC, 0x00FC);
        #endif

        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816000, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    }

    #if 0
    /*
    temp_v0_22 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_22 + 8;
    temp_v0_22->words.w0 = 0xE4280234;
    temp_v0_22->words.w1 = 0x00080134;
    */
    gTexRect(POLY_OPA_DISP++, 0x0080, 0x0134, 0x0280, 0x0234, G_TX_RENDERTILE);



    /*
    temp_v0_23 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_23 + 8;
    temp_v0_23->words.w1 = 0;
    temp_v0_23->words.w0 = 0xE1000000;
    */
    gDPHalf1(POLY_OPA_DISP++, 0x00000000);

    /*

    temp_v0_24 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_24 + 8;
    temp_v0_24->words.w1 = 0x04000400;
    temp_v0_24->words.w0 = 0xF1000000;
    */
    gDPHalf2(POLY_OPA_DISP++, 0x04000400);
    //gDPHalf2(POLY_OPA_DISP++, &D_04000400);
    #endif
    gSPTextureRectangle(POLY_OPA_DISP++, 0x0080, 0x0134, 0x0280, 0x0234, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);


    if (gSaveContext.day < 9) {
        #if 0
        /*
        temp_v0_25 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_25 + 8;
        temp_v0_25->words.w0 = 0xFD900000;
        temp_v0_25->words.w1 = (((s32*)D_80816000)[(((s32) gSaveContext.day % 5) * 4)]);
        */
        gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (((s32*)D_80816000)[(((s32) gSaveContext.day % 5))]));

        /*
        temp_v0_26 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_26 + 8;
        temp_v0_26->words.w1 = 0x07000000;
        temp_v0_26->words.w0 = 0xF5900000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_27 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_27 + 8;
        temp_v0_27->words.w1 = 0;
        temp_v0_27->words.w0 = 0xE6000000;
        */
        gDPLoadSync(POLY_OPA_DISP++);

        /*
        temp_v0_28 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_28 + 8;
        temp_v0_28->words.w1 = 0x077FF100;
        temp_v0_28->words.w0 = 0xF3000000;
        */
        gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 2047, 256);

        /*
        temp_v0_29 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_29 + 8;
        temp_v0_29->words.w1 = 0;
        temp_v0_29->words.w0 = 0xE7000000;
        */
        gDPPipeSync(POLY_OPA_DISP++);

        /*
        temp_v0_30 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_30 + 8;
        temp_v0_30->words.w1 = 0;
        temp_v0_30->words.w0 = 0xF5801000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_4b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_31 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_31 + 8;
        temp_v0_31->words.w1 = 0x001FC0FC;
        temp_v0_31->words.w0 = 0xF2000000;
        */
        gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x01FC, 0x00FC);
        #endif

        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816004[CURRENT_DAY-1], G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        #if 0
        /*
        temp_v0_32 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_32 + 8;
        temp_v0_32->words.w0 = 0xFD900000;
        temp_v0_32->words.w1 = D_80816010;
        */
        //gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, D_80816010);
        gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, D_80816010[0]);

        /*
        temp_v0_33 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_33 + 8;
        temp_v0_33->words.w1 = 0x07000000;
        temp_v0_33->words.w0 = 0xF5900000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_34 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_34 + 8;
        temp_v0_34->words.w1 = 0;
        temp_v0_34->words.w0 = 0xE6000000;
        */
        gDPLoadSync(POLY_OPA_DISP++);

        /*
        temp_v0_35 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_35 + 8;
        temp_v0_35->words.w1 = 0x077FF100;
        temp_v0_35->words.w0 = 0xF3000000;
        */
        gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 2047, 256);

        /*
        temp_v0_36 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_36 + 8;
        temp_v0_36->words.w1 = 0;
        temp_v0_36->words.w0 = 0xE7000000;
        */
        gDPPipeSync(POLY_OPA_DISP++);

        /*
        temp_v0_37 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_37 + 8;
        temp_v0_37->words.w1 = 0;
        temp_v0_37->words.w0 = 0xF5801000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_4b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_38 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_38 + 8;
        temp_v0_38->words.w1 = 0x001FC0FC;
        temp_v0_38->words.w0 = 0xF2000000;
        */
        gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x01FC, 0x00FC);

        #endif
        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816010, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    }

    #if 0
    /*
    temp_v0_39 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_39 + 8;
    temp_v0_39->words.w0 = 0xE4480234;
    temp_v0_39->words.w1 = 0x00280134;
    */
    gTexRect(POLY_OPA_DISP++, 0x0280, 0x0134, 0x0480, 0x0234, G_TX_RENDERTILE);


    /*
    temp_v0_40 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_40 + 8;
    temp_v0_40->words.w1 = 0;
    temp_v0_40->words.w0 = 0xE1000000;
    */
    gDPHalf1(POLY_OPA_DISP++, 0x00000000);

    /*
    temp_v0_41 = temp_a0->polyOpa.p;
    temp_a0->polyOpa.p = temp_v0_41 + 8;
    temp_v0_41->words.w1 = 0x04000400;
    temp_v0_41->words.w0 = 0xF1000000;
    */
    gDPHalf2(POLY_OPA_DISP++, 0x04000400);
    #endif
    gSPTextureRectangle(POLY_OPA_DISP++, 0x0280, 0x0134, 0x0480, 0x0234, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    if (gSaveContext.day < 9) {

        /*
        temp_v0_42 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_42 + 8;
        temp_v0_42->words.w1 = 0;
        temp_v0_42->words.w0 = 0xE7000000;
        */
        gDPPipeSync(POLY_OPA_DISP++);

        /*
        temp_v0_43 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_43 + 8;
        temp_v0_43->words.w1 = 0x00504240;
        temp_v0_43->words.w0 = 0xE200001C;
        */
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

        /*
        temp_v0_44 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_44 + 8;
        temp_v0_44->words.w0 = 0xFA000000;
        temp_v0_44->words.w1 = (this->alpha & 0xFF) | ~0xFF;
        */
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->alpha);

        #if 0
        /*
        temp_v0_45 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_45 + 8;
        temp_v0_45->words.w0 = 0xFD900000;
        //temp_v0_25->words.w1 = (((s32*)D_80816000)[(((s32) gSaveContext.day % 5) * 4)]);
        //temp_v0_45->words.w1 = *(&D_80816010 + (((s32) gSaveContext.day % 5) * 4));
        temp_v0_45->words.w1 = (((s32*)D_80816010)[(((s32) gSaveContext.day % 5) * 4)]);
        */
        gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (((s32*)D_80816010)[(((s32) gSaveContext.day % 5) )]));

        /*
        temp_v0_46 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_46 + 8;
        temp_v0_46->words.w1 = 0x07000000;
        temp_v0_46->words.w0 = 0xF5900000;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_47 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_47 + 8;
        temp_v0_47->words.w1 = 0;
        temp_v0_47->words.w0 = 0xE6000000;
        */
        gDPLoadSync(POLY_OPA_DISP++);

        /*
        temp_v0_48 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_48 + 8;
        temp_v0_48->words.w1 = 0x0747F0E4;
        temp_v0_48->words.w0 = 0xF3000000;
        */
        gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 1151, 228);


        /*
        temp_v0_49 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_49 + 8;
        temp_v0_49->words.w1 = 0;
        temp_v0_49->words.w0 = 0xE7000000;
        */
        gDPPipeSync(POLY_OPA_DISP++);

        /*
        temp_v0_50 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_50 + 8;
        temp_v0_50->words.w1 = 0;
        temp_v0_50->words.w0 = 0xF5801200;
        */
        gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_4b, 9, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

        /*
        temp_v0_51 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_51 + 8;
        temp_v0_51->words.w1 = 0x0023C07C;
        temp_v0_51->words.w0 = 0xF2000000;
        */
        gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x023C, 0x007C);
        #endif 

        gDPLoadTextureBlock_4b(POLY_OPA_DISP++, D_80816014[CURRENT_DAY-1], G_IM_FMT_I, 144, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);


        #if 0
        /*
        temp_v0_52 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_52 + 8;
        temp_v0_52->words.w0 = 0xE43A02C0;
        temp_v0_52->words.w1 = 0x00160240;
        */
        gTexRect(POLY_OPA_DISP++, 0x0160, 0x0240, 0x03A0, 0x02C0, G_TX_RENDERTILE);

        /*
        temp_v0_53 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_53 + 8;
        temp_v0_53->words.w1 = 0;
        temp_v0_53->words.w0 = 0xE1000000;
        */
        gDPHalf1(POLY_OPA_DISP++, 0x00000000);

        /*
        temp_v0_54 = temp_a0->polyOpa.p;
        temp_a0->polyOpa.p = temp_v0_54 + 8;
        temp_v0_54->words.w1 = 0x04000400;
        temp_v0_54->words.w0 = 0xF1000000;
        */
        gDPHalf2(POLY_OPA_DISP++, 0x04000400);

        #endif
        gSPTextureRectangle(POLY_OPA_DISP++, 0x0160, 0x0240, 0x03A0, 0x02C0, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    }

    CLOSE_DISPS(this->common.gfxCtx);
}
//#else
//void Daytelop_Draw(DaytelopContext* this);
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Draw.s")
//#endif


void Daytelop_Main(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    func_8012CF0C(this->common.gfxCtx, 1, 1, 0, 0, 0);

    OPEN_DISPS(this->common.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, this->unk_A4);
    gSPSegment(POLY_OPA_DISP++, 0x0C, this->unk_A8);
    CLOSE_DISPS(this->common.gfxCtx);

    Daytelop_Draw(this);
    Daytelop_Update(this, &this->common);
}

void Daytelop_Destroy(GameState* thisx) {
    ShrinkWindow_Fini();
}

void Daytelop_nop80815770(DaytelopContext* this) {

}

void Daytelop_LoadGraphics(DaytelopContext* this) {
    size_t segmentSize = SEGMENT_ROM_SIZE(daytelop_static);

    this->unk_A4 = THA_AllocEndAlign16(&this->common.heap, segmentSize);
    DmaMgr_SendRequest0(this->unk_A4, SEGMENT_ROM_START(daytelop_static), segmentSize);

    segmentSize = SEGMENT_ROM_SIZE(icon_item_gameover_static);
    this->unk_A8 = THA_AllocEndAlign16(&this->common.heap, segmentSize);
    DmaMgr_SendRequest0(this->unk_A8, SEGMENT_ROM_START(icon_item_gameover_static), segmentSize);
}

void Daytelop_Init(GameState* thisx) {
    DaytelopContext* this = (DaytelopContext*)thisx;

    Game_SetFramerateDivisor(thisx, 1);
    SysMatrix_StateAlloc(thisx);
    ShrinkWindow_Fini();
    View_Init(&this->view, thisx->gfxCtx);
    thisx->main = Daytelop_Main;
    thisx->destroy = Daytelop_Destroy;
    this->transitionCountdown = 0x8C;
    this->unk_242 = 0;

    if (gSaveContext.day < 9) {
        if (gSaveContext.day == 0) {
            func_80143AC4();
        }
        Sram_IncrementDay();
    }
    Daytelop_nop80815770(this);
    Daytelop_LoadGraphics(this);
    play_sound(0x5808);
}
