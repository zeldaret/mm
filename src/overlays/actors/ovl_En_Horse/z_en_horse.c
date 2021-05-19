#include "z_en_horse.h"

#define FLAGS 0x00000010

#define THIS ((EnHorse*)thisx)

void EnHorse_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Horse_InitVars = {
    ACTOR_EN_HORSE,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHorse),
    (ActorFunc)EnHorse_Init,
    (ActorFunc)EnHorse_Destroy,
    (ActorFunc)EnHorse_Update,
    (ActorFunc)EnHorse_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087B730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087B784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087B7C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C0AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C1C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C38C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C43C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C8D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C8E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C9D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C9EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087C9F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087CA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/EnHorse_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087D540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/EnHorse_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087D70C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087D75C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087D814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087D988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087DDEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087DE28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087DF64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E2A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E5B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E5D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E6D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087E9D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087EA1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087EB54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087EB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087EC20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087EC78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087ED10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087EEC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F1FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F39C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F5B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F9A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087F9C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087FB08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087FB14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087FD94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087FDB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087FF08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8087FF14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808801A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808801F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808802D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808804A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808804CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880534.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808806DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880D50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80880E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8088126C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8088159C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8088168C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808819D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881BDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80881F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808821C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808822CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8088247C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80882564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808826B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80882820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808829D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808829F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80882A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80882B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80882D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80882DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883BEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883CB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80883F98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808840C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8088424C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808843B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808844E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808846B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808846DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808846F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808848C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884A40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80884E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808850DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808853E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_8088598C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885A80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885C90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80885DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80886C00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80886DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80886FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808870A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_808871A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80887270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/EnHorse_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80887D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80887D60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80887E64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80887EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80887F58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80888C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/func_80888D18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Horse_0x8087B730/EnHorse_Draw.asm")
