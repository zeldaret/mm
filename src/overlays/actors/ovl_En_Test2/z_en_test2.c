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

void func_80A3E4EC(Actor* actor, PlayState* play);
void func_80A3E524(Actor* thisx, PlayState* play);

#if 0
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A3E74C[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 8000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2500, ICHAIN_STOP),
};
s32 D_80A3E6B0 = 0x06000040;
static s16 D_80A3E75C[0x12] = {
    0x180,
    0x17F,
    0x76,
    0x190,
    0x190,
    0x190,
    0x1BC,
    0x1E0,
    0x1E0,
    0x190,
    0x190,
    0x190,
    0x190,
    0,
    0,
    0,
    0,
    0,
};

#endif

extern InitChainEntry D_80A3E74C[];
extern u32 D_80A3E6B0[][3];
extern s16 D_80A3E75C[];
extern s32 D_80A3E6B4[][3];

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
    u32* temp_v0_2;
    EnTest2* this = (EnTest2*)thisx;
    objectIndex = Object_GetIndex(&play->objectCtx, D_80A3E75C[this->actor.params]);

    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (Object_IsLoaded(&play->objectCtx, objectIndex) != 0) {
        temp_v0_2 = D_80A3E6B0[this->actor.params];
        this->actor.objBankIndex = objectIndex;
        this->actor.draw = func_80A3E524;
        if ((temp_v0_2[2]) != 0) {
            Actor_SetObjectDependency(play, &this->actor);
            this->unk144 = Lib_SegmentedToVirtual(temp_v0_2[2]);
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
    Gfx* temp_a3 = D_80A3E6B0[this->actor.params][1];

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
        gSPDisplayList(POLY_XLU_DISP++, D_80A3E6B0[this->actor.params][0]);
        CLOSE_DISPS(play->state.gfxCtx);
        return;
    }
    if (temp_a3 != 0) {
        Gfx_DrawDListXlu(play, temp_a3);
    }
    Gfx_DrawDListOpa(play, D_80A3E6B0[this->actor.params][0]);
}