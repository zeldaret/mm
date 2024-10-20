#include "text/message_data.h"

/*
 * The following two messages should be kept last and in this order.
 * Message 0xFFFD must be last to not break the message debugger.
 * Message 0xFFFC must be immediately before message 0xFFFD to not break Font_LoadOrderedFont.
 */

DEFINE_MESSAGE(0xFFFC, 0x00, 0x00,
MSG(
HEADER(0x0000, 0xFE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF)
)
)

DEFINE_MESSAGE(0xFFFD, 0x00, 0x00,
MSG(
HEADER(0x0000, 0xFE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF)
"end!"
)
)
