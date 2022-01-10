# Introduction

In this project, we are decompiling The Legend of Zelda: Majora's Mask. This means that we take the assembly language that is on the cartridge,

```
glabel func_809529AC
/* 00038C 809529AC 27BDFFE0 */  addiu       $sp, $sp, -0x20
/* 000390 809529B0 AFBF001C */  sw          $ra, 0x1c($sp)
/* 000394 809529B4 AFA40020 */  sw          $a0, 0x20($sp)
/* 000398 809529B8 0C02E27E */  jal         Actor_HasParent
/* 00039C 809529BC AFA50024 */   sw         $a1, 0x24($sp)
/* 0003A0 809529C0 8FA40020 */  lw          $a0, 0x20($sp)
/* 0003A4 809529C4 1040000C */  beqz        $v0, .L809529F8
/* 0003A8 809529C8 8FA50024 */   lw         $a1, 0x24($sp)
/* 0003AC 809529CC A4800116 */  sh          $zero, 0x116($a0)
/* 0003B0 809529D0 8C860098 */  lw          $a2, 0x98($a0)
/* 0003B4 809529D4 8C87009C */  lw          $a3, 0x9c($a0)
/* 0003B8 809529D8 AFA40020 */  sw          $a0, 0x20($sp)
/* 0003BC 809529DC 0C02E140 */  jal         func_800B8500
/* 0003C0 809529E0 AFA00010 */   sw         $zero, 0x10($sp)
/* 0003C4 809529E4 8FA40020 */  lw          $a0, 0x20($sp)
/* 0003C8 809529E8 3C0E8095 */  lui         $t6, %hi(func_80952A1C)
/* 0003CC 809529EC 25CE2A1C */  addiu       $t6, $t6, %lo(func_80952A1C)
/* 0003D0 809529F0 10000006 */  b           .L80952A0C
/* 0003D4 809529F4 AC8E01F4 */   sw         $t6, 0x1f4($a0)
.L809529F8:
/* 0003D8 809529F8 C484009C */  lwc1        $f4, 0x9c($a0)
/* 0003DC 809529FC 8C870098 */  lw          $a3, 0x98($a0)
/* 0003E0 80952A00 24060035 */  addiu       $a2, $zero, 0x35
/* 0003E4 80952A04 0C02E287 */  jal         Actor_PickUp
/* 0003E8 80952A08 E7A40010 */   swc1       $f4, 0x10($sp)
.L80952A0C:
/* 0003EC 80952A0C 8FBF001C */  lw          $ra, 0x1c($sp)
/* 0003F0 80952A10 27BD0020 */  addiu       $sp, $sp, 0x20
/* 0003F4 80952A14 03E00008 */  jr          $ra
/* 0003F8 80952A18 00000000 */   nop
```

(the commented numbers on the left are the original machine code, the middle the translation into MIPS assembly, the right useful information about the numbers in the code)
and turn it into compilable C code:

```C
void func_809529AC(EnMs *this, GlobalContext *globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.textId = 0;
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, 0);
        this->actionFunc = func_80952A1C;
    } else {
        Actor_PickUp(&this->actor, globalCtx, 0x35, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    }
}
```

which is intended to be as close to the original code as we can get just by looking at the assembly. We are doing *matching* decomp: in the right context, and with the right compiler settings, the above C compiles into *precisely* the assembly code above, not just equivalent code.

N.B. We are using only publicly available code. In particular, we are not looking at any of the recent Nintendo source code leaks.

Progress of the project can be found at [https://zelda64.dev]. The long-term goal of this project is to obtain a complete compilable version of the code for every publicly released version of Majora's Mask (in the same way as the Ocarina of Time project and many other Zelda games). *We are not working on a PC Port, and neither this project nor the ZeldaRET organisation will not be making one*, although the resulting code will be very useful if someone does intend to make such a port.

Most of the discussion on the project takes place on the Zelda Decompilation Discord (linked in the [README.md](../../README.md)). We are very welcoming to newcomers and are happy to help you with any problems you might have with the decompilation process.

## What do I need to know to take part?

Basic knowledge of C, particularly arrays and pointers, is extremely useful. Knowledge of MIPS is not required initially, but if you are serious about decompilation you will soon pick up a lot of it.

Knowledge of the fundamentals of git and GitHub is required. There are a number of tutorials available online, and a later document in this tutorial describes how you contribute to this project outside the actual decompilation process.

The most useful knowledge to have is a general understanding of how the game works. An afternoon of constructive mucking about in the [Practice Rom](https://kz.zeldacodes.org/) (aka KZ) will be very beneficial if you have not looked at the game's subsurface workings before.

## Structure of the code

A lot of work has already been done on the code to bring it into a format that is easy to decompile. I will discuss actors, since this is where the majority of new people should begin.

An *actor* is any thing in the game that moves or performs actions or interactions: Link is an actor, enemies are actors, NPCs are actors, props like grass are actors. The vast majority of actors are *overlays*, which means they are loaded only when the game needs them.

In the code, each actor is associated to several files: there is 
- the main .c file, e.g. `src/overlays/actors/ovl_En_Ms/z_en_ms.c`
- the actor's Header file, e.g. `src/overlays/actors/ovl_En_Ms/z_en_ms.h`
- various .o files that tell the `make` script how to incorporate it into building the ROM, 

and then for undecompiled actors, various assembly (.s) files, generally including: 
- one for the actor's *data* (this usually includes things like its collision information about how to draw it, and various other stuff that is used in it), e.g. `data/overlays/actors/ovl_En_Ms.data.s`
- one for each function in the actor, e.g. `asm/non_matchings/overlays/actors/ovl_En_Ms/func_809529AC.s`

(In this project, all assembly code and asset files are extracted from a user-provided ROM: if you look in the GitHub repository, you will see that only decompiled source code is present.)

The basic process of decomp is to take one or more of the .s files, run it through a decompilation program (mips_to_c) that reads the ASM very literally, and then, through human ingenuity, reshape it into code that not only compiles in the first place, but completely matches the assembly generation of the original code (well-written or otherwise; it's also very likely that our constructed code differs significantly from the original, even if it still compiles to the same thing).
