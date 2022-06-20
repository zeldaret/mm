/*
 * File: z_elf_msg6.c
 * Overlay: ovl_Elf_Msg6
 * Description: Tatl Hint (another proximity-activated C-up hint?)
 */

#include "z_elf_msg6.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg6*)thisx)

void ElfMsg6_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80BA1CF8(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA1E30(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA1F80(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA2038(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA2048(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA215C(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA21C4(ElfMsg6* this, GlobalContext* globalCtx);

const ActorInit Elf_Msg6_InitVars = {
    ACTOR_ELF_MSG6,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg6),
    (ActorFunc)ElfMsg6_Init,
    (ActorFunc)ElfMsg6_Destroy,
    (ActorFunc)ElfMsg6_Update,
    (ActorFunc)NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

s32 func_80BA15A0(void) {
    if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA) && !(gSaveContext.save.weekEventReg[87] & 0x10)) {
        return true;
    }

    if (CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT) && !(gSaveContext.save.weekEventReg[87] & 0x20)) {
        return true;
    }

    if (CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG) && !(gSaveContext.save.weekEventReg[87] & 0x40)) {
        return true;
    }

    if (CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD) && !(gSaveContext.save.weekEventReg[87] & 0x80)) {
        return true;
    }

    return false;
}

void func_80BA165C(void) {
    if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA)) {
        gSaveContext.save.weekEventReg[87] |= 0x10;
    }

    if (CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT)) {
        gSaveContext.save.weekEventReg[87] |= 0x20;
    }

    if (CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG)) {
        gSaveContext.save.weekEventReg[87] |= 0x40;
    }

    if (CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
        gSaveContext.save.weekEventReg[87] |= 0x80;
    }
}

s32 func_80BA16F4(ElfMsg6* this, GlobalContext* globalCtx) {
    if (!(gSaveContext.save.weekEventReg[31] & 4) && (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU)) {
        this->actor.textId = 0x216;
        return false;
    }

    if (!func_80BA15A0()) {
        return true;
    }

    if (!CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA)) {
        this->actor.textId = 0x256;
        return false;
    }

    if (!CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT)) {
        if (gSaveContext.save.weekEventReg[31] & 1) {
            this->actor.textId = 0x257;
        } else {
            this->actor.textId = 0x231;
        }
        return false;
    }

    if (!CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG)) {
        if (gSaveContext.save.weekEventReg[31] & 2) {
            this->actor.textId = 0x258;
        } else {
            this->actor.textId = 0x232;
        }
        return false;
    }

    if (!CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
        if (gSaveContext.save.weekEventReg[80] & 4) {
            this->actor.textId = 0x259;
        } else {
            this->actor.textId = 0x233;
        }
        return false;
    }

    return true;
}

void ElfMsg6_Init(Actor* thisx, GlobalContext* globalCtx) {
    ElfMsg6* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    if (ABS_ALT(this->actor.home.rot.x) == 0) {
        this->actor.scale.z = 0.4f;
        this->actor.scale.x = 0.4f;
    } else {
        this->actor.scale.x = this->actor.scale.z = ABS_ALT(this->actor.home.rot.x) * 0.04f;
    }

    if (this->actor.home.rot.z == 0) {
        this->actor.scale.y = 0.4f;
    } else {
        this->actor.scale.y = this->actor.home.rot.z * 0.04f;
    }

    this->actor.shape.rot.x = this->actor.shape.rot.y = this->actor.shape.rot.z = 0;

    switch (ELFMSG6_GET_F(&this->actor)) {
        case 0:
            this->actionFunc = func_80BA1E30;
            if (func_80BA16F4(this, globalCtx)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;

        case 1:
            this->actionFunc = func_80BA1F80;
            if ((this->actor.cutscene == -1) || ((ELFMSG6_SWITCHFLAG(&this->actor) != 0x7F) &&
                                                 Flags_GetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor)))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            switch (ELFMSG6_GET_F0(&this->actor)) {
                case 0:
                    if (gSaveContext.save.inventory.items[ITEM_HOOKSHOT] != ITEM_HOOKSHOT) {
                        Actor_MarkForDeath(&this->actor);
                        return;
                    }
                    break;

                case 1:
                    if (gSaveContext.save.weekEventReg[83] & 2) {
                        Actor_MarkForDeath(&this->actor);
                        return;
                    }
                    break;
            }
            break;

        case 2:
            if (INV_CONTENT(ITEM_OCARINA) == ITEM_OCARINA) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            if (gSaveContext.save.weekEventReg[8] & 0x40) {
                if (gSaveContext.save.weekEventReg[88] & 0x20) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                this->actor.textId = 0x25B;
            } else {
                if (!(gSaveContext.save.weekEventReg[74] & 0x20) || (gSaveContext.save.weekEventReg[79] & 0x10)) {
                    Actor_MarkForDeath(&this->actor);
                    return;
                }
                this->actor.textId = 0x224;
            }
            this->actionFunc = func_80BA1CF8;
            break;

        case 3:
            if (((ELFMSG6_SWITCHFLAG(&this->actor) != 0x7F) &&
                 Flags_GetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor))) ||
                (gSaveContext.save.weekEventReg[88] & 0x10) || (gSaveContext.save.weekEventReg[91] & 1) ||
                (INV_CONTENT(ITEM_MASK_ZORA) == ITEM_MASK_ZORA)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->actionFunc = func_80BA2048;
            this->actor.textId = 0x24D;
            break;

        case 4:
            this->actionFunc = func_80BA215C;
            this->actor.textId = 0x255;
            break;

        case 5:
            this->actionFunc = func_80BA21C4;
            this->actor.textId = 0x25E;
            break;

        case 6:
            this->actionFunc = func_80BA21C4;
            this->actor.textId = 0x25F;
            break;

        default:
            this->actionFunc = func_80BA2038;
            break;
    }
}

