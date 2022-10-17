#include "global.h"

/**
 * Calculates the distances between `a` and `b`
 */
f32 OLib_Vec3fDist(Vec3f* a, Vec3f* b) {
    f32 dx = a->x - b->x;
    f32 dy = a->y - b->y;
    f32 dz = a->z - b->z;

    return sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
}

/**
 * Calculates the distances between `a` and `b`, and outputs the vector
 * created by the difference into `dest`
 */
f32 OLib_Vec3fDistOutDiff(Vec3f* a, Vec3f* b, Vec3f* dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;

    return sqrtf(SQ(dest->x) + SQ(dest->y) + SQ(dest->z));
}

/**
 * Calculates the distances on the xz plane between `a` and `b`
 */
f32 OLib_Vec3fDistXZ(Vec3f* a, Vec3f* b) {
    return sqrtf(SQ(a->x - b->x) + SQ(a->z - b->z));
}

/**
 * Clamps `val` to a maximum of -`min` as `val` approaches zero, and a minimum of
 * `min` as `val` approaches zero
 */
f32 OLib_ClampMinDist(f32 val, f32 min) {
    if (val < 0.0f) {
        return CLAMP_MAX(val, -min);
    } else {
        return CLAMP_MIN(val, min);
    }
}

/**
 * Clamps `val` to a minimum of -`max` as `val` approaches -`max`, and a maximum of `max`
 * as `val` approaches `max`
 */
f32 OLib_ClampMaxDist(f32 val, f32 max) {
    if (val < 0.0f) {
        return CLAMP_MIN(val, -max);
    } else {
        return CLAMP_MAX(val, max);
    }
}

/**
 * Takes the difference of points b and a, and creates a normal vector
 */
Vec3f* OLib_Vec3fDistNormalize(Vec3f* dest, Vec3f* a, Vec3f* b) {
    Vec3f v1;
    Vec3f v2;
    f32 dist;

    v1.x = b->x - a->x;
    v1.y = b->y - a->y;
    v1.z = b->z - a->z;

    dist = OLib_ClampMinDist(sqrtf(SQXYZ(v1)), 0.01f);

    v2.x = v1.x / dist;
    v2.y = v1.y / dist;
    v2.z = v1.z / dist;

    *dest = v2;

    return dest;
}

/**
 * Takes the spherical coordinate `sph`, and converts it into a x,y,z position
 */
Vec3f* OLib_VecSphToVec3f(Vec3f* dest, VecSph* sph) {
    Vec3f v;
    f32 sinPitch;
    f32 cosPitch = Math_CosS(sph->pitch);
    f32 sinYaw;
    f32 cosYaw = Math_CosS(sph->yaw);

    sinPitch = Math_SinS(sph->pitch);
    sinYaw = Math_SinS(sph->yaw);

    v.x = sph->r * sinPitch * sinYaw;
    v.y = sph->r * cosPitch;
    v.z = sph->r * sinPitch * cosYaw;

    *dest = v;

    return dest;
}

/**
 * Takes the geographic point `geo` and converts it into a x,y,z position
 */
Vec3f* OLib_VecGeoToVec3f(Vec3f* dest, VecGeo* geo) {
    VecSph sph;

    sph.r = geo->r;
    sph.pitch = 0x4000 - geo->pitch;
    sph.yaw = geo->yaw;

    return OLib_VecSphToVec3f(dest, &sph);
}

/**
 * Takes the point `vec`, and converts it into a spherical coordinate
 */
VecSph* OLib_Vec3fToVecSph(VecSph* dest, Vec3f* vec) {
    VecSph sph;
    f32 distXZSq = SQ(vec->x) + SQ(vec->z);
    f32 distXZ = sqrtf(distXZSq);

    if ((distXZ == 0.0f) && (vec->y == 0.0f)) {
        sph.pitch = 0;
    } else {
        sph.pitch = CAM_DEG_TO_BINANG(RAD_TO_DEG(func_80086B30(distXZ, vec->y)));
    }

    sph.r = sqrtf(SQ(vec->y) + distXZSq);
    if ((vec->x == 0.0f) && (vec->z == 0.0f)) {
        sph.yaw = 0;
    } else {
        sph.yaw = CAM_DEG_TO_BINANG(RAD_TO_DEG(func_80086B30(vec->x, vec->z)));
    }

    *dest = sph;

    return dest;
}

/**
 * Takes the point `vec`, and converts it to a geographic coordinate
 */
VecGeo* OLib_Vec3fToVecGeo(VecGeo* dest, Vec3f* vec) {
    VecSph sph;

    OLib_Vec3fToVecSph(&sph, vec);
    sph.pitch = 0x4000 - sph.pitch;

    *dest = sph;

    return dest;
}

