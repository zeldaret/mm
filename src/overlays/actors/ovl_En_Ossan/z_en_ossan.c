#include "z_en_ossan.h"

#define FLAGS 0x00000019

#define THIS ((EnOssan*)thisx)

void EnOssan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808ABE58(Actor* thisx, GlobalContext* globalCtx); // Draw
void func_808ABF30(Actor* thisx, GlobalContext* globalCtx); // Draw

s32 func_808ABCD0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_808ABD60(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_808AB52C(GlobalContext* globalCtx, EnOssan* this, f32 arg2, f32 arg3, f32 arg4, u8 arg5);
void func_808AB928(GlobalContext* globalCtx, EnOssan* this);
s32 func_808ABD10(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_808ABE18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_808AB78C(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t,
                         f32 dx, f32 dy);

void func_808AB16C(EnOssan *this, GlobalContext* globalCtx);
void func_808A812C(EnOssan *this);
void func_808A80A0(EnOssan *this, EnOssanActionFunc action);
void func_808AB404(EnOssan *this, GlobalContext* globalCtx);
void func_808AACE0(EnOssan *this);
void func_808A8798(EnOssan *this, GlobalContext* globalCtx);
void func_808A82F4(EnOssan *this, GlobalContext* globalCtx, EnOssanUnkStruct *arg3);
void func_808AADB4(EnOssan *this, GlobalContext* globalCtx);
void func_808AAE1C(EnOssan *this, GlobalContext* globalCtx);
void func_808AAD14(EnOssan* this);
void func_808A890C(EnOssan* this, GlobalContext* globalCtx);
void func_808AB0B0(EnOssan* this);
s32 func_808AAE84(EnOssan* this, GlobalContext* globalCtx);
void func_808A86A8(GlobalContext* globalCtx, EnOssan* this, u8 arg2);
s32 func_808AAFB0(EnOssan* this, GlobalContext* globalCtx);
void func_808A8EEC(EnOssan* this, GlobalContext* globalCtx);
void func_808A8708(GlobalContext* globalCtx, EnOssan* this);
void func_808A8218(EnOssan* this, GlobalContext* globalCtx);
void func_808A8500(GlobalContext* globalCtx, EnOssan* this);
s32 func_808A85FC(EnOssan* this, GlobalContext* globalCtx, Input* input);
void func_808A91B4(EnOssan* this, GlobalContext* globalCtx);
void func_808A9400(EnOssan* this, GlobalContext* globalCtx);
void func_808A94FC(EnOssan* this, GlobalContext* globalCtx);
u8 func_808A8CC0(EnOssan* this, u8 arg1);
void func_808A849C(GlobalContext* globalCtx, EnOssan* this);
void func_808A98E4(EnOssan* this, GlobalContext *globalCtx);
void func_808A9AB8(EnOssan* this, GlobalContext *globalCtx);
s32 func_808AA85C(EnOssan* this);
s32 func_808A980C(GlobalContext* globalCtx, EnOssan* this, Input* input);
u8 func_808A8DF8(EnOssan *this, u8 arg1, u8 arg2);
void func_808A875C(GlobalContext* globalCtx, EnOssan* this);
u8 func_808A8E84(EnOssan *this, u8 arg1, u8 arg2);
void func_808AA6D8(EnOssan *this);
s32 func_808A80AC(GlobalContext* globalCtx);
void func_808AA0C8(EnOssan* this, GlobalContext* globalCtx);
void func_808A9C8C(EnOssan* this, GlobalContext* globalCtx);
s32 func_808AA7C0(EnOssan* this);
s32 func_808A8644(EnOssan* this, GlobalContext* globalCtx, Input* input);
void func_808A9E98(GlobalContext* globalCtx, EnOssan* this);
void func_808A9D64(GlobalContext* globalCtx, EnOssan* this);
void func_808A9E5C(GlobalContext *globalCtx, EnOssan* this, u16 arg2);
void func_808A9E20(GlobalContext *globalCtx, EnOssan* this, u16 arg2);
void func_808AA2C8(EnOssan* this, GlobalContext* globalCtx);
void func_808AA224(EnOssan* this, GlobalContext* globalCtx);
void func_808AA1B0(EnOssan* this, GlobalContext* globalCtx);
void func_808AA33C(EnOssan* this, GlobalContext* globalCtx);
void func_808AA5E8(EnOssan* this, GlobalContext* globalCtx);
void func_808AA404(EnOssan* this, GlobalContext* globalCtx);
void func_808AA79C(EnOssan* this);
void func_808A8B74(GlobalContext* globalCtx, EnOssan* this);
void func_808AA8E8(EnOssan* this);
void func_808AAA64(EnOssan* this);
s32 func_808A90A4(EnOssan* this, GlobalContext* globalCtx);
void func_808A935C(EnOssan* this, GlobalContext* globalCtx);
void func_808AAB30(EnOssan* this);
void func_808A95F8(EnOssan *this);

/*
const ActorInit En_Ossan_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOssan),
    (ActorFunc)EnOssan_Init,
    (ActorFunc)EnOssan_Destroy,
    (ActorFunc)EnOssan_Update,
    (ActorFunc)NULL,
};
*/

extern UNK_TYPE D_0401F740;

extern UNK_TYPE D_0401F8C0;

extern UNK_TYPE D_0401F7C0;

extern FlexSkeletonHeader D_06013320;

extern AnimationHeader D_06012C34;

extern FlexSkeletonHeader D_060028A0;

extern AnimationHeader D_06009D34;

extern s16 D_808AC1C0[];
//static s16 D_808AC1C0[] = { 0x01AB, 0x00C2 }

extern InitChainEntry D_808AC288[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};
*/

extern EnOssanActionFunc D_808AC2A4[];
//static EnOssanActionFunc D_808AC2A4[] = {func_808AADB4, func_808AAE1C}

extern u16 D_808AC254[][2];

extern u16 D_808AC274[][2];

extern EnOssanUnkStruct D_808AC1D4[8][8];

extern f32 D_808AC1CC[];

extern EnOssanAnimation* D_808AC1C4[];

extern Vec3f D_808AC28C[];

extern UNK_PTR D_808AC2B8[][3];

extern Vec3f D_808AC2AC;

void func_808A80A0(EnOssan *this, EnOssanActionFunc action) {
    this->actionFunc = action;
}

s32 func_808A80AC(GlobalContext *globalCtx) {
    MessageContext *msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12021 == 0x10 || msgCtx->unk12021 == 0x11) {
        return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A);
    }
    return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) || 
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B) || 
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CUP);
}

void func_808A812C(EnOssan *this) {
    switch(gSaveContext.day) {
        case 1:
        case 2:
            if (gSaveContext.time < 0xE556 && gSaveContext.time >= 0x4001) {
                if (this->actor.params != 0) {
                    Actor_MarkForDeath(&this->actor);
                }
            } else if (this->actor.params == 0) {
                Actor_MarkForDeath(&this->actor);
            }
            break;
        case 3:
            if (this->actor.params == 0) {
                Actor_MarkForDeath(&this->actor);
            }
            if (!(gSaveContext.time < 0xEAAB && gSaveContext.time >= 0x4000)) {
                if (this->actor.params != 0) {
                    Actor_MarkForDeath(&this->actor);
                }
            }
            break;
    }
}

