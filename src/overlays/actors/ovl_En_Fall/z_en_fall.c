/*
 * File: z_en_fall.c
 * Overlay: ovl_En_Fall
 * Description: The Moon and related effects
 */

#include "z_en_fall.h"

#define FLAGS 0x00000030

#define THIS ((EnFall*)thisx)

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Update(Actor* thisx, GlobalContext* globalCtx);

void EnFall_Setup(EnFall* this, GlobalContext* globalCtx);
void EnFall_CrashingMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_StoppedOpenMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_StoppedClosedMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx);
void EnFall_UnspecifiedMoon_Act(EnFall* this, GlobalContext* globalCtx);
void EnFall_DoNothing(EnFall* this, GlobalContext* globalCtx);
void EnFall_MoonsTear_Fall(EnFall* this, GlobalContext* globalCtx);
void EnFall_FireBall_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall_Moon_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_FireBall_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_RisingDebris_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall_RisingDebris_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DC20(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DC40(Actor* thisx, GlobalContext* globalCtx);
void EnFall_FireRing_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFall_FireRing_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_OpenMouthMoon_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnFall_MoonsTear_Draw(Actor* thisx, GlobalContext* globalCtx);

typedef struct {
    u8 dListIndex;
    Vec3f pos;
    Vec3f velocity;
    Vec3s rot;
} EnFallDebrisParticle;

EnFallDebrisParticle debrisParticles[50];

const ActorInit En_Fall_InitVars = {
    ACTOR_EN_FALL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFall),
    (ActorFunc)EnFall_Init,
    (ActorFunc)EnFall_Destroy,
    (ActorFunc)EnFall_Update,
    (ActorFunc)NULL,
};

// object_lodmoon
extern Gfx D_060010E0[]; // LodMoon eyes
extern Gfx D_06001158[]; // LodMoon moon

// object_moonston
extern Gfx D_06000400[]; // Falling moon's tear
extern Gfx D_060004C8[]; // Falling moon's tear flame trail
extern AnimatedMaterial D_06001220;

// object_fall2
extern Gfx D_06002970[]; // Open-mouthed moon

// object_fall
extern Gfx D_06000198[]; // Sets up textures for debris
extern Gfx D_06000220[]; // Debris 1
extern Gfx D_06000428[]; // Debris 2
extern Gfx D_06000498[]; // Debris 3
extern Vtx D_060004C0[]; // Fire ball vertices
extern Gfx D_060011D0[]; // Fire ball
extern Gfx D_06003C30[]; // Fire ring
extern AnimatedMaterial D_06004E38;
extern Gfx D_060077F0[]; // Moon

void EnFall_Moon_AdjustScaleAndPosition(EnFall* this, GlobalContext* globalCtx) {
    u16 temp_v0;
    u16 temp_v1;
    f32 phi_f0;

    temp_v0 = gSaveContext.time;
    temp_v1 = this->dayStartTime;
    if (temp_v0 < temp_v1) {
        phi_f0 = 1.0f - (((f32)temp_v1 - (f32)temp_v0) * (1.0f / 0x10000));
    } else {
        phi_f0 = ((f32)temp_v0 - (f32)temp_v1) * (1.0f / 0x10000);
    }
    switch (CURRENT_DAY) {
        case 0:
            Actor_SetScale(&this->actor, this->scale * 1.2f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 1:
            Actor_SetScale(&this->actor, this->scale * 2.4f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 2:
            Actor_SetScale(&this->actor, this->scale * 3.6f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 3:
            Actor_SetScale(&this->actor, this->scale * 3.6f);
            if (EN_FALL_TYPE(&this->actor) == EN_FALL_TYPE_INVERTED_STONE_TOWER_GAMEPLAY_MOON) {
                this->actor.world.pos.y = this->actor.home.pos.y + (phi_f0 * 6700.0f * (this->scale * 6.25f));
            } else {
                this->actor.world.pos.y = this->actor.home.pos.y - (phi_f0 * 6700.0f * (this->scale * 6.25f));
            }
            break;
    }
}

void EnFall_RisingDebris_ResetParticles(EnFall* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        debrisParticles[i].dListIndex = 3;
    }
    this->unk_158 = 0;
}

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 objectIndex;

    this->unk_150 = 0.0f;
    this->unk_154 = 0;
    switch (EN_FALL_SCALE(&this->actor)) {
        case 1:
            this->scale = 0.08f;
            break;
        case 2:
            this->scale = 0.04f;
            break;
        case 3:
            this->scale = 0.02f;
            break;
        case 4:
            this->scale = 0.01f;
            break;
        default:
            this->scale = 0.16f;
            break;
    }
    switch (EN_FALL_TYPE(&this->actor)) {
        case EN_FALL_TYPE_UNK_5:
        case EN_FALL_TYPE_REGULAR_GAMEPLAY_MOON:
        case EN_FALL_TYPE_INVERTED_STONE_TOWER_GAMEPLAY_MOON:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_LODMOON);
            break;
        case EN_FALL_TYPE_MOONS_TEAR:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MOONSTON);
            break;
        case EN_FALL_TYPE_STOPPED_MOON_OPEN_MOUTH:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_FALL2);
            break;
        default:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_FALL);
            break;
    }
    if (objectIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->objIndex = objectIndex;
    this->actionFunc = EnFall_Setup;
}

