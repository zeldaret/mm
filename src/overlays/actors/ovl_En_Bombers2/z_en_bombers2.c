/*
 * File: z_en_bombers2.c
 * Overlay: ovl_En_Bombers2
 * Description: Bombers - Hideout Guard
 */

#include "z_en_bombers2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBombers2*)thisx)

void EnBombers2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C04BA0(EnBombers2* this, GlobalContext* globalCtx);
void func_80C04D8C(EnBombers2* this, GlobalContext* globalCtx);
void func_80C0520C(EnBombers2* this, GlobalContext* globalCtx);
void func_80C04B40(EnBombers2* this);
void func_80C04AAC(EnBombers2* this, s32 animIndex, f32 playSpeed);
void func_80C04D00(EnBombers2* this);
void func_80C050B8(EnBombers2* this, GlobalContext* globalCtx);

const ActorInit En_Bombers2_InitVars = {
    ACTOR_EN_BOMBERS2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBombers2),
    (ActorFunc)EnBombers2_Init,
    (ActorFunc)EnBombers2_Destroy,
    (ActorFunc)EnBombers2_Update,
    (ActorFunc)EnBombers2_Draw,
};

u16 D_80C058A0[] = {
    0x0727, 0x0728, 0x0726, 0x0729, 0x072B, 0x0725, 0x072A, 0x073C,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C058B0 = {
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
    { 35, 30, 0, { 0, 0, 0 } },
};

AnimationHeader* D_80C058DC[] = {
    0x060064B8, 0x060053F4, 0x0601007C, 0x0600349C, 0x060060E8, 0x06005DC4, 0x060026B0,
};

u8 D_80C058F8[] = {
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00,
};

Gfx D_80C05900[] = {
    gsDPSetPrimColor(0, 0xFF, 198, 140, 0, 255),
    gsSPEndDisplayList(),
};

Gfx* D_80C05910 = D_80C05900;

void* D_80C05914[] = { //Eye textures
    0x0600C520,
    0x0600CD20,
    0x0600D520,
};

void* D_80C05920 = 0x0600E220;

extern ColliderCylinderInit D_80C058B0;

extern AnimationHeader D_060064B8;
extern FlexSkeletonHeader D_0600F82C;

void EnBombers2_Init(Actor* thisx, GlobalContext* globalCtx) {
    f32 cos;
    EnBombers2* this = (EnBombers2*)thisx;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600F82C, &D_060064B8, this->morphTable, this->jointTable, 21);
    this->actor.targetMode = 6;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80C058B0);
    if ((gSaveContext.weekEventReg[0x49] & 0x80) || (gSaveContext.entranceIndex == 0xD220)) {
        this->actor.world.pos.x += Math_SinS(this->actor.home.rot.y + 0xC100) * 50.0f;
        cos = Math_CosS(this->actor.home.rot.y + 0xC100) * 50.0f;
        this->unk_2AC = 1;
        this->actor.world.pos.z += cos;
    }
    this->cutscene = this->actor.cutscene;
    if (this->cutscene == 0) {
        Actor_MarkForDeath(&this->actor);
    }
    func_80C04B40(this);
}

void EnBombers2_Destroy(Actor* thisx, GlobalContext* globalCtx){
    EnBombers2* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80C04AAC(EnBombers2* this, s32 animIndex, f32 playSpeed) { // Set anim
    f32 lastFrame;

    this->animIndex = animIndex;
    lastFrame = Animation_GetLastFrame(D_80C058DC[this->animIndex]);
    this->lastAnimFrame = lastFrame;
    Animation_Change(&this->skelAnime, D_80C058DC[this->animIndex], playSpeed, 0.0f, lastFrame,
                     D_80C058F8[this->animIndex], -10.0f);
}

void func_80C04B40(EnBombers2* this) {
    if (this->unk_2AC == 0) {
        func_80C04AAC(this, 4, 1.0f);
    } else {
        func_80C04AAC(this, 0, 1.0f);
    }
    this->unk_2C0 = 0;
    this->actionFunc = func_80C04BA0;
}

void func_80C04BA0(EnBombers2* this, GlobalContext* globalCtx) {
    s32 yawDiffAbs;
    s16 yawDiff;
    Player* player;

    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    yawDiffAbs = ABS_ALT(yawDiff);
    player = GET_PLAYER(globalCtx);

    switch (player->transformation) {
        case 1:
        case 2:
            this->unk_2C2 = 1;
            this->unk_2CE = 5;
            break;
        case 3:
        case 4:
            this->unk_2C2 = 2;
            this->unk_2CE = 5;
            break;
    }
    if (this->unk_2AC != 0) {
        this->unk_2C2 = 7;
    }
    this->actor.textId = D_80C058A0[this->unk_2C2];

    if (Text_GetFaceReaction(globalCtx, 0x15) != 0) {
        this->actor.textId = Text_GetFaceReaction(globalCtx, 0x15);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) != 0) {
        this->unk_2B6 = this->actor.world.rot.y;
        gSaveContext.weekEventReg[0x56] |= 2;
        func_80C04D00(this);
        return;
    }
    if (yawDiffAbs < 0x3BB5) {
        func_800B8614(&this->actor, globalCtx, 70.0f);
    }
}

