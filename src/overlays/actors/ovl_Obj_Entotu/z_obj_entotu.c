/*
 * File: z_obj_entotu.c
 * Overlay: ovl_Obj_Entotu
 * Description: Clock Town Smoking Chimney
 */

#include "z_obj_entotu.h"
#include "objects/object_f53_obj/object_f53_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjEntotu*)thisx)

void ObjEntotu_Init(Actor* thisx, PlayState* play);
void ObjEntotu_Destroy(Actor* thisx, PlayState* play);
void ObjEntotu_Update(Actor* thisx, PlayState* play);
void ObjEntotu_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Entotu_InitVars = {
    /**/ ACTOR_OBJ_ENTOTU,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_F53_OBJ,
    /**/ sizeof(ObjEntotu),
    /**/ ObjEntotu_Init,
    /**/ ObjEntotu_Destroy,
    /**/ ObjEntotu_Update,
    /**/ ObjEntotu_Draw,
};

#include "overlays/ovl_Obj_Entotu/ovl_Obj_Entotu.c"

s32 func_80A34700(s16 minutes) {
    s32 ret = 0;
    s16 time = TIME_TO_MINUTES_F(gSaveContext.save.time);
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

void func_80A34A44(ObjEntotu* this, PlayState* play) {
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)));
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(0.1f, 0.1f, 0.0f, MTXMODE_APPLY);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_f53_obj_DL_000158);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A34B28(ObjEntotu* this, PlayState* play) {
    u8 sp57;
    u8 sp56;
    s32 i;

    this->unk_1B8.y += 1.8f;
    this->unk_1B8.z += 0.6f;
    sp57 = 0x7F - (u8)this->unk_1B8.y;
    sp56 = 0x7F - (u8)this->unk_1B8.z;

    this->unk_1B8.x = CLAMP(this->unk_1B8.x, 0.0f, 1.0f);

    for (i = 0; i < ARRAY_COUNT(ovl_Obj_Entotu_Vtx_000D10); i++) {
        this->unk_148[i].v.cn[3] = ovl_Obj_Entotu_Vtx_000D10[i].v.cn[3] * this->unk_1B8.x;
    }

    if (this->unk_1B8.x > 0.0f) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        this->actor.shape.rot.y = BINANG_ROT180(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)));
        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.0f, MTXMODE_APPLY);

        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, sp57, 0x20, 0x20, 1, 0, sp56, 0x20, 0x20));
        gSPSegment(POLY_XLU_DISP++, 0x09, Lib_SegmentedToVirtual(this->unk_148));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_f53_obj_DL_001C00);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void ObjEntotu_Init(Actor* thisx, PlayState* play) {
    ObjEntotu* this = THIS;

    Lib_MemCpy(this->unk_148, ovl_Obj_Entotu_Vtx_000D10, sizeof(ovl_Obj_Entotu_Vtx_000D10));
    this->unk_1C6 = Rand_S16Offset(0, 59);
    this->unk_1C4 = 0;
}

void ObjEntotu_Destroy(Actor* thisx, PlayState* play) {
}

void ObjEntotu_Update(Actor* thisx, PlayState* play) {
    ObjEntotu* this = THIS;

    func_80A349C0(this);
}

void ObjEntotu_Draw(Actor* thisx, PlayState* play) {
    ObjEntotu* this = THIS;

    func_80A34B28(this, play);
    func_80A34A44(this, play);
}
