#include "ultra64.h"
#include "global.h"

/*=====================================================================
 *                   Default Data: NORMAL0 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal0ModeNormalData[] = {
    CAM_FUNCDATA_NORM1( // CAM_FUNC_NORM1
        -20,            // CAM_DATA_YOFFSET
        0x118,          // CAM_DATA_01
        0x140,          // CAM_DATA_02
        10,             // CAM_DATA_PITCHTARGET
        0x16,           // CAM_DATA_04
        0xF,            // CAM_DATA_05
        0x28,           // CAM_DATA_YAWDIFFRANGE
        60,             // CAM_DATA_FOV
        0x54,           // CAM_DATA_08
        (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
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
 * BOSS_GOHT    TARGET      PARA1
 * BOSS_GYORG   TARGET      PARA1
 * FORCEKEEP    TARGET      PARA1
 * PARALLEL1    TARGET      PARA1
 * NORMAL4      TARGET      PARA1
 */
CameraModeValue sSetNormal0ModeTargetData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x5, CAM_DATA_04 },
    { 0x5, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting         Mode            Function
 * ------------    ------------    --------
 * NORMAL0         FOLLOWTARGET    KEEP1
 * NORMAL3         FOLLOWTARGET    KEEP1
 * FUKAN0          FOLLOWTARGET    KEEP1
 * NORMAL1         FOLLOWTARGET    KEEP1
 * NANAME          FOLLOWTARGET    KEEP1
 * TOWER0          FOLLOWTARGET    KEEP1
 * CLIMEMAZE       FOLLOWTARGET    KEEP1
 * KEEPBACK        FOLLOWTARGET    KEEP1
 * FUKAN1          FOLLOWTARGET    KEEP1
 * BOSS_GOHT       FOLLOWTARGET    KEEP1
 * PINNACLE_ROCK   FOLLOWTARGET    KEEP1
 * NORMAL2         FOLLOWTARGET    KEEP1
 * WHIRLPOOL       FOLLOWTARGET    KEEP1
 * CUCCO_SHACK     FOLLOWTARGET    KEEP1
 * GIANT           FOLLOWTARGET    KEEP1
 * WATER2          FOLLOWTARGET    KEEP1
 * PARALLEL1       FOLLOWTARGET    KEEP1
 * NORMAL4         FOLLOWTARGET    KEEP1
 */
CameraModeValue sSetNormal0ModeFollowTargetData[] = {
    { -30, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x28, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0xF, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting         Mode      Function
 * ------------    ------    --------
 * NORMAL0         BATTLE    BATT1
 * NORMAL3         BATTLE    BATT1
 * FUKAN0          BATTLE    BATT1
 * NORMAL1         BATTLE    BATT1
 * NANAME          BATTLE    BATT1
 * TOWER0          BATTLE    BATT1
 * CLIMEMAZE       BATTLE    BATT1
 * KEEPBACK        BATTLE    BATT1
 * FUKAN1          BATTLE    BATT1
 * PINNACLE_ROCK   BATTLE    BATT1
 * NORMAL2         BATTLE    BATT1
 * WHIRLPOOL       BATTLE    BATT1
 * CUCCO_SHACK     BATTLE    BATT1
 * GIANT           BATTLE    BATT1
 * WATER2          BATTLE    BATT1
 * PARALLEL1       BATTLE    BATT1
 * NORMAL4         BATTLE    BATT1
 */
CameraModeValue sSetNormal0ModeBattleData[] = {
    { -30, CAM_DATA_YOFFSET },
    { 0x96, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 60, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 20, CAM_DATA_16 },
    { 0x23, CAM_DATA_17 },
    { 55, CAM_DATA_FOV },
    { 0x46, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x19, CAM_DATA_11 },
    { 0x28, CAM_DATA_18 },
};

/**
 * Setting        Mode           Function
 * ------------   -----------    --------
 * NORMAL0        FIRSTPERSON    SUBJ1
 * NORMAL3        FIRSTPERSON    SUBJ1
 * FUKAN0         FIRSTPERSON    SUBJ1
 * NORMAL1        FIRSTPERSON    SUBJ1
 * NANAME         FIRSTPERSON    SUBJ1
 * CIRCLE0        FIRSTPERSON    SUBJ1
 * FIXED0         FIRSTPERSON    SUBJ1
 * DUNGEON0       FIRSTPERSON    SUBJ1
 * DUNGEON1       FIRSTPERSON    SUBJ1
 * CIRCLE3        FIRSTPERSON    SUBJ1
 * FIXED3         FIRSTPERSON    SUBJ1
 * TOWER0         FIRSTPERSON    SUBJ1
 * JCRUISING      FIRSTPERSON    SUBJ1
 * CLIMEMAZE      FIRSTPERSON    SUBJ1
 * DUNGEON2       FIRSTPERSON    SUBJ1
 * BOSS_ODOLWA    FIRSTPERSON    SUBJ1
 * KEEPBACK       FIRSTPERSON    SUBJ1
 * MINIBOSS       FIRSTPERSON    SUBJ1
 * FUKAN1         FIRSTPERSON    SUBJ1
 * DUNGEON3       FIRSTPERSON    SUBJ1
 * ROOM0          FIRSTPERSON    SUBJ1
 * CIRCLE9        FIRSTPERSON    SUBJ1
 * ONTHEPOLE      FIRSTPERSON    SUBJ1
 * BOSS_MAJORA    FIRSTPERSON    SUBJ1
 * BOSS_TWINMOLD  FIRSTPERSON    SUBJ1
 * BOSS_GOHT      FIRSTPERSON    SUBJ1
 * BOSS_GYORG     FIRSTPERSON    SUBJ1
 * PINNACLE_ROCK  FIRSTPERSON    SUBJ1
 * NORMAL2        FIRSTPERSON    SUBJ1
 * BOMBBOWL       FIRSTPERSON    SUBJ1
 * WHIRLPOOL      FIRSTPERSON    SUBJ1
 * CUCCO_SHACK    FIRSTPERSON    SUBJ1
 * GIANT          FIRSTPERSON    SUBJ1
 * ROOM1          FIRSTPERSON    SUBJ1
 * WATER2         FIRSTPERSON    SUBJ1
 * FORCEKEEP      FIRSTPERSON    SUBJ1
 * PARALLEL1      FIRSTPERSON    SUBJ1
 * ROOM2          FIRSTPERSON    SUBJ1
 * NORMAL4        FIRSTPERSON    SUBJ1
 * DUNGEON4       FIRSTPERSON    SUBJ1
 */
CameraModeValue sSetNormal0ModeFirstPersonData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 5, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting        Mode    Function
 * ------------   ----    --------
 * NORMAL0        TALK    KEEP3
 * NORMAL3        TALK    KEEP3
 * FUKAN0         TALK    KEEP3
 * NORMAL1        TALK    KEEP3
 * NANAME         TALK    KEEP3
 * DUNGEON0       TALK    KEEP3
 * DUNGEON1       TALK    KEEP3
 * TOWER0         TALK    KEEP3
 * CLIMEMAZE      TALK    KEEP3
 * DUNGEON2       TALK    KEEP3
 * KEEPBACK       TALK    KEEP3
 * MINIBOSS       TALK    KEEP3
 * FUKAN1         TALK    KEEP3
 * DUNGEON3       TALK    KEEP3
 * ONTHEPOLE      TALK    KEEP3
 * BOSS_MAJORA    TALK    KEEP3
 * BOSS_TWINMOLD  TALK    KEEP3
 * BOSS_GOHT      TALK    KEEP3
 * BOSS_GYORG     TALK    KEEP3
 * PINNACLE_ROCK  TALK    KEEP3
 * NORMAL2        TALK    KEEP3
 * WHIRLPOOL      TALK    KEEP3
 * CUCCO_SHACK    TALK    KEEP3
 * GIANT          TALK    KEEP3
 * FORCEKEEP      TALK    KEEP3
 * PARALLEL1      TALK    KEEP3
 * DUNGEON4       TALK    KEEP3
 */
CameraModeValue sSetNormal0ModeTalkData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 80, CAM_DATA_01 },
    { 0x96, CAM_DATA_02 },
    { 50, CAM_DATA_13 },
    { 0x5, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 0x5, CAM_DATA_16 },
    { 0x28, CAM_DATA_17 },
    { 35, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5), CAM_DATA_FLAGS },
    { 60, CAM_DATA_18 },
};

/**
 * Setting        Mode     Function
 * ------------   -----    --------
 * NORMAL0        CLIMB    JUMP2
 * NORMAL3        CLIMB    JUMP2
 * FUKAN0         CLIMB    JUMP2
 * NORMAL1        CLIMB    JUMP2
 * NANAME         CLIMB    JUMP2
 * TOWER0         CLIMB    JUMP2
 * KEEPBACK       CLIMB    JUMP2
 * FUKAN1         CLIMB    JUMP2
 * INBUSH         CLIMB    JUMP2
 * BOSS_TWINMOLD  CLIMB    JUMP2
 * BOSS_GYORG     CLIMB    JUMP2
 * PINNACLE_ROCK  CLIMB    JUMP2
 * NORMAL2        CLIMB    JUMP2
 * WHIRLPOOL      CLIMB    JUMP2
 * CUCCO_SHACK    CLIMB    JUMP2
 * GIANT          CLIMB    JUMP2
 * WATER2         CLIMB    JUMP2
 * FORCEKEEP      CLIMB    JUMP2
 * PARALLEL1      CLIMB    JUMP2
 * NORMAL4        CLIMB    JUMP2
 */
