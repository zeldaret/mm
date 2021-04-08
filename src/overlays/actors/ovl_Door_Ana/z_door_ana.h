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

#define DOORANA_TYPE_REGULAR      0x000
#define DOORANA_TYPE_UNK          0x100
#define DOORANA_TYPE_HIDDEN       0x200
#define DOORANA_TYPE_ADJACENT     0x300
#define DOORANA_TYPE_BITRANGE     0x300

#define GET_DOORANA_TYPE(this)(this->actor.params & 0x300)

#define DOORANA_TYPE_ROTATION_ENTRANCE(directEntrance)(directEntrance < 0)
#define GET_DOORANA_DIRECT_ENTRANCE(this) ((((this)->actor.params >> 0xC) & 0x7) - 1) 
#define GET_DOORANA_ADJACENT_ENTRANCE(this) ((this)->actor.params & 0x1F) 
#define GET_DOORANA_ROTATION_ENTRANCE(this) (this->actor.home.rot.z + 1) 
#define GET_DOORANA_ITEMFLAGS(this) ((this)->actor.params & 0xFF) 

#endif // Z_DOOR_ANA_H
