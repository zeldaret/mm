#include <ultra64.h>
#include <global.h>

#ifdef NON_MATCHING
void func_800A81F0(EffectBlure* this, Vec3f* p1, Vec3f* p2) {
    EffectBlureElement* elem;
    s32 numElements;
    Vec3f sp16C;
    Vec3f sp160;
    Vec3f sp154;
    f32 scale;
    MtxF sp110;
    MtxF spD0;
    MtxF sp90;
    MtxF sp50;
    Vec3f sp44;
    Vec3f sp38;

    if (this != NULL) {
        numElements = this->numElements;
        if (numElements >= 16) {
            return;
        }

        elem = &this->elements[numElements];
        elem->state = 1;

        if (!(this->flags & 2)) {
            elem->p1.x = p1->x;
            elem->p1.y = p1->y;
            elem->p1.z = p1->z;
            elem->p2.x = p2->x;
            elem->p2.y = p2->y;
            elem->p2.z = p2->z;
        } else {
            sp16C.x = ((f32)(elem - 1)->p2.x + (f32)(elem - 1)->p1.x) * 0.5f;
            sp16C.y = ((f32)(elem - 1)->p2.y + (f32)(elem - 1)->p1.y) * 0.5f;
            sp16C.z = ((f32)(elem - 1)->p2.z + (f32)(elem - 1)->p1.z) * 0.5f;
            sp160.x = (p1->x + p2->x) * 0.5f;
            sp160.y = (p1->y + p2->y) * 0.5f;
            sp160.z = (p1->z + p2->z) * 0.5f;

            Math_Vec3f_Diff(&sp160, &sp16C, &sp154);
            scale = Math3D_Vec3fMagnitude(&sp154);
            if (!(fabsf(scale) < D_801DC080)) {
                scale = 1.0f / scale;
                Math_Vec3f_Scale(&sp154, scale);

                SkinMatrix_SetTranslate(&sp110, sp160.x, sp160.y, sp160.z);
                Matrix_MakeRotationAroundUnitVector(&spD0, this->addAngle, sp154.x, sp154.y, sp154.z);
                SkinMatrix_MtxFMtxFMult(&sp110, &spD0, &sp90);
                SkinMatrix_SetTranslate(&sp110, -sp160.x, -sp160.y, -sp160.z);
                SkinMatrix_MtxFMtxFMult(&sp90, &sp110, &sp50);
                SkinMatrix_Vec3fMtxFMultXYZ(&sp50, p1, &sp38);
                SkinMatrix_Vec3fMtxFMultXYZ(&sp50, p2, &sp44);

                elem->p1.x = sp38.x;
                elem->p1.y = sp38.y;
                elem->p1.z = sp38.z;
                elem->p2.x = sp44.x;
                elem->p2.y = sp44.y;
                elem->p2.z = sp44.z;
            }
        }

        elem->timer = 1;
        this->numElements++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A81F0.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A8514.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/EffectBlure_Initcommon.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/EffectBlure_Init1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/EffectBlure_Init2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/EffectBlure_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/EffectBlure_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A8C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A8DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A92FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A9330.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800A9804.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800AA190.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800AA460.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800AA498.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800AA700.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/func_800AABE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_eff_blure/EffectBlure_Draw.s")
