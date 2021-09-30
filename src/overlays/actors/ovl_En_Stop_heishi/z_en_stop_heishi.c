/*
 * File: z_en_stop_heishi.c
 * Overlay: ovl_En_Stop_heishi
 * Description: Clock Town - Gate-Blocking Soldier
 */

#include "z_en_stop_heishi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnStopheishi*)thisx)

void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnStopheishi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE85C4(EnStopheishi* this, GlobalContext* globalCtx);
void func_80AE7E9C(EnStopheishi* this);

extern AnimationHeader D_06004AC0;
extern AnimationHeader D_06005320;
extern AnimationHeader D_06006C18;
extern AnimationHeader D_0600DC7C;
extern AnimationHeader D_060057BC;
extern AnimationHeader D_06005D28;
extern AnimationHeader D_060064C0;
extern AnimationHeader D_06000A54;

const ActorInit En_Stop_heishi_InitVars = {
    ACTOR_EN_STOP_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStopheishi),
    (ActorFunc)EnStopheishi_Init,
    (ActorFunc)EnStopheishi_Destroy,
    (ActorFunc)EnStopheishi_Update,
    (ActorFunc)EnStopheishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 50, 260, 0, { 0, 0, 0 } },
};

typedef struct struct_80AE88DC {
    u16 textId;
    u16 unk_02;
} struct_80AE88DC;

struct_80AE88DC D_80AE88DC[] = {
    { 0x0516, 0x0517 }, { 0x051A, 0x0000 }, { 0x051C, 0x0000 }, { 0x051E, 0x0000 }, { 0x0520, 0x0521 },
    { 0x0524, 0x0000 }, { 0x0526, 0x0000 }, { 0x0528, 0x0000 }, { 0x052A, 0x052B }, { 0x052E, 0x0000 },
    { 0x0530, 0x0000 }, { 0x0532, 0x0000 }, { 0x0534, 0x0535 }, { 0x0538, 0x0000 }, { 0x053A, 0x0000 },
    { 0x053C, 0x0000 }, { 0x0518, 0x0519 }, { 0x051B, 0x0000 }, { 0x051D, 0x0000 }, { 0x051F, 0x0000 },
    { 0x0522, 0x0523 }, { 0x0525, 0x0000 }, { 0x0527, 0x0000 }, { 0x0529, 0x0000 }, { 0x052C, 0x052D },
    { 0x052F, 0x0000 }, { 0x0531, 0x0000 }, { 0x0533, 0x0000 }, { 0x0536, 0x0537 }, { 0x0539, 0x0000 },
    { 0x053B, 0x0000 }, { 0x053D, 0x0000 }, { 0x0514, 0x0000 }, { 0x0560, 0x0000 }, { 0x0562, 0x0000 },
    { 0x0564, 0x0000 }, { 0x0515, 0x0000 }, { 0x0561, 0x0000 }, { 0x0563, 0x0000 }, { 0x0565, 0x0000 },
};

typedef struct struct_80AE897C {
    u16 textId;
    u16 unk_02;
} struct_80AE897C;

struct_80AE897C D_80AE897C[] = {
    { 0x0540, 0x0541 }, { 0x0542, 0x0000 }, { 0x0543, 0x0000 }, { 0x0543, 0x0000 }, { 0x0547, 0x0548 },
    { 0x0549, 0x0000 }, { 0x054A, 0x0000 }, { 0x054B, 0x0000 }, { 0x054F, 0x0550 }, { 0x0551, 0x0000 },
    { 0x0552, 0x0000 }, { 0x0553, 0x0000 }, { 0x0557, 0x0558 }, { 0x0559, 0x0000 }, { 0x055A, 0x0000 },
    { 0x055A, 0x0000 }, { 0x0544, 0x0545 }, { 0x0546, 0x0000 }, { 0x0546, 0x0000 }, { 0x0546, 0x0000 },
    { 0x054C, 0x054D }, { 0x054E, 0x0000 }, { 0x054E, 0x0000 }, { 0x054E, 0x0000 }, { 0x0554, 0x0555 },
    { 0x0556, 0x0000 }, { 0x0556, 0x0000 }, { 0x0556, 0x0000 }, { 0x055B, 0x055C }, { 0x055D, 0x0000 },
    { 0x055D, 0x0000 }, { 0x055D, 0x0000 }, { 0x053E, 0x0000 }, { 0x053E, 0x0000 }, { 0x053E, 0x0000 },
    { 0x053E, 0x0000 }, { 0x053F, 0x0000 }, { 0x053F, 0x0000 }, { 0x053F, 0x0000 }, { 0x053F, 0x0000 },
};

