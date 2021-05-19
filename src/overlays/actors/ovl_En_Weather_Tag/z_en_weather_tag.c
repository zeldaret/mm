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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_8096689C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966A68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966BF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966F74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80966FEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809671A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809671B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809672DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_809674C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/func_80967608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Weather_Tag_0x80966410/EnWeatherTag_Draw.asm")
