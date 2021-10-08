#include "global.h"

void func_80147520(void) {
    D_801CFC98 = 0xFF;
    D_801CFCA4[0] = D_801CFCA4[1] = D_801CFCA4[2] = D_801CFCA4[3]= D_801CFCA4[4] = D_801CFCA4[5] = D_801CFCA4[6] = D_801CFCA4[7]  = D_801CFCA4[8] = 0;
}

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


void func_80147564(GlobalContext *globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    
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


//Message_ShouldAdvance
s32 func_80147624(GlobalContext *globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Input* controller = CONTROLLER1(globalCtx);

    if ((msgCtx->unk12020 == 0x10) || (msgCtx->unk12020 == 0x11)) {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
             
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    }else{
        if(CHECK_BTN_ALL(controller->press.button, BTN_A) ||  CHECK_BTN_ALL(controller->press.button,BTN_B) || CHECK_BTN_ALL(controller->press.button, BTN_CUP)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A) ||  CHECK_BTN_ALL(controller->press.button,BTN_B) || CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

#ifdef NON_MATCHING

//Message_ShouldAdvance_Silent
s32 func_80147734(GlobalContext *globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Input* controller = CONTROLLER1(globalCtx);

    if(msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11){
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    }else{
       return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) 
            ||  CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
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

void func_80148B98(GlobalContext *globalCtx, u8 bParm2) {
    static s16 held = 0;
    MessageContext *msgCtx = &globalCtx->msgCtx;
    Input* curInput = CONTROLLER1(globalCtx);
    
    if ((curInput->rel.stick_y > 29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex--;
        if (msgCtx->choiceIndex > 128) {
            msgCtx->choiceIndex = 0;
        }else{
            play_sound(NA_SE_SY_CURSOR);
        }
        return;
    }
    
    else if ((curInput->rel.stick_y < -29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex++;
        if (msgCtx->choiceIndex > bParm2) {
            msgCtx->choiceIndex = bParm2;
        }else{
            play_sound(NA_SE_SY_CURSOR);
        }
        return;
    }else{
        if (ABS_ALT(curInput->rel.stick_y) < 30) {
            held = 0;
        }
    }
}

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


//Message_FindMessageSegment(globalCtx, textId)
void func_80149EBC(GlobalContext *globalCtx, u16 textId) {
    char* foundSegment;
    char* nextSegment;
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Font* font = &msgCtx->font;
    UnkMsgStruct* msgEntry = &msgCtx->unk12080[0];
    char* segment = msgEntry->segment;

    while(msgEntry->textId != 0xFFFF){
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd =  nextSegment - foundSegment;
            return;
        }
        msgEntry++;
    }

    msgEntry = &msgCtx->unk12080[0];
    foundSegment = msgEntry->segment;
    msgEntry++;
    nextSegment = msgEntry->segment;
    font->messageStart = foundSegment - segment;
    font->messageEnd = nextSegment - foundSegment;

    
}

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

void func_8014CCB4(GlobalContext* globalCtx, s16* arg1, s32* arg2, f32* arg3) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s16 t = *arg1;
    s32 k = *arg2;
    f32 f = *arg3;

    Font_LoadChar(globalCtx, 0x838BU, k);
    k += 0x80;
    msgCtx->unk11F24[t] = 0x838B;
    t += 1;
    Font_LoadChar(globalCtx, 0x8373U, k);
    k += 0x80;
    msgCtx->unk11F24[t] = 0x8373;
    t += 1;
    Font_LoadChar(globalCtx, 0x815CU, k);
    k += 0x80;
    msgCtx->unk11F24[t] = 0x815C;

    //k = (k + 10);
    f += 16.0f * msgCtx->unk12098 * 3.0f;
    *arg1 = t;
    *arg2 = k;
    *arg3 = f;
}

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


void func_80151938(GlobalContext* globalCtx, u16 textId) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;

    msgCtx->unk11F10 = 0;
    func_80150D08(globalCtx, (u32)textId);
    func_80150A84(globalCtx);
    msgCtx->msgMode = 5;
    msgCtx->unk12023 = 8;
    msgCtx->unk12024 = 0;
    
    if (interfaceCtx->unk_222 == 0) {
        if (textId != 0x1B93) {
            func_8011552C(globalCtx, 0x10);
        }
        else if (textId != 0xF8) {
            func_8011552C(globalCtx, 6);
        }
    }
    msgCtx->unk1203C = msgCtx->unk1203A;
    if (globalCtx->pauseCtx.unk_1F0 != 0) {
        msgCtx->unk12004 = 0x22; 
        msgCtx->unk12006 = 0x15E;
        func_80149C18(globalCtx);
        msgCtx->unk12023 = 1;
    }
}

void func_80151A68(GlobalContext *globalCtx, u16 param_2) {
    MessageContext *msgCtx = &globalCtx->msgCtx;
    u32 temp = 0x1E;
    
    msgCtx->unk11F10 = 0;
    func_80150D08(globalCtx, param_2);
    func_80150A84(globalCtx);
    func_8015B198(globalCtx);
    msgCtx->msgMode = 0x45;
    msgCtx->unk12024 = 0;
    msgCtx->unk1203C = (msgCtx->unk1203A = (msgCtx->unk1201E = 0));
    msgCtx->unk12023 = 0x1E;
    if ((((s32) msgCtx->unk11F04) >= 0x1BB2) && (((s32) msgCtx->unk11F04) < 0x1BB7))
    {
        XREG(74) = 0x6A;
        XREG(75) = 0;
        XREG(77) = 0x58;
        XREG(76) = 0x44;
    }
    else
    {
        XREG(74) = 0x42;
        XREG(75) = temp;
        XREG(77) = 0x3C;
        XREG(76) = 0x1C;
        msgCtx->unk11F1A[0] = (msgCtx->unk11F1A[1] = (msgCtx->unk11F1A[2] = 0));
        Interface_ChangeAlpha(1U);
    }
}


extern u16 D_801C6B28[];

void func_80151BB4(GlobalContext* globalCtx, u8 uParm2) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    u8 temp = uParm2;

    if (CHECK_QUEST_ITEM(18)) { // CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)
        if (((gSaveContext.weekEventReg[D_801C6B28[uParm2] >> 8]) & (u8)D_801C6B28[uParm2]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    }
    else if (uParm2 >= 20) {
        //temp = uParm2;
        if (((gSaveContext.weekEventReg[D_801C6B28[uParm2] >> 8]) & (u8)D_801C6B28[uParm2]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    }
}


extern u16 D_801C6AB8[];
//extern ? D_801C6B28;

u32 func_80151C9C(GlobalContext *globalCtx) {
    MessageContext* msgCtx;
    u8 flag;

    msgCtx = &globalCtx->msgCtx;
    while(1){
        if(msgCtx->unk120B1 == 0){
            return 0;
        }
        msgCtx->unk120B1--;


        if (((gSaveContext.weekEventReg[ D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]>>8]) & (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]) == 0) {
            flag = gSaveContext.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]>>8];
            gSaveContext.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]>>8] = flag | (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]];
            if((D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]] != 0) && (CHECK_QUEST_ITEM(0x12))){ // CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)
                func_80151938(globalCtx, D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]]);
                play_sound(NA_SE_SY_SCHEDULE_WRITE);
                return 1;
            }
        }
    }
}

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


//Spawn song effect?
void func_80152EC0(GlobalContext *globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Actor* actor = (Actor*)PLAYER;
    
    if(1){}
    if ((msgCtx->songPlayed < 0x17) && (msgCtx->songPlayed != 0xE) && ((msgCtx->ocarinaAction < 0x43) || (msgCtx->ocarinaAction >= 0x47))) {
        msgCtx->unk120B0 = 1;
        if (msgCtx->songPlayed != 0x16) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, D_801D02D8[msgCtx->songPlayed], actor->world.pos.x, actor->world.pos.y, actor->world.pos.z, 0,  0,  0, D_801D02F8[msgCtx->songPlayed]);
            return;
        }
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xF6, actor->world.pos.x, actor->world.pos.y, actor->world.pos.z, 0, 0,  0,  0);
    }
}


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
    messageCtx->ocarinaAction = messageCtx->unk11FF2 = 0;
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


