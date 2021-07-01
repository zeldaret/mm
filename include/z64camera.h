#ifndef _Z64CAMERA_H_
#define _Z64CAMERA_H_

#include "ultra64.h"

#define CAM_STAT_CUT        0
#define CAM_STAT_WAIT       1
#define CAM_STAT_UNK3       3
#define CAM_STAT_ACTIVE     7
#define CAM_STAT_UNK100     0x100

#define NUM_CAMS 4
#define MAIN_CAM 0
#define SUBCAM_FIRST 1
#define SUBCAM_FREE 0
#define SUBCAM_NONE -1
#define SUBCAM_ACTIVE -1

#define SHRINKWIN_MASK (0xF000)
#define SHRINKWINVAL_MASK (0x7000)
#define SHRINKWIN_CURVAL (0x8000)
#define IFACE_ALPHA_MASK (0x0F00)

#define RELOAD_PARAMS \
    (camera->animState == 0 || camera->animState == 10 || camera->animState == 20)

#define PCT(x) ((x)*0.01f)
#define NEXTSETTING ((values++)->val)
#define NEXTPCT PCT(NEXTSETTING)

#define BGCAM_POS(v) ((v)[0])
#define BGCAM_ROT(v) ((v)[1])
#define BGCAM_FOV(v) ((v)[2].x)
#define BGCAM_JFIFID(v) ((v)[2].y)
#define BGCAM_UNK(v) ((v)[2].z)

#define FLG_ADJSLOPE (1 << 0)
#define FLG_OFFGROUND (1 << 7)

