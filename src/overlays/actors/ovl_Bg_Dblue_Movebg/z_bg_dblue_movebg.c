/*
 * File: z_bg_dblue_movebg.c
 * Overlay: ovl_Bg_Dblue_Movebg
 * Description: Great Bay Temple - Waterwheels and push switches
 */

#include "z_bg_dblue_movebg.h"
#include "objects/object_dblue_object/object_dblue_object.h"
#include "overlays/actors/ovl_Obj_Hunsui/z_obj_hunsui.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgDblueMovebg*)thisx)

void BgDblueMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2A1E0(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2A32C(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2A444(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2A670(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2A688(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2A714(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2A7F8(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2AAB8(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2AED0(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2B1A0(BgDblueMovebg* this, GlobalContext* globalCtx);
void func_80A2B274(Actor* thisx, GlobalContext* globalCtx);
void func_80A2B308(Actor* thisx, GlobalContext* globalCtx);

BgDblueMovebg* D_80A2BBF0;

typedef struct {
    u8 unk_00;
    u8 unk_01;
} BgDblueMovebgUnkStruct;

BgDblueMovebgUnkStruct D_80A2BBF4;

u8 D_80A2B870[][2] = {
    { 0x01, 0x01 }, { 0x01, 0x00 }, { 0x02, 0x03 }, { 0x02, 0x01 }, { 0x02, 0x02 }, { 0x02, 0x00 }, { 0x03, 0x07 },
    { 0x03, 0x03 }, { 0x03, 0x05 }, { 0x03, 0x01 }, { 0x03, 0x06 }, { 0x03, 0x02 }, { 0x03, 0x04 }, { 0x03, 0x00 },
};

const ActorInit Bg_Dblue_Movebg_InitVars = {
    ACTOR_BG_DBLUE_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueMovebg),
    (ActorFunc)BgDblueMovebg_Init,
    (ActorFunc)BgDblueMovebg_Destroy,
    (ActorFunc)BgDblueMovebg_Update,
    (ActorFunc)BgDblueMovebg_Draw,
};

Gfx* D_80A2B8AC[] = {
    NULL,
    object_dblue_object_DL_0069D8,
    NULL,
    NULL,
    NULL,
    NULL,
    object_dblue_object_DL_004848,
    object_dblue_object_DL_0061B8,
    NULL,
    NULL,
    NULL,
    NULL,
};

Gfx* D_80A2B8DC[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, object_dblue_object_DL_00CAA0, NULL,
};

CollisionHeader* D_80A2B90C[] = {
    NULL,
    &object_dblue_object_Colheader_006EA8,
    NULL,
    NULL,
    NULL,
    &object_dblue_object_Colheader_00D3DC,
    &object_dblue_object_Colheader_005D28,
    &object_dblue_object_Colheader_00714C,
    &object_dblue_object_Colheader_00AED0,
    &object_dblue_object_Colheader_00AED0,
    NULL,
    NULL,
};

AnimatedMaterial* D_80A2B93C[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, object_dblue_object_Matanimheader_00CC18, NULL,
};

s16 D_80A2B96C[] = { 0, 0x16C, -0x16C, 0 };

s16 D_80A2B974[] = { -1, -1 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

Vec3f D_80A2B988 = { 1785.0f, 0.0f, 220.0f };

s32 func_80A29A80(GlobalContext* globalCtx, s32 arg1, s32 arg2) {
    s32 sp2C = 1;
    s32 val;
    s32 val2;

    if (arg2 < 14) {
        val = D_80A2B870[arg2][0];
        val2 = D_80A2B870[arg2][1];

        while (val--) {
            if ((1 << val) & val2) {
                if (!Flags_GetSwitch(globalCtx, arg1 + val)) {
                    sp2C = 0;
                    break;
                }
            } else if (Flags_GetSwitch(globalCtx, arg1 + val)) {
                sp2C = 0;
                break;
            }
        }
    } else {
        sp2C = 0;
        switch (arg2) {
            case 14:
                if (!Flags_GetSwitch(globalCtx, arg1)) {
                    sp2C = 1;
                }

                if (Flags_GetSwitch(globalCtx, arg1 + 1) && Flags_GetSwitch(globalCtx, arg1 + 2) &&
                    Flags_GetSwitch(globalCtx, arg1 + 3)) {
                    sp2C += 2;
                }
                break;

            case 15:
                if (!Flags_GetSwitch(globalCtx, arg1) ||
                    (Flags_GetSwitch(globalCtx, arg1 + 1) && Flags_GetSwitch(globalCtx, arg1 + 2) &&
                     Flags_GetSwitch(globalCtx, arg1 + 3))) {
                    sp2C = 1;
                }
                break;
        }
    }
    return sp2C;
}

void BgDblueMovebg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgDblueMovebg* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->unk_160 = BGDBLUEMOVEBG_GET_F(thisx);
    this->unk_1BC = BGDBLUEMOVEBG_GET_F000(thisx);
    this->unk_1C0 = BGDBLUEMOVEBG_GET_FF0(thisx);
    DynaPolyActor_Init(&this->dyna, 1);

    if ((this->unk_160 == 9) || (this->unk_160 == 8)) {
        if (D_80A2BBF4.unk_00 != 0) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }
        this->unk_170 = this->dyna.actor.room;
        this->dyna.actor.room = -1;
        D_80A2BBF4.unk_00 = 1;
        this->unk_171 = this->dyna.actor.world.rot.z;
        this->dyna.actor.world.rot.z = 0;
        this->dyna.actor.shape.rot.z = 0;
    } else if (this->unk_160 == 6) {
        if (D_80A2BBF4.unk_01 != 0) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }
        this->unk_171 = this->dyna.actor.world.rot.z;
        this->unk_170 = this->dyna.actor.room;
        this->dyna.actor.world.rot.z = 0;
        this->dyna.actor.shape.rot.z = 0;
        this->dyna.actor.room = -1;
        D_80A2BBF4.unk_01 = 1;
    }

    if (D_80A2B90C[this->unk_160] != NULL) {
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, D_80A2B90C[this->unk_160]);
    }

    this->unk_164 = D_80A2B8AC[this->unk_160];
    this->unk_168 = D_80A2B8DC[this->unk_160];
    this->unk_16C = D_80A2B93C[this->unk_160];

    SubS_FillCutscenesList(&this->dyna.actor, this->unk_1B6, ARRAY_COUNT(this->unk_1B6));

    switch (this->unk_160) {
        case 1:
            this->unk_1C4 = this->dyna.actor.world.rot.x;
            this->unk_1C8 = this->dyna.actor.world.rot.z;
            this->dyna.actor.world.rot.x = 0;
            this->dyna.actor.shape.rot.x = 0;
            this->dyna.actor.world.rot.z = 0;
            this->dyna.actor.shape.rot.z = 0;
            if (func_80A29A80(globalCtx, this->unk_1C8, this->unk_1C4)) {
                this->unk_172 |= 1;
            } else {
                this->unk_172 &= ~1;
            }
            this->unk_17E = 0;
            this->unk_184 = 0.0f;
            if (Flags_GetSwitch(globalCtx, this->unk_1C0)) {
                this->unk_18C = 0x384;
            } else {
                this->unk_18C = 0;
            }
            this->dyna.actor.shape.rot.y += (s16)((this->unk_18C / 10.0f) * (0x10000 / 360.0f));
            this->actionFunc = func_80A2A714;
            break;

        case 6:
            this->unk_178 = func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC);
            this->unk_1CC = D_80A2B96C[this->unk_178];
            this->unk_1CE = this->unk_1CC;
            this->actionFunc = func_80A2A1E0;
            break;

        case 7:
            this->unk_1C4 = this->dyna.actor.world.rot.x;
            this->unk_1C8 = this->dyna.actor.world.rot.z;
            this->dyna.actor.world.rot.x = 0;
            this->dyna.actor.shape.rot.x = 0;
            this->dyna.actor.world.rot.z = 0;
            this->dyna.actor.shape.rot.z = 0;
            if (Flags_GetSwitch(globalCtx, this->unk_1C0)) {
                Actor_MarkForDeath(&this->dyna.actor);
                break;
            }
            this->unk_18C = 0;
            this->dyna.actor.draw = func_80A2B308;
            this->unk_17E = 0;
            this->unk_184 = 0.0f;
            this->dyna.actor.shape.rot.y += (s16)((this->unk_18C / 10.0f) * (0x10000 / 360.0f));
            this->actionFunc = func_80A2A32C;
            break;

        case 8:
        case 9:
            this->unk_2F8[1] = NULL;
            this->unk_2F8[0] = NULL;
        label:
            for (i = 0; i < ARRAY_COUNT(D_80A2B974); i++) {
                D_80A2B974[i] = this->unk_1B6[i];
            }
            this->unk_178 = func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC);
            this->unk_1CC = D_80A2B96C[this->unk_178];
            this->unk_1CE = this->unk_1CC;
            Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
            Matrix_GetStateTranslationAndScaledX(2240.0f, &this->unk_190);
            Matrix_GetStateTranslationAndScaledX(-10.0f, &this->unk_19C);
            Math_Vec3f_Sum(&this->unk_190, &this->dyna.actor.world.pos, &this->unk_190);
            Math_Vec3f_Sum(&this->unk_19C, &this->dyna.actor.world.pos, &this->unk_19C);
            D_80A2BBF0 = this;
            this->dyna.actor.flags |= ACTOR_FLAG_20;
            this->actionFunc = func_80A2AED0;
            break;

        case 10:
            this->actionFunc = func_80A2B1A0;
            break;

        case 11:
            this->unk_1CC = D_80A2B96C[func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC)];
            D_80A2BBF0 = this;
            this->dyna.actor.flags |= ACTOR_FLAG_20;
            this->dyna.actor.update = Actor_Noop;
            this->dyna.actor.draw = func_80A2B274;
            break;
    }
}

void BgDblueMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgDblueMovebg* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    if ((this->unk_160 == 9) || (this->unk_160 == 8)) {
        Audio_StopSfxByPos(&this->unk_1A8);
    }
}

void func_80A2A128(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Actor* phi_s0 = NULL;

    while (true) {
        phi_s0 = SubS_FindActor(globalCtx, phi_s0, ACTORCAT_BG, ACTOR_OBJ_HUNSUI);
        if (phi_s0 != NULL) {
            if ((OBJHUNSUI_GET_F000(phi_s0) == 5) && (phi_s0->update != NULL)) {
                this->unk_2F8[1] = phi_s0;
            } else if ((OBJHUNSUI_GET_F000(phi_s0) == 6) && (phi_s0->update != NULL)) {
                this->unk_2F8[0] = phi_s0;
            }
            phi_s0 = phi_s0->next;
        }

        if (phi_s0 == NULL) {
            break;
        }
    }
}

void func_80A2A1E0(BgDblueMovebg* this, GlobalContext* globalCtx) {
    s32 temp_v0 = func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC);

    if (temp_v0 != this->unk_178) {
        switch (temp_v0) {
            case 1:
            case 2:
                this->unk_17E = 40;
                break;

            case 0:
            case 3:
                this->unk_17E = 15;
                break;
        }
    }
    this->unk_178 = temp_v0;

    if (this->unk_17E <= 0) {
        this->unk_1CE = D_80A2B96C[temp_v0];
    } else {
        this->unk_17E--;
    }

    Math_StepToS(&this->unk_1CC, this->unk_1CE, 12);
    this->dyna.actor.shape.rot.y += this->unk_1CC;

    if (globalCtx->roomCtx.currRoom.num == 0) {
        this->unk_164 = object_dblue_object_DL_004848;
    } else if (globalCtx->roomCtx.currRoom.num == 8) {
        this->unk_164 = NULL;
    }

    if (globalCtx->roomCtx.currRoom.num != this->unk_170) {
        if (globalCtx->roomCtx.currRoom.num != this->unk_171) {
            if ((globalCtx->roomCtx.prevRoom.num != this->unk_170) &&
                (globalCtx->roomCtx.prevRoom.num != this->unk_171)) {
                D_80A2BBF4.unk_01 = 0;
                Actor_MarkForDeath(&this->dyna.actor);
            }
        }
    }
}

