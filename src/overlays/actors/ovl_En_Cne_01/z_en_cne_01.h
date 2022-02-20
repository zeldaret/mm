#ifndef Z_EN_CNE_01_H
#define Z_EN_CNE_01_H

#include "z_en_hy_code.h"

struct EnCne01;

typedef void (*EnCne01ActionFunc)(struct EnCne01*, GlobalContext*);

#define ENCNE01_GET_PATH(thisx) (((thisx)->params & 0x7E00) >> 9)
#define ENCNE01_NO_PATH 0x3F

typedef struct EnCne01 {
    /* 0x000 */ EnHy enHy;
    /* 0x3EC */ UNK_TYPE1 unk_3EC[0x230];
} EnCne01; // size = 0x61C

extern const ActorInit En_Cne_01_InitVars;

#endif // Z_EN_CNE_01_H
