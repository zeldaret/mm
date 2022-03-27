#ifndef Z_DM_CHAR08_H
#define Z_DM_CHAR08_H

#include "global.h"

struct DmChar08;

typedef void (*DmChar08ActionFunc)(struct DmChar08*, GlobalContext*);

typedef struct DmChar08 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;                   /* inferred */
    /* 0x1A0 */ DmChar08ActionFunc actionFunc;
    /* 0x1A4 */ Actor *unk1A4;                      /* inferred */
    /* 0x1A8 */ Actor *unk1A8;                      /* inferred */
    /* 0x1AC */ Vec3f unk1AC;                         /* inferred */
    /* 0x1B8 */ Vec3f unk1B8;                       /* inferred */    
    /* 0x1C4 */ Vec3f unk1C4;     
    /* 0x1D0 */ Vec3f unk1D0;
    /* 0x1DC */ char pad1DC[8];                     /* maybe part of unk1D8[3]? */                 /* maybe part of unk1A8[0xF]? */
    /* 0x1E4 */ f32 unk1E4;                         /* inferred */
    /* 0x1E8 */ char pad1E8[8];                     /* maybe part of unk1E4[3]? */
    /* 0x1F0 */ f32 unk1F0;                         /* inferred */
    /* 0x1F4 */ s16 unk1F4;                         /* inferred */
    /* 0x1F6 */ s16 unk1F6;
    /* 0x1F6 */ s16 unk1F8;
    /* 0x1FA */ s16 unk1FA;                         /* inferred */
    /* 0x1FC */ u16 unk1FC;                        /* inferred */
    /* 0x1FE */ u8 unk1FE;                          /* inferred */
    /* 0x1FF */ u8 unk1FF;                          /* inferred */
    /* 0x200 */ u8 unk200;                          /* inferred */
    /* 0x201 */ u8 unk201;
    /* 0x202 */ u8 unk202;                          /* inferred */
    /* 0x203 */ u8 unk203;                          /* inferred */
    /* 0x204 */ char pad204[1];
    /* 0x205 */ u8 unk205;                          /* inferred */
    /* 0x206 */ u8 pad206;
    /* 0x207 */ u8 unk207;                          /* inferred */
    /* 0x208 */ u8 unk208;                          /* inferred */
    /* 0x209 */ s8 unk209;                          /* inferred */
    /* 0x20A */ char pad20A[2];                     /* maybe part of unk209[3]? */
} DmChar08;   

extern const ActorInit Dm_Char08_InitVars;

#endif // Z_DM_CHAR08_H
