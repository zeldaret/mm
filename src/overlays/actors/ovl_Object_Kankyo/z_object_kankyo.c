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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjectKankyo),
    (ActorFunc)ObjectKankyo_Init,
    (ActorFunc)ObjectKankyo_Destroy,
    (ActorFunc)ObjectKankyo_Update,
    (ActorFunc)ObjectKankyo_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DBE80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DBE8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DBEB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DBFB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DC038.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DC18C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DC454.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DCB7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DCBF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DCDB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DD3C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DD970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DDE74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Object_Kankyo_0x808DBE80/func_808DDE9C.asm")
