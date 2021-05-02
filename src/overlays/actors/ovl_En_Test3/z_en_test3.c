#include "z_en_test3.h"

#define FLAGS 0x04000030

#define THIS ((EnTest3*)thisx)

void EnTest3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A40678(EnTest3* this, GlobalContext* globalCtx);
void func_80A40A6C(EnTest3* this, GlobalContext* globalCtx);
void func_80A40824(EnTest3* this, GlobalContext* globalCtx);

s32 func_80A3F080(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F09C(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A40098(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A40230(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F62C(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F73C(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F8D4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F9A4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3F9E4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FA58(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FBCC(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FBE8(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FDE4(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FE20(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FF10(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);
s32 func_80A3FFD0(EnTest3* this, GlobalContext* globalCtx, struct_80A417E8_arg2* arg2, struct_80A417E8_arg3* arg3);

// bss
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
        return false;
    }

    this->actionFunc = actionFunc;
    this->unk_D8A = 0;
    this->schedule = 0;
    return true;
}

s32 func_80A3E80C(EnTest3* this, GlobalContext* globalCtx, s32 actionIndex) {
    static KafeiActionSetupInfo actionSetupInfoList[] = {
        { func_80A40A6C, NULL },
        { NULL, NULL },
    };
    KafeiActionSetupInfo* actionSetup = &actionSetupInfoList[actionIndex];

    actionSetup->actionInitFunc(this, globalCtx);

    if (actionSetup->actionFunc == NULL) {
        return false;
    }

    func_80A3E7E0(this, actionSetup->actionFunc);

    return true;
}

s32 func_80A3E870(EnTest3* this, GlobalContext* globalCtx) {
    return true;
}

s32 func_80A3E884(EnTest3* this, GlobalContext* globalCtx) {
    return false;
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
        return true;
    } else {
        return false;
    }
}

s32 func_80A3E9DC(EnTest3* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actorCutsceneId)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actorCutsceneId, &this->actor.base);
        return true;
    } else {
        ActorCutscene_SetIntentToPlay(this->actorCutsceneId);
        return false;
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
        return true;
    } else {
        return false;
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
        return true;
    } else {
        return false;
    }
}

s32 func_80A3EB8C(EnTest3* this, GlobalContext* globalCtx) {
    if (func_80A3EAF8(this, globalCtx) != 0) {
        Actor* actor = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_ITEMACTION, ACTOR_OBJ_NOZOKI);

        if (actor != NULL) {
            this->actor.unk_730 = actor;
        }

        globalCtx->msgCtx.unk_11F23 = 0x44;
        return true;
    } else {
        return false;
    }
}

s32 func_80A3EBFC(EnTest3* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 2) {
        return true;
    } else {
        return false;
    }
}

s32 func_80A3EC30(EnTest3* this, GlobalContext* globalCtx) {
    return false;
}

#ifdef NON_EQUIVALENT
// single instruction difference at "return (globalCtx->msgCtx.unk_12022) ..."
s32 func_80A3EC44(EnTest3* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 4) && (func_80147624(globalCtx))) {
        if (globalCtx->msgCtx.unk_12022) {
            func_8019F230();
        } else {
            func_8019F208();
        }

        return (globalCtx->msgCtx.unk_12022) ? true : this->talkState->unk_01;
    }

    return false;
}
#else
s32 func_80A3EC44(EnTest3* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3EC44.asm")
#endif

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

    D_80A41D24 = true;
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
        Camera_SetFlags(camera, 0x41);
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

TalkState D_80A418A4[] = {
    { 4, 0, 0x1465 },
};

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F080.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F09C.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F0B0.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F114.asm")

// 97 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F15C.asm")

// 54 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F2BC.asm")

// 78 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F384.asm")

// 38 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F4A4.asm")

// 32 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F534.asm")

// 39 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F5A4.asm")

TalkState* D_80A418A8[] = {
    D_80A41854, D_80A41858, D_80A41880, D_80A41884, D_80A418A0,
};

// 76 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F62C.asm")

// 109 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F73C.asm")

// 55 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F8D4.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F9A4.asm")

// 31 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3F9E4.asm")

// 103 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FA58.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FBCC.asm")

// 138 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FBE8.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FDE4.asm")

// 65 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FE20.asm")

/* static */ Vec3f D_80A418BC[] = { -420.0f, 210.0f, -162.0f };

// 51 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FF10.asm")

// 54 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A3FFD0.asm")

// 112 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40098.asm")

// 286 line yikes
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40230.asm")

// 117 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40678.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40824.asm")

// 54 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A4084C.asm")

// 54 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40908.asm")

// 42 line
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A409D4.asm")

// very easy
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/EnTest3_Update.asm")

/* static */ s32 D_80A418C8 = false;

void func_80A40CF0();
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40CF0.asm")

/* static */ Vec3f D_80A418CC[] = { 1100.0f, -700.0f, 0.0f };

void func_80A40F34();
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A40F34.asm")

/* static */ void* eyeTextures[] = {
    0x06000DC0, 0x06003680, 0x06003E80, 0x06004680, 0x06004E80, 0x06005680, 0x06005E80, 0x06006680,
};

/* static */ void* mouthTextures[] = {
    0x060009C0,
    0x06006E80,
    0x06007280,
    0x06007680,
};

/* static */ FaceAnimKeyFrame faceAnimInfo[] = {
    { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }, { 4, 0 }, { 5, 1 }, { 7, 2 }, { 0, 2 },
    { 3, 0 }, { 4, 0 }, { 2, 2 }, { 1, 1 }, { 0, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
};

#ifdef NON_EQUIVALENT
// needs a lot more work done
void func_80A4129C(Actor* thisx, GlobalContext* globalCtx) {
    EnTest3* this = THIS;
    s32 pad;
    s32 eyeTexId = (this->actor.skelAnime.limbDrawTbl[11].x & 0xF) - 1;
    s32 mouthTexId = ((this->actor.skelAnime.limbDrawTbl[11].x >> 4) & 0xF) - 1;
    s32 pad2;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C268(globalCtx);

    if (this->actor.unk_D5C > 0) {
        // s32 num = this->actor.unk_B5F + CLAMP(0x32 - this->actor.unk_D5C, 8, 40);
        // this->actor.unk_B5F = num;
        this->actor.unk_B5F += CLAMP(0x32 - this->actor.unk_D5C, 8, 40);
        POLY_OPA_DISP =
            Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 0, 0, 0xFA0 - (Math_CosS(this->actor.unk_B5F << 8) * 2000.0f));
    }

    func_800B8050(this, globalCtx, 0);
    D_80A418C8 = false;

    if (this->actor.stateFlags1 & 0x100000) {
        Vec3f cameraPos;

        SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->unk187B0, &this->actor.base.focus, &cameraPos);

        if (cameraPos.z < -4.0f) {
            D_80A418C8 = true;
        }
    }

    if (eyeTexId < 0) {
        eyeTexId = faceAnimInfo[this->actor.base.shape.face].eyeTexId;
    }

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(eyeTextures[eyeTexId]));

    if (mouthTexId < 0) {
        mouthTexId = faceAnimInfo[this->actor.base.shape.face].mouthTexId;
    }

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(mouthTextures[mouthTexId]));

    SkelAnime_LodDrawSV(globalCtx, this->actor.skelAnime.skeleton, this->actor.skelAnime.limbDrawTbl,
                        this->actor.skelAnime.dListCount, func_80A40CF0, func_80A40F34, this, 0);

    if (this->actor.unk_D5C > 0) {
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    if (this->actor.unk_B2A != 0) {
        func_8012697C(globalCtx, &this->actor);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
void func_80A4129C(Actor* thisx, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test3_0x80A3E7E0/func_80A4129C.asm")
#endif
