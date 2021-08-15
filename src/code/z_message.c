#include "global.h"

void func_80147520(void) {
    D_801CFC98 = 0xFF;
    D_801CFCA4[0] = D_801CFCA4[1] = D_801CFCA4[2] = D_801CFCA4[3]= D_801CFCA4[4] = D_801CFCA4[5] = D_801CFCA4[6] = D_801CFCA4[7]  = D_801CFCA4[8] = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147564.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147624.s")

#ifdef NON_MATCHING

u32 func_80147734(GlobalContext *globalCtx) {
    s32 ret_value;
    Input* controller;
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if(msgCtx->unk12020 == 0x10 ||msgCtx->unk12020 == 0x11){
        return CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A);
    }
    controller = CONTROLLER1(globalCtx);
    ret_value = CHECK_BTN_ALL(controller->press.button, BTN_A);
    if(ret_value == 0){
        ret_value = CHECK_BTN_ALL(controller->press.button, BTN_B);
        if(ret_value == 0){
            ret_value = CHECK_BTN_ALL(controller->press.button, BTN_CUP);
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

void func_80148CBC(GlobalContext *globalCtx, UNK_PTR puParm2, u8 arg2) {
    MessageContext* msgCtx;

    msgCtx = &globalCtx->msgCtx;
    msgCtx->unk11FF4 = 0x30;
    if (arg2  == 1) {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[1+msgCtx->choiceIndex];
    } else {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[msgCtx->choiceIndex];
    }
    func_80147818(globalCtx, puParm2, msgCtx->unk11FF4, msgCtx->unk11FF6);
}

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

void func_8014CC14(GlobalContext* globalCtx, u16 codePointIndex, s32* offset, f32* arg3, s16 arg4) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    
    Font_LoadChar(globalCtx, codePointIndex, temp1);
    msgCtx->unk11F24[arg4] = codePointIndex; 
    temp1 += 128;
    temp2 += (16.0f * msgCtx->unk12098);
    *offset = temp1;
    *arg3 = temp2;
}

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

void func_80152464(GlobalContext *globalCtx, u16 arg1) {
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

void func_80156758(GlobalContext *globalCtx) {
    Gfx* nextDisplayList;
    Gfx* _polyOpa;
    GraphicsContext* gfxCtx;

    gfxCtx = globalCtx->state.gfxCtx;
    OPEN_DISPS(gfxCtx);
    nextDisplayList = Graph_GfxPlusOne(_polyOpa = POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);
    if ((globalCtx->msgCtx.unk11F04 != 0x5E6) || (func_801690CC(globalCtx) == 0)) {
        func_801541D4(globalCtx, &nextDisplayList);
    }
    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(_polyOpa, nextDisplayList);
    gfxCtx->polyOpa.p = nextDisplayList;
    CLOSE_DISPS(gfxCtx);
}

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
    messageCtx->unk1202C = messageCtx->unk11FF2 = 0;
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


