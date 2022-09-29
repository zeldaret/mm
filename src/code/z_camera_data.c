#include "ultra64.h"
#include "global.h"

/*=====================================================================
 *                   Default Data: NORMAL0 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal0ModeNormalData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 22, 15, 40, 60, 84,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal0ModeTargetData[] = {
    PARALLEL1_FIXED_DATA(0, 350, 50, 0, 0, 5, 5, 45, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue sSetNormal0ModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(-30, 180, 200, 20, 40, -5, 10, 15, 45, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue sSetNormal0ModeBattleData[] = {
    BATTLE1_FIXED_DATA(-30, 150, 250, 10, 60, -5, 20, 35, 55, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 40),
};

CameraModeValue sSetNormal0ModeFirstPersonData[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 45, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeTalkData[] = {
    KEEPON3_FIXED_DATA(-20, 80, 150, 50, 5, 20, 5, 40, 35, 50, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, 0),
                       60),
};

CameraModeValue sSetNormal0ModeClimbData[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 5, 5, 60, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeBowArrowData[] = {
    SUBJECT1_FIXED_DATA(0xFFF9, 0xE, 50, 10, 0, -30, -5, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeBowArrowZData[] = {
    SUBJECT1_FIXED_DATA(20, 70, 70, 10, 0xFF88, 20, 0, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeHookshotData[] = {
    SPECIAL5_FIXED_DATA(-20, 80, 250, 45, 60, 40, 6,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeBoomerangData[] = {
    SUBJECT1_FIXED_DATA(5, 50, 50, 10, 0, 0, 0, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeSlingshotData[] = {
    SUBJECT1_FIXED_DATA(0xFFF9, 14, 50, 10, 0, -50, -10, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeClimbZData[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 999, 5, 60, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, JUMP2_FLAG_2 | JUMP2_FLAG_1)),
};

CameraModeValue sSetNormal0ModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 240, 340, 10, 30, 12, 40, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal0ModeHangData[] = {
    PARALLEL1_FIXED_DATA(-40, 320, 50, 40, 0, 8, 5, 60, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         60, 12),
};

CameraModeValue sSetNormal0ModeHangZData[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 300, 50, 70, 0, 12, 5, 45, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         60, 2),
};

CameraModeValue sSetNormal0ModeFreeFallData[] = {
    PARALLEL1_FIXED_DATA(
        -10, 320, 100, 70, 0, 4, 5, 70, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_7 | PARALLEL1_FLAG_3), 60, 12),
};

CameraModeValue sSetNormal0ModeChargeData[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 300, -20, 50, 0, 50, 5, 80, 20,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0), 60, 10),
};

CameraModeValue sSetNormal0ModeChargeZData[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 300, -20, 40, 0, 50, 5, 80, 20,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue sSetNormal0ModeStillData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal0ModePushPullData[] = {
    PARALLEL1_FIXED_DATA(
        0, 350, 5, 45, 0, 5, 5, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 80, 0),
};

CameraModeValue sSetNormal0ModeFollowBoomerangData[] = {
    KEEPON1_FIXED_DATA(-5, 220, 240, 5, 75, 10, 5, 40, 50, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue sSetNormal0ModeDekuShootData[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 10, 0, 50, 65, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetNormal0ModeGoronDashData[] = {
    NORMAL1_FIXED_DATA(50, 160, 255, -2, 12, 10, 40, 92, 88,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_2 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal0ModeDekuHideData[] = {
    PARALLEL1_FIXED_DATA(
        100, 300, -20, 40, 0, 4, 5, 80, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 80,
        20),
};

CameraModeValue sSetNormal0ModeDekuFlyData[] = {
    NORMAL1_FIXED_DATA(0xFFB0, 280, 320, 40, 20, 12, 40, 80, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal0ModeDekuFlyZData[] = {
    PARALLEL1_FIXED_DATA(0xFFBA, 350, 10, 10, 0, 5, 5, 70, 90,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_3 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         90, 0),
};

CameraModeValue sSetNormal0ModeGoronJumpData[] = {
    NORMAL1_FIXED_DATA(
        -10, 160, 400, 0, 18, 12, 40, 80, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                            NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_2 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal0ModeZoraFinData[] = {
    SUBJECT1_FIXED_DATA(5, 100, 100, 10, 0, 0, 0, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *                   Custom Data: NORMAL3 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal3ModeNormalData[] = {
    JUMP3_FIXED_DATA(-40, 280, 300, 20, 15, 5, 40, 60, 100,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2)),
};

CameraModeValue sSetNormal3ModeTargetData[] = {
    PARALLEL1_FIXED_DATA(
        -50, 280, 40, 10, 0, 15, 5, 60, 100,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1 | PARALLEL1_FLAG_0), 80, 0),
};

CameraModeValue sSetNormal3ModeFreeFallData[] = {
    JUMP3_FIXED_DATA(0, 80, 100, 30, 10, 5, 40, 80, 20,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_2)),
};

CameraModeValue sSetNormal3ModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 150, 240, -5, 18, 5, 40, 70, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

CameraModeValue sSetNormal3ModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-40, 150, 250, 10, 18, 5, 60, 60, 60,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetNormal3ModeDekuHideData[] = {
    JUMP3_FIXED_DATA(
        0xFFC4, 150, 250, -15, 18, 5, 60, 60, 40,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetNormal3ModeStillData[] = {
    NORMAL1_FIXED_DATA(-40, 80, 300, 20, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal3ModeGoronDashData[] = {
    JUMP3_FIXED_DATA(-40, 180, 200, 5, 20, 5, 40, 80, 35,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

/*=====================================================================
 *                Custom Data: PIVOT_DIVING Setting
 *=====================================================================
 */

CameraModeValue sSetPivotDivingModeNormalData[] = {
    UNIQUE2_FIXED_DATA(-40, 60, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, UNIQUE2_FLAG_1)),
};

CameraModeValue sSetPivotDivingModeTargetData[] = {
    UNIQUE2_FIXED_DATA(-30, 45, 100, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, UNIQUE2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: HORSE Setting
 *=====================================================================
 */

CameraModeValue sSetHorseModeNormalData[] = {
    NORMAL3_FIXED_DATA(-50, 220, 250, 10, 10, 20, 60, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE,
                                           NORMAL3_FLAG_5)),
};

CameraModeValue sSetHorseModeTargetData[] = {
    NORMAL3_FIXED_DATA(-40, 180, 200, -3, 2, 100, 50, 90,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM,
                                           CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE, NORMAL3_FLAG_1)),
};

CameraModeValue sSetHorseModeJumpData[] = {
    NORMAL3_FIXED_DATA(
        -50, 220, 260, 10, 10, 20, 60, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE, 0)),
};

CameraModeValue sSetHorseModeBowArrowData[] = {
    SUBJECT1_FIXED_DATA(
        0xFFF9, 14, 100, 10, 0, -30, -5, 40,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE, 0)),
};

CameraModeValue sSetHorseModeSlingShotData[] = {
    SUBJECT1_FIXED_DATA(0xFFF9, 14, 100, 10, 0, -50, -10, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetHorseModeBattleData[] = {
    BATTLE1_FIXED_DATA(0xFFC4, 180, 280, 10, 60, -5, 20, 60, 60, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 40),
};

CameraModeValue sSetHorseModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(0xFFC4, 180, 220, 25, 45, -5, 15, 15, 45, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM,
                                           CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE, KEEPON1_FLAG_0),
                       20),
};

CameraModeValue sSetHorseModeTalkData[] = {
    KEEPON3_FIXED_DATA(-50, 140, 200, 40, 10, 0, 5, 100, 45, 50, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, 0),
                       60),
};

CameraModeValue sSetHorseModeStillData[] = {
    NORMAL3_FIXED_DATA(-40, 180, 200, -3, 100, 100, 60, 10,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, NORMAL3_FLAG_7)),
};

/*=====================================================================
 *                Custom Data: ZORA_DIVING Setting
 *=====================================================================
 */

CameraModeValue sSetZoraDivingModeNormalData[] = {
    NORMAL3_FIXED_DATA(-20, 250, 250, 0, 20, 20, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE,
                                           NORMAL3_FLAG_7)),
};

/*=====================================================================
 *                Custom Data: PREREND_FIXED Setting
 *=====================================================================
 */