void func_808A8218(EnOssan *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    if (this->actor.params == 1) {
        if (player->unk14B == 2) {
            Math_SmoothStepToS(&this->unk406, this->unk2C6.y, 3, 2000, 0);
        } else if (this->unk40A & 1) {
            Math_SmoothStepToS(&this->unk406, 8000, 3, 2000, 0);
        } else {
            Math_SmoothStepToS(&this->unk406, this->unk2C6.y, 3, 2000, 0);
            if (ABS_ALT(this->unk406 - this->unk2C6.y) < 16) {
                this->unk40A |= 1;
            }
        }
    }
}

void func_808A82F4(EnOssan *this, GlobalContext *globalCtx, EnOssanUnkStruct *arg3) {
    s32 i;

    for(i=0; i<8; i++, arg3++) {
        if (arg3->unk0 < 0) {
            this->unk1E8[i] = NULL;
        } else {
            this->unk1E8[i] = (EnGirlA*) Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA, arg3->unk2, arg3->unk4, arg3->unk6, 0, 0, 0, arg3->unk0);
        }
    }
}

void EnOssan_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnOssan *this = THIS;
    s16 id;

    //! @bug Condition is impossible
    if (this->actor.params >= 2 && this->actor.params < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    id = D_808AC1C0[this->actor.params];
    this->unk1DE = Object_GetIndex(&globalCtx->objectCtx, id);
    if (this->unk1DE < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    func_808A812C(this);
    Actor_ProcessInitChain(&this->actor, D_808AC288);
    func_808A80A0(this, func_808AB16C);
}

void EnOssan_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnOssan *this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_808A849C(GlobalContext *globalCtx, EnOssan *this) {
    s16 sp1E;
    s16 sp1C;

    func_800B8898(globalCtx, &this->unk1E8[this->unk236]->actor, &sp1E, &sp1C);
    this->unk214 = sp1E;
    this->unk218 = sp1C;
}

void func_808A8500(GlobalContext *globalCtx, EnOssan *this) {
    ActorPlayer *player = PLAYER;

    func_800B84D0(&this->actor, globalCtx);
    globalCtx->msgCtx.unk11F23 = 0x43;
    globalCtx->msgCtx.unk12024 = 4;
    Interface_ChangeAlpha(0x32);
    this->unk235 = 0;
    this->unk238.isEnabled = 0;
    this->unk270.isEnabled = 0;
    player->unkA70 &= ~0x20000000;
    globalCtx->interfaceCtx.unk222 = 0;
    globalCtx->interfaceCtx.unk224 = 0;
    if (this->unk2C2 == 2) {
        ActorCutscene_Stop(this->unk2C0);
        this->unk2C2 = 0;
    }
    if (this->actor.params == 0) {
        func_808A80A0(this, func_808A890C);
    } else {
        func_808A80A0(this, func_808A8798);
    }
}

s32 func_808A85FC(EnOssan *this, GlobalContext *globalCtx, Input *input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        func_808A8500(globalCtx, this);
        return 1;
    }
    return 0;
}

s32 func_808A8644(EnOssan *this, GlobalContext *globalCtx, Input *input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        this->actionFunc = this->actionFunc2;
        func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
        return 1;
    }
    return 0;
}

void func_808A86A8(GlobalContext *globalCtx, EnOssan *this, u8 arg2) {
    func_8011552C(globalCtx, 0x10);
    if (arg2 == 0) {
        func_808A80A0(this, func_808A8EEC);
    } else {
        func_808A8708(globalCtx, this);
    }
}

void func_808A8708(GlobalContext *globalCtx, EnOssan *this) {
    func_808A80A0(this, func_808A91B4);
    func_80151938(globalCtx, 0x640);
    func_8011552C(globalCtx, 6);
    this->unk270.isEnabled = 1;
    this->unk238.isEnabled = 1;
}

void func_808A875C(GlobalContext *globalCtx, EnOssan *this) {
    play_sound(0x4809);
    this->unk235 = 0;
    func_808A80A0(this, func_808A9C8C);
}

void func_808A8798(EnOssan *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    func_8013D9C8(globalCtx, this->unk2D2, this->unk2F8, 0x13);
    if (func_800B84D0(&this->actor, globalCtx)) {
        player->unkA70 |= 0x20000000;
        func_808A80A0(this, func_808A890C);
        if (this->unk2C2 == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk2C0 = this->unk2B8;
            ActorCutscene_SetIntentToPlay(this->unk2C0);
            this->unk2C2 = 1;
        }
    } else {
        if (this->actor.xzDistToPlayer < 100.0f && (player->base.world.pos.x >= -40.0f && player->base.world.pos.x <= 40.0f) && (player->base.world.pos.z >= -91.0f && player->base.world.pos.z <= -60.0f)) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
        if (this->actor.params == 1) {
            Math_SmoothStepToS(&this->unk406, 8000, 3, 2000, 0);
        }
    }
}

