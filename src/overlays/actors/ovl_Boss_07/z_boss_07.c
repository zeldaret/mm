#include "z_boss_07.h"

#define FLAGS 0x00000035

#define THIS ((Boss07*)thisx)

void Boss07_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss07_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_07_InitVars = {
    ACTOR_BOSS_07,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS07,
    sizeof(Boss07),
    (ActorFunc)Boss07_Init,
    (ActorFunc)Boss07_Destroy,
    (ActorFunc)Boss07_Update,
    (ActorFunc)Boss07_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F49A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F49C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4BB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4CBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F4FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F51E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F52CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F536C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F5E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F64F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F748C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F76D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F77A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F783C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F7D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F805C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F86B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F87C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8E68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F8EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F91D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F9280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F93DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F94AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F99C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F9CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809F9E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FAA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FB7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FBB9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FBF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/Boss07_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC4C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC8B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FC960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCBC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FCCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD5F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD89C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FD984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDB2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FDF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FE734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FEE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF5CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FF900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_809FFEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0021C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A006D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A006F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A00720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A016E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A01750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A025AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0264C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A02B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A02C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A036C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A03F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A0434C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A045A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A04E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A055E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A057A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A05DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A06F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A07604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A07638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_07/func_80A07740.s")
