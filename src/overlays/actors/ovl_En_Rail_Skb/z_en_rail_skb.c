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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_SKB,
    sizeof(EnRailSkb),
    (ActorFunc)EnRailSkb_Init,
    (ActorFunc)EnRailSkb_Destroy,
    (ActorFunc)EnRailSkb_Update,
    (ActorFunc)EnRailSkb_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B708C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B70AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B70B04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B70D24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/EnRailSkb_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/EnRailSkb_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B70FA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B70FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B710AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B710E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71114.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B7114C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71228.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B7123C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B712FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71314.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B713A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B714D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B7151C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B715AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71650.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B716A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B717C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B717E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B718B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B718C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71954.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71A08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71A58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71BB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71D8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71DF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71EA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B71F3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72100.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B723F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B725C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B726B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B7285C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/EnRailSkb_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B72E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/func_80B7302C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rail_Skb_0x80B708C0/EnRailSkb_Draw.asm")
