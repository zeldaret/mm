#include <ultra64.h>
#include <global.h>

void* Lib_bcopy(void* dest, void* src, size_t n) {
    bcopy(src, dest, n);

    return dest;
}

s32* Lib_MemSet(s32* buffer, s32 value, s32 size) {
    u8* v0;
    s32 i;

    if (value == 0) {
        bzero((void*)buffer, (u32)size);

        return buffer;
    }

    for (v0 = buffer, i = size; i > 0; i--) {
        *v0++ = value;
    }

    return buffer;
}

f32 Math_CosS(s16 angle) {
    return coss(angle) * D_801DDA80;
}

f32 Math_SinS(s16 angle) {
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

s32 Lib_StepTowardsCheck_f(f32* start, f32 target, f32 step) {
    if (step != 0.0f) {
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

s32 func_800FF0D0(s16* a0, s16 a1, s16 a2) {
    s16 v0 = *a0;

    *a0 += a2;

    if (((s16)(*a0 - a1) * (s16)(v0 - a1)) <= 0) {
        *a0 = a1;

        return 1;
    }

    return 0;
}

s32 func_800FF138(s16* pValue, s16 target, s16 step) {
    s32 diff = target - *pValue;

    if (diff < 0) {
        step = -step;
    }

    if (diff >= 0x8000) {
        step = -step;
        diff = -0xFFFF - -diff;
    } else if (diff <= -0x8000) {
        diff += 0xFFFF;
        step = -step;
    }

    if (step != 0) {
        *pValue += step;

        if ((diff * step) <= 0) {
            *pValue = target;
            return 1;
        }
    } else if (target == *pValue) {
        return 1;
    }

    return 0;
}

s32 func_800FF1FC(s16* a0, s16 a1, s16 a2, s16 a3) {
    s16 phi_v1;

    phi_v1 = ((a1 - *a0) >= 0) ? a2 : a3;
    if (phi_v1 != 0) {
        if (a1 < *a0) {
            phi_v1 = -phi_v1;
        }
        *a0 += phi_v1;
        if (((*a0 - a1) * phi_v1) >= 0) {
            *a0 = a1;
            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }
    return 0;
}

s32 func_800FF2A8(f32* pValue, f32 limit, f32 step) {
    f32 orig = *pValue;

    *pValue += step;

    if (((*pValue - limit) * (orig - limit)) <= 0) {
        *pValue = limit;
        return 1;
    }

    return 0;
}

s32 func_800FF2F8(f32* pValue, f32 target, f32 incrStep, f32 decrStep) {
    f32 step = (target >= *pValue) ? incrStep : decrStep;

    if (step != 0) {
        if (target < *pValue) {
            step = -step;
        }

        *pValue += step;

        if (((*pValue - target) * step) >= 0) {
            *pValue = target;
            return 1;
        }
    } else if (target == *pValue) {
        return 1;
    }

    return 0;
}

void func_800FF3A0(f32* arg0, s16* arg1, Input* input) {
    f32 x = input->rel.stick_x;
    f32 y = input->rel.stick_y;
    f32 dist;

    dist = sqrtf(SQ(x) + SQ(y));
    *arg0 = (60.0f < dist) ? 60.0f : dist;

    if (dist > 0.0f) {
        x = input->cur.stick_x;
        y = input->cur.stick_y;
        *arg1 = atans_flip(y, -x);
    } else {
        *arg1 = 0;
    }
}

s16 Rand_S16Offset(s16 base, s16 range) {
    return (s16)(Rand_ZeroOne() * range) + base;
}

s16 Math_Rand_S16OffsetStride(s16 base, s16 stride, s16 range) {
    return (s16)(Rand_ZeroOne() * range) * stride + base;
}

void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src) {
    s16 x = src->x;
    s16 y = src->y;
    s16 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3f_ToVec3s(Vec3s* dest, Vec3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dest->x = x;
    dest->y = y;
    dest->z = z;
}

void Math_Vec3f_Sum(Vec3f* l, Vec3f* r, Vec3f* dest) {
    dest->x = l->x + r->x;
    dest->y = l->y + r->y;
    dest->z = l->z + r->z;
}

void Math_Vec3f_Diff(Vec3f* l, Vec3f* r, Vec3f* dest) {
    dest->x = l->x - r->x;
    dest->y = l->y - r->y;
    dest->z = l->z - r->z;
}

void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* l, Vec3s* r) {
    dest->x = l->x - r->x;
    dest->y = l->y - r->y;
    dest->z = l->z - r->z;
}

void Math_Vec3f_Scale(Vec3f* vec, f32 scale) {
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
}

void Math_Vec3f_ScaleAndStore(Vec3f* vec, f32 scale, Vec3f* dest) {
    dest->x = vec->x * scale;
    dest->y = vec->y * scale;
    dest->z = vec->z * scale;
}

void Math_Vec3f_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dest) {
    dest->x = (b->x - a->x) * t + a->x;
    dest->y = (b->y - a->y) * t + a->y;
    dest->z = (b->z - a->z) * t + a->z;
}

void Math_Vec3f_SumScaled(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest) {
    dest->x = b->x * scale + a->x;
    dest->y = b->y * scale + a->y;
    dest->z = b->z * scale + a->z;
}

void Math_Vec3f_ModifyRand(Vec3f* orig, f32 scale, Vec3f* dest) {
    dest->x = randPlusMinusPoint5Scaled(scale) + orig->x;
    dest->y = randPlusMinusPoint5Scaled(scale) + orig->y;
    dest->z = randPlusMinusPoint5Scaled(scale) + orig->z;
}

void Math_Vec3f_DistXYZAndStoreNormalizedDiff(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest) {
    f32 f0 = Math_Vec3f_DistXYZAndStoreDiff(a, b, dest);
    f32 f2;

    if (f0 == 0) {
        return;
    }

    f2 = scale / f0;

    dest->x *= f2;
    dest->y *= f2;
    dest->z *= f2;
}

f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b) {
    Vec3f sp1C;
    Math_Vec3f_Diff(b, a, &sp1C);
    return sqrtf((sp1C.x * sp1C.x) + (sp1C.y * sp1C.y) + (sp1C.z * sp1C.z));
}

f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* difference) {
    Math_Vec3f_Diff(b, a, difference);
    return sqrtf((difference->x * difference->x) + (difference->y * difference->y) + (difference->z * difference->z));
}

