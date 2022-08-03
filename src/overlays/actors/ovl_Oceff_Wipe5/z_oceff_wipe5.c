/*
 * File: z_oceff_wipe5.c
 * Overlay: ovl_Oceff_Wipe5
 * Description: Sonata/Lullaby/Bossa Nova/Elegy/Oath Ocarina Effect
 */

#include "z_oceff_wipe5.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe5*)thisx)

void OceffWipe5_Init(Actor* thisx, PlayState* play);
void OceffWipe5_Destroy(Actor* thisx, PlayState* play);
void OceffWipe5_Update(Actor* thisx, PlayState* play);
void OceffWipe5_Draw(Actor* thisx, PlayState* play);

#if 0
const ActorInit Oceff_Wipe5_InitVars = {
    ACTOR_OCEFF_WIPE5,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe5),
    (ActorFunc)OceffWipe5_Init,
    (ActorFunc)OceffWipe5_Destroy,
    (ActorFunc)OceffWipe5_Update,
    (ActorFunc)OceffWipe5_Draw,
};

#endif

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Init.s")

void OceffWipe5_Init(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->unk144 = 0;
    this->actor.world.pos = play->cameraPtrs[play->activeCamId]->eye;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Destroy.s")

void OceffWipe5_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;

    func_80115D5C(&play->state);
    play->msgCtx.unk120B0 = 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Update.s")

void OceffWipe5_Update(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->unk144 < 100) {
        this->unk144++;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Draw.s")
extern Gfx* D_80BC9080;
extern AnimatedMaterial D_80BC7F18;
extern Color_RGBA8 D_80BC9198;
extern Color_RGBA8 D_80BC9188;
extern Vtx D_80BC8F90[22];
extern Vtx D_80BC9090[22];

void OceffWipe5_Draw(Actor* thisx, PlayState* play) {
    f32 z;
    f32 sp58;
    Vec3f sp48;
    s32 sp40;
    f32 sp3C;
    GraphicsContext* sp38;
    Gfx* sp30;
    s32* temp_v0_3;
    Camera* temp_t0;
    Gfx* temp_v0_4;
    Gfx* temp_v0_5;
    Gfx* temp_v0_6;
    Gfx* temp_v0_7;
    s16 temp_a1;
    s32 params;
    s32 temp_v1;
    u16 temp_v0_2;
    void* temp_v1_2;
    void* temp_v1_3;
    s32 phi_v1;
    f32 phi_fv1;
    s16 phi_a1;
    u8 alpha;
    s32 temp_v0;
    s32* phi_v0;
    Vec3f activeCamEye;
    Vec3f quakeOffset;
    s32 i;
    Color_RGBA8* primColor;
    Color_RGBA8* envColor;
    Vtx* test;
    s32 counter;
    OceffWipe5* this = (OceffWipe5*)thisx;

    activeCamEye = GET_ACTIVE_CAM(play)->eye;
    params = this->actor.params & 0xF;
    temp_v0 = this->actor.params & 0xF;
    temp_v1 = temp_v0 * 3;
    phi_fv1 = 1220.0f;
    if ((params == 2) && (play->sceneNum == 0x2F) &&
        ((play->csCtx.currentCsIndex == 0) || (play->csCtx.currentCsIndex == 1)) && (play->csCtx.state != 0)) {
        phi_fv1 = 1150.0f;
    }
    if (phi_fv1 >= 13) {
        temp_v1 = 0;
    }
    // sp40 = phi_v1;
    // sp3C = phi_fv1;
    Camera_GetQuakeOffset(&quakeOffset, play->cameraPtrs[play->activeCamId]);
    //    phi_a1 = this->unk144;

    if (this->unk144 < 32) {
        // sp3C = sp3C;
        counter = this->unk144;
        z = Math_SinS((s16)(counter << 9)) * phi_fv1;
        // phi_a1 = this->unk144;
    } else {
        z = phi_fv1;
    }
    // phi_v0 = &D_80BC8F90;
    phi_v0 = &D_80BC8F90;
    if (this->unk144 >= 80) {
        alpha = ((this->unk144 * -0xC) + 0x4B0) & 255;
    } else {
        alpha = 255;
    }

    test = &D_80BC8F90;
    /*
    *D_80BC8F3F = alpha;
    *D_80BC8F5F = alpha;
    *D_80BC8F7F = alpha;
    do {
        temp_v0_3 = phi_v0 + 0x80;
        temp_v0_3->unk-51 = alpha;
        temp_v0_3->unk-31 = alpha;
        temp_v0_3->unk-11 = alpha;
        temp_v0_3->unk-71 = alpha;
        phi_v0 = temp_v0_3;
    } while (temp_v0_3 != &D_80BC9090);
*/
    for (i = 1; i < ARRAY_COUNT(D_80BC9090); i += 2) {
        D_80BC9090[i].v.cn[3] = alpha;
    }

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    Matrix_Translate(activeCamEye.x + quakeOffset.x, activeCamEye.y + quakeOffset.y, activeCamEye.z + quakeOffset.z,
                     MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);
    // temp_v0_4 = sp38->polyXlu.p;
    // sp38->polyXlu.p = temp_v0_4 + 8;
    // temp_v0_4->words.w0 = 0xDA380003;
    // sp30 = temp_v0_4;
    // sp30->words.w1 = Matrix_NewMtx(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    // temp_v0_5 = sp38->polyXlu.p;
    // sp38->polyXlu.p = temp_v0_5 + 8;
    // temp_v1_2 = sp40 + &D_80BC9188;
    // temp_v0_5->words.w0 = 0xFA000080;
    // temp_v0_5->words.w1 = (temp_v1_2->unk2 << 8) | (temp_v1_2->unk0 << 0x18) | (temp_v1_2->unk1 << 0x10) | 0xFF;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, primColor->r, primColor->g, primColor->b, 255);
    // temp_v0_6 = sp38->polyXlu.p;
    // sp38->polyXlu.p = temp_v0_6 + 8;
    envColor = sp40 + &D_80BC9198;
    // temp_v0_6->words.w0 = 0xFB000000;
    // temp_v0_6->words.w1 = (temp_v1_3->unk2 << 8) | (temp_v1_3->unk0 << 0x18) | (temp_v1_3->unk1 << 0x10) | 0xFF;
    //gDPSetEnvColor(POLY_XLU_DISP++, envColor->r, envColor->g, envColor->b, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, envColor->r, envColor->g, envColor->b, 255);
    AnimatedMat_Draw(play, &D_80BC7F18);
    // temp_v0_7 = sp38->polyXlu.p;
    // sp38->polyXlu.p = temp_v0_7 + 8;
    // temp_v0_7->words.w1 = (u32) &D_80BC9080;
    // temp_v0_7->words.w0 = 0xDE000000;
    gSPDisplayList(POLY_XLU_DISP++, &D_80BC9080);

    CLOSE_DISPS(play->state.gfxCtx);
}