CameraModeValue sSetPrerendFixedModeNormalData[] = {
    FIXED3_FIXED_DATA(CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *                   Custom Data: PREREND_PIVOT Setting
 *=====================================================================
 */

CameraModeValue sSetPrerendPivotModeNormalData[] = {
    UNIQUE7_FIXED_DATA(60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *                   Custom Data: DOORC Setting
 *=====================================================================
 */

CameraModeValue sSetDoorCModeNormalData[] = {
    SPECIAL9_FIXED_DATA(-5, 60,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE_4, CAM_HUD_VISIBILITY_NONE_ALT, SPECIAL9_FLAG_1)),
};

/*=====================================================================
 *                   Custom Data: DEMO0 Setting
 *=====================================================================
 */

CameraModeValue D_801B4EF0[] = {
    FLAGS_FIXED_DATA(CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_NONE_ALT, 0)),
};

/*=====================================================================
 *                   Custom Data: Various Cutscenes
 *=====================================================================
 */

// Camera Settings: FREE0, NAVI, TRANSFORM, ATTENTION, WARP1, STOP0,  CONNECT0
CameraModeValue sSetCutscenesModeNormalData[] = {
    FLAGS_FIXED_DATA(CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0)),
};

/*=====================================================================
 *                   Custom Data: FUKAN0 Setting
 *=====================================================================
 */

CameraModeValue D_801B4EF8[] = {
    NORMAL1_FIXED_DATA(
        -40, 600, 600, 45, 50, 10, 50, 45, 90,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_6 | NORMAL1_FLAG_1)),
};

CameraModeValue D_801B4F20[] = {
    PARALLEL1_FIXED_DATA(-40, 400, 25, 60, 0, 5, 5, 60, 60,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 80, 0),
};

CameraModeValue D_801B4F50[] = {
    NORMAL1_FIXED_DATA(-40, 600, 600, 45, 50, 10, 50, 45, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B4F78[] = {
    NORMAL1_FIXED_DATA(-40, 600, 600, 45, 100, 100, 100, 45, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: NORMAL1 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal1ModeNormalData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 15, 18, 12, 70, 60, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_1)),
};

CameraModeValue sSetNormal1ModeStillData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 15, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: NANAME Setting
 *=====================================================================
 */

// Normal4
CameraModeValue D_801B4FF0[] = {
    NORMAL1_FIXED_DATA(
        -20, 280, 320, 10, 18, 12, 40, 60, 80,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5018[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 10, 20, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, FIXED2_FLAG_0)),
};

CameraModeValue D_801B5034[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 100, 80, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, FIXED2_FLAG_6)),
};

CameraModeValue D_801B5050[] = {
    FIXED2_FIXED_DATA(-40, 40, 200, 100, 50, 45,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, FIXED2_FLAG_7)),
};

/*=====================================================================
 *                   Custom Data: FIXED0 Setting
 *=====================================================================
 */

