/*
 * File: z_en_test2.c
 * Overlay: ovl_En_Test2
 * Description: Objects affected by the Lens of Truth
 */

#include "z_en_test2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80)

#define THIS ((EnTest2*)thisx)

void EnTest2_Init(Actor* thisx, PlayState* play);
void EnTest2_Update(Actor* thisx, PlayState* play);

void func_80A3E4EC(Actor* thisx, PlayState* play);
void func_80A3E524(Actor* thisx, PlayState* play);

typedef struct UnkStruct {
    Gfx* unk0;
    Gfx* unk4;
    AnimatedMaterial* unk8;
} UnkStruct;

#if 1
const ActorInit En_Test2_InitVars = {
    ACTOR_EN_TEST2,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest2),
    (ActorFunc)EnTest2_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)EnTest2_Update,
    (ActorFunc)NULL,
};

// UnkStruct* D_80A3E6B0 = 0x06000040;
UnkStruct D_80A3E6B0[] = {
    { (Gfx*)0x06000040, NULL, NULL },
    { (Gfx*)0x06001820, NULL, NULL },
    { (Gfx*)0x060008C0, NULL, NULL },
    { (Gfx*)0x060016D8, NULL, (AnimatedMaterial*)0x060017A8 },
    { (Gfx*)0x06002018, NULL, (AnimatedMaterial*)0x060020E8 },
    { (Gfx*)0x06005268, NULL, (AnimatedMaterial*)0x06005338 },
    { (Gfx*)0x06000110, (Gfx*)0x06000080, NULL },
    { (Gfx*)0x06000F70, NULL, NULL },
    { (Gfx*)0x06001200, NULL, NULL },
    { (Gfx*)0x06004928, NULL, (AnimatedMaterial*)0x060049F8 },
    { (Gfx*)0x06002978, NULL, (AnimatedMaterial*)0x06002A58 },
    { (Gfx*)0x06000D38, NULL, (AnimatedMaterial*)0x06000E48 },
    { (Gfx*)0x060035A8, NULL, (AnimatedMaterial*)0x06003888 },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A3E74C[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 8000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2500, ICHAIN_STOP),
};

static s16 D_80A3E75C[] = {
    OBJECT_DEKUCITY_ANA_OBJ, OBJECT_SICHITAI_OBJ,  OBJECT_YUKIMURA_OBJ, OBJECT_HAKUGIN_OBJ, OBJECT_HAKUGIN_OBJ,
    OBJECT_HAKUGIN_OBJ,      OBJECT_MEGANEANA_OBJ, OBJECT_HAKA_OBJ,     OBJECT_HAKA_OBJ,    OBJECT_HAKUGIN_OBJ,
    OBJECT_HAKUGIN_OBJ,      OBJECT_HAKUGIN_OBJ,   OBJECT_HAKUGIN_OBJ,
};

#endif

 //extern InitChainEntry D_80A3E74C[];
 //extern UnkStruct D_80A3E6B0[][];
 //extern s16 D_80A3E75C[];
 //extern s32 D_80A3E6B4[][];

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/EnTest2_Init.s")

void EnTest2_Init(Actor* thisx, PlayState* play) {
    EnTest2* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80A3E74C);
    if ((this->actor.params == 0xB) || (this->actor.params == 0xC)) {
        this->actor.flags |= 0x20;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/EnTest2_Update.s")

void EnTest2_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    s32 objectIndex;
    UnkStruct* temp_v0_2;
    EnTest2* this = THIS;
    objectIndex = Object_GetIndex(&play->objectCtx, D_80A3E75C[this->actor.params]);

    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (Object_IsLoaded(&play->objectCtx, objectIndex) != 0) {
        temp_v0_2 = &D_80A3E6B0[this->actor.params].unk0;
        this->actor.objBankIndex = objectIndex;
        this->actor.draw = func_80A3E524;
        if ((temp_v0_2->unk8) != 0) {
            Actor_SetObjectDependency(play, &this->actor);
            this->unk144 = Lib_SegmentedToVirtual(temp_v0_2->unk8);
        }
        if (play->roomCtx.currRoom.unk5 != 0) {
            this->actor.update = func_80A3E4EC;
            return;
        }
        this->actor.update = Actor_Noop;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/func_80A3E4EC.s")

void func_80A3E4EC(Actor* thisx, PlayState* play) {
    if (play->actorCtx.unk4 == 0x64) {
        thisx->flags |= 0x80;
        return;
    }
    thisx->flags &= -0x81;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/func_80A3E524.s")

void func_80A3E524(Actor* thisx, PlayState* play) {
    s32 pad;
    EnTest2* this = (EnTest2*)thisx;
    UnkStruct* temp_a3 = D_80A3E6B0[this->actor.params].unk0;

    if (this->unk144 != NULL) {
        AnimatedMat_Draw(play, this->unk144);
    }
    if ((this->actor.flags & 0x80) == 0x80) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (temp_a3 != 0) {
            gSPDisplayList(POLY_XLU_DISP++, temp_a3);
        }
        gSPDisplayList(POLY_XLU_DISP++, D_80A3E6B0[this->actor.params].unk0);
        CLOSE_DISPS(play->state.gfxCtx);
        return;
    }
    if (temp_a3 != 0) {
        Gfx_DrawDListXlu(play, temp_a3);
    }
    Gfx_DrawDListOpa(play, D_80A3E6B0[this->actor.params].unk0);
}