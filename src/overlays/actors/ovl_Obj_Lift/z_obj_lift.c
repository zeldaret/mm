/*
 * File: z_obj_lift.c
 * Overlay: ovl_Obj_Lift
 * Description: Dampé's Grave - Brown Elevator
 */

#include "z_obj_lift.h"
#include "objects/object_d_lift/object_d_lift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjLift*)thisx)

void ObjLift_Init(Actor* thisx, PlayState* play);
void ObjLift_Destroy(Actor* thisx, PlayState* play);
void ObjLift_Update(Actor* thisx, PlayState* play);
void ObjLift_Draw(Actor* thisx, PlayState* play);

void func_8093D760(ObjLift* this);
void func_8093D7A0(ObjLift* this, PlayState* play);
void func_8093D9C0(ObjLift* this);
void func_8093D8B4(ObjLift* this, PlayState* play);
void func_8093D88C(ObjLift* this);
void func_8093DA48(ObjLift* this, PlayState* play);
void func_8093DB70(ObjLift* this);
void func_8093DB90(ObjLift* this, PlayState* play);
void func_8093DC90(Actor* thisx, PlayState* play);

const ActorInit Obj_Lift_InitVars = {
    ACTOR_OBJ_LIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjLift),
    (ActorFunc)ObjLift_Init,
    (ActorFunc)ObjLift_Destroy,
    (ActorFunc)ObjLift_Update,
    (ActorFunc)ObjLift_Draw,
};

static s16 D_8093DD50[] = { 0, 10, 20, 30, 40, 50, 60 };

Vec2s D_8093DD60[] = {
    { 120, -120 }, { 120, 0 },     { 120, 120 }, { 0, -120 },   { 0, 0 },
    { 0, 120 },    { -120, -120 }, { -120, 0 },  { -120, 120 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -600, ICHAIN_CONTINUE),   ICHAIN_F32_DIV1000(terminalVelocity, -15000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 350, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_STOP),
};

static f32 D_8093DD98[] = { 0.1f, 0.05f };

static f32 yOffset[] = { -18.0f, -9.0f, 0.0f, 0.0f };

void func_8093D3C0(ObjLift* this, PlayState* play) {
    Vec3f pos;
    Vec3f vel;
    s32 pad;
    s32 i;
    Vec3f* actorPos = &this->dyna.actor.world.pos;

    for (i = 0; i < ARRAY_COUNT(D_8093DD60); i++) {
        pos.x = (D_8093DD60[i].x * this->dyna.actor.scale.x) + actorPos->x;
        pos.y = actorPos->y;
        pos.z = (D_8093DD60[i].z * this->dyna.actor.scale.z) + actorPos->z;

        vel.x = D_8093DD60[i].x * this->dyna.actor.scale.x * 0.8f;
        vel.y = (Rand_ZeroOne() * 10.0f) + 6.0f;
        vel.z = D_8093DD60[i].z * this->dyna.actor.scale.z * 0.8f;

        EffectSsKakera_Spawn(play, &pos, &vel, actorPos, -0x100, ((s32)Rand_Next() > 0) ? 64 : 32, 15, 15, 0,
                             ((Rand_ZeroOne() * 50.0f) + 50.0f) * this->dyna.actor.scale.x, 0, 32, 50, -1,
                             OBJECT_D_LIFT, object_d_lift_DL_000D10);
    }
    if (OBJLIFT_GET_1(&this->dyna.actor) == 0) {
        func_800BBFB0(play, &this->dyna.actor.world.pos, 120.0f, 12, 120, 100, 1);
    } else if (OBJLIFT_GET_1(&this->dyna.actor) == 1) {
        func_800BBFB0(play, &this->dyna.actor.world.pos, 60.0f, 8, 60, 100, 1);
    }
}

