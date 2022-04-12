/*
 * File: z_en_trt2.c
 * Overlay: ovl_En_Trt2
 * Description: Kotake in Southern Swamp and Woods of Mystery
 */

#include "z_en_trt2.h"
#include "objects/object_trt/object_trt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTrt2*)thisx)

void EnTrt2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt2_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80AD46F8(EnTrt2* this);
s32 func_80AD475C(EnTrt2* this, Path* path, s32 arg2);
s16 func_80AD48F8(Path* path, s32 arg1, Vec3f* arg2, f32* arg3);
f32 func_80AD49B8(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3);
void func_80AD4A78(EnTrt2* this, GlobalContext* globalCtx);
s32 func_80AD4B08(GlobalContext* globalCtx);
void func_80AD4DB4(EnTrt2* this, GlobalContext* globalCtx);
void func_80AD4FE4(EnTrt2* this, GlobalContext* globalCtx);
void func_80AD5234(EnTrt2* this, GlobalContext* globalCtx);
void func_80AD56E8(Actor* thisx, GlobalContext* globalCtx);

static AnimationInfoS sAnimations[] = {
    { &object_trt_Anim_00DE68, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_trt_Anim_00EE98, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_trt_Anim_00FD34, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_trt_Anim_0030EC, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_trt_Anim_003D78, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_trt_Anim_00D52C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_trt_Anim_000A44, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_trt_Anim_001EF4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_trt_Anim_002224, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_trt_Anim_002CB0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

const ActorInit En_Trt2_InitVars = {
    ACTOR_EN_TRT2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRT,
    sizeof(EnTrt2),
    (ActorFunc)EnTrt2_Init,
    (ActorFunc)EnTrt2_Destroy,
    (ActorFunc)EnTrt2_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 32, 56, 30, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x1),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

void func_80AD3380(SkelAnime* skelAnime, AnimationInfoS* animation, s32 arg2) {
    f32 phi_f0;

    animation += arg2;

    if (animation->frameCount < 0) {
        phi_f0 = Animation_GetLastFrame(animation->animation);
    } else {
        phi_f0 = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, phi_f0,
                     animation->mode, animation->morphFrames);
}

void func_80AD341C(EnTrt2* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80AD349C(EnTrt2* this) {
    if ((gSaveContext.save.weekEventReg[85] & 0x10) && !(gSaveContext.save.weekEventReg[84] & 0x40)) {
        this->unk_3A8 = 0x88F;
    } else if (this->unk_3A8 == 0) {
        this->unk_3A8 = 0x84B;
    } else if (gSaveContext.save.weekEventReg[16] & 0x10) {
        this->unk_3A8 = 0x838;
    } else if (gSaveContext.save.weekEventReg[17] & 1) {
        this->unk_3A8 = 0x84D;
    } else {
        this->unk_3A8 = 0x849;
    }
}

void func_80AD3530(EnTrt2* this, GlobalContext* globalCtx) {
    s16 phi_a1;
    f32 sp30;

    func_80AD46F8(this);
    if (this->path != NULL) {
        phi_a1 = func_80AD48F8(this->path, this->unk_1E4, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            phi_a1 = this->actor.wallYaw;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, phi_a1, 4, 1000, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        if (func_80AD475C(this, this->path, this->unk_1E4)) {
            if (this->unk_1E4 >= (this->path->count - 1)) {
                this->unk_1E4 = 0;
            } else {
                this->unk_1E4++;
            }
        }
        Math_ApproachF(&this->actor.speedXZ, 1.5f, 0.2f, 1.0f);
    }

    Actor_MoveWithGravity(&this->actor);

    if (DECR(this->unk_3AE) == 0) {
        this->unk_3AE = Rand_S16Offset(20, 20);
        func_80AD3380(&this->skelAnime, sAnimations, 7);
        this->unk_3B2 = 5;
    }
}

void func_80AD3664(EnTrt2* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_3DA)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_3DA, &this->actor);
        if (this->unk_3D9 == 0) {
            this->unk_3B2 = 1;
        } else {
            this->unk_3B2 = 2;
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->unk_3DA);
        return;
    }
    func_800B9010(&this->actor, NA_SE_EN_KOTAKE_FLY - SFX_FLAG);
}

void func_80AD36EC(EnTrt2* this, GlobalContext* globalCtx) {
    Vec3s sp30;
    f32 sp2C;

    if (this->path != NULL) {
        sp2C = func_80AD49B8(this->path, this->unk_1E4, &this->actor.world.pos, &sp30);
        this->actor.shape.rot.y += 0x1000;
        Math_ApproachF(&this->actor.velocity.y, 0.5f, 0.2f, 1.0f);
        if (sp2C < 5.0f) {
            if (this->unk_1E4 >= (this->path->count - 1)) {
                this->unk_1E4 = 0;
                this->unk_3D9 = 1;
                this->actor.velocity.y = 0.0f;
                this->path = SubS_GetPathByIndex(globalCtx, this->path->unk1, -1);
                ActorCutscene_Stop(this->unk_3DA);
                this->unk_3DA = ActorCutscene_GetAdditionalCutscene(this->unk_3DA);
                ActorCutscene_SetIntentToPlay(this->unk_3DA);
                this->unk_3B2 = 0;
            } else {
                this->unk_1E4++;
            }
        }
    }
    Actor_MoveWithGravity(&this->actor);
    func_800B9010(&this->actor, NA_SE_EN_KOTAKE_FLY - SFX_FLAG);
    if ((this->actor.shape.rot.y >= 0x2800) && (this->actor.shape.rot.y < 0x3800)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KOTAKE_ROLL);
    }
}

