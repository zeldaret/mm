#define MESSAGE_DATA_STATIC

#include "versions.h"
#if MM_VERSION < N64_US
#include "message_data_fmt_jpn.h"
#else
#include "message_data_fmt_nes.h"
#endif

#define DEFINE_MESSAGE(textId, type, pos, msg) \
    const char _message_##textId[] = msg;

#include "assets/text/message_data.enc.h"

#undef DEFINE_MESSAGE
