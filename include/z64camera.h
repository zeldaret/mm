#ifndef Z64CAMERA_H
#define Z64CAMERA_H

#include "ultra64.h"

// these two angle conversion macros are slightly inaccurate
#define CAM_DEG_TO_BINANG(degrees) (s16)((degrees) * 182.04167f + .5f)
#define CAM_BINANG_TO_DEG(binang) ((f32)(binang) * (360.0001525f / 65535.0f))

#define NUM_CAMS 4

// Camera IDs are indices into `cameraPtrs`
#define CAM_ID_MAIN 0 // The index of the main camera
#define CAM_ID_SUB_FIRST 1 // The index sub cameras start at
#define CAM_ID_NONE -1 // Used to indicate no camera. Can be used to default to the active camera in some scenarios

#define SUB_CAM_ID_DONE 0 // Used in some actors for variables holding sub camera IDs to indicate "subcam is finished"

#define CAM_HUD_ALPHA_SHIFT 8
#define CAM_HUD_ALPHA_MASK (0x0F00)
#define CAM_HUD_ALPHA(alpha) (((alpha) & 0xF) << CAM_HUD_ALPHA_SHIFT)

#define CAM_HUD_ALPHA_50 CAM_HUD_ALPHA(0)
#define CAM_HUD_ALPHA_1 CAM_HUD_ALPHA(1)
#define CAM_HUD_ALPHA_2 CAM_HUD_ALPHA(2)
#define CAM_HUD_ALPHA_3 CAM_HUD_ALPHA(3)
#define CAM_HUD_ALPHA_4 CAM_HUD_ALPHA(4)
#define CAM_HUD_ALPHA_5 CAM_HUD_ALPHA(5)
#define CAM_HUD_ALPHA_6 CAM_HUD_ALPHA(6)
#define CAM_HUD_ALPHA_7 CAM_HUD_ALPHA(7)
#define CAM_HUD_ALPHA_8 CAM_HUD_ALPHA(8)
#define CAM_HUD_ALPHA_9 CAM_HUD_ALPHA(9)
#define CAM_HUD_ALPHA_A CAM_HUD_ALPHA(10)
#define CAM_HUD_ALPHA_B CAM_HUD_ALPHA(11)
#define CAM_HUD_ALPHA_C CAM_HUD_ALPHA(12)
#define CAM_HUD_ALPHA_D CAM_HUD_ALPHA(13)
#define CAM_HUD_ALPHA_E CAM_HUD_ALPHA(14)
#define CAM_HUD_ALPHA_IGNORE CAM_HUD_ALPHA(0xF)

/**
 * shrinkWindowFlag: determines the size of the letter-box shrink window. See CAM_SHRINKWINVAL_* enums.
 *                  Can also add on the flag ( | CAM_SHRINKWIN_INSTANT) to make the window shrink immediately
 * interfaceAlpha: hides certain hud icons
 *    - A value of 0 in camera is translated to an interface alpha of 50, 
 *      which is the value to restore all hud icons to the screen (CAM_HUD_ALPHA_50)
 *    - A value of 0xF in camera results in no change in the alpha (CAM_HUD_ALPHA_IGNORE)
 * funcFlags: Custom flags for functions
 */
#define CAM_INTERFACE_FLAGS(shrinkWindowFlag, interfaceAlpha, funcFlags) \
    (((shrinkWindowFlag) & CAM_SHRINKWIN_MASK) | (interfaceAlpha) | ((funcFlags) & 0xFF))

// Shrinking the window from the top and bottom with black borders (letterboxing)
#define CAM_SHRINKWIN_MASK 0xF000

#define CAM_SHRINKWINVAL_MASK 0x7000
#define CAM_SHRINKWINVAL_NONE 0x0000
// small/medium/large black borders
#define CAM_SHRINKWINVAL_SMALL 0x1000
#define CAM_SHRINKWINVAL_MEDIUM 0x2000
#define CAM_SHRINKWINVAL_LARGE 0x3000
#define CAM_SHRINKWINVAL_NONE_4 0x4000

