/*
 * File: z_oceff_storm.c
 * Overlay: ovl_Oceff_Storm
 * Description: Song of Storms Ocarina Effect
 */

#include "z_oceff_storm.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((OceffStorm*)thisx)

void OceffStorm_Init(Actor* thisx, PlayState* play);
void OceffStorm_Destroy(Actor* thisx, PlayState* play);
void OceffStorm_Update(Actor* thisx, PlayState* play);
void OceffStorm_Draw(Actor* thisx, PlayState* play);

void func_80981928(OceffStorm* this, PlayState* play);
void func_80981B48(OceffStorm* this, PlayState* play);

void OceffStorm_SetupAction(OceffStorm* this, OceffStormActionFunc actionFunc);
s32 func_8098176C(PlayState* play); /* extern */
void func_80981BB8(Actor* thisx, PlayState* play);
#if 0
const ActorInit Oceff_Storm_InitVars = {
    ACTOR_OCEFF_STORM,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffStorm),
    (ActorFunc)OceffStorm_Init,
    (ActorFunc)OceffStorm_Destroy,
    (ActorFunc)OceffStorm_Update,
    (ActorFunc)OceffStorm_Draw,
};

#endif

extern Gfx* D_80982F90;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_SetupAction.s")

void OceffStorm_SetupAction(OceffStorm* this, OceffStormActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_8098176C.s")

s32 func_8098176C(PlayState* play) {
    s32 phi_v1 = 0;

    switch (play->sceneNum) {
        case SCENE_13HUBUKINOMITI:
        case SCENE_11GORONNOSATO:
        case SCENE_10YUKIYAMANOMURA:
        case SCENE_14YUKIDAMANOMITI:
        case SCENE_12HAKUGINMAE:
        case SCENE_17SETUGEN:
        case SCENE_GORONRACE:
            if (gSaveContext.sceneSetupIndex == 0) {
                phi_v1 = 1;
            }
            break;
        case SCENE_10YUKIYAMANOMURA2:
            if (gSaveContext.sceneSetupIndex == 1) {
                phi_v1 = 1;
            }
            break;
        
    }
    return phi_v1;
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Init.s")

void OceffStorm_Init(Actor* thisx, PlayState* play) {
    s32 pad[2];
    Player* player = GET_PLAYER(play);
    OceffStorm* this = THIS;

    OceffStorm_SetupAction(this, func_80981928);
    this->posYOffAdd = 0;
    this->counter = 0;
    this->primColorAlpha = 0;
    this->vtxAlpha = 0;
    this->actor.scale.y = 0.0f;
    this->actor.scale.z = 0.0f;
    this->actor.scale.x = 0.0f;
    this->posYOff = this->posYOffAdd;
    if (this->actor.params == 1) {
        OceffStorm_SetupAction(this, func_80981B48);
        this->actor.draw = func_80981BB8;
    } else {
        this->actor.world.pos.y = player->actor.world.pos.y;
        this->actor.world.pos.x = player->bodyPartsPos[0].x;
        this->actor.world.pos.z = player->bodyPartsPos[0].z;
        gSaveContext.jinxTimer = 0;
        if ((play->interfaceCtx.restrictions.songOfStorms == 0) && (!func_8098176C(play))) {
            Actor_Spawn(&play->actorCtx, play, 0xC4, this->actor.world.pos.x, this->actor.world.pos.y - 30.0f,
                        this->actor.world.pos.z, 0, 0, 0, 1);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Destroy.s")

void OceffStorm_Destroy(Actor* thisx, PlayState* play) {
    OceffStorm* this = THIS;

    func_80115D5C(&play->state);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981928.s")

void func_80981928(OceffStorm* this, PlayState* play) {
    f32 phi_fv1;

    switch (gSaveContext.save.playerForm) {
        default:
            phi_fv1 = 1.0f;
            break;
        case 3:
            phi_fv1 = 1.3f;
            break;
        case 2:
            phi_fv1 = 1.2f;
            break;
        case 1:
            phi_fv1 = 2.0f;
            break;
    }

    if (this->counter < 10) {
        this->primColorAlpha = (s8)(this->counter * 10.0f);
    } else if (this->counter > 60) {
        this->primColorAlpha = (s8)((70 - this->counter) * 10.0f);
    } else {
        this->primColorAlpha = 100;
    }
    if ((this->counter < 10) || (this->counter >= 60)) {
        this->vtxAlpha = 0;
    } else if (this->counter <= 40) {
        if (this->vtxAlpha <= 200) {
            this->vtxAlpha += 10;
        }
        this->actor.scale.x = this->actor.scale.z = 0.4f * phi_fv1;
        this->actor.scale.y = 0.3f;
    } else if (this->counter > 40) {
        this->vtxAlpha = (60 - this->counter) * 10;
    } else {
        this->actor.scale.x = this->actor.scale.z = 0.4f * phi_fv1;
        this->vtxAlpha = -1;
    }
    if (this->counter > 40) {
        this->actor.world.pos.y += this->posYOff * 0.01f;
        this->posYOff += this->posYOffAdd;
        this->posYOffAdd += 10;
    }
    if (this->counter < 70) {
        this->counter++;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981B48.s")

void func_80981B48(OceffStorm* this, PlayState* play) {
    if (this->primColorAlpha < 100) {
        this->primColorAlpha += 5;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Update.s")

void OceffStorm_Update(Actor* thisx, PlayState* play) {
    OceffStorm* this = THIS;

    this->actor.shape.rot.y = Camera_GetCamDirYaw(GET_ACTIVE_CAM(play));
    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981BB8.s")

void func_80981BB8(Actor* thisx, PlayState* play) {
    s32 scroll = play->state.frames & 0xFFF;
    OceffStorm* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_XLU_DISP++);

    POLY_XLU_DISP = func_8012C3A4(POLY_XLU_DISP);

    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
    gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 200, 200, 150, this->primColorAlpha);
    gSPDisplayList(POLY_XLU_DISP++, &D_80982F90);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(play->state.gfxCtx, 0, scroll * 8, scroll * 4, 0x40, 0x40, 1,
                                                     scroll * 4, scroll * 4, 0x40, 0x40));
    gSPTextureRectangle(POLY_XLU_DISP++, 0, 0, 0x0500, 0x03C0, G_TX_RENDERTILE, 0, 0, 0x008C, -0x008C);

    CLOSE_DISPS(play->state.gfxCtx);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Draw.s")

extern Gfx* D_809831E8;
extern Gfx* D_80983290;
extern Vtx* D_80983038;

void OceffStorm_Draw(Actor* thisx, PlayState* play) {
    u32 scroll = play->state.frames & 0xFFF;
    OceffStorm* this = (OceffStorm*)thisx;
    Vtx* vtxPtr = &D_80983038;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 200, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 150, 150, 0, 128);
    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
    gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);

    vtxPtr[0].v.cn[3] = vtxPtr[6].v.cn[3] = vtxPtr[16].v.cn[3] = vtxPtr[25].v.cn[3] = this->vtxAlpha >> 1;
    vtxPtr[10].v.cn[3] = vtxPtr[22].v.cn[3] = this->vtxAlpha;

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, &D_809831E8);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, scroll * 4, (0 - scroll) * 8,
                                                     32, 32, 1, scroll * 8, (0 - scroll) * 12, 32, 32));
    gSPDisplayList(POLY_XLU_DISP++, &D_80983290);

    CLOSE_DISPS(play->state.gfxCtx);

    func_80981BB8(&this->actor, play);
}