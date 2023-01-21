#ifndef Z_EN_PAPER_H
#define Z_EN_PAPER_H

#include "global.h"

struct EnPaper;

typedef void (*EnPaperActionFunc)(struct EnPaper*, PlayState*);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
} EnPaperStruct; // size = 0x34

typedef struct EnPaper {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnPaperActionFunc actionFunc;
    /* 0x148 */ EnPaperStruct unk_148[60];
    /* 0xD78 */ Vec3f unk_D78;
    /* 0xD84 */ s16 timer;
} EnPaper; // size = 0xD88

#endif // Z_EN_PAPER_H
