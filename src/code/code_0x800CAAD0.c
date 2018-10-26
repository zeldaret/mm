#include <ultra64.h>
#include <global.h>

UNK_RET func_800CAAD0(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
    UNK_TYPE sp208;
    UNK_TYPE sp144;
    UNK_TYPE sp80;
    UNK_TYPE sp68;
    UNK_TYPE sp56;
    UNK_TYPE sp36;
    
    s800CAAD0* v1;
    
    if (func_800C6024(a1) == 0) return;
    
    v1 = (s800CAAD0*)(a0 + a1 * 100);
    
    func_80139894(&sp208, v1->unk104, v1->unk108, v1->unk112, v1->unk116, v1->unk118,
                  v1->unk120, v1->unk124, v1->unk128, v1->unk132);
    
    if (func_80139188(&sp208, &sp144) == 2) return;
    
    func_80139894(&sp80, v1->unk136, v1->unk140, v1->unk144, v1->unk148, v1->unk150,
                  v1->unk152, v1->unk156, v1->unk160, v1->unk164);
                  
    func_80138C88(&sp144, (UNK_PTR)(a2 + 36), &sp36);
    func_80138C88(&sp80, &sp56, &sp68);
    
    v1->unk0 = *(UNK_TYPE*)((u8*)sp36 + 0);
    v1->unk4 = *(UNK_TYPE*)((u8*)sp36 + 4);
    v1->unk8 = *(UNK_TYPE*)((u8*)sp36 + 8);
}

UNK_RET func_800CAC0C(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
    UNK_TYPE v0;
    s16 v1;
    
    if (func_800C6024(a0) == 0) return;
    
    v0 = a0 + a1 * 100;
    
    v1 = *(s16*)(v0 + 150) - *(s16*)(v0 + 118);
    
    if (*(s16*)a2 == 0) {
        *(s16*)(a2 + 2772) += v1;
    }
    
    *(s16*)(a2 + 190) += v1;
    *(s16*)(a2 + 50) += v1;
}

UNK_RET func_800CACA0(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
    UNK_TYPE sp28;
    
    if (func_800C6024(a2) == 0) return;
    
    sp28 = func_800C6248(a0, a2);
    
    if (sp28 == 0) return;
    
    func_800CAE88(sp28);
    
    if ((*(u32*)(a1 + 4) & 0x04000000) == 0x0400) {
        func_800CAF24(sp28);
    }
    
    if ((*(u32*)(a1 + 4) & 0x20000) == 0x20000) {
        func_800CAF38(sp28);
    }
}

UNK_TYPE func_800CAD2C(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
    UNK_TYPE v1;
    UNK_TYPE sp36 = 0;
    
    if (func_800C6024(a1) == 0) return;
    
    if (((*(u16*)(a0 + a1*2 + 5084) & 0x2) != 0) || 
        ((*(u16*)(a0 + a1*2 + 5084) & 0x1) == 0)) {
        return 0;
    }
    
    v1 = func_800C6248(a0, a1);
    if (v1 == 0) {
        return 0;
    }
    
    if ((*(u32*)(v1 + 340) & 0x1) != 0) {
        func_800CAAD0(a0, a1, a2);
        sp36 = 1;
    }
    
    if ((*(u32*)(v1 + 340) & 0x2) != 0) {
        func_800CAC0C(a0, a1, a2);
        sp36 = 1;
    }
    
    return sp36;
}
