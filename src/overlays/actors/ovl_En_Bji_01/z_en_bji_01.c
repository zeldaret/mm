#include "z_en_bji_01.h"

#define FLAGS 0x00000019

#define THIS ((EnBji01*)thisx)

void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Draw(Actor* thisx, GlobalContext* globalCtx);

/* Init helper functions */
void func_809CCE98(EnBji01* this, GlobalContext* globalCtx); /* Level 1 */
void func_809CCEE8(EnBji01* this, GlobalContext* globalCtx); /* Level 2 */
void func_809CD028(EnBji01* this, GlobalContext* globalCtx); /* Level 3 */
void func_809CD328(EnBji01* this, GlobalContext* globalCtx); /* Level 4 */
void func_809CCDE0(EnBji01* this, GlobalContext* globalCtx); /* Level 5 */
void func_809CD634(EnBji01* this, GlobalContext* globalCtx); /* Level 5 */
void func_809CD6B0(EnBji01* this, GlobalContext* globalCtx); /* Level 6 */
void func_809CD6C0(EnBji01* this, GlobalContext* globalCtx); /* Level 3 */
void func_809CD70C(EnBji01* this, GlobalContext* globalCtx); /* Level 4 */
void func_809CD77C(EnBji01* this, GlobalContext* globalCtx); /* Level 5 */

/* Draw helper functions */
s32 func_809CDA4C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
void func_809CDB04(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);

/* Segmented data */
extern AnimationHeader D_06000FDC;
extern AnimationHeader D_06005B58;
extern AnimationHeader D_06000AB0;
extern AnimationHeader D_0600066C;
extern void* D_060049F0[];
extern void* D_06004E70[];
extern void* D_06005270[];
extern FlexSkeletonHeader D_0600578C;

/* .data */
const ActorInit En_Bji_01_InitVars = {
    ACTOR_EN_BJI_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJI,
    sizeof(EnBji01),
    (ActorFunc)EnBji01_Init,
    (ActorFunc)EnBji01_Destroy,
    (ActorFunc)EnBji01_Update,
    (ActorFunc)EnBji01_Draw,
};

static ColliderCylinderInit D_809CDC50 = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

static struct_80B8E1A8 D_809CDC7C[4] = {
    { &D_06000FDC, 1.0f, 0, 0.0f },
    { &D_06005B58, 1.0f, 0, 10.0f },
    { &D_06000AB0, 1.0f, 0, 0.0f },
    { &D_0600066C, 1.0f, 2, -5.0f },
};

static s16 D_809CDCBC[6] = { 0, 1, 2, 1, 0, 0 }; /*These are 16-bit values, but it's not confirmed they are s16.*/

static Vec3f D_809CDCC8 = { 1088.0f, 1200.0f, 0.0f };

static void* D_809CDCD4[3] = { D_060049F0, D_06004E70, D_06005270 };

void func_809CCDE0(EnBji01* this, GlobalContext* globalCtx) {

    Player* player = PLAYER;

    Vec3f sp58;
    s32 pad[2];

    Math_Vec3f_Copy(&sp58, &player->actor.world.pos);
    sp58.y = player->bodyPartsPos[7].y + 3.0f;
    func_8013E950(&this->actor.world.pos, &this->actor.focus.pos, this->actor.shape.rot.y, &player->actor.world.pos,
                  &sp58, &this->unk2A6, &this->unk2A8, &this->unk2A2, &this->unk2A4, 0x1554, 0x1FFE, 0xE38, 0x1C70);
}

void func_809CCE98(EnBji01* this, GlobalContext* globalCtx) {

    func_8013E1C8(&this->skelAnime, &D_809CDC7C, 0, &this->unk298);
    this->actor.textId = 0;
    this->actionFunc = func_809CCEE8;
}

void func_809CCEE8(EnBji01* this, GlobalContext* globalCtx) {

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x444);
    if (this->actor.params == 0) {
        if ((this->actor.xzDistToPlayer <= 60.0f) && (this->actor.yDistToPlayer <= 10.0f)) {
            this->actor.flags |= 0x10000;
        } else {
            this->actor.flags &= 0xFFFEFFFF;
        }
    }
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        globalCtx->msgCtx.unk11F22 = 0;
        globalCtx->msgCtx.unk11F10 = 0;
        func_809CD028(this, globalCtx);
    } else {
        if (this->moonsTear != NULL) {
            if (this->moonsTear->actor.colChkInfo.health == 1) {
                func_809CD6C0(this, globalCtx);
                return;
            }
        } else {
            this->moonsTear =
                (ObjMoonStone*)func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_PROP, ACTOR_OBJ_MOON_STONE);
        }
        func_800B8500(&this->actor, globalCtx, 60.0f, 10.0f, 0);
    }
}

