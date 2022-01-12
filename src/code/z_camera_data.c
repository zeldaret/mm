#include "ultra64.h"
#include "global.h"

/*=====================================================================
 *                   Default Data: NORMAL0 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal0ModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 22, 15, 40, 60, 84,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal0ModeTargetData[] = {
    PARA1_FIXED_DATA(0, 350, 50, 0, 0, 5, 5, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue sSetNormal0ModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(-30, 180, 200, 20, 40, -5, 10, 15, 45, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1),
                     30),
};

CameraModeValue sSetNormal0ModeBattleData[] = {
    BATT1_FIXED_DATA(-30, 150, 250, 10, 60, -5, 20, 35, 55, 70, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2),
                     25, 40),
};

CameraModeValue sSetNormal0ModeFirstPersonData[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 45, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeTalkData[] = {
    KEEP3_FIXED_DATA(-20, 80, 150, 50, 5, 20, 5, 40, 35, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5)), 60),
};

CameraModeValue sSetNormal0ModeClimbData[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 5, 5, 60, 40, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeBowArrowData[] = {
    SUBJ1_FIXED_DATA(0xFFF9, 0xE, 50, 10, 0, -30, -5, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeBowArrowZData[] = {
    SUBJ1_FIXED_DATA(20, 70, 70, 10, 0xFF88, 20, 0, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeHookshotData[] = {
    SPEC5_FIXED_DATA(-20, 80, 250, 45, 60, 40, 6, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeBoomerangData[] = {
    SUBJ1_FIXED_DATA(5, 50, 50, 10, 0, 0, 0, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeSlingshotData[] = {
    SUBJ1_FIXED_DATA(0xFFF9, 14, 50, 10, 0, -50, -10, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeClimbZData[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 999, 5, 60, 40,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | JUMP2_FLG_4 | JUMP2_FLG_2)),
};

CameraModeValue sSetNormal0ModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 240, 340, 10, 30, 12, 40, 60, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal0ModeHangData[] = {
    PARA1_FIXED_DATA(-40, 320, 50, 40, 0, 8, 5, 60, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 60, 12),
};

CameraModeValue sSetNormal0ModeHangZData[] = {
    PARA1_FIXED_DATA(0xFFB0, 300, 50, 70, 0, 12, 5, 45, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 60, 2),
};

CameraModeValue sSetNormal0ModeFreeFallData[] = {
    PARA1_FIXED_DATA(-10, 320, 100, 70, 0, 4, 5, 70, 20,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_8), 60, 12),
};

CameraModeValue sSetNormal0ModeChargeData[] = {
    PARA1_FIXED_DATA(0xFFB0, 300, -20, 50, 0, 50, 5, 80, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0)), 60, 10),
};

CameraModeValue sSetNormal0ModeChargeZData[] = {
    PARA1_FIXED_DATA(0xFFB0, 300, -20, 40, 0, 50, 5, 80, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue sSetNormal0ModeStillData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal0ModePushPullData[] = {
    PARA1_FIXED_DATA(0, 350, 5, 45, 0, 5, 5, 70, 30,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2), 80, 0),
};

CameraModeValue sSetNormal0ModeFollowBoomerangData[] = {
    KEEP1_FIXED_DATA(-5, 220, 240, 5, 75, 10, 5, 40, 50, 40, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1), 30),
};

CameraModeValue sSetNormal0ModeDekuShootData[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 10, 0, 50, 65, 45, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue sSetNormal0ModeGoronDashData[] = {
    NORM1_FIXED_DATA(50, 160, 255, -2, 12, 10, 40, 92, 88,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal0ModeDekuHideData[] = {
    PARA1_FIXED_DATA(100, 300, -20, 40, 0, 4, 5, 80, 60,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | PARA1_FLG_20 | PARA1_FLG_2), 80, 20),
};

CameraModeValue sSetNormal0ModeDekuFlyData[] = {
    NORM1_FIXED_DATA(0xFFB0, 280, 320, 40, 20, 12, 40, 80, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal0ModeDekuFlyZData[] = {
    PARA1_FIXED_DATA(0xFFBA, 350, 10, 10, 0, 5, 5, 70, 90,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2), 90, 0),
};

CameraModeValue sSetNormal0ModeGoronJumpData[] = {
    NORM1_FIXED_DATA(
        -10, 160, 400, 0, 18, 12, 40, 80, 60,
        (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal0ModeZoraFinData[] = {
    SUBJ1_FIXED_DATA(5, 100, 100, 10, 0, 0, 0, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

/*=====================================================================
 *                   Custom Data: NORMAL3 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal3ModeNormalData[] = {
    JUMP3_FIXED_DATA(-40, 280, 300, 20, 15, 5, 40, 60, 100,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4)),
};

CameraModeValue sSetNormal3ModeTargetData[] = {
    PARA1_FIXED_DATA(-50, 280, 40, 10, 0, 15, 5, 60, 100,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2 | PARA1_FLG_1), 80, 0),
};

CameraModeValue sSetNormal3ModeFreeFallData[] = {
    JUMP3_FIXED_DATA(0, 80, 100, 30, 10, 5, 40, 80, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_4)),
};

CameraModeValue sSetNormal3ModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 150, 240, -5, 18, 5, 40, 70, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

CameraModeValue sSetNormal3ModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-40, 150, 250, 10, 18, 5, 60, 60, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetNormal3ModeDekuHideData[] = {
    JUMP3_FIXED_DATA(0xFFC4, 150, 250, -15, 18, 5, 60, 60, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetNormal3ModeStillData[] = {
    NORM1_FIXED_DATA(-40, 80, 300, 20, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal3ModeGoronDashData[] = {
    JUMP3_FIXED_DATA(-40, 180, 200, 5, 20, 5, 40, 80, 35,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

/*=====================================================================
 *                Custom Data: PIVOT_DIVING Setting
 *=====================================================================
 */

CameraModeValue sSetPivotDivingModeNormalData[] = {
    UNIQ2_FIXED_DATA(-40, 60, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | UNIQ2_FLG_2)),
};

CameraModeValue sSetPivotDivingModeTargetData[] = {
    UNIQ2_FIXED_DATA(-30, 45, 100, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | UNIQ2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: HORSE Setting
 *=====================================================================
 */

CameraModeValue sSetHorseModeNormalData[] = {
    NORM3_FIXED_DATA(-50, 220, 250, 10, 10, 20, 60, 80, (SHRINKWINVAL_NONE | IFACE_ALPHA(6) | NORM3_FLG_20)),
};

CameraModeValue sSetHorseModeTargetData[] = {
    NORM3_FIXED_DATA(-40, 180, 200, -3, 2, 100, 50, 90, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(6) | NORM3_FLG_2)),
};

CameraModeValue sSetHorseModeJumpData[] = {
    NORM3_FIXED_DATA(-50, 220, 260, 10, 10, 20, 60, 50, (SHRINKWINVAL_NONE | IFACE_ALPHA(6))),
};

CameraModeValue sSetHorseModeBowArrowData[] = {
    SUBJ1_FIXED_DATA(0xFFF9, 14, 100, 10, 0, -30, -5, 40, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(6))),
};

CameraModeValue sSetHorseModeSlingShotData[] = {
    SUBJ1_FIXED_DATA(0xFFF9, 14, 100, 10, 0, -50, -10, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0))),
};

CameraModeValue sSetHorseModeBattleData[] = {
    BATT1_FIXED_DATA(0xFFC4, 180, 280, 10, 60, -5, 20, 60, 60, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2),
                     25, 40),
};

CameraModeValue sSetHorseModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(0xFFC4, 180, 220, 25, 45, -5, 15, 15, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(6) | KEEP1_FLG_1),
                     20),
};

CameraModeValue sSetHorseModeTalkData[] = {
    KEEP3_FIXED_DATA(-50, 140, 200, 40, 10, 0, 5, 100, 45, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5)), 60),
};

CameraModeValue sSetHorseModeStillData[] = {
    NORM3_FIXED_DATA(-40, 180, 200, -3, 100, 100, 60, 10, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | NORM3_FLG_80)),
};

/*=====================================================================
 *                Custom Data: ZORA_DIVING Setting
 *=====================================================================
 */

CameraModeValue sSetZoraDivingModeNormalData[] = {
    NORM3_FIXED_DATA(-20, 250, 250, 0, 20, 20, 60, 50, (SHRINKWINVAL_NONE | IFACE_ALPHA(6) | NORM3_FLG_80)),
};

/*=====================================================================
 *                Custom Data: PREREND_FIXED Setting
 *=====================================================================
 */

