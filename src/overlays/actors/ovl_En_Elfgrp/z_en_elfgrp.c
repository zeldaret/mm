/*
 * File: z_en_elfgrp.c
 * Overlay: ovl_En_Elfgrp
 * Description: Manager for group of Stray Fairies and Great Fairy in Great Fairy Fountains
 */

#include "z_en_elfgrp.h"
#include "overlays/actors/ovl_En_Elforg/z_en_elforg.h"
#include "overlays/actors/ovl_Demo_Effect/z_demo_effect.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnElfgrp*)thisx)

void EnElfgrp_Init(Actor* thisx, PlayState* play);
void EnElfgrp_Destroy(Actor* thisx, PlayState* play);
void EnElfgrp_Update(Actor* thisx, PlayState* play);

s32 func_80A39BD0(PlayState* play, s32 type);
s32 func_80A39C1C(PlayState* play, s32 type);
void EnElfgrp_SpawnStrayFairies(EnElfgrp* this, PlayState* play, s32 count, s32 fairyType);
// void func_80A3A0AC(EnElfgrp* this, PlayState* play);
// void func_80A3A0F4(EnElfgrp* this, PlayState* play);
// void func_80A3A210(EnElfgrp* this, PlayState* play);
// void func_80A3A274(EnElfgrp* this, PlayState* play);
void func_80A3A398(EnElfgrp* this, PlayState* play);
// void func_80A3A484(EnElfgrp* this, PlayState* play);
// void func_80A3A4AC(EnElfgrp* this, PlayState* play);
void func_80A3A520(EnElfgrp* this, PlayState* play);
void EnElfgrp_DoNothing(EnElfgrp* this, PlayState* play);
// void func_80A3A610(EnElfgrp* this, PlayState* play);
// void func_80A3A6F4(EnElfgrp* this, PlayState* play);
// void func_80A3A77C(EnElfgrp* this, PlayState* play);
void func_80A3A7FC(EnElfgrp* this, PlayState* play);
void func_80A3A8F8(EnElfgrp* this, PlayState* play);

//! State flags
#define ELFGRP_STATE_0 (1 << 0)
#define ELFGRP_STATE_1 (1 << 1)
#define ELFGRP_STATE_2 (1 << 2)
#define ELFGRP_STATE_3 (1 << 3)
#define ELFGRP_STATE_4 (1 << 4)

//! Used for the type in EnElfgrp_SpawnStrayFairies()
typedef enum {
    /* 0 */ SPAWNED_STRAY_FAIRY_TYPE_PRESENT,  //!< STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN
    /* 1 */ SPAWNED_STRAY_FAIRY_TYPE_RETURNING //!< STRAY_FAIRY_TYPE_RETURNING_TO_FOUNTAIN
} ElfgrpSpawnedFairyTypes;

const ActorInit En_Elfgrp_InitVars = {
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

/**
 * Set the actor's cutscene to a later one, or -1 if run out.
 *
 * @note This is only expected to be called in Init when this actor has the first cutscene set, but can also work for
 * later cutscenes if \p numberToSkip is set correcly.
 *
 * @param numberToSkip Number of cutscenes in the list to skip forward to set this one.
 */
void EnElfgrp_SetCutscene(EnElfgrp* this, s32 numberToSkip) {
    while (numberToSkip > 0) {
        if (this->actor.cutscene == -1) {
            break;
        }
        this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);

        numberToSkip--;
    }
}

