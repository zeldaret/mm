/*
 * File: z_en_bom_bowl_man.c
 * Overlay: ovl_En_Bom_Bowl_Man
 * Description: Line of Bombers when they teach you the password
 */

#include "z_en_bom_bowl_man.h"
#include "objects/object_cs/object_cs.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBomBowlMan*)thisx)

void EnBomBowlMan_Init(Actor* thisx, PlayState* play);
void EnBomBowlMan_Destroy(Actor* thisx, PlayState* play);
void EnBomBowlMan_Update(Actor* thisx, PlayState* play);
void EnBomBowlMan_Draw(Actor* thisx, PlayState* play);

void func_809C4BC4(EnBomBowlMan* this, PlayState* play);
void func_809C4DA4(EnBomBowlMan* this, PlayState* play);
void func_809C51B4(EnBomBowlMan* this, PlayState* play);
void func_809C52B4(EnBomBowlMan* this);
void func_809C5310(EnBomBowlMan* this, PlayState* play);
void func_809C53A4(EnBomBowlMan* this);
void func_809C5408(EnBomBowlMan* this, PlayState* play);
void func_809C5524(EnBomBowlMan* this, PlayState* play);
void func_809C5598(EnBomBowlMan* this, PlayState* play);
void func_809C5738(EnBomBowlMan* this, PlayState* play);
void func_809C59A4(EnBomBowlMan* this, PlayState* play);
void func_809C59F0(EnBomBowlMan* this, PlayState* play);
void func_809C5AA4(EnBomBowlMan* this, PlayState* play);
void func_809C5B1C(EnBomBowlMan* this, PlayState* play);
void func_809C5BA0(EnBomBowlMan* this);
void func_809C5BF4(EnBomBowlMan* this, PlayState* play);

s32 D_809C6100 = 0;

s32 D_809C6104 = 0;

const ActorInit En_Bom_Bowl_Man_InitVars = {
    ACTOR_EN_BOM_BOWL_MAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomBowlMan),
    (ActorFunc)EnBomBowlMan_Init,
    (ActorFunc)EnBomBowlMan_Destroy,
    (ActorFunc)EnBomBowlMan_Update,
    (ActorFunc)EnBomBowlMan_Draw,
};

static AnimationHeader* sAnimations[] = {
    &gBomberIdleAnim,       &object_cs_Anim_00FAF4, &object_cs_Anim_0057C8, &object_cs_Anim_0053F4,
    &object_cs_Anim_002044, &object_cs_Anim_01007C, &object_cs_Anim_00349C, &object_cs_Anim_004960,
    &object_cs_Anim_005128, &object_cs_Anim_004C1C, &object_cs_Anim_001A1C, &object_cs_Anim_003EE4,
    &object_cs_Anim_00478C, &object_cs_Anim_00433C, &object_cs_Anim_0060E8, &object_cs_Anim_001708,
    &object_cs_Anim_005DC4, &object_cs_Anim_0026B0, &object_cs_Anim_0036B0, &object_cs_Anim_0031C4,
};

u8 D_809C6178[] = {
    0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0,
};

u16 D_809C618C[] = { 0x710, 0x711, 0x715, 0x716, 0x717, 0x718 };

u16 D_809C6198[] = { 0x74F, 0x750, 0x751, 0x752 };

Vec3f D_809C61A0[] = {
    { -730.0f, 200.0f, -2350.0f }, { -690.0f, 200.0f, -2350.0f }, { -650.0f, 200.0f, -2350.0f },
    { -610.0f, 200.0f, -2350.0f }, { -570.0f, 200.0f, -2350.0f },
};

