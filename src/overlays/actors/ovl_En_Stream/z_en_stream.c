#include "z_en_stream.h"

#define FLAGS 0x00000010

#define THIS ((EnStream*)thisx)

void EnStream_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStream_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Stream_InitVars = {
    ACTOR_EN_STREAM,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_STREAM,
    sizeof(EnStream),
    (ActorFunc)EnStream_Init,
    (ActorFunc)EnStream_Destroy,
    (ActorFunc)EnStream_Update,
    (ActorFunc)EnStream_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/func_80965650.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/EnStream_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/EnStream_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/func_809656D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/func_809657F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/func_8096597C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/EnStream_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Stream_0x80965650/EnStream_Draw.asm")