typedef enum {
    /* 0x00 */ CAM_SET_NONE,
    /* 0x01 */ CAM_SET_NORMAL0,
    /* 0x02 */ CAM_SET_NORMAL3,
    /* 0x03 */ CAM_SET_CIRCLE5,
    /* 0x04 */ CAM_SET_HORSE0,
    /* 0x05 */ CAM_SET_ZORA0,
    /* 0x06 */ CAM_SET_PREREND0,
    /* 0x07 */ CAM_SET_PREREND1,
    /* 0x08 */ CAM_SET_DOORC,
    /* 0x09 */ CAM_SET_DEMO0,
    /* 0x0A */ CAM_SET_FREE0,
    /* 0x0B */ CAM_SET_FUKAN0,
    /* 0x0C */ CAM_SET_NORMAL1,
    /* 0x0D */ CAM_SET_NANAME,
    /* 0x0E */ CAM_SET_CIRCLE0,
    /* 0x0F */ CAM_SET_FIXED0,
    /* 0x10 */ CAM_SET_SPIRAL,
    /* 0x11 */ CAM_SET_DUNGEON0,
    /* 0x12 */ CAM_SET_ITEM0,
    /* 0x13 */ CAM_SET_ITEM1,
    /* 0x14 */ CAM_SET_ITEM2,
    /* 0x15 */ CAM_SET_ITEM3,
    /* 0x16 */ CAM_SET_NAVI,
    /* 0x17 */ CAM_SET_WARP0,
    /* 0x18 */ CAM_SET_DEATH,
    /* 0x19 */ CAM_SET_REBIRTH,
    /* 0x1A */ CAM_SET_TREASURE,
    /* 0x1B */ CAM_SET_TRANSFORM,
    /* 0x1C */ CAM_SET_ATTENTION,
    /* 0x1D */ CAM_SET_WARP1,
    /* 0x1E */ CAM_SET_DUNGEON1,
    /* 0x1F */ CAM_SET_FIXED1,
    /* 0x20 */ CAM_SET_FIXED2,
    /* 0x21 */ CAM_SET_MAZE,
    /* 0x22 */ CAM_SET_REMOTEBOMB,
    /* 0x23 */ CAM_SET_CIRCLE1,
    /* 0x24 */ CAM_SET_CIRCLE2,
    /* 0x25 */ CAM_SET_CIRCLE3,
    /* 0x26 */ CAM_SET_CIRCLE4,
    /* 0x27 */ CAM_SET_FIXED3,
    /* 0x28 */ CAM_SET_TOWER0,
    /* 0x29 */ CAM_SET_PARALLEL0,
    /* 0x2A */ CAM_SET_NORMALD,
    /* 0x2B */ CAM_SET_SUBJECTD,
    /* 0x2C */ CAM_SET_START0,
    /* 0x2D */ CAM_SET_START2,
    /* 0x2E */ CAM_SET_STOP0,
    /* 0x2F */ CAM_SET_JCRUISING,
    /* 0x30 */ CAM_SET_CLIMEMAZE,
    /* 0x31 */ CAM_SET_SIDED,
    /* 0x32 */ CAM_SET_DUNGEON2,
    /* 0x33 */ CAM_SET_BOSS_SHIGE,
    /* 0x34 */ CAM_SET_KEEPBACK,
    /* 0x35 */ CAM_SET_CIRCLE6,
    /* 0x36 */ CAM_SET_CIRCLE7,
    /* 0x37 */ CAM_SET_CHUBOSS,
    /* 0x38 */ CAM_SET_RFIXED1,
    /* 0x39 */ CAM_SET_TRESURE1,
    /* 0x3A */ CAM_SET_BOMBBASKET,
    /* 0x3B */ CAM_SET_CIRCLE8,
    /* 0x3C */ CAM_SET_FUKAN1,
    /* 0x3D */ CAM_SET_DUNGEON3,
    /* 0x3E */ CAM_SET_TELESCOPE,
    /* 0x3F */ CAM_SET_ROOM0,
    /* 0x40 */ CAM_SET_RCIRC0,
    /* 0x41 */ CAM_SET_CIRCLE9,
    /* 0x42 */ CAM_SET_ONTHEPOLE,
    /* 0x43 */ CAM_SET_INBUSH,
    /* 0x44 */ CAM_SET_BOSS_LAST,
    /* 0x45 */ CAM_SET_BOSS_INI,
    /* 0x46 */ CAM_SET_BOSS_HAK,
    /* 0x47 */ CAM_SET_BOSS_KON,
    /* 0x48 */ CAM_SET_CONNECT0,
    /* 0x49 */ CAM_SET_MORAY,
    /* 0x4A */ CAM_SET_NORMAL2,
    /* 0x4B */ CAM_SET_BOMBBOWL,
    /* 0x4C */ CAM_SET_CIRCLEA,
    /* 0x4D */ CAM_SET_WHIRLPOOL,
    /* 0x4E */ CAM_SET_KOKKOGAME,
    /* 0x4F */ CAM_SET_GIANT,
    /* 0x50 */ CAM_SET_SCENE0,
    /* 0x51 */ CAM_SET_ROOM1,
    /* 0x52 */ CAM_SET_WATER2,
    /* 0x53 */ CAM_SET_SOKONASI,
    /* 0x54 */ CAM_SET_FORCEKEEP,
    /* 0x55 */ CAM_SET_PARALLEL1,
    /* 0x56 */ CAM_SET_START1,
    /* 0x57 */ CAM_SET_ROOM2,
    /* 0x58 */ CAM_SET_NORMAL4,
    /* 0x59 */ CAM_SET_SHELL,
    /* 0x5A */ CAM_SET_DUNGEON4,
    /* 0x5B */ CAM_SET_MAX
} CameraSettingType;