#define CAM_SHRINKWIN_INSTANT 0x8000 // Bit to determine whether to set the current value directly (on), or to set the shrink-value target (off) 

#define CAM_SHRINKWINVAL_IGNORE 0xF000 // No change in shrink window, keep the previous values


#define CAM_TRACKED_PLAYER(camera) ((Player*)camera->trackActor)

// Camera behaviorFlags. Flags specifically for settings, modes, and bgCam
// Used to store current state, only CAM_BEHAVIOR_SETTING_1 and CAM_BEHAVIOR_BG_2 are read from and used in logic
// Setting (0x1, 0x10)
#define CAM_BEHAVIOR_SETTING_USE_PRIORITY (1 << 0) // Use settings priority system
#define CAM_BEHAVIOR_SETTING_2 (1 << 4)
// Mode (0x2, 0x20)
#define CAM_BEHAVIOR_MODE_1 (1 << 1)
#define CAM_BEHAVIOR_MODE_2 (1 << 5)
// bgCam (0x4, 0x40)
#define CAM_BEHAVIOR_BGCAM_1 (1 << 2)
#define CAM_BEHAVIOR_BGCAM_2 (1 << 6)

// Camera stateFlags. Variety of generic flags
#define CAM_STATE_0 (1 << 0) // Must be set for the camera from changing settings based on the bg surface
#define CAM_STATE_1 (1 << 1)
#define CAM_STATE_2 (1 << 2)
#define CAM_STATE_3 (1 << 3)
#define CAM_STATE_4 (1 << 4)
#define CAM_STATE_5 (1 << 5)
#define CAM_STATE_6 (1 << 6)
#define CAM_STATE_7 (1 << 7)
#define CAM_STATE_UNDERWATER (1 << 8)
#define CAM_STATE_9 (1 << 9)
#define CAM_STATE_10 (1 << 10) // Surpresses the camera from changing settings based on the bg surface
#define CAM_STATE_11 (1 << 11)
#define CAM_STATE_12 (1 << 12)
#define CAM_STATE_13 (1 << 13)
#define CAM_STATE_14 (1 << 14)
#define CAM_STATE_15 ((s16)(1 << 15))

// Camera viewFlags. Set params related to view
#define CAM_VIEW_AT (1 << 0) // camera->at
#define CAM_VIEW_EYE (1 << 1) // camera->eye and camera->eyeNext
#define CAM_VIEW_UP (1 << 2) // camera->up
#define CAM_VIEW_TARGET (1 << 3) // camera->target
#define CAM_VIEW_TARGET_POS (1 << 4) // camera->targetPosRot.pos
#define CAM_VIEW_FOV (1 << 5) // camera->fov
#define CAM_VIEW_ROLL (1 << 6) // camera->roll

/**
 * Camera Status type
 * Determines how much the camera is updated each frame
 * Higher values represents higher levels of activity
 */
// Camera is on
#define CAM_STATUS_CUT        0 // The camera is not updated at all
#define CAM_STATUS_WAIT       1 // There is minimally/partially updated, action function is not run
#define CAM_STATUS_UNK3       3 // The camera is mostly updated including running its action function, but data is not set to view
#define CAM_STATUS_ACTIVE     7 // The camera is fully updated, info is sent to view
// Camera is off
#define CAM_STATUS_INACTIVE   0x100

