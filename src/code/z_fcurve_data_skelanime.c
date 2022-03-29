/**
 * File: z_fcurve_data_skelanime.c
 * Description: Curve skeleton animation system
 *
 * A curve skeleton has a fixed number of limbs, each of which has 9 propetries that may be changed by the animation:
 * - 3 scales,
 * - 3 rotations,
 * - 3 positions
 * (note the position is stored in the animations instead of being stored in the limbs like SkelAnime would).
 *
 * A curve animation consists of 4 parts:
 * - a header (really a footer, for it is always last in the object file)
 * - a list of counts for the 9 properties of each limb (u8)
 * - a list of interpolation data (CurveInterpKnot). The length is the sum of the counts.
 * - a list of fixed data (). The length is the number of 0 in counts.
 *
 * If the interpolation count for a property is 0, the value of the property is copied from the next number in the
 * fixed data; there are no gaps for nonzero interpolation count.
 * If the interpolation count N for a property is larger than 0, the next N elements of the interpolation data array
 * are used to interpolate the value of the property, using Curve_Interpolate.
 *
 * Curve limbs may use LOD:
 * - lower detail draws only the first displaylist
 * - higher detail draws both.
 */

#include "global.h"
#include "z64curve.h"

void SkelCurve_Clear(SkelCurve* skelCurve) {
    skelCurve->limbCount = 0;
    skelCurve->skeleton = NULL;
    skelCurve->animation = NULL;
    skelCurve->curFrame = 0.0f;
    skelCurve->playSpeed = 0.0f;
    skelCurve->endFrame = 0.0f;
    skelCurve->unk_0C = 0.0f;
    skelCurve->transforms = NULL;
}

/**
 * Initialises the SkelCurve struct and mallocs the joint data.
 *
 * @return bool always true
 */
s32 SkelCurve_Init(GlobalContext* globalCtx, SkelCurve* skelCurve, CurveSkeletonHeader* limbListSeg,
                   CurveAnimationHeader* animation) {
    SkelCurveLimb** limbs;
    CurveSkeletonHeader* skeleton = Lib_SegmentedToVirtual(limbListSeg);

    skelCurve->limbCount = skeleton->limbCount;
    skelCurve->skeleton = Lib_SegmentedToVirtual(skeleton->limbs);

    skelCurve->transforms = ZeldaArena_Malloc(sizeof(*skelCurve->transforms) * skelCurve->limbCount);

    skelCurve->curFrame = 0.0f;
    return true;
}

/**
 * Frees the joint data.
 */
void SkelCurve_Destroy(GlobalContext* globalCtx, SkelCurve* skelCurve) {
    if (skelCurve->transforms != NULL) {
        ZeldaArena_Free(skelCurve->transforms);
    }
}

void SkelCurve_SetAnim(SkelCurve* skelCurve, CurveAnimationHeader* animation, f32 arg2, f32 endFrame, f32 curFrame,
                       f32 playSpeed) {
    skelCurve->unk_0C = arg2 - skelCurve->playSpeed;
    skelCurve->endFrame = endFrame;
    skelCurve->curFrame = curFrame;
    skelCurve->playSpeed = playSpeed;
    skelCurve->animation = animation;
}

typedef enum {
    /* 0 */ SKELCURVE_VEC_TYPE_SCALE,
    /* 1 */ SKELCURVE_VEC_TYPE_ROTATION,
    /* 2 */ SKELCURVE_VEC_TYPE_POSIITON,
    /* 3 */ SKELCURVE_VEC_TYPE_MAX,
} SkelCurveVecType;

#define SKELCURVE_SCALE_SCALE 1024.0f
#define SKELCURVE_SCALE_ROTATION (32768.0f / 180.0f)
#define SKELCURVE_SCALE_POSITION 100

/**
 * The only animation updating function.
 *
 * @return bool true when the animation has finished.
 */
