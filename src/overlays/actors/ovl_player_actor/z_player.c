/*
 * File: z_player.c
 * Overlay: ovl_player_actor
 * Description: Player
 */

#include "global.h"

#define THIS ((Player*)thisx)

extern UNK_TYPE D_06008860;
extern UNK_TYPE D_0600BDD8;
extern UNK_TYPE D_060178D0;

void Player_Init(Actor* thisx, GlobalContext* globalCtx);
void Player_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Player_Update(Actor* thisx, GlobalContext* globalCtx);
void Player_Draw(Actor* thisx, GlobalContext* globalCtx);

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DAD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DAFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DB18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DB60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DBC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DC28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DE14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DE88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DF48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082DF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E0F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E12C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E5A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082E9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EAC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EB18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EB38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ECCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ECE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ED20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082ED94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EEA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082EFE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F02C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F43C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F5FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082F938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FA5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FBE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FC24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FC60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FD0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FDC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8082FE0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808302CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808304BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808305BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808306F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808308DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808309CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830E30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80830FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083133C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808313A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808313F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083172C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808317C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808318C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083213C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083216C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808323C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083249C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808324EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832CAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832F24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80832F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808331FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808332A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808333CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808334D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808335B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808335F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083375C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808339B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808339D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80833B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808340AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808340D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808341F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808344C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083456C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808345A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808345C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80834DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808353DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808354A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808355D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083562C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835D58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80835EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083604C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808365DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083692C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808369F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80836F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808370D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808373A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808373F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083784C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808378FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083798C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808379C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80837DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808381A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808381F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083827C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083868C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808387A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808388B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808389BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80838A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808391D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808395F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808396B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839E3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80839F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083A98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AD04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AD8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083ADB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083ADF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083AF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B32C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B3B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B8D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083B930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083BB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083BF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C6E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C85C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083C8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CB04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083CF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D6DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083D860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DCC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DEE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DF38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083DFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E2F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083E9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083EA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083EBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083EE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F57C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083F8A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FD80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FE90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8083FFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808400CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808401F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808409A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840CD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80840F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808411D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808412A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808412BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808414E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841528.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808415A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808415E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841624.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084182C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80842510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808425B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808426F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808430E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80843178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80843EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808442D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808445C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808446F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80844784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80844D80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80844EF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808463C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80846460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084748C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808475B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808477D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808479F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80847FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808481CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808482E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808484CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808484F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808487B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084894C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80848E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808490B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808491B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084923C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808492C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808496AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808497A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80849FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A26C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084A8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AEEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084AF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B0EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B4A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084B5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BE40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084BFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C16C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084C94C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CA24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084CE84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084D820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E4E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E65C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084E980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084ED9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084EE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084EF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084F1B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084F3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084F4E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084FE7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808505D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808508C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80850D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808513EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808516B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808519FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80851F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808521E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085255C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808525C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085269C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80852FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808530E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808534C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80853D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808540A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085421C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085437C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085439C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808546D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808548B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80854EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808550D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808553F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80855F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808561B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808566C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085687C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80856918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808573A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808576BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808577E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857AEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80857BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858E80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80858FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808591BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085929C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859300.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808594D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808595B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085968C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085978C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808599DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859D44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80859FF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A19C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A1D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A24C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A2AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A40C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A66C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085A940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085ABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085AD5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085ADA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B74C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8085B930.s")
