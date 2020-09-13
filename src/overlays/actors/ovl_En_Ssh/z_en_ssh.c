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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SSH,
    sizeof(EnSsh),
    (ActorFunc)EnSsh_Init,
    (ActorFunc)EnSsh_Destroy,
    (ActorFunc)EnSsh_Update,
    (ActorFunc)EnSsh_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80973EF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80973EFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80973F84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974220.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_8097424C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974374.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809744A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809744C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809744FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809745BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_8097480C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809748DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_8097497C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809749B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974A24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974B0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974B84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974CC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974D3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974E44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974EA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80974F78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_8097502C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975300.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/EnSsh_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/EnSsh_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809755C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_8097561C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809756D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975720.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_809758B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975998.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975A98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/EnSsh_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975DBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/func_80975EB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ssh_0x80973EF0/EnSsh_Draw.asm")
