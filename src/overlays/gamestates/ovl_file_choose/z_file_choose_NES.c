/*
 * File: z_file_choose_NES.c
 * Overlay: ovl_file_choose
 * Description:
 */

#include "z_file_choose.h"

void func_801A3238(u8 playerIdx, u16 seqId, u8 fadeTimer, s8 arg3, s8 arg4); /* extern */
void func_801A4058(u16);



extern Gfx D_010311F0[];
extern Gfx D_01031408[];
extern Gfx D_01031618[];

extern UNK_TYPE D_01002800;
extern UNK_TYPE D_01007980;
extern UNK_TYPE D_0102A6B0;
extern UNK_TYPE D_0102B170;
extern UNK_TYPE D_010310F0;

// there are uses of D_0E000000.fillRect (appearing as D_0E0002E0) in this file
extern GfxMasterList D_0E000000;

extern s16 fileChooseSkyboxRotation;

extern u32 D_801C6798[];

#define gSramSlotOffsets D_801C6798
#define GET_NEWF(sramCtx, slotNum, index) (sramCtx->readBuff[gSramSlotOffsets[slotNum] + offsetof(SaveContext, newf[index])])
#define SLOT_OCCUPIED(sramCtx, slotNum) \
    ((GET_NEWF(sramCtx, slotNum, 0) == 'Z') || \
     (GET_NEWF(sramCtx, slotNum, 1) == 'E') || \
     (GET_NEWF(sramCtx, slotNum, 2) == 'L') || \
     (GET_NEWF(sramCtx, slotNum, 3) == 'D') || \
     (GET_NEWF(sramCtx, slotNum, 4) == 'A') || \
     (GET_NEWF(sramCtx, slotNum, 5) == '3'))

#define GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, index) (fileChooseCtx->newf[slotNum][index])
#define FILE_CHOOSE_SLOT_OCCUPIED(fileChooseCtx, slotNum) \
    ((GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, 0) == 'Z') && \
     (GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, 1) == 'E') && \
     (GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, 2) == 'L') && \
     (GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, 3) == 'D') && \
     (GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, 4) == 'A') && \
     (GET_FILE_CHOOSE_NEWF(fileChooseCtx, slotNum, 5) == '3'))


void func_8080BC20(FileChooseContext* this) {
    this->unk_24486++;
}

void FileChoose_nop8080bc44(void) {
}

void FileChoose_nop8080BC4C(FileChooseContext* this) {
}

void func_8080BC58(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    if (this->unk_24486 == 0) {
        if (gSaveContext.option_id != 0xA51D) { // Magic number?
            this->unk_24486++;
        } else {
            // TODO: defines for these
            this->unk_24484 = 1;
            this->unk_24486 = 0;
            this->unk_244AC = 0;
            this->unk_244AE = 1;
        }
    }
    if (this->unk_24486 == 1) {
        this->unk_2450A -= 40;
        if (this->unk_2450A <= 0) {
            this->unk_2450A = 0;
            this->unk_24486++;
        }
    } else {
        if (this->unk_24486 == 2) {
            func_8080BC20(this);
            return;
        }
        this->unk_2450A += 40;
        if (this->unk_2450A >= 255) {
            this->unk_2450A = 255;
            this->unk_24484 = 1;
            this->unk_24486 = 0;
            this->unk_244AC = 0;
            this->unk_244AE = 1;
        }
    }
}

void func_8080BDAC(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    func_8012C628(this->state.gfxCtx);
    FileChoose_nop8080BC4C(this);
}

void FileChoose_RenderView(FileChooseContext* this, f32 eyeX, f32 eyeY, f32 eyeZ) {
    Vec3f eye;
    Vec3f lookAt;
    Vec3f up;

    eye.x = eyeX;
    eye.y = eyeY;
    eye.z = eyeZ;

    lookAt.x = 
    lookAt.y = 
    lookAt.z = 
    0.0f;

    up.x = 
    up.z = 0.0f;
    up.y = 1.0f;

    View_SetViewOrientation(&this->view, &eye, &lookAt, &up);
    View_RenderView(&this->view, 0x7F);
}

// FileChoose_QuadTextureIA8
Gfx* func_8080BE60(Gfx* gfx, void* texture, s16 width, s16 height, s16 point) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSP1Quadrangle(gfx++, point, point + 2, point + 3, point + 1, 0);

    return gfx;
}

// FileChoose_FadeInMenuElements
void func_8080C040(FileChooseContext* this) {
    SramContext* sramCtx = &this->sramCtx;
    s16 i;

    this->unk_244B6[0] += 20;
    this->unk_244BA += 0x10;

    for (i = 0; i < 3; i++) {
        this->unk_244BC[i] = this->unk_244BA;
        if (gSaveContext.unk_3F3F == 0) {
            if (SLOT_OCCUPIED(sramCtx, i)) {
                this->unk_244C2[i] = 
                this->unk_244C8[i] = 
                this->unk_244BA;
                this->unk_244CE[i] += 20;
                if (this->unk_244CE[i] >= 255) {
                    this->unk_244CE[i] = 255;
                }
            }
        } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->unk_244C2[i] = 
                this->unk_244C8[i] = 
                this->unk_244BA;
                this->unk_244CE[i] += 20;

                if (this->unk_244CE[i] >= 255) {
                    this->unk_244CE[i] = 255;
                }
            }
    }

    this->unk_244DA[0] =
    this->unk_244DA[1] =
    this->unk_244E2 =
    this->unk_244BA;
}

// FileChoose_SplitNumber // SplitDigits? ExtractDigits?
void func_8080C228(u16 value, u16* hundreds, u16* tens, u16* ones) {
    *hundreds = 0;
    *tens = 0;
    *ones = value;
    
    do {
        if ((*ones - 100) < 0) {
            break;
        }  
        (*hundreds)++;
        *ones -= 100;
    } while (true);

    do {
        if ((*ones - 10) < 0) {
            break;
        }
        (*tens)++;
        *ones -= 10;
    } while (true);
}

// Start of Config Mode Update Functions

void func_8080C29C(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    func_8080C040(this);
    this->unk_2450A -= 40;
    this->unk_24508 -= 20;
    if (this->unk_24508 <= -94) {
        this->unk_24508 = -94;
        this->unk_24486 = 1;
        this->unk_2450A = 0;
    }
}

void func_8080C324(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    this->unk_244E6 += 20;
    func_8080C040(this);

    if (this->unk_244B6[0] >= 255) {
        this->unk_244B6[0] = 255;
        this->unk_244E6 = 255;
        this->unk_244BA = 200;
        this->unk_24486 = 2;
    }
}

// (FileChooseContext* this);
// (GameState* thisx) {
//     FileChooseContext *this = (FileChooseContext*)thisx;

