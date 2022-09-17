/*
 * File: z_en_go.c
 * Overlay: ovl_En_Go
 * Description: Goron
 *
 * This actor handles multiple (but not all) Gorons. The gorons included are:
 * - RacerGoron: Gorons in the racetrack performing stretches before/after a race.
 * - SpectatorGoron: Gorons scattered throughout the racetrack watching the race.
 * - GatekeeperGoron: The Gatekeeper of the Goron Shrine
 * - GraveBroBoron: Both Goron brothers outside Darmani's grave (one of which is frozen)
 * - ShrineGoron: Gorons in the goron shrine (specifically, one in the elders room, one outside the elder's room, and
 *     one outside the shop, not all gorons in the goron shrine are covered by this actor)
 * - PowderKegGoron: The Powder Keg Making Goron in Goron Village.
 *
 * TODO:
 * - Do something about conversation references. Good to audit review, bad for readability.
 */

#include "z_en_go.h"
#include "objects/object_oF1d_map/object_oF1d_map.h"
#include "objects/object_hakugin_demo/object_hakugin_demo.h"
#include "objects/object_taisou/object_taisou.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)
#define THIS ((EnGo*)thisx)

#define ENGO_STANDING_Y_OFFSET 0.0f  // Actor shape offset in use when the goron is in any standing state.
#define ENGO_ROLLEDUP_Y_OFFSET 14.0f // Actor shape offset in use when a goron is "rolled up".
#define ENGO_SNOWBALL_Y_OFFSET 46.0f // Actor shape offset in use when a goron is in a snowball.

#define ENGO_NORMAL_SCALE 0.01f             // "Unit Scale" of a normal goron.
#define ENGO_BIGGORON_SCALE_MULTIPLIER 5.0f // Scale factor for the Powder Keg Biggoron

#define ENGO_NORMAL_GRAVITY -1.0f

#define ENGO_POUND_RISE_VEL 10.0f // Velocity at which the Gatekeeper's pound surges into the air.
#define ENGO_POUND_FALL_VEL -6.0f // Velocity at which the Gatekeeper's pound surgest to the ground.

#define ENGO_DUST_STEAM_LIFETIME 16 // Lifetime in frames of the Dust and Steam effects

#define ENGO_FLAG_NONE 0
#define ENGO_FLAG_ENGAGED (1 << 3)        // 0x0008
#define ENGO_FLAG_FACE_TARGET (1 << 4)    // 0x0010
#define ENGO_FLAG_EYESOPEN (1 << 5)       // 0x0020
#define ENGO_FLAG_LOST_ATTENTION (1 << 6) // 0x0040
#define ENGO_FLAG_STANDING (1 << 7)       // 0x0080
#define ENGO_FLAG_SNOWBALLED (1 << 8)     // 0x0100
#define ENGO_FLAG_ROLLEDUP (1 << 9)       // 0x0200
#define ENGO_FLAG_FROZEN (1 << 10)        // 0x0400
#define ENGO_FLAG_HIT_OTHER (1 << 11)     // 0x0800
#define ENGO_FLAG_HIT_BY_OTHER (1 << 12)  // 0x1000
#define ENGO_FLAG_HIT_OBJ (1 << 13)       // 0x2000
#define ENGO_FLAG_ROLLINGUP (1 << 14)     // 0x4000
#define ENGO_FLAG_UNROLLING (1 << 15)     // 0x8000

// gSaveContext.save.weekEventReg masks used in this actor.
// Formatted as WE_<index>_<bitpos>_<name>
#define WE_18_5_TALKED_TO_PKSELLER_AS_NONGORON (1 << 5)
#define WE_18_6_TALKED_TO_PKSELLER_AS_GORON (1 << 6)
#define WE_18_7_HAS_PK_PRIVLEDGES (1 << 7)
#define WE_19_0_STARTED_PKTEST (1 << 0)
#define WE_19_1_COMPLETED_PKTEST (1 << 1)
#define WE_21_1_SPOKE_TO_GRAVEMAKER_AS_NONGORON (1 << 1)
#define WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON (1 << 2)
#define WE_21_3_THAWED_GRAVEMAKERS_BROTHER (1 << 3)
#define WE_23_0_TALKED_TO_ASIDE_ELDERSROOM_AS_GORON (1 << 0)
#define WE_22_2_GK_CALMED (1 << 2)
#define WE_22_4_TALKED_TO_ASIDE_ELDERSSON_AS_GORON (1 << 4)
#define WE_24_7_TALKED_TO_ASIDE_ELDERSSON_AS_ANY (1 << 7)
#define WE_88_6_GATEKEEPER_OPENED_SHRINE (1 << 6)
#define WE_88_7_GATEKEEPER_OPENED_SHRINE_FOR_HUMAN (1 << 7)
#define WE_89_0_GATEKEEPER_OPENED_SHRINE_FOR_DEKU (1 << 0)
#define WE_89_1_GATEKEEPER_OPENED_SHRINE_FOR_ZORA (1 << 1)
#define WE_89_2_GATEKEEPER_OPENED_SHRINE_FOR_GORON (1 << 2)

void EnGo_Init(Actor* thisx, PlayState* play);
void EnGo_Destroy(Actor* thisx, PlayState* play);
void EnGo_Update(Actor* thisx, PlayState* play);
void EnGo_Draw(Actor* thisx, PlayState* play);

typedef enum EnGoEyeTexture {
    /* 0 */ ENGO_EYETEX_OPEN,
    /* 1 */ ENGO_EYETEX_HALF,
    /* 2 */ ENGO_EYETEX_CLOSED,
    /* 3 */ ENGO_EYETEX_HALF2,
    /* 4 */ ENGO_EYETEX_CLOSED2,
} EnGoEyeTexture;

typedef enum EnGoSleepState {
    /* -1 */ ENGO_ASLEEP_NEG = -1,
    /*  0 */ ENGO_AWAKE = 0,
    /*  1 */ ENGO_ASLEEP_POS,
} EnGoSleepState;

typedef enum EnGoEffectType {
    /* 0 */ ENGO_EFFECT_NONE = 0,
    /* 1 */ ENGO_EFFECT_SNOW1,
    /* 2 */ ENGO_EFFECT_SNOW2,
    /* 3 */ ENGO_EFFECT_SNOW3,
    /* 4 */ ENGO_EFFECT_DUST_START = 4,
    /* 4 */ ENGO_EFFECT_DUST1 = 4,
    /* 5 */ ENGO_EFFECT_DUST2,
    /* 6 */ ENGO_EFFECT_DUST3,
    /* 7 */ ENGO_EFFECT_STEAM_START = 7,
    /* 7 */ ENGO_EFFECT_STEAM = 7,
} EnGoEffectType;

typedef enum EnGoAnimationIndex {
    /* -1 */ ENGO_ANIM_INVALID = -1,
    /*  0 */ ENGO_ANIM_GORON_START = 0,
    /*  0 */ ENGO_ANIM_LYINGDOWNIDLE = 0,
    /*  1 */ ENGO_ANIM_LYINGDOWNIDLE_IMM,
    /*  2 */ ENGO_ANIM_UNROLL,
    /*  3 */ ENGO_ANIM_UNROLL_IMM,
    /*  4 */ ENGO_ANIM_ROLL,
    /*  5 */ ENGO_ANIM_SHIVER,
    /*  6 */ ENGO_ANIM_SHIVER_IMM,
    /*  7 */ ENGO_ANIM_DROPKEG,
    /*  8 */ ENGO_ANIM_COVEREARS,
    /*  9 */ ENGO_ANIM_SHIVERINGSURPRISED,

    /*  10 */ ENGO_ANIM_TAISOU_START = 10,
    /*  10 */ ENGO_ANIM_DOUBLE_ARM_SIDEBEND = 10,
    /*  11 */ ENGO_ANIM_SQUAT_SIDE_TO_SIDE,
    /*  12 */ ENGO_ANIM_SHAKE_LIMBS,
    /*  13 */ ENGO_ANIM_SINGLE_ARM_SIDEBEND,
    /*  14 */ ENGO_ANIM_SITTING_STRETCH,
    /*  15 */ ENGO_ANIM_CHEER,
    /*  16 */ ENGO_ANIM_SHOUT,
    /*  17 */ ENGO_ANIM_HELP_SITTING_STRETCH,

    // ???
    /*  18 */ ENGO_ANIM_HAKUGIN_START = 18,
    /*  18 */ ENGO_ANIM_SHOW = 18,
    /*  19 */ ENGO_ANIM_SHOW_LOOPED,
    /*  20 */ ENGO_ANIM_LOOK_AROUND,
    /*  21 */ ENGO_ANIM_LOOK_AROUND_LOOPED,
} EnGoAnimationIndex;

