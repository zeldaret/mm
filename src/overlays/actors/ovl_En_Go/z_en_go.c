/*
 * File: z_en_go.c
 * Overlay: ovl_En_Go
 * Description: Goron
 */

#include "z_en_go.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"
#include "objects/object_hakugin_demo/object_hakugin_demo.h"
#include "objects/object_taisou/object_taisou.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define ENGO_EYE_OPEN 0
#define ENGO_EYE_HALF 1
#define ENGO_EYE_CLOSED 2
#define ENGO_EYE_HALF2 3
#define ENGO_EYE_CLOSED2 4

#define ENGO_FLAG_NONE 0
#define ENGO_FLAG_BLINKING (1 << 5) // 0x0020
#define ENGO_FLAG_CURLED (1 << 9)   // 0x0200
#define ENGO_FLAG_CURLING (1 << 14) // 0x4000

typedef enum {
    ENGO_AWAKE = 0,
    ENGO_ASLEEP,
} EnGoSleepState;

#define THIS ((EnGo*)thisx)

void EnGo_Init(Actor* thisx, PlayState* play);
void EnGo_Destroy(Actor* thisx, PlayState* play);
void EnGo_Update(Actor* thisx, PlayState* play);

void func_ACT_80A14798(EnGo* this, PlayState* play);
void func_ACT_80A149B0(EnGo* this, PlayState* play);
void func_ACT_80A14B30(EnGo* this, PlayState* play);
void func_ACT_80A14E14(EnGo* this, PlayState* play);
void func_ACT_80A14E74(EnGo* this, PlayState* play);
void func_ACT_80A14EB0(EnGo* this, PlayState* play);
void func_ACT_80A14FC8(EnGo* this, PlayState* play);
void func_ACT_80A153FC(EnGo* this, PlayState* play);
void func_ACT_80A157C4(EnGo* this, PlayState* play);
void EnGo_Draw(Actor* thisx, PlayState* play);

// MsgScript
static s32 D_80A16100[] = {
    0x00150800, 0x40010022, 0x00150200, 0x180E0E10, 0x0C0F0E11, 0x0C0F0E12, 0x0C0F0E13, 0x0C0F0E14, 0x0C111502,
    0x100E0E15, 0x0C100015, 0x0400110E, 0x0E160C0F, 0x0E170C0F, 0x0E180C11, 0x15041610, 0x0E0E190C, 0x10001504,
    0x000D0100, 0x050E0E31, 0x0C100E0E, 0x2F0C1001, 0x00050E0E, 0x2D0C100E, 0x0E2B0C10,
};

// MsgScript sMsgScript[] = {
// /* 0x0000 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x08, 0x0045 - 0x0005),
// /* 0x0005 0x03 */  MSCRIPT_CMD01(0x002A - 0x0008),
// /* 0x0008 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x02, 0x0025 - 0x000D),
// /* 0x000D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E10), // This is the grave where a Goron hero rests.
// /* 0x0010 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0011 0x03 */  MSCRIPT_CMD15(0x0E11), // I came here to put up the great hero's memorial... But the return rout
// has been blocked by snow, and I can't get back to Goron Village.
// /* 0x0014 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0015 0x03 */  MSCRIPT_CMD15(0x0E12), // And even worse, my borther has been frozen solid from teh cold. The way
// things are looking, I'll be frozen too.
// /* 0x0018 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0019 0x03 */  MSCRIPT_CMD15(0x0E13), // hhhh...It's times like these that make me wish i had taken some of the
// hot spring water I found when I was digging the hero's grave.
// /* 0x001C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x001D 0x03 */  MSCRIPT_CMD15(0x0E14),
// /* 0x0020 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0021 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x15, 0x02), // But the hot spring is now covered by the gravestone. I
// can't move a gravestone that big by myself. But I guess this is what's meant by the Goron saying, "There's no use in
// crying over split rocks."...Brrrrrr
// /* 0x0024 0x01 */  MSCRIPT_DONE(),

// /* 0x0025 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E15), // H-h-hoo. If only I had water from the hot spring beneath the gravt
// hero's grave...then I could melt the ice off of my brother.
// /* 0x0028 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0029 0x01 */  MSCRIPT_DONE(),

// /* 0x002A 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x04, 0x0040 - 0x002F),
// /* 0x002F 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E16), //Y-you're...No! No, you're not the great darmani, are you?
// /* 0x0032 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0033 0x03 */  MSCRIPT_CMD15(0x0E17), // Then...just whose grave was I making?
// /* 0x0036 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0037 0x03 */  MSCRIPT_CMD15(0x0E18), // Did you come back to life because it was so warm beneath your grave?
// /* 0x003A 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x003B 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x15, 0x04),
// /* 0x003E 0x01 */  MSCRIPT_CMD22(),
// /* 0x003F 0x01 */  MSCRIPT_DONE(),

// /* 0x0040 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E19), // There used to be a hot spring bubbling beneath the great Darmani's
// grave. If I had some of that hot spring water, I might be able to thaw out my frozen brother.
// /* 0x0043 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0044 0x01 */  MSCRIPT_DONE(),

// /* 0x0045 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x04, 0x0057 - 0x004A),
// /* 0x004A 0x03 */  MSCRIPT_CMD01(0x0052 - 0x004D),
// /* 0x004D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E31),
// /* 0x0050 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0051 0x01 */  MSCRIPT_DONE(),

// /* 0x0052 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E2F),
// /* 0x0055 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0056 0x01 */  MSCRIPT_DONE(),

// /* 0x0057 0x03 */  MSCRIPT_CMD01(0x005F - 0x005A),
// /* 0x005A 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E2D),
// /* 0x005D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x005E 0x01 */  MSCRIPT_DONE(),

// /* 0x005F 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E2B),
// /* 0x0062 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0063 0x01 */  MSCRIPT_DONE(),
// };

static s32 D_80A16164[] = {
    0x00150800, 0x7E01004D, 0x00150400, 0x180E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C12, 0x16111508,
    0x100E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C17, 0x0F0E260C, 0x180F0E27, 0x0C170F0E, 0x280C180F,
    0x0E290C17, 0x0F0E2A0C, 0x16111508, 0x100E0E1A, 0x0C170F0E, 0x1B0C180F, 0x0E1C0C0F, 0x0E1D0C0F, 0x0E1E0C17,
    0x0F0E1F0C, 0x180F0E20, 0x0C170F0E, 0x210C0F0E, 0x220C1611, 0x15081000, 0x1504000D, 0x0100050E, 0x0E320C10,
    0x0E0E300C, 0x10010005, 0x0E0E2E0C, 0x100E0E2C, 0x0C100000,
};

// MsgScript sMsgScript[] = {
// /* 0x0000 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x08, 0x0083 - 0x0005),
// /* 0x0005 0x03 */  MSCRIPT_CMD01(0x0055 - 0x0008),
// /* 0x0008 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x04, 0x0025 - 0x000D),
// /* 0x000D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E1A),
// /* 0x0010 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0011 0x01 */  MSCRIPT_CMD23(),
// /* 0x0012 0x03 */  MSCRIPT_CMD15(0x0E23),
// /* 0x0015 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0016 0x01 */  MSCRIPT_CMD24(),
// /* 0x0017 0x03 */  MSCRIPT_CMD15(0x0E24),
// /* 0x001A 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x001B 0x03 */  MSCRIPT_CMD15(0x0E25),
// /* 0x001E 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x001F 0x01 */  MSCRIPT_CMD18(),
// /* 0x0020 0x01 */  MSCRIPT_CMD22(),
// /* 0x0021 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x15, 0x08),
// /* 0x0024 0x01 */  MSCRIPT_DONE(),

// /* 0x0025 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E1A),
// /* 0x0028 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0029 0x01 */  MSCRIPT_CMD23(),
// /* 0x002A 0x03 */  MSCRIPT_CMD15(0x0E23),
// /* 0x002D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x002E 0x01 */  MSCRIPT_CMD24(),
// /* 0x002F 0x03 */  MSCRIPT_CMD15(0x0E24),
// /* 0x0032 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0033 0x03 */  MSCRIPT_CMD15(0x0E25),
// /* 0x0036 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0037 0x01 */  MSCRIPT_CMD23(),
// /* 0x0038 0x03 */  MSCRIPT_CMD15(0x0E26),
// /* 0x003B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x003C 0x01 */  MSCRIPT_CMD24(),
// /* 0x003D 0x03 */  MSCRIPT_CMD15(0x0E27),
// /* 0x0040 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0041 0x01 */  MSCRIPT_CMD23(),
// /* 0x0042 0x03 */  MSCRIPT_CMD15(0x0E28),
// /* 0x0045 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0046 0x01 */  MSCRIPT_CMD24(),
// /* 0x0047 0x03 */  MSCRIPT_CMD15(0x0E29),
// /* 0x004A 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x004B 0x01 */  MSCRIPT_CMD23(),
// /* 0x004C 0x03 */  MSCRIPT_CMD15(0x0E2A),
// /* 0x004F 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0050 0x01 */  MSCRIPT_CMD22(),
// /* 0x0051 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x15, 0x08),
// /* 0x0054 0x01 */  MSCRIPT_DONE(),

// /* 0x0055 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E1A),
// /* 0x0058 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0059 0x01 */  MSCRIPT_CMD23(),
// /* 0x005A 0x03 */  MSCRIPT_CMD15(0x0E1B),
// /* 0x005D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x005E 0x01 */  MSCRIPT_CMD24(),
// /* 0x005F 0x03 */  MSCRIPT_CMD15(0x0E1C),
// /* 0x0062 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0063 0x03 */  MSCRIPT_CMD15(0x0E1D),
// /* 0x0066 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0067 0x03 */  MSCRIPT_CMD15(0x0E1E),
// /* 0x006A 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x006B 0x01 */  MSCRIPT_CMD23(),
// /* 0x006C 0x03 */  MSCRIPT_CMD15(0x0E1F),
// /* 0x006F 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0070 0x01 */  MSCRIPT_CMD24(),
// /* 0x0071 0x03 */  MSCRIPT_CMD15(0x0E20),
// /* 0x0074 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0075 0x01 */  MSCRIPT_CMD23(),
// /* 0x0076 0x03 */  MSCRIPT_CMD15(0x0E21),
// /* 0x0079 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x007A 0x03 */  MSCRIPT_CMD15(0x0E22),
// /* 0x007D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x007E 0x01 */  MSCRIPT_CMD22(),
// /* 0x007F 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x15, 0x08),
// /* 0x0082 0x01 */  MSCRIPT_DONE(),

// /* 0x0083 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x15, 0x04, 0x0095 - 0x0088),
// /* 0x0088 0x03 */  MSCRIPT_CMD01(0x0090 - 0x008B),
// /* 0x008B 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E32),
// /* 0x008E 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x008F 0x01 */  MSCRIPT_DONE(),

// /* 0x0090 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E30),
// /* 0x0093 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0094 0x01 */  MSCRIPT_DONE(),

// /* 0x0095 0x03 */  MSCRIPT_CMD01(0x009D - 0x0098),
// /* 0x0098 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E2E),
// /* 0x009B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x009C 0x01 */  MSCRIPT_DONE(),

// /* 0x009D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E2C),
// /* 0x00A0 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x00A1 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A16208[2] = { 0xE0E520C, 0x10000000 };

// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E52),
// /* 0x0003 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0004 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A16210[17] = {
    0x160400,  0x38010010, 0xE0E430C, 0xF0E440C, 0xF0E450C,  0x11188010, 0x160800,   0x1B0E0E46, 0xC0F0E47,
    0xC0F0E48, 0xC0F0E49,  0xC0F0E4A, 0xC111608, 0x11188010, 0xE0E4B0C,  0x100E0E42, 0xC100000,
};

// MsgScript sMsgScript[] = {
// /* 0x0000 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x16, 0x04, 0x003D - 0x0005),
// /* 0x0005 0x03 */  MSCRIPT_CMD01(0x0018 - 0x0008),
// /* 0x0008 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E43),
// /* 0x000B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000C 0x03 */  MSCRIPT_CMD15(0x0E44),
// /* 0x000F 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0010 0x03 */  MSCRIPT_CMD15(0x0E45),
// /* 0x0013 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0014 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x18, 0x80),
// /* 0x0017 0x01 */  MSCRIPT_DONE(),

// /* 0x0018 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x16, 0x08, 0x0038 - 0x001D),
// /* 0x001D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E46),
// /* 0x0020 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0021 0x03 */  MSCRIPT_CMD15(0x0E47),
// /* 0x0024 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0025 0x03 */  MSCRIPT_CMD15(0x0E48),
// /* 0x0028 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0029 0x03 */  MSCRIPT_CMD15(0x0E49),
// /* 0x002C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x002D 0x03 */  MSCRIPT_CMD15(0x0E4A),
// /* 0x0030 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0031 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x16, 0x08),
// /* 0x0034 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x18, 0x80),
// /* 0x0037 0x01 */  MSCRIPT_DONE(),

// /* 0x0038 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E4B),
// /* 0x003B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x003C 0x01 */  MSCRIPT_DONE(),

// /* 0x003D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E42),
// /* 0x0040 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0041 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A16254[11] = {
    0x160400,   0x22010009, 0xE0E4D0C, 0xF0E4E0C,  0x10001701, 0xC0E0E,
    0x4F0C0F0E, 0x500C1117, 0x1100E0E, 0x510C100E, 0xE4C0C10,
};
// MsgScript sMsgScript[] = {
// /* 0x0000 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x16, 0x04, 0x0027 - 0x0005),
// /* 0x0005 0x03 */  MSCRIPT_CMD01(0x0011 - 0x0008),
// /* 0x0008 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E4D),
// /* 0x000B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000C 0x03 */  MSCRIPT_CMD15(0x0E4E),
// /* 0x000F 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0010 0x01 */  MSCRIPT_DONE(),

// /* 0x0011 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x17, 0x01, 0x0022 - 0x0016),
// /* 0x0016 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E4F),
// /* 0x0019 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x001A 0x03 */  MSCRIPT_CMD15(0x0E50),
// /* 0x001D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x001E 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x17, 0x01),
// /* 0x0021 0x01 */  MSCRIPT_DONE(),

// /* 0x0022 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E51),
// /* 0x0025 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0026 0x01 */  MSCRIPT_DONE(),

// /* 0x0027 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E4C),
// /* 0x002A 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x002B 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A16280[52] = {
    0x1001200,  0x12200008, 0xE0C8E0C,  0x11122010, 0xE0C8F0C,  0x10001240, 0x1D0E0C,   0x800C1112, 0x40001280,
    0x742500,   0xC006F00,  0x13010045, 0xF0C810C,  0x19001300, 0x1280005E, 0x25000C00, 0x59001301, 0x2F0E0C,
    0x810C0F0C, 0x820C0500, 0x1A00,     0x1A300E0C, 0x830C1209, 0x700,      0xE0C84,    0x160C1113, 0x1100E0C,
    0x840C1031, 0xE0C850C,  0x1029FFF2, 0x130200,   0xF0E0C88,  0xC0F0C89,  0xC05000A,  0xFFE3FFE3, 0xE0C860C,
    0x11128019, 0x213019,   0xFFC02900, 0x2C0E0C8C, 0xC050000,  0x50000,    0x8006400,  0x6320E0C,  0x8D0C1030,
    0x14FF9C12, 0x6003400,  0x130034,   0x700000E,  0xC870C16,  0x100E0C8B, 0xC100000,
};
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0015 - 0x0003),
// /* 0x0003 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x12, 0x20, 0x0010 - 0x0008),
// /* 0x0008 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C8E),
// /* 0x000B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000C 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x12, 0x20),
// /* 0x000F 0x01 */  MSCRIPT_DONE(),

// /* 0x0010 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C8F),
// /* 0x0013 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0014 0x01 */  MSCRIPT_DONE(),

// /* 0x0015 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x12, 0x40, 0x0037 - 0x001A),
// /* 0x001A 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C80),
// /* 0x001D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x001E 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x12, 0x40),
// /* 0x0021 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x12, 0x80, 0x009A - 0x0026),
// /* 0x0026 0x05 */  MSCRIPT_BRANCH_ON_ITEM(ITEM_POWDER_KEG, 0x009A - 0x002B),
// /* 0x002B 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x13, 0x01, 0x0075 - 0x0030),
// /* 0x0030 0x03 */  MSCRIPT_CMD15(0x0C81),
// /* 0x0033 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0034 0x03 */  MSCRIPT_CMD25(0x004A - 0x0037),
// /* 0x0037 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x12, 0x80, 0x009A - 0x003C),
// /* 0x003C 0x05 */  MSCRIPT_BRANCH_ON_ITEM(ITEM_POWDER_KEG, 0x009A - 0x0041),
// /* 0x0041 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x13, 0x01, 0x0075 - 0x0046),
// /* 0x0046 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C81),
// /* 0x0049 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x004A 0x03 */  MSCRIPT_CMD15(0x0C82),
// /* 0x004D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x004E 0x07 */  MSCRIPT_CMD05(0x0, 0x006F - 0x0055, 0x006F - 0x0055),
// /* 0x0055 0x01 */  MSCRIPT_CMD48(),
// /* 0x0056 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C83),
// /* 0x0059 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x005A 0x01 */  MSCRIPT_CMD18(),
// /* 0x005B 0x03 */  MSCRIPT_CMD09(0x0),
// /* 0x005E 0x03 */  MSCRIPT_CMD07(0x0),
// /* 0x0061 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C84),
// /* 0x0064 0x01 */  MSCRIPT_CMD22(),
// /* 0x0065 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0066 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x13, 0x01),
// /* 0x0069 0x01 */  MSCRIPT_DONE(),

// /* 0x006A 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C84),
// /* 0x006D 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x006E 0x01 */  MSCRIPT_DONE(),

// /* 0x006F 0x01 */  MSCRIPT_CMD49(),
// /* 0x0070 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C85),
// /* 0x0073 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0074 0x01 */  MSCRIPT_DONE(),

// /* 0x0075 0x03 */  MSCRIPT_CMD41(0x006A - 0x0078),

// /* 0x0078 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x13, 0x02, 0x008C - 0x007D),
// /* 0x007D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C88),
// /* 0x0080 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0081 0x03 */  MSCRIPT_CMD15(0x0C89),
// /* 0x0084 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0085 0x07 */  MSCRIPT_CMD05(0x0096 - 0x008C, 0x006F - 0x008C, 0x006F - 0x008C),

// /* 0x008C 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C86),
// /* 0x008F 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0090 0x03 */  MSCRIPT_WEEK_EVENT_REG_SET(0x12, 0x80),
// /* 0x0093 0x03 */  MSCRIPT_CMD25(0x00B7 - 0x0096),
// /* 0x0096 0x01 */  MSCRIPT_CMD48(),
// /* 0x0097 0x03 */  MSCRIPT_CMD25(0x005A - 0x009A),

// /* 0x009A 0x03 */  MSCRIPT_CMD41(0x00C9 - 0x009D),
// /* 0x009D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C8C),
// /* 0x00A0 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x00A1 0x07 */  MSCRIPT_CMD05(0x0, 0x00AD - 0x00A8, 0x0),
// /* 0x00A8 0x05 */  MSCRIPT_CMD08(0x0064, 0x00B3 - 0x00AD),
// /* 0x00AD 0x01 */  MSCRIPT_CMD50(),
// /* 0x00AE 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C8D),
// /* 0x00B1 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x00B2 0x01 */  MSCRIPT_DONE(),

// /* 0x00B3 0x01 */  MSCRIPT_CMD48(),
// /* 0x00B4 0x03 */  MSCRIPT_CMD20(0xFF9C),
// /* 0x00B7 0x01 */  MSCRIPT_CMD18(),
// /* 0x00B8 0x05 */  MSCRIPT_CMD06(0x0034, 0x0),
// /* 0x00BD 0x03 */  MSCRIPT_COLLECT_SET(0x0034),
// /* 0x00C0 0x03 */  MSCRIPT_CMD07(0x0),
// /* 0x00C3 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C87),
// /* 0x00C6 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x00C7 0x01 */  MSCRIPT_CMD22(),
// /* 0x00C8 0x01 */  MSCRIPT_DONE(),

// /* 0x00C9 0x03 */  MSCRIPT_BEGIN_TEXT(0x0C8B),
// /* 0x00CC 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x00CD 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A16350[27] = {
    0x584000,  0x2903000E, 0x2001301, 0x180058,   0x80005119, 0x1E0059,   0x1004919, 0x160059,  0x2004119,
    0xE0059,   0x4003919,  0x2F0E0D,  0x4D0C1210, 0xE0D480C,  0xF0D490C,  0xF0D4A0C, 0x5000000, 0xF000F30,
    0xE0D4B0C, 0x15090000, 0xE0D4D0C, 0x1210310E, 0xD4C0C12,  0x100E0D4E, 0xC19FFD8, 0xE0D4F0C, 0x19FFD500,
};

// MsgScript sMsgScript[] = {
// /* 0x0000 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x58, 0x40, 0x002E - 0x0005),
// /* 0x0005 0x03 */  MSCRIPT_CMD03(0x0016 - 0x0008),
// /* 0x0008 0x03 */  MSCRIPT_CMD02(0x001E - 0x000B),
// /* 0x000B 0x03 */  MSCRIPT_CMD01(0x0026 - 0x000E),
// /* 0x000E 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x58, 0x80, 0x0064 - 0x0013),
// /* 0x0013 0x03 */  MSCRIPT_CMD25(0x0034 - 0x0016),
// /* 0x0016 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x59, 0x01, 0x0064 - 0x001B),
// /* 0x001B 0x03 */  MSCRIPT_CMD25(0x0034 - 0x001E),
// /* 0x001E 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x59, 0x02, 0x0064 - 0x0023),
// /* 0x0023 0x03 */  MSCRIPT_CMD25(0x0034 - 0x0026),
// /* 0x0026 0x05 */  MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(0x59, 0x04, 0x0064 - 0x002B),
// /* 0x002B 0x03 */  MSCRIPT_CMD25(0x005D - 0x002E),
// /* 0x002E 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D4D),
// /* 0x0031 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0032 0x01 */  MSCRIPT_CMD18(),
// /* 0x0033 0x01 */  MSCRIPT_DONE(),

