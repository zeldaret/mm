/*
 * File: z_en_kgy.c
 * Overlay: ovl_En_Kgy
 * Description: Blacksmith - Gabora
 */

#include "overlays/actors/ovl_En_Kbt/z_en_kbt.h"
#include "overlays/actors/ovl_Obj_Ice_Poly/z_obj_ice_poly.h"
#include "z_en_kgy.h"
#include "objects/object_kgy/object_kgy.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnKgy*)thisx)

void EnKgy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKgy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKgy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKgy_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnKgy_ChangeAnim(EnKgy* this, s16 arg1, u8 arg2, f32 arg3);
EnKbt* EnKgy_FindZubora(GlobalContext* globalCtx);
ObjIcePoly* EnKgy_FindIceBlock(GlobalContext* globalCtx);
void func_80B40D30(GlobalContext* globalCtx);
s32 func_80B40D64(GlobalContext* globalCtx);
s32 func_80B40DB4(GlobalContext* globalCtx);
void func_80B419B0(EnKgy* this, GlobalContext* globalCtx);
void func_80B41A48(EnKgy* this, GlobalContext* globalCtx);
void func_80B41E18(EnKgy* this, GlobalContext* globalCtx);
void func_80B42508(EnKgy* this, GlobalContext* globalCtx);
void func_80B425A0(EnKgy* this, GlobalContext* globalCtx);
void func_80B42714(EnKgy* this, GlobalContext* globalCtx);
void func_80B42D28(EnKgy* this, GlobalContext* globalCtx);

const ActorInit En_Kgy_InitVars = {
    ACTOR_EN_KGY,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KGY,
    sizeof(EnKgy),
    (ActorFunc)EnKgy_Init,
    (ActorFunc)EnKgy_Destroy,
    (ActorFunc)EnKgy_Update,
    (ActorFunc)EnKgy_Draw,
};

void EnKgy_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnKgy* this = THIS;
    s16 cs;
    s32 i;

    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_kgy_Skel_00F910, &object_kgy_Anim_004B98, this->jointTable,
                       this->morphTable, 23);
    this->unk_2D2 = -1;
    this->unk_29C = 0;
    this->unk_2E4 = 0;
    this->unk_2E2 = -1;
    this->zubora = EnKgy_FindZubora(globalCtx);
    this->iceBlock = EnKgy_FindIceBlock(globalCtx);
    Flags_UnsetSwitch(globalCtx, ENKGY_GET_FE00(&this->actor) + 1);
    if (Flags_GetSwitch(globalCtx, ENKGY_GET_FE00(&this->actor)) || (gSaveContext.save.weekEventReg[33] & 0x80)) {
        Flags_SetSwitch(globalCtx, ENKGY_GET_FE00(&this->actor) + 1);
        globalCtx->envCtx.lightSettingOverride = 1;
        gSaveContext.save.weekEventReg[21] |= 1;
        if (!func_80B40D64(globalCtx)) {
            EnKgy_ChangeAnim(this, 4, 0, 0);
            this->actionFunc = func_80B425A0;
            this->actor.textId = 0xC35;
        } else if (!func_80B40DB4(globalCtx)) {
            EnKgy_ChangeAnim(this, 6, 2, 0);
            this->actionFunc = func_80B419B0;
            this->actor.textId = 0xC4E;
            this->unk_29C |= 1;
            this->unk_2EA = 3;
        } else {
            EnKgy_ChangeAnim(this, 4, 0, 0);
            this->actionFunc = func_80B42714;
            this->actor.textId = 0xC50;
        }
    } else {
        if (gSaveContext.save.weekEventReg[20] & 0x80) {
            EnKgy_ChangeAnim(this, 4, 0, 0);
        } else {
            EnKgy_ChangeAnim(this, 0, 0, 0);
        }
        this->actionFunc = func_80B42D28;
    }

    cs = this->actor.cutscene;
    for (i = 0; i < ARRAY_COUNT(this->unk_2D4); i++) {
        this->unk_2D4[i] = cs;
        if (cs != -1) {
            this->actor.cutscene = cs;
            cs = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    Lights_PointNoGlowSetInfo(&this->lightInfo, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, 255, 64, 64, -1);
    this->lightNode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &this->lightInfo);
    this->unk_300 = -1;
    this->actor.flags &= ~ACTOR_FLAG_1;
}

void EnKgy_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnKgy* this = THIS;

    LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, this->lightNode);
}

