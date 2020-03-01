#include <ultra64.h>
#include <global.h>

void BcCheck3_BgActorInit(BgActor* actor, UNK_TYPE4 param_2) {
    actor->bgActorId = -1;
    actor->unk148 = 0;
    actor->unk14C = 0;
    actor->unk154 = param_2;
    actor->bgFlags = 0;
}

void BgCheck3_LoadMesh(GlobalContext* ctxt, BgActor* actor, BgMeshHeader* meshHeader) {
    BgMeshHeader* header;

    header = NULL;
    BgCheck_RelocateMeshHeader(meshHeader, &header);
    actor->bgActorId = BgCheck_AddActorMesh(ctxt, &ctxt->bgCheckContext.dyna, actor, header);
}

void BgCheck3_ResetFlags(BgActor* actor) {
    actor->bgFlags = 0;
}

void func_800CAE88(BgActor* actor) {
    actor->bgFlags |= 1;
}

void func_800CAE9C(BgActor* actor) {
    actor->bgFlags |= 2;
}

void func_800CAEB0(BgCheckContext* bgCtxt, s32 index) {
    BgActor* actor;

    actor = BgCheck_GetActorOfMesh(bgCtxt, index);
    if (actor != (BgActor *)0x0) {
        func_800CAE9C(actor);
    }
}

void func_800CAEE0(BgActor* actor) {
    actor->bgFlags |= 4;
}

void func_800CAEF4(BgCheckContext* bgCtxt, s32 index) {
    BgActor* actor;

    actor = BgCheck_GetActorOfMesh(bgCtxt, index);
    if (actor != (BgActor *)0x0) {
        func_800CAEE0(actor);
    }
}

void func_800CAF24(BgActor* actor) {
    actor->bgFlags |= 8;
}

void func_800CAF38(BgActor* actor) {
    actor->bgFlags |= 0x10;
}

s32 func_800CAF4C(BgActor* actor) {
    if (actor->bgFlags & 1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAF70(BgActor* actor) {
    if (actor->bgFlags & 2) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAF94(BgActor* actor) {
    if (actor->bgFlags & 4) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAFB8(BgActor* actor) {
    if (actor->bgFlags & 8) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800CAFDC(BgActor* actor) {
    if (actor->bgFlags & 0x10) {
        return 1;
    } else {
        return 0;
    }
}
