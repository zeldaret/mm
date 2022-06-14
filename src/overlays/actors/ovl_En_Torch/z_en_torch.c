/*
 * File: z_en_torch.c
 * Overlay: ovl_En_Torch
 * Description: Grotto chest spawner
 */

#include "z_en_torch.h"

#define FLAGS 0x00000000

#define THIS ((EnTorch*)thisx)

void EnTorch_Init(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Torch_InitVars = {
    ACTOR_EN_TORCH,          ACTORCAT_ITEMACTION, FLAGS,           GAMEPLAY_KEEP,   sizeof(EnTorch),
    (ActorFunc)EnTorch_Init, (ActorFunc)NULL,     (ActorFunc)NULL, (ActorFunc)NULL,
};

static u8 sChestContents[] = { 0x02, 0x04, 0x05, 0x06, 0x36, 0x3A, 0x14, 0x14 };

void EnTorch_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTorch* this = THIS;
    s8 returnData = gSaveContext.respawn[RESPAWN_MODE_UNK_3].data;

    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOX, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                (sChestContents[(returnData >> 0x5) & 0x7] << 0x5) | 0x5000 | (returnData & 0x1F));
    Actor_MarkForDeath(&this->actor);
}