// /* 0x0034 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D48),
// /* 0x0037 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0038 0x03 */  MSCRIPT_CMD15(0x0D49),
// /* 0x003B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x003C 0x03 */  MSCRIPT_CMD15(0x0D4A),
// /* 0x003F 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0040 0x07 */  MSCRIPT_CMD05(0x0, 0x0056 - 0x0047, 0x0056 - 0x0047),
// /* 0x0047 0x01 */  MSCRIPT_CMD48(),
// /* 0x0048 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D4B),
// /* 0x004B 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x004C 0x01 */  MSCRIPT_CMD21(),
// /* 0x004D 0x03 */  MSCRIPT_CMD09(0x0),
// /* 0x0050 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D4D),
// /* 0x0053 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0054 0x01 */  MSCRIPT_CMD18(),
// /* 0x0055 0x01 */  MSCRIPT_DONE(),

// /* 0x0056 0x01 */  MSCRIPT_CMD49(),
// /* 0x0057 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D4C),
// /* 0x005A 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x005B 0x01 */  MSCRIPT_CMD18(),
// /* 0x005C 0x01 */  MSCRIPT_DONE(),

// /* 0x005D 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D4E),
// /* 0x0060 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0061 0x03 */  MSCRIPT_CMD25(0x003C - 0x0064),

// /* 0x0064 0x03 */  MSCRIPT_BEGIN_TEXT(0x0D4F),
// /* 0x0067 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0068 0x03 */  MSCRIPT_CMD25(0x0040 - 0x006B),
// };

// MsgScript
static s32 D_80A163BC[4] = { 0x100060E, 0xDFE0C12, 0x100E0DFF, 0xC121000 };
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0DFE),
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0DFF),
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A163CC[4] = { 0x100060E, 0xE000C12, 0x100E0E01, 0xC121000 };
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E00),
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E01),
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A163DC[4] = { 0x100060E, 0xE020C12, 0x100E0E03, 0xC121000 };
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E02),
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E03),
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A163EC[4] = { 0x100060E, 0xE040C12, 0x100E0E05, 0xC121000 };
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E04),
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E05),
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A163FC[4] = { 0x100060E, 0xE060C12, 0x100E0E07, 0xC121000 };
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E06),
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E07),
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A1640C[2] = { 0xE023A0C, 0x12100000 };
// MsgScript sMsgScript[] = {
// /* 0x0000 0x03 */  MSCRIPT_BEGIN_TEXT(0x023A),
// /* 0x0003 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0004 0x01 */  MSCRIPT_CMD18(),
// /* 0x0005 0x01 */  MSCRIPT_DONE(),
// };

const ActorInit En_Go_InitVars = {
    ACTOR_EN_GO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGo),
    (ActorFunc)EnGo_Init,
    (ActorFunc)EnGo_Destroy,
    (ActorFunc)EnGo_Update,
    (ActorFunc)NULL,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 0 }, 100 },
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0xF7CFFFFF, 0x02, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, 0, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 0, 0, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static AnimationInfoS sAnimationInfo[] = {
    { &gGoronLyingDownIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gGoronLyingDownIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gGoronUnrollAnim, 2.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gGoronUnrollAnim, 2.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gGoronUnrollAnim, -2.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gGoronShiverAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gGoronShiverAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gGoronDropKegAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gGoronCoverEarsAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gGoronShiveringSurprisedAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },

    { &object_taisou_Anim_004DD4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_0016C8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_00283C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_007764, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005EE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_002C48, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_0031D8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_taisou_Anim_005790, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },

    { &object_hakugin_demo_Anim_001420, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_hakugin_demo_Anim_001A4C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_hakugin_demo_Anim_002704, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_hakugin_demo_Anim_003378, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

EnGoStruct* func_80A10FD0(EnGoStruct* ptr, Vec3f position, Vec3f acceleration, Vec3f velocity, f32 scale,
                          f32 deltaScale, s32 arg6) {
    s32 i;

    for (i = 16; i < 32; i++, ptr++) {
        if (ptr->unk_00 != 0)
            continue;

        ptr->unk_00 = 7;
        ptr->alphaDenom = (Rand_ZeroOne() * (2.0f * (arg6 / 3.0f))) + (arg6 / 3.0f);
        ptr->alphaNumer = ptr->alphaDenom;
        ptr->position = position;
        ptr->acceleration = acceleration;
        ptr->velocity = velocity;
        ptr->scaleXY = scale;
        ptr->scaleXYDelta = deltaScale;
        break;
    }
    return ptr;
}

// Draw Steam (7)
void func_80A11144(EnGoStruct* ptr, PlayState* play2) {
    PlayState* play = play2;
    s32 i;
    s32 flag = false;
    f32 temp;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < 32; i++, ptr++) {
        if (ptr->unk_00 != 7)
            continue;

        gDPPipeSync(POLY_XLU_DISP++);
        if (!flag) {
            gSPDisplayList(POLY_XLU_DISP++, gGoronSteamMaterialDL);
            flag = true;
        }

        Matrix_Push();

        temp = ((f32)ptr->alphaNumer / ptr->alphaDenom);
        temp *= 255;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, (u8)temp);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, (ptr->alphaNumer + (i * 3)) * 3,
                                    (ptr->alphaNumer + (i * 3)) * 15, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));

        Matrix_Translate(ptr->position.x, ptr->position.y, ptr->position.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(ptr->scaleXY, ptr->scaleXY, 1.0f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGoronSteamModelDL);

        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

/*
Called for each element in the first half of the array,
*/
void func_80A1143C(EnGoStruct* ptr, Vec3f pos, Vec3f accel, Vec3f vel, f32 scale, f32 deltaScale, s32 arg6, s32 arg7) {
    s32 i;

    for (i = 16; i < 32; i++, ptr++) {
        if (ptr->unk_00 != 0)
            continue;

        ptr->unk_00 = arg7 + 4;
        ptr->alphaDenom = (Rand_ZeroOne() * (2.0f * (arg6 / 3.0f))) + (arg6 / 3.0f);
        ptr->alphaNumer = ptr->alphaDenom;
        ptr->position = pos;
        ptr->acceleration = accel;
        ptr->velocity = vel;
        ptr->scaleXY = scale;
        ptr->scaleXYDelta = deltaScale;
        break;
    }
}

// Draw Dust (4, 5, 6)
void func_80A115B4(EnGoStruct* ptr, PlayState* play2) {
    static TexturePtr sEnGoDustTexturePtrs[] = {
        gDust8Tex, gDust7Tex, gDust6Tex, gDust5Tex, gDust4Tex, gDust3Tex, gDust2Tex, gDust1Tex,
    };
    static Color_RGBA8 sEnGoDustColorPrim[] = {
        { 255, 255, 255, 0 }, // White
        { 170, 130, 90, 0 },  // Light Brown
        { 0, 0, 0, 0 },       // Black
    };
    static Color_RGBA8 sEnGoDustColorEnv[] = {
        { 255, 255, 255, 0 }, // White
        { 100, 60, 20, 0 },   // Dark Brown
        { 0, 0, 0, 0 },       // Black
    };
    PlayState* play = play2;
    s32 i;
    u8 flag = false;
    f32 temp;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < 32; i++, ptr++) {
        if ((ptr->unk_00 < 4) || (ptr->unk_00 >= 7))
            continue;

        if (!flag) {
            POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);
            gSPDisplayList(POLY_XLU_DISP++, gGoronDustMaterialDL);
            flag = true;
        }

        Matrix_Push();

        temp = (f32)ptr->alphaNumer / ptr->alphaDenom;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, sEnGoDustColorPrim[(s32)ptr->unk_00 - 4].r,
                        sEnGoDustColorPrim[(s32)ptr->unk_00 - 4].g, sEnGoDustColorPrim[(s32)ptr->unk_00 - 4].b,
                        (u8)(temp * 255));
        gDPSetEnvColor(POLY_XLU_DISP++, sEnGoDustColorEnv[(s32)ptr->unk_00 - 4].r,
                       sEnGoDustColorEnv[(s32)ptr->unk_00 - 4].g, sEnGoDustColorEnv[(s32)ptr->unk_00 - 4].b, 0);

        Matrix_Translate(ptr->position.x, ptr->position.y, ptr->position.z, MTXMODE_NEW);
        Matrix_Scale(ptr->scaleXY, ptr->scaleXY, 1.0f, MTXMODE_APPLY);
        Matrix_ReplaceRotation(&play->billboardMtxF);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sEnGoDustTexturePtrs[(s32)(temp * 7.0f)]));
        gSPDisplayList(POLY_XLU_DISP++, gGoronDustModelDL);

        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

/* Called after Snowball broken sound effect, before goron cold */
void func_80A118F8(EnGoStruct* ptr, Vec3f worldPos) {
    static u8 D_80A1667C[] = {
        3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3, 1, 1, 2,
    };

    EnGoStruct* pEnd = &ptr[16];
    s32 i;
    Vec3f randRelativeToWorldPos;
    Vec3f randYOneToFour;
    f32 temp_fs0;

    for (i = 0; i < 16; i++, ptr++) {
        if (ptr->unk_00 != 0)
            continue;

        ptr->position = worldPos;
        ptr->position.y += 56.0f;

        // Generate a +-15 degree rotational velocity
        ptr->rotVelocity.x = (Rand_ZeroOne() - 0.5f) * (f32)0x1554; /* 30 degrees */
        ptr->rotVelocity.y = (Rand_ZeroOne() - 0.5f) * (f32)0x1554; /* 30 degrees */
        ptr->rotVelocity.z = (Rand_ZeroOne() - 0.5f) * (f32)0x1554; /* 30 degrees */

        // Generate a radially outward velocity for each of the 16 pieces
        temp_fs0 = (Rand_ZeroOne() * 4.0f) + 6.0f;
        ptr->velocity.x = Math_SinS(i * (0x10000 / 16)) * temp_fs0;
        ptr->velocity.z = Math_CosS(i * (0x10000 / 16)) * temp_fs0;
        ptr->velocity.y = (Rand_ZeroOne() * 3.0f) + 6.0f;

        // No acceleration on the X,Z axis, Negative acceleration on the Y axis
        ptr->acceleration = gZeroVec3f;
        ptr->acceleration.y = -0.8f;

        // Full visibility (1/1)
        ptr->alphaDenom = ptr->alphaNumer = 1;

        // Assign a value of 1, 2, or 3
        ptr->unk_00 = D_80A1667C[i];

        // Initialize the Paired element
        randRelativeToWorldPos.x = ((Rand_ZeroOne() - 0.5f) * 80.0f) + ptr->position.x;
        randRelativeToWorldPos.y = ((Rand_ZeroOne() - 0.5f) * 40.0f) + ptr->position.y;
        randRelativeToWorldPos.z = ((Rand_ZeroOne() - 0.5f) * 80.0f) + ptr->position.z;

        randYOneToFour = gZeroVec3f;
        randYOneToFour.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

        // Initialize the paired element.
        func_80A1143C(pEnd, randRelativeToWorldPos, gZeroVec3f, randYOneToFour, 0.6f, 0.2f, 16, 0);
    }
}

