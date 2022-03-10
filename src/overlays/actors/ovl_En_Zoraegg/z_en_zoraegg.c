/*
 * File: z_en_zoraegg.c
 * Overlay: ovl_En_Zoraegg
 * Description: Zora Egg
 */

#include "z_en_zoraegg.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_zoraegg/object_zoraegg.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnZoraegg*)thisx)

void EnZoraegg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80B319A8(GlobalContext* globalCtx);
void func_80B32084(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32094(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B320E0(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B321D0(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32228(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B322BC(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32390(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B324B0(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32644(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B326F4(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32820(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32928(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32A88(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32B10(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32B3C(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32B70(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32BB8(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32C34(EnZoraegg* this, GlobalContext* globalCtx);
void func_80B32D08(EnZoraegg* this, GlobalContext* globalCtx);

const ActorInit En_Zoraegg_InitVars = {
    ACTOR_EN_ZORAEGG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZORAEGG,
    sizeof(EnZoraegg),
    (ActorFunc)EnZoraegg_Init,
    (ActorFunc)EnZoraegg_Destroy,
    (ActorFunc)EnZoraegg_Update,
    (ActorFunc)EnZoraegg_Draw,
};

void func_80B31590(EnZoraegg* this) {
    this->actor.shape.yOffset = 0.0f;

    if (this->actor.home.rot.x == 0) {
        this->actor.scale.x = 0.4f;
    } else {
        this->actor.scale.x = this->actor.home.rot.x * 0.04f;
    }

    if (this->actor.home.rot.z == 0) {
        this->actor.scale.z = 0.4f;
    } else {
        this->actor.scale.z = this->actor.home.rot.z * 0.04f;
    }

    this->actor.shape.rot.z = 0;
    this->actor.scale.y = 0.4f;
    this->actor.draw = NULL;
    this->actor.shape.rot.y = this->actor.shape.rot.z;
    this->actor.shape.rot.x = this->actor.shape.rot.z;
}

void EnZoraegg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnZoraegg* this = THIS;
    u16 sp40[] = { 457, 458, 459, 460, 461, 462, 464 };

    Actor_SetScale(&this->actor, 0.006f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_zoraegg_Skel_004C90, &object_zoraegg_Anim_005098,
                       this->jointTable, this->morphTable, 7);
    Animation_PlayLoop(&this->skelAnime, &object_zoraegg_Anim_005098);
    ActorShape_Init(&this->actor.shape, 1100.0f, NULL, 0.0f);

    this->actionFunc = func_80B32084;

    this->unk_1ED = 255;
    this->unk_1EC = 0;
    this->unk_1EA = 0;

    this->unk_1E0 = 1.0f;
    this->unk_1E4 = 0.0f;
    this->actor.velocity.y = -10.0f;
    this->actor.terminalVelocity = -10.0f;
    this->actor.gravity = -5.0f;

    switch (ENZORAEGG_GET_1F(&this->actor)) {
        case ENZORAEGG_1F_0:
            if (Flags_GetSwitch(globalCtx, ENZORAEGG_GET_FE00(&this->actor))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case ENZORAEGG_1F_17:
            if (func_80B319A8(globalCtx) >= 7) {
                Actor_MarkForDeath(&this->actor);
                this->actor.home.rot.z = 1;
                return;
            }
            break;

        case ENZORAEGG_1F_3:
        case ENZORAEGG_1F_4:
        case ENZORAEGG_1F_5:
        case ENZORAEGG_1F_6:
        case ENZORAEGG_1F_7:
        case ENZORAEGG_1F_8:
        case ENZORAEGG_1F_9:
            if (gSaveContext.save.weekEventReg[19] & 0x40) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case ENZORAEGG_1F_10:
        case ENZORAEGG_1F_11:
        case ENZORAEGG_1F_12:
        case ENZORAEGG_1F_13:
        case ENZORAEGG_1F_14:
        case ENZORAEGG_1F_15:
        case ENZORAEGG_1F_16:
            if (!(gSaveContext.save.weekEventReg[19] & 0x40)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
    }

    switch (ENZORAEGG_GET_1F(&this->actor)) {
        case ENZORAEGG_1F_0:
            this->actionFunc = func_80B320E0;
            this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
            this->actor.targetMode = 3;
            break;

        case ENZORAEGG_1F_1:
            this->actionFunc = func_80B322BC;
            func_80B31590(this);
            break;

        case ENZORAEGG_1F_2:
            this->actionFunc = func_80B32390;
            func_80B31590(this);
            break;

        case ENZORAEGG_1F_3:
        case ENZORAEGG_1F_4:
        case ENZORAEGG_1F_5:
        case ENZORAEGG_1F_6:
        case ENZORAEGG_1F_7:
        case ENZORAEGG_1F_8:
        case ENZORAEGG_1F_9:
            this->actorActionCmd = sp40[(ENZORAEGG_GET_1F(&this->actor)) - ENZORAEGG_1F_3];
            Animation_PlayOnce(&this->skelAnime, &object_zoraegg_Anim_001E08);
            this->unk_1EC = 1;
            this->unk_1EE = 0;
            this->unk_1EF = 0;
            this->actionFunc = func_80B32B10;
            if (((ENZORAEGG_GET_1F(&this->actor)) - ENZORAEGG_1F_3) >= func_80B319A8(globalCtx)) {
                this->actionFunc = func_80B32B3C;
                this->actor.draw = NULL;
            }
            break;

        case ENZORAEGG_1F_10:
        case ENZORAEGG_1F_11:
        case ENZORAEGG_1F_12:
        case ENZORAEGG_1F_13:
        case ENZORAEGG_1F_14:
        case ENZORAEGG_1F_15:
        case ENZORAEGG_1F_16:
            this->actorActionCmd = sp40[(ENZORAEGG_GET_1F(&this->actor)) - ENZORAEGG_1F_10];
            this->unk_1EC = 2;
            this->actionFunc = func_80B324B0;
            Animation_PlayLoop(&this->skelAnime, &object_zoraegg_Anim_004FE4);
            this->unk_1EE = 0;
            this->unk_1ED = 0;
            this->unk_1EA |= 3;
            break;

        case ENZORAEGG_1F_17:
            Actor_SetScale(&this->actor, 0.0006f);
            this->actionFunc = func_80B32D08;
            this->actor.world.pos.y -= this->actor.shape.yOffset * this->actor.scale.y;
            this->actor.shape.rot.x = 0;
            this->actor.velocity.y = 0.0f;
            this->actor.terminalVelocity = -10.0f;
            this->actor.gravity = -1.0f;
            break;
    }
}

void EnZoraegg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 func_80B319A8(GlobalContext* globalCtx) {
    return gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 & 7;
}

void func_80B319D0(GlobalContext* globalCtx, s32 arg1) {
    if ((arg1 < 8) && (arg1 >= 0)) {
        gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 &= ~7;
        gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 |= arg1;
    }
}

void func_80B31A34(EnZoraegg* this) {
    s32 curFrame;

    if (this->unk_1EA & 1) {
        this->unk_1EE = this->unk_1EF = 100;
        return;
    }

    curFrame = this->skelAnime.curFrame;
    if (curFrame < 6) {
        this->unk_1EE = 0;
        this->unk_1EF = 0;
    } else if (curFrame < 93) {
        this->unk_1EE = Math_SinS((curFrame * 0xBC) - 0x468) * 100.0f;
        if (curFrame >= 89) {
            this->unk_1EF = Math_SinS((curFrame * 0x1000) - (0x59 * 0x1000)) * 100.0f;
        } else {
            this->unk_1EF = 0;
        }
    } else {
        this->unk_1EE = this->unk_1EF = 100;
    }
}

void func_80B31C40(EnZoraegg* this, GlobalContext* globalCtx) {
    Actor_MoveWithGravity(&this->actor);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.focus.pos.y += 10.0f;
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
}

Actor* func_80B31CB4(GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_EN_ZORAEGG) && (ENZORAEGG_GET_1F(actor) == ENZORAEGG_1F_17) &&
            (actor->home.rot.z == 0)) {
            actor->home.rot.z = 1;
            return actor;
        }
        actor = actor->next;
    }
    return NULL;
}

Actor* func_80B31D14(GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_EN_ZORAEGG) && (ENZORAEGG_GET_1F(actor) == ENZORAEGG_1F_3)) {
            return actor;
        }
        actor = actor->next;
    }
    return NULL;
}

void func_80B31D64(EnZoraegg* this, GlobalContext* globalCtx, s32 arg2, f32 arg3) {
    Vec3f sp24 = this->actor.world.pos;

    sp24.y += arg3;

    if ((globalCtx->gameplayFrames & arg2) == 0) {
        EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 0.0f, 0.0f, 10.0f, 0.13f);
    }
}

void func_80B31E00(EnZoraegg* this) {
    f32 sp20[] = {
        1.0f,
        1.075f,
        1.15f,
        1.075f,
    };

    if (this->unk_1E8 < 112) {
        if (this->unk_1E8 > 10) {
            this->unk_1ED = (s32)((112.0f - this->unk_1E8) * 2.5f) & 0xFF;
        }
    } else {
        this->unk_1ED = 0;
    }

    if (this->unk_1E8 < 10) {
        this->unk_1E0 = sp20[this->unk_1E8 & 3];
    } else if (this->unk_1E8 < 22) {
        this->unk_1E0 = (Math_SinS((this->unk_1E8 - 10.0f) * (4096.0f / 3)) * 0.8f) + 1.0f;
    } else if (this->unk_1E8 < 26) {
        this->unk_1E0 = (Math_CosS((this->unk_1E8 - 22.0f) * 4096.0f) * 0.8f) + 1.0f;
    } else if (this->unk_1E8 < 32) {
        this->unk_1E0 = sp20[(this->unk_1E8 - 1) & 3];
    } else if (this->unk_1E8 < 47) {
        this->unk_1E0 = 1.0f;
    } else if (this->unk_1E8 < 53) {
        this->unk_1E0 = sp20[(this->unk_1E8 - 2) & 3];
    } else if (this->unk_1E8 < 74) {
        this->unk_1E0 = 1.0f - ((this->unk_1E8 - 53.0f) * (1.0f / 105));
    } else if (this->unk_1E8 < 112) {
        this->unk_1E0 = (this->unk_1E0 * 0.9f) + 0.15f;
    }

    if ((this->unk_1E8 == 111) || (this->unk_1E8 == 32)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ZORA_KIDS_BORN);
    }
}

void func_80B32084(EnZoraegg* this, GlobalContext* globalCtx) {
}

void func_80B32094(EnZoraegg* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 2) {
        this->actionFunc = func_80B320E0;
    }
    func_80B31C40(this, globalCtx);
}

void func_80B320E0(EnZoraegg* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        Flags_SetSwitch(globalCtx, ENZORAEGG_GET_FE00(&this->actor));
        Actor_MarkForDeath(&this->actor);
    } else if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B32094;
        Message_StartTextbox(globalCtx, 0x24B, &this->actor);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_MAX, 80.0f, 60.0f);
        if (this->actor.isTargeted) {
            func_800B8614(&this->actor, globalCtx, 110.0f);
        }
    }

    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actor.targetMode = 3;
    func_80B31C40(this, globalCtx);
}

void func_80B321D0(EnZoraegg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        this->actionFunc = func_80B322BC;
        func_80B319D0(globalCtx, func_80B319A8(globalCtx) + 1);
    }
}

void func_80B32228(EnZoraegg* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, this->unk_1DC);
        this->actionFunc = func_80B321D0;
    } else {
        if (this->unk_1E8 > 0) {
            this->unk_1E8--;
        } else if (this->unk_1E8 == 0) {
            ActorCutscene_Stop(player->unk_A86);
            player->unk_A86 = -1;
            this->unk_1E8 = -1;
        }

        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80B322BC(EnZoraegg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.cutscene != -1) {
        this->unk_1DC = func_80B31CB4(globalCtx);
        if (this->unk_1DC != NULL) {
            this->unk_1E8 = 3;
            this->actionFunc = func_80B32228;
            return;
        }
    }

    if ((fabsf(player->actor.world.pos.x - this->actor.world.pos.x) < (100.0f * this->actor.scale.x)) &&
        (fabsf(player->actor.world.pos.z - this->actor.world.pos.z) < (100.0f * this->actor.scale.z))) {
        func_8012300C(globalCtx, 25);
    }
}

void func_80B32390(EnZoraegg* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        Actor* temp_v0 = func_80B31D14(globalCtx);

        if (temp_v0 != NULL) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, temp_v0);
            gSaveContext.eventInf[3] |= 8;
            Actor_MarkForDeath(&this->actor);
        }
    } else if ((func_80B319A8(globalCtx) >= 7) &&
               (fabsf(player->actor.world.pos.x - this->actor.world.pos.x) < (100.0f * this->actor.scale.x)) &&
               (fabsf(player->actor.world.pos.z - this->actor.world.pos.z) < (100.0f * this->actor.scale.z)) &&
               (fabsf(player->actor.world.pos.y - this->actor.world.pos.y) < 30.0f)) {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80B324B0(EnZoraegg* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_CheckActorAction(globalCtx, this->actorActionCmd)) {
        if (this->unk_1EA & 4) {
            if (Cutscene_CheckActorAction(globalCtx, this->actorActionCmd) &&
                (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd)]->action ==
                 3)) {
                Animation_PlayLoop(&this->skelAnime, &object_zoraegg_Anim_004FE4);
                this->unk_1EA &= ~4;
            }
        } else {
            if (Cutscene_CheckActorAction(globalCtx, this->actorActionCmd) &&
                (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd)]->action ==
                 4)) {
                Animation_PlayLoop(&this->skelAnime, &object_zoraegg_Anim_004E04);
                this->unk_1EA |= 4;
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx,
                                      Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd));

        if ((this->unk_1EA & 4) && Animation_OnFrame(&this->skelAnime, this->unk_1E4)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ZORA_KIDS_SWIM_1);
            this->unk_1E4 = Rand_ZeroFloat(5.0f);
        }
    } else if (this->unk_1EA & 4) {
        Animation_PlayLoop(&this->skelAnime, &object_zoraegg_Anim_004FE4);
        this->unk_1EA &= ~4;
    }
}