typedef enum EnGoLimbIndex {
    /* 10 */ ENGO_LIMB_INDEX_BODY = 10,
    /* 11 */ ENGO_LIMB_INDEX_LEFTARM = 11,
    /* 14 */ ENGO_LIMB_INDEX_RIGHTARM = 14,
    /* 17 */ ENGO_LIMB_INDEX_HEAD = 17,
} EnGoLimbIndex;

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for the goron who made Darmani's grave in the mountain village
static s32 sMsgScriptGoronGravemaker[] = {
    0x00150800, 0x40010022, 0x00150200, 0x180E0E10, 0x0C0F0E11, 0x0C0F0E12, 0x0C0F0E13, 0x0C0F0E14, 0x0C111502,
    0x100E0E15, 0x0C100015, 0x0400110E, 0x0E160C0F, 0x0E170C0F, 0x0E180C11, 0x15041610, 0x0E0E190C, 0x10001504,
    0x000D0100, 0x050E0E31, 0x0C100E0E, 0x2F0C1001, 0x00050E0E, 0x2D0C100E, 0x0E2B0C10,
};
#else
MsgScript sMsgScriptGoronGravemaker[] = {
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
// Message script for the frozen brother of the goron who made Darmani's grave in the mountain village
static s32 sMsgScriptGoronBrother[] = {
    0x00150800, 0x7E01004D, 0x00150400, 0x180E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C12, 0x16111508,
    0x100E0E1A, 0x0C170F0E, 0x230C180F, 0x0E240C0F, 0x0E250C17, 0x0F0E260C, 0x180F0E27, 0x0C170F0E, 0x280C180F,
    0x0E290C17, 0x0F0E2A0C, 0x16111508, 0x100E0E1A, 0x0C170F0E, 0x1B0C180F, 0x0E1C0C0F, 0x0E1D0C0F, 0x0E1E0C17,
    0x0F0E1F0C, 0x180F0E20, 0x0C170F0E, 0x210C0F0E, 0x220C1611, 0x15081000, 0x1504000D, 0x0100050E, 0x0E320C10,
    0x0E0E300C, 0x10010005, 0x0E0E2E0C, 0x100E0E2C, 0x0C100000,
};
#else
MsgScript sMsgScriptGoronBrother[] = {
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
// Message script for the shrine goron standing aside the store
static s32 sMsgScriptGoronAsideStore[2] = { 0xE0E520C, 0x10000000 };
#else
MsgScript sMsgScriptGoronAsideStore[] = {
    /* 0x0000 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E52), // This store is having trouble getting product because of the cold.
                                                  // Things are kind of expensive now, so you shouldn't shop here...
    /* 0x0003 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0004 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Messag Script for the shrine goron standing aside the Elder's son
static s32 sMsgScriptGoronAsideEldersSon[17] = {
    0x160400,  0x38010010, 0xE0E430C, 0xF0E440C, 0xF0E450C,  0x11188010, 0x160800,   0x1B0E0E46, 0xC0F0E47,
    0xC0F0E48, 0xC0F0E49,  0xC0F0E4A, 0xC111608, 0x11188010, 0xE0E4B0C,  0x100E0E42, 0xC100000,
};
#else

MsgScript sMsgScriptGoronAsideEldersSon[] = {
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
// Message Script for the shrine goron standing aside the Elder's room
static s32 sMsgScriptGoronAsideEldersRoom[11] = {
    0x160400,   0x22010009, 0xE0E4D0C, 0xF0E4E0C,  0x10001701, 0xC0E0E,
    0x4F0C0F0E, 0x500C1117, 0x1100E0E, 0x510C100E, 0xE4C0C10,
};
#else
MsgScript sMsgScriptGoronAsideEldersRoom[] = {
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

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for the goron in the goron village who sells powder kegs
static s32 sMsgScriptGoronPowderKegSeller[52] = {
    0x1001200,  0x12200008, 0xE0C8E0C,  0x11122010, 0xE0C8F0C,  0x10001240, 0x1D0E0C,   0x800C1112, 0x40001280,
    0x742500,   0xC006F00,  0x13010045, 0xF0C810C,  0x19001300, 0x1280005E, 0x25000C00, 0x59001301, 0x2F0E0C,
    0x810C0F0C, 0x820C0500, 0x1A00,     0x1A300E0C, 0x830C1209, 0x700,      0xE0C84,    0x160C1113, 0x1100E0C,
    0x840C1031, 0xE0C850C,  0x1029FFF2, 0x130200,   0xF0E0C88,  0xC0F0C89,  0xC05000A,  0xFFE3FFE3, 0xE0C860C,
    0x11128019, 0x213019,   0xFFC02900, 0x2C0E0C8C, 0xC050000,  0x50000,    0x8006400,  0x6320E0C,  0x8D0C1030,
    0x14FF9C12, 0x6003400,  0x130034,   0x700000E,  0xC870C16,  0x100E0C8B, 0xC100000,
};
#else
MsgScript sMsgScriptGoronPowderKegSeller[] = {
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

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for the gatekeeper goron in the goron village who opens the shrine gate
static s32 sMsgScriptGoronGatekeeper[27] = {
    0x584000,  0x2903000E, 0x2001301, 0x180058,   0x80005119, 0x1E0059,   0x1004919, 0x160059,  0x2004119,
    0xE0059,   0x4003919,  0x2F0E0D,  0x4D0C1210, 0xE0D480C,  0xF0D490C,  0xF0D4A0C, 0x5000000, 0xF000F30,
    0xE0D4B0C, 0x15090000, 0xE0D4D0C, 0x1210310E, 0xD4C0C12,  0x100E0D4E, 0xC19FFD8, 0xE0D4F0C, 0x19FFD500,
};
#else
MsgScript sMsgScriptGoronGatekeeper[] = {
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

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for one of the goron stretchers at the racetrack (Initially stretching Side to Side while squatting)
static s32 sMsgScriptGoronStretcherA[4] = { 0x100060E, 0xDFE0C12, 0x100E0DFF, 0xC121000 };
#else
MsgScript sMsgScriptGoronStretcherA[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
    /* 0x0003 0x03 */ MSCRIPT_BEGIN_TEXT(0x0DFE),     // It's spring! It's spring! I can't sit still any longer!
    /* 0x0006 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD18(),
    /* 0x0008 0x01 */ MSCRIPT_DONE(),

    /* 0x0009 0x03 */ MSCRIPT_BEGIN_TEXT(0x0DFF), // Darmani! Are you ready? I'm rarin' to go!
    /* 0x000C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000D 0x01 */ MSCRIPT_CMD18(),
    /* 0x000E 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for one of the goron stretchers at the racetrack (Initially doing sidebend stretches with one arm) -
// Unused
static s32 sMsgScriptGoronStretcherB[4] = { 0x100060E, 0xE000C12, 0x100E0E01, 0xC121000 };
#else
MsgScript sMsgScriptGoronStretcherB[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
    /* 0x0003 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E00), // (From Japanese: Haru Goro Haru Goro! Goro, the body starts to move
                                                  // naturally)
    /* 0x0006 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD18(),
    /* 0x0008 0x01 */ MSCRIPT_DONE(),

    /* 0x0009 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E01), // (From Japanese: Darmani, This year, I will win the ground ball.)
    /* 0x000C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000D 0x01 */ MSCRIPT_CMD18(),
    /* 0x000E 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for one of the goron stretchers at the racetrack (Initially shaking out their limbs)
static s32 sMsgScriptGoronStretcherC[4] = { 0x100060E, 0xE020C12, 0x100E0E03, 0xC121000 };
#else
MsgScript sMsgScriptGoronStretcherC[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
    /* 0x0003 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E02),     // Sprint has finally com! I have been waiting for this moment.
    /* 0x0006 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD18(),
    /* 0x0008 0x01 */ MSCRIPT_DONE(),

    /* 0x0009 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E03), // This year is my debut at the races...Please go easy on me
    /* 0x000C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000D 0x01 */ MSCRIPT_CMD18(),
    /* 0x000E 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for one of the goron stretchers (Initially doing sidebend stretches with both arms)
static s32 sMsgScriptGoronStretcherD[4] = { 0x100060E, 0xE040C12, 0x100E0E05, 0xC121000 };
#else
MsgScript sMsgScriptGoronStretcherD[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
    /* 0x0003 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E04),     // Since it has warmed up... my spirits have lifted!
    /* 0x0006 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD18(),
    /* 0x0008 0x01 */ MSCRIPT_DONE(),

    /* 0x0009 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E05), // This year, I'm feeling a little different...
    /* 0x000C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000D 0x01 */ MSCRIPT_CMD18(),
    /* 0x000E 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for the pair of gorons stretching one's hamstrings.
static s32 sMsgScriptGoronStretcherHamstring[4] = { 0x100060E, 0xE060C12, 0x100E0E07, 0xC121000 };
#else
MsgScript sMsgScriptGoronStretcherHamstring[] = {
    /* 0x0000 0x03 */ MSCRIPT_CMD01(0x0009 - 0x0003), // B if Goron
    /* 0x0003 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E06),     // Watch my race!
    /* 0x0006 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0007 0x01 */ MSCRIPT_CMD18(),
    /* 0x0008 0x01 */ MSCRIPT_DONE(),

    /* 0x0009 0x03 */ MSCRIPT_BEGIN_TEXT(0x0E07), // Darmani! Are you entering after all? ...Iguess I'll be last again.
    /* 0x000C 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x000D 0x01 */ MSCRIPT_CMD18(),
    /* 0x000E 0x01 */ MSCRIPT_DONE(),
};
#endif

#if !defined(ENGO_MSGSCRIPT_READY)
// Message script for any sleeping goron
static s32 sMsgScriptGoronSleeping[2] = { 0xE023A0C, 0x12100000 };
#else
MsgScript sMsgScriptGoronSleeping[] = {
    /* 0x0000 0x03 */ MSCRIPT_BEGIN_TEXT(0x023A), // Aha! So the Gorons fall asleep if they hear the Goron's Lullaby!
                                                  // That's convenient...
    /* 0x0003 0x01 */ MSCRIPT_AWAIT_TEXT(),
    /* 0x0004 0x01 */ MSCRIPT_CMD18(),
    /* 0x0005 0x01 */ MSCRIPT_DONE(),
};
#endif

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

// Collider for the frozen solid gorons
static ColliderCylinderInit sCylinderInitFrozen = {
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

// Collider for normal gorons
static ColliderCylinderInit sCylinderInit = {
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
    /* 0x2 */ ENGO_DMGEFF_FIRE = 0x2,
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

/**
 * Animations used in the actor
 *
 * @see EnGoAnimationIndex
 */
static AnimationInfoS sAnimationInfo[] = {

    /* Animations for generic goron actions */
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

    /* Animations for stretching gorons at the racetrack */
    { &gTaisouDoubleArmSideBendAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouSquatSideToSideAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouShakeLimbsAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouSingleArmSidebendAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouHamstringStretchSittingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouCheerAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouShoutAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gTaisouHamstringStretchStandingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },

    /* Animations for the goron brothers during the spring arrival cutscene */
    { &gHakuginShowAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gHakuginShowLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gHakuginLookAroundAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gHakuginLookAroundLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

Actor* EnGo_FindGravemaker(EnGo* this, PlayState* play);
s32 EnGo_ChangeAnimation(EnGo* this, PlayState* play, EnGoAnimationIndex anim);
s32 EnGo_CheckAndChangeCutscene(EnGo* this, s16 indexCutscene);
s32 EnGo_IsEnteringSleep(EnGo* this, PlayState* play);

void EnGo_SetupAction(EnGo* this, PlayState* play);
void EnGo_StretcherGoron_Setup(EnGo* this, PlayState* play);
void EnGo_SpectatorGoron_Setup(EnGo* this, PlayState* play);
void EnGo_GatekeeperGoron_Setup(EnGo* this, PlayState* play);
void EnGo_GraveBroGoron_Setup(EnGo* this, PlayState* play);
void EnGo_ShrineGoron_Setup(EnGo* this, PlayState* play);
void EnGo_PowderKegGoron_Setup(EnGo* this, PlayState* play);

void EnGo_Idle(EnGo* this, PlayState* play);
void EnGo_GraveBroGoron_Gravemaker_Idle(EnGo* this, PlayState* play);
void EnGo_GraveBroGoron_Frozen_Idle(EnGo* this, PlayState* play);

void EnGo_UpdateToCoveringEars(EnGo* this, PlayState* play);
void EnGo_UpdateToShivering(EnGo* this, PlayState* play);
void EnGo_UpdateToStretching(EnGo* this, PlayState* play);
void EnGo_UpdateToSpectating(EnGo* this, PlayState* play);
void EnGo_UpdateToFrozen(EnGo* this, PlayState* play);

void EnGo_Sleep(EnGo* this, PlayState* play);
void EnGo_Talk(EnGo* this, PlayState* play);
void EnGo_Frozen(EnGo* this, PlayState* play);
void EnGo_Thaw(EnGo* this, PlayState* play);
void EnGo_AwaitThaw(EnGo* this, PlayState* play);

s32 EnGo_CheckAndSetupTalk(EnGo* this, PlayState* play);

void EnGo_Gatekeeper_Snowball(EnGo* this, PlayState* play);
void EnGo_Gatekeeper_UpdateToSnowball(EnGo* this, PlayState* play);

void EnGo_GraveBroGoron_CutsceneSpringArrival(EnGo* this, PlayState* play);
s32 EnGo_GraveBroGoron_CheckAndSetupCutsceneSpringArrival(EnGo* this, PlayState* play);

s32 EnGo_GatekeeperGoron_CutsceneOpenShrine(Actor* thisx, PlayState* play);
s32 EnGo_GatekeeperGoron_CutscenePound(EnGo* this, f32 initialVelocity, f32 maxDistortion, s32 maxHangtime);
void EnGo_GatekeeperGoron_CutscenePoundQuake(PlayState* play, s16 quakeSpeed, s16 vertMagnitude, s16 quakeTime);
void EnGo_GatekeeperGoron_CutscenePoundQuakeEffects(EnGo* this, PlayState* play);

s32 EnGo_PowderKegGoron_CutsceneGivePowderKeg(Actor* thisx, PlayState* play);
void EnGo_PowderKegGoron_UpdateColliderRadius(EnGo* this, PlayState* play, s32 isGivenPK);

s32 EnGo_DetectCollisions(EnGo* this, PlayState* play);

void EnGo_UpdateEyes(EnGo* this);

s32 EnGo_UpdateAnimationToCurrent(EnGo* this, PlayState* play);
s32 EnGo_UpdateAttentionTargetAndReactions(EnGo* this, PlayState* play);
s32 EnGo_GraveBroGoron_UpdateAttentionTargetAndReactions(EnGo* this, PlayState* play);
void EnGo_GraveBroGoron_UpdateToSurprised(EnGo* this, PlayState* play);

s32 EnGo_UpdateRotationToTarget(EnGo* this, PlayState* play);

s32 EnGo_UpdateSfx(EnGo* this, PlayState* play);

s32 EnGo_UpdateFocus(EnGo* this);

void EnGo_UpdateCollider(EnGo* this, PlayState* play);
void EnGo_UpdateCollider_Snowball(EnGo* this, PlayState* play);
void EnGo_UpdateCollider_RolledUp(EnGo* this, PlayState* play);
void EnGo_UpdateCollider_Frozen(EnGo* this, PlayState* play);
void EnGo_UpdateCollider_Standing(EnGo* this, PlayState* play);
void EnGo_PowderKegGoron_UpdateCollider(EnGo* this, PlayState* play);
s32 EnGo_Snowball_CanHurtPlayer(PlayState* play);

void EnGo_UpdateEffects(EnGo* this);
void EnGo_UpdateEffect_Snow(EnGoEffect* pEffect, f32 dustConversionHeight);
void EnGo_MakeSteamEffect(EnGo* this);
void EnGo_InitializeEffect_Snow(EnGoEffect* pEffect, Vec3f worldPos);
void EnGo_InitializeEffect_Dust(EnGoEffect* pEffect, Vec3f pos, Vec3f accel, Vec3f vel, f32 scale, f32 deltaScale,
                                s32 maxFrames, EnGoEffectType parentEffectType);
EnGoEffect* EnGo_InitializeEffect_Steam(EnGoEffect* pEffect, Vec3f position, Vec3f acceleration, Vec3f velocity,
                                        f32 scale, f32 deltaScale, s32 maxFrames);

void EnGo_CheckAndDrawIceBlock(EnGo* this, PlayState* play, f32 scale, f32 alpha);
void EnGo_DrawSnow(EnGoEffect* pEffect, PlayState* play, Gfx* material, Gfx* model, u8 effectType);
void EnGo_DrawDust(EnGoEffect* pEffect, PlayState* play2);
void EnGo_DrawSteam(EnGoEffect* pEffect, PlayState* play2);
void EnGo_DrawEffects(EnGo* this, PlayState* play);

/**
 * Initialize the 2nd Half of the effect objects to be of type ENGO_EFFECT_STEAM.
 *
 * @param pEffect Pointer to the latter half of the EnGoEffect Table.
 * @param position Initial position
 * @param acceleration Initial acceleration
 * @param velocity Initial velocity
 * @param scale Initial scale
 * @param deltaScale How much the effect scales per frame (additive)
 * @param maxFrames Maximum number of frames the effect will last. Actual lifetime will be 1/3 * maxFrames -> maxFrames
 */
EnGoEffect* EnGo_InitializeEffect_Steam(EnGoEffect* pEffect, Vec3f position, Vec3f acceleration, Vec3f velocity,
                                        f32 scale, f32 deltaScale, s32 maxFrames) {
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

/**
 * Draw all effects of type ENGO_EFFECT_STEAM.
 *
 * @param pEffect First element in EnGoEffect table.
 */
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

/**
 * Initialize the 2nd Half of the effect objects to be of type ENGO_EFFECT_DUST<1|2|3>.
 *
 * @param pEffect Pointer to the latter half of the EnGoEffect Table.
 * @param position Initial position
 * @param acceleration Initial acceleration
 * @param velocity Initial velocity
 * @param scale Initial scale
 * @param deltaScale How much the effect scales per frame (additive)
 * @param maxFrames Maximum number of frames the effect will last. Actual lifetime will be 1/3 * maxFrames -> maxFrames
 * @param parentEffectType Type of the parent effect, determines which of the possible dust effects correspond
 */
void EnGo_InitializeEffect_Dust(EnGoEffect* pEffect, Vec3f pos, Vec3f accel, Vec3f vel, f32 scale, f32 deltaScale,
                                s32 maxFrames, EnGoEffectType parentEffectType) {
    s32 i;

    for (i = (ENGO_NUM_EFFECTS / 2); i < ENGO_NUM_EFFECTS; i++, pEffect++) {
        if (pEffect->effectType != ENGO_EFFECT_NONE)
            continue;

        pEffect->effectType = parentEffectType + ENGO_EFFECT_DUST_START;
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

/**
 * Draw all effects of type ENGO_EFFECT_DUST<1|2|3>.
 *
 * @param pEffect First element in EnGoEffect table.
 */
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

/**
 * Initialize the Snowball Break effects
 *
 * Half of the elements will be ENGO_EFFECT_SNOW<1|2|3> randomly generated around the character. The second half
 * will be dedicated ENGO_EFFECT_DUST<1|2|3> paired with the snow.
 *
 * @param pEffect Pointer to the EnGoEffect Table.
 * @param position Actor's current world position
 */
void EnGo_InitializeEffect_Snow(EnGoEffect* pEffect, Vec3f worldPos) {
    static u8 effectIndexToSnowEffectTable[] = {
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
        pEffect->rotVelocity.x = (Rand_ZeroOne() - 0.5f) * (f32)0x1554;
        pEffect->rotVelocity.y = (Rand_ZeroOne() - 0.5f) * (f32)0x1554;
        pEffect->rotVelocity.z = (Rand_ZeroOne() - 0.5f) * (f32)0x1554;

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
        pEffect->effectType = effectIndexToSnowEffectTable[i];

        // Initialize the parameters for the paired element
        randRelativeToWorldPos.x = ((Rand_ZeroOne() - 0.5f) * 80.0f) + pEffect->position.x;
        randRelativeToWorldPos.y = ((Rand_ZeroOne() - 0.5f) * 40.0f) + pEffect->position.y;
        randRelativeToWorldPos.z = ((Rand_ZeroOne() - 0.5f) * 80.0f) + pEffect->position.z;

        randYOneToFour = gZeroVec3f;
        randYOneToFour.y = (Rand_ZeroOne() * 3.0f) + 1.0f;

        // Initialize the paired element.
        EnGo_InitializeEffect_Dust(pEnd, randRelativeToWorldPos, gZeroVec3f, randYOneToFour, 0.6f, 0.2f,
                                   ENGO_DUST_STEAM_LIFETIME, 0);
    }
}

/**
 * Update the snow effect's movement.
 *
 * When the snow drops to the ground, it is converted to dust.
 *
 * @param pEffect Effect to update
 * @param dustConversionHeight  Height at which to conver the effect to dust
 */
void EnGo_UpdateEffect_Snow(EnGoEffect* pEffect, f32 dustConversionHeight) {
    f32 test;
    f32 test2;
    f32 x;
    f32 z;

    pEffect->position.x += pEffect->velocity.x;
    pEffect->position.y += pEffect->velocity.y;
    pEffect->position.z += pEffect->velocity.z;

    pEffect->velocity.y += pEffect->acceleration.y;
    pEffect->scaleXY += pEffect->scaleXYDelta;

    if (pEffect->position.y < dustConversionHeight) {
        pEffect->position.y = dustConversionHeight;

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

/**
 * Draw all effects of type ENGO_EFFECT_SNOW<1|2|3>.
 *
 * @param pEffect Pointer to first half of the EnGoEffect table.
 * @param material Snow Material
 * @param model Snow Model
 * @param effectType Snow Effect type to draw
 */
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

/**
 * Update all effects, potentially fading them away to nothing.
 */
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

/**
 * Draw all Effects
 */
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
s32 EnGo_Snowball_CanHurtPlayer(PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((player->transformation == PLAYER_FORM_GORON) && (player->stateFlags3 & PLAYER_STATE3_2000000)) {
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

/**
 * Update the actor's focus
 */
s32 EnGo_UpdateFocus(EnGo* this) {
    static Vec3f sPowderKegSellerPos = { 0.0f, 100.0f, 160.0f };
    s32 pad;
    f32 yAxisOffsetToFocusPoint = 58.0f;

    if (ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &sPowderKegSellerPos,
                                      &this->actor.focus.pos);
    } else {
        if ((this->actionFlags & ENGO_FLAG_ROLLEDUP) || (this->actionFlags & ENGO_FLAG_SNOWBALLED)) {
            yAxisOffsetToFocusPoint = this->actor.shape.yOffset;
        }
        Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
        this->actor.focus.pos.y += yAxisOffsetToFocusPoint;
    }

    this->actor.focus.rot.x = this->actor.world.rot.x;
    this->actor.focus.rot.y = this->actor.world.rot.y;
    this->actor.focus.rot.z = this->actor.world.rot.z;
    return false;
}

/**
 * Collider Update for the Rolling Snowball form of the Gatekeeper
 */
void EnGo_UpdateCollider_Snowball(EnGo* this, PlayState* play) {
    Vec3f worldPos;

    Math_Vec3f_Copy(&worldPos, &this->actor.world.pos);

    this->colliderSphere.dim.worldSphere.center.x = worldPos.x;
    this->colliderSphere.dim.worldSphere.center.y = worldPos.y;
    this->colliderSphere.dim.worldSphere.center.y += (s16)this->actor.shape.yOffset;
    this->colliderSphere.dim.worldSphere.center.z = worldPos.z;

    this->colliderSphere.dim.modelSphere.radius = 48;
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;

    if (EnGo_Snowball_CanHurtPlayer(play)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->colliderSphere.base);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderSphere.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

/**
 * Collider Update for the Powder Keg Seller
 */
void EnGo_PowderKegGoron_UpdateCollider(EnGo* this, PlayState* play) {
    this->colliderSphere.dim.worldSphere.radius =
        this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderSphere.base);
}

/**
 * Collider Update for the curled form of the gorons
 */
void EnGo_UpdateCollider_RolledUp(EnGo* this, PlayState* play) {
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

/**
 * Collider Update for the frozen form of the goron
 */
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

/**
 * Collider Update for all standing forms of the goron
 */
void EnGo_UpdateCollider_Standing(EnGo* this, PlayState* play) {
    Math_Vec3f_ToVec3s(&this->colliderCylinder.dim.pos, &this->actor.world.pos);
    this->colliderCylinder.dim.radius = 24;
    this->colliderCylinder.dim.height = 62;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
}

/**
 * Update the collider for the goron.
 *
 * Both the Rolling Snowball and Frozen forms can attack on collision, others do not.
 */
void EnGo_UpdateCollider(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags2 & PLAYER_STATE2_4000)) {
        DECR(this->harmlessTimer);
    }
    if (ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) {
        EnGo_PowderKegGoron_UpdateCollider(this, play);
    } else if (this->actionFlags & ENGO_FLAG_SNOWBALLED) {
        EnGo_UpdateCollider_Snowball(this, play);
    } else if (this->actionFlags & ENGO_FLAG_ROLLEDUP) {
        EnGo_UpdateCollider_RolledUp(this, play);
    } else if (this->actionFlags & ENGO_FLAG_FROZEN) {
        EnGo_UpdateCollider_Frozen(this, play);
    } else {
        EnGo_UpdateCollider_Standing(this, play);
    }
}

/**
 * Check if the actor is talking, and if so set the action function to handle it.
 *
 * @return True if talking.
 */
s32 EnGo_CheckAndSetupTalk(EnGo* this, PlayState* play) {
    if (!(this->actionFlags & 7) || !Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        return false;
    }

    if ((ENGO_GET_TYPE(&this->actor) != ENGO_PKEG_SELLER) && //
        (ENGO_GET_TYPE(&this->actor) != ENGO_STRETCHER)) {
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
    this->gatekeeperAnimState = 0;
    this->interruptedActionFn = this->actionFunc;
    this->actionFunc = EnGo_Talk;
    return true;
}

/**
 * Detect any collisions, and convert detections to object specific actionFlags
 */
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

/**
 * Start, or finish, the cutscene for the arrival of springtime.
 */
s32 EnGo_GraveBroGoron_CheckAndSetupCutsceneSpringArrival(EnGo* this, PlayState* play) {
    const u8 CS_ACTION_INVALID = UINT8_MAX;

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_GRAVEBRO) && (play->csCtx.state != 0) && (this->actor.draw != NULL) &&
        (play->sceneNum == SCENE_10YUKIYAMANOMURA2) && (gSaveContext.sceneSetupIndex == 1) &&
        (play->csCtx.currentCsIndex == 0)) {
        if (this->springArrivalCutsceneActive == false) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->springArrivalCurrentCsAction = CS_ACTION_INVALID;
            this->springArrivalCutsceneActive = true;
            this->interruptedActionFn = this->actionFunc;
        }
        SubS_UpdateFlags(&this->actionFlags, 0, 7);
        this->actionFunc = EnGo_GraveBroGoron_CutsceneSpringArrival;
    } else if (this->springArrivalCutsceneActive) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->springArrivalCurrentCsAction = CS_ACTION_INVALID;
        this->springArrivalCutsceneActive = false;
        SubS_UpdateFlags(&this->actionFlags, 3, 7);
        this->actionFunc = this->interruptedActionFn;
    }

    return false;
}

/**
 * Update the Animation to the actor's currently set value
 *
 * @return true of non-repeating animation has finished
 */
s32 EnGo_UpdateAnimationToCurrent(EnGo* this, PlayState* play) {
    s8 objIdx = this->actor.objBankIndex;
    s8 objIdx2 = -1;
    s32 ret = false;

    if ((this->currAnimIndex >= ENGO_ANIM_HAKUGIN_START) && (this->indexHakuginDemo >= 0)) {
        objIdx2 = this->indexHakuginDemo;
    } else if ((this->currAnimIndex >= ENGO_ANIM_TAISOU_START) && (this->indexTaisou >= 0)) {
        objIdx2 = this->indexTaisou;
    } else if (this->currAnimIndex < ENGO_ANIM_TAISOU_START) {
        objIdx2 = this->actor.objBankIndex;
    }

    if (objIdx2 >= 0) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx2].segment);
        this->skelAnime.playSpeed = this->currAnimPlaySpeed;
        ret = SkelAnime_Update(&this->skelAnime);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx].segment);
    }

    return ret;
}

/**
 * Update Sound Effects based on animation.
 */
s32 EnGo_UpdateSfx(EnGo* this, PlayState* play) {
    if (play->csCtx.state == 0) {
        if (this->currAnimIndex == ENGO_ANIM_ROLL) {
            if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_CIRCLE);
            }

            if (Animation_OnFrame(&this->skelAnime, 22.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_SIT_IMT);
            }
        } else if ((this->currAnimIndex == ENGO_ANIM_UNROLL) || (this->currAnimIndex == ENGO_ANIM_UNROLL_IMM)) {
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
 * Change the Goron's animation.
 *
 * Goron animations come from one of three categories
 * - Basic Goron animations
 * - Goron Gymnastics like Stretches, Cheers, etc... (Taisou)
 * - Spring has Arrived Cutscene Animationstodo (Hakugin)
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
        this->currAnimIndex = anim;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, anim);
        this->currAnimPlaySpeed = this->skelAnime.playSpeed;
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[objIdx].segment);
    }

    return ret;
}

