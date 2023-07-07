/*
 * File: z_en_elfgrp.c
 * Overlay: ovl_En_Elfgrp
 * Description: Group of Stray Fairies in Fairy Fountain
 */

#include "z_en_elfgrp.h"
#include "overlays/actors/ovl_En_Elforg/z_en_elforg.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnElfgrp*)thisx)

//! TODO: this file require macros for its uses of weekEventReg

void EnElfgrp_Init(Actor* thisx, PlayState* play);
void EnElfgrp_Destroy(Actor* thisx, PlayState* play);
void EnElfgrp_Update(Actor* thisx, PlayState* play);

s32 func_80A39BD0(PlayState* play, s32 arg2);
s32 func_80A39C1C(PlayState* play, s32 arg1);
void func_80A39DC8(EnElfgrp* this, PlayState* play, s32 arg2, s32 arg3);
void func_80A3A0AC(EnElfgrp* this, PlayState* play);
void func_80A3A0F4(EnElfgrp* this, PlayState* play);
void func_80A3A210(EnElfgrp* this, PlayState* play);
void func_80A3A274(EnElfgrp* this, PlayState* play);
void func_80A3A398(EnElfgrp* this, PlayState* play);
void func_80A3A484(EnElfgrp* this, PlayState* play);
void func_80A3A4AC(EnElfgrp* this, PlayState* play);
void func_80A3A520(EnElfgrp* this, PlayState* play);
void func_80A3A600(EnElfgrp* this, PlayState* play);
void func_80A3A610(EnElfgrp* this, PlayState* play);
void func_80A3A6F4(EnElfgrp* this, PlayState* play);
void func_80A3A77C(EnElfgrp* this, PlayState* play);
void func_80A3A7FC(EnElfgrp* this, PlayState* play);
void func_80A3A8F8(EnElfgrp* this, PlayState* play);

ActorInit En_Elfgrp_InitVars = {
    ACTOR_EN_ELFGRP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElfgrp),
    (ActorFunc)EnElfgrp_Init,
    (ActorFunc)EnElfgrp_Destroy,
    (ActorFunc)EnElfgrp_Update,
    (ActorFunc)NULL,
};

void func_80A396B0(EnElfgrp* this, s32 numCutscenes) {
    while (numCutscenes > 0) {
        if (this->actor.csId == CS_ID_NONE) {
            break;
        }
        this->actor.csId = CutsceneManager_GetAdditionalCsId(this->actor.csId);

        numCutscenes--;
    }
}

void EnElfgrp_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnElfgrp* this = THIS;
    s32 sp24;

    this->unk_147 = ENELFGRP_GET(&this->actor);
    this->unk_148 = 0;
    this->unk_14A = 0;
    this->actor.focus.pos.y += 40.0f;
    this->actor.flags &= ~ACTOR_FLAG_1;

    switch (this->unk_147) {
        case ENELFGRP_1:
        case ENELFGRP_2:
        case ENELFGRP_3:
        case ENELFGRP_4:
            this->unk_148 = this->unk_147 - 1;
            sp24 = func_80A39C1C(play, this->unk_147);
            this->unk_146 = 1 << this->unk_147;

            if (sp24 < 25) {
                func_80A39DC8(this, play, sp24, 0);
            }

            if (sp24 >= 25) {
                this->actionFunc = func_80A3A520;
                func_80A396B0(this, 2);
                return;
            }

            if ((func_80A39BD0(play, this->unk_147) + sp24) >= 25) {
                this->actionFunc = func_80A3A398;

                switch (this->unk_147) {
                    case ENELFGRP_1:
                        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_23_02)) {
                            func_80A396B0(this, 1);
                        } else {
                            this->unk_14A |= 4;
                        }
                        break;

                    case ENELFGRP_2:
                        if (gSaveContext.save.saveInfo.playerData.isDoubleMagicAcquired == true) {
                            func_80A396B0(this, 1);
                        }
                        break;

                    case ENELFGRP_3:
                        if (gSaveContext.save.saveInfo.playerData.doubleDefense) {
                            func_80A396B0(this, 1);
                        }
                        break;

                    case ENELFGRP_4:
                        if (INV_CONTENT(ITEM_SWORD_GREAT_FAIRY) == ITEM_SWORD_GREAT_FAIRY) {
                            func_80A396B0(this, 1);
                        } else {
                            this->unk_14A |= 0x10;
                        }
                        break;
                }
            } else if (func_80A39BD0(play, this->unk_147)) {
                this->actionFunc = func_80A3A7FC;
                this->actor.textId = (this->unk_147 * 3) + 0x581;
            } else {
                this->actionFunc = func_80A3A8F8;
                if ((gSaveContext.save.saveInfo.weekEventReg[9] & this->unk_146)) {
                    this->actor.textId = (this->unk_147 * 3) + 0x580;
                } else {
                    this->actor.textId = (this->unk_147 * 3) + 0x57F;
                }
            }
            break;

        default:
            sp24 = func_80A39C1C(play, 0);
            this->unk_146 = ENELFGRP_1;
            if (sp24 >= 25) {
                this->actionFunc = func_80A3A520;
                if ((this->actor.home.rot.z != 0) && Flags_GetSwitch(play, this->actor.home.rot.z)) {
                    this->actionFunc = func_80A3A600;
                } else if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
                    func_80A396B0(this, 4);
                } else if (INV_CONTENT(ITEM_MASK_DEKU) != ITEM_MASK_DEKU) {
                    func_80A396B0(this, 5);
                } else {
                    this->unk_14A |= 2;
                    func_80A396B0(this, 6);
                }
            } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_08_80)) {
                func_80A39DC8(this, play, 24, 0);
                this->actionFunc = func_80A3A398;
                if (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU) {
                    if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
                        func_80A396B0(this, 2);
                    } else {
                        func_80A396B0(this, 3);
                        this->unk_14A |= 2;
                    }
                } else if (gSaveContext.save.saveInfo.playerData.isMagicAcquired == true) {
                    func_80A396B0(this, 1);
                }
            } else {
                func_80A39DC8(this, play, 24, 0);
                this->actionFunc = func_80A3A8F8;
                if ((gSaveContext.save.saveInfo.weekEventReg[9] & this->unk_146)) {
                    this->actor.textId = 0x580;
                } else {
                    this->actor.textId = 0x578;
                }
                this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
            }
            break;
    }
}