CameraModeValue D_801B506C[] = {
    FIXED1_FIXED_DATA(-40, 10, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *                 Custom Data: SPIRAL_DOOR Setting
 *=====================================================================
 */

CameraModeValue sSetSpiralDoorModeNormalData[] = {
    SPECIAL8_FIXED_DATA(-40, 50, 80, 60, 10,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, SPECIAL8_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: DUNGEON0 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon0ModeNormalData[] = {
    NORMAL1_FIXED_DATA(-20, 150, 250, 5, 18, 5, 45, 60, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon0ModeTargetData[] = {
    PARALLEL1_FIXED_DATA(
        0, 200, 25, 5, 0, 5, 5, 45, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_6 | PARALLEL1_FLAG_1), 80, 0),
};

CameraModeValue sSetDungeon0ModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(-20, 120, 140, 25, 45, -5, 15, 15, 45, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 20),
};

CameraModeValue sSetDungeon0ModeBattleData[] = {
    BATTLE1_FIXED_DATA(-30, 150, 240, 10, 50, 5, 10, 25, 50, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 50),
};

CameraModeValue sSetDungeon0ModeFollowBoomerangData[] = {
    KEEPON1_FIXED_DATA(-5, 150, 240, 5, 65, 10, 5, 40, 55, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue sSetDungeon0ModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 150, 250, 5, 24, 5, 50, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon0ModeFreeFallData[] = {
    PARALLEL1_FIXED_DATA(
        -10, 250, 100, 70, 0, 4, 5, 70, 10,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_7 | PARALLEL1_FLAG_3), 70, 12),
};

CameraModeValue sSetDungeon0ModeClimbData[] = {
    JUMP2_FIXED_DATA(-40, 150, 250, 20, 5, 5, 60, 20,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue sSetDungeon0ModeClimbZData[] = {
    JUMP2_FIXED_DATA(-40, 250, 250, 20, 999, 5, 60, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, JUMP2_FLAG_2 | JUMP2_FLAG_1)),
};

CameraModeValue sSetDungeon0ModeChargeData[] = {
    PARALLEL1_FIXED_DATA(0, 250, -20, 50, 0, 50, 5, 60, 20,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0), 60, 10),
};

CameraModeValue sSetDungeon0ModeChargeZData[] = {
    PARALLEL1_FIXED_DATA(50, 250, -20, 40, 0, 50, 5, 80, 20,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue sSetDungeon0ModeHangData[] = {
    PARALLEL1_FIXED_DATA(-40, 220, 50, 40, 0, 12, 5, 60, 10,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         60, 12),
};

CameraModeValue sSetDungeon0ModeHangZData[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 250, 50, 70, 0, 10, 5, 45, 10,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         60, 2),
};

CameraModeValue sSetDungeon0ModeStillData[] = {
    NORMAL1_FIXED_DATA(
        -10, 180, 220, 10, 100, 100, 100, 60, 10,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon0ModePushPullData[] = {
    PARALLEL1_FIXED_DATA(
        0, 250, 5, 30, 0, 5, 5, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 80, 0),
};

/*=====================================================================
 *                   Custom Data: ITEM0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5338[] = {
    KEEPON4_FIXED_DATA(5, 70, 25, 0, 0, 45,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B535C[] = {
    KEEPON4_FIXED_DATA(-30, 35, 40, 0, 6, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B5380[] = {
    KEEPON4_FIXED_DATA(-15, 90, -8, 0, 0, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B53A4[] = {
    KEEPON4_FIXED_DATA(20, 45, 0x0037, 0, 12, 55,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B53C8[] = {
    KEEPON4_FIXED_DATA(10, 70, 30, 0, 4, 42,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

/*=====================================================================
 *                   Custom Data: ITEM1 Setting
 *=====================================================================
 */

CameraModeValue D_801B53EC[] = {
    KEEPON4_FIXED_DATA(-45, 75, 0xFFF4, 165, 5, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B5410[] = {
    KEEPON4_FIXED_DATA(-40, 70, 20, 140, 5, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B5434[] = {
    KEEPON4_FIXED_DATA(-20, 85, -5, 140, 15, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B5458[] = {
    KEEPON4_FIXED_DATA(-50, 0x005F, -15, 160, 6, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B547C[] = {
    KEEPON4_FIXED_DATA(
        0xFFC4, 70, -15, 0xFF74, 30, 70,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_3 | KEEPON4_FLAG_2), 25, 6),
};

/*=====================================================================
 *                   Custom Data: ITEM2 Setting
 *=====================================================================
 */

CameraModeValue D_801B54A0[] = {
    KEEPON4_FIXED_DATA(-40, 0x006E, 5, 150, 5, 65,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B54C4[] = {
    KEEPON4_FIXED_DATA(0xFFC4, 0x0082, -10, 0x00AA, 5, 65,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B54E8[] = {
    KEEPON4_FIXED_DATA(-40, 0x006E, 0, 140, 5, 65,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B550C[] = {
    KEEPON4_FIXED_DATA(-50, 140, -10, 160, 5, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B5530[] = {
    KEEPON4_FIXED_DATA(0xFFC4, 120, -8, 150, 5, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

/*=====================================================================
 *                   Custom Data: ITEM3 Setting
 *=====================================================================
 */

CameraModeValue D_801B5554[] = {
    KEEPON4_FIXED_DATA(
        -15, 65, 50, 0xFF65, 5, 75,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_3 | KEEPON4_FLAG_2), 25, 6),
};

CameraModeValue D_801B5578[] = {
    KEEPON4_FIXED_DATA(
        -20, 60, 50, 0xFF65, 5, 75,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_3 | KEEPON4_FLAG_2), 25, 6),
};

CameraModeValue D_801B559C[] = {
    KEEPON4_FIXED_DATA(-15, 60, 40, 0x00AA, 5, 75,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 6),
};

CameraModeValue D_801B55C0[] = {
    KEEPON4_FIXED_DATA(
        -25, 0x005F, 50, 0xFF65, 5, 75,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_3 | KEEPON4_FLAG_2), 25, 6),
};

CameraModeValue D_801B55E4[] = {
    KEEPON4_FIXED_DATA(
        -20, 75, 45, 0xFF6A, -5, 75,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_3 | KEEPON4_FLAG_2), 25, 6),
};

/*=====================================================================
 *                   Custom Data: WARP0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5608[] = {
    KEEPON4_FIXED_DATA(-45, 165, 0, 0x00B2, 0, 45,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE,
                                           KEEPON4_FLAG_6 | KEEPON4_FLAG_3 | KEEPON4_FLAG_2 | KEEPON4_FLAG_1),
                       30, 10),
};

CameraModeValue D_801B562C[] = {
    KEEPON4_FIXED_DATA(0xFFC9, 180, 0, 0x00B2, 0, 45,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE,
                                           KEEPON4_FLAG_6 | KEEPON4_FLAG_3 | KEEPON4_FLAG_2 | KEEPON4_FLAG_1),
                       30, 10),
};

CameraModeValue D_801B5650[] = {
    KEEPON4_FIXED_DATA(-20, 0x00AF, 0, 0x00B2, 0, 45,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE,
                                           KEEPON4_FLAG_6 | KEEPON4_FLAG_3 | KEEPON4_FLAG_2 | KEEPON4_FLAG_1),
                       30, 10),
};

CameraModeValue D_801B5674[] = {
    KEEPON4_FIXED_DATA(-50, 220, 0, 0x00B2, 0, 45,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE,
                                           KEEPON4_FLAG_6 | KEEPON4_FLAG_3 | KEEPON4_FLAG_2 | KEEPON4_FLAG_1),
                       30, 10),
};

CameraModeValue D_801B5698[] = {
    KEEPON4_FIXED_DATA(0xFFC4, 200, 0, 0x00B2, 0, 45,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE,
                                           KEEPON4_FLAG_6 | KEEPON4_FLAG_3 | KEEPON4_FLAG_2 | KEEPON4_FLAG_1),
                       30, 10),
};

/*=====================================================================
 *                   Custom Data: DEATH Setting
 *=====================================================================
 */

CameraModeValue sSetDeathModeNormalData[] = {
    KEEPON4_FIXED_DATA(0xFFBA, 160, 0, 0, 10, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0), 5, 100),
};

CameraModeValue sSetDeathModeJumpData[] = {
    KEEPON4_FIXED_DATA(0xFFBA, 160, 0, 0, 5, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0), 5, 100),
};

CameraModeValue sSetDeathModeDekuShootData[] = {
    KEEPON4_FIXED_DATA(0xFFBA, 150, 0, 0, 5, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0), 5, 100),
};

/*=====================================================================
 *                   Custom Data: REBIRTH Setting
 *=====================================================================
 */

CameraModeValue D_801B5728[] = {
    KEEPON4_FIXED_DATA(
        0xFFC4, 160, 30, 160, 10, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_2 | KEEPON4_FLAG_1), 5, 100),
};

CameraModeValue D_801B574C[] = {
    KEEPON4_FIXED_DATA(
        -20, 140, 30, 160, 10, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_2 | KEEPON4_FLAG_1), 5, 100),
};

/*=====================================================================
 *                   Custom Data: LONG_CHEST_OPENING Setting
 *=====================================================================
 */

CameraModeValue sSetLongChestOpeningModeNormalData[] = {
    DEMO2_FIXED_DATA(60, 30, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0)),
};

/*=====================================================================
 *                   Custom Data: DUNGEON1 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon1ModeNormalData[] = {
    NORMAL1_FIXED_DATA(-20, 350, 400, 45, 50, 20, 70, 50, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon1ModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 350, 400, 40, 50, 20, 50, 50, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon1ModeStillData[] = {
    NORMAL1_FIXED_DATA(-20, 350, 400, 45, 100, 100, 100, 50, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon1ModePushPullData[] = {
    PARALLEL1_FIXED_DATA(
        0, 250, 5, 30, 0, 5, 5, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 30, 0),
};

/*=====================================================================
 *                   Custom Data: FIXED1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5824[] = {
    FIXED1_FIXED_DATA(-40, 100, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0)),
};

/*=====================================================================
 *                   Custom Data: FIXED2 Setting
 *=====================================================================
 */

CameraModeValue D_801B5834[] = {
    FIXED1_FIXED_DATA(-40, 10, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0)),
};

/*=====================================================================
 *                   Custom Data: MAZE Setting
 *=====================================================================
 */

CameraModeValue sSetMazeModeNormalData[] = {
    PARALLEL2_FIXED_DATA(0xFFDD, 160, 65, -5, 2, 70, 99,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL2_FLAG_1)),
};

/*=====================================================================
 *                   Custom Data: REMOTEBOMB Setting
 *=====================================================================
 */

CameraModeValue sSetRemoteBombModeNormalData[] = {
    NORMAL2_FIXED_DATA(20, 200, 800, 15, 6, 70, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL2_FLAG_1)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5884[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 10, 20, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE2 Setting
 *=====================================================================
 */

CameraModeValue D_801B58A0[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 100, 80, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE3 Setting
 *=====================================================================
 */

CameraModeValue D_801B58BC[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 100, 80, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE4 Setting
 *=====================================================================
 */

CameraModeValue D_801B58D8[] = {
    FIXED2_FIXED_DATA(
        -40, 40, 0x3200, 100, 10, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED2_FLAG_3 | FIXED2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: FIXED3 Setting
 *=====================================================================
 */

CameraModeValue D_801B58F4[] = {
    FIXED1_FIXED_DATA(-40, 100, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *             Custom Data: CAM_SET_TOWER_ASCENT Setting
 *=====================================================================
 */

CameraModeValue sSetTowerClimbModeNormalData[] = {
    NORMAL0_FIXED_DATA(0, 350, 400, 20, 20, 50, 65, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL0_FLAG_0)),
};

CameraModeValue sSetTowerClimbModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 340, 400, 10, 30, 12, 40, 65, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetTowerClimbModeStillData[] = {
    NORMAL1_FIXED_DATA(0, 350, 400, 10, 100, 100, 100, 65, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: PARALLEL0 Setting
 *=====================================================================
 */

CameraModeValue D_801B5978[] = {
    PARALLEL1_FIXED_DATA(
        0, 400, 20, 0, 0, 20, 5, 70, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_3 | PARALLEL1_FLAG_1), 80, 0),
};

/*=====================================================================
 *                   Custom Data: NORMALD Setting
 *=====================================================================
 */

CameraModeValue D_801B59A8[] = {
    NORMAL1_FIXED_DATA(
        0, 400, 0x01F4, 15, 18, 12, 35, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: SUBJECTD Setting
 *=====================================================================
 */

CameraModeValue D_801B59D0[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 10, 0, 0, 10, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, 0)),
};

/*=====================================================================
 *                   Custom Data: START0 Setting
 *=====================================================================
 */

CameraModeValue D_801B59F4[] = {
    UNIQUE0_FIXED_DATA(0, 100, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, UNIQUE0_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: START2 Setting
 *=====================================================================
 */

CameraModeValue D_801B5A00[] = {
    UNIQUE0_FIXED_DATA(
        0, 30, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, UNIQUE0_FLAG_4 | UNIQUE0_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: BOAT_CRUISE Setting
 *=====================================================================
 */

CameraModeValue sSetBoatCruiseModeNormalData[] = {
    SUBJECT1_FIXED_DATA(20, 90, 80, 10, 0, 50, 0xFF38, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

/*=====================================================================
 *                   Custom Data: VERTICAL_CLIMB Setting
 *=====================================================================
 */

CameraModeValue sSetVerticalClimbModeClimbData[] = {
    PARALLEL1_FIXED_DATA_ALT(0, 400, 50, 0, 0, 5, 5, 45, 50,
                             CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 70, 0,
                             50),
};

/*=====================================================================
 *                   Custom Data: SIDED Setting
 *=====================================================================
 */

CameraModeValue D_801B5A64[] = {
    PARALLEL1_FIXED_DATA(0, 400, 10, 0, 0xFFA6, 20, 5, 70, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_5 | PARALLEL1_FLAG_3 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         70, 0),
};

/*=====================================================================
 *                   Custom Data: DUNGEON2 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon2ModeNormalData[] = {
    NORMAL1_FIXED_DATA(-10, 270, 300, 20, 0x001C, 20, 65, 60, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon2ModeBattleData[] = {
    BATTLE1_FIXED_DATA(-40, 200, 240, 50, 20, 5, 10, 20, 50, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 40),
};

CameraModeValue sSetDungeon2ModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 270, 300, 40, 50, 20, 50, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon2ModeStillData[] = {
    NORMAL1_FIXED_DATA(-10, 270, 300, 20, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon2ModePushPullData[] = {
    PARALLEL1_FIXED_DATA(
        0, 200, 5, 15, 0, 5, 5, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 30, 0),
};

/*=====================================================================
 *                   Custom Data: BOSS_ODOLWA Setting
 *=====================================================================
 */

CameraModeValue sSetBossOdolwaModeNormalData[] = {
    NORMAL1_FIXED_DATA(-20, 250, 350, 10, 24, 12, 40, 65, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossOdolwaModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(-50, 300, 350, 10, 20, 5, 12, 70, 60, 30,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0), 20),
};

CameraModeValue sSetBossOdolwaModeTalkData[] = {
    KEEPON3_FIXED_DATA(
        -20, 230, 260, 20, 10, 20, 15, 40, 55, 20, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, KEEPON3_FLAG_5), 40),
};

CameraModeValue sSetBossOdolwaModeBattleData[] = {
    BATTLE1_FIXED_DATA(0xFFC4, 200, 220, 20, 10, 0, 10, 60, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 10, 40),
};

CameraModeValue sSetBossOdolwaModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 250, 350, 10, 30, 12, 40, 65, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossOdolwaModeStillData[] = {
    NORMAL1_FIXED_DATA(-20, 250, 350, 10, 100, 100, 100, 65, 15,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: KEEP_BACK Setting
 *=====================================================================
 */

CameraModeValue D_801B5C80[] = {
    PARALLEL1_FIXED_DATA(
        100, 300, -20, 40, 0, 4, 5, 80, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 60, 20),
};

/*=====================================================================
 *                   Custom Data: CIRCLE6 Setting
 *=====================================================================
 */

CameraModeValue D_801B5CB0[] = {
    FIXED2_FIXED_DATA(
        -40, 60, 0x3200, 10, 20, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED2_FLAG_1 | FIXED2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE7 Setting
 *=====================================================================
 */

CameraModeValue D_801B5CCC[] = {
    FIXED2_FIXED_DATA(-40, 40, 200, 10, 20, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED2_FLAG_5)),
};

/*=====================================================================
 *                   Custom Data: MINI_BOSS Setting
 *=====================================================================
 */

CameraModeValue sSetMiniBossModeNormalData[] = {
    NORMAL1_FIXED_DATA(-15, 220, 280, 17, 14, 5, 65, 70, 75,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetMiniBossModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(0, 200, 250, 25, 45, 40, 15, 40, 60, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 20),
};

CameraModeValue sSetMiniBossModeBattleData[] = {
    BATTLE1_FIXED_DATA(-25, 180, 220, 10, 40, 10, 0, 40, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 20, 50),
};

CameraModeValue sSetMiniBossModeJumpData[] = {
    NORMAL1_FIXED_DATA(-15, 220, 280, 16, 12, 5, 60, 70, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetMiniBossModeStillData[] = {
    NORMAL1_FIXED_DATA(-15, 220, 280, 16, 100, 100, 100, 70, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: RFIXED1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5DC4[] = {
    FIXED1_FIXED_DATA(-40, 10, 60, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED1_FLAG_4)),
};

/*=====================================================================
 *                   Custom Data: TRESURE1 Setting
 *=====================================================================
 */

CameraModeValue sSetTreasureChestMinigameModeNormalData[] = {
    NORMAL1_FIXED_DATA(
        -20, 80, 120, -10, 15, 20, 40, 70, 70,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_7 | NORMAL1_FLAG_1)),
};

CameraModeValue sSetTreasureChestMinigameModeTargetData[] = {
    PARALLEL1_FIXED_DATA(
        0xFFC4, 0x0226, 0, 65, 0, 5, 5, 75, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_6 | PARALLEL1_FLAG_1), 60, 0),
};

/*=====================================================================
 *                   Custom Data: BOMBBASKET Setting
 *=====================================================================
 */

CameraModeValue D_801B5E2C[] = {
    FIXED2_FIXED_DATA(70, 50, 0x3200, 100, 30, 70,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, FIXED2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: CIRCLE8 Setting
 *=====================================================================
 */

CameraModeValue D_801B5E48[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 100, 20, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED2_FLAG_3)),
};

/*=====================================================================
 *                   Custom Data: BIRDS_EYE_VIEW_1 Setting
 *=====================================================================
 */

CameraModeValue D_801B5E64[] = {
    NORMAL1_FIXED_DATA(
        -20, 800, 800, 60, 50, 10, 50, 45, 90,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_6 | NORMAL1_FLAG_1)),
};

CameraModeValue D_801B5E8C[] = {
    NORMAL1_FIXED_DATA(-20, 800, 800, 60, 100, 100, 100, 45, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: DUNGEON3 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon3ModeNormalData[] = {
    NORMAL1_FIXED_DATA(
        -30, 180, 250, -5, 18, 20, 60, 55, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_7 | NORMAL1_FLAG_1)),
};

CameraModeValue sSetDungeon3ModeTargetData[] = {
    PARALLEL1_FIXED_DATA(
        -30, 180, 20, 0, 0, 5, 5, 45, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_6 | PARALLEL1_FLAG_1), 80, 0),
};

CameraModeValue sSetDungeon3ModeJumpData[] = {
    NORMAL1_FIXED_DATA(-30, 160, 190, 0, 30, 20, 60, 55, 30,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon3ModeStillData[] = {
    NORMAL1_FIXED_DATA(-40, 0x00AA, 200, 0, 100, 100, 100, 55, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon3ModePushPullData[] = {
    PARALLEL1_FIXED_DATA(
        0, 180, 5, 5, 0, 5, 5, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 30, 0),
};

/*=====================================================================
 *                   Custom Data: TELESCOPE Setting
 *=====================================================================
 */

CameraModeValue sSetTelescopeModeNormalData[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 30,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_NONE_ALT, 0)),
};

CameraModeValue sSetTelescopeModeTargetData[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 15,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_NONE_ALT, 0)),
};

CameraModeValue sSetTelescopeModeFirstPersonData[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 10, 0, 0, 0, 30,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_NONE_ALT, SUBJECT1_FLAG_4)),
};

CameraModeValue sSetTelescopeModeDekuHideData[] = {
    SUBJECT1_FIXED_DATA(0, 5, 50, 0x0001, 0, 0, 0, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_NONE_ALT, SUBJECT1_FLAG_4)),
};

/*=====================================================================
 *                   Custom Data: ROOM0 Setting
 *=====================================================================
 */

CameraModeValue D_801B601C[] = {
    NORMAL1_FIXED_DATA(0xFFDD, 100, 220, 15, 0x0011, 12, 35, 65, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B6044[] = {
    PARALLEL1_FIXED_DATA(-10, 200, 50, 0, 0, 5, 5, 65, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_6 | PARALLEL1_FLAG_4 | PARALLEL1_FLAG_1),
                         60, 0),
};

CameraModeValue D_801B6074[] = {
    KEEPON1_FIXED_DATA(-30, 60, 200, 20, 40, -5, 10, 30, 45, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue D_801B60A4[] = {
    KEEPON3_FIXED_DATA(
        -20, 50, 100, 50, 5, 20, 5, 40, 35, 50, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, KEEPON3_FLAG_5), 60),
};

CameraModeValue D_801B60D8[] = {
    BATTLE1_FIXED_DATA(-25, 100, 140, 10, 40, -2, 10, 25, 50, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 50),
};

CameraModeValue D_801B610C[] = {
    JUMP2_FIXED_DATA(-20, 100, 220, 20, 5, 5, 65, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue D_801B6130[] = {
    JUMP2_FIXED_DATA(-20, 120, 240, 20, 999, 5, 60, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, JUMP2_FLAG_2 | JUMP2_FLAG_1)),
};

CameraModeValue D_801B6154[] = {
    NORMAL1_FIXED_DATA(-30, 100, 220, 10, 30, 12, 80, 65, 30,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B617C[] = {
    PARALLEL1_FIXED_DATA(-40, 200, 50, 40, 0, 8, 5, 65, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         60, 12),
};

CameraModeValue D_801B61AC[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 240, 50, 70, 0, 12, 5, 45, 60,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         60, 2),
};

CameraModeValue D_801B61DC[] = {
    PARALLEL1_FIXED_DATA(
        -10, 200, 100, 70, 0, 4, 5, 70, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_7 | PARALLEL1_FLAG_3), 65, 12),
};

CameraModeValue D_801B620C[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 240, -20, 50, 0, 50, 5, 80, 20,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0), 65, 10),
};

CameraModeValue D_801B623C[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 240, -20, 40, 0, 50, 5, 80, 20,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 65, 0),
};

CameraModeValue D_801B626C[] = {
    NORMAL1_FIXED_DATA(-20, 100, 220, 10, 100, 100, 100, 65, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B6294[] = {
    PARALLEL1_FIXED_DATA(0, 200, 5, 45, 0, 5, 5, 70, 30,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_5 | PARALLEL1_FLAG_4 | PARALLEL1_FLAG_1),
                         80, 0),
};

CameraModeValue D_801B62C4[] = {
    KEEPON1_FIXED_DATA(-5, 120, 140, 5, 85, 10, 5, 25, 45, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue D_801B62F4[] = {
    NORMAL1_FIXED_DATA(50, 140, 220, 0, 0xC, 10, 40, 90, 90,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_2 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B631C[] = {
    PARALLEL1_FIXED_DATA(
        100, 220, -20, 40, 0, 4, 5, 80, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 80,
        20),
};

CameraModeValue D_801B634C[] = {
    NORMAL1_FIXED_DATA(0xFFC4, 150, 250, 40, 20, 12, 40, 80, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B6374[] = {
    PARALLEL1_FIXED_DATA(0xFFC4, 220, 20, 10, 0, 5, 5, 60, 90,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_3 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         90, 0),
};

CameraModeValue D_801B63A4[] = {
    NORMAL1_FIXED_DATA(
        -10, 120, 240, 0, 18, 12, 40, 80, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                            NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_2 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B63CC[] = {
    PARALLEL1_FIXED_DATA(0, 220, 50, 0, 0, 5, 5, 45, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

/*=====================================================================
 *                   Custom Data: RCIRC0 Setting
 *=====================================================================
 */

CameraModeValue D_801B63FC[] = {
    FIXED2_FIXED_DATA(
        -10, 40, 0x3200, 100, 20, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, FIXED2_FLAG_4 | FIXED2_FLAG_3)),
};

/*=====================================================================
 *                   Custom Data: CIRC9 Setting
 *=====================================================================
 */

CameraModeValue D_801B6418[] = {
    FIXED2_FIXED_DATA(-40, 40, 0x3200, 5, 25, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, FIXED2_FLAG_2 | FIXED2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: ONTHEPOLE Setting
 *=====================================================================
 */

CameraModeValue D_801B6434[] = {
    NORMAL1_FIXED_DATA(-15, 60, 600, 35, 40, 20, 60, 45, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_1)),
};

CameraModeValue D_801B645C[] = {
    PARALLEL1_FIXED_DATA(
        0, 300, 5, 35, 0, 5, 5, 60, 70,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_6 | PARALLEL1_FLAG_1), 80, 0),
};

CameraModeValue D_801B648C[] = {
    NORMAL1_FIXED_DATA(-10, 320, 0x017C, 30, 0x0016, 10, 0x0020, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B64B4[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 5, 5, 60, 50,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue D_801B64D8[] = {
    JUMP2_FIXED_DATA(-20, 280, 320, 20, 999, 5, 60, 50,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, JUMP2_FLAG_2 | JUMP2_FLAG_1)),
};

CameraModeValue D_801B64FC[] = {
    PARALLEL1_FIXED_DATA(-40, 320, 50, 40, 0, 8, 5, 60, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         50, 12),
};

CameraModeValue D_801B652C[] = {
    PARALLEL1_FIXED_DATA(0xFFB0, 300, 50, 70, 0, 12, 5, 45, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL,
                                             PARALLEL1_FLAG_7 | PARALLEL1_FLAG_2 | PARALLEL1_FLAG_1),
                         50, 2),
};

CameraModeValue D_801B655C[] = {
    NORMAL1_FIXED_DATA(-15, 340, 350, 30, 100, 100, 100, 60, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: INBUSH Setting
 *=====================================================================
 */

CameraModeValue D_801B6584[] = {
    NORMAL1_FIXED_DATA(
        0, 260, 280, 20, 20, 12, 50, 60, 80,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_7 | NORMAL1_FLAG_1)),
};

CameraModeValue D_801B65AC[] = {
    PARALLEL1_FIXED_DATA(10, 260, 50, 15, 0, 5, 5, 45, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue D_801B65DC[] = {
    KEEPON1_FIXED_DATA(10, 200, 220, 20, 40, 20, 30, 15, 45, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue D_801B660C[] = {
    KEEPON3_FIXED_DATA(
        10, 180, 200, 30, 10, 30, 30, 70, 45, 50, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, KEEPON3_FLAG_6), 60),
};

CameraModeValue D_801B6640[] = {
    BATTLE1_FIXED_DATA(10, 220, 220, 10, 80, 20, 30, 25, 50, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 60),
};

CameraModeValue D_801B6674[] = {
    SUBJECT1_FIXED_DATA(0, 10, 60, 10, 0, 50, 0, 45,
                        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, 0)),
};

CameraModeValue D_801B6698[] = {
    NORMAL1_FIXED_DATA(0, 260, 280, 40, 20, 12, 40, 60, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1)),
};

CameraModeValue D_801B66C0[] = {
    NORMAL1_FIXED_DATA(0, 260, 280, 20, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: BOSS_MAJORA Setting
 *=====================================================================
 */

CameraModeValue sSetBossMajoraModeNormalData[] = {
    NORMAL1_FIXED_DATA(0, 280, 320, -5, 24, 12, 0x0020, 65, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossMajoraModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(-30, 240, 260, 20, 40, 10, 5, 60, 50, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0), 30),
};

CameraModeValue sSetBossMajoraModeBattleData[] = {
    BATTLE1_FIXED_DATA(0xFFC4, 180, 200, 10, 20, 20, 10, 20, 70, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 10, 40),
};

CameraModeValue sSetBossMajoraModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 30, 12, 40, 65, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossMajoraModeStillData[] = {
    NORMAL1_FIXED_DATA(0, 280, 320, 0, 100, 100, 100, 65, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: BOSS_TWINMOLD Setting
 *=====================================================================
 */

CameraModeValue sSetBossTwinmoldModeNormalData[] = {
    NORMAL1_FIXED_DATA(20, 350, 400, 0, 0x001A, 12, 0x0020, 75, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossTwinmoldModeTargetData[] = {
    PARALLEL1_FIXED_DATA(0, 400, 50, 0, 0, 5, 5, 55, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue sSetBossTwinmoldModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(-30, 250, 300, 20, 40, 10, 5, 60, 50, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, 0), 30),
};

CameraModeValue sSetBossTwinmoldModeBattleData[] = {
    BATTLE1_FIXED_DATA(0, 150, 200, 10, 30, 10, 0, 20, 70, 30,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 10, 40),
};

CameraModeValue sSetBossTwinmoldModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 350, 400, 10, 30, 12, 40, 75, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossTwinmoldModeStillData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_4 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: BOSS_GOHT Setting
 *=====================================================================
 */

CameraModeValue sSetBossGohtModeNormalData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 20, 12, 50, 60, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossGohtModeBattleData[] = {
    BATTLE1_FIXED_DATA(-25, 220, 220, 10, 80, -2, 10, 25, 50, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 50),
};

CameraModeValue sSetBossGohtModeJumpData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 30, 12, 40, 60, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossGohtModeStillData[] = {
    NORMAL1_FIXED_DATA(-20, 280, 320, 10, 100, 100, 100, 60, 15,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetBossGohtModeGoronDashData[] = {
    NORMAL1_FIXED_DATA(60, 200, 340, 10, 15, 10, 50, 85, 90,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_2 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: BOSS_GYORG Setting
 *=====================================================================
 */

CameraModeValue sSetBossGyorgModeNormalData[] = {
    JUMP3_FIXED_DATA(-20, 280, 320, 10, 20, 12, 40, 60, 80,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2)),
};

CameraModeValue sSetBossGyorgModeFollowTargetData[] = {
    KEEPON1_FIXED_DATA(-30, 200, 240, 20, 40, -5, 10, 15, 45, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue sSetBossGyorgModeBattleData[] = {
    BATTLE1_FIXED_DATA(-30, 190, 250, 10, 50, 0, 10, 20, 50, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 25, 50),
};

CameraModeValue sSetBossGyorgModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 160, 260, -5, 18, 5, 40, 70, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

CameraModeValue sSetBossGyorgModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-30, 220, 280, 0, 18, 5, 60, 60, 60,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetBossGyorgModeDekuHideData[] = {
    JUMP3_FIXED_DATA(
        0xFFC4, 160, 280, -15, 18, 5, 60, 60, 40,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetBossGyorgModeStillData[] = {
    NORMAL1_FIXED_DATA(-40, 100, 320, 20, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: PINNACLE_ROCK Setting
 *=====================================================================
 */

CameraModeValue sSetPinnacleRockModeNormalData[] = {
    JUMP3_FIXED_DATA(-40, 250, 350, 30, 15, 5, 40, 60, 100,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2)),
};

CameraModeValue sSetPinnacleRockModeTargetData[] = {
    PARALLEL1_FIXED_DATA(
        -50, 350, 40, 10, 0, 15, 5, 60, 100,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1 | PARALLEL1_FLAG_0), 80, 0),
};

CameraModeValue sSetPinnacleRockModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(-40, 320, 400, -5, 18, 5, 40, 60, 40,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

CameraModeValue sSetPinnacleRockModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(-40, 300, 350, 10, 18, 5, 60, 60, 60,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetPinnacleRockModeDekuHideData[] = {
    JUMP3_FIXED_DATA(
        0xFFC4, 150, 250, -18, 18, 5, 60, 60, 40,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetPinnacleRockModeStillData[] = {
    NORMAL1_FIXED_DATA(-40, 250, 350, 30, 100, 100, 100, 60, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetPinnacleRockModeGoronDashData[] = {
    JUMP3_FIXED_DATA(-40, 250, 280, 5, 0x0011, 5, 40, 75, 35,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

/*=====================================================================
 *                   Custom Data: NORMAL2 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal2ModeNormalData[] = {
    NORMAL1_FIXED_DATA(-10, 350, 400, 14, 25, 14, 60, 65, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal2ModeTargetData[] = {
    PARALLEL1_FIXED_DATA(0, 350, 80, 0, 0, 5, 5, 50, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue sSetNormal2ModeJumpData[] = {
    NORMAL1_FIXED_DATA(-10, 350, 0x01A4, 10, 30, 10, 40, 65, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetNormal2ModeStillData[] = {
    NORMAL1_FIXED_DATA(-10, 350, 400, 14, 100, 100, 100, 65, 16,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: BOMBBOWL Setting
 *=====================================================================
 */

CameraModeValue D_801B6C98[] = {
    NORMAL1_FIXED_DATA(-30, 300, 320, 15, 0x0016, 12, 30, 55, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B6CC0[] = {
    KEEPON1_FIXED_DATA(-30, 180, 200, 20, 30, -5, 10, 40, 45, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 30),
};

CameraModeValue D_801B6CF0[] = {
    KEEPON3_FIXED_DATA(
        -30, 65, 70, 10, 10, 5, 5, 20, 45, 50, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, KEEPON3_FLAG_5), 50),
};

CameraModeValue D_801B6D24[] = {
    NORMAL1_FIXED_DATA(-20, 300, 320, 10, 30, 12, 40, 55, 30,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B6D4C[] = {
    NORMAL1_FIXED_DATA(-30, 300, 320, 15, 100, 100, 100, 55, 25,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: CIRCA Setting
 *=====================================================================
 */

CameraModeValue D_801B6D74[] = {
    FIXED2_FIXED_DATA(-40, 60, 0x3200, 100, 20, 60,
                      CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE,
                                          FIXED2_FLAG_3 | FIXED2_FLAG_1 | FIXED2_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: WHIRLPOOL Setting
 *=====================================================================
 */

CameraModeValue sSetWhirlpoolModeNormalData[] = {
    JUMP3_FIXED_DATA(
        -10, 280, 350, 50, 12, 5, 30, 60, 80,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_5 | JUMP3_FLAG_2)),
};

CameraModeValue sSetWhirlpoolModeFreeFallData[] = {
    JUMP3_FIXED_DATA(0, 180, 300, 30, 12, 5, 25, 75, 20,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_4 | JUMP3_FLAG_2)),
};

CameraModeValue sSetWhirlpoolModeGoronJumpData[] = {
    JUMP3_FIXED_DATA(
        -40, 320, 350, -5, 12, 5, 25, 65, 40,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_4 | JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

CameraModeValue sSetWhirlpoolModeDekuFlyData[] = {
    JUMP3_FIXED_DATA(
        -40, 300, 350, 10, 15, 5, 30, 65, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_5 | JUMP3_FLAG_2 | JUMP3_FLAG_0)),
};

CameraModeValue sSetWhirlpoolModeDekuHideData[] = {
    JUMP3_FIXED_DATA(
        0xFFC4, 150, 250, -18, 15, 5, 30, 60, 40,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_4 | JUMP3_FLAG_2)),
};

CameraModeValue sSetWhirlpoolModeGoronDashData[] = {
    JUMP3_FIXED_DATA(
        -40, 220, 260, 5, 8, 5, 20, 75, 35,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_4 | JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

/*=====================================================================
 *                   Custom Data: CUCCO_SHACK Setting
 *=====================================================================
 */

CameraModeValue sSetCuccoShackModeNormalData[] = {
    NORMAL1_FIXED_DATA(0xFFBA, 250, 0x01F4, 5, 30, 12, 45, 50, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetCuccoShackModeStillData[] = {
    NORMAL1_FIXED_DATA(-40, 250, 0x01F4, 5, 100, 100, 100, 50, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetCuccoShackModeDekuHideData[] = {
    NORMAL1_FIXED_DATA(-40, 250, 0x01F4, 5, 25, 12, 40, 50, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: GIANT Setting
 *=====================================================================
 */

CameraModeValue sSetGiantModeNormalData[] = {
    NORMAL1_FIXED_DATA(-40, 150, 160, -15, 25, 14, 50, 50, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetGiantModeTargetData[] = {
    PARALLEL1_FIXED_DATA(-40, 180, 80, 0, 0, 5, 5, 50, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 60, 0),
};

CameraModeValue sSetGiantModeJumpData[] = {
    NORMAL1_FIXED_DATA(-10, 100, 150, 10, 30, 10, 40, 70, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetGiantModeStillData[] = {
    NORMAL1_FIXED_DATA(-40, 150, 160, 0xFFF4, 25, 14, 50, 50, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

/*=====================================================================
 *                   Custom Data: SCENE0 Setting
 *=====================================================================
 */

CameraModeValue D_801B6FA0[] = {
    UNIQUE2_FIXED_DATA(-40, 20, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           UNIQUE2_FLAG_5 | UNIQUE2_FLAG_4 | UNIQUE2_FLAG_1)),
};

/*=====================================================================
 *                   Custom Data: ROOM1 Setting
 *=====================================================================
 */

CameraModeValue D_801B6FB0[] = {
    NORMAL1_FIXED_DATA(-15, 120, 250, 16, 16, 5, 65, 60, 75,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B6FD8[] = {
    KEEPON1_FIXED_DATA(-20, 100, 150, 0, 4, 20, 10, 40, 60, 60,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_0), 20),
};

CameraModeValue D_801B7008[] = {
    BATTLE1_FIXED_DATA(-25, 100, 180, 10, 40, 10, 0, 40, 60, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_1), 20, 50),
};

CameraModeValue D_801B703C[] = {
    NORMAL1_FIXED_DATA(-15, 120, 250, 16, 12, 5, 60, 70, 40,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B7064[] = {
    NORMAL1_FIXED_DATA(-15, 120, 250, 16, 100, 100, 100, 70, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_5 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue D_801B708C[] = {
    PARALLEL1_FIXED_DATA(
        0, 200, 5, 30, 0, 5, 5, 70, 30,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_5 | PARALLEL1_FLAG_1), 80, 0),
};

/*=====================================================================
 *                   Custom Data: WATER2 Setting
 *=====================================================================
 */

CameraModeValue D_801B70BC[] = {
    JUMP3_FIXED_DATA(-10, 270, 300, 20, 30, 20, 65, 60, 80,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_7 | JUMP3_FLAG_2)),
};

CameraModeValue D_801B70E4[] = {
    PARALLEL1_FIXED_DATA(
        -30, 280, 40, 10, 0, 15, 5, 60, 100,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1 | PARALLEL1_FLAG_0), 60, 0),
};

CameraModeValue D_801B7114[] = {
    KEEPON3_FIXED_DATA(-20, 50, 100, 50, 5, 20, 10, 40, 45, 50, 20,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, 0),
                       60),
};

CameraModeValue D_801B7148[] = {
    JUMP3_FIXED_DATA(-40, 180, 200, 5, 20, 5, 40, 75, 35,
                     CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, JUMP3_FLAG_3 | JUMP3_FLAG_2)),
};

/*=====================================================================
 *                   Custom Data: FORCEKEEP Setting
 *=====================================================================
 */

CameraModeValue D_801B7170[] = {
    KEEPON1_FIXED_DATA(
        -30, 180, 200, 20, 40, -5, 10, 15, 45, 60,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, KEEPON1_FLAG_4 | KEEPON1_FLAG_0), 30),
};

CameraModeValue D_801B71A0[] = {
    BATTLE1_FIXED_DATA(
        -30, 150, 250, 10, 60, -5, 20, 35, 55, 70,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, BATTLE1_FLAG_4 | BATTLE1_FLAG_1), 25, 40),
};

/*=====================================================================
 *                   Custom Data: PARALLEL1 Setting
 *=====================================================================
 */

CameraModeValue D_801B71D4[] = {
    PARALLEL1_FIXED_DATA(
        0, 400, 20, 20, 0, 20, 5, 70, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_3 | PARALLEL1_FLAG_1), 80, 0),
};

/*=====================================================================
 *                   Custom Data: START1 Setting
 *=====================================================================
 */

CameraModeValue D_801B7204[] = {
    UNIQUE0_FIXED_DATA(0, 100, CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL, UNIQUE0_FLAG_1)),
};

/*=====================================================================
 *                   Custom Data: ROOM2 Setting
 *=====================================================================
 */

CameraModeValue D_801B7210[] = {
    KEEPON3_FIXED_DATA(
        -10, 120, 180, 50, 5, 10, 5, 70, 35, 50, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, KEEPON3_FLAG_5), 60),
};

/*=====================================================================
 *                   Custom Data: NORMAL4 Setting
 *=====================================================================
 */

CameraModeValue sSetNormal4ModeTalkData[] = {
    KEEPON3_FIXED_DATA(
        -20, 0x006E, 160, 80, 15, 10, 0, 70, 40, 50, 20,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_LARGE, CAM_HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE, KEEPON3_FLAG_5), 50),
};

/*=====================================================================
 *                   Custom Data: ELEGY_SHELL Setting
 *=====================================================================
 */

CameraModeValue sSetElegyShellModeNormalData[] = {
    KEEPON4_FIXED_DATA(-45, 150, -10, 165, 5, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 30),
};

CameraModeValue sSetElegyShellModeJumpData[] = {
    KEEPON4_FIXED_DATA(-40, 150, 18, 140, 5, 70,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 30),
};

CameraModeValue sSetElegyShellModeDekuShootData[] = {
    KEEPON4_FIXED_DATA(-20, 150, -2, 140, 15, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 30),
};

CameraModeValue sSetElegyShellModeGoronDashData[] = {
    KEEPON4_FIXED_DATA(-50, 150, 0xFFF4, 160, 6, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_1), 25, 30),
};

CameraModeValue sSetElegyShellModeDekuFlyData[] = {
    KEEPON4_FIXED_DATA(
        0xFFC4, 150, 0xFFF4, 0xFF74, 30, 50,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_IGNORE, KEEPON4_FLAG_3 | KEEPON4_FLAG_2), 25, 30),
};

/*=====================================================================
 *                   Custom Data: DUNGEON4 Setting
 *=====================================================================
 */

CameraModeValue sSetDungeon4ModeNormalData[] = {
    NORMAL1_FIXED_DATA(0, 150, 250, -5, 16, 5, 0x0034, 55, 80,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon4ModeTargetData[] = {
    PARALLEL1_FIXED_DATA(0, 200, 25, 5, 0, 5, 5, 45, 50,
                         CAM_INTERFACE_FLAGS(CAM_LETTERBOX_MEDIUM, CAM_HUD_VISIBILITY_ALL, PARALLEL1_FLAG_1), 80, 0),
};

CameraModeValue sSetDungeon4ModeJumpData[] = {
    NORMAL1_FIXED_DATA(0, 150, 250, 0, 24, 5, 50, 55, 50,
                       CAM_INTERFACE_FLAGS(CAM_LETTERBOX_NONE, CAM_HUD_VISIBILITY_ALL,
                                           NORMAL1_FLAG_7 | NORMAL1_FLAG_3 | NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
};

CameraModeValue sSetDungeon4ModeStillData[] = {
    NORMAL1_FIXED_DATA(
        0, 180, 220, 5, 100, 100, 100, 55, 10,
        CAM_INTERFACE_FLAGS(CAM_LETTERBOX_IGNORE, CAM_HUD_VISIBILITY_ALL, NORMAL1_FLAG_1 | NORMAL1_FLAG_0)),
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
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
};

CameraMode sCamSetNormal3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronDashData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal3ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal3ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronJumpData),
};

CameraMode sCamSetPivotDivingModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE2, sSetPivotDivingModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE2, sSetPivotDivingModeTargetData),
};

CameraMode sCamSetHorseModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL3, sSetHorseModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL3, sSetHorseModeJumpData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetHorseModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL3, sSetHorseModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetHorseModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetHorseModeSlingShotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetHorseModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetHorseModeBattleData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL3, sSetHorseModeStillData),
};

CameraMode sCamSetZoraDivingModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL3, sSetZoraDivingModeNormalData),
};

CameraMode sCamSetPreRendFixedModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED3, sSetPrerendFixedModeNormalData),
};

CameraMode sCamSetPreRendPivotModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE7, sSetPrerendPivotModeNormalData),
};

CameraMode sCamSetDoorCModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL9, sSetDoorCModeNormalData),
};

CameraMode sCamSetDemo0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO1, D_801B4EF0),
};

CameraMode sCamSetFree0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE6, sSetCutscenesModeNormalData),
};

CameraMode sCamSetFukan0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4EF8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4F50),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B4F20),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4F78),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4EF8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetNormal1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal1ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal1ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetNanameModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL4, D_801B4FF0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetCirc0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5018),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5034),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5050),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetFixed0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED1, D_801B506C),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetSpiralDoorModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL8, sSetSpiralDoorModeNormalData),
};

CameraMode sCamSetDungeon0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon0ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetDungeon0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
};

CameraMode sCamSetItem0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5338),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B535C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B53A4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5380),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B53C8),
};

CameraMode sCamSetItem1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B53EC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5410),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5458),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5434),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B547C),
};

CameraMode sCamSetItem2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B54A0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B54C4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B550C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B54E8),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5530),
};

CameraMode sCamSetItem3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5554),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5578),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B55C0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B559C),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B55E4),
};

CameraMode sCamSetNaviModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE6, sSetCutscenesModeNormalData),
};

CameraMode sCamSetWarp0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5608),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B562C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5674),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5650),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5698),
};

CameraMode sCamSetDeathModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetDeathModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetDeathModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetDeathModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetDeathModeDekuShootData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetDeathModeJumpData),
};

CameraMode sCamSetRebirthModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5728),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5728),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5728),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B574C),
    CAM_SETTING_MODE_NULL, // CAM_MODE_BOWARROWZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, D_801B5728),
};

CameraMode sCamSetLongChestOpeningModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO2, sSetLongChestOpeningModeNormalData),
};

CameraMode sCamSetMaskTransformationModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO4, sSetCutscenesModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO5, sSetCutscenesModeNormalData),
};

CameraMode sCamSetAttentionModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO1, sSetCutscenesModeNormalData),
};

CameraMode sCamSetWarp1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO3, sSetCutscenesModeNormalData),
};

CameraMode sCamSetDungeon1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon1ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon1ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetDungeon0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon1ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon1ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetFixed1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED1, D_801B5824),
};

CameraMode sCamSetFixed2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED1, D_801B5834),
};

CameraMode sCamSetMazeModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL2, sSetMazeModeNormalData),
};

CameraMode sCamSetRemoteBombModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL2, sSetRemoteBombModeNormalData),
};