#if NON_MATCHING
// Matches but jumptable is in late rodata
void func_808A890C(EnOssan *this, GlobalContext *globalCtx) {
    EnOssanAnimation *animations = D_808AC1C4[this->actor.params];
    s16 curFrame = this->skelAnime.animCurrentFrame;
    s16 frameCount;

    frameCount = SkelAnime_GetFrameCount(&animations[this->unk402].animationSeg->common);
    if (this->unk402 == 3) {
        frameCount = 0;
    }
    if (this->unk2C2 == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk2C0)) {
            ActorCutscene_StartAndSetFlag(this->unk2C0, &this->actor);
            this->unk2C2 = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk2C0);
        }
    }
    if (this->actor.params == 0) {
        if (curFrame == frameCount) {
            switch(this->unk402) {
                case 1:
                    this->unk402 = 2;
                    func_8013BC6C(&this->skelAnime, animations, 2);
                    break;
                case 2:
                    func_808AB0B0(this);
                    this->unk2C4 = func_808AAE84(this, globalCtx);
                    func_8013BC6C(&this->skelAnime, animations, this->unk402);
                    break;
                case 4:
                case 6:
                case 8:
                case 10:
                    this->unk402++;
                    func_8013BC6C(&this->skelAnime, animations, this->unk402);
                    func_801518B0(globalCtx, this->unk2C4, &this->actor);
                    func_808A86A8(globalCtx, this, 0);
                    break;
                case 5:
                case 7:
                case 9:
                case 11:
                    this->unk402 = 3;
                    func_8013BC6C(&this->skelAnime, animations, 3);
                    break;
                case 3:
                    this->unk402 = 1;
                    func_8013BC6C(&this->skelAnime, animations, 1);
                    func_808A80A0(this,func_808A8798);
                    break;
                default:
                    this->unk402 = 1;
                    func_8013BC6C(&this->skelAnime, animations, 1);
                    func_808A80A0(this, func_808A8798);
            }
        }
    } else {
        func_808AB0B0(this);
        this->unk2C4 = func_808AAFB0(this, globalCtx);
        func_801518B0(globalCtx, this->unk2C4, &this->actor);
        func_808A86A8(globalCtx, this, 0);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A890C.asm")
#endif

void func_808A8B74(GlobalContext *globalCtx, EnOssan *this) {
    Input* controller1 = &globalCtx->state.input[0];
    s8 temp_v0 = controller1->rel.stick_x;
    s8 temp_v1 = controller1->rel.stick_y;

    this->unk210 = this->unk211 = 0;

    if (this->unk208 == 0) {
        if (temp_v0 >= 0x1F || temp_v0 < -0x1E) {
            this->unk208 = temp_v0;
            this->unk210 = 1;
        }
    } else if (temp_v0 < 0x1F && temp_v0 >= -0x1E) {
        this->unk208 = 0;
    } else {
        if ((this->unk208 * temp_v0) < 0) {
            this->unk208 = temp_v0;
            this->unk210 = 1;
        } else {
            this->unk208 += temp_v0;
            if (this->unk208 >= 0x7D1) {
                this->unk208 = 0x7D0;
            } else if (this->unk208 < -0x7D0) {
                this->unk208 = -0x7D0;
            }
        }
    }
    if (this->unk20C == 0) {
        if (temp_v1 >= 0x1F || temp_v1 < -0x1E) {
            this->unk20C = temp_v1;
            this->unk211 = 1;
        }
    } else {
        if (temp_v1 < 0x1F && temp_v1 >= -0x1E) {
            this->unk20C = 0;
        } else {;
            if ((this->unk20C * temp_v1) < 0) {
                this->unk20C = temp_v1;
                this->unk211 = 1;
            } else {
                this->unk20C += temp_v1;
                if (this->unk20C >= 0x7D1) {
                    this->unk20C = 0x7D0;
                } else if (this->unk20C < -0x7D0) {
                    this->unk20C = -0x7D0;
                }
            }
        }
    }
}

u8 func_808A8CC0(EnOssan *this, u8 arg1) {
    u8 i;

    if (this->unk236 & 1) {
        for(i = arg1 + 1; i < arg1 + 4; i += 2) {
            if (this->unk1E8[i] != NULL) {
                return i;
            }
        }
        for(i = arg1; i < arg1 + 4; i += 2) {
            if (this->unk1E8[i] != NULL) {
                return i;
            }
        }
    } else {
        for(i = arg1; i < arg1 + 4; i += 2) {
            if (this->unk1E8[i] != NULL) {
                return i;
            }
        }
        for(i= arg1 + 1; i < arg1 + 4; i += 2) {
            if (this->unk1E8[i] != NULL) {
                return i;
            }
        }
    }
    return 0xFF;
}

#if NON_MATCHING
//Weird for loop
u8 func_808A8DF8(EnOssan *this, u8 arg1, u8 arg2) {
    u8 end = arg2 + 4;
    if(arg1 >= arg2 && arg1 < end){
        for(arg1 -= 2; arg1 >= arg2 && arg1 < end; arg1 -= 2) {
            if(this->unk1E8[arg1] != NULL) {
                return arg1;
            }
        }
    }
    return 0xFF;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8DF8.asm")
#endif

#if NON_MATCHING
//Weird for loop
u8 func_808A8E84(EnOssan *this, u8 arg1, u8 arg2) {
    if (arg1 < arg2) {
        for(arg1 += 2; arg1 < arg2; arg1 += 2) {
            if (arg1 < arg2 && this->unk1E8[arg1] != NULL) {
                return arg1;
            }
        }
    }
    return 0xFF;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A8E84.asm")
#endif

void func_808A8EEC(EnOssan *this, GlobalContext *globalCtx) {
    EnOssanAnimation *animations = D_808AC1C4[this->actor.params];
    u8 sp33 = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    ActorPlayer *player = PLAYER;

    func_808A8218(this, globalCtx);
    if (sp33 == 5 && func_80147624(globalCtx)) {
        if (this->unk402 == 9 && this->actor.params == 1) {
            this->unk402 = 1;
            func_8013BC6C(&this->skelAnime, animations, 1);
        }
        this->unk40A &= ~1;
        if (player->unk14B == 3) {
            func_808A8500(globalCtx, this);
        } else {
            if (this->unk40A & 2) {
                this->unk40A &= ~2;
                func_808A8500(globalCtx, this);
            } else if (!func_808A85FC(this, globalCtx, globalCtx->state.input)) {
                func_808A8708(globalCtx, this);
            } else {
                return;
            }
        }
    }
    if (sp33 == 10 && this->actor.params == 1 && player->unk14B == 2 && func_80147624(globalCtx)) {
        this->unk402 = 9;
        func_8013BC6C(&this->skelAnime, animations, 9);
    }
    if (this->unk402 == 11 && func_801378B8(&this->skelAnime, 18.0f)) {
        Audio_PlayActorSound2(&this->actor, 0x2993);
    }  
}

s32 func_808A90A4(EnOssan *this, GlobalContext *globalCtx) {
    EnOssanAnimation *animations = D_808AC1C4[this->actor.params];
    ActorPlayer *player = PLAYER;

    switch(globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            if (this->actor.params == 1 && player->unk14B == 2) {
                this->unk402 = 9;
                func_8013BC6C(&this->skelAnime, animations, 9);
            }
            func_808A80A0(this, func_808A935C);
            func_80151938(globalCtx, D_808AC254[1][this->actor.params]);
            func_8011552C(globalCtx, 6);
            this->unk238.isEnabled = 0;
            this->unk270.isEnabled = 0;
            return 1;
        case 1:
            func_8019F230();
            func_808A8500(globalCtx, this);
            return 1;
    }
    return 0;
}

void func_808A91B4(EnOssan *this, GlobalContext *globalCtx) {
    u8 tmp = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    ActorPlayer *player = PLAYER;

    if (this->unk2C2 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk2C0 = this->unk2B8;
        ActorCutscene_SetIntentToPlay(this->unk2C0);
        this->unk2C2 = 1;
    } else {
        if (tmp == 4) {
            func_8011552C(globalCtx, 6);
            if (!func_808A85FC(this, globalCtx, globalCtx->state.input) && (!func_80147624(globalCtx) || !func_808A90A4(this, globalCtx))) {
                if (this->unk208 < 0) {
                    tmp = func_808A8CC0(this, 4);
                    if (tmp != 255) {
                        this->unk236 = tmp;
                        func_808A80A0(this, func_808A9400);
                        func_8011552C(globalCtx, 6);
                        this->unk238.isEnabled = 0;
                        play_sound(0x4809);
                    }
                } else if (this->unk208 > 0) {
                    tmp = func_808A8CC0(this, 0);
                    if (tmp != 255) {
                        this->unk236 = tmp;
                        func_808A80A0(this, func_808A94FC);
                        func_8011552C(globalCtx, 6);
                        this->unk270.isEnabled = 0;
                        play_sound(0x4809);
                    }
                }
            } else {
                return;
            }
        }
        if (this->actor.params == 1 && player->unk14B != 2) {
            Math_SmoothStepToS(&this->unk406, 8000, 3, 2000, 0);
        }
    }
}

void func_808A935C(EnOssan *this, GlobalContext *globalCtx) {
    EnOssanAnimation *animations = D_808AC1C4[this->actor.params];

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->unk402 == 9 && this->actor.params == 1) {
            this->unk402 = 1;
            func_8013BC6C(&this->skelAnime, animations, 1);
        }
        func_808A8708(globalCtx, this);
    }
}

void func_808A9400(EnOssan *this, GlobalContext *globalCtx) {
    if (this->unk2C2 == 2) {
        ActorCutscene_Stop(this->unk2C0);
        this->unk2C2 = 0;
    }
    if (this->unk2C2 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk2C0 = this->unk2BA;
        ActorCutscene_SetIntentToPlay(this->unk2C0);
        this->unk2C2 = 1;
    } else {
        if (this->unk2C2 == 1) {
            if (ActorCutscene_GetCanPlayNext(this->unk2C0)) {
                ActorCutscene_StartAndSetFlag(this->unk2C0, &this->actor);
                this->unk2C2 = 2;
                func_808A849C(globalCtx, this);
                func_808A80A0(this, func_808A98E4);
                func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
            } else {
                ActorCutscene_SetIntentToPlay(this->unk2C0);
            }
        }
        this->unk208 = 0;
    }
}

void func_808A94FC(EnOssan *this, GlobalContext *globalCtx) {
    if (this->unk2C2 == 2) {
        ActorCutscene_Stop(this->unk2C0);
        this->unk2C2 = 0;
    }
    if (this->unk2C2 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk2C0 = this->unk2BC;
        ActorCutscene_SetIntentToPlay(this->unk2C0);
        this->unk2C2 = 1;
    } else {
        if (this->unk2C2 == 1) {
            if (ActorCutscene_GetCanPlayNext(this->unk2C0)) {
                ActorCutscene_StartAndSetFlag(this->unk2C0, &this->actor);
                this->unk2C2 = 2;
                func_808A849C(globalCtx, this);
                func_808A80A0(this, func_808A9AB8);
                func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
            } else {
                ActorCutscene_SetIntentToPlay(this->unk2C0);
            }
        }
        this->unk208 = 0;
    }
}

void func_808A95F8(EnOssan* this) {
    u8 curTemp = this->unk236;
    u8 curScanTemp;

    if (this->unk20C < 0) {
        curTemp &= 0xFE;
        if (this->unk1E8[curTemp] != NULL) {
            this->unk236 = curTemp;
            return;
        }
        // cursorIndex on right shelf
        if (curTemp < 4) {
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 4) {
                curScanTemp = 0;
            }
            while (curScanTemp != curTemp) {
                if (this->unk1E8[curScanTemp] != NULL) {
                    this->unk236 = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 4) {
                    curScanTemp = 0;
                }
            }
        } else {
            // cursorIndex on left shelf
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 8) {
                curScanTemp = 4;
            }
            while (curScanTemp != curTemp) {
                if (this->unk1E8[curScanTemp] != NULL) {
                    this->unk236 = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 8) {
                    curScanTemp = 4;
                }
            }
        }
    } else if (this->unk20C > 0) {
        curTemp |= 1;
        if (this->unk1E8[curTemp] != NULL) {
            this->unk236 = curTemp;
            return;
        }
        // cursorIndex on right shelf
        if (curTemp < 4) {
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 4) {
                curScanTemp = 1;
            }
            while (curScanTemp != curTemp) {
                if (this->unk1E8[curScanTemp] != NULL) {
                    this->unk236 = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 4) {
                    curScanTemp = 1;
                }
            }
        } else {
            // cursorIndex on left shelf
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 8) {
                curScanTemp = 5;
            }
            while (curScanTemp != curTemp) {
                if (this->unk1E8[curScanTemp] != NULL) {
                    this->unk236 = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 8) {
                    curScanTemp = 5;
                }
            }
        }
    }
}