/**
 * Update the eye textures to blink.
 */
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

/**
 * Play the surprise animation then return to shivering.
 */
void EnGo_GraveBroGoron_UpdateToSurprised(EnGo* this, PlayState* play) {
    if (this->surprisePhase == 0) {
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVERINGSURPRISED);
        this->surprisePhase++;
    } else if ((this->surprisePhase == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER_IMM);
        this->surprisePhase++;
    }
}

/**
 * Change the Attention Target, and dialog reactions of the Gorons outside Darmani's grave.
 */
s32 EnGo_GraveBroGoron_UpdateAttentionTargetAndReactions(EnGo* this, PlayState* play) {
    u16 textId = play->msgCtx.currentTextId;
    Player* player = GET_PLAYER(play);

    if (ENGO_GET_TYPE(&this->actor) != ENGO_GRAVEBRO) {
        return false;
    }

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        if (this->lastTextId != textId) {
            switch (textId) {
                case 0xE1A: // Hunh? What  have I been doing?
                    this->actionFlags |= ENGO_FLAG_ENGAGED;
                    this->attentionTarget = this->actor.child;
                    break;

                case 0xE1D: // You hear this guy? The great Darmani died long ago and is lying in his gr...
                case 0xE25: // ...Really? I don't know who you are, but thank you!
                    if (ENGO_GET_SUBTYPE(&this->actor) == ENGO_GRAVEBRO_FROZEN) {
                        this->attentionTarget = &GET_PLAYER(play)->actor;
                    }
                    break;

                case 0xE27: // What's this?
                    if (ENGO_GET_SUBTYPE(&this->actor) == ENGO_GRAVEBRO_FROZEN) {
                        this->attentionTarget = this->actor.child;
                    }

                case 0xE16: // Y-you're...No! No, you're not the great Darmani, are you?
                case 0xE1E: // Heeee!!! Darmani!
                    this->graveBroDialogActionFn = EnGo_GraveBroGoron_UpdateToSurprised;
                    break;

                case 0xE1F: // I was shocked, too. But somehow, it seems the great Darmani isn't dead.
                    if (ENGO_GET_SUBTYPE(&this->actor) == ENGO_GRAVEBRO_GRAVEMAKER) {
                        this->attentionTarget = &GET_PLAYER(play)->actor;
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
        this->graveBroDialogActionFn = NULL;
        this->lastTextId = 0;
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
        this->actionFlags &= ~ENGO_FLAG_ENGAGED;
    }

    if (this->graveBroDialogActionFn != NULL) {
        this->graveBroDialogActionFn(this, play);
    }

    return false;
}

/**
 * Update the actors rotation to point towards the target.
 */
s32 EnGo_UpdateRotationToTarget(EnGo* this, PlayState* play) {
    s32 pad;
    Vec3f targetPos;
    Vec3f thisPos;
    s16 desiredYaw;

    Math_Vec3f_Copy(&targetPos, &this->attentionTarget->world.pos);
    Math_Vec3f_Copy(&thisPos, &this->actor.world.pos);
    desiredYaw = Math_Vec3f_Yaw(&thisPos, &targetPos);

    Math_ApproachS(&this->headRotY, (desiredYaw - this->bodyRotY) - this->actor.shape.rot.y, 4, 0x2AA8); // 60 degree
    this->headRotY = CLAMP(this->headRotY, -0x1FFE, 0x1FFE);                                             // +-45 degrees

    Math_ApproachS(&this->bodyRotY, (desiredYaw - this->headRotY) - this->actor.shape.rot.y, 4, 0x2AA8); // 60 degree
    this->bodyRotY = CLAMP(this->bodyRotY, -0x1C70, 0x1C70);                                             // +-40 degrees

    Math_Vec3f_Copy(&thisPos, &this->actor.focus.pos);
    if (this->attentionTarget->id == ACTOR_PLAYER) {
        targetPos.y = ((Player*)this->attentionTarget)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&targetPos, &this->attentionTarget->focus.pos);
    }

    Math_ApproachS(&this->headRotZ, Math_Vec3f_Pitch(&thisPos, &targetPos) - this->bodyRotZ, 4, 0x2AA8); // 60 degree
    this->headRotZ = CLAMP(this->headRotZ, -0x1554, 0x1554);                                             // +-30 degrees

    Math_ApproachS(&this->bodyRotZ, Math_Vec3f_Pitch(&thisPos, &targetPos) - this->headRotZ, 4, 0x2AA8); // 60 degree
    this->bodyRotZ = CLAMP(this->bodyRotZ, -0xE38, 0xE38);                                               // +-20 degrees

    return false;
}

/**
 * Handle updating of goron's attention target, and reactions during dialog.
 */
s32 EnGo_UpdateAttentionTargetAndReactions(EnGo* this, PlayState* play) {
    if (!this->changedText) {
        this->attentionTarget = &GET_PLAYER(play)->actor;
    }

    EnGo_GraveBroGoron_UpdateAttentionTargetAndReactions(this, play);

    if (this->actionFlags & ENGO_FLAG_ENGAGED) {
        this->actionFlags &= ~ENGO_FLAG_LOST_ATTENTION;
        this->actionFlags |= ENGO_FLAG_FACE_TARGET;
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

/**
 * Idle action function for the gravemaker brother
 */
void EnGo_GraveBroGoron_Gravemaker_Idle(EnGo* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 deltaYaw = BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y);

    if ((fabsf(this->actor.playerHeightRel) > 20.0f) || (this->actor.xzDistToPlayer > 300.0f)) {
        SubS_UpdateFlags(&this->actionFlags, 3, 7);
    } else if ((player->transformation != PLAYER_FORM_GORON) || (ABS_ALT(deltaYaw) >= 0x1C70 /* 40 degrees */) ||
               (gSaveContext.save.weekEventReg[21] & WE_21_2_SPOKE_TO_GRAVEMAKER_AS_GORON) ||
               (gSaveContext.save.weekEventReg[21] & WE_21_3_THAWED_GRAVEMAKERS_BROTHER)) {
        SubS_UpdateFlags(&this->actionFlags, 3, 7);
    } else {
        SubS_UpdateFlags(&this->actionFlags, 4, 7);
    }
}

/**
 * Idle action function for the frozen brother
 */
void EnGo_GraveBroGoron_Frozen_Idle(EnGo* this, PlayState* play) {
    if (gSaveContext.save.weekEventReg[21] & WE_21_3_THAWED_GRAVEMAKERS_BROTHER) {
        SubS_UpdateFlags(&this->actionFlags, 3, 7);
    } else {
        SubS_UpdateFlags(&this->actionFlags, 4, 7);
    }
}

/**
 * Obtain a pointer to the gravemaker brother.
 */
Actor* EnGo_FindGravemaker(EnGo* this, PlayState* play) {
    Actor* actor;
    Actor* retActor = NULL;

    while (true) {
        actor = SubS_FindActor(play, retActor, ACTORCAT_NPC, ACTOR_EN_GO);
        retActor = actor;

        if ((actor != NULL) && ((EnGo*)actor != this) && //
            (ENGO_GET_TYPE(actor) == ENGO_GRAVEBRO) &&   //
            (ENGO_GET_SUBTYPE(actor) == ENGO_GRAVEBRO_GRAVEMAKER)) {
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
void EnGo_PowderKegGoron_UpdateColliderRadius(EnGo* this, PlayState* play, s32 isGivenPK) {
    if ((gSaveContext.save.weekEventReg[18] & WE_18_7_HAS_PK_PRIVLEDGES) ||
        (play->actorCtx.unk5 & 1) // Same check occurs in PowderKeg ammo check MessageScript Command
        || isGivenPK) {
        this->colliderSphere.dim.modelSphere.radius = 300;
    } else {
        this->colliderSphere.dim.modelSphere.radius = 380;
    }
}

/**
 * Helper to change cutscenes.
 *
 * @return true when changed.
 */
s32 EnGo_CheckAndChangeCutscene(EnGo* this, s16 indexCutscene) {
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
s32 EnGo_GatekeeperGoron_CutscenePound(EnGo* this, f32 initialVelocity, f32 maxDistortion, s32 maxHangtime) {
    s32 pad;
    f32 rotAndDistortFactor = 1.0f;
    f32 velocity = this->actor.velocity.y + this->actor.gravity;
    s32 isFinished;

    if (this->actor.bgCheckFlags & 2) { // Settled to the Ground
        // Transition 3->DONE
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
            // PHASE 3: Goron is falling (Just letting gravity take effect)
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

/**
 * Create the quake caused by the gatekeeper's pound.
 */
void EnGo_GatekeeperGoron_CutscenePoundQuake(PlayState* play, s16 quakeSpeed, s16 vertMagnitude, s16 quakeTime) {
    s16 indexQuake = Quake_Add(Play_GetCamera(play, CAM_ID_MAIN), 3);

    Quake_SetCountdown(indexQuake, quakeTime);
    Quake_SetSpeed(indexQuake, quakeSpeed);
    Quake_SetQuakeValues(indexQuake, vertMagnitude, 0, 0, 0);
}

/**
 * Create the visual effects caused by the gatekeeper's pound.
 */
void EnGo_GatekeeperGoron_CutscenePoundQuakeEffects(EnGo* this, PlayState* play) {
    EnGo_GatekeeperGoron_CutscenePoundQuake(play, 0x6C77, 7, 20);
    play->actorCtx.unk2 = 4;
    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_TEST, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, 0);
    EffectSsBlast_SpawnWhiteShockwave(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f);
}

/**
 * Draw the Ice encasing frozen gorons
 */
void EnGo_CheckAndDrawIceBlock(EnGo* this, PlayState* play, f32 scale, f32 alpha) {
    u32 y1;
    u32 y2;

    if (this->actionFlags & ENGO_FLAG_FROZEN) {
        Matrix_Push();

        OPEN_DISPS(play->state.gfxCtx);

        func_8012C2DC(play->state.gfxCtx);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(scale * 0.7f, scale * 0.8f, scale, MTXMODE_APPLY);
        func_800B8118(&this->actor, play, 0);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        y1 = play->gameplayFrames % 256;
        y2 = (play->gameplayFrames * 2) % 256;
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, y1, 0x20, 0x10, 1, 0, y2, 0x40, 0x20));
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 100, (u8)alpha);
        gSPDisplayList(POLY_XLU_DISP++, gEffIceFragment3DL);

        CLOSE_DISPS(play->state.gfxCtx);

        Matrix_Pop();
    }
}

/**
 * Initialize the steam effect used for melting ice.
 */
void EnGo_MakeSteamEffect(EnGo* this) {
    static Vec3f accel = { 0.0f, 0.06f, 0.0f };
    Vec3f tempPos;
    Vec3f effectPos;
    s16 rotAngle = Rand_ZeroOne() * 360.0f * 182.0f;

    Math_Vec3f_Copy(&tempPos, &gZeroVec3f);
    tempPos.z = 28.0f;
    Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, rotAngle, &tempPos, &effectPos);
    effectPos.y = (Rand_ZeroOne() * 10.0f) + 4.0f;
    effectPos.y += this->actor.floorHeight;
    EnGo_InitializeEffect_Steam(&this->effectTable[ENGO_NUM_EFFECTS / 2], effectPos, accel, gZeroVec3f,
                                ENGO_NORMAL_SCALE, (0.2f * ENGO_NORMAL_SCALE), ENGO_DUST_STEAM_LIFETIME);
}

/**
 * Transition through the cutscenes when the gatekeeper is opening the shrine.
 *
 * @return true when cutscenes end.
 */
s32 EnGo_GatekeeperGoron_CutsceneOpenShrine(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    EnGo* this = THIS;
    s32 ret = false;

    switch (this->cutsceneState) {
        case 0:
            this->indexCutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            if (EnGo_CheckAndChangeCutscene(this, this->indexCutscene)) {
                this->gatekeeperAnimState = 1;
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
            if (EnGo_CheckAndChangeCutscene(this, this->indexCutscene)) {
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

    switch (this->gatekeeperAnimState) {
        case 1:
            EnGo_ChangeAnimation(this, play, ENGO_ANIM_ROLL);
            this->actionFlags |= ENGO_FLAG_ROLLINGUP;
            this->gatekeeperAnimState++;
            break;

        case 2:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                this->actionFlags &= ~ENGO_FLAG_ROLLINGUP;
                this->actionFlags &= ~ENGO_FLAG_STANDING;
                this->actionFlags |= ENGO_FLAG_ROLLEDUP;
                this->gatekeeperAnimState++;
                this->cutsceneDelayTimer = 0;
                this->actor.shape.yOffset = ENGO_ROLLEDUP_Y_OFFSET;
            }
            break;

        case 3:
            this->cutsceneDelayTimer++;
            if (this->cutsceneDelayTimer >= 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_JUMP);
                this->actor.velocity.y = ENGO_POUND_RISE_VEL;
                this->actor.gravity = ENGO_NORMAL_GRAVITY;
                this->gatekeeperAnimState++;
            }
            break;

        case 4:
            if (EnGo_GatekeeperGoron_CutscenePound(this, ENGO_POUND_RISE_VEL, (0.4f) * ENGO_NORMAL_SCALE, 6)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_LAND_BIG);
                EnGo_GatekeeperGoron_CutscenePoundQuakeEffects(this, play);
                this->gatekeeperAnimState++;
                this->cutsceneDelayTimer = 0;
                gSaveContext.save.weekEventReg[88] |= WE_88_6_GATEKEEPER_OPENED_SHRINE;
            }
            break;

        case 5:
            this->cutsceneDelayTimer++;
            if (this->cutsceneDelayTimer >= 10) {
                EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
                this->actor.shape.rot.x = 0;
                this->actionFlags &= ~ENGO_FLAG_ROLLEDUP;
                this->actionFlags |= ENGO_FLAG_STANDING;
                this->gatekeeperAnimState++;
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
s32 EnGo_PowderKegGoron_CutsceneGivePowderKeg(Actor* thisx, PlayState* play) {
    static Vec3f sPowderKegSpawnOffset = { 0.0f, 200.0f, 280.0f };
    EnGo* this = THIS;
    Vec3f powderKegSpawnPos;
    s32 ret = false;

    switch (this->cutsceneState) {
        case 0:
            this->indexCutscene = this->actor.cutscene;
            if (EnGo_CheckAndChangeCutscene(this, this->indexCutscene)) {
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
                EnGo_PowderKegGoron_UpdateColliderRadius(this, play, true);
                this->cutsceneDelayTimer = 0;
                this->cutsceneState++;
            }
            break;

        case 3:
            if (this->cutsceneDelayTimer >= 60) {
                ActorCutscene_Stop(this->indexCutscene);
                this->cutsceneDelayTimer = 0;
                this->cutsceneState = 0;
                ret = true;
            } else {
                this->cutsceneDelayTimer++;
            }
            break;
    }

    return ret;
}

/**
 * Update the stretching racer's animation and action flags
 *
 * EnGoGoronRaceSubtypes A-D exchange animations before and after the race, while the Hamstring Stretchers
 * have the same animation every time.
 *
 * @see EnGo_Idle
 */
void EnGo_UpdateToStretching(EnGo* this, PlayState* play) {
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
    if (this->currAnimIndex == ENGO_ANIM_SITTING_STRETCH) {

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
 * Update the Goron's Animation and Action Flags to Spectating
 *
 * Spectators engage in one of two cheering animations. Either Cheering with their hands above their head, or
 * cupping their hands infront of their faces and shouting.
 *
 * @see EnGo_Idle
 */
void EnGo_UpdateToSpectating(EnGo* this, PlayState* play) {
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
 * Update the Goron's Animation/Action Flags to Frozen
 *
 * The Goron will shiver upon awakening, but is otherwise encased in a block of ice which deals damage upon contact.
 *
 * @see EnGo_Frozen
 */
void EnGo_UpdateToFrozen(EnGo* this, PlayState* play) {
    Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInitFrozen);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->currAnimIndex = -1;
    EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHIVER);
    this->sleepState = ENGO_AWAKE;
    this->iceBlockScale = (this->scaleFactor / 0.01f) * 0.9f;
    this->eyeTexIndex = ENGO_EYETEX_CLOSED;
    this->actionFlags = ENGO_FLAG_NONE;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFlags |= ENGO_FLAG_FROZEN;
    this->iceBlockAlpha = 100.0f;
}

/**
 * Update the Goron Gatekeeper's Animation and Action Flags to Snowball
 *
 * @see EnGo_Gatekeeper_Snowball
 */
void EnGo_Gatekeeper_UpdateToSnowball(EnGo* this, PlayState* play) {
    s16 yawToPathPoint;
    Vec3f currentPos;
    Vec3f startingPathPoint;

    Math_Vec3f_Copy(&currentPos, &this->actor.world.pos);
    if (this->gatekeeperPath != NULL) {
        this->actor.flags &= ~ACTOR_FLAG_2000000;
        SubS_CopyPointFromPathCheckBounds(this->gatekeeperPath, 0, &startingPathPoint);
        yawToPathPoint = Math_Vec3f_Yaw(&currentPos, &startingPathPoint);
        this->actor.shape.rot.y = yawToPathPoint;
        this->actor.world.rot.y = yawToPathPoint;
    }
    this->actionFlags = ENGO_FLAG_NONE;
    this->actionFlags |= ENGO_FLAG_SNOWBALLED;
    this->actor.shape.yOffset = ENGO_SNOWBALL_Y_OFFSET;
    this->actor.gravity = ENGO_NORMAL_GRAVITY;
}

/**
 * Update the Goron's Animation and Action Flags to Covering Ears
 *
 * @see EnGo_Idle
 */
void EnGo_UpdateToCoveringEars(EnGo* this, PlayState* play) {
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
 * Update the Goron's Animation and Action Flags to Shivering.
 *
 * @see EnGo_Idle
 */
void EnGo_UpdateToShivering(EnGo* this, PlayState* play) {
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
 * Setup a goron stretching at the racetrack.
 *
 * Stretching gorons placed in the starting area of the racetrack doing various stretches.
 */
void EnGo_StretcherGoron_Setup(EnGo* this, PlayState* play) {
    if (((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 0)) ||
         (gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 2))) &&
        (gSaveContext.save.weekEventReg[33] & 0x80)) {
        EnGo_UpdateToStretching(this, play);
        this->actionFunc = EnGo_Idle;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * Setup a goron spectating at the racetrack.
 *
 * Spectators to the goron races cannot be engaged, they simply stand idle and cheer.
 */
void EnGo_SpectatorGoron_Setup(EnGo* this, PlayState* play) {
    if ((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1)) ||
        (gSaveContext.save.entrance == ENTRANCE(CUTSCENE, 0))) {
        EnGo_UpdateToSpectating(this, play);
        this->actionFunc = EnGo_Idle;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * Setup the Goron Shrine GateKeeper.
 *
 * When spoken to, can open the Goron Shrine for the player.
 * - On Day 1: Can be found in the open, shivering
 * - On Days 2,3: Can be found in a snowball.
 */
void EnGo_GatekeeperGoron_Setup(EnGo* this, PlayState* play) {
    if (gSaveContext.save.day >= 2) {
        this->gatekeeperPath = SubS_GetDayDependentPath(play, ENGO_GET_7F80(&this->actor), 0xFF, &this->indexPathPoint);
        if (this->gatekeeperPath != NULL) {
            this->indexPathPoint = 1;
        }
        EnGo_Gatekeeper_UpdateToSnowball(this, play);
        this->actionFunc = EnGo_Gatekeeper_Snowball;
        this->msgEventCb = EnGo_GatekeeperGoron_CutsceneOpenShrine;
    } else {
        EnGo_UpdateToShivering(this, play);
        this->actionFunc = EnGo_Idle;
        this->msgEventCb = EnGo_GatekeeperGoron_CutsceneOpenShrine;
    }
}

/**
 * Setup a goron Brother at Darmani's Grave
 *
 * The Goron Brothers are together, one shivering from the cold, another frozen solid.
 */
void EnGo_GraveBroGoron_Setup(EnGo* this, PlayState* play) {
    if ((ENGO_GET_SUBTYPE(&this->actor) == ENGO_GRAVEBRO_FROZEN) &&
        (((play->sceneNum == SCENE_10YUKIYAMANOMURA2) && /* Snow Mountain Village */
          (gSaveContext.sceneSetupIndex == 1) && (play->csCtx.currentCsIndex == 0)) ||
         !(gSaveContext.save.weekEventReg[21] & WE_21_3_THAWED_GRAVEMAKERS_BROTHER))) {
        this->actor.child = EnGo_FindGravemaker(this, play);
        this->actor.child->child = &this->actor;
        EnGo_UpdateToFrozen(this, play);
        this->actionFunc = EnGo_Frozen;
    } else {
        EnGo_UpdateToShivering(this, play);
        this->actionFunc = EnGo_Idle;
    }
}

/**
 * Setup a Shrine Goron.
 *
 * There are three, but they all behave the same way aside from dialog.
 */
void EnGo_ShrineGoron_Setup(EnGo* this, PlayState* play) {
    if (!(gSaveContext.save.weekEventReg[22] & WE_22_2_GK_CALMED)) {
        EnGo_UpdateToCoveringEars(this, play);
        this->actionFunc = EnGo_Idle;
    } else {
        EnGo_UpdateToShivering(this, play);
        this->actionFunc = EnGo_Idle;
    }
}

/**
 * Setup the PowderKeg Seller Goron.
 *
 * This goron sells powder kegs, and gives the player a PowderKeg as part of a challenge to gain
 * the privledge to buy them.
 */
void EnGo_PowderKegGoron_Setup(EnGo* this, PlayState* play) {
    EnGo_PowderKegGoron_UpdateColliderRadius(this, play, false);
    EnGo_ChangeAnimation(this, play, ENGO_ANIM_LYINGDOWNIDLE);
    this->scaleFactor *= ENGO_BIGGORON_SCALE_MULTIPLIER;
    Actor_SetScale(&this->actor, this->scaleFactor);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.targetMode = 3;
    this->actionFlags = ENGO_FLAG_NONE;
    this->actor.gravity = ENGO_NORMAL_GRAVITY;
    SubS_UpdateFlags(&this->actionFlags, 3, 7);
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFlags |= ENGO_FLAG_EYESOPEN;
    this->msgEventCb = EnGo_PowderKegGoron_CutsceneGivePowderKeg;
    this->actionFunc = EnGo_Idle;
}

/**
 * Default Setup function as the initial action function
 */
void EnGo_SetupAction(EnGo* this, PlayState* play) {
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

        this->currAnimIndex = ENGO_ANIM_INVALID;
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_UNROLL);
        this->actor.draw = EnGo_Draw;

        Collider_InitAndSetSphere(play, &this->colliderSphere, &this->actor, &sSphereInit);
        Collider_InitAndSetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
        Effect_Add(play, &this->indexEffect, EFFECT_TIRE_MARK, 0, 0, &tireMarkInit);

        this->actor.targetMode = 1;
        this->scaleFactor = ENGO_NORMAL_SCALE;
        this->msgEventCb = NULL;

        switch (ENGO_GET_TYPE(&this->actor)) {
            case ENGO_STRETCHER:
                EnGo_StretcherGoron_Setup(this, play);
                break;
            case ENGO_SPECTATOR:
                EnGo_SpectatorGoron_Setup(this, play);
                break;
            case ENGO_GATEKEEPER:
                EnGo_GatekeeperGoron_Setup(this, play);
                break;
            case ENGO_GRAVEBRO:
                EnGo_GraveBroGoron_Setup(this, play);
                break;
            case ENGO_ASIDE_STORE:
            case ENGO_ASIDE_ELDERSROOM:
            case ENGO_ASIDE_ELDERSSON:
                EnGo_ShrineGoron_Setup(this, play);
                break;
            case ENGO_PKEG_SELLER:
                EnGo_PowderKegGoron_Setup(this, play);
                break;
            default:
                Actor_MarkForDeath(&this->actor);
                break;
        }
    }
}

/**
 * Default action for the gorons. Different types have different default actions.
 *
 * The Default Action possibilities include...
 * - Shivering
 * - Covering Ears
 * - Spectating (Cheering or Shouting)
 * - Stretching (Side-to-side squatting, two-arm Sidebend, Limb Shake, 1-arm side-bend, hamstring stretching while
 * sitting, and helping the hamstring stretching goron.)
 */
void EnGo_Idle(EnGo* this, PlayState* play) {
    s16 targetRot = this->actor.world.rot.y;

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_SPECTATOR) &&
        (gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1))) {
        // Spectators only cheer. No other interactions
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_GORON_CHEER - SFX_FLAG);
    } else if (ENGO_GET_TYPE(&this->actor) != ENGO_PKEG_SELLER) {
        // All others besides the Powder Keg Seller can be slept,
        if (EnGo_IsEnteringSleep(this, play)) {
            SubS_UpdateFlags(&this->actionFlags, 0, 7);
            this->sleepState = ENGO_ASLEEP_POS;
            this->actionFunc = EnGo_Sleep;
        } else if (ENGO_GET_TYPE(&this->actor) == ENGO_GRAVEBRO) {
            switch (ENGO_GET_SUBTYPE(&this->actor)) {
                case ENGO_GRAVEBRO_GRAVEMAKER:
                    EnGo_GraveBroGoron_Gravemaker_Idle(this, play);
                    break;

                case ENGO_GRAVEBRO_FROZEN:
                    EnGo_GraveBroGoron_Frozen_Idle(this, play);
                    break;
            }
        } else if (ENGO_GET_TYPE(&this->actor) == ENGO_STRETCHER) {
            if (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x3FFC) {
                SubS_UpdateFlags(&this->actionFlags, 3, 7);
            } else {
                SubS_UpdateFlags(&this->actionFlags, 0, 7);
            }
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, targetRot, 4, 0x2AA8);
}

/**
 * Handles the entry into sleep, as well as snoring while asleep
 */
void EnGo_Sleep(EnGo* this, PlayState* play) {
    s16 targetRot = this->actor.world.rot.y;
    u16 sfxId;

    if (EnGo_IsEnteringSleep(this, play)) {
        this->sleepState = ENGO_ASLEEP_POS;
    }

    if (this->actionFlags & ENGO_FLAG_ROLLINGUP) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->actionFlags &= ~ENGO_FLAG_ROLLINGUP;
            this->actionFlags |= ENGO_FLAG_ROLLEDUP;
            if (this->sleepState != ENGO_AWAKE) {
                this->snorePhase = 0;
            }
            this->actor.shape.yOffset = ENGO_ROLLEDUP_Y_OFFSET;
        }
    } else if (this->actionFlags & ENGO_FLAG_UNROLLING) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->actionFlags |= ENGO_FLAG_STANDING;
            this->actionFlags &= ~ENGO_FLAG_UNROLLING;
        }
    } else if (this->actionFlags & ENGO_FLAG_ROLLEDUP) {
        if ((this->actor.xzDistToPlayer < 160.0f) && (this->actor.playerHeightRel < 20.0f) &&
            (this->sleepState == ENGO_AWAKE)) {
            EnGo_ChangeAnimation(this, play, ENGO_ANIM_UNROLL_IMM);
            this->actionFlags &= ~ENGO_FLAG_STANDING;
            this->actionFlags &= ~ENGO_FLAG_ROLLEDUP;
            this->actionFlags |= ENGO_FLAG_UNROLLING;
            this->actor.shape.yOffset = ENGO_STANDING_Y_OFFSET;
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
            this->snorePhase += 0x400; // ~5.7 degrees per frame or ~1/3 rotation per second.
            this->actor.shape.yOffset = (this->actor.scale.y / this->scaleFactor) * ENGO_ROLLEDUP_Y_OFFSET;
            SubS_UpdateFlags(&this->actionFlags, 3, 7);
        }
    } else if ((this->actor.xzDistToPlayer >= 240.0f) || (this->actor.playerHeightRel >= 20.0f) ||
               (this->sleepState != ENGO_AWAKE)) {
        EnGo_ChangeAnimation(this, play, ENGO_ANIM_ROLL);
        this->actionFlags &= ~ENGO_FLAG_STANDING;
        this->actionFlags &= ~ENGO_FLAG_ROLLEDUP;
        this->actionFlags |= ENGO_FLAG_ROLLINGUP;
        this->actor.shape.yOffset = ENGO_STANDING_Y_OFFSET;
    }

    SubS_FillLimbRotTables(play, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
    Math_ApproachS(&this->actor.shape.rot.y, targetRot, 4, 0x2AA8);
}

/**
 * Action function for a frozen goron
 *
 * Transitions to the thawing cutscene
 */
void EnGo_Frozen(EnGo* this, PlayState* play) {
    Actor* actorCollidedWith = this->colliderCylinder.base.ac;

    if ((this->actionFlags & ENGO_FLAG_HIT_BY_OTHER) &&
        (((actorCollidedWith != NULL) && (actorCollidedWith->id == ACTOR_OBJ_AQUA) &&
          (actorCollidedWith->params & 1)) ||
         (this->actor.colChkInfo.damageEffect == ENGO_DMGEFF_FIRE))) {
        this->actionFunc = EnGo_AwaitThaw;
    }
}

/**
 * Action Function for transitioning to thawing
 */
void EnGo_AwaitThaw(EnGo* this, PlayState* play) {
    if (EnGo_CheckAndChangeCutscene(this, this->actor.cutscene)) {
        this->actionFunc = EnGo_Thaw;
    }
}

/**
 * Action function for thawing of the goron, melting sounds, and steam.
 *
 */
void EnGo_Thaw(EnGo* this, PlayState* play) {
    EnGo* unfrozenBro = (EnGo*)this->actor.child;

    if ((s32)(this->iceBlockScale * 3.0f) != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
        Math_ApproachF(&this->iceBlockScale, 0.0f, 0.02f, 1.0f);
        this->iceBlockAlpha = (this->iceBlockScale / 0.9f) * 100.0f;
        EnGo_MakeSteamEffect(this);
    } else {
        ActorCutscene_Stop(this->actor.cutscene);
        EnGo_UpdateToShivering(this, play);
        if ((ENGO_GET_TYPE(&this->actor) == ENGO_GRAVEBRO) &&
            (ENGO_GET_SUBTYPE(&this->actor) == ENGO_GRAVEBRO_FROZEN)) {
            SubS_UpdateFlags(&this->actionFlags, 4, 7);
            EnGo_UpdateToShivering(unfrozenBro, play);
            unfrozenBro->actionFunc = EnGo_Idle;
        }
        this->actionFunc = EnGo_Idle;
    }
}

/**
 * Cutscene action function for the arrival of springtime
 *
 * This cutscene consists of:
 * - The non-frozen brother stops shivering and looks around.
 * - The frozen brother thaws and shivers briefly.
 * - The non-frozen brother pats his brother on the back and shows him the change in temperature.
 * - They both look around
 * - They both cheer.
 */
void EnGo_GraveBroGoron_CutsceneSpringArrival(EnGo* this, PlayState* play) {
    s32 animationIndices[] = {
        ENGO_ANIM_LYINGDOWNIDLE, ENGO_ANIM_UNROLL, ENGO_ANIM_SHIVER_IMM, ENGO_ANIM_LOOK_AROUND,
        ENGO_ANIM_SHOW,          ENGO_ANIM_SHIVER, ENGO_ANIM_SHIVER,     ENGO_ANIM_CHEER,
    };
    u16 actorActionCmd = 0;
    s32 csAction;
    s32 actionIndex;

    switch (ENGO_GET_SUBTYPE(&this->actor)) {
        case ENGO_GRAVEBRO_GRAVEMAKER:
            actorActionCmd = 128;
            break;

        case ENGO_GRAVEBRO_FROZEN:
            actorActionCmd = 129;
            break;
    }

    if ((actorActionCmd == 128) || (actorActionCmd == 129)) {
        if (Cutscene_CheckActorAction(play, actorActionCmd)) {
            actionIndex = Cutscene_GetActorActionIndex(play, actorActionCmd);
            csAction = play->csCtx.actorActions[actionIndex]->action;

            if (this->springArrivalCurrentCsAction != (u8)csAction) {
                this->springArrivalCurrentCsAction = csAction;
                EnGo_ChangeAnimation(this, play, animationIndices[csAction]);
                this->actionFlags = ENGO_FLAG_NONE;
                this->actionFlags |= ENGO_FLAG_EYESOPEN;
                this->eyeTexIndex = ENGO_EYETEX_OPEN;
                this->iceBlockScale = 0.0f;
                this->iceBlockAlpha = 0.0f;

                switch (csAction) {
                    case 1:
                        this->actionFlags |= ENGO_FLAG_STANDING;
                        this->skelAnime.curFrame = this->skelAnime.endFrame;
                        break;

                    case 5:
                    case 6:
                        EnGo_UpdateToFrozen(this, play);
                        break;
                }
            }

            switch (this->springArrivalCurrentCsAction) {
                case 3:
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) &&
                        (this->currAnimIndex == ENGO_ANIM_LOOK_AROUND)) {
                        EnGo_ChangeAnimation(this, play, ENGO_ANIM_LOOK_AROUND_LOOPED);
                    }
                    break;

                case 4:
                    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame) &&
                        (this->currAnimIndex == ENGO_ANIM_SHOW)) {
                        EnGo_ChangeAnimation(this, play, ENGO_ANIM_SHOW_LOOPED);
                    }
                    break;

                case 6:
                    if ((s32)(this->iceBlockScale * 3.0f) != 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_MELT_LEVEL - SFX_FLAG);
                        Math_ApproachF(&this->iceBlockScale, 0.0f, 0.02f, 1.0f);
                        this->iceBlockAlpha = (this->iceBlockScale / 0.9f) * 100.0f;
                        EnGo_MakeSteamEffect(this);
                    } else if (this->actionFlags & ENGO_FLAG_FROZEN) {
                        EnGo_UpdateToShivering(this, play);
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
 * Action function for the Gatekeeper while they're in a snowball.
 *
 * On Day 2, they'll roll along a set path, and can be halted with certain attacks.
 * On Day 3, they're frozen solid.
 */
void EnGo_Gatekeeper_Snowball(EnGo* this, PlayState* play) {
    Vec3s* pPathPoints;
    Vec3f currentPos;
    Vec3f currentPathPoint;

    if ((this->actionFlags & ENGO_FLAG_HIT_BY_OTHER) && (this->actor.colChkInfo.damageEffect == ENGO_DMGEFF_BREAK)) {
        // Stop the Gatekeeper when hit by an appropriate effect
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SNOWBALL_BROKEN);
        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;
        EnGo_InitializeEffect_Snow(this->effectTable, this->actor.world.pos);
        this->actor.shape.rot.x = 0;
        this->actor.speedXZ = 0.0f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GOLON_COLD);

        if (gSaveContext.save.day == 3) {
            EnGo_UpdateToFrozen(this, play);
            this->actionFunc = EnGo_Frozen;
        } else {
            EnGo_UpdateToShivering(this, play);
            this->actionFunc = EnGo_Idle;
        }
    } else if (this->gatekeeperPath != NULL) {
        if (this->actionFlags & ENGO_FLAG_HIT_OTHER) {
            func_800B8E58(GET_PLAYER(play), NA_SE_PL_BODY_HIT);
            func_800B8D50(play, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f, 0);
        }

        pPathPoints = Lib_SegmentedToVirtual(this->gatekeeperPath->points);
        if (SubS_HasReachedPoint(&this->actor, this->gatekeeperPath, this->indexPathPoint)) {
            if (this->indexPathPoint >= (this->gatekeeperPath->count - 1)) {
                this->indexPathPoint = 0;
            } else {
                this->indexPathPoint++;
            }
        }

        Math_Vec3s_ToVec3f(&currentPathPoint, &pPathPoints[this->indexPathPoint]);
        Math_Vec3f_Copy(&currentPos, &this->actor.world.pos);
        Math_ApproachS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&currentPos, &currentPathPoint), 4,
                       0x38E /* 5 degrees */);
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