CameraMode sCamSetCirc1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5884),
};

CameraMode sCamSetCirc2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B58A0),
};

CameraMode sCamSetCirc3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B58BC),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5034),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5050),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetCirc4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B58D8),
};

CameraMode sCamSetFixed3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED1, D_801B58F4),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetTowerClimbModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL0, sSetTowerClimbModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetTowerClimbModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetTowerClimbModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetParallel0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B5978),
};

CameraMode sCamSetNormDModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B59A8),
};

CameraMode sCamSetSubjectDModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, D_801B59D0),
};

CameraMode sCamSetStart0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE0, D_801B59F4),
};

CameraMode sCamSetStart2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE0, D_801B5A00),
};

CameraMode sCamSetStop0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE6, sSetCutscenesModeNormalData),
};

CameraMode sCamSetBoatCruiseModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetBoatCruiseModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
};

CameraMode sCamSetVerticalClimbModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetVerticalClimbModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetVerticalClimbModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetSidedModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B5A64),
};

CameraMode sCamSetDungeon2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon2ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon2ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetDungeon2ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon2ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon2ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetBossOdolwaModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossOdolwaModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossOdolwaModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetBossOdolwaModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetBossOdolwaModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetBossOdolwaModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossOdolwaModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetKeepBackModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B5C80),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetVerticalClimbModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetCirc6Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5CB0),
};