void func_80AD381C(EnTrt2* this, GlobalContext* globalCtx) {
    if ((CURRENT_DAY == 2) || (CURRENT_DAY == 3)) {
        if (func_80AD4B08(globalCtx) == 1) {
            this->actor.world.pos.y -= 50.0f;
            this->unk_3D9 = 0;
            this->unk_3B2 = 0;
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->actor.flags |= ACTOR_FLAG_10;
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80AD38B8(EnTrt2* this, GlobalContext* globalCtx) {
    Vec3s sp30;

    if (this->unk_3D9 == 2) {
        Actor_MarkForDeath(&this->actor);
    }

    if (this->path != NULL) {
        func_80AD49B8(this->path, this->unk_1E4, &this->actor.world.pos, &sp30);
        Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 4, 1000, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Math_SmoothStepToS(&this->actor.shape.rot.x, sp30.x, 4, 1000, 1);
        this->actor.world.rot.x = -this->actor.shape.rot.x;
        if (func_80AD475C(this, this->path, this->unk_1E4)) {
            if (this->unk_1E4 >= (this->path->count - 1)) {
                ActorCutscene_Stop(this->unk_3DA);
                this->unk_3D9 = 2;
            } else {
                this->unk_1E4++;
            }
        }

        if (this->actor.bgCheckFlags & 8) {
            if (this->unk_1E4 >= (this->path->count - 1)) {
                ActorCutscene_Stop(this->unk_3DA);
                this->unk_3D9 = 2;
            } else {
                sp30.y = this->actor.wallYaw;
            }
        }
        Math_ApproachF(&this->actor.speedXZ, 5.0f, 0.2f, 1.0f);
    }

    Actor_MoveWithoutGravity(&this->actor);
    func_800B9010(&this->actor, NA_SE_EN_KOTAKE_FLY - SFX_FLAG);
}

void func_80AD3A24(EnTrt2* this, GlobalContext* globalCtx) {
    func_80AD46F8(this);
    if (this->actor.speedXZ > 0.05f) {
        Math_ApproachF(&this->actor.speedXZ, 0.0f, 0.2f, 1.0f);
    } else if (DECR(this->unk_3AE) == 0) {
        this->unk_3AE = Rand_S16Offset(100, 50);
        func_80AD3380(&this->skelAnime, sAnimations, 6);
        this->unk_3B2 = 4;
    }
    Actor_MoveWithGravity(&this->actor);
}

void func_80AD3AE4(EnTrt2* this, GlobalContext* globalCtx) {
    if (this->actor.world.pos.y < this->actor.home.pos.y) {
        Math_ApproachF(&this->actor.velocity.y, 0.5f, 0.2f, 0.1f);
    } else {
        this->actor.velocity.y = 0.0f;
        func_80AD3380(&this->skelAnime, sAnimations, 6);
        this->unk_3B2 = 4;
    }
    Actor_MoveWithGravity(&this->actor);
}

void func_80AD3B6C(EnTrt2* this, GlobalContext* globalCtx) {
    if (DECR(this->unk_3B0) == 0) {
        this->unk_3B0 = 10;
        this->actor.velocity.y = -1.0f;
        func_80AD3380(&this->skelAnime, sAnimations, 8);
        this->unk_3B2 = 8;
    }
}

void func_80AD3BE4(EnTrt2* this, GlobalContext* globalCtx) {
    s16 sp2E = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    Math_ScaledStepToS(&this->unk_3C0, sp2E, 400);
    Math_SmoothStepToS(&this->unk_3C0, sp2E, 4, 10000, 0);
    this->actor.world.rot.y += this->unk_3C0;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->actor.world.pos.y < 5.0f) {
        func_80AD3380(&this->skelAnime, sAnimations, 9);
        this->unk_3B2 = 9;
    }
}

void func_80AD3C94(EnTrt2* this, GlobalContext* globalCtx) {
    if (this->actor.world.pos.y < 5.0f) {
        func_80AD4A78(this, globalCtx);
        if (this->actor.bgCheckFlags & 1) {
            this->unk_3B2 = 0xF;
        }
    }
}

void func_80AD3CEC(EnTrt2* this, GlobalContext* globalCtx) {
    u8 sp27 = Message_GetState(&globalCtx->msgCtx);

    func_80AD46F8(this);
    if (this->unk_3D8) {
        Message_StartTextbox(globalCtx, this->unk_3A8, &this->actor);
        this->unk_3D8 = false;
    } else if ((sp27 == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        func_80AD3380(&this->skelAnime, sAnimations, 6);
        this->unk_3B2 = 4;
    }
}

void func_80AD3DA4(EnTrt2* this, GlobalContext* globalCtx) {
    this->actor.velocity.y = 0.0f;
    Message_StartTextbox(globalCtx, this->unk_3A8, &this->actor);

    if (this->unk_3A8 == 0x838) {
        this->unk_3B2 = 11;
        return;
    } else if (this->unk_3A8 == 0x88F) {
        if (Interface_HasEmptyBottle()) {
            this->unk_3B2 = 11;
        } else {
            this->unk_3B2 = 10;
        }
    } else {
        this->unk_3B2 = 10;
    }
}

void func_80AD3E34(EnTrt2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        if (Interface_HasEmptyBottle()) {
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_3B2 = 12;
        } else {
            gSaveContext.save.weekEventReg[85] |= 0x10;
            this->unk_3A8 = 0x88E;
            Message_StartTextbox(globalCtx, this->unk_3A8, &this->actor);
            this->unk_3B2 = 10;
        }
    }
}

void func_80AD3EF0(EnTrt2* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 6) {
        if (Message_ShouldAdvance(globalCtx)) {
            if ((Interface_HasEmptyBottle() && !(gSaveContext.save.weekEventReg[84] & 0x40)) ||
                !(gSaveContext.save.weekEventReg[12] & 0x10)) {
                this->unk_3B2 = 12;
            } else {
                gSaveContext.save.weekEventReg[85] |= 0x10;
                this->unk_3A8 = 0x88E;
                Message_StartTextbox(globalCtx, this->unk_3A8, &this->actor);
                this->unk_3B2 = 10;
            }
        }
    } else if ((temp_v0 == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->unk_3B2 = 12;
    }
}

void func_80AD3FF4(EnTrt2* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        if (!(gSaveContext.save.weekEventReg[12] & 0x10)) {
            gSaveContext.save.weekEventReg[12] |= 0x10;
        }
        gSaveContext.save.weekEventReg[84] |= 0x40;
        this->actor.parent = NULL;
        this->unk_3B2 = 14;
    } else if (gSaveContext.save.weekEventReg[12] & 0x10) {
        Actor_PickUp(&this->actor, globalCtx, GI_POTION_RED, 300.0f, 300.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_BOTTLE_POTION_RED, 300.0f, 300.0f);
    }
}

void func_80AD40AC(EnTrt2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 6) && Message_ShouldAdvance(globalCtx)) {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
        this->unk_3B2 = 13;
    }
}

