#ifndef Z_KALEIDO_SCOPE_H
#define Z_KALEIDO_SCOPE_H

#include "global.h"

// NES
void func_80821984(PlayState* play, s16 cursorSpecialPos);

// Map
void func_8081FB1C(PlayState* play);

// Debug
void KaleidoScope_DrawDebugEditor(PlayState* play);
void KaleidoScope_UpdateDebugEditor(PlayState* play);

#endif
