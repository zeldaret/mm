#include "z_obj_hsstump.h"

#define FLAGS 0x00000010

#define THIS ((ObjHsStump*)thisx)

void ObjHsStump_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHsStump_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjHsStump_SetupIdle(ObjHsStump* this, GlobalContext* globalCtx);
void ObjHsStump_Idle(ObjHsStump* this, GlobalContext* globalCtx);
void ObjHsStump_SetupAppear(ObjHsStump* this, GlobalContext* globalCtx);
void func_80BDABCC(ObjHsStump* this, GlobalContext* globalCtx);

/*
const ActorInit Obj_HsStump_InitVars = {
    ACTOR_OBJ_HSSTUMP,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HSSTUMP,
    sizeof(ObjHsStump),
    (ActorFunc)ObjHsStump_Init,
    (ActorFunc)ObjHsStump_Destroy,
    (ActorFunc)ObjHsStump_Update,
    (ActorFunc)ObjHsStump_Draw,
};
*/

extern Gfx D_060003B8[];

extern CollisionHeader D_060011B0;

extern InitChainEntry D_80BDAF80[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 180, ICHAIN_STOP),
};
*/

extern Vec3f D_80BDAF84;
// static Vec3f iceSmokeAccel = {0.0f, 0.0f, 0.0f};

void ObjHsStump_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, D_80BDAF80);
    this->isHidden = OBJHSSTUMP_GET_ISHIDDEN(thisx);
    this->switchFlag = OBJHSSTUMP_GET_SWITCHFLAG(thisx); // Must be thisx to match
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_060011B0);
    if (this->isHidden != 0) {
        if (this->isHidden != 1) {
            return;
        }
        if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
            this->isHidden = 0;
        } else {
            this->dyna.actor.draw = NULL;
            Actor_SetScale(&this->dyna.actor, 0.0f);
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        }
    }
    ObjHsStump_SetupIdle(this, globalCtx);
}

void ObjHsStump_SetupIdle(ObjHsStump* this, GlobalContext* globalCtx) {
    this->actionFunc = ObjHsStump_Idle;
}

void ObjHsStump_Idle(ObjHsStump* this, GlobalContext* globalCtx) {
    if (this->isHidden == 1) {
        if (Flags_GetSwitch(globalCtx, this->switchFlag)) {
            ObjHsStump_SetupAppear(this, globalCtx);
        }
    }
}

void ObjHsStump_SetupAppear(ObjHsStump* this, GlobalContext* globalCtx) {
    this->dyna.actor.draw = ObjHsStump_Draw;
    this->framesAppeared = 0;
    this->rotAngle = 0;
    this->rotFactor = 3640.0f;
    func_8019F128(0x3A86);
    this->actionFunc = func_80BDABCC;
}

#ifdef NON_MATCHING
// Correct instructions, but they are all out of order in the (this->framesAppeared) < 11 branch
void func_80BDABCC(ObjHsStump* this, GlobalContext* globalCtx) {
    s32 i;
    s32 angle;
    s16 numDirections;
    Vec3f iceSmokePosOffset;
    Vec3f iceSmokeVelOffset;
    s16 offsetAngle;
    Vec3f iceSmokeVel;
    f32 angleBAMS;
    Vec3f iceSmokePos;

    if (this->framesAppeared >= 0) {
        Math_SmoothStepToF(&this->rotFactor, 0.0f, 1.0f, this->framesAppeared + 18.0f, 0.01f);
        this->dyna.actor.shape.rot.x = (Math_SinS(this->rotAngle) * this->rotFactor) + this->dyna.actor.home.rot.x;
        this->dyna.actor.shape.rot.z = (Math_SinS(this->rotAngle * 2) * this->rotFactor) + this->dyna.actor.home.rot.z;
        this->rotAngle += 0x2000;
    }
    if (this->framesAppeared < 11) {
        if (this->framesAppeared == 0) {
            iceSmokePosOffset.x = 1.0f;
            iceSmokePosOffset.y = 0.5f;
            iceSmokePosOffset.z = 0.0f;
            iceSmokeVelOffset.x = 1.0f;
            iceSmokeVelOffset.y = 0.5f;
            iceSmokeVelOffset.z = 0.0f;

            numDirections = 4;
            angle = 360.0f / numDirections;
            angleBAMS = angle * (0x10000 / 360.0f);

            for (i = 0; i < numDirections; i++) {
                offsetAngle = i * angleBAMS;
                Lib_Vec3f_TranslateAndRotateY(&this->dyna.actor.world.pos, offsetAngle, &iceSmokePosOffset,
                                              &iceSmokePos);
                Lib_Vec3f_TranslateAndRotateY(&D_801D15B0, offsetAngle, &iceSmokeVelOffset, &iceSmokeVel);
                EffectSsIceSmoke_Spawn(globalCtx, &iceSmokePos, &iceSmokeVel, &D_80BDAF84, 0x64);
            }
        }
    }
    if (this->framesAppeared >= 10) {
        Math_SmoothStepToF(&this->dyna.actor.scale.x, 0.17999999f, 1.0f, 0.01f, 0.001f);
        Actor_SetScale(&this->dyna.actor, this->dyna.actor.scale.x);
    }
    if (this->dyna.actor.scale.x == 0.17999999f) {
        this->isHidden = 0;
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        ObjHsStump_SetupIdle(this, globalCtx);
    }
    this->framesAppeared++;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_HsStump_0x80BDAA30/func_80BDABCC.asm")
#endif

void ObjHsStump_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjHsStump_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjHsStump_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_060003B8);
}