void EnElfgrp_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnElfgrp* this = THIS;
    s32 sp24;

    this->type = ENELFGRP_GET_TYPE(&this->actor);
    this->unk_148 = 0;
    this->stateFlags = 0;
    this->actor.focus.pos.y += 40.0f;
    this->actor.flags &= ~ACTOR_FLAG_1;

    switch (this->type) {
        case ENELFGRP_TYPE_POWER:
        case ENELFGRP_TYPE_WISDOM:
        case ENELFGRP_TYPE_COURAGE:
        case ENELFGRP_TYPE_KINDNESS:
            this->unk_148 = this->type - 1;
            sp24 = func_80A39C1C(play, this->type);
            this->talkedOnceFlag = 1 << this->type;

            if (sp24 < STRAY_FAIRY_TOTAL) {
                EnElfgrp_SpawnStrayFairies(this, play, sp24, SPAWNED_STRAY_FAIRY_TYPE_PRESENT);
            }

            if (sp24 >= STRAY_FAIRY_TOTAL) {
                this->actionFunc = func_80A3A520;
                EnElfgrp_SetCutscene(this, 2);
                break;
            }

            if ((func_80A39BD0(play, this->type) + sp24) >= STRAY_FAIRY_TOTAL) {
                this->actionFunc = func_80A3A398;

                switch (this->type) {
                    case ENELFGRP_TYPE_POWER:
                        if (gSaveContext.save.weekEventReg[23] & 2) { // Obtained great spin attack
                            EnElfgrp_SetCutscene(this, 1);
                        } else {
                            this->stateFlags |= ELFGRP_STATE_2;
                        }
                        break;

                    case ENELFGRP_TYPE_WISDOM:
                        if (gSaveContext.save.playerData.doubleMagic == true) {
                            EnElfgrp_SetCutscene(this, 1);
                        }
                        break;

                    case ENELFGRP_TYPE_COURAGE:
                        if (gSaveContext.save.playerData.doubleDefense) {
                            EnElfgrp_SetCutscene(this, 1);
                        }
                        break;

                    case ENELFGRP_TYPE_KINDNESS:
                        if (INV_CONTENT(ITEM_SWORD_GREAT_FAIRY) == ITEM_SWORD_GREAT_FAIRY) {
                            EnElfgrp_SetCutscene(this, 1);
                        } else {
                            this->stateFlags |= ELFGRP_STATE_4;
                        }
                        break;
                }
            } else if (func_80A39BD0(play, this->type)) {
                this->actionFunc = func_80A3A7FC;
                this->actor.textId = (this->type * 3) + 0x581;
            } else {
                this->actionFunc = func_80A3A8F8;

                if ((gSaveContext.save.weekEventReg[9] & this->talkedOnceFlag)) { // talked for first time
                    this->actor.textId = (this->type * 3) + 0x580;
                } else {
                    this->actor.textId = (this->type * 3) + 0x57F;
                }
            }
            break;

        default: // ENELFGRP_TYPE_MAGIC
            sp24 = func_80A39C1C(play, ENELFGRP_TYPE_MAGIC);
            this->talkedOnceFlag = 1 << ENELFGRP_TYPE_MAGIC;

            if (sp24 >= STRAY_FAIRY_TOTAL) {
                this->actionFunc = func_80A3A520;

                if ((this->actor.home.rot.z != 0) && Flags_GetSwitch(play, this->actor.home.rot.z)) {
                    this->actionFunc = EnElfgrp_DoNothing;
                } else if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
                    EnElfgrp_SetCutscene(this, 4);
                } else if (INV_CONTENT(ITEM_MASK_DEKU) != ITEM_MASK_DEKU) {
                    EnElfgrp_SetCutscene(this, 5);
                } else {
                    this->stateFlags |= ELFGRP_STATE_1;
                    EnElfgrp_SetCutscene(this, 6);
                }
            } else if ((gSaveContext.save.weekEventReg[8] & 0x80)) {
                EnElfgrp_SpawnStrayFairies(this, play, STRAY_FAIRY_TOTAL - 1, SPAWNED_STRAY_FAIRY_TYPE_PRESENT);
                this->actionFunc = func_80A3A398;

                if (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU) {
                    if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
                        EnElfgrp_SetCutscene(this, 2);
                    } else {
                        EnElfgrp_SetCutscene(this, 3);
                        this->stateFlags |= ELFGRP_STATE_1;
                    }
                } else if (gSaveContext.save.playerData.magicAcquired == true) {
                    EnElfgrp_SetCutscene(this, 1);
                }
            } else {
                EnElfgrp_SpawnStrayFairies(this, play, STRAY_FAIRY_TOTAL - 1, SPAWNED_STRAY_FAIRY_TYPE_PRESENT);
                this->actionFunc = func_80A3A8F8;
                if ((gSaveContext.save.weekEventReg[9] & this->talkedOnceFlag)) {
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

s32 func_80A39BD0(PlayState* play, s32 type) {
    if ((type <= ENELFGRP_TYPE_MAGIC) || (type > ENELFGRP_TYPE_KINDNESS)) {
        return 0;
    }

    return ((void)0, gSaveContext.save.inventory.strayFairies[type - 1]) - func_80A39C1C(play, type) +
           (STRAY_FAIRY_TOTAL - STRAY_FAIRY_SCATTERED_TOTAL);
}

s32 func_80A39C1C(PlayState* play, s32 type) {
    // the permanentSceneFlags access here is in the form
    // struct {
    //   u32 clockTown : 1;
    //   u32 fountains[4] : 5;
    // } FairyFountains;
    // where arg1 is:
    //    0: Clock Town
    //    1: Woodfall,
    //    2: Snowhead,
    //    3: Great Bay,
    //    4: Ikana
    // Clock Town is handled separately, and then the fountains are looked up as array indexing
    //! @note Clock Town is handled separately in a number of places

    s32 temp_v1;

    if ((type < ENELFGRP_TYPE_MAGIC) || (type > ENELFGRP_TYPE_KINDNESS)) {
        return 0;
    }

    if (type == ENELFGRP_TYPE_MAGIC) {
        if (gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 & 1) {
            return STRAY_FAIRY_TOTAL;
        } else {
            return STRAY_FAIRY_TOTAL - 1;
        }
    }

    temp_v1 = (gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 >> (((type - 1) * 5) + 1)) & 0x1F;
    if (temp_v1 < STRAY_FAIRY_TOTAL - STRAY_FAIRY_SCATTERED_TOTAL) {
        temp_v1 = STRAY_FAIRY_TOTAL - STRAY_FAIRY_SCATTERED_TOTAL;
    } else if (temp_v1 > STRAY_FAIRY_TOTAL) {
        temp_v1 = STRAY_FAIRY_TOTAL;
    }
    return temp_v1;
}

void func_80A39CD4(PlayState* play, s32 type, s32 arg2) {
    if ((type < ENELFGRP_TYPE_MAGIC) || (type > ENELFGRP_TYPE_KINDNESS) ||
        (arg2 < (STRAY_FAIRY_TOTAL - STRAY_FAIRY_SCATTERED_TOTAL)) || (arg2 > STRAY_FAIRY_TOTAL)) {
        return;
    }

    if (type == ENELFGRP_TYPE_MAGIC) {
        if (arg2 == STRAY_FAIRY_TOTAL) {
            gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 |= 1;
        } else {
            gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 &= ~1;
        }
    } else {
        gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 &= ~(0x1F << ((type * 5) - 4));
        gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 |= arg2 << ((type * 5) - 4);
    }
}

void EnElfgrp_SpawnStrayFairies(EnElfgrp* this, PlayState* play, s32 count, s32 fairyType) {
    s32 pad;
    s32 i;
    Actor* strayFairy;
    s32 strayFairyParams;
    Vec3f spawnCentrePos;
    Player* player = GET_PLAYER(play);

    if (fairyType == 0) {
        this->stateFlags |= ELFGRP_STATE_3;
    }

    if (fairyType == 0) {
        spawnCentrePos = this->actor.world.pos;
        spawnCentrePos.y += 20.0f;
        strayFairyParams = STRAY_FAIRY_PARAMS(0, this->type, STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN);
    } else {
        spawnCentrePos = player->actor.world.pos;
        spawnCentrePos.y += 20.0f;
        strayFairyParams = STRAY_FAIRY_PARAMS(0, this->type, STRAY_FAIRY_TYPE_RETURNING_TO_FOUNTAIN);
    }

    for (i = 0; i < count; i++) {
        strayFairy = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG,
                                 randPlusMinusPoint5Scaled(20.0f) + spawnCentrePos.x, spawnCentrePos.y,
                                 randPlusMinusPoint5Scaled(20.0f) + spawnCentrePos.z, 0, 0, 0, strayFairyParams);

        if (strayFairy == NULL) {
            continue;
        }
        strayFairy->home.pos.x = this->actor.home.pos.x;
        strayFairy->home.pos.y = this->actor.home.pos.y + 20.0f;
        strayFairy->home.pos.z = this->actor.home.pos.z;
    }
}

s32 func_80A39F50(PlayState* play) {
    Actor* itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    EnElforg* strayFairy;

    while (itemAction != NULL) {
        if ((itemAction->id != ACTOR_EN_ELFORG) ||
            ((STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN) &&
             (STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_RETURNING_TO_FOUNTAIN))) {
            itemAction = itemAction->next;
            continue;
        }

        strayFairy = (EnElforg*)itemAction;
        if (!(strayFairy->stateFlags & STRAY_FAIRY_FLAG_MOVES_QUICKLY_TO_HOME)) {
            strayFairy->stateFlags |= STRAY_FAIRY_FLAG_MOVES_QUICKLY_TO_HOME;
        }
        itemAction = itemAction->next;
    }

    return 0;
}

s32 func_80A39FBC(PlayState* play) {
    Actor* itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    EnElforg* strayFairy;
    s32 phi_v1 = 30;

    while (itemAction != NULL) {
        if ((itemAction->id != ACTOR_EN_ELFORG) ||
            ((STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN) &&
             (STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_RETURNING_TO_FOUNTAIN))) {
            itemAction = itemAction->next;
            continue;
        }

        strayFairy = (EnElforg*)itemAction;
        if (!(strayFairy->stateFlags & STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN)) {
            strayFairy->stateFlags |= STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN;
            if (phi_v1 >= 100) {
                return phi_v1;
            }
            strayFairy->secondaryTimer = phi_v1;
            phi_v1 += 5;
        }

        itemAction = itemAction->next;
    }

    return phi_v1;
}

void func_80A3A044(PlayState* play) {
    Actor* itemAction = play->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;
    EnElforg* strayFairy;

    while (itemAction != NULL) {
        if ((itemAction->id != ACTOR_EN_ELFORG) ||
            ((STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN) &&
             (STRAY_FAIRY_TYPE(itemAction) != STRAY_FAIRY_TYPE_RETURNING_TO_FOUNTAIN))) {
            itemAction = itemAction->next;
            continue;
        }

        strayFairy = (EnElforg*)itemAction;
        strayFairy->actor.home.rot.x = 20;
        strayFairy->stateFlags |= STRAY_FAIRY_FLAG_SPARKLES_AND_SHRINKS;

        itemAction = itemAction->next;
    }
}

void func_80A3A0AC(EnElfgrp* this, PlayState* play) {
    if (!Cutscene_CheckActorAction(play, 0x64)) {
        this->actionFunc = EnElfgrp_DoNothing;
        ActorCutscene_Stop(this->actor.cutscene);
    }
}

void func_80A3A0F4(EnElfgrp* this, PlayState* play) {
    if (this->timer == 10) {
        play_sound(NA_SE_SY_WHITE_OUT_T);
        if (ENELFGRP_GET_TYPE(&this->actor) < ENELFGRP_TYPE_KINDNESS) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0,
                        ENELFGRP_GET_TYPE(&this->actor) + DEMO_EFFECT_TYPE_LIGHT_BASE);
        } else { // ENELFGRP_TYPE_KINDNESS
            Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_EFFECT, this->actor.world.pos.x,
                        this->actor.world.pos.y + 30.0f, this->actor.world.pos.z, 0, 0, 0,
                        DEMO_EFFECT_TYPE_LIGHT_DARK_YELLOW);
        }
    }

    if ((this->timer > 10) && (this->stateFlags & ELFGRP_STATE_0)) {
        func_800B9010(&this->actor, NA_SE_EV_FAIRY_GROUP_FRY - SFX_FLAG);
    }

    if (this->timer == 0) {
        this->actionFunc = func_80A3A0AC;
    }
}

