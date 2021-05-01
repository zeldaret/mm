#ifndef _Z64CUTSCENE_COMMANDS_H_
#define _Z64CUTSCENE_COMMANDS_H_

#include "command_macros_base.h"
#include "z64cutscene.h"

/**
 * ARGS
 *   s32 totalEntries (e), s32 endFrame (n)
 * FORMAT
 *   eeeeeeee nnnnnnnn
 *   size = 0x8
 */
#define CS_BEGIN_CUTSCENE(totalEntries, endFrame) CMD_W(totalEntries), CMD_W(endFrame)

/**
 * Marks the end of a cutscene
 */
#define CS_END() 0xFFFFFFFF

#endif