s32 SkelCurve_Update(GlobalContext* globalCtx, SkelCurve* skelCurve) {
    s16* transforms;
    u8* transformMaxIndex;
    CurveAnimationHeader* transformIndex;
    u16* transformCopyValues;
    s32 i;
    s32 ret = false;
    s32 coord;
    CurveInterpKnot* transData;
    s32 vecType;

    transformIndex = Lib_SegmentedToVirtual(skelCurve->animation);
    transformMaxIndex = Lib_SegmentedToVirtual(transformIndex->maxIndex);
    transData = Lib_SegmentedToVirtual(transformIndex->CurveInterpKnot);
    transformCopyValues = Lib_SegmentedToVirtual(transformIndex->copyValues);
    transforms = (s16*)skelCurve->transforms;

    skelCurve->curFrame += skelCurve->playSpeed * ((s32)globalCtx->state.framerateDivisor * 0.5f);

    if (((skelCurve->playSpeed >= 0.0f) && (skelCurve->curFrame > skelCurve->endFrame)) ||
        ((skelCurve->playSpeed < 0.0f) && (skelCurve->curFrame < skelCurve->endFrame))) {
        skelCurve->curFrame = skelCurve->endFrame;
        ret = true;
    }

    for (i = 0; i < skelCurve->limbCount; i++) {
        for (vecType = SKELCURVE_VEC_TYPE_SCALE; vecType < SKELCURVE_VEC_TYPE_MAX;
             vecType++) {                         // scale/rotation/position
            for (coord = 0; coord < 3; coord++) { // x/y/z
                f32 transformValue;

                if (*transformMaxIndex == 0) {
                    transformValue = *transformCopyValues;
                    *transforms = transformValue;
                    transformCopyValues++;
                } else {
                    transformValue = Curve_Interpolate(skelCurve->curFrame, transData, *transformMaxIndex);
                    transData += *transformMaxIndex;
                    if (vecType == SKELCURVE_VEC_TYPE_SCALE) {
                        // Rescaling allows for more refined scaling using an s16
                        *transforms = transformValue * SKELCURVE_SCALE_SCALE;
                    } else if (vecType == SKELCURVE_VEC_TYPE_ROTATION) {
                        // Convert value from degrees to a binary angle
                        *transforms = transformValue * SKELCURVE_SCALE_ROTATION;
                    } else { // SKELCURVE_VEC_TYPE_POSIITON
                        // Model scale to world scale
                        *transforms = transformValue * SKELCURVE_SCALE_POSITION;
                    }
                }
                transformMaxIndex++;
                transforms++;
            }
        }
    }

    return ret;
}

/**
 * Recursively draws limbs with appropriate properties.
 */
void SkelCurve_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, SkelCurve* skelCurve,
                        OverrideCurveLimbDraw overrideLimbDraw, PostCurveLimbDraw postLimbDraw, s32 lod, Actor* thisx) {
    SkelCurveLimb* limb = Lib_SegmentedToVirtual(skelCurve->skeleton[limbIndex]);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    if ((overrideLimbDraw == NULL) ||
        ((overrideLimbDraw != NULL) && overrideLimbDraw(globalCtx, skelCurve, limbIndex, thisx))) {
        Vec3f scale;
        Vec3s rot;
        Vec3f pos;
        Gfx* dList;
        Vec3s* transform = (Vec3s*)&skelCurve->transforms[limbIndex];

        scale.x = transform->x / SKELCURVE_SCALE_SCALE;
        scale.y = transform->y / SKELCURVE_SCALE_SCALE;
        scale.z = transform->z / SKELCURVE_SCALE_SCALE;
        transform++;
        rot.x = transform->x;
        rot.y = transform->y;
        rot.z = transform->z;
        transform++;
        // Position.
        pos.x = transform->x;
        pos.y = transform->y;
        pos.z = transform->z;

        Matrix_JointPosition(&pos, &rot);
        Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);

        if (lod == 0) {
            s32 pad1;

            dList = limb->dList[0];
            if (dList != NULL) {
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, dList);
            }
        } else if (lod == 1) {
            s32 pad2;

            dList = limb->dList[0];
            if (dList != NULL) {
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, dList);
            }
            dList = limb->dList[1];
            if (dList != NULL) {
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, dList);
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, skelCurve, limbIndex, thisx);
    }

    if (limb->child != LIMB_DONE) {
        SkelCurve_DrawLimb(globalCtx, limb->child, skelCurve, overrideLimbDraw, postLimbDraw, lod, thisx);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        SkelCurve_DrawLimb(globalCtx, limb->sibling, skelCurve, overrideLimbDraw, postLimbDraw, lod, thisx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void SkelCurve_Draw(Actor* actor, GlobalContext* globalCtx, SkelCurve* skelCurve,
                    OverrideCurveLimbDraw overrideLimbDraw, PostCurveLimbDraw postLimbDraw, s32 lod, Actor* thisx) {
    if (skelCurve->transforms != NULL) {
        SkelCurve_DrawLimb(globalCtx, 0, skelCurve, overrideLimbDraw, postLimbDraw, lod, thisx);
    }
}
