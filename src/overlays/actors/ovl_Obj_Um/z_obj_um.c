/*
 * File: z_obj_um.c
 * Overlay: ovl_Obj_Um
 * Description: Cremia's Cart and milk run minigame
 */

#include "z_obj_um.h"
#include "overlays/actors/ovl_En_In/z_en_in.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjUm*)thisx)

#define NOT_DEBUG_PRINT 1

/**
 * weekEventReg flags checked by this actor:
 * - gSaveContext.save.weekEventReg[22] & 1: Aliens defeated
 *     If false: The actor doesn't spawn
 * - gSaveContext.save.weekEventReg[31] & 0x40
 *     If true: Cremia doesn't explain again she'll deliever milk to town
 * - gSaveContext.save.weekEventReg[31] & 0x80
 *     If true: Triggers cutscene on Romani's Ranch
 * - gSaveContext.save.weekEventReg[34] & 0x80
 *     If true: Doesn't spawn on Romani's Ranch
 * - gSaveContext.save.weekEventReg[52] & 1
 *     If true: Doesn't spawn on Romani's Ranch or Milk Road
 * - gSaveContext.save.weekEventReg[52] & 2
 *     If true: Doesn't spawn on Romani's Ranch or Milk Road
 * - gSaveContext.save.weekEventReg[59] & 2
 *     If true: Doesn't spawn again on Milk Road
 *
 * weekEventReg flags set by this actor:
 * - gSaveContext.save.weekEventReg[31] |= 0x40: Cremia offered a ride
 *     Cremia offered a ride accross the Milk Road to Player
 * - gSaveContext.save.weekEventReg[31] |= 0x80: Player is in Milk Run
 *     Player accepts the ride and is with Cremia during the Milk Run.
 * - gSaveContext.save.weekEventReg[34] |= 0x80: Cremia does Milk Run alone
 *     Player didn't interact or didn't accept the ride
 * - gSaveContext.save.weekEventReg[52] |= 1: Won Milk Run minigame
 *     At least one pot is safe. Turns off the "Lose Milk Run minigame"
 * - gSaveContext.save.weekEventReg[52] |= 2: Lose Milk Run minigame
 *     Every pot was broken by bandits. Turns off the ""Win" Milk Run minigame"
 * - gSaveContext.save.weekEventReg[59] |= 2: ?
 *     Passed through Milk Road after winning the Milk Run
 *
 * weekEventReg flags unset by this actor:
 * - gSaveContext.save.weekEventReg[31] &= (u8)~0x80
 *     Turned off when the Milk Run finishes
 * - gSaveContext.save.weekEventReg[52] &= (u8)~1
 *     Turned off if Player lose the Milk Run
 * - gSaveContext.save.weekEventReg[52] &= (u8)~2
 *     Turned off if Player wins the Milk Run
 */