/**
 * Return the message script appropriate for the actor
 *
 * @returns Message Script corresponding to the actor
 */
s32* EnGo_GetMessageScript(EnGo* this, PlayState* play) {
    static s32 D_80A16704[] = {
        /* ENGO_GRAVEBRO */ sMsgScriptGoronGravemaker,
        /* ENGO_FROZEBRO */ sMsgScriptGoronBrother,
    };

    if (this->sleepState != ENGO_AWAKE) {
        return sMsgScriptGoronSleeping; // Lullaby Hint
    }

    if (ENGO_GET_TYPE(&this->actor) == ENGO_STRETCHER) {
        switch (ENGO_GET_SUBTYPE(&this->actor) % 6) {
            case ENGO_STRETCHER_A:
                return sMsgScriptGoronStretcherA;
            case ENGO_STRETCHER_B: // Unused!
                return sMsgScriptGoronStretcherB;
            case ENGO_STRETCHER_C:
                return sMsgScriptGoronStretcherC;
            case ENGO_STRETCHER_D:
                return sMsgScriptGoronStretcherD;
            case ENGO_STRETCHER_HAMSTRINGSIT:
                return sMsgScriptGoronStretcherHamstring;
            case ENGO_STRETCHER_HAMSTRINGSTAND:
                return sMsgScriptGoronStretcherHamstring;
        }
    }

    switch (ENGO_GET_TYPE(&this->actor)) {
        case ENGO_GATEKEEPER:
            return sMsgScriptGoronGatekeeper;
        case ENGO_GRAVEBRO:
            return D_80A16704[ENGO_GET_SUBTYPE(&this->actor)];
        case ENGO_ASIDE_STORE:
            return sMsgScriptGoronAsideStore;
        case ENGO_ASIDE_ELDERSROOM:
            return sMsgScriptGoronAsideEldersRoom;
        case ENGO_ASIDE_ELDERSSON:
            return sMsgScriptGoronAsideEldersSon;
        case ENGO_PKEG_SELLER:
            return sMsgScriptGoronPowderKegSeller;
        default:
            return sMsgScriptGoronAsideStore;
    }
}

