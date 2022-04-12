#include "global.h"
#include "message_data_static.h"

void Message_FindCreditsMessage(GlobalContext* globalCtx, u16 textId) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = msgCtx->messageTableStaff;
    const char* segment = msgEntry->segment;
    const char* foundSegment;
    const char* nextSegment;

    while (msgEntry->textId != 0xFFFF) {
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            font->charBuf[font->unk_11D88][0] = msgEntry->typePos;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd = nextSegment - foundSegment;
            return;
        }
        msgEntry++;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/func_8015E7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/func_8015F8A8.s")