void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B7A070(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A7AC(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_PostMilkRunStartCs(ObjUm* this, GlobalContext* globalCtx);

void ObjUm_StopAnim(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_UpdateAnim(ObjUm* this, GlobalContext* globalCtx, s32);

void ObjUm_SetupAction(ObjUm* this, ObjUmActionFunc actionFunc);

const ActorInit Obj_Um_InitVars = {
    ACTOR_OBJ_UM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_UM,
    sizeof(ObjUm),
    (ActorFunc)ObjUm_Init,
    (ActorFunc)ObjUm_Destroy,
    (ActorFunc)ObjUm_Update,
    (ActorFunc)ObjUm_Draw,
};

static TexturePtr sEyeTextures[] = {
    gUmEyeOpenTex,
    gUmEyeHalfTex,
    gUmEyeClosedTex,
    gUmEyePleasedTex,
    gUmEyeAngryTex,
    gUmEyeSadTex,
};

static TexturePtr sMouthTextures[] = {
    gUmMouthNeutralTex,
    gUmMouthHappyTex,
    gUmMouthOpenTex,
    gUmMouthSadTex,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000020, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 40, 64, 0, { 0, 0, 0 } },
};

// actionfuncs
void func_80B7A144(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_RanchWait(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_PreMilkRunStartCs(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_StartCs(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_PostMilkRunStartCs(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_TerminaFieldIdle(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_RanchWaitPathFinished(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A070(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_RanchStartCs(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A240(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A394(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_RunMinigame(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AB78(ObjUm* this, GlobalContext* globalCtx);
void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_PostMilkRunWaitPathFinished(ObjUm* this, GlobalContext* globalCtx);

// This function may be wrongly named...
void ObjUm_UpdateBanditsPositions(ObjUm* this, GlobalContext* globalCtx) {
    s16 rotY = this->dyna.actor.shape.rot.y;
    Vec3f sp108;
    Vec3f spFC;
    Vec3f spF0;
    Vec3f spE4;
    Vec3f spD8;
    Vec3f spCC;
    Vec3f spC0;
    Vec3f spB4;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60 = this->dyna.actor.world.pos;

    // Loop unroll?
    this->unk_360[15] = sp60;
    sp6C = sp60;
    this->unk_360[14] = sp6C;
    sp78 = sp6C;
    this->unk_360[13] = sp78;
    sp84 = sp78;
    this->unk_360[12] = sp84;
    sp90 = sp84;
    this->unk_360[11] = sp90;
    sp9C = sp90;
    this->unk_360[10] = sp9C;
    spA8 = sp9C;
    this->unk_360[9] = spA8;
    spB4 = spA8;
    this->unk_360[8] = spB4;
    spC0 = spB4;
    this->unk_360[7] = spC0;
    spCC = spC0;
    this->unk_360[6] = spCC;
    spD8 = spCC;
    this->unk_360[5] = spD8;
    spE4 = spD8;
    this->unk_360[4] = spE4;
    spF0 = spE4;
    this->unk_360[3] = spF0;
    spFC = spF0;
    this->unk_360[2] = spFC;
    sp108 = spFC;
    this->unk_360[1] = sp108;
    this->unk_360[0] = sp108;

    this->unk_360[0].x += 110.0f * Math_SinS(rotY + 0x4000);
    this->unk_360[0].z += 110.0f * Math_CosS(rotY + 0x4000);
    this->unk_360[1].x += 110.0f * Math_SinS(rotY - 0x4000);
    this->unk_360[1].z += 110.0f * Math_CosS(rotY - 0x4000);
    Math_Vec3f_Copy(&this->unk_360[2], &this->unk_360[0]);
    this->unk_360[2].x -= 200.0f * Math_SinS(rotY);
    this->unk_360[2].z -= 200.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[4], &this->unk_360[1]);
    this->unk_360[4].x -= 200.0f * Math_SinS(rotY);
    this->unk_360[4].z -= 200.0f * Math_CosS(rotY);
    this->unk_360[3].x -= 220.0f * Math_SinS(rotY);
    this->unk_360[3].z -= 220.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[5], &this->unk_360[0]);
    this->unk_360[5].x -= 500.0f * Math_SinS(rotY);
    this->unk_360[5].z -= 500.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[7], &this->unk_360[1]);
    this->unk_360[7].x -= 500.0f * Math_SinS(rotY);
    this->unk_360[7].z -= 500.0f * Math_CosS(rotY);
    this->unk_360[6].x -= 500.0f * Math_SinS(rotY);
    this->unk_360[6].z -= 500.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[8], &this->unk_360[0]);
    this->unk_360[8].x -= 700.0f * Math_SinS(rotY);
    this->unk_360[8].z -= 700.0f * Math_CosS(rotY);
    Math_Vec3f_Copy(&this->unk_360[10], &this->unk_360[1]);
    this->unk_360[10].x -= 700.0f * Math_SinS(rotY);
    this->unk_360[10].z -= 700.0f * Math_CosS(rotY);
    this->unk_360[9].x -= 700.0f * Math_SinS(rotY);
    this->unk_360[9].z -= 700.0f * Math_CosS(rotY);
    this->unk_360[11] = this->unk_360[3];
    this->unk_360[11].x += 40.0f * Math_SinS(rotY + 0x4000);
    this->unk_360[11].z += 40.0f * Math_CosS(rotY + 0x4000);
    this->unk_360[12] = this->unk_360[3];
    this->unk_360[12].x += 40.0f * Math_SinS(rotY - 0x4000);
    this->unk_360[12].z += 40.0f * Math_CosS(rotY - 0x4000);
    this->unk_360[13] = this->unk_360[2];
    this->unk_360[14] = this->unk_360[4];
}

s32 ObjUm_InitBandits(ObjUm* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[this->pathIdx];
    s16 pad;
    Vec3s* spawnPoints;
    EnHorse* bandit1;
    EnHorse* bandit2;

    spawnPoints = Lib_SegmentedToVirtual(path->points);
    Audio_QueueSeqCmd(0x8003);

    bandit1 = (EnHorse*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, spawnPoints[0].x, spawnPoints[0].y,
                                    spawnPoints[0].z, 0, this->dyna.actor.shape.rot.y, 0, ENHORSE_PARAM(ENHORSE_2000, ENHORSE_19));
    this->bandit1 = bandit1;

    bandit1->unk_540 = bandit1->actor.world.pos;

    bandit1->unk_54C = 0xF;
    bandit1->unk_550 = 10;

    bandit1->unk_554 = this->pathIdx;
    bandit1->unk_568 = 0.0f;
    bandit1->unk_56C = 0.0f;
    bandit1->unk_558 = 0;
    bandit1->unk_55C = 40;
    bandit1->unk_560 = 40;

    bandit1->unk_570 = gZeroVec3f;
    bandit1->unk_57C = gZeroVec3f;

    bandit1->unk_588 = this->dyna.actor.shape.rot.y;
    bandit1->curRaceWaypoint = 1;

    bandit2 = (EnHorse*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, spawnPoints[1].x, spawnPoints[1].y,
                                    spawnPoints[1].z, 0, this->dyna.actor.shape.rot.y, 0, ENHORSE_PARAM(ENHORSE_2000, ENHORSE_20));
    this->bandit2 = bandit2;

    bandit2->unk_540 = bandit2->actor.world.pos;

    bandit2->unk_54C = 0xF;
    bandit2->unk_550 = 8;

    bandit2->unk_554 = this->pathIdx;
    bandit2->unk_568 = 0.0f;
    bandit2->unk_56C = 0.0f;
    bandit2->unk_55C = 40;
    bandit2->unk_560 = 40;

    bandit2->unk_57C = gZeroVec3f;

    bandit2->unk_588 = this->dyna.actor.shape.rot.y;
    bandit2->curRaceWaypoint = 2;

    this->potsLife[0] = 4;
    this->potsLife[1] = 4;
    this->potsLife[2] = 4;

    return 0;
}

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 unk_10;
} struct_80B7C254; // size = 0x14

struct_80B7C254 D_80B7C164[] = {
    { 2, 0, 0, 1.0f, 40 },     { 4, 1, 0, 1.0f, 40 },   { 3, 2, 0, 1.0f, 40 },    { 3, 4, 0, 1.0f, 40 },
    { 5, 3, 1, -1.0f, 30 },    { 7, 3, 1, 1.0f, 30 },   { 0, 13, 1, -1.0f, 60 }, { 1, 14, 1, 1.0f, 60 },
    { 13, 10, 0, 1.0f, 40 }, { 14, 8, 0, 1.0f, 40 }, { 8, 5, 0, 1.0f, 30 },    { 10, 7, 0, 1.0f, 30 },
};

// BanditAttack?
s32 func_80B781DC(ObjUm* this, EnHorse* arg2, EnHorse* arg3, GlobalContext* globalCtx) {
    s32 temp_v0;
    s32 phi_s3 = -1;
    s32 phi_s4 = 0;
    s32 phi_s2 = 0;
    f32 phi_f20 = 0.0f;
    s32 i;
    s32 mask;

    for (i = 0; i < ARRAY_COUNT(D_80B7C164); i++) {
        if (arg2->unk_550 == D_80B7C164[i].unk_00) {
            if (arg3->unk_550 != D_80B7C164[i].unk_04) {
                if (D_80B7C164[i].unk_00 != 3) {
                    if (D_80B7C164[i].unk_04 != 3 ||
                        ((mask = Player_GetMask(globalCtx)), PLAYER_MASK_CIRCUS_LEADER != mask)) {
                        phi_s3 = D_80B7C164[i].unk_04;
                        phi_s4 = D_80B7C164[i].unk_08;
                        phi_f20 = D_80B7C164[i].unk_0C;
                        phi_s2 = D_80B7C164[i].unk_10;
                    }
                } else if (((arg2->unk_54C != 5) || (D_80B7C164[i].unk_04 != 2)) &&
                           ((arg2->unk_54C != 7) || (D_80B7C164[i].unk_04 != 4))) {
                    phi_s3 = D_80B7C164[i].unk_04;
                    phi_s4 = D_80B7C164[i].unk_08;
                    phi_f20 = D_80B7C164[i].unk_0C;
                    if ((2.0f * Rand_ZeroOne()) < 1.0f) {
                        phi_f20 *= -1.0f;
                    }
                    phi_s2 = D_80B7C164[i].unk_10;
                }
                // Semicolon is required to match...
                ;
            }
        }
    }

    if (phi_s3 == -1) {
        return 0;
    }

    arg2->unk_540 = arg2->actor.world.pos;
    arg2->unk_54C = arg2->unk_550;
    arg2->unk_550 = phi_s3;
    arg2->unk_55C = phi_s2;
    arg2->unk_560 = phi_s2;
    arg2->unk_564 = phi_s4;
    arg2->unk_568 = phi_f20;

    if (phi_s3 == 3) {
        arg2->unk_558 = (s32)(Rand_ZeroOne() * 3.0f);
    dummy_label_437827:;
    } else {
        arg2->unk_558 = 0;
    }

    return 0;
}

// ObjUm_Bandit_UpdatePosition?
s32 func_80B783E0(ObjUm* this, GlobalContext* globalCtx, s32 banditIndex, EnHorse* bandit) {
    Path* sp6C = &globalCtx->setupPathList[this->pathIdx];
    s32 sp68;
    Vec3s* sp64;
    f32 phi_f12;
    s32 phi_v1_2;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 temp_a1;
    f32 sp3C;
    f32 phi_f14;

    sp68 = sp6C->count;
    sp64 = Lib_SegmentedToVirtual(sp6C->points);

    if (sp68 == 0) {
        return 0;
    }

    if (Math3D_Distance(&bandit->actor.world.pos, &this->dyna.actor.world.pos) < 800.0f) {
        if (banditIndex == 0) {
            this->flags |= OBJ_UM_FLAG_0200;
        } else {
            this->flags |= OBJ_UM_FLAG_0400;
        }
        bandit->unk_540 = bandit->actor.world.pos;
        bandit->unk_55C = 50;
        bandit->unk_560 = 50;
        bandit->unk_564 = 1;
    }

    Math_Vec3s_ToVec3f(&sp50, &sp64[bandit->curRaceWaypoint]);

    if (bandit->curRaceWaypoint == 0) {
        phi_f12 = (f32)(sp64[1].x - sp64[0].x);
        phi_f14 = (f32)(sp64[1].z - sp64[0].z);
    } else {
        if ((bandit->curRaceWaypoint + 1) == sp6C->count) {
            phi_f12 = (f32)(sp64[sp6C->count - 1].x - sp64[sp6C->count - 2].x);
            phi_f14 = (f32)(sp64[sp6C->count - 1].z - sp64[sp6C->count - 2].z);
        } else {
            phi_f12 = (f32)(sp64[bandit->curRaceWaypoint + 1].x - sp64[bandit->curRaceWaypoint - 1].x);
            phi_f14 = (f32)(sp64[bandit->curRaceWaypoint + 1].z - sp64[bandit->curRaceWaypoint - 1].z);
        }
    }

    temp_a1 = Math_Atan2S(phi_f12, phi_f14);

    func_8017B7F8(&sp50, (s16)temp_a1, &sp4C, &sp48, &sp44);
    if (((bandit->actor.world.pos.x * sp4C) + (sp48 * bandit->actor.world.pos.z) + sp44) > 0.0f) {
        bandit->curRaceWaypoint++;
        if (bandit->curRaceWaypoint >= sp68) {
            bandit->curRaceWaypoint = 0;
        }
        Math_Vec3s_ToVec3f(&sp50, &sp64[bandit->curRaceWaypoint]);
    }

    bandit->actor.world.rot.y = Math_Vec3f_Yaw(&bandit->actor.world.pos, &sp50);
    bandit->actor.speedXZ = 45.0f;

    sp3C = Math_CosS(bandit->actor.world.rot.x) * bandit->actor.speedXZ;
    bandit->actor.velocity.x = Math_SinS(bandit->actor.world.rot.y) * sp3C;
    bandit->actor.velocity.y = Math_SinS(bandit->actor.world.rot.x) * bandit->actor.speedXZ;
    bandit->actor.velocity.z = Math_CosS(bandit->actor.world.rot.y) * sp3C;

    bandit->unk_570.x = bandit->actor.world.pos.x + (bandit->actor.velocity.x * 0.5f) + bandit->actor.colChkInfo.displacement.x;
    bandit->unk_570.y = bandit->actor.world.pos.y + (bandit->actor.velocity.y * 0.5f) + bandit->actor.colChkInfo.displacement.y;
    bandit->unk_570.z = bandit->actor.world.pos.z + (bandit->actor.velocity.z * 0.5f) + bandit->actor.colChkInfo.displacement.z;

    phi_v1_2 = BINANG_SUB(bandit->actor.world.rot.y, bandit->actor.shape.rot.y);

    if (phi_v1_2 > 0x190) {
        phi_v1_2 = 0x190;
    } else if (phi_v1_2 < -0x190) {
        phi_v1_2 = -0x190;
    }

    bandit->actor.shape.rot.y = bandit->actor.shape.rot.y + phi_v1_2;
    return 0;
}

// ObjUm_Bandit_GetCloserAndAttack
s32 func_80B78764(ObjUm* this, GlobalContext* globalCtx, EnHorse* bandit1, EnHorse* bandit2) {
    s32 pad;
    Vec3f sp30;
    s16 phi_v1_5;

    bandit1->unk_55C--;
    if (bandit1->unk_55C <= 0) {
        bandit1->unk_55C = 0;

        if ((bandit1->unk_550 == 3) && !(this->flags & OBJ_UM_FLAG_MINIGAME_FINISHED)) {
            s32 potIndex = -1;

            if (this->potsLife[0] != 1) {
                potIndex = 0;
            }

            if (this->potsLife[1] != 1) {
                if ((potIndex == -1) || (potIndex == 0 && Rand_ZeroOne() < 0.3f)) {
                    potIndex = 1;
                }
            }

            if (this->potsLife[2] != 1) {
                if ((potIndex == -1) || (potIndex != -1 && Rand_ZeroOne() < 0.3f)) {
                    potIndex = 2;
                }
            }

            if (this->potsLife[potIndex] != 1) {
                this->wasPotHit[potIndex] = true;
                if (this->potsLife[potIndex] == 2) {
                    Audio_PlaySfxAtPos(&this->potPos[potIndex], NA_SE_EV_MILK_POT_BROKEN);
                } else {
                    Audio_PlaySfxAtPos(&this->potPos[potIndex], NA_SE_EV_MILK_POT_DAMAGE);
                }

                this->potsLife[potIndex]--;
                if (this->potsLife[potIndex] < 1) {
                    this->potsLife[potIndex] = 1;
                }
            }
        }

        func_80B781DC(this, bandit1, bandit2, globalCtx);
    }

    Math3D_Lerp(&bandit1->unk_540, &this->unk_360[bandit1->unk_550], 1.0f - ((f32)bandit1->unk_55C / bandit1->unk_560), &sp30);
    bandit1->unk_570 = sp30;
    bandit1->unk_588 = this->dyna.actor.shape.rot.y;

    if ((bandit1->unk_550 == 10) || ((bandit1->unk_550 == 8))) {
        phi_v1_5 = bandit1->unk_588;
    } else if (Math3D_Distance(&bandit1->actor.prevPos, &bandit1->actor.world.pos) < 10.0f) {
        phi_v1_5 = bandit1->unk_588;
    } else {
        phi_v1_5 = Math_Vec3f_Yaw(&bandit1->actor.prevPos, &bandit1->actor.world.pos);
    }

    if (1) {}

    phi_v1_5 -= bandit1->actor.shape.rot.y;
    if (phi_v1_5 > 0x190) {
        bandit1->actor.shape.rot.y += 0x190;
    } else if (phi_v1_5 < -0x190) {
        bandit1->actor.shape.rot.y += -0x190;
    } else {
        bandit1->actor.shape.rot.y += phi_v1_5;
    }

    return 0;
}

// ObjUm_UpdateBandits...
s32 func_80B78A54(ObjUm* this, GlobalContext* globalCtx, s32 arg2, EnHorse* arg3, EnHorse* arg4) {
    if (this->banditsCollisions[arg2].base.acFlags & AC_HIT) {
        if (arg3->unk_550 == 3) {
            s16 sp36 =
                Math_Vec3f_Yaw(&this->dyna.actor.world.pos, &arg3->actor.world.pos) - this->dyna.actor.shape.rot.y;

            this->banditsCollisions[arg2].base.acFlags &= ~AC_HIT;
            Audio_PlaySfxAtPos(&arg3->actor.projectedPos, NA_SE_EN_CUTBODY);
            arg3->unk_54C = 0xF;

            if (Math_SinS(sp36) > 0.0f) {
                arg3->unk_550 = arg4->unk_550 != 10 ? 10 : 8;
                arg3->unk_568 = -1.0f;
            } else {
                arg3->unk_550 = arg4->unk_550 != 8 ? 8 : 10;
                arg3->unk_568 = 1.0f;
            }

            arg3->unk_540 = arg3->actor.world.pos;
            arg3->unk_55C = 40;
            arg3->unk_560 = 40;
            arg3->unk_564 = 1;
            if (arg3->rider != NULL) {
                arg3->rider->actor.colorFilterTimer = 20;
                // TODO: remove cast?
                Actor_SetColorFilter(&arg3->rider->actor, 0x4000, 0xFF, 0, (s16) 0x28);
            }
        } else {
            if (arg3->rider != NULL) {
                arg3->rider->actor.colorFilterTimer = 20;
                // TODO: remove cast?
                Actor_SetColorFilter(&arg3->rider->actor, 0x4000, 0xFF, 0, (s16) 0x28);
            }
            Audio_PlaySfxAtPos(&arg3->actor.projectedPos, NA_SE_EN_CUTBODY);
        }
    }

    return 0;
}

// ObjUm_UpdateBanditLogic?
s32 func_80B78C18(ObjUm* this, GlobalContext* globalCtx) {
    EnHorse* bandit1 = this->bandit1;
    EnHorse* bandit2 = this->bandit2;

    if (!(this->flags & OBJ_UM_FLAG_0200)) {
        func_80B783E0(this, globalCtx, 0, bandit1);
    } else {
        func_80B78764(this, globalCtx, bandit1, bandit2);
    }

    if (!(this->flags & OBJ_UM_FLAG_0400)) {
        func_80B783E0(this, globalCtx, 1, bandit2);
    } else {
        func_80B78764(this, globalCtx, bandit2, bandit1);
    }

    func_80B78A54(this, globalCtx, 0, bandit1, bandit2);
    func_80B78A54(this, globalCtx, 1, bandit2, bandit1);
    return 0;
}

s32 ObjUm_UpdateBanditsCollisions(ObjUm* this, GlobalContext* globalCtx) {
    s32 pad[3];

    this->banditsCollisions[0].dim.pos.x = this->bandit1->actor.world.pos.x;
    this->banditsCollisions[0].dim.pos.y = this->bandit1->actor.world.pos.y + 70.0f;
    this->banditsCollisions[0].dim.pos.z = this->bandit1->actor.world.pos.z;

    this->banditsCollisions[1].dim.pos.x = this->bandit2->actor.world.pos.x;
    this->banditsCollisions[1].dim.pos.y = this->bandit2->actor.world.pos.y + 70.0f;
    this->banditsCollisions[1].dim.pos.z = this->bandit2->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->banditsCollisions[0].base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->banditsCollisions[1].base);
    return 0;
}

// ObjUm_UpdateBandits?
s32 func_80B78DF0(ObjUm* this, GlobalContext* globalCtx) {
    func_80B78C18(this, globalCtx);
    ObjUm_UpdateBanditsCollisions(this, globalCtx);
    return 0;
}

void ObjUm_SetupAction(ObjUm* this, ObjUmActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ObjUm_SetPlayerPosition(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->flags & OBJ_UM_FLAG_DRAWN_FLOOR) {
        player->actor.world.pos = this->unk_308;
        player->actor.prevPos = this->unk_308;
    }
}

void ObjUm_RotatePlayer(ObjUm* this, GlobalContext* globalCtx, s16 angle) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.shape.rot.y = player->actor.world.rot.y = player->currentYaw = this->dyna.actor.shape.rot.y + angle;
}

void func_80B78EBC(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.focus.rot.x = 0;
    player->actor.focus.rot.z = 0;
    player->actor.focus.rot.y = player->actor.shape.rot.y;

    player->unk_AAC.x = 0;
    player->unk_AAC.y = 0;
    player->unk_AAC.z = 0;

    player->unk_AB2.x = 0;
    player->unk_AB2.y = 0;
    player->unk_AB2.z = 0;

    player->currentYaw = player->actor.focus.rot.y;
}

void ObjUm_RotatePlayerView(ObjUm* this, GlobalContext* globalCtx, s16 angle) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.focus.rot.y += angle;
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjUm* this = THIS;
    s32 sp54 = true;
    s32 i;

    DynaPolyActor_Init(&this->dyna, 0);
    this->unk_350 = 0;

    this->unk_2C4 = this->dyna.actor.world.pos;
    this->unk_2DC = this->dyna.actor.world.pos;
    this->unk_308 = this->dyna.actor.world.pos;

    for (i = 0; i < 3; i++) {
        this->potsLife[i] = 5;
        this->wasPotHit[i] = false;
        this->potPos[i] = gZeroVec3f;
    }

    this->donkey = NULL;
    this->unk_354 = 0;
    this->unk_420 = 0;
    this->cartBedPos = this->dyna.actor.world.pos;

    this->unk_4CC = 0;
    this->mouthTexIndex = 0;
    this->flags = OBJ_UM_FLAG_0000;
    this->dyna.actor.gravity = -3.5f;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 50.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_um_Skel_011DF8, NULL, this->jointTable, this->morphTable, UM_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &object_um_Anim_012CC0);

    this->wheelRot = 0;
    ObjUm_StopAnim(this, globalCtx);

    this->type = OBJ_UM_PARSE_TYPE(thisx->params);
    this->initialPathIdx = OBJ_UM_PARSE_PATH_IDX(thisx->params);

    // if (!AliensDefeated)
    if (!(gSaveContext.save.weekEventReg[22] & 1)) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (this->type == OBJ_UM_TYPE_TERMINA_FIELD) {
        ObjUm_SetupAction(this, ObjUm_TerminaFieldIdle);
    } else if (this->type == OBJ_UM_TYPE_RANCH) {
        this->pathIdx = this->initialPathIdx;
        if (gSaveContext.save.weekEventReg[31] & 0x80) {
            // In cutscene

            sp54 = false;
            this->flags |= OBJ_UM_FLAG_0100;
            ObjUm_SetupAction(this, func_80B7A144);
            func_800FE484();
        } else {
            // Waiting for player

            if ((gSaveContext.save.weekEventReg[34] & 0x80) || gSaveContext.save.time >= CLOCK_TIME(19, 0) ||
                gSaveContext.save.time <= CLOCK_TIME(6, 0) || (gSaveContext.save.weekEventReg[52] & 1) ||
                (gSaveContext.save.weekEventReg[52] & 2)) {
                Actor_MarkForDeath(&this->dyna.actor);
                return;
            }

            this->dyna.actor.targetMode = 6;
            this->unk_2B4 = 0;
            ObjUm_SetupAction(this, ObjUm_RanchWait);
        }
    } else if (this->type == OBJ_UM_TYPE_PRE_MILK_RUN) {
        if (!(gSaveContext.save.weekEventReg[31] & 0x80) || (gSaveContext.save.weekEventReg[52] & 1)) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }

        if (!(gSaveContext.save.weekEventReg[52] & 2)) {
            this->pathIdx = this->initialPathIdx;
            sp54 = false;
            func_800FE484();
            ObjUm_SetupAction(this, ObjUm_PreMilkRunStartCs);
            this->unk_354 = 0;
            ObjUm_RotatePlayer(this, globalCtx, 0);
        }
    } else if (this->type == OBJ_UM_TYPE_MILK_RUN_MINIGAME) {
        if (!(gSaveContext.save.weekEventReg[31] & 0x80)) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }

        this->pathIdx = this->initialPathIdx;
        sp54 = false;
        func_800FE484();
        ObjUm_SetupAction(this, ObjUm_StartCs);
        this->unk_354 = 0;
        ObjUm_RotatePlayer(this, globalCtx, 0);
    } else if (this->type == OBJ_UM_TYPE_POST_MILK_RUN) {
        if (!(gSaveContext.save.weekEventReg[52] & 1) || (gSaveContext.save.weekEventReg[59] & 2)) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }

        this->pathIdx = this->initialPathIdx;
        sp54 = false;
        func_800FE484();
        ObjUm_SetupAction(this, ObjUm_PostMilkRunStartCs);
        this->unk_354 = 0;
        ObjUm_RotatePlayer(this, globalCtx, 0);
        func_801A3098(0x19);
    } else {
        this->type = OBJ_UM_TYPE_TERMINA_FIELD;
        ObjUm_SetupAction(this, ObjUm_TerminaFieldIdle);
    }

    this->unk_2F8 = this->unk_2FE = gZeroVec3s;

    if (sp54) {
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_um_Colheader_007E20);
    } else {
        DynaPolyActor_Init(&this->dyna, 3);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_um_Colheader_007F50);
    }

    if (this->dyna.bgId == 0x32) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    func_800C636C(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);

    this->donkey = (EnHorse*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HORSE, this->dyna.actor.world.pos.x,
                                         this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0,
                                         this->dyna.actor.shape.rot.y, 0, ENHORSE_PARAM(ENHORSE_8000, ENHORSE_18));

    if (this->donkey == NULL) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    Collider_InitAndSetCylinder(globalCtx, &this->banditsCollisions[0], &this->dyna.actor, &sCylinderInit);
    Collider_InitAndSetCylinder(globalCtx, &this->banditsCollisions[1], &this->dyna.actor, &sCylinderInit);

    return;
}

