/*
 * File: z_en_ruppecrow.c
 * Overlay: ovl_En_Ruppecrow
 * Description: Guay Circling Clock Town
 */

#include "z_en_ruppecrow.h"

#define FLAGS 0x00004030

#define THIS ((EnRuppecrow*)thisx)

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80BE3178(EnRuppecrow*, GlobalContext*);
s32 func_80BE2260(EnRuppecrow*, GlobalContext*);
void func_80BE2808(EnRuppecrow*);
void func_80BE30F4(EnRuppecrow*, GlobalContext*);
void func_80BE2F6C(EnRuppecrow*);
void func_80BE35A4(EnRuppecrow*, GlobalContext*);
void func_80BE2728(EnRuppecrow*, GlobalContext*);
void func_80BE2B80(EnRuppecrow*, GlobalContext*);
s32 func_80BE2D4C(GlobalContext*);
void func_80BE32DC(EnRuppecrow*, GlobalContext*);
s32 func_80BE2330(EnRuppecrow*, Path*, s32);
s32 func_80BE24CC(EnRuppecrow*, Path*, s32);
f32 func_80BE2668(Path*, s32, PosRot*, Vec3s*);
s32 func_80BE2794(GlobalContext*);
void func_80BE2874(EnRuppecrow*, GlobalContext*);
void func_80BE3354(EnRuppecrow*, GlobalContext*);
void func_80BE2E18(EnRuppecrow*, GlobalContext*);
void func_80BE348C(EnRuppecrow*, GlobalContext*);

extern AnimationHeader D_060000F0;
extern FlexSkeletonHeader D_060010C0;

const ActorInit En_Ruppecrow_InitVars = {
    ACTOR_EN_RUPPECROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnRuppecrow),
    (ActorFunc)EnRuppecrow_Init,
    (ActorFunc)EnRuppecrow_Destroy,
    (ActorFunc)EnRuppecrow_Update,
    (ActorFunc)EnRuppecrow_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80BE39B0[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80BE39D4 = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    D_80BE39B0, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80BE39E4 = { 1, 15, 30, 30 };

// static DamageTable sDamageTable = {
static DamageTable D_80BE39EC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BE3A0C[] = {
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

s32 func_80BE2260(EnRuppecrow* this, GlobalContext* globalCtx) {
    UNK_TYPE pad;

    this->collider.elements->dim.worldSphere.center.x = (s16)this->actor.world.pos.x;
    this->collider.elements->dim.worldSphere.center.y =
        (s16)(D_80BE39D4.elements->dim.modelSphere.center.y + this->actor.world.pos.y);
    this->collider.elements->dim.worldSphere.center.z = (s16)this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f, 25.0f, 50.0f, 0x07);

    return true;
}

s32 func_80BE2330(EnRuppecrow* this, Path* path, s32 arg2) {
    Vec3s* points3s;
    s32 pathCount;
    s32 idx;
    s32 result;
    f32 y;
    f32 x;
    Vec3f vec;
    Vec3f points3f;

    idx = arg2;
    points3s = Lib_SegmentedToVirtual(path->points);
    pathCount = path->count;
    result = false;

    Math_Vec3s_ToVec3f(&points3f, &points3s[idx]);

    if (idx == 0) {
        y = points3s[1].x - points3s[0].x;
        x = points3s[1].z - points3s[0].z;
    } else {
        if (idx == (pathCount - 1)) {
            y = points3s[pathCount - 1].x - points3s[pathCount - 2].x;
            x = points3s[pathCount - 1].z - points3s[pathCount - 2].z;
        } else {
            y = points3s[idx + 1].x - points3s[idx - 1].x;
            x = points3s[idx + 1].z - points3s[idx - 1].z;
        }
    }

    func_8017B7F8(&points3f, (func_80086B30(y, x) * 10430.378f), &vec.z, &vec.y, &vec.x);
    if (((this->actor.world.pos.x * vec.z) + (vec.y * this->actor.world.pos.z) + vec.x) > 0.0f) {
        result = true;
    }

    return result;
}

s32 func_80BE24CC(EnRuppecrow* this, Path* path, s32 arg2) {
    Vec3s* points3s;
    s32 pathCount;
    s32 idx;
    s32 result;
    f32 y;
    f32 x;
    Vec3f vec;
    Vec3f points3f;

    idx = arg2;
    points3s = Lib_SegmentedToVirtual(path->points);
    pathCount = path->count;
    result = false;

    Math_Vec3s_ToVec3f(&points3f, &points3s[idx]);

    if (idx == 0) {
        y = points3s[0].x - points3s[1].x;
        x = points3s[0].z - points3s[1].z;
    } else {
        if (idx == (pathCount - 1)) {
            y = points3s[pathCount - 2].x - points3s[pathCount - 1].x;
            x = points3s[pathCount - 2].z - points3s[pathCount - 1].z;
        } else {
            y = points3s[idx - 1].x - points3s[idx + 1].x;
            x = points3s[idx - 1].z - points3s[idx + 1].z;
        }
    }
    func_8017B7F8(&points3f, (func_80086B30(y, x) * 10430.378f), &vec.z, &vec.y, &vec.x);
    if (((this->actor.world.pos.x * vec.z) + (vec.y * this->actor.world.pos.z) + vec.x) > 0.0f) {
        result = true;
    }
    return result;
}

f32 func_80BE2668(Path* path, s32 arg1, PosRot* world, Vec3s* arg3) {
    Vec3s* points;
    Vec3f sp20;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        sp20.x = (f32)points->x;
        sp20.y = (f32)points->y;
        sp20.z = (f32)points->z;
    }

    arg3->y = Math_Vec3f_Yaw(&world->pos, &sp20);
    arg3->x = Math_Vec3f_Pitch(&world->pos, &sp20);

    return sp20.y - world->pos.y;
}