typedef enum {
    /* 0x00 */ CAM_SET_NONE,
    /* 0x01 */ CAM_SET_NORMAL0, // Generic camera 0, used in various places
    /* 0x02 */ CAM_SET_NORMAL3, // Generic camera 3, used in various places
    /* 0x03 */ CAM_SET_PIVOT_DIVING, // Player diving from the surface of the water to underwater not as zora "CIRCLE5"
    /* 0x04 */ CAM_SET_HORSE, // Reiding a horse "HORSE0"
    /* 0x05 */ CAM_SET_ZORA_DIVING, // Parallel's Pivot Diving, but as Zora. However, Zora does not dive like a human. So this setting appears to not be set "ZORA0"
    /* 0x06 */ CAM_SET_PREREND_FIXED, // Unused remnant of OoT: camera is fixed in position and rotation "PREREND0"
    /* 0x07 */ CAM_SET_PREREND_PIVOT, // Unused remnant of OoT: Camera is fixed in position with fixed pitch, but is free to rotate in the yaw direction 360 degrees "PREREND1"
    /* 0x08 */ CAM_SET_DOORC, // Generic room door transitions, camera moves and follows player as the door is open and closed
    /* 0x09 */ CAM_SET_DEMO0, // Unknown, possibly related to treasure chest game as goron?
    /* 0x0A */ CAM_SET_FREE0, // Free Camera, manual control is given, no auto-updating eye or at
    /* 0x0B */ CAM_SET_BIRDS_EYE_VIEW_0, // Appears unused. Camera is a top-down view "FUKAN0"
    /* 0x0C */ CAM_SET_NORMAL1, // Generic camera 1, used in various places
    /* 0x0D */ CAM_SET_NANAME, // Unknown, slanted or tilted. Behaves identical to Normal0 except with added roll
    /* 0x0E */ CAM_SET_CIRCLE0, // Used in Curiosity Shop, Pirates Fortress, Mayor's Residence
    /* 0x0F */ CAM_SET_FIXED0, // Used in Sakon's Hideout puzzle rooms, milk bar stage
    /* 0x10 */ CAM_SET_SPIRAL_DOOR, // Exiting a Spiral Staircase "SPIRAL"
    /* 0x11 */ CAM_SET_DUNGEON0, // Generic dungeon camera 0, used in various places
    /* 0x12 */ CAM_SET_ITEM0, // Getting an item and holding it above Player's head (from small chest, freestanding, npc, ...)
    /* 0x13 */ CAM_SET_ITEM1, // Looking at player while playing the ocarina
    /* 0x14 */ CAM_SET_ITEM2, // Bottles: chugging, releasing fairy, dropping fish
    /* 0x15 */ CAM_SET_ITEM3, // Bottles: catching fish or bugs, showing an item
    /* 0x16 */ CAM_SET_NAVI, // Song of Soaring, variations of playing Song of Time "NAVI"
    /* 0x17 */ CAM_SET_WARP_PAD_MOON, // Warp circles from Goron Trial on the moon "WARP0"
    /* 0x18 */ CAM_SET_DEATH, // Player death animation when health goes to 0 "DEATH"
    /* 0x19 */ CAM_SET_REBIRTH, // Unknown set with camDataId = -9 (it's not being revived by a fairy)
    /* 0x1A */ CAM_SET_LONG_CHEST_OPENING, // Long cutscene when opening a big chest with a major item "TREASURE"
    /* 0x1B */ CAM_SET_MASK_TRANSFORMATION, // Putting on a transformation mask "TRANSFORM"
    /* 0x1C */ CAM_SET_ATTENTION, // Unknown, set with camDataId = -15
    /* 0x1D */ CAM_SET_WARP_PAD_ENTRANCE, // Warp pad from start of a dungeon to the boss-room "WARP1"
    /* 0x1E */ CAM_SET_DUNGEON1, // Generic dungeon camera 1, used in various places
    /* 0x1F */ CAM_SET_FIXED1, // Fixes camera in place, used in various places eg. entering Stock Pot Inn, hiting a switch, giving witch a red potion, shop browsing
    /* 0x20 */ CAM_SET_FIXED2, // Used in Pinnacle Rock after defeating Sea Monsters, and by Tatl in Fortress
    /* 0x21 */ CAM_SET_MAZE, // Unused. Set to use Camera_Parallel2(), which is only Camera_Noop()
    /* 0x22 */ CAM_SET_REMOTEBOMB, // Unused. Set to use Camera_Parallel2(), which is only Camera_Noop(). But also related to Play_ChangeCameraSetting?
    /* 0x23 */ CAM_SET_CIRCLE1, // Unknown
    /* 0x24 */ CAM_SET_CIRCLE2, // Looking at far-away NPCs eg. Garo in Road to Ikana, Hungry Goron, Tingle
    /* 0x25 */ CAM_SET_CIRCLE3, // Used in curiosity shop, goron racetrack, final room in Sakon's hideout, other places
    /* 0x26 */ CAM_SET_CIRCLE4, // Used during the races on the doggy racetrack
    /* 0x27 */ CAM_SET_FIXED3, // Used in Stock Pot Inn Toilet (???) and Tatl cutscene after woodfall "FIXED3"
    /* 0x28 */ CAM_SET_TOWER_ASCENT, // Various climbing structures (Snowhead climb to the temple entrance) "TOWER0"
    /* 0x29 */ CAM_SET_PARALLEL0, // Unknown
    /* 0x2A */ CAM_SET_NORMALD, // Unknown, set with camDataId = -20
    /* 0x2B */ CAM_SET_SUBJECTD, // Unknown, set with camDataId = -21
    /* 0x2C */ CAM_SET_START0, // Entering a room, either Dawn of a New Day reload, or entering a door where the camera is fixed on the other end "START0"
    /* 0x2D */ CAM_SET_START2, // Entering a scene, camera is put at a low angle eg. Grottos, Deku Palace, Stock Pot Inn "START2"
    /* 0x2E */ CAM_SET_STOP0, // Called in z_play "STOP0"
    /* 0x2F */ CAM_SET_BOAT_CRUISE, //  Koume's boat cruise "JCRUISING"
    /* 0x30 */ CAM_SET_VERTICAL_CLIMB, // Large vertical climbs, such as Mountain Village wall or Pirates Fortress ladder. "CLIMBMAZE"
    /* 0x31 */ CAM_SET_SIDED, // Unknown, set with camDataId = -24
    /* 0x32 */ CAM_SET_DUNGEON2, // Generic dungeon camera 2, used in various places
    /* 0x33 */ CAM_SET_BOSS_ODOLWA, // Odolwa's Lair, also used in GBT entrance: "BOSS_SHIGE"
    /* 0x34 */ CAM_SET_KEEPBACK, // Unknown. Possibly related to climbing something?
    /* 0x35 */ CAM_SET_CIRCLE6, // Used in select regions from Ikana
    /* 0x36 */ CAM_SET_CIRCLE7, // Unknown
    /* 0x37 */ CAM_SET_MINI_BOSS, // Used during the various minibosses of the "CHUBOSS"
    /* 0x38 */ CAM_SET_RFIXED1, // Talking to Koume stuck on the floor in woods of mystery
    /* 0x39 */ CAM_SET_TREASURE_CHEST_MINIGAME, // Treasure Chest Shop in East Clock Town, minigame location "TRESURE1"
    /* 0x3A */ CAM_SET_HONEY_AND_DARLING_1, // Honey and Darling Minigames "BOMBBASKET"
    /* 0x3B */ CAM_SET_CIRCLE8, // Used by Stone Tower moving platforms, Falling eggs in Marine Lab, Bugs into soilpatch cutscene
    /* 0x3C */ CAM_SET_BIRDS_EYE_VIEW_1, // Camera is a top-down view. Used in Fishermans minigame and Deku Palace "FUKAN1"
    /* 0x3D */ CAM_SET_DUNGEON3, // Generic dungeon camera 3, used in various places
    /* 0x3E */ CAM_SET_TELESCOPE, // Observatory telescope and Curiosity Shop Peep-Hole "TELESCOPE"
    /* 0x3F */ CAM_SET_ROOM0, // Certain rooms eg. inside the clock tower
    /* 0x40 */ CAM_SET_RCIRC0, // Used by a few NPC cutscenes, focus close on the NPC
    /* 0x41 */ CAM_SET_CIRCLE9, // Used by Sakon Hideout entrance and Deku Palace Maze
    /* 0x42 */ CAM_SET_ONTHEPOLE, // Somewhere in Snowhead Temple and Woodfall Temple
    /* 0x43 */ CAM_SET_INBUSH, // Various bush environments eg. grottos, Swamp Spider House, Termina Field grass bushes, Deku Palace near bean "INBUSH"
    /* 0x44 */ CAM_SET_BOSS_MAJORA, // Majora's Lair: "BOSS_LAST" 
    /* 0x45 */ CAM_SET_BOSS_TWINMOLD, // Twinmold's Lair: "BOSS_INI"
    /* 0x46 */ CAM_SET_BOSS_GOHT, // Goht's Lair: "BOSS_HAK" 
    /* 0x47 */ CAM_SET_BOSS_GYORG, // Gyorg's Lair: "BOSS_KON"
    /* 0x48 */ CAM_SET_CONNECT0, // Smoothly and gradually return camera to Player after a cutscene
    /* 0x49 */ CAM_SET_PINNACLE_ROCK, // Pinnacle Rock trench "MORAY"
    /* 0x4A */ CAM_SET_NORMAL2, // Generic camera 2, used in various places
    /* 0x4B */ CAM_SET_HONEY_AND_DARLING_2, // "BOMBBOWL"
    /* 0x4C */ CAM_SET_CIRCLEA, // Unknown, Circle 10
    /* 0x4D */ CAM_SET_WHIRLPOOL, // Great Bay Temple Central Room Whirlpool
    /* 0x4E */ CAM_SET_CUCCO_SHACK, // "KOKKOGAME"
    /* 0x4F */ CAM_SET_GIANT, // "Giants Mask in Twinmold's Lair"
    /* 0x50 */ CAM_SET_SCENE0, // Entering doors to a new scene
    /* 0x51 */ CAM_SET_ROOM1, // Certain rooms eg. some rooms in Stock Pot Inn
    /* 0x52 */ CAM_SET_WATER2, // Swimming as Zora in Great Bay Temple
    /* 0x53 */ CAM_SET_WOODFALL_SWAMP, // Woodfall inside the swamp, but not on the platforms, "SOKONASI"
    /* 0x54 */ CAM_SET_FORCEKEEP, // Unknown
    /* 0x55 */ CAM_SET_PARALLEL1, // Unknown
    /* 0x56 */ CAM_SET_START1, // Used when entering the lens cave
    /* 0x57 */ CAM_SET_ROOM2, // Certain rooms eg. Deku King's Chamber, Ocean Spider House "ROOM2"
    /* 0x58 */ CAM_SET_NORMAL4, // Generic camera 4, used in Ikana Graveyard
    /* 0x59 */ CAM_SET_ELEGY_SHELL, // cutscene after playing elegy of emptyness and spawning a shell "SHELL"
    /* 0x5A */ CAM_SET_DUNGEON4, // Used in Pirates Fortress Interior, hidden room near hookshot
    /* 0x5B */ CAM_SET_MAX
} CameraSettingType;

