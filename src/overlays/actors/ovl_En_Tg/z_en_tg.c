/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Target Game (Honey & Darling)
 */

#include "z_en_tg.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8098FA70(EnTg* this, GlobalContext* globalCtx);
void func_8098FEA8(GlobalContext* globalCtx, EnTgIdk* ptr, s32 len);
void func_8099000C(GlobalContext* globalCtx, EnTgIdk* ptr, s32 len);

#if 0
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809901C0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_809901EC = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_809901F8 = {
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

#endif

// In data
extern ColliderCylinderInit D_809901C0;
extern CollisionCheckInfoInit2 D_809901EC;
extern DamageTable D_809901F8;

extern AnimationInfoS D_80990218;
extern Vec3f D_80990228; // = { 0.0f, 0.0f, 0.0f };
extern UNK_TYPE D_80990234; // from data
extern UNK_TYPE D_80990240; // from data
extern Vec3f D_8099024C; // = { 0.0f, 0.0f, 0.0f };

// Not in data?
extern void* D_0405E6F0;
extern FlexSkeletonHeader D_0600B2B0;
extern UNK_TYPE D_0600B0A0;
extern UNK_TYPE D_0600B0E0; //last

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F800.s")
void func_8098F800(SkelAnime* skelAnime, AnimationInfoS* animation, s16 idx) {
    f32 phi_f0;

    animation += idx;

    if (animation->frameCount < 0) {
        phi_f0 = (f32)Animation_GetLastFrame(animation->animation);
    } else {
        phi_f0 = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, phi_f0,
                     animation->mode, animation->morphFrames);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F8A8.s")
void func_8098F8A8(EnTg* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = (s16)this->actor.world.pos.x;
    this->collider.dim.pos.y = (s16)this->actor.world.pos.y;
    this->collider.dim.pos.z = (s16)this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F928.s")
void func_8098F928(EnTg* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Init.s")
void EnTg_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600B2B0, NULL, this->jointTable, this->morphTable, 21);
    func_8098F800(&this->skelAnime, &D_80990218, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_809901C0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_809901F8, &D_809901EC);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_8098FA70;
    this->actor.gravity = -4.0f;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Destroy.s")
void EnTg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FA70.s")
// void func_8098FA70(EnTg *this, GlobalContext *globalCtx) {
//     f32 sp28;
//     ? sp24;
//     s16 temp_v0;
//     s16 phi_v1;

//     temp_v0 = this->unk2EC;
//     this->actor.shape.rot.y = this->actor.shape.rot.y + gGameInfo->data[0x600] + 0x258;
//     this->unk30 = (unaligned s32) this->unkBC;
//     this->actor.world.rot.z = (s16) (u16) this->actor.shape.rot.z;
//     if (temp_v0 == 0) {
//         phi_v1 = 0;
//     } else {
//         this->unk2EC = (s16) (temp_v0 - 1);
//         phi_v1 = this->unk2EC;
//     }
//     if (phi_v1 == 0) {
//         this->unk2EC = 0xC;
//         sp24.unk0 = (f32) this->actor.world.pos.x;
//         sp24.unk4 = (f32) this->actor.world.pos.y;
//         sp24.unk8 = (f32) this->actor.world.pos.z;
//         sp28 += 62.0f;
//         func_8098FD50(&this->unk2F0, &sp24, 0xA);
//     }
// }
void func_8098FA70(EnTg *this, GlobalContext *globalCtx) {
    // f32 sp28;
    Vec3f sp24;
    // s16 temp_v0;
    s16 phi_v1;// = this->unk2EC;

    // temp_v0 = this->unk2EC;
    // this->actor.shape.rot.y = this->actor.shape.rot.y + gGameInfo->data[0x600] + 0x258;
    // this->actor.shape.rot.y += gGameInfo->data[0x600] + 0x258;
    this->actor.shape.rot.y += sREG(0) + 0x258; // 0x258 = 600
    // this->unk30 = (unaligned s32) this->unkBC;
    this->actor.world.rot.x = this->actor.shape.rot.x;
    // this->actor.world.rot.y = this->actor.shape.rot.y;
    // this->actor.world.rot.z = this->actor.shape.rot.z;

    if (this->unk2EC == 0) {
        phi_v1 = 0;
    } else {
        this->unk2EC -= 1;
        phi_v1 = this->unk2EC;
    }
    if (phi_v1 == 0) {
        this->unk2EC = 0xC; // 0xC = 12
        sp24.x = (f32) this->actor.world.pos.x;
        sp24.y = (f32) this->actor.world.pos.y;
        sp24.z = (f32) this->actor.world.pos.z;
        // sp28 += 62.0f;
        func_8098FD50(&this->unk2F0, &sp24, 0xA); // 0xA = 10
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Update.s")
void EnTg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTg* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4U);
    func_8098F928(this, globalCtx);
    func_8098FEA8(globalCtx, &this->unk2F0, 0xA);
    func_8098F8A8(this, globalCtx);
}

// s32 func_8098FBB4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBB4.s")
s32 func_8098FBB4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;
    return 0;
}

// void func_8098FBD0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBD0.s")
void func_8098FBD0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;

    Vec3f sp18 = D_80990228;

    if (limbIndex == 9) {
        Matrix_MultiplyVector3fByState(&sp18, &this->actor.focus.pos);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Draw.s")
void EnTg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTg* this = THIS;

    GraphicsContext* gfxCtx;

    Matrix_StatePush();
    func_8099000C(globalCtx, &this->unk2F0, 0xA);
    Matrix_StatePop();

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 0, 0x32, 0xA0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 0xFF, 0xFF, 0xFF, 0));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          (s32)this->skelAnime.dListCount, func_8098FBB4, func_8098FBD0, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FD50.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FEA8.s")
// Looks just like func_809647EC in z_en_fu.c
void func_8098FEA8(GlobalContext* globalCtx, EnTgIdk* ptr, s32 len) {
    Vec3f sp44 = D_8099024C; // or just { 0.0f, 0.0f, 0.0f };
    s16 yaw = Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx));
    s32 i;

    for (i = 0; i < len; i++, ptr++) {
        if (ptr->unk0 == 1) {
            if (DECR(ptr->unk1) == 0) {
                ptr->unk0 = 0U;
            }
            ptr->unk14.y += ptr->unk30;
            ptr->unk14.x += 2.0f * Math_SinS(ptr->unk38);
            ptr->unk14.z += 2.0f * Math_CosS(ptr->unk38);
            Matrix_StatePush();
            Matrix_InsertTranslation(ptr->unk14.x, ptr->unk14.y, ptr->unk14.z, MTXMODE_NEW);
            Matrix_RotateY(yaw, MTXMODE_APPLY);
            Matrix_MultiplyVector3fByState(&sp44, &ptr->unk14);
            Matrix_StatePop();
            ptr->unk38 += 6000;
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8099000C.s")
void func_8099000C(GlobalContext* globalCtx, EnTgIdk* ptr, s32 len) {
    s32 i;
    s32 flag = false;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

    for (i = 0; i < len; i++, ptr++) {
        if (ptr->unk0 == 1) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, &D_0600B0A0);
                flag = true;
            }
            Matrix_InsertTranslation(ptr->unk14.x, ptr->unk14.y, ptr->unk14.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(ptr->unk4, ptr->unk4, ptr->unk4, MTXMODE_APPLY);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(&D_0405E6F0));
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, &D_0600B0E0);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
