#ifndef _Z64CAMERA_H_
#define _Z64CAMERA_H_

#include "ultra64.h"

// Camera Id flags
#define NUM_CAMS 4
#define CAM_ID_MAIN 0
#define CAM_ID_SUB_FIRST 1
#define CAM_ID_NONE -1
#define CAM_ID_ACTIVE -1

// Camera shrink window flags
#define SHRINKWINVAL_NONE 0x0000
#define SHRINKWINVAL_SMALL 0x1000
#define SHRINKWINVAL_MEDIUM 0x2000
#define SHRINKWINVAL_LARGE 0x3000
#define SHRINKWINVAL_NONE_4 0x4000
#define SHRINKWIN_MAG 0x8000
#define SHRINKWINVAL_PREV 0xF000
#define SHRINKWIN_MASK 0xF000
#define SHRINKWINVAL_MASK 0x7000

// Camera Interface flags
#define IFACE_ALPHA(alpha) ((alpha) << 8)
#define IFACE_ALPHA_MASK (0x0F00)

// Camera bg surface flags
#define FLG_ADJSLOPE (1 << 0)
#define FLG_OFFGROUND (1 << 7)

#define CAM_TRACKED_PLAYER(camera) ((Player*)camera->trackActor)

// Camera flags1. Flags spcifically for settings, modes, and scene/bg/cs camData
// Used to store current state, but not read from with only 1 exception (possibly read from outside of camera)
// Setting (0x1, 0x10)
#define CAM_FLAG1_SET_USE_PRIORITY (1 << 0) // Use settings priority system
#define CAM_FLAG1_SET_2 (1 << 4)
// Mode (0x2, 0x20)
#define CAM_FLAG1_MODE_1 (1 << 1)
#define CAM_FLAG1_MODE_2 (1 << 5)
// scene Data (0x4, 0x40)
#define CAM_FLAG1_SCENE_DATA_1 (1 << 2)
#define CAM_FLAG1_SCENE_DATA_2 (1 << 6)

// Camera flags2. Variety of generic flags
#define CAM_FLAG2_1 (1 << 0) // Must be set for the camera from changing settings based on the bg surface
#define CAM_FLAG2_2 (1 << 1)
#define CAM_FLAG2_4 (1 << 2)
#define CAM_FLAG2_8 (1 << 3)
#define CAM_FLAG2_10 (1 << 4)
#define CAM_FLAG2_20 (1 << 5)
#define CAM_FLAG2_40 (1 << 6)
#define CAM_FLAG2_80 (1 << 7)
#define CAM_FLAG2_100 (1 << 8)
#define CAM_FLAG2_200 (1 << 9)
#define CAM_FLAG2_400 (1 << 10) // Surpresses the camera from changing settings based on the bg surface
#define CAM_FLAG2_800 (1 << 11)
#define CAM_FLAG2_1000 (1 << 12)
#define CAM_FLAG2_2000 (1 << 13)
#define CAM_FLAG2_4000 (1 << 14)
#define CAM_FLAG2_8000 (1 << 15)

// Camera paramFlags. Each corresponds to a struct member from the camera struct
#define CAM_PARAM_FLAG_1 (1 << 0)
#define CAM_PARAM_FLAG_2 (1 << 1)
#define CAM_PARAM_FLAG_4 (1 << 2)
#define CAM_PARAM_FLAG_8 (1 << 3)
#define CAM_PARAM_FLAG_10 (1 << 4)
#define CAM_PARAM_FLAG_20 (1 << 5)
#define CAM_PARAM_FLAG_40 (1 << 6)

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
    /* 0x01 */ CAM_FUNC_NORM0,
    /* 0x02 */ CAM_FUNC_NORM1,
    /* 0x03 */ CAM_FUNC_NORM2,
    /* 0x04 */ CAM_FUNC_NORM3,
    /* 0x05 */ CAM_FUNC_NORM4,
    /* 0x06 */ CAM_FUNC_PARA0,
    /* 0x07 */ CAM_FUNC_PARA1,
    /* 0x08 */ CAM_FUNC_PARA2,
    /* 0x09 */ CAM_FUNC_PARA3,
    /* 0x0A */ CAM_FUNC_PARA4,
    /* 0x0B */ CAM_FUNC_KEEP0,
    /* 0x0C */ CAM_FUNC_KEEP1,
    /* 0x0D */ CAM_FUNC_KEEP2,
    /* 0x0E */ CAM_FUNC_KEEP3,
    /* 0x0F */ CAM_FUNC_KEEP4,
    /* 0x10 */ CAM_FUNC_SUBJ0,
    /* 0x11 */ CAM_FUNC_SUBJ1,
    /* 0x12 */ CAM_FUNC_SUBJ2,
    /* 0x13 */ CAM_FUNC_SUBJ3,
    /* 0x14 */ CAM_FUNC_SUBJ4,
    /* 0x15 */ CAM_FUNC_JUMP0,
    /* 0x16 */ CAM_FUNC_JUMP1,
    /* 0x17 */ CAM_FUNC_JUMP2,
    /* 0x18 */ CAM_FUNC_JUMP3,
    /* 0x19 */ CAM_FUNC_JUMP4,
    /* 0x1A */ CAM_FUNC_BATT0,
    /* 0x1B */ CAM_FUNC_BATT1,
    /* 0x1C */ CAM_FUNC_BATT2,
    /* 0x1D */ CAM_FUNC_BATT3,
    /* 0x1E */ CAM_FUNC_BATT4,
    /* 0x1F */ CAM_FUNC_FIXD0,
    /* 0x20 */ CAM_FUNC_FIXD1,
    /* 0x21 */ CAM_FUNC_FIXD2,
    /* 0x22 */ CAM_FUNC_FIXD3,
    /* 0x23 */ CAM_FUNC_FIXD4,
    /* 0x24 */ CAM_FUNC_DATA0,
    /* 0x25 */ CAM_FUNC_DATA1,
    /* 0x26 */ CAM_FUNC_DATA2,
    /* 0x27 */ CAM_FUNC_DATA3,
    /* 0x28 */ CAM_FUNC_DATA4,
    /* 0x29 */ CAM_FUNC_UNIQ0,
    /* 0x2A */ CAM_FUNC_UNIQ1,
    /* 0x2B */ CAM_FUNC_UNIQ2,
    /* 0x2C */ CAM_FUNC_UNIQ3,
    /* 0x2D */ CAM_FUNC_UNIQ4,
    /* 0x2E */ CAM_FUNC_UNIQ5,
    /* 0x2F */ CAM_FUNC_UNIQ6,
    /* 0x30 */ CAM_FUNC_UNIQ7,
    /* 0x31 */ CAM_FUNC_UNIQ8,
    /* 0x32 */ CAM_FUNC_UNIQ9,
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
    /* 0x3D */ CAM_FUNC_SPEC0,
    /* 0x3E */ CAM_FUNC_SPEC1,
    /* 0x3F */ CAM_FUNC_SPEC2,
    /* 0x40 */ CAM_FUNC_SPEC3,
    /* 0x41 */ CAM_FUNC_SPEC4,
    /* 0x42 */ CAM_FUNC_SPEC5,
    /* 0x43 */ CAM_FUNC_SPEC6,
    /* 0x44 */ CAM_FUNC_SPEC7,
    /* 0x45 */ CAM_FUNC_SPEC8,
    /* 0x46 */ CAM_FUNC_SPEC9,
    /* 0x47 */ CAM_FUNC_MAX
} CameraFuncType;