void func_80A2A32C(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 phi_v0;
    f32 phi_f0;
    s32 phi_v1;

    if (this->dyna.pushForce != 0.0f) {
        this->unk_18E = BINANG_SUB(this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer);
        this->unk_184 = this->dyna.actor.xzDistToPlayer;

        if (this->dyna.pushForce >= 0.0f) {
            phi_f0 = 1.0f;
        } else {
            phi_f0 = -1.0f;
        }

        if (BINANG_SUB(this->dyna.actor.yawTowardsPlayer, player->actor.shape.rot.y) > 0) {
            phi_v0 = -1;
        } else {
            phi_v0 = 1;
        }
        this->unk_17E = phi_v0 * phi_f0;

        phi_v1 = false;
        if (this->unk_17E > 0) {
            phi_v1 = true;
        }

        if (phi_v1) {
            this->unk_180 = func_800F2178(this->unk_1B6[0]);
            this->unk_1D2 = this->unk_1B6[0];
            this->unk_172 |= 8;
            this->actionFunc = func_80A2A444;
        } else {
            player->stateFlags2 &= ~0x10;
            this->dyna.pushForce = 0.0f;
        }
    }
}

void func_80A2A444(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp20;
    Player* temp_a3;
    s16 temp_v0;

    this->unk_188++;
    this->unk_188 = CLAMP_MAX(this->unk_188, 5);

    sp20 = Math_StepToS(&this->unk_18A, 900, this->unk_188);
    temp_v0 = this->unk_18A * this->unk_17E;
    this->dyna.actor.shape.rot.y =
        (s32)((this->unk_18C + temp_v0) * 0.1f * (0x10000 / 360.0f)) + this->dyna.actor.home.rot.y;

    if ((player->stateFlags2 & 0x10) && (this->unk_184 > 0.0f)) {
        player->actor.world.pos.x =
            (Math_SinS(this->dyna.actor.shape.rot.y - this->unk_18E) * this->unk_184) + this->dyna.actor.home.pos.x;
        player->actor.world.pos.z =
            (Math_CosS(this->dyna.actor.shape.rot.y - this->unk_18E) * this->unk_184) + this->dyna.actor.home.pos.z;
    } else {
        this->unk_184 = 0.0f;
    }

    if (sp20) {
        player->stateFlags2 &= ~0x10;
        this->dyna.pushForce = 0.0f;
        Flags_SetSwitch(globalCtx, this->unk_1C0);
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_STONEDOOR_STOP);

        if (func_80A29A80(globalCtx, this->unk_1C8, this->unk_1C4)) {
            this->unk_172 |= 1;
        } else {
            this->unk_172 &= ~1;
        }

        if (!(this->unk_174 & 1) && (this->unk_172 & 1)) {
            func_801000CC(NA_SE_EV_PIPE_STREAM_START);
        }
        func_80A2A670(this, globalCtx);
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_COCK_SWITCH_ROLL - SFX_FLAG);
    }
}