void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

Actor* EnFall_MoonsTear_GetTerminaFieldMoon(GlobalContext* globalCtx) {
    Actor* itemAction = globalCtx->actorCtx.actorList[ACTORCAT_ITEMACTION].first;

    while (itemAction != NULL) {
        if (itemAction->id == ACTOR_EN_FALL && EN_FALL_TYPE(itemAction) == EN_FALL_TYPE_TERMINA_FIELD_MOON) {
            return itemAction;
        }
        itemAction = itemAction->next;
    }
    return NULL;
}

void EnFall_Setup(EnFall* this, GlobalContext* globalCtx) {
    Actor* moon;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        this->actor.objBankIndex = this->objIndex;
        this->actionFunc = EnFall_UnspecifiedMoon_Act;
        switch (EN_FALL_TYPE(&this->actor)) {
            case EN_FALL_TYPE_TITLE_SCREEN_MOON:
                this->actor.draw = EnFall_Moon_Draw;
                this->actionFunc = EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale);
                break;
            case EN_FALL_TYPE_STOPPED_MOON_CLOSED_MOUTH:
                this->actor.draw = EnFall_Moon_Draw;
                this->actionFunc = EnFall_StoppedClosedMouthMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale * 3.0f);
                if ((gSaveContext.weekEventReg[0x19] & 2) == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case EN_FALL_TYPE_CLOCK_TOWER_MOON:
                this->actionFunc = EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale * 3.0f);
                this->actor.draw = EnFall_Moon_Draw;
                if ((gSaveContext.weekEventReg[0x19] & 2) != 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case EN_FALL_TYPE_CRASHING_MOON:
                this->actor.draw = EnFall_Moon_Draw;
                Actor_SetScale(&this->actor, this->scale * 5.3999996f);
                this->actionFunc = EnFall_CrashingMoon_PerformCutsceneActions;
                break;
            case EN_FALL_TYPE_CRASH_FIRE_BALL:
                this->actor.update = EnFall_FireBall_Update;
                this->actor.draw = EnFall_FireBall_Draw;
                this->scale = 1.0f;
                this->actor.shape.rot.z = 0;
                this->unk_150 = 0.0f;
                this->unk_158 = 0x64;
                this->actor.shape.rot.x = this->actor.shape.rot.z;
                break;
            case EN_FALL_TYPE_CRASH_RISING_DEBRIS:
                this->actor.update = EnFall_RisingDebris_Update;
                this->actor.draw = EnFall_RisingDebris_Draw;
                this->scale = 1.0f;
                EnFall_RisingDebris_ResetParticles(this);
                Actor_SetScale(&this->actor, 1.0f);
                this->actor.shape.rot.x = 0;
                break;
            case EN_FALL_TYPE_UNK_5:
                this->actor.draw = func_80A6DC20;
                this->dayStartTime = CLOCK_TIME(6, 0);
                this->currentDay = CURRENT_DAY;
                EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
                break;
            case EN_FALL_TYPE_REGULAR_GAMEPLAY_MOON:
            case EN_FALL_TYPE_INVERTED_STONE_TOWER_GAMEPLAY_MOON:
                this->actor.draw = func_80A6DC40;
                this->dayStartTime = CLOCK_TIME(6, 0);
                this->currentDay = CURRENT_DAY;
                EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
                break;
            case EN_FALL_TYPE_MOONS_TEAR:
                this->actor.update = EnFall_Update;
                this->actor.draw = NULL;
                this->actionFunc = EnFall_MoonsTear_Fall;
                Actor_SetScale(&this->actor, 0.02f);
                if ((globalCtx->actorCtx.unk5 & 2) == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                moon = EnFall_MoonsTear_GetTerminaFieldMoon(globalCtx);
                this->actor.child = moon;
                if (moon == NULL) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case EN_FALL_TYPE_STOPPED_MOON_OPEN_MOUTH:
                this->actor.draw = NULL;
                this->actionFunc = EnFall_StoppedOpenMouthMoon_PerformCutsceneActions;
                Actor_SetScale(&this->actor, this->scale * 3.0f);
                break;
            case EN_FALL_TYPE_CRASH_FIRE_RING:
                this->actor.update = EnFall_FireRing_Update;
                this->actor.draw = EnFall_FireRing_Draw;
                Actor_SetScale(&this->actor, 0.2f);
                break;
            default:
                this->actor.draw = EnFall_Moon_Draw;
                this->dayStartTime = CLOCK_TIME(6, 0);
                this->currentDay = CURRENT_DAY;
                EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
                break;
        }
    }
}

