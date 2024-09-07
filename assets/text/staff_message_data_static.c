#define MESSAGE_DATA_STATIC

#include "message_data_fmt_staff.h"

#define DEFINE_MESSAGE(textId, type, pos, msg) \
    const char _message_##textId##_staff[] = msg;

#include "assets/text/message_data_staff.enc.h"

#undef DEFINE_MESSAGE
