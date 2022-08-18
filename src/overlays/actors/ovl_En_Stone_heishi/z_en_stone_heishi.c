/*
 * File: z_en_stone_heishi.c
 * Overlay: ovl_En_Stone_heishi
 * Description: Shiro
 */

#include "z_en_stone_heishi.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_80)

#define THIS ((EnStoneheishi*)thisx)

void EnStoneheishi_Init(Actor* thisx, PlayState* play);
void EnStoneheishi_Destroy(Actor* thisx, PlayState* play);
void EnStoneheishi_Update(Actor* thisx, PlayState* play);
void EnStoneheishi_Draw(Actor* thisx, PlayState* play);

void func_80BC9560(EnStoneheishi* this, PlayState* play);
void func_80BC9680(EnStoneheishi* this, PlayState* play);
void func_80BC9908(EnStoneheishi* this, PlayState* play);
void func_80BC9A2C(EnStoneheishi* this, PlayState* play);
void func_80BC9D28(EnStoneheishi* this, PlayState* play);
void func_80BC9E50(EnStoneheishi* this, PlayState* play);
void func_80BC94B0(EnStoneheishi* this);
void func_80BC941C(EnStoneheishi* this);
void func_80BC935C(EnStoneheishi* this, s32 animIndex);
void func_80BC9660(EnStoneheishi* this);
void func_80BC98EC(EnStoneheishi*); /* extern */
void func_80BC9C88(EnStoneheishi* this, PlayState* play);
void func_80BC9A10(EnStoneheishi* this);
s32 func_80BCA0AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx);                                                                         /* extern */
void func_80BCA104(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx); /* extern */

#if 1
const ActorInit En_Stone_heishi_InitVars = {
    ACTOR_EN_STONE_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnStoneheishi),
    (ActorFunc)EnStoneheishi_Init,
    (ActorFunc)EnStoneheishi_Destroy,
    (ActorFunc)EnStoneheishi_Update,
    (ActorFunc)EnStoneheishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BCA3A0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 15, 70, 0, { 0, 0, 0 } },
};

static u16 D_80BCA3CC[0xA] = { 0x1473, 0x1474, 0x1475, 0x1476, 0x1477, 0x1478, 0x1479, 0x147A, 0x1472, 0, };

static AnimationHeader *D_80BCA3E0[5] = {
    (AnimationHeader *)0x06006C18,
    (AnimationHeader *)0x060020D8,
    (AnimationHeader *)0x06002A84,
    (AnimationHeader *)0x06003BFC,
    (AnimationHeader *)0x06003380,
};

AnimationHeader *D_80BCA3F4 = (AnimationHeader *)0x060020D8;

u8 *D_80BCA3FC = 0x20000;

//static Vec3f D_80BCA404 = { 0.0f, 0.0f, 0.0f, };

//static f32 D_80BCA408 = 0.0f;

#endif

extern ColliderCylinderInit D_80BCA3A0;

extern UNK_TYPE D_06000768;
extern UNK_TYPE D_06003BFC;

extern FlexSkeletonHeader D_0600D640;

extern AnimationHeader* D_80BCA3E0[5];
extern AnimationHeader* D_80BCA3F4;
//extern u8 D_80BCA3FC[];
//extern u16 D_80BCA3CC[10];
extern Gfx* D_06000630;

//extern Vec3f D_80BCA404;
// extern f32 D_80BCA408;
// extern f32 D_80BCA40C;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Init.s")

void EnStoneheishi_Init(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_0600D640, (AnimationHeader*)&D_06003BFC, &this->unk188, &this->unk1EE,
                       0x11);

    this->actor.colChkInfo.mass = 0xFF;
    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;

    Collider_InitAndSetCylinder(play, &this->unk278, &this->actor, &D_80BCA3A0);

    this->unk278.dim.radius = 0x28;
    this->unk278.dim.height = 0x28;
    this->unk278.dim.yShift = 0;

    func_80BC94B0(this);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Destroy.s")