void func_80B32644(EnZoraegg* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_PlayLoop(&this->skelAnime, &object_zoraegg_Anim_004FE4);
        this->unk_1EE = 0;
        this->unk_1EA |= 2;
    }

    if (!Cutscene_CheckActorAction(globalCtx, this->actorActionCmd)) {
        this->actionFunc = func_80B324B0;
    } else {
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx,
                                      Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd));

        if (this->unk_1EE > 25) {
            this->unk_1EE -= 25;
        } else {
            this->unk_1EE = 0;
        }
    }
}

void func_80B326F4(EnZoraegg* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);

    if (Cutscene_CheckActorAction(globalCtx, this->actorActionCmd) &&
        (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd)]->action == 3)) {
        Animation_Change(&this->skelAnime, &object_zoraegg_Anim_004D20, 1.0f, 0.0f,
                         Animation_GetLastFrame(&object_zoraegg_Anim_004D20), 2, 5.0f);
        this->unk_1E8 = 0;
        this->actionFunc = func_80B32644;
        gSaveContext.save.weekEventReg[19] |= 0x40;
        this->unk_1EC = 2;
        this->unk_1EE = 100;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ZORA_KIDS_SWIM_2);
    }

    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx,
                                  Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd));

    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ZORA_KIDS_SWIM_1);
    }
}

