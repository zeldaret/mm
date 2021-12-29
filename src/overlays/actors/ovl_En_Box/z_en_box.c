/*
 * File: z_en_box.c
 * Overlay: ovl_En_Box
 * Description: Chest
 */

#include "z_en_box.h"

#define FLAGS 0x00000000

#define THIS ((EnBox*)thisx)

void EnBox_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBox_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80868944(EnBox* this, GlobalContext* globalCtx);
void func_808689E8(EnBox* this, GlobalContext* globalCtx);
void func_80868A6C(EnBox* this, GlobalContext* globalCtx);
void func_80868AFC(EnBox* this, GlobalContext* globalCtx);
void func_80868B74(EnBox* this, GlobalContext* globalCtx);
void func_80868CC8(EnBox* this, GlobalContext* globalCtx);
void func_80869020(EnBox* this, GlobalContext* globalCtx);

void func_80867FBC(func_80867BDC_a0* arg0, GlobalContext* globalCtx, s32 arg2);
void func_80867FE4(func_80867BDC_a0* arg0, GlobalContext* globalCtx);

extern T_80869B54 D_80869B54;
extern AnimationHeader* D_80869B68[5];

#if 0
const ActorInit En_Box_InitVars = {
    ACTOR_EN_BOX,
    ACTORCAT_CHEST,
    FLAGS,
    OBJECT_BOX,
    sizeof(EnBox),
    (ActorFunc)EnBox_Init,
    (ActorFunc)EnBox_Destroy,
    (ActorFunc)EnBox_Update,
    (ActorFunc)EnBox_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80869B50[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80869B50[];

extern AnimationHeader D_0600043C;
extern SkeletonHeader D_060066A0;
extern CollisionHeader D_060080E8;
extern Gfx D_060006F0;
extern Gfx D_06000A50;
extern Gfx D_06000DB0;
extern Gfx D_060012E8;
extern Gfx D_06001850;
extern Gfx D_06001D58;

void func_80867BD0(EnBox* this, EnBoxActionFunc func) {
    this->actionFunc = func;
}

void func_80867BDC(func_80867BDC_a0* arg0, GlobalContext* globalCtx, Vec3f* pos) {
    arg0->pos = *pos;
    arg0->unk_0C = NULL;
    arg0->unk_10 = NULL;
    arg0->unk_14 = 0;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
}

void func_80867C14(func_80867BDC_a0* arg0, GlobalContext* globalCtx) {
    arg0->unk_18++;
    if (arg0->unk_18 > 0x55) {
        arg0->unk_18 = 0x55;
    }
    if (arg0->unk_18 != 0x55) {
        arg0->unk_1C = arg0->unk_18 - 0x1C;
        if (arg0->unk_18 - 0x1C < 0) {
            arg0->unk_1C = 0;
        }
    } else {
        arg0->unk_1C++;
        if (arg0->unk_1C > 0x55) {
            func_80867FE4(arg0, globalCtx);
        }
    }
    arg0->unk_14++;
}

void func_80867C8C(func_80867BDC_a0* arg0, GlobalContext* globalCtx) {
    s32 temp_s6 = arg0->unk_18 - arg0->unk_1C;
    s32 i;
    f32 pad;

    if (temp_s6 > 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        Matrix_StatePush();
        for (i = 0; i < temp_s6; i++) {
            f32 temp_f0 = (f32)i / temp_s6;
            s16 temp_s0 = ((f32)arg0->unk_18 - arg0->unk_1C) * temp_f0 + arg0->unk_1C;
            f32 temp_f24 = 1.0f - (temp_s0 * 0.011764706f);
            f32 temp_f26 = Rand_ZeroOne() * 0.03f * temp_f0 * temp_f24;
            f32 temp_f28;
            f32 temp_f30 = Math_SinS(temp_s0 * 0x9A6) * 45.0f + arg0->pos.x;
            f32 phi_f24;

            if (arg0->unk_20 != 0) {
                phi_f24 = arg0->pos.y - (0.03f * temp_s0) - (0.01f * temp_s0 * temp_s0);
            } else {
                phi_f24 = arg0->pos.y + (0.03f * temp_s0) + (0.01f * temp_s0 * temp_s0);
            }
            temp_f28 = (Math_CosS(temp_s0 * 0x9A6) * 45.0f) + arg0->pos.z;
            Matrix_InsertTranslation(2.0f * Rand_Centered() + temp_f30, 2.0f * Rand_Centered() + phi_f24,
                                     2.0f * Rand_Centered() + temp_f28, 0);
            Matrix_Scale(temp_f26, temp_f26, temp_f26, 1);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, 255);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 150, 0, 255);
            func_8012C2DC(globalCtx->state.gfxCtx);
            Matrix_InsertMatrix(&globalCtx->billboardMtxF, 1);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_04023210);
        }
        Matrix_StatePop();
        gSPMatrix(POLY_XLU_DISP++, &D_801D1DE0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void func_80867FBC(func_80867BDC_a0* arg0, GlobalContext* globalCtx, s32 arg2) {
    arg0->unk_0C = func_80867C14;
    arg0->unk_10 = func_80867C8C;
    arg0->unk_20 = arg2;
}

void func_80867FE4(func_80867BDC_a0* arg0, GlobalContext* globalCtx) {
    arg0->unk_0C = NULL;
    arg0->unk_10 = NULL;
    func_80867BDC(arg0, globalCtx, &arg0->pos);
}

void func_8086800C(EnBox* this, GlobalContext* globalCtx) {
    s32 pad;
    CollisionPoly* outPoly;
    s32 outBgId;
    Vec3f pos;
    f32 floorHeight;

    if (!(this->unk_1EE & 0x80)) {
        pos = this->dyna.actor.world.pos;
        pos.y += 1.0f;
        floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &outPoly, &outBgId, &this->dyna.actor, &pos);
        if (floorHeight != BGCHECK_Y_MIN) {
            this->dyna.actor.world.pos.y = floorHeight;
            this->dyna.actor.floorHeight = floorHeight;
        }
    }
}

#ifdef NON_MATCHING
void EnBox_Init(Actor* thisx, GlobalContext* globalCtx) {
    s16 phi_s0;
    EnBox* this = (EnBox*)thisx;
    s16 pad;
    CollisionHeader* sp48;
    f32 sp44; // animationFrame
    f32 sp40; // animationFrameCount

    sp48 = NULL;
    sp44 = 0.0f;
    sp40 = Animation_GetLastFrame(&D_0600043C);
    Actor_ProcessInitChain(&this->dyna.actor, D_80869B50);
    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&D_060080E8, &sp48);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp48);
    this->unk_1EE = 0;
    this->unk_1F1 = (this->dyna.actor.params >> 0xC) & 0xF;
    this->unk_1F2 = 0;
    this->unk_1F3 = 0;
    this->dyna.actor.gravity = -5.5f;
    this->dyna.actor.minVelocityY = -50.0f;
    this->unk_1F0 = this->dyna.actor.world.rot.z;
    this->dyna.actor.floorHeight = this->dyna.actor.world.pos.y;
    if (this->dyna.actor.world.rot.x == 180) {
        this->unk_1EE = 0x80;
        this->dyna.actor.world.rot.x = 0x7FFF;
        this->unk_220 = 0;
    } else {
        func_800C636C(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->unk_220 = this->dyna.actor.world.rot.x & 0x7F;
        this->dyna.actor.world.rot.x = 0;
    }
    this->getItem = (this->dyna.actor.params >> 5) & 0x7F;
    this->dyna.actor.shape.rot.x = this->dyna.actor.world.rot.x;
    if (Actor_GetChestFlag(globalCtx, this->dyna.actor.params & 0x1F) || this->getItem == 0) {
        this->unk_1EF = 0xFF;
        this->unk_1F2 = 100;
        func_80867BD0(this, func_80869020);
        this->unk_1EE |= 0x10;
        sp44 = sp40;
    } else if ((this->unk_1F1 == 3 || this->unk_1F1 == 8) && (Flags_GetSwitch(globalCtx, this->unk_1F0) == 0)) {
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        if (Rand_ZeroOne() < 0.5f) {
            this->unk_1EE |= 4;
        }
        this->unk_1A0 = -12;
        func_80867BD0(this, func_80868944);
        this->unk_1EF = 0;
        this->unk_1EE |= 1;
        this->dyna.actor.flags |= 0x10;
    } else if ((this->unk_1F1 == 1 || this->unk_1F1 == 7) &&
               (Actor_GetRoomCleared(globalCtx, this->dyna.actor.room) == 0)) {
        func_80867BD0(this, func_80868A6C);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        if (this->unk_1EE & 0x80) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 50.0f;
        } else {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y - 50.0f;
        }
        this->unk_1EF = 0;
        this->unk_1EE |= 1;
        this->dyna.actor.flags |= 0x10;
    } else if (this->unk_1F1 == 9 || this->unk_1F1 == 0xA) {

    } else if ((this->unk_1F1 == 0xB || this->unk_1F1 == 0xC) && (Flags_GetSwitch(globalCtx, this->unk_1F0) == 0)) {
        func_80867BD0(this, func_808689E8);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        if (this->unk_1EE & 0x80) {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 50.0f;
        } else {
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y - 50.0f;
        }
        this->unk_1EF = 0;
        this->unk_1EE |= 1;
        this->dyna.actor.flags |= 0x10;
    } else {
        if (this->unk_1F1 == 4 || this->unk_1F1 == 6) {
            this->dyna.actor.flags |= 0x80;
        }
        func_80867BD0(this, func_80868CC8);
        this->unk_1EE |= 1;
        this->unk_1EE |= 0x10;
    }

    if (this->getItem == 0x11 && Actor_GetChestFlag(globalCtx, this->dyna.actor.params & 0x1F) == 0) {
        this->dyna.actor.flags |= 0x10;
    }

    this->dyna.actor.shape.rot.y += 0x8000;

    this->dyna.actor.home.rot.z = this->dyna.actor.world.rot.z = this->dyna.actor.shape.rot.z = 0;

    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060066A0, &D_0600043C, &this->jointTable, &this->morphTable, 5);
    Animation_Change(&this->skelAnime, &D_0600043C, 1.5f, sp44, sp40, (u8)2, 0.0f);
    if (func_800BE63C(this) != 0) {
        Actor_SetScale(&this->dyna.actor, 0.0075f);
        Actor_SetHeight(&this->dyna.actor, 20.0f);
    } else {
        Actor_SetScale(&this->dyna.actor, 0.01f);
        Actor_SetHeight(&this->dyna.actor, 40.0f);
    }

    this->unk_218 = -1;
    this->unk_21A = -1;
    phi_s0 = this->dyna.actor.cutscene;

    while (phi_s0 != -1) {
        if (func_800F2178(phi_s0) == 1) {
            this->unk_21A = phi_s0;
        } else {
            this->unk_218 = phi_s0;
        }
        phi_s0 = ActorCutscene_GetAdditionalCutscene(phi_s0);
    }
    func_80867BDC(&this->unk_1F4, globalCtx, &this->dyna.actor.home.pos);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/EnBox_Init.s")
