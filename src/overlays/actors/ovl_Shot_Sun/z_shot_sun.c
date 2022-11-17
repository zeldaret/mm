/*
 * File: z_shot_sun.c
 * Overlay: ovl_Shot_Sun
 * Description: Leftover sun hitbox from OOT and fairy spawner
 */

#include "z_shot_sun.h"
#include "overlays/actors/ovl_Item_Etcetera/z_item_etcetera.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((ShotSun*)thisx)

void ShotSun_Init(Actor* thisx, PlayState* play);
void ShotSun_Destroy(Actor* thisx, PlayState* play);
void ShotSun_Update(Actor* thisx, PlayState* play);

void ShotSun_UpdateForOcarina(ShotSun* this, PlayState* play);
void ShotSun_UpdateHyliaSun(ShotSun* this, PlayState* play);

ActorInit Shot_Sun_InitVars = {
    /**/ ACTOR_SHOT_SUN,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(ShotSun),
    /**/ ShotSun_Init,
    /**/ ShotSun_Destroy,
    /**/ ShotSun_Update,
    /**/ NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000020, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 60, 0, { 0, 0, 0 } },
};

void ShotSun_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ShotSun* this = THIS;

    if ((SHOTSUN_GET_FF(thisx) == SHOTSUN_FAIRY_SPAWNER_SUNS) ||
        (SHOTSUN_GET_FF(thisx) == SHOTSUN_FAIRY_SPAWNER_STORMS)) {
        this->unk_19C = 0;
        this->actor.flags |= ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;
        this->actionFunc = ShotSun_UpdateForOcarina;
        this->actor.flags |= ACTOR_FLAG_8000000;
    } else {
        Collider_InitCylinder(play, &this->collider);
        Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
        this->actionFunc = ShotSun_UpdateHyliaSun;
        this->actor.flags &= ~ACTOR_FLAG_1;
    }
}

void ShotSun_Destroy(Actor* thisx, PlayState* play) {
    ShotSun* this = THIS;

    if ((SHOTSUN_GET_FF(thisx) != SHOTSUN_FAIRY_SPAWNER_SUNS) &&
        (SHOTSUN_GET_FF(thisx) != SHOTSUN_FAIRY_SPAWNER_STORMS)) {
        Collider_DestroyCylinder(play, &this->collider);
    }
}

void ShotSun_SpawnFairy(ShotSun* this, PlayState* play2) {
    s32 params = SHOTSUN_GET_FF(&this->actor);
    s32 fairyType = 0;
    PlayState* play = play2;

    if (this->timer > 0) {
        this->timer--;
    } else {
        ActorCutscene_Stop(this->actor.cutscene);
        switch (params) {
            case SHOTSUN_FAIRY_SPAWNER_SUNS:
                fairyType = ENELF_TYPE_7;
                break;
            case SHOTSUN_FAIRY_SPAWNER_STORMS:
                fairyType = ENELF_TYPE_7;
                break;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELF, this->actor.home.pos.x, this->actor.home.pos.y,
                    this->actor.home.pos.z, 0, 0, 0, fairyType);
        Actor_Kill(&this->actor);
    }
}

void ShotSun_TriggerFairy(ShotSun* this, PlayState* play) {
    if ((this->actor.cutscene == -1) || ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        if (this->actor.cutscene != -1) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
        }
        this->actionFunc = ShotSun_SpawnFairy;
        this->timer = 50;
        Actor_Spawn(&play->actorCtx, play, ACTOR_DEMO_KANKYO, this->actor.home.pos.x, this->actor.home.pos.y,
                    this->actor.home.pos.z, 0, 0, 0, 0x11);
        Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_TRE_BOX_APPEAR);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void ShotSun_UpdateForOcarina(ShotSun* this, PlayState* play) {
    s32 params = SHOTSUN_GET_FF(&this->actor);

    if (play->msgCtx.ocarinaMode == 3) {
        switch (play->msgCtx.lastPlayedSong) {
            case OCARINA_SONG_STORMS:
                if (params == SHOTSUN_FAIRY_SPAWNER_STORMS) {
                    this->actionFunc = ShotSun_TriggerFairy;
                    play->msgCtx.ocarinaMode = 4;
                }
                break;
            case OCARINA_SONG_SUNS:
                if (params == SHOTSUN_FAIRY_SPAWNER_SUNS) {
                    this->actionFunc = ShotSun_TriggerFairy;
                    play->msgCtx.ocarinaMode = 4;
                }
                break;
        }
    }
}

void ShotSun_UpdateHyliaSun(ShotSun* this, PlayState* play) {
    Vec3s cylinderPos;
    Player* player = GET_PLAYER(play);
    EnItem00* collectible;
    s32 pad;
    Vec3f spawnPos;

    if (this->collider.base.acFlags & AC_HIT) {
        play_sound(NA_SE_SY_CORRECT_CHIME);
        if (1) {}
        if (INV_CONTENT(ITEM_ARROW_FIRE) == ITEM_NONE) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_ETCETERA, 700.0f, -800.0f, 7261.0f, 0, 0, 0,
                        ITEM_ETC_ARROW_FIRE);
            if (1) {}
            gSaveContext.cutsceneTrigger = 1;
        } else {
            spawnPos.x = 700.0f;
            spawnPos.y = -800.0f;
            spawnPos.z = 7261.0f;
            collectible = (EnItem00*)Item_DropCollectible(play, &spawnPos, ITEM00_MAGIC_LARGE);
            if (collectible != NULL) {
                collectible->unk152 = 0x1770;
                collectible->actor.speedXZ = 0.0f;
            }
        }

        Actor_Kill(&this->actor);
        return;
    }

    if (!(this->actor.xzDistToPlayer > 120.0f)) {
        if ((gSaveContext.save.time >= CLOCK_TIME(6, 30)) && (gSaveContext.save.time < CLOCK_TIME(7, 30))) {
            cylinderPos.x = player->bodyPartsPos[PLAYER_BODYPART_HEAD].x + (play->envCtx.unk_4 * (1.0f / 6.0f));
            cylinderPos.y =
                (player->bodyPartsPos[PLAYER_BODYPART_HEAD].y - 30.0f) + (play->envCtx.unk_8 * (1.0f / 6.0f));
            cylinderPos.z = player->bodyPartsPos[PLAYER_BODYPART_HEAD].z + (play->envCtx.unk_C * (1.0f / 6.0f));

            this->hitboxPos = cylinderPos;

            Collider_SetCylinderPosition(&this->collider, &cylinderPos);
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

void ShotSun_Update(Actor* thisx, PlayState* play) {
    ShotSun* this = THIS;

    this->actionFunc(this, play);
}
