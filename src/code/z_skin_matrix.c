#include <ultra64.h>
#include <global.h>

// clang-format off
MtxF sMtxFClear = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};
// clang-format on

/**
 * Multiplies a 4 component row vector [ src , 1 ] by the matrix mf and writes the resulting 4 components to xyzDest
 * and wDest.
 *
 * \f[ [\texttt{xyzDest}, \texttt{wDest}] = [\texttt{src}, 1] \cdot [mf] \f]
 */
void SkinMatrix_Vec3fMtxFMultXYZW(MtxF* mf, Vec3f* src, Vec3f* xyzDest, f32* wDest) {
    xyzDest->x = mf->wx + ((src->x * mf->xx) + (src->y * mf->yx) + (src->z * mf->zx));
    xyzDest->y = mf->wy + ((src->x * mf->xy) + (src->y * mf->yy) + (src->z * mf->zy));
    xyzDest->z = mf->wz + ((src->x * mf->xz) + (src->y * mf->yz) + (src->z * mf->zz));
    *wDest = mf->ww + ((src->x * mf->xw) + (src->y * mf->yw) + (src->z * mf->zw));
}

/**
 * Multiplies a 4 component row vector [ src , 1 ] by the matrix mf and writes the resulting xyz components to dest.
 *
 * \f[ [\texttt{dest}, -] = [\texttt{src}, 1] \cdot [mf] \f]
 */
void SkinMatrix_Vec3fMtxFMultXYZ(MtxF* mf, Vec3f* src, Vec3f* dest) {
    f32 mx = mf->xx;
    f32 my = mf->yx;
    f32 mz = mf->zx;
    f32 mw = mf->wx;
    dest->x = mw + ((src->x * mx) + (src->y * my) + (src->z * mz));

    mx = mf->xy;
    my = mf->yy;
    mz = mf->zy;
    mw = mf->wy;
    dest->y = mw + ((src->x * mx) + (src->y * my) + (src->z * mz));

    mx = mf->xz;
    my = mf->yz;
    mz = mf->zz;
    mw = mf->wz;
    dest->z = mw + ((src->x * mx) + (src->y * my) + (src->z * mz));
}

/**
 * Matrix multiplication, dest = mfA * mfB.
 * mfA and dest should not be the same matrix.
 */
void SkinMatrix_MtxFMtxFMult(MtxF* mfB, MtxF* mfA, MtxF* dest) {
    f32 rx;
    f32 ry;
    f32 rz;
    f32 rw;

    //---COL1---
    f32 cx = mfB->xx;
    f32 cy = mfB->yx;
    f32 cz = mfB->zx;
    f32 cw = mfB->wx;
    //--------

    rx = mfA->xx;
    ry = mfA->xy;
    rz = mfA->xz;
    rw = mfA->xw;
    dest->xx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->yx;
    ry = mfA->yy;
    rz = mfA->yz;
    rw = mfA->yw;
    dest->yx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->zx;
    ry = mfA->zy;
    rz = mfA->zz;
    rw = mfA->zw;
    dest->zx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->wx;
    ry = mfA->wy;
    rz = mfA->wz;
    rw = mfA->ww;
    dest->wx = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    //---2Col---
    cx = mfB->xy;
    cy = mfB->yy;
    cz = mfB->zy;
    cw = mfB->wy;
    //--------
    rx = mfA->xx;
    ry = mfA->xy;
    rz = mfA->xz;
    rw = mfA->xw;
    dest->xy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->yx;
    ry = mfA->yy;
    rz = mfA->yz;
    rw = mfA->yw;
    dest->yy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->zx;
    ry = mfA->zy;
    rz = mfA->zz;
    rw = mfA->zw;
    dest->zy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->wx;
    ry = mfA->wy;
    rz = mfA->wz;
    rw = mfA->ww;
    dest->wy = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    //---3Col---
    cx = mfB->xz;
    cy = mfB->yz;
    cz = mfB->zz;
    cw = mfB->wz;
    //--------
    rx = mfA->xx;
    ry = mfA->xy;
    rz = mfA->xz;
    rw = mfA->xw;
    dest->xz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->yx;
    ry = mfA->yy;
    rz = mfA->yz;
    rw = mfA->yw;
    dest->yz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->zx;
    ry = mfA->zy;
    rz = mfA->zz;
    rw = mfA->zw;
    dest->zz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->wx;
    ry = mfA->wy;
    rz = mfA->wz;
    rw = mfA->ww;
    dest->wz = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    //---4Col---
    cx = mfB->xw;
    cy = mfB->yw;
    cz = mfB->zw;
    cw = mfB->ww;
    //--------
    rx = mfA->xx;
    ry = mfA->xy;
    rz = mfA->xz;
    rw = mfA->xw;
    dest->xw = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->yx;
    ry = mfA->yy;
    rz = mfA->yz;
    rw = mfA->yw;
    dest->yw = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->zx;
    ry = mfA->zy;
    rz = mfA->zz;
    rw = mfA->zw;
    dest->zw = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);

    rx = mfA->wx;
    ry = mfA->wy;
    rz = mfA->wz;
    rw = mfA->ww;
    dest->ww = (cx * rx) + (cy * ry) + (cz * rz) + (cw * rw);
}

