/*
 * File: z_dm_ah.c
 * Overlay: ovl_Dm_Ah
 * Description: Anju's Mother (cutscene)
 */

#include "z_dm_ah.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((DmAh*)thisx)

void DmAh_Init(Actor* thisx, PlayState* play);
void DmAh_Destroy(Actor* thisx, PlayState* play);
void DmAh_Update(Actor* thisx, PlayState* play);
void DmAh_Draw(Actor* thisx, PlayState* play);

void func_80C1D7FC(DmAh* this, PlayState* play);
void func_80C1D92C(DmAh* this, PlayState* play);
s32 func_80C1D410(DmAh *this, s32 arg1);
void func_80C1D458(DmAh *this);
s32 func_80C1D4D0(DmAh *this, s32 arg1);
s32 func_80C1D6E0(DmAh *this, s32 arg1);
#if 0
const ActorInit Dm_Ah_InitVars = {
    ACTOR_DM_AH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(DmAh),
    (ActorFunc)DmAh_Init,
    (ActorFunc)DmAh_Destroy,
    (ActorFunc)DmAh_Update,
    (ActorFunc)DmAh_Draw,
};

static AnimationInfoS D_80C1DDE0[2] = {
    { (AnimationHeader *)0x06001860, 1.0f, 0, -1, 0, 0 },
    { (AnimationHeader *)0x06000DDC, 1.0f, 0, -1, 0, 0 },
};

static Vec3f D_80C1DE14 = { 1000.0f, 0.0f, 0.0f };

static ? D_80C1DE00;                                /* unable to generate initializer */
static Vec3f D_80C1DE14 = { 1000.0f, 0.0f, 0.0f };
static void *D_80C1DE20[2] = { (void *)0x06008D70, (void *)0x06009570 };
static void *D_80C1DE28[6] = {
    (void *)0x06006D70,
    (void *)0x06007570,
    (void *)0x06007D70,
    (void *)0x06007570,
    (void *)0x06008570,
    NULL,
};

#endif

extern UNK_TYPE D_06009E70;
extern AnimationInfoS D_80C1DDE0[];

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D410.s")

s32 func_80C1D410(DmAh *this, s32 arg1) {
    s32 phi_v1;

    phi_v1 = 0;
    if (arg1 != this->unk294) {
        this->unk294 = arg1;
        phi_v1 = SubS_ChangeAnimationByInfoS(&this->unk144, D_80C1DDE0, arg1);
    }
    return phi_v1;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D458.s")

void func_80C1D458(DmAh *this) {
    s16 phi_v1;

    if (this->unk286 == 0) {
        phi_v1 = 0;
    } else {
        this->unk286--;
        phi_v1 = this->unk286;
    }
    if (phi_v1 == 0) {
        this->unk284++;
        if (this->unk284 >= 4) {
            this->unk286 = Rand_S16Offset(0x1E, 0x1E);
            this->unk284 = 0;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D4D0.s")

s32 func_80C1D4D0(DmAh *this, s32 arg1) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s16 temp_v0;

    Math_Vec3f_Copy(&sp40, &this->unk280->actor.world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    temp_v0 = Math_Vec3f_Yaw(&sp34, &sp40);
    
    Math_ApproachS(&this->unk28C, (temp_v0 - this->unk290) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk28C = CLAMP(this->unk28C, -0x1FFE, 0x1FFE);
    
    Math_ApproachS(&this->unk290, (s16) ((temp_v0 - this->unk28C) - this->actor.shape.rot.y), 4, 0x2AA8);
    this->unk290 = CLAMP(this->unk290, -0x1C70, 0x1C70);

    if (this->unk280->actor.id == 0) {
        sp40.y = this->unk280->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk280->actor.focus.pos);
    }

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);
    Math_ApproachS(&this->unk28A, (s16) (Math_Vec3f_Pitch(&sp34, &sp40) - this->unk28E), 4, 0x2AA8);
    this->unk28A = CLAMP(this->unk28A, -0x1C70, 0x1C70);

    Math_ApproachS(&this->unk28E, (s16) (Math_Vec3f_Pitch(&sp34, &sp40) - this->unk28A), 4, 0x2AA8);
    this->unk28E = CLAMP(this->unk28E, -0x1C70, 0x1C70);
    return true;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D6E0.s")

s32 func_80C1D6E0(DmAh *this, s32 arg1) {
    //s16 temp_v0_2;
    u16 temp_t0;
    u16 temp_t9;
    //u16 temp_v0;
    s16 phi_v1;

    if (this->unk280 != NULL) {
        func_80C1D4D0(this, arg1);
        this->unk27C &= 0xFFFE;
        this->unk27C |= 2;
    } else if (this->unk27C & 2) {
            this->unk27C &= 0xFFFD;
            this->unk28A = 0;
            this->unk28C = 0;
            this->unk28E = 0;
            this->unk290 = 0;
            this->unk288 = 0x14;
        } else {
            if (this->unk288 == 0) {
                phi_v1 = 0;
            } else {
                this->unk288--;
                phi_v1 = this->unk288;
            }
            if (phi_v1 == 0) {
                this->unk27C |= 1;
            }
        }
    
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1D92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1DAD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/func_80C1DB24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ah/DmAh_Draw.s")