void func_80A3A210(EnElfgrp* this, PlayState* play) {
    if (this->timer == 0) {
        this->actionFunc = func_80A3A0F4;
        func_80A3A044(play);
        this->timer = 30;
    }

    if (this->stateFlags & ELFGRP_STATE_0) {
        func_800B9010(&this->actor, NA_SE_EV_FAIRY_GROUP_FRY - SFX_FLAG);
    }
}

void func_80A3A274(EnElfgrp* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x64)) {
        if (this->stateFlags & ELFGRP_STATE_0) {
            func_800B9010(&this->actor, NA_SE_PL_CHIBI_FAIRY_HEAL - SFX_FLAG);
        }

        switch (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x64)]->action) {
            case 2:
                if (!(this->stateFlags & ELFGRP_STATE_0)) {
                    if (this->type == ENELFGRP_TYPE_MAGIC) { // Clock Town
                        EnElfgrp_SpawnStrayFairies(this, play, 1, SPAWNED_STRAY_FAIRY_TYPE_RETURNING);
                    } else {
                        EnElfgrp_SpawnStrayFairies(this, play, func_80A39BD0(play, this->type),
                                                   SPAWNED_STRAY_FAIRY_TYPE_RETURNING);
                    }
                    this->stateFlags |= ELFGRP_STATE_0;
                    func_80A39CD4(play, this->type, 25);
                }
                break;

            case 3:
                func_80A39F50(play);
                this->actionFunc = func_80A3A210;
                this->timer = 90;
                break;
        }
    }
}

