/*
 * File: z_obj_lift.c
 * Overlay: ovl_Obj_Lift
 * Description: Dampé's Grave - Brown Elevator
 */

#include "z_obj_lift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjLift*)thisx)

void ObjLift_Init(Actor* thisx, PlayState* play);
void ObjLift_Destroy(Actor* thisx, PlayState* play);
void ObjLift_Update(Actor* thisx, PlayState* play);
void ObjLift_Draw(Actor* thisx, PlayState* play);
void func_8093D760(ObjLift* this);
void func_8093D9C0(ObjLift* this);
void func_8093D7A0(ObjLift* this, PlayState* play);
void func_8093DC90(Actor* thisx, PlayState* play);
void func_8093D8B4(ObjLift* this, PlayState* play);

void func_8093D3C0(ObjLift* this, PlayState* play);
void func_8093DB70(ObjLift* this);
void func_8093DA48(ObjLift* this, PlayState* play);
void func_8093DB90(ObjLift* this, PlayState* play);
void func_8093D88C(ObjLift* this);
#if 0
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

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -600, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(terminalVelocity, -15000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 350, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_STOP),
};

static f32 D_8093DD98[2] = { 0.1f, 0.05f };

static s16 D_8093DD50[8] = { 0, 0xA, 0x14, 0x1E, 0x28, 0x32, 0x3C, 0 };
static f32 D_8093DDA0[4] = { -18.0f, -9.0f, 0.0f, 0.0f };
#endif

extern s16 D_8093DD50[];
extern InitChainEntry sInitChain[];
extern f32 D_8093DD98[];
extern f32 D_8093DDA0[];
extern UNK_TYPE D_06000D10;
extern UNK_TYPE D_06000F00;
extern Vec2s D_8093DD60[];
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D3C0.s")

void func_8093D3C0(ObjLift* this, PlayState* play) {
    Vec3f pos;
    Vec3f vel;
    s32 pad;
    s32 i;
    Vec3f* actorPos = &this->dyna.actor.world.pos;

    for (i = 0; i < ARRAY_COUNT(&D_8093DD60); i++) {
        pos.x = (D_8093DD60[i].x * this->dyna.actor.scale.x) + actorPos->x;
        pos.y = actorPos->y;
        pos.z = (D_8093DD60[i].z * this->dyna.actor.scale.z) + actorPos->z;

        vel.x = D_8093DD60[i].x * this->dyna.actor.scale.x * 0.8f;
        vel.y = (Rand_ZeroOne() * 10.0f) + 6.0f;
        vel.z = D_8093DD60[i].z * this->dyna.actor.scale.z * 0.8f;

        EffectSsKakera_Spawn(play, &pos, &vel, actorPos, -0x100, ((s32)Rand_Next() > 0) ? 0x40 : 0x20, 0xF, 0xF, 0,
                             ((Rand_ZeroOne() * 50.0f) + 50.0f) * this->dyna.actor.scale.x, 0, 0x20, 0x32, -1, 0xED,
                             (Gfx*)&D_06000D10);
    }
    if ((this->dyna.actor.params & 1) == 0) {
        func_800BBFB0(play, &this->dyna.actor.world.pos, 120.0f, 0xC, 0x78, 0x64, 1);
    } else if ((this->dyna.actor.params & 1) == 1) {
        func_800BBFB0(play, &this->dyna.actor.world.pos, 60.0f, 8, 0x3C, 0x64, 1);
    }
}

