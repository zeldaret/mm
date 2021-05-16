#include "z_en_rail_skb.h"

#define FLAGS 0x00000015

#define THIS ((EnRailSkb*)thisx)

void EnRailSkb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRailSkb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rail_Skb_InitVars = {
    ACTOR_EN_RAIL_SKB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnRailSkb),
    (ActorFunc)EnRailSkb_Init,
    (ActorFunc)EnRailSkb_Destroy,
    (ActorFunc)EnRailSkb_Update,
    (ActorFunc)EnRailSkb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B708C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70D24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B70FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B710AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B710E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7114C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7123C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B712FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B713A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B714D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7151C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B715AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B716A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B717C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B717E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B718B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B718C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71EA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B71F3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B723F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B725C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B726B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7285C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B72E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/func_80B7302C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rail_Skb/EnRailSkb_Draw.s")
