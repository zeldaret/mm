#include "global.h"

f32 func_800F23E0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    char pad[0x1C];
    f32 sq = SQ(arg0);
    f32 cube = sq * arg0;

    return (((cube + cube) - sq * 3.0f) + 1.0f) * arg2 + (sq * 3.0f - (cube + cube)) * arg3 +
           ((cube - (sq + sq)) + arg0) * arg4 * arg1 + (cube - sq) * arg5 * arg1;
}

f32 func_800F2478(f32 target, TransformData* transData, s32 refIdx) {
    s32 i;
    s32 j;

    if (target <= transData->unk02) {
        return transData->unk08;
    }

    if (transData[refIdx - 1].unk02 <= target) {
        return transData[refIdx - 1].unk08;
    }

    for (i = 0;; i++) {
        j = i + 1;
        if (transData[j].unk02 > target) {
            if (transData[i].unk00 & 1) {
                return transData[i].unk08;
            } else if (transData[i].unk00 & 2) {
                return transData[i].unk08 +
                       ((target - (f32)transData[i].unk02) / ((f32)transData[j].unk02 - (f32)transData[i].unk02)) *
                           (transData[j].unk08 - transData[i].unk08);
            } else {
                f32 diff = (f32)transData[j].unk02 - (f32)transData[i].unk02;
                return func_800F23E0((target - transData[i].unk02) / ((f32)transData[j].unk02 - transData[i].unk02),
                                     diff * (1.0f / 30.0f), transData[i].unk08, transData[j].unk08, transData[i].unk06,
                                     transData[j].unk04);
            }
        }
    }
}