#endif

void EnBox_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBox* this = (EnBox*)thisx;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80868630(EnBox* this, Vec3f* pos, Vec3f* velocity, Vec3f* accel) {
    f32 sp24;
    s16 rot;

    sp24 = Rand_ZeroOne() * 25.0f;
    rot = Rand_ZeroOne() * 65536.0f;
    *pos = this->dyna.actor.world.pos;
    pos->x += Math_SinS(rot) * sp24;
    pos->z += Math_CosS(rot) * sp24;
    velocity->y = 1.0f;
    velocity->x = Math_SinS(rot);
    velocity->z = Math_CosS(rot);
    accel->x = 0.0f;
    accel->y = 0.0f;
    accel->z = 0.0f;
}

void func_80868734(EnBox* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;

    for (i = 0; i < 20; i++) {
        func_80868630(this, &pos, &velocity, &accel);
        func_800B1280(globalCtx, &pos, &velocity, &accel, 100, 30, 15);
    }
}

void func_808687E8(EnBox* this, GlobalContext* globalCtx) {
    f32 temp_f0;

    this->unk_1EF = -1;
    this->unk_1EE &= ~1;
    if (this->dyna.actor.bgCheckFlags & 1) {
        this->unk_1EE |= 2;
        if (this->unk_1EE & 4) {
            this->unk_1EE &= ~4;
        } else {
            this->unk_1EE |= 4;
        }
        if (this->unk_1F1 == 3) {
            this->dyna.actor.velocity.y = -this->dyna.actor.velocity.y * 0.55f;
        } else {
            this->dyna.actor.velocity.y = -this->dyna.actor.velocity.y * 0.65f;
        }
        if (this->dyna.actor.velocity.y < 5.5f) {
            this->dyna.actor.shape.rot.z = 0;
            this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
            func_80867BD0(this, func_80868CC8);
        }
        func_8019F1C0(&this->dyna.actor.projectedPos, NA_SE_EV_TRE_BOX_BOUND);
        func_80868734(this, globalCtx);
    }
    temp_f0 = this->dyna.actor.world.pos.y - this->dyna.actor.floorHeight;
    if (this->unk_1EE & 4) {
        this->dyna.actor.shape.rot.z = temp_f0 * 50.0f;
    } else {
        this->dyna.actor.shape.rot.z = -temp_f0 * 50.0f;
    }
}

