#include "z_en_elfgrp.h"

#define FLAGS 0x00000010

#define THIS ((EnElfgrp*)thisx)

void EnElfgrp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElfgrp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElfgrp_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A396B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/EnElfgrp_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/EnElfgrp_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A39BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A39C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A39CD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A39DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A39F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A39FBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A0AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A0F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A4AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A6F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A77C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A7FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/func_80A3A8F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elfgrp_0x80A396B0/EnElfgrp_Update.asm")
