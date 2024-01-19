#ifndef Z_OBJ_MAKEKINSUTA_H
#define Z_OBJ_MAKEKINSUTA_H

#include "global.h"

struct ObjMakekinsuta;

#define OBJMAKEKINSUTA_GET_1F(thisx) (((thisx)->params >> 8) & 0x1F)
#define OBJMAKEKINSUTA_GETS_3(params) ((params & 3) & 0xFF)
#define OBJMAKEKINSUTA_GETS_3FC(params) (((params & 0x3FC) >> 2) & 0xFF)
#define OBJMAKEKINSUTA_GET_SWITCH_FLAG(thisx) ((thisx)->params & 0x7F)

typedef struct ObjMakekinsuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s8 unk144;
} ObjMakekinsuta; // size = 0x148

#endif // Z_OBJ_MAKEKINSUTA_H