typedef enum {
    /* 0x00 */ CAM_MODE_NORMAL,
    /* 0x01 */ CAM_MODE_JUMP,
    /* 0x02 */ CAM_MODE_GORONDASH,
    /* 0x03 */ CAM_MODE_DEKUSHOOT, // "CAM_MODE_NUTSSHOT"
    /* 0x04 */ CAM_MODE_BOWARROWZ,
    /* 0x05 */ CAM_MODE_DEKUFLY, // "CAM_MODE_NUTSFLY"
    /* 0x06 */ CAM_MODE_FIRSTPERSON, // "SUBJECT"
    /* 0x07 */ CAM_MODE_FOLLOWBOOMERANG, // "BOOKEEPON"
    /* 0x08 */ CAM_MODE_ZORAFIN,
    /* 0x09 */ CAM_MODE_FOLLOWTARGET, // "KEEPON"
    /* 0x0A */ CAM_MODE_TARGET, // "PARALLEL"
    /* 0x0B */ CAM_MODE_TALK, 
    /* 0x0C */ CAM_MODE_SLINGSHOT, // "PACHINCO"
    /* 0x0D */ CAM_MODE_BOWARROW,
    /* 0x0E */ CAM_MODE_BATTLE,
    /* 0x0F */ CAM_MODE_DEKUHIDE, // "CAM_MODE_NUTSHIDE"
    /* 0x10 */ CAM_MODE_STILL,
    /* 0x11 */ CAM_MODE_CHARGE,
    /* 0x12 */ CAM_MODE_CLIMB,
    /* 0x13 */ CAM_MODE_CLIMBZ,
    /* 0x14 */ CAM_MODE_HOOKSHOT, // "FOOKSHOT"
    /* 0x15 */ CAM_MODE_FREEFALL,
    /* 0x16 */ CAM_MODE_HANG,
    /* 0x17 */ CAM_MODE_HANGZ,
    /* 0x18 */ CAM_MODE_PUSHPULL,
    /* 0x19 */ CAM_MODE_DEKUFLYZ, // "CAM_MODE_NUTSFLYZ"
    /* 0x1A */ CAM_MODE_GORONJUMP,
    /* 0x1B */ CAM_MODE_BOOMERANG,
    /* 0x1C */ CAM_MODE_CHARGEZ,
    /* 0x1D */ CAM_MODE_ZORAFINZ,
    /* 0x1E */ CAM_MODE_MAX
} CameraModeType;

