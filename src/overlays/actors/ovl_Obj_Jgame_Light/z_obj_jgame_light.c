/*
 * File: z_obj_jgame_light.c
 * Overlay: ovl_Obj_Jgame_Light
 * Description: Fisherman's Jumping Game - Torch
 */

#include "z_obj_jgame_light.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_syokudai/object_syokudai.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjJgameLight*)thisx)

void ObjJgameLight_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C15474(ObjJgameLight* this, GlobalContext* globalCtx);
void func_80C156C4(ObjJgameLight* this, GlobalContext* globalCtx);
void func_80C15718(ObjJgameLight* this, GlobalContext* globalCtx);

const ActorInit Obj_Jgame_Light_InitVars = {
    ACTOR_OBJ_JGAME_LIGHT,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SYOKUDAI,
    sizeof(ObjJgameLight),
    (ActorFunc)ObjJgameLight_Init,
    (ActorFunc)ObjJgameLight_Destroy,
    (ActorFunc)ObjJgameLight_Update,
    (ActorFunc)ObjJgameLight_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0xF6CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 12, 45, 0, { 0, 0, 0 } },
};

#include "assets/overlays/ovl_Obj_Jgame_Light/ovl_Obj_Jgame_Light.c"

void ObjJgameLight_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgameLight* this = THIS;
    LightInfo* lights = &this->lightInfo;

    Actor_SetScale(&this->actor, 1.0f);
    func_800B4AEC(globalCtx, &this->actor, 50.0f);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B4B50, 1.0f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Lights_PointGlowSetInfo(lights, this->actor.world.pos.x, (this->actor.world.pos.y + 70.0f), this->actor.world.pos.z,
                            0xFF, 0xFF, 0xB4, -1);
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    Actor_SetFocus(&this->actor, 60.0f);
    this->actor.colChkInfo.health = 0;
    this->unk_1B8 = 0;
    this->unk_1B6 = 0;
    this->unk_1AC = 0;
    this->unk_1B2 = 0;
    this->unk_1B4 = 0;
    this->unk_1A8 = 0.0f;
}

void ObjJgameLight_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgameLight* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
}

void func_80C15474(ObjJgameLight* this, GlobalContext* globalCtx) {
    u8 temp_a1;

    if (((this->actor.colChkInfo.health & 1) != 0) && (this->unk_1B6 == 0)) {
        if (this->unk_1AC < 0xA0) {
            this->unk_1AC += 0x28;
        } else {
            this->unk_1AC = 0xC8;
            this->unk_1B6 = 1;
        }
        if (this->unk_1A8 < 0.7f) {
            this->unk_1A8 += 0.3f;
        } else {
            this->unk_1A8 = 1.0f;
        }
    } else if ((this->actor.colChkInfo.health & 8) != 0) {
        if (this->unk_1AC >= 0x29) {
            this->unk_1AC -= 0x28;
        } else {
            this->unk_1AC = -1;
            if (this->unk_1A8 == 0.0f) {
                this->unk_1B6 = 0;
                this->actor.colChkInfo.health &= 0xFFFE;
                this->actor.colChkInfo.health &= (s16)0xFFF7;
            }
        }
        if (this->unk_1A8 > 0.3f) {
            this->unk_1A8 -= 0.3f;
        } else {
            this->unk_1A8 = 0.0f;
        }
    }
    if (this->unk_1A8 > 0.1f) {
        func_800B9010(&this->actor, NA_SE_EV_TORCH - SFX_FLAG);
    }
    temp_a1 = (((s32)(Rand_ZeroOne() * 127.0f) + 0x80));
    Lights_PointSetColorAndRadius(&this->lightInfo, temp_a1, (u32)(temp_a1 * 0.7f) & 0xFF, 0, this->unk_1AC);
}

void func_80C156C4(ObjJgameLight* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80C15718(ObjJgameLight* this, GlobalContext* globalCtx) {
    u8 colChk;

    if (((this->actor.colChkInfo.health & 1) != 0) && (((this->unk_1B8) & 1) == 0)) {
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_FLAME_IGNITION);
        this->unk_1B8 = colChk = this->actor.colChkInfo.health;
    }
    if ((this->actor.colChkInfo.health & 2) != 0) {
        this->actor.colChkInfo.health = this->actor.colChkInfo.health & 0xFFFD;
        this->unk_1B2 = 0x12C & 0xFFFF;
        this->unk_1B4 = 1;
    } else if ((this->actor.colChkInfo.health & 4) != 0) {
        this->actor.colChkInfo.health = this->actor.colChkInfo.health & 0xFFFB;
        this->unk_1B2 = 0x12C;
        this->unk_1B4 = 2;
    }
    if (this->unk_1B2 >= 0x10) {
        this->unk_1B2 -= 0xF;
    } else {
        this->unk_1B2 = 0;
    }
}

void ObjJgameLight_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjJgameLight* this = THIS;

    func_80C15718(this, globalCtx);
    func_80C15474(this, globalCtx);
    func_80C156C4(this, globalCtx);
    this->unk_1AE += 1;
}

void ObjJgameLight_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjJgameLight* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, &gObjectSyokudaiTypeSwitchCausesFlameDL);
    if (this->unk_1B2 > 0) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        if (this->unk_1B2 >= 0x100) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 210, 64, 32, 255);
        } else {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 210, 64, 32, this->unk_1B2);
        }
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (this->unk_1B4 == 1) {
            gSPDisplayList(POLY_XLU_DISP++, &D_80C160B0);
        } else if (this->unk_1B4 == 2) {
            gSPDisplayList(POLY_XLU_DISP++, &D_80C16030);
        }
    }
    if (this->unk_1A8 != 0.0f) {
        f32 scale;
        func_8012C2DC(globalCtx->state.gfxCtx);
        scale = (this->unk_1A8 * 27.0f) / 10000.0f;
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, (this->unk_1AE * -0x14) & 0x1FF,
                                    0x20, 0x80));
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 0, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
        Matrix_Translate(0.0f, 52.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateYS(
            ((Camera_GetCamDirYaw(globalCtx->cameraPtrs[globalCtx->activeCamera]) - this->actor.shape.rot.y) + 0x8000),
            MTXMODE_APPLY);
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
