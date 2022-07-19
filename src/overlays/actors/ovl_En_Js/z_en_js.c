/*
 * File: z_en_js.c
 * Overlay: ovl_En_Js
 * Description: Moon Child
 */

#include "z_en_js.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnJs*)thisx)

void EnJs_Init(Actor* thisx, PlayState* play);
void EnJs_Destroy(Actor* thisx, PlayState* play);
void EnJs_Update(Actor* thisx, PlayState* play);
void EnJs_Draw(Actor* thisx, PlayState* play);

void func_80968A5C(EnJs* this);                  /* extern */
void func_80968B8C(EnJs* this, PlayState* play); /* extern */
s32 func_809692A8(s32);                          /* extern */
void func_8096971C(EnJs* this, PlayState* play); /* extern */
void func_80969B5C(EnJs* this, PlayState* play); /* extern */
void func_8096A104(EnJs* this, PlayState* play); /* extern */
void func_8096A6F4(EnJs* this, PlayState* play);
s32 func_80969400(s32);
void func_80968B18(EnJs* this);
#if 0
const ActorInit En_Js_InitVars = {
    ACTOR_EN_JS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OB,
    sizeof(EnJs),
    (ActorFunc)EnJs_Init,
    (ActorFunc)EnJs_Destroy,
    (ActorFunc)EnJs_Update,
    (ActorFunc)EnJs_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8096ABA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_8096ABA0;

extern UNK_TYPE D_06010880;
extern UNK_TYPE D_06016F58;
extern UNK_TYPE D_06017E98;
extern FlexSkeletonHeader D_060164B8;
extern AnimationHeader D_06010CD8;
extern AnimationHeader D_0601764C;
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Init.s")

void EnJs_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    s16 cs;
    s32 i;
    EnJs* this = (EnJs*)thisx;

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->unk144, &D_060164B8, (AnimationHeader*)&D_06017E98, &this->unk1D4, &this->unk240,
                       0x12);
    Animation_PlayLoop(&this->unk144, (AnimationHeader*)&D_06017E98);
    Collider_InitAndSetCylinder(play, &this->unk188, &this->actor, &D_8096ABA0);
    this->actionFunc = func_8096971C;
    this->unk2BA = 0;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;
    cs = this->actor.cutscene;
    i = 0;
    while (i != 2) {
        this->unk2BE[i] = cs;
        if (cs != -1) {
            this->actor.cutscene = (s8)cs;
            cs = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
        i += 1;
    }
    this->unk2C2 = -1;
    switch (this->actor.params & 0xF) {
        case 0:
            this->unk2BA = 0;
            this->actionFunc = func_8096A6F4;
            Animation_PlayLoop(&this->unk144, &D_0601764C);
            func_8016566C(0x3CU);
            if ((gSaveContext.save.weekEventReg[0x54] & 0x20) != 0) {
                Inventory_DeleteItem(0x35, (s16)gItemSlots[0x35]);
                gSaveContext.save.weekEventReg[0x54] &= 0xDF;
                return;
            }
        default:
            return;
        case 1:
        case 2:
        case 3:
        case 4:
            this->unk2BA = this->actor.params & 0xF;
            func_80968B8C(this, play);
            this->actionFunc = func_80969B5C;
            func_80968A5C(this);
            if (func_809692A8((this->actor.params & 0xF) + 4) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            this->unk2BA = (this->actor.params & 0xF) - 4;
            this->actionFunc = func_8096A104;
            break;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Destroy.s")

void EnJs_Destroy(Actor* thisx, PlayState* play) {
    u32 paramsF;
    EnJs* this = (EnJs*)thisx;

    Collider_DestroyCylinder(play, &this->unk188);
    paramsF = this->actor.params & 0xF;
    switch (paramsF) {
        case 0:
            func_80165690();
            return;
        case 5:
        case 6:
        case 7:
        case 8:
            if (func_809692A8(paramsF) == 0) {
                func_80969400(this->actor.params & 0xF);
            }
        default:
            return;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968A5C.s")

void func_80968A5C(EnJs* this) {
    if (Rand_ZeroOne() < 0.5f) {
        Animation_MorphToLoop(&this->unk144, &D_06010CD8, -10.0f);
        this->unk2B4 = 5.0f;
    } else {
        Animation_MorphToLoop(&this->unk144, (AnimationHeader*)&D_06010880, -10.0f);
        this->unk2B4 = 2.5f;
    }
    this->unk2B8 &= ~4;
    this->unk2BC = Rand_ZeroFloat(40.0f) + 80.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B18.s")

void func_80968B18(EnJs* this) {
    Animation_MorphToLoop(&this->unk144, (AnimationHeader*)&D_06017E98, -10.0f);
    this->unk2B4 = 0.0f;
    this->unk2BC = Rand_ZeroFloat(20.0f) + 40.0f;
    this->unk2B8 |= 4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B8C.s")

void func_80968B8C(EnJs* this, PlayState* play) {
    // Path* sp2C;
    f32 sp18;
    Path* path;
    Vec2f test;
    // f32 temp_fv0;
    // f32 temp_fv1;
    f32 temp_fv0_2;
    // s32 temp_t2;
    s32 params;
    // s32 temp_v1;
    // u8 temp_a1;
    s32 phi_v1;
    s32 i;
    Vec2f* phi_a0;
    f32 phi_fa0;
    s32 phi_a1;

    params = (s32)(this->actor.params & 0xFC00) >> 0xA;
    phi_fa0 = 0.0f;
    if (params != 0x3F) {
        path = &play->setupPathList[params];
        this->unk2AC = path;
        if (path != NULL) {
            sp18 = 0.0f;
            // sp2C = path;
            // temp_a1 = path->count;
            // phi_v1 = 0;
            phi_a0 = Lib_SegmentedToVirtual(path->points);
            // phi_a1 = (s32)path->count;
            if (path->count > 0) {
                for (i = 0; i < path->count; i++) {
                    // while (temp_v1 < phi_a1) {
                    test.x = phi_a0->x - this->actor.world.pos.x; // temp_fv0
                    test.z = phi_a0->z - this->actor.world.pos.z; // temp_fv1
                    temp_fv0_2 = SQ(test.x) + SQ(test.z);
                    if (i != 0) {
                        this->unk2B0 = 0;
                        if ((temp_fv0_2 > i)) {
                            this->unk2B0 = i;
                        }
                        // phi_a1 = (s32)path->count;
                        // phi_fa0 = temp_fv0_2;
                    }
                    // temp_v1 = phi_v1 + 1;
                    // phi_v1 = temp_v1;
                    // phi_a0 += 6;
                }
            }
            // temp_t2 = this->unk2B0 + 1;
            this->unk2B0++;
            if (this->unk2B0 < path->count) {
                this->unk2AC = NULL;
            }
            this->unk2B0 = 0;
        }
    }
    return;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809691B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809692A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809694E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809695FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809696EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096971C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969898.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A38C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A6F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A9F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Draw.s")
