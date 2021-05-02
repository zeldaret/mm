/*
 * File: z_obj_tokei_step.c
 * Overlay: obj_Tokei_Step
 * Description: Door to Top of Clock Tower
 */

#include "z_obj_tokei_step.h"

#define FLAGS 0x00400010

#define THIS ((ObjTokeiStep*)thisx)

void ObjTokeiStep_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeiStep_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AD5C70(ObjTokeiStep *this, ObjTokeiStepStep *step, GlobalContext* globalCtx);
void func_80AD5DFC(ObjTokeiStep *this);
void func_80AD5BB0(ObjTokeiStepStep *step);
void func_80AD5EB8(ObjTokeiStep *this);
void func_80AD5BE8(ObjTokeiStep *this, GlobalContext* globalCtx);
void func_80AD5F70(ObjTokeiStep *this);
int func_80AD5FB0(ObjTokeiStep *this, GlobalContext* globalCtx);
void func_80AD6348(ObjTokeiStep *this);
void func_80AD635C(ObjTokeiStep *this, GlobalContext* globalCtx);
void func_80AD63D4(ObjTokeiStep *this);
void func_80AD63E8(ObjTokeiStep *this, GlobalContext* globalCtx);
void func_80AD63F8(ObjTokeiStep *this);
void func_80AD642C(ObjTokeiStep *this, GlobalContext* globalCtx);
void func_80AD6480(ObjTokeiStep *this);
void func_80AD64A4(ObjTokeiStep *this, GlobalContext* globalCtx);
void func_80AD6508(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Tokei_Step_InitVars = {
    ACTOR_OBJ_TOKEI_STEP,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TOKEI_STEP,
    sizeof(ObjTokeiStep),
    (ActorFunc)ObjTokeiStep_Init,
    (ActorFunc)ObjTokeiStep_Destroy,
    (ActorFunc)ObjTokeiStep_Update,
    (ActorFunc)ObjTokeiStep_Draw
};
*/

extern InitChainEntry D_80AD6664[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};
*/
extern Gfx D_06000088[];

extern BgMeshHeader D_06000968;

extern f32 D_80AD6620[];
//f32 D_80AD6620[] = {-105.0f, -90.0f, -75.0f, -60.0f, -45.0f, -30.0f, -15.0f}

extern f32 D_80AD663C[];
//f32 D_80AD663C[] = {-60.0f, -40.0f, -20.0f, 0.0f, 20.0f, 40.0f, 60.0f}

extern Vec3f D_80AD6658;


void func_80AD5BB0(ObjTokeiStepStep *step) {
    MtxF* sysMatrix;

    sysMatrix = SysMatrix_GetCurrentState();
    sysMatrix->wx = step->unk0.x;
    sysMatrix->wy = step->unk0.y;
    sysMatrix->wz = step->unk0.z;
}

void func_80AD5BE8(ObjTokeiStep *this, GlobalContext *globalCtx) {
    s32 pad[2];
    s16 idx;

    idx = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 3);
    Quake_SetSpeed(idx, 0x4E20);
    Quake_SetQuakeValues(idx, 1, 0, 0, 0);
    Quake_SetCountdown(idx, 7);
    func_8013ECE0(this->dyna.actor.xyzDistToPlayerSq, 0x78, 0x14, 0xA);
}

void func_80AD5C70(ObjTokeiStep *this, ObjTokeiStepStep *step, GlobalContext *globalCtx) {
    int i;
    s32 pad;
    Vec3f sp84;
    Vec3f sp78;
    
    Matrix_RotateY(this->dyna.actor.shape.rot.y, 0);

    sp84.y = 115.0f;
    sp84.z = -10.0f;

    for(i=0; i<7; i++) {
        sp84.x = D_80AD663C[i];
        SysMatrix_MultiplyVector3fByState(&sp84, &sp78);
        sp78.x += step->unk0.x;
        sp78.y += step->unk0.y;
        sp78.z += step->unk0.z;
        func_800B1210(globalCtx, &sp78, &D_801D15B0, &D_80AD6658, (s32) ((Rand_ZeroOne() * 40.0f) + 80.0f), (s32) ((Rand_ZeroOne() * 20.0f) + 50.0f));
    }
}

void func_80AD5DFC(ObjTokeiStep *this) {
    int i;
    ObjTokeiStepStep *step;
    Vec3f sp4c;
    s32 pad;

    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    sp4c.x = 0.0f;
    sp4c.y = 0.0f;

    for(i=0; i<7; i++) {
        step = &this->steps[i];
        sp4c.z = i * -20.0f;
        SysMatrix_MultiplyVector3fByState(&sp4c, &step->unk0);
        step->unkc = 0.0f;
        step->unk12 = 0;
    }
}

void func_80AD5EB8(ObjTokeiStep *this) {
    int i;
    ObjTokeiStepStep *step;
    Vec3f sp44;

    SysMatrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    
    sp44.x = 0.0f;
    for (i=0; i<7; i++) {
        step = &this->steps[i];
        sp44.y = D_80AD6620[i];
        sp44.z = i * -20.0f;
        SysMatrix_MultiplyVector3fByState(&sp44, step);
    }
}