void func_80A2A670(BgDblueMovebg* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80A2A688;
}

void func_80A2A688(BgDblueMovebg* this, GlobalContext* globalCtx) {
    this->unk_180--;
    if (this->unk_180 <= 0) {
        ActorCutscene_Stop(this->unk_1B6[0]);
    }

    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y - 60.0f, 2.0f) &&
        (this->unk_180 <= 0)) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void func_80A2A714(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 phi_v0;
    f32 phi_f0;

    if (this->dyna.pushForce != 0.0f) {
        this->unk_18E = BINANG_SUB(this->dyna.actor.shape.rot.y, this->dyna.actor.yawTowardsPlayer);
        this->unk_184 = this->dyna.actor.xzDistToPlayer;
        if (this->dyna.pushForce >= 0.0f) {
            phi_f0 = 1.0f;
        } else {
            phi_f0 = -1.0f;
        }

        if (BINANG_SUB(this->dyna.actor.yawTowardsPlayer, player->actor.shape.rot.y) > 0) {
            phi_v0 = -1;
        } else {
            phi_v0 = 1;
        }
        this->unk_17E = phi_v0 * phi_f0;

        this->unk_180 = func_800F2178(this->unk_1B6[0]);
        this->unk_1D2 = this->unk_1B6[0];
        this->unk_172 |= 8;
        this->actionFunc = func_80A2A7F8;
    }
}

