#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <PR/ultratypes.h>
#include <unk.h>
#include <os.h>

typedef struct s80085320_s {
/* 0x00 */    struct s80085320_s* next;
/* 0x04 */    struct s80085320_s* prev;
/* 0x08 */    UNK_TYPE* unk8;
/* 0x0C */    UNK_TYPE* unkC;
/* 0x10 */    UNK_TYPE unk10;
/* 0x14 */    UNK_TYPE unk14;
/* 0x18 */    UNK_TYPE* unk18;
} s80085320;

typedef struct {
/* 0x0 */    UNK_TYPE unk0;
/* 0x4 */    UNK_TYPE unk4;
/* 0x8 */    UNK_TYPE unk8;
/* 0xC */    UNK_TYPE unkC;
} s8008A6FC;

// TODO this should extend from z_Actor
typedef struct s800A5AC0_s {
	/* 0x000 */ u8 pad0[0x1C];
	/* 0x01C */ s16 unk1C;
	/* 0x01E */ u8 pad1[0x74];
	/* 0x092 */ s16 unk92;
	/* 0x094 */ u8 pad2[0x22];
	/* 0x0B6 */ u8 unkB6;
	/* 0x0B7 */ u8 pad4[5];
	/* 0x0BC */ u16 unkBC; // or char
	/* 0x0BE */ s16 unkBE;
	/* 0x0C0 */ u8 pad5[0x56];
	/* 0x116 */ u16 unk116;
	/* 0x118 */ u8 pad6[0x2C];
	/* 0x144 */ void(*unk144)(struct s800A5AC0_s*, UNK_TYPE);
	/* 0x148 */ UNK_TYPE unk148;
} s800A5AC0;

typedef struct {
	/* 0x00 */ u8 pad0[8];
	/* 0x08 */ UNK_TYPE unk8;
	/* 0x0C */ UNK_TYPE unkC;
	/* 0x10 */ u32 unk10;
	/* 0x14 */ u8 pad1[0xA];
	/* 0x1E */ s8 unk1E;
	/* 0x1F */ u8 pad2[1];
} s800BF9A0;

typedef struct {
	/* 0x00 */ UNK_TYPE unk0;
	/* 0x04 */ UNK_TYPE unk4;
	/* 0x08 */ UNK_TYPE unk8;
	/* 0x12 */ u8 pad0[0x5C];
	/* 0x68 */ UNK_TYPE unk68;
	/* 0x6C */ UNK_TYPE unk6C;
	/* 0x70 */ UNK_TYPE unk70;
	/* 0x72 */ u16 unk72;
	/* 0x74 */ u16 unk74;
	/* 0x76 */ u16 unk76;
	/* 0x78 */ u8 pad1[2];
	/* 0x7C */ f32 unk7C;
	/* 0x80 */ f32 unk80;
	/* 0x84 */ f32 unk84;
	/* 0x88 */ UNK_TYPE unk88;
	/* 0x8C */ UNK_TYPE unk8C;
	/* 0x90 */ UNK_TYPE unk90;
	/* 0x94 */ u16 unk94;
	/* 0x96 */ u16 unk96;
	/* 0x98 */ u16 unk98;
	/* 0x9A */ u8 pad2[2];
	/* 0x9C */ f32 unk9C;
	/* 0xA0 */ f32 unkA0;
	/* 0xA4 */ f32 unkA4;
} s800CAAD0;

typedef struct {
    /* 0x00 */ u8 pad[0x20];
} s800E03A0;

// Entries in dmadata
typedef struct {
    /* 0x0 */ u32 vromStart;
    /* 0x4 */ u32 vromEnd;
    /* 0x8 */ u32 romStart;
    /* 0xC */ u32 romEnd;
} DmadataEntry;

typedef struct {
    /* 0x00 */ UNK_PTR unk0;
    /* 0x04 */ UNK_FUN_PTR(unk4);
    /* 0x08 */ UNK_TYPE unk8;
    /* 0x0C */ u8 pad1[8];
    /* 0x14 */ UNK_TYPE unk14;
    /* 0x18 */ OSMesgQueue* unk18;
    /* 0x1C */ UNK_TYPE unk1C;
} s80080A08;

