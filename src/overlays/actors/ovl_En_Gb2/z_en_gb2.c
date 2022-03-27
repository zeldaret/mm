/*
 * File: z_en_gb2.c
 * Overlay: ovl_En_Gb2
 * Description: Spirit House - Owner
 */

#include "z_en_gb2.h"
#include "objects/object_ps/object_ps.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnGb2*)thisx)

void EnGb2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGb2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B0FBF0(EnGb2* this, GlobalContext* globalCtx);
void func_80B0FEBC(EnGb2* this, GlobalContext* globalCtx);
void func_80B0FFA8(EnGb2* this, GlobalContext* globalCtx);
void func_80B10240(EnGb2* this, GlobalContext* globalCtx);
void func_80B10344(EnGb2* this, GlobalContext* globalCtx);
void func_80B10584(EnGb2* this, GlobalContext* globalCtx);
void func_80B10634(EnGb2* this, GlobalContext* globalCtx);
void func_80B10868(EnGb2* this, GlobalContext* globalCtx);
void func_80B10924(EnGb2* this, GlobalContext* globalCtx);
void func_80B109DC(EnGb2* this, GlobalContext* globalCtx);
void func_80B10A48(EnGb2* this, GlobalContext* globalCtx);
void func_80B10B5C(EnGb2* this, GlobalContext* globalCtx);
void func_80B10DAC(EnGb2* this, GlobalContext* globalCtx);
void func_80B10E98(EnGb2* this, GlobalContext* globalCtx);
void func_80B11048(EnGb2* this, GlobalContext* globalCtx);
void func_80B110F8(EnGb2* this, GlobalContext* globalCtx);
void func_80B111AC(EnGb2* this, GlobalContext* globalCtx);
void func_80B11268(EnGb2* this, GlobalContext* globalCtx);
void func_80B11344(EnGb2* this, GlobalContext* globalCtx);

const ActorInit En_Gb2_InitVars = {
    ACTOR_EN_GB2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_PS,
    sizeof(EnGb2),
    (ActorFunc)EnGb2_Init,
    (ActorFunc)EnGb2_Destroy,
    (ActorFunc)EnGb2_Update,
    (ActorFunc)EnGb2_Draw,
};

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ s16 unk_10;
} EnGbStruct; // size = 0x14

static EnGbStruct D_80B119B0[] = {
    { ACTOR_EN_PO_SISTERS, { 0.0f, 0.0f, 0.0f }, 0x300 },
    { ACTOR_EN_PO_SISTERS, { 100.0f, 0.0f, 0.0f }, 0x200 },
    { ACTOR_EN_PO_SISTERS, { -100.0f, 0.0f, 0.0f }, 0x100 },
    { ACTOR_EN_PO_SISTERS, { 0.0f, 0.0f, 0.0f }, 0 },
};

static f32 D_80B11A00[][4] = {
    { 0.0f, -13.0f, 549.0f, 0.0f },
    { -242.0f, -13.0f, 390.0f, -90.0f },
    { 0.0f, -13.0f, 148.0f, 180.0f },
    { 244.0f, -13.0f, 390.0f, 90.0f },
};

static ColliderCylinderInitType1 sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 40, 75, 0, { 0, 0, 0 } },
};

