#include "z_en_weather_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnWeatherTag*)thisx)

void EnWeatherTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWeatherTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWeatherTag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWeatherTag_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Weather_Tag_InitVars = {
    ACTOR_EN_WEATHER_TAG,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnWeatherTag),
    (ActorFunc)EnWeatherTag_Init,
    (ActorFunc)EnWeatherTag_Destroy,
    (ActorFunc)EnWeatherTag_Update,
    (ActorFunc)EnWeatherTag_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/EnWeatherTag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/EnWeatherTag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_8096689C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966F74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80966FEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80967060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80967148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_809671A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_809671B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80967250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_809672DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_809674C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/func_80967608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/EnWeatherTag_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Weather_Tag/EnWeatherTag_Draw.s")