void ObjLift_Init(Actor* thisx, PlayState* play) {
    f32 temp_fv0;
    ObjLift* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    temp_fv0 = D_8093DD98[OBJLIFT_GET_1(&this->dyna.actor)];
    this->dyna.actor.scale.z = temp_fv0;
    this->dyna.actor.scale.x = temp_fv0;
    this->dyna.actor.scale.y = 0.055555556f;
    this->dyna.actor.shape.rot.z = 0;
    this->unk178 = this->dyna.actor.home.rot.z;
    this->dyna.actor.world.rot.z = this->dyna.actor.shape.rot.z;
    this->dyna.actor.home.rot.z = this->dyna.actor.shape.rot.z;
    DynaPolyActor_Init(&this->dyna, 1);
    if ((this->unk178 <= 0) && (Flags_GetSwitch(play, OBJLIFT_GET_7F(&this->dyna.actor)))) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        DynaPolyActor_LoadMesh(play, &this->dyna, &object_d_lift_Colheader_000F00);
        this->unk160 = Rand_Next() >> 0x10;
        this->unk162 = Rand_Next() >> 0x10;
        this->unk164 = Rand_Next() >> 0x10;
        func_8093D760(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Destroy.s")

void ObjLift_Destroy(Actor* thisx, PlayState* play) {
    ObjLift* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D760.s")

void func_8093D760(ObjLift* this) {
    this->unk166 = D_8093DD50[OBJLIFT_GET_7(&this->dyna.actor)];
    this->actionFunc = func_8093D7A0;
    this->dyna.actor.draw = ObjLift_Draw;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D7A0.s")

void func_8093D7A0(ObjLift* this, PlayState* play) {
    s32 pad;
    s16 quake;

    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        if (this->unk166 <= 0) {
            if (OBJLIFT_GET_7(&this->dyna.actor) == 7) {
                func_8093D9C0(this);
            } else {
                quake = Quake_Add(play->cameraPtrs[play->activeCamera], 1);
                Quake_SetSpeed((quake), 0x2710);
                Quake_SetQuakeValues(quake, 2, 0, 0, 0);
                Quake_SetCountdown(quake, 0x14);
                func_8093D88C(this);
            }
        }
    } else {
        this->unk166 = D_8093DD50[OBJLIFT_GET_7(&this->dyna.actor)];
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D88C.s")

void func_8093D88C(ObjLift* this) {
    this->unk166 = 0x14;
    this->actionFunc = func_8093D8B4;
    this->dyna.actor.draw = func_8093DC90;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D8B4.s")

void func_8093D8B4(ObjLift* this, PlayState* play) {
    if (this->unk166 <= 0) {
        func_8093D9C0(this);
    } else {
        this->unk160 += 0x2710;
        this->unk174 = Math_SinS(this->unk160) * 300.0f;
        this->unk176 = Math_CosS(this->unk160) * 300.0f;
        this->unk162 += 0x4650;
        this->unk168.y = Math_SinS(this->unk162);
        this->unk164 += 0x4650;
        this->unk168.x = Math_SinS(this->unk164) * 3.0f;
        this->unk168.z = Math_CosS(this->unk164) * 3.0f;
    }
    if ((this->unk166 & 3) == 3) {
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 0x10U, 0x2838U);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D9C0.s")

void func_8093D9C0(ObjLift* this) {
    this->actionFunc = func_8093DA48;
    Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos);
    this->dyna.actor.shape.rot = this->dyna.actor.world.rot = this->dyna.actor.home.rot;
    this->dyna.actor.draw = ObjLift_Draw;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DA48.s")

void func_8093DA48(ObjLift* this, PlayState* play) {
    s32 pad;
    s32 sp38;
    Vec3f sp2C;
    f32 temp_fv0;

    Actor_MoveWithGravity(&this->dyna.actor);
    Math_Vec3f_Copy(&sp2C, &this->dyna.actor.prevPos);
    sp2C.y += yOffset[OBJLIFT_GET_1(&this->dyna.actor)];
    temp_fv0 = BgCheck_EntityRaycastFloor5(&play->colCtx, &this->dyna.actor.floorPoly, &sp38, &this->dyna.actor, &sp2C);
    this->dyna.actor.floorHeight = temp_fv0;
    if ((yOffset[OBJLIFT_GET_1(&this->dyna.actor)] - 0.001f) <= (temp_fv0 - this->dyna.actor.world.pos.y)) {
        func_8093D3C0(this, play);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 0x14, NA_SE_EV_BOX_BREAK);
        if (this->unk178 > 0) {
            func_8093DB70(this);
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
        } else {
            Flags_SetSwitch(play, OBJLIFT_GET_7F(&this->dyna.actor));
            Actor_MarkForDeath(&this->dyna.actor);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DB70.s")

void func_8093DB70(ObjLift* this) {
    this->unk166 = this->unk178;
    this->actionFunc = func_8093DB90;
    this->dyna.actor.draw = NULL;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DB90.s")

void func_8093DB90(ObjLift* this, PlayState* play) {
    if (this->unk166 <= 0) {
        Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos);
        this->dyna.actor.world.rot = this->dyna.actor.shape.rot = this->dyna.actor.home.rot;
        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
        func_8093D760(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Update.s")

void ObjLift_Update(Actor* thisx, PlayState* play) {
    ObjLift* this = THIS;
    
    if (this->unk166 > 0) {
        this->unk166--;
    }
    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Draw.s")

void ObjLift_Draw(Actor* thisx, PlayState* play) {
    ObjLift* this = THIS;

    Gfx_DrawDListOpa(play, object_d_lift_DL_000D10);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DC90.s")

void func_8093DC90(Actor* thisx, PlayState* play) {
    ObjLift* this = THIS;
    Vec3f sp28;
    Vec3s sp20;

    Math_Vec3f_Sum(&this->dyna.actor.world.pos, &this->unk168, &sp28);
    sp20.x = this->unk174 + this->dyna.actor.home.rot.x;
    sp20.y = this->dyna.actor.home.rot.y;
    sp20.z = this->unk176 + this->dyna.actor.home.rot.z;
    Matrix_SetTranslateRotateYXZ(sp28.x, sp28.y, sp28.z, &sp20);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);
    Gfx_DrawDListOpa(play, object_d_lift_DL_000D10);
}