void func_80A3A398(EnElfgrp* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = func_80A3A274;
        Flags_UnsetSwitch(play, ENELFGRP_GET_SWITCHFLAG(&this->actor));

        if (this->stateFlags & ELFGRP_STATE_1) {
            Item_Give(play, ITEM_MASK_GREAT_FAIRY);
        }

        if (this->stateFlags & ELFGRP_STATE_2) {
            gSaveContext.save.weekEventReg[23] |= 2; // Obtained Great Spin Attack
        }

        if (this->stateFlags & ELFGRP_STATE_4) {
            Item_Give(play, ITEM_SWORD_GREAT_FAIRY);
        }

        this->stateFlags &= ~ELFGRP_STATE_3;
    } else if (this->actor.xzDistToPlayer < 350.0f) {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80A3A484(EnElfgrp* this, PlayState* play) {
    if (this->timer == 0) {
        this->actionFunc = func_80A3A0F4;
        this->timer = 30;
    }
}

void func_80A3A4AC(EnElfgrp* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x64)) {
        s32 csAction = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x64)]->action;

        if (csAction == 3) {
            this->actionFunc = func_80A3A484;
            this->timer = 90;
        }
    }
}

void func_80A3A520(EnElfgrp* this, PlayState* play) {
    // Great Fairy's action
    if (Cutscene_CheckActorAction(play, 0x67)) {
        this->actionFunc = EnElfgrp_DoNothing;
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = func_80A3A4AC;
        Flags_SetSwitch(play, ENELFGRP_GET_SWITCHFLAG(&this->actor));

        if (this->stateFlags & ELFGRP_STATE_1) {
            Item_Give(play, ITEM_MASK_GREAT_FAIRY);
        }

        if (this->actor.home.rot.z != 0) {
            Flags_SetSwitch(play, this->actor.home.rot.z);
        }
    } else if (this->actor.xzDistToPlayer < 350.0f) {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnElfgrp_DoNothing(EnElfgrp* this, PlayState* play) {
}

void func_80A3A610(EnElfgrp* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->timer == 60) {
        Parameter_AddMagic(play,
                           ((void)0, gSaveContext.unk_3F30) + (gSaveContext.save.playerData.doubleMagic * 0x30) + 0x30);
        gSaveContext.healthAccumulator = 0x140;
    }

    if (this->timer > 0) {
        player->actor.freezeTimer = 100;
        player->stateFlags1 |= PLAYER_STATE1_20000000;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_GROUP_HEAL - SFX_FLAG);
    } else {
        player->actor.freezeTimer = 0;
        player->stateFlags1 &= ~PLAYER_STATE1_20000000;
        this->actionFunc = EnElfgrp_DoNothing;
        this->stateFlags |= ELFGRP_STATE_3;
    }
}

