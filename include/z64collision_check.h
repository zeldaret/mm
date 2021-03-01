#ifndef _Z_COLLISION_CHECK_H_
#define _Z_COLLISION_CHECK_H_

#include <PR/ultratypes.h>
#include <z64math.h>
#include <unk.h>

struct Actor;

typedef struct {
    /* 0x00 */ struct Actor* actor; // Attached actor
    /* 0x04 */ struct Actor* at;    // Actor attached to what it collided with as an AT collider.
    /* 0x08 */ struct Actor* ac;    // Actor attached to what it collided with as an AC collider.
    /* 0x0C */ struct Actor* oc;    // Actor attached to what it collided with as an OC collider.
    /* 0x10 */ u8 atFlags;          // Information flags for AT collisions. 
    /* 0x11 */ u8 acFlags;          // Information flags for AC collisions.
    /* 0x12 */ u8 ocFlags1;         // Information flags for OC collisions.
    /* 0x13 */ u8 ocFlags2;         // Flags related to which colliders it can OC collide with.
    /* 0x14 */ u8 colType;          // Determines hitmarks and sound effects during AC collisions.
    /* 0x15 */ u8 shape;            // JntSph, Cylinder, Tris, or Quad
} Collider; // size = 0x18

typedef struct {
    /* 0x00 */ u8 colType;  // Determines hitmarks and sound effects during AC collisions.
    /* 0x01 */ u8 atFlags;  // Information flags for AT collisions. 
    /* 0x02 */ u8 acFlags;  // Information flags for OC collisions.
    /* 0x03 */ u8 ocFlags1; // Information flags for OC collisions.
    /* 0x04 */ u8 ocFlags2; // Flags related to which colliders it can OC collide with.
    /* 0x05 */ u8 shape;    // JntSph, Cylinder, Tris, or Quad
} ColliderInit; // size = 0x06

typedef struct {
    /* 0x00 */ u8 colType;  // Determines hitmarks and sound effects during AC collisions.
    /* 0x01 */ u8 atFlags;  // Information flags for AT collisions. 
    /* 0x02 */ u8 acFlags;  // Information flags for AC collisions.
    /* 0x03 */ u8 ocFlags1; // Information flags for OC collisions.
    /* 0x04 */ u8 shape;    // JntSph, Cylinder, Tris, or Quad
} ColliderInitType1; // size = 0x05

typedef struct {
    /* 0x00 */ struct Actor* actor; // Attached actor
    /* 0x04 */ u8 atFlags;          // Information flags for AT collisions.
    /* 0x05 */ u8 acFlags;          // Information flags for AC collisions.
    /* 0x06 */ u8 ocFlags1;         // Information flags for OC collisions.
    /* 0x07 */ u8 shape;            // JntSph, Cylinder, Tris, or Quad
} ColliderInitToActor; // size = 0x08

typedef struct {
    /* 0x00 */ u32 dmgFlags;    // Toucher damage type flags.
    /* 0x04 */ u8  effect;      // Damage Effect (Knockback, Fire, etc.)
    /* 0x05 */ u8  damage;      // Damage or Stun Timer
} ColliderTouch; // size = 0x08

typedef struct {
    /* 0x00 */ u32 dmgFlags;    // Toucher damage type flags.
    /* 0x04 */ u8  effect;      // Damage Effect (Knockback, Fire, etc.)
    /* 0x05 */ u8  damage;      // Damage or Stun Timer
} ColliderTouchInit; // size = 0x08

typedef struct {
    /* 0x00 */ u32   dmgFlags;  // Bumper damage type flags.
    /* 0x04 */ u8    effect;    // Damage Effect (Knockback, Fire, etc.)
    /* 0x05 */ u8    defense;   // Damage Resistance
    /* 0x06 */ Vec3s hitPos;    // Point of contact
} ColliderBump; // size = 0x0C

typedef struct {
    /* 0x00 */ u32 dmgFlags;    // Bumper exclusion mask
    /* 0x04 */ u8  effect;      // Damage Effect (Knockback, Fire, etc.)
    /* 0x05 */ u8  defense;     // Damage Resistance
} ColliderBumpInit; // size = 0x08

typedef struct ColliderInfo {
    /* 0x00 */ ColliderTouch toucher;           // Damage properties when acting as an AT collider
    /* 0x08 */ ColliderBump  bumper;            // Damage properties when acting as an AC collider
    /* 0x14 */ u8 elemType;                     // Affects sfx reaction when attacked by Link and hookability. Full purpose unknown.
    /* 0x15 */ u8 toucherFlags;                 // Information flags for AT collisions
    /* 0x16 */ u8 bumperFlags;                  // Information flags for AC collisions
    /* 0x17 */ u8 ocElemFlags;                  // Information flags for OC collisions
    /* 0x18 */ Collider* atHit;                 // object touching this element's AT collider
    /* 0x1C */ Collider* acHit;                 // object touching this element's AC collider
    /* 0x20 */ struct ColliderInfo* atHitInfo;  // element that hit the AT collider
    /* 0x24 */ struct ColliderInfo* acHitInfo;  // element that hit the AC collider
} ColliderInfo; // size = 0x28

