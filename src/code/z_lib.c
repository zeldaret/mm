#include <ultra64.h>
#include <global.h>

#pragma intrinsic (sqrtf)
extern float fabsf(float);
#pragma intrinsic (fabsf)

void* Lib_bcopy(void* dest, void* src, size_t n) {
    _bcopy(src, dest, n);

    return dest;
}

#ifdef NONMATCHING

void* Lib_memset(u8* a0, u32 a1, u32 a2) {
    u8* v0;

    // XXX: realloc is messed up
    if (a1 == 0) {
        _blkclr((void*)a0, (u32)a2);

        return a0;
    }

    for (v0 = a0; a2 != 0; a2--) {
        *v0++ = a1;
    }

    return a0;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_memset.asm")

#endif

f32 Lib_cos(s16 angle) {
    return coss(angle) * D_801DDA80;
}

f32 Lib_sin(s16 angle) {
    return sins(angle) * D_801DDA84;
}

s32 Lib_StepTowardsGet_i(s32 start, s32 value, s32 step) {
    s32 v1;

    if (value >= start) {
        v1 = start + step;
        if (value >= v1) {
            return v1;
        }
    } else {
        v1 = start - step;
        if (v1 >= value) {
            return v1;
        }
    }
    return value;
}

void Lib_StepTowards_i(s32* start, s32 value, s32 step) {
    *start = Lib_StepTowardsGet_i(*start, value, step);
}

s32 Lib_StepTowardsCheck_i(s32* start, s32 value, s32 step) {
    Lib_StepTowards_i(start, value, step);

    return value == *start;
}

s32 Lib_StepTowardsCheckFramerateScaled_s(s16* start, s16 target, s16 step) {
    f32 f0;

    if (step != 0) {
        f0 = gFramerateDivisorHalf;

        if ((s16)(*start - target) > 0) {
            step = -step;
        }

        *start += (s16)(step * f0);

        if (((s16)(*start - target) * step) >= 0) {
            *start = target;

            return 1;
        }
    } else if (target == *start) {
        return 1;
    }

    return 0;
}

s32 Lib_StepTowardsCheck_s(s16* start, s16 target, s16 step) {
    if (step != 0) {
        if (target < *start) {
            step = -step;
        }

        *start += step;

        if (((*start - target) * step) >= 0) {
            *start = target;

            return 1;
        }
    } else if (target == *start) {
        return 1;
    }

    return 0;
}

s32 Lib_StepTowardsCheck_c(s8* start, s8 target, s8 step) {
    if (step != 0) {
        if (target < *start) {
            step = -step;
        }

        *start += step;

        if (((*start - target) * step) >= 0) {
            *start = target;

            return 1;
        }
    } else if (target == *start) {
        return 1;
    }

    return 0;
}

#ifdef NONMATCHING

s32 Lib_StepTowardsCheck_f(f32* start, f32 target, f32 step) {
    if (step != 0) {
        // XXX: regalloc is messed up
        if (target < *start) {
            step = -step;
        }

        *start += step;

        if (((*start - target) * step) >= 0) {
            *start = target;

            return 1;
        }
    } else if (target != *start) {
        return 1;
    }

    return 0;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_StepTowardsCheck_f.asm")

#endif

#ifdef NONMATCHING

s32 func_800FF0D0(s16* a0, s16 a1, s16 a2) {
    s32 v0 = *a0;

    // XXX: regalloc is messed up
    *a0 += a2;

    if (((*a0 - a1) * (v0 - a1)) <= 0) {
        *a0 = a1;

        return 1;
    }

    return 0;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF0D0.asm")

#endif

#ifdef NONMATCHING

void func_800FF138() {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF138.asm")

#endif

#ifdef NONMATCHING

void func_800FF1FC(void) {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF1FC.asm")

#endif

#ifdef NONMATCHING

void func_800FF2A8(void) {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF2A8.asm")

#endif

#ifdef NONMATCHING

void func_800FF2F8(void) {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF2F8.asm")

#endif

#ifdef NONMATCHING

void func_800FF3A0(void) {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF3A0.asm")

#endif

s16 Lib_rand_s(s16 base, s16 range) {
    return (s16)(randZeroOne() * range) + base;
}

s16 Lib_randestride_s(s16 base, s16 stride, s16 range) {
    return (s16)(randZeroOne() * range) * stride + base;
}

void Lib_CopyVec3f(Vector3f* dest, Vector3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Lib_CopyVec3s(Vector3s* dest, Vector3s* src) {
    s16 x = src->x;
    s16 y = src->y;
    s16 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Lib_ToVec3f(Vector3f* dest, Vector3s* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Lib_ToVec3s(Vector3s* dest, Vector3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Lib_AddVec3f(Vector3f* l, Vector3f* r, Vector3f* dest) {
    dest->x = l->x + r->x;
    dest->y = l->y + r->y;
    dest->z = l->z + r->z;
}

void Lib_SubVec3f(Vector3f* l, Vector3f* r, Vector3f* dest) {
    dest->x = l->x - r->x;
    dest->y = l->y - r->y;
    dest->z = l->z - r->z;
}

void Lib_SubVec3sToVec3f(Vector3f* dest, Vector3s* l, Vector3s* r) {
    dest->x = l->x - r->x;
    dest->y = l->y - r->y;
    dest->z = l->z - r->z;
}

void Lib_ScaleInPlaceVec3f(Vector3f* vec, f32 scale) {
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
}

void Lib_ScaleVec3f(Vector3f* vec, f32 scale, Vector3f* dest) {
    dest->x = vec->x * scale;
    dest->y = vec->y * scale;
    dest->z = vec->z * scale;
}

void Lib_LerpVec3f(Vector3f* a, Vector3f* b, f32 t, Vector3f* dest) {
    dest->x = (b->x - a->x) * t + a->x;
    dest->y = (b->y - a->y) * t + a->y;
    dest->z = (b->z - a->z) * t + a->z;
}

void Lib_AddScaledVec3f(Vector3f* a, Vector3f* b, f32 scale, Vector3f* dest) {
    dest->x = b->x * scale + a->x;
    dest->y = b->y * scale + a->y;
    dest->z = b->z * scale + a->z;
}

void Lib_ModifyRandScaled(Vector3f* orig, f32 scale, Vector3f* dest) {
    dest->x = randPlusMinusPoint5Scaled(scale) + orig->x;
    dest->y = randPlusMinusPoint5Scaled(scale) + orig->y;
    dest->z = randPlusMinusPoint5Scaled(scale) + orig->z;
}

void Lib_ScaledNormalizedDifferenceVec3f(Vector3f* a, Vector3f* b, f32 scale, Vector3f* dest) {
    f32 f0 = Lib_DistanceAndDifferenceVec3f(a, b, dest);
    f32 f2;

    if (f0 == 0) {
        return;
    }

    f2 = scale / f0;

    dest->x *= f2;
    dest->y *= f2;
    dest->z *= f2;
}

f32 Lib_DistanceVec3f(Vector3f* a, Vector3f* b) {
    Vector3f sp1C;
    Lib_SubVec3f(b, a, &sp1C);
    return sqrtf((sp1C.x * sp1C.x) + (sp1C.y * sp1C.y) + (sp1C.z * sp1C.z));
}

f32 Lib_DistanceAndDifferenceVec3f(Vector3f* a, Vector3f* b, Vector3f* difference) {
    Lib_SubVec3f(b, a, difference);
    return sqrtf((difference->x * difference->x) + (difference->y * difference->y) + (difference->z * difference->z));
}

f32 Lib_DistanceXZVec3f(Vector3f* a, Vector3f* b) {
    f32 dx = b->x - a->x;
    f32 dz = b->z - a->z;
    return sqrtf((dx * dx) + (dz * dz));
}

f32 Lib_DistanceAndDifferenceXZVec3f(Vector3f* a, Vector3f* b, f32* xDiff, f32* zDiff) {
    *xDiff = b->x - a->x;
    *zDiff = b->z - a->z;
    return sqrtf((*xDiff * *xDiff) + (*zDiff * *zDiff));
}

#ifdef NONMATCHING

void Lib_PushAwayXZVec3f(Vector3f* start, Vector3f* pusher, f32 distanceToApproach) {
    f32 sp24;
    f32 sp20;
    f32 f0 = Lib_DistanceAndDifferenceXZVec3f(pusher, start, &sp24, &sp20);
    f32 f2 = f0 - distanceToApproach;

    if ((f0 >= distanceToApproach) && (f2 != 0)) {
        f2 /= f0;
    } else {
        f2 = 0;
    }

    start->x = pusher->x + sp24 * f2;
    start->z = pusher->z + sp20 * f2;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_PushAwayXZVec3f.asm")

#endif

f32 Lib_DistanceYVec3f(Vector3f* a, Vector3f* b) {
    return b->y - a->y;
}

s16 Lib_YawVec3f(Vector3f* from, Vector3f* to) {
    f32 f14 = to->x - from->x;
    f32 f12 = to->z - from->z;
    return atans_flip(f12, f14);
}

s16 Lib_PitchVec3f(Vector3f* from, Vector3f* to) {
    return atans_flip(Lib_DistanceXZVec3f(from, to), from->y - to->y);
}

void Lib_ApplyActorInitVars(Actor* actor, ActorInitVar* init) {
    do {
        actorInitVarFuncs[init->type]((u8*)actor, init);
    } while ((init++)->cont);
}

void Lib_ApplyActorInitVarByte1(u8* actor, ActorInitVar* init) {
    *(u8*)(actor + init->offset) = (u8)(init->value);
}

void Lib_ApplyActorInitVarByte2(u8* actor, ActorInitVar* init) {
    *(u8*)(actor + init->offset) = (u8)(init->value);
}

void Lib_ApplyActorInitVarShort1(u8* actor, ActorInitVar* init) {
    *(u16*)(actor + init->offset) = (u16)(init->value);
}

void Lib_ApplyActorInitVarShort2(u8* actor, ActorInitVar* init) {
    *(u16*)(actor + init->offset) = (u16)(init->value);
}

void Lib_ApplyActorInitVarWord1(u8* actor, ActorInitVar* init) {
    *(u32*)(actor + init->offset) = (u32)(init->value);
}

void Lib_ApplyActorInitVarWord2(u8* actor, ActorInitVar* init) {
    *(u32*)(actor + init->offset) = (u32)(init->value);
}

void Lib_ApplyActorInitVarFloat(u8* actor, ActorInitVar* init) {
    *(f32*)(actor + init->offset) = (f32)(init->value);
}

void Lib_ApplyActorInitVarFloat1000th(u8* actor, ActorInitVar* init) {
    *(f32*)(actor + init->offset) = (f32)(init->value) / 1000;
}

void Lib_ApplyActorInitVarVector3f(u8* actor, ActorInitVar* init) {
    Vector3f* v0 = (Vector3f*)(actor + init->offset);
    f32 f0 = (f32)(init->value);

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

void Lib_ApplyActorInitVarVector3f1000th(u8* actor, ActorInitVar* init) {
    Vector3f* v0 = (Vector3f*)(actor + init->offset);
    f32 f0 = (f32)(init->value) / 1000;

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

void Lib_ApplyActorInitVarVector3s(u8* actor, ActorInitVar* init) {
    Vector3s* v0 = (Vector3s*)(actor + init->offset);
    s16 v1 = (s16)(init->value);

    v0->z = v1;
    v0->y = v1;
    v0->x = v1;
}

f32 func_800FFCD8(f32* a0, f32 a1, f32 a2, f32 a3, f32 a4) {
    f32 f0;

    if (*a0 != a1) {
        f0 = (a1 - *a0) * a2;

        if ((f0 >= a4) || (f0 <= -a4)) {
            if (f0 > a3) {
                f0 = a3;
            }

            if (f0 < -a3) {
                f0 = -a3;
            }

            *a0 += f0;
        } else {
            if (f0 > 0) {
                if (f0 < a4) {
                    *a0 += a4;

                    if (a1 < *a0) {
                        *a0 = a1;
                    }
                }
            } else {
                if (-a4 < f0) {
                    *a0 += -a4;

                    if (*a0 < a1) {
                        *a0 = a1;
                    }
                }
            }
        }
    }

    return fabsf(a1 - *a0);
}

void Lib_ScaleMax_f(f32* start, f32 target, f32 scale, f32 maxStep) {
    f32 f2;

    if (*start != target) {
        f2 = (target - *start) * scale;

        if (f2 > maxStep) {
            f2 = maxStep;
        } else if (f2 < -maxStep) {
            f2 = -maxStep;
        }

        *start += f2;
    }
}

void Lib_Scale_f(f32* start, f32 scale, f32 maxStep) {
  f32 f0 = *start * scale;

  if (maxStep < f0) {
    f0 = maxStep;
  } else if (f0 < -maxStep) {
    f0 = -maxStep;
  }

  *start = *start - f0;
}

#ifdef NONMATCHING

s32 Lib_ScaleMaxMin_s(s16* start, s16 target, s16 scale, s16 maxStep, s16 minStep) {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_ScaleMaxMin_s.asm")

#endif

void Lib_ScaleMax_s(s16* start, s16 target, s16 scale, s16 maxStep) {
    s16 v0 = target - *start;
    v0 /= scale;

    if (v0 > maxStep) {
        *start += maxStep;
        return;
    }

    if (v0 < -maxStep) {
        *start -= maxStep;
        return;
    }

    *start += v0;
}

void Lib_CopyColor(ColorRGBA8* dst, ColorRGBA8* src) {
    dst->red = src->red;
    dst->green = src->green;
    dst->blue = src->blue;
    dst->alpha = src->alpha;
}

void func_801000A4(u16 a0) {
    play_sound(a0);
}

void func_801000CC(u16 a0) {
    func_8019F128(a0);
}

void func_801000F4(s32 a0, u16 a1) {
    func_8019F1C0(a0, a1);
}

void Lib_TranslateAndRotateYVec3f(Vector3f* translation, s16 rotation, Vector3f* src, Vector3f* dst) {
    f32 sp1C;
    f32 f0;

    sp1C = Lib_cos(rotation);
    f0 = Lib_sin(rotation);
    dst->x = translation->x + (src->x * sp1C + src->z * f0);
    dst->y = translation->y + src->y;
    dst->z = translation->z + (src->z * sp1C - src->x * f0);
}

#ifdef NONMATCHING

void Lib_LerpRGB(RGB* a, RGB* b, f32 t, RGB* dst) {
    // XXX regalloc is slightly off
    dst->red = (f32)a->red + ((f32)b->red - (f32)a->red) * t;
    dst->green = (f32)a->green + ((f32)b->green - (f32)a->green) * t;
    dst->blue = (f32)a->blue + ((f32)b->blue - (f32)a->blue) * t;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_LerpRGB.asm")

#endif

f32 Lib_PushAwayVec3f(Vector3f* start, Vector3f* pusher, f32 distanceToApproach) {
    Vector3f sp24;
    f32 f2;
    f32 f0;

    Lib_SubVec3f(pusher, start, &sp24);
    f0 = Math3D_Length(&sp24);
    if (distanceToApproach < f0) {
        f2 = distanceToApproach / f0;
        f0 = f0 - distanceToApproach;
        start->x = start->x + f2 * sp24.x;
        start->y = start->y + f2 * sp24.y;
        start->z = start->z + f2 * sp24.z;
    } else {
        Lib_CopyVec3f(start, pusher);
        f0 = 0;
    }

    return f0;
}

void Lib_Nop801004FC(void) {}

u32 Lib_PtrSegToVirt(void* ptr) {
    return(gRspSegmentPhysAddrs[((u32)ptr << 4) >> 28] + ((u32)ptr & 0xFFFFFF)) + 0x80000000;
}

u32 Lib_PtrSegToVirtNull(void* ptr) {
    if (((u32)ptr >> 28) == 0) {
        return (u32)ptr;
    }

    return(gRspSegmentPhysAddrs[((u32)ptr << 4) >> 28] + ((u32)ptr & 0xFFFFFF)) + 0x80000000;
}

u32 Lib_PtrSegToK0(void* ptr) {
    if (ptr == NULL) {
        return 0;
    } else {
        return (u32)ptr + 0x80000000;
    }
}

u32 Lib_PtrSegToK0Null(void* ptr) {
    if (ptr == NULL) {
        return 0;
    } else {
        return (u32)ptr + 0x80000000;
    }
}