void func_80B32820(EnZoraegg* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_1E8 >= 2) {
            this->actionFunc = func_80B326F4;
            Animation_Change(&this->skelAnime, &object_zoraegg_Anim_005098, 1.0f, 0.0f,
                             Animation_GetLastFrame(&object_zoraegg_Anim_005098), 0, 10.0f);
            this->unk_1E8 = 0;
            SkelAnime_Update(&this->skelAnime);
            return;
        }

        Animation_PlayOnce(&this->skelAnime, &object_zoraegg_Anim_0005D4);
        this->unk_1E8 += 1;
        SkelAnime_Update(&this->skelAnime);
    }

    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx,
                                  Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd));

    if (Animation_OnFrame(&this->skelAnime, 16.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ZORA_KIDS_SWIM_0);
    }
}

void func_80B32928(EnZoraegg* this, GlobalContext* globalCtx) {
    if (this->unk_1E8 < 112) {
        this->unk_1E8++;
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_PlayOnce(&this->skelAnime, &object_zoraegg_Anim_0005D4);
        this->unk_1EA |= 1;
        this->actionFunc = func_80B32820;
        this->unk_1E8 = 0;
        this->actor.velocity.y = 0.0f;
        return;
    }

    func_80B31A34(this);
    func_80B31E00(this);

    if (this->unk_1E8 < 112) {
        if ((this->unk_1E8 >= 69) && (this->unk_1E8 < 72)) {
            func_80B31D64(this, globalCtx, 0, 0.0f);
            func_80B31D64(this, globalCtx, 0, 0.0f);
            func_80B31D64(this, globalCtx, 0, 0.0f);
        } else {
            func_80B31D64(this, globalCtx, 0xD, 0.0f);
        }
    }

    Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx,
                                  Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd));

    if (Animation_OnFrame(&this->skelAnime, 97.0f) || Animation_OnFrame(&this->skelAnime, 101.0f) ||
        Animation_OnFrame(&this->skelAnime, 105.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ZORA_KIDS_SWIM_1);
    }
}

