#ifndef Z_DOOR_ANA_H
#define Z_DOOR_ANA_H

#include "global.h"

struct DoorAna;

typedef void (*DoorAnaActionFunc)(struct DoorAna*, GlobalContext*);

typedef struct DoorAna {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder bombCollider;
    /* 0x190 */ DoorAnaActionFunc actionFunc;
} DoorAna; // size = 0x194

extern const ActorInit Door_Ana_InitVars;

#define DOORANA_TYPE_VISIBLE            0x000
#define DOORANA_TYPE_HIDDEN_STORMS      0x100 // Unused, leftover from OoT 
#define DOORANA_TYPE_HIDDEN_BOMB        0x200
#define DOORANA_TYPE_VISIBLE_SCENE_EXIT 0x300 // Destination dependent on scene exit list
#define DOORANA_TYPE_BITRANGE           0x300

#define DOORANA_GET_TYPE(this)(this->actor.params & 0x300)

#define DOORANA_GET_ENTRANCE(this) ((((this)->actor.params >> 12) & 0x7) - 1) 
#define DOORANA_GET_EX_ENTRANCE(this) (this->actor.home.rot.z + 1)
#define DOORANA_GET_EXIT_INDEX(this) ((this)->actor.params & 0x1F)
#define DOORANA_GET_ITEMFLAGS(this) ((this)->actor.params & 0xFF) 

#endif // Z_DOOR_ANA_H
