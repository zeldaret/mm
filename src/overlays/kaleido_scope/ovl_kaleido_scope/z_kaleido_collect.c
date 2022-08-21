/*
 * File: z_kaleido_collect.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Quest Page
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point);

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

s16 D_8082AED0[] = { 120, 60, 2, 80 };

s16 D_8082AED8[] = { 20, 4, 20, 10 };

s16 D_8082AEE0 = 0;

s32 D_8082AEE4[] = { 0, 0, 0 };

s32 D_8082AEF0[] = { 0, 0, 0, 0, 0 };

// OoT D_8082A070
s16 D_8082AF04[][4] = {
    { 255, 0, 0, 255 },
    { 255, 70, 0, 150 },
    { 255, 70, 0, 150 },
    { 255, 0, 0, 255 },
};
// OoT D_8082A090
s16 D_8082AF24[][3] = {
    { 0, 0, 0 },  { 0, 0, 0 },  { 0, 0, 0 },    { 0, 0, 0 },   { 0, 0, 0 },   { 0, 0, 0 },
    { 0, 60, 0 }, { 90, 0, 0 }, { 0, 40, 110 }, { 80, 40, 0 }, { 70, 0, 90 }, { 90, 90, 0 },
};
// OoT D_8082A0D8
s16 D_8082AF6C[] = {
    255, 255, 255, 255, 255, 255,
};
// OoT D_8082A0E4
s16 D_8082AF78[] = {
    255, 255, 255, 255, 255, 255,
};
// OoT D_8082A0F0
s16 D_8082AF84[] = {
    150, 150, 150, 150, 150, 150,
};
s16 D_8082AF90 = 20;
s16 D_8082AF94 = 0;
s16 D_8082AF98 = 0;
s16 D_8082AF9C = 0;
s16 D_8082AFA0 = 0;
s16 D_8082AFA4 = 0;
s16 D_8082AFA8 = 20;
s16 D_8082AFAC = 0;

// OoT D_8082A130
TexturePtr D_8082AFB0[] = {
    gOcarinaATex, gOcarinaCDownTex, gOcarinaCRightTex, gOcarinaCLeftTex, gOcarinaCUpTex,
};

// OoT D_8082A164
s16 D_8082AFC4[] = {
    150, 255, 100, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};

// OoT D_8082A17C
s16 D_8082AFDC[] = {
    255, 80, 150, 160, 100, 240, 255, 255, 255, 255, 255, 255,
};

// OoT D_8082A194
s16 D_8082AFF4[] = {
    100, 40, 255, 0, 255, 100, 255, 255, 255, 255, 255, 255,
};

void* D_8082B00C[] = {
    0x08053000, 0x08054000, 0x08055000, 0x08056000, 0x08057000, 0x08058000,
};
s16 D_8082B024 = 1;
s16 D_8082B028 = 0;

// OoT D_8082A1AC
s16 D_8082B02C[][4] = {
    { -1, 3, 2, 1 },    { 0, 4, 3, -2 },   { 0, 5, 22, 3 },   { 0, 4, 2, 1 },     { 1, 20, 5, -2 },  { 2, 19, 16, 4 },
    { 12, -1, -3, 7 },  { 13, -1, 6, 8 },  { 14, -1, 7, 9 },  { 15, -1, 8, 10 },  { 16, -1, 9, 19 }, { 17, -1, 10, 5 },
    { 18, 6, -3, 13 },  { 18, 7, 12, 14 }, { 22, 8, 13, 15 }, { 22, 9, 14, 16 },  { 22, 10, 15, 5 }, { 22, 11, 16, 5 },
    { -1, 12, -3, 22 }, { 5, -1, 10, 20 }, { 4, -1, 19, -2 }, { 19, 12, -3, 22 }, { -1, 16, 18, 2 },
};

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawQuestStatus.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateQuestStatus.s")

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point) {
    pauseCtx->cursorPoint[PAUSE_QUEST] = point;

    return 1;
}
