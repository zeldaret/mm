#include "z_en_stream.h"

#define FLAGS 0x00000010

#define THIS ((EnStream*)thisx)

void EnStream_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Stream_InitVars = {
    ACTOR_EN_STREAM,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_STREAM,
    sizeof(EnStream),
    (ActorFunc)EnStream_Init,
    (ActorFunc)EnStream_Destroy,
    (ActorFunc)EnStream_Update,
    (ActorFunc)EnStream_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80965B20[] = {
    ICHAIN_VEC3F_DIV1000(scale, 20, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/func_80965650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/EnStream_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/EnStream_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/func_809656D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/func_809657F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/func_8096597C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/EnStream_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Stream_0x80965650/EnStream_Draw.asm")
