/*
 * File: z_elf_msg3.c
 * Overlay: ovl_Elf_Msg3
 * Description: Tatl Message (Proximity-activated dialogue?)
 */

#include "z_elf_msg3.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg3*)thisx)

void ElfMsg3_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Update(Actor* thisx, GlobalContext* globalCtx);

void ElfMsg3_SetupAction(ElfMsg3* this, ElfMsg3ActionFunc actionFunc);
s32 func_80A2CD1C(ElfMsg3* this, GlobalContext* globalCtx);  /* extern */
void func_80A2CF7C(ElfMsg3* this, GlobalContext* globalCtx); /* extern */
s32 func_80A2CF50(ElfMsg3* this);
#if 0
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A2D1E0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80A2D1E0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/D_80A2D1F0.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_SetupAction.s")
void ElfMsg3_SetupAction(ElfMsg3* this, ElfMsg3ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CD1C.s")
s32 func_80A2CD1C(ElfMsg3* this, GlobalContext* globalCtx) {
    if ((this->actor.home.rot.y > 0) && (this->actor.home.rot.y < 0x81) &&
        (Flags_GetSwitch(globalCtx, this->actor.home.rot.y - 1) != 0)) {
        if (((this->actor.params & 0x7F00) >> 8) != 0x7F) {
            Flags_SetSwitch(globalCtx, ((this->actor.params & 0x7F00) >> 8));
        }
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    if (this->actor.home.rot.y == 0x81) {
        if (Flags_GetClear(globalCtx, (s32)this->actor.room) != 0) {
            if (((this->actor.params & 0x7F00) >> 8) != 0x7F) {
                Flags_SetSwitch(globalCtx, ((this->actor.params & 0x7F00) >> 8));
            }
            Actor_MarkForDeath(&this->actor);
            return true;
        }
    }
    if (((this->actor.params & 0x7F00) >> 8) == 0x7F) {
        return false;
    }
    if (Flags_GetSwitch(globalCtx, ((this->actor.params & 0x7F00) >> 8)) != 0) {
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    return false;
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_Init.s")

void ElfMsg3_Init(Actor* thisx, GlobalContext* globalCtx) {
    ElfMsg3* this = (ElfMsg3*)thisx;
    s32 tmp;
    if (func_80A2CD1C(this, globalCtx) == 0) {
        Actor_ProcessInitChain(&this->actor, D_80A2D1E0);
        if (ABS_ALT(this->actor.home.rot.x) == 0) {
            this->actor.scale.z = 0.4f;
            this->actor.scale.x = 0.4f;
        } else {
            tmp = ABS_ALT(this->actor.home.rot.x);
            this->actor.scale.z = tmp * 0.04f;
            this->actor.scale.x = tmp * 0.04f;
        }
        if (this->actor.home.rot.z == 0) {
            this->actor.scale.y = 0.4f;
        } else {
            this->actor.scale.y = ((f32)this->actor.home.rot.z) * 0.04f;
        }
        ElfMsg3_SetupAction(this, func_80A2CF7C);
        this->actor.shape.rot.z = 0;
        this->actor.shape.rot.y = this->actor.shape.rot.z;
        this->actor.shape.rot.x = this->actor.shape.rot.z;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_Destroy.s")
void ElfMsg3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CF50.s")

s32 func_80A2CF50(ElfMsg3* this) {
    if ((this->actor.params & 0x8000) != 0) {
        return (this->actor.params & 0xFF) + 0x200;
    }
    return -0x200 - (this->actor.params & 0xFF);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CF7C.s")
void func_80A2CF7C(ElfMsg3* this, GlobalContext* globalCtx) {
    // Actor *sp24;
    // void *sp20;
    // Actor *temp_v1;
    // f32 temp_fv0;
    // f32 temp_fv1;
    // void *temp_v0;

    Player* temp_v1;

    temp_v1->tatlActor = GET_PLAYER(globalCtx);
    // temp_v0 = temp_v1->unkA80;
    // sp20 = temp_v0;
    if ((temp_v1->tatlActor != NULL) &&
        (fabsf(temp_v1->tatlActor->world.pos.x - this->actor.world.pos.x) < (100.0f * this->actor.scale.x)) &&
        ((this->actor.world.pos.y <= temp_v1->tatlActor->world.pos.y)) &&
        ((temp_v1->tatlActor->world.pos.y - this->actor.world.pos.y) < (100.0f * this->actor.scale.y)) &&
        (fabsf(temp_v1->tatlActor->world.pos.z - this->actor.world.pos.z) < (100.0f * this->actor.scale.z))) {
        // sp24 = temp_v1;
        temp_v1->tatlActor = func_80A2CF50(this);
        ActorCutscene_SetIntentToPlay(0x7C);
        // sp20->unk230 = this;
        if (this->actor.cutscene == -1) {
            this->actor.cutscene = 0x7C;
        }
        if ((temp_v1->tatlActor->id < 0) && (this->actor.home.rot.x < 0)) {
            if (ActorCutscene_GetCurrentIndex() == 0x7D) {
                ActorCutscene_Stop(0x7D);
                ActorCutscene_SetIntentToPlay((s16)this->actor.cutscene);

            } else if (ActorCutscene_GetCanPlayNext((s16)this->actor.cutscene) != 0) {
                ActorCutscene_Start((s16)this->actor.cutscene, &this->actor);
                func_800E0348(globalCtx->cameraPtrs[0]);

            } else {
                ActorCutscene_SetIntentToPlay((s16)this->actor.cutscene);
            }
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_Update.s")
void ElfMsg3_Update(Actor* thisx, GlobalContext* globalCtx) {
    ElfMsg3* this = THIS;

    if (func_80A2CD1C(this, globalCtx) == 0) {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) != 0) {
            if (((this->actor.params & 0x7F00) >> 8) != 0x7F) {
                Flags_SetSwitch(globalCtx, ((this->actor.params & 0x7F00) >> 8));
            }
            Actor_MarkForDeath(&this->actor);
            return;
        }
        if ((this->actor.home.rot.y >= 0) || (this->actor.home.rot.y < -0x80) ||
            (Flags_GetSwitch(globalCtx, -1 - this->actor.home.rot.y) != 0)) {
            this->actionFunc(this, globalCtx);
        }
    }
}