void EnKgy_ChangeAnim(EnKgy* this, s16 animIndex, u8 mode, f32 transitionRate) {
    static AnimationHeader* sAnimations[] = {
        &object_kgy_Anim_004B98, &object_kgy_Anim_0008FC, &object_kgy_Anim_00292C, &object_kgy_Anim_0042E4,
        &object_kgy_Anim_0101F0, &object_kgy_Anim_001764, &object_kgy_Anim_003334, &object_kgy_Anim_010B84,
        &object_kgy_Anim_001EA4, &object_kgy_Anim_003D88,
    };

    Animation_Change(&this->skelAnime, sAnimations[animIndex], 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimations[animIndex]), mode, transitionRate);
    this->unk_2D2 = animIndex;
}

void func_80B40BC0(EnKgy* this, s16 arg1) {
    if (arg1 != this->unk_2D2) {
        EnKgy_ChangeAnim(this, arg1, 0, -5.0f);
    }
}

EnKbt* EnKgy_FindZubora(GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actor != NULL) {
        if (actor->id == ACTOR_EN_KBT) {
            return (EnKbt*)actor;
        }
        actor = actor->next;
    }
    return NULL;
}

ObjIcePoly* EnKgy_FindIceBlock(GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (actor != NULL) {
        if (actor->id == ACTOR_OBJ_ICE_POLY) {
            return (ObjIcePoly*)actor;
        }
        actor = actor->next;
    }
    return NULL;
}

void func_80B40C74(GlobalContext* globalCtx) {
    gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 |= 1;
    if (CURRENT_DAY == 1) {
        gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 |= 2;
    } else {
        gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 &= ~2;
    }
}

void func_80B40D00(GlobalContext* globalCtx) {
    gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 |= 4;
}

void func_80B40D30(GlobalContext* globalCtx) {
    gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 &= ~7;
}

s32 func_80B40D64(GlobalContext* globalCtx) {
    return gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 & 1;
}

s32 func_80B40D8C(GlobalContext* globalCtx) {
    return gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 & 4;
}

s32 func_80B40DB4(GlobalContext* globalCtx) {
    if ((CURRENT_DAY == 3) ||
        ((CURRENT_DAY == 2) && (gSaveContext.save.permanentSceneFlags[globalCtx->sceneNum].unk_14 & 2))) {
        return true;
    }
    return false;
}

void func_80B40E18(EnKgy* this, u16 textId) {
    if (this->zubora != NULL) {
        this->zubora->actor.textId = textId;
    }
}

void func_80B40E38(EnKgy* this) {
    if (this->zubora != NULL) {
        this->zubora->actor.home.rot.z = 1;
    }
}

s32 func_80B40E54(EnKgy* this) {
    if (this->zubora != NULL) {
        return this->zubora->actor.home.rot.z;
    }
    return 0;
}

void func_80B40E74(EnKgy* this, GlobalContext* globalCtx, u16 textId) {
    func_80151938(globalCtx, textId);
    this->actor.textId = textId;
    func_80B40E18(this, this->actor.textId);
}

void func_80B40EBC(EnKgy* this, GlobalContext* globalCtx, u16 arg2) {
    func_80B40E74(this, globalCtx, ++arg2);
}

