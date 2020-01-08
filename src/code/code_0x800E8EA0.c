#include <ultra64.h>
#include <global.h>

void func_800E8EA0(GlobalContext* ctxt, Actor* actor, u16 param_3) {
    func_80151938(ctxt, param_3);
    actor->textId = param_3;
}

s32 nop_800E8ED0(UNK_TYPE4 param_1) {
    return 0;
}

void nop_800E8EE0(UNK_TYPE4 param_1) {}

s32 nop_800E8EEC(UNK_TYPE4 param_1) {
    return 0;
}

void nop_800E8EFC(UNK_TYPE4 param_1) {}

s32 func_800E8F08(Vector3s* param_1, Vector3s* param_2) {
  Lib_ScaleMaxMin_s(&param_1->y, 0, 6, 6200, 100);
  Lib_ScaleMaxMin_s(&param_1->x, 0, 6, 6200, 100);
  Lib_ScaleMaxMin_s(&param_2->y, 0, 6, 6200, 100);
  Lib_ScaleMaxMin_s(&param_2->x, 0, 6, 6200, 100);
  return 1;
}

s32 func_800E8FA4(Actor* actor, Vector3f* param_2, Vector3s* param_3, Vector3s* param_4) {
    s16 targetPitch;
    s16 targetYaw;
    s16 yawDiffFromTarget;

    targetPitch = Lib_PitchVec3f(&actor->topPosRot.pos,param_2);
    targetYaw = Lib_YawVec3f(&actor->topPosRot.pos,param_2) - actor->currPosRot.rot.y;

    Lib_ScaleMaxMin_s(&param_3->x, targetPitch, 6, 2000, 1);
    param_3->x = (param_3->x < -6000)? -6000 : ((6000 < param_3->x)? 6000 : param_3->x);

    yawDiffFromTarget = Lib_ScaleMaxMin_s(&param_3->y, targetYaw, 6, 2000, 1);
    param_3->y = (param_3->y < -8000)? -8000 : ((8000 < param_3->y)? 8000 : param_3->y);

    if (yawDiffFromTarget != 0) {
        if ((param_3->y < 0? -param_3->y : param_3->y) < 8000) {
            return 0;
        }
    }

    Lib_ScaleMaxMin_s(&param_4->y, targetYaw - param_3->y, 4, 2000, 1);
    param_4->y = (param_4->y < -12000)? -12000 : ((12000 < param_4->y)? 12000 : param_4->y);

    return 1;
}

s32 func_800E9138(GlobalContext* ctxt, Actor* actor, Vector3s* param_3, Vector3s* param_4, f32 param_5) {
    s16 sVar3;
    Actor *player;
    Vector3f local_14;

    player = (ctxt->actorContext).actorTypeLists[2].head;
    actor->topPosRot.pos = actor->currPosRot.pos;
    actor->topPosRot.pos.y += param_5;

    if (((ctxt->cutsceneContext).state == 0) && (D_801D0D50 == 0)) {
        sVar3 = actor->yawToLink - actor->drawParams.rot.y;
        // TODO is this shifting because of a missing cast?
        if (0x42ff < (sVar3 < 0? ((-sVar3 << 0x10) >> 0x10) : ((sVar3 << 0x10) >> 0x10))) {
            func_800E8F08(param_3,param_4);
            return 0;
        }
    }

    if (((ctxt->cutsceneContext).state != 0) || (D_801D0D50 != 0)) {
        local_14 = ctxt->view.eye;
    } else {
        local_14 = player->topPosRot.pos;
    }

    func_800E8FA4(actor,&local_14,param_3,param_4);

    return 1;
}
s32 func_800E9250(GlobalContext* ctxt, Actor* actor, Vector3s* param_3, Vector3s* param_4, Vector3f param_5) {
    s16 sVar3;
    Actor *player;
    Vector3f local_14;

    player = (ctxt->actorContext).actorTypeLists[2].head;
    actor->topPosRot.pos = param_5;

    if (((ctxt->cutsceneContext).state == 0) && (D_801D0D50 == 0)) {
        sVar3 = actor->yawToLink - actor->drawParams.rot.y;
        // TODO is this shifting because of a missing cast?
        if (0x42ff < (sVar3 < 0? ((-sVar3 << 0x10) >> 0x10) : ((sVar3 << 0x10) >> 0x10))) {
            func_800E8F08(param_3,param_4);
            return 0;
        }
    }

    if (((ctxt->cutsceneContext).state != 0) || (D_801D0D50 != 0)) {
        local_14 = ctxt->view.eye;
    } else {
        local_14 = player->topPosRot.pos;
    }

    func_800E8FA4(actor,&local_14,param_3,param_4);

    return 1;
}

