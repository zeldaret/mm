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
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnWeatherTag),
    (ActorFunc)EnWeatherTag_Init,
    (ActorFunc)EnWeatherTag_Destroy,
    (ActorFunc)EnWeatherTag_Update,
    (ActorFunc)EnWeatherTag_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_8096689C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966A08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966AE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966BF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966D20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966E0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966E84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966EF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966F74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80966FEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80967060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80967148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_809671A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_809671B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80967250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_809672DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_809674C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/func_80967608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Draw.asm")
