/*
 * File: z_en_raf.c
 * Overlay: ovl_En_Raf
 * Description: Carnivorous Lilypad
 */

#include "z_en_raf.h"

#define FLAGS (ACTOR_FLAG_8000000)

#define THIS ((EnRaf*)thisx)

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A171D8(EnRaf* this, GlobalContext* globalCtx);
void func_80A17464(EnRaf* this, GlobalContext* globalCtx);
void func_80A175E4(EnRaf* this, GlobalContext* globalCtx);
void func_80A178A0(EnRaf* this, GlobalContext* globalCtx);
void func_80A17C6C(EnRaf* this, GlobalContext* globalCtx);
void func_80A17D54(EnRaf* this, GlobalContext* globalCtx);
void func_80A17E1C(EnRaf* this, GlobalContext* globalCtx);
void func_80A180B4(EnRaf* this, GlobalContext* globalCtx);
void func_80A1712C(EnRaf* this);
void func_80A18080(EnRaf* this);
void func_80A17414(EnRaf* this);
void func_80A17530(EnRaf* this);
void func_80A18DA0(EnRaf* this, GlobalContext* globalCtx);
void func_80A17848(EnRaf* this, GlobalContext* globalCtx);
void func_80A179C8(EnRaf* this, GlobalContext* globalCtx);
void func_80A18A90(EnRaf* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5);

#if 0
const ActorInit En_Raf_InitVars = {
    ACTOR_EN_RAF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A18EE0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 50, 10, -10, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A1939C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

static AnimationHeader* D_80A193C8[] = {
    &D_06000A64, &D_06000C7C, &D_06000B30, &D_06000A64, &D_060003FC, &D_060007A8
};
static u8 D_80A193E0[] = {
    ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE
};

#endif

extern ColliderCylinderInit D_80A18EE0;
extern DamageTable D_80A1939C;
extern Vec3f D_80A193BC;
extern AnimationHeader* D_80A193C8[];
extern u8 D_80A193E0[];
extern Vec3f D_80A1940C;
extern Vec3f D_80A193E8;
extern Vec3f D_80A193F4;
extern Vec3f D_80A19400;

extern AnimationHeader D_06000A64;
extern FlexSkeletonHeader D_06003428;
extern CollisionHeader D_06000108;
extern AnimationHeader D_06000C7C;
extern AnimationHeader D_06000B30;
extern AnimationHeader D_060003FC;
extern AnimationHeader D_060007A8;
extern UNK_TYPE D_060024E0;
extern UNK_TYPE D_060032F8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A16D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A16D6C.s")

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;
    Vec3f sp60 = D_80A193BC;
    s32 i;
    s32 j;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&D_06000108, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_80A18EE0);
    this->dyna.actor.targetMode = 3;
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06003428, &D_06000A64, this->jointTable, this->morphTable, 12);
    for (i = 0; i < 12; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &sp60);
        Math_Vec3f_Copy(&this->unk_234[i], &sp60);
    }

    this->dyna.actor.colChkInfo.damageTable = &D_80A1939C;
    this->dyna.actor.colChkInfo.health = BREG(1) + 2;
    this->unk_3BE = EN_RAF_GET_F(&this->dyna.actor);
    this->unk_3BA = EN_RAF_GET_1F(&this->dyna.actor);
    this->unk_3C0 = EN_RAF_GET_7F(&this->dyna.actor);
    if (this->unk_3C0 == 0x7F) {
        this->unk_3C0 = -1;
    }

    if (this->unk_3BA == 0x1F) {
        this->unk_3BA = -1;
    } else {
        this->unk_3BA = 0x1E;
    }

    if (((this->unk_3C0 >= 0) || (this->unk_3BE == 1) || (gSaveContext.save.weekEventReg[12] & 1)) &&
        ((Flags_GetSwitch(globalCtx, this->unk_3C0)) || (this->unk_3BE == 1))) {
        for (j = 2; j < 11; j++) {
            Math_Vec3f_Copy(&this->unk_234[j], &gZeroVec3f);
            Math_Vec3f_Copy(&this->unk_2C4[j], &gZeroVec3f);
        }

        func_80A18080(this);
    } else {
        this->unk_3B0 = Rand_ZeroFloat(1.0f) * 20000.0f;
        Actor_SetScale(&this->dyna.actor, 0.01f);
        func_80A1712C(this);
    }
}

void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A17060(EnRaf* this, s32 index) {
    f32 startFrame = 0.0f;
    f32 playSpeed = 1.0f;

    this->unk_3A0 = Animation_GetLastFrame(D_80A193C8[index]);
    if (index == 0) {
        startFrame = this->unk_3A0;
    } else if (index == 1) {
        playSpeed = 2.0f;
    }

    Animation_Change(&this->skelAnime, D_80A193C8[index], playSpeed, startFrame, this->unk_3A0, D_80A193E0[index],
                     -4.0f);
}