void EnElfgrp_Destroy(Actor* thisx, PlayState* play) {
}

s32 func_80A39BD0(PlayState* play, s32 arg2) {
    if ((arg2 < 1) || (arg2 >= 5)) {
        return 0;
    }

    return (((void)0, gSaveContext.save.saveInfo.inventory.strayFairies[arg2 - 1]) - func_80A39C1C(play, arg2)) + 10;
}

s32 func_80A39C1C(PlayState* play, s32 arg1) {
    // the permanentSceneFlags access here is in the form
    // struct {
    //   u32 clockTown : 1;
    //   u32 fountains[4] : 5;
    // } FairyFountains;
    // where arg1 is:
    //    0: clocktown
    //    1: woodfall,
    //    2: snowhead,
    //    3: great bay,
    //    4: stone tower
    // clocktown is handled separately, and then the fountains are looked up as array indexing

    s32 temp_v1;

    if ((arg1 < 0) || (arg1 >= 5)) {
        return 0;
    }

    if (arg1 == 0) {
        if (gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 & 1) {
            return 25;
        }
        return 24;
    }

    temp_v1 = (gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 >> (((arg1 - 1) * 5) + 1)) & 0x1F;
    if (temp_v1 < 10) {
        temp_v1 = 10;
    } else if (temp_v1 > 25) {
        temp_v1 = 25;
    }
    return temp_v1;
}

void func_80A39CD4(PlayState* play, s32 arg1, s32 arg2) {
    if ((arg1 < 0) || (arg1 > 4) || (arg2 < 10) || (arg2 > 25)) {
        return;
    }

    if (arg1 == 0) {
        if (arg2 == 25) {
            gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 |= 1;
        } else {
            gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 &= ~1;
        }
    } else {
        gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 &= ~(0x1F << ((arg1 * 5) - 4));
        gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 |= arg2 << ((arg1 * 5) - 4);
    }
}

void func_80A39DC8(EnElfgrp* this, PlayState* play, s32 arg2, s32 arg3) {
    s32 pad;
    s32 i;
    Actor* elforg;
    s32 params;
    Vec3f sp6C;
    Player* player = GET_PLAYER(play);

    if (arg3 == 0) {
        this->unk_14A |= 8;
    }

    if (arg3 == 0) {
        sp6C = this->actor.world.pos;
        sp6C.y += 20.0f;
        params = STRAY_FAIRY_PARAMS(0, this->unk_147, STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN);
    } else {
        sp6C = player->actor.world.pos;
        sp6C.y += 20.0f;
        params = STRAY_FAIRY_PARAMS(0, this->unk_147, STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN);
    }

    for (i = 0; i < arg2; i++) {
        elforg = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG, Rand_CenteredFloat(20.0f) + sp6C.x, sp6C.y,
                             Rand_CenteredFloat(20.0f) + sp6C.z, 0, 0, 0, params);
        if (elforg == NULL) {
            continue;
        }
        elforg->home.pos.x = this->actor.home.pos.x;
        elforg->home.pos.y = this->actor.home.pos.y + 20.0f;
        elforg->home.pos.z = this->actor.home.pos.z;
    }
}

