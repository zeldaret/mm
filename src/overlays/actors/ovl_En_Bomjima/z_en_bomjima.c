/*
 * File: z_en_bomjima.c
 * Overlay: ovl_En_Bomjima
 * Description: Bombers - Jim
 */

#include "overlays/actors/ovl_En_Bombal/z_en_bombal.h"
#include "z_en_bomjima.h"
#include "objects/object_cs/object_cs.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBomjima*)thisx)

void EnBomjima_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomjima_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomjima_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomjima_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BFEA94(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFEB1C(EnBomjima* this);
void func_80BFEB64(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFEFF0(EnBomjima* this);
void func_80BFF03C(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFF120(EnBomjima* this);
void func_80BFF174(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFF430(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFF52C(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFF6CC(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFF754(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFF9B0(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFFB40(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFFBC4(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFFCFC(EnBomjima* this);
void func_80BFFD48(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFFE48(EnBomjima* this, GlobalContext* globalCtx);
void func_80BFFF54(EnBomjima* this, GlobalContext* globalCtx);
void func_80C00168(EnBomjima* this, GlobalContext* globalCtx);
void func_80C00234(EnBomjima* this);
void func_80C00284(EnBomjima* this, GlobalContext* globalCtx);

static s32 D_80C009F0 = 0;
static s32 D_80C009F4 = 0;

const ActorInit En_Bomjima_InitVars = {
    ACTOR_EN_BOMJIMA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomjima),
    (ActorFunc)EnBomjima_Init,
    (ActorFunc)EnBomjima_Destroy,
    (ActorFunc)EnBomjima_Update,
    (ActorFunc)EnBomjima_Draw,
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
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 30, 0, { 0, 0, 0 } },
};

u16 D_80C00A44[] = { 0x719, 0x71A, 0x71B, 0x708 };

u16 D_80C00A4C[] = { 0x739, 0x73A, 0x73B, 0x000 };

u16 D_80C00A54[] = {
    0x739, 0x73A, 0x73B, 0x714, 0x709, 0x70A, 0x70B, 0x70C, 0x70D, 0x70E, 0x70F, 0x712, 0x713,
};

u16 D_80C00A70[] = {
    0x739, 0x73A, 0x73B, 0x759, 0x753, 0x754, 0x755, 0x756, 0x70D, 0x757, 0x758, 0x712, 0x713,
};

u16 D_80C00A8C[] = { 0x736, 0x737, 0x738, 0x74E };

static AnimationHeader* sAnimations[] = {
    &gBomberIdleAnim,       &object_cs_Anim_00FAF4, &object_cs_Anim_0057C8, &object_cs_Anim_0053F4,
    &object_cs_Anim_002044, &object_cs_Anim_01007C, &object_cs_Anim_00349C, &object_cs_Anim_004960,
    &object_cs_Anim_005128, &object_cs_Anim_004C1C, &object_cs_Anim_001A1C, &object_cs_Anim_003EE4,
    &object_cs_Anim_00478C, &object_cs_Anim_00433C, &object_cs_Anim_0060E8, &object_cs_Anim_001708,
    &object_cs_Anim_005DC4, &object_cs_Anim_0026B0, &object_cs_Anim_0036B0, &object_cs_Anim_0031C4,
};

u8 D_80C00AE4[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE,
    ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP,
    ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP,
};

s16 D_80C00AF8[] = {
    0x4000, 60, 0x4000, 30, 0xC000, 30, 0xC000, 60,
};

void EnBomjima_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBomjima* this = THIS;
    s32 cs;
    s32 i;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_cs_Skel_00F82C, &gBomberIdleAnim, this->jointTable,
                       this->morphTable, OBJECT_CS_LIMB_MAX);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    gSaveContext.save.weekEventReg[83] &= (u8)~4;
    this->actor.targetMode = 0;
    this->unk_2E6 = ENBOMJIMA_GET_F0(&this->actor);
    this->unk_2E4 = ENBOMJIMA_GET_F(&this->actor);
    Actor_SetScale(&this->actor, 0.01f);

    if (this->unk_2E6 == 0) {
        cs = this->actor.cutscene;
        i = 0;

        while (cs != -1) {
            // clang-format off
            this->unk_2D4[i] = cs; cs = ActorCutscene_GetAdditionalCutscene(cs);
            // clang-format on
            i++;
        }

        this->actionFunc = func_80BFEA94;
    } else if (this->unk_2E6 == 2) {
        func_80BFFCFC(this);
    }

    if ((gSaveContext.save.weekEventReg[75] & 0x40) || (gSaveContext.save.weekEventReg[73] & 0x10) ||
        (gSaveContext.save.weekEventReg[85] & 2)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnBomjima_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBomjima* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BFE32C(EnBomjima* this, GlobalContext* globalCtx, s32 arg2) {
    Player* player = GET_PLAYER(globalCtx);

    this->unk_2CA = arg2;
    if (player->transformation == PLAYER_FORM_GORON) {
        this->unk_2C8 = 1;
    }
    if (player->transformation == PLAYER_FORM_ZORA) {
        this->unk_2C8 = 2;
    }

    switch (this->unk_2CA) {
        case 0:
            if (player->transformation == PLAYER_FORM_DEKU) {
                this->actor.textId = 0x759;
                if (!(gSaveContext.save.weekEventReg[73] & 0x20)) {
                    this->actor.textId = 0x708;
                }
            } else if (player->transformation == PLAYER_FORM_HUMAN) {
                this->actor.textId = 0x75A;
                if (!(gSaveContext.save.weekEventReg[84] & 0x80)) {
                    this->actor.textId = 0x719;
                }
            } else if ((this->unk_2C8 == 1) || (this->unk_2C8 == 2)) {
                this->actor.textId = D_80C00A44[this->unk_2C8];
            }
            break;

        case 1:
            this->actor.textId = D_80C00A4C[this->unk_2C8];
            break;

        case 2:
            if (player->transformation == PLAYER_FORM_DEKU) {
                this->actor.textId = D_80C00A54[this->unk_2C8];
                return;
            }
            this->actor.textId = D_80C00A70[this->unk_2C8];
            break;

        case 3:
            this->actor.textId = D_80C00A8C[this->unk_2C8];
            break;
    }
}

void func_80BFE494(EnBomjima* this, s32 arg1, f32 arg2) {
    this->unk_2EC = arg1;
    this->unk_2CC = Animation_GetLastFrame(sAnimations[arg1]);
    Animation_Change(&this->skelAnime, sAnimations[this->unk_2EC], arg2, 0.0f, this->unk_2CC, D_80C00AE4[this->unk_2EC],
                     -4.0f);
}

void func_80BFE524(EnBomjima* this) {
    if ((this->unk_2EC == 5) &&
        (Animation_OnFrame(&this->skelAnime, 9.0f) || Animation_OnFrame(&this->skelAnime, 10.0f) ||
         Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 18.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2EC == 18) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 2.0f) ||
         Animation_OnFrame(&this->skelAnime, 4.0f) || Animation_OnFrame(&this->skelAnime, 6.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2EC == 15) && Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_LAND);
    }

    if ((this->unk_2EC == 6) && Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_LAND);
    }
}

void func_80BFE65C(EnBomjima* this) {
    this->unk_2BC = 0;
    this->unk_2C0 = 0;
    this->unk_2BE = 0;
    this->unk_2A2 = 0;
    this->unk_290 = 0;
    this->unk_29A = 0;
}

void func_80BFE67C(EnBomjima* this, GlobalContext* globalCtx) {
    f32 sp84 = this->skelAnime.curFrame;
    f32 x;
    f32 z;
    s16 abs;
    s16 abs2;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    CollisionPoly* sp50;
    s32 sp4C;

    this->unk_2DC = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2A4);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 1, 5000, 0);

    switch (this->unk_2A2) {
        case 0:
            if (this->unk_2C0 == 0) {
                Math_Vec3f_Copy(&sp54, &this->actor.home.pos);

                sp54.x += randPlusMinusPoint5Scaled(150.0f);
                sp54.z += randPlusMinusPoint5Scaled(150.0f);

                abs = ABS_ALT(BINANG_SUB(this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp54)));
                if ((abs < 0x4000) && !BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp54, &sp6C,
                                                               &sp50, true, false, false, true, &sp4C)) {
                    func_80BFE494(this, 5, 1.0f);
                    Math_Vec3f_Copy(&this->unk_2A4, &sp54);
                    this->unk_2BE = Rand_S16Offset(30, 50);
                    this->unk_2A2++;
                }
            }
            break;

        case 1:
            if (sp84 >= 0.0f) {
                this->unk_2DC = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2A4);
                Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 10, 2000, 20);
            }

            abs2 = BINANG_SUB(this->actor.world.rot.y, this->unk_2DC);
            if ((s16)ABS_ALT(abs2) < 0x100) {
                Math_Vec3f_Copy(&sp60, &this->actor.world.pos);

                sp60.x += Math_SinS(this->actor.world.rot.y) * 60.0f;
                sp60.z += Math_CosS(this->actor.world.rot.y) * 60.0f;

                if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp60, &sp6C, &sp50, true,
                                            false, false, true, &sp4C)) {
                    this->unk_2C0 = 0;
                    if (Rand_ZeroOne() < 0.5f) {
                        func_80BFE494(this, 19, 1.0f);
                    } else {
                        func_80BFE494(this, 0, 1.0f);
                    }
                    this->unk_2A2 = 0;
                    this->unk_2D0 = 0.0f;
                    break;
                }
            }

            x = this->unk_2A4.x - this->actor.world.pos.x;
            z = this->unk_2A4.z - this->actor.world.pos.z;

            if ((this->unk_2BE == 0) || (sqrtf(SQ(x) + SQ(z)) < 4.0f)) {
                this->unk_2C0 = Rand_S16Offset(20, 20);
                if (!(this->unk_2C0 & 1)) {
                    func_80BFE494(this, 19, 1.0f);
                } else {
                    func_80BFE494(this, 0, 1.0f);
                }
                this->unk_2A2 = 0;
                this->unk_2D0 = 0.0f;
            } else if (sp84 >= 0.0f) {
                Math_ApproachF(&this->actor.world.pos.x, this->unk_2A4.x, 0.3f, this->unk_2D0);
                Math_ApproachF(&this->actor.world.pos.z, this->unk_2A4.z, 0.3f, this->unk_2D0);
                Math_ApproachF(&this->unk_2D0, 1.0f, 0.3f, 0.5f);
            }
            break;
    }
}

