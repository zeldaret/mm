#include "z_en_twig.h"

#define FLAGS 0x00000010

#define THIS ((EnTwig*)thisx)

#define GET_PARAM1(ring) ((ring)->dyna.actor.params & 0xF)
#define GET_PARAM2(ring) (((ring)->dyna.actor.params >> 4) & 0x1F)
#define GET_PARAM3(ring) (((ring)->dyna.actor.params >> 9) & 0x7F)

void EnTwig_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Update(Actor* this, GlobalContext* globalCtx);
void EnTwig_Draw(EnTwig* this, GlobalContext* globalCtx);

void func_80AC0A54(EnTwig* this, GlobalContext* globalCtx);
void func_80AC0A6C(EnTwig* this, GlobalContext* globalCtx);

void func_80AC0A7C(EnTwig* this, GlobalContext* globalCtx);
void func_80AC0AC8(EnTwig* this, GlobalContext* globalCtx);

void func_80AC0CC4(EnTwig* this, GlobalContext* globalCtx);
void func_80AC0D2C(EnTwig* this, GlobalContext* globalCtx);

const ActorInit En_Twig_InitVars = {
    ACTOR_EN_TWIG,
    ACTORCAT_MISC,
    FLAGS,
    OBJECT_TWIG,
    sizeof(EnTwig),
    (ActorFunc)EnTwig_Init,
    (ActorFunc)EnTwig_Destroy,
    (ActorFunc)EnTwig_Update,
    (ActorFunc)EnTwig_Draw,
};

static s32 sCurrentRing;
static s16 sRingCount;
static s16 sRingNotCollected[25];

extern Gfx D_060014C8[];
extern Gfx D_06001C38[];

static CollisionHeader* sColHeaders[] = { NULL, 0x060020A0, 0x060016C0 };

static s16 sRingsHaveSpawned = 0;

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void EnTwig_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTwig* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->unk_160 = GET_PARAM1(this);
    BcCheck3_BgActorInit(&this->dyna, 1);
    if (sColHeaders[this->unk_160] != NULL) {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, sColHeaders[this->unk_160]);
    }
    this->dyna.actor.bgCheckFlags |= 0x400;
    switch (this->unk_160) {
        case 0:
            Actor_MarkForDeath(&this->dyna.actor);
            break;
        case 1:
            if (!sRingsHaveSpawned) {
                sRingCount = (gSaveContext.weekEventReg[24] & 4) ? 25 : 20;
                for (i = 0; i < sRingCount; i++) {
                    sRingNotCollected[i] = false;
                }
                sRingsHaveSpawned = true;
            }
            if (GET_PARAM2(this) != 0) {
                if (!(gSaveContext.weekEventReg[24] & 4)) {
                    Actor_MarkForDeath(&this->dyna.actor);
                    return;
                }
            } else if (gSaveContext.weekEventReg[24] & 4) {
                Actor_MarkForDeath(&this->dyna.actor);
                return;
            }
            Actor_SetScale(&this->dyna.actor, 4.2f);
            this->dyna.actor.uncullZoneScale = this->dyna.actor.uncullZoneDownward = this->dyna.actor.scale.x * 60.0f;
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            func_80AC0A7C(this, globalCtx);
            break;
        case 2:
            Actor_SetScale(&this->dyna.actor, 1.0f);
            this->dyna.actor.uncullZoneScale = this->dyna.actor.uncullZoneDownward = this->dyna.actor.scale.x * 880.0f;
            func_80AC0A54(this, globalCtx);
            break;
    }
}

