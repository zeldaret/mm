/*
 * File: z_en_jgame_tsn.c
 * Overlay: ovl_En_Jgame_Tsn
 * Description: Fisherman's Jumping Game - Fisherman
 */

#include "z_en_jgame_tsn.h"
#include "overlays/actors/ovl_Obj_Jgame_Light/z_obj_jgame_light.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnJgameTsn*)thisx)

void EnJgameTsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJgameTsn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C13A2C(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C13B74(EnJgameTsn* this);
void func_80C13BB8(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C13E6C(EnJgameTsn* this);
void func_80C13E90(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C13F9C(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C14030(EnJgameTsn* this);
void func_80C14044(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C1418C(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C141DC(EnJgameTsn* this);
void func_80C14230(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C144F8(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C14554(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C145FC(EnJgameTsn* this);
void func_80C14610(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C14684(EnJgameTsn* this, GlobalContext* globalCtx);
void func_80C147B4(EnJgameTsn* this, GlobalContext* globalCtx);
s32 func_80C149B0(GlobalContext* globalCtx, EnJgameTsnStruct* arg1);
s32 func_80C14BCC(EnJgameTsn* this, GlobalContext* globalCtx);

const ActorInit En_Jgame_Tsn_InitVars = {
    ACTOR_EN_JGAME_TSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnJgameTsn),
    (ActorFunc)EnJgameTsn_Init,
    (ActorFunc)EnJgameTsn_Destroy,
    (ActorFunc)EnJgameTsn_Update,
    (ActorFunc)EnJgameTsn_Draw,
};

static AnimationInfo sAnimations[] = {
    { &object_tsn_Anim_0092FC, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f },
    { &object_tsn_Anim_000964, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f },
    { &object_tsn_Anim_001198, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f },
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
    { 30, 40, 0, { 0, 0, 0 } },
};

TexturePtr D_80C150A4[] = {
    object_tsn_Tex_0073B8,
    object_tsn_Tex_0085B8,
};

void EnJgameTsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnJgameTsn* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_tsn_Skel_008AB8, &object_tsn_Anim_0092FC, this->jointTable,
                       this->morphTable, OBJECT_TSN_LIMB_MAX);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    this->actor.targetMode = 6;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.velocity.y = 0.0f;

    if (gSaveContext.save.entranceIndex == 0x68D0) {
        this->actor.flags |= ACTOR_FLAG_10000;
    }

    this->unk_2F8 = 0;
    this->unk_2FA = 0;
    this->unk_21C = 0;
    this->unk_2FE = 0;

    func_80C13A2C(this, globalCtx);
    func_80C13B74(this);
}

void func_80C13A2C(EnJgameTsn* this, GlobalContext* globalCtx) {
    Path* path = &globalCtx->setupPathList[ENJGAMETSN_GET_FF(&this->actor)];
    s32 i;

    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_1D8); i++) {
        this->unk_1D8[i].points = Lib_SegmentedToVirtual(path->points);
        this->unk_1D8[i].count = path->count;

        path = &globalCtx->setupPathList[path->unk1];
        if (path == NULL) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    this->unk_1F8.points = Lib_SegmentedToVirtual(path->points);
    this->unk_1F8.count = path->count;

    path = &globalCtx->setupPathList[path->unk1];
    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
    }

    this->unk_200.points = Lib_SegmentedToVirtual(path->points);
    this->unk_200.count = path->count;
}

void EnJgameTsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJgameTsn* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    gSaveContext.save.weekEventReg[90] &= (u8)~0x20;
}

void func_80C13B74(EnJgameTsn* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
    this->actionFunc = func_80C13BB8;
}

void func_80C13BB8(EnJgameTsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (this->actor.flags & ACTOR_FLAG_10000) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            if (gSaveContext.unk_3DE0[4] > 0) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                Message_StartTextbox(globalCtx, 0x10A2, &this->actor);
                this->unk_300 = 0x10A2;
            } else if (gSaveContext.minigameScore < 20) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                Message_StartTextbox(globalCtx, 0x10A2, &this->actor);
                this->unk_300 = 0x10A2;
            } else {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                Message_StartTextbox(globalCtx, 0x10A3, &this->actor);
                this->unk_300 = 0x10A3;
            }
        } else if (((gSaveContext.save.time > CLOCK_TIME(4, 0)) && (gSaveContext.save.time < CLOCK_TIME(7, 0))) ||
                   ((gSaveContext.save.time > CLOCK_TIME(16, 0)) && (gSaveContext.save.time < CLOCK_TIME(19, 0)))) {
            Message_StartTextbox(globalCtx, 0x1094, &this->actor);
            this->unk_300 = 0x1094;
        } else if (this->unk_2F8 == 0) {
            this->unk_2F8 = 1;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
            Message_StartTextbox(globalCtx, 0x1095, &this->actor);
            this->unk_300 = 0x1095;
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
            Message_StartTextbox(globalCtx, 0x1096, &this->actor);
            this->unk_300 = 0x1096;
        }
        func_80C14030(this);
    } else if (this->actor.flags & ACTOR_FLAG_10000) {
        func_800B8614(&this->actor, globalCtx, 200.0f);
    } else {
        func_800B8614(&this->actor, globalCtx, 80.0f);
    }

    if ((player->actor.bgCheckFlags & 1) && !(player->stateFlags1 & 0x2000) && (this->unk_2FE == 0) &&
        (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) && func_80C149B0(globalCtx, &this->unk_1F8)) {
        this->unk_2FE = 1;
        func_80C13E6C(this);
    } else if (!(player->actor.bgCheckFlags & 1)) {
        this->unk_2FE = 0;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x71C, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80C13E6C(EnJgameTsn* this) {
    this->actor.flags |= ACTOR_FLAG_10000;
    this->actionFunc = func_80C13E90;
}

void func_80C13E90(EnJgameTsn* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        if (((gSaveContext.save.time > CLOCK_TIME(4, 0)) && (gSaveContext.save.time < CLOCK_TIME(7, 0))) ||
            ((gSaveContext.save.time > CLOCK_TIME(16, 0)) && (gSaveContext.save.time < CLOCK_TIME(19, 0)))) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
            Message_StartTextbox(globalCtx, 0x1094, &this->actor);
            this->unk_300 = 0x1094;
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
            Message_StartTextbox(globalCtx, 0x1098, &this->actor);
            this->unk_300 = 0x1098;
        }
        func_80C14030(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 1000.0f);
    }
}