typedef enum {
    /* 0x00 */ CAM_DATA_Y_OFFSET,
    /* 0x01 */ CAM_DATA_01,
    /* 0x02 */ CAM_DATA_02,
    /* 0x03 */ CAM_DATA_PITCHTARGET,
    /* 0x04 */ CAM_DATA_04,
    /* 0x05 */ CAM_DATA_05,
    /* 0x06 */ CAM_DATA_YAWDIFFRANGE,
    /* 0x07 */ CAM_DATA_FOV,
    /* 0x08 */ CAM_DATA_08,
    /* 0x09 */ CAM_DATA_FLAGS,
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


/*================================
 *   MISC DATA
 *================================
 */

// Camera Collision Check
typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f norm;
    /* 0x18 */ CollisionPoly* poly;
    /* 0x1C */ VecSph sphNorm;
    /* 0x24 */ s32 bgId;
} CamColChk; // size = 0x28

typedef struct {
    /* 0x00 */ Vec3f collisionClosePoint;
    /* 0x0C */ CamColChk atEyeColChk;
    /* 0x34 */ CamColChk eyeAtColChk;
    /* 0x5C */ f32 swingUpdateRate;
    /* 0x60 */ s16 pitch;
    /* 0x62 */ s16 yaw;
    /* 0x64 */ s16 unk_64;
    /* 0x66 */ s16 unk_66; // startSwingTimer
} SwingAnimation; // size = 0x68


/*================================
 *   MAIN CAMERA STRUCT
 *================================
 */

typedef struct Camera {
    /* 0x000 */ char actionFuncHeap[0x50]; // function Data, acts like a heap that's reset every time a new action function is switched to
    /* 0x050 */ Vec3f at;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f up;
    /* 0x074 */ Vec3f eyeNext;
    /* 0x080 */ Vec3f skyboxOffset;
    /* 0x08C */ struct GlobalContext* globalCtx;
    /* 0x090 */ Actor* trackActor; // trackActor Is likely Actor* not Player*. This is the actor the camera focuses on
    /* 0x094 */ PosRot trackActorPosRot;
    /* 0x0A8 */ Actor* target; // targetedActor
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
    /* 0x0E4 */ Vec3f atActorOffset; // Displacement from trackActor to at (Offset between camera's at-coordinates and centered actor's coordinates)
    /* 0x0F0 */ Vec3f trackActorPosRelToCam; // Displacement from cam's trackActor pos to real-time trackActor pos (Offset between camera's trackActor-coordinates and centered actor's coordinates)
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
    /* 0x14A */ s16 flags1;
    /* 0x14C */ s16 flags2;
    /* 0x14E */ s16 childCamId;
    /* 0x150 */ s16 doorTimer1; // a door timer used when door cam is indexed from bgCamDataId
    /* 0x152 */ s16 unk152;
    /* 0x154 */ s16 prevSetting;
    /* 0x156 */ s16 nextCamSceneDataId;
    /* 0x158 */ s16 nextBgId;
    /* 0x15A */ s16 roll;
    /* 0x15C */ s16 paramFlags;
    /* 0x15E */ s16 actionFuncState; // A state that starts at 0 when a new action function is started, and increments
                                     // upwards as the action function reaches new states
    /* 0x160 */ s16 unk160;
    /* 0x162 */ s16 doorTimer2; // a door timer used when door cam is indexed from bgCamDataId
    /* 0x164 */ s16 camId;
    /* 0x166 */ s16 prevBgCamDataId;
    /* 0x168 */ s16 unk168;
    /* 0x16C */ Vec3f meshActorPos;
} Camera; // size = 0x178


