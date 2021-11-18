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

void func_80A6C3FC(EnFall* this, GlobalContext* globalCtx);
void func_80A6C9A8(EnFall* this, GlobalContext* globalCtx);
void func_80A6CA9C(EnFall* this, GlobalContext* globalCtx);
void func_80A6CB74(EnFall* this, GlobalContext* globalCtx);
void func_80A6CD38(EnFall* this, GlobalContext* globalCtx);
void func_80A6CD74(EnFall* this, GlobalContext* globalCtx);
void func_80A6CF60(EnFall* this, GlobalContext* globalCtx);
void func_80A6CF70(EnFall* this, GlobalContext* globalCtx);
void func_80A6D220(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D88C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DD3C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D698(Actor* thisx, GlobalContext* globalCtx);
void func_80A6E07C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DC20(Actor* thisx, GlobalContext* globalCtx);
void func_80A6DC40(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D75C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6E214(Actor* thisx, GlobalContext* globalCtx);
void func_80A6D98C(Actor* thisx, GlobalContext* globalCtx);
void func_80A6E37C(Actor* thisx, GlobalContext* globalCtx);

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

static s32 D_80A6E4B0 = 0x00000000;

static u8 D_80A6E4B4[] = {
    0x04, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x03, 0x00, 0x01, 0x01, 0x01, 0x04,
    0x00, 0x04, 0x00, 0x01, 0x01, 0x01, 0x03, 0x00, 0x03, 0x00, 0x01, 0x01, 0x01, 0x04, 0x04, 0x01, 0x01, 0x00, 0x04,
    0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00,
    0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04, 0x00, 0x04, 0x00, 0x01, 0x01, 0x01, 0x03,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02,
    0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x02, 0x01, 0x02, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x02, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
    0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01,
    0x02, 0x02, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00
};

static u8 D_80A6E584[] = { 0x00, 0x00, 0x00, 0x00 };

static Vec3f D_80A6E588[] = { 1800.0f, 1000.0f, 4250.0f };

static s32 D_80A6E594[] = { 0x06000220, 0x06000428, 0x06000498 };

extern UNK_TYPE D_06000198;
extern Vtx D_060004C0[];
extern Gfx D_060010E0[];
extern Gfx D_06001158[];
extern Gfx D_060011D0[];
extern UNK_TYPE D_06001220;
extern Gfx D_06002970[];
extern Gfx D_06003C30[];
extern UNK_TYPE D_06004E38;
extern Gfx D_060077F0[];

void func_80A6BF90(EnFall* this, GlobalContext* globalCtx) {
    u16 temp_v0;
    u16 temp_v1;
    f32 phi_f0;

    temp_v0 = gSaveContext.time;
    temp_v1 = this->unk_144;
    if (temp_v0 < temp_v1) {
        phi_f0 = 1.0f - (((f32)temp_v1 - (f32)temp_v0) * (1.0f / 0x10000));
    } else {
        phi_f0 = ((f32)temp_v0 - (f32)temp_v1) * (1.0f / 0x10000);
    }
    switch (CURRENT_DAY) {
        case 0:
            Actor_SetScale(&this->actor, this->unk_14C * 1.2f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 1:
            Actor_SetScale(&this->actor, this->unk_14C * 2.4f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 2:
            Actor_SetScale(&this->actor, this->unk_14C * 3.6f);
            this->actor.world.pos.y = this->actor.home.pos.y;
            break;
        case 3:
            Actor_SetScale(&this->actor, this->unk_14C * 3.6f);
            if (EN_FALL_TYPE(&this->actor) == 0xC) {
                this->actor.world.pos.y = this->actor.home.pos.y + (phi_f0 * 6700.0f * (this->unk_14C * 6.25f));
            } else {
                this->actor.world.pos.y = this->actor.home.pos.y - (phi_f0 * 6700.0f * (this->unk_14C * 6.25f));
            }
            break;
    }
}

// bss function
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C1DC.s")

void EnFall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 objectIndex;

    this->unk_150 = 0.0f;
    this->unk_154 = 0;
    switch (EN_FALL_SCALE(&this->actor)) {
        case 1:
            this->unk_14C = 0.08f;
            break;
        case 2:
            this->unk_14C = 0.04f;
            break;
        case 3:
            this->unk_14C = 0.02f;
            break;
        case 4:
            this->unk_14C = 0.01f;
            break;
        default:
            this->unk_14C = 0.16f;
            break;
    }
    switch (EN_FALL_TYPE(&this->actor)) {
        case 5:
        case 6:
        case 12:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_LODMOON);
            break;
        case 8:
            objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MOONSTON);
            break;
        case 10:
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
    this->unk_148 = objectIndex;
    this->actionFunc = func_80A6C3FC;
}

void EnFall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

Actor* func_80A6C3AC(GlobalContext* globalCtx) {
    Actor* temp_v1;

    temp_v1 = globalCtx->actorCtx.actorList[ACTORCAT_ITEMACTION].first;
    while (temp_v1 != NULL) {
        if (temp_v1->id == ACTOR_EN_FALL && EN_FALL_TYPE(temp_v1) == 0) {
            return temp_v1;
        }
        temp_v1 = temp_v1->next;
    }
    return NULL;
}

void func_80A6C3FC(EnFall* this, GlobalContext* globalCtx) {
    Actor* temp_v0;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_148)) {
        this->actor.objBankIndex = this->unk_148;
        this->actionFunc = func_80A6CD74;
        switch (EN_FALL_TYPE(&this->actor)) {
            case 1:
                this->actor.draw = func_80A6D88C;
                this->actionFunc = func_80A6CD38;
                Actor_SetScale(&this->actor, this->unk_14C);
                break;
            case 7:
                this->actor.draw = func_80A6D88C;
                this->actionFunc = func_80A6CB74;
                Actor_SetScale(&this->actor, this->unk_14C * 3.0f);
                if ((gSaveContext.weekEventReg[0x19] & 2) == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case 9:
                this->actionFunc = func_80A6CD38;
                Actor_SetScale(&this->actor, this->unk_14C * 3.0f);
                this->actor.draw = func_80A6D88C;
                if ((gSaveContext.weekEventReg[0x19] & 2) != 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case 2:
                this->actor.draw = func_80A6D88C;
                Actor_SetScale(&this->actor, this->unk_14C * 5.3999996f);
                this->actionFunc = func_80A6C9A8;
                break;
            case 3:
                this->actor.update = func_80A6D220;
                this->actor.draw = func_80A6DD3C;
                this->unk_14C = 1.0f;
                this->actor.shape.rot.z = 0;
                this->unk_150 = 0.0f;
                this->unk_158 = 0x64;
                this->actor.shape.rot.x = this->actor.shape.rot.z;
                break;
            case 4:
                this->actor.update = func_80A6D698;
                this->actor.draw = func_80A6E07C;
                this->unk_14C = 1.0f;
                func_80A6C1DC(this);
                Actor_SetScale(&this->actor, 1.0f);
                this->actor.shape.rot.x = 0;
                break;
            case 5:
                this->actor.draw = func_80A6DC20;
                this->unk_144 = 0x4000;
                this->unk_146 = CURRENT_DAY;
                func_80A6BF90(this, globalCtx);
                break;
            case 6:
            case 12:
                this->actor.draw = func_80A6DC40;
                this->unk_144 = 0x4000;
                this->unk_146 = CURRENT_DAY;
                func_80A6BF90(this, globalCtx);
                break;
            case 8:
                this->actor.update = EnFall_Update;
                this->actor.draw = NULL;
                this->actionFunc = func_80A6CF70;
                Actor_SetScale(&this->actor, 0.02f);
                if ((globalCtx->actorCtx.unk5 & 2) == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                temp_v0 = func_80A6C3AC(globalCtx);
                this->actor.child = temp_v0;
                if (temp_v0 == 0) {
                    Actor_MarkForDeath(&this->actor);
                }
                break;
            case 10:
                this->actor.draw = NULL;
                this->actionFunc = func_80A6CA9C;
                Actor_SetScale(&this->actor, this->unk_14C * 3.0f);
                break;
            case 11:
                this->actor.update = func_80A6D75C;
                this->actor.draw = func_80A6E214;
                Actor_SetScale(&this->actor, 0.2f);
                break;
            default:
                this->actor.draw = func_80A6D88C;
                this->unk_144 = 0x4000;
                this->unk_146 = CURRENT_DAY;
                func_80A6BF90(this, globalCtx);
                break;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6C7C0.s")

void func_80A6C9A8(EnFall* this, GlobalContext* globalCtx) {
    func_80A6C7C0(this, globalCtx);
    if (func_800EE29C(globalCtx, 0x85)) {
        if (func_800EE29C(globalCtx, 0x85) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 1) {
            this->actor.draw = NULL;
        } else {
            this->actor.draw = func_80A6D88C;
            if (func_800EE29C(globalCtx, 0x85) &&
                globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 2) {
                func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x85));
            }
        }
    } else {
        this->actor.draw = NULL;
    }
}

void func_80A6CA9C(EnFall* this, GlobalContext* globalCtx) {
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
                this->actor.draw = func_80A6D98C;
                break;
        }
    }
}

void func_80A6CB74(EnFall* this, GlobalContext* globalCtx) {
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

void func_80A6CD38(EnFall* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0 && globalCtx->sceneNum == SCENE_OKUJOU) {
        func_800B9010(&this->actor, NA_SE_EV_MOON_FALL - SFX_FLAG);
    }
}

void func_80A6CD74(EnFall* this, GlobalContext* globalCtx) {
    u16 currentDay;

    if (func_800EE29C(globalCtx, 0x85)) {
        if (func_800EE29C(globalCtx, 0x85) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 1) {
            this->actor.draw = NULL;
        } else {
            Actor_SetScale(&this->actor, this->unk_14C * 3.6f);
            this->actor.draw = func_80A6D88C;
            if (func_800EE29C(globalCtx, 0x85) &&
                globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x85)]->unk0 == 2) {
                func_800EDF24(&this->actor, globalCtx, func_800EE200(globalCtx, 0x85));
            }
        }
    } else {
        if (this->actor.draw == NULL) {
            this->actor.draw = func_80A6D88C;
        }
        currentDay = CURRENT_DAY;
        if ((u16)this->unk_146 != (u32)currentDay) {
            this->unk_146 = currentDay;
            this->unk_144 = gSaveContext.time;
        }
        func_80A6BF90(this, globalCtx);
    }
}

