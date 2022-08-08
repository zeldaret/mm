/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Target Game (Honey & Darling)
 */

#include "z_en_tg.h"
#include "objects/object_mu/object_mu.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, PlayState* play);
void EnTg_Destroy(Actor* thisx, PlayState* play);
void EnTg_Update(Actor* thisx, PlayState* play);
void EnTg_Draw(Actor* thisx, PlayState* play);

void func_8098FA70(EnTg* this, PlayState* play);
void func_8098FEA8(PlayState* play, EnTgIdk* ptr, s32 len);
void func_8099000C(PlayState* play, EnTgIdk* ptr, s32 len);
void func_8098FD50(EnTg* this, EnTgIdk* ptr, Vec3f* arg2, s32 arg3);

const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static AnimationInfoS sAnimations = { &object_mu_Anim_0053E0, 1.0f, 0, -1, 0, 0 };
static Vec3f D_80990228 = { 0.0f, 0.0f, 0.0f };
static Vec3f D_80990234 = { 0.0f, 1.5f, 0.0f };
static Vec3f D_80990240 = { 0.0f, 0.0f, 0.0f };
static Vec3f D_8099024C = { 0.0f, 0.0f, 0.0f };

// EnTg_ChangeAnimation - func_8098F800
void EnTg_ChangeAnimation(SkelAnime* skelAnime, AnimationInfoS* animation, s16 unusedExtraOffset) {
    f32 endFrame;

    animation += unusedExtraOffset;

    if (animation->frameCount < 0) {
        endFrame = (f32)Animation_GetLastFrame(animation->animation);
    } else {
        endFrame = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, endFrame,
                     animation->mode, animation->morphFrames);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_UpdateCollider.s")
// EnTg_UpdateCollider - EnTg_UpdateCollider
void EnTg_UpdateCollider(EnTg* this, PlayState* play) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F928.s")
void func_8098F928(EnTg* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Init.s")
void EnTg_Init(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_mu_Skel_00B2B0, NULL, this->jointTable, this->morphTable, 21);
    EnTg_ChangeAnimation(&this->skelAnime, &sAnimations, 0);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_8098FA70;
    this->actor.gravity = -4.0f;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Destroy.s")
void EnTg_Destroy(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FA70.s")
void func_8098FA70(EnTg* this, PlayState* play) {
    Vec3f sp24;

    this->actor.shape.rot.y += sREG(0) + 0x258; // 0x258 = 600
    this->actor.world.rot = this->actor.shape.rot;

    if (DECR(this->unk2EC) == 0) {
        this->unk2EC = 0xC;
        sp24 = this->actor.world.pos;
        sp24.y += 62.0f;
        func_8098FD50(this, &this->unk2F0, &sp24, 0xA);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Update.s")
void EnTg_Update(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    this->actionFunc(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4U);
    func_8098F928(this, play);
    func_8098FEA8(play, &this->unk2F0, 0xA);
    EnTg_UpdateCollider(this, play);
}

// EnTg_OverrideLimbDraw
// func_8098FBB4
s32 func_8098FBB4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;
    return 0;
}

// EnTg_PostLimbDraw
// func_8098FBD0
void func_8098FBD0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;

    Vec3f sp18 = D_80990228; //{ 0.0f, 0.0f, 0.0f };

    if (limbIndex == 9) {
        Matrix_MultVec3f(&sp18, &this->actor.focus.pos);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Draw.s")
void EnTg_Draw(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    GraphicsContext* gfxCtx;

    Matrix_Push();
    func_8099000C(play, &this->unk2F0, 0xA);
    Matrix_Pop();

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 0, 0x32, 0xA0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 0xFF, 0xFF, 0xFF, 0));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32)this->skelAnime.dListCount,
                          func_8098FBB4, func_8098FBD0, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FD50.s")
void func_8098FD50(EnTg* this, EnTgIdk* ptr, Vec3f* arg2, s32 len) {
    Vec3f sp2C = D_80990234;
    Vec3f sp20 = D_80990240;
    s32 i = 0;

    while ((i < len) && (ptr->unk0 != 0)) {
        i++;
        ptr++;
    }

    if (i < len) {
        ptr->unk0 = 1;
        ptr->unk14 = *arg2;
        ptr->unk2C = sp2C;
        ptr->unk20 = sp20;
        ptr->unk4 = 0.01f;

        ptr->unk14.x += 4.0f * Math_SinS(this->actor.shape.rot.y);
        ptr->unk14.z += 4.0f * Math_CosS(this->actor.shape.rot.y);
        ptr->unk1 = 0x10;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FEA8.s")
// Looks just like func_809647EC in z_en_fu.c
void func_8098FEA8(PlayState* play, EnTgIdk* ptr, s32 len) {
    Vec3f sp44 = D_8099024C;
    s16 yaw = Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
    s32 i;

    for (i = 0; i < len; i++, ptr++) {
        if (ptr->unk0 == 1) {
            if (DECR(ptr->unk1) == 0) {
                ptr->unk0 = 0U;
            }
            ptr->unk14.y += ptr->unk2C.y;
            ptr->unk14.x += 2.0f * Math_SinS(ptr->unk38);
            ptr->unk14.z += 2.0f * Math_CosS(ptr->unk38);
            Matrix_Push();
            Matrix_Translate(ptr->unk14.x, ptr->unk14.y, ptr->unk14.z, MTXMODE_NEW);
            Matrix_RotateYS(yaw, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp44, &ptr->unk14);
            Matrix_Pop();
            ptr->unk38 += 6000;
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8099000C.s")
void func_8099000C(PlayState* play, EnTgIdk* ptr, s32 len) {
    s32 i;
    s32 flag = false;

    OPEN_DISPS(play->state.gfxCtx);

    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

    for (i = 0; i < len; i++, ptr++) {
        if (ptr->unk0 == 1) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, object_mu_DL_00B0A0);
                flag = true;
            }
            Matrix_Translate(ptr->unk14.x, ptr->unk14.y, ptr->unk14.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(ptr->unk4, ptr->unk4, ptr->unk4, MTXMODE_APPLY);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_05E6F0));
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_mu_DL_00B0E0);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