void func_80A11BF8(EnGoStruct* ptr, f32 arg1) {
    f32 test;
    f32 test2;
    f32 x;
    f32 z;

    ptr->position.x += ptr->velocity.x;
    ptr->position.y += ptr->velocity.y;
    ptr->position.z += ptr->velocity.z;

    ptr->velocity.y += ptr->acceleration.y;
    ptr->scaleXY += ptr->scaleXYDelta;

    if (ptr->position.y < arg1) {
        ptr->position.y = arg1;

        ptr->unk_00 = 4;
        ptr->alphaDenom = (Rand_ZeroOne() * 8.0f) + 4.0f;
        ptr->alphaNumer = ptr->alphaDenom;

        ptr->velocity = gZeroVec3f;
        ptr->velocity.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

        ptr->scaleXY = 0.4f;
        ptr->scaleXYDelta = 0.1f;
        return;
    }

    if (ptr->velocity.x != 0.0f) {
        x = ptr->velocity.x / fabsf(ptr->velocity.x);
        x *= ((sREG(13) + 140) * 0.01f);
        Math_StepToF(&ptr->velocity.x, x, (sREG(14) + 40) * 0.01f);
    }

    if (ptr->velocity.z != 0.0f) {
        z = ptr->velocity.z / fabsf(ptr->velocity.z);
        z *= ((sREG(13) + 140) * 0.01f);
        Math_StepToF(&ptr->velocity.z, z, (sREG(14) + 40) * 0.01f);
    }

    ptr->rotAngle.x += ptr->rotVelocity.x;
    ptr->rotAngle.y += ptr->rotVelocity.y;
    ptr->rotAngle.z += ptr->rotVelocity.z;
}

// Draw snowball (1, 2, or 3)
void func_80A11EC0(EnGoStruct* ptr, PlayState* play, Gfx* arg2, Gfx* arg3, u8 arg4) {
    s32 i;
    u8 flag = false;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    for (i = 0; i < 16; i++, ptr++) {
        if (ptr->unk_00 != arg4)
            continue;

        if (!flag) {
            gSPDisplayList(POLY_OPA_DISP++, arg2);
            flag = true;
        }

        Matrix_Push();
        Matrix_Translate(ptr->position.x, ptr->position.y, ptr->position.z, MTXMODE_NEW);
        Matrix_Scale(0.08f, 0.08f, 0.08f, MTXMODE_APPLY);
        Matrix_RotateZS(ptr->rotAngle.z, MTXMODE_APPLY);
        Matrix_RotateXS(ptr->rotAngle.x, MTXMODE_APPLY);
        Matrix_RotateYS(ptr->rotAngle.y, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, arg3);

        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A1203C(EnGo* this) {
    EnGoStruct* ptr = this->unk_3F8;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++, ptr++) {
        if (ptr->unk_00 == 0)
            continue;

        if (ptr->alphaNumer == 0) {
            ptr->unk_00 = 0;
        } else if ((ptr->unk_00 > 0) && (ptr->unk_00 < 4)) {
            func_80A11BF8(ptr, this->actor.world.pos.y);
        } else {
            ptr->position.x += ptr->velocity.x;
            ptr->position.y += ptr->velocity.y;
            ptr->position.z += ptr->velocity.z;

            ptr->velocity.x += ptr->acceleration.x;
            ptr->velocity.y += ptr->acceleration.y;
            ptr->velocity.z += ptr->acceleration.z;

            ptr->scaleXY += ptr->scaleXYDelta;
            ptr->alphaNumer--;
        }
    }
}

// Draw Effects (1,2,3 = Snowball, 4,5,6 = Dust, 7 = Steam)
void func_80A1213C(EnGo* this, PlayState* play) {
    func_80A11EC0(this->unk_3F8, play, gGoronLargeSnowballFragmentMaterialDL, gGoronLargeSnowballFragmentModelDL, 1);
    func_80A11EC0(this->unk_3F8, play, gGoronMediumSnowballFragmentMaterialDL, gGoronMediumSnowballFragmentModelDL, 2);
    func_80A11EC0(this->unk_3F8, play, gGoronSmallSnowballFragmentMaterialDL, gGoronSmallSnowballFragmentModelDL, 3);
    func_80A11144(this->unk_3F8, play);
    func_80A115B4(this->unk_3F8, play);
}

s32 func_80A121F4(PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((player->transformation == PLAYER_FORM_GORON) && (player->stateFlags3 & 0x2000000)) {
        return false;
    }
    return true;
}

s32 EnGo_IsEnteringSleep(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 ret = false;

    if (((player->transformation == PLAYER_FORM_GORON) && (play->msgCtx.ocarinaMode == 3) &&
         (play->msgCtx.lastPlayedSong == OCARINA_SONG_GORON_LULLABY) && (this->sleepState == ENGO_AWAKE) &&
         (this->actor.xzDistToPlayer < 400.0f)) ||
        (!(gSaveContext.save.weekEventReg[22] & 4) && (play->sceneNum == SCENE_16GORON_HOUSE) &&
         (gSaveContext.sceneSetupIndex == 0) && (this->sleepState == ENGO_AWAKE) &&
         (play->csCtx.currentCsIndex == 1))) {
        ret = true;
    }
    return ret;
}

s32 func_80A122EC(EnGo* this) {
    static Vec3f D_80A1668C = { 0.0f, 100.0f, 160.0f };
    s32 pad;
    f32 sp20 = 58.0f;

    if (ENGO_GET_F(&this->actor) == ENGO_F_8) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80A1668C,
                                      &this->actor.focus.pos);
    } else {
        if ((this->flags & ENGO_FLAG_CURLED) || (this->flags & 0x100)) {
            sp20 = this->actor.shape.yOffset;
        }
        Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
        this->actor.focus.pos.y += sp20;
    }

    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
    return false;
}

void func_80A123A0(EnGo* this, PlayState* play) {
    Vec3f sp2C;

    Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = sp2C.x;
    this->colliderSphere.dim.worldSphere.center.y = sp2C.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = sp2C.z;

    this->colliderSphere.dim.modelSphere.radius = 48;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    if (func_80A121F4(play)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->colliderSphere.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderSphere.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void func_80A124A0(EnGo* this, PlayState* play) {
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void func_80A124FC(EnGo* this, PlayState* play) {
    Vec3f sp1C;

    Math_Vec3f_Copy(&sp1C, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = sp1C.x;
    this->colliderSphere.dim.worldSphere.center.y = sp1C.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = sp1C.z;

    this->colliderSphere.dim.modelSphere.radius = 20;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void func_80A125BC(EnGo* this, PlayState* play) {
    s32 pad;

    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);

    this->colliderCylinder.dim.radius = 46;
    this->colliderCylinder.dim.height = 78;

    if (this->unk_3C6 == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->colliderCylinder.base);
    }
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderCylinder.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
}

void func_80A12660(EnGo* this, PlayState* play) {
    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);
    this->colliderCylinder.dim.radius = 24;
    this->colliderCylinder.dim.height = 62;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
}

void func_80A126BC(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags2 & 0x4000)) {
        if (this->unk_3C6 != 0) {
            this->unk_3C6--;
        }
    }

    if (ENGO_GET_F(&this->actor) == ENGO_F_8) {
        func_80A124A0(this, play);
    } else if (this->flags & 0x100) {
        func_80A123A0(this, play);
    } else if (this->flags & ENGO_FLAG_CURLED) {
        func_80A124FC(this, play);
    } else if (this->flags & 0x400) {
        func_80A125BC(this, play);
    } else {
        func_80A12660(this, play);
    }
}

s32 func_80A12774(EnGo* this, PlayState* play) {
    if (!(this->flags & 7) || !Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        return false;
    }

    if ((ENGO_GET_F(&this->actor) != ENGO_F_8) && (ENGO_GET_F(&this->actor) != ENGO_F_1)) {
        if (!(this->flags & ENGO_FLAG_CURLED)) {
            this->flags |= 8;
        }
    }

    if ((ENGO_GET_F(&this->actor) == ENGO_F_5) || (ENGO_GET_F(&this->actor) == ENGO_F_6) ||
        (ENGO_GET_F(&this->actor) == ENGO_F_7)) {
        this->blinkCountdown = 0;
        this->indexEyeTex = ENGO_EYE_OPEN;
        this->flags |= ENGO_FLAG_BLINKING;
    }

    SubS_UpdateFlags(&this->flags, 0, 7);
    this->cutsceneState = 0;
    this->unk_3C4 = 0;
    this->priorActionFn = this->actionFunc;
    this->actionFunc = func_ACT_80A157C4;
    return true;
}

s32 func_80A12868(EnGo* this, PlayState* play) {
    this->flags &= ~0x800;
    this->flags &= ~0x1000;
    this->flags &= ~0x2000;

    if ((this->colliderCylinder.base.atFlags & AT_HIT) || (this->colliderSphere.base.atFlags & AT_HIT)) {
        this->colliderCylinder.base.atFlags &= ~AT_HIT;
        this->colliderSphere.base.atFlags &= ~AT_HIT;
        this->flags |= 0x800;
        this->unk_3C6 = 0x28;
    }

    if ((this->colliderCylinder.base.acFlags & AC_HIT) || (this->colliderSphere.base.acFlags & AC_HIT)) {
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
        this->colliderSphere.base.acFlags &= ~AC_HIT;
        this->flags |= 0x1000;
    }

    if ((this->colliderCylinder.base.ocFlags1 & OC1_HIT) || (this->colliderSphere.base.ocFlags1 & OC1_HIT)) {
        this->colliderCylinder.base.ocFlags1 &= ~OC1_HIT;
        this->colliderSphere.base.ocFlags1 &= ~OC1_HIT;
        this->flags |= 0x2000;
    }

    return false;
}

s32 func_80A12954(EnGo* this, PlayState* play) {
    if ((ENGO_GET_F(&this->actor) == ENGO_F_4) && (play->csCtx.state != 0) && (this->actor.draw != NULL) &&
        (play->sceneNum == SCENE_10YUKIYAMANOMURA2) && // Snow Mountain Village
        (gSaveContext.sceneSetupIndex == 1) && (play->csCtx.currentCsIndex == 0)) {

        if (this->unk_3F0 == 0) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_394 = 255;
            this->unk_3F0 = 1;
            this->priorActionFn = this->actionFunc;
        }
        SubS_UpdateFlags(&this->flags, 0, 7);
        this->actionFunc = func_ACT_80A14FC8;
    } else if (this->unk_3F0 != 0) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->unk_394 = 255;
        this->unk_3F0 = 0;
        SubS_UpdateFlags(&this->flags, 3, 7);
        this->actionFunc = this->priorActionFn;
    }

    return false;
}

s32 func_80A12A64(EnGo* this, PlayState* play) {
    s8 objIdx = this->actor.objBankIndex;
    s8 objIdx2 = -1;
    s32 ret = 0;

    if ((this->anim >= 18) && (this->indexHakuginDemo >= 0)) {
        objIdx2 = this->indexHakuginDemo;
    } else if ((this->anim >= 10) && (this->indexTaisou >= 0)) {
        objIdx2 = this->indexTaisou;
    } else if (this->anim < 10) {
        objIdx2 = this->actor.objBankIndex;
    }

    if (objIdx2 >= 0) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx2].segment);
        this->skelAnime.playSpeed = this->playSpeed;
        ret = SkelAnime_Update(&this->skelAnime);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx].segment);
    }

    return ret;
}

