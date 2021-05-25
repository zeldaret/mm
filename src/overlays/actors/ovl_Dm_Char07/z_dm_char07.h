#ifndef Z_DM_CHAR07_H
#define Z_DM_CHAR07_H

#include <global.h>

struct DmChar07;

typedef void (*DmChar07ActionFunc)(struct DmChar07*, GlobalContext*);

typedef struct DmChar07 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ char pad15C[0x14C];
    /* 0x2A8 */ DmChar07ActionFunc actionFunc;
    /* 0x2AC */ char pad2AC[0xD];
    /* 0x2B9 */ u8 unk2B9;
    /* 0x2BA */ u8 unk2BA;
} DmChar07; // size = 0x2BC

extern const ActorInit Dm_Char07_InitVars;

#endif // Z_DM_CHAR07_H
