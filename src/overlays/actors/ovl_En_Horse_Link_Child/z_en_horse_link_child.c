/*
 * File: z_en_horse_link_child.c
 * Overlay: ovl_En_Horse_Link_Child
 * Description: Child Epona
 */

#include "z_en_horse_link_child.h"
#include "z64horse.h"
#include "objects/object_horse_link_child/object_horse_link_child.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnHorseLinkChild*)thisx)

void EnHorseLinkChild_Init(Actor* thisx, PlayState* play);
void EnHorseLinkChild_Destroy(Actor* thisx, PlayState* play);
void EnHorseLinkChild_Update(Actor* thisx, PlayState* play);
void EnHorseLinkChild_Draw(Actor* thisx, PlayState* play);

void func_808DEA0C(EnHorseLinkChild* this, PlayState* play);
void func_808DEB14(EnHorseLinkChild* this, PlayState* play);
void func_808DECA0(EnHorseLinkChild* this);
void func_808DED40(EnHorseLinkChild* this, PlayState* play);
void func_808DEFE8(EnHorseLinkChild* this);
void func_808DF194(EnHorseLinkChild* this, PlayState* play);
void func_808DF620(EnHorseLinkChild* this, PlayState* play);
void func_808DF788(EnHorseLinkChild* this);
void func_808DF838(EnHorseLinkChild* this, PlayState* play);

ActorInit En_Horse_Link_Child_InitVars = {
    ACTOR_EN_HORSE_LINK_CHILD,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HORSE_LINK_CHILD,
    sizeof(EnHorseLinkChild),
    (ActorFunc)EnHorseLinkChild_Init,
    (ActorFunc)EnHorseLinkChild_Destroy,
    (ActorFunc)EnHorseLinkChild_Update,
    (ActorFunc)EnHorseLinkChild_Draw,
};

AnimationHeader* D_808DFEC0[] = { &object_horse_link_child_Anim_006D44, &object_horse_link_child_Anim_007468 };

AnimationHeader* D_808DFEC8[] = { &object_horse_link_child_Anim_007D50, &object_horse_link_child_Anim_0043AC,
                                  &object_horse_link_child_Anim_002F98 };

static ColliderJntSphElementInit sJntSphElementsInit[] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 13, { { 0, 0, 0 }, 10 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1 | OC2_UNK1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 10, 35, 100, MASS_HEAVY };

s32 D_808DFF10[] = { 1, 19 };

f32 D_808DFF18[] = { 1.0f, 1.0f, 1.5f, 1.5f, 1.5f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_STOP),
};

EnHorseLinkChildUnkFunc D_808DFF30[] = {
    func_808DEA0C, func_808DED40, func_808DEB14, func_808DF194, func_808DF838, func_808DF620,
};

TexturePtr D_808DFF48[] = { object_horse_link_child_Tex_001D28, object_horse_link_child_Tex_001928,
                            object_horse_link_child_Tex_001B28 };

s8 D_808DFF54[] = { 0, 1, 2, 1 };

void func_808DE5C0(EnHorseLinkChild* this) {
    if ((D_808DFF10[this->unk_1E8] < this->skin.skelAnime.curFrame) &&
        ((this->unk_1E8 != 0) || !(D_808DFF10[1] < this->skin.skelAnime.curFrame))) {
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_WALK);
        this->unk_1E8++;
        if (this->unk_1E8 >= 2) {
            this->unk_1E8 = 0;
        }
    }
}

void func_808DE660(EnHorseLinkChild* this) {
    if (this->unk_148 == 2) {
        func_808DE5C0(this);
    } else if (this->skin.skelAnime.curFrame == 0.0f) {
        if ((this->unk_148 == 3) || (this->unk_148 == 4)) {
            Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_RUN);
        } else if (this->unk_148 == 1) {
            if (Rand_ZeroOne() > 0.5f) {
                Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_GROAN);
            } else {
                Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
            }
        }
    }
}