// This struct is huge! Global context?
typedef struct {
    /* 0x00000 */ u8 pad[0x167F8];
    /* 0x167F8 */ u8 unk167F8;
} s800F4F54;

typedef struct {
	/* 0x0 */ f32 x;
	/* 0x4 */ f32 y;
	/* 0x8 */ f32 z;
} z_Vector3D;

struct z_Actor;

typedef void(*z_ActorFunc)(struct z_Actor*, void*);

typedef struct {
	/* 0x000 */ u8 pad0[4];
	/* 0x004 */ UNK_TYPE unk4;
	/* 0x008 */ u8 pad1[0x14];
	/* 0x01C */ s16 unk1C;
	/* 0x01E */ u8 pad2[0x3A];
	/* 0x058 */ z_Vector3D unk58; // scale?
	/* 0x064 */ u8 pad3[0x2E];
	/* 0x092 */ s16 unk92;
	/* 0x094 */ u8 pad4[0x22];
	/* 0x0B6 */ u8 unkB6;
	/* 0x0B7 */ u8 pad5[5];
	/* 0x0BC */ u16 unkBC; // or char
	/* 0x0BE */ s16 unkBE;
	/* 0x0C0 */ u8 pad6[0x3C];
	/* 0x0FC */ f32 unkFC; // start of z_Vector3D?
	/* 0x100 */ f32 unk100;
	/* 0x104 */ f32 unk104;
	/* 0x108 */ u8 pad7[0xE];
	/* 0x116 */ u16 unk116;
	/* 0x118 */ u8 pad8[0x24];
	/* 0x13C */ z_ActorFunc drawFunc;
	/* 0x140 */ u8 pad9[4];
	// TODO figure out what size this is
} z_Actor;

typedef struct s80BD5530_s {
	/* 0x00000 */ u8 pad[0x18884];
	/* 0x18884 */ UNK_TYPE unk18884;
} z_GlobalContext;

typedef struct {
	u32 cont : 1;
	u32 type : 4;
	u32 offset : 11;
	u32 value : 16;
} z_ActorCompInitEntry;

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8  type; // Classifies actor and determines when actor will execute
    /* 0x03 */ u8  room; // Room instance was spawned in. If value set to FF in
	                     // rom, instance does not despawn when swapping rooms
    /* 0x04 */ s32 flags; // unknown
    /* 0x08 */ s16 objectId; // Possibly it's primary object dependency
    /* 0x0A */ // Padding
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ z_ActorFunc init; // Constructor
    /* 0x14 */ z_ActorFunc fini; // Destructor
    /* 0x18 */ z_ActorFunc main; // Main Update Function
    /* 0x1C */ z_ActorFunc draw; // Draw function
} z_ActorInit;

// TODO everything past here should be placed in an appropiate libultra header

typedef long Mtx_t[4][4];

typedef union {
    /* 0x0 */ Mtx_t m;
    /* 0x0 */ long long force_structure_alignment;
} Mtx;


typedef struct {
    /* 0x0 */ int quot;
    /* 0x4 */ int rem;
} div_t;


typedef struct {
    /* 0x0 */ long quot;
    /* 0x4 */ long rem;
} ldiv_t;


typedef struct {
    /* 0x0 */ long long quot;
    /* 0x8 */ long long rem;
} lldiv_t;

typedef unsigned int size_t;

typedef double ldouble;

typedef struct {
    /* 0x0 */ union {
        /* 0x0 */ long long ll;
        /* 0x0 */ ldouble ld;
    } v;
    /* 0x8 */ unsigned char* s;
    /* 0xC */ int n0;
    /* 0x10 */ int nz0;
    /* 0x14 */ int n1;
    /* 0x18 */ int nz1;
    /* 0x1C */ int n2;
    /* 0x20 */ int nz2;
    /* 0x24 */ int prec;
    /* 0x28 */ int width;
    /* 0x2C */ size_t nchar;
    /* 0x30 */ unsigned int flags;
    /* 0x34 */ unsigned char qual;
} _Pft;

#endif
