/*
 * File: z_shot_sun.c
 * Overlay: ovl_Shot_Sun
 * Description:
 */

#include "z_shot_sun.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((ShotSun*)thisx)

void ShotSun_Init(Actor* thisx, PlayState* play);
void ShotSun_Destroy(Actor* thisx, PlayState* play);
void ShotSun_Update(Actor* thisx, PlayState* play);

void ShotSun_SpawnFairy(ShotSun* this, PlayState* play2);
void func_80973804(ShotSun* this, PlayState* play);
void func_809738D0(ShotSun* this, PlayState* play);
void func_80973960(ShotSun* this, PlayState* play2);

#if 0
const ActorInit Shot_Sun_InitVars = {
    ACTOR_SHOT_SUN,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ShotSun),
    (ActorFunc)ShotSun_Init,
    (ActorFunc)ShotSun_Destroy,
    (ActorFunc)ShotSun_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80973BA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000020, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 60, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80973BA0;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/ShotSun_Init.s")

void ShotSun_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ShotSun* this = (ShotSun*)thisx;

    if (((this->actor.params & 0xFF) == 0x40) || ((this->actor.params & 0xFF) == 0x41)) {
        this->unk19C = 0;
        this->actor.flags |= ACTOR_FLAG_10;
        this->actor.flags |= ACTOR_FLAG_2000000;
        this->actionFunc = func_809738D0;
        this->actor.flags |= ACTOR_FLAG_8000000;
        ;
    } else {
        Collider_InitCylinder(play, &this->collider);
        Collider_SetCylinder(play, &this->collider, &this->actor, &D_80973BA0);
        this->actionFunc = func_80973960;
        this->actor.flags &= -2;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/ShotSun_Destroy.s")

void ShotSun_Destroy(Actor* thisx, PlayState* play) {
    ShotSun* this = THIS;

    if (((this->actor.params & 0xFF) != 0x40) && ((this->actor.params & 0xFF) != 0x41)) {
        Collider_DestroyCylinder(play, &this->collider);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_80973740.s")

void ShotSun_SpawnFairy(ShotSun* this, PlayState* play2) {
    s32 params = this->actor.params & 0xFF;
    s32 fairyType = 0;
    PlayState* play = play2;

    if (this->unk19A > 0) {
        this->unk19A--;
    } else {
        ActorCutscene_Stop(this->actor.cutscene);
        switch (params) {
            case 0x40:
                fairyType = 7;
                break;
            case 0x41:
                fairyType = 7;
                break;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELF, this->actor.home.pos.x, this->actor.home.pos.y,
                    this->actor.home.pos.z, 0, 0, 0, fairyType);
        Actor_MarkForDeath(&this->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_80973804.s")

void func_80973804(ShotSun* this, PlayState* play) {
    if ((this->actor.cutscene == -1) || ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        if (this->actor.cutscene != -1) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
        }
        this->actionFunc = ShotSun_SpawnFairy;
        this->unk19A = 0x32;
        Actor_Spawn(&play->actorCtx, play, 0x49, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
                    0, 0, 0, 0x11);
        Audio_PlaySfxAtPos(&this->actor.projectedPos, 0x287B);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_809738D0.s")

void func_809738D0(ShotSun* this, PlayState* play) {
    s32 params = this->actor.params & 0xFF;

    if (play->msgCtx.ocarinaMode == 3) {
        switch (play->msgCtx.unk1202E) {
            case 10:
                if (params == 0x41) {
                    this->actionFunc = func_80973804;
                    play->msgCtx.ocarinaMode = 4;
                }
                break;
            case 11:
                if (params == 0x40) {
                    this->actionFunc = func_80973804;
                    play->msgCtx.ocarinaMode = 4;
                }
                break;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_80973960.s")

void func_80973960(ShotSun* this, PlayState* play) {
    Vec3s cylinderPos;
    Player* player = (Player*)play->actorCtx.actorLists[2].first;
    EnItem00* item;
    s32 pad;
    Vec3f spawnPos;
    
    if (this->collider.base.acFlags & 2) {
        play_sound(0x4802);
        if(1){}
        if (gSaveContext.save.inventory.items[gItemSlots[2]] == 0xFF) {
            Actor_Spawn(&play->actorCtx, play, 0x80, 700.0f, -800.0f, 7261.0f, 0, 0, 0, 7);
            if(1){}
            gSaveContext.cutsceneTrigger = 1;
        } else {
            spawnPos.x = 700.0f;
            spawnPos.y = -800.0f;
            spawnPos.z = 7261.0f;
            item = Item_DropCollectible(play, &spawnPos, 0xE);
            if (item != NULL) {
                item->unk152 = 0x1770;
                item->actor.speedXZ = 0.0f;
            }
        }
        
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (!(this->actor.xzDistToPlayer > 120.0f)) {
        if ((gSaveContext.save.time >= 0x4555) && (gSaveContext.save.time < 0x5000)) {
            cylinderPos.x = player->bodyPartsPos[7].x + (play->envCtx.unk_4 * 0.16666667f);
            cylinderPos.y = (player->bodyPartsPos[7].y - 30.0f) + (play->envCtx.unk_8 * 0.16666667f);
            cylinderPos.z = player->bodyPartsPos[7].z + (play->envCtx.unk_C * 0.16666667f);
            
            this->hitboxPos = cylinderPos;
            
            Collider_SetCylinderPosition(&this->collider, &cylinderPos);
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/ShotSun_Update.s")

void ShotSun_Update(Actor* thisx, PlayState* play) {
    ShotSun* this = THIS;

    this->actionFunc(this, play);
}

