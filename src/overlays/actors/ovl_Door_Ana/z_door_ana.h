#ifndef _Z_DOOR_ANA_H_
#define _Z_DOOR_ANA_H_

#include <global.h>

struct DoorAna;

typedef struct DoorAna {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} DoorAna; // size = 0x194

extern const ActorInit Door_Ana_InitVars;

#endif
