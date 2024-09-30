#ifndef Z64ACTOR_DLFTBLS_H
#define Z64ACTOR_DLFTBLS_H

#include "PR/ultratypes.h"
#include "stdint.h"
#include "segment_symbols.h"

// This value is hardcoded to be the size of ovl_Arrow_Fire which currently is the biggest actor that uses the AM_FIELD.
DECLARE_OVERLAY_SEGMENT(Arrow_Fire)
#define AM_FIELD_SIZE SEGMENT_SIZE(ovl_Arrow_Fire)

struct ActorProfile;

#define DEFINE_ACTOR(_name, enumValue, _allocType, _debugName) enumValue,
#define DEFINE_ACTOR_INTERNAL(_name, enumValue, _allocType, _debugName) enumValue,
#define DEFINE_ACTOR_UNSET(enumValue) enumValue,

typedef enum ActorId {
    #include "tables/actor_table.h"
    /* 0x2B2 */ ACTOR_ID_MAX // originally "ACTOR_DLF_MAX"
} ActorId;

#undef DEFINE_ACTOR
#undef DEFINE_ACTOR_INTERNAL
#undef DEFINE_ACTOR_UNSET

typedef enum AllocType {
    /* 0 */ ALLOCTYPE_NORMAL,
    /* 1 */ ALLOCTYPE_ABSOLUTE,
    /* 2 */ ALLOCTYPE_PERMANENT
} AllocType;

typedef struct ActorOverlay {
    /* 0x00 */ RomFile file;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ struct ActorProfile* profile;
    /* 0x18 */ char* name;
    /* 0x1C */ u16 allocType; // bit 0: don't allocate memory, use actorContext->0x250? bit 1: Always keep loaded?
    /* 0x1E */ s8 numLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20

void ActorOverlayTable_Init(void);
void ActorOverlayTable_Cleanup(void);

extern ActorOverlay gActorOverlayTable[ACTOR_ID_MAX];
extern ActorId gMaxActorId;

#endif
