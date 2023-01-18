#include "global.h"

// cKF_FrameControl_zeroClera
void func_801830A0(FrameControl* frameCtrl) {
    frameCtrl->unk_8 = 0.0f;
    frameCtrl->unk_10 = 0.0f;
    frameCtrl->unk_C = 0.0f;
    frameCtrl->unk_4 = 0.0f;
    frameCtrl->unk_0 = 0.0f;
    frameCtrl->unk_14 = false;
}

// cKF_FrameControl_ct
void func_801830C8(FrameControl* frameCtrl) {
    func_801830A0(frameCtrl);
}

// cKF_FrameControl_setFrame
void func_801830E8(FrameControl* frameCtrl, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    frameCtrl->unk_0 = arg1;
    frameCtrl->unk_4 = (arg2 < 1.0f) ? arg3 : arg2;
    frameCtrl->unk_8 = arg3;
    frameCtrl->unk_C = arg5;
    frameCtrl->unk_10 = arg4;
    frameCtrl->unk_14 = arg6;
}

s32 func_80183148(FrameControl* frameCtrl, f32 arg1, f32* out) {
    f32 temp_f0;
    f32 temp_f14;
    f32 phi_f2;

    *out = 0.0f;
    temp_f0 = frameCtrl->unk_10;

    if (arg1 == temp_f0) {
        return false;
    }

    phi_f2 = (frameCtrl->unk_0 < frameCtrl->unk_4) ? frameCtrl->unk_C : -frameCtrl->unk_C;
    temp_f14 = phi_f2 * 1.5f;

    if ((temp_f14 >= 0.0f && temp_f0 < arg1 && arg1 <= temp_f0 + temp_f14) ||
        (temp_f14 < 0.0f && arg1 < temp_f0 && temp_f0 + temp_f14 <= arg1)) {

        *out = temp_f0 + temp_f14 - arg1;
        return true;
    }
    return false;
}

s32 func_80183224(FrameControl* frameCtrl) {
    f32 sp1C;

    if (frameCtrl->unk_10 == frameCtrl->unk_4) {
        return 1;
    }
    if (func_80183148(frameCtrl, frameCtrl->unk_4, &sp1C)) {
        frameCtrl->unk_10 = frameCtrl->unk_4;
        return 1;
    }
    if (func_80183148(frameCtrl, frameCtrl->unk_0, &sp1C)) {
        frameCtrl->unk_10 = frameCtrl->unk_4;
        return 1;
    }
    return 0;
}

s32 func_801832B0(FrameControl* frameCtrl) {
    f32 sp1C;

    if (func_80183148(frameCtrl, frameCtrl->unk_4, &sp1C)) {
        frameCtrl->unk_10 = frameCtrl->unk_0 + sp1C;
        return 2;
    }
    if (func_80183148(frameCtrl, frameCtrl->unk_0, &sp1C)) {
        frameCtrl->unk_10 = frameCtrl->unk_4 + sp1C;
        return 2;
    }
    return 0;
}

s32 func_8018332C(FrameControl* frameCtrl) {
    s32 phi_v0;
    f32 phi_f0;

    if (!frameCtrl->unk_14) {
        phi_v0 = func_80183224(frameCtrl);
    } else {
        phi_v0 = func_801832B0(frameCtrl);
    }
    if (phi_v0 == 0) {
        phi_f0 = (frameCtrl->unk_0 < frameCtrl->unk_4) ? frameCtrl->unk_C : -frameCtrl->unk_C;
        frameCtrl->unk_10 = frameCtrl->unk_10 + phi_f0 * 1.5f;
    }
    if (frameCtrl->unk_10 < 1.0f) {
        frameCtrl->unk_10 = (frameCtrl->unk_10 - 1.0f) + frameCtrl->unk_8;
    } else if (frameCtrl->unk_8 < frameCtrl->unk_10) {
        frameCtrl->unk_10 = (frameCtrl->unk_10 - frameCtrl->unk_8) + 1.0f;
    }
    return phi_v0;
}