void func_80B32A88(EnZoraegg* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, this->actorActionCmd) &&
        (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, this->actorActionCmd)]->action == 2)) {
        this->unk_1E8 = 0;
        this->actionFunc = func_80B32928;
    }
    func_80B31D64(this, globalCtx, 13, 0.0f);
}

void func_80B32B10(EnZoraegg* this, GlobalContext* globalCtx) {
    if (gSaveContext.eventInf[3] & 8) {
        this->actionFunc = func_80B32A88;
    }
}

void func_80B32B3C(EnZoraegg* this, GlobalContext* globalCtx) {
    if (gSaveContext.eventInf[3] & 8) {
        this->actionFunc = func_80B32A88;
        this->actor.draw = EnZoraegg_Draw;
    }
}

void func_80B32B70(EnZoraegg* this, GlobalContext* globalCtx) {
    func_80B31C40(this, globalCtx);
    if (Cutscene_CheckActorAction(globalCtx, 0x1C9)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B32BB8(EnZoraegg* this, GlobalContext* globalCtx) {
    func_80B31C40(this, globalCtx);
    func_80B31D64(this, globalCtx, 13, 0.0f);

    if (this->actor.bgCheckFlags & 0x1) {
        this->actionFunc = func_80B32B70;
    }

    if (Cutscene_CheckActorAction(globalCtx, 0x1C9)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B32C34(EnZoraegg* this, GlobalContext* globalCtx) {
    WaterBox* sp34;
    f32 sp30;
    s32 pad;

    Actor_MoveWithGravity(&this->actor);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.focus.pos.y += 10.0f;
    sp30 = this->actor.world.pos.y;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp30,
                             &sp34)) {
        if ((this->actor.world.pos.y + 50.0f) < sp30) {
            this->actionFunc = func_80B32BB8;
        }

        func_80B31D64(this, globalCtx, 0, -20.0f);
        func_80B31D64(this, globalCtx, 0, -20.0f);
    }
}

void func_80B32D08(EnZoraegg* this, GlobalContext* globalCtx) {
    WaterBox* sp44;
    f32 sp40;
    Vec3f sp34;
    s32 pad;

    Actor_MoveWithGravity(&this->actor);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.focus.pos.y += 10.0f;
    sp40 = this->actor.world.pos.y;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp40,
                             &sp44)) {
        if (this->actor.world.pos.y < sp40) {
            sp34.x = this->actor.world.pos.x;
            sp34.y = sp40;
            sp34.z = this->actor.world.pos.z;

            EffectSsGRipple_Spawn(globalCtx, &sp34, 150, 500, 0);
            EffectSsGSplash_Spawn(globalCtx, &sp34, NULL, NULL, 0, 200);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIVE_INTO_WATER_L);

            this->actionFunc = func_80B32C34;
            this->actor.velocity.y = -1.0f;
            this->actor.terminalVelocity = -1.0f;
            this->actor.gravity = -1.0f;
        }
    }

    if (this->actor.scale.x < 0.006f) {
        Actor_SetScale(&this->actor, this->actor.scale.x + 0.0012f);
    }

    if (this->actor.scale.x > 0.006f) {
        Actor_SetScale(&this->actor, 0.006f);
    }
}