/**
 * Action function for dialog, movement due to dialog, and ending dialog
 */
void EnGo_Talk(EnGo* this, PlayState* play) {
    s32 pad;
    Vec3f targetPos;
    Vec3f thisPos;

    if (!func_8010BF58(&this->actor, play, EnGo_GetMessageScript(this, play), this->msgEventCb,
                       &this->msgScriptResumePos)) {
        if ((ENGO_GET_TYPE(&this->actor) != ENGO_STRETCHER) && !(this->actionFlags & ENGO_FLAG_ROLLEDUP)) {
            Math_Vec3f_Copy(&targetPos, &this->attentionTarget->world.pos);
            Math_Vec3f_Copy(&thisPos, &this->actor.world.pos);
            Math_ApproachS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&thisPos, &targetPos), 4, 0x2AA8 /* 60 degrees */);
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
    SubS_UpdateFlags(&this->actionFlags, 3, 7);
    this->msgScriptResumePos = 0;
    this->actionFlags |= ENGO_FLAG_LOST_ATTENTION;
    this->actionFunc = this->interruptedActionFn;
}

/**
 *  Initialize the goron, deferring most of the work to the first Update cycle.
 */
void EnGo_Init(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;

    this->indexTaisou = SubS_GetObjectIndex(OBJECT_TAISOU, play);
    this->indexHakuginDemo = SubS_GetObjectIndex(OBJECT_HAKUGIN_DEMO, play);
    this->actionFunc = EnGo_SetupAction;
}

