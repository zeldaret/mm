/*
 * File: z_en_sekihi.c
 * Overlay: ovl_En_Sekihi
 * Description: Mikau's Grave & Song Pedestals
 */

#include "z_en_sekihi.h"
#include "objects/object_sekihil/object_sekihil.h"
#include "objects/object_sekihig/object_sekihig.h"
#include "objects/object_sekihin/object_sekihin.h"
#include "objects/object_sekihiz/object_sekihiz.h"
#include "objects/object_zog/object_zog.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnSekihi*)thisx)

void EnSekihi_Init(Actor* thisx, PlayState* play);
void EnSekihi_Destroy(Actor* thisx, PlayState* play);
void EnSekihi_Update(Actor* thisx, PlayState* play);
void EnSekihi_Draw(Actor* thisx, PlayState* play);

void func_80A44DE8(EnSekihi* this, PlayState* play);
void func_80A450B0(EnSekihi* this, PlayState* play);
void EnSekihi_DoNothing(EnSekihi* this, PlayState* play);

const ActorInit En_Sekihi_InitVars = {
    ACTOR_EN_SEKIHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSekihi),
    (ActorFunc)EnSekihi_Init,
    (ActorFunc)EnSekihi_Destroy,
    (ActorFunc)EnSekihi_Update,
    (ActorFunc)NULL,
};

static s16 sObjectIds[] = { OBJECT_SEKIHIL, OBJECT_SEKIHIG, OBJECT_SEKIHIN, OBJECT_SEKIHIZ, OBJECT_ZOG };

static Gfx* sOpaDLists[] = {
    gGraveTriforceSymbolDL, gGraveGoronSymbolDL, gGraveKokiriSymbolDL, gTombSongOfSoaringDL, gMikauGraveDL,
};

static Gfx* sXluDLists[] = {
    gSunSongTriforceSymbolDL, gSunSongGoronSymbolDL, gSunSongKokiriSymbolDL, gSekihizEmptyDL, gMikauGraveDirtDL,
};

static u16 sTextIds[] = { 0, 0, 0, 0, 0x1018 };

void EnSekihi_Init(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;
    s32 params = ENSIKIHI_GET_TYPE(thisx);
    s32 objectIndex;
    s32 pad;

    if ((params < SEKIHI_TYPE_0 || params >= SEKIHI_TYPE_MAX) || sOpaDLists[params] == NULL) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        if ((params == SEKIHI_TYPE_4) && (((gSaveContext.save.skullTokenCount & 0xFFFF)) >= 30)) {
            gSaveContext.save.weekEventReg[13] |= 0x20;
        }
        objectIndex = Object_GetIndex(&play->objectCtx, sObjectIds[params]);
        if (objectIndex >= 0) {
            this->objectIndex = objectIndex;
        }
        this->actionFunc = func_80A44DE8;
        this->opaDList = sOpaDLists[params];
        this->xluDList = sXluDLists[params];
        this->dyna.actor.textId = sTextIds[params];
        this->dyna.actor.focus.pos.y = this->dyna.actor.world.pos.y + 60.0f;
        Actor_SetScale(&this->dyna.actor, 0.1f);
    }
}

void EnSekihi_Destroy(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80A44DE8(EnSekihi* this, PlayState* play) {
    CollisionHeader* colHeader = NULL;
    s32 params;
    CollisionHeader* colHeaders[] = {
        &gSekihilCol, &gSekihigCol, &gSekihinCol, &gSekihizCol, &gObjectZogCol,
    };

    params = ENSIKIHI_GET_TYPE(&this->dyna.actor);
    if (Object_IsLoaded(&play->objectCtx, this->objectIndex)) {
        this->dyna.actor.objBankIndex = this->objectIndex;
        this->dyna.actor.draw = EnSekihi_Draw;
        if (params == SEKIHI_TYPE_4) {
            this->actionFunc = func_80A450B0;
        } else {
            this->actionFunc = EnSekihi_DoNothing;
        }

        Actor_SetObjectDependency(play, &this->dyna.actor);
        DynaPolyActor_Init(&this->dyna, 0);
        if (colHeaders[params] != NULL) {
            CollisionHeader_GetVirtual(colHeaders[params], &colHeader);
        }

        this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
        if ((params == SEKIHI_TYPE_4) && (INV_CONTENT(ITEM_MASK_ZORA) != ITEM_MASK_ZORA)) {
            Actor_MarkForDeath(&this->dyna.actor);
        }
    }
}

void func_80A44F40(EnSekihi* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            if (Message_ShouldAdvance(play) && (play->msgCtx.currentTextId == 0x1019)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(play, 0x101A);
                        break;
                    case 1:
                        func_8019F208();
                        func_80151938(play, 0x101B);
                        break;
                    case 2:
                        func_8019F230();
                        func_801477B4(play);
                        this->actionFunc = func_80A450B0;
                        break;
                }
            } else {
                break;
            }
            break;
        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x1018:
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;
                    case 0x101A:
                    case 0x101B:
                        func_801477B4(play);
                        this->actionFunc = func_80A450B0;
                        break;
                }
            }
            break;
    }
}

void func_80A450B0(EnSekihi* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->dyna.actor, &play->state)) {
        this->actionFunc = func_80A44F40;
    } else if ((this->dyna.actor.xzDistToPlayer < 100.0f) && (Player_IsFacingActor(&this->dyna.actor, 0x2600, play))) {
        func_800B8614(&this->dyna.actor, play, 120.0f);
    }
}

void EnSekihi_DoNothing(EnSekihi* this, PlayState* play) {
}

void EnSekihi_Update(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;

    this->actionFunc(this, play);
}

void EnSekihi_Draw(Actor* thisx, PlayState* play) {
    EnSekihi* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->xluDList != NULL) {
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C2DC(play->state.gfxCtx);
        gSPDisplayList(POLY_XLU_DISP++, this->xluDList);
    }

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(play->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->opaDList);

    CLOSE_DISPS(play->state.gfxCtx);
}
