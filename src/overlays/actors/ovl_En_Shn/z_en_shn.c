/*
 * File: z_en_shn.c
 * Overlay: ovl_En_Shn
 * Description: Swamp Tourist Center Guide
 * Shashin
 */

#include "z_en_shn.h"

#define FLAGS 0x00000009

#define THIS ((EnShn*)thisx)

void EnShn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE69E8(EnShn* this, GlobalContext* globalCtx);
void func_80AE6A64(EnShn* this, GlobalContext* globalCtx);
void func_80AE6704(EnShn* this, GlobalContext* globalCtx);

s32 D_80AE6F00[] = { 0x00170800, 0x0B0E09C4, 0x0C0F09C5, 0x0C111708, 0x03018C04, 0x018E1901, 0x860F00FF, 0x1E001300,
                     0x00011501, 0x47280012, 0x28001928, 0x002D2800, 0x5D280093, 0x28003319, 0x00472C09, 0xE70C2F00,
                     0x000C1210, 0x2C09CB0C, 0x2F00000C, 0x0F09CC0C, 0x0F09CD0C, 0x0500A500, 0xCB00CB2C, 0x09D10C2F,
                     0x00000C0F, 0x09D20C19, 0xFFE62C09, 0xD30C2F00, 0x000C0F09, 0xD40C0F09, 0xD50C0500, 0x9200B200,
                     0xB22C09D9, 0x0C2F0000, 0x0C0F09DA, 0x0C102C09, 0xE80C2F00, 0x000C0F09, 0xE90C0F09, 0xEA0C0057,
                     0x04001712, 0x06000C00, 0x0013000C, 0x0C115704, 0x0700000E, 0x09EB0C12, 0x16101206, 0x00060000,
                     0x1300060C, 0x07FFEC2C, 0x09EC0C2F, 0x00000C0F, 0x09ED0C0F, 0x09EE0C00, 0x57040017, 0x1206000C,
                     0x00001300, 0x0C0C1157, 0x04070000, 0x0E09EF0C, 0x12161012, 0x06000600, 0x00130006, 0x0C07FFEC,
                     0x12060004, 0x00001300, 0x040C0700, 0x000E09CE, 0x0C161012, 0x06000200, 0x00130002, 0x0C070000,
                     0x0E09D80C, 0x16100C0F, 0x09CF0C1C, 0x05011509, 0x0000100E, 0x09D60C19, 0xFFF10037, 0x40001C2C,
                     0x09DB0C2F, 0x00000C0F, 0x09DC0C0F, 0x09DD0C0F, 0x09DE0C0F, 0x09DF0C11, 0x3740102C, 0x09E00C2F,
                     0x00000C0F, 0x09E10C0F, 0x09E20C10, 0x00374000, 0x180E09DB, 0x0C0F09DC, 0x0C0F09DD, 0x0C0F09DE,
                     0x0C0F09DF, 0x0C113740, 0x100E09E0, 0x0C0F09E1, 0x0C0F09E2, 0x0C100E09, 0xC90C0F09, 0xCA0C100E,
                     0x09C60C10, 0x001402FF, 0xED0E09C8, 0x0C19FE69 };

s32 D_80AE70B0[] = { 0x0E09D00C, 0x16100000 };

s32 D_80AE70B8[] = { 0x28001228, 0x00152800, 0x28280055, 0x28008A28, 0x002D1900, 0x402C09E7, 0x0C12102C, 0x09CB2F00,
                     0x000C0F09, 0xCC0C0F09, 0xCD0C0500, 0xA000C600, 0xC62C09D1, 0x2F00000C, 0x0F09D20C, 0x19FFE72C,
                     0x09D32F00, 0x000C0F09, 0xD40C0F09, 0xD50C0500, 0x8F00AF00, 0xAF2C09D9, 0x2F00000C, 0x0F09DA0C,
                     0x102C09E8, 0x2F00000C, 0x0F09E90C, 0x0F09EA0C, 0x00570400, 0x17120600, 0x0C000013, 0x000C0C11,
                     0x57040700, 0x000E09EB, 0x0C121610, 0x12060006, 0x00001300, 0x060C07FF, 0xEC2C09EC, 0x2F00000C,
                     0x0F09ED0C, 0x0F09EE0C, 0x00570800, 0x17120600, 0x0C000013, 0x000C0C11, 0x57080700, 0x000E09EF,
                     0x0C121610, 0x12060006, 0x00001300, 0x060C07FF, 0xEC120600, 0x04000013, 0x00040C07, 0x00000E09,
                     0xCE0C1610, 0x12060002, 0x00001300, 0x020C0700, 0x000E09D8, 0x0C16100C, 0x0F09CF0C, 0x1C050115,
                     0x09000010, 0x0E09D60C, 0x19FFF100 };

