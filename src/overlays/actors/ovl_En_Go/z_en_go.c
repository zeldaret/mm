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
#define THIS ((EnGo*)thisx)

#define ENGO_ROLLEDUP_Y_OFFSET 14.0f  // Actor shape offset in use when a goron is "rolled up".
#define ENGO_SNOWBALL_Y_OFFSET 46.0f  // Actor shape offset in use when a goron is in a snowball.
#define ENGO_NORMAL_SCALE 0.01f       // "Unit Scale" of a normal goron.
#define ENGO_BIGGORON_MULTIPLIER 5.0f // Scale factor for the Powder Keg Biggoron

#define ENGO_NORMAL_GRAVITY -1.0f

#define ENGO_POUND_RISE_VEL 10.0f // Velocity at which the Gatekeeper's pound surges into the air.
#define ENGO_POUND_FALL_VEL -6.0f // Velocity at which the Gatekeeper's pound surgest to the ground.

#define ENGO_DUST_STEAM_LIFETIME 16 // Lifetime in frames of the Dust and Steam effects

#define ENGO_LIMB_INDEX_HEAD 17
#define ENGO_LIMB_INDEX_BODY 10

typedef enum EnGoEyeTexture {
    /* 0 */ ENGO_EYETEX_OPEN,
    /* 1 */ ENGO_EYETEX_HALF,
    /* 2 */ ENGO_EYETEX_CLOSED,
    /* 3 */ ENGO_EYETEX_HALF2,
    /* 4 */ ENGO_EYETEX_CLOSED2,
} EnGoEyeTexture;

#define ENGO_FLAG_NONE 0
#define ENGO_FLAG_UNK0 (1 << 0)           // These three each
#define ENGO_FLAG_UNK1 (1 << 1)           // are equivalent to
#define ENGO_FLAG_UNK2 (1 << 2)           // A false ProcessTalkRequest
#define ENGO_FLAG_ENGAGED (1 << 3)        // 0x0008
#define ENGO_FLAG_FACE_TARGET (1 << 4)    // 0x0010
#define ENGO_FLAG_EYESOPEN (1 << 5)       // 0x0020
#define ENGO_FLAG_LOST_ATTENTION (1 << 6) // 0x0040
#define ENGO_FLAG_STANDINGMAYBE (1 << 7)  // 0x0080
#define ENGO_FLAG_SNOWBALLED (1 << 8)     // 0x0100
#define ENGO_FLAG_ROLLEDUP (1 << 9)       // 0x0200
#define ENGO_FLAG_FROZEN (1 << 10)        // 0x0400
#define ENGO_FLAG_HIT_OTHER (1 << 11)     // 0x0800
#define ENGO_FLAG_HIT_BY_OTHER (1 << 12)  // 0x1000
#define ENGO_FLAG_HIT_OBJ (1 << 13)       // 0x2000
#define ENGO_FLAG_CURLING (1 << 14)       // 0x4000
#define ENGO_FLAG_UNCURLING (1 << 15)     // 0x8000

typedef enum {
    ENGO_AWAKE = 0,
    ENGO_ASLEEP,
} EnGoSleepState;

void EnGo_Init(Actor* thisx, PlayState* play);
void EnGo_Destroy(Actor* thisx, PlayState* play);
void EnGo_Update(Actor* thisx, PlayState* play);

void EnGo_Setup(EnGo* this, PlayState* play);
void EnGo_Idle(EnGo* this, PlayState* play);
void EnGo_Sleep(EnGo* this, PlayState* play);
void EnGo_Frozen(EnGo* this, PlayState* play);
void EnGo_AwaitThaw(EnGo* this, PlayState* play);
void EnGo_Thaw(EnGo* this, PlayState* play);
void EnGo_Cutscene_ThawBrother(EnGo* this, PlayState* play);
void EnGo_Snowballing(EnGo* this, PlayState* play);
void EnGo_Talk(EnGo* this, PlayState* play);
void EnGo_Draw(Actor* thisx, PlayState* play);

#define WE_21_1_SPOKE_TO_GRAVEMAKER_AS_NONGORON (1 << 1)
#define WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON (1 << 2)
#define WE_21_3_THAWED_GRAVEMAKERS_BROTHER (1 << 3)

#if !defined(ENGO_MSGSCRIPT_READY)
// Goron with Frozen Brother
static s32 D_80A16100[] = {
    0x00150800, 0x40010022, 0x00150200, 0x180E0E10, 0x0C0F0E11, 0x0C0F0E12, 0x0C0F0E13, 0x0C0F0E14, 0x0C111502,
    0x100E0E15, 0x0C100015, 0x0400110E, 0x0E160C0F, 0x0E170C0F, 0x0E180C11, 0x15041610, 0x0E0E190C, 0x10001504,
    0x000D0100, 0x050E0E31, 0x0C100E0E, 0x2F0C1001, 0x00050E0E, 0x2D0C100E, 0x0E2B0C10,
};
#else
MsgScript D_80A16100[] = {
    /* 0x0000 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, WE_21_3_THAWED_GRAVEMAKERS_BROTHER, 0x0045 - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD01(0x002A - 0x0008), // Branch if Goron
    /* 0x0008 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, WE_21_1_SPOKE_TO_GRAVEMAKER_AS_NONGORON, 0x0025 - 0x000D),
    /* 0x000D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E10), // This is the grave where a Goron hero rests.
    /* 0x0010 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0011 0x03 */ MSCRIPT_CMD15(0x0E11), // I came here to put up the great hero's memorial... But the return route
                                             // has been blocked by snow, and I can't get back to Goron Village.
    /* 0x0014 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0015 0x03 */ MSCRIPT_CMD15(0x0E12), // And even worse, my borther has been frozen solid from the cold. The way
                                             // things are looking, I'll be frozen too.
    /* 0x0018 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0019 0x03 */ MSCRIPT_CMD15(0x0E13), // Ohhhh...It's times like these that make me wish i had taken some of the
                                             // hot spring water I found when I was digging the hero's grave.
    /* 0x001C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x001D 0x03 */ MSCRIPT_CMD15(0x0E14), // But the hot spring is now covered by the gravestone. I can't move a
                                             // gravestone that big by myself. But I guess this is what's meant by the
                                             // Goron saying, "There's no use in crying over split rocks."...Brrrrrr
    /* 0x0020 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0021 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(21, WE_21_1_SPOKE_TO_GRAVEMAKER_AS_NONGORON),
    /* 0x0024 0x01 */ MSCRIPT_DONE(),

    /* 0x0025 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E15), // H-h-hoo. If only I had water from the hot spring beneath the great
                                                  // hero's grave...then I could melt the ice off of my brother.
    /* 0x0028 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0029 0x01 */ MSCRIPT_DONE(),

    /* 0x002A 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON, 0x0040 - 0x002F),
    /* 0x002F 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E16), // Y-you're...No! No, you're not the great darmani, are you?
    /* 0x0032 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0033 0x03 */ MSCRIPT_CMD15(0x0E17), // Then...just whose grave was I making?
    /* 0x0036 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0037 0x03 */ MSCRIPT_CMD15(0x0E18), // Did you come back to life because it was so warm beneath your grave?
    /* 0x003A 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x003B 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(21, WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON),
    /* 0x003E 0x01 */ MSCRIPT_CMD22(),
    /* 0x003F 0x01 */ MSCRIPT_DONE(),

    /* 0x0040 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E19), // There used to be a hot spring bubbling beneath the great Darmani's
                                                  // grave. If I had some of that hot spring water, I might be able to
                                                  // thaw out my frozen brother.
    /* 0x0043 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0044 0x01 */ MSCRIPT_DONE(),

    /* 0x0045 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON, 0x0057 - 0x004A),
    /* 0x004A 0x03 */ MSCRIPT_CMD01(0x0052 - 0x004D), // Branch if Goron
    /* 0x004D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E31), // Thank you for saving my brother. But something has to be done about
                                                  // this cold. Otherwise, we'll be Goronsicles.
    /* 0x0050 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0051 0x01 */ MSCRIPT_DONE(),

    /* 0x0052 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E2F), // H-h-hooo.,..It's cold. This cold has me hallucinating about
                                                  // Darmani. I can't take it.
    /* 0x0055 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0056 0x01 */ MSCRIPT_DONE(),

    /* 0x0057 0x03 */ MSCRIPT_CMD01(0x005F - 0x005A), // Branch if Goron
    /* 0x005A 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E2D), // Do you know the great Darmani? He is the greatest hero of the Goron
                                                  // tribe. He is our last hope.
    /* 0x005D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x005E 0x01 */ MSCRIPT_DONE(),

    /* 0x005F 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E2B), // Great Darmani! Hurry! Please do something about the blizzard
                                                  // blowing in from Snow head.
    /* 0x0062 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0063 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Frozen Goron Brother Message Script
static s32 D_80A16164[] = {
    0x00150800, 0x7E01004D, 0x00150400, 0x180E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C12, 0x16111508,
    0x100E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C17, 0x0F0E260C, 0x180F0E27, 0x0C170F0E, 0x280C180F,
    0x0E290C17, 0x0F0E2A0C, 0x16111508, 0x100E0E1A, 0x0C170F0E, 0x1B0C180F, 0x0E1C0C0F, 0x0E1D0C0F, 0x0E1E0C17,
    0x0F0E1F0C, 0x180F0E20, 0x0C170F0E, 0x210C0F0E, 0x220C1611, 0x15081000, 0x1504000D, 0x0100050E, 0x0E320C10,
    0x0E0E300C, 0x10010005, 0x0E0E2E0C, 0x100E0E2C, 0x0C100000,
};
#else
MsgScript D_80A16164[] = {
    /* 0x0000 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, WE_21_3_THAWED_GRAVEMAKERS_BROTHER, 0x0083 - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD01(0x0055 - 0x0008), // Branch if Goron
    /* 0x0008 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, 0x04, 0x0025 - 0x000D),
    /* 0x000D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E1A), // Hunh? What have I been doing?
    /* 0x0010 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0011 0x01 */ MSCRIPT_CMD23(),
    /* 0x0012 0x03 */ MSCRIPT_CMD15(0x0E23), // Oh! Are you all right, brother? You were frozen and this person saved
                                             // you!
    /* 0x0015 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0016 0x01 */ MSCRIPT_CMD24(),
    /* 0x0017 0x03 */ MSCRIPT_CMD15(0x0E24), // Frozen?! I was?
    /* 0x001A 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x001B 0x03 */ MSCRIPT_CMD15(0x0E25), // Really? I don't know who you are, but thank you!
    /* 0x001E 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x001F 0x01 */ MSCRIPT_CMD18(),
    /* 0x0020 0x01 */ MSCRIPT_CMD22(),
    /* 0x0021 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(21, WE_21_3_THAWED_GRAVEMAKERS_BROTHER),
    /* 0x0024 0x01 */ MSCRIPT_DONE(),

    /* 0x0025 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E1A), // Hunh? What have I been doing?
    /* 0x0028 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0029 0x01 */ MSCRIPT_CMD23(),
    /* 0x002A 0x03 */ MSCRIPT_CMD15(0x0E23), // Oh! Are you all right, brother? You were frozen and this person saved
                                             // you!
    /* 0x002D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x002E 0x01 */ MSCRIPT_CMD24(),
    /* 0x002F 0x03 */ MSCRIPT_CMD15(0x0E24), // Frozen?! I was?
    /* 0x0032 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0033 0x03 */ MSCRIPT_CMD15(0x0E25), // Really? I don't know who you are, but thank you!
    /* 0x0036 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0037 0x01 */ MSCRIPT_CMD23(),
    /* 0x0038 0x03 */ MSCRIPT_CMD15(0x0E26), // But besides that, it turns out the greate Darmani is alive!
    /* 0x003B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x003C 0x01 */ MSCRIPT_CMD24(),
    /* 0x003D 0x03 */ MSCRIPT_CMD15(0x0E27), // What's this?
    /* 0x0040 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0041 0x01 */ MSCRIPT_CMD23(),
    /* 0x0042 0x03 */ MSCRIPT_CMD15(0x0E28), // I was shocked, too, but somehow, it seems the great darmani is not dead.
    /* 0x0045 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0046 0x01 */ MSCRIPT_CMD24(),
    /* 0x0047 0x03 */ MSCRIPT_CMD15(0x0E29), // Really? If that's true, then a glimmer of hope has appeared in Goron
                                             // Village
    /* 0x004A 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x004B 0x01 */ MSCRIPT_CMD23(),
    /* 0x004C 0x03 */ MSCRIPT_CMD15(0x0E2A), // It's true! Surely the great Darmani can do something about the blizard
                                             // that blows in from Snowhead
    /* 0x004F 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0050 0x01 */ MSCRIPT_CMD22(),
    /* 0x0051 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(21, WE_21_3_THAWED_GRAVEMAKERS_BROTHER),
    /* 0x0054 0x01 */ MSCRIPT_DONE(),

    /* 0x0055 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E1A), // Hunh? What have I been doing?
    /* 0x0058 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0059 0x01 */ MSCRIPT_CMD23(),
    /* 0x005A 0x03 */ MSCRIPT_CMD15(0x0E1B), // Oh! Are you all right, brother? You were frozen but the great Darmani
                                             // saved you!
    /* 0x005D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x005E 0x01 */ MSCRIPT_CMD24(),
    /* 0x005F 0x03 */ MSCRIPT_CMD15(0x0E1C), // The greate Darmani?! What's with you? Are you half asleep?
    /* 0x0062 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0063 0x03 */ MSCRIPT_CMD15(0x0E1D), // Did you hear this guy? The great Darmani died long ago and is lying in
                                             // his gr...
    /* 0x0066 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0067 0x03 */ MSCRIPT_CMD15(0x0E1E), // Heeee!!! Darmani!
    /* 0x006A 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x006B 0x01 */ MSCRIPT_CMD23(),
    /* 0x006C 0x03 */ MSCRIPT_CMD15(0x0E1F), // I was shocked, too But somehow, it seems the greate Darmani isn't dead.
    /* 0x006F 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0070 0x01 */ MSCRIPT_CMD24(),
    /* 0x0071 0x03 */ MSCRIPT_CMD15(0x0E20), // R-Really?
    /* 0x0074 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0075 0x01 */ MSCRIPT_CMD23(),
    /* 0x0076 0x03 */ MSCRIPT_CMD15(0x0E21), // With this, a star of hope appears in Goron Village
    /* 0x0079 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x007A 0x03 */ MSCRIPT_CMD15(0x0E22), // Great Darmani! Please do something about the blizzard blowing in from
                                             // Snowhead!
    /* 0x007D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x007E 0x01 */ MSCRIPT_CMD22(),
    /* 0x007F 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(21, WE_21_3_THAWED_GRAVEMAKERS_BROTHER),
    /* 0x0082 0x01 */ MSCRIPT_DONE(),

    /* 0x0083 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(21, WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON, 0x0095 - 0x0088),
    /* 0x0088 0x03 */ MSCRIPT_CMD01(0x0090 - 0x008B), // B if Goron
    /* 0x008B 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E32), // h-h-hoooo. It's cold. I wonder if we'll ever be able to return to
                                                  // Goron Village.
    /* 0x008E 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x008F 0x01 */ MSCRIPT_DONE(),

    /* 0x0090 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E30), // h-h-hooo. It's cold. This cold has me seeing Darmani's ghost.
                                                  // Y-Yikes. I th-think I'll go freeze again...
    /* 0x0093 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0094 0x01 */ MSCRIPT_DONE(),

    /* 0x0095 0x03 */ MSCRIPT_CMD01(0x009D - 0x0098), // B if Goron
    /* 0x0098 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E2E), // Have you seen the great Darmani? No one can withstand his punching
                                                  // and pounding.
    /* 0x009B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x009C 0x01 */ MSCRIPT_DONE(),

    /* 0x009D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E2C), // Great Darmani! Have you seen the Goron Elder yet? If you haven't
                                                  // you should go see him soon. I'm sure he'll be very happy.
    /* 0x00A0 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x00A1 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Store review Message Script
static s32 D_80A16208[2] = { 0xE0E520C, 0x10000000 };
#else
MsgScript D_80A16208[] = {
    /* 0x0000 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E52), // This store is having trouble getting product because of the cold.
                                                  // Things are kind of expensive now, so you shouldn't shop here...
    /* 0x0003 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0004 0x01 */ MSCRIPT_DONE(),
};
#endif