CameraMode sCamSetCirc7Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5CCC),
};

CameraMode sCamSetMiniBossModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetMiniBossModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetMiniBossModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetMiniBossModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetMiniBossModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetMiniBossModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetRFixed1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED1, D_801B5DC4),
};

CameraMode sCamSetTreasureChestMinigameModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetTreasureChestMinigameModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetTreasureChestMinigameModeTargetData),
};

CameraMode sCamSetBombBasketModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5E2C),
};

CameraMode sCamSetCirc8Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5E48),
};

CameraMode sCamSetFukan1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B5E64),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4F50),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B4F20),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B5E8C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4EF8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetDungeon3Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon3ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon3ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon3ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetDungeon0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon3ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon3ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetTelescopeModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetTelescopeModeNormalData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetTelescopeModeFirstPersonData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetTelescopeModeTargetData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetTelescopeModeDekuHideData),
};

CameraMode sCamSetRoom0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B601C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6154),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B62F4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B634C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B62C4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B6074),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B6044),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B60A4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, D_801B60D8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B631C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B626C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B620C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B610C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B6130),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B61DC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B617C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B61AC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B6294),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B6374),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B63A4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B623C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B63CC),
};

CameraMode sCamSetRCirc0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B63FC),
};

CameraMode sCamSetCirc9Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B6418),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5034),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B5050),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
};