void func_80C04D00(EnBombers2* this) {
    if ((this->unk_2C2 == 0) || (this->unk_2C2 == 1)) {
        func_80C04AAC(this, 5, 1.0f);
    } else {
        func_80C04AAC(this, 1, 1.0f);
    }

    this->unk_2A8 = 0;
    if (this->unk_2AC != 0) {
        func_80C04AAC(this, 6, 1.0f);
    }
    this->unk_2C0 = 1;
    this->actionFunc = func_80C04D8C;
}

void func_80C04D8C(EnBombers2* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp = this->skelAnime.curFrame;

    if ((this->unk_2AC == 0) && (this->lastAnimFrame <= temp)) {
        if ((this->unk_2A8 & 1) == 0) {
            func_80C04AAC(this, 1, 1.0f);
        } else {
            func_80C04AAC(this, 5, 1.0f);
        }
        this->unk_2A8++;
        this->unk_2A8 &= 1;
    }
    switch (player->transformation) {
        case 4:
            this->unk_28E = -0xFA0;
            break;
        case 1:
        case 2:
            this->unk_28E = -0x1770;
            break;
        default:
            break;
    }
    if ((this->unk_2CE == Message_GetState(&globalCtx->msgCtx)) && (func_80147624(globalCtx) != 0)) {
        if (this->unk_2CE == 0xF) {
            s32 i;
            s32 correctDigits;

            for (i = 0; i < ARRAY_COUNT(this->unk_2C4); i++) {
                if ((this->unk_2C4[i] == 0) && (globalCtx->msgCtx.unk12054[i] == gSaveContext.bomberCode[i])) {
                    this->unk_2C4[i] = 1;
                }
            }
            for (i = 0, correctDigits = 0; i < ARRAY_COUNT(this->unk_2C4); i++) {
                if (this->unk_2C4[i] != 0) {
                    correctDigits++;
                }
            }

            if (correctDigits >= 5) {
                this->unk_2C2 = 6;
                this->actor.textId = D_80C058A0[this->unk_2C2];
                func_80151938(globalCtx, this->actor.textId);
                Actor_PlaySfxAtPos(&this->actor, 0x4823);
                this->unk_2CE = 5;
                return;
            }
        }
        if (Text_GetFaceReaction(globalCtx, 0x15) != 0) {
            this->unk_28E = 0;
            func_801477B4(globalCtx);
            func_80C04B40(this);
        } else {
            s32 j;

            switch (this->unk_2C2) {
                case 0:
                case 1:
                case 5:
                case 7:
                    this->unk_28E = 0;
                    func_801477B4(globalCtx);
                    func_80C04B40(this);
                    break;
                case 2:
                    this->unk_2C2 = 3;
                    this->actor.textId = D_80C058A0[this->unk_2C2];
                    func_80151938(globalCtx, this->actor.textId);
                    this->unk_2CE = 0xF;
                    break;
                case 3:
                    for (j = 0 ; j < 5; j++){
                        this->unk_2C4[j] = 0;
                    }
                    this->unk_2C2 = 4;
                    Actor_PlaySfxAtPos(&this->actor, 0x4806);
                    this->actor.textId = D_80C058A0[this->unk_2C2];
                    func_80151938(globalCtx, this->actor.textId);
                    this->unk_2CE = 5;
                    break;
                case 4:
                    this->unk_2C2 = 5;
                    this->actor.textId = D_80C058A0[this->unk_2C2];
                    func_80151938(globalCtx, this->actor.textId);
                    this->unk_2CE = 5;
                    break;
                case 6:
                    globalCtx->msgCtx.unk11F10 = 0;
                    func_80C050B8(this, globalCtx);
                    break;
            }
        }
    }
}

void func_80C050B8(EnBombers2 *this, GlobalContext *globalCtx) {
    Player *player = GET_PLAYER(globalCtx);
    s16 homeYawToPlayer;
    
    func_80C04AAC(this, 2, 1.0f);
    this->unk_2A8 = 0;
    homeYawToPlayer = Math_Vec3f_Yaw(&this->actor.home.pos, &player->actor.world.pos);
    Math_Vec3f_Copy(&this->unk_29C, &this->actor.world.pos);
    if (this->actor.home.rot.y < homeYawToPlayer) {
        this->unk_29C.x += Math_SinS(this->actor.home.rot.y + 0xC100) * 50.0f;
        this->unk_29C.z += Math_CosS(this->actor.home.rot.y + 0xC100) * 50.0f;
    } else {
        this->unk_29C.x += Math_SinS(this->actor.home.rot.y + 0x3F00) * 50.0f;
        this->unk_29C.z += Math_CosS(this->actor.home.rot.y + 0x3F00) * 50.0f;
    }
    this->unk_2B6 = Math_Vec3f_Yaw(&this->actor.home.pos, &this->unk_29C);
    this->unk_2C0 = 2;
    this->actionFunc = func_80C0520C;
}