void func_80A2A7F8(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp28;
    s16 sp26;
    s32 temp;

    this->unk_188++;
    this->unk_188 = CLAMP_MAX(this->unk_188, 5);

    sp28 = Math_StepToS(&this->unk_18A, 900, this->unk_188);
    sp26 = this->unk_18A * this->unk_17E;
    this->dyna.actor.shape.rot.y =
        (s32)((this->unk_18C + sp26) * 0.1f * (0x10000 / 360.0f)) + this->dyna.actor.home.rot.y;

    if ((player->stateFlags2 & 0x10) && (this->unk_184 > 0.0f)) {
        player->actor.world.pos.x =
            (Math_SinS(this->dyna.actor.shape.rot.y - this->unk_18E) * this->unk_184) + this->dyna.actor.home.pos.x;
        player->actor.world.pos.z =
            (Math_CosS(this->dyna.actor.shape.rot.y - this->unk_18E) * this->unk_184) + this->dyna.actor.home.pos.z;
    } else {
        this->unk_184 = 0.0f;
    }

    if (sp28) {
        temp = (this->unk_18C + sp26 + 3600) % 3600;

        if ((temp == 900) || (temp == 2700)) {
            Flags_SetSwitch(globalCtx, this->unk_1C0);
        } else {
            Flags_UnsetSwitch(globalCtx, this->unk_1C0);
        }

        player->stateFlags1 |= 0x20;
        player->stateFlags2 &= ~0x10;
        this->dyna.pushForce = 0.0f;

        this->unk_18C = (this->unk_18C + sp26 + 3600) % 3600;
        this->unk_188 = 0;
        this->unk_18A = 0;
        this->unk_17E = 0;

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_STONEDOOR_STOP);

        if (func_80A29A80(globalCtx, this->unk_1C8, this->unk_1C4)) {
            this->unk_172 |= 1;
        } else {
            this->unk_172 &= ~1;
        }

        if (!(this->unk_174 & 1) && (this->unk_172 & 1)) {
            func_801000CC(NA_SE_EV_PIPE_STREAM_START);
        }

        this->unk_174 = this->unk_172;
        this->unk_1D0 = 17;
        this->actionFunc = func_80A2AAB8;
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_COCK_SWITCH_ROLL - SFX_FLAG);
    }
}

