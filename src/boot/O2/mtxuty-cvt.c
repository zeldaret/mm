#include "global.h"

void MtxConv_F2L(Mtx* mtx, MtxF* mf) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s32 value = (mf->mf[i][j] * 0x10000);
            struct {
                u16 intPart[4][4];
                u16 fracPart[4][4];
            }* mu = (void*)mtx;

            mu->intPart[i][j] = value >> 16;
            mu->fracPart[i][j] = value;
        }
    }
}

void MtxConv_L2F(MtxF* mtx, Mtx* mf) {
    guMtxL2F(mtx->mf, mf);
}
