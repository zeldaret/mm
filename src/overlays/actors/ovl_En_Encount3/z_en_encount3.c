/*
 * File: z_en_encount3.c
 * Overlay: ovl_En_Encount3
 * Description: Garo spawner
 */

#include "z_en_encount3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_CANT_LOCK_ON)

#define THIS ((EnEncount3*)thisx)

void EnEncount3_Init(Actor* thisx, PlayState* play);
void EnEncount3_Destroy(Actor* thisx, PlayState* play);
void EnEncount3_Update(Actor* thisx, PlayState* play);
void EnEncount3_Draw(Actor* thisx, PlayState* play);

void func_809AD058(EnEncount3* this);

void func_809AD084(EnEncount3* this, PlayState* play);
void func_809AD194(EnEncount3* this, PlayState* play);
void func_809AD1EC(EnEncount3* this, PlayState* play);

ActorInit En_Encount3_InitVars = {
    ACTOR_EN_ENCOUNT3,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIG_FWALL,
    sizeof(EnEncount3),
    (ActorFunc)EnEncount3_Init,
    (ActorFunc)EnEncount3_Destroy,
    (ActorFunc)EnEncount3_Update,
    (ActorFunc)EnEncount3_Draw,
};

u32 D_809AD810 = false;

extern UNK_TYPE D_060009A0;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Init.s")
void EnEncount3_Init(Actor* thisx, PlayState* play) {
    EnEncount3* this = THIS;

    this->unk14A = (this->actor.params >> 0xC) & 0xF;
    this->unk158 = (this->actor.params >> 7) & 0x1F;
    this->unk15C = this->actor.params & 0x7F;
    this->unk15A = this->actor.csId;
    this->unk16C = this->actor.world.rot.z * 10.0f;
    if (this->unk16C < 10.0f) {
        this->unk16C = 10.0f;
    } else if (this->unk16C > 1000.0f) {
        this->unk16C = 1000.0f;
    }
    if (this->unk15C == 0x7F) {
        this->unk15C = -1;
    }
    if ((this->unk15C >= 0) && (Flags_GetSwitch(play, this->unk15C) != 0)) {
        Actor_Kill(&this->actor);
    }
    this->actor.flags |= 0x08000000;
    this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    func_809AD058(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Destroy.s")
void EnEncount3_Destroy(Actor* thisx, PlayState* play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD058.s")
void func_809AD058(EnEncount3* this) {
    this->unk154 = 0x113;
    this->unk150 = 1;
    this->unk15E = 0x1E;
    this->actionFunc = func_809AD084;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD084.s")
void func_809AD084(EnEncount3* this, PlayState* play) {
    if ((this->unk15C >= 0) && (Flags_GetSwitch(play, this->unk15C) != 0)) {
        Actor_Kill(&this->actor);
        return;
    }
    if (!(this->unk16C < this->actor.xzDistToPlayer) && (Player_GetMask(play) == 6) && (!D_809AD810)) {
        if (this->unk15E > 0) {
            this->unk15E--;
            return;
        }
        this->unk17C = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, this->unk154, this->actor.world.pos.x,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, this->unk158);
        if (this->unk17C != NULL) {
            this->unk14E++;
            D_809AD810 = true;
            this->actionFunc = func_809AD194;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD194.s")
void func_809AD194(EnEncount3* this, PlayState* play) {
    if (this->unk14E == 0) {
        this->unk178 = 0.0f;
        if (this->unk15C >= 0) {
            Flags_SetSwitch(play, this->unk15C);
        }
        this->actionFunc = func_809AD1EC;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD1EC.s")
void func_809AD1EC(EnEncount3* this, PlayState* play) {
    if (this->unk174 < 0.002f) {
        D_809AD810 = false;
        Actor_Kill(&this->actor);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Update.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Draw.s")
void EnEncount3_Draw(Actor* thisx, PlayState* play) {
    EnEncount3* this = THIS;
    s32 pad;

    if (this->unk170 > 0.0f) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        Matrix_Push();

        gDPPipeSync(POLY_XLU_DISP++);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, (s32)play->gameplayFrames, 0U, 0x20, 0x40, 1,
                                    (s32)play->gameplayFrames * -2, (s32)play->gameplayFrames * -8, 0x20, 0x20));

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 200, 0, (s8)this->unk170);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 128);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y - 40.0f, this->actor.world.pos.z,
                         MTXMODE_NEW);
        Matrix_Scale(this->unk168, this->unk174, this->unk168, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, &D_060009A0);

        Matrix_Pop();
        CLOSE_DISPS(play->state.gfxCtx);
    }
}
