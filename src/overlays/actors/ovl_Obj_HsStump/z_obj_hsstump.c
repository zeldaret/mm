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
    (ActorFunc)ObjHsStump_Draw
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
//static Vec3f D_80BDAF84 = {0.0f, 0.0f, 0.0f};

void ObjHsStump_Init(Actor *thisx, GlobalContext *globalCtx) {
    ObjHsStump *this = THIS;
    s16 *params;

    params = &this->dyna.actor.params;  
    Actor_ProcessInitChain(&this->dyna.actor, D_80BDAF80);
    this->unk162 = (this->dyna.actor.params >> 0xC) & 0xF;
    this->unk160 = *params & 0x7F;
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_060011B0);
    if (this->unk162 != 0) {
        if (this->unk162 != 1) {
            return;
        }
        if (Actor_GetSwitchFlag(globalCtx, this->unk160)) {
            this->unk162 = 0;
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

void ObjHsStump_Idle(ObjHsStump* this, GlobalContext *globalCtx) {
    if (this->unk162 == 1) {
        if (Actor_GetSwitchFlag(globalCtx, this->unk160)) {
            ObjHsStump_SetupAppear(this, globalCtx);
        }
    }
}

void ObjHsStump_SetupAppear(ObjHsStump *this, GlobalContext *globalCtx) {
    this->dyna.actor.draw = ObjHsStump_Draw;
    this->unk164 = 0;
    this->unk166 = 0;
    this->unk168 = 3640.0f;
    func_8019F128(0x3A86);
    this->actionFunc = func_80BDABCC;
}

#ifdef NON_MATCHING
void func_80BDABCC(ObjHsStump *this, GlobalContext *globalCtx) {
    int i;
    Vec3f iceSmokePosOffset;
    Vec3f iceSmokeVelOffset;
    Vec3f iceSmokeVel;
    Vec3f iceSmokePos;
    s16 offsetAngle;
    s32 tmp;
    s16 tmp3;
    

    if (this->unk164 >= 0) {
        Math_SmoothStepToF(&this->unk168, 0.0f, 1.0f, this->unk164 + 18.0f, 0.01f);
        this->dyna.actor.shape.rot.x = (Math_SinS(this->unk166) * this->unk168) + this->dyna.actor.home.rot.x;
        this->dyna.actor.shape.rot.z = (Math_SinS(this->unk166 * 2) * this->unk168) + this->dyna.actor.home.rot.z;
        this->unk166 += 0x2000;
    }
    if (this->unk164 < 0xB) {
        if (this->unk164 == 0) {
            iceSmokePosOffset.x = 1.0f;
            iceSmokePosOffset.y = 0.5f;
            iceSmokePosOffset.z = 0.0f;
            iceSmokeVelOffset.x = 1.0f;
            iceSmokeVelOffset.y = 0.5f;
            iceSmokeVelOffset.z = 0.0f;

            tmp3 = 4;
            tmp = 360.0f / tmp3;

            for(i=0; i<tmp3; i++) {
                offsetAngle = tmp * 182.04445f * i;
                Lib_Vec3f_TranslateAndRotateY(&this->dyna.actor.world.pos, offsetAngle, &iceSmokePosOffset, &iceSmokePos);
                Lib_Vec3f_TranslateAndRotateY(&D_801D15B0, offsetAngle, &iceSmokeVelOffset, &iceSmokeVel);
                EffectSsIceSmoke_Spawn(globalCtx, &iceSmokePos, &iceSmokeVel, &D_80BDAF84, 0x64);
            }
        }
    }
    if (this->unk164 >= 0xA) {
        Math_SmoothStepToF(&this->dyna.actor.scale.x, 0.17999999f, 1.0f, 0.01f, 0.001f);
        Actor_SetScale(&this->dyna.actor, this->dyna.actor.scale.x);
    }
    if (this->dyna.actor.scale.x == 0.17999999f) {
        this->unk162 = 0;
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        ObjHsStump_SetupIdle(this, globalCtx);
    }
    this->unk164++;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_HsStump_0x80BDAA30/func_80BDABCC.asm")
#endif

void ObjHsStump_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    ObjHsStump *this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjHsStump_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump *this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjHsStump_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjHsStump *this = THIS;

    func_800BDFC0(globalCtx, D_060003B8);
}