void func_80BFEA94(EnBomjima* this, GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (actor != NULL) {
        if (actor->id != ACTOR_EN_BOMBAL) {
            actor = actor->next;
            continue;
        }

        this->unk_2F0 = (EnBombal*)actor;
        Math_Vec3f_Copy(&this->unk_2B0, &actor->world.pos);
        if (this->unk_2F4 == 0) {
            this->unk_2F4 = this->unk_2F0->actor.cutscene;
        }
        func_80BFEB1C(this);
        break;
    }
}

void func_80BFEB1C(EnBomjima* this) {
    func_80BFE494(this, 1, 1.0f);
    func_80BFE65C(this);
    this->unk_2A0 = 0;
    this->actionFunc = func_80BFEB64;
}

void func_80BFEB64(EnBomjima* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad[2];
    Vec3f sp40;

    func_80BFE32C(this, globalCtx, 0);
    if (player->transformation == PLAYER_FORM_DEKU) {
        if (gSaveContext.save.weekEventReg[73] & 0x20) {
            this->unk_2C8 = 3;
            func_80BFE32C(this, globalCtx, 3);
        } else if (gSaveContext.save.weekEventReg[77] & 2) {
            this->unk_2C8 = 11;
            func_80BFE32C(this, globalCtx, 2);
        }
    } else if (player->transformation == PLAYER_FORM_HUMAN) {
        if (gSaveContext.save.weekEventReg[84] & 0x80) {
            this->unk_2C8 = 0;
            func_80BFE32C(this, globalCtx, 3);
        } else if (gSaveContext.save.weekEventReg[85] & 1) {
            this->unk_2C8 = 11;
            func_80BFE32C(this, globalCtx, 2);
        }
    }

    if (Text_GetFaceReaction(globalCtx, 0x11) != 0) {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 0x11);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_2DC = this->actor.yawTowardsPlayer;
        func_80C00234(this);
        return;
    }

    if (ActorCutscene_GetCurrentIndex() == -1) {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }

    if ((this->unk_2F0->actor.update == NULL) || (this->unk_2F0->actor.colChkInfo.health == 0)) {
        func_80BFEFF0(this);
        return;
    }

    switch (this->unk_2A2) {
        case 0:
            func_80BFE494(this, 4, 1.0f);
            this->unk_29A = -7000;
            this->unk_2A2++;
            break;

        case 1:
            this->unk_2DC = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2F0->actor.world.pos);
            if (Animation_OnFrame(&this->skelAnime, 19.0f)) {
                this->unk_2C0 = 5;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_SHOT_BREATH);
            }

            if (this->unk_2C0 == 1) {
                s16 sp3E = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2F0->actor.world.pos);

                if (Rand_ZeroOne() < 0.5f) {
                    sp3E += 0x4000;
                } else {
                    sp3E += 0xC000;
                }

                sp40.x = (Math_SinS(sp3E) * (Rand_ZeroFloat(20.0f) + 40.0f)) + this->unk_2F0->actor.world.pos.x;
                sp40.y = this->unk_2F0->actor.world.pos.y - randPlusMinusPoint5Scaled(40.0f);
                sp40.z = (Math_CosS(sp3E) * (Rand_ZeroFloat(20.0f) + 40.0f)) + this->unk_2F0->actor.world.pos.z;

                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &sp40, 50, NA_SE_EV_BOMBERS_SHOT_EXPLOSUIN);
                EffectSsHitMark_SpawnFixedScale(globalCtx, 0, &sp40);
                this->unk_2BC++;

                if (((s16)Rand_ZeroFloat(2.0f) + 3) < this->unk_2BC) {
                    func_80BFE494(this, 5, 1.0f);
                    this->unk_29A = 0;
                    Math_Vec3f_Copy(&this->unk_2A4, &this->actor.home.pos);
                    this->unk_2A4.x += randPlusMinusPoint5Scaled(150.0f);
                    this->unk_2A4.z += randPlusMinusPoint5Scaled(150.0f);
                    this->unk_2A2++;
                }
            }
            break;

        case 2:
            this->unk_2DC = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2A4);
            Math_ApproachF(&this->actor.world.pos.x, this->unk_2A4.x, 0.3f, 2.0f);
            Math_ApproachF(&this->actor.world.pos.z, this->unk_2A4.z, 0.3f, 2.0f);
            if (sqrtf(SQ(this->actor.world.pos.x - this->unk_2A4.x) + SQ(this->actor.world.pos.z - this->unk_2A4.z)) <
                4.0f) {
                func_80BFE65C(this);
            }
            break;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 1, 5000, 0);
}