// cKF_SkeletonInfo_R_zeroClear
void func_8018340C(SkeletonInfo* skeleton) {
    skeleton->unk_18 = NULL;
    skeleton->unk_1C = NULL;
    skeleton->frameData = NULL;
    skeleton->unk_20 = NULL;
    skeleton->unk_2C = NULL;
    skeleton->unk_24 = 0.0f;
}

// cKF_SkeletonInfo_R_ct
void func_80183430(SkeletonInfo* skeleton, Struct_801BFA14_Arg1* arg1, SkeletonInfo_1C* arg2, Vec3s* frameData,
                   s16* arg4, UnkKeyframeCallback* callbacks) {
    func_8018340C(skeleton);
    func_801830C8(&skeleton->frameCtrl);
    skeleton->unk_18 = (Struct_801BFA14_Arg1*)Lib_SegmentedToVirtual(arg1);
    skeleton->unk_1C = (SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg2);
    skeleton->frameData = frameData;
    skeleton->unk_2C = arg4;
    skeleton->unk_20 = callbacks;
}

// cKF_SkeletonInfo_R_dt
void func_8018349C(SkeletonInfo* skeleton) {
}

void func_8018373C(SkeletonInfo* skeleton, Struct_801BFA14_Arg1* arg1, SkeletonInfo_1C* arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8);

void func_801834A8(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1) {
    func_8018373C(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, 0.0f, false);
}

void func_80183510(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1, f32 arg2) {
    func_8018373C(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, arg2, 0.0f, false);
}

void func_80183580(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1, f32 arg2) {
    func_8018373C(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, arg2, false);
}

void func_801835EC(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1) {
    func_8018373C(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, 0.0f, true);
}

void func_80183658(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1, f32 arg2) {
    func_8018373C(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, arg2, 0.0f, true);
}

void func_801836CC(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1, f32 arg2) {
    func_8018373C(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, arg2, true);
}

void func_8018373C(SkeletonInfo* skeleton, Struct_801BFA14_Arg1* arg1, SkeletonInfo_1C* arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8) {
    skeleton->unk_24 = arg7;

    if (skeleton->unk_18 != arg1) {
        skeleton->unk_18 = (Struct_801BFA14_Arg1*)Lib_SegmentedToVirtual(arg1);
    }
    skeleton->unk_1C = (SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg2);

    func_801830E8(&skeleton->frameCtrl, arg3, arg4, skeleton->unk_1C->unk_12, arg5, arg6, arg8);
}

void func_801837CC(SkeletonInfo* skeleton, SkeletonInfo_1C* arg1) {
    skeleton->unk_1C = (SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1);
    skeleton->frameCtrl.unk_8 = skeleton->unk_1C->unk_12;
}

#define CB(x) ((x) * (x) * (x))

// cKF_HermitCalc
// hermite interpolation
f32 func_80183808(f32 t, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 p = 3.0f * SQ(t) - 2.0f * CB(t);

    return (1.0f - p) * arg2 + p * arg3 + ((CB(t) - 2.0f * SQ(t) + t) * arg4 + (CB(t) - SQ(t)) * arg5) * arg1;
}

// cKF_KeyCalc
s16 func_80183880(s16 arg0, s16 arg1, Vec3s* arg2, f32 arg3) {
    Vec3s* temp_a3 = &arg2[arg0];
    Vec3s* temp_v1 = &temp_a3[arg1];
    f32 temp_f2;
    s16 phi_v0;
    s16 phi_v1;

    if (arg3 <= temp_a3->x) {
        return temp_a3->y;
    }
    if (temp_a3[arg1 - 1].x <= arg3) {
        return temp_a3[arg1 - 1].y;
    }

    for (phi_v0 = 1, phi_v1 = 0; true; phi_v0++, phi_v1++) {
        if (arg3 < temp_a3[phi_v0].x) {
            temp_f2 = temp_a3[phi_v0].x - temp_a3[phi_v1].x;

            if (!IS_ZERO(temp_f2)) {
                return nearbyint(func_80183808((arg3 - temp_a3[phi_v1].x) / temp_f2, temp_f2 * (1.0f / 30),
                                               temp_a3[phi_v1].y, temp_a3[phi_v0].y, temp_a3[phi_v1].z,
                                               temp_a3[phi_v0].z));
            }
            return temp_a3[phi_v1].y;
        }
    }
}

