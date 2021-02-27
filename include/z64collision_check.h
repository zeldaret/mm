#ifndef _Z_COLLISION_CHECK_H_
#define _Z_COLLISION_CHECK_H_

#include <PR/ultratypes.h>
#include <z64math.h>
#include <unk.h>

struct Actor;

typedef struct {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} ColBumpInit; // size = 0x8

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 type;
} ColCommonInit; // size = 0x6

typedef struct {
    /* 0x0 */ u32 collidesWith;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 damage;
} ColTouch; // size = 0x8

typedef struct {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} ColTouchInit; // size = 0x8

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x04 */ ColTouchInit unk4;
    /* 0x0C */ ColBumpInit unkC;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
} ColBodyInfoInit; // size = 0x18

typedef struct {
    /* 0x0 */ u32 collidesWith;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ Vec3s unk6;
} ColBump; // size = 0xC

typedef struct {
    /* 0x0 */ s16 radius;
    /* 0x2 */ s16 height;
    /* 0x4 */ s16 yOffset;
    /* 0x6 */ Vec3s loc;
} ColCylinderParams; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f quad[4];
    /* 0x30 */ Vec3s unk30;
    /* 0x36 */ Vec3s unk36;
    /* 0x3C */ f32 unk3C;
} ColQuadParams; // size = 0x40

typedef struct {
    /* 0x00 */ Vec3f quad[4];
} ColQuadParamsInit; // size = 0x30

typedef struct {
    /* 0x0 */ Vec3s loc;
    /* 0x6 */ s16 radius;
} ColSphereCollisionInfo; // size = 0x8

typedef struct {
    /* 0x00 */ ColSphereCollisionInfo unk0;
    /* 0x08 */ ColSphereCollisionInfo colInfo;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ UNK_TYPE1 pad15[0x3];
} ColSphereParams; // size = 0x18

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ ColSphereCollisionInfo unk1;
    /* 0xA */ s16 unkA;
} ColSphereParamsInit; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f vtx[3];
    /* 0x24 */ Vec3f unitNormal;
    /* 0x30 */ f32 unk30;
} ColTriParams; // size = 0x34

typedef struct {
    /* 0x00 */ Vec3f vtx[3];
} ColTriParamsInit; // size = 0x24

typedef struct {
    /* 0x00 */ ColCommonInit base;
    /* 0x08 */ ColBodyInfoInit body;
    /* 0x20 */ ColCylinderParams info;
} ColCylinderInit; // size = 0x2C

typedef struct {
    /* 0x00 */ ColCommonInit base;
    /* 0x08 */ ColBodyInfoInit body;
    /* 0x20 */ ColQuadParamsInit params;
} ColQuadInit; // size = 0x50

typedef struct {
    /* 0x00 */ ColBodyInfoInit body;
    /* 0x18 */ ColSphereParamsInit params;
} ColSphereGroupElementInit; // size = 0x24

typedef struct {
    /* 0x0 */ ColCommonInit base;
    /* 0x6 */ UNK_TYPE1 pad6[0x2];
    /* 0x8 */ s32 count;
    /* 0xC */ ColSphereGroupElementInit* init;
} ColSphereGroupInit; // size = 0x10

typedef struct {
    /* 0x00 */ ColCommonInit base;
    /* 0x08 */ ColBodyInfoInit body;
    /* 0x20 */ ColSphereParamsInit info;
} ColSphereInit; // size = 0x2C

typedef struct {
    /* 0x00 */ ColBodyInfoInit body;
    /* 0x18 */ ColTriParamsInit params;
} ColTriInit; // size = 0x3C

typedef struct {
    /* 0x0 */ ColCommonInit base;
    /* 0x8 */ s32 count;
    /* 0xC */ ColTriInit* elemInit;
} ColTriGroupInit; // size = 0x10

typedef struct {
    /* 0x00 */ struct Actor* actor;
    /* 0x04 */ struct Actor* collisionAT;
    /* 0x08 */ struct Actor* collisionAC;
    /* 0x0C */ struct Actor* collisionOT;
    /* 0x10 */ u8 flagsAT;
    /* 0x11 */ u8 flagsAC; // bit 1 - collision occured?
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 type;
    /* 0x16 */ UNK_TYPE1 pad16[0x2];
} ColCommon; // size = 0x18

typedef struct {
    /* 0x000 */ s16 ATgroupLength;
    /* 0x002 */ u16 flags; // bit 0: collision bodies can't be added or removed, only swapped out
    /* 0x004 */ ColCommon* ATgroup[50];
    /* 0x0CC */ s32 ACgroupLength;
    /* 0x0D0 */ ColCommon* ACgroup[60];
    /* 0x1C0 */ s32 OTgroupLength;
    /* 0x1C4 */ ColCommon* OTgroup[50];
    /* 0x28C */ s32 group4Length;
    /* 0x290 */ ColCommon* group4[3];
} CollisionCheckContext; // size = 0x29C

typedef struct ColBodyInfo {
    /* 0x00 */ ColTouch toucher;
    /* 0x08 */ ColBump bumper;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15; // bit 0: can be toucher in AT-AC collision
    /* 0x16 */ u8 unk16; // bit 0: can be bumper in AT-AC collision
    /* 0x17 */ u8 unk17;
    /* 0x18 */ ColCommon* unk18;
    /* 0x1C */ ColCommon* unk1C;
    /* 0x20 */ struct ColBodyInfo* unk20;
    /* 0x24 */ struct ColBodyInfo* unk24;
} ColBodyInfo; // size = 0x28

typedef struct {
    /* 0x00 */ ColBodyInfo body;
    /* 0x28 */ ColSphereParams params;
} ColSphereGroupElement; // size = 0x40

typedef struct {
    /* 0x00 */ ColBodyInfo body;
    /* 0x28 */ ColTriParams params;
} ColTri; // size = 0x5C

typedef struct {
    /* 0x00 */ ColCommon base;
    /* 0x18 */ ColBodyInfo body;
    /* 0x40 */ ColCylinderParams params;
} ColCylinder; // size = 0x4C

typedef struct {
    /* 0x00 */ ColCommon base;
    /* 0x18 */ ColBodyInfo body;
    /* 0x40 */ ColQuadParams params;
} ColQuad; // size = 0x80

typedef struct {
    /* 0x00 */ ColCommon base;
    /* 0x18 */ ColBodyInfo body;
    /* 0x40 */ ColSphereParams params;
} ColSphere; // size = 0x58

typedef struct {
    /* 0x00 */ ColCommon base;
    /* 0x18 */ s32 count;
    /* 0x1C */ ColSphereGroupElement* spheres;
} ColSphereGroup; // size = 0x20

typedef struct {
    /* 0x00 */ ColCommon base;
    /* 0x18 */ s32 count;
    /* 0x1C */ ColTri* tris;
} ColTriGroup; // size = 0x20

#endif