CameraModeValue sSetPrerendFixedModeNormalData[] = {
    FIXD3_FIXED_DATA((SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

/*=====================================================================
 *                   Custom Data: PREREND_PIVOT Setting
 *=====================================================================
 */

CameraModeValue sSetPrerendPivotModeNormalData[] = {
    UNIQ7_FIXED_DATA(60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

/*=====================================================================
 *                   Custom Data: DOORC Setting
 *=====================================================================
 */

CameraModeValue sSetDoorCModeNormalData[] = {
    SPEC9_FIXED_DATA(-5, 60, (SHRINKWINVAL_NONE_4 | IFACE_ALPHA(2) | SPEC9_FLG_2)),
};

/*=====================================================================
 *                   Custom Data: DEMO0 Setting
 *=====================================================================
 */

/* CAM_FUNC_DEMO1 */
CameraModeValue D_801B4EF0[] = {
    FLAGS_FIXED_DATA((SHRINKWINVAL_LARGE | IFACE_ALPHA(2))),
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
    FLAGS_FIXED_DATA((SHRINKWINVAL_PREV | IFACE_ALPHA(0xF))),
};

/*=====================================================================
 *                   Custom Data: FUKAN0 Setting
 *=====================================================================
 */

CameraModeValue D_801B4EF8[] = {
    NORM1_FIXED_DATA(-40, 600, 600, 45, 50, 10, 50, 45, 90,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_40 | NORM1_FLG_2)),
};

CameraModeValue D_801B4F20[] = {
    PARA1_FIXED_DATA(-40, 400, 25, 60, 0, 5, 5, 60, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 80, 0),
};

CameraModeValue D_801B4F50[] = {
    NORM1_FIXED_DATA(-40, 600, 600, 45, 50, 10, 50, 45, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B4F78[] = {
    NORM1_FIXED_DATA(-40, 600, 600, 45, 100, 100, 100, 45, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: NORMAL1 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal1ModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 15, 18, 12, 70, 60, 80, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_2)),
};

CameraModeValue sSetNormal1ModeStillData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 15, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: NANAME Setting
 *=====================================================================
 */

// Normal4
CameraModeValue D_801B4FF0[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 18, 12, 40, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5018[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 10, 20, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | FIXD2_FLG_1)),
};

CameraModeValue D_801B5034[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 100, 80, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | FIXD2_FLG_40)),
};

CameraModeValue D_801B5050[] = {
    FIXD2_FIXED_DATA(-40, 40, 200, 100, 50, 45, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | FIXD2_FLG_80)),
};

/*=====================================================================
 *                   Custom Data: FIXED0 Setting
 *=====================================================================
 */

CameraModeValue D_801B506C[] = {
    FIXD1_FIXED_DATA(-40, 10, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

/*=====================================================================
 *                 Custom Data: SPIRAL_DOOR Setting
 *=====================================================================
 */

CameraModeValue sSetSpiralDoorModeNormalData[] = {
    SPEC8_FIXED_DATA(-40, 50, 80, 60, 10, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | SPEC8_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: DUNGEON0 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon0ModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 150, 250, 5, 18, 5, 45, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon0ModeTargetData[] = {
    PARA1_FIXED_DATA(0, 200, 25, 5, 0, 5, 5, 45, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_40 | PARA1_FLG_2), 80, 0),
};

CameraModeValue sSetDungeon0ModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(-20, 120, 140, 25, 45, -5, 15, 15, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1),
                     20),
};

CameraModeValue sSetDungeon0ModeBattleData[] = {
    BATT1_FIXED_DATA(-30, 150, 240, 10, 50, 5, 10, 25, 50, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 25,
                     50),
};

CameraModeValue sSetDungeon0ModeFollowBoomerangData[] = {
    KEEP1_FIXED_DATA(-5, 150, 240, 5, 65, 10, 5, 40, 55, 40, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1), 30),
};

CameraModeValue sSetDungeon0ModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 150, 250, 5, 24, 5, 50, 60, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon0ModeFreeFallData[] = {
    PARA1_FIXED_DATA(-10, 250, 100, 70, 0, 4, 5, 70, 10,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_8), 70, 12),
};

CameraModeValue sSetDungeon0ModeClimbData[] = {
    JUMP2_FIXED_DATA(-40, 150, 250, 20, 5, 5, 60, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue sSetDungeon0ModeClimbZData[] = {
    JUMP2_FIXED_DATA(-40, 250, 250, 20, 999, 5, 60, 40,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | JUMP2_FLG_4 | JUMP2_FLG_2)),
};

CameraModeValue sSetDungeon0ModeChargeData[] = {
    PARA1_FIXED_DATA(0, 250, -20, 50, 0, 50, 5, 60, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0)), 60, 10),
};