s32 func_808A980C(GlobalContext *globalCtx, EnOssan *this, Input *input) {
    EnGirlA *shopItem;

    shopItem = this->unk1E8[this->unk236];
    if (func_808A85FC(this, globalCtx, input)) {
        return 1;
    }
    if (func_808A80AC(globalCtx)) {
        if (!shopItem->isOutOfStock) {
            this->actionFunc2 = this->actionFunc;
            func_80151938(globalCtx, this->unk1E8[this->unk236]->choiceTextId);
            this->unk238.isEnabled = 0;
            this->unk270.isEnabled = 0;
            play_sound(NA_SE_SY_DECIDE);
            this->unk235 = 0;
            func_808A80A0(this, func_808AA0C8);
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return 1;
    }
    return 0;

}

void func_808A98E4(EnOssan *this, GlobalContext *globalCtx) {
    u8 sp2F = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 sp27 = this->unk236;
    u8 tmp;

    if (!func_808AA85C(this)) {
        this->unk1DC = 3;
    } else if (this->unk1DC != 0) {
        this->unk1DC--;
    } else {
        this->unk235 = 0xFF;
        this->unk270.isEnabled = 1;
        func_808A849C(globalCtx, this);
        if (sp2F == 5) {
            func_8011552C(globalCtx, 6);
            if (!func_808A980C(globalCtx, this, globalCtx->state.input)) {
                if (this->unk210 != 0) {
                    if (this->unk208 > 0) {
                        tmp = func_808A8DF8(this, this->unk236, 4);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp; 
                        } else {
                            func_808A875C(globalCtx, this);
                            return;
                        }
                    } else if (this->unk208 < 0) {
                        tmp = func_808A8E84(this, this->unk236, 8);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        }
                    }
                } else {
                    if ((this->unk208 > 0) && (this->unk208 >= 0x1F5)) {
                        tmp = func_808A8DF8(this, this->unk236, 4);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        } else {
                            func_808A875C(globalCtx, this);
                            return;
                        }
                    } else if ((this->unk208 < 0) && (this->unk208 < -0x1F4)) {
                        tmp = func_808A8E84(this, this->unk236, 8);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        }
                    }
                }
                func_808A95F8(this);
                if (this->unk236 != sp27) {
                    func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
                    play_sound(0x4809);
                }
            }
        }
    }
}

