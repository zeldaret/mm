/*
 * File: z_bg_ingate.c
 * Overlay: ovl_Bg_Ingate
 * Description: Swamp Tour Boat
 */

#include "z_bg_ingate.h"
#include "objects/object_sichitai_obj/object_sichitai_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgIngate*)thisx)

void BgIngate_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIngate_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIngate_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIngate_Draw(Actor* thisx, GlobalContext* globalCtx);

Actor* BgIngate_FindActor(BgIngate* this, GlobalContext* globalCtx, u8 actorCat, s16 actorId);
s32 func_80953BEC(BgIngate* this);
void func_80953B40(BgIngate* this);
void func_80953F8C(BgIngate* this, GlobalContext* globalCtx);
void func_80953F9C(BgIngate* this, GlobalContext* globalCtx);
void func_809541B8(BgIngate* this, GlobalContext* globalCtx);
void func_809542A0(BgIngate* this, GlobalContext* globalCtx);
void func_80954340(BgIngate* this, GlobalContext* globalCtx);
void func_809543D4(BgIngate* this, GlobalContext* globalCtx);

const ActorInit Bg_Ingate_InitVars = {
    ACTOR_BG_INGATE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_SICHITAI_OBJ,
    sizeof(BgIngate),
    (ActorFunc)BgIngate_Init,
    (ActorFunc)BgIngate_Destroy,
    (ActorFunc)BgIngate_Update,
    (ActorFunc)BgIngate_Draw,
};

/**
 * @brief Searches for an actor based on the parameters given to the function. Returns Actor* of actor found or NULL
 *
 * @param this
 * @param globalCtx
 * @param actorCat - Category of Actor
 * @param actorId - ID of actor to search for
 * @return Actor*
 */
Actor* BgIngate_FindActor(BgIngate* this, GlobalContext* globalCtx, u8 actorCat, s16 actorId) {
    Actor* foundActor = NULL;
    Actor* tempActor;

    while (true) {
        foundActor = SubS_FindActor(globalCtx, foundActor, actorCat, actorId);

        if ((foundActor == NULL) || (((this != (BgIngate*)foundActor)) && (foundActor->update != NULL))) {
            break;
        }

        tempActor = foundActor->next;
        if (tempActor == NULL) {
            foundActor = NULL;
            break;
        }
        foundActor = tempActor;
    }

    return foundActor;
}

void func_80953B40(BgIngate* this) {
    s32 temp;

    if (!(gSaveContext.eventInf[3] & 0x20)) {
        this->unk180 = 0xFA0;
        this->unk168 = 4;
    } else {
        this->unk180 = 0x7D0;
        this->unk168 = 1;
    }
    temp = this->unk164->count - 2;
    this->unk184 = this->unk180 / temp;
    this->unk188 = 2;
    this->unk18C = 0;
    this->unk160 &= ~0x1;
    this->unk160 &= ~0x2;
}

s32 func_80953BEC(BgIngate* this) {
    f32 sp74[265];
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f unkVec;
    s16 yaw;

    func_8013AF00(sp74, 3, this->unk164->count + 3);
    if (!(this->unk160 & 1)) {
        unkVec = gZeroVec3f;
        func_8013B6B0(this->unk164, &this->unk17C, &this->unk18C, this->unk184, this->unk180, &this->unk188, sp74,
                      &unkVec, this->unk168);
        this->unk160 |= 1;
    } else {
        unkVec = this->unk170;
    }
    this->dyna.actor.world.pos.x = unkVec.x;
    this->dyna.actor.world.pos.z = unkVec.z;
    this->unk170 = gZeroVec3f;
    if (func_8013B6B0(this->unk164, &this->unk17C, &this->unk18C, this->unk184, this->unk180, &this->unk188, sp74,
                      &this->unk170, this->unk168) != 0) {
        this->unk160 |= 2;
    } else {
        sp68 = this->dyna.actor.world.pos;
        sp5C = this->unk170;
        yaw = Math_Vec3f_Yaw(&sp68, &sp5C);
        this->dyna.actor.world.rot.y = yaw;
        this->dyna.actor.shape.rot.y = yaw;
    }

    return false;
}

s32 func_80953DA8(BgIngate* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, CAM_ID_MAIN);

    if (gSaveContext.eventInf[3] & 0x20) {
        func_800B7298(globalCtx, &this->dyna.actor, 7);
    } else {
        gSaveContext.eventInf[4] |= 2;
    }
    func_800DFAC8(camera, 47);
    globalCtx->unk_1887C = 0x63;

    return false;
}

