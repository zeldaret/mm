#ifndef Z64ACTOR_H
#define Z64ACTOR_H

#include "PR/ultratypes.h"
#include "z64math.h"
#include "z64animation.h"
#include "z64collision_check.h"
#include "unk.h"

// This value is hardcoded to be the size of ovl_Arrow_Fire which currently is the biggest actor that uses the AM_FIELD.
#define AM_FIELD_SIZE SEGMENT_SIZE(ovl_Arrow_Fire)
#define MASS_IMMOVABLE 0xFF // Cannot be pushed by OC collisions
#define MASS_HEAVY 0xFE     // Can only be pushed by OC collisions with IMMOVABLE and HEAVY objects.

struct Actor;
struct GlobalContext;
struct Lights;
struct CollisionPoly;

struct EnBox;

typedef void(*ActorFunc)(struct Actor* this, struct GlobalContext* globalCtx);

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3s rot;
} PosRot; // size = 0x14

typedef struct {
    /* 0x00 */ u8 attack[32];
} DamageTable; // size = 0x20

typedef struct {
    /* 0x00 */ u8 health;
    /* 0x02 */ s16 cylRadius;
    /* 0x04 */ s16 cylHeight;
    /* 0x06 */ u8 mass;
} CollisionCheckInfoInit;

typedef struct {
    /* 0x00 */ u8 health;
    /* 0x02 */ s16 cylRadius;
    /* 0x04 */ s16 cylHeight;
    /* 0x06 */ s16 cylYShift;
    /* 0x08 */ u8 mass;
} CollisionCheckInfoInit2; // size = 0xC

typedef struct {
    /* 0x00 */ DamageTable* damageTable;
    /* 0x04 */ Vec3f displacement;
    /* 0x10 */ s16 cylRadius;
    /* 0x12 */ s16 cylHeight;
    /* 0x14 */ s16 cylYShift;
    /* 0x16 */ u8 mass;
    /* 0x17 */ u8 health;
    /* 0x18 */ u8 damage;
    /* 0x19 */ u8 damageEffect;
    /* 0x1A */ u8 atHitEffect;
    /* 0x1B */ u8 acHitEffect;
} CollisionCheckInfo; // size = 0x1C

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
} ActorEnTest20C; // size = 0x3C

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8 type;
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ ActorFunc init;
    /* 0x14 */ ActorFunc destroy;
    /* 0x18 */ ActorFunc update;
    /* 0x1C */ ActorFunc draw;
} ActorInit; // size = 0x20

typedef enum {
    ALLOCTYPE_NORMAL,
    ALLOCTYPE_ABSOLUTE,
    ALLOCTYPE_PERMANENT
} AllocType;

typedef struct {
    /* 0x00 */ u32 vromStart;
    /* 0x04 */ u32 vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ ActorInit* initInfo;
    /* 0x18 */ char* name;
    /* 0x1C */ u16 allocType; // bit 0: don't allocate memory, use actorContext->0x250? bit 1: Always keep loaded?
    /* 0x1E */ s8 numLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20

typedef void(*ActorShadowFunc)(struct Actor* actor, struct Lights* mapper, struct GlobalContext* globalCtx);

typedef struct {
    /* 0x00 */ Vec3s rot; // Current actor shape rotation
    /* 0x06 */ s16 face; // Used to index eyebrow/eye/mouth textures. Only used by player
    /* 0x08 */ f32 yOffset; // Model y axis offset. Represents model space units
    /* 0x0C */ ActorShadowFunc shadowDraw; // Shadow draw function
    /* 0x10 */ f32 shadowScale; // Changes the size of the shadow
    /* 0x14 */ u8 shadowAlpha; // Default is 255
    /* 0x15 */ u8 feetFloorFlags; // Set if the actor's foot is clipped under the floor. & 1 is right foot, & 2 is left
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ Vec3f feetPos[2]; // Update by using `Actor_SetFeetPos` in PostLimbDrawOpa
} ActorShape; // size = 0x30

typedef struct Actor {
    /* 0x000 */ s16 id; // Actor ID
    /* 0x002 */ u8 category; // Actor category. Refer to the corresponding enum for values
    /* 0x003 */ s8 room; // Room number the actor is in. -1 denotes that the actor won't despawn on a room change
    /* 0x004 */ u32 flags; // Flags used for various purposes
    /* 0x008 */ PosRot home; // Initial position/rotation when spawned. Can be used for other purposes
    /* 0x01C */ s16 params; // Configurable variable set by the actor's spawn data; original name: "args_data"
    /* 0x01E */ s8 objBankIndex; // Object bank index of the actor's object dependency; original name: "bank"
    /* 0x01F */ s8 targetMode; // Controls how far the actor can be targeted from and how far it can stay locked on
    /* 0x020 */ s16 unk20;
    /* 0x024 */ PosRot world; // Position/rotation in the world
    /* 0x038 */ s8 cutscene;
    /* 0x039 */ u8 audioFlags; // Another set of flags? Seems related to sfx or bgm
    /* 0x03C */ PosRot focus; // Target reticle focuses on this position. For player this represents head pos and rot
    /* 0x050 */ u16 sfxId; // Id of sound effect to play. Plays when value is set, then is cleared the following update cycle
    /* 0x054 */ f32 targetArrowOffset; // Height offset of the target arrow relative to `focus` position
    /* 0x058 */ Vec3f scale; // Scale of the actor in each axis
    /* 0x064 */ Vec3f velocity; // Velocity of the actor in each axis
    /* 0x070 */ f32 speedXZ; // How fast the actor is traveling along the XZ plane
    /* 0x074 */ f32 gravity; // Acceleration due to gravity. Value is added to Y velocity every frame
    /* 0x078 */ f32 terminalVelocity; // Sets the lower bounds cap on velocity along the Y axis
    /* 0x07C */ struct CollisionPoly* wallPoly; // Wall polygon the actor is touching
    /* 0x080 */ struct CollisionPoly* floorPoly; // Floor polygon directly below the actor
    /* 0x084 */ u8 wallBgId; // Bg ID of the wall polygon the actor is touching
    /* 0x085 */ u8 floorBgId; // Bg ID of the floor polygon directly below the actor
    /* 0x086 */ s16 wallYaw; // Y rotation of the wall polygon the actor is touching
    /* 0x088 */ f32 floorHeight; // Y position of the floor polygon directly below the actor
    /* 0x08C */ f32 depthInWater; // Directed distance to the surface of active waterbox. Negative value means water is below.
    /* 0x090 */ u16 bgCheckFlags; // See comments below actor struct for wip docs. TODO: macros for these flags
    /* 0x092 */ s16 yawTowardsPlayer; // Y rotation difference between the actor and the player
    /* 0x094 */ f32 xyzDistToPlayerSq; // Squared distance between the actor and the player in the x,y,z axis
    /* 0x098 */ f32 xzDistToPlayer; // Distance between the actor and the player in the XZ plane
    /* 0x09C */ f32 playerHeightRel; // Directed distance is negative if the player is below.
    /* 0x0A0 */ CollisionCheckInfo colChkInfo; // Variables related to the Collision Check system
    /* 0x0BC */ ActorShape shape; // Variables related to the physical shape of the actor
    /* 0x0EC */ Vec3f projectedPos; // Position of the actor in projected space
    /* 0x0F8 */ f32 projectedW; // w component of the projected actor position
    /* 0x0FC */ f32 uncullZoneForward; // Amount to increase the uncull zone forward by (in projected space)
    /* 0x100 */ f32 uncullZoneScale; // Amount to increase the uncull zone scale by (in projected space)
    /* 0x104 */ f32 uncullZoneDownward; // Amount to increase uncull zone downward by (in projected space)
    /* 0x108 */ Vec3f prevPos; // World position from the previous update cycle
    /* 0x114 */ u8 isTargeted; // Set to true if the actor is currently being targeted by the player
    /* 0x115 */ u8 targetPriority; // Lower values have higher priority. Resets to 0 when player stops targeting
    /* 0x116 */ u16 textId; // Text ID to pass to link/display when interacting with the actor
    /* 0x118 */ u16 freezeTimer; // Actor does not update when set. Timer decrements automatically
    /* 0x11A */ u16 colorFilterParams; // Set color filter to red, blue, or white. Toggle opa or xlu
    /* 0x11C */ u8 colorFilterTimer; // A non-zero value enables the color filter. Decrements automatically
    /* 0x11D */ u8 isDrawn; // Set to true if the actor is currently being drawn. Always stays false for lens actors
    /* 0x11E */ u8 dropFlag; // Configures what item is dropped by the actor from `Item_DropCollectibleRandom`
    /* 0x11F */ u8 hintId; // Sets what 0600 dialog to display when talking to Tatl. Default 0xFF
    /* 0x120 */ struct Actor* parent; // Usage is actor specific. Set if actor is spawned via `Actor_SpawnAsChild`
    /* 0x124 */ struct Actor* child; // Usage is actor specific. Set if actor is spawned via `Actor_SpawnAsChild`
    /* 0x128 */ struct Actor* prev; // Previous actor of this category
    /* 0x12C */ struct Actor* next; // Next actor of this category
    /* 0x130 */ ActorFunc init; // Initialization Routine. Called by `Actor_InitContext` or `Actor_UpdateAll`
    /* 0x134 */ ActorFunc destroy; // Destruction Routine. Called by `Actor_Destroy`
    /* 0x138 */ ActorFunc update; // Update Routine. Called by `Actor_UpdateAll`
    /* 0x13C */ ActorFunc draw; // Draw Routine. Called by `Actor_Draw`
    /* 0x140 */ ActorOverlay* overlayEntry; // Pointer to the overlay table entry for this actor
} Actor; // size = 0x144

typedef enum {
    /* 0 */ FOOT_LEFT,
    /* 1 */ FOOT_RIGHT
} ActorFootIndex;

/**
 * BgCheckFlags WIP documentation (logical masks):
 * 0x001 : Standing on the ground
 * 0x002 : Has touched the ground (only active for 1 frame)
 * 0x004 : Has left the ground (only active for 1 frame)
 * 0x008 : Touching a wall
 * 0x010 : Touching a ceiling
 * 0x020 : On or below water surface
 * 0x040 : Has touched water (actor is responsible for unsetting this the frame it touches the water)
 * 0x080 : Similar to & 0x1 but with no velocity check and is cleared every frame
 * 0x100 : Crushed between a floor and ceiling (triggers a void for player)
 * 0x200 : Unknown (only set/used by player so far)
 */

typedef struct {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 bgId;
    /* 0x148 */ f32 pushForce;
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ s16 yRotation;
    /* 0x152 */ u16 unk152;
    /* 0x154 */ u32 flags;
    /* 0x158 */ u8 stateFlags;
    /* 0x15A */ s16 pad15A;
} DynaPolyActor; // size = 0x15C

typedef enum {
    /* 0x00 */ ITEM00_RUPEE_GREEN,
    /* 0x01 */ ITEM00_RUPEE_BLUE,
    /* 0x02 */ ITEM00_RUPEE_RED,
    /* 0x03 */ ITEM00_HEART,
    /* 0x04 */ ITEM00_BOMBS_A,
    /* 0x05 */ ITEM00_ARROWS_10,
    /* 0x06 */ ITEM00_HEART_PIECE,
    /* 0x07 */ ITEM00_HEART_CONTAINER,
    /* 0x08 */ ITEM00_ARROWS_30,
    /* 0x09 */ ITEM00_ARROWS_40,
    /* 0x0A */ ITEM00_ARROWS_50,
    /* 0x0B */ ITEM00_BOMBS_B,
    /* 0x0C */ ITEM00_NUTS_1,
    /* 0x0D */ ITEM00_STICK,
    /* 0x0E */ ITEM00_MAGIC_LARGE,
    /* 0x0F */ ITEM00_MAGIC_SMALL,
    /* 0x10 */ ITEM00_MASK,
    /* 0x11 */ ITEM00_SMALL_KEY,
    /* 0x12 */ ITEM00_FLEXIBLE,
    /* 0x13 */ ITEM00_RUPEE_HUGE,
    /* 0x14 */ ITEM00_RUPEE_PURPLE,
    /* 0x15 */ ITEM00_3_HEARTS,
    /* 0x16 */ ITEM00_SHIELD_HERO,
    /* 0x17 */ ITEM00_NUTS_10,
    /* 0x18 */ ITEM00_NOTHING,
    /* 0x19 */ ITEM00_BOMBS_0,
    /* 0x1A */ ITEM00_BIG_FAIRY,
    /* 0x1B */ ITEM00_MAP,
    /* 0x1C */ ITEM00_COMPASS,
    /* 0x1D */ ITEM00_MUSHROOM_CLOUD,

    /* 0xFF */ ITEM00_NO_DROP = -1
} Item00Type;

struct EnItem00;

typedef void (*EnItem00ActionFunc)(struct EnItem00*, struct GlobalContext*);

typedef struct EnItem00 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnItem00ActionFunc actionFunc;
    /* 0x148 */ s16 collectibleFlag;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ f32 unk154;
    /* 0x158 */ ColliderCylinder collider;
    /* 0x1A4 */ s8 unk1A4;
} EnItem00; // size = 0x1A8