void EnTwig_Destroy(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTwig* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80AC0A54(EnTwig* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80AC0A6C;
}

void func_80AC0A6C(EnTwig* this, GlobalContext* globalCtx) {
}

void func_80AC0A7C(EnTwig* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_Vec3f_Copy(&this->unk_180, &player->bodyPartsPos[0]);
    this->unk_178 = 0;
    this->unk_17A = 0;
    this->actionFunc = func_80AC0AC8;
}

void func_80AC0AC8(EnTwig* this, GlobalContext* globalCtx) {
    static Vec3f D_80AC10D0 = { 0.0f, 0.0f, 1.0f };
    Player* player = GET_PLAYER(globalCtx);
    Plane sp4C;
    Vec3f sp40;

    if (sCurrentRing == GET_PARAM3(this)) {
        if (this->unk_17A == 3) {
            this->unk_17A = 0;
            this->dyna.actor.shape.rot.z += 0x2000;
        } else {
            this->unk_17A++;
        }
    }
    func_8013E4B0(&this->dyna.actor.world.pos, &D_80AC10D0, &this->dyna.actor.shape.rot, &sp4C);
    if ((sCurrentRing == GET_PARAM3(this)) && func_8017D2FC(sp4C.normal.x, sp4C.normal.y, sp4C.normal.z, sp4C.originDist,
                                                          &this->unk_180, &player->bodyPartsPos[0], &sp40, 0)) {
        if (Math3D_DistanceSquared(&this->dyna.actor.world.pos, &sp40) <=
            SQ(this->dyna.actor.scale.x * 0.345f * 40.0f)) {
            func_80AC0CC4(this, globalCtx);
            return;
        }
    } else {
        if (this->dyna.actor.xyzDistToPlayerSq <= SQ((this->dyna.actor.scale.x * 40.0f) + 40)) {
            func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        } else {
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        }
        if (this->dyna.actor.xyzDistToPlayerSq >= (this->dyna.actor.scale.x * 10.0f * 40.0f * 40.0f)) {
            this->dyna.actor.shape.rot.y = this->dyna.actor.yawTowardsPlayer;
            this->dyna.actor.world.rot.y = this->dyna.actor.yawTowardsPlayer;
        }
    }
    Math_Vec3f_Copy(&this->unk_180, &player->bodyPartsPos[0]);
}

void func_80AC0CC4(EnTwig* this, GlobalContext* globalCtx) {
    this->unk_170 = 3458.0f;
    this->unk_174 = 0.2f;
    this->unk_16C |= 1;
    func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    this->actionFunc = func_80AC0D2C;
}

void func_80AC0D2C(EnTwig* this, GlobalContext* globalCtx) {
    static Vec3f sKiraVel = { 0.0f, -0.05f, 0.0f };
    static Vec3f sKiraAccel = { 0.0f, -0.025f, 0.0f };
    static Color_RGBA8 sColorWhite = { 255, 255, 255, 130 };
    static Color_RGBA8 sColorYellow = { 255, 255, 0, 0 };
    Player* player = GET_PLAYER(globalCtx);

    Math_SmoothStepToF(&this->dyna.actor.world.pos.x, player->bodyPartsPos[0].x, 0.5f, 100.0f, 0.01f);
    Math_SmoothStepToF(&this->dyna.actor.world.pos.y, player->bodyPartsPos[0].y, 0.5f, 100.0f, 0.01f);
    Math_SmoothStepToF(&this->dyna.actor.world.pos.z, player->bodyPartsPos[0].z, 0.5f, 100.0f, 0.01f);
    this->dyna.actor.shape.rot.z += (s16)this->unk_170;
    this->dyna.actor.scale.x -= this->unk_174;
    if (this->dyna.actor.scale.x < 0.0f) {
        Actor_SetScale(&this->dyna.actor, 0.0f);
    } else {
        Actor_SetScale(&this->dyna.actor, this->dyna.actor.scale.x);
    }
    if (this->dyna.actor.scale.x <= 0.0f) {
        s32 phi_s0;
        Vec3f sp6C;

        for (phi_s0 = 0; phi_s0 < 7; phi_s0++) {
            sp6C.x = (Rand_Centered() * 10.0f) + this->dyna.actor.world.pos.x;
            sp6C.y = (Rand_Centered() * 10.0f) + this->dyna.actor.world.pos.y;
            sp6C.z = (Rand_Centered() * 10.0f) + this->dyna.actor.world.pos.z;
            EffectSsKiraKira_SpawnDispersed(globalCtx, &sp6C, &sKiraVel, &sKiraAccel, &sColorWhite, &sColorYellow, 1000,
                                            (s32)(Rand_ZeroOne() * 10.0f) + 20);
        }
        play_sound(NA_SE_SY_GET_ITEM);
        globalCtx->interfaceCtx.unk_25C += -1;
        sRingNotCollected[GET_PARAM3(this)] = true;
        if (sCurrentRing == GET_PARAM3(this)) {
            s32 i;

            for (i = 0; i < sRingCount; i++) {
                if (!sRingNotCollected[i]) {
                    sCurrentRing = i;
                    break;
                }
            }
            if (i == sRingCount) {
                sCurrentRing = -1;
            }
        }
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    this->unk_170 += 0.002746582f;
    this->unk_174 += 0.15f;
}

void EnTwig_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTwig* this = THIS;

    this->actionFunc(this, globalCtx);
}

void EnTwig_Draw(EnTwig* thisx, GlobalContext* globalCtx) {
    EnTwig* this = THIS;

    switch (this->unk_160) {
        case 1:
            func_800BDFC0(globalCtx, D_06001C38);
            break;
        case 2:
            func_800BDFC0(globalCtx, D_060014C8);
            break;
    }
}