f32 func_808DE728(EnHorseLinkChild* this) {
    f32 phi_fv1;

    if (this->unk_148 == 2) {
        phi_fv1 = D_808DFF18[this->unk_148] * this->actor.speed * (1.0f / 2.0f);
    } else if (this->unk_148 == 3) {
        phi_fv1 = D_808DFF18[this->unk_148] * this->actor.speed * (1.0f / 3.0f);
    } else if (this->unk_148 == 4) {
        phi_fv1 = D_808DFF18[this->unk_148] * this->actor.speed * (1.0f / 5.0f);
    } else {
        phi_fv1 = D_808DFF18[this->unk_148];
    }
    return phi_fv1;
}

void EnHorseLinkChild_Init(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Actor_SetScale(&this->actor, 0.00648f);

    this->actor.gravity = -3.5f;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawHorse, 20.0f);

    this->unk_144 = 1;
    this->actor.speed = 0.0f;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 70.0f;

    Skin_Init(&play->state, &this->skin, &object_horse_link_child_Skel_00A480, &object_horse_link_child_Anim_002F98);
    this->unk_148 = 0;
    Animation_PlayOnce(&this->skin.skelAnime, D_808DFEC0[0]);

    Collider_InitCylinder(play, &this->colldierCylinder);
    Collider_InitJntSph(play, &this->colliderJntSph);
    Collider_SetJntSph(play, &this->colliderJntSph, &this->actor, &sJntSphInit, this->colliderJntSphElements);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);

    this->unk_1E8 = 0;
    this->unk_1E4 = 0;

    if (gSaveContext.sceneLayer >= 4) {
        func_808DEFE8(this);
    } else {
        func_808DEFE8(this);
    }

    this->actor.home.rot.z = this->actor.world.rot.z = this->actor.shape.rot.z = 0;
}

void EnHorseLinkChild_Destroy(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS;

    Skin_Free(&play->state, &this->skin);
    Collider_DestroyCylinder(play, &this->colldierCylinder);
    Collider_DestroyJntSph(play, &this->colliderJntSph);
}

void func_808DE9A8(EnHorseLinkChild* this) {
    this->unk_144 = 0;
    this->unk_148++;
    if (this->unk_148 >= ARRAY_COUNT(D_808DFF18)) {
        this->unk_148 = 0;
    }
    Animation_PlayOnce(&this->skin.skelAnime, D_808DFEC0[this->unk_148]);
    this->skin.skelAnime.playSpeed = func_808DE728(this);
}

void func_808DEA0C(EnHorseLinkChild* this, PlayState* play) {
    this->actor.speed = 0.0f;
    if (SkelAnime_Update(&this->skin.skelAnime)) {
        func_808DE9A8(this);
    }
}

void func_808DEA54(EnHorseLinkChild* this, s32 arg1) {
    this->unk_144 = 2;
    this->actor.speed = 0.0f;

    if ((arg1 != 0) && (arg1 != 1)) {
        arg1 = 0;
    }

    if (arg1 != this->unk_148) {
        this->unk_148 = arg1;
        Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                         Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
    }
}

void func_808DEB14(EnHorseLinkChild* this, PlayState* play) {
    f32 sp44 = Actor_WorldDistXZToActor(&this->actor, &GET_PLAYER(play)->actor);
    s32 phi_v0;

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if ((sp44 < 1000.0f) && (sp44 > 70.0f)) {
            func_808DECA0(this);
            return;
        }

        if (this->unk_148 == 1) {
            phi_v0 = 0;
        } else {
            phi_v0 = 1;
        }

        if (phi_v0 != this->unk_148) {
            this->unk_148 = phi_v0;
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                             Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                             Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, 0.0f);
        }
    }
}

void func_808DECA0(EnHorseLinkChild* this) {
    this->unk_144 = 1;
    this->unk_148 = 0;
    this->actor.speed = 0.0f;
    Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                     Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
}