/**
 *  Destroy the goron.
 */
void EnGo_Destroy(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;

    Collider_DestroyCylinder(play, &this->colliderCylinder);
    Collider_DestroySphere(play, &this->colliderSphere);
    Effect_Destroy(play, this->indexEffect);
}

/**
 * Update function for the Goron
 */
void EnGo_Update(Actor* thisx, PlayState* play) {
    EnGo* this = THIS;
    f32 xzRange;

    EnGo_DetectCollisions(this, play);

    if (!EnGo_CheckAndSetupTalk(this, play)) {
        EnGo_GraveBroGoron_CheckAndSetupCutsceneSpringArrival(this, play);
    }

    this->actionFunc(this, play);

    if (!(this->actionFlags & ENGO_FLAG_FROZEN)) {
        EnGo_UpdateEyes(this);
        EnGo_UpdateAnimationToCurrent(this, play);
        EnGo_UpdateAttentionTargetAndReactions(this, play);
        EnGo_UpdateSfx(this, play);
    }

    if (!(this->actionFlags & ENGO_FLAG_SNOWBALLED) && !(this->actionFlags & ENGO_FLAG_ROLLEDUP) &&
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
        (ENGO_GET_TYPE(&this->actor) != ENGO_STRETCHER)) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
    }

    EnGo_UpdateFocus(this);
    EnGo_UpdateCollider(this, play);
    EnGo_UpdateEffects(this);
}

