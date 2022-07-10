/*
 * File: z_obj_ocarinalift.c
 * Overlay: ovl_Obj_Ocarinalift
 * Description: Elevator With Triforce Texture (unused?)
 */

#include "z_obj_ocarinalift.h"
#include "objects/object_raillift/object_raillift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjOcarinalift*)thisx)

void ObjOcarinalift_Init(Actor* thisx, PlayState* play);
void ObjOcarinalift_Destroy(Actor* thisx, PlayState* play);
void ObjOcarinalift_Update(Actor* thisx, PlayState* play);
void ObjOcarinalift_Draw(Actor* thisx, PlayState* play);

void func_80AC94C0(ObjOcarinalift* this, s32 arg1);
void func_80AC9680(ObjOcarinalift* this);
void func_80AC96B4(ObjOcarinalift* this);
void func_80AC9AB8(ObjOcarinalift* this);
void func_80AC96A4(ObjOcarinalift* this, PlayState* play);
void func_80AC96D0(ObjOcarinalift* this, PlayState* play);
void func_80AC99C0(ObjOcarinalift* this);
void func_80AC9A68(ObjOcarinalift* this);
void func_80AC99D4(ObjOcarinalift* this, PlayState* play);
void func_80AC9A7C(ObjOcarinalift* this, PlayState* play);
void func_80AC9AE0(ObjOcarinalift* this, PlayState* play);
void func_80AC9B48(ObjOcarinalift* this);
void func_80AC9B5C(ObjOcarinalift* this, PlayState* play);
void func_80AC9C20(ObjOcarinalift* this);
void func_80AC9C48(ObjOcarinalift* this, PlayState* play);

const ActorInit Obj_Ocarinalift_InitVars = {
    ACTOR_OBJ_OCARINALIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjOcarinalift),
    (ActorFunc)ObjOcarinalift_Init,
    (ActorFunc)ObjOcarinalift_Destroy,
    (ActorFunc)ObjOcarinalift_Update,
    (ActorFunc)ObjOcarinalift_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void func_80AC94C0(ObjOcarinalift *this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, &this->unk170[arg1]);
}