void func_80B40EE8(EnKgy* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->unk_2E4 > 0) {
        this->unk_2E4--;
        if ((this->unk_2E4 == 0) && (this->unk_2E2 >= 0)) {
            if (this->unk_2E2 == 3) {
                EnKgy_ChangeAnim(this, 3, 2, -5.0f);
            } else {
                func_80B40BC0(this, this->unk_2E2);
            }
            this->unk_2E2 = -1;
        }
    }

    if ((this->unk_2E0 != -1) && (ActorCutscene_GetCurrentIndex() != this->unk_2D4[this->unk_2E0])) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->unk_2D4[this->unk_2E0]);
        } else if (ActorCutscene_GetCanPlayNext(this->unk_2D4[this->unk_2E0])) {
            ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D4[this->unk_2E0], &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_2D4[this->unk_2E0]);
        }
    }

    if (this->unk_29C & 2) {
        Vec3f sp38;
        f32 sp34;
        f32 temp_f0;

        Actor_GetProjectedPos(globalCtx, &this->unk_2B4, &sp38, &sp34);
        temp_f0 = sp38.x * sp34;
        if (this->unk_2E6 > 0) {
            this->unk_2E6--;
        }

        if (((temp_f0 < 0.15f) && (temp_f0 > -0.15f)) || (this->unk_2E6 == 0)) {
            func_80151938(globalCtx, this->actor.textId);
            this->unk_29C &= ~0x2;
            func_80B40E18(this, this->actor.textId);

            switch (this->actor.textId) {
                case 0xC22:
                    this->unk_2E4 = 20;
                    this->unk_2E2 = 3;
                    break;

                case 0xC43:
                    if (func_80B40D64(globalCtx)) {
                        func_80B40BC0(this, 7);
                    } else {
                        func_80B40BC0(this, 1);
                    }
                    this->unk_2E4 = 30;
                    this->actionFunc = func_80B41A48;
                    break;

                case 0xC52:
                case 0xC54:
                    func_80B40BC0(this, 1);
                    break;
            }
        }
    }

    if (this->unk_29C & 4) {
        if (this->unk_2E8 > 0) {
            this->unk_2E8--;
        } else {
            this->unk_2E8 = 0;
        }
        if (this->unk_2E8 == 0) {
            if ((this->actor.textId == 0xC1D) || (this->actor.textId == 0xC2D)) {
                this->unk_2E4 = 20;
                this->unk_2E2 = 3;
                func_80B40EBC(this, globalCtx, this->actor.textId);
            } else {
                func_80B40EBC(this, globalCtx, this->actor.textId);
            }
            this->unk_29C &= ~4;
        }
    }
}

void func_80B411DC(EnKgy* this, GlobalContext* globalCtx, s32 arg2) {
    Player* player = GET_PLAYER(globalCtx);

    switch (arg2) {
        case 0:
            this->unk_2B4 = this->unk_2A8;
            this->actor.focus.pos = this->unk_2A8;
            this->unk_2E0 = 0;
            break;

        case 1:
            if (this->zubora != NULL) {
                this->unk_2B4 = this->zubora->actor.focus.pos;
                this->actor.focus.pos = this->zubora->actor.focus.pos;
            }
            this->unk_2E0 = 1;
            break;

        case 2:
            if (this->iceBlock != NULL) {
                this->unk_2B4 = this->iceBlock->actor.world.pos;
                this->actor.focus.pos = this->iceBlock->actor.focus.pos;
            }
            this->unk_2E0 = 2;
            break;

        case 3:
            this->unk_2B4 = player->actor.world.pos;
            if (this->zubora != NULL) {
                this->actor.focus.pos = this->zubora->actor.focus.pos;
            }
            this->unk_2E0 = 3;
            break;

        case 4:
            if (this->zubora != NULL) {
                this->unk_2B4 = this->zubora->actor.focus.pos;
                this->actor.focus.pos = this->zubora->actor.focus.pos;
            }
            this->unk_2E0 = 4;
            break;
    }
}

void func_80B41368(EnKgy* this, GlobalContext* globalCtx, s32 arg2) {
    ActorCutscene_Stop(this->unk_2D4[this->unk_2E0]);
    func_80B411DC(this, globalCtx, arg2);
    this->unk_2E6 = 20;
    this->unk_29C |= 2;
}

void func_80B413C8(EnKgy* this) {
    Vec3f sp1C = this->unk_2A8;

    this->unk_2B4 = sp1C;
    this->actor.focus.pos = sp1C;
    ActorCutscene_Stop(this->unk_2D4[this->unk_2E0]);
    this->unk_2E0 = -1;
    this->unk_2E6 = 0;
    this->unk_29C &= ~2;
}

s32 func_80B41460(void) {
    if ((gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) ||
        ((CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_KOKIRI) && (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_RAZOR) &&
         (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_GILDED))) {
        return 0xC38;
    }

    if (CURRENT_DAY == 3) {
        return 0xC39;
    }

    return 0xC3A;
}

s32 func_80B41528(GlobalContext* globalCtx) {
    if (CUR_FORM_EQUIP(EQUIP_SLOT_B) == ITEM_SWORD_GILDED) {
        return 0xC4C;
    }

    if (CUR_FORM_EQUIP(EQUIP_SLOT_B) == ITEM_SWORD_RAZOR) {
        return 0xC45;
    }

    return 0xC3B;
}

