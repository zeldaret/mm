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

void func_80AC9680(ObjOcarinalift* this);
void func_80AC96A4(ObjOcarinalift* this, PlayState* play);
void func_80AC96B4(ObjOcarinalift* this);
void func_80AC96D0(ObjOcarinalift* this, PlayState* play);
void func_80AC99D4(ObjOcarinalift* this, PlayState* play);
void func_80AC99C0(ObjOcarinalift* this);
void func_80AC9A68(ObjOcarinalift* this);
void func_80AC9A7C(ObjOcarinalift* this, PlayState* play);
void func_80AC9AB8(ObjOcarinalift* this);
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
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),         ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void func_80AC94C0(ObjOcarinalift* this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, &this->unk170[arg1]);
}

void ObjOcarinalift_Init(Actor* thisx, PlayState* play) {
    Path* path;
    ObjOcarinalift* this = THIS;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.world.rot.z = 0;
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_raillift_Colheader_0048D0);
    this->unk160 = thisx->home.rot.z * 0.1f;
    if (this->unk160 < 0.01f) {
        func_80AC9680(this);
    } else {
        path = &play->setupPathList[OBJOCARINALIFT_GET_7F(&this->dyna.actor)];
        this->unk168 = OBJOCARINALIFT_GET_1F(&this->dyna.actor);
        this->unk164 = path->count - 1;
        this->unk16C = 1;
        this->unk170 = Lib_SegmentedToVirtual(path->points);
        func_80AC94C0(this, this->unk168);
        if ((OBJOCARINALIFT_GET_C(&this->dyna.actor) != OBJOCARINALIFT_PARAMSC_1) &&
            (Flags_GetSwitch(play, OBJOCARINALIFT_GET_SWITCH_FLAG(&this->dyna.actor)))) {
            func_80AC96B4(this);
        } else {
            func_80AC9AB8(this);
        }
    }
}

void ObjOcarinalift_Destroy(Actor* thisx, PlayState* play) {
    ObjOcarinalift* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80AC9680(ObjOcarinalift* this) {
    this->dyna.actor.flags &= ~ACTOR_FLAG_10;
    this->actionFunc = func_80AC96A4;
}

void func_80AC96A4(ObjOcarinalift* this, PlayState* play) {
}

void func_80AC96B4(ObjOcarinalift* this) {
    this->actionFunc = func_80AC96D0;
    this->dyna.actor.speedXZ = 0.0f;
}

void func_80AC96D0(ObjOcarinalift* this, PlayState* play) {
    Actor* thisx = &this->dyna.actor;
    Vec3f sp48;
    f32 magnitude;
    f32 phi_fv0;
    f32 phi_fa0;
    s32 paramsC;
    s32 sp34;
    Vec3s* temp_v1_2;

    func_800B9010(thisx, NA_SE_EV_PLATE_LIFT_LEVEL - SFX_FLAG);
    Math_Vec3s_ToVec3f(&sp48, this->unk170 + this->unk168 + this->unk16C);
    Math_Vec3f_Diff(&sp48, &thisx->world.pos, &thisx->velocity);
    magnitude = Math3D_Vec3fMagnitude(&thisx->velocity);

    if ((magnitude < (this->unk160 * 8.0f)) && (this->unk160 > 2.0f)) {
        phi_fv0 = ((this->unk160 - 2.0f) * 0.1f) + 2.0f;
        phi_fa0 = this->unk160 * 0.03f;
    } else {
        phi_fv0 = this->unk160;
        phi_fa0 = this->unk160 * 0.16f;
    }

    Math_StepToF(&thisx->speedXZ, phi_fv0, phi_fa0);
    if ((thisx->speedXZ + 0.05f) < magnitude) {
        Math_Vec3f_Scale(&thisx->velocity, thisx->speedXZ / magnitude);
        thisx->world.pos.x += thisx->velocity.x;
        thisx->world.pos.y += thisx->velocity.y;
        thisx->world.pos.z += thisx->velocity.z;
    } else {
        paramsC = OBJOCARINALIFT_GET_C(thisx);
        sp34 = true;
        this->unk168 += this->unk16C;
        thisx->speedXZ *= 0.4f;
        if (((this->unk168 >= this->unk164) && (this->unk16C > 0)) || ((this->unk168 <= 0) && (this->unk16C < 0))) {
            if (paramsC == OBJOCARINALIFT_PARAMSC_0) {
                this->unk16C = -this->unk16C;
                this->timer = 10;
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
                    sp34 = false;
                } else if ((paramsC == OBJOCARINALIFT_PARAMSC_1) && (this->unk168 == OBJOCARINALIFT_GET_1F(thisx))) {
                    func_80AC9AB8(this);
                }
            }
        } else if ((paramsC == OBJOCARINALIFT_PARAMSC_1) && (this->unk168 == OBJOCARINALIFT_GET_1F(thisx))) {
            func_80AC9AB8(this);
        }
        if (sp34) {
            func_80AC94C0(this, this->unk168);
        }
    }
}