void ObjOcarinalift_Init(Actor* thisx, PlayState* play) {
    Path* path;
    f32 test;
    ObjOcarinalift* this = (ObjOcarinalift*)thisx;
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.world.rot.z = 0;
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_raillift_Colheader_0048D0);
    test = this->dyna.actor.home.rot.z * 0.1f;
    this->unk160 = ((f32)this->dyna.actor.home.rot.z) * 0.1f;
    if (1) {}
    if (this->unk160 < 0.01f) {
        func_80AC9680(this);
    } else {
        path = &play->setupPathList[this->dyna.actor.params & 0x7F];
        this->unk168 = (this->dyna.actor.params >> 7) & 0x1F;
        this->unk164 = path->count - 1;
        this->unk16C = 1;
        this->unk170 = Lib_SegmentedToVirtual(path->points);
        func_80AC94C0(this, this->unk168);
        if (((((this->dyna.actor.params) >> 0xC) & 3) != 1) &&
            (Flags_GetSwitch(play, this->dyna.actor.home.rot.x & 0x7F))) {
            func_80AC96B4(this);
        } else {
            func_80AC9AB8(this);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Destroy.s")

void ObjOcarinalift_Destroy(Actor* thisx, PlayState* play) {
    ObjOcarinalift* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9680.s")

void func_80AC9680(ObjOcarinalift* this) {
    this->dyna.actor.flags &= -0x11;
    this->actionFunc = func_80AC96A4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC96A4.s")

void func_80AC96A4(ObjOcarinalift* this, PlayState* play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC96B4.s")
void func_80AC96B4(ObjOcarinalift* this) {
    this->actionFunc = func_80AC96D0;
    this->dyna.actor.speedXZ = 0.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC96D0.s")
void func_80AC96D0(ObjOcarinalift* this, PlayState* play) {
    PlayState* play2 = play;
    Vec3f sp48;
    f32 magnitude;
    ObjOcarinalift* new_var = this;
    f32 phi_fv0;
    f32 phi_fa0;
    s32 sp34;
    s32 params;
    Vec3s* temp_v1_2;

    func_800B9010(&this->dyna.actor, 0x2103);
    Math_Vec3s_ToVec3f(&sp48, this->unk170 + this->unk168 + this->unk16C);
    Math_Vec3f_Diff(&sp48, &this->dyna.actor.world.pos, &this->dyna.actor.velocity);
    magnitude = Math3D_Vec3fMagnitude(&this->dyna.actor.velocity);
    if ((magnitude < (this->unk160 * 8.0f)) && (this->unk160 > 2.0f)) {
        phi_fv0 = ((this->unk160 - 2.0f) * 0.1f) + 2.0f;
        phi_fa0 = this->unk160 * 0.03f;
    } else {
        phi_fv0 = this->unk160;
        phi_fa0 = this->unk160 * 0.16f;
    }
    Math_StepToF(&this->dyna.actor.speedXZ, phi_fv0, phi_fa0);
    if ((this->dyna.actor.speedXZ + 0.05f) < magnitude) {
        Math_Vec3f_Scale(&this->dyna.actor.velocity, this->dyna.actor.speedXZ / magnitude);
        this->dyna.actor.world.pos.x += this->dyna.actor.velocity.x;
        this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
        this->dyna.actor.world.pos.z += this->dyna.actor.velocity.z;
    } else {
        params = (this->dyna.actor.params >> 0xC) & 3;
        sp34 = 1;
        this->unk168 += this->unk16C;
        new_var->dyna.actor.speedXZ *= 0.4f;
        if (((this->unk168 >= this->unk164) && (this->unk16C > 0)) || ((this->unk168 <= 0) && (new_var->unk16C < 0))) {
            if (params == 0) {
                this->unk16C = -this->unk16C;
                this->unk174 = 0xA;
                func_80AC9A68(this);
            } else {
                temp_v1_2 = this->unk170 + this->unk164;
                if (this->unk16C > 0) {
                    this->unk168 = 0;
                } else {
                    this->unk168 = this->unk164;
                }
                if (((this->unk170->x != temp_v1_2->x) || (this->unk170->y != temp_v1_2->y)) ||
                    (this->unk170->z != temp_v1_2->z)) {
                    func_80AC99C0(this);
                    func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
                    sp34 = 0;
                } else if ((params == 1) && (this->unk168 == (((this->dyna.actor.params) >> 7) & 0x1F))) {
                    func_80AC9AB8(this);
                }
            }
        } else if ((params == 1) && (this->unk168 == (((this->dyna.actor.params) >> 7) & 0x1F))) {
            func_80AC9AB8(this);
        }
        if (sp34 != 0) {
            func_80AC94C0(this, this->unk168);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC99C0.s")

void func_80AC99C0(ObjOcarinalift* this) {
    this->actionFunc = func_80AC99D4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC99D4.s")

void func_80AC99D4(ObjOcarinalift* this, PlayState* play) {
    if (DynaPolyActor_IsInRidingMovingState(&this->dyna) == 0) {
        func_80AC94C0(this, this->unk168);
        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
        if ((((this->dyna.actor.params >> 0xC) & 3) == 1) &&
            (this->unk168 == ((this->dyna.actor.params >> 7) & 0x1F))) {
            func_80AC9AB8(this);
        } else {
            func_80AC96B4(this);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9A68.s")

void func_80AC9A68(ObjOcarinalift* this) {
    this->actionFunc = func_80AC9A7C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9A7C.s")

void func_80AC9A7C(ObjOcarinalift* this, PlayState* play) {
    this->unk174 -= 1;
    if (this->unk174 <= 0) {
        func_80AC96B4(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9AB8.s")

void func_80AC9AB8(ObjOcarinalift* this) {
    this->dyna.actor.flags |= 0x0A000001;
    this->actionFunc = func_80AC9AE0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9AE0.s")

void func_80AC9AE0(ObjOcarinalift* this, PlayState* play) {
    if (func_800B8718(&this->dyna.actor, &play->state)) {
        func_80152434(play, 1);
        func_80AC9B48(this);
        return;
    }
    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_800B8804(&this->dyna.actor, play, 40.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9B48.s")

void func_80AC9B48(ObjOcarinalift* this) {
    this->actionFunc = func_80AC9B5C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9B5C.s")

void func_80AC9B5C(ObjOcarinalift* this, PlayState* play) {
    if (func_800B886C(&this->dyna.actor, play) != 0) {
        if (play->msgCtx.ocarinaMode == 4) {
            if (play->msgCtx.unk1202E == 0) {
                if (((this->dyna.actor.params >> 0xC) & 3) != 1) {
                    Flags_SetSwitch(play, this->dyna.actor.home.rot.x & 0x7F);
                }
                ActorCutscene_SetIntentToPlay((s16)this->dyna.actor.cutscene);
                func_80AC9C20(this);
            }
        } else {
            if (play->msgCtx.ocarinaMode >= 2) {
                play->msgCtx.ocarinaMode = 4;
            }
            func_80AC9AB8(this);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9C20.s")

void func_80AC9C20(ObjOcarinalift* this) {
    this->dyna.actor.flags &= 0xF5FFFFFE;
    this->actionFunc = func_80AC9C48;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/func_80AC9C48.s")

void func_80AC9C48(ObjOcarinalift* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext((s16)this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields((s16)this->dyna.actor.cutscene, &this->dyna.actor);
        this->unk176 = 0x32;
        func_80AC96B4(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Update.s")

void ObjOcarinalift_Update(Actor* thisx, PlayState* play) {
    ObjOcarinalift* this = THIS;

    this->actionFunc(this, play);
    Actor_SetFocus(&this->dyna.actor, 10.0f);
    if (this->unk176 > 0) {
        this->unk176--;
        if (this->unk176 == 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Ocarinalift/ObjOcarinalift_Draw.s")

void ObjOcarinalift_Draw(Actor* thisx, PlayState* play) {
    ObjOcarinalift* this = THIS;

    Gfx_DrawDListOpa(play, object_raillift_DL_001E40);
    Gfx_DrawDListXlu(play, object_raillift_DL_001DB0);
}
