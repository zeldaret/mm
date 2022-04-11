#include "global.h"

// SetTextId?, OOT's func_80035B18
void func_800E8EA0(GlobalContext* globalCtx, Actor* actor, u16 textId) {
    func_80151938(globalCtx, textId); // ContinueTextBox?
    actor->textId = textId;
}

// OOT's Flags_GetEventChkInf?
s32 nop_800E8ED0(UNK_TYPE4 arg0) {
    return false;
}

// OOT's Flags_SetEventChkInf?
void nop_800E8EE0(UNK_TYPE4 arg0) {
}

// OOT's Flags_GetInfTable?
s32 nop_800E8EEC(UNK_TYPE4 arg0) {
    return false;
}

// OOT's Flags_SetInfTable?
void nop_800E8EFC(UNK_TYPE4 arg0) {
}


// RotateBack, OOT's func_80037F30
s32 func_800E8F08(Vec3s* headRot, Vec3s* torsoRot) {
    Math_SmoothStepToS(&headRot->y, 0, 6, 0x1838, 0x64);
    Math_SmoothStepToS(&headRot->x, 0, 6, 0x1838, 0x64);
    Math_SmoothStepToS(&torsoRot->y, 0, 6, 0x1838, 0x64);
    Math_SmoothStepToS(&torsoRot->x, 0, 6, 0x1838, 0x64);
    return true;
}

// RotateToPoint, OOT's func_80037FC8
s32 func_800E8FA4(Actor* actor, Vec3f* target, Vec3s* headRot, Vec3s* torsoRot) {
    s16 targetPitch;
    s16 targetYaw;
    s16 yawDiffFromTarget;

    targetPitch = Math_Vec3f_Pitch(&actor->focus.pos, target);
    targetYaw = Math_Vec3f_Yaw(&actor->focus.pos, target) - actor->world.rot.y;

    Math_SmoothStepToS(&headRot->x, targetPitch, 6, 0x7D0, 1);
    headRot->x = CLAMP(headRot->x, -0x1770, 0x1770);

    yawDiffFromTarget = Math_SmoothStepToS(&headRot->y, targetYaw, 6, 0x7D0, 1);
    headRot->y = CLAMP(headRot->y, -0x1F40, 0x1F40);

    if (yawDiffFromTarget != 0) {
        if (ABS_ALT(headRot->y) < 0x1F40) {
            return false;
        }
    }

    Math_SmoothStepToS(&torsoRot->y, targetYaw - headRot->y, 4, 0x7D0, 1);
    torsoRot->y = CLAMP(torsoRot->y, -0x2EE0, 0x2EE0);

    return true;
}

// TurnToPlayer, OOT's func_80038154
s32 func_800E9138(GlobalContext* globalCtx, Actor* actor, Vec3s* headRot, Vec3s* torsoRot, f32 focusPosYAdj) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yaw;
    Vec3f target;

    actor->focus.pos = actor->world.pos;
    actor->focus.pos.y += focusPosYAdj;

    if (!((globalCtx->csCtx.state != 0) || D_801D0D50)) {
        yaw = ABS_ALT(BINANG_SUB(actor->yawTowardsPlayer, actor->shape.rot.y));
        if (yaw >= 0x4300) {
            func_800E8F08(headRot, torsoRot);
            return false;
        }
    }

    if ((globalCtx->csCtx.state != 0) || D_801D0D50) {
        target = globalCtx->view.eye;
    } else {
        target = player->actor.focus.pos;
    }

    func_800E8FA4(actor, &target, headRot, torsoRot);

    return true;
}

// TurnToPlayerSetFocus, OOT's func_80038290
s32 func_800E9250(GlobalContext* globalCtx, Actor* actor, Vec3s* headRot, Vec3s* torsoRot, Vec3f focusPos) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yaw;
    Vec3f target;

    actor->focus.pos = focusPos;

    if (!((globalCtx->csCtx.state != 0) || D_801D0D50)) {
        yaw = ABS_ALT(BINANG_SUB(actor->yawTowardsPlayer, actor->shape.rot.y));
        if (yaw >= 0x4300) {
            func_800E8F08(headRot, torsoRot);
            return false;
        }
    }

    if ((globalCtx->csCtx.state != 0) || D_801D0D50) {
        target = globalCtx->view.eye;
    } else {
        target = player->actor.focus.pos;
    }

    func_800E8FA4(actor, &target, headRot, torsoRot);

    return true;
}