#define WE_22_2_GK_CALMED (1 << 2)
#define WE_22_4_TALKED_TO_ASIDE_ELDERSSON_AS_GORON (1 << 4)

#define WE_24_7_TALKED_TO_ASIDE_ELDERSSON_AS_ANY (1 << 7)

#if !defined(ENGO_MSGSCRIPT_READY)
// Elder's Gone, Son is Crying
static s32 D_80A16210[17] = {
    0x160400,  0x38010010, 0xE0E430C, 0xF0E440C, 0xF0E450C,  0x11188010, 0x160800,   0x1B0E0E46, 0xC0F0E47,
    0xC0F0E48, 0xC0F0E49,  0xC0F0E4A, 0xC111608, 0x11188010, 0xE0E4B0C,  0x100E0E42, 0xC100000,
};
#else

MsgScript D_80A16210[] = {
    /* 0x0000 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(22, WE_22_2_GK_CALMED, 0x003D - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD01(0x0018 - 0x0008), // B if Goron
    /* 0x0008 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E43),     // We're at our wits' end.
    /* 0x000B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000C 0x03 */ MSCRIPT_CMD15(0x0E44), // The elder went to Snowhead and doesn't seem to be coming back. Now his
                                             // son is so lonely that he won't stop crying.
    /* 0x000F 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0010 0x03 */ MSCRIPT_CMD15(0x0E45), // It keeps getting colder outside, and inside we're so cold we could
                                             // freeze.
    /* 0x0013 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0014 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(24, WE_24_7_TALKED_TO_ASIDE_ELDERSSON_AS_ANY),
    /* 0x0017 0x01 */ MSCRIPT_DONE(),

    /* 0x0018 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(22, WE_22_4_TALKED_TO_ASIDE_ELDERSSON_AS_GORON, 0x0038 - 0x001D),
    /* 0x001D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E46), // Those sideburns... Aren't you Darmani? You're supposed to be dead
                                                  // but you're alive? The Elder was troubled because he thought you
                                                  // were dead.
    /* 0x0020 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0021 0x03 */ MSCRIPT_CMD15(0x0E47), // I'm troubled, too.
    /* 0x0024 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0025 0x03 */ MSCRIPT_CMD15(0x0E48), // The Elder went to snowhead and hasn't come back, so now his son is so
                                             // lonely he won't stop crying.
    /* 0x0028 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0029 0x03 */ MSCRIPT_CMD15(0x0E49), // If you don't find the Goron Elder and ask him to come back. I'll never
                                             // be able to sleep.
    /* 0x002C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x002D 0x03 */ MSCRIPT_CMD15(0x0E4A), // And it just keeps getting colder outside. Even in here it is so cold
                                             // that we could freeze.
    /* 0x0030 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0031 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(22, WE_22_4_TALKED_TO_ASIDE_ELDERSSON_AS_GORON),
    /* 0x0034 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(24, WE_24_7_TALKED_TO_ASIDE_ELDERSSON_AS_ANY),
    /* 0x0037 0x01 */ MSCRIPT_DONE(),

    /* 0x0038 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E4B), // At his age, the Elder couldn't have gotten very far... I fear that
                                                  // he may have froze out there.
    /* 0x003B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x003C 0x01 */ MSCRIPT_DONE(),

    /* 0x003D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E42), // This is great. The Elder's sone has finally quit crying. Now we can
                                                  // sleep, too.
    /* 0x0040 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0041 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
#define WE_23_0_TALKED_TO_ASIDE_ELDERSROOM_AS_GORON (1 << 0)
// Outside Elder's room, Elder's gone, son is crying
static s32 D_80A16254[11] = {
    0x160400,   0x22010009, 0xE0E4D0C, 0xF0E4E0C,  0x10001701, 0xC0E0E,
    0x4F0C0F0E, 0x500C1117, 0x1100E0E, 0x510C100E, 0xE4C0C10,
};
#else
MsgScript D_80A16254[] = {
    /* 0x0000 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(ELDERS_SON, WE_22_2_GK_CALMED, 0x0027 - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD01(0x0011 - 0x0008), // B if Goron
    /* 0x0008 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E4D), // This is the room of the Goron Tribe's Elder. Do you have some kind
                                                  // of business with the Elder? Unfortunately, he's out.
    /* 0x000B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000C 0x03 */ MSCRIPT_CMD15(0x0E4E), // Since the Elder is gone, his sone won't stop crying, I wish someone
                                             // would do something.
    /* 0x000F 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0010 0x01 */ MSCRIPT_DONE(),

    /* 0x0011 0x05 */
    MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(23, WE_23_0_TALKED_TO_ASIDE_ELDERSROOM_AS_GORON, 0x0022 - 0x0016),
    /* 0x0016 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E4F), // Those sideburns. Aren't you darmani? You're supposed to be dead.
                                                  // But you're alive? What have you been doing?
    /* 0x0019 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x001A 0x03 */ MSCRIPT_CMD15(0x0E50), // Thinking you were dead, the Elder went to snowhead on his own. But for
                                             // now, please go see the elder's son. Hurry!
    /* 0x001D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x001E 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(23, WE_23_0_TALKED_TO_ASIDE_ELDERSROOM_AS_GORON),
    /* 0x0021 0x01 */ MSCRIPT_DONE(),

    /* 0x0022 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E51), // The Elder's sone is in there This crying is heartbreaking. Will it
                                                  // ever stop?
    /* 0x0025 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0026 0x01 */ MSCRIPT_DONE(),

    /* 0x0027 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E4C), // This is nice. The Elder's son has finally stopped crying. Now we
                                                  // can sleep, too.
    /* 0x002A 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x002B 0x01 */ MSCRIPT_DONE(),
};
#endif

#define WE_18_5_TALKED_TO_PKSELLER_AS_NONGORON (1 << 5)
#define WE_18_6_TALKED_TO_PKSELLER_AS_GORON (1 << 6)
#define WE_18_7_HAS_PK_PRIVLEDGES (1 << 7)

#define WE_19_0_STARTED_PKTEST (1 << 0)
#define WE_19_1_COMPLETED_PKTEST (1 << 1)

#if !defined(ENGO_MSGSCRIPT_READY)
// Powder Keg Goron Message Script
static s32 D_80A16280[52] = {
    0x1001200,  0x12200008, 0xE0C8E0C,  0x11122010, 0xE0C8F0C,  0x10001240, 0x1D0E0C,   0x800C1112, 0x40001280,
    0x742500,   0xC006F00,  0x13010045, 0xF0C810C,  0x19001300, 0x1280005E, 0x25000C00, 0x59001301, 0x2F0E0C,
    0x810C0F0C, 0x820C0500, 0x1A00,     0x1A300E0C, 0x830C1209, 0x700,      0xE0C84,    0x160C1113, 0x1100E0C,
    0x840C1031, 0xE0C850C,  0x1029FFF2, 0x130200,   0xF0E0C88,  0xC0F0C89,  0xC05000A,  0xFFE3FFE3, 0xE0C860C,
    0x11128019, 0x213019,   0xFFC02900, 0x2C0E0C8C, 0xC050000,  0x50000,    0x8006400,  0x6320E0C,  0x8D0C1030,
    0x14FF9C12, 0x6003400,  0x130034,   0x700000E,  0xC870C16,  0x100E0C8B, 0xC100000,
};
#else
MsgScript D_80A16280[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD01(0x0015 - 0x0003), // B if Goron
    /* 0x0003 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(18, WE_18_5_TALKED_TO_PKSELLER_AS_NONGORON, 0x0010 - 0x0008),
    /* 0x0008 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C8E), // I'm the Goron who sells Poweder Kegs, the most famous product of
                                                  // the Gorons. But the rules say I can't sell Powder Kegs to anyone
                                                  // who isn't a Goron, Sorry
    /* 0x000B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000C 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(18, WE_18_5_TALKED_TO_PKSELLER_AS_NONGORON),
    /* 0x000F 0x01 */ MSCRIPT_DONE(),

    /* 0x0010 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C8F), // The rules say I can't sell Powder Kegs to anyone who isn't a Goron.
                                                  // Sorry.
    /* 0x0013 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0014 0x01 */ MSCRIPT_DONE(),

    /* 0x0015 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(18, WE_18_6_TALKED_TO_PKSELLER_AS_GORON, 0x0037 - 0x001A),
    /* 0x001A 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C80), // I'm the Goron who sells the Powder Keg, the most famous product of
                                                  // the Gorons.
    /* 0x001D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x001E 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(18, WE_18_6_TALKED_TO_PKSELLER_AS_GORON),
    /* 0x0021 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(18, WE_18_7_HAS_PK_PRIVLEDGES, 0x009A - 0x0026),
    /* 0x0026 0x05 */ MSCRIPT_BRANCH_ON_ITEM(ITEM_POWDER_KEG, 0x009A - 0x002B),
    /* 0x002B 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(19, WE_19_0_STARTED_PKTEST, 0x0075 - 0x0030),
    /* 0x0030 0x03 */ MSCRIPT_CMD15(0x0C81), // Want a Powder Keg? Powder Kegs explode with powerful blasts and are very
                                             // dangerous. Until I have tested you to see if you can use them properly,
                                             // I can't let you use any on your own.
    /* 0x0033 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0034 0x03 */ MSCRIPT_BRANCH(0x004A - 0x0037),
    /* 0x0037 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(18, WE_18_7_HAS_PK_PRIVLEDGES, 0x009A - 0x003C),
    /* 0x003C 0x05 */ MSCRIPT_BRANCH_ON_ITEM(ITEM_POWDER_KEG, 0x009A - 0x0041),
    /* 0x0041 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(19, WE_19_0_STARTED_PKTEST, 0x0075 - 0x0046),
    /* 0x0046 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C81), // Want a Powder Keg? Powder Kegs explode with powerful blasts and are
                                                  // very dangerous. Until I have tested you to see if you can use them
                                                  // properly, I can't let you use any on your own.
    /* 0x0049 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x004A 0x03 */ MSCRIPT_CMD15(0x0C82), // Will you give it a try? [Yes/No]
    /* 0x004D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x004E 0x07 */ MSCRIPT_BRANCH_ON_CHOICE(0x0, 0x006F - 0x0055, 0x006F - 0x0055),
    /* 0x0055 0x01 */ MSCRIPT_PLAYSFX_DECIDE(),
    /* 0x0056 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C83), // If you can destroy the boulder that blocks the entrance to the
                                                  // Goron Racetrack near here using the powder keg I'm about to give
                                                  // you, then I'll approve you to carry them.
    /* 0x0059 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x005A 0x01 */ MSCRIPT_CMD18(),
    /* 0x005B 0x03 */ MSCRIPT_BRANCH_ON_CALLBACK(0x0),
    /* 0x005E 0x03 */ MSCRIPT_CMD07(0x0),
    /* 0x0061 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C84), // When the Powder Keg beings ticking faster, it means that it's about
                                                  // to explode. Try to blow up the boulder blocking the goron racetrack
                                                  // entrance without the powder keg exploding on the way. There's a
                                                  // sign near the racetrack, so keep an eye out for it. When you've
                                                  // finished, come see me.
    /* 0x0064 0x01 */ MSCRIPT_CMD22(),
    /* 0x0065 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0066 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(19, WE_19_0_STARTED_PKTEST),
    /* 0x0069 0x01 */ MSCRIPT_DONE(),

    /* 0x006A 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C84), // When the Powder Keg beings ticking faster, it means that it's about
                                                  // to explode. Try to blow up the boulder blocking the goron racetrack
                                                  // entrance without the powder keg exploding on the way. There's a
                                                  // sign near the racetrack, so keep an eye out for it. When you've
                                                  // finished, come see me.
    /* 0x006D 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x006E 0x01 */ MSCRIPT_DONE(),

    /* 0x006F 0x01 */ MSCRIPT_PLAYSFX_CANCEL(),
    /* 0x0070 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C85), // Come back if you change your mind.
    /* 0x0073 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0074 0x01 */ MSCRIPT_DONE(),

    /* 0x0075 0x03 */ MSCRIPT_BRANCH_ON_PKAMMO(0x006A - 0x0078),

    /* 0x0078 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(19, WE_19_1_COMPLETED_PKTEST, 0x008C - 0x007D),
    /* 0x007D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C88), // You vailed? In that case, I can't approve you to use Powder Kegs.
    /* 0x0080 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0081 0x03 */ MSCRIPT_CMD15(0x0C89), // Will you take the challenge again? [Yes/No]
    /* 0x0084 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0085 0x07 */ MSCRIPT_BRANCH_ON_CHOICE(0x0096 - 0x008C, 0x006F - 0x008C, 0x006F - 0x008C),

    /* 0x008C 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C86), // It looks like you managed to succeed! Knowing your skills, I feel
                                                  // fine letting you handle Powder Kegs on your own. It was bad of me
                                                  // to put you through such a dangerous test. I wanted you to take this
                                                  // as  my apology.
    /* 0x008F 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0090 0x03 */ MSCRIPT_WEEK_EVENT_REG_SET(18, WE_18_7_HAS_PK_PRIVLEDGES),
    /* 0x0093 0x03 */ MSCRIPT_BRANCH(0x00B7 - 0x0096),
    /* 0x0096 0x01 */ MSCRIPT_PLAYSFX_DECIDE(),
    /* 0x0097 0x03 */ MSCRIPT_BRANCH(0x005A - 0x009A),

    /* 0x009A 0x03 */ MSCRIPT_BRANCH_ON_PKAMMO(0x00C9 - 0x009D),
    /* 0x009D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C8C), // Will you buy a powder keg for 100 rupees? [I'll buy it/No thanks]
    /* 0x00A0 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x00A1 0x07 */ MSCRIPT_BRANCH_ON_CHOICE(0x0, 0x00AD - 0x00A8, 0x0),
    /* 0x00A8 0x05 */ MSCRIPT_BRANCH_ON_RUPEES(100, 0x00B3 - 0x00AD),
    /* 0x00AD 0x01 */ MSCRIPT_PLAYSFX_ERR(),
    /* 0x00AE 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C8D), // If you change your mind, see me.
    /* 0x00B1 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x00B2 0x01 */ MSCRIPT_DONE(),

    /* 0x00B3 0x01 */ MSCRIPT_PLAYSFX_DECIDE(),
    /* 0x00B4 0x03 */ MSCRIPT_CMD20(0xFF9C),
    /* 0x00B7 0x01 */ MSCRIPT_CMD18(),
    /* 0x00B8 0x05 */ MSCRIPT_CMD06(0x0034, 0x0),
    /* 0x00BD 0x03 */ MSCRIPT_COLLECT_SET(0x0034),
    /* 0x00C0 0x03 */ MSCRIPT_CMD07(0x0),
    /* 0x00C3 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C87), // Powder Kegs are very volatile, so you can can carry only one at a
                                                  // time. If you shoot them with an arrow, they'll explode as soon as
                                                  // they're hit, so be careful.
    /* 0x00C6 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x00C7 0x01 */ MSCRIPT_CMD22(),
    /* 0x00C8 0x01 */ MSCRIPT_DONE(),

    /* 0x00C9 0x03 */ MSCRIPT_BEGIN_TEXT(0x0C8B), // You can carry only one Powder Keg at a time. Once you've used it,
                                                  // come back.
    /* 0x00CC 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x00CD 0x01 */ MSCRIPT_DONE(),
};
#endif

