/*
 * File: z_obj_wind.c
 * Overlay: ovl_Obj_Wind
 * Description: Updraft Current (STT) and Water Current (PFInterior)
 */

#include "z_obj_wind.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "z64math.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjWind*)thisx)

void ObjWind_Init(Actor* thisx, PlayState* play);
void ObjWind_Destroy(Actor* thisx, PlayState* play);
void ObjWind_Update(Actor* thisx, PlayState* play);
void ObjWind_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Wind_InitVars = {
    ACTOR_OBJ_WIND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjWind),
    (ActorFunc)ObjWind_Init,
    (ActorFunc)ObjWind_Destroy,
    (ActorFunc)ObjWind_Update,
    (ActorFunc)ObjWind_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 4000, ICHAIN_STOP),
};

void ObjWind_Init(Actor* thisx, PlayState* play) {
    ObjWind* this = (ObjWind*)thisx;
    s32 pad;
    WaterBox* waterbox;
    f32 ySurface;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &ySurface,
                             &waterbox) &&
        (this->actor.world.pos.y < ySurface)) {
        this->underWater = 1;
    }
}

void ObjWind_Destroy(Actor* thisx, PlayState* play) {
}

typedef struct sD_80B2448C {
    s16 unk_0;
    s16 unk_2;
    s16 unk_4;
    s16 unk_6;
    s16 unk_8;
} sD_80B2448C;

static sD_80B2448C D_80B2448C[] = {
    { 0x0212, 0x005A, 0x0BB8, 0x07D0, 0x0000 }, { 0x0460, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x026C, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0654, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 }, { 0x0190, 0x0064, 0x07D0, 0x03E8, 0x0000 },
    { 0x0258, 0x0078, 0x0BB8, 0x07D0, 0x0000 }, { 0x01F4, 0x0050, 0x0BB8, 0x07D0, 0x0000 },
    { 0x0190, 0x003C, 0x07D0, 0x07D0, 0x0000 }, { 0x01D6, 0x0046, 0x07D0, 0x03E8, 0x0000 },
};

static s32 D_80B245CC = 0xFFFFFFFF;

#ifdef NON_MATCHING
void ObjWind_Update(Actor* thisx, PlayState* play) {
    ObjWind* this = (ObjWind*)thisx;
    Player* player;
    f32 cosX;
    f32 sinYTimesX;
    Vec3f posCopy;
    Vec3f sp60;
    Vec3f sp54;
    f32 sinX;
    f32 sp40;
    f32 temp_fa0;
    f32 temp_fa1_2;
    f32 temp_ft0;
    f32 cosYTimesX;
    f32 temp_ft4;
    f32 temp_ft4_2;
    f32 temp_fv0;
    f32 dist;
    f32 var_fa0;
    sD_80B2448C* entry;

    entry = &D_80B2448C[(this->actor.params >> 7) & 0x1F];
    if (D_80B245CC != DREG(85)) {
        if ((DREG(85) >= 0) && (DREG(85) < 0x20)) {
            gRegEditor->data[0x2F0] = D_80B2448C[DREG(85)].unk_0;
            gRegEditor->data[0x2F1] = D_80B2448C[DREG(85)].unk_2;
            gRegEditor->data[0x2F2] = D_80B2448C[DREG(85)].unk_4;
            gRegEditor->data[0x2F3] = D_80B2448C[DREG(85)].unk_6;
            gRegEditor->data[0x2F4] = D_80B2448C[DREG(85)].unk_8;
            D_80B245CC = DREG(85);
        }
    } else {
        D_80B2448C[DREG(85)].unk_0 = gRegEditor->data[0x2F0];
        D_80B2448C[DREG(85)].unk_2 = gRegEditor->data[0x2F1];
        D_80B2448C[DREG(85)].unk_4 = gRegEditor->data[0x2F2];
        D_80B2448C[DREG(85)].unk_6 = gRegEditor->data[0x2F3];
        D_80B2448C[DREG(85)].unk_8 = gRegEditor->data[0x2F4];
    }
    if (((this->actor.params & 0x7F) == 0x7F) || !Flags_GetSwitch(play, this->actor.params & 0x7F)) {
        player = GET_PLAYER(play);
        Math_Vec3f_Copy(&posCopy, &this->actor.world.pos);
        cosX = Math_CosS(this->actor.shape.rot.x);
        sinX = Math_SinS(this->actor.shape.rot.x);
        sinYTimesX = Math_SinS(this->actor.shape.rot.y) * sinX;
        cosYTimesX = Math_CosS(this->actor.shape.rot.y) * sinX;
        temp_fv0 = func_80179A44(&posCopy, &player->actor.world, &sp60);
        if ((temp_fv0 >= 0.0f) && (temp_fv0 < entry->unk_0)) {
            dist = Math_Vec3f_DistXYZAndStoreDiff(&player->actor.world.pos, &sp60, &sp54);
            if (dist < entry->unk_2) {
                const float one = 1.0f;
                var_fa0 = 1.0f - temp_fv0 / entry->unk_0;
                sp40 = ((f32)entry->unk_4 / 100.0f) *
                       ((var_fa0 * (1.0f - dist / entry->unk_2)) + ((f32)entry->unk_8 / 100.0f));
                if (0.8f < temp_fv0 / entry->unk_0) {
                    var_fa0 = one - 1.0f;
                }
                temp_ft0 = ((f32)entry->unk_6 / 100.0f) * (dist / entry->unk_2 * var_fa0);
                if (dist != 0.0f) {
                    dist = 1.0f / dist;
                }
                temp_ft0 *= dist;
                temp_fa1_2 = (sinYTimesX * sp40) + (sp54.x * temp_ft0);
                temp_ft4_2 = (cosX * sp40) + (sp54.y * temp_ft0);
                temp_fa0 = (cosYTimesX * sp40) + (sp54.z * temp_ft0);
                player->windSpeed = sqrtf(SQ(temp_fa1_2) + SQ(temp_ft4_2) + SQ(temp_fa0));
                player->windAngleY = Math_Atan2S_XY(temp_fa0, temp_fa1_2);
                player->windAngleX = Math_Atan2S_XY(sqrtf(SQ(temp_fa1_2) + SQ(temp_fa0)), temp_ft4_2);
            }
        }
    }
    this->actor.scale.x = (f32)entry->unk_2 / 50.0f;
    this->actor.scale.z = (f32)entry->unk_2 / 50.0f;
    this->actor.scale.y = (f32)entry->unk_0 / 400.0f;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Update.s")
#endif

void ObjWind_Draw(Actor* thisx, PlayState* play) {
    ObjWind* this = (ObjWind*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&gameplay_keep_Matanimheader_07F218));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07E8C0);

    CLOSE_DISPS(play->state.gfxCtx);
}
