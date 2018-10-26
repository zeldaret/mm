#include <ultra64.h>
#include <global.h>

UNK_RET func_800A5AC0(void* a0, UNK_TYPE a1) {
    struct s800A5AC0* s0 = (struct s800A5AC0*)a0;
    s0->unk278 = ((s0->unk28 >> 8) & 0xFF) | 0x300;
    s0->unk28 = (s0->unk28 & 0xFF) - 9;
    func_800FFADC(s0, &D_801ADEAC);
    func_800B3BA4(&s0->unk188, 0, (void*)&func_800B3FC0, 0x41400000);
    func_800E1374(a1, &s0->unk328, s0, &D_801ADE80);
    func_800E7DF8(s0, &s0->unk328);
    s0->unk182 = 255;
    s0->unk324 = func_800A5B98;
}

UNK_RET func_800A5B6C(struct s800A5AC0* a0, UNK_TYPE a1) {
    func_800E11EC(a1, &a0->unk328);
}

UNK_RET func_800A5B98(struct s800A5AC0* a0, UNK_TYPE a1) {
    s16 v0;
    s32 v1;
    if (func_800B84D0(a0, a1) != 0) {
        a0->unk324 = func_800A5C28;
    } else {
        v0 = a0->unk146 - a0->unk190;
        if (v0 < 0) {
            v1 = -v0;
        } else {
            v1 = v0;
        }
        if ((v1 < 10240) || ((a0->unk28 == 1) && (v1 > 22528))) {
            func_800B863C(a0, a1);
        }
    }
}

UNK_RET func_800A5C28(struct s800A5AC0* a0, UNK_TYPE a1 /* unused */ ) {
    if (func_800B867C(a0) != 0) {
        a0->unk324 = func_800A5B98;
    }
}

UNK_RET func_800A5C60(struct s800A5AC0* a0, UNK_TYPE a1) {
    (a0->unk324)(a0, a1);
    func_800B675C(a0, 0x42340000);
    func_800E2928(a1, a1 + 0x18884, &a0->unk328);
}

UNK_RET func_800A5CB8(struct s800A5AC0* a0, UNK_TYPE a1) {
    func_800BDFC0(a1, D_801ADEB0[a0->unk28], a1, a0);
}