// cKF_SkeletonInfo_subRotInterpolation
void func_80183A3C(f32 t, s16* out, s16 rot1, s16 rot2) {
    u16 urot1 = rot1;
    s32 pad;
    u16 urot2 = rot2;
    f32 f1 = rot1;
    f32 signedDiff = rot2 - f1;
    f32 f2 = urot1;
    f32 unsignedDiff = urot2 - f2;

    if (fabsf(signedDiff) < fabsf(unsignedDiff)) {
        *out = f1 + signedDiff * t;
    } else {
        *out = f2 + unsignedDiff * t;
    }
}

// lerp
// cKF_SkeletonInfo_morphST
void func_80183B08(s16 arg0[3], s16 arg1[3], f32 t) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (*arg0 != *arg1) {
            f32 f1 = *arg0;
            f32 f2 = *arg1;
            *arg0 = f1 + (f2 - f1) * t;
        }
        arg0++;
        arg1++;
    }
}

void func_80183B68(SkeletonInfo* skeleton) {
    Vec3s* frameData = skeleton->frameData;
    Vec3s* phi_s1 = (Vec3s*)skeleton->unk_2C;
    f32 t = 1.0f / fabsf(skeleton->unk_24);
    s32 i;

    for (i = 0; i < skeleton->unk_18->limbCount; i++) {
        Vec3s temp_a2;
        Vec3s temp_a3;

        func_80183B08((s16*)frameData, (s16*)phi_s1, t);

        frameData++;
        phi_s1++;

        temp_a2.x = frameData->x;
        temp_a2.y = frameData->y;
        temp_a2.z = frameData->z;

        temp_a3.x = phi_s1->x;
        temp_a3.y = phi_s1->y;
        temp_a3.z = phi_s1->z;

        if (temp_a2.x != temp_a3.x || temp_a2.y != temp_a3.y || temp_a2.z != temp_a3.z) {
            Vec3s temp_a0;
            f32 v1;
            f32 v2;

            temp_a0.x = 0x7FFF + temp_a2.x;
            temp_a0.y = 0x7FFF - temp_a2.y;
            temp_a0.z = 0x7FFF + temp_a2.z;

            v1 = fabsf((f32)temp_a3.x - temp_a2.x) + fabsf((f32)temp_a3.y - temp_a2.y) +
                 fabsf((f32)temp_a3.z - temp_a2.z);
            v2 = fabsf((f32)temp_a3.x - temp_a0.x) + fabsf((f32)temp_a3.y - temp_a0.y) +
                 fabsf((f32)temp_a3.z - temp_a0.z);

            if (v1 < v2) {
                func_80183A3C(t, &frameData->x, temp_a2.x, temp_a3.x);
                func_80183A3C(t, &frameData->y, temp_a2.y, temp_a3.y);
                func_80183A3C(t, &frameData->z, temp_a2.z, temp_a3.z);
            } else {
                func_80183A3C(t, &frameData->x, temp_a0.x, temp_a3.x);
                func_80183A3C(t, &frameData->y, temp_a0.y, temp_a3.y);
                func_80183A3C(t, &frameData->z, temp_a0.z, temp_a3.z);
            }
        }
        phi_s1++;
        frameData++;
        func_80183B08((s16*)frameData, (s16*)phi_s1, t);
        frameData++;
        phi_s1++;
    }
}

