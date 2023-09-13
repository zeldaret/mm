/*
 * File: z_dm_hina.c
 * Overlay: ovl_Dm_Hina
 * Description: Boss mask cutscene objects
 */

#include "z_dm_hina.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmHina*)thisx)

void DmHina_Init(Actor* thisx, PlayState* play);
void DmHina_Destroy(Actor* thisx, PlayState* play);
void DmHina_Update(Actor* thisx, PlayState* play);
void DmHina_Draw(Actor* thisx, PlayState* play);

void func_80A1F470(DmHina* this, PlayState* play);
void func_80A1F56C(DmHina* this, PlayState* play);
void func_80A1F5AC(DmHina* this, PlayState* play);
void func_80A1F63C(DmHina* this, PlayState* play);

ActorInit Dm_Hina_InitVars = {
    ACTOR_DM_HINA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BSMASK,
    sizeof(DmHina),
    (ActorFunc)DmHina_Init,
    (ActorFunc)DmHina_Destroy,
    (ActorFunc)DmHina_Update,
    (ActorFunc)DmHina_Draw,
};

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Init.s")
void DmHina_Init(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    this->unk180 = 1;
    this->actionFunc = func_80A1F470;
    this->unk_158 = this->actor.world.pos.y;
    this->actor.focus.pos.y = this->actor.world.pos.y;
    this->unk148 = 0.0f;
    this->unk_15C = 1.0f;
    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.z = this->actor.world.pos.z;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Destroy.s")
void DmHina_Destroy(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F470.s")
void func_80A1F470(DmHina* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Math_SmoothStepToF(&this->unk148, 0.6f, 0.5f, 0.05f, 0.001f);
    this->unk154 = Math_SinS((s16)(play->gameplayFrames * 0x708)) * 8.0f;
    if ((player->stateFlags1 & 0x400) && (this->actor.xzDistToPlayer < 80.0f)) {
        this->unk180 = 0;
        this->unk154 = 0.0f;
        this->actor.world.pos.y += 40.0f;
        this->actionFunc = func_80A1F56C;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F56C.s")
void func_80A1F56C(DmHina* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == (u8)2) {
        this->unk17C = 2;
        this->actionFunc = func_80A1F5AC;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F5AC.s")
void func_80A1F5AC(DmHina* this, PlayState* play) {
    this->unk17C--;
    if (this->unk17C == 0) {
        this->unk180 = 1;
        Cutscene_StartManual(play, &play->csCtx);
        this->unk17A = Play_CreateSubCamera(play);
        Play_ChangeCameraStatus(play, 0, 1);
        Play_ChangeCameraStatus(play, this->unk17A, 7);
        this->actionFunc = func_80A1F63C;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F63C.s")
void func_80A1F63C(DmHina* this, PlayState* play) {
    this->unk160 = this->actor.world.pos.x + 100.0f;
    this->unk164 = this->unk_158 + 260.0f;
    this->unk168 = this->actor.world.pos.z + 100.0f;
    this->unk16C = this->actor.world.pos.x;
    this->unk174 = this->actor.world.pos.z;
    this->unk170 = this->actor.world.pos.y + (this->unk154 * this->unk_15C) + (40.0f * this->unk_15C);
    Play_SetCameraAtEye(play, this->unk17A, (Vec3f*)&this->unk16C, (Vec3f*)&this->unk160);
    Math_SmoothStepToF(&this->actor.world.pos.y, this->unk_158 + 300.0f, 0.5f, 2.0f, 0.1f);
    if (((this->unk_158 + 240.0f) < this->actor.world.pos.y) && (this->unk17E != 1)) {
        this->unk17E = 1;
        Actor_PlaySfx(&this->actor, 0x580BU);
    }
    Actor_PlaySfx(&this->actor, 0x219BU);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F75C.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Update.s")
void func_80A1F75C(DmHina* this, PlayState* play); /* extern */

void DmHina_Update(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    this->actionFunc(this, play);
    func_80A1F75C(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/func_80A1F9AC.s")
extern UNK_TYPE D_04023348;
extern UNK_TYPE D_04023428;

void func_80A1F9AC(DmHina* this, PlayState* play) {
    GraphicsContext* gfxCtx;
    gfxCtx = play->state.gfxCtx;

    if (this->unk17E != 0) {
        OPEN_DISPS(gfxCtx);

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)(this->unk14C * 100.0f) + 0x9B, this->unk17F);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, (u8)(this->unk150 * 100.0f) + 0x32, 0);
        gSPDisplayList(POLY_XLU_DISP++, &D_04023348);

        Matrix_Translate(this->actor.world.pos.x,
                         this->actor.world.pos.y + (this->unk154 * this->unk_15C) + (40.0f * this->unk_15C),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->unk14C * 20.0f, this->unk14C * 20.0f, this->unk14C * 20.0f, MTXMODE_APPLY);
        Matrix_RotateZF(Rand_ZeroFloat(6.2831855f), MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, &D_04023428);

        CLOSE_DISPS(gfxCtx);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Hina/DmHina_Draw.s")
void DmHina_Draw(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    if ((u8)this->unk180 != 0) {
        Matrix_Translate(this->actor.world.pos.x,
                         this->actor.world.pos.y + (this->unk154 * this->unk_15C) + (40.0f * this->unk_15C),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateZYX(0, (s16)(play->gameplayFrames * 0x3E8), 0, MTXMODE_APPLY);
        Matrix_Scale((this->unk148 * (1.0f - this->unk14C) * this->unk_15C),
                     (this->unk148 * (1.0f - this->unk14C) * this->unk_15C),
                     (this->unk148 * (1.0f - this->unk14C) * this->unk_15C), MTXMODE_APPLY);
        switch (this->actor.params) {
            case 0:
                GetItem_Draw(play, 0x5C);
                break;
            case 1:
                GetItem_Draw(play, 0x63);
                break;
            case 2:
                GetItem_Draw(play, 0x64);
                break;
            case 3:
                GetItem_Draw(play, 0x65);
                break;
        }
        func_80A1F9AC(this, play);
    }
}
