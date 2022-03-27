#include "global.h"
#include "z64rumble.h"

u8 D_801D1E70 = true;

// RumbleImpl?
void func_80182CE0(UnkRumbleStruct* arg0) {
    s32 index = -1;
    s32 i;
    s32 temp;

    for (i = 0; i < ARRAY_COUNT(arg0->rumbleEnabled); i++) {
        arg0->rumbleEnabled[i] = 0;
    }

    if (!arg0->unk_105) {
        if (D_801D1E70) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                func_8017544C(i, false);
            }
        }

        D_801D1E70 = arg0->unk_105;
        func_80175434();
        return;
    }

    D_801D1E70 = arg0->unk_105;

    if (arg0->unk_104 == 2) {
        for (i = 0; i < MAXCONTROLLERS; ++i) {
            func_8017544C(i, false);
        }

        for (i = 0; i < ARRAY_COUNT(arg0->unk_04); i++) {
            arg0->unk_04[i] = 0;
            arg0->unk_44[i] = 0;
            arg0->unk_84[i] = 0;
            arg0->unk_C4[i] = 0;
        }

        arg0->unk_106 = 0;
        arg0->unk_108 = 0;
        arg0->unk_10A = 0;
        arg0->unk_10B = 0;
        arg0->unk_10C = 0;
        arg0->unk_10D = 0;
        arg0->unk_104 = 1;

        func_80175434();
    }

    if (arg0->unk_104 != 0) {
        for (i = 0; i < ARRAY_COUNT(arg0->unk_04); i++) {
            if (arg0->unk_04[i] != 0) {
                if (arg0->unk_44[i] > 0) {
                    arg0->unk_44[i]--;
                } else {
                    temp = arg0->unk_04[i] - arg0->unk_84[i];
                    if (temp > 0) {
                        arg0->unk_04[i] = temp;
                    } else {
                        arg0->unk_04[i] = 0;
                    }
                }

                temp = arg0->unk_C4[i] + arg0->unk_04[i];
                arg0->unk_C4[i] = temp;
                if (index == -1) {
                    index = i;
                    arg0->rumbleEnabled[0] = (temp >= 0x100);
                } else if (arg0->unk_04[index] < arg0->unk_04[i]) {
                    index = i;
                    arg0->rumbleEnabled[0] = (temp >= 0x100);
                }
            }
        }

        if (arg0->unk_10A != 0) {
            if (arg0->unk_10B > 0) {
                arg0->unk_10B--;
            } else {
                temp = arg0->unk_10A - arg0->unk_10C;
                if (temp > 0) {
                    arg0->unk_10A = temp;
                } else {
                    arg0->unk_10A = 0;
                }
            }

            temp = arg0->unk_10D + arg0->unk_10A;
            arg0->unk_10D = temp;
            arg0->rumbleEnabled[0] = (temp >= 0x100);
        }

        if (arg0->unk_10A != 0) {
            temp = arg0->unk_10A;
        } else if (index == -1) {
            temp = 0;
        } else {
            temp = arg0->unk_04[index];
        }

        if (temp == 0) {
            arg0->unk_108++;
            if (arg0->unk_108 > 5) {
                arg0->unk_106 = 0;
                arg0->unk_108 = 5;
            }
        } else {
            arg0->unk_108 = 0;
            arg0->unk_106++;
            if (arg0->unk_106 > 0x1C20) {
                arg0->unk_104 = 0;
            }
        }
    } else {
        for (i = 0; i < ARRAY_COUNT(arg0->unk_04); i++) {
            arg0->unk_04[i] = 0;
            arg0->unk_44[i] = 0;
            arg0->unk_84[i] = 0;
            arg0->unk_C4[i] = 0;
        }

        arg0->unk_106 = 0;
        arg0->unk_108 = 0;
        arg0->unk_10A = 0;
        arg0->unk_10B = 0;
        arg0->unk_10C = 0;
        arg0->unk_10D = 0;
        func_80175434();
    }
}

void func_80183020(UnkRumbleStruct* arg0) {
    bzero(arg0, sizeof(UnkRumbleStruct));
    arg0->unk_104 = 2;
    arg0->unk_105 = true;
}

void func_80183058(UnkRumbleStruct* arg0) {
}