CameraModeValue sSetDungeon0ModeChargeZData[] = {
    PARA1_FIXED_DATA(50, 250, -20, 40, 0, 50, 5, 80, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue sSetDungeon0ModeHangData[] = {
    PARA1_FIXED_DATA(-40, 220, 50, 40, 0, 12, 5, 60, 10,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 60, 12),
};

CameraModeValue sSetDungeon0ModeHangZData[] = {
    PARA1_FIXED_DATA(0xFFB0, 250, 50, 70, 0, 10, 5, 45, 10,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 60, 2),
};

CameraModeValue sSetDungeon0ModeStillData[] = {
    NORM1_FIXED_DATA(-10, 180, 220, 10, 100, 100, 100, 60, 10,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon0ModePushPullData[] = {
    PARA1_FIXED_DATA(0, 250, 5, 30, 0, 5, 5, 70, 30,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2), 80, 0),
};

/*=====================================================================
 *                   Custom Data: ITEM0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5338[] = {
    KEEP4_FIXED_DATA(5, 70, 25, 0, 0, 45, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B535C[] = {
    KEEP4_FIXED_DATA(-30, 35, 40, 0, 6, 80, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B5380[] = {
    KEEP4_FIXED_DATA(-15, 90, -8, 0, 0, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B53A4[] = {
    KEEP4_FIXED_DATA(20, 45, 0x0037, 0, 12, 55, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B53C8[] = {
    KEEP4_FIXED_DATA(10, 70, 30, 0, 4, 42, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

/*=====================================================================
 *                   Custom Data: ITEM1 Setting
 *=====================================================================
 */

CameraModeValue D_801B53EC[] = {
    KEEP4_FIXED_DATA(-45, 75, 0xFFF4, 165, 5, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B5410[] = {
    KEEP4_FIXED_DATA(-40, 70, 20, 140, 5, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B5434[] = {
    KEEP4_FIXED_DATA(-20, 85, -5, 140, 15, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B5458[] = {
    KEEP4_FIXED_DATA(-50, 0x005F, -15, 160, 6, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B547C[] = {
    KEEP4_FIXED_DATA(0xFFC4, 70, -15, 0xFF74, 30, 70,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_8 | KEEP4_FLG_4), 25, 6),
};

/*=====================================================================
 *                   Custom Data: ITEM2 Setting
 *=====================================================================
 */

CameraModeValue D_801B54A0[] = {
    KEEP4_FIXED_DATA(-40, 0x006E, 5, 150, 5, 65, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B54C4[] = {
    KEEP4_FIXED_DATA(0xFFC4, 0x0082, -10, 0x00AA, 5, 65, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B54E8[] = {
    KEEP4_FIXED_DATA(-40, 0x006E, 0, 140, 5, 65, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B550C[] = {
    KEEP4_FIXED_DATA(-50, 140, -10, 160, 5, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B5530[] = {
    KEEP4_FIXED_DATA(0xFFC4, 120, -8, 150, 5, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

/*=====================================================================
 *                   Custom Data: ITEM3 Setting
 *=====================================================================
 */

CameraModeValue D_801B5554[] = {
    KEEP4_FIXED_DATA(-15, 65, 50, 0xFF65, 5, 75, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_8 | KEEP4_FLG_4), 25,
                     6),
};

CameraModeValue D_801B5578[] = {
    KEEP4_FIXED_DATA(-20, 60, 50, 0xFF65, 5, 75, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_8 | KEEP4_FLG_4), 25,
                     6),
};

CameraModeValue D_801B559C[] = {
    KEEP4_FIXED_DATA(-15, 60, 40, 0x00AA, 5, 75, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 6),
};

CameraModeValue D_801B55C0[] = {
    KEEP4_FIXED_DATA(-25, 0x005F, 50, 0xFF65, 5, 75, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_8 | KEEP4_FLG_4),
                     25, 6),
};

CameraModeValue D_801B55E4[] = {
    KEEP4_FIXED_DATA(-20, 75, 45, 0xFF6A, -5, 75, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_8 | KEEP4_FLG_4),
                     25, 6),
};

/*=====================================================================
 *                   Custom Data: WARP0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5608[] = {
    KEEP4_FIXED_DATA(-45, 165, 0, 0x00B2, 0, 45,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_40 | KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2),
                     30, 10),
};

CameraModeValue D_801B562C[] = {
    KEEP4_FIXED_DATA(0xFFC9, 180, 0, 0x00B2, 0, 45,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_40 | KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2),
                     30, 10),
};

CameraModeValue D_801B5650[] = {
    KEEP4_FIXED_DATA(-20, 0x00AF, 0, 0x00B2, 0, 45,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_40 | KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2),
                     30, 10),
};

CameraModeValue D_801B5674[] = {
    KEEP4_FIXED_DATA(-50, 220, 0, 0x00B2, 0, 45,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_40 | KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2),
                     30, 10),
};

CameraModeValue D_801B5698[] = {
    KEEP4_FIXED_DATA(0xFFC4, 200, 0, 0x00B2, 0, 45,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_40 | KEEP4_FLG_8 | KEEP4_FLG_4 | KEEP4_FLG_2),
                     30, 10),
};

/*=====================================================================
 *                   Custom Data: DEATH Setting
 *=====================================================================
 */

CameraModeValue sSetDeathModeNormalData[] = {
    KEEP4_FIXED_DATA(0xFFBA, 160, 0, 0, 10, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF)), 5, 100),
};

CameraModeValue sSetDeathModeJumpData[] = {
    KEEP4_FIXED_DATA(0xFFBA, 160, 0, 0, 5, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF)), 5, 100),
};

CameraModeValue sSetDeathModeDekuShootData[] = {
    KEEP4_FIXED_DATA(0xFFBA, 150, 0, 0, 5, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF)), 5, 100),
};

/*=====================================================================
 *                   Custom Data: REBIRTH Setting
 *=====================================================================
 */

CameraModeValue D_801B5728[] = {
    KEEP4_FIXED_DATA(0xFFC4, 160, 30, 160, 10, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_4 | KEEP4_FLG_2),
                     5, 100),
};

CameraModeValue D_801B574C[] = {
    KEEP4_FIXED_DATA(-20, 140, 30, 160, 10, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_4 | KEEP4_FLG_2), 5,
                     100),
};

/*=====================================================================
 *                   Custom Data: LONG_CHEST_OPENING Setting
 *=====================================================================
 */

CameraModeValue sSetLongChestOpeningModeNormalData[] = {
    DEMO2_FIXED_DATA(60, 30, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF))),
};

/*=====================================================================
 *                   Custom Data: DUNGEON1 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon1ModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 350, 400, 45, 50, 20, 70, 50, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon1ModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 350, 400, 40, 50, 20, 50, 50, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon1ModeStillData[] = {
    NORM1_FIXED_DATA(-20, 350, 400, 45, 100, 100, 100, 50, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon1ModePushPullData[] = {
    PARA1_FIXED_DATA(0, 250, 5, 30, 0, 5, 5, 70, 30,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2), 30, 0),
};

/*=====================================================================
 *                   Custom Data: FIXED1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5824[] = {
    FIXD1_FIXED_DATA(-40, 100, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF))),
};

/*=====================================================================
 *                   Custom Data: FIXED2 Setting
 *=====================================================================
 */

CameraModeValue D_801B5834[] = {
    FIXD1_FIXED_DATA(-40, 10, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF))),
};

/*=====================================================================
 *                   Custom Data: MAZE Setting
 *=====================================================================
 */

CameraModeValue sSetMazeModeNormalData[] = {
    PARA2_FIXED_DATA(0xFFDD, 160, 65, -5, 2, 70, 99, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA2_FLG_2)),
};

/*=====================================================================
 *                   Custom Data: REMOTEBOMB Setting
 *=====================================================================
 */

CameraModeValue sSetRemoteBombModeNormalData[] = {
    NORM2_FIXED_DATA(20, 200, 800, 15, 6, 70, 40, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM2_FLG_2)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5884[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 10, 20, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE2 Setting
 *=====================================================================
 */

CameraModeValue D_801B58A0[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 100, 80, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF))),
};

/*=====================================================================
 *                   Custom Data: CIRCLE3 Setting
 *=====================================================================
 */

CameraModeValue D_801B58BC[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 100, 80, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

/*=====================================================================
 *                   Custom Data: CIRCLE4 Setting
 *=====================================================================
 */

CameraModeValue D_801B58D8[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 100, 10, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_8 | FIXD2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: FIXED3 Setting
 *=====================================================================
 */

CameraModeValue D_801B58F4[] = {
    FIXD1_FIXED_DATA(-40, 100, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

/*=====================================================================
 *             Custom Data: CAM_SET_TOWER_ASCENT Setting
 *=====================================================================
 */

CameraModeValue sSetTowerClimbModeNormalData[] = {
    NORM0_FIXED_DATA(0, 350, 400, 20, 20, 50, 65, 50, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM0_FLG_1)),
};

CameraModeValue sSetTowerClimbModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 340, 400, 10, 30, 12, 40, 65, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetTowerClimbModeStillData[] = {
    NORM1_FIXED_DATA(0, 350, 400, 10, 100, 100, 100, 65, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: PARALLEL0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5978[] = {
    PARA1_FIXED_DATA(0, 400, 20, 0, 0, 20, 5, 70, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_8 | PARA1_FLG_2), 80, 0),
};

/*=====================================================================
 *                   Custom Data: NORMALD Setting
 *=====================================================================
 */

CameraModeValue D_801B59A8[] = {
    NORM1_FIXED_DATA(0, 400, 0x01F4, 15, 18, 12, 35, 70, 30,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: SUBJECTD Setting
 *=====================================================================
 */

CameraModeValue D_801B59D0[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 10, 0, 0, 10, 45, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF))),
};

/*=====================================================================
 *                   Custom Data: START0 Setting
 *=====================================================================
 */

CameraModeValue D_801B59F4[] = {
    UNIQ0_FIXED_DATA(0, 100, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | UNIQ0_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: START2 Setting
 *=====================================================================
 */

CameraModeValue D_801B5A00[] = {
    UNIQ0_FIXED_DATA(0, 30, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | UNIQ0_FLG_10 | UNIQ0_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: BOAT_CRUISE Setting
 *=====================================================================
 */

CameraModeValue sSetBoatCruiseModeNormalData[] = {
    SUBJ1_FIXED_DATA(20, 90, 80, 10, 0, 50, 0xFF38, 45, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

/*=====================================================================
 *                   Custom Data: VERTICAL_CLIMB Setting
 *=====================================================================
 */

CameraModeValue sSetVerticalClimbModeClimbData[] = {
    PARA1_FIXED_DATA_ALT(0, 400, 50, 0, 0, 5, 5, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 70, 0,
                         50),
};

/*=====================================================================
 *                   Custom Data: SIDED Setting
 *=====================================================================
 */

CameraModeValue D_801B5A64[] = {
    PARA1_FIXED_DATA(0, 400, 10, 0, 0xFFA6, 20, 5, 70, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2),
                     70, 0),
};

/*=====================================================================
 *                   Custom Data: DUNGEON2 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon2ModeNormalData[] = {
    NORM1_FIXED_DATA(-10, 270, 300, 20, 0x001C, 20, 65, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon2ModeBattleData[] = {
    BATT1_FIXED_DATA(-40, 200, 240, 50, 20, 5, 10, 20, 50, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 25,
                     40),
};

CameraModeValue sSetDungeon2ModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 270, 300, 40, 50, 20, 50, 60, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon2ModeStillData[] = {
    NORM1_FIXED_DATA(-10, 270, 300, 20, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon2ModePushPullData[] = {
    PARA1_FIXED_DATA(0, 200, 5, 15, 0, 5, 5, 70, 30,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2), 30, 0),
};

/*=====================================================================
 *                   Custom Data: BOSS_ODOLWA Setting
 *=====================================================================
 */

CameraModeValue sSetBossOdolwaModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 250, 350, 10, 24, 12, 40, 65, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossOdolwaModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(-50, 300, 350, 10, 20, 5, 12, 70, 60, 30, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0)), 20),
};

CameraModeValue sSetBossOdolwaModeTalkData[] = {
    KEEP3_FIXED_DATA(-20, 230, 260, 20, 10, 20, 15, 40, 55, 20, 20,
                     (SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | KEEP3_FLG_20), 40),
};

CameraModeValue sSetBossOdolwaModeBattleData[] = {
    BATT1_FIXED_DATA(0xFFC4, 200, 220, 20, 10, 0, 10, 60, 60, 20, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2),
                     10, 40),
};

CameraModeValue sSetBossOdolwaModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 250, 350, 10, 30, 12, 40, 65, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossOdolwaModeStillData[] = {
    NORM1_FIXED_DATA(-20, 250, 350, 10, 100, 100, 100, 65, 15,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: KEEP_BACK Setting
 *=====================================================================
 */

CameraModeValue D_801B5C80[] = {
    PARA1_FIXED_DATA(100, 300, -20, 40, 0, 4, 5, 80, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2), 60, 20),
};

/*=====================================================================
 *                   Custom Data: CIRCLE6 Setting
 *=====================================================================
 */

CameraModeValue D_801B5CB0[] = {
    FIXD2_FIXED_DATA(-40, 60, 0x3200, 10, 20, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_2 | FIXD2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE7 Setting
 *=====================================================================
 */

CameraModeValue D_801B5CCC[] = {
    FIXD2_FIXED_DATA(-40, 40, 200, 10, 20, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_20)),
};

/*=====================================================================
 *                   Custom Data: MINI_BOSS Setting
 *=====================================================================
 */

CameraModeValue sSetMiniBossModeNormalData[] = {
    NORM1_FIXED_DATA(-15, 220, 280, 17, 14, 5, 65, 70, 75,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetMiniBossModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(0, 200, 250, 25, 45, 40, 15, 40, 60, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1), 20),
};

CameraModeValue sSetMiniBossModeBattleData[] = {
    BATT1_FIXED_DATA(-25, 180, 220, 10, 40, 10, 0, 40, 60, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 20,
                     50),
};

CameraModeValue sSetMiniBossModeJumpData[] = {
    NORM1_FIXED_DATA(-15, 220, 280, 16, 12, 5, 60, 70, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetMiniBossModeStillData[] = {
    NORM1_FIXED_DATA(-15, 220, 280, 16, 100, 100, 100, 70, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: RFIXED1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5DC4[] = {
    FIXD1_FIXED_DATA(-40, 10, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD1_FLG_10)),
};

/*=====================================================================
 *                   Custom Data: TRESURE1 Setting
 *=====================================================================
 */

CameraModeValue sSetTreasureChestMinigameModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 80, 120, -10, 15, 20, 40, 70, 70,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2)),
};

CameraModeValue sSetTreasureChestMinigameModeTargetData[] = {
    PARA1_FIXED_DATA(0xFFC4, 0x0226, 0, 65, 0, 5, 5, 75, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_40 | PARA1_FLG_2), 60, 0),
};

/*=====================================================================
 *                   Custom Data: BOMBBASKET Setting
 *=====================================================================
 */

CameraModeValue D_801B5E2C[] = {
    FIXD2_FIXED_DATA(70, 50, 0x3200, 100, 30, 70, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | FIXD2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE8 Setting
 *=====================================================================
 */

CameraModeValue D_801B5E48[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 100, 20, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_8)),
};

/*=====================================================================
 *                   Custom Data: BIRDS_EYE_VIEW_1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5E64[] = {
    NORM1_FIXED_DATA(-20, 800, 800, 60, 50, 10, 50, 45, 90,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_40 | NORM1_FLG_2)),
};

CameraModeValue D_801B5E8C[] = {
    NORM1_FIXED_DATA(-20, 800, 800, 60, 100, 100, 100, 45, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: DUNGEON3 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon3ModeNormalData[] = {
    NORM1_FIXED_DATA(-30, 180, 250, -5, 18, 20, 60, 55, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2)),
};

CameraModeValue sSetDungeon3ModeTargetData[] = {
    PARA1_FIXED_DATA(-30, 180, 20, 0, 0, 5, 5, 45, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_40 | PARA1_FLG_2), 80, 0),
};

CameraModeValue sSetDungeon3ModeJumpData[] = {
    NORM1_FIXED_DATA(-30, 160, 190, 0, 30, 20, 60, 55, 30,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon3ModeStillData[] = {
    NORM1_FIXED_DATA(-40, 0x00AA, 200, 0, 100, 100, 100, 55, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon3ModePushPullData[] = {
    PARA1_FIXED_DATA(0, 180, 5, 5, 0, 5, 5, 70, 30, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2),
                     30, 0),
};

/*=====================================================================
 *                   Custom Data: TELESCOPE Setting
 *=====================================================================
 */

CameraModeValue sSetTelescopeModeNormalData[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 30, (SHRINKWINVAL_NONE | IFACE_ALPHA(2))),
};

CameraModeValue sSetTelescopeModeTargetData[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 15, (SHRINKWINVAL_NONE | IFACE_ALPHA(2))),
};

CameraModeValue sSetTelescopeModeFirstPersonData[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 30, (SHRINKWINVAL_NONE | IFACE_ALPHA(2) | SUBJ1_FLG_10)),
};

CameraModeValue sSetTelescopeModeDekuHideData[] = {
    SUBJ1_FIXED_DATA(0, 5, 50, 0x0001, 0, 0, 0, 45, (SHRINKWINVAL_NONE | IFACE_ALPHA(2) | SUBJ1_FLG_10)),
};

/*=====================================================================
 *                   Custom Data: ROOM0 Setting
 *=====================================================================
 */

CameraModeValue D_801B601C[] = {
    NORM1_FIXED_DATA(0xFFDD, 100, 220, 15, 0x0011, 12, 35, 65, 70,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B6044[] = {
    PARA1_FIXED_DATA(-10, 200, 50, 0, 0, 5, 5, 65, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_40 | PARA1_FLG_10 | PARA1_FLG_2), 60, 0),
};

CameraModeValue D_801B6074[] = {
    KEEP1_FIXED_DATA(-30, 60, 200, 20, 40, -5, 10, 30, 45, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1),
                     30),
};

CameraModeValue D_801B60A4[] = {
    KEEP3_FIXED_DATA(-20, 50, 100, 50, 5, 20, 5, 40, 35, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | KEEP3_FLG_20),
                     60),
};

CameraModeValue D_801B60D8[] = {
    BATT1_FIXED_DATA(-25, 100, 140, 10, 40, -2, 10, 25, 50, 80, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2),
                     25, 50),
};

CameraModeValue D_801B610C[] = {
    JUMP2_FIXED_DATA(-20, 100, 220, 20, 5, 5, 65, 40, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue D_801B6130[] = {
    JUMP2_FIXED_DATA(-20, 120, 240, 20, 999, 5, 60, 40,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | JUMP2_FLG_4 | JUMP2_FLG_2)),
};

CameraModeValue D_801B6154[] = {
    NORM1_FIXED_DATA(-30, 100, 220, 10, 30, 12, 80, 65, 30,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B617C[] = {
    PARA1_FIXED_DATA(-40, 200, 50, 40, 0, 8, 5, 65, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 60, 12),
};

CameraModeValue D_801B61AC[] = {
    PARA1_FIXED_DATA(0xFFB0, 240, 50, 70, 0, 12, 5, 45, 60,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 60, 2),
};

CameraModeValue D_801B61DC[] = {
    PARA1_FIXED_DATA(-10, 200, 100, 70, 0, 4, 5, 70, 20,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_8), 65, 12),
};

CameraModeValue D_801B620C[] = {
    PARA1_FIXED_DATA(0xFFB0, 240, -20, 50, 0, 50, 5, 80, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0)), 65, 10),
};

CameraModeValue D_801B623C[] = {
    PARA1_FIXED_DATA(0xFFB0, 240, -20, 40, 0, 50, 5, 80, 20, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_2), 65, 0),
};

CameraModeValue D_801B626C[] = {
    NORM1_FIXED_DATA(-20, 100, 220, 10, 100, 100, 100, 65, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B6294[] = {
    PARA1_FIXED_DATA(0, 200, 5, 45, 0, 5, 5, 70, 30,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_10 | PARA1_FLG_2), 80, 0),
};

CameraModeValue D_801B62C4[] = {
    KEEP1_FIXED_DATA(-5, 120, 140, 5, 85, 10, 5, 25, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1), 30),
};

CameraModeValue D_801B62F4[] = {
    NORM1_FIXED_DATA(50, 140, 220, 0, 0xC, 10, 40, 90, 90,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B631C[] = {
    PARA1_FIXED_DATA(100, 220, -20, 40, 0, 4, 5, 80, 60,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | PARA1_FLG_20 | PARA1_FLG_2), 80, 20),
};

CameraModeValue D_801B634C[] = {
    NORM1_FIXED_DATA(0xFFC4, 150, 250, 40, 20, 12, 40, 80, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B6374[] = {
    PARA1_FIXED_DATA(0xFFC4, 220, 20, 10, 0, 5, 5, 60, 90,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_8 | PARA1_FLG_4 | PARA1_FLG_2), 90, 0),
};

CameraModeValue D_801B63A4[] = {
    NORM1_FIXED_DATA(
        -10, 120, 240, 0, 18, 12, 40, 80, 60,
        (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B63CC[] = {
    PARA1_FIXED_DATA(0, 220, 50, 0, 0, 5, 5, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

/*=====================================================================
 *                   Custom Data: RCIRC0 Setting
 *=====================================================================
 */

CameraModeValue D_801B63FC[] = {
    FIXD2_FIXED_DATA(-10, 40, 0x3200, 100, 20, 60, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_10 | FIXD2_FLG_8)),
};

/*=====================================================================
 *                   Custom Data: CIRC9 Setting
 *=====================================================================
 */

CameraModeValue D_801B6418[] = {
    FIXD2_FIXED_DATA(-40, 40, 0x3200, 5, 25, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | FIXD2_FLG_4 | FIXD2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: ONTHEPOLE Setting
 *=====================================================================
 */

CameraModeValue D_801B6434[] = {
    NORM1_FIXED_DATA(-15, 60, 600, 35, 40, 20, 60, 45, 80, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_2)),
};

CameraModeValue D_801B645C[] = {
    PARA1_FIXED_DATA(0, 300, 5, 35, 0, 5, 5, 60, 70,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_40 | PARA1_FLG_2), 80, 0),
};

CameraModeValue D_801B648C[] = {
    NORM1_FIXED_DATA(-10, 320, 0x017C, 30, 0x0016, 10, 0x0020, 60, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B64B4[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 5, 5, 60, 50, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue D_801B64D8[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 999, 5, 60, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | JUMP2_FLG_4 | JUMP2_FLG_2)),
};

CameraModeValue D_801B64FC[] = {
    PARA1_FIXED_DATA(-40, 320, 50, 40, 0, 8, 5, 60, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 50, 12),
};

CameraModeValue D_801B652C[] = {
    PARA1_FIXED_DATA(0xFFB0, 300, 50, 70, 0, 12, 5, 45, 50,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_80 | PARA1_FLG_4 | PARA1_FLG_2), 50, 2),
};

CameraModeValue D_801B655C[] = {
    NORM1_FIXED_DATA(-15, 340, 350, 30, 100, 100, 100, 60, 40,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: INBUSH Setting
 *=====================================================================
 */

CameraModeValue D_801B6584[] = {
    NORM1_FIXED_DATA(0, 260, 280, 20, 20, 12, 50, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2)),
};

CameraModeValue D_801B65AC[] = {
    PARA1_FIXED_DATA(10, 260, 50, 15, 0, 5, 5, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue D_801B65DC[] = {
    KEEP1_FIXED_DATA(10, 200, 220, 20, 40, 20, 30, 15, 45, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1),
                     30),
};

CameraModeValue D_801B660C[] = {
    KEEP3_FIXED_DATA(10, 180, 200, 30, 10, 30, 30, 70, 45, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | KEEP3_FLG_40),
                     60),
};

CameraModeValue D_801B6640[] = {
    BATT1_FIXED_DATA(10, 220, 220, 10, 80, 20, 30, 25, 50, 80, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 25,
                     60),
};

CameraModeValue D_801B6674[] = {
    SUBJ1_FIXED_DATA(0, 10, 60, 10, 0, 50, 0, 45, (SHRINKWINVAL_NONE | IFACE_ALPHA(0))),
};

CameraModeValue D_801B6698[] = {
    NORM1_FIXED_DATA(0, 260, 280, 40, 20, 12, 40, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2)),
};

CameraModeValue D_801B66C0[] = {
    NORM1_FIXED_DATA(0, 260, 280, 20, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: BOSS_MAJORA Setting
 *=====================================================================
 */

CameraModeValue sSetBossMajoraModeNormalData[] = {
    NORM1_FIXED_DATA(0, 280, 320, -5, 24, 12, 0x0020, 65, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossMajoraModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(-30, 240, 260, 20, 40, 10, 5, 60, 50, 40, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0)), 30),
};

CameraModeValue sSetBossMajoraModeBattleData[] = {
    BATT1_FIXED_DATA(0xFFC4, 180, 200, 10, 20, 20, 10, 20, 70, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2),
                     10, 40),
};

CameraModeValue sSetBossMajoraModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 30, 12, 40, 65, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossMajoraModeStillData[] = {
    NORM1_FIXED_DATA(0, 280, 320, 0, 100, 100, 100, 65, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: BOSS_TWINMOLD Setting
 *=====================================================================
 */

CameraModeValue sSetBossTwinmoldModeNormalData[] = {
    NORM1_FIXED_DATA(20, 350, 400, 0, 0x001A, 12, 0x0020, 75, 70,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossTwinmoldModeTargetData[] = {
    PARA1_FIXED_DATA(0, 400, 50, 0, 0, 5, 5, 55, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue sSetBossTwinmoldModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(-30, 250, 300, 20, 40, 10, 5, 60, 50, 40, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0)), 30),
};

CameraModeValue sSetBossTwinmoldModeBattleData[] = {
    BATT1_FIXED_DATA(0, 150, 200, 10, 30, 10, 0, 20, 70, 30, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 10,
                     40),
};

CameraModeValue sSetBossTwinmoldModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 350, 400, 10, 30, 12, 40, 75, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossTwinmoldModeStillData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_10 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: BOSS_GOHT Setting
 *=====================================================================
 */

CameraModeValue sSetBossGohtModeNormalData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 20, 12, 50, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossGohtModeBattleData[] = {
    BATT1_FIXED_DATA(-25, 220, 220, 10, 80, -2, 10, 25, 50, 80, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2),
                     25, 50),
};

CameraModeValue sSetBossGohtModeJumpData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 30, 12, 40, 60, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossGohtModeStillData[] = {
    NORM1_FIXED_DATA(-20, 280, 320, 10, 100, 100, 100, 60, 15,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetBossGohtModeGoronDashData[] = {
    NORM1_FIXED_DATA(60, 200, 340, 10, 15, 10, 50, 85, 90,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_4 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: BOSS_GYORG Setting
 *=====================================================================
 */

CameraModeValue sSetBossGyorgModeNormalData[] = {
    JUMP3_FIXED_DATA(-20, 280, 320, 10, 20, 12, 40, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4)),
};

CameraModeValue sSetBossGyorgModeFollowTargetData[] = {
    KEEP1_FIXED_DATA(-30, 200, 240, 20, 40, -5, 10, 15, 45, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1),
                     30),
};

CameraModeValue sSetBossGyorgModeBattleData[] = {
    BATT1_FIXED_DATA(-30, 190, 250, 10, 50, 0, 10, 20, 50, 80, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 25,
                     50),
};

CameraModeValue sSetBossGyorgModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 160, 260, -5, 18, 5, 40, 70, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

CameraModeValue sSetBossGyorgModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-30, 220, 280, 0, 18, 5, 60, 60, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetBossGyorgModeDekuHideData[] = {
    JUMP3_FIXED_DATA(0xFFC4, 160, 280, -15, 18, 5, 60, 60, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetBossGyorgModeStillData[] = {
    NORM1_FIXED_DATA(-40, 100, 320, 20, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: PINNACLE_ROCK Setting
 *=====================================================================
 */

CameraModeValue sSetPinnacleRockModeNormalData[] = {
    JUMP3_FIXED_DATA(-40, 250, 350, 30, 15, 5, 40, 60, 100,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4)),
};

CameraModeValue sSetPinnacleRockModeTargetData[] = {
    PARA1_FIXED_DATA(-50, 350, 40, 10, 0, 15, 5, 60, 100,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2 | PARA1_FLG_1), 80, 0),
};

CameraModeValue sSetPinnacleRockModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 320, 400, -5, 18, 5, 40, 60, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

CameraModeValue sSetPinnacleRockModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-40, 300, 350, 10, 18, 5, 60, 60, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetPinnacleRockModeDekuHideData[] = {
    JUMP3_FIXED_DATA(0xFFC4, 150, 250, -18, 18, 5, 60, 60, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetPinnacleRockModeStillData[] = {
    NORM1_FIXED_DATA(-40, 250, 350, 30, 100, 100, 100, 60, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetPinnacleRockModeGoronDashData[] = {
    JUMP3_FIXED_DATA(-40, 250, 280, 5, 0x0011, 5, 40, 75, 35,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

/*=====================================================================
 *                   Custom Data: NORMAL2 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal2ModeNormalData[] = {
    NORM1_FIXED_DATA(-10, 350, 400, 14, 25, 14, 60, 65, 70,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal2ModeTargetData[] = {
    PARA1_FIXED_DATA(0, 350, 80, 0, 0, 5, 5, 50, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue sSetNormal2ModeJumpData[] = {
    NORM1_FIXED_DATA(-10, 350, 0x01A4, 10, 30, 10, 40, 65, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetNormal2ModeStillData[] = {
    NORM1_FIXED_DATA(-10, 350, 400, 14, 100, 100, 100, 65, 16,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: BOMBBOWL Setting
 *=====================================================================
 */

CameraModeValue D_801B6C98[] = {
    NORM1_FIXED_DATA(-30, 300, 320, 15, 0x0016, 12, 30, 55, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B6CC0[] = {
    KEEP1_FIXED_DATA(-30, 180, 200, 20, 30, -5, 10, 40, 45, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1),
                     30),
};

CameraModeValue D_801B6CF0[] = {
    KEEP3_FIXED_DATA(-30, 65, 70, 10, 10, 5, 5, 20, 45, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | KEEP3_FLG_20),
                     50),
};

CameraModeValue D_801B6D24[] = {
    NORM1_FIXED_DATA(-20, 300, 320, 10, 30, 12, 40, 55, 30,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B6D4C[] = {
    NORM1_FIXED_DATA(-30, 300, 320, 15, 100, 100, 100, 55, 25,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: CIRCA Setting
 *=====================================================================
 */

CameraModeValue D_801B6D74[] = {
    FIXD2_FIXED_DATA(-40, 60, 0x3200, 100, 20, 60,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | FIXD2_FLG_8 | FIXD2_FLG_2 | FIXD2_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: WHIRLPOOL Setting
 *=====================================================================
 */

CameraModeValue sSetWhirlpoolModeNormalData[] = {
    JUMP3_FIXED_DATA(-10, 280, 350, 50, 12, 5, 30, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_20 | JUMP3_FLG_4)),
};

CameraModeValue sSetWhirlpoolModeFreeFallData[] = {
    JUMP3_FIXED_DATA(0, 180, 300, 30, 12, 5, 25, 75, 20,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_10 | JUMP3_FLG_4)),
};

CameraModeValue sSetWhirlpoolModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 320, 350, -5, 12, 5, 25, 65, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_10 | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

CameraModeValue sSetWhirlpoolModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-40, 300, 350, 10, 15, 5, 30, 65, 60,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_20 | JUMP3_FLG_4 | JUMP3_FLG_1)),
};

CameraModeValue sSetWhirlpoolModeDekuHideData[] = {
    JUMP3_FIXED_DATA(0xFFC4, 150, 250, -18, 15, 5, 30, 60, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_10 | JUMP3_FLG_4)),
};

CameraModeValue sSetWhirlpoolModeGoronDashData[] = {
    JUMP3_FIXED_DATA(-40, 220, 260, 5, 8, 5, 20, 75, 35,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_10 | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

/*=====================================================================
 *                   Custom Data: CUCCO_SHACK Setting
 *=====================================================================
 */

CameraModeValue sSetCuccoShackModeNormalData[] = {
    NORM1_FIXED_DATA(0xFFBA, 250, 0x01F4, 5, 30, 12, 45, 50, 70,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetCuccoShackModeStillData[] = {
    NORM1_FIXED_DATA(-40, 250, 0x01F4, 5, 100, 100, 100, 50, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetCuccoShackModeDekuHideData[] = {
    NORM1_FIXED_DATA(-40, 250, 0x01F4, 5, 25, 12, 40, 50, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: GIANT Setting
 *=====================================================================
 */

CameraModeValue sSetGiantModeNormalData[] = {
    NORM1_FIXED_DATA(-40, 150, 160, -15, 25, 14, 50, 50, 70,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetGiantModeTargetData[] = {
    PARA1_FIXED_DATA(-40, 180, 80, 0, 0, 5, 5, 50, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 60, 0),
};

CameraModeValue sSetGiantModeJumpData[] = {
    NORM1_FIXED_DATA(-10, 100, 150, 10, 30, 10, 40, 70, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetGiantModeStillData[] = {
    NORM1_FIXED_DATA(-40, 150, 160, 0xFFF4, 25, 14, 50, 50, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

/*=====================================================================
 *                   Custom Data: SCENE0 Setting
 *=====================================================================
 */

CameraModeValue D_801B6FA0[] = {
    UNIQ2_FIXED_DATA(-40, 20, 60, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | UNIQ2_FLG_20 | UNIQ2_FLG_10 | UNIQ2_FLG_2)),
};

/*=====================================================================
 *                   Custom Data: ROOM1 Setting
 *=====================================================================
 */

CameraModeValue D_801B6FB0[] = {
    NORM1_FIXED_DATA(-15, 120, 250, 16, 16, 5, 65, 60, 75,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B6FD8[] = {
    KEEP1_FIXED_DATA(-20, 100, 150, 0, 4, 20, 10, 40, 60, 60, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_1), 20),
};

CameraModeValue D_801B7008[] = {
    BATT1_FIXED_DATA(-25, 100, 180, 10, 40, 10, 0, 40, 60, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_2), 20,
                     50),
};

CameraModeValue D_801B703C[] = {
    NORM1_FIXED_DATA(-15, 120, 250, 16, 12, 5, 60, 70, 40,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B7064[] = {
    NORM1_FIXED_DATA(-15, 120, 250, 16, 100, 100, 100, 70, 20,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_20 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue D_801B708C[] = {
    PARA1_FIXED_DATA(0, 200, 5, 30, 0, 5, 5, 70, 30,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_20 | PARA1_FLG_2), 80, 0),
};

/*=====================================================================
 *                   Custom Data: WATER2 Setting
 *=====================================================================
 */

CameraModeValue D_801B70BC[] = {
    JUMP3_FIXED_DATA(-10, 270, 300, 20, 30, 20, 65, 60, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_80 | JUMP3_FLG_4)),
};

CameraModeValue D_801B70E4[] = {
    PARA1_FIXED_DATA(-30, 280, 40, 10, 0, 15, 5, 60, 100,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2 | PARA1_FLG_1), 60, 0),
};

CameraModeValue D_801B7114[] = {
    KEEP3_FIXED_DATA(-20, 50, 100, 50, 5, 20, 10, 40, 45, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5)), 60),
};

CameraModeValue D_801B7148[] = {
    JUMP3_FIXED_DATA(-40, 180, 200, 5, 20, 5, 40, 75, 35,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | JUMP3_FLG_8 | JUMP3_FLG_4)),
};

/*=====================================================================
 *                   Custom Data: FORCEKEEP Setting
 *=====================================================================
 */

CameraModeValue D_801B7170[] = {
    KEEP1_FIXED_DATA(-30, 180, 200, 20, 40, -5, 10, 15, 45, 60,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | KEEP1_FLG_10 | KEEP1_FLG_1), 30),
};

CameraModeValue D_801B71A0[] = {
    BATT1_FIXED_DATA(-30, 150, 250, 10, 60, -5, 20, 35, 55, 70,
                     (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | BATT1_FLG_10 | BATT1_FLG_2), 25, 40),
};

/*=====================================================================
 *                   Custom Data: PARALLEL1 Setting
 *=====================================================================
 */

CameraModeValue D_801B71D4[] = {
    PARA1_FIXED_DATA(0, 400, 20, 20, 0, 20, 5, 70, 50, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | PARA1_FLG_8 | PARA1_FLG_2),
                     80, 0),
};

/*=====================================================================
 *                   Custom Data: START1 Setting
 *=====================================================================
 */

CameraModeValue D_801B7204[] = {
    UNIQ0_FIXED_DATA(0, 100, (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | UNIQ0_FLG_2)),
};

/*=====================================================================
 *                   Custom Data: ROOM2 Setting
 *=====================================================================
 */

CameraModeValue D_801B7210[] = {
    KEEP3_FIXED_DATA(-10, 120, 180, 50, 5, 10, 5, 70, 35, 50, 20, (SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | KEEP3_FLG_20),
                     60),
};

/*=====================================================================
 *                   Custom Data: NORMAL4 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal4ModeTalkData[] = {
    KEEP3_FIXED_DATA(-20, 0x006E, 160, 80, 15, 10, 0, 70, 40, 50, 20,
                     (SHRINKWINVAL_LARGE | IFACE_ALPHA(5) | KEEP3_FLG_20), 50),
};

/*=====================================================================
 *                   Custom Data: ELEGY_SHELL Setting
 *=====================================================================
 */

CameraModeValue sSetElegyShellModeNormalData[] = {
    KEEP4_FIXED_DATA(-45, 150, -10, 165, 5, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 30),
};

CameraModeValue sSetElegyShellModeJumpData[] = {
    KEEP4_FIXED_DATA(-40, 150, 18, 140, 5, 70, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 30),
};

CameraModeValue sSetElegyShellModeDekuShootData[] = {
    KEEP4_FIXED_DATA(-20, 150, -2, 140, 15, 50, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 30),
};

CameraModeValue sSetElegyShellModeGoronDashData[] = {
    KEEP4_FIXED_DATA(-50, 150, 0xFFF4, 160, 6, 50, (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_2), 25, 30),
};

CameraModeValue sSetElegyShellModeDekuFlyData[] = {
    KEEP4_FIXED_DATA(0xFFC4, 150, 0xFFF4, 0xFF74, 30, 50,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0xF) | KEEP4_FLG_8 | KEEP4_FLG_4), 25, 30),
};

/*=====================================================================
 *                   Custom Data: DUNGEON4 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon4ModeNormalData[] = {
    NORM1_FIXED_DATA(0, 150, 250, -5, 16, 5, 0x0034, 55, 80,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon4ModeTargetData[] = {
    PARA1_FIXED_DATA(0, 200, 25, 5, 0, 5, 5, 45, 50, (SHRINKWINVAL_MEDIUM | IFACE_ALPHA(0) | PARA1_FLG_2), 80, 0),
};

CameraModeValue sSetDungeon4ModeJumpData[] = {
    NORM1_FIXED_DATA(0, 150, 250, 0, 24, 5, 50, 55, 50,
                     (SHRINKWINVAL_NONE | IFACE_ALPHA(0) | NORM1_FLG_80 | NORM1_FLG_8 | NORM1_FLG_2 | NORM1_FLG_1)),
};

CameraModeValue sSetDungeon4ModeStillData[] = {
    NORM1_FIXED_DATA(0, 180, 220, 5, 100, 100, 100, 55, 10,
                     (SHRINKWINVAL_PREV | IFACE_ALPHA(0) | NORM1_FLG_2 | NORM1_FLG_1)),
};

/**
 * =====================================================================
 *    CAMERA SETTINGS: USAGE OF FUNCTIONS AND DATA FOR SPECIFIC MODES
 * =====================================================================
 */

#define CAM_SETTING_MODE_ENTRY(func, data) \
    { func, ARRAY_COUNT(data), data }

#define CAM_SETTING_MODE_NULL \
    { CAM_FUNC_NONE, 0, NULL }

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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal3ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL,
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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronJumpData),
};

CameraMode sCamSetPivotDivingModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ2, sSetPivotDivingModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ2, sSetPivotDivingModeTargetData),
};

CameraMode sCamSetHorseModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeJumpData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetHorseModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetHorseModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetHorseModeSlingShotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetHorseModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetHorseModeBattleData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetHorseModeStillData),
};

CameraMode sCamSetZoraDivingModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM3, sSetZoraDivingModeNormalData),
};

CameraMode sCamSetPreRendFixedModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD3, sSetPrerendFixedModeNormalData),
};

CameraMode sCamSetPreRendPivotModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQ7, sSetPrerendPivotModeNormalData),
};

CameraMode sCamSetDoorCModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC9, sSetDoorCModeNormalData),
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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5034),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5050),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetFixed0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B506C),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetSpiralDoorModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPEC8, sSetSpiralDoorModeNormalData),
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B53C8),
};

CameraMode sCamSetItem1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B53EC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5410),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5458),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5434),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B547C),
};

CameraMode sCamSetItem2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B54A0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B54C4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B550C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B54E8),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5530),
};

