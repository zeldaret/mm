#ifndef Z_OBJ_MU_PICT_H
#define Z_OBJ_MU_PICT_H

#include <global.h>

struct ObjMuPict;

#define UNK_ACTOR_PARAM ((this->actor.params & 0xF000) >> 0xC)

typedef void (*ObjMuPictActionFunc)(struct ObjMuPict*, GlobalContext*);

typedef struct ObjMuPict {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjMuPictActionFunc actionFunc;
    /* 0x148 */ s16 unk148;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ u16 textId;
} ObjMuPict; // size = 0x150

extern const ActorInit Obj_Mu_Pict_InitVars;


#endif // Z_OBJ_MU_PICT_H
