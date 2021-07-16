#include "z_en_bji_01.h"

#define FLAGS 0x00000019

#define THIS ((EnBji01*)thisx)

/*void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx);*/
void EnBji01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*extern UNK_TYPE D_809CDC50;*/
extern FlexSkeletonHeader D_0600578C;
extern AnimationHeader D_06000FDC;

/*
const ActorInit En_Bji_01_InitVars = {
    ACTOR_EN_BJI_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJI,
    sizeof(EnBji01),
    (ActorFunc)EnBji01_Init,
    (ActorFunc)EnBji01_Destroy,
    (ActorFunc)EnBji01_Update,
    (ActorFunc)EnBji01_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CCDE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CCE98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CCEE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD70C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CD77C.asm")

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/EnBji01_Init.asm")*/

/*? func_8013E3B8(EnBji01 *, void *, ?); // extern
? func_801A5BD0(?); // extern
? func_801A89A8(?); // extern
? func_809CCE98(EnBji01 *, GlobalContext *); // extern*/
extern ColliderCylinderInit D_809CDC50;

void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx) {

    EnBji01* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 30.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600578C, &D_06000FDC, this->jointTable, this->morphTable, 0x10);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_809CDC50);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 0;
    this->actor.child = NULL;
    this->unk_298 = -1;
    Actor_SetScale(&this->actor, 0.01f);
    func_8013E3B8(&this->actor, &this->unk_2AC, 1);
    this->moonsTear = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_PROP, ACTOR_OBJ_MOON_STONE);
    switch (gSaveContext.entranceIndex) {
	    case 0x4C00: /* Observatory from ECT */
	    case 0x4C10: /* Observatory from Termina Field door */
		    this->actor.params = 0;
                    func_809CCE98(&this->actor, globalCtx);
		    break;
	    case 0x4C20: /* Observatory from Termina Field telescope */
		    this->actor.flags |= 0x10000;
                    func_801A5BD0(0);
                    func_801A89A8(0xE0000100);
                    this->actor.params = 3;
                    func_809CCE98(&this->actor, globalCtx);
		    break;
	    default:
                    Actor_MarkForDeath(&this->actor);
		    break;
    }

}


/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/EnBji01_Destroy.asm")*/

void EnBji01_Destroy(Actor* thisx, GlobalContext *globalCtx) {

    EnBji01* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);

}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/EnBji01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CDA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/func_809CDB04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bji_01_0x809CCDE0/EnBji01_Draw.asm")