void func_80BFEFF0(EnBomjima* this) {
    this->unk_2F0 = NULL;
    func_80BFE494(this, 19, 1.0f);
    func_80BFE65C(this);
    this->unk_2A0 = 1;
    this->actionFunc = func_80BFF03C;
}

void func_80BFF03C(EnBomjima* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->unk_2D4[0]);
    } else if (!ActorCutscene_GetCanPlayNext(this->unk_2D4[0])) {
        ActorCutscene_SetIntentToPlay(this->unk_2D4[0]);
    } else {
        player->stateFlags1 &= ~0x20;
        gSaveContext.save.weekEventReg[83] &= (u8)~4;
        this->actor.world.rot.y = Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx));
        this->unk_2DC = Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx));
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D4[0], &this->actor);
        func_80BFF120(this);
    }
}

void func_80BFF120(EnBomjima* this) {
    func_80BFE65C(this);
    this->unk_2C4 = 30;
    func_80BFE494(this, 6, 1.0f);
    this->unk_2DE = 0;
    this->unk_2A0 = 2;
    this->actionFunc = func_80BFF174;
}

void func_80BFF174(EnBomjima* this, GlobalContext* globalCtx) {
    f32 sp2C = this->skelAnime.curFrame;
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_2C4 == 1) {
        ActorCutscene_Stop(this->unk_2D4[0]);
        this->unk_2DE = 1;
    }

    if (Text_GetFaceReaction(globalCtx, 0x11) != 0) {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 0x11);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_2DC = this->actor.yawTowardsPlayer;
        func_80C00234(this);
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 1, 5000, 0);

    if ((this->unk_2CC <= sp2C) && (this->unk_2BC < 5)) {
        this->unk_2BC++;
        if (this->unk_2EC != 19) {
            func_80BFE494(this, 19, 1.0f);
        }
    }

    if (player->transformation == PLAYER_FORM_DEKU) {
        if (gSaveContext.save.weekEventReg[73] & 0x20) {
            this->unk_2C8 = 3;
            func_80BFE32C(this, globalCtx, 3);
        } else {
            if (!(gSaveContext.save.weekEventReg[77] & 2)) {
                if (this->unk_2E8 == 0) {
                    this->unk_2C8 = 4;
                } else {
                    this->unk_2C8 = 3;
                }
            } else {
                this->unk_2C8 = 11;
            }
            func_80BFE32C(this, globalCtx, 2);
        }
    } else if (player->transformation == PLAYER_FORM_HUMAN) {
        if (gSaveContext.save.weekEventReg[84] & 0x80) {
            this->unk_2C8 = 0;
            func_80BFE32C(this, globalCtx, 3);
        } else {
            if (!(gSaveContext.save.weekEventReg[85] & 1)) {
                if (this->unk_2EA == 0) {
                    this->unk_2C8 = 4;
                } else {
                    this->unk_2C8 = 3;
                }
            } else {
                this->unk_2C8 = 11;
            }
            func_80BFE32C(this, globalCtx, 2);
        }
    } else if (this->unk_2CA != 1) {
        func_80BFE32C(this, globalCtx, 1);
    }

    if (this->unk_2DE != 0) {
        if (this->unk_2BC >= 5) {
            func_80BFE67C(this, globalCtx);
        }
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80BFF3F0(EnBomjima* this) {
    func_80BFE494(this, 15, 1.0f);
    this->unk_2A0 = 3;
    this->actionFunc = func_80BFF430;
}

void func_80BFF430(EnBomjima* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_2CC <= curFrame) {
        EnBombal* bombal = (EnBombal*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOMBAL, this->unk_2B0.x,
                                                  this->unk_2B0.y, this->unk_2B0.z, 0, 0, 0, 0);

        if (bombal != NULL) {
            bombal->unk_150 = 0.0f;
            bombal->unk_14C = this->unk_2F4;
            Actor_ChangeFocus(&this->actor, globalCtx, &bombal->actor);
            gSaveContext.save.weekEventReg[83] &= (u8)~4;
            func_80BFE65C(this);
            func_801477B4(globalCtx);
            this->actionFunc = func_80BFEA94;
        }
    }
}