static AnimationHeader* sAnimations[] = {
    &D_06004AC0, &D_06005320, &D_06006C18, &D_0600DC7C, &D_060057BC, &D_06005D28, &D_060064C0, &D_06000A54,

};

extern FlexSkeletonHeader D_0600D640;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Init.s")
void EnStopheishi_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnStopheishi* this = THIS;
    f32 temp_f10;
    s16 zRot;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600D640, &D_06006C18, this->limbDrawTable,
                     this->transitionDrawTable, 17);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_276 = ((this->actor.params >> 0xC) & 0xF);
    this->unk_27A = (this->actor.params & 0x3F);
    this->unk_288 = (this->actor.world.rot.z * 40.0f) + 50.0f;
    this->actor.world.rot.z = 0;
    if (this->unk_27A == 0x7F) {
        this->unk_27A = -1;
    }
    if ((this->unk_27A >= 0) && (Flags_GetSwitch(globalCtx, this->unk_27A) != 0)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actor.targetMode = 0;
    this->actor.gravity = -3.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_280 = this->actor.world.rot.y;
    this->unk_284 = 6;
    func_80AE7E9C(this);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Destroy.s")

void EnStopHeishi_ChangeAnim(EnStopheishi* this, s32 animIndex) { // Set anim?
    s32 mode;
    f32 phi_f0;

    this->unk_268 = animIndex;
    this->currentAnimFrameCount = SkelAnime_GetFrameCount(sAnimations[animIndex]);
    mode = 2;
    phi_f0 = -10.0f;
    if ((animIndex >= 2) && (animIndex != 4)) {
        mode = 0;
    }
    if (animIndex == 5) {
        phi_f0 = 0.0f;
    }
    SkelAnime_ChangeAnim(&this->skelAnime, sAnimations[animIndex], 1.0f, 0.0f, this->currentAnimFrameCount, mode,
                         phi_f0);
}

void func_80AE75C8(EnStopheishi* this, GlobalContext* globalCtx) {
    s32 yawDiff;
    Player* player;
    Vec3f playerPos;

    yawDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y));

    this->unk_260 = 0;

    if (this->actor.xzDistToPlayer < 200.0f) {
        player = PLAYER;
        if (yawDiff < 0x4E20) {
            this->unk_260 = (this->actor.yawTowardsPlayer - this->actor.world.rot.y);
            if (this->unk_260 >= 0x2711) {
                this->unk_260 = 0x2710;
            } else if (this->unk_260 < -0x2710) {
                this->unk_260 = -0x2710;
            }
        }

        Math_Vec3f_Copy(&playerPos, &player->actor.world.pos);

        if ((player->transformation == PLAYER_FORM_DEKU) || (player->transformation == PLAYER_FORM_HUMAN)) {
            playerPos.y += (57.0f + BREG(34));
        } else {
            playerPos.y += (70.0f + BREG(35));
        }
        this->pitchToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, &playerPos);
    }
}

