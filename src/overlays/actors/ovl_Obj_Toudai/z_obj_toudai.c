/*
 * File: z_obj_toudai.c
 * Overlay: ovl_Obj_Toudai
 * Description: Unused early Clock Tower Spotlight
 */

#include "z_obj_toudai.h"
#include "objects/object_f53_obj/object_f53_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjToudai*)thisx)

void ObjToudai_Init(Actor* thisx, PlayState* play);
void ObjToudai_Destroy(Actor* thisx, PlayState* play);
void ObjToudai_Update(Actor* thisx, PlayState* play);
void ObjToudai_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Toudai_InitVars = {
    /**/ ACTOR_OBJ_TOUDAI,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_F53_OBJ,
    /**/ sizeof(ObjToudai),
    /**/ ObjToudai_Init,
    /**/ ObjToudai_Destroy,
    /**/ ObjToudai_Update,
    /**/ ObjToudai_Draw,
};

#include "assets/overlays/ovl_Obj_Toudai/ovl_Obj_Toudai.c"

void func_80A33B00(ObjToudai* this, PlayState* play) {
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_f53_obj_DL_0024E8);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A33BB4(ObjToudai* this, PlayState* play) {
    u8 sp57;
    u8 sp56;
    s32 i;

    this->unk_22C += 1.8f;
    this->unk_230 += 0.6f;
    sp57 = this->unk_22C;
    sp56 = this->unk_230;

    this->unk_228 = CLAMP(this->unk_228, 0.0f, 1.0f);

    for (i = 0; i < ARRAY_COUNT(ovl_Obj_Toudai_Vtx_D_80A34590); i++) {
        this->unk_148[i].v.cn[3] = ovl_Obj_Toudai_Vtx_D_80A34590[i].v.cn[3] * this->unk_228;
    }

    if (this->unk_228 > 0.0f) {
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);

        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, sp57, 0x20, 0x80, 1, 0, sp56, 0x20, 0x20));
        gSPSegment(POLY_XLU_DISP++, 0x09, Lib_SegmentedToVirtual(this->unk_148));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_f53_obj_DL_0023B0);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

u8 func_80A342F4(s16 arg0) {
    u8 var_v1 = 0;
    s16 minutes = TIME_TO_MINUTES_F(gSaveContext.save.time);
    s32 hours = minutes / 60;

    if (hours >= 17) {
        if ((hours == 17) && ((minutes % 60) < arg0)) {
            return var_v1;
        }
        var_v1 = 2;
    } else if (hours < 6) {
        if ((hours == 5) && ((minutes % 60) < arg0)) {
            return var_v1;
        }
        var_v1 = 1;
    }
    return var_v1;
}

void ObjToudai_Init(Actor* thisx, PlayState* play) {
    ObjToudai* this = THIS;

    Lib_MemCpy(this->unk_148, &ovl_Obj_Toudai_Vtx_D_80A34590, sizeof(ovl_Obj_Toudai_Vtx_D_80A34590));
}

void ObjToudai_Destroy(Actor* thisx, PlayState* play) {
}

void ObjToudai_Update(Actor* thisx, PlayState* play) {
    ObjToudai* this = THIS;
    u8 temp_v0 = func_80A342F4(this->unk_238);

    if (temp_v0 != this->unk_236) {
        this->unk_236 = temp_v0;
        this->unk_238 = Rand_S16Offset(0, 50);
    }

    Math_ApproachF(&this->unk_228, (this->unk_236 == 0) ? 0.0f : 1.0f, 0.01f, 1000.0f);
    this->unk_234 += 100;
    thisx->shape.rot.y = (s16)(Math_SinS(this->unk_234) * 16000.0f) + thisx->world.rot.y;
}

void ObjToudai_Draw(Actor* thisx, PlayState* play) {
    ObjToudai* this = THIS;

    func_80A33B00(this, play);
    func_80A33BB4(this, play);
}