#define WE_88_6_GATEKEEPER_OPENED_SHRINE (1 << 6)
#define WE_88_7_GATEKEEPER_OPENED_SHRINE_FOR_HUMAN (1 << 7)

#define WE_89_0_GATEKEEPER_OPENED_SHRINE_FOR_DEKU (1 << 0)
#define WE_89_1_GATEKEEPER_OPENED_SHRINE_FOR_ZORA (1 << 1)
#define WE_89_2_GATEKEEPER_OPENED_SHRINE_FOR_GORON (1 << 2)

#if !defined(ENGO_MSGSCRIPT_READY)
// Goron Gatekeeper
static s32 D_80A16350[27] = {
    0x584000,  0x2903000E, 0x2001301, 0x180058,   0x80005119, 0x1E0059,   0x1004919, 0x160059,  0x2004119,
    0xE0059,   0x4003919,  0x2F0E0D,  0x4D0C1210, 0xE0D480C,  0xF0D490C,  0xF0D4A0C, 0x5000000, 0xF000F30,
    0xE0D4B0C, 0x15090000, 0xE0D4D0C, 0x1210310E, 0xD4C0C12,  0x100E0D4E, 0xC19FFD8, 0xE0D4F0C, 0x19FFD500,
};
#else
MsgScript D_80A16350[] = {
    /* 0x0000 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(88, WE_88_6_GATEKEEPER_OPENED_SHRINE, 0x002E - 0x0005),
    /* 0x0005 0x03 */ MSCRIPT_CMD03(0x0016 - 0x0008), // B if Deku
    /* 0x0008 0x03 */ MSCRIPT_CMD02(0x001E - 0x000B), // B if Zora
    /* 0x000B 0x03 */ MSCRIPT_CMD01(0x0026 - 0x000E), // B if Goron
    /* 0x000E 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(88, WE_88_7_GATEKEEPER_OPENED_SHRINE_FOR_HUMAN, 0x0064 - 0x0013),
    /* 0x0013 0x03 */ MSCRIPT_BRANCH(0x0034 - 0x0016),
    /* 0x0016 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(89, WE_89_0_GATEKEEPER_OPENED_SHRINE_FOR_DEKU, 0x0064 - 0x001B),
    /* 0x001B 0x03 */ MSCRIPT_BRANCH(0x0034 - 0x001E),
    /* 0x001E 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(89, WE_89_1_GATEKEEPER_OPENED_SHRINE_FOR_ZORA, 0x0064 - 0x0023),
    /* 0x0023 0x03 */ MSCRIPT_BRANCH(0x0034 - 0x0026),
    /* 0x0026 0x05 */ MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(89, WE_89_2_GATEKEEPER_OPENED_SHRINE_FOR_GORON, 0x0064 - 0x002B),
    /* 0x002B 0x03 */ MSCRIPT_BRANCH(0x005D - 0x002E),
    /* 0x002E 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D4D), // The door's already open. I'm going to close it right away, so hurry
                                                  // up!
    /* 0x0031 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0032 0x01 */ MSCRIPT_CMD18(),
    /* 0x0033 0x01 */ MSCRIPT_DONE(),

    /* 0x0034 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D48), // It's cold...
    /* 0x0037 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0038 0x03 */ MSCRIPT_CMD15(0x0D49), // Being the gatekeeper in this cold is h-h-hard.
    /* 0x003B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x003C 0x03 */ MSCRIPT_CMD15(0x0D4A), // Do you want to enter the Goron Shrine? [Yes/No]
    /* 0x003F 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0040 0x07 */ MSCRIPT_BRANCH_ON_CHOICE(0x0, 0x0056 - 0x0047, 0x0056 - 0x0047),
    /* 0x0047 0x01 */ MSCRIPT_PLAYSFX_DECIDE(),
    /* 0x0048 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D4B), // Then I'll open the door with a Goron Pound. I'm going to close it
                                                  // right away so it doesn't get cold inside, so hurry up and get in.
                                                  // Are you ready?
    /* 0x004B 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x004C 0x01 */ MSCRIPT_CMD21(),
    /* 0x004D 0x03 */ MSCRIPT_BRANCH_ON_CALLBACK(0x0),
    /* 0x0050 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D4D), // The door's already open. I'm going to close it right away, so hurry
                                                  // up!
    /* 0x0053 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0054 0x01 */ MSCRIPT_CMD18(),
    /* 0x0055 0x01 */ MSCRIPT_DONE(),

    /* 0x0056 0x01 */ MSCRIPT_PLAYSFX_CANCEL(),
    /* 0x0057 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D4C), // Are you sure? It's a little bit warmer inside. Ohhh, I want to go
                                                  // in, too.
    /* 0x005A 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x005B 0x01 */ MSCRIPT_CMD18(),
    /* 0x005C 0x01 */ MSCRIPT_DONE(),

    /* 0x005D 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D4E), // You're Darmani! How? You're alive?
    /* 0x0060 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0061 0x03 */ MSCRIPT_BRANCH(0x003C - 0x0064),

    /* 0x0064 0x03 */ MSCRIPT_BEGIN_TEXT(0x0D4F), // Do you want me to open it again? [Yes/No]
    /* 0x0067 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0068 0x03 */ MSCRIPT_BRANCH(0x0040 - 0x006B),
};
#endif
// clang-format off

// Side to Side squatting Goron Racer
static s32 D_80A163BC[4] = { 0x100060E, 0xDFE0C12, 0x100E0DFF, 0xC121000 };
// MsgScript D_80A163BC[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),   // B if Goron
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0DFE),       // It's spring! It's spring! I can't sit still any longer!
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0DFF),       // Darmani! Are you ready? I'm rarin' to go!
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// MsgScript
static s32 D_80A163CC[4] = { 0x100060E, 0xE000C12, 0x100E0E01, 0xC121000 };
// MsgScript D_80A163CC[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E00),     // (From Japanese: Haru Goro Haru Goro! Goro, the body starts to move naturally)
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E01),     // (From Japanese: Darmani, This year, I will win the ground ball.)
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// Limb Shaking Goron Racer
static s32 D_80A163DC[4] = { 0x100060E, 0xE020C12, 0x100E0E03, 0xC121000 };
// MsgScript D_80A163DC[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E02),     // Sprint has finally com! I have been waiting for this moment.
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E03),     // This year is my debut at the races...Please go easy on me
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// Side Stretching Goron Racer
static s32 D_80A163EC[4] = { 0x100060E, 0xE040C12, 0x100E0E05, 0xC121000 };
// MsgScript D_80A163EC[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),   // B if Goron
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E04),       // Since it has warmed up... my spirits have lifted!
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E05),       // This year, I'm feeling a little different...
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// Hamstring Stretch Helper (Standing)
static s32 D_80A163FC[4] = { 0x100060E, 0xE060C12, 0x100E0E07, 0xC121000 };
// MsgScript D_80A163FC[] = {
// /* 0x0000 0x03 */  MSCRIPT_CMD01(0x0009 - 0x0003),   // B if Goron
// /* 0x0003 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E06),       // Watch my race!
// /* 0x0006 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0007 0x01 */  MSCRIPT_CMD18(),
// /* 0x0008 0x01 */  MSCRIPT_DONE(),

// /* 0x0009 0x03 */  MSCRIPT_BEGIN_TEXT(0x0E07),       // Darmani! Are you entering after all? ...Iguess I'll be last again.
// /* 0x000C 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x000D 0x01 */  MSCRIPT_CMD18(),
// /* 0x000E 0x01 */  MSCRIPT_DONE(),
// };

// Lullaby Hint
static s32 D_80A1640C[2] = { 0xE023A0C, 0x12100000 };
// MsgScript D_80A1640C[] = {
// /* 0x0000 0x03 */  MSCRIPT_BEGIN_TEXT(0x023A), // Aha! So the Gorons fall asleep if they hear the Goron's Lullaby!
                                                  // That's convenient...
// /* 0x0003 0x01 */  MSCRIPT_AWAIT_TEXT(),
// /* 0x0004 0x01 */  MSCRIPT_CMD18(),
// /* 0x0005 0x01 */  MSCRIPT_DONE(),
// };
// clang-format on

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

// Frozen Collider Cylinder
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

// Normal Collider Cylinder
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

typedef enum {
    /* 0x0 */ ENGO_DMGEFF_NONE,
    /* 0x1 */ ENGO_DMGEFF_FIRE = 0x2,
    /* 0xF */ ENGO_DMGEFF_BREAK = 0xF,
} EnGoDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Goron punch    */ DMG_ENTRY(1, ENGO_DMGEFF_BREAK),
    /* Sword          */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, ENGO_DMGEFF_BREAK),
    /* Fire arrow     */ DMG_ENTRY(1, ENGO_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Light arrow    */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Goron spikes   */ DMG_ENTRY(1, ENGO_DMGEFF_BREAK),
    /* Deku spin      */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Normal shield  */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, ENGO_DMGEFF_NONE),
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

// Initialize the 2nd Half of the effect objects to be Steam.
EnGoEffect* EnGo_VfxInit_Steam(EnGoEffect* pEffect, Vec3f position, Vec3f acceleration, Vec3f velocity, f32 scale,
                               f32 deltaScale, s32 maxFrames) {
    s32 i;

    for (i = (ENGO_NUM_EFFECTS / 2); i < ENGO_NUM_EFFECTS; i++, pEffect++) {
        if (pEffect->effectType != ENGO_EFFECT_NONE)
            continue;

        pEffect->effectType = ENGO_EFFECT_STEAM;
        pEffect->alphaDenom = (Rand_ZeroOne() * (2.0f * (maxFrames / 3.0f))) + (maxFrames / 3.0f);
        pEffect->alphaNumer = pEffect->alphaDenom;
        pEffect->position = position;
        pEffect->acceleration = acceleration;
        pEffect->velocity = velocity;
        pEffect->scaleXY = scale;
        pEffect->scaleXYDelta = deltaScale;
        break;
    }
    return pEffect;
}

