#include <ultra64.h>
#include <global.h>

UNK_RET func_800CAAD0(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
    UNK_TYPE spD0;
    UNK_TYPE sp90;
    UNK_TYPE sp50;
    UNK_TYPE sp44;
    UNK_TYPE sp38;
    UNK_TYPE sp24;

    s800CAAD0* v1;

    if (func_800C6024(a1) == 0) return;

    v1 = (s800CAAD0*)(a0 + a1 * 100);

    func_80139894(&spD0, v1->unk68, v1->unk6C, v1->unk70, v1->unk74, v1->unk76,
                  v1->unk78, v1->unk7C, v1->unk80, v1->unk84);

    if (func_80139188(&spD0, &sp90) == 2) return;

    func_80139894(&sp50, v1->unk88, v1->unk8C, v1->unk90, v1->unk94, v1->unk96,
                  v1->unk98, v1->unk9C, v1->unkA0, v1->unkA4);

    func_80138C88(&sp90, (UNK_PTR)(a2 + 36), &sp24);
    func_80138C88(&sp50, &sp38, &sp44);

    v1->unk0 = *(UNK_TYPE*)((u8*)sp24 + 0);
    v1->unk4 = *(UNK_TYPE*)((u8*)sp24 + 4);
    v1->unk8 = *(UNK_TYPE*)((u8*)sp24 + 8);
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
    UNK_TYPE sp1C;

    if (func_800C6024(a2) == 0) return;

    sp1C = func_800C6248(a0, a2);

    if (sp1C == 0) return;

    func_800CAE88(sp1C);

    if ((*(u32*)(a1 + 4) & 0x04000000) == 0x0400) {
        func_800CAF24(sp1C);
    }

    if ((*(u32*)(a1 + 4) & 0x20000) == 0x20000) {
        func_800CAF38(sp1C);
    }
}

UNK_TYPE func_800CAD2C(UNK_TYPE a0, UNK_TYPE a1, UNK_TYPE a2) {
    UNK_TYPE v1;
    UNK_TYPE sp24 = 0;

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
        sp24 = 1;
    }

    if ((*(u32*)(v1 + 340) & 0x2) != 0) {
        func_800CAC0C(a0, a1, a2);
        sp24 = 1;
    }

    return sp24;
}