void func_808A9AB8(EnOssan *this, GlobalContext *globalCtx) {
    u8 sp2F = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 sp27 = this->unk236;
    u8 tmp;

    if (!func_808AA85C(this)) {
        this->unk1DC = 3;
    } else if (this->unk1DC != 0) {
        this->unk1DC--;
    } else {
        this->unk235 = 0xFF;
        this->unk238.isEnabled = 1;
        func_808A849C(globalCtx, this);
        if (sp2F == 5) {
            func_8011552C(globalCtx, 6);
            if (!func_808A980C(globalCtx, this, globalCtx->state.input)) {
                if (this->unk210 != 0) {
                    if (this->unk208 < 0) {
                        tmp = func_808A8DF8(this, this->unk236, 0);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        } else {
                            func_808A875C(globalCtx, this);
                            return;
                        }
                    } else if (this->unk208 > 0) {
                        tmp = func_808A8E84(this, this->unk236, 4);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        }
                    }
                } else {
                    if (this->unk208 < 0 && this->unk208 < -0x1F4) {
                        tmp = func_808A8DF8(this, this->unk236, 0);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        } else {
                            func_808A875C(globalCtx, this);
                            return;
                        }
                    } else if (this->unk208 > 0 && this->unk208 >= 0x1F5) {
                        tmp = func_808A8E84(this, this->unk236, 4);
                        if (tmp != 0xFF) {
                            this->unk236 = tmp;
                        }
                    }
                }
                func_808A95F8(this);
                if (this->unk236 != sp27) {
                    func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
                    play_sound(0x4809);
                }
            }
        }
    }
}

void func_808A9C8C(EnOssan *this, GlobalContext *globalCtx) {
    if (this->unk2C2 == 2) {
        ActorCutscene_Stop(this->unk2C0);
        this->unk2C2 = 0;
    }
    if (this->unk2C2 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk2C0 = this->unk2BE;
        ActorCutscene_SetIntentToPlay(this->unk2C0);
        this->unk2C2 = 1;
    } else if (this->unk2C2 == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk2C0)) {
            ActorCutscene_StartAndSetFlag(this->unk2C0, &this->actor);
            this->unk2C2 = 2;
            func_808A849C(globalCtx, this);
            func_808A8708(globalCtx, this);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk2C0);
        }
    }
}

void func_808A9D64(GlobalContext *globalCtx, EnOssan *this) {
    ActorPlayer *player = PLAYER;

    func_800B8A1C(&this->actor, globalCtx, this->unk1E8[this->unk236]->getItemId, 300.0f, 300.0f);
    globalCtx->msgCtx.unk11F23 = 0x43;
    globalCtx->msgCtx.unk12024 = 4;
    player->unkA70 &= ~0x20000000;
    Interface_ChangeAlpha(0x32);
    this->unk235 = 0;
    func_808A80A0(this, func_808AA2C8);
}

void func_808A9E20(GlobalContext *globalCtx, EnOssan *this, u16 arg2) {
    func_80151938(globalCtx, arg2);
    func_808A80A0(this, func_808AA1B0);
}

void func_808A9E5C(GlobalContext *globalCtx, EnOssan *this, u16 arg2) {
    func_80151938(globalCtx, arg2);
    func_808A80A0(this, func_808AA224);
}

#if NON_MATCHING
//Matches but jmptable is in late rodata
void func_808A9E98(GlobalContext *globalCtx, EnOssan *this) {
    EnGirlA *enGirlA;;

    enGirlA = this->unk1E8[this->unk236];
    switch(enGirlA->unk1B4Func(globalCtx, enGirlA)) {
        case 0:
            if (this->unk2C2 == 2) {
                ActorCutscene_Stop(this->unk2C0);
                this->unk2C2 = 0;
            }
            func_8019F208();
            enGirlA->unk1BCFunc(globalCtx, enGirlA);
            func_808A9D64(globalCtx, this);
            this->unk235 = 0;
            this->unk2B4 = 0.0f;
            enGirlA->unk1A4Func(globalCtx, enGirlA);
            break;
        case 1:
            func_8019F208();
            enGirlA->unk1B8Func(globalCtx, enGirlA);
            func_808A9E5C(globalCtx, this, D_808AC274[3][this->actor.params]);
            this->unk235 = 0;
            this->unk2B4 = 0.0f;
            enGirlA->unk1A4Func(globalCtx, enGirlA);
            break;
        case 2:
        case 7:
            play_sound(0x4806);
            func_808A9E20(globalCtx, this, D_808AC274[2][this->actor.params]);
            break;
        case 3:
            play_sound(0x4806);
            func_808A9E20(globalCtx, this, D_808AC274[0][this->actor.params]);
            break;
        case 4:
            play_sound(0x4806);
            func_808A9E20(globalCtx, this, D_808AC274[1][this->actor.params]);
            break;
        case 6:
            play_sound(0x4806);
            func_808A9E20(globalCtx, this, D_808AC274[4][this->actor.params]);
            break;
        case 5:
            play_sound(0x4806);
            func_808A9E20(globalCtx, this, D_808AC274[2][this->actor.params]);
            break;
        }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808A9E98.asm")
#endif

void func_808AA0C8(EnOssan *this, GlobalContext *globalCtx) {
    u8 sp27 = func_80152498(&globalCtx->msgCtx);

    if (func_808AA7C0(this) && sp27 == 4) {
        func_8011552C(globalCtx, 6);
        if (!func_808A8644(this, globalCtx, globalCtx->state.input) && func_80147624(globalCtx)) {
            switch(globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_808A9E98(globalCtx, this);
                    break;
                case 1:
                    func_8019F230();
                    this->actionFunc = this->actionFunc2;
                    func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
                    break;
            }
        }
    }
}

void func_808AA1B0(EnOssan *this, GlobalContext *globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5) {
        if (func_80147624(globalCtx)) {
            this->actionFunc = this->actionFunc2;
            func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
        }
    }
}

void func_808AA224(EnOssan *this, GlobalContext *globalCtx) {
    EnGirlA *enGirlA;

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->unk2B4 = 0.0f;
        func_808AA79C(this);
        enGirlA = this->unk1E8[this->unk236];
        enGirlA->restockFunc(globalCtx, enGirlA);
        this->actionFunc = this->actionFunc2;
        func_80151938(globalCtx, this->unk1E8[this->unk236]->actor.textId);
    }
}

void func_808AA2C8(EnOssan *this, GlobalContext *globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_808A80A0(this, func_808AA33C);
    } else {
        func_800B8A1C(&this->actor, globalCtx, this->unk1E8[this->unk236]->getItemId, 300.0f, 300.0f);
    }
}

