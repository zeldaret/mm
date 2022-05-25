/*
 * File: z_eff_ss_extra.c
 * Overlay: ovl_Effect_Ss_Extra
 * Description:
 */

#include "z_eff_ss_extra.h"

#define PARAMS ((EffectSsExtraInitParams*)initParamsx)

s32 EffectSsExtra_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsExtra_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsExtra_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

s16 D_809808E0[] = { 0x1E, 0x3C, 0x64};


const EffectSsInit Effect_Ss_Extra_InitVars = {
    EFFECT_SS_EXTRA,
    EffectSsExtra_Init,
};

// wtf
UNK_TYPE D_809808F0[] = { 0x06000000, 0x06000480, 0x06000900};

s32 EffectSsExtra_Init(GlobalContext *globalCtx, u32 index, EffectSs *this, void *initParamsx) {
    EffectSsExtraInitParams* params = PARAMS;
    s32 pad;
    s32 objIndex;
    //*segBackup;

    objIndex = Object_GetIndex(&globalCtx->objectCtx, 0xE7);
    if (objIndex >= 0) {
        if (Object_IsLoaded(&globalCtx->objectCtx, objIndex)) {
            void* segBackup = gSegments[6];
            gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[objIndex].segment);


            //this->pos.x = PARAMS->pos.x;
            //this->pos.y = PARAMS->pos.y;
            //this->pos.z = PARAMS->pos.z;
            this->pos = PARAMS->pos;
            //this->velocity.x = PARAMS->velocity.x;
            //this->velocity.y = PARAMS->velocity.y;
            //this->velocity.z = PARAMS->velocity.z;
            this->velocity = PARAMS->velocity;
            //this->accel.x = PARAMS->accel.x;
            //this->accel.y = PARAMS->accel.y;
            //this->accel.z = PARAMS->accel.z;
            this->accel = PARAMS->accel;
            this->draw = EffectSsExtra_Draw;
            this->update = EffectSsExtra_Update;
            this->life = 0x32;

            this->regs[2] = PARAMS->scoreIdx;
            this->regs[3] = PARAMS->scale;
            this->regs[1] = 5;
            this->regs[0] = objIndex;

            gSegments[6] = segBackup;
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Extra/EffectSsExtra_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Extra/EffectSsExtra_Update.s")
