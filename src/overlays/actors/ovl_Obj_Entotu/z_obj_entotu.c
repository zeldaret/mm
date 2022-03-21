/*
 * File: z_obj_entotu.c
 * Overlay: ovl_Obj_Entotu
 * Description: Clock Town Smoking Chimney
 */

#include "z_obj_entotu.h"
#include "objects/object_f53_obj/object_f53_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjEntotu*)thisx)

void ObjEntotu_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEntotu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjEntotu_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEntotu_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Entotu_InitVars = {
    ACTOR_OBJ_ENTOTU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_F53_OBJ,
    sizeof(ObjEntotu),
    (ActorFunc)ObjEntotu_Init,
    (ActorFunc)ObjEntotu_Destroy,
    (ActorFunc)ObjEntotu_Update,
    (ActorFunc)ObjEntotu_Draw,
};

u8 D_80A35410[][16] = {
    { 0xFA, 0x7F, 0x14, 0x05, 0x01, 0x2D, 0x00, 0x00, 0xFF, 0x75, 0xF4, 0x69, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x08, 0xD5, 0x02, 0x5B, 0x00, 0x00, 0x02, 0x00, 0x03, 0xCC, 0x4D, 0x44, 0x34, 0xFF },
    { 0x00, 0x00, 0x1B, 0xAC, 0x01, 0x2D, 0x00, 0x00, 0x02, 0x00, 0xE9, 0xD0, 0x00, 0x00, 0x00, 0x00 },
    { 0xFB, 0xAD, 0x08, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x05, 0x81, 0x14, 0x05, 0x01, 0x2D, 0x00, 0x00, 0x04, 0x8B, 0xF4, 0x69, 0x00, 0x00, 0x00, 0x00 },
    { 0x04, 0x53, 0x08, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x3A, 0x26, 0x21, 0x19, 0x7E },
};

s32 func_80A34700(s16 minutes) {
    s32 ret = 0;
    s16 time = TIME_TO_MINUTES_F(gSaveContext.time);
    s32 hours = time / 60;
    s32 currMinutes = time % 60;

    if (hours >= 16) {
        if ((hours == 16) && (currMinutes < minutes)) {
            return 0;
        }

        if (hours >= 20) {
            return 0;
        }

        if ((hours == 19) && (minutes < currMinutes)) {
            return 0;
        }

        ret = 3;
    } else if (hours >= 11) {
        if ((hours == 11) && (currMinutes < minutes)) {
            return 0;
        }

        if (hours >= 14) {
            return 0;
        }

        if ((hours == 13) && (minutes < currMinutes)) {
            return 0;
        }

        ret = 2;
    } else if (hours >= 6) {
        if ((hours == 6) && (currMinutes < minutes)) {
            return 0;
        }

        if (hours >= 9) {
            return 0;
        }

        if ((hours == 8) && (minutes < currMinutes)) {
            return 0;
        }

        ret = 1;
    }
    return ret;
}

void func_80A349C0(ObjEntotu* this) {
    s32 temp_v0 = func_80A34700(this->unk_1C6);
    u8 temp = temp_v0;
    s16 temp2 = this->unk_1C4;

    if (temp_v0 != temp2) {
        this->unk_1C4 = temp;
        this->unk_1C6 = Rand_S16Offset(0, 59);
    }

    temp2 = this->unk_1C4;
    Math_ApproachF(&this->unk_1B8.x, (temp2 == 0) ? 0.0f : 1.0f, 0.02f, 1000.0f);
}

void func_80A34A44(ObjEntotu* this, GlobalContext* globalCtx) {
    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)));
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(0.1f, 0.1f, 0.0f, MTXMODE_APPLY);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_f53_obj_DL_000158);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A34B28(ObjEntotu* this, GlobalContext* globalCtx) {
    u8 sp57;
    u8 sp56;
    s32 i;

    this->unk_1B8.y += 1.8f;
    this->unk_1B8.z += 0.6f;
    sp57 = 0x7F - (u8)this->unk_1B8.y;
    sp56 = 0x7F - (u8)this->unk_1B8.z;

    this->unk_1B8.x = CLAMP(this->unk_1B8.x, 0.0f, 1.0f);

    for (i = 0; i < ARRAY_COUNT(D_80A35410); i++) {
        this->unk_148[i][15] = D_80A35410[i][15] * this->unk_1B8.x;
    }

    if (this->unk_1B8.x > 0.0f) {
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)));
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.0f, MTXMODE_APPLY);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, sp57, 0x20, 0x20, 1, 0, sp56, 0x20, 0x20));
        gSPSegment(POLY_XLU_DISP++, 0x09, Lib_SegmentedToVirtual(this->unk_148));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_f53_obj_DL_001C00);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void ObjEntotu_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjEntotu* this = THIS;

    Lib_MemCpy(this->unk_148, D_80A35410, sizeof(D_80A35410));
    this->unk_1C6 = Rand_S16Offset(0, 59);
    this->unk_1C4 = 0;
}

void ObjEntotu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjEntotu_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjEntotu* this = THIS;

    func_80A349C0(this);
}

void ObjEntotu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjEntotu* this = THIS;

    func_80A34B28(this, globalCtx);
    func_80A34A44(this, globalCtx);
}
