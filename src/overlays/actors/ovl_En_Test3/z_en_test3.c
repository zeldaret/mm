#include "z_en_test3.h"
#include "../ovl_En_Door/z_en_door.h"

#define FLAGS 0x04000030

#define THIS ((EnTest3*)thisx)

void EnTest3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A40678(EnTest3* this, GlobalContext* globalCtx);
void func_80A40A6C(EnTest3* this, GlobalContext* globalCtx);
void func_80A40824(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3F080(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F09C(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A40098(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A40230(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3F62C(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F73C(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3F8D4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F9A4(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3F9E4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FA58(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3FBCC(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FBE8(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3FDE4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FE20(EnTest3* this, GlobalContext* globalCtx);
s32 func_80A3FF10(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FFD0(EnTest3* this, GlobalContext* globalCtx);

// bss
extern s32 D_80A41D20;
extern s32 D_80A41D24;

// Extenal
extern LinkAnimetionEntry D_0400CF88;
extern FlexSkeletonHeader D_0600F7EC;

u32 D_80A41530[] = {
    0x0C000142, 0x0A007018, 0x02063207, 0x140C0F07, 0x1E070033, 0x04010509, 0x0A050E06, 0x3207140F, 0x0A006F21,
    0x02060006, 0x1E150206, 0x1E06230D, 0x02062306, 0x3201050E, 0x06230632, 0x0E09010E, 0x0600061E, 0x0D050C00,
    0x02510033, 0x020A1100, 0x00330401, 0x0504000A, 0x0A007025, 0x0F0D00F0, 0x020F050F, 0x1915020F, 0x190F280D,
    0x020F2810, 0x0001050E, 0x0F281000, 0x1109010E, 0x0F050F19, 0x100A000D, 0x15020F37, 0x100A0902, 0x100A160A,
    0x01050903, 0x0E0F3710, 0x0A0C050D, 0x00030098, 0x01210800, 0x87014F40, 0x00820A00, 0x4F020907, 0x00332029,
    0x0A001324, 0x00330802, 0x0905003D, 0x08180033, 0x10070F13, 0x00010509, 0x05021300, 0x130A0105, 0x0E130013,
    0x0A140905, 0x050A0013, 0x07005A02, 0x02090905, 0x0A006C0D, 0x02040004, 0x0A01050E, 0x0400040A, 0x0B0A0061,
    0x2E02040A, 0x041E2200, 0x33011502, 0x041E042D, 0x0902042D, 0x06000105, 0x09060E04, 0x1E042D13, 0x02041E06,
    0x00010509, 0x080E040A, 0x041E1205, 0x0A000D07, 0x00330801, 0x05090405, 0x05000000,
};

const ActorInit En_Test3_InitVars = {
    ACTOR_EN_TEST3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TEST3,
    sizeof(EnTest3),
    (ActorFunc)EnTest3_Init,
    (ActorFunc)EnTest3_Destroy,
    (ActorFunc)EnTest3_Update,
    (ActorFunc)NULL,
};

s32 func_80A3E7E0(EnTest3* this, EnTest3ActionFunc actionFunc) {
    if (actionFunc == this->actionFunc) {
        return 0;
    }

    this->actionFunc = actionFunc;
    this->unk_D8A = 0;
    this->schedule = 0;
    return 1;
}

s32 func_80A3E80C(EnTest3* this, GlobalContext* globalCtx, s32 actionIndex) {
    static KafeiActionSetupInfo actionSetupInfoList[] = {
        { func_80A40A6C, NULL },
        { NULL, NULL },
    };
    KafeiActionSetupInfo* actionSetup = &actionSetupInfoList[actionIndex];

    actionSetup->init(this, globalCtx);

    if (actionSetup->action == NULL) {
        return 0;
    }

    func_80A3E7E0(this, actionSetup->action);

    return 1;
}

s32 func_80A3E870(EnTest3* this, GlobalContext* globalCtx) {
    return 1;
}

s32 func_80A3E884(EnTest3* this, GlobalContext* globalCtx) {
    return 0;
}

s32 func_80A3E898(EnTest3* this, GlobalContext* globalCtx) {
    u16 textId = this->talkState->textId;

    if ((this->talkState->unk_00 == 4) && (gSaveContext.perm.weekEventReg[51])) {
        func_80151BB4(globalCtx, 2);
    }

    if (textId == 0xFFFF) {
        func_801477B4(globalCtx);
    } else if (textId) {
        func_80151938(globalCtx, textId);
    }

    if (textId == 0x296B) {
        SkelAnime_ChangeLinkAnimPlaybackStop(globalCtx, &this->actor.skelAnime, &D_0400CF88, 0.6666667f);
    }

    return 0;
}

s32 func_80A3E960(EnTest3* this, GlobalContext* globalCtx) {
    this->timer = this->talkState->unk_01;
    return 0;
}

s32 func_80A3E97C(EnTest3* this, GlobalContext* globalCtx) {
    if (DECR(this->timer) == 0) {
        func_801518B0(globalCtx, this->talkState->textId, NULL);
        return 1;
    } else {
        return 0;
    }
}

s32 func_80A3E9DC(EnTest3* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actorCutsceneId)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutsceneId, &this->actor.base);
        return 1;
    } else {
        ActorCutscene_SetIntentToPlay(this->actorCutsceneId);
        return 0;
    }
}

s32 func_80A3EA30(EnTest3* this, GlobalContext* globalCtx) {
    if (this->talkState->textId == 0x145F) {
        Actor* actor = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_BG, ACTOR_BG_IKNV_OBJ);

        if (actor != NULL) {
            this->actor.unk_730 = actor;
        }
    }

    if (this->talkState->unk_01 != 0) {
        ActorCutscene_Stop(124);
        ActorCutscene_SetIntentToPlay(this->actorCutsceneId);
        globalCtx->msgCtx.unk_11F23 = 0x44;
    }

    return 0;
}

s32 func_80A3EAC4(EnTest3* this, GlobalContext* game_play) {
    if (func_80152498(&game_play->msgCtx) == 6) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80A3EAF8(EnTest3* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx) != 0)) {
        if (this->talkState->textId == 0x145F) {
            ActorCutscene_Stop(this->actorCutsceneId);
            this->actorCutsceneId = 0x7C;
            ActorCutscene_SetIntentToPlay(this->actorCutsceneId);
            this->actor.unk_730 = (Actor*)PLAYER;
        }
        return 1;
    } else {
        return 0;
    }
}

s32 func_80A3EB8C(EnTest3* this, GlobalContext* globalCtx) {
    if (func_80A3EAF8(this, globalCtx) != 0) {
        Actor* actor = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_ITEMACTION, ACTOR_OBJ_NOZOKI);

        if (actor != NULL) {
            this->actor.unk_730 = actor;
        }

        globalCtx->msgCtx.unk_11F23 = 0x44;
        return 1;
    } else {
        return 0;
    }
}

s32 func_80A3EBFC(EnTest3* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 2) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80A3EC30(EnTest3* this, GlobalContext* globalCtx) {
    return 0;
}

s32 func_80A3EC44(EnTest3* this, GlobalContext* globalCtx) {
    u8 ret;

    if ((func_80152498(&globalCtx->msgCtx) == 4) && func_80147624(globalCtx)) {
        if (globalCtx->msgCtx.choiceIndex) {
            func_8019F230();
        } else {
            func_8019F208();
        }

        if (globalCtx->msgCtx.choiceIndex) {
            return 1;
        } else {
            ret = this->talkState->unk_01;
            return ret + 1;
        }
    }

    return 0;
}

s32 func_80A3ECEC(EnTest3* this, GlobalContext* globalCtx) {
    static EnTest3_functions_80A4169C D_80A4169C[] = {
        func_80A3E898, func_80A3E898, func_80A3E884, func_80A3E898, func_80A3E898,
        func_80A3EA30, func_80A3E898, func_80A3E960, func_80A3E870,
    };

    return D_80A4169C[this->talkState->unk_00](this, globalCtx);
}

s32 func_80A3ED24(EnTest3* this, GlobalContext* globalCtx) {
    static EnTest3_functions_80A4169C D_80A416C0[] = {
        func_80A3EAC4, func_80A3EAF8, func_80A3EBFC, func_80A3EC44,
        func_80A3EC30, func_80A3E9DC, func_80A3EB8C, func_80A3E97C,
    };
    s32 index = D_80A416C0[this->talkState->unk_00](this, globalCtx);

    if (index != 0) {
        this->talkState = &this->talkState[index];
        return func_80A3ECEC(this, globalCtx);
    }

    return 0;
}

PlayerAgeProperties D_80A416E0 = {
    40.0f,
    60.0f,
    0.647059f,
    71.0f,
    50.0f,
    49.0f,
    39.0f,
    27.0f,
    19.0f,
    22.0f,
    32.4f,
    32.0f,
    48.0f,
    45.2941f,
    14.0f,
    12.0f,
    55.0f,
    { -24, 3565, 876 },
    {
        { -24, 3474, 862 },
        { -24, 4977, 937 },
        { 8, 4694, 380 },
        { 9, 6122, 359 },
    },
    {
        { -24, 4977, 0x03A9 },
        { -24, 6495, 0x03A9 },
        { 9, 6122, 359 },
        { 9, 7693, 380 },
    },
    {
        { 8, 4694, 380 },
        { 9, 6122, 359 },
        { -1592, 4694, 380 },
        { -1591, 6122, 359 },
    },
    0x20,
    0,
    22.0f,
    29.4343f,
    0x0400D128,
    0x0400D170,
    0x0400D1B8,
    0x0400D1F8,
    0x0400D200,
    { 0x0400D208, 0x0400D210, 0x0400DAB0, 0x0400DAB8 },
    { 0x0400DA90, 0x0400DA98 },
    { 0x0400D1D8, 0x0400D1E0 },
    { 0x0400D1F0, 0x0400D1E8 },
};

u32 D_80A417BC[] = {
    0x00000000, 0x00080000, 0xFFFFFFFF, 0xFFFFFF40, 0xFFFFFF00, 0xFFFFFF00, 0x04000200, 0x00000000, 0x00000000,
};

u32 D_80A417E0[] = {
    0x0000003F,
    0x00000F64,
};

void EnTest3_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTest3* this = THIS;
    s32 pad;
    Camera* camera;

    if (D_80A41D24) {
        Actor_MarkForDeath(&this->actor.base);
        return;
    }

    D_80A41D24 = 1;
    this->actor.base.room = -1;
    this->actor.unk_A86 = -1;
    this->actor.linkForm = 4;
    this->actor.ageProperties = &D_80A416E0;
    this->actor.itemActionParam = 0;
    this->actor.heldItemId = 0;
    func_80123BD4(&this->actor.base, 3);

    if (1) {}

    globalCtx->playerInit(&this->actor, globalCtx, &D_0600F7EC);

    Effect_Add(globalCtx, &this->actor.blureEffectIndex[0], 2, 0, 0, D_80A417BC);
    Effect_Add(globalCtx, &this->actor.blureEffectIndex[1], 2, 0, 0, D_80A417BC);
    Effect_Add(globalCtx, &this->actor.blureEffectIndex[2], 4, 0, 0, D_80A417E0);

    this->actor.maskObjectSegment = zelda_malloc(0x3800);

    globalCtx->func_18780(&this->actor, globalCtx);

    this->player = PLAYER;
    this->actor.giObjectSegment = this->player->giObjectSegment;
    this->actor.naviActor = this->player->naviActor;

    if (((gSaveContext.perm.day % 5) != 3) || (gSaveContext.perm.weekEventReg[33] & 8) ||
        (!(gSaveContext.perm.weekEventReg[51] & 8))) {
        this->actor.currentMask = 5;
    }

    this->actor.prevMask = this->actor.currentMask;

    if (globalCtx->sceneNum == SCENE_SECOM) {
        this->camId = func_801694DC(globalCtx);
        camera = Play_GetCamera(globalCtx, this->camId);
        func_800DE0EC(camera, &this->actor.base);
        Camera_SetFlags(camera, 64 | 1);
        func_80169590(globalCtx, this->camId, 1);
    }

    this->actor.base.colChkInfo.cylRadius = 20;
    this->actor.base.colChkInfo.cylHeight = 60;
    this->actor.base.colChkInfo.health = 0xFF;

    if (((this->actor.base.params >> 5) & 0xF) == 0) {
        func_80A3E7E0(this, func_80A40824);
    } else {
        func_80A3E7E0(this, func_80A40678);
    }
}

void EnTest3_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTest3* this = THIS;

    Effect_Destroy(globalCtx, this->actor.blureEffectIndex[0]);
    Effect_Destroy(globalCtx, this->actor.blureEffectIndex[1]);
    Effect_Destroy(globalCtx, this->actor.blureEffectIndex[2]);

    Collider_DestroyCylinder(globalCtx, &this->actor.cylinder);
    Collider_DestroyCylinder(globalCtx, &this->actor.shieldCylinder);

    Collider_DestroyQuad(globalCtx, &this->actor.swordQuads[0]);
    Collider_DestroyQuad(globalCtx, &this->actor.swordQuads[1]);
    Collider_DestroyQuad(globalCtx, &this->actor.swordQuads[2]);

    zelda_free(this->actor.maskObjectSegment);

    func_800FE498();
}

struct_80A417E8 D_80A417E8[] = {
    { func_80A3F080, func_80A3F09C }, { func_80A40098, func_80A40230 }, { func_80A3F62C, func_80A3F73C },
    { func_80A3F8D4, func_80A3F9A4 }, { func_80A3F9E4, func_80A3FA58 }, { func_80A3FBCC, func_80A3FBE8 },
    { func_80A3FDE4, func_80A3FE20 }, { func_80A3FF10, func_80A3FFD0 },
};

struct_80A417E8_arg2 D_80A41828[] = {
    { 0, 0, 0 },  { 3, 14, 0 }, { 2, 15, 0 }, { 2, 15, 1 }, { 2, 15, 2 }, { 2, 1, 3 }, { 2, 14, 4 }, { 5, 1, 0 },
    { 7, 15, 0 }, { 6, 2, 0 },  { 4, 4, 0 },  { 1, 1, 0 },  { 1, 1, 0 },  { 1, 2, 0 }, { 1, 1, 0 },  { 1, 1, 0 },
    { 1, 2, 0 },  { 1, 3, 0 },  { 1, 1, 0 },  { 1, 2, 0 },  { 1, 1, 0 },  { 0, 0, 0 },
};

TalkState D_80A41854[] = {
    { 0x04, 0x00, 0x2B25 },
};

TalkState D_80A41858[] = {
    { 1, 0, 0x2969 }, { 3, 1, 0x296A }, { 1, 0, 0x296B }, { 5, 1, 0x0000 }, { 8, 0, 0x0000 },
};

TalkState D_80A4186C[] = {
    { 4, 0, 0x2976 },
};

TalkState D_80A41870[] = {
    { 6, 0, 0x2977 },
    { 7, 10, 0x2978 },
    { 4, 1, 0x0000 },
};

TalkState D_80A4187C[] = {
    { 4, 0, 0x2968 },
};

TalkState D_80A41880[] = {
    { 4, 0, 0x297A },
};

TalkState D_80A41884[] = {
    { 1, 0, 0x145D }, { 1, 0, 0x145E }, { 5, 1, 0x145F }, { 1, 0, 0x145F }, { 5, 0, 0x0000 }, { 4, 0, 0x1460 },
};

TalkState D_80A4189C[] = {
    { 4, 0, 0x145C },
};

TalkState D_80A418A0[] = {
    { 4, 0, 0x2913 },
};

s32 func_80A3F080(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3) {
    return 1;
}

s32 func_80A3F09C(EnTest3* this, GlobalContext* globalCtx) {
    this->actor.base.draw = NULL;
    return 1;
}

void func_80A3F0B0(EnTest3* this, GlobalContext* globalCtx) {
    func_800BC154(globalCtx, &globalCtx->actorCtx, (Actor*)this->player, ACTORCAT_PLAYER);
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor.base, ACTORCAT_NPC);

    this->player->stateFlags1 &= ~0x20;
}

void func_80A3F114(EnTest3* this, GlobalContext* globalCtx) {
    if (this->actor.unk_394 != 0) {
        globalCtx->func_1877C(globalCtx, &this->actor, 6);
    }
}

s32 func_80A3F15C(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2) {
    s32 pathIndex = ABS_ALT(arg2->unk_01_0) - 1;

    if (pathIndex >= 0) {
        PathInfo* path = func_8013BB34(globalCtx, this->actor.base.params & 0x1F, pathIndex);
        Vec3s* startPosP = Lib_SegmentedToVirtual(path->pos);
        Vec3s* nextPosP;
        Vec3f startPos;
        Vec3f nextPos;

        if (arg2->unk_01_0 > 0) {
            nextPosP = startPosP + 1;
        } else {
            startPosP += path->unk_00 - 1;
            nextPosP = startPosP - 1;
        }

        Math_Vec3s_ToVec3f(&startPos, startPosP);
        Math_Vec3s_ToVec3f(&nextPos, nextPosP);

        if (Math_Vec3f_DistXZ(&this->actor.base.world.pos, &startPos) > 10.0f) {
            Math_Vec3f_Copy(&this->actor.base.world.pos, &startPos);
            Math_Vec3f_Copy(&this->actor.base.home.pos, &startPos);
            Math_Vec3f_Copy(&this->actor.base.prevPos, &startPos);
            this->actor.unk_AD4 = Math_Vec3f_Yaw(&this->actor.base.world.pos, &nextPos);

            if (arg2->unk_01_0 < 0) {
                this->actor.unk_AD4 += 0x8000;
            }

            this->actor.base.shape.rot.y = this->actor.unk_AD4;

            return 1;
        }
    }

    return 0;
}

Actor* func_80A3F2BC(GlobalContext* globalCtx, Actor* thisx, s32 actorId, s32 actorCat, f32 xzDist, f32 yDist) {
    Actor* curActor = globalCtx->actorCtx.actorList[actorCat].first;

    while (curActor != NULL) {
        if (actorId == curActor->id) {
            f32 dist = thisx->world.pos.y - curActor->world.pos.y;

            if ((fabsf(dist) < yDist) && (Actor_XZDistanceBetweenActors(thisx, curActor) < xzDist)) {
                return curActor;
            }
        }

        curActor = curActor->next;
    }

    return NULL;
}

s32 func_80A3F384(EnTest3* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    EnDoor* doorActor =
        (EnDoor*)func_80A3F2BC(globalCtx, &this->actor.base, ACTOR_EN_DOOR, ACTORCAT_DOOR, 55.0f, 20.0f);
    Vec3f dist;

    if ((doorActor != NULL) && (!(doorActor->opening))) {
        if ((player->doorType == 0) || ((Actor*)doorActor != player->doorActor)) {
            if (Actor_IsActorFacingActor(&this->actor.base, (Actor*)doorActor, 0x3000)) {
                Actor_CalcOffsetOrientedToDrawRotation((Actor*)doorActor, &dist, &this->actor.base.world.pos);
                this->actor.doorType = 1;
                this->actor.doorDirection = (dist.z >= 0.0f) ? 1.0f : -1.0f;
                this->actor.doorActor = (Actor*)doorActor;
                this->actor.unk_A86 = -1;
                return 1;
            }
        }
    }

    return 0;
}

s32 func_80A3F4A4(GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F4A4.asm")

void func_80A3F534(EnTest3* this, GlobalContext* globalCtx) {
    if (func_80A3F4A4(globalCtx) == 0) {
        this->talkState = D_80A4187C;
    } else if (gSaveContext.perm.weekEventReg[51] & 8) {
        this->talkState = D_80A41870;
    } else {
        this->talkState = D_80A41858;
    }

    this->actorCutsceneId = this->actor.base.cutscene;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F5A4.asm")

TalkState* D_80A418A8[] = {
    D_80A41854, D_80A41858, D_80A41880, D_80A41884, D_80A418A0,
};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F8D4.asm")

s32 func_80A3F9A4(EnTest3* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.base.shape.rot.y, this->actor.base.home.rot.y, 800);
    this->actor.unk_AD4 = this->actor.base.shape.rot.y;
    return 0;
}

s32 func_80A3F9E4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3) {
    arg3->unk_04 = (gSaveContext.perm.time - 0x3FFC) & 0xFFFF;
    arg3->unk_08 = (arg3->unk_04 + 0x46) & 0xFFFF;
    func_80A40098(this, globalCtx, arg2, arg3);

    if (this->actor.base.xzDistToPlayer < 300.0f) {
        this->unk_D8A = -1;
    } else {
        this->unk_D8A = 0x78;
    }

    return 1;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FA58.asm")

s32 func_80A3FBCC(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3) {
    return 1;
}

s32 func_80A3FBE8(EnTest3* this, GlobalContext* globalCtx) {
    static TalkState D_80A418A4[] = {
        { 4, 0, 0x1465 },
    };

    if ((D_80A41D20 == 0) && (func_801690CC(globalCtx) == 0)) {
        D_80A41D20 = 1;
        this->talkState = D_80A418A4;
        this->actorCutsceneId = this->actor.base.cutscene;
        this->actor.base.textId = D_80A418A4->textId;
    } else if (D_80A41D20 == 1) {
        if ((this->actorCutsceneId >= 0) && (func_80A3E9DC(this, globalCtx))) {
            this->actorCutsceneId = -1;
            func_800FE484();
        } else {
            if ((globalCtx->actorCtx.unk5 & 0x40) || (globalCtx->actorCtx.unk5 & 0x20)) {
                this->actorCutsceneId = ActorCutscene_GetAdditionalCutscene(this->actor.base.cutscene);
                gSaveContext.perm.weekEventReg[90] |= 2;

                if (globalCtx->actorCtx.unk5 & 0x20) {
                    this->actorCutsceneId = ActorCutscene_GetAdditionalCutscene(this->actorCutsceneId);
                }

                func_801A89A8(0x100100FF);

                D_80A41D20 = 2;
            } else {
                func_80A3F73C(this, globalCtx);
            }
        }
    } else if ((D_80A41D20 == 2) && (func_80A3E9DC(this, globalCtx))) {
        ActorCutscene_SetReturnCamera(0);
        func_800FE498();

        if (gSaveContext.perm.time > 0x4000) {
            func_800FE658(fabsf((s16) - ((0, gSaveContext.perm.time))) / 45.511112f);
        }

        if ((globalCtx->actorCtx.unk5 & 0x40) != 0) {
            gSaveContext.perm.weekEventReg[51] |= 0x20;
            gSaveContext.perm.weekEventReg[90] &= 0xfd;
        }

        D_80A41D20 = 3;
    }

    return 0;
}

s32 func_80A3FDE4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3) {
    this->actorCutsceneId = ActorCutscene_GetAdditionalCutscene(this->actor.base.cutscene);
    return 1;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FE20.asm")

Vec3f D_80A418BC[] = { -420.0f, 210.0f, -162.0f };

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FF10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FFD0.asm")

#ifdef NON_MATCHING
// reg alloc
s32 func_80A40098(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3) {
    u16 curTime = gSaveContext.perm.time - 0x3FFC;
    u16 nextTime;
    u16 new_var;

    func_80A3F15C(this, globalCtx, arg2);
    this->path = func_8013BB34(globalCtx, this->actor.base.params & 0x1F, ABS_ALT(arg2->unk_01_0) - 1);

    nextTime = ((this->schedule < 7) && (this->schedule != 0) && (this->unk_D80 >= 0)) ? (u32)curTime : arg3->unk_04;
    this->unk_DA8 = (arg3->unk_08 < nextTime) ? (nextTime - arg3->unk_08) + 0xFFFF : arg3->unk_08 - nextTime;

    if (1) {}

    this->unk_DB4 = curTime - nextTime;

    if (1) {}

    new_var = this->path->unk_00 - 2;
    this->unk_DAC = this->unk_DA8 / new_var;
    this->unk_DB0 = (this->unk_DB4 / this->unk_DAC) + 2;
    this->actionId &= ~1;
    this->unk_D84 = 1.0f;

    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40098.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40678.asm")

void func_80A40824(EnTest3* this, GlobalContext* globalCtx) {
    this->talkState = D_80A41854;
    func_80A3F73C(this, globalCtx);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A4084C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A409D4.asm")

void func_80A40A6C(EnTest3* this, GlobalContext* globalCtx) {
    gSaveContext.perm.weekEventReg[64] |= 0x20;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/EnTest3_Update.asm")

s32 D_80A418C8 = 0;

void func_80A40CF0();
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40CF0.asm")

Vec3f D_80A418CC[] = { 1100.0f, -700.0f, 0.0f };

void func_80A40F34();
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40F34.asm")

void func_80A4129C(Actor* thisx, GlobalContext* globalCtx) {
    static void* eyeTextures[] = {
        0x06000DC0, 0x06003680, 0x06003E80, 0x06004680, 0x06004E80, 0x06005680, 0x06005E80, 0x06006680,
    };
    static void* mouthTextures[] = {
        0x060009C0,
        0x06006E80,
        0x06007280,
        0x06007680,
    };
    static FaceAnimKeyFrame faceAnimInfo[] = {
        { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 4, 0 }, { 5, 1 }, { 7, 2 }, { 0, 2 },
        { 3, 0 }, { 4, 0 }, { 2, 2 }, { 1, 1 }, { 0, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    };
    EnTest3* this = THIS;
    s32 pad;
    s32 eyeTexId = (this->actor.skelAnime.limbDrawTbl[22].x & 0xF) - 1;
    s32 mouthTexId = ((this->actor.skelAnime.limbDrawTbl[22].x >> 4) & 0xF) - 1;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C268(globalCtx);

    if (this->actor.unk_D5C > 0) {
        s32 lodFrac;

        this->actor.unk_B5F += CLAMP(50 - this->actor.unk_D5C, 8, 40);
        lodFrac = 4000 - (s32)(Math_CosS(this->actor.unk_B5F << 8) * 2000.0f);
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 0, 0, lodFrac);
    }

    func_800B8050(thisx, globalCtx, 0);
    D_80A418C8 = 0;

    if (this->actor.stateFlags1 & 0x100000) {
        Vec3f cameraPos;

        SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->unk187B0, &this->actor.base.focus.pos, &cameraPos);

        if (cameraPos.z < -4.0f) {
            D_80A418C8 = 1;
        }
    }

    gfx = POLY_OPA_DISP;

    if (eyeTexId < 0) {
        eyeTexId = faceAnimInfo[thisx->shape.face].eyeTexId;
    }

    gSPSegment(&gfx[0], 0x08, Lib_SegmentedToVirtual(eyeTextures[eyeTexId]));

    if (mouthTexId < 0) {
        mouthTexId = faceAnimInfo[this->actor.base.shape.face].mouthTexId;
    }

    gSPSegment(&gfx[1], 0x09, Lib_SegmentedToVirtual(mouthTextures[mouthTexId]));

    POLY_OPA_DISP = &gfx[2];

    SkelAnime_LodDrawSV(globalCtx, this->actor.skelAnime.skeleton, this->actor.skelAnime.limbDrawTbl,
                        this->actor.skelAnime.dListCount, func_80A40CF0, func_80A40F34, &this->actor.base, 0);

    if (this->actor.unk_D5C > 0) {
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    if (this->actor.unk_B2A != 0) {
        func_8012697C(globalCtx, &this->actor);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
