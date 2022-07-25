/*
 * File: z_demo_getitem.c
 * Overlay: ovl_Demo_Getitem
 * Description: Cutscene objectIndex for Great Fairy's Mask and Great Fairy's Sword
 */

#include "z_demo_getitem.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoGetitem*)thisx)

void DemoGetitem_Init(Actor* thisx, PlayState* play);
void DemoGetitem_Destroy(Actor* thisx, PlayState* play);
void DemoGetitem_Update(Actor* thisx, PlayState* play);

void func_80A4FB10(DemoGetitem* this, PlayState* play);
void func_80A4FB68(DemoGetitem* this, PlayState* play2);
void DemoGetitem_Draw(Actor* thisx, PlayState* play);

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

static s16 sObjectBankIndices[] = { OBJECT_GI_MASK14, OBJECT_GI_SWORD_4 };

static s16 sGetItemDraws[] = { GID_MASK_GREAT_FAIRY, GID_SWORD_GREAT_FAIRY };

static u16 sCsActionIndices[] = { 0x6E, 0x236 };

void DemoGetitem_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    s32 objectIndex;
    s32 itemIndex;
    DemoGetitem* this = THIS;

    itemIndex = 0;
    if (DEMOGETITEM_GET_F(thisx) == 1) {
        itemIndex = 1;
    }
    Actor_SetScale(&this->actor, 0.25f);
    this->actionFunc = func_80A4FB10;
    this->item = sGetItemDraws[itemIndex];
    this->csAction = sCsActionIndices[itemIndex];
    objectIndex = Object_GetIndex(&play->objectCtx, sObjectBankIndices[itemIndex]);
    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->objectIndex = objectIndex;
    }
}

void DemoGetitem_Destroy(Actor* thisx, PlayState* play) {
}

void func_80A4FB10(DemoGetitem* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->objectIndex)) {
        this->actor.draw = NULL;
        this->actor.objBankIndex = this->objectIndex;
        this->actionFunc = func_80A4FB68;
    }
}

void func_80A4FB68(DemoGetitem* this, PlayState* play2) {
    PlayState* play = play2;
    u16 sp22 = (play->gameplayFrames * 1000) & 0xFFFF;

    if (Cutscene_CheckActorAction(play, this->csAction)) {
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->csAction)]->action != 4) {
            this->actor.shape.yOffset = 0.0f;
        }
        switch (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->csAction)]->action) {
            case 2:
                this->actor.draw = DemoGetitem_Draw;
                Cutscene_ActorTranslate(&this->actor, play, Cutscene_GetActorActionIndex(play, this->csAction));
                this->actor.shape.rot.y += 0x3E8;
                return;
            case 3:
                Actor_MarkForDeath(&this->actor);
                return;
            case 4:
                this->actor.draw = DemoGetitem_Draw;
                Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->csAction));
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

void DemoGetitem_Draw(Actor* thisx, PlayState* play) {
    DemoGetitem* this = THIS;

    func_800B8050(&this->actor, play, 0);
    func_800B8118(&this->actor, play, 0);
    GetItem_Draw(play, this->item);
}
