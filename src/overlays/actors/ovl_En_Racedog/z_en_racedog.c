/*
 * File: z_en_racedog.c
 * Overlay: ovl_En_Racedog
 * Description: Racetrack Dog
 */

#include "z_en_racedog.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnRacedog*)thisx)

void EnRacedog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B24C14(EnRacedog* this, GlobalContext* globalCtx);
void func_80B24CB4(EnRacedog* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Racedog_InitVars = {
    ACTOR_EN_RACEDOG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnRacedog),
    (ActorFunc)EnRacedog_Init,
    (ActorFunc)EnRacedog_Destroy,
    (ActorFunc)EnRacedog_Update,
    (ActorFunc)EnRacedog_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B25E98 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 13, 19, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B25EC4 = { 0, 0, 0, 0, 1 };

// static DamageTable sDamageTable = {
static DamageTable D_80B25ED0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B25FF0[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
    f32 unk_0C;
} D_80B25D90_s;

extern ColliderCylinderInit D_80B25E98;
extern CollisionCheckInfoInit2 D_80B25EC4;
extern DamageTable D_80B25ED0;
extern InitChainEntry D_80B25FF0[];
extern f32 D_80B25F14;
extern D_80B25D90_s D_80B25D90[];
extern Vec3f D_80B26000;

extern UNK_TYPE D_06000618;
extern UNK_TYPE D_060080F0;

void func_80B24630(SkelAnime* skelAnime, AnimationInfoS arg1[], s32 arg2) {
    f32 frameCount;

    arg1 += arg2;
    if (arg1->frameCount < 0) {
        frameCount = Animation_GetLastFrame(arg1->animation);
    } else {
        frameCount = arg1->frameCount;
    }

    Animation_Change(skelAnime, arg1->animation, arg1->playSpeed + (BREG(88) * 0.1f), arg1->startFrame, frameCount,
                     arg1->mode, arg1->morphFrames);
}

void func_80B246F4(EnRacedog* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 26.0f, 10.0f, 0.0f, 5);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2478C.s")

void func_80B248B8(EnRacedog* this, Vec3f* arg1) {
    f32 sp20;
    f32 sp1C;

    if (this->actor.floorPoly != NULL) {
        sp20 = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.y);
        sp1C = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.z);

        arg1->x = -Math_Acot2F(1.0f, -sp1C * sp20);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B251EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B252F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2538C.s")

void func_80B25448(EnRacedog* this) {
    if (this->actor.speedXZ < 3.0f) {
        D_80B25F14 = 0.9f;
    } else {
        D_80B25F14 = 1.0f;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B255AC.s")

void func_80B256BC(EnRacedog* this) {
    s16 curFrame = this->skelAnime.curFrame;

    if ((curFrame == 1) || (curFrame == 7)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2583C.s")

void func_80B258D8(EnRacedog* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B258D8.s")

s32 func_80B25A74(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void func_80B25A90(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnRacedog* this = THIS;
    Vec3f sp1C;

    sp1C = D_80B26000;

    if (limbIndex == 5) {
        Matrix_MultiplyVector3fByState(&sp1C, &this->actor.focus.pos);
    }

    if (limbIndex == 12) {
        func_80B258D8(this, globalCtx);
    }
}

void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRacedog* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    switch (D_80B25D90[this->unk_290].unk_00) {
        case 3:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
            break;
        case 1:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 0);
            break;
        case 5:
            gDPSetEnvColor(POLY_OPA_DISP++, 79, 79, 143, 0);
            break;
        case 6:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 207, 47, 0);
            break;
        case 4:
            gDPSetEnvColor(POLY_OPA_DISP++, 143, 79, 47, 0);
            break;
        case 2:
            gDPSetEnvColor(POLY_OPA_DISP++, 143, 143, 143, 0);
            break;
        default:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
            break;
    }

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateStateAroundXAxis(this->unk_2AC);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B25A74, func_80B25A90, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
