/*
 * File: z_en_guard_nuts.c
 * Overlay: ovl_En_Guard_Nuts
 * Description: Deku Palace - Entrance Guard
 */

#include "z_en_guard_nuts.h"
#include "objects/object_dnk/object_dnk.h"

#define FLAGS 0x80100009

#define THIS ((EnGuardNuts*)thisx)

void EnGuardNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGuardNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ABB210(EnGuardNuts* this, s32 index);
void func_80ABB29C(EnGuardNuts* this);
void func_80ABB2D4(EnGuardNuts* this, GlobalContext* globalCtx);
void func_80ABB540(EnGuardNuts* this);
void func_80ABB590(EnGuardNuts* this, GlobalContext* globalCtx);
void func_80ABB854(EnGuardNuts* this, GlobalContext* globalCtx);
void func_80ABB91C(EnGuardNuts* this, GlobalContext* globalCtx);
void func_80ABB990(EnGuardNuts* this, GlobalContext* globalCtx);

const ActorInit En_Guard_Nuts_InitVars = {
    ACTOR_EN_GUARD_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnGuardNuts),
    (ActorFunc)EnGuardNuts_Init,
    (ActorFunc)EnGuardNuts_Destroy,
    (ActorFunc)EnGuardNuts_Update,
    (ActorFunc)EnGuardNuts_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON | OCELEM_UNK3,
    },
    { 50, 50, 0, { 0, 0, 0 } },
};

s32 D_80ABBE1C = 0;

s32 D_80ABBE20 = 0;

u16 D_80ABBE24[] = { 0x0824, 0x0825, 0x0826, 0x082D, 0x0827, 0x0828, 0x0829, 0x082A, 0x082B, 0x082C };

s16 D_80ABBE38[] = { 0x0000, 0x0000, 0x0002, 0x0001, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0002 };

static AnimationHeader* D_80ABBE4C[] = {
    &object_dnk_Anim_002A08,
    &object_dnk_Anim_002B6C,
    &object_dnk_Anim_000430,
    &object_dnk_Anim_002B6C,
};

u8 D_80ABBE5C[] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE };

static TexturePtr D_80ABBE60[] = { object_dnk_Tex_001680, object_dnk_Tex_001700, object_dnk_Tex_001780 };

void EnGuardNuts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_dnk_Skel_002848, &object_dnk_Anim_002A08, this->jointTable,
                   this->morphTable, 11);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 1;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Actor_SetScale(&this->actor, 0.015f);
    Math_Vec3f_Copy(&this->unk228, &this->actor.world.pos);
    this->unk21E = D_80ABBE1C;
    D_80ABBE1C++;
    if (!(gSaveContext.weekEventReg[23] & 0x20)) {
        func_80ABB29C(this);
    } else {
        func_80ABB854(this, globalCtx);
    }
}

void EnGuardNuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80ABB210(EnGuardNuts* this, s32 index) {
    this->animIndex = index;
    this->animeFrameCount = Animation_GetLastFrame(D_80ABBE4C[this->animIndex]);
    Animation_Change(&this->skelAnime, D_80ABBE4C[this->animIndex], 1.0f, 0.0f, this->animeFrameCount,
                     D_80ABBE5C[this->animIndex], -2.0f);
}

void func_80ABB29C(EnGuardNuts* this) {
    func_80ABB210(this, 0);
    this->unk21C = 0;
    this->actionFunc = func_80ABB2D4;
}

