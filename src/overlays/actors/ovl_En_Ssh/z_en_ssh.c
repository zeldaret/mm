#include "z_en_ssh.h"

#define FLAGS 0x00000035

#define THIS ((EnSsh*)thisx)

void EnSsh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSsh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSsh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSsh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ssh_InitVars = {
    ACTOR_EN_SSH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SSH,
    sizeof(EnSsh),
    (ActorFunc)EnSsh_Init,
    (ActorFunc)EnSsh_Destroy,
    (ActorFunc)EnSsh_Update,
    (ActorFunc)EnSsh_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80973EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80973EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80973F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_8097424C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809744A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809744C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809744FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809745BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_8097480C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809748DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_8097497C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809749B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80974F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_8097502C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/EnSsh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/EnSsh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809755C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_8097561C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809756D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_809758B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/EnSsh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975DBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/func_80975EB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ssh/EnSsh_Draw.s")
