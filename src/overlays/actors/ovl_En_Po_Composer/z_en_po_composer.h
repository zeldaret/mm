#ifndef Z_EN_PO_COMPOSER_H
#define Z_EN_PO_COMPOSER_H

#include "global.h"
#include "objects/object_po_composer/object_po_composer.h"

#define PO_COMPOSER_IS_FLAT(actor) ((actor)->params & 0x8000)

typedef enum {
    COMPOSER_CS_ACTION_IDLE = 1,
    COMPOSER_CS_ACTION_APPEAR_SPIN,
    COMPOSER_CS_ACTION_IDLE2,
    COMPOSER_CS_ACTION_RAISE_ARMS,
    COMPOSER_CS_ACTION_LOWER_ARMS,
    COMPOSER_CS_ACTION_PLAY_CURSE,
    COMPOSER_CS_ACTION_ROLL,
    COMPOSER_CS_ACTION_APPEAR,
    COMPOSER_CS_ACTION_DISAPPEAR,
    COMPOSER_CS_ACTION_DONE,

    COMPOSER_CS_ACTION_NONE = 99
} EnPoComposerCutsceneAction;

struct EnPoComposer;

typedef void (*EnPoComposerActionFunc)(struct EnPoComposer*, PlayState*);

typedef struct EnPoComposer {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder bodyCollider;
    /* 0x190 */ ColliderJntSph lanternCollider;
    /* 0x1B0 */ ColliderJntSphElement lanternColliderElements[1];
    /* 0x1F0 */ SkelAnime skelAnime;
    /* 0x234 */ EnPoComposerActionFunc actionFunc;
    /* 0x238 */ MtxF lanternMtxF;
    /* 0x278 */ LightNode* lightNode;
    /* 0x27C */ LightInfo lightInfo;
    /* 0x28A */ char unk_28A[0x6];
    /* 0x290 */ s32 unk290; // cutscene to play
    /* 0x294 */ Vec3s jointTable[OBJECT_PO_COMPOSER_LIMB_MAX];
    /* 0x2DC */ Vec3s morphTable[OBJECT_PO_COMPOSER_LIMB_MAX];
    /* 0x324 */ s16 csIndices[4];
    /* 0x32C */ s16 actionTimer;
    /* 0x32E */ s16 csActionTimer;
    /* 0x330 */ s16 unk330; // boolean, do respond to cs actions?
    /* 0x332 */ s16 visible;
    /* 0x334 */ u16 lastCsAction;
    /* 0x336 */ Color_RGBA8 lightColor;
    /* 0x33A */ Color_RGBA8 envColor;
} EnPoComposer; // size = 0x340

#endif // Z_EN_PO_COMPOSER_H