void func_80BE2728(EnRuppecrow* this, GlobalContext* globalCtx) {
    if ((u8)this->unk_2C4 == 0xA) {
        this->unk_2C4 = 0x0;
        this->unk_2C8 = 0.0f;
        func_800BF7CC(globalCtx, &this->actor, this->limbPos, 0x4, 0x2, 0.2f, 0.2f);
    }
}

s32 func_80BE2794(GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            return false;
        case PLAYER_FORM_GORON:
            return true;
        case PLAYER_FORM_ZORA:
            return false;
        case PLAYER_FORM_HUMAN:
            if (player->stateFlags1 & 0x800000) {
                return true;
            } else {
                return false;
            }
    }

    return false;
}

void func_80BE2808(EnRuppecrow* this) {
    EnItem00* item;
    s16 phi_s0;

    for (phi_s0 = 0; phi_s0 < 20; phi_s0++) {
        item = this->items[phi_s0];
        if (item != NULL && item->unk152 == 0) {
            Actor_MarkForDeath(&item->actor);
        }
    }
}

void func_80BE2874(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player;
    f32 phi_f0;
    EnItem00* item;
    s16 sp3A;

    player = GET_PLAYER(globalCtx);
    sp3A = this->unk_2BC;

    if (!(player->stateFlags3 & 0x1000)) {
        phi_f0 = this->unk_2BC & 1 ? 10.0f : -10.0f;
    } else {
        phi_f0 = 0.0f;
    }

    if (func_80BE2794(globalCtx) && (this->unk_2BC % 5) == 4) {
        if (this->unk_2BC == 19) {
            item = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + phi_f0,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, 0x2);
            this->items[sp3A] = item;
            this->items[sp3A]->actor.gravity = -5.0f;
            this->items[sp3A]->actor.velocity.y = 0.0f;
            Audio_PlayActorSound2(&this->actor, 0x28D9);
            item = this->items[sp3A];
            item->unk152 = 0x3C;
            this->items[sp3A]->actor.flags |= 0x10;
        } else {
            item = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + phi_f0,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, 0x1);
            this->items[sp3A] = item;
            this->items[sp3A]->actor.gravity = -5.0f;
            this->items[sp3A]->actor.velocity.y = 0.0f;
            Audio_PlayActorSound2(&this->actor, 0x28D9);
            item = this->items[sp3A];
            item->unk152 = 0x3C;
            this->items[sp3A]->actor.flags |= 0x10;
        }
    } else if (this->unk_2BC == 19) {
        item = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + phi_f0,
                                      this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, 0x2);
        this->items[sp3A] = item;
        this->items[sp3A]->actor.gravity = -5.0f;
        this->items[sp3A]->actor.velocity.y = 0.0f;
        Audio_PlayActorSound2(&this->actor, 0x28D9);
        item = this->items[sp3A];
        item->unk152 = 0x3C;
        this->items[sp3A]->actor.flags |= 0x10;
    } else {
        item = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + phi_f0,
                                      this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, 0x0);
        this->items[sp3A] = item;
        this->items[sp3A]->actor.gravity = -5.0f;
        this->items[sp3A]->actor.velocity.y = 0.0f;
        Audio_PlayActorSound2(&this->actor, 0x28D9);
        item = this->items[sp3A];
        item->unk152 = 0x3C;
        this->items[sp3A]->actor.flags |= 0x10;
    }

    this->unk_2BC++;
}