void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjUm* this = THIS;
    s32 i;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);

    for (i = 0; i < ARRAY_COUNT(this->potPos); i++) {
        Audio_StopSfxByPos(&this->potPos[i]);
    }

    Collider_DestroyCylinder(globalCtx, &this->banditsCollisions[0]);
    Collider_DestroyCylinder(globalCtx, &this->banditsCollisions[1]);
}

// ObjUm_MarkMyDonkeyAndMyselfForDeath, ObjUm_TerminateMe, ObjUmn't, ObjUm_Asinucide
void func_80B79524(ObjUm* this) {
    Actor_MarkForDeath(&this->dyna.actor);
    if (this->donkey != NULL) {
        Actor_MarkForDeath(&this->donkey->actor);
    }
}

void func_80B79560(GlobalContext* globalCtx, ObjUm* this, s32 arg2, u16 textId) {
    // "Thanks, I rely on you"
    if (textId == 0x33BF) {
        ObjUm_SetupAction(this, ObjUm_StartCs);
    }
}

s32 func_80B795A0(GlobalContext* globalCtx, ObjUm* this, s32 arg2) {
    s32 pad[2];
    s32 phi_v1 = true;
    u16 textId = this->dyna.actor.textId;
    Player* player;

    switch (textId) {
        // "I'll go to town"
        case 0x33B4:
        // "Want a ride?"
        case 0x33CF:
            gSaveContext.save.weekEventReg[31] |= 0x40;
            if (globalCtx->msgCtx.choiceIndex == 0) {
                player = GET_PLAYER(globalCtx);
                func_8019F208();
                gSaveContext.save.weekEventReg[31] |= 0x80;
                globalCtx->nextEntranceIndex = 0x64B0;
                if (player->stateFlags1 & 0x800000) {
                    D_801BDAA0 = 1;
                }
                globalCtx->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                globalCtx->sceneLoadFlag = 0x14;
                phi_v1 = true;
            } else {
                func_800E8EA0(globalCtx, &this->dyna.actor, 0x33B5);
                func_8019F230();
                func_80151BB4(globalCtx, 6U);
                phi_v1 = false;
            }
            break;

        // "I'll go as fast as I can!"
        case 0x33BB:
            func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BC);
            phi_v1 = false;
            break;

        // "Chase pursuers with your arrows."
        case 0x33BC:
            func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BD);
            phi_v1 = false;
            break;

        // "Understand?"
        case 0x33BD:
            if (globalCtx->msgCtx.choiceIndex == 0) {
                func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BE);
                func_8019F230();
            } else {
                func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BF);
                func_8019F208();
            }
            phi_v1 = false;
            break;

        // "I'll tell you again!"
        case 0x33BE:
            func_800E8EA0(globalCtx, &this->dyna.actor, 0x33BC);
            phi_v1 = false;
            break;
    }

    return phi_v1;
}

