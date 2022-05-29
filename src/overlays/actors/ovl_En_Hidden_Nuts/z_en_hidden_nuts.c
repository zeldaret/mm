/*
 * File: z_en_hidden_nuts.c
 * Overlay: ovl_En_Hidden_Nuts
 * Description: Swamp Spider House - Sleeping Deku Scrub
 */

#include "z_en_hidden_nuts.h"
#include "objects/object_hintnuts/object_hintnuts.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_2000000)

#define THIS ((EnHiddenNuts*)thisx)

void EnHiddenNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BDB268(EnHiddenNuts* this);
void func_80BDB2B8(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDB580(EnHiddenNuts* this);
void func_80BDB59C(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDB788(EnHiddenNuts* this);
void func_80BDB7E8(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDB8F4(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDB930(EnHiddenNuts* this);
void func_80BDB978(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDBA28(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDBB48(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDBE70(EnHiddenNuts* this, GlobalContext* globalCtx);
void func_80BDBED4(EnHiddenNuts* this, GlobalContext* globalCtx);

const ActorInit En_Hidden_Nuts_InitVars = {
    ACTOR_EN_HIDDEN_NUTS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HINTNUTS,
    sizeof(EnHiddenNuts),
    (ActorFunc)EnHiddenNuts_Init,
    (ActorFunc)EnHiddenNuts_Destroy,
    (ActorFunc)EnHiddenNuts_Update,
    (ActorFunc)EnHiddenNuts_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 30, 20, 0, { 0, 0, 0 } },
};

static AnimationHeader* D_80BDC0FC[] = {
    &object_hintnuts_Anim_000168, &object_hintnuts_Anim_0024CC, &object_hintnuts_Anim_0026C4,
    &object_hintnuts_Anim_002894, &object_hintnuts_Anim_002B90, &object_hintnuts_Anim_002F7C,
    &object_hintnuts_Anim_003128, &object_hintnuts_Anim_0029BC, &object_hintnuts_Anim_0024CC,
};

u8 D_80BDC120[] = {
    ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE,
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP,
};

void EnHiddenNuts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHiddenNuts* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_hintnuts_Skel_0023B8.sh, &object_hintnuts_Anim_0024CC,
                   this->jointTable, this->morphTable, 10);
    Actor_SetScale(&this->actor, 0.01f);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 0;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    this->unk_21E = ENHIDDENNUTS_GET_F80(&this->actor);
    this->switchFlag = ENHIDDENNUTS_GET_SWITCHFLAG(&this->actor);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->switchFlag >= 0) && Flags_GetSwitch(globalCtx, this->switchFlag)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->unk_21E == 0x1F) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->path = SubS_GetPathByIndex(globalCtx, this->unk_21E, 0x3F);
    this->unk_226 = this->actor.cutscene;
    func_801A5080(2);
    func_80BDB268(this);
}

void EnHiddenNuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHiddenNuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BDB1B4(EnHiddenNuts* this, s32 arg1) {
    f32 sp34;
    f32 sp30;

    this->unk_220 = arg1;
    sp34 = 0.0f;
    sp30 = -4.0f;
    this->unk_22C = Animation_GetLastFrame(D_80BDC0FC[arg1]);
    if (this->unk_220 == 1) {
        sp34 = this->unk_22C;
        sp30 = 0.0f;
    }
    Animation_Change(&this->skelAnime, D_80BDC0FC[this->unk_220], 1.0f, sp34, this->unk_22C, D_80BDC120[this->unk_220],
                     sp30);
}

void func_80BDB268(EnHiddenNuts* this) {
    this->actor.textId = 0x234;
    this->unk_228 = 1600.0f;
    this->actor.shape.yOffset = 1600.0f;
    func_80BDB1B4(this, 1);
    this->unk_21A = 0;
    this->actionFunc = func_80BDB2B8;
}

void func_80BDB2B8(EnHiddenNuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NEMURI_SLEEP - SFX_FLAG);

    if (player->stateFlags2 & 0x8000000) {
        if (this->unk_20A == 0) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            this->unk_20A = 1;
        }
    } else {
        this->unk_20A = 0;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) != 0) {
        func_80BDB580(this);
        return;
    }

    if (this->unk_218 == 0) {
        Vec3f sp94 = { 0.0f, 0.0f, 0.0f };
        Vec3f sp88 = { 0.0f, 0.0f, 0.0f };
        Color_RGBA8 sp84 = { 255, 255, 255, 255 };
        Color_RGBA8 sp80 = { 150, 150, 150, 0 };
        Vec3f sp74;

        for (i = 0; i < 3; i++) {
            sp94.y = Rand_ZeroFloat(1.0f) + 1.0f;

            Math_Vec3f_Copy(&sp74, &this->actor.world.pos);

            sp74.x += randPlusMinusPoint5Scaled(15.0f);
            sp74.z += randPlusMinusPoint5Scaled(15.0f);

            EffectSsDtBubble_SpawnCustomColor(globalCtx, &sp74, &sp94, &sp88, &sp84, &sp80, Rand_S16Offset(120, 90), 30,
                                              1);
        }
        this->unk_218 = 30;
    }

    if (!(this->actor.xzDistToPlayer > 120.0f)) {
        if ((globalCtx->msgCtx.ocarinaMode == 3) && (globalCtx->msgCtx.unk1202E == 0)) {
            globalCtx->msgCtx.ocarinaMode = 4;
            func_80BDB788(this);
        } else if (func_801A5100() == 2) {
            func_80BDB788(this);
        } else {
            func_800B8614(&this->actor, globalCtx, BREG(13) + 100.0f);
        }
    }
}