void func_80AD4110(EnTrt2* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_3A8 = 0x84C;
        func_80151938(globalCtx, this->unk_3A8);
        this->unk_3B2 = 10;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80AD417C(EnTrt2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_3A8 == 0x84B) {
            func_80AD349C(this);
            func_80AD3DA4(this, globalCtx);
        } else {
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            if (this->unk_3A8 == 0x84C) {
                func_80AD3380(&this->skelAnime, sAnimations, 6);
                this->path = SubS_GetPathByIndex(globalCtx, ENTRT2_GET_FC00(&this->actor), 0x3F);
                this->unk_3B2 = 18;
            } else if (this->unk_3A8 == 0x88F) {
                this->unk_3A8 = 0x88E;
                Message_StartTextbox(globalCtx, this->unk_3A8, &this->actor);
            } else {
                this->actor.textId = 0;
                this->unk_3B2 = 15;
            }
        }
    }
}

void func_80AD4298(EnTrt2* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (ActorCutscene_GetCanPlayNext(this->unk_3DA)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_3DA, &this->actor);
        player->stateFlags1 |= 0x20;
        this->unk_3B2 = 6;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->unk_3DA);
    }
}

void func_80AD431C(EnTrt2* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->stateFlags1 &= ~0x20;
    Actor_MarkForDeath(&this->actor);
}

