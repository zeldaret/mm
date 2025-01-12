#define MESSAGE_DATA_STATIC

#include "message_data_fmt_nes.h"

#define DEFINE_MESSAGE(textId, type, pos, msg) \
    const char _message_##textId[] = msg;

#include "assets/text/message_data.enc.h"

#undef DEFINE_MESSAGE
