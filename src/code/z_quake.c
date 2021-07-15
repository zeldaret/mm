#include "global.h"

QuakeRequest sQuakeRequest[4];
s16 D_801C0EC0 = 1;
s16 sQuakeRequestCount = 0;

s16 (*sQuakeCallbacks[])(QuakeRequest*, ShakeInfo*) = {
    NULL, Quake_Callback1, Quake_Callback2, Quake_Callback3, Quake_Callback4, Quake_Callback5, Quake_Callback6,
};


s32 D_801C0EE4 = { 0x03F00000 };
s32 D_801C0EE8 = { 0x01560000 };
s32 D_801C0EEC = { 0x00010000 };

f32 Quake_Random(void) {
    return 2.0f * (Rand_ZeroOne() - 0.5f);
}

void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 y, f32 x) {
    Vec3f* unk50 = &req->cam->focalPoint;
    Vec3f* unk5C = &req->cam->eye;

    Vec3f vec;
    VecSph struc2;
    VecSph struc1;
    Vec3f vec2;

    if (req->unk1C) {
        vec.x = 0;
        vec.y = 0;
        vec.z = 0;
        OLib_Vec3fDiffToVecSphGeo(&struc1, unk5C, unk50);
        struc2.r = req->y * y;
        struc2.pitch = struc1.pitch + req->unk14.unk00 + 0x4000;
        struc2.yaw = struc1.yaw + req->unk14.unk02;
        OLib_AddVec(&vec, &vec, &struc2);
        struc2.r = req->x * x;
        struc2.pitch = struc1.pitch + req->unk14.unk00;
        struc2.yaw = struc1.yaw + req->unk14.unk02 + 0x4000;
        OLib_AddVec(&vec, &vec, &struc2);
    } else {
        vec.x = 0;
        vec.y = req->y * y;
        vec.z = 0;
        struc2.r = req->x * x;
        struc2.pitch = req->unk14.unk00;
        struc2.yaw = req->unk14.unk02;
        OLib_AddVec(&vec, &vec, &struc2);
    }

    vec2 = vec;
    shake->eyeChange = vec2;
    shake->focalPointChange = vec2;
    shake->rotZ = req->rotZ * y;
    shake->zoom = req->zoom * y;
}

s16 Quake_Callback1(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 a = Math_SinS(req->speed * req->countdown);
        Quake_UpdateShakeInfo(req, shake, a, Rand_ZeroOne() * a);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback5(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 a = Math_SinS(req->speed * req->countdown);
        Quake_UpdateShakeInfo(req, shake, a, a);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback6(QuakeRequest* req, ShakeInfo* shake) {
    f32 a;

    req->countdown--;
    a = Math_SinS(req->speed * ((req->countdown & 0xF) + 500));
    Quake_UpdateShakeInfo(req, shake, a, Rand_ZeroOne() * a);
    return 1;
}

s16 Quake_Callback3(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 a = Math_SinS(req->speed * req->countdown) * ((f32)req->countdown / (f32)req->countdownMax);
        Quake_UpdateShakeInfo(req, shake, a, a);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback2(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 a = Quake_Random();

        Quake_UpdateShakeInfo(req, shake, a, Rand_ZeroOne() * a);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_Callback4(QuakeRequest* req, ShakeInfo* shake) {
    if (req->countdown > 0) {
        f32 a = Quake_Random() * ((f32)req->countdown / (f32)req->countdownMax);

        Quake_UpdateShakeInfo(req, shake, a, Rand_ZeroOne() * a);
        req->countdown--;
    }
    return req->countdown;
}

s16 Quake_GetFreeIndex(void) {
    s32 i;
    s32 ret = 0;
    s32 min = 0x10000;

    for (i = 0; i < ARRAY_COUNT(sQuakeRequest); i++) {
        if (sQuakeRequest[i].callbackIdx == 0) {
            ret = i;
            break;
        }

        if (sQuakeRequest[i].countdown < min) {
            min = sQuakeRequest[i].countdown;
            ret = i;
        }
    }

    return ret;
}

QuakeRequest* Quake_AddImpl(Camera* cam, u32 callbackIdx) {
    s16 idx = Quake_GetFreeIndex();
    QuakeRequest* req = &sQuakeRequest[idx];

    func_80096880(req, 0, sizeof(QuakeRequest)); // memset
    req->cam = cam;
    req->camPtrIdx = cam->thisIdx;
    req->callbackIdx = callbackIdx;
    req->unk1C = 1;
    req->randIdx = ((s16)(Rand_ZeroOne() * (f32)0x10000) & ~3) + idx;
    sQuakeRequestCount++;

    return req;
}

void Quake_Remove(QuakeRequest* req) {
    req->callbackIdx = 0;
    req->countdown = -1;
    sQuakeRequestCount--;
}

QuakeRequest* Quake_GetRequest(s16 idx) {
    QuakeRequest* req = &sQuakeRequest[idx & 3];

    if (req->callbackIdx == 0) {
        return NULL;
    }

    if (idx != req->randIdx) {
        return NULL;
    }

    return req;
}

#ifdef NON_MATCHING
u32 Quake_SetValue(s16 idx, s16 valueType, s16 value) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req == NULL) {
        return false;
    } else {
        switch (valueType) {
            case 1:
                req->speed = value;
                break;
            case 2:
                req->y = value;
                break;
            case 4:
                req->x = value;
                break;
            case 8:
                req->zoom = value;
                break;
            case 0x10:
                req->rotZ = value;
                break;
            case 0x20:
                req->unk14.unk00 = value;
                break;
            case 0x40:
                req->unk14.unk02 = value;
                break;
            case 0x80:
                req->unk14.unk04 = value;
                break;
            case 0x100:
                req->countdown = value;
                req->countdownMax = req->countdown;
                break;
            case 0x200:
                req->unk1C = value;
                break;
        }
        return true;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake_SetValue.asm")
#endif

u32 Quake_SetSpeed(s16 idx, s16 value) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->speed = value;
        return true;
    }
    return false;
}

u32 Quake_SetCountdown(s16 idx, s16 value) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->countdown = value;
        req->countdownMax = req->countdown;
        return true;
    }
    return false;
}

s16 Quake_GetCountdown(s16 idx) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        return req->countdown;
    }
    return 0;
}

u32 Quake_SetQuakeValues(s16 idx, s16 y, s16 x, s16 zoom, s16 rotZ) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->y = y;
        req->x = x;
        req->zoom = zoom;
        req->rotZ = rotZ;
        return true;
    }
    return false;
}

u32 Quake_SetUnkValues(s16 idx, s16 arg1, SubQuakeRequest14 arg2) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        req->unk1C = arg1;

        req->unk14 = arg2;
        return true;
    }
    return false;
}

void Quake_Init(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(sQuakeRequest); i++) {
        sQuakeRequest[i].callbackIdx = 0;
        sQuakeRequest[i].countdown = 0;
    }
    D_801C0EC0 = 1;
    sQuakeRequestCount = 0;
}

s16 Quake_Add(Camera* cam, u32 callbackIdx) {
    return Quake_AddImpl(cam, callbackIdx)->randIdx;
}

u32 Quake_RemoveFromIdx(s16 idx) {
    QuakeRequest* req = Quake_GetRequest(idx);

    if (req != NULL) {
        Quake_Remove(req);
        return true;
    }
    return false;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake_Calc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_SetCountdown.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_GetCountdown.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_GetType.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_SetType.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_ClearType.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_GetFloorQuake.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_quake/Quake_NumActiveQuakes.asm")


