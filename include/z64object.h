#ifndef Z64OBJECT_H
#define Z64OBJECT_H

#include "libc/stdint.h"

typedef struct ObjectOverlay {
    /* 0x0 */ uintptr_t vromStart;
    /* 0x4 */ uintptr_t vromEnd;
} ObjectOverlay; // size = 0x8

#define DEFINE_OBJECT(_name, enumValue) enumValue,
#define DEFINE_OBJECT_UNSET(enumValue) enumValue,
#define DEFINE_OBJECT_SIZE_ZERO(_name, enumValue) enumValue,

typedef enum ObjectId {
    #include "tables/object_table.h"
    /* 0x283 */ OBJECT_ID_MAX
} ObjectId;

#undef DEFINE_OBJECT
#undef DEFINE_OBJECT_UNSET
#undef DEFINE_OBJECT_SIZE_ZERO

extern ObjectId gObjectTableSize;
extern ObjectOverlay gObjectTable[OBJECT_ID_MAX];

#endif
