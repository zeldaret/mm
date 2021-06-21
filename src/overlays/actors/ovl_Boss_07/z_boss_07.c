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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F49A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F49C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4AE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4BB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4D54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F4FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F51E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F52CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F536C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F5494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F5E14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F5E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F64F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F65F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F748C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F76D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F77A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F783C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7BC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F7D2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F805C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F86B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F87C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8E68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F8EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F91D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F9280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F93DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F94AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F99C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F9CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809F9E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FAA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FB7D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FBB9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FBF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/Boss07_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FC4C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FC8B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FC960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FCBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FCC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FCCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD89C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FD984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDAB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDBA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDEDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FDF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE4B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FE734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FEE70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF12C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF5CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FF900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_809FFEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A0021C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A006D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A006F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A00720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A016E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A01750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A025AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A0264C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A02B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A02C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A036C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A03F5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A0434C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A045A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A04E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A055E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A057A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05B50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A05DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A06F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A07604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A07638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_07_0x809F4980/func_80A07740.asm")
