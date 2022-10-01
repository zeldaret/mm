#include "z_en_invadepoh.h"
// #include "assets/objects/gameplay_keep/gameplay_keep.h"
// #include "assets/objects/object_uch/object_uch.h"
// #include "assets/objects/object_ma1/object_ma1.h"
// #include "assets/objects/object_ma2/object_ma2.h"
// #include "assets/objects/object_cow/object_cow.h"
// #include "assets/objects/object_dog/object_dog.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepoh*)thisx)

typedef struct {
    f32 unk0;
    s16 unk4;
    s16 unk6;
} EnInvadepohUnkStruct1;

typedef struct {
    u8* unk0;
    u8 unk4;
} EnInvadepohUnkStruct2;

typedef struct {
    s32 unk0;
    EnInvadepohUnkStruct2* unk4;
} EnInvadepohUnkStruct3;

typedef struct {
    u8 unk0;
    f32 unk4;
} EnInvadepohUnkStruct4;

typedef struct {
    u8 unk0;
    EnInvadepohUnkStruct2* unk4;
    u8 unk8;
    EnInvadepohUnkStruct4* unkC;
} EnInvadepohUnkStruct5;

typedef struct {
    u8 unk0;
    EnInvadepohUnkStruct2* unk4;
    u8 unk8;
    EnInvadepohUnkStruct4* unkC;
    s16 unk10;
    s16 unk12;
} EnInvadepohUnkStruct6;

void EnInvadepoh_Init(Actor* thisx, PlayState* play);
void EnInvadepoh_Destroy(Actor* thisx, PlayState* play);
void EnInvadepoh_Update(Actor* thisx, PlayState* play);

void func_80B4D9B4(Actor* thisx, PlayState* play);

void func_80B4627C(EnInvadepoh* this, PlayState* play);
void func_80B46414(EnInvadepoh* this, PlayState* play);
void func_80B46520(EnInvadepoh* this, PlayState* play);
void func_80B465CC(EnInvadepoh* this, PlayState* play);
void func_80B46644(EnInvadepoh* this, PlayState* play);
void func_80B46644(EnInvadepoh* this, PlayState* play);
void func_80B468B4(EnInvadepoh* this, PlayState* play);
void func_80B46644(EnInvadepoh* this, PlayState* play);
void func_80B46644(EnInvadepoh* this, PlayState* play);
void func_80B46644(EnInvadepoh* this, PlayState* play);
void func_80B469C4(EnInvadepoh* this, PlayState* play);
void func_80B46A80(EnInvadepoh* this, PlayState* play);
void func_80B46644(EnInvadepoh* this, PlayState* play);
void func_80B46414(EnInvadepoh* this, PlayState* play);

void func_80B46BB0(EnInvadepoh* this, PlayState* play);
void func_80B46BC0(EnInvadepoh* this, PlayState* play);
void func_80B46C08(EnInvadepoh* this, PlayState* play);
void func_80B46C34(EnInvadepoh* this, PlayState* play);
void func_80B46C50(EnInvadepoh* this, PlayState* play);
void func_80B46C50(EnInvadepoh* this, PlayState* play);
void func_80B46C7C(EnInvadepoh* this, PlayState* play);
void func_80B46C50(EnInvadepoh* this, PlayState* play);
void func_80B46C50(EnInvadepoh* this, PlayState* play);
void func_80B46C50(EnInvadepoh* this, PlayState* play);
void func_80B46C94(EnInvadepoh* this, PlayState* play);
void func_80B46CC0(EnInvadepoh* this, PlayState* play);
void func_80B46CF4(EnInvadepoh* this, PlayState* play);
void func_80B46D28(EnInvadepoh* this, PlayState* play);