void func_80AE7718(EnStopheishi* this) {
    if (this->unk_272 != 0) {
        this->unk_272--;
    }
    this->pitchToPlayer = -0xBB8;
    this->unk_260 = 0;
    if (this->unk_284 < 6) {
        this->unk_260 = 0x1770;
        if (!(this->unk_284 & 7)) {
            this->unk_260 = -0x1770;
        }
        if (this->unk_272 == 0) {
            this->unk_284++;
            this->unk_272 = 10;
            if (this->unk_284 >= 6) {
                this->unk_272 = 50;
            }
        }
    } else if ((this->unk_272 == 0) && (Quake_NumActiveQuakes() != 0) && (this->unk_284 >= 6)) {
        this->unk_284 = 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE77D4.s")

/*//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE795C.s")
void func_80AE795C(EnStopheishi* this, GlobalContext* globalCtx) {
    f32 currentFrame;
    Vec3f homePos;
    f32 sp48;
    Player* player;
    // f32 temp_f12;
    // f32 temp_f18;
    f32 temp_f2;
    s32 yawDiff;
    s16 yawHomeToPlayer;
    f32 phi_f12;

    player = PLAYER;
    currentFrame = this->skelAnime.animCurrentFrame;
    yawDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.home.rot.y));
    // if ((s32)yawDiff < 0) {
    //    yawDiff = -(s32)yawDiff;
    //} else {
    //    yawDiff = (s32)yawDiff;
    //}
    if (yawDiff < 0x2000) {
        this->unk_280 = this->actor.yawTowardsPlayer;
    }
    if (this->unk_274 != 4) {
        temp_f2 = fabsf((f32)this->actor.yawTowardsPlayer -
                        (f32)Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos)) *
                  0.01f * 5.0f;
        if (temp_f2 < 1.0f) {
            this->skelAnime.animPlaybackSpeed = 1.0f;
        } else {
            // if (temp_f2 > 5.0f) {
            //    phi_f0 = 5.0f;
            //} else {
            //    phi_f0 = temp_f2;
            //}
            this->skelAnime.animPlaybackSpeed = (temp_f2 > 5.0f) ? 5.0f : temp_f2;
        }
    }
    yawHomeToPlayer = Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos);
    sp48 = fabsf(this->actor.home.pos.x - player->actor.world.pos.x);
    homePos.y = fabsf(this->actor.home.pos.z - player->actor.world.pos.z);
    Math_Vec3f_Copy(&homePos, &this->actor.home.pos);
    if (this->actor.home.rot.y == -0x8000) {
        if (yawHomeToPlayer > 0) {
            sp48 *= Math_SinS(this->actor.home.rot.y + 0xC000);
            homePos.y = Math_CosS(this->actor.home.rot.y + 0xC000) * homePos.y;
        } else {
            sp48 *= Math_SinS(this->actor.home.rot.y + 0x4000);
            homePos.y = Math_CosS(this->actor.home.rot.y + 0x4000) * homePos.y;
        }
    } else if (yawHomeToPlayer < this->actor.home.rot.y) {
        sp48 *= Math_SinS(this->actor.home.rot.y + 0xC000);
        homePos.y = Math_CosS(this->actor.home.rot.y + 0xC000) * homePos.y;
    } else {
        sp48 *= Math_SinS(this->actor.home.rot.y + 0x4000);
        homePos.y = Math_CosS(this->actor.home.rot.y + 0x4000) * homePos.y;
    }
    if (this->unk_288 < sp48) {
        sp48 = this->unk_288;
    } else {
        if (sp48 < -this->unk_288) {
            sp48 = -this->unk_288;
        }
    }
    homePos.x = homePos.x + sp48;
    if (this->unk_288 < homePos.y) {
        homePos.y = this->unk_288;
    } else {
        this->unk_288 = -this->unk_288;
        if (homePos.y < this->unk_288) {
            homePos.y = this->unk_288;
        }
    }
    // homePos.x = temp_f18;
    // homePos.y += phi_f12;
    Math_ApproachF(&this->actor.world.pos.x, homePos.x, 0.5f, this->unk_28C);
    Math_ApproachF(&this->actor.world.pos.z, homePos.y, 0.5f, this->unk_28C);
    Math_ApproachF(&this->unk_28C, 50.0f, 0.3f, 1.0f);
    switch (this->unk_274) {
        case 0:
            if (gSaveContext.day != 3) {
                EnStopHeishi_ChangeAnim(this, 4);
                this->unk_274 = 2;
            } else {
                EnStopHeishi_ChangeAnim(this, 2);
                this->unk_274 = 1;
            }
            break;
        case 1:
            EnStopHeishi_ChangeAnim(this, 4);
            this->unk_274 = 2;
            break;
        case 2:
            if (this->currentAnimFrameCount <= currentFrame) {
                EnStopHeishi_ChangeAnim(this, 5);
                this->unk_274 = 3;
            }
            break;
        case 3:
            if ((fabsf(this->actor.world.pos.x - homePos.x) < 2.0f) &&
                (fabsf(this->actor.world.pos.z - homePos.z) < 2.0f)) {
                this->skelAnime.animPlaybackSpeed = 1.0f;
                EnStopHeishi_ChangeAnim(this, 6);
                this->unk_274 = 4;
            }
            break;
        case 4:
            if ((fabsf(this->actor.world.pos.x - homePos.x) > 4.0f) ||
                (fabsf(this->actor.world.pos.z - homePos.z) > 4.0f)) {
                EnStopHeishi_ChangeAnim(this, 5);
                this->unk_274 = 3;
            }
            break;
    }
    this->unk_264 = 0;
    this->unk_270 = 0x14;
    this->pitchToPlayer = 0;
    Math_Vec3f_Copy(&homePos, &player->actor.world.pos);
    if ((this->unk_276 == 3) &&
        ((player->transformation == PLAYER_FORM_DEKU) || (player->transformation == PLAYER_FORM_HUMAN))) {
        homePos.y += 77.0f + BREG(37);
        this->pitchToPlayer = Math_Vec3f_Pitch((Vec3f*)&this->actor.focus, &homePos);
    }
}*/

void func_80AE795C(EnStopheishi* this, GlobalContext* globalCtx) {
    f32 sp58;
    Vec3f oldHomePos;
    f32 xDiff;
    f32 zDiff;
    s16 yawHomeToPlayer;
    Player* player;
    s32 yawDiff;
    //f32 xOffset;
    f32 temp_f2;
    //s16 temp_v0;
    //s32 phi_a0;
    f32 phi_f0;

    sp58 = this->skelAnime.animCurrentFrame;
    player = PLAYER;
    yawDiff = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.home.rot.y));
    //temp_v0 =  this->actor.yawTowardsPlayer - this->actor.home.rot.y;
    //if ((s32)temp_v0 < 0) {
    //    phi_a0 = -(s32)temp_v0;
    //} else {
    //    phi_a0 = (s32)temp_v0;
    //}

    if (yawDiff < 0x2000) {
        this->unk_280 =  this->actor.yawTowardsPlayer;
    }
    if (this->unk_274 != 4) {
        temp_f2 = fabsf((f32)this->actor.yawTowardsPlayer - (f32)Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos)) *
                  0.01f * 5.0f;
        if (temp_f2 < 1.0f) {
            this->skelAnime.animPlaybackSpeed = 1.0f;
        } else {
            if (temp_f2 > 5.0f) {
                phi_f0 = 5.0f;
            } else {
                phi_f0 = temp_f2;
            }
            this->skelAnime.animPlaybackSpeed = phi_f0;
        }
    }
    yawHomeToPlayer = Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos);
    xDiff = fabsf(this->actor.home.pos.x - player->actor.world.pos.x);
    zDiff = fabsf(this->actor.home.pos.z - player->actor.world.pos.z);
    Math_Vec3f_Copy(&oldHomePos, &this->actor.home.pos);
    if ( this->actor.home.rot.y == -0x8000) {
        if (yawHomeToPlayer > 0) {
            xDiff *= Math_SinS((s16)( this->actor.home.rot.y + 0xC000));
            zDiff = Math_CosS((s16)(this->actor.home.rot.y + 0xC000)) * zDiff;
        } else {
            xDiff *= Math_SinS((s16)( this->actor.home.rot.y + 0x4000));
            zDiff = Math_CosS((s16)(this->actor.home.rot.y + 0x4000)) * zDiff;
        }
    } else if (yawHomeToPlayer < this->actor.home.rot.y) {
        xDiff *= Math_SinS((s16)( this->actor.home.rot.y + 0xC000));
        zDiff = Math_CosS((s16)(this->actor.home.rot.y + 0xC000)) * zDiff;
    } else {
        xDiff *= Math_SinS((s16)( this->actor.home.rot.y + 0x4000));
        zDiff = Math_CosS((s16)(this->actor.home.rot.y + 0x4000)) * zDiff;
    }
    if (this->unk_288 < xDiff) {
        xDiff = this->unk_288;
    } else {
     //   temp_f0 = -this->unk_288;
        if (xDiff < -this->unk_288) {
            xDiff = -this->unk_288;
        }
    }
    //xOffset = oldHomePos.x + xDiff;
    if (this->unk_288 < zDiff) {
        zDiff = this->unk_288;
    } else {
       // temp_f0_2 = -this->unk_288;
        if (zDiff < -this->unk_288) {
            zDiff = -this->unk_288;
        }
    }
    //oldHomePos.x = xOffset;
    oldHomePos.x += xDiff;
    oldHomePos.z += zDiff;
    Math_ApproachF(&this->actor.world.pos.x, oldHomePos.x, 0.5f, this->unk_28C);
    Math_ApproachF(&this->actor.world.pos.z, oldHomePos.z, 0.5f, this->unk_28C);
    Math_ApproachF(&this->unk_28C, 50.0f, 0.3f, 1.0f);
    switch (this->unk_274) {
        case 0:
            if (gSaveContext.day != 3) {
                EnStopHeishi_ChangeAnim(this, 4);
                this->unk_274 = 2;
            } else {
                EnStopHeishi_ChangeAnim(this, 2);
                this->unk_274 = 1;
            }
            break;
        case 1:
            EnStopHeishi_ChangeAnim(this, 4);
            this->unk_274 = 2;
            break;
        case 2:
            if (this->currentAnimFrameCount <= sp58) {
                EnStopHeishi_ChangeAnim(this, 5);
                this->unk_274 = 3;
            }
            break;
        case 3:
            if ((fabsf(this->actor.world.pos.x - oldHomePos.x) < 2.0f) && (fabsf(this->actor.world.pos.z - oldHomePos.z) < 2.0f)) {
                this->skelAnime.animPlaybackSpeed = 1.0f;
                EnStopHeishi_ChangeAnim(this, 6);
                this->unk_274 = 4;
            }
            break;
        case 4:
            if ((fabsf(this->actor.world.pos.x - oldHomePos.x) > 4.0f) || (fabsf(this->actor.world.pos.z - oldHomePos.z) > 4.0f)) {
                EnStopHeishi_ChangeAnim(this, 5);
                this->unk_274 = 3;
            }
            break;
    }
    this->unk_264 = 0;
    this->unk_270 = 0x14;
    this->pitchToPlayer = 0;
    Math_Vec3f_Copy(&oldHomePos, &player->actor.world.pos);

    if ((this->unk_276 == 3) && ((Math_Vec3f_Copy(&oldHomePos, &player->actor.world.pos),
        ((player->transformation == PLAYER_FORM_DEKU) || (player->transformation == PLAYER_FORM_HUMAN))))) {
        oldHomePos.y += 77.0f + (f32)gGameInfo->data[2437];
        this->pitchToPlayer = Math_Vec3f_Pitch(&this->actor.focus.pos, (Vec3f*)&oldHomePos);
    }
}

