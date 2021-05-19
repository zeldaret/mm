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
    (ActorFunc)EnSsh_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80973EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80973EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80973F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_8097424C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809744A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809744C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809744FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809745BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_8097480C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809748DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_8097497C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809749B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974B84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80974F78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_8097502C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/EnSsh_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/EnSsh_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809755C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_8097561C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809756D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_809758B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975A98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/EnSsh_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975DBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/func_80975EB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ssh_0x80973EF0/EnSsh_Draw.asm")