void func_80A3A6F4(EnElfgrp* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        player->actor.freezeTimer = 100;
        player->stateFlags1 |= PLAYER_STATE1_20000000;
        this->timer = func_80A39FBC(play);
        this->actionFunc = func_80A3A610;
        this->stateFlags &= ~ELFGRP_STATE_3;
    }
}

void func_80A3A77C(EnElfgrp* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.freezeTimer = 100;
    player->stateFlags1 |= PLAYER_STATE1_20000000;
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        this->timer = func_80A39FBC(play);
        this->actionFunc = func_80A3A610;
        this->stateFlags &= ~ELFGRP_STATE_3;
    }
}

void func_80A3A7FC(EnElfgrp* this, PlayState* play) {
    s32 temp_s0;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        gSaveContext.save.weekEventReg[9] |= this->talkedOnceFlag;
        this->actionFunc = func_80A3A6F4;

        temp_s0 = func_80A39BD0(play, this->type);
        EnElfgrp_SpawnStrayFairies(this, play, temp_s0, SPAWNED_STRAY_FAIRY_TYPE_RETURNING);
        temp_s0 += func_80A39C1C(play, this->type);
        if (temp_s0 > STRAY_FAIRY_TOTAL) {
            temp_s0 = STRAY_FAIRY_TOTAL;
        }

        func_80A39CD4(play, this->type, temp_s0);
    } else if (this->actor.xzDistToPlayer < 280.0f) {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, play, 300.0f);
    }
}

void func_80A3A8F8(EnElfgrp* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        gSaveContext.save.weekEventReg[9] |= this->talkedOnceFlag;
        this->actionFunc = func_80A3A6F4;
    } else if ((this->type != ENELFGRP_TYPE_MAGIC) && (func_80A39BD0(play, this->type) > 0)) {
        this->actionFunc = func_80A3A7FC;
    } else if (this->actor.xzDistToPlayer < 30.0f) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            player->actor.freezeTimer = 100;
            player->stateFlags1 |= PLAYER_STATE1_20000000;
            Message_StartTextbox(play, this->actor.textId, &this->actor);
            this->actionFunc = func_80A3A77C;
            gSaveContext.save.weekEventReg[9] |= this->talkedOnceFlag;
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

    if (this->stateFlags & ELFGRP_STATE_3) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_GROUP_FRY - SFX_FLAG);
    }

    if (this->timer != 0) {
        this->timer--;
    }
}