void EnZoraegg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnZoraegg* this = THIS;

    this->actionFunc(this, globalCtx);

    if (DECR(this->unk_1F4) == 0) {
        this->unk_1F4 = Rand_S16Offset(60, 60);
    }

    this->unk_1F2 = this->unk_1F4;
    if (this->unk_1F2 >= 3) {
        this->unk_1F2 = 0;
    }
}

void func_80B32F04(Actor* thisx, GlobalContext* globalCtx) {
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    EnZoraegg* this = THIS;
    s32 pad[3];
    s16 sp62;
    s16 sp60;
    f32 temp_f2;
    Gfx* gfx;
    Vec3f sp4C;
    s32 pad2;

    Matrix_StatePush();

    sp4C = GET_ACTIVE_CAM(globalCtx)->eye;

    sp62 = Math_Vec3f_Yaw(&sp4C, &this->actor.focus.pos);
    sp60 = -Math_Vec3f_Pitch(&sp4C, &this->actor.focus.pos);

    sp74 = -((15.0f * Math_SinS(sp62)) * Math_CosS(sp60));
    sp78 = -(15.0f * Math_SinS(sp60));
    sp7C = -((15.0f * Math_CosS(sp62)) * Math_CosS(sp60));

    Matrix_InsertTranslation(this->actor.world.pos.x + sp74, this->actor.world.pos.y + sp78 + 6.0f,
                             temp_f2 = this->actor.world.pos.z + sp7C, 0);

    sp7C = Math_SinS(globalCtx->gameplayFrames * 0x4000);

    Matrix_Scale(this->actor.scale.x * (((sp7C + 1.0f) * 0.1f) + 9.0f),
                 this->actor.scale.y * (((sp7C + 1.0f) * 0.1f) + 9.0f),
                 this->actor.scale.z * (((sp7C + 1.0f) * 0.1f) + 9.0f), 1);

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_XLU_DISP;
    gfx = func_8012C868(gfx);

    gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 4, 4, 0x00000080);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    gSPDisplayList(gfx++, gameplay_keep_DL_029CB0);

    gDPSetPrimColor(gfx++, 0, 0, 120, 180, 200, (s32)(this->unk_1ED * (20.0f / 51)));
    gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, gameplay_keep_DL_029CF0);

    POLY_XLU_DISP = gfx;

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B331C8(Actor* thisx, GlobalContext* globalCtx) {
    EnZoraegg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    Matrix_Scale(this->unk_1E0, this->unk_1E0, this->unk_1E0, MTXMODE_APPLY);

    if (this->unk_1ED >= 254) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(POLY_OPA_DISP++, object_zoraegg_DL_005250);
    } else {
        func_8012C304(POLY_XLU_DISP++);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_1ED);
        gSPDisplayList(POLY_XLU_DISP++, object_zoraegg_DL_005250);
    }

    Matrix_StatePop();

    func_80B32F04(thisx, globalCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 EnZoraegg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnZoraegg* this = THIS;

    switch (this->unk_1EC) {
        case 1:
            if ((limbIndex != 1) && (limbIndex != 3) && (limbIndex != 4)) {
                *dList = NULL;
            }
            break;

        case 2:
            if ((limbIndex != 1) && (limbIndex != 3)) {
                *dList = NULL;
            }
            break;
    }
    return false;
}