void func_808DED40(EnHorseLinkChild* this, PlayState* play) {
    f32 temp_fv0;
    s16 temp_a0;
    s32 phi_v0;

    if ((this->unk_148 == 4) || (this->unk_148 == 3) || (this->unk_148 == 2)) {
        temp_a0 = Actor_WorldYawTowardActor(&this->actor, &GET_PLAYER(play)->actor) - this->actor.world.rot.y;
        if (temp_a0 > 0x12C) {
            this->actor.world.rot.y += 0x12C;
        } else if (temp_a0 < -0x12C) {
            this->actor.world.rot.y -= 0x12C;
        } else {
            this->actor.world.rot.y += temp_a0;
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        temp_fv0 = Actor_WorldDistXZToActor(&this->actor, &GET_PLAYER(play)->actor);
        if (temp_fv0 > 1000.0f) {
            func_808DEA54(this, 0);
            return;
        }

        if ((temp_fv0 < 1000.0f) && (temp_fv0 >= 300.0f)) {
            phi_v0 = 4;
            this->actor.speed = 6.0f;
        } else if ((temp_fv0 < 300.0f) && (temp_fv0 >= 150.0f)) {
            phi_v0 = 3;
            this->actor.speed = 4.0f;
        } else if ((temp_fv0 < 150.0f) && (temp_fv0 >= 70.0f)) {
            phi_v0 = 2;
            this->unk_1E8 = 0;
            this->actor.speed = 2.0f;
        } else {
            func_808DEA54(this, 1);
            return;
        }

        if (phi_v0 != this->unk_148) {
            this->unk_148 = phi_v0;
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                             Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                             Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, 0.0f);
        }
    }
}

void func_808DEFE8(EnHorseLinkChild* this) {
    this->unk_144 = 3;
    this->unk_148 = 0;
    this->actor.speed = 0.0f;
    Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                     Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
}

void func_808DF088(EnHorseLinkChild* this, PlayState* play) {
    if ((this->unk_148 == 4) || (this->unk_148 == 3) || (this->unk_148 == 2)) {
        Player* player = GET_PLAYER(play);
        s16 sp32;
        s32 phi_v0;
        s32 pad;

        if (Math3D_Distance(&player->actor.world.pos, &this->actor.home.pos) < 250.0f) {
            sp32 = player->actor.shape.rot.y;
            if (Actor_WorldYawTowardActor(&this->actor, &player->actor) > 0) {
                phi_v0 = 1;
            } else {
                phi_v0 = -1;
            }
            sp32 += (phi_v0 << 0xE);
        } else {
            sp32 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos) - this->actor.world.rot.y;
        }

        if (sp32 > 0x12C) {
            this->actor.world.rot.y += 0x12C;
        } else if (sp32 < -0x12C) {
            this->actor.world.rot.y += -0x12C;
        } else {
            this->actor.world.rot.y += sp32;
        }

        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
}

