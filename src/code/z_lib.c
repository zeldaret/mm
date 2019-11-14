#include <ultra64.h>
#include <global.h>

#pragma intrinsic (sqrtf)
extern float fabsf(float);
#pragma intrinsic (fabsf)

void* Lib_bcopy(void* dst, void* src, size_t n) {
    _bcopy(src, dst, n);

    return dst;
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

f32 Lib_cos(s16 a0) {
    return coss(a0) * D_801DDA80;
}

f32 Lib_sin(s16 a0) {
    return sins(a0) * D_801DDA84;
}

s32 Lib_StepTowardsGet_i(s32 a0, s32 a1, s32 a2) {
    s32 v1;

    if (a1 >= a0) {
        v1 = a0 + a2;
        if (a1 >= v1) {
            return v1;
        }
    } else {
        v1 = a0 - a2;
        if (v1 >= a1) {
            return v1;
        }
    }
    return a1;
}

UNK_RET Lib_StepTowards_i(u32* a0, u32 a1, u32 a2) {
    *a0 = Lib_StepTowardsGet_i(*a0, a1, a2);
}

UNK_TYPE Lib_StepTowardsCheck_i(u32* a0, u32 a1, u32 a2) {
    Lib_StepTowards_i(a0, a1, a2);

    return a1 == *a0;
}

UNK_TYPE Lib_StepTowardsCheckFramerateScaled_s(s16* a0, s16 a1, s16 a2) {
    f32 f0;

    if (a2 != 0) {
        f0 = D_801D1508;

        if ((s16)(*a0 - a1) > 0) {
            a2 = -a2;
        }

        *a0 += (s16)(a2 * f0);

        if (((s16)(*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }

    return 0;
}

UNK_TYPE Lib_StepTowardsCheck_s(s16* a0, s16 a1, s16 a2) {
    if (a2 != 0) {
        if (a1 < *a0) {
            a2 = -a2;
        }

        *a0 += a2;

        if (((*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }

    return 0;
}

UNK_TYPE Lib_StepTowardsCheck_c(s8* a0, s8 a1, s8 a2) {
    if (a2 != 0) {
        if (a1 < *a0) {
            a2 = -a2;
        }

        *a0 += a2;

        if (((*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 == *a0) {
        return 1;
    }

    return 0;
}

#ifdef NONMATCHING

UNK_TYPE Lib_StepTowardsCheck_f(f32* a0, f32 a1, f32 a2) {
    if (a2 != 0) {
        // XXX: regalloc is messed up
        if (a1 < *a0) {
            a2 = -a2;
        }

        *a0 += a2;

        if (((*a0 - a1) * a2) >= 0) {
            *a0 = a1;

            return 1;
        }
    } else if (a1 != *a0) {
        return 1;
    }

    return 0;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_StepTowardsCheck_f.asm")

#endif

#ifdef NONMATCHING

UNK_TYPE func_800FF0D0(s16* a0, s16 a1, s16 a2) {
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

UNK_RET func_800FF138() {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF138.asm")

#endif

#ifdef NONMATCHING

UNK_RET func_800FF1FC() {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF1FC.asm")

#endif

#ifdef NONMATCHING

UNK_RET func_800FF2A8() {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF2A8.asm")

#endif

#ifdef NONMATCHING

UNK_RET func_800FF2F8() {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF2F8.asm")

#endif

#ifdef NONMATCHING

UNK_RET func_800FF3A0() {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/func_800FF3A0.asm")

#endif

s16 Lib_rand_s(s16 a0, s16 a1) {
    return (s16)(randZeroOne() * a1) + a0;
}

s16 Lib_randStride_s(s16 a0, s16 a1, s16 a2) {
    return (s16)(randZeroOne() * a2) * a1 + a0;
}

UNK_RET Lib_CopyVec3f(z_Vector3f* dst, z_Vector3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET Lib_CopyVec3s(z_Vector3s* dst, z_Vector3s* src) {
    s16 x = src->x;
    s16 y = src->y;
    s16 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET Lib_ToVec3f(z_Vector3f* dst, z_Vector3s* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET Lib_ToVec3s(z_Vector3s* dst, z_Vector3f* src) {
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

UNK_RET Lib_AddVec3f(z_Vector3f* a0, z_Vector3f* a1, z_Vector3f* a2) {
    a2->x = a0->x + a1->x;
    a2->y = a0->y + a1->y;
    a2->z = a0->z + a1->z;
}

UNK_RET Lib_SubVec3f(z_Vector3f* a0, z_Vector3f* a1, z_Vector3f* a2) {
    a2->x = a0->x - a1->x;
    a2->y = a0->y - a1->y;
    a2->z = a0->z - a1->z;
}

UNK_RET Lib_SubVec3sToVec3f(z_Vector3f* a0, z_Vector3s* a1, z_Vector3s* a2) {
    a0->x = a1->x - a2->x;
    a0->y = a1->y - a2->y;
    a0->z = a1->z - a2->z;
}

UNK_RET Lib_ScaleInPlaceVec3f(z_Vector3f* a0, f32 a1) {
    a0->x *= a1;
    a0->y *= a1;
    a0->z *= a1;
}

UNK_RET Lib_ScaleVec3f(z_Vector3f* a0, f32 a1, z_Vector3f* a2) {
    a2->x = a0->x * a1;
    a2->y = a0->y * a1;
    a2->z = a0->z * a1;
}

UNK_RET Lib_LerpVec3f(z_Vector3f* a0, z_Vector3f* a1, f32 a2, z_Vector3f* a3) {
    a3->x = (a1->x - a0->x) * a2 + a0->x;
    a3->y = (a1->y - a0->y) * a2 + a0->y;
    a3->z = (a1->z - a0->z) * a2 + a0->z;
}

UNK_RET Lib_AddScaledVec3f(z_Vector3f* a0, z_Vector3f* a1, f32 a2, z_Vector3f* a3) {
    a3->x = a1->x * a2 + a0->x;
    a3->y = a1->y * a2 + a0->y;
    a3->z = a1->z * a2 + a0->z;
}

UNK_RET Lib_ModifyRandScaled(z_Vector3f* a0, f32 a1, z_Vector3f* a2) {
    a2->x = randPlusMinusPoint5Scaled(a1) + a0->x;
    a2->y = randPlusMinusPoint5Scaled(a1) + a0->y;
    a2->z = randPlusMinusPoint5Scaled(a1) + a0->z;
}

void Lib_ScaledNormalizedDifferenceVec3f(z_Vector3f* a0, z_Vector3f* a1, f32 a2, z_Vector3f* a3) {
    f32 f0 = Lib_DistanceAndDifferenceVec3f(a0, a1, a3);
    f32 f2;

    if (f0 == 0) {
        return;
    }

    f2 = a2 / f0;

    a3->x *= f2;
    a3->y *= f2;
    a3->z *= f2;
}

f32 Lib_DistanceVec3f(z_Vector3f* a0, z_Vector3f* a1) {
    z_Vector3f sp1C;
    Lib_SubVec3f(a1, a0, &sp1C);
    return sqrtf((sp1C.x * sp1C.x) + (sp1C.y * sp1C.y) + (sp1C.z * sp1C.z));
}

f32 Lib_DistanceAndDifferenceVec3f(z_Vector3f* a0, z_Vector3f* a1, z_Vector3f* a2) {
    Lib_SubVec3f(a1, a0, a2);
    return sqrtf((a2->x * a2->x) + (a2->y * a2->y) + (a2->z * a2->z));
}

f32 Lib_DistanceXZVec3f(z_Vector3f* a0, z_Vector3f* a1) {
    f32 dx = a1->x - a0->x;
    f32 dz = a1->z - a0->z;
    return sqrtf((dx * dx) + (dz * dz));
}

f32 Lib_DistanceAndDifferenceXZVec3f(z_Vector3f* a0, z_Vector3f* a1, f32* a2, f32* a3) {
    *a2 = a1->x - a0->x;
    *a3 = a1->z - a0->z;
    return sqrtf((*a2 * *a2) + (*a3 * *a3));
}

#ifdef NONMATCHING

UNK_RET Lib_PushAwayXZVec3f(z_Vector3f* a0, z_Vector3f* a1, f32 a2) {
    f32 sp24;
    f32 sp20;
    f32 f0 = Lib_DistanceAndDifferenceXZVec3f(a1, a0, &sp24, &sp20);
    f32 f2 = f0 - a2;

    if ((f0 >= a2) && (f2 != 0)) {
        f2 /= f0;
    } else {
        f2 = 0;
    }

    a0->x = a1->x + sp24 * f2;
    a0->z = a1->z + sp20 * f2;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_PushAwayXZVec3f.asm")

#endif

f32 Lib_DistanceYVec3f(z_Vector3f* a0, z_Vector3f* a1) {
    return a1->y - a0->y;
}

UNK_TYPE Lib_YawVec3f(z_Vector3f* a0, z_Vector3f* a1) {
    f32 f14 = a1->x - a0->x;
    f32 f12 = a1->z - a0->z;
    return atans_flip(f12, f14);
}

UNK_TYPE Lib_PitchVec3f(z_Vector3f* a0, z_Vector3f* a1) {
    return atans_flip(Lib_DistanceXZVec3f(a0, a1), a0->y - a1->y);
}

void Lib_ApplyActorInitVars(z_Actor* a0, z_ActorInitVar* a1) {
    do {
        D_801BE960[a1->type]((u8*)a0, a1);
    } while ((a1++)->cont);
}

UNK_RET Lib_ApplyActorInitVarByte1(u8* a0, z_ActorInitVar* a1) {
    *(u8*)(a0 + a1->offset) = (u8)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarByte2(u8* a0, z_ActorInitVar* a1) {
    *(u8*)(a0 + a1->offset) = (u8)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarShort1(u8* a0, z_ActorInitVar* a1) {
    *(u16*)(a0 + a1->offset) = (u16)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarShort2(u8* a0, z_ActorInitVar* a1) {
    *(u16*)(a0 + a1->offset) = (u16)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarWord1(u8* a0, z_ActorInitVar* a1) {
    *(u32*)(a0 + a1->offset) = (u32)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarWord2(u8* a0, z_ActorInitVar* a1) {
    *(u32*)(a0 + a1->offset) = (u32)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarFloat(u8* a0, z_ActorInitVar* a1) {
    *(f32*)(a0 + a1->offset) = (f32)(a1->value);
}

UNK_RET Lib_ApplyActorInitVarFloat1000th(u8* a0, z_ActorInitVar* a1) {
    *(f32*)(a0 + a1->offset) = (f32)(a1->value) / 1000;
}

UNK_RET Lib_ApplyActorInitVarVector3f(u8* a0, z_ActorInitVar* a1) {
    z_Vector3f* v0 = (z_Vector3f*)(a0 + a1->offset);
    f32 f0 = (f32)(a1->value);

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

UNK_RET Lib_ApplyActorInitVarVector3f1000th(u8* a0, z_ActorInitVar* a1) {
    z_Vector3f* v0 = (z_Vector3f*)(a0 + a1->offset);
    f32 f0 = (f32)(a1->value) / 1000;

    v0->z = f0;
    v0->y = f0;
    v0->x = f0;
}

UNK_RET Lib_ApplyActorInitVarVector3s(u8* a0, z_ActorInitVar* a1) {
    z_Vector3s* v0 = (z_Vector3s*)(a0 + a1->offset);
    s16 v1 = (s16)(a1->value);

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

UNK_RET Lib_ScaleMax_f(f32* a0, f32 a1, f32 a2, f32 a3) {
    f32 f2;

    if (*a0 != a1) {
        f2 = (a1 - *a0) * a2;

        if (f2 > a3) {
            f2 = a3;
        } else if (f2 < -a3) {
            f2 = -a3;
        }

        *a0 += f2;
    }
}

void Lib_Scale_f(f32* a0, f32 a1, f32 a2) {
  f32 f0 = *a0 * a1;

  if (a2 < f0) {
    f0 = a2;
  } else if (f0 < -a2) {
    f0 = -a2;
  }

  *a0 = *a0 - f0;
}

#ifdef NONMATCHING

s16 Lib_ScaleMaxMin_s(s16* a0, s16 a1, s16 a2, s16 a3, s16 a4) {

}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_ScaleMaxMin_s.asm")

#endif

void Lib_ScaleMax_s(s16* a0, s16 a1, s16 a2, s16 a3) {
    s16 v0 = a1 - *a0;
    v0 /= a2;

    if (v0 > a3) {
        *a0 += a3;
        return;
    }

    if (v0 < -a3) {
        *a0 -= a3;
        return;
    }

    *a0 += v0;
}

UNK_RET Lib_CopyColor(u8* a0, u8* a1) {
    a0[0] = a1[0];
    a0[1] = a1[1];
    a0[2] = a1[2];
    a0[3] = a1[3];
}

UNK_RET func_801000A4(u16 a0) {
    func_8019F0C8(a0);
}

UNK_RET func_801000CC(u16 a0) {
    func_8019F128(a0);
}

UNK_RET func_801000F4(UNK_TYPE a0, u16 a1) {
    func_8019F1C0(a0, a1);
}

void Lib_TranslateAndRotateYVec3f(z_Vector3f* a0, s16 a1, z_Vector3f* a2, z_Vector3f* a3) {
    f32 sp1C;
    f32 f0;

    sp1C = Lib_cos(a1);
    f0 = Lib_sin(a1);
    a3->x = a0->x + (a2->x * sp1C + a2->z * f0);
    a3->y = a0->y + a2->y;
    a3->z = a0->z + (a2->z * sp1C - a2->x * f0);
}

#ifdef NONMATCHING

void Lib_LerpRGB(u8* a0, u8* a1, f32 a2, u8* a3) {
    // XXX regalloc is slightly off
    a3[0] = (f32)a0[0] + ((f32)a1[0] - (f32)a0[0]) * a2;
    a3[1] = (f32)a0[1] + ((f32)a1[1] - (f32)a0[1]) * a2;
    a3[2] = (f32)a0[2] + ((f32)a1[2] - (f32)a0[2]) * a2;
}

#else

GLOBAL_ASM("./asm/nonmatching/z_lib/Lib_LerpRGB.asm")

#endif

f32 Lib_PushAwayVec3f(z_Vector3f* a0, z_Vector3f* a1, f32 a2) {
    z_Vector3f sp24;
    f32 f2;
    f32 f0;

    Lib_SubVec3f(a1, a0, &sp24);
    f0 = Math3D_Length(&sp24);
    if (a2 < f0) {
        f2 = a2 / f0;
        f0 = f0 - a2;
        a0->x = a0->x + f2 * sp24.x;
        a0->y = a0->y + f2 * sp24.y;
        a0->z = a0->z + f2 * sp24.z;
    } else {
        Lib_CopyVec3f(a0, a1);
        f0 = 0;
    }

    return f0;
}

void Lib_Nop801004FC(void) {}

UNK_TYPE Lib_PtrSegToPhys(u32 a0) {
    return(D_801F8180[(a0 << 4) >> 28] + (a0 & 0xFFFFFF)) + 0x80000000;
}

UNK_TYPE Lib_PtrSegToPhysNull(u32 a0) {
    if ((a0 >> 28) == 0) {
        return a0;
    }

    return(D_801F8180[(a0 << 4) >> 28] + (a0 & 0xFFFFFF)) + 0x80000000;
}

UNK_TYPE Lib_PtrSegToK0(UNK_TYPE a0) {
    if (a0 == 0) {
        return 0;
    } else {
        return a0 + 0x80000000;
    }
}

UNK_TYPE Lib_PtrSegToK0Null(UNK_TYPE a0) {
    if (a0 == 0) {
        return 0;
    } else {
        return a0 + 0x80000000;
    }
}