s32 func_80A39F50(PlayState* play) {
    Actor* itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    EnElforg* elfOrg;

    while (itemAction != NULL) {
        if ((itemAction->id != ACTOR_EN_ELFORG) ||
            ((STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN) &&
             (STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN))) {
            itemAction = itemAction->next;
            continue;
        }

        elfOrg = (EnElforg*)itemAction;
        if (!(elfOrg->strayFairyFlags & STRAY_FAIRY_FLAG_MOVES_QUICKLY_TO_HOME)) {
            elfOrg->strayFairyFlags |= STRAY_FAIRY_FLAG_MOVES_QUICKLY_TO_HOME;
        }
        itemAction = itemAction->next;
    }

    return 0;
}

s32 func_80A39FBC(PlayState* play) {
    Actor* itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    EnElforg* elfOrg;
    s32 phi_v1 = 30;

    while (itemAction != NULL) {
        if ((itemAction->id != ACTOR_EN_ELFORG) ||
            ((STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN) &&
             (STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN))) {
            itemAction = itemAction->next;
            continue;
        }

        elfOrg = (EnElforg*)itemAction;
        if (!(elfOrg->strayFairyFlags & STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN)) {
            elfOrg->strayFairyFlags |= STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN;
            if (phi_v1 >= 100) {
                return phi_v1;
            }
            elfOrg->secondaryTimer = phi_v1;
            phi_v1 += 5;
        }

        itemAction = itemAction->next;
    }

    return phi_v1;
}

void func_80A3A044(PlayState* play) {
    Actor* itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    EnElforg* elfOrg;

    while (itemAction != NULL) {
        if ((itemAction->id != ACTOR_EN_ELFORG) ||
            ((STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN) &&
             (STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN))) {
            itemAction = itemAction->next;
            continue;
        }

        elfOrg = (EnElforg*)itemAction;
        elfOrg->actor.home.rot.x = 0x14;
        elfOrg->strayFairyFlags |= STRAY_FAIRY_FLAG_SPARKLES_AND_SHRINKS;

        itemAction = itemAction->next;
    }
}

void func_80A3A0AC(EnElfgrp* this, PlayState* play) {
    if (!Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_100)) {
        this->actionFunc = func_80A3A600;
        CutsceneManager_Stop(this->actor.csId);
    }
}

void func_80A3A0F4(EnElfgrp* this, PlayState* play) {
    if (this->unk_144 == 10) {
        Audio_PlaySfx(NA_SE_SY_WHITE_OUT_T);
        if (ENELFGRP_GET(&this->actor) < ENELFGRP_4) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0,
                        ENELFGRP_GET(&this->actor) + ENELFGRP_4);
        } else {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0, 4);
        }
    }

    if ((this->unk_144 > 10) && (this->unk_14A & 1)) {
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_FAIRY_GROUP_FRY - SFX_FLAG);
    }

    if (this->unk_144 == 0) {
        this->actionFunc = func_80A3A0AC;
    }
}

void func_80A3A210(EnElfgrp* this, PlayState* play) {
    if (this->unk_144 == 0) {
        this->actionFunc = func_80A3A0F4;
        func_80A3A044(play);
        this->unk_144 = 30;
    }

    if (this->unk_14A & 1) {
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_FAIRY_GROUP_FRY - SFX_FLAG);
    }
}

void func_80A3A274(EnElfgrp* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_100)) {
        if (this->unk_14A & 1) {
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_PL_CHIBI_FAIRY_HEAL - SFX_FLAG);
        }

        switch (play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_100)]->id) {
            case 2:
                if (!(this->unk_14A & 1)) {
                    if (this->unk_147 == ENELFGRP_0) {
                        func_80A39DC8(this, play, 1, 1);
                    } else {
                        func_80A39DC8(this, play, func_80A39BD0(play, this->unk_147), 1);
                    }
                    this->unk_14A |= 1;
                    func_80A39CD4(play, this->unk_147, 25);
                }
                break;

            case 3:
                func_80A39F50(play);
                this->actionFunc = func_80A3A210;
                this->unk_144 = 90;
                break;
        }
    }
}

void func_80A3A398(EnElfgrp* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
        this->actionFunc = func_80A3A274;
        Flags_UnsetSwitch(play, ENELFGRP_GET_FE00(&this->actor));
        if (this->unk_14A & 2) {
            Item_Give(play, ITEM_MASK_GREAT_FAIRY);
        }

        if ((this->unk_14A & 4) != 0) {
            SET_WEEKEVENTREG(WEEKEVENTREG_23_02);
        }

        if (this->unk_14A & 0x10) {
            Item_Give(play, ITEM_SWORD_GREAT_FAIRY);
        }
        this->unk_14A &= ~8;
    } else if (this->actor.xzDistToPlayer < 350.0f) {
        CutsceneManager_Queue(this->actor.csId);
    }
}

