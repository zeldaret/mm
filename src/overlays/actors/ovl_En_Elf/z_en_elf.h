#ifndef Z_EN_ELF_H
#define Z_EN_ELF_H

#include "global.h"

struct EnElf;

typedef void (*EnElfActionFunc)(struct EnElf*, GlobalContext*);
typedef void (*EnElfUnkFunc)(struct EnElf*, GlobalContext*);

#define ENELF_GET_F(thisx) ((thisx)->params & 0xF)
#define ENELF_GET_FE00(thisx) (((thisx)->params & 0xFE00) >> 9)

typedef struct EnElf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[7];
    /* 0x01B2 */ Vec3s morphTable[7];
    /* 0x01DC */ Color_RGBAf innerColor;
    /* 0x01EC */ Color_RGBAf outerColor;
    /* 0x01FC */ LightInfo lightInfoGlow;
    /* 0x020C */ LightNode* lightNodeGlow;
    /* 0x0210 */ LightInfo lightInfoNoGlow;
    /* 0x0220 */ LightNode* lightNodeNoGlow;
    /* 0x0224 */ Vec3f unk_224;
    /* 0x0230 */ Actor* elfMsg;
    /* 0x0234 */ Actor* unk_234;
    /* 0x0238 */ f32 unk_238;
    /* 0x023C */ f32 unk_23C;
    /* 0x0240 */ f32 unk_240;
    /* 0x0244 */ s16 unk_244;
    /* 0x0246 */ s16 unk_246;
    /* 0x0248 */ s16 unk_248;
    /* 0x024A */ s16 unk_24A;
    /* 0x024C */ s16 unk_24C;
    /* 0x0250 */ f32 unk_250;
    /* 0x0254 */ f32 unk_254;
    /* 0x0258 */ s16 unk_258;
    /* 0x025A */ u16 timer;
    /* 0x025C */ s16 unk_25C;
    /* 0x025E */ s16 disappearTimer;
    /* 0x0260 */ s16 unk_260;
    /* 0x0262 */ u16 fairyFlags;
    /* 0x0264 */ u16 unk_264;
    /* 0x0266 */ u16 unk_266;
    /* 0x0268 */ u8 unk_268;
    /* 0x0269 */ u8 unk_269;
    /* 0x026C */ EnElfUnkFunc unk_26C;
    /* 0x0270 */ EnElfActionFunc actionFunc;
} EnElf; // size = 0x274

extern const ActorInit En_Elf_InitVars;

#endif // Z_EN_ELF_H