void func_80A2AAB8(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp18;

    if (this->unk_180-- <= 0) {
        ActorCutscene_Stop(this->unk_1B6[0]);
    }

    sp18 = false;
    if ((this->unk_1D0 > 0) && ((D_80A2B974[0] >= 0) || (D_80A2B974[1] >= 0))) {
        if (ActorCutscene_GetCurrentIndex() != -1) {
            sp18 = true;
        }
    }

    if (!sp18 && (this->unk_180 <= 0)) {
        this->unk_1D0--;

        if (this->unk_1D0 == 1) {
            this->dyna.pushForce = 0.0f;
            player->stateFlags1 |= 0x20;
            player->stateFlags2 &= ~0x10;
        }

        if (this->unk_1D0 <= 0) {
            player->stateFlags1 &= ~0x20;
            this->actionFunc = func_80A2A714;
        }
    }
}

void func_80A2ABD0(BgDblueMovebg* this, GlobalContext* globalCtx) {
    Vec3f spAC;
    f32 temp_f0;
    f32 temp_f20;
    s32 phi_v0;
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(this->unk_2F8); i++) {
        if (this->unk_2F8[i] == NULL) {
            func_80A2A128(this, globalCtx);
            continue;
        }

        for (j = 0; j < ARRAY_COUNT(this->unk_1D8[0]); j++) {
            Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
            Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x + (j * 0x2000), MTXMODE_APPLY);
            Matrix_InsertZRotation_s(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
            Matrix_MultiplyVector3fByState(&D_80A2B988, &spAC);
            Math_Vec3f_Sum(&this->dyna.actor.world.pos, &spAC, &spAC);
            Math_Vec3f_Copy(&this->unk_238[i][j], &spAC);
            temp_f20 = spAC.y - this->unk_2F8[i]->world.pos.y;
            temp_f0 = Math_Vec3f_DistXZ(&this->unk_2F8[i]->world.pos, &spAC);

            if ((this->unk_300[i][j] != 0) && (temp_f20 <= 12.0f) && (temp_f20 >= 0.0f) && (temp_f0 <= 60.0f)) {
                phi_v0 = 1;
            } else {
                phi_v0 = 1;
                phi_v0 = (s64)phi_v0;
                if (((temp_f20 >= 0.0f) && ((temp_f20 > 0.0f) || (temp_f0 > 60.f))) ||
                    ((temp_f20 < 0.0f) && ((temp_f20 < -150.0f) || (temp_f0 > 40.0f)))) {
                    phi_v0 = 0;
                }
            }

            if (phi_v0) {
                this->unk_300[i][j] = i + 1;
                Math_StepToF(&this->unk_1F8[i][j], 1.0f, 0.2f);
                Math_StepToS(&this->unk_1D8[i][j], 255, 20);
            } else {
                this->unk_300[i][j] = 0;
                Math_StepToF(&this->unk_1F8[i][j], 0.0f, 0.01f);
                Math_StepToS(&this->unk_1D8[i][j], 0, 20);
            }
        }
    }
}