void func_80A1712C(EnRaf* this) {
    Vec3f sp3C = D_80A193E8;
    s32 i;

    func_80A17060(this, 0);
    for (i = 2; i < 11; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &sp3C);
    }

    this->unk_3C2 = 3;
    this->unk_3C6 = 0;
    this->actionFunc = func_80A171D8;
}

void func_80A171D8(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Actor* explosive;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;

    if (this->unk_3B4 == 0) {
        if ((player->transformation != PLAYER_FORM_DEKU) &&
            (this->dyna.actor.xzDistToPlayer < (BREG(48) + 80.0f) && (player->invincibilityTimer == 0) &&
             DynaPolyActor_IsInRidingMovingState(&this->dyna) && !(player->stateFlags1 & 0x8000000) &&
             globalCtx->grabPlayer(globalCtx, player))) {
            player->actor.parent = &this->dyna.actor;
            this->unk_39C = 0;

            if (player->transformation == PLAYER_FORM_GORON) {
                this->unk_39C = 2;
            } else {
                player->unk_AE8 = 50;
            }

            this->unk_3BC = player->actor.world.rot.y;
            func_80A17414(this);
            return;
        }

        if ((globalCtx->gameplayFrames % 2) == 0) {
            return;
        }

        explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;
        while (explosive != NULL) {
            if ((EnRaf*)explosive == this) {
                explosive = explosive->next;
                continue;
            }

            xDiff = explosive->world.pos.x - this->dyna.actor.world.pos.x;
            yDiff = explosive->world.pos.y - this->dyna.actor.world.pos.y;
            zDiff = explosive->world.pos.z - this->dyna.actor.world.pos.z;
            if ((fabsf(xDiff) < 80.0f) && (fabsf(yDiff) < 30.0f) && (fabsf(zDiff) < 80.0f) &&
                (explosive->update != NULL) && (explosive->velocity.y != 0.0f)) {
                Actor_MarkForDeath(explosive);
                this->unk_39C = 1;
                this->collider.dim.radius = 30;
                this->collider.dim.height = 90;
                this->collider.dim.yShift = -10;
                func_80A17414(this);
                return;
            }

            explosive = explosive->next;
        }
    }
}

void func_80A17414(EnRaf* this) {
    func_80A17060(this, 1);
    this->unk_3C2 = 1;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_DRINK);
    this->unk_3C6 = 1;
    this->actionFunc = func_80A17464;
}

void func_80A17464(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if ((this->unk_39C != 1) && (player->stateFlags2 & 0x80) && (&this->dyna.actor == player->actor.parent)) {
        Math_ApproachF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.y, this->dyna.actor.world.pos.y, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.3f, 10.0f);
    }

    if (this->unk_3A0 <= curFrame) {
        func_80A17530(this);
    }
}

void func_80A17530(EnRaf* this) {
    s32 i;

    func_80A17060(this, 2);
    this->unk_3C4 = 0;
    for (i = 0; i < 12; i++) {
        this->unk_354[i].x = Rand_S16Offset(8, 8) << 8;
        this->unk_354[i].y = Rand_S16Offset(8, 8) << 8;
        this->unk_354[i].z = Rand_S16Offset(8, 8) << 8;
    }

    this->unk_3C2 = 2;
    this->unk_3C6 = 2;
    this->actionFunc = func_80A175E4;
}

void func_80A175E4(EnRaf* this, GlobalContext* globalCtx) {
    f32 temp;
    f32 curFrame;
    Player* player = GET_PLAYER(globalCtx);

    curFrame = this->skelAnime.curFrame;
    temp = (BREG(51) / 100.0f) + 0.2f;
    Math_ApproachF(&this->unk_3A4, temp, 0.2f, 0.03f);

    if ((player->stateFlags2 & 0x80) && (this->unk_39C != 1) && (&this->dyna.actor == player->actor.parent)) {
        Math_ApproachF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.y, this->dyna.actor.world.pos.y, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.3f, 10.0f);
    }

    if (this->unk_3A0 <= curFrame) {
        if (BREG(52) == 0) {
            this->unk_3C4++;
        }

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_EAT);
        switch (this->unk_39C) {
            case 0:
                globalCtx->damagePlayer(globalCtx, -2);
                func_800B8E58((Player*)this, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
                CollisionCheck_GreenBlood(globalCtx, NULL, &player->actor.world.pos);
                if (((BREG(53) + 5) < this->unk_3C4) || !(player->stateFlags2 & 0x80)) {
                    player->actor.freezeTimer = 10;
                    func_80A17848(this, globalCtx);
                    return;
                }
                break;

            case 1:
                Actor_ApplyDamage(&this->dyna.actor);
                if ((BREG(54) + 4) < this->unk_3C4) {
                    func_80A179C8(this, globalCtx);
                    return;
                }
                break;

            case 2:
                if ((BREG(54) + 4) < this->unk_3C4) {
                    player->actor.parent = NULL;
                    player->unk_AE8 = 1000;
                    func_80A179C8(this, globalCtx);
                }
                break;
        }
    }
}

