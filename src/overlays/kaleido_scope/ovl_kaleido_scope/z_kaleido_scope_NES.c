/*
 * File: z_kaleido_scope_NES.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"
#include "z64view.h"

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

s16 sQuestVtxRectLeft[] = {
    45,   // QUEST_REMAINS_ODOLWA
    78,   // QUEST_REMAINS_GOHT
    10,   // QUEST_REMAINS_GYORG
    45,   // QUEST_REMAINS_TWINMOLD
    80,   // QUEST_SHIELD
    11,   // QUEST_SWORD
    -109, // QUEST_SONG_SONATA
    -87,  // QUEST_SONG_LULLABY
    -65,  // QUEST_SONG_BOSSA_NOVA
    -41,  // QUEST_SONG_ELEGY
    -19,  // QUEST_SONG_OATH
    -18,  // QUEST_SONG_SARIA
    -109, // QUEST_SONG_TIME
    -87,  // QUEST_SONG_HEALING
    -65,  // QUEST_SONG_EPONA
    -41,  // QUEST_SONG_SOARING
    -19,  // QUEST_SONG_STORMS
    -18,  // QUEST_SONG_SUN
    -103, // QUEST_BOMBERS_NOTEBOOK
    7,    // QUEST_QUIVER
    82,   // QUEST_BOMB_BAG
    -110, // QUEST_SKULL_TOKEN (unused)
    -54,  // QUEST_HEART_PIECE
    -98,  // ocarina song button index 0
    -86,  // ocarina song button index 1
    -74,  // ocarina song button index 2
    -62,  // ocarina song button index 3
    -50,  // ocarina song button index 4
    -38,  // ocarina song button index 5
    -26,  // ocarina song button index 6
    -14,  // ocarina song button index 7
    -98,  // ocarina input button index 0
    -86,  // ocarina input button index 1
    -74,  // ocarina input button index 2
    -62,  // ocarina input button index 3
    -50,  // ocarina input button index 4
    -38,  // ocarina input button index 5
    -26,  // ocarina input button index 6
    -14,  // ocarina input button index 7
};

s16 sQuestVtxRectTop[] = {
    62,  // QUEST_REMAINS_ODOLWA
    42,  // QUEST_REMAINS_GOHT
    42,  // QUEST_REMAINS_GYORG
    20,  // QUEST_REMAINS_TWINMOLD
    -9,  // QUEST_SHIELD
    -9,  // QUEST_SWORD
    -20, // QUEST_SONG_SONATA
    -20, // QUEST_SONG_LULLABY
    -20, // QUEST_SONG_BOSSA_NOVA
    -20, // QUEST_SONG_ELEGY
    -20, // QUEST_SONG_OATH
    -20, // QUEST_SONG_SARIA
    2,   // QUEST_SONG_TIME
    2,   // QUEST_SONG_HEALING
    2,   // QUEST_SONG_EPONA
    2,   // QUEST_SONG_SOARING
    2,   // QUEST_SONG_STORMS
    2,   // QUEST_SONG_SUN
    54,  // QUEST_BOMBERS_NOTEBOOK
    -44, // QUEST_QUIVER
    -44, // QUEST_BOMB_BAG
    34,  // QUEST_SKULL_TOKEN (unused)
    58,  // QUEST_HEART_PIECE
    -52, // ocarina song button index 0
    -52, // ocarina song button index 1
    -52, // ocarina song button index 2
    -52, // ocarina song button index 3
    -52, // ocarina song button index 4
    -52, // ocarina song button index 5
    -52, // ocarina song button index 6
    -52, // ocarina song button index 7
    -52, // ocarina input button index 0
    -52, // ocarina input button index 1
    -52, // ocarina input button index 2
    -52, // ocarina input button index 3
    -52, // ocarina input button index 4
    -52, // ocarina input button index 5
    -52, // ocarina input button index 6
    -52, // ocarina input button index 7
};

s16 sQuestVtxWidths[] = {
    32, // QUEST_REMAINS_ODOLWA
    32, // QUEST_REMAINS_GOHT
    32, // QUEST_REMAINS_GYORG
    32, // QUEST_REMAINS_TWINMOLD
    32, // QUEST_SHIELD
    32, // QUEST_SWORD
    16, // QUEST_SONG_SONATA
    16, // QUEST_SONG_LULLABY
    16, // QUEST_SONG_BOSSA_NOVA
    16, // QUEST_SONG_ELEGY
    16, // QUEST_SONG_OATH
    16, // QUEST_SONG_SARIA
    16, // QUEST_SONG_TIME
    16, // QUEST_SONG_HEALING
    16, // QUEST_SONG_EPONA
    16, // QUEST_SONG_SOARING
    16, // QUEST_SONG_STORMS
    16, // QUEST_SONG_SUN
    32, // QUEST_BOMBERS_NOTEBOOK
    32, // QUEST_QUIVER
    32, // QUEST_BOMB_BAG
    24, // QUEST_SKULL_TOKEN (unused)
    48, // QUEST_HEART_PIECE
    16, // ocarina song button index 0
    16, // ocarina song button index 1
    16, // ocarina song button index 2
    16, // ocarina song button index 3
    16, // ocarina song button index 4
    16, // ocarina song button index 5
    16, // ocarina song button index 6
    16, // ocarina song button index 7
    16, // ocarina input button index 0
    16, // ocarina input button index 1
    16, // ocarina input button index 2
    16, // ocarina input button index 3
    16, // ocarina input button index 4
    16, // ocarina input button index 5
    16, // ocarina input button index 6
    16, // ocarina input button index 7
};

s16 sQuestVtxHeights[] = {
    32, // QUEST_REMAINS_ODOLWA
    32, // QUEST_REMAINS_GOHT
    32, // QUEST_REMAINS_GYORG
    32, // QUEST_REMAINS_TWINMOLD
    32, // QUEST_SHIELD
    32, // QUEST_SWORD
    24, // QUEST_SONG_SONATA
    24, // QUEST_SONG_LULLABY
    24, // QUEST_SONG_BOSSA_NOVA
    24, // QUEST_SONG_ELEGY
    24, // QUEST_SONG_OATH
    24, // QUEST_SONG_SARIA
    24, // QUEST_SONG_TIME
    24, // QUEST_SONG_HEALING
    24, // QUEST_SONG_EPONA
    24, // QUEST_SONG_SOARING
    24, // QUEST_SONG_STORMS
    24, // QUEST_SONG_SUN
    32, // QUEST_BOMBERS_NOTEBOOK
    32, // QUEST_QUIVER
    32, // QUEST_BOMB_BAG
    24, // QUEST_SKULL_TOKEN (unused)
    48, // QUEST_HEART_PIECE
    16, // ocarina song button index 0
    16, // ocarina song button index 1
    16, // ocarina song button index 2
    16, // ocarina song button index 3
    16, // ocarina song button index 4
    16, // ocarina song button index 5
    16, // ocarina song button index 6
    16, // ocarina song button index 7
    16, // ocarina input button index 0
    16, // ocarina input button index 1
    16, // ocarina input button index 2
    16, // ocarina input button index 3
    16, // ocarina input button index 4
    16, // ocarina input button index 5
    16, // ocarina input button index 6
    16, // ocarina input button index 7
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_MoveCursorToSpecialPos.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawTexQuadRGBA32.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_SetView.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808274DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808286D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80828788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Update.s")