void func_80A6CECC(EnFall* this) {
    s32 pad[2];

    this->actor.draw = func_80A6E37C;
    if (this->actor.child != NULL) {
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.child->focus.pos);
    }
    this->actor.world.rot.y = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.world.rot.x = Math_Vec3f_Pitch(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.speedXZ = Math_Vec3f_DistXYZ(&this->actor.world.pos, &this->actor.home.pos) / 82.0f;
    this->actor.shape.rot.x = this->actor.world.rot.x;
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80A6CF60(EnFall* this, GlobalContext* globalCtx) {
}

void func_80A6CF70(EnFall* this, GlobalContext* globalCtx) {
    s32 pad;

    if (func_800EE29C(globalCtx, 0x205) && globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x205)]->unk0 == 2 &&
        this->actor.draw == NULL) {
        func_80A6CECC(this);
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
            this->actionFunc = func_80A6CF60;
        } else {
            func_800B9010(&this->actor, NA_SE_EV_MOONSTONE_FALL - SFX_FLAG);
        }
    }
}

void EnFall_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    this->actionFunc(this, globalCtx);
}

void func_80A6D100(f32 arg0) {
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

void func_80A6D220(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 0 && globalCtx->csCtx.unk_12 == 2) {
        globalCtx->skyboxCtx.rotY -= 0.05f;
    }

    if (func_800EE29C(globalCtx, 0x1C2)) {
        this->actor.draw = func_80A6DD3C;
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
                func_80A6D100(this->unk_158 * 0.01f);
                break;
            case 3:
                if (this->unk_158 > 0) {
                    this->unk_158 -= 2;
                }
                if (this->unk_158 < 0) {
                    this->unk_158 = 0;
                }
                func_80A6D100(this->unk_158 * 0.01f);
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
        func_8019F128(0x214F);
    }
    Actor_SetScale(&this->actor, this->unk_14C * 1.74f);
}