// Plays Rolling/Unrolling Sitting/Standing sounds.
s32 func_80A12B78(EnGo* this, PlayState* play) {
    if (play->csCtx.state == 0) {
        if (this->anim == ENGO_ANIM_ROLL) {
            if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_CIRCLE);
            }

            if (Animation_OnFrame(&this->skelAnime, 22.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SIT_IMT);
            }
        } else if ((this->anim == ENGO_ANIM_UNROLL) || (this->anim == ENGO_ANIM_UNROLL_IMM)) {
            if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_CIRCLE_OFF);
            }

            if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_STAND_IMT);
            }
        }
    }
    return 0;
}

// Change the animation to the arg2 value (save as anim)
s32 func_80A12C48(EnGo* this, PlayState* play, EnGoAnimationIndex anim) {
    s8 objIdx = this->actor.objBankIndex;
    s8 objIdx2 = -1;
    s32 ret = false;

    if ((anim >= ENGO_ANIM_HAKUGIN_START) && (this->indexHakuginDemo >= 0)) {
        objIdx2 = this->indexHakuginDemo;
    } else if ((anim >= ENGO_ANIM_TAISOU_START) && (this->indexTaisou >= 0)) {
        objIdx2 = this->indexTaisou;
    } else if (anim < ENGO_ANIM_TAISOU_START) {
        objIdx2 = this->actor.objBankIndex;
    }

    if (objIdx2 >= 0) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx2].segment);
        this->anim = anim;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, anim);
        this->playSpeed = this->skelAnime.playSpeed;
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx].segment);
    }

    return ret;
}

void EnGo_HandleBlink(EnGo* this) {
    if ((this->flags & ENGO_FLAG_BLINKING) && (DECR(this->blinkCountdown) == 0)) {
        this->indexEyeTex++;
        if (this->indexEyeTex >= ENGO_EYE_CLOSED2) {
            this->blinkCountdown = Rand_S16Offset(30, 30);
            this->indexEyeTex = ENGO_EYE_OPEN;
        }
    }
}

// Changes Animation from ? to ShiveringSurprised to Shivering
void func_80A12DF4(EnGo* this, PlayState* play) {
    if (this->unk_3D4 == 0) {
        func_80A12C48(this, play, ENGO_ANIM_SHIVERINGSURPRISED);
        this->unk_3D4++;
    } else if ((this->unk_3D4 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80A12C48(this, play, ENGO_ANIM_SHIVER_IMM);
        this->unk_3D4++;
    }
}

// Handling Dialog
s32 func_80A12E80(EnGo* this, PlayState* play) {
    u16 textId = play->msgCtx.currentTextId;
    Player* player = GET_PLAYER(play);

    if (ENGO_GET_F(&this->actor) != ENGO_F_4) {
        return false;
    }

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        if (this->lastTextId != textId) {
            switch (textId) {
                case 0xE1A: // Hunh? What  have I been doing?
                    this->flags |= 8;
                    this->targetActor = this->actor.child;
                    break;

                case 0xE1D: // You hear this guy? The great Darmani died long ago and is lying in his gr...
                case 0xE25: // ...Really? I don't know who you are, but thank you!
                    if (ENGO_GET_70(&this->actor) == ENGO_70_1) {
                        this->targetActor = &GET_PLAYER(play)->actor;
                    }
                    break;

                case 0xE27: // What's this?
                    if (ENGO_GET_70(&this->actor) == ENGO_70_1) {
                        this->targetActor = this->actor.child;
                    }

                case 0xE16: // Y-you're...No! No, you're not the great Darmani, are you?
                case 0xE1E: // Heeee!!! Darmani!
                    this->dialogActionFn = func_80A12DF4;
                    break;

                case 0xE1F: // I was shocked, too. But somehow, it seems the great Darmani isn't dead.
                    if (ENGO_GET_70(&this->actor) == ENGO_70_0) {
                        this->targetActor = &GET_PLAYER(play)->actor;
                    }
                    break;
            }
        }
        this->unk_3F4 = 1;
        this->lastTextId = textId;
    } else if (this->unk_3F4 != 0) {
        this->unk_3F4 = 0;
        this->dialogActionFn = NULL;
        this->lastTextId = 0;
        func_80A12C48(this, play, ENGO_ANIM_SHIVER);
        this->flags &= ~8;
    }

    if (this->dialogActionFn != NULL) {
        this->dialogActionFn(this, play);
    }

    return false;
}

// Move Towards Player?
s32 func_80A12FE8(EnGo* this, PlayState* play) {
    s32 pad;
    Vec3f targetActorPos;
    Vec3f thisActorPos;
    s16 yaw;

    Math_Vec3f_Copy(&targetActorPos, &this->targetActor->world.pos);
    Math_Vec3f_Copy(&thisActorPos, &this->actor.world.pos);
    yaw = Math_Vec3f_Yaw(&thisActorPos, &targetActorPos);

    Math_ApproachS(&this->unk_3B2, (yaw - this->unk_3B6) - this->actor.shape.rot.y, 4, 0x2AA8); /* 60 degree */
    this->unk_3B2 = CLAMP(this->unk_3B2, -0x1FFE, 0x1FFE);                                      /* +-45 degrees */

    Math_ApproachS(&this->unk_3B6, (yaw - this->unk_3B2) - this->actor.shape.rot.y, 4, 0x2AA8); /* 60 degree */
    this->unk_3B6 = CLAMP(this->unk_3B6, -0x1C70, 0x1C70);                                      /* +-40 degrees */

    Math_Vec3f_Copy(&thisActorPos, &this->actor.focus.pos);

    if (this->targetActor->id == ACTOR_PLAYER) {
        targetActorPos.y = ((Player*)this->targetActor)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&targetActorPos, &this->targetActor->focus.pos);
    }

    Math_ApproachS(&this->unk_3B0, Math_Vec3f_Pitch(&thisActorPos, &targetActorPos) - this->unk_3B4, 4,
                   0x2AA8);                                /* 60 degree */
    this->unk_3B0 = CLAMP(this->unk_3B0, -0x1554, 0x1554); /* +-30 degrees */

    Math_ApproachS(&this->unk_3B4, Math_Vec3f_Pitch(&thisActorPos, &targetActorPos) - this->unk_3B0, 4,
                   0x2AA8);                              /* 60 degree */
    this->unk_3B4 = CLAMP(this->unk_3B4, -0xE38, 0xE38); /* +-20 degrees */

    return false;
}

s32 func_80A131F8(EnGo* this, PlayState* play) {
    if (this->unk_3F4 == 0) {
        this->targetActor = &GET_PLAYER(play)->actor;
    }

    func_80A12E80(this, play); // Handling Dialog?

    if (this->flags & 0x08) {
        this->flags &= ~0x40;
        this->flags |= 0x10;
        func_80A12FE8(this, play); // Moving Towards Player?
    } else if (this->flags & 0x10) {
        this->flags &= ~0x10;
        this->unk_3B0 = 0;
        this->unk_3B2 = 0;
        this->unk_3B4 = 0;
        this->unk_3B6 = 0;
        this->unk_3BA = 0x14;
    } else if (DECR(this->unk_3BA) == 0) {
        this->flags |= 0x40;
        this->unk_3BA = 0x14;
    }

    return true;
}

void func_80A132C8(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v1 = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    if ((fabsf(this->actor.playerHeightRel) > 20.0f) || (this->actor.xzDistToPlayer > 300.0f)) {
        // Break off conversation if distances are too great?
        SubS_UpdateFlags(&this->flags, 3, 7); // |= 0x08 &= ~0x80
    } else if ((player->transformation != PLAYER_FORM_GORON) || (ABS_ALT(temp_v1) >= 0x1C70) ||
               (gSaveContext.save.weekEventReg[21] & 4) || (gSaveContext.save.weekEventReg[21] & 8)) {
        // Change Flags if not goron or yaw too great or certain events are set.
        SubS_UpdateFlags(&this->flags, 3, 7); // |= 0x08 &= ~0x80
    } else {
        // Change OTHER flags
        SubS_UpdateFlags(&this->flags, 4, 7); // |= 0x10 &= ~0x80
    }
}

void func_80A133A8(EnGo* this, PlayState* play) {
    if (gSaveContext.save.weekEventReg[21] & 8) {
        SubS_UpdateFlags(&this->flags, 3, 7);
    } else {
        SubS_UpdateFlags(&this->flags, 4, 7);
    }
}

Actor* func_80A13400(EnGo* this, PlayState* play) {
    Actor* actor;
    Actor* retActor = NULL;

    while (true) {
        actor = SubS_FindActor(play, retActor, ACTORCAT_NPC, ACTOR_EN_GO);
        retActor = actor;

        if ((actor != NULL) && ((EnGo*)actor != this) && (ENGO_GET_F(actor) == ENGO_F_4) &&
            (ENGO_GET_70(actor) == ENGO_70_0)) {
            return retActor;
        }

        if (actor == NULL) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            break;
        }
        retActor = actor;
    }

    return NULL;
}

void func_80A134B0(EnGo* this, PlayState* play, s32 arg2) {
    if ((gSaveContext.save.weekEventReg[18] & 0x80) || (play->actorCtx.unk5 & 1) || arg2) {
        this->colliderSphere.dim.modelSphere.radius = 300;
    } else {
        this->colliderSphere.dim.modelSphere.radius = 380;
    }
}

s32 func_80A134F4(EnGo* this, s16 arg1) {
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        return true;
    }
    ActorCutscene_SetIntentToPlay(arg1);
    return false;
}

s32 func_80A13564(EnGo* this, f32 arg1, f32 arg2, s32 arg3) {
    s32 pad;
    f32 temp_f0 = 1.0f;
    f32 temp_f14 = this->actor.velocity.y + this->actor.gravity;
    s32 ret;

    if (this->actor.bgCheckFlags & 2) {
        ret = true;
    } else {
        if (temp_f14 > 0.0f) {
            temp_f0 = temp_f14 / arg1;
            this->actor.shape.rot.x += (s16)(9100.0f * temp_f0);
            this->unk_3AE = 0;
        } else if ((s32)this->actor.velocity.y == 0) {
            if (arg3 >= this->unk_3AE) {
                temp_f0 = (f32)this->unk_3AE / arg3;
            } else {
                this->actor.gravity = -6.0f;
            }
            this->unk_3AE++;
        } else if (this->unk_3AE == 0) {
            this->actor.velocity.y = 0.0f;
            this->actor.gravity = 0.0f;
            temp_f0 = temp_f14 / arg1;
        }
        ret = false;
    }

    this->unk_3A8 = (1.0f - temp_f0) * arg2;
    this->actor.scale.x = this->scale - this->unk_3A8;
    this->actor.scale.y = this->scale + this->unk_3A8;

    if (this->actor.scale.y < this->actor.scale.x) {
        this->actor.scale.z = this->actor.scale.x;
    } else {
        this->actor.scale.z = this->actor.scale.y;
    }
    return ret;
}

void func_80A136B8(PlayState* play, s16 arg1, s16 arg2, s16 arg3) {
    s16 sp26 = Quake_Add(Play_GetCamera(play, CAM_ID_MAIN), 3);

    Quake_SetCountdown(sp26, arg3);
    Quake_SetSpeed(sp26, arg1);
    Quake_SetQuakeValues(sp26, arg2, 0, 0, 0);
}

