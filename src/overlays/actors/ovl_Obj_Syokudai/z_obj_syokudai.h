#ifndef Z_OBJ_SYOKUDAI_H
#define Z_OBJ_SYOKUDAI_H

#include "global.h"

struct ObjSyokudai;

typedef struct ObjSyokudai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder standCollider;
    /* 0x190 */ ColliderCylinder flameCollider;
    /* 0x1DC */ s16 snuffTimer;
    /* 0x1DE */ u8 flameTexScroll;
    /* 0x1DF */ s8 pendingAction;
    /* 0x1E0 */ LightNode* lightNode;
    /* 0x1E4 */ LightInfo lightInfo;
} ObjSyokudai; // size = 0x1F4

extern const ActorInit Obj_Syokudai_InitVars;

typedef enum {
    /* 0 */ OBJ_SYOKUDAI_TYPE_SWITCH_CAUSES_FLAME,
    /* 1 */ OBJ_SYOKUDAI_TYPE_FLAME_CAUSES_SWITCH,
    /* 2 */ OBJ_SYOKUDAI_TYPE_NO_SWITCH
} ObjSyokudaiTypes;

typedef enum {
    /* -1 */ OBJ_SYOKUDAI_SNUFF_NEVER = -1,
    /*  0 */ OBJ_SYOKUDAI_SNUFF_OUT
} ObjSyokudaiSnuffStates;

typedef enum {
    /* -1 */ OBJ_SYOKUDAI_PENDING_ACTION_CUTSCENE_NO_SWITCH = -1,
    /*  0 */ OBJ_SYOKUDAI_PENDING_ACTION_NONE,
    /*  1 */ OBJ_SYOKUDAI_PENDING_ACTION_CUTSCENE_AND_SWITCH
} ObjSyokudaiPendingActions;

typedef enum {
    /* -1 */ OBJ_SYOKUDAI_INTERACTION_STICK = -1,
    /*  0 */ OBJ_SYOKUDAI_INTERACTION_NONE,
    /*  1 */ OBJ_SYOKUDAI_INTERACTION_ARROW_FA
} ObjSyokudaiInteractions;

#define OBJ_SYOKUDAI_GET_TYPE(thisx) (thisx->params >> 0xC)
#define OBJ_SYOKUDAI_GET_START_LIT(thisx) (thisx->params & 0x800)
#define OBJ_SYOKUDAI_GET_GROUP_SIZE(thisx) ((thisx->params >> 7) & 0xF)
#define OBJ_SYOKUDAI_GET_SWITCH_FLAG(thisx) (thisx->params & 0x7F)

#endif // Z_OBJ_SYOKUDAI_H
