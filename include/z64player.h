#ifndef Z64PLAYER_H
#define Z64PLAYER_H

#include "z64actor.h"
#include "os.h"

struct Player;

typedef enum {
    /* 0x00 */ PLAYER_SHIELD_NONE,
    /* 0x01 */ PLAYER_SHIELD_HEROS_SHIELD,
    /* 0x02 */ PLAYER_SHIELD_MIRROR_SHIELD,
    /* 0x03 */ PLAYER_SHIELD_MAX
} PlayerShield;

typedef enum {
    /* 0x00 */ PLAYER_BOOTS_FIERCE_DEITY,
    /* 0x01 */ PLAYER_BOOTS_HYLIAN,
    /* 0x02 */ PLAYER_BOOTS_GIANT,
    /* 0x03 */ PLAYER_BOOTS_DEKU,
    /* 0x04 */ PLAYER_BOOTS_ZORA_LAND,
    /* 0x05 */ PLAYER_BOOTS_ZORA_UNDERWATER,
    /* 0x06 */ PLAYER_BOOTS_GORON,
    /* 0x07 */ PLAYER_BOOTS_MAX
} PlayerBoots;

typedef enum {
    /* 0x00 */ PLAYER_FORM_FIERCE_DEITY,
    /* 0x01 */ PLAYER_FORM_GORON,
    /* 0x02 */ PLAYER_FORM_ZORA,
    /* 0x03 */ PLAYER_FORM_DEKU,
    /* 0x04 */ PLAYER_FORM_HUMAN,
    /* 0x05 */ PLAYER_FORM_MAX
} PlayerTransformation;

typedef enum {
    /* 0x00 */ PLAYER_MASK_NONE,
    /* 0x01 */ PLAYER_MASK_TRUTH,
    /* 0x02 */ PLAYER_MASK_KAFEIS_MASK,
    /* 0x03 */ PLAYER_MASK_ALL_NIGHT,
    /* 0x04 */ PLAYER_MASK_BUNNY,
    /* 0x05 */ PLAYER_MASK_KEATON,
    /* 0x06 */ PLAYER_MASK_GARO,
    /* 0x07 */ PLAYER_MASK_ROMANI,
    /* 0x08 */ PLAYER_MASK_CIRCUS_LEADER,
    /* 0x09 */ PLAYER_MASK_POSTMAN,
    /* 0x0A */ PLAYER_MASK_COUPLE,
    /* 0x0B */ PLAYER_MASK_GREAT_FAIRY,
    /* 0x0C */ PLAYER_MASK_GIBDO,
    /* 0x0D */ PLAYER_MASK_DON_GERO,
    /* 0x0E */ PLAYER_MASK_KAMARO,
    /* 0x0F */ PLAYER_MASK_CAPTAIN,
    /* 0x10 */ PLAYER_MASK_STONE,
    /* 0x11 */ PLAYER_MASK_BREMEN,
    /* 0x12 */ PLAYER_MASK_BLAST,
    /* 0x13 */ PLAYER_MASK_SCENTS,
    /* 0x14 */ PLAYER_MASK_GIANT,
    /* 0x15 */ PLAYER_MASK_FIERCE_DEITY,
    /* 0x16 */ PLAYER_MASK_GORON,
    /* 0x17 */ PLAYER_MASK_ZORA,
    /* 0x18 */ PLAYER_MASK_DEKU,
    /* 0x19 */ PLAYER_MASK_MAX
} PlayerMask;