void func_80B415A8(GlobalContext* globalCtx, Vec3f* arg1) {
    static EffectShieldParticleInit D_80B43298 = {
        16,
        { 0, 0, 0 },
        { 0, 200, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 128, 255 },
        { 255, 255, 0, 255 },
        { 255, 64, 0, 200 },
        { 255, 0, 0, 255 },
        2.0f,
        15.0f,
        10.0f,
        4,
        { 0, 0, 0, { 0, 128, 255 }, 0, 300 },
        0,
    };
    s32 effectIndex;

    D_80B43298.position.x = arg1->x;
    D_80B43298.position.y = arg1->y;
    D_80B43298.position.z = arg1->z;
    D_80B43298.lightPoint.x = D_80B43298.position.x;
    D_80B43298.lightPoint.y = D_80B43298.position.y;
    D_80B43298.lightPoint.z = D_80B43298.position.z;

    Effect_Add(globalCtx, &effectIndex, EFFECT_SHIELD_PARTICLE, 0, 1, &D_80B43298);
}

void func_80B4163C(EnKgy* this, GlobalContext* globalCtx) {
    this->actor.focus.pos = this->unk_2A8;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_2D2 == 6) {
            if (this->unk_2EA > 0) {
                EnKgy_ChangeAnim(this, 6, 2, 0.0f);
                this->unk_2EA--;
            } else {
                EnKgy_ChangeAnim(this, 9, 2, -5.0f);
                this->unk_2EA = (s32)Rand_ZeroFloat(3.0f) + 2;
            }
        } else {
            EnKgy_ChangeAnim(this, 6, 2, -5.0f);
        }
        SkelAnime_Update(&this->skelAnime);
    }

    switch ((s32)this->skelAnime.curFrame) {
        case 1:
        case 7:
        case 13:
        case 19:
        case 25:
            func_80B415A8(globalCtx, &this->unk_2C0);
            this->lightInfo.params.point.x = this->unk_2C0.x;
            this->lightInfo.params.point.y = this->unk_2C0.y;
            this->lightInfo.params.point.z = this->unk_2C0.z;
            this->unk_300 = 200;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SWORD_FORGE);
            break;
    }

    this->lightInfo.params.point.radius = this->unk_300;
    if (this->unk_300 > 0) {
        this->unk_300 -= 50;
    }
}

void func_80B417B8(EnKgy* this, GlobalContext* globalCtx) {
    func_80B4163C(this, globalCtx);
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80B413C8(this);
        this->actor.flags &= ~ACTOR_FLAG_100;
        this->actionFunc = func_80B419B0;
        func_80B40E18(this, 7);
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B41858(EnKgy* this, GlobalContext* globalCtx) {
    func_80B4163C(this, globalCtx);
    if (ActorCutscene_GetCanPlayNext(this->unk_2D4[5])) {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2D4[5], &this->actor);
        this->actionFunc = func_80B419B0;
        func_80B40E18(this, 7);
    } else {
        ActorCutscene_SetIntentToPlay(this->unk_2D4[5]);
    }
}

void func_80B418C4(EnKgy* this, GlobalContext* globalCtx) {
    func_80B4163C(this, globalCtx);
    if ((this->unk_2E4 <= 0) && !(this->unk_29C & 2) && (func_80B40E54(this) == 0) &&
        (Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx) &&
        ((globalCtx->msgCtx.currentTextId == 0xC4E) || (globalCtx->msgCtx.currentTextId == 0xC4F))) {
        func_801477B4(globalCtx);
        this->actor.textId = 0xC4F;
        func_80B413C8(this);
        ActorCutscene_SetIntentToPlay(this->unk_2D4[5]);
        this->actionFunc = func_80B41858;
        this->actor.flags &= ~ACTOR_FLAG_100;
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B419B0(EnKgy* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    func_80B4163C(this, globalCtx);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) || (&this->actor == player->targetActor)) {
        func_80B411DC(this, globalCtx, 4);
        func_80B40E18(this, this->actor.textId);
        if (this->actor.textId == 0xC37) {
            this->actionFunc = func_80B417B8;
        } else {
            this->actionFunc = func_80B418C4;
        }
    }
}

void func_80B41A48(EnKgy* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_2E4 > 0) {
        this->unk_2E4--;
    } else {
        globalCtx->nextEntranceIndex = globalCtx->setupExitList[ENKGY_GET_1F(&this->actor)];
        globalCtx->sceneLoadFlag = 20;
    }
}