void func_80BDB580(EnHiddenNuts* this) {
    this->unk_21A = 1;
    this->actionFunc = func_80BDB59C;
}

void func_80BDB59C(EnHiddenNuts* this, GlobalContext* globalCtx) {
    s32 i;

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NEMURI_SLEEP - SFX_FLAG);

    if (this->unk_218 == 0) {
        Vec3f sp98 = { 0.0f, 0.0f, 0.0f };
        Vec3f sp8C = { 0.0f, 0.0f, 0.0f };
        Color_RGBA8 sp88 = { 255, 255, 255, 255 };
        Color_RGBA8 sp84 = { 150, 150, 150, 0 };
        Vec3f sp78;

        for (i = 0; i < 3; i++) {
            sp98.y = Rand_ZeroFloat(1.0f) + 1.0f;

            Math_Vec3f_Copy(&sp78, &this->actor.world.pos);

            sp78.x += randPlusMinusPoint5Scaled(15.0f);
            sp78.z += randPlusMinusPoint5Scaled(15.0f);

            EffectSsDtBubble_SpawnCustomColor(globalCtx, &sp78, &sp98, &sp8C, &sp88, &sp84, Rand_S16Offset(120, 90), 30,
                                              1);
        }
        this->unk_218 = 30;
    }

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80BDB268(this);
    }
}

void func_80BDB788(EnHiddenNuts* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.flags |= ACTOR_FLAG_8000000;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DEAD);
    this->unk_21A = 2;
    this->actionFunc = func_80BDB7E8;
}

void func_80BDB7E8(EnHiddenNuts* this, GlobalContext* globalCtx) {
    Vec3f sp3C;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->unk_226);
        return;
    }

    if (!ActorCutscene_GetCanPlayNext(this->unk_226)) {
        ActorCutscene_SetIntentToPlay(this->unk_226);
        return;
    }

    ActorCutscene_StartAndSetUnkLinkFields(this->unk_226, &this->actor);
    this->unk_228 = -1200.0f;

    Math_Vec3f_Copy(&sp3C, &this->actor.world.pos);
    sp3C.y = this->actor.floorHeight + 30.0f;

    EffectSsHahen_SpawnBurst(globalCtx, &sp3C, 4.0f, 0, 10, 3, 15, -1, 10, NULL);

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    func_80BDB1B4(this, 7);
    this->actionFunc = func_80BDB8F4;
}

void func_80BDB8F4(EnHiddenNuts* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_22C <= curFrame) {
        func_80BDB930(this);
    }
}

void func_80BDB930(EnHiddenNuts* this) {
    func_80BDB1B4(this, 3);
    this->unk_21A = 3;
    this->unk_228 = 500.0f;
    this->actionFunc = func_80BDB978;
}

void func_80BDB978(EnHiddenNuts* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 8.0f) ||
        Animation_OnFrame(&this->skelAnime, 18.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUT_FAINT);
    }

    if (this->unk_22C <= curFrame) {
        this->unk_224++;
        if (this->unk_224 >= 2) {
            func_80BDBA28(this, globalCtx);
        }
    }
}