void func_809CD028(EnBji01* this, GlobalContext* globalCtx) {

    s32 tempDay;
    f32 tempTimeBeforeMoonCrash;

    switch (this->actor.params) {
        case 0: /* Have not talked to Shikashi as of entering observatory last */
        case 1: /* Have finished a conversation with Shikashi */
            switch (gSaveContext.playerForm) {
                case PLAYER_FORM_DEKU:
                    if ((gSaveContext.weekEventReg[17] & 0x10) != 0) {
                        if ((gSaveContext.weekEventReg[74] & 0x80) != 0) {
                            this->unk2AA = 0x5F4;
                        } else {
                            this->unk2AA = 0x5E2;
                        }
                    } else {
                        this->unk2AA = 0x5EC;
                        gSaveContext.weekEventReg[17] |= 0x10;
                    }
                    break;
                case PLAYER_FORM_HUMAN:
                    if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
                        this->unk2AA = 0x236A;
                    } else if ((gSaveContext.weekEventReg[74] & 0x10) != 0) {
                        this->unk2AA = 0x5F6;
                    } else {
                        this->unk2AA = 0x5F5;
                        gSaveContext.weekEventReg[74] |= 0x10;
                    }
                    break;
                case PLAYER_FORM_GORON:
                case PLAYER_FORM_ZORA:
                    if ((gSaveContext.weekEventReg[75] & 8) != 0) {
                        this->unk2AA = 0x5E4;
                    } else {
                        this->unk2AA = 0x5DC;
                        gSaveContext.weekEventReg[75] |= 8;
                    }
                    break;
            }
            break;
        case 3: /* Currently engaged in post-telescope Shikashi dialogue */
            switch (gSaveContext.playerForm) {
                case PLAYER_FORM_DEKU:
                    if ((gSaveContext.weekEventReg[74] & 0x80) != 0) {
                        this->unk2AA = 0x5F2;
                    } else {
                        this->unk2AA = 0x5F1;
                    }
                    func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.yDistToPlayer, 0);
                    break;
                case PLAYER_FORM_HUMAN:
                    this->unk2AA = 0x5F7;
                    break;
                case PLAYER_FORM_GORON:
                case PLAYER_FORM_ZORA:
                    switch (CURRENT_DAY) {
                        case 1:
                            this->unk2AA = 0x5E9;
                            break;
                        case 2:
                            this->unk2AA = 0x5EA;
                            break;
                        case 3:
                            tempDay = gSaveContext.day;
                            tempTimeBeforeMoonCrash =
                                ((-(tempDay % 5 << 0x10) - ((u16)(gSaveContext.time - 0x4000))) + 0x40000);
                            if (tempTimeBeforeMoonCrash < 2730.6667f /* 1 hr */) {
                                this->unk2AA = 0x5E8;
                            } else {
                                this->unk2AA = 0x5EB;
                            }
                            break;
                    }
            }
            break;
    }
    func_8013E1C8(&this->skelAnime, (s32)D_809CDC7C, 2, &this->unk298);
    this->actionFunc = func_809CD328;
}

void func_809CD328(EnBji01* this, GlobalContext* globalCtx) {

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
            Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x444);
            func_809CCDE0(this, globalCtx);
            if (this->actor.shape.rot.y == this->actor.yawTowardsPlayer) {
                func_801518B0(globalCtx, (u16)this->unk2AA, &this->actor);
            }
            break;
        case 4:
            if (func_80147624(globalCtx) != 0) {
                this->actor.flags &= 0xFFFEFFFF;
                this->actor.params = 1;
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_801477B4(globalCtx);
                        func_809CD634(this, globalCtx);
                        break;
                    case 1:
                        func_8019F230();
                        switch (gSaveContext.playerForm) {
                            case PLAYER_FORM_DEKU:
                                func_80151938(globalCtx, 0x5F0U);
                                break;
                            case PLAYER_FORM_HUMAN:
                                func_80151938(globalCtx, 0x5F8U);
                                break;
                            case PLAYER_FORM_GORON:
                            case PLAYER_FORM_ZORA:
                                func_80151938(globalCtx, 0x5E1U);
                                break;
                        }
                        break;
                }
            }
            break;
        case 5:
            if (func_80147624(globalCtx) != 0) {
                this->actor.flags &= 0xFFFEFFFF;
                switch (globalCtx->msgCtx.unk11F04) {
                    case 1502:
                        func_8013E1C8((s32) & this->skelAnime, (s32)D_809CDC7C, 3, &this->unk298);
                        func_80151938(globalCtx, 0x5DFU);
                        break;
                    case 1508:
                        func_80151938(globalCtx, 0x5E7U);
                        break;
                    case 1509:
                        func_80151938(globalCtx, 0x5E0U);
                        break;
                    case 1511:
                        func_80151938(globalCtx, 0x5E5U);
                        break;
                    case 1500:
                    case 1501:
                    case 1503:
                    case 1516:
                    case 1517:
                    case 1518:
                    case 1522:
                    case 1525:
                        func_80151938(globalCtx, (globalCtx->msgCtx.unk11F04 + 1) & 0xFFFF);
                        break;
                    case 1520:
                    case 1526:
                        func_80151938(globalCtx, 0x5EFU);
                        break;
                    case 1505:
                    case 1512:
                    case 1513:
                    case 1514:
                    case 1515:
                    case 1521:
                    case 1523:
                    case 1524:
                    case 1527:
                    case 1528:
                        func_801477B4(globalCtx);
                        this->actor.flags &= 0xFFFEFFFF;
                        this->actor.params = 1;
                        func_809CCE98(this, globalCtx);
                        break;
                }
            }
            break;
        case 6:
            this->actor.params = 1;
            this->actor.flags &= 0xFFFEFFFF;
            func_809CCE98(this, globalCtx);
            break;
    }
    if ((this->unk298 == 3) && (this->skelAnime.animCurrentFrame == this->skelAnime.animFrameCount)) {
        func_8013E1C8((s32) & this->skelAnime, (s32)D_809CDC7C, 2, &this->unk298);
    }
}