typedef enum {
    /* 0x00 */ CAM_FUNC_NONE,
    /* 0x01 */ CAM_FUNC_NORMAL0,
    /* 0x02 */ CAM_FUNC_NORMAL1,
    /* 0x03 */ CAM_FUNC_NORMAL2,
    /* 0x04 */ CAM_FUNC_NORMAL3,
    /* 0x05 */ CAM_FUNC_NORMAL4,
    /* 0x06 */ CAM_FUNC_PARALLEL0,
    /* 0x07 */ CAM_FUNC_PARALLEL1,
    /* 0x08 */ CAM_FUNC_PARALLEL2,
    /* 0x09 */ CAM_FUNC_PARALLEL3,
    /* 0x0A */ CAM_FUNC_PARALLEL4,
    /* 0x0B */ CAM_FUNC_KEEPON0,
    /* 0x0C */ CAM_FUNC_KEEPON1,
    /* 0x0D */ CAM_FUNC_KEEPON2,
    /* 0x0E */ CAM_FUNC_KEEPON3,
    /* 0x0F */ CAM_FUNC_KEEPON4,
    /* 0x10 */ CAM_FUNC_SUBJECT0,
    /* 0x11 */ CAM_FUNC_SUBJECT1,
    /* 0x12 */ CAM_FUNC_SUBJECT2,
    /* 0x13 */ CAM_FUNC_SUBJECT3,
    /* 0x14 */ CAM_FUNC_SUBJECT4,
    /* 0x15 */ CAM_FUNC_JUMP0,
    /* 0x16 */ CAM_FUNC_JUMP1,
    /* 0x17 */ CAM_FUNC_JUMP2,
    /* 0x18 */ CAM_FUNC_JUMP3,
    /* 0x19 */ CAM_FUNC_JUMP4,
    /* 0x1A */ CAM_FUNC_BATTLE0,
    /* 0x1B */ CAM_FUNC_BATTLE1,
    /* 0x1C */ CAM_FUNC_BATTLE2,
    /* 0x1D */ CAM_FUNC_BATTLE3,
    /* 0x1E */ CAM_FUNC_BATTLE4,
    /* 0x1F */ CAM_FUNC_FIXED0,
    /* 0x20 */ CAM_FUNC_FIXED1,
    /* 0x21 */ CAM_FUNC_FIXED2,
    /* 0x22 */ CAM_FUNC_FIXED3,
    /* 0x23 */ CAM_FUNC_FIXED4,
    /* 0x24 */ CAM_FUNC_DATA0,
    /* 0x25 */ CAM_FUNC_DATA1,
    /* 0x26 */ CAM_FUNC_DATA2,
    /* 0x27 */ CAM_FUNC_DATA3,
    /* 0x28 */ CAM_FUNC_DATA4,
    /* 0x29 */ CAM_FUNC_UNIQUE0,
    /* 0x2A */ CAM_FUNC_UNIQUE1,
    /* 0x2B */ CAM_FUNC_UNIQUE2,
    /* 0x2C */ CAM_FUNC_UNIQUE3,
    /* 0x2D */ CAM_FUNC_UNIQUE4,
    /* 0x2E */ CAM_FUNC_UNIQUE5,
    /* 0x2F */ CAM_FUNC_UNIQUE6,
    /* 0x30 */ CAM_FUNC_UNIQUE7,
    /* 0x31 */ CAM_FUNC_UNIQUE8,
    /* 0x32 */ CAM_FUNC_UNIQUE9,
    /* 0x33 */ CAM_FUNC_DEMO0,
    /* 0x34 */ CAM_FUNC_DEMO1,
    /* 0x35 */ CAM_FUNC_DEMO2,
    /* 0x36 */ CAM_FUNC_DEMO3,
    /* 0x37 */ CAM_FUNC_DEMO4,
    /* 0x38 */ CAM_FUNC_DEMO5,
    /* 0x39 */ CAM_FUNC_DEMO6,
    /* 0x3A */ CAM_FUNC_DEMO7,
    /* 0x3B */ CAM_FUNC_DEMO8,
    /* 0x3C */ CAM_FUNC_DEMO9,
    /* 0x3D */ CAM_FUNC_SPECIAL0,
    /* 0x3E */ CAM_FUNC_SPECIAL1,
    /* 0x3F */ CAM_FUNC_SPECIAL2,
    /* 0x40 */ CAM_FUNC_SPECIAL3,
    /* 0x41 */ CAM_FUNC_SPECIAL4,
    /* 0x42 */ CAM_FUNC_SPECIAL5,
    /* 0x43 */ CAM_FUNC_SPECIAL6,
    /* 0x44 */ CAM_FUNC_SPECIAL7,
    /* 0x45 */ CAM_FUNC_SPECIAL8,
    /* 0x46 */ CAM_FUNC_SPECIAL9,
    /* 0x47 */ CAM_FUNC_MAX
} CameraFuncType;

