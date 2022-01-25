#include "global.h"

#define SCHEDULE_CALC_TIME(hour, minute, dest, temp) \
    (temp) = (hour) * 60.0f; \
    (temp) += (minute); \
    (dest) = (temp) * 45.5f; /* 45.5f = (0x10000 / 60 / 24.0f) */ \
    (dest) = SCHEDULE_CONVERT_TIME(dest);

s32 Schedule_FlagCheckS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdFlagCheckS* cmd = (ScheduleCmdFlagCheckS*)*script;
    u16 flag = (cmd->flagByte << 8) | cmd->flagMask;

    if (gSaveContext.weekEventReg[flag >> 8] & (flag & 0xFF)) {
        *script = *script + cmd->offset;
    }

    return false;
}

s32 Schedule_FlagCheckL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdFlagCheckL* cmd = (ScheduleCmdFlagCheckL*)*script;
    u16 flag = (cmd->flagByte << 8) | cmd->flagMask;

    if (gSaveContext.weekEventReg[flag >> 8] & (flag & 0xFF)) {
        *script = *script + (s16)((cmd->offsetH << 8) | cmd->offsetL);
    }

    return false;
}

s32 Schedule_TimeRangeCheckS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    s32 inRange = 0;
    ScheduleCmdTimeRangeCheckS* cmd = (ScheduleCmdTimeRangeCheckS*)*script;
    f32 f;
    u16 start;
    u16 end;
    u16 now;

    SCHEDULE_CALC_TIME(cmd->startHr, cmd->startMin, start, f);

    SCHEDULE_CALC_TIME(cmd->endHr, cmd->endMin, end, f);
    end -= 1;

    now = SCHEDULE_TIME_NOW;

    if ((start <= now) && (now <= end)) {
        inRange = 1;
    }

    if (inRange == 1) {
        *script = *script + cmd->offset;
    }

    return false;
}

s32 Schedule_TimeRangeCheckL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    s32 inRange = false;
    ScheduleCmdTimeRangeCheckL* cmd = (ScheduleCmdTimeRangeCheckL*)*script;
    f32 f;
    u16 start;
    u16 end;
    u16 now;

    SCHEDULE_CALC_TIME(cmd->startHr, cmd->startMin, start, f);

    SCHEDULE_CALC_TIME(cmd->endHr, cmd->endMin, end, f);
    end -= 1;

    now = SCHEDULE_TIME_NOW;

    if ((start <= now) && (now <= end)) {
        inRange = true;
    }

    if (inRange == true) { // direct comparison required to match
        *script = *script + (s16)((cmd->offsetH << 8) | cmd->offsetL);
    }

    return false;
}

s32 Schedule_ReturnL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdReturnL* cmd = (ScheduleCmdReturnL*)*script;

    result->result = (cmd->retH << 8) | cmd->retL; //! @bug result is a u8, value is truncated
    result->hasResult = true;

    return true;
}

s32 Schedule_End(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    result->hasResult = false;

    return true;
}

s32 Schedule_ReturnEmpty(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    result->hasResult = true;

    return true;
}

s32 Schedule_Nop(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    return false;
}

s32 Schedule_ItemCheckS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdItemCheckS* cmd = (ScheduleCmdItemCheckS*)*script;

    if (((cmd->which == SCHEDULE_ITEM_CHECK_ROOM_KEY) && (INV_CONTENT(ITEM_ROOM_KEY) == ITEM_ROOM_KEY)) ||
        ((cmd->which == SCHEDULE_ITEM_CHECK_LETTER_TO_KAFEI) &&
         (INV_CONTENT(ITEM_LETTER_TO_KAFEI) == ITEM_LETTER_TO_KAFEI)) ||
        ((cmd->which == SCHEDULE_ITEM_CHECK_MASK_ROMANI) && (Player_GetMask(globalCtx) == PLAYER_MASK_ROMANI))) {
        *script = *script + cmd->offset;
    }

    return false;
}

s32 Schedule_ReturnS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdReturnS* cmd = (ScheduleCmdReturnS*)*script;

    result->result = cmd->result;
    result->hasResult = true;

    return true;
}

s32 Schedule_SceneCheckS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdSceneCheckS* cmd = (ScheduleCmdSceneCheckS*)*script;
    s16 scene = (cmd->sceneH << 8) | cmd->sceneL;

    if (scene != globalCtx->sceneNum) {
        *script = *script + cmd->offset;
    }

    return false;
}

s32 Schedule_SceneCheckL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdSceneCheckL* cmd = (ScheduleCmdSceneCheckL*)*script;
    s16 scene = (cmd->sceneH << 8) | cmd->sceneL;

    if (scene != globalCtx->sceneNum) {
        *script = *script + (s16)((cmd->offsetH << 8) | cmd->offsetL);
    }

    return false;
}