void func_8080C3A8(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080C3A8.s")

void func_8080D164(GameState* thisx) {
}

void func_8080D170(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D170.s")
// Requires in-function static data to match
// void func_8080D170(GameState *thisx) {
//     static s16 D_80814564 = 0;
//     FileChooseContext *this = (FileChooseContext*)thisx;

//     D_80814564 += 2;
//     if (D_80814564 == 0xFE) {
//         this->unk_24486 = this->unk_2448A;
//         D_80814564 = 0;
//     }
// }

void func_8080D1BC(GameState *thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    this->unk_2450C += 50.0f;
    if (this->unk_2450C >= 314.0f) {
        this->unk_2450C = 314.0f;
        this->unk_24486 = 35;
    }
}

void func_8080D220(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    this->unk_2450C += 50.0f;
    if (this->unk_2450C >= 314.0f) {
        this->unk_2450C = 314.0f;
        this->unk_24486 = 40;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D284.s")
void func_8080D284(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    this->unk_2450C += 50.0f;
    if (this->unk_2450C >= 628.0f) {
        this->unk_2450C = 0.0f;
        this->unk_24486 = 2;
    }
}

// End of Config Mode Update Functions

extern s16 D_8081461C[];
// s16 D_8081461C[] = { 70, 200 };

void func_8080D2EC(FileChooseContext *this) {
    s32 step = ABS_ALT(this->unk_244EA[3] - D_8081461C[this->unk_244F2]) / this->unk_24528;

    if (this->unk_244EA[3] >= D_8081461C[this->unk_244F2]) {
        this->unk_244EA[3] -= step;
    } else {
        this->unk_244EA[3] += step;
    }

    this->unk_24528--;

    if (this->unk_24528 == 0) {
        this->unk_244EA[3] = D_8081461C[this->unk_244F2];
        this->unk_24528 = 0x14;
        this->unk_244F2 ^= 1;
    }
}

// Nameset
void func_80804010(GameState* thisx);
void func_808041A0(GameState* thisx);
void func_80804654(GameState* thisx);
void func_808047D8(GameState* thisx);
void func_8080489C(GameState* thisx);
void func_80804DAC(GameState* thisx);
void func_80804E74(GameState* thisx);
void func_80804F98(GameState* thisx);
void func_8080525C(GameState* thisx);
void func_808052B0(GameState* thisx);
void func_808054A4(GameState* thisx);
void func_808055D0(GameState* thisx);
void func_808058A4(GameState* thisx);
void func_80805918(GameState* thisx);
void func_80805A58(GameState* thisx);
void func_80805B30(GameState* thisx);
void func_80805C1C(GameState* thisx);
void func_80806014(GameState* thisx);
void func_80806148(GameState* thisx);
void func_80806310(GameState* thisx);
void func_808067E0(GameState* thisx);
void func_80806BC8(GameState* thisx);
void func_80806CA0(GameState* thisx);
void func_80806E84(GameState* thisx);
void func_80806F30(GameState* thisx);
void func_808071E4(GameState* thisx);
void func_80807390(GameState* thisx);
void func_8080742C(GameState* thisx);
void func_808074B4(GameState* thisx);
void func_808077AC(GameState* thisx);

// Copy/erase?
void func_80809DF0(GameState* thisx);
void func_80809EA0(GameState* thisx);
void func_8080A3CC(GameState* thisx);
void func_8080A418(GameState* thisx);
void func_8080A4A0(GameState* thisx);
void func_8080A6BC(GameState* thisx);

// gConfigModeUpdateFuncs
extern void (*D_80814568[])(GameState*);
// void (*D_80814568)(GameState*)[] = {
//     func_8080C29C,
//     func_8080C324,
//     func_8080C3A8,
//     func_80804010,
//     func_808041A0,
//     func_80804654,
//     func_808047D8,
//     func_8080489C,
//     func_80804DAC,
//     func_80804E74,
//     func_80804F98,
//     func_8080525C,
//     func_808052B0,
//     func_808054A4,
//     func_808055D0,
//     func_808058A4,
//     func_80805918,
//     func_80805A58,
//     func_80805B30,
//     func_80805C1C,
//     func_80806014,
//     func_80806148,
//     func_80806310,
//     func_808067E0,
//     func_80806BC8,
//     func_80806CA0,
//     func_80806E84,
//     func_80806F30,
//     func_808071E4,
//     func_80807390,
//     func_8080742C,
//     func_808074B4,
//     func_808077AC,
//     func_8080D164,
//     func_8080D1BC,
//     func_80809DF0,
//     func_80809EA0,
//     func_8080A3CC,
//     func_8080D284,
//     func_8080D220,
//     func_8080A418,
//     func_8080A4A0,
//     func_8080A6BC,
//     func_8080D284,
//     func_8080D170,
// };

// FileChoose_ConfigModeUpdate
void func_8080D3D0(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    D_80814568[this->unk_24486](&this->state);
}

// FileChoose_SetWindowVtx
void func_8080D40C(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    s16 i;
    s16 j;
    s16 x;
    s32 tmp;
    s32 tmp2;
    s32 tmp3;

    // windowVtx
    this->unk_A4 = GRAPH_ALLOC(this->state.gfxCtx, sizeof(Vtx) * 80);
    // windowPos
    tmp = this->unk_24508 - 90;

    for (x = 0, i = 0; i < 4; i++) {
        tmp += 0x40;
        tmp2 = (i == 3) ? 0x30 : 0x40;

        for (j = 0, tmp3 = 0x50; j < 5; j++, x += 4, tmp3 -= 0x20) {
            this->unk_A4[x].v.ob[0] = this->unk_A4[x + 2].v.ob[0] = tmp;

            this->unk_A4[x + 1].v.ob[0] = this->unk_A4[x + 3].v.ob[0] = tmp2 + tmp;

            this->unk_A4[x].v.ob[1] = this->unk_A4[x + 1].v.ob[1] = tmp3;

            this->unk_A4[x + 2].v.ob[1] = this->unk_A4[x + 3].v.ob[1] = tmp3 - 0x20;

            this->unk_A4[x].v.ob[2] = this->unk_A4[x + 1].v.ob[2] = this->unk_A4[x + 2].v.ob[2] =
                this->unk_A4[x + 3].v.ob[2] = 0;

            this->unk_A4[x].v.flag = this->unk_A4[x + 1].v.flag = this->unk_A4[x + 2].v.flag =
                this->unk_A4[x + 3].v.flag = 0;

            this->unk_A4[x].v.tc[0] = this->unk_A4[x].v.tc[1] = this->unk_A4[x + 1].v.tc[1] =
                this->unk_A4[x + 2].v.tc[0] = 0;

            this->unk_A4[x + 1].v.tc[0] = this->unk_A4[x + 3].v.tc[0] = tmp2 * 0x20;

            this->unk_A4[x + 2].v.tc[1] = this->unk_A4[x + 3].v.tc[1] = 0x400;

            this->unk_A4[x].v.cn[0] = this->unk_A4[x + 2].v.cn[0] = this->unk_A4[x].v.cn[1] =
                this->unk_A4[x + 2].v.cn[1] = this->unk_A4[x].v.cn[2] = this->unk_A4[x + 2].v.cn[2] =
                    this->unk_A4[x + 1].v.cn[0] = this->unk_A4[x + 3].v.cn[0] = this->unk_A4[x + 1].v.cn[1] =
                        this->unk_A4[x + 3].v.cn[1] = this->unk_A4[x + 1].v.cn[2] =
                            this->unk_A4[x + 3].v.cn[2] = this->unk_A4[x].v.cn[3] =
                                this->unk_A4[x + 2].v.cn[3] = this->unk_A4[x + 1].v.cn[3] =
                                    this->unk_A4[x + 3].v.cn[3] = 255;
        }
    }
}

// void func_8080D6D4(FileChooseContext* this);
void func_8080D6D4(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D6D4.s")
extern s16 D_80814280[];
extern s16 D_80814538[];
extern s16 D_80814554[];
extern s16 D_80814620[];
extern s16 D_80814628[];
extern s16 D_80814630[];
extern s16 D_80814638[];
extern s16 D_80814644[];
extern s16 D_8081464C[];
extern s16 D_80814650[];

// void func_8080D6D4(FileChooseContext *this) {
//     s16 spAC;
//     u16 spA8;
//     u16 spA6;
//     u16 spA4;
//     s32 sp9C;
//     s32 sp98;
//     void *sp50;
//     Gfx *temp_v0;
//     GraphicsContext *temp_v1;
//     Vtx *temp_a0;
//     Vtx *temp_a0_10;
//     Vtx *temp_a0_11;
//     Vtx *temp_a0_12;
//     Vtx *temp_a0_13;
//     Vtx *temp_a0_14;
//     Vtx *temp_a0_15;
//     Vtx *temp_a0_16;
//     Vtx *temp_a0_17;
//     Vtx *temp_a0_18;
//     Vtx *temp_a0_19;
//     Vtx *temp_a0_20;
//     Vtx *temp_a0_21;
//     Vtx *temp_a0_22;
//     Vtx *temp_a0_23;
//     Vtx *temp_a0_24;
//     Vtx *temp_a0_25;
//     Vtx *temp_a0_26;
//     Vtx *temp_a0_27;
//     Vtx *temp_a0_28;
//     Vtx *temp_a0_29;
//     Vtx *temp_a0_2;
//     Vtx *temp_a0_30;
//     Vtx *temp_a0_31;
//     Vtx *temp_a0_32;
//     Vtx *temp_a0_33;
//     Vtx *temp_a0_34;
//     Vtx *temp_a0_35;
//     Vtx *temp_a0_36;
//     Vtx *temp_a0_37;
//     Vtx *temp_a0_38;
//     Vtx *temp_a0_39;
//     Vtx *temp_a0_3;
//     Vtx *temp_a0_40;
//     Vtx *temp_a0_41;
//     Vtx *temp_a0_42;
//     Vtx *temp_a0_43;
//     Vtx *temp_a0_44;
//     Vtx *temp_a0_45;
//     Vtx *temp_a0_46;
//     Vtx *temp_a0_47;
//     Vtx *temp_a0_48;
//     Vtx *temp_a0_49;
//     Vtx *temp_a0_4;
//     Vtx *temp_a0_50;
//     Vtx *temp_a0_51;
//     Vtx *temp_a0_52;
//     Vtx *temp_a0_53;
//     Vtx *temp_a0_54;
//     Vtx *temp_a0_55;
//     Vtx *temp_a0_56;
//     Vtx *temp_a0_57;
//     Vtx *temp_a0_58;
//     Vtx *temp_a0_59;
//     Vtx *temp_a0_5;
//     Vtx *temp_a0_60;
//     Vtx *temp_a0_61;
//     Vtx *temp_a0_62;
//     Vtx *temp_a0_63;
//     Vtx *temp_a0_64;
//     Vtx *temp_a0_65;
//     Vtx *temp_a0_66;
//     Vtx *temp_a0_67;
//     Vtx *temp_a0_68;
//     Vtx *temp_a0_69;
//     Vtx *temp_a0_6;
//     Vtx *temp_a0_70;
//     Vtx *temp_a0_71;
//     Vtx *temp_a0_72;
//     Vtx *temp_a0_73;
//     Vtx *temp_a0_74;
//     Vtx *temp_a0_75;
//     Vtx *temp_a0_76;
//     Vtx *temp_a0_77;
//     Vtx *temp_a0_78;
//     Vtx *temp_a0_79;
//     Vtx *temp_a0_7;
//     Vtx *temp_a0_80;
//     Vtx *temp_a0_81;
//     Vtx *temp_a0_82;
//     Vtx *temp_a0_83;
//     Vtx *temp_a0_84;
//     Vtx *temp_a0_85;
//     Vtx *temp_a0_8;
//     Vtx *temp_a0_9;
//     Vtx *temp_a1_20;
//     Vtx *temp_a1_21;
//     Vtx *temp_a1_4;
//     Vtx *temp_a1_5;
//     Vtx *temp_a1_6;
//     Vtx *temp_a1_7;
//     Vtx *temp_v0_4;
//     Vtx *temp_v0_5;
//     Vtx *temp_v0_6;
//     Vtx *temp_v0_7;
//     s16 *temp_a1_10;
//     s16 *temp_a1_8;
//     s16 *temp_a2_3;
//     s16 *temp_a2_4;
//     s16 *temp_t0;
//     s16 *temp_t0_2;
//     s16 temp_a1;
//     s16 temp_a1_13;
//     s16 temp_a1_14;
//     s16 temp_a1_15;
//     s16 temp_a1_16;
//     s16 temp_a1_17;
//     s16 temp_a1_18;
//     s16 temp_a1_19;
//     s16 temp_a1_3;
//     s16 temp_a1_9;
//     s16 temp_a2;
//     s16 temp_a2_2;
//     s16 temp_a2_5;
//     s16 temp_a2_6;
//     s16 temp_a2_7;
//     s16 temp_a2_8;
//     s16 temp_a2_9;
//     s16 temp_a3;
//     s16 temp_a3_2;
//     s16 temp_a3_3;
//     s16 temp_a3_4;
//     s16 temp_a3_5;
//     s16 temp_a3_6;
//     s16 temp_a3_7;
//     s16 temp_a3_8;
//     s16 temp_a3_9;
//     s16 temp_s1;
//     s16 temp_s1_5;
//     s16 temp_s4;
//     s16 temp_s4_2;
//     s16 temp_s4_3;
//     s16 temp_s4_4;
//     s16 temp_t2;
//     s16 temp_t2_2;
//     s16 temp_t3;
//     s16 temp_t3_2;
//     s16 temp_t3_3;
//     s16 temp_t4;
//     s16 temp_v0_2;
//     s16 temp_v0_3;
//     s16 temp_v0_8;
//     s16 temp_v1_10;
//     s16 temp_v1_11;
//     s16 temp_v1_12;
//     s16 temp_v1_13;
//     s16 temp_v1_14;
//     s16 temp_v1_15;
//     s16 temp_v1_16;
//     s16 temp_v1_17;
//     s16 temp_v1_18;
//     s16 temp_v1_19;
//     s16 temp_v1_20;
//     s16 temp_v1_21;
//     s16 temp_v1_22;
//     s16 temp_v1_23;
//     s16 temp_v1_24;
//     s16 temp_v1_25;
//     s16 temp_v1_26;
//     s16 temp_v1_27;
//     s16 temp_v1_28;
//     s16 temp_v1_29;
//     s16 temp_v1_2;
//     s16 temp_v1_30;
//     s16 temp_v1_31;
//     s16 temp_v1_32;
//     s16 temp_v1_33;
//     s16 temp_v1_34;
//     s16 temp_v1_35;
//     s16 temp_v1_36;
//     s16 temp_v1_37;
//     s16 temp_v1_38;
//     s16 temp_v1_39;
//     s16 temp_v1_3;
//     s16 temp_v1_40;
//     s16 temp_v1_41;
//     s16 temp_v1_42;
//     s16 temp_v1_43;
//     s16 temp_v1_44;
//     s16 temp_v1_45;
//     s16 temp_v1_46;
//     s16 temp_v1_47;
//     s16 temp_v1_48;
//     s16 temp_v1_49;
//     s16 temp_v1_4;
//     s16 temp_v1_50;
//     s16 temp_v1_51;
//     s16 temp_v1_52;
//     s16 temp_v1_53;
//     s16 temp_v1_54;
//     s16 temp_v1_55;
//     s16 temp_v1_56;
//     s16 temp_v1_57;
//     s16 temp_v1_58;
//     s16 temp_v1_59;
//     s16 temp_v1_60;
//     s16 temp_v1_61;
//     s16 temp_v1_62;
//     s16 temp_v1_63;
//     s16 temp_v1_64;
//     s16 temp_v1_65;
//     s16 temp_v1_66;
//     s16 temp_v1_67;
//     s16 temp_v1_68;
//     s16 temp_v1_69;
//     s16 temp_v1_6;
//     s16 temp_v1_70;
//     s16 temp_v1_71;
//     s16 temp_v1_72;
//     s16 temp_v1_73;
//     s16 temp_v1_74;
//     s16 temp_v1_75;
//     s16 temp_v1_76;
//     s16 temp_v1_77;
//     s16 temp_v1_78;
//     s16 temp_v1_79;
//     s16 temp_v1_7;
//     s16 temp_v1_80;
//     s16 temp_v1_81;
//     s16 temp_v1_82;
//     s16 temp_v1_83;
//     s16 temp_v1_84;
//     s16 temp_v1_8;
//     s16 temp_v1_9;
//     s32 temp_a1_11;
//     s32 temp_a1_12;
//     s32 temp_s1_2;
//     s32 temp_s1_3;
//     s32 temp_s1_4;
//     s32 temp_s3;
//     s32 temp_s3_10;
//     s32 temp_s3_11;
//     s32 temp_s3_12;
//     s32 temp_s3_13;
//     s32 temp_s3_14;
//     s32 temp_s3_2;
//     s32 temp_s3_3;
//     s32 temp_s3_4;
//     s32 temp_s3_5;
//     s32 temp_s3_6;
//     s32 temp_s3_7;
//     s32 temp_s3_8;
//     s32 temp_s3_9;
//     s32 temp_t1;
//     u16 temp_a1_2;
//     u8 temp_v1_5;
//     s32 phi_t1;
//     s16 phi_s1;
//     s32 phi_s3;
//     s16 phi_s4;
//     s16 phi_a3;
//     s32 phi_s3_2;
//     s16 phi_s4_2;
//     s32 phi_t0;
//     s16 phi_s4_3;
//     s16 phi_a3_2;
//     s32 phi_s1_2;
//     s32 phi_s3_3;
//     u16 *phi_t2;
//     s32 phi_s1_3;
//     s32 phi_s3_4;
//     s16 phi_a3_3;
//     s16 phi_a3_4;
//     s32 phi_s1_4;
//     s32 phi_s3_5;
//     s16 phi_s1_5;
//     s32 phi_s3_6;
//     s16 phi_t0_2;
//     s16 phi_a3_5;
//     s16 phi_s1_6;
//     s32 phi_s3_7;
//     s16 phi_a3_6;
//     s32 phi_t0_3;
//     s16 phi_a3_7;
//     s32 phi_s3_8;
//     s16 phi_s1_7;
//     s32 phi_s3_9;
//     s16 phi_a3_8;
//     s32 phi_s3_10;
//     s16 phi_s4_4;
//     s32 phi_a1;
//     s16 phi_s4_5;
//     s32 phi_s3_11;
//     s16 phi_s1_8;
//     void *phi_s6;
//     s16 phi_t6;
//     s32 phi_t9;
//     s32 phi_s3_12;

//     // temp_v1 = this->state.gfxCtx;
//     // temp_v0 = temp_v1->polyOpa.d - 0x3C00;
//     // temp_v1->polyOpa.d = temp_v0;
//     // this->unk_243E4 = (Vtx *) temp_v0;

//     this->unk_243E4 = GRAPH_ALLOC(this->state.gfxCtx, 0x3C0 * sizeof(Vtx));



//     for (phi_t1 = 0; phi_t1 < 0x3C0; phi_t1 += 4) {
//         this->unk_243E4[phi_t1].v.ob[0] = this->unk_243E4[phi_t1 + 2].v.ob[0] = 0x12C;
//         this->unk_243E4[phi_t1 + 1].v.ob[0] = this->unk_243E4[phi_t1 + 3].v.ob[0] =
//             this->unk_243E4[phi_t1].v.ob[0] + 0x10;

//         this->unk_243E4[phi_t1].v.ob[1] = this->unk_243E4[phi_t1 + 1].v.ob[1] = 0;
//         this->unk_243E4[phi_t1 + 2].v.ob[1] = this->unk_243E4[phi_t1 + 3].v.ob[1] =
//             this->unk_243E4[phi_t1].v.ob[1] - 0x10;

//         this->unk_243E4[phi_t1].v.ob[2] = this->unk_243E4[phi_t1 + 1].v.ob[2] =
//             this->unk_243E4[phi_t1 + 2].v.ob[2] = this->unk_243E4[phi_t1 + 3].v.ob[2] = 0;

//         this->unk_243E4[phi_t1].v.flag = this->unk_243E4[phi_t1 + 1].v.flag =
//             this->unk_243E4[phi_t1 + 2].v.flag = this->unk_243E4[phi_t1 + 3].v.flag = 0;

//         this->unk_243E4[phi_t1].v.tc[0] = this->unk_243E4[phi_t1].v.tc[1] =
//             this->unk_243E4[phi_t1 + 1].v.tc[1] = this->unk_243E4[phi_t1 + 2].v.tc[0] = 0;

//         this->unk_243E4[phi_t1 + 1].v.tc[0] = this->unk_243E4[phi_t1 + 2].v.tc[1] =
//             this->unk_243E4[phi_t1 + 3].v.tc[0] = this->unk_243E4[phi_t1 + 3].v.tc[1] = 0x200;

//         this->unk_243E4[phi_t1].v.cn[0] = this->unk_243E4[phi_t1 + 1].v.cn[0] =
//             this->unk_243E4[phi_t1 + 2].v.cn[0] = this->unk_243E4[phi_t1 + 3].v.cn[0] =
//                 this->unk_243E4[phi_t1].v.cn[1] = this->unk_243E4[phi_t1 + 1].v.cn[1] =
//                     this->unk_243E4[phi_t1 + 2].v.cn[1] = this->unk_243E4[phi_t1 + 3].v.cn[1] =
//                         this->unk_243E4[phi_t1].v.cn[2] = this->unk_243E4[phi_t1 + 1].v.cn[2] =
//                             this->unk_243E4[phi_t1 + 2].v.cn[2] = this->unk_243E4[phi_t1 + 3].v.cn[2] =
//                                 this->unk_243E4[phi_t1].v.cn[3] = this->unk_243E4[phi_t1 + 1].v.cn[3] =
//                                     this->unk_243E4[phi_t1 + 2].v.cn[3] =
//                                         this->unk_243E4[phi_t1 + 3].v.cn[3] = 0xFF;
//     }

//     // phi_t1 = 0;
//     // do {
//     //     this->unk_243E4[phi_t1].unk20 = 0x12C;
//     //     temp_t1 = (phi_t1 + 4) & 0xFFFF;
//     //     temp_a0 = &this->unk_243E4[phi_t1];
//     //     temp_a0->v.ob[0] = temp_a0->unk20;
//     //     temp_a0_2 = &this->unk_243E4[phi_t1];
//     //     temp_v1_2 = temp_a0_2->v.ob[0] + 0x10;
//     //     temp_a0_2->unk30 = temp_v1_2;
//     //     this->unk_243E4[phi_t1].unk10 = temp_v1_2;
//     //     this->unk_243E4[phi_t1].unk12 = 0;
//     //     temp_a0_3 = &this->unk_243E4[phi_t1];
//     //     temp_a0_3->v.ob[1] = temp_a0_3->unk12;
//     //     temp_a0_4 = &this->unk_243E4[phi_t1];
//     //     temp_v1_3 = temp_a0_4->v.ob[1] - 0x10;
//     //     temp_a0_4->unk32 = temp_v1_3;
//     //     this->unk_243E4[phi_t1].unk22 = temp_v1_3;
//     //     this->unk_243E4[phi_t1].unk34 = 0;
//     //     temp_a0_5 = &this->unk_243E4[phi_t1];
//     //     temp_a1 = temp_a0_5->unk34;
//     //     temp_a0_5->unk24 = temp_a1;
//     //     this->unk_243E4[phi_t1].unk14 = temp_a1;
//     //     this->unk_243E4[phi_t1].v.ob[2] = temp_a1;
//     //     this->unk_243E4[phi_t1].unk36 = 0;
//     //     temp_a0_6 = &this->unk_243E4[phi_t1];
//     //     temp_a1_2 = temp_a0_6->unk36;
//     //     temp_a0_6->unk26 = temp_a1_2;
//     //     this->unk_243E4[phi_t1].unk16 = temp_a1_2;
//     //     this->unk_243E4[phi_t1].v.flag = temp_a1_2;
//     //     this->unk_243E4[phi_t1].unk28 = 0;
//     //     temp_a0_7 = &this->unk_243E4[phi_t1];
//     //     temp_v1_4 = temp_a0_7->unk28;
//     //     temp_a0_7->unk1A = temp_v1_4;
//     //     this->unk_243E4[phi_t1].v.tc[1] = temp_v1_4;
//     //     this->unk_243E4[phi_t1].v.tc[0] = temp_v1_4;
//     //     this->unk_243E4[phi_t1].unk3A = 0x200;
//     //     temp_a0_8 = &this->unk_243E4[phi_t1];
//     //     temp_a1_3 = temp_a0_8->unk3A;
//     //     temp_a0_8->unk38 = temp_a1_3;
//     //     this->unk_243E4[phi_t1].unk2A = temp_a1_3;
//     //     this->unk_243E4[phi_t1].unk18 = temp_a1_3;
//     //     this->unk_243E4[phi_t1].unk3F = 0xFF;
//     //     temp_a0_9 = &this->unk_243E4[phi_t1];
//     //     temp_v1_5 = temp_a0_9->unk3F;
//     //     temp_a0_9->unk2F = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk1F = temp_v1_5;
//     //     this->unk_243E4[phi_t1].v.cn[3] = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk3E = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk2E = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk1E = temp_v1_5;
//     //     this->unk_243E4[phi_t1].v.cn[2] = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk3D = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk2D = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk1D = temp_v1_5;
//     //     this->unk_243E4[phi_t1].v.cn[1] = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk3C = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk2C = temp_v1_5;
//     //     this->unk_243E4[phi_t1].unk1C = temp_v1_5;
//     //     this->unk_243E4[phi_t1].v.cn[0] = temp_v1_5;
//     //     phi_t1 = temp_t1;
//     // } while (temp_t1 < 0x3C0);



//     this->unk_243E4[0].v.ob[0] = this->unk_243E4[2].v.ob[0] = this->unk_24508;
//     this->unk_243E4[1].v.ob[0] = this->unk_243E4[3].v.ob[0] = this->unk_243E4[0].v.ob[0] + 0x80;
//     this->unk_243E4[0].v.ob[1] = this->unk_243E4[1].v.ob[1] = 0x48;
//     this->unk_243E4[2].v.ob[1] = this->unk_243E4[3].v.ob[1] = this->unk_243E4[0].v.ob[1] - 0x10;
//     this->unk_243E4[1].v.tc[0] = this->unk_243E4[3].v.tc[0] = 0x1000;


// //     temp_v1_6 = this->unk_24508;
// //     this->unk_243E4->unk20 = temp_v1_6;
// //     this->unk_243E4->v.ob[0] = temp_v1_6;
// //     temp_a1_4 = this->unk_243E4;
// //     temp_v1_7 = temp_a1_4->v.ob[0] + 0x80;
// //     temp_a1_4->unk30 = temp_v1_7;
// //     this->unk_243E4->unk10 = temp_v1_7;
// //     this->unk_243E4->unk12 = 0x48;
// //     temp_a1_5 = this->unk_243E4;
// //     temp_a1_5->v.ob[1] = temp_a1_5->unk12;
// //     temp_a1_6 = this->unk_243E4;
// //     temp_v1_8 = temp_a1_6->v.ob[1] - 0x10;
// //     temp_a1_6->unk32 = temp_v1_8;
// //     this->unk_243E4->unk22 = temp_v1_8;
// //     this->unk_243E4->unk38 = 0x1000;
// //     temp_a1_7 = this->unk_243E4;
// //     temp_a1_7->unk18 = (s16) temp_a1_7->unk38;


//     for (phi_a3 = 0, phi_s3 = 4; phi_a3 < 3; phi_a3++) {
//         phi_s1 = this->unk_24508 - 6;

//         for (phi_s4 = 0; phi_s4 < 7; phi_s4++, phi_s3 += 4) {
//             this->unk_243E4[phi_s3].v.ob[0] = this->unk_243E4[phi_s3 + 2].v.ob[0] = phi_s1;
//             this->unk_243E4[phi_s3 + 1].v.ob[0] = this->unk_243E4[phi_s3 + 3].v.ob[0] =
//                 this->unk_243E4[phi_s3].v.ob[0] + D_80814538[phi_s4];

//             this->unk_243E4[phi_s3].v.ob[1] = this->unk_243E4[phi_s3 + 1].v.ob[1] =
//                 this->unk_24492[phi_a3] + 0x2C;

//             this->unk_243E4[phi_s3 + 2].v.ob[1] = this->unk_243E4[phi_s3 + 3].v.ob[1] =
//                 this->unk_243E4[phi_s3].v.ob[1] - 0x38;

//             this->unk_243E4[phi_s3 + 1].v.tc[0] = this->unk_243E4[phi_s3 + 3].v.tc[0] =
//                 D_80814538[phi_s4] << 5;
//             this->unk_243E4[phi_s3 + 2].v.tc[1] = this->unk_243E4[phi_s3 + 3].v.tc[1] = 0x700;
//             phi_s1 += D_80814538[phi_s4];
//         }
//     }


// //     phi_a3 = 0;
// //     phi_a3_2 = 0;
// //     phi_a3_3 = 0;
// //     phi_a3_5 = 0;
// //     phi_a3_6 = 0;
// //     phi_a3_7 = 0;
// //     phi_a3_8 = 0;
// //     phi_s3 = 4;
// //     do {
// //         phi_s1 = this->unk_24508 - 6;
// //         phi_s4 = 0;
// //         phi_s4_2 = 0;
// //         phi_s4_3 = 0;
// //         phi_s4_4 = 0;
// // loop_4:
// //         this->unk_243E4[phi_s3].unk20 = phi_s1;
// //         temp_a1_8 = &D_80814538 + (phi_s4 * 2);
// //         this->unk_243E4[phi_s3].v.ob[0] = phi_s1;
// //         temp_s4 = phi_s4 + 1;
// //         temp_a0_10 = &this->unk_243E4[phi_s3];
// //         temp_v1_9 = *temp_a1_8 + temp_a0_10->v.ob[0];
// //         temp_a0_10->unk30 = temp_v1_9;
// //         temp_s3 = (phi_s3 + 4) & 0xFFFF;
// //         this->unk_243E4[phi_s3].unk10 = temp_v1_9;
// //         temp_v1_10 = this->unk_24492[phi_a3] + 0x2C;
// //         this->unk_243E4[phi_s3].unk12 = temp_v1_10;
// //         this->unk_243E4[phi_s3].v.ob[1] = temp_v1_10;
// //         temp_a0_11 = &this->unk_243E4[phi_s3];
// //         temp_v1_11 = temp_a0_11->v.ob[1] - 0x38;
// //         temp_a0_11->unk32 = temp_v1_11;
// //         this->unk_243E4[phi_s3].unk22 = temp_v1_11;
// //         temp_v1_12 = *temp_a1_8 << 5;
// //         this->unk_243E4[phi_s3].unk38 = temp_v1_12;
// //         this->unk_243E4[phi_s3].unk18 = temp_v1_12;
// //         this->unk_243E4[phi_s3].unk3A = 0x700;
// //         temp_a0_12 = &this->unk_243E4[phi_s3];
// //         temp_a0_12->unk2A = (s16) temp_a0_12->unk3A;
// //         phi_s1 += *temp_a1_8;
// //         phi_s3 = temp_s3;
// //         phi_s4 = temp_s4;
// //         phi_s3_2 = temp_s3;
// //         phi_s3 = temp_s3;
// //         if ((s32) temp_s4 < 7) {
// //             goto loop_4;
// //         }
// //         temp_a3 = phi_a3 + 1;
// //         phi_a3 = temp_a3;
// //     } while ((s32) temp_a3 < 3);


    
//     temp_s1 = this->unk_24508 - 6;
// //     temp_a1_9 = temp_s1 + 0x40;
// //     temp_a2 = temp_s1 + 0x34;
// //     temp_a3_2 = temp_s1 + 0xA9;
//     phi_t0 = 0x2C;

//     for (phi_s4_2 = 0; phi_s4_2 < 3; phi_s4_2++, phi_t0 -= 0x20) {

//     }

// //     do {
// //         this->unk_243E4[phi_s3_2].unk20 = temp_s1;
// //         temp_s3_2 = (phi_s3_2 + 0x10) & 0xFFFF;
// //         this->unk_243E4[phi_s3_2].v.ob[0] = temp_s1;
// //         temp_a0_13 = &this->unk_243E4[phi_s3_2];
// //         temp_s4_2 = phi_s4_2 + 1;
// //         temp_v1_13 = temp_a0_13->v.ob[0] + 0x40;
// //         temp_a0_13->unk30 = temp_v1_13;
// //         this->unk_243E4[phi_s3_2].unk10 = temp_v1_13;
// //         temp_v1_14 = this->unk_2449A[phi_s4_2] + phi_t0;
// //         this->unk_243E4[phi_s3_2].unk12 = temp_v1_14;
// //         this->unk_243E4[phi_s3_2].v.ob[1] = temp_v1_14;
// //         temp_a0_14 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_15 = temp_a0_14->v.ob[1] - 0x10;
// //         temp_a0_14->unk32 = temp_v1_15;
// //         this->unk_243E4[phi_s3_2].unk22 = temp_v1_15;
// //         this->unk_243E4[phi_s3_2].unk38 = 0x800;
// //         temp_a0_15 = &this->unk_243E4[phi_s3_2];
// //         temp_a0_15->unk18 = (s16) temp_a0_15->unk38;
// //         this->unk_243E4[phi_s3_2].unk60 = temp_a1_9;
// //         this->unk_243E4[phi_s3_2].unk40 = temp_a1_9;
// //         temp_a0_16 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_16 = temp_a0_16->unk40 + 0x6C;
// //         temp_a0_16->unk70 = temp_v1_16;
// //         this->unk_243E4[phi_s3_2].unk50 = temp_v1_16;
// //         temp_v1_17 = this->unk_2449A[phi_s4_2] + phi_t0;
// //         this->unk_243E4[phi_s3_2].unk52 = temp_v1_17;
// //         this->unk_243E4[phi_s3_2].unk42 = temp_v1_17;
// //         temp_a0_17 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_18 = temp_a0_17->unk42 - 0x10;
// //         temp_a0_17->unk72 = temp_v1_18;
// //         this->unk_243E4[phi_s3_2].unk62 = temp_v1_18;
// //         this->unk_243E4[phi_s3_2].unk78 = 0xD80;
// //         temp_a0_18 = &this->unk_243E4[phi_s3_2];
// //         temp_a0_18->unk58 = (s16) temp_a0_18->unk78;
// //         this->unk_243E4[phi_s3_2].unkA0 = temp_a2;
// //         this->unk_243E4[phi_s3_2].unk80 = temp_a2;
// //         temp_a0_19 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_19 = temp_a0_19->unk80 + 0x18;
// //         temp_a0_19->unkB0 = temp_v1_19;
// //         this->unk_243E4[phi_s3_2].unk90 = temp_v1_19;
// //         temp_v1_20 = this->unk_2449A[phi_s4_2] + phi_t0;
// //         this->unk_243E4[phi_s3_2].unk92 = temp_v1_20;
// //         this->unk_243E4[phi_s3_2].unk82 = temp_v1_20;
// //         temp_a0_20 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_21 = temp_a0_20->unk82 - 0x10;
// //         temp_a0_20->unkB2 = temp_v1_21;
// //         this->unk_243E4[phi_s3_2].unkA2 = temp_v1_21;
// //         this->unk_243E4[phi_s3_2].unkB8 = 0x300;
// //         temp_a0_21 = &this->unk_243E4[phi_s3_2];
// //         temp_a0_21->unk98 = (s16) temp_a0_21->unkB8;
// //         this->unk_243E4[phi_s3_2].unkE0 = temp_a3_2;
// //         this->unk_243E4[phi_s3_2].unkC0 = temp_a3_2;
// //         temp_a0_22 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_22 = temp_a0_22->unkC0 + 0x34;
// //         temp_a0_22->unkF0 = temp_v1_22;
// //         this->unk_243E4[phi_s3_2].unkD0 = temp_v1_22;
// //         temp_v1_23 = this->unk_2449A[phi_s4_2] + phi_t0;
// //         this->unk_243E4[phi_s3_2].unkD2 = temp_v1_23;
// //         this->unk_243E4[phi_s3_2].unkC2 = temp_v1_23;
// //         temp_a0_23 = &this->unk_243E4[phi_s3_2];
// //         temp_v1_24 = temp_a0_23->unkC2 - 0x10;
// //         temp_a0_23->unkF2 = temp_v1_24;
// //         this->unk_243E4[phi_s3_2].unkE2 = temp_v1_24;
// //         this->unk_243E4[phi_s3_2].unkF8 = 0x680;
// //         temp_a0_24 = &this->unk_243E4[phi_s3_2];
// //         temp_a0_24->unkD8 = (s16) temp_a0_24->unkF8;
// //         phi_s3_2 = temp_s3_2;
// //         phi_s4_2 = temp_s4_2;
// //         phi_t0 += -0x10;
// //         phi_s3_11 = temp_s3_2;
// //     } while ((s32) temp_s4_2 < 3);




// //     sp9C = 0x2C;

// //     do {
// //         phi_s3_3 = phi_s3_11;
// //         phi_s3_12 = phi_s3_11;
// //         if (gSaveContext.unk_3F3F != 0) {
// //             spAC = phi_s4_3;
// //             if ((this + phi_s4_3)->unk2446A != 0) {
// //                 spAC = phi_s4_3 + 2;
// //             }
// //             temp_v0_2 = this->unk_24486;
// //             phi_s1_2 = this->unk_24508 - 6;
// //             if ((temp_v0_2 == 0x10) && (phi_s6 = this + (phi_s4_3 * 2) + 0x20000, (phi_s4_3 == this->unk_244A6))) {
// //                 sp98 = this->unk_24492[phi_s4_3] + 0x2C;
// //             } else if (((temp_v0_2 == 0x11) || (temp_v0_2 == 0x12)) && (phi_s6 = this + (phi_s4_3 * 2) + 0x20000, (phi_s4_3 == this->unk_244A6))) {
// //                 sp98 = this->unk_2449A[phi_s4_3] + sp9C;
// //             } else {
// //                 sp98 = this->unk_24492[phi_s4_3] + sp9C + this->unk_2449A[phi_s4_3];
// //                 phi_s6 = this + (phi_s4_3 * 2) + 0x20000;
// //             }
// //             temp_t2 = sp98 - 2;
// //             temp_a2_2 = temp_t2 - 1;
// //             do {
// //                 temp_a1_10 = &D_80814280 + ((this + (phi_s4_3 * 8) + phi_a3_2)->unk24414 * 2);
// //                 temp_a3_3 = phi_a3_2 + 1;
// //                 temp_v1_25 = *temp_a1_10 + phi_s1_2 + 0x4E;
// //                 this->unk_243E4[phi_s3_3].unk20 = temp_v1_25;
// //                 this->unk_243E4[phi_s3_3].v.ob[0] = temp_v1_25;
// //                 temp_a0_25 = &this->unk_243E4[phi_s3_3];
// //                 temp_s3_3 = (phi_s3_3 + 4) & 0xFFFF;
// //                 temp_v1_26 = temp_a0_25->v.ob[0] + 0xB;
// //                 temp_a0_25->unk30 = temp_v1_26;
// //                 this->unk_243E4[phi_s3_3].unk10 = temp_v1_26;
// //                 this->unk_243E4[phi_s3_3].unk12 = temp_t2;
// //                 this->unk_243E4[phi_s3_3].v.ob[1] = temp_t2;
// //                 temp_a0_26 = &this->unk_243E4[phi_s3_3];
// //                 temp_v1_27 = temp_a0_26->v.ob[1] - 0xC;
// //                 temp_a0_26->unk32 = temp_v1_27;
// //                 this->unk_243E4[phi_s3_3].unk22 = temp_v1_27;
// //                 temp_v1_28 = *temp_a1_10 + phi_s1_2 + 0x4F;
// //                 this->unk_243E4[phi_s3_3].unk220 = temp_v1_28;
// //                 this->unk_243E4[phi_s3_3].unk200 = temp_v1_28;
// //                 temp_a0_27 = &this->unk_243E4[phi_s3_3];
// //                 temp_v1_29 = temp_a0_27->unk200 + 0xB;
// //                 temp_a0_27->unk230 = temp_v1_29;
// //                 this->unk_243E4[phi_s3_3].unk210 = temp_v1_29;
// //                 this->unk_243E4[phi_s3_3].unk212 = temp_a2_2;
// //                 this->unk_243E4[phi_s3_3].unk202 = temp_a2_2;
// //                 temp_a0_28 = &this->unk_243E4[phi_s3_3];
// //                 temp_v1_30 = temp_a0_28->unk202 - 0xC;
// //                 temp_a0_28->unk232 = temp_v1_30;
// //                 this->unk_243E4[phi_s3_3].unk222 = temp_v1_30;
// //                 phi_a3_2 = temp_a3_3;
// //                 phi_s1_2 += 0xA;
// //                 phi_s3_3 = temp_s3_3;
// //             } while ((s32) temp_a3_3 < 8);
// //             temp_s1_2 = this->unk_24508 + 0xE;
// //             func_8080C228((u16) this->rupees[spAC], &spA4, &spA6, &spA8);
// //             temp_t3 = sp98 - 0x18;
// //             temp_t4 = temp_t3 - 1;
// //             sp50 = this + spAC + 0x20000;
// //             phi_t2 = &(&spA4)[*(&D_80814554 + (this->unk_24474[spAC] * 2))];
// //             phi_s1_3 = temp_s1_2;
// //             phi_s3_4 = (temp_s3_3 + 0x20) & 0xFFFF;
// //             do {
// //                 temp_a1_11 = phi_a3_3 * 2;
// //                 temp_t0 = &D_80814628 + temp_a1_11;
// //                 temp_v1_31 = *(&D_80814280 + (*phi_t2 * 2)) + phi_s1_3;
// //                 this->unk_243E4[phi_s3_4].unk20 = temp_v1_31;
// //                 temp_a2_3 = &D_80814630 + temp_a1_11;
// //                 temp_a3_4 = phi_a3_3 + 1;
// //                 this->unk_243E4[phi_s3_4].v.ob[0] = temp_v1_31;
// //                 temp_a0_29 = &this->unk_243E4[phi_s3_4];
// //                 temp_v1_32 = *temp_t0 + temp_a0_29->v.ob[0];
// //                 temp_a0_29->unk30 = temp_v1_32;
// //                 temp_s3_4 = (phi_s3_4 + 4) & 0xFFFF;
// //                 this->unk_243E4[phi_s3_4].unk10 = temp_v1_32;
// //                 this->unk_243E4[phi_s3_4].unk12 = temp_t3;
// //                 this->unk_243E4[phi_s3_4].v.ob[1] = temp_t3;
// //                 temp_a0_30 = &this->unk_243E4[phi_s3_4];
// //                 temp_v1_33 = temp_a0_30->v.ob[1] - *temp_a2_3;
// //                 temp_a0_30->unk32 = temp_v1_33;
// //                 this->unk_243E4[phi_s3_4].unk22 = temp_v1_33;
// //                 temp_a0_31 = &this->unk_243E4[phi_s3_4];
// //                 temp_v1_34 = temp_a0_31->v.ob[0] + 1;
// //                 temp_a0_31->unkE0 = temp_v1_34;
// //                 this->unk_243E4[phi_s3_4].unkC0 = temp_v1_34;
// //                 temp_a0_32 = &this->unk_243E4[phi_s3_4];
// //                 temp_v1_35 = *temp_t0 + temp_a0_32->unkC0;
// //                 temp_a0_32->unkF0 = temp_v1_35;
// //                 this->unk_243E4[phi_s3_4].unkD0 = temp_v1_35;
// //                 this->unk_243E4[phi_s3_4].unkD2 = temp_t4;
// //                 this->unk_243E4[phi_s3_4].unkC2 = temp_t4;
// //                 temp_a0_33 = &this->unk_243E4[phi_s3_4];
// //                 temp_v1_36 = temp_a0_33->unkC2 - *temp_a2_3;
// //                 temp_a0_33->unkF2 = temp_v1_36;
// //                 this->unk_243E4[phi_s3_4].unkE2 = temp_v1_36;
// //                 phi_t2 += 2;
// //                 phi_s1_3 += *(&D_80814620 + temp_a1_11);
// //                 phi_s3_4 = temp_s3_4;
// //                 phi_a3_3 = temp_a3_4;
// //             } while ((s32) temp_a3_4 < 3);
// //             temp_s1_3 = this->unk_24508 + 0x2A;
// //             func_8080C228((u16) this->unk_24478[spAC], &spA4, &spA6, &spA8);
// //             temp_t2_2 = sp98 - 0x2A;
// //             temp_t3_2 = temp_t2_2 - 1;
// //             phi_a3_4 = 1;
// //             phi_s1_4 = temp_s1_3;
// //             phi_s3_5 = (temp_s3_4 + 0xC) & 0xFFFF;
// //             do {
// //                 temp_a1_12 = phi_a3_4 * 2;
// //                 temp_t0_2 = &D_80814628 + temp_a1_12;
// //                 temp_a2_4 = &D_80814630 + temp_a1_12;
// //                 temp_v1_37 = *(&D_80814280 + ((sp + temp_a1_12)->unkA4 * 2)) + phi_s1_4;
// //                 this->unk_243E4[phi_s3_5].unk20 = temp_v1_37;
// //                 temp_a3_5 = phi_a3_4 + 1;
// //                 this->unk_243E4[phi_s3_5].v.ob[0] = temp_v1_37;
// //                 temp_a0_34 = &this->unk_243E4[phi_s3_5];
// //                 temp_v1_38 = *temp_t0_2 + temp_a0_34->v.ob[0];
// //                 temp_a0_34->unk30 = temp_v1_38;
// //                 temp_s3_5 = (phi_s3_5 + 4) & 0xFFFF;
// //                 this->unk_243E4[phi_s3_5].unk10 = temp_v1_38;
// //                 this->unk_243E4[phi_s3_5].unk12 = temp_t2_2;
// //                 this->unk_243E4[phi_s3_5].v.ob[1] = temp_t2_2;
// //                 temp_a0_35 = &this->unk_243E4[phi_s3_5];
// //                 temp_v1_39 = temp_a0_35->v.ob[1] - *temp_a2_4;
// //                 temp_a0_35->unk32 = temp_v1_39;
// //                 this->unk_243E4[phi_s3_5].unk22 = temp_v1_39;
// //                 temp_a0_36 = &this->unk_243E4[phi_s3_5];
// //                 temp_v1_40 = temp_a0_36->v.ob[0] + 1;
// //                 temp_a0_36->unkA0 = temp_v1_40;
// //                 this->unk_243E4[phi_s3_5].unk80 = temp_v1_40;
// //                 temp_a0_37 = &this->unk_243E4[phi_s3_5];
// //                 temp_v1_41 = *temp_t0_2 + temp_a0_37->unk80;
// //                 temp_a0_37->unkB0 = temp_v1_41;
// //                 this->unk_243E4[phi_s3_5].unk90 = temp_v1_41;
// //                 this->unk_243E4[phi_s3_5].unk92 = temp_t3_2;
// //                 this->unk_243E4[phi_s3_5].unk82 = temp_t3_2;
// //                 temp_a0_38 = &this->unk_243E4[phi_s3_5];
// //                 temp_v1_42 = temp_a0_38->unk82 - *temp_a2_4;
// //                 temp_a0_38->unkB2 = temp_v1_42;
// //                 this->unk_243E4[phi_s3_5].unkA2 = temp_v1_42;
// //                 phi_a3_4 = temp_a3_5;
// //                 phi_s1_4 += *(&D_80814620 + temp_a1_12);
// //                 phi_s3_5 = temp_s3_5;
// //             } while ((s32) temp_a3_5 < 3);
// //             phi_s1_5 = this->unk_24508 + 0x3F;
// //             phi_s3_6 = (temp_s3_5 + 8) & 0xFFFF;
// //             phi_t0_2 = sp98 - 0x10;
// //             do {
// //                 this->unk_243E4[phi_s3_6].unk20 = phi_s1_5;
// //                 this->unk_243E4[phi_s3_6].v.ob[0] = phi_s1_5;
// //                 temp_s3_6 = (phi_s3_6 + 4) & 0xFFFF;
// //                 temp_a0_39 = &this->unk_243E4[phi_s3_6];
// //                 temp_v1_43 = temp_a0_39->v.ob[0] + 0xA;
// //                 temp_a0_39->unk30 = temp_v1_43;
// //                 this->unk_243E4[phi_s3_6].unk10 = temp_v1_43;
// //                 this->unk_243E4[phi_s3_6].unk12 = phi_t0_2;
// //                 this->unk_243E4[phi_s3_6].v.ob[1] = phi_t0_2;
// //                 temp_a0_40 = &this->unk_243E4[phi_s3_6];
// //                 temp_v1_44 = temp_a0_40->v.ob[1] - 0xA;
// //                 temp_a0_40->unk32 = temp_v1_44;
// //                 this->unk_243E4[phi_s3_6].unk22 = temp_v1_44;
// //                 phi_s3_6 = temp_s3_6;
// //                 phi_s3_7 = temp_s3_6;
// //                 phi_s1_8 = phi_s1_5;
// //                 if (phi_a3_5 == 9) {
// //                     phi_s1_8 = this->unk_24508 + 0x36;
// //                     phi_t0_2 += -8;
// //                 }
// //                 temp_a3_6 = phi_a3_5 + 1;
// //                 phi_s1_5 = phi_s1_8 + 9;
// //                 phi_a3_5 = temp_a3_6;
// //             } while ((s32) temp_a3_6 < 0x14);
// //             temp_a2_5 = sp98 - 0x20;
// //             phi_s1_6 = this->unk_24508 + 0x40;
// //             do {
// //                 temp_a3_7 = phi_a3_6 + 1;
// //                 this->unk_243E4[phi_s3_7].unk20 = phi_s1_6;
// //                 this->unk_243E4[phi_s3_7].v.ob[0] = phi_s1_6;
// //                 temp_a0_41 = &this->unk_243E4[phi_s3_7];
// //                 temp_s3_7 = (phi_s3_7 + 4) & 0xFFFF;
// //                 temp_v1_45 = temp_a0_41->v.ob[0] + 0x14;
// //                 temp_a0_41->unk30 = temp_v1_45;
// //                 this->unk_243E4[phi_s3_7].unk10 = temp_v1_45;
// //                 this->unk_243E4[phi_s3_7].unk12 = temp_a2_5;
// //                 this->unk_243E4[phi_s3_7].v.ob[1] = temp_a2_5;
// //                 temp_a0_42 = &this->unk_243E4[phi_s3_7];
// //                 temp_v1_46 = temp_a0_42->v.ob[1] - 0x14;
// //                 temp_a0_42->unk32 = temp_v1_46;
// //                 this->unk_243E4[phi_s3_7].unk22 = temp_v1_46;
// //                 this->unk_243E4[phi_s3_7].unk3A = 0x400;
// //                 temp_a0_43 = &this->unk_243E4[phi_s3_7];
// //                 temp_a1_13 = temp_a0_43->unk3A;
// //                 temp_a0_43->unk38 = temp_a1_13;
// //                 this->unk_243E4[phi_s3_7].unk2A = temp_a1_13;
// //                 this->unk_243E4[phi_s3_7].unk18 = temp_a1_13;
// //                 phi_s1_6 += 0x18;
// //                 phi_s3_7 = temp_s3_7;
// //                 phi_a3_6 = temp_a3_7;
// //             } while ((s32) temp_a3_7 < 4);
// //             temp_v1_47 = this->unk_24508 - 1;
// //             this->unk_243E4[temp_s3_7].unk20 = temp_v1_47;
// //             this->unk_243E4[temp_s3_7].v.ob[0] = temp_v1_47;
// //             temp_s3_8 = (temp_s3_7 + 4) & 0xFFFF;
// //             temp_a0_44 = &this->unk_243E4[temp_s3_7];
// //             temp_v1_48 = temp_a0_44->v.ob[0] + 0x10;
// //             temp_a0_44->unk30 = temp_v1_48;
// //             this->unk_243E4[temp_s3_7].unk10 = temp_v1_48;
// //             temp_a1_14 = sp98 - 0x15;
// //             this->unk_243E4[temp_s3_7].unk12 = temp_a1_14;
// //             this->unk_243E4[temp_s3_7].v.ob[1] = temp_a1_14;
// //             temp_a0_45 = &this->unk_243E4[temp_s3_7];
// //             temp_v1_49 = temp_a0_45->v.ob[1] - 0x10;
// //             temp_a0_45->unk32 = temp_v1_49;
// //             this->unk_243E4[temp_s3_7].unk22 = temp_v1_49;
// //             this->unk_243E4[temp_s3_7].unk38 = 0x200;
// //             temp_a0_46 = &this->unk_243E4[temp_s3_7];
// //             temp_a0_46->unk18 = (s16) temp_a0_46->unk38;
// //             this->unk_243E4[temp_s3_7].unk3A = 0x200;
// //             temp_a0_47 = &this->unk_243E4[temp_s3_7];
// //             temp_a0_47->unk2A = (s16) temp_a0_47->unk3A;
// //             temp_s3_9 = (temp_s3_8 + 4) & 0xFFFF;
// //             temp_v1_50 = this->unk_24508 + 0x27;
// //             this->unk_243E4[temp_s3_8].unk20 = temp_v1_50;
// //             this->unk_243E4[temp_s3_8].v.ob[0] = temp_v1_50;
// //             temp_a0_48 = &this->unk_243E4[temp_s3_8];
// //             temp_v1_51 = temp_a0_48->v.ob[0] + 0x18;
// //             temp_a0_48->unk30 = temp_v1_51;
// //             this->unk_243E4[temp_s3_8].unk10 = temp_v1_51;
// //             this->unk_243E4[temp_s3_8].unk12 = temp_a1_14;
// //             this->unk_243E4[temp_s3_8].v.ob[1] = temp_a1_14;
// //             temp_a0_49 = &this->unk_243E4[temp_s3_8];
// //             temp_v1_52 = temp_a0_49->v.ob[1] - 0x10;
// //             temp_a0_49->unk32 = temp_v1_52;
// //             this->unk_243E4[temp_s3_8].unk22 = temp_v1_52;
// //             this->unk_243E4[temp_s3_8].unk38 = 0x300;
// //             temp_a0_50 = &this->unk_243E4[temp_s3_8];
// //             temp_a0_50->unk18 = (s16) temp_a0_50->unk38;
// //             this->unk_243E4[temp_s3_8].unk3A = 0x200;
// //             temp_a0_51 = &this->unk_243E4[temp_s3_8];
// //             temp_a0_51->unk2A = (s16) temp_a0_51->unk3A;
// //             temp_s3_10 = (temp_s3_9 + 8) & 0xFFFF;
// //             temp_v1_53 = this->unk_24508 - 0xA;
// //             this->unk_243E4[temp_s3_9].unk20 = temp_v1_53;
// //             this->unk_243E4[temp_s3_9].v.ob[0] = temp_v1_53;
// //             temp_a0_52 = &this->unk_243E4[temp_s3_9];
// //             temp_v1_54 = temp_a0_52->v.ob[0] + 0x40;
// //             temp_a0_52->unk30 = temp_v1_54;
// //             this->unk_243E4[temp_s3_9].unk10 = temp_v1_54;
// //             temp_a2_6 = sp98 - 0x27;
// //             this->unk_243E4[temp_s3_9].unk12 = temp_a2_6;
// //             temp_a1_15 = temp_a2_6 - 1;
// //             this->unk_243E4[temp_s3_9].v.ob[1] = temp_a2_6;
// //             temp_a0_53 = &this->unk_243E4[temp_s3_9];
// //             temp_v1_55 = temp_a0_53->v.ob[1] - 0x10;
// //             temp_a0_53->unk32 = temp_v1_55;
// //             this->unk_243E4[temp_s3_9].unk22 = temp_v1_55;
// //             this->unk_243E4[temp_s3_9].unk38 = 0x800;
// //             temp_a0_54 = &this->unk_243E4[temp_s3_9];
// //             temp_a0_54->unk18 = (s16) temp_a0_54->unk38;
// //             this->unk_243E4[temp_s3_9].unk3A = 0x200;
// //             temp_a0_55 = &this->unk_243E4[temp_s3_9];
// //             temp_a0_55->unk2A = (s16) temp_a0_55->unk3A;
// //             temp_a0_56 = &this->unk_243E4[temp_s3_9];
// //             temp_v1_56 = temp_a0_56->v.ob[0] + 1;
// //             temp_a0_56->unk60 = temp_v1_56;
// //             this->unk_243E4[temp_s3_9].unk40 = temp_v1_56;
// //             temp_a0_57 = &this->unk_243E4[temp_s3_9];
// //             temp_v1_57 = temp_a0_57->unk40 + 0x40;
// //             temp_a0_57->unk70 = temp_v1_57;
// //             this->unk_243E4[temp_s3_9].unk50 = temp_v1_57;
// //             this->unk_243E4[temp_s3_9].unk52 = temp_a1_15;
// //             this->unk_243E4[temp_s3_9].unk42 = temp_a1_15;
// //             temp_a0_58 = &this->unk_243E4[temp_s3_9];
// //             temp_v1_58 = temp_a0_58->unk42 - 0x10;
// //             temp_a0_58->unk72 = temp_v1_58;
// //             this->unk_243E4[temp_s3_9].unk62 = temp_v1_58;
// //             this->unk_243E4[temp_s3_9].unk78 = 0x800;
// //             temp_a0_59 = &this->unk_243E4[temp_s3_9];
// //             temp_a0_59->unk58 = (s16) temp_a0_59->unk78;
// //             this->unk_243E4[temp_s3_9].unk7A = 0x200;
// //             temp_a0_60 = &this->unk_243E4[temp_s3_9];
// //             temp_a0_60->unk6A = (s16) temp_a0_60->unk7A;
// //             temp_v0_3 = this->unk_24486;
// //             temp_s1_4 = this->unk_24508 + 0xA3;
// //             if ((temp_v0_3 == 0x10) && (phi_s4_3 == this->unk_244A6)) {
// //                 phi_t0_3 = phi_s6->unk4492 + 0x2C;
// //             } else {
// //                 if (((temp_v0_3 == 0x11) || (temp_v0_3 == 0x12)) && (phi_t9 = sp9C, (phi_s4_3 == this->unk_244A6))) {
// //                     phi_t6 = phi_s6->unk449A;
// //                 } else {
// //                     phi_t6 = phi_s6->unk4492 + sp9C;
// //                     phi_t9 = (s32) phi_s6->unk449A;
// //                 }
// //                 phi_t0_3 = phi_t6 + phi_t9;
// //             }
// //             temp_a1_16 = temp_s1_4 + 0xE;
// //             this->unk_243E4[temp_s3_10].unk20 = temp_a1_16;
// //             temp_a2_7 = phi_t0_3 - 2;
// //             temp_t3_3 = phi_t0_3 - 0x2B;
// //             this->unk_243E4[temp_s3_10].v.ob[0] = temp_a1_16;
// //             temp_a0_61 = &this->unk_243E4[temp_s3_10];
// //             temp_v1_59 = temp_a0_61->v.ob[0] + 0x18;
// //             temp_a0_61->unk30 = temp_v1_59;
// //             this->unk_243E4[temp_s3_10].unk10 = temp_v1_59;
// //             this->unk_243E4[temp_s3_10].unk12 = temp_a2_7;
// //             this->unk_243E4[temp_s3_10].v.ob[1] = temp_a2_7;
// //             temp_a0_62 = &this->unk_243E4[temp_s3_10];
// //             temp_v1_60 = temp_a0_62->v.ob[1] - 0xC;
// //             temp_a0_62->unk32 = temp_v1_60;
// //             this->unk_243E4[temp_s3_10].unk22 = temp_v1_60;
// //             this->unk_243E4[temp_s3_10].unk38 = 0x300;
// //             temp_a0_63 = &this->unk_243E4[temp_s3_10];
// //             temp_a0_63->unk18 = (s16) temp_a0_63->unk38;
// //             this->unk_243E4[temp_s3_10].unk3A = 0x180;
// //             temp_a0_64 = &this->unk_243E4[temp_s3_10];
// //             temp_a0_64->unk2A = (s16) temp_a0_64->unk3A;
// //             phi_s3_8 = (temp_s3_10 + 4) & 0xFFFF;
// //             do {
// //                 temp_a1_17 = temp_s1_4 + phi_a3_7 + 2;
// //                 this->unk_243E4[phi_s3_8].unk20 = temp_a1_17;
// //                 temp_a2_8 = (phi_t0_3 - phi_a3_7) - 0x12;
// //                 this->unk_243E4[phi_s3_8].v.ob[0] = temp_a1_17;
// //                 temp_a3_8 = phi_a3_7 + 1;
// //                 temp_a0_65 = &this->unk_243E4[phi_s3_8];
// //                 temp_v1_61 = temp_a0_65->v.ob[0] + 0x30;
// //                 temp_a0_65->unk30 = temp_v1_61;
// //                 temp_s3_11 = (phi_s3_8 + 4) & 0xFFFF;
// //                 this->unk_243E4[phi_s3_8].unk10 = temp_v1_61;
// //                 this->unk_243E4[phi_s3_8].unk12 = temp_a2_8;
// //                 this->unk_243E4[phi_s3_8].v.ob[1] = temp_a2_8;
// //                 temp_a0_66 = &this->unk_243E4[phi_s3_8];
// //                 temp_v1_62 = temp_a0_66->v.ob[1] - 0x18;
// //                 temp_a0_66->unk32 = temp_v1_62;
// //                 this->unk_243E4[phi_s3_8].unk22 = temp_v1_62;
// //                 this->unk_243E4[phi_s3_8].unk38 = 0x600;
// //                 temp_a0_67 = &this->unk_243E4[phi_s3_8];
// //                 temp_a0_67->unk18 = (s16) temp_a0_67->unk38;
// //                 this->unk_243E4[phi_s3_8].unk3A = 0x300;
// //                 temp_a0_68 = &this->unk_243E4[phi_s3_8];
// //                 temp_a0_68->unk2A = (s16) temp_a0_68->unk3A;
// //                 phi_a3_7 = temp_a3_8;
// //                 phi_s3_8 = temp_s3_11;
// //                 phi_s3_9 = temp_s3_11;
// //             } while ((s32) temp_a3_8 < 2);
// //             temp_a2_9 = phi_t0_3 - 0x2A;
// //             phi_s1_7 = temp_s1_4 + 6;
// //             do {
// //                 temp_a1_18 = phi_s1_7 + 1;
// //                 this->unk_243E4[phi_s3_9].unk20 = phi_s1_7;
// //                 temp_a3_9 = phi_a3_8 + 1;
// //                 this->unk_243E4[phi_s3_9].v.ob[0] = phi_s1_7;
// //                 temp_a0_69 = &this->unk_243E4[phi_s3_9];
// //                 temp_s3_12 = (phi_s3_9 + 4) & 0xFFFF;
// //                 temp_v1_63 = temp_a0_69->v.ob[0] + 0xC;
// //                 temp_a0_69->unk30 = temp_v1_63;
// //                 this->unk_243E4[phi_s3_9].unk10 = temp_v1_63;
// //                 this->unk_243E4[phi_s3_9].unk12 = temp_a2_9;
// //                 this->unk_243E4[phi_s3_9].v.ob[1] = temp_a2_9;
// //                 temp_a0_70 = &this->unk_243E4[phi_s3_9];
// //                 temp_v1_64 = temp_a0_70->v.ob[1] - 0xC;
// //                 temp_a0_70->unk32 = temp_v1_64;
// //                 this->unk_243E4[phi_s3_9].unk22 = temp_v1_64;
// //                 this->unk_243E4[phi_s3_9].unk160 = temp_a1_18;
// //                 this->unk_243E4[phi_s3_9].unk140 = temp_a1_18;
// //                 temp_a0_71 = &this->unk_243E4[phi_s3_9];
// //                 temp_v1_65 = temp_a0_71->unk140 + 0xC;
// //                 temp_a0_71->unk170 = temp_v1_65;
// //                 this->unk_243E4[phi_s3_9].unk150 = temp_v1_65;
// //                 this->unk_243E4[phi_s3_9].unk152 = temp_t3_3;
// //                 this->unk_243E4[phi_s3_9].unk142 = temp_t3_3;
// //                 temp_a0_72 = &this->unk_243E4[phi_s3_9];
// //                 temp_v1_66 = temp_a0_72->unk142 - 0xC;
// //                 temp_a0_72->unk172 = temp_v1_66;
// //                 this->unk_243E4[phi_s3_9].unk162 = temp_v1_66;
// //                 phi_s1_7 += 8;
// //                 phi_s3_9 = temp_s3_12;
// //                 phi_a3_8 = temp_a3_9;
// //             } while ((s32) temp_a3_9 < 5);
// //             temp_v0_4 = &this->unk_243E4[temp_s3_11];
// //             temp_v1_67 = temp_v0_4->unk80 + 3;
// //             temp_v0_4->unkA0 = temp_v1_67;
// //             this->unk_243E4[temp_s3_11].unk80 = temp_v1_67;
// //             temp_v0_5 = &this->unk_243E4[temp_s3_11];
// //             temp_v1_68 = temp_v0_5->unk80 + 0xC;
// //             temp_v0_5->unkB0 = temp_v1_68;
// //             this->unk_243E4[temp_s3_11].unk90 = temp_v1_68;
// //             temp_v0_6 = &this->unk_243E4[temp_s3_11];
// //             temp_v1_69 = temp_v0_6->unk80 + 1;
// //             temp_v0_6->unk1E0 = temp_v1_69;
// //             this->unk_243E4[temp_s3_11].unk1C0 = temp_v1_69;
// //             temp_v0_7 = &this->unk_243E4[temp_s3_11];
// //             temp_v1_70 = temp_v0_7->unk1C0 + 0xC;
// //             temp_v0_7->unk1F0 = temp_v1_70;
// //             this->unk_243E4[temp_s3_11].unk1D0 = temp_v1_70;
// //             phi_s3_12 = (temp_s3_12 + 0x14) & 0xFFFF;
// //         }
// //         temp_s4_3 = phi_s4_3 + 1;
// //         sp9C += -0x10;
// //         phi_s4_3 = temp_s4_3;
// //         phi_s3_10 = phi_s3_12;
// //         phi_s3_11 = phi_s3_12;
// //     } while ((s32) temp_s4_3 < 3);




// //     temp_s1_5 = this->unk_24508 - 6;
// //     phi_a1 = -0xC;



// //     do {
// //         this->unk_243E4[phi_s3_10].unk20 = temp_s1_5;
// //         temp_s3_13 = (phi_s3_10 + 4) & 0xFFFF;
// //         this->unk_243E4[phi_s3_10].v.ob[0] = temp_s1_5;
// //         temp_s4_4 = phi_s4_4 + 1;
// //         temp_a0_73 = &this->unk_243E4[phi_s3_10];
// //         temp_v1_71 = temp_a0_73->v.ob[0] + 0x40;
// //         temp_a0_73->unk30 = temp_v1_71;
// //         this->unk_243E4[phi_s3_10].unk10 = temp_v1_71;
// //         temp_v1_72 = (this + (phi_s4_4 * 2))->unk244A0 + phi_a1;
// //         this->unk_243E4[phi_s3_10].unk12 = temp_v1_72;
// //         this->unk_243E4[phi_s3_10].v.ob[1] = temp_v1_72;
// //         temp_a0_74 = &this->unk_243E4[phi_s3_10];
// //         temp_v1_73 = temp_a0_74->v.ob[1] - 0x10;
// //         temp_a0_74->unk32 = temp_v1_73;
// //         this->unk_243E4[phi_s3_10].unk22 = temp_v1_73;
// //         this->unk_243E4[phi_s3_10].unk38 = 0x800;
// //         temp_a0_75 = &this->unk_243E4[phi_s3_10];
// //         temp_a0_75->unk18 = (s16) temp_a0_75->unk38;
// //         phi_s3_10 = temp_s3_13;
// //         phi_s4_4 = temp_s4_4;
// //         phi_a1 += -0x10;
// //     } while ((s32) temp_s4_4 < 2);



// //     this->unk_243E4[temp_s3_13].unk20 = temp_s1_5;
// //     temp_s3_14 = (temp_s3_13 + 4) & 0xFFFF;
// //     this->unk_243E4[temp_s3_13].v.ob[0] = temp_s1_5;
// //     temp_a0_76 = &this->unk_243E4[temp_s3_13];
// //     temp_v1_74 = temp_a0_76->v.ob[0] + 0x40;
// //     temp_a0_76->unk30 = temp_v1_74;
// //     this->unk_243E4[temp_s3_13].unk10 = temp_v1_74;
// //     temp_v1_75 = this->unk_2449A[5] - 0x34;
// //     this->unk_243E4[temp_s3_13].unk12 = temp_v1_75;
// //     this->unk_243E4[temp_s3_13].v.ob[1] = temp_v1_75;
// //     temp_a0_77 = &this->unk_243E4[temp_s3_13];
// //     temp_v1_76 = temp_a0_77->v.ob[1] - 0x10;
// //     temp_a0_77->unk32 = temp_v1_76;
// //     this->unk_243E4[temp_s3_13].unk22 = temp_v1_76;
// //     this->unk_243E4[temp_s3_13].unk38 = 0x800;
// //     temp_a0_78 = &this->unk_243E4[temp_s3_13];
// //     temp_a0_78->unk18 = (s16) temp_a0_78->unk38;
// //     temp_a1_19 = this->unk_24484;



// //     if (((temp_a1_19 == 1) && ((s32) this->unk_24486 >= 2)) || ((temp_a1_19 == 2) && (this->unk_2448C == 3))) {
// //         if (temp_a1_19 == 1) {
// //             temp_v0_8 = this->unk_24486;
// //             if ((temp_v0_8 == 4) || (temp_v0_8 == 7) || (temp_v0_8 == 0x16)) {
// //                 phi_s4_5 = *(&D_80814644 + (this->unk_24480 * 2));
// //             } else if ((temp_v0_8 == 0x19) || (temp_v0_8 == 0xC)) {
// //                 phi_s4_5 = *(&D_8081464C + (this->unk_24480 * 2));
// //             } else {
// //                 phi_s4_5 = *(&D_80814638 + (this->unk_24480 * 2));
// //             }
// //         } else {
// //             phi_s4_5 = *(&D_80814650 + (this->unk_24482 * 2));
// //         }
// //         temp_v1_77 = this->unk_24508 - 0xA;
// //         this->unk_243E4[temp_s3_14].unk20 = temp_v1_77;
// //         this->unk_243E4[temp_s3_14].v.ob[0] = temp_v1_77;
// //         temp_a0_79 = &this->unk_243E4[temp_s3_14];
// //         temp_v1_78 = temp_a0_79->v.ob[0] + 0x48;
// //         temp_a0_79->unk30 = temp_v1_78;
// //         this->unk_243E4[temp_s3_14].unk10 = temp_v1_78;
// //         temp_a1_20 = this->unk_243E4;
// //         temp_v1_79 = temp_a1_20[phi_s4_5].v.ob[1] + 4;
// //         temp_a1_20[temp_s3_14].unk12 = temp_v1_79;
// //         this->unk_243E4[temp_s3_14].v.ob[1] = temp_v1_79;
// //         temp_a0_80 = &this->unk_243E4[temp_s3_14];
// //         temp_v1_80 = temp_a0_80->v.ob[1] - 0x18;
// //         temp_a0_80->unk32 = temp_v1_80;
// //         this->unk_243E4[temp_s3_14].unk22 = temp_v1_80;
// //         this->unk_243E4[temp_s3_14].unk38 = 0x900;
// //         temp_a0_81 = &this->unk_243E4[temp_s3_14];
// //         temp_a0_81->unk18 = (s16) temp_a0_81->unk38;
// //         this->unk_243E4[temp_s3_14].unk3A = 0x300;
// //         temp_a0_82 = &this->unk_243E4[temp_s3_14];
// //         temp_a0_82->unk2A = (s16) temp_a0_82->unk3A;
// //     }
// //     temp_v1_81 = this->unk_24508 + 0x3A;
// //     this->unk_243E4[temp_s3_14].unk60 = temp_v1_81;
// //     this->unk_243E4[temp_s3_14].unk40 = temp_v1_81;
// //     temp_a0_83 = &this->unk_243E4[temp_s3_14];
// //     temp_v1_82 = temp_a0_83->unk40 + 0x80;
// //     temp_a0_83->unk70 = temp_v1_82;
// //     this->unk_243E4[temp_s3_14].unk50 = temp_v1_82;
// //     temp_a1_21 = this->unk_243E4;
// //     temp_v1_83 = temp_a1_21[*(&D_80814638 + (this->unk_244AA * 2))].v.ob[1];
// //     temp_a1_21[temp_s3_14].unk52 = temp_v1_83;
// //     this->unk_243E4[temp_s3_14].unk42 = temp_v1_83;
// //     temp_a0_84 = &this->unk_243E4[temp_s3_14];
// //     temp_v1_84 = temp_a0_84->unk42 - 0x10;
// //     temp_a0_84->unk72 = temp_v1_84;
// //     this->unk_243E4[temp_s3_14].unk62 = temp_v1_84;
// //     this->unk_243E4[temp_s3_14].unk78 = 0x1000;
// //     temp_a0_85 = &this->unk_243E4[temp_s3_14];
// //     temp_a0_85->unk58 = (s16) temp_a0_85->unk78;
// }


#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080F25C.s")

void func_808108DC(GameState* thisx);
// void func_808108DC(FileChooseContext* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_808108DC.s")

void func_80808F1C(GameState*);
void func_8080BBFC(GameState*);

// FileChoose_ConfigModeDraw
void func_80811CB8(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    OPEN_DISPS(this->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    func_8012C8AC(this->state.gfxCtx);
    FileChoose_RenderView(this, 0.0f, 0.0f, 64.0f);
    // FileChoose_SetWindowVtx
    func_8080D40C(&this->state);
    // FileChoose_SetWindowContentVtx
    func_8080D6D4(&this->state);

    if ((this->unk_24486 != 36) && (this->unk_24486 != 35)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_244B0[0], this->unk_244B0[1], this->unk_244B0[2], this->unk_244BA);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        Matrix_InsertTranslation(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
        Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);

        if (this->unk_2450C) {
            Matrix_RotateStateAroundXAxis(this->unk_2450C / 100.0f);
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[0], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[32], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031408);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[64], 16, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031618);

        gDPPipeSync(POLY_OPA_DISP++);

        // FileChoose_DrawWindowContents
        func_808108DC(&this->state);
    }

    // draw name entry menu
    if ((this->unk_24486 >= 34) && (this->unk_24486 <= 38)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_244B0[0], this->unk_244B0[1], this->unk_244B0[2], this->unk_244BA);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        Matrix_InsertTranslation(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
        Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
        Matrix_RotateStateAroundXAxis((this->unk_2450C - 314.0f) / 100.0f);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[0], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[32], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031408);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[64], 16, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031618);

        gDPPipeSync(POLY_OPA_DISP++);

        // FileChoose_DrawNameEntry
        func_80808F1C(&this->state);
    }

    // draw options menu
    if ((this->unk_24486 >= 39) && (this->unk_24486 <= 43)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_244B0[0], this->unk_244B0[1], this->unk_244B0[2], this->unk_244BA);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        Matrix_InsertTranslation(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
        Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
        Matrix_RotateStateAroundXAxis((this->unk_2450C - 314.0f) / 100.0f);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        
        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[0], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[32], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031408);

        gSPVertex(POLY_OPA_DISP++, &this->unk_A4[64], 16, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031618);

        gDPPipeSync(POLY_OPA_DISP++);

        // FileChoose_DrawOptions
        func_8080BBFC(&this->state);
    }
    
    gDPPipeSync(POLY_OPA_DISP++);
    
    FileChoose_RenderView(this, 0.0f, 0.0f, 64.0f);
    
    CLOSE_DISPS(this->state.gfxCtx);
}

// FileChoose_FadeMainToSelect
void func_80812460(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;

    for (i = 0; i < 3; i++) {
        if (i != this->unk_24480) {
            this->unk_244BC[i] -= 50;
            this->unk_244DA[0] = 
            this->unk_244DA[1] = 
            this->unk_244E2 = 
            this->unk_244BC[i];

            if (gSaveContext.unk_3F3F == 0) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->unk_244C8[i] =
                    this->unk_244C2[i] = 
                    this->unk_244BC[i];
                    this->unk_244CE[i] -= 63;
                }
            } else {
                if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                    this->unk_244C8[i] = 
                    this->unk_244C2[i] = 
                    this->unk_244BC[i];
                    this->unk_244CE[i] -= 63;
                }
            }
        }
    }

    this->unk_244B6[0] += -63;
    this->unk_244B6[1] += 63;
    this->unk_24498--;

    if (this->unk_24498 == 0) {
        this->unk_24498 = 4;
        this->unk_2448C++;
        this->unk_24482 = 0;
    }
}