CameraMode sCamSetOnThePoleModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6434),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B648C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B645C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetDungeon0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B655C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B64B4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B64D8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B64FC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B652C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon1ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetInBushModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6584),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6698),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, D_801B6674),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B65DC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B65AC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B660C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, D_801B6640),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B66C0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B4EF8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetBossMajoraModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossMajoraModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossMajoraModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetBossMajoraModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetBossMajoraModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossMajoraModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetBossTwinmoldModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossTwinmoldModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossTwinmoldModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetBossTwinmoldModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetBossTwinmoldModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetBossTwinmoldModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossTwinmoldModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetBossGohtModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossGohtModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossGohtModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossGohtModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetBossGohtModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossGohtModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetBossGyorgModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronDashData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetBossGyorgModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_SLINGSHOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetBossGyorgModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetBossGyorgModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetBossGyorgModeGoronJumpData),
};

CameraMode sCamSetConnect0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_DEMO0, sSetCutscenesModeNormalData),
};

CameraMode sCamSetPinnacleRockModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeGoronDashData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetPinnacleRockModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_SLINGSHOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetPinnacleRockModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetPinnacleRockModeGoronJumpData),
};

CameraMode sCamSetNormal2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal2ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal2ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal2ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal2ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetBombBowlModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6C98),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6D24),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B62F4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B634C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B62C4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B6CC0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B6044),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B6CF0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, D_801B60D8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B631C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6D4C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B620C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B610C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, D_801B6130),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B61DC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B617C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B61AC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B6294),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B6374),
};