/**
 * "Clear" in this file means the identity matrix.
 */
void SkinMatrix_GetClear(MtxF** mfp) {
    *mfp = &sMtxFClear;
}

void SkinMatrix_Clear(MtxF* mf) {
    mf->xx = 1.0f;
    mf->xy = 0.0f;
    mf->xz = 0.0f;
    mf->xw = 0.0f;
    mf->yx = 0.0f;
    mf->yy = 1.0f;
    mf->yz = 0.0f;
    mf->yw = 0.0f;
    mf->zx = 0.0f;
    mf->zy = 0.0f;
    mf->zz = 1.0f;
    mf->zw = 0.0f;
    mf->wx = 0.0f;
    mf->wy = 0.0f;
    mf->wz = 0.0f;
    mf->ww = 1.0f;
}

void SkinMatrix_MtxFCopy(MtxF* src, MtxF* dest) {
    dest->xx = src->xx;
    dest->xy = src->xy;
    dest->xz = src->xz;
    dest->xw = src->xw;
    dest->yx = src->yx;
    dest->yy = src->yy;
    dest->yz = src->yz;
    dest->yw = src->yw;
    dest->zx = src->zx;
    dest->zy = src->zy;
    dest->zz = src->zz;
    dest->zw = src->zw;
    dest->wx = src->wx;
    dest->wy = src->wy;
    dest->wz = src->wz;
    dest->ww = src->ww;
}

/**
 * Inverts a matrix using a slight modification of the Gauss-Jordan method
 * (column operations instead of row operations).
 * returns 0 if successfully inverted
 * returns 2 if matrix non-invertible (0 determinant)
 */
s32 SkinMatrix_Invert(MtxF* src, MtxF* dest) {
    MtxF mfCopy;
    s32 i;
    f32 temp2;
    s32 thisRow;
    s32 thisCol;

    SkinMatrix_MtxFCopy(src, &mfCopy);
    SkinMatrix_Clear(dest);

    for (thisRow = 0; thisRow < 4; thisRow++) {
        thisCol = thisRow;
        while ((thisCol < 4) && (fabsf(mfCopy.mf[thisRow][thisCol]) < 0.0005f)) {
            thisCol++;
        }
        if (thisCol == 4) {
            // reaching col = 4 means the row is either all 0 or a duplicate row.
            // therefore singular matrix (0 determinant).
            return 2;
        }
        if (thisCol != thisRow) { // responsible for swapping columns if zero on diagonal
            for (i = 0; i < 4; i++) {
                SWAP(f32, mfCopy.mf[i][thisCol], mfCopy.mf[i][thisRow]);
                SWAP(f32, dest->mf[i][thisCol], dest->mf[i][thisRow]);
            }
        }

        // Scale this whole column s.t. the diag element = 1
        temp2 = mfCopy.mf[thisRow][thisRow];
        for (i = 0; i < 4; i++) {
            mfCopy.mf[i][thisRow] /= temp2;
            dest->mf[i][thisRow] /= temp2;
        }

        for (thisCol = 0; thisCol < 4; thisCol++) {
            if (thisCol != thisRow) {
                temp2 = mfCopy.mf[thisRow][thisCol];
                for (i = 0; i < 4; i++) {
                    mfCopy.mf[i][thisCol] -= mfCopy.mf[i][thisRow] * temp2;
                    dest->mf[i][thisCol] -= dest->mf[i][thisRow] * temp2;
                }
            }
        }
    }

    return 0;
}

