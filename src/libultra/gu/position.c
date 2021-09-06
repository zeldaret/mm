#include "global.h"

// #pragma GLOBAL_ASM("asm/non_matchings/boot/position/guPositionF.s")

// #pragma GLOBAL_ASM("asm/non_matchings/boot/position/guPosition.s")
#include "global.h"

/**
 * guPositionF
 * Creates a rotation/parallel translation modelling matrix (floating point)
 */
void guPositionF(f32 mf[4][4], f32 rot, f32 pitch, f32 yaw, f32 scale, f32 x, f32 y, f32 z) {
    static f32 D_80134D00 = M_PI / 180.0;
    f32 sinr, sinp, sinh;
    f32 cosr, cosp, cosh;

    rot *= D_80134D00;
    pitch *= D_80134D00;
    yaw *= D_80134D00;

    sinr = __sinf(rot);
    cosr = __cosf(rot);
    sinp = __sinf(pitch);
    cosp = __cosf(pitch);
    sinh = __sinf(yaw);
    cosh = __cosf(yaw);

    mf[0][0] = (cosp * cosh) * scale;
    mf[0][1] = (cosp * sinh) * scale;
    mf[0][2] = (-sinp) * scale;
    mf[0][3] = 0.0f;

    mf[1][0] = ((sinr * sinp * cosh) - (cosr * sinh)) * scale;
    mf[1][1] = ((sinr * sinp * sinh) + (cosr * cosh)) * scale;
    mf[1][2] = (sinr * cosp) * scale;
    mf[1][3] = 0.0f;

    mf[2][0] = ((cosr * sinp * cosh) + (sinr * sinh)) * scale;
    mf[2][1] = ((cosr * sinp * sinh) - (sinr * cosh)) * scale;
    mf[2][2] = (cosr * cosp) * scale;
    mf[2][3] = 0.0f;

    mf[3][0] = x;
    mf[3][1] = y;
    mf[3][2] = z;
    mf[3][3] = 1.0f;
}

/**
 * guPosition
 * Creates a rotational/parallel translation modeling matrix (fixed point)
 */
void guPosition(Mtx* m, f32 rot, f32 pitch, f32 yaw, f32 scale, f32 x, f32 y, f32 z) {
    f32 mf[4][4];

    guPositionF(mf, rot, pitch, yaw, scale, x, y, z);

    guMtxF2L(mf, m);
}