CameraMode sCamSetCircAModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_FIXED2, D_801B6D74),
};

CameraMode sCamSetWhirlpoolModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeGoronDashData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUSHOOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetPinnacleRockModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_SLINGSHOT
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLYZ
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetWhirlpoolModeGoronJumpData),
};

CameraMode sCamSetCuccoShackModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetCuccoShackModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal2ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_NULL, // CAM_MODE_DEKUFLY
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal2ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetCuccoShackModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetCuccoShackModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
};

CameraMode sCamSetGiantModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetGiantModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetGiantModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetGiantModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetGiantModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetScene0Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE2, D_801B6FA0),
};

CameraMode sCamSetRoom1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6FB0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B703C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B62C4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B6FD8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B60A4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, D_801B7008),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B7064),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B708C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetWater2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, D_801B70BC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, D_801B7148),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B70E4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B7114),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal3ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP3, sSetNormal3ModeGoronJumpData),
};

CameraMode sCamSetWoodfallSwampModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE3, D_801B6584),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE3, D_801B6698),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE3, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE3, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, D_801B6674),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B65DC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, D_801B65AC),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B660C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE5, D_801B6640),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE3, D_801B66C0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE3, D_801B6584),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE4, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetForceKeepModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B7170),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, D_801B71A0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetParallel1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B71D4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetStart1Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_UNIQUE0, D_801B7204),
};