void func_80C13F88(EnJgameTsn* this) {
    this->actionFunc = func_80C13F9C;
}

void func_80C13F9C(EnJgameTsn* this, GlobalContext* globalCtx) {
    if (this->actor.cutscene != -1) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
            func_80C14030(this);
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    } else {
        func_80C14030(this);
    }
}

void func_80C14030(EnJgameTsn* this) {
    this->actionFunc = func_80C14044;
}

void func_80C14044(EnJgameTsn* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;

        case 4:
            func_80C14684(this, globalCtx);
            break;

        case 5:
            func_80C147B4(this, globalCtx);
            break;

        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                    ActorCutscene_Stop(this->actor.cutscene);
                }
                func_80C13B74(this);
            }
            break;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x71C, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80C1410C(EnJgameTsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->stateFlags1 |= 0x20;
    func_801A2BB8(0x25);
    globalCtx->interfaceCtx.unk_280 = 1;
    func_80112AFC(globalCtx);
    gSaveContext.save.weekEventReg[90] |= 0x20;
    func_8010E9F0(4, 0x78);
    this->actionFunc = func_80C1418C;
}

void func_80C1418C(EnJgameTsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->interfaceCtx.unk_280 == 8) {
        func_80C141DC(this);
        player->stateFlags1 &= ~0x20;
    }
}

void func_80C141DC(EnJgameTsn* this) {
    this->unk_218 = Rand_Next() & 3;
    this->unk_2FC = 0;
    *this->unk_208[this->unk_218] |= 1;
    this->actionFunc = func_80C14230;
}