extern ColliderCylinderInit D_80B4E8B0;
extern ColliderCylinderInit D_80B4E8DC;
extern ColliderCylinderInit D_80B4E908;
extern Vec3f D_80B4E934;
extern s32 D_80B4E940;
extern TexturePtr sRomaniEyeTextures[];
extern TexturePtr sRomaniMouthTextures[];
extern s32 D_80B4E968;
extern TexturePtr sCremiaEyeTextures[];
extern TexturePtr sCremiaMouthTextures[];
extern s32 D_80B4E994;
extern s32 D_80B4E998;
extern u8 D_80B4E99C[];
extern u8 D_80B4E9A0[];
extern u8 D_80B4E9A4[];
extern u8 D_80B4E9AC[];
extern u8 D_80B4E9B4[];
extern u8 D_80B4E9BC[];
extern u8 D_80B4E9C0[];
extern u8 D_80B4EAB0[];
extern EnInvadepohUnkStruct2 D_80B4E9C4[];
extern EnInvadepohUnkStruct2 D_80B4E9CC[];
extern EnInvadepohUnkStruct2 D_80B4E9D4[];
extern EnInvadepohUnkStruct2 D_80B4E9DC[];
extern EnInvadepohUnkStruct2 D_80B4E9E4[];
extern EnInvadepohUnkStruct2 D_80B4E9EC[];
extern EnInvadepohUnkStruct2 D_80B4E9F4[];
extern EnInvadepohUnkStruct3 D_80B4E9FC;
extern EnInvadepohUnkStruct4 D_80B4EA04[];
extern EnInvadepohUnkStruct4 D_80B4EA24;
extern EnInvadepohUnkStruct6 D_80B4EA2C;
extern EnInvadepohUnkStruct5 D_80B4EA40;
extern EnInvadepohUnkStruct5 D_80B4EA50;
extern EnInvadepohUnkStruct5 D_80B4EA60;
extern EnInvadepohUnkStruct5 D_80B4EA70;
extern EnInvadepohUnkStruct3 D_80B4EA80;
extern EnInvadepohUnkStruct3 D_80B4EA88;
extern void* D_80B4EA90[];
extern u8 D_80B4EAB0[];
extern u8 D_80B4EAB4[];
extern u8 D_80B4EAB8[];
extern u8 D_80B4EABC[];
extern EnInvadepohUnkStruct2 D_80B4EAC0;
extern EnInvadepohUnkStruct2 D_80B4EAC8;
extern EnInvadepohUnkStruct2 D_80B4EAD0;
extern EnInvadepohUnkStruct2 D_80B4EAD8;
extern EnInvadepohUnkStruct3 D_80B4EAE0;
extern EnInvadepohUnkStruct3 D_80B4EAE8;
extern EnInvadepohUnkStruct3 D_80B4EAF0;
extern EnInvadepohUnkStruct3 D_80B4EAF8;
extern EnInvadepohUnkStruct3* D_80B4EB00[];
extern u8 D_80B4EB10[];
extern u8 D_80B4EB14[];
extern u8 D_80B4EB18[];
extern u8 D_80B4EB20[];
extern u8 D_80B4EB28[];
extern EnInvadepohUnkStruct2 D_80B4EB30;
extern EnInvadepohUnkStruct2 D_80B4EB38;
extern EnInvadepohUnkStruct2 D_80B4EB40;
extern EnInvadepohUnkStruct2 D_80B4EB48;
extern EnInvadepohUnkStruct2 D_80B4EB50;
extern EnInvadepohUnkStruct2 D_80B4EB58;
extern EnInvadepohUnkStruct3 D_80B4EB58;
extern EnInvadepohUnkStruct4 D_80B4EB60[];
extern EnInvadepohUnkStruct4 D_80B4EB80;
extern EnInvadepohUnkStruct6 D_80B4EB88;
extern EnInvadepohUnkStruct5 D_80B4EB9C;
extern EnInvadepohUnkStruct5 D_80B4EBAC;
extern EnInvadepohUnkStruct5 D_80B4EBBC;
extern EnInvadepohUnkStruct5 D_80B4EBCC;
extern void* D_80B4EBDC[];
extern u8 D_80B4EBF4[];
extern EnInvadepohUnkStruct2 D_80B4EBF8;
extern EnInvadepohUnkStruct3 D_80B4EC00;
extern EnInvadepohUnkStruct3* D_80B4EC08;
extern void* D_80B4EC0C[];
extern Color_RGBA8 D_80B4EC18;
extern Color_RGBA8 D_80B4EC1C;
extern void* D_80B4EC20;
extern InitChainEntry D_80B4EC24[];
extern InitChainEntry D_80B4EC34[];
extern InitChainEntry D_80B4EC44[];
extern InitChainEntry D_80B4EC54[];
extern InitChainEntry D_80B4EC68[];
extern InitChainEntry D_80B4EC80[];
extern InitChainEntry D_80B4EC98[];
extern EnInvadepohInitFunc* D_80B4ECB0[];
extern EnInvadepohDestFunc* D_80B4ECE8[];
extern s16 D_80B4ED20[];
extern Vec3f D_80B4ED30[];
extern Vec3f D_80B4ED6C[];
extern Vec3s D_80B4EDC0;
extern Vec3s D_80B4EDC8;
extern Vec3f D_80B4EDD0[];
extern EnInvadepohUnkStruct1 D_80B4EE0C[];
extern Vec3f D_80B4EE24;
extern Vec3f D_80B4EE30;