/**
 * Produces a matrix which scales x,y,z components of vectors or x,y,z rows of matrices (when applied on LHS)
 */
void SkinMatrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z) {
    mf->xy = 0.0f;
    mf->xz = 0.0f;
    mf->xw = 0.0f;
    mf->yx = 0.0f;
    mf->yz = 0.0f;
    mf->yw = 0.0f;
    mf->zx = 0.0f;
    mf->zy = 0.0f;
    mf->zw = 0.0f;
    mf->wx = 0.0f;
    mf->wy = 0.0f;
    mf->wz = 0.0f;
    mf->ww = 1.0f;
    mf->xx = x;
    mf->yy = y;
    mf->zz = z;
}

/**
 * Produces a rotation matrix = (roll rotation matrix) * (pitch rotation matrix) * (yaw rotation matrix)
 */
void SkinMatrix_SetRotateRPY(MtxF* mf, s16 roll, s16 pitch, s16 yaw) {
    f32 cos2;
    f32 sin = Math_SinS(yaw);
    f32 cos = Math_CosS(yaw);
    f32 yx;
    f32 sin2;
    f32 zx;
    f32 yy;
    f32 zy;

    mf->yy = cos;
    mf->yx = -sin;
    mf->xw = mf->yw = mf->zw = 0;
    mf->wx = mf->wy = mf->wz = 0;
    mf->ww = 1;

    if (pitch != 0) {
        sin2 = Math_SinS(pitch);
        cos2 = Math_CosS(pitch);

        mf->xx = cos * cos2;
        mf->zx = cos * sin2;

        mf->xy = sin * cos2;
        mf->zy = sin * sin2;
        mf->xz = -sin2;
        mf->zz = cos2;
    } else {
        mf->xx = cos;
        if (1) {}
        if (1) {}
        zx = sin; // required to match
        mf->xy = sin;
        mf->xz = mf->zx = mf->zy = 0;
        mf->zz = 1;
    }

    if (roll != 0) {
        sin2 = Math_SinS(roll);
        cos2 = Math_CosS(roll);

        yx = mf->yx;
        zx = mf->zx;
        mf->yx = (yx * cos2) + (zx * sin2);
        mf->zx = (zx * cos2) - (yx * sin2);

        if (1) {}
        zy = mf->zy;
        yy = mf->yy;
        mf->yy = (yy * cos2) + (zy * sin2);
        mf->zy = (zy * cos2) - (yy * sin2);

        if (cos2) {}
        mf->yz = mf->zz * sin2;
        mf->zz = mf->zz * cos2;
    } else {
        mf->yz = 0;
    }
}

/**
 * Produces a rotation matrix = (yaw rotation matrix) * (roll rotation matrix) * (pitch rotation matrix)
 */
void SkinMatrix_SetRotateYRP(MtxF* mf, s16 yaw, s16 roll, s16 pitch) {
    f32 cos2;
    f32 sin;
    f32 cos;
    f32 xz;
    f32 sin2;
    f32 yz;
    f32 xx;
    f32 yx;

    sin = Math_SinS(roll);
    cos = Math_CosS(roll);

    mf->xx = cos;
    mf->xz = -sin;
    mf->zw = 0;
    mf->yw = 0;
    mf->xw = 0;
    mf->wz = 0;
    mf->wy = 0;
    mf->wx = 0;
    mf->ww = 1;

    if (yaw != 0) {
        sin2 = Math_SinS(yaw);
        cos2 = Math_CosS(yaw);

        mf->zz = cos * cos2;
        mf->yz = cos * sin2;

        mf->zx = sin * cos2;
        mf->yx = sin * sin2;
        mf->zy = -sin2;
        mf->yy = cos2;
    } else {
        mf->zz = cos;
        if (1) {}
        if (1) {}
        yx = sin; // required to match
        mf->zx = sin;
        mf->yx = mf->yz = mf->zy = 0;
        mf->yy = 1;
    }

    if (pitch != 0) {
        sin2 = Math_SinS(pitch);
        cos2 = Math_CosS(pitch);
        xx = mf->xx;
        yx = mf->yx;
        mf->xx = (xx * cos2) + (yx * sin2);
        mf->yx = yx * cos2 - (xx * sin2);
        if (1) {}
        yz = mf->yz;
        xz = mf->xz;
        mf->xz = (xz * cos2) + (yz * sin2);
        mf->yz = (yz * cos2) - (xz * sin2);
        if (cos2) {}
        mf->xy = mf->yy * sin2;
        mf->yy = mf->yy * cos2;
    } else {
        mf->xy = 0;
    }
}