void func_80ABB2D4(EnGuardNuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 phi_a1;
    s16 temp_a2;
    s32 phi_a2;

    SkelAnime_Update(&this->skelAnime);
    temp_a2 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.home.rot.y));
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80ABB540(this);
        return;
    }
    if (temp_a2 > 0x6000) {
        D_80ABBE20 = 2;
    }
    if (player->transformation == 3) {
        this->textId = 0;
        if ((gSaveContext.weekEventReg[0x11] & 4) && (this->unk224 == 0)) {
            this->textId = 7;
        } else if (gSaveContext.weekEventReg[0xC] & 0x40) {
            this->textId = 4;
        }
    } else {
        this->textId = 3;
    }
    this->actor.textId = D_80ABBE24[this->textId];
    phi_a1 = this->actor.world.rot.y;
    if (D_80ABBE20 == 2) {
        func_80ABB854(this, globalCtx);
        return;
    }
    if (D_80ABBE20 == 1) {
        if (this->animIndex != 1) {
            func_80ABB210(this, 1);
        }
        phi_a1 = (this->actor.home.rot.y + 0x8000);
    }
    if (fabsf((f32)(this->actor.shape.rot.y - phi_a1)) < 100.0f) {
        this->actor.shape.rot.y = phi_a1;
        if ((D_80ABBE20 == 1) && (this->animIndex != 3)) {
            func_80ABB210(this, 3);
        }
    } else {
        Math_SmoothStepToS(&this->actor.shape.rot.y, phi_a1, 1, 0xBB8, 0);
    }
    if (this->unk23A == 0) {
        if (fabsf((f32)this->actor.world.rot.y - (f32)this->actor.yawTowardsPlayer) < 10000.0f) {
            this->unk23C = this->actor.world.rot.y - this->actor.yawTowardsPlayer;
            this->unk23C = -this->unk23C;
        }
    }
    func_800B8614(&this->actor, globalCtx, 70.0f);
}

void func_80ABB540(EnGuardNuts* this) {
    func_80ABB210(this, 1);
    this->unk23C = 0;
    this->unk23A = this->unk23C;
    this->unk214 = 0x10;
    this->unk21C = 1;
    this->actionFunc = func_80ABB590;
}

void func_80ABB590(EnGuardNuts* this, GlobalContext* globalCtx) {
    s16 yaw = this->actor.yawTowardsPlayer;
    f32 curFrame;

    if (D_80ABBE20 == 1) {
        yaw = (this->actor.home.rot.y + 0x8000);
    }
    if (fabsf((this->actor.shape.rot.y - yaw)) < 100.0f) {
        this->actor.shape.rot.y = yaw;
        curFrame = this->skelAnime.curFrame;
        if ((curFrame < this->animeFrameCount) || (this->textId >= 7)) {
            SkelAnime_Update(&this->skelAnime);
        }
    } else {
        SkelAnime_Update(&this->skelAnime);
        Math_SmoothStepToS(&this->actor.shape.rot.y, yaw, 1, 0xBB8, 0);
    }
    if (Message_GetState(&globalCtx->msgCtx) == 5) {
        this->unk23C = 0;
        this->unk23A = 0;
        if ((this->textId == 3) && (this->animIndex == 0)) {
            func_80ABB210(this, 0);
        }
        if (func_80147624(globalCtx) != 0) {
            if (D_80ABBE38[this->textId] != 1) {
                if (D_80ABBE38[this->textId] == 2) {
                    func_801477B4(globalCtx);
                    D_80ABBE20 = 2;
                    gSaveContext.weekEventReg[0xC] |= 0x40;
                    func_80ABB854(this, globalCtx);
                    return;
                }
                this->textId++;
                func_801518B0(globalCtx, D_80ABBE24[this->textId], &this->actor);
                if (D_80ABBE38[this->textId] == 2) {
                    D_80ABBE20 = 1;
                }
                this->unk214 = 0x10;
                return;
            }
            if (this->textId != 3) {
                this->unk23A = 0;
                this->unk23C = this->unk23A;
                func_801477B4(globalCtx);
                this->unk21C = 4;
                this->actionFunc = func_80ABB990;
                return;
            }
            func_801477B4(globalCtx);
            func_80ABB29C(this);
        }
    } else if ((Message_GetState(&globalCtx->msgCtx) >= 3) && (D_80ABBE20 == 0)) {
        if ((this->textId == 0) || (this->textId == 3) || (this->textId >= 7)) {
            if (this->unk214 == 0) {
                this->unk214 = 2;
                this->unk23C ^= 0x2000;
            }
        } else if (this->unk214 == 0) {
            this->unk214 = 2;
            this->unk23A ^= 0x2000;
        }
    }
}