typedef enum {
    /* 0x00 */ CAM_MODE_NORMAL,
    /* 0x01 */ CAM_MODE_JUMP,
    /* 0x02 */ CAM_MODE_GORONDASH,
    /* 0x03 */ CAM_MODE_NUTSSHOT,
    /* 0x04 */ CAM_MODE_BOWARROWZ,
    /* 0x05 */ CAM_MODE_NUTSFLY,
    /* 0x06 */ CAM_MODE_FIRSTPERSON, // Original: CAM_MODE_SUBJECT
    /* 0x07 */ CAM_MODE_BOOMFOLLLOW, // Original: CAM_MODE_BOOKEEPON
    /* 0x08 */ CAM_MODE_ZORAFIN,
    /* 0x09 */ CAM_MODE_FOLLOWTARGET, // Original: CAM_MODE_KEEPON
    /* 0x0A */ CAM_MODE_TARGET, // Original: CAM_MODE_PARALLEL
    /* 0x0B */ CAM_MODE_TALK, 
    /* 0x0C */ CAM_MODE_SLINGSHOT, // Original: CAM_MODE_PACHINCO
    /* 0x0D */ CAM_MODE_BOWARROW,
    /* 0x0E */ CAM_MODE_BATTLE,
    /* 0x0F */ CAM_MODE_NUTSHIDE,
    /* 0x10 */ CAM_MODE_STILL,
    /* 0x11 */ CAM_MODE_CHARGE,
    /* 0x12 */ CAM_MODE_CLIMB,
    /* 0x13 */ CAM_MODE_CLIMBZ,
    /* 0x14 */ CAM_MODE_FOOKSHOT,
    /* 0x15 */ CAM_MODE_FREEFALL,
    /* 0x16 */ CAM_MODE_HANG,
    /* 0x17 */ CAM_MODE_HANGZ,
    /* 0x18 */ CAM_MODE_PUSHPULL,
    /* 0x19 */ CAM_MODE_NUTSFLYZ,
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

typedef struct {
    /* 0x0 */ s16 val;
    /* 0x2 */ s16 param;
} CameraModeValue; // size = 0x4

typedef struct {
    /* 0x0 */ s16 funcIdx;
    /* 0x2 */ s16 valueCnt;
    /* 0x4 */ CameraModeValue* values;
} CameraMode; // size = 0x8

typedef struct {
    /* 0x0 */ u32 validModes;
    /* 0x4 */ u32 unk_04;
    /* 0x8 */ CameraMode* cameraModes;
} CameraSetting; // size = 0xC

typedef struct {
    /* 0x00 */ f32 unk_00; // yPos
    /* 0x04 */ f32 unk_04; // xzSpeed
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A; // angle
    /* 0x0C */ s16 unk_0C; // flags (May be s32)
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ f32 unk_10; // set to float
} Normal1Anim;

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
    /* 0x22 */ s16 unk_22; // interfaceFlags
    /* 0x24 */ Normal1Anim anim;
} Normal1; // 10

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
} Normal3Anim;

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
    /* 0x20 */ Normal3Anim anim;
} Normal3; // 9

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
} Normal0Anim;

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
    /* 0x20 */ Normal0Anim anim;
} Normal0; // 9

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
} Parallel1Anim;

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
    /* 0x28 */ Parallel1Anim anim;
} Parallel1; // 12

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
} Jump2Anim;

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
    /* 0x22 */ s16 pad;
    /* 0x24 */ Jump2Anim anim;
} Jump2; // 9

typedef struct {
    /* 0x00 */ f32 unk_00; //
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08; //
    /* 0x0A */ s16 unk_0A; //
    /* 0x0C */ s32 unk_0C; // mode
    /* 0x10 */ s16 unk_10; //
    /* 0x12 */ s16 unk_12;
    /* 0x1C */ s16 unk_1C;
} Jump3Anim;

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
    /* 0x24 */ Jump3Anim anim;
} Jump3; // 10

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ struct Actor* unk_08; // targe3t
    /* 0x0C */ s32 unk_0C; // unused?
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} Battle1Anim;

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
    /* 0x32 */ s16 pad; // TODO: May not need
    /* 0x34 */ Battle1Anim anim;
} Battle1; // 13

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
} KeepOn1Anim; // size = 0x18

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
    /* 0x2E */ s16 unk_2E; // Pad?
    /* 0x30 */ KeepOn1Anim anim;
} KeepOn1; // 12

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ // KeepOn3Anim anim;
} KeepOn3; // 13

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ // KeepOn4Anim anim;
} KeepOn4; // 9

