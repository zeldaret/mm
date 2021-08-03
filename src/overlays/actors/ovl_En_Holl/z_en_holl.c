#include "z_en_holl.h"

#define FLAGS 0x00000010

#define THIS ((EnHoll*)thisx)

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80899960(EnHoll* this);
void func_808999B0(GlobalContext* globalCtx, EnHoll* this, UNK_PTR unkPtr);

const ActorInit En_Holl_InitVars = {
    ACTOR_EN_HOLL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHoll),
    (ActorFunc)EnHoll_Init,
    (ActorFunc)EnHoll_Destroy,
    (ActorFunc)EnHoll_Update,
    (ActorFunc)EnHoll_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

static UNK_PTR D_8089A5B8 = 0;

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_808999B0.asm")

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;
    UNK_TYPE4 pad[5];

    Actor_ProcessInitChain(&this->actor, sInitChain);
    func_80899960(this);
    this->alwaysZero = 0;
    this->opacity = 0xFF;
    func_808999B0(globalCtx, this, &pad[1]);
}

//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Destroy.asm")

void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHoll* this = THIS;

    if (this->type != 4) {
	u32 transitionActorIndex = ((u16)this->actor.params) >> 0xA;

        globalCtx->doorCtx.transitionActorList[transitionActorIndex].id = -globalCtx->doorCtx.transitionActorList[transitionActorIndex].id;
        if (this == D_8089A5B8) {
            D_8089A5B8 = NULL;
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899ACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A0C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Draw.asm")
