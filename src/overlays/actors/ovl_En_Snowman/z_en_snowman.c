#include "z_en_snowman.h"

#define FLAGS 0x00000005

#define THIS ((EnSnowman*)thisx)

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Snowman_InitVars = {
    ACTOR_EN_SNOWMAN,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SNOWMAN,
    sizeof(EnSnowman),
    (ActorFunc)EnSnowman_Init,
    (ActorFunc)EnSnowman_Destroy,
    (ActorFunc)EnSnowman_Update,
    (ActorFunc)EnSnowman_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B16FC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B173D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B1746C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B177EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B178B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B179D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17A58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B180A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B183A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B183C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B1848C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B1861C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B189C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B189D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18A04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18A28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18BB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18C7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19948.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19998.asm")