typedef struct {
    /* 0x00 */ PosRot eyePosRotTarget;
    /* 0x14 */ s16 fov;
    /* 0x18 */ struct ActorPlayer* player;
} Fixed1Anim; // size = 0x1C

typedef struct {
    /* 0x0000 */ f32 unk_00;
    /* 0x0004 */ f32 jfifId;
    /* 0x0008 */ f32 fov;
    /* 0x000C */ s16 interfaceFlags;
    /* 0x0010 */ Fixed1Anim anim;
} Fixed1; // size = 0x2C

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
} Fixed2Anim;

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A; //pad
    /* 0x1C */ Fixed2Anim anim;
} Fixed2; // 7

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ // Subj1Anim anim;
} Subj1; // 9

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
} Unique2Anim; // size = 0xC

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12; // pad
    /* 0x14 */ Unique2Anim anim;
} Unique2; //

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
} Unique0Anim; // size = 0xC

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ Unique0Anim anim;
} Unique0; // 3

typedef struct {
    /* 0x00 */ s16 interfaceFlags;
} Unique6; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ VecSph unk_0C;
    /* 0x14 */ VecSph unk_14;
    /* 0x1C */ s16 unk_1C;
} Demo1Anim; // size = 0xC

typedef struct {
    /* 0x00 */ s16 interfaceFlags;
    /* 0x04 */ Demo1Anim anim;
} Demo1; // size = 0x4

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ // Demo2Anim anim;
} Demo2; // size = 0xC

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} Demo3Anim; // size = 0xC

typedef struct {
    /* 0x00 */ s16 interfaceFlags;
    /* 0x04 */ Demo3Anim anim;
} Demo3; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ VecSph unk_18; // sp18-1C-20--24-26-28 // CutsceneCameraPoint?
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
} Demo4Anim;

typedef struct {
    /* 0x00 */ s16 interfaceFlags;
    /* 0x04 */ Demo4Anim anim;
} Demo4; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ VecSph unk_1C;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
} Demo5Anim;

typedef struct {
    /* 0x00 */ s16 interfaceFlags;
    /* 0x04 */ Demo5Anim anim;
} Demo5; // size = 0x4

typedef struct {
    /* 0x00 */ s16 interfaceFlags;
    /* 0x04 */ // Demo0Anim anim;
} Demo0; // size = 0x4

typedef struct {
    /* 0x00 */ s16 unk_00;
} Special5Anim; // size = 0x1C

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 pad;
    /* 0x1C */ Special5Anim anim;
} Special5; // 8

typedef struct {
    /* 0x00 */ struct Actor* doorActor;
    /* 0x04 */ s16 camDataIdx;
    /* 0x06 */ s16 timer1;
    /* 0x08 */ s16 timer2;
    /* 0x0A */ s16 timer3;
} DoorParams; // size = 0xC

typedef struct {
    // /* 0x00 */ s16 unk_00;
    // /* 0x00 */ s16 unk_02;
    // /* 0x04 */ f32 unk_04;
    // /* 0x04 */ s16 unk_06;
    // /* 0x08 */ s16 unk_08;
    // /* 0x0A */ s16 unk_0A;
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} Special8Anim; // size = 0x1C

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x00 */ f32 unk_08;
    /* 0x04 */ f32 unk_0C;
    /* 0x08 */ s16 unk_10;
    /* 0x0A */ s16 unk_12;
    /* 0x14 */ Special8Anim anim;
} Special8Params;

typedef struct {
    /* 0x00 */ DoorParams doorParams;
    /* 0x0C */ Special8Params params;
} Special8; //

typedef struct {
    /* 0x00 */ s16 unk_00;
} Special9Anim;

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 pad;
    /* 0x0C */ Special9Anim anim;
} Special9Params;

