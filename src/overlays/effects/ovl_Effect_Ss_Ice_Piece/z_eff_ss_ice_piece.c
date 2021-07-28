/*
 * File: z_eff_ss_ice_piece.c
 * Overlay: ovl_Effect_Ss_Ice_Piece
 * Description:
 */

#include "z_eff_ss_ice_piece.h"

#define PARAMS ((EffectSsIcePieceInitParams*)initParamsx)

s32 EffectSsIcePiece_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsIcePiece_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsIcePiece_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Ice_Piece_InitVars = {
    EFFECT_SS_ICE_PIECE,
    EffectSsIcePiece_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Ice_Piece/EffectSsIcePiece_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Ice_Piece/EffectSsIcePiece_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Ice_Piece/EffectSsIcePiece_Update.s")