void func_80BE2B80(EnRuppecrow* this, GlobalContext* globalCtx) {
    Vec3s sp30;

    func_80BE2668(this->path, this->unk_250, &this->actor.world, &sp30);
    if (this->actor.bgCheckFlags & 8) {
        sp30.y = this->actor.wallYaw;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 0x4, 0x3E8, 0x1);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_SmoothStepToS(&this->actor.world.rot.x, -sp30.x, 0x4, 0x3E8, 0x1);

    if (this->unk_2B4 & 0x1) {
        if (func_80BE24CC(this, this->path, this->unk_250)) {
            this->unk_250 = (this->unk_250 <= 0) ? (this->path->count - 0x1) : (this->unk_250 - 0x1);

            if ((this->actionFunc == &func_80BE3354) && (!func_80BE2794(globalCtx) || (this->unk_250 % -2) == 0)) {
                func_80BE2874(this, globalCtx);
            }
        }
    } else if (func_80BE2330(this, this->path, this->unk_250)) {
        this->unk_250 = (this->unk_250 >= this->path->count - 0x1) ? 0x0 : this->unk_250 + 0x1;

        if (this->actionFunc == &func_80BE3354 && (!func_80BE2794(globalCtx) || (this->unk_250 % -2) == 0)) {
            func_80BE2874(this, globalCtx);
        }
    }
}

s32 func_80BE2D4C(GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    if (globalCtx->msgCtx.unk1202A == 3) {
        switch (player->transformation) {
            case PLAYER_FORM_DEKU:
                if (globalCtx->msgCtx.unk1202E == 0) {
                    return true;
                }
                break;
            case PLAYER_FORM_GORON:
                if (globalCtx->msgCtx.unk1202E == 1) {
                    return true;
                }
                break;
            case PLAYER_FORM_ZORA:
                if (globalCtx->msgCtx.unk1202E == 2) {
                    return true;
                }
                break;
            case PLAYER_FORM_HUMAN:
                if (globalCtx->msgCtx.unk1202E == 0) {
                    return true;
                } else if (globalCtx->msgCtx.unk1202E == 1) {
                    return true;
                } else if (globalCtx->msgCtx.unk1202E == 2) {
                    return true;
                }
                break;
        }
    }

    return false;
}