extern s16 D_80814774[];
// s16 D_80814774[] = { 0, 16, 32 };

// FileChoose_MoveSelectedFileToTop
void func_80812668(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    s32 yStep;

    yStep = ABS_ALT(this->unk_2449A[this->unk_24480] - D_80814774[this->unk_24480]) / this->unk_24498;
    this->unk_2449A[this->unk_24480] += yStep;
    this->unk_24498--;

    if ((this->unk_24498 == 0) || (this->unk_2449A[this->unk_24480] == D_80814774[this->unk_24480])) {
        this->unk_2449A[3] =
        this->unk_2449A[4] = -24;
        this->unk_24498 = 4;
        this->unk_2448C++;
    }
}

// FileChoose_FadeInFileInfo
void func_80812760(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    this->unk_244D4[this->unk_24480] += 50;
    this->unk_244C2[this->unk_24480] -= 100;

    if (this->unk_244C2[this->unk_24480] <= 0) {
        this->unk_244C2[this->unk_24480] = 0;
    }
    this->unk_24498--;

    if (this->unk_24498 == 0) {
        this->unk_244D4[this->unk_24480] = 200;
        this->unk_24498 = 4;
        this->unk_2448C++;
    }

    this->unk_244DE[0] =
    this->unk_244DE[1] =
    this->unk_244D4[this->unk_24480];
}