/*================================
 *   CAMERA MINI-HEAP
 *================================
 */

/**
 * Each camera has its own mini-heap stored within the first 50 bytes, called camera->actionFuncHeap
 * This heap is used by action functions to store data that needs to persist over multiple calls to the action function
 * Every action function has its own custom structs to store data in a way customized to that particular function
 * This data is broken up into two types:
 *     - Fixed Data: Camera Action-Function data that is predefined in Camera_Data.c. Is read-only data (a majority of camera_data is for this type of data)
 *     - Dynamic Data: Camera Action-Function data that is calculated at run-time but needs to persist over multiple function calls
 */

/**
 * Everything below in this file is for these customized functions
 */

#define CAM_GET_STATIC_DATA(type) &((type*)camera->actionFuncHeap)->fixedData
#define CAM_GET_DYNAMIC_DATA(type) &((type*)camera->actionFuncHeap)->dynamicData

// Camera will reload static data from camera_data
#define RELOAD_PARAMS \
    (camera->actionFuncState == 0 || camera->actionFuncState == 10 || camera->actionFuncState == 20)

/**
 * All static data is stored in memory as s16, and then converted to the appropriate type during runtime.
 * If a small f32 is being stored as an s16, it is common to store that value 100 times larger than the original value.
 * This is then scaled back down during runtime with the SCALED_STATIC_DATA macro.
 */
#define SCALED_STATIC_DATA(x) ((x) * 0.01f)

// Load the next setting from camera_data.c
#define READ_STATIC_DATA_VAL ((values++)->val)
// Load the next setting from camera_data.c and scale
#define READ_SCALED_STATIC_DATA_VAL SCALED_STATIC_DATA(READ_STATIC_DATA_VAL)



/*================================
 *   Camera_Normal1() HEAP DATA
 *================================
 */

#define NORM1_FIXED_DATA(yOffset, data01, data02, pitchTarget, eyeStepScale, posStepScale, yawDiffRange, fov, data08, flags) \
    { yOffset,      CAM_DATA_Y_OFFSET }, \
    { data01,       CAM_DATA_01 }, \
    { data02,       CAM_DATA_02 }, \
    { pitchTarget,  CAM_DATA_PITCHTARGET }, \
    { eyeStepScale, CAM_DATA_04 }, \
    { posStepScale, CAM_DATA_05 }, \
    { yawDiffRange, CAM_DATA_YAWDIFFRANGE }, \
    { fov,          CAM_DATA_FOV }, \
    { data08,       CAM_DATA_08 }, \
    { flags,        CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 unk_00; // yOffset
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14; // attenuationYawDiffRange
    /* 0x18 */ f32 unk_18; // fovTarget
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20; // pitchTarget
    /* 0x22 */ s16 unk_22; // flags
} Normal1FixedData; // size = 0x24

typedef struct {
    /* 0x00 */ f32 unk_00; // yPos
    /* 0x04 */ f32 unk_04; // xzSpeed
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A; // angle
    /* 0x0C */ s16 unk_0C; // flags (May be s32)
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ f32 unk_10; // set to float
} Normal1DynamicData; // size = 0x14

typedef struct {
    /* 0x00 */ Normal1FixedData fixedData;
    /* 0x24 */ Normal1DynamicData dynamicData;
} Normal1; // size = 0x38

#define NORM1_FLG_1 (1 << 0)
#define NORM1_FLG_2 (1 << 1)
#define NORM1_FLG_4 (1 << 2)
#define NORM1_FLG_8 (1 << 3)
#define NORM1_FLG_10 (1 << 4)
#define NORM1_FLG_20 (1 << 5)
#define NORM1_FLG_40 (1 << 6)
#define NORM1_FLG_80 (1 << 7)


/*================================
 *   Camera_Normal2() HEAP DATA
 *================================
 */

// Unused Camera RemoteBomb Setting

#define NORM2_FIXED_DATA(yOffset, data01, data02, pitchTarget, data04, fov, data08, flags) \
    { yOffset,     CAM_DATA_Y_OFFSET }, \
    { data01,      CAM_DATA_01 }, \
    { data02,      CAM_DATA_02 }, \
    { pitchTarget, CAM_DATA_PITCHTARGET }, \
    { data04,      CAM_DATA_04 }, \
    { fov,         CAM_DATA_FOV }, \
    { data08,      CAM_DATA_08 }, \
    { flags,       CAM_DATA_FLAGS }

#define NORM2_FLG_2 (1 << 1)


/*================================
 *   Camera_Normal3() HEAP DATA
 *================================
 */

