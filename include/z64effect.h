#ifndef _Z64EFFECT_H_
#define _Z64EFFECT_H_

#include <PR/ultratypes.h>
#include <color.h>
#include <z64light.h>
#include <z64math.h>
#include <unk.h>

struct GraphicsContext;
struct GlobalContext;

typedef void(*eff_destroy_func)(void* params);

typedef void(*eff_draw_func)(void* params, struct GraphicsContext* gCtxt);

typedef void(*eff_init_func)(void* params, void* init);

typedef s32(*eff_update_func)(void* params);

typedef struct {
    /* 0x0 */ u8 active;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ UNK_TYPE1 pad3[0x1];
} EffCommon; // size = 0x4

typedef struct {
    /* 0x00 */ Vec3f velocity;
    /* 0x0C */ Vec3f position;
    /* 0x18 */ Vec3s unk18;
    /* 0x1E */ Vec3s unk1E;
} EffSparkParticle; // size = 0x24

typedef struct {
    /* 0x000 */ Vec3s position;
    /* 0x008 */ s32 numParticles; // Will be calculated as particleFactor1 * particleFactor2 + 2
    /* 0x00C */ EffSparkParticle particles[32];
    /* 0x48C */ f32 velocity;
    /* 0x490 */ f32 gravity;
    /* 0x494 */ u32 particleFactor1;
    /* 0x498 */ u32 particleFactor2;
    /* 0x49C */ Color_RGBA8 colorStart[4];
    /* 0x4AC */ Color_RGBA8 colorEnd[4];
    /* 0x4BC */ s32 age;
    /* 0x4C0 */ s32 duration;
} EffSparkParams; // size = 0x4C4

typedef struct {
    /* 0x000 */ EffCommon base;
    /* 0x004 */ EffSparkParams params;
} EffSpark; // size = 0x4C8

typedef struct {
    /* 0x00 */ UNK_TYPE1 pad0[0x18];
} EffBlureParticle; // size = 0x18

typedef struct {
    /* 0x000 */ UNK_TYPE1 pad0[0x184];
    /* 0x184 */ Color_RGBA8 unk184;
    /* 0x188 */ Color_RGBA8 unk188;
    /* 0x18C */ Color_RGBA8 unk18C;
    /* 0x190 */ Color_RGBA8 unk190;
    /* 0x194 */ UNK_TYPE1 pad194[0xC];
} EffBlureInit1; // size = 0x1A0

typedef struct {
    /* 0x00 */ UNK_TYPE1 pad0[0x8];
    /* 0x08 */ Color_RGBA8 unk8;
    /* 0x0C */ Color_RGBA8 unkC;
    /* 0x10 */ Color_RGBA8 unk10;
    /* 0x14 */ Color_RGBA8 unk14;
    /* 0x18 */ UNK_TYPE1 pad18[0xC];
} EffBlureInit2; // size = 0x24

typedef struct {
    /* 0x000 */ EffBlureParticle particles[16];
    /* 0x180 */ UNK_TYPE1 pad180[0x4];
    /* 0x184 */ f32 unk184;
    /* 0x188 */ u16 unk188;
    /* 0x18A */ UNK_TYPE1 pad18A[0x4];
    /* 0x18E */ Color_RGBA8 unk18E;
    /* 0x192 */ Color_RGBA8 unk192;
    /* 0x196 */ Color_RGBA8 unk196;
    /* 0x19A */ Color_RGBA8 unk19A;
    /* 0x19E */ u8 unk19E;
    /* 0x19F */ u8 unk19F;
    /* 0x1A0 */ u8 unk1A0;
    /* 0x1A1 */ u8 unk1A1;
    /* 0x1A2 */ UNK_TYPE1 pad1A2[0xA];
} EffBlureParams; // size = 0x1AC

typedef struct {
    /* 0x000 */ EffCommon base;
    /* 0x004 */ EffBlureParams params;
} EffBlure; // size = 0x1B0

typedef struct {
    /* 0x00 */ f32 startSpeed;
    /* 0x04 */ f32 endXChange;
    /* 0x08 */ f32 endX;
    /* 0x0C */ f32 startXChange;
    /* 0x10 */ f32 startX;
    /* 0x14 */ s16 rotationY;
    /* 0x16 */ s16 rotationZ;
} EffShieldParticleParticle; // size = 0x18