/**
 * Produces a matrix which translates a vector by amounts in the x, y and z directions
 */
void SkinMatrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z) {
    mf->xy = 0.0f;
    mf->xz = 0.0f;
    mf->xw = 0.0f;
    mf->yx = 0.0f;
    mf->yz = 0.0f;
    mf->yw = 0.0f;
    mf->zx = 0.0f;
    mf->zy = 0.0f;
    mf->zw = 0.0f;
    mf->xx = 1.0f;
    mf->yy = 1.0f;
    mf->zz = 1.0f;
    mf->ww = 1.0f;
    mf->wx = x;
    mf->wy = y;
    mf->wz = z;
}

/**
 * Produces a matrix which scales, then rotates (RPY), then translates a vector
 */
void SkinMatrix_SetScaleRotateRPYTranslate(MtxF* mf, f32 scaleX, f32 scaleY, f32 scaleZ, s16 roll, s16 pitch, s16 yaw,
                                           f32 dx, f32 dy, f32 dz) {
    MtxF mft1;
    MtxF mft2;

    SkinMatrix_SetTranslate(mf, dx, dy, dz);
    SkinMatrix_SetRotateRPY(&mft1, roll, pitch, yaw);
    SkinMatrix_MtxFMtxFMult(mf, &mft1, &mft2);
    SkinMatrix_SetScale(&mft1, scaleX, scaleY, scaleZ);
    SkinMatrix_MtxFMtxFMult(&mft2, &mft1, mf);
}

/**
 * Produces a matrix which scales, then rotates (YRP), then translates a vector
 */
void SkinMatrix_SetScaleRotateYRPTranslate(MtxF* mf, f32 scaleX, f32 scaleY, f32 scaleZ, s16 yaw, s16 roll, s16 pitch,
                                           f32 dx, f32 dy, f32 dz) {
    MtxF mft1;
    MtxF mft2;

    SkinMatrix_SetTranslate(mf, dx, dy, dz);
    SkinMatrix_SetRotateYRP(&mft1, yaw, roll, pitch);
    SkinMatrix_MtxFMtxFMult(mf, &mft1, &mft2);
    SkinMatrix_SetScale(&mft1, scaleX, scaleY, scaleZ);
    SkinMatrix_MtxFMtxFMult(&mft2, &mft1, mf);
}

/**
 * Produces a matrix which rotates (RPY), then translates a vector
 */
void SkinMatrix_SetRotateRPYTranslate(MtxF* mf, s16 roll, s16 pitch, s16 yaw, f32 dx, f32 dy, f32 dz) {
    MtxF mft1;
    MtxF mft2;

    SkinMatrix_SetTranslate(&mft2, dx, dy, dz);
    SkinMatrix_SetRotateRPY(&mft1, roll, pitch, yaw);
    SkinMatrix_MtxFMtxFMult(&mft2, &mft1, mf);
}

