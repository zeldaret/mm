/*
 * File: z_demo_moonend.c
 * Overlay: ovl_Demo_Moonend
 * Description: Moon Disappearing (cutscene)
 */

#include "z_demo_moonend.h"
#include "objects/object_moonend/object_moonend.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoMoonend*)thisx)

void DemoMoonend_Init(Actor* thisx, PlayState* play);
void DemoMoonend_Destroy(Actor* thisx, PlayState* play);
void DemoMoonend_Update(Actor* thisx, PlayState* play);
void DemoMoonend_Draw(Actor* thisx, PlayState* play);

void func_80C17B50(DemoMoonend* this, PlayState* play);
void func_80C17B60(DemoMoonend* this, PlayState* play);
void func_80C17C48(DemoMoonend* this, PlayState* play);

const ActorInit Demo_Moonend_InitVars = {
    ACTOR_DEMO_MOONEND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MOONEND,
    sizeof(DemoMoonend),
    (ActorFunc)DemoMoonend_Init,
    (ActorFunc)DemoMoonend_Destroy,
    (ActorFunc)DemoMoonend_Update,
    (ActorFunc)DemoMoonend_Draw,
};

extern UNK_TYPE D_06001214;
extern UNK_TYPE D_0600B540;
extern UNK_TYPE D_0600B5A0;
extern UNK_TYPE D_060129F0;
extern Gfx D_06010C40[];

void DemoMoonend_Init(Actor* thisx, PlayState* play) {
    DemoMoonend* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    this->actionFunc = func_80C17B50;

    if ((this->actor.params & 0xF) == 1) {
        Actor_SetScale(&this->actor, 0.05f);
        Actor_SetScale(&this->actor, 6.0f);
        this->actor.draw = NULL;
        this->unk_2DC = 0x22E;
        this->actionFunc = func_80C17B60;
    } else {
        Actor_SetScale(&this->actor, 0.095f);
        func_80183430(&this->skelInfo, &D_0600B5A0, &D_06001214, this->unk_174, &this->unk_228[0].x, NULL);
        func_801834A8(&this->skelInfo, &D_06001214);
        this->unk_2DC = 0x230;
        this->actionFunc = func_80C17C48;
        this->actor.home.rot.z = 0;
        this->actor.draw = NULL;
        this->skelInfo.frameCtrl.unk_C = 0.6666667f;
    }
}

void DemoMoonend_Destroy(Actor* thisx, PlayState* play) {
    DemoMoonend* this = THIS;

    if ((this->actor.params & 0xF) != 1) {
        func_8018349C(&this->skelInfo);
    }
}

void func_80C17B50(DemoMoonend* this, PlayState* play) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Demo_Moonend/func_80C17C48.s")

void DemoMoonend_Update(Actor* thisx, PlayState* play) {
    DemoMoonend* this = THIS;

    this->actionFunc(this, play);
}

s32 func_80C17E70(PlayState* play, SkeletonInfo* skeletonInfo, s32 limbIndex, Gfx** dList, u8* flags, Actor* thisx,
                  Vec3f* scale, Vec3s* rot, Vec3f* pos) {
    DemoMoonend* this = THIS;

    if (limbIndex == 2) {
        Matrix_Push();
        Matrix_RotateYS(Camera_GetCamDirYaw(play->cameraPtrs[play->activeCamera]) + 0x8000, MTXMODE_APPLY);
    }

    return true;
}

s32 func_80C17EE0(PlayState* play, SkeletonInfo* skeleton, s32 limbIndex, Gfx** dList, u8* flags, Actor* thisx,
                  Vec3f* scale, Vec3s* rot, Vec3f* pos) {
    DemoMoonend* this = THIS;

    if (limbIndex == 8) {
        Matrix_Pop();
    }

    return 1;
}

void DemoMoonend_Draw(Actor* thisx, PlayState* play) {
    DemoMoonend* this = THIS;
    Mtx* mtx;

    AnimatedMat_Draw(play, (AnimatedMaterial*)Lib_SegmentedToVirtual(&D_0600B540));

    mtx = GRAPH_ALLOC(play->state.gfxCtx, ALIGN16(this->skelInfo.unk_18->unk_1 * sizeof(Mtx)));

    if (mtx != NULL) {
        func_8012C2DC(play->state.gfxCtx);
        func_8012C28C(play->state.gfxCtx);
        func_8018450C(play, &this->skelInfo, mtx, func_80C17E70, func_80C17EE0, &this->actor);
    }
}

void func_80C17FCC(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(&D_060129F0));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06010C40);

    CLOSE_DISPS(play->state.gfxCtx);
}