void func_80AD434C(EnTrt2* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y += 0x1000;
    Math_ApproachF(&this->actor.velocity.y, 1.5f, 0.2f, 0.1f);

    if (this->actor.world.pos.y > 200.0f) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->unk_3B2 = 0x13;
            ActorCutscene_Stop(this->unk_3DA);
        } else {
            s32 i;
            Vec3f sp68;
            Vec3f sp5C = { 0.0f, 0.5f, 0.0f };

            for (i = (s32)this->skelAnime.animLength - (s32)this->skelAnime.curFrame; i >= 0; i -= 2) {
                sp68.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
                sp68.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
                sp68.y = randPlusMinusPoint5Scaled(50.0f) + (this->actor.world.pos.y + 20.0f);
                func_800B3030(globalCtx, &sp68, &sp5C, &sp5C, 100, 0, 3);
            }

            func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        }
    } else if (this->actor.world.pos.y < 5.0f) {
        func_80AD4A78(this, globalCtx);
    }

    Actor_MoveWithGravity(&this->actor);

    if ((this->actor.shape.rot.y >= 0x2800) && (this->actor.shape.rot.y < 0x3800)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KOTAKE_ROLL);
    }
}

void func_80AD4550(EnTrt2* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u8 sp23 = Message_GetState(&globalCtx->msgCtx);

    if ((player->transformation != PLAYER_FORM_HUMAN) && (player->transformation != PLAYER_FORM_FIERCE_DEITY)) {
        func_80AD3380(&this->skelAnime, sAnimations, 7);
        this->unk_3B2 = 17;
    }

    if ((sp23 == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
    }
}

void func_80AD4608(EnTrt2* this) {
    s16 temp = this->unk_3B6 - 1;

    if (temp != 0) {
        this->unk_3B6 = temp;
        return;
    }

    temp = this->unk_3B8 + 1;
    if (temp >= 3) {
        this->unk_3B8 = 0;
        this->unk_3B6 = (s32)(Rand_ZeroOne() * 60.0f) + 20;
    } else {
        this->unk_3B8 = temp;
        this->unk_3B6 = 1;
    }
}

void func_80AD469C(EnTrt2* this, GlobalContext* globalCtx) {
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_trt_Skel_00FEF0, &object_trt_Anim_000A44, NULL, NULL, 0);
    this->actor.draw = func_80AD56E8;
}

void func_80AD46F8(EnTrt2* this) {
    if ((this->actor.home.pos.y + 60.0f) < this->actor.world.pos.y) {
        this->actor.velocity.y = -0.2f;
    } else if (this->actor.world.pos.y <= (this->actor.home.pos.y + 50.0f)) {
        this->actor.velocity.y = 0.2f;
    }
}