/**
 *  Draw function for a Snowballed or RolledUp goron (no need to draw limbs).
 */
void EnGo_Draw_Limbless(EnGo* this, PlayState* play) {
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

/**
 * OverrideLimbDrawOpa function for the Gorons
 */
s32 EnGo_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGo* this = THIS;
    Vec3f worldPos;
    s32 idx;

    if ((ENGO_GET_TYPE(&this->actor) == ENGO_PKEG_SELLER) && (limbIndex == ENGO_LIMB_INDEX_BODY)) {
        Matrix_MultZero(&worldPos);
        worldPos.y = this->actor.world.pos.y;
        Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &worldPos);
    }

    switch (limbIndex) {
        case ENGO_LIMB_INDEX_BODY:
            idx = 0;
            break;

        case ENGO_LIMB_INDEX_LEFTARM:
            idx = 1;
            break;

        case ENGO_LIMB_INDEX_RIGHTARM:
            idx = 2;
            break;

        default:
            idx = 9;
            break;
    }

    if ((this->actionFlags & ENGO_FLAG_STANDING) && (idx < 9)) {
        rot->y += (s16)(Math_SinS(this->limbRotTableY[idx]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->limbRotTableZ[idx]) * 200.0f);
    }
    return false;
}

/**
 * TransformLimbDrawOpa function for the Gorons
 */
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