void func_80BFF4F4(EnBomjima* this) {
    func_80BFE65C(this);
    this->unk_2A0 = 4;
    this->actionFunc = func_80BFF52C;
}

void func_80BFF52C(EnBomjima* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 4) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        if (globalCtx->msgCtx.choiceIndex == 0) {
            Player* player = GET_PLAYER(globalCtx);

            func_8019F208();
            func_80BFE65C(this);
            this->unk_28E = 0;
            this->unk_29A = 0;
            this->unk_2C8 = 8;
            if (player->transformation == PLAYER_FORM_DEKU) {
                this->actor.textId = D_80C00A54[this->unk_2C8];
            } else {
                this->actor.textId = D_80C00A70[this->unk_2C8];
            }
            func_80151938(globalCtx, this->actor.textId);
            play_sound(NA_SE_SY_FOUND);
            func_80BFE494(this, 15, 1.0f);
            this->unk_2A0 = 5;
            this->actionFunc = func_80BFF6CC;
        } else {
            Player* player = GET_PLAYER(globalCtx);

            func_8019F230();
            func_80BFE65C(this);
            this->unk_2C8 = 10;
            if (player->transformation == PLAYER_FORM_DEKU) {
                this->actor.textId = D_80C00A54[this->unk_2C8];
                this->unk_2E8 = 1;
            } else {
                this->actor.textId = D_80C00A70[this->unk_2C8];
                this->unk_2EA = 1;
            }
            func_80151938(globalCtx, this->actor.textId);
            func_80C00234(this);
        }
    }
}