s32 func_80B79734(GlobalContext* globalCtx, ObjUm* this, s32 arg2) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s32 ret = false;

    switch (Message_GetState(msgCtx)) {
        case 2:
            // TODO: test
            func_80B79560(globalCtx, this, arg2, this->dyna.actor.textId);
            return true;

        case 4:
        case 5:
            if (Message_ShouldAdvance(globalCtx) && func_80B795A0(globalCtx, this, arg2)) {
                msgCtx->msgMode = 0x43;
                ret = true;
            }
            break;
    }
    return ret;
}

u16 ObjUm_RanchGetDialogue(GlobalContext* globalCtx, ObjUm* this, s32 arg2) {
    u16 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
        if (gSaveContext.save.weekEventReg[31] & 0x40) {
            // "Want a ride?"
            textId = 0x33CF;
        } else {
            // "I'll deliver milk"
            textId = 0x33B4;
        }
    } else {
        textId = 0x33B7;
    }

    if (textId == 0) {
        textId = 1;
    }
    return textId;
}

s32 func_80B7984C(GlobalContext* globalCtx, ObjUm* this, s32 arg2, s32* arg3) {
    s16 temp_v0_2;
    s16 phi_v1;

    if (*arg3 == 4) {
        return 0;
    }
    if (*arg3 == 2) {
        Message_StartTextbox(globalCtx, this->dyna.actor.textId, &this->dyna.actor);
        *arg3 = 1;
        return 0;
    }
    if (*arg3 == 3) {
        func_80151938(globalCtx, this->dyna.actor.textId);
        *arg3 = 1;
        return 0;
    }

    if (Actor_ProcessTalkRequest(&this->dyna.actor, &globalCtx->state)) {
        *arg3 = 1;
        return 1;
    }

    if (*arg3 == 1) {
        if (func_80B79734(globalCtx, this, arg2)) {
            *arg3 = 0;
        }
        return 0;
    }

    phi_v1 = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;
    temp_v0_2 = ABS_ALT(phi_v1);

    if (temp_v0_2 >= 20000) {
        return 0;
    }

    if ((this->dyna.actor.xyzDistToPlayerSq > SQ(100.0f)) && !this->dyna.actor.isTargeted) {
        return 0;
    }

    if (this->dyna.actor.xyzDistToPlayerSq <= SQ(50.0f)) {
        if (func_800B8614(&this->dyna.actor, globalCtx, 50.0f)) {
            this->dyna.actor.textId = ObjUm_RanchGetDialogue(globalCtx, this, arg2);
        }
    } else if (func_800B863C(&this->dyna.actor, globalCtx)) {
        this->dyna.actor.textId = ObjUm_RanchGetDialogue(globalCtx, this, arg2);
    }

    return 0;
}

s32 func_80B79A24(s32 arg0) {
    if ((arg0 == 1) || (arg0 == 2) || (arg0 == 3)) {
        return true;
    }

    return false;
}

// 0x80b79a30
void ObjUm_RanchWait(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->dyna.actor.flags |= ACTOR_FLAG_1;
    SkelAnime_Update(&this->skelAnime);
    ObjUm_UpdateAnim(this, globalCtx, 2);
    this->flags |= OBJ_UM_FLAG_WAITING;
    if (gSaveContext.save.time > CLOCK_TIME(18, 0) && gSaveContext.save.time <= CLOCK_TIME(19, 0)) {
        if (!(player->stateFlags1 & 0x800000)) {
            func_80B7984C(globalCtx, this, 0, &this->unk_2B4);
        }
    } else if (!func_80B79A24(this->unk_2B4) && gSaveContext.save.time > CLOCK_TIME(19, 0)) {
        gSaveContext.save.weekEventReg[34] |= 0x80;
        ObjUm_SetupAction(this, ObjUm_RanchWaitPathFinished);
    }

    switch (globalCtx->msgCtx.currentTextId) {
        default:
            this->unk_4CC = 0;
            this->mouthTexIndex = 0;
            break;

        // "I'm worried about my sister"
        case 0x33B7:
        // "I'll deliver milk"
        case 0x33B4:
            this->unk_4CC = 0;
            this->mouthTexIndex = 1;
            break;

        // "I'll leave at 7"
        case 0x33B5:
            this->unk_4CC = 3;
            this->mouthTexIndex = 1;
            break;
    }
}

typedef enum {
    /* 0 */ OBJUM_PATH_STATE_0,
    /* 1 */ OBJUM_PATH_STATE_1,
    /* 2 */ OBJUM_PATH_STATE_FINISH,
    /* 3 */ OBJUM_PATH_STATE_3,
    /* 4 */ OBJUM_PATH_STATE_4,
} ObjUmPathState;

ObjUmPathState ObjUm_UpdatePath(ObjUm* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[this->pathIdx];
    s32 pathCount;
    Vec3s* pathPoints;
    f32 phi_f12;
    f32 phi_f14;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 aux;
    ObjUmPathState sp3C;
    s16 phi_a2;

    pathCount = path->count;
    pathPoints = Lib_SegmentedToVirtual(path->points);
    sp3C = OBJUM_PATH_STATE_0;

    if (pathCount == 0) {
        return 0;
    }

    Math_Vec3s_ToVec3f(&sp50, &pathPoints[this->pointIdx]);

    if (this->pointIdx == 0) {
        phi_f12 = pathPoints[1].x - pathPoints[0].x;
        phi_f14 = pathPoints[1].z - pathPoints[0].z;
    } else if ((this->pointIdx + 1) == path->count) {
        phi_f12 = pathPoints[path->count - 1].x - pathPoints[path->count - 2].x;
        phi_f14 = pathPoints[path->count - 1].z - pathPoints[path->count - 2].z;
    } else {
        phi_f12 = pathPoints[this->pointIdx + 1].x - pathPoints[this->pointIdx - 1].x;
        phi_f14 = pathPoints[this->pointIdx + 1].z - pathPoints[this->pointIdx - 1].z;
    }

    aux = Math_Atan2S(phi_f12, phi_f14);

    func_8017B7F8(&sp50, aux, &sp4C, &sp48, &sp44);
    if (((this->dyna.actor.world.pos.x * sp4C) + (sp48 * this->dyna.actor.world.pos.z) + sp44) > 0.0f) {
        this->pointIdx++;

        if (this->pointIdx >= (pathCount - 7)) {
            sp3C = OBJUM_PATH_STATE_3;
        }
        if (this->pointIdx >= (pathCount - 3)) {
            sp3C = OBJUM_PATH_STATE_1;
        }
        if (this->pointIdx >= (pathCount - 2)) {
            sp3C = OBJUM_PATH_STATE_4;
        }
        if (this->pointIdx >= pathCount) {
            this->pointIdx = 0;
            sp3C = OBJUM_PATH_STATE_FINISH;
        }

        Math_Vec3s_ToVec3f(&sp50, &pathPoints[this->pointIdx]);
    }

    if (this->donkey != NULL) {
        this->dyna.actor.world.rot.y = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, &sp50);
        func_800F415C(&this->donkey->actor, &sp50, 0x190);

        if (1) {}

        phi_a2 = this->donkey->actor.shape.rot.y - this->dyna.actor.shape.rot.y;
        if (fabsf(phi_a2) < 2730.0f) {
            if (fabsf(phi_a2) < 100.0f) {
                this->dyna.actor.shape.rot.y = this->donkey->actor.shape.rot.y;
            } else if (phi_a2 > 0) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y + 0x64;
                phi_a2 = 0x64;
            } else if (phi_a2 < 0) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y - 0x64;
                phi_a2 = -0x64;
            }
        } else if (phi_a2 > 0) {
            this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y + 0x190;
            phi_a2 = 0x190;
        } else {
            if (phi_a2 < 0) {
                this->dyna.actor.shape.rot.y = this->dyna.actor.shape.rot.y - 0x190;
                phi_a2 = -0x190;
            }
        }

        if (this->flags & (OBJ_UM_FLAG_0010 | OBJ_UM_FLAG_0004)) {
            ObjUm_RotatePlayerView(this, globalCtx, phi_a2);
        }
    }

    if (this->unk_304 == 0) {
        this->dyna.actor.speedXZ = 4.0f;
    } else if (this->unk_304 == 1) {
        this->dyna.actor.speedXZ = 8.0f;
    }

    return sp3C;
}

