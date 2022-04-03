/*
 * File: z_obj_dora.c
 * Overlay: ovl_Obj_Dora
 * Description: Swordsman's School - Gong
 */

#include "z_obj_dora.h"
#include "assets/objects/object_dora/object_dora.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDora*)thisx)

void ObjDora_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjDora_SetupWait(ObjDora* this);
void ObjDora_Wait(ObjDora* this, GlobalContext* globalCtx);
void ObjDora_SetupMoveGong(ObjDora* this);
void ObjDora_MoveGong(ObjDora* this, GlobalContext* globalCtx);
bool ObjDora_IsHalfHourly(u16 time);
void ObjDora_CheckCollision(ObjDora* this, GlobalContext* globalCtx);

const ActorInit Obj_Dora_InitVars = {
    ACTOR_OBJ_DORA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjDora),
    (ActorFunc)ObjDora_Init,
    (ActorFunc)ObjDora_Destroy,
    (ActorFunc)ObjDora_Update,
    (ActorFunc)ObjDora_Draw,
};

static ColliderTrisElementInit sTrisElementsInit[6] = {
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0x00100000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, -35.0f, 0.0f }, { 260.0f, -185.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0x00100000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 260.0f, -185.0f, 0.0f }, { 260.0f, -485.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 260.0f, -485.0f, 0.0f }, { 0.0f, -635.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, -635.0f, 0.0f }, { -260.0f, -485.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -260.0f, -485.0f, 0.0f }, { -260.0f, -185.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -260.0f, -185.0f, 0.0f }, { 0.0f, -35.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_TRIS,
    },
    6,
    sTrisElementsInit,
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 8, 0, 0, 0, MASS_HEAVY };

void ObjDora_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjDora* this = THIS;
    s32 i, j;
    Vec3f vtx[3];
    s32 buf = 0, buff2 = 0;

    Actor_SetScale(&this->actor, 0.1f);
    ActorShape_Init(&this->actor.shape, 0.0f, &ActorShadow_DrawCircle, 36.0f);

    this->gongRotation.x = 0;
    this->gongRotation.z = 0;
    this->gongAngle.x = 0;
    this->gongAngle.z = 0;
    this->lastGongHitType = DORA_HIT_NONE;
    this->rupeeDropTimer = 0;
    this->collisionCooldownTimer = 0;
    this->unk3AA = 0;
    this->gongForce.x = 0.0f;
    this->gongForce.y = 0.0f;
    this->gongForce.z = 0.0f;

    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->actor, &sTrisInit, this->colliderTrisElements);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    Matrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                          &this->actor.shape.rot);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->colliderTrisElements); i++) {
        for (j = 0; j < ARRAY_COUNT(vtx); j++) {
            Matrix_MultiplyVector3fByState(&sTrisElementsInit[i].dim.vtx[j], &vtx[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &vtx[0], &vtx[1], &vtx[2]);
    }
    ObjDora_SetupWait(this);
}

void ObjDora_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjDora* this = THIS;

    Collider_DestroyTris(globalCtx, &this->colliderTris);
}

void ObjDora_SetupWait(ObjDora* this) {
    this->actionFunc = ObjDora_Wait;
}

void ObjDora_Wait(ObjDora* this, GlobalContext* globalCtx) {
}

void ObjDora_SetupMoveGong(ObjDora* this) {
    if (this->lastGongHitType == DORA_HIT_LIGHT) {
        this->gongForce.x = 2.0f;
        this->gongForce.y = 5461.0f;
        this->gongForce.z = 1820.0f;
    } else {
        this->gongForce.x = 4.0f;
        this->gongForce.y = 12743.0f;
        this->gongForce.z = 5461.0f;
    }
    this->gongAngle.x = 0;
    this->gongAngle.z = 0;
    this->actionFunc = ObjDora_MoveGong;
}