typedef struct {
    /* 0x00 */ u8 elemType;                 // Affects sfx reaction when attacked by Link and hookability. Full purpose unknown.
    /* 0x04 */ ColliderTouchInit toucher;   // Damage properties when acting as an AT collider
    /* 0x0C */ ColliderBumpInit  bumper;    // Damage properties when acting as an AC collider
    /* 0x14 */ u8 toucherFlags;             // Information flags for AT collisions
    /* 0x15 */ u8 bumperFlags;              // Information flags for AC collisions
    /* 0x16 */ u8 ocElemFlags;              // Information flags for OC collisions
} ColliderInfoInit; // size = 0x18

typedef struct {
    /* 0x00 */ Sphere16 modelSphere;    // model space sphere
    /* 0x08 */ Sphere16 worldSphere;    // world space sphere
    /* 0x10 */ f32      scale;          // worldsphere = modelsphere * scale * 0.01
    /* 0x14 */ u8       limb;           // attached limb
} ColliderJntSphElementDim; // size = 0x18

typedef struct {
    /* 0x00 */ u8       limb;           // attached limb
    /* 0x02 */ Sphere16 modelSphere;    // model space sphere
    /* 0x0A */ s16      scale;          // world space sphere = model * scale * 0.01
} ColliderJntSphElementDimInit; // size = 0x0C

typedef struct {
    /* 0x00 */ ColliderInfo info;
    /* 0x28 */ ColliderJntSphElementDim dim;
} ColliderJntSphElement; // size = 0x40

typedef struct {
    /* 0x00 */ ColliderInfoInit info;
    /* 0x18 */ ColliderJntSphElementDimInit dim;
} ColliderJntSphElementInit; // size = 0x24

typedef struct {
    /* 0x00 */ Collider base;
    /* 0x18 */ s32 count;
    /* 0x1C */ ColliderJntSphElement* elements;
} ColliderJntSph; // size = 0x20

typedef struct {
    /* 0x0 */ ColliderInit base;
    /* 0x8 */ s32 count;
    /* 0xC */ ColliderJntSphElementInit* elements;
} ColliderJntSphInit; // size = 0x10

typedef struct {
    /* 0x00 */ ColliderInitType1 base;
    /* 0x08 */ s32 count;
    /* 0x0C */ ColliderJntSphElementInit* elements;
} ColliderJntSphInitType1; // size = 0x10

typedef struct {
    /* 0x00 */ ColliderInitToActor base;
    /* 0x08 */ s32 count;
    /* 0x0C */ ColliderJntSphElementInit* elements;
} ColliderJntSphInitToActor; // size = 0x10

typedef struct {
    /* 0x00 */ Collider     base;
    /* 0x18 */ ColliderInfo info;
    /* 0x40 */ Cylinder16   dim;
} ColliderCylinder; // size = 0x4C

typedef struct {
    /* 0x00 */ ColliderInit     base;
    /* 0x08 */ ColliderInfoInit info;
    /* 0x20 */ Cylinder16       dim;
} ColliderCylinderInit; // size = 0x2C

typedef struct {
    /* 0x00 */ ColliderInitType1 base;
    /* 0x08 */ ColliderInfoInit  info;
    /* 0x20 */ Cylinder16        dim;
} ColliderCylinderInitType1; // size = 0x2C

typedef struct {
    /* 0x00 */ ColliderInitToActor base;
    /* 0x08 */ ColliderInfoInit    info;
    /* 0x20 */ Cylinder16          dim;
} ColliderCylinderInitToActor; // size = 0x2C

typedef struct {
    /* 0x00 */ Vec3f vtx[3];
} ColliderTrisElementDimInit; // size = 0x24

typedef struct {
    /* 0x00 */ ColliderInfo info;
    /* 0x28 */ TriNorm      dim;
} ColliderTrisElement; // size = 0x5C

typedef struct {
    /* 0x00 */ ColliderInfoInit info;
    /* 0x18 */ ColliderTrisElementDimInit dim;
} ColliderTrisElementInit; // size = 0x3C

typedef struct {
    /* 0x00 */ Collider base;
    /* 0x18 */ s32 count;
    /* 0x1C */ ColliderTrisElement* elements;
} ColliderTris; // size = 0x20

typedef struct {
    /* 0x0 */ ColliderInit base;
    /* 0x8 */ s32 count;
    /* 0xC */ ColliderTrisElementInit* elements;
} ColliderTrisInit; // size = 0x10

typedef struct {
    /* 0x00 */ ColliderInitType1 base;
    /* 0x08 */ s32 count;
    /* 0x0C */ ColliderTrisElementInit* elements;
} ColliderTrisInitType1; // size = 0x10

typedef struct {
    /* 0x00 */ Vec3f quad[4];
    /* 0x30 */ Vec3s dcMid;     // midpoint of vectors d, c
    /* 0x36 */ Vec3s baMid;     // midpoint of vectors b, a
    /* 0x3C */ f32   acDist;    // distance to nearest AC collision this frame.
} ColliderQuadDim; // size = 0x40