#define NORM3_FIXED_DATA(yOffset, data01, data02, pitchTarget, eyeStepScale, posStepScale, fov, data08, flags) \
    { yOffset,      CAM_DATA_Y_OFFSET }, \
    { data01,       CAM_DATA_01 }, \
    { data02,       CAM_DATA_02 }, \
    { pitchTarget,  CAM_DATA_PITCHTARGET }, \
    { eyeStepScale, CAM_DATA_04 }, \
    { posStepScale, CAM_DATA_05 }, \
    { fov,          CAM_DATA_FOV }, \
    { data08,       CAM_DATA_08 }, \
    { flags,        CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 yOffset;
    /* 0x04 */ f32 distMin;
    /* 0x08 */ f32 distMax;
    /* 0x0C */ f32 yawUpdateRateInv;
    /* 0x10 */ f32 pitchUpdateRateInv;
    /* 0x14 */ f32 fovTarget;
    /* 0x18 */ f32 maxAtLERPScale;
    /* 0x1C */ s16 pitchTarget;
    /* 0x1E */ s16 flags;
} Normal3FixedData; // size = 0x20

typedef struct {
    /* 0x00 */ f32 isZero; // set but unused
    /* 0x04 */ f32 yPosOffset;
    /* 0x08 */ s16 curPitch;
    /* 0x0A */ s16 yawUpdateRate;
    /* 0x0C */ s16 yawTimer;
    /* 0x0E */ s16 distTimer;
    /* 0x10 */ s16 flag;
    /* 0x12 */ s16 is1200; // set but unused
} Normal3DynamicData; // size = 0x14

typedef struct {
    /* 0x00 */ Normal3FixedData fixedData;
    /* 0x20 */ Normal3DynamicData dynamicData;
} Normal3; // size = 0x34

#define NORM3_FLG_2 (1 << 1)
#define NORM3_FLG_20 (1 << 5)
#define NORM3_FLG_40 (1 << 6)
#define NORM3_FLG_80 (1 << 7)


/*================================
 *   Camera_Normal0() HEAP DATA
 *================================
 */

#define NORM0_FIXED_DATA(yOffset, data01, data02, data21, data04, yawDiffRange, fov, data08, flags) \
    { yOffset,      CAM_DATA_Y_OFFSET }, \
    { data01,       CAM_DATA_01 }, \
    { data02,       CAM_DATA_02 }, \
    { data21,       CAM_DATA_21 }, \
    { data04,       CAM_DATA_04 }, \
    { yawDiffRange, CAM_DATA_YAWDIFFRANGE }, \
    { fov,          CAM_DATA_FOV }, \
    { data08,       CAM_DATA_08 }, \
    { flags,        CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} Normal0FixedData; // size = 0x20

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ s16 unk_2C;
} Normal0DynamicData; // size = 0x30

typedef struct {
    /* 0x00 */ Normal0FixedData fixedData;
    /* 0x20 */ Normal0DynamicData dynamicData;
} Normal0; // size = 0x50

#define NORM0_FLG_1 (1 << 0)
#define NORM0_FLG_4 (1 << 2)
#define NORM0_FLG_10 (1 << 4)
#define NORM0_FLG_80 (1 << 7)


/*================================
 *   Camera_Parallel1() HEAP DATA
 *================================
 */

#define PARA1_FIXED_DATA(yOffset, data01, data02, pitchTarget, data10, data04, data05, fov, data08, flags, data11, data12) \
    { yOffset,      CAM_DATA_Y_OFFSET }, \
    { data01,       CAM_DATA_01 }, \
    { data02,       CAM_DATA_02 }, \
    { pitchTarget,  CAM_DATA_PITCHTARGET }, \
    { data10,       CAM_DATA_10 }, \
    { data04,       CAM_DATA_04 }, \
    { data05,       CAM_DATA_05 }, \
    { fov,          CAM_DATA_FOV }, \
    { data08,       CAM_DATA_08 }, \
    { flags,        CAM_DATA_FLAGS }, \
    { data11,       CAM_DATA_11 }, \
    { data12,       CAM_DATA_12 }

// Same as above but with extra unused entry
#define PARA1_FIXED_DATA_ALT(yOffset, data01, data02, pitchTarget, data10, data04, data05, fov, data08, flags, data11, data12, data18) \
    { yOffset,      CAM_DATA_Y_OFFSET }, \
    { data01,       CAM_DATA_01 }, \
    { data02,       CAM_DATA_02 }, \
    { pitchTarget,  CAM_DATA_PITCHTARGET }, \
    { data10,       CAM_DATA_10 }, \
    { data04,       CAM_DATA_04 }, \
    { data05,       CAM_DATA_05 }, \
    { fov,          CAM_DATA_FOV }, \
    { data08,       CAM_DATA_08 }, \
    { flags,        CAM_DATA_FLAGS }, \
    { data11,       CAM_DATA_11 }, \
    { data12,       CAM_DATA_12 }, \
    { data18,       CAM_DATA_18 }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
} Parallel1FixedData; // size = 0x28

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
} Parallel1DynamicData; // size = 0x28

typedef struct {
    /* 0x00 */ Parallel1FixedData fixedData;
    /* 0x28 */ Parallel1DynamicData dynamicData;
} Parallel1; // size = 0x50