typedef enum {
    /* 0x00 */ PLAYER_AP_NONE,
    /* 0x01 */ PLAYER_AP_UNK_1,
    /* 0x02 */ PLAYER_AP_UNK_2,
    /* 0x03 */ PLAYER_AP_SWORD_KOKIRI,
    /* 0x04 */ PLAYER_AP_SWORD_RAZOR,
    /* 0x05 */ PLAYER_AP_SWORD_GILDED,
    /* 0x06 */ PLAYER_AP_SWORD_GREAT_FAIRY,
    /* 0x07 */ PLAYER_AP_STICK,
    /* 0x08 */ PLAYER_AP_UNK_8,
    /* 0x09 */ PLAYER_AP_BOW,
    /* 0x0A */ PLAYER_AP_BOW_FIRE,
    /* 0x0B */ PLAYER_AP_BOW_ICE,
    /* 0x0C */ PLAYER_AP_BOW_LIGHT,
    /* 0x0D */ PLAYER_AP_HOOKSHOT,
    /* 0x0E */ PLAYER_AP_BOMB,
    /* 0x0F */ PLAYER_AP_POWDER_KEG,
    /* 0x10 */ PLAYER_AP_BOMBCHU,
    /* 0x12 */ PLAYER_AP_NUT = 0x12,
    /* 0x13 */ PLAYER_AP_PICTO_BOX,
    /* 0x14 */ PLAYER_AP_OCARINA,
    /* 0x15 */ PLAYER_AP_BOTTLE,
    /* 0x16 */ PLAYER_AP_BOTTLE_FISH,
    /* 0x17 */ PLAYER_AP_BOTTLE_SPRING_WATER,
    /* 0x18 */ PLAYER_AP_BOTTLE_HOT_SPRING_WATER,
    /* 0x19 */ PLAYER_AP_BOTTLE_ZORA_EGG,
    /* 0x1A */ PLAYER_AP_BOTTLE_DEKU_PRINCESS,
    /* 0x1B */ PLAYER_AP_BOTTLE_GOLD_DUST,
    /* 0x1D */ PLAYER_AP_BOTTLE_SEA_HORSE = 0x1D,
    /* 0x1E */ PLAYER_AP_BOTTLE_MUSHROOM,
    /* 0x1F */ PLAYER_AP_BOTTLE_HYLIAN_LOACH,
    /* 0x20 */ PLAYER_AP_BOTTLE_BUG,
    /* 0x21 */ PLAYER_AP_BOTTLE_POE,
    /* 0x22 */ PLAYER_AP_BOTTLE_BIG_POE,
    /* 0x23 */ PLAYER_AP_BOTTLE_POTION_RED,
    /* 0x24 */ PLAYER_AP_BOTTLE_POTION_BLUE,
    /* 0x25 */ PLAYER_AP_BOTTLE_POTION_GREEN,
    /* 0x26 */ PLAYER_AP_BOTTLE_MILK,
    /* 0x27 */ PLAYER_AP_BOTTLE_MILK_HALF,
    /* 0x28 */ PLAYER_AP_BOTTLE_CHATEAU,
    /* 0x29 */ PLAYER_AP_BOTTLE_FAIRY,
    /* 0x2A */ PLAYER_AP_MOON_TEAR,
    /* 0x2B */ PLAYER_AP_DEED_LAND,
    /* 0x2C */ PLAYER_AP_ROOM_KEY,
    /* 0x2D */ PLAYER_AP_LETTER_TO_KAFEI,
    /* 0x2E */ PLAYER_AP_MAGIC_BEANS,
    /* 0x2F */ PLAYER_AP_DEED_SWAMP,
    /* 0x30 */ PLAYER_AP_DEED_MOUNTAIN,
    /* 0x31 */ PLAYER_AP_DEED_OCEAN,
    /* 0x33 */ PLAYER_AP_LETTER_MAMA = 0x33,
    /* 0x36 */ PLAYER_AP_PENDANT_MEMORIES = 0x36,
    /* 0x3A */ PLAYER_AP_MASK_TRUTH = 0x3A,
    /* 0x3B */ PLAYER_AP_MASK_KAFEIS_MASK,
    /* 0x3C */ PLAYER_AP_MASK_ALL_NIGHT,
    /* 0x3D */ PLAYER_AP_MASK_BUNNY,
    /* 0x3E */ PLAYER_AP_MASK_KEATON,
    /* 0x3F */ PLAYER_AP_MASK_GARO,
    /* 0x40 */ PLAYER_AP_MASK_ROMANI,
    /* 0x41 */ PLAYER_AP_MASK_CIRCUS_LEADER,
    /* 0x42 */ PLAYER_AP_MASK_POSTMAN,
    /* 0x43 */ PLAYER_AP_MASK_COUPLE,
    /* 0x44 */ PLAYER_AP_MASK_GREAT_FAIRY,
    /* 0x45 */ PLAYER_AP_MASK_GIBDO,
    /* 0x46 */ PLAYER_AP_MASK_DON_GERO,
    /* 0x47 */ PLAYER_AP_MASK_KAMARO,
    /* 0x48 */ PLAYER_AP_MASK_CAPTAIN,
    /* 0x49 */ PLAYER_AP_MASK_STONE,
    /* 0x4A */ PLAYER_AP_MASK_BREMEN,
    /* 0x4B */ PLAYER_AP_MASK_BLAST,
    /* 0x4C */ PLAYER_AP_MASK_SCENTS,
    /* 0x4D */ PLAYER_AP_MASK_GIANT,
    /* 0x4E */ PLAYER_AP_MASK_FIERCE_DEITY,
    /* 0x4F */ PLAYER_AP_MASK_GORON,
    /* 0x50 */ PLAYER_AP_MASK_ZORA,
    /* 0x51 */ PLAYER_AP_MASK_DEKU,
    /* 0x52 */ PLAYER_AP_LENS,
    /* 0xFD */ PLAYER_AP_MAX = 0xFD
} PlayerActionParam;

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
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ Vec3s unk_44;
    /* 0x4A */ Vec3s unk_4A[4];
    /* 0x62 */ Vec3s unk_62[4];
    /* 0x7A */ Vec3s unk_7A[4];
    /* 0x92 */ u16 unk_92;
    /* 0x94 */ u16 unk_94;
    /* 0x98 */ f32 unk_98;
    /* 0x9C */ f32 unk_9C;
    /* 0xA0 */ LinkAnimationHeader* unk_A0;
    /* 0xA4 */ LinkAnimationHeader* unk_A4;
    /* 0xA8 */ LinkAnimationHeader* unk_A8;
    /* 0xAC */ LinkAnimationHeader* unk_AC;
    /* 0xB0 */ LinkAnimationHeader* unk_B0;
    /* 0xB4 */ LinkAnimationHeader* unk_B4[4];
    /* 0xC4 */ LinkAnimationHeader* unk_C4[2];
    /* 0xCC */ LinkAnimationHeader* unk_CC[2];
    /* 0xD4 */ LinkAnimationHeader* unk_D4[2];
} PlayerAgeProperties; // size = 0xDC