f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b) {
    f32 dx = b->x - a->x;
    f32 dz = b->z - a->z;
    return sqrtf((dx * dx) + (dz * dz));
}

f32 Math_Vec3f_DistXZAndStore(Vec3f* a, Vec3f* b, f32* xDiff, f32* zDiff) {
    *xDiff = b->x - a->x;
    *zDiff = b->z - a->z;
    return sqrtf((*xDiff * *xDiff) + (*zDiff * *zDiff));
}

f32 Math_Vec3f_PushAwayXZ(Vec3f* start, Vec3f* pusher, f32 distanceToApproach) {
    f32 sp24;
    f32 sp20;
    f32 f0 = Math_Vec3f_DistXZAndStore(pusher, start, &sp24, &sp20);
    f32 f2 = f0 - distanceToApproach;

    if (distanceToApproach > f0) {
        f2 = 0.0f;
    }

    if (f2 == 0.0f) {
        f0 = 0.0f;
    } else {
        f0 = f2 / f0;
    }

    start->x = pusher->x + sp24 * f0;
    start->z = pusher->z + sp20 * f0;

    return f2;
}

f32 Math_Vec3f_DiffY(Vec3f* a, Vec3f* b) {
    return b->y - a->y;
}

s16 Math_Vec3f_Yaw(Vec3f* from, Vec3f* to) {
    f32 f14 = to->x - from->x;
    f32 f12 = to->z - from->z;
    return Math_FAtan2F(f12, f14);
}

s16 Math_Vec3f_Pitch(Vec3f* from, Vec3f* to) {
    return Math_FAtan2F(Math_Vec3f_DistXZ(from, to), from->y - to->y);
}

void Actor_ProcessInitChain(Actor* actor, InitChainEntry* init) {
    do {
        actorInitVarFuncs[init->type]((u8*)actor, init);
    } while ((init++)->cont);
}

void IChain_Apply_u8(u8* actor, InitChainEntry* init) {
    *(u8*)(actor + init->offset) = (u8)(init->value);
}

void IChain_Apply_s8(u8* actor, InitChainEntry* init) {
    *(u8*)(actor + init->offset) = (u8)(init->value);
}

void IChain_Apply_u16(u8* actor, InitChainEntry* init) {
    *(u16*)(actor + init->offset) = (u16)(init->value);
}

void IChain_Apply_s16(u8* actor, InitChainEntry* init) {
    *(u16*)(actor + init->offset) = (u16)(init->value);
}

void IChain_Apply_u32(u8* actor, InitChainEntry* init) {
    *(u32*)(actor + init->offset) = (u32)(init->value);
}

void IChain_Apply_s32(u8* actor, InitChainEntry* init) {
    *(u32*)(actor + init->offset) = (u32)(init->value);
}

void IChain_Apply_f32(u8* actor, InitChainEntry* init) {
    *(f32*)(actor + init->offset) = (f32)(init->value);
}

void IChain_Apply_f32div1000(u8* actor, InitChainEntry* init) {
    *(f32*)(actor + init->offset) = (f32)(init->value) / 1000;
}

