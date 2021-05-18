#include "z_tg_sw.h"

#define FLAGS 0x00000010

#define THIS ((TGSw*)thisx)

// Prototypes
void TGSw_Init(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Update(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Draw(Actor* thisx, GlobalContext* globalCtx);

static void TGSw_ActionExecuteOneShot(struct TGSw* this, GlobalContext* globalCtx);

const ActorInit TG_Sw_InitVars = {
    ACTOR_TG_SW,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(TGSw),
    (ActorFunc)TGSw_Init,
    (ActorFunc)TGSw_Destroy,
    (ActorFunc)TGSw_Update,
    (ActorFunc)TGSw_Draw,
};

static void TGSw_ActionDecider(struct TGSw* this, GlobalContext* globalCtx) {
    f32 scaledAbsoluteRotZ;
    f32 scaledAbsoluteRotY;
    u8 unk1F4;

    // Maybe actorCtx Debug Flag?
    if (!!globalCtx->actorCtx.unk1F5) {
        scaledAbsoluteRotY = ABS_ALT(this->actor.world.rot.y) * 4.0f;
        scaledAbsoluteRotZ = ABS_ALT(this->actor.world.rot.z) * 4.0f;

        if (!(scaledAbsoluteRotZ < this->actor.xzDistToPlayer) && !(scaledAbsoluteRotY < this->actor.yDistToPlayer)) {
            unk1F4 = globalCtx->actorCtx.unk1F4;
            if (unk1F4 == 2 || !unk1F4) {
                this->actionFunc = &TGSw_ActionExecuteOneShot;
            }
        }
    }
}

static void TGSw_ActionExecuteOneShot(struct TGSw* this, GlobalContext* globalCtx) {
    void* actorIterator;
    struct Actor* actorEntry;

    actorIterator = NULL;
    do {
        actorEntry =
            func_ActorCategoryIterateById(globalCtx, (struct Actor*)actorIterator, ACTORCAT_ENEMY, ACTOR_EN_SW);
        if (actorIterator = (void*)!actorEntry) {
            break;
        }

        if ((((this->actor.params & 0xFC) >> 2) & 0xFF) == (((actorEntry->params & 0xFC) >> 2) & 0xFF)) {
            // Prevents register swap
            if (1) {}
            actorEntry->parent = (struct Actor*)this;
            actorEntry->speedXZ = ABS_ALT(this->actor.world.rot.x);
            break;
        }
    } while (actorIterator = actorEntry->next);

    actorIterator = NULL;
    do {
        actorEntry = func_ActorCategoryIterateById(globalCtx, actorIterator, ACTORCAT_NPC, ACTOR_EN_SW);
        if (actorIterator = (void*)!actorEntry) {
            break;
        }

        if ((((this->actor.params & 0xFC) >> 2) & 0xFF) == (((actorEntry->params & 0xFC) >> 2) & 0xFF)) {
            actorEntry->parent = (struct Actor*)this;
            actorEntry->speedXZ = ABS_ALT(this->actor.world.rot.x);
            break;
        }
    } while (actorIterator = actorEntry->next);

    Actor_MarkForDeath((Actor*)this);
}

void TGSw_Init(Actor* thisx, GlobalContext* globalCtx) {
    TGSw* this = THIS;
    this->actor.cutscene = this->actor.world.rot.z;
    this->actionFunc = &TGSw_ActionDecider;
}

void TGSw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ;
}

void TGSw_Update(Actor* thisx, GlobalContext* globalCtx) {
    TGSw* this = THIS;
    this->actionFunc(this, globalCtx);
}

void TGSw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad0;
    s32 absoluteRotZ;
    s32 absoluteRotY;
    f32 factoredRotZ;
    TGSw* this = THIS;

    if (!!sREG(0)) {
        absoluteRotZ = ABS_ALT(this->actor.world.rot.z);
        factoredRotZ = absoluteRotZ * 0.2f;
        // if needs to use the factored Rot as a var, "true" doesnt work
        if (factoredRotZ) {
            ;
        }
        absoluteRotY = ABS_ALT(this->actor.world.rot.y);

        DebugDisplay_AddObject(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0,
                               this->actor.shape.rot.y, 0, 0.1f, 0.1f, factoredRotZ, 0xA0, 0xA0, 0xA0, 0xFF, 6,
                               globalCtx->state.gfxCtx);
        DebugDisplay_AddObject(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0.1f,
                               absoluteRotY * 0.2f, 0.1f, 0xA0, 0xA0, 0xA0, 0xFF, 6, globalCtx->state.gfxCtx);
        this->actor.shape.rot.y = (s16)(this->actor.shape.rot.y + 0x1000);
    }
}