#define PARA1_FLG_1 (1 << 0)
#define PARA1_FLG_2 (1 << 1)
#define PARA1_FLG_4 (1 << 2)
#define PARA1_FLG_8 (1 << 3)
#define PARA1_FLG_10 (1 << 4)
#define PARA1_FLG_20 (1 << 5)
#define PARA1_FLG_40 (1 << 6)
#define PARA1_FLG_80 (1 << 7)


/*================================
 *   Camera_Parallel2() HEAP DATA
 *================================
 */

// Unused Camera Maze Setting

#define PARA2_FIXED_DATA(yOffset, data02, data01, pitchTarget, data04, fov, data08, flags) \
    { yOffset,     CAM_DATA_Y_OFFSET }, \
    { data02,      CAM_DATA_02 }, \
    { data01,      CAM_DATA_01 }, \
    { pitchTarget, CAM_DATA_PITCHTARGET }, \
    { data04,      CAM_DATA_04 }, \
    { fov,         CAM_DATA_FOV }, \
    { data08,      CAM_DATA_08 }, \
    { flags,       CAM_DATA_FLAGS }

#define PARA2_FLG_2 (1 << 1)


/*================================
 *   Camera_Jump2() HEAP DATA
 *================================
 */

#define JUMP2_FIXED_DATA(yOffset, data01, data02, data20, data04, data05, fov, data08, flags) \
    { yOffset,     CAM_DATA_Y_OFFSET }, \
    { data01,      CAM_DATA_01 }, \
    { data02,      CAM_DATA_02 }, \
    { data20,      CAM_DATA_20 }, \
    { data04,      CAM_DATA_04 }, \
    { data05,      CAM_DATA_05 }, \
    { fov,         CAM_DATA_FOV }, \
    { data08,      CAM_DATA_08 }, \
    { flags,       CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
} Jump2FixedData; // size = 0x24

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s32 unk_10; // unused?
    /* 0x1C */ s16 unk_1C;
} Jump2DynamicData; // size = 0x20

typedef struct {
    /* 0x00 */ Jump2FixedData fixedData;
    /* 0x02 */ Jump2DynamicData dynamicData;
} Jump2; // size = 0x44

#define JUMP2_FLG_2 (1 << 1)
#define JUMP2_FLG_4 (1 << 2)


/*================================
 *   Camera_Jump3() HEAP DATA
 *================================
 */

#define JUMP3_FIXED_DATA(yOffset, data01, data02, pitchTarget, data04, data05, yawDiffRange, fov, data08, flags) \
    { yOffset,      CAM_DATA_Y_OFFSET }, \
    { data01,       CAM_DATA_01 }, \
    { data02,       CAM_DATA_02 }, \
    { pitchTarget,  CAM_DATA_PITCHTARGET }, \
    { data04,       CAM_DATA_04 }, \
    { data05,       CAM_DATA_05 }, \
    { yawDiffRange, CAM_DATA_YAWDIFFRANGE }, \
    { fov,          CAM_DATA_FOV }, \
    { data08,       CAM_DATA_08 }, \
    { flags,        CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 unk_00; // yOffset
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14; // attenuationYawDiffRange
    /* 0x18 */ f32 unk_18; // fovTarget
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22; // flags
} Jump3FixedData; // size = 0x24

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C; // mode
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x1C */ s16 unk_1C;
} Jump3DynamicData; // size = 0x20

typedef struct {
    /* 0x00 */ Jump3FixedData fixedData; // yOffset
    /* 0x24 */ Jump3DynamicData dynamicData;
} Jump3; // size = 0x44

#define JUMP3_FLG_1 (1 << 0)
#define JUMP3_FLG_4 (1 << 2)
#define JUMP3_FLG_8 (1 << 3)
#define JUMP3_FLG_10 (1 << 4)
#define JUMP3_FLG_20 (1 << 5)
#define JUMP3_FLG_40 (1 << 6)
#define JUMP3_FLG_80 (1 << 7)


/*================================
 *   Camera_Battle1() HEAP DATA
 *================================
 */

#define BATT1_FIXED_DATA(yOffset, data01, data02, data13, data14, data15, data16, data17, fov, data08, flags, data11, data18) \
    { yOffset, CAM_DATA_Y_OFFSET }, \
    { data01,  CAM_DATA_01 }, \
    { data02,  CAM_DATA_02 }, \
    { data13,  CAM_DATA_13 }, \
    { data14,  CAM_DATA_14 }, \
    { data15,  CAM_DATA_15 }, \
    { data16,  CAM_DATA_16 }, \
    { data17,  CAM_DATA_17 }, \
    { fov,     CAM_DATA_FOV }, \
    { data08,  CAM_DATA_08 }, \
    { flags,   CAM_DATA_FLAGS }, \
    { data11,  CAM_DATA_11 }, \
    { data18,  CAM_DATA_18 }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ s16 unk_30;
} Battle1FixedData; // size = 0x34

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ Actor* unk_08; // targe3t
    /* 0x0C */ s32 unk_0C; // unused?
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} Battle1DynamicData; // size = 0x1C

typedef struct {
    /* 0x00 */ Battle1FixedData fixedData;
    /* 0x24 */ Battle1DynamicData dynamicData;
} Battle1; // size = 0x50

#define BATT1_FLG_1 (1 << 0)
#define BATT1_FLG_2 (1 << 1)
#define BATT1_FLG_10 (1 << 4)
#define BATT1_FLG_80 (1 << 7)


