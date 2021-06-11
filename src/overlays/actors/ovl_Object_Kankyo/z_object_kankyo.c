#include "z_object_kankyo.h"

#define FLAGS 0x02000030

#define THIS ((ObjectKankyo*)thisx)

void ObjectKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjectKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjectKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjectKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Object_Kankyo_InitVars = {
    ACTOR_OBJECT_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjectKankyo),
    (ActorFunc)ObjectKankyo_Init,
    (ActorFunc)ObjectKankyo_Destroy,
    (ActorFunc)ObjectKankyo_Update,
    (ActorFunc)ObjectKankyo_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DBE80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DBE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DBEB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DBFB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DC038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/ObjectKankyo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/ObjectKankyo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DC18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DC454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DCB7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DCBF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DCDB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/ObjectKankyo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/ObjectKankyo_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DD3C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DD970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DDE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Object_Kankyo/func_808DDE9C.s")