typedef enum {
    /* 0x00 */ CAM_DATA_00,
    /* 0x01 */ CAM_DATA_01,
    /* 0x02 */ CAM_DATA_02,
    /* 0x03 */ CAM_DATA_03,
    /* 0x04 */ CAM_DATA_04,
    /* 0x05 */ CAM_DATA_05,
    /* 0x06 */ CAM_DATA_06,
    /* 0x07 */ CAM_DATA_07,
    /* 0x08 */ CAM_DATA_08,
    /* 0x09 */ CAM_DATA_09,
    /* 0x0A */ CAM_DATA_10,
    /* 0x0B */ CAM_DATA_11,
    /* 0x0C */ CAM_DATA_12,
    /* 0x0D */ CAM_DATA_13,
    /* 0x0E */ CAM_DATA_14,
    /* 0x0F */ CAM_DATA_15,
    /* 0x10 */ CAM_DATA_16,
    /* 0x11 */ CAM_DATA_17,
    /* 0x12 */ CAM_DATA_18,
    /* 0x13 */ CAM_DATA_19,
    /* 0x14 */ CAM_DATA_20,
    /* 0x15 */ CAM_DATA_21,
} CameraDataType;

typedef struct {
    /* 0x0 */ s16 val;
    /* 0x2 */ s16 param;
} CameraModeValue; // size = 0x4