void func_80BFF6CC(EnBomjima* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_2CC <= curFrame) {
        if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
            func_801477B4(globalCtx);
            func_80BFE494(this, 1, 1.0f);
            this->actionFunc = func_80BFF754;
        }
    }
}

void func_80BFF754(EnBomjima* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f spA0;
    EnBombal* temp_s3;
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->unk_2D4[1]);
        return;
    }

    if (!ActorCutscene_GetCanPlayNext(this->unk_2D4[1])) {
        ActorCutscene_SetIntentToPlay(this->unk_2D4[1]);
        return;
    }

    for (i = 1; i < 5; i++) {
        Math_Vec3f_Copy(&spA0, &player->actor.world.pos);

        x = spA0.x - this->actor.world.pos.x;
        y = spA0.y - this->actor.world.pos.y;
        z = spA0.z - this->actor.world.pos.z;

        spA0.x += x * (2.0f + (i * 0.2f));
        spA0.y += y * (2.0f + (i * 0.2f));
        spA0.z += z * (2.0f + (i * 0.2f));

        temp_s3 = (EnBombal*)Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_BOMJIMA, spA0.x,
                                                spA0.y, spA0.z, 0, 0, 0, i + 32);
        if (temp_s3 != NULL) {
            s32 index = (i * 2) - 2;

            Math_Vec3f_Copy(&spA0, &this->actor.world.pos);

            spA0.x += Math_SinS(D_80C00AF8[(i * 2) - 2] + this->actor.world.rot.y) * D_80C00AF8[index + 1];
            spA0.z += Math_CosS(D_80C00AF8[index] + this->actor.world.rot.y) * D_80C00AF8[index + 1];

            Math_Vec3f_Copy(&temp_s3->unk_2A4, &spA0);
        }
    }

    D_80C009F0 = 0;
    ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D4[1], &this->actor);
    this->actionFunc = func_80BFF9B0;
}