s32 D_80AE71C4[] = { 0x00374000, 0x1C2C09DB, 0x0C2F0000, 0x0C0F09DC, 0x0C0F09DD, 0x0C0F09DE, 0x0C0F09DF,
                     0x0C113740, 0x102C09E0, 0x0C2F0000, 0x0C0F09E1, 0x0C0F09E2, 0x0C100000 };

const ActorInit En_Shn_InitVars = {
    ACTOR_EN_SHN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SHN,
    sizeof(EnShn),
    (ActorFunc)EnShn_Init,
    (ActorFunc)EnShn_Destroy,
    (ActorFunc)EnShn_Update,
    (ActorFunc)EnShn_Draw,
};

s32 D_80AE7218[] = { 0x0600D9D0, 0x3F800000, 0x0000FFFF, 0x00000000, 0x0600D9D0, 0x3F800000, 0x0000FFFF, 0x0000FFFC,
                     0x0600E6C4, 0x3F800000, 0x0000FFFF, 0x00000000, 0x0600E6C4, 0x3F800000, 0x0000FFFF, 0x0000FFFC };

s32 D_80AE7258[] = { 0x00000000, 0x00000002, 0x00000003, 0x00000008, 0x0000000A, 0x00000001 };

s32 D_80AE7270[] = { 0x44960000, 0x00000000, 0x00000000, 0x00000000 };

extern UNK_TYPE D_0600B738;
extern UNK_TYPE D_0600E7D0;

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6130.s")
void func_80AE6130(EnShn* this) {
    this->skelAnime.playSpeed = this->unk2CC;
    SkelAnime_Update(&this->skelAnime);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE615C.s")
s32 func_80AE615C(EnShn* this, s32 arg1) {
    s32 phi_v0;
    s32 phi_v1;

    phi_v0 = 0;
    phi_v1 = 0;
    if (arg1 != this->unk2E8) {
        phi_v0 = 1;
    }
    if (phi_v0 != 0) {
        this->unk2E8 = arg1;
        phi_v1 = func_8013BC6C(&this->skelAnime, D_80AE7218, arg1);
        this->unk2CC = this->skelAnime.playSpeed;
    }
    return phi_v1;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE61C0.s")
s32 func_80AE61C0(EnShn* this) {
    s16 phi_v1;
    f32 phi_f0;

    if (this->unk2C8 == 0) {
        phi_v1 = 0;
    } else {
        this->unk2C8--;
        phi_v1 = this->unk2C8;
    }
    if (phi_v1 == 0) {
        this->unk2EC ^= 1;
        this->unk2C8 = Rand_S16Offset(0x1E, 0x1E);
    }
    if (this->unk2EC != 0) {
        phi_f0 = 120.0f;
    } else {
        phi_f0 = 80.0f;
    }
    return Actor_IsActorFacingLinkAndWithinRange(&this->actor, phi_f0, 0x238C);
}

Player* func_80AE625C(EnShn* this, GlobalContext* globalCtx) {
    return GET_PLAYER(globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE626C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE63A8.s")
// void func_80AE63A8(EnShn* this, GlobalContext* globalCtx) {
//     s16 phi_v1;
//     s16 phi_v1_2;

//     this->unk1E4 = func_80AE625C(this, globalCtx);
//     if (((this->unk1D8 & 8) != 0) && (this->unk1E4 != 0)) {
//         if (this->unk2CA == 0) {
//             phi_v1 = 0;
//         } else {
//             this->unk2CA--;
//             phi_v1 = this->unk2CA;
//         }
//         if (phi_v1 == 0) {
//             func_80AE626C(this);
//             this->unk1D8 &= ~0x20;
//             this->unk1D8 |= 0x10;
//         }
//         else if ((this->unk1D8 & 0x10) != 0) {
//             this->unk1D8 &= ~0x10;
//             this->unk2BA = 0;
//             this->unk2BC = 0;
//             this->unk2CA = 0x14;
//         } else {
//             if (this->unk2CA == 0) {
//                 phi_v1_2 = 0;
//             } else {
//                 this->unk2CA--;
//                 phi_v1_2 = this->unk2CA;
//             }
//             if (phi_v1_2 == 0) {
//                 this->unk1D8 |= 0x20;
//             }
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6704.s")

s32* func_80AE6880(EnShn* this, GlobalContext* globalCtx) {
    if (this->unk2BE != 0) {
        return D_80AE70B0;
    }
    if ((this->unk1D8 & 0x80) != 0) {
        this->unk2D8 = func_80AE6704;
        return D_80AE70B8;
    }
    if ((this->unk1D8 & 0x100) != 0) {
        return D_80AE71C4;
    }
    this->unk2D8 = func_80AE6704;
    return D_80AE6F00;
}

s32 func_80AE68F0(EnShn* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 ret = 0;

    if (this->unk1D8 & 7) {
        if (func_800B84D0(&this->actor, globalCtx)) {
            this->unk1D8 &= ~0x180;
            if (player->unk_A87 == 0x13) {
                this->unk1D8 |= 0x80;
                this->unk2E4 = player->unk_A87;
            } else if (player->unk_A87) {
                this->unk1D8 |= 0x100;
                this->unk2E4 = player->unk_A87;
            }
            func_8013AED4(&this->unk1D8, 0, 7);
            this->unk1DC = func_80AE6880(this, globalCtx);
            this->unk2C6 = 0;
            if ((gSaveContext.weekEventReg[0x17] & 8)) {
                this->unk1D8 |= 8;
            }
            this->actionFunc = func_80AE6A64;
            ret = 1;
        }
    }
    return ret;
}

void func_80AE69E8(EnShn* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
    if ((gSaveContext.weekEventReg[0x17] & 8) && (func_80AE61C0(this))) {
        this->unk1D8 |= 8;
    } else {
        this->unk1D8 &= ~0x8;
    }
}

void func_80AE6A64(EnShn* this, GlobalContext* globalCtx) {
    s16 yawBetweenActors;
    Vec3f playerPos;
    Vec3f shnPos;

    if (func_8010BF58(&this->actor, globalCtx, this->unk1DC, this->unk2D8, &this->unk1E0) != 0) {
        func_8013AED4(&this->unk1D8, 3, 7);
        this->unk1D8 &= 0xFFF7;
        this->unk1D8 |= 0x20;
        this->unk2CA = 0x14;
        this->unk1E0 = 0;
        this->unk2BE = 0;
        this->actionFunc = func_80AE69E8;
    } else if (this->unk1E4 != 0) {
        Math_Vec3f_Copy(&playerPos, &this->unk1E4->actor.world.pos);
        Math_Vec3f_Copy(&shnPos, &this->actor.world.pos);
        yawBetweenActors = Math_Vec3f_Yaw(&shnPos, &playerPos);
        Math_ApproachS(&this->actor.shape.rot.y, yawBetweenActors, 4, 0x2AA8);
    }
}

void EnShn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnShn* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600E7D0, NULL, &this->unk1FA, &this->unk25A, 16);
    this->unk2E8 = -1;
    if ((gSaveContext.weekEventReg[0x17] & 8) != 0) {
        func_80AE615C(this, 0);
    } else {
        func_80AE615C(this, 2);
    }
    this->actor.targetMode = 6;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk2E0 = 0;
    this->unk2D8 = 0;
    this->unk1D8 = 0;
    if (gSaveContext.entranceIndex != 0xA820) {
        func_8013AED4(&this->unk1D8, 3, 7);
        this->unk2BE = 0;
    } else {
        func_8013AED4(&this->unk1D8, 4, 7);
        this->unk2BE = 1;
    }
    this->actionFunc = func_80AE69E8;
}

void EnShn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnShn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnShn* this = THIS;

    func_80AE68F0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80AE65F4(this, globalCtx);
    func_80AE6130(this);
    func_80AE63A8(this, globalCtx);
    this->unk2E0 = 0;
    func_8013C964(&this->actor, globalCtx, 120.0f, 40.0f, 0, this->unk1D8 & 7);
}

// OverrideLimb
s32 func_80AE6CF0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 0xF) {
        func_80AE6488(thisx, globalCtx);
        *dList = &D_0600B738;
    }
    return 0;
}

