/*
 * File: z_elf_msg3.c
 * Overlay: ovl_Elf_Msg3
 * Description: Tatl Message (Proximity-activated dialogue?)
 */

#include "z_elf_msg3.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg3*)thisx)

void ElfMsg3_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A2CF7C(ElfMsg3* this, GlobalContext* globalCtx);

const ActorInit Elf_Msg3_InitVars = {
    ACTOR_ELF_MSG3,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg3),
    (ActorFunc)ElfMsg3_Init,
    (ActorFunc)ElfMsg3_Destroy,
    (ActorFunc)ElfMsg3_Update,
    (ActorFunc)NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

void ElfMsg3_SetupAction(ElfMsg3* this, ElfMsg3ActionFunc actionFunc) {
    (void)"共倒れ"; // "Collapse together"
    (void)"共倒れ";
    this->actionFunc = actionFunc;
}

s32 func_80A2CD1C(ElfMsg3* this, GlobalContext* globalCtx) {
    if ((this->actor.home.rot.y > 0) && (this->actor.home.rot.y < 0x81) &&
        (Flags_GetSwitch(globalCtx, this->actor.home.rot.y - 1) != 0)) {
        if (ELFMSG3_GET_SWITCH(&this->actor) != 0x7F) {
            Flags_SetSwitch(globalCtx, ELFMSG3_GET_SWITCH(&this->actor));
        }
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    if (this->actor.home.rot.y == 0x81) {
        if (Flags_GetClear(globalCtx, this->actor.room) != 0) {
            if (ELFMSG3_GET_SWITCH(&this->actor) != 0x7F) {
                Flags_SetSwitch(globalCtx, ELFMSG3_GET_SWITCH(&this->actor));
            }
            Actor_MarkForDeath(&this->actor);
            return true;
        }
    }
    if (ELFMSG3_GET_SWITCH(&this->actor) == 0x7F) {
        return false;
    }
    if (Flags_GetSwitch(globalCtx, ELFMSG3_GET_SWITCH(&this->actor)) != 0) {
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    return false;
}

void ElfMsg3_Init(Actor* thisx, GlobalContext* globalCtx) {
    ElfMsg3* this = THIS;
    s32 absolute;

    if (func_80A2CD1C(this, globalCtx) == 0) {
        Actor_ProcessInitChain(&this->actor, sInitChain);
        if (ABS_ALT(this->actor.home.rot.x) == 0) {
            this->actor.scale.z = 0.4f;
            this->actor.scale.x = 0.4f;
        } else {
            absolute = ABS_ALT(this->actor.home.rot.x);
            this->actor.scale.z = absolute * 0.04f;
            this->actor.scale.x = absolute * 0.04f;
        }
        if (this->actor.home.rot.z == 0) {
            this->actor.scale.y = 0.4f;
        } else {
            this->actor.scale.y = this->actor.home.rot.z * 0.04f;
        }
        ElfMsg3_SetupAction(this, func_80A2CF7C);
        this->actor.shape.rot.z = 0;
        this->actor.shape.rot.y = this->actor.shape.rot.z;
        this->actor.shape.rot.x = this->actor.shape.rot.z;
    }
}

void ElfMsg3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 func_80A2CF50(ElfMsg3* this) {
    if (ELFMSG3_GET_8000(&this->actor) != 0) {
        return (ELFMSG3_GET_FF(&this->actor)) + 0x200;
    }
    return -0x200 - (ELFMSG3_GET_FF(&this->actor));
}

void func_80A2CF7C(ElfMsg3* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnElf* elf = (EnElf*)player->tatlActor;

    if (((((player->tatlActor != NULL) &&
           (fabsf(player->actor.world.pos.x - this->actor.world.pos.x) < (100.0f * this->actor.scale.x))) &&
          (this->actor.world.pos.y <= player->actor.world.pos.y)) &&
         ((player->actor.world.pos.y - this->actor.world.pos.y) < (100.0f * this->actor.scale.y))) &&
        (fabsf(player->actor.world.pos.z - this->actor.world.pos.z) < (100.0f * this->actor.scale.z))) {
        player->tatlTextId = func_80A2CF50(this);
        ActorCutscene_SetIntentToPlay(0x7C);
        elf->elfMsg = &this->actor;
        if (this->actor.cutscene == -1) {
            this->actor.cutscene = 0x7C;
        }
        if ((player->tatlTextId < 0) && (this->actor.home.rot.x < 0)) {
            if (ActorCutscene_GetCurrentIndex() == 0x7D) {
                ActorCutscene_Stop(0x7D);
                ActorCutscene_SetIntentToPlay(this->actor.cutscene);
            } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene) != 0) {
                ActorCutscene_Start(this->actor.cutscene, &this->actor);
                func_800E0348(globalCtx->cameraPtrs[0]);
            } else {
                ActorCutscene_SetIntentToPlay(this->actor.cutscene);
            }
        }
    }
}

void ElfMsg3_Update(Actor* thisx, GlobalContext* globalCtx) {
    ElfMsg3* this = THIS;

    if (func_80A2CD1C(this, globalCtx) == 0) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) != 0) {
            if (ELFMSG3_GET_SWITCH(thisx) != 0x7F) {
                Flags_SetSwitch(globalCtx, ELFMSG3_GET_SWITCH(thisx));
            }
            Actor_MarkForDeath(&this->actor);
        } else if ((this->actor.home.rot.y >= 0) || (this->actor.home.rot.y < -0x80) ||
                   (Flags_GetSwitch(globalCtx, -1 - this->actor.home.rot.y) != 0)) {
            this->actionFunc(this, globalCtx);
        }
    }
}