void EnBomBowlMan_Init(Actor* thisx, PlayState* play) {
    EnBomBowlMan* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    this->actor.gravity = -3.0f;
    SkelAnime_InitFlex(play, &this->skelAnime, &object_cs_Skel_00F82C, &gBomberIdleAnim, this->jointTable,
                       this->morphTable, 21);
    this->unk_2F6 = ENBOMBOWLMAN_GET_F0(&this->actor);
    this->unk_2F4 = ENBOMBOWLMAN_GET_F(&this->actor);
    this->actor.targetMode = 6;
    Actor_SetScale(&this->actor, 0.01f);

    if (this->unk_2F6 == ENBOMBOWLMAN_F0_0) {
        if (this->unk_2F4 == 0) {
            func_809C4BC4(this, play);
        } else {
            this->unk_2F4--;
            func_809C5BA0(this);
        }
        return;
    }

    this->unk_29A = ENBOMBOWLMAN_GET_FF00(&this->actor);
    this->path = SubS_GetPathByIndex(play, this->unk_29A, 0x3F);
    this->unk_2C8 = 80.0f;

    if ((gSaveContext.save.entranceIndex == 0xD220) && (gSaveContext.save.weekEventReg[73] & 0x80) &&
        !CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        this->unk_2D6 = this->actor.cutscene;
        if (this->unk_2D6 == 0) {
            Actor_MarkForDeath(&this->actor);
        }
        func_809C52B4(this);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnBomBowlMan_Destroy(Actor* thisx, PlayState* play) {
}

void func_809C493C(EnBomBowlMan* this, s32 arg1, f32 arg2) {
    this->unk_2F8 = arg1;
    this->unk_2C4 = Animation_GetLastFrame(sAnimations[arg1]);
    Animation_Change(&this->skelAnime, sAnimations[this->unk_2F8], arg2, 0.0f, this->unk_2C4, D_809C6178[this->unk_2F8],
                     -4.0f);
}

void func_809C49CC(EnBomBowlMan* this) {
    if ((this->unk_2F8 == 5) &&
        (Animation_OnFrame(&this->skelAnime, 9.0f) || Animation_OnFrame(&this->skelAnime, 10.0f) ||
         Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 18.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2F8 == 0xB) &&
        (Animation_OnFrame(&this->skelAnime, 4.0f) || Animation_OnFrame(&this->skelAnime, 8.0f) ||
         Animation_OnFrame(&this->skelAnime, 12.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2F8 == 0x12) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 2.0f) ||
         Animation_OnFrame(&this->skelAnime, 4.0f) || Animation_OnFrame(&this->skelAnime, 6.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }

    if ((this->unk_2F8 == 0xF) && Animation_OnFrame(&this->skelAnime, 15.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_LAND);
    }

    if ((this->unk_2F8 == 6) && Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_LAND);
    }
}

void func_809C4B50(EnBomBowlMan* this) {
    this->unk_2B8 = 0;
    this->unk_2BC = 0;
    this->unk_2BA = 0;
    this->unk_29E = 0;
    this->unk_290 = 0;
}

void func_809C4B6C(EnBomBowlMan* this) {
    if ((this->unk_29A != ENBOMBOWLMAN_FF00_MINUS1) && (this->path != NULL)) {
        if (!SubS_CopyPointFromPath(this->path, this->unk_298, &this->unk_2A0)) {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_809C4BC4(EnBomBowlMan* this, PlayState* play) {
    s32 pad;
    s32 i;
    Vec3f sp7C;
    EnBomBowlMan* bomBowlMan;
    s8 code;

    func_809C4B50(this);
    func_809C493C(this, 0, 1.0f);

    for (i = 0; i < ARRAY_COUNT(gSaveContext.save.bomberCode); i++) {
        Math_Vec3f_Copy(&sp7C, &this->actor.home.pos);
        code = gSaveContext.save.bomberCode[i];
        if (code == 1) {
            Math_Vec3f_Copy(&this->actor.world.pos, &D_809C61A0[i]);
            this->unk_2D8[code] = this;
        } else {
            Math_Vec3f_Copy(&sp7C, &D_809C61A0[i]);
            bomBowlMan = (EnBomBowlMan*)Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_BOM_BOWL_MAN,
                                                           sp7C.x, sp7C.y, sp7C.z, 0, this->actor.world.rot.y, 0, code);
            if (bomBowlMan != NULL) {
                if (i == 2) {
                    this->unk_2D8[0] = bomBowlMan;
                }
                this->unk_2D8[code] = bomBowlMan;
            }
        }
    }

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->unk_2D0);
    } else if (!ActorCutscene_GetCanPlayNext(this->unk_2D0)) {
        ActorCutscene_SetIntentToPlay(this->unk_2D0);
    }

    func_809C493C(this, 3, 1.0f);
    this->unk_2D4 = this->actor.yawTowardsPlayer;
    this->unk_290 = this->actor.yawTowardsPlayer;
    gSaveContext.save.weekEventReg[73] &= (u8)~0x10;
    gSaveContext.save.weekEventReg[85] &= (u8)~2;
    this->unk_29C = 0;
    this->actionFunc = func_809C4DA4;
}

void func_809C4DA4(EnBomBowlMan* this, PlayState* play) {
    Math_SmoothStepToS(&this->unk_290, this->unk_2D4, 1, 5000, 0);

    if (this->unk_2B8 == 0) {
        Player* player = GET_PLAYER(play);

        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk_2D0);
            return;
        }

        if (!ActorCutscene_GetCanPlayNext(this->unk_2D0)) {
            ActorCutscene_SetIntentToPlay(this->unk_2D0);
            return;
        }

        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D0, &this->actor);
        this->unk_2B8 = 1;
        this->unk_2C0 = 0;
        this->unk_2D4 = this->actor.yawTowardsPlayer;
        this->unk_290 = this->actor.yawTowardsPlayer;
        if (player->transformation == PLAYER_FORM_HUMAN) {
            Message_StartTextbox(play, D_809C618C[0], &this->actor);
        } else {
            Message_StartTextbox(play, D_809C6198[0], &this->actor);
        }
    }

    if ((this->unk_2BC == 0) && (Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        Player* player = GET_PLAYER(play);
        s32 pad;
        s32 sp28 = false;

        func_801477B4(play);

        switch (this->unk_2C0) {
            case 0:
                this->unk_2C0 = 1;
                D_809C6104 = 1;
                Camera_SetTargetActor(Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(this->unk_2D0)),
                                      &this->unk_2D8[0]->actor);
                this->unk_2D4 = 0;
                this->unk_2BC = 10;
                func_809C493C(this, 17, 1.0f);
                break;

            case 1:
                D_809C6104 = 0;
                func_809C493C(this, 3, 1.0f);
                this->unk_2D4 = this->actor.yawTowardsPlayer;
                this->unk_2C0 = 2;
                if ((player->transformation == PLAYER_FORM_HUMAN) && CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                    this->unk_2C0 = 4;
                }
                break;

            case 2:
                if (player->transformation == PLAYER_FORM_HUMAN) {
                    this->unk_2B8 = 2;
                    ActorCutscene_Stop(this->unk_2D0);
                    func_809C59A4(this, play);
                    sp28 = true;
                } else {
                    this->unk_2C0 = 3;
                    play->msgCtx.msgLength = 0;
                    func_809C493C(this, 1, 1.0f);
                    D_809C6100 = 1;
                    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                        ActorCutscene_Stop(0x7C);
                        ActorCutscene_SetIntentToPlay(this->unk_2D2);
                    } else if (!ActorCutscene_GetCanPlayNext(this->unk_2D2)) {
                        ActorCutscene_SetIntentToPlay(this->unk_2D2);
                    }
                    ActorCutscene_Stop(this->unk_2D0);
                    this->actionFunc = func_809C5B1C;
                    sp28 = true;
                }
                break;

            case 3:
                if (player->transformation == PLAYER_FORM_HUMAN) {
                    this->unk_2C0 = 4;
                } else {
                    this->actionFunc = func_809C51B4;
                    return;
                }
                break;

            case 4:
                if (this->unk_2B8 != 2) {
                    ActorCutscene_Stop(this->unk_2D0);
                }
                play->msgCtx.msgLength = 0;
                func_809C493C(this, 1, 1.0f);
                D_809C6100 = 1;
                this->actionFunc = func_809C5B1C;
                sp28 = true;
                break;

            case 5:
                func_80151BB4(play, 0x24);
                func_80151BB4(play, 0x25);
                func_80151BB4(play, 0);
                this->actionFunc = func_809C51B4;
                sp28 = true;
                break;
        }

        if (!sp28) {
            if (player->transformation == PLAYER_FORM_HUMAN) {
                func_80151938(play, D_809C618C[this->unk_2C0]);
            } else {
                func_80151938(play, D_809C6198[this->unk_2C0]);
            }
        }
    }
}