struct EnAObj;

typedef void (*EnAObjActionFunc)(struct EnAObj*, struct GlobalContext*);

typedef struct EnAObj {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnAObjActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder collision;
    /* 0x194 */ UNK_TYPE1 pad194[0x14];
} EnAObj; // size = 0x1A8

typedef enum {
    /* 0x00 */ ACTORCAT_SWITCH,
    /* 0x01 */ ACTORCAT_BG,
    /* 0x02 */ ACTORCAT_PLAYER,
    /* 0x03 */ ACTORCAT_EXPLOSIVES,
    /* 0x04 */ ACTORCAT_NPC,
    /* 0x05 */ ACTORCAT_ENEMY,
    /* 0x06 */ ACTORCAT_PROP,
    /* 0x07 */ ACTORCAT_ITEMACTION,
    /* 0x08 */ ACTORCAT_MISC,
    /* 0x09 */ ACTORCAT_BOSS,
    /* 0x0A */ ACTORCAT_DOOR,
    /* 0x0B */ ACTORCAT_CHEST,
    /* 0x0C */ ACTORCAT_MAX
} ActorType;

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ Color_RGBA8 color;
} TargetContextEntry; // size = 0x14

typedef struct TargetContext {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f targetCenterPos;
    /* 0x18 */ Color_RGBAf fairyInner;
    /* 0x28 */ Color_RGBAf fairyOuter;
    /* 0x38 */ Actor* arrowPointedActor;
    /* 0x3C */ Actor* targetedActor;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ s16 unk48; // alpha
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ s8 unk4C;
    /* 0x4D */ UNK_TYPE1 pad4D[0x3];
    /* 0x50 */ TargetContextEntry unk50[3];
    /* 0x8C */ Actor* unk8C;
    /* 0x90 */ Actor* bgmEnemy;
    /* 0x94 */ Actor* unk_94;
} TargetContext; // size = 0x98

typedef struct {
    /* 0x0 */ TexturePtr texture;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
    /* 0x8 */ u8 width;
    /* 0x9 */ u8 height;
    /* 0xA */ u8 durationTimer; // how long the title card appears for before fading
    /* 0xB */ u8 delayTimer; // how long the title card waits to appear
    /* 0xC */ s16 alpha;
    /* 0xE */ s16 intensity;
} TitleCardContext; // size = 0x10

typedef struct ActorContext_unk_20C {
    /* 0x0 */ s16 id;
    /* 0x2 */ s8 isDynamicallyInitialised;
    /* 0x4 */ void* ptr;
} ActorContext_unk_20C; // size = 0x8

typedef struct ActorContextFlags {
    /* 0x00 */ u32 switches[4]; // First 0x40 are permanent, second 0x40 are temporary
    /* 0x10 */ u32 chest;
    /* 0x14 */ u32 clearedRoom;
    /* 0x18 */ u32 clearedRoomTemp;
    /* 0x1C */ u32 collectible[4]; // bitfield of 128 bits
} ActorContextFlags; // size = 0x2C

typedef struct ActorListEntry {
    /* 0x0 */ s32 length; // number of actors loaded of this type
    /* 0x4 */ Actor* first; // pointer to first actor of this type
    /* 0x8 */ s32 unk_08;
} ActorListEntry; // size = 0xC

