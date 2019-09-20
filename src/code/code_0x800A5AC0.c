#include <ultra64.h>
#include <global.h>

// TODO this file looks like an actor, it should be cleaned up as such

// This file is most likely En_A_Obj

UNK_RET EnAObj_Init(void* a0, UNK_TYPE a1) {
    s800A5AC0* s0 = (s800A5AC0*)a0;
    s0->unk116 = ((s0->unk1C >> 8) & 0xFF) | 0x300;
    s0->unk1C = (s0->unk1C & 0xFF) - 9;
    Lib_ApplyActorInitVars((z_Actor*)s0, (z_ActorCompInitEntry*)&D_801ADEAC);
    func_800B3BA4(&s0->unkBC, 0, (UNK_PTR)&func_800B3FC0, 12);
    Collision_InitCylinder(a1, &s0->unk148, (z_Actor*)s0, &D_801ADE80);
    Collision_CylinderMoveToActor((z_Actor*)s0, &s0->unk148);
    s0->unkB6 = 255;
    s0->unk144 = EnAObj_Update1;
}

UNK_RET EnAObj_Fini(s800A5AC0* a0, z_GlobalContext* a1) {
    UNK_TYPE* a2 = &a0->unk148;
    Collision_FiniCylinder(a1, a2);
}

UNK_RET EnAObj_Update1(s800A5AC0* a0, UNK_TYPE a1) {
    s16 v0;
    s32 v1;
    if (func_800B84D0(a0, a1) != 0) {
        a0->unk144 = (void(*)(s800A5AC0*, UNK_TYPE))EnAObj_Update2; //! Is this cast correct?
    } else {
        v0 = a0->unk92 - a0->unkBE;
        v1 = (v0 < 0)? -v0 : v0;
        if ((v1 < 10240) || ((a0->unk1C == 1) && (v1 > 22528))) {
            func_800B863C(a0, a1);
        }
    }
}

UNK_RET EnAObj_Update2(s800A5AC0* a0) {
    if (func_800B867C(a0) != 0) {
        a0->unk144 = EnAObj_Update1;
    }
}

UNK_RET EnAObj_Main(s800A5AC0* a0, UNK_TYPE a1) {
    (a0->unk144)(a0, a1);
    func_800B675C(a0, 0x42340000);
    Collision_AddOT(a1, a1 + 0x18884, &a0->unk148);
}

UNK_RET EnAObj_Draw(s800A5AC0* a0, UNK_TYPE a1) {
    func_800BDFC0(a1, D_801ADEB0[a0->unk1C], a1, a0);
}