// Draw all Steam Effects
void EnGo_DrawSteam(EnGoEffect* pEffect, PlayState* play2) {
    PlayState* play = play2;
    s32 i;
    s32 flag = false;
    f32 temp;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < ENGO_NUM_EFFECTS; i++, pEffect++) {
        if (pEffect->effectType != ENGO_EFFECT_STEAM)
            continue;

        gDPPipeSync(POLY_XLU_DISP++);
        if (!flag) {
            gSPDisplayList(POLY_XLU_DISP++, gGoronSteamMaterialDL);
            flag = true;
        }

        Matrix_Push();

        temp = ((f32)pEffect->alphaNumer / pEffect->alphaDenom);
        temp *= UINT8_MAX;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, (u8)temp);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, (pEffect->alphaNumer + (i * 3)) * 3,
                                    (pEffect->alphaNumer + (i * 3)) * 15, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));

        Matrix_Translate(pEffect->position.x, pEffect->position.y, pEffect->position.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(pEffect->scaleXY, pEffect->scaleXY, 1.0f, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGoronSteamModelDL);

        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

// Initialize the 2nd Half of the effect objects to be Dust.
void EnGo_VfxInit_Dust(EnGoEffect* pEffect, Vec3f pos, Vec3f accel, Vec3f vel, f32 scale, f32 deltaScale, s32 maxFrames,
                       s32 parentVfxType) {
    s32 i;

    for (i = (ENGO_NUM_EFFECTS / 2); i < ENGO_NUM_EFFECTS; i++, pEffect++) {
        if (pEffect->effectType != ENGO_EFFECT_NONE)
            continue;

        pEffect->effectType = parentVfxType + ENGO_EFFECT_DUST_START;
        pEffect->alphaDenom = (Rand_ZeroOne() * (2.0f * (maxFrames / 3.0f))) + (maxFrames / 3.0f);
        pEffect->alphaNumer = pEffect->alphaDenom;
        pEffect->position = pos;
        pEffect->acceleration = accel;
        pEffect->velocity = vel;
        pEffect->scaleXY = scale;
        pEffect->scaleXYDelta = deltaScale;
        break;
    }
}

// Draw all Dust Effects
void EnGo_DrawDust(EnGoEffect* pEffect, PlayState* play2) {
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
    u8 isMaterialSet = false;
    f32 alpha;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < ENGO_NUM_EFFECTS; i++, pEffect++) {
        if ((pEffect->effectType < ENGO_EFFECT_DUST_START) || (pEffect->effectType >= ENGO_EFFECT_STEAM_START))
            continue;

        if (!isMaterialSet) {
            POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0);
            gSPDisplayList(POLY_XLU_DISP++, gGoronDustMaterialDL);
            isMaterialSet = true;
        }

        Matrix_Push();

        alpha = (f32)pEffect->alphaNumer / pEffect->alphaDenom;
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, sEnGoDustColorPrim[(s32)pEffect->effectType - ENGO_EFFECT_DUST_START].r,
                        sEnGoDustColorPrim[(s32)pEffect->effectType - ENGO_EFFECT_DUST_START].g,
                        sEnGoDustColorPrim[(s32)pEffect->effectType - ENGO_EFFECT_DUST_START].b,
                        (u8)(alpha * UINT8_MAX));
        gDPSetEnvColor(POLY_XLU_DISP++, sEnGoDustColorEnv[(s32)pEffect->effectType - ENGO_EFFECT_DUST_START].r,
                       sEnGoDustColorEnv[(s32)pEffect->effectType - ENGO_EFFECT_DUST_START].g,
                       sEnGoDustColorEnv[(s32)pEffect->effectType - ENGO_EFFECT_DUST_START].b, 0);

        Matrix_Translate(pEffect->position.x, pEffect->position.y, pEffect->position.z, MTXMODE_NEW);
        Matrix_Scale(pEffect->scaleXY, pEffect->scaleXY, 1.0f, MTXMODE_APPLY);
        Matrix_ReplaceRotation(&play->billboardMtxF);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sEnGoDustTexturePtrs[(s32)(alpha * 7.0f)]));
        gSPDisplayList(POLY_XLU_DISP++, gGoronDustModelDL);

        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

/* Called after Snowball broken sound effect, before goron cold */
void EnGo_VfxSnowballBreak(EnGoEffect* pEffect, Vec3f worldPos) {
    static u8 D_80A1667C[] = {
        ENGO_EFFECT_SNOW3, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW2, //
        ENGO_EFFECT_SNOW3, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW2, //
        ENGO_EFFECT_SNOW3, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW2, //
        ENGO_EFFECT_SNOW3, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW1, ENGO_EFFECT_SNOW2, //
    };

    EnGoEffect* pEnd = &pEffect[ENGO_NUM_EFFECTS / 2];
    s32 i;
    Vec3f randRelativeToWorldPos;
    Vec3f randYOneToFour;
    f32 temp_fs0;

    for (i = 0; i < (ENGO_NUM_EFFECTS / 2); i++, pEffect++) {
        if (pEffect->effectType != ENGO_EFFECT_NONE)
            continue;

        pEffect->position = worldPos;
        pEffect->position.y += 56.0f;

        // Generate a +-15 degree rotational velocity
        pEffect->rotVelocity.x = (Rand_ZeroOne() - 0.5f) * (f32)0x1554; /* 30 degrees */
        pEffect->rotVelocity.y = (Rand_ZeroOne() - 0.5f) * (f32)0x1554; /* 30 degrees */
        pEffect->rotVelocity.z = (Rand_ZeroOne() - 0.5f) * (f32)0x1554; /* 30 degrees */

        // Generate a radially outward velocity for each of the Effects
        temp_fs0 = (Rand_ZeroOne() * 4.0f) + 6.0f;
        pEffect->velocity.x = Math_SinS(i * (0x10000 / (ENGO_NUM_EFFECTS / 2))) * temp_fs0;
        pEffect->velocity.z = Math_CosS(i * (0x10000 / (ENGO_NUM_EFFECTS / 2))) * temp_fs0;
        pEffect->velocity.y = (Rand_ZeroOne() * 3.0f) + 6.0f;

        // No acceleration on the X,Z axis, Negative acceleration on the Y axis
        pEffect->acceleration = gZeroVec3f;
        pEffect->acceleration.y = -0.8f;

        // Full visibility (1/1)
        pEffect->alphaDenom = pEffect->alphaNumer = 1;

        // Assign a value of 1, 2, or 3
        pEffect->effectType = D_80A1667C[i];

        // Initialize the parameters for the paired element
        randRelativeToWorldPos.x = ((Rand_ZeroOne() - 0.5f) * 80.0f) + pEffect->position.x;
        randRelativeToWorldPos.y = ((Rand_ZeroOne() - 0.5f) * 40.0f) + pEffect->position.y;
        randRelativeToWorldPos.z = ((Rand_ZeroOne() - 0.5f) * 80.0f) + pEffect->position.z;

        randYOneToFour = gZeroVec3f;
        randYOneToFour.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

        // Initialize the paired element.
        EnGo_VfxInit_Dust(pEnd, randRelativeToWorldPos, gZeroVec3f, randYOneToFour, 0.6f, 0.2f,
                          ENGO_DUST_STEAM_LIFETIME, 0);
    }
}

void EnGo_UpdateEffect_Snow(EnGoEffect* pEffect, f32 arg1) {
    f32 test;
    f32 test2;
    f32 x;
    f32 z;

    pEffect->position.x += pEffect->velocity.x;
    pEffect->position.y += pEffect->velocity.y;
    pEffect->position.z += pEffect->velocity.z;

    pEffect->velocity.y += pEffect->acceleration.y;
    pEffect->scaleXY += pEffect->scaleXYDelta;

    if (pEffect->position.y < arg1) {
        pEffect->position.y = arg1;

        pEffect->effectType = ENGO_EFFECT_DUST1;
        pEffect->alphaDenom = (Rand_ZeroOne() * 8.0f) + 4.0f;
        pEffect->alphaNumer = pEffect->alphaDenom;

        pEffect->velocity = gZeroVec3f;
        pEffect->velocity.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

        pEffect->scaleXY = 0.4f;
        pEffect->scaleXYDelta = 0.1f;
        return;
    }

    if (pEffect->velocity.x != 0.0f) {
        x = pEffect->velocity.x / fabsf(pEffect->velocity.x);
        x *= ((sREG(13) + 140) * 0.01f);
        Math_StepToF(&pEffect->velocity.x, x, (sREG(14) + 40) * 0.01f);
    }

    if (pEffect->velocity.z != 0.0f) {
        z = pEffect->velocity.z / fabsf(pEffect->velocity.z);
        z *= ((sREG(13) + 140) * 0.01f);
        Math_StepToF(&pEffect->velocity.z, z, (sREG(14) + 40) * 0.01f);
    }

    pEffect->rotAngle.x += pEffect->rotVelocity.x;
    pEffect->rotAngle.y += pEffect->rotVelocity.y;
    pEffect->rotAngle.z += pEffect->rotVelocity.z;
}

// Draw snowball (1, 2, or 3)
void EnGo_DrawSnow(EnGoEffect* pEffect, PlayState* play, Gfx* material, Gfx* model, u8 effectType) {
    s32 i;
    u8 isMaterialSet = false;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    for (i = 0; i < (ENGO_NUM_EFFECTS / 2); i++, pEffect++) {
        if (pEffect->effectType != effectType)
            continue;

        if (!isMaterialSet) {
            gSPDisplayList(POLY_OPA_DISP++, material);
            isMaterialSet = true;
        }

        Matrix_Push();
        Matrix_Translate(pEffect->position.x, pEffect->position.y, pEffect->position.z, MTXMODE_NEW);
        Matrix_Scale(0.08f, 0.08f, 0.08f, MTXMODE_APPLY);
        Matrix_RotateZS(pEffect->rotAngle.z, MTXMODE_APPLY);
        Matrix_RotateXS(pEffect->rotAngle.x, MTXMODE_APPLY);
        Matrix_RotateYS(pEffect->rotAngle.y, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, model);

        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

// Update the effect, changing its position and potentially fading it away.
void EnGo_UpdateEffects(EnGo* this) {
    EnGoEffect* pEffect = this->effectTable;
    s32 i;

    for (i = 0; i < ENGO_NUM_EFFECTS; i++, pEffect++) {
        if (pEffect->effectType == ENGO_EFFECT_NONE)
            continue;

        if (pEffect->alphaNumer == 0) {
            // "Delete" the effect by assigning its type to None.
            pEffect->effectType = ENGO_EFFECT_NONE;
        } else if ((pEffect->effectType > ENGO_EFFECT_NONE) && (pEffect->effectType < ENGO_EFFECT_DUST_START)) {
            // Snow rotates, and changes to dust upon dropping below the actor position
            EnGo_UpdateEffect_Snow(pEffect, this->actor.world.pos.y);
        } else {
            // Dust and Steam move according to their initial values.
            pEffect->position.x += pEffect->velocity.x;
            pEffect->position.y += pEffect->velocity.y;
            pEffect->position.z += pEffect->velocity.z;

            pEffect->velocity.x += pEffect->acceleration.x;
            pEffect->velocity.y += pEffect->acceleration.y;
            pEffect->velocity.z += pEffect->acceleration.z;

            pEffect->scaleXY += pEffect->scaleXYDelta;
            pEffect->alphaNumer--;
        }
    }
}

// Draw all Effects
void EnGo_DrawEffects(EnGo* this, PlayState* play) {
    EnGo_DrawSnow(this->effectTable, play, gGoronLargeSnowballFragmentMaterialDL, gGoronLargeSnowballFragmentModelDL,
                  ENGO_EFFECT_SNOW1);
    EnGo_DrawSnow(this->effectTable, play, gGoronMediumSnowballFragmentMaterialDL, gGoronMediumSnowballFragmentModelDL,
                  ENGO_EFFECT_SNOW2);
    EnGo_DrawSnow(this->effectTable, play, gGoronSmallSnowballFragmentMaterialDL, gGoronSmallSnowballFragmentModelDL,
                  ENGO_EFFECT_SNOW3);
    EnGo_DrawSteam(this->effectTable, play);
    EnGo_DrawDust(this->effectTable, play);
}

/**
 * Check if the Goron can hurt the player.
 */
s32 EnGo_RollingSnowballCanHurtPlayer(PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((player->transformation == PLAYER_FORM_GORON) && (player->stateFlags3 & 0x2000000)) {
        return false;
    }
    return true;
}

/**
 * Check if the Goron is being put to sleep.
 */
s32 EnGo_IsEnteringSleep(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 isEnteringSleep = false;

    if (((player->transformation == PLAYER_FORM_GORON) && (play->msgCtx.ocarinaMode == 3) &&
         (play->msgCtx.lastPlayedSong == OCARINA_SONG_GORON_LULLABY) && (this->sleepState == ENGO_AWAKE) &&
         (this->actor.xzDistToPlayer < 400.0f)) ||
        (!(gSaveContext.save.weekEventReg[22] & WE_22_2_GK_CALMED) && (play->sceneNum == SCENE_16GORON_HOUSE) &&
         (gSaveContext.sceneSetupIndex == 0) && (this->sleepState == ENGO_AWAKE) &&
         (play->csCtx.currentCsIndex == 1))) {
        isEnteringSleep = true;
    }
    return isEnteringSleep;
}

s32 func_80A122EC(EnGo* this) {
    static Vec3f sPowderKegSellerPos = { 0.0f, 100.0f, 160.0f };
    s32 pad;
    f32 yAxisOffset = 58.0f;

    if (ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &sPowderKegSellerPos,
                                      &this->actor.focus.pos);
    } else {
        if ((this->actionFlags & ENGO_FLAG_ROLLEDUP) || (this->actionFlags & ENGO_FLAG_SNOWBALLED)) {
            yAxisOffset = this->actor.shape.yOffset;
        }
        Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
        this->actor.focus.pos.y += yAxisOffset;
    }

    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
    return false;
}

/**
 * @brief Collider setup for the Rolling Snowball Goron
 *
 * @param this
 * @param play
 */
void EnGo_UpdateCollider_RollingSnowball(EnGo* this, PlayState* play) {
    Vec3f worldPos;

    Math_Vec3f_Copy(&worldPos, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = worldPos.x;
    this->colliderSphere.dim.worldSphere.center.y = worldPos.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = worldPos.z;

    this->colliderSphere.dim.modelSphere.radius = 48;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    if (EnGo_RollingSnowballCanHurtPlayer(play)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->colliderSphere.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderSphere.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void EnGo_UpdateCollider_PowderKegSeller(EnGo* this, PlayState* play) {
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void EnGo_UpdateCollider_Curled(EnGo* this, PlayState* play) {
    Vec3f worldPos;

    Math_Vec3f_Copy(&worldPos, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = worldPos.x;
    this->colliderSphere.dim.worldSphere.center.y = worldPos.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = worldPos.z;

    this->colliderSphere.dim.modelSphere.radius = 20;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

void EnGo_UpdateCollider_Frozen(EnGo* this, PlayState* play) {
    s32 pad;

    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);

    this->colliderCylinder.dim.radius = 46;
    this->colliderCylinder.dim.height = 78;

    if (this->harmlessTimer == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->colliderCylinder.base);
    }
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderCylinder.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
}

void EnGo_UpdateCollider_Default(EnGo* this, PlayState* play) {
    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);
    this->colliderCylinder.dim.radius = 24;
    this->colliderCylinder.dim.height = 62;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
}

void EnGo_UpdateCollider(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags2 & ENGO_FLAG_CURLING)) {
        DECR(this->harmlessTimer);
    }

    if (ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) {
        EnGo_UpdateCollider_PowderKegSeller(this, play);
    } else if (this->actionFlags & ENGO_FLAG_SNOWBALLED) {
        EnGo_UpdateCollider_RollingSnowball(this, play);
    } else if (this->actionFlags & ENGO_FLAG_ROLLEDUP) {
        EnGo_UpdateCollider_Curled(this, play);
    } else if (this->actionFlags & ENGO_FLAG_FROZEN) {
        EnGo_UpdateCollider_Frozen(this, play);
    } else {
        EnGo_UpdateCollider_Default(this, play);
    }
}

// Interrupt current Action to talk.
s32 func_80A12774(EnGo* this, PlayState* play) {
    if (!(this->actionFlags & 7) || !Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        return false;
    }

    if ((ENGO_GET_TYPE(&this->actor) != ENGO_PKEG_SELLER) && //
        (ENGO_GET_TYPE(&this->actor) != ENGO_RACER)) {
        if (!(this->actionFlags & ENGO_FLAG_ROLLEDUP)) {
            this->actionFlags |= ENGO_FLAG_ENGAGED;
        }
    }

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_ASIDE_STORE) ||      //
        (ENGO_GET_TYPE(&this->actor) == ENGO_ASIDE_ELDERSROOM) || //
        (ENGO_GET_TYPE(&this->actor) == ENGO_ASIDE_ELDERSSON)) {
        this->eyeTimer = 0;
        this->eyeTexIndex = ENGO_EYETEX_OPEN;
        this->actionFlags |= ENGO_FLAG_EYESOPEN;
    }

    SubS_UpdateFlags(&this->actionFlags, 0, 7);
    this->cutsceneState = 0;
    this->animState = 0;
    this->priorActionFn = this->actionFunc;
    this->actionFunc = EnGo_Talk;
    return true;
}