void ObjDora_MoveGong(ObjDora* this, GlobalContext* globalCtx) {

    if ((this->gongForce.y < 182.0f) && (this->gongForce.z < 182.0f)) {
        this->lastGongHitType = DORA_HIT_LIGHT;
        ObjDora_SetupWait(this);
    }

    Math_SmoothStepToF(&(this->gongForce.x), 0, 0.2f, 0.2f, 0.1f);
    Math_SmoothStepToF(&(this->gongForce.y), 0, 0.5f, 54.0f, 18.0f);
    Math_SmoothStepToF(&(this->gongForce.z), 0, 0.5f, 54.0f, 18.0f);
    this->gongAngle.x += 0x1555;
    this->gongAngle.z += 0x238E;
    this->gongRotation.x = Math_SinS(this->gongAngle.x) * this->gongForce.y;
    this->gongRotation.z = Math_SinS(this->gongAngle.z) * this->gongForce.z;
}

bool ObjDora_IsHalfHourly(u16 time) {
    f32 temp = time;
    temp -= (1365.3334f * (s32)(time / 1365.3334f));

    if ((temp < 45.511112f) || (1319.8223f < temp)) {
        return true;
    }

    return false;
}

void ObjDora_CheckCollision(ObjDora* this, GlobalContext* globalCtx) {
    Actor* itemDrop;
    u16 time;

    if (this->colliderTris.base.acFlags & AC_HIT) {
        time = gSaveContext.save.time;
        this->colliderTris.base.acFlags &= ~AC_HIT;
        this->collisionCooldownTimer = 5;

        switch (this->actor.colChkInfo.damageEffect) {
            case 14:
            case 15:
                if (this->actor.colChkInfo.damageEffect == 15) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DORA_S);
                    this->lastGongHitType = DORA_HIT_LIGHT;
                } else {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DORA_L);
                    this->lastGongHitType = DORA_HIT_STRONG;
                }

                func_800BC848(&this->actor, globalCtx, 5, 10);
                ObjDora_SetupMoveGong(this);

                if ((ObjDora_IsHalfHourly(time) == 1) && (this->rupeeDropTimer == 0)) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
                    itemDrop = Item_DropCollectible(globalCtx, &this->actor.world.pos, ITEM00_RUPEE_BLUE);
                    itemDrop->world.rot.y = this->actor.world.rot.y;
                    itemDrop->world.rot.y += (s32)(Rand_Centered() * 90.0f * 182.04445f);
                    itemDrop->velocity.y = 5.0f;
                    itemDrop->gravity = -1.0f;
                    this->rupeeDropTimer = 40;
                }
                break;
        }
    }

    if (this->rupeeDropTimer > 0) {
        this->rupeeDropTimer -= 1;
    }

    if (this->collisionCooldownTimer > 0) {
        this->collisionCooldownTimer -= 1;
    } else {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
    }
}

void ObjDora_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjDora* this = THIS;

    this->actionFunc(this, globalCtx);
    ObjDora_CheckCollision(this, globalCtx);
}

void ObjDora_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjDora* this = THIS;
    f32 gongXForce;

    static Vec3f position = { 0.0f, -61.5f, 0.0f };

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->actionFunc == ObjDora_MoveGong) {
        gongXForce = this->gongForce.x;
        if ((globalCtx->state.frames % 2) != 0) {
            gongXForce *= -1.0f;
        }

        Matrix_StatePush();
        Matrix_InsertXRotation_s(this->gongRotation.x, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, &gDoraGongDL);

        Matrix_InsertTranslation(position.x, position.y + gongXForce, position.z + gongXForce, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->gongRotation.z - this->gongRotation.x, MTXMODE_APPLY);
        Matrix_InsertTranslation(-position.x, -position.y, -position.z, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, &gDoraChainDL);

        Matrix_StatePop();
    } else {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, &gDoraChainDL);
        gSPDisplayList(POLY_OPA_DISP++, &gDoraGongDL);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