void func_808DF194(EnHorseLinkChild* this, PlayState* play) {
    Player* player;
    f32 sp50;
    s32 sp4C;
    s32 sp48;

    func_808DF088(this, play);

    player = GET_PLAYER(play);
    sp50 = Actor_WorldDistXZToActor(&this->actor, &player->actor);
    sp48 = this->unk_148;
    sp4C = SkelAnime_Update(&this->skin.skelAnime);

    if ((sp4C != 0) || (this->unk_148 == 1) || (this->unk_148 == 0)) {
        // The carry-over of this flag from OoT was not done correctly
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_ENTERED_ZORA_HALL)) {
            f32 sp44 = Math3D_Distance(&this->actor.world.pos, &this->actor.home.pos);
            s32 pad;

            if (Math3D_Distance(&player->actor.world.pos, &this->actor.home.pos) > 250.0f) {
                if (sp44 >= 300.0f) {
                    sp48 = 4;
                    this->actor.speed = 6.0f;
                } else if ((sp44 < 300.0f) && (sp44 >= 150.0f)) {
                    sp48 = 3;
                    this->actor.speed = 4.0f;
                } else if ((sp44 < 150.0f) && (sp44 >= 70.0f)) {
                    sp48 = 2;
                    this->unk_1E8 = 0;
                    this->actor.speed = 2.0f;
                } else {
                    this->actor.speed = 0.0f;
                    if (this->unk_148 == 0) {
                        sp48 = (sp4C == 1) ? 1 : 0;
                    } else {
                        sp48 = (sp4C == 1) ? 0 : 1;
                    }
                }
            } else if (sp50 < 200.0f) {
                sp48 = 4;
                this->actor.speed = 6.0f;
            } else if (sp50 < 300.0f) {
                sp48 = 3;
                this->actor.speed = 4.0f;
            } else if (sp50 < 400.0f) {
                sp48 = 2;
                this->unk_1E8 = 0;
                this->actor.speed = 2.0f;
            } else {
                this->actor.speed = 0.0f;
                if (this->unk_148 == 0) {
                    sp48 = (sp4C == 1) ? 1 : 0;
                } else {
                    sp48 = (sp4C == 1) ? 0 : 1;
                }
            }
        } else {
            this->actor.speed = 0.0f;
            if (this->unk_148 == 0) {
                sp48 = (sp4C == 1) ? 1 : 0;
            } else {
                sp48 = (sp4C == 1) ? 0 : 1;
            }
        }
    }

    if ((sp48 != this->unk_148) || (sp4C == 1)) {
        this->unk_148 = sp48;
        Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                         Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
    } else {
        Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this),
                         this->skin.skelAnime.curFrame, Animation_GetLastFrame(D_808DFEC0[this->unk_148]),
                         ANIMMODE_ONCE, 0.0f);
    }
}

void func_808DF560(EnHorseLinkChild* this) {
    this->unk_144 = 5;

    if (Rand_ZeroOne() > 0.5f) {
        this->unk_148 = 0;
    } else {
        this->unk_148 = 1;
    }

    gHorsePlayedEponasSong = false;
    Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                     Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, 0.0f);
}

void func_808DF620(EnHorseLinkChild* this, PlayState* play) {
    s16 sp36;

    if (gHorsePlayedEponasSong) {
        gHorsePlayedEponasSong = false;
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_EV_KID_HORSE_NEIGH);
        func_808DF788(this);
        return;
    }

    this->actor.speed = 0.0f;
    sp36 = Actor_WorldYawTowardActor(&this->actor, &GET_PLAYER(play)->actor) - this->actor.world.rot.y;

    if ((Math_CosS(sp36) < 0.7071f) && (this->unk_148 == 2)) {
        Horse_RotateToPoint(&this->actor, &GET_PLAYER(play)->actor.world.pos, 0x12C);
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (Math_CosS(sp36) < 0.0f) {
            this->unk_148 = 2;
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], D_808DFF18[this->unk_148], 0.0f,
                             Animation_GetLastFrame(D_808DFEC8[0]), ANIMMODE_ONCE, -5.0f);
        } else {
            func_808DF560(this);
        }
    }
}

void func_808DF788(EnHorseLinkChild* this) {
    this->unk_1DC = 0;
    this->unk_144 = 4;
    this->unk_148 = 2;
    this->unk_1E0 = 0;
    this->actor.speed = 2.0f;
    Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                     Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
}