CameraMode sCamSetItem3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5554),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5578),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B55C0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B559C),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5698),
};

CameraMode sCamSetDeathModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeDekuShootData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, sSetDeathModeJumpData),
};

CameraMode sCamSetRebirthModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B574C),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP4, D_801B5728),
};

CameraMode sCamSetLongChestOpeningModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO2, sSetLongChestOpeningModeNormalData),
};

CameraMode sCamSetMaskTransformationModes[] = {
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
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA2, sSetMazeModeNormalData),
};

CameraMode sCamSetRemoteBombModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM2, sSetRemoteBombModeNormalData),
};

CameraMode sCamSetCirc1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5884),
};

CameraMode sCamSetCirc2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B58A0),
};

CameraMode sCamSetCirc3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B58BC),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5034),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5050),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetCirc4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B58D8),
};

CameraMode sCamSetFixed3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD1, D_801B58F4),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetTowerClimbModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM0, sSetTowerClimbModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetTowerClimbModeJumpData),
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
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetTowerClimbModeStillData),
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

CameraMode sCamSetBoatCruiseModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetBoatCruiseModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),
};

CameraMode sCamSetVerticalClimbModes[] = {
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
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetVerticalClimbModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetVerticalClimbModeClimbData),
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
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetVerticalClimbModeClimbData),
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
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetMiniBossModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetMiniBossModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetMiniBossModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATT1, sSetMiniBossModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetMiniBossModeStillData),
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

CameraMode sCamSetTreasureChestMinigameModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetTreasureChestMinigameModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetTreasureChestMinigameModeTargetData),
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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetTelescopeModeFirstPersonData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetTelescopeModeTargetData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXD2, D_801B5034),
    CAM_SETTING_MODE_NULL,
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetBossGyorgModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_SLINGSHOT
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeGoronJumpData),
};

CameraMode sCamSetConnect0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO0, D_801B4EF4),
};

CameraMode sCamSetPinnacleRockModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeGoronDashData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetPinnacleRockModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_SLINGSHOT
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLYZ
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, sSetPinnacleRockModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_SLINGSHOT
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
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeGoronJumpData),
};

CameraMode sCamSetCuccoShackModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetCuccoShackModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal2ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORM1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLY
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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJ1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARA1, D_801B70E4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEP3, D_801B7114),
    CAM_SETTING_MODE_NULL,
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
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronJumpData),
};

CameraMode sCamSetWoodfallSwampModes[] = {
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
    CAM_SETTING_MODE_NULL,
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
    { 0x00000000, 0x00000000, NULL },                              // CAM_SET_NONE
    { 0x3FFFFFFF, 0x00000005, sCamSetNormal0Modes },               // CAM_SET_NORMAL0
    { 0x05FFEFF7, 0x00000005, sCamSetNormal3Modes },               // CAM_SET_NORMAL3
    { 0x00000401, 0x00000005, sCamSetPivotDivingModes },           // CAM_SET_PIVOT_DIVING
    { 0x00017E13, 0x80000005, sCamSetHorseModes },                 // CAM_SET_HORSE
    { 0x00000001, 0x80000005, sCamSetZoraDivingModes },            // CAM_SET_ZORA_DIVING
    { 0x00000001, 0x8000000C, sCamSetPreRendFixedModes },          // CAM_SET_PREREND_FIXED
    { 0x00000001, 0x8000000C, sCamSetPreRendPivotModes },          // CAM_SET_PREREND_PIVOT
    { 0x00000001, 0xC0000007, sCamSetDoorCModes },                 // CAM_SET_DOORC
    { 0x00000001, 0xC000000E, sCamSetDemo0Modes },                 // CAM_SET_DEMO0
    { 0x00000001, 0x80000005, sCamSetFree0Modes },                 // CAM_SET_FREE0
    { 0x03FFFFFF, 0x00000005, sCamSetFukan0Modes },                // CAM_SET_BIRDS_EYE_VIEW_0
    { 0x03FFFFFF, 0x00000005, sCamSetNormal1Modes },               // CAM_SET_NORMAL1
    { 0x03FFFFFF, 0x80000005, sCamSetNanameModes },                // CAM_SET_NANAME
    { 0x00001BD9, 0x80000005, sCamSetCirc0Modes },                 // CAM_SET_CIRCLE0
    { 0x000011D9, 0x80000005, sCamSetFixed0Modes },                // CAM_SET_FIXED0
    { 0x00000001, 0x40000005, sCamSetSpiralDoorModes },            // CAM_SET_SPIRAL_DOOR
    { 0x3FFFFFFF, 0x00000005, sCamSetDungeon0Modes },              // CAM_SET_DUNGEON0
    { 0x0000002F, 0x00000005, sCamSetItem0Modes },                 // CAM_SET_ITEM0
    { 0x0000002F, 0x00000005, sCamSetItem1Modes },                 // CAM_SET_ITEM1
    { 0x0000002F, 0x00000005, sCamSetItem2Modes },                 // CAM_SET_ITEM2
    { 0x0000002F, 0x00000005, sCamSetItem3Modes },                 // CAM_SET_ITEM3
    { 0x00000001, 0x00000005, sCamSetNaviModes },                  // CAM_SET_NAVI
    { 0x0000002F, 0x00000005, sCamSetWarp0Modes },                 // CAM_SET_WARP_PAD_MOON
    { 0x0000002F, 0x00000005, sCamSetDeathModes },                 // CAM_SET_DEATH
    { 0x0000002F, 0x00000005, sCamSetRebirthModes },               // CAM_SET_REBIRTH
    { 0x00000001, 0x40000005, sCamSetLongChestOpeningModes },      // CAM_SET_LONG_CHEST_OPENING
    { 0x00000003, 0x00000005, sCamSetMaskTransformationModes },    // CAM_SET_MASK_TRANSFORMATION
    { 0x00000001, 0x00000005, sCamSetAttentionModes },             // CAM_SET_ATTENTION
    { 0x00000001, 0x00000005, sCamSetWarp1Modes },                 // CAM_SET_WARP_PAD_ENTRANCE
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon1Modes },              // CAM_SET_DUNGEON1
    { 0x00000001, 0x80000005, sCamSetFixed1Modes },                // CAM_SET_FIXED1
    { 0x00000001, 0x80000005, sCamSetFixed2Modes },                // CAM_SET_FIXED2
    { 0x00000001, 0x00000005, sCamSetMazeModes },                  // CAM_SET_MAZE
    { 0x00000001, 0x00000005, sCamSetRemoteBombModes },            // CAM_SET_REMOTEBOMB
    { 0x00000001, 0x80000005, sCamSetCirc1Modes },                 // CAM_SET_CIRCLE1
    { 0x00000001, 0x80000005, sCamSetCirc2Modes },                 // CAM_SET_CIRCLE2
    { 0x00001BD9, 0x80000005, sCamSetCirc3Modes },                 // CAM_SET_CIRCLE3
    { 0x00000001, 0x80000005, sCamSetCirc4Modes },                 // CAM_SET_CIRCLE4
    { 0x000011D9, 0x80000005, sCamSetFixed3Modes },                // CAM_SET_FIXED3
    { 0x03FFFFFF, 0x80000005, sCamSetTowerClimbModes },            // CAM_SET_TOWER_ASCENT
    { 0x00000001, 0x80000005, sCamSetParallel0Modes },             // CAM_SET_PARALLEL0
    { 0x00000001, 0x00000005, sCamSetNormDModes },                 // CAM_SET_NORMALD
    { 0x00000001, 0x00000005, sCamSetSubjectDModes },              // CAM_SET_SUBJECTD
    { 0x00000001, 0xC0000008, sCamSetStart0Modes },                // CAM_SET_START0
    { 0x00000001, 0xC0000008, sCamSetStart2Modes },                // CAM_SET_START2
    { 0x00000001, 0x00000005, sCamSetStop0Modes },                 // CAM_SET_STOP0
    { 0x00003051, 0x00000005, sCamSetBoatCruiseModes },            // CAM_SET_BOAT_CRUISE
    { 0x03FFFFFF, 0x00000005, sCamSetVerticalClimbModes },         // CAM_SET_VERTICAL_CLIMB
    { 0x00000001, 0x00000005, sCamSetSidedModes },                 // CAM_SET_SIDED
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon2Modes },              // CAM_SET_DUNGEON2
    { 0x03FFFFFF, 0x00000005, sCamSetBossOdolwaModes },            // CAM_SET_BOSS_ODOLWA
    { 0x03FFFFFF, 0x80000005, sCamSetKeepBackModes },              // CAM_SET_KEEPBACK
    { 0x00000001, 0x80000005, sCamSetCirc6Modes },                 // CAM_SET_CIRCLE6
    { 0x00000001, 0x80000005, sCamSetCirc7Modes },                 // CAM_SET_CIRCLE7
    { 0x03FFFFFF, 0x00000005, sCamSetMiniBossModes },              // CAM_SET_MINI_BOSS
    { 0x00000001, 0x80000005, sCamSetRFixed1Modes },               // CAM_SET_RFIXED1
    { 0x00000401, 0x00000005, sCamSetTreasureChestMinigameModes }, // CAM_SET_TREASURE_CHEST_MINIGAME
    { 0x00000001, 0x80000005, sCamSetBombBasketModes },            // CAM_SET_HONEY_AND_DARLING_1
    { 0x00000001, 0x80000005, sCamSetCirc8Modes },                 // CAM_SET_CIRCLE8
    { 0x03FFFFFF, 0x00000005, sCamSetFukan1Modes },                // CAM_SET_BIRDS_EYE_VIEW_1
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon3Modes },              // CAM_SET_DUNGEON3
    { 0x00008441, 0x0000000A, sCamSetTelescopeModes },             // CAM_SET_TELESCOPE
    { 0x3FFFFFFF, 0x00000005, sCamSetRoom0Modes },                 // CAM_SET_ROOM0
    { 0x00000001, 0x80000005, sCamSetRCirc0Modes },                // CAM_SET_RCIRC0
    { 0x00001BD9, 0x80000005, sCamSetCirc9Modes },                 // CAM_SET_CIRCLE9
    { 0x03FFFFFF, 0x00000005, sCamSetOnThePoleModes },             // CAM_SET_ONTHEPOLE
    { 0x03FFFFFF, 0x00000005, sCamSetInBushModes },                // CAM_SET_INBUSH
    { 0x03FFFFFF, 0x00000005, sCamSetBossMajoraModes },            // CAM_SET_BOSS_MAJORA
    { 0x03FFFFFF, 0x00000005, sCamSetBossTwinmoldModes },          // CAM_SET_BOSS_TWINMOLD
    { 0x03FFFFFF, 0x00000005, sCamSetBossGohtModes },              // CAM_SET_BOSS_GOHT
    { 0x05FFEFF7, 0x00000005, sCamSetBossGyorgModes },             // CAM_SET_BOSS_GYORG
    { 0x00000001, 0x00000005, sCamSetConnect0Modes },              // CAM_SET_CONNECT0
    { 0x05FFEFF7, 0x00000005, sCamSetPinnacleRockModes },          // CAM_SET_PINNACLE_ROCK
    { 0x03FFFFFF, 0x00000005, sCamSetNormal2Modes },               // CAM_SET_NORMAL2
    { 0x03FFFFFF, 0x00000005, sCamSetBombBowlModes },              // CAM_SET_HONEY_AND_DARLING_2
    { 0x00000001, 0x80000005, sCamSetCircAModes },                 // CAM_SET_CIRCLEA
    { 0x05FFEFF7, 0x00000005, sCamSetWhirlpoolModes },             // CAM_SET_WHIRLPOOL
    { 0x01FFFFDF, 0x00000005, sCamSetCuccoShackModes },            // CAM_SET_CUCCO_SHACK
    { 0x03FFFFFF, 0x00000005, sCamSetGiantModes },                 // CAM_SET_GIANT
    { 0x00000001, 0x00000008, sCamSetScene0Modes },                // CAM_SET_SCENE0
    { 0x03FFFFFF, 0x00000005, sCamSetRoom1Modes },                 // CAM_SET_ROOM1
    { 0x05FFEFF7, 0x00000005, sCamSetWater2Modes },                // CAM_SET_WATER2
    { 0x03FFFFFF, 0x00000005, sCamSetWoodfallSwampModes },         // CAM_SET_WOODFALL_SWAMP
    { 0x03FFFFFF, 0x00000005, sCamSetForceKeepModes },             // CAM_SET_FORCEKEEP
    { 0x03FFFFFF, 0x80000005, sCamSetParallel1Modes },             // CAM_SET_PARALLEL1
    { 0x00000001, 0xC0000008, sCamSetStart1Modes },                // CAM_SET_START1
    { 0x03FFFFFF, 0x00000005, sCamSetRoom2Modes },                 // CAM_SET_ROOM2
    { 0x03FFFFFF, 0x00000005, sCamSetNorm4Modes },                 // CAM_SET_NORMAL4
    { 0x0000002F, 0x00000005, sCamSetElegyShellModes },            // CAM_SET_ELEGY_SHELL
    { 0x03FFFFFF, 0x00000005, sCamSetDungeon4Modes },              // CAM_SET_DUNGEON4
};