// FileChoose_ConfirmFile
void func_80812840(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    Input* input = &this->state.input[0];

    if (CHECK_BTN_ALL(input->press.button, BTN_START) || (CHECK_BTN_ALL(input->press.button, BTN_A))) {
        if (this->unk_24482 == 0) {
            func_8013ECE0(300.0f, 180, 20, 100);
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
            this->unk_2448C = 6;
            func_801A4058(0xF);
        } else {
            play_sound(NA_SE_SY_FSEL_CLOSE);
            this->unk_2448C++;
        }
    } else if CHECK_BTN_ALL(input->press.button, BTN_B) {
        play_sound(NA_SE_SY_FSEL_CLOSE);
        this->unk_2448C++;
    } else if (ABS_ALT(this->unk_24504) >= 30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);
        this->unk_24482 ^= 1;
    }
}

// FileChoose_FadeOutFileInfo
void func_80812980(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    this->unk_244D4[this->unk_24480] -= 200 / 4;
    this->unk_244C2[this->unk_24480] += 200 / 4;
    this->unk_24498--;

    if (this->unk_24498 == 0) {
        this->unk_2449A[3] = this->unk_2449A[4] = 0;
        this->unk_244C2[this->unk_24480] = 200;
        this->unk_244D4[this->unk_24480] = 0;
        this->unk_244AE = 0;
        this->unk_24498 = 4;
        this->unk_2448C++;
    }
    this->unk_244DA[2] =
    this->unk_244DA[3] = 
    this->unk_244D4[this->unk_24480];
}

