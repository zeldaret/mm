/*
 * File: z_obj_tokeidai.c
 * Overlay: ovl_Obj_Tokeidai
 * Description: Clock Face
 */

#include "z_obj_tokeidai.h"

#define FLAGS 0x00000030

#define THIS ((ObjTokeidai*)thisx)

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AB319C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3240(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB32F0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3370(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB34CC(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3544(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3598(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB363C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB365C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3808(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3880(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB38B0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB39BC(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3A7C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3B34(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3BD8(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3BE8(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3ED0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4040(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4080(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4160(ObjTokeidai* this, GlobalContext* globalCtx);

const ActorInit Obj_Tokeidai_InitVars = {
    ACTOR_OBJ_TOKEIDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_TOKEIDAI,
    sizeof(ObjTokeidai),
    (ActorFunc)ObjTokeidai_Init,
    (ActorFunc)ObjTokeidai_Destroy,
    (ActorFunc)ObjTokeidai_Update,
    (ActorFunc)ObjTokeidai_Draw,
};

static s32 D_80AB49E0[] = { 0xC8580064, 0xB0FC0FA0, 0xB1000CE4, 0x30FC044C };

extern UNK_TYPE D_0600B208;
extern UNK_TYPE D_0600BA78;
extern UNK_TYPE D_0600CF28;
extern UNK_TYPE D_0600D388;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB2790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB27B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB2834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB28C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB29F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB2BBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/ObjTokeidai_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/ObjTokeidai_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB319C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB32F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3370.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB34CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB363C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB365C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB36C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB38B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB39BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3B34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3BB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3BD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/ObjTokeidai_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/ObjTokeidai_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4894.s")
