#include "z_en_encount2.h"

#define FLAGS 0x00000010

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808E1714(EnEncount2* this, GlobalContext* globalCtx);
void func_808E17C4(EnEncount2* this, GlobalContext* globalCtx);
void func_808E18A8(EnEncount2* this, GlobalContext* globalCtx);
void func_808E16FC(EnEncount2* this);
void func_808E1A24(EnEncount2* this, Vec3f* vec, s16 arg2);
void func_808E1B4C(EnEncount2* this, GlobalContext* globalCtx);
void func_808E1C9C(EnEncount2* this, GlobalContext* globalCtx);

const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    (ActorFunc)EnEncount2_Destroy,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = { // D_808E1EF0
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

static ColliderJntSphInit sJntSphInit = { // D_808E1F14 
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, sJntSphElementsInit,
};

DamageTable damageTable[] = {
    0xF0, 0xF0, 0x00, 0xF0, 0xE1, 0xE1, 0x00, 0xE1, 0xF0, 0xF0, 0xF0, 0xE1, 0xE1, 0xE1, 0xF0, 0xF0, 
    0xE1, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0xE1, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
};

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    s8 pad[4];
    CollisionHeader* colHeader = NULL;

    BcCheck3_BgActorInit(&this->dynaActor, 0);
    BgCheck_RelocateMeshHeader(&D_06002420, &colHeader);
    this->dynaActor.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dynaActor, colHeader);
    ActorShape_Init(&this->dynaActor.actor.shape, 0.0f, func_800B3FC0, 25.0f);
    this->dynaActor.actor.colChkInfo.mass = 0xFF;
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->dynaActor, &sJntSphInit, &this->colElement);

    this->dynaActor.actor.targetMode = 6;
    this->dynaActor.actor.colChkInfo.health = 1;
    this->scale = 0.1;
    this->switchFlag = (s16) (this->dynaActor.actor.params & 0x7F);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->switchFlag >= 0) && (Actor_GetSwitchFlag(globalCtx, this->switchFlag) != 0)) {
        Actor_MarkForDeath(this);
        return;
    }

    this->collider.elements->dim.modelSphere.radius = 0x39;
    this->collider.elements->dim.scale = 1.0f;
    this->collider.elements->dim.modelSphere.center.x = 0;
    this->collider.elements->dim.modelSphere.center.y = -4;
    this->collider.elements->dim.modelSphere.center.z = 0;

    this->dynaActor.actor.colChkInfo.damageTable = &damageTable;
    func_808E16FC(this);
}

void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dynaActor.bgId);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

// init extension func
void func_808E16FC(EnEncount2* this) {
    this->statePopped = 0;
    this->actionFunc = &func_808E1714;
}

//actionfunc: idle floating
void func_808E1714(EnEncount2* this, GlobalContext* globalCtx) {
    this->oscillationAngle += 1500.0f;
    this->dynaActor.actor.velocity.y = Math_SinS(this->oscillationAngle);
    Math_ApproachF(&this->scale, 0.1f, 0.3f, 0.01f);
    if (((this->collider.base.acFlags & AC_HIT) != 0) && (this->dynaActor.actor.colChkInfo.damageEffect == 0xE)) {
        this->dynaActor.actor.colChkInfo.health = 0;
        this->statePopped = 1;
        this->actionFunc = func_808E17C4; // pop
    }
}

//actionfunc: pop
void func_808E17C4(EnEncount2* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f curPos;

    Math_Vec3f_Copy(&curPos, &this->dynaActor.actor.world.pos);
    curPos.y += 60.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, curPos.x, curPos.y, curPos.z,
       0xFF, 0xFF, 0xC8, 0x0001);

    for(i = 0; i != 100; i++){
        func_808E1A24(this, &curPos, 10); // init particle
    }

    Audio_PlayActorSound2(this, 0x2949);
    this->deathTimer = 30;
    this->actionFunc = func_808E18A8; // post-pop
}