void func_80B0F5E0(EnGb2* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80B0F660(EnGb2* this, GlobalContext* globalCtx) {
    Actor* temp_v0;
    Actor* phi_s0 = NULL;

    while (true) {
        temp_v0 = SubS_FindActor(globalCtx, phi_s0, ACTORCAT_NPC, ACTOR_EN_GB2);
        if (temp_v0 == NULL) {
            break;
        }

        if ((EnGb2*)temp_v0 != this) {
            return true;
        }

        temp_v0 = temp_v0->next;
        if (temp_v0 == NULL) {
            break;
        }
        phi_s0 = temp_v0;
    };

    return false;
}

void func_80B0F6DC(EnGb2* this) {
    if (!(gSaveContext.save.weekEventReg[54] & 0x20)) {
        gSaveContext.save.weekEventReg[54] |= 0x20;
        this->unk_26E = 0x14D0;
    } else {
        this->unk_26E = 0x14D1;
    }
    this->unk_288 = 30;
    this->actionFunc = func_80B0FEBC;
}

void func_80B0F728(EnGb2* this, GlobalContext* globalCtx) {
    if (gSaveContext.eventInf[4] & 0x10) {
        func_80B0FBF0(this, globalCtx);
        this->unk_26E = 0x14E1;
        if (gSaveContext.eventInf[4] & 0x80) {
            this->unk_288 = 10;
        } else {
            this->unk_288 = 30;
        }
    } else if (gSaveContext.eventInf[4] & 0x20) {
        func_80B0FBF0(this, globalCtx);
        this->unk_26E = 0x14E0;
        this->unk_26C |= 2;
    } else {
        this->unk_26E = 0x14DC;
    }

    gSaveContext.eventInf[4] &= (u8)~0x10;
    gSaveContext.eventInf[4] &= (u8)~0x20;
    gSaveContext.eventInf[4] &= (u8)~0x40;
    this->actionFunc = func_80B10584;
}

u16 func_80B0F7FC(EnGb2* this) {
    switch (this->unk_26E) {
        case 0x14D0:
            return 0x14D1;

        case 0x14D1:
            if (gSaveContext.eventInf[4] & 0x80) {
                return 0x14E4;
            }

            if (gSaveContext.save.playerData.health > 48) {
                return 0x14D2;
            }

            this->unk_26C |= 2;
            return 0x14D3;

        case 0x14E4:
            if (gSaveContext.save.playerData.health > 48) {
                return 0x14D2;
            }

            this->unk_26C |= 2;
            return 0x14D3;

        case 0x14D2:
            if (gSaveContext.eventInf[4] & 0x80) {
                return 0x14E5;
            }
            return 0x14D4;

        case 0x14D4:
        case 0x14E5:
            return 0x14D5;

        case 0x14D8:
            return 0x14D9;

        case 0x14D9:
            return 0x14DA;
    }
    return 0;
}

u16 func_80B0F8F8(EnGb2* this) {
    switch (this->unk_26E) {
        case 0x14DC:
            this->unk_26C |= 2;
            return 0x14DD;

        case 0x14DD:
            return 0x14DE;

        case 0x14DE:
            this->unk_26C |= 2;
            gSaveContext.save.weekEventReg[54] |= 0x80;
            return 0x14DF;

        case 0x14E1:
            return 0x14E2;
    }
    return 0;
}

u16 func_80B0F97C(EnGb2* this) {
    switch (this->unk_26E) {
        case 0x14F5:
            return 0x14F6;

        case 0x14F6:
            return 0x14F7;

        case 0x14F7:
            gSaveContext.save.weekEventReg[76] |= 0x80;
            this->unk_26C |= 2;
            return 0x14F8;

        case 0x14F9:
            return 0x14FA;

        case 0x14FA:
            this->unk_26C |= 2;
            return 0x14FB;
    }
    return 0;
}

void func_80B0FA04(EnGb2* this) {
    this->unk_282[0] = this->actor.cutscene;
    this->unk_282[1] = ActorCutscene_GetAdditionalCutscene(this->unk_282[0]);
    this->unk_282[2] = ActorCutscene_GetAdditionalCutscene(this->unk_282[1]);
}

s32 func_80B0FA48(EnGb2* this, GlobalContext* globalCtx) {
    switch (Player_GetMask(globalCtx)) {
        case PLAYER_MASK_GIBDO:
            this->unk_26C |= 4;
            this->unk_26E = 0x14E6;
            return false;

        case PLAYER_MASK_GARO:
            this->unk_26C |= 8;
            this->unk_26E = 0x14E6;
            return false;

        case PLAYER_MASK_CAPTAIN:
            if (!(gSaveContext.save.weekEventReg[80] & 0x40)) {
                this->unk_26E = 0x14EB;
                return false;
            }
            this->unk_26E = 0x14EE;
            return true;
    }

    if (!(gSaveContext.save.weekEventReg[80] & 0x20)) {
        this->unk_26E = 0x14EF;
        return false;
    } else {
        this->unk_26E = 0x14F4;
        return true;
    }
}

u16 func_80B0FB24(EnGb2* this) {
    switch (this->unk_26E) {
        case 0x14E6:
            if (this->unk_26C & 4) {
                return 0x14E7;
            }

            if (this->unk_26C & 8) {
                return 0x14E9;
            }

        case 0x14E7:
            this->unk_26C |= 2;
            return 0x14E8;

        case 0x14E9:
            this->unk_26C |= 2;
            return 0x14EA;

        case 0x14EB:
            return 0x14EC;

        case 0x14EC:
            this->unk_26C |= 2;
            return 0x14ED;

        case 0x14EF:
            return 0x14F0;

        case 0x14F0:
            return 0x14F1;

        case 0x14F1:
            return 0x14F2;

        case 0x14F2:
            this->unk_26C |= 2;
            return 0x14F3;
    }
    return 0;
}

void func_80B0FBF0(EnGb2* this, GlobalContext* globalCtx) {
    Vec3f sp90[4] = {
        { 120.0f, 0.0f, 800.0f },
        { -120.0f, 0.0f, 750.0f },
        { 60.0f, 0.0f, 750.0f },
        { -60.0f, 0.0f, 800.0f },
    };
    Vec3s sp78[] = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 },
    };
    s32 sp68[] = {
        0x1000,
        0x1100,
        0x1200,
        0x1300,
    };
    s16 i;
    s16 end = ARRAY_COUNT(sp90);

    for (i = 0; i < end; i++) {
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_PO_SISTERS, sp90[i].x, sp90[i].y,
                           sp90[i].z, sp78[i].x, sp78[i].y, sp78[i].z, sp68[i]);
    }
}