s32 func_80183DE0(SkeletonInfo* skeleton) {
    s32 sp9C;
    s32 pad[7];
    s16* sp7C;
    Vec3s* sp78;
    s16* sp74;
    s32 pad1[2];
    f32 temp_f0;
    u16* phi_v1;
    s32 phi_s1;
    s16* phi_s2;
    u32 phi_s3;
    s32 phi_s4 = 0;
    s32 phi_s5 = 0;
    s32 phi_s6 = 0;
    s32 phi_s7;

    if (skeleton->unk_24 != 0.0f) {
        phi_s2 = skeleton->unk_2C;
    } else {
        phi_s2 = (s16*)skeleton->frameData;
    }

    sp7C = (s16*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_C);
    sp74 = (s16*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_8);
    sp78 = (Vec3s*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_4);
    phi_v1 = (u16*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_0);

    for (sp9C = 0; sp9C < skeleton->unk_18->limbCount; sp9C++, phi_v1++) {
        for (phi_s3 = 256, phi_s7 = 0; phi_s7 < 3; phi_s7++) {
            for (phi_s1 = 0; phi_s1 < 3; phi_s1++, phi_s2++) {
                if (*phi_v1 & phi_s3) {
                    *phi_s2 = func_80183880(phi_s6, sp74[phi_s4], sp78, skeleton->frameCtrl.unk_10);
                    phi_s6 += sp74[phi_s4];
                    phi_s4++;
                } else {
                    *phi_s2 = sp7C[phi_s5];
                    phi_s5++;
                }
                phi_s3 >>= 1;
                if (phi_s7 == 1) {
                    temp_f0 = *phi_s2 * 0.1f;
                    *phi_s2 = (temp_f0 - ((s32)(temp_f0 * (1.0f / 360)) * 360.0f)) * 182.04445f;
                }
            }
        }
    }

    if (IS_ZERO(skeleton->unk_24)) {
        return func_8018332C(&skeleton->frameCtrl);
    } else if (skeleton->unk_24 > 0.0f) {
        func_80183B68(skeleton);
        skeleton->unk_24 -= 1.0f;
        if (skeleton->unk_24 <= 0.0f) {
            skeleton->unk_24 = 0.0f;
        }
        return 0;
    } else {
        func_80183B68(skeleton);
        skeleton->unk_24 += 1.0f;
        if (skeleton->unk_24 >= 0.0f) {
            skeleton->unk_24 = 0.0f;
        }
        return func_8018332C(&skeleton->frameCtrl);
    }
}

// cKF_Si3_draw_SV_R_child
void func_8018410C(PlayState* play, SkeletonInfo* skeleton, s32* limbIndex,
                   OverrideKeyframeDrawScaled overrideKeyframeDraw, PostKeyframeDrawScaled postKeyframeDraw, void* arg,
                   Mtx** mtx) {
    Struct_801BFA14_Arg1_Field4_2* limb =
        (Struct_801BFA14_Arg1_Field4_2*)Lib_SegmentedToVirtual(skeleton->unk_18->unk_4_2);
    s32 i;
    Gfx* newDList;
    Gfx* limbDList;
    u8 flags;
    Vec3f scale;
    Vec3s rot;
    Vec3f pos;
    Vec3s* frameData;

    OPEN_DISPS(play->state.gfxCtx);

    limb += *limbIndex;
    frameData = &skeleton->frameData[*limbIndex * 3];

    scale.x = frameData->x * 0.01f;
    scale.y = frameData->y * 0.01f;
    scale.z = frameData->z * 0.01f;

    frameData++;

    rot.x = frameData->x;
    rot.y = frameData->y;
    rot.z = frameData->z;

    frameData++;

    pos.x = frameData->x;
    pos.y = frameData->y;
    pos.z = frameData->z;

    Matrix_Push();

    newDList = limbDList = limb->dList;
    flags = limb->flags;

    if (overrideKeyframeDraw == NULL ||
        (overrideKeyframeDraw != NULL &&
         overrideKeyframeDraw(play, skeleton, *limbIndex, &newDList, &flags, arg, &scale, &rot, &pos) != 0)) {
        if ((skeleton->unk_20 == NULL) || (limb->unk_6 == 0xFF) || (skeleton->unk_20[limb->unk_6] == NULL) ||
            skeleton->unk_20[limb->unk_6](play, skeleton, *limbIndex, &newDList, &flags, arg) != 0) {

            Matrix_TranslateRotateZYX(&pos, &rot);

            if (scale.x != 1.0f || scale.y != 1.0f || scale.z != 1.0f) {
                Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);
            }

            if (newDList != NULL) {
                Matrix_ToMtx(*mtx);

                if (flags & KEYFRAME_XLU) {
                    gSPMatrix(POLY_XLU_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_XLU_DISP++, newDList);
                } else {
                    gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_OPA_DISP++, newDList);
                }

                (*mtx)++;
            } else if (limbDList != NULL) {
                gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                Matrix_ToMtx(*mtx);

                (*mtx)++;
            }
        }
    }

    if (postKeyframeDraw != NULL) {
        postKeyframeDraw(play, skeleton, *limbIndex, &newDList, &flags, arg, &scale, &rot, &pos);
    }

    (*limbIndex)++;

    for (i = 0; i < limb->unk_4; i++) {
        func_8018410C(play, skeleton, limbIndex, overrideKeyframeDraw, postKeyframeDraw, arg, mtx);
    }

    Matrix_Pop();
    CLOSE_DISPS(play->state.gfxCtx);
}