void func_80BE2E18(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            this->unk_2B8 = 7.0f;
            break;
        case PLAYER_FORM_GORON:
            this->unk_2B8 = (player->stateFlags3 & 0x1000) ? 19.0f : 7.0f;
            break;
        case PLAYER_FORM_ZORA:
            this->unk_2B8 = 7.0f;
            break;
        case PLAYER_FORM_HUMAN:
            this->unk_2B8 = (player->stateFlags1 & 0x800000) ? 16.0f : 7.0f;
            break;
    }

    this->skelAnime.playSpeed = this->unk_2B8 / 6.0f;
    if (this->actor.xzDistToPlayer > 800.0f) {
        this->unk_2B8 *= 0.5f;
    } else if (this->actor.xzDistToPlayer > 500.0f) {
        this->unk_2B8 *= 0.8f;
    } else if (this->actor.xzDistToPlayer < 150.0f) {
        this->unk_2B8 *= 1.2f;
    }
}

void func_80BE2F6C(EnRuppecrow* this) {
    f32 scale;

    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.velocity.y = 0.0f;
    Animation_Change(&this->skelAnime, &D_060000F0, 0.4f, 0.0f, 0.0f, 0x1, -3.0f);

    this->actor.shape.yOffset = 0.0f;
    this->actor.targetArrowOffset = 0.0f;
    this->actor.bgCheckFlags &= 0xFFFE;

    scale = this->actor.scale.x * 100.0f;
    this->actor.world.pos.y += 20.0f * scale;

    Audio_PlayActorSound2(&this->actor, 0x38EBU);

    this->unk_2CC = 0.5f;
    if (this->actor.colChkInfo.damageEffect == 3) {
        this->unk_2C4 = 0xA;
        this->unk_2C8 = 1.0f;
        this->unk_2D0 = 0.75f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->unk_2C4 = 0x14;
        this->unk_2C8 = 5.0f;
    } else if (this->actor.colChkInfo.damageEffect == 2) {
        this->unk_2C4 = 0x0;
        this->unk_2C8 = 5.0f;
    }

    func_800BCB70(&this->actor, 0x4000, 0xFF, 0x0, 0x28);
    if (this->actor.flags & 0x8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->collider.base.acFlags &= 0xFFFE;
    this->actor.flags |= 0x10;
    this->actionFunc = func_80BE35A4;
}

void func_80BE30F4(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & 0x2) {
        this->collider.base.acFlags &= 0xFFFD;
        func_800BE258(&this->actor, this->collider.elements);
        if (this->actor.colChkInfo.damageEffect != 1) {
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= ~1;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            func_80BE2F6C(this);
        }
    }
}

void func_80BE3178(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    func_80BE2B80(this, globalCtx);
    if (this->actor.xzDistToPlayer < 1000.0f && func_80BE2D4C(globalCtx)) {
        if (Actor_IsActorFacingLink(&this->actor, 0x4000)) {
            this->unk_2B4 |= 0x1;
            if (this->unk_250 > 0) {
                this->unk_250--;
            } else {
                this->unk_250 = this->path->count - 1;
            }
        }

        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->actionFunc = func_80BE32DC;
    }

    if (((s32)player->stateFlags2 * 0x10) < 0) {
        Math_ApproachF(&this->actor.speedXZ, 0.0f, 0.1f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.1f, 0.1f);
    }

    Actor_SetVelocityAndMoveXYRotation(&this->actor);
    this->unk_2BE += 0x1000;
    this->actor.shape.yOffset = Math_SinS(this->unk_2BE) * 500.0f;
    if (globalCtx->state.frames % 43 == 0) {
        Audio_PlayActorSound2(&this->actor, 0x38B6U);
    }
}

void func_80BE32DC(EnRuppecrow* this, GlobalContext* globalCtx) {
    func_80BE2B80(this, globalCtx);

    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_80BE2E18(this, globalCtx);
        this->actionFunc = func_80BE3354;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }

    Actor_SetVelocityAndMoveXYRotation(&this->actor);
}