void func_80B0FD8C(EnGb2* this, GlobalContext* globalCtx) {
    this->unk_280++;
    this->unk_268 = this->actor.child;
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_PO_SISTERS,
                       D_80B119B0[this->unk_280].unk_04.x, D_80B119B0[this->unk_280].unk_04.y,
                       D_80B119B0[this->unk_280].unk_04.z, 0, 0, 0, D_80B119B0[this->unk_280].unk_10);
}

void func_80B0FE18(GlobalContext* globalCtx) {
    func_800FD750(0x38);
    globalCtx->nextEntranceIndex = 0x9C10;
    globalCtx->unk_1887F = 0x40;
    gSaveContext.nextTransition = 0x40;
    globalCtx->sceneLoadFlag = 0x14;
}

void func_80B0FE7C(GlobalContext* globalCtx) {
    globalCtx->nextEntranceIndex = 0x9C20;
    globalCtx->unk_1887F = 0x40;
    gSaveContext.nextTransition = 0x40;
    globalCtx->sceneLoadFlag = 0x14;
}

void func_80B0FEBC(EnGb2* this, GlobalContext* globalCtx) {
    if ((globalCtx->msgCtx.ocarinaMode == 3) && (globalCtx->msgCtx.unk1202E == 7)) {
        globalCtx->msgCtx.ocarinaMode = 4;
        gSaveContext.eventInf[4] |= 0x80;
        this->unk_26E = 0x14D1;
        this->unk_288 = 10;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
        this->actionFunc = func_80B0FFA8;
    } else if ((this->actor.xzDistToPlayer < 300.0f) || this->actor.isTargeted) {
        func_800B863C(&this->actor, globalCtx);
    }
}

void func_80B0FFA8(EnGb2* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            if (this->unk_26C & 2) {
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_26E = 0x14D1;
                this->unk_288 = 30;
                gSaveContext.eventInf[4] &= (u8)~0x80;
                this->unk_26C &= ~2;
                this->actionFunc = func_80B0FEBC;
            } else {
                this->unk_26E = func_80B0F7FC(this);
                Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
            }
        }
    } else if ((temp_v0 == 4) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_26E == 0x14D5) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    if (gSaveContext.save.playerData.rupees < this->unk_288) {
                        play_sound(NA_SE_SY_ERROR);
                        this->unk_26E = 0x14D7;
                        this->unk_26C |= 2;
                        Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
                    } else {
                        func_8019F208();
                        this->unk_26E = 0x14D8;
                        Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
                    }
                    break;

                case 1:
                    func_8019F230();
                    this->unk_26E = 0x14D6;
                    this->unk_26C |= 2;
                    Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
                    break;
            }
        } else if (this->unk_26E == 0x14DA) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    func_801159EC(-this->unk_288);
                    globalCtx->msgCtx.msgMode = 0x43;
                    globalCtx->msgCtx.unk12023 = 4;
                    func_800B7298(globalCtx, NULL, 7);
                    this->actionFunc = func_80B11344;
                    break;

                case 1:
                    func_8019F230();
                    this->unk_26E = 0x14DB;
                    this->unk_26C |= 2;
                    Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
                    break;
            }
        }
    }
}

