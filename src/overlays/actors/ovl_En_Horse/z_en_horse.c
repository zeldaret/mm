#include "z_en_horse.h"

#define FLAGS 0x00000010

#define THIS ((EnHorse*)thisx)

void EnHorse_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorse_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80888F74 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_PLAYER, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1 | OC2_UNK1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000004, 0x00, 0x02 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80888FA0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1 | OC2_UNK1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80888FCC[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00013820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_AT_INFO | BUMP_NO_DAMAGE | BUMP_NO_SWORD_SFX | BUMP_NO_HITMARK, OCELEM_ON, },
        { 13, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80888FF0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1 | OC2_UNK1, COLSHAPE_JNTSPH, },
    1, D_80888FCC, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80889000 = { 10, 35, 100, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80889010[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80888F74;
extern ColliderCylinderInit D_80888FA0;
extern ColliderJntSphElementInit D_80888FCC[1];
extern ColliderJntSphInit D_80888FF0;
extern CollisionCheckInfoInit D_80889000;
extern InitChainEntry D_80889010[];

extern UNK_TYPE D_06008C68;
extern UNK_TYPE D_0600A8DC;
extern UNK_TYPE D_0600AD08;
extern UNK_TYPE D_0600B3E0;
extern UNK_TYPE D_0600BDE0;
extern UNK_TYPE D_0600D178;
extern UNK_TYPE D_0600D4E8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087B730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087B784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087B7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C0AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C1C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C38C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C43C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C8D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C9D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C9EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087C9F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087CA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087D540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087D70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087D75C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087D814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087D988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087DDEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087DE28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087DF64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E2A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E5B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E5D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E6D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087E9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087EA1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087EB54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087EB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087EC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087EC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087ED10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087EEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F1FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F39C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F5B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F9A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087F9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087FB08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087FB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087FD94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087FDB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087FF08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8087FF14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808801A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808801F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808802D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808804A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808804CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808806DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80880E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8088126C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8088159C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8088168C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808819D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881BDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80881F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808821C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808822CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8088247C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80882564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808826B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80882820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808829D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808829F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80882A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80882B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80882D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80882DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80883F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808840C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8088424C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808843B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808844E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808846B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808846DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808846F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808848C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884A40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80884E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808850DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808853E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_8088598C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80885DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80886C00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80886DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80886FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808870A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_808871A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80887270.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80887D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80887D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80887E64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80887EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80887F58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80888C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/func_80888D18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse/EnHorse_Draw.s")
