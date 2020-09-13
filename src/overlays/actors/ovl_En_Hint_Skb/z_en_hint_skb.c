#include "z_en_hint_skb.h"

#define FLAGS 0x00000019

#define THIS ((EnHintSkb*)thisx)

void EnHintSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHintSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hint_Skb_InitVars = {
    ACTOR_EN_HINT_SKB,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnHintSkb),
    (ActorFunc)EnHintSkb_Init,
    (ActorFunc)EnHintSkb_Destroy,
    (ActorFunc)EnHintSkb_Update,
    (ActorFunc)EnHintSkb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/EnHintSkb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/EnHintSkb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C1FE0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C1FE20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C1FE30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C1FE80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C1FF30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C1FF88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2003C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C200B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2011C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2016C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20334.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C204F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2066C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2069C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2075C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C2077C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C208BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C208D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20A74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20B88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20C24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C20E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C21250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C21320.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C21414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C21468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C215E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/EnHintSkb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C21858.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/func_80C219D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hint_Skb_0x80C1FCF0/EnHintSkb_Draw.asm")