extern MtxF D_80B502A0;
extern MtxF D_80B502E0;
extern Actor *D_80B50320;
extern s32 D_80B50324;
extern s32 D_80B50328;
extern s32 D_80B5032C;
extern u8 D_80B50340;
extern s8 D_80B50348;
extern s32 D_80B50350[];
extern Actor *D_80B503F0;
extern EnInvadepoh *D_80B503F4;
extern EnInvadepoh *D_80B503F8;
extern AnimatedMaterial *sAlienEmptyTexAnim;
extern AnimatedMaterial *sAlienEyeBeamTexAnim;
extern s16 D_80B50404;
extern s16 D_80B50406;
extern s16 D_80B5040A;
extern Actor *D_80B5040C;


/*
const ActorInit En_Invadepoh_InitVars = {
    ACTOR_EN_INVADEPOH,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepoh),
    (ActorFunc)EnInvadepoh_Init,
    (ActorFunc)EnInvadepoh_Destroy,
    (ActorFunc)EnInvadepoh_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B439B0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43A24.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43A74.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43A9C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43AB0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43AF0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43B80.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43BC8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43DD4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43E6C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43F0C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B43F70.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44024.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4407C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B440B8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44234.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B442E4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B443A0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B444BC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B444F4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44514.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44540.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44570.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44620.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44640.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44664.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44690.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B446D0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44700.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B447C0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44A90.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44B78.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44B84.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44C24.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44C80.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44E90.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44EFC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44F58.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B44FEC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45080.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B450C0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4516C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B451A0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B452EC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B453F4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45460.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B454BC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45518.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45550.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4560C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45648.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B456A8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B457A0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B458D8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45980.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B459E8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45A4C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45A94.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45B1C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45BB8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45C04.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45CE0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B45EC8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46118.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46184.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B461DC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4627C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46414.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46520.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B465CC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46644.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B468B4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B469C4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46A80.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/EnInvadepoh_Init.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46BB0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46BC0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C08.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C34.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C50.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C7C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46C94.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46CC0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46CF4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46D28.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/EnInvadepoh_Destroy.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46DA8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46DC8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46E20.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46E44.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46EC0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46EE8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46F88.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B46FA8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47064.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47084.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B470E0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47108.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B471C0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B471E0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47248.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47268.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47278.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47298.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47304.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47324.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/EnInvadepoh_Update.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47380.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B473E4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47478.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B474DC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47568.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47600.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4770C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B477B4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47830.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B478F4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47938.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B479E8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47BAC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47D30.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B47FA8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48060.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B481C4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4827C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B482D4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48324.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48374.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B483CC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4843C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B484EC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48588.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48610.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48620.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4873C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B487B4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48848.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48948.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48AD4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48DE4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48E4C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B48FB0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B490F0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B491EC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49228.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B492FC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4934C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49404.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49454.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49628.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49670.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B497A4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B497EC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49904.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4994C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B499BC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49A00.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49B1C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49BD0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49C38.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49DA0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49DFC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B49F88.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A168.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A1B8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A2C0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A350.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A570.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A5E4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A614.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A67C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A7C0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A81C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4A9C8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AB8C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ABDC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ACDC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ACF0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AD3C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AD60.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ADB8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4ADCC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AEC0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AEDC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AF80.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4AF94.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B024.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B048.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B0C4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B218.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B3DC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B430.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B484.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B510.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B564.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B724.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B768.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B820.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B864.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4B8BC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BA30.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BA84.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BBE0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BC4C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4BFFC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C058.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C1BC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C218.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C3A0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C568.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C5C0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C6C8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4C730.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CAB0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CB0C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CC70.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CCCC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CE54.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4CFFC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D054.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D15C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D290.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D3E4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D480.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D670.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D760.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D7B8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D9B4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D9D8.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4D9F4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4DB14.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E120.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E158.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E1B0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E200.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E2AC.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E324.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E3F0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E5B0.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E61C.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E660.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E6E4.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E784.s")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh/func_80B4E7BC.s")