s32 func_80AD475C(EnTrt2* this, Path* path, s32 arg2) {
    Vec3s* points;
    s32 count;
    f32 phi_f12;
    s32 ret;
    f32 phi_f14;
    s32 arg = arg2;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    points = Lib_SegmentedToVirtual(path->points);
    count = path->count;
    ret = false;
    Math_Vec3s_ToVec3f(&sp30, &points[arg]);

    if (arg == 0) {
        phi_f12 = points[1].x - points[0].x;
        phi_f14 = points[1].z - points[0].z;
    } else if ((count - 1) == arg) {
        phi_f12 = points[count - 1].x - points[count - 2].x;
        phi_f14 = points[count - 1].z - points[count - 2].z;
    } else {
        phi_f12 = points[arg + 1].x - points[arg - 1].x;
        phi_f14 = points[arg + 1].z - points[arg - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        ret = true;
    }
    return ret;
}

s16 func_80AD48F8(Path* path, s32 arg1, Vec3f* arg2, f32* arg3) {
    Vec3s* points;
    f32 phi_f14;
    f32 phi_f12;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        phi_f14 = points->x - arg2->x;
        phi_f12 = points->z - arg2->z;
    } else {
        phi_f14 = 0.0f;
        phi_f12 = 0.0f;
    }
    *arg3 = SQ(phi_f14) + SQ(phi_f12);
    return RADF_TO_BINANG(Math_Acot2F(phi_f12, phi_f14));
}

f32 func_80AD49B8(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3) {
    s32 pad;
    Vec3f sp20;
    Vec3s* temp_v1;

    if (path != NULL) {
        temp_v1 = Lib_SegmentedToVirtual(path->points);
        temp_v1 = &temp_v1[arg1];

        sp20.x = temp_v1->x;
        sp20.y = temp_v1->y;
        sp20.z = temp_v1->z;
    }
    arg3->y = Math_Vec3f_Yaw(arg2, &sp20);
    arg3->x = Math_Vec3f_Pitch(arg2, &sp20);
    return sp20.y - arg2->y;
}

void func_80AD4A78(EnTrt2* this, GlobalContext* globalCtx) {
    Vec3f sp34;

    sp34.x = randPlusMinusPoint5Scaled(15.0f) + this->actor.world.pos.x;
    sp34.y = this->actor.world.pos.y;
    sp34.z = randPlusMinusPoint5Scaled(15.0f) + this->actor.world.pos.z;
    Actor_SpawnFloorDustRing(globalCtx, &this->actor, &sp34, 50.0f, 0, 2.0f, 0, 0, 0);
}

s32 func_80AD4B08(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 ret;

    if (SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId) == 0x15) {
        ret = true;
    } else {
        ret = false;
    }
    return ret;
}

s32 func_80AD4B4C(EnTrt2* this, GlobalContext* globalCtx) {
    s32 sp24 = false;
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        sp24 = true;
        this->actor.speedXZ = 0.0f;
        func_80AD349C(this);
        this->unk_3B4 = this->unk_3B2;
        if (this->actor.bgCheckFlags & 1) {
            if ((player->transformation != PLAYER_FORM_HUMAN) && (player->transformation != PLAYER_FORM_FIERCE_DEITY)) {
                this->unk_3A8 = 0x84F;
            }
            func_80AD3DA4(this, globalCtx);
        } else if ((player->transformation == PLAYER_FORM_HUMAN) ||
                   (player->transformation == PLAYER_FORM_FIERCE_DEITY)) {
            this->unk_3B2 = 16;
            this->actor.velocity.y = 1.5f;
        } else {
            this->unk_3A8 = 0x84F;
            this->unk_3D8 = true;
            func_80AD3380(&this->skelAnime, sAnimations, 7);
            this->unk_3B2 = 7;
        }
    }
    return sp24;
}

s32 func_80AD4C4C(EnTrt2* this) {
    if (this->actor.bgCheckFlags & 1) {
        if (this->actor.xzDistToPlayer < 100.0f) {
            return true;
        }
    } else if ((this->actor.xzDistToPlayer > 50.0f) && (this->actor.xzDistToPlayer < 200.0f)) {
        return true;
    }
    return false;
}

