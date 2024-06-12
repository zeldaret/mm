#ifndef Z64OBJECT_H
#define Z64OBJECT_H

#include "stdint.h"

#define DEFINE_OBJECT(_name, enumValue) enumValue,
#define DEFINE_OBJECT_UNSET(enumValue) enumValue,
#define DEFINE_OBJECT_EMPTY(_name, enumValue) enumValue,

typedef enum ObjectId {
    #include "tables/object_table.h"
    /* 0x283 */ OBJECT_ID_MAX
} ObjectId;

#undef DEFINE_OBJECT
#undef DEFINE_OBJECT_UNSET
#undef DEFINE_OBJECT_EMPTY

extern ObjectId gObjectTableSize;
extern RomFile gObjectTable[OBJECT_ID_MAX];

#endif