void func_809C51B4(EnBomBowlMan* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((play->msgCtx.unk120B1 == 0) &&
        ((play->msgCtx.msgMode == 0) || (Message_GetState(&play->msgCtx) == TEXT_STATE_DONE))) {
        play->nextEntranceIndex = Entrance_CreateIndexFromSpawn(6);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_86;
        gSaveContext.nextTransitionType = TRANS_TYPE_03;
        gSaveContext.save.weekEventReg[75] &= (u8)~0x40;
        if (player->transformation == PLAYER_FORM_HUMAN) {
            gSaveContext.save.weekEventReg[84] |= 0x80;
            gSaveContext.save.weekEventReg[77] &= (u8)~2;
        } else {
            gSaveContext.save.weekEventReg[73] |= 0x20;
            gSaveContext.save.weekEventReg[85] &= (u8)~1;
        }
    }
}

void func_809C52B4(EnBomBowlMan* this) {
    this->actor.draw = NULL;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.world.pos.x = 1340.0f;
    this->actor.world.pos.z = -1795.0f;
    this->unk_29C = 3;
    this->actionFunc = func_809C5310;
}

void func_809C5310(EnBomBowlMan* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->actor.world.pos.x < 1510.0f) {
        if (player->transformation != PLAYER_FORM_DEKU) {
            if (this->actor.xzDistToPlayer < this->unk_2C8) {
                func_800B7298(play, &this->actor, 7);
                func_809C53A4(this);
            }
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_809C53A4(EnBomBowlMan* this) {
    this->actor.draw = EnBomBowlMan_Draw;
    this->actor.world.pos.x = 1360.0f;
    this->actor.world.pos.z = -1870.0f;
    func_809C493C(this, 18, 1.0f);
    this->unk_29C = 3;
    this->actionFunc = func_809C5408;
}

void func_809C5408(EnBomBowlMan* this, PlayState* play) {
    s32 pad[2];
    Player* player = GET_PLAYER(play);

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &player->actor.world.pos), 1,
                       0x1388, 0);
    Math_SmoothStepToS(&player->actor.shape.rot.y, Math_Vec3f_Yaw(&player->actor.world.pos, &this->actor.world.pos), 1,
                       0x1388, 0);
    player->actor.world.rot.y = player->actor.shape.rot.y;
    Math_ApproachF(&this->actor.world.pos.x, 1350.0f, 0.3f, 2.0f);
    Math_ApproachF(&this->actor.world.pos.z, -1800.0f, 0.3f, 2.0f);
    if (sqrtf(SQ(this->actor.world.pos.x - 1350.0f) + SQ(this->actor.world.pos.z + 1800.0f)) < 4.0f) {
        func_809C5524(this, play);
    }
}