void func_80A2AED0(BgDblueMovebg* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 temp_v0_3;

    if (globalCtx->roomCtx.currRoom.num != this->unk_170) {
        if (globalCtx->roomCtx.currRoom.num != this->unk_171) {
            if ((globalCtx->roomCtx.prevRoom.num != this->unk_170) &&
                (globalCtx->roomCtx.prevRoom.num != this->unk_171)) {
                D_80A2BBF4.unk_00 = 0;
                Actor_MarkForDeath(&this->dyna.actor);
                return;
            }
        }
    }

    temp_v0_3 = func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC);
    if (temp_v0_3 != this->unk_178) {
        switch (temp_v0_3) {
            case 1:
            case 2:
                this->unk_1D2 = this->unk_1B6[0];
                this->unk_17E = 40;
                break;

            case 0:
            case 3:
                this->unk_1D2 = this->unk_1B6[1];
                this->unk_17E = 15;
                break;
        }
        this->unk_172 |= 8;
    }
    this->unk_178 = temp_v0_3;

    if (!(this->unk_172 & 8)) {
        if (this->unk_17E <= 0) {
            this->unk_1CE = D_80A2B96C[temp_v0_3];
        } else {
            this->unk_17E--;
        }
    }

    Math_StepToS(&this->unk_1CC, this->unk_1CE, 12);
    this->dyna.actor.shape.rot.x += this->unk_1CC;

    if (this->unk_160 == 8) {
        if (globalCtx->roomCtx.currRoom.num == 8) {
            func_80A2ABD0(this, globalCtx);
            this->unk_172 |= 0x20;
        } else {
            this->unk_172 &= ~0x20;
        }
    }

    if (globalCtx->roomCtx.currRoom.num == 0) {
        this->unk_164 = object_dblue_object_DL_008778;
    } else if (globalCtx->roomCtx.currRoom.num == 8) {
        this->unk_164 = object_dblue_object_DL_00A528;
    }

    if (this == D_80A2BBF0) {
        Vec3f sp54;
        f32 sp50;

        if (Math3D_PointDistToLine2D(globalCtx->view.eye.x, globalCtx->view.eye.z, this->unk_190.x, this->unk_190.z,
                                     this->unk_19C.x, this->unk_19C.z, &sp54.x, &sp54.z, &sp50)) {
            sp54.y = this->dyna.actor.world.pos.y;
        } else {
            if (Math_Vec3f_DistXYZ(&globalCtx->view.eye, &this->unk_190) <=
                Math_Vec3f_DistXYZ(&globalCtx->view.eye, &this->unk_19C)) {
                Math_Vec3f_Copy(&sp54, &this->unk_190);
            } else {
                Math_Vec3f_Copy(&sp54, &this->unk_19C);
            }
        }

        SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &sp54, &this->unk_1A8);
        this->unk_1D4 = ABS(this->unk_1CC) / 364.0f;
    }
}

void func_80A2B1A0(BgDblueMovebg* this, GlobalContext* globalCtx) {
    switch (func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC)) {
        case 1:
            this->dyna.actor.shape.rot.z = this->dyna.actor.home.rot.z;
            break;

        case 2:
            this->dyna.actor.shape.rot.z = BINANG_ROT180(this->dyna.actor.home.rot.z);
            break;
    }
}

void BgDblueMovebg_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgDblueMovebg* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->unk_172 & 8) {
        if (SubS_StartActorCutscene(&this->dyna.actor, this->unk_1D2, -1, SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
            this->unk_172 &= ~8;
        }
    }
}

