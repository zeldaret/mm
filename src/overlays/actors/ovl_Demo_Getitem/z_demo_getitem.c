/*
 * File: z_demo_getitem.c
 * Overlay: ovl_Demo_Getitem
 * Description: Cutscene object for Great Fairy's Mask and Great Fairy's Sword
 */

#include "z_demo_getitem.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoGetitem*)thisx)

void DemoGetitem_Init(Actor* thisx, PlayState* play);
void DemoGetitem_Destroy(Actor* thisx, PlayState* play);
void DemoGetitem_Update(Actor* thisx, PlayState* play);

void func_80A4FB10(DemoGetitem* this, PlayState* play);
void func_80A4FB68(DemoGetitem* this, PlayState* play2);
void func_80A4FCF0(Actor* thisx, PlayState* play);

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

static s16 csDrawIndex[] = { GID_MASK_GREAT_FAIRY, GID_SWORD_GREAT_FAIRY };

static u16 csActionIndex[] = {
    0x6E,
    0x236,
};

void DemoGetitem_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    s32 objIndex;
    s32 itemIndex;
    DemoGetitem* this = THIS;

    itemIndex = 0;
    if (DEMOGETITEM_GET_F(thisx) == 1) {
        itemIndex = 1;
    }
    Actor_SetScale(&this->actor, 0.25f);
    this->actionFunc = func_80A4FB10;
    this->item = csDrawIndex[itemIndex];
    this->action = csActionIndex[itemIndex];
    objIndex = Object_GetIndex(&play->objectCtx, bankIndex[itemIndex]);
    if (objIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->object = objIndex;
    }
}

void DemoGetitem_Destroy(Actor* thisx, PlayState* play) {
}

void func_80A4FB10(DemoGetitem* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->object) != 0) {
        this->actor.draw = NULL;
        this->actor.objBankIndex = this->object;
        this->actionFunc = func_80A4FB68;
    }
}

void func_80A4FB68(DemoGetitem* this, PlayState* play2) {
    PlayState* play = play2;
    u16 sp22 = (play->gameplayFrames * 1000) & 0xFFFF;

    if (Cutscene_CheckActorAction(play, this->action)) {
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->action)]->action != 4) {
            this->actor.shape.yOffset = 0.0f;
        }
        switch (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->action)]->action) {
            case 2:
                this->actor.draw = func_80A4FCF0;
                Cutscene_ActorTranslate(&this->actor, play, Cutscene_GetActorActionIndex(play, this->action));
                this->actor.shape.rot.y += 1000;
                return;
            case 3:
                Actor_MarkForDeath(&this->actor);
                return;
            case 4:
                this->actor.draw = func_80A4FCF0;
                Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->action));
                this->actor.shape.yOffset = Math_SinS(sp22) * 15.0f;
                return;
        }
        this->actor.draw = NULL;
    } else {
        this->actor.draw = NULL;
    }
}

void DemoGetitem_Update(Actor* thisx, PlayState* play) {
    DemoGetitem* this = THIS;

    this->actionFunc(this, play);
}

void func_80A4FCF0(Actor* thisx, PlayState* play) {
    DemoGetitem* this = THIS;

    func_800B8050(&this->actor, play, 0);
    func_800B8118(&this->actor, play, 0);
    GetItem_Draw(play, this->item);
}
