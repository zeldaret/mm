#include "z_en_test3.h"

#define FLAGS 0x04000030

#define THIS ((EnTest3*)thisx)

void EnTest3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A40A6C(); // TODO

u32 D_80A41530[] = {
    0x0C000142, 0x0A007018, 0x02063207, 0x140C0F07, 0x1E070033, 0x04010509, 0x0A050E06, 0x3207140F, 0x0A006F21,
    0x02060006, 0x1E150206, 0x1E06230D, 0x02062306, 0x3201050E, 0x06230632, 0x0E09010E, 0x0600061E, 0x0D050C00,
    0x02510033, 0x020A1100, 0x00330401, 0x0504000A, 0x0A007025, 0x0F0D00F0, 0x020F050F, 0x1915020F, 0x190F280D,
    0x020F2810, 0x0001050E, 0x0F281000, 0x1109010E, 0x0F050F19, 0x100A000D, 0x15020F37, 0x100A0902, 0x100A160A,
    0x01050903, 0x0E0F3710, 0x0A0C050D, 0x00030098, 0x01210800, 0x87014F40, 0x00820A00, 0x4F020907, 0x00332029,
    0x0A001324, 0x00330802, 0x0905003D, 0x08180033, 0x10070F13, 0x00010509, 0x05021300, 0x130A0105, 0x0E130013,
    0x0A140905, 0x050A0013, 0x07005A02, 0x02090905, 0x0A006C0D, 0x02040004, 0x0A01050E, 0x0400040A, 0x0B0A0061,
    0x2E02040A, 0x041E2200, 0x33011502, 0x041E042D, 0x0902042D, 0x06000105, 0x09060E04, 0x1E042D13, 0x02041E06,
    0x00010509, 0x080E040A, 0x041E1205, 0x0A000D07, 0x00330801, 0x05090405, 0x05000000,
};

const ActorInit En_Test3_InitVars = {
    ACTOR_EN_TEST3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TEST3,
    sizeof(EnTest3),
    (ActorFunc)EnTest3_Init,
    (ActorFunc)EnTest3_Destroy,
    (ActorFunc)EnTest3_Update,
    (ActorFunc)NULL,
};

// char bss[0x50];

s32 func_80A3E7E0(EnTest3* this, EnTest3ActionFunc actionFunc) {
    if (actionFunc == this->actionFunc) {
        return false;
    }

    this->actionFunc = actionFunc;
    this->unk_D8A = 0;
    this->schedule = 0;
    return true;
}

typedef struct {
    EnTest3ActionFunc actionInitFunc;
    EnTest3ActionFunc actionFunc;
} KafeiActionSetupInfo;

s32 func_80A3E80C(EnTest3* this, GlobalContext* globalCtx, s32 actionIndex) {
    static KafeiActionSetupInfo actionSetupInfoList[] = {
        { func_80A40A6C, NULL },
        { NULL, NULL },
    };
    KafeiActionSetupInfo* actionSetup = &actionSetupInfoList[actionIndex];

    actionSetup->actionInitFunc(this, globalCtx);

    if (actionSetup->actionFunc == NULL) {
        return false;
    }

    func_80A3E7E0(this, actionSetup->actionFunc);

    return true;
}

// function pointers!
u32 D_80A4169C[] = {
    0x80A3E898, 0x80A3E898, 0x80A3E884, 0x80A3E898, 0x80A3E898, 0x80A3EA30, 0x80A3E898, 0x80A3E960, 0x80A3E870,
};

// function pointers!
u32 D_80A416C0[] = {
    0x80A3EAC4, 0x80A3EAF8, 0x80A3EBFC, 0x80A3EC44, 0x80A3EC30, 0x80A3E9DC, 0x80A3EB8C, 0x80A3E97C,
};

u32 D_80A416E0[] = {
    0x42200000, 0x42700000, 0x3F25A5A6, 0x428E0000, 0x42480000, 0x42440000, 0x421C0000, 0x41D80000,
    0x41980000, 0x41B00000, 0x4201999A, 0x42000000, 0x42400000, 0x42352D2E, 0x41600000, 0x41400000,
    0x425C0000, 0xFFE80DED, 0x036CFFE8, 0x0D92035E, 0xFFE81371, 0x03A90008, 0x1256017C, 0x000917EA,
    0x0167FFE8, 0x137103A9, 0xFFE8195F, 0x03A90009, 0x17EA0167, 0x00091E0D, 0x017C0008, 0x1256017C,
    0x000917EA, 0x0167F9C8, 0x1256017C, 0xF9C917EA, 0x01670020, 0x00000000, 0x41B00000, 0x41EB7972,
    0x0400D128, 0x0400D170, 0x0400D1B8, 0x0400D1F8, 0x0400D200, 0x0400D208, 0x0400D210, 0x0400DAB0,
    0x0400DAB8, 0x0400DA90, 0x0400DA98, 0x0400D1D8, 0x0400D1E0, 0x0400D1F0, 0x0400D1E8,
};