void func_80BE3354(EnRuppecrow* this, GlobalContext* globalCtx) {
    func_80BE2B80(this, globalCtx);
    if (this->unk_2BC >= 0x14) {
        this->unk_2B8 = 6.0f;
        this->actor.gravity = 0.0f;
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.2f, 0.5f);
        Math_ApproachF(&this->actor.velocity.y, 3.0f, 0.2f, 0.5f);
        this->actionFunc = func_80BE348C;
        this->skelAnime.playSpeed = 1.0f;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    } else {
        if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
            func_80BE2E18(this, globalCtx);
            Math_ApproachF(&this->actor.speedXZ, this->unk_2B8, 0.2f, 0.5f);
        }
        Actor_SetVelocityAndMoveXYRotation(&this->actor);
        this->unk_2BE += 0x1000;
        this->actor.shape.yOffset = Math_SinS(this->unk_2BE) * 500.0f;
        if ((globalCtx->state.frames % 43) == 0) {
            Audio_PlayActorSound2(&this->actor, 0x38B6U);
        }
    }
}

void func_80BE348C(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 0x8) {
        this->actor.world.rot.y *= -1;
    }
    Math_ApproachF(&this->actor.speedXZ, this->unk_2B8, 0.1f, 0.1f);
    Math_ApproachF(&this->actor.velocity.y, 3.0f, 0.2f, 0.5f);
    if (this->actor.world.pos.y > 1000.0f || this->actor.xzDistToPlayer > 2000.0f) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->unk_2BE += 0x800;
        this->actor.shape.yOffset = Math_SinS(this->unk_2BE) * 500.0f;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        if ((globalCtx->state.frames % 43) == 0) {
            Audio_PlayActorSound2(&this->actor, 0x38B6U);
        }
    }
}

void func_80BE35A4(EnRuppecrow* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);

    if ((u8)this->unk_2C4 != 0xA) {
        Math_StepToF(&this->unk_2C8, 0.0f, 0.05f);

        this->unk_2CC = (this->unk_2C8 + 1.0f) * 0.25f;
        if (this->unk_2CC > 0.5f) {
            this->unk_2CC = 0.5f;
        } else {
            this->unk_2CC = this->unk_2CC;
        }
    } else if (Math_StepToF(&this->unk_2D0, 0.5f, 0.0125f) == 0) {
        func_800B9010(&this->actor, 0x20B2U);
    }

    this->actor.colorFilterTimer = 0x28;
    if (!(this->actor.flags & 0x8000)) {
        if ((u8)this->unk_2C4 != 0xA) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }
        if (this->actor.bgCheckFlags & 1 || this->actor.floorHeight == -32000.0f) {
            func_80BE2728(this, globalCtx);
            func_800B3030(globalCtx, &this->actor.world.pos, &D_801D15B0, &D_801D15B0,
                          (s16)(this->actor.scale.x * 10000.0f), 0x0, 0x0);
            Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0xB, 0x3878U);
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }

    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx2) {
    EnRuppecrow* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    Actor_ProcessInitChain(&this->actor, D_80BE3A0C);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060010C0, &D_060000F0, this->joinTable, this->morphTable, 9);
    ActorShape_Init(&this->actor.shape, 2000.0f, func_800B3FC0, 20.0f);

    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_80BE39D4, &this->colliderElement);
    this->collider.elements->dim.worldSphere.radius = D_80BE39D4.elements->dim.modelSphere.radius;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80BE39EC, &D_80BE39E4);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags |= 0x2000000;

    this->path = func_8013D648(globalCtx, (s16)((s32)(this->actor.params & 0xFC00) >> 0xA), 0x3F);
    if (this->path != NULL) {
        this->actionFunc = func_80BE3178;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    func_80BE30F4(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80BE2808(this);
    this->actor.focus.pos = this->actor.world.pos;
    SkelAnime_Update(&this->skelAnime);
    func_80BE2260(this, globalCtx);
}

void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          (s32)this->skelAnime.dListCount, NULL, NULL, &this->actor);
}