void func_80B41ACC(EnKgy* this, GlobalContext* globalCtx) {
    s32 itemActionParam;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    if (Message_GetState(&globalCtx->msgCtx) == 0x10) {
        itemActionParam = func_80123810(globalCtx);
        if (itemActionParam != PLAYER_AP_NONE) {
            this->actionFunc = func_80B41E18;
        }

        if (itemActionParam > PLAYER_AP_NONE) {
            func_801477B4(globalCtx);
            if (itemActionParam == PLAYER_AP_BOTTLE_GOLD_DUST) {
                if (this->unk_29C & 0x10) {
                    this->actor.textId = 0xC55;
                    player->actor.textId = 0xC55;
                } else {
                    this->actor.textId = 0xC46;
                    player->actor.textId = 0xC46;
                    func_80B40D00(globalCtx);
                }
            } else if (this->unk_29C & 0x10) {
                this->actor.textId = 0xC57;
                player->actor.textId = 0xC57;
            } else {
                this->actor.textId = 0xC47;
                player->actor.textId = 0xC47;
            }
            this->unk_29C |= 8;
        } else if (itemActionParam < PLAYER_AP_NONE) {
            if (this->unk_29C & 0x10) {
                this->actor.textId = 0xC57;
            } else {
                this->actor.textId = 0xC47;
            }
            player->actor.textId = 0;
            globalCtx->msgCtx.unk11F10 = 0;
            func_80B41368(this, globalCtx, 4);
        }
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B41C30(EnKgy* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (&this->actor != player->targetActor) {
        this->actionFunc = func_80B42508;
    }
}

void func_80B41C54(EnKgy* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        this->actionFunc = func_80B41C30;
        this->actor.flags &= ~ACTOR_FLAG_100;
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B41CBC(EnKgy* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80B40E18(this, this->actor.textId);
        this->actionFunc = func_80B41E18;
        func_80B411DC(this, globalCtx, 4);
    } else {
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, EXCH_ITEM_MINUS1);
    }
}

void func_80B41D64(EnKgy* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actionFunc = func_80B41CBC;
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, EXCH_ITEM_MINUS1);
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->unk_2EA, 2000.0f, 1000.0f);
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B41E18(EnKgy* this, GlobalContext* globalCtx) {
    u16 temp;
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if (SkelAnime_Update(&this->skelAnime) && (this->unk_2D2 == 3)) {
        func_80B40BC0(this, 4);
    }

    if ((this->unk_2E4 <= 0) && !(this->unk_29C & 2) && func_80B40E54(this) == 0) {
        switch (Message_GetState(&globalCtx->msgCtx)) {
            case 4:
                if (Message_ShouldAdvance(globalCtx)) {
                    temp = globalCtx->msgCtx.currentTextId;

                    switch (temp) {
                        case 0xC3B:
                            switch (globalCtx->msgCtx.choiceIndex) {
                                case 0:
                                    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
                                        play_sound(NA_SE_SY_ERROR);
                                        func_80B40E74(this, globalCtx, 0xC3F);
                                    } else {
                                        func_8019F208();
                                        func_80B40E74(this, globalCtx, 0xC42);
                                        func_801159EC(-globalCtx->msgCtx.unk1206C);
                                    }
                                    break;

                                case 1:
                                    func_8019F230();
                                    func_80B40EBC(this, globalCtx, temp);
                                    break;
                            }
                            break;

                        case 0xC3E:
                            switch (globalCtx->msgCtx.choiceIndex) {
                                case 0:
                                    func_8019F208();
                                    func_80B40E74(this, globalCtx, func_80B41460());
                                    break;

                                case 1:
                                    func_8019F230();
                                    func_80B40E74(this, globalCtx, 0xC3C);
                                    break;
                            }
                            break;
                    }
                }
                break;

            case 5:
                if (Message_ShouldAdvance(globalCtx)) {
                    temp = globalCtx->msgCtx.currentTextId;

                    switch (temp) {
                        case 0xC35:
                            globalCtx->msgCtx.unk11F10 = 0;
                            this->actor.textId = temp;
                            this->unk_29C |= 4;
                            this->unk_2E8 = 3;
                            func_80B40E38(this);
                            break;

                        case 0xC36:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 4);
                            this->actor.textId = func_80B41460();
                            break;

                        case 0xC38:
                        case 0xC39:
                        case 0xC52:
                        case 0xC54:
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80B425A0;
                            func_80B413C8(this);
                            func_80B40E18(this, 5);
                            func_80B40BC0(this, 4);
                            this->actor.textId = 0xC35;
                            break;

                        case 0xC3A:
                            func_80B40E74(this, globalCtx, func_80B41528(globalCtx));
                            func_80B40BC0(this, 4);
                            break;

                        case 0xC3C:
                        case 0xC3F:
                        case 0xC4C:
                            func_80B40EBC(this, globalCtx, temp);
                            break;

                        case 0xC3D:
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80B41C54;
                            this->actor.textId = 0xC3E;
                            func_80B413C8(this);
                            func_80B40E18(this, 2);
                            break;

                        case 0xC40:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 0);
                            this->actor.textId = 0xC43;
                            break;

                        case 0xC42:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 0);
                            this->actor.textId = 0xC43;
                            CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_NONE;
                            SET_EQUIP_VALUE(EQUIP_SWORD, 0);
                            func_80112B40(globalCtx, 0);
                            func_80B40C74(globalCtx);
                            break;

                        case 0xC4D:
                        case 0xC58:
                            this->unk_29C |= 0x10;

                        case 0xC45:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 3);
                            this->actor.textId = 0xFF;
                            this->actionFunc = func_80B41ACC;
                            break;

                        case 0xC57:
                            this->unk_29C &= ~0x8;
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80B41C54;
                            this->actor.textId = 0xC58;
                            func_80B413C8(this);
                            func_80B40E18(this, 3);
                            break;

                        case 0xC46:
                        case 0xC55:
                            func_80123D50(globalCtx, GET_PLAYER(globalCtx), ITEM_BOTTLE, PLAYER_AP_BOTTLE);
                            player->exchangeItemId = EXCH_ITEM_NONE;
                            this->unk_29C &= ~0x8;
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 4);
                            if (this->unk_29C & 0x10) {
                                this->actor.textId = 0xC56;
                                func_801159EC(globalCtx->msgCtx.unk1206C);
                            } else {
                                this->actor.textId = 0xC42;
                            }
                            break;

                        case 0xC47:
                            func_80B40BC0(this, 1);
                            if (this->unk_29C & 8) {
                                player->exchangeItemId = EXCH_ITEM_NONE;
                                this->unk_29C &= ~8;
                            }
                            func_80B40EBC(this, globalCtx, temp);
                            break;

                        case 0xC48:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 0);
                            this->actor.textId = temp + 1;
                            break;

                        case 0xC49:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 4);
                            this->actor.textId = temp + 1;
                            break;

                        case 0xC4A:
                        case 0xC4B:
                            func_80B40BC0(this, 4);
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80B41C54;
                            this->actor.textId = 0xC4B;
                            func_80B413C8(this);
                            func_80B40E18(this, 4);
                            break;

                        case 0xC50:
                            if (func_80B40D8C(globalCtx)) {
                                this->unk_2EA = 57;
                                this->actor.textId = 0xC53;
                            } else {
                                this->unk_2EA = 56;
                                this->actor.textId = 0xC51;
                            }
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80B41D64;
                            func_80B413C8(this);
                            Actor_PickUp(&this->actor, globalCtx, this->unk_2EA, 2000.0f, 1000.0f);
                            break;

                        case 0xC51:
                        case 0xC53:
                            globalCtx->msgCtx.unk11F10 = 0;
                            func_80B41368(this, globalCtx, 0);
                            this->actor.textId = temp + 1;
                            func_80B40D30(globalCtx);
                            break;

                        case 0xC56:
                            func_801477B4(globalCtx);
                            this->actionFunc = func_80B41C54;
                            this->actor.textId = 0xC56;
                            func_80B413C8(this);
                            func_80B40E18(this, 8);
                            break;
                    }
                }
                break;
        }
    }

    func_80B40EE8(this, globalCtx);
}