void ObjUm_RanchWaitPathFinished(ObjUm* this, GlobalContext* globalCtx) {
    this->wheelRot += 1000;
    this->flags &= ~OBJ_UM_FLAG_WAITING;
    ObjUm_UpdateAnim(this, globalCtx, 0);

    switch (ObjUm_UpdatePath(this, globalCtx)) {
        case OBJUM_PATH_STATE_1:
        case OBJUM_PATH_STATE_FINISH:
            if (gSaveContext.save.weekEventReg[31] & 0x80) {
                ActorCutscene_Stop(this->dyna.actor.cutscene);
                globalCtx->nextEntranceIndex = 0x3E50;
                globalCtx->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                globalCtx->sceneLoadFlag = 0x14;
            } else {
                func_80B79524(this);
            }
            break;

        default:
            Actor_MoveWithGravity(&this->dyna.actor);
            break;
    }
}

void ObjUm_RanchStartCs(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_UpdateAnim(this, globalCtx, 2);

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->lastTime = gSaveContext.save.time;
        ObjUm_SetupAction(this, func_80B7A0E0);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80B7A070(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_RanchWaitPathFinished(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0);

    switch (globalCtx->msgCtx.currentTextId) {
        case 0x33B6:
            this->unk_4CC = 1;
            this->mouthTexIndex = 1;
            break;

        default:
            this->unk_4CC = 0;
            this->mouthTexIndex = 0;
            break;
    }
}

void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_UpdateAnim(this, globalCtx, 2);
    if (gSaveContext.save.time != this->lastTime) {
        ObjUm_UpdateAnim(this, globalCtx, 0);
        ObjUm_SetupAction(this, func_80B7A070);
    }
}

void func_80B7A144(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    ObjUm_SetPlayerPosition(this, globalCtx);
    this->flags |= OBJ_UM_FLAG_0100;
    this->flags |= OBJ_UM_FLAG_0004;
    player->stateFlags1 |= 0x20;
    ObjUm_UpdateAnim(this, globalCtx, 2);
    ObjUm_SetupAction(this, ObjUm_RanchStartCs);
}

void ObjUm_PreMilkRunDialogueHandler(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_SetPlayerPosition(this, globalCtx);
    this->flags |= OBJ_UM_FLAG_0004;

    switch (globalCtx->msgCtx.currentTextId) {
        case 0x33B8:
            this->unk_4CC = 0;
            this->mouthTexIndex = 3;
            break;

        case 0x33B9:
            this->unk_4CC = 2;
            this->mouthTexIndex = 0;
            break;

        default:
            this->flags &= ~OBJ_UM_FLAG_0800;
            this->unk_4CC = 0;
            this->mouthTexIndex = 0;
            break;
    }
}

void func_80B7A240(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_UpdateAnim(this, globalCtx, 2);
    if (gSaveContext.save.time != this->lastTime) {
        ObjUm_SetupAction(this, func_80B7A2AC);
    }

    this->lastTime = gSaveContext.save.time;
    ObjUm_PreMilkRunDialogueHandler(this, globalCtx);
}

void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx) {
    this->wheelRot += 1000;
    ObjUm_UpdateAnim(this, globalCtx, 0);

    switch (ObjUm_UpdatePath(this, globalCtx)) {
        case OBJUM_PATH_STATE_1:
        case OBJUM_PATH_STATE_FINISH:
            globalCtx->nextEntranceIndex = 0xCE40;
            globalCtx->unk_1887F = 0x40;
            gSaveContext.nextTransition = 3;
            globalCtx->sceneLoadFlag = 0x14;
            break;

        default:
            if (gSaveContext.save.time == this->lastTime) {
                ObjUm_SetupAction(this, func_80B7A240);
            }

            this->lastTime = gSaveContext.save.time;
            Actor_MoveWithGravity(&this->dyna.actor);
            ObjUm_PreMilkRunDialogueHandler(this, globalCtx);
            break;
    }
}

void func_80B7A394(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_SetPlayerPosition(this, globalCtx);
    this->flags |= OBJ_UM_FLAG_0004;
    if (gSaveContext.save.time != this->lastTime) {
        ObjUm_UpdateAnim(this, globalCtx, 0);
        ObjUm_SetupAction(this, func_80B7A2AC);
    }
}

void ObjUm_PreMilkRunStartCs(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    ObjUm_SetPlayerPosition(this, globalCtx);
    this->flags |= OBJ_UM_FLAG_0004;
    player->stateFlags1 |= 0x20;
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->lastTime = gSaveContext.save.time;
        ObjUm_SetupAction(this, func_80B7A394);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjUm_RunMinigame(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0x7FFF);
    this->wheelRot += 2000;
    this->flags |= OBJ_UM_FLAG_0010;
    ObjUm_UpdateAnim(this, globalCtx, 1);

    switch (ObjUm_UpdatePath(this, globalCtx)) {
        case OBJUM_PATH_STATE_1:
        case OBJUM_PATH_STATE_FINISH:
            gSaveContext.seqIndex = 0xFF;
            gSaveContext.save.weekEventReg[31] &= (u8)~0x80;
            gSaveContext.nightSeqIndex = 0xFF;

            if (!(gSaveContext.save.weekEventReg[52] & 1) && !(gSaveContext.save.weekEventReg[52] & 2)) {
                if (this->arePotsBroken == false) {
                    globalCtx->nextEntranceIndex = 0x3E60;
                    globalCtx->unk_1887F = 0x40;
                    gSaveContext.nextTransition = 3;
                    globalCtx->sceneLoadFlag = 0x14;
                    gSaveContext.save.weekEventReg[52] |= 1;
                    gSaveContext.save.weekEventReg[52] &= (u8)~2;
                } else {
                    globalCtx->nextEntranceIndex = 0x6480;
                    globalCtx->unk_1887F = 0x40;
                    gSaveContext.nextTransition = 3;
                    globalCtx->sceneLoadFlag = 0x14;
                    gSaveContext.save.weekEventReg[52] |= 2;
                    gSaveContext.save.weekEventReg[52] &= (u8)~1;
                }
            }
            break;

        default:
            Actor_MoveWithGravity(&this->dyna.actor);
            func_80B78DF0(this, globalCtx);
            break;
    }
}

void func_80B7A614(ObjUm* this, GlobalContext* globalCtx) {
    s32 pad;

    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0x7FFF);
    this->wheelRot += 2000;
    this->flags |= OBJ_UM_FLAG_0010;
    this->flags |= OBJ_UM_FLAG_PLAYING_MINIGAME;
    ObjUm_UpdateAnim(this, globalCtx, 1);

    if (ObjUm_UpdatePath(this, globalCtx) == OBJUM_PATH_STATE_3 && this->unk_4DC == 0) {
        this->unk_4DC = 1;
    } else if (this->unk_4DC > 0) {
        if (this->unk_4DC == 1) {
            s32 i;

            this->arePotsBroken = true;

            for (i = 0; i < ARRAY_COUNT(this->potsLife); i++) {
                if (this->potsLife[i] != 1) {
                    this->arePotsBroken = false;
                    break;
                }
            }

            this->flags |= OBJ_UM_FLAG_MINIGAME_FINISHED;

        dummy_label:;
        }

        this->unk_4DC++;
    }

    if (this->flags & OBJ_UM_FLAG_MINIGAME_FINISHED) {
        s32 sp20 = ActorCutscene_GetAdditionalCutscene(this->dyna.actor.cutscene);

        if (this->arePotsBroken) {
            sp20 = ActorCutscene_GetAdditionalCutscene(sp20);
        }
        if (ActorCutscene_GetCanPlayNext(sp20)) {
            ActorCutscene_StartAndSetUnkLinkFields(sp20, &this->dyna.actor);
            ObjUm_SetupAction(this, ObjUm_RunMinigame);
            this->flags &= ~OBJ_UM_FLAG_PLAYING_MINIGAME;
        } else {
            ActorCutscene_SetIntentToPlay(sp20);
        }
    }

    Actor_MoveWithGravity(&this->dyna.actor);
    func_80B78DF0(this, globalCtx);
}

void func_80B7A7AC(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->unk_4DC = 0;
    this->arePotsBroken = false;
    player->stateFlags1 &= ~0x20;
    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0x7FFF);
    func_80B78EBC(this, globalCtx);
    this->flags |= OBJ_UM_FLAG_0010;
    func_80B78DF0(this, globalCtx);
    this->flags |= 4;
    ObjUm_UpdateAnim(this, globalCtx, 1);
    ObjUm_SetupAction(this, func_80B7A614);
}