typedef struct {
    /* 0x00 */ DoorParams doorParams;
    /* 0x0C */ Special9Params params;
} Special9; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f norm;
    /* 0x18 */ CollisionPoly* poly;
    /* 0x1C */ VecSph sphNorm;
    /* 0x24 */ s32 bgId;
} CamColChk; // size = 0x28

typedef struct {
    Vec3f unk_00; // collisionClosePoint
    CamColChk unk_0C;
    CamColChk unk_34;
    VecSph unk_5C; // (Not VecSph) swingUpdateRate - yaw - pitch
    s16 unk_64;
    s16 unk_66; // startSwingTimer
} SwingAnimation; // size = 0x68

typedef struct {
    s32 unk_00;
    char unk_04[0x20];
    Vec3f unk_24;
} UnkStruct_D801ED920; // size = ??

typedef struct Camera {
    /* 0x000 */ char paramData[0x50];
    /* 0x050 */ Vec3f focalPoint;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f upDir;
    /* 0x074 */ Vec3f eyeNext;
    /* 0x080 */ Vec3f skyboxOffset;
    /* 0x08C */ struct GlobalContext* globalCtx;
    /* 0x090 */ struct ActorPlayer* player;
    /* 0x094 */ PosRot playerPosRot;
    /* 0x0A8 */ struct Actor* target;
    /* 0x0AC */ PosRot targetPosRot;
    /* 0x0C0 */ f32 rUpdateRateInv;
    /* 0x0C4 */ f32 pitchUpdateRateInv;
    /* 0x0C8 */ f32 yawUpdateRateInv;
    /* 0x0CC */ f32 xzOffsetUpdateRate; // May be swapped with yOffset immediately below
    /* 0x0D0 */ f32 yOffsetUpdateRate;
    /* 0x0D4 */ f32 fovUpdateRate;
    /* 0x0D8 */ f32 xzSpeed;
    /* 0x0DC */ f32 dist;
    /* 0x0E0 */ f32 speedRatio;
    /* 0x0E4 */ Vec3f posOffset;
    /* 0x0F0 */ Vec3f playerPosDelta;
    /* 0x0FC */ f32 fov;
    /* 0x100 */ f32 atLERPStepScale;
    /* 0x104 */ f32 playerGroundY;
    /* 0x108 */ Vec3f floorNorm;
    /* 0x114 */ f32 waterYPos;
    /* 0x118 */ s32 waterPrevCamIdx;
    /* 0x11C */ s32 waterPrevCamSetting;
    /* 0x120 */ s16 waterQuakeId;
    /* 0x122 */ s16 unk_122;
    /* 0x124 */ void* data0;
    /* 0x128 */ void* data1;
    /* 0x12C */ s16 data2;
    /* 0x12E */ s16 data3;
    /* 0x130 */ s16 uid;
    /* 0x132 */ char unk_132[2];
    /* 0x134 */ Vec3s inputDir;
    /* 0x13A */ Vec3s camDir;
    /* 0x140 */ s16 status;
    /* 0x142 */ s16 setting;
    /* 0x144 */ s16 mode;
    /* 0x146 */ s16 bgCheckId;
    /* 0x148 */ s16 camDataIdx;
    /* 0x14A */ s16 unk_14A;
    /* 0x14C */ s16 flags;
    /* 0x14E */ s16 childCamIdx;
    /* 0x150 */ s16 unk_150;
    /* 0x152 */ s16 unk_152;
    /* 0x154 */ s16 prevSetting;
    /* 0x156 */ s16 nextCamDataIdx;
    /* 0x158 */ s16 nextBGCheckId;
    /* 0x15A */ s16 roll;
    /* 0x15C */ s16 paramFlags;
    /* 0x15E */ s16 animState;
    /* 0x160 */ s16 unk_160;
    /* 0x162 */ s16 timer;
    /* 0x164 */ s16 thisIdx;
    /* 0x166 */ s16 prevCamDataIdx;
    /* 0x168 */ s16 unk_168;
    /* 0x16A */ UNK_TYPE1 pad16A[0xE];
} Camera; // size = 0x178

#endif