void func_80C14230(EnJgameTsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;
    s32 rand;

    if ((this->unk_2FC > 100) || func_80C14BCC(this, globalCtx)) {
        rand = (u32)Rand_Next() % 3;

        this->unk_2FC = 0;
        if (rand < this->unk_218) {
            this->unk_218 = rand;
        } else {
            this->unk_218 = rand + 1;
        }

        for (i = 0; i < ARRAY_COUNT(this->unk_208); i++) {
            if (i == this->unk_218) {
                *this->unk_208[i] |= 1;
                *this->unk_208[i] &= ~8;
            } else {
                *this->unk_208[i] |= 8;
            }
        }
    }

    this->unk_2FC++;

    if ((player->actor.bgCheckFlags & 2) && func_80C149B0(globalCtx, &this->unk_200)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
        Message_StartTextbox(globalCtx, 0x109F, &this->actor);
        this->unk_300 = 0x109F;
        player->stateFlags1 |= 0x20;
        *this->unk_208[this->unk_218] &= ~1;
        func_801A2C20();
        func_80C14030(this);
    } else if ((player->actor.bgCheckFlags & 0x40) || (player->actor.bgCheckFlags & 0x20)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
        Message_StartTextbox(globalCtx, 0x10A0, &this->actor);
        this->unk_300 = 0x10A0;
        player->stateFlags1 |= 0x20;
        *this->unk_208[this->unk_218] &= ~1;
        func_801A2C20();
        func_80C14030(this);
    }

    if (gSaveContext.unk_3DE0[4] == 0) {
        Message_StartTextbox(globalCtx, 0x10A1, &this->actor);
        this->unk_300 = 0x10A1;
        player->stateFlags1 |= 0x20;
        *this->unk_208[this->unk_218] &= ~1;
        func_801A2C20();
        func_80C14030(this);
    }
}

void func_80C144E4(EnJgameTsn* this) {
    this->actionFunc = func_80C144F8;
}

void func_80C144F8(EnJgameTsn* this, GlobalContext* globalCtx) {
    globalCtx->nextEntranceIndex = 0x68D0;
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 0x50;
    gSaveContext.nextTransition = 3;
}

void func_80C14540(EnJgameTsn* this) {
    this->actionFunc = func_80C14554;
}

void func_80C14554(EnJgameTsn* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        if (!(gSaveContext.save.weekEventReg[82] & 0x10)) {
            gSaveContext.save.weekEventReg[82] |= 0x10;
        }
        func_80C145FC(this);
    } else if (gSaveContext.save.weekEventReg[82] & 0x10) {
        Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 500.0f, 100.0f);
    }
}

void func_80C145FC(EnJgameTsn* this) {
    this->actionFunc = func_80C14610;
}

void func_80C14610(EnJgameTsn* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, 0x10A4, &this->actor);
        this->unk_300 = 0x10A4;
        func_80C14030(this);
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_80C14684(EnJgameTsn* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex == 0) {
            if (gSaveContext.save.playerData.rupees >= 20) {
                Message_StartTextbox(globalCtx, 0x109E, &this->actor);
                this->unk_300 = 0x109E;
                func_801159EC(-20);
            } else {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
                Message_StartTextbox(globalCtx, 0x109D, &this->actor);
                this->unk_300 = 0x109D;
            }
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
            Message_StartTextbox(globalCtx, 0x109C, &this->actor);
            this->unk_300 = 0x109C;
        }
    }
}

void func_80C1476C(EnJgameTsn* this, GlobalContext* globalCtx) {
    Actor* prop = globalCtx->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (prop != NULL) {
        if (prop->id == ACTOR_OBJ_JGAME_LIGHT) {
            this->unk_208[OBJJGAMELIGHT_GET_7F(prop)] = &prop->colChkInfo.health;
        }
        prop = prop->next;
    }
}

void func_80C147B4(EnJgameTsn* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->unk_300) {
            case 0x1095:
                Message_StartTextbox(globalCtx, 0x1096, &this->actor);
                this->unk_300 = 0x1096;
                break;

            case 0x1096:
                Message_StartTextbox(globalCtx, 0x1097, &this->actor);
                this->unk_300 = 0x1097;
                break;

            case 0x1098:
                Message_StartTextbox(globalCtx, 0x1099, &this->actor);
                this->unk_300 = 0x1099;
                func_80C13F88(this);
                break;

            case 0x1099:
                Message_StartTextbox(globalCtx, 0x109A, &this->actor);
                this->unk_300 = 0x109A;
                break;

            case 0x109A:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
                Message_StartTextbox(globalCtx, 0x109B, &this->actor);
                this->unk_300 = 0x109B;
                break;

            case 0x109E:
                if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                    ActorCutscene_Stop(this->actor.cutscene);
                }
                func_801477B4(globalCtx);
                func_80C1476C(this, globalCtx);
                func_80C1410C(this, globalCtx);
                break;

            case 0x109F:
            case 0x10A0:
            case 0x10A1:
                func_801477B4(globalCtx);
                gSaveContext.minigameState = 3;
                gSaveContext.unk_3DD0[4] = 5;
                gSaveContext.save.weekEventReg[90] &= (u8)~0x20;
                func_80C144E4(this);
                break;

            case 0x10A3:
                func_801477B4(globalCtx);
                func_80C14540(this);
                func_80C14554(this, globalCtx);
                break;
        }
    }
}

