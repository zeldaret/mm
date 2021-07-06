#include "z_obj_hgdoor.h"

#define FLAGS 0x00100000

#define THIS ((ObjHgdoor*)thisx)

void ObjHgdoor_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHgdoor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHgdoor_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHgdoor_Draw(Actor* thisx, GlobalContext* globalCtx);

void ObjHgdoor_SetupCheckShouldOpen(ObjHgdoor* this);
void ObjHgdoor_CheckShouldOpen(ObjHgdoor* this, GlobalContext* globalCtx);
void func_80BD42AC(ObjHgdoor* this);
void func_80BD42C0(ObjHgdoor* this, GlobalContext* globalCtx);
void func_80BD433C(ObjHgdoor* this);
void func_80BD4358(ObjHgdoor* this, GlobalContext* globalCtx);
void func_80BD4460(ObjHgdoor* this);
void func_80BD4478(ObjHgdoor* this, GlobalContext* globalCtx);
s32 func_80BD44D0(ObjHgdoor* this, GlobalContext* globalCtx);

extern CollisionHeader D_06001D10;
extern CollisionHeader D_060018C0;
extern Gfx D_06001AB0[];
extern Gfx D_06001BA8[];
extern Gfx D_06001670[];
extern Gfx D_06001768[];

const ActorInit Obj_Hgdoor_InitVars = {
    ACTOR_OBJ_HGDOOR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HGDOOR,
    sizeof(ObjHgdoor),
    (ActorFunc)ObjHgdoor_Init,
    (ActorFunc)ObjHgdoor_Destroy,
    (ActorFunc)ObjHgdoor_Update,
    (ActorFunc)ObjHgdoor_Draw,
};

static s16 D_80BD4690 = 0;
static s32 unused = 0;
static s32 unused2 = 0;

void ObjHgdoor_SetChild(ObjHgdoor* this, GlobalContext* globalCtx) {
    Actor* actorIterator = globalCtx->actorCtx.actorList[ACTORCAT_PROP].first;

    while (actorIterator) {
        if ((actorIterator->id == ACTOR_OBJ_HGDOOR) && (&this->dyna.actor != actorIterator)) {
            this->dyna.actor.child = actorIterator;
            break;
        }
        actorIterator = actorIterator->next;
    }
}

void ObjHgdoor_SetParent(ObjHgdoor* this, GlobalContext* globalCtx) {
    Actor* actorIterator = globalCtx->actorCtx.actorList[ACTORCAT_PROP].first;

    while (actorIterator) {
        if (actorIterator->id == ACTOR_EN_HG) {
            this->dyna.actor.parent = actorIterator;
            break;
        }
        actorIterator = actorIterator->next;
    }
}

void ObjHgdoor_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjHgdoor* this = THIS;
    s32 pad;
    CollisionHeader* header = NULL;

    Actor_SetScale(&this->dyna.actor, 0.1f);
    BcCheck3_BgActorInit(&this->dyna, 1);
    if (OBJHGDOOR_IS_RIGHT_DOOR(&this->dyna.actor)) {
        BgCheck_RelocateMeshHeader(&D_06001D10, &header);
    } else {
        BgCheck_RelocateMeshHeader(&D_060018C0, &header);
    }
    this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, header);
    this->rotation = 0;
    this->timer = 0;
    this->cutscene = this->dyna.actor.cutscene;
    ObjHgdoor_SetupCheckShouldOpen(this);
}

void ObjHgdoor_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjHgdoor* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjHgdoor_SetupCheckShouldOpen(ObjHgdoor* this) {
    this->actionFunc = ObjHgdoor_CheckShouldOpen;
}

void ObjHgdoor_CheckShouldOpen(ObjHgdoor* this, GlobalContext* globalCtx) {
    if (!(gSaveContext.weekEventReg[75] & 0x20) && !(gSaveContext.weekEventReg[52] & 0x20) &&
        (this->dyna.actor.xzDistToPlayer < 100.0f) && (this->dyna.actor.yDistToPlayer < 40.0f) &&
        OBJHGDOOR_IS_RIGHT_DOOR(&this->dyna.actor)) {
        ObjHgdoor_SetChild(this, globalCtx);
        ObjHgdoor_SetParent(this, globalCtx);
        func_80BD42AC(this);
    }
}

void func_80BD42AC(ObjHgdoor* this) {
    this->actionFunc = func_80BD42C0;
}

void func_80BD42C0(ObjHgdoor* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->dyna.actor);
        func_80BD433C(this);
        func_80BD433C((ObjHgdoor*)this->dyna.actor.child);
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void func_80BD433C(ObjHgdoor* this) {
    this->unk166 = 0x63;
    this->actionFunc = func_80BD4358;
}

void func_80BD4358(ObjHgdoor* this, GlobalContext* globalCtx) {
    u32 actionIndex;

    if (func_800EE29C(globalCtx, 0x1E3)) {
        actionIndex = func_800EE200(globalCtx, 0x1E3);
        if (this->unk166 != globalCtx->csCtx.npcActions[actionIndex]->unk0) {
            this->unk166 = globalCtx->csCtx.npcActions[actionIndex]->unk0;
            switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
                case 1:
                    Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_WOOD_DOOR_OPEN_SPEEDY);
                    if ((this->dyna.actor.parent != NULL) && (this->dyna.actor.parent->id == ACTOR_EN_HG)) {
                        this->dyna.actor.parent->colChkInfo.health = 1;
                    }
                    D_80BD4690 = 1;
                    break;
                case 2:
                    break;
            }
        }
        if ((D_80BD4690 == 1) && (func_80BD44D0(this, globalCtx))) {
            func_80BD4460(this);
        }
    } else {
        this->unk166 = 0x63;
    }
}

void func_80BD4460(ObjHgdoor* this) {
    this->timer = 0;
    this->actionFunc = func_80BD4478;
}

void func_80BD4478(ObjHgdoor* this, GlobalContext* globalCtx) {
    if (this->timer++ > 80 && !ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Stop(this->cutscene);
    }
}

s32 func_80BD44D0(ObjHgdoor* this, GlobalContext* globalCtx) {
    if (this->rotation < 0x5555) {
        this->rotation += 0x1388;
    } else {
        return true;
    }

    return false;
}

void func_80BD4500(ObjHgdoor* this) {
    this->dyna.actor.shape.rot.y = this->dyna.actor.home.rot.y;
    if (OBJHGDOOR_IS_RIGHT_DOOR(&this->dyna.actor)) {
        this->dyna.actor.shape.rot.y += this->rotation;
    } else {
        this->dyna.actor.shape.rot.y -= this->rotation;
    }
}

void ObjHgdoor_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHgdoor* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80BD4500(this);
}

void ObjHgdoor_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (OBJHGDOOR_IS_RIGHT_DOOR(thisx)) {
        gSPDisplayList(POLY_OPA_DISP++, D_06001AB0);
        gSPDisplayList(POLY_OPA_DISP++, D_06001BA8);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, D_06001670);
        gSPDisplayList(POLY_OPA_DISP++, D_06001768);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