void func_80A13728(EnGo* this, PlayState* play) {
    func_80A136B8(play, 0x6C77, 7, 20);
    play->actorCtx.unk2 = 4;
    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, 0);
    EffectSsBlast_SpawnWhiteShockwave(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f);
}

void func_80A137C0(EnGo* this, PlayState* play, f32 arg2, f32 arg3) {
    u32 frames1;
    u32 frames2;

    if (this->flags & 0x400) {
        Matrix_Push();

        OPEN_DISPS(play->state.gfxCtx);

        func_8012C2DC(play->state.gfxCtx);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(arg2 * 0.7f, arg2 * 0.8f, arg2, MTXMODE_APPLY);
        func_800B8118(&this->actor, play, 0);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        frames1 = play->gameplayFrames % 256;
        frames2 = (play->gameplayFrames * 2) % 256;
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, frames1, 0x20, 0x10, 1, 0, frames2, 0x40, 0x20));
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, (u8)arg3);
        gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);

        CLOSE_DISPS(play->state.gfxCtx);

        Matrix_Pop();
    }
}

void func_80A139E4(EnGo* this) {
    static Vec3f D_80A16698 = { 0.0f, 0.06f, 0.0f };
    Vec3f sp54;
    Vec3f sp48;
    s16 rotAngle = Rand_ZeroOne() * 360.0f * 182.0f;

    Math_Vec3f_Copy(&sp54, &gZeroVec3f);
    sp54.z = 28.0f;
    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, rotAngle, &sp54, &sp48);
    sp48.y = (Rand_ZeroOne() * 10.0f) + 4.0f;
    sp48.y += this->actor.floorHeight;
    func_80A10FD0(&this->unk_3F8[16], sp48, D_80A16698, gZeroVec3f, 0.01f, 0.002f, 16);
}

s32 func_CB_80A13B1C(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    EnGo* this = THIS;
    s32 ret = false;

    switch (this->cutsceneState) {
        case 0:
            this->indexCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            if (func_80A134F4(this, this->indexCutscene)) {
                this->unk_3C4 = 1;
                this->cutsceneState = 1;
            } else {
                break;
            }

        case 1:
            if (ActorCutscene_GetCurrentIndex() != this->indexCutscene) {
                this->indexCutscene = ActorCutscene_GetAdditionalCutscene(this->indexCutscene);
                this->cutsceneState = 2;
            } else {
                break;
            }

        case 2:
            if (func_80A134F4(this, this->indexCutscene)) {
                this->cutsceneState = 3;
            } else {
                break;
            }

        case 3:
            if (ActorCutscene_GetCanPlayNext(0x7C)) {
                ActorCutscene_StartAndSetUnkLinkFields(0x7C, NULL);
                this->cutsceneState = 4;
            } else if (ActorCutscene_GetCurrentIndex() == this->indexCutscene) {
                ActorCutscene_SetIntentToPlay(0x7C);
            }
    }

    switch (this->unk_3C4) {
        case 1:
            func_80A12C48(this, play, ENGO_ANIM_ROLL);
            this->flags |= ENGO_FLAG_CURLING;
            this->unk_3C4++;
            break;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->flags &= ~ENGO_FLAG_CURLING;
                this->flags &= ~0x80;
                this->flags |= ENGO_FLAG_CURLED;
                this->unk_3C4++;
                this->unk_3C2 = 0;
                this->actor.shape.yOffset = 14.0f;
            }
            break;

        case 3:
            this->unk_3C2++;
            if (this->unk_3C2 >= 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_JUMP);
                this->actor.velocity.y = 10.0f;
                this->actor.gravity = -1.0f;
                this->unk_3C4++;
            }
            break;

        case 4:
            if (func_80A13564(this, 10.0f, 0.004f, 6)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_LAND_BIG);
                func_80A13728(this, play);
                this->unk_3C4++;
                this->unk_3C2 = 0;
                gSaveContext.save.weekEventReg[88] |= 0x40;
            }
            break;

        case 5:
            this->unk_3C2++;
            if (this->unk_3C2 >= 10) {
                func_80A12C48(this, play, 5);
                this->actor.shape.rot.x = 0;
                this->flags &= ~ENGO_FLAG_CURLED;
                this->flags |= 0x80;
                this->unk_3C4++;
            }
            break;

        case 6:
            this->cutsceneState++;
            if (this->cutsceneState >= 65) {
                switch (player->transformation) {
                    case PLAYER_FORM_HUMAN:
                        gSaveContext.save.weekEventReg[88] |= 0x80;
                        break;

                    case PLAYER_FORM_GORON:
                        gSaveContext.save.weekEventReg[89] |= 4;
                        break;

                    case PLAYER_FORM_ZORA:
                        gSaveContext.save.weekEventReg[89] |= 2;
                        break;

                    case PLAYER_FORM_DEKU:
                        gSaveContext.save.weekEventReg[89] |= 1;
                        break;
                }
                ret = true;
            }
            break;
    }

    Actor_MoveWithGravity(&this->actor);
    return ret;
}

s32 func_CB_80A13E80(Actor* thisx, PlayState* play) {
    static Vec3f D_80A166A4 = { 0.0f, 200.0f, 280.0f };
    EnGo* this = THIS;
    Vec3f sp48;
    s32 ret = false;

    switch (this->cutsceneState) {
        case 0:
            this->indexCutscene = this->actor.cutscene;
            if (func_80A134F4(this, this->indexCutscene)) {
                this->cutsceneState++;
            }
            break;

        case 1:
            func_80A12C48(this, play, 7);
            this->cutsceneState++;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, 16.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_HAND_HIT);
            }

            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80A12C48(this, play, 1);
                Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80A166A4, &sp48);
                gSaveContext.powderKegTimer = 2400;
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, sp48.x, sp48.y, sp48.z, 1, 0, 0, 0);
                func_80A134B0(this, play, 1);
                this->unk_3C2 = 0;
                this->cutsceneState++;
            }
            break;

        case 3:
            if (this->unk_3C2 >= 60) {
                ActorCutscene_Stop(this->indexCutscene);
                this->unk_3C2 = 0;
                this->cutsceneState = 0;
                ret = true;
            } else {
                this->unk_3C2++;
            }
            break;
    }

    return ret;
}

void func_80A14018(EnGo* this, PlayState* play) {
    static Vec3f D_80A166B0 = { 0.0f, 0.0f, 40.0f };
    static s32 D_80A166BC[] = { 11, 10, 12, 13, 14, 17 };
    Vec3f sp2C;
    s32 phi_v0 = ENGO_GET_70(&this->actor) % 6;

    if (phi_v0 < 4) {
        phi_v0 = ((gSaveContext.eventInf[2] & 0xF) + phi_v0) % 4;
    }

    func_80A12C48(this, play, D_80A166BC[phi_v0]);

    if (this->anim == ENGO_ANIM_TAISOU_14) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80A166B0, &sp2C);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp2C);
    }
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, this->scale);
    this->sleepState = ENGO_AWAKE;
    this->flags = ENGO_FLAG_NONE;
    this->flags |= (0x40 | ENGO_FLAG_BLINKING);
    this->actor.gravity = 0.0f;
}

void func_80A14104(EnGo* this, PlayState* play) {
    static s32 D_80A166D4[] = { ENGO_ANIM_TAISOU_15, ENGO_ANIM_TAISOU_16 };
    s16 animFrame;

    func_80A12C48(this, play, D_80A166D4[ENGO_GET_70(&this->actor) % 2]);
    // Randomize the starting position of the animation
    animFrame = Rand_ZeroOne() * this->skelAnime.endFrame;
    this->skelAnime.curFrame = animFrame;

    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, this->scale);
    this->sleepState = ENGO_AWAKE;
    this->flags = ENGO_FLAG_NONE;
    this->flags |= 0x40;
    this->flags |= ENGO_FLAG_BLINKING;
    this->actor.gravity = 0.0f;
}

void func_80A141D4(EnGo* this, PlayState* play) {
    Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit1);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->anim = -1;
    func_80A12C48(this, play, 5);
    this->sleepState = ENGO_AWAKE;
    this->unk_39C = (this->scale / 0.01f) * 0.9f;
    this->indexEyeTex = ENGO_EYE_CLOSED;
    this->flags = ENGO_FLAG_NONE;
    this->flags |= 0x40;
    this->flags |= 0x400;
    this->unk_3A0 = 100.0f;
}

void func_80A1428C(EnGo* this, PlayState* play) {
    s16 temp;
    Vec3f sp30;
    Vec3f sp24;

    Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
    if (this->path != NULL) {
        this->actor.flags &= ~ACTOR_FLAG_2000000;
        SubS_CopyPointFromPathCheckBounds(this->path, 0, &sp24);
        temp = Math_Vec3f_Yaw(&sp30, &sp24);
        this->actor.shape.rot.y = temp;
        this->actor.world.rot.y = temp;
    }
    this->flags = ENGO_FLAG_NONE;
    this->flags |= 0x100;
    this->actor.shape.yOffset = 46.0f;
    this->actor.gravity = -1.0f;
}

void func_80A14324(EnGo* this, PlayState* play) {
    func_80A12C48(this, play, 8);
    Actor_SetScale(&this->actor, this->scale);
    this->flags = ENGO_FLAG_NONE;
    this->actor.gravity = -1.0f;
    SubS_UpdateFlags(&this->flags, 3, 7);
    this->sleepState = ENGO_AWAKE;
    this->flags |= 0x40;
    this->blinkCountdown = 0;
    this->indexEyeTex = ENGO_EYE_CLOSED2;
    this->unk_39C = 0.0f;
    this->unk_3A0 = 0.0f;
}

void func_80A143A8(EnGo* this, PlayState* play) {
    func_80A12C48(this, play, 5);
    Actor_SetScale(&this->actor, this->scale);
    this->flags = ENGO_FLAG_NONE;
    this->actor.gravity = -1.0f;
    SubS_UpdateFlags(&this->flags, 3, 7);
    this->sleepState = ENGO_AWAKE;
    this->flags |= 0x40;
    this->flags |= ENGO_FLAG_BLINKING;
    this->blinkCountdown = 0;
    this->indexEyeTex = ENGO_EYE_OPEN;
    this->unk_39C = 0.0f;
    this->unk_3A0 = 0.0f;
}