typedef struct ActorContext {
    /* 0x000 */ u8 freezeFlashTimer;
    /* 0x001 */ UNK_TYPE1 pad1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ s8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ UNK_TYPE1 pad6[0x5];
    /* 0x00B */ s8 unkB;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 totalLoadedActors;
    /* 0x00F */ u8 undrawnActorCount;
    /* 0x010 */ ActorListEntry actorLists[ACTORCAT_MAX];
    /* 0x0A0 */ Actor* undrawnActors[32]; // Records the first 32 actors drawn each frame
    /* 0x120 */ TargetContext targetContext;
    /* 0x1B8 */ ActorContextFlags flags;
    /* 0x1E4 */ TitleCardContext titleCtxt;
    /* 0x1F4 */ u8 unk1F4;
    /* 0x1F5 */ u8 unk1F5;
    /* 0x1F6 */ UNK_TYPE1 pad1F6[0x2];
    /* 0x1F8 */ f32 unk1F8;
    /* 0x1FC */ Vec3f unk1FC;
    /* 0x208 */ UNK_TYPE1 unk_208[0x4];
    /* 0x20C */ ActorContext_unk_20C unk_20C[8];
    /* 0x24C */ UNK_TYPE1 unk_24C[0x4];
    /* 0x250 */ void* absoluteSpace; // Space used to allocate actor overlays of alloc type ALLOCTYPE_ABSOLUTE
    /* 0x254 */ u32 unk254[5];
    /* 0x268 */ u8 unk268;
    /* 0x269 */ UNK_TYPE1 pad269[0x3];
    /* 0x26C */ Input unk_26C;
} ActorContext; // size = 0x284

typedef enum {
    /* 00 */ ACTOR_DRAW_DMGEFF_FIRE,
    /* 01 */ ACTOR_DRAW_DMGEFF_BLUE_FIRE,
    /* 10 */ ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX = 10,
    /* 11 */ ACTOR_DRAW_DMGEFF_FROZEN_SFX,
    /* 20 */ ACTOR_DRAW_DMGEFF_LIGHT_ORBS = 20,
    /* 21 */ ACTOR_DRAW_DMGEFF_BLUE_LIGHT_ORBS,
    /* 30 */ ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL = 30,
    /* 31 */ ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM,
    /* 32 */ ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_LARGE
} ActorDrawDamageEffectType;

