#ifndef MESSAGE_DATA_STATIC_H
#define MESSAGE_DATA_STATIC_H

#include "PR/ultratypes.h"

typedef struct MessageTableEntry {
    /* 0x0 */ u16 textId;
    /* 0x2 */ u8 typePos;
    /* 0x4 */ const char* segment;
} MessageTableEntry; // size = 0x8;

#define DEFINE_MESSAGE(textId, type, yPos, msg) \
    extern const char _message_##textId[];

#include "assets/text/message_data.h"

#undef DEFINE_MESSAGE

#define DEFINE_MESSAGE(textId, type, yPos, msg) \
    extern const char _message_##textId##_staff[];

#include "assets/text/message_data_staff.h"

#undef DEFINE_MESSAGE

#endif
