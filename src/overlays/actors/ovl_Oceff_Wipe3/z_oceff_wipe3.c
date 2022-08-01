/*
 * File: z_oceff_wipe3.c
 * Overlay: ovl_Oceff_Wipe3
 * Description: Unused OoT Saria's Song Ocarina Effect
 */

#include "prevent_bss_reordering.h"
#include "z_oceff_wipe3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe3*)thisx)

void OceffWipe3_Init(Actor* thisx, PlayState* play);
void OceffWipe3_Destroy(Actor* thisx, PlayState* play);
void OceffWipe3_Update(Actor* thisx, PlayState* play);
void OceffWipe3_Draw(Actor* thisx, PlayState* play);

#if 0
const ActorInit Oceff_Wipe3_InitVars = {
    ACTOR_OCEFF_WIPE3,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe3),
    (ActorFunc)OceffWipe3_Init,
    (ActorFunc)OceffWipe3_Destroy,
    (ActorFunc)OceffWipe3_Update,
    (ActorFunc)OceffWipe3_Draw,
};
u8 D_80988E2F[0x1F] = {
    0xFF, 0, 0x8F, 0, 0x2E, 0, 0,    0, 0, 4, 0xCD, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    1, 0x2C, 0, 0,    3, 0xE8, 0, 0, 4, 0,    0, 0, 0xFF, 0xFF,
};
u8 D_80988E4F[0x1F] = {
    0xFF, 0, 0,    0, 0x96, 0, 0,    0, 0, 8, 0,    8, 0, 0xFF, 0xFF, 0xFF,
    0,    0, 0x5D, 1, 0x1D, 3, 0xE8, 0, 0, 7, 0x33, 0, 0, 0xFF, 0xFF,
};
u8 D_80988E6F[0x1F] = {
    0xFF, 0xFF, 0xA8, 0, 0x79, 0, 0,    0, 0, 9, 0x9A, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    0xFF, 0xA3, 1, 0x1D, 3, 0xE8, 0, 0, 8, 0xCD, 0, 0, 0xFF, 0xFF,
};
u8 D_80988E8F[0x1F] = {
    0xFF, 0xFF, 0x71, 0, 0x2E, 0, 0,    0, 0, 0xB, 0x33, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    0xFF, 0xD,  0, 0xB0, 3, 0xE8, 0, 0, 0xA, 0x66, 0, 0, 0xFF, 0xFF,
};
u8 D_80988EAF[0x1F] = {
    0xFF, 0xFF, 0x71, 0xFF, 0xD2, 0, 0,    0, 0, 0xC, 0xCD, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    0xFE, 0xD4, 0,    0,    3, 0xE8, 0, 0, 0xC, 0,    0, 0, 0xFF, 0xFF,
};
u8 D_80988ECF[0x1F] = {
    0xFF, 0xFF, 0xA8, 0xFF, 0x87, 0, 0,    0, 0, 0xE, 0x66, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    0xFF, 0xD,  0xFF, 0x50, 3, 0xE8, 0, 0, 0xD, 0x9A, 0, 0, 0xFF, 0xFF,
};
u8 D_80988EEF[0x1F] = {
    0xFF, 0,    0,    0xFF, 0x6A, 0, 0,    0, 0, 0x10, 0,    8, 0, 0xFF, 0xFF, 0xFF,
    0,    0xFF, 0xA3, 0xFE, 0xE3, 3, 0xE8, 0, 0, 0xF,  0x33, 0, 0, 0xFF, 0xFF,
};
u8 D_80988F0F[0x1F] = {
    0xFF, 0, 0x58, 0xFF, 0x87, 0, 0,    0, 0, 1, 0x9A, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    0, 0x5D, 0xFE, 0xE3, 3, 0xE8, 0, 0, 0, 0xCD, 0, 0, 0xFF, 0xFF,
};
u8 D_80988F2F[0x1F] = {
    0xFF, 0, 0,    0xFF, 0x6A, 0, 0,    0, 0, 0,    0,    8, 0, 0xFF, 0xFF, 0xFF,
    0,    0, 0x5D, 0xFE, 0xE3, 3, 0xE8, 0, 0, 0x10, 0xCD, 0, 0, 0xFF, 0xFF,
};
u8 D_80988F4F[0x1F] = {
    0xFF, 0, 0x8F, 0xFF, 0xD2, 0, 0,    0, 0, 3, 0x33, 8, 0, 0xFF, 0xFF, 0xFF,
    0,    0, 0xF3, 0xFF, 0x50, 3, 0xE8, 0, 0, 2, 0x66, 0, 0, 0xFF, 0xFF,
};

s32 D_80988F70 = -0x19000000;
s32 D_80988FF8 = 0x0101602C;
#endif

