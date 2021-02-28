#include "z_door_spiral.h"

#define FLAGS 0x00000010

#define THIS ((DoorSpiral*)thisx)

void DoorSpiral_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809A2DB0(DoorSpiral* this, GlobalContext* globalCtx);

const ActorInit Door_Spiral_InitVars = {
    ACTOR_DOOR_SPIRAL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorSpiral),
    (ActorFunc)DoorSpiral_Init,
    (ActorFunc)DoorSpiral_Destroy,
    (ActorFunc)DoorSpiral_Update,
    (ActorFunc)DoorSpiral_Draw,
};

typedef struct {
    /* 0x00 */ Gfx* doorDList[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
} SpiralStruct_809A3250;

SpiralStruct_809A3250 D_809A3250[] = {
    { { NULL, NULL }, 0, 130, 12, 50, 15 },
    { { 0x050219E0, 0x0501D980 }, 0, 130, 12, 50, 15 },
    { { 0x06004448, 0x060007A8 }, 0, 130, 12, 50, 15 },
    { { 0x060051B8, 0x060014C8 }, 0, 130, 12, 50, 15 },
    { { 0x06009278, 0x06006128 }, 0, 130, 12, 50, 15 },
    { { 0x06013EA8, 0x06012B70 }, 0, 130, 12, 50, 15 },
    { { 0x06000EA0, 0x06000590 }, 0, 130, 12, 50, 15 },
    { { 0x06002110, 0x060012C0 }, 0, 130, 12, 50, 15 },
};

typedef struct {
    /* 0x00 */ s16 objectBankId;
    /* 0x02 */ u8 modelNum;
} SpiralStruct_809A32D0;

SpiralStruct_809A32D0 D_809A32D0[] = {
    { GAMEPLAY_KEEP, 0 },    { GAMEPLAY_DANGEON_KEEP, 1 }, { OBJECT_NUMA_OBJ, 2 },      { OBJECT_HAKUGIN_OBJ, 4 },
    { OBJECT_IKANA_OBJ, 5 }, { OBJECT_DANPEI_OBJECT, 7 },  { OBJECT_IKNINSIDE_OBJ, 6 },
};

typedef struct {
    /* 0x00 */ s16 sceneNum;
    /* 0x02 */ u8 doorType;
} SpiralStruct_809A32EC;

SpiralStruct_809A32EC D_809A32EC[] = {
    { SCENE_MITURIN, 2 },     { SCENE_HAKUGIN, 3 },   { SCENE_INISIE_N, 4 }, { SCENE_INISIE_R, 4 },
    { SCENE_DANPEI2TEST, 5 }, { SCENE_IKNINSIDE, 6 }, { SCENE_CASTLE, 6 },
};

u32 D_809A3308[] = {
    0xC0580001, 0xB0FC0FA0, 0xB1000190, 0x31040190, 0x00000000, 0x00000000,
};

void func_809A2B60(DoorSpiral* this, DoorSpiralActionFunc* actionFunc);

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2B60.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2B70.asm")

s32 func_809A2BF8(GlobalContext* globalCtx);

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2BF8.asm")

void DoorSpiral_Init(Actor* thisx, GlobalContext* globalCtx) {
    DoorSpiral* this = THIS;
    s32 pad;
    s32 transition = (u16)thisx->params >> 10;
    s8 objBankId;

    if (thisx->room != globalCtx->transitionActorList[transition].sides[0].room) {
        Actor_MarkForDeath(thisx);
        return;
    }

    Actor_ProcessInitChain(thisx, &D_809A3308);
    this->unk145 = (thisx->params >> 8) & 3;
    this->unk146 = (thisx->params >> 7) & 1;
    this->unk147 = func_809A2BF8(globalCtx);
    objBankId = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, D_809A32D0[this->unk147].objectBankId);
    this->unk149 = objBankId;

    if (objBankId < 0) {
        Actor_MarkForDeath(thisx);
        return;
    }

    func_809A2B60(this, func_809A2DB0);
    Actor_SetHeight(thisx, 60.0f);
}

void DoorSpiral_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    s32 transition = (u16)thisx->params >> 10;
    
    globalCtx->transitionActorList[transition].id *= -1;
}

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2DB0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2E08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2EA0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2FF8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A3098.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Update.asm")

void DoorSpiral_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DoorSpiral* this = THIS;

    if (this->actor.objBankIndex == this->unk149) {
        SpiralStruct_809A3250* modelInfo = &D_809A3250[this->unk148];
        Gfx* dList;

        dList = modelInfo->doorDList[this->unk146];

        if (dList != NULL) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            func_8012C28C(globalCtx->state.gfxCtx);

            gSPMatrix(POLY_OPA_DISP++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, modelInfo->doorDList[this->unk146]);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
