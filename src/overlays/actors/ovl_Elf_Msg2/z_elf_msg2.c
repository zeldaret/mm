/*
 * File: z_elf_msg2.c
 * Overlay: ovl_Elf_Msg2
 * Description: Tatl Hint (Z-target-activated C-up hint?)
 */

#include "z_elf_msg2.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg2*)thisx)

void ElfMsg2_Init(Actor* thisx, PlayState* play);
void ElfMsg2_Destroy(Actor* thisx, PlayState* play);
void ElfMsg2_Update(Actor* thisx, PlayState* play);

s32 func_8096EE50(ElfMsg2* this);
void func_8096EF98(ElfMsg2* this, PlayState* play);
void func_8096EFD0(ElfMsg2* this, PlayState* play);

const ActorInit Elf_Msg2_InitVars = {
    ACTOR_ELF_MSG2,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg2),
    (ActorFunc)ElfMsg2_Init,
    (ActorFunc)ElfMsg2_Destroy,
    (ActorFunc)ElfMsg2_Update,
    (ActorFunc)NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

void ElfMsg2_SetupAction(ElfMsg2* this, ElfMsg2ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

s32 func_8096EC4C(ElfMsg2* this, PlayState* play) {
    if ((this->actor.home.rot.y > 0) && (this->actor.home.rot.y < 0x81) &&
        (Flags_GetSwitch(play, this->actor.home.rot.y - 1))) {
        (void)"共倒れ"; // "Collapse together"
        if (ELFMSG2_GET_SWITCHFLAG(&this->actor) != 0x7F) {
            Flags_SetSwitch(play, ELFMSG2_GET_SWITCHFLAG(&this->actor));
        }
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    if (this->actor.home.rot.y == 129) {

        if (Flags_GetClear(play, this->actor.room)) {
            (void)"共倒れ２"; // "Collapse 2"
            if (ELFMSG2_GET_SWITCHFLAG(&this->actor) != 0x7F) {
                Flags_SetSwitch(play, ELFMSG2_GET_SWITCHFLAG(&this->actor));
            }
            Actor_MarkForDeath(&this->actor);
            return true;
        }
    }
    if (ELFMSG2_GET_SWITCHFLAG(&this->actor) == 0x7F) {
        return false;
    }
    if (Flags_GetSwitch(play, ELFMSG2_GET_SWITCHFLAG(&this->actor))) {
        (void)"共倒れ"; // "Collapse together"
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    return false;
}

void ElfMsg2_Init(Actor* thisx, PlayState* play) {
    ElfMsg2* this = THIS;

    if (!func_8096EC4C(this, play)) {
        if ((this->actor.home.rot.x > 0) && (this->actor.home.rot.x < 8)) {
            this->actor.targetMode = this->actor.home.rot.x - 1;
        }
        Actor_ProcessInitChain(&this->actor, sInitChain);
        if (this->actor.home.rot.y < 0) {
            ElfMsg2_SetupAction(this, func_8096EFD0);
        } else {
            ElfMsg2_SetupAction(this, func_8096EF98);
            this->actor.flags |= (ACTOR_FLAG_40000 | ACTOR_FLAG_1);
            this->actor.textId = func_8096EE50(this);
        }
        this->actor.shape.rot.z = 0;
        this->actor.shape.rot.x = this->actor.shape.rot.y = this->actor.shape.rot.z;
    }
}

void ElfMsg2_Destroy(Actor* thisx, PlayState* play) {
}

s32 func_8096EE50(ElfMsg2* this) {
    return ELFMSG2_GET_FF(&this->actor) + 0x200;
}

void func_8096EE64(ElfMsg2* this, PlayState* play) {
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.cutscene != -1) {
            if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                ActorCutscene_Stop(this->actor.cutscene);
            }
        }
        if (this->actor.home.rot.z != 1) {
            Actor_MarkForDeath(&this->actor);
            if (ELFMSG2_GET_SWITCHFLAG(&this->actor) != 0x7F) {
                Flags_SetSwitch(play, ELFMSG2_GET_SWITCHFLAG(&this->actor));
            }
        } else {
            ElfMsg2_SetupAction(this, func_8096EF98);
        }
    } else if ((this->actor.cutscene != -1) && (ActorCutscene_GetCurrentIndex() != this->actor.cutscene)) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void func_8096EF98(ElfMsg2* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        ElfMsg2_SetupAction(this, func_8096EE64);
    }
}

void func_8096EFD0(ElfMsg2* this, PlayState* play) {
    if ((this->actor.home.rot.y < 0) && (this->actor.home.rot.y >= -0x80) &&
        (Flags_GetSwitch(play, -this->actor.home.rot.y - 1))) {
        ElfMsg2_SetupAction(this, func_8096EF98);
        this->actor.flags |= (ACTOR_FLAG_40000 | ACTOR_FLAG_1);
        this->actor.textId = func_8096EE50(this);
    }
}

void ElfMsg2_Update(Actor* thisx, PlayState* play) {
    ElfMsg2* this = THIS;

    if (!func_8096EC4C(this, play)) {
        this->actionFunc(this, play);
    }
}