void func_80B10240(EnGb2* this, GlobalContext* globalCtx) {
    this->unk_27C = D_80B119B0[this->unk_280].unk_00;
    this->unk_27E = D_80B119B0[this->unk_280].unk_10;
    this->unk_282[0] = this->actor.cutscene;
    this->unk_268 = NULL;
    if (ActorCutscene_GetCanPlayNext(this->unk_282[0])) {
        ActorCutscene_Start(this->unk_282[0], &this->actor);
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, this->unk_27C,
                           D_80B119B0[this->unk_280].unk_04.x, D_80B119B0[this->unk_280].unk_04.y,
                           D_80B119B0[this->unk_280].unk_04.z, 0, 0, 0, this->unk_27E);
        if (this->unk_280 == 0) {
            func_8010E9F0(1, 180);
        }
        this->actionFunc = func_80B10344;
    } else {
        ActorCutscene_SetIntentToPlay(this->unk_282[0]);
    }
}

void func_80B10344(EnGb2* this, GlobalContext* globalCtx) {
    if (this->unk_280 == 1) {
        func_80B0FD8C(this, globalCtx);
    }

    if (this->unk_280 == 2) {
        if ((this->unk_268 != NULL) && (this->unk_268->update == NULL)) {
            this->unk_268 = NULL;
            this->unk_26C |= 0x400;
        }
    }

    if ((this->actor.child != NULL) && (this->actor.child->update == NULL)) {
        this->actor.child = NULL;
        this->unk_26C |= 0x200;
    }

    if (this->unk_26C & 0x200) {
        if (this->unk_280 == 3) {
            this->unk_26C &= ~0x200;
            gSaveContext.unk_3DD0[1] = 5;
            func_800FE498();
            gSaveContext.eventInf[4] |= 0x40;
            func_80B0FE7C(globalCtx);
        } else if (this->unk_280 == 2) {
            if (this->unk_26C & 0x400) {
                this->unk_280++;
                this->unk_26C &= ~0x200;
                this->unk_26C &= ~0x400;
                this->actionFunc = func_80B10240;
            }
        } else {
            this->unk_280++;
            this->unk_26C &= ~0x200;
            this->actionFunc = func_80B10240;
        }
    }

    if (gSaveContext.save.playerData.health < 49) {
        gSaveContext.unk_3DD0[1] = 5;
        gSaveContext.eventInf[4] |= 0x40;
        gSaveContext.eventInf[4] |= 0x20;

        if ((this->unk_268 != NULL) && (this->unk_268->update == NULL)) {
            this->unk_268 = NULL;
        }

        if ((this->actor.child != NULL) && (this->actor.child->update == NULL)) {
            this->actor.child = NULL;
        }

        func_80B0FE7C(globalCtx);
    } else if (gSaveContext.unk_3DE0[1] == 0) {
        gSaveContext.unk_3DD0[1] = 5;
        gSaveContext.eventInf[4] |= 0x40;
        gSaveContext.eventInf[4] |= 0x10;

        if ((this->unk_268 != NULL) && (this->unk_268->update == NULL)) {
            this->unk_268 = NULL;
        }

        if ((this->actor.child != NULL) && (this->actor.child->update == NULL)) {
            this->actor.child = NULL;
        }

        func_80B0FE7C(globalCtx);
    }
}

void func_80B10584(EnGb2* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = func_80B10634;
    } else if (this->actor.xzDistToPlayer < 300.0f) {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, globalCtx, 300.0f);
    }
}