void func_80A6C7C0(EnFall* this, GlobalContext* globalCtx) {
    static s32 D_80A6E4B0 = 0;

    if (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 1 && globalCtx->csCtx.unk_12 == 0) {
        switch (D_80A6E4B0) {
            case 0:
                if (globalCtx->csCtx.state != 0) {
                    D_80A6E4B0 = D_80A6E4B0 + 2;
                }
                break;
            case 2:
                if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA) && CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT) &&
                    CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG) && CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
                    if (gSaveContext.weekEventReg[0x5D] & 4) {
                        if (ActorCutscene_GetCanPlayNext(0xC)) {
                            ActorCutscene_Start(0xC, &this->actor);
                            D_80A6E4B0 += 1;
                        } else {
                            ActorCutscene_SetIntentToPlay(0xC);
                        }
                    } else if (ActorCutscene_GetCanPlayNext(0xB)) {
                        ActorCutscene_Start(0xB, &this->actor);
                        gSaveContext.weekEventReg[0x5D] |= 4;
                        D_80A6E4B0 += 1;
                    } else {
                        ActorCutscene_SetIntentToPlay(0xB);
                    }
                } else if (globalCtx->csCtx.frames >= 0x641) {
                    globalCtx->nextEntranceIndex = 0x2C00;
                    gSaveContext.nextCutsceneIndex = 0xFFF2;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 2;
                    gSaveContext.nextTransition = 2;
                    D_80A6E4B0 = 9;
                }
                break;
            case 9:
                globalCtx->csCtx.frames -= 1;
                break;
        }
    }
}

void EnFall_CrashingMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    func_80A6C7C0(this, globalCtx);
    if (func_800EE29C(globalCtx, 0x85)) {
        if (func_800EE29C(globalCtx, 0x85) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 1) {
            this->actor.draw = NULL;
        } else {
            this->actor.draw = EnFall_Moon_Draw;
            if (func_800EE29C(globalCtx, 0x85) &&
                globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 2) {
                func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x85));
            }
        }
    } else {
        this->actor.draw = NULL;
    }
}

void EnFall_StoppedOpenMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x85)) {
        switch (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0) {
            case 3:
                if (this->unk_150 == 0.0f) {
                    Audio_PlayActorSound2(&this->actor, NA_SE_EV_MOON_EYE_FLASH);
                }
                this->unk_150 += 0.033333335f;
                if (this->unk_150 > 1.0f) {
                    this->unk_150 = 1.0f;
                }
                break;
            case 4:
                this->actor.draw = EnFall_OpenMouthMoon_Draw;
                break;
        }
    }
}

