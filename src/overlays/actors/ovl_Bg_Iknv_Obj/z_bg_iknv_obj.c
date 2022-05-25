/*
 * File: z_bg_iknv_obj.c
 * Overlay: ovl_Bg_Iknv_Obj
 * Description: Ikana - waterwheel, stone tower door, sakon's hideout door
 */

#include "z_bg_iknv_obj.h"
#include "objects/object_iknv_obj/object_iknv_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIknvObj*)thisx)

void BgIknvObj_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgIknvObj_DoNothing(BgIknvObj* this, GlobalContext* globalCtx);
void BgIknvObj_UpdateWaterwheel(BgIknvObj* this, GlobalContext* globalCtx);
void BgIknvObj_UpdateRaisedDoor(BgIknvObj* this, GlobalContext* globalCtx);
void BgIknvObj_UpdateSakonDoor(BgIknvObj* this, GlobalContext* globalCtx);

const ActorInit Bg_Iknv_Obj_InitVars = {
    ACTOR_BG_IKNV_OBJ,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvObj),
    (ActorFunc)BgIknvObj_Init,
    (ActorFunc)BgIknvObj_Destroy,
    (ActorFunc)BgIknvObj_Update,
    (ActorFunc)BgIknvObj_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 40, 40, 0, { 0, 0, 0 } },
};

void BgIknvObj_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIknvObj* this = THIS;
    CollisionHeader* colHeader = NULL;

    Actor_SetScale(&this->dyna.actor, 0.1f);
    this->actionFunc = BgIknvObj_DoNothing;
    switch (IKNV_OBJ_TYPE(this)) {
        case IKNV_OBJ_WATERWHEEL:
            this->displayListPtr = object_iknv_obj_DL_013058;
            this->actionFunc = BgIknvObj_UpdateWaterwheel;
            this->dyna.actor.flags |= ACTOR_FLAG_100000;
            this->dyna.actor.flags |= ACTOR_FLAG_10;
            break;
        case IKNV_OBJ_RAISED_DOOR:
            this->displayListPtr = object_iknv_obj_DL_011880;
            DynaPolyActor_Init(&this->dyna, 0);
            CollisionHeader_GetVirtual(&object_iknv_obj_Colheader_0119D4, &colHeader);
            this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
            this->actionFunc = BgIknvObj_UpdateRaisedDoor;
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 120.0f;
            break;
        case IKNV_OBJ_SAKON_DOOR:
            this->displayListPtr = object_iknv_obj_DL_0129C8;
            this->actionFunc = BgIknvObj_UpdateSakonDoor;
            DynaPolyActor_Init(&this->dyna, 0);
            CollisionHeader_GetVirtual(&object_iknv_obj_Colheader_012CA4, &colHeader);
            this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
            Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
            this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
            gSaveContext.save.weekEventReg[51] &= (u8)~0x10;
            Actor_SetFocus(&this->dyna.actor, IREG(88));
            break;
        default:
            Actor_MarkForDeath(&this->dyna.actor);
    }
}

void BgIknvObj_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIknvObj* this = THIS;

    if (IKNV_OBJ_TYPE(this) != IKNV_OBJ_RAISED_DOOR) {
        if (IKNV_OBJ_TYPE(this) == IKNV_OBJ_SAKON_DOOR) {
            Collider_DestroyCylinder(globalCtx, &this->collider);
            gSaveContext.save.weekEventReg[51] &= (u8)~0x10;
        } else {
            return;
        }
    }
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

s32 func_80BD7CEC(BgIknvObj* this) {
    if (this->dyna.actor.cutscene == -1) {
        return true;
    }

    if (ActorCutscene_GetCurrentIndex() == this->dyna.actor.cutscene) {
        return true;
    }

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        return true;
    }

    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    return false;
}

void BgIknvObj_UpdateWaterwheel(BgIknvObj* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.weekEventReg[14] & 4) {
        this->dyna.actor.shape.rot.z -= 0x64;
        func_800B9098(&this->dyna.actor);
        func_800B9010(&this->dyna.actor, NA_SE_EV_WOOD_WATER_WHEEL - SFX_FLAG);
    }

    if ((globalCtx->csCtx.state != 0) && (gSaveContext.sceneSetupIndex == 1) &&
        (globalCtx->csCtx.currentCsIndex == 4) && (globalCtx->csCtx.frames == 1495)) {
        func_8019F128(NA_SE_EV_DOOR_UNLOCK);
    }
}

s32 func_80BD7E0C(BgIknvObj* this, s16 targetRotation, GlobalContext* globalCtx) {
    this->dyna.actor.shape.yOffset = 0.0f;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    if (targetRotation != this->dyna.actor.shape.rot.y) {
        Math_SmoothStepToS(&this->dyna.actor.shape.rot.y, targetRotation, 2, 100, 100);
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;
        if ((globalCtx->gameplayFrames % 2) != 0) {
            this->dyna.actor.shape.yOffset = 5.0f;
        }
        func_800B9010(&this->dyna.actor, NA_SE_EV_STONEDOOR_OPEN_S - SFX_FLAG);
        return false;
    }
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_STONEDOOR_STOP);
    return true;
}

void func_80BD7ED8(BgIknvObj* this, GlobalContext* globalCtx) {
    if (func_80BD7E0C(this, this->dyna.actor.home.rot.y, globalCtx)) {
        this->actionFunc = BgIknvObj_UpdateSakonDoor;
        gSaveContext.save.weekEventReg[51] &= (u8)~0x10;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80BD7F4C(BgIknvObj* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.time > CLOCK_TIME(19, 30)) {
        this->actionFunc = func_80BD7ED8;
    }
    if ((this->dyna.actor.home.rot.x == 1) && !(gSaveContext.save.weekEventReg[58] & 0x80)) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->dyna.actor.home.rot.x = 0;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80BD7FDC(BgIknvObj* this, GlobalContext* globalCtx) {
    if (func_80BD7E0C(this, this->dyna.actor.home.rot.y + 0x4000, globalCtx)) {
        this->actionFunc = func_80BD7F4C;
        gSaveContext.save.weekEventReg[51] |= 0x10;
        this->dyna.actor.home.rot.x = 1;
    }
}

void func_80BD8040(BgIknvObj* this, GlobalContext* globalCtx) {
    if (func_80BD7CEC(this)) {
        this->actionFunc = func_80BD7FDC;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void BgIknvObj_UpdateSakonDoor(BgIknvObj* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.weekEventReg[58] & 0x80) {
        this->actionFunc = func_80BD8040;
        gSaveContext.save.weekEventReg[89] |= 0x80;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void BgIknvObj_UpdateRaisedDoor(BgIknvObj* this, GlobalContext* globalCtx) {
}

void BgIknvObj_DoNothing(BgIknvObj* this, GlobalContext* globalCtx) {
}

void BgIknvObj_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIknvObj* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgIknvObj_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIknvObj* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->displayListPtr);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