s32 Schedule_DayCheckS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdDayCheckS* cmd = (ScheduleCmdDayCheckS*)*script;
    s16 day = (cmd->dayH << 8) | cmd->dayL;

    if (day != (s16)gSaveContext.day) {
        *script = *script + cmd->offset;
    }

    return false;
}

s32 Schedule_DayCheckL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdDayCheckL* cmd = (ScheduleCmdDayCheckL*)*script;
    s16 day = (cmd->dayH << 8) | cmd->dayL;

    if (day != (s16)gSaveContext.day) {
        *script = *script + (s16)((cmd->offsetH << 8) | cmd->offsetL);
    }

    return false;
}

s32 Schedule_ReturnTime(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdReturnTime* cmd = (ScheduleCmdReturnTime*)*script;
    f32 f;
    u16 time0;
    u16 time1;

    SCHEDULE_CALC_TIME(cmd->time0Hr, cmd->time0Min, time0, f);

    SCHEDULE_CALC_TIME(cmd->time1Hr, cmd->time1Min, time1, f);
    time1 -= 1;

    result->result = cmd->result;
    result->time0 = time0;
    result->time1 = time1;
    result->hasResult = true;

    return true;
}

s32 Schedule_TimeCheckS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdTimeCheckS* cmd = (ScheduleCmdTimeCheckS*)*script;
    f32 f;
    u16 testTime;
    u16 now;

    SCHEDULE_CALC_TIME(cmd->timeHr, cmd->timeMin, testTime, f);

    now = SCHEDULE_TIME_NOW;

    if (now < testTime) {
        *script = *script + cmd->offset;
    }

    return false;
}

s32 Schedule_TimeCheckL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdTimeCheckL* cmd = (ScheduleCmdTimeCheckL*)*script;
    f32 f;
    u16 testTime;
    u16 now;

    SCHEDULE_CALC_TIME(cmd->timeHr, cmd->timeMin, testTime, f);

    now = SCHEDULE_TIME_NOW;

    if (now < testTime) {
        *script = *script + (s16)((cmd->offsetH << 8) | cmd->offsetL);
    }

    return false;
}

s32 Schedule_JumpS(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdJumpS* cmd = (ScheduleCmdJumpS*)*script;

    *script = *script + cmd->offset;
    return false;
}

s32 Schedule_JumpL(GlobalContext* globalCtx, u8** script, ScheduleResult* result) {
    ScheduleCmdJumpL* cmd = (ScheduleCmdJumpL*)*script;

    *script = *script + (s16)((cmd->offsetH << 8) | cmd->offsetL);
    return false;
}

static s32 (*sCmdFuncs[])(GlobalContext*, u8**, ScheduleResult*) = {
    Schedule_FlagCheckS, Schedule_FlagCheckL, Schedule_TimeRangeCheckS, Schedule_TimeRangeCheckL,
    Schedule_ReturnL,    Schedule_End,        Schedule_ReturnEmpty,     Schedule_Nop,
    Schedule_ItemCheckS, Schedule_ReturnS,    Schedule_SceneCheckS,     Schedule_SceneCheckL,
    Schedule_DayCheckS,  Schedule_DayCheckL,  Schedule_ReturnTime,      Schedule_TimeCheckS,
    Schedule_TimeCheckL, Schedule_JumpS,      Schedule_JumpL,
};

static u8 sCmdSizes[] = {
    sizeof(ScheduleCmdFlagCheckS),
    sizeof(ScheduleCmdFlagCheckL),
    sizeof(ScheduleCmdTimeRangeCheckS),
    sizeof(ScheduleCmdTimeRangeCheckL),
    sizeof(ScheduleCmdReturnL),
    sizeof(ScheduleCmdBase),
    sizeof(ScheduleCmdBase),
    sizeof(ScheduleCmdNop),
    sizeof(ScheduleCmdItemCheckS),
    sizeof(ScheduleCmdReturnS),
    sizeof(ScheduleCmdSceneCheckS),
    sizeof(ScheduleCmdSceneCheckL),
    sizeof(ScheduleCmdDayCheckS),
    sizeof(ScheduleCmdDayCheckL),
    sizeof(ScheduleCmdReturnTime),
    sizeof(ScheduleCmdTimeCheckS),
    sizeof(ScheduleCmdTimeCheckL),
    sizeof(ScheduleCmdJumpS),
    sizeof(ScheduleCmdJumpL),
};

s32 Schedule_RunScript(GlobalContext* globalCtx, u8* script, ScheduleResult* result) {
    u8 size;
    s32 stop;

    do {
        size = sCmdSizes[*script];
        stop = (*sCmdFuncs[*script])(globalCtx, &script, result);
        script += size;
    } while (!stop);

    return result->hasResult;
}