void EnFall_StoppedClosedMouthMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x85)) {
        switch (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0) {
            case 2:
                func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x85));
                break;
            case 4:
                this->actor.draw = NULL;
                break;
        }
    }
    if (globalCtx->sceneNum == SCENE_OKUJOU && gSaveContext.sceneSetupIndex == 2) {
        switch (globalCtx->csCtx.unk_12) {
            case 0:
                switch (globalCtx->csCtx.frames) {
                    case 0x424:
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_MOON_SCREAM1);
                        break;
                    case 0x441:
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_MOON_CRY);
                        break;
                    case 0x517:
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SLIP_MOON);
                        break;
                }
                if (globalCtx->csCtx.frames >= 0x479) {
                    func_800B9010(&this->actor, NA_SE_EV_FALL_POWER - SFX_FLAG);
                }
                break;
            case 1:
                switch (globalCtx->csCtx.frames) {
                    case 0x231:
                        Audio_PlayActorSound2(&this->actor, NA_SE_EN_MOON_SCREAM1);
                        break;
                    case 0x24E:
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_MOON_CRY);
                        break;
                    case 0x2E1:
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SLIP_MOON);
                        break;
                }
                if (globalCtx->csCtx.frames >= 0x28A) {
                    func_800B9010(&this->actor, NA_SE_EV_FALL_POWER - SFX_FLAG);
                }
                break;
        }
    }
}

void EnFall_ClockTowerOrTitleScreenMoon_PerformCutsceneActions(EnFall* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0 && globalCtx->sceneNum == SCENE_OKUJOU) {
        func_800B9010(&this->actor, NA_SE_EV_MOON_FALL - SFX_FLAG);
    }
}

// TODO: Figure out what the heck is actually happening here
// Does this actually do anything in-game?
void EnFall_UnspecifiedMoon_Act(EnFall* this, GlobalContext* globalCtx) {
    u16 currentDay;

    if (func_800EE29C(globalCtx, 0x85)) {
        if (func_800EE29C(globalCtx, 0x85) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 1) {
            this->actor.draw = NULL;
        } else {
            Actor_SetScale(&this->actor, this->scale * 3.6f);
            this->actor.draw = EnFall_Moon_Draw;
            if (func_800EE29C(globalCtx, 0x85) &&
                globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 2) {
                func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x85));
            }
        }
    } else {
        if (this->actor.draw == NULL) {
            this->actor.draw = EnFall_Moon_Draw;
        }
        currentDay = CURRENT_DAY;
        if ((u16)this->currentDay != (u32)currentDay) {
            this->currentDay = currentDay;
            this->dayStartTime = gSaveContext.time;
        }
        EnFall_Moon_AdjustScaleAndPosition(this, globalCtx);
    }
}

void EnFall_MoonsTear_Initialize(EnFall* this) {
    s32 pad[2];

    this->actor.draw = EnFall_MoonsTear_Draw;
    if (this->actor.child != NULL) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.child->focus.pos);
    }
    this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.world.rot.x = Math_Vec3f_Pitch(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.speedXZ = Math_Vec3f_DistXYZ(&this->actor.world.pos, &this->actor.home.pos) / 82.0f;
    this->actor.shape.rot.x = this->actor.world.rot.x;
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void EnFall_DoNothing(EnFall* this, GlobalContext* globalCtx) {
}

void EnFall_MoonsTear_Fall(EnFall* this, GlobalContext* globalCtx) {
    s32 pad;

    if (func_800EE29C(globalCtx, 0x205) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x205)]->unk0 == 2 &&
        this->actor.draw == NULL) {
        EnFall_MoonsTear_Initialize(this);
    }
    if (this->actor.draw != NULL) {
        if (Math_Vec3f_StepTo(&this->actor.world.pos, &this->actor.home.pos, this->actor.speedXZ) <= 0.0f) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_GORON_BOUND_1);
            gSaveContext.weekEventReg[0x4A] |= 0x80;
            gSaveContext.weekEventReg[0x4A] |= 0x20;
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TEST, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, -2);
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, CLEAR_TAG_LARGE_EXPLOSION);
            this->actor.draw = NULL;
            this->actionFunc = EnFall_DoNothing;
        } else {
            func_800B9010(&this->actor, NA_SE_EV_MOONSTONE_FALL - SFX_FLAG);
        }
    }
}