void func_80868944(EnBox* this, GlobalContext* globalCtx) {
    func_800B8C50(&this->dyna.actor, globalCtx);
    if (this->unk_1A0 >= 0) {
        func_80867BD0(this, func_808687E8);
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    } else if (this->unk_1A0 >= -11) {
        this->unk_1A0++;
    } else if (Flags_GetSwitch(globalCtx, this->unk_1F0)) {
        this->unk_1A0++;
    }
}

void func_808689E8(EnBox* this, GlobalContext* globalCtx) {
    func_800B8C50(&this->dyna.actor, globalCtx);
    if (Flags_GetSwitch(globalCtx, this->unk_1F0)) {
        if (ActorCutscene_GetCanPlayNext(this->unk_218)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_218, &this->dyna.actor);
            func_80867BD0(this, func_80868AFC);
            this->unk_1A0 = -30;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_218);
        }
    }
}

void func_80868A6C(EnBox* this, GlobalContext* globalCtx) {
    func_800B8C50(&this->dyna.actor, globalCtx);
    if (Actor_GetRoomClearedTemp(globalCtx, this->dyna.actor.room)) {
        if (ActorCutscene_GetCanPlayNext(this->unk_218)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_218, &this->dyna.actor);
            Actor_SetRoomCleared(globalCtx, this->dyna.actor.room);
            func_80867BD0(this, func_80868AFC);
            this->unk_1A0 = -30;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_218);
        }
    }
}

