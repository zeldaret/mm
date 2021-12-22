/*
 * File: z_en_nb.c
 * Overlay: ovl_En_Nb
 * Description: Anju's Grandma
 */

#include "z_en_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC0D84(EnNb* this, GlobalContext* globalCtx);
void func_80BC0EAC(EnNb* this, GlobalContext* globalCtx);

void func_80BC08E0(EnNb* this, GlobalContext* globalCtx);
void func_80BC0978(EnNb* this, GlobalContext* globalCtx);

s32 func_80BC00AC(EnNb* this, GlobalContext* globalCtx);
s32 func_80BC01DC(EnNb* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BC15F0 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 68, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BC161C = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80BC15F0;
extern CollisionCheckInfoInit2 D_80BC161C;

extern FlexSkeletonHeader D_06008C40;

Actor* func_80BBFDB0(EnNb* this, GlobalContext* globalCtx, u8 arg2, s16 arg3);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BBFDB0.s")

void func_80BBFE60(EnNb* this) {
    this->skelAnime.playSpeed = this->unk_268;
    SkelAnime_Update(&this->skelAnime);
}

extern ActorAnimationEntryS D_80BC1628[];

s32 func_80BBFE8C(EnNb* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 phi_t0 = 0;

    if ((arg1 == 0) || (arg1 == 1)) {
        if ((this->unk_290 != 0) && (this->unk_290 != 1)) {
            phi_v1 = true;
        }
    } else if (arg1 != this->unk_290) {
        phi_v1 = true;
    }

    if (phi_v1) {
        this->unk_290 = arg1;
        phi_t0 = func_8013BC6C(&this->skelAnime, D_80BC1628, arg1);
        this->unk_268 = this->skelAnime.playSpeed;
    }

    return phi_t0;
}

void func_80BBFF24(EnNb* this, GlobalContext* globalCtx) {
    f32 diff;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);

    diff = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = diff;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

Actor* func_80BBFF90(EnNb* this, GlobalContext* globalCtx) {
    Actor* phi_v1;

    if (this->unk_1DC == 2) {
        phi_v1 = func_80BBFDB0(this, globalCtx, 4, 0x202);
    } else {
        phi_v1 = &GET_PLAYER(globalCtx)->actor;
    }
    return phi_v1;
}

s32 func_80BBFFD4(EnNb* this, s16 arg1) {
    s32 sp1C = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(arg1);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        sp1C = true;
    } else {
        ActorCutscene_SetIntentToPlay(arg1);
    }

    return sp1C;
}

s16 func_80BC0050(EnNb* this, s32 arg1) {
    s16 cutscene = this->actor.cutscene;
    s32 i;

    for (i = 0; i < arg1; i++) {
        cutscene = ActorCutscene_GetAdditionalCutscene(cutscene);
    }

    return cutscene;
}

s32 func_80BC00AC(EnNb* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80BC0050(this, 0);
    s32 phi_v1 = 0;

    switch (this->unk_288) {
        case 0x0:
            if (func_80BBFFD4(this, sp2A) != 0) {
            case 0x2:
            case 0x4:
            case 0x6:
            case 0x8:
                func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), this);
                this->unk_288++;
                phi_v1 = 1;
            }
            break;

        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), this->actor.child);
            }
            this->unk_288++;
            phi_v1 = 1;
            break;

        case 0x9:
            ActorCutscene_Stop(sp2A);
            this->unk_288++;
            phi_v1 = 1;
            break;
    }

    return phi_v1;
}

s32 func_80BC01DC(EnNb* this, GlobalContext* globalCtx) {
    s32 pad[2];
    s32 sp2C = 0;

    switch ( this->unk_288) {
        case 0x0:
            if (Player_GetMask(globalCtx) == PLAYER_MASK_ALL_NIGHT) {
                this->unk_288 = 1;
            } else {
                this->unk_288 = 5;
            }
            break;

        case 0x1:
            func_8016A268(globalCtx, 1, 0, 0, 0, 0);
            this->unk_286 = 0x28;
            this->unk_288 = (u16) ((s16) this->unk_288 + 1);
            break;

        case 0x2:
            gGameInfo->data[0x224] = (s16) (s32) (255.0f - (((f32) ABS_ALT(20 - this->unk_286) / 20.0f) * 255.0f));

            if (this->unk_286 == 0x14) {
                if ((gSaveContext.eventInf[4] & 4) != 0) {
                    globalCtx->interfaceCtx.unk_31B = 0;
                } else {
                    globalCtx->interfaceCtx.unk_31B = 1;
                }
                globalCtx->interfaceCtx.unk_31A = 6;
                gGameInfo->data[0x59B] = 0xFF;
            }

            if (DECR(this->unk_286) == 0) {
                this->unk_288++;
            }
            break;

        case 0x3:
            globalCtx->interfaceCtx.unk_31A = 4;
            this->unk_288++;
            sp2C = 1;
            break;

        case 0x4:
            globalCtx->interfaceCtx.unk_31A = 5;
            this->unk_288++;
            /* fallthrough */
        case 0x5:
            if (!(gSaveContext.eventInf[4] & 4)) {
                gSaveContext.time = CLOCK_TIME(8, 0);
                Sram_IncrementDay();
            } else {
                func_800FE658(120.0f);
            }

            this->unk_288++;
            globalCtx->nextEntranceIndex = 0xBC20;
            gSaveContext.nextCutsceneIndex = 0;
            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 2;
            gSaveContext.nextTransition = 6;
            gSaveContext.eventInf[4] |= 8;
            break;
    }

    return sp2C;
}