void func_80B333DC(GlobalContext* globalCtx, Gfx** dList, f32 arg2) {
    Matrix_StatePush();
    Matrix_Scale(arg2, arg2, arg2, MTXMODE_APPLY);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, *dList);

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnZoraegg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnZoraegg* this = THIS;
    f32 temp_f20;
    f32 temp_f2;

    switch (this->unk_1EC) {
        case 1:
            switch (limbIndex) {
                case 2:
                    temp_f20 = this->unk_1EE * 0.01f;
                    Matrix_StatePush();
                    Matrix_Scale(temp_f20, temp_f20, temp_f20, MTXMODE_APPLY);

                    OPEN_DISPS(globalCtx->state.gfxCtx);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_OPA_DISP++, *dList);

                    CLOSE_DISPS(globalCtx->state.gfxCtx);
                    break;

                case 4:
                    Matrix_StatePop();
                    break;

                case 5:
                case 6:
                    temp_f20 = this->unk_1EF * 0.01f;
                    func_80B333DC(globalCtx, dList, temp_f20);
                    break;
            }
            break;

        case 2:
            switch (limbIndex) {
                case 2:
                    temp_f20 = (this->unk_1EE * 0.005f) + 0.5f;
                    Matrix_StatePush();
                    Matrix_Scale(1.0f, temp_f20, temp_f20, MTXMODE_APPLY);

                    OPEN_DISPS(globalCtx->state.gfxCtx);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_OPA_DISP++, *dList);

                    CLOSE_DISPS(globalCtx->state.gfxCtx);
                    break;

                case 4:
                    temp_f2 = 1.0f / ((this->unk_1EE * 0.005f) + 0.5f);
                    temp_f20 = (this->unk_1EE * 0.0035f) + 0.65f;
                    Matrix_Scale(1.0f, temp_f20 * temp_f2, temp_f2, MTXMODE_APPLY);

                    OPEN_DISPS(globalCtx->state.gfxCtx);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_OPA_DISP++, *dList);

                    CLOSE_DISPS(globalCtx->state.gfxCtx);

                    Matrix_StatePop();
                    break;

                case 5:
                case 6:
                    temp_f20 = this->unk_1EE * 0.01f;
                    func_80B333DC(globalCtx, dList, temp_f20);
                    break;
            }
            break;
    }
}

TexturePtr D_80B33950[] = { object_zoraegg_Tex_003430, object_zoraegg_Tex_004430, object_zoraegg_Tex_004830 };

void func_80B33818(Actor* thisx, GlobalContext* globalCtx) {
    EnZoraegg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B33950[this->unk_1F2]));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnZoraegg_OverrideLimbDraw, EnZoraegg_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnZoraegg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnZoraegg* this = THIS;

    if (this->unk_1ED > 0) {
        func_80B331C8(thisx, globalCtx);
    }

    if (this->unk_1ED != 255) {
        func_80B33818(thisx, globalCtx);
    }
}