typedef struct {
    /* 0x00 */ u8 numParticles;
    /* 0x02 */ Vec3s position;
    /* 0x08 */ Color_RGBA8 primColorStart;
    /* 0x0C */ Color_RGBA8 envColorStart;
    /* 0x10 */ Color_RGBA8 primColorMid;
    /* 0x14 */ Color_RGBA8 envColorMid;
    /* 0x18 */ Color_RGBA8 primColorEnd;
    /* 0x1C */ Color_RGBA8 envColorEnd;
    /* 0x20 */ f32 acceleration;
    /* 0x24 */ f32 maxInitialSpeed;
    /* 0x28 */ f32 lengthCutoff;
    /* 0x2C */ u8 duration;
    /* 0x2E */ LightPoint lightPoint;
    /* 0x3C */ s32 hasLight;
} EffShieldParticleInit; // size = 0x40

typedef struct {
    /* 0x000 */ EffShieldParticleParticle particles[16];
    /* 0x180 */ u8 numParticles;
    /* 0x181 */ UNK_TYPE1 pad181[0x1];
    /* 0x182 */ Vec3s position;
    /* 0x188 */ Color_RGBA8 primColorStart;
    /* 0x18C */ Color_RGBA8 envColorStart;
    /* 0x190 */ Color_RGBA8 primColorMid;
    /* 0x194 */ Color_RGBA8 envColorMid;
    /* 0x198 */ Color_RGBA8 primColorEnd;
    /* 0x19C */ Color_RGBA8 envColorEnd;
    /* 0x1A0 */ f32 acceleration;
    /* 0x1A4 */ UNK_TYPE1 pad1A4[0x4];
    /* 0x1A8 */ f32 maxInitialSpeed;
    /* 0x1AC */ f32 lengthCutoff;
    /* 0x1B0 */ u8 duration;
    /* 0x1B1 */ u8 age;
    /* 0x1B2 */ LightInfo lightInfo;
    /* 0x1C0 */ LightNode* light;
    /* 0x1C4 */ s32 hasLight;
} EffShieldParticleParams; // size = 0x1C8

typedef struct {
    /* 0x000 */ EffCommon base;
    /* 0x004 */ EffShieldParticleParams params;
} EffShieldParticle; // size = 0x1CC

typedef struct {
    /* 0x00 */ UNK_TYPE2 active;
    /* 0x02 */ Vec3s position1;
    /* 0x08 */ Vec3s position2;
    /* 0x0E */ s16 life;
    /* 0x10 */ UNK_TYPE1 pad10[0x4];
    /* 0x14 */ UNK_TYPE4 unk14;
} EffTireMarkParticle; // size = 0x18

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 maxLife;
    /* 0x4 */ Color_RGBA8 color;
} EffTireMarkInit; // size = 0x8

typedef struct {
    /* 0x000 */ EffTireMarkParticle particles[64];
    /* 0x600 */ s16 unk600;
    /* 0x602 */ s16 numParticles;
    /* 0x604 */ s16 maxLife;
    /* 0x606 */ Color_RGBA8 color;
    /* 0x60A */ UNK_TYPE1 pad60A[0x2];
} EffTireMarkParams; // size = 0x60C

typedef struct {
    /* 0x000 */ EffCommon base;
    /* 0x004 */ EffTireMarkParams params;
} EffTireMark; // size = 0x610

typedef struct {
    /* 0x00 */ u32 paramsSize;
    /* 0x04 */ eff_init_func init;
    /* 0x08 */ eff_destroy_func destroy;
    /* 0x0C */ eff_update_func update;
    /* 0x10 */ eff_draw_func draw;
} EffInfo; // size = 0x14

typedef struct {
    /* 0x0000 */ struct GlobalContext* ctxt;
    /* 0x0004 */ EffSpark sparks[3];
    /* 0x0E5C */ EffBlure blures[25];
    /* 0x388C */ EffShieldParticle shieldParticles[3];
    /* 0x3DF0 */ EffTireMark tireMarks[15];
} EffTables; // size = 0x98E0

typedef struct {
    /* 0x00 */ Vec3f position;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f acceleration;
    /* 0x24 */ Color_RGBA8 color1;
    /* 0x28 */ Color_RGBA8 color2;
    /* 0x2C */ s16 scale;
    /* 0x2E */ s16 scaleChangePerFrame;
    /* 0x30 */ s16 life;
    /* 0x32 */ u16 flags; // bit0: ? bit1: ? bit2: randomize colors
    /* 0x34 */ u8 type; // type0: start small, get big, fade away type1: start big, fade away
} EffectDustInit; // size = 0x35

typedef struct LoadedParticleEntry LoadedParticleEntry;

typedef void(*effect_func)(struct GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle);

typedef void(*effect_init_func)(struct GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle, void* init);

