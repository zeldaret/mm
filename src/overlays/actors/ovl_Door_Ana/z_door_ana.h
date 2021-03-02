#ifndef Z_DOOR_ANA_H
#define Z_DOOR_ANA_H

#include <global.h>

struct DoorAna;

typedef void (*DoorAnaActionFunc)(struct DoorAna*, GlobalContext*);

typedef struct DoorAna {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder bombCollider;
    /* 0x190 */ DoorAnaActionFunc actionFunc;
} DoorAna; // size = 0x194

extern const ActorInit Door_Ana_InitVars;

extern Gfx D_05000C40[];

#define DOORANA_TYPE_REGULAR  0x000
#define DOORANA_TYPE_UNK      0x100
#define DOORANA_TYPE_HIDDEN   0x200
#define DOORANA_TYPE_ADJACENT 0x300
#define DOORANA_TYPE_BITRANGE 0x300

#define GET_DOORANA_TYPE(thisx)(this->actor.params & 0x300)

#endif // Z_DOOR_ANA_H