// FileChoose_MoveSelectedFileToSlot
void func_80812A6C(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s32 yStep;
    s16 i;

    yStep = ABS_ALT(this->unk_2449A[this->unk_24480]) / this->unk_24498;
    this->unk_2449A[this->unk_24480] -= yStep;
    
    if (this->unk_2449A[this->unk_24480] <= 0) {
        this->unk_2449A[this->unk_24480] = 0;
    }

    for (i = 0; i < 3; i++) {
        if (i != this->unk_24480) {
            this->unk_244BC[i] += 200 / 4;
            
            if (this->unk_244BC[i] >= 200) {
                this->unk_244BC[i] = 200;
            }

            this->unk_244DA[0] = 
            this->unk_244DA[1] = 
            this->unk_244E2 = 
            this->unk_244BC[i];

            if (gSaveContext.unk_3F3F == 0) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->unk_244C2[i] = 
                    this->unk_244C8[i] =
                    this->unk_244BC[i];
                    this->unk_244CE[i] += 255 / 4;
                }
            } else {
                if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                    this->unk_244C2[i] = 
                    this->unk_244C8[i] =
                    this->unk_244BC[i];
                    this->unk_244CE[i] += 255 / 4;
                }
            }
        }
    }

    this->unk_244B6[0] -= 255 / 4;
    this->unk_244B6[1] += 255 / 4;
    this->unk_24498--;

    if (this->unk_24498 == 0) {
        this->unk_244B6[0] = 255;
        this->unk_244B6[1] = 0;
        this->unk_244AC = this->unk_244AE;
        this->unk_24498 = 4;
        this->unk_24484 = 1;
        this->unk_24486 = 2;
        this->unk_2448A = 2;
        this->unk_2448C = 0;
    }
}