void func_80868AFC(EnBox* this, GlobalContext* globalCtx) {
    if ((func_800F22C4(this->unk_218, &this->dyna.actor) != 0) || (this->unk_1A0 != 0)) {
        func_80867BD0(this, func_80868B74);
        this->unk_1A0 = 0;
        func_80867FBC(&this->unk_1F4, globalCtx, (this->unk_1EE & 0x80) != 0);
        func_8019F1C0(&this->dyna.actor.projectedPos, 0x287B);
    }
}

void func_80868B74(EnBox* this, GlobalContext* globalCtx) {
    func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    if (this->unk_1A0 < 0) {
        this->unk_1A0++;
    } else if (this->unk_1A0 < 40) {
        if (this->unk_1EE & 0x80) {
            this->dyna.actor.world.pos.y -= 1.25f;
        } else {
            this->dyna.actor.world.pos.y += 1.25f;
        }
        this->unk_1A0 += 1;
        if (this->unk_218 != -1 && ActorCutscene_GetCurrentIndex() == this->unk_218) {
            if (this->unk_1A0 == 2) {
                func_800B724C(globalCtx, &this->dyna.actor, 4);
            } else if (this->unk_1A0 == 22) {
                func_800B724C(globalCtx, &this->dyna.actor, 1);
            }
        }
    } else if (this->unk_1A0 < 60) {
        this->unk_1EF += 12;
        this->unk_1A0++;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
    } else {
        func_80867BD0(this, func_80868CC8);
        ActorCutscene_Stop(this->dyna.actor.cutscene);
    }
}

