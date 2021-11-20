#ifndef Z_EN_PO_COMPOSER_H
#define Z_EN_PO_COMPOSER_H

#include "global.h"

struct EnPoComposer;

typedef void (*EnPoComposerActionFunc)(struct EnPoComposer*, GlobalContext*);

typedef struct EnPoComposer {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xF0];
    /* 0x0234 */ EnPoComposerActionFunc actionFunc;
    /* 0x0238 */ char unk_238[0x108];
} EnPoComposer; // size = 0x340

extern const ActorInit En_Po_Composer_InitVars;

#endif // Z_EN_PO_COMPOSER_H
