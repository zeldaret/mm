/*
 * File: z_en_fishing.c
 * Overlay: ovl_En_Fishing
 * Description: Fishing
 */

#include "z_en_fishing.h"

#define FLAGS 0x00000010

#define THIS ((EnFishing*)thisx)

void EnFishing_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Draw(Actor* thisx, GlobalContext* globalCtx);

/* 
const ActorInit En_Fishing_InitVars = {
    0x0079,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FISH,
    sizeof(EnFishing),
    (ActorFunc)EnFishing_Init,
    (ActorFunc)EnFishing_Destroy,
    (ActorFunc)EnFishing_Update,
    (ActorFunc)EnFishing_Draw,
};
 */

