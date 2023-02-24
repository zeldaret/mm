/*
 * File: z_obj_tokei_tobira.c
 * Overlay: ovl_Obj_Tokei_Tobira
 * Description: Clock Tower - Swinging Doors
 */

#include "z_obj_tokei_tobira.h"

#define FLAGS 0x00000000

#define THIS ((ObjTokeiTobira*)thisx)

void ObjTokeiTobira_Init(Actor* thisx, PlayState* play);
void ObjTokeiTobira_Destroy(Actor* thisx, PlayState* play);
void ObjTokeiTobira_Update(Actor* thisx, PlayState* play);
void ObjTokeiTobira_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Obj_Tokei_Tobira_InitVars = {
    /**/ ACTOR_OBJ_TOKEI_TOBIRA,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_TOKEI_TOBIRA,
    /**/ sizeof(ObjTokeiTobira),
    /**/ ObjTokeiTobira_Init,
    /**/ ObjTokeiTobira_Destroy,
    /**/ ObjTokeiTobira_Update,
    /**/ ObjTokeiTobira_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ABD750[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80ABD750[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira/ObjTokeiTobira_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira/ObjTokeiTobira_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira/func_80ABD3B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira/ObjTokeiTobira_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokei_Tobira/ObjTokeiTobira_Draw.s")