typedef struct {
    /* 0x0 */ s16 funcId;
    /* 0x2 */ s16 numValues;
    /* 0x4 */ CameraModeValue* values;
} CameraMode; // size = 0x8

/**
 * Flags:
 * (flags & 0xF): Priority (lower value has higher priority)
 * (flags & 0x40000000): Store previous setting and bgCamData, also ignores water checks
 * (flags & 0x80000000): Set camera setting based on bg/scene data and reset action function state
 */
typedef struct {
    /* 0x0 */ u32 validModes;
    /* 0x4 */ u32 flags;
    /* 0x8 */ CameraMode* cameraModes;
} CameraSetting; // size = 0xC

typedef struct Camera {
    /* 0x000 */ u8 paramData[0x50]; // function Data, acts like a heap that's reset every time a new action function is switched to
    /* 0x050 */ Vec3f at;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f up;
    /* 0x074 */ Vec3f eyeNext;
    /* 0x080 */ Vec3f quakeOffset;
    /* 0x08C */ struct PlayState* play;
    /* 0x090 */ Actor* trackActor; // the actor the camera is focused on. Most often Player, but can be any actor
    /* 0x094 */ PosRot trackActorPosRot;
    /* 0x0A8 */ Actor* target; // the actor that is being z-targeted
    /* 0x0AC */ PosRot targetPosRot;
    /* 0x0C0 */ f32 rUpdateRateInv;
    /* 0x0C4 */ f32 pitchUpdateRateInv;
    /* 0x0C8 */ f32 yawUpdateRateInv;
    /* 0x0CC */ f32 yOffsetUpdateRate;
    /* 0x0D0 */ f32 xzOffsetUpdateRate;
    /* 0x0D4 */ f32 fovUpdateRate;
    /* 0x0D8 */ f32 xzSpeed;
    /* 0x0DC */ f32 dist;
    /* 0x0E0 */ f32 speedRatio;
    /* 0x0E4 */ Vec3f atActorOffset;
    /* 0x0F0 */ Vec3f trackActorOffset;
    /* 0x0FC */ f32 fov;
    /* 0x100 */ f32 atLERPStepScale;
    /* 0x104 */ f32 playerFloorHeight;
    /* 0x108 */ Vec3f floorNorm;
    /* 0x114 */ f32 waterYPos;
    /* 0x118 */ s32 waterPrevBgCamDataId;
    /* 0x11C */ s32 waterPrevCamSetting;
    /* 0x120 */ s16 waterQuakeId;
    /* 0x122 */ s16 unk122;
    /* 0x124 */ void* data0;
    /* 0x128 */ void* data1;
    /* 0x12C */ s16 data2;
    /* 0x12E */ s16 data3;
    /* 0x130 */ s16 uid;
    /* 0x132 */ UNK_TYPE1 pad132;
    /* 0x134 */ Vec3s inputDir;
    /* 0x13A */ Vec3s camDir;
    /* 0x140 */ s16 status;
    /* 0x142 */ s16 setting;
    /* 0x144 */ s16 mode;
    /* 0x146 */ s16 bgId;
    /* 0x148 */ s16 bgCamDataId;
    /* 0x14A */ s16 behaviorFlags;
    /* 0x14C */ s16 stateFlags;
    /* 0x14E */ s16 childCamId;
    /* 0x150 */ s16 doorTimer1; // a door timer used when door cam is indexed from bgCamDataId
    /* 0x152 */ s16 unk152;
    /* 0x154 */ s16 prevSetting;
    /* 0x156 */ s16 nextCamSceneDataId;
    /* 0x158 */ s16 nextBgId;
    /* 0x15A */ s16 roll;
    /* 0x15C */ s16 viewFlags;
    /* 0x15E */ s16 animState; // Determines the current state of the current camera behavior function
    /* 0x160 */ s16 unk160;
    /* 0x162 */ s16 doorTimer2; // a door timer used when door cam is indexed from bgCamDataId
    /* 0x164 */ s16 camId;
    /* 0x166 */ s16 prevBgCamDataId;
    /* 0x168 */ s16 unk168;
    /* 0x16C */ Vec3f meshActorPos;
} Camera; // size = 0x178

#endif
