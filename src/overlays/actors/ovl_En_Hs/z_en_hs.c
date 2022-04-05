/*
 * File: z_en_hs.c
 * Overlay: ovl_En_Hs
 * Description: Grog
 */

#include "z_en_hs.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnHs*)thisx)

void EnHs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80952FE0(EnHs* this, GlobalContext* globalCtx);
void func_80953098(EnHs* this, GlobalContext* globalCtx);
void func_80953180(EnHs* this, GlobalContext* globalCtx);
void func_809532C0(EnHs* this, GlobalContext* globalCtx);
void func_809532D0(EnHs* this, GlobalContext* globalCtx);
void func_80953354(EnHs* this, GlobalContext* globalCtx);
void func_8095345C(EnHs* this, GlobalContext* globalCtx);

const ActorInit En_Hs_InitVars = {
    ACTOR_EN_HS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HS,
    sizeof(EnHs),
    (ActorFunc)EnHs_Init,
    (ActorFunc)EnHs_Destroy,
    (ActorFunc)EnHs_Update,
    (ActorFunc)EnHs_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 40, 40, 0, { 0, 0, 0 } },
};

Vec3f D_8095393C = { 300.0f, 1000.0f, 0.0f };

void func_80952C50(EnHs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_2A4); i++) {
        Math_Vec3f_Copy(&this->unk_2A4[i], &player->actor.world.pos);
    }

    this->actor.home.rot.x = 0;
    this->actor.home.rot.z = 0;
}

void EnHs_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnHs* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_hs_Skel_006260, &object_hs_Anim_0005C0, this->jointTable,
                       this->morphTable, OBJECT_HS_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &object_hs_Anim_0005C0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_8095345C;
    if (globalCtx->curSpawn == 1) {
        this->actor.flags |= ACTOR_FLAG_10000;
    }
    this->unk_2A0 = 0;
    this->actor.targetMode = 6;
    func_80952C50(this, globalCtx);
}

void EnHs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80952DFC(GlobalContext* globalCtx) {
    if (INV_CONTENT(ITEM_MASK_BUNNY) == ITEM_MASK_BUNNY) {
        func_80151BB4(globalCtx, 0x2E);
    }
    func_80151BB4(globalCtx, 0x10);
}

void func_80952E50(Vec3f* dst, Vec3f src, f32 arg2) {
    Vec3f sp1C;
    f32 temp_f0;

    Math_Vec3f_Diff(&src, dst, &sp1C);

    temp_f0 = SQ(sp1C.x) + SQ(sp1C.z);

    if (SQ(arg2) > temp_f0) {
        return;
    }

    temp_f0 = sqrtf(temp_f0);
    sp1C.x *= (temp_f0 - arg2) / temp_f0;
    sp1C.z *= (temp_f0 - arg2) / temp_f0;

    dst->x += sp1C.x;
    dst->z += sp1C.z;
}

void func_80952F00(EnHs* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;
    f32 phi_f20;

    if (this->actor.home.rot.z >= 20) {
        phi_f20 = 15.0f;
    } else {
        phi_f20 = 10.0f;
    }

    func_80952E50(&this->unk_2A4[0], player->actor.world.pos, phi_f20);

    for (i = 1; i < ARRAY_COUNT(this->unk_2A4); i++) {
        func_80952E50(&this->unk_2A4[i], this->unk_2A4[i - 1], phi_f20);
    }
}

void func_80952FE0(EnHs* this, GlobalContext* globalCtx) {
    if (this->unk_2A2 < 40) {
        Math_SmoothStepToS(&this->unk_294.y, 0x1F40, 6, 0x1838, 0x64);
    } else if (this->unk_2A2 < 80) {
        Math_SmoothStepToS(&this->unk_294.y, -0x1F40, 6, 0x1838, 0x64);
    } else {
        this->actionFunc = func_80953180;
        this->unk_2A0 &= ~4;
        func_80151938(globalCtx, 0x33F6);
        func_80952DFC(globalCtx);
    }
    this->unk_2A2++;
}

void func_80953098(EnHs* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_8095345C;
        this->actor.flags |= ACTOR_FLAG_10000;
        this->unk_2A0 |= 0x10;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
    } else {
        this->unk_2A0 |= 8;
        if (INV_CONTENT(ITEM_MASK_BUNNY) == ITEM_MASK_BUNNY) {
            Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_RED, 10000.0f, 50.0f);
        } else {
            Actor_PickUp(&this->actor, globalCtx, GI_MASK_BUNNY, 10000.0f, 50.0f);
        }
    }
}

