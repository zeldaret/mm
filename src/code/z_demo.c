#include "global.h"

#if 0

glabel D_801F4D40
/* 010DA0 801F4D40 */ .space 0x2

glabel D_801F4D42
/* 010DA2 801F4D42 */ .space 0x6

glabel D_801F4D48
/* 010DA8 801F4D48 */ .space 0x80

glabel D_801F4DC8
/* 010E28 801F4DC8 */ .space 0x2

glabel D_801F4DCA
/* 010E2A 801F4DCA */ .space 0x2

glabel D_801F4DCC
/* 010E2C 801F4DCC */ .space 0x10

glabel D_801F4DDC
/* 010E3C 801F4DDC */ .space 0x4

glabel D_801F4DE0
/* 010E40 801F4DE0 */ .space 0x2

glabel D_801F4DE2
/* 010E42 801F4DE2 */ .space 0xE
#endif


#if 0
void Cutscene_Init(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    ?* temp_v0;
    ?* phi_v0;

    csCtx->state = 0;
    csCtx->frames = 0;
    csCtx->unk_0C = 0.0f;
    globalCtx->csCtx.sceneCsCount = 0;
    globalCtx->csCtx.unk_12 = 0;
    D_801F4DCA = 0;
    D_801F4DCA = 0;
    phi_v0 = &D_801F4DCC;
    do {
        temp_v0 = phi_v0 + 8;
        temp_v0->unk_-6 = 0;
        temp_v0->unk_-4 = 0;
        temp_v0->unk_-2 = 0;
        temp_v0->unk_-8 = 0;
        phi_v0 = temp_v0;
    } while (temp_v0 != &D_801F4DDC);
    D_801F4DE0 = 0;
    func_801A3F54(0);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_Init.s")
#endif

void func_800EA0D4(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    csCtx->state = 1;
    csCtx->linkAction = NULL;
}

void func_800EA0EC(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (csCtx->state != 4) {
        csCtx->state = 3;
    }
}

void Cutscene_StepCutscene1(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (gSaveContext.cutscene < 0xFFF0) {
        sCsStateHandlers1[csCtx->state](globalCtx, csCtx);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_StepCutscene2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_Nop800EA210.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EA220.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EA258.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EA2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EA324.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EABAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAC08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAC44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAC94.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAD48.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EADB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB1DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB364.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB4B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBCD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBD60.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC678.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC924.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800ECD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_ProcessCommands.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800ED980.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800ED9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDBE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/nop_800EDDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDDBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDDCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDF78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE1D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE200.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE2F4.s")