void func_80C0520C(EnBombers2 *this, GlobalContext *globalCtx) {
    if (this->unk_2A8 == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->cutscene);
            return;
        }
        if (ActorCutscene_GetCanPlayNext(this->cutscene) == 0) {
            ActorCutscene_SetIntentToPlay(this->cutscene);
            return;
        }
        ActorCutscene_StartAndSetUnkLinkFields(this->cutscene, &this->actor);
        this->unk_2A8 = 1;
        return;
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2B6, 1, 0xBB8, 0);
    if ((fabsf(this->unk_29C.x - this->actor.world.pos.x) < 3.0f) && (fabsf(this->unk_29C.z - this->actor.world.pos.z) < 3.0f)) {
        this->unk_2B6 = this->actor.yawTowardsPlayer;
        this->actor.speedXZ = 0.0f;
        if (fabsf(this->actor.world.rot.y - this->actor.yawTowardsPlayer) < 100.0f) {
            func_801477B4(globalCtx);
            this->unk_2CE = 5;
            this->unk_2C2 = 7;
            func_80C04AAC(this, 6, 1.0f);
            this->unk_2A8 = 0;
            this->unk_2C0 = 1;
            gSaveContext.weekEventReg[0x49] |= 0x80;
            ActorCutscene_Stop(this->cutscene);
            this->unk_2AC = 1;
            this->actor.textId =  D_80C058A0[this->unk_2C2];
            Message_StartTextbox(globalCtx,  this->actor.textId, &this->actor);
            this->actionFunc = func_80C04D8C;
        }
    } else {
        Math_ApproachF(&this->actor.world.pos.x, this->unk_29C.x, 0.3f, 1.0f);
        Math_ApproachF(&this->actor.world.pos.z, this->unk_29C.z, 0.3f, 1.0f);
    }
}

void EnBombers2_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnBombers2 *this = (EnBombers2 *) thisx;
    f32 temp_f4;
    Vec3f sp34;
    s32 phi_v1;

    SkelAnime_Update(&this->skelAnime);
    if (this->unk_2B2 != 0) {
        this->unk_2B2--;
    }
    if ((this->animIndex == 2) && (Animation_OnFrame(&this->skelAnime, 9.0f) || Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 18.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMBERS_WALK);
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->unk_2C0 != 2) {
        
        phi_v1 = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.world.rot.y));
        this->unk_290 = 0;
        if (phi_v1 < 0x3A98) {
            this->unk_290 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
            if (this->unk_290 >= 0x2711) {
                this->unk_290 = 0x2710;
            } else if (this->unk_290 < -0x2710) {
                this->unk_290 = -0x2710;
            }
        }
    }
    Actor_SetFocus(&this->actor, 20.0f);
    Actor_SetScale(&this->actor, 0.008f);
    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Math_SmoothStepToS(&this->unk_28A, this->unk_290, 1, 0xBB8, 0);
    Math_SmoothStepToS(&this->unk_288, this->unk_28E, 1, 0xBB8, 0);
    if (this->unk_2BE == 0) {
        this->unk_2BC += 1;
        if (this->unk_2BC >= 3) {
            this->unk_2BC = 0;
            this->unk_2BE = (s16)Rand_ZeroFloat(60.0f) + 0x14;
        }
    }
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    if (this->unk_2AC == 0) {
        this->actor.world.pos.x = (Math_SinS((this->actor.world.rot.y + 0x8000)) * 26.0f) + sp34.x;
        temp_f4 = Math_CosS(this->actor.world.rot.y + 0x8000) * 26.0f;
        this->actor.world.pos.z = temp_f4 + sp34.z;
        this->collider.dim.radius = 0x23;
        this->collider.dim.height = 0x1E;
    } else {
        this->collider.dim.radius = 0xA;
        this->collider.dim.height = 0x19;
    }
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    if (this->unk_2AC == 0) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1D);
    }
    Math_Vec3f_Copy(&this->actor.world.pos, &sp34);
}


s32 func_80C056D4(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnBombers2* this = THIS;

    if (limbIndex == 8) {
        rot->x += this->unk_296;
    }
    if (limbIndex == 17) {
        rot->x += this->unk_28A;
        rot->z += this->unk_288;
    }
    if ((limbIndex == 15) || (limbIndex == 19) || (limbIndex == 20)) {
        *dList = NULL;
    }
    return 0;
}


void EnBombers2_Draw(Actor *thisx, GlobalContext *globalCtx) {

    EnBombers2 *this = THIS;
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80C05914[this->unk_2BC]));
    gSPSegment(POLY_OPA_DISP++, 0x09,  Lib_SegmentedToVirtual(D_80C05920));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(D_80C05910));
    Scene_SetRenderModeXlu(globalCtx, 0, 1);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, func_80C056D4, NULL, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
