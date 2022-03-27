/*
 * File: z_en_kbt.c
 * Overlay: ovl_En_Kbt
 * Description: Zubora
 */

#include "z_en_kbt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnKbt*)thisx)

void EnKbt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKbt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKbt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKbt_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80B33E64(GlobalContext* globalCtx);
s32 func_80B33E8C(GlobalContext* globalCtx);
void func_80B33EF0(EnKbt* this, s16 arg1);
Actor* func_80B3403C(GlobalContext* globalCtx);
void func_80B34314(EnKbt* this, GlobalContext* globalCtx);
void func_80B34598(EnKbt* this, GlobalContext* globalCtx);

const ActorInit En_Kbt_InitVars = {
    ACTOR_EN_KBT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KBT,
    sizeof(EnKbt),
    (ActorFunc)EnKbt_Init,
    (ActorFunc)EnKbt_Destroy,
    (ActorFunc)EnKbt_Update,
    (ActorFunc)EnKbt_Draw,
};

void EnKbt_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKbt* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_kbt_Skel_00DEE8, &object_kbt_Anim_004274, this->jointTable,
                       this->morphTable, OBJECT_KBT_LIMB_MAX);
    this->unk_27C = 0;
    this->actor.home.rot.z = 0;
    this->unk_27E = 4;
    this->unk_27F = 0;
    this->unk_280 = 13;
    this->unk_282 = 13;
    this->unk_278 = func_80B3403C(globalCtx);
    this->unk_284 = 0;
    this->actor.textId = 0;
    if (func_80B33E64(globalCtx)) {
        func_80B33EF0(this, 6);
        this->unk_282 = 11;
        if (func_80B33E8C(globalCtx)) {
            this->actor.textId = 0xC50;
        } else {
            this->actor.textId = 0xC4E;
            this->unk_27C |= 1;
        }
        this->actionFunc = func_80B34314;
    } else {
        func_80B33EF0(this, 0);
        this->unk_282 = 0;
        this->actionFunc = func_80B34598;
    }
    this->actor.flags &= ~ACTOR_FLAG_1;
}

void EnKbt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 func_80B33E64(GlobalContext* globalCtx) {
    return gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 & 1;
}

s32 func_80B33E8C(GlobalContext* globalCtx) {
    if ((CURRENT_DAY == 3) ||
        ((CURRENT_DAY == 2) && (gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 & 2))) {
        return true;
    }
    return false;
}

void func_80B33EF0(EnKbt* this, s16 arg1) {
    static AnimationHeader* sAnimations[] = {
        &object_kbt_Anim_000670, &object_kbt_Anim_001674, &object_kbt_Anim_002084, &object_kbt_Anim_000FE8,
        &object_kbt_Anim_001940, &object_kbt_Anim_00E7BC, &object_kbt_Anim_00F0C8, &object_kbt_Anim_002710,
        &object_kbt_Anim_002DE0, &object_kbt_Anim_003414, &object_kbt_Anim_003D24, &object_kbt_Anim_001BF4,
        &object_kbt_Anim_002084,
    };
    u8 sp38[] = {
        ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_LOOP,
        ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE,
    };

    if (arg1 != this->unk_280) {
        if (arg1 >= 12) {
            Animation_Change(&this->skelAnime, sAnimations[arg1], -1.0f,
                             Animation_GetLastFrame(sAnimations[arg1]) - 1.0f, 0.0f, sp38[arg1], -5.0f);
        } else {
            Animation_Change(&this->skelAnime, sAnimations[arg1], 1.0f, 0.0f, Animation_GetLastFrame(sAnimations[arg1]),
                             sp38[arg1], -5.0f);
        }
        this->unk_280 = arg1;
    }
}

Actor* func_80B3403C(GlobalContext* globalCtx) {
    Actor* npc = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if (npc->id == ACTOR_EN_KGY) {
            return npc;
        }
        npc = npc->next;
    }

    return NULL;
}

void func_80B34078(EnKbt* this) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_284 > 0) {
            this->unk_284--;
        } else {
            switch (this->unk_280) {
                case 2:
                    switch (this->unk_282) {
                        case 0:
                            func_80B33EF0(this, 12);
                            break;

                        case 5:
                            this->actor.home.rot.z = 0;
                            break;

                        default:
                            func_80B33EF0(this, 5);
                            break;
                    }
                    break;

                case 12:
                    func_80B33EF0(this, 0);
                    this->actor.home.rot.z = 0;
                    break;

                case 4:
                    func_80B33EF0(this, 1);
                    this->unk_27E = 2;
                    this->actor.home.rot.z = 0;
                    break;
            }
        }
    }
}