void func_80953180(EnHs* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x33F4:
            case 0x33F6:
                func_801477B4(globalCtx);
                this->actionFunc = func_8095345C;
                break;

            case 0x33F7:
                this->actor.flags &= ~ACTOR_FLAG_10000;
                func_801477B4(globalCtx);
                this->actionFunc = func_80953098;
                func_80953098(this, globalCtx);
                break;

            case 0x33F9:
                this->actor.flags &= ~ACTOR_FLAG_10000;
                func_801477B4(globalCtx);
                this->actionFunc = func_8095345C;
                break;

            case 0x33F5:
                globalCtx->msgCtx.unk11F10 = 0;
                this->actionFunc = func_80952FE0;
                this->unk_2A2 = 0;
                this->unk_294.z = 0;
                this->unk_2A0 |= 4;
                break;

            default:
                func_801477B4(globalCtx);
                this->actionFunc = func_8095345C;
                break;
        }
    }
}

void func_809532C0(EnHs* this, GlobalContext* globalCtx) {
}

void func_809532D0(EnHs* this, GlobalContext* globalCtx) {
    if (DECR(this->unk_2A2) == 0) {
        globalCtx->nextEntranceIndex = globalCtx->setupExitList[ENHS_GET_F(&this->actor)];
        globalCtx->sceneLoadFlag = 0x14;
        gSaveContext.save.weekEventReg[25] |= 8;
        this->actionFunc = func_809532C0;
    }
}

void func_80953354(EnHs* this, GlobalContext* globalCtx) {
    if (!Play_InCsMode(globalCtx)) {
        func_800B7298(globalCtx, &this->actor, 7);
        this->actionFunc = func_809532D0;
    }
}

void func_809533A0(EnHs* this, GlobalContext* globalCtx) {
    u16 sp1E;

    if ((globalCtx->curSpawn == 1) && !(this->unk_2A0 & 0x20)) {
        sp1E = 0x33F7;
        this->unk_2A0 |= 0x20;
    } else if (this->unk_2A0 & 0x10) {
        sp1E = 0x33F9;
        this->unk_2A0 &= ~0x10;
    } else if (gSaveContext.save.weekEventReg[25] & 8) {
        sp1E = 0x33F4;
    } else {
        sp1E = 0x33F5;
    }

    Message_StartTextbox(globalCtx, sp1E, &this->actor);

    if (sp1E == 0x33F4) {
        func_80952DFC(globalCtx);
    }
}

void func_8095345C(EnHs* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80953180;
        func_809533A0(this, globalCtx);
        if (this->unk_2A0 & 8) {
            func_80952DFC(globalCtx);
            this->unk_2A0 &= ~8;
        }
    } else if (this->actor.home.rot.x >= 20) {
        this->actionFunc = func_80953354;
        this->unk_2A2 = 40;
    } else if CHECK_FLAG_ALL (this->actor.flags, ACTOR_FLAG_10000) {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, -1);
        this->unk_2A0 |= 1;
    } else if ((this->actor.xzDistToPlayer < 120.0f) && Player_IsFacingActor(&this->actor, 0x2000, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 130.0f);
        this->unk_2A0 |= 1;
    } else {
        this->unk_2A0 &= ~1;
    }
}

void EnHs_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnHs* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (SkelAnime_Update(&this->skelAnime)) {
        this->skelAnime.curFrame = 0.0f;
    }

    this->actionFunc(this, globalCtx);

    func_80952F00(this, globalCtx);

    if (this->unk_2A0 & 4) {
        Math_SmoothStepToS(&this->unk_294.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_29A.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_29A.y, 0, 6, 0x1838, 0x64);
    } else if (this->unk_2A0 & 1) {
        func_800E9250(globalCtx, &this->actor, &this->unk_294, &this->unk_29A, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_294.x, 0x3200, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_294.y, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_29A.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_29A.y, 0, 6, 0x1838, 0x64);
    }
}

s32 EnHs_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHs* this = THIS;

    switch (limbIndex) {
        case OBJECT_HS_LIMB_09:
            rot->x += this->unk_294.y;
            rot->z += this->unk_294.x;
            break;

        case OBJECT_HS_LIMB_0A:
            rot->x += this->unk_294.y;
            rot->z += this->unk_294.x;
            break;

        case OBJECT_HS_LIMB_0B:
            *dList = NULL;
            return false;

        case OBJECT_HS_LIMB_0C:
            if (this->actor.params == ENHS_1) {
                *dList = NULL;
                return false;
            }
            break;

        case OBJECT_HS_LIMB_0D:
            if (this->actor.params == ENHS_1) {
                *dList = NULL;
                return false;
            }
            break;
    }
    return false;
}

void EnHs_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnHs* this = THIS;

    if (limbIndex == OBJECT_HS_LIMB_09) {
        Matrix_MultiplyVector3fByState(&D_8095393C, &this->actor.focus.pos);
    }
}

void EnHs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHs* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnHs_OverrideLimbDraw, EnHs_PostLimbDraw, &this->actor);
}
