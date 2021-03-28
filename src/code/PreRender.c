#include <ultra64.h>
#include <global.h>

void PreRender_SetValuesSave(PreRenderContext* this, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg) {
    this->widthSave = width;
    this->heightSave = height;
    this->fbufSave = fbuf;
    this->cvgSave = cvg;
    this->zbufSave = zbuf;
    this->uls = 0;
    this->ult = 0;
    this->lrs = width - 1;
    this->lrt = height - 1;
}

void PreRender_Init(PreRenderContext* this) {
    bzero(this, sizeof(PreRenderContext));
    ListAlloc_Init(&this->alloc);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/PreRender_SetValues.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/PreRender_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8016FDB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8016FF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8016FF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170200.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017023C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017057C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801705B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801705EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170798.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017160C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801716C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801717F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80171F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80171FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80172078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801720C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801720FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80172758.asm")