void func_80953E38(GlobalContext* globalCtx) {
    func_800DFAC8(Play_GetCamera(globalCtx, CAM_ID_MAIN), 1);

    if (!(gSaveContext.eventInf[3] & 0x20)) {
        gSaveContext.eventInf[4] &= (u8)~2;
    }

    globalCtx->unk_1887C = -1;
}

void func_80953EA4(BgIngate* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_800B7298(globalCtx, &this->dyna.actor, 0x3A);
    player->unk_3A0.x = this->dyna.actor.world.pos.x;
    player->unk_3A0.z = this->dyna.actor.world.pos.z;
    this->unk160 &= ~0x4;
    this->unk16A = 0x1E;
    this->actionFunc = func_80954340;
}

void func_80953F14(BgIngate* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.shape.rot.y = this->dyna.actor.shape.rot.y;
    player->actor.world.rot.y = player->actor.shape.rot.y;
    player->currentYaw = player->actor.shape.rot.y;
    player->actor.focus.rot.y = player->actor.shape.rot.y;
    this->unk160 |= 0x10;
    func_80953DA8(this, globalCtx);
    if (this->unk164 != 0) {
        func_80953B40(this);
    }
    this->unk16E = -1;
    this->actionFunc = func_80953F9C;
}

void func_80953F8C(BgIngate* this, GlobalContext* globalCtx) {
}

void func_80953F9C(BgIngate* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Camera* camera = Play_GetCamera(globalCtx, CAM_ID_MAIN);

    if (!(gSaveContext.eventInf[4] & 1)) {

        if (!(gSaveContext.eventInf[3] & 0x20) && (this->unk160 & 0x10) && (this->unk16C == 0)) {
            this->dyna.actor.textId = 0x9E3;
            Message_StartTextbox(globalCtx, this->dyna.actor.textId, NULL);
            this->unk160 &= ~0x10;
        }

        if (this->unk160 & 2) {

            if (this->unk164->unk1 != 0xFF) {
                func_80953E38(globalCtx);
                func_800B7298(globalCtx, &this->dyna.actor, 7);
                this->dyna.actor.textId = 0x9E4;
                Message_StartTextbox(globalCtx, this->dyna.actor.textId, NULL);
                this->unk16C += 1;
                gSaveContext.save.weekEventReg[90] |= 0x40;
                this->actionFunc = func_809543D4;
            } else {

                if (!(gSaveContext.eventInf[3] & 0x20)) {
                    gSaveContext.eventInf[4] &= (u8)~2;
                } else {
                    gSaveContext.eventInf[4] |= 1;
                }
                this->actionFunc = func_809542A0;
            }
        } else if ((ActorCutscene_GetCurrentIndex() == -1) && (this->unk164 != NULL)) {
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_CRUISER - SFX_FLAG);
            func_80953BEC(this);
        }
    }
    if (ActorCutscene_GetCurrentIndex() != this->unk16E) {
        if (ActorCutscene_GetCurrentIndex() != -1) {
            func_800DFAC8(camera, 1);
            player->stateFlags1 |= 0x20;
            globalCtx->actorCtx.unk5 &= ~0x4;
        } else {
            func_800DFAC8(camera, 47);
            player->stateFlags1 &= ~0x20;
        }
    }
    this->unk16E = ActorCutscene_GetCurrentIndex();
}

void func_809541B8(BgIngate* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk160 & 0x4) {
        if ((player->transformation == PLAYER_FORM_HUMAN) && (player->actor.bgCheckFlags & 1) &&
            (this->dyna.actor.xzDistToPlayer < 40.0f)) {
            if (this->dyna.actor.playerHeightRel > 15.0f) {
                func_800B7298(globalCtx, &this->dyna.actor, 7);
                this->dyna.actor.textId = 0x9E6;
                Message_StartTextbox(globalCtx, this->dyna.actor.textId, NULL);
                this->actionFunc = func_809543D4;
            }
        }
    } else if (!DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        this->unk160 |= 4;
    }
}

void func_809542A0(BgIngate* this, GlobalContext* globalCtx) {
    if (gSaveContext.eventInf[5] & 1) {
        globalCtx->nextEntranceIndex = 0xA820;
        gSaveContext.eventInf[5] &= (u8)~1;
    } else {
        globalCtx->nextEntranceIndex = 0xA810;
    }
    gSaveContext.nextCutsceneIndex = 0;
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 3;
    gSaveContext.nextTransition = 3;
    this->actionFunc = func_80953F8C;
    gSaveContext.save.weekEventReg[90] &= (u8)~0x40;
    func_800FE498();
}

