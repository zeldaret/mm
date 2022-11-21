/*
 * File: z_kaleido_scope_NES.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
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

extern u8 sUnpausedButtonStatus[5];

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

s16 sGameOverPrimR = 0;
s16 sGameOverPrimG = 0;
s16 sGameOverPrimB = 0;
s16 sGameOverPrimAlpha = 255;
s16 sCursorPrimR = 0;
s16 sCursorPrimG = 0;
s16 sCursorPrimB = 0;
s16 sCursorEnvR = 0;
s16 sCursorEnvG = 0;
s16 sCursorEnvB = 0;
s16 sGameOverEnvR = 255;
s16 sGameOverEnvG = 0;
s16 sGameOverEnvB = 0;

s16 sInDungeonScene = false;

f32 sPageSwitchEyeDx[] = {
    -PAUSE_EYE_DIST * (PAUSE_MAP_X - PAUSE_ITEM_X) / 16, // From PAUSE_ITEM to PAUSE_MAP (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MASK_X - PAUSE_ITEM_X) / 16,  // From PAUSE_ITEM to PAUSE_MASK (switching left)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_X - PAUSE_MAP_X) / 16,  // From PAUSE_MAP to PAUSE_QUEST (switching right)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_X - PAUSE_MAP_X) / 16,   // From PAUSE_MAP to PAUSE_ITEM (switching left)
    -PAUSE_EYE_DIST*(PAUSE_MASK_X - PAUSE_QUEST_X) / 16, // From PAUSE_QUEST to PAUSE_MASK (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MAP_X - PAUSE_QUEST_X) / 16,  // From PAUSE_QUEST to PAUSE_MAP (switching left)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_X - PAUSE_MASK_X) / 16,  // From PAUSE_MASK to PAUSE_ITEM (switching right)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_X - PAUSE_MASK_X) / 16, // From PAUSE_MASK to PAUSE_QUEST (switching left)
};

f32 sPageSwitchEyeDz[] = {
    -PAUSE_EYE_DIST * (PAUSE_MAP_Z - PAUSE_ITEM_Z) / 16, // From PAUSE_ITEM to PAUSE_MAP (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MASK_Z - PAUSE_ITEM_Z) / 16,  // From PAUSE_ITEM to PAUSE_MASK (switching left)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_Z - PAUSE_MAP_Z) / 16,  // From PAUSE_MAP to PAUSE_QUEST (switching right)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_Z - PAUSE_MAP_Z) / 16,   // From PAUSE_MAP to PAUSE_ITEM (switching left)
    -PAUSE_EYE_DIST*(PAUSE_MASK_Z - PAUSE_QUEST_Z) / 16, // From PAUSE_QUEST to PAUSE_MASK (switching right)
    -PAUSE_EYE_DIST*(PAUSE_MAP_Z - PAUSE_QUEST_Z) / 16,  // From PAUSE_QUEST to PAUSE_MAP (switching left)
    -PAUSE_EYE_DIST*(PAUSE_ITEM_Z - PAUSE_MASK_Z) / 16,  // From PAUSE_MASK to PAUSE_ITEM (switching right)
    -PAUSE_EYE_DIST*(PAUSE_QUEST_Z - PAUSE_MASK_Z) / 16, // From PAUSE_MASK to PAUSE_QUEST (switching left)
};

u16 sPageSwitchNextPageIndex[] = {
    PAUSE_MAP,   // From PAUSE_ITEM (switching right)
    PAUSE_MASK,  // From PAUSE_ITEM (switching left)
    PAUSE_QUEST, // From PAUSE_MAP (switching right)
    PAUSE_ITEM,  // From PAUSE_MAP (switching left)
    PAUSE_MASK,  // From PAUSE_QUEST (switching right)
    PAUSE_MAP,   // From PAUSE_QUEST (switching left)
    PAUSE_ITEM,  // From PAUSE_MASK (switching right)
    PAUSE_QUEST, // From PAUSE_MASK (switching left)
};

f32 sPauseMenuVerticalOffset = 0.0f;
f32 D_8082B90C = 0.0f;
f32 sPauseCursorLeftMoveOffsetX = 40.0f;
f32 sPauseCursorRightMoveOffsetX = -40.0f;

s16 sPauseCursorLeftX = 0;
s16 sPauseCursorRightX = 0;

s16 D_8082B920 = 10;

u8 D_8082B924[] = {
    0x00, 0x14, 0x00, 0x04, 0x00, 0x14, 0x00, 0x0A, 0x0F, 0x1F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    0x07, 0x07, 0x03, 0x0F, 0x07, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x03, 0x0F, 0x00, 0x00,
};

// TODO: Also applies to owl warps
s16 sGameOverRectPosY = 66;

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

void func_80821900(void* segment, u32 texIndex) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), texIndex, segment, 0x400);
}

void func_8082192C(void* segment, u32 texIndex) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), texIndex, segment, 0xA00);
}

void func_80821958(void* segment, u32 texIndex) {
    func_80178E3C(SEGMENT_ROM_START(item_name_static), texIndex, segment, 0x400);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_MoveCursorToSpecialPos.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawTexQuadRGBA32.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821CC4.s")

void KaleidoScope_HandlePageToggles(PlayState* play, Input* input);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_HandlePageToggles.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808221DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80823350.s")

void KaleidoScope_UpdateNamePanel(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateNamePanel.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808248D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824B90.s")

void KaleidoScope_UpdateOwlWarpNamePanel(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateOwlWarpNamePanel.s")

void KaleidoScope_UpdateSwitchPage(PlayState* play, Input* input);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateSwitchPage.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_SetView.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808274DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Draw.s")

void KaleidoScope_GrayOutTextureRGBA32(u32* texture, u16 pixelCount);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_GrayOutTextureRGBA32.s")

void KaleidoScope_UpdateOpening(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->eye.x += sPageSwitchEyeDx[pauseCtx->nextPageMode] * 2.0f;
    pauseCtx->eye.z += sPageSwitchEyeDz[pauseCtx->nextPageMode] * 2.0f;
    pauseCtx->switchPageTimer += 8;

    if (pauseCtx->switchPageTimer == 64) {
        // Finished opening
        func_80112C0C(play, 1);

        if (pauseCtx->cursorSpecialPos == 0) {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = D_801C6A98[pauseCtx->pageIndex][0];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = D_801C6A98[pauseCtx->pageIndex][1];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = D_801C6A98[pauseCtx->pageIndex][1];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = D_801C6A98[pauseCtx->pageIndex][1];
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
        } else {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
        }

        pauseCtx->pageIndex = sPageSwitchNextPageIndex[pauseCtx->nextPageMode];
        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
        pauseCtx->state++; // PAUSE_STATE_MAIN
        pauseCtx->alpha = 255;
        func_80115844(play, 3);
    } else if (pauseCtx->switchPageTimer == 64) {
        pauseCtx->pageIndex = sPageSwitchNextPageIndex[pauseCtx->nextPageMode];
        pauseCtx->nextPageMode = (pauseCtx->pageIndex * 2) + 1;
    }
}

void KaleidoScope_Update(PlayState* play) {
    static u16 sCursorPointsToOcarinaModes[] = {
        28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    };
    static s16 sUnpausedHudVisibility = HUD_VISIBILITY_IDLE;
    static s16 sNextMainState = PAUSE_MAIN_STATE_IDLE;
    static s16 sDelayTimer = 10;
    static s16 sGameOverColorTimer = 0;
    static s16 sStickXRepeatTimer = 0;
    static s16 sStickYRepeatTimer = 0;
    static s16 sStickXRepeatState = 0;
    static s16 sStickYRepeatState = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    MessageContext* msgCtx = &play->msgCtx;
    GameOverContext* gameOverCtx = &play->gameOverCtx;
    SramContext* sramCtx = &play->sramCtx;
    Input* input = CONTROLLER1(&play->state);
    size_t size0;
    size_t size1;
    size_t size2;
    u16 itemId;
    u16 worldMapCursorPoint;
    void* iconItemLangSegment;
    s16 stepR;
    s16 stepG;
    s16 stepB;
    s16 stepA;
    s16 stickAdjX = input->rel.stick_x;

    func_80109428(play);

    pauseCtx->stickAdjX = input->rel.stick_x;
    pauseCtx->stickAdjY = input->rel.stick_y;

    switch (pauseCtx->state) {
        case PAUSE_STATE_OPENING_2:
            sUnpausedHudVisibility = gSaveContext.hudVisibility;
            sPauseMenuVerticalOffset = -6240.0f;

            sUnpausedButtonStatus[EQUIP_SLOT_B] = gSaveContext.buttonStatus[EQUIP_SLOT_B];
            sUnpausedButtonStatus[EQUIP_SLOT_C_LEFT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT];
            sUnpausedButtonStatus[EQUIP_SLOT_C_DOWN] = gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN];
            sUnpausedButtonStatus[EQUIP_SLOT_C_RIGHT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT];
            sUnpausedButtonStatus[EQUIP_SLOT_A] = gSaveContext.buttonStatus[EQUIP_SLOT_A];

            pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
            pauseCtx->cursorSlot[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256 = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;

            sPauseCursorLeftX = -175;
            sPauseCursorRightX = 155;
            pauseCtx->roll = -314.0f;

            pauseCtx->iconItemSegment = (void*)ALIGN16((uintptr_t)play->objectCtx.spaceStart);
            size0 = SEGMENT_ROM_SIZE(icon_item_static_old);
            func_80178E7C((uintptr_t)SEGMENT_ROM_START(icon_item_static_test), pauseCtx->iconItemSegment, size0);

            gSegments[0x08] = PHYSICAL_TO_VIRTUAL(pauseCtx->iconItemSegment);

            for (itemId = 0; itemId <= ITEM_BOW_ARROW_FIRE; itemId++) {
                if (!gPlayerFormItemRestrictions[(void)0, gSaveContext.save.playerForm][(s32)itemId]) {
                    KaleidoScope_GrayOutTextureRGBA32(Lib_SegmentedToVirtual(gItemIcons[(s32)itemId]), 0x400);
                }
            }

            pauseCtx->iconItem24Segment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemSegment + size0);
            size1 = SEGMENT_ROM_SIZE(icon_item_24_static_old);
            func_80178E7C((uintptr_t)SEGMENT_ROM_START(icon_item_24_static_test), pauseCtx->iconItem24Segment, size1);

            pauseCtx->iconItemAltSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItem24Segment + size1);
            if (func_8010A0A4(play)) {
                size_t size = SEGMENT_ROM_SIZE(icon_item_dungeon_static);

                DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, SEGMENT_ROM_START(icon_item_dungeon_static), size);
                iconItemLangSegment =
                    func_801068FC(play, (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size), size);
                sInDungeonScene = true;
            } else {
                size_t size;

                sInDungeonScene = false;
                size = SEGMENT_ROM_SIZE(icon_item_field_static);
                DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, _icon_item_field_staticSegmentRomStart, size);
                iconItemLangSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size);
            }

            pauseCtx->iconItemLangSegment = iconItemLangSegment;
            size2 = SEGMENT_ROM_SIZE(icon_item_jpn_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemLangSegment, SEGMENT_ROM_START(icon_item_jpn_static), size2);

            pauseCtx->nameSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemLangSegment + size2);
            func_8011552C(play, 0x15);
            if (((void)0, gSaveContext.worldMapArea) < 0x16) {
                func_8082192C(pauseCtx->nameSegment + 0x400, ((void)0, gSaveContext.worldMapArea));
            }

            pauseCtx->iconItemVtxSegment = (void*)ALIGN16((uintptr_t)pauseCtx->nameSegment + 0xA00);
            DmaMgr_SendRequest0(pauseCtx->iconItemVtxSegment, SEGMENT_ROM_START(icon_item_vtx_static),
                                SEGMENT_ROM_SIZE(icon_item_vtx_static));

            pauseCtx->unk_2B6 = 255;
            pauseCtx->unk_2B7 = 255;
            pauseCtx->unk_2B8 = 255;
            pauseCtx->state = PAUSE_STATE_OPENING_3;
            break;

        case PAUSE_STATE_OPENING_3:
            pauseCtx->infoPanelOffsetY += 10;
            pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll -= 40.0f;

            interfaceCtx->startAlpha += 63;
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
            pauseCtx->alpha += 31;
            if (pauseCtx->itemPageRoll == 0) {
                interfaceCtx->startAlpha = 255;
                sPauseMenuVerticalOffset = 0.0f;
                pauseCtx->state = PAUSE_STATE_OPENING_4;
            }

            KaleidoScope_UpdateOpening(play);
            break;

        case PAUSE_STATE_OPENING_4:
            pauseCtx->alpha += 31;
            KaleidoScope_UpdateOpening(play);

            if (pauseCtx->state == PAUSE_STATE_MAIN) {
                KaleidoScope_UpdateNamePanel(play);
            }
            break;

        case PAUSE_STATE_MAIN:
            switch (pauseCtx->mainState) {
                case PAUSE_MAIN_STATE_IDLE:
                    if (!pauseCtx->itemDescriptionOn &&
                        (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B))) {
                        func_8011552C(play, 0xA);
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_SETUP;
                        sPauseMenuVerticalOffset = -6240.0f;
                        func_801A3AEC(0);
                    }
                    break;

                case PAUSE_MAIN_STATE_SWITCHING_PAGE:
                    KaleidoScope_UpdateSwitchPage(play, input);
                    break;

                case PAUSE_MAIN_STATE_SONG_PLAYBACK:
                    // Song is in playback
                    pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                    if (pauseCtx->ocarinaStaff->state == 0) {
                        // Song playback is finished, give song prompt to player
                        pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PROMPT_INIT;
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                    }
                    break;

                case PAUSE_MAIN_STATE_EQUIP_ITEM:
                    KaleidoScope_UpdateItemEquip(play);
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT_INIT:
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT:
                    pauseCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();

                    if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
                        // Abort having the player play the song and close the pause menu
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        func_8011552C(play, 0xA);
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_SETUP;
                        sPauseMenuVerticalOffset = -6240.0f;
                        func_801A3AEC(0);
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    } else if (pauseCtx->ocarinaStaff->state == pauseCtx->ocarinaSongIndex) {
                        // The player successfully played the song
                        play_sound(NA_SE_SY_TRE_BOX_APPEAR);
                        sNextMainState = PAUSE_MAIN_STATE_IDLE;
                        sDelayTimer = 30;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PROMPT_DONE;
                    } else if (pauseCtx->ocarinaStaff->state == 0xFF) {
                        // The player failed to play the song
                        play_sound(NA_SE_SY_OCARINA_ERROR);
                        sNextMainState = PAUSE_MAIN_STATE_SONG_PROMPT_INIT;
                        sDelayTimer = 20;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PROMPT_DONE;
                    }
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT_DONE:
                    sDelayTimer--;
                    if (sDelayTimer == 0) {
                        pauseCtx->mainState = sNextMainState;
                        if (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) {
                            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        }
                    }
                    break;

                case PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED:
                    break;

                case PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG:
                    if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                        func_8011552C(play, 0xA);
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_SETUP;
                        sPauseMenuVerticalOffset = -6240.0f;
                        func_801A3AEC(0);
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    }
                    break;

                case PAUSE_MAIN_STATE_SONG_PLAYBACK_INIT:
                    break;

                case PAUSE_MAIN_STATE_EQUIP_MASK:
                    KaleidoScope_UpdateMaskEquip(play);
                    break;

                case PAUSE_MAIN_STATE_BOMBERS_NOTEBOOK_OPEN:
                    if (!play->pauseCtx.bombersNotebookOpen) {
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    }
                    break;

                default:
                    pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    break;
            }
            break;

        case PAUSE_STATE_SAVEPROMPT:
            switch (pauseCtx->savePromptState) {
                case PAUSE_SAVEPROMPT_STATE_0:
                    pauseCtx->roll -= 78.5f;
                    sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                    sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                    if (pauseCtx->roll <= -628.0f) {
                        pauseCtx->roll = -628.0f;
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_1;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_1:
                    if (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
                        if (pauseCtx->promptChoice != PAUSE_PROMPT_YES) {
                            func_8011552C(play, 0xA);
                            pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_2;
                        } else {
                            play_sound(NA_SE_SY_PIECE_OF_HEART);
                            Play_SaveCycleSceneFlags(&play->state);
                            gSaveContext.save.playerData.savedSceneId = play->sceneId;
                            func_8014546C(sramCtx);
                            if (gSaveContext.unk_3F3F == 0) {
                                pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_5;
                            } else {
                                func_80147008(sramCtx, D_801C67C8[gSaveContext.fileNum],
                                              D_801C67F0[gSaveContext.fileNum]);
                                func_80147020(sramCtx);
                                pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_4;
                            }
                            sDelayTimer = 90;
                        }
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_START)) {
                        func_8011552C(play, 0xA);
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_3;
                        sPauseMenuVerticalOffset = -6240.0f;
                        D_8082B90C = pauseCtx->roll;
                        func_801A3AEC(0);
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
                        func_8011552C(play, 0xA);
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_2;
                        D_8082B90C = pauseCtx->roll;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_4:
                    if (sramCtx->status == 0) {
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_5;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_5:
                    if (CHECK_BTN_ALL(input->press.button, BTN_B) || CHECK_BTN_ALL(input->press.button, BTN_A) ||
                        CHECK_BTN_ALL(input->press.button, BTN_START) || (--sDelayTimer == 0)) {
                        func_8011552C(play, 0xA);
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_3;
                        sPauseMenuVerticalOffset = -6240.0f;
                        D_8082B90C = pauseCtx->roll;
                        func_801A3AEC(0);
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_3:
                case PAUSE_SAVEPROMPT_STATE_7:
                    if (pauseCtx->roll != (D_8082B90C + 160.0f)) {
                        pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll =
                            pauseCtx->maskPageRoll += 40.0f;
                        pauseCtx->roll += 40.0f;
                        pauseCtx->infoPanelOffsetY -= 10;
                        sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                        sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                        pauseCtx->alpha -= 63;
                        if (pauseCtx->roll == (D_8082B90C + 160.0f)) {
                            pauseCtx->alpha = 0;
                        }
                    } else {
                        pauseCtx->debugEditor = DEBUG_EDITOR_NONE;
                        pauseCtx->state = PAUSE_STATE_UNPAUSE_CLOSE;
                        pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll =
                            pauseCtx->maskPageRoll = 160.0f;
                        pauseCtx->roll = -434.0f;
                        pauseCtx->namedItem = PAUSE_ITEM_NONE;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_2:
                    pauseCtx->roll += 78.5f;
                    sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
                    sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
                    if (pauseCtx->roll >= -314.0f) {
                        pauseCtx->state = PAUSE_STATE_MAIN;
                        pauseCtx->savePromptState = PAUSE_SAVEPROMPT_STATE_0;
                        pauseCtx->roll = -314.0f;
                        pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll =
                            pauseCtx->maskPageRoll = 0.0f;
                        func_8011552C(play, 0x15);
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = D_801C6A98[pauseCtx->pageIndex + 1][0];
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = D_801C6A98[pauseCtx->pageIndex + 1][1];
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = D_801C6A98[pauseCtx->pageIndex + 1][1];
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = D_801C6A98[pauseCtx->pageIndex + 1][1];
                        if ((pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) ||
                            (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT)) {
                            KaleidoScope_MoveCursorToSpecialPos(play, pauseCtx->cursorSpecialPos);
                        } else {
                            func_80821A04(play);
                        }
                    }
                    break;

                case PAUSE_SAVEPROMPT_STATE_6:
                    if (interfaceCtx->unk_264 != 255) {
                        interfaceCtx->unk_264 += 10;
                        if (interfaceCtx->unk_264 >= 255) {
                            interfaceCtx->unk_264 = 255;
                            pauseCtx->state = PAUSE_STATE_OFF;
                            Game_SetFramerateDivisor(&play->state, 3);
                            R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                            Object_LoadAll(&play->objectCtx);
                            BgCheck_InitCollisionHeaders(&play->colCtx, play);
                            STOP_GAMESTATE(&play->state);
                            SET_NEXT_GAMESTATE(&play->state, TitleSetup_Init, sizeof(TitleSetupState));
                            func_801A4058(0x14);
                            gSaveContext.seqId = (u8)NA_BGM_DISABLED;
                            gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
                        }
                    }
                    break;
            }
            break;

        case PAUSE_STATE_GAMEOVER_2:
            pauseCtx->cursorSlot[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            pauseCtx->cursorPoint[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            sPauseCursorLeftX = -175;
            sPauseCursorRightX = 155;
            pauseCtx->roll = -434.0f;
            Interface_SetHudVisibility(HUD_VISIBILITY_NONE);

            pauseCtx->iconItemSegment =
                (void*)(((uintptr_t)play->objectCtx.spaceStart + 0x30) & ~0x3F); // Messed up ALIGN64
            size0 = SEGMENT_ROM_SIZE(icon_item_static_old);
            func_80178E7C(SEGMENT_ROM_START(icon_item_static_test), pauseCtx->iconItemSegment, size0);

            pauseCtx->iconItem24Segment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemSegment + size0);
            size1 = SEGMENT_ROM_SIZE(icon_item_24_static_old);
            func_80178E7C(SEGMENT_ROM_START(icon_item_24_static_test), pauseCtx->iconItem24Segment, size1);

            pauseCtx->iconItemAltSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItem24Segment + size1);
            size2 = SEGMENT_ROM_SIZE(icon_item_gameover_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, SEGMENT_ROM_START(icon_item_gameover_static), size2);

            pauseCtx->iconItemLangSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size2);
            DmaMgr_SendRequest0(pauseCtx->iconItemLangSegment, SEGMENT_ROM_START(icon_item_jpn_static),
                                SEGMENT_ROM_SIZE(icon_item_jpn_static));

            gSaveContext.timerStates[TIMER_ID_MOON_CRASH] = TIMER_STATE_OFF;

            sGameOverPrimR = 255;
            sGameOverPrimG = 130;
            sGameOverPrimB = 0;
            sGameOverPrimAlpha = 0;
            sGameOverEnvR = 30;
            sGameOverEnvG = 0;
            sGameOverEnvB = 0;
            sGameOverRectPosY = 98;
            sGameOverColorTimer = 30;

            pauseCtx->promptChoice = PAUSE_PROMPT_YES;
            pauseCtx->state++;
            if (gameOverCtx->state == GAMEOVER_INACTIVE) {
                pauseCtx->state++;
            }
            break;

        case PAUSE_STATE_GAMEOVER_3:
            stepR = ABS_ALT(sGameOverPrimR - 30) / sGameOverColorTimer;
            stepG = ABS_ALT(sGameOverPrimG - 0) / sGameOverColorTimer;
            stepB = ABS_ALT(sGameOverPrimB - 0) / sGameOverColorTimer;
            stepA = ABS_ALT(sGameOverPrimAlpha - 255) / sGameOverColorTimer;
            if (sGameOverPrimR >= 30) {
                sGameOverPrimR -= stepR;
            } else {
                sGameOverPrimR += stepR;
            }
            if (sGameOverPrimG >= 0) {
                sGameOverPrimG -= stepG;
            } else {
                sGameOverPrimG += stepG;
            }
            if (sGameOverPrimB >= 0) {
                sGameOverPrimB -= stepB;
            } else {
                sGameOverPrimB += stepB;
            }
            if (sGameOverPrimAlpha >= 255) {
                sGameOverPrimAlpha -= stepA;
            } else {
                sGameOverPrimAlpha += stepA;
            }

            stepR = ABS_ALT(sGameOverEnvR - 255) / sGameOverColorTimer;
            stepG = ABS_ALT(sGameOverEnvG - 130) / sGameOverColorTimer;
            stepB = ABS_ALT(sGameOverEnvB - 0) / sGameOverColorTimer;
            if (sGameOverEnvR >= 255) {
                sGameOverEnvR -= stepR;
            } else {
                sGameOverEnvR += stepR;
            }
            if (sGameOverEnvG >= 130) {
                sGameOverEnvG -= stepG;
            } else {
                sGameOverEnvG += stepG;
            }
            if (sGameOverEnvB >= 0) {
                sGameOverEnvB -= stepB;
            } else {
                sGameOverEnvB += stepB;
            }

            sGameOverColorTimer--;
            if (sGameOverColorTimer == 0) {
                sGameOverPrimR = 30;
                sGameOverPrimG = 0;
                sGameOverPrimB = 0;
                sGameOverPrimAlpha = 255;

                sGameOverEnvR = 255;
                sGameOverEnvG = 130;
                sGameOverEnvB = 0;

                sGameOverColorTimer = 40;
                pauseCtx->state++;
            }
            break;

        case PAUSE_STATE_GAMEOVER_4:
            sGameOverColorTimer--;
            if (sGameOverColorTimer == 0) {
                pauseCtx->state = PAUSE_STATE_GAMEOVER_5;
            }
            break;

        case PAUSE_STATE_GAMEOVER_5:
            pauseCtx->infoPanelOffsetY += 10;
            pauseCtx->roll -= 40.0f;
            pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll =
                pauseCtx->roll;
            interfaceCtx->startAlpha += 63;
            sGameOverRectPosY -= 3;
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
            pauseCtx->alpha += 31;
            if (pauseCtx->roll < -628.0f) {
                pauseCtx->roll = -628.0f;
                interfaceCtx->startAlpha = 255;
                sGameOverRectPosY = 66;
                sPauseMenuVerticalOffset = 0.0f;
                pauseCtx->alpha = 255;
                if (gameOverCtx->state == GAMEOVER_INACTIVE) {
                    pauseCtx->state = PAUSE_STATE_GAMEOVER_SAVE_PROMPT;
                } else {
                    pauseCtx->state = PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT;
                }
            }
            break;

        case PAUSE_STATE_GAMEOVER_SAVE_PROMPT:
            if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                if (pauseCtx->promptChoice != PAUSE_PROMPT_YES) {
                    pauseCtx->promptChoice = PAUSE_PROMPT_YES;
                    play_sound(NA_SE_SY_DECIDE);
                    pauseCtx->state = PAUSE_STATE_OFF;
                    Game_SetFramerateDivisor(&play->state, 3);
                    R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                    Object_LoadAll(&play->objectCtx);
                    BgCheck_InitCollisionHeaders(&play->colCtx, play);
                } else {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    pauseCtx->promptChoice = PAUSE_PROMPT_YES;
                    Play_SaveCycleSceneFlags(&play->state);
                    gSaveContext.save.playerData.savedSceneId = play->sceneId;
                    gSaveContext.save.playerData.health = 0x30;
                    func_8014546C(sramCtx);
                    if (gSaveContext.unk_3F3F == 0) {
                        pauseCtx->state = PAUSE_STATE_GAMEOVER_8;
                    } else {
                        func_80147008(sramCtx, D_801C67C8[gSaveContext.fileNum], D_801C67F0[gSaveContext.fileNum]);
                        func_80147020(sramCtx);
                        pauseCtx->state = PAUSE_STATE_GAMEOVER_7;
                    }
                    sDelayTimer = 90;
                }
            } else if ((pauseCtx->promptChoice == PAUSE_PROMPT_YES) && (stickAdjX >= 30)) {
                play_sound(NA_SE_SY_CURSOR);
                pauseCtx->promptChoice = PAUSE_PROMPT_NO;
            } else if ((pauseCtx->promptChoice != PAUSE_PROMPT_YES) && (stickAdjX <= -30)) {
                play_sound(NA_SE_SY_CURSOR);
                pauseCtx->promptChoice = PAUSE_PROMPT_YES;
            }
            break;

        case PAUSE_STATE_GAMEOVER_7:
            if (sramCtx->status == 0) {
                pauseCtx->state = PAUSE_STATE_OFF;
                Game_SetFramerateDivisor(&play->state, 3);
                R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                Object_LoadAll(&play->objectCtx);
                BgCheck_InitCollisionHeaders(&play->colCtx, play);
            }
            break;

        case PAUSE_STATE_GAMEOVER_8:
            sDelayTimer--;
            if (sDelayTimer == 0) {
                pauseCtx->state = PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT;
                gameOverCtx->state++;
            } else if ((sDelayTimer <= 80) &&
                       (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_START))) {
                pauseCtx->state = PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT;
                gameOverCtx->state++;
                func_801A3AEC(0);
            }
            break;

        case PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT:
            if (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_START)) {
                if (pauseCtx->promptChoice == PAUSE_PROMPT_YES) {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    Play_SaveCycleSceneFlags(&play->state);
                    if (gSaveContext.save.entrance == ENTRANCE(UNSET_0D, 0)) {}
                } else { // PAUSE_PROMPT_NO
                    play_sound(NA_SE_SY_DECIDE);
                }
                pauseCtx->state = PAUSE_STATE_GAMEOVER_10;
            }
            break;

        case PAUSE_STATE_GAMEOVER_10:
            if (interfaceCtx->unk_264 != 255) {
                interfaceCtx->unk_264 += 10;
                if (interfaceCtx->unk_264 >= 255) {
                    interfaceCtx->unk_264 = 255;

                    pauseCtx->state = PAUSE_STATE_OFF;
                    Game_SetFramerateDivisor(&play->state, 3);
                    R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
                    Object_LoadAll(&play->objectCtx);
                    BgCheck_InitCollisionHeaders(&play->colCtx, play);

                    if (pauseCtx->promptChoice == PAUSE_PROMPT_YES) {
                        func_80169FDC(&play->state);
                        gSaveContext.respawnFlag = -2;
                        gSaveContext.nextTransitionType = TRANS_TYPE_02;
                        gSaveContext.save.playerData.health = 0x30;
                        Audio_SetSpec(0xA);
                        gSaveContext.healthAccumulator = 0;
                        gSaveContext.magicState = MAGIC_STATE_IDLE;
                        gSaveContext.magicFlag = 0;
                        gSaveContext.magicCapacity = 0;
                        gSaveContext.magicFillTarget = gSaveContext.save.playerData.magic;
                        gSaveContext.save.playerData.magicLevel = 0;
                        gSaveContext.save.playerData.magic = 0;
                    } else { // PAUSE_PROMPT_NO
                        STOP_GAMESTATE(&play->state);
                        SET_NEXT_GAMESTATE(&play->state, TitleSetup_Init, sizeof(TitleSetupState));
                    }
                }
            }
            break;

        case PAUSE_STATE_OWLWARP_2:
            sPauseMenuVerticalOffset = -6240.0f;

            sUnpausedButtonStatus[EQUIP_SLOT_B] = gSaveContext.buttonStatus[EQUIP_SLOT_B];
            sUnpausedButtonStatus[EQUIP_SLOT_C_LEFT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT];
            sUnpausedButtonStatus[EQUIP_SLOT_C_DOWN] = gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN];
            sUnpausedButtonStatus[EQUIP_SLOT_C_RIGHT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT];
            sUnpausedButtonStatus[EQUIP_SLOT_A] = gSaveContext.buttonStatus[EQUIP_SLOT_A];

            pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
            pauseCtx->cursorSlot[PAUSE_MAP] = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;
            pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256 = R_REVERSE_FLOOR_INDEX + DUNGEON_FLOOR_INDEX_4;

            sPauseCursorLeftX = -175;
            sPauseCursorRightX = 155;

            pauseCtx->iconItemSegment = (void*)ALIGN16((uintptr_t)play->objectCtx.spaceStart);
            size0 = SEGMENT_ROM_SIZE(icon_item_static_old);
            func_80178E7C(SEGMENT_ROM_START(icon_item_static_test), pauseCtx->iconItemSegment, size0);

            pauseCtx->iconItemAltSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemSegment + size0);
            sInDungeonScene = false;
            size1 = SEGMENT_ROM_SIZE(icon_item_field_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemAltSegment, SEGMENT_ROM_START(icon_item_field_static), size1);

            pauseCtx->iconItemLangSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemAltSegment + size1);
            size2 = SEGMENT_ROM_SIZE(icon_item_jpn_static);
            DmaMgr_SendRequest0(pauseCtx->iconItemLangSegment, SEGMENT_ROM_START(icon_item_jpn_static), size2);

            pauseCtx->nameSegment = (void*)ALIGN16((uintptr_t)pauseCtx->iconItemLangSegment + size2);
            func_8011552C(play, 0x16);
            worldMapCursorPoint = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
            func_80821900(pauseCtx->nameSegment, worldMapCursorPoint);

            pauseCtx->iconItemVtxSegment = (void*)ALIGN16((uintptr_t)pauseCtx->nameSegment + 0xA00);
            DmaMgr_SendRequest0(pauseCtx->iconItemVtxSegment, SEGMENT_ROM_START(icon_item_vtx_static),
                                SEGMENT_ROM_SIZE(icon_item_vtx_static));

            pauseCtx->state = PAUSE_STATE_OWLWARP_3;
            sGameOverRectPosY = 98;
            pauseCtx->promptChoice = PAUSE_PROMPT_YES;
            break;

        case PAUSE_STATE_OWLWARP_3:
            R_PAUSE_OWLWARP_ALPHA += 20;
            pauseCtx->infoPanelOffsetY += 10;
            pauseCtx->mapPageRoll -= 40.0f;
            interfaceCtx->startAlpha += 63;
            sGameOverRectPosY -= 3;
            sPauseCursorLeftX += (s16)(sPauseCursorLeftMoveOffsetX / 4);
            sPauseCursorRightX += (s16)(sPauseCursorRightMoveOffsetX / 4);
            pauseCtx->alpha += 31;

            if (pauseCtx->mapPageRoll == 0) {
                interfaceCtx->startAlpha = 255;
                sPauseMenuVerticalOffset = 0.0f;
                pauseCtx->alpha = 255;
                pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                pauseCtx->cursorSpecialPos = 0;
                pauseCtx->state = PAUSE_STATE_OWLWARP_SELECT;
                R_PAUSE_OWLWARP_ALPHA = 120;
            }
            break;

        case PAUSE_STATE_OWLWARP_SELECT:
            if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
                func_8011552C(play, 0xA);
                pauseCtx->state = PAUSE_STATE_OWLWARP_6;
                sPauseMenuVerticalOffset = -6240.0f;
                func_801A3AEC(0);
                play->msgCtx.ocarinaMode = 4;
                gSaveContext.prevHudVisibility = HUD_VISIBILITY_ALL;
            } else if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                play_sound(NA_SE_SY_DECIDE);
                Message_StartTextbox(play, 0x1B93, NULL);
                pauseCtx->state = PAUSE_STATE_OWLWARP_CONFIRM;
            } else {
                KaleidoScope_UpdateOwlWarpNamePanel(play);
            }
            break;

        case PAUSE_STATE_OWLWARP_CONFIRM:
            if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = 0;
                if (msgCtx->choiceIndex == 0) {
                    func_8011552C(play, 0xA);
                    pauseCtx->state = PAUSE_STATE_OWLWARP_6;
                    sPauseMenuVerticalOffset = -6240.0f;
                    func_801A3AEC(0);
                    play->msgCtx.ocarinaMode = sCursorPointsToOcarinaModes[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]];
                    play_sound(NA_SE_SY_DECIDE);
                } else {
                    pauseCtx->state = PAUSE_STATE_OWLWARP_SELECT;
                    func_8011552C(play, 0x16);
                    play_sound(NA_SE_SY_MESSAGE_PASS);
                }
            } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = 0;
                pauseCtx->state = PAUSE_STATE_OWLWARP_SELECT;
                play_sound(NA_SE_SY_MESSAGE_PASS);
            } else if (CHECK_BTN_ALL(input->press.button, BTN_START)) {
                msgCtx->msgLength = 0;
                msgCtx->msgMode = 0;
                func_8011552C(play, 0xA);
                pauseCtx->state = PAUSE_STATE_OWLWARP_6;
                sPauseMenuVerticalOffset = -6240.0f;
                func_801A3AEC(0);
                play->msgCtx.ocarinaMode = 4;
                gSaveContext.prevHudVisibility = HUD_VISIBILITY_ALL;
            }
            break;

        case PAUSE_STATE_OWLWARP_6:
            if (pauseCtx->mapPageRoll != 160.0f) {
                R_PAUSE_OWLWARP_ALPHA -= 60;
                if (R_PAUSE_OWLWARP_ALPHA <= 0) {
                    R_PAUSE_OWLWARP_ALPHA = 0;
                }
                pauseCtx->infoPanelOffsetY -= 10;
                pauseCtx->mapPageRoll += 40.0f;
                interfaceCtx->startAlpha -= 63;
                sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                pauseCtx->alpha -= 63;
                if (pauseCtx->mapPageRoll == 160.0f) {
                    pauseCtx->alpha = 0;
                }
            } else {
                pauseCtx->debugEditor = DEBUG_EDITOR_NONE;
                pauseCtx->state = PAUSE_STATE_UNPAUSE_CLOSE;
                pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll =
                    160.0f;
                pauseCtx->namedItem = PAUSE_ITEM_NONE;
                interfaceCtx->startAlpha = 0;
                pauseCtx->pageIndex = pauseCtx->unk_2C8;
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = pauseCtx->unk_2CA;
            }
            break;

        case PAUSE_STATE_UNPAUSE_SETUP:
            if (pauseCtx->itemPageRoll != 160.0f) {
                pauseCtx->infoPanelOffsetY -= 10;
                pauseCtx->itemPageRoll = pauseCtx->mapPageRoll = pauseCtx->questPageRoll = pauseCtx->maskPageRoll +=
                    40.0f;
                interfaceCtx->startAlpha -= 63;
                sPauseCursorLeftX -= (s16)(sPauseCursorLeftMoveOffsetX / 4);
                sPauseCursorRightX -= (s16)(sPauseCursorRightMoveOffsetX / 4);
                pauseCtx->alpha -= 63;
                if (pauseCtx->itemPageRoll == 160.0f) {
                    pauseCtx->alpha = 0;
                }
            } else {
                pauseCtx->debugEditor = DEBUG_EDITOR_NONE;
                pauseCtx->state = PAUSE_STATE_UNPAUSE_CLOSE;
                pauseCtx->maskPageRoll = 160.0f;
                pauseCtx->questPageRoll = 160.0f;
                pauseCtx->mapPageRoll = 160.0f;
                pauseCtx->itemPageRoll = 160.0f;
                pauseCtx->namedItem = PAUSE_ITEM_NONE;
                interfaceCtx->startAlpha = 0;
            }
            break;

        case PAUSE_STATE_UNPAUSE_CLOSE:
            pauseCtx->state = PAUSE_STATE_OFF;
            Game_SetFramerateDivisor(&play->state, 3);
            R_PAUSE_BG_PRERENDER_STATE = PAUSE_BG_PRERENDER_UNK4;
            Object_LoadAll(&play->objectCtx);
            BgCheck_InitCollisionHeaders(&play->colCtx, play);

            gSaveContext.buttonStatus[EQUIP_SLOT_B] = sUnpausedButtonStatus[EQUIP_SLOT_B];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = sUnpausedButtonStatus[EQUIP_SLOT_C_LEFT];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = sUnpausedButtonStatus[EQUIP_SLOT_C_DOWN];
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = sUnpausedButtonStatus[EQUIP_SLOT_C_RIGHT];
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = sUnpausedButtonStatus[EQUIP_SLOT_A];

            func_80110038(play);
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
            MsgEvent_SendNullTask();
            func_80143324(play, &play->skyboxCtx, play->skyboxId);

            if ((msgCtx->msgMode != 0) && (msgCtx->currentTextId == 0xFF)) {
                func_80115844(play, 0x12);
                func_8011552C(play, 0x12);
                Interface_SetHudVisibility(HUD_VISIBILITY_A_B_C);
            } else {
                interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;
            }
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            Interface_SetHudVisibility(sUnpausedHudVisibility);
            func_801A3A7C(0);
            break;
    }

    // If stickAdj is held, set a delay to allow the cursor to read the next input.
    // The first delay is given a longer time than all subsequent delays.
    if (!IS_PAUSE_STATE_GAMEOVER && (pauseCtx->state != PAUSE_STATE_SAVEPROMPT)) {
        if (pauseCtx->stickAdjX < -30) {
            if (sStickXRepeatState == -1) {
                sStickXRepeatTimer--;
                if (sStickXRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickXRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjX = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickXRepeatTimer = 10;
                sStickXRepeatState = -1;
            }
        } else if (pauseCtx->stickAdjX > 30) {
            if (sStickXRepeatState == 1) {
                sStickXRepeatTimer--;
                if (sStickXRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickXRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjX = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickXRepeatTimer = 10;
                sStickXRepeatState = 1;
            }
        } else {
            sStickXRepeatState = 0;
        }

        if (pauseCtx->stickAdjY < -30) {
            if (sStickYRepeatState == -1) {
                sStickYRepeatTimer--;
                if (sStickYRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickYRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjY = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickYRepeatTimer = 10;
                sStickYRepeatState = -1;
            }
        } else if (pauseCtx->stickAdjY > 30) {
            if (sStickYRepeatState == 1) {
                sStickYRepeatTimer--;
                if (sStickYRepeatTimer < 0) {
                    // Allow the input to register and apply the delay for all subsequent repeated inputs
                    sStickYRepeatTimer = 2;
                } else {
                    // Cancel the current input
                    pauseCtx->stickAdjY = 0;
                }
            } else {
                // Allow the input to register and apply the delay for the first repeated input
                sStickYRepeatTimer = 10;
                sStickYRepeatState = 1;
            }
        } else {
            sStickYRepeatState = 0;
        }
    }

    // Process the Cursor input
    if ((R_PAUSE_BG_PRERENDER_STATE == PAUSE_BG_PRERENDER_DONE) && (pauseCtx->debugEditor == DEBUG_EDITOR_NONE) &&
        !IS_PAUSE_STATE_OWLWARP &&
        (((pauseCtx->state >= PAUSE_STATE_OPENING_3) && (pauseCtx->state <= PAUSE_STATE_SAVEPROMPT)) ||
         ((pauseCtx->state >= PAUSE_STATE_GAMEOVER_2) && (pauseCtx->state <= PAUSE_STATE_UNPAUSE_SETUP)))) {
        if (!IS_PAUSE_STATE_GAMEOVER) {
            switch (pauseCtx->pageIndex) {
                case PAUSE_ITEM:
                    KaleidoScope_UpdateItemCursor(play);
                    break;

                case PAUSE_MAP:
                    if (sInDungeonScene) {
                        KaleidoScope_UpdateDungeonCursor(play);
                    } else {
                        KaleidoScope_UpdateWorldMapCursor(play);
                    }
                    break;

                case PAUSE_QUEST:
                    KaleidoScope_UpdateQuestCursor(play);
                    break;

                case PAUSE_MASK:
                    KaleidoScope_UpdateMaskCursor(play);
                    break;
            }

            if ((pauseCtx->state == PAUSE_STATE_MAIN) &&
                ((pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) ||
                 (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG))) {
                KaleidoScope_HandlePageToggles(play, input);
            }
        }
        if (pauseCtx->state == PAUSE_STATE_MAIN) {
            KaleidoScope_UpdateNamePanel(play);
        }
    } else if (pauseCtx->state == PAUSE_STATE_OWLWARP_SELECT) {
        KaleidoScope_UpdateWorldMapCursor(play);
        KaleidoScope_UpdateNamePanel(play);
    }

    // Update the inventory editor
    if ((pauseCtx->debugEditor == DEBUG_EDITOR_INVENTORY_INIT) || (pauseCtx->debugEditor == DEBUG_EDITOR_INVENTORY)) {
        KaleidoScope_UpdateInventoryEditor(play);
    }
}