void func_80B42508(EnKgy* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    this->actor.focus.pos = this->unk_2A8;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) || (&this->actor == player->targetActor)) {
        this->actionFunc = func_80B41E18;
        func_80B411DC(this, globalCtx, 4);
        func_80B40E18(this, this->actor.textId);
    }
}

void func_80B425A0(EnKgy* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    this->actor.focus.pos = this->unk_2A8;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B41E18;
        func_80B40BC0(this, 1);
        func_80B411DC(this, globalCtx, 0);
        func_80B40E18(this, this->actor.textId);
    } else if (this->actor.xzDistToPlayer < 200.0f) {
        func_800B8614(&this->actor, globalCtx, 210.0f);
    }
}

void func_80B42660(EnKgy* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    this->actor.focus.pos = this->unk_2A8;
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        func_80B413C8(this);
        this->actor.flags &= ~ACTOR_FLAG_100;
        this->actionFunc = func_80B42714;
        func_80B40E18(this, 7);
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B42714(EnKgy* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    this->actor.focus.pos = this->unk_2A8;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) || (&this->actor == player->targetActor)) {
        func_80B411DC(this, globalCtx, 4);
        func_80B40E18(this, this->actor.textId);
        if (this->actor.textId == 0xC37) {
            this->actionFunc = func_80B42660;
        } else {
            this->actionFunc = func_80B41E18;
        }
    }
}