void IChain_Apply_Vec3f(u8* actor, InitChainEntry* init) {
    Vec3f* v0 = (Vec3f*)(actor + init->offset);
    f32 f0 = (f32)(init->value);

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

void IChain_Apply_Vec3fdiv1000(u8* actor, InitChainEntry* init) {
    Vec3f* v0 = (Vec3f*)(actor + init->offset);
    f32 f0 = (f32)(init->value) / 1000;

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

void IChain_Apply_Vec3s(u8* actor, InitChainEntry* init) {
    Vec3s* v0 = (Vec3s*)(actor + init->offset);
    s16 v1 = (s16)(init->value);

    v0->z = v1;
    v0->y = v1;
    v0->x = v1;
}

f32 Math_SmoothScaleMaxMinF(f32* a0, f32 a1, f32 a2, f32 a3, f32 a4) {
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

void Math_SmoothScaleMaxF(f32* start, f32 target, f32 scale, f32 maxStep) {
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

void Math_SmoothDownscaleMaxF(f32* start, f32 scale, f32 maxStep) {
  f32 f0 = *start * scale;

  if (maxStep < f0) {
    f0 = maxStep;
  } else if (f0 < -maxStep) {
    f0 = -maxStep;
  }

  *start = *start - f0;
}

s32 Math_SmoothScaleMaxMinS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep) {
    s16 stepSize = 0;
    s16 diff = target - *pValue;

    if (*pValue != target) {
        stepSize = diff / scale;

        if ((stepSize > minStep) || (stepSize < -minStep)) {
            if (stepSize > step) {
                stepSize = step;
            }

            if (stepSize < -step) {
                stepSize = -step;
            }

            *pValue += stepSize;
        } else {
            if (diff >= 0) {
                *pValue += minStep;

                if ((s16)(target - *pValue) <= 0) {
                    *pValue = target;
                }
            } else {
                *pValue -= minStep;

                if ((s16)(target - *pValue) >= 0) {
                    *pValue = target;
                }
            }
        }
    }

    return diff;
}

void Math_SmoothScaleMaxS(s16* start, s16 target, s16 scale, s16 maxStep) {
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

void Color_RGBA8_Copy(Color_RGBA8* dst, Color_RGBA8* src) {
    dst->r = src->r;
    dst->g = src->g;
    dst->b = src->b;
    dst->a = src->a;
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

void Lib_TranslateAndRotateYVec3f(Vec3f* translation, s16 rotation, Vec3f* src, Vec3f* dst) {
    f32 sp1C;
    f32 f0;

    sp1C = Math_CosS(rotation);
    f0 = Math_SinS(rotation);
    dst->x = translation->x + (src->x * sp1C + src->z * f0);
    dst->y = translation->y + src->y;
    dst->z = translation->z + (src->z * sp1C - src->x * f0);
}

void Lib_LerpRGB(Color_RGB8* a, Color_RGB8* b, f32 t, Color_RGB8* dst) {
    f32 aF;

    aF = a->r;
    dst->r = aF + (b->r - aF) * t;
    aF = a->g;
    dst->g = aF + (b->g - aF) * t;
    aF = a->b;
    dst->b = aF + (b->b - aF) * t;
}

f32 Lib_PushAwayVec3f(Vec3f* start, Vec3f* pusher, f32 distanceToApproach) {
    Vec3f sp24;
    f32 f2;
    f32 f0;

    Math_Vec3f_Diff(pusher, start, &sp24);
    f0 = Math3D_Vec3fMagnitude(&sp24);
    if (distanceToApproach < f0) {
        f2 = distanceToApproach / f0;
        f0 = f0 - distanceToApproach;
        start->x = start->x + f2 * sp24.x;
        start->y = start->y + f2 * sp24.y;
        start->z = start->z + f2 * sp24.z;
    } else {
        Math_Vec3f_Copy(start, pusher);
        f0 = 0;
    }

    return f0;
}

void Lib_Nop801004FC(void) {}

void* Lib_PtrSegToVirt(void* ptr) {
    return SEGMENTED_TO_VIRTUAL(ptr);
}

void* Lib_PtrSegToVirtNull(void* ptr) {
    // UB: to cast the pointer to u32 in order to bitshift.
    if (((u32)ptr >> 28) == 0) {
        return ptr;
    }

    return SEGMENTED_TO_VIRTUAL(ptr);
}

void* Lib_PtrSegToK0(void* ptr) {
    if (ptr == NULL) {
        return NULL;
    } else {
        return (void*)PHYSICAL_TO_VIRTUAL(ptr);
    }
}

void* Lib_PtrSegToK0Null(void* ptr) {
    if (ptr == NULL) {
        return NULL;
    } else {
        return (void*)PHYSICAL_TO_VIRTUAL(ptr);
    }
}
