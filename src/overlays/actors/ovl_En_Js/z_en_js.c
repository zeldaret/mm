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
s32 func_80968B8C(EnJs* this, PlayState* play);  /* extern */
s32 func_809692A8(s32);                          /* extern */
void func_8096971C(EnJs* this, PlayState* play); /* extern */
void func_80969B5C(EnJs* this, PlayState* play); /* extern */
void func_8096A104(EnJs* this, PlayState* play); /* extern */
void func_8096A6F4(EnJs* this, PlayState* play);
s32 func_80969400(s32);
void func_80968B18(EnJs* this);
s32 func_80968CB8(EnJs* this);
s32 func_80968DD0(EnJs* this, PlayState* play);
s32 func_80968E38(s32 arg0);
void func_80969494(EnJs* this, PlayState* play);
void func_809694E8(EnJs* this, PlayState* play);
void func_80969530(EnJs* this, PlayState* play);
s32 func_809695FC(EnJs* this, PlayState* play);
void func_80969688(EnJs* this);
void func_809696EC(EnJs* this, s16 arg1);
void func_80969748(EnJs* this, PlayState* play);
void func_80969898(EnJs* this, PlayState* play);
void func_809691B8(s32 arg0, s32 arg1);
s32 func_8096933C(s32 arg0);
void func_80969AA0(EnJs* this, PlayState* play);
void func_80969C54(EnJs* this, PlayState* play);
void func_80969DA4(EnJs* this, PlayState* play);
void func_80969DA4(EnJs* this, PlayState* play);
void func_8096A080(EnJs* this, PlayState* play);
void func_8096A184(EnJs* this, PlayState* play);
void func_8096A1E8(EnJs* this, PlayState* play);
void func_8096A38C(EnJs* this, PlayState* play);
void func_8096A2C0(EnJs* this, PlayState* play);
void func_8096A9F4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
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
static u32 D_8096ABCC[5] = { 0x06006380, 0x06000690, 0x06003AD0, 0x06001D80, 0x06005020 };
static f32 D_8096ABE0[5] = { 1.0f, 0.5f, 0.5f, 0.48f, 0.45f };
static f32 D_8096ABF4[5] = { 60.0f, 0.0f, 0.0f, 0.0f, 0.0f };
static f32 D_8096AC08[5] = { -450.0f, 1400.0f, 1470.0f, 1670.0f, 1470.0f };
static f32 D_8096AC1C[5] = { 0.0f, 700.0f, 900.0f, 900.0f, 900.0f };
static Vec3f D_8096AC30 = { 500.0f, -500.0f, 0.0f };
#endif

extern ColliderCylinderInit D_8096ABA0;

extern UNK_TYPE D_06010880;
extern UNK_TYPE D_06016F58;
extern UNK_TYPE D_06017E98;
extern FlexSkeletonHeader D_060164B8;
extern AnimationHeader D_06010CD8;
extern AnimationHeader D_0601764C;

extern u32 D_8096ABCC[];
extern f32 D_8096ABE0[];
extern f32 D_8096ABF4[];
extern f32 D_8096AC08[];
extern f32 D_8096AC1C[];
extern Vec3f D_8096AC30;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Init.s")

