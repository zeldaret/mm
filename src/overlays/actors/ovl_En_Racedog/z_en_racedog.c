/*
 * File: z_en_racedog.c
 * Overlay: ovl_En_Racedog
 * Description: Racetrack Dog
 */

#include "z_en_racedog.h"
#include "objects/object_dog/object_dog.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnRacedog*)thisx)

void EnRacedog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B24C14(EnRacedog* this, GlobalContext* globalCtx);
void func_80B24CB4(EnRacedog* this, GlobalContext* globalCtx);
s32 func_80B25490(EnRacedog* this, f32* arg1);

typedef struct {
    f32 unk_00;
    f32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} UnkRacedogStruct;

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

static s16 D_80B25D40 = 0;

static s16 D_80B25D44 = -1;

static s16 D_80B25D48 = 0;

static s16 D_80B25D4C = -1;

static f32 D_80B25D50[] = {
    0.0f, 0.0f, 5.0f, 5.5f, 5.0f, 5.0f, 5.5f, 5.0f, 4.5f, 5.5f, 6.0f, 4.0f, 4.0f, 6.0f,
};

static UnkRacedogStruct D_80B25D88[] = {
    { -1.0f, 1.20000004768f, 3, 0, 9, 0x3539 },  { -1.0f, 1.20000004768f, 1, 1, 9, 0x353A },
    { -1.0f, 1.20000004768f, 5, 2, 10, 0x353B }, { -1.0f, 1.20000004768f, 2, 3, 9, 0x353C },
    { -1.0f, 1.20000004768f, 4, 4, 8, 0x353D },  { -1.0f, 1.20000004768f, 2, 5, 9, 0x353E },
    { -1.0f, 1.20000004768f, 3, 6, 9, 0x353F },  { -1.0f, 1.20000004768f, 1, 7, 9, 0x3540 },
    { -1.0f, 1.20000004768f, 1, 8, 9, 0x3541 },  { -1.0f, 1.20000004768f, 6, 9, 8, 0x3542 },
    { -1.0f, 1.20000004768f, 2, 10, 9, 0x3543 }, { -1.0f, 1.20000004768f, 3, 11, 9, 0x3544 },
    { -1.0f, 1.20000004768f, 1, 12, 9, 0x3545 }, { -1.0f, 1.20000004768f, 4, 13, 8, 0x3546 },
};

static UnkRacedogStruct D_80B25E68 = { -1.0f, 1.0, 0, -1, 0, 0x353E };