/*================================
 *   Camera_KeepOn1() HEAP DATA
 *================================
 */

#define KEEP1_FIXED_DATA(yOffset, data01, data02, data13, data14, data15, data16, data17, fov, data08, flags, data11) \
    { yOffset, CAM_DATA_Y_OFFSET }, \
    { data01,  CAM_DATA_01 }, \
    { data02,  CAM_DATA_02 }, \
    { data13,  CAM_DATA_13 }, \
    { data14,  CAM_DATA_14 }, \
    { data15,  CAM_DATA_15 }, \
    { data16,  CAM_DATA_16 }, \
    { data17,  CAM_DATA_17 }, \
    { fov,     CAM_DATA_FOV }, \
    { data08,  CAM_DATA_08 }, \
    { flags,   CAM_DATA_FLAGS }, \
    { data11,  CAM_DATA_11 }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ s16 unk_2C;
} KeepOn1FixedData; // size = 0x30

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Actor* unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
} KeepOn1DynamicData; // size = 0x1C

typedef struct {
    /* 0x00 */ KeepOn1FixedData fixedData;
    /* 0x30 */ KeepOn1DynamicData dynamicData;
} KeepOn1; // size = 0x4C

#define KEEP1_FLG_1 (1 << 0)
#define KEEP1_FLG_2 (1 << 1)
#define KEEP1_FLG_10 (1 << 4)
#define KEEP1_FLG_80 (1 << 7)


/*================================
 *   Camera_KeepOn3() HEAP DATA
 *================================
 */

#define KEEP3_FIXED_DATA(yOffset, data01, data02, data13, data14, data15, data16, data17, fov, data08, data04, flags, data18) \
    { yOffset, CAM_DATA_Y_OFFSET }, \
    { data01,  CAM_DATA_01 }, \
    { data02,  CAM_DATA_02 }, \
    { data13,  CAM_DATA_13 }, \
    { data14,  CAM_DATA_14 }, \
    { data15,  CAM_DATA_15 }, \
    { data16,  CAM_DATA_16 }, \
    { data17,  CAM_DATA_17 }, \
    { fov,     CAM_DATA_FOV }, \
    { data08,  CAM_DATA_08 }, \
    { data04,  CAM_DATA_04 }, \
    { flags,   CAM_DATA_FLAGS }, \
    { data18,  CAM_DATA_18 }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
} KeepOn3FixedData; // size = 0x30

typedef struct {
    /* 0x00 */ f32 unk_00; // Vec3f?
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Actor* unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ s16 unk_1C;
} KeepOn3DynamicData; // size = 0x20

typedef struct {
    /* 0x00 */ KeepOn3FixedData fixedData;
    /* 0x30 */ KeepOn3DynamicData dynamicData;
} KeepOn3; // size = 0x50

#define KEEP3_FLG_20 (1 << 5)
#define KEEP3_FLG_40 (1 << 6)
#define KEEP3_FLG_80 (1 << 7)


/*================================
 *   Camera_KeepOn4() HEAP DATA
 *================================
 */

#define KEEP4_FIXED_DATA(yOffset, data01, pitchTarget, data10, data18, fov, flags, data04, data12) \
    { yOffset,     CAM_DATA_Y_OFFSET }, \
    { data01,      CAM_DATA_01 }, \
    { pitchTarget, CAM_DATA_PITCHTARGET }, \
    { data10,      CAM_DATA_10 }, \
    { data18,      CAM_DATA_18 }, \
    { fov,         CAM_DATA_FOV }, \
    { flags,       CAM_DATA_FLAGS }, \
    { data04,      CAM_DATA_04 }, \
    { data12,      CAM_DATA_12 }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} KeepOn4FixedData; // size = 0x20

typedef struct {
    /* 0x00 */ f32 unk_00; // Vec3f?
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Actor* unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
} KeepOn4DynamicData; // size = 0x1C

typedef struct {
    /* 0x00 */ KeepOn4FixedData fixedData;
    /* 0x20 */ KeepOn4DynamicData dynamicData;
} KeepOn4; // size = 0x3C

#define KEEP4_FLG_2 (1 << 1)
#define KEEP4_FLG_4 (1 << 2)
#define KEEP4_FLG_8 (1 << 3)
#define KEEP4_FLG_40 (1 << 6)


/*================================
 *   Camera_Fixed1() HEAP DATA
 *================================
 */

#define FIXD1_FIXED_DATA(yOffset, data04, fov, flags) \
    { yOffset,     CAM_DATA_Y_OFFSET }, \
    { data04,      CAM_DATA_04 }, \
    { fov,         CAM_DATA_FOV }, \
    { flags,       CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 jfifId;
    /* 0x08 */ f32 fov;
    /* 0x0C */ s16 flags;
} Fixed1FixedData; // size = 0x10

typedef struct {
    /* 0x00 */ PosRot eyePosRotTarget;
    /* 0x14 */ s16 fov;
    /* 0x18 */ Actor* trackActor;
} Fixed1DynamicData; // size = 0x1C

typedef struct {
    /* 0x00 */ Fixed1FixedData fixedData;
    /* 0x10 */ Fixed1DynamicData dynamicData;
} Fixed1; // size = 0x2C

#define FIXD1_FLG_10 (1 << 4)


