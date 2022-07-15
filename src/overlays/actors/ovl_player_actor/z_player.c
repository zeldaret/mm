/*
 * File: z_player.c
 * Overlay: ovl_player_actor
 * Description: Player
 */

#include "global.h"
#include "z64rumble.h"

#define THIS ((Player*)thisx)

extern UNK_TYPE D_06008860;
extern UNK_TYPE D_0600BDD8;
extern UNK_TYPE D_060178D0;

void Player_Init(Actor* thisx, PlayState* play);
void Player_Destroy(Actor* thisx, PlayState* play);
void Player_Update(Actor* thisx, PlayState* play);
void Player_Draw(Actor* thisx, PlayState* play);


void func_80844EF8(Player* player, PlayState* play, Input* input);
s32 func_8085B134(PlayState* play);
void func_8085B170(PlayState* play, Player* player);

s32 func_8082DA90(PlayState* play);
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

void func_8082DCA0(PlayState* play, Player* this);
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

void func_80831454(Player* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80831454.s")

s32 func_80831494(PlayState* play, Player* this, void (*arg2)(Player*, PlayState* play), s32 arg3);
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

void func_80835BC8(Player* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3);
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

void func_8084182C(Player* this, PlayState* play, FlexSkeletonHeader* skelHeader);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_8084182C.s")

void func_80841A50(PlayState* play, Player* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80841A50.s")


extern LinkAnimationHeader D_0400CF98;
extern LinkAnimationHeader D_0400D0A8;
extern LinkAnimationHeader D_0400D0B0;
extern LinkAnimationHeader D_0400D0C8;
extern LinkAnimationHeader D_0400D0D0;
extern LinkAnimationHeader D_0400D100;
extern LinkAnimationHeader D_0400D218;
extern LinkAnimationHeader D_0400D220;
extern LinkAnimationHeader D_0400D228;
extern LinkAnimationHeader D_0400D3E8;
extern LinkAnimationHeader D_0400D3F8;
extern LinkAnimationHeader D_0400D420;
extern LinkAnimationHeader D_0400D488;
extern LinkAnimationHeader D_0400D490;
extern LinkAnimationHeader D_0400D4A8;
extern LinkAnimationHeader D_0400D4B0;
extern LinkAnimationHeader D_0400D4B8;
extern LinkAnimationHeader D_0400D4C0;
extern LinkAnimationHeader D_0400D4D8;
extern LinkAnimationHeader D_0400D4F0;
extern LinkAnimationHeader D_0400D4F8;
extern LinkAnimationHeader D_0400D500;
extern LinkAnimationHeader D_0400D5A8;
extern LinkAnimationHeader D_0400D5B0;
extern LinkAnimationHeader D_0400D638;
extern LinkAnimationHeader D_0400D660;
extern LinkAnimationHeader D_0400D698;
extern LinkAnimationHeader D_0400D8B0;
extern LinkAnimationHeader D_0400D9C8;
extern LinkAnimationHeader D_0400D9D0;
extern LinkAnimationHeader D_0400D9D8;
extern LinkAnimationHeader D_0400DA60;
extern LinkAnimationHeader D_0400DA68;
extern LinkAnimationHeader D_0400DA70;
extern LinkAnimationHeader D_0400DA88;
extern LinkAnimationHeader D_0400DAA0;
extern LinkAnimationHeader D_0400DAA8;
extern LinkAnimationHeader D_0400DAC0;
extern LinkAnimationHeader D_0400DAC8;
extern LinkAnimationHeader D_0400DAD0;
extern LinkAnimationHeader D_0400DAD8;
extern LinkAnimationHeader D_0400DAE0;
extern LinkAnimationHeader D_0400DAF0;
extern LinkAnimationHeader D_0400DB10;
extern LinkAnimationHeader D_0400DB18;
extern LinkAnimationHeader D_0400DB30;
extern LinkAnimationHeader D_0400DB68;
extern LinkAnimationHeader D_0400DBB0;
extern LinkAnimationHeader D_0400DBE8;
extern LinkAnimationHeader D_0400DC20;
extern LinkAnimationHeader D_0400DC28;
extern LinkAnimationHeader D_0400DC30;
extern LinkAnimationHeader D_0400DC48;
extern LinkAnimationHeader D_0400DC60;
extern LinkAnimationHeader D_0400DC78;
extern LinkAnimationHeader D_0400DC80;
extern LinkAnimationHeader D_0400DC88;
extern LinkAnimationHeader D_0400DCA8;
extern LinkAnimationHeader D_0400DCD0;
extern LinkAnimationHeader D_0400DCF8;
extern LinkAnimationHeader D_0400DD10;
extern LinkAnimationHeader D_0400DD30;
extern LinkAnimationHeader D_0400DD38;
extern LinkAnimationHeader D_0400DD40;
extern LinkAnimationHeader D_0400DD70;
extern LinkAnimationHeader D_0400DD78;
extern LinkAnimationHeader D_0400DD80;
extern LinkAnimationHeader D_0400DDF0;
extern LinkAnimationHeader D_0400DDF8;
extern LinkAnimationHeader D_0400DE00;
extern LinkAnimationHeader D_0400DE08;
extern LinkAnimationHeader D_0400DE10;
extern LinkAnimationHeader D_0400DE28;
extern LinkAnimationHeader D_0400DE30;
extern LinkAnimationHeader D_0400DE50;
extern LinkAnimationHeader D_0400DE60;
extern LinkAnimationHeader D_0400DEA0;
extern LinkAnimationHeader D_0400DEA8;
extern LinkAnimationHeader D_0400DF78;
extern LinkAnimationHeader D_0400DF90;
extern LinkAnimationHeader D_0400DF98;
extern LinkAnimationHeader D_0400DFA0;
extern LinkAnimationHeader D_0400DFA8;
extern LinkAnimationHeader D_0400DFB0;
extern LinkAnimationHeader D_0400DFB8;
extern LinkAnimationHeader D_0400DFC0;
extern LinkAnimationHeader D_0400DFC8;
extern LinkAnimationHeader D_0400DFD0;
extern LinkAnimationHeader D_0400DFD8;
extern LinkAnimationHeader D_0400DFE0;
extern LinkAnimationHeader D_0400DFE8;
extern LinkAnimationHeader D_0400DFF0;
extern LinkAnimationHeader D_0400DFF8;
extern LinkAnimationHeader D_0400E000;
extern LinkAnimationHeader D_0400E008;
extern LinkAnimationHeader D_0400E050;
extern LinkAnimationHeader D_0400E060;
extern LinkAnimationHeader D_0400E070;
extern LinkAnimationHeader D_0400E080;
extern LinkAnimationHeader D_0400E088;
extern LinkAnimationHeader D_0400E098;
extern LinkAnimationHeader D_0400E1F0;
extern LinkAnimationHeader D_0400E200;
extern LinkAnimationHeader D_0400E208;
extern LinkAnimationHeader D_0400E260;
extern LinkAnimationHeader D_0400E270;
extern LinkAnimationHeader D_0400E278;
extern LinkAnimationHeader D_0400E290;
extern LinkAnimationHeader D_0400E298;
extern LinkAnimationHeader D_0400E2A0;
extern LinkAnimationHeader D_0400E2B8;
extern LinkAnimationHeader D_0400E2C0;
extern LinkAnimationHeader D_0400E2C8;
extern LinkAnimationHeader D_0400E2D8;
extern LinkAnimationHeader D_0400E2E8;
extern LinkAnimationHeader D_0400E2F0;
extern LinkAnimationHeader D_0400E2F8;
extern LinkAnimationHeader D_0400E398;
extern LinkAnimationHeader D_0400E3A0;
extern LinkAnimationHeader D_0400E3A8;
extern LinkAnimationHeader D_0400E3B0;
extern LinkAnimationHeader D_0400E3B8;
extern LinkAnimationHeader D_0400E3C0;
extern LinkAnimationHeader D_0400E3D8;
extern LinkAnimationHeader D_0400E408;
extern LinkAnimationHeader D_0400E410;
extern LinkAnimationHeader D_0400E418;

// extern void (*D_8085D2CC[0x10])(PlayState*, Player*, s32);
extern void (*D_8085D2CC[0x10])();
extern PlayerAgeProperties D_8085BA38[PLAYER_FORM_MAX];
extern LinkAnimationHeader* D_8085D160[PLAYER_FORM_MAX];
extern UNK_TYPE D_8085D30C;
extern UNK_TYPE D_8085D330;
extern Vec3f D_8085D340;

s32 func_8085B1F0(PlayState* play, Player* player);
s32 func_8085B28C(PlayState* play, Player* player, s32 mode);
void func_8085B384(Player* player, PlayState* play, Player*);
s32 func_8085B3E0(PlayState* play, s32 damage);
void func_8085B460(PlayState* play, Actor* actor, Player* player);
void func_8085B74C(PlayState* play);
void func_8085B820(PlayState* play, s16 arg1, Actor* actor);
s32 func_8085B854(PlayState* play, Player* player, s32 itemId, s32 arg3);
s32 func_8085B930(PlayState* play, void* talkAnim, s32 arg2);
void func_8085B08C(Player* arg0, PlayState* play);
void func_80855818(Player* arg0, PlayState* play);

#if 0
void Player_Init(Actor* thisx, PlayState* play) {
    s32 sp60;
    s8* sp44;
    PosRot* sp40;
    PosRot* temp_a0_2;
    RespawnData* temp_t8;
    RespawnData* temp_t9_2;
    SaveContext* var_v1;
    s16 temp_v0;
    s16 temp_v0_6;
    s16 temp_v1_3;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0_2;
    s32 var_v0_3;
    s8 temp_v0_2;
    s8* temp_a0;
    s8* temp_v1_2;
    u32 temp_t7;
    u32 temp_t9;
    u8 temp_t1;
    u8 temp_t6;
    u8 temp_v0_4;
    u8 temp_v0_5;
    u8 var_v0;
    void* temp_v0_3;
    Player* this = (Player* ) thisx;

    play->playerInit = func_8084182C;
    play->playerUpdate = func_80844EF8;
    play->unk_18770 = func_8085B170;
    play->startPlayerFishing = func_8085B134;
    play->grabPlayer = func_8085B1F0;
    play->startPlayerCutscene = func_8085B28C;
    play->func_18780 = func_8085B384;
    play->damagePlayer = func_8085B3E0;
    play->talkWithPlayer = func_8085B460;
    play->unk_1878C = func_8085B74C;
    play->unk_18790 = func_8085B820;
    play->unk_18794 = func_8085B854;
    play->setPlayerTalkAnim = func_8085B930;

    gActorOverlayTable[0].initInfo->objectId = 1;
    temp_v0 = this->actor.shape.rot.x;
    this->actor.room = -1;
    this->unk_A86 = -1;
    temp_t1 = temp_v0 - 1;
    if (temp_v0 != 0) {
        this->transformation = temp_t1;
        temp_v0_2 = Object_GetIndex(&play->objectCtx, gPlayerFormObjectIndices[temp_t1 & 0xFF]);
        this->actor.objBankIndex = temp_v0_2;
        if (temp_v0_2 < 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        Actor_SetObjectDependency(play, &this->actor);
    } else {
        temp_t6 = gSaveContext.save.playerForm;
        temp_v1 = temp_t6 & 0xFF;
        this->transformation = temp_t6;
        if (temp_v1 == 4) {
            var_v0 = gSaveContext.save.equippedMask;
            if (var_v0 == 0x14) {
                gSaveContext.save.equippedMask = 0;
                var_v0 = 0;
            }
            this->currentMask = var_v0;
        } else {
            this->currentMask = temp_v1 + 0x15;
            gSaveContext.save.equippedMask = 0;
        }
        Inventory_UpdateDeitySwordEquip(play);
        this->unk_B28 = 0;
        this->unk_B90 = 0;
        this->unk_B92 = 0;
        this->unk_B94 = 0;
        this->unk_B96 = 0;
        this->stateFlags1 &= 0xFCFFEFF7;
        this->stateFlags2 &= 0xBEFDFFFF;
        this->stateFlags3 &= 0xFC424437;
        this->unk_B08[0] = 0.0f;
        this->unk_B08[1] = 0.0f;
    }
    if (this->transformation == 2) {
        if ((this->stateFlags1 * 0x10) < 0) {
            this->unk_B08[2] = 1.0f;
        } else {
            this->unk_B08[2] = 0.0f;
        }
    }
    this->actor.flags &= 0xFBFDFFFF;
    if (this->transformation != 3) {
        this->actor.flags |= 0x04000000;
        if (this->transformation == 1) {
            this->actor.flags |= 0x20000;
        }
    }
    this->ageProperties = &D_8085BA38[this->transformation];
    this->heldItemActionParam = 0;
    this->itemActionParam = 0;
    this->heldItemId = 0xFF;
    // todo: declaration
    func_80831990(play, &this->actor, 0xFFU);
    Player_SetEquipmentData(play, this);
    this->prevBoots = this->currentBoots;
    func_8084182C(&this->actor, play, gPlayerSkeletons[this->transformation]);
    if (this->actor.shape.rot.z != 0) {
        this->actor.shape.rot.z = 0;
        // todo: declaration
        func_8082F938((Player* ) play, this, 0, 4);
        #if 0
        temp_v0_3 = Effect_GetByIndex(this->meleeWeaponEffectIndex[2]);
        if (this->transformation == 1) {
            temp_v0_3->unk_606 = (unaligned s32) D_8085D338;
        } else {
            temp_v0_3->unk_606 = (unaligned s32) D_8085D33C;
        }
        #endif
        if ((this->csMode == 9) || (this->csMode == 0x5D)) {
            // todo: declaration
            func_80831494(play, this, func_8085B08C, 0);
            this->stateFlags1 |= 0x20000000;
            return;
        }
        // todo: declaration
        func_80831494(play, this, func_80855818, 0);
        this->actor.shape.rot.y = this->currentYaw;
        if (this->prevMask != 0) {
            // todo: declaration
            func_8082DB90(play, this, &D_0400D0A8);
        } else {
            if (this->transformation == 4) {
                LinkAnimation_Change(play, &this->skelAnime, D_8085D160[this->transformation], -0.6666667f, 9.0f, 0.0f, (u8) 2, 0.0f);
            } else {
                // todo: declaration
                func_8082DB60(play, this, &D_0400D0D0);
            }
        }
        this->stateFlags1 |= 0x30000000;
        this->stateFlags3 |= 0x20000;
        this->unk_B08[7] = 3.0f;
        return;
    }
    this->prevMask = this->currentMask;
    Effect_Add(play, this->meleeWeaponEffectIndex, 2, 0U, (u8) 0, &D_8085D30C);
    Effect_Add(play, &this->meleeWeaponEffectIndex[1], 2, 0U, (u8) 0, &D_8085D30C);
    // todo: declaration
    func_8082F938((Player* ) play, this, 0, 4);
    #if 0
    if (this->transformation == 1) {
        *(&D_8085D330 + 4) = (unaligned s32) D_8085D338;
    } else {
        *(&D_8085D330 + 4) = (unaligned s32) D_8085D33C;
    }
    #endif
    Effect_Add(play, &this->meleeWeaponEffectIndex[2], 4, 0U, (u8) 0, &D_8085D330);
    if (this->actor.shape.rot.x != 0) {
        this->actor.shape.rot.x = 0;
        this->csMode = 0x44;
        // todo: declaration
        func_80831494(play, this, func_8085B08C, 0);
        this->stateFlags1 |= 0x20000000;
        return;
    }
    play->unk_1887C = 0;
    play->unk_1887D = 0;
    play->unk_1887E = 0;
    this->giObjectSegment = ZeldaArena_Malloc(0x2000U);
    this->maskObjectSegment = ZeldaArena_Malloc(0x3800U);
    temp_a0 = &this->unk_404[0x24];
    Lights_PointNoGlowSetInfo((LightInfo* ) temp_a0, (s16) (s32) this->actor.world.pos.x, (s16) (s32) this->actor.world.pos.y, (s16) (s32) this->actor.world.pos.z, (u8) 0xFF, (u8) 0x80, (u8) 0, (s16) -1);
    #if 0
    this->unk_504 = LightContext_InsertLight(play, &play->lightCtx, (LightInfo* ) temp_a0);
    #endif
    Play_AssignPlayerActorCsIdsFromScene(&play->state, (s32) this->actor.cutscene);
    var_a2 = gSaveContext.respawnFlag;
    if (var_a2 != 0) {
        if (var_a2 == -3) {
            this->actor.params = gSaveContext.respawn[3].playerParams;
        } else {
            if ((var_a2 == 1) || (var_a2 == -1)) {
                this->unk_D6A = -2;
            }
            if (var_a2 != -7) {
                temp_a0_2 = &this->actor.world;
                if ((var_a2 == -8) || (var_a2 == -5) || (var_a2 == -4)) {
                    var_a2 = 1;
                }
                if ((var_a2 < 0) && (var_a2 != -1) && (var_a2 != -6)) {
                    var_v1 = &gSaveContext;
                } else {
                    var_v0_2 = var_a2 - 1;
                    if (var_a2 < 0) {
                        var_v0_2 = 2;
                    }
                    temp_v1_2 = &gSaveContext + (var_v0_2 << 5);
                    sp40 = temp_a0_2;
                    Math_Vec3f_Copy(&temp_a0_2->pos, &gSaveContext.respawn[var_v0_2].pos);
                    Math_Vec3f_Copy(&this->actor.home.pos, &sp40->pos);
                    Math_Vec3f_Copy(&this->actor.prevPos, &sp40->pos);
                    Math_Vec3f_Copy(&this->actor.focus.pos, &sp40->pos);
                    var_v1 = (SaveContext* ) temp_v1_2;
                    this->unk_B68 = (s16) (s32) this->actor.world.pos.y;
                    temp_v0_6 = var_v1->respawn[0].yaw;
                    this->actor.shape.rot.y = temp_v0_6;
                    this->currentYaw = temp_v0_6;
                    this->actor.params = var_v1->respawn[0].playerParams;
                }
                play->actorCtx.flags.switches[2] = var_v1->respawn[0].tempSwitchFlags;
                play->actorCtx.flags.collectible[1] = var_v1->respawn[0].unk_18;
                play->actorCtx.flags.collectible[2] = var_v1->respawn[0].tempCollectFlags;
            }
        }
    }
    if ((var_a2 == 4) || (var_a1 = 0, (gSaveContext.respawnFlag == -4))) {
        var_a1 = 1;
    }
    if (func_801226E0(play, var_a1) == 0) {
        gSaveContext.respawn[0].playerParams = (this->actor.params & 0xFF) | 0xD00;
    }
    gSaveContext.respawn[0].data = 1;
    if (var_a2 == 0) {
        temp_t9_2 = gSaveContext.respawn;
        temp_t8 = &gSaveContext.respawn[2];
        temp_t8->pos.x = temp_t9_2->pos.x;
        temp_t8->pos.y = temp_t9_2->pos.y;
        temp_t8->pos.z = temp_t9_2->pos.z;
        temp_t8->yaw = (s32) temp_t9_2->yaw;
        temp_t8->entranceIndex = (s32) temp_t9_2->entranceIndex;
        temp_t8->tempSwitchFlags = temp_t9_2->tempSwitchFlags;
        temp_t8->unk_18 = temp_t9_2->unk_18;
        temp_t8->tempCollectFlags = temp_t9_2->tempCollectFlags;
    }
    gSaveContext.respawn[2].playerParams = (gSaveContext.respawn[2].playerParams & 0xFF) | 0xD00;
    var_v0_3 = (s32) (this->actor.params & 0xF00) >> 8;
    if (((var_v0_3 == 5) || (var_v0_3 == 6)) && (gSaveContext.save.cutscene >= 0xFFF0)) {
        var_v0_3 = 0xD;
    }
    D_8085D2CC[var_v0_3](play, this, var_a2);
    if ((this->actor.draw != NULL) && (gSaveContext.save.hasTatl != 0)) {
        if ((((gSaveContext.gameMode == 0)) || (gSaveContext.gameMode == 3)) && (play->sceneNum != 8)) {
            // todo: declaration
            this->tatlActor = func_80835C64(play, &this->actor, &this->actor.world.pos, &D_8085D340, 0);
            temp_v1_3 = (s16) gSaveContext.dogParams;
            if (temp_v1_3 != 0) {
                gSaveContext.dogParams = temp_v1_3 | 0x8000;
            }
            if (gSaveContext.powderKegTimer != 0) {
                this->nextModelGroup = Player_ActionToModelGroup(this, PLAYER_AP_POWDER_KEG);
                this->heldItemId = 0xC;
                func_8082F8BC(play, this, PLAYER_AP_POWDER_KEG);
                // todo: declaration
                func_808313F0(this, play);
            } else if (gSaveContext.unk_1014 != 0) {
                // todo: declaration
                func_8082F5FC(this, Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, 0xB9, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, (s16) 0, (s16) (s32) this->actor.shape.rot.y, (s16) 0, 0x8000));
            // todo: declaration
                func_808313F0(this, play);
            }
        }
    }
    Minimap_SavePlayerRoomInitInfo(play);
    // todo: declaration
    func_80841A50(play, this);
    this->unk_3CF = 0;
    gGameInfo->data[0x220] = 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Init.s")
#endif

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

extern Vec3f D_8085D41C;

#ifdef NON_MATCHING
// in-function static bss
void Player_Update(Actor* thisx, PlayState* play) {
    static Vec3f D_80862AF0; // sDogSpawnPos
    Player* this = (Player* ) thisx;
    s32 dogParams;
    s32 pad;
    Input input;
    s32 pad2;

    this->stateFlags3 &= ~0x10;
    if (gSaveContext.dogParams < 0) {
        if (Object_GetIndex(&play->objectCtx, 0x132) < 0) {
            gSaveContext.dogParams = 0;
        } else {
            Actor* dog;

            gSaveContext.dogParams &= (u16)~0x8000;
            func_80835BC8(this, &this->actor.world.pos, &D_8085D41C, &D_80862AF0);

            dogParams = gSaveContext.dogParams;

            dog = Actor_Spawn(&play->actorCtx, play, 0xE2, D_80862AF0.x, D_80862AF0.y, D_80862AF0.z, 0, this->actor.shape.rot.y, 0, dogParams | 0x8000);
            if (dog != NULL) {
                dog->room = -1;
            }
        }
    }

    if ((this->interactRangeActor != NULL) && (this->interactRangeActor->update == NULL)) {
        this->interactRangeActor = NULL;
    }

    if ((this->heldActor != NULL) && (this->heldActor->update == NULL)) {
        func_8082DCA0(play, this);
    }

    if ((play->actorCtx.unk268 != 0) && (this == GET_PLAYER(play))) {
        input = play->actorCtx.unk_26C;
    } else if ((this->csMode == 5) || (this->stateFlags1 & 0x20000020) || (this != GET_PLAYER(play)) || (func_8082DA90(play) != 0) || (gSaveContext.save.playerData.health == 0)) {
        bzero(&input, sizeof(Input));
        this->unk_B68 = this->actor.world.pos.y;
    } else {
        input = play->state.input[0];
        if (this->unk_B5E != 0) {
            input.cur.button &= ~0xC008;
            input.press.button &= ~0xC008;
        }
    }

    func_80844EF8(this, play, &input);
    play->actorCtx.unk268 = 0;
    bzero(&play->actorCtx.unk_26C, sizeof(Input));

    gGameInfo->data[0x214] = this->actor.world.pos.x;
    gGameInfo->data[0x215] = this->actor.world.pos.y;
    gGameInfo->data[0x216] = this->actor.world.pos.z;
    gGameInfo->data[0x217] = this->actor.world.rot.y;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Update.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_808463C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/func_80846460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_player_actor/Player_Draw.s")

void Player_Destroy(Actor* thisx, PlayState* play) {
    Player* this = (Player* ) thisx;

    Effect_Destroy(play, this->meleeWeaponEffectIndex[0]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[1]);
    Effect_Destroy(play, this->meleeWeaponEffectIndex[2]);
    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyCylinder(play, &this->cylinder);
    Collider_DestroyCylinder(play, &this->shieldCylinder);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[0]);
    Collider_DestroyQuad(play, &this->meleeWeaponQuads[1]);
    Collider_DestroyQuad(play, &this->shieldQuad);
    ZeldaArena_Free(this->giObjectSegment);
    ZeldaArena_Free(this->maskObjectSegment);
    func_80115D5C(&play->state);
    func_80831454(this);
}

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
