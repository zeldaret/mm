#include "z_oceff_wipe6.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe6*)thisx)

void OceffWipe6_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Oceff_Wipe6_InitVars = {
    ACTOR_OCEFF_WIPE6,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe6),
    (ActorFunc)OceffWipe6_Init,
    (ActorFunc)OceffWipe6_Destroy,
    (ActorFunc)OceffWipe6_Update,
    (ActorFunc)OceffWipe6_Draw,
};

#endif

extern void func_800E01B8(Vec3f*, Camera*);
extern AnimatedMaterial D_80BCA8D8;
extern Vtx D_80BCA8E0;
extern u8 D_80BCA8FF; // 0x35F (vtx[1].alpha)
extern u8 D_80BCA91F; // 0x37F (vtx[3].alpha)
extern u8 D_80BCA93F; // 0x39F (vtx[5].alpha
extern s16 D_80BCA950; // 0x3B0 (vtx[7].x)
extern Gfx D_80BCAA40;
extern Gfx D_80BCAA50; // 0x4B0 SetCombine

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Init.s")
void OceffWipe6_Init(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe6* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->counter = 0;
    this->actor.world.pos = ACTIVE_CAM->eye;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Destroy.s")
void OceffWipe6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    func_80115D5C(globalCtx);
    globalCtx->msgCtx.pad12080[0x30] = 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Update.s")
void OceffWipe6_Update(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe6* this = THIS;

    this->actor.world.pos = ACTIVE_CAM->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Draw.s")
void OceffWipe6_Draw(Actor* thisx, GlobalContext* globalCtx) { /* 2582 */
    s32 _pad;
    OceffWipe6* this = THIS;
    f32 z;
    u8 alpha;
    s32 pad[2];
    Vec3f eye;
    Vtx* vtxPtr;
    Vec3f vec;

    eye = ACTIVE_CAM->eye;
    func_800E01B8(&vec, ACTIVE_CAM);

    if (this->counter < 32) {
        z = Math_SinS(this->counter << 0x19) * 1220.f;
    } else {
        z = 1220.0f;
    }

    vtxPtr = &D_80BCA8E0;
    if (this->counter >= 80) {
        alpha = 12 * (1200 - this->counter);
    } else {
        alpha = 0xFF;
    }

    vtxPtr[1].v.cn[3] = vtxPtr[3].v.cn[3] = vtxPtr[5].v.cn[3] = vtxPtr[7].v.cn[3] = alpha;

    func_8012C2DC(globalCtx->state.gfxCtx);
    SysMatrix_InsertTranslation(eye.x + vec.x, eye.y + vec.y, eye.z + vec.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
    SysMatrix_InsertXRotation_s(0x708, 1);
    SysMatrix_InsertTranslation(0.0f, 0.0f, -z, 1);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    AnimatedMat_Draw(globalCtx, &D_80BCA8D8);
    gSPDisplayList(POLY_XLU_DISP++, &D_80BCAA40);
}