// Maybe XZ vectors?
static f32 D_80B25E78[] = {
    -3914.0f, 1283.0f, -3747.0f, 1104.0f, -3717.0f, 1169.0f, -3897.0f, 1308.0f,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B25E98 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
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

static AnimationInfoS D_80B25EF0[] = {
    { &object_dog_Anim_0021C8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dog_Anim_0021C8, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },
    { &object_dog_Anim_001BD8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dog_Anim_000998, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },
    { &object_dog_Anim_001FB0, 1.0f, 0, -1, ANIMMODE_ONCE, -6 },
    { &object_dog_Anim_001FB0, 1.0f, 0, -1, ANIMMODE_LOOP_PARTIAL, -6 },
    { &object_dog_Anim_001048, 1.0f, 0, -1, ANIMMODE_ONCE, -6 },
    { &object_dog_Anim_001348, 1.0f, 0, -1, ANIMMODE_LOOP, -6 },
    { &object_dog_Anim_001048, 1.0f, 0, 27, ANIMMODE_ONCE, -6 },
    { &object_dog_Anim_001048, 1.0f, 28, -1, ANIMMODE_ONCE, -6 },
    { &object_dog_Anim_001048, 1.0f, 54, 54, ANIMMODE_ONCE, -6 },
    { &object_dog_Anim_0021C8, -1.5f, -1, 0, ANIMMODE_LOOP, -6 },
    { &object_dog_Anim_001560, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dog_Anim_001A84, 1.2f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dog_Anim_0017C0, 1.2f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dog_Anim_0021C8, 0.5f, 0, -1, ANIMMODE_LOOP, 0 },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B25FF0[] = {
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

static Vec3f D_80B25FF4 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80B26000 = { 0.0f, 20.0f, 0.0f };

extern Gfx D_06000618[];
extern UNK_TYPE D_060080F0;
extern Gfx D_06000550[];

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

void func_80B252F8(EnRacedog* this) {
    if ((this->unk_1E8 >= 9) && (this->unk_29C == 0)) {
        this->unk_29C = 1;
    }

    if ((this->unk_1E8 >= 0xB) && (this->unk_29C == 1)) {
        this->unk_29C = 2;
    }

    if (((this->unk_1E8 >= D_80B25D44) || (this->unk_29C <= 0)) && (this->unk_1E8 > D_80B25D44)) {
        D_80B25D44 = this->unk_1E8;
        D_80B25D4C = this->unk_290;
    }
}

void func_80B2538C(EnRacedog* this) {
    if (func_80B25490(this, D_80B25E78) && this->unk_29C == 2) {
        D_80B25D40++;
        if (D_80B25D40 == 1) {
            Audio_QueueSeqCmd(NA_BGM_HORSE_GOAL | 0x8000);
            play_sound(NA_SE_SY_START_SHOT);
        }

        this->unk_29C = 3;
        if (this->unk_290 == this->unk_292) {
            gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & 7) | (D_80B25D40 * 8);
        }
    }
}

void func_80B25448(EnRacedog* this) {
    if (this->actor.speedXZ < 3.0f) {
        D_80B25EF0[2].playSpeed = 0.9f;
    } else {
        D_80B25EF0[2].playSpeed = 1.0f;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25490.s")

void func_80B255AC(EnRacedog* this, GlobalContext* globalCtx) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 mod = (this->actor.speedXZ > 6.0f) ? 2 : 3;
    Vec3f sp38;

    if (((this->unk_290 + curFrame) % mod) == 0) {
        sp38.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(15.0f);
        sp38.y = this->actor.world.pos.y;
        sp38.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(15.0f);
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &sp38, 10.0f, 0, 2.0f, 300, 0, true);
    }
}

void func_80B256BC(EnRacedog* this) {
    s16 curFrame = this->skelAnime.curFrame;

    if ((curFrame == 1) || (curFrame == 7)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRacedog* this = THIS;
    Vec3f sp2C;

    sp2C = D_80B25FF4;
    this->unk_292 = D_80B25E68.unk_0A;

    this->actionFunc(this, globalCtx);

    func_80B246F4(this, globalCtx);
    func_80B248B8(this, &sp2C);
    Math_ApproachF(&this->unk_2AC.x, sp2C.x, 0.2f, 0.1f);

    if (this->unk_2A0.x > 0.0f) {
        if ((this->unk_2AC.x < 0.0f) && (this->unk_2AC.x > -0.1f)) {
            this->skelAnime.curFrame = 4.0f;
            this->actor.velocity.y = 5.5f;
        }
    }

    if (!(this->actor.bgCheckFlags & 1)) {
        this->skelAnime.curFrame = 0.0f;
    }

    this->unk_2A0 = this->unk_2AC;
    SkelAnime_Update(&this->skelAnime);
}

void func_80B2583C(EnRacedog* this) {
    s16 phi_v1;

    if (this->unk_288 >= 7) {
        this->unk_2BC -= 0x10;
        this->unk_2C0 += 8;
        this->unk_2C4 += 0.05f;
    } else {
        this->unk_2BC += 0x10;
        this->unk_2C0 -= 8;
        this->unk_2C4 -= 0.05f;
    }

    if (this->unk_288 == 0) {
        phi_v1 = 0;
    } else {
        this->unk_288--;
        phi_v1 = this->unk_288;
    }

    if (phi_v1 == 0) {
        this->unk_288 = 0xC;
    }
}

void func_80B258D8(EnRacedog* this, GlobalContext* globalCtx) {
    Vec3s sp48 = gZeroVec3s;
    s32 phi_v0 = (this->unk_290 == this->unk_292) ? 1 : 0;

    if (phi_v0 != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);
        func_80B2583C(this);
        Matrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y + 40.0f,
                                              this->actor.world.pos.z, &sp48);

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, this->unk_2BC, 0, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, this->unk_2C0, 0, 255);
        Matrix_Scale(this->unk_2C4 * 2.0f, this->unk_2C4 * 2.0f, this->unk_2C4 * 2.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06000618);
        gSPDisplayList(POLY_OPA_DISP++, D_06000550);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

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

    switch (D_80B25D88[this->unk_290].unk_08) {
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
    Matrix_RotateStateAroundXAxis(this->unk_2AC.x);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B25A74, func_80B25A90, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
