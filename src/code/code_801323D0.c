#include "global.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
} cmd0;

s32 func_801323D0(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd0* cmd = (cmd0*)*arg1;
    u16 a0 = (cmd->unk1 << 8) | cmd->unk2;

    if (gSaveContext.weekEventReg[a0 >> 8] & (a0 & 0xFF)) {
        *arg1 = *arg1 + cmd->unk3;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
} cmd1;

s32 func_80132428(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd1* cmd = (cmd1*)*arg1;
    u16 a0 = (cmd->unk1 << 8) | cmd->unk2;

    if (gSaveContext.weekEventReg[a0 >> 8] & (a0 & 0xFF)) {
        *arg1 = *arg1 + (s16)((cmd->unk3 << 8) | cmd->unk4);;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    s8 unk5;
} cmd2;

s32 func_80132494(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    s32 inRange = 0;
    cmd2* cmd = (cmd2*)*arg1;

    f32 f;
    u16 start;
    u16 end;
    u16 now;

    f = cmd->unk1 * 60.0f;
    f += cmd->unk2;
    start = f * 45.5f;
    start -= 0x3FFC;


    f = cmd->unk3 * 60.0f;
    f += cmd->unk4;
    end = f * 45.5f;
    end -= 0x3FFC;
    end -= 1;

    now = gSaveContext.time;
    now -= 0x3FFC;

    if ((start <= now) && (now <= end)) {
        inRange = 1;
    }

    if (inRange == 1) {
        *arg1 = *arg1 + cmd->unk5;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
} cmd3;

s32 func_801326B8(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    s32 inRange = 0;
    cmd3* cmd = (cmd3*)*arg1;

    f32 f;
    u16 start;
    u16 end;
    u16 now;

    f = cmd->unk1 * 60.0f;
    f += cmd->unk2;
    start = f * 45.5f;
    start -= 0x3FFC;


    f = cmd->unk3 * 60.0f;
    f += cmd->unk4;
    end = f * 45.5f;
    end -= 0x3FFC;
    end -= 1;

    now = gSaveContext.time;
    now -= 0x3FFC;

    if ((start <= now) && (now <= end)) {
        inRange = 1;
    }

    if (inRange == 1) {
        *arg1 = *arg1 + (s16)((cmd->unk5 << 8) | cmd->unk6);
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} cmd4;

s32 func_801328F0(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd4* cmd = (cmd4*)*arg1;

    arg2->unk0 = (cmd->unk1 << 8) | cmd->unk2;
    arg2->unkC = 1;

    return 1;
}

s32 func_80132920(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    arg2->unkC = 0;

    return 1;
}

s32 func_80132938(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    arg2->unkC = 1;

    return 1;
}

s32 func_80132954(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    s8 unk2;
} cmd8;

s32 func_8013296C(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd8* cmd = (cmd8*)*arg1;

    if (((cmd->unk1 == 0) && (gSaveContext.inventory.items[gItemSlots[0x2D]] == 0x2D)) ||
        ((cmd->unk1 == 1) && (gSaveContext.inventory.items[gItemSlots[0x2F]] == 0x2F)) ||
        ((cmd->unk1 == 2) && (Player_GetMask(globalCtx) == 7))) {
        *arg1 = *arg1 + cmd->unk2;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
} cmd9;

s32 func_80132A18(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd9* cmd = (cmd9*)*arg1;

    arg2->unk0 = cmd->unk1;
    arg2->unkC = 1;

    return 1;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
} cmd10;

s32 func_80132A3C(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd10* cmd = (cmd10*)*arg1;
    s16 a0 = (cmd->unk1 << 8) | cmd->unk2;

    if (a0 != globalCtx->sceneNum) {
        *arg1 = *arg1 + cmd->unk3;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
} cmd11;

s32 func_80132A80(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd11* cmd = (cmd11*)*arg1;
    s16 a0 = (cmd->unk1 << 8) | cmd->unk2;

    if (a0 != globalCtx->sceneNum) {
        *arg1 = *arg1 + (s16)((cmd->unk3 << 8) | cmd->unk4);
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
} cmd12;

s32 func_80132AD8(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd12* cmd = (cmd12*)*arg1;
    s16 a0 = (cmd->unk1 << 8) | cmd->unk2;

    if (a0 != (s16)gSaveContext.day) {
        *arg1 = *arg1 + cmd->unk3;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
} cmd13;

s32 func_80132B24(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd13* cmd = (cmd13*)*arg1;
    s16 a0 = (cmd->unk1 << 8) | cmd->unk2;

    if (a0 != (s16)gSaveContext.day) {
        *arg1 = *arg1 + (s16)((cmd->unk3 << 8) | cmd->unk4);
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} cmd14;

s32 func_80132B84(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd14* cmd = (cmd14*)*arg1;
    f32 f;
    u16 time0;
    u16 time1;

    f = cmd->unk1 * 60.0f;
    f += cmd->unk2;
    time0 = f * 45.5f;
    time0 -= 0x3FFC;


    f = cmd->unk3 * 60.0f;
    f += cmd->unk4;
    time1 = f * 45.5f;
    time1 -= 0x3FFC;
    time1 -= 1;

    arg2->unk0 = cmd->unk5;
    arg2->unk4 = time0;
    arg2->unk8 = time1;
    arg2->unkC = 1;

    return 1;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
} cmd15;

s32 func_80132D70(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd15* cmd = (cmd15*)*arg1;
    f32 f;
    u16 testTime;
    u16 now;

    f = cmd->unk1 * 60.0f;
    f += cmd->unk2;
    testTime = f * 45.5f;
    testTime -= 0x3FFC;

    now = gSaveContext.time;
    now -= 0x3FFC;

    if (now < testTime) {
        *arg1 = *arg1 + cmd->unk3;
    }

    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
} cmd16;

s32 func_80132E9C(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd16* cmd = (cmd16*)*arg1;
    f32 f;
    u16 testTime;
    u16 now;

    f = (cmd->unk1 * 60.0f);
    f += cmd->unk2;
    testTime = (u16)(f * 45.5f) - 0x3FFC;
    now = gSaveContext.time - 0x3FFC;

    if (now < testTime) {
        *arg1 = *arg1 + (s16)((cmd->unk3 << 8) | cmd->unk4);
    }

    return 0;
}

typedef struct {
    u8 unk0;
    s8 unk1;
} cmd17;

s32 func_80132FDC(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd17* cmd = (cmd17*)*arg1;

    *arg1 = *arg1 + cmd->unk1;
    return 0;
}

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} cmd18;

s32 func_80133000(GlobalContext* globalCtx, u8** arg1, struct_80133038_arg2* arg2) {
    cmd18* cmd = (cmd18*)*arg1;

    *arg1 = *arg1 + (s16)((cmd->unk1 << 8) | cmd->unk2);
    return 0;
}

s32 func_80133038(GlobalContext* globalCtx, u8* arg1, struct_80133038_arg2* arg2) {
    static s32 (*D_801C5C50[])(GlobalContext*, u8**, struct_80133038_arg2*) = {
        func_801323D0, func_80132428, func_80132494, func_801326B8,
        func_801328F0, func_80132920, func_80132938, func_80132954,
        func_8013296C, func_80132A18, func_80132A3C, func_80132A80,
        func_80132AD8, func_80132B24, func_80132B84, func_80132D70,
        func_80132E9C, func_80132FDC, func_80133000
    };

    static u8 D_801C5C9C[] = { // TODO
        4, 5, 6, 7,
        3, 1, 1, 4,
        3, 2, 4, 5,
        4, 5, 6, 4,
        5, 2, 3
    };

    u8 size;
    s32 ret;

    do {
        size = D_801C5C9C[*arg1];
        ret = (*D_801C5C50[*arg1])(globalCtx, &arg1, arg2);
        arg1 += size;
    } while (ret == 0);

    return arg2->unkC;
}