typedef struct {
    /* 0x00 */ s32 active;
    /* 0x04 */ Vec3f tip;
    /* 0x10 */ Vec3f base;
} WeaponInfo; // size = 0x1C


typedef void (*PlayerFuncD58)(struct GlobalContext*, struct Player*);


typedef struct Player {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s8 currentShield;
    /* 0x145 */ s8 currentBoots;
    /* 0x146 */ s8 heldItemButton;
    /* 0x147 */ s8 itemActionParam;
    /* 0x148 */ u8 heldItemId;
    /* 0x149 */ s8 prevBoots;
    /* 0x14A */ s8 heldItemActionParam;
    /* 0x14B */ u8 transformation;
    /* 0x14C */ u8 modelGroup;
    /* 0x14D */ u8 nextModelGroup;
    /* 0x14E */ s8 unk_14E;
    /* 0x14F */ u8 modelAnimType;
    /* 0x150 */ u8 leftHandType;
    /* 0x151 */ u8 rightHandType;
    /* 0x152 */ u8 sheathType;
    /* 0x153 */ u8 currentMask;
    /* 0x154 */ s8 unk_154;
    /* 0x155 */ u8 prevMask;
    /* 0x158 */ Gfx** rightHandDLists;
    /* 0x15C */ Gfx** leftHandDLists;
    /* 0x160 */ Gfx** sheathDLists;
    /* 0x164 */ Gfx** waistDLists;
    /* 0x168 */ f32 unk_168;
    /* 0x16C */ f32 unk_16C;
    /* 0x170 */ f32 unk_170;
    /* 0x174 */ f32 unk_174;
    /* 0x178 */ f32 unk_178;
    /* 0x17C */ f32 unk_17C;
    /* 0x180 */ f32 unk_180;
    /* 0x184 */ f32 unk_184;
    /* 0x188 */ f32 unk_188;
    /* 0x18C */ f32 unk_18C;
    /* 0x190 */ f32 unk_190;
    /* 0x194 */ f32 unk_194;
    /* 0x198 */ f32 unk_198;
    /* 0x19C */ f32 unk_19C;
    /* 0x1A0 */ f32 unk_1A0;
    /* 0x1A4 */ f32 unk_1A4;
    /* 0x1A8 */ f32 unk_1A8;
    /* 0x1AC */ f32 unk_1AC;
    /* 0x1B0 */ f32 unk_1B0;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ char unk_1B6[2];
    /* 0x1B8 */ u8 giObjectLoading;
    /* 0x1BC */ DmaRequest giObjectDmaRequest;
    /* 0x1DC */ OSMesgQueue giObjectLoadQueue;
    /* 0x1F4 */ OSMesg giObjectLoadMsg;
    /* 0x1F8 */ void* giObjectSegment;
    /* 0x1FC */ u8 maskObjectLoading;
    /* 0x1FD */ s8 maskId;
    /* 0x200 */ DmaRequest maskDmaRequest;
    /* 0x220 */ OSMesgQueue maskObjectLoadQueue;
    /* 0x238 */ OSMesg maskObjectLoadMsg;
    /* 0x23C */ void* maskObjectSegment;
    /* 0x240 */ SkelAnime skelAnime;
    /* 0x284 */ SkelAnime unk_284;
    /* 0x2C8 */ SkelAnime unk_2C8;
    /* 0x30C */ Vec3s jointTable[5];
    /* 0x32A */ Vec3s morphTable[5];
    /* 0x348 */ s16 eyeTexId;
    /* 0x34A */ s16 eyeAnimTimer;
    /* 0x34C */ Actor* heldActor;
    /* 0x350 */ PosRot leftHandWorld;
    /* 0x364 */ Actor* rightHandActor;
    /* 0x368 */ PosRot rightHandWorld;
    /* 0x37C */ s8 doorType;
    /* 0x37D */ s8 doorDirection;
    /* 0x37E */ s8 doorTimer;
    /* 0x37F */ s8 doorNext; // used with spiral staircase
    /* 0x380 */ Actor* doorActor;
    /* 0x384 */ s16 getItemId;
    /* 0x386 */ u16 getItemDirection;
    /* 0x388 */ Actor* interactRangeActor;
    /* 0x38C */ s8 mountSide;
    /* 0x390 */ Actor* rideActor;
    /* 0x394 */ u8 csMode;
    /* 0x395 */ u8 unk_395;
    /* 0x396 */ u8 unk_396;
    /* 0x397 */ u8 unk_397;
    /* 0x398 */ Actor* unk_398;
    /* 0x39C */ s16 unk_39C;
    /* 0x39E */ s16 unk_39E;
    /* 0x3A0 */ Vec3f unk_3A0;
    /* 0x3AC */ Vec3f unk_3AC;
    /* 0x3B8 */ u16 unk_3B8;
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ s16 unk_3BC;
    /* 0x3BE */ char unk_3BE[2];
    /* 0x3C0 */ Vec3f unk_3C0;
    /* 0x3CC */ s16 unk_3CC;
    /* 0x3CE */ s8 unk_3CE;
    /* 0x3CF */ u8 unk_3CF;
    /* 0x3D0 */ char unk_3D0[0x148];
    /* 0x518 */ ColliderCylinder cylinder;
    /* 0x564 */ ColliderQuad swordQuads[2];
    /* 0x664 */ ColliderQuad shieldQuad;
    /* 0x6E4 */ ColliderCylinder shieldCylinder;
    /* 0x730 */ Actor* unk_730;
    /* 0x734 */ char unk_734[4];
    /* 0x738 */ s32 unk_738;
    /* 0x73C */ s32 blureEffectIndex[3];
    /* 0x748 */ char unk_748[0x320];
    /* 0xA68 */ PlayerAgeProperties* ageProperties; // repurposed as "transformation properties"?
    /* 0xA6C */ u32 stateFlags1;
    /* 0xA70 */ u32 stateFlags2;
    /* 0xA74 */ u32 stateFlags3;
    /* 0xA78 */ Actor* unk_A78;
    /* 0xA7C */ Actor* boomerangActor;
    /* 0xA80 */ Actor* tatlActor;
    /* 0xA84 */ s16 tatlTextId;
    /* 0xA86 */ s8 unk_A86;
    /* 0xA87 */ s8 exchangeItemId;
    /* 0xA88 */ Actor* targetActor;
    /* 0xA8C */ f32 targetActorDistance;
    /* 0xA90 */ Actor* unk_A90;
    /* 0xA94 */ f32 unk_A94;
    /* 0xA98 */ Actor* unk_A98;
    /* 0xA9C */ f32 unk_A9C;
    /* 0xAA0 */ f32 unk_AA0;
    /* 0xAA4 */ s8 unk_AA4;
    /* 0xAA5 */ u8 unk_AA5;
    /* 0xAA6 */ u16 unk_AA6;
    /* 0xAA8 */ s16 unk_AA8;
    /* 0xAAA */ s16 unk_AAA;
    /* 0xAAC */ Vec3s unk_AAC;
    /* 0xAB2 */ Vec3s unk_AB2;
    /* 0xAB8 */ f32 unk_AB8;
    /* 0xABC */ f32 unk_ABC;
    /* 0xAC0 */ f32 unk_AC0;
    /* 0xAC4 */ void* unk_AC4;
    /* 0xAC8 */ f32 unk_AC8;
    /* 0xACC */ s16 unk_ACC;
    /* 0xACE */ s8 unk_ACE;
    /* 0xACF */ u8 unk_ACF;
    /* 0xAD0 */ f32 linearVelocity;
    /* 0xAD4 */ s16 currentYaw;
    /* 0xAD6 */ s16 targetYaw;
    /* 0xAD8 */ u16 unk_AD8;
    /* 0xADA */ s8 swordAnimation;
    /* 0xADB */ s8 swordState;
    /* 0xADC */ s8 unk_ADC;
    /* 0xADD */ s8 unk_ADD;
    /* 0xADE */ u8 unk_ADE;
    /* 0xADF */ s8 unk_ADF[4];
    /* 0xAE3 */ s8 unk_AE3[4];
    /* 0xAE7 */ s8 unk_AE7; // a timer
    /* 0xAE8 */ s16 unk_AE8; // multipurpose timer
    /* 0xAEC */ f32 unk_AEC;
    /* 0xAF0 */ Vec3f unk_AF0[2];
    /* 0xB08 */ f32 unk_B08[8];
    /* 0xB28 */ s16 unk_B28; //Burning stick timer?
    /* 0xB2A */ s8 unk_B2A;
    /* 0xB2B */ s8 unk_B2B;
    /* 0xB2C */ f32 windSpeed;
    /* 0xB30 */ s16 windAngleX;
    /* 0xB32 */ s16 windAngleY;
    /* 0xB34 */ f32 unk_B34;
    /* 0xB38 */ f32 unk_B38;
    /* 0xB3C */ f32 unk_B3C;
    /* 0xB40 */ f32 unk_B40;
    /* 0xB44 */ f32 unk_B44;
    /* 0xB48 */ f32 unk_B48;
    /* 0xB4C */ s16 unk_B4C;
    /* 0xB4E */ s16 unk_B4E;
    /* 0xB50 */ f32 unk_B50;
    /* 0xB54 */ f32 unk_B54;
    /* 0xB58 */ f32 unk_B58;
    /* 0xB5C */ u8 unk_B5C;
    /* 0xB5D */ u8 unk_B5D;
    /* 0xB5E */ u8 unk_B5E;
    /* 0xB5F */ u8 unk_B5F;
    /* 0xB60 */ u16 unk_B60; // blast mask timer?
    /* 0xB62 */ s16 unk_B62;
    /* 0xB64 */ u8 unk_B64;
    /* 0xB65 */ u8 unk_B65;
    /* 0xB66 */ u8 unk_B66;
    /* 0xB67 */ u8 unk_B67; // deku hop timer?
    /* 0xB68 */ s16 unk_B68;
    /* 0xB6A */ s16 unk_B6A;
    /* 0xB6C */ s16 unk_B6C;
    /* 0xB6E */ s16 unk_B6E;
    /* 0xB70 */ s16 unk_B70;
    /* 0xB72 */ u16 unk_B72; // floor type?
    /* 0xB74 */ u8 unk_B74;
    /* 0xB75 */ u8 unk_B75;
    /* 0xB76 */ s16 unk_B76;
    /* 0xB78 */ f32 unk_B78;
    /* 0xB7C */ f32 unk_B7C;
    /* 0xB80 */ f32 unk_B80;
    /* 0xB84 */ s16 unk_B84;
    /* 0xB86 */ s16 unk_B86;
    /* 0xB88 */ s16 unk_B88;
    /* 0xB8A */ s16 unk_B8A;
    /* 0xB8C */ s16 unk_B8C;
    /* 0xB8E */ s16 unk_B8E;
    /* 0xB90 */ s16 unk_B90;
    /* 0xB92 */ s16 unk_B92;
    /* 0xB94 */ s16 unk_B94;
    /* 0xB96 */ s16 unk_B96;
    /* 0xB98 */ WeaponInfo swordInfo[3];
    /* 0xBEC */ Vec3f bodyPartsPos[18];
    /* 0xCC4 */ MtxF mf_CC4;
    /* 0xD04 */ MtxF shieldMf;
    /* 0xD44 */ u8 isBurning;
    /* 0xD45 */ u8 flameTimers[18]; // one flame per body part
    /* 0xD57 */ u8 unk_D57;
    /* 0xD58 */ PlayerFuncD58 unk_D58;
    /* 0xD5C */ s8 invincibilityTimer; // prevents damage when nonzero (positive = visible, counts towards zero each frame)
    /* 0xD5D */ u8 unk_D5D;
    /* 0xD5E */ u8 unk_D5E;
    /* 0xD5F */ u8 unk_D5F;
    /* 0xD60 */ f32 unk_D60;
    /* 0xD64 */ s16 unk_D64;
    /* 0xD66 */ u16 unk_D66;
    /* 0xD68 */ s16 unk_D68;
    /* 0xD6A */ s8 unk_D6A;
    /* 0xD6B */ u8 unk_D6B;
    /* 0xD6C */ Vec3f unk_D6C; // previous body part 0 position
} Player; // size = 0xD78

#endif
