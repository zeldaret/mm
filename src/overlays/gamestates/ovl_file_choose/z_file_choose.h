#ifndef Z64_FILE_CHOOSE_H
#define Z64_FILE_CHOOSE_H

#include "global.h"

void FileSelect_Init(GameState* thisx);
void FileSelect_Destroy(GameState* thisx);

typedef struct FileSelectState {
    /* 0x00000 */ GameState state;
    /* 0x000A4 */ Vtx* windowVtx;
    /* 0x000A8 */ u8* staticSegment;
    /* 0x000AC */ u8* parameterSegment;
    /* 0x000B0 */ u8* titleSegment;
    /* 0x000B8 */ View view;
    /* 0x00220 */ SramContext sramCtx;
    /* 0x00248 */ SkyboxContext skyboxCtx;
    /* 0x00470 */ MessageContext msgCtx;
    /* 0x12550 */ Font font;
    /* 0x242E0 */ EnvironmentContext envCtx;
    /* 0x243E0 */ Vtx* unk_243E0;
    /* 0x243E4 */ Vtx* windowContentVtx;
    /* 0x243E8 */ u8   newf2[2][6];
    /* 0x243F4 */ u8   newf[4][6];
    /* 0x2440C */ u16 unk_2440C[2];
    /* 0x24410 */ u16 unk_24410[2];
    /* 0x24414 */ u8 unk_24414[2][8]; // playername
    /* 0x24424 */ u8 unk_24424[2][8]; // playername
    /* 0x24434 */ s16 healthCapacity[2];
    /* 0x24438 */ u16 unk_24438[2];
    /* 0x2443C */ s16 health[2];
    /* 0x24440 */ u16 unk_24440[2];
    /* 0x24444 */ u32 unk_24444[2];
    /* 0x2444C */ u32 unk_2444C[2];
    /* 0x24454 */ s8 unk_24454[2];
    /* 0x24456 */ u8 unk_24456[2];
    /* 0x24458 */ u16 unk_24458[2];
    /* 0x2445C */ u16 unk_2445C[2];
    /* 0x24460 */ s16 unk_24460[2];
    /* 0x24464 */ s16 unk_24464[2];
    /* 0x24468 */ u8 unk_24468[2];
    /* 0x2446A */ u8 unk_2446A[2];
    /* 0x2446C */ s16 rupees[2];
    /* 0x24470 */ s16 unk_24470[2];
    /* 0x24474 */ u8 unk_24474[2];
    /* 0x24476 */ s8 unk_24476[2];
    /* 0x24478 */ u8 maskCount[2];
    /* 0x2447A */ s8 unk_2447A[2];
    /* 0x2447C */ s8 heartPieceCount[2];
    /* 0x2447E */ s8 unk_2447E[2];
    /* 0x24480 */ s16  buttonIndex;
    /* 0x24482 */ s16  confirmButtonIndex;
    /* 0x24484 */ s16  menuMode;
    /* 0x24486 */ s16  configMode;
    /* 0x24488 */ s16  unk_24488;
    /* 0x2448A */ s16  nextConfigMode;
    /* 0x2448C */ s16  selectMode;
    /* 0x2448E */ s16  unk_2448E;
    /* 0x24490 */ s16  unk_24490;
    /* 0x24492 */ s16  fileNamesY[3];
    /* 0x24498 */ s16  actionTimer;
    /* 0x2449A */ s16  buttonYOffsets[6];
    /* 0x244A6 */ s16  fileNum;
    /* 0x244A8 */ s16  warningLabel;
    /* 0x244AA */ s16  warningButtonIndex;
    /* 0x244AC */ s16  titleLabel;
    /* 0x244AE */ s16  nextTitleLabel;
    /* 0x244B0 */ s16  windowColor[3];
    /* 0x244B6 */ s16  titleAlpha[2];
    /* 0x244BA */ s16  windowAlpha;
    /* 0x244BC */ s16  fileButtonAlpha[3];
    /* 0x244C2 */ s16  nameBoxAlpha[3];
    /* 0x244C8 */ s16  nameAlpha[3];
    /* 0x244CE */ s16  connectorAlpha[3];
    /* 0x244D4 */ s16  fileInfoAlpha[3];
    /* 0x244DA */ s16  actionButtonAlpha[2];
    /* 0x244DA */ s16  confirmButtonAlpha[2];
    /* 0x244E2 */ s16  optionButtonAlpha;
    /* 0x244E4 */ s16  nameEntryBoxAlpha;
    /* 0x244E6 */ s16  controlsAlpha;
    /* 0x244E8 */ s16  emptyFileTextAlpha;
    /* 0x244EA */ s16  highlightColor[4]; // last elt may be separate
    /* 0x244F2 */ s16  highlightPulseDir;
    /* 0x244F4 */ s16  unk_244F4;
    /* 0x244F6 */ s16  confirmButtonTexIndices[2];
    /* 0x244FA */ s16  inputTimerX;
    /* 0x244FC */ s16  inputTimerY;
    /* 0x244FE */ s16  stickXDir;
    /* 0x24500 */ s16  stickYDir;
    /* 0x24502 */ s16  stickRelX;
    /* 0x24504 */ s16  stickRelY;
    /* 0x24506 */ s16  nameEntryBoxPosX;
    /* 0x24508 */ s16  windowPosX;
    /* 0x2450A */ s16  screenFillAlpha;
    /* 0x2450C */ f32  windowRot;
    /* 0x24510 */ s16  kbdButton;
    /* 0x24512 */ s16  unk_24512;
    /* 0x24514 */ s16  unk_24514;
    /* 0x24516 */ s16  unk_24516;
    /* 0x24518 */ s16  kbdX;
    /* 0x2451A */ s16  kbdY;
    /* 0x2451C */ s16  unk_2451C;
    /* 0x2451E */ s16  unk_2451E[5];
    /* 0x24528 */ s16  highlightTimer;
    /* 0x2452A */ s16  unk_2452A;
    /* 0x2452C */ s16  unk_2452C[4];
    /* 0x24534 */ s16  unk_24534[4];
    /* 0x2453C */ s16  unk_2453C[4];
    /* 0x24544 */ s16  unk_24544[4];
    /* 0x2454C */ s16  unk_2454C;
    /* 0x2454E */ s16  unk_2454E;
    /* 0x24550 */ s16  unk_24550;
} FileSelectState; // size = 0x24558

#endif
