#include "global.h"

//Message_FindMessageStaff(globalCtx, textId)
void func_8015E750(GlobalContext *globalCtx, u16 textId) {
    const char* foundSegment;
    const char* nextSegment;
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = msgCtx->unk1208C;
    const char* segment = msgEntry->segment;

     while(msgEntry->textId != 0xFFFF){
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            font->charBuf[font->unk_11D88][0] = msgEntry->typePos;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd =  nextSegment - foundSegment;
            return;
        }
        msgEntry++;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/func_8015E7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/func_8015F8A8.s")