// bss function
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D444.s")

// bss function
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6D504.s")

void func_80A6D698(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;

    if (func_800EE29C(globalCtx, 0x1C3)) {
        if (func_800EE29C(globalCtx, 0x1C3) &&
            globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x1C3)]->unk0 == 2) {
            func_80A6D444(this);
            func_80A6D504(this);
        } else if (this->unk_158 != 0) {
            func_80A6C1DC(this);
        }
    } else if (thisx->home.rot.x != 0) {
        func_80A6D444(this);
        func_80A6D504(this);
    }
}

void func_80A6D75C(Actor* thisx, GlobalContext* globalCtx) {
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

void func_80A6D88C(Actor* thisx, GlobalContext* globalCtx) {
    EnFall* this = THIS;
    s32 temp_v1;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Matrix_MultiplyVector3fByState(D_80A6E588, &this->actor.focus.pos);
    temp_v1 = (this->unk_150 * 200.0f) + 40.0f;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, temp_v1, temp_v1, temp_v1, 255);
    gSPDisplayList(POLY_OPA_DISP++, D_060077F0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A6D98C(Actor* thisx, GlobalContext* globalCtx) {
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

void func_80A6DA7C(Actor* thisx, GlobalContext* globalCtx) {
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
    func_80A6DA7C(thisx, globalCtx);
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
    func_80A6DA7C(thisx, globalCtx);
}

void func_80A6DD3C(Actor* thisx, GlobalContext* globalCtx) {
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

// bss function
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E07C.s")

void func_80A6E214(Actor* thisx, GlobalContext* globalCtx) {
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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fall/func_80A6E37C.s")