void func_809C5524(EnBomBowlMan* this, PlayState* play) {
    this->actor.textId = 0x730;
    if (!(gSaveContext.save.weekEventReg[85] & 2)) {
        this->actor.textId = 0x72F;
    }
    func_809C493C(this, 3, 1.0f);
    Message_StartTextbox(play, this->actor.textId, &this->actor);
    this->actionFunc = func_809C5598;
}

void func_809C5598(EnBomBowlMan* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        if ((this->actor.textId == 0x72F) || (this->actor.textId == 0x730)) {
            this->actor.textId = 0x731;
        } else if (this->actor.textId == 0x731) {
            this->actor.textId = 0x732;
        } else if (this->actor.textId == 0x732) {
            this->actor.textId = 0x733;
        } else if (this->actor.textId == 0x733) {
            this->actor.textId = 0x734;
        } else if (this->actor.textId == 0x734) {
            this->actor.textId = 0x715;
        } else if (this->actor.textId == 0x715) {
            func_800B7298(play, &this->actor, 6);
            func_809C493C(this, 17, 1.0f);
            func_809C59A4(this, play);
            return;
        } else if (this->actor.textId == 0x716) {
            this->actor.textId = 0x735;
        } else if (this->actor.textId == 0x735) {
            this->unk_2C2 = 0;
            func_809C493C(this, 17, 1.0f);
            func_80151BB4(play, 0x24);
            func_80151BB4(play, 0x25);
            func_80151BB4(play, 0);
            func_800B7298(play, &this->actor, 7);
            this->actionFunc = func_809C5738;
            return;
        }
        func_80151938(play, this->actor.textId);
    }
}