s32 EnGo_DetectCollisions(EnGo* this, PlayState* play) {
    this->actionFlags &= ~ENGO_FLAG_HIT_OTHER;
    this->actionFlags &= ~ENGO_FLAG_HIT_BY_OTHER;
    this->actionFlags &= ~ENGO_FLAG_HIT_OBJ;

    if ((this->colliderCylinder.base.atFlags & AT_HIT) || (this->colliderSphere.base.atFlags & AT_HIT)) {
        this->colliderCylinder.base.atFlags &= ~AT_HIT;
        this->colliderSphere.base.atFlags &= ~AT_HIT;
        this->actionFlags |= ENGO_FLAG_HIT_OTHER;
        this->harmlessTimer = 40;
    }

    if ((this->colliderCylinder.base.acFlags & AC_HIT) || (this->colliderSphere.base.acFlags & AC_HIT)) {
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
        this->colliderSphere.base.acFlags &= ~AC_HIT;
        this->actionFlags |= ENGO_FLAG_HIT_BY_OTHER;
    }

    if ((this->colliderCylinder.base.ocFlags1 & OC1_HIT) || (this->colliderSphere.base.ocFlags1 & OC1_HIT)) {
        this->colliderCylinder.base.ocFlags1 &= ~OC1_HIT;
        this->colliderSphere.base.ocFlags1 &= ~OC1_HIT;
        this->actionFlags |= ENGO_FLAG_HIT_OBJ;
    }

    return false;
}

s32 func_80A12954(EnGo* this, PlayState* play) {
    const u8 CS_ACTION_INVALID = UINT8_MAX;

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_BROTHER) && (play->csCtx.state != 0) && (this->actor.draw != NULL) &&
        (play->sceneNum == SCENE_10YUKIYAMANOMURA2) && (gSaveContext.sceneSetupIndex == 1) &&
        (play->csCtx.currentCsIndex == 0)) {
        if (this->unk_3F0 == 0) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->currentCsAction = CS_ACTION_INVALID;
            this->unk_3F0 = 1;
            this->priorActionFn = this->actionFunc;
        }
        SubS_UpdateFlags(&this->actionFlags, 0, 7);
        this->actionFunc = EnGo_Cutscene_ThawBrother;
    } else if (this->unk_3F0 != 0) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->currentCsAction = CS_ACTION_INVALID;
        this->unk_3F0 = 0;
        SubS_UpdateFlags(&this->actionFlags, 3, 7);
        this->actionFunc = this->priorActionFn;
    }

    return false;
}

s32 EnGo_HandleAnimation(EnGo* this, PlayState* play) {
    s8 objIdx = this->actor.objBankIndex;
    s8 objIdx2 = -1;
    s32 ret = 0;

    if ((this->anim >= ENGO_ANIM_HAKUGIN_START) && (this->indexHakuginDemo >= 0)) {
        objIdx2 = this->indexHakuginDemo;
    } else if ((this->anim >= ENGO_ANIM_TAISOU_START) && (this->indexTaisou >= 0)) {
        objIdx2 = this->indexTaisou;
    } else if (this->anim < ENGO_ANIM_TAISOU_START) {
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
s32 EnGo_HandleSfx(EnGo* this, PlayState* play) {
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

/**
 * @brief Change the Goron's animation.
 *
 * Goron animations come from one of three categories
 * - Basic Goron animations
 * - Goron Gymnastics (Stretches, Cheers, etc...)
 * - TBD
 * Changing animations with this function handles the transitions between the three categories.
 *
 * @return true if animation request was valid
 */
s32 EnGo_ChangeAnimation(EnGo* this, PlayState* play, EnGoAnimationIndex anim) {
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

void EnGo_UpdateEyes(EnGo* this) {
    if (this->actionFlags & ENGO_FLAG_EYESOPEN) {
        if (DECR(this->eyeTimer) == 0) {
            this->eyeTexIndex++;
            if (this->eyeTexIndex >= ENGO_EYETEX_CLOSED2) {
                this->eyeTimer = Rand_S16Offset(30, 30);
                this->eyeTexIndex = ENGO_EYETEX_OPEN;
            }
        }
    }
}

// Changes Animation from ? to ShiveringSurprised to Shivering
void EnGo_Surprised(EnGo* this, PlayState* play) {
    if (this->surprisePhase == 0) {
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVERINGSURPRISED);
        this->surprisePhase++;
    } else if ((this->surprisePhase == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER_IMM);
        this->surprisePhase++;
    }
}

s32 EnGo_HandleBrotherReactions(EnGo* this, PlayState* play) {
    u16 textId = play->msgCtx.currentTextId;
    Player* player = GET_PLAYER(play);

    if (ENGO_GET_TYPE(&this->actor) != ENGO_BROTHER) {
        return false;
    }

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        if (this->lastTextId != textId) {
            switch (textId) {
                case 0xE1A: // Hunh? What  have I been doing?
                    this->actionFlags |= ENGO_FLAG_ENGAGED;
                    this->targetActor = this->actor.child;
                    break;

                case 0xE1D: // You hear this guy? The great Darmani died long ago and is lying in his gr...
                case 0xE25: // ...Really? I don't know who you are, but thank you!
                    if (ENGO_GET_SUBTYPE(&this->actor) == ENGO_FROZEBRO) {
                        this->targetActor = &GET_PLAYER(play)->actor;
                    }
                    break;

                case 0xE27: // What's this?
                    if (ENGO_GET_SUBTYPE(&this->actor) == ENGO_FROZEBRO) {
                        this->targetActor = this->actor.child;
                    }

                case 0xE16: // Y-you're...No! No, you're not the great Darmani, are you?
                case 0xE1E: // Heeee!!! Darmani!
                    this->dialogActionFn = EnGo_Surprised;
                    break;

                case 0xE1F: // I was shocked, too. But somehow, it seems the great Darmani isn't dead.
                    if (ENGO_GET_SUBTYPE(&this->actor) == ENGO_GRAVEBRO) {
                        this->targetActor = &GET_PLAYER(play)->actor;
                    }
                    break;
            }
        }
        this->changedText = true;
        this->lastTextId = textId;
    } else if (this->changedText) {
        // If the Player isn't Talking, and the text has changed, its the last text
        // Set everything back to the "Idle" behavior.
        this->changedText = false;
        this->dialogActionFn = NULL;
        this->lastTextId = 0;
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
        this->actionFlags &= ~ENGO_FLAG_ENGAGED;
    }

    if (this->dialogActionFn != NULL) {
        this->dialogActionFn(this, play);
    }

    return false;
}

s32 EnGo_UpdateRotationToTarget(EnGo* this, PlayState* play) {
    s32 pad;
    Vec3f targetPos;
    Vec3f thisPos;
    s16 desiredYaw;

    Math_Vec3f_Copy(&targetPos, &this->targetActor->world.pos);
    Math_Vec3f_Copy(&thisPos, &this->actor.world.pos);
    desiredYaw = Math_Vec3f_Yaw(&thisPos, &targetPos);

    Math_ApproachS(&this->headRotY, (desiredYaw - this->bodyRotY) - this->actor.shape.rot.y, 4, 0x2AA8); // 60 degree
    this->headRotY = CLAMP(this->headRotY, -0x1FFE, 0x1FFE);                                             // +-45 degrees

    Math_ApproachS(&this->bodyRotY, (desiredYaw - this->headRotY) - this->actor.shape.rot.y, 4, 0x2AA8); // 60 degree
    this->bodyRotY = CLAMP(this->bodyRotY, -0x1C70, 0x1C70);                                             // +-40 degrees

    Math_Vec3f_Copy(&thisPos, &this->actor.focus.pos);
    if (this->targetActor->id == ACTOR_PLAYER) {
        targetPos.y = ((Player*)this->targetActor)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&targetPos, &this->targetActor->focus.pos);
    }

    Math_ApproachS(&this->headRotZ, Math_Vec3f_Pitch(&thisPos, &targetPos) - this->bodyRotZ, 4, 0x2AA8); // 60 degree
    this->headRotZ = CLAMP(this->headRotZ, -0x1554, 0x1554);                                             // +-30 degrees

    Math_ApproachS(&this->bodyRotZ, Math_Vec3f_Pitch(&thisPos, &targetPos) - this->headRotZ, 4, 0x2AA8); // 60 degree
    this->bodyRotZ = CLAMP(this->bodyRotZ, -0xE38, 0xE38);                                               // +-20 degrees

    return false;
}

// Handle Dialog + something else
s32 EnGo_HandleDialogReactions(EnGo* this, PlayState* play) {
    if (!this->changedText) {
        this->targetActor = &GET_PLAYER(play)->actor;
    }

    EnGo_HandleBrotherReactions(this, play);

    if (this->actionFlags & ENGO_FLAG_ENGAGED) { // Engaged
        this->actionFlags &= ~ENGO_FLAG_LOST_ATTENTION;
        this->actionFlags |= ENGO_FLAG_FACE_TARGET; // Face Player
        EnGo_UpdateRotationToTarget(this, play);
    } else if (this->actionFlags & ENGO_FLAG_FACE_TARGET) {
        this->actionFlags &= ~ENGO_FLAG_FACE_TARGET;
        this->headRotZ = 0;
        this->headRotY = 0;
        this->bodyRotZ = 0;
        this->bodyRotY = 0;
        this->loseAttentionTimer = 20;
    } else if (DECR(this->loseAttentionTimer) == 0) {
        this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
        this->loseAttentionTimer = 20;
    }

    return true;
}

void func_80A132C8(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_v1 = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    if ((fabsf(this->actor.playerHeightRel) > 20.0f) || (this->actor.xzDistToPlayer > 300.0f)) {
        SubS_UpdateFlags(&this->actionFlags, 3, 7); // |= 0b011 &= ~0b111
    } else if ((player->transformation != PLAYER_FORM_GORON) || (ABS_ALT(temp_v1) >= 0x1C70) ||
               (gSaveContext.save.weekEventReg[21] & WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON) ||
               (gSaveContext.save.weekEventReg[21] & WE_21_3_THAWED_GRAVEMAKERS_BROTHER)) {
        // Change Flags if not goron or yaw too great or certain events are set.
        SubS_UpdateFlags(&this->actionFlags, 3, 7); // |= 0b011 &= ~0b111
    } else {
        // Change OTHER actionFlags
        SubS_UpdateFlags(&this->actionFlags, 4, 7); // |= 0b100 &= ~0b111
    }
}

void func_80A133A8(EnGo* this, PlayState* play) {
    if (gSaveContext.save.weekEventReg[21] & WE_21_3_THAWED_GRAVEMAKERS_BROTHER) {
        SubS_UpdateFlags(&this->actionFlags, 3, 7); // |= 0b011 &= ~0b111
    } else {
        SubS_UpdateFlags(&this->actionFlags, 4, 7); // |= 0b100 &= ~0b111
    }
}

Actor* EnGo_LookupBrother(EnGo* this, PlayState* play) {
    Actor* actor;
    Actor* retActor = NULL;

    while (true) {
        actor = SubS_FindActor(play, retActor, ACTORCAT_NPC, ACTOR_EN_GO);
        retActor = actor;

        if ((actor != NULL) && ((EnGo*)actor != this) && //
            (ENGO_GET_TYPE(actor) == ENGO_BROTHER) &&    //
            (ENGO_GET_SUBTYPE(actor) == ENGO_GRAVEBRO)) {
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

/**
 * The goron's collider radius is greater when it needs to be able to drop the powder-keg infront of the player.
 */
void EnGo_UpdateColliderRadius_PowderKegSeller(EnGo* this, PlayState* play, s32 isGivenPK) {
    if ((gSaveContext.save.weekEventReg[18] & WE_18_7_HAS_PK_PRIVLEDGES) ||
        (play->actorCtx.unk5 & 1) // Same check occurs in PowderKeg ammo check MessageScript Command
        || isGivenPK) {
        this->colliderSphere.dim.modelSphere.radius = 300;
    } else {
        this->colliderSphere.dim.modelSphere.radius = 380;
    }
}

// EnGoCutscene_StopIfDoneAndCheckCanPlay
s32 EnGoCutscene_StopIfDoneAndCheckCanPlay(EnGo* this, s16 indexCutscene) {
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
    } else if (ActorCutscene_GetCanPlayNext(indexCutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(indexCutscene, &this->actor);
        return true;
    }
    ActorCutscene_SetIntentToPlay(indexCutscene);
    return false;
}

/**
 * Handle the animation of the "Goron Pound"
 *
 * There are Several Phases to the pound.
 * - Phase 1: (Once in Rolled-Up form) the pound starts by leaping into the air.
 *   - The goron rotates until it's back faces the ground at its peak.
 *   - The goron distorts shape until at its peak.
 *   - Transition: At the peak, all movement is halted
 * - Phase 2: While hanging, the goron reverts back to normal shape
 *   - Transition: At reaching maxHangTime, ENGO_POUND_FALL_VEL is applied.
 * - Phase 3: The Goron falls to the ground
 *   - Transition: At reaching the ground.
 *
 * @param initialVelocity Initial +Y velocity of the pound.
 * @param maxDistortion Maximum distortion of the goron's shape
 * @param maxHangtime Maximum hangtime at the peak of the pound
 * @returns True when pound finishes
 */
s32 EnGo_CutsceneGateKeeperPound(EnGo* this, f32 initialVelocity, f32 maxDistortion, s32 maxHangtime) {
    s32 pad;
    f32 rotAndDistortFactor = 1.0f;
    f32 velocity = this->actor.velocity.y + this->actor.gravity;
    s32 isFinished;

    if (this->actor.bgCheckFlags & 2) { // Settled to the Ground
        isFinished = true;
    } else {
        if (velocity > 0.0f) {
            // PHASE 1: Goron is rising
            rotAndDistortFactor = velocity / initialVelocity;
            this->actor.shape.rot.x += (s16)(0x238C * rotAndDistortFactor); // Max 50 degrees
            this->elapsedHangtime = 0;
        } else if ((s32)this->actor.velocity.y == 0) {
            if (maxHangtime >= this->elapsedHangtime) {
                // PHASE 2: Goron is hanging in the air
                rotAndDistortFactor = (f32)this->elapsedHangtime / maxHangtime;
            } else {
                // Transition 2->3: Hanging is complete
                this->actor.gravity = ENGO_POUND_FALL_VEL;
            }
            this->elapsedHangtime++;
        } else if (this->elapsedHangtime == 0) {
            // Transition 1->2: Goron has reached the peak
            this->actor.velocity.y = 0.0f;
            this->actor.gravity = 0.0f;
            rotAndDistortFactor = velocity / initialVelocity;
        } else {
            // PHASE 3: Goron is falling
        }
        isFinished = false;
    }

    // Handle Shape distortions
    this->scaleFactorPoundDistortion = (1.0f - rotAndDistortFactor) * maxDistortion;
    this->actor.scale.x = this->scaleFactor - this->scaleFactorPoundDistortion;
    this->actor.scale.y = this->scaleFactor + this->scaleFactorPoundDistortion;
    this->actor.scale.z = MAX(this->actor.scale.x, this->actor.scale.y);

    return isFinished;
}

void EnGo_CutsceneGateKeeperPoundQuake(PlayState* play, s16 quakeSpeed, s16 vertMagnitude, s16 quakeTime) {
    s16 indexQuake = Quake_Add(Play_GetCamera(play, CAM_ID_MAIN), 3);

    Quake_SetCountdown(indexQuake, quakeTime);
    Quake_SetSpeed(indexQuake, quakeSpeed);
    Quake_SetQuakeValues(indexQuake, vertMagnitude, 0, 0, 0);
}

void EnGo_CutsceneGateKeeperPoundEffects(EnGo* this, PlayState* play) {
    EnGo_CutsceneGateKeeperPoundQuake(play, 0x6C77, 7, 20);
    play->actorCtx.unk2 = 4;
    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, 0);
    EffectSsBlast_SpawnWhiteShockwave(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f);
}

void EnGo_DrawIceBlockIfFrozen(EnGo* this, PlayState* play, f32 scale, f32 alpha) {
    u32 frames1;
    u32 frames2;

    if (this->actionFlags & ENGO_FLAG_FROZEN) {
        Matrix_Push();

        OPEN_DISPS(play->state.gfxCtx);

        func_8012C2DC(play->state.gfxCtx);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(scale * 0.7f, scale * 0.8f, scale, MTXMODE_APPLY);
        func_800B8118(&this->actor, play, 0);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        frames1 = play->gameplayFrames % 256;
        frames2 = (play->gameplayFrames * 2) % 256;
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, frames1, 0x20, 0x10, 1, 0, frames2, 0x40, 0x20));
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, (u8)alpha);
        gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);

        CLOSE_DISPS(play->state.gfxCtx);

        Matrix_Pop();
    }
}

