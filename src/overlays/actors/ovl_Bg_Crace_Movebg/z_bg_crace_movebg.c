/*
 * File: z_bg_crace_movebg.c
 * Overlay: ovl_Bg_Crace_Movebg
 * Description: Huge sliding doors in Deku Shrine
 */

#include "z_bg_crace_movebg.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgCraceMovebg*)thisx)

void BgCraceMovebg_Init(Actor* thisx, PlayState* play);
void BgCraceMovebg_Destroy(Actor* thisx, PlayState* play);
void BgCraceMovebg_Update(Actor* thisx, PlayState* play);
void BgCraceMovebg_Draw(Actor* thisx, PlayState* play);

s32 func_80A7090C(PlayState* play);
void func_80A70970(BgCraceMovebg* this, PlayState* play);
void func_80A7099C(BgCraceMovebg* this, PlayState* play);
void func_80A709E4(BgCraceMovebg* this, PlayState* play);
void func_80A70A08(BgCraceMovebg* this, PlayState* play);
void func_80A70A84(BgCraceMovebg* this, PlayState* play);
void func_80A70A9C(BgCraceMovebg* this, PlayState* play);
void func_80A70C04(BgCraceMovebg* this, PlayState* play);
void func_80A70D74(BgCraceMovebg* this, PlayState* play);
void func_80A70DA8(BgCraceMovebg* this, PlayState* play);
void func_80A70E2C(BgCraceMovebg* this, PlayState* play);
void func_80A70E70(BgCraceMovebg* this, PlayState* play);
void func_80A70F14(BgCraceMovebg* this, PlayState* play);
void func_80A70F2C(BgCraceMovebg* this, PlayState* play);
void func_80A70FF4(BgCraceMovebg* this, PlayState* play);
void func_80A71040(BgCraceMovebg* this, PlayState* play);

const ActorInit Bg_Crace_Movebg_InitVars = {
    ACTOR_BG_CRACE_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_CRACE_OBJECT,
    sizeof(BgCraceMovebg),
    (ActorFunc)BgCraceMovebg_Init,
    (ActorFunc)BgCraceMovebg_Destroy,
    (ActorFunc)BgCraceMovebg_Update,
    (ActorFunc)BgCraceMovebg_Draw,
};

static u8 D_80A710A0 = 0;
static u8 D_80A710A4 = 0;
static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};
static Vec3f D_80A710AC[] = { 0.0f, 0.0f, 1.0f };
u8 D_80A711B0[32];

void BgCraceMovebg_Init(Actor* thisx, PlayState* play) {
    BgCraceMovebg* this = THIS;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    if (D_80A710A0 == 0) {
        for (i = 0; i < ARRAY_COUNT(D_80A711B0); i++) {
            D_80A711B0[i] = 0;
        }
        D_80A710A0 = 1;
    }

    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_crace_object_Colheader_000E00);

    this->unk184 = this->dyna.actor.world.rot.x;
    this->unk16C = this->dyna.actor.world.rot.z;
    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.world.rot.z = 0;
    this->dyna.actor.home.rot.x = 0;
    this->dyna.actor.home.rot.z = 0;
    this->dyna.actor.flags |= ACTOR_FLAG_10000000;

    switch (BGCRACEMOVEBG_GET_F(&this->dyna.actor)) {
        case 0:
        case 2:
            for (j = 0; j < D_80A710A4; j++) {
                if (D_80A711B0[j] == this->unk184) {
                    this->unk170 |= 8;
                    Actor_MarkForDeath(&this->dyna.actor);
                    return;
                }
            }
            if (D_80A710A4 < ARRAY_COUNT(D_80A711B0)) {
                D_80A711B0[(s32)D_80A710A4++] = this->unk184;
            }
            this->dyna.actor.room = -1;
            switch (func_80A7090C(play)) {
                case 0:
                    func_80A70D74(this, play);
                    break;
                case 1:
                    func_80A70D74(this, play);
                    break;
                case 2:
                    Flags_UnsetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor) + 1);
                    func_80A70D74(this, play);
                    break;
            }
            break;
        case 1:
            func_80A70970(this, play);
            break;
        default:
            Actor_MarkForDeath(&this->dyna.actor);
            break;
    }
}

s32 func_80A7090C(PlayState* play) {
    s32 pad;
    s32 returnVal = 0;
    Actor* tempActor = SubS_FindActor(play, NULL, ACTORCAT_NPC, ACTOR_EN_DNO);

    if (tempActor != NULL) {
        if (Flags_GetSwitch(play, BGCRACEMOVEBG_GET_3F80(tempActor))) {
            returnVal = 2;
        } else {
            returnVal = 1;
        }
    }
    return returnVal;
}

void func_80A70970(BgCraceMovebg* this, PlayState* play) {
    this->unk164 = 0.0f;
    this->unk160 = 0.0f;
    this->actionFunc = func_80A7099C;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
}

void func_80A7099C(BgCraceMovebg* this, PlayState* play) {
    if (Flags_GetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor))) {
        func_80A709E4(this, play);
    }
}

void func_80A709E4(BgCraceMovebg* this, PlayState* play) {
    this->actionFunc = func_80A70A08;
    this->unk164 = 180.0f;
}

