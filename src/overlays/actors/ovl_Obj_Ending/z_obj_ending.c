#include "z_obj_ending.h"

#define FLAGS 0x00000030

#define THIS ((ObjEnding*)thisx)

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Ending_InitVars = {
    ACTOR_OBJ_ENDING,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ENDING_OBJ,
    sizeof(ObjEnding),
    (ActorFunc)ObjEnding_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjEnding_Update,
    (ActorFunc)ObjEnding_Draw
};
*/

extern InitChainEntry D_80C25CF8[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};
*/

extern unkStruct D_80C25CE0[];
/*
static unkStruct D_80C25CE0[] = {
    {0x06003440, 0x060031A0, 0x00000000},
    {0x00000000, 0x060003D0, 0x06001FF8}
};
*/

//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ending_0x80C25BC0/ObjEnding_Init.asm")
/* 
void ObjEnding_Init(ObjEnding *this, GlobalContext *globalCtx) {
    ObjEnding *temp_a0;
    char *temp_t9;
    void *temp_a0_2;

    temp_a0 = this;
    this = this;
    Actor_ProcessInitChain((Actor *) temp_a0, &D_80C25CF8);
    temp_t9 = (this->actor.params * 0xC) + &D_80C25CE0;
    this->unk_144 = temp_t9;
    temp_a0_2 = temp_t9->unk8;
    if (temp_a0_2 != 0) {
        this = this;
        this->unk148 = Lib_SegmentedToVirtual(temp_a0_2);
    }
}
*/
void ObjEnding_Init(Actor* thisx, GlobalContext *globalCtx) {
    ObjEnding* this = THIS;
    UNK_PTR *tempPtr;

    Actor_ProcessInitChain(&this->actor, D_80C25CF8);
    this->unk144 = &D_80C25CE0[this->actor.params];
    if(false){}
    tempPtr = this->unk144->unk8;
    
    if (tempPtr != NULL) {
        this->texturePtr = Lib_SegmentedToVirtual(tempPtr);
    }
}

void ObjEnding_Update(Actor *thisx, GlobalContext *globalCtx) {
}

//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ending_0x80C25BC0/ObjEnding_Draw.asm")
/*
void ObjEnding_Draw(ObjEnding *this, GlobalContext *globalCtx) {
    AnimatedTexture *temp_a1;
    AnimatedTexture *temp_a3;
    Gfx *temp_a1_3;
    char *temp_v0;
    s32 temp_a1_2;
    char *phi_v0;

    temp_a3 = this->unk148;
    temp_a1 = temp_a3;
    if (temp_a3 != 0) {
        this = this;
        SceneProc_DrawAllSceneAnimatedTextures(globalCtx, temp_a1);
    }
    temp_v0 = this->unk_144;
    temp_a1_2 = *temp_v0;
    phi_v0 = temp_v0;
    if (temp_a1_2 != 0) {
        this = this;
        func_800BDFC0(globalCtx, temp_a1_2);
        phi_v0 = this->unk_144;
    }
    temp_a1_3 = phi_v0->unk4;
    if (temp_a1_3 != 0) {
        func_800BE03C(globalCtx, temp_a1_3);
    }
}
*/
void ObjEnding_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjEnding *this = THIS;
    Gfx *dl;
    UNK_TYPE4 tempunk4;

    if (this->texturePtr != NULL) {
        SceneProc_DrawAllSceneAnimatedTextures(globalCtx, this->texturePtr);
    }
    tempunk4 = this->unk144->unk0;
    if (tempunk4 != 0) {
        func_800BDFC0(globalCtx, tempunk4);
    }
    dl = this->unk144->dl;
    if (dl != NULL) {
        func_800BE03C(globalCtx, dl);
    }
}
