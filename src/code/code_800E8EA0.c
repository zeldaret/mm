#include "global.h"

void func_800E8EA0(GlobalContext* globalCtx, Actor* actor, u16 textId) {
    func_80151938(globalCtx, textId);
    actor->textId = textId;
}

s32 nop_800E8ED0(UNK_TYPE4 param_1) {
    return 0;
}

void nop_800E8EE0(UNK_TYPE4 param_1) {
}

s32 nop_800E8EEC(UNK_TYPE4 param_1) {
    return 0;
}

void nop_800E8EFC(UNK_TYPE4 param_1) {
}

s32 func_800E8F08(Vec3s* param_1, Vec3s* param_2) {
    Math_SmoothStepToS(&param_1->y, 0, 6, 6200, 100);
    Math_SmoothStepToS(&param_1->x, 0, 6, 6200, 100);
    Math_SmoothStepToS(&param_2->y, 0, 6, 6200, 100);
    Math_SmoothStepToS(&param_2->x, 0, 6, 6200, 100);
    return 1;
}

s32 func_800E8FA4(Actor* actor, Vec3f* param_2, Vec3s* param_3, Vec3s* param_4) {
    s16 targetPitch;
    s16 targetYaw;
    s16 yawDiffFromTarget;

    targetPitch = Math_Vec3f_Pitch(&actor->focus.pos, param_2);
    targetYaw = Math_Vec3f_Yaw(&actor->focus.pos, param_2) - actor->world.rot.y;

    Math_SmoothStepToS(&param_3->x, targetPitch, 6, 2000, 1);
    param_3->x = CLAMP(param_3->x, -6000, 6000);

    yawDiffFromTarget = Math_SmoothStepToS(&param_3->y, targetYaw, 6, 2000, 1);
    param_3->y = CLAMP(param_3->y, -8000, 8000);

    if (yawDiffFromTarget != 0) {
        if (ABS_ALT(param_3->y) < 8000) {
            return 0;
        }
    }

    Math_SmoothStepToS(&param_4->y, targetYaw - param_3->y, 4, 2000, 1);
    param_4->y = CLAMP(param_4->y, -12000, 12000);

    return 1;
}

s32 func_800E9138(GlobalContext* globalCtx, Actor* actor, Vec3s* param_3, Vec3s* param_4, f32 param_5) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sVar3;
    Vec3f local_14;

    actor->focus.pos = actor->world.pos;
    actor->focus.pos.y += param_5;

    if (((globalCtx->csCtx).state == 0) && (D_801D0D50 == 0)) {
        sVar3 = ABS_ALT(BINANG_SUB(actor->yawTowardsPlayer, actor->shape.rot.y));
        if (sVar3 >= 0x4300) {
            func_800E8F08(param_3, param_4);
            return 0;
        }
    }

    if (((globalCtx->csCtx).state != 0) || (D_801D0D50 != 0)) {
        local_14 = globalCtx->view.eye;
    } else {
        local_14 = player->actor.focus.pos;
    }

    func_800E8FA4(actor, &local_14, param_3, param_4);

    return 1;
}

s32 func_800E9250(GlobalContext* globalCtx, Actor* actor, Vec3s* param_3, Vec3s* param_4, Vec3f param_5) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sVar3;
    Vec3f local_14;

    actor->focus.pos = param_5;

    if (((globalCtx->csCtx).state == 0) && (D_801D0D50 == 0)) {
        sVar3 = ABS_ALT(BINANG_SUB(actor->yawTowardsPlayer, actor->shape.rot.y));
        if (sVar3 >= 0x4300) {
            func_800E8F08(param_3, param_4);
            return 0;
        }
    }

    if (((globalCtx->csCtx).state != 0) || (D_801D0D50 != 0)) {
        local_14 = globalCtx->view.eye;
    } else {
        local_14 = player->actor.focus.pos;
    }

    func_800E8FA4(actor, &local_14, param_3, param_4);

    return 1;
}