void EnGo_MakeSteamEffect(EnGo* this) {
    static Vec3f accel = { 0.0f, 0.06f, 0.0f };
    Vec3f tempPos;
    Vec3f pos;
    s16 rotAngle = Rand_ZeroOne() * 360.0f * 182.0f;

    Math_Vec3f_Copy(&tempPos, &gZeroVec3f);
    tempPos.z = 28.0f;
    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, rotAngle, &tempPos, &pos);
    pos.y = (Rand_ZeroOne() * 10.0f) + 4.0f;
    pos.y += this->actor.floorHeight;
    EnGo_VfxInit_Steam(&this->effectTable[ENGO_NUM_EFFECTS / 2], pos, accel, gZeroVec3f, ENGO_NORMAL_SCALE,
                       (0.2f * ENGO_NORMAL_SCALE), ENGO_DUST_STEAM_LIFETIME);
}

/**
 * Gatekeepers Message Callback to open the Goron Shrine.
 */
s32 EnGo_Cutscene_OpenShrine(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    EnGo* this = THIS;
    s32 ret = false;

    switch (this->cutsceneState) {
        case 0:
            this->indexCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            if (EnGoCutscene_StopIfDoneAndCheckCanPlay(this, this->indexCutscene)) {
                this->animState = 1;
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
            if (EnGoCutscene_StopIfDoneAndCheckCanPlay(this, this->indexCutscene)) {
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

    switch (this->animState) {
        case 1:
            EnGo_ChangeAnimation(this, play, ENGO_ANIM_ROLL);
            this->actionFlags |= ENGO_FLAG_CURLING;
            this->animState++;
            break;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->actionFlags &= ~ENGO_FLAG_CURLING;
                this->actionFlags &= ~ENGO_FLAG_STANDINGMAYBE;
                this->actionFlags |= ENGO_FLAG_ROLLEDUP;
                this->animState++;
                this->delayTimer = 0;
                this->actor.shape.yOffset = ENGO_ROLLEDUP_Y_OFFSET;
            }
            break;

        case 3:
            this->delayTimer++;
            if (this->delayTimer >= 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_JUMP);
                this->actor.velocity.y = ENGO_POUND_RISE_VEL;
                this->actor.gravity = ENGO_NORMAL_GRAVITY;
                this->animState++;
            }
            break;

        case 4:
            if (EnGo_CutsceneGateKeeperPound(this, ENGO_POUND_RISE_VEL, (0.4f) * ENGO_NORMAL_SCALE, 6)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_LAND_BIG);
                EnGo_CutsceneGateKeeperPoundEffects(this, play);
                this->animState++;
                this->delayTimer = 0;
                gSaveContext.save.weekEventReg[88] |= WE_88_6_GATEKEEPER_OPENED_SHRINE;
            }
            break;

        case 5:
            this->delayTimer++;
            if (this->delayTimer >= 10) {
                EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
                this->actor.shape.rot.x = 0;
                this->actionFlags &= ~ENGO_FLAG_ROLLEDUP;
                this->actionFlags |= ENGO_FLAG_STANDINGMAYBE;
                this->animState++;
            }
            break;

        case 6:
            this->cutsceneState++;
            if (this->cutsceneState >= 65) {
                switch (player->transformation) {
                    case PLAYER_FORM_HUMAN:
                        gSaveContext.save.weekEventReg[88] |= WE_88_7_GATEKEEPER_OPENED_SHRINE_FOR_HUMAN;
                        break;

                    case PLAYER_FORM_GORON:
                        gSaveContext.save.weekEventReg[89] |= WE_89_2_GATEKEEPER_OPENED_SHRINE_FOR_GORON;
                        break;

                    case PLAYER_FORM_ZORA:
                        gSaveContext.save.weekEventReg[89] |= WE_89_1_GATEKEEPER_OPENED_SHRINE_FOR_ZORA;
                        break;

                    case PLAYER_FORM_DEKU:
                        gSaveContext.save.weekEventReg[89] |= WE_89_0_GATEKEEPER_OPENED_SHRINE_FOR_DEKU;
                        break;
                }
                ret = true;
            }
            break;
    }

    Actor_MoveWithGravity(&this->actor);
    return ret;
}

/**
 * Powder Keg Salesman Message Callback to give the Powder Keg for the Test.
 */
s32 EnGo_Cutscene_GivePowderKeg(Actor* thisx, PlayState* play) {
    static Vec3f sPowderKegSpawnOffset = { 0.0f, 200.0f, 280.0f };
    EnGo* this = THIS;
    Vec3f powderKegSpawnPos;
    s32 ret = false;

    switch (this->cutsceneState) {
        case 0:
            this->indexCutscene = this->actor.cutscene;
            if (EnGoCutscene_StopIfDoneAndCheckCanPlay(this, this->indexCutscene)) {
                this->cutsceneState++;
            }
            break;

        case 1:
            EnGo_ChangeAnimation(this, play, ENGO_ANIM_DROPKEG);
            this->cutsceneState++;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, 16.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_HAND_HIT);
            }

            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                EnGo_ChangeAnimation(this, play, ENGO_ANIM_LYINGDOWNIDLE_IMM);
                Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &sPowderKegSpawnOffset,
                                              &powderKegSpawnPos);
                gSaveContext.powderKegTimer = 2400;
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, powderKegSpawnPos.x, powderKegSpawnPos.y,
                            powderKegSpawnPos.z, 1, 0, 0, 0);
                EnGo_UpdateColliderRadius_PowderKegSeller(this, play, true);
                this->delayTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 3:
            if (this->delayTimer >= 60) {
                ActorCutscene_Stop(this->indexCutscene);
                this->delayTimer = 0;
                this->cutsceneState = 0;
                ret = true;
            } else {
                this->delayTimer++;
            }
            break;
    }

    return ret;
}

void EnGo_SetRacerAnimation(EnGo* this, PlayState* play) {
    static Vec3f sStretchingGoronOffset = { 0.0f, 0.0f, 40.0f };

    static s32 sSubtypeToAnimIndex[] = { ENGO_ANIM_SQUAT_SIDE_TO_SIDE, ENGO_ANIM_DOUBLE_ARM_SIDEBEND,
                                         ENGO_ANIM_SHAKE_LIMBS,        ENGO_ANIM_SINGLE_ARM_SIDEBEND,
                                         ENGO_ANIM_SITTING_STRETCH,    ENGO_ANIM_HELP_SITTING_STRETCH };
    Vec3f newSittingStretcherPos;

    // The first four Racer gorons have different stretches depending on context
    // The last two remain the same (since they are dependent on one-another)
    s32 subtypeLookup = ENGO_GET_SUBTYPE(&this->actor) % 6;
    if (subtypeLookup < 4) {
        subtypeLookup = ((gSaveContext.eventInf[2] & 0xF) + subtypeLookup) % 4;
    }

    EnGo_ChangeAnimation(this, play, sSubtypeToAnimIndex[subtypeLookup]);

    // Move the Sitting Gorward, since it spawns at the same location as its helper.
    if (this->anim == ENGO_ANIM_SITTING_STRETCH) {

        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &sStretchingGoronOffset,
                                      &newSittingStretcherPos);
        Math_Vec3f_Copy(&this->actor.world.pos, &newSittingStretcherPos);
    }

    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, this->scaleFactor);
    this->sleepState = ENGO_AWAKE;
    this->actionFlags = ENGO_FLAG_NONE;
    this->actionFlags |= (ENGO_FLAG_LOST_ATTENTION | ENGO_FLAG_EYESOPEN);
    this->actor.gravity = 0.0f;
}

/**
 * Set the goron as a spectator.
 *
 * Spectators engage in one of two cheering animations. Either Cheering with their hands above their head, or
 * cupping their hands infront of their faces and shouting.
 */
void EnGo_SetSpectatorAnimation(EnGo* this, PlayState* play) {
    static s32 sSubtypeToAnimIndex[] = { ENGO_ANIM_CHEER, ENGO_ANIM_SHOUT };
    s16 animFrame;

    EnGo_ChangeAnimation(this, play, sSubtypeToAnimIndex[ENGO_GET_SUBTYPE(&this->actor) % 2]);
    animFrame = Rand_ZeroOne() * this->skelAnime.endFrame;
    this->skelAnime.curFrame = animFrame;

    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, this->scaleFactor);
    this->sleepState = ENGO_AWAKE;
    this->actionFlags = ENGO_FLAG_NONE;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFlags |= ENGO_FLAG_EYESOPEN;
    this->actor.gravity = 0.0f;
}

/**
 * Set the goron as frozen.
 *
 * Will shiver upon awakening, but otherwise encased in a block of ice.
 */
void EnGo_SetFrozenAnimation(EnGo* this, PlayState* play) {
    Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit1);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->anim = -1;
    EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
    this->sleepState = ENGO_AWAKE;
    this->iceBlockScale = (this->scaleFactor / 0.01f) * 0.9f;
    this->eyeTexIndex = ENGO_EYETEX_CLOSED;
    this->actionFlags = ENGO_FLAG_NONE;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFlags |= ENGO_FLAG_FROZEN;
    this->iceBlockAlpha = 100.0f;
}

// Called from Gatekeepr's Setup function
void func_80A1428C(EnGo* this, PlayState* play) {
    s16 yawToPathPoint;
    Vec3f currentPos;
    Vec3f startingPathPoint;

    Math_Vec3f_Copy(&currentPos, &this->actor.world.pos);
    if (this->path != NULL) {
        this->actor.flags &= ~ACTOR_FLAG_2000000;
        SubS_CopyPointFromPathCheckBounds(this->path, 0, &startingPathPoint);
        yawToPathPoint = Math_Vec3f_Yaw(&currentPos, &startingPathPoint);
        this->actor.shape.rot.y = yawToPathPoint;
        this->actor.world.rot.y = yawToPathPoint;
    }
    this->actionFlags = ENGO_FLAG_NONE;
    this->actionFlags |= 0x100;
    this->actor.shape.yOffset = ENGO_SNOWBALL_Y_OFFSET;
    this->actor.gravity = ENGO_NORMAL_GRAVITY;
}

/**
 * Set the goron as covering their ears.
 */
void EnGo_SetCoverEarsAnimation(EnGo* this, PlayState* play) {
    EnGo_ChangeAnimation(this, play, ENGO_ANIM_COVEREARS);
    Actor_SetScale(&this->actor, this->scaleFactor);
    this->actionFlags = ENGO_FLAG_NONE;
    this->actor.gravity = ENGO_NORMAL_GRAVITY;
    SubS_UpdateFlags(&this->actionFlags, 3, 7);
    this->sleepState = ENGO_AWAKE;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->eyeTimer = 0;
    this->eyeTexIndex = ENGO_EYETEX_CLOSED2;
    this->iceBlockScale = 0.0f;
    this->iceBlockAlpha = 0.0f;
}

