/*
 * File: z_obj_jg_gakki.c
 * Overlay: ovl_Obj_Jg_Gakki
 * Description: Goron Elder's Drum
 */

#include "z_obj_jg_gakki.h"

#define FLAGS 0x00000020

#define THIS ((ObjJgGakki*)thisx)

void ObjJgGakki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjJgGakki_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjJgGakki_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjJgGakki_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Jg_Gakki_InitVars = {
    ACTOR_OBJ_JG_GAKKI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_JG,
    sizeof(ObjJgGakki),
    (ActorFunc)ObjJgGakki_Init,
    (ActorFunc)ObjJgGakki_Destroy,
    (ActorFunc)ObjJgGakki_Update,
    (ActorFunc)ObjJgGakki_Draw,
};

#endif

extern UNK_TYPE D_0601B1E8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jg_Gakki/ObjJgGakki_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jg_Gakki/ObjJgGakki_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jg_Gakki/ObjJgGakki_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jg_Gakki/ObjJgGakki_Draw.s")
