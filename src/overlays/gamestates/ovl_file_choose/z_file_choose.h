#ifndef Z64_FILE_CHOOSE_H
#define Z64_FILE_CHOOSE_H

#include "global.h"

void FileChoose_Init(GameState* thisx);
void FileChoose_Destroy(GameState* thisx);

typedef struct {
    /* 0x00000 */ GameState state;
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
    /* 0x243E4 */ Vtx* unk_243E4;
    /* 0x243E8 */ Vtx* unk_243E8;
    /* 0x243EC */ Vtx* unk_243EC;
    /* 0x243F0 */ Vtx* unk_243F0;
    /* 0x243F4 */ u8   newf[6][4];
    /* 0x2440C */ u16  unk_2440C[4];
    /* 0x24414 */ u8   unk_24414[8][4];
    /* 0x24434 */ s16  healthCapacity[4];
    /* 0x2443C */ s16  health[4];
    /* 0x24444 */ u32  unk_24444[4];
    /* 0x24454 */ s8   unk_24454[4];
    /* 0x24458 */ u16  unk_24458[4];
    /* 0x24460 */ s16  unk_24460[4];
    /* 0x24468 */ u8   unk_24468[4];
    /* 0x2446C */ s16  rupees[4];
    /* 0x24474 */ u8   unk_24474[4];
    /* 0x24478 */ u8   unk_24478[4];
    /* 0x2447C */ u8   unk_2447C[4];
    /* 0x24480 */ s16  unk_24480;
    /* 0x24482 */ s16  unk_24482;
    /* 0x24484 */ s16  unk_24484;
    /* 0x24486 */ s16  unk_24486;
    /* 0x24488 */ s16  unk_24488;
    /* 0x2448A */ s16  unk_2448A;
    /* 0x2448C */ s16  unk_2448C;
    /* 0x2448E */ s16  unk_2448E;
    /* 0x24490 */ s16  unk_24490;
    /* 0x24492 */ s16  unk_24492[3];
    /* 0x24498 */ s16  unk_24498;
    /* 0x2449A */ s16  unk_2449A[6];
    /* 0x244A6 */ s16  unk_244A6;
    /* 0x244A8 */ s16  unk_244A8;
    /* 0x244AA */ s16  unk_244AA;
    /* 0x244AC */ s16  unk_244AC;
    /* 0x244AE */ s16  unk_244AE;
    /* 0x244B0 */ s16  unk_244B0[3];
    /* 0x244B6 */ s16  unk_244B6[2];
    /* 0x244BA */ s16  unk_244BA;
    /* 0x244BC */ s16  unk_244BC[3];
    /* 0x244C2 */ s16  unk_244C2[3];
    /* 0x244C8 */ s16  unk_244C8[3];
    /* 0x244CE */ s16  unk_244CE[3];
    /* 0x244D4 */ s16  unk_244D4[3];
    /* 0x244DA */ s16  unk_244DA[4];
    /* 0x244E2 */ s16  unk_244E2;
    /* 0x244E4 */ s16  unk_244E4;
    /* 0x244E6 */ s16  unk_244E6;
    /* 0x244E8 */ s16  unk_244E8;
    /* 0x244EA */ s16  unk_244EA[4];
    /* 0x244F2 */ s16  unk_244F2;
    /* 0x244F4 */ s16  unk_244F4;
    /* 0x244F6 */ s16  unk_244F6[2];
    /* 0x244FA */ s16  unk_244FA;
    /* 0x244FC */ s16  unk_244FC;
    /* 0x244FE */ s16  unk_244FE;
    /* 0x24500 */ s16  unk_24500;
    /* 0x24502 */ s16  unk_24502;
    /* 0x24504 */ s16  unk_24504;
    /* 0x24506 */ s16  unk_24506;
    /* 0x24508 */ s16  unk_24508;
    /* 0x2450A */ s16  unk_2450A;
    /* 0x2450C */ f32  unk_2450C;
    /* 0x24510 */ s16  unk_24510;
    /* 0x24512 */ s16  unk_24512;
    /* 0x24514 */ s16  unk_24514;
    /* 0x24516 */ s16  unk_24516;
    /* 0x24518 */ s16  unk_24518;
    /* 0x2451A */ s16  unk_2451A;
    /* 0x2451C */ s16  unk_2451C;
    /* 0x2451E */ s16  unk_2451E[5];
    /* 0x24528 */ s16  unk_24528;
    /* 0x2452A */ s16  unk_2452A;
    /* 0x2452C */ s16  unk_2452C[4];
    /* 0x24534 */ s16  unk_24534[4];
    /* 0x2453C */ s16  unk_2453C[4];
    /* 0x24544 */ s16  unk_24544[4];
    /* 0x2454C */ s16  unk_2454C;
    /* 0x2454E */ s16  unk_2454E;
    /* 0x24550 */ s16  unk_24550;
} FileChooseContext; // size = 0x24558

#endif