/*================================
 *   Camera_Fixed2() HEAP DATA
 *================================
 */

#define FIXD2_FIXED_DATA(yOffset, data01, data02, data04, data05, fov, flags) \
    { yOffset,     CAM_DATA_Y_OFFSET }, \
    { data01,      CAM_DATA_01 }, \
    { data02,      CAM_DATA_02 }, \
    { data04,      CAM_DATA_04 }, \
    { data05,      CAM_DATA_05 }, \
    { fov,         CAM_DATA_FOV }, \
    { flags,       CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
} Fixed2FixedData; // size = 0x1C

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
} Fixed2DynamicData; // size = 0x20

typedef struct {
    /* 0x00 */ Fixed2FixedData fixedData;
    /* 0x1C */ Fixed2DynamicData dynamicData;
} Fixed2; // size = 0x3C

#define FIXD2_FLG_1 (1 << 0)
#define FIXD2_FLG_2 (1 << 1)
#define FIXD2_FLG_4 (1 << 2)
#define FIXD2_FLG_8 (1 << 3)
#define FIXD2_FLG_10 (1 << 4)
#define FIXD2_FLG_20 (1 << 5)
#define FIXD2_FLG_40 (1 << 6)
#define FIXD2_FLG_80 (1 << 7)


/*================================
 *   Camera_Subj1() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
} Subj1FixedData; // size = 0x24

typedef struct {
    /* 0x0 */ f32 unk_00;
    /* 0x4 */ s16 unk_04; // yaw
    /* 0x6 */ s16 unk_06; // pitch
    /* 0x8 */ s16 unk_08;
} Subj1DynamicData; // size = 0xC

typedef struct {
    /* 0x00 */ Subj1FixedData fixedData;
    /* 0x24 */ Subj1DynamicData dynamicData;
} Subj1; // size = 0x30

#define SUBJ1_FLG_10 (1 << 4)


/*================================
 *   Camera_Unique2() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
} Unique2FixedData; // size = 0x14

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
} Unique2DynamicData; // size = 0x8

typedef struct {
    /* 0x00 */ Unique2FixedData fixedData;
    /* 0x14 */ Unique2DynamicData dynamicData;
} Unique2; // size = 0x1C

#define UNIQ2_FLG_1 (1 << 0)
#define UNIQ2_FLG_2 (1 << 1)
#define UNIQ2_FLG_10 (1 << 4)
#define UNIQ2_FLG_20 (1 << 5)


/*================================
 *   Camera_Unique0() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x0 */ f32 unk_00;
    /* 0x4 */ f32 unk_04;
    /* 0x8 */ s16 unk_08;
} Unique0FixedData; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ Vec3f unk_28;
    /* 0x34 */ Vec3s unk_34;
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ s16 unk_3E;
} Unique0DynamicData; // size = 0x40

typedef struct {
    /* 0x00 */ Unique0FixedData fixedData;
    /* 0x0C */ Unique0DynamicData dynamicData;
} Unique0; // size = 0x4C

#define UNIQ0_FLG_1 (1 << 0)
#define UNIQ0_FLG_2 (1 << 1)
#define UNIQ0_FLG_10 (1 << 4)


/*================================
 *   Camera_Unique6() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ s16 flags;
} Unique6FixedData; // size = 0x4

typedef struct {
    /* 0x00 */ Unique6FixedData fixedData;
} Unique6; // size = 0x4

#define UNIQ6_FLG_1 (1 << 0)


/*================================
 *   Camera_Demo1() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ s16 flags;
} Demo1FixedData; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ VecSph unk_0C;
    /* 0x14 */ VecSph unk_14;
    /* 0x1C */ s16 unk_1C;
} Demo1DynamicData; // size = 0x20

typedef struct {
    /* 0x00 */ Demo1FixedData fixedData;
    /* 0x04 */ Demo1DynamicData dynamicData;
} Demo1; // size = 0x24


/*================================
 *   Camera_Demo2() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ f32 fov;
    /* 0x04 */ f32 unk_04; // unused
    /* 0x08 */ s16 flags;
} Demo2FixedData; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f initialAt;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 animFrame;
    /* 0x12 */ s16 yawDir;
} Demo2DynamicData; // size = 0x14

typedef struct {
    /* 0x08 */ Demo2FixedData fixedData;
    /* 0x0C */ Demo2DynamicData dynamicData;
} Demo2; // size = 0x20


/*================================
 *   Camera_Demo3() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ s16 flags;
} Demo3FixedData; // size = 0x4

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 timer;
} Demo3DynamicData; // size = 0x8

typedef struct {
    /* 0x00 */ Demo3FixedData fixedData;
    /* 0x04 */ Demo3DynamicData dynamicData;
} Demo3; // size = 0xC


/*================================
 *   Camera_Demo4() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ s16 flags;
} Demo4FixedData; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ VecSph unk_18; // sp18-1C-20--24-26-28 // CutsceneCameraPoint?
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
} Demo4DynamicData; // size = 0x24

typedef struct {
    /* 0x00 */ Demo4FixedData fixedData;
    /* 0x04 */ Demo4DynamicData dynamicData;
} Demo4; // size = 0x28