void func_80AD5F70(ObjTokeiStep *this) {
    int i;

    this->steps[0].unk10 = 0;
    for(i=1; i<7; i++) {
        this->steps[i].unk10 = 0xA;
    }
}

s32 func_80AD5FB0(ObjTokeiStep *this, GlobalContext *globalCtx) {
    int i;
    ObjTokeiStepStep *step;
    f32 tempf20;
    ObjTokeiStep *new_var = this;
    s32 ret = 1;
    s32 phi_v1 = 1;

    for(i=0; i<7; i++) {
        step = &this->steps[i];
        if (phi_v1 && step->unk10 > 0) {
            step->unk10--;
            ret = 0;
        }
        if (phi_v1 && step->unk12 < 3 && step->unk10 <= 0){
            tempf20 = D_80AD6620[i] + this->dyna.actor.world.pos.y;
            if (step->unk13 == 0) {
                Audio_PlayActorSound2(&this->dyna.actor, 0x2945);
                step->unk13 = 1;
            }
            step->unkc += -2.5f;
            step->unkc *= 0.83f;
            step->unk0.y += step->unkc;
            ret = 0;
            if (step->unk0.y < tempf20) {
                step->unk12++;
                if (step->unk12 >= 3) {
                    step->unk0.y = tempf20;
                } else {
                    step->unkc *= -0.4f;
                    if (step->unkc > 4.0f) {
                        step->unkc = 4.0f;
                    }
                    step->unk0.y = (step->unk0.y - tempf20) * -0.4f;
                    if (step->unkc < step->unk0.y) {
                        step->unk0.y = step->unkc + tempf20;
                    } else {
                        step->unk0.y += tempf20;
                    }
                    if (step->unk12 == 1) {
                        func_80AD5C70(new_var, step, globalCtx);
                        func_80AD5BE8(new_var, globalCtx);
                    }
                }
            }
        }
        phi_v1 = step->unk12 > 0;
    }
    return ret;
}

void ObjTokeiStep_Init(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    globalCtx = globalCtx;
    Actor_ProcessInitChain(&this->dyna.actor, D_80AD6664);
    BcCheck3_BgActorInit(&this->dyna, 0);
    if ((globalCtx->sceneNum == 0x6F) && (gSaveContext.extra.sceneSetupIndex == 2) && (globalCtx->csCtx.unk12 == 0)) {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000968);
        func_80AD5DFC(this);
        func_80AD6348(this);
    }
    else if (!((((s32) gSaveContext.perm.day % 5) != 3) || (gSaveContext.perm.time >= 0x4000)) || (s32) gSaveContext.perm.day >= 4) {
        this->dyna.actor.draw = func_80AD6508;
        func_80AD5EB8(this);
        func_80AD6480(this);
    } else {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000968);
        func_80AD5DFC(this);
        func_80AD63D4(this);
    }
}

void ObjTokeiStep_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}


void func_80AD6348(ObjTokeiStep *this) {
    this->actionFunc = func_80AD635C;
}

void func_80AD635C(ObjTokeiStep *this, GlobalContext *globalCtx) {
    CsCmdActorAction *temp_v1;

    if (func_800EE29C(globalCtx, 0x86)) {
        temp_v1 = globalCtx->csCtx.actorActions[func_800EE200(globalCtx, 0x86)];
        if ((globalCtx->csCtx.frames == (*temp_v1).startFrame) && temp_v1->unk0) {
            this->dyna.actor.draw = func_80AD6508;
            func_80AD63F8(this);
        }
    }
}

void func_80AD63D4(ObjTokeiStep *this) {
    this->actionFunc = func_80AD63E8;
}

void func_80AD63E8(ObjTokeiStep *this, GlobalContext *globalCtx) {
}

void func_80AD63F8(ObjTokeiStep *this) {
    func_80AD5F70(this);
    this->actionFunc = func_80AD642C;
}

void func_80AD642C(ObjTokeiStep *this, GlobalContext *globalCtx) {
    if (func_80AD5FB0(this, globalCtx) != 0) {
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        func_80AD6480(this);
    }
}

void func_80AD6480(ObjTokeiStep *this) {
    this->dyna.actor.flags &= ~0x10;
    this->actionFunc = func_80AD64A4;
}

void func_80AD64A4(ObjTokeiStep *this, GlobalContext *globalCtx) {
}

void ObjTokeiStep_Update(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    this->actionFunc(thisx, globalCtx);
}

void ObjTokeiStep_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;

    func_800BDFC0(globalCtx, D_06000088);
}

#if 1
void func_80AD6508(Actor *thisx, GlobalContext *globalCtx) {
    ObjTokeiStep *this = THIS;
    int i;
    ObjTokeiStepStep *step;

    OPEN_DISPS(globalCtx->state.gfxCtx)
    gSPDisplayList(POLY_OPA_DISP++, &sSetupDL[6 * 0x19]);

    for(i=0; i<7; i++) {
        step = &this->steps[i];
        func_80AD5BB0(step);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06000088);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tokei_Step_0x80AD5BB0/func_80AD6508.asm")
#endif