// cKF_Si3_draw_R_SV
void func_8018450C(PlayState* play, SkeletonInfo* skeleton, Mtx* mtx,
                   OverrideKeyframeDrawScaled overrideKeyframeDraw, PostKeyframeDrawScaled postKeyframeDraw,
                   void* arg) {
    s32 limbIndex;

    if (mtx == NULL) {
        return;
    }

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);
    gSPSegment(POLY_XLU_DISP++, 0x0D, mtx);

    limbIndex = 0;
    func_8018410C(play, skeleton, &limbIndex, overrideKeyframeDraw, postKeyframeDraw, arg, &mtx);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_801845A4(SkeletonInfo2* skeleton) {
    skeleton->unk_18 = 0;
    skeleton->unk_1C = 0;
    skeleton->frameData = NULL;
    skeleton->unk_28 = 0;
    skeleton->unk_2C = 0;
    skeleton->unk_20 = 0.0f;
}

void func_801845C8(SkeletonInfo2* skeleton, Struct_801BFA14_Arg1* arg1, SkeletonInfo_1C* arg2, Vec3s* frameData,
                   s16* arg4) {
    func_801845A4(skeleton);
    func_801830C8(&skeleton->frameCtrl);
    skeleton->unk_18 = (Struct_801BFA14_Arg1*)Lib_SegmentedToVirtual(arg1);
    skeleton->unk_1C = (SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg2);
    skeleton->frameData = frameData;
    skeleton->unk_28 = arg4;
}

void func_8018462C(SkeletonInfo2* skeleton) {
}

void func_80184914(SkeletonInfo2* skeleton, Struct_801BFA14_Arg1* arg1, SkeletonInfo_1C* arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9);

void func_80184638(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1, s32 arg2) {
    func_80184914(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, 0.0f, false, arg2);
}

void func_801846AC(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1, s32 arg2, f32 arg3) {
    func_80184914(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, arg3, 0.0f, false, arg2);
}

void func_80184728(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1, s32 arg2, f32 arg3) {
    func_80184914(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, arg3, false, arg2);
}

void func_801847A0(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1, s32 arg2) {
    func_80184914(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, 0.0f, true, arg2);
}

void func_80184818(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1, s32 arg2, f32 arg3) {
    func_80184914(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, arg3, 0.0f, true, arg2);
}

void func_80184898(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1, s32 arg2, f32 arg3) {
    func_80184914(skeleton, skeleton->unk_18, arg1, 1.0f, ((SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg1))->unk_12,
                  1.0f, 1.0f, arg3, true, arg2);
}