void func_809C5738(EnBomBowlMan* this, PlayState* play) {
    s32 pad[3];
    s16 yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2A0);

    if (this->unk_2C2 == 0) {
        if ((play->msgCtx.unk120B1 == 0) &&
            ((play->msgCtx.msgMode == 0) || (Message_GetState(&play->msgCtx) == TEXT_STATE_DONE))) {
            this->unk_2C2 = 1;
            func_809C4B6C(this);
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
                ActorCutscene_SetIntentToPlay(this->unk_2D6);
            } else if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
                ActorCutscene_SetIntentToPlay(this->unk_2D6);
            } else {
                ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
                this->unk_2C2 = 2;
                func_809C493C(this, 18, 1.0f);
            }
        }
    } else if (this->unk_2C2 == 1) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk_2D6);
        } else if (!ActorCutscene_GetCanPlayNext(this->unk_2D6)) {
            ActorCutscene_SetIntentToPlay(this->unk_2D6);
        } else {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D6, &this->actor);
            this->unk_2C2 = 2;
            func_809C493C(this, 18, 1.0f);
        }
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.y, yaw, 1, 2000, 10);
        Math_ApproachF(&this->actor.world.pos.x, this->unk_2A0.x, 0.5f, 6.0f);
        Math_ApproachF(&this->actor.world.pos.z, this->unk_2A0.z, 0.5f, 6.0f);
        if ((sqrtf(SQ(this->actor.world.pos.x - this->unk_2A0.x) + SQ(this->actor.world.pos.z - this->unk_2A0.z)) <
             4.0f) &&
            (this->path != NULL)) {
            this->unk_298++;
            if (this->unk_298 >= this->path->count) {
                gSaveContext.save.weekEventReg[84] |= 0x80;
                gSaveContext.save.weekEventReg[83] &= (u8)~4;
                ActorCutscene_Stop(this->unk_2D6);
                Actor_MarkForDeath(&this->actor);
            } else {
                func_809C4B6C(this);
            }
        }
    }
}

void func_809C59A4(EnBomBowlMan* this, PlayState* play) {
    Actor_PickUp(&this->actor, play, GI_BOMBERS_NOTEBOOK, 300.0f, 300.0f);
    this->unk_29C = 1;
    this->actionFunc = func_809C59F0;
}

void func_809C59F0(EnBomBowlMan* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        if (this->unk_2F6 == ENBOMBOWLMAN_F0_0) {
            this->unk_2C0 = 3;
            this->actor.textId = D_809C618C[this->unk_2C0];
        } else {
            this->actor.textId = 0x716;
        }
        func_800B8500(&this->actor, play, 400.0f, 400.0f, -1);
        this->actionFunc = func_809C5AA4;
    } else {
        Actor_PickUp(&this->actor, play, GI_BOMBERS_NOTEBOOK, 300.0f, 300.0f);
    }
}

void func_809C5AA4(EnBomBowlMan* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (this->unk_2F6 == ENBOMBOWLMAN_F0_0) {
            this->actionFunc = func_809C4DA4;
        } else {
            this->actionFunc = func_809C5598;
        }
    } else {
        func_800B8500(&this->actor, play, 400.0f, 400.0f, -1);
    }
}

void func_809C5B1C(EnBomBowlMan* this, PlayState* play) {
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->unk_2D2);
    } else if (!ActorCutscene_GetCanPlayNext(this->unk_2D2)) {
        ActorCutscene_SetIntentToPlay(this->unk_2D2);
    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D2, &this->actor);
        func_809C5BA0(this);
    }
}

void func_809C5BA0(EnBomBowlMan* this) {
    if (this->unk_2F4 != 0) {
        func_809C493C(this, 0, 1.0f);
    } else {
        this->unk_2F8 = 0;
    }
    this->unk_29C = 2;
    this->actionFunc = func_809C5BF4;
}