#ifdef shit
void func_8093D3C0(ObjLift* this, PlayState* play) {
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    ? *temp_s0;
    PosRot* temp_s3;
    f32 temp_fv0;
    s32 temp_v0;
    ? *phi_s0;
    s32 phi_s1;

    temp_s3 = &this->dyna.actor.world;
    phi_s0 = &D_8093DD60;
    do {
        temp_fv0 = (f32)phi_s0->unk0;
        spBC = (temp_fv0 * this->dyna.actor.scale.x) + temp_s3->pos.x;
        spC0 = temp_s3->pos.y;
        spC4 = ((f32)phi_s0->unk2 * this->dyna.actor.scale.z) + temp_s3->pos.z;
        spB0 = temp_fv0 * this->dyna.actor.scale.x * 0.8f;
        spB4 = (Rand_ZeroOne() * 10.0f) + 6.0f;
        spB8 = (f32)phi_s0->unk2 * this->dyna.actor.scale.z * 0.8f;
        phi_s1 = 0x20;
        if (Rand_Next() > 0) {
            phi_s1 = 0x40;
        }
        EffectSsKakera_Spawn(play, (Vec3f*)&spBC, (Vec3f*)&spB0, &temp_s3->pos, (s16)-0x100, (s16)phi_s1, (s16)0xF,
                             (s16)0xF, (s16)0,
                             (s16)(s32)(((Rand_ZeroOne() * 50.0f) + 50.0f) * this->dyna.actor.scale.x), (s16)0,
                             (s16)0x20, 0x32, (s16)-1, (s16)0xED, (Gfx*)&D_06000D10);
        temp_s0 = phi_s0 + 4;
        phi_s0 = temp_s0;
    } while (temp_s0 != sInitChain);
    temp_v0 = this->dyna.actor.params & 1;
    if (temp_v0 == 0) {
        func_800BBFB0(play, &temp_s3->pos, 120.0f, 0xC, (s16)0x78, (s16)0x64, (u8)1);
        return;
    }
    if (temp_v0 == 1) {
        func_800BBFB0(play, &temp_s3->pos, 60.0f, 8, (s16)0x3C, (s16)0x64, (u8)1);
    }
}
#endif

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Init.s")

void ObjLift_Init(Actor* thisx, PlayState* play) {
    f32 temp_fv0;
    ObjLift* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    temp_fv0 = D_8093DD98[this->dyna.actor.params & 1];
    this->dyna.actor.scale.z = temp_fv0;
    this->dyna.actor.scale.x = temp_fv0;
    this->dyna.actor.scale.y = 0.055555556f;
    this->dyna.actor.shape.rot.z = 0;
    this->unk178 = this->dyna.actor.home.rot.z;
    this->dyna.actor.world.rot.z = this->dyna.actor.shape.rot.z;
    this->dyna.actor.home.rot.z = this->dyna.actor.shape.rot.z;
    DynaPolyActor_Init(&this->dyna, 1);
    if ((this->unk178 <= 0) && (Flags_GetSwitch(play, ((s16)this->dyna.actor.params >> 1) & 0x7F))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06000F00);
    this->unk160 = (s16)(Rand_Next() >> 0x10);
    this->unk162 = (s16)(Rand_Next() >> 0x10);
    this->unk164 = (s16)(Rand_Next() >> 0x10);
    func_8093D760(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Destroy.s")

void ObjLift_Destroy(Actor* thisx, PlayState* play) {
    ObjLift* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D760.s")

void func_8093D760(ObjLift* this) {
    this->unk166 = D_8093DD50[(this->dyna.actor.params >> 8) & 7];
    this->actionFunc = func_8093D7A0;
    this->dyna.actor.draw = ObjLift_Draw;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D7A0.s")

void func_8093D7A0(ObjLift* this, PlayState* play) {
    s32 pad;
    s16 quake;

    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        if (this->unk166 <= 0) {
            if (((this->dyna.actor.params >> 8) & 7) == 7) {
                func_8093D9C0(this);
            } else {
                quake = Quake_Add(play->cameraPtrs[play->activeCamera], 1);
                Quake_SetSpeed((s16)(quake), 0x2710);
                Quake_SetQuakeValues(quake, 2, 0, 0, 0);
                Quake_SetCountdown(quake, 0x14);
                func_8093D88C(this);
            }
        }
    } else {
        this->unk166 = D_8093DD50[(this->dyna.actor.params >> 8) & 7];
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
    sp2C.y += D_8093DDA0[this->dyna.actor.params & 1];
    temp_fv0 = BgCheck_EntityRaycastFloor5(&play->colCtx, &this->dyna.actor.floorPoly, &sp38, &this->dyna.actor, &sp2C);
    this->dyna.actor.floorHeight = temp_fv0;
    if ((D_8093DDA0[this->dyna.actor.params & 1] - 0.001f) <= (temp_fv0 - this->dyna.actor.world.pos.y)) {
        func_8093D3C0(this, play);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 0x14U, 0x2839U);
        if (this->unk178 > 0) {
            func_8093DB70(this);
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
        } else {
            Flags_SetSwitch(play, ((s16)this->dyna.actor.params >> 1) & 0x7F);
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
    ObjLift* this = (ObjLift*)thisx;
    if (this->unk166 > 0) {
        this->unk166--;
    }
    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Draw.s")

void ObjLift_Draw(Actor* thisx, PlayState* play) {
    ObjLift* this = THIS;

    Gfx_DrawDListOpa(play, (Gfx*)&D_06000D10);
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
    Gfx_DrawDListOpa(play, (Gfx*)&D_06000D10);
}