void func_80BFF9B0(EnBomjima* this, GlobalContext* globalCtx) {
    if (D_80C009F0 >= 4) {
        Player* player = GET_PLAYER(globalCtx);

        D_80C009F0 = 0;
        this->unk_2C8 = 9;
        if (player->transformation == PLAYER_FORM_DEKU) {
            gSaveContext.save.weekEventReg[73] |= 0x10;
            gSaveContext.save.weekEventReg[77] |= 2;
        } else {
            gSaveContext.save.weekEventReg[85] |= 2;
            gSaveContext.save.weekEventReg[85] |= 1;
        }

        gSaveContext.save.weekEventReg[11] &= (u8)~1;
        gSaveContext.save.weekEventReg[11] &= (u8)~2;
        gSaveContext.save.weekEventReg[11] &= (u8)~4;
        gSaveContext.save.weekEventReg[11] &= (u8)~8;
        gSaveContext.save.weekEventReg[11] &= (u8)~0x10;

        gSaveContext.save.weekEventReg[76] &= (u8)~1;
        gSaveContext.save.weekEventReg[76] &= (u8)~2;
        gSaveContext.save.weekEventReg[76] &= (u8)~4;
        gSaveContext.save.weekEventReg[76] &= (u8)~8;
        gSaveContext.save.weekEventReg[76] &= (u8)~0x10;

        gSaveContext.save.bombersCaughtNum = 0;
        gSaveContext.save.bombersCaughtOrder[0] = 0;
        gSaveContext.save.bombersCaughtOrder[1] = 0;
        gSaveContext.save.bombersCaughtOrder[2] = 0;
        gSaveContext.save.bombersCaughtOrder[3] = 0;
        gSaveContext.save.bombersCaughtOrder[4] = 0;

        func_80BFE494(this, 3, 1.0f);
        this->unk_2C8 = 9;

        if (player->transformation == PLAYER_FORM_DEKU) {
            this->actor.textId = D_80C00A54[this->unk_2C8];
        } else {
            this->actor.textId = D_80C00A70[this->unk_2C8];
        }
        func_80151938(globalCtx, this->actor.textId);
        this->actionFunc = func_80BFFB40;
    }
}

void func_80BFFB40(EnBomjima* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80BFE494(this, 15, 1.0f);
        D_80C009F0 = 100;
        this->unk_2DC = 0;
        this->actionFunc = func_80BFFBC4;
    }
}

void func_80BFFBC4(EnBomjima* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if ((this->unk_2EC != 1) && (this->unk_2CC <= curFrame)) {
        func_80BFE494(this, 1, 1.0f);
    }

    if ((D_80C009F4 != 0) && (this->unk_2C2 == 0)) {
        this->unk_2C2 = Rand_S16Offset(5, 5);
    }

    if (this->unk_2C2 == 1) {
        this->unk_2DC = -10000;
    }

    Math_SmoothStepToS(&this->unk_290, this->unk_2DC, 1, 5000, 0);
    if (D_80C009F0 >= 104) {
        D_80C009F0 = 0;
        func_801477B4(globalCtx);
        globalCtx->nextEntranceIndex = Entrance_CreateIndexFromSpawn(6);
        gSaveContext.nextCutsceneIndex = 0;
        globalCtx->sceneLoadFlag = 20;
        globalCtx->unk_1887F = 0x56;
        gSaveContext.nextTransition = 3;
        ActorCutscene_Stop(this->unk_2D4[1]);
    }
}

void func_80BFFCFC(EnBomjima* this) {
    func_80BFE65C(this);
    func_80BFE494(this, 18, 1.0f);
    this->unk_2A0 = 6;
    this->actionFunc = func_80BFFD48;
}

void func_80BFFD48(EnBomjima* this, GlobalContext* globalCtx) {
    s32 pad[2];

    this->unk_2DC = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2A4);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 1, 5000, 0);
    Math_ApproachF(&this->actor.world.pos.x, this->unk_2A4.x, 0.3f, 4.0f);
    Math_ApproachF(&this->actor.world.pos.z, this->unk_2A4.z, 0.3f, 4.0f);
    if (sqrtf(SQ(this->actor.world.pos.x - this->unk_2A4.x) + SQ(this->actor.world.pos.z - this->unk_2A4.z)) < 4.0f) {
        D_80C009F0++;
        this->unk_2DC = this->actor.parent->world.rot.y;
        func_80BFE494(this, 0, 1.0f);
        this->actionFunc = func_80BFFE48;
    }
}