typedef enum {
    /* 0x000 */ ACTOR_PLAYER,
    /* 0x001 */ ACTOR_EN_TEST,
    /* 0x002 */ ACTOR_EN_GIRLA,
    /* 0x003 */ ACTOR_EN_PART,
    /* 0x004 */ ACTOR_EN_LIGHT,
    /* 0x005 */ ACTOR_EN_DOOR,
    /* 0x006 */ ACTOR_EN_BOX,
    /* 0x007 */ ACTOR_EN_PAMETFROG,
    /* 0x008 */ ACTOR_EN_OKUTA,
    /* 0x009 */ ACTOR_EN_BOM,
    /* 0x00A */ ACTOR_EN_WALLMAS,
    /* 0x00B */ ACTOR_EN_DODONGO,
    /* 0x00C */ ACTOR_EN_FIREFLY,
    /* 0x00D */ ACTOR_EN_HORSE,
    /* 0x00E */ ACTOR_EN_ITEM00,
    /* 0x00F */ ACTOR_EN_ARROW,
    /* 0x010 */ ACTOR_EN_ELF,
    /* 0x011 */ ACTOR_EN_NIW,
    /* 0x012 */ ACTOR_EN_TITE,
    /* 0x013 */ ACTOR_UNSET_13,
    /* 0x014 */ ACTOR_EN_PEEHAT,
    /* 0x015 */ ACTOR_EN_BUTTE,
    /* 0x016 */ ACTOR_EN_INSECT,
    /* 0x017 */ ACTOR_EN_FISH,
    /* 0x018 */ ACTOR_EN_HOLL,
    /* 0x019 */ ACTOR_EN_DINOFOS,
    /* 0x01A */ ACTOR_EN_HATA,
    /* 0x01B */ ACTOR_EN_ZL1,
    /* 0x01C */ ACTOR_EN_VIEWER,
    /* 0x01D */ ACTOR_EN_BUBBLE,
    /* 0x01E */ ACTOR_DOOR_SHUTTER,
    /* 0x01F */ ACTOR_UNSET_1F,
    /* 0x020 */ ACTOR_EN_BOOM,
    /* 0x021 */ ACTOR_EN_TORCH2,
    /* 0x022 */ ACTOR_EN_MINIFROG,
    /* 0x023 */ ACTOR_UNSET_23,
    /* 0x024 */ ACTOR_EN_ST,
    /* 0x025 */ ACTOR_UNSET_25,
    /* 0x026 */ ACTOR_EN_A_OBJ,
    /* 0x027 */ ACTOR_OBJ_WTURN,
    /* 0x028 */ ACTOR_EN_RIVER_SOUND,
    /* 0x029 */ ACTOR_UNSET_29,
    /* 0x02A */ ACTOR_EN_OSSAN,
    /* 0x02B */ ACTOR_UNSET_2B,
    /* 0x02C */ ACTOR_UNSET_2C,
    /* 0x02D */ ACTOR_EN_FAMOS,
    /* 0x02E */ ACTOR_UNSET_2E,
    /* 0x02F */ ACTOR_EN_BOMBF,
    /* 0x030 */ ACTOR_UNSET_30,
    /* 0x031 */ ACTOR_UNSET_31,
    /* 0x032 */ ACTOR_EN_AM,
    /* 0x033 */ ACTOR_EN_DEKUBABA,
    /* 0x034 */ ACTOR_EN_M_FIRE1,
    /* 0x035 */ ACTOR_EN_M_THUNDER,
    /* 0x036 */ ACTOR_BG_BREAKWALL,
    /* 0x037 */ ACTOR_UNSET_37,
    /* 0x038 */ ACTOR_DOOR_WARP1,
    /* 0x039 */ ACTOR_OBJ_SYOKUDAI,
    /* 0x03A */ ACTOR_ITEM_B_HEART,
    /* 0x03B */ ACTOR_EN_DEKUNUTS,
    /* 0x03C */ ACTOR_EN_BBFALL,
    /* 0x03D */ ACTOR_ARMS_HOOK,
    /* 0x03E */ ACTOR_EN_BB,
    /* 0x03F */ ACTOR_BG_KEIKOKU_SPR,
    /* 0x040 */ ACTOR_UNSET_40,
    /* 0x041 */ ACTOR_EN_WOOD02,
    /* 0x042 */ ACTOR_UNSET_42,
    /* 0x043 */ ACTOR_EN_DEATH,
    /* 0x044 */ ACTOR_EN_MINIDEATH,
    /* 0x045 */ ACTOR_UNSET_45,
    /* 0x046 */ ACTOR_UNSET_46,
    /* 0x047 */ ACTOR_EN_VM,
    /* 0x048 */ ACTOR_DEMO_EFFECT,
    /* 0x049 */ ACTOR_DEMO_KANKYO,
    /* 0x04A */ ACTOR_EN_FLOORMAS,
    /* 0x04B */ ACTOR_UNSET_4B,
    /* 0x04C */ ACTOR_EN_RD,
    /* 0x04D */ ACTOR_BG_F40_FLIFT,
    /* 0x04E */ ACTOR_UNSET_4E,
    /* 0x04F */ ACTOR_OBJ_MURE,
    /* 0x050 */ ACTOR_EN_SW,
    /* 0x051 */ ACTOR_OBJECT_KANKYO,
    /* 0x052 */ ACTOR_UNSET_52,
    /* 0x053 */ ACTOR_UNSET_53,
    /* 0x054 */ ACTOR_EN_HORSE_LINK_CHILD,
    /* 0x055 */ ACTOR_DOOR_ANA,
    /* 0x056 */ ACTOR_UNSET_56,
    /* 0x057 */ ACTOR_UNSET_57,
    /* 0x058 */ ACTOR_UNSET_58,
    /* 0x059 */ ACTOR_UNSET_59,
    /* 0x05A */ ACTOR_UNSET_5A,
    /* 0x05B */ ACTOR_EN_ENCOUNT1,
    /* 0x05C */ ACTOR_DEMO_TRE_LGT,
    /* 0x05D */ ACTOR_UNSET_5D,
    /* 0x05E */ ACTOR_UNSET_5E,
    /* 0x05F */ ACTOR_EN_ENCOUNT2,
    /* 0x060 */ ACTOR_EN_FIRE_ROCK,
    /* 0x061 */ ACTOR_BG_CTOWER_ROT,
    /* 0x062 */ ACTOR_MIR_RAY,
    /* 0x063 */ ACTOR_UNSET_63,
    /* 0x064 */ ACTOR_EN_SB,
    /* 0x065 */ ACTOR_EN_BIGSLIME,
    /* 0x066 */ ACTOR_EN_KAREBABA,
    /* 0x067 */ ACTOR_EN_IN,
    /* 0x068 */ ACTOR_UNSET_68,
    /* 0x069 */ ACTOR_EN_RU,
    /* 0x06A */ ACTOR_EN_BOM_CHU,
    /* 0x06B */ ACTOR_EN_HORSE_GAME_CHECK,
    /* 0x06C */ ACTOR_EN_RR,
    /* 0x06D */ ACTOR_UNSET_6D,
    /* 0x06E */ ACTOR_UNSET_6E,
    /* 0x06F */ ACTOR_UNSET_6F,
    /* 0x070 */ ACTOR_UNSET_70,
    /* 0x071 */ ACTOR_UNSET_71,
    /* 0x072 */ ACTOR_UNSET_72,
    /* 0x073 */ ACTOR_EN_FR,
    /* 0x074 */ ACTOR_UNSET_74,
    /* 0x075 */ ACTOR_UNSET_75,
    /* 0x076 */ ACTOR_UNSET_76,
    /* 0x077 */ ACTOR_UNSET_77,
    /* 0x078 */ ACTOR_UNSET_78,
    /* 0x079 */ ACTOR_EN_FISHING,
    /* 0x07A */ ACTOR_OBJ_OSHIHIKI,
    /* 0x07B */ ACTOR_EFF_DUST,
    /* 0x07C */ ACTOR_BG_UMAJUMP,
    /* 0x07D */ ACTOR_ARROW_FIRE,
    /* 0x07E */ ACTOR_ARROW_ICE,
    /* 0x07F */ ACTOR_ARROW_LIGHT,
    /* 0x080 */ ACTOR_ITEM_ETCETERA,
    /* 0x081 */ ACTOR_OBJ_KIBAKO,
    /* 0x082 */ ACTOR_OBJ_TSUBO,
    /* 0x083 */ ACTOR_UNSET_83,
    /* 0x084 */ ACTOR_EN_IK,
    /* 0x085 */ ACTOR_UNSET_85,
    /* 0x086 */ ACTOR_UNSET_86,
    /* 0x087 */ ACTOR_UNSET_87,
    /* 0x088 */ ACTOR_UNSET_88,
    /* 0x089 */ ACTOR_DEMO_SHD,
    /* 0x08A */ ACTOR_EN_DNS,
    /* 0x08B */ ACTOR_ELF_MSG,
    /* 0x08C */ ACTOR_EN_HONOTRAP,
    /* 0x08D */ ACTOR_EN_TUBO_TRAP,
    /* 0x08E */ ACTOR_OBJ_ICE_POLY,
    /* 0x08F */ ACTOR_EN_FZ,
    /* 0x090 */ ACTOR_EN_KUSA,
    /* 0x091 */ ACTOR_OBJ_BEAN,
    /* 0x092 */ ACTOR_OBJ_BOMBIWA,
    /* 0x093 */ ACTOR_OBJ_SWITCH,
    /* 0x094 */ ACTOR_UNSET_94,
    /* 0x095 */ ACTOR_OBJ_LIFT,
    /* 0x096 */ ACTOR_OBJ_HSBLOCK,
    /* 0x097 */ ACTOR_EN_OKARINA_TAG,
    /* 0x098 */ ACTOR_UNSET_98,
    /* 0x099 */ ACTOR_EN_GOROIWA,
    /* 0x09A */ ACTOR_UNSET_9A,
    /* 0x09B */ ACTOR_UNSET_9B,
    /* 0x09C */ ACTOR_EN_DAIKU,
    /* 0x09D */ ACTOR_EN_NWC,
    /* 0x09E */ ACTOR_ITEM_INBOX,
    /* 0x09F */ ACTOR_EN_GE1,
    /* 0x0A0 */ ACTOR_OBJ_BLOCKSTOP,
    /* 0x0A1 */ ACTOR_EN_SDA,
    /* 0x0A2 */ ACTOR_EN_CLEAR_TAG,
    /* 0x0A3 */ ACTOR_UNSET_A3,
    /* 0x0A4 */ ACTOR_EN_GM,
    /* 0x0A5 */ ACTOR_EN_MS,
    /* 0x0A6 */ ACTOR_EN_HS,
    /* 0x0A7 */ ACTOR_BG_INGATE,
    /* 0x0A8 */ ACTOR_EN_KANBAN,
    /* 0x0A9 */ ACTOR_UNSET_A9,
    /* 0x0AA */ ACTOR_EN_ATTACK_NIW,
    /* 0x0AB */ ACTOR_UNSET_AB,
    /* 0x0AC */ ACTOR_UNSET_AC,
    /* 0x0AD */ ACTOR_UNSET_AD,
    /* 0x0AE */ ACTOR_EN_MK,
    /* 0x0AF */ ACTOR_EN_OWL,
    /* 0x0B0 */ ACTOR_EN_ISHI,
    /* 0x0B1 */ ACTOR_OBJ_HANA,
    /* 0x0B2 */ ACTOR_OBJ_LIGHTSWITCH,
    /* 0x0B3 */ ACTOR_OBJ_MURE2,
    /* 0x0B4 */ ACTOR_UNSET_B4,
    /* 0x0B5 */ ACTOR_EN_FU,
    /* 0x0B6 */ ACTOR_UNSET_B6,
    /* 0x0B7 */ ACTOR_UNSET_B7,
    /* 0x0B8 */ ACTOR_EN_STREAM,
    /* 0x0B9 */ ACTOR_EN_MM,
    /* 0x0BA */ ACTOR_UNSET_BA,
    /* 0x0BB */ ACTOR_UNSET_BB,
    /* 0x0BC */ ACTOR_EN_WEATHER_TAG,
    /* 0x0BD */ ACTOR_EN_ANI,
    /* 0x0BE */ ACTOR_UNSET_BE,
    /* 0x0BF */ ACTOR_EN_JS,
    /* 0x0C0 */ ACTOR_UNSET_C0,
    /* 0x0C1 */ ACTOR_UNSET_C1,
    /* 0x0C2 */ ACTOR_UNSET_C2,
    /* 0x0C3 */ ACTOR_UNSET_C3,
    /* 0x0C4 */ ACTOR_EN_OKARINA_EFFECT,
    /* 0x0C5 */ ACTOR_EN_MAG,
    /* 0x0C6 */ ACTOR_ELF_MSG2,
    /* 0x0C7 */ ACTOR_BG_F40_SWLIFT,
    /* 0x0C8 */ ACTOR_UNSET_C8,
    /* 0x0C9 */ ACTOR_UNSET_C9,
    /* 0x0CA */ ACTOR_EN_KAKASI,
    /* 0x0CB */ ACTOR_OBJ_MAKEOSHIHIKI,
    /* 0x0CC */ ACTOR_OCEFF_SPOT,
    /* 0x0CD */ ACTOR_UNSET_CD,
    /* 0x0CE */ ACTOR_EN_TORCH,
    /* 0x0CF */ ACTOR_UNSET_CF,
    /* 0x0D0 */ ACTOR_SHOT_SUN,
    /* 0x0D1 */ ACTOR_UNSET_D1,
    /* 0x0D2 */ ACTOR_UNSET_D2,
    /* 0x0D3 */ ACTOR_OBJ_ROOMTIMER,
    /* 0x0D4 */ ACTOR_EN_SSH,
    /* 0x0D5 */ ACTOR_UNSET_D5,
    /* 0x0D6 */ ACTOR_OCEFF_WIPE,
    /* 0x0D7 */ ACTOR_OCEFF_STORM,
    /* 0x0D8 */ ACTOR_OBJ_DEMO,
    /* 0x0D9 */ ACTOR_EN_MINISLIME,
    /* 0x0DA */ ACTOR_EN_NUTSBALL,
    /* 0x0DB */ ACTOR_UNSET_DB,
    /* 0x0DC */ ACTOR_UNSET_DC,
    /* 0x0DD */ ACTOR_UNSET_DD,
    /* 0x0DE */ ACTOR_UNSET_DE,
    /* 0x0DF */ ACTOR_OCEFF_WIPE2,
    /* 0x0E0 */ ACTOR_OCEFF_WIPE3,
    /* 0x0E1 */ ACTOR_UNSET_E1,
    /* 0x0E2 */ ACTOR_EN_DG,
    /* 0x0E3 */ ACTOR_EN_SI,
    /* 0x0E4 */ ACTOR_OBJ_COMB,
    /* 0x0E5 */ ACTOR_OBJ_KIBAKO2,
    /* 0x0E6 */ ACTOR_UNSET_E6,
    /* 0x0E7 */ ACTOR_EN_HS2,
    /* 0x0E8 */ ACTOR_OBJ_MURE3,
    /* 0x0E9 */ ACTOR_EN_TG,
    /* 0x0EA */ ACTOR_UNSET_EA,
    /* 0x0EB */ ACTOR_UNSET_EB,
    /* 0x0EC */ ACTOR_EN_WF,
    /* 0x0ED */ ACTOR_EN_SKB,
    /* 0x0EE */ ACTOR_UNSET_EE,
    /* 0x0EF */ ACTOR_EN_GS,
    /* 0x0F0 */ ACTOR_OBJ_SOUND,
    /* 0x0F1 */ ACTOR_EN_CROW,
    /* 0x0F2 */ ACTOR_UNSET_F2,
    /* 0x0F3 */ ACTOR_EN_COW,
    /* 0x0F4 */ ACTOR_UNSET_F4,
    /* 0x0F5 */ ACTOR_UNSET_F5,
    /* 0x0F6 */ ACTOR_OCEFF_WIPE4,
    /* 0x0F7 */ ACTOR_UNSET_F7,
    /* 0x0F8 */ ACTOR_EN_ZO,
    /* 0x0F9 */ ACTOR_OBJ_MAKEKINSUTA,
    /* 0x0FA */ ACTOR_EN_GE3,
    /* 0x0FB */ ACTOR_UNSET_FB,
    /* 0x0FC */ ACTOR_OBJ_HAMISHI,
    /* 0x0FD */ ACTOR_EN_ZL4,
    /* 0x0FE */ ACTOR_EN_MM2,
    /* 0x0FF */ ACTOR_UNSET_FF,
    /* 0x100 */ ACTOR_DOOR_SPIRAL,
    /* 0x101 */ ACTOR_UNSET_101,
    /* 0x102 */ ACTOR_OBJ_PZLBLOCK,
    /* 0x103 */ ACTOR_OBJ_TOGE,
    /* 0x104 */ ACTOR_UNSET_104,
    /* 0x105 */ ACTOR_OBJ_ARMOS,
    /* 0x106 */ ACTOR_OBJ_BOYO,
    /* 0x107 */ ACTOR_UNSET_107,
    /* 0x108 */ ACTOR_UNSET_108,
    /* 0x109 */ ACTOR_EN_GRASSHOPPER,
    /* 0x10A */ ACTOR_UNSET_10A,
    /* 0x10B */ ACTOR_OBJ_GRASS,
    /* 0x10C */ ACTOR_OBJ_GRASS_CARRY,
    /* 0x10D */ ACTOR_OBJ_GRASS_UNIT,
    /* 0x10E */ ACTOR_UNSET_10E,
    /* 0x10F */ ACTOR_UNSET_10F,
    /* 0x110 */ ACTOR_BG_FIRE_WALL,
    /* 0x111 */ ACTOR_EN_BU,
    /* 0x112 */ ACTOR_EN_ENCOUNT3,
    /* 0x113 */ ACTOR_EN_JSO,
    /* 0x114 */ ACTOR_OBJ_CHIKUWA,
    /* 0x115 */ ACTOR_EN_KNIGHT,
    /* 0x116 */ ACTOR_EN_WARP_TAG,
    /* 0x117 */ ACTOR_EN_AOB_01,
    /* 0x118 */ ACTOR_EN_BOJ_01,
    /* 0x119 */ ACTOR_EN_BOJ_02,
    /* 0x11A */ ACTOR_EN_BOJ_03,
    /* 0x11B */ ACTOR_EN_ENCOUNT4,
    /* 0x11C */ ACTOR_EN_BOM_BOWL_MAN,
    /* 0x11D */ ACTOR_EN_SYATEKI_MAN,
    /* 0x11E */ ACTOR_UNSET_11E,
    /* 0x11F */ ACTOR_BG_ICICLE,
    /* 0x120 */ ACTOR_EN_SYATEKI_CROW,
    /* 0x121 */ ACTOR_EN_BOJ_04,
    /* 0x122 */ ACTOR_EN_CNE_01,
    /* 0x123 */ ACTOR_EN_BBA_01,
    /* 0x124 */ ACTOR_EN_BJI_01,
    /* 0x125 */ ACTOR_BG_SPDWEB,
    /* 0x126 */ ACTOR_UNSET_126,
    /* 0x127 */ ACTOR_UNSET_127,
    /* 0x128 */ ACTOR_EN_MT_TAG,
    /* 0x129 */ ACTOR_BOSS_01,
    /* 0x12A */ ACTOR_BOSS_02,
    /* 0x12B */ ACTOR_BOSS_03,
    /* 0x12C */ ACTOR_BOSS_04,
    /* 0x12D */ ACTOR_BOSS_05,
    /* 0x12E */ ACTOR_BOSS_06,
    /* 0x12F */ ACTOR_BOSS_07,
    /* 0x130 */ ACTOR_BG_DY_YOSEIZO,
    /* 0x131 */ ACTOR_UNSET_131,
    /* 0x132 */ ACTOR_EN_BOJ_05,
    /* 0x133 */ ACTOR_UNSET_133,
    /* 0x134 */ ACTOR_UNSET_134,
    /* 0x135 */ ACTOR_EN_SOB1,
    /* 0x136 */ ACTOR_UNSET_136,
    /* 0x137 */ ACTOR_UNSET_137,
    /* 0x138 */ ACTOR_EN_GO,
    /* 0x139 */ ACTOR_UNSET_139,
    /* 0x13A */ ACTOR_EN_RAF,
    /* 0x13B */ ACTOR_OBJ_FUNEN,
    /* 0x13C */ ACTOR_OBJ_RAILLIFT,
    /* 0x13D */ ACTOR_BG_NUMA_HANA,
    /* 0x13E */ ACTOR_OBJ_FLOWERPOT,
    /* 0x13F */ ACTOR_OBJ_SPINYROLL,
    /* 0x140 */ ACTOR_DM_HINA,
    /* 0x141 */ ACTOR_EN_SYATEKI_WF,
    /* 0x142 */ ACTOR_OBJ_SKATEBLOCK,
    /* 0x143 */ ACTOR_OBJ_ICEBLOCK,
    /* 0x144 */ ACTOR_EN_BIGPAMET,
    /* 0x145 */ ACTOR_EN_SYATEKI_DEKUNUTS,
    /* 0x146 */ ACTOR_ELF_MSG3,
    /* 0x147 */ ACTOR_EN_FG,
    /* 0x148 */ ACTOR_DM_RAVINE,
    /* 0x149 */ ACTOR_DM_SA,
    /* 0x14A */ ACTOR_EN_SLIME,
    /* 0x14B */ ACTOR_EN_PR,
    /* 0x14C */ ACTOR_OBJ_TOUDAI,
    /* 0x14D */ ACTOR_OBJ_ENTOTU,
    /* 0x14E */ ACTOR_OBJ_BELL,
    /* 0x14F */ ACTOR_EN_SYATEKI_OKUTA,
    /* 0x150 */ ACTOR_UNSET_150,
    /* 0x151 */ ACTOR_OBJ_SHUTTER,
    /* 0x152 */ ACTOR_DM_ZL,
    /* 0x153 */ ACTOR_EN_ELFGRP,
    /* 0x154 */ ACTOR_DM_TSG,
    /* 0x155 */ ACTOR_EN_BAGUO,
    /* 0x156 */ ACTOR_OBJ_VSPINYROLL,
    /* 0x157 */ ACTOR_OBJ_SMORK,
    /* 0x158 */ ACTOR_EN_TEST2,
    /* 0x159 */ ACTOR_EN_TEST3,
    /* 0x15A */ ACTOR_EN_TEST4,
    /* 0x15B */ ACTOR_EN_BAT,
    /* 0x15C */ ACTOR_EN_SEKIHI,
    /* 0x15D */ ACTOR_EN_WIZ,
    /* 0x15E */ ACTOR_EN_WIZ_BROCK,
    /* 0x15F */ ACTOR_EN_WIZ_FIRE,
    /* 0x160 */ ACTOR_EFF_CHANGE,
    /* 0x161 */ ACTOR_DM_STATUE,
    /* 0x162 */ ACTOR_OBJ_FIRESHIELD,
    /* 0x163 */ ACTOR_BG_LADDER,
    /* 0x164 */ ACTOR_EN_MKK,
    /* 0x165 */ ACTOR_DEMO_GETITEM,
    /* 0x166 */ ACTOR_UNSET_166,
    /* 0x167 */ ACTOR_EN_DNB,
    /* 0x168 */ ACTOR_EN_DNH,
    /* 0x169 */ ACTOR_EN_DNK,
    /* 0x16A */ ACTOR_EN_DNQ,
    /* 0x16B */ ACTOR_UNSET_16B,
    /* 0x16C */ ACTOR_BG_KEIKOKU_SAKU,
    /* 0x16D */ ACTOR_OBJ_HUGEBOMBIWA,
    /* 0x16E */ ACTOR_EN_FIREFLY2,
    /* 0x16F */ ACTOR_EN_RAT,
    /* 0x170 */ ACTOR_EN_WATER_EFFECT,
    /* 0x171 */ ACTOR_EN_KUSA2,
    /* 0x172 */ ACTOR_BG_SPOUT_FIRE,
    /* 0x173 */ ACTOR_UNSET_173,
    /* 0x174 */ ACTOR_BG_DBLUE_MOVEBG,
    /* 0x175 */ ACTOR_EN_DY_EXTRA,
    /* 0x176 */ ACTOR_EN_BAL,
    /* 0x177 */ ACTOR_EN_GINKO_MAN,
    /* 0x178 */ ACTOR_EN_WARP_UZU,
    /* 0x179 */ ACTOR_OBJ_DRIFTICE,
    /* 0x17A */ ACTOR_EN_LOOK_NUTS,
    /* 0x17B */ ACTOR_EN_MUSHI2,
    /* 0x17C */ ACTOR_EN_FALL,
    /* 0x17D */ ACTOR_EN_MM3,
    /* 0x17E */ ACTOR_BG_CRACE_MOVEBG,
    /* 0x17F */ ACTOR_EN_DNO,
    /* 0x180 */ ACTOR_EN_PR2,
    /* 0x181 */ ACTOR_EN_PRZ,
    /* 0x182 */ ACTOR_EN_JSO2,
    /* 0x183 */ ACTOR_OBJ_ETCETERA,
    /* 0x184 */ ACTOR_EN_EGOL,
    /* 0x185 */ ACTOR_OBJ_MINE,
    /* 0x186 */ ACTOR_OBJ_PURIFY,
    /* 0x187 */ ACTOR_EN_TRU,
    /* 0x188 */ ACTOR_EN_TRT,
    /* 0x189 */ ACTOR_UNSET_189,
    /* 0x18A */ ACTOR_UNSET_18A,
    /* 0x18B */ ACTOR_EN_TEST5,
    /* 0x18C */ ACTOR_EN_TEST6,
    /* 0x18D */ ACTOR_EN_AZ,
    /* 0x18E */ ACTOR_EN_ESTONE,
    /* 0x18F */ ACTOR_BG_HAKUGIN_POST,
    /* 0x190 */ ACTOR_DM_OPSTAGE,
    /* 0x191 */ ACTOR_DM_STK,
    /* 0x192 */ ACTOR_DM_CHAR00,
    /* 0x193 */ ACTOR_DM_CHAR01,
    /* 0x194 */ ACTOR_DM_CHAR02,
    /* 0x195 */ ACTOR_DM_CHAR03,
    /* 0x196 */ ACTOR_DM_CHAR04,
    /* 0x197 */ ACTOR_DM_CHAR05,
    /* 0x198 */ ACTOR_DM_CHAR06,
    /* 0x199 */ ACTOR_DM_CHAR07,
    /* 0x19A */ ACTOR_DM_CHAR08,
    /* 0x19B */ ACTOR_DM_CHAR09,
    /* 0x19C */ ACTOR_OBJ_TOKEIDAI,
    /* 0x19D */ ACTOR_UNSET_19D,
    /* 0x19E */ ACTOR_EN_MNK,
    /* 0x19F */ ACTOR_EN_EGBLOCK,
    /* 0x1A0 */ ACTOR_EN_GUARD_NUTS,
    /* 0x1A1 */ ACTOR_BG_HAKUGIN_BOMBWALL,
    /* 0x1A2 */ ACTOR_OBJ_TOKEI_TOBIRA,
    /* 0x1A3 */ ACTOR_BG_HAKUGIN_ELVPOLE,
    /* 0x1A4 */ ACTOR_EN_MA4,
    /* 0x1A5 */ ACTOR_EN_TWIG,
    /* 0x1A6 */ ACTOR_EN_PO_FUSEN,
    /* 0x1A7 */ ACTOR_EN_DOOR_ETC,
    /* 0x1A8 */ ACTOR_EN_BIGOKUTA,
    /* 0x1A9 */ ACTOR_BG_ICEFLOE,
    /* 0x1AA */ ACTOR_OBJ_OCARINALIFT,
    /* 0x1AB */ ACTOR_EN_TIME_TAG,
    /* 0x1AC */ ACTOR_BG_OPEN_SHUTTER,
    /* 0x1AD */ ACTOR_BG_OPEN_SPOT,
    /* 0x1AE */ ACTOR_BG_FU_KAITEN,
    /* 0x1AF */ ACTOR_OBJ_AQUA,
    /* 0x1B0 */ ACTOR_EN_ELFORG,
    /* 0x1B1 */ ACTOR_EN_ELFBUB,
    /* 0x1B2 */ ACTOR_UNSET_1B2,
    /* 0x1B3 */ ACTOR_EN_FU_MATO,
    /* 0x1B4 */ ACTOR_EN_FU_KAGO,
    /* 0x1B5 */ ACTOR_EN_OSN,
    /* 0x1B6 */ ACTOR_BG_CTOWER_GEAR,
    /* 0x1B7 */ ACTOR_EN_TRT2,
    /* 0x1B8 */ ACTOR_OBJ_TOKEI_STEP,
    /* 0x1B9 */ ACTOR_BG_LOTUS,
    /* 0x1BA */ ACTOR_EN_KAME,
    /* 0x1BB */ ACTOR_OBJ_TAKARAYA_WALL,
    /* 0x1BC */ ACTOR_BG_FU_MIZU,
    /* 0x1BD */ ACTOR_EN_SELLNUTS,
    /* 0x1BE */ ACTOR_BG_DKJAIL_IVY,
    /* 0x1BF */ ACTOR_UNSET_1BF,
    /* 0x1C0 */ ACTOR_OBJ_VISIBLOCK,
    /* 0x1C1 */ ACTOR_EN_TAKARAYA,
    /* 0x1C2 */ ACTOR_EN_TSN,
    /* 0x1C3 */ ACTOR_EN_DS2N,
    /* 0x1C4 */ ACTOR_EN_FSN,
    /* 0x1C5 */ ACTOR_EN_SHN,
    /* 0x1C6 */ ACTOR_UNSET_1C6,
    /* 0x1C7 */ ACTOR_EN_STOP_HEISHI,
    /* 0x1C8 */ ACTOR_OBJ_BIGICICLE,
    /* 0x1C9 */ ACTOR_EN_LIFT_NUTS,
    /* 0x1CA */ ACTOR_EN_TK,
    /* 0x1CB */ ACTOR_UNSET_1CB,
    /* 0x1CC */ ACTOR_BG_MARKET_STEP,
    /* 0x1CD */ ACTOR_OBJ_LUPYGAMELIFT,
    /* 0x1CE */ ACTOR_EN_TEST7,
    /* 0x1CF */ ACTOR_OBJ_LIGHTBLOCK,
    /* 0x1D0 */ ACTOR_MIR_RAY2,
    /* 0x1D1 */ ACTOR_EN_WDHAND,
    /* 0x1D2 */ ACTOR_EN_GAMELUPY,
    /* 0x1D3 */ ACTOR_BG_DANPEI_MOVEBG,
    /* 0x1D4 */ ACTOR_EN_SNOWWD,
    /* 0x1D5 */ ACTOR_EN_PM,
    /* 0x1D6 */ ACTOR_EN_GAKUFU,
    /* 0x1D7 */ ACTOR_ELF_MSG4,
    /* 0x1D8 */ ACTOR_ELF_MSG5,
    /* 0x1D9 */ ACTOR_EN_COL_MAN,
    /* 0x1DA */ ACTOR_EN_TALK_GIBUD,
    /* 0x1DB */ ACTOR_EN_GIANT,
    /* 0x1DC */ ACTOR_OBJ_SNOWBALL,
    /* 0x1DD */ ACTOR_BOSS_HAKUGIN,
    /* 0x1DE */ ACTOR_EN_GB2,
    /* 0x1DF */ ACTOR_EN_ONPUMAN,
    /* 0x1E0 */ ACTOR_BG_TOBIRA01,
    /* 0x1E1 */ ACTOR_EN_TAG_OBJ,
    /* 0x1E2 */ ACTOR_OBJ_DHOUSE,
    /* 0x1E3 */ ACTOR_OBJ_HAKAISI,
    /* 0x1E4 */ ACTOR_BG_HAKUGIN_SWITCH,
    /* 0x1E5 */ ACTOR_UNSET_1E5,
    /* 0x1E6 */ ACTOR_EN_SNOWMAN,
    /* 0x1E7 */ ACTOR_TG_SW,
    /* 0x1E8 */ ACTOR_EN_PO_SISTERS,
    /* 0x1E9 */ ACTOR_EN_PP,
    /* 0x1EA */ ACTOR_EN_HAKUROCK,
    /* 0x1EB */ ACTOR_EN_HANABI,
    /* 0x1EC */ ACTOR_OBJ_DOWSING,
    /* 0x1ED */ ACTOR_OBJ_WIND,
    /* 0x1EE */ ACTOR_EN_RACEDOG,
    /* 0x1EF */ ACTOR_EN_KENDO_JS,
    /* 0x1F0 */ ACTOR_BG_BOTIHASIRA,
    /* 0x1F1 */ ACTOR_EN_FISH2,
    /* 0x1F2 */ ACTOR_EN_PST,
    /* 0x1F3 */ ACTOR_EN_POH,
    /* 0x1F4 */ ACTOR_OBJ_SPIDERTENT,
    /* 0x1F5 */ ACTOR_EN_ZORAEGG,
    /* 0x1F6 */ ACTOR_EN_KBT,
    /* 0x1F7 */ ACTOR_EN_GG,
    /* 0x1F8 */ ACTOR_EN_MARUTA,
    /* 0x1F9 */ ACTOR_OBJ_SNOWBALL2,
    /* 0x1FA */ ACTOR_EN_GG2,
    /* 0x1FB */ ACTOR_OBJ_GHAKA,
    /* 0x1FC */ ACTOR_EN_DNP,
    /* 0x1FD */ ACTOR_EN_DAI,
    /* 0x1FE */ ACTOR_BG_GORON_OYU,
    /* 0x1FF */ ACTOR_EN_KGY,
    /* 0x200 */ ACTOR_EN_INVADEPOH,
    /* 0x201 */ ACTOR_EN_GK,
    /* 0x202 */ ACTOR_EN_AN,
    /* 0x203 */ ACTOR_UNSET_203,
    /* 0x204 */ ACTOR_EN_BEE,
    /* 0x205 */ ACTOR_EN_OT,
    /* 0x206 */ ACTOR_EN_DRAGON,
    /* 0x207 */ ACTOR_OBJ_DORA,
    /* 0x208 */ ACTOR_EN_BIGPO,
    /* 0x209 */ ACTOR_OBJ_KENDO_KANBAN,
    /* 0x20A */ ACTOR_OBJ_HARIKO,
    /* 0x20B */ ACTOR_EN_STH,
    /* 0x20C */ ACTOR_BG_SINKAI_KABE,
    /* 0x20D */ ACTOR_BG_HAKA_CURTAIN,
    /* 0x20E */ ACTOR_BG_KIN2_BOMBWALL,
    /* 0x20F */ ACTOR_BG_KIN2_FENCE,
    /* 0x210 */ ACTOR_BG_KIN2_PICTURE,
    /* 0x211 */ ACTOR_BG_KIN2_SHELF,
    /* 0x212 */ ACTOR_EN_RAIL_SKB,
    /* 0x213 */ ACTOR_EN_JG,
    /* 0x214 */ ACTOR_EN_TRU_MT,
    /* 0x215 */ ACTOR_OBJ_UM,
    /* 0x216 */ ACTOR_EN_NEO_REEBA,
    /* 0x217 */ ACTOR_BG_MBAR_CHAIR,
    /* 0x218 */ ACTOR_BG_IKANA_BLOCK,
    /* 0x219 */ ACTOR_BG_IKANA_MIRROR,
    /* 0x21A */ ACTOR_BG_IKANA_ROTARYROOM,
    /* 0x21B */ ACTOR_BG_DBLUE_BALANCE,
    /* 0x21C */ ACTOR_BG_DBLUE_WATERFALL,
    /* 0x21D */ ACTOR_EN_KAIZOKU,
    /* 0x21E */ ACTOR_EN_GE2,
    /* 0x21F */ ACTOR_EN_MA_YTS,
    /* 0x220 */ ACTOR_EN_MA_YTO,
    /* 0x221 */ ACTOR_OBJ_TOKEI_TURRET,
    /* 0x222 */ ACTOR_BG_DBLUE_ELEVATOR,
    /* 0x223 */ ACTOR_OBJ_WARPSTONE,
    /* 0x224 */ ACTOR_EN_ZOG,
    /* 0x225 */ ACTOR_OBJ_ROTLIFT,
    /* 0x226 */ ACTOR_OBJ_JG_GAKKI,
    /* 0x227 */ ACTOR_BG_INIBS_MOVEBG,
    /* 0x228 */ ACTOR_EN_ZOT,
    /* 0x229 */ ACTOR_OBJ_TREE,
    /* 0x22A */ ACTOR_OBJ_Y2LIFT,
    /* 0x22B */ ACTOR_OBJ_Y2SHUTTER,
    /* 0x22C */ ACTOR_OBJ_BOAT,
    /* 0x22D */ ACTOR_OBJ_TARU,
    /* 0x22E */ ACTOR_OBJ_HUNSUI,
    /* 0x22F */ ACTOR_EN_JC_MATO,
    /* 0x230 */ ACTOR_MIR_RAY3,
    /* 0x231 */ ACTOR_EN_ZOB,
    /* 0x232 */ ACTOR_ELF_MSG6,
    /* 0x233 */ ACTOR_OBJ_NOZOKI,
    /* 0x234 */ ACTOR_EN_TOTO,
    /* 0x235 */ ACTOR_EN_RAILGIBUD,
    /* 0x236 */ ACTOR_EN_BABA,
    /* 0x237 */ ACTOR_EN_SUTTARI,
    /* 0x238 */ ACTOR_EN_ZOD,
    /* 0x239 */ ACTOR_EN_KUJIYA,
    /* 0x23A */ ACTOR_EN_GEG,
    /* 0x23B */ ACTOR_OBJ_KINOKO,
    /* 0x23C */ ACTOR_OBJ_YASI,
    /* 0x23D */ ACTOR_EN_TANRON1,
    /* 0x23E */ ACTOR_EN_TANRON2,
    /* 0x23F */ ACTOR_EN_TANRON3,
    /* 0x240 */ ACTOR_OBJ_CHAN,
    /* 0x241 */ ACTOR_EN_ZOS,
    /* 0x242 */ ACTOR_EN_S_GORO,
    /* 0x243 */ ACTOR_EN_NB,
    /* 0x244 */ ACTOR_EN_JA,
    /* 0x245 */ ACTOR_BG_F40_BLOCK,
    /* 0x246 */ ACTOR_BG_F40_SWITCH,
    /* 0x247 */ ACTOR_EN_PO_COMPOSER,
    /* 0x248 */ ACTOR_EN_GURUGURU,
    /* 0x249 */ ACTOR_OCEFF_WIPE5,
    /* 0x24A */ ACTOR_EN_STONE_HEISHI,
    /* 0x24B */ ACTOR_OCEFF_WIPE6,
    /* 0x24C */ ACTOR_EN_SCOPENUTS,
    /* 0x24D */ ACTOR_EN_SCOPECROW,
    /* 0x24E */ ACTOR_OCEFF_WIPE7,
    /* 0x24F */ ACTOR_EFF_KAMEJIMA_WAVE,
    /* 0x250 */ ACTOR_EN_HG,
    /* 0x251 */ ACTOR_EN_HGO,
    /* 0x252 */ ACTOR_EN_ZOV,
    /* 0x253 */ ACTOR_EN_AH,
    /* 0x254 */ ACTOR_OBJ_HGDOOR,
    /* 0x255 */ ACTOR_BG_IKANA_BOMBWALL,
    /* 0x256 */ ACTOR_BG_IKANA_RAY,
    /* 0x257 */ ACTOR_BG_IKANA_SHUTTER,
    /* 0x258 */ ACTOR_BG_HAKA_BOMBWALL,
    /* 0x259 */ ACTOR_BG_HAKA_TOMB,
    /* 0x25A */ ACTOR_EN_SC_RUPPE,
    /* 0x25B */ ACTOR_BG_IKNV_DOUKUTU,
    /* 0x25C */ ACTOR_BG_IKNV_OBJ,
    /* 0x25D */ ACTOR_EN_PAMERA,
    /* 0x25E */ ACTOR_OBJ_HSSTUMP,
    /* 0x25F */ ACTOR_EN_HIDDEN_NUTS,
    /* 0x260 */ ACTOR_EN_ZOW,
    /* 0x261 */ ACTOR_EN_TALK,
    /* 0x262 */ ACTOR_EN_AL,
    /* 0x263 */ ACTOR_EN_TAB,
    /* 0x264 */ ACTOR_EN_NIMOTSU,
    /* 0x265 */ ACTOR_EN_HIT_TAG,
    /* 0x266 */ ACTOR_EN_RUPPECROW,
    /* 0x267 */ ACTOR_EN_TANRON4,
    /* 0x268 */ ACTOR_EN_TANRON5,
    /* 0x269 */ ACTOR_EN_TANRON6,
    /* 0x26A */ ACTOR_EN_DAIKU2,
    /* 0x26B */ ACTOR_EN_MUTO,
    /* 0x26C */ ACTOR_EN_BAISEN,
    /* 0x26D */ ACTOR_EN_HEISHI,
    /* 0x26E */ ACTOR_EN_DEMO_HEISHI,
    /* 0x26F */ ACTOR_EN_DT,
    /* 0x270 */ ACTOR_EN_CHA,
    /* 0x271 */ ACTOR_OBJ_DINNER,
    /* 0x272 */ ACTOR_EFF_LASTDAY,
    /* 0x273 */ ACTOR_BG_IKANA_DHARMA,
    /* 0x274 */ ACTOR_EN_AKINDONUTS,
    /* 0x275 */ ACTOR_EFF_STK,
    /* 0x276 */ ACTOR_EN_IG,
    /* 0x277 */ ACTOR_EN_RG,
    /* 0x278 */ ACTOR_EN_OSK,
    /* 0x279 */ ACTOR_EN_STH2,
    /* 0x27A */ ACTOR_EN_YB,
    /* 0x27B */ ACTOR_EN_RZ,
    /* 0x27C */ ACTOR_EN_SCOPECOIN,
    /* 0x27D */ ACTOR_EN_BJT,
    /* 0x27E */ ACTOR_EN_BOMJIMA,
    /* 0x27F */ ACTOR_EN_BOMJIMB,
    /* 0x280 */ ACTOR_EN_BOMBERS,
    /* 0x281 */ ACTOR_EN_BOMBERS2,
    /* 0x282 */ ACTOR_EN_BOMBAL,
    /* 0x283 */ ACTOR_OBJ_MOON_STONE,
    /* 0x284 */ ACTOR_OBJ_MU_PICT,
    /* 0x285 */ ACTOR_BG_IKNINSIDE,
    /* 0x286 */ ACTOR_EFF_ZORABAND,
    /* 0x287 */ ACTOR_OBJ_KEPN_KOYA,
    /* 0x288 */ ACTOR_OBJ_USIYANE,
    /* 0x289 */ ACTOR_EN_NNH,
    /* 0x28A */ ACTOR_OBJ_KZSAKU,
    /* 0x28B */ ACTOR_OBJ_MILK_BIN,
    /* 0x28C */ ACTOR_EN_KITAN,
    /* 0x28D */ ACTOR_BG_ASTR_BOMBWALL,
    /* 0x28E */ ACTOR_BG_IKNIN_SUSCEIL,
    /* 0x28F */ ACTOR_EN_BSB,
    /* 0x290 */ ACTOR_EN_RECEPGIRL,
    /* 0x291 */ ACTOR_EN_THIEFBIRD,
    /* 0x292 */ ACTOR_EN_JGAME_TSN,
    /* 0x293 */ ACTOR_OBJ_JGAME_LIGHT,
    /* 0x294 */ ACTOR_OBJ_YADO,
    /* 0x295 */ ACTOR_DEMO_SYOTEN,
    /* 0x296 */ ACTOR_DEMO_MOONEND,
    /* 0x297 */ ACTOR_BG_LBFSHOT,
    /* 0x298 */ ACTOR_BG_LAST_BWALL,
    /* 0x299 */ ACTOR_EN_AND,
    /* 0x29A */ ACTOR_EN_INVADEPOH_DEMO,
    /* 0x29B */ ACTOR_OBJ_DANPEILIFT,
    /* 0x29C */ ACTOR_EN_FALL2,
    /* 0x29D */ ACTOR_DM_AL,
    /* 0x29E */ ACTOR_DM_AN,
    /* 0x29F */ ACTOR_DM_AH,
    /* 0x2A0 */ ACTOR_DM_NB,
    /* 0x2A1 */ ACTOR_EN_DRS,
    /* 0x2A2 */ ACTOR_EN_ENDING_HERO,
    /* 0x2A3 */ ACTOR_DM_BAL,
    /* 0x2A4 */ ACTOR_EN_PAPER,
    /* 0x2A5 */ ACTOR_EN_HINT_SKB,
    /* 0x2A6 */ ACTOR_DM_TAG,
    /* 0x2A7 */ ACTOR_EN_BH,
    /* 0x2A8 */ ACTOR_EN_ENDING_HERO2,
    /* 0x2A9 */ ACTOR_EN_ENDING_HERO3,
    /* 0x2AA */ ACTOR_EN_ENDING_HERO4,
    /* 0x2AB */ ACTOR_EN_ENDING_HERO5,
    /* 0x2AC */ ACTOR_EN_ENDING_HERO6,
    /* 0x2AD */ ACTOR_DM_GM,
    /* 0x2AE */ ACTOR_OBJ_SWPRIZE,
    /* 0x2AF */ ACTOR_EN_INVISIBLE_RUPPE,
    /* 0x2B0 */ ACTOR_OBJ_ENDING,
    /* 0x2B1 */ ACTOR_EN_RSN,
    /* 0x2B2 */ ACTOR_ID_MAX // originally "ACTOR_DLF_MAX"
} ActorID;

