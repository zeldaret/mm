#include <ultra64.h>
#include <global.h>

UNK_RET func_800BF9A0(UNK_TYPE a0, UNK_TYPE a1) {
    s32 i;
    s800BF9A0_s* s0;
    
    func_8008439C(-2, 0);
    func_800847CC(&D_801DCBB0, D_801B4610);
    func_800847CC(&D_801DCBC4);
    
    for (i = 0, s0 = D_801AEFD0; i < D_801B4610; i++, s0++) {
        if (s0->unk16 == 0) continue;
        func_800847CC(&D_801DCBE4, i, s0->unk16, s0->unk16 + (s0->unk12 - s0->unk8), s0->unk30, &D_801DCBFC);
    }
}

UNK_TYPE func_800BFA78(UNK_TYPE a0, UNK_TYPE a1) {
    
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