CameraModeValue sSetNormal0ModeClimbData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x5, CAM_DATA_04 },
    { 0x5, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 0x28, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL0        BOWARROW    SUBJ1
 * NORMAL3        BOWARROW    SUBJ1
 * FUKAN0         BOWARROW    SUBJ1
 * NORMAL1        BOWARROW    SUBJ1
 * NANAME         BOWARROW    SUBJ1
 * DUNGEON0       BOWARROW    SUBJ1
 * DUNGEON1       BOWARROW    SUBJ1
 * TOWER0         BOWARROW    SUBJ1
 * JCRUISING      BOWARROW    SUBJ1
 * CLIMEMAZE      BOWARROW    SUBJ1
 * DUNGEON2       BOWARROW    SUBJ1
 * BOSS_ODOLWA    BOWARROW    SUBJ1
 * KEEPBACK       BOWARROW    SUBJ1
 * MINIBOSS       BOWARROW    SUBJ1
 * FUKAN1         BOWARROW    SUBJ1
 * DUNGEON3       BOWARROW    SUBJ1
 * ROOM0          BOWARROW    SUBJ1
 * ONTHEPOLE      BOWARROW    SUBJ1
 * INBUSH         BOWARROW    SUBJ1
 * BOSS_MAJORA    BOWARROW    SUBJ1
 * BOSS_TWINMOLD  BOWARROW    SUBJ1
 * BOSS_GOHT      BOWARROW    SUBJ1
 * BOSS_GYORG     BOWARROW    SUBJ1
 * PINNACLE_ROCK  BOWARROW    SUBJ1
 * NORMAL2        BOWARROW    SUBJ1
 * BOMBBOWL       BOWARROW    SUBJ1
 * WHIRLPOOL      BOWARROW    SUBJ1
 * CUCCO_SHACK    BOWARROW    SUBJ1
 * GIANT          BOWARROW    SUBJ1
 * ROOM1          BOWARROW    SUBJ1
 * WATER2         BOWARROW    SUBJ1
 * SOKONASI       BOWARROW    SUBJ1
 * FORCEKEEP      BOWARROW    SUBJ1
 * PARALLEL1      BOWARROW    SUBJ1
 * ROOM2          BOWARROW    SUBJ1
 * NORMAL4        BOWARROW    SUBJ1
 * DUNGEON4       BOWARROW    SUBJ1
 */
CameraModeValue sSetNormal0ModeBowArrowData[] = {
    { 0xFFF9, CAM_DATA_YOFFSET },
    { 0xE, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { -30, CAM_DATA_17 },
    { -5, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting        Mode         Function
 * ------------   ---------    --------
 * NORMAL0        BOWARROWZ    SUBJ1
 * NORMAL3        BOWARROWZ    SUBJ1
 * HORSE          BOWARROWZ    SUBJ1
 * FUKAN0         BOWARROWZ    SUBJ1
 * NORMAL1        BOWARROWZ    SUBJ1
 * NANAME         BOWARROWZ    SUBJ1
 * CIRCLE0        BOWARROWZ    SUBJ1
 * FIXED0         BOWARROWZ    SUBJ1
 * DUNGEON0       BOWARROWZ    SUBJ1
 * DUNGEON1       BOWARROWZ    SUBJ1
 * CIRCLE3        BOWARROWZ    SUBJ1
 * FIXED3         BOWARROWZ    SUBJ1
 * TOWER0         BOWARROWZ    SUBJ1
 * JCRUISING      BOWARROWZ    SUBJ1
 * CLIMEMAZE      BOWARROWZ    SUBJ1
 * DUNGEON2       BOWARROWZ    SUBJ1
 * BOSS_ODOLWA    BOWARROWZ    SUBJ1
 * KEEPBACK       BOWARROWZ    SUBJ1
 * MINIBOSS       BOWARROWZ    SUBJ1
 * FUKAN1         BOWARROWZ    SUBJ1
 * DUNGEON3       BOWARROWZ    SUBJ1
 * ROOM0          BOWARROWZ    SUBJ1
 * CIRCLE9        BOWARROWZ    SUBJ1
 * ONTHEPOLE      BOWARROWZ    SUBJ1
 * INBUSH         BOWARROWZ    SUBJ1
 * BOSS_MAJORA    BOWARROWZ    SUBJ1
 * BOSS_TWINMOLD  BOWARROWZ    SUBJ1
 * BOSS_GOHT      BOWARROWZ    SUBJ1
 * BOSS_GYORG     BOWARROWZ    SUBJ1
 * PINNACLE_ROCK  BOWARROWZ    SUBJ1
 * NORMAL2        BOWARROWZ    SUBJ1
 * BOMBBOWL       BOWARROWZ    SUBJ1
 * WHIRLPOOL      BOWARROWZ    SUBJ1
 * CUCCO_SHACK    BOWARROWZ    SUBJ1
 * GIANT          BOWARROWZ    SUBJ1
 * ROOM1          BOWARROWZ    SUBJ1
 * WATER2         BOWARROWZ    SUBJ1
 * SOKONASI       BOWARROWZ    SUBJ1
 * FORCEKEEP      BOWARROWZ    SUBJ1
 * PARALLEL1      BOWARROWZ    SUBJ1
 * ROOM2          BOWARROWZ    SUBJ1
 * NORMAL4        BOWARROWZ    SUBJ1
 * DUNGEON4       BOWARROWZ    SUBJ1
 */
CameraModeValue sSetNormal0ModeBowArrowZData[] = {
    { 20, CAM_DATA_YOFFSET },
    { 0x46, CAM_DATA_01 },
    { 0x46, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0xFF88, CAM_DATA_19 },
    { 20, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting        Mode         Function
 * ------------   ---------    --------
 * NORMAL0        HOOKSHOT    SPEC5
 * NORMAL3        HOOKSHOT    SPEC5
 * FUKAN0         HOOKSHOT    SPEC5
 * NORMAL1        HOOKSHOT    SPEC5
 * NANAME         HOOKSHOT    SPEC5
 * DUNGEON0       HOOKSHOT    SPEC5
 * DUNGEON1       HOOKSHOT    SPEC5
 * TOWER0         HOOKSHOT    SPEC5
 * CLIMEMAZE      HOOKSHOT    SPEC5
 * DUNGEON2       HOOKSHOT    SPEC5
 * BOSS_ODOLWA    HOOKSHOT    SPEC5
 * KEEPBACK       HOOKSHOT    SPEC5
 * MINIBOSS       HOOKSHOT    SPEC5
 * FUKAN1         HOOKSHOT    SPEC5
 * DUNGEON3       HOOKSHOT    SPEC5
 * ROOM0          HOOKSHOT    SPEC5
 * ONTHEPOLE      HOOKSHOT    SPEC5
 * INBUSH         HOOKSHOT    SPEC5
 * BOSS_MAJORA    HOOKSHOT    SPEC5
 * BOSS_TWINMOLD  HOOKSHOT    SPEC5
 * BOSS_GOHT      HOOKSHOT    SPEC5
 * BOSS_GYORG     HOOKSHOT    SPEC5
 * PINNACLE_ROCK  HOOKSHOT    SPEC5
 * NORMAL2        HOOKSHOT    SPEC5
 * BOMBBOWL       HOOKSHOT    SPEC5
 * WHIRLPOOL      HOOKSHOT    SPEC5
 * CUCCO_SHACK    HOOKSHOT    SPEC5
 * GIANT          HOOKSHOT    SPEC5
 * ROOM1          HOOKSHOT    SPEC5
 * WATER2         HOOKSHOT    SPEC5
 * SOKONASI       HOOKSHOT    SPEC5
 * FORCEKEEP      HOOKSHOT    SPEC5
 * PARALLEL1      HOOKSHOT    SPEC5
 * ROOM2          HOOKSHOT    SPEC5
 * NORMAL4        HOOKSHOT    SPEC5
 * DUNGEON4       HOOKSHOT    SPEC5
 */
CameraModeValue sSetNormal0ModeHookshotData[] = {
    { -20, CAM_DATA_YOFFSET },    // yOffset
    { 80, CAM_DATA_01 },     // eyeDist
    { 250, CAM_DATA_02 },    // minDistForRot
    { 45, CAM_DATA_PITCHTARGET },     // fovTarget
    { 60, CAM_DATA_FOV },     // atMaxLERPScale
    { 40, CAM_DATA_08 },     // timerInit
    { 6, CAM_DATA_12 },      // pitch
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting     Mode         Function
 * --------    ---------    --------
 * NORMAL0     BOOMERANG    SUBJ1
 * DUNGEON0    BOOMERANG    SUBJ1
 * ROOM0       BOOMERANG    SUBJ1
 */
CameraModeValue sSetNormal0ModeBoomerangData[] = {
    { 0x5, CAM_DATA_YOFFSET },
    { 50, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting        Mode         Function
 * ------------   ---------    --------
 * NORMAL0        SLINGSHOT    SUBJ1
 * FUKAN0         SLINGSHOT    SUBJ1
 * NORMAL1        SLINGSHOT    SUBJ1
 * NANAME         SLINGSHOT    SUBJ1
 * CIRCLE0        SLINGSHOT    SUBJ1
 * FIXED0         SLINGSHOT    SUBJ1
 * DUNGEON0       SLINGSHOT    SUBJ1
 * DUNGEON1       SLINGSHOT    SUBJ1
 * CIRCLE3        SLINGSHOT    SUBJ1
 * FIXED3         SLINGSHOT    SUBJ1
 * TOWER0         SLINGSHOT    SUBJ1
 * JCRUISING      SLINGSHOT    SUBJ1
 * CLIMEMAZE      SLINGSHOT    SUBJ1
 * DUNGEON2       SLINGSHOT    SUBJ1
 * BOSS_ODOLWA    SLINGSHOT    SUBJ1
 * KEEPBACK       SLINGSHOT    SUBJ1
 * MINIBOSS       SLINGSHOT    SUBJ1
 * FUKAN1         SLINGSHOT    SUBJ1
 * DUNGEON3       SLINGSHOT    SUBJ1
 * ROOM0          SLINGSHOT    SUBJ1
 * CIRCLE9        SLINGSHOT    SUBJ1
 * ONTHEPOLE      SLINGSHOT    SUBJ1
 * INBUSH         SLINGSHOT    SUBJ1
 * BOSS_MAJORA    SLINGSHOT    SUBJ1
 * BOSS_TWINMOLD  SLINGSHOT    SUBJ1
 * BOSS_GOHT      SLINGSHOT    SUBJ1
 * NORMAL2        SLINGSHOT    SUBJ1
 * BOMBBOWL       SLINGSHOT    SUBJ1
 * CUCCO_SHACK    SLINGSHOT    SUBJ1
 * GIANT          SLINGSHOT    SUBJ1
 * ROOM1          SLINGSHOT    SUBJ1
 * SOKONASI       SLINGSHOT    SUBJ1
 * FORCEKEEP      SLINGSHOT    SUBJ1
 * PARALLEL1      SLINGSHOT    SUBJ1
 * ROOM2          SLINGSHOT    SUBJ1
 * NORMAL4        SLINGSHOT    SUBJ1
 * DUNGEON4       SLINGSHOT    SUBJ1
 */
CameraModeValue sSetNormal0ModeSlingshotData[] = {
    { 0xFFF9, CAM_DATA_YOFFSET },
    { 0x000E, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { -50, CAM_DATA_17 },
    { -10, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting        Mode      Function
 * ------------   ------    --------
 * NORMAL0        CLIMBZ    JUMP2
 * NORMAL3        CLIMBZ    JUMP2
 * FUKAN0         CLIMBZ    JUMP2
 * NORMAL1        CLIMBZ    JUMP2
 * NANAME         CLIMBZ    JUMP2
 * TOWER0         CLIMBZ    JUMP2
 * FUKAN1         CLIMBZ    JUMP2
 * INBUSH         CLIMBZ    JUMP2
 * BOSS_TWINMOLD  CLIMBZ    JUMP2
 * BOSS_GYORG     CLIMBZ    JUMP2
 * PINNACLE_ROCK  CLIMBZ    JUMP2
 * NORMAL2        CLIMBZ    JUMP2
 * WHIRLPOOL      CLIMBZ    JUMP2
 * CUCCO_SHACK    CLIMBZ    JUMP2
 * GIANT          CLIMBZ    JUMP2
 * WATER2         CLIMBZ    JUMP2
 * FORCEKEEP      CLIMBZ    JUMP2
 * PARALLEL1      CLIMBZ    JUMP2
 * NORMAL4        CLIMBZ    JUMP2
 */
CameraModeValue sSetNormal0ModeClimbZData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x03E7, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x4 | 0x2, CAM_DATA_FLAGS },
};

CameraModeValue sSetNormal0ModeJumpData[] = {
    CAM_FUNCDATA_NORM1( // CAM_FUNC_NORM1
        -20,            // CAM_DATA_YOFFSET
        0xF0,           // CAM_DATA_01
        0x154,          // CAM_DATA_02
        10,             // CAM_DATA_PITCHTARGET
        30,             // CAM_DATA_04
        0xC,            // CAM_DATA_05
        0x28,           // CAM_DATA_YAWDIFFRANGE
        60,             // CAM_DATA_FOV
        50,             // CAM_DATA_08
        (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/**
 * Setting        Mode    Function
 * ------------   ----    --------
 * NORMAL0        HANG    PARA1
 * NORMAL3        HANG    PARA1
 * FUKAN0         HANG    PARA1
 * NORMAL1        HANG    PARA1
 * NANAME         HANG    PARA1
 * TOWER0         HANG    PARA1
 * CLIMEMAZE      HANG    PARA1
 * KEEPBACK       HANG    PARA1
 * FUKAN1         HANG    PARA1
 * INBUSH         HANG    PARA1
 * BOSS_TWINMOLD  HANG    PARA1
 * BOSS_GYORG     HANG    PARA1
 * PINNACLE_ROCK  HANG    PARA1
 * NORMAL2        HANG    PARA1
 * WHIRLPOOL      HANG    PARA1
 * CUCCO_SHACK    HANG    PARA1
 * GIANT          HANG    PARA1
 * WATER2         HANG    PARA1
 * SOKONASI       HANG    PARA1
 * FORCEKEEP      HANG    PARA1
 * PARALLEL1      HANG    PARA1
 * NORMAL4        HANG    PARA1
 */
CameraModeValue sSetNormal0ModeHangData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0140, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0008, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting        Mode     Function
 * ------------   -----    --------
 * NORMAL0        HANGZ    PARA1
 * NORMAL3        HANGZ    PARA1
 * FUKAN0         HANGZ    PARA1
 * NORMAL1        HANGZ    PARA1
 * NANAME         HANGZ    PARA1
 * TOWER0         HANGZ    PARA1
 * CLIMEMAZE      HANGZ    PARA1
 * KEEPBACK       HANGZ    PARA1
 * FUKAN1         HANGZ    PARA1
 * INBUSH         HANGZ    PARA1
 * BOSS_TWINMOLD  HANGZ    PARA1
 * BOSS_GYORG     HANGZ    PARA1
 * PINNACLE_ROCK  HANGZ    PARA1
 * NORMAL2        HANGZ    PARA1
 * WHIRLPOOL      HANGZ    PARA1
 * CUCCO_SHACK    HANGZ    PARA1
 * GIANT          HANGZ    PARA1
 * WATER2         HANGZ    PARA1
 * SOKONASI       HANGZ    PARA1
 * FORCEKEEP      HANGZ    PARA1
 * PARALLEL1      HANGZ    PARA1
 * NORMAL4        HANGZ    PARA1
 */
CameraModeValue sSetNormal0ModeHangZData[] = {
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x0002, CAM_DATA_12 },
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL0        FREEFALL    PARA1
 * FUKAN0         FREEFALL    PARA1
 * NORMAL1        FREEFALL    PARA1
 * NANAME         FREEFALL    PARA1
 * TOWER0         FREEFALL    PARA1
 * CLIMEMAZE      FREEFALL    PARA1
 * KEEPBACK       FREEFALL    PARA1
 * FUKAN1         FREEFALL    PARA1
 * INBUSH         FREEFALL    PARA1
 * BOSS_TWINMOLD  FREEFALL    PARA1
 * NORMAL2        FREEFALL    PARA1
 * CUCCO_SHACK    FREEFALL    PARA1
 * GIANT          FREEFALL    PARA1
 * SOKONASI       FREEFALL    PARA1
 * FORCEKEEP      FREEFALL    PARA1
 * PARALLEL1      FREEFALL    PARA1
 * NORMAL4        FREEFALL    PARA1
 */
CameraModeValue sSetNormal0ModeFreeFallData[] = {
    { -10, CAM_DATA_YOFFSET },
    { 0x0140, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x80 | 0x8, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting        Mode      Function
 * ------------   ------    --------
 * NORMAL0        CHARGE    PARA1
 * NORMAL3        CHARGE    PARA1
 * FUKAN0         CHARGE    PARA1
 * NORMAL1        CHARGE    PARA1
 * NANAME         CHARGE    PARA1
 * TOWER0         CHARGE    PARA1
 * CLIMEMAZE      CHARGE    PARA1
 * KEEPBACK       CHARGE    PARA1
 * FUKAN1         CHARGE    PARA1
 * INBUSH         CHARGE    PARA1
 * BOSS_TWINMOLD  CHARGE    PARA1
 * BOSS_GYORG     CHARGE    PARA1
 * PINNACLE_ROCK  CHARGE    PARA1
 * NORMAL2        CHARGE    PARA1
 * WHIRLPOOL      CHARGE    PARA1
 * CUCCO_SHACK    CHARGE    PARA1
 * GIANT          CHARGE    PARA1
 * WATER2         CHARGE    PARA1
 * SOKONASI       CHARGE    PARA1
 * FORCEKEEP      CHARGE    PARA1
 * PARALLEL1      CHARGE    PARA1
 * NORMAL4        CHARGE    PARA1
 */
CameraModeValue sSetNormal0ModeChargeData[] = {
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 50, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * NORMAL0    CHARGEZ    PARA1
 */
CameraModeValue sSetNormal0ModeChargeZData[] = {
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 50, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

CameraModeValue sSetNormal0ModeStillData[] = {
    CAM_FUNCDATA_NORM1( // CAM_FUNC_NORM1
        -20,            // CAM_DATA_YOFFSET
        0x118,          // CAM_DATA_01
        0x140,          // CAM_DATA_02
        10,             // CAM_DATA_PITCHTARGET
        100,           // CAM_DATA_04
        100,            // CAM_DATA_05
        100,           // CAM_DATA_YAWDIFFRANGE
        60,             // CAM_DATA_FOV
        20,           // CAM_DATA_08
        (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL0        PUSHPULL    PARA1
 * NORMAL3        PUSHPULL    PARA1
 * NORMAL1        PUSHPULL    PARA1
 * NANAME         PUSHPULL    PARA1
 * TOWER0         PUSHPULL    PARA1
 * CLIMEMAZE      PUSHPULL    PARA1
 * KEEPBACK       PUSHPULL    PARA1
 * BOSS_TWINMOLD  PUSHPULL    PARA1
 * BOSS_GYORG     PUSHPULL    PARA1
 * PINNACLE_ROCK  PUSHPULL    PARA1
 * NORMAL2        PUSHPULL    PARA1
 * WHIRLPOOL      PUSHPULL    PARA1
 * CUCCO_SHACK    PUSHPULL    PARA1
 * GIANT          PUSHPULL    PARA1
 * WATER2         PUSHPULL    PARA1
 * FORCEKEEP      PUSHPULL    PARA1
 * PARALLEL1      PUSHPULL    PARA1
 * NORMAL4        PUSHPULL    PARA1
 */
CameraModeValue sSetNormal0ModePushPullData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting        Mode          Function
 * ------------   ----------   --------
 * NORMAL0        FOLLOWBOOMERANG    KEEP1
 * NORMAL3        FOLLOWBOOMERANG    KEEP1
 * FUKAN0         FOLLOWBOOMERANG    KEEP1
 * NORMAL1        FOLLOWBOOMERANG    KEEP1
 * NANAME         FOLLOWBOOMERANG    KEEP1
 * CIRCLE0        FOLLOWBOOMERANG    KEEP1
 * FIXED0         FOLLOWBOOMERANG    KEEP1
 * CIRCLE3        FOLLOWBOOMERANG    KEEP1
 * FIXED3         FOLLOWBOOMERANG    KEEP1
 * TOWER0         FOLLOWBOOMERANG    KEEP1
 * CLIMEMAZE      FOLLOWBOOMERANG    KEEP1
 * KEEPBACK       FOLLOWBOOMERANG    KEEP1
 * FUKAN1         FOLLOWBOOMERANG    KEEP1
 * CIRCLE9        FOLLOWBOOMERANG    KEEP1
 * INBUSH         FOLLOWBOOMERANG    KEEP1
 * BOSS_TWINMOLD  FOLLOWBOOMERANG    KEEP1
 * BOSS_GYORG     FOLLOWBOOMERANG    KEEP1
 * PINNACLE_ROCK  FOLLOWBOOMERANG    KEEP1
 * NORMAL2        FOLLOWBOOMERANG    KEEP1
 * WHIRLPOOL      FOLLOWBOOMERANG    KEEP1
 * CUCCO_SHACK    FOLLOWBOOMERANG    KEEP1
 * GIANT          FOLLOWBOOMERANG    KEEP1
 * WATER2         FOLLOWBOOMERANG    KEEP1
 * SOKONASI       FOLLOWBOOMERANG    KEEP1
 * FORCEKEEP      FOLLOWBOOMERANG    KEEP1
 * PARALLEL1      FOLLOWBOOMERANG    KEEP1
 * NORMAL4        FOLLOWBOOMERANG    KEEP1
 */
CameraModeValue sSetNormal0ModeFollowBoomerangData[] = {
    { -5, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 0x0005, CAM_DATA_13 },
    { 0x004B, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL0        DEKUSHOOT    SUBJ1
 * FUKAN0         DEKUSHOOT    SUBJ1
 * NORMAL1        DEKUSHOOT    SUBJ1
 * NANAME         DEKUSHOOT    SUBJ1
 * CIRCLE0        DEKUSHOOT    SUBJ1
 * FIXED0         DEKUSHOOT    SUBJ1
 * DUNGEON0       DEKUSHOOT    SUBJ1
 * DUNGEON1       DEKUSHOOT    SUBJ1
 * CIRCLE3        DEKUSHOOT    SUBJ1
 * FIXED3         DEKUSHOOT    SUBJ1
 * TOWER0         DEKUSHOOT    SUBJ1
 * CLIMEMAZE      DEKUSHOOT    SUBJ1
 * DUNGEON2       DEKUSHOOT    SUBJ1
 * BOSS_ODOLWA    DEKUSHOOT    SUBJ1
 * KEEPBACK       DEKUSHOOT    SUBJ1
 * MINIBOSS       DEKUSHOOT    SUBJ1
 * FUKAN1         DEKUSHOOT    SUBJ1
 * DUNGEON3       DEKUSHOOT    SUBJ1
 * ROOM0          DEKUSHOOT    SUBJ1
 * CIRCLE9        DEKUSHOOT    SUBJ1
 * ONTHEPOLE      DEKUSHOOT    SUBJ1
 * INBUSH         DEKUSHOOT    SUBJ1
 * BOSS_MAJORA    DEKUSHOOT    SUBJ1
 * BOSS_TWINMOLD  DEKUSHOOT    SUBJ1
 * BOSS_GOHT      DEKUSHOOT    SUBJ1
 * NORMAL2        DEKUSHOOT    SUBJ1
 * BOMBBOWL       DEKUSHOOT    SUBJ1
 * CUCCO_SHACK    DEKUSHOOT    SUBJ1
 * GIANT          DEKUSHOOT    SUBJ1
 * ROOM1          DEKUSHOOT    SUBJ1
 * SOKONASI       DEKUSHOOT    SUBJ1
 * FORCEKEEP      DEKUSHOOT    SUBJ1
 * PARALLEL1      DEKUSHOOT    SUBJ1
 * ROOM2          DEKUSHOOT    SUBJ1
 * NORMAL4        DEKUSHOOT    SUBJ1
 * DUNGEON4       DEKUSHOOT    SUBJ1
 */
CameraModeValue sSetNormal0ModeDekuShootData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 0x0005, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 50, CAM_DATA_17 },
    { 0x0041, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

CameraModeValue sSetNormal0ModeGoronDashData[] = {
    CAM_FUNCDATA_NORM1( // CAM_FUNC_NORM1
        50,            // CAM_DATA_YOFFSET
        0xA0,          // CAM_DATA_01
        0xFF,          // CAM_DATA_02
        0xFFFE,             // CAM_DATA_PITCHTARGET
        0xC,           // CAM_DATA_04
        10,            // CAM_DATA_05
        0x28,           // CAM_DATA_YAWDIFFRANGE
        92,             // CAM_DATA_FOV
        0x58,           // CAM_DATA_08
        (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL0        DEKUHIDE    PARA1
 * FUKAN0         DEKUHIDE    PARA1
 * NORMAL1        DEKUHIDE    PARA1
 * NANAME         DEKUHIDE    PARA1
 * DUNGEON0       DEKUHIDE    PARA1
 * DUNGEON1       DEKUHIDE    PARA1
 * TOWER0         DEKUHIDE    PARA1
 * CLIMEMAZE      DEKUHIDE    PARA1
 * DUNGEON2       DEKUHIDE    PARA1
 * BOSS_ODOLWA    DEKUHIDE    PARA1
 * KEEPBACK       DEKUHIDE    PARA1
 * MINIBOSS       DEKUHIDE    PARA1
 * FUKAN1         DEKUHIDE    PARA1
 * DUNGEON3       DEKUHIDE    PARA1
 * ONTHEPOLE      DEKUHIDE    PARA1
 * INBUSH         DEKUHIDE    PARA1
 * BOSS_MAJORA    DEKUHIDE    PARA1
 * BOSS_TWINMOLD  DEKUHIDE    PARA1
 * BOSS_GOHT      DEKUHIDE    PARA1
 * NORMAL2        DEKUHIDE    PARA1
 * GIANT          DEKUHIDE    PARA1
 * ROOM1          DEKUHIDE    PARA1
 * SOKONASI       DEKUHIDE    PARA1
 * FORCEKEEP      DEKUHIDE    PARA1
 * PARALLEL1      DEKUHIDE    PARA1
 * ROOM2          DEKUHIDE    PARA1
 * NORMAL4        DEKUHIDE    PARA1
 * DUNGEON4       DEKUHIDE    PARA1
 */
CameraModeValue sSetNormal0ModeDekuHideData[] = {
    { 100, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x22, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 20, CAM_DATA_12 },
};

/**
 * Setting        Mode       Function
 * ------------   -------    --------
 * NORMAL0        DEKUFLY    NORM1
 * FUKAN0         DEKUFLY    NORM1
 * NORMAL1        DEKUFLY    NORM1
 * NANAME         DEKUFLY    NORM1
 * DUNGEON0       DEKUFLY    NORM1
 * DUNGEON1       DEKUFLY    NORM1
 * TOWER0         DEKUFLY    NORM1
 * CLIMEMAZE      DEKUFLY    NORM1
 * DUNGEON2       DEKUFLY    NORM1
 * BOSS_ODOLWA    DEKUFLY    NORM1
 * KEEPBACK       DEKUFLY    NORM1
 * MINIBOSS       DEKUFLY    NORM1
 * FUKAN1         DEKUFLY    NORM1
 * DUNGEON3       DEKUFLY    NORM1
 * ONTHEPOLE      DEKUFLY    NORM1
 * INBUSH         DEKUFLY    NORM1
 * BOSS_MAJORA    DEKUFLY    NORM1
 * BOSS_TWINMOLD  DEKUFLY    NORM1
 * BOSS_GOHT      DEKUFLY    NORM1
 * NORMAL2        DEKUFLY    NORM1
 * GIANT          DEKUFLY    NORM1
 * ROOM1          DEKUFLY    NORM1
 * SOKONASI       DEKUFLY    NORM1
 * FORCEKEEP      DEKUFLY    NORM1
 * PARALLEL1      DEKUFLY    NORM1
 * ROOM2          DEKUFLY    NORM1
 * NORMAL4        DEKUFLY    NORM1
 * DUNGEON4       DEKUFLY    NORM1
 */
CameraModeValue sSetNormal0ModeDekuFlyData[] = {
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 80, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL0        DEKUFLYZ    PARA1
 * FUKAN0         DEKUFLYZ    PARA1
 * NORMAL1        DEKUFLYZ    PARA1
 * NANAME         DEKUFLYZ    PARA1
 * DUNGEON0       DEKUFLYZ    PARA1
 * DUNGEON1       DEKUFLYZ    PARA1
 * TOWER0         DEKUFLYZ    PARA1
 * CLIMEMAZE      DEKUFLYZ    PARA1
 * DUNGEON2       DEKUFLYZ    PARA1
 * BOSS_ODOLWA    DEKUFLYZ    PARA1
 * KEEPBACK       DEKUFLYZ    PARA1
 * MINIBOSS       DEKUFLYZ    PARA1
 * FUKAN1         DEKUFLYZ    PARA1
 * DUNGEON3       DEKUFLYZ    PARA1
 * ONTHEPOLE      DEKUFLYZ    PARA1
 * INBUSH         DEKUFLYZ    PARA1
 * BOSS_MAJORA    DEKUFLYZ    PARA1
 * BOSS_TWINMOLD  DEKUFLYZ    PARA1
 * BOSS_GOHT      DEKUFLYZ    PARA1
 * NORMAL2        DEKUFLYZ    PARA1
 * GIANT          DEKUFLYZ    PARA1
 * ROOM1          DEKUFLYZ    PARA1
 * SOKONASI       DEKUFLYZ    PARA1
 * FORCEKEEP      DEKUFLYZ    PARA1
 * PARALLEL1      DEKUFLYZ    PARA1
 * ROOM2          DEKUFLYZ    PARA1
 * NORMAL4        DEKUFLYZ    PARA1
 * DUNGEON4       DEKUFLYZ    PARA1
 */
CameraModeValue sSetNormal0ModeDekuFlyZData[] = {
    { 0xFFBA, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 10, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 90, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x0E, CAM_DATA_FLAGS },
    { 90, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting     Mode         Function
 * --------    ---------    --------
 * NORMAL0     GORONJUMP    NORM1
 * DUNGEON0    GORONJUMP    NORM1
 */
CameraModeValue sSetNormal0ModeGoronJumpData[] = {
    { -10, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 80, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting        Mode       Function
 * ------------   -------    --------
 * NORMAL0        ZORAFIN    SUBJ1
 * NORMAL3        ZORAFIN    SUBJ1
 * FUKAN0         ZORAFIN    SUBJ1
 * NORMAL1        ZORAFIN    SUBJ1
 * NANAME         ZORAFIN    SUBJ1
 * CIRCLE0        ZORAFIN    SUBJ1
 * FIXED0         ZORAFIN    SUBJ1
 * DUNGEON0       ZORAFIN    SUBJ1
 * DUNGEON1       ZORAFIN    SUBJ1
 * CIRCLE3        ZORAFIN    SUBJ1
 * FIXED3         ZORAFIN    SUBJ1
 * TOWER0         ZORAFIN    SUBJ1
 * CLIMEMAZE      ZORAFIN    SUBJ1
 * DUNGEON2       ZORAFIN    SUBJ1
 * BOSS_ODOLWA    ZORAFIN    SUBJ1
 * KEEPBACK       ZORAFIN    SUBJ1
 * MINIBOSS       ZORAFIN    SUBJ1
 * FUKAN1         ZORAFIN    SUBJ1
 * DUNGEON3       ZORAFIN    SUBJ1
 * ROOM0          ZORAFIN    SUBJ1
 * CIRCLE9        ZORAFIN    SUBJ1
 * ONTHEPOLE      ZORAFIN    SUBJ1
 * INBUSH         ZORAFIN    SUBJ1
 * BOSS_MAJORA    ZORAFIN    SUBJ1
 * BOSS_TWINMOLD  ZORAFIN    SUBJ1
 * BOSS_GOHT      ZORAFIN    SUBJ1
 * BOSS_GYORG     ZORAFIN    SUBJ1
 * PINNACLE_ROCK  ZORAFIN    SUBJ1
 * NORMAL2        ZORAFIN    SUBJ1
 * BOMBBOWL       ZORAFIN    SUBJ1
 * WHIRLPOOL      ZORAFIN    SUBJ1
 * CUCCO_SHACK    ZORAFIN    SUBJ1
 * GIANT          ZORAFIN    SUBJ1
 * ROOM1          ZORAFIN    SUBJ1
 * WATER2         ZORAFIN    SUBJ1
 * SOKONASI       ZORAFIN    SUBJ1
 * FORCEKEEP      ZORAFIN    SUBJ1
 * PARALLEL1      ZORAFIN    SUBJ1
 * ROOM2          ZORAFIN    SUBJ1
 * NORMAL4        ZORAFIN    SUBJ1
 * DUNGEON4       ZORAFIN    SUBJ1
 */
CameraModeValue sSetNormal0ModeZoraFinData[] = {
    { 0x0005, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
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
CameraModeValue sSetNormal3ModeNormalData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 100, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x84, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL3    TARGET    PARA1
 */
CameraModeValue sSetNormal3ModeTargetData[] = {
    { -50, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0028, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 100, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x03, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting        Mode        Function
 * ------------   --------    --------
 * NORMAL3        FREEFALL    JUMP3
 * BOSS_GYORG     FREEFALL    JUMP3
 * PINNACLE_ROCK  FREEFALL    JUMP3
 * WATER2         FREEFALL    JUMP3
 */
CameraModeValue sSetNormal3ModeFreeFallData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 80, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 10, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 80, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x4, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * NORMAL3    GORONJUMP    JUMP3
 * WATER2     GORONJUMP    JUMP3
 */
CameraModeValue sSetNormal3ModeGoronJumpData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xC, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * NORMAL3    DEKUFLY    JUMP3
 * WATER2     DEKUFLY    JUMP3
 */
CameraModeValue sSetNormal3ModeDekuFlyData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x5, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * NORMAL3    DEKUHIDE    JUMP3
 * WATER2     DEKUHIDE    JUMP3
 */
CameraModeValue sSetNormal3ModeDekuHideData[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { -15, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x85, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * NORMAL3    STILL    NORM1
 * WATER2     STILL    NORM1
 */
CameraModeValue sSetNormal3ModeStillData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 80, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting     Mode         Function
 * --------    ---------    --------
 * NORMAL3     GORONDASH    JUMP3
 * BOSS_GYORG  GORONDASH    JUMP3
 */
CameraModeValue sSetNormal3ModeGoronDashData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 80, CAM_DATA_FOV },
    { 0x0023, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xC, CAM_DATA_FLAGS },
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
CameraModeValue sSetPivotDivingModeNormalData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 60, 1 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * CIRCLE5    TARGET    UNIQ2
 */
CameraModeValue sSetPivotDivingModeTargetData[] = {
    { -30, CAM_DATA_YOFFSET },
    { 0x002D, 1 },
    { 100, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
};

/*=====================================================================
 *                   Custom Data: HORSE Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * HORSE      NORMAL    NORM3
 */
CameraModeValue sSetHorseModeNormalData[] = {
    { -50, CAM_DATA_YOFFSET },    // yOffset
    { 220, CAM_DATA_01 },    // distMin
    { 250, CAM_DATA_02 },    // distMax
    { 10, CAM_DATA_PITCHTARGET },     // yawUpdateRateInv
    { 10, CAM_DATA_04 },     // pitchUpdateRateInv
    { 20, CAM_DATA_05 },     // fovTarget
    { 60, CAM_DATA_FOV },     // maxAtLERPScale
    { 80, CAM_DATA_08 },     // pitchTarget
    { SHRINKWINVAL_NONE | IFACE_ALPHA(6) | NORM3_FLG_20, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * HORSE      TARGET    NORM3
 */
CameraModeValue sSetHorseModeTargetData[] = {
    { -40, CAM_DATA_YOFFSET },    // yOffset
    { 180, CAM_DATA_01 },    // distMin
    { 200, CAM_DATA_02 },    // distMax
    { -3, CAM_DATA_PITCHTARGET },     // yawUpdateRateInv
    { 2, CAM_DATA_04 },      // pitchUpdateRateInv
    { 100, CAM_DATA_05 },    // fovTarget
    { 50, CAM_DATA_FOV },     // maxAtLERPScale
    { 90, CAM_DATA_08 },     // pitchTarget
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(6) | NORM3_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * HORSE      JUMP    NORM3
 */
CameraModeValue sSetHorseModeJumpData[] = {
    { -50, CAM_DATA_YOFFSET },    // yOffset
    { 220, CAM_DATA_01 },    // distMin
    { 260, CAM_DATA_02 },    // distMax
    { 10, CAM_DATA_PITCHTARGET },     // yawUpdateRateInv
    { 10, CAM_DATA_04 },     // pitchUpdateRateInv
    { 20, CAM_DATA_05 },     // fovTarget
    { 60, CAM_DATA_FOV },     // maxAtLERPScale
    { 50, CAM_DATA_08 },     // pitchTarge
    { SHRINKWINVAL_NONE | IFACE_ALPHA(6), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * HORSE      BOWARROW    SUBJ1
 */
CameraModeValue sSetHorseModeBowArrowData[] = {
    { 0xFFF9, CAM_DATA_YOFFSET },
    { 0x000E, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { -30, CAM_DATA_17 },
    { -5, CAM_DATA_18 },
    { 40, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(6), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * HORSE      SLINGSHOT    SUBJ1
 */
CameraModeValue sSetHorseModeSlingShotData[] = {
    { 0xFFF9, CAM_DATA_YOFFSET },
    { 0x000E, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { -50, CAM_DATA_17 },
    { -10, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * HORSE      BATTLE    BATT1
 */
CameraModeValue sSetHorseModeBattleData[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 60, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 20, CAM_DATA_16 },
    { 60, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode            Function
 * -------    ------------    --------
 * HORSE      FOLLOWTARGET    KEEP1
 */
CameraModeValue sSetHorseModeFollowTargetData[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 0x0019, CAM_DATA_13 },
    { 0x002D, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 0x000F, CAM_DATA_16 },
    { 0x000F, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(6) | 0x1, CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * HORSE      TALK    KEEP3
 */
CameraModeValue sSetHorseModeTalkData[] = {
    { -50, CAM_DATA_YOFFSET },
    { 0x008C, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 0x0028, CAM_DATA_13 },
    { 10, CAM_DATA_14 },
    { 0, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 100, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5), CAM_DATA_FLAGS },
    { 60, CAM_DATA_18 },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * HORSE      STILL    NORM3
 */
CameraModeValue sSetHorseModeStillData[] = {
    { -40, CAM_DATA_YOFFSET },    // yOffset
    { 180, CAM_DATA_01 },    // distMin
    { 200, CAM_DATA_02 },    // distMax
    { -3, CAM_DATA_PITCHTARGET },     // yawUpdateRateInv
    { 100, CAM_DATA_04 },    // pitchUpdateRateInv
    { 100, CAM_DATA_05 },    // fovTarget
    { 60, CAM_DATA_FOV },     // maxAtLERPScale
    { 10, CAM_DATA_08 },     // pitchTarget
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | NORM3_FLG_80, CAM_DATA_FLAGS },
};

/*=====================================================================
 *                   Custom Data: ZORA Setting
 *=====================================================================
 */

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * ZORA       NORMAL    NORM3
 */
CameraModeValue D_801B4EB4[] = {
    { -20, CAM_DATA_YOFFSET },    // yOffset
    { 250, CAM_DATA_01 },    // distMin
    { 250, CAM_DATA_02 },    // distMax
    { 0, CAM_DATA_PITCHTARGET },      // yawUpdateRateInv
    { 20, CAM_DATA_04 },     // pitchUpdateRateInv
    { 20, CAM_DATA_05 },     // fovTarget
    { 60, CAM_DATA_FOV },     // maxAtLERPScale
    { 50, CAM_DATA_08 },     // pitchTarget
    { SHRINKWINVAL_NONE | IFACE_ALPHA(6) | NORM3_FLG_80, CAM_DATA_FLAGS },
};

/*=====================================================================
 *                   Custom Data: PREREND_FIXED Setting
 *=====================================================================
 */

/**
 * Setting          Mode      Function
 * -------------    ------    --------
 * PREREND_FIXED    NORMAL    FIXD3
 */
CameraModeValue sSetPrerendFixedModeNormalData[] = {
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/*=====================================================================
 *                   Custom Data: PREREND_PIVOT Setting
 *=====================================================================
 */

/**
 * Setting          Mode      Function
 * -------------    ------    --------
 * PREREND_PIVOT    NORMAL    UNIQ7
 */
CameraModeValue sSetPrerendPivotModeNormalData[] = {
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
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
    { -5, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE_4 | IFACE_ALPHA(2) | 0x2, CAM_DATA_FLAGS },
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
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(2), CAM_DATA_FLAGS },
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
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x0258, CAM_DATA_01 },
    { 0x0258, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 50, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 45, CAM_DATA_FOV },
    { 90, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_40 | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * FUKAN0     TARGET    PARA1
 * FUKAN1     TARGET    PARA1
 */
CameraModeValue D_801B4F20[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 0x0019, CAM_DATA_02 },
    { 60, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * FUKAN0     JUMP    NORM1
 * FUKAN1     JUMP    NORM1
 */
CameraModeValue D_801B4F50[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0258, CAM_DATA_01 },
    { 0x0258, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 50, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * FUKAN0     STILL    NORM1
 */
CameraModeValue D_801B4F78[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0258, CAM_DATA_01 },
    { 0x0258, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 45, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
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
CameraModeValue sSetNormal1ModeNormalData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0046, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * NORMAL1    STILL    NORM1
 */
CameraModeValue sSetNormal1ModeStillData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
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
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x3, CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode            Function
 * -------    ------------    --------
 * CIRCLE0    FOLLOWTARGET    FIXD2
 * CIRCLE3    FOLLOWTARGET    FIXD2
 * CIRCLE9    FOLLOWTARGET    FIXD2
 */
CameraModeValue D_801B5034[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 80, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x40, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * CIRCLE0    TALK    FIXD2
 * CIRCLE3    TALK    FIXD2
 * CIRCLE9    TALK    FIXD2
 */
CameraModeValue D_801B5050[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 50, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x80, CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 10, CAM_DATA_04 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },    // yOffset
    { 50, CAM_DATA_04 },     // eyeStepScale
    { 80, CAM_DATA_05 },     // posStepScale
    { 60, CAM_DATA_FOV },     // fov
    { 10, CAM_DATA_12 },     // maxDoorCutsceneCounter
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
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
CameraModeValue sSetDungeon0ModeNormalData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x002D, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * DUNGEON0      TARGET    PARA1
 * DUNGEON1      TARGET    PARA1
 * DUNGEON2      TARGET    PARA1
 * BOSS_ODOLWA   TARGET    PARA1
 * MINIBOSS      TARGET    PARA1
 * BOSS_MAJORA   TARGET    PARA1
 * ROOM1         TARGET    PARA1
 * ROOM2         TARGET    PARA1
 */
CameraModeValue sSetDungeon0ModeTargetData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0019, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x42, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
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
CameraModeValue sSetDungeon0ModeFollowTargetData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 0x008C, CAM_DATA_02 },
    { 0x0019, CAM_DATA_13 },
    { 0x002D, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 0x000F, CAM_DATA_16 },
    { 0x000F, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
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
CameraModeValue sSetDungeon0ModeBattleData[] = {
    { -30, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 50, CAM_DATA_14 },
    { 0x0005, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x0019, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting       Mode          Function
 * ----------    ----------    --------
 * DUNGEON0      FOLLOWBOOMERANG    KEEP1
 * DUNGEON1      FOLLOWBOOMERANG    KEEP1
 * DUNGEON2      FOLLOWBOOMERANG    KEEP1
 * BOSS_ODOLWA   FOLLOWBOOMERANG    KEEP1
 * MINIBOSS      FOLLOWBOOMERANG    KEEP1
 * DUNGEON3      FOLLOWBOOMERANG    KEEP1
 * ONTHEPOLE     FOLLOWBOOMERANG    KEEP1
 * BOSS_MAJORA   FOLLOWBOOMERANG    KEEP1
 * BOSS_GOHT     FOLLOWBOOMERANG    KEEP1
 * DUNGEON4      FOLLOWBOOMERANG    KEEP1
 */
CameraModeValue sSetDungeon0ModeFollowBoomerangData[] = {
    { -5, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 0x0005, CAM_DATA_13 },
    { 0x0041, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 55, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting     Mode    Function
 * --------    ----    --------
 * DUNGEON0    JUMP    NORM1
 */
CameraModeValue sSetDungeon0ModeJumpData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0x0018, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting       Mode        Function
 * ----------    --------    --------
 * DUNGEON0      FREEFALL    PARA1
 * DUNGEON1      FREEFALL    PARA1
 * DUNGEON2      FREEFALL    PARA1
 * BOSS_ODOLWA   FREEFALL    PARA1
 * MINIBOSS      FREEFALL    PARA1
 * DUNGEON3      FREEFALL    PARA1
 * ONTHEPOLE     FREEFALL    PARA1
 * BOSS_MAJORA   FREEFALL    PARA1
 * BOSS_GOHT     FREEFALL    PARA1
 * ROOM1         FREEFALL    PARA1
 * ROOM2         FREEFALL    PARA1
 * DUNGEON4      FREEFALL    PARA1
 */
CameraModeValue sSetDungeon0ModeFreeFallData[] = {
    { -10, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 10, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x88, CAM_DATA_FLAGS },
    { 0x0046, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting       Mode     Function
 * ----------    -----    --------
 * DUNGEON0      CLIMB    JUMP2
 * DUNGEON1      CLIMB    JUMP2
 * DUNGEON2      CLIMB    JUMP2
 * BOSS_ODOLWA   CLIMB    JUMP2
 * MINIBOSS      CLIMB    JUMP2
 * DUNGEON3      CLIMB    JUMP2
 * BOSS_MAJORA   CLIMB    JUMP2
 * BOSS_GOHT     CLIMB    JUMP2
 * ROOM1         CLIMB    JUMP2
 * SOKONASI      CLIMB    JUMP2
 * ROOM2         CLIMB    JUMP2
 * DUNGEON4      CLIMB    JUMP2
 */
CameraModeValue sSetDungeon0ModeClimbData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * DUNGEON0      CLIMBZ    JUMP2
 * DUNGEON1      CLIMBZ    JUMP2
 * DUNGEON2      CLIMBZ    JUMP2
 * BOSS_ODOLWA   CLIMBZ    JUMP2
 * MINIBOSS      CLIMBZ    JUMP2
 * DUNGEON3      CLIMBZ    JUMP2
 * BOSS_MAJORA   CLIMBZ    JUMP2
 * BOSS_GOHT     CLIMBZ    JUMP2
 * ROOM1         CLIMBZ    JUMP2
 * SOKONASI      CLIMBZ    JUMP2
 * ROOM2         CLIMBZ    JUMP2
 * DUNGEON4      CLIMBZ    JUMP2
 */
CameraModeValue sSetDungeon0ModeClimbZData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x03E7, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x4 | 0x2, CAM_DATA_FLAGS },
};

/**
 * Setting       Mode      Function
 * ----------    ------    --------
 * DUNGEON0      CHARGE    PARA1
 * DUNGEON1      CHARGE    PARA1
 * DUNGEON2      CHARGE    PARA1
 * BOSS_ODOLWA   CHARGE    PARA1
 * MINIBOSS      CHARGE    PARA1
 * DUNGEON3      CHARGE    PARA1
 * ONTHEPOLE     CHARGE    PARA1
 * BOSS_MAJORA   CHARGE    PARA1
 * BOSS_GOHT     CHARGE    PARA1
 * ROOM1         CHARGE    PARA1
 * ROOM2         CHARGE    PARA1
 * DUNGEON4      CHARGE    PARA1
 */
CameraModeValue sSetDungeon0ModeChargeData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 50, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting     Mode       Function
 * --------    -------    --------
 * DUNGEON0    CHARGEZ    PARA1
 */
CameraModeValue sSetDungeon0ModeChargeZData[] = {
    { 50, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 50, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting       Mode    Function
 * ----------    ----    --------
 * DUNGEON0      HANG    PARA1
 * DUNGEON1      HANG    PARA1
 * DUNGEON2      HANG    PARA1
 * BOSS_ODOLWA   HANG    PARA1
 * MINIBOSS      HANG    PARA1
 * DUNGEON3      HANG    PARA1
 * BOSS_MAJORA   HANG    PARA1
 * BOSS_GOHT     HANG    PARA1
 * ROOM1         HANG    PARA1
 * ROOM2         HANG    PARA1
 * DUNGEON4      HANG    PARA1
 */
CameraModeValue sSetDungeon0ModeHangData[] = {
    { -40, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 10, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting       Mode     Function
 * ----------    -----    --------
 * DUNGEON0      HANGZ    PARA1
 * DUNGEON1      HANGZ    PARA1
 * DUNGEON2      HANGZ    PARA1
 * BOSS_ODOLWA   HANGZ    PARA1
 * MINIBOSS      HANGZ    PARA1
 * DUNGEON3      HANGZ    PARA1
 * BOSS_MAJORA   HANGZ    PARA1
 * BOSS_GOHT     HANGZ    PARA1
 * ROOM1         HANGZ    PARA1
 * ROOM2         HANGZ    PARA1
 * DUNGEON4      HANGZ    PARA1
 */
CameraModeValue sSetDungeon0ModeHangZData[] = {
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 10, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 10, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x0002, CAM_DATA_12 },
};

/**
 * Setting     Mode     Function
 * --------    -----    --------
 * DUNGEON0    STILL    NORM1
 */
CameraModeValue sSetDungeon0ModeStillData[] = {
    { -10, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 10, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting       Mode        Function
 * ----------    --------    --------
 * DUNGEON0      PUSHPULL    PARA1
 * BOSS_ODOLWA   PUSHPULL    PARA1
 * MINIBOSS      PUSHPULL    PARA1
 * BOSS_MAJORA   PUSHPULL    PARA1
 * BOSS_GOHT     PUSHPULL    PARA1
 * DUNGEON4      PUSHPULL    PARA1
 */
CameraModeValue sSetDungeon0ModePushPullData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
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
    { 0x0005, CAM_DATA_YOFFSET },
    { 0x0046, CAM_DATA_01 },
    { 0x0019, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM0      JUMP    KEEP4
 */
CameraModeValue D_801B535C[] = {
    { -30, CAM_DATA_YOFFSET },
    { 0x0023, CAM_DATA_01 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0006, CAM_DATA_18 },
    { 80, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM0      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5380[] = {
    { -15, CAM_DATA_YOFFSET },
    { 90, CAM_DATA_01 },
    { -8, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM0      GORONDASH    KEEP4
 */
CameraModeValue D_801B53A4[] = {
    { 20, CAM_DATA_YOFFSET },
    { 0x002D, CAM_DATA_01 },
    { 0x0037, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000C, CAM_DATA_18 },
    { 55, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM0      DEKUFLY    KEEP4
 */
CameraModeValue D_801B53C8[] = {
    { 10, CAM_DATA_YOFFSET },
    { 0x0046, CAM_DATA_01 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_18 },
    { 0x002A, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
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
    { -45, CAM_DATA_YOFFSET },
    { 0x004B, CAM_DATA_01 },
    { 0xFFF4, CAM_DATA_PITCHTARGET },
    { 0x00A5, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM1      JUMP    KEEP4
 */
CameraModeValue D_801B5410[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x0046, CAM_DATA_01 },
    { 20, CAM_DATA_PITCHTARGET },
    { 0x008C, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM1      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5434[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0055, CAM_DATA_01 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x008C, CAM_DATA_10 },
    { 0x000F, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM1      GORONDASH    KEEP4
 */
CameraModeValue D_801B5458[] = {
    { -50, CAM_DATA_YOFFSET },
    { 0x005F, CAM_DATA_01 },
    { -15, CAM_DATA_PITCHTARGET },
    { 0x00A0, CAM_DATA_10 },
    { 0x0006, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM1      DEKUFLY    KEEP4
 */
CameraModeValue D_801B547C[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0046, CAM_DATA_01 },
    { -15, CAM_DATA_PITCHTARGET },
    { 0xFF74, CAM_DATA_10 },
    { 30, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x0C, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x006E, CAM_DATA_01 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0x0096, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x0041, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM2      JUMP    KEEP4
 */
CameraModeValue D_801B54C4[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0082, CAM_DATA_01 },
    { -10, CAM_DATA_PITCHTARGET },
    { 0x00AA, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x0041, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM2      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B54E8[] = {
    { -40, CAM_DATA_YOFFSET },
    { 0x006E, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x008C, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x0041, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM2      GORONDASH    KEEP4
 */
CameraModeValue D_801B550C[] = {
    { -50, CAM_DATA_YOFFSET },
    { 0x008C, CAM_DATA_01 },
    { -10, CAM_DATA_PITCHTARGET },
    { 0x00A0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM2      DEKUFLY    KEEP4
 */
CameraModeValue D_801B5530[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { -8, CAM_DATA_PITCHTARGET },
    { 0x0096, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
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
    { -15, CAM_DATA_YOFFSET },
    { 0x0041, CAM_DATA_01 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0xFF65, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x004B, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0xC, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * ITEM3      JUMP    KEEP4
 */
CameraModeValue D_801B5578[] = {
    { -20, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_01 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0xFF65, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x004B, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0xC, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * ITEM3      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B559C[] = {
    { -15, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_01 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0x00AA, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x004B, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * ITEM3      GORONDASH    KEEP4
 */
CameraModeValue D_801B55C0[] = {
    { -25, CAM_DATA_YOFFSET },
    { 0x005F, CAM_DATA_01 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0xFF65, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 0x004B, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0xC, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * ITEM3      DEKUFLY    KEEP4
 */
CameraModeValue D_801B55E4[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x004B, CAM_DATA_01 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 0xFF6A, CAM_DATA_10 },
    { -5, CAM_DATA_18 },
    { 0x004B, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0xC, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 0x0006, CAM_DATA_12 },
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
    { -45, CAM_DATA_YOFFSET },
    { 0x00A5, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x00B2, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4E, CAM_DATA_FLAGS },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * WARP0      JUMP    KEEP4
 */
CameraModeValue D_801B562C[] = {
    { 0xFFC9, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x00B2, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4E, CAM_DATA_FLAGS },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * WARP0      NUTSSHOT    KEEP4
 */
CameraModeValue D_801B5650[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x00AF, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x00B2, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4E, CAM_DATA_FLAGS },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * WARP0      GORONDASH    KEEP4
 */
CameraModeValue D_801B5674[] = {

    { -50, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x00B2, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4E, CAM_DATA_FLAGS },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting    Mode       Function
 * -------    -------    --------
 * WARP0      DEKUFLY    KEEP4
 */
CameraModeValue D_801B5698[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x00B2, CAM_DATA_10 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4E, CAM_DATA_FLAGS },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_12 },
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
CameraModeValue sSetDeathModeNormalData[] = {
    { 0xFFBA, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 10, CAM_DATA_18 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
    { 0x0005, CAM_DATA_04 },
    { 100, CAM_DATA_12 },
};

/**
 * Setting    Mode         Function
 * -------    ---------    --------
 * DEATH      JUMP         KEEP4
 * DEATH      GORONDASH    KEEP4
 * DEATH      DEKUFLY      KEEP4
 */
CameraModeValue sSetDeathModeJumpData[] = {
    { 0xFFBA, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
    { 0x0005, CAM_DATA_04 },
    { 100, CAM_DATA_12 },
};

/**
 * Setting    Mode        Function
 * -------    --------    --------
 * DEATH      NUTSSHOT    KEEP4
 */
CameraModeValue sSetDeathModeDekuShootData[] = {
    { 0xFFBA, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
    { 0x0005, CAM_DATA_04 },
    { 100, CAM_DATA_12 },
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
 * REBIRTH    DEKUFLY      KEEP4
 */
CameraModeValue D_801B5728[] = {
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0x00A0, CAM_DATA_10 },
    { 10, CAM_DATA_18 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4 | 0x2, CAM_DATA_FLAGS },
    { 0x0005, CAM_DATA_04 },
    { 100, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * REBIRTH    NUTSSHOT    KEEP4
 */
CameraModeValue D_801B574C[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x008C, CAM_DATA_01 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0x00A0, CAM_DATA_10 },
    { 10, CAM_DATA_18 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x4 | 0x2, CAM_DATA_FLAGS },
    { 0x0005, CAM_DATA_04 },
    { 100, CAM_DATA_12 },
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
    { 60, CAM_DATA_FOV },     // fov
    { 30, CAM_DATA_08 },     // unk_04
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
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
CameraModeValue sSetDungeon1ModeNormalData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 50, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 0x0046, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting     Mode    Function
 * --------    ----    --------
 * DUNGEON1    JUMP    NORM1
 */
CameraModeValue sSetDungeon1ModeJumpData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 50, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting     Mode     Function
 * --------    -----    --------
 * DUNGEON1    STILL    NORM1
 */
CameraModeValue sSetDungeon1ModeStillData[] = {
    { -20, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting      Mode        Function
 * ---------    --------    --------
 * DUNGEON1     PUSHPULL    PARA1
 * ONTHEPOLL    PUSHPULL    PARA1
 */
CameraModeValue sSetDungeon1ModePushPullData[] = {
    { 0, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
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
    { -40, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_04 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 10, CAM_DATA_04 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
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
    { 0xFFDD, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_02 },
    { 0x0041, CAM_DATA_01 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0002, CAM_DATA_04 },
    { 70, CAM_DATA_FOV },
    { 0x0063, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
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
    { 20, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0320, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0x0006, CAM_DATA_04 },
    { 70, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x1, CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 80, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 80, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x9, CAM_DATA_FLAGS },
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
    { -40, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_04 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
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
    { 0, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 20, CAM_DATA_21 },
    { 20, CAM_DATA_04 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM0_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode    Function
 * -------    ----    --------
 * TOWER0    JUMP    NORM1
 */
CameraModeValue D_801B5928[] = {
    { -20, CAM_DATA_YOFFSET },
    { 0x0154, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode     Function
 * -------    -----    --------
 * TOWER0     STILL    NORM1
 */
CameraModeValue D_801B5950[] = {
    { 0, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
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
    { 0, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 20, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 20, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x8 | 0x2, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
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
    { 0, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 0x01F4, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0023, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
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
    { 0, CAM_DATA_YOFFSET },
    { 0x0005, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 10, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF), CAM_DATA_FLAGS },
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
    { 0, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_04 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
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
    { 0, CAM_DATA_YOFFSET },
    { 30, CAM_DATA_04 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x11, CAM_DATA_FLAGS },
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
    { 20, CAM_DATA_YOFFSET },
    { 90, CAM_DATA_01 },
    { 80, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 50, CAM_DATA_17 },
    { 0xFF38, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
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
    { 0, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0046, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5A64[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 10, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0xFFA6, CAM_DATA_10 },
    { 20, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2E, CAM_DATA_FLAGS },
    { 0x0046, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon2ModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 270, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 0x001C, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 0x0041, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon2ModeBattleData[] = {
    /* CAM_FUNC_BATT1 */
    { -40, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 50, CAM_DATA_13 },
    { 20, CAM_DATA_14 },
    { 0x0005, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 20, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon2ModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 270, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 50, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon2ModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 270, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon2ModePushPullData[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossOdolwaModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0x0018, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossOdolwaModeFollowTargetData[] = {
    /* CAM_FUNC_KEEP1 */
    { -50, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 20, CAM_DATA_14 },
    { 0x0005, CAM_DATA_15 },
    { 0x000C, CAM_DATA_16 },
    { 0x0046, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossOdolwaModeTalkData[] = {
    /* CAM_FUNC_KEEP3 */
    { -20, CAM_DATA_YOFFSET },
    { 230, CAM_DATA_01 },
    { 260, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 10, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 0x000F, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 55, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | 0x20, CAM_DATA_FLAGS },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossOdolwaModeBattleData[] = {
    /* CAM_FUNC_BATT1 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 10, CAM_DATA_14 },
    { 0, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 60, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 10, CAM_DATA_11 },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossOdolwaModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossOdolwaModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 0x000F, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5C80[] = {
    /* CAM_FUNC_PARA1 */
    { 100, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 20, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5CB0[] = {
    /* CAM_FUNC_FIXD2 */
    { -40, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x3, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5CCC[] = {
    /* CAM_FUNC_FIXD2 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x20, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5CE8[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 0x0011, CAM_DATA_PITCHTARGET },
    { 0x000E, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0041, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 0x004B, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D10[] = {
    /* CAM_FUNC_KEEP1 */
    { 0, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0019, CAM_DATA_13 },
    { 0x002D, CAM_DATA_14 },
    { 0x0028, CAM_DATA_15 },
    { 0x000F, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D40[] = {
    /* CAM_FUNC_BATT1 */
    { -25, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D74[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 0x0010, CAM_DATA_PITCHTARGET },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5D9C[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 0x0010, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5DC4[] = {
    /* CAM_FUNC_FIXD1 */
    { -40, CAM_DATA_YOFFSET },
    { 10, CAM_DATA_04 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x10, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5DD4[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 80, CAM_DATA_01 },
    { 0x0078, CAM_DATA_02 },
    { -10, CAM_DATA_PITCHTARGET },
    { 0x000F, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5DFC[] = {
    /* CAM_FUNC_PARA1 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0226, CAM_DATA_01 },
    { 0, CAM_DATA_02 },
    { 0x0041, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x004B, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x42, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E2C[] = {
    /* CAM_FUNC_FIXD2 */
    { 0x0046, CAM_DATA_YOFFSET },
    { 50, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 30, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E48[] = {
    /* CAM_FUNC_FIXD2 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x8, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E64[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0320, CAM_DATA_01 },
    { 0x0320, CAM_DATA_02 },
    { 60, CAM_DATA_PITCHTARGET },
    { 50, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 45, CAM_DATA_FOV },
    { 90, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_40 | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B5E8C[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0320, CAM_DATA_01 },
    { 0x0320, CAM_DATA_02 },
    { 60, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 45, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon3ModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { -30, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon3ModeTargetData[] = {
    /* CAM_FUNC_PARA1 */
    { -30, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 20, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x42, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon3ModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -30, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 0x00BE, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon3ModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 0x00AA, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon3ModePushPullData[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetTelescopeModeNormalData[] = {
    /* CAM_FUNC_SUBJ1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0005, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 30, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(2), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetTelescopeModeTargetData[] = {
    /* CAM_FUNC_SUBJ1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0005, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 0x000F, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(2), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetTelescopeModeFirstPersonData[] = {
    /* CAM_FUNC_SUBJ1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0005, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 30, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(2) | 0x10, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetTelescopeModeDekuHideData[] = {
    /* CAM_FUNC_SUBJ1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0005, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0001, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 0, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(2) | 0x10, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B601C[] = {
    /* CAM_FUNC_NORM1 */
    { 0xFFDD, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0x0011, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0023, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6044[] = {
    /* CAM_FUNC_PARA1 */
    { -10, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x52, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6074[] = {
    /* CAM_FUNC_KEEP1 */
    { -30, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 30, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B60A4[] = {
    /* CAM_FUNC_KEEP3 */
    { -20, CAM_DATA_YOFFSET },
    { 50, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 50, CAM_DATA_13 },
    { 0x0005, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 35, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | 0x20, CAM_DATA_FLAGS },
    { 60, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B60D8[] = {
    /* CAM_FUNC_BATT1 */
    { -25, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 0x008C, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { 0xFFFE, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x0019, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B610C[] = {
    /* CAM_FUNC_JUMP2 */
    { -20, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0041, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6130[] = {
    /* CAM_FUNC_JUMP2 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x03E7, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x4 | 0x2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6154[] = {
    /* CAM_FUNC_NORM1 */
    { -30, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 80, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B617C[] = {
    /* CAM_FUNC_PARA1 */
    { -40, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0008, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B61AC[] = {
    /* CAM_FUNC_PARA1 */
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 0x00F0, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0x0002, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B61DC[] = {
    /* CAM_FUNC_PARA1 */
    { -10, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x88, CAM_DATA_FLAGS },
    { 0x0041, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B620C[] = {
    /* CAM_FUNC_PARA1 */
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 0x00F0, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 50, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
    { 0x0041, CAM_DATA_11 },
    { 10, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B623C[] = {
    /* CAM_FUNC_PARA1 */
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 0x00F0, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 50, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0041, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B626C[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6294[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 0x002D, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x32, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B62C4[] = {
    /* CAM_FUNC_KEEP1 */
    { -5, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 0x008C, CAM_DATA_02 },
    { 0x0005, CAM_DATA_13 },
    { 0x0055, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 0x0019, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B62F4[] = {
    /* CAM_FUNC_NORM1 */
    { 50, CAM_DATA_YOFFSET },
    { 0x008C, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x000C, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 90, CAM_DATA_FOV },
    { 90, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B631C[] = {
    /* CAM_FUNC_PARA1 */
    { 100, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { -20, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0004, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 80, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x22, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 20, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B634C[] = {
    /* CAM_FUNC_NORM1 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 80, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6374[] = {
    /* CAM_FUNC_PARA1 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 20, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 90, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0xE, CAM_DATA_FLAGS },
    { 90, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B63A4[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 80, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B63CC[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B63FC[] = {
    /* CAM_FUNC_FIXD2 */
    { -10, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x18, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6418[] = {
    /* CAM_FUNC_FIXD2 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0028, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 0x0005, CAM_DATA_04 },
    { 0x0019, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x5, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6434[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_01 },
    { 0x0258, CAM_DATA_02 },
    { 0x0023, CAM_DATA_PITCHTARGET },
    { 0x0028, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 45, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B645C[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 0x0023, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x42, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B648C[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 0x0140, CAM_DATA_01 },
    { 0x017C, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0x0016, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 0x0020, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B64B4[] = {
    /* CAM_FUNC_JUMP2 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B64D8[] = {
    /* CAM_FUNC_JUMP2 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 20, CAM_DATA_20 },
    { 0x03E7, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x4 | 0x2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B64FC[] = {
    /* CAM_FUNC_PARA1 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0140, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0008, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 50, CAM_DATA_11 },
    { 0x000C, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B652C[] = {
    /* CAM_FUNC_PARA1 */
    { 0xFFB0, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x0046, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x86, CAM_DATA_FLAGS },
    { 50, CAM_DATA_11 },
    { 0x0002, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B655C[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 0x0154, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6584[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 260, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B65AC[] = {
    /* CAM_FUNC_PARA1 */
    { 10, CAM_DATA_YOFFSET },
    { 260, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B65DC[] = {
    /* CAM_FUNC_KEEP1 */
    { 10, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 30, CAM_DATA_16 },
    { 0x000F, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B660C[] = {
    /* CAM_FUNC_KEEP3 */
    { 10, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 30, CAM_DATA_13 },
    { 10, CAM_DATA_14 },
    { 30, CAM_DATA_15 },
    { 30, CAM_DATA_16 },
    { 0x0046, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | 0x40, CAM_DATA_FLAGS },
    { 60, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6640[] = {
    /* CAM_FUNC_BATT1 */
    { 10, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 80, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 30, CAM_DATA_16 },
    { 0x0019, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 60, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6674[] = {
    /* CAM_FUNC_SUBJ1 */
    { 0, CAM_DATA_YOFFSET },
    { 10, CAM_DATA_01 },
    { 60, CAM_DATA_02 },
    { 10, CAM_DATA_04 },
    { 0, CAM_DATA_19 },
    { 50, CAM_DATA_17 },
    { 0, CAM_DATA_18 },
    { 45, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0), CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6698[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 260, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 0x0028, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B66C0[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 260, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossMajoraModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0018, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0020, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossMajoraModeFollowTargetData[] = {
    /* CAM_FUNC_KEEP1 */
    { -30, CAM_DATA_YOFFSET },
    { 0x00F0, CAM_DATA_01 },
    { 260, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 60, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossMajoraModeBattleData[] = {
    /* CAM_FUNC_BATT1 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 20, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 20, CAM_DATA_17 },
    { 70, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 10, CAM_DATA_11 },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossMajoraModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossMajoraModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossTwinmoldModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { 20, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x001A, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0020, CAM_DATA_YAWDIFFRANGE },
    { 0x004B, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossTwinmoldModeTargetData[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 50, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 55, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossTwinmoldModeFollowTargetData[] = {
    /* CAM_FUNC_KEEP1 */
    { -30, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 60, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0), CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossTwinmoldModeBattleData[] = {
    /* CAM_FUNC_BATT1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 30, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0, CAM_DATA_16 },
    { 20, CAM_DATA_17 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 10, CAM_DATA_11 },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossTwinmoldModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x004B, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossTwinmoldModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_10 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGohtModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGohtModeBattleData[] = {
    /* CAM_FUNC_BATT1 */
    { -25, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 80, CAM_DATA_14 },
    { 0xFFFE, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x0019, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGohtModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGohtModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x000F, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGohtModeGoronDashData[] = {
    /* CAM_FUNC_NORM1 */
    { 60, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0154, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0x000F, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 0x0055, CAM_DATA_FOV },
    { 90, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeNormalData[] = {
    /* CAM_FUNC_JUMP3 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x84, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeFollowTargetData[] = {
    /* CAM_FUNC_KEEP1 */
    { -30, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x00F0, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x000F, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeBattleData[] = {
    /* CAM_FUNC_BATT1 */
    { -30, CAM_DATA_YOFFSET },
    { 0x00BE, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 50, CAM_DATA_14 },
    { 0, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 20, CAM_DATA_17 },
    { 50, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeGoronJumpData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 260, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xC, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeDekuFlyData[] = {
    /* CAM_FUNC_JUMP3 */
    { -30, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x5, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeDekuHideData[] = {
    /* CAM_FUNC_JUMP3 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x00A0, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { -15, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x85, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetBossGyorgModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeNormalData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 100, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x84, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeTargetData[] = {
    /* CAM_FUNC_PARA1 */
    { -50, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0028, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 100, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x3, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeGoronJumpData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0140, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xC, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeDekuFlyData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x5, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeDekuHideData[] = {
    /* CAM_FUNC_JUMP3 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { -18, CAM_DATA_PITCHTARGET },
    { 0x0012, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x85, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetPinnacleRockModeGoronDashData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 0x0118, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0x0011, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x004B, CAM_DATA_FOV },
    { 0x0023, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xC, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetNormal2ModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0x000E, CAM_DATA_PITCHTARGET },
    { 0x0019, CAM_DATA_04 },
    { 0x000E, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetNormal2ModeTargetData[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 80, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 50, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetNormal2ModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x01A4, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetNormal2ModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 350, CAM_DATA_01 },
    { 0x0190, CAM_DATA_02 },
    { 0x000E, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 0x0010, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6C98[] = {
    /* CAM_FUNC_NORM1 */
    { -30, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 0x0016, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 30, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6CC0[] = {
    /* CAM_FUNC_KEEP1 */
    { -30, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 30, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6CF0[] = {
    /* CAM_FUNC_KEEP3 */
    { -30, CAM_DATA_YOFFSET },
    { 0x0041, CAM_DATA_01 },
    { 0x0046, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 10, CAM_DATA_14 },
    { 0x0005, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 20, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | 0x20, CAM_DATA_FLAGS },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D24[] = {
    /* CAM_FUNC_NORM1 */
    { -20, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D4C[] = {
    /* CAM_FUNC_NORM1 */
    { -30, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 0x0140, CAM_DATA_02 },
    { 0x000F, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 0x0019, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6D74[] = {
    /* CAM_FUNC_FIXD2 */
    { -40, CAM_DATA_YOFFSET },
    { 60, CAM_DATA_01 },
    { 0x3200, CAM_DATA_02 },
    { 100, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0xB, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetWhirlpoolModeNormalData[] = {
    /* CAM_FUNC_JUMP3 */
    { -10, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 50, CAM_DATA_PITCHTARGET },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 30, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xA4, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetWhirlpoolModeFreeFallData[] = {
    /* CAM_FUNC_JUMP3 */
    { 0, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0019, CAM_DATA_YAWDIFFRANGE },
    { 0x004B, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x14, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetWhirlpoolModeGoronJumpData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0140, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0019, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x1C, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetWhirlpoolModeDekuFlyData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 300, CAM_DATA_01 },
    { 350, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 30, CAM_DATA_YAWDIFFRANGE },
    { 0x0041, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x25, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetWhirlpoolModeDekuHideData[] = {
    /* CAM_FUNC_JUMP3 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { -18, CAM_DATA_PITCHTARGET },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 30, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x94, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetWhirlpoolModeGoronDashData[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 220, CAM_DATA_01 },
    { 260, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0x0008, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 20, CAM_DATA_YAWDIFFRANGE },
    { 0x004B, CAM_DATA_FOV },
    { 0x0023, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x1C, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetCuccoShackModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { 0xFFBA, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 0x01F4, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x002D, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetCuccoShackModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 0x01F4, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetCuccoShackModeDekuHideData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 250, CAM_DATA_01 },
    { 0x01F4, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0x0019, CAM_DATA_04 },
    { 0x000C, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetGiantModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0x00A0, CAM_DATA_02 },
    { -15, CAM_DATA_PITCHTARGET },
    { 0x0019, CAM_DATA_04 },
    { 0x000E, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetGiantModeTargetData[] = {
    /* CAM_FUNC_PARA1 */
    { -40, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 80, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 50, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetGiantModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { -10, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 0x0096, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 10, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetGiantModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0x00A0, CAM_DATA_02 },
    { 0xFFF4, CAM_DATA_PITCHTARGET },
    { 0x0019, CAM_DATA_04 },
    { 0x000E, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 50, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6FA0[] = {
    /* CAM_FUNC_UNIQ2 */
    { -40, CAM_DATA_YOFFSET },
    { 20, CAM_DATA_01 },
    { 60, CAM_DATA_FOV },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x32, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6FB0[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0010, CAM_DATA_PITCHTARGET },
    { 0x0010, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0041, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 0x004B, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B6FD8[] = {
    /* CAM_FUNC_KEEP1 */
    { -20, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 0x0096, CAM_DATA_02 },
    { 0, CAM_DATA_13 },
    { 0x0004, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x1, CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7008[] = {
    /* CAM_FUNC_BATT1 */
    { -25, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_01 },
    { 180, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 60, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 20, CAM_DATA_11 },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B703C[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0010, CAM_DATA_PITCHTARGET },
    { 0x000C, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 0x0028, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7064[] = {
    /* CAM_FUNC_NORM1 */
    { -15, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0x0010, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 70, CAM_DATA_FOV },
    { 20, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B708C[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0005, CAM_DATA_02 },
    { 30, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 30, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x22, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B70BC[] = {
    /* CAM_FUNC_JUMP3 */
    { -10, CAM_DATA_YOFFSET },
    { 270, CAM_DATA_01 },
    { 300, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 30, CAM_DATA_04 },
    { 20, CAM_DATA_05 },
    { 0x0041, CAM_DATA_YAWDIFFRANGE },
    { 60, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x84, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B70E4[] = {
    /* CAM_FUNC_PARA1 */
    { -30, CAM_DATA_YOFFSET },
    { 0x0118, CAM_DATA_01 },
    { 0x0028, CAM_DATA_02 },
    { 10, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x000F, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 60, CAM_DATA_FOV },
    { 100, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x3, CAM_DATA_FLAGS },
    { 60, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7114[] = {
    /* CAM_FUNC_KEEP3 */
    { -20, CAM_DATA_YOFFSET },
    { 50, CAM_DATA_01 },
    { 100, CAM_DATA_02 },
    { 50, CAM_DATA_13 },
    { 0x0005, CAM_DATA_14 },
    { 20, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x0028, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5), CAM_DATA_FLAGS },
    { 60, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7148[] = {
    /* CAM_FUNC_JUMP3 */
    { -40, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 20, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0028, CAM_DATA_YAWDIFFRANGE },
    { 0x004B, CAM_DATA_FOV },
    { 0x0023, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xC, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7170[] = {
    /* CAM_FUNC_KEEP1 */
    { -30, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 200, CAM_DATA_02 },
    { 20, CAM_DATA_13 },
    { 0x0028, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 10, CAM_DATA_16 },
    { 0x000F, CAM_DATA_17 },
    { 45, CAM_DATA_FOV },
    { 60, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x11, CAM_DATA_FLAGS },
    { 30, CAM_DATA_11 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B71A0[] = {
    /* CAM_FUNC_BATT1 */
    { -30, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 10, CAM_DATA_13 },
    { 60, CAM_DATA_14 },
    { -5, CAM_DATA_15 },
    { 20, CAM_DATA_16 },
    { 0x0023, CAM_DATA_17 },
    { 55, CAM_DATA_FOV },
    { 0x0046, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x12, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_11 },
    { 0x0028, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B71D4[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0190, CAM_DATA_01 },
    { 20, CAM_DATA_02 },
    { 20, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 20, CAM_DATA_04 },
    { 5, CAM_DATA_05 },
    { 70, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0xA, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7204[] = {
    /* CAM_FUNC_UNIQ0 */
    { 0, CAM_DATA_YOFFSET },
    { 100, CAM_DATA_04 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue D_801B7210[] = {
    /* CAM_FUNC_KEEP3 */
    { -10, CAM_DATA_YOFFSET },
    { 0x0078, CAM_DATA_01 },
    { 180, CAM_DATA_02 },
    { 50, CAM_DATA_13 },
    { 0x0005, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0x0005, CAM_DATA_16 },
    { 0x0046, CAM_DATA_17 },
    { 35, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | 0x20, CAM_DATA_FLAGS },
    { 60, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetNormal4ModeTalkData[] = {
    /* CAM_FUNC_KEEP3 */
    { -20, CAM_DATA_YOFFSET },
    { 0x006E, CAM_DATA_01 },
    { 0x00A0, CAM_DATA_02 },
    { 80, CAM_DATA_13 },
    { 0x000F, CAM_DATA_14 },
    { 10, CAM_DATA_15 },
    { 0, CAM_DATA_16 },
    { 0x0046, CAM_DATA_17 },
    { 40, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { 20, CAM_DATA_04 },
    { SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | 0x20, CAM_DATA_FLAGS },
    { 50, CAM_DATA_18 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetElegyShellModeNormalData[] = {
    /* CAM_FUNC_KEEP4 */
    { -45, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { -10, CAM_DATA_PITCHTARGET },
    { 0x00A5, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 30, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetElegyShellModeJumpData[] = {
    /* CAM_FUNC_KEEP4 */
    { -40, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0x0012, CAM_DATA_PITCHTARGET },
    { 0x008C, CAM_DATA_10 },
    { 0x0005, CAM_DATA_18 },
    { 70, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 30, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetElegyShellModeDekuShootData[] = {
    /* CAM_FUNC_KEEP4 */
    { -20, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0xFFFE, CAM_DATA_PITCHTARGET },
    { 0x008C, CAM_DATA_10 },
    { 0x000F, CAM_DATA_18 },
    { 50, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 30, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetElegyShellModeGoronDashData[] = {
    /* CAM_FUNC_KEEP4 */
    { -50, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0xFFF4, CAM_DATA_PITCHTARGET },
    { 0x00A0, CAM_DATA_10 },
    { 0x0006, CAM_DATA_18 },
    { 50, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0x2, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 30, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetElegyShellModeDekuFlyData[] = {
    /* CAM_FUNC_KEEP4 */
    { 0xFFC4, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 0xFFF4, CAM_DATA_PITCHTARGET },
    { 0xFF74, CAM_DATA_10 },
    { 30, CAM_DATA_18 },
    { 50, CAM_DATA_FOV },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | 0xC, CAM_DATA_FLAGS },
    { 0x0019, CAM_DATA_04 },
    { 30, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon4ModeNormalData[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { -5, CAM_DATA_PITCHTARGET },
    { 0x0010, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 0x0034, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 80, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon4ModeTargetData[] = {
    /* CAM_FUNC_PARA1 */
    { 0, CAM_DATA_YOFFSET },
    { 200, CAM_DATA_01 },
    { 0x0019, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 0, CAM_DATA_10 },
    { 0x0005, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 45, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | 0x2, CAM_DATA_FLAGS },
    { 80, CAM_DATA_11 },
    { 0, CAM_DATA_12 },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon4ModeJumpData[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 0x0096, CAM_DATA_01 },
    { 250, CAM_DATA_02 },
    { 0, CAM_DATA_PITCHTARGET },
    { 0x0018, CAM_DATA_04 },
    { 0x0005, CAM_DATA_05 },
    { 50, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 50, CAM_DATA_08 },
    { SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * Setting    Mode      Function
 * -------    ------    --------
 * NORMAL0    NORMAL    NORM1
 */
CameraModeValue sSetDungeon4ModeStillData[] = {
    /* CAM_FUNC_NORM1 */
    { 0, CAM_DATA_YOFFSET },
    { 180, CAM_DATA_01 },
    { 220, CAM_DATA_02 },
    { 0x0005, CAM_DATA_PITCHTARGET },
    { 100, CAM_DATA_04 },
    { 100, CAM_DATA_05 },
    { 100, CAM_DATA_YAWDIFFRANGE },
    { 55, CAM_DATA_FOV },
    { 10, CAM_DATA_08 },
    { SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_2 | NORM1_FLG_1, CAM_DATA_FLAGS },
};

/**
 * =====================================================================
 *    CAMERA SETTINGS: USAGE OF FUNCTIONS AND DATA FOR SPECIFIC MODES
 * =====================================================================
 */

#define CAM_SETTING_MODE_ENTRY(func, data) \
    { func, ARRAY_COUNT(data), data }

CameraMode sCamSetNormal0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronJumpData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBoomerangData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeZData), 
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),
};

CameraMode sCamSetNormal3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronDashData),  
    { CAM_FUNC_NONE, 0, NULL },                               
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal3ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    { CAM_FUNC_NONE, 0, NULL },                               
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal3ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    { CAM_FUNC_NONE, 0, NULL },                               
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronJumpData),  
};

CameraMode sCamSetPivotDivingModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ2, sSetPivotDivingModeNormalData),  
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ2, sSetPivotDivingModeTargetData),  
};

CameraMode sCamSetHorseModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeNormalData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeJumpData),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetHorseModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeTargetData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetHorseModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetHorseModeSlingShotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetHorseModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetHorseModeBattleData),  
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeStillData),   
};

CameraMode sCamSetZora0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, D_801B4EB4),  
};

CameraMode sCamSetPreRendFixedModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD3, sSetPrerendFixedModeNormalData),  
};

CameraMode sCamSetPreRendPivotModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ7, sSetPrerendPivotModeNormalData),  
};

CameraMode sCamSetDoorCModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC9, D_801B4EE4),  
};

CameraMode sCamSetDemo0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO1, D_801B4EF0),  
};

CameraMode sCamSetFree0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ6, D_801B4EF4),  
};

CameraMode sCamSetFukan0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4EF8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4F50),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B4F20),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4F78),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4EF8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetNormal1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal1ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal1ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetNanameModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM4, D_801B4FF0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetCirc0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5018),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5034),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5050),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
};

CameraMode sCamSetFixed0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B506C),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
};

CameraMode sCamSetSpiralModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC8, D_801B507C),  
};

CameraMode sCamSetDungeon0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon0ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetDungeon0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBoomerangData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
};

CameraMode sCamSetItem0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5338),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B535C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B53A4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5380),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B53C8),  
};

CameraMode sCamSetItem1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B53EC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5410),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5458),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5434),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B547C),  
};

CameraMode sCamSetItem2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B54A0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B54C4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B550C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B54E8),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5530),  
};

CameraMode sCamSetItem3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5554),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5578),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B55C0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B559C),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B55E4),  
};

CameraMode sCamSetNaviModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ6, D_801B4EF4),  
};

CameraMode sCamSetWarp0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5608),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B562C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5674),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5650),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5698),  
};

CameraMode sCamSetDeathModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeDekuShootData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeJumpData),  
};

CameraMode sCamSetRebirthModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B574C),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),  
};

CameraMode sCamSetTreasureModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO2, D_801B5770),  
};

CameraMode sCamSetTransformModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO4, D_801B4EF4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO5, D_801B4EF4),  
};

CameraMode sCamSetAttentionModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO1, D_801B4EF4),  
};

CameraMode sCamSetWarp1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO3, D_801B4EF4),  
};

CameraMode sCamSetDungeon1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon1ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon1ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetDungeon0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon1ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon1ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetFixed1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B5824),  
};

CameraMode sCamSetFixed2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B5834),  
};

CameraMode sCamSetMazeModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA2, D_801B5844),  
};

CameraMode sCamSetRemoteBombModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM2, D_801B5864),  
};

CameraMode sCamSetCirc1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5884),  
};

CameraMode sCamSetCirc2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B58A0),  
};

CameraMode sCamSetCirc3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B58BC),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5034),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5050),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
};

CameraMode sCamSetCirc4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B58D8),  
};

CameraMode sCamSetFixed3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B58F4),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
};

CameraMode sCamSetTower0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM0, D_801B5904),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5928),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5950),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetParallel0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5978),  
};

CameraMode sCamSetNormDModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B59A8),  
};

CameraMode sCamSetSubjectDModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, D_801B59D0),  
};

CameraMode sCamSetStart0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ0, D_801B59F4),  
};

CameraMode sCamSetStart2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ0, D_801B5A00),  
};

CameraMode sCamSetStop0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ6, D_801B4EF4),  
};

CameraMode sCamSetJCruisingModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, D_801B5A0C),  
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),  
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),  
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),  
};

CameraMode sCamSetClimeMazeModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5A30),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5A30),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetSidedModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5A64),  
};

CameraMode sCamSetDungeon2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon2ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon2ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetDungeon2ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon2ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon2ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetBossOdolwaModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossOdolwaModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossOdolwaModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetBossOdolwaModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetBossOdolwaModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetBossOdolwaModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossOdolwaModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetKeepBackModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5C80),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5A30),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetCirc6Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5CB0),  
};

CameraMode sCamSetCirc7Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5CCC),  
};

CameraMode sCamSetMiniBossModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5CE8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5D74),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B5D10),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B5D40),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5D9C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetRFixed1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B5DC4),  
};

CameraMode sCamSetTresure1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5DD4),  
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B5DFC),  
};

CameraMode sCamSetBombBasketModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5E2C),  
};

CameraMode sCamSetCirc8Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5E48),  
};

CameraMode sCamSetFukan1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5E64),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4F50),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B4F20),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B5E8C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4EF8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetDungeon3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon3ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon3ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon3ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetDungeon0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon3ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon3ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetTelescopeModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetTelescopeModeNormalData),  
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetTelescopeModeFirstPersonData),  
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetTelescopeModeTargetData),  
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetTelescopeModeDekuHideData),  
};

CameraMode sCamSetRoom0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B601C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6154),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B62F4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B634C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B62C4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B6074),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B6044),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B60A4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B60D8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B631C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B626C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B620C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B610C),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B6130),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B61DC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B617C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B61AC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B6294),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B6374),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B63A4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBoomerangData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B623C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B63CC),  
};

CameraMode sCamSetRCirc0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B63FC),  
};

CameraMode sCamSetCirc9Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B6418),   
    { CAM_FUNC_NONE, 0, NULL },          
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5034),   
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5050),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
};

CameraMode sCamSetOnThePoleModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6434),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B648C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B645C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetDungeon0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B655C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B64B4),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B64D8),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B64FC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B652C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon1ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetInBushModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6584),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6698),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, D_801B6674),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B65DC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B65AC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B660C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B6640),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B66C0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B4EF8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetBossMajoraModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossMajoraModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossMajoraModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetBossMajoraModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetBossMajoraModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossMajoraModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetBossTwinmoldModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossTwinmoldModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossTwinmoldModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetBossTwinmoldModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetBossTwinmoldModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetBossTwinmoldModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossTwinmoldModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetBossGohtModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossGohtModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossGohtModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossGohtModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetBossGohtModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossGohtModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetBossGyorgModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronDashData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetBossGyorgModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_SLINGSHOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetBossGyorgModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetBossGyorgModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUFLYZ      
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeGoronJumpData),  
};

CameraMode sCamSetConnect0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO0, D_801B4EF4),  
};

CameraMode sCamSetPinnacleRockModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeGoronDashData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetPinnacleRockModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_SLINGSHOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetPinnacleRockModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeGoronJumpData),  
};

CameraMode sCamSetNormal2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal2ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal2ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal2ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal2ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetBombBowlModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6C98),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6D24),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B62F4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B634C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B62C4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B6CC0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B6044),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B6CF0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B60D8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B631C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6D4C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B620C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B610C),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B6130),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B61DC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B617C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B61AC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B6294),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B6374),  
};

CameraMode sCamSetCircAModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B6D74),  
};

CameraMode sCamSetWhirlpoolModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeGoronDashData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetPinnacleRockModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    { CAM_FUNC_NONE, 0, NULL },  // CAM_MODE_SLINGSHOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeGoronJumpData),  
};

CameraMode sCamSetCuccoShackModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetCuccoShackModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal2ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    { CAM_FUNC_NONE, 0, NULL }, // CAM_MODE_DEKUFLY
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal2ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetCuccoShackModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetCuccoShackModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
};

CameraMode sCamSetGiantModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetGiantModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetGiantModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetGiantModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetGiantModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetScene0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ2, D_801B6FA0),  
};

CameraMode sCamSetRoom1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6FB0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B703C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B62C4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B6FD8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B60A4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B7008),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B7064),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B708C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetWater2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, D_801B70BC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, D_801B7148),  
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B70E4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B7114),  
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal3ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    { CAM_FUNC_NONE, 0, NULL },          
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronJumpData),  
};

CameraMode sCamSetSokonasiModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ3, D_801B6584),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ3, D_801B6698),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ3, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ3, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, D_801B6674),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B65DC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, D_801B65AC),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B660C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ5, D_801B6640),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ3, D_801B66C0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ3, D_801B6584),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ4, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetForceKeepModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B7170),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B71A0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetParallel1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B71D4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetStart1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ0, D_801B7204),  
};

CameraMode sCamSetRoom2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B6FB0),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B703C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B62C4),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, D_801B6FD8),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B7210),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, D_801B7008),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, D_801B7064),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B708C),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetNorm4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal4ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetNormal0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraMode sCamSetElegyShellModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetElegyShellModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetElegyShellModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetElegyShellModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetElegyShellModeDekuShootData),  
    { CAM_FUNC_NONE, 0, NULL },         
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetElegyShellModeDekuFlyData),  
};

CameraMode sCamSetDungeon4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon4ModeNormalData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon4ModeJumpData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon4ModeTargetData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetDungeon0ModeBattleData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetDungeon4ModeStillData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeChargeData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC5, sSetNormal0ModeHookshotData),   
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeFreeFallData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeHangZData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModePushPullData),  
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuFlyZData),  
};

CameraSetting sCameraSettings[] = {
    { 0x00000000, 0x00000000, NULL },                     // CAM_SET_NONE
    { 0x3FFFFFFF, 0x00000005, sCamSetNormal0Modes },        // CAM_SET_NORMAL0
    { 0x05FFEFF7, 0x00000005, sCamSetNormal3Modes },        // CAM_SET_NORMAL3
    { 0x00000401, 0x00000005, sCamSetPivotDivingModes },        // CAM_SET_PIVOT_DIVING
    { 0x00017E13, 0x80000005, sCamSetHorseModes },       // CAM_SET_HORSE
    { 0x00000001, 0x80000005, sCamSetZora0Modes },        // CAM_SET_ZORA
    { 0x00000001, 0x8000000C, sCamSetPreRendFixedModes },     // CAM_SET_PREREND_FIXED
    { 0x00000001, 0x8000000C, sCamSetPreRendPivotModes },     // CAM_SET_PREREND_PIVOT
    { 0x00000001, 0xC0000007, sCamSetDoorCModes },        // CAM_SET_DOORC
    { 0x00000001, 0xC000000E, sCamSetDemo0Modes },        // CAM_SET_DEMO0
    { 0x00000001, 0x80000005, sCamSetFree0Modes },        // CAM_SET_FREE0
    { 0x03FFFFFF, 0x00000005, sCamSetFukan0Modes },       // CAM_SET_FUKAN0
    { 0x03FFFFFF, 0x00000005, sCamSetNormal1Modes },        // CAM_SET_NORMAL1
    { 0x03FFFFFF, 0x80000005, sCamSetNanameModes },       // CAM_SET_NANAME
    { 0x00001BD9, 0x80000005, sCamSetCirc0Modes },        // CAM_SET_CIRCLE0
    { 0x000011D9, 0x80000005, sCamSetFixed0Modes },       // CAM_SET_FIXED0
    { 0x00000001, 0x40000005, sCamSetSpiralModes },       // CAM_SET_SPIRAL
    { 0x3FFFFFFF, 0x00000005, sCamSetDungeon0Modes },     // CAM_SET_DUNGEON0
    { 0x0000002F, 0x00000005, sCamSetItem0Modes },        // CAM_SET_ITEM0
    { 0x0000002F, 0x00000005, sCamSetItem1Modes },        // CAM_SET_ITEM1
    { 0x0000002F, 0x00000005, sCamSetItem2Modes },        // CAM_SET_ITEM2
    { 0x0000002F, 0x00000005, sCamSetItem3Modes },        // CAM_SET_ITEM3
    { 0x00000001, 0x00000005, sCamSetNaviModes },         // CAM_SET_NAVI
    { 0x0000002F, 0x00000005, sCamSetWarp0Modes },        // CAM_SET_WARP0
    { 0x0000002F, 0x00000005, sCamSetDeathModes },        // CAM_SET_DEATH
    { 0x0000002F, 0x00000005, sCamSetRebirthModes },      // CAM_SET_REBIRTH
    { 0x00000001, 0x40000005, sCamSetTreasureModes },     // CAM_SET_TREASURE_MINIGAME
    { 0x00000003, 0x00000005, sCamSetTransformModes },    // CAM_SET_TRANSFORM
    { 0x00000001, 0x00000005, sCamSetAttentionModes },    // CAM_SET_ATTENTION
    { 0x00000001, 0x00000005, sCamSetWarp1Modes },        // CAM_SET_WARP1
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon1Modes },     // CAM_SET_DUNGEON1
    { 0x00000001, 0x80000005, sCamSetFixed1Modes },       // CAM_SET_FIXED1
    { 0x00000001, 0x80000005, sCamSetFixed2Modes },       // CAM_SET_FIXED2
    { 0x00000001, 0x00000005, sCamSetMazeModes },         // CAM_SET_MAZE
    { 0x00000001, 0x00000005, sCamSetRemoteBombModes },   // CAM_SET_REMOTEBOMB
    { 0x00000001, 0x80000005, sCamSetCirc1Modes },        // CAM_SET_CIRCLE1
    { 0x00000001, 0x80000005, sCamSetCirc2Modes },        // CAM_SET_CIRCLE2
    { 0x00001BD9, 0x80000005, sCamSetCirc3Modes },        // CAM_SET_CIRCLE3
    { 0x00000001, 0x80000005, sCamSetCirc4Modes },        // CAM_SET_CIRCLE4
    { 0x000011D9, 0x80000005, sCamSetFixed3Modes },       // CAM_SET_FIXED3
    { 0x03FFFFFF, 0x80000005, sCamSetTower0Modes },       // CAM_SET_TOWER0
    { 0x00000001, 0x80000005, sCamSetParallel0Modes },    // CAM_SET_PARALLEL0
    { 0x00000001, 0x00000005, sCamSetNormDModes },        // CAM_SET_NORMALD
    { 0x00000001, 0x00000005, sCamSetSubjectDModes },     // CAM_SET_SUBJECTD
    { 0x00000001, 0xC0000008, sCamSetStart0Modes },       // CAM_SET_START0
    { 0x00000001, 0xC0000008, sCamSetStart2Modes },       // CAM_SET_START2
    { 0x00000001, 0x00000005, sCamSetStop0Modes },        // CAM_SET_STOP0
    { 0x00003051, 0x00000005, sCamSetJCruisingModes },    // CAM_SET_JCRUISING
    { 0x03FFFFFF, 0x00000005, sCamSetClimeMazeModes },    // CAM_SET_CLIMEMAZE
    { 0x00000001, 0x00000005, sCamSetSidedModes },        // CAM_SET_SIDED
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon2Modes },     // CAM_SET_DUNGEON2
    { 0x03FFFFFF, 0x00000005, sCamSetBossOdolwaModes },   // CAM_SET_BOSS_ODOLWA
    { 0x03FFFFFF, 0x80000005, sCamSetKeepBackModes },     // CAM_SET_KEEPBACK
    { 0x00000001, 0x80000005, sCamSetCirc6Modes },        // CAM_SET_CIRCLE6
    { 0x00000001, 0x80000005, sCamSetCirc7Modes },        // CAM_SET_CIRCLE7
    { 0x03FFFFFF, 0x00000005, sCamSetMiniBossModes },     // CAM_SET_MINIBOSS
    { 0x00000001, 0x80000005, sCamSetRFixed1Modes },      // CAM_SET_RFIXED1
    { 0x00000401, 0x00000005, sCamSetTresure1Modes },     // CAM_SET_TRESURE1
    { 0x00000001, 0x80000005, sCamSetBombBasketModes },   // CAM_SET_BOMBBASKET
    { 0x00000001, 0x80000005, sCamSetCirc8Modes },        // CAM_SET_CIRCLE8
    { 0x03FFFFFF, 0x00000005, sCamSetFukan1Modes },       // CAM_SET_FUKAN1
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon3Modes },     // CAM_SET_DUNGEON3
    { 0x00008441, 0x0000000A, sCamSetTelescopeModes },    // CAM_SET_TELESCOPE
    { 0x3FFFFFFF, 0x00000005, sCamSetRoom0Modes },        // CAM_SET_ROOM0
    { 0x00000001, 0x80000005, sCamSetRCirc0Modes },       // CAM_SET_RCIRC0
    { 0x00001BD9, 0x80000005, sCamSetCirc9Modes },        // CAM_SET_CIRCLE9
    { 0x03FFFFFF, 0x00000005, sCamSetOnThePoleModes },    // CAM_SET_ONTHEPOLE
    { 0x03FFFFFF, 0x00000005, sCamSetInBushModes },       // CAM_SET_INBUSH
    { 0x03FFFFFF, 0x00000005, sCamSetBossMajoraModes },   // CAM_SET_BOSS_MAJORA
    { 0x03FFFFFF, 0x00000005, sCamSetBossTwinmoldModes }, // CAM_SET_BOSS_TWINMOLD
    { 0x03FFFFFF, 0x00000005, sCamSetBossGohtModes },     // CAM_SET_BOSS_GOHT
    { 0x05FFEFF7, 0x00000005, sCamSetBossGyorgModes },    // CAM_SET_BOSS_GYORG
    { 0x00000001, 0x00000005, sCamSetConnect0Modes },     // CAM_SET_CONNECT0
    { 0x05FFEFF7, 0x00000005, sCamSetPinnacleRockModes }, // CAM_SET_PINNACLE_ROCK
    { 0x03FFFFFF, 0x00000005, sCamSetNormal2Modes },        // CAM_SET_NORMAL2
    { 0x03FFFFFF, 0x00000005, sCamSetBombBowlModes },     // CAM_SET_BOMBBOWL
    { 0x00000001, 0x80000005, sCamSetCircAModes },        // CAM_SET_CIRCLEA
    { 0x05FFEFF7, 0x00000005, sCamSetWhirlpoolModes },    // CAM_SET_WHIRLPOOL
    { 0x01FFFFDF, 0x00000005, sCamSetCuccoShackModes },   // CAM_SET_CUCCO_SHACK
    { 0x03FFFFFF, 0x00000005, sCamSetGiantModes },        // CAM_SET_GIANT
    { 0x00000001, 0x00000008, sCamSetScene0Modes },       // CAM_SET_SCENE0
    { 0x03FFFFFF, 0x00000005, sCamSetRoom1Modes },        // CAM_SET_ROOM1
    { 0x05FFEFF7, 0x00000005, sCamSetWater2Modes },       // CAM_SET_WATER2
    { 0x03FFFFFF, 0x00000005, sCamSetSokonasiModes },     // CAM_SET_SOKONASI
    { 0x03FFFFFF, 0x00000005, sCamSetForceKeepModes },    // CAM_SET_FORCEKEEP
    { 0x03FFFFFF, 0x80000005, sCamSetParallel1Modes },    // CAM_SET_PARALLEL1
    { 0x00000001, 0xC0000008, sCamSetStart1Modes },       // CAM_SET_START1
    { 0x03FFFFFF, 0x00000005, sCamSetRoom2Modes },        // CAM_SET_ROOM2
    { 0x03FFFFFF, 0x00000005, sCamSetNorm4Modes },        // CAM_SET_NORMAL4
    { 0x0000002F, 0x00000005, sCamSetElegyShellModes },        // CAM_SET_ELEGY_SHELL
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon4Modes },     // CAM_SET_DUNGEON4
};

static s16 sCsCamSceneDataGlobalSettings[26] = {
    /* -25 */ CAM_SET_ELEGY_SHELL,
    /* -24 */ CAM_SET_SIDED,
    /* -23 */ CAM_SET_JCRUISING,
    /* -22 */ CAM_SET_NONE,
    /* -21 */ CAM_SET_SUBJECTD,
    /* -20 */ CAM_SET_NORMALD,
    /* -19 */ CAM_SET_NONE,
    /* -18 */ CAM_SET_NONE,
    /* -17 */ CAM_SET_NONE,
    /* -16 */ CAM_SET_WARP1,
    /* -15 */ CAM_SET_ATTENTION,
    /* -14 */ CAM_SET_CONNECT0,
    /* -13 */ CAM_SET_REMOTEBOMB,
    /* -12 */ CAM_SET_NONE,
    /* -11 */ CAM_SET_TRANSFORM,
    /* -10 */ CAM_SET_TREASURE_MINIGAME,
    /* -09 */ CAM_SET_REBIRTH,
    /* -08 */ CAM_SET_DEATH,
    /* -07 */ CAM_SET_WARP0,
    /* -06 */ CAM_SET_NAVI,
    /* -05 */ CAM_SET_ITEM3,
    /* -04 */ CAM_SET_ITEM2,
    /* -03 */ CAM_SET_ITEM1,
    /* -02 */ CAM_SET_ITEM0,
    /* -01 */ CAM_SET_STOP0,
    /*  0  */ CAM_SET_NONE,
};

static s16* sCsCamSceneDataGlobalSettingsPtr = &sCsCamSceneDataGlobalSettings[25];

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
static s32 sCameraNegOne = -1;

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
