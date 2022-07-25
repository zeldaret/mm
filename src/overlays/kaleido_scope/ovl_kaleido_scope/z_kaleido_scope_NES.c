/*
 * File: z_kaleido_scope_NES.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

void* D_8082B700[] = {
    0x08064440, 0x0806E440, 0x08077A40, 0x08081040, 0x0808A640, 0x0D003A00, 0x0806EE40, 0x08078440,
    0x08081A40, 0x0808B040, 0x08065840, 0x0806F840, 0x08078E40, 0x08082440, 0x0808BA40,
};
void* D_8082B73C[] = {
    0x0D004400, 0x08070240, 0x08079840, 0x08082E40, 0x0808C440, 0x0D004E00, 0x08070C40, 0x0807A240,
    0x08083840, 0x0808CE40, 0x0D005800, 0x08071640, 0x0807AC40, 0x08084240, 0x0808D840,
};
void* D_8082B778[] = {
    0x08068040, 0x08072040, 0x0807B640, 0x08084C40, 0x0808E240, 0x0D006200, 0x08072A40, 0x0807C040,
    0x08085640, 0x0808EC40, 0x08069440, 0x08073440, 0x0807CA40, 0x08086040, 0x0808F640,
};
void* D_8082B7B4[] = {
    0x0D006C00, 0x08073E40, 0x0807D440, 0x08086A40, 0x08090040, 0x0D007600, 0x08074840, 0x0807DE40,
    0x08087440, 0x08090A40, 0x0D008000, 0x08075240, 0x0807E840, 0x08087E40, 0x08091440,
};

s16 D_8082B7F0[] = {
    0x0050, 0x0040, 0x0040, 0x0040, 0x0010, 0x0040, 0x0070, 0x0070, 0x0030, 0x0040, 0x0040, 0x0040,
    0x0040, 0x0030, 0x0040, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
};
s16 D_8082B838[] = {
    0x0028, 0x001F, 0x0035, 0x0035, 0x0035, 0x0034, 0x0023, 0x0023, 0x0020, 0x0040, 0x0040, 0x0040,
    0x0040, 0x0052, 0x003D, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C,
};

s16 D_8082B880 = 0;
s16 D_8082B884 = 0;
s16 D_8082B888 = 0;
s16 D_8082B88C = 255;
s16 D_8082B890 = 0;
s16 D_8082B894 = 0;
s16 D_8082B898 = 0;
s16 D_8082B89C = 0;
s16 D_8082B8A0 = 0;
s16 D_8082B8A4 = 0;
s16 D_8082B8A8 = 255;
s16 D_8082B8AC = 0;
s16 D_8082B8B0 = 0;

s16 D_8082B8B4 = false;

f32 D_8082B8B8[] = {
    -4.0f, 4.0f, 4.0f, 4.0f, 4.0f, -4.0f, -4.0f, -4.0f,
};

f32 D_8082B8D8[] = {
    -4.0f, -4.0f, -4.0f, 4.0f, 4.0f, 4.0f, 4.0f, -4.0f,
};

s16 D_8082B8F8[] = {
    PAUSE_MAP, PAUSE_MASK, PAUSE_QUEST, PAUSE_ITEM, PAUSE_MASK, PAUSE_MAP, PAUSE_ITEM, PAUSE_QUEST,
};

f32 D_8082B908 = 0.0f;
f32 D_8082B90C = 0.0f;
f32 D_8082B910 = 40.0f;
f32 D_8082B914 = -40.0f;

s32 D_8082B918 = 0;

s32 D_8082B91C = 0;

s16 D_8082B920 = 10;

u8 D_8082B924[] = {
    0x00, 0x14, 0x00, 0x04, 0x00, 0x14, 0x00, 0x0A, 0x0F, 0x1F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    0x07, 0x07, 0x03, 0x0F, 0x07, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x03, 0x0F, 0x00, 0x00,
};

s16 D_8082B944 = 0x42;

s16 D_8082B948[][3] = {
    { 0x00FF, 0x00FF, 0x00FF }, { 0x00FF, 0x00FF, 0x00FF }, { 0x00FF, 0x00FF, 0x0000 },
    { 0x00FF, 0x00FF, 0x0000 }, { 0x0064, 0x0096, 0x00FF }, { 0x0064, 0x00FF, 0x00FF },
};

s16 D_8082B96C[][3] = {
    { 0x0000, 0x0000, 0x0000 }, { 0x00AA, 0x00AA, 0x00AA }, { 0x0000, 0x0000, 0x0000 },
    { 0x00FF, 0x00A0, 0x0000 }, { 0x0000, 0x0000, 0x0064 }, { 0x0000, 0x0096, 0x00FF },
};

s16 D_8082B990 = 10;
s16 D_8082B994 = 0;

s32 D_8082B998[] = {
    0x0D003300,
    0x0D002700,
    0x0D002B00,
    0x0D002F00,
};

s32 D_8082B9A8[] = {
    0x0D002B00,
    0x0D002F00,
    0x0D003300,
    0x0D002700,
};

s16 D_8082B9B8[] = {
    0x00B4, 0x00D2, 0x00FF, 0x00DC, 0x0064, 0x0064, 0x0096, 0x00DC,
};

s16 D_8082B9C8 = 20;

s32 D_8082B9CC = 0;

s16 D_8082B9D0[] = {
    0x00B4, 0x00D2, 0x00FF, 0x00DC, 0x0064, 0x0064, 0x0096, 0x00DC,
};

s16 D_8082B9E0 = 20;

s32 D_8082B9E4 = 0;

s32 D_8082B9E8 = 0;

s32 D_8082B9EC = 0;

s16 D_8082B9F0[] = {
    0xFFEB, 0xFF98, 0xFFB4, 0xFFD0, 0xFF98, 0xFFD8,
};

s32 D_8082B9FC = 0;

s16 D_8082BA00[] = {
    0xFFD7, 0x0009, 0x002B, 0xFFEB, 0xFFDB, 0x002B, 0xFFBB, 0xFFBB, 0xFFE0, 0xFF93, 0xFFD3, 0xFF93,
    0xFFD3, 0x003B, 0xFFFB, 0xFFBA, 0xFFCC, 0xFFF5, 0xFFFE, 0x0008, 0x0002, 0x0001, 0x002B, 0x0034,
    0x0036, 0x003E, 0xFFB0, 0xFFC0, 0xFFF7, 0xFFFD, 0xFFF9, 0xFFF0, 0xFFFF, 0x0017, 0x002C, 0x0036,
};

s16 D_8082BA48[] = {
    0xFFB4, 0xFFC6, 0x000A, 0xFFC6, 0x000A, 0x0000,
};

s32 D_8082BA54 = 0;

s32 D_8082BA58 = 0;

s16 D_8082BA5C[] = {
    0x0080, 0x0018, 0x0018, 0x0018, 0x0020, 0x0018,
};

s32 D_8082BA68 = 0;

s16 D_8082BA6C[] = {
    0x0098, 0x0030, 0x0030, 0x0030, 0x0030, 0x0000,
};

s32 D_8082BA78 = 0;

s32 D_8082BA7C = 0;

s16 D_8082BA80[] = {
    0x0036, 0xFFD6, 0xFFD6, 0xFFD6, 0xFFE8, 0x0032,
};

s32 D_8082BA8C = 0;

s16 D_8082BA90[] = {
    0x000B, 0x0016, 0xFFF0, 0xFFF0, 0xFFF0, 0x003B, 0x0018, 0x003B, 0xFFF5, 0xFFFB, 0xFFFB, 0x003B,
    0x003B, 0x0027, 0x001F, 0xFFF6, 0xFFDC, 0xFFED, 0xFFCB, 0xFFE5, 0xFFFE, 0x0029, 0x000B, 0xFFFD,
    0x002D, 0x0012, 0xFFF8, 0xFFDA, 0x0027, 0x001A, 0x0001, 0xFFF9, 0xFFE4, 0xFFE5, 0xFFFF, 0x0018,
};

s16 D_8082BAD8[] = {
    0x0024, 0x000A, 0x000A, 0xFFFA, 0xFFFA, 0x0000,
};

s32 D_8082BAE4 = 0;

s32 D_8082BAE8 = 0;

s16 D_8082BAEC[] = {
    0x0010, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
};

s32 D_8082BAF8 = 0;

s16 D_8082BAFC[] = {
    0x0010, 0x0030, 0x0030, 0x0010, 0x0010, 0x0000,
};

void* D_8082BB08[] = {
    &D_8082B9E8, &D_8082B9EC, &D_8082B9F0, &D_8082B9FC, &D_8082BA00, &D_8082BA48,
};

void* D_8082BB20[] = {
    &D_8082BA54, &D_8082BA58, &D_8082BA5C, &D_8082BA68, &D_8082B7F0, &D_8082BA6C,
};

void* D_8082BB38[] = {
    &D_8082BA78, &D_8082BA7C, &D_8082BA80, &D_8082BA8C, &D_8082BA90, &D_8082BAD8,
};

void* D_8082BB50[] = {
    &D_8082BAE4, &D_8082BAE8, &D_8082BAEC, &D_8082BAF8, &D_8082B838, &D_8082BAFC,
};

s16 D_8082BB68[] = {
    0x000E, 0xFFFE, 0xFFFE, 0xFFEE, 0xFFEE, 0x0000,
};

s16 D_8082BB74[] = {
    0x002D, 0x004E, 0x000A, 0x002D, 0x0050, 0x000B, 0xFF93, 0xFFA9, 0xFFBF, 0xFFD7, 0xFFED, 0xFFEE, 0xFF93, 0xFFA9,
    0xFFBF, 0xFFD7, 0xFFED, 0xFFEE, 0xFF99, 0x0007, 0x0052, 0xFF92, 0xFFCA, 0xFF9E, 0xFFAA, 0xFFB6, 0xFFC2, 0xFFCE,
    0xFFDA, 0xFFE6, 0xFFF2, 0xFF9E, 0xFFAA, 0xFFB6, 0xFFC2, 0xFFCE, 0xFFDA, 0xFFE6, 0xFFF2, 0x0000,
};

s16 D_8082BBC4[] = {
    0x003E, 0x002A, 0x002A, 0x0014, 0xFFF7, 0xFFF7, 0xFFEC, 0xFFEC, 0xFFEC, 0xFFEC, 0xFFEC, 0xFFEC, 0x0002, 0x0002,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0036, 0xFFD4, 0xFFD4, 0x0022, 0x003A, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC,
    0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0xFFCC, 0x0000,
};

s16 D_8082BC14[] = {
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0020, 0x0020, 0x0020, 0x0018, 0x0030, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0000,
};

s16 D_8082BC64[] = {
    0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
    0x0018, 0x0018, 0x0018, 0x0018, 0x0020, 0x0020, 0x0020, 0x0018, 0x0030, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0000,
};

f32 D_8082BCB4[] = {
    -62.0f, -36.0f, -10.0f, 16.0f, 42.0f, 68.0f,
};

f32 D_8082BCCC[] = {
    31.0f,
    5.0f,
    -21.0f,
    -47.0f,
};

f32 D_8082BCDC[] = {
    -49.0f, -35.0f, -3.0f, 4.0f, 12.0f, 8.0f, 7.0f, 40.0f, 47.0f, 49.0f, 55.0f,
};

f32 D_8082BD08[] = {
    -15.0f, -36.0f, -23.0f, -49.0f, -29.0f, -8.0f, 25.0f, 2.0f, -9.0f, 28.0f, 7.0f,
};

f32 D_8082BD34[] = {
    -50.0f, -38.0f, 6.0f, 11.0f, 8.0f, 0.0f, 12.0f, 31.0f, 48.0f, 56.0f,
};

f32 D_8082BD5C[] = {
    -14.0f, -39.0f, 23.0f, 11.0f, -8.0f, -15.0f, -31.0f, -30.0f, -10.0f, 11.0f,
};

f32 D_8082BD84[] = {
    -72.0f, -47.0f, -26.0f, -50.0f, -48.0f, -48.0f, -48.0f, -48.0f, -48.0f,
};

f32 D_8082BDA8[] = {
    -47.0f, -47.0f, -47.0f, -30.0f, 33.0f, 22.0f, 11.0f, -2.0f, -13.0f,
};

f32 D_8082BDCC[] = {
    52.0f,  80.0f,  24.0f,  52.0f,  81.0f, 24.0f, -78.0f, -61.0f, -44.0f, -24.0f, -6.0f,  -3.0f,
    -78.0f, -61.0f, -44.0f, -24.0f, -6.0f, -3.0f, -68.0f, 22.0f,  83.0f,  -67.0f, -21.0f,
};

f32 D_8082BE28[] = {
    33.0f,  18.0f,  18.0f,  0.0f,   -23.0f, -23.0f, -29.0f, -29.0f, -29.0f, -29.0f, -29.0f, -29.0f,
    -11.0f, -11.0f, -11.0f, -11.0f, -11.0f, -11.0f, 27.0f,  -53.0f, -53.0f, 14.0f,  26.0f,
};

s16 D_8082BE84 = 0;

s16 D_8082BE88[] = {
    0x001C, 0x001D, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025,
};

s32 D_8082BE9C = 0;

s32 D_8082BEA0 = 0;

s16 D_8082BEA4 = 10;

s32 D_8082BEA8 = 0;

s32 D_8082BEAC = 0;

s32 D_8082BEB0 = 0;

s32 D_8082BEB4 = 0;

s32 D_8082BEB8[] = { 0, 0 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8082192C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821D84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808221DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80823350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808248D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808256E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8082585C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808259D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808274DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808286D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80828788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Update.s")