// FileChoose_FadeOut
void func_80812D44(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    this->unk_2450A += 40;
    if (this->unk_2450A >= 0xFF) {
        this->unk_2450A = 0xFF;
        this->unk_2448C++;
    }
}

void func_80144E78(FileChooseContext* fileChooseCtx, SramContext* sramCtx);

// FileChoose_LoadGame
void func_80812D94(GameState *thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    u16 phi_v0;

    gSaveContext.fileNum = this->unk_24480;
    func_80144E78(this, &this->sramCtx);

    gSaveContext.gameMode = 0;
    
    // TODO: Macro this properly everywhere
    do { \
        { \
            GameState* state = (&this->state); \
            state->running = false; \
        } \
        SET_NEXT_GAMESTATE(&this->state, Play_Init, GlobalContext);
    } while (0);


    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[0].entranceIndex = 0xFFFF;
    gSaveContext.seqIndex = 0xFF;
    gSaveContext.nightSeqIndex = 0xFF;
    gSaveContext.showTitleCard = 1;
    gSaveContext.dogParams = 0;

    phi_v0 = 0;
    do {
        gSaveContext.unk_3DD0[phi_v0] = 0;
        phi_v0++;
    } while (phi_v0 < 7);

    gSaveContext.unk_3F26 = 0x32;
    gSaveContext.unk_3DC0 = 0;
    gSaveContext.healthAccumulator = 0;
    gSaveContext.unk_3F2C = 0;
    gSaveContext.unk_3F46 = 0;
    gSaveContext.environmentTime = 0;
    gSaveContext.nextTransition = 0xFF;
    gSaveContext.cutsceneTrigger = 0;
    gSaveContext.unk_3F4D = 0;
    gSaveContext.nextDayTime = 0xFFFF;
    gSaveContext.unk_3DBB = 0;
    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = 0;
    gSaveContext.buttonStatus[2] = 0;
    gSaveContext.buttonStatus[3] = 0;
    gSaveContext.buttonStatus[4] = 0;
    gSaveContext.unk_3F1E = 0;
    gSaveContext.unk_3F20 = 0;
    gSaveContext.unk_3F22 = 0;
    gSaveContext.unk_3F24 = 0;
    gSaveContext.tatlTimer = 0;
}