void SkinMatrix_Vec3fToVec3s(Vec3f* src, Vec3s* dest) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void SkinMatrix_Vec3sToVec3f(Vec3s* src, Vec3f* dest) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void SkinMatrix_MtxFToMtx(MtxF* src, Mtx* dest) {
    s32 temp;
    u16* m1 = (u16*)&dest->m[0][0];
    u16* m2 = (u16*)&dest->m[2][0];

    temp = src->xx * 0x10000;
    m1[0] = (temp >> 0x10);
    m1[16 + 0] = temp & 0xFFFF;

    temp = src->xy * 0x10000;
    m1[1] = (temp >> 0x10);
    m1[16 + 1] = temp & 0xFFFF;

    temp = src->xz * 0x10000;
    m1[2] = (temp >> 0x10);
    m1[16 + 2] = temp & 0xFFFF;

    temp = src->xw * 0x10000;
    m1[3] = (temp >> 0x10);
    m1[16 + 3] = temp & 0xFFFF;

    temp = src->yx * 0x10000;
    m1[4] = (temp >> 0x10);
    m1[16 + 4] = temp & 0xFFFF;

    temp = src->yy * 0x10000;
    m1[5] = (temp >> 0x10);
    m1[16 + 5] = temp & 0xFFFF;

    temp = src->yz * 0x10000;
    m1[6] = (temp >> 0x10);
    m1[16 + 6] = temp & 0xFFFF;

    temp = src->yw * 0x10000;
    m1[7] = (temp >> 0x10);
    m1[16 + 7] = temp & 0xFFFF;

    temp = src->zx * 0x10000;
    m1[8] = (temp >> 0x10);
    m1[16 + 8] = temp & 0xFFFF;

    temp = src->zy * 0x10000;
    m1[9] = (temp >> 0x10);
    m2[9] = temp & 0xFFFF;

    temp = src->zz * 0x10000;
    m1[10] = (temp >> 0x10);
    m2[10] = temp & 0xFFFF;

    temp = src->zw * 0x10000;
    m1[11] = (temp >> 0x10);
    m2[11] = temp & 0xFFFF;

    temp = src->wx * 0x10000;
    m1[12] = (temp >> 0x10);
    m2[12] = temp & 0xFFFF;

    temp = src->wy * 0x10000;
    m1[13] = (temp >> 0x10);
    m2[13] = temp & 0xFFFF;

    temp = src->wz * 0x10000;
    m1[14] = (temp >> 0x10);
    m2[14] = temp & 0xFFFF;

    temp = src->ww * 0x10000;
    m1[15] = (temp >> 0x10);
    m2[15] = temp & 0xFFFF;
}

Mtx* SkinMatrix_MtxFToNewMtx(GraphicsContext* gfxCtx, MtxF* src) {
    s32 pad;
    Mtx* mtx;

    // TODO allocation should be a macro
    mtx = (Mtx*)((int)gfxCtx->polyOpa.d - sizeof(Mtx));
    gfxCtx->polyOpa.d = (void*)mtx;

    if (mtx == NULL) {
        return NULL;
    }

    SkinMatrix_MtxFToMtx(src, mtx);
    return mtx;
}

/**
 * Produces a matrix which rotates vectors by angle a around a unit vector with components (x,y,z)
 */
void SkinMatrix_SetRotateAroundVec(MtxF* mf, s16 a, f32 x, f32 y, f32 z) {
    f32 sinA;
    f32 cosA;
    f32 xx;
    f32 yy;
    f32 zz;
    f32 xy;
    f32 yz;
    f32 xz;
    f32 pad;

    sinA = Math_SinS(a);
    cosA = Math_CosS(a);

    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    xz = x * z;

    mf->xx = (1.0f - xx) * cosA + xx;
    mf->xy = (1.0f - cosA) * xy + z * sinA;
    mf->xz = (1.0f - cosA) * xz - y * sinA;
    mf->xw = 0.0f;

    mf->yx = (1.0f - cosA) * xy - z * sinA;
    mf->yy = (1.0f - yy) * cosA + yy;
    mf->yz = (1.0f - cosA) * yz + x * sinA;
    mf->yw = 0.0f;

    mf->zx = (1.0f - cosA) * xz + y * sinA;
    mf->zy = (1.0f - cosA) * yz - x * sinA;
    mf->zz = (1.0f - zz) * cosA + zz;
    mf->zw = 0.0f;

    mf->wx = mf->wy = mf->wz = 0.0f;
    mf->ww = 1.0f;
}