void func_80A3A484(EnElfgrp* this, PlayState* play) {
    if (this->unk_144 == 0) {
        this->actionFunc = func_80A3A0F4;
        this->unk_144 = 30;
    }
}

void func_80A3A4AC(EnElfgrp* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_100)) {
        s32 cueId = play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_100)]->id;

        if (cueId == 3) {
            this->actionFunc = func_80A3A484;
            this->unk_144 = 90;
        }
    }
}

void func_80A3A520(EnElfgrp* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_103)) {
        this->actionFunc = func_80A3A600;
    } else if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
        this->actionFunc = func_80A3A4AC;
        Flags_SetSwitch(play, ENELFGRP_GET_FE00(&this->actor));

        if (this->unk_14A & 2) {
            Item_Give(play, ITEM_MASK_GREAT_FAIRY);
        }

        if (this->actor.home.rot.z != 0) {
            Flags_SetSwitch(play, this->actor.home.rot.z);
        }
    } else if (this->actor.xzDistToPlayer < 350.0f) {
        CutsceneManager_Queue(this->actor.csId);
    }
}

void func_80A3A600(EnElfgrp* this, PlayState* play) {
}

void func_80A3A610(EnElfgrp* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->unk_144 == 60) {
        Magic_Add(play, MAGIC_FILL_TO_CAPACITY);
        gSaveContext.healthAccumulator = 320;
    }

    if (this->unk_144 > 0) {
        player->actor.freezeTimer = 100;
        player->stateFlags1 |= PLAYER_STATE1_20000000;
        Actor_PlaySfx(&this->actor, NA_SE_EV_FAIRY_GROUP_HEAL - SFX_FLAG);
    } else {
        player->actor.freezeTimer = 0;
        player->stateFlags1 &= ~PLAYER_STATE1_20000000;
        this->actionFunc = func_80A3A600;
        this->unk_14A |= 8;
    }
}

void func_80A3A6F4(EnElfgrp* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        player->actor.freezeTimer = 100;
        player->stateFlags1 |= PLAYER_STATE1_20000000;
        this->unk_144 = func_80A39FBC(play);
        this->actionFunc = func_80A3A610;
        this->unk_14A &= ~8;
    }
}

void func_80A3A77C(EnElfgrp* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.freezeTimer = 100;
    player->stateFlags1 |= PLAYER_STATE1_20000000;
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        this->unk_144 = func_80A39FBC(play);
        this->actionFunc = func_80A3A610;
        this->unk_14A &= ~8;
    }
}

void func_80A3A7FC(EnElfgrp* this, PlayState* play) {
    s32 temp_s0;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        gSaveContext.save.saveInfo.weekEventReg[9] |= this->unk_146;
        this->actionFunc = func_80A3A6F4;
        temp_s0 = func_80A39BD0(play, this->unk_147);
        func_80A39DC8(this, play, temp_s0, 1);
        temp_s0 += func_80A39C1C(play, this->unk_147);
        if (temp_s0 > 25) {
            temp_s0 = 25;
        }
        func_80A39CD4(play, this->unk_147, temp_s0);
    } else if (this->actor.xzDistToPlayer < 280.0f) {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, play, 300.0f);
    }
}

void func_80A3A8F8(EnElfgrp* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        gSaveContext.save.saveInfo.weekEventReg[9] |= this->unk_146;
        this->actionFunc = func_80A3A6F4;
        return;
    }

    if (this->unk_147 != ENELFGRP_0) {
        if (func_80A39BD0(play, this->unk_147) > 0) {
            this->actionFunc = func_80A3A7FC;
            return;
        }
    }

    if (this->actor.xzDistToPlayer < 30.0f) {
        if (GET_PLAYER_FORM == PLAYER_FORM_DEKU) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            player->actor.freezeTimer = 100;
            player->stateFlags1 |= PLAYER_STATE1_20000000;
            Message_StartTextbox(play, this->actor.textId, &this->actor);
            this->actionFunc = func_80A3A77C;
            gSaveContext.save.saveInfo.weekEventReg[9] |= this->unk_146;
        } else {
            this->actor.flags |= ACTOR_FLAG_10000;
            func_800B8614(&this->actor, play, 100.0f);
        }
    } else {
        this->actor.flags &= ~ACTOR_FLAG_10000;
    }
}

void EnElfgrp_Update(Actor* thisx, PlayState* play) {
    EnElfgrp* this = THIS;

    this->actionFunc(this, play);

    if (this->unk_14A & 8) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_FAIRY_GROUP_FRY - SFX_FLAG);
    }

    if (this->unk_144 != 0) {
        this->unk_144--;
    }
}