void func_80B10634(EnGb2* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            if (this->unk_26C & 2) {
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->unk_26C &= ~2;
                if (this->unk_26E == 0x14DD) {
                    this->unk_26E = 0x14DE;
                    this->actionFunc = func_80B10924;
                } else if (this->unk_26E == 0x14DF) {
                    this->actionFunc = func_80B10A48;
                } else {
                    this->unk_26E = 0x14D1;
                    this->unk_288 = 30;
                    gSaveContext.eventInf[4] &= (u8)~0x80;
                    this->actionFunc = func_80B0FEBC;
                }
            } else {
                this->unk_26E = func_80B0F8F8(this);
                Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
            }
        }
    } else if ((temp_v0 == 4) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                if (gSaveContext.save.playerData.rupees < this->unk_288) {
                    play_sound(NA_SE_SY_ERROR);
                    this->unk_26E = 0x14D7;
                    this->unk_26C |= 2;
                    Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
                } else {
                    func_8019F208();
                    func_801159EC(-this->unk_288);
                    globalCtx->msgCtx.msgMode = 0x43;
                    globalCtx->msgCtx.unk12023 = 4;
                    func_800B7298(globalCtx, NULL, 7);
                    this->actionFunc = func_80B11344;
                }
                break;

            case 1:
                func_8019F230();
                this->unk_26E = 0x14E3;
                this->unk_26C |= 2;
                Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
                break;
        }
    }
}

void func_80B10868(EnGb2* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCurrentIndex() != this->unk_282[2]) {
        if (ActorCutscene_GetCanPlayNext(this->unk_282[this->unk_290])) {
            this->actionFunc = func_80B10A48;
            ActorCutscene_StartAndSetFlag(this->unk_282[this->unk_290], &this->actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk_282[this->unk_290]);
        }
    } else {
        this->unk_290 = 1;
        ActorCutscene_SetIntentToPlay(this->unk_282[this->unk_290]);
    }
}

void func_80B10924(EnGb2* this, GlobalContext* globalCtx) {
    s32 sp24;

    if (gSaveContext.save.weekEventReg[54] & 0x40) {
        sp24 = 5;
    } else {
        sp24 = 12;
    }

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        if (sp24 == 12) {
            gSaveContext.save.weekEventReg[54] |= 0x40;
        } else {
            func_801159EC(50);
        }
        this->actionFunc = func_80B109DC;
    } else {
        Actor_PickUp(&this->actor, globalCtx, sp24, 300.0f, 300.0f);
    }
}

void func_80B109DC(EnGb2* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
        this->actionFunc = func_80B10634;
    } else {
        func_800B85E0(&this->actor, globalCtx, 300.0f, -1);
    }
}

void func_80B10A48(EnGb2* this, GlobalContext* globalCtx) {
    this->unk_28A -= 5;
    if (this->unk_28A < 5) {
        this->unk_28A = 0;

        switch (ENGB2_GET_7(&this->actor)) {
            case ENGB2_7_0:
                Actor_MarkForDeath(&this->actor);
                break;

            case ENGB2_7_1:
                ActorCutscene_Stop(this->unk_282[this->unk_290]);
                Actor_MarkForDeath(&this->actor);
                break;

            case ENGB2_7_2:
                ActorCutscene_Stop(this->unk_282[this->unk_290]);
                if (this->unk_26E == 0x14FB) {
                    Flags_SetSwitch(globalCtx, ENGB2_GET_7F8(&this->actor));
                    Actor_MarkForDeath(&this->actor);
                } else {
                    this->actor.draw = NULL;
                    this->unk_26C |= 0x100;
                    this->actor.flags &= ~ACTOR_FLAG_1;
                    this->actionFunc = func_80B111AC;
                }
                break;
        }
    }
}

void func_80B10B5C(EnGb2* this, GlobalContext* globalCtx) {
    s32 mask = Player_GetMask(globalCtx);

    if (this->unk_28C != mask) {
        this->unk_28C = Player_GetMask(globalCtx);
        this->unk_26C &= ~0x80;
        this->unk_26C &= ~0x20;
        this->unk_26C &= ~0x40;
    }

    if (func_80B0FA48(this, globalCtx)) {
        this->unk_26C &= ~0x20;
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) && (this->unk_26C & 0x40)) {
            if ((this->unk_26E == 0x14EE) || (this->unk_26E == 0x14F4)) {
                this->unk_26C |= 2;
            }
            Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
            this->unk_290 = 1;
            this->unk_26C &= ~0x40;
            this->actionFunc = func_80B10DAC;
        } else if ((this->actor.xzDistToPlayer < 300.0f) && this->actor.isTargeted) {
            this->unk_26C |= 0x40;
            func_800B8614(&this->actor, globalCtx, 300.0f);
        }
    } else {
        this->unk_26C &= ~0x40;
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) && (this->unk_26C & 0x20)) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
            if (this->unk_26E == 0x14EB) {
                gSaveContext.save.weekEventReg[80] |= 0x40;
            } else if (this->unk_26E == 0x14EF) {
                gSaveContext.save.weekEventReg[80] |= 0x20;
            }
            this->unk_26C &= ~0x20;
            this->unk_290 = 0;
            this->unk_26C |= 0x80;
            this->actionFunc = func_80B10DAC;
        } else if (this->actor.xzDistToPlayer < 300.0f) {
            if (!(this->unk_26C & 0x80)) {
                this->actor.flags |= ACTOR_FLAG_10000;
                this->unk_26C |= 0x20;
                func_800B8614(&this->actor, globalCtx, 300.0f);
            }
        }
    }
}