void func_80BDBA28(EnHiddenNuts* this, GlobalContext* globalCtx) {
    Vec3f sp44;

    func_80BDB1B4(this, 2);
    this->unk_228 = 0.0f;

    Math_Vec3f_Copy(&sp44, &this->actor.world.pos);
    sp44.y = this->actor.floorHeight + 30.0f;

    EffectSsHahen_SpawnBurst(globalCtx, &sp44, 4.0f, 0, 10, 3, 15, -1, 10, NULL);

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    this->unk_208 = 1;

    if ((this->path != NULL) && !SubS_CopyPointFromPath(this->path, this->unk_208, &this->unk_20C)) {
        Actor_MarkForDeath(&this->actor);
    }

    this->actor.speedXZ = 2.0f;
    this->actor.gravity = -2.0f;
    this->actor.velocity.y = 4.0f;
    this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_20C);
    this->unk_21A = 4;
    this->actionFunc = func_80BDBB48;
}

void func_80BDBB48(EnHiddenNuts* this, GlobalContext* globalCtx) {
    s32 pad[3];
    f32 sp58 = this->skelAnime.curFrame;
    WaterBox* sp54;
    f32 sp50;
    s16 sp4E = 0;
    Vec3f sp40;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp50,
                             &sp54) &&
        (this->actor.world.pos.y < sp50)) {
        this->actor.velocity.y = 0.0f;
        Math_Vec3f_Copy(&sp40, &this->actor.world.pos);
        sp40.y = sp50;
        this->actor.gravity = 0.0f;

        if ((globalCtx->gameplayFrames % 8) == 0) {
            EffectSsGRipple_Spawn(globalCtx, &sp40, 650, 3150, 0);
        }

        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f) ||
            Animation_OnFrame(&this->skelAnime, 10.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WALK_WATER);
            sp4E = 1;
        }
    }

    if ((sp4E != 0) && (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f) ||
                        Animation_OnFrame(&this->skelAnime, 10.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_20C), 1, 0x1388, 0);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x3E8, 0);

    if (this->unk_220 == 2) {
        if (this->unk_22C <= sp58) {
            this->actor.speedXZ = 0.0f;
            this->actor.velocity.y = 0.0f;
            func_80BDB1B4(this, 6);
        }
    } else {
        Math_ApproachF(&this->actor.world.pos.x, this->unk_20C.x, 0.5f,
                       fabsf(Math_SinS(this->actor.world.rot.y) * (BREG(33) + 8.0f)));
        Math_ApproachF(&this->actor.world.pos.z, this->unk_20C.z, 0.5f,
                       fabsf(Math_CosS(this->actor.world.rot.y) * (BREG(33) + 8.0f)));

        if ((sqrtf(SQ(this->actor.world.pos.x - this->unk_20C.x) + SQ(this->actor.world.pos.z - this->unk_20C.z)) <
             4.0f) &&
            (this->path != NULL)) {
            this->unk_208++;
            if (this->unk_208 >= this->path->count) {
                func_80BDBE70(this, globalCtx);
            } else if ((this->path != NULL) && !SubS_CopyPointFromPath(this->path, this->unk_208, &this->unk_20C)) {
                Actor_MarkForDeath(&this->actor);
            }
        }
    }
}

void func_80BDBE70(EnHiddenNuts* this, GlobalContext* globalCtx) {
    if (this->switchFlag >= 0) {
        Flags_SetSwitch(globalCtx, this->switchFlag);
    }
    func_80BDB1B4(this, 8);
    this->unk_21A = 5;
    this->actionFunc = func_80BDBED4;
}

void func_80BDBED4(EnHiddenNuts* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f sp38;

    if (this->unk_22C <= curFrame) {
        Math_Vec3f_Copy(&sp38, &this->actor.world.pos);
        sp38.y = this->actor.floorHeight;

        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
        EffectSsHahen_SpawnBurst(globalCtx, &sp38, 4.0f, 0, 10, 3, 15, -1, 10, NULL);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnHiddenNuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnHiddenNuts* this = THIS;

    if (this->unk_218 != 0) {
        this->unk_218--;
    }

    Actor_SetFocus(&this->actor, 20.0f);
    SkelAnime_Update(&this->skelAnime);

    this->actionFunc(this, globalCtx);

    Math_ApproachF(&this->actor.shape.yOffset, this->unk_228, 0.5f, 200.0f);

    if (this->unk_21A >= 4) {
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 40.0f, 0x1D);
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnHiddenNuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHiddenNuts* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, &this->actor);
}