void func_80A2B274(Actor* thisx, GlobalContext* globalCtx) {
    BgDblueMovebg* this = THIS;
    s16 temp_v1;

    if (this != D_80A2BBF0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    temp_v1 = D_80A2B96C[func_80A29A80(globalCtx, this->unk_1C0, this->unk_1BC)];
    if (temp_v1 != 0) {
        if (temp_v1 > 0) {
            func_8019FC20(&this->dyna.actor.projectedPos, NA_SE_EV_DUMMY_WATER_WHEEL_RR - SFX_FLAG);
        } else {
            func_8019FC20(&this->dyna.actor.projectedPos, NA_SE_EV_DUMMY_WATER_WHEEL_LR - SFX_FLAG);
        }
    }
}

void func_80A2B308(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgDblueMovebg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->unk_164);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void BgDblueMovebg_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgDblueMovebg* this = THIS;
    s32 i;
    s32 j;
    Gfx* gfx;
    Gfx* gfx2;

    Matrix_StatePush();

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((this->unk_160 == 9) || (this->unk_160 == 8) || (this->dyna.actor.flags & ACTOR_FLAG_40)) {
        if (this->unk_16C != NULL) {
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(this->unk_16C));
        }

        if ((this->unk_164 != 0) || (this->unk_160 == 6)) {
            gfx2 = Gfx_CallSetupDL(POLY_OPA_DISP, 0x19);

            gSPMatrix(&gfx2[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            if (this->unk_160 == 6) {
                gSPDisplayList(&gfx2[1], object_dblue_object_DL_0052B8);
                if (this->unk_164 != 0) {
                    gSPDisplayList(&gfx2[2], this->unk_164);
                    POLY_OPA_DISP = &gfx2[3];
                } else {
                    POLY_OPA_DISP = &gfx2[2];
                }
            } else {
                gSPDisplayList(&gfx2[1], this->unk_164);
                POLY_OPA_DISP = &gfx2[2];
            }
        }

        if (this->unk_168 != NULL) {
            gfx = func_8012C2B4(POLY_XLU_DISP);

            gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(&gfx[1], this->unk_168);

            POLY_XLU_DISP = &gfx[2];
        }
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if ((this->unk_160 == 8) && (this->unk_172 & 0x20)) {
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_dblue_object_Matanimheader_00CE00));

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                 this->dyna.actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
        gfx = func_8012C2B4(POLY_XLU_DISP);

        for (i = 0; i < ARRAY_COUNT(this->unk_1D8[0]); i++) {
            for (j = 0; j < ARRAY_COUNT(this->unk_1D8); j++) {
                if (this->unk_1D8[j][i] > 0) {
                    if (this->unk_1F8[j][i] > 0.1f) {
                        gSPSegment(
                            gfx++, 0x09,
                            Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0,
                                             (s32)(((globalCtx->gameplayFrames % 128) * -9.0f) / this->unk_1F8[j][i]),
                                             0x20, 0x20, 1, 0, 0, 0x20, 0x20));
                    }
                    Matrix_StatePush();
                    Matrix_InsertXRotation_s(i * 0x2000, MTXMODE_APPLY);
                    Matrix_InsertTranslation(1785.0f, 0.0f, 270.0f, MTXMODE_APPLY);
                    if (j != 0) {
                        Matrix_InsertZRotation_s(-0x8000, MTXMODE_APPLY);
                    }
                    Matrix_Scale(this->unk_1F8[j][i] * this->dyna.actor.scale.x,
                                 this->unk_1F8[j][i] * this->dyna.actor.scale.y,
                                 this->unk_1F8[j][i] * this->dyna.actor.scale.z, MTXMODE_APPLY);

                    gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gDPSetEnvColor(gfx++, 255, 255, 255, this->unk_1D8[j][i]);
                    gSPDisplayList(gfx++, object_dblue_object_DL_00CD10);

                    Matrix_StatePop();
                }
            }
        }
        POLY_XLU_DISP = gfx;

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if ((this->unk_160 == 9) || (this->unk_160 == 8)) {
        if (this->unk_1CC >= 0) {
            func_8019FB0C(&this->unk_1A8, NA_SE_EV_BIG_WATER_WHEEL_RR - SFX_FLAG, this->unk_1D4, 32);
        } else {
            func_8019FB0C(&this->unk_1A8, NA_SE_EV_BIG_WATER_WHEEL_LR - SFX_FLAG, this->unk_1D4, 32);
        }
    }
}
