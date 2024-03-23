#ifndef Z64DLF_H
#define Z64DLF_H

struct GameStateOverlay;

void Overlay_LoadGameState(struct GameStateOverlay* overlayEntry);
void Overlay_FreeGameState(struct GameStateOverlay* overlayEntry);

#endif
