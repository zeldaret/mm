/*
 * File: z_obj_dora.c
 * Overlay: ovl_Obj_Dora
 * Description: Swordsman's School - Gong
 */

#include "z_obj_dora.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDora*)thisx)

void ObjDora_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B60C9C(ObjDora* this);
void func_80B60CB0(ObjDora* this, GlobalContext* globalCtx);
void func_80B60CC0(ObjDora* this);
void func_80B60D34(ObjDora* this, GlobalContext* globalCtx);
bool func_80B60E54(u16 time);
void func_80B60EE8(ObjDora *this, GlobalContext *globalCtx);

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

// static ColliderTrisElementInit sTrisElementsInit[6] = {
static ColliderTrisElementInit D_80B61310[6] = {
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x00100000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, -35.0f, 0.0f }, { 260.0f, -185.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0x00100000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 260.0f, -185.0f, 0.0f }, { 260.0f, -485.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 260.0f, -485.0f, 0.0f }, { 0.0f, -635.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, -635.0f, 0.0f }, { -260.0f, -485.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -260.0f, -485.0f, 0.0f }, { -260.0f, -185.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK5, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -260.0f, -185.0f, 0.0f }, { 0.0f, -35.0f, 0.0f }, { 0.0f, -335.0f, 0.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B61478 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_TRIS, },
    6, D_80B61310, // sTrisElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_80B61488 = {
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

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B614A8 = { 8, 0, 0, 0, MASS_HEAVY };

extern UNK_TYPE D_06004160;
extern UNK_TYPE D_06003FD0;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Init.s")
void ObjDora_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjDora *this = THIS;
    s32 i, j;
    Vec3f vtx[3];
    s32 buf = 0, buff2 = 0;

    Actor_SetScale(&this->actor, 0.1f);
    ActorShape_Init(&this->actor.shape, 0.0f, &ActorShadow_DrawCircle, 36.0f);

    this->unk3A2 = 0;
    this->unk3A4 = 0;
    this->unk39C = 0;
    this->unk39E = 0;
    this->unk3A0 = 0;
    this->unk3A6 = 0;
    this->unk3A8 = 0;
    this->unk3AA = 0;
    this->unk390 = 0.0f;
    this->unk394 = 0.0f;
    this->unk398 = 0.0f;
    
    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->actor, &D_80B61478, this->colliderTrisElements);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_80B61488, &D_80B614A8);

    Matrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, &this->actor.shape.rot);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    
    for (i = 0; i < ARRAY_COUNT(this->colliderTrisElements); i++) {
        for (j = 0; j < ARRAY_COUNT(vtx); j++) {
            Matrix_MultiplyVector3fByState(&D_80B61310[i].dim.vtx[j], &vtx[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &vtx[0], &vtx[1], &vtx[2]);
    }
    func_80B60C9C(this);
    return;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Destroy.s")
void ObjDora_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjDora *this = THIS;
    
    Collider_DestroyTris(globalCtx, &this->colliderTris);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60C9C.s")
void func_80B60C9C(ObjDora* this) {
    this->actionFunc = func_80B60CB0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60CB0.s")
void func_80B60CB0(ObjDora* this, GlobalContext* globalCtx) {

}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60CC0.s")
void func_80B60CC0(ObjDora* this) {
    if (this->unk3A0 == 1) {
        this->unk390 = 2.0f;
        this->unk394 = 5461.0f;
        this->unk398 = 1820.0f;
    } else {
        this->unk390 = 4.0f;
        this->unk394 = 12743.0f;
        this->unk398 = 5461.0f;
    }
    this->unk39C = 0;
    this->unk39E = 0;
    this->actionFunc = func_80B60D34;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60D34.s")
void func_80B60D34(ObjDora* this, GlobalContext* globalCtx) {

    if ((this->unk394 < 182.0f) && (this->unk398 < 182.0f)) {
        this->unk3A0 = 1;
        func_80B60C9C(this);
    }

    Math_SmoothStepToF(&(this->unk390), 0, 0.2f, 0.2f, 0.1f);
    Math_SmoothStepToF(&(this->unk394), 0, 0.5f, 54.0f, 18.0f);
    Math_SmoothStepToF(&(this->unk398), 0, 0.5f, 54.0f, 18.0f);
    this->unk39C += 0x1555;
    this->unk39E += 0x238E;
    this->unk3A2 = Math_SinS(this->unk39C) * this->unk394;
    this->unk3A4 = Math_SinS(this->unk39E) * this->unk398;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60E54.s")
bool func_80B60E54(u16 time) {
    f32 phi_f0 = (f32) time;
    phi_f0 -= (1365.3334f * (s32) (phi_f0 / 1365.3334f));
    
    if ((phi_f0 < 45.511112f) || (1319.8223f < phi_f0)) {
        return 1;
    }

    return 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60EE8.s")
extern f32 D_80B614E4;
void func_80B60EE8(ObjDora *this, GlobalContext *globalCtx) {
    Actor *itemDrop;
    u16 time; // good
    f32 itemRandRotation; // good
    u8 damageEffect; // good
    
    if ((this->colliderTris.base.acFlags & AC_HIT) != 0) {
        time = gSaveContext.time;
        damageEffect = this->actor.colChkInfo.damageEffect;
        this->colliderTris.base.acFlags &= 0xFFFD; // reset flag 2 (AC_HIT)
        this->unk3A8 = 5;

        if(damageEffect == 14 || damageEffect == 15) {

            if (damageEffect == 15) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DORA_S);
                this->unk3A0 = 1;
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DORA_L);
                this->unk3A0 = 2;
            }

            func_800BC848(&this->actor, globalCtx, 5, 10);
            func_80B60CC0(this);

            if ((func_80B60E54(time) == 1) && (this->unk3A6 == 0)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
                itemDrop = Item_DropCollectible(globalCtx, &this->actor.world.pos, ITEM00_RUPEE_BLUE);
                itemDrop->world.rot.y = (s16) this->actor.world.rot.y;
                itemRandRotation = Rand_Centered() * 90.0f * D_80B614E4;
                itemDrop->velocity.y = 5.0f;
                itemDrop->gravity = -1.0f;
                itemDrop->world.rot.y += (s32) itemRandRotation;
                this->unk3A6 = 0x28;
            }
        }
    }
    
    if (this->unk3A6 > 0) {
        this->unk3A6 -= 1;
    }

    if (this->unk3A8 > 0) {
        this->unk3A8 -= 1;
        return;
    }
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
}


//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Update.s")
void ObjDora_Update(Actor* thisx, GlobalContext *globalCtx) {
    ObjDora *this = THIS;

    this->actionFunc(this, globalCtx);
    func_80B60EE8(this, globalCtx);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Draw.s")
void ObjDora_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjDora* this = THIS;
    f32 unk390;

    static Vec3f position = {0.0f, -61.5f, 0.0f};

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->actionFunc == func_80B60D34) {
        unk390 = this->unk390;
        if ((globalCtx->state.frames % 2) != 0) {
            unk390 *= -1.0f;
        }

        Matrix_StatePush();
        Matrix_InsertXRotation_s(this->unk3A2, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);    
        gSPDisplayList(POLY_OPA_DISP++, &D_06004160);

        Matrix_InsertTranslation(position.x, position.y + unk390 , position.z + unk390, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk3A4 - this->unk3A2, MTXMODE_APPLY);
        Matrix_InsertTranslation(-position.x, -position.y, -position.z, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, &D_06003FD0);

        Matrix_StatePop();
    }else{
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, &D_06003FD0); // DLIST
        gSPDisplayList(POLY_OPA_DISP++, &D_06004160); // DLIST
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