void func_80A17848(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80A17060(this, 3);
    player->actor.freezeTimer = 10;
    this->unk_3C2 = 3;
    this->unk_3C6 = 3;
    this->actionFunc = func_80A178A0;
}

void func_80A178A0(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        player->actor.freezeTimer = 0;
        player->actor.parent = NULL;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_THROW);
        func_800B8D50(globalCtx, &this->dyna.actor, BREG(55) + 3.0f, this->unk_3BC + 0x8000, BREG(56) + 10.0f, 0);
    } else if (curFrame < 10.0f) {
        player->actor.freezeTimer = 10;
    }

    if (this->unk_3A0 <= curFrame) {
        this->unk_3C2 = 3;
        this->unk_3C6 = 0;
        this->unk_3B4 = 0x14;
        this->actionFunc = func_80A171D8;
    }
}

void func_80A179C8(EnRaf* this, GlobalContext* globalCtx) {
    Vec3f spAC = D_80A193F4;
    Vec3f spA0 = D_80A19400;
    Vec3f sp94;
    s32 i;
    s32 pad;

    this->unk_3C6 = 4;
    Math_Vec3f_Copy(&sp94, &this->dyna.actor.world.pos);
    sp94.y += 10.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, sp94.x, sp94.y, sp94.z, 0, 0, 0,
                CLEAR_TAG_SMALL_EXPLOSION);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_IT_BOMB_EXPLOSION);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_DEAD);
    if (this->unk_3C0 >= 0) {
        Flags_SetSwitch(globalCtx, this->unk_3C0);
    }

    this->unk_3C2 = 0;
    for (i = 0; i < BREG(57) + 30; i++) {
        spA0.x = (Rand_ZeroOne() - 0.5f) * 0.5f;
        spA0.y = -0.3f;
        spA0.z = (Rand_ZeroOne() - 0.5f) * 0.5f;
        spAC.x = Rand_ZeroOne() - 0.5f;
        spAC.y = Rand_ZeroOne() * 10.0f;
        spAC.z = Rand_ZeroOne() - 0.5f;
        func_80A18A90(this, &this->dyna.actor.world.pos, &spAC, &spA0, (Rand_ZeroFloat(1.0f) / 500.0f) + 0.002f, 90);
    }

    for (i = 2; i < 11; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &gZeroVec3f);
    }

    this->unk_3B4 = 5;
    if (this->unk_39C == 1) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 5);
        this->dyna.actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
    }

    this->actionFunc = func_80A17C6C;
}

void func_80A17C6C(EnRaf* this, GlobalContext* globalCtx) {
    if (this->unk_3B4 == 0) {
        this->collider.dim.radius = 50;
        this->collider.dim.height = 10;
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 6);
        this->dyna.actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        func_80A18080(this);
    } else if (this->unk_39C == 1) {
        this->collider.dim.radius = 80;
        this->collider.dim.height = 50;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A17E1C.s")

void func_80A18080(EnRaf* this) {
    if (this->unk_3C6 == 4) {
        this->unk_3B4 = 0x5A;
    } else {
        this->unk_3C6 = 7;
    }

    this->actionFunc = func_80A180B4;
}

void func_80A180B4(EnRaf* this, GlobalContext* globalCtx) {
    Vec3f sp3C = D_80A1940C;
    s32 i;

    if (this->unk_3B4 == 0) {
        this->unk_3C6 = 7;
    }

    if (this->unk_3BA >= 0) {
        if (this->unk_3BA != 0) {
            this->unk_3BA--;
        }

        if (this->unk_3BA == 0) {
            func_80A17060(this, 3);
            for (i = 2; i < 11; i++) {
                Math_Vec3f_Copy(&this->unk_2C4[i], &sp3C);
            }

            this->unk_3C2 = 3;
            this->unk_3C6 = 0;
            this->unk_3BA = EN_RAF_GET_1F(&this->dyna.actor);
            this->unk_3BA += 0x1E;
            this->actionFunc = func_80A171D8;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/EnRaf_Update.s")

void func_80A1859C(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A1859C.s")

void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, NULL, func_80A1859C, &this->dyna.actor);
    if (this->unk_3C6 == 4) {
        func_80A18DA0(this, globalCtx);
    }
}

void func_80A18A90(EnRaf* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5) {
    EnRafUnkStruct* ptr;
    s16 i;

    ptr = this->unk_41C;
    for (i = 0; i < 31; i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 1;
            ptr->unk_04 = *arg1;
            ptr->unk_10 = *arg2;
            ptr->unk_1C = *arg3;
            ptr->unk_30 = arg4;
            ptr->unk_34 = arg5;
            ptr->unk_28.x = randPlusMinusPoint5Scaled(30000.0f);
            ptr->unk_28.y = randPlusMinusPoint5Scaled(30000.0f);
            ptr->unk_28.z = randPlusMinusPoint5Scaled(30000.0f);
            return;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Raf/func_80A18DA0.s")
