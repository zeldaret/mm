#include <ultra64.h>
#include <global.h>

s16 atans_first_8th(f32 opposite, f32 adjacent) {
    return atan_first_8th_array[(s32)((opposite / adjacent) * 0x400)];
}

s16 atans(f32 opposite, f32 adjacent) {
    s32 phi_v1;

    if (opposite == 0.0f) {
        if (adjacent >= 0.0f) {
            phi_v1 = 0;
        } else {
            phi_v1 = 0x8000;
        }
    } else if (adjacent == 0.0f) {
        if (opposite >= 0.0f) {
            phi_v1 = 0x4000;
        } else {
            phi_v1 = 0xC000;
        }
    } else if (opposite >= 0.0f) {
        if (adjacent >= 0.0f) {
            if (opposite <= adjacent) {
                phi_v1 = atans_first_8th(opposite, adjacent);
            } else {
                phi_v1 = 0x4000 - atans_first_8th(adjacent, opposite);
            }
        } else {
            if (-adjacent < opposite) {
                phi_v1 = atans_first_8th(-adjacent, opposite) + 0x4000;
            } else {
                phi_v1 = 0x8000 - atans_first_8th(opposite, -adjacent);
            }
        }
    } else if (adjacent < 0.0f) {
        if (-opposite <= -adjacent) {
            phi_v1 = atans_first_8th(-opposite, -adjacent) + 0x8000;
        } else {
            phi_v1 = 0xC000 - atans_first_8th(-adjacent, -opposite);
        }
    } else {
        if (adjacent < -opposite) {
            phi_v1 = atans_first_8th(adjacent, -opposite) + 0xC000;
        } else {
            phi_v1 = -atans_first_8th(-opposite, adjacent);
        }
    }
    return phi_v1;
}

f32 atan(f32 opposite, f32 adjacent) {
    return atans(opposite, adjacent) * D_801E01E0;
}

s16 Math_FAtan2F(f32 adjacent, f32 opposite) {
    return atans(opposite, adjacent);
}

f32 atan_flip(f32 adjacent, f32 opposite) {
    return atan(opposite, adjacent);
}