//actionfunc: after pop, waiting for timer then death
void func_808E18A8(EnEncount2* this, GlobalContext* globalCtx) {
    if (this->deathTimer == 0) {
        if (this->switchFlag >= 0) {
            Actor_SetSwitchFlag(globalCtx, this->switchFlag);
        }
        Actor_MarkForDeath(&this->dynaActor.actor);
    }
}

void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    s8 pad[4];

    if (this->deathTimer != 0) {
        this->deathTimer--;
    }

    this->dynaActor.actor.shape.rot.y = this->dynaActor.actor.world.rot.y;
    Actor_SetHeight(&this->dynaActor.actor, 30.0f);
    Actor_SetScale(&this->dynaActor.actor, this->scale);
    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->dynaActor.actor);
    func_808E1B4C(this, globalCtx); // update all particles

    if (! this->statePopped) {
        Collider_UpdateSpheresElement(&this->collider, 0, &this->dynaActor.actor);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}

void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnEncount2* this = THIS;
    if (this->statePopped != 1) { // is NOT popped (0 only other option)
        func_800BDFC0(globalCtx, &D_06000A00);
        func_800BDFC0(globalCtx, &D_06000D78);
    }
    func_808E1C9C(this, globalCtx);
}

// init all particles
void func_808E1A24(EnEncount2* this, Vec3f *vec, s16 fadeDelay) {
    s16 i;
    EnEncount2Particle *sPtr = &this->particles;

    for (i = 0; i < 200; ++i) {
        if ( ! sPtr->enabled) {
            sPtr->enabled = 1;
            sPtr->unk4 = *vec;
            sPtr->alphaFadeDelay = fadeDelay;
            sPtr->alpha = 0xFF;

            sPtr->unk24.x = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->unk24.y = (Rand_ZeroOne() - 0.5f) * 10.0f;
            sPtr->unk24.z = (Rand_ZeroOne() - 0.5f) * 10.0f;

            sPtr->unk18.x = Rand_ZeroOne() - 0.5f;
            sPtr->unk18.y = Rand_ZeroOne() - 0.5f;
            sPtr->unk18.z = Rand_ZeroOne() - 0.5f;

            sPtr->scale = (Rand_ZeroFloat(1.0f) * 0.5f) + 2.0f;
            return;
        }
        sPtr++;
    }
}

// updates all effect structs
void func_808E1B4C(EnEncount2* this, GlobalContext* globalCtx) {
    s32 i;
    EnEncount2Particle *sPtr = &this->particles;

    for(i = 0 ; i < 200; i += 2) {
        if (sPtr->enabled) {
            sPtr->unk4.x += sPtr->unk18.x;
            sPtr->unk4.y += sPtr->unk18.y;
            sPtr->unk4.z += sPtr->unk18.z;
            sPtr->unk18.x += sPtr->unk24.x;
            sPtr->unk18.y += sPtr->unk24.y;
            sPtr->unk18.z += sPtr->unk24.z;
            if (sPtr->alphaFadeDelay != 0) {
                sPtr->alphaFadeDelay--;
            } else {
                sPtr->alpha -= 10;
                if (sPtr->alpha < 10) {
                    sPtr->enabled = 0;
                }
            }
        }
        sPtr++;

        if (sPtr->enabled) {
            sPtr->unk4.x += sPtr->unk18.x;
            sPtr->unk4.y += sPtr->unk18.y;
            sPtr->unk4.z += sPtr->unk18.z;
            sPtr->unk18.x += sPtr->unk24.x;
            sPtr->unk18.y += sPtr->unk24.y;
            sPtr->unk18.z += sPtr->unk24.z;
            if (sPtr->alphaFadeDelay != 0) {
                sPtr->alphaFadeDelay--;
            } else {
                sPtr->alpha -= 10;
                if (sPtr->alpha < 10) {
                    sPtr->enabled = 0;
                }
            }
        }
        sPtr++;
    }
}

// draw particles
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E1C9C.asm")