void func_80B3415C(EnKbt* this) {
    if (this->unk_27C & 2) {
        if (this->unk_284 > 0) {
            this->unk_284--;
        } else {
            this->unk_27F = 0;
            this->unk_282 = 3;
            this->unk_27C &= ~2;
        }
    }

    switch (this->unk_282) {
        case 0:
            if ((this->unk_280 != 2) && (this->unk_280 != 12)) {
                func_80B33EF0(this, 0);
            }
            break;

        case 1:
            func_80B33EF0(this, 2);
            this->unk_282 = 0;
            break;

        case 2:
            if (this->unk_280 != 12) {
                func_80B33EF0(this, 3);
            }
            break;

        case 3:
            if (this->unk_280 != 1) {
                func_80B33EF0(this, 4);
            }
            break;

        case 10:
            func_80B33EF0(this, 11);
            break;

        case 4:
            func_80B33EF0(this, 2);
            this->unk_282 = 6;
            break;

        case 6:
            if (this->unk_280 != 2) {
                func_80B33EF0(this, 5);
            }
            break;

        case 11:
            func_80B33EF0(this, 6);
            break;

        case 7:
            if (this->unk_280 != 2) {
                func_80B33EF0(this, 7);
            }
            break;

        case 8:
            if (this->unk_280 != 2) {
                func_80B33EF0(this, 8);
            }
            break;

        case 9:
            if (this->unk_280 != 2) {
                func_80B33EF0(this, 9);
            }
            break;

        case 12:
            func_80B33EF0(this, 10);
            break;
    }
}

void func_80B34314(EnKbt* this, GlobalContext* globalCtx) {
    s32 playerForm;

    func_80B34078(this);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B34598;
        Actor_ChangeFocus(&this->actor, globalCtx, this->unk_278);
        this->unk_278->textId = this->actor.textId;
        this->unk_27C &= ~4;
        if (this->actor.textId == 0xC4E) {
            this->unk_27C |= 0x10;
        }
    } else if (this->actor.xzDistToPlayer < 250.0f) {
        if ((this->unk_278 != NULL) && (this->unk_278->xzDistToPlayer < 250.0f)) {
            if (this->unk_27C & 4) {
                playerForm = gSaveContext.save.playerForm;
                if (((playerForm ^ 0) != PLAYER_FORM_HUMAN) || ((CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_KOKIRI) &&
                                                                (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_RAZOR) &&
                                                                (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_GILDED))) {
                    this->actor.textId = 0xC38;
                } else if (CURRENT_DAY == 3) {
                    this->actor.textId = 0xC39;
                } else if (this->unk_27C & 8) {
                    this->actor.textId = 0xC3E;
                } else {
                    this->actor.textId = 0xC3A;
                }
            }

            if (this->actor.textId != 0xC37) {
                if (((this->actor.textId == 0xC4E) || (this->actor.textId == 0xC4F) || (this->actor.textId == 0xC50)) &&
                    (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN)) {
                    this->actor.textId = 0xC37;
                }
            } else if (gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) {
                if (func_80B33E8C(globalCtx)) {
                    this->actor.textId = 0xC50;
                } else {
                    this->actor.textId = 0xC4E;
                }
            }
            func_800B8614(&this->actor, globalCtx, 260.0f);
        }
    }
    func_80B3415C(this);
}

void func_80B34574(EnKbt* this) {
    this->unk_27E = 0;
    this->unk_27F = 0;
    this->unk_282 = 6;
    this->actionFunc = func_80B34314;
}

