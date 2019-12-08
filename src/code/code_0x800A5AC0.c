#include <ultra64.h>
#include <global.h>

// TODO this file looks like an actor, it should be cleaned up as such

// This file is most likely En_A_Obj

UNK_RET EnAObj_Init(ActorEnAObj* a0, GlobalContext* a1) {
    ActorEnAObj* s0 = (ActorEnAObj*)a0;
    s0->base.textId = ((s0->base.variable >> 8) & 0xFF) | 0x300;
    s0->base.variable = (s0->base.variable & 0xFF) - 9;
    Lib_ApplyActorInitVars((Actor*)s0, (ActorInitVar*)&enAObjInitVar);
    func_800B3BA4(&s0->base.unkBC, 0, (UNK_PTR)&func_800B3FC0, 12);
    Collision_InitCylinder(a1, &s0->collision, (Actor*)s0, &enAObjCylinderInit);
    Collision_CylinderMoveToActor((Actor*)s0, &s0->collision);
    s0->base.unkA0.unk16 = 255;
    s0->update = (actor_func)EnAObj_Update1;
}

UNK_RET EnAObj_Fini(ActorEnAObj* a0, GlobalContext* a1) {
    ColCylinder* a2 = &a0->collision;
    Collision_FiniCylinder(a1, a2);
}

UNK_RET EnAObj_Update1(ActorEnAObj* a0, GlobalContext* a1) {
    s16 v0;
    s32 v1;
    if (func_800B84D0((Actor*)a0, a1) != 0) {
        a0->update = (actor_func)EnAObj_Update2;
    } else {
        v0 = a0->base.unk92 - a0->base.unkBC.rotation.y;
        v1 = (v0 < 0)? -v0 : v0;
        if ((v1 < 10240) || ((a0->base.variable == 1) && (v1 > 22528))) {
            func_800B863C((Actor*)a0, a1);
        }
    }
}

UNK_RET EnAObj_Update2(ActorEnAObj* a0, GlobalContext* a1) {
    if (func_800B867C((Actor*)a0, a1) != 0) {
        a0->update = (actor_func)EnAObj_Update1;
    }
}

UNK_RET EnAObj_Main(ActorEnAObj* a0, GlobalContext* a1) {
    (a0->update)((Actor*)a0, (GlobalContext*)a1);
    func_800B675C((Actor*)a0, 45.0f);
    Collision_AddOT(a1, &a1->collisionContext, (ColCommon*)&a0->collision);
}

UNK_RET EnAObj_Draw(ActorEnAObj* a0, GlobalContext* a1) {
    func_800BDFC0(a1, D_801ADEB0[a0->base.variable]);
}
