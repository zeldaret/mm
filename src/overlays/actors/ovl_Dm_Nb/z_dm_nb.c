#include "z_dm_nb.h"

#define FLAGS 0x00000009

#define THIS ((DmNb*)thisx)

void DmNb_Init(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Update(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Draw(Actor* thisx, GlobalContext* globalCtx);

UNK_TYPE func_80C1DED0(DmNb* this, s32 arg1);
void func_80C1DF18(DmNb* this, GlobalContext* globalCtx);
void DmNb_UnkActorDraw(GlobalContext* globalCtx, s32 limbIndex, Actor *actor);

/*
const ActorInit Dm_Nb_InitVars = {
    ACTOR_DM_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(DmNb),
    (ActorFunc)DmNb_Init,
    (ActorFunc)DmNb_Destroy,
    (ActorFunc)DmNb_Update,
    (ActorFunc)DmNb_Draw
};
*/

extern SkeletonHeader D_06008C40; 

extern UNK_TYPE D_80C1E200;

extern s32 D_80C1E210[];
//static s32 D_80C1E210[] = {0, 0, 0, 0, 0}

UNK_TYPE func_80C1DED0(DmNb *this, s32 arg1) {
    UNK_TYPE ret = 0;

    if (arg1 != this->unk1F0) {
        this->unk1F0 = arg1;
        ret = func_8013BC6C(&this->skelAnime, &D_80C1E200, arg1);
    }
    return ret;
}

#if NON_MATCHING
void func_80C1DF18(DmNb *this, GlobalContext *globalCtx) {
    int i;
    s32 sp2C[5];
    u32 actorActionsIndex;
    u16 actorActionsUnk0;

    for(i=0; i<5; i++) {
        sp2C[i] = D_80C1E210[i];
    }
    if (globalCtx->csCtx.state != 0) {
        if (this->unk1F8 == 0) {
            this->unk1EC = 0xFF;
            this->unk1F8 = 1;
            this->unk1F4 = this->unk1F0;
        }
        if (func_800EE29C(globalCtx, 0x232)) {
            actorActionsIndex = func_800EE200(globalCtx, 0x232);
            actorActionsUnk0 = globalCtx->csCtx.actorActions[actorActionsIndex]->unk0;
            if ((actorActionsUnk0 & 0xFF) != this->unk1EC) {
                this->unk1EC = actorActionsUnk0;
                func_80C1DED0(this, sp2C[actorActionsUnk0]);
            }
            func_800EDF24(&this->actor, globalCtx, actorActionsIndex);
        }
    } else if (this->unk1F8 != 0) {
        this->unk1F8 = 0;
        func_80C1DED0(this, this->unk1F4);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Nb_0x80C1DED0/func_80C1DF18.asm")
#endif

void DmNb_Init(Actor *thisx, GlobalContext *globalCtx) {
    DmNb *this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06008C40, NULL, this->limbDrawTable, this->transitionDrawTable, 8);
    this->unk1F0 = -1;
    func_80C1DED0(this, 0);
    this->actor.flags &= ~1;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80C1DF18;
}

void DmNb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmNb_Update(Actor *thisx, GlobalContext *globalCtx) {
    DmNb *this = THIS;

    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_800B78B8(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
}

void DmNb_UnkActorDraw(GlobalContext* globalCtx, s32 limbIndex, Actor *actor) {    
}


void DmNb_Draw(Actor *thisx, GlobalContext *globalCtx) {
    DmNb *this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL, NULL, DmNb_UnkActorDraw, &this->actor);
}