void func_80B7A860(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0);
    this->flags |= OBJ_UM_FLAG_0004;

    if (globalCtx->csCtx.frames == 449) {
        ObjUm_InitBandits(this, globalCtx);
    } else if (globalCtx->csCtx.frames >= 450) {
        func_80B78DF0(this, globalCtx);
    }

    if (globalCtx->csCtx.state == 0) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        ObjUm_SetupAction(this, func_80B7A7AC);
    }

    switch (globalCtx->msgCtx.currentTextId) {
        case 0x33BA:
            this->unk_4CC = 2;
            this->mouthTexIndex = 3;
            break;

        // "We'll go through here as fast as we can"
        case 0x33BB:
            if (IS_ZERO(this->skelAnime.curFrame) && !(this->flags & OBJ_UM_FLAG_1000)) {
                this->flags |= OBJ_UM_FLAG_1000;
                this->unk_4CC = 4;
                this->mouthTexIndex = 0;
            } else if (IS_ZERO(this->skelAnime.morphWeight)) {
                this->unk_4CC = 2;
                this->mouthTexIndex = 2;
            } else {
                this->unk_4CC = 5;
                this->mouthTexIndex = 0;
            }

            this->flags |= OBJ_UM_FLAG_0800;
            break;

        // "Chase pursuers with your arrows"
        case 0x33BC:
            if (IS_ZERO(this->skelAnime.curFrame) && !(this->flags & OBJ_UM_FLAG_1000)) {
                this->flags |= OBJ_UM_FLAG_1000;
                this->unk_4CC = 4;
                this->mouthTexIndex = 0;
            } else if (IS_ZERO(this->skelAnime.morphWeight)) {
                this->unk_4CC = 2;
                this->mouthTexIndex = 2;
            } else {
                this->unk_4CC = 5;
                this->mouthTexIndex = 0;
            }
            this->flags |= OBJ_UM_FLAG_0800;
            break;

        // "Understand?"
        case 0x33BD:
            if (IS_ZERO(this->skelAnime.curFrame) && !(this->flags & OBJ_UM_FLAG_1000)) {
                this->flags |= OBJ_UM_FLAG_1000;
                this->unk_4CC = 4;
                this->mouthTexIndex = 0;
            } else if (IS_ZERO(this->skelAnime.morphWeight)) {
                this->unk_4CC = 2;
            } else {
                this->unk_4CC = 5;
            }
            this->mouthTexIndex = 0;
            this->unk_4D8 = 0;
            this->flags |= OBJ_UM_FLAG_0800;
            break;

        case 0x33BE:
            this->flags |= OBJ_UM_FLAG_0800;
            this->unk_4CC = 2;
            this->mouthTexIndex = 3;
            break;

        case 0x33BF:
            this->unk_4D8++;
            if (IS_ZERO(this->skelAnime.morphWeight) && this->unk_4D8 >= 6) {
                this->unk_4CC = 0;
                this->mouthTexIndex = 0;
            } else {
                this->unk_4CC = 2;
                this->mouthTexIndex = 2;
            }
            this->flags &= ~OBJ_UM_FLAG_0800;
            break;

        default:
            this->unk_4CC = 0;
            this->mouthTexIndex = 0;
            break;
    }
}

void func_80B7AB78(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_UpdateAnim(this, globalCtx, 2);
    if (gSaveContext.save.time != this->lastTime) {
        ObjUm_SetupAction(this, func_80B7ABE4);
    }

    this->lastTime = gSaveContext.save.time;
    func_80B7A860(this, globalCtx);
}

void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx) {
    this->wheelRot += 1000;

    ObjUm_UpdateAnim(this, globalCtx, 0);
    switch (ObjUm_UpdatePath(this, globalCtx)) {
        case OBJUM_PATH_STATE_FINISH:
            func_80B79524(this);
            break;

        default:
            if (gSaveContext.save.time == this->lastTime) {
                ObjUm_SetupAction(this, func_80B7AB78);
            }

            this->lastTime = gSaveContext.save.time;
            Actor_MoveWithGravity(&this->dyna.actor);
            func_80B7A860(this, globalCtx);
            break;
    }
}

void ObjUm_StartCs(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->stateFlags1 |= 0x20;
    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0);
    this->flags |= OBJ_UM_FLAG_0004;

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->lastTime = gSaveContext.save.time;
        ObjUm_SetupAction(this, func_80B7ABE4);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjUm_PostMilkRunWaitPathFinished(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->stateFlags1 |= 0x20;
    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0);
    this->flags |= OBJ_UM_FLAG_0004;
    this->wheelRot += 1000;
    ObjUm_UpdateAnim(this, globalCtx, 0);

    if ((ObjUm_UpdatePath(this, globalCtx) == OBJUM_PATH_STATE_4) && !(gSaveContext.save.weekEventReg[59] & 2)) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        Audio_SetCutsceneFlag(0);
        gSaveContext.save.weekEventReg[59] |= 2;
        gSaveContext.nextCutsceneIndex = 0xFFF3;
        globalCtx->nextEntranceIndex = 0x5400;
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 3;
        globalCtx->sceneLoadFlag = 0x14;
        // A bit more than an hour
        gSaveContext.save.time += 0xAAC;
    }
    Actor_MoveWithGravity(&this->dyna.actor);
}

void ObjUm_PostMilkRunStartCs(ObjUm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->stateFlags1 |= 0x20;
    ObjUm_SetPlayerPosition(this, globalCtx);
    ObjUm_RotatePlayer(this, globalCtx, 0);
    this->flags |= OBJ_UM_FLAG_0004;
    ObjUm_UpdateAnim(this, globalCtx, 2);

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        ObjUm_SetupAction(this, ObjUm_PostMilkRunWaitPathFinished);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjUm_TerminaFieldIdle(ObjUm* this, GlobalContext* globalCtx) {
    ObjUm_UpdateAnim(this, globalCtx, 2);
    SkelAnime_Update(&this->skelAnime);
}

void func_80B7AF30(ObjUm* this, GlobalContext* globalCtx) {
    if (!(this->flags & OBJ_UM_FLAG_0001)) {
        this->dyna.actor.shape.rot.x = 0;
        this->dyna.actor.shape.rot.z = 0;
    } else {
        CollisionPoly* sp44;
        s32 pad;
        s32 pad2;
        Vec3f sp30;

        this->flags &= ~OBJ_UM_FLAG_0001;

        if (1) {}

        this->unk_2D0 = this->unk_2C4;
        this->unk_2E8 = this->unk_2DC;

        this->unk_2D0.y = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp44, &this->unk_2C4);
        if (this->unk_2D0.y == BGCHECK_Y_MIN) {
            this->unk_2D0.y = this->dyna.actor.floorHeight;
        }

        if (1) {}

        this->unk_2E8.y = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &sp44, &this->unk_2DC);
        if (this->unk_2E8.y == BGCHECK_Y_MIN) {
            this->unk_2E8.y = this->dyna.actor.floorHeight;
        }

        sp30.x = (this->unk_2D0.x + this->unk_2E8.x) * 0.5f;
        sp30.y = (this->unk_2D0.y + this->unk_2E8.y) * 0.5f;
        sp30.z = (this->unk_2D0.z + this->unk_2E8.z) * 0.5f;

        this->dyna.actor.shape.rot.x =
            (s16)Math_Atan2S(sp30.y - this->dyna.actor.world.pos.y, sqrtf(SQ(sp30.x - this->dyna.actor.world.pos.x) +
                                                                          SQ(sp30.z - this->dyna.actor.world.pos.z)));
        this->dyna.actor.shape.rot.z = (s16)-Math_Atan2S(
            sp30.y - this->unk_2D0.y, sqrtf(SQ(sp30.x - this->unk_2D0.x) + SQ(sp30.z - this->unk_2D0.z)));
        if (this->flags & OBJ_UM_FLAG_MOVING) {
            this->dyna.actor.shape.rot.x += BINANG_SUB((Rand_ZeroOne() * 100.0f), 50.0f);
            this->dyna.actor.shape.rot.z += BINANG_SUB((Rand_ZeroOne() * 100.0f), 50.0f);
        }
    }
}

void ObjUm_StopAnim(ObjUm* this, GlobalContext* globalCtx) {
    Animation_PlayOnce(&this->skelAnime, &object_um_Anim_012CC0);
    this->unk_304 = 0;
}

typedef struct {
    /* 0x00 */ AnimationHeader* anim;
    /* 0x04 */ s32 animMoves;
} struct_80B7C25C; // size = 0x08

struct_80B7C25C D_80B7C25C[] = {
    { &object_um_Anim_012CC0, true }, { &object_um_Anim_01213C, true }, { &object_um_Anim_019E10, false }, { NULL, false }, { &object_um_Anim_0126C4, false }
};

void ObjUm_UpdateAnim(ObjUm* this, GlobalContext* globalCtx, s32 index) {
    s32 changeAnim;
    s32 temp;
    s32 indexTemp = index;
    f32 animPlaybackSpeed = 0.0f;

    if (D_80B7C25C[index].animMoves) {
        this->flags |= OBJ_UM_FLAG_MOVING;
    } else {
        this->flags &= ~OBJ_UM_FLAG_MOVING;
    }

    if (index == 0) {
        animPlaybackSpeed = this->dyna.actor.speedXZ * 0.25f;
    } else if (index == 1) {
        animPlaybackSpeed = this->dyna.actor.speedXZ * 0.2f;
    } else if (index == 2) {
        animPlaybackSpeed = 1.0f;
    }
    this->skelAnime.playSpeed = animPlaybackSpeed;

    if (this->flags & OBJ_UM_FLAG_0800) {
        this->skelAnime.playSpeed = 1.0f;
        index = -1;
    }

    changeAnim = index != this->unk_304;
    if (SkelAnime_Update(&this->skelAnime) || changeAnim) {
        this->unk_304 = index;

        if (index != -1) {
            if (this->donkey != NULL) {
                this->donkey->unk_538 = index;
            }

            if (changeAnim) {
                Animation_MorphToPlayOnce(&this->skelAnime, D_80B7C25C[index].anim, -3.0f);
            } else {
                Animation_PlayOnce(&this->skelAnime, D_80B7C25C[index].anim);
            }
        } else {
            EnHorse* donkey = this->donkey;

            if (donkey != NULL) {
                donkey->unk_538 = indexTemp;
            }

            if (changeAnim) {
                temp = 3 - index;
                Animation_MorphToPlayOnce(&this->skelAnime, D_80B7C25C[temp].anim, -10.0f);
            } else {
                temp = 3 - index;
                Animation_PlayOnce(&this->skelAnime, D_80B7C25C[temp].anim);
            }
        }
    }

    if (this->wheelRot / 0x199A != this->unk_420) {
        this->unk_420 = this->wheelRot / 0x199A;
        // Required to match
        if (!&D_80B7C25C[0]) {}
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_CART_WHEEL);
    }
}