void EnJs_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    s16 cs;
    s32 i;
    EnJs* this = (EnJs*)thisx;

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_060164B8, (AnimationHeader*)&D_06017E98, &this->unk1D4, &this->unk240,
                       0x12);
    Animation_PlayLoop(&this->skelAnime, (AnimationHeader*)&D_06017E98);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &D_8096ABA0);
    this->actionFunc = func_8096971C;
    this->unk2BA = 0;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;
    cs = this->actor.cutscene;
    i = 0;
    while (i != 2) {
        this->cutscenes[i] = cs;
        if (cs != -1) {
            this->actor.cutscene = (s8)cs;
            cs = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
        i++;
    }
    this->cutsceneIndex = -1;
    switch (this->actor.params & 0xF) {
        case 0:
            this->unk2BA = 0;
            this->actionFunc = func_8096A6F4;
            Animation_PlayLoop(&this->skelAnime, &D_0601764C);
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

    Collider_DestroyCylinder(play, &this->collider);
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
        Animation_MorphToLoop(&this->skelAnime, &D_06010CD8, -10.0f);
        this->unk2B4 = 5.0f;
    } else {
        Animation_MorphToLoop(&this->skelAnime, (AnimationHeader*)&D_06010880, -10.0f);
        this->unk2B4 = 2.5f;
    }
    this->unk2B8 &= ~4;
    this->unk2BC = Rand_ZeroFloat(40.0f) + 80.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B18.s")

void func_80968B18(EnJs* this) {
    Animation_MorphToLoop(&this->skelAnime, (AnimationHeader*)&D_06017E98, -10.0f);
    this->unk2B4 = 0.0f;
    this->unk2BC = Rand_ZeroFloat(20.0f) + 40.0f;
    this->unk2B8 |= 4;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B8C.s")

s32 func_80968B8C(EnJs* this, PlayState* play) {
    Path* path;
    f32 f0;
    f32 f2;
    s32 params;
    s32 i;
    f32 sp18;
    Vec3s* phi_a0;

    sp18 = 0.0f;
    params = ((s32)(this->actor.params & 0xFC00)) >> 0xA;
    if (params != 0x3F) {
        this->unk2AC = play->setupPathList + params;
        if (this->unk2AC != NULL) {
            path = this->unk2AC;

            phi_a0 = Lib_SegmentedToVirtual(path->points);

            for (i = 0; i < path->count; i++, phi_a0++) {
                f0 = phi_a0->x - this->actor.world.pos.x;
                f2 = phi_a0->z - this->actor.world.pos.z;
                f0 = SQ(f0) + SQ(f2);
                if (i == 0) {
                    sp18 = f0;
                    this->unk2B0 = 0;
                } else if (f0 < sp18) {
                    sp18 = f0;
                    this->unk2B0 = i;
                }
            }

            this->unk2B0++;
            if (this->unk2B0 >= path->count) {
                this->unk2B0 = 0;
            }
        }
    } else {
        this->unk2AC = NULL;
        this->unk2B0 = 0;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968CB8.s")

s32 func_80968CB8(EnJs* this) {
    Path* new_var3;
    s32 pad;
    f32 temp_fa0;
    f32 temp_fa1;
    Vec3s* temp_v1;
    if (this->unk2AC == NULL) {
        return 1;
    }
    new_var3 = this->unk2AC;
    temp_v1 = &((Vec3s*)Lib_SegmentedToVirtual(new_var3->points))[this->unk2B0];
    temp_fa0 = temp_v1->x - this->actor.world.pos.x;
    temp_fa1 = temp_v1->z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Atan2S(temp_fa0, temp_fa1);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, 0x7D0, 0xC8);
    if ((SQ(temp_fa0) + SQ(temp_fa1)) < 100.0f) {
        this->unk2B0++;
        if (this->unk2B0 >= new_var3->count) {
            this->unk2B0 = 0;
        }
        return 1;
    }
    Math_StepToF(&this->actor.speedXZ, this->unk2B4, 0.5f);
    return 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968DD0.s")

s32 func_80968DD0(EnJs* this, PlayState* play) {
    if ((this->actor.xzDistToPlayer < 100.0f) && (Player_IsFacingActor(&this->actor, 0x3000, play)) &&
        (Actor_IsFacingPlayer(&this->actor, 0x3000))) {
        return true;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968E38.s")

s32 func_80968E38(s32 arg0) {
    s32 i;
    s32 count;
    u8 mask;
    u8* maskMaskBit = gSaveContext.maskMaskBit;
    
    if (((arg0 < 0) || (arg0 > 8))) {
        return 0;
    }

    count = 0;
    
    arg0 *= 3;
    for (mask = 1, i = 0; i < 8; i++, mask <<= 1) {
        if (maskMaskBit[arg0] & mask) {
            count++;
        }
    }

    arg0++;
    for (mask = 1, i = 0; i < 8; i++, mask <<= 1) {
        if (maskMaskBit[arg0] & mask) {
            count++;
        }
    }

    arg0++;
    for (mask = 1, i = 0; i < 5; i++, mask <<= 1) {
        if (maskMaskBit[arg0] & mask) {
            count++;
        }
    }
   
    return count;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809691B8.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809692A8.s")

s32 func_809692A8(s32 arg0) {
    s32 phi_v0;

    phi_v0 = 0;
    switch (arg0) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (func_80968E38(arg0) < arg0) {
                return 0;
            }
            return 1;
        case 5:
        case 6:
        case 7:
        case 8:
            if (func_80968E38(arg0) < (arg0 - 4)) {
                return 0;
            }
            return 1;
        default:
            return phi_v0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096933C.s")
/*
s32 func_8096933C(s32 arg0) {
    s32 sp1C;
    s32 phi_v0;

    phi_v0 = 0;
    switch (arg0) {
    case 1:
    case 2:
    case 3:
    case 4:
        sp1C = func_80968F48();
        if ((func_80968E38(arg0) + sp1C) < arg0) {
            return 0;
        }
        return 1;
    case 5:
    case 6:
    case 7:
    case 8:
        sp1C = func_80968F48();
        if ((func_80968E38(arg0) + sp1C) < (arg0 - 4)) {
            return 0;
        }
        phi_v0 = 1;
    default:
        return phi_v0;
    }
}*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969400.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969494.s")

void func_80969494(EnJs* this, PlayState* play) {
    func_80968A5C(this);
    func_801477B4(play);
    this->actor.flags &= -0x101;
    this->actionFunc = func_80969B5C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809694E8.s")

void func_809694E8(EnJs* this, PlayState* play) {
    func_801477B4(play);
    this->actor.flags &= -0x101;
    this->actionFunc = func_8096A104;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969530.s")

void func_80969530(EnJs* this, PlayState* play) {
    func_801477B4(play);
    this->actor.flags &= -0x101;
    this->actionFunc = func_8096A6F4;
    if ((this->actor.home.rot.y == this->actor.shape.rot.y) && ((this->unk2B8 & 0x10) != 0)) {
        Animation_Change(&this->skelAnime, (AnimationHeader*)(&D_06016F58), -1.0f,
                         ((f32)Animation_GetLastFrame(&D_06016F58)) - 1.0f, 0.0f, (u8)2, -10.0f);
        this->unk2B8 &= 0xFFEF;
        this->unk2B8 |= 8;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809695FC.s")

s32 func_809695FC(EnJs* this, PlayState* play) {
    if (((s32)(this->actor.params & 0x3F0) >> 4) == 0x3F) {
        return 0;
    }
    play->sceneLoadFlag = 0x14;
    play->nextEntranceIndex = play->setupExitList[(s32)(this->actor.params & 0x3F0) >> 4];
    this->actionFunc = func_8096971C;
    play->msgCtx.unk11F10 = 0;
    gSaveContext.respawnFlag = -2;
    return 1;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969688.s")

void func_80969688(EnJs* this) {
    if (this->cutsceneIndex != -1) {
        if (ActorCutscene_GetCurrentIndex() == this->cutscenes[this->cutsceneIndex]) {
            ActorCutscene_Stop(this->cutscenes[this->cutsceneIndex]);
        }
        this->cutsceneIndex = -1;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809696EC.s")

void func_809696EC(EnJs* this, s16 arg1) {
    func_80969688(this);
    this->cutsceneIndex = arg1;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096971C.s")

void func_8096971C(EnJs* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969748.s")

void func_80969748(EnJs* this, PlayState* play) {
    s32 temp_v0;
    Player* player = GET_PLAYER(play);

    // player = play->actorCtx.player;
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 6, 0x1838, (s16)0x64);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (Message_GetState(&play->msgCtx) == 0x10) {
        temp_v0 = func_80123810(play);
        if (temp_v0 != 0) {
            this->actionFunc = func_80969898;
        }
        if (temp_v0 > 0) {
            func_801477B4(play);
            if ((temp_v0 >= 0x3A) && (temp_v0 < 0x4E)) {
                func_809691B8(temp_v0, this->actor.params & 0xF);
                Inventory_UnequipItem((s16)(temp_v0 - 4));
                if (func_809692A8(this->actor.params & 0xF) == 0) {
                    player->actor.textId = 0x2212;
                } else {
                    player->actor.textId = 0x2213;
                }
            } else if ((temp_v0 >= 0x4E) && (temp_v0 < 0x52)) {
                player->actor.textId = 0x2211;
            } else {
                player->actor.textId = 0x2210;
            }
        }
        if (temp_v0 < 0) {
            func_80151938(play, 0x2216U);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969898.s")

void func_80969898(EnJs* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 6, 0x1838, (s16)0x64);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if ((Message_ShouldAdvance(play) != 0) && (play->msgCtx.currentTextId == 0x2215)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(play, 0x2217U);
                        return;
                    case 1:
                        func_8019F230();
                        func_80151938(play, 0x2216U);
                        return;
                }
            } else {
                return;
            }
            break;
        case 5:
            if (Message_ShouldAdvance(play) != 0) {
                switch (play->msgCtx.currentTextId) {
                    case 0x220C:
                        this->unk2B8 |= 1;
                        if (func_8096933C(this->actor.params & 0xF) == 0) {
                            func_80151938(play, 0x220FU);
                            return;
                        }
                        func_80151938(play, 0x220DU);
                        return;
                    case 0x220D:
                    case 0x2213:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        return;
                    case 0x220E:
                        func_80151938(play, 0xFFU);
                        this->actionFunc = func_80969748;
                        return;
                    case 0x2210:
                    case 0x2211:
                    case 0x2212:
                        player->exchangeItemId = 0;
                        func_80151938(play, 0xFFU);
                        this->actionFunc = func_80969748;
                        return;
                    case 0x2214:
                    case 0x2217:
                        if (func_809695FC(this, play) == 0) {
                            func_80969494(this, play);
                            return;
                        }
                        break;
                    default:
                        func_80969494(this, play);
                        break;
                }
            }
            break;
    }
}
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969AA0.s")
/*

void func_80969AA0(EnJs* this, PlayState* play) {
    u16 phi_a3;

    if (gSaveContext.save.playerForm != 4) {
        phi_a3 = 0x220B;
    } else {
        phi_a3 = 0x2215;
        if ((this->unk2B8 & 1) != 0) {
            if (func_809692A8(this->actor.params & 0xF) == 0) {
                if (func_8096933C(this->actor.params & 0xF) == 0) {
                    phi_a3 = 0x220F;
                } else {
                    phi_a3 = 0x220E;
                }
            } else {
                phi_a3 = 0x220C;
            }
        }
    }
    Animation_MorphToLoop(&this->skelAnime, (AnimationHeader*)&D_06017E98, -10.0f);
    Message_StartTextbox(play, phi_a3, &this->actor);
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969B5C.s")

void func_80969B5C(EnJs* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (this->unk2BC > 0) {
        this->unk2BC--;
        if (this->unk2BC == 0) {
            if ((this->unk2B8 & 4) != 0) {
                func_80968A5C(this);
            } else {
                func_80968B18(this);
            }
        }
    }
    if (Actor_ProcessTalkRequest(&this->actor, &play->state) != 0) {
        this->actionFunc = func_80969898;
        this->actor.speedXZ = 0.0f;
        this->unk2B4 = 0.0f;
        func_80969AA0(this, play);
    } else if ((this->actor.xzDistToPlayer < 100.0f) && (Player_IsFacingActor(&this->actor, 0x3000, play) != 0)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
    func_80968CB8(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969C54.s")

void func_80969C54(EnJs* this, PlayState* play) {
    s32 temp_v0;
    Player* player = GET_PLAYER(play);

    // player = play->actorCtx.player;
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 6, 0x1838, (s16)0x64);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (Message_GetState(&play->msgCtx) == 0x10) {
        temp_v0 = func_80123810(play);
        if (temp_v0 != 0) {
            this->actionFunc = func_80969DA4;
        }
        if (temp_v0 > 0) {
            func_801477B4(play);
            if ((temp_v0 >= 0x3A) && (temp_v0 < 0x4E)) {
                func_809691B8(temp_v0, this->actor.params & 0xF);
                Inventory_UnequipItem((s16)(temp_v0 - 4));
                if (func_809692A8(this->actor.params & 0xF) == 0) {
                    player->actor.textId = 0x2221;
                } else {
                    player->actor.textId = 0x2222;
                }
            } else if ((temp_v0 >= 0x4E) && (temp_v0 < 0x52)) {
                player->actor.textId = 0x2220;
            } else {
                player->actor.textId = 0x221D;
            }
        }
        if (temp_v0 < 0) {
            func_80151938(play, 0x221EU);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969DA4.s")

void func_80969DA4(EnJs* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 6, 0x1838, (s16)0x64);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if ((Message_ShouldAdvance(play) != 0) &&
                (((play->msgCtx.currentTextId == 0x2219)) || (play->msgCtx.currentTextId == 0x221E))) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        if (func_809695FC(this, play) == 0) {
                            func_809694E8(this, play);
                            return;
                        }
                        break;
                    case 1:
                        func_8019F230();
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        return;
                }
            } else {
                return;
            }
            break;
        case 5:
            if (Message_ShouldAdvance(play) != 0) {
                switch (play->msgCtx.currentTextId) {
                    case 0x221B:
                        if (func_8096933C(this->actor.params & 0xF) == 0) {
                            func_80151938(play, 0x2219U);
                            return;
                        }
                        func_80151938(play, 0x221CU);
                        return;
                    case 0x2224:
                    case 0x2226:
                    case 0x2228:
                    case 0x222A:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        return;
                    case 0x2225:
                    case 0x2227:
                    case 0x2229:
                    case 0x222B:
                        if (func_809695FC(this, play) == 0) {
                            func_809694E8(this, play);
                            return;
                        }
                        break;
                    case 0x2222:
                        player->exchangeItemId = 0;
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        return;
                    case 0x2223:
                        switch (this->actor.params & 0xF) {
                            case 5:
                                func_80151938(play, 0x2224U);
                                return;
                            case 6:
                                func_80151938(play, 0x2226U);
                                return;
                            case 7:
                                func_80151938(play, 0x2228U);
                                return;
                            case 8:
                                func_80151938(play, 0x222AU);
                                return;
                        }
                        break;
                    case 0x221C:
                        func_80151938(play, 0xFFU);
                        this->actionFunc = func_80969C54;
                        return;
                    case 0x221D:
                    case 0x2220:
                    case 0x2221:
                        player->exchangeItemId = 0;
                        func_80151938(play, 0xFFU);
                        this->actionFunc = func_80969C54;
                        return;
                    default:
                        func_809694E8(this, play);
                        break;
                }
            }
            break;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A080.s")

void func_8096A080(EnJs* this, PlayState* play) {
    u16 phi_a1;

    if (gSaveContext.save.playerForm != 4) {
        phi_a1 = 0x2218U;
    } else {
        phi_a1 = 0x221BU;
        if ((this->unk2B8 & 1) != 0) {
            if (func_8096933C(this->actor.params & 0xF) == 0) {
                phi_a1 = 0x2219U;
            } else {
                phi_a1 = 0x221CU;
            }
        } else {
            this->unk2B8 |= 1;
        }
    }
    Message_StartTextbox(play, phi_a1, &this->actor);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A104.s")

void func_8096A104(EnJs* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80969DA4;
        func_8096A080(this, play);
    } else {
        if (func_80968DD0(this, play)) {
            func_800B8614(&this->actor, play, 120.0f);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A184.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A1E8.s")

void func_8096A1E8(EnJs* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        Animation_MorphToLoop(&this->skelAnime, (AnimationHeader*)&D_06017E98, 0.0f);
    }
    if (Actor_ProcessTalkRequest(&this->actor, play) != 0) {
        this->actor.flags &= 0xFFFEFFFF;
        this->actionFunc = func_8096A38C;
        Message_StartTextbox(play, 0x2208U, &this->actor);
        gSaveContext.save.weekEventReg[0x54] |= 0x20;
        func_809696EC(this, 0);
        return;
    }
    func_800B8500(&this->actor, play, 1000.0f, 1000.0f, -1);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A2C0.s")

void func_8096A2C0(EnJs* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_MorphToLoop(&this->skelAnime, (AnimationHeader*)&D_06017E98, 0.0f);
    }
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actor.flags |= 0x10000;
        this->actionFunc = func_8096A1E8;
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, -1);
    } else {
        Actor_PickUp(&this->actor, play, 0x7B, 10000.0f, 1000.0f);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A38C.s")
/*
void func_8096A38C(EnJs *this, PlayState *play) {
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        Animation_MorphToLoop(&this->skelAnime, (AnimationHeader *) &D_06017E98, 0.0f);
        this->unk2B8 |= 2;
    }
    //temp_v0 = Message_GetState(&play->msgCtx);
    switch (Message_GetState(&play->msgCtx)) {
    case 4:
        if (Message_ShouldAdvance(play)) {
            switch (play->msgCtx.choiceIndex) {
            case 0:
                func_8019F208();
                break;
            case 1:
                func_8019F230();
                break;
            }
            switch (play->msgCtx.currentTextId) {
            case 0x21FC:
                if (play->msgCtx.choiceIndex != 0) {
                    if (play->msgCtx.currentTextId == 1) {
                        return;
                    }
                    func_80151938(play, 0x21FDU);
                    return;
                }
                func_80151938(play, 0x21FEU);
                Animation_MorphToPlayOnce(&this->skelAnime, (AnimationHeader *) &D_06016F58, -5.0f);
                this->unk2B8 |= 0x10;
                return;
            case 0x21FE:

                if (play->msgCtx.currentTextId != 0) {
                    if (play->msgCtx.currentTextId == 1) {
                        return;
                    }
                    func_80151938(play, 0x21FFU);
                    return;
                }
                func_80151938(play, 0x2200U);
                func_809696EC(this, 0);
                return;
            case 0x2203:
                if (play->msgCtx.currentTextId != 0) {
                    if (play->msgCtx.currentTextId != 1) {
                        return;
                    }
                    func_80151938(play, 0x2204U);
                    return;
                }
                func_80151938(play, 0x2205U);
                Animation_MorphToPlayOnce(&this->skelAnime, (AnimationHeader *) &D_06016F58, -5.0f);
                this->unk2B8 |= 0x10;
                return;
            }
        } else {
            return;
        }
        break;
    case 5:
        if (Message_ShouldAdvance(play) != 0) {
            switch (play->msgCtx.currentTextId) {
            case 0x2202:
            case 0x2205:
            case 0x2206:
            case 0x2209:
                func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                return;
            case 0x2200:
            case 0x2208:
                func_809696EC(this, 1);
                func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                return;
            case 0x2207:
                if (gSaveContext.save.inventory.items[gItemSlots[0x35]] == 0x35) {
                    func_80151938(play, 0x2208U);
                    func_809696EC(this, 0);
                    return;
                }
                func_801477B4(play);
                this->actionFunc = func_8096A2C0;
                func_8096A2C0(this, play);
                return;
            case 0x2201:
            case 0x220A:
                if (func_809695FC(this, play) == 0) {
                    func_80969530(this, play);
                    return;
                }
                break;
            default:
                func_80969530(this, play);
                break;
            }
        }
        break;
    }
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A6F4.s")

void func_8096A6F4(EnJs* this, PlayState* play) {
    PosRot* new_var = &this->actor.home;

    if (this->actor.shape.rot.y != (*new_var).rot.y) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 2, 0x400, (s16)0x100);
        if ((this->actor.shape.rot.y == (*new_var).rot.y) && ((this->unk2B8 & 0x10) != 0)) {
            Animation_Change(&this->skelAnime, (AnimationHeader*)(&D_06016F58), -1.0f,
                             ((f32)Animation_GetLastFrame(&D_06016F58)) - 1.0f, 0.0f, (u8)2, -10.0f);
            this->unk2B8 &= 0xFFEF;
            this->unk2B8 |= 8;
        }
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
    if (SkelAnime_Update(&this->skelAnime) != 0) {
        Animation_MorphToLoop(&this->skelAnime, &D_0601764C, -10.0f);
        this->unk2B8 &= 0xFFF7;
    }
    if (Actor_ProcessTalkRequest(&this->actor, &play->state) != 0) {
        this->actionFunc = func_8096A38C;
        this->unk2B8 &= 0xFFFD;
        func_8096A184(this, play);
        return;
    }
    if (((((this->unk2B8 & 8) == 0) && (this->actor.xzDistToPlayer < 100.0f)) &&
         (Player_IsFacingActor(&this->actor, 0x3000, play) != 0)) &&
        (Actor_IsFacingPlayer(&this->actor, 0x1000) != 0)) {
        func_800B8614(&this->actor, play, 120.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Update.s")

void EnJs_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnJs* this = THIS;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 25.0f, 40.0f, 5U);
    this->actionFunc(this, play);
    if ((this->cutsceneIndex != -1) && (ActorCutscene_GetCurrentIndex() != this->cutscenes[this->cutsceneIndex])) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->cutscenes[this->cutsceneIndex]);
        } else {
            if (ActorCutscene_GetCanPlayNext(this->cutscenes[this->cutsceneIndex])) {
                ActorCutscene_Start(this->cutscenes[this->cutsceneIndex], &this->actor);
            } else {
                ActorCutscene_SetIntentToPlay(this->cutscenes[this->cutsceneIndex]);
            }
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A9F4.s")

void func_8096A9F4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    s32 pad;
    EnJs* this = THIS;

    if (limbIndex == 0xA) {
        Matrix_MultVec3f(&D_8096AC30, &thisx->focus.pos);
        if ((this->unk2BA >= 0) && (this->unk2BA < 5)) {
            OPEN_DISPS(play->state.gfxCtx);

            if (this->unk2BA != 0) {
                Matrix_Scale(D_8096ABE0[this->unk2BA], D_8096ABE0[this->unk2BA], D_8096ABE0[this->unk2BA],
                             MTXMODE_APPLY);
                Matrix_RotateZYX(0, -0x4000, -0x36B0, MTXMODE_APPLY);
            }
            Matrix_Translate(D_8096ABF4[this->unk2BA], D_8096AC08[this->unk2BA], D_8096AC1C[this->unk2BA],
                             MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, D_8096ABCC[this->unk2BA]);
        }
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Draw.s")

void EnJs_Draw(Actor* thisx, PlayState* play) {
    EnJs* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32)this->skelAnime.dListCount,
                          NULL, func_8096A9F4, &this->actor);
}