/**
 * Draw function
 *
 * Draws the goron in any/all forms, and the effects swawned off of them.
 * Examples include:
 * - Regular animations
 * - Gorons Encased in ice (Gatekeeper and GraveDigger's brother)
 * - Gatekeeper's rolling snowball
 * - Snow, Dust, and Steam effects coming off gorons (When breaking the snowball or melting the ice)
 */
void EnGo_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80A1670C[] = {
        gGoronEyeOpenTex, gGoronEyeHalfTex, gGoronEyeClosedTex, gGoronEyeHalfTex, gGoronEyeClosed2Tex,
    };
    EnGo* this = THIS;

    if (!(this->actionFlags & (ENGO_FLAG_SNOWBALLED | ENGO_FLAG_ROLLEDUP))) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C28C(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A1670C[this->eyeTexIndex]));

        if (this->currAnimIndex == ENGO_ANIM_SITTING_STRETCH) {
            Matrix_Translate(0.0f, 0.0f, -4000.0f, MTXMODE_APPLY);
        }
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnGo_OverrideLimbDraw, NULL, EnGo_TransfromLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        EnGo_Draw_Limbless(this, play);
    }
    EnGo_CheckAndDrawIceBlock(this, play, this->iceBlockScale, this->iceBlockAlpha);
    EnGo_DrawEffects(this, play);
}