void EnFall_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    this->actionFunc(this, globalCtx);
}

void EnFall_FireBall_UpdateVertexNormals(f32 arg0) {
    static u8 D_80A6E4B4[] = { 0x04, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x03, 0x00,
                               0x01, 0x01, 0x01, 0x04, 0x00, 0x04, 0x00, 0x01, 0x01, 0x01, 0x03, 0x00, 0x03, 0x00, 0x01,
                               0x01, 0x01, 0x04, 0x04, 0x01, 0x01, 0x00, 0x04, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
                               0x01, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,
                               0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00,
                               0x00, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04, 0x00, 0x04,
                               0x00, 0x01, 0x01, 0x01, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
                               0x01, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x01,
                               0x01, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x02, 0x01,
                               0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x02, 0x01, 0x01,
                               0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02,
                               0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00,
                               0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00 };
    u8* phi_a0;
    u8 unk[5];
    Vtx* vertices;
    s32 i;

    vertices = Lib_SegmentedToVirtual(&D_060004C0);
    if (arg0 > 1.0f) {
        arg0 = 1.0f;
    }
    unk[0] = 0;
    unk[1] = (s8)(255.0f * arg0);
    unk[2] = (s8)(155.0f * arg0);
    unk[3] = (s8)(104.0f * arg0);
    unk[4] = (s8)(54.0f * arg0);

    for (i = 0; i < 209; i++, vertices++) {
        vertices->v.cn[3] = unk[D_80A6E4B4[i]];
    }
}

void EnFall_FireBall_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 0 && globalCtx->csCtx.unk_12 == 2) {
        globalCtx->skyboxCtx.rotY -= 0.05f;
    }

    if (func_800EE29C(globalCtx, 0x1C2)) {
        this->actor.draw = EnFall_FireBall_Draw;
        if (this->unk_154 & 1) {
            this->unk_150 += 0.01f;
            if (this->unk_150 > 1.0f) {
                this->unk_150 = 1.0f;
            }
        }
        func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x1C2));

        switch (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x1C2)]->unk0) {
            default:
                this->actor.draw = NULL;
                this->unk_158 = 0;
                break;
            case 2:
                if (this->unk_158 < 0x64) {
                    this->unk_158 += 4;
                }
                if (this->unk_158 >= 0x65) {
                    this->unk_158 = 0x64;
                }
                EnFall_FireBall_UpdateVertexNormals(this->unk_158 * 0.01f);
                break;
            case 3:
                if (this->unk_158 > 0) {
                    this->unk_158 -= 2;
                }
                if (this->unk_158 < 0) {
                    this->unk_158 = 0;
                }
                EnFall_FireBall_UpdateVertexNormals(this->unk_158 * 0.01f);
                break;
            case 4:
                this->unk_154 |= 1;
                break;
            case 5:
                break;
        }
    } else {
        this->actor.draw = NULL;
    }
    if (func_800EE29C(globalCtx, 0x1C2) && this->unk_158 > 0) {
        func_8019F128(NA_SE_EV_MOON_FALL_LAST - SFX_FLAG);
    }
    Actor_SetScale(&this->actor, this->scale * 1.74f);
}

void EnFall_RisingDebris_UpdateParticles(EnFall* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        if (debrisParticles[i].dListIndex < 3) {
            debrisParticles[i].pos.x += debrisParticles[i].velocity.x;
            debrisParticles[i].pos.y += debrisParticles[i].velocity.y;
            debrisParticles[i].pos.z += debrisParticles[i].velocity.z;
            debrisParticles[i].rot.x += 0x64;
            debrisParticles[i].rot.y += 0xC8;
            debrisParticles[i].rot.z += 0x12C;
            if ((this->actor.world.pos.y + 3000.0f) < debrisParticles[i].pos.y) {
                debrisParticles[i].dListIndex = 3;
                this->unk_158 -= 1;
            }
        }
    }
}