void func_80B34598(EnKbt* this, GlobalContext* globalCtx) {
    func_80B34078(this);

    switch (this->actor.textId) {
        case 0x1:
            this->unk_27E = 4;
            this->unk_27F = 0;
            this->unk_282 = 0;
            break;

        case 0x2:
            func_80B34574(this);
            this->actor.textId = 0xC3E;
            this->unk_27C |= 0x4;
            this->unk_27C |= 0x8;
            return;

        case 0x3:
            func_80B34574(this);
            this->actor.textId = 0xC58;
            return;

        case 0x4:
            func_80B34574(this);
            this->actor.textId = 0xC4B;
            return;

        case 0x5:
            this->unk_27E = 4;
            this->unk_27F = 0;
            this->unk_282 = 0;
            func_80B33EF0(this, 12);
            break;

        case 0x6:
            func_80B34574(this);
            this->actor.textId = 0xC3A;
            this->unk_27C |= 4;
            return;

        case 0x7:
            this->unk_27E = 4;
            this->unk_27F = 0;
            this->unk_282 = 11;
            if (func_80B33E8C(globalCtx)) {
                this->actor.textId = 0xC50;
            } else if (this->unk_27C & 0x10) {
                this->actor.textId = 0xC4F;
            } else {
                this->actor.textId = 0xC4E;
            }
            this->actionFunc = func_80B34314;
            return;

        case 0x8:
            func_80B34574(this);
            this->actor.textId = 0xC56;
            return;

        case 0xC1E:
            this->unk_27E = 2;
            this->unk_27F = 1;
            break;

        case 0xC1F:
        case 0xC2E:
            this->unk_27E = 2;
            this->unk_27F = 1;
            this->unk_282 = 1;
            this->unk_284 = 20;
            break;

        case 0xC20:
        case 0xC23:
        case 0xC2F:
            this->unk_27E = 0;
            this->unk_282 = 2;
            break;

        case 0xC21:
        case 0xC29:
            this->unk_284 = 10;
            this->unk_27C |= 2;
            break;

        case 0xC22:
        case 0xC2A:
            this->unk_27F = 1;
            break;

        case 0xC2C:
            this->unk_27E = 0;
            this->unk_27F = 0;
            this->unk_282 = 2;
            break;

        case 0xC31:
            this->unk_27E = 2;
            this->unk_27F = 1;
            this->unk_282 = 4;
            break;

        case 0xC32:
            this->unk_27E = 1;
            this->unk_282 = 7;
            break;

        case 0xC34:
            this->unk_27E = 0;
            this->unk_282 = 8;
            break;

        case 0xC35:
            this->unk_27E = 4;
            this->unk_27F = 0;
            func_80B33EF0(this, 2);
            this->unk_282 = 5;
            break;

        case 0xC36:
            this->unk_27E = 1;
            this->unk_27F = 1;
            func_80B33EF0(this, 7);
            this->unk_282 = 7;
            break;

        case 0xC37:
            func_80B33EF0(this, 10);
            this->unk_27E = 0;
            this->unk_27F = 1;
            break;

        case 0xC38:
        case 0xC39:
            func_80B33EF0(this, 7);
            this->unk_27E = 0;
            this->unk_27F = 1;
            break;

        case 0xC3A:
        case 0xC4D:
        case 0xC58:
            this->unk_27E = 0;
            this->unk_27F = 1;
            this->unk_282 = 8;
            break;

        case 0xC3C:
        case 0xC57:
            this->unk_27E = 1;
            this->unk_282 = 7;
            break;

        case 0xC3D:
            this->unk_27E = 0;
            break;

        case 0xC3E:
            this->unk_27F = 1;
            this->unk_282 = 8;
            break;

        case 0xC3F:
        case 0xC47:
        case 0xC4C:
            this->unk_27E = 1;
            this->unk_27F = 1;
            this->unk_282 = 7;
            break;

        case 0xC40:
            this->unk_27E = 3;
            this->unk_282 = 6;
            break;

        case 0xC45:
        case 0xC4B:
        case 0xC56:
            this->unk_27E = 0;
            this->unk_27F = 1;
            this->unk_282 = 7;
            break;

        case 0xC46:
            this->unk_27E = 1;
            this->unk_27F = 1;
            this->unk_282 = 9;
            break;

        case 0xC48:
            this->unk_27E = 2;
            this->unk_27F = 0;
            this->unk_282 = 10;
            break;

        case 0xC49:
            this->unk_27F = 1;
            break;

        case 0xC4A:
            this->unk_27E = 0;
            this->unk_282 = 7;
            break;

        case 0xC4E:
            this->unk_27E = 1;
            this->unk_27F = 1;
            this->unk_282 = 12;
            break;

        case 0xC4F:
            this->unk_27E = 2;
            this->unk_27F = 1;
            this->unk_282 = 12;
            break;

        case 0xC50:
            this->unk_27E = 0;
            this->unk_27F = 1;
            this->unk_282 = 12;
            break;
    }

    this->actor.textId = 0;
    func_80B3415C(this);
}

void EnKbt_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKbt* this = THIS;

    this->actionFunc(this, globalCtx);
}

s32 EnKbt_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKbt* this = THIS;

    if (!(this->unk_27C & 1) && (limbIndex == OBJECT_KBT_LIMB_0E)) {
        *dList = NULL;
    }
    return false;
}

Vec3f D_80B34B84 = { 500.0f, 500.0f, 0.0f };

void EnKbt_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnKbt* this = THIS;

    if (limbIndex == OBJECT_KBT_LIMB_09) {
        Matrix_MultiplyVector3fByState(&D_80B34B84, &this->actor.focus.pos);
    }
}

TexturePtr D_80B34B90[] = {
    object_kbt_Tex_00A5B8,
    object_kbt_Tex_00ADB8,
};

TexturePtr D_80B34B98[] = {
    object_kbt_Tex_00B5B8, object_kbt_Tex_00BDB8, object_kbt_Tex_00C5B8, object_kbt_Tex_00CDB8, object_kbt_Tex_00D5B8,
};

void EnKbt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKbt* this = THIS;
    Gfx* gfx;
    TexturePtr tex;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gfx = POLY_OPA_DISP;

    tex = Lib_SegmentedToVirtual(D_80B34B98[this->unk_27E]);
    gSPSegment(&gfx[0], 0x08, tex);

    tex = Lib_SegmentedToVirtual(D_80B34B90[this->unk_27F]);
    gSPSegment(&gfx[1], 0x09, tex);

    POLY_OPA_DISP = &gfx[2];

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnKbt_OverrideLimbDraw, EnKbt_PostLimbDraw, &this->actor);
}