/**
 * Takes the differences of positions `a` and `b`, and converts them to spherical coordinates
 */
VecSph* OLib_Vec3fDiffToVecSph(VecSph* dest, Vec3f* a, Vec3f* b) {
    Vec3f diff;

    diff.x = b->x - a->x;
    diff.y = b->y - a->y;
    diff.z = b->z - a->z;

    return OLib_Vec3fToVecSph(dest, &diff);
}

/**
 * Takes the difference of positions `a` and `b`, and converts them to geographic coordinates
 */
VecGeo* OLib_Vec3fDiffToVecGeo(VecGeo* dest, Vec3f* a, Vec3f* b) {
    Vec3f diff;

    diff.x = b->x - a->x;
    diff.y = b->y - a->y;
    diff.z = b->z - a->z;

    return OLib_Vec3fToVecGeo(dest, &diff);
}

/**
 * Takes the sum of positions `a` (x,y,z coordinates) and `geo` (geographic coordinates), result is in x,y,z position
 * Identical to Quake_AddVec from OoT
 */
Vec3f* OLib_AddVecGeoToVec3f(Vec3f* dest, Vec3f* a, VecGeo* geo) {
    Vec3f sum;
    Vec3f b;

    OLib_VecGeoToVec3f(&b, geo);
    sum.x = a->x + b.x;
    sum.y = a->y + b.y;
    sum.z = a->z + b.z;

    *dest = sum;

    return dest;
}

/**
 * Gets the pitch/yaw of the vector formed from `b`-`a`, result is in radians
 */
Vec3f* OLib_Vec3fDiffRad(Vec3f* dest, Vec3f* a, Vec3f* b) {
    Vec3f anglesRad;

    anglesRad.x = func_80086B30(b->z - a->z, b->y - a->y);
    anglesRad.y = func_80086B30(b->x - a->x, b->z - a->z);
    anglesRad.z = 0;

    *dest = anglesRad;

    return dest;
}

/**
 * Gets the pitch/yaw of the vector formed from `b`-`a`, result is in degrees
 */
Vec3f* OLib_Vec3fDiffDegF(Vec3f* dest, Vec3f* a, Vec3f* b) {
    Vec3f anglesRad;
    Vec3f anglesDegrees;

    OLib_Vec3fDiffRad(&anglesRad, a, b);

    anglesDegrees.x = RAD_TO_DEG(anglesRad.x);
    anglesDegrees.y = RAD_TO_DEG(anglesRad.y);
    anglesDegrees.z = 0.0f;

    *dest = anglesDegrees;

    return dest;
}

/**
 * Gets the pitch/yaw of the vector formed from `b`-`a`, result is in binary degrees
 */
Vec3s* OLib_Vec3fDiffBinAng(Vec3s* dest, Vec3f* a, Vec3f* b) {
    Vec3f anglesRad;
    Vec3s anglesBinAng;

    OLib_Vec3fDiffRad(&anglesRad, a, b);

    anglesBinAng.x = CAM_DEG_TO_BINANG(RAD_TO_DEG(anglesRad.x));
    anglesBinAng.y = CAM_DEG_TO_BINANG(RAD_TO_DEG(anglesRad.y));
    anglesBinAng.z = 0.0f;

    *dest = anglesBinAng;

    return dest;
}

/**
 * Gets a x,y,z position diff depending on the mode
 */
void OLib_Vec3fDiff(PosRot* a, Vec3f* b, Vec3f* dest, s16 mode) {
    VecGeo geo;

    switch (mode) {
        case OLIB_ADD_OFFSET:
            OLib_Vec3fDiffToVecGeo(&geo, &a->pos, b);
            geo.yaw -= a->rot.y;
            OLib_VecGeoToVec3f(dest, &geo);
            break;

        case OLIB_ADD:
            dest->x = b->x - a->pos.x;
            dest->y = b->y - a->pos.y;
            dest->z = b->z - a->pos.z;
            break;

        default: // OLIB_COPY
            *dest = *b;
            break;
    }
}

/**
 * Gets a x,y,z position sum depending on the mode
 */
void OLib_Vec3fAdd(PosRot* a, Vec3f* b, Vec3f* dest, s16 mode) {
    VecGeo geo;

    switch (mode) {
        case 1:
            OLib_Vec3fToVecGeo(&geo, b);
            geo.yaw += a->rot.y;
            OLib_AddVecGeoToVec3f(dest, &a->pos, &geo);
            break;

        case 2:
            dest->x = a->pos.x + b->x;
            dest->y = a->pos.y + b->y;
            dest->z = a->pos.z + b->z;
            break;

        default:
            *dest = *b;
            break;
    }
}