static s16 sGlobalCamDataSettings[26] = {
    /* -25 */ CAM_SET_ELEGY_SHELL,
    /* -24 */ CAM_SET_SIDED,
    /* -23 */ CAM_SET_BOAT_CRUISE,
    /* -22 */ CAM_SET_NONE,
    /* -21 */ CAM_SET_SUBJECTD,
    /* -20 */ CAM_SET_NORMALD,
    /* -19 */ CAM_SET_NONE,
    /* -18 */ CAM_SET_NONE,
    /* -17 */ CAM_SET_NONE,
    /* -16 */ CAM_SET_WARP_PAD_ENTRANCE,
    /* -15 */ CAM_SET_ATTENTION,
    /* -14 */ CAM_SET_CONNECT0,
    /* -13 */ CAM_SET_REMOTEBOMB,
    /* -12 */ CAM_SET_NONE,
    /* -11 */ CAM_SET_MASK_TRANSFORMATION,
    /* -10 */ CAM_SET_LONG_CHEST_OPENING,
    /* -09 */ CAM_SET_REBIRTH,
    /* -08 */ CAM_SET_DEATH,
    /* -07 */ CAM_SET_WARP_PAD_MOON,
    /* -06 */ CAM_SET_NAVI,
    /* -05 */ CAM_SET_ITEM3,
    /* -04 */ CAM_SET_ITEM2,
    /* -03 */ CAM_SET_ITEM1,
    /* -02 */ CAM_SET_ITEM0,
    /* -01 */ CAM_SET_STOP0,
    /*  0  */ CAM_SET_NONE,
};

static s16* sGlobalCamDataSettingsPtr = &sGlobalCamDataSettings[25];

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

s32 (*sCameraActionFunctions[])(Camera*) = {
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

static s32 sUpdateCameraDirection = false;
static s32 sIsFalse = false;
static s32 sCameraInitSceneTimer = 0;