void func_80B427C8(EnKgy* this, GlobalContext* globalCtx) {
    s32 pad;
    u16 temp_a2;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_2D2 == 5) {
            func_80B40BC0(this, 7);
        }
        if (this->unk_2D2 == 3) {
            func_80B40BC0(this, 4);
        }
    }

    if ((this->unk_2E4 <= 0) && !(this->unk_29C & 2) && (func_80B40E54(this) == 0) &&
        (Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        temp_a2 = globalCtx->msgCtx.currentTextId;

        switch (temp_a2) {
            case 0xC30:
                globalCtx->msgCtx.unk11F10 = 0;
                this->actor.textId = temp_a2;
                this->unk_29C |= 4;
                this->unk_2E8 = 3;
                break;

            case 0xC31:
                globalCtx->msgCtx.unk11F10 = 0;
                func_80B41368(this, globalCtx, 4);
                this->actor.textId = temp_a2 + 1;
                break;

            case 0xC32:
            case 0xC33:
                func_80B40EBC(this, globalCtx, temp_a2);
                break;

            case 0xC34:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B41C54;
                func_80B413C8(this);
                func_80B40E18(this, 6);
                func_80B40BC0(this, 4);
                this->actor.textId = 0xC3A;
                break;
        }
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B4296C(EnKgy* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime) && (this->unk_2D2 == 8)) {
        func_80B40BC0(this, 2);
    }

    this->actor.focus.pos = this->unk_2A8;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B427C8;
        if (this->unk_2D2 == 4) {
            func_80B40BC0(this, 7);
        } else {
            EnKgy_ChangeAnim(this, 5, 2, -5.0f);
        }
        func_80B411DC(this, globalCtx, 0);
        func_80B40E18(this, this->actor.textId);
        this->actor.flags &= ~ACTOR_FLAG_10000;
    } else {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8500(&this->actor, globalCtx, 1000.0f, 1000.0f, EXCH_ITEM_NONE);
    }
}

void func_80B42A8C(EnKgy* this, GlobalContext* globalCtx) {
    u16 temp_a2;
    s32 pad;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_2D2 == 5) {
            func_80B40BC0(this, 1);
        }

        if (this->unk_2D2 == 3) {
            func_80B40BC0(this, 4);
        }
    }

    if ((this->unk_2E4 <= 0) && !(this->unk_29C & 2) && (func_80B40E54(this) == 0) &&
        (Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        temp_a2 = globalCtx->msgCtx.currentTextId;
        switch (temp_a2) {
            case 0xC1D:
            case 0xC2D:
                globalCtx->msgCtx.unk11F10 = 0;
                this->actor.textId = temp_a2;
                this->unk_29C |= 4;
                this->unk_2E8 = 3;
                break;

            case 0xC1E:
                globalCtx->msgCtx.unk11F10 = 0;
                func_80B41368(this, globalCtx, 1);
                this->actor.textId = temp_a2 + 1;
                func_80B40E38(this);
                break;

            case 0xC1F:
            case 0xC23:
            case 0xC24:
            case 0xC27:
                func_80B40EBC(this, globalCtx, temp_a2);
                break;

            case 0xC20:
            case 0xC28:
                func_80B40BC0(this, 1);
                globalCtx->msgCtx.unk11F10 = 0;
                this->unk_29C |= 4;
                this->unk_2E8 = 3;
                this->actor.textId = temp_a2;
                func_80B40E38(this);
                break;

            case 0xC21:
            case 0xC29:
                globalCtx->msgCtx.unk11F10 = 0;
                func_80B41368(this, globalCtx, 0);
                this->actor.textId = temp_a2 + 1;
                break;

            case 0xC22:
            case 0xC26:
            case 0xC2B:
            case 0xC2E:
                globalCtx->msgCtx.unk11F10 = 0;
                func_80B41368(this, globalCtx, 1);
                this->actor.textId = temp_a2 + 1;
                break;

            case 0xC25:
                globalCtx->msgCtx.unk11F10 = 0;
                func_80B41368(this, globalCtx, 2);
                this->actor.textId = temp_a2 + 1;
                break;

            case 0xC2A:
                this->unk_2E4 = 20;
                this->unk_2E2 = 3;
                func_80B40EBC(this, globalCtx, this->actor.textId);
                break;

            case 0xC2C:
            case 0xC2F:
                func_801477B4(globalCtx);
                this->actionFunc = func_80B42D28;
                func_80B413C8(this);
                func_80B40E18(this, 1);
                break;
        }
    }
    func_80B40EE8(this, globalCtx);
}

