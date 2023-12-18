#include "message_data_static.h"
#include "PR/mbi.h"

#define DEFINE_MESSAGE(textId, typePos, msg) { textId, typePos, _message_##textId },

MessageTableEntry D_801C6B98[] = {
#include "assets/text/message_data.h"
    { 0xFFFF, 0, NULL },
};

#undef DEFINE_MESSAGE

#define DEFINE_MESSAGE(textId, typePos, msg) { textId, typePos, _message_##textId##_staff },

MessageTableEntry D_801CFB08[] = {
#include "assets/text/staff_message_data.h"
    { 0xFFFF, 0, NULL },
};

#undef DEFINE_MESSAGE