void EnStoneheishi_Destroy(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;

    Collider_DestroyCylinder(play, &this->unk278);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC935C.s")

void func_80BC935C(EnStoneheishi* this, s32 animIndex) {
    f32 phi_fv0 = 0.0f;

    this->animMode = animIndex;
    this->endFrame = (f32)Animation_GetLastFrame(D_80BCA3E0[animIndex]);

    if (animIndex == 5) {
        phi_fv0 = 55.0f;
    }

    Animation_Change(&this->skelAnime, D_80BCA3E0[this->animMode], 1.0f, phi_fv0, this->endFrame,
                     D_80BCA3FC[this->animMode], -10.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC941C.s")

void func_80BC941C(EnStoneheishi* this) {
    s16 temp_v0;
    s32 phi_v1;

    temp_v0 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    phi_v1 = ABS_ALT(temp_v0);

    this->unk260 = 0;

    if ((this->actor.xzDistToPlayer < 200.0f) && (phi_v1 < 0x4E20)) {
        this->unk260 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
        if (this->unk260 >= 0x2711) {
            this->unk260 = 0x2710;
        } else {
            if (this->unk260 < -0x2710) {
                this->unk260 = -0x2710;
            }
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC94B0.s")

void func_80BC94B0(EnStoneheishi* this) {
    this->unk272 = 0;
    if ((gSaveContext.save.weekEventReg[0x29] & 0x40) != 0) {
        func_80BC935C(this, 2);
        this->unk272 = 8;
        this->actor.flags &= -0x81;
    } else {
        func_80BC935C(this, 3);
        if ((gSaveContext.save.weekEventReg[0x29] & 0x80) != 0) {
            this->unk272 = 2;
        }
    }
    this->actor.textId = D_80BCA3CC[this->unk272];
    this->unk270 = 0;
    this->actionFunc = func_80BC9560;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9560.s")

void func_80BC9560(EnStoneheishi* this, PlayState* play) {
    Player* sp1C = GET_PLAYER(play);
    s16 temp_v1;
    s32 phi_v0;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BC9660(this);
        return;
    }

    if (((gSaveContext.save.weekEventReg[0x29] & 0x40) == 0) && (play->actorCtx.unk4 != 0x64)) {
        this->actor.flags |= 0x08000000;
        return;
    }

    SkelAnime_Update(&this->skelAnime);

    this->actor.flags &= 0xF7FFFFFF;
    temp_v1 = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    phi_v0 = ABS_ALT(temp_v1);

    if ((phi_v0 < 0x18F1) && ((s32)(sp1C->stateFlags1 << 8) >= 0)) {
        func_800B8614(&this->actor, play, 70.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9660.s")

void func_80BC9660(EnStoneheishi* this) {
    this->unk274 = 0;
    this->unk270 = 1;
    this->actionFunc = func_80BC9680;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9680.s")

void func_80BC9680(EnStoneheishi* this, PlayState* play) {
    f32 frame = this->skelAnime.curFrame;

    if ((this->unk272 == 0) || (this->unk272 == 2)) {
        if (this->animMode != 4) {
            if (fabsf(this->unk258 - this->unk25E) < 50.0f) {
                func_80BC935C(this, 4);
            }
            return;
        }
    } else if (this->unk272 == 3) {
        if (this->animMode != 3) {
            if ((this->unk268 == 0) && (fabsf((f32)(this->unk258 - this->unk25E)) < 50.0f)) {
                func_80BC935C(this, 3);
            }
            return;
        } else if ((this->unk274 == 0) && (this->endFrame <= frame)) {
            Player* player = GET_PLAYER(play);

            this->unk274 = 1;
            player->actor.textId = D_80BCA3CC[this->unk272];

            func_80151938(play, D_80BCA3CC[this->unk272]);
            func_80151BB4(play, 0x12);
        }
    }

    SkelAnime_Update(&this->skelAnime);

    if ((Message_GetState(&play->msgCtx) == 5) && (Message_ShouldAdvance(play) != 0)) {
        func_801477B4(play);

        if (this->unk272 == 2) {
            func_80151938(play, 0xFF);
            func_80BC98EC(this);
            return;
        }
        if (this->unk272 == 3) {
            func_80BC94B0(this);
            return;
        }
        if (this->unk272 == 6) {
            func_80BC9C88(this, play);
            return;
        }
        if (this->unk272 < 7) {
            this->unk272++;
        } else {
            func_80151BB4(play, 0x12);
            func_80BC94B0(this);
            return;
        }

        func_80151938(play, D_80BCA3CC[this->unk272]);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC98EC.s")

void func_80BC98EC(EnStoneheishi* this) {
    this->unk270 = 2;
    this->actionFunc = func_80BC9908;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9908.s")

void func_80BC9908(EnStoneheishi* this, PlayState* play) {
    s32 temp_v0;

    SkelAnime_Update(&this->skelAnime);

    if (Message_GetState(&play->msgCtx) == 0x10) {
        temp_v0 = func_80123810(play);
        if (temp_v0 > 0) {
            this->unk268 = 0x28;
            func_801477B4(play);

            if ((temp_v0 == 0x23) || (temp_v0 == 0x24)) {
                this->unk277 = 0;
                if (temp_v0 == 0x24) {
                    this->unk277 = 1;
                }
                func_80BC9A10(this);
            } else {
                Player* player = GET_PLAYER(play);
                this->unk272 = 3;
                player->actor.textId = 0;
                gSaveContext.save.weekEventReg[0x29] |= 0x80;
                this->unk270 = 1;
                this->actionFunc = func_80BC9680;
            }
        } else if (temp_v0 < 0) {
            func_801477B4(play);
            func_80151BB4(play, 0x12);
            func_80BC94B0(this);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9A10.s")

void func_80BC9A10(EnStoneheishi* this) {
    this->unk270 = 3;
    this->actionFunc = func_80BC9A2C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9A2C.s")

void func_80BC9A2C(EnStoneheishi* this, PlayState* play) {
    f32 temp_fv0 = this->skelAnime.curFrame;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);

    switch (this->unk26A) {
        case 0:
            if (this->unk268 == 0) {
                this->unk272 = 4;
                func_80151938(play, D_80BCA3CC[this->unk272]);
                player->actor.textId = D_80BCA3CC[this->unk272];
                this->unk26A += 1;
            }

        default:
            return;

        case 1:
            if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
                Player* temp_a0 = (Player*)play->actorCtx.actorLists[ACTORCAT_PLAYER].first;
                play->msgCtx.msgLength = 0;
                temp_a0->actor.textId = 0;
                temp_a0->exchangeItemId = 0;
                this->unk276 = 1;

                if (this->unk277) {
                    this->unk276 = 3;
                }

                Player_SetModels(temp_a0, 3);
                func_80BC935C(this, 1);
                this->unk268 = 0x1E;
                this->unk26A++;
            }
            break;

        case 2:
            if (this->unk268 != 0) {
                if ((this->unk268 < 0xA) && (this->unk276 != 2)) {
                    this->unk276 = 2;
                    Actor_PlaySfxAtPos(&this->actor, 0x684E);
                    func_80123D50(play, GET_PLAYER(play), 0x12, 0x15);
                }
            } else {
                this->unk26A++;
            }
            break;

        case 3:
            if (this->endFrame <= temp_fv0) {
                func_801A3098(0x922U);
                this->unk276 = 0;
                func_80BC935C(this, 6);
                this->unk26A += 1;
            }
            break;

        case 4:
            if (this->endFrame <= temp_fv0) {
                this->unk272 = 5;
                func_80151938(play, D_80BCA3CC[this->unk272]);
                player->actor.textId = D_80BCA3CC[this->unk272];
                func_80BC935C(this, 0);
                this->unk270 = 1;
                this->actionFunc = func_80BC9680;
            }
            break;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9C88.s")

void func_80BC9C88(EnStoneheishi* this, PlayState* play) {
    func_801477B4(play);

    if (gSaveContext.save.inventory.items[gItemSlots[0x45]] == 0x45) {
        Actor_PickUp(&this->actor, play, 2, 300.0f, 300.0f);
    } else {
        Actor_PickUp(&this->actor, play, 0x8B, 300.0f, 300.0f);
    }

    this->unk270 = 4;
    this->actionFunc = func_80BC9D28;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9D28.s")

void func_80BC9D28(EnStoneheishi* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->unk272 += 1;
        this->actor.textId = D_80BCA3CC[this->unk272];
        gSaveContext.save.weekEventReg[0x29] |= 0x40;
        Actor_ProcessTalkRequest(&this->actor, &play->state);
        func_800B8500(&this->actor, play, 400.0f, 400.0f, PLAYER_AP_MINUS1);
        this->actionFunc = func_80BC9E50;
    } else if (gSaveContext.save.inventory.items[gItemSlots[0x45]] == 0x45) {
        Actor_PickUp(&this->actor, play, 2, 300.0f, 300.0f);
    } else {
        Actor_PickUp(&this->actor, play, 0x8B, 300.0f, 300.0f);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BC9E50.s")

void func_80BC9E50(EnStoneheishi* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80151BB4(play, 0x35);
        func_80151BB4(play, 0x12);
        this->unk270 = 1;
        this->actionFunc = func_80BC9680;
    } else {
        func_800B8500(&this->actor, play, 400.0f, 400.0f, PLAYER_AP_MINUS1);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Update.s")

void EnStoneheishi_Update(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = THIS;
    s32 pad;
    Player* sp2C = GET_PLAYER(play);

    if (this->unk268 != 0) {
        this->unk268--;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actionFunc(this, play);

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 50.0f, 0x1DU);
    Actor_SetScale(&this->actor, 0.01f);

    if ((((gSaveContext.save.weekEventReg[0x29] & 0x40) != 0) || (play->actorCtx.unk4 == 0x64)) &&
        (((s32)sp2C->stateFlags1 << 8) >= 0)) {
        if ((this->animMode != 3) && ((((this->unk270 == 0) || (this->unk270 == 1)) || (this->unk270 == 2)) ||
                                      ((this->unk270 == 3) && (this->unk26A < 2)))) {
            func_80BC941C(this);
        } else {
            this->unk260 = 0;
        }

        if ((gSaveContext.save.weekEventReg[0x29] & 0x40) == 0) {
            Actor_SetFocus(&this->actor, 30.0f);
        } else {
            Actor_SetFocus(&this->actor, 60.0f);
        }

        Math_SmoothStepToS(&this->unk25A, this->unk260, 1, 0xBB8, 0);
        Math_SmoothStepToS(&this->unk258, this->unk25E, 1, 0x3E8, 0);
        Collider_UpdateCylinder(&this->actor, &this->unk278);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk278.base);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BCA0AC.s")

s32 func_80BCA0AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnStoneheishi* this = (EnStoneheishi*)thisx;
    if (limbIndex == 0x10) {
        rot->x += this->unk25A;
        rot->y += this->unk258;
        rot->z += this->unk25C;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/func_80BCA104.s")

void func_80BCA104(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    
    static Vec3f D_80BCA404 = { 0.0f, 0.0f, 0.0f, };
    EnStoneheishi* this = THIS;
    Gfx* gfx2;

    if ((limbIndex == 0xC) && ((this->unk276) != 0)) {
        gfx2 = func_8012C2B4(*gfx);

        D_80BCA404.x = 320.0f;
        D_80BCA404.y = 210.0f;
        D_80BCA404.z = 440.0f;
        Matrix_Translate(D_80BCA404.x, D_80BCA404.y, D_80BCA404.z, MTXMODE_APPLY);

        gDPPipeSync(gfx2++);

        Matrix_RotateYS(-0x1770, MTXMODE_APPLY);
        Matrix_RotateXS(0x7D0, MTXMODE_APPLY);
        Matrix_RotateZS(-0x7530, MTXMODE_APPLY);

        if (this->unk276 != 2) {
            if (this->unk276 == 3) {
                gDPSetEnvColor(gfx2++, 0, 0, 200, 0);
            } else {
                gDPSetEnvColor(gfx2++, 200, 0, 0, 0);
            }
            gSPMatrix(gfx2++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx2++, &D_06000768);
        }

        gSPMatrix(gfx2++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx2++, &D_06000630);

        *gfx = gfx2++;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Stone_heishi/EnStoneheishi_Draw.s")

void EnStoneheishi_Draw(Actor* thisx, PlayState* play) {
    EnStoneheishi* this = (EnStoneheishi*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    if ((gSaveContext.save.weekEventReg[0x29] & 0x40) == 0) {
        func_8012C2DC(play->state.gfxCtx);

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               func_80BCA0AC, func_80BCA104, &this->actor, POLY_XLU_DISP);
    } else {
        func_8012C28C(play->state.gfxCtx);

        POLY_OPA_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               func_80BCA0AC, func_80BCA104, &this->actor, POLY_OPA_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