void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjUm* this = THIS;

    this->actionFunc(this, globalCtx);
    this->unk_350 += 1;
    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 0x1C);

    if (this->donkey != NULL) {
        this->donkey->actor.world.pos.x = this->dyna.actor.world.pos.x;
        this->donkey->actor.world.pos.y = this->dyna.actor.floorHeight;
        this->donkey->actor.world.pos.z = this->dyna.actor.world.pos.z;
    }

    if (this->flags & OBJ_UM_FLAG_0010) {
        func_80123F2C(globalCtx, 0x63);
        this->flags &= ~OBJ_UM_FLAG_0010;
    } else if (this->flags & OBJ_UM_FLAG_0004) {
        func_80123F2C(globalCtx, -3);
        this->flags &= ~OBJ_UM_FLAG_0004;
    }

    if (this->flags & OBJ_UM_FLAG_0100) {
        this->flags &= ~OBJ_UM_FLAG_0100;
        ObjUm_RotatePlayer(this, globalCtx, 0);
        func_80B78EBC(this, globalCtx);
    }

    func_80B7AF30(this, globalCtx);
    switch (this->unk_4CC) {
        case 0:
            switch (this->eyeTexIndex) {
                case 0:
                    if (Rand_ZeroOne() < 0.025f) {
                        this->eyeTexIndex = 1;
                    }
                    break;

                case 1:
                    if (Rand_ZeroOne() < 0.6f) {
                        this->eyeTexIndex = 2;
                    }
                    break;

                case 2:
                    if (Rand_ZeroOne() < 0.6f) {
                        this->eyeTexIndex = 0;
                    }
                    break;

                default:
                    this->eyeTexIndex = 0;
                    break;
            }
            break;

        case 1:
            this->eyeTexIndex = 3;
            break;
        case 2:
            this->eyeTexIndex = 4;
            break;
        case 3:
            this->eyeTexIndex = 5;
            break;
        case 4:
            this->eyeTexIndex = 2;
            break;
        case 5:
            this->eyeTexIndex = 0;
            break;
        default:
            this->unk_4CC = 0;
            this->eyeTexIndex = 0;
            break;
    }
}

s32 ObjUm_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    ObjUm* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s16 temp_v0_3;
    Vec3f sp5C = { 4223.0f, -979.0f, 4098.0f };
    Vec3f sp50 = { 4223.0f, -980.0f, -4083.0f };

    if ((limbIndex >= UM_LIMB_CREMIA_ROOT) && (this->type == OBJ_UM_TYPE_TERMINA_FIELD)) {
        *dList = NULL;
        return false;
    }

    if (limbIndex == UM_LIMB_CREMIA_HEAD) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTexIndex]));

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == UM_LIMB_WAGGON_RIGHT_WHEEL) {
        if (this->flags & OBJ_UM_FLAG_MOVING) {
            rot->x = -this->wheelRot;
        }
        Matrix_MultiplyVector3fByState(&sp5C, &this->unk_2C4);
    } else if (limbIndex == UM_LIMB_WAGGON_LEFT_WHEEL) {
        if (this->flags & OBJ_UM_FLAG_MOVING) {
            rot->x = this->wheelRot;
        }
        Matrix_MultiplyVector3fByState(&sp50, &this->unk_2DC);
    } else if ((limbIndex == UM_LIMB_CREMIA_HEAD) && (this->flags & OBJ_UM_FLAG_WAITING)) {
        if ((SubS_AngleDiffLessEqual(this->dyna.actor.shape.rot.y, 0x4E20, this->dyna.actor.yawTowardsPlayer) != 0) &&
            (this->dyna.actor.xzDistToPlayer < 500.0f)) {
            s16 sp3E;
            Vec3f sp30 = player->actor.world.pos;

            sp30.y = player->bodyPartsPos[7].y + 3.0f;
            sp3E = Math_Vec3f_Yaw(&this->dyna.actor.focus.pos, &sp30) - this->dyna.actor.shape.rot.y;
            temp_v0_3 = Math_Atan2S(
                this->dyna.actor.focus.pos.y - sp30.y,
                Math3D_XZLength(sp30.x - this->dyna.actor.focus.pos.x, sp30.z - this->dyna.actor.focus.pos.z));
            this->unk_2FE.x = rot->x + sp3E;
            this->unk_2FE.y = rot->y;
            this->unk_2FE.z = rot->z + temp_v0_3;
            Math_SmoothStepToS(&this->unk_2F8.x, this->unk_2FE.x, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk_2F8.z, this->unk_2FE.z, 4, 0x3E8, 1);
            this->unk_2F8.y = rot->y;
            rot->x = this->unk_2F8.x;
            rot->z = this->unk_2F8.z;
        } else {
            this->unk_2FE.x = rot->x;
            this->unk_2FE.y = rot->y;
            this->unk_2FE.z = rot->z;
            Math_SmoothStepToS(&this->unk_2F8.x, this->unk_2FE.x, 4, 0x3E8, 1);
            Math_SmoothStepToS(&this->unk_2F8.z, this->unk_2FE.z, 4, 0x3E8, 1);
            this->unk_2F8.y = rot->y;
            rot->x = this->unk_2F8.x;
            rot->z = this->unk_2F8.z;
        }
    } else if ((limbIndex == UM_LIMB_WAGGON_CART_COVER) && (this->flags & OBJ_UM_FLAG_PLAYING_MINIGAME)) {
        *dList = NULL;
    }

    return false;
}

void ObjUm_SpawnFragments(GlobalContext* globalCtx, Vec3f* potPos) {
    Vec3f sp8C = { 0.0f, -1.0f, 0.0f };
    Gfx* potFragments[] = { object_um_DL_000040, object_um_DL_000910, object_um_DL_0011E0 };
    s32 i;
    Vec3f sp70;

    EffectSsHitMark_SpawnFixedScale(globalCtx, 0, potPos);

    for (i = 0; i < 20; i++) {
        sp70.x = (Rand_ZeroOne() * 20.0f) - 10.0f;
        sp70.y = -((Rand_ZeroOne() * 20.0f) - 10.0f);
        sp70.z = (Rand_ZeroOne() * 20.0f) - 10.0f;
        EffectSsHahen_Spawn(globalCtx, potPos, &sp70, &sp8C, 1, 100, OBJECT_UM, 10,
                            potFragments[(s32)(Rand_ZeroOne() * ARRAY_COUNT(potFragments))]);
    }
}

void ObjUm_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    ObjUm* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Mtx* mtx_s3;
    Gfx* spFC[] = { NULL, gUmBrokenMinigamePotDL, gUmMinigamePotDL, gUmMinigamePotDL, gUmMinigamePotDL, object_um_DL_0067C0 };
    Gfx* spE4[] = { NULL, NULL, object_um_DL_004B60, object_um_DL_0043E0, NULL, NULL };
    f32 spCC[] = { 0.0f, 1070.0f, 1070.0f, 1070.0f, 1070.0f, 2100.0f };
    Vec3f spC0 = gZeroVec3f;
    Vec3f calcPotPos;
    f32 spB0;

    spC0.y += 1700.0f;

    if (limbIndex == UM_LIMB_WAGGON_CART_BED) {
        Vec3f spA4 = { 2000.0f, 1070.0f, 0.0f };

        Matrix_MultiplyVector3fByState(&spA4, &this->unk_308);
        this->flags |= OBJ_UM_FLAG_DRAWN_FLOOR;
    }

    if (limbIndex == UM_LIMB_WAGGON_CART_BED) {
        Vec3f sp98 = { 2500.0f, 200.0f, 0.0f };

        Matrix_MultiplyVector3fByState(&sp98, &this->cartBedPos);
    }

    if (limbIndex == UM_LIMB_WAGGON_CART_BED) {
        Vec3f* potPos;
        Vec3f sp88;
        Vec3s sp80;
        s32 i;
        f32 sp70[] = { 2000.0f, 0.0f, -2000.0f };

        if (!i) {}

        sp80.x = 0;
        sp80.z = 0;
        sp88.x = 6800.0f;
        OPEN_DISPS(gfxCtx);

        for (i = 0; i < ARRAY_COUNT(this->potsLife); i++) {
            sp88.z = sp70[i];
            sp88.y = spCC[this->potsLife[i]];

            if (this->potsLife[i] == 5) {
                sp80.y = 0x4000;
            } else {
                sp80.y = -0x4000;
            }

            Matrix_StatePush();
            Matrix_JointPosition(&sp88, &sp80);
            mtx_s3 = Matrix_NewMtx(gfxCtx);
            potPos = &this->potPos[i];
            Matrix_MultiplyVector3fByState(&spC0, &calcPotPos);
            SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, &calcPotPos, potPos, &spB0);

            if (this->wasPotHit[i]) {
                this->wasPotHit[i] = false;
                if (this->potsLife[i] == 1) {
                    ObjUm_SpawnFragments(globalCtx, &calcPotPos);
                } else {
                    EffectSsHitMark_SpawnFixedScale(globalCtx, 0, &calcPotPos);
                }
            }
            Matrix_StatePop();

            if (mtx_s3 != NULL) {
                if (globalCtx) {}
                gSPMatrix(POLY_OPA_DISP++, mtx_s3, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (spFC[this->potsLife[i]] != NULL) {
                    s32 pad;

                    gSPDisplayList(POLY_OPA_DISP++, spFC[this->potsLife[i]]);

                    if (spE4[this->potsLife[i]] != NULL) {
                        gSPDisplayList(POLY_OPA_DISP++, spE4[this->potsLife[i]]);
                    }
                }
            } else {
                return;
            }
        }

        CLOSE_DISPS(gfxCtx);
    }
    if (limbIndex == UM_LIMB_CREMIA_HEAD) {
        Matrix_GetStateTranslation(&this->dyna.actor.focus.pos);
    }
}