extern Vtx D_80988E10[];
extern Vtx D_80988E4F[];
extern u8 D_80988E6F[];
extern u8 D_80988E8F[];
extern u8 D_80988EAF[];
extern u8 D_80988ECF[];
extern Vtx D_80988EEF[];
//extern u8 D_80988F0F[];
extern u8 D_80988F2F[];
extern u8 D_80988F4F[];
extern u8 D_80988F6F;
extern UNK_TYPE D_80988F70;
extern UNK_TYPE D_80988FF8;
extern Vtx D_80988F0F[];
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe3/OceffWipe3_Init.s")

void OceffWipe3_Init(Actor* thisx, PlayState* play) {
    OceffWipe3* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    this->counter = 0;
    this->actor.world.pos = play->cameraPtrs[play->activeCamId]->eye;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe3/OceffWipe3_Destroy.s")

void OceffWipe3_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe3* this = THIS;

    func_80115D5C(&play->state);
    play->msgCtx.unk120B0 = 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe3/OceffWipe3_Update.s")

void OceffWipe3_Update(Actor* thisx, PlayState* play) {
    OceffWipe3* this = (OceffWipe3*)thisx;

    this->actor.world.pos = play->cameraPtrs[play->activeCamId]->eye;
    if (this->counter < 0x64) {
        this->counter++;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe3/OceffWipe3_Draw.s")

void OceffWipe3_Draw(Actor *thisx, PlayState *play) {
    u32 spA4 = play->state.frames & 0xFFF;
    OceffWipe3 *this = (OceffWipe3 *) thisx;
    f32 z;  
    u8 alpha;
    s32 pad[2];
    Vec3f eye;
    Vtx* vtxPtr;
    Vec3f vec;
    
    eye = GET_ACTIVE_CAM(play)->eye;
    Camera_GetQuakeOffset(&vec, GET_ACTIVE_CAM(play));

    vtxPtr = D_80988E10;
    if (this->counter < 0x20) {
        z = Math_SinS(this->counter << 9) * 1220.0f;
    } else {
        z = 1220.0f;
    }
    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 255;
    }
    vtxPtr[1].v.cn[3] = vtxPtr[3].v.cn[3] = vtxPtr[5].v.cn[3] = vtxPtr[7].v.cn[3] = vtxPtr[9].v.cn[3] =
        vtxPtr[11].v.cn[3] = vtxPtr[13].v.cn[3] = vtxPtr[15].v.cn[3] = vtxPtr[17].v.cn[3] = vtxPtr[19].v.cn[3] =
            vtxPtr[21].v.cn[3] = alpha;
    //temp_a0 = play->state.gfxCtx;
    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    Matrix_Translate(eye.x + vec.x, eye.y+ vec.y, eye.z + vec.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);
    //temp_v0_2 = temp_s0_2->polyXlu.p;
    //temp_s0_2->polyXlu.p = temp_v0_2 + 8;
    //temp_v0_2->words.w0 = 0xDA380003;
    //sp68 = temp_v0_2;
    //sp68->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    //temp_v0_3 = temp_s0_2->polyXlu.p;
    //temp_s0_2->polyXlu.p = temp_v0_3 + 8;
    //temp_v0_3->words.w1 = -0x5501U;
    //temp_v0_3->words.w0 = 0xFA000000;
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 170, 255);
    //temp_v0_4 = temp_s0_2->polyXlu.p;
    //temp_s0_2->polyXlu.p = temp_v0_4 + 8;
    //temp_v0_4->words.w1 = 0x64C80080;
    //temp_v0_4->words.w0 = temp_v0_3->words.w1 = -0x5501U;
    gDPSetEnvColor(POLY_XLU_DISP++, 100, 200, 0, 128);
    //temp_v0_5 = temp_s0_2->polyXlu.p;
    //temp_s0_2->polyXlu.p = temp_v0_5 + 8;
    //temp_v0_5->words.w1 = (u32) &D_80988F70;
    //temp_v0_5->words.w0 = 0xDE000000;
    gSPDisplayList(POLY_XLU_DISP++, (u32) &D_80988F70);
    //temp_v0_6 = temp_s0_2->polyXlu.p;
    //temp_s0_2->polyXlu.p = temp_v0_6 + 8;
    //temp_v0_6->words.w0 = 0xDE000000;
    //sp58 = temp_v0_6;
    //sp58->words.w1 = Gfx_TwoTexScroll(play->state.gfxCtx, 0, spA4 * 0xC, spA4 * -0xC, 0x40, 0x40, 1, spA4 * 8, spA4 * -8, 0x40, 0x40);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(play->state.gfxCtx, 0, spA4 * 0xC, spA4 * -0xC, 0x40, 0x40, 1, spA4 * 8, spA4 * -8, 0x40, 0x40));
    //temp_v0_7 = temp_s0_2->polyXlu.p;
    //temp_s0_2->polyXlu.p = temp_v0_7 + 8;
    //temp_v0_7->words.w1 = (u32) &D_80988FF8;
    //temp_v0_7->words.w0 = 0xDE000000;
    gSPDisplayList(POLY_XLU_DISP++, (u32) &D_80988FF8);
    CLOSE_DISPS(play->state.gfxCtx);
}