void func_80A14430(EnGo* this, PlayState* play) {
    if (((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 0)) ||
         (gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 2))) &&
        (gSaveContext.save.weekEventReg[33] & 0x80)) {
        func_80A14018(this, play);
        this->actionFunc = func_ACT_80A149B0;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80A1449C(EnGo* this, PlayState* play) {
    if ((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1)) ||
        (gSaveContext.save.entrance == ENTRANCE(CUTSCENE, 0))) {
        func_80A14104(this, play);
        this->actionFunc = func_ACT_80A149B0;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80A144F4(EnGo* this, PlayState* play) {
    if (gSaveContext.save.day >= 2) {
        this->path = SubS_GetDayDependentPath(play, ENGO_GET_7F80(&this->actor), 0xFF, &this->indexPathPoint);
        if (this->path != NULL) {
            this->indexPathPoint = 1;
        }
        func_80A1428C(this, play);
        this->actionFunc = func_ACT_80A153FC;
        this->msgEventCb = func_CB_80A13B1C;
    } else {
        func_80A143A8(this, play);
        this->actionFunc = func_ACT_80A149B0;
        this->msgEventCb = func_CB_80A13B1C;
    }
}

void func_80A145AC(EnGo* this, PlayState* play) {

    if ((ENGO_GET_70(&this->actor) == ENGO_70_1) &&
        (((play->sceneNum == SCENE_10YUKIYAMANOMURA2) && /* Snow Mountain Village */
          (gSaveContext.sceneSetupIndex == 1) && (play->csCtx.currentCsIndex == 0)) ||
         !(gSaveContext.save.weekEventReg[21] & 8))) {
        this->actor.child = func_80A13400(this, play);
        this->actor.child->child = &this->actor;
        func_80A141D4(this, play);
        this->actionFunc = func_ACT_80A14E14;
    } else {
        func_80A143A8(this, play);
        this->actionFunc = func_ACT_80A149B0;
    }
}

void func_80A14668(EnGo* this, PlayState* play) {
    if (!(gSaveContext.save.weekEventReg[22] & 4)) {
        func_80A14324(this, play);
        this->actionFunc = func_ACT_80A149B0;
    } else {
        func_80A143A8(this, play);
        this->actionFunc = func_ACT_80A149B0;
    }
}

void func_80A146CC(EnGo* this, PlayState* play) {
    func_80A134B0(this, play, 0);
    func_80A12C48(this, play, 0);
    this->scale *= 5.0f;
    Actor_SetScale(&this->actor, this->scale);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.targetMode = 3;
    this->flags = ENGO_FLAG_NONE;
    this->actor.gravity = -1.0f;
    SubS_UpdateFlags(&this->flags, 3, 7);
    this->flags |= 0x40;
    this->flags |= ENGO_FLAG_BLINKING;
    this->msgEventCb = func_CB_80A13E80;
    this->actionFunc = func_ACT_80A149B0;
}

// Initial Action Function
void func_ACT_80A14798(EnGo* this, PlayState* play) {
    EffectTireMarkInit tireMarkInit = {
        0,
        62,
        { 0, 0, 15, 100 },
    };

    if ((this->indexTaisou < 0) || SubS_IsObjectLoaded(this->indexTaisou, play) || (this->indexHakuginDemo < 0) ||
        SubS_IsObjectLoaded(this->indexHakuginDemo, play)) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gGoronSkel, NULL, this->jointTable, this->morphTable,
                           GORON_LIMB_MAX);

        this->anim = ENGO_ANIM_INVALID;
        func_80A12C48(this, play, ENGO_ANIM_UNROLL);
        this->actor.draw = EnGo_Draw;

        Collider_InitAndSetSphere(play, &this->colliderSphere, &this->actor, &sSphereInit);
        Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit2);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        Effect_Add(play, &this->unk_3E8, EFFECT_TIRE_MARK, 0, 0, &tireMarkInit);

        this->actor.targetMode = 1;
        this->scale = 0.01f;
        this->msgEventCb = NULL;

        switch (ENGO_GET_F(&this->actor)) {
            case ENGO_F_1:
                func_80A14430(this, play);
                break;

            case ENGO_F_2:
                func_80A1449C(this, play);
                break;

            case ENGO_F_3:
                func_80A144F4(this, play);
                break;

            case ENGO_F_4:
                func_80A145AC(this, play);
                break;

            case ENGO_F_5:
            case ENGO_F_6:
            case ENGO_F_7:
                func_80A14668(this, play);
                break;

            case ENGO_F_8:
                func_80A146CC(this, play);
                break;

            default:
                Actor_MarkForDeath(&this->actor);
                break;
        }
    }
}

/* Action function*/
void func_ACT_80A149B0(EnGo* this, PlayState* play) {
    s16 sp26 = this->actor.world.rot.y;

    if ((ENGO_GET_F(&this->actor) == ENGO_F_2) && (gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_CHEER - SFX_FLAG);
    } else if (ENGO_GET_F(&this->actor) != ENGO_F_8) {
        if (EnGo_IsEnteringSleep(this, play)) {
            SubS_UpdateFlags(&this->flags, 0, 7); // &= ~0x80
            this->sleepState = ENGO_ASLEEP;
            this->actionFunc = func_ACT_80A14B30;
        } else if (ENGO_GET_F(&this->actor) == ENGO_F_4) {
            switch (ENGO_GET_70(&this->actor)) {
                case ENGO_70_0:
                    func_80A132C8(this, play);
                    break;

                case ENGO_70_1:
                    func_80A133A8(this, play);
                    break;
            }
        } else if (ENGO_GET_F(&this->actor) == ENGO_F_1) {
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3FFC) {
                SubS_UpdateFlags(&this->flags, 3, 7); // |=0x08 &= ~0x80
            } else {
                SubS_UpdateFlags(&this->flags, 0, 7); // &= ~0x80
            }
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, sp26, 4, 0x2AA8);
}

void func_ACT_80A14B30(EnGo* this, PlayState* play) {
    s16 sp26 = this->actor.world.rot.y;
    u16 sfxId;

    if (EnGo_IsEnteringSleep(this, play)) {
        this->sleepState = ENGO_ASLEEP;
    }

    if (this->flags & ENGO_FLAG_CURLING) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->flags &= ~ENGO_FLAG_CURLING;
            this->flags |= ENGO_FLAG_CURLED;
            if (this->sleepState != ENGO_AWAKE) {
                this->unk_3AE = 0;
            }
            this->actor.shape.yOffset = 14.0f;
        }
    } else if (this->flags & 0x8000) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->flags |= 0x80;
            this->flags &= ~0x8000;
        }
    } else if (this->flags & ENGO_FLAG_CURLED) {
        if ((this->actor.xzDistToPlayer < 160.0f) && (this->actor.playerHeightRel < 20.0f) &&
            (this->sleepState == ENGO_AWAKE)) {
            func_80A12C48(this, play, ENGO_ANIM_UNROLL_IMM);
            this->flags &= ~0x80;
            this->flags &= ~ENGO_FLAG_CURLED;
            this->flags |= 0x8000;
            this->actor.shape.yOffset = 0.0f;
        } else if ((this->sleepState != ENGO_AWAKE) && (gSaveContext.save.weekEventReg[22] & 4)) {
            this->actor.scale.x = this->scale - (Math_SinS(this->unk_3AE) * 0.001f);
            this->actor.scale.y = (Math_SinS(this->unk_3AE) * 0.001f) + this->scale;
            this->actor.scale.z = (Math_SinS(this->unk_3AE) * 0.001f) + this->scale;
            if (this->unk_3AE == 0) {
                this->sleepState = -this->sleepState;
                if (this->sleepState > ENGO_AWAKE) {
                    sfxId = NA_SE_EN_GOLON_SNORE1;
                } else {
                    sfxId = NA_SE_EN_GOLON_SNORE2;
                }
                Actor_PlaySfxAtPos(&this->actor, sfxId);
            }
            this->unk_3AE += 0x400;
            this->actor.shape.yOffset = (this->actor.scale.y / this->scale) * 14.0f;
            SubS_UpdateFlags(&this->flags, 3, 7);
        }
    } else if ((this->actor.xzDistToPlayer >= 240.0f) || (this->actor.playerHeightRel >= 20.0f) ||
               (this->sleepState != ENGO_AWAKE)) {
        func_80A12C48(this, play, ENGO_ANIM_ROLL);
        this->flags &= ~0x80;
        this->flags &= ~ENGO_FLAG_CURLED;
        this->flags |= ENGO_FLAG_CURLING;
        this->actor.shape.yOffset = 0.0f;
    }

    SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
    Math_ApproachS(&this->actor.shape.rot.y, sp26, 4, 0x2AA8);
}

void func_ACT_80A14E14(EnGo* this, PlayState* play) {
    Actor* actor = this->colliderCylinder.base.ac;

    if ((this->flags & 0x1000) && (((actor != NULL) && (actor->id == ACTOR_OBJ_AQUA) && (actor->params & 1)) ||
                                   (this->actor.colChkInfo.damageEffect == 2))) {
        this->actionFunc = func_ACT_80A14E74;
    }
}

void func_ACT_80A14E74(EnGo* this, PlayState* play) {
    if (func_80A134F4(this, this->actor.cutscene)) {
        this->actionFunc = func_ACT_80A14EB0;
    }
}

void func_ACT_80A14EB0(EnGo* this, PlayState* play) {
    EnGo* sp24 = (EnGo*)this->actor.child;

    if ((s32)(this->unk_39C * 3.0f) != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
        Math_ApproachF(&this->unk_39C, 0.0f, 0.02f, 1.0f);
        this->unk_3A0 = (this->unk_39C / 0.9f) * 100.0f;
        func_80A139E4(this);
    } else {
        ActorCutscene_Stop(this->actor.cutscene);
        func_80A143A8(this, play);
        if ((ENGO_GET_F(&this->actor) == ENGO_F_4) && (ENGO_GET_70(&this->actor) == ENGO_70_1)) {
            SubS_UpdateFlags(&this->flags, 4, 7);
            func_80A143A8(sp24, play);
            sp24->actionFunc = func_ACT_80A149B0;
        }
        this->actionFunc = func_ACT_80A149B0;
    }
}

void func_ACT_80A14FC8(EnGo* this, PlayState* play) {
    s32 sp38[] = {
        0, 2, 6, 20, 18, 5, 5, 15,
    };
    u16 actorActionCmd = 0;
    s32 csAction;
    s32 actionIndex;

    switch (ENGO_GET_70(&this->actor)) {
        case ENGO_70_0:
            actorActionCmd = 128;
            break;

        case ENGO_70_1:
            actorActionCmd = 129;
            break;
    }

    if ((actorActionCmd == 128) || (actorActionCmd == 129)) {
        if (Cutscene_CheckActorAction(play, actorActionCmd)) {
            actionIndex = Cutscene_GetActorActionIndex(play, actorActionCmd);
            csAction = play->csCtx.actorActions[actionIndex]->action;

            if (this->unk_394 != (u8)csAction) {
                this->unk_394 = csAction;
                func_80A12C48(this, play, sp38[csAction]);
                this->flags = ENGO_FLAG_NONE;
                this->flags |= ENGO_FLAG_BLINKING;
                this->indexEyeTex = ENGO_EYE_OPEN;
                this->unk_39C = 0.0f;
                this->unk_3A0 = 0.0f;

                switch (csAction) {
                    case 1:
                        this->flags |= 0x80;
                        this->skelAnime.curFrame = this->skelAnime.endFrame;
                        break;

                    case 5:
                    case 6:
                        func_80A141D4(this, play);
                        break;
                }
            }

            switch (this->unk_394) {
                case 3:
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) &&
                        (this->anim == ENGO_ANIM_HAKUGIN_20)) {
                        func_80A12C48(this, play, ENGO_ANIM_HAKUGIN_21_IMM);
                    }
                    break;

                case 4:
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) &&
                        (this->anim == ENGO_ANIM_HAKUGIN_18)) {
                        func_80A12C48(this, play, ENGO_ANIM_HAKUGIN_19_IMM);
                    }
                    break;

                case 6:
                    if ((s32)(this->unk_39C * 3.0f) != 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
                        Math_ApproachF(&this->unk_39C, 0.0f, 0.02f, 1.0f);
                        this->unk_3A0 = (this->unk_39C / 0.9f) * 100.0f;
                        func_80A139E4(this);
                    } else if (this->flags & 0x400) {
                        func_80A143A8(this, play);
                    }
                    break;
            }

            if (actorActionCmd == 128) {
                switch (play->csCtx.frames) {
                    case 55:
                    case 100:
                    case 130:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);
                        break;

                    case 185:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_WAKE_UP);
                        break;

                    case 250:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_EYE_BIG);
                        break;

                    case 465:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_IWAIGORON_SOLO);
                        break;

                    case 490:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_VOICE_EATFULL);
                        break;
                }
            } else if (actorActionCmd == 129) {
                switch (play->csCtx.frames) {
                    case 360:
                    case 390:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);
                        break;

                    case 430:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_WAKE_UP);
                        break;

                    case 450:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_EYE_BIG);
                        break;

                    case 480:
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_VOICE_EATFULL);
                        break;
                }
            }

            SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
        }
    }
}