void ElfMsg6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 func_80BA1C00(ElfMsg6* this) {
    return (this->actor.xzDistToPlayer < (100.0f * this->actor.scale.x)) &&
           ((this->actor.playerHeightRel >= 0.0f) && (this->actor.playerHeightRel < (100.0f * this->actor.scale.y)));
}

void func_80BA1C88(ElfMsg6* this, GlobalContext* globalCtx, s16 arg2) {
    Player* player = GET_PLAYER(globalCtx);
    EnElf* sp20 = (EnElf*)player->tatlActor;

    if (player->tatlActor != NULL) {
        player->tatlTextId = arg2;
        ActorCutscene_SetIntentToPlay(0x7C);
        sp20->elfMsg = &this->actor;
        if (this->actor.cutscene == -1) {
            this->actor.cutscene = 0x7C;
        }
    }
}

void func_80BA1CF8(ElfMsg6* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnElf* sp20 = (EnElf*)player->tatlActor;

    if (player->tatlActor == NULL) {
        return;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        switch (this->actor.textId) {
            case 0x224:
                gSaveContext.save.weekEventReg[79] |= 0x10;
                break;

            case 0x25B:
                gSaveContext.save.weekEventReg[88] |= 0x20;
                break;
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if ((this->actor.textId == 0x224) && (gSaveContext.save.weekEventReg[8] & 0x40)) {
        this->actor.textId = 0x25B;
    } else if (func_80BA1C00(this) && (player->actor.speedXZ > 1.0f)) {
        player->tatlTextId = -this->actor.textId;
        ActorCutscene_SetIntentToPlay(0x7C);
        sp20->elfMsg = &this->actor;
        if (this->actor.cutscene == -1) {
            this->actor.cutscene = 0x7C;
        }
    }
}

void func_80BA1E30(ElfMsg6* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnElf* sp20 = (EnElf*)player->tatlActor;

    if (player->tatlActor == NULL) {
        return;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        switch (this->actor.textId) {
            case 0x216:
                gSaveContext.save.weekEventReg[31] |= 4;
                break;

            case 0x231:
                gSaveContext.save.weekEventReg[31] |= 1;
                break;

            case 0x232:
                gSaveContext.save.weekEventReg[31] |= 2;
                break;

            case 0x233:
                gSaveContext.save.weekEventReg[80] |= 4;
                break;
        }
        func_80BA165C();
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_80BA1C00(this) && (player->actor.speedXZ > 1.0f)) {
        player->tatlTextId = -this->actor.textId;
        ActorCutscene_SetIntentToPlay(0x7C);
        sp20->elfMsg = &this->actor;
        if (this->actor.cutscene == -1) {
            this->actor.cutscene = 0x7C;
        }
    }
}

void func_80BA1F80(ElfMsg6* this, GlobalContext* globalCtx) {
    if (((ELFMSG6_GET_F0(&this->actor)) == 1) && (gSaveContext.save.weekEventReg[83] & 2)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_80BA1C00(this)) {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, NULL);
            Flags_SetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor));
            Actor_MarkForDeath(&this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void func_80BA2038(ElfMsg6* this, GlobalContext* globalCtx) {
}

void func_80BA2048(ElfMsg6* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        EnElf* sp20 = (EnElf*)GET_PLAYER(globalCtx)->tatlActor;

        sp20->unk_264 |= 0x20;
        if (ELFMSG6_SWITCHFLAG(&this->actor) != 0x7F) {
            Flags_SetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor));
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (((ELFMSG6_SWITCHFLAG(&this->actor) != 0x7F) && Flags_GetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor))) ||
        (gSaveContext.save.weekEventReg[88] & 0x10) || (gSaveContext.save.weekEventReg[91] & 1) ||
        (INV_CONTENT(ITEM_MASK_ZORA) == ITEM_MASK_ZORA)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_80BA1C00(this)) {
        func_80BA1C88(this, globalCtx, 0x24D);
    }
}

void func_80BA215C(ElfMsg6* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_80BA1C00(this)) {
        func_80BA1C88(this, globalCtx, -this->actor.textId);
    }
}

void func_80BA21C4(ElfMsg6* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        EnElf* sp20 = (EnElf*)GET_PLAYER(globalCtx)->tatlActor;

        sp20->unk_264 |= 0x20;
        if (ELFMSG6_SWITCHFLAG(&this->actor) != 0x7F) {
            Flags_SetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor));
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (((ELFMSG6_SWITCHFLAG(&this->actor) != 0x7F) && Flags_GetSwitch(globalCtx, ELFMSG6_SWITCHFLAG(&this->actor))) ||
        CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (func_80BA1C00(this)) {
        func_80BA1C88(this, globalCtx, this->actor.textId);
    }
}

void ElfMsg6_Update(Actor* thisx, GlobalContext* globalCtx) {
    ElfMsg6* this = THIS;

    this->actionFunc(this, globalCtx);
}
