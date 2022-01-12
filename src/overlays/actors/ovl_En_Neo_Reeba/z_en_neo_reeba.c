/*
 * File: z_en_neo_reeba.c
 * Overlay: ovl_En_Neo_Reeba
 * Description: (New) Leevers
 */

#include "z_en_neo_reeba.h"

#define FLAGS 0x00000205

#define THIS ((EnNeoReeba*)thisx)

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Neo_Reeba_InitVars = {
    ACTOR_EN_NEO_REEBA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RB,
    sizeof(EnNeoReeba),
    (ActorFunc)EnNeoReeba_Init,
    (ActorFunc)EnNeoReeba_Destroy,
    (ActorFunc)EnNeoReeba_Update,
    (ActorFunc)EnNeoReeba_Draw,
};

// static DamageTable sDamageTable = {
static DamageTable D_80B7E500 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xE),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xC),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xD),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B7E520 = {
    { COLTYPE_HIT5, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x08, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 18, 30, 0, { 0, 0, 0 } },
};

#endif

extern DamageTable D_80B7E500;
extern ColliderCylinderInit D_80B7E520;

extern AnimationHeader D_060001E4;
extern SkeletonHeader D_06001EE8;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Init.s")
void func_80B7CA34(EnNeoReeba*); /* extern */

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06001EE8, &D_060001E4, this->jointTable, this->morphTable, 18);
    if (!(this->actor.params & 0x8000)) {
        Actor_SetScale(&this->actor, 0.04f);
        this->actor.colChkInfo.mass = 0x5A;
        this->actor.colChkInfo.health = 1;
    } else {
        Actor_SetScale(&this->actor, 0.05f);
        this->actor.colChkInfo.mass = 0xB4;
        this->actor.colChkInfo.health = 3;
    }

    this->actor.colChkInfo.damageTable = &D_80B7E500;
    this->actor.targetMode = 2;
    this->actor.hintId = 0x47;
    this->actor.gravity = -0.5f;
    this->unk_2B0 = gZeroVec3f;
    this->unk_2BC = gZeroVec3f;
    this->unk_308 = 0;
    this->unk_30C = 0;
    this->unk_30E = 0;
    this->unk_30A = 0;
    this->unk_2F8 = 0.0f;
    this->unk_2FC = 0.0f;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B7E520);
    func_80B7CA34(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Destroy.s")
void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CA34.s")
void func_80B7CA70(EnNeoReeba*, GlobalContext*); /* extern */

void func_80B7CA34(EnNeoReeba* this) {
    this->actor.flags &= -2;
    this->actor.draw = NULL;
    this->unk_30A = 0xA;
    this->actionFunc = func_80B7CA70;
    this->actor.shape.yOffset = -2000.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CA70.s")
void func_80B7CE34(EnNeoReeba*); /* extern */

void func_80B7CA70(EnNeoReeba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    if ((Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos) < 200.0f) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && (fabsf(this->actor.playerHeightRel) < 100.0f)) {
        func_80B7CE34(this);
    }
    if (this->unk_30A == 0) {
        this->actor.world.pos = this->actor.home.pos;
        this->unk_30A = -1;
    } else {
        this->unk_30A--;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CB3C.s")
void func_80B7CB88(EnNeoReeba*, GlobalContext*); /* extern */
void func_80B7CFFC(EnNeoReeba*, GlobalContext*);

void func_80B7CB3C(EnNeoReeba* this) {
    this->actor.shape.yOffset = 0.0f;
    if (this->actionFunc == func_80B7CFFC) {
        this->unk_30A = 0x14;
    } else {
        this->unk_30A = 0xA;
    }
    this->actionFunc = func_80B7CB88;
    this->skelAnime.playSpeed = 1.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CB88.s")
void func_80B7CCE0(EnNeoReeba*); /* extern */
void func_80B7CFA0(EnNeoReeba*); /* extern */
void func_80B7D130(EnNeoReeba*); /* extern */

void func_80B7CB88(EnNeoReeba* this, GlobalContext* globalCtx) {
    Player* player;
    f32 temp_f0;
    f32 temp_f2;

    player = GET_PLAYER(globalCtx);
    temp_f0 = Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos);
    if ((temp_f0 > 200.0f) || (fabsf(this->actor.playerHeightRel) > 100.0f)) {
        func_80B7CCE0(this);
    } else {
        if (this->unk_30A == 0) {
            if ((temp_f0 < 140.0f) && (fabsf(this->actor.playerHeightRel) < 100.0f)) {
                this->unk_2B0 = player->actor.world.pos;
                this->unk_2B0.x += 10.0f * player->actor.speedXZ * Math_SinS(player->actor.world.rot.y);
                this->unk_2B0.z += 10.0f * player->actor.speedXZ * Math_CosS(player->actor.world.rot.y);
                func_80B7CFA0(this);
            } else {
                func_80B7D130(this);
            }
        }
    }
    if (this->unk_30A != 0) {
        this->unk_30A--;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CCE0.s")
void func_80B7CD28(EnNeoReeba*, GlobalContext*); /* extern */

void func_80B7CCE0(EnNeoReeba* this) {
    this->unk_2F8 = 0.0f;
    this->skelAnime.playSpeed = 2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
    this->actionFunc = func_80B7CD28;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CD28.s")
void func_80B7CD28(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (Math_SmoothStepToF(&this->actor.shape.yOffset, -2000.0f, 0.5f, this->unk_2F8, 10.0f) == 0.0f) {
        func_80B7CA34(this);
    } else if ((globalCtx->gameplayFrames % 4) == 0) {
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1, 8.0f, 500, 10,
                      1);
    }
    if (this->unk_2F8 < 300.0f) {
        this->unk_2F8 += 20.0f;
    }
    Math_ApproachF(&this->actor.shape.shadowScale, 0.0f, 1.0f, 1.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CE34.s")
void func_80B7CE94(EnNeoReeba*, GlobalContext*); /* extern */

void func_80B7CE34(EnNeoReeba* this) {
    this->actor.draw = EnNeoReeba_Draw;
    this->unk_2F8 = 300.0f;
    this->skelAnime.playSpeed = 2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_APPEAR);
    this->actor.flags |= 1;
    this->actionFunc = func_80B7CE94;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CE94.s")
void func_80B7CB3C(EnNeoReeba*); /* extern */

void func_80B7CE94(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 0.5f, this->unk_2F8, 10.0f) == 0.0f) {
        func_80B7CB3C(this);
    } else if ((globalCtx->gameplayFrames & 3) == 0) {
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1, 8.0f, 500, 10,
                      1);
    }
    if (this->unk_2F8 > 20.0f) {
        this->unk_2F8 = this->unk_2F8 - 10.0f;
    }
    Math_ApproachF(&this->actor.shape.shadowScale, 12.0f, 1.0f, 1.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CFA0.s")
void func_80B7CFA0(EnNeoReeba* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_MOVE);
    this->unk_30C = 0xA;
    this->unk_30A = 0x3C;
    this->actionFunc = func_80B7CFFC;
    this->skelAnime.playSpeed = 2.0f;
    this->actor.speedXZ = 14.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CFFC.s")
void func_80B7CFFC(EnNeoReeba* this, GlobalContext* globalCtx) {
    f32 sp3C = Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->unk_2B0, this->actor.speedXZ);

    Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1, 4.0f, (s16)0xFA,
                  (s16)0xA, (u8)1);
    if (sp3C < 2.0f) {
        func_80B7CB3C(this);
    } else if (sp3C < 40.0f && this->actor.speedXZ > 3.0f) {
        this->actor.speedXZ -= 2.0f;
    }
    if (this->unk_30C == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_MOVE);
        this->unk_30C = 0xA;
    } else {
        this->unk_30C--;
    }
    if (this->unk_30A == 0) {
        func_80B7CB3C(this);
    } else {
        this->unk_30A--;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D130.s")
void func_80B7D150(EnNeoReeba*, GlobalContext*); /* extern */

void func_80B7D130(EnNeoReeba* this) {
    this->actionFunc = func_80B7D150;
    this->actor.speedXZ = 6.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D150.s")
void func_80B7D150(EnNeoReeba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp_f0;
    s32 pad;

    temp_f0 = Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->actor.home.pos, this->actor.speedXZ);
    if (temp_f0 < 2.0f) {
        func_80B7CB3C(this);
    } else if (temp_f0 < 40.0f && this->actor.speedXZ > 3.0f) {
        this->actor.speedXZ -= 1.0f;
    }
    if ((Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos) > 200.0f) ||
        (fabsf(this->actor.playerHeightRel) > 100.0f)) {
        func_80B7CCE0(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D254.s")
void func_80B7D2E4(EnNeoReeba*, GlobalContext*); /* extern */

void func_80B7D254(EnNeoReeba* this) {
    this->unk_30A = 0x3C;
    this->unk_2B0 = this->actor.world.pos;
    this->unk_2B0.x -= 20.0f * Math_SinS(this->actor.yawTowardsPlayer);
    this->unk_2B0.z -= 20.0f * Math_CosS(this->actor.yawTowardsPlayer);
    this->actionFunc = func_80B7D2E4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D2E4.s")
void func_80B7D2E4(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->unk_2B0, this->actor.speedXZ) < 2.0f) {
        func_80B7CB3C(this);
    }
    if (this->unk_30A == 0) {
        func_80B7CB3C(this);
    } else {
        this->unk_30A--;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D360.s")
void func_80B7D398(EnNeoReeba*, GlobalContext*);
void func_80B7D360(EnNeoReeba* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80B7D398;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D398.s")
void func_80B7D398(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (this->unk_30E > 0) {
        this->unk_30E--;
    } else {
        this->unk_300 = 0.0f;
        this->unk_304 = 0.0f;
    }
    if (this->actor.colorFilterTimer == 0) {
        this->unk_30E = 0;
        func_80B7CB3C(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D3EC.s")
void func_80B7D47C(EnNeoReeba*, GlobalContext*);
void func_80B7D3EC(EnNeoReeba* this) {
    this->unk_310 = 0xB;
    this->unk_304 = 0.5f;
    this->unk_300 = 1.0f;
    if (this->actor.params & 0x8000) {
        this->unk_304 *= 1.5f;
    }
    if (this->actor.colChkInfo.health != 0) {
        this->unk_30E = 0x50;
    } else {
        this->unk_30E = 0xC;
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80B7D47C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D47C.s")
void func_80B7D4FC(EnNeoReeba*);
void func_80B7D6D0(EnNeoReeba*);                 /* extern */
void func_80B7E0BC(EnNeoReeba*, GlobalContext*); /* extern */

void func_80B7D47C(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (this->unk_30E == 0) {
        this->unk_30E = 0;
        this->unk_304 = 0.0f;
        this->unk_300 = 0.0f;
        if (this->actor.colChkInfo.health != 0) {
            func_80B7D4FC(this);
        } else {
            func_80B7D6D0(this);
        }
    } else if (this->unk_30E == 1) {
        this->unk_30E--;
        func_80B7E0BC(this, globalCtx);
    } else {
        this->unk_30E--;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D4FC.s")
void func_80B7D5A4(EnNeoReeba*, GlobalContext*);

void func_80B7D4FC(EnNeoReeba* this) {
    this->unk_30A = 0xA;
    this->skelAnime.playSpeed = 1.0f;
    this->unk_2BC.x = Math_SinS(this->actor.yawTowardsPlayer) * -12.0f;
    this->unk_2BC.z = Math_CosS(this->actor.yawTowardsPlayer) * -12.0f;
    this->unk_2FC = 4551.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 25);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_DAMAGE);
    this->actionFunc = func_80B7D5A4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D5A4.s")
extern f32 D_80B7E54C[];
extern f32 D_80B7E578[];

void func_80B7D5A4(EnNeoReeba* this, GlobalContext* globalCtx) {
    f32 temp_f0;

    if (this->unk_30A == 0) {
        this->unk_2FC = 0.0f;
        func_80B7CB3C(this);
    } else {
        this->unk_308 += -0x1F40;
        Math_SmoothStepToF(&this->unk_2FC, 0.0f, 0.5f, 182.0f, 18.0f);
        this->actor.scale.x = this->actor.scale.z = D_80B7E54C[this->unk_30A];
        this->actor.scale.y = D_80B7E578[this->unk_30A];
        if (this->actor.params & 0x8000) {
            this->actor.scale.x *= 1.5f;
            this->actor.scale.y *= 1.5f;
            this->actor.scale.z *= 1.5f;
        }
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1, 4.0f,
                      250, 10, 1);
        this->unk_30A += -1;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D9B8.s")
void func_80B7D360(EnNeoReeba*); /* extern */
void func_80B7D3EC(EnNeoReeba*); /* extern */
void func_80B7D5A4(EnNeoReeba*, GlobalContext*);
void func_80B7D788(EnNeoReeba*, GlobalContext*);
void func_80B7D47C(EnNeoReeba*, GlobalContext*);
void func_80B7D398(EnNeoReeba*, GlobalContext*);

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DC80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E0BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E260.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Update.s")
void func_80B7D9B8(EnNeoReeba*, GlobalContext*); /* extern */
void func_80B7DC80(EnNeoReeba*, GlobalContext*); /* extern */
void func_80B7E260(EnNeoReeba*, GlobalContext*); /* extern */
void func_80B7D398(EnNeoReeba*, GlobalContext*);
void func_80B7D47C(EnNeoReeba*, GlobalContext*);

void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    if ((this->actor.params & 0x8000)) {
        this->collider.dim.radius = 0x1B;
        this->collider.dim.height = 0x2D;
    }
    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != func_80B7CA70) && (this->actionFunc != func_80B7D398) &&
        (this->actionFunc != func_80B7D47C)) {
        SkelAnime_Update(&this->skelAnime);
    }
    func_80B7D9B8(this, globalCtx);
    func_80B7DC80(this, globalCtx);
    func_80B7E260(this, globalCtx);
}
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Draw.s")