void func_80A70A08(BgCraceMovebg* this, PlayState* play) {
    func_800B9010(&this->dyna.actor, NA_SE_EV_STONEDOOR_OPEN_S - SFX_FLAG);
    Math_SmoothStepToF(&this->unk160, this->unk164, 2.0f, this->unk16C, 0.01f);
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->unk160;
    if (this->unk160 == this->unk164) {
        func_80A70A84(this, play);
    }
}

void func_80A70A84(BgCraceMovebg* this, PlayState* play) {
    this->actionFunc = func_80A70A9C;
}

void func_80A70A9C(BgCraceMovebg* this, PlayState* play) {
}

void BgCraceMovebg_Destroy(Actor* thisx, PlayState* play) {
    BgCraceMovebg* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    if (!(this->unk170 & 0x8)) {
        switch (BGCRACEMOVEBG_GET_F(&this->dyna.actor)) {
            case 0:
            case 2:
                Flags_UnsetSwitch(play, BGCRACEMOVEBG_GET_7F0(thisx));
                Flags_UnsetSwitch(play, BGCRACEMOVEBG_GET_7F0(thisx) + 1);
                break;
            case 1:
                Flags_UnsetSwitch(play, BGCRACEMOVEBG_GET_7F0(thisx));
                break;
        }
    }
}

void BgCraceMovebg_Update(Actor* thisx, PlayState* play) {
    BgCraceMovebg* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(play);
    s16 tempRot;

    switch (BGCRACEMOVEBG_GET_F(&this->dyna.actor)) {
        case 0:
        case 2:
            tempRot = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.home.rot.y;
            if ((tempRot >= -0x4000) && (tempRot <= 0x4000)) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.home.rot.y;
            } else {
                this->dyna.actor.shape.rot.y = this->dyna.actor.home.rot.y + 0x8000;
            }
        default:
            this->actionFunc(this, play);
            Math_Vec3f_Copy(&this->unk188, &player->bodyPartsPos[0]);
    }
}

void func_80A70C04(BgCraceMovebg* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);
    Vec3f intersect;
    Vec3f diff;

    if ((BGCRACEMOVEBG_GET_F(&this->dyna.actor) != 2) &&
        SubS_LineSegVsPlane(&this->dyna.actor.home.pos, &this->dyna.actor.home.rot, D_80A710AC, &this->unk188,
                            &player->bodyPartsPos[0], &intersect)) {
        Matrix_RotateYS(-this->dyna.actor.home.rot.y, MTXMODE_NEW);
        Math_Vec3f_Diff(&player->bodyPartsPos[0], &this->dyna.actor.home.pos, &diff);
        Matrix_MultVec3f(&diff, &this->unk178);
        if (fabsf(this->unk178.x) < 100.0f && this->unk178.y >= -10.0f && this->unk178.y <= 180.0f) {
            if (this->unk178.z < 0.0f) {
                Flags_SetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor) + 1);
                this->unk170 |= 2;
            } else {
                Flags_UnsetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor) + 1);
                this->unk170 &= ~2;
            }
        }
    }
}

void func_80A70D74(BgCraceMovebg* this, PlayState* play) {
    this->unk164 = 180.0f;
    this->unk160 = 180.0f;
    this->actionFunc = func_80A70DA8;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 180.0f;
}

void func_80A70DA8(BgCraceMovebg* this, PlayState* play) {
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->unk160;
    func_80A70C04(this, play);
    if (this->unk170 & 1) {
        func_80A70E2C(this, play);
    }
    if (Flags_GetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor))) {
        func_80A70F14(this, play);
    }
}

void func_80A70E2C(BgCraceMovebg* this, PlayState* play) {
    this->unk174 = BGCRACEMOVEBG_GET_F800(&this->dyna.actor) * 10;
    this->unk164 = 180.0f;
    this->unk160 = 180.0f;
    this->actionFunc = func_80A70E70;
}

void func_80A70E70(BgCraceMovebg* this, PlayState* play) {
    if (this->unk174 > 0) {
        this->unk174--;
    }
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->unk160;
    func_80A70C04(this, play);
    if (this->unk174 <= 0) {
        this->unk160 = 180.0f;
        this->unk164 = 0.0f;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 180.0f;
        Flags_SetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor));
        func_80A70F14(this, play);
    }
}

void func_80A70F14(BgCraceMovebg* this, PlayState* play) {
    this->actionFunc = func_80A70F2C;
}

void func_80A70F2C(BgCraceMovebg* this, PlayState* play) {
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->unk160;
    func_80A70C04(this, play);
    if (Math_StepToF(&this->unk160, 0.0f, 1.0f)) {
        if (!(this->unk170 & 2) && !Flags_GetSwitch(play, BGCRACEMOVEBG_GET_7F0(&this->dyna.actor) + 1)) {
            play->unk_18845 = 1;
            func_80169FDC(&play->state);
            play_sound(NA_SE_OC_ABYSS);
        }
        func_80A70FF4(this, play);
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_STONEDOOR_CLOSE_S - SFX_FLAG);
    }
}

void func_80A70FF4(BgCraceMovebg* this, PlayState* play) {
    this->unk164 = 0.0f;
    this->unk160 = 0.0f;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_STONEDOOR_STOP);
    this->actionFunc = func_80A71040;
}

void func_80A71040(BgCraceMovebg* this, PlayState* play) {
}

void BgCraceMovebg_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, object_crace_object_DL_0003A0);
}