UNK_PTR func_80BC045C(EnNb* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC045C.s")

s32 func_80BC04FC(EnNb* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC04FC.s")

void func_80BC05A8(EnNb* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC05A8.s")

void func_80BC06C4(EnNb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC06C4.s")

void func_80BC0800(EnNb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC08E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0978.s")

UNK_TYPE func_80BC0A18(EnNb* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0A18.s")

// ?
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0B98.s")

// ?
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0C0C.s")

UNK_TYPE func_80BC0C80(EnNb* this, GlobalContext* globalCtx, u8* arg2);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0C80.s")

// ?
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0D08.s")

void func_80BC0D1C(EnNb* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0D1C.s")

extern UNK_TYPE D_80BC13F0[];

#ifdef NON_MATCHING
void func_80BC0D84(EnNb* this, GlobalContext* globalCtx) {
    s32 pad;
    struct_80133038_arg2 sp20;

    this->unk_280 =  gGameInfo->data[0xF] + ((void)0, gSaveContext.unk_14);

    if (gSaveContext.eventInf[4] & 8) {
        sp20.unk0 = 1;
        func_80BC0C80(this, globalCtx, &sp20.unk0);
        this->actor.shape.shadowDraw = func_800B3FC0;
        this->actor.flags |= 1;
    } else if ((func_80133038(globalCtx, D_80BC13F0, &sp20) == 0) || ((sp20.unk0 != this->unk_1DC) && (func_80BC0C80(this, globalCtx, &sp20.unk0) == 0))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~1;
        sp20.unk0 = 0;
    } else {
        this->actor.shape.shadowDraw = func_800B3FC0;
        this->actor.flags |= 1;
    }

    this->unk_1DC = sp20.unk0;
    this->unk_1E8 = func_80BBFF90(this, globalCtx);
    func_80BC0D1C(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0D84.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Nb/func_80BC0EAC.s")

void EnNb_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06008C40, NULL, this->jointTable, this->morphTable, 8);

    this->unk_290 = -1;
    func_80BBFE8C(this, 0);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80BC15F0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80BC161C);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_262 = 0;

    if (gSaveContext.eventInf[4] & 8) {
        func_8013AED4(&this->unk_262, 4, 7);
    } else {
        gSaveContext.eventInf[4] &= 0xFB;
        gSaveContext.eventInf[4] &= 0xF7;
    }

    this->actionFunc = func_80BC0D84;
    this->actionFunc(this, globalCtx);
}

void EnNb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    globalCtx->interfaceCtx.unk_31A = 3;
}

void EnNb_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    func_80BC04FC(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80BC0A18(this, globalCtx);

    if (this->unk_1DC != 0) {
        func_80BBFE60(this);
        func_80BC0800(this);
        if (Actor_IsActorFacingLink(&this->actor, 0x38E0)) {
            func_8013C964(&this->actor, globalCtx, this->unk_274, 30.0f, 0, this->unk_262 & 7);
        }
        func_80BBFF24(this, globalCtx);
    }
}

// OverrideLimbDraw
s32 func_80BC1174(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 5) {
        func_80BC05A8((EnNb* ) thisx, globalCtx);
    }
    return 0;
}

// PostLimbDraw
void func_80BC11B4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnNb* this = THIS;
    Vec3f sp18;

    if ((ActorCutscene_GetCurrentIndex() == -1) && (limbIndex == 5)) {
        Matrix_MultiplyVector3fByState(&D_801D15B0, (Vec3f* ) &sp18);
        Math_ApproachF(&thisx->focus.pos.x, sp18.x, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.y, sp18.y, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.z, sp18.z, 0.6f, 10000.0f);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

// UnkActorDraw
void func_80BC1278(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnNb* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    if (!(this->unk_262 & 0x400)) {
        phi_v1 = false;
        if (this->unk_262 & 0x100) {
            phi_v1 = true;
            phi_v0 = true;
        } else {
            phi_v0 = true;
        }
    } else {
        phi_v1 = false;
        phi_v0 = false;
    }

    if (limbIndex == 5) {
        func_8013AD9C(this->unk_27C + 0x4000, this->unk_27E + this->actor.shape.rot.y + 0x4000, &this->unk_1F0, &this->unk_1FC, phi_v0, phi_v1);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_1F0.x, this->unk_1F0.y, this->unk_1F0.z, 0);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
        Matrix_RotateY(this->unk_1FC.y, 1);
        Matrix_InsertXRotation_s(this->unk_1FC.x, 1);
        Matrix_InsertZRotation_s(this->unk_1FC.z, 1);
        Matrix_StatePush();
    }
}

void EnNb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNb* this = THIS;

    if (this->unk_1DC != 0) {
        func_8012C5B0(globalCtx->state.gfxCtx);
        func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, func_80BC1174, func_80BC11B4, func_80BC1278, &this->actor);
    }
}