void func_809CD634(EnBji01* this, GlobalContext* globalCtx) {

    func_801A5BD0(0x6F);
    func_801A89A8(0xE0000101);
    globalCtx->nextEntranceIndex = 0x54A0; /* Termina Field from telescope */
    gSaveContext.respawn[0].entranceIndex = globalCtx->nextEntranceIndex;
    func_80169EFC(globalCtx);
    gSaveContext.respawnFlag = -2;
    this->actionFunc = func_809CD6B0;
}

void func_809CD6B0(EnBji01* this, GlobalContext* globalCtx) {
}

void func_809CD6C0(EnBji01* this, GlobalContext* globalCtx) {

    func_8013E1C8(&this->skelAnime, D_809CDC7C, 2, &this->unk298);
    this->actionFunc = func_809CD70C;
}

void func_809CD70C(EnBji01* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x444);
    func_809CCDE0(this, globalCtx);
    if (this->actor.shape.rot.y == this->actor.yawTowardsPlayer) {
        func_800B86C8(&this->moonsTear->actor, globalCtx, &this->actor); /* Z-Target the Moon's Tear? */
        this->actionFunc = func_809CD77C;
    }
}

void func_809CD77C(EnBji01* this, GlobalContext* globalCtx) {
    if (this->moonsTear->actor.colChkInfo.health == 0) {
        func_809CCE98(this, globalCtx);
    }
}

void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx) {

    EnBji01* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 30.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600578C, &D_06000FDC, this->jointTable, this->morphTable, 0x10);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_809CDC50);

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 0;
    this->actor.child = NULL;
    this->unk298 = -1;

    Actor_SetScale(&this->actor, 0.01f);
    func_8013E3B8(&this->actor, &this->unk2AC, 1);
    this->moonsTear =
        (ObjMoonStone*)func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_PROP, ACTOR_OBJ_MOON_STONE);

    switch (gSaveContext.entranceIndex) {
        case 0x4C00: /* Observatory from ECT */
        case 0x4C10: /* Observatory from Termina Field door */
            this->actor.params = 0;
            func_809CCE98(this, globalCtx);
            break;
        case 0x4C20: /* Observatory from Termina Field telescope */
            this->actor.flags |= 0x10000;
            func_801A5BD0(0);
            func_801A89A8(0xE0000100);
            this->actor.params = 3;
            func_809CCE98(this, globalCtx);
            break;
        default:
            Actor_MarkForDeath(&this->actor);
            break;
    }
}

void EnBji01_Destroy(Actor* thisx, GlobalContext* globalCtx) {

    EnBji01* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnBji01_Update(Actor* thisx, GlobalContext* globalCtx) {

    EnBji01* this = THIS;

    s32 pad; /*pad until 4 main functions take gamestate that gets promoted to globalctx*/

    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, (Actor*)this, 0.0f, 0.0f, 0.0f, 4U);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (this->unk2A0-- <= 0) {
        if (--this->unk29E < 0) {
            this->unk29E = 4;
            this->unk2A0 = (Rand_ZeroOne() * 60.0f) + 20.0f;
        } else {
            this->unk29C = D_809CDCBC[this->unk29E];
        }
    }

    Actor_SetHeight(&this->actor, 40.0f);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_809CDA4C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {

    EnBji01* this = THIS;

    if ((limbIndex == 0) && ((globalCtx->gameplayFrames & 1) != 0)) {
        *dList = NULL;
    }
    if (limbIndex == 0) {
        rot->x = rot->x;
        rot->y = rot->y;
        rot->z = rot->z;
    }

    switch (limbIndex) {
        case 8:
            rot->x += this->unk2A4;
            rot->z += this->unk2A2;
            break;
        case 15:
            rot->x += this->unk2A8;
            rot->z += this->unk2A6;
            break;
    }

    return 0;
}

void func_809CDB04(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {

    EnBji01* this = THIS;

    Vec3f sp20;
    s32 temp_f4 = 0;

    if (limbIndex == 0xF) {
        Math_Vec3f_Copy((Vec3f*)&sp20, &D_809CDCC8);
        sp20.x += temp_f4 * 0.1f;
        sp20.y += temp_f4 * 0.1f;
        sp20.z += temp_f4 * 0.1f;
        SysMatrix_MultiplyVector3fByState(&sp20, &this->actor.focus.pos);
    }
}

void EnBji01_Draw(Actor* thisx, GlobalContext* globalCtx) {

    EnBji01* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_809CDCD4[this->unk29C]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_809CDA4C, func_809CDB04, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