void func_80B42D28(EnKgy* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime) && (this->unk_2D2 == 8)) {
        func_80B40BC0(this, 2);
    }

    this->actor.focus.pos = this->unk_2A8;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = func_80B42A8C;
        if (this->actor.textId == 0xC2D) {
            func_80B40BC0(this, 1);
        } else {
            EnKgy_ChangeAnim(this, 5, 2, -5.0f);
            gSaveContext.save.weekEventReg[20] |= 0x80;
        }
        func_80B411DC(this, globalCtx, 0);
        func_80B40E18(this, this->actor.textId);
    } else {
        if (Flags_GetSwitch(globalCtx, ENKGY_GET_FE00(&this->actor))) {
            this->actor.textId = 0xC30;
            this->actionFunc = func_80B4296C;
            gSaveContext.save.weekEventReg[21] |= 1;
        } else if (this->actor.xzDistToPlayer < 200.0f) {
            if (this->unk_2D2 == 4) {
                this->actor.textId = 0xC2D;
            } else {
                this->actor.textId = 0xC1D;
            }
            func_800B8614(&this->actor, globalCtx, 210.0f);
        }

        if ((this->unk_2D2 == 0) && (this->actor.xzDistToPlayer < 200.0f)) {
            EnKgy_ChangeAnim(this, 8, 2, 5.0f);
        }
    }
}

void EnKgy_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnKgy* this = THIS;
    s32 pad;
    Vec3s sp30;

    this->actionFunc(this, globalCtx);
    if (this->unk_2D2 == 2) {
        sp30.z = 0;
        sp30.y = 0;
        sp30.x = 0;
        func_800E9250(globalCtx, &this->actor, &this->unk_2CC, &sp30, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_2CC.x, 0, 6, 6200, 100);
        Math_SmoothStepToS(&this->unk_2CC.y, 0, 6, 6200, 100);
    }
}

s32 EnKgy_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnKgy* this = THIS;

    if (!(this->unk_29C & 1)) {
        if (limbIndex == 17) {
            *dList = NULL;
        }
    } else if (limbIndex == 16) {
        *dList = NULL;
    }

    if (limbIndex == 11) {
        rot->x += this->unk_2CC.y;
    }

    return false;
}

void EnKgy_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_80B432D8 = { 1000.0f, 2000.0f, 0.0f };
    static Vec3f D_80B432E4 = { 3000.0f, 4000.0f, 300.0f };
    EnKgy* this = THIS;

    if (limbIndex == 11) {
        Matrix_MultiplyVector3fByState(&D_80B432D8, &this->unk_2A8);
    }

    if (limbIndex == 16) {
        Matrix_MultiplyVector3fByState(&D_80B432E4, &this->unk_2C0);
    }
}

void func_80B43074(EnKgy* this, GlobalContext* globalCtx) {
    s32 pad;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_800B8050(&this->actor, globalCtx, MTXMODE_NEW);
    Matrix_StatePush();
    Matrix_InsertTranslation(-800.0f, 3100.0f, 8400.0f, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(0x4000, MTXMODE_APPLY);

    if (func_80B40D8C(globalCtx)) {
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_kgy_Matanimheader_00F6A0));
    } else {
        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_kgy_Matanimheader_00EE58));
    }

    gfx = POLY_OPA_DISP;
    gSPMatrix(gfx, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (func_80B40D8C(globalCtx)) {
        gSPDisplayList(&gfx[1], gameplay_keep_DL_001D00);
        gSPDisplayList(&gfx[2], object_kgy_DL_00F180);
    } else {
        gSPDisplayList(&gfx[1], gameplay_keep_DL_0021A8);
        gSPDisplayList(&gfx[2], object_kgy_DL_00E8F0);
    }
    POLY_OPA_DISP = &gfx[3];

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePop();
}

void EnKgy_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnKgy* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->unk_29C & 1) {
        func_80B43074(this, globalCtx);
    }
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnKgy_OverrideLimbDraw, EnKgy_PostLimbDraw, &this->actor);
}