void func_809C5BF4(EnBomBowlMan* this, PlayState* play) {
    f32 sp2C = this->skelAnime.curFrame;
    s32 subCam;

    if ((D_809C6104 != 0) && (this->unk_2F8 != 15)) {
        func_809C493C(this, 15, 1.0f);
    }

    if ((this->unk_2F8 == 15) && (this->unk_2C4 <= sp2C)) {
        func_809C493C(this, 0, 1.0f);
    }

    if (D_809C6100 != 0) {
        if ((this->unk_2F8 == 0) && (D_809C6100 == (this->unk_2F4 + 1))) {
            func_809C493C(this, 11, 1.0f);
        }

        if ((this->unk_2F8 == 11) && (this->unk_2C4 <= sp2C)) {
            func_809C493C(this, 12, 1.0f);
            D_809C6100++;
        }

        if (this->unk_2F4 == 0) {
            subCam = Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(this->unk_2D2));

            if (D_809C6100 > 5) {
                Player* player = GET_PLAYER(play);

                func_801477B4(play);
                Camera_SetTargetActor(subCam, &this->unk_2D8[0]->actor);
                func_809C493C(this, 13, 1.0f);
                D_809C6100 = 0;
                if (player->transformation == PLAYER_FORM_HUMAN) {
                    this->unk_2C0 = 5;
                    Message_StartTextbox(play, D_809C618C[this->unk_2C0], &this->actor);
                } else {
                    this->unk_2C0 = 3;
                    Message_StartTextbox(play, D_809C6198[this->unk_2C0], &this->actor);
                }
                this->unk_29C = 0;
                this->actionFunc = func_809C4DA4;
            } else {
                s32 idx = D_809C6100 - 1;

                Camera_SetTargetActor(subCam, &this->unk_2D8[1 + idx]->actor);
            }
        }
    }
}

void EnBomBowlMan_Update(Actor* thisx, PlayState* play) {
    EnBomBowlMan* this = THIS;

    if (this->unk_2BA != 0) {
        this->unk_2BA--;
    }

    if (this->unk_2BC != 0) {
        this->unk_2BC--;
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    func_809C49CC(this);
    Actor_SetFocus(&this->actor, 20.0f);

    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Math_SmoothStepToS(&this->unk_28A, this->unk_290, 1, 0x1388, 0);
    Math_SmoothStepToS(&this->unk_288, this->unk_28E, 1, 0x3E8, 0);

    if (this->unk_2F2 == 0) {
        this->unk_2F0++;
        if (this->unk_2F0 >= 3) {
            this->unk_2F0 = 0;
            this->unk_2F2 = (s32)Rand_ZeroFloat(60.0f) + 20;
        }
    }
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
}

s32 EnBomBowlMan_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnBomBowlMan* this = THIS;

    if (limbIndex == 15) {
        *dList = NULL;
    }

    if (limbIndex == 17) {
        rot->x += this->unk_28A;
    }

    if ((limbIndex == 19) && (this->unk_2F6 == ENBOMBOWLMAN_F0_2)) {
        *dList = NULL;
    }

    if ((limbIndex == 20) && (this->unk_2F6 == ENBOMBOWLMAN_F0_0)) {
        *dList = NULL;
    }
    return false;
}

#include "overlays/ovl_En_Bom_Bowl_Man/ovl_En_Bom_Bowl_Man.c"

TexturePtr D_809C6200[] = {
    gEnBomBowlMan_D_809C61E0, gEnBomBowlMan_D_809C61F0, gEnBomBowlMan_D_809C61F0,
    gEnBomBowlMan_D_809C61F0, gEnBomBowlMan_D_809C61F0,
};

TexturePtr D_809C6214[] = {
    object_cs_Tex_00C520,
    object_cs_Tex_00CD20,
    object_cs_Tex_00D520,
};

TexturePtr D_809C6220[] = {
    object_cs_Tex_00E620, object_cs_Tex_00EA20, object_cs_Tex_00EE20, object_cs_Tex_00DD20, object_cs_Tex_00F220,
};

void EnBomBowlMan_Draw(Actor* thisx, PlayState* play) {
    EnBomBowlMan* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_809C6214[this->unk_2F0]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_809C6220[this->unk_2F4]));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_809C6200[this->unk_2F4]));

    Scene_SetRenderModeXlu(play, 0, 1);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnBomBowlMan_OverrideLimbDraw, NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
