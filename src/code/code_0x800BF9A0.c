#include <ultra64.h>
#include <global.h>

UNK_RET func_800BF9A0(UNK_TYPE a0, UNK_TYPE a1) {
    s32 i;
    s800BF9A0* s0;
    UNK_TYPE v1;

    func_8008439C(-2, 0);
    func_800847CC(&D_801DCBB0, D_801B4610);
    func_800847CC(&D_801DCBC4);

    for (i = 0, s0 = &D_801AEFD0; i < D_801B4610; i++, s0++) {
        v1 = s0->unkC - s0->unk8;
        if (s0->unk10 == 0) continue;
        func_800847CC(&D_801DCBE4, i, s0->unk10, s0->unk10 + v1, s0->unk1E, &D_801DCBFC);
    }
}

UNK_TYPE func_800BFA78(UNK_TYPE a0, UNK_TYPE a1) {
    s32 i;
    s800BF9A0* v0 = &D_801AEFD0;
    UNK_TYPE t1;
    UNK_TYPE a2;
    UNK_TYPE a0_2 = a0;

    for (i = 0; i < D_801B4610; i++, v0++) {
        t1 = v0->unk8 - v0->unk10;
        a2 = v0->unkC - v0->unk8;

        if (v0->unk10 == 0) continue;
        if (a0_2 < v0->unk10) continue;

        if (a0_2 < (v0->unk10 + a2)) {
            return a0_2 + t1;
        }
    }

    return 0;
}

UNK_RET func_800BFAE8(UNK_ARGS) {
    D_801B4610 = 690;
    func_800819F0(&D_801ED930, func_800BF9A0, 0, 0);
    func_80081BCC(&D_801ED940, func_800BFA78, 0);
}

UNK_RET func_800BFB40(UNK_ARGS) {
    func_80081AD4(&D_801ED930);
    func_80081CA4(&D_801ED940);
    D_801B4610 = 0;
}
