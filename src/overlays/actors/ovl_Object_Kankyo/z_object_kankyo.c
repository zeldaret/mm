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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DBE80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DBE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DBEB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DBFB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DC038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DC18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DC454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DCB7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DCBF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DCDB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/ObjectKankyo_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DD3C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DD970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DDE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Object_Kankyo_0x808DBE80/func_808DDE9C.asm")