void func_80BFFE48(EnBomjima* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 1, 5000, 0);
    Math_ApproachF(&this->actor.world.pos.x, this->unk_2A4.x, 0.3f, 4.0f);
    Math_ApproachF(&this->actor.world.pos.z, this->unk_2A4.z, 0.3f, 4.0f);

    if (D_80C009F0 >= 100) {
        if (this->unk_2E4 != 4) {
            func_80BFE494(this, 15, 1.0f);
            this->unk_2DC = 0;
            func_80BFE65C(this);
            this->actionFunc = func_80BFFF54;
        } else {
            Math_SmoothStepToS(&this->unk_290, 10000, 1, 5000, 0);
            if (D_80C009F0 >= 103) {
                this->unk_2DC = 0;
                func_80BFE494(this, 15, 1.0f);
                func_80BFE65C(this);
                this->actionFunc = func_80BFFF54;
            }
        }
    }
}

void func_80BFFF54(EnBomjima* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->unk_290, this->unk_2DC, 1, 5000, 0);

    if ((D_80C009F4 != 0) && (this->unk_2C2 == 0)) {
        this->unk_2C2 = Rand_S16Offset(5, 5);
    }

    if (this->unk_2C2 == 1) {
        this->unk_2DC = -10000;
    }

    if (this->unk_2E4 != 4) {
        if ((this->unk_2EC != 0) && (this->unk_2CC <= curFrame)) {
            D_80C009F0++;
            func_80BFE494(this, 0, 1.0f);
        }
    } else if ((this->unk_2EC != 8) && (this->unk_2CC <= curFrame)) {
        func_80BFE494(this, 8, 1.0f);
        D_80C009F4 = 1;
    }

    if (this->unk_2EC == 8) {
        if ((D_80C009F4 == 1) && Animation_OnFrame(&this->skelAnime, 7.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HUMAN_BOUND);
            D_80C009F4 = 2;
        }

        if ((this->unk_2CC <= curFrame) && (this->unk_2C0 == 0)) {
            this->unk_2C0 = 10;
        }

        if (this->unk_2C0 == 1) {
            D_80C009F0++;
        }
    }
}

void func_80C0011C(EnBomjima* this) {
    func_80BFE65C(this);
    func_80BFE494(this, 0, 1.0f);
    this->unk_2A0 = 7;
    this->actionFunc = func_80C00168;
}

void func_80C00168(EnBomjima* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->transformation == PLAYER_FORM_HUMAN) {
        this->unk_2C8 = 4;
    } else if (player->transformation == PLAYER_FORM_DEKU) {
        this->unk_2C8 = 7;
    }

    func_80BFE32C(this, globalCtx, 0);
    func_80BFE67C(this, globalCtx);

    if (Text_GetFaceReaction(globalCtx, 0x11) != 0) {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 0x11);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_2DC = this->actor.yawTowardsPlayer;
        func_80C00234(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80C00234(EnBomjima* this) {
    func_80BFE494(this, 3, 1.0f);
    this->collider.dim.radius = 15;
    this->collider.dim.height = 40;
    func_80BFE65C(this);
    this->actionFunc = func_80C00284;
}

void func_80C00284(EnBomjima* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 sp28 = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2DC, 1, 5000, 0);
    if (((this->unk_2A0 == 0) || (this->unk_2C8 == 10) || (this->unk_2C8 == 11) || (this->unk_2CA == 1)) &&
        (this->unk_2CC <= sp28)) {
        if (!(this->unk_2BC & 1)) {
            func_80BFE494(this, 3, 1.0f);
        } else {
            func_80BFE494(this, 16, 1.0f);
        }
        this->unk_2BC++;
        this->unk_2BC &= 1;
    }

    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            this->unk_28E = -0xFA0;
            break;

        case PLAYER_FORM_GORON:
        case PLAYER_FORM_ZORA:
            this->unk_28E = -0x1770;
            break;
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        this->collider.dim.radius = 10;
        this->collider.dim.height = 30;
        if ((this->unk_2A0 == 4) || (this->unk_2CA == 1) || ((this->unk_2CA == 3) && (this->unk_2C8 >= 2))) {
            this->unk_28E = 0;
            if (player->stateFlags1 & 0x20) {
                player->stateFlags1 &= ~0x20;
            }

            if ((this->unk_2F0 == 0) || (this->unk_2F0->actor.update == NULL) ||
                (this->unk_2F0->actor.colChkInfo.health <= 0)) {
                func_80BFF3F0(this);
            } else {
                func_80BFE65C(this);
                func_801477B4(globalCtx);
                this->actionFunc = func_80BFEA94;
            }
            return;
        }

        func_801477B4(globalCtx);

        switch (this->unk_2CA) {
            case 0:
                this->unk_28E = 0;
                if (this->unk_2A0 == 7) {
                    func_80C0011C(this);
                } else {
                    func_80BFEB1C(this);
                }
                break;

            case 2:
                if (this->unk_2C8 == 10) {
                    func_80BFE65C(this);
                    this->unk_28E = 0;
                    func_80BFE494(this, 1, 1.0f);
                    this->unk_2A0 = 2;
                    this->actionFunc = func_80BFF174;
                    return;
                }

                this->unk_2C8++;
                if (player->transformation == PLAYER_FORM_DEKU) {
                    if ((this->unk_2E8 != 0) && (this->unk_2C8 == 4)) {
                        this->unk_2C8 = 6;
                    }
                    this->actor.textId = D_80C00A54[this->unk_2C8];
                } else {
                    if ((this->unk_2EA != 0) && (this->unk_2C8 == 4)) {
                        this->unk_2C8 = 6;
                    }
                    this->actor.textId = D_80C00A70[this->unk_2C8];
                }
                func_80151938(globalCtx, this->actor.textId);
                if ((this->unk_2C8 == 7) || (this->unk_2C8 == 12)) {
                    func_80BFF4F4(this);
                }
                break;

            case 3:
                this->unk_2C8++;
                this->actor.textId = D_80C00A8C[this->unk_2C8];
                func_80151938(globalCtx, this->actor.textId);
                if (this->unk_2C8 >= 2) {
                    func_80BFE494(this, 17, 1.0f);
                }
                break;
        }
    }
}

