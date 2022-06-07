/*
 * File: z_en_hata.c
 * Overlay: ovl_En_Hata
 * Description: Red Flag on Post
 */

#include "z_en_hata.h"
#include "objects/object_hata/object_hata.h"

#define FLAGS 0x00000000

#define THIS ((EnHata*)thisx)

void EnHata_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Update(Actor* thisx, GlobalContext* globalCtx2);
void EnHata_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_8089EC68(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);

const ActorInit En_Hata_InitVars = {
    ACTOR_EN_HATA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HATA,
    sizeof(EnHata),
    (ActorFunc)EnHata_Init,
    (ActorFunc)EnHata_Destroy,
    (ActorFunc)EnHata_Update,
    (ActorFunc)EnHata_Draw,
};

void EnHata_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 rand;
    EnHata* this = THIS;
    f32 endFrame;

    SkelAnime_Init(globalCtx, &this->skelAnime, &object_hata_Skel_002FD0, NULL, &this->jointTable, &this->morphTable,
                   21);
    endFrame = Animation_GetLastFrame(&object_hata_Anim_000444);
    Animation_Change(&this->skelAnime, &object_hata_Anim_000444, 1.0f, 0.0f, endFrame, 0, 0.0f);
    rand = Rand_ZeroFloat(endFrame);
    this->skelAnime.curFrame = rand;
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_hata_Colheader_0000C0);
    Actor_SetScale(&this->dyna.actor, 0.013f);
    this->dyna.actor.uncullZoneScale = 500.0f;
    this->dyna.actor.uncullZoneDownward = 500.0f;
    this->dyna.actor.uncullZoneForward = 2200.0f;
}

void EnHata_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHata* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void EnHata_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnHata* this = THIS;
    Vec3f sp34;
    f32 phi_fv0;
    f32 phi_fv0_3;

    phi_fv0 = CLAMP(globalCtx->envCtx.windSpeed / 120.0f, 0.0f, 1.0f);
    this->skelAnime.playSpeed = 2.75f * phi_fv0;
    this->skelAnime.playSpeed += 1.0f + Rand_ZeroFloat(1.25f);

    sp34.x = globalCtx->envCtx.windDir.x;
    sp34.y = (globalCtx->envCtx.windDir.y) + ((1.0f - phi_fv0) * 240.0f);
    sp34.y = CLAMP(sp34.y, -118.0f, 118.0f);
    sp34.z = globalCtx->envCtx.windDir.z;

    phi_fv0 = CLAMP(phi_fv0, 0.1f, 0.4f);
    Math_ApproachF(&this->unk2A4.x, sp34.x, phi_fv0, 1000.0f);
    Math_ApproachF(&this->unk2A4.y, sp34.y, phi_fv0, 1000.0f);
    Math_ApproachF(&this->unk2A4.z, sp34.z, phi_fv0, 1000.0f);

    sp34 = this->unk2A4;
    this->unk29C = Math_Vec3f_Pitch(&gZeroVec3f, &sp34);
    this->unk29C = -this->unk29C;
    this->unk2A0 = Math_Vec3f_Yaw(&gZeroVec3f, &sp34);
    this->unk2A0 += -0x4000;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_8089EC68(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHata* this = THIS;

    if ((limbIndex == 4) || (limbIndex == 13)) {
        rot->y += this->unk29C;
        rot->z += this->unk2A0;
    }
    return false;
}

void EnHata_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHata* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_8089EC68, NULL,
                      &this->dyna.actor);
}