void func_80B10DAC(EnGb2* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_282[this->unk_290])) {
        if (ENGB2_GET_7(&this->actor) == ENGB2_7_1) {
            if (this->unk_290 != 2) {
                this->actionFunc = func_80B10E98;
            } else {
                Flags_SetSwitch(globalCtx, ENGB2_GET_7F8(&this->actor));
                this->actionFunc = func_80B10868;
            }
        } else {
            this->actionFunc = func_80B110F8;
        }
        ActorCutscene_StartAndSetFlag(this->unk_282[this->unk_290], &this->actor);
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->unk_282[this->unk_290]);
    }
}

void func_80B10E98(EnGb2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_26C & 2) {
            this->unk_26C &= ~2;
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            if ((this->unk_26E != 0x14E8) && (this->unk_26E != 0x14EA)) {
                ActorCutscene_Stop(this->unk_282[this->unk_290]);
                this->actionFunc = func_80B10B5C;
            } else if (Flags_GetSwitch(globalCtx, ENGB2_GET_7F8(&this->actor))) {
                this->actionFunc = func_80B10A48;
            } else {
                ActorCutscene_Stop(this->unk_282[this->unk_290]);
                this->unk_290 = 2;
                ActorCutscene_SetIntentToPlay(this->unk_282[this->unk_290]);
                this->actionFunc = func_80B10DAC;
            }
        } else {
            s32 temp;

            this->unk_26E = func_80B0FB24(this);
            Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
            temp = this->unk_26E;
            if ((temp == 0x14E7) || (temp == 0x14E9) || (temp == 0x14EC) || (temp == 0x14F0)) {
                ActorCutscene_Stop(this->unk_282[this->unk_290]);
                this->unk_290 = 1;
                ActorCutscene_SetIntentToPlay(this->unk_282[this->unk_290]);
                this->actionFunc = func_80B10DAC;
            }
        }
    }
}

void func_80B11048(EnGb2* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
        this->actionFunc = func_80B10DAC;
    } else if (this->actor.xzDistToPlayer < 300.0f) {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, globalCtx, 200.0f);
    }
}

void func_80B110F8(EnGb2* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_26C & 2) {
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->unk_26C &= ~2;
            this->actionFunc = func_80B10A48;
        } else {
            this->unk_26E = func_80B0F97C(this);
            Message_StartTextbox(globalCtx, this->unk_26E, &this->actor);
        }
    }
}

void func_80B111AC(EnGb2* this, GlobalContext* globalCtx) {
    s32 index;

    if (globalCtx->roomCtx.currRoom.num == 1) {
        return;
    }

    switch (globalCtx->roomCtx.currRoom.num) {
        case 2:
            index = 1;
            break;

        case 3:
        case 4:
            index = 2;
            break;

        case 5:
            index = 3;
            break;

        default:
            index = 0;
    }

    this->actor.world.pos.x = D_80B11A00[index][0];
    this->actor.world.pos.y = D_80B11A00[index][1];
    this->actor.world.pos.z = D_80B11A00[index][2];
    this->actor.world.rot.y = D_80B11A00[index][3] * 182.04445f;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actionFunc = func_80B11268;
}

void func_80B11268(EnGb2* this, GlobalContext* globalCtx) {
    if (globalCtx->roomCtx.currRoom.num == 1) {
        this->unk_290 = 0;
        this->unk_282[0] = this->actor.cutscene;
        if (Flags_GetClear(globalCtx, 2) && Flags_GetClear(globalCtx, 3) && Flags_GetClear(globalCtx, 4) &&
            Flags_GetClear(globalCtx, 5)) {
            this->unk_28A = 0xFF;
            this->unk_26C &= ~0x100;
            this->actor.flags |= ACTOR_FLAG_1;
            this->actor.draw = EnGb2_Draw;
            this->unk_26E = 0x14F9;
            this->actionFunc = func_80B11048;
        } else {
            this->actionFunc = func_80B111AC;
        }
    }
}

