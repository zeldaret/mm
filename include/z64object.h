#ifndef Z64OBJECT_H
#define Z64OBJECT_H

#define OBJECT_SPACE_SIZE_DEFAULT 1413120
#define OBJECT_SPACE_SIZE_CLOCK_TOWN 1566720
#define OBJECT_SPACE_SIZE_MILK_BAR 1617920
#define OBJECT_SPACE_SIZE_TERMINA_FIELD 1505280

#define OBJECT_EXCHANGE_BANK_MAX 35

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

#endif