typedef struct {
    /* 0x00 */ Vec3f quad[4];
} ColliderQuadDimInit; // size = 0x30

typedef struct {
    /* 0x00 */ Collider        base;
    /* 0x18 */ ColliderInfo    info;
    /* 0x40 */ ColliderQuadDim dim;
} ColliderQuad; // size = 0x80

typedef struct {
    /* 0x00 */ ColliderInit        base;
    /* 0x08 */ ColliderInfoInit    info;
    /* 0x20 */ ColliderQuadDimInit dim;
} ColliderQuadInit; // size = 0x50

typedef struct {
    /* 0x00 */ ColliderInitType1   base;
    /* 0x08 */ ColliderInfoInit    info;
    /* 0x20 */ ColliderQuadDimInit dim;
} ColliderQuadInitType1; // size = 0x50

typedef struct {
    /* 0x00 */ Collider     base;
    /* 0x18 */ ColliderInfo info;
    /* 0x40 */ ColliderJntSphElementDim dim;
} ColliderSphere; // size = 0x58

typedef struct {
    /* 0x00 */ ColliderInit     base;
    /* 0x08 */ ColliderInfoInit info;
    /* 0x20 */ ColliderJntSphElementDimInit dim;
} ColliderSphereInit; // size = 0x2C

typedef struct {
    /* 0x00 */ LineSegment line;
    /* 0x18 */ u16         ocFlags;
} OcLine; // size = 0x1C

typedef struct {
    /* 0x000 */ s16       colATCount;
    /* 0x002 */ u16       flags;        // Controls whether new collidors can be added or removed, or only swapped
    /* 0x004 */ Collider* colAT[50];
    /* 0x0CC */ s32       colACCount;
    /* 0x0D0 */ Collider* colAC[60];
    /* 0x1C0 */ s32       colOCCount;
    /* 0x1C4 */ Collider* colOC[50];
    /* 0x28C */ s32       colLineCount;
    /* 0x290 */ OcLine*   colLine[3];
} CollisionCheckContext; // size = 0x29C

typedef struct {
    /* 0 */ u8 blood;
    /* 1 */ u8 effect;
} HitInfo; // size = 0x2

typedef enum {
    /* 0 */ BLOOD_NONE,
    /* 1 */ BLOOD_BLUE,
    /* 2 */ BLOOD_GREEN,
    /* 3 */ BLOOD_WATER,
    /* 4 */ BLOOD_RED,
    /* 5 */ BLOOD_RED2
} ColChkBloodType;

typedef enum {
    /* 0 */ HIT_WHITE,
    /* 1 */ HIT_DUST,
    /* 2 */ HIT_RED,
    /* 3 */ HIT_SOLID,
    /* 4 */ HIT_WOOD,
    /* 5 */ HIT_NONE
} ColChkHitType;

typedef enum {
    /* 0 */ MASSTYPE_IMMOVABLE,
    /* 1 */ MASSTYPE_HEAVY,
    /* 2 */ MASSTYPE_NORMAL
} ColChkMassType;

typedef enum {
    /* 0  */ COLTYPE_HIT0, // Blue blood, white hitmark
    /* 1  */ COLTYPE_HIT1, // No blood, dust hitmark
    /* 2  */ COLTYPE_HIT2, // Green blood, dust hitmark
    /* 3  */ COLTYPE_HIT3, // No blood, white hitmark
    /* 4  */ COLTYPE_HIT4, // Water burst, no hitmark
    /* 5  */ COLTYPE_HIT5, // No blood, red hitmark
    /* 6  */ COLTYPE_HIT6, // Green blood, white hitmark
    /* 7  */ COLTYPE_HIT7, // Red blood, white hitmark
    /* 8  */ COLTYPE_HIT8, // Blue blood, red hitmark
    /* 9  */ COLTYPE_METAL,
    /* 10 */ COLTYPE_NONE,
    /* 11 */ COLTYPE_WOOD,
    /* 12 */ COLTYPE_HARD,
    /* 13 */ COLTYPE_TREE
} ColliderType;

typedef enum {
    /* 0 */ COLSHAPE_JNTSPH,
    /* 1 */ COLSHAPE_CYLINDER,
    /* 2 */ COLSHAPE_TRIS,
    /* 3 */ COLSHAPE_QUAD,
    /* 4 */ COLSHAPE_SPHERE,
    /* 5 */ COLSHAPE_MAX
} ColliderShape;

typedef enum {
    /* 0 */ ELEMTYPE_UNK0,
    /* 1 */ ELEMTYPE_UNK1,
    /* 2 */ ELEMTYPE_UNK2,
    /* 3 */ ELEMTYPE_UNK3,
    /* 4 */ ELEMTYPE_UNK4,
    /* 5 */ ELEMTYPE_UNK5,
    /* 6 */ ELEMTYPE_UNK6,
    /* 7 */ ELEMTYPE_UNK7
} ElementType;

#endif