/*    if ((this->unk_276 == 3) &&
        ((player->transformation == PLAYER_FORM_DEKU) || (player->transformation == PLAYER_FORM_HUMAN))) {
        homePos.y += 77.0f + BREG(37);
        this->pitchToPlayer = Math_Vec3f_Pitch((Vec3f*)&this->actor.focus, &homePos);
    }*/

void func_80AE7E9C(EnStopheishi* this) {
    EnStopHeishi_ChangeAnim(this, 2);
    if ((gSaveContext.day != 3) && (gSaveContext.isNight != 0)) {
        EnStopHeishi_ChangeAnim(this, 3);
    }
    if (gSaveContext.day == 3) {
        EnStopHeishi_ChangeAnim(this, 7);
    }
    this->unk_274 = 0;
    this->unk_278 = 0;
    this->actionFunc = func_80AE7F34;
    this->actor.speedXZ = 0.0f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE7F34.s")
/*void func_80AE7F34(EnStopheishi* this, GlobalContext* globalCtx) {
    Player* player;
    s16 sp32;
    f32 zDistToPlayer;
    f32 xDistToPlayer;
    s16 yawDiff;
    s32 yawDiffAbs;
    u8 temp_v0;
    u8 temp_v0_1;
    s16 phi_a2;
    u16 phi_t8;

    player = PLAYER;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->unk_268 == 5) && (((s32)this->skelAnime.animCurrentFrame % 2) != 0)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SOLDIER_WALK);
    }
    if (gSaveContext.day != 3) {
        func_80AE75C8(this, globalCtx);
    } else {
        func_80AE7718(this);
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_280, 1, 0x1388, 0);
    sp32 = 0;
    if (gSaveContext.isNight != 0) {
        sp32 = 0x20;
    }
    phi_a2 = 0;
    switch (player->transformation) {
        case PLAYER_FORM_HUMAN:
            // temp_v1 = gSaveContext.roomInf[126][5];
            temp_v0_1 = (gSaveContext.roomInf[126][5] & 0xFF000000) >> 0x18;

            if ((temp_v0_1 == 0x10) || (temp_v0_1 == 0x4D) || (temp_v0_1 == 0x4E) || (temp_v0_1 == 0x4F) ||
                    (temp_v0 = (gSaveContext.roomInf[126][5] & 0xFF0000) >> 0x10),
                ((temp_v0 == 0x10)) || (temp_v0 == 0x4D) || (temp_v0 == 0x4E) || (temp_v0 == 0x4F)) {
                if (this->unk_265 != 0) {
                    phi_a2 = 1;
                }
            } else if ((gSaveContext.weekEventReg[0xC] & 0x20) != 0) {
                phi_a2 = 1;
            }
            break;
        case PLAYER_FORM_GORON:
            phi_a2 = 2;
            break;
        case PLAYER_FORM_ZORA:
            phi_a2 = 3;
            break;
        case PLAYER_FORM_DEKU:
            phi_a2 = 4;
            break;
    }

    if (((phi_a2 == 1) || (phi_a2 == 2) || (phi_a2 == 3)) &&
        (((this->unk_268 == 4)) || (this->unk_268 == 5) || (this->unk_268 == 6))) {
        EnStopHeishi_ChangeAnim(this, 2);

        if ((gSaveContext.day != 3) && (gSaveContext.isNight != 0)) {
            EnStopHeishi_ChangeAnim(this, 3);
        }
        if (gSaveContext.day == 3) {
            EnStopHeishi_ChangeAnim(this, 7);
        }
    }
    if ((phi_a2 == 0) || (phi_a2 == 4)) {
        xDistToPlayer = this->actor.home.pos.x - player->actor.world.pos.x;
        zDistToPlayer = this->actor.home.pos.z - player->actor.world.pos.z;
        this->collider.dim.radius = 0x32;
        this->collider.dim.height = 0x104;
        if (sqrtf((xDistToPlayer * xDistToPlayer) + (zDistToPlayer * zDistToPlayer)) < 240.0f) {
            func_80AE795C(this, globalCtx);
        } else {
            func_80AE77D4(this, globalCtx);
        }
    } else {
        this->collider.dim.radius = 0xF;
        this->collider.dim.height = 0x3C;
    }
    if (phi_a2 != 4) {
        //this->unk_27C += (this->unk_276 * 8) + sp32 + (phi_a2 * 2);
        this->unk_27C = this->unk_276 * 8;
        this->unk_27C = this->unk_27C + sp32;
        this->unk_27C = this->unk_27C + (phi_a2 * 2);
    } else {
        this->unk_27C = 0x40;
        if (sp32 != 0) {
            this->unk_27C = 0x48;
        }
        // this->unk_27C = sp32 != 0 ? 0x48 : 0x40;
        this->unk_27C += (this->unk_276 * 2);
    }
    if (gSaveContext.day != 3) {
        this->actor.textId = D_80AE88DC[this->unk_27C].textId;
        this->unk_27E = D_80AE88DC[this->unk_27C].unk_02;
    } else {
        this->actor.textId = D_80AE897C[this->unk_27C].textId;
        this->unk_27E = D_80AE897C[this->unk_27C].unk_02;
    }
    if (this->unk_27E != 0) {
        // temp_v1 = gSaveContext.roomInf[126][5];
        temp_v0 = (gSaveContext.roomInf[126][5] & 0xFF000000) >> 0x18;
        temp_v0_1 = (gSaveContext.roomInf[126][5] & 0xFF0000) >> 0x10;
        if ((temp_v0 == 0x10) || (temp_v0 == 0x4D) || (temp_v0 == 0x4E) || (temp_v0 == 0x4F) || (temp_v0_1 == 0x10) ||
            (temp_v0_1 == 0x4D) || (temp_v0_1 == 0x4E) || (temp_v0_1 == 0x4F)) {
            if (this->actor.textId == 0x516) {
                this->actor.textId = 0x56C;
            } else {
                if (this->actor.textId == 0x520) {
                    this->actor.textId = 0x56EU;
                } else if (this->actor.textId == 0x52A) {
                    this->actor.textId = 0x570;
                } else if (this->actor.textId == 0x534) {
                    this->actor.textId = 0x572;
                } else if (this->actor.textId == 0x518) {
                    this->actor.textId = 0x56D;
                } else if (this->actor.textId == 0x522) {
                    this->actor.textId = 0x56F;
                } else if (this->actor.textId == 0x52C) {
                    this->actor.textId = 0x571;
                } else if (this->actor.textId == 0x536) {
                    this->actor.textId = 0x573;
                }
            }
        } else if (CUR_EQUIP_VALUE(EQUIP_SWORD) == 0) {
            if (this->actor.textId == 0x516) {
                this->actor.textId = 0x55E;
            } else if (this->actor.textId == 0x520) {
                this->actor.textId = 0x566;
            } else if (this->actor.textId == 0x52A) {
                this->actor.textId = 0x568;
            } else if (this->actor.textId == 0x534) {
                this->actor.textId = 0x56A;
            } else if (this->actor.textId == 0x518) {
                this->actor.textId = 0x55F;
            } else if (this->actor.textId == 0x522) {
                this->actor.textId = 0x567;
            } else if (this->actor.textId == 0x52C) {
                this->actor.textId = 0x569;
            } else {
                this->actor.textId = this->actor.textId == 0x536 ? 0x56B : this->actor.textId;
                // phi_t8 = 0x56BU;
                // if (this->actor.textId == 0x536) {
                //    this->actor.textId = phi_t8;
                //}
            }
        }
    }
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    // ABS macro doesn't work here
    if (yawDiff < 0) {
        yawDiffAbs = -yawDiff;
    } else {
        yawDiffAbs = yawDiff;
    }
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->skelAnime.animPlaybackSpeed = 1.0f;
        func_80AE854C(&this->actor, globalCtx);
        return;
    }
    if (yawDiffAbs < 0x4BB9) {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE854C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE85C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE87A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/func_80AE87EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stop_heishi/EnStopheishi_Draw.s")