void func_80954340(BgIngate* this, GlobalContext* globalCtx) {
    if (!DECR(this->unk16A)) {
        if (this->unk164 != 0) {
            func_800B7298(globalCtx, &this->dyna.actor, 6);
            this->unk164 = &globalCtx->setupPathList[this->unk164->unk1];
            func_80953F14(this, globalCtx);
            func_800FE484();
        }
    }
}

void func_809543D4(BgIngate* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);

    if (((talkState == 4) || (talkState == 5)) && Message_ShouldAdvance(globalCtx)) {
        switch (this->dyna.actor.textId) {
            case 0x9E4:
                this->dyna.actor.textId = 0x9E5;
                func_80151938(globalCtx, this->dyna.actor.textId);
                break;
            case 0x9E5:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_800B7298(globalCtx, &this->dyna.actor, 6);
                    this->unk160 &= ~0x4;
                    this->actionFunc = func_809541B8;
                    func_800FE498();
                    func_8019F208();
                } else {
                    if (this->unk164 != 0) {
                        this->unk164 = &globalCtx->setupPathList[this->unk164->unk1];
                    }
                    func_80953F14(this, globalCtx);
                    gSaveContext.save.weekEventReg[90] &= (u8)~0x40;
                    func_8019F230();
                }
                func_801477B4(globalCtx);
                break;
            case 0x9E6:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    func_80953EA4(this, globalCtx);
                    gSaveContext.save.weekEventReg[90] &= (u8)~0x40;
                    func_8019F208();
                } else {
                    this = this;
                    func_800B7298(globalCtx, &this->dyna.actor, 6);
                    this->unk160 &= ~0x4;
                    this->actionFunc = func_809541B8;
                    func_800FE498();
                    func_8019F230();
                }
                func_801477B4(globalCtx);
                break;
        }
    }
}

void BgIngate_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIngate* this = THIS;
    s32 phi_a2;
    Vec3s* sp38;
    Vec3f sp2C;
    Vec3f sp20;

    if (BgIngate_FindActor(this, globalCtx, ACTORCAT_BG, ACTOR_BG_INGATE) == NULL) {
        DynaPolyActor_Init(&this->dyna, 3);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gSichitaiBoatCol);
        this->unk160 = 0;
        this->unk160 |= 0x8;
        this->unk160 |= 0x10;
        Actor_SetScale(&this->dyna.actor, 1.0f);
        this->unk164 = SubS_GetAdditionalPath(globalCtx, BGINGATE_GET_FF(&this->dyna.actor), 0);
        this->dyna.actor.room = -1;
        if (gSaveContext.save.weekEventReg[20] & 2) {
            gSaveContext.save.weekEventReg[90] &= (u8)~0x40;
        }
        if (!(gSaveContext.eventInf[3] & 0x20) && (gSaveContext.save.weekEventReg[90] & 0x40)) {
            phi_a2 = 1;
            this->unk16C = 1;
            this->actionFunc = func_809541B8;
        } else {
            phi_a2 = 0;
            if (globalCtx->curSpawn == 6) {
                func_80953F14(this, globalCtx);
                if (gSaveContext.eventInf[3] & 0x20) {
                    func_80112AFC(globalCtx);
                } else {
                    gSaveContext.eventInf[4] |= 2;
                }
            } else {
                this->actionFunc = func_80953F8C;
            }
        }
        this->unk164 = SubS_GetAdditionalPath(globalCtx, BGINGATE_GET_FF(&this->dyna.actor), phi_a2);
        if (this->unk164 != 0) {
            sp38 = Lib_SegmentedToVirtual(this->unk164->points);
            Math_Vec3s_ToVec3f(&sp2C, &sp38[0]);
            Math_Vec3s_ToVec3f(&sp20, &sp38[1]);
            this->dyna.actor.world.rot.y = Math_Vec3f_Yaw(&sp2C, &sp20);
            this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
            this->dyna.actor.world.pos.x = sp2C.x;
            this->dyna.actor.world.pos.y = -15.0f;
            this->dyna.actor.world.pos.z = sp2C.z;
        }
        this->unk164 = SubS_GetAdditionalPath(globalCtx, BGINGATE_GET_FF(&this->dyna.actor), 0);
    } else {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void BgIngate_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIngate* this = THIS;

    if (this->unk160 & 8) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void BgIngate_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIngate* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgIngate_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gSichitaiBoat);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