/**
 * Set the goron as shivering from the cold.
 */
void EnGo_SetShiverAnimation(EnGo* this, PlayState* play) {
    EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
    Actor_SetScale(&this->actor, this->scaleFactor);
    this->actionFlags = ENGO_FLAG_NONE;
    this->actor.gravity = ENGO_NORMAL_GRAVITY;
    SubS_UpdateFlags(&this->actionFlags, 3, 7);
    this->sleepState = ENGO_AWAKE;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFlags |= ENGO_FLAG_EYESOPEN;
    this->eyeTimer = 0;
    this->eyeTexIndex = ENGO_EYETEX_OPEN;
    this->iceBlockScale = 0.0f;
    this->iceBlockAlpha = 0.0f;
}

/**
 * Set up the Racers Animation/Actions
 *
 * Racers are strewn about the starting area of the racetrack doing various stretches.
 */
void EnGo_Racer_Setup(EnGo* this, PlayState* play) {
    if (((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 0)) ||
         (gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 2))) &&
        (gSaveContext.save.weekEventReg[33] & 0x80)) {
        EnGo_SetRacerAnimation(this, play);
        this->actionFunc = EnGo_Idle;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * Set up the Spectators Animation/Actions
 *
 * Racers are strewn about the racetrack doing cheers
 */
void EnGo_Spectator_Setup(EnGo* this, PlayState* play) {
    if ((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1)) ||
        (gSaveContext.save.entrance == ENTRANCE(CUTSCENE, 0))) {
        EnGo_SetSpectatorAnimation(this, play);
        this->actionFunc = EnGo_Idle;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * Sets up the GateKeeper's Aniation/Actions
 *
 * When spoken to, can open the Goron Shrine for the player.
 * - On Day 1: Can be found shivering above the Goron Shrine.
 * - On Days 2,3: Can be found in a snowball.
 */
void EnGo_GateKeeper_Setup(EnGo* this, PlayState* play) {
    if (gSaveContext.save.day >= 2) {
        this->path = SubS_GetDayDependentPath(play, ENGO_GET_7F80(&this->actor), 0xFF, &this->indexPathPoint);
        if (this->path != NULL) {
            this->indexPathPoint = 1;
        }
        func_80A1428C(this, play);
        this->actionFunc = EnGo_Snowballing;
        this->msgEventCb = EnGo_Cutscene_OpenShrine;
    } else {
        EnGo_SetShiverAnimation(this, play);
        this->actionFunc = EnGo_Idle;
        this->msgEventCb = EnGo_Cutscene_OpenShrine;
    }
}

/**
 * Set up the Brothers' Animation/Actions
 *
 * The brothers are near Darmani's grave, once encrusted in ice.
 */
void EnGo_Brother_Setup(EnGo* this, PlayState* play) {

    if ((ENGO_GET_SUBTYPE(&this->actor) == ENGO_FROZEBRO) &&
        (((play->sceneNum == SCENE_10YUKIYAMANOMURA2) && /* Snow Mountain Village */
          (gSaveContext.sceneSetupIndex == 1) && (play->csCtx.currentCsIndex == 0)) ||
         !(gSaveContext.save.weekEventReg[21] & WE_21_3_THAWED_GRAVEMAKERS_BROTHER))) {
        this->actor.child = EnGo_LookupBrother(this, play);
        this->actor.child->child = &this->actor;
        EnGo_SetFrozenAnimation(this, play);
        this->actionFunc = EnGo_Frozen;
    } else {
        EnGo_SetShiverAnimation(this, play);
        this->actionFunc = EnGo_Idle;
    }
}

void EnGo_ShrineGoron_Setup(EnGo* this, PlayState* play) {
    if (!(gSaveContext.save.weekEventReg[22] & WE_22_2_GK_CALMED)) {
        EnGo_SetCoverEarsAnimation(this, play); // Cover Ears
        this->actionFunc = EnGo_Idle;
    } else {
        EnGo_SetShiverAnimation(this, play); // Shiver
        this->actionFunc = EnGo_Idle;
    }
}

void EnGo_PKegSeller_Setup(EnGo* this, PlayState* play) {
    EnGo_UpdateColliderRadius_PowderKegSeller(this, play, false);
    EnGo_ChangeAnimation(this, play, 0);
    this->scaleFactor *= ENGO_BIGGORON_MULTIPLIER;
    Actor_SetScale(&this->actor, this->scaleFactor);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.targetMode = 3;
    this->actionFlags = ENGO_FLAG_NONE;
    this->actor.gravity = ENGO_NORMAL_GRAVITY;
    SubS_UpdateFlags(&this->actionFlags, 3, 7);
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFlags |= ENGO_FLAG_EYESOPEN;
    this->msgEventCb = EnGo_Cutscene_GivePowderKeg; // Powder Keg Salesman Callback
    this->actionFunc = EnGo_Idle;
}

// Initial Action Function
void EnGo_Setup(EnGo* this, PlayState* play) {
    EffectTireMarkInit tireMarkInit = {
        0,
        62,
        { 0, 0, 15, 100 },
    };

    if (((this->indexTaisou < 0) || SubS_IsObjectLoaded(this->indexTaisou, play)) ||
        ((this->indexHakuginDemo < 0) || SubS_IsObjectLoaded(this->indexHakuginDemo, play))) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gGoronSkel, NULL, this->jointTable, this->morphTable,
                           GORON_LIMB_MAX);

        this->anim = ENGO_ANIM_INVALID;
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_UNROLL);
        this->actor.draw = EnGo_Draw;

        Collider_InitAndSetSphere(play, &this->colliderSphere, &this->actor, &sSphereInit);
        Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit2);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        Effect_Add(play, &this->indexEffect, EFFECT_TIRE_MARK, 0, 0, &tireMarkInit);

        this->actor.targetMode = 1;
        this->scaleFactor = ENGO_NORMAL_SCALE;
        this->msgEventCb = NULL;

        switch (ENGO_GET_TYPE(&this->actor)) {
            case ENGO_RACER: // Goron Racers
                EnGo_Racer_Setup(this, play);
                break;

            case ENGO_SPECTATOR:
                EnGo_Spectator_Setup(this, play);
                break;

            case ENGO_GATEKEEPER:
                EnGo_GateKeeper_Setup(this, play);
                break;

            case ENGO_BROTHER:
                EnGo_Brother_Setup(this, play);
                break;

            case ENGO_ASIDE_STORE:
            case ENGO_ASIDE_ELDERSROOM:
            case ENGO_ASIDE_ELDERSSON:
                EnGo_ShrineGoron_Setup(this, play); // Shrine Gorons
                break;

            case ENGO_PKEG_SELLER:
                EnGo_PKegSeller_Setup(this, play);
                break;

            default:
                Actor_MarkForDeath(&this->actor);
                break;
        }
    }
}

void EnGo_Idle(EnGo* this, PlayState* play) {
    s16 targetRot = this->actor.world.rot.y;

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_SPECTATOR) &&
        (gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1))) {
        // Spectators only cheer. No other interactions
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_CHEER - SFX_FLAG);
    } else if (ENGO_GET_TYPE(&this->actor) != ENGO_PKEG_SELLER) {
        // All others besides the Powder Keg Seller can be slept,
        if (EnGo_IsEnteringSleep(this, play)) {
            SubS_UpdateFlags(&this->actionFlags, 0, 7); // |=0b000 &= ~0b111
            this->sleepState = ENGO_ASLEEP;
            this->actionFunc = EnGo_Sleep;
        } else if (ENGO_GET_TYPE(&this->actor) == ENGO_BROTHER) {
            switch (ENGO_GET_SUBTYPE(&this->actor)) {
                case ENGO_GRAVEBRO:
                    func_80A132C8(this, play);
                    break;

                case ENGO_FROZEBRO:
                    func_80A133A8(this, play);
                    break;
            }
        } else if (ENGO_GET_TYPE(&this->actor) == ENGO_RACER) {
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3FFC) {
                SubS_UpdateFlags(&this->actionFlags, 3, 7); // |=0b011 &= ~0b111
            } else {
                SubS_UpdateFlags(&this->actionFlags, 0, 7); // |=0b000 &= ~0b111
            }
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, targetRot, 4, 0x2AA8);
}

/**
 * @brief Sleep
 */
void EnGo_Sleep(EnGo* this, PlayState* play) {
    s16 targetRot = this->actor.world.rot.y;
    u16 sfxId;

    if (EnGo_IsEnteringSleep(this, play)) {
        this->sleepState = ENGO_ASLEEP;
    }

    if (this->actionFlags & ENGO_FLAG_CURLING) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            // Finished Curling, now in a Rolled up form.
            this->actionFlags &= ~ENGO_FLAG_CURLING;
            this->actionFlags |= ENGO_FLAG_ROLLEDUP;
            if (this->sleepState != ENGO_AWAKE) {
                this->snorePhase = 0;
            }
            this->actor.shape.yOffset = ENGO_ROLLEDUP_Y_OFFSET;
        }
    } else if (this->actionFlags & ENGO_FLAG_UNCURLING) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            // Finished Uncurling, now in a standing up form.
            this->actionFlags |= ENGO_FLAG_STANDINGMAYBE;
            this->actionFlags &= ~ENGO_FLAG_UNCURLING;
        }
    } else if (this->actionFlags & ENGO_FLAG_ROLLEDUP) {
        if ((this->actor.xzDistToPlayer < 160.0f) && (this->actor.playerHeightRel < 20.0f) &&
            (this->sleepState == ENGO_AWAKE)) {
            // Changing from Rolled up to Unrolling, return to standing position.
            EnGo_ChangeAnimation(this, play, ENGO_ANIM_UNROLL_IMM);
            this->actionFlags &= ~ENGO_FLAG_STANDINGMAYBE;
            this->actionFlags &= ~ENGO_FLAG_ROLLEDUP;
            this->actionFlags |= ENGO_FLAG_UNCURLING;
            this->actor.shape.yOffset = 0.0f;
        } else if ((this->sleepState != ENGO_AWAKE) && (gSaveContext.save.weekEventReg[22] & WE_22_2_GK_CALMED)) {
            // While asleep, rhythmicallly snore and distort shape to show breathing.
            const f32 MAX_DISTORTION = (0.1f * ENGO_NORMAL_SCALE); // 10% maximum distortion from snoring
            this->actor.scale.x = this->scaleFactor - (Math_SinS(this->snorePhase) * MAX_DISTORTION);
            this->actor.scale.y = this->scaleFactor + (Math_SinS(this->snorePhase) * MAX_DISTORTION);
            this->actor.scale.z = this->scaleFactor + (Math_SinS(this->snorePhase) * MAX_DISTORTION);

            if (this->snorePhase == 0) {
                this->sleepState = -this->sleepState;
                sfxId = (this->sleepState > ENGO_AWAKE) ? NA_SE_EN_GOLON_SNORE1 : NA_SE_EN_GOLON_SNORE2;
                Actor_PlaySfxAtPos(&this->actor, sfxId);
            }
            this->snorePhase += 0x400; // ~5.7 degrees or ~1/3 rotation per second.
            this->actor.shape.yOffset = (this->actor.scale.y / this->scaleFactor) * ENGO_ROLLEDUP_Y_OFFSET;
            SubS_UpdateFlags(&this->actionFlags, 3, 7);
        }
    } else if ((this->actor.xzDistToPlayer >= 240.0f) || (this->actor.playerHeightRel >= 20.0f) ||
               (this->sleepState != ENGO_AWAKE)) {
        // A Standing goron not awake will start curling to go to sleep
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_ROLL);
        this->actionFlags &= ~ENGO_FLAG_STANDINGMAYBE;
        this->actionFlags &= ~ENGO_FLAG_ROLLEDUP;
        this->actionFlags |= ENGO_FLAG_CURLING;
        this->actor.shape.yOffset = 0.0f;
    }

    SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
    Math_ApproachS(&this->actor.shape.rot.y, targetRot, 4, 0x2AA8);
}

void EnGo_Frozen(EnGo* this, PlayState* play) {
    Actor* actor = this->colliderCylinder.base.ac;

    if ((this->actionFlags & ENGO_FLAG_HIT_BY_OTHER) && //
        (((actor != NULL) && (actor->id == ACTOR_OBJ_AQUA) && (actor->params & 1)) ||
         (this->actor.colChkInfo.damageEffect == 2))) {
        this->actionFunc = EnGo_AwaitThaw;
    }
}

void EnGo_AwaitThaw(EnGo* this, PlayState* play) {
    if (EnGoCutscene_StopIfDoneAndCheckCanPlay(this, this->actor.cutscene)) {
        this->actionFunc = EnGo_Thaw;
    }
}

void EnGo_Thaw(EnGo* this, PlayState* play) {
    EnGo* unfrozenBro = (EnGo*)this->actor.child;

    if ((s32)(this->iceBlockScale * 3.0f) != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
        Math_ApproachF(&this->iceBlockScale, 0.0f, 0.02f, 1.0f);
        this->iceBlockAlpha = (this->iceBlockScale / 0.9f) * 100.0f;
        EnGo_MakeSteamEffect(this);
    } else {
        ActorCutscene_Stop(this->actor.cutscene);
        EnGo_SetShiverAnimation(this, play);
        if ((ENGO_GET_TYPE(&this->actor) == ENGO_BROTHER) && (ENGO_GET_SUBTYPE(&this->actor) == ENGO_FROZEBRO)) {
            SubS_UpdateFlags(&this->actionFlags, 4, 7);

            // When the frozen goron has thawed, set the brother back to Idle.
            EnGo_SetShiverAnimation(unfrozenBro, play);
            unfrozenBro->actionFunc = EnGo_Idle;
        }
        this->actionFunc = EnGo_Idle;
    }
}