CameraMode sCamSetRoom2Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B6FB0),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B703C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B62C4),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, D_801B6FD8),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, D_801B7210),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, D_801B7008),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, D_801B7064),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, D_801B708C),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetNorm4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetNormal0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal4ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetNormal0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetNormal0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
};

CameraMode sCamSetElegyShellModes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetElegyShellModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetElegyShellModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetElegyShellModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetElegyShellModeDekuShootData),
    CAM_SETTING_MODE_NULL,
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON4, sSetElegyShellModeDekuFlyData),
};

CameraMode sCamSetDungeon4Modes[] = {
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon4ModeNormalData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon4ModeJumpData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeGoronDashData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeDekuShootData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetNormal0ModeDekuFlyData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeFirstPersonData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowBoomerangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeZoraFinData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON1, sSetDungeon0ModeFollowTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon4ModeTargetData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_KEEPON3, sSetNormal0ModeTalkData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeSlingshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SUBJECT1, sSetNormal0ModeBowArrowData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_BATTLE1, sSetDungeon0ModeBattleData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuHideData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_NORMAL1, sSetDungeon4ModeStillData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeChargeData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_JUMP2, sSetDungeon0ModeClimbZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_SPECIAL5, sSetNormal0ModeHookshotData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeFreeFallData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModeHangZData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetDungeon0ModePushPullData),
    CAM_SETTING_MODE_ENTRY(CAM_FUNC_PARALLEL1, sSetNormal0ModeDekuFlyZData),
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

s16 sGlobalCamDataSettings[] = {
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
    /*  -9 */ CAM_SET_REBIRTH,
    /*  -8 */ CAM_SET_DEATH,
    /*  -7 */ CAM_SET_WARP_PAD_MOON,
    /*  -6 */ CAM_SET_NAVI,
    /*  -5 */ CAM_SET_ITEM3,
    /*  -4 */ CAM_SET_ITEM2,
    /*  -3 */ CAM_SET_ITEM1,
    /*  -2 */ CAM_SET_ITEM0,
    /*  -1 */ CAM_SET_STOP0,
    /*   0 */ CAM_SET_NONE,
};

s16* sGlobalCamDataSettingsPtr = &sGlobalCamDataSettings[ARRAY_COUNT(sGlobalCamDataSettings) - 1];

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
s32 Camera_Subject1(Camera* camera);
s32 Camera_Subject2(Camera* camera);
s32 Camera_Subject3(Camera* camera);
s32 Camera_Subject4(Camera* camera);
s32 Camera_Subject0(Camera* camera);
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

s32 (*sCameraUpdateHandlers[])(Camera*) = {
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
    Camera_Subject0,
    Camera_Subject1,
    Camera_Subject2,
    Camera_Subject3,
    Camera_Subject4,
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

s16 sCameraNextUID = 0;
s32 sCameraInterfaceFlags = 1;
s32 sCameraHudVisibility = 2;
s32 sCameraLetterboxSize = 32;
s32 sCameraNegOne = -1;

// VecSph yaw data
s16 D_801B9E18[] = {
    0x0AAA, 0xF556, 0x1555, 0xEAAB, 0x2AAA, 0xD556, 0x3FFF, 0xC001, 0x5555, 0xAAAB, 0x6AAA, 0x9556, 0x7FFF, 0x0000,
};

// VecSph pitch data
s16 D_801B9E34[] = {
    0x0000, 0x02C6, 0x058C, 0x0000, 0x0000, 0xFD3A, 0x0000, 0x0852, 0x0000, 0x0000, 0x0B18, 0x02C6, 0xFA74, 0x0000,
};

s32 sUpdateCameraDirection = false;
static s32 sIsFalse = false;
s32 sCameraInitSceneTimer = 0;