void func_80184914(SkeletonInfo2* skeleton, Struct_801BFA14_Arg1* arg1, SkeletonInfo_1C* arg2, f32 arg3, f32 arg4,
                   f32 arg5, f32 arg6, f32 arg7, s32 arg8, s32 arg9) {
    skeleton->unk_20 = arg7;
    skeleton->unk_18 = (Struct_801BFA14_Arg1*)Lib_SegmentedToVirtual(arg1);
    skeleton->unk_1C = (SkeletonInfo_1C*)Lib_SegmentedToVirtual(arg2);

    func_801830E8(&skeleton->frameCtrl, arg3, arg4, skeleton->unk_1C->unk_12, arg5, arg6, arg8);
    skeleton->unk_2C = arg9;
}

void func_801849A0(SkeletonInfo2* skeleton, SkeletonInfo_1C* arg1) {
    skeleton->unk_1C = Lib_SegmentedToVirtual(arg1);
    skeleton->frameCtrl.unk_8 = skeleton->unk_1C->unk_12;
}

void func_801849DC(SkeletonInfo2* skeleton) {
    Vec3s* frameData = skeleton->frameData;
    Vec3s* phi_s7 = (Vec3s*)skeleton->unk_28;
    f32 t = 1.0f / fabsf(skeleton->unk_20);
    s32 i;

    func_80183B08((s16*)frameData, (s16*)phi_s7, t);

    frameData++;
    phi_s7++;

    for (i = 0; i < skeleton->unk_18->limbCount; i++) {
        Vec3s temp_a2;
        Vec3s temp_a3;

        temp_a2.x = frameData->x;
        temp_a2.y = frameData->y;
        temp_a2.z = frameData->z;

        temp_a3.x = phi_s7->x;
        temp_a3.y = phi_s7->y;
        temp_a3.z = phi_s7->z;

        if (temp_a2.x != temp_a3.x || temp_a2.y != temp_a3.y || temp_a2.z != temp_a3.z) {
            Vec3s temp_a0;
            f32 v1;
            f32 v2;

            temp_a0.x = temp_a2.x + 0x7FFF;
            temp_a0.y = 0x7FFF - temp_a2.y;
            temp_a0.z = temp_a2.z + 0x7FFF;

            v1 = fabsf((f32)temp_a3.x - temp_a2.x) + fabsf((f32)temp_a3.y - temp_a2.y) +
                 fabsf((f32)temp_a3.z - temp_a2.z);
            v2 = fabsf((f32)temp_a3.x - temp_a0.x) + fabsf((f32)temp_a3.y - temp_a0.y) +
                 fabsf((f32)temp_a3.z - temp_a0.z);

            if (v1 < v2) {
                func_80183A3C(t, &frameData->x, temp_a2.x, temp_a3.x);
                func_80183A3C(t, &frameData->y, temp_a2.y, temp_a3.y);
                func_80183A3C(t, &frameData->z, temp_a2.z, temp_a3.z);
            } else {
                func_80183A3C(t, &frameData->x, temp_a0.x, temp_a3.x);
                func_80183A3C(t, &frameData->y, temp_a0.y, temp_a3.y);
                func_80183A3C(t, &frameData->z, temp_a0.z, temp_a3.z);
            }
        }
        phi_s7++;
        frameData++;
    }
}