typedef enum {
    /* 0 */ DOORLOCK_NORMAL,
    /* 1 */ DOORLOCK_BOSS,
    /* 2 */ DOORLOCK_2, // DOORLOCK_NORMAL_SPIRIT on OoT
    /* 3 */ DOORLOCK_MAX
} DoorLockType;

// Targetability / ACTOR_FLAG_TARGETABLE?
#define ACTOR_FLAG_1             (1 << 0)
// 
#define ACTOR_FLAG_2             (1 << 1)
// 
#define ACTOR_FLAG_4             (1 << 2)
// 
#define ACTOR_FLAG_8             (1 << 3)
// 
#define ACTOR_FLAG_10            (1 << 4)
// 
#define ACTOR_FLAG_20            (1 << 5)
// 
#define ACTOR_FLAG_40            (1 << 6)
// Invisible
#define ACTOR_FLAG_80            (1 << 7)
// Related to talk
#define ACTOR_FLAG_100           (1 << 8)
// 
#define ACTOR_FLAG_200           (1 << 9)
// 
#define ACTOR_FLAG_400           (1 << 10)
// 
#define ACTOR_FLAG_800           (1 << 11)
// 
#define ACTOR_FLAG_1000          (1 << 12)
// 
#define ACTOR_FLAG_2000          (1 << 13)
// 
#define ACTOR_FLAG_4000          (1 << 14)
// 
#define ACTOR_FLAG_8000          (1 << 15)
// 
#define ACTOR_FLAG_10000         (1 << 16)
// 
#define ACTOR_FLAG_20000         (1 << 17)
// 
#define ACTOR_FLAG_40000         (1 << 18)
// 
#define ACTOR_FLAG_80000         (1 << 19)
// 
#define ACTOR_FLAG_100000        (1 << 20)
// 
#define ACTOR_FLAG_200000        (1 << 21)
// 
#define ACTOR_FLAG_400000        (1 << 22)
// 
#define ACTOR_FLAG_800000        (1 << 23)
// 
#define ACTOR_FLAG_1000000       (1 << 24)
// 
#define ACTOR_FLAG_2000000       (1 << 25)
// 
#define ACTOR_FLAG_4000000       (1 << 26)
// 
#define ACTOR_FLAG_8000000       (1 << 27)
// 
#define ACTOR_FLAG_10000000      (1 << 28)
// 
#define ACTOR_FLAG_20000000      (1 << 29)
// 
#define ACTOR_FLAG_40000000      (1 << 30)
// 
#define ACTOR_FLAG_80000000      (1 << 31)

typedef enum {
    /* 0x00 */ CLEAR_TAG_SMALL_EXPLOSION,
    /* 0x01 */ CLEAR_TAG_LARGE_EXPLOSION,
    /* 0x02 */ CLEAR_TAG_POP,
    /* 0x03 */ CLEAR_TAG_SMALL_LIGHT_RAYS,
    /* 0x04 */ CLEAR_TAG_LARGE_LIGHT_RAYS,
    /* 0x23 */ CLEAR_TAG_SPLASH = 35,
    /* 0xC8 */ CLEAR_TAG_SMOKE = 200
} ClearTagType;

#endif
