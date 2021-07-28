/*
 * File: z_player.c
 * Overlay: ovl_Player_Actor
 * Description: Player
 */

#include "ultra64.h"
#include "global.h"

#define THIS ((Player*)thisx)

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DA90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DAD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DAFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DB18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DB3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DB60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DB90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DC28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DE14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DE50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DE88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DF2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DF48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082DF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E00C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E0F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E12C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E1BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E224.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E5A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E6F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082E9C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EA10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EA38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EAC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EB18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EB38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082ECCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082ECE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082ED20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082ED94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EEA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EEE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EF9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082EFE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F02C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F09C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F164.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F43C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F5FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F8A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F8BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082F938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FA5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FB68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FBE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FC24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FC78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FCC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FD0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FDC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8082FE0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808302CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808304BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808305BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808306F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808308DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808309CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830A58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830AE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830E30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80830FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083133C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808313A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808313F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083172C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808317C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808318C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80831F34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083213C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083216C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808323C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083249C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808324EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832558.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832CAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832F24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80832F78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808331FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808332A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808333CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808334D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808335B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808335F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083375C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808339B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808339D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833AA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80833B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808340AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808340D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808341F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808344C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834534.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083456C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808345A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808345C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834D50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80834DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835324.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808353DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808354A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808355D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083562C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835D2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835D58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80835EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083604C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808365DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083692C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808369F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836A5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836A98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836AD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836C70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80836F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808370D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808373A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808373F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083784C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808378FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083798C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808379C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837C20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80837DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808381A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808381F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083827C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083868C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80838760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808387A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80838830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808388B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808389BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80838A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80838A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808391D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839518.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808395F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808396B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839A84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839E3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80839F98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A04C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083A98C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083AD04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083AD8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083ADB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083ADF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083AE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083AECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083AF30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083AF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B0E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B23C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B2E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B32C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B3B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B798.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B850.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B8D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083B930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083BB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083BF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083C62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083C6E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083C85C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083C8E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083CB04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083CB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083CBC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083CCB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083CF68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083D168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083D23C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083D6DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083D738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083D78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083D860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083DCC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083DD1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083DEE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083DF38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083DFC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E14C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E2F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E7F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E8E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083E9C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083EA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083EBD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083EE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F57C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083F8A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FBC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FCF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FD80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FE90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FF30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8083FFEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808400CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808401F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808409A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840A30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840CD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840EC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840F34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80840F90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808411D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808412A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808412BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808414E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841528.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808415A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808415E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841624.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084182C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80841AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80842510.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808425B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808426F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808430E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80843178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80843EC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808442D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808445C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808446F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80844784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80844D80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80844EF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808460B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808463C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80846460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80846528.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808470D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084748C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808475B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808477D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808479F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847BF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80847FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808481CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808482E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808484CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808484F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808487B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848808.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084894C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848A0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848BF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80848E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80849054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808490B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808491B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084923C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808492C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084933C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80849570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80849620.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808496AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808497A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80849A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80849DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80849FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084A26C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084A5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084A794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084A884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084A8E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084AB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084AC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084AEEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084AF9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084B0EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084B288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084B3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084B4A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084B5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084BAA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084BBF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084BC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084BE40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084BF28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084BFDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084C124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084C16C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084C6EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084C94C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084CA24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084CB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084CCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084CE84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084D18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084D4EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084D770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084D820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E25C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E4E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E58C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E65C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084E980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084ED9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084EE50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084EF9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084F1B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084F3DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084F4E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084FC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084FD7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084FE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8084FE7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808505D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808508C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850BA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80850D68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808513EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808516B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808519FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851BD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80851F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808521E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80852290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085255C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808525C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085269C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80852B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80852C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80852FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808530E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80853194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808534C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80853754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80853850.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80853A5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80853CC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80853D68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808540A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085421C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085437C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085439C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854614.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808546D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808548B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854C70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80854EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808550D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855218.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808553F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855E08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80855F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80856000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80856074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80856110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808561B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808566C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085687C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80856888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80856918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808573A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80857640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808576BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808577E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80857950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80857A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80857AEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80857BE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858DB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858E80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858EC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858F3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858F5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858FBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80858FE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808591BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859248.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085929C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808594D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808595B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085968C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085978C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_808599DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859AD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859BA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859C60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859CA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859CE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859CFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859D44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859D70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_80859FF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A04C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A19C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A1D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A24C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A2AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A364.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A40C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A5DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A66C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A7C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A8C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085A940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AA10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AA84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085ABA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085AD5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085ADA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B08C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B3E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B74C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Player_Actor_0x8082DA90/func_8085B930.asm")