void func_808DF838(EnHorseLinkChild* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 phi_fv0;
    s32 phi_v0;

    this->unk_1DC++;
    if (this->unk_1DC > 300) {
        this->unk_1E0 = 1;
    }

    if ((this->unk_148 == 4) || (this->unk_148 == 3) || (this->unk_148 == 2)) {
        if (this->unk_1E0 == 0) {
            Horse_RotateToPoint(&this->actor, &player->actor.world.pos, 0x12C);
        } else {
            Horse_RotateToPoint(&this->actor, &this->actor.home.pos, 0x12C);
        }
    }

    if (SkelAnime_Update(&this->skin.skelAnime)) {
        if (this->unk_1E0 == 0) {
            phi_fv0 = Actor_WorldDistXZToActor(&this->actor, &GET_PLAYER(play)->actor);
        } else {
            phi_fv0 = Math3D_Distance(&this->actor.world.pos, &this->actor.home.pos);
        }

        if (this->unk_1E0 == 0) {
            if (phi_fv0 >= 300.0f) {
                phi_v0 = 4;
                this->actor.speed = 6.0f;
            } else if (phi_fv0 >= 150.0f) {
                phi_v0 = 3;
                this->actor.speed = 4.0f;
            } else {
                phi_v0 = 2;
                this->unk_1E8 = 0;
                this->actor.speed = 2.0f;
            }
        } else if (phi_fv0 >= 300.0f) {
            phi_v0 = 4;
            this->actor.speed = 6.0f;
        } else if (phi_fv0 >= 150.0f) {
            phi_v0 = 3;
            this->actor.speed = 4.0f;
        } else if (phi_fv0 >= 70.0f) {
            phi_v0 = 2;
            this->unk_1E8 = 0;
            this->actor.speed = 2.0f;
        } else {
            func_808DF560(this);
            return;
        }

        if (phi_v0 != this->unk_148) {
            this->unk_148 = phi_v0;
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                             Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, -5.0f);
        } else {
            Animation_Change(&this->skin.skelAnime, D_808DFEC0[this->unk_148], func_808DE728(this), 0.0f,
                             Animation_GetLastFrame(D_808DFEC0[this->unk_148]), ANIMMODE_ONCE, 0.0f);
        }
    }
}

void EnHorseLinkChild_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnHorseLinkChild* this = THIS;

    D_808DFF30[this->unk_144](this, play);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 55.0f, 100.0f,
                            UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4 | UPDBGCHECKINFO_FLAG_8 |
                                UPDBGCHECKINFO_FLAG_10);

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 70.0f;

    if ((Rand_ZeroOne() < 0.025f) && (this->unk_1E4 == 0)) {
        this->unk_1E4++;
    } else if (this->unk_1E4 > 0) {
        this->unk_1E4++;
        if (this->unk_1E4 >= 4) {
            this->unk_1E4 = 0;
        }
    }

    Collider_UpdateCylinder(&this->actor, &this->colldierCylinder);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colldierCylinder.base);

    func_808DE660(this);
}

void EnHorseLinkChild_PostSkinDraw(Actor* thisx, PlayState* play, Skin* skin) {
    Vec3f sp4C;
    Vec3f sp40;
    EnHorseLinkChild* this = THIS;
    s32 i;

    for (i = 0; i < this->colliderJntSph.count; i++) {
        sp4C.x = this->colliderJntSph.elements[i].dim.modelSphere.center.x;
        sp4C.y = this->colliderJntSph.elements[i].dim.modelSphere.center.y;
        sp4C.z = this->colliderJntSph.elements[i].dim.modelSphere.center.z;

        Skin_GetLimbPos(skin, this->colliderJntSph.elements[i].dim.limb, &sp4C, &sp40);

        this->colliderJntSph.elements[i].dim.worldSphere.center.x = sp40.x;
        this->colliderJntSph.elements[i].dim.worldSphere.center.y = sp40.y;
        this->colliderJntSph.elements[i].dim.worldSphere.center.z = sp40.z;
        this->colliderJntSph.elements[i].dim.worldSphere.radius =
            this->colliderJntSph.elements[i].dim.modelSphere.radius * this->colliderJntSph.elements[i].dim.scale;
    }

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderJntSph.base);
}

s32 EnHorseLinkChild_OverrideSkinDraw(Actor* thisx, PlayState* play, s32 limbIndex, Skin* skin) {
    EnHorseLinkChild* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (limbIndex == OBJECT_HORSE_LINK_CHILD_LIMB_0D) {
        u8 index = D_808DFF54[this->unk_1E4];

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_808DFF48[index]));
    }

    CLOSE_DISPS(play->state.gfxCtx);

    return true;
}

void EnHorseLinkChild_Draw(Actor* thisx, PlayState* play) {
    EnHorseLinkChild* this = THIS;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    func_80138258(&this->actor, play, &this->skin, EnHorseLinkChild_PostSkinDraw, EnHorseLinkChild_OverrideSkinDraw,
                  true);
}