s32 EnFall_RisingDebris_InitializeParticles(EnFall* this) {
    s16 sp2E;
    s32 i;
    f32 temp_f16;

    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        if (debrisParticles[i].dListIndex >= 3) {
            debrisParticles[i].dListIndex = (s32)Rand_ZeroFloat(3.0f);
            debrisParticles[i].pos.x = this->actor.world.pos.x;
            debrisParticles[i].pos.y = this->actor.world.pos.y;
            debrisParticles[i].pos.z = this->actor.world.pos.z;
            sp2E = randPlusMinusPoint5Scaled(65536.0f);
            temp_f16 = (1.0f - (Rand_ZeroFloat(1.0f) * Rand_ZeroFloat(1.0f))) * 3000.0f;
            debrisParticles[i].pos.x += Math_SinS(sp2E) * temp_f16;
            debrisParticles[i].pos.z += Math_CosS(sp2E) * temp_f16;
            debrisParticles[i].velocity.x = 0.0f;
            debrisParticles[i].velocity.z = 0.0f;
            debrisParticles[i].velocity.y = 80.0f;
            debrisParticles[i].rot.x = randPlusMinusPoint5Scaled(65536.0f);
            debrisParticles[i].rot.y = randPlusMinusPoint5Scaled(65536.0f);
            debrisParticles[i].rot.z = randPlusMinusPoint5Scaled(65536.0f);
            this->unk_158 += 1;
            return 1;
        }
    }

    return 0;
}

void EnFall_RisingDebris_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (func_800EE29C(globalCtx, 0x1C3)) {
        if (func_800EE29C(globalCtx, 0x1C3) &&
            globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x1C3)]->unk0 == 2) {
            EnFall_RisingDebris_UpdateParticles(this);
            EnFall_RisingDebris_InitializeParticles(this);
        } else if (this->unk_158 != 0) {
            EnFall_RisingDebris_ResetParticles(this);
        }
    } else if (thisx->home.rot.x != 0) {
        EnFall_RisingDebris_UpdateParticles(this);
        EnFall_RisingDebris_InitializeParticles(this);
    }
}

void EnFall_FireRing_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (func_800EE29C(globalCtx, 0x1C2) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x1C2)]->unk0 == 5) {
        if (!(this->unk_154 & 2)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_IT_DM_RING_EXPLOSION);
        }
        this->unk_154 |= 2;
    }
    if (this->unk_154 & 2) {
        this->unk_150 += 0.033333335f;
        if (this->unk_150 > 1.0f) {
            this->unk_150 = 1.0f;
        }
        if (this->actor.scale.x < 18.0f) {
            this->actor.scale.x += 0.2f;
        }
        this->actor.scale.z = this->actor.scale.x;
        this->actor.scale.y = Math_SinS(this->unk_15C) * 5.0f;
        if (this->unk_15C < 0x4000) {
            this->unk_15C += 0x147;
        }
    }
}

void EnFall_Moon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_80A6E588[] = { 1800.0f, 1000.0f, 4250.0f };
    EnFall* this = THIS;
    s32 temp_v1;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Matrix_MultiplyVector3fByState(D_80A6E588, &this->actor.focus.pos);
    temp_v1 = (this->unk_150 * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, temp_v1, temp_v1, temp_v1, 255); // this lights up the eyes
    gSPDisplayList(POLY_OPA_DISP++, D_060077F0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_OpenMouthMoon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 temp_v1;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    temp_v1 = (this->unk_150 * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, temp_v1, temp_v1, temp_v1, 255);
    gSPDisplayList(POLY_OPA_DISP++, D_06002970);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_LodMoon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFall* this = THIS;
    s32 temp_v1;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 20, 25, 30, 0, 0x3E7, 0x3200);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    temp_v1 = (this->unk_150 * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, temp_v1, temp_v1, temp_v1, 255);
    gSPDisplayList(POLY_OPA_DISP++, D_060010E0);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gSPDisplayList(POLY_OPA_DISP++, D_06001158);
    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A6DC20(Actor* thisx, GlobalContext* globalCtx) {
    EnFall_LodMoon_Draw(thisx, globalCtx);
}