#ifdef NON_MATCHING
s32 func_80184C48(SkeletonInfo2* skeleton) {
    s32 sp84;
    s16* sp68;
    Vec3s* sp64;
    s16* sp60;
    f32 temp_f0;
    s32 phi_s6 = 0;
    s32 phi_s4 = 0;
    s32 phi_s5 = 0;
    u32 phi_s2;
    s32 phi_s3;
    s16* phi_s1;
    u8* phi_s7;
    u8* phi_t0;
    Vec3s* phi_v0;
    s32 phi_v1;

    if (skeleton->unk_20 != 0.0f) {
        phi_s1 = skeleton->unk_28;
    } else {
        phi_s1 = (s16*)skeleton->frameData;
    }

    sp68 = (s16*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_C);
    sp60 = (s16*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_8);
    sp64 = (Vec3s*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_4);
    phi_t0 = (u8*)Lib_SegmentedToVirtual(skeleton->unk_1C->unk_0);

    for (phi_s2 = 32, phi_s3 = 0; phi_s3 < 3; phi_s3++, phi_s2 >>= 1) {
        if (*phi_t0 & phi_s2) {
            *phi_s1 = func_80183880(phi_s6, sp60[phi_s4], sp64, skeleton->frameCtrl.unk_10);
            phi_s6 += sp60[phi_s4++];
        } else {
            *phi_s1 = sp68[phi_s5++];
        }
        phi_s1++;
        if (1) {}
        if (!phi_v1) {}
    }
    phi_s7 = phi_t0;

    for (sp84 = 0; sp84 < skeleton->unk_18->limbCount; sp84++, phi_s7++) {
        for (phi_s2 = 4, phi_s3 = 0; phi_s3 < 3; phi_s3++, phi_s2 >>= 1, phi_s1++) {
            if (*phi_s7 & phi_s2) {
                *phi_s1 = func_80183880(phi_s6, sp60[phi_s4], sp64, skeleton->frameCtrl.unk_10);
                phi_s6 += sp60[phi_s4++];
            } else {
                *phi_s1 = sp68[phi_s5++];
            }
            temp_f0 = *phi_s1 * 0.1f;
            *phi_s1 = (temp_f0 - ((s32)(temp_f0 * (1.0f / 360)) * 360.0f)) * 182.04445f;
        }
    }

    if (skeleton->unk_2C != NULL) {
        if (skeleton->unk_20 != 0.0f) {
            phi_v0 = (Vec3s*)skeleton->unk_28;
        } else {
            phi_v0 = skeleton->frameData;
        }

        phi_v0++;
        for (phi_v1 = 0, sp84 = 0; sp84 < skeleton->unk_18->limbCount; sp84++, phi_v1++, phi_v0++) {
            phi_v0->x = phi_v0->x + skeleton->unk_2C[phi_v1].x;
            phi_v0->y = phi_v0->y + skeleton->unk_2C[phi_v1].y;
            phi_v0->z = phi_v0->z + skeleton->unk_2C[phi_v1].z;
        }
    }

    if (IS_ZERO(skeleton->unk_20)) {
        return func_8018332C(&skeleton->frameCtrl);
    }
    if (skeleton->unk_20 > 0.0f) {
        func_801849DC(skeleton);
        skeleton->unk_20 -= 1.0f;
        if (skeleton->unk_20 <= 0.0f) {
            skeleton->unk_20 = 0.0f;
        }
        return 0;
    }
    func_801849DC(skeleton);
    skeleton->unk_20 += 1.0f;
    if (skeleton->unk_20 >= 0.0f) {
        skeleton->unk_20 = 0.0f;
    }
    return func_8018332C(&skeleton->frameCtrl);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/c_keyframe/func_80184C48.s")
#endif

void func_801850A0(PlayState* play, SkeletonInfo2* skeleton, s32* limbIndex,
                   OverrideKeyframeDraw overrideKeyframeDraw, PostKeyframeDraw postKeyframeDraw, void* arg, Mtx** mtx) {
    Struct_801BFA14_Arg1_Field4* jointData =
        *limbIndex + (Struct_801BFA14_Arg1_Field4*)Lib_SegmentedToVirtual(skeleton->unk_18->unk_4);
    s32 i;
    Gfx* newDList;
    Gfx* limbDList;
    u8 flags;
    Vec3s rot;
    Vec3s* frameData = &skeleton->frameData[*limbIndex];
    Vec3f pos;

    if (*limbIndex != 0) {
        pos.x = jointData->root.x;
        pos.y = jointData->root.y;
        pos.z = jointData->root.z;
    } else {
        pos.x = frameData->x;
        pos.y = frameData->y;
        pos.z = frameData->z;
    }

    frameData++;

    rot.x = frameData->x;
    rot.y = frameData->y;
    rot.z = frameData->z;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Push();

    newDList = limbDList = jointData->dList;
    flags = jointData->flags;

    if (overrideKeyframeDraw == NULL ||
        (overrideKeyframeDraw != NULL &&
         overrideKeyframeDraw(play, skeleton, *limbIndex, &newDList, &flags, arg, &rot, &pos) != 0)) {
        Matrix_TranslateRotateZYX(&pos, &rot);
        if (newDList != NULL) {
            Matrix_ToMtx(*mtx);

            if (flags & KEYFRAME_XLU) {
                gSPMatrix(POLY_XLU_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, newDList);
            } else {
                gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, newDList);
            }
            (*mtx)++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(*mtx);

            gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            (*mtx)++;
        }
    }

    if (postKeyframeDraw != NULL) {
        postKeyframeDraw(play, skeleton, *limbIndex, &newDList, &flags, arg, &rot, &pos);
    }

    (*limbIndex)++;

    for (i = 0; i < jointData->unk_4; i++) {
        func_801850A0(play, skeleton, limbIndex, overrideKeyframeDraw, postKeyframeDraw, arg, mtx);
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_801853C8(PlayState* play, SkeletonInfo2* skeleton, Mtx* mtx,
                   OverrideKeyframeDraw overrideKeyframeDraw, PostKeyframeDraw postKeyframeDraw, void* arg) {
    s32 limbIndex;

    if (mtx == NULL) {
        return;
    }

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);
    gSPSegment(POLY_XLU_DISP++, 0x0D, mtx);

    limbIndex = 0;
    func_801850A0(play, skeleton, &limbIndex, overrideKeyframeDraw, postKeyframeDraw, arg, &mtx);

    CLOSE_DISPS(play->state.gfxCtx);
}

#ifdef NON_MATCHING
void func_80185460(SkeletonInfo2* arg0, s32 arg1, s16* arg2) {
    s32 sp78;
    s16* sp5C;
    Vec3s* sp58;
    s32 sp44;
    s32 var_s1;
    u16* var_v1;
    u32 var_s2;
    s16* temp_fp;
    s32 var_s3 = 0;
    s32 var_s4 = 0;
    s32 var_s5 = 0;
    s16* var_s6 = arg2;

    sp5C = (s16*)Lib_SegmentedToVirtual(arg0->unk_1C->unk_C);
    temp_fp = (s16*)Lib_SegmentedToVirtual(arg0->unk_1C->unk_8);
    sp58 = (Vec3s*)Lib_SegmentedToVirtual(arg0->unk_1C->unk_4);
    var_v1 = (u16*)Lib_SegmentedToVirtual(arg0->unk_1C->unk_0);

    for (sp44 = 0; sp44 < arg0->unk_18->limbCount * 2; sp44 += 2, var_v1++) {
        for (var_s2 = 256, sp78 = 0; sp78 < 3; sp78++) {
            if ((sp44 == arg1 * 2) && (sp78 == 0)) {
                for (var_s1 = 0; var_s1 < 3; var_s1++, var_s6++) {
                    if (*var_v1 & var_s2) {
                        *var_s6 = func_80183880(var_s5, temp_fp[var_s3], sp58, arg0->frameCtrl.unk_10);
                        var_s5 += temp_fp[var_s3];
                        var_s3++;
                    } else {
                        *var_s6 = sp5C[var_s4];
                        var_s4++;
                    }
                    var_s2 >>= 1;
                }
            } else {
                for (var_s1 = 0; var_s1 < 3; var_s1++) {
                    if (*var_v1 & var_s2) {
                        var_s5 += temp_fp[var_s3];
                        var_s3++;
                    } else {
                        var_s4++;
                    }
                    var_s2 >>= 1;
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/c_keyframe/func_80185460.s")
#endif
