/*
 * File: z_en_rz.c
 * Overlay: ovl_En_Rz
 * Description: Rosa Sisters, Judo (red) and Marilla (blue)
 */

#include "z_en_rz.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnRz*)thisx)

void EnRz_Init(Actor* thisx, PlayState* play);
void EnRz_Destroy(Actor* thisx, PlayState* play);
void EnRz_Update(Actor* thisx, PlayState* play);
void EnRz_Draw(Actor* thisx, PlayState* play);

void func_80BFC058(EnRz* this, PlayState* play);
void func_80BFC078(EnRz* this, PlayState* play);
void func_80BFC19C(EnRz* this, PlayState* play);
void func_80BFC214(EnRz* this, PlayState* play);
void func_80BFC270(EnRz* this, PlayState* play);
void func_80BFC2F4(EnRz* this, PlayState* play);
void func_80BFC36C(EnRz* this, PlayState* play);
void func_80BFC3F8(EnRz* this, PlayState* play);
void func_80BFC608(EnRz* this, PlayState* play);
void func_80BFC674(EnRz* this, PlayState* play);
void func_80BFC728(EnRz* this, PlayState* play);
void func_80BFC7E0(EnRz* this, PlayState* play);
void func_80BFC8F8(EnRz* this, PlayState* play);

