#include "ultra64.h"
#include "global.h"

/*=====================================================================
 *                   Default Data: NORMAL0 Setting
 *=====================================================================
 */

/**
 * Setting      Mode      Function
 * ---------    ------    --------
 * NORMAL0      NORMAL    NORM1
 * CLIMEMAZE    NORMAL    NORM1
 * FORCEKEEP    NORMAL    NORM1
 * NORMAL4      NORMAL    NORM1
 */
CameraModeValue D_801B4710[] = {
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 0x0016, 4 },
	{ 0x000F, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 0x0054, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting      Mode        Function
 * ---------    --------    --------
 * NORMAL0      TARGET      PARA1
 * NORMAL0      ZORAFINZ    PARA1
 * NORMAL1      TARGET      PARA1
 * NANAME       TARGET      PARA1
 * DUNGEON0     ZORAFINZ    PARA1
 * TOWER0       TARGET      PARA1
 * CLIMEMAZE    TARGET      PARA1
 * KEEPBACK     TARGET      PARA1
 * BOSS_HAK     TARGET      PARA1
 * BOSS_KON     TARGET      PARA1
 * FORCEKEEP    TARGET      PARA1
 * PARALLEL1    TARGET      PARA1
 * NORMAL4      TARGET      PARA1
 */
CameraModeValue D_801B4738[] = {
	{ 0, 0 },
	{ 350, 1 },
	{ 50, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting      Mode            Function
 * ---------    ------------    --------
 * NORMAL0      FOLLOWTARGET    KEEP1
 * NORMAL3      FOLLOWTARGET    KEEP1
 * FUKAN0       FOLLOWTARGET    KEEP1
 * NORMAL1      FOLLOWTARGET    KEEP1
 * NANAME       FOLLOWTARGET    KEEP1
 * TOWER0       FOLLOWTARGET    KEEP1
 * CLIMEMAZE    FOLLOWTARGET    KEEP1
 * KEEPBACK     FOLLOWTARGET    KEEP1
 * FUKAN1       FOLLOWTARGET    KEEP1
 * BOSS_HAK     FOLLOWTARGET    KEEP1
 * MORAY        FOLLOWTARGET    KEEP1
 * NORMAL2      FOLLOWTARGET    KEEP1
 * WHIRLPOOL    FOLLOWTARGET    KEEP1
 * KOKKOGAME    FOLLOWTARGET    KEEP1
 * GIANT        FOLLOWTARGET    KEEP1
 * WATER2       FOLLOWTARGET    KEEP1
 * PARALLEL1    FOLLOWTARGET    KEEP1
 * NORMAL4      FOLLOWTARGET    KEEP1
 */
CameraModeValue D_801B4768[] = {
	{ -30, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ -5, 15 },
	{ 10, 16 },
	{ 0x000F, 17 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting      Mode      Function
 * ---------    ------    --------
 * NORMAL0      BATTLE    BATT1
 * NORMAL3      BATTLE    BATT1
 * FUKAN0       BATTLE    BATT1
 * NORMAL1      BATTLE    BATT1
 * NANAME       BATTLE    BATT1
 * TOWER0       BATTLE    BATT1
 * CLIMEMAZE    BATTLE    BATT1
 * KEEPBACK     BATTLE    BATT1
 * FUKAN1       BATTLE    BATT1
 * MORAY        BATTLE    BATT1
 * NORMAL2      BATTLE    BATT1
 * WHIRLPOOL    BATTLE    BATT1
 * KOKKOGAME    BATTLE    BATT1
 * GIANT        BATTLE    BATT1
 * WATER2       BATTLE    BATT1
 * PARALLEL1    BATTLE    BATT1
 * NORMAL4      BATTLE    BATT1
 */
CameraModeValue D_801B4798[] = {
	{ -30, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 10, 13 },
	{ 60, 14 },
	{ -5, 15 },
	{ 20, 16 },
	{ 0x0023, 17 },
	{ 0x0037, 7 },
	{ 0x0046, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting      Mode           Function
 * ---------    -----------    --------
 * NORMAL0      FIRSTPERSON    SUBJ1
 * NORMAL3      FIRSTPERSON    SUBJ1
 * FUKAN0       FIRSTPERSON    SUBJ1
 * NORMAL1      FIRSTPERSON    SUBJ1
 * NANAME       FIRSTPERSON    SUBJ1
 * CIRCLE0      FIRSTPERSON    SUBJ1
 * FIXED0       FIRSTPERSON    SUBJ1
 * DUNGEON0     FIRSTPERSON    SUBJ1
 * DUNGEON1     FIRSTPERSON    SUBJ1
 * CIRCLE3      FIRSTPERSON    SUBJ1
 * FIXED3       FIRSTPERSON    SUBJ1
 * TOWER0       FIRSTPERSON    SUBJ1
 * JCRUISING    FIRSTPERSON    SUBJ1
 * CLIMEMAZE    FIRSTPERSON    SUBJ1
 * DUNGEON2     FIRSTPERSON    SUBJ1
 * BOSS_SHIGE   FIRSTPERSON    SUBJ1
 * KEEPBACK     FIRSTPERSON    SUBJ1
 * CHUBOSS      FIRSTPERSON    SUBJ1
 * FUKAN1       FIRSTPERSON    SUBJ1
 * DUNGEON3     FIRSTPERSON    SUBJ1
 * ROOM0        FIRSTPERSON    SUBJ1
 * CIRCLE9      FIRSTPERSON    SUBJ1
 * ONTHEPOLE    FIRSTPERSON    SUBJ1
 * BOSS_LAST    FIRSTPERSON    SUBJ1
 * BOSS_INI     FIRSTPERSON    SUBJ1
 * BOSS_HAK     FIRSTPERSON    SUBJ1
 * BOSS_KON     FIRSTPERSON    SUBJ1
 * MORAY        FIRSTPERSON    SUBJ1
 * NORMAL2      FIRSTPERSON    SUBJ1
 * BOMBBOWL     FIRSTPERSON    SUBJ1
 * WHIRLPOOL    FIRSTPERSON    SUBJ1
 * KOKKOGAME    FIRSTPERSON    SUBJ1
 * GIANT        FIRSTPERSON    SUBJ1
 * ROOM1        FIRSTPERSON    SUBJ1
 * WATER2       FIRSTPERSON    SUBJ1
 * FORCEKEEP    FIRSTPERSON    SUBJ1
 * PARALLEL1    FIRSTPERSON    SUBJ1
 * ROOM2        FIRSTPERSON    SUBJ1
 * NORMAL4      FIRSTPERSON    SUBJ1
 * DUNGEON4     FIRSTPERSON    SUBJ1
 */
CameraModeValue D_801B47CC[] = {
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0, 9 },
};

/**
 * Setting      Mode    Function
 * ---------    ----    --------
 * NORMAL0      TALK    KEEP3
 * NORMAL3      TALK    KEEP3
 * FUKAN0       TALK    KEEP3
 * NORMAL1      TALK    KEEP3
 * NANAME       TALK    KEEP3
 * DUNGEON0     TALK    KEEP3
 * DUNGEON1     TALK    KEEP3
 * TOWER0       TALK    KEEP3
 * CLIMEMAZE    TALK    KEEP3
 * DUNGEON2     TALK    KEEP3
 * KEEPBACK     TALK    KEEP3
 * CHUBOSS      TALK    KEEP3
 * FUKAN1       TALK    KEEP3
 * DUNGEON3     TALK    KEEP3
 * ONTHEPOLE    TALK    KEEP3
 * BOSS_LAST    TALK    KEEP3
 * BOSS_INI     TALK    KEEP3
 * BOSS_HAK     TALK    KEEP3
 * BOSS_KON     TALK    KEEP3
 * MORAY        TALK    KEEP3
 * NORMAL2      TALK    KEEP3
 * WHIRLPOOL    TALK    KEEP3
 * KOKKOGAME    TALK    KEEP3
 * GIANT        TALK    KEEP3
 * FORCEKEEP    TALK    KEEP3
 * PARALLEL1    TALK    KEEP3
 * DUNGEON4     TALK    KEEP3
 */
CameraModeValue D_801B47F0[] = {
	{ -20, 0 },
	{ 80, 1 },
	{ 0x0096, 2 },
	{ 50, 13 },
	{ 0x0005, 14 },
	{ 20, 15 },
	{ 0x0005, 16 },
	{ 0x0028, 17 },
	{ 0x0023, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3500, 9 },
	{ 60, 18 },
};

/**
 * Setting      Mode     Function
 * ---------    -----    --------
 * NORMAL0      CLIMB    JUMP2
 * NORMAL3      CLIMB    JUMP2
 * FUKAN0       CLIMB    JUMP2
 * NORMAL1      CLIMB    JUMP2
 * NANAME       CLIMB    JUMP2
 * TOWER0       CLIMB    JUMP2
 * KEEPBACK     CLIMB    JUMP2
 * FUKAN1       CLIMB    JUMP2
 * INBUSH       CLIMB    JUMP2
 * BOSS_INI     CLIMB    JUMP2
 * BOSS_KON     CLIMB    JUMP2
 * MORAY        CLIMB    JUMP2
 * NORMAL2      CLIMB    JUMP2
 * WHIRLPOOL    CLIMB    JUMP2
 * KOKKOGAME    CLIMB    JUMP2
 * GIANT        CLIMB    JUMP2
 * WATER2       CLIMB    JUMP2
 * FORCEKEEP    CLIMB    JUMP2
 * PARALLEL1    CLIMB    JUMP2
 * NORMAL4      CLIMB    JUMP2
 */
CameraModeValue D_801B4824[] = {
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 20, 20 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0, 9 },
};

/**
 * Setting      Mode        Function
 * ---------    --------    --------
 * NORMAL0      BOWARROW    SUBJ1
 * NORMAL3      BOWARROW    SUBJ1
 * FUKAN0       BOWARROW    SUBJ1
 * NORMAL1      BOWARROW    SUBJ1
 * NANAME       BOWARROW    SUBJ1
 * DUNGEON0     BOWARROW    SUBJ1
 * DUNGEON1     BOWARROW    SUBJ1
 * TOWER0       BOWARROW    SUBJ1
 * JCRUISING    BOWARROW    SUBJ1
 * CLIMEMAZE    BOWARROW    SUBJ1
 * DUNGEON2     BOWARROW    SUBJ1
 * BOSS_SHIGE   BOWARROW    SUBJ1
 * KEEPBACK     BOWARROW    SUBJ1
 * CHUBOSS      BOWARROW    SUBJ1
 * FUKAN1       BOWARROW    SUBJ1
 * DUNGEON3     BOWARROW    SUBJ1
 * ROOM0        BOWARROW    SUBJ1
 * ONTHEPOLE    BOWARROW    SUBJ1
 * INBUSH       BOWARROW    SUBJ1
 * BOSS_LAST    BOWARROW    SUBJ1
 * BOSS_INI     BOWARROW    SUBJ1
 * BOSS_HAK     BOWARROW    SUBJ1
 * BOSS_KON     BOWARROW    SUBJ1
 * MORAY        BOWARROW    SUBJ1
 * NORMAL2      BOWARROW    SUBJ1
 * BOMBBOWL     BOWARROW    SUBJ1
 * WHIRLPOOL    BOWARROW    SUBJ1
 * KOKKOGAME    BOWARROW    SUBJ1
 * GIANT        BOWARROW    SUBJ1
 * ROOM1        BOWARROW    SUBJ1
 * WATER2       BOWARROW    SUBJ1
 * SOKONASI     BOWARROW    SUBJ1
 * FORCEKEEP    BOWARROW    SUBJ1
 * PARALLEL1    BOWARROW    SUBJ1
 * ROOM2        BOWARROW    SUBJ1
 * NORMAL4      BOWARROW    SUBJ1
 * DUNGEON4     BOWARROW    SUBJ1
 */
CameraModeValue D_801B4848[] = {
	{ 0xFFF9, 0 },
	{ 0x000E, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ -30, 17 },
	{ -5, 18 },
	{ 0x002D, 7 },
	{ 0x2000, 9 },
};

/**
 * Setting      Mode         Function
 * ---------    ---------    --------
 * NORMAL0      BOWARROWZ    SUBJ1
 * NORMAL3      BOWARROWZ    SUBJ1
 * HORSE0       BOWARROWZ    SUBJ1
 * FUKAN0       BOWARROWZ    SUBJ1
 * NORMAL1      BOWARROWZ    SUBJ1
 * NANAME       BOWARROWZ    SUBJ1
 * CIRCLE0      BOWARROWZ    SUBJ1
 * FIXED0       BOWARROWZ    SUBJ1
 * DUNGEON0     BOWARROWZ    SUBJ1
 * DUNGEON1     BOWARROWZ    SUBJ1
 * CIRCLE3      BOWARROWZ    SUBJ1
 * FIXED3       BOWARROWZ    SUBJ1
 * TOWER0       BOWARROWZ    SUBJ1
 * JCRUISING    BOWARROWZ    SUBJ1
 * CLIMEMAZE    BOWARROWZ    SUBJ1
 * DUNGEON2     BOWARROWZ    SUBJ1
 * BOSS_SHIGE   BOWARROWZ    SUBJ1
 * KEEPBACK     BOWARROWZ    SUBJ1
 * CHUBOSS      BOWARROWZ    SUBJ1
 * FUKAN1       BOWARROWZ    SUBJ1
 * DUNGEON3     BOWARROWZ    SUBJ1
 * ROOM0        BOWARROWZ    SUBJ1
 * CIRCLE9      BOWARROWZ    SUBJ1
 * ONTHEPOLE    BOWARROWZ    SUBJ1
 * INBUSH       BOWARROWZ    SUBJ1
 * BOSS_LAST    BOWARROWZ    SUBJ1
 * BOSS_INI     BOWARROWZ    SUBJ1
 * BOSS_HAK     BOWARROWZ    SUBJ1
 * BOSS_KON     BOWARROWZ    SUBJ1
 * MORAY        BOWARROWZ    SUBJ1
 * NORMAL2      BOWARROWZ    SUBJ1
 * BOMBBOWL     BOWARROWZ    SUBJ1
 * WHIRLPOOL    BOWARROWZ    SUBJ1
 * KOKKOGAME    BOWARROWZ    SUBJ1
 * GIANT        BOWARROWZ    SUBJ1
 * ROOM1        BOWARROWZ    SUBJ1
 * WATER2       BOWARROWZ    SUBJ1
 * SOKONASI     BOWARROWZ    SUBJ1
 * FORCEKEEP    BOWARROWZ    SUBJ1
 * PARALLEL1    BOWARROWZ    SUBJ1
 * ROOM2        BOWARROWZ    SUBJ1
 * NORMAL4      BOWARROWZ    SUBJ1
 * DUNGEON4     BOWARROWZ    SUBJ1
 */
CameraModeValue D_801B486C[] = {
	{ 20, 0 },
	{ 0x0046, 1 },
	{ 0x0046, 2 },
	{ 10, 4 },
	{ 0xFF88, 19 },
	{ 20, 17 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0x2000, 9 },
};

/**
 * Setting      Mode         Function
 * ---------    ---------    --------
 * NORMAL0      HOOKSHOT    SPEC5
 * NORMAL3      HOOKSHOT    SPEC5
 * FUKAN0       HOOKSHOT    SPEC5
 * NORMAL1      HOOKSHOT    SPEC5
 * NANAME       HOOKSHOT    SPEC5
 * DUNGEON0     HOOKSHOT    SPEC5
 * DUNGEON1     HOOKSHOT    SPEC5
 * TOWER0       HOOKSHOT    SPEC5
 * CLIMEMAZE    HOOKSHOT    SPEC5
 * DUNGEON2     HOOKSHOT    SPEC5
 * BOSS_SHIGE   HOOKSHOT    SPEC5
 * KEEPBACK     HOOKSHOT    SPEC5
 * CHUBOSS      HOOKSHOT    SPEC5
 * FUKAN1       HOOKSHOT    SPEC5
 * DUNGEON3     HOOKSHOT    SPEC5
 * ROOM0        HOOKSHOT    SPEC5
 * ONTHEPOLE    HOOKSHOT    SPEC5
 * INBUSH       HOOKSHOT    SPEC5
 * BOSS_LAST    HOOKSHOT    SPEC5
 * BOSS_INI     HOOKSHOT    SPEC5
 * BOSS_HAK     HOOKSHOT    SPEC5
 * BOSS_KON     HOOKSHOT    SPEC5
 * MORAY        HOOKSHOT    SPEC5
 * NORMAL2      HOOKSHOT    SPEC5
 * BOMBBOWL     HOOKSHOT    SPEC5
 * WHIRLPOOL    HOOKSHOT    SPEC5
 * KOKKOGAME    HOOKSHOT    SPEC5
 * GIANT        HOOKSHOT    SPEC5
 * ROOM1        HOOKSHOT    SPEC5
 * WATER2       HOOKSHOT    SPEC5
 * SOKONASI     HOOKSHOT    SPEC5
 * FORCEKEEP    HOOKSHOT    SPEC5
 * PARALLEL1    HOOKSHOT    SPEC5
 * ROOM2        HOOKSHOT    SPEC5
 * NORMAL4      HOOKSHOT    SPEC5
 * DUNGEON4     HOOKSHOT    SPEC5
 */
CameraModeValue D_801B4890[] = {
    { -20, 0 },    // yOffset
    { 80, 1 },     // eyeDist
    { 250, 2 },    // minDistForRot
    { 45, 3 },     // fovTarget
    { 60, 7 },     // atMaxLERPScale
    { 40, 8 },     // timerInit
    { 6, 12 },     // pitch
    { 0x2000, 9 }, // flags
};

/**
 * Setting     Mode         Function
 * --------    ---------    --------
 * NORMAL0     BOOMERANG    SUBJ1
 * DUNGEON0    BOOMERANG    SUBJ1
 * ROOM0       BOOMERANG    SUBJ1
 */
CameraModeValue D_801B48B0[] = {
	{ 0x0005, 0 },
	{ 50, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0x2000, 9 },
};

/**
 * Setting      Mode         Function
 * ---------    ---------    --------
 * NORMAL0      SLINGSHOT    SUBJ1
 * FUKAN0       SLINGSHOT    SUBJ1
 * NORMAL1      SLINGSHOT    SUBJ1
 * NANAME       SLINGSHOT    SUBJ1
 * CIRCLE0      SLINGSHOT    SUBJ1
 * FIXED0       SLINGSHOT    SUBJ1
 * DUNGEON0     SLINGSHOT    SUBJ1
 * DUNGEON1     SLINGSHOT    SUBJ1
 * CIRCLE3      SLINGSHOT    SUBJ1
 * FIXED3       SLINGSHOT    SUBJ1
 * TOWER0       SLINGSHOT    SUBJ1
 * JCRUISING    SLINGSHOT    SUBJ1
 * CLIMEMAZE    SLINGSHOT    SUBJ1
 * DUNGEON2     SLINGSHOT    SUBJ1
 * BOSS_SHIGE   SLINGSHOT    SUBJ1
 * KEEPBACK     SLINGSHOT    SUBJ1
 * CHUBOSS      SLINGSHOT    SUBJ1
 * FUKAN1       SLINGSHOT    SUBJ1
 * DUNGEON3     SLINGSHOT    SUBJ1
 * ROOM0        SLINGSHOT    SUBJ1
 * CIRCLE9      SLINGSHOT    SUBJ1
 * ONTHEPOLE    SLINGSHOT    SUBJ1
 * INBUSH       SLINGSHOT    SUBJ1
 * BOSS_LAST    SLINGSHOT    SUBJ1
 * BOSS_INI     SLINGSHOT    SUBJ1
 * BOSS_HAK     SLINGSHOT    SUBJ1
 * NORMAL2      SLINGSHOT    SUBJ1
 * BOMBBOWL     SLINGSHOT    SUBJ1
 * KOKKOGAME    SLINGSHOT    SUBJ1
 * GIANT        SLINGSHOT    SUBJ1
 * ROOM1        SLINGSHOT    SUBJ1
 * SOKONASI     SLINGSHOT    SUBJ1
 * FORCEKEEP    SLINGSHOT    SUBJ1
 * PARALLEL1    SLINGSHOT    SUBJ1
 * ROOM2        SLINGSHOT    SUBJ1
 * NORMAL4      SLINGSHOT    SUBJ1
 * DUNGEON4     SLINGSHOT    SUBJ1
 */
CameraModeValue D_801B48D4[] = {
	{ 0xFFF9, 0 },
	{ 0x000E, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ -50, 17 },
	{ -10, 18 },
	{ 0x002D, 7 },
	{ 0x2000, 9 },
};

/**
 * Setting      Mode      Function
 * ---------    ------    --------
 * NORMAL0      CLIMBZ    JUMP2
 * NORMAL3      CLIMBZ    JUMP2
 * FUKAN0       CLIMBZ    JUMP2
 * NORMAL1      CLIMBZ    JUMP2
 * NANAME       CLIMBZ    JUMP2
 * TOWER0       CLIMBZ    JUMP2
 * FUKAN1       CLIMBZ    JUMP2
 * INBUSH       CLIMBZ    JUMP2
 * BOSS_INI     CLIMBZ    JUMP2
 * BOSS_KON     CLIMBZ    JUMP2
 * MORAY        CLIMBZ    JUMP2
 * NORMAL2      CLIMBZ    JUMP2
 * WHIRLPOOL    CLIMBZ    JUMP2
 * KOKKOGAME    CLIMBZ    JUMP2
 * GIANT        CLIMBZ    JUMP2
 * WATER2       CLIMBZ    JUMP2
 * FORCEKEEP    CLIMBZ    JUMP2
 * PARALLEL1    CLIMBZ    JUMP2
 * NORMAL4      CLIMBZ    JUMP2
 */
CameraModeValue D_801B48F8[] = {
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 20, 20 },
	{ 0x03E7, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x2006, 9 },
};

/**
 * Setting      Mode    Function
 * ---------    ----    --------
 * NORMAL0      JUMP    NORM1
 * NORMAL3      JUMP    NORM1
 * NORMAL1      JUMP    NORM1
 * NANAME       JUMP    NORM1
 * CLIMEMAZE    JUMP    NORM1
 * KEEPBACK     JUMP    NORM1
 * BOSS_KON     JUMP    NORM1
 * MORAY        JUMP    NORM1
 * WHIRLPOOL    JUMP    NORM1
 * WATER2       JUMP    NORM1
 * FORCEKEEP    JUMP    NORM1
 * PARALLEL1    JUMP    NORM1
 * NORMAL4      JUMP    NORM1
 */
CameraModeValue D_801B491C[] = {
	{ -20, 0 },
	{ 0x00F0, 1 },
	{ 0x0154, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4944[] = {
    /* CAM_FUNC_PARA1 */
	{ -40, 0 },
	{ 0x0140, 1 },
	{ 50, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0008, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x0086, 9 },
	{ 60, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4974[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 300, 1 },
	{ 50, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2086, 9 },
	{ 60, 11 },
	{ 0x0002, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B49A4[] = {
    /* CAM_FUNC_PARA1 */
	{ -10, 0 },
	{ 0x0140, 1 },
	{ 100, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 0x0004, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 20, 8 },
	{ 0x0088, 9 },
	{ 60, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B49D4[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 300, 1 },
	{ -20, 2 },
	{ 50, 3 },
	{ 0, 10 },
	{ 50, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 20, 8 },
	{ 0, 9 },
	{ 60, 11 },
	{ 10, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4A04[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 300, 1 },
	{ -20, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 50, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 20, 8 },
	{ 0x0002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4A34[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4A5C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 350, 1 },
	{ 0x0005, 2 },
	{ 0x002D, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2022, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4A8C[] = {
    /* CAM_FUNC_KEEP1 */
	{ -5, 0 },
	{ 220, 1 },
	{ 0x00F0, 2 },
	{ 0x0005, 13 },
	{ 0x004B, 14 },
	{ 10, 15 },
	{ 0x0005, 16 },
	{ 0x0028, 17 },
	{ 50, 7 },
	{ 0x0028, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4ABC[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 50, 17 },
	{ 0x0041, 18 },
	{ 0x002D, 7 },
	{ 0, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4AE0[] = {
    /* CAM_FUNC_NORM1 */
	{ 50, 0 },
	{ 0x00A0, 1 },
	{ 0x00FF, 2 },
	{ 0xFFFE, 3 },
	{ 0x000C, 4 },
	{ 10, 5 },
	{ 0x0028, 6 },
	{ 0x005C, 7 },
	{ 0x0058, 8 },
	{ 0x0087, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4B08[] = {
    /* CAM_FUNC_PARA1 */
	{ 100, 0 },
	{ 300, 1 },
	{ -20, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0004, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 60, 8 },
	{ 0xFF22, 9 },
	{ 80, 11 },
	{ 20, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4B38[] = {
    /* CAM_FUNC_NORM1 */
	{ 0xFFB0, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 0x0028, 3 },
	{ 20, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 80, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4B60[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFBA, 0 },
	{ 350, 1 },
	{ 10, 2 },
	{ 10, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 90, 8 },
	{ 0x200E, 9 },
	{ 90, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4B90[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 0x00A0, 1 },
	{ 0x0190, 2 },
	{ 0, 3 },
	{ 0x0012, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 80, 7 },
	{ 60, 8 },
	{ 0x008F, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B4BB8[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0x0005, 0 },
	{ 100, 1 },
	{ 100, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0x2000, 9 },
};

/*=====================================================================
 *                   Custom Data: NORMAL3 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL3    NORMAL    JUMP3
 */
CameraModeValue D_801B4BDC[] = {
	{ -40, 0 },
	{ 0x0118, 1 },
	{ 300, 2 },
	{ 20, 3 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 100, 8 },
	{ 0x0084, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL3    TARGET    PARA1
 */
CameraModeValue D_801B4C04[] = {
	{ -50, 0 },
	{ 0x0118, 1 },
	{ 0x0028, 2 },
	{ 10, 3 },
	{ 0, 10 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 100, 8 },
	{ 0x2003, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting     Mode        Function
 * --------    --------    --------
 * NORMAL3     FREEFALL    JUMP3
 * BOSS_KON    FREEFALL    JUMP3
 * MORAY       FREEFALL    JUMP3
 * WATER2      FREEFALL    JUMP3
 */
CameraModeValue D_801B4C34[] = {
	{ 0, 0 },
	{ 80, 1 },
	{ 100, 2 },
	{ 30, 3 },
	{ 10, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 80, 7 },
	{ 20, 8 },
	{ 0x0004, 9 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * NORMAL3    GORONJUMP    JUMP3
 * WATER2     GORONJUMP    JUMP3
 */
CameraModeValue D_801B4C5C[] = {
	{ -40, 0 },
	{ 0x0096, 1 },
	{ 0x00F0, 2 },
	{ -5, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 0x0046, 7 },
	{ 0x0028, 8 },
	{ 0x000C, 9 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * NORMAL3    NUTSFLY    JUMP3
 * WATER2     NUTSFLY    JUMP3
 */
CameraModeValue D_801B4C84[] = {
	{ -40, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 10, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x0005, 9 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * NORMAL3    NUTSHIDE    JUMP3
 * WATER2     NUTSHIDE    JUMP3
 */
CameraModeValue D_801B4CAC[] = {
	{ 0xFFC4, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ -15, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x0085, 9 },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * NORMAL3    STILL    NORM1
 * WATER2     STILL    NORM1
 */
CameraModeValue D_801B4CD4[] = {
	{ -40, 0 },
	{ 80, 1 },
	{ 300, 2 },
	{ 20, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting     Mode         Function
 * --------    ---------    --------
 * NORMAL3     GORONDASH    JUMP3
 * BOSS_KON    GORONDASH    JUMP3
 */
CameraModeValue D_801B4CFC[] = {
	{ -40, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 0x0005, 3 },
	{ 20, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 80, 7 },
	{ 0x0023, 8 },
	{ 0x000C, 9 },
};

/*=====================================================================
 *                   Custom Data: CIRCLE5 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE5    NORMAL    UNIQ2
 */
CameraModeValue D_801B4D24[] = {
	{ -40, 0 },
	{ 60, 1 },
	{ 60, 7 },
	{ 0x0002, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE5    TARGET    UNIQ2
 */
CameraModeValue D_801B4D34[] = {
	{ -30, 0 },
	{ 0x002D, 1 },
	{ 100, 7 },
	{ 0x2001, 9 },
};

/*=====================================================================
 *                   Custom Data: HORSE0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * HORSE0     NORMAL    NORM3
 */
CameraModeValue D_801B4D44[] = {
    { -50, 0 },    // yOffset
    { 220, 1 },    // distMin
    { 250, 2 },    // distMax
    { 10, 3 },     // yawUpdateRateInv
    { 10, 4 },     // pitchUpdateRateInv
    { 20, 5 },     // fovTarget
    { 60, 7 },     // maxAtLERPScale
    { 80, 8 },     // pitchTarget
    { 0x0620, 9 }, // flags
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * HORSE0     TARGET    NORM3
 */
CameraModeValue D_801B4D68[] = {
    { -40, 0 },    // yOffset
    { 180, 1 },    // distMin
    { 200, 2 },    // distMax
    { -3, 3 },     // yawUpdateRateInv
    { 2, 4 },      // pitchUpdateRateInv
    { 100, 5 },    // fovTarget
    { 50, 7 },     // maxAtLERPScale
    { 90, 8 },     // pitchTarget
    { 0x2602, 9 }, // flags
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * HORSE0     JUMP    NORM3
 */
CameraModeValue D_801B4D8C[] = {
    { -50, 0 },    // yOffset
    { 220, 1 },    // distMin
    { 260, 2 },    // distMax
    { 10, 3 },     // yawUpdateRateInv
    { 10, 4 },     // pitchUpdateRateInv
    { 20, 5 },     // fovTarget
    { 60, 7 },     // maxAtLERPScale
    { 50, 8 },     // pitchTarge
    { 0x0600, 9 }, // flags
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * HORSE0     BOWARROW    SUBJ1
 */
CameraModeValue D_801B4DB0[] = {
	{ 0xFFF9, 0 },
	{ 0x000E, 1 },
	{ 100, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ -30, 17 },
	{ -5, 18 },
	{ 0x0028, 7 },
	{ 0x2600, 9 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * HORSE0     SLINGSHOT    SUBJ1
 */
CameraModeValue D_801B4DD4[] = {
	{ 0xFFF9, 0 },
	{ 0x000E, 1 },
	{ 100, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ -50, 17 },
	{ -10, 18 },
	{ 0x002D, 7 },
	{ 0x2000, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * HORSE0     BATTLE    BATT1
 */
CameraModeValue D_801B4DF8[] = {
	{ 0xFFC4, 0 },
	{ 180, 1 },
	{ 0x0118, 2 },
	{ 10, 13 },
	{ 60, 14 },
	{ -5, 15 },
	{ 20, 16 },
	{ 60, 17 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode            Function
 * -------    ------------    --------
 * HORSE0     FOLLOWTARGET    KEEP1
 */
CameraModeValue D_801B4E2C[] = {
	{ 0xFFC4, 0 },
	{ 180, 1 },
	{ 220, 2 },
	{ 0x0019, 13 },
	{ 0x002D, 14 },
	{ -5, 15 },
	{ 0x000F, 16 },
	{ 0x000F, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2601, 9 },
	{ 20, 11 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * HORSE0     TALK    KEEP3
 */
CameraModeValue D_801B4E5C[] = {
	{ -50, 0 },
	{ 0x008C, 1 },
	{ 200, 2 },
	{ 0x0028, 13 },
	{ 10, 14 },
	{ 0, 15 },
	{ 0x0005, 16 },
	{ 100, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3500, 9 },
	{ 60, 18 },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * HORSE0     STILL    NORM3
 */
CameraModeValue D_801B4E90[] = {
    { -40, 0 },    // yOffset
    { 180, 1 },    // distMin
    { 200, 2 },    // distMax
    { -3, 3 },     // yawUpdateRateInv
    { 100, 4 },    // pitchUpdateRateInv
    { 100, 5 },    // fovTarget
    { 60, 7 },     // maxAtLERPScale
    { 10, 8 },     // pitchTarget
    { 0xFF80, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data: ZORA0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * ZORA0      NORMAL    NORM3
 */
CameraModeValue D_801B4EB4[] = {
    { -20, 0 },    // yOffset
    { 250, 1 },    // distMin
    { 250, 2 },    // distMax
    { 0, 3 },      // yawUpdateRateInv
    { 20, 4 },     // pitchUpdateRateInv
    { 20, 5 },     // fovTarget
    { 60, 7 },     // maxAtLERPScale
    { 50, 8 },     // pitchTarget
    { 0x0680, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data: PREREND0 Setting
 *=====================================================================
 */

/**
 * Setting     Mode      Function
 * --------    ------    --------
 * PREREND0    NORMAL    FIXD3
 */
CameraModeValue D_801B4ED8[] = {
	{ 0x0000, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data: PREREND1 Setting
 *=====================================================================
 */

/**
 * Setting     Mode      Function
 * --------    ------    --------
 * PREREND1    NORMAL    UNIQ7
 */
CameraModeValue D_801B4EDC[] = {
	{ 60, 7 },
	{ 0x0000, 9 },  // flags
};

/*=====================================================================
 *                   Custom Data: DOORC Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * DOORC      NORMAL    SPEC9
 */
CameraModeValue D_801B4EE4[] = {
	{ -5, 0 },
	{ 60, 7 },
	{ 0x4202, 9 },  // flags
};

/*=====================================================================
 *                   Custom Data: DEMO0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * DEMO0      NORMAL    DEMO1
 */
CameraModeValue D_801B4EF0[] = {
	{ 0x3200, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data:
 *=====================================================================
 */

/**
 * Setting      Mode      Function
 * -------      ------    --------
 * FREE0        NORMAL    UNIQ6
 * NAVI         NORMAL    UNIQ6
 * TRANSFORM    NORMAL    DEMO4
 * TRANSFORM    JUMP      DEMO5
 * ATTENTION    NORMAL    DEMO1
 * WARP1        NORMAL    DEMO3
 * STOP0        NORMAL    UNIQ6
 * CONNECT0     NORMAL    DEMO0
 */
CameraModeValue D_801B4EF4[] = {
    { 0xFF00, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data: FUKAN0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * FUKAN0     NORMAL      NORM1
 * FUKAN0     PUSHPULL    NORM1
 * FUKAN1     PUSHPULL    NORM1
 * INBUSH     PUSHPULL    NORM1
 */
CameraModeValue D_801B4EF8[] = {
	{ -40, 0 },
	{ 0x0258, 1 },
	{ 0x0258, 2 },
	{ 0x002D, 3 },
	{ 50, 4 },
	{ 10, 5 },
	{ 50, 6 },
	{ 0x002D, 7 },
	{ 90, 8 },
	{ 0x0042, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * FUKAN0     TARGET    PARA1
 * FUKAN1     TARGET    PARA1
 */
CameraModeValue D_801B4F20[] = {
	{ -40, 0 },
	{ 0x0190, 1 },
	{ 0x0019, 2 },
	{ 60, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x2002, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * FUKAN0     JUMP    NORM1
 * FUKAN1     JUMP    NORM1
 */
CameraModeValue D_801B4F50[] = {
	{ -40, 0 },
	{ 0x0258, 1 },
	{ 0x0258, 2 },
	{ 0x002D, 3 },
	{ 50, 4 },
	{ 10, 5 },
	{ 50, 6 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * FUKAN0     STILL    NORM1
 */
CameraModeValue D_801B4F78[] = {
	{ -40, 0 },
	{ 0x0258, 1 },
	{ 0x0258, 2 },
	{ 0x002D, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x002D, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/*=====================================================================
 *                   Custom Data: NORMAL1 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL1    NORMAL    NORM1
 */
CameraModeValue D_801B4FA0[] = {
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 0x000F, 3 },
	{ 0x0012, 4 },
	{ 0x000C, 5 },
	{ 0x0046, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0002, 9 },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * NORMAL1    STILL    NORM1
 */
CameraModeValue D_801B4FC8[] = {
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 0x000F, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/*=====================================================================
 *                   Custom Data: NANAME Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NANAME     NORMAL    NORM4
 */
CameraModeValue D_801B4FF0[] = {
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 0x0012, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0003, 9 },
};

/*=====================================================================
 *                   Custom Data: CIRCLE0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE0    NORMAL    FIXD2
 */
CameraModeValue D_801B5018[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 10, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0x0001, 9 },
};

/**
 * Setting    Mode            Function
 * -------    ------------    --------
 * CIRCLE0    FOLLOWTARGET    FIXD2
 * CIRCLE3    FOLLOWTARGET    FIXD2
 * CIRCLE9    FOLLOWTARGET    FIXD2
 */
CameraModeValue D_801B5034[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 80, 5 },
	{ 60, 7 },
	{ 0x2040, 9 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * CIRCLE0    TALK    FIXD2
 * CIRCLE3    TALK    FIXD2
 * CIRCLE9    TALK    FIXD2
 */
CameraModeValue D_801B5050[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 200, 2 },
	{ 100, 4 },
	{ 50, 5 },
	{ 0x002D, 7 },
	{ 0x2080, 9 },
};

/*=====================================================================
 *                   Custom Data: FIXED0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * FIXED0     NORMAL    FIXD1
 */
CameraModeValue D_801B506C[] = {
	{ -40, 0 },
	{ 10, 4 },
	{ 60, 7 },
	{ 0, 9 },
};

/*=====================================================================
 *                   Custom Data: SPIRAL Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * SPIRAL     NORMAL    SPEC8
 */
CameraModeValue D_801B507C[] = {
    { -40, 0 },    // yOffset
    { 50, 4 },     // eyeStepScale
    { 80, 5 },     // posStepScale
    { 60, 7 },     // fov
    { 10, 12 },    // maxDoorCutsceneCounter
    { 0x0001, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data: DUNGEON0 Setting
 *=====================================================================
 */

/**
 * Setting     Mode      Function
 * --------    ------    --------
 * DUNGEON0    NORMAL    NORM1
 */
CameraModeValue D_801B5094[] = {
	{ -20, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 0x0005, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * DUNGEON0      TARGET    PARA1
 * DUNGEON1      TARGET    PARA1
 * DUNGEON2      TARGET    PARA1
 * BOSS_SHIGE    TARGET    PARA1
 * CHUBOSS       TARGET    PARA1
 * BOSS_LAST     TARGET    PARA1
 * ROOM1         TARGET    PARA1
 * ROOM2         TARGET    PARA1
 */
CameraModeValue D_801B50BC[] = {
	{ 0, 0 },
	{ 200, 1 },
	{ 0x0019, 2 },
	{ 0x0005, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2042, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting      Mode            Function
 * ---------    ------------    --------
 * DUNGEON0     FOLLOWTARGET    KEEP1
 * DUNGEON1     FOLLOWTARGET    KEEP1
 * DUNGEON2     FOLLOWTARGET    KEEP1
 * DUNGEON3     FOLLOWTARGET    KEEP1
 * ONTHEPOLE    FOLLOWTARGET    KEEP1
 * DUNGEON4     FOLLOWTARGET    KEEP1
 */
CameraModeValue D_801B50EC[] = {
	{ -20, 0 },
	{ 0x0078, 1 },
	{ 0x008C, 2 },
	{ 0x0019, 13 },
	{ 0x002D, 14 },
	{ -5, 15 },
	{ 0x000F, 16 },
	{ 0x000F, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2001, 9 },
	{ 20, 11 },
};

/**
 * Setting      Mode      Function
 * ---------    ------    --------
 * DUNGEON0     BATTLE    BATT1
 * DUNGEON1     BATTLE    BATT1
 * DUNGEON3     BATTLE    BATT1
 * ONTHEPOLE    BATTLE    BATT1
 * DUNGEON4     BATTLE    BATT1
 */
CameraModeValue D_801B511C[] = {
	{ -30, 0 },
	{ 0x0096, 1 },
	{ 0x00F0, 2 },
	{ 10, 13 },
	{ 50, 14 },
	{ 0x0005, 15 },
	{ 10, 16 },
	{ 0x0019, 17 },
	{ 50, 7 },
	{ 60, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 50, 18 },
};

/**
 * Setting       Mode          Function
 * ----------    ----------    --------
 * DUNGEON0      BOOMFOLLOW    KEEP1
 * DUNGEON1      BOOMFOLLOW    KEEP1
 * DUNGEON2      BOOMFOLLOW    KEEP1
 * BOSS_SHIGE    BOOMFOLLOW    KEEP1
 * CHUBOSS       BOOMFOLLOW    KEEP1
 * DUNGEON3      BOOMFOLLOW    KEEP1
 * ONTHEPOLE     BOOMFOLLOW    KEEP1
 * BOSS_LAST     BOOMFOLLOW    KEEP1
 * BOSS_HAK      BOOMFOLLOW    KEEP1
 * DUNGEON4      BOOMFOLLOW    KEEP1
 */
CameraModeValue D_801B5150[] = {
	{ -5, 0 },
	{ 0x0096, 1 },
	{ 0x00F0, 2 },
	{ 0x0005, 13 },
	{ 0x0041, 14 },
	{ 10, 15 },
	{ 0x0005, 16 },
	{ 0x0028, 17 },
	{ 0x0037, 7 },
	{ 0x0028, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting     Mode    Function
 * --------    ----    --------
 * DUNGEON0    JUMP    NORM1
 */
CameraModeValue D_801B5180[] = {
	{ -20, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 0x0005, 3 },
	{ 0x0018, 4 },
	{ 0x0005, 5 },
	{ 50, 6 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting       Mode        Function
 * ----------    --------    --------
 * DUNGEON0      FREEFALL    PARA1
 * DUNGEON1      FREEFALL    PARA1
 * DUNGEON2      FREEFALL    PARA1
 * BOSS_SHIGE    FREEFALL    PARA1
 * CHUBOSS       FREEFALL    PARA1
 * DUNGEON3      FREEFALL    PARA1
 * ONTHEPOLE     FREEFALL    PARA1
 * BOSS_LAST     FREEFALL    PARA1
 * BOSS_HAK      FREEFALL    PARA1
 * ROOM1         FREEFALL    PARA1
 * ROOM2         FREEFALL    PARA1
 * DUNGEON4      FREEFALL    PARA1
 */
CameraModeValue D_801B51A8[] = {
	{ -10, 0 },
	{ 250, 1 },
	{ 100, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 0x0004, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 10, 8 },
	{ 0x0088, 9 },
	{ 0x0046, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting       Mode     Function
 * ----------    -----    --------
 * DUNGEON0      CLIMB    JUMP2
 * DUNGEON1      CLIMB    JUMP2
 * DUNGEON2      CLIMB    JUMP2
 * BOSS_SHIGE    CLIMB    JUMP2
 * CHUBOSS       CLIMB    JUMP2
 * DUNGEON3      CLIMB    JUMP2
 * BOSS_LAST     CLIMB    JUMP2
 * BOSS_HAK      CLIMB    JUMP2
 * ROOM1         CLIMB    JUMP2
 * SOKONASI      CLIMB    JUMP2
 * ROOM2         CLIMB    JUMP2
 * DUNGEON4      CLIMB    JUMP2
 */
CameraModeValue D_801B51D8[] = {
	{ -40, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 20, 20 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0, 9 },
};

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * DUNGEON0      CLIMBZ    JUMP2
 * DUNGEON1      CLIMBZ    JUMP2
 * DUNGEON2      CLIMBZ    JUMP2
 * BOSS_SHIGE    CLIMBZ    JUMP2
 * CHUBOSS       CLIMBZ    JUMP2
 * DUNGEON3      CLIMBZ    JUMP2
 * BOSS_LAST     CLIMBZ    JUMP2
 * BOSS_HAK      CLIMBZ    JUMP2
 * ROOM1         CLIMBZ    JUMP2
 * SOKONASI      CLIMBZ    JUMP2
 * ROOM2         CLIMBZ    JUMP2
 * DUNGEON4      CLIMBZ    JUMP2
 */
CameraModeValue D_801B51FC[] = {
	{ -40, 0 },
	{ 250, 1 },
	{ 250, 2 },
	{ 20, 20 },
	{ 0x03E7, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x2006, 9 },
};

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * DUNGEON0      CHARGE    PARA1
 * DUNGEON1      CHARGE    PARA1
 * DUNGEON2      CHARGE    PARA1
 * BOSS_SHIGE    CHARGE    PARA1
 * CHUBOSS       CHARGE    PARA1
 * DUNGEON3      CHARGE    PARA1
 * ONTHEPOLE     CHARGE    PARA1
 * BOSS_LAST     CHARGE    PARA1
 * BOSS_HAK      CHARGE    PARA1
 * ROOM1         CHARGE    PARA1
 * ROOM2         CHARGE    PARA1
 * DUNGEON4      CHARGE    PARA1
 */
CameraModeValue D_801B5220[] = {
	{ 0, 0 },
	{ 250, 1 },
	{ -20, 2 },
	{ 50, 3 },
	{ 0, 10 },
	{ 50, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0, 9 },
	{ 60, 11 },
	{ 10, 12 },
};

/**
 * Setting     Mode       Function
 * --------    -------    --------
 * DUNGEON0    CHARGEZ    PARA1
 */
CameraModeValue D_801B5250[] = {
	{ 50, 0 },
	{ 250, 1 },
	{ -20, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 50, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 20, 8 },
	{ 0x0002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting       Mode    Function
 * ----------    ----    --------
 * DUNGEON0      HANG    PARA1
 * DUNGEON1      HANG    PARA1
 * DUNGEON2      HANG    PARA1
 * BOSS_SHIGE    HANG    PARA1
 * CHUBOSS       HANG    PARA1
 * DUNGEON3      HANG    PARA1
 * BOSS_LAST     HANG    PARA1
 * BOSS_HAK      HANG    PARA1
 * ROOM1         HANG    PARA1
 * ROOM2         HANG    PARA1
 * DUNGEON4      HANG    PARA1
 */
CameraModeValue D_801B5280[] = {
	{ -40, 0 },
	{ 220, 1 },
	{ 50, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 10, 8 },
	{ 0x0086, 9 },
	{ 60, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting       Mode     Function
 * ----------    -----    --------
 * DUNGEON0      HANGZ    PARA1
 * DUNGEON1      HANGZ    PARA1
 * DUNGEON2      HANGZ    PARA1
 * BOSS_SHIGE    HANGZ    PARA1
 * CHUBOSS       HANGZ    PARA1
 * DUNGEON3      HANGZ    PARA1
 * BOSS_LAST     HANGZ    PARA1
 * BOSS_HAK      HANGZ    PARA1
 * ROOM1         HANGZ    PARA1
 * ROOM2         HANGZ    PARA1
 * DUNGEON4      HANGZ    PARA1
 */
CameraModeValue D_801B52B0[] = {
	{ 0xFFB0, 0 },
	{ 250, 1 },
	{ 50, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 10, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 10, 8 },
	{ 0x2086, 9 },
	{ 60, 11 },
	{ 0x0002, 12 },
};

/**
 * Setting     Mode     Function
 * --------    -----    --------
 * DUNGEON0    STILL    NORM1
 */
CameraModeValue D_801B52E0[] = {
	{ -10, 0 },
	{ 180, 1 },
	{ 220, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 10, 8 },
	{ 0xF003, 9 },
};

/**
 * Setting       Mode        Function
 * ----------    --------    --------
 * DUNGEON0      PUSHPULL    PARA1
 * BOSS_SHIGE    PUSHPULL    PARA1
 * CHUBOSS       PUSHPULL    PARA1
 * BOSS_LAST     PUSHPULL    PARA1
 * BOSS_HAK      PUSHPULL    PARA1
 * DUNGEON4      PUSHPULL    PARA1
 */
CameraModeValue D_801B5308[] = {
	{ 0, 0 },
	{ 250, 1 },
	{ 0x0005, 2 },
	{ 30, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2022, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/*=====================================================================
 *                   Custom Data: ITEM0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * ITEM0      NORMAL    KEEP4
 */
CameraModeValue D_801B5338[] = {
	{ 0x0005, 0 },
	{ 0x0046, 1 },
	{ 0x0019, 3 },
	{ 0, 10 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM0      JUMP    KEEP4
 */
CameraModeValue D_801B535C[] = {
	{ -30, 0 },
	{ 0x0023, 1 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0006, 18 },
	{ 80, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM0      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5380[] = {
	{ -15, 0 },
	{ 90, 1 },
	{ -8, 3 },
	{ 0, 10 },
	{ 0, 18 },
	{ 60, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM0      GORONDASH    KEEP4
 */
CameraModeValue D_801B53A4[] = {
	{ 20, 0 },
	{ 0x002D, 1 },
	{ 0x0037, 3 },
	{ 0, 10 },
	{ 0x000C, 18 },
	{ 0x0037, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM0      NUTSFLY    KEEP4
 */
CameraModeValue D_801B53C8[] = {
	{ 10, 0 },
	{ 0x0046, 1 },
	{ 30, 3 },
	{ 0, 10 },
	{ 0x0004, 18 },
	{ 0x002A, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/*=====================================================================
 *                   Custom Data: ITEM1 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * ITEM1      NORMAL    KEEP4
 */
CameraModeValue D_801B53EC[] = {
	{ -45, 0 },
	{ 0x004B, 1 },
	{ 0xFFF4, 3 },
	{ 0x00A5, 10 },
	{ 0x0005, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM1      JUMP    KEEP4
 */
CameraModeValue D_801B5410[] = {
	{ -40, 0 },
	{ 0x0046, 1 },
	{ 20, 3 },
	{ 0x008C, 10 },
	{ 0x0005, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM1      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5434[] = {
	{ -20, 0 },
	{ 0x0055, 1 },
	{ -5, 3 },
	{ 0x008C, 10 },
	{ 0x000F, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM1      GORONDASH    KEEP4
 */
CameraModeValue D_801B5458[] = {
	{ -50, 0 },
	{ 0x005F, 1 },
	{ -15, 3 },
	{ 0x00A0, 10 },
	{ 0x0006, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM1      NUTSFLY    KEEP4
 */
CameraModeValue D_801B547C[] = {
	{ 0xFFC4, 0 },
	{ 0x0046, 1 },
	{ -15, 3 },
	{ 0xFF74, 10 },
	{ 30, 18 },
	{ 0x0046, 7 },
	{ 0xFF0C, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/*=====================================================================
 *                   Custom Data: ITEM2 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * ITEM2      NORMAL    KEEP4
 */
CameraModeValue D_801B54A0[] = {
	{ -40, 0 },
	{ 0x006E, 1 },
	{ 0x0005, 3 },
	{ 0x0096, 10 },
	{ 0x0005, 18 },
	{ 0x0041, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM2      JUMP    KEEP4
 */
CameraModeValue D_801B54C4[] = {
	{ 0xFFC4, 0 },
	{ 0x0082, 1 },
	{ -10, 3 },
	{ 0x00AA, 10 },
	{ 0x0005, 18 },
	{ 0x0041, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM2      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B54E8[] = {
	{ -40, 0 },
	{ 0x006E, 1 },
	{ 0, 3 },
	{ 0x008C, 10 },
	{ 0x0005, 18 },
	{ 0x0041, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM2      GORONDASH    KEEP4
 */
CameraModeValue D_801B550C[] = {
	{ -50, 0 },
	{ 0x008C, 1 },
	{ -10, 3 },
	{ 0x00A0, 10 },
	{ 0x0005, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM2      NUTSFLY    KEEP4
 */
CameraModeValue D_801B5530[] = {
	{ 0xFFC4, 0 },
	{ 0x0078, 1 },
	{ -8, 3 },
	{ 0x0096, 10 },
	{ 0x0005, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/*=====================================================================
 *                   Custom Data: ITEM3 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * ITEM3      NORMAL    KEEP4
 */
CameraModeValue D_801B5554[] = {
	{ -15, 0 },
	{ 0x0041, 1 },
	{ 50, 3 },
	{ 0xFF65, 10 },
	{ 0x0005, 18 },
	{ 0x004B, 7 },
	{ 0xFF0C, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM3      JUMP    KEEP4
 */
CameraModeValue D_801B5578[] = {
	{ -20, 0 },
	{ 60, 1 },
	{ 50, 3 },
	{ 0xFF65, 10 },
	{ 0x0005, 18 },
	{ 0x004B, 7 },
	{ 0xFF0C, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM3      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B559C[] = {
	{ -15, 0 },
	{ 60, 1 },
	{ 0x0028, 3 },
	{ 0x00AA, 10 },
	{ 0x0005, 18 },
	{ 0x004B, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM3      GORONDASH    KEEP4
 */
CameraModeValue D_801B55C0[] = {
	{ -25, 0 },
	{ 0x005F, 1 },
	{ 50, 3 },
	{ 0xFF65, 10 },
	{ 0x0005, 18 },
	{ 0x004B, 7 },
	{ 0xFF0C, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM3      NUTSFLY    KEEP4
 */
CameraModeValue D_801B55E4[] = {
	{ -20, 0 },
	{ 0x004B, 1 },
	{ 0x002D, 3 },
	{ 0xFF6A, 10 },
	{ -5, 18 },
	{ 0x004B, 7 },
	{ 0xFF0C, 9 },
	{ 0x0019, 4 },
	{ 0x0006, 12 },
};

/*=====================================================================
 *                   Custom Data: WARP0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * WARP0      NORMAL    KEEP4
 */
CameraModeValue D_801B5608[] = {
	{ -45, 0 },
	{ 0x00A5, 1 },
	{ 0, 3 },
	{ 0x00B2, 10 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0xFF4E, 9 },
	{ 30, 4 },
	{ 10, 12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * WARP0      JUMP    KEEP4
 */
CameraModeValue D_801B562C[] = {
	{ 0xFFC9, 0 },
	{ 180, 1 },
	{ 0, 3 },
	{ 0x00B2, 10 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0xFF4E, 9 },
	{ 30, 4 },
	{ 10, 12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * WARP0      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5650[] = {
	{ -20, 0 },
	{ 0x00AF, 1 },
	{ 0, 3 },
	{ 0x00B2, 10 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0xFF4E, 9 },
	{ 30, 4 },
	{ 10, 12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * WARP0      GORONDASH    KEEP4
 */
CameraModeValue D_801B5674[] = {

	{ -50, 0 },
	{ 220, 1 },
	{ 0, 3 },
	{ 0x00B2, 10 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0xFF4E, 9 },
	{ 30, 4 },
	{ 10, 12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * WARP0      NUTSFLY    KEEP4
 */
CameraModeValue D_801B5698[] = {
	{ 0xFFC4, 0 },
	{ 200, 1 },
	{ 0, 3 },
	{ 0x00B2, 10 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0xFF4E, 9 },
	{ 30, 4 },
	{ 10, 12 },
};

/*=====================================================================
 *                   Custom Data: DEATH Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * DEATH      NORMAL    KEEP4
 */
CameraModeValue D_801B56BC[] = {
	{ 0xFFBA, 0 },
	{ 0x00A0, 1 },
	{ 0, 3 },
	{ 0, 10 },
	{ 10, 18 },
	{ 60, 7 },
	{ 0xFF00, 9 },
	{ 0x0005, 4 },
	{ 100, 12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * DEATH      JUMP         KEEP4
 * DEATH      GORONDASH    KEEP4
 * DEATH      NUTSFLY      KEEP4
 */
CameraModeValue D_801B56E0[] = {
	{ 0xFFBA, 0 },
	{ 0x00A0, 1 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 18 },
	{ 60, 7 },
	{ 0xFF00, 9 },
	{ 0x0005, 4 },
	{ 100, 12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * DEATH      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5704[] = {
	{ 0xFFBA, 0 },
	{ 0x0096, 1 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 18 },
	{ 60, 7 },
	{ 0xFF00, 9 },
	{ 0x0005, 4 },
	{ 100, 12 },
};

/*=====================================================================
 *                   Custom Data: REBIRTH Setting
 *=====================================================================
 */

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * REBIRTH    NORMAL       KEEP4
 * REBIRTH    JUMP         KEEP4
 * REBIRTH    GORONDASH    KEEP4
 * REBIRTH    NUTSFLY      KEEP4
 */
CameraModeValue D_801B5728[] = {
	{ 0xFFC4, 0 },
	{ 0x00A0, 1 },
	{ 30, 3 },
	{ 0x00A0, 10 },
	{ 10, 18 },
	{ 60, 7 },
	{ 0xFF06, 9 },
	{ 0x0005, 4 },
	{ 100, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * REBIRTH    NUTSSHOT    KEEP4
 */
CameraModeValue D_801B574C[] = {
	{ -20, 0 },
	{ 0x008C, 1 },
	{ 30, 3 },
	{ 0x00A0, 10 },
	{ 10, 18 },
	{ 60, 7 },
	{ 0xFF06, 9 },
	{ 0x0005, 4 },
	{ 100, 12 },
};

/*=====================================================================
 *                   Custom Data: TREASURE Setting
 *=====================================================================
 */

/**
 * Setting     Mode      Function
 * --------    ------    --------
 * TREASURE    NORMAL    DEMO2
 */
CameraModeValue D_801B5770[] = {
    { 60, 7 },     // fov
    { 30, 8 },     // unk_04
    { 0xFF00, 9 }, // flags
};

/*=====================================================================
 *                   Custom Data: DUNGEON1 Setting
 *=====================================================================
 */

/**
 * Setting     Mode      Function
 * --------    ------    --------
 * DUNGEON1    NORMAL    NORM1
 */
CameraModeValue D_801B577C[] = {
	{ -20, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 0x002D, 3 },
	{ 50, 4 },
	{ 20, 5 },
	{ 0x0046, 6 },
	{ 50, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting     Mode    Function
 * --------    ----    --------
 * DUNGEON1    JUMP    NORM1
 */
CameraModeValue D_801B57A4[] = {
	{ -20, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 0x0028, 3 },
	{ 50, 4 },
	{ 20, 5 },
	{ 50, 6 },
	{ 50, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting     Mode     Function
 * --------    -----    --------
 * DUNGEON1    STILL    NORM1
 */
CameraModeValue D_801B57CC[] = {
	{ -20, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 0x002D, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 50, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting      Mode        Function
 * ---------    --------    --------
 * DUNGEON1     PUSHPULL    PARA1
 * ONTHEPOLL    PUSHPULL    PARA1
 */
CameraModeValue D_801B57F4[] = {
	{ 0, 0 },
	{ 250, 1 },
	{ 0x0005, 2 },
	{ 30, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2022, 9 },
	{ 30, 11 },
	{ 0, 12 },
};

/*=====================================================================
 *                   Custom Data: FIXED1 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * FIXED1     NORMAL    FIXD1
 */
CameraModeValue D_801B5824[] = {
	{ -40, 0 },
	{ 100, 4 },
	{ 60, 7 },
	{ 0xFF00, 9 },
};

/*=====================================================================
 *                   Custom Data: FIXED2 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * FIXED2     NORMAL    FIXD1
 */
CameraModeValue D_801B5834[] = {
	{ -40, 0 },
	{ 10, 4 },
	{ 60, 7 },
	{ 0xFF00, 9 },
};

/*=====================================================================
 *                   Custom Data: MAZE Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * MAZE       NORMAL    PARA2
 */
CameraModeValue D_801B5844[] = {
	{ 0xFFDD, 0 },
	{ 0x00A0, 2 },
	{ 0x0041, 1 },
	{ -5, 3 },
	{ 0x0002, 4 },
	{ 0x0046, 7 },
	{ 0x0063, 8 },
	{ 0x0002, 9 },
};

/*=====================================================================
 *                   Custom Data: REMOTEBOMB Setting
 *=====================================================================
 */

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * REMOTEBOMB    NORMAL    NORM2
 */
CameraModeValue D_801B5864[] = {
	{ 20, 0 },
	{ 200, 1 },
	{ 0x0320, 2 },
	{ 0x000F, 3 },
	{ 0x0006, 4 },
	{ 0x0046, 7 },
	{ 0x0028, 8 },
	{ 0x0002, 9 },
};

/*=====================================================================
 *                   Custom Data: CIRCLE1 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE1    NORMAL    FIXD2
 */
CameraModeValue D_801B5884[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 10, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0xFF01, 9 },
};

/*=====================================================================
 *                   Custom Data: CIRCLE2 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE2    NORMAL    FIXD2
 */
CameraModeValue D_801B58A0[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 80, 5 },
	{ 60, 7 },
	{ 0xFF00, 9 },
};

/*=====================================================================
 *                   Custom Data: CIRCLE3 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE3    NORMAL    FIXD2
 */
CameraModeValue D_801B58BC[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 80, 5 },
	{ 60, 7 },
	{ 0, 9 },
};

/*=====================================================================
 *                   Custom Data: CIRCLE4 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE4    NORMAL    FIXD2
 */
CameraModeValue D_801B58D8[] = {
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 10, 5 },
	{ 60, 7 },
	{ 0xFF09, 9 },
};

/*=====================================================================
 *                   Custom Data: FIXED3 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * FIXED3     NORMAL    FIXD1
 */
CameraModeValue D_801B58F4[] = {
	{ -40, 0 },
	{ 100, 4 },
	{ 60, 7 },
	{ 0, 9 },
};

/*=====================================================================
 *                   Custom Data: TOWER0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * TOWER0    NORMAL    NORM0
 */
CameraModeValue D_801B5904[] = {
	{ 0, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 20, 21 },
	{ 20, 4 },
	{ 50, 6 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x0001, 9 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * TOWER0    JUMP    NORM1
 */
CameraModeValue D_801B5928[] = {
	{ -20, 0 },
	{ 0x0154, 1 },
	{ 0x0190, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * TOWER0     STILL    NORM1
 */
CameraModeValue D_801B5950[] = {
	{ 0, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0041, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/*=====================================================================
 *                   Custom Data: PARALLEL0 Setting
 *=====================================================================
 */

/**
 * Setting      Mode      Function
 * ---------    ------    --------
 * PARALLEL0    NORMAL    PARA1
 */
CameraModeValue D_801B5978[] = {
	{ 0, 0 },
	{ 0x0190, 1 },
	{ 20, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 20, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 50, 8 },
	{ 0x200A, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/*=====================================================================
 *                   Custom Data: NORMALD Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMALD    NORMAL    NORM1
 */
CameraModeValue D_801B59A8[] = {
	{ 0, 0 },
	{ 0x0190, 1 },
	{ 0x01F4, 2 },
	{ 0x000F, 3 },
	{ 0x0012, 4 },
	{ 0x000C, 5 },
	{ 0x0023, 6 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0xFF03, 9 },
};

/*=====================================================================
 *                   Custom Data: SUBJECTD Setting
 *=====================================================================
 */

/**
 * Setting     Mode      Function
 * --------    ------    --------
 * SUBJECTD    NORMAL    SUBJ1
 */
CameraModeValue D_801B59D0[] = {
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 10, 18 },
	{ 0x002D, 7 },
	{ 0xFF00, 9 },
};

/*=====================================================================
 *                   Custom Data: START0 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * START0     NORMAL    UNIQ0
 */
CameraModeValue D_801B59F4[] = {
	{ 0, 0 },
	{ 100, 4 },
	{ 0x0001, 9 },
};

/*=====================================================================
 *                   Custom Data: START2 Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * START2     NORMAL    UNIQ0
 */
CameraModeValue D_801B5A00[] = {
	{ 0, 0 },
	{ 30, 4 },
	{ 0x0011, 9 },
};

/*=====================================================================
 *                   Custom Data: JCRUISING Setting
 *=====================================================================
 */

/**
 * Setting      Mode      Function
 * ---------    ------    --------
 * JCRUISING    NORMAL    SUBJ1
 */
CameraModeValue D_801B5A0C[] = {
	{ 20, 0 },
	{ 90, 1 },
	{ 80, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 50, 17 },
	{ 0xFF38, 18 },
	{ 0x002D, 7 },
	{ 0, 9 },
};

/*=====================================================================
 *                   Custom Data: CLIMEMAZE Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5A30[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 0x0190, 1 },
	{ 50, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 0x0046, 11 },
	{ 0, 12 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5A64[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 0x0190, 1 },
	{ 10, 2 },
	{ 0, 3 },
	{ 0xFFA6, 10 },
	{ 20, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 50, 8 },
	{ 0x202E, 9 },
	{ 0x0046, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5A94[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 270, 1 },
	{ 300, 2 },
	{ 20, 3 },
	{ 0x001C, 4 },
	{ 20, 5 },
	{ 0x0041, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5ABC[] = {
    /* CAM_FUNC_BATT1 */
	{ -40, 0 },
	{ 200, 1 },
	{ 0x00F0, 2 },
	{ 50, 13 },
	{ 20, 14 },
	{ 0x0005, 15 },
	{ 10, 16 },
	{ 20, 17 },
	{ 50, 7 },
	{ 60, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5AF0[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 270, 1 },
	{ 300, 2 },
	{ 0x0028, 3 },
	{ 50, 4 },
	{ 20, 5 },
	{ 50, 6 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5B18[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 270, 1 },
	{ 300, 2 },
	{ 20, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5B40[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 200, 1 },
	{ 0x0005, 2 },
	{ 0x000F, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2022, 9 },
	{ 30, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5B70[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 250, 1 },
	{ 350, 2 },
	{ 10, 3 },
	{ 0x0018, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 0x0041, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5B98[] = {
    /* CAM_FUNC_KEEP1 */
	{ -50, 0 },
	{ 300, 1 },
	{ 350, 2 },
	{ 10, 13 },
	{ 20, 14 },
	{ 0x0005, 15 },
	{ 0x000C, 16 },
	{ 0x0046, 17 },
	{ 60, 7 },
	{ 30, 8 },
	{ 0x2000, 9 },
	{ 20, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5BC8[] = {
    /* CAM_FUNC_KEEP3 */
	{ -20, 0 },
	{ 230, 1 },
	{ 260, 2 },
	{ 20, 13 },
	{ 10, 14 },
	{ 20, 15 },
	{ 0x000F, 16 },
	{ 0x0028, 17 },
	{ 0x0037, 7 },
	{ 20, 8 },
	{ 20, 4 },
	{ 0x3520, 9 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5BFC[] = {
    /* CAM_FUNC_BATT1 */
	{ 0xFFC4, 0 },
	{ 200, 1 },
	{ 220, 2 },
	{ 20, 13 },
	{ 10, 14 },
	{ 0, 15 },
	{ 10, 16 },
	{ 60, 17 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0x2002, 9 },
	{ 10, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5C30[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 250, 1 },
	{ 350, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5C58[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 250, 1 },
	{ 350, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0041, 7 },
	{ 0x000F, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5C80[] = {
    /* CAM_FUNC_PARA1 */
	{ 100, 0 },
	{ 300, 1 },
	{ -20, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0004, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 60, 8 },
	{ 0x0022, 9 },
	{ 60, 11 },
	{ 20, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5CB0[] = {
    /* CAM_FUNC_FIXD2 */
	{ -40, 0 },
	{ 60, 1 },
	{ 0x3200, 2 },
	{ 10, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0xFF03, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5CCC[] = {
    /* CAM_FUNC_FIXD2 */
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 200, 2 },
	{ 10, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0xFF20, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5CE8[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 220, 1 },
	{ 0x0118, 2 },
	{ 0x0011, 3 },
	{ 0x000E, 4 },
	{ 0x0005, 5 },
	{ 0x0041, 6 },
	{ 0x0046, 7 },
	{ 0x004B, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D10[] = {
    /* CAM_FUNC_KEEP1 */
	{ 0, 0 },
	{ 200, 1 },
	{ 250, 2 },
	{ 0x0019, 13 },
	{ 0x002D, 14 },
	{ 0x0028, 15 },
	{ 0x000F, 16 },
	{ 0x0028, 17 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 20, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D40[] = {
    /* CAM_FUNC_BATT1 */
	{ -25, 0 },
	{ 180, 1 },
	{ 220, 2 },
	{ 10, 13 },
	{ 0x0028, 14 },
	{ 10, 15 },
	{ 0, 16 },
	{ 0x0028, 17 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 20, 11 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D74[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 220, 1 },
	{ 0x0118, 2 },
	{ 0x0010, 3 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 0x0046, 7 },
	{ 0x0028, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D9C[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 220, 1 },
	{ 0x0118, 2 },
	{ 0x0010, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0046, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5DC4[] = {
	/* CAM_FUNC_FIXD1 */
	{ -40, 0 },
	{ 10, 4 },
	{ 60, 7 },
	{ 0xFF10, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5DD4[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 80, 1 },
	{ 0x0078, 2 },
	{ -10, 3 },
	{ 0x000F, 4 },
	{ 20, 5 },
	{ 0x0028, 6 },
	{ 0x0046, 7 },
	{ 0x0046, 8 },
	{ 0x0082, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5DFC[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFC4, 0 },
	{ 0x0226, 1 },
	{ 0, 2 },
	{ 0x0041, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x004B, 7 },
	{ 50, 8 },
	{ 0x2042, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E2C[] = {
    /* CAM_FUNC_FIXD2 */
	{ 0x0046, 0 },
	{ 50, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 30, 5 },
	{ 0x0046, 7 },
	{ 0x0001, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E48[] = {
    /* CAM_FUNC_FIXD2 */
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0xFF08, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E64[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0320, 1 },
	{ 0x0320, 2 },
	{ 60, 3 },
	{ 50, 4 },
	{ 10, 5 },
	{ 50, 6 },
	{ 0x002D, 7 },
	{ 90, 8 },
	{ 0x0042, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E8C[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0320, 1 },
	{ 0x0320, 2 },
	{ 60, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x002D, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5EB4[] = {
    /* CAM_FUNC_NORM1 */
	{ -30, 0 },
	{ 180, 1 },
	{ 250, 2 },
	{ -5, 3 },
	{ 0x0012, 4 },
	{ 20, 5 },
	{ 60, 6 },
	{ 0x0037, 7 },
	{ 50, 8 },
	{ 0x0082, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5EDC[] = {
    /* CAM_FUNC_PARA1 */
	{ -30, 0 },
	{ 180, 1 },
	{ 20, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2042, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5F0C[] = {
    /* CAM_FUNC_NORM1 */
	{ -30, 0 },
	{ 0x00A0, 1 },
	{ 0x00BE, 2 },
	{ 0, 3 },
	{ 30, 4 },
	{ 20, 5 },
	{ 60, 6 },
	{ 0x0037, 7 },
	{ 30, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5F34[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 0x00AA, 1 },
	{ 200, 2 },
	{ 0, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0037, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5F5C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 180, 1 },
	{ 0x0005, 2 },
	{ 0x0005, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2022, 9 },
	{ 30, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5F8C[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 30, 7 },
	{ 0x0200, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5FB0[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 0x000F, 7 },
	{ 0x0200, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5FD4[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 30, 7 },
	{ 0x0210, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5FF8[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0, 0 },
	{ 0x0005, 1 },
	{ 50, 2 },
	{ 0x0001, 4 },
	{ 0, 19 },
	{ 0, 17 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0x0210, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B601C[] = {
    /* CAM_FUNC_NORM1 */
	{ 0xFFDD, 0 },
	{ 100, 1 },
	{ 220, 2 },
	{ 0x000F, 3 },
	{ 0x0011, 4 },
	{ 0x000C, 5 },
	{ 0x0023, 6 },
	{ 0x0041, 7 },
	{ 0x0046, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6044[] = {
    /* CAM_FUNC_PARA1 */
	{ -10, 0 },
	{ 200, 1 },
	{ 50, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x2052, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6074[] = {
    /* CAM_FUNC_KEEP1 */
	{ -30, 0 },
	{ 60, 1 },
	{ 200, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ -5, 15 },
	{ 10, 16 },
	{ 30, 17 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B60A4[] = {
    /* CAM_FUNC_KEEP3 */
	{ -20, 0 },
	{ 50, 1 },
	{ 100, 2 },
	{ 50, 13 },
	{ 0x0005, 14 },
	{ 20, 15 },
	{ 0x0005, 16 },
	{ 0x0028, 17 },
	{ 0x0023, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3520, 9 },
	{ 60, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B60D8[] = {
    /* CAM_FUNC_BATT1 */
	{ -25, 0 },
	{ 100, 1 },
	{ 0x008C, 2 },
	{ 10, 13 },
	{ 0x0028, 14 },
	{ 0xFFFE, 15 },
	{ 10, 16 },
	{ 0x0019, 17 },
	{ 50, 7 },
	{ 80, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B610C[] = {
    /* CAM_FUNC_JUMP2 */
	{ -20, 0 },
	{ 100, 1 },
	{ 220, 2 },
	{ 20, 20 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0041, 7 },
	{ 0x0028, 8 },
	{ 0, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6130[] = {
    /* CAM_FUNC_JUMP2 */
	{ -20, 0 },
	{ 0x0078, 1 },
	{ 0x00F0, 2 },
	{ 20, 20 },
	{ 0x03E7, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x2006, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6154[] = {
    /* CAM_FUNC_NORM1 */
	{ -30, 0 },
	{ 100, 1 },
	{ 220, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 80, 6 },
	{ 0x0041, 7 },
	{ 30, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B617C[] = {
    /* CAM_FUNC_PARA1 */
	{ -40, 0 },
	{ 200, 1 },
	{ 50, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0008, 4 },
	{ 0x0005, 5 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x0086, 9 },
	{ 60, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B61AC[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 0x00F0, 1 },
	{ 50, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2086, 9 },
	{ 60, 11 },
	{ 0x0002, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B61DC[] = {
    /* CAM_FUNC_PARA1 */
	{ -10, 0 },
	{ 200, 1 },
	{ 100, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 0x0004, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 20, 8 },
	{ 0x0088, 9 },
	{ 0x0041, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B620C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 0x00F0, 1 },
	{ -20, 2 },
	{ 50, 3 },
	{ 0, 10 },
	{ 50, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 20, 8 },
	{ 0, 9 },
	{ 0x0041, 11 },
	{ 10, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B623C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 0x00F0, 1 },
	{ -20, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 50, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 20, 8 },
	{ 0x0002, 9 },
	{ 0x0041, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B626C[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 100, 1 },
	{ 220, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0041, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6294[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 200, 1 },
	{ 0x0005, 2 },
	{ 0x002D, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2032, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B62C4[] = {
    /* CAM_FUNC_KEEP1 */
	{ -5, 0 },
	{ 0x0078, 1 },
	{ 0x008C, 2 },
	{ 0x0005, 13 },
	{ 0x0055, 14 },
	{ 10, 15 },
	{ 0x0005, 16 },
	{ 0x0019, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B62F4[] = {
    /* CAM_FUNC_NORM1 */
	{ 50, 0 },
	{ 0x008C, 1 },
	{ 220, 2 },
	{ 0, 3 },
	{ 0x000C, 4 },
	{ 10, 5 },
	{ 0x0028, 6 },
	{ 90, 7 },
	{ 90, 8 },
	{ 0x0087, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B631C[] = {
    /* CAM_FUNC_PARA1 */
	{ 100, 0 },
	{ 220, 1 },
	{ -20, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0004, 4 },
	{ 0x0005, 5 },
	{ 80, 7 },
	{ 60, 8 },
	{ 0xFF22, 9 },
	{ 80, 11 },
	{ 20, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B634C[] = {
    /* CAM_FUNC_NORM1 */
	{ 0xFFC4, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 0x0028, 3 },
	{ 20, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 80, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6374[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFC4, 0 },
	{ 220, 1 },
	{ 20, 2 },
	{ 10, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 90, 8 },
	{ 0x200E, 9 },
	{ 90, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B63A4[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 0x0078, 1 },
	{ 0x00F0, 2 },
	{ 0, 3 },
	{ 0x0012, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 80, 7 },
	{ 60, 8 },
	{ 0x008F, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B63CC[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 220, 1 },
	{ 50, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B63FC[] = {
    /* CAM_FUNC_FIXD2 */
	{ -10, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0xFF18, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6418[] = {
    /* CAM_FUNC_FIXD2 */
	{ -40, 0 },
	{ 0x0028, 1 },
	{ 0x3200, 2 },
	{ 0x0005, 4 },
	{ 0x0019, 5 },
	{ 60, 7 },
	{ 0x0005, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6434[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 60, 1 },
	{ 0x0258, 2 },
	{ 0x0023, 3 },
	{ 0x0028, 4 },
	{ 20, 5 },
	{ 60, 6 },
	{ 0x002D, 7 },
	{ 80, 8 },
	{ 0x0002, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B645C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 300, 1 },
	{ 0x0005, 2 },
	{ 0x0023, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 0x0046, 8 },
	{ 0x2042, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B648C[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 0x0140, 1 },
	{ 0x017C, 2 },
	{ 30, 3 },
	{ 0x0016, 4 },
	{ 10, 5 },
	{ 0x0020, 6 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B64B4[] = {
    /* CAM_FUNC_JUMP2 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 20, 20 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B64D8[] = {
    /* CAM_FUNC_JUMP2 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 20, 20 },
	{ 0x03E7, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x2006, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B64FC[] = {
    /* CAM_FUNC_PARA1 */
	{ -40, 0 },
	{ 0x0140, 1 },
	{ 50, 2 },
	{ 0x0028, 3 },
	{ 0, 10 },
	{ 0x0008, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x0086, 9 },
	{ 50, 11 },
	{ 0x000C, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B652C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0xFFB0, 0 },
	{ 300, 1 },
	{ 50, 2 },
	{ 0x0046, 3 },
	{ 0, 10 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2086, 9 },
	{ 50, 11 },
	{ 0x0002, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B655C[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 0x0154, 1 },
	{ 350, 2 },
	{ 30, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6584[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 260, 1 },
	{ 0x0118, 2 },
	{ 20, 3 },
	{ 20, 4 },
	{ 0x000C, 5 },
	{ 50, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0082, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B65AC[] = {
    /* CAM_FUNC_PARA1 */
	{ 10, 0 },
	{ 260, 1 },
	{ 50, 2 },
	{ 0x000F, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B65DC[] = {
    /* CAM_FUNC_KEEP1 */
	{ 10, 0 },
	{ 200, 1 },
	{ 220, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ 20, 15 },
	{ 30, 16 },
	{ 0x000F, 17 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B660C[] = {
    /* CAM_FUNC_KEEP3 */
	{ 10, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 30, 13 },
	{ 10, 14 },
	{ 30, 15 },
	{ 30, 16 },
	{ 0x0046, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3540, 9 },
	{ 60, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6640[] = {
    /* CAM_FUNC_BATT1 */
	{ 10, 0 },
	{ 220, 1 },
	{ 220, 2 },
	{ 10, 13 },
	{ 80, 14 },
	{ 20, 15 },
	{ 30, 16 },
	{ 0x0019, 17 },
	{ 50, 7 },
	{ 80, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 60, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6674[] = {
    /* CAM_FUNC_SUBJ1 */
	{ 0, 0 },
	{ 10, 1 },
	{ 60, 2 },
	{ 10, 4 },
	{ 0, 19 },
	{ 50, 17 },
	{ 0, 18 },
	{ 0x002D, 7 },
	{ 0, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6698[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 260, 1 },
	{ 0x0118, 2 },
	{ 0x0028, 3 },
	{ 20, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x008A, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B66C0[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 260, 1 },
	{ 0x0118, 2 },
	{ 20, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B66E8[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ -5, 3 },
	{ 0x0018, 4 },
	{ 0x000C, 5 },
	{ 0x0020, 6 },
	{ 0x0041, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6710[] = {
    /* CAM_FUNC_KEEP1 */
	{ -30, 0 },
	{ 0x00F0, 1 },
	{ 260, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ 10, 15 },
	{ 0x0005, 16 },
	{ 60, 17 },
	{ 50, 7 },
	{ 0x0028, 8 },
	{ 0x2000, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6740[] = {
    /* CAM_FUNC_BATT1 */
	{ 0xFFC4, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 10, 13 },
	{ 20, 14 },
	{ 20, 15 },
	{ 10, 16 },
	{ 20, 17 },
	{ 0x0046, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 10, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6774[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B679C[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 0, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0041, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B67C4[] = {
    /* CAM_FUNC_NORM1 */
	{ 20, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 0, 3 },
	{ 0x001A, 4 },
	{ 0x000C, 5 },
	{ 0x0020, 6 },
	{ 0x004B, 7 },
	{ 0x0046, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B67EC[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 0x0190, 1 },
	{ 50, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0037, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B681C[] = {
    /* CAM_FUNC_KEEP1 */
	{ -30, 0 },
	{ 250, 1 },
	{ 300, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ 10, 15 },
	{ 0x0005, 16 },
	{ 60, 17 },
	{ 50, 7 },
	{ 0x0028, 8 },
	{ 0x2000, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B684C[] = {
    /* CAM_FUNC_BATT1 */
	{ 0, 0 },
	{ 0x0096, 1 },
	{ 200, 2 },
	{ 10, 13 },
	{ 30, 14 },
	{ 10, 15 },
	{ 0, 16 },
	{ 20, 17 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2002, 9 },
	{ 10, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6880[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 0x004B, 7 },
	{ 0x0028, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B68A8[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF033, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B68D0[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 20, 4 },
	{ 0x000C, 5 },
	{ 50, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B68F8[] = {
    /* CAM_FUNC_BATT1 */
	{ -25, 0 },
	{ 220, 1 },
	{ 220, 2 },
	{ 10, 13 },
	{ 80, 14 },
	{ 0xFFFE, 15 },
	{ 10, 16 },
	{ 0x0019, 17 },
	{ 50, 7 },
	{ 80, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B692C[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6954[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 0x000F, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B697C[] = {
    /* CAM_FUNC_NORM1 */
	{ 60, 0 },
	{ 200, 1 },
	{ 0x0154, 2 },
	{ 10, 3 },
	{ 0x000F, 4 },
	{ 10, 5 },
	{ 50, 6 },
	{ 0x0055, 7 },
	{ 90, 8 },
	{ 0x0087, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B69A4[] = {
    /* CAM_FUNC_JUMP3 */
	{ -20, 0 },
	{ 0x0118, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 20, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0084, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B69CC[] = {
    /* CAM_FUNC_KEEP1 */
	{ -30, 0 },
	{ 200, 1 },
	{ 0x00F0, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ -5, 15 },
	{ 10, 16 },
	{ 0x000F, 17 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B69FC[] = {
    /* CAM_FUNC_BATT1 */
	{ -30, 0 },
	{ 0x00BE, 1 },
	{ 250, 2 },
	{ 10, 13 },
	{ 50, 14 },
	{ 0, 15 },
	{ 10, 16 },
	{ 20, 17 },
	{ 50, 7 },
	{ 80, 8 },
	{ 0x2002, 9 },
	{ 0x0019, 11 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6A30[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 0x00A0, 1 },
	{ 260, 2 },
	{ -5, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 0x0046, 7 },
	{ 0x0028, 8 },
	{ 0x000C, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6A58[] = {
    /* CAM_FUNC_JUMP3 */
	{ -30, 0 },
	{ 220, 1 },
	{ 0x0118, 2 },
	{ 0, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x0005, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6A80[] = {
    /* CAM_FUNC_JUMP3 */
	{ 0xFFC4, 0 },
	{ 0x00A0, 1 },
	{ 0x0118, 2 },
	{ -15, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x0085, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6AA8[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 100, 1 },
	{ 0x0140, 2 },
	{ 20, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6AD0[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 250, 1 },
	{ 350, 2 },
	{ 30, 3 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 100, 8 },
	{ 0x0084, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6AF8[] = {
    /* CAM_FUNC_PARA1 */
	{ -50, 0 },
	{ 350, 1 },
	{ 0x0028, 2 },
	{ 10, 3 },
	{ 0, 10 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 100, 8 },
	{ 0x2003, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6B28[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 0x0140, 1 },
	{ 0x0190, 2 },
	{ -5, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x000C, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6B50[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 300, 1 },
	{ 350, 2 },
	{ 10, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x0005, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6B78[] = {
    /* CAM_FUNC_JUMP3 */
	{ 0xFFC4, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ -18, 3 },
	{ 0x0012, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x0085, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6BA0[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 250, 1 },
	{ 350, 2 },
	{ 30, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 60, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6BC8[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 250, 1 },
	{ 0x0118, 2 },
	{ 0x0005, 3 },
	{ 0x0011, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 0x004B, 7 },
	{ 0x0023, 8 },
	{ 0x000C, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6BF0[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 0x000E, 3 },
	{ 0x0019, 4 },
	{ 0x000E, 5 },
	{ 60, 6 },
	{ 0x0041, 7 },
	{ 0x0046, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6C18[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 350, 1 },
	{ 80, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 50, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6C48[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 350, 1 },
	{ 0x01A4, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 10, 5 },
	{ 0x0028, 6 },
	{ 0x0041, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6C70[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 350, 1 },
	{ 0x0190, 2 },
	{ 0x000E, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0041, 7 },
	{ 0x0010, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6C98[] = {
    /* CAM_FUNC_NORM1 */
	{ -30, 0 },
	{ 300, 1 },
	{ 0x0140, 2 },
	{ 0x000F, 3 },
	{ 0x0016, 4 },
	{ 0x000C, 5 },
	{ 30, 6 },
	{ 0x0037, 7 },
	{ 60, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6CC0[] = {
    /* CAM_FUNC_KEEP1 */
	{ -30, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 20, 13 },
	{ 30, 14 },
	{ -5, 15 },
	{ 10, 16 },
	{ 0x0028, 17 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6CF0[] = {
    /* CAM_FUNC_KEEP3 */
	{ -30, 0 },
	{ 0x0041, 1 },
	{ 0x0046, 2 },
	{ 10, 13 },
	{ 10, 14 },
	{ 0x0005, 15 },
	{ 0x0005, 16 },
	{ 20, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3520, 9 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D24[] = {
    /* CAM_FUNC_NORM1 */
	{ -20, 0 },
	{ 300, 1 },
	{ 0x0140, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 0x0037, 7 },
	{ 30, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D4C[] = {
    /* CAM_FUNC_NORM1 */
	{ -30, 0 },
	{ 300, 1 },
	{ 0x0140, 2 },
	{ 0x000F, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0037, 7 },
	{ 0x0019, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D74[] = {
    /* CAM_FUNC_FIXD2 */
	{ -40, 0 },
	{ 60, 1 },
	{ 0x3200, 2 },
	{ 100, 4 },
	{ 20, 5 },
	{ 60, 7 },
	{ 0xFF0B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D90[] = {
    /* CAM_FUNC_JUMP3 */
	{ -10, 0 },
	{ 0x0118, 1 },
	{ 350, 2 },
	{ 50, 3 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 30, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x00A4, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6DB8[] = {
    /* CAM_FUNC_JUMP3 */
	{ 0, 0 },
	{ 180, 1 },
	{ 300, 2 },
	{ 30, 3 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 0x0019, 6 },
	{ 0x004B, 7 },
	{ 20, 8 },
	{ 20, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6DE0[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 0x0140, 1 },
	{ 350, 2 },
	{ -5, 3 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 0x0019, 6 },
	{ 0x0041, 7 },
	{ 0x0028, 8 },
	{ 0x001C, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6E08[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 300, 1 },
	{ 350, 2 },
	{ 10, 3 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 30, 6 },
	{ 0x0041, 7 },
	{ 60, 8 },
	{ 0x0025, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6E30[] = {
    /* CAM_FUNC_JUMP3 */
	{ 0xFFC4, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ -18, 3 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 30, 6 },
	{ 60, 7 },
	{ 0x0028, 8 },
	{ 0x0094, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6E58[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 220, 1 },
	{ 260, 2 },
	{ 0x0005, 3 },
	{ 0x0008, 4 },
	{ 0x0005, 5 },
	{ 20, 6 },
	{ 0x004B, 7 },
	{ 0x0023, 8 },
	{ 0x001C, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6E80[] = {
    /* CAM_FUNC_NORM1 */
	{ 0xFFBA, 0 },
	{ 250, 1 },
	{ 0x01F4, 2 },
	{ 0x0005, 3 },
	{ 30, 4 },
	{ 0x000C, 5 },
	{ 0x002D, 6 },
	{ 50, 7 },
	{ 0x0046, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6EA8[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 250, 1 },
	{ 0x01F4, 2 },
	{ 0x0005, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 50, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6ED0[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 250, 1 },
	{ 0x01F4, 2 },
	{ 0x0005, 3 },
	{ 0x0019, 4 },
	{ 0x000C, 5 },
	{ 0x0028, 6 },
	{ 50, 7 },
	{ 0x0028, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6EF8[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 0x0096, 1 },
	{ 0x00A0, 2 },
	{ -15, 3 },
	{ 0x0019, 4 },
	{ 0x000E, 5 },
	{ 50, 6 },
	{ 50, 7 },
	{ 0x0046, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6F20[] = {
    /* CAM_FUNC_PARA1 */
	{ -40, 0 },
	{ 180, 1 },
	{ 80, 2 },
	{ 0, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 50, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6F50[] = {
    /* CAM_FUNC_NORM1 */
	{ -10, 0 },
	{ 100, 1 },
	{ 0x0096, 2 },
	{ 10, 3 },
	{ 30, 4 },
	{ 10, 5 },
	{ 0x0028, 6 },
	{ 0x0046, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6F78[] = {
    /* CAM_FUNC_NORM1 */
	{ -40, 0 },
	{ 0x0096, 1 },
	{ 0x00A0, 2 },
	{ 0xFFF4, 3 },
	{ 0x0019, 4 },
	{ 0x000E, 5 },
	{ 50, 6 },
	{ 50, 7 },
	{ 50, 8 },
	{ 0x0023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6FA0[] = {
    /* CAM_FUNC_UNIQ2 */
	{ -40, 0 },
	{ 20, 1 },
	{ 60, 7 },
	{ 50, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6FB0[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 0x0078, 1 },
	{ 250, 2 },
	{ 0x0010, 3 },
	{ 0x0010, 4 },
	{ 0x0005, 5 },
	{ 0x0041, 6 },
	{ 60, 7 },
	{ 0x004B, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6FD8[] = {
    /* CAM_FUNC_KEEP1 */
	{ -20, 0 },
	{ 100, 1 },
	{ 0x0096, 2 },
	{ 0, 13 },
	{ 0x0004, 14 },
	{ 20, 15 },
	{ 10, 16 },
	{ 0x0028, 17 },
	{ 60, 7 },
	{ 60, 8 },
	{ 0x2001, 9 },
	{ 20, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7008[] = {
    /* CAM_FUNC_BATT1 */
	{ -25, 0 },
	{ 100, 1 },
	{ 180, 2 },
	{ 10, 13 },
	{ 0x0028, 14 },
	{ 10, 15 },
	{ 0, 16 },
	{ 0x0028, 17 },
	{ 60, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 20, 11 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B703C[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 0x0078, 1 },
	{ 250, 2 },
	{ 0x0010, 3 },
	{ 0x000C, 4 },
	{ 0x0005, 5 },
	{ 60, 6 },
	{ 0x0046, 7 },
	{ 0x0028, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7064[] = {
    /* CAM_FUNC_NORM1 */
	{ -15, 0 },
	{ 0x0078, 1 },
	{ 250, 2 },
	{ 0x0010, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0046, 7 },
	{ 20, 8 },
	{ 0xF023, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B708C[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 200, 1 },
	{ 0x0005, 2 },
	{ 30, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 30, 8 },
	{ 0x2022, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B70BC[] = {
    /* CAM_FUNC_JUMP3 */
	{ -10, 0 },
	{ 270, 1 },
	{ 300, 2 },
	{ 20, 3 },
	{ 30, 4 },
	{ 20, 5 },
	{ 0x0041, 6 },
	{ 60, 7 },
	{ 80, 8 },
	{ 0x0084, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B70E4[] = {
    /* CAM_FUNC_PARA1 */
	{ -30, 0 },
	{ 0x0118, 1 },
	{ 0x0028, 2 },
	{ 10, 3 },
	{ 0, 10 },
	{ 0x000F, 4 },
	{ 0x0005, 5 },
	{ 60, 7 },
	{ 100, 8 },
	{ 0x2003, 9 },
	{ 60, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7114[] = {
    /* CAM_FUNC_KEEP3 */
	{ -20, 0 },
	{ 50, 1 },
	{ 100, 2 },
	{ 50, 13 },
	{ 0x0005, 14 },
	{ 20, 15 },
	{ 10, 16 },
	{ 0x0028, 17 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3500, 9 },
	{ 60, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7148[] = {
    /* CAM_FUNC_JUMP3 */
	{ -40, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 0x0005, 3 },
	{ 20, 4 },
	{ 0x0005, 5 },
	{ 0x0028, 6 },
	{ 0x004B, 7 },
	{ 0x0023, 8 },
	{ 0x000C, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7170[] = {
    /* CAM_FUNC_KEEP1 */
	{ -30, 0 },
	{ 180, 1 },
	{ 200, 2 },
	{ 20, 13 },
	{ 0x0028, 14 },
	{ -5, 15 },
	{ 10, 16 },
	{ 0x000F, 17 },
	{ 0x002D, 7 },
	{ 60, 8 },
	{ 0x2011, 9 },
	{ 30, 11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B71A0[] = {
    /* CAM_FUNC_BATT1 */
	{ -30, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 10, 13 },
	{ 60, 14 },
	{ -5, 15 },
	{ 20, 16 },
	{ 0x0023, 17 },
	{ 0x0037, 7 },
	{ 0x0046, 8 },
	{ 0x2012, 9 },
	{ 0x0019, 11 },
	{ 0x0028, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B71D4[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 0x0190, 1 },
	{ 20, 2 },
	{ 20, 3 },
	{ 0, 10 },
	{ 20, 4 },
	{ 0x0005, 5 },
	{ 0x0046, 7 },
	{ 50, 8 },
	{ 10, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7204[] = {
    /* CAM_FUNC_UNIQ0 */
	{ 0, 0 },
	{ 100, 4 },
	{ 0x0002, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7210[] = {
    /* CAM_FUNC_KEEP3 */
	{ -10, 0 },
	{ 0x0078, 1 },
	{ 180, 2 },
	{ 50, 13 },
	{ 0x0005, 14 },
	{ 10, 15 },
	{ 0x0005, 16 },
	{ 0x0046, 17 },
	{ 0x0023, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3520, 9 },
	{ 60, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7244[] = {
    /* CAM_FUNC_KEEP3 */
	{ -20, 0 },
	{ 0x006E, 1 },
	{ 0x00A0, 2 },
	{ 80, 13 },
	{ 0x000F, 14 },
	{ 10, 15 },
	{ 0, 16 },
	{ 0x0046, 17 },
	{ 0x0028, 7 },
	{ 50, 8 },
	{ 20, 4 },
	{ 0x3520, 9 },
	{ 50, 18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7278[] = {
    /* CAM_FUNC_KEEP4 */
	{ -45, 0 },
	{ 0x0096, 1 },
	{ -10, 3 },
	{ 0x00A5, 10 },
	{ 0x0005, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 30, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B729C[] = {
    /* CAM_FUNC_KEEP4 */
	{ -40, 0 },
	{ 0x0096, 1 },
	{ 0x0012, 3 },
	{ 0x008C, 10 },
	{ 0x0005, 18 },
	{ 0x0046, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 30, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B72C0[] = {
    /* CAM_FUNC_KEEP4 */
	{ -20, 0 },
	{ 0x0096, 1 },
	{ 0xFFFE, 3 },
	{ 0x008C, 10 },
	{ 0x000F, 18 },
	{ 50, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 30, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B72E4[] = {
    /* CAM_FUNC_KEEP4 */
	{ -50, 0 },
	{ 0x0096, 1 },
	{ 0xFFF4, 3 },
	{ 0x00A0, 10 },
	{ 0x0006, 18 },
	{ 50, 7 },
	{ 0xFF02, 9 },
	{ 0x0019, 4 },
	{ 30, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7308[] = {
    /* CAM_FUNC_KEEP4 */
	{ 0xFFC4, 0 },
	{ 0x0096, 1 },
	{ 0xFFF4, 3 },
	{ 0xFF74, 10 },
	{ 30, 18 },
	{ 50, 7 },
	{ 0xFF0C, 9 },
	{ 0x0019, 4 },
	{ 30, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B732C[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ -5, 3 },
	{ 0x0010, 4 },
	{ 0x0005, 5 },
	{ 0x0034, 6 },
	{ 0x0037, 7 },
	{ 80, 8 },
	{ 0x0083, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7354[] = {
    /* CAM_FUNC_PARA1 */
	{ 0, 0 },
	{ 200, 1 },
	{ 0x0019, 2 },
	{ 0x0005, 3 },
	{ 0, 10 },
	{ 0x0005, 4 },
	{ 0x0005, 5 },
	{ 0x002D, 7 },
	{ 50, 8 },
	{ 0x2002, 9 },
	{ 80, 11 },
	{ 0, 12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7384[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 0x0096, 1 },
	{ 250, 2 },
	{ 0, 3 },
	{ 0x0018, 4 },
	{ 0x0005, 5 },
	{ 50, 6 },
	{ 0x0037, 7 },
	{ 50, 8 },
	{ 0x008B, 9 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B73AC[] = {
    /* CAM_FUNC_NORM1 */
	{ 0, 0 },
	{ 180, 1 },
	{ 220, 2 },
	{ 0x0005, 3 },
	{ 100, 4 },
	{ 100, 5 },
	{ 100, 6 },
	{ 0x0037, 7 },
	{ 10, 8 },
	{ 0xF003, 9 },
};

CameraMode sCamSetNorm0Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B4710 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_NORM1, 10, D_801B4B90 }, // CAM_MODE_GORONJUMP
    { CAM_FUNC_SUBJ1, 9, D_801B48B0 },  // CAM_MODE_BOOMERANG
    { CAM_FUNC_PARA1, 12, D_801B4A04 }, // CAM_MODE_CHARGEZ
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_ZORAFINZ
};

CameraMode sCamSetNorm3Modes[] = {
    { CAM_FUNC_JUMP3, 10, D_801B4BDC }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_JUMP3, 10, D_801B4CFC }, // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_JUMP3, 10, D_801B4C84 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4C04 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_JUMP3, 10, D_801B4CAC }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4CD4 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_JUMP3, 10, D_801B4C34 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_JUMP3, 10, D_801B4C5C }, // CAM_MODE_GORONJUMP
};

CameraMode sCamSetCirc5Modes[] = {
    { CAM_FUNC_UNIQ2, 4, D_801B4D24 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_NUTSFLY
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_ZORAFIN
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_UNIQ2, 4, D_801B4D34 }, // CAM_MODE_TARGET
};

CameraMode sCamSetHorse0Modes[] = {
    { CAM_FUNC_NORM3, 9, D_801B4D44 },  // CAM_MODE_NORMAL
    { CAM_FUNC_NORM3, 9, D_801B4D8C },  // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4E2C }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NORM3, 9, D_801B4D68 },  // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B4E5C }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B4DD4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4DB0 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4DF8 }, // CAM_MODE_BATTLE
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM3, 9, D_801B4E90 },  // CAM_MODE_STILL
};

CameraMode sCamSetZora0Modes[] = {
    { CAM_FUNC_NORM3, 9, D_801B4EB4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetPreRend0Modes[] = {
    { CAM_FUNC_FIXD3, 1, D_801B4ED8 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetPreRend1Modes[] = {
    { CAM_FUNC_UNIQ7, 2, D_801B4EDC }, // CAM_MODE_NORMAL
};

CameraMode sCamSetDoorCModes[] = {
    { CAM_FUNC_SPEC9, 3, D_801B4EE4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetDemo0Modes[] = {
    { CAM_FUNC_DEMO1, 1, D_801B4EF0 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetFree0Modes[] = {
    { CAM_FUNC_UNIQ6, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetFukan0Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B4EF8 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B4F50 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4F20 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4F78 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_NORM1, 10, D_801B4EF8 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetNorm1Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B4FA0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4FC8 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetNanameModes[] = {
    { CAM_FUNC_NORM4, 10, D_801B4FF0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetCirc0Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B5018 },  // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_FIXD2, 7, D_801B5034 },  // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TARGET
    { CAM_FUNC_FIXD2, 7, D_801B5050 },  // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
};

CameraMode sCamSetFixed0Modes[] = {
    { CAM_FUNC_FIXD1, 4, D_801B506C },  // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
};

CameraMode sCamSetSpiralModes[] = {
    { CAM_FUNC_SPEC8, 6, D_801B507C }, // CAM_MODE_NORMAL
};

CameraMode sCamSetDungeon0Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5094 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B5180 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B50EC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B511C }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B52E0 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5308 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_NORM1, 10, D_801B4B90 }, // CAM_MODE_GORONJUMP
    { CAM_FUNC_SUBJ1, 9, D_801B48B0 },  // CAM_MODE_BOOMERANG
    { CAM_FUNC_PARA1, 12, D_801B5250 }, // CAM_MODE_CHARGEZ
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_ZORAFINZ
};

CameraMode sCamSetItem0Modes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B5338 }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B535C }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B53A4 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B5380 }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B53C8 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetItem1Modes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B53EC }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B5410 }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B5458 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B5434 }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B547C }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetItem2Modes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B54A0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B54C4 }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B550C }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B54E8 }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B5530 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetItem3Modes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B5554 }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B5578 }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B55C0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B559C }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B55E4 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetNaviModes[] = {
    { CAM_FUNC_UNIQ6, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetWarp0Modes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B5608 }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B562C }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B5674 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B5650 }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B5698 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetDeathModes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B56BC }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B56E0 }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B56E0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B5704 }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B56E0 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetRebirthModes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B5728 }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B5728 }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B5728 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B574C }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B5728 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetTreasureModes[] = {
    { CAM_FUNC_DEMO2, 3, D_801B5770 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetTransformModes[] = {
    { CAM_FUNC_DEMO4, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
    { CAM_FUNC_DEMO5, 1, D_801B4EF4 }, // CAM_MODE_JUMP
};

CameraMode sCamSetAttentionModes[] = {
    { CAM_FUNC_DEMO1, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetWarp1Modes[] = {
    { CAM_FUNC_DEMO3, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetDungeon1Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B577C }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B57A4 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B50EC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B511C }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B57CC }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B57F4 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetFixed1Modes[] = {
    { CAM_FUNC_FIXD1, 4, D_801B5824 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetFixed2Modes[] = {
    { CAM_FUNC_FIXD1, 4, D_801B5834 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetMazeModes[] = {
    { CAM_FUNC_PARA2, 8, D_801B5844 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetRemoteBombModes[] = {
    { CAM_FUNC_NORM2, 8, D_801B5864 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetCirc1Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B5884 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetCirc2Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B58A0 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetCirc3Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B58BC },  // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_FIXD2, 7, D_801B5034 },  // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TARGET
    { CAM_FUNC_FIXD2, 7, D_801B5050 },  // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
};

CameraMode sCamSetCirc4Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B58D8 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetFixed3Modes[] = {
    { CAM_FUNC_FIXD1, 4, D_801B58F4 },  // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
};

CameraMode sCamSetTower0Modes[] = {
    { CAM_FUNC_NORM0, 9, D_801B5904 },  // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B5928 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B5950 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetParallel0Modes[] = {
    { CAM_FUNC_PARA1, 12, D_801B5978 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetNormDModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B59A8 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetSubjectDModes[] = {
    { CAM_FUNC_SUBJ1, 9, D_801B59D0 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetStart0Modes[] = {
    { CAM_FUNC_UNIQ0, 3, D_801B59F4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetStart2Modes[] = {
    { CAM_FUNC_UNIQ0, 3, D_801B5A00 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetStop0Modes[] = {
    { CAM_FUNC_UNIQ6, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetJCruisingModes[] = {
    { CAM_FUNC_SUBJ1, 9, D_801B5A0C }, // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C }, // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC }, // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_ZORAFIN
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_TARGET
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 }, // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 }, // CAM_MODE_BOWARROW
};

CameraMode sCamSetClimeMazeModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B4710 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_PARA1, 13, D_801B5A30 }, // CAM_MODE_CLIMB
    { CAM_FUNC_PARA1, 13, D_801B5A30 }, // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetSidedModes[] = {
    { CAM_FUNC_PARA1, 12, D_801B5A64 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetDungeon2Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5A94 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B5AF0 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B50EC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B5ABC }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B5B18 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5B40 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetBossShigeModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5B70 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B5C30 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B5B98 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B5BC8 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B5BFC }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B5C58 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_PARA1, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5308 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetKeepBackModes[] = {
    { CAM_FUNC_PARA1, 12, D_801B5C80 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_PARA1, 13, D_801B5A30 }, // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetCirc6Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B5CB0 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetCirc7Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B5CCC }, // CAM_MODE_NORMAL
};

CameraMode sCamSetChuBossModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5CE8 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B5D74 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B5D10 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B5D40 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B5D9C }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5308 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetRFixed1Modes[] = {
    { CAM_FUNC_FIXD1, 4, D_801B5DC4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetTresure1Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5DD4 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_ZORAFIN
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B5DFC }, // CAM_MODE_TARGET
};

CameraMode sCamSetBombBasketModes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B5E2C }, // CAM_MODE_NORMAL
};

CameraMode sCamSetCirc8Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B5E48 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetFukan1Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5E64 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B4F50 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4F20 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B5E8C }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_NORM1, 10, D_801B4EF8 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetDungeon3Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B5EB4 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B5F0C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B50EC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B5EDC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B511C }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B5F34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5F5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetTelescopeModes[] = {
    { CAM_FUNC_SUBJ1, 9, D_801B5F8C }, // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B5FD4 }, // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_ZORAFIN
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_SUBJ1, 9, D_801B5FB0 }, // CAM_MODE_TARGET
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_TALK
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_SLINGSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROW
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BATTLE
    { CAM_FUNC_SUBJ1, 9, D_801B5FF8 }, // CAM_MODE_NUTSHIDE
};

CameraMode sCamSetRoom0Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B601C }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6154 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B62F4 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B634C }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B62C4 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B6074 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6044 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B60A4 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B60D8 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B631C }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B626C }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B620C }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B610C },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B6130 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B61DC }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B617C }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B61AC }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B6294 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B6374 }, // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_NORM1, 10, D_801B63A4 }, // CAM_MODE_GORONJUMP
    { CAM_FUNC_SUBJ1, 9, D_801B48B0 },  // CAM_MODE_BOOMERANG
    { CAM_FUNC_PARA1, 12, D_801B623C }, // CAM_MODE_CHARGEZ
    { CAM_FUNC_PARA1, 12, D_801B63CC }, // CAM_MODE_ZORAFINZ
};

CameraMode sCamSetRCirc0Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B63FC }, // CAM_MODE_NORMAL
};

CameraMode sCamSetCirc9Modes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B6418 },  // CAM_MODE_NORMAL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_JUMP
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_FIXD2, 7, D_801B5034 },  // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_TARGET
    { CAM_FUNC_FIXD2, 7, D_801B5050 },  // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
};

CameraMode sCamSetOnThePoleModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6434 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B648C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B50EC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B645C }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B511C }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B655C }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B64B4 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B64D8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B64FC }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B652C }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B57F4 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetInBushModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6584 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6698 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B6674 },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B65DC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B65AC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B660C }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B6640 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B66C0 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_NORM1, 10, D_801B4EF8 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetBossLastModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B66E8 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6774 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B6710 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B6740 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B679C }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_PARA1, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5308 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetBossIniModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B67C4 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6880 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B681C }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B67EC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B684C }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B68A8 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_PARA1, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetBossHakModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B68D0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B692C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B697C }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B68F8 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6954 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_PARA1, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5308 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetBossKonModes[] = {
    { CAM_FUNC_JUMP3, 10, D_801B69A4 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_JUMP3, 10, D_801B4CFC }, // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_JUMP3, 10, D_801B6A58 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B69CC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B69FC }, // CAM_MODE_BATTLE
    { CAM_FUNC_JUMP3, 10, D_801B6A80 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6AA8 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_JUMP3, 10, D_801B4C34 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_JUMP3, 10, D_801B6A30 }, // CAM_MODE_GORONJUMP
};

CameraMode sCamSetConnect0Modes[] = {
    { CAM_FUNC_DEMO0, 1, D_801B4EF4 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetMorayModes[] = {
    { CAM_FUNC_JUMP3, 10, D_801B6AD0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_JUMP3, 10, D_801B6BC8 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_JUMP3, 10, D_801B6B50 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6AF8 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_JUMP3, 10, D_801B6B78 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6BA0 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_JUMP3, 10, D_801B4C34 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_JUMP3, 10, D_801B6B28 }, // CAM_MODE_GORONJUMP
};

CameraMode sCamSetNorm2Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6BF0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6C48 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6C18 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6C70 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetBombBowlModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6C98 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6D24 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B62F4 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B634C }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B62C4 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B6CC0 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6044 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B6CF0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B60D8 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B631C }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6D4C }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B620C }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B610C },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B6130 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B61DC }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B617C }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B61AC }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B6294 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B6374 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetCircAModes[] = {
    { CAM_FUNC_FIXD2, 7, D_801B6D74 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetWhirlpoolModes[] = {
    { CAM_FUNC_JUMP3, 10, D_801B6D90 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_JUMP3, 10, D_801B6E58 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_JUMP3, 10, D_801B6E08 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6AF8 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_JUMP3, 10, D_801B6E30 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_JUMP3, 10, D_801B6DB8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_JUMP3, 10, D_801B6DE0 }, // CAM_MODE_GORONJUMP
};

CameraMode sCamSetKokkogameModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6E80 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6C48 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6C18 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_NORM1, 10, D_801B6ED0 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6EA8 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
};

CameraMode sCamSetGiantModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6EF8 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B6F50 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B6F20 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B6F78 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetScene0Modes[] = {
    { CAM_FUNC_UNIQ2, 4, D_801B6FA0 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetRoom1Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6FB0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B703C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B62C4 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B6FD8 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B60A4 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B7008 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B7064 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B708C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetWater2Modes[] = {
    { CAM_FUNC_JUMP3, 10, D_801B70BC }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_JUMP3, 10, D_801B7148 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_JUMP3, 10, D_801B4C84 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B70E4 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B7114 }, // CAM_MODE_TALK
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_JUMP3, 10, D_801B4CAC }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4CD4 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_JUMP3, 10, D_801B4C34 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_NONE, 0, NULL },         // CAM_MODE_NUTSFLYZ
    { CAM_FUNC_JUMP3, 10, D_801B4C5C }, // CAM_MODE_GORONJUMP
};

CameraMode sCamSetSokonasiModes[] = {
    { CAM_FUNC_UNIQ3, 10, D_801B6584 }, // CAM_MODE_NORMAL
    { CAM_FUNC_UNIQ3, 10, D_801B6698 }, // CAM_MODE_JUMP
    { CAM_FUNC_UNIQ3, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_UNIQ3, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B6674 },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B65DC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_UNIQ4, 12, D_801B65AC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B660C }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_UNIQ5, 13, D_801B6640 }, // CAM_MODE_BATTLE
    { CAM_FUNC_UNIQ4, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_UNIQ3, 10, D_801B66C0 }, // CAM_MODE_STILL
    { CAM_FUNC_UNIQ4, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_UNIQ4, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_UNIQ4, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_UNIQ4, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_UNIQ3, 10, D_801B6584 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_UNIQ4, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetForceKeepModes[] = {
    { CAM_FUNC_NORM1, 10, D_801B4710 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B7170 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B71A0 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetParallel1Modes[] = {
    { CAM_FUNC_PARA1, 12, D_801B71D4 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetStart1Modes[] = {
    { CAM_FUNC_UNIQ0, 3, D_801B7204 }, // CAM_MODE_NORMAL
};

CameraMode sCamSetRoom2Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B6FB0 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B703C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B62C4 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B6FD8 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B50BC }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B7210 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B7008 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B7064 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B708C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetNorm4Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B4710 }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B491C }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B4A8C }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B4768 }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B4738 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B7244 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B4798 }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B4A34 }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B49D4 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B4824 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B48F8 },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B49A4 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B4944 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B4974 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B4A5C }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraMode sCamSetShellModes[] = {
    { CAM_FUNC_KEEP4, 9, D_801B7278 }, // CAM_MODE_NORMAL
    { CAM_FUNC_KEEP4, 9, D_801B729C }, // CAM_MODE_JUMP
    { CAM_FUNC_KEEP4, 9, D_801B72E4 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_KEEP4, 9, D_801B72C0 }, // CAM_MODE_NUTSSHOT
    { CAM_FUNC_NONE, 0, NULL },        // CAM_MODE_BOWARROWZ
    { CAM_FUNC_KEEP4, 9, D_801B7308 }, // CAM_MODE_NUTSFLY
};

CameraMode sCamSetDungeon4Modes[] = {
    { CAM_FUNC_NORM1, 10, D_801B732C }, // CAM_MODE_NORMAL
    { CAM_FUNC_NORM1, 10, D_801B7384 }, // CAM_MODE_JUMP
    { CAM_FUNC_NORM1, 10, D_801B4AE0 }, // CAM_MODE_GORONDASH
    { CAM_FUNC_SUBJ1, 9, D_801B4ABC },  // CAM_MODE_NUTSSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B486C },  // CAM_MODE_BOWARROWZ
    { CAM_FUNC_NORM1, 10, D_801B4B38 }, // CAM_MODE_NUTSFLY
    { CAM_FUNC_SUBJ1, 9, D_801B47CC },  // CAM_MODE_FIRSTPERSON
    { CAM_FUNC_KEEP1, 12, D_801B5150 }, // CAM_MODE_BOOMFOLLLOW
    { CAM_FUNC_SUBJ1, 9, D_801B4BB8 },  // CAM_MODE_ZORAFIN
    { CAM_FUNC_KEEP1, 12, D_801B50EC }, // CAM_MODE_FOLLOWTARGET
    { CAM_FUNC_PARA1, 12, D_801B7354 }, // CAM_MODE_TARGET
    { CAM_FUNC_KEEP3, 13, D_801B47F0 }, // CAM_MODE_TALK
    { CAM_FUNC_SUBJ1, 9, D_801B48D4 },  // CAM_MODE_SLINGSHOT
    { CAM_FUNC_SUBJ1, 9, D_801B4848 },  // CAM_MODE_BOWARROW
    { CAM_FUNC_BATT1, 13, D_801B511C }, // CAM_MODE_BATTLE
    { CAM_FUNC_PARA1, 12, D_801B4B08 }, // CAM_MODE_NUTSHIDE
    { CAM_FUNC_NORM1, 10, D_801B73AC }, // CAM_MODE_STILL
    { CAM_FUNC_PARA1, 12, D_801B5220 }, // CAM_MODE_CHARGE
    { CAM_FUNC_JUMP2, 9, D_801B51D8 },  // CAM_MODE_CLIMB
    { CAM_FUNC_JUMP2, 9, D_801B51FC },  // CAM_MODE_CLIMBZ
    { CAM_FUNC_SPEC5, 8, D_801B4890 },  // CAM_MODE_HOOKSHOT
    { CAM_FUNC_PARA1, 12, D_801B51A8 }, // CAM_MODE_FREEFALL
    { CAM_FUNC_PARA1, 12, D_801B5280 }, // CAM_MODE_HANG
    { CAM_FUNC_PARA1, 12, D_801B52B0 }, // CAM_MODE_HANGZ
    { CAM_FUNC_PARA1, 12, D_801B5308 }, // CAM_MODE_PUSHPULL
    { CAM_FUNC_PARA1, 12, D_801B4B60 }, // CAM_MODE_NUTSFLYZ
};

CameraSetting sCameraSettings[] = {
    { 0x00000000, 0x00000000, NULL },                   // CAM_SET_NONE
    { 0x3FFFFFFF, 0x00000005, sCamSetNorm0Modes },      // CAM_SET_NORMAL0
    { 0x05FFEFF7, 0x00000005, sCamSetNorm3Modes },      // CAM_SET_NORMAL3
    { 0x00000401, 0x00000005, sCamSetCirc5Modes },      // CAM_SET_CIRCLE5
    { 0x00017E13, 0x80000005, sCamSetHorse0Modes },     // CAM_SET_HORSE0
    { 0x00000001, 0x80000005, sCamSetZora0Modes },      // CAM_SET_ZORA0
    { 0x00000001, 0x8000000C, sCamSetPreRend0Modes },   // CAM_SET_PREREND0
    { 0x00000001, 0x8000000C, sCamSetPreRend1Modes },   // CAM_SET_PREREND1
    { 0x00000001, 0xC0000007, sCamSetDoorCModes },      // CAM_SET_DOORC
    { 0x00000001, 0xC000000E, sCamSetDemo0Modes },      // CAM_SET_DEMO0
    { 0x00000001, 0x80000005, sCamSetFree0Modes },      // CAM_SET_FREE0
    { 0x03FFFFFF, 0x00000005, sCamSetFukan0Modes },     // CAM_SET_FUKAN0
    { 0x03FFFFFF, 0x00000005, sCamSetNorm1Modes },      // CAM_SET_NORMAL1
    { 0x03FFFFFF, 0x80000005, sCamSetNanameModes },     // CAM_SET_NANAME
    { 0x00001BD9, 0x80000005, sCamSetCirc0Modes },      // CAM_SET_CIRCLE0
    { 0x000011D9, 0x80000005, sCamSetFixed0Modes },     // CAM_SET_FIXED0
    { 0x00000001, 0x40000005, sCamSetSpiralModes },     // CAM_SET_SPIRAL
    { 0x3FFFFFFF, 0x00000005, sCamSetDungeon0Modes },   // CAM_SET_DUNGEON0
    { 0x0000002F, 0x00000005, sCamSetItem0Modes },      // CAM_SET_ITEM0
    { 0x0000002F, 0x00000005, sCamSetItem1Modes },      // CAM_SET_ITEM1
    { 0x0000002F, 0x00000005, sCamSetItem2Modes },      // CAM_SET_ITEM2
    { 0x0000002F, 0x00000005, sCamSetItem3Modes },      // CAM_SET_ITEM3
    { 0x00000001, 0x00000005, sCamSetNaviModes },       // CAM_SET_NAVI
    { 0x0000002F, 0x00000005, sCamSetWarp0Modes },      // CAM_SET_WARP0
    { 0x0000002F, 0x00000005, sCamSetDeathModes },      // CAM_SET_DEATH
    { 0x0000002F, 0x00000005, sCamSetRebirthModes },    // CAM_SET_REBIRTH
    { 0x00000001, 0x40000005, sCamSetTreasureModes },   // CAM_SET_TREASURE
    { 0x00000003, 0x00000005, sCamSetTransformModes },  // CAM_SET_TRANSFORM
    { 0x00000001, 0x00000005, sCamSetAttentionModes },  // CAM_SET_ATTENTION
    { 0x00000001, 0x00000005, sCamSetWarp1Modes },      // CAM_SET_WARP1
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon1Modes },   // CAM_SET_DUNGEON1
    { 0x00000001, 0x80000005, sCamSetFixed1Modes },     // CAM_SET_FIXED1
    { 0x00000001, 0x80000005, sCamSetFixed2Modes },     // CAM_SET_FIXED2
    { 0x00000001, 0x00000005, sCamSetMazeModes },       // CAM_SET_MAZE
    { 0x00000001, 0x00000005, sCamSetRemoteBombModes }, // CAM_SET_REMOTEBOMB
    { 0x00000001, 0x80000005, sCamSetCirc1Modes },      // CAM_SET_CIRCLE1
    { 0x00000001, 0x80000005, sCamSetCirc2Modes },      // CAM_SET_CIRCLE2
    { 0x00001BD9, 0x80000005, sCamSetCirc3Modes },      // CAM_SET_CIRCLE3
    { 0x00000001, 0x80000005, sCamSetCirc4Modes },      // CAM_SET_CIRCLE4
    { 0x000011D9, 0x80000005, sCamSetFixed3Modes },     // CAM_SET_FIXED3
    { 0x03FFFFFF, 0x80000005, sCamSetTower0Modes },     // CAM_SET_TOWER0
    { 0x00000001, 0x80000005, sCamSetParallel0Modes },  // CAM_SET_PARALLEL0
    { 0x00000001, 0x00000005, sCamSetNormDModes },      // CAM_SET_NORMALD
    { 0x00000001, 0x00000005, sCamSetSubjectDModes },   // CAM_SET_SUBJECTD
    { 0x00000001, 0xC0000008, sCamSetStart0Modes },     // CAM_SET_START0
    { 0x00000001, 0xC0000008, sCamSetStart2Modes },     // CAM_SET_START2
    { 0x00000001, 0x00000005, sCamSetStop0Modes },      // CAM_SET_STOP0
    { 0x00003051, 0x00000005, sCamSetJCruisingModes },  // CAM_SET_JCRUISING
    { 0x03FFFFFF, 0x00000005, sCamSetClimeMazeModes },  // CAM_SET_CLIMEMAZE
    { 0x00000001, 0x00000005, sCamSetSidedModes },      // CAM_SET_SIDED
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon2Modes },   // CAM_SET_DUNGEON2
    { 0x03FFFFFF, 0x00000005, sCamSetBossShigeModes },  // CAM_SET_BOSS_SHIGE
    { 0x03FFFFFF, 0x80000005, sCamSetKeepBackModes },   // CAM_SET_KEEPBACK
    { 0x00000001, 0x80000005, sCamSetCirc6Modes },      // CAM_SET_CIRCLE6
    { 0x00000001, 0x80000005, sCamSetCirc7Modes },      // CAM_SET_CIRCLE7
    { 0x03FFFFFF, 0x00000005, sCamSetChuBossModes },    // CAM_SET_CHUBOSS
    { 0x00000001, 0x80000005, sCamSetRFixed1Modes },    // CAM_SET_RFIXED1
    { 0x00000401, 0x00000005, sCamSetTresure1Modes },   // CAM_SET_TRESURE1
    { 0x00000001, 0x80000005, sCamSetBombBasketModes }, // CAM_SET_BOMBBASKET
    { 0x00000001, 0x80000005, sCamSetCirc8Modes },      // CAM_SET_CIRCLE8
    { 0x03FFFFFF, 0x00000005, sCamSetFukan1Modes },     // CAM_SET_FUKAN1
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon3Modes },   // CAM_SET_DUNGEON3
    { 0x00008441, 0x0000000A, sCamSetTelescopeModes },  // CAM_SET_TELESCOPE
    { 0x3FFFFFFF, 0x00000005, sCamSetRoom0Modes },      // CAM_SET_ROOM0
    { 0x00000001, 0x80000005, sCamSetRCirc0Modes },     // CAM_SET_RCIRC0
    { 0x00001BD9, 0x80000005, sCamSetCirc9Modes },      // CAM_SET_CIRCLE9
    { 0x03FFFFFF, 0x00000005, sCamSetOnThePoleModes },  // CAM_SET_ONTHEPOLE
    { 0x03FFFFFF, 0x00000005, sCamSetInBushModes },     // CAM_SET_INBUSH
    { 0x03FFFFFF, 0x00000005, sCamSetBossLastModes },   // CAM_SET_BOSS_LAST
    { 0x03FFFFFF, 0x00000005, sCamSetBossIniModes },    // CAM_SET_BOSS_INI
    { 0x03FFFFFF, 0x00000005, sCamSetBossHakModes },    // CAM_SET_BOSS_HAK
    { 0x05FFEFF7, 0x00000005, sCamSetBossKonModes },    // CAM_SET_BOSS_KON
    { 0x00000001, 0x00000005, sCamSetConnect0Modes },   // CAM_SET_CONNECT0
    { 0x05FFEFF7, 0x00000005, sCamSetMorayModes },      // CAM_SET_MORAY
    { 0x03FFFFFF, 0x00000005, sCamSetNorm2Modes },      // CAM_SET_NORMAL2
    { 0x03FFFFFF, 0x00000005, sCamSetBombBowlModes },   // CAM_SET_BOMBBOWL
    { 0x00000001, 0x80000005, sCamSetCircAModes },      // CAM_SET_CIRCLEA
    { 0x05FFEFF7, 0x00000005, sCamSetWhirlpoolModes },  // CAM_SET_WHIRLPOOL
    { 0x01FFFFDF, 0x00000005, sCamSetKokkogameModes },  // CAM_SET_KOKKOGAME
    { 0x03FFFFFF, 0x00000005, sCamSetGiantModes },      // CAM_SET_GIANT
    { 0x00000001, 0x00000008, sCamSetScene0Modes },     // CAM_SET_SCENE0
    { 0x03FFFFFF, 0x00000005, sCamSetRoom1Modes },      // CAM_SET_ROOM1
    { 0x05FFEFF7, 0x00000005, sCamSetWater2Modes },     // CAM_SET_WATER2
    { 0x03FFFFFF, 0x00000005, sCamSetSokonasiModes },   // CAM_SET_SOKONASI
    { 0x03FFFFFF, 0x00000005, sCamSetForceKeepModes },  // CAM_SET_FORCEKEEP
    { 0x03FFFFFF, 0x80000005, sCamSetParallel1Modes },  // CAM_SET_PARALLEL1
    { 0x00000001, 0xC0000008, sCamSetStart1Modes },     // CAM_SET_START1
    { 0x03FFFFFF, 0x00000005, sCamSetRoom2Modes },      // CAM_SET_ROOM2
    { 0x03FFFFFF, 0x00000005, sCamSetNorm4Modes },      // CAM_SET_NORMAL4
    { 0x0000002F, 0x00000005, sCamSetShellModes },      // CAM_SET_SHELL
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon4Modes },   // CAM_SET_DUNGEON4
};

static s16 D_801B9CB0[26] = { CAM_SET_SHELL,     CAM_SET_SIDED,    CAM_SET_JCRUISING,  CAM_SET_NONE,  CAM_SET_SUBJECTD,
                              CAM_SET_NORMALD,   CAM_SET_NONE,     CAM_SET_NONE,       CAM_SET_NONE,  CAM_SET_WARP1,
                              CAM_SET_ATTENTION, CAM_SET_CONNECT0, CAM_SET_REMOTEBOMB, CAM_SET_NONE,  CAM_SET_TRANSFORM,
                              CAM_SET_TREASURE,  CAM_SET_REBIRTH,  CAM_SET_DEATH,      CAM_SET_WARP0, CAM_SET_NAVI,
                              CAM_SET_ITEM3,     CAM_SET_ITEM2,    CAM_SET_ITEM1,      CAM_SET_ITEM0, CAM_SET_STOP0,
                              CAM_SET_NONE };

static s16* D_801B9CE4 = &D_801B9CB0[25];

s32 Camera_Noop(Camera* camera);
s32 Camera_Normal1(Camera* camera);
s32 Camera_Normal2(Camera* camera);
s32 Camera_Normal3(Camera* camera);
s32 Camera_Normal4(Camera* camera);
s32 Camera_Normal0(Camera* camera);
s32 Camera_Parallel1(Camera* camera);
s32 Camera_Parallel2(Camera* camera);
s32 Camera_Parallel3(Camera* camera);
s32 Camera_Parallel4(Camera* camera);
s32 Camera_Parallel0(Camera* camera);
s32 Camera_Jump1(Camera* camera);
s32 Camera_Jump2(Camera* camera);
s32 Camera_Jump3(Camera* camera);
s32 Camera_Jump4(Camera* camera);
s32 Camera_Jump0(Camera* camera);
s32 Camera_Battle1(Camera* camera);
s32 Camera_Battle2(Camera* camera);
s32 Camera_Battle3(Camera* camera);
s32 Camera_Battle4(Camera* camera);
s32 Camera_Battle0(Camera* camera);
s32 Camera_KeepOn1(Camera* camera);
s32 Camera_KeepOn2(Camera* camera);
s32 Camera_KeepOn3(Camera* camera);
s32 Camera_KeepOn4(Camera* camera);
s32 Camera_KeepOn0(Camera* camera);
s32 Camera_Fixed1(Camera* camera);
s32 Camera_Fixed2(Camera* camera);
s32 Camera_Fixed3(Camera* camera);
s32 Camera_Fixed4(Camera* camera);
s32 Camera_Fixed0(Camera* camera);
s32 Camera_Subj1(Camera* camera);
s32 Camera_Subj2(Camera* camera);
s32 Camera_Subj3(Camera* camera);
s32 Camera_Subj4(Camera* camera);
s32 Camera_Subj0(Camera* camera);
s32 Camera_Data0(Camera* camera);
s32 Camera_Data1(Camera* camera);
s32 Camera_Data2(Camera* camera);
s32 Camera_Data3(Camera* camera);
s32 Camera_Data4(Camera* camera);
s32 Camera_Unique1(Camera* camera);
s32 Camera_Unique2(Camera* camera);
s32 Camera_Unique3(Camera* camera);
s32 Camera_Unique4(Camera* camera);
s32 Camera_Unique5(Camera* camera);
s32 Camera_Unique0(Camera* camera);
s32 Camera_Unique6(Camera* camera);
s32 Camera_Unique7(Camera* camera);
s32 Camera_Unique8(Camera* camera);
s32 Camera_Unique9(Camera* camera);
s32 Camera_Demo1(Camera* camera);
s32 Camera_Demo2(Camera* camera);
s32 Camera_Demo3(Camera* camera);
s32 Camera_Demo4(Camera* camera);
s32 Camera_Demo5(Camera* camera);
s32 Camera_Demo6(Camera* camera);
s32 Camera_Demo7(Camera* camera);
s32 Camera_Demo8(Camera* camera);
s32 Camera_Demo9(Camera* camera);
s32 Camera_Demo0(Camera* camera);
s32 Camera_Special0(Camera* camera);
s32 Camera_Special1(Camera* camera);
s32 Camera_Special2(Camera* camera);
s32 Camera_Special3(Camera* camera);
s32 Camera_Special4(Camera* camera);
s32 Camera_Special5(Camera* camera);
s32 Camera_Special6(Camera* camera);
s32 Camera_Special7(Camera* camera);
s32 Camera_Special8(Camera* camera);
s32 Camera_Special9(Camera* camera);

s32 (*sCameraFunctions[])(Camera*) = {
	NULL,
	Camera_Normal0,
	Camera_Normal1,
	Camera_Normal2,
	Camera_Normal3,
	Camera_Normal4,
	Camera_Parallel0,
	Camera_Parallel1,
	Camera_Parallel2,
	Camera_Parallel3,
	Camera_Parallel4,
	Camera_KeepOn0,
	Camera_KeepOn1,
	Camera_KeepOn2,
	Camera_KeepOn3,
	Camera_KeepOn4,
	Camera_Subj0,
	Camera_Subj1,
	Camera_Subj2,
	Camera_Subj3,
	Camera_Subj4,
	Camera_Jump0,
	Camera_Jump1,
	Camera_Jump2,
	Camera_Jump3,
	Camera_Jump4,
	Camera_Battle0,
	Camera_Battle1,
	Camera_Battle2,
	Camera_Battle3,
	Camera_Battle4,
	Camera_Fixed0,
	Camera_Fixed1,
	Camera_Fixed2,
	Camera_Fixed3,
	Camera_Fixed4,
	Camera_Data0,
	Camera_Data1,
	Camera_Data2,
	Camera_Data3,
	Camera_Data4,
	Camera_Unique0,
	Camera_Unique1,
	Camera_Unique2,
	Camera_Unique3,
	Camera_Unique4,
	Camera_Unique5,
	Camera_Unique6,
	Camera_Unique7,
	Camera_Unique8,
	Camera_Unique9,
	Camera_Demo0,
	Camera_Demo1,
	Camera_Demo2,
	Camera_Demo3,
	Camera_Demo4,
	Camera_Demo5,
	Camera_Demo6,
	Camera_Demo7,
	Camera_Demo8,
	Camera_Demo9,
	Camera_Special0,
	Camera_Special1,
	Camera_Special2,
	Camera_Special3,
	Camera_Special4,
	Camera_Special5,
	Camera_Special6,
	Camera_Special7,
	Camera_Special8,
	Camera_Special9,
};

static s16 sNextUID = 0;
static s32 sCameraInterfaceFlags = 1;
static s32 sCameraInterfaceAlpha = 2;
static s32 sCameraShrinkWindowVal = 0x20;
static s32 D_801B9E14 = -1;

// VecSph yaw data
static s16 D_801B9E18[] = {
    0x0AAA, 0xF556, 0x1555, 0xEAAB, 0x2AAA, 0xD556, 0x3FFF, 0xC001, 0x5555, 0xAAAB, 0x6AAA, 0x9556, 0x7FFF, 0x0000,
};

// VecSph pitch data
static s16 D_801B9E34[] = {
    0x0000, 0x02C6, 0x058C, 0x0000, 0x0000, 0xFD3A, 0x0000, 0x0852, 0x0000, 0x0000, 0x0B18, 0x02C6, 0xFA74, 0x0000,
};

static s32 sUpdateCameraDirection = 0;
static s32 sIsFalse = false;
static s32 sCameraInitCounter = 0;