// PostLimb
void func_80AE6D40(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx)
{
    if (limbIndex == 0xF)
    {
        Matrix_MultiplyVector3fByState((Vec3f *) D_80AE7270, &thisx->focus.pos);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6D90.s")
// void func_80AE6D90(GlobalContext *globalCtx, s32 limbIndex, Actor *thisx)
// {
//     EnShn* this = THIS;
//     u16 temp_v0;
//     s32 phi_v0;
//     s32 phi_v1;

//     temp_v0 = this->unk1D8;
//     phi_v1 = 0;
//     if ((temp_v0 & 0x20) == 0)
//     {
//         if ((temp_v0 & 0x10) != 0)
//         {
//             phi_v0 = 1;
//             phi_v1 = 1;
//         }
//         else
//         {
//             phi_v0 = 1;
//         }
//     }
//     else
//     {
//         phi_v0 = 0;
//     }
//     if (limbIndex == 0xF)
//     {
//         func_8013AD9C((s16) (this->unk2BA + 0x4000), (s16) (this->unk2BC + thisx->shape.rot.y + 0x4000), thisx + 0x1E8, thisx + 0x1F4, phi_v0, phi_v1);
//         Matrix_StatePop();
//         Matrix_InsertTranslation(this->unk1E8, this->unk1EC, this->unk1F0, 0);
//         Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, 1);
//         Matrix_RotateY(this->unk1F6, 1);
//         Matrix_InsertXRotation_s(this->unk1F4, 1);
//         Matrix_InsertZRotation_s(this->unk1F8, 1);
//         Matrix_StatePush();
//     }
// }

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Draw.s")