// gSelectModeUpdateFuncs
extern void (*D_8081477C[])(GameState*);
// void (*D_8081477C[])(GameState*) = {
//     func_80812460,
//     func_80812668,
//     func_80812760,
//     func_80812840,
//     func_80812980,
//     func_80812A6C,
//     func_80812D44,
//     func_80812D94,
// };

// SelectModeUpdate
void func_80812E94(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    // selectMode
    D_8081477C[this->unk_2448C](&this->state);
}

// SelectModeDraw
void func_80812ED0(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    OPEN_DISPS(this->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    func_8012C8AC(this->state.gfxCtx);
    FileChoose_RenderView(this, 0.0f, 0.0f, 64.0f);
    func_8080D40C(&this->state);
    func_8080D6D4(&this->state);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_244B0[0], this->unk_244B0[1], this->unk_244B0[2], this->unk_244BA);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    Matrix_InsertTranslation(0.0f, 0.0f, -93.6f, 0);
    Matrix_Scale(0.78f, 0.78f, 0.78f, 1);
    Matrix_RotateStateAroundXAxis(this->unk_2450C / 100.0f);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(POLY_OPA_DISP++, &this->unk_A4[0], 32, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

    gSPVertex(POLY_OPA_DISP++, &this->unk_A4[32], 32, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_01031408);

    gSPVertex(POLY_OPA_DISP++, &this->unk_A4[64], 16, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_01031618);

    func_808108DC(&this->state);
    gDPPipeSync(POLY_OPA_DISP++);
    FileChoose_RenderView(this, 0.0f, 0.0f, 64.0f);

    CLOSE_DISPS(this->state.gfxCtx);
}

void FileChoose_UpdateAndDrawSkybox(FileChooseContext* this) {
    GraphicsContext* gfxCtx; // TODO: check if this temp is needed, or if it recasts thisx instead
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;

    gfxCtx = this->state.gfxCtx;
    OPEN_DISPS(gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    eyeX = 1000.0f * Math_CosS(fileChooseSkyboxRotation) - 1000.0f * Math_SinS(fileChooseSkyboxRotation);
    eyeY = -700.0f;
    eyeZ =  1000.0f * Math_SinS(fileChooseSkyboxRotation) + 1000.0f * Math_CosS(fileChooseSkyboxRotation);

    FileChoose_RenderView(this, eyeX, eyeY, eyeZ);
    SkyboxDraw_Draw(&this->skyboxCtx, this->state.gfxCtx, 1, this->envCtx.unk_13, eyeX, -700.0f, eyeZ);

    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);

    fileChooseSkyboxRotation += -0xA;

    CLOSE_DISPS(gfxCtx);
}

// sScreenFillSetupDL
extern Gfx D_80814510[];

// State update/draws
extern void (*D_8081479C[])(GameState*);
// void (*D_8081479C[])(GameState*) = {
//     func_8080BDAC,
//     func_80811CB8,
//     func_80812ED0,
// };
extern void (*D_808147A8[])(GameState*);
// void (*D_808147A8[])(GameState*) = {
//     func_8080BC58,
//     func_8080D3D0,
//     func_80812E94,
// };

extern void* D_808147B4[];
// Please wait, Decide/Cancel, Decide/Save
// void* D_808147B4[] = { 0x0100B2B0, 0x0100A030, 0x0100A930 };
extern s16 D_808147C0[];
// s16 D_808147C0[] = { 144, 144, 152 };
extern s16 D_808147C8[];
// s16 D_808147C8[] = { 90, 90, 86 };

void FileChoose_Main(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    Input* input = &this->state.input[0];
    s32 texIndex;
    s32 pad;

    func_8012CF0C(this->state.gfxCtx, 0, 1, 0, 0, 0);

    OPEN_DISPS(this->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x01, this->staticSegment);
    gSPSegment(POLY_OPA_DISP++, 0x02, this->parameterSegment);
    gSPSegment(POLY_OPA_DISP++, 0x06, this->titleSegment);

    // stickRelX
    this->unk_24502 = input->rel.stick_x;
    // stickRelY
    this->unk_24504 = input->rel.stick_y;

    if (this->unk_24502 < -30) {
        // stickXDir
        if (this->unk_244FE == -1) {
            // inputTimerX
            this->unk_244FA--;
            if (this->unk_244FA < 0) {
                this->unk_244FA = 2;
            } else {
                this->unk_24502 = 0;
            }
        } else {
            this->unk_244FA = 10;
            this->unk_244FE = -1;
        }
    } else if (this->unk_24502 > 30) {
        if (this->unk_244FE == 1) {
            this->unk_244FA--;
            if (this->unk_244FA < 0) {
                this->unk_244FA = 2;
            } else {
                this->unk_24502 = 0;
            }
        } else {
            this->unk_244FA = 10;
            this->unk_244FE = 1;
        }
    } else {
        this->unk_244FE = 0;
    }

    if (this->unk_24504 < -30) {
        // stickYDir
        if (this->unk_24500 == -1) {
            // inputTimerY
            this->unk_244FC--;
            if (this->unk_244FC < 0) {
                this->unk_244FC = 2;
            } else {
                this->unk_24504 = 0;
            }
        } else {
            this->unk_244FC = 10;
            this->unk_24500 = -1;
        }
    } else if (this->unk_24504 > 30) {
        if (this->unk_24500 == 1) {
            this->unk_244FC--;
            if (this->unk_244FC < 0) {
                this->unk_244FC = 2;
            } else {
                this->unk_24504 = 0;
            }
        } else {
            this->unk_244FC = 10;
            this->unk_24500 = 1;
        }
    } else {
        this->unk_24500 = 0;
    }

    // emptyFileTextAlpha ?
    this->unk_244E8 = 0;

    func_8080D2EC(this);
    // menuMode
    D_808147A8[this->unk_24484](&this->state);
    FileChoose_UpdateAndDrawSkybox(this);
    D_8081479C[this->unk_24484](&this->state);

    func_8012C628(this->state.gfxCtx);

    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 100, 255, 255, this->unk_244E6);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    if (this->sramCtx.status > 0) {
        texIndex = 0;
    } else if ((this->unk_24486 > 38) && (this->unk_24486 < 44)) {
        texIndex = 2;
    } else {
        texIndex = 1;
    }

    gDPLoadTextureBlock(POLY_OPA_DISP++, D_808147B4[texIndex], G_IM_FMT_IA, G_IM_SIZ_8b, D_808147C0[texIndex], 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, D_808147C8[texIndex] << 2, 204 << 2, (D_808147C8[texIndex] + D_808147C0[texIndex]) << 2, 
                        (204 + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPDisplayList(POLY_OPA_DISP++, D_80814510);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, this->unk_2450A);
    gSPDisplayList(POLY_OPA_DISP++, D_0E000000.fillRect);

    CLOSE_DISPS(this->state.gfxCtx);
}

// FileChoose_InitContext
void func_80813908(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    EnvironmentContext* envCtx = &this->envCtx;

    Sram_Alloc(&this->state, &this->sramCtx);
    func_801457CC(&this->state, &this->sramCtx);

    // this->menuMode = FS_MENU_MODE_INIT;
    this->unk_24484 = 0;

    this->unk_24480 = 
    this->unk_2448C = 
    this->unk_2448E = 
    this->unk_244A6 = 
    this->unk_24482 = 0;

    this->unk_244F6[0] = 2;
    this->unk_244F6[1] = 3;
    this->unk_244AC = 0;
    this->unk_244AE = 1;

    this->unk_2450A = 255;
    this->unk_244F2 = 1;
    this->unk_244F4 = 0xC;
    this->unk_244EA[0] = 155;
    this->unk_244EA[1] = 255;
    this->unk_244EA[2] = 255;
    this->unk_244EA[3] = 70;
    this->unk_24486 = 0;
    this->unk_2450C = 0.0f;

    this->unk_244FE = 
    this->unk_244FA = 0;

    this->unk_24500 = 
    this->unk_244FC = 0;

    this->unk_24518 = 
    this->unk_2451A = 
    this->unk_24516 = 0;

    // this->kbdButton = FS_KBD_BTN_NONE;
    this->unk_24510 = 99;

    // windowColor
    this->unk_244B0[0] = 100;
    this->unk_244B0[1] = 150;
    this->unk_244B0[2] = 255;

    this->unk_244BA    = 
    this->unk_244B6[0] = 
    this->unk_244B6[1] = 
    this->unk_244BC[0] = 
    this->unk_244BC[1] = 
    this->unk_244BC[2] = 
    this->unk_244C2[0] = 
    this->unk_244C2[1] = 
    this->unk_244C2[2] = 
    this->unk_244C8[0] = 
    this->unk_244C8[1] = 
    this->unk_244C8[2] = 
    this->unk_244CE[0] = 
    this->unk_244CE[1] = 
    this->unk_244CE[2] = 
    this->unk_244D4[0] = 
    this->unk_244D4[1] = 
    this->unk_244D4[2] = 
    this->unk_244DA[0] = 
    this->unk_244DA[1] = 
    this->unk_244DA[2] = 
    this->unk_244DA[3] = 
    this->unk_244E2    = 
    this->unk_244E4    = 
    this->unk_244E6    = 
    this->unk_244E8 = 0;

    this->unk_24508 = 6;
    this->unk_24498 = 4;
    this->unk_244A8 = -1;

    this->unk_244AA    =
    this->unk_2449A[0] =
    this->unk_2449A[1] =
    this->unk_2449A[2] =
    this->unk_2449A[3] =
    this->unk_2449A[4] =
    this->unk_2449A[5] =
    this->unk_24492[0] =
    this->unk_24492[1] =
    this->unk_24492[2] = 0;

    this->unk_2451E[0] = 0;
    this->unk_2451E[1] = 3;
    this->unk_2451E[2] = 6;
    this->unk_2451E[3] = 8;
    this->unk_2451E[4] = 10;
    this->unk_24528 = 20;

    ShrinkWindow_SetLetterboxTarget(0);
    gSaveContext.environmentTime = 0;
    gSaveContext.time = 0;

    // Skybox_Init
    func_801434E4(&this->state, &this->skyboxCtx, 1);
    R_ENV_TIME_INCREMENT = 10;

    // TODO: copy some variable names from OoT
    envCtx->unk_19 = 0;
    envCtx->unk_1A = 0;
    envCtx->unk_21 = 0;
    envCtx->unk_22 = 0;
    envCtx->unk_44 = 0;
    envCtx->unk_10 = 99;
    envCtx->unk_11 = 99;
    envCtx->unk_1F = 0;
    envCtx->unk_20 = 0;
    envCtx->unk_C1 = 0;
    envCtx->unk_17 = 2;
    envCtx->skyboxDisabled = 0;
    envCtx->unk_13 = 0;
    envCtx->unk_84 = 0.0f;
    envCtx->unk_88 = 0.0f;

    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = 0;
    gSaveContext.buttonStatus[2] = 0;
    gSaveContext.buttonStatus[3] = 0;
    gSaveContext.buttonStatus[4] = 0;
}

void FileChoose_Destroy(GameState* this) {
    ShrinkWindow_Destroy();
}

void FileChoose_Init(GameState* thisx) {
    s32 pad;
    FileChooseContext* this = (FileChooseContext*)thisx;
    size_t size;

    Game_SetFramerateDivisor(&this->state, 1);
    Matrix_StateAlloc(&this->state);
    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = FileChoose_Main;
    this->state.destroy = FileChoose_Destroy;
    func_80813908(&this->state);
    Font_LoadOrderedFont(&this->font);

    size = SEGMENT_ROM_SIZE(title_static);
    this->staticSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->staticSegment, SEGMENT_ROM_START(title_static), size);

    size = SEGMENT_ROM_SIZE(parameter_static);
    this->parameterSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->parameterSegment, SEGMENT_ROM_START(parameter_static), size);

    size = objectFileTable[OBJECT_MAG].vromEnd - objectFileTable[OBJECT_MAG].vromStart;
    this->titleSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->titleSegment, objectFileTable[OBJECT_MAG].vromStart, size);

    audio_setBGM(0xA);
    func_801A3238(SEQ_PLAYER_BGM_MAIN, NA_BGM_FILE_SELECT, 0, 7, 1);
}