void func_80AC99C0(ObjOcarinalift* this) {
    this->actionFunc = func_80AC99D4;
}

void func_80AC99D4(ObjOcarinalift* this, PlayState* play) {
    if (!DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_80AC94C0(this, this->unk168);
        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
        if ((OBJOCARINALIFT_GET_C(&this->dyna.actor) == OBJOCARINALIFT_PARAMSC_1) &&
            (this->unk168 == OBJOCARINALIFT_GET_1F(&this->dyna.actor))) {
            func_80AC9AB8(this);
        } else {
            func_80AC96B4(this);
        }
    }
}

void func_80AC9A68(ObjOcarinalift* this) {
    this->actionFunc = func_80AC9A7C;
}

void func_80AC9A7C(ObjOcarinalift* this, PlayState* play) {
    this->timer--;
    if (this->timer <= 0) {
        func_80AC96B4(this);
    }
}

void func_80AC9AB8(ObjOcarinalift* this) {
    this->dyna.actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_2000000 | ACTOR_FLAG_8000000);
    this->actionFunc = func_80AC9AE0;
}

void func_80AC9AE0(ObjOcarinalift* this, PlayState* play) {
    if (func_800B8718(&this->dyna.actor, &play->state)) {
        func_80152434(play, 1);
        func_80AC9B48(this);
    } else if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_800B8804(&this->dyna.actor, play, 40.0f);
    }
}

void func_80AC9B48(ObjOcarinalift* this) {
    this->actionFunc = func_80AC9B5C;
}

void func_80AC9B5C(ObjOcarinalift* this, PlayState* play) {
    if (func_800B886C(&this->dyna.actor, play)) {
        if (play->msgCtx.ocarinaMode == 4) {
            if (play->msgCtx.unk1202E == 0) {
                if (OBJOCARINALIFT_GET_C(&this->dyna.actor) != OBJOCARINALIFT_PARAMSC_1) {
                    Flags_SetSwitch(play, OBJOCARINALIFT_GET_SWITCH_FLAG(&this->dyna.actor));
                }
                ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
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

void func_80AC9C20(ObjOcarinalift* this) {
    this->dyna.actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_2000000 | ACTOR_FLAG_8000000);
    this->actionFunc = func_80AC9C48;
}

void func_80AC9C48(ObjOcarinalift* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->cutsceneTimer = 50;
        func_80AC96B4(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjOcarinalift_Update(Actor* thisx, PlayState* play) {
    ObjOcarinalift* this = THIS;

    this->actionFunc(this, play);
    Actor_SetFocus(&this->dyna.actor, 10.0f);
    if (this->cutsceneTimer > 0) {
        this->cutsceneTimer--;
        if (this->cutsceneTimer == 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }
}

void ObjOcarinalift_Draw(Actor* thisx, PlayState* play) {
    ObjOcarinalift* this = THIS;

    Gfx_DrawDListOpa(play, object_raillift_DL_001E40);
    Gfx_DrawDListXlu(play, object_raillift_DL_001DB0);
}