/*================================
 *   Camera_Demo5() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ s16 flags;
} Demo5FixedData; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ VecSph unk_1C;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 timer;
} Demo5DynamicData; // size = 0x28

typedef struct {
    /* 0x00 */ Demo5FixedData fixedData;
    /* 0x04 */ Demo5DynamicData dynamicData;
} Demo5; // size = 0x2C


/*================================
 *   Camera_Demo0() HEAP DATA
 *================================
 */

typedef struct {
    /* 0x00 */ s16 unk_00;
} Demo0FixedData; // size = 0x4

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ VecSph unk_04;
    /* 0x0C */ VecSph unk_0C;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} Demo0DynamicData; // size = 0x1C

typedef struct {
    /* 0x00 */ Demo0FixedData fixedData;
    /* 0x04 */ Demo0DynamicData dynamicData;
} Demo0; // size = 0x20


/*================================
 *   Camera_Special5() HEAP DATA
 *================================
 */

#define SPEC5_FIXED_DATA(yOffset, eyeDist, minDistForRot, fov, atMaxLERPScale, timerInit, pitch, flags) \
    { yOffset,        CAM_DATA_Y_OFFSET }, \
    { eyeDist,        CAM_DATA_01 }, \
    { minDistForRot,  CAM_DATA_02 }, \
    { fov,            CAM_DATA_PITCHTARGET }, \
    { atMaxLERPScale, CAM_DATA_FOV }, \
    { timerInit,      CAM_DATA_08 }, \
    { pitch,          CAM_DATA_12 }, \
    { flags,          CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 yOffset;
    /* 0x04 */ f32 eyeDist;
    /* 0x08 */ f32 minDistForRot;
    /* 0x0C */ f32 fovTarget;
    /* 0x10 */ f32 atMaxLERPScale;
    /* 0x14 */ s16 timerInit;
    /* 0x16 */ s16 pitch;
    /* 0x18 */ s16 flags;
} Special5FixedData; // size = 0x1C

typedef struct {
    /* 0x00 */ s16 animTimer;
} Special5DynamicData; // size = 0x4

typedef struct {
    /* 0x00 */ Special5FixedData fixedData;
    /* 0x1C */ Special5DynamicData dynamicData;
} Special5; // size = 0x20


/*================================
 *   DOOR HEAP DATA
 *================================
 */

// For functions that deal with doors, an extra struct is added to the heap

typedef struct {
    /* 0x00 */ Actor* doorActor;
    /* 0x04 */ s16 bgCamDataId;
    /* 0x06 */ union {
        Vec3s eye; // position of the camera while exiting a spiral staircase
        struct {
            s16 timer1; // timer while camera is fixed in front of the door
            s16 timer2; // timer while camera is behind the door looking at player
            s16 timer3; // timer while camera turns around to face forward
        };
    };
} DoorParams; // size = 0xC

#define CAM_GET_DOOR_PARAMS(type) &((type*)camera->actionFuncHeap)->doorParams


/*================================
 *   Camera_Special8() HEAP DATA
 *================================
 */

#define SPEC8_FIXED_DATA(yOffset, eyeStepScale, posStepScale, fov, spiralDoorCsLength, flags) \
    { yOffset,            CAM_DATA_Y_OFFSET }, \
    { eyeStepScale,       CAM_DATA_04 }, \
    { posStepScale,       CAM_DATA_05 }, \
    { fov,                CAM_DATA_FOV }, \
    { spiralDoorCsLength, CAM_DATA_12 }, \
    { flags,              CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 yOffset;
    /* 0x04 */ f32 eyeStepScale;
    /* 0x08 */ f32 posStepScale;
    /* 0x0C */ f32 fov;
    /* 0x10 */ s16 spiralDoorCsLength;
    /* 0x12 */ s16 flags;
} Special8FixedData; // size = 0x14

typedef struct {
    /* 0x00 */ Vec3f eye;
    /* 0x0C */ s16 spiralDoorCsFrame; // 1/5th of the length of the cutscene
    /* 0x0E */ s16 fov;
} Special8DynamicData; // size = 0x10

typedef struct {
    /* 0x00 */ DoorParams doorParams;
    /* 0x0C */ Special8FixedData fixedData;
    /* 0x20 */ Special8DynamicData dynamicData;
} Special8; // size = 0x30

#define SPEC8_FLG_1 (1 << 0)
#define SPEC8_FLG_8 (1 << 3)


/*================================
 *   Camera_Special9() HEAP DATA
 *================================
 */

#define SPEC9_FIXED_DATA(yOffset, fov, flags) \
    { yOffset, CAM_DATA_Y_OFFSET }, \
    { fov,     CAM_DATA_FOV }, \
    { flags,   CAM_DATA_FLAGS }

typedef struct {
    /* 0x00 */ f32 yOffset;
    /* 0x04 */ f32 fov;
    /* 0x08 */ s16 flags;
} Special9FixedData; // size = 0xC

typedef struct {
    /* 0x00 */ s16 unk_00;
} Special9DynamicData; // size = 0x4

typedef struct {
    /* 0x00 */ DoorParams doorParams;
    /* 0x0C */ Special9FixedData fixedData;
    /* 0x18 */ Special9DynamicData dynamicData;
} Special9; // size = 0x1C

#define SPEC9_FLG_1 (1 << 0)
#define SPEC9_FLG_2 (1 << 1)
#define SPEC9_FLG_8 (1 << 3)


#endif