void EnBomjima_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBomjima* this = THIS;

    if (this->unk_2BE != 0) {
        this->unk_2BE--;
    }

    if (this->unk_2C2 != 0) {
        this->unk_2C2--;
    }

    if (this->unk_2C0 != 0) {
        this->unk_2C0--;
    }

    if (this->unk_2C6 != 0) {
        this->unk_2C6--;
    }

    if (this->unk_2C4 != 0) {
        this->unk_2C4--;
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    func_80BFE524(this);
    Actor_SetFocus(&this->actor, 20.0f);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Math_SmoothStepToS(&this->unk_28A, this->unk_290, 1, 5000, 0);
    Math_SmoothStepToS(&this->unk_288, this->unk_28E, 1, 1000, 0);
    Math_SmoothStepToS(&this->unk_294, this->unk_29A, 1, 1000, 0);

    if (this->unk_2E2 == 0) {
        this->unk_2E0++;
        if (this->unk_2E0 >= 3) {
            this->unk_2E0 = 0;
            this->unk_2E2 = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    this->actor.uncullZoneForward = 500.0f;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnBomjima_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnBomjima* this = THIS;

    if (limbIndex == 8) {
        rot->z += this->unk_294;
    }

    if ((limbIndex == 15) && (this->unk_2E6 == 2)) {
        *dList = NULL;
    }

    if (limbIndex == 17) {
        rot->x += this->unk_28A;
        rot->z += this->unk_288;
    }

    if ((limbIndex == 19) && (this->unk_2E6 == 2)) {
        *dList = NULL;
    }

    if ((limbIndex == 20) && (this->unk_2E6 == 0)) {
        *dList = NULL;
    }

    return false;
}

#include "overlays/ovl_En_Bomjima/ovl_En_Bomjima.c"

void EnBomjima_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* D_80C00B28[] = {
        gEnBomjima_D_80C00B08, gEnBomjima_D_80C00B18, gEnBomjima_D_80C00B18,
        gEnBomjima_D_80C00B18, gEnBomjima_D_80C00B18,
    };
    static TexturePtr D_80C00B3C[] = {
        object_cs_Tex_00C520,
        object_cs_Tex_00CD20,
        object_cs_Tex_00D520,
    };
    static TexturePtr D_80C00B48[] = {
        object_cs_Tex_00E620, object_cs_Tex_00EA20, object_cs_Tex_00EE20, object_cs_Tex_00DD20, object_cs_Tex_00F220,
    };
    EnBomjima* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C00B3C[this->unk_2E0]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C00B48[this->unk_2E4]));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_80C00B28[this->unk_2E4]));

    Scene_SetRenderModeXlu(globalCtx, 0, 1);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnBomjima_OverrideLimbDraw, NULL, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