s32 func_80AD4CCC(EnTrt2* this, GlobalContext* globalCtx) {
    s16 sp1E = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    Player* player = GET_PLAYER(globalCtx);

    if (((this->unk_3B2 == 4) || (this->unk_3B2 == 5)) && this->actor.isTargeted && !(this->actor.bgCheckFlags & 1) &&
        ((player->transformation == PLAYER_FORM_HUMAN) || (player->transformation == PLAYER_FORM_FIERCE_DEITY))) {
        this->actor.speedXZ = 0.0f;
        this->actor.velocity.y = 1.5f;
        this->unk_3B2 = 16;
        return true;
    }

    if (func_80AD4C4C(this) && this->actor.isTargeted && (sp1E < 0x4000) && (sp1E > -0x4000)) {
        func_800B863C(&this->actor, globalCtx);
    }

    return true;
}

void func_80AD4DB4(EnTrt2* this, GlobalContext* globalCtx) {
    static Vec3f D_80AD5904 = { 0.0f, 50.0f, 0.0 };

    this->actor.flags &= ~ACTOR_FLAG_10;
    Actor_SetObjectDependency(globalCtx, &this->actor);
    Actor_SetScale(&this->actor, 0.008f);
    this->path = SubS_GetPathByIndex(globalCtx, ENTRT2_GET_FC00(&this->actor), 0x3F);
    this->unk_3AE = Rand_S16Offset(100, 50);
    this->unk_3B0 = 10;
    this->unk_3A8 = 0;

    this->actor.world.pos.x += D_80AD5904.x;
    this->actor.world.pos.y += D_80AD5904.y;
    this->actor.world.pos.z += D_80AD5904.z;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    func_80AD469C(this, globalCtx);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.colChkInfo.cylRadius = 50;

    this->unk_3C0 = 0;
    this->unk_3D8 = false;
    this->unk_3DA = this->actor.cutscene;
    this->unk_3B6 = 20;
    this->unk_3B8 = 0;
    this->unk_3BC = func_80AD4608;

    if (gSaveContext.save.weekEventReg[12] & 8) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (gSaveContext.save.weekEventReg[84] & 0x40) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if ((globalCtx->sceneNum == SCENE_20SICHITAI) || (globalCtx->sceneNum == SCENE_20SICHITAI2)) {
        if (gSaveContext.save.day == 2) {
            if (!(gSaveContext.save.weekEventReg[15] & 0x80)) {
                gSaveContext.save.weekEventReg[15] |= 0x80;
                this->unk_3B2 = 3;
            } else {
                Actor_MarkForDeath(&this->actor);
                return;
            }
        } else {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    } else if (gSaveContext.save.day == 2) {
        if (gSaveContext.save.weekEventReg[15] & 0x80) {
            this->unk_3B2 = 4;
        } else {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    } else if (gSaveContext.save.day == 3) {
        this->unk_3B2 = 4;
    }
    this->actionFunc = func_80AD4FE4;
}

void func_80AD4FE4(EnTrt2* this, GlobalContext* globalCtx) {
    static EnTrt2UnkFunc2 D_80AD5910[] = {
        func_80AD3664, func_80AD36EC, func_80AD38B8, func_80AD381C, func_80AD3530, func_80AD3A24, func_80AD434C,
        func_80AD3CEC, func_80AD3BE4, func_80AD3C94, func_80AD417C, func_80AD3EF0, func_80AD3FF4, func_80AD4110,
        func_80AD40AC, func_80AD4550, func_80AD3B6C, func_80AD3AE4, func_80AD4298, func_80AD431C, func_80AD3E34,
    };

    this->unk_3BC(this);

    D_80AD5910[this->unk_3B2](this, globalCtx);
    Actor_MoveWithGravity(&this->actor);

    if (globalCtx->sceneNum != SCENE_20SICHITAI) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 26.0f, 10.0f, 0.0f, 5);
    }

    Actor_SetFocus(&this->actor, 90.0f);
    SkelAnime_Update(&this->skelAnime);
}

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 3, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

void EnTrt2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt2* this = THIS;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actionFunc = func_80AD4DB4;
}