void func_80B7BEA4(Vec3f* cartBedPos, s16 arg1, Vec3f* arg2, u8 alpha, GlobalContext* globalCtx) {
    f32 temp;
    Vec3f sp108;
    CollisionPoly* sp104;
    Mtx* sp100;
    MtxF spC0;
    MtxF sp80;
    MtxF sp40;

    sp108.x = cartBedPos->x;
    sp108.y = cartBedPos->y + 1.0f;
    sp108.z = cartBedPos->z;

    temp = BgCheck_EntityRaycastFloor2(globalCtx, &globalCtx->colCtx, &sp104, &sp108);
    if (sp104 != NULL) {
        func_800C0094(sp104, cartBedPos->x, temp, cartBedPos->z, &spC0);
    } else {
        SkinMatrix_SetTranslate(&spC0, cartBedPos->x, cartBedPos->y, cartBedPos->z);
    }

    SkinMatrix_MulYRotation(&spC0, arg1);
    SkinMatrix_SetScale(&sp80, arg2->x, 1.0f, arg2->z);
    SkinMatrix_MtxFMtxFMult(&spC0, &sp80, &sp40);

    sp100 = SkinMatrix_MtxFToNewMtx(globalCtx->state.gfxCtx, &sp40);
    if (sp100 != NULL) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, alpha);
        gSPMatrix(POLY_OPA_DISP++, sp100, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gSquareShadowDL);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

#ifndef NOT_DEBUG_PRINT
#define BOOLSTR(x) ((x) ? "true" : "false")

void ObjUm_PrintStruct(ObjUm* this, GlobalContext* globalCtx, GfxPrint* printer) {
    s32 x = 31;
    s32 y = 3;
    s32 i;
    uintptr_t actionFuncReloc;

    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    GfxPrint_SetPos(printer, 28, 1);
    GfxPrint_Printf(printer, "gTime:%X", gSaveContext.save.time);

    GfxPrint_SetPos(printer, x - 7, ++y);
    actionFuncReloc = (uintptr_t)this->actionFunc - (uintptr_t)ObjUm_UpdateBanditsPositions + SEGMENT_START(ovl_Obj_Um);
    GfxPrint_Printf(printer, "actionFunc:%X", actionFuncReloc & 0x0000FFFF);

    // GfxPrint_SetPos(printer, x-5, ++y);
    // GfxPrint_Printf(printer, "wheelRot:%X", this->wheelRot);

    GfxPrint_SetPos(printer, x - 1, ++y);
    GfxPrint_Printf(printer, "type:%X", this->type);
    // GfxPrint_SetPos(printer, x-8, ++y);
    // GfxPrint_Printf(printer, "initialPath:%X", this->initialPathIdx);
    GfxPrint_SetPos(printer, x - 2, ++y);
    GfxPrint_Printf(printer, "! 2B4:%X", this->unk_2B4);

    // GfxPrint_SetPos(printer, x-1, ++y);
    // GfxPrint_Printf(printer, "path:%X", this->pathIdx);
    GfxPrint_SetPos(printer, x - 5, ++y);
    GfxPrint_Printf(printer, "pointIdx:%X", this->pointIdx);

    // GfxPrint_SetPos(printer, x-2, ++y);
    // GfxPrint_Printf(printer, "flags:%X", this->flags);

    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "304:%i", this->unk_304);

    // GfxPrint_SetPos(printer, x-2, ++y);
    // GfxPrint_Printf(printer, "308.x:%f", this->unk_308.x);
    // GfxPrint_SetPos(printer, x-2, ++y);
    // GfxPrint_Printf(printer, "308.y:%f", this->unk_308.y);
    // GfxPrint_SetPos(printer, x-2, ++y);
    // GfxPrint_Printf(printer, "308.z:%f", this->unk_308.z);

    if (this->type == OBJ_UM_TYPE_MILK_RUN_MINIGAME) {
        GfxPrint_SetPos(printer, x - 8, ++y);
        GfxPrint_Printf(printer, "potsLife[0]:%i", this->potsLife[0]);
        GfxPrint_SetPos(printer, x - 8, ++y);
        GfxPrint_Printf(printer, "potsLife[1]:%i", this->potsLife[1]);
        GfxPrint_SetPos(printer, x - 8, ++y);
        GfxPrint_Printf(printer, "potsLife[2]:%i", this->potsLife[2]);

        // GfxPrint_SetPos(printer, x-9, ++y);
        // GfxPrint_Printf(printer, "wasPotHit[0]:%i", this->wasPotHit[0]);
        // GfxPrint_SetPos(printer, x-9, ++y);
        // GfxPrint_Printf(printer, "wasPotHit[1]:%i", this->wasPotHit[1]);
        // GfxPrint_SetPos(printer, x-9, ++y);
        // GfxPrint_Printf(printer, "wasPotHit[2]:%i", this->wasPotHit[2]);
    }

    GfxPrint_SetPos(printer, x - 1, ++y);
    GfxPrint_Printf(printer, "time:%X", this->lastTime);

    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "4CC:%X", this->unk_4CC);

    // GfxPrint_SetPos(printer, x, ++y);
    // GfxPrint_Printf(printer, "4D8:%X", this->unk_4D8);

    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "4DC:%X", this->unk_4DC);

    if (this->type == OBJ_UM_TYPE_MILK_RUN_MINIGAME) {
        GfxPrint_SetPos(printer, x - 10, ++y);
        GfxPrint_Printf(printer, "arePotsBroken:%s", BOOLSTR(this->arePotsBroken));
    }

    y = 20;

    GfxPrint_SetPos(printer, 1, ++y);
    GfxPrint_Printf(printer, "Flags:");
    GfxPrint_SetPos(printer, 1, ++y);
    GfxPrint_Printf(printer, "   8 4 2 1");
    GfxPrint_SetPos(printer, 1, ++y);
    GfxPrint_Printf(printer, "1  %i %i %i %i", (this->flags & 0x08) >> 3, (this->flags & 0x04) >> 2,
                    (this->flags & 0x02) >> 1, this->flags & 0x01);
    GfxPrint_SetPos(printer, 1, ++y);
    GfxPrint_Printf(printer, "2  %i %i %i %i", (this->flags & 0x80) >> 7, (this->flags & 0x40) >> 6,
                    (this->flags & 0x20) >> 5, (this->flags & 0x10) >> 4);
    GfxPrint_SetPos(printer, 1, ++y);
    GfxPrint_Printf(printer, "3  %i %i %i %i", (this->flags & 0x800) >> 11, (this->flags & 0x400) >> 10,
                    (this->flags & 0x200) >> 9, (this->flags & 0x100) >> 8);
    GfxPrint_SetPos(printer, 1, ++y);
    GfxPrint_Printf(printer, "4      %i %i", (this->flags & 0x2000) >> 13, (this->flags & 0x1000) >> 12);

    y = 0;
    for (i = 0; i < 16; i++) {
        static char* flagsMap[] = {
            "OBJ_UM_FLAG_0001", "OBJ_UM_FLAG_MOVING",
            "OBJ_UM_FLAG_0004", "OBJ_UM_FLAG_WAITING",
            "OBJ_UM_FLAG_0010", "OBJ_UM_FLAG_DRAWN_FLOOR",
            "OBJ_UM_FLAG_0040", "OBJ_UM_FLAG_PLAYING_MINIGAME",
            "OBJ_UM_FLAG_0100", "OBJ_UM_FLAG_0200",
            "OBJ_UM_FLAG_0400", "OBJ_UM_FLAG_0800",
            "OBJ_UM_FLAG_1000", "OBJ_UM_FLAG_MINIGAME_FINISHED",
        };

        if (this->flags & (1 << i)) {
            GfxPrint_SetPos(printer, 1, ++y);
            GfxPrint_Printf(printer, "%s", &flagsMap[i][7]);
        }
    }

    y = 20;
    x = 29;

    GfxPrint_SetPos(printer, x - 2, ++y);
    GfxPrint_Printf(printer, "weekEvent");
    // GfxPrint_SetPos(printer, x, ++y);
    // GfxPrint_Printf(printer, "[22]&1: %i", gSaveContext.save.weekEventReg[22] & 1);
    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "[31]&40:%i", gSaveContext.save.weekEventReg[31] & 0x40 ? 1 : 0);
    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "[31]&80:%i", gSaveContext.save.weekEventReg[31] & 0x80 ? 1 : 0);
    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "[34]&80:%i", gSaveContext.save.weekEventReg[34] & 0x80 ? 1 : 0);
    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "[52]&01:%i", gSaveContext.save.weekEventReg[52] & 1 ? 1 : 0);
    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "[52]&02:%i", gSaveContext.save.weekEventReg[52] & 2 ? 1 : 0);
    GfxPrint_SetPos(printer, x, ++y);
    GfxPrint_Printf(printer, "[59]&02:%i", gSaveContext.save.weekEventReg[59] & 2 ? 1 : 0);
}

void ObjUm_DrawStruct(ObjUm* this, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    GfxPrint printer;
    Gfx* gfxRef;
    Gfx* gfx;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    GfxPrint_Init(&printer);

    gfxRef = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(gfxRef);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Open(&printer, gfx);

    ObjUm_PrintStruct(this, globalCtx, &printer);

    gfx = GfxPrint_Close(&printer);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(gfxRef, gfx);
    POLY_OPA_DISP = gfx;

    GfxPrint_Destroy(&printer);

    CLOSE_DISPS(gfxCtx);
}
#endif

void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjUm* this = THIS;
    Vec3f sp34;

    this->flags |= OBJ_UM_FLAG_0001;
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          ObjUm_OverrideLimbDraw, ObjUm_PostLimbDraw, &this->dyna.actor);
    sp34.x = 0.45f;
    sp34.y = 0.0f;
    sp34.z = 0.7f;
    func_80B7BEA4(&this->cartBedPos, this->dyna.actor.shape.rot.y, &sp34, 180, globalCtx);
    ObjUm_UpdateBanditsPositions(this, globalCtx);

#ifndef NOT_DEBUG_PRINT
    ObjUm_DrawStruct(this, globalCtx);
#endif
}