void func_80ABB854(EnGuardNuts* this, GlobalContext* globalCtx) {
    Vec3f sp3C;

    func_80ABB210(this, 2);
    Math_Vec3f_Copy(&sp3C, &this->actor.world.pos);
    sp3C.y = this->actor.floorHeight;
    EffectSsHahen_SpawnBurst(globalCtx, &sp3C, 4.0f, 0, 0xA, 3, 0xF, -1, 0xA, NULL);
    this->unk23C = 0;
    this->actor.flags |= 0x08000000;
    this->unk23A = this->unk23C;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    this->actionFunc = func_80ABB91C;
}

void func_80ABB91C(EnGuardNuts* this, GlobalContext* globalCtx) {
    f32 sp1C = this->skelAnime.curFrame;

    SkelAnime_Update(&this->skelAnime);
    if (this->animeFrameCount <= sp1C) {
        this->unk21C = 3;
        this->actionFunc = func_80ABB990;
        this->actor.world.rot.y = this->actor.home.rot.y;
        this->actor.shape.rot.y = this->actor.home.rot.y;
    }
}

void func_80ABB990(EnGuardNuts* this, GlobalContext* globalCtx) {
    s16 phi_v1;
    Vec3f sp40;

    if (!(gSaveContext.weekEventReg[0x17] & 0x20)) {
        phi_v1 = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.home.rot.y));
        if ((phi_v1 < 0x4000) && ((D_80ABBE20 == 0) || (this->actor.xzDistToPlayer > 150.0f))) {
            Math_Vec3f_Copy(&sp40, &this->actor.world.pos);
            sp40.y = this->actor.floorHeight;
            EffectSsHahen_SpawnBurst(globalCtx, &sp40, 4.0f, 0, 0xA, 3, 0xF, -1, 0xA, NULL);
            Actor_PlaySfxAtPos(&this->actor, 0x387CU);
            D_80ABBE20 = 0;
            if (this->textId == 9) {
                this->unk224 = 1;
            }
            this->actor.flags &= 0xF7FFFFFF;
            func_80ABB29C(this);
        }
    }
}

void EnGuardNuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;
    s32 pad;

    if (this->unk212 == 0) {
        this->unk210++;
        if (this->unk210 >= 3) {
            this->unk210 = 0;
            this->unk212 = (s16)Rand_ZeroFloat(60.0f) + 0x14;
        }
    }
    if ((this->animIndex == 1) &&
        ((Animation_OnFrame(&this->skelAnime, 1.0f)) || (Animation_OnFrame(&this->skelAnime, 5.0f)))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
    }

    this->actionFunc(this, globalCtx);
    Actor_SetFocus(&this->actor, 40.0f);
    Math_SmoothStepToS(&this->unk234, this->unk23A, 1, 0xBB8, 0);
    Math_SmoothStepToS(&this->unk236, this->unk23C, 1, 0xBB8, 0);

    if (this->unk212 != 0) {
        this->unk212--;
    }
    if (this->unk214 != 0) {
        this->unk214--;
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);
    if ((this->unk21C != 3) && (this->unk21C != 4)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

// OverrideLimb
s32 func_80ABBC60(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGuardNuts* this = THIS;

    if (limbIndex == 2) {
        rot->x += this->unk234;
        rot->y += this->unk236;
        rot->z += this->unk238;
    }
    return false;
}

void EnGuardNuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGuardNuts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80ABBE60[this->unk210]));

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80ABBC60, NULL,
                      &this->actor);
    Matrix_InsertTranslation(this->unk228.x, this->actor.floorHeight, this->unk228.z, 0);
    Matrix_Scale(0.015f, 0.015f, 0.015f, 1);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, object_dnk_DL_002700);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