void EnTrt2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt2* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTrt2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt2* this = THIS;

    if ((this->unk_3B2 != 6) && (this->unk_3B2 != 10) && (this->unk_3B2 != 13) && (this->unk_3B2 != 14) &&
        (this->unk_3B2 != 16) && (this->unk_3B2 != 8) && (this->unk_3B2 != 9)) {
        func_80AD4B4C(this, globalCtx);
    }

    this->actionFunc(this, globalCtx);

    func_80AD341C(this, globalCtx);
    func_80AD5234(this, globalCtx);

    if ((this->unk_3B2 != 6) && (this->unk_3B2 != 10) && (this->unk_3B2 != 13) && (this->unk_3B2 != 14) &&
        (this->unk_3B2 != 16) && (this->unk_3B2 != 8) && (this->unk_3B2 != 9)) {
        func_80AD4CCC(this, globalCtx);
    }
}

void func_80AD5234(EnTrt2* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp40;
    Vec3f sp34;

    Math_SmoothStepToS(&this->unk_3D6, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 4, 0x38E0, 1);
    this->unk_3D6 = CLAMP(this->unk_3D6, -0x38E0, 0x38E0);

    sp40 = player->actor.world.pos;

    if (this->unk_3B2 == 8) {
        sp40.y = player->bodyPartsPos[7].y + 3.0f;
    } else {
        sp40.y = player->bodyPartsPos[7].y + 45.0f;
    }

    sp34 = this->actor.world.pos;

    Math_SmoothStepToS(&this->unk_3D4, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x1C70, 1);
    this->unk_3D4 = CLAMP(this->unk_3D4, -0x1C70, 0x1C70);
}

void func_80AD5394(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4) {
    Vec3f sp7C;
    Vec3f sp70 = gZeroVec3f;
    Vec3s sp68;
    MtxF sp28;

    Matrix_MultiplyVector3fByState(&sp70, &sp7C);
    Matrix_CopyCurrentState(&sp28);
    func_8018219C(&sp28, &sp68, 0);

    *arg2 = sp7C;

    if (arg4) {
        sp68.x += arg0;
        sp68.y += arg1;
        Math_SmoothStepToS(&arg3->x, sp68.x, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&arg3->y, sp68.y, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&arg3->z, sp68.z, 4, 0x1FFE, 1);
    } else {
        arg3->x = sp68.x;
        arg3->y = sp68.y;
        arg3->z = sp68.z;
    }
}

s32 EnTrt2_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnTrt2* this = THIS;

    if ((limbIndex == 8) || (limbIndex == 13) || (limbIndex == 19)) {
        rot->y += (s16)Math_SinS(this->unk_33C[limbIndex]) * 200;
        rot->z += (s16)Math_CosS(this->unk_372[limbIndex]) * 200;
    }
    return false;
}

void EnTrt2_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTrt2* this = THIS;
    Vec3f sp30 = { 0.0f, -30.0f, 0.0f };
    s32 phi_v0 = false;

    if (this->unk_3B2 >= 8) {
        phi_v0 = true;
    }

    if (limbIndex == 21) {
        func_80AD5394(this->unk_3D4, this->unk_3D6, &this->unk_3C8, &this->unk_3C2, phi_v0);
        Matrix_InsertTranslation(this->unk_3C8.x, this->unk_3C8.y, this->unk_3C8.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_3C2.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_3C2.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_3C2.z, MTXMODE_APPLY);
        Matrix_MultiplyVector3fByState(&sp30, &this->actor.focus.pos);
    }
}

void EnTrt2_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnTrt2* this = THIS;

    if (limbIndex == 21) {
        Matrix_InsertTranslation(this->unk_3C8.x, this->unk_3C8.y, this->unk_3C8.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_3C2.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_3C2.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_3C2.z, MTXMODE_APPLY);
    }
}

void func_80AD56E8(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80AD5978[] = {
        object_trt_Tex_00B0B8,
        object_trt_Tex_00B8B8,
        object_trt_Tex_00C0B8,
    };
    s32 pad;
    EnTrt2* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AD5978[this->unk_3B8]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AD5978[this->unk_3B8]));

    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnTrt2_OverrideLimbDraw, EnTrt2_PostLimbDraw,
                                   EnTrt2_TransformLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
