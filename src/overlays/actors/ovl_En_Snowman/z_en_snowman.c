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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B16FC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B173D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1746C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B177EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B178B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B179D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B17FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B180A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B183A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B183C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1848C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B1861C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B189C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B189D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18A28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B18F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/EnSnowman_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowman/func_80B19998.s")