void func_80B11344(EnGb2* this, GlobalContext* globalCtx) {
    if (gSaveContext.rupeeAccumulator == 0) {
        func_80B0FE18(globalCtx);
    }
}

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 4, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2200, ICHAIN_STOP),
};

void EnGb2_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnGb2* this = THIS;

    if (func_80B0F660(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.room = -1;
    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_ps_Skel_007230, &object_ps_Anim_00049C, this->jointTable,
                       this->morphTable, 12);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinderType1(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Actor_SetScale(&this->actor, 0.01f);

    switch (ENGB2_GET_7(&this->actor)) {
        case ENGB2_7_0:
            if (gSaveContext.save.weekEventReg[54] & 0x80) {
                Actor_MarkForDeath(&this->actor);
            } else if (gSaveContext.save.weekEventReg[52] & 0x20) {
                Actor_MarkForDeath(&this->actor);
            }

            if (gSaveContext.save.entranceIndex == 0x9C10) {
                func_800FE484();
                this->actionFunc = func_80B10240;
                break;
            }

            this->unk_28A = 255;
            this->actor.flags |= ACTOR_FLAG_10;
            this->actor.flags |= ACTOR_FLAG_2000000;

            if (gSaveContext.eventInf[4] & 0x40) {
                func_80B0F728(this, globalCtx);
            } else {
                func_80B0FBF0(this, globalCtx);
                func_80B0F6DC(this);
            }
            break;

        case ENGB2_7_1:
            if ((globalCtx->curSpawn == 1) || (gSaveContext.save.weekEventReg[80] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            if (Flags_GetSwitch(globalCtx, ENGB2_GET_7F8(thisx))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->unk_28A = 255;
            func_80B0FA04(this);
            this->unk_28C = Player_GetMask(globalCtx);
            this->actionFunc = func_80B10B5C;
            break;

        case ENGB2_7_2:
            this->unk_290 = 0;
            this->unk_282[0] = this->actor.cutscene;
            if (Flags_GetSwitch(globalCtx, ENGB2_GET_7F8(thisx))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            if (Flags_GetClear(globalCtx, 2) && Flags_GetClear(globalCtx, 3) && Flags_GetClear(globalCtx, 4) &&
                Flags_GetClear(globalCtx, 5)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            if (gSaveContext.save.weekEventReg[76] & 0x80) {
                this->actor.draw = NULL;
                this->unk_26C |= 0x100;
                this->actor.flags &= ~ACTOR_FLAG_1;
                this->actionFunc = func_80B111AC;
            } else {
                this->unk_28A = 255;
                this->unk_26E = 0x14F5;
                this->actionFunc = func_80B11048;
            }
            break;

        default:
            Actor_MarkForDeath(&this->actor);
            return;
    }
}

void EnGb2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnGb2* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnGb2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGb2* this = THIS;

    SkelAnime_Update(&this->skelAnime);

    this->actionFunc(this, globalCtx);

    if (!(this->unk_26C & 0x100)) {
        func_80B0F5E0(this, globalCtx);
    }
    func_800E9250(globalCtx, &this->actor, &this->unk_270, &this->unk_276, this->actor.focus.pos);
}

s32 EnGb2_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                           Gfx** gfx) {
    EnGb2* this = THIS;

    if (limbIndex == 7) {
        limbIndex = limbIndex;
        Matrix_RotateY(this->unk_270.y, MTXMODE_APPLY);
    }

    if (limbIndex == 1) {
        *dList = NULL;
    }

    return false;
}

void EnGb2_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnGb2* this = THIS;
    Vec3f sp18 = { 2400.0f, 0.0f, 0.0f };

    if (limbIndex == 7) {
        Matrix_MultiplyVector3fByState(&sp18, &this->actor.focus.pos);
    }
}

void EnGb2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGb2* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_28A == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnGb2_OverrideLimbDraw, EnGb2_PostLimbDraw,
                                           &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, this->unk_28A);

        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnGb2_OverrideLimbDraw, EnGb2_PostLimbDraw,
                                           &this->actor, POLY_XLU_DISP);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
