#include "z_en_kame.h"

#define FLAGS 0x00000405

#define THIS ((EnKame*)thisx)

void EnKame_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKame_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kame_InitVars = {
    ACTOR_EN_KAME,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_TL,
    sizeof(EnKame),
    (ActorFunc)EnKame_Init,
    (ActorFunc)EnKame_Destroy,
    (ActorFunc)EnKame_Update,
    (ActorFunc)EnKame_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/EnKame_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/EnKame_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD6F34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD6F9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7018.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD70A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD70EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD71B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7254.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD73A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7424.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD75A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD76CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7798.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD792C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7948.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7B18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7B90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7C54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7D40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7E0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7EC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7F10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7FA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD7FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD810C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD825C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8364.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD84C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/EnKame_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/EnKame_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8CEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kame_0x80AD6DD0/func_80AD8D64.asm")