struct LoadedParticleEntry {
    /* 0x00 */ Vec3f position;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f acceleration;
    /* 0x24 */ effect_func update;
    /* 0x28 */ effect_func draw;
    /* 0x2C */ Vec3f unk2C;
    /* 0x38 */ u32 displayList;
    /* 0x3C */ UNK_TYPE4 unk3C;
    /* 0x40 */ s16 regs[13]; // These are particle-specific
    /* 0x5A */ u16 flags; // bit 0: set if this entry is not considered free on a priority tie bit 1: ? bit 2: ?
    /* 0x5C */ s16 life; // -1 means this entry is free
    /* 0x5E */ u8 priority; // Lower number mean higher priority
    /* 0x5F */ u8 type;
}; // size = 0x60

typedef struct {
    /* 0x0 */ LoadedParticleEntry* data_table; // Name from debug assert
    /* 0x4 */ s32 searchIndex;
    /* 0x8 */ s32 size;
} EffectTableInfo; // size = 0xC

typedef struct {
    /* 0x0 */ UNK_TYPE4 unk0;
    /* 0x4 */ effect_init_func init;
} ParticleOverlayInfo; // size = 0x8

typedef struct {
    /* 0x00 */ u32 vromStart;
    /* 0x04 */ u32 vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr;
    /* 0x14 */ ParticleOverlayInfo* overlayInfo;
    /* 0x18 */ u32 unk18; // Always 0x01000000?
} ParticleOverlay; // size = 0x1C

typedef enum EffectSSType {
    EFFECT_SS2_TYPE_DUST = 0x0,
    EFFECT_SS2_TYPE_SPARKLE = 0x1,
    EFFECT_SS2_TYPE_DELETED_2 = 0x2,
    EFFECT_SS2_TYPE_BOMB2 = 0x3,
    EFFECT_SS2_TYPE_BLAST = 0x4,
    EFFECT_SS2_TYPE_G_SPARK = 0x5,
    EFFECT_SS2_TYPE_DODONGO_FIRE = 0x6,
    EFFECT_SS2_TYPE_BUBBLE = 0x7,
    EFFECT_SS2_TYPE_DELETED_8 = 0x8,
    EFFECT_SS2_TYPE_G_RIPPLE = 0x9,
    EFFECT_SS2_TYPE_G_SPLASH = 0xA,
    EFFECT_SS2_TYPE_DELETED_B = 0xB,
    EFFECT_SS2_TYPE_G_FIRE = 0xC,
    EFFECT_SS2_TYPE_LIGHTNING = 0xD,
    EFFECT_SS2_TYPE_BIG_OCTO_BUBBLE = 0xE,
    EFFECT_SS2_TYPE_FRAGMENT = 0xF,
    EFFECT_SS2_TYPE_STICK = 0x10,
    EFFECT_SS2_TYPE_SPLASH = 0x11,
    EFFECT_SS2_TYPE_DELETED_12 = 0x12,
    EFFECT_SS2_TYPE_DELETED_13 = 0x13,
    EFFECT_SS2_TYPE_STONE1 = 0x14,
    EFFECT_SS2_TYPE_HIT_MARK = 0x15,
    EFFECT_SS2_TYPE_PHANTOM_GANON_FLASH = 0x16,
    EFFECT_SS2_TYPE_KAKARIKO_FIRE = 0x17,
    EFFECT_SS2_TYPE_SOLDIER_SEARCH_BALL = 0x18,
    EFFECT_SS2_TYPE_SHARD = 0x19,
    EFFECT_SS2_TYPE_ICE_PIECE = 0x1A,
    EFFECT_SS2_TYPE_ENEMY_ICE = 0x1B,
    EFFECT_SS2_TYPE_FIRE_TAIL = 0x1C,
    EFFECT_SS2_TYPE_ENEMY_FIRE = 0x1D,
    EFFECT_SS2_TYPE_EXTRA = 0x1E,
    EFFECT_SS2_TYPE_DELETED_1F = 0x1F,
    EFFECT_SS2_TYPE_DEAD_DEKU_BABA = 0x20,
    EFFECT_SS2_TYPE_DEAD_DODONGO = 0x21,
    EFFECT_SS2_TYPE_DEAD_DEKU_SCRUB = 0x22,
    EFFECT_SS2_TYPE_DELETED_23 = 0x23,
    EFFECT_SS2_TYPE_ICE_SMOKE = 0x24,
    EFFECT_SS2_TYPE_ICE_BLOCK = 0x25,
    EFFECT_SS2_TYPE_SBN = 0x26,
    EFFECT_SS2_TYPE_LAST_LABEL = 0x27
} EffectSSType;

#endif
