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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnSkb),
    (ActorFunc)EnSkb_Init,
    (ActorFunc)EnSkb_Destroy,
    (ActorFunc)EnSkb_Update,
    (ActorFunc)EnSkb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809947B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099495C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809949C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80994F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099504C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809952D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099533C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809953E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099544C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809954F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099556C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099571C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809958F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099599C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995E64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80995F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809960AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809961E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809962D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099630C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809963C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809963D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809964A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809964DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_8099672C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_80996F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/func_809970D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Skb/EnSkb_Draw.s")
