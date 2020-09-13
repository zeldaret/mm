#include "z_en_skb.h"

#define FLAGS 0x00000005

#define THIS ((EnSkb*)thisx)

void EnSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Skb_InitVars = {
    ACTOR_EN_SKB,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnSkb),
    (ActorFunc)EnSkb_Init,
    (ActorFunc)EnSkb_Destroy,
    (ActorFunc)EnSkb_Update,
    (ActorFunc)EnSkb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809947B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099495C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809949C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80994A30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80994A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/EnSkb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/EnSkb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80994DA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80994E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80994E94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80994F7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099504C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995068.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809952D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099533C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809953E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099544C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809954F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099556C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099571C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809958F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099599C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995A30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995A8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995C24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995C84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995D3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995E08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995E64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80995F98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809960AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809961E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996284.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809962D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099630C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809963C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809963D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996474.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809964A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809964DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996544.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996594.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_8099672C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996AD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996BEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996D68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/EnSkb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_80996F78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/func_809970D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Skb_0x809947B0/EnSkb_Draw.asm")