void func_80868CC8(EnBox* this, GlobalContext* globalCtx) {
    s32 pad;
    AnimationHeader* animHeader;
    f32 lastFrame;
    f32 playbackSpeed;
    T_80869B54 sp5C;
    Player* player;
    Vec3f offset;

    this->unk_1EF = 0xFF;
    this->unk_1EE |= 1;
    if (this->unk_1EC != 0 && (this->unk_21A < 0 || ActorCutscene_GetCurrentIndex() == this->unk_21A ||
                               ActorCutscene_GetCurrentIndex() == -1)) {
        if (this->unk_1EC < 0) {
            animHeader = &D_0600043C;
            playbackSpeed = 1.5f;
        } else {
            u8 playerForm;
            sp5C = D_80869B54;
            playerForm = gSaveContext.playerForm;
            animHeader = D_80869B68[playerForm];
            playbackSpeed = sp5C.test[playerForm];
        }

        lastFrame = Animation_GetLastFrame(animHeader);
        Animation_Change(&this->skelAnime, animHeader, playbackSpeed, 0.0f, lastFrame, 2, 0.0f);
        func_80867BD0(this, func_80869020);
        if (this->unk_1EC > 0) {
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_DEMO_TRE_LGT,
                               this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                               this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z,
                               -1);
            func_801A3098(0x92BU);
        }

        if (this->getItem == 0x11) {
            this->unk_1EE |= 0x20;
        } else {
            if (this->getItem == GI_HEART_PIECE || this->getItem == GI_5A) {
                Actor_SetCollectibleFlag(globalCtx, this->unk_220);
            }
            Actor_SetChestFlag(globalCtx, this->dyna.actor.params & 0x1F);
        }
    } else {
        player = GET_PLAYER(globalCtx);
        Actor_CalcOffsetOrientedToDrawRotation(&this->dyna.actor, &offset, &player->actor.world.pos);
        if (offset.z > -50.0f && offset.z < 0.0f && fabsf(offset.y) < 10.0f && fabsf(offset.x) < 20.0f &&
            Actor_IsLinkFacingActor(&this->dyna.actor, 0x3000, globalCtx)) {
            if ((this->getItem == GI_HEART_PIECE || this->getItem == GI_5A) &&
                Actor_GetCollectibleFlag(globalCtx, this->unk_220)) {
                this->getItem = GI_0A;
            }
            if (this->getItem == 0x7C && INV_CONTENT(ITEM_MASK_CAPTAIN) == ITEM_MASK_CAPTAIN) {
                this->getItem = GI_0A;
            }
            if (this->getItem == 0x7D && INV_CONTENT(ITEM_MASK_GIANT) == ITEM_MASK_GIANT) {
                this->getItem = GI_0A;
            }
            func_800B8B84(&this->dyna.actor, globalCtx, -this->getItem);
        }
        if (Actor_GetChestFlag(globalCtx, this->dyna.actor.params & 0x1F)) {
            func_80867BD0(this, func_80869020);
        }
    }
}

