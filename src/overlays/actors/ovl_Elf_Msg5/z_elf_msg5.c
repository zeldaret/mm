/*
 * File: z_elf_msg5.c
 * Overlay: ovl_Elf_Msg5
 * Description: Tatl Message (Another proximity-activated dialogue?)
 */

#include "z_elf_msg5.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg5*)thisx)

void ElfMsg5_Init(Actor* thisx, PlayState* play);
void ElfMsg5_Destroy(Actor* thisx, PlayState* play);
void ElfMsg5_Update(Actor* thisx, PlayState* play);

void func_80AFDB38(ElfMsg5* this, PlayState* play);
s32 func_80AFD990(ElfMsg5* this, PlayState* play);

ActorInit Elf_Msg5_InitVars = {
    ACTOR_ELF_MSG5,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg5),
    (ActorFunc)ElfMsg5_Init,
    (ActorFunc)ElfMsg5_Destroy,
    (ActorFunc)ElfMsg5_Update,
    (ActorFunc)NULL,
};

static InitChainEntry sInitChainsInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

s32 func_80AFD990(ElfMsg5* this, PlayState* play) {
    if ((this->actor.home.rot.y > 0) && (this->actor.home.rot.y < 0x81) &&
        (Flags_GetSwitch(play, this->actor.home.rot.y - 1))) {
        (void)"共倒れ"; // Collapse together
        if (ELFMSG5_GET_SWITCH_FLAG(&this->actor) != 0x7F) {
            Flags_SetSwitch(play, ELFMSG5_GET_SWITCH_FLAG(&this->actor));
        }
        Actor_Kill(&this->actor);
        return true;
    }
    if (this->actor.home.rot.y == 0x81) {
        if (Flags_GetClear(play, this->actor.room)) {
            (void)"共倒れ２"; // Collapse 2
            if (ELFMSG5_GET_SWITCH_FLAG(&this->actor) != 0x7F) {
                Flags_SetSwitch(play, ELFMSG5_GET_SWITCH_FLAG(&this->actor));
            }
            Actor_Kill(&this->actor);
            return true;
        }
    }
    if (ELFMSG5_GET_SWITCH_FLAG(&this->actor) == 0x7F) {
        return false;
    }
    if (Flags_GetSwitch(play, ELFMSG5_GET_SWITCH_FLAG(&this->actor))) {
        (void)"共倒れ"; // Collapse together
        Actor_Kill(&this->actor);
        return true;
    }
    return false;
}

void ElfMsg5_Init(Actor* thisx, PlayState* play) {
    ElfMsg5* this = THIS;

    if (!func_80AFD990(this, play)) {
        Actor_ProcessInitChain(&this->actor, sInitChainsInitChain);
        this->actor.shape.rot.z = 0;
        this->actionFunc = func_80AFDB38;
        this->actor.home.rot.x = -0x961;
        this->actor.shape.rot.x = this->actor.shape.rot.y = this->actor.shape.rot.z;
    }
}

void ElfMsg5_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AFDB38(ElfMsg5* this, PlayState* play) {
}

void ElfMsg5_Update(Actor* thisx, PlayState* play) {
    ElfMsg5* this = THIS;

    if ((this->actor.home.rot.y >= 0) || (this->actor.home.rot.y < -0x80) ||
        (Flags_GetSwitch(play, -this->actor.home.rot.y - 1))) {
        this->actionFunc(this, play);
    }
}