u32 D_80A417BC[] = {
    0x00000000, 0x00080000, 0xFFFFFFFF, 0xFFFFFF40, 0xFFFFFF00, 0xFFFFFF00, 0x04000200, 0x00000000, 0x00000000,
};

u32 D_80A417E0[] = {
    0x0000003F,
    0x00000F64,
};

// function pointers!
u32 D_80A417E8[] = {
    0x80A3F080, 0x80A3F09C, 0x80A40098, 0x80A40230, 0x80A3F62C, 0x80A3F73C, 0x80A3F8D4, 0x80A3F9A4,
    0x80A3F9E4, 0x80A3FA58, 0x80A3FBCC, 0x80A3FBE8, 0x80A3FDE4, 0x80A3FE20, 0x80A3FF10, 0x80A3FFD0,
};

u32 D_80A41828[] = {
    0x000003E0, 0x02F002F1, 0x02F20213, 0x02E40510, 0x07F00620, 0x04400110,
    0x01100120, 0x01100110, 0x01200130, 0x01100120, 0x01100000,
};

u32 D_80A41854[] = {
    0x04002B25,
};

u32 D_80A41858[] = {
    0x01002969, 0x0301296A, 0x0100296B, 0x05010000, 0x08000000,
};

u32 D_80A4186C[] = {
    0x04002976,
};

u32 D_80A41870[] = {
    0x06002977,
    0x070A2978,
    0x04010000,
};

u32 D_80A4187C[] = {
    0x04002968,
};

u32 D_80A41880[] = {
    0x0400297A,
};

u32 D_80A41884[] = {
    0x0100145D, 0x0100145E, 0x0501145F, 0x0100145F, 0x05000000,
};

u32 D_80A41898[] = {
    0x04001460,
};

u32 D_80A4189C[] = {
    0x0400145C,
};

u32 D_80A418A0[] = {
    0x04002913,
};

u32 D_80A418A4[] = {
    0x04001465,
};

s32 func_80A3E870(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3E870.asm")

s32 func_80A3E884(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3E884.asm")

s32 func_80A3E898(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3E898.asm")

s32 func_80A3E960(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3E960.asm")

s32 func_80A3E97C(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3E97C.asm")

s32 func_80A3E9DC(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3E9DC.asm")

s32 func_80A3EA30(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EA30.asm")

s32 func_80A3EAC4(EnTest3* this, GlobalContext* game_play);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EAC4.asm")

s32 func_80A3EAF8(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EAF8.asm")

s32 func_80A3EB8C(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EB8C.asm")

s32 func_80A3EBFC(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EBFC.asm")

s32 func_80A3EC30(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EC30.asm")

s32 func_80A3EC44(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EC44.asm")

s32 func_80A3ECEC(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3ECEC.asm")

s32 func_80A3ED24(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3ED24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/EnTest3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/EnTest3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F09C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F0B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F2BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F534.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F5A4.asm")

/* static */ void* D_80A418A8[] = {
    D_80A41854, D_80A41858, D_80A41880, D_80A41884, D_80A418A0,
};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F8D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F9A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FA58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FBCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FBE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FDE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FE20.asm")

/* static */ Vec3f D_80A418BC[] = { -420.0f, 210.0f, -162.0f };

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FF10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FFD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40824.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A4084C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A409D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/EnTest3_Update.asm")

/* static */ u32 D_80A418C8 = 0;

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40CF0.asm")

/* static */ Vec3f D_80A418CC[] = { 1100.0f, -700.0f, 0.0f };

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40F34.asm")

/* static */ void* eyeTextures[] = {
    0x06000DC0, 0x06003680, 0x06003E80, 0x06004680, 0x06004E80, 0x06005680, 0x06005E80, 0x06006680,
};

/* static */ void* mouthTextures[] = {
    0x060009C0,
    0x06006E80,
    0x06007280,
    0x06007680,
};

/* static */ FaceAnimKeyFrame faceAnimInfo[] = {
    { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 4, 0 }, { 5, 1 }, { 7, 2 }, { 0, 2 },
    { 3, 0 }, { 4, 0 }, { 2, 2 }, { 1, 1 }, { 0, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A4129C.asm")