void EnGo_Cutscene_ThawBrother(EnGo* this, PlayState* play) {
    s32 animationIndices[] = {
        ENGO_ANIM_LYINGDOWNIDLE, ENGO_ANIM_UNROLL, ENGO_ANIM_SHIVER_IMM, ENGO_ANIM_HAKUGIN_20,
        ENGO_ANIM_HAKUGIN_18,    ENGO_ANIM_SHIVER, ENGO_ANIM_SHIVER,     ENGO_ANIM_CHEER,
    };
    u16 actorActionCmd = 0;
    s32 csAction;
    s32 actionIndex;

    switch (ENGO_GET_SUBTYPE(&this->actor)) {
        case ENGO_GRAVEBRO: // ENGO_70_0 (@todo Verify that this is the right EnGoType!)
            actorActionCmd = 128;
            break;

        case ENGO_FROZEBRO: // ENGO_70_1 (@todo Verify that this is the right EnGoType!)
            actorActionCmd = 129;
            break;
    }

    if ((actorActionCmd == 128) || (actorActionCmd == 129)) {
        if (Cutscene_CheckActorAction(play, actorActionCmd)) {
            actionIndex = Cutscene_GetActorActionIndex(play, actorActionCmd);
            csAction = play->csCtx.actorActions[actionIndex]->action;

            if (this->currentCsAction != (u8)csAction) {
                this->currentCsAction = csAction;
                EnGo_ChangeAnimation(this, play, animationIndices[csAction]);
                this->actionFlags = ENGO_FLAG_NONE;
                this->actionFlags |= ENGO_FLAG_EYESOPEN;
                this->eyeTexIndex = ENGO_EYETEX_OPEN;
                this->iceBlockScale = 0.0f;
                this->iceBlockAlpha = 0.0f;

                switch (csAction) {
                    case 1: // Unrolling
                        this->actionFlags |= ENGO_FLAG_STANDINGMAYBE;
                        this->skelAnime.curFrame = this->skelAnime.endFrame;
                        break;

                    case 5: // Shivering
                    case 6:
                        EnGo_SetFrozenAnimation(this, play);
                        break;
                }
            }

            switch (this->currentCsAction) {
                case 3: // ENGO_ANIM_HAKUGIN_20
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) &&
                        (this->anim == ENGO_ANIM_HAKUGIN_20)) {
                        EnGo_ChangeAnimation(this, play, ENGO_ANIM_HAKUGIN_21_IMM);
                    }
                    break;

                case 4: // ENGO_ANIM_HAKUGIN_18
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) &&
                        (this->anim == ENGO_ANIM_HAKUGIN_18)) {
                        EnGo_ChangeAnimation(this, play, ENGO_ANIM_HAKUGIN_19_IMM);
                    }
                    break;

                case 6: // ENGO_ANIM_SHIVER
                    if ((s32)(this->iceBlockScale * 3.0f) != 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
                        Math_ApproachF(&this->iceBlockScale, 0.0f, 0.02f, 1.0f);
                        this->iceBlockAlpha = (this->iceBlockScale / 0.9f) * 100.0f;
                        EnGo_MakeSteamEffect(this);
                    } else if (this->actionFlags & ENGO_FLAG_FROZEN) {
                        EnGo_SetShiverAnimation(this, play);
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

/**
 * Handle the Gatekeeper while they're in a snowball.
 *
 * On Day 2, they'll roll along a set path, and can be halted with certain attacks.
 * On Day 3, they're frozen solid.
 *
 * @param this
 * @param play
 */
// The Goron Gatekeeper rolls around the village, accruing snow.
void EnGo_Snowballing(EnGo* this, PlayState* play) {
    Vec3s* pPathPoints;
    Vec3f currentPos;
    Vec3f currentPathPoint;

    if ((this->actionFlags & ENGO_FLAG_HIT_BY_OTHER) && (this->actor.colChkInfo.damageEffect == ENGO_DMGEFF_BREAK)) {
        // Stop the Gatekeeper when hit by an appropriate effect
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SNOWBALL_BROKEN);
        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;
        EnGo_VfxSnowballBreak(this->effectTable, this->actor.world.pos);
        this->actor.shape.rot.x = 0;
        this->actor.speedXZ = 0.0f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);

        if (gSaveContext.save.day == 3) {
            EnGo_SetFrozenAnimation(this, play);
            this->actionFunc = EnGo_Frozen;
        } else {
            EnGo_SetShiverAnimation(this, play);
            this->actionFunc = EnGo_Idle;
        }
    } else if (this->path != NULL) {
        if (this->actionFlags & ENGO_FLAG_HIT_OTHER) {
            func_800B8E58(GET_PLAYER(play), NA_SE_PL_BODY_HIT);
            func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);
        }

        pPathPoints = Lib_SegmentedToVirtual(this->path->points);
        if (SubS_HasReachedPoint(&this->actor, this->path, this->indexPathPoint)) {
            if (this->indexPathPoint >= (this->path->count - 1)) {
                this->indexPathPoint = 0;
            } else {
                this->indexPathPoint++;
            }
        }

        Math_Vec3s_ToVec3f(&currentPathPoint, &pPathPoints[this->indexPathPoint]);
        Math_Vec3f_Copy(&currentPos, &this->actor.world.pos);
        Math_ApproachS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&currentPos, &currentPathPoint), 4, 0x38E);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (this->actor.bgCheckFlags & 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BIGBALL_ROLL - SFX_FLAG);
            func_800AE930(&play->colCtx, Effect_GetByIndex(this->indexEffect), &this->actor.world.pos, 18.0f,
                          this->actor.shape.rot.y, this->actor.floorPoly, this->actor.floorBgId);
        } else {
            func_800AEF44(Effect_GetByIndex(this->indexEffect));
        }

        this->actor.speedXZ = 4.0f;
        this->actor.shape.rot.x += (s16)(this->actor.speedXZ * 546.0f);
        Actor_MoveWithGravity(&this->actor);
    }
}

// Return the Character's Message Script
s32* EnGo_GetMessageScript(EnGo* this, PlayState* play) {
    static s32 D_80A16704[] = {
        /* ENGO_GRAVEBRO */ D_80A16100,
        /* ENGO_FROZEBRO */ D_80A16164,
    };

    if (this->sleepState != ENGO_AWAKE) {
        return D_80A1640C; // Lullaby Hint
    }

    if (ENGO_GET_TYPE(&this->actor) == ENGO_RACER) { // Goron Racer
        switch (ENGO_GET_SUBTYPE(&this->actor) % 6) {
            case ENGO_SQUAT_STRETCHER:
                return D_80A163BC; // Side to Side Squatting Goron Racer
            case ENGO_UNUSED:
                return D_80A163CC; // Unused Goron Racer?
            case ENGO_LIMB_SHAKER:
                return D_80A163DC; // Libm Shaking Goron Racer
            case ENGO_SIDE_STRETCHER:
                return D_80A163EC; // Side Stretching Goron Racer
            case ENGO_HAMSTRING_STRETCHER:
                return D_80A163FC;
            case ENGO_HAMSTRING_STRETCH_HELPER:
                return D_80A163FC;
        }
    }

    switch (ENGO_GET_TYPE(&this->actor)) {
        case ENGO_GATEKEEPER:
            return D_80A16350; // Goron Gatekeeper Message
        case ENGO_BROTHER:
            return D_80A16704[ENGO_GET_SUBTYPE(&this->actor)]; // Goron Brothers
        case ENGO_ASIDE_STORE:
            return D_80A16208; // Store reviewer?
        case ENGO_ASIDE_ELDERSROOM:
            return D_80A16254; // Shrine Gorons Elder's room
        case ENGO_ASIDE_ELDERSSON:
            return D_80A16210; // Shrine Gorons
        case ENGO_PKEG_SELLER:
            return D_80A16280; // Powder Keg Goron
        default:
            return D_80A16208; // Store reviewer?
    }
}

void EnGo_Talk(EnGo* this, PlayState* play) {
    s32 pad;
    Vec3f targetPos;
    Vec3f thisPos;

    if (!func_8010BF58(&this->actor, play, EnGo_GetMessageScript(this, play), this->msgEventCb,
                       &this->msgScriptResumePos)) {
        if ((ENGO_GET_TYPE(&this->actor) != ENGO_RACER) && !(this->actionFlags & ENGO_FLAG_ROLLEDUP)) {
            // Turn towards the player when in dialog
            Math_Vec3f_Copy(&targetPos, &this->targetActor->world.pos);
            Math_Vec3f_Copy(&thisPos, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&thisPos, &targetPos), 4, 0x2AA8);
        }
        SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
        return;
    }

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_ASIDE_STORE) || (ENGO_GET_TYPE(&this->actor) == ENGO_ASIDE_ELDERSROOM) ||
        (ENGO_GET_TYPE(&this->actor) == ENGO_ASIDE_ELDERSSON)) {
        this->eyeTimer = 0;
        this->actionFlags &= ~ENGO_FLAG_EYESOPEN;
        this->eyeTexIndex = ENGO_EYETEX_CLOSED2;
    }

    this->actionFlags &= ~ENGO_FLAG_ENGAGED;
    SubS_UpdateFlags(&this->actionFlags, 3, 7); // |= 0b011 &= ~0b111
    this->msgScriptResumePos = 0;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFunc = this->priorActionFn;
}

void EnGo_Init(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;

    this->indexTaisou = SubS_GetObjectIndex(OBJECT_TAISOU, play);            /* Gymnastics */
    this->indexHakuginDemo = SubS_GetObjectIndex(OBJECT_HAKUGIN_DEMO, play); /* White Silver / Even Silver? */
    this->actionFunc = EnGo_Setup;
}

void EnGo_Destroy(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;

    Collider_DestroyCylinder(play, &this->colliderCylinder);
    Collider_DestroySphere(play, &this->colliderSphere);
    Effect_Destroy(play, this->indexEffect);
}

void EnGo_Update(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;
    f32 xzRange;

    EnGo_DetectCollisions(this, play);

    // Something to do with the dialog.
    if (!func_80A12774(this, play)) {
        func_80A12954(this, play);
    }

    this->actionFunc(this, play);

    if (!(this->actionFlags & ENGO_FLAG_FROZEN)) {
        EnGo_UpdateEyes(this);
        EnGo_HandleAnimation(this, play);
        EnGo_HandleDialogReactions(this, play);
        EnGo_HandleSfx(this, play);
    }

    if (!(this->actionFlags & 0x100) && !(this->actionFlags & ENGO_FLAG_ROLLEDUP) &&
        !(this->actionFlags & ENGO_FLAG_FROZEN)) {
        if (ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) {
            xzRange = this->colliderSphere.dim.worldSphere.radius + 60;
        } else {
            xzRange = this->colliderCylinder.dim.radius + 40;
        }
        func_8013C964(&this->actor, play, xzRange, 20.0f, PLAYER_AP_NONE, this->actionFlags & 7);
    } else if ((this->actionFlags & ENGO_FLAG_ROLLEDUP) && (this->sleepState != ENGO_AWAKE)) {
        xzRange = this->colliderCylinder.dim.radius + 40;
        func_8013C964(&this->actor, play, xzRange, 20.0f, PLAYER_AP_NONE, this->actionFlags & 7);
    }

    if ((ENGO_GET_TYPE(&this->actor) != ENGO_PKEG_SELLER) && (ENGO_GET_TYPE(&this->actor) != ENGO_SPECTATOR) &&
        (ENGO_GET_TYPE(&this->actor) != ENGO_RACER)) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
    }

    func_80A122EC(this);
    EnGo_UpdateCollider(this, play);
    EnGo_UpdateEffects(this);
}

void EnGo_Draw_SnowballedOrCurled(EnGo* this, PlayState* play) {
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y + this->actor.shape.yOffset,
                     this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Translate(0.0f, -this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_Translate(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);

    if (this->actionFlags & ENGO_FLAG_SNOWBALLED) {
        Matrix_Scale(this->actor.scale.x * 8.0f, this->actor.scale.y * 8.0f, this->actor.scale.z * 8.0f, MTXMODE_APPLY);
    } else {
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    }

    Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, (this->actionFlags & ENGO_FLAG_SNOWBALLED) ? gGoronSnowballDL : gGoronRolledUpDL);

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnGo_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGo* this = THIS;
    Vec3f sp30;
    s32 idx;

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) && (limbIndex == 10)) {
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

    if ((this->actionFlags & ENGO_FLAG_STANDINGMAYBE) && (idx < 9)) {
        rot->y += (s16)(Math_SinS(this->limbRotTableY[idx]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->limbRotTableZ[idx]) * 200.0f);
    }
    return false;
}

void EnGo_TransfromLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnGo* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (this->actionFlags & ENGO_FLAG_LOST_ATTENTION) {
        stepRot = false;
    } else {
        stepRot = true;
    }

    if (this->actionFlags & ENGO_FLAG_FACE_TARGET) {
        overrideRot = true;
    } else {
        overrideRot = false;
    }

    if (!stepRot) {
        overrideRot = false;
    }

    switch (limbIndex) {
        case ENGO_LIMB_INDEX_HEAD:
            SubS_UpdateLimb(this->headRotZ + this->bodyRotZ + 0x4000,
                            this->headRotY + this->bodyRotY + this->actor.shape.rot.y + 0x4000, &this->headPos,
                            &this->headRot, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->headPos.x, this->headPos.y, this->headPos.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->headRot.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->headRot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->headRot.z, MTXMODE_APPLY);
            Matrix_Push();
            break;

        case ENGO_LIMB_INDEX_BODY:
            SubS_UpdateLimb(this->bodyRotZ + 0x4000, this->bodyRotY + this->actor.shape.rot.y + 0x4000, &this->bodyPos,
                            &this->bodyRot, stepRot, overrideRot);
            Matrix_Pop();
            Matrix_Translate(this->bodyPos.x, this->bodyPos.y, this->bodyPos.z, MTXMODE_NEW);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_RotateYS(this->bodyRot.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->bodyRot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->bodyRot.z, MTXMODE_APPLY);
            Matrix_Push();
            break;
    }
}

void EnGo_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80A1670C[] = {
        gGoronEyeOpenTex, gGoronEyeHalfTex, gGoronEyeClosedTex, gGoronEyeHalfTex, gGoronEyeClosed2Tex,
    };
    EnGo* this = THIS;

    if (!(this->actionFlags & (ENGO_FLAG_SNOWBALLED | ENGO_FLAG_ROLLEDUP))) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C28C(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A1670C[this->eyeTexIndex]));

        if (this->anim == ENGO_ANIM_SITTING_STRETCH) {
            Matrix_Translate(0.0f, 0.0f, -4000.0f, MTXMODE_APPLY);
        }
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnGo_OverrideLimbDraw, NULL, EnGo_TransfromLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        EnGo_Draw_SnowballedOrCurled(this, play);
    }
    EnGo_DrawIceBlockIfFrozen(this, play, this->iceBlockScale, this->iceBlockAlpha);
    EnGo_DrawEffects(this, play);
}
