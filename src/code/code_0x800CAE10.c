#include <ultra64.h>
#include <global.h>

void BcCheck3_BgActorInit(DynaPolyActor* actor, UNK_TYPE4 param_2) {
    actor->bgId = -1;
    actor->unk148 = 0;
    actor->unk14C = 0;
    actor->unk154 = param_2;
    actor->unk_158 = 0;
}

void BgCheck3_LoadMesh(GlobalContext* globalCtx, DynaPolyActor* actor, CollisionHeader* meshHeader) {
    CollisionHeader* header;

    header = NULL;
    BgCheck_RelocateMeshHeader(meshHeader, &header);
    actor->bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, actor, header);
}

void BgCheck3_ResetFlags(DynaPolyActor* actor) {
    actor->unk_158 = 0;
}

void func_800CAE88(DynaPolyActor* actor) {
    actor->unk_158 |= 1;
}

void func_800CAE9C(DynaPolyActor* actor) {
    actor->unk_158 |= 2;
}

void func_800CAEB0(CollisionContext* colCtx, s32 index) {
    DynaPolyActor* actor;

    actor = BgCheck_GetActorOfMesh(colCtx, index);
    if (actor != (DynaPolyActor*)0x0) {
        func_800CAE9C(actor);
    }
}

void func_800CAEE0(DynaPolyActor* actor) {
    actor->unk_158 |= 4;
}

void func_800CAEF4(CollisionContext* colCtx, s32 index) {
    DynaPolyActor* actor;

    actor = BgCheck_GetActorOfMesh(colCtx, index);
    if (actor != (DynaPolyActor*)0x0) {
        func_800CAEE0(actor);
    }
}

void func_800CAF24(DynaPolyActor* actor) {
    actor->unk_158 |= 8;
}

void func_800CAF38(DynaPolyActor* actor) {
    actor->unk_158 |= 0x10;
}

s32 func_800CAF4C(DynaPolyActor* actor) {
    if (actor->unk_158 & 1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAF70(DynaPolyActor* actor) {
    if (actor->unk_158 & 2) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAF94(DynaPolyActor* actor) {
    if (actor->unk_158 & 4) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAFB8(DynaPolyActor* actor) {
    if (actor->unk_158 & 8) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAFDC(DynaPolyActor* actor) {
    if (actor->unk_158 & 0x10) {
        return 1;
    } else {
        return 0;
    }
}