void SkinMatrix_SetXRotation(MtxF* mf, s16 a) {
    f32 sinA;
    f32 cosA;

    if (a != 0) {
        sinA = Math_SinS(a);
        cosA = Math_CosS(a);
    } else {
        sinA = 0.0f;
        cosA = 1.0f;
    }

    mf->xy = 0.0f;
    mf->xz = 0.0f;
    mf->xw = 0.0f;

    mf->yx = 0.0f;
    mf->yw = 0.0f;

    mf->zx = 0.0f;
    mf->zw = 0.0f;

    mf->wx = 0.0f;
    mf->wy = 0.0f;
    mf->wz = 0.0f;

    mf->xx = 1.0f;
    mf->ww = 1.0f;

    mf->yy = cosA;
    mf->zz = cosA;
    mf->yz = sinA;
    mf->zy = -sinA;
}

void SkinMatrix_MulXRotation(MtxF* mf, s16 a) {
    f32 sinA;
    f32 cosA;
    f32 ry;
    f32 rz;

    if (a != 0) {
        sinA = Math_SinS(a);
        cosA = Math_CosS(a);

        ry = mf->yx;
        rz = mf->zx;
        mf->yx = ry * cosA + rz * sinA;
        mf->zx = rz * cosA - ry * sinA;

        ry = mf->yy;
        rz = mf->zy;
        mf->yy = ry * cosA + rz * sinA;
        mf->zy = rz * cosA - ry * sinA;

        ry = mf->yz;
        rz = mf->zz;
        mf->yz = ry * cosA + rz * sinA;
        mf->zz = rz * cosA - ry * sinA;

        ry = mf->yw;
        rz = mf->zw;
        mf->yw = ry * cosA + rz * sinA;
        mf->zw = rz * cosA - ry * sinA;
    }
}

void SkinMatrix_SetYRotation(MtxF* mf, s16 a) {
    f32 sinA;
    f32 cosA;

    if (a != 0) {
        sinA = Math_SinS(a);
        cosA = Math_CosS(a);
    } else {
        sinA = 0.0f;
        cosA = 1.0f;
    }

    mf->xy = 0.0f;
    mf->xw = 0.0f;

    mf->yx = 0.0f;
    mf->yz = 0.0f;
    mf->yw = 0.0f;

    mf->zy = 0.0f;
    mf->zw = 0.0f;

    mf->wx = 0.0f;
    mf->wy = 0.0f;
    mf->wz = 0.0f;

    mf->yy = 1.0f;
    mf->ww = 1.0f;

    mf->xx = cosA;
    mf->zz = cosA;
    mf->xz = -sinA;
    mf->zx = sinA;
}

void SkinMatrix_MulYRotation(MtxF* mf, s16 a) {
    f32 sinA;
    f32 cosA;
    f32 rx;
    f32 rz;

    if (a != 0) {
        sinA = Math_SinS(a);
        cosA = Math_CosS(a);

        rx = mf->xx;
        rz = mf->zx;
        mf->xx = rx * cosA - rz * sinA;
        mf->zx = rx * sinA + rz * cosA;

        rx = mf->xy;
        rz = mf->zy;
        mf->xy = rx * cosA - rz * sinA;
        mf->zy = rx * sinA + rz * cosA;

        rx = mf->xz;
        rz = mf->zz;
        mf->xz = rx * cosA - rz * sinA;
        mf->zz = rx * sinA + rz * cosA;

        rx = mf->xw;
        rz = mf->zw;
        mf->xw = rx * cosA - rz * sinA;
        mf->zw = rx * sinA + rz * cosA;
    }
}

void SkinMatrix_SetZRotation(MtxF* mf, s16 a) {
    f32 sinA;
    f32 cosA;

    if (a != 0) {
        sinA = Math_SinS(a);
        cosA = Math_CosS(a);
    } else {
        sinA = 0.0f;
        cosA = 1.0f;
    }

    mf->xz = 0.0f;
    mf->xw = 0.0f;

    mf->yz = 0.0f;
    mf->yw = 0.0f;

    mf->zx = 0.0f;
    mf->zy = 0.0f;
    mf->zw = 0.0f;

    mf->wx = 0.0f;
    mf->wy = 0.0f;
    mf->wz = 0.0f;

    mf->zz = 1.0f;
    mf->ww = 1.0f;

    mf->xx = cosA;
    mf->yy = cosA;
    mf->xy = sinA;
    mf->yx = -sinA;
}