void func_80A6DC40(Actor* thisx, GlobalContext* globalCtx) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 zTranslation;
    f32 yTranslation;
    f32 xTranslation;

    temp_f0 = Actor_DistanceToPoint(thisx, &globalCtx->view.eye);
    if (temp_f0 > 9000.0f) {
        temp_f0_2 = 9000.0f / temp_f0;
        xTranslation = (-(globalCtx->view.eye.x - thisx->world.pos.x) * temp_f0_2) + globalCtx->view.eye.x;
        yTranslation = (-(globalCtx->view.eye.y - thisx->world.pos.y) * temp_f0_2) + globalCtx->view.eye.y;
        zTranslation = (-(globalCtx->view.eye.z - thisx->world.pos.z) * temp_f0_2) + globalCtx->view.eye.z;
        Matrix_InsertTranslation(xTranslation, yTranslation, zTranslation, MTXMODE_NEW);
        Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, MTXMODE_APPLY);
        Matrix_RotateY(thisx->shape.rot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(thisx->shape.rot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(thisx->shape.rot.z, MTXMODE_APPLY);
    }
    EnFall_LodMoon_Draw(thisx, globalCtx);
}

void EnFall_FireBall_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFall* this = THIS;
    u32 gameplayFrames = globalCtx->gameplayFrames;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);
    this->unk_15C += (s32)(4.0f + (this->unk_150 * 12.0f));
    this->unk_15E += (s32)(2.0f + (this->unk_150 * 6.0f));
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, (s32)(((1.0f - this->unk_150) * 160.0f) + (255.0f * this->unk_150)),
                    (s32)((70.0f * (1.0f - this->unk_150)) + (255.0f * this->unk_150)),
                    (s32)(70.0f * (1.0f - this->unk_150)), 255);
    gDPSetEnvColor(POLY_XLU_DISP++, (s32)(((1.0f - this->unk_150) * 50.0f) + (200.0f * this->unk_150)),
                   (s32)(20.0f * (1.0f - this->unk_150)), (s32)(20.0f * (1.0f - this->unk_150)), 255);
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, gameplayFrames, -this->unk_15E, 0x40, 0x40, 1,
                                -gameplayFrames, -this->unk_15C, 0x40, 0x40));
    gSPSegment(POLY_XLU_DISP++, 0x0A,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, gameplayFrames * 2, -this->unk_15C, 0x40, 0x40, 1,
                                -gameplayFrames * 2, -this->unk_15C, 0x40, 0x40));
    gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
    gSPDisplayList(POLY_XLU_DISP++, D_060011D0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_RisingDebris_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Gfx* D_80A6E594[] = { D_06000220, D_06000428, D_06000498 };
    EnFall* this = THIS;
    f32 scale;
    s32 i;

    scale = this->scale * 0.06f;
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, D_06000198);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 0x00, 0x00, 0x00, 255);
    for (i = 0; i < ARRAY_COUNT(debrisParticles); i++) {
        if (debrisParticles[i].dListIndex < 3) {
            Matrix_InsertTranslation(debrisParticles[i].pos.x, debrisParticles[i].pos.y, debrisParticles[i].pos.z,
                                     MTXMODE_NEW);
            Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
            Matrix_InsertRotation(debrisParticles[i].rot.x, debrisParticles[i].rot.y, debrisParticles[i].rot.z,
                                  MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, D_80A6E594[debrisParticles[i].dListIndex]);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFall_FireRing_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFall* this = THIS;

    if (!(this->unk_150 <= 0.0f)) {
        if (this->unk_150 > 1.0f) {
            this->unk_150 = 1.0f;
        }
        OPEN_DISPS(globalCtx->state.gfxCtx);
        AnimatedMat_DrawXlu(globalCtx, Lib_SegmentedToVirtual(&D_06004E38));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C2DC(globalCtx->state.gfxCtx);
        gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
        gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, (s32)(this->unk_150 * 255.0f));
        gSPDisplayList(POLY_XLU_DISP++, D_06003C30);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnFall_MoonsTear_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06001220));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, D_06000400);
    Matrix_Scale(3.0f, 3.0f, 6.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_XLU_DISP++, D_060004C8);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