void func_80BFB780(EnRz* this, Lights* mapper, PlayState* play);
void func_80BFB864(PlayState*, EnRz*, s32, s32, f32);
void func_80BFBA50(EnRz* this, PlayState*);
s32 func_80BFBDA0(EnRz* this, PlayState*);
s32 func_80BFBCEC(EnRz* this, PlayState* play);
void func_80BFBD54(EnRz* this, PlayState* play);
s32 func_80BFBE70(EnRz* this, PlayState* play);
s32 func_80BFBFAC(EnRz* this, PlayState* play);
#if 0
const ActorInit En_Rz_InitVars = {
    ACTOR_EN_RZ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RZ,
    sizeof(EnRz),
    (ActorFunc)EnRz_Init,
    (ActorFunc)EnRz_Destroy,
    (ActorFunc)EnRz_Update,
    (ActorFunc)EnRz_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFCCF4 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BFCCF4;

extern UNK_TYPE D_06003A20;
extern UNK_TYPE D_0600D768;

extern FlexSkeletonHeader D_0600D8D8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Init.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFB780.s")

void func_80BFB780(EnRz* this, Lights* mapper, PlayState* play) {
    Vec3f sp34;
    f32 new_var;
    s32 pad;

    if (this->unk422 == 8) {
        new_var = (((27.0f - this->unk414.y) + this->actor.world.pos.y) * 0.00044444448f) + 0.01f;
        this->actor.scale.x = new_var;
    }
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk414);
    func_800B4AEC(play, &this->actor, 50.0f);
    if (sp34.y < this->actor.floorHeight) {
        this->actor.world.pos.y = this->actor.floorHeight;
    } else {
        this->actor.world.pos.y = sp34.y;
    }
    ActorShadow_DrawCircle(&this->actor, mapper, play);
    Math_Vec3f_Copy(&this->actor.world.pos, &sp34);
    this->actor.scale.x = 0.01f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFB864.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFB9E4.s")

void func_80BFB9E4(PlayState* arg0, EnRz* arg1, s16 arg2) {
    func_80BFB864(arg0, arg1, (s32)arg2, 0, -5.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBA1C.s")

void func_80BFBA1C(PlayState* arg0, EnRz* arg1, s16 arg2) {
    func_80BFB864(arg0, arg1, (s32)arg2, 0, 0.0f);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBA50.s")
/*
void func_80BFBA50(EnRz *this, PlayState *play) {
    //Path *sp1C;
    Path *path;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 params;
    Vec3f *points;

    params = (s32) (this->actor.params & 0x7E00) >> 9;
    if ((params) != 0x3F) {
        path = &play->setupPathList[params];
        this->unk3B8 = path;
        if (path != NULL) {
            points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
            temp_fv0 = (f32) points->x - this->actor.world.pos.x;
            temp_fv1 = (f32) points->y - this->actor.world.pos.z;
            if (((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1)) < 100.0f) {
                this->unk3BC = 0;
                this->unk420 &= 0xFFFE;
            } else {
                this->unk3BC = path->count - 1;
                this->unk420 |= 1;
            }
        }
    } else {
        this->unk3B8 = NULL;
        this->unk3BC = 0;
    }
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBB44.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBC78.s")

s32 func_80BFBC78(EnRz* this, PlayState* play) {
    if ((this->actor.xzDistToPlayer < 80.0f) && (fabsf(this->actor.playerHeightRel) < 20.0f) &&
        (Player_IsFacingActor(&this->actor, 0x3000, play))) {
        return true;
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBCEC.s")

s32 func_80BFBCEC(EnRz* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (this->actor.xzDistToPlayer < 100.0f) {
        if ((Actor_IsFacingPlayer(&this->actor, 0x3000) != 0) && (player->stateFlags2 & 0x02000000)) {
            return true;
        }
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBD54.s")

void func_80BFBD54(EnRz* this, PlayState* play) {
    if (this->unk422 < 7) {
        SkelAnime_Update(&this->skelanime);
    } else {
        LinkAnimation_Update(play, &this->skelanime);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBDA0.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBDFC.s")

void func_80BFBDFC(PlayState* play) {
    if ((gSaveContext.save.weekEventReg[0x4B] & 0x80) != 0) {
        func_80151BB4(play, 0x27);
    }
    func_80151BB4(play, 0xC);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Destroy.s")

void EnRz_Destroy(Actor* thisx, PlayState* play) {
    EnRz* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBE70.s")
/*
s32 func_80BFBE70(EnRz* this, PlayState* play) {
    u16 action;

    if (((this->actor.params & 0x8000) == 0) && (this->unk422 == 4)) {
        func_800B9010(&this->actor, 0x2198);
    }
    if (Cutscene_CheckActorAction(play, this->unk426) != 0) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, this->unk426));
        action = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, this->unk426)]->action;
        if (action != this->unk428) {
            this->unk428 = action;
            switch (action & 0xFFFF) {
                case 1:
                    func_80BFBA1C(play, this, 1);
                    return 1;
                case 2:
                    func_80BFBA1C(play, this, 5);
                    return 1;
                case 3:
                    func_80BFBA1C(play, this, 4);
                    return 1;
                case 4:
                    func_80BFBA1C(play, this, 8);
                    return 1;
                default:
                    return 1;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFBFAC.s")

s32 func_80BFBFAC(EnRz* this, PlayState* play) {
    if (this->actor.cutscene == -1) {
        Message_StartTextbox(play, 0x2925U, &this->actor);
        this->actionFunc = func_80BFC078;
    } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        return false;
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        return true;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC058.s")

void func_80BFC058(EnRz* this, PlayState* play) {
    func_80BFBD54(this, play);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC078.s")
/*
void func_80BFC078(EnRz* this, PlayState* play) {
    Vec3f sp28;
    u16 temp_v1;

    func_80BFBD54(this, play);
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        // if (1)
        temp_v1 = play->msgCtx.currentTextId;
        if ((temp_v1 == 0x2927) || (temp_v1 == 0x2928)) {
            func_80151938(play, (temp_v1 + 1) & 0xFFFF);
            gSaveContext.save.weekEventReg[0x4D] |= 4;
        } else {
            func_801477B4(play);
            this->actionFunc = func_80BFC3F8;
            if (this->unk422 != 8) {
                func_80BFB9E4(play, this, 6);
                if (this->unk40C != NULL) {
                    func_80BFB9E4(play, this->unk40C, 6);
                }
            }
        }
    }
    if ((this->actor.params & 0x8000) == 0) {
        sp28.x = this->actor.projectedPos.x;
        sp28.y = this->actor.projectedPos.y;
        sp28.z = this->actor.projectedPos.z;
        func_801A1FB4(3, &sp28, 0x2A, 900.0f);
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC19C.s")

void func_80BFC19C(EnRz *this, PlayState *play) {
    func_80BFBD54(this, play);
    if (!func_80BFBE70(this, play)) {
        this->actionFunc = func_80BFC3F8;
        func_80BFBA1C(play, this, 8);
        if (this->unk40C != NULL) {
            func_80BFBA1C(play, (EnRz *) this->unk40C, 8);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC214.s")

void func_80BFC214(EnRz *this, PlayState *play) {
    func_80BFBD54(this, play);
    if (!func_80BFBE70(this, play) && func_80BFBFAC(this, play)) {
        this->actionFunc = func_80BFC19C;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC270.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC2F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC36C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC7E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC8AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFC8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/func_80BFCAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rz/EnRz_Draw.s")