s32 func_80C14960(Vec2f arg0, Vec2f arg1) {
    s32 phi_v1;

    if ((arg1.x * arg0.z) < (arg0.x * arg1.z)) {
        phi_v1 = 1;
    } else {
        phi_v1 = -1;
    }
    return phi_v1;
}

s32 func_80C149B0(GlobalContext* globalCtx, EnJgameTsnStruct* arg1) {
    s32 i = 1;
    s32 temp_s3;
    Player* player = GET_PLAYER(globalCtx);
    Vec2f sp64;
    Vec2f sp5C;
    s32 sp58 = true;
    s32 pad;
    s32 sp50 = 0;
    f32 temp_f20 = player->actor.world.pos.z;
    f32 temp_f22 = player->actor.world.pos.x;

    sp64.x = arg1->points[0].z - temp_f20;
    sp64.z = arg1->points[0].x - temp_f22;
    sp5C.x = arg1->points[1].z - temp_f20;
    sp5C.z = arg1->points[1].x - temp_f22;
    temp_s3 = func_80C14960(sp64, sp5C);

    while (i != 0) {
        sp50++;
        if (i < (arg1->count - 1)) {
            i++;
        } else {
            i = 0;
        }

        sp64.x = arg1->points[sp50].z - temp_f20;
        sp64.z = arg1->points[sp50].x - temp_f22;
        sp5C.x = arg1->points[i].z - temp_f20;
        sp5C.z = arg1->points[i].x - temp_f22;

        if (func_80C14960(sp64, sp5C) != temp_s3) {
            sp58 = false;
            break;
        }
    }

    return sp58;
}

s32 func_80C14BCC(EnJgameTsn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;
    s32 phi_s3 = -1;

    if (player->actor.bgCheckFlags & 2) {
        for (i = 0; i < ARRAY_COUNT(this->unk_1D8); i++) {
            if (func_80C149B0(globalCtx, &this->unk_1D8[i])) {
                phi_s3 = i;
            }
        }

        if (phi_s3 == -1) {
            return false;
        }

        if (phi_s3 == this->unk_218) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
            *this->unk_208[phi_s3] |= 2;
            globalCtx->interfaceCtx.unk_25C = 1;
            return true;
        }

        if (*this->unk_208[phi_s3] & 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
            *this->unk_208[phi_s3] |= 2;
            globalCtx->interfaceCtx.unk_25C = 1;
        } else {
            *this->unk_208[phi_s3] |= 4;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_ERROR);
        }
    }

    return false;
}

void func_80C14D14(EnJgameTsn* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80C14D58(EnJgameTsn* this, GlobalContext* globalCtx) {
    func_800E9250(globalCtx, &this->actor, &this->unk_2EC, &this->unk_2F2, this->actor.focus.pos);

    if (DECR(this->unk_2FA) == 0) {
        this->unk_2FA = Rand_S16Offset(60, 60);
    }

    if ((this->unk_2FA == 1) || (this->unk_2FA == 3)) {
        this->unk_21C = 1;
    } else {
        this->unk_21C = 0;
    }
}

void EnJgameTsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJgameTsn* this = THIS;

    this->actionFunc(this, globalCtx);

    SkelAnime_Update(&this->skelAnime);
    func_80C14D14(this, globalCtx);
    func_80C14D58(this, globalCtx);
}

s32 EnJgamesTsn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    EnJgameTsn* this = THIS;
    s16 temp_v0 = this->unk_2EC.x >> 1;

    if (limbIndex == OBJECT_TSN_LIMB_0F) {
        rot->x += this->unk_2EC.y;
        rot->z += temp_v0;
    } else if (limbIndex == OBJECT_TSN_LIMB_08) {
        rot->x += this->unk_2F2.y;
        rot->z += temp_v0;
    }
    return false;
}

void EnJgamesTsn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == OBJECT_TSN_LIMB_0F) {
        Matrix_GetStateTranslation(&thisx->focus.pos);
    }
}

void EnJgameTsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnJgameTsn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C5B0(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C150A4[this->unk_21C]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80C150A4[this->unk_21C]));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnJgamesTsn_OverrideLimbDraw, EnJgamesTsn_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