/* Action function, called on day 2 or greater */
void func_ACT_80A153FC(EnGo* this, PlayState* play) {
    Vec3s* sp5C;
    Vec3f sp50;
    Vec3f sp44;

    if ((this->flags & 0x1000) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SNOWBALL_BROKEN);

        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;

        func_80A118F8(this->unk_3F8, this->actor.world.pos);
        this->actor.shape.rot.x = 0;
        this->actor.speedXZ = 0.0f;

        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);

        if (gSaveContext.save.day == 3) {
            func_80A141D4(this, play);
            this->actionFunc = func_ACT_80A14E14;
        } else {
            func_80A143A8(this, play);
            this->actionFunc = func_ACT_80A149B0;
        }
    } else if (this->path != NULL) {
        if (this->flags & 0x800) {
            func_800B8E58(GET_PLAYER(play), NA_SE_PL_BODY_HIT);
            func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);
        }

        sp5C = Lib_SegmentedToVirtual(this->path->points);
        if (SubS_HasReachedPoint(&this->actor, this->path, this->indexPathPoint)) {
            if (this->indexPathPoint >= (this->path->count - 1)) {
                this->indexPathPoint = 0;
            } else {
                this->indexPathPoint++;
            }
        }

        Math_Vec3s_ToVec3f(&sp44, &sp5C[this->indexPathPoint]);
        Math_Vec3f_Copy(&sp50, &this->actor.world.pos);
        Math_ApproachS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&sp50, &sp44), 4, 0x38E);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (this->actor.bgCheckFlags & 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BIGBALL_ROLL - SFX_FLAG);
            func_800AE930(&play->colCtx, Effect_GetByIndex(this->unk_3E8), &this->actor.world.pos, 18.0f,
                          this->actor.shape.rot.y, this->actor.floorPoly, this->actor.floorBgId);
        } else {
            func_800AEF44(Effect_GetByIndex(this->unk_3E8));
        }

        this->actor.speedXZ = 4.0f;
        this->actor.shape.rot.x += (s16)(this->actor.speedXZ * 546.0f);
        Actor_MoveWithGravity(&this->actor);
    }
}

s32* func_80A15684(EnGo* this, PlayState* play) {
    static s32 D_80A16704[] = {
        D_80A16100,
        D_80A16164,
    };

    if (this->sleepState != ENGO_AWAKE) {
        return D_80A1640C;
    }

    if (ENGO_GET_F(&this->actor) == ENGO_F_1) {
        switch (ENGO_GET_70(&this->actor) % 6) {
            case ENGO_70_0:
                return D_80A163BC;
            case ENGO_70_1:
                return D_80A163CC;
            case ENGO_70_2:
                return D_80A163DC;
            case ENGO_70_3:
                return D_80A163EC;
            case ENGO_70_4:
                return D_80A163FC;
            case ENGO_70_5:
                return D_80A163FC;
        }
    }

    switch (ENGO_GET_F(&this->actor)) {
        case ENGO_F_3:
            return D_80A16350;
        case ENGO_F_4:
            return D_80A16704[ENGO_GET_70(&this->actor)];
        case ENGO_F_5:
            return D_80A16208;
        case ENGO_F_6:
            return D_80A16254;
        case ENGO_F_7:
            return D_80A16210;
        case ENGO_F_8:
            return D_80A16280;
        default:
            return D_80A16208;
    }
}

void func_ACT_80A157C4(EnGo* this, PlayState* play) {
    s32 pad;
    Vec3f targetActorPos;
    Vec3f thisActorPos;

    if (!func_8010BF58(&this->actor, play, func_80A15684(this, play), // MsgScript*
                       this->msgEventCb,                              // MsgEventCallback
                       &this->msgScriptResumePos                      // s32* resumePosition
                       )) {
        if ((ENGO_GET_F(&this->actor) != ENGO_F_1) && !(this->flags & ENGO_FLAG_CURLED)) {
            Math_Vec3f_Copy(&targetActorPos, &this->targetActor->world.pos);
            Math_Vec3f_Copy(&thisActorPos, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&thisActorPos, &targetActorPos), 4, 0x2AA8);
        }
        SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
        return;
    }

    if ((ENGO_GET_F(&this->actor) == ENGO_F_5) || (ENGO_GET_F(&this->actor) == ENGO_F_6) ||
        (ENGO_GET_F(&this->actor) == ENGO_F_7)) {
        this->blinkCountdown = 0;
        this->flags &= ~ENGO_FLAG_BLINKING;
        this->indexEyeTex = ENGO_EYE_CLOSED2;
    }

    this->flags &= ~0x8;
    SubS_UpdateFlags(&this->flags, 3, 7); // |= 0x08 &= 0x80
    this->msgScriptResumePos = 0;
    this->flags |= 0x40;
    this->actionFunc = this->priorActionFn;
}

void EnGo_Init(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;

    this->indexTaisou = SubS_GetObjectIndex(OBJECT_TAISOU, play);            /* Gymnastics */
    this->indexHakuginDemo = SubS_GetObjectIndex(OBJECT_HAKUGIN_DEMO, play); /* White Silver / Even Silver? */
    this->actionFunc = func_ACT_80A14798;
}

void EnGo_Destroy(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;

    Collider_DestroyCylinder(play, &this->colliderCylinder);
    Collider_DestroySphere(play, &this->colliderSphere);
    Effect_Destroy(play, this->unk_3E8);
}

void EnGo_Update(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;
    f32 phi_f0;

    func_80A12868(this, play);
    if (!func_80A12774(this, play)) {
        func_80A12954(this, play);
    }

    this->actionFunc(this, play);

    if (!(this->flags & 0x400)) {
        EnGo_HandleBlink(this);
        func_80A12A64(this, play);
        func_80A131F8(this, play);
        func_80A12B78(this, play);
    }

    if (!(this->flags & 0x100) && !(this->flags & ENGO_FLAG_CURLED) && !(this->flags & 0x400)) {
        if (ENGO_GET_F(&this->actor) == ENGO_F_8) {
            phi_f0 = this->colliderSphere.dim.worldSphere.radius + 60;
        } else {
            phi_f0 = this->colliderCylinder.dim.radius + 40;
        }
        func_8013C964(&this->actor, play, phi_f0, 20.0f, PLAYER_AP_NONE, this->flags & 7);
    } else if ((this->flags & ENGO_FLAG_CURLED) && (this->sleepState != ENGO_AWAKE)) {
        phi_f0 = this->colliderCylinder.dim.radius + 40;
        func_8013C964(&this->actor, play, phi_f0, 20.0f, PLAYER_AP_NONE, this->flags & 7);
    }

    if ((ENGO_GET_F(&this->actor) != ENGO_F_8) && (ENGO_GET_F(&this->actor) != ENGO_F_2) &&
        (ENGO_GET_F(&this->actor) != ENGO_F_1)) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
    }

    func_80A122EC(this);
    func_80A126BC(this, play);
    func_80A1203C(this);
}

void func_80A15B80(EnGo* this, PlayState* play) {
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + this->actor.shape.yOffset,
                     this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Translate(0.0f, -this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_Translate(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);

    if (this->flags & 0x100) {
        Matrix_Scale(this->actor.scale.x * 8.0f, this->actor.scale.y * 8.0f, this->actor.scale.z * 8.0f, MTXMODE_APPLY);
    } else {
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    }

    Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, (this->flags & 0x100) ? gGoronSnowballDL : gGoronRolledUpDL);

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnGo_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGo* this = THIS;
    Vec3f sp30;
    s32 idx;

    if ((ENGO_GET_F(&this->actor) == ENGO_F_8) && (limbIndex == 10)) {
        Matrix_MultZero(&sp30);
        sp30.y = this->actor.world.pos.y;
        Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp30);
    }

    switch (limbIndex) {
        case 10:
            idx = 0;
            break;

        case 11:
            idx = 1;
            break;

        case 14:
            idx = 2;
            break;

        default:
            idx = 9;
            break;
    }

    if ((this->flags & 0x80) && (idx < 9)) {
        rot->y += (s16)(Math_SinS(this->limbRotTableY[idx]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->limbRotTableZ[idx]) * 200.0f);
    }
    return false;
}

void EnGo_TransfromLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnGo* this = THIS;
    u16 temp_v0;
    s32 stepRot;
    s32 overrideRot;

    if (this->flags & 0x40) {
        stepRot = false;
    } else {
        stepRot = true;
    }

    if (this->flags & 0x10) {
        overrideRot = true;
    } else {
        overrideRot = false;
    }

    if (!stepRot) {
        overrideRot = false;
    }

    switch (limbIndex) {
        case 17:
            SubS_UpdateLimb(this->unk_3B0 + this->unk_3B4 + 0x4000,
                            this->unk_3B2 + this->unk_3B6 + this->actor.shape.rot.y + 0x4000, &this->limb17Pos,
                            &this->limb17Rot, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->limb17Pos.x, this->limb17Pos.y, this->limb17Pos.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->limb17Rot.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->limb17Rot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->limb17Rot.z, MTXMODE_APPLY);
            Matrix_Push();
            break;

        case 10:
            SubS_UpdateLimb(this->unk_3B4 + 0x4000, this->unk_3B6 + this->actor.shape.rot.y + 0x4000, &this->limb10Pos,
                            &this->limb10Rot, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->limb10Pos.x, this->limb10Pos.y, this->limb10Pos.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->limb10Rot.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->limb10Rot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->limb10Rot.z, MTXMODE_APPLY);
            Matrix_Push();
            break;
    }
}

void EnGo_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80A1670C[] = {
        gGoronEyeOpenTex, gGoronEyeHalfTex, gGoronEyeClosedTex, gGoronEyeHalfTex, gGoronEyeClosed2Tex,
    };
    EnGo* this = THIS;

    if (!(this->flags & 0x300)) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C28C(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A1670C[this->indexEyeTex]));

        if (this->anim == ENGO_ANIM_TAISOU_14) {
            Matrix_Translate(0.0f, 0.0f, -4000.0f, MTXMODE_APPLY);
        }
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnGo_OverrideLimbDraw, NULL, EnGo_TransfromLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        func_80A15B80(this, play);
    }
    func_80A137C0(this, play, this->unk_39C, this->unk_3A0);
    func_80A1213C(this, play);
}
