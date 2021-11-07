/*
 * File: z_en_elfgrp.c
 * Overlay: ovl_En_Elfgrp
 * Description: Group of Stray Fairies in Fairy Fountain
 */

#include "z_en_elfgrp.h"

#define FLAGS 0x00000010

#define THIS ((EnElfgrp*)thisx)

void EnElfgrp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElfgrp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElfgrp_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Elfgrp_InitVars = {
    ACTOR_EN_ELFGRP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElfgrp),
    (ActorFunc)EnElfgrp_Init,
    (ActorFunc)EnElfgrp_Destroy,
    (ActorFunc)EnElfgrp_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A396B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/EnElfgrp_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/EnElfgrp_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A39BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A39C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A39CD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A39DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A39F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A39FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A0AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A0F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A4AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A520.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A6F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A77C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/func_80A3A8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elfgrp/EnElfgrp_Update.s")
