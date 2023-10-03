/*
 * File: z_obj_sound.c
 * Overlay: ovl_Obj_Sound
 * Description: Plays certain sounds (e.g., swamp waterfall noise)
 */

#include "z_obj_sound.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjSound*)thisx)

void ObjSound_Init(Actor* thisx, PlayState* play);
void ObjSound_Destroy(Actor* thisx, PlayState* play);
void ObjSound_Update(Actor* thisx, PlayState* play);
void ObjSound_Draw(Actor* thisx, PlayState* play);

/**
 * Sound Modes:
 *
 * Mode 0:
 *   - NA_SE_EV_FOUNTAIN
 *   - NA_SE_EV_COW_CRY_LV
 *   - NA_SE_EV_WATER_WALL_BIG
 *   - NA_SE_EV_WATER_WALL
 *   - NA_SE_EV_MAKE_TURRET
 *   - NA_SE_EV_WATER_BUBBLE
 *   - NA_SE_EV_DRAIN
 *   - NA_SE_EV_BOILED_WATER_S
 * Mode 1: ()
 *   - NA_BGM_SHOP
 *   - NA_BGM_MINI_GAME
 *   - NA_BGM_MILK_BAR
 *   - NA_BGM_MILK_BAR_DUPLICATE
 *   - NA_BGM_ASTRAL_OBSERVATORY
 * Mode 2:
 *   - Unused in scenes
 * Mode 3: (Fanfares)
 *   - NA_BGM_SWAMP_CRUISE
 */

ActorInit Obj_Sound_InitVars = {
    ACTOR_OBJ_SOUND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjSound),
    (ActorFunc)ObjSound_Init,
    (ActorFunc)ObjSound_Destroy,
    (ActorFunc)ObjSound_Update,
    (ActorFunc)NULL,
};

void ObjSound_Init(Actor* thisx, PlayState* play) {
    ObjSound* this = THIS;

    this->unk_144 = false;
    this->soundType = OBJ_SOUND_GET_TYPE(&this->actor);
    this->sfxType = OBJ_SOUND_GET_SFX_TYPE(&this->actor);
    this->actor.params &= OBJ_SOUND_ID_MASK;
    if (this->soundType == OBJ_SOUND_TYPE_FANFARE) {
        this->actor.draw = ObjSound_Draw;
    }
}

void ObjSound_Destroy(Actor* thisx, PlayState* play) {
    ObjSound* this = THIS;

    if (this->soundType == OBJ_SOUND_TYPE_BGM) {
        Audio_PlayObjSoundBgm(NULL, NA_BGM_GENERAL_SFX);
    }
}

void ObjSound_Update(Actor* thisx, PlayState* play) {
    ObjSound* this = THIS;

    if (this->soundType == OBJ_SOUND_TYPE_SFX) {
        if (this->sfxType != 0) {
            Actor_PlaySfx_Flagged(&this->actor, gAudioEnvironmentalSfx[this->actor.params]);
        } else {
            Actor_PlaySfx_FlaggedCentered3(&this->actor, gAudioEnvironmentalSfx[this->actor.params]);
        }
    } else if (this->unk_144) {
        if (this->soundType == OBJ_SOUND_TYPE_BGM) {
            Audio_PlayObjSoundBgm(&this->actor.projectedPos, this->actor.params);
        } else if (this->soundType == OBJ_SOUND_TYPE_FIXED_SFX) {
            Audio_PlaySfx_AtFixedPos(&this->actor.projectedPos, gAudioEnvironmentalSfx[this->actor.params]);
        }
    } else {
        this->unk_144 = true;
    }
}

void ObjSound_Draw(Actor* thisx, PlayState* play) {
    ObjSound* this = THIS;

    if (CHECK_EVENTINF(EVENTINF_41) || CHECK_EVENTINF(EVENTINF_35)) {
        Audio_PlayObjSoundFanfare(&this->actor.projectedPos, this->actor.params);
    }
}
