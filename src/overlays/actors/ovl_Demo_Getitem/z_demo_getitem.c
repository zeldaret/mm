/*
 * File: z_demo_getitem.c
 * Overlay: ovl_Demo_Getitem
 * Description: Cutscene object for Great Fairy's Mask and Great Fairy's Sword
 */

#include "z_demo_getitem.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoGetitem*)thisx)

void DemoGetitem_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoGetitem_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoGetitem_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A4FB10(DemoGetitem* this, GlobalContext* globalCtx);
void func_80A4FB68(DemoGetitem* this, GlobalContext* globalCtx2);
void func_80A4FCF0(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Demo_Getitem_InitVars = {
    ACTOR_DEMO_GETITEM,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoGetitem),
    (ActorFunc)DemoGetitem_Init,
    (ActorFunc)DemoGetitem_Destroy,
    (ActorFunc)DemoGetitem_Update,
    (ActorFunc)NULL,
};

static s16 bankIndex[] = { OBJECT_GI_MASK14, OBJECT_GI_SWORD_4 };

static s16 drawIndex[] = { GID_MASK_GREAT_FAIRY, GID_SWORD_GREAT_FAIRY };

static u16 actionIndex[] = {
    0x6E,
    0x236,
};

void DemoGetitem_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    s32 objIndex;
    s32 itemIndex;
    DemoGetitem* this = THIS;

    itemIndex = 0;
    if ((this->actor.params & 0xF) == 1) {
        itemIndex = 1;
    }
    Actor_SetScale(&this->actor, 0.25f);
    this->actionFunc = func_80A4FB10;
    this->item = drawIndex[itemIndex];
    this->action = actionIndex[itemIndex];
    objIndex = Object_GetIndex(&globalCtx->objectCtx, bankIndex[itemIndex]);
    if (objIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->object = objIndex;
    }
}

void DemoGetitem_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80A4FB10(DemoGetitem* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->object) != 0) {
        this->actor.draw = NULL;
        this->actor.objBankIndex = this->object;
        this->actionFunc = func_80A4FB68;
    }
}

void func_80A4FB68(DemoGetitem* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s16 sp22 = (globalCtx->gameplayFrames * 0x3E8) & 0xFFFF;

    if (Cutscene_CheckActorAction(globalCtx, this->action) != 0) {
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, this->action)]->action != 4) {
            this->actor.shape.yOffset = 0.0f;
        }
        switch (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, this->action)]->action) {
            case 2:
                this->actor.draw = func_80A4FCF0;
                Cutscene_ActorTranslate(&this->actor, globalCtx, Cutscene_GetActorActionIndex(globalCtx, this->action));
                this->actor.shape.rot.y = this->actor.shape.rot.y + 0x3E8;
                return;
            case 3:
                Actor_MarkForDeath(&this->actor);
                return;
            case 4:
                this->actor.draw = func_80A4FCF0;
                Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx,
                                              Cutscene_GetActorActionIndex(globalCtx, this->action));
                this->actor.shape.yOffset = Math_SinS(sp22) * 15.0f;
                return;
        }
        this->actor.draw = NULL;
    } else {
        this->actor.draw = NULL;
    }
}

void DemoGetitem_Update(Actor* thisx, GlobalContext* globalCtx) {
    DemoGetitem* this = THIS;

    this->actionFunc(this, globalCtx);
}

void func_80A4FCF0(Actor* thisx, GlobalContext* globalCtx) {
    DemoGetitem* this = THIS;

    func_800B8050(&this->actor, globalCtx, 0);
    func_800B8118(&this->actor, globalCtx, 0);
    GetItem_Draw(globalCtx, this->item);
}
