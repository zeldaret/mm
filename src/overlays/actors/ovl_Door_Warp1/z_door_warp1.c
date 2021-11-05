/*
 * File: z_door_warp1.c
 * Overlay: ovl_Door_Warp1
 * Description: Blue Warp
 */

#include "z_door_warp1.h"

#define FLAGS 0x00000000

#define THIS ((DoorWarp1*)thisx)

void DoorWarp1_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808B921C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B93A0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B94A4(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9524(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B958C(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B96B0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9840(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B98A8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9B30(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9BE8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9CE8(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9E94(DoorWarp1* this, GlobalContext* globalCtx);
void func_808B9FD0(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BA550(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BAAF4(DoorWarp1* this, GlobalContext* globalCtx);
void func_808BABF4(DoorWarp1* this, GlobalContext* globalCtx);

void DoorWarp1_SetupAction(DoorWarp1* this, DoorWarp1ActionFunc actionFunc);

#if 0
const ActorInit Door_Warp1_InitVars = {
    ACTOR_DOOR_WARP1,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_WARP1,
    sizeof(DoorWarp1),
    (ActorFunc)DoorWarp1_Init,
    (ActorFunc)DoorWarp1_Destroy,
    (ActorFunc)DoorWarp1_Update,
    (ActorFunc)DoorWarp1_Draw,
};

#endif

extern UNK_TYPE D_060001A0;
extern UNK_TYPE D_06001374;
extern UNK_TYPE D_060044D8;
extern UNK_TYPE D_060076C0;
extern UNK_TYPE D_06008BD4;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/DoorWarp1_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B849C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B8568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B866C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/DoorWarp1_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/DoorWarp1_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B8924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B8A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B8C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B8E78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B900C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B90CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B921C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B93A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B94A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B958C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B96A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B96B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B977C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B98A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808B9FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BA10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BA550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BAAF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BABF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/DoorWarp1_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BACCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BAE9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BB4C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BB4F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/DoorWarp1_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Warp1/func_808BB8D4.s")
