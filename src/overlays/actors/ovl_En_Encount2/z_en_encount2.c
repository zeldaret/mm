#include "z_en_encount2.h"

#define FLAGS 0x00000010

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);


const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    (ActorFunc)EnEncount2_Destroy,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw
};

static ColliderJntSphElementInit D_808E1EF0[1] = {
//static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

//glabel D_808E1F14 collider init
static ColliderJntSphInit D_808E1F14 = {
//static ColliderJntSphInit sJntSphInit = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_808E1EF0,
    //1, sJntSphElementsInit,
};

DamageTable D_808E1F24[] = {
    0xF0, 0xF0, 0x00, 0xF0, 0xE1, 0xE1, 0x00, 0xE1, 0xF0, 0xF0, 0xF0, 0xE1, 0xE1, 0xE1, 0xF0, 0xF0, 
    0xE1, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0xE1, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
};

UNK_TYPE1 unkpadding[] = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
};

/*
// does not fit because THIS
void EnEncount2_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnEncount2* this = THIS;
    BgMeshHeader* bgMeshHeader = NULL;

    BcCheck3_BgActorInit((DynaPolyActor *) this, 0);
    BgCheck_RelocateMeshHeader(&D_06002420, &bgMeshHeader);
    this->unk144 = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, (DynaPolyActor *) this, bgMeshHeader);
    ActorShape_Init(&this->actor.shape, 0.0f, 
        (void (*)(struct Actor *actor, struct Lights *mapper, struct GlobalContext *ctxt)) func_800B3FC0, 25.0f);
    this->actor.colChkInfo.mass = 0xFF;
    //Collider_InitAndSetJntSph(globalCtx, thisx + 0x170, thisx, &D_808E1F14, thisx + 0x190);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, &this->colElement);

    this->actor.targetMode = 6;
    this->actor.colChkInfo.health = 1;
    //this->unk168 = D_808E1F50;
    this->unk168 = 0.1;
    this->unk164 = (s16) (this->actor.params & 0x7F);

    if (this->unk164 == 0x7F) {
        this->unk164 = (u16) -1;
    }

    if ((this->unk164 >= 0) && (Actor_GetSwitchFlag(globalCtx, this->unk164) != 0)) {
        Actor_MarkForDeath(this);
        return;
    }

    this->collider.elements->dim.modelSphere.radius = 0x39;
    this->collider.elements->dim.scale = 1.0f;
    this->collider.elements->dim.modelSphere.center.x = 0;
    this->collider.elements->dim.modelSphere.center.y = -4;
    this->collider.elements->dim.modelSphere.center.z = 0;

    this->actor.colChkInfo.damageTable = &D_808E1F24;
    func_808E16FC(this);
} // */

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/EnEncount2_Init.asm")

void EnEncount2_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnEncount2* this = THIS;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->unk144);
    Collider_DestroyJntSph(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E16FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E1714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E17C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E18A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/EnEncount2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/EnEncount2_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E1A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E1B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Encount2_0x808E1560/func_808E1C9C.asm")