#ifdef NON_MATCHING
void func_80869020(EnBox* this, GlobalContext* globalCtx) {
    s32 pad;

    this->dyna.actor.flags &= ~0x80;

    if (SkelAnime_Update(&this->skelAnime) != 0) {
        if (this->unk_1EC > 0) {
            if (this->unk_1EC < 0x78) {
                this->unk_1EC++;
            } else {
                Math_StepToF(&this->unk_1A8, 0.0f, 0.05f);
            }
        } else if (this->unk_1EC >= -0x77) {
            this->unk_1EC--;
        } else {
            Math_StepToF(&this->unk_1A8, 0.0f, 0.05f);
        }
        if (this->unk_1EE & 0x20) {
            this->unk_1EE &= ~0x20;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_EN_ELFORG,
                               this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                               this->dyna.actor.world.rot.x, this->dyna.actor.world.rot.y, this->dyna.actor.world.rot.z,
                               ((this->dyna.actor.params & 0x1F) << 9) | 2 | 4);
        } else if (this->unk_1EE & 0x40) {
            this->unk_1EE &= ~0x40;
        }
    } else {
        f32 sp58;
        WaterBox* sp54;
        s32 sp50;
        u16 sp4E = 0;

        if (Animation_OnFrame(&this->skelAnime, gSaveContext.playerForm == PLAYER_FORM_DEKU ? 14.0f : 30.0f) != 0) {
            sp4E = NA_SE_EV_TBOX_UNLOCK;
        } else if (Animation_OnFrame(&this->skelAnime, gSaveContext.playerForm == PLAYER_FORM_DEKU ? 15.0f : 90.0f) !=
                   0) {
            sp4E = NA_SE_EV_TBOX_OPEN;
        }
        if (sp4E != 0) {
            func_8019F1C0(&this->dyna.actor.projectedPos, sp4E);
        }
        if (this->skelAnime.jointTable[3].z > 0) {
            this->unk_1A8 = (0x7D00 - this->skelAnime.jointTable[3].z) * 0.00006f;
            if (this->unk_1A8 < 0.0f) {
                this->unk_1A8 = 0.0f;
            } else if (this->unk_1A8 > 1.0f) {
                this->unk_1A8 = 1.0f;
            }
        }
        if ((WaterBox_GetSurfaceImpl(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x,
                                     this->dyna.actor.world.pos.z, &sp58, &sp54, &sp50) != 0) &&
            this->dyna.actor.floorHeight < sp58) {
            EffectSsBubble_Spawn(globalCtx, &this->dyna.actor.world.pos, 5.0f, 2.0f, 20.0f, 0.3f);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Box/func_80869020.s")
#endif

extern Vec3f D_80869B7C;
extern Vec3f D_80869B88;

void func_808692E0(EnBox* this, GlobalContext* globalCtx) {
    Vec3f pos;
    Vec3f velocity = D_80869B7C;
    Vec3f accel = D_80869B88;
    f32 randomf;

    this->unk_1F2++;
    func_800B9010(&this->dyna.actor, NA_SE_EN_LAST3_COIL_ATTACK_OLD - SFX_FLAG);
    if (Rand_ZeroOne() < 0.3f) {
        randomf = 2.0f * Rand_ZeroOne() - 1.0f;
        pos = this->dyna.actor.world.pos;
        pos.x += randomf * 20.0f * Math_SinS(this->dyna.actor.world.rot.y + 0x4000);
        pos.z += randomf * 20.0f * Math_CosS(this->dyna.actor.world.rot.y + 0x4000);

        randomf = 2.0f * Rand_ZeroOne() - 1.0f;
        velocity.x = randomf * 1.6f * Math_SinS(this->dyna.actor.world.rot.y);
        velocity.y = 1.8f;
        velocity.z = randomf * 1.6f * Math_CosS(this->dyna.actor.world.rot.y);
        EffectSsIceSmoke_Spawn(globalCtx, &pos, &velocity, &accel, 150);
    }
}

void EnBox_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBox* this = (EnBox*)thisx;

    if (this->unk_1EE & 0x10) {
        this->unk_1EE &= ~0x10;
        func_8086800C(this, globalCtx);
    }
    if (this->getItem == 0x11 && !Actor_GetChestFlag(globalCtx, this->dyna.actor.params & 0x1F)) {
        globalCtx->actorCtx.unk5 |= 8;
    }
    this->actionFunc(this, globalCtx);
    if (this->unk_1EE & 0x80) {
        this->unk_1EE |= 1;
    }
    if (!(this->unk_1EE & 1)) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->dyna.actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 0x1CU);
    }
    Actor_SetHeight(&this->dyna.actor, 40.0f);
    if (this->getItem == 0x76 && this->actionFunc == func_80869020 && this->skelAnime.curFrame > 45.0f &&
        this->unk_1F2 < 0x64) {
        func_808692E0(this, globalCtx);
    }
    if (this->unk_1F4.unk_0C != NULL) {
        this->unk_1F4.unk_0C(&this->unk_1F4, globalCtx);
    }
}

