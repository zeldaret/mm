/*
 * File: z_en_toto.c
 * Overlay: ovl_En_Toto
 * Description: Toto
 */

#include "z_en_toto.h"
#include "objects/object_zm/object_zm.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnToto*)thisx)

#define ENTOTO_WEEK_EVENT_FLAGS (gSaveContext.save.weekEventReg[50] & 1 || gSaveContext.save.weekEventReg[51] & 0x80)

void EnToto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnToto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnToto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnToto_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BA3930(EnToto* this, GlobalContext* globalCtx);
void func_80BA39C8(EnToto* this, GlobalContext* globalCtx);
void func_80BA3DBC(EnToto* this, GlobalContext* globalCtx);
void func_80BA3BFC(EnToto* this, GlobalContext* globalCtx);
void func_80BA3CC4(EnToto* this, GlobalContext* globalCtx);
void func_80BA3D38(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA3EC0(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA3ED4(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA3EE8(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA3F2C(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA3FB0(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA3FCC(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA402C(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA407C(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA40D4(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4128(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA415C(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4204(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA42BC(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA43F4(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA445C(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA44A0(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4530(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA46D8(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4740(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA47E0(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA49A4(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4A00(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4B24(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4C0C(EnToto* this, GlobalContext* globalCtx);
s32 func_80BA4C44(EnToto* this, GlobalContext* globalCtx);

const ActorInit En_Toto_InitVars = {
    ACTOR_EN_TOTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZM,
    sizeof(EnToto),
    (ActorFunc)EnToto_Init,
    (ActorFunc)EnToto_Destroy,
    (ActorFunc)EnToto_Update,
    (ActorFunc)EnToto_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0x01000202, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

static EnTotoActionFunc D_80BA501C[] = {
    func_80BA3930,
    func_80BA3BFC,
    func_80BA3D38,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};

static EnTotoText D_80BA502C[] = {
    { 0, 0, 0x2B21 },
    { 3, 2, 0 },
};

static EnTotoText D_80BA5034[] = {
    { 0, 0, 0x2B23 },
};

static EnTotoText D_80BA5038[] = {
    { 2, 1, 0x2B24 },
    { 4, 0, 0x2B25 },
    { 3, 2, 0 },
};

static EnTotoText D_80BA5044[] = {
    { 4, 0, 0x2B25 },
};

static EnTotoText D_80BA5048[] = {
    { 16, 0, 0x2A94 }, { 0, 0, 0x2A95 }, { 4, 0, 0x2A96 }, { 4, 0, 0x2A97 },
    { 0, 0, 0x2A98 },  { 0, 0, 0x2A99 }, { 4, 0, 0x2A9A }, { 4, 0, 0x2A9B },
};

static EnTotoText D_80BA5068[] = {
    { 0, 0, 0x2AE1 },
    { 0, 0, 0x2AE2 },
    { 4, 0, 0x2AE3 },
};

static EnTotoText D_80BA5074[] = {
    { 4, 0, 0x2AE4 },
};

static AnimationHeader* D_80BA5078[] = { &object_zm_Anim_0028B8, &object_zm_Anim_00B894, &object_zm_Anim_002F20,
                                         &object_zm_Anim_00BC08 };

static EnTotoText D_80BA5088[] = {
    { 5, 0, 0 },  { 6, 20, 0 }, { 7, 0, 0 },  { 8, 9, 0 },  { 9, 10, 0 }, { 1, 0, 0 },  { 10, 0, 0 },
    { 11, 0, 0 }, { 12, 0, 0 }, { 13, 0, 0 }, { 15, 0, 0 }, { 17, 1, 0 }, { 17, 0, 0 },
};

static EnTotoText D_80BA50BC[] = {
    { 5, 0, 0 }, { 6, 20, 0 }, { 8, 5, 0 }, { 12, 0, 0 }, { 13, 0, 0 }, { 14, 20, 0x2B22 }, { 1, 0, 0 }, { 17, 0, 0 },
};

static EnTotoUnkStruct2 D_80BA50DC[] = {
    { 0x2B2F, 0x2B30, 0X2B31, { 0xFF96, 0x0016, 0xFE16 } },
    { 0x2B26, 0x2B27, 0x2B28, { 0x0072, 0x0016, 0xFE3C } },
    { 0x2B29, 0x2B2A, 0x2B2B, { 0xFF67, 0x0016, 0xFE6E } },
    { 0x2B2C, 0x2B2D, 0x2B2E, { 0xFFF1, 0x0016, 0xFE74 } },
};

static Vec3s D_80BA510C[] = {
    { 0xFF46, 0xFFF8, 0xFF40 },
    { 0xFF21, 0xFFFD, 0xFF04 },
    { 0xFF64, 0x0016, 0xFE7E },
};

static u16 D_80BA5120[] = { 67, 68, 69, 70 };

static u8 D_80BA5128[] = { 8, 4, 2, 1 };

static EnTotoUnkFunc D_80BA512C[] = {
    func_80BA3F2C, func_80BA3ED4, func_80BA3F2C, func_80BA3F2C, func_80BA3F2C, func_80BA3ED4,
    func_80BA42BC, func_80BA3ED4, func_80BA44A0, func_80BA3FB0, func_80BA402C, func_80BA46D8,
    func_80BA47E0, func_80BA49A4, func_80BA3FB0, func_80BA402C, func_80BA3F2C, func_80BA3EC0,
};

static EnTotoUnkFunc D_80BA5174[] = {
    func_80BA40D4, func_80BA4128, func_80BA415C, func_80BA3EE8, func_80BA3EE8, func_80BA407C,
    func_80BA43F4, func_80BA445C, func_80BA4530, func_80BA4204, func_80BA407C, func_80BA4740,
    func_80BA407C, func_80BA4A00, func_80BA3FCC, func_80BA407C, func_80BA4B24,
};

static EnTotoActionFunc D_80BA51B8[] = {
    func_80BA39C8,
    func_80BA3CC4,
    func_80BA3DBC,
};

void func_80BA36C0(EnToto* this, GlobalContext* globalCtx, s32 index) {
    this->unk2B7 = 0;
    this->actionFuncIndex = index;
    D_80BA501C[this->actionFuncIndex](this, globalCtx);
}

void EnToto_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnToto* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    if (globalCtx->sceneNum == SCENE_MILK_BAR &&
        (gSaveContext.save.time >= CLOCK_TIME(6, 0) && gSaveContext.save.time < CLOCK_TIME(21, 30))) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    this->actor.bgCheckFlags |= 0x400;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_zm_Skel_00A978,
                       ((globalCtx->sceneNum == SCENE_SONCHONOIE) ? &object_zm_Anim_003AA8 : &object_zm_Anim_00C880),
                       this->jointTable, this->morphTable, 18);
    func_80BA36C0(this, globalCtx, 0);
    this->actor.shape.rot.x = 0;
}

void EnToto_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnToto* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BA383C(EnToto* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime) && this->actionFuncIndex == 1 &&
        this->skelAnime.animation != &object_zm_Anim_000C80) {
        if (globalCtx->msgCtx.currentTextId != 0x2A98 && globalCtx->msgCtx.currentTextId != 0x2A99) {
            if (this->unk2B4 & 1 || Rand_ZeroOne() > 0.5f) {
                this->unk2B4 = (this->unk2B4 + 1) & 3;
            }
        }
        Animation_PlayOnce(&this->skelAnime, D_80BA5078[this->unk2B4]);
    }
    func_800BBB74(this->unk260, 0x14, 0x50, 3);
}

void func_80BA3930(EnToto* this, GlobalContext* globalCtx) {
    AnimationHeader* animationHeader = &object_zm_Anim_00C880;

    if (globalCtx->sceneNum == SCENE_SONCHONOIE) {
        animationHeader = &object_zm_Anim_003AA8;
    }
    Animation_MorphToLoop(&this->skelAnime, animationHeader, -4.0f);
}

s32 func_80BA397C(EnToto* this, s16 arg1) {
    s16 diff;

    diff = this->actor.yawTowardsPlayer - this->actor.home.rot.y;
    if (ABS_ALT(diff) < arg1) {
        return 1;
    }
    return 0;
}

void func_80BA39C8(EnToto* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80BA383C(this, globalCtx);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80BA36C0(this, globalCtx, 1);
        if (globalCtx->sceneNum != SCENE_SONCHONOIE) {
            Flags_SetSwitch(globalCtx, this->actor.params & 0x7F);
        } else if (player->transformation == PLAYER_FORM_DEKU) {
            Flags_SetSwitch(globalCtx, this->actor.home.rot.x);
        }
        this->unk2B6 = 0;
        return;
    }

    //! @TODO: 0xED02 nor 0xED01 match CLOCK_TIME macro
    if ((globalCtx->sceneNum == SCENE_MILK_BAR &&
         !(gSaveContext.save.time >= CLOCK_TIME(6, 0) && gSaveContext.save.time < 0xED02)) ||
        (globalCtx->sceneNum != SCENE_MILK_BAR && func_80BA397C(this, 0x2000))) {
        if (this->unk2B6 != 0) {
            this->text = D_80BA5044;
            this->actor.flags |= ACTOR_FLAG_10000;
            func_800B8500(&this->actor, globalCtx, 9999.9f, 9999.9f, EXCH_ITEM_NONE);
        } else {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            func_800B8614(&this->actor, globalCtx, 50.0f);
            if (globalCtx->sceneNum == SCENE_SONCHONOIE) {
                if (player->transformation == PLAYER_FORM_DEKU) {
                    if (!Flags_GetSwitch(globalCtx, this->actor.home.rot.x)) {
                        this->text = D_80BA5068;
                    } else {
                        this->text = D_80BA5074;
                    }
                } else {
                    this->text = D_80BA5048;
                }
            } else if (ENTOTO_WEEK_EVENT_FLAGS) {
                this->text = D_80BA502C;
            } else if (!Flags_GetSwitch(globalCtx, this->actor.params & 0x7F)) {
                this->text = D_80BA5034;
            } else {
                this->text = D_80BA5038;
            }
        }

        this->actor.textId = this->text->textId;
    }
}

void func_80BA3BFC(EnToto* this, GlobalContext* globalCtx) {
    if (globalCtx->sceneNum == SCENE_SONCHONOIE) {
        Animation_MorphToPlayOnce(&this->skelAnime, &object_zm_Anim_000C80, -4.0f);
        this->unk2B4 = 0;
    } else {
        if (this->text->unk0 == 4) {
            func_80151BB4(globalCtx, 9);
        }
        Animation_MorphToLoop(&this->skelAnime, &object_zm_Anim_00B3E0, -4.0f);
    }
}

void func_80BA3C88(EnToto* this) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 4000, 800);
}

void func_80BA3CC4(EnToto* this, GlobalContext* globalCtx) {
    func_80BA383C(this, globalCtx);
    func_80BA3C88(this);
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        func_80BA36C0(this, globalCtx, this->text->unk1);
    } else {
        func_80BA4C44(this, globalCtx);
    }
}

void func_80BA3D38(EnToto* this, GlobalContext* globalCtx) {
    this->cutscene = this->actor.cutscene;
    this->text = ENTOTO_WEEK_EVENT_FLAGS ? D_80BA50BC : D_80BA5088;
    func_80BA4C0C(this, globalCtx);
    globalCtx->actorCtx.unk5 |= 0x20;
    this->unk260[0] = 0;
}

void func_80BA3DBC(EnToto* this, GlobalContext* globalCtx) {
    Player* player;

    func_80BA383C(this, globalCtx);
    if (this->unk2B7 == 0) {
        if (!func_80BA4C44(this, globalCtx)) {
            return;
        }
        if (this->text->unk1 != 0 && ENTOTO_WEEK_EVENT_FLAGS) {
            this->unk2B7 = 1;
            return;
        }
    } else {
        player = GET_PLAYER(globalCtx);
        if (player->stateFlags1 & 0x400 && player->unk_AE7 != 0) {
            func_80151BB4(globalCtx, 48);
            func_80151BB4(globalCtx, 9);
            func_80151BB4(globalCtx, 10);
        } else {
            return;
        }
    }

    func_80BA36C0(this, globalCtx, 0);
    ActorCutscene_Stop(this->cutscene);
    globalCtx->actorCtx.unk5 &= ~0x20;
}

s32 func_80BA3EC0(EnToto* this, GlobalContext* globalCtx) {
    return 1;
}

s32 func_80BA3ED4(EnToto* this, GlobalContext* globalCtx) {
    return 0;
}

s32 func_80BA3EE8(EnToto* this, GlobalContext* globalCtx) {
    if (this->text->unk1 == 2) {
        func_800B7298(globalCtx, NULL, 7);
    }
    return 0;
}

s32 func_80BA3F2C(EnToto* this, GlobalContext* globalCtx) {
    if (this->text->textId != 0) {
        func_80151938(globalCtx, this->text->textId);
    } else {
        func_801477B4(globalCtx);
        func_80BA3EE8(this, globalCtx);
    }
    if (this->text->unk0 == 4) {
        func_80151BB4(globalCtx, 9);
    }
    return 0;
}

s32 func_80BA3FB0(EnToto* this, GlobalContext* globalCtx) {
    this->unk2B1 = this->text->unk1;
    return 0;
}

s32 func_80BA3FCC(EnToto* this, GlobalContext* globalCtx) {
    if (DECR(this->unk2B1) == 0) {
        Message_StartTextbox(globalCtx, this->text->textId, NULL);
        return 1;
    }
    return 0;
}

s32 func_80BA402C(EnToto* this, GlobalContext* globalCtx) {
    s16 prevCutscene = this->cutscene;

    this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
    ActorCutscene_SetIntentToPlay(this->cutscene);
    ActorCutscene_Stop(prevCutscene);
    return 0;
}

s32 func_80BA407C(EnToto* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->cutscene, &GET_PLAYER(globalCtx)->actor);
        return 1;
    }

    ActorCutscene_SetIntentToPlay(this->cutscene);
    return 0;
}

s32 func_80BA40D4(EnToto* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx)) {
        return 1;
    }
    return 0;
}

s32 func_80BA4128(EnToto* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 2) {
        return 1;
    }
    return 0;
}

s32 func_80BA415C(EnToto* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 4 && Message_ShouldAdvance(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex != 0) {
            func_8019F230();
        } else {
            func_8019F208();
        }
        return (globalCtx->msgCtx.choiceIndex != 0 ? 0 : this->text->unk1) + 1; // Possible msg MACRO
    }
    return 0;
}

s32 func_80BA4204(EnToto* this, GlobalContext* globalCtx) {
    EnTotoUnkStruct2* temp_v1_2;

    if (DECR(this->unk2B1) == 0) {
        if (!ENTOTO_WEEK_EVENT_FLAGS) {
            temp_v1_2 = &D_80BA50DC[gSaveContext.save.playerForm - 1];
            Message_StartTextbox(globalCtx, (this->text->unk0 == 6) ? temp_v1_2->unk0 : temp_v1_2->unk4, NULL);
        }
        return 1;
    }
    return 0;
}

s32 func_80BA42BC(EnToto* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u32 phi_s0 = 0;
    Vec3s* end = &D_80BA510C[3];

    func_80BA3FB0(this, globalCtx);
    func_800B7298(globalCtx, NULL, 6);
    if (player->actor.world.pos.z > -310.0f) {
        if ((player->actor.world.pos.x > -150.0f) || (player->actor.world.pos.z > -172.0f)) {
            phi_s0 = 3;
        } else {
            if (player->actor.world.pos.z > -232.0f) {
                phi_s0 = 2;
            } else {
                phi_s0 = 1;
            }
        }
    }
    func_80122744(globalCtx, this->unk2BC, phi_s0, end - phi_s0);
    this->spotlights = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_DM_CHAR07, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0xF02);
    return 0;
}

s32 func_80BA43F4(EnToto* this, GlobalContext* globalCtx) {
    func_80BA3C88(this);
    if (func_80122760(globalCtx, this->unk2BC, 60.0f)) {
        func_800B7298(globalCtx, NULL, 0x13);
        return func_80BA4204(this, globalCtx);
    }
    return 0;
}

s32 func_80BA445C(EnToto* this, GlobalContext* globalCtx) {
    if (func_80BA4128(this, globalCtx)) {
        func_800B7298(globalCtx, NULL, 6);
        return 1;
    }
    return 0;
}

s32 func_80BA44A0(EnToto* this, GlobalContext* globalCtx) {
    ActorCutscene_Stop(this->cutscene);
    this->unk2B1 = 0;
    return 0;
}

s32 func_80BA44D4(EnTotoUnkStruct2* arg0, Player* player) {
    Vec3f unk6;

    Math_Vec3s_ToVec3f(&unk6, &arg0->unk6);
    if (Math_Vec3f_DistXZ(&player->actor.world.pos, &unk6) < 10.0f) {
        return 1;
    }
    return 0;
}

s32 func_80BA4530(EnToto* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnTotoUnkStruct2* temp_s0;
    s32 i;

    func_80BA3C88(this);
    if (player->actor.world.pos.z > -270.0f) {
        if (this->spotlights != NULL) {
            Actor_MarkForDeath(this->spotlights);
        }
        this->unk2B6 = 1;
        return this->text->unk1;
    }
    if (player->actor.bgCheckFlags & 1) {
        temp_s0 = &D_80BA50DC[gSaveContext.save.playerForm - 1];
        if (func_80BA44D4(temp_s0, player)) {
            Math_Vec3s_ToVec3f(&player->actor.world.pos, &temp_s0->unk6);
            player->actor.shape.rot.y = 0;
            player->currentYaw = 0;
            return func_80BA407C(this, globalCtx);
        }
        if (!ENTOTO_WEEK_EVENT_FLAGS) {
            for (i = 0; i < 4; i++) {
                if (func_80BA44D4(&D_80BA50DC[i], player)) {
                    if (this->unk2B1 < 10) {
                        this->unk2B1++;
                        if (this->unk2B1 >= 10) {
                            Message_StartTextbox(globalCtx,
                                                 D_80BA50DC[((void)0, gSaveContext.save.playerForm) - 1].unk2, NULL);
                        }
                    }
                    return 0;
                }
            }
            this->unk2B1 = 0;
        }
    }
    return 0;
}

s32 func_80BA46D8(EnToto* this, GlobalContext* globalCtx) {
    func_800B7298(globalCtx, NULL, 0x44);
    func_80152434(globalCtx, D_80BA5120[CUR_FORM]);
    return 0;
}

s32 func_80BA4740(EnToto* this, GlobalContext* globalCtx) {
    if (globalCtx->msgCtx.ocarinaMode == 4) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
            gSaveContext.save.weekEventReg[56] |= 0x10;
        }
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            gSaveContext.save.weekEventReg[56] |= 0x20;
        }
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            gSaveContext.save.weekEventReg[56] |= 0x40;
        }
        if (gSaveContext.save.playerForm == PLAYER_FORM_GORON) {
            gSaveContext.save.weekEventReg[56] |= 0x80;
        }
        return 1;
    }
    return 0;
}

s32 func_80BA47E0(EnToto* this, GlobalContext* globalCtx) {
    Vec3f spawnPos;
    s32 i;

    this->unk2B3 = 0;
    if (gSaveContext.save.weekEventReg[56] & 0x10) {
        this->unk2B3 += 1;
    }
    if (gSaveContext.save.weekEventReg[56] & 0x20) {
        this->unk2B3 += 2;
    }
    if (gSaveContext.save.weekEventReg[56] & 0x40) {
        this->unk2B3 += 4;
    }
    if (gSaveContext.save.weekEventReg[56] & 0x80) {
        this->unk2B3 += 8;
    }
    for (i = 0; i < 4; i++) {
        if (gSaveContext.save.playerForm != (i + 1) && (D_80BA5128[i] & this->unk2B3)) {
            Math_Vec3s_ToVec3f(&spawnPos, &D_80BA50DC[i].unk6);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_PLAYER, spawnPos.x, spawnPos.y, spawnPos.z, i + 2, 0, 0,
                        -1);
        }
    }
    func_80BA402C(this, globalCtx);
    if (ENTOTO_WEEK_EVENT_FLAGS) {
        func_80BA402C(this, globalCtx);
    }
    return 0;
}

s32 func_80BA49A4(EnToto* this, GlobalContext* globalCtx) {
    func_800B7298(globalCtx, NULL, 0x44);
    func_801A31EC(NA_BGM_BALLAD_OF_THE_WIND_FISH, 4, this->unk2B3 ^ 0xF);
    this->unk2B1 = 4;
    return 0;
}

s32 func_80BA4A00(EnToto* this, GlobalContext* globalCtx) {
    Actor* actor;

    if (DECR(this->unk2B1) == 0) {
        if (!Audio_IsSequencePlaying(NA_BGM_BALLAD_OF_THE_WIND_FISH)) {
            actor = &GET_PLAYER(globalCtx)->actor;
            actor = actor->next;
            while (actor != NULL) {
                Actor_MarkForDeath(actor);
                actor = actor->next;
            }
            if (this->spotlights != NULL) {
                Actor_MarkForDeath(this->spotlights);
            }
            func_800B7298(globalCtx, NULL, 0x45);
            if (this->unk2B3 == 0xF) {
                if (CURRENT_DAY == 1) {
                    gSaveContext.save.weekEventReg[50] |= 1;
                } else {
                    gSaveContext.save.weekEventReg[51] |= 0x80;
                }
            } else {
                func_80BA402C(this, globalCtx);
            }
            return 1;
        }
    }
    return 0;
}

s32 func_80BA4B24(EnToto* this, GlobalContext* globalCtx) {
    Player* player;

    if (func_80BA40D4(this, globalCtx)) {
        player = GET_PLAYER(globalCtx);
        Animation_MorphToPlayOnce(&this->skelAnime, &object_zm_Anim_0028B8, -4.0f);
        if (player->transformation == PLAYER_FORM_ZORA) {
            if (!Flags_GetSwitch(globalCtx, this->actor.params & 0x7F)) {
                Flags_SetSwitch(globalCtx, this->actor.params & 0x7F);
                return 1;
            } else {
                return 3;
            }
        } else {
            if (!Flags_GetSwitch(globalCtx, (this->actor.params >> 7) & 0x7F)) {
                Flags_SetSwitch(globalCtx, (this->actor.params >> 7) & 0x7F);
                return 4;
            } else {
                return 7;
            }
        }
    }
    return 0;
}

s32 func_80BA4C0C(EnToto* this, GlobalContext* globalCtx) {
    return D_80BA512C[this->text->unk0](this, globalCtx);
}

s32 func_80BA4C44(EnToto* this, GlobalContext* globalCtx) {
    s32 ret;

    ret = D_80BA5174[this->text->unk0](this, globalCtx);
    if (ret != 0) {
        this->text += ret;
        return func_80BA4C0C(this, globalCtx);
    }
    return 0;
}

void func_80BA4CB4(EnToto* this, GlobalContext* globalCtx) {
    CsCmdActorAction* action = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 525)];

    if (this->unk2B5 != action->action) {
        this->unk2B5 = action->action;
        if (this->unk2B5 != 4) {
            if (this->unk2B5 == 3) {
                Animation_MorphToPlayOnce(&this->skelAnime, &object_zm_Anim_001DF0, -4.0f);
            } else {
                Animation_PlayOnce(&this->skelAnime,
                                   this->unk2B5 == 1 ? &object_zm_Anim_0016A4 : &object_zm_Anim_0022C8);
                if (this->unk2B5 == 2 && this->unk2B3 != 0xF) {
                    func_80151BB4(globalCtx, 9);
                    func_80151BB4(globalCtx, 10);
                }
            }
        }
    }
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x320);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk2B5 != 3) {
            Animation_PlayLoop(&this->skelAnime, this->unk2B5 == 1 ? &object_zm_Anim_00C880 : &object_zm_Anim_001324);
        }
    }
    if (this->unk2B5 == 4 && !Actor_HasParent(&this->actor, globalCtx)) {
        Actor_PickUp(&this->actor, globalCtx, GI_MASK_CIRCUS_LEADER, 9999.9f, 9999.9f);
    }
}

void EnToto_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnToto* this = THIS;
    s32 pad;

    if (Cutscene_CheckActorAction(globalCtx, 0x20D)) {
        func_80BA4CB4(this, globalCtx);
    } else {
        D_80BA51B8[this->actionFuncIndex](this, globalCtx);
    }

    Collider_ResetCylinderAC(globalCtx, &this->collider.base);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_SetFocus(&this->actor, 40.0f);
}

void EnToto_Draw(Actor* thisx, GlobalContext* globalCtx) {
    TexturePtr sp4C[] = { object_zm_Tex_008AE8, object_zm_Tex_00A068, object_zm_Tex_00A468 };
    EnToto* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sp4C[this->unk260[0]]));
    Scene_SetRenderModeXlu(globalCtx, 0, 1);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