void func_808AA33C(EnOssan *this, GlobalContext *globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        globalCtx->msgCtx.unk11F23 = 0x43;
        globalCtx->msgCtx.unk12024 = 4;
        func_808A80A0(this, func_808AA5E8);
        if (this->unk2C2 == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk2C0 = this->unk2B8;
            ActorCutscene_SetIntentToPlay(this->unk2C0);
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_808AA404(EnOssan *this, GlobalContext *globalCtx) {
    u8 sp27 = func_80152498(&globalCtx->msgCtx);
    ActorPlayer *player = PLAYER;
    EnGirlA *enGirlA;

    if (sp27 == 4) {
        func_8011552C(globalCtx, 6);
        if (func_80147624(globalCtx)) {
            func_808AA79C(this);
            enGirlA = this->unk1E8[this->unk236];
            enGirlA->restockFunc(globalCtx, enGirlA);
            if (!func_808A85FC(this, globalCtx, globalCtx->state.input)) {
                switch(globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        player->base.shape.rot.y += 0x8000;
                        player->unkA70 |= 0x20000000;
                        func_801518B0(globalCtx, this->unk2C4, &this->actor);
                        func_808A86A8(globalCtx, this, 1);
                        func_800B85E0(&this->actor, globalCtx, 100.0f, -1);
                        break;
                    case 1:
                    default:
                        func_8019F230();
                        func_808A8500(globalCtx, this);
                        break;
                }
            }
        }
    } else if (sp27 == 5 && func_80147624(globalCtx)) {
        func_808AA79C(this);
        enGirlA = this->unk1E8[this->unk236];
        enGirlA->restockFunc(globalCtx,enGirlA);
        player->base.shape.rot.y += 0x8000;
        player->unkA70 |= 0x20000000;
        func_801518B0(globalCtx, this->unk2C4, &this->actor);
        func_808A86A8(globalCtx, this, 1);
        func_800B85E0(&this->actor, globalCtx, 100.0f, -1);
    }
}

void func_808AA5E8(EnOssan *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    if (this->unk2C2 == 0) {
        if (ActorCutscene_GetCanPlayNext(this->unk2C0)) {
            ActorCutscene_StartAndSetFlag(this->unk2C0, &this->actor);
            player->unkA70 |= 0x20000000;
            func_808A80A0(this, func_808AA404);
            this->unk2C2 = 2;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk2C0 = this->unk2B8;
            ActorCutscene_SetIntentToPlay(this->unk2C0);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80151938(globalCtx, 0x642);
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_808AA6D8(EnOssan *this) {
    EnGirlA *enGirlA;
    u8 i;
    u8 i2;
    EnOssanUnkStruct *unkStruct;
    Vec3f worldPos;

    i = this->unk236;
    unkStruct = &D_808AC1D4[this->actor.params][i];
    enGirlA = this->unk1E8[i];

    i2 = i >> 2;
    worldPos.x = (D_808AC28C[i2].x - unkStruct->unk2) * this->unk2B4 + unkStruct->unk2;
    worldPos.y = (D_808AC28C[i2].y - unkStruct->unk4) * this->unk2B4 + unkStruct->unk4;
    worldPos.z = (D_808AC28C[i2].z - unkStruct->unk6) * this->unk2B4 + unkStruct->unk6;

    enGirlA->actor.world.pos.x = worldPos.x;
    enGirlA->actor.world.pos.y = worldPos.y;
    enGirlA->actor.world.pos.z = worldPos.z;
}

void func_808AA79C(EnOssan *this) {
    this->unk2B4 = 0.0f;
    func_808AA6D8(this);
}

#if NON_MATCHING
//Matches but floats are in late rodata
s32 func_808AA7C0(EnOssan *this) {
    Math_ApproachF(&this->unk2B4, 1.0f, 1.0f, 0.15f);
    if (this->unk2B4 >= 0.85f) {
        this->unk2B4 = 1.0f;
    }
    func_808AA6D8(this);
    if (this->unk2B4 == 1.0f) {
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA7C0.asm")
#endif

#if NON_MATCHING
// Matches but floats are in late rodata
s32 func_808AA85C(EnOssan *this) {
    Math_ApproachF(&this->unk2B4, 0.0f, 1.0f, 0.15f);
    if (this->unk2B4 <= 0.15f) {
        this->unk2B4 = 0.0f;
    }
    func_808AA6D8(this);
    if (this->unk2B4 == 0.0f) {
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA85C.asm")
#endif

#if NON_MATCHING
//Needs to unroll to 4 not 2
void func_808AA8E8(EnOssan *this) {
    EnGirlA **tmp = this->unk1E8;
    s32 i;

    for(i=0; i<8; i++, tmp++) {
        if (*tmp != NULL) {
            if (this->actionFunc != func_808AA0C8 && this->actionFunc != func_808AA1B0 && this->unk235 == 0) {
                (*tmp)->unk1AC = 0;
            } else {
                (*tmp)->unk1AC = this->unk236 == i ? 1 : 0;
            } 
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AA8E8.asm")
#endif

#define ColChanMix(c1, c2, m) (c1 - (s32)(c2 * m)) & 0xFF

#if NON_MATCHING
//Matches but floats are in late rodata
void func_808AAA64(EnOssan *this) {
    f32 t;

    t = this->unk230;
    if (this->unk234 == 0) {
        t += 0.05f;
        if (t >= 1.0f) {
            t = 1.0f;
            this->unk234 = 1;
        }
    } else {
        t -= 0.05f;
        if (t <= 0.0f) {
            t = 0.0f;
            this->unk234 = 0;
        }
    }
    this->unk220.r = ColChanMix(0, 0.0f, t);
    this->unk220.g = ColChanMix(80, 80.0f, t);
    this->unk220.b = ColChanMix(255, 0.0f, t);
    this->unk220.a = ColChanMix(255, 0.0f, t);
    this->unk230 = t;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAA64.asm")
#endif

#if NON_MATCHING
//A lot is wrong with this one
void func_808AAB30(EnOssan *this) {
    f32 t1;
    f32 t2;

    t1 = this->unk2A8;
    if (this->unk2B0 == 0) {
        t1 += 0.05f;
        if (t1 > 1.0f) {
            t1 = 1.0f;
            this->unk2B0 = 1;
        }
    } else {
        t1 -= 0.05f;
        if (t1 < 0.0f) {
            t1 = 0.0f;
            this->unk2B0 = 0;
        }
    }
    this->unk2A8 = t1;

    t2 = this->unk2AC;
    if (this->unk2B1 == 0) {
        t1 += 0.05f;
        if (t1 > 1.0f) {
            t1 = 1.0f;
            this->unk2B1 = 1;
        }
    } else {
        t1 = 0.0f;
        this->unk2B1 = 1;
    }
    this->unk2AC = t2;

    this->unk238.arrowColor.r = ColChanMix(255, 155.0f, t1);
    this->unk238.arrowColor.g = ColChanMix(255, 0.0f, t1);
    this->unk238.arrowColor.b = ColChanMix(0, 100.0f, t1);
    this->unk238.arrowColor.a = ColChanMix(200, 50.0f, t1);
    this->unk270.arrowColor.r = ColChanMix(255, 155.0f, t1);
    this->unk270.arrowColor.g = ColChanMix(255, 0.0f, t1);
    this->unk270.arrowColor.b = ColChanMix(0, 100.0f, t1);
    this->unk270.arrowColor.a = ColChanMix(200, 50.0f, t1);

    this->unk238.arrowTexX = 33.0f;
    this->unk238.arrowTexY = 91.0f;
    this->unk238.stickTexX = 49.0 + 8.0f * t2;
    this->unk238.stickTexY = 95.0f;

    this->unk270.arrowTexX = 290.0f;
    this->unk270.arrowTexY = 91.0f;
    this->unk270.stickTexX = 274.0f + 8.0f * t2;
    this->unk270.stickTexY = 95.0f;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AAB30.asm")
#endif

void func_808AACE0(EnOssan *this) {
    s16 tmp;

    tmp = this->unk1E2 - 1;
    if (tmp != 0) {
        this->unk1E2 = tmp;
    } else {
        this->unkFunc = func_808AAD14;
    }
}

void func_808AAD14(EnOssan *this) {
    s16 tmp;
    s16 tmp2;

    tmp = this->unk1E2 - 1;
    if (tmp != 0) {
        this->unk1E2 = tmp;
        return;
    }
    tmp2 = this->unk1E0 + 1;
    if (tmp2 > 2) {
        this->unk1E0 = 0;
        this->unk1E2 = (s32)(Rand_ZeroOne() * 60.0f) + 20;
        this->unkFunc = func_808AACE0;
    } else {
        this->unk1E0 = tmp2;
        this->unk1E2 = 1;
    }
}

void func_808AADB4(EnOssan *this, GlobalContext *globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013320, &D_06012C34, this->limbDrawTbl, this->transitionDrawTbl, 19);
    this->actor.draw = func_808ABE58;
}

void func_808AAE1C(EnOssan *this, GlobalContext *globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060028A0, &D_06009D34, this->limbDrawTbl, this->transitionDrawTbl, 16);
    this->actor.draw = func_808ABF30;
}

s32 func_808AAE84(EnOssan *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    u16 ret;

    ret = func_800F1250(globalCtx, 0x2F);
    if (ret != 0) {
        this->unk402 = 4;
        this->unk40A |= 2;
        return ret;
    }
    switch(player->unk14B) {
        case 3:
            this->unk402 = 10;
            if(gSaveContext.weekEventReg[18] & 16) {
                return D_808AC254[7][0];
            }
            return D_808AC254[4][0];
        case 2:
            this->unk402 = 8;
            if(gSaveContext.weekEventReg[18] & 8) {
                return D_808AC254[6][0];
            }
            return D_808AC254[3][0];
        case 1:
            this->unk402 = 6;
            if(gSaveContext.weekEventReg[18] & 4) {
                return D_808AC254[5][0];
            }
            return D_808AC254[2][0];
        default:
            this->unk402 = 4;
            return D_808AC254[0][0];
    }
}

s32 func_808AAFB0(EnOssan *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    u16 ret;

    ret = func_800F1250(globalCtx, 0x36);
    if (ret != 0) {
        this->unk40A |= 2;
        return ret;
    }
    switch(player->unk14B) {
        case 3:
            if(gSaveContext.weekEventReg[55] & 16) {
                return D_808AC254[7][1];
            }
            return D_808AC254[4][1];
        case 2:
            if(gSaveContext.weekEventReg[55] & 8) {
                return D_808AC254[6][1];
            }
            return D_808AC254[3][1];
        case 1:
            if(gSaveContext.weekEventReg[55] & 4) {
                return D_808AC254[5][1];
            }
            return D_808AC254[2][1];
        default:
            return D_808AC254[0][1];
    }
}

#if NON_MATCHING
//Matches but jump table is in late rodata
void func_808AB0B0(EnOssan *this) {
    switch(this->unk2C4) {
        case 0x6A9:
            gSaveContext.weekEventReg[18] |= 0x10;
            break;
        case 0x6C6:
            gSaveContext.weekEventReg[55] |= 0x10;
            break;
        case 0x6A7:
            gSaveContext.weekEventReg[18] |= 8;
            break;
        case 0x6C4:
            gSaveContext.weekEventReg[55] |= 8;
            break;
        case 0x6A5:
            gSaveContext.weekEventReg[18] |= 4;
            break;
        case 0x6C2:
            gSaveContext.weekEventReg[55] |= 4;
            break;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ossan_0x808A80A0/func_808AB0B0.asm")
#endif

void func_808AB16C(EnOssan *this, GlobalContext *globalCtx) {
    EnOssanUnkStruct *sp24;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk1DE)) {
        this->actor.flags &= -0x11;
        this->actor.objBankIndex = this->unk1DE;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        sp24 = D_808AC1D4[this->actor.params];
        ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
        D_808AC2A4[this->actor.params](this, globalCtx);
        this->unk2C4 = D_808AC254[0][this->actor.params];
        func_808AB404(this, globalCtx);

        this->unk218 = this->unk214 = 100.0f;
        this->unk2C2 = 0;
        this->unk2C0 = this->unk2B8;
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
        this->actor.colChkInfo.cylRadius = 50;
        this->unk208 = this->unk20C = 0;

        this->unk236 = 0;
        this->unk21C = 1.5f;
        this->unk220.r = 0;
        this->unk220.g = 80;
        this->unk220.b = 255;
        this->unk220.a = 255;
        this->unk230 = 0.0f;

        this->unk234 = 0;
        this->unk235 = 0;

        this->unk238.stickColor.r = 200;
        this->unk238.stickColor.g = 200;
        this->unk238.stickColor.b = 200;
        this->unk238.stickColor.a = 180;
        this->unk238.stickTexX = 49.0f;
        this->unk238.stickTexY = 95.0f;
        this->unk238.arrowColor.r = 255;
        this->unk238.arrowColor.g = 255;
        this->unk238.arrowColor.b = 0;
        this->unk238.arrowColor.a = 200;
        this->unk238.arrowTexX = 33.0f;
        this->unk238.arrowTexY = 91.0f;
        this->unk238.z = 1.0f;
        this->unk238.isEnabled = false;


        this->unk270.stickColor.r = 200;
        this->unk270.stickColor.g = 200;
        this->unk270.stickColor.b = 200;
        this->unk270.stickColor.a = 180;
        this->unk270.stickTexX = 274.0f;
        this->unk270.stickTexY = 95.0f;
        this->unk270.arrowColor.r = 255;
        this->unk270.arrowColor.g = 255;
        this->unk270.arrowColor.b = 0;
        this->unk270.arrowColor.a = 200;
        this->unk270.arrowTexX = 290.0f;
        this->unk270.arrowTexY = 91.0f;
        this->unk270.z = 1.0f;
        this->unk270.isEnabled = false;

        this->unk2B0 = 0;
        this->unk2B1 = 0;
        this->unk2A8 = 0.0f;
        this->unk2AC = 0.0f;
        this->unk2B4 = 0.0f;
        Actor_SetScale(&this->actor, D_808AC1CC[this->actor.params]);
        this->unk402 = 1;
        func_8013BC6C(&this->skelAnime, D_808AC1C4[this->actor.params], 1);
        func_808A82F4(this, globalCtx, sp24);
        this->unk1E2 = 20;
        this->unk1E0 = 0;
        this->unkFunc = func_808AACE0;
        this->actor.flags &= ~1;
        func_808A80A0(this, func_808A8798);
    }
}

void func_808AB404(EnOssan *this, GlobalContext *globalCtx) {
    this->unk2B8 = this->actor.cutscene;
    this->unk2BA = ActorCutscene_GetAdditionalCutscene(this->unk2B8);
    this->unk2BC = ActorCutscene_GetAdditionalCutscene(this->unk2BA);
    this->unk2BE = ActorCutscene_GetAdditionalCutscene(this->unk2BC);
}

void EnOssan_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnOssan *this = THIS;

    if (this->actionFunc != func_808AB16C) {
        this->unkFunc(this);
        func_808A8B74(globalCtx, this);
        func_808AA8E8(this);
        func_808AAB30(this);
        func_808AAA64(this);
        func_800E9250(globalCtx, &this->actor, &this->unk2C6, &this->unk2CC, this->actor.focus.pos);
        this->actionFunc(this, globalCtx);
        Actor_SetHeight(&this->actor, 90.0f);
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    } else {
        this->actionFunc(this, globalCtx);
    }
}

void func_808AB52C(GlobalContext* globalCtx, EnOssan* this, f32 arg2, f32 arg3, f32 arg4, u8 arg5) {
    s32 ulx, uly, lrx, lry;
    f32 w;
    s32 dsdx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (arg5 != 0) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, this->unk220.r, this->unk220.g, this->unk220.b,
                        this->unk220.a);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &D_0401F740, G_IM_FMT_IA, 16, 16, 0,
                               G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
        w = 16.0f * arg4;
        ulx = (arg2 - w) * 4.0f;
        uly = (arg3 - w) * 4.0f;
        lrx = (arg2 + w) * 4.0f;
        lry = (arg3 + w) * 4.0f;
        dsdx = (1.0f / arg4) * 1024.0f;
        gSPTextureRectangle(OVERLAY_DISP++, ulx, uly, lrx, lry, G_TX_RENDERTILE, 0, 0, dsdx, dsdx);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_808AB78C(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t,
                         f32 dx, f32 dy) {
    f32 unk;
    s32 ulx, uly, lrx, lry;
    f32 w, h;
    s32 dsdx, dtdy;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gDPPipeSync(OVERLAY_DISP++);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, r, g, b, a);

    w = 8.0f * z;
    ulx = (x - w) * 4.0f;
    lrx = (x + w) * 4.0f;

    h = 12.0f * z;
    uly = (y - h) * 4.0f;
    lry = (y + h) * 4.0f;

    unk = 1024 * (1.0f / z);
    dsdx = unk * dx;
    dtdy = dy * unk;
    
    gSPTextureRectangle(OVERLAY_DISP++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, dsdx, dtdy);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_808AB928(GlobalContext* globalCtx, EnOssan* this) {
    s32 drawStickRightPrompt = this->unk238.isEnabled;
    s32 drawStickLeftPrompt = this->unk270.isEnabled;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (drawStickRightPrompt || drawStickLeftPrompt) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetTextureImage(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, &D_0401F8C0);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPLoadSync(OVERLAY_DISP++);
        gDPLoadBlock(OVERLAY_DISP++, G_TX_LOADTILE, 0, 0, 191, 1024);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPSetTileSize(OVERLAY_DISP++, G_TX_RENDERTILE, 0, 0, 15 * 4, 23 * 4);
        if (drawStickRightPrompt) {
            func_808AB78C(globalCtx, this->unk238.arrowColor.r, this->unk238.arrowColor.g,
                                this->unk238.arrowColor.b, this->unk238.arrowColor.a,
                                this->unk238.arrowTexX, this->unk238.arrowTexY,
                                this->unk238.z, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_808AB78C(globalCtx, this->unk270.arrowColor.r, this->unk270.arrowColor.g,
                                this->unk270.arrowColor.b, this->unk270.arrowColor.a,
                                this->unk270.arrowTexX, this->unk270.arrowTexY,
                                this->unk270.z, 0, 0, 1.0f, 1.0f);
        }
        gDPSetTextureImage(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, &D_0401F7C0);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPLoadSync(OVERLAY_DISP++);
        gDPLoadBlock(OVERLAY_DISP++, G_TX_LOADTILE, 0, 0, 127, 1024);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPSetTileSize(OVERLAY_DISP++, G_TX_RENDERTILE, 0, 0, 15 * 4, 15 * 4);
        if (drawStickRightPrompt) {
            func_808AB78C(globalCtx, this->unk238.stickColor.r, this->unk238.stickColor.g,
                                this->unk238.stickColor.b, this->unk238.stickColor.a,
                                this->unk238.stickTexX, this->unk238.stickTexY,
                                this->unk238.z, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_808AB78C(globalCtx, this->unk270.stickColor.r, this->unk270.stickColor.g,
                                this->unk270.stickColor.b, this->unk270.stickColor.a,
                                this->unk270.stickTexX, this->unk270.stickTexY,
                                this->unk270.z, 0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_808ABCD0(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnOssan *this = THIS;

    if (limbIndex == 16) {
        SysMatrix_InsertXRotation_s(this->unk2C6.y, 1);
    }
    return 0;
}

s32 func_808ABD10(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnOssan *this = THIS;

    if (limbIndex == 15) {
        SysMatrix_InsertXRotation_s(this->unk406, 1);
        SysMatrix_InsertZRotation_s(this->unk404, 1);
    }
    return 0;
}

void func_808ABD60(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnOssan *this = THIS;

    if (limbIndex == 1 || limbIndex == 9 || limbIndex == 12) {
        rot->y += (s16) Math_SinS(this->unk2D2[limbIndex]) * 200;
        rot->z += (s16) Math_CosS(this->unk2F8[limbIndex]) * 200;
    }
}

void func_808ABE18(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnOssan *this = THIS;

    if (limbIndex == 15) {
        SysMatrix_MultiplyVector3fByState(&D_808AC2AC, &this->actor.focus.pos);
    }
}

void func_808ABE58(Actor *thisx, GlobalContext *globalCtx) {
    EnOssan *this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_808AC2B8[0][this->unk1E0]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_808ABCD0, func_808ABD60, &this->actor);
    func_808AB52C(globalCtx, this, this->unk214, this->unk218, this->unk21C, this->unk235);
    func_808AB928(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_808ABF30(Actor *thisx, GlobalContext *globalCtx) {
    EnOssan *this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_808AC2B8[1][this->unk1E0]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, func_808ABD10, func_808ABE18, &this->actor);
    func_808AB52C(globalCtx, this, this->unk214, this->unk218, this->unk21C, this->unk235);
    func_808AB928(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