// PostLimbDraw
void func_80869600(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnBox* this = THIS;
    s32 pad;

    if (limbIndex == 1) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (this->unk_1F1 == 2) {
            gSPDisplayList((*gfx)++, &D_06000DB0);
        } else if (func_800BE63C(this) != 0) {
            if (this->getItem == 0x3C) {
                gSPDisplayList((*gfx)++, &D_06000A50);
            } else {
                gSPDisplayList((*gfx)++, &D_060006F0);
            }
        } else {
            gSPDisplayList((*gfx)++, &D_06000A50);
        }
    } else if (limbIndex == 3) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (this->unk_1F1 == 2) {
            gSPDisplayList((*gfx)++, &D_06001D58);
        } else if (func_800BE63C(this) != 0) {
            if (this->getItem == 0x3C) {
                gSPDisplayList((*gfx)++, &D_06001850);
            } else {
                gSPDisplayList((*gfx)++, &D_060012E8);
            }
        } else {
            gSPDisplayList((*gfx)++, &D_06001850);
        }
    }
}

Gfx* func_80869850(GraphicsContext* gfxCtx) {
    Gfx* dl = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);

    gSPEndDisplayList(dl);
    return dl;
}

Gfx* func_80869874(GraphicsContext* gfxCtx) {
    Gfx* dl = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);
    Gfx* cur = dl;

    gDPSetRenderMode(
        cur++, AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL | G_RM_FOG_SHADE_A,
        AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
            GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));

    gSPEndDisplayList(cur++);
    return dl;
}

Gfx* func_808698B4(GraphicsContext* gfxCtx) {
    Gfx* dl = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);
    Gfx* cur = dl;

    gDPSetRenderMode(cur++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gSPEndDisplayList(cur++);
    return dl;
}

void EnBox_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBox* this = (EnBox*)thisx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (this->unk_1F4.unk_10 != NULL) {
        this->unk_1F4.unk_10(&this->unk_1F4, globalCtx);
    }
    if ((this->unk_1EF == 0xFF && this->unk_1F1 != 4 && this->unk_1F1 != 6) ||
        ((this->dyna.actor.flags & 0x80) != 0x80 && (this->unk_1F1 == 4 || this->unk_1F1 == 6))) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
        gSPSegment(POLY_OPA_DISP++, 0x08, func_80869850(globalCtx->state.gfxCtx));
        func_8012C28C(globalCtx->state.gfxCtx);
        POLY_OPA_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL,
                                       func_80869600, &this->dyna.actor, POLY_OPA_DISP);
    } else if (this->unk_1EF != 0) {
        gDPPipeSync(POLY_XLU_DISP++);
        func_8012C2DC(globalCtx->state.gfxCtx);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_1EF);
        if (this->unk_1F1 == 4 || this->unk_1F1 == 6) {
            gSPSegment(POLY_XLU_DISP++, 0x08, func_808698B4(globalCtx->state.gfxCtx));
        } else {
            gSPSegment(POLY_XLU_DISP++, 0x08, func_80869874(globalCtx->state.gfxCtx));
        }
        POLY_XLU_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL,
                                       func_80869600, &this->dyna.actor, POLY_XLU_DISP);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
