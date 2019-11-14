#include <ultra64.h>
#include <global.h>

// TODO this file looks like an actor, it should be cleaned up as such

// This file is most likely En_A_Obj

UNK_RET EnAObj_Init(void* a0, UNK_TYPE a1) {
    z_ActorEnAObj* s0 = (z_ActorEnAObj*)a0;
    s0->base.textId = ((s0->base.variable >> 8) & 0xFF) | 0x300;
    s0->base.variable = (s0->base.variable & 0xFF) - 9;
    Lib_ApplyActorInitVars((z_Actor*)s0, (z_ActorInitVar*)&D_801ADEAC);
    func_800B3BA4(&s0->base.unkBC, 0, (UNK_PTR)&func_800B3FC0, 12);
    Collision_InitCylinder(a1, &s0->collision, (z_Actor*)s0, &D_801ADE80);
    Collision_CylinderMoveToActor((z_Actor*)s0, &s0->collision);
    s0->base.unkA0.unk16 = 255;
    s0->update = (actor_func)EnAObj_Update1;
}

UNK_RET EnAObj_Fini(z_ActorEnAObj* a0, z_GlobalContext* a1) {
    z_ColCylinder* a2 = &a0->collision;
    Collision_FiniCylinder(a1, a2);
}

UNK_RET EnAObj_Update1(z_ActorEnAObj* a0, UNK_TYPE a1) {
    s16 v0;
    s32 v1;
    if (func_800B84D0(a0, a1) != 0) {
        a0->update = (actor_func)EnAObj_Update2;
    } else {
        v0 = a0->base.unk92 - a0->base.unkBC.rotation.y;
        v1 = (v0 < 0)? -v0 : v0;
        if ((v1 < 10240) || ((a0->base.variable == 1) && (v1 > 22528))) {
            func_800B863C(a0, a1);
        }
    }
}

UNK_RET EnAObj_Update2(z_ActorEnAObj* a0) {
    if (func_800B867C(a0) != 0) {
        a0->update = (actor_func)EnAObj_Update1;
    }
}

UNK_RET EnAObj_Main(z_ActorEnAObj* a0, UNK_TYPE a1) {
    (a0->update)((z_Actor*)a0, (z_GlobalContext*)a1);
    func_800B675C(a0, 0x42340000);
    Collision_AddOT(a1, a1 + 0x18884, &a0->collision);
}

UNK_RET EnAObj_Draw(z_ActorEnAObj* a0, UNK_TYPE a1) {
    func_800BDFC0(a1, D_801ADEB0[a0->base.variable], a1, a0);
}
