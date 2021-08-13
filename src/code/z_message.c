#include "global.h"

void func_80147520(void) {
    D_801CFC98 = 0xFF;
    D_801CFCA4[0] = D_801CFCA4[1] = D_801CFCA4[2] = D_801CFCA4[3]= D_801CFCA4[4] = D_801CFCA4[5] = D_801CFCA4[6] = D_801CFCA4[7]  = D_801CFCA4[8] = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147564.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147624.s")

#ifdef NON_MATCHING

u32 func_80147734(GlobalContext *globalCtx) {
    u32 ret_value;
 
    MessageContext* msgCtx = &globalCtx->msgCtx;
    if(msgCtx->unk12020 == 0x10 ||msgCtx->unk12020 == 0x11){
        return ~(CONTROLLER1(globalCtx)->press.button | 0xFFFF7FFF) == 0;
    }
    //buttons = 
    ret_value = (~(CONTROLLER1(globalCtx)->press.button | 0xFFFF7FFF) == 0);
    if(ret_value == 0){
        ret_value = (~(CONTROLLER1(globalCtx)->press.button | ~0x4000) == 0);
        if(ret_value == 0){
            ret_value = (~(CONTROLLER1(globalCtx)->press.button | ~8) == 0);
        }
    }
    return ret_value;
}
#else

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147734.s")
#endif

void func_801477B4(GlobalContext *globalCtx) {
    MessageContext *msgCtx;

    msgCtx = &globalCtx->msgCtx;
    if (globalCtx->msgCtx.unk11F10 != 0) {
        msgCtx->unk12023 = 2;
        msgCtx->msgMode = 0x43;
        msgCtx->unk12020 = 0;
        play_sound(0U);
    }
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147818.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148558.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149048.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801491DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149454.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801496C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014995C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149F74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014AAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014ADBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014C70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CC14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D304.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D7B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801514B0.s")

void Message_StartTextbox(GlobalContext* globalCtx, u16 textId, Actor* Actor) {
    MessageContext* msgCtx;

    msgCtx = &globalCtx->msgCtx;
    msgCtx->ocarinaAction = 0xFFFF;
    func_80150D08(globalCtx, textId);
    msgCtx->unkActor = Actor;
    msgCtx->msgMode = 1;
    msgCtx->unk12023 = 0;
    msgCtx->unk12024 = 0;
    globalCtx->msgCtx.ocarinaMode = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151938.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151DA4.s")


void func_80152434(GlobalContext *globalCtx, u16 arg2) {
    globalCtx->msgCtx.unk12046 = 0;
    func_80151DA4(globalCtx, arg2);
} 


void func_80152464(GlobalContext *globalCtx, s32 arg1) {
    globalCtx->msgCtx.unk12046 = 1;
    func_80151DA4(globalCtx, arg1);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_GetState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015268C.s")

void func_80152C64(View *view) {
    Viewport viewport; 
    viewport.bottomY = 0xF0; viewport.rightX = 0x140;
    viewport.topY = 0;
    viewport.leftX = 0;
    

    View_SetViewport(view, (Viewport *) &viewport);
    func_8013FBC8(view);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152CAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152FB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153750.s")

void func_80153E7C(GlobalContext *globalCtx, void *arg1) {
    if ((gSaveContext.language == 0) && (globalCtx->msgCtx.unk12090 == 0)) {
        func_8014ADBC(globalCtx, arg1);
        return;
    }
    if (globalCtx->msgCtx.unk12090 != 0) {
        func_8015E7EC(globalCtx, arg1);
        return;
    }
    func_8015966C(globalCtx, arg1, 0);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801541D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80156758.s")

 /*
s32 ShrinkWindow_GetLetterboxTarget(); // extern
s32 func_8010A0A4(GlobalContext *, u16, s32, s16 *); // extern
void func_8014546C(SramContext *); // extern
void func_80147008(PauseContext *, s32, s32); // extern
void func_80147138(PauseContext *, s32, s32); // extern
void func_80149C18(GlobalContext *, s32, SaveContext *); // extern
void func_8019C300(?, s32, s32); // extern
void func_8019CD08(?, s32, s32); // extern
void func_801A3AEC(?); // extern
void func_801A3FB4(?); // extern
extern UNK_TYPE1 D_801C67C8;
extern UNK_TYPE1 D_801C6818;
extern UNK_TYPE1 D_801C6840;
extern UNK_TYPE1 D_801C6850;
extern u8 D_801C6A70;
extern s16 D_801C6A7C;
extern s16 D_801D03C8[];
extern s16 D_801D03E8[];
extern s16 D_801D0408[];
extern s16 D_801D0428[];
extern UNK_TYPE1 D_801D045A;
extern UNK_TYPE1 D_801D0462;
extern u8 D_801D0468;

void func_8015680C(GlobalContext *globalCtx) {
    s16 sp50;
    s16 sp4C;
    s16 sp4A;
    s32 sp44;
    s32 sp40;
    u16 sp3E;
    MessageContext *sp30;
    PauseContext *sp2C;
    void *sp28;
    void *sp20;
    DmaRequest *temp_v0_18;
    Input *temp_v1_5;
    MessageContext *msgCtx;
    MessageContext *temp_t5_2;
    PauseContext *temp_v0_16;
    PauseContext *temp_v0_21;
    SramContext *temp_a0_5;
    SramContext *temp_a0_6;
    s16 temp_v0;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_23;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_v0_22;
    s32 temp_v0_26;
    s32 temp_v0_27;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_10;
    s32 temp_v1_7;
    s32 temp_v1_9;
    u16 temp_a0_3;
    u16 temp_a0_4;
    u16 temp_t7;
    u16 temp_v0_13;
    u16 temp_v0_14;
    u16 temp_v0_15;
    u16 temp_v0_17;
    u16 temp_v0_19;
    u16 temp_v0_20;
    u16 temp_v0_24;
    u16 temp_v0_25;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 temp_v1_6;
    u16 temp_v1_8;
    u8 temp_a0_2;
    u8 temp_t8;
    u8 temp_t9;
    u8 temp_v0_12;
    u8 temp_v1;
    u8 temp_v1_4;
    void *temp_t0;
    void *phi_ra;
    s32 phi_v1;
    s32 phi_a1;
    s16 phi_t8;
    void *phi_at;
    s32 phi_v0;
    s32 phi_t0;
    s32 phi_a3;
    u8 phi_v1_2;
    void *phi_t0_2;
    void *phi_ra_2;
    MessageContext *phi_t5;
    s16 *phi_a3_2;
    void *phi_ra_3;

    globalCtx->msgCtx.unk120A4 = (s16) globalCtx->state.input[0].rel.stick_x;
    temp_t0 = globalCtx + 0x10000;
    globalCtx->msgCtx.unk120A6 = (s16) globalCtx->state.input[0].rel.stick_y;
    msgCtx = &globalCtx->msgCtx;
    phi_ra = msgCtx + 0x10000;
    phi_a1 = 0;
    phi_t0_2 = temp_t0;
    phi_t0_2 = temp_t0;
    if ((s32) globalCtx->msgCtx.unk120A4 < -30) {
        if (msgCtx->unk120A8 == -1) {
            msgCtx->unk120AC = (s16) (msgCtx->unk120AC - 1);
            if ((s32) msgCtx->unk120AC < 0) {
                msgCtx->unk120AC = 2;
            } else {
                msgCtx->unk120A4 = 0;
            }
        } else {
            msgCtx->unk120AC = 0xA;
            msgCtx->unk120A8 = -1;
        }
    } else if ((s32) msgCtx->unk120A4 >= 31) {
        if (msgCtx->unk120A8 == 1) {
            msgCtx->unk120AC = (s16) (msgCtx->unk120AC - 1);
            if ((s32) msgCtx->unk120AC < 0) {
                msgCtx->unk120AC = 2;
            } else {
                msgCtx->unk120A4 = 0;
            }
        } else {
            msgCtx->unk120AC = 0xA;
            msgCtx->unk120A8 = 1;
        }
    } else {
        msgCtx->unk120A8 = 0;
    }
    if ((s32) globalCtx->msgCtx.unk120A6 < -30) {
        if (msgCtx->unk120AA == -1) {
            globalCtx->msgCtx.unk120AE = (s16) (msgCtx->unk120AE - 1);
            if ((s32) msgCtx->unk120AE < 0) {
                globalCtx->msgCtx.unk120AE = 2;
            } else {
                globalCtx->msgCtx.unk120A6 = 0;
            }
        } else {
            globalCtx->msgCtx.unk120AE = 0xA;
            globalCtx->msgCtx.unk120AA = -1;
        }
    } else if (globalCtx->msgCtx.unk120A6 >= 31) {
        if (msgCtx->unk120AA == 1) {
            globalCtx->msgCtx.unk120AE = (s16) (msgCtx->unk120AE - 1);
            if ((s32) msgCtx->unk120AE < 0) {
                globalCtx->msgCtx.unk120AE = 2;
            } else {
                globalCtx->msgCtx.unk120A6 = 0;
            }
        } else {
            globalCtx->msgCtx.unk120AE = 0xA;
            globalCtx->msgCtx.unk120AA = 1;
        }
    } else {
        globalCtx->msgCtx.unk120AA = 0;
    }
    if (msgCtx->unk11F10 != 0) {
        switch (msgCtx->msgMode) {
        case 1:
            temp_t8 = D_801C6A70 + 1;
            temp_a0 = temp_t8 & 0xFF;
            D_801C6A70 = temp_t8;
            phi_v1 = 0;
            if ((temp_a0 >= 4) || ((msgCtx->unk12040 == 0) && (temp_a0 >= 2))) {
                phi_v1 = 1;
            }
            if (phi_v1 != 0) {
                if (msgCtx->unk12040 != 0) {
                    sp20 = phi_ra;
                    sp30 = &globalCtx->msgCtx;
                    func_800B8898(globalCtx, globalCtx->actorCtx.actorList[2].first, &sp50, &sp4C);
                    func_800B8898(globalCtx, msgCtx->unk12040, &sp50, &sp4A);
                    if ((s32) sp4C >= (s32) sp4A) {
                        phi_a1 = (s32) (s16) (((s32) (sp4C - sp4A) / 2) + sp4A);
                    } else {
                        phi_a1 = (s32) (s16) (((s32) (sp4A - sp4C) / 2) + sp4C);
                    }
                } else {
                    globalCtx->msgCtx.unk12068 = (s16) msgCtx->unk12004;
                    globalCtx->msgCtx.unk1206A = msgCtx->unk12006;
                }
                temp_a0_2 = msgCtx->unk11F0B;
                temp_v1 = msgCtx->unk11F0A;
                switch(temp_a0_2){
                    case 0:
                        temp_v0_2 = globalCtx->sceneNum;
                        if ((temp_v0_2 == 4) || (temp_v0_2 == 5) || (temp_v0_2 == 6)) {
                            if (phi_a1 < 100) {
                                globalCtx->msgCtx.unk12006 = D_801D03E8[temp_v1];
                                phi_v0 = temp_v0_5;
                                phi_t0 = 5;
                            } else {
                                temp_v0_6 = temp_v1 * 2;
                                globalCtx->msgCtx.unk12006 = D_801D0408[temp_v1];
                                phi_v0 = temp_v0_6;
                                phi_t0 = 5;
                            }
                        } else {
                            temp_v0_3 = temp_v1 * 2;
                            phi_v0 = temp_v0_3;
                            if (phi_a1 < 0xA0) {
                                temp_v0_4 = temp_v1 * 2;
                                globalCtx->msgCtx.unk12006 = D_801D03E8[temp_v1];
                                phi_v0 = temp_v0_4;
                                phi_t0 = 5;
                            } else {
                                msgCtx->unk12006 = D_801D0408[temp_v1];
                                phi_at = &globalCtx->msgCtx + 0x10000;
                            }
                        }
                        break;
                    case 1:
                        temp_v0_7 = temp_v1 * 2;
                        globalCtx->msgCtx.unk12006 = D_801D0408[temp_v1];
                        phi_v0 = temp_v0_7;
                        phi_t0 = 5;
                        break;                 
                    case 2:
                        temp_v0_8 = temp_v1 * 2;
                        globalCtx->msgCtx.unk12006 = D_801D0428[temp_v1];
                        phi_v0 = temp_v0_8;
                        phi_t0 = 5;
                        break;
                    case 7:
                        globalCtx->msgCtx.unk12006 = 0x9E;
                        phi_v0 = temp_v1 * 2;
                        phi_t0 = 5;
                        break;
                    default:
                        temp_v0_9 = temp_v1 * 2;
                        msgCtx->unk12006 = D_801D03E8[temp_v1];
                        phi_v0 = temp_v0_9;
                        break;
                }

                //END SWITCH
                globalCtx->msgCtx.unk12004 = D_801D03C8[temp_v1];
                if ((gSaveContext.language == 0) && (msgCtx->unk12090 == 0)) {
                    temp_v0_10 = msgCtx->unk12006;
                    msgCtx->unk11FFE = (s16) (temp_v0_10 + 7);
                    msgCtx->unk12000 = (s16) (temp_v0_10 + 25);
                    msgCtx->unk12002 = (s16) (temp_v0_10 + 43);
                } else {
                    temp_v0_11 = msgCtx->unk12006;
                    msgCtx->unk11FFE = (s16) (temp_v0_11 + 20);
                    msgCtx->unk12000 = (s16) (temp_v0_11 + 32);
                    msgCtx->unk12002 = (s16) (temp_v0_11 + 44);
                }
                temp_v0_12 = msgCtx->unk11F0A;
                if ((temp_v0_12 == 4) || (phi_t0 == temp_v0_12)) {
                    globalCtx->msgCtx.msgMode = 3;
                    globalCtx->msgCtx.unk12068 = msgCtx->unk12004;
                    globalCtx->msgCtx.unk1206A = msgCtx->unk12006;
                    globalCtx->msgCtx.unk12008 = 0x100;
                    globalCtx->msgCtx.unk1200A = 0x40;
                    globalCtx->msgCtx.unk1200C = 0x200;
                    globalCtx->msgCtx.unk1200E = 0x200;
                    return;
                }
                sp30 = &globalCtx->msgCtx;
                func_80149C18(globalCtx, phi_a1, &gSaveContext);
                func_801A3FB4(0);
                globalCtx->msgCtx.unk12023 = 0;
                globalCtx->msgCtx.msgMode = 2;
                if (globalCtx->pauseCtx.unk_2B9 == 0) {
                    func_80150A84();
                    return;
                }
            }
            return;
        case 2:
            func_80149C18(globalCtx, 0, (SaveContext *) 0x10000);
            return;
        case 3:
            globalCtx->msgCtx.msgMode = 4;
            if (globalCtx->pauseCtx.unk_2B9 == 0) {
                temp_v0_13 = msgCtx->unk11F04;
                if (temp_v0_13 == 0xFF) {
                    func_8011552C(globalCtx, 0x12);
                    return;
                }
                if (temp_v0_13 != 0xF8) {
                    func_8011552C(globalCtx, 0x10);
                    return;
                }
            }
            return;
        case 4:
            sp20 = phi_ra;
            sp30 = &globalCtx->msgCtx;
            func_8014D7B4();
            if (msgCtx->unk1209C != 0) {
                sp20 = phi_ra;
                sp30 = &globalCtx->msgCtx;
                Interface_ChangeAlpha(1U);
            }
            if (D_801D0468 != 0) {
                globalCtx->msgCtx.unk11FEE = (u16) msgCtx->unk11FF0;
                D_801D0468 = 0U;
                return;
            }
            return;
        case 5:
            globalCtx->msgCtx.unk12023 = msgCtx->unk12023 - 1;
            if (msgCtx->unk12023 == 0) {
                func_8014D7B4();
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 6:
            if (msgCtx->unk11F0A != 4) {
                temp_v0_14 = globalCtx->state.input[0].press.button;
                if ((~(temp_v0_14 | ~0x4000) == 0) && (msgCtx->unk11FF2 == 0)) {
                    globalCtx->msgCtx.unk12094 = 1;
                    globalCtx->msgCtx.unk11FEE = (u16) msgCtx->unk11FF0;
                    return;
                }
                if ((~(temp_v0_14 | 0xFFFF7FFF) == 0) && (msgCtx->unk11FF2 == 0)) {
                    for(temp_v1_2 = globalCtx->msgCtx.unk11F24[msgCtx->unk11FEE];
                        (temp_v1_2 != 0x10) && (temp_v1_2 != 0x12) && (temp_v1_2 != 0x1B) 
                        && (temp_v1_2 != 0x1C) && (temp_v1_2 != 0x1D) && (temp_v1_2 != 0x19) 
                        && (temp_v1_2 != 0xE0) && (temp_v1_2 != 0xBF) && (temp_v1_2 != 0x15) 
                        && (temp_v1_2 != 0x1A);
                        temp_v1_2 = globalCtx->msgCtx.unk11F24[msgCtx->unk11FEE]){
                        msgCtx->unk11FEE++;
                    }
                }
                return;
            }
            if ((~(globalCtx->state.input[0].press.button | 0xFFFF7FFF) == 0) && (msgCtx->unk11FF2 == 0)) {
                for(temp_v1_3 = globalCtx->msgCtx.unk11F24[temp_a0_4];
                    (temp_v1_3 != 0x10) && (temp_v1_3 != 0x12) && (temp_v1_3 != 0x1B) 
                    && (temp_v1_3 != 0x1C) && (temp_v1_3 != 0x1D) && (temp_v1_3 != 0x19) 
                    && (temp_v1_3 != 0xE0) && (temp_v1_3 != 0xBF) && (temp_v1_3 != 0x15) 
                    && (temp_v1_3 != 0x1A);
                    temp_v1_3 = globalCtx->msgCtx.unk11F24[temp_a0_4]){
                    globalCtx->msgCtx.unk11FEE++;
                }
            }
            return;
        case 7:
            if (func_80147624(globalCtx) != 0) {
                globalCtx->msgCtx.msgMode = 6;
                globalCtx->msgCtx.unk11FEE++;
            }
            return;
        case 8:
            globalCtx->msgCtx.unk12023--;
            if (msgCtx->unk12023 == 0) {
                globalCtx->msgCtx.msgMode = 4;
            }
            return;
        case 65:
            if (func_80147624(globalCtx) != 0) {
                globalCtx->msgCtx.msgMode = 4;
                globalCtx->msgCtx.unk11FEC++;
            }
            return;
        case 66:
            temp_v1_4 = msgCtx->unk12020;
            phi_v1_2 = temp_v1_4;
            if ((temp_v1_4 == 80) || (temp_v1_4 == 82)) {
                globalCtx->msgCtx.unk12023--;
                if ((msgCtx->unk12023 == 0) || ((msgCtx->unk12020 == 82) && (func_80147624(globalCtx) != 0))) {
                    if (msgCtx->unk11F14 != 0xFFFF) {
                        play_sound(0x4818U);
                        func_80151938(globalCtx, msgCtx->unk11F14);
                        return;
                    }
                    if (msgCtx->unk120B1 != 0) {
                        func_80151C9C();
                        if (MIPS2C_ERROR(Read from unset register $v0) == 0) {
                            func_801477B4(globalCtx);
                            return;
                        }
                        // Duplicate return node #352. Try simplifying control flow for better match
                        return;
                    }
                    func_801477B4(globalCtx);
                    return;
                }
                // Duplicate return node #352. Try simplifying control flow for better match
                return;
            }
            if ((temp_v1_4 != 0x30) && (temp_v1_4 != 0x40) && (temp_v1_4 != 0x42) && (phi_a3 = 0x10, phi_a3 = 0x10, (temp_v1_4 != 0x41))) {
                if (temp_v1_4 != 0x10) {
                    if (temp_v1_4 != 0x11) {
                        if (temp_v1_4 != 0x12) {
                            if (temp_v1_4 != 0x55) {
                                if (temp_v1_4 != 0x56) {
                                    if (temp_v1_4 != 0x57) {
                                        goto block_157;
                                    }
                                    globalCtx->msgCtx.unk1201E = (s16) (phi_ra->unk201E - 0x14);
                                    if ((s32) phi_ra->unk201E <= 0) {
                                        globalCtx->msgCtx.unk1201E = 0;
                                        if (phi_ra->unk1F14 != 0xFFFF) {
                                            sp20 = phi_ra;
                                            play_sound(0x4818U);
                                            func_80151938(globalCtx, phi_ra->unk1F14);
                                            return;
                                        }
                                        if (phi_ra->unk20B1 != 0) {
                                            sp20 = phi_ra;
                                            sp28 = temp_t0;
                                            sp30 = &globalCtx->msgCtx;
                                            func_80151C9C();
                                            if (MIPS2C_ERROR(Read from unset register $v0) == 0) {
                                                func_801477B4(globalCtx);
                                                return;
                                            }
                                            goto block_151;
                                        }
                                        func_801477B4(globalCtx);
                                        return;
                                    }
block_151:
                                    goto block_156;
                                }
                                globalCtx->msgCtx.unk12023 = phi_ra->unk2023 - 1;
                                if (phi_ra->unk2023 == 0) {
                                    globalCtx->msgCtx.unk12020 = 0x57;
                                }
                                goto block_156;
                            }
                            globalCtx->msgCtx.unk1201E = (s16) (phi_ra->unk201E + 0x14);
                            if ((s32) phi_ra->unk201E >= 0xFF) {
                                globalCtx->msgCtx.unk1201E = 0xFF;
                                globalCtx->msgCtx.unk12020 = 0x56;
                            }
                            goto block_156;
                        }
                        sp20 = phi_ra;
                        sp28 = temp_t0;
                        sp30 = &globalCtx->msgCtx;
                        func_80148B98(globalCtx, 1U);
                        phi_ra_3 = phi_ra;
                        phi_t0_2 = temp_t0;
                        phi_t5 = &globalCtx->msgCtx;
                        goto block_156;
                    }
                    sp20 = phi_ra;
                    sp28 = temp_t0;
                    sp30 = &globalCtx->msgCtx;
                    func_80148B98(globalCtx, 2U);
                    phi_ra_3 = phi_ra;
                    phi_t0_2 = temp_t0;
                    phi_t5 = &globalCtx->msgCtx;
                    goto block_156;
                }
                sp20 = phi_ra;
                sp28 = temp_t0;
                sp30 = &globalCtx->msgCtx;
                func_80148B98(globalCtx, 1U);
                phi_ra_3 = phi_ra;
                phi_t0_2 = temp_t0;
                phi_t5 = &globalCtx->msgCtx;
block_156:
                phi_v1_2 = phi_ra_3->unk2020;
                phi_ra_2 = phi_ra_3;
block_157:
                if ((phi_a3 == phi_v1_2) && (phi_t0_2->unk6932 == 1)) {
                    sp20 = phi_ra_2;
                    if (func_80147624(globalCtx) != 0) {
                        if (phi_ra_2->unk2021 == 0) {
                            globalCtx->msgCtx.ocarinaMode = 2;
                        } else {
                            globalCtx->msgCtx.ocarinaMode = 4;
                        }
                        func_801477B4(globalCtx);
                        return;
                    }
                    // Duplicate return node #352. Try simplifying control flow for better match
                    return;
                }
                if ((phi_a3 == phi_v1_2) && (phi_t0_2->unk6932 == 0x12)) {
                    sp20 = phi_ra_2;
                    sp30 = phi_t5;
                    if (func_80147624(globalCtx) != 0) {
                        if (phi_ra_2->unk2021 == 0) {
                            sp20 = phi_ra_2;
                            sp30 = phi_t5;
                            func_8019F208();
                            phi_t5->msgMode = 0x4A;
                            phi_t5->unk11FF0 = (s16) (phi_ra_2->unk1FF0 - 3);
                            phi_t5->unk120D6 = 0;
                            phi_t5->unk120D4 = 0;
                            return;
                        }
                        func_8019F230();
                        globalCtx->msgCtx.ocarinaMode = 4;
                        func_801477B4(globalCtx);
                        return;
                    }
                    // Duplicate return node #352. Try simplifying control flow for better match
                    return;
                }
                if ((phi_a3 == phi_v1_2) && (phi_t0_2->unk6932 == 0x13)) {
                    sp20 = phi_ra_2;
                    if (func_80147624(globalCtx) != 0) {
                        if (phi_ra_2->unk2021 == 0) {
                            func_8019F208();
                            if (gSaveContext.unk_14 == 0) {
                                globalCtx->msgCtx.ocarinaMode = 0x19;
                                gSaveContext.unk_14 = -2;
                            } else {
                                globalCtx->msgCtx.ocarinaMode = 0x18;
                                gSaveContext.unk_14 = 0;
                            }
                            func_801477B4(globalCtx);
                            return;
                        }
                        func_8019F230();
                        globalCtx->msgCtx.ocarinaMode = 4;
                        func_801477B4(globalCtx);
                        return;
                    }
                    // Duplicate return node #352. Try simplifying control flow for better match
                    return;
                }
                if ((phi_a3 == phi_v1_2) && (phi_t0_2->unk6932 == 0x15)) {
                    sp20 = phi_ra_2;
                    if (func_80147624(globalCtx) != 0) {
                        if (phi_ra_2->unk2021 == 0) {
                            func_8019F208();
                            if (gSaveContext.isNight != 0) {
                                gSaveContext.time = 0x4000;
                            } else {
                                gSaveContext.time = 0xC000;
                            }
                            globalCtx->msgCtx.ocarinaMode = 0x1A;
                            gSaveContext.unk3DD3 = 0;
                        } else {
                            func_8019F230();
                            globalCtx->msgCtx.ocarinaMode = 4;
                        }
                        func_801477B4(globalCtx);
                        return;
                    }
                    // Duplicate return node #352. Try simplifying control flow for better match
                    return;
                }
                if ((phi_a3 != phi_v1_2) || (globalCtx->pauseCtx.state != 0x18)) {
                    if ((phi_a3 == phi_v1_2) && (phi_t0_2->unk6932 == 0x1B)) {
                        sp20 = phi_ra_2;
                        if (func_80147624(globalCtx) != 0) {
                            if (phi_ra_2->unk2021 == 0) {
                                func_8019F208();
                                globalCtx->msgCtx.ocarinaMode = 0x26;
                            } else {
                                func_8019F230();
                                globalCtx->msgCtx.ocarinaMode = 4;
                            }
                            func_801477B4(globalCtx);
                            return;
                        }
                        // Duplicate return node #352. Try simplifying control flow for better match
                        return;
                    }
                    if ((phi_v1_2 == 0x60) || (phi_v1_2 == 0x61) || (phi_a3 == phi_v1_2) || (phi_v1_2 == 0x11) || (phi_v1_2 == 0x50) || (phi_v1_2 == 0x52) || (phi_v1_2 == 0x55) || (phi_v1_2 == 0x56) || (phi_v1_2 == 0x57) || (phi_v1_2 == 0x62)) {
                        if (phi_v1_2 == 0x50) {
                            return;
                        }
                        // Duplicate return node #352. Try simplifying control flow for better match
                        return;
                    }
                    temp_v1_5 = globalCtx->state.input;
                    if (globalCtx->pauseCtx.unk_2B9 != 0) {
                        if ((temp_v1_5->rel.stick_x != 0) || (temp_v1_5->rel.stick_y != 0) || (temp_v0_15 = temp_v1_5->press.button, (~(temp_v0_15 | 0xFFFF7FFF) == 0)) || (~(temp_v0_15 | ~0x4000) == 0) || (~(temp_v0_15 | ~0x1000) == 0)) {
                            play_sound(0x4808U);
                            func_801477B4(globalCtx);
                            return;
                        }
                        // Duplicate return node #352. Try simplifying control flow for better match
                        return;
                    }
                    if (phi_t0_2->unk6932 == 0x27) {
                        if (func_80147734(globalCtx) != 0) {
                            play_sound(0x4808U);
                            func_801477B4(globalCtx);
                            globalCtx->msgCtx.ocarinaMode = 4;
                            return;
                        }
                        // Duplicate return node #352. Try simplifying control flow for better match
                        return;
                    }
                    if ((phi_ra_2->unk1F04 != 0x2790) && (sp20 = phi_ra_2, (func_80147734(globalCtx) != 0))) {
                        if (phi_ra_2->unk1F14 != 0xFFFF) {
                            sp20 = phi_ra_2;
                            play_sound(0x4818U);
                            func_80151938(globalCtx, phi_ra_2->unk1F14);
                            return;
                        }
                        if ((phi_ra_2->unk20B1 == 0) || (sp20 = phi_ra_2, func_80151C9C(), (MIPS2C_ERROR(Read from unset register $v0) != 1))) {
                            if (phi_ra_2->unk1F04 == 0x579) {
                                gSaveContext.unk_3F22 = 0;
                            }
                            play_sound(0x4808U);
                            func_801477B4(globalCtx);
                            return;
                        }
                        // Duplicate return node #352. Try simplifying control flow for better match
                        return;
                    }
                    // Duplicate return node #352. Try simplifying control flow for better match
                    return;
                }
                // Duplicate return node #352. Try simplifying control flow for better match
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 67:
            globalCtx->msgCtx.unk12023 = phi_ra->unk2023 - 1;
            if (phi_ra->unk2023 == 0) {
                if (D_801C6A7C == 9) {
                    if (globalCtx->interfaceCtx.restrictions.songOfSoaring == 0) {
                        sp20 = phi_ra;
                        sp30 = &globalCtx->msgCtx;
                        if ((func_8010A0A4(globalCtx, 0x1B95U, 0x10000, &D_801C6A7C) != 0) || (globalCtx->sceneNum == 0x4F)) {
                            Message_StartTextbox(globalCtx, 0x1B93U, NULL);
                            globalCtx->msgCtx.ocarinaMode = 0x1B;
                            D_801C6A7C = 0xFF;
                            return;
                        }
                        if (phi_ra->unk20B0 == 0) {
                            if (gSaveContext.owlActivationFlags != 0) {
                                temp_v0_16 = &globalCtx->pauseCtx;
                                temp_t7 = temp_v0_16->pageIndex;
                                temp_v0_16->pageIndex = 0;
                                temp_v0_16->state = 0x13;
                                temp_v0_16->unk_2C8 = temp_t7;
                                temp_v0_16->unk_2CA = temp_v0_16->unk_238[4];
                                sp2C = temp_v0_16;
                                func_800F4A10(globalCtx);
                                temp_v0_16->pageIndex = 1;
                                D_801C6A7C = 0xFF;
                                func_801477B4(globalCtx);
                                globalCtx->msgCtx.ocarinaMode = 4;
                                gSaveContext.unk_3F26 = 0x15;
                                func_80115844(globalCtx, 0x12);
                                Game_SetFramerateDivisor((GameState *) globalCtx, 2);
                                if (ShrinkWindow_GetLetterboxTarget() != 0) {
                                    ShrinkWindow_SetLetterboxTarget(0);
                                }
                                func_801A3AEC(1);
                                return;
                            }
                            D_801C6A7C = 0xFF;
                            Message_StartTextbox(globalCtx, 0xFBU, NULL);
                            globalCtx->msgCtx.ocarinaMode = 0x27;
                            return;
                        }
                        globalCtx->msgCtx.unk12023 = 1;
                        return;
                    }
                    D_801C6A7C = 0xFF;
                    Message_StartTextbox(globalCtx, 0x1B95U, NULL);
                    globalCtx->msgCtx.ocarinaMode = 0x27;
                    return;
                }
                temp_v0_17 = phi_ra->unk1F04;
                if ((temp_v0_17 == 0xC) || (temp_v0_17 == 0xD) || (temp_v0_17 == 0xC5) || (temp_v0_17 == 0xC6) || (temp_v0_17 == 0xC7) || (temp_v0_17 == 0x2165) || (temp_v0_17 == 0x2166) || (temp_v0_17 == 0x2167) || (temp_v0_17 == 0x2168)) {
                    gSaveContext.healthAccumulator = 0x140;
                }
                if ((globalCtx->csCtx.state == 0) && (gSaveContext.cutscene < 0xFFF0) && ((temp_v0_18 = &globalCtx->objectCtx.status[9].dmaReq, (globalCtx->activeCamera == 0)) || ((temp_v0_18->unk875 == 0) && (temp_v0_18->unkB4A == 0))) && (globalCtx->msgCtx.ocarinaMode == 4)) {
                    temp_v0_19 = gSaveContext.unk_3F26;
                    if ((temp_v0_19 == 0) || (temp_v0_19 == 1) || (temp_v0_19 == 2)) {
                        gSaveContext.unk_3F26 = 0x32;
                    }
                    gSaveContext.unk_3F22 = 0;
                }
                temp_v0_20 = phi_ra->unk1F04;
                if (((s32) temp_v0_20 >= 0x1BB2) && ((s32) temp_v0_20 < 0x1BB7) && ((globalCtx->actorCtx.unk5 & 2) != 0)) {
                    Message_StartTextbox(globalCtx, 0x5E6U, NULL);
                    return;
                }
                if (phi_ra->unk20B1 != 0) {
                    sp30 = &globalCtx->msgCtx;
                    func_80151C9C();
                    if (MIPS2C_ERROR(Read from unset register $v0) == 0) {
                        globalCtx->msgCtx.unk12023 = 1;
                        return;
                    }
                    // Duplicate return node #352. Try simplifying control flow for better match
                    return;
                }
                globalCtx->msgCtx.unk11F10 = 0;
                globalCtx->msgCtx.msgMode = 0;
                globalCtx->msgCtx.unk11F04 = 0;
                globalCtx->msgCtx.unk12023 = 0;
                temp_v0_21 = &globalCtx->pauseCtx;
                gGameInfo->data[1375] = 0;
                if (temp_v0_21->unk_2B9 != 0) {
                    sp20 = phi_ra;
                    sp2C = temp_v0_21;
                    sp28 = temp_t0;
                    sp30 = &globalCtx->msgCtx;
                    func_8011552C(globalCtx, 0x15);
                    temp_v0_21->unk_2B9 = 0;
                }
                phi_a3_2 = &D_801C6A7C;
                if (phi_ra->unk2020 == 0x30) {
                    globalCtx->msgCtx.unk12020 = 0;
                    globalCtx->msgCtx.ocarinaMode = 2;
                } else {
                    globalCtx->msgCtx.unk12020 = 0;
                }
                temp_v0_22 = gSaveContext.inventory.questItems;
                if ((temp_v0_22 & 0xF0000000) == 0x40000000) {
                    gSaveContext.inventory.questItems = temp_v0_22 ^ 0x40000000;
                    gSaveContext.healthCapacity += 0x10;
                    gSaveContext.health += 0x10;
                }
                temp_v1_6 = phi_ra->unk202C;
                if (temp_v1_6 != 0x39) {
                    temp_v0_23 = D_801C6A7C;
                    if (temp_v0_23 == 6) {
                        if (globalCtx->interfaceCtx.restrictions.unk_312 == 0) {
                            Message_StartTextbox(globalCtx, 0x1B8AU, NULL);
                            globalCtx->msgCtx.ocarinaMode = 0x12;
                            phi_a3_2 = &D_801C6A7C;
                        } else {
                            D_801C6A7C = 0xFF;
                            Message_StartTextbox(globalCtx, 0x1B95U, NULL);
                            globalCtx->msgCtx.ocarinaMode = 0x27;
                            phi_a3_2 = &D_801C6A7C;
                        }
                    } else if (temp_v0_23 == 0xC) {
                        if (globalCtx->interfaceCtx.restrictions.unk_314 == 0) {
                            if (gGameInfo->data[15] != 0) {
                                if (gSaveContext.unk_14 == 0) {
                                    Message_StartTextbox(globalCtx, 0x1B8CU, NULL);
                                } else {
                                    Message_StartTextbox(globalCtx, 0x1B8DU, NULL);
                                }
                                globalCtx->msgCtx.ocarinaMode = 0x13;
                                phi_a3_2 = &D_801C6A7C;
                            } else {
                                Message_StartTextbox(globalCtx, 0x1B8BU, NULL);
                                globalCtx->msgCtx.ocarinaMode = 4;
                                phi_a3_2 = &D_801C6A7C;
                            }
                        } else {
                            D_801C6A7C = 0xFF;
                            Message_StartTextbox(globalCtx, 0x1B95U, NULL);
                            globalCtx->msgCtx.ocarinaMode = 0x27;
                            phi_a3_2 = &D_801C6A7C;
                        }
                    } else if (temp_v0_23 == 0xD) {
                        if (globalCtx->interfaceCtx.restrictions.unk_313 == 0) {
                            temp_v1_7 = gSaveContext.day;
                            if (((temp_v1_7 % 5) != 3) || (gSaveContext.isNight == 0)) {
                                if (gSaveContext.isNight != 0) {
                                    Message_StartTextbox(globalCtx, *(&D_801D0462 + ((temp_v1_7 % 5) * 2)), NULL);
                                } else {
                                    Message_StartTextbox(globalCtx, *(&D_801D045A + ((temp_v1_7 % 5) * 2)), NULL);
                                }
                                globalCtx->msgCtx.ocarinaMode = 0x15;
                                phi_a3_2 = &D_801C6A7C;
                            } else {
                                Message_StartTextbox(globalCtx, 0x1B94U, NULL);
                                globalCtx->msgCtx.ocarinaMode = 4;
                                phi_a3_2 = &D_801C6A7C;
                            }
                        } else {
                            D_801C6A7C = 0xFF;
                            Message_StartTextbox(globalCtx, 0x1B95U, NULL);
                            globalCtx->msgCtx.ocarinaMode = 0x27;
                            phi_a3_2 = &D_801C6A7C;
                        }
                    } else if ((temp_v1_6 == 0x32) && ((temp_v0_24 = (globalCtx + 0x10000)->unk6932, (temp_v0_24 == 1)) || (temp_v0_24 == 3) || (temp_v0_24 == 0xD) || (temp_v0_24 == 0x2A))) {
                        globalCtx->msgCtx.ocarinaMode = 4;
                        if (phi_ra->unk202E == 9) {
                            globalCtx->msgCtx.ocarinaMode = 1;
                        }
                    }
                    *phi_a3_2 = 0xFF;
                    return;
                }
                // Duplicate return node #352. Try simplifying control flow for better match
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 13:
            if (~(globalCtx->state.input[0].press.button | ~0x4000) == 0) {
                func_8019C300(0, 0, 0x10000);
                globalCtx->msgCtx.ocarinaMode = 4;
                func_801477B4(globalCtx);
                return;
            }
            globalCtx->msgCtx.unk12048 = 0xFF;
            return;
        case 32:
            temp_v1_8 = phi_ra->unk202C;
            if ((temp_v1_8 != 0x41) && (temp_v1_8 != 0x42) && (sp20 = phi_ra, (func_80147624(globalCtx) != 0))) {
                func_80152434(globalCtx, phi_ra->unk202C);
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 43:
            if (~(globalCtx->state.input[0].press.button | ~0x4000) == 0) {
                sp30 = &globalCtx->msgCtx;
                func_8019CD08(0, 0, 0x10000);
                play_sound(0x4827U);
                func_801477B4(globalCtx);
                globalCtx->msgCtx.msgMode = 0x2C;
                return;
            }
            globalCtx->msgCtx.unk12048 = 0xFF;
            return;
        case 69:
            globalCtx->msgCtx.unk1203C = (s16) (phi_ra->unk203C + gGameInfo->data[1417]);
            if ((s32) phi_ra->unk203C >= 0xFF) {
                globalCtx->msgCtx.unk1203C = 0xFF;
                globalCtx->msgCtx.msgMode = 0x46;
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 70:
            globalCtx->msgCtx.unk1201E = (s16) (phi_ra->unk201E + gGameInfo->data[1417]);
            if ((s32) phi_ra->unk201E >= 0xFF) {
                globalCtx->msgCtx.unk1201E = 0xFF;
                globalCtx->msgCtx.msgMode = 0x47;
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 71:
            globalCtx->msgCtx.unk12023 = phi_ra->unk2023 - 1;
            if (phi_ra->unk2023 == 0) {
                globalCtx->msgCtx.msgMode = 0x48;
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 72:
            globalCtx->msgCtx.unk1201E = (s16) (phi_ra->unk201E - gGameInfo->data[1414]);
            if ((s32) phi_ra->unk201E <= 0) {
                globalCtx->msgCtx.unk1201E = 0;
                globalCtx->msgCtx.msgMode = 0x49;
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 73:
            globalCtx->msgCtx.unk1203C = (s16) (phi_ra->unk203C - gGameInfo->data[1414]);
            if ((s32) phi_ra->unk203C <= 0) {
                temp_v0_25 = phi_ra->unk1F04;
                if (((s32) temp_v0_25 >= 0x1BB2) && ((s32) temp_v0_25 < 0x1BB7) && ((globalCtx->actorCtx.unk5 & 2) != 0)) {
                    Message_StartTextbox(globalCtx, 0x5E6U, NULL);
                    Interface_ChangeAlpha(2U);
                    return;
                }
                if ((s32) temp_v0_25 >= 0x100) {

                }
                globalCtx->msgCtx.unk1203C = 0;
                globalCtx->msgCtx.unk11F10 = 0;
                globalCtx->msgCtx.msgMode = 0;
                globalCtx->msgCtx.unk11F04 = 0;
                globalCtx->msgCtx.unk12023 = 0;
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        case 74:
            globalCtx->state.unkA3 = 1;
            sp30 = &globalCtx->msgCtx;
            sp44 = gSaveContext.cutscene;
            sp3E = gSaveContext.time;
            sp40 = gSaveContext.day;
            func_80143B0C(globalCtx);
            temp_a0_5 = &globalCtx->sramCtx;
            gSaveContext.unk3DD3 = 0;
            sp2C = (PauseContext *) temp_a0_5;
            func_8014546C(temp_a0_5);
            temp_v0_26 = gSaveContext.fileNum;
            gSaveContext.day = sp40;
            gSaveContext.time = sp3E;
            gSaveContext.cutscene = sp44;
            if (temp_v0_26 != 0xFF) {
                temp_v1_9 = temp_v0_26 * 8;
                sp30 = &globalCtx->msgCtx;
                func_80147008(sp2C, *(&D_801C67C8 + temp_v1_9), *(&D_801C6818 + temp_v1_9));
                func_80147020((SramContext *) sp2C);
            }
            globalCtx->msgCtx.msgMode = 0x4B;
            return;
        case 75:
            if (gSaveContext.fileNum != 0xFF) {
                globalCtx->state.unkA3 = 1;
                if (globalCtx->sramCtx.status == 0) {
                    globalCtx->msgCtx.ocarinaMode = 0x16;
                    globalCtx->msgCtx.msgMode = 0x4C;
                    return;
                }
                // Duplicate return node #352. Try simplifying control flow for better match
                return;
            }
            globalCtx->msgCtx.ocarinaMode = 0x16;
            globalCtx->msgCtx.msgMode = 0x4C;
            return;
        case 77:
            globalCtx->state.unkA3 = 1;
            gSaveContext.isOwlSave = (u8) 1;
            sp30 = &globalCtx->msgCtx;
            func_80169D40(globalCtx);
            temp_a0_6 = &globalCtx->sramCtx;
            sp2C = (PauseContext *) temp_a0_6;
            func_8014546C(temp_a0_6);
            temp_v0_27 = gSaveContext.fileNum;
            if (temp_v0_27 != 0xFF) {
                temp_v1_10 = temp_v0_27 * 8;
                sp30 = &globalCtx->msgCtx;
                func_80147138(sp2C, *(&D_801C6840 + temp_v1_10), *(&D_801C6850 + temp_v1_10));
                func_80147150((SramContext *) sp2C);
            }
            globalCtx->msgCtx.msgMode = 0x4E;
            return;
        case 78:
            if (gSaveContext.fileNum != 0xFF) {
                globalCtx->state.unkA3 = 1;
                if (globalCtx->sramCtx.status == 0) {
                    globalCtx->msgCtx.ocarinaMode = 0x16;
                    globalCtx->msgCtx.msgMode = 0x4F;
                }
            } else {
                globalCtx->msgCtx.ocarinaMode = 0x16;
                globalCtx->msgCtx.msgMode = 0x4F;
            }
            if (phi_ra->unk1F22 == 0x4F) {
                gSaveContext.gameMode = 4;
                globalCtx->sceneLoadFlag = 0x14;
                globalCtx->unk_1887F = 2;
                globalCtx->nextEntranceIndex = 0x1C00;
                gSaveContext.cutscene = 0;
                gSaveContext.sceneSetupIndex = 0;
                return;
            }
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        default:
            globalCtx->msgCtx.unk12048 = 0xFF;
            // Duplicate return node #352. Try simplifying control flow for better match
            return;
        }
    } else {
    case 9:
    case 68:
    case 76:
    case 79:
    }
}
*/ 

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015680C.s")


void func_801586A4(GlobalContext *globalCtx) {
    globalCtx->msgCtx.unk12084 = &D_801C6B98;
    globalCtx->msgCtx.unk1208C = &D_801CFB08;
}
void Message_Init(GlobalContext *globalCtx) {
    Font *font;
    MessageContext *messageCtx = &globalCtx->msgCtx;

    func_801586A4(globalCtx);
    globalCtx->msgCtx.ocarinaMode = 0;
    messageCtx->msgMode = 0;
    messageCtx->unk11F10 = 0;
    messageCtx->unk11F04 = 0;
    messageCtx->unk12020 = 0;
    messageCtx->choiceIndex = 0;
    messageCtx->pad1202C = messageCtx->unk11FF2 = 0;
    messageCtx->unk1201E = 0xFF;
    View_Init( &messageCtx->view, globalCtx->state.gfxCtx);
    messageCtx->unk11EF8 = THA_AllocEndAlign16(&globalCtx->state.heap, 0x13C00);
    font = &globalCtx->msgCtx.font;
    Font_LoadOrderedFont(&globalCtx->msgCtx.font);
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

