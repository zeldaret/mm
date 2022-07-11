/*
 * File: z_en_ge1.c
 * Overlay: ovl_En_Ge1
 * Description: White-clad Gerudo Pirate
 */

#include "z_en_ge1.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnGe1*)thisx)

void EnGe1_Init(Actor* thisx, PlayState* play);
void EnGe1_Destroy(Actor* thisx, PlayState* play);
void EnGe1_Update(Actor* thisx, PlayState* play);
void EnGe1_Draw(Actor* thisx, PlayState* play);

const ActorInit En_Ge1_InitVars = {
    ACTOR_EN_GE1,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GE1,
    sizeof(EnGe1),
    (ActorFunc)EnGe1_Init,
    (ActorFunc)EnGe1_Destroy,
    (ActorFunc)EnGe1_Update,
    (ActorFunc)EnGe1_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809464D0 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x01000202, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, 0, { 0, 0, 0 } },
};

extern FlexSkeletonHeader D_06002CA0;
extern AnimationHeader D_06002B98;

void func_80945A00(Actor* actor, Lights* mapper, PlayState* play);
void func_80945CAC(EnGe1* this, PlayState* play);
void func_80945CE4(EnGe1* this, PlayState* play);

// Pictograph related
s32 func_80946190(PlayState* play, Actor* this);

// Animation
void func_809457EC(EnGe1* this, s16 index, u8 mode, f32 morphFrames);

void EnGe1_Init(Actor* thisx, PlayState* play) {
    EnGe1* this = THIS;
    s32 type;

    ActorShape_Init(&this->picto.actor.shape, 0.0f, func_80945A00, 30.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &D_06002CA0, &D_06002B98, this->jointTable, this->morphTable, 16);
    Collider_InitAndSetCylinder(play, &this->collider, &this->picto.actor, &D_809464D0);
    this->picto.actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->picto.actor.targetMode = 6;
    Actor_SetScale(&this->picto.actor, 0.01f);
    this->unk2C0 = -1;
    this->unk2BC = 0;
    this->unk2BE = this->unk2C0;
    func_809457EC(this, 0, 0, 0.0f);
    this->actionFunc = func_80945CAC;
    this->picto.pictoFunc = func_80946190;

    type = this->picto.actor.params & 0xF;
    switch (type) {
        default:
            this->unk2C4 = 0;
            break;

        case 1:
            this->unk2C4 = 1;
            break;

        case 2:
            this->unk2C4 = 2;
            break;

        case 0:
            this->unk2C4 = 0;
            this->actionFunc = func_80945CE4;
            this->picto.actor.draw = NULL;
            this->picto.actor.flags |= 0x30;
            this->picto.actor.flags &= ~1;
            break;
    }

    this->picto.actor.terminalVelocity = -9.0f;
    this->picto.actor.velocity.y = -9.0f;
    this->picto.actor.gravity = -1.0f;
}

void EnGe1_Destroy(Actor* thisx, PlayState* play) {
    EnGe1* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_809457EC(EnGe1* this, s16 index, u8 mode, f32 morphFrames) {
    static AnimationHeader* D_809464FC[] = {
        0x06002B98, 0x06002AD8, 0x06000594, 0x06000CF8, 0x060013CC,
        0x0600202C, 0x06002954, 0x06000ABC, 0x06002148, 0x06002148,
    };
    switch (index) {
        case 8:
            Animation_Change(&this->skelAnime, D_809464FC[index], 0.0f, 0.0f, 0.0f, 2, 0.0f);
            break;

        case 9:
            Animation_Change(&this->skelAnime, D_809464FC[index], 0.0f, 1.0f, 1.0f, 2, 0.0f);
            break;

        default:
            Animation_Change(&this->skelAnime, D_809464FC[index], 1.0f, 0.0f, Animation_GetLastFrame(D_809464FC[index]),
                             mode, morphFrames);
            break;
    }

    this->unk2BE = index;
}

void func_80945924(EnGe1* this, PlayState* play) {
    s16 yawDiff = this->picto.actor.yawTowardsPlayer - this->picto.actor.shape.rot.y;

    if ((ABS_ALT(yawDiff) <= 0x4300) && (this->picto.actor.xzDistToPlayer < 100.0f)) {
        Actor_TrackPlayer(play, &this->picto.actor, &this->unk2A4, &this->unk2AA, this->picto.actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk2A4.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk2A4.y, 0, 6, 0x1838, 0x64);
    }
}

void func_80945A00(Actor* thisx, Lights* mapper, PlayState* play) {
    Vec3f pos;
    EnGe1* this = THIS;

    Math_Vec3f_Copy(&pos, &thisx->world.pos);
    Math_Vec3f_Copy(&thisx->world.pos, &this->unk1D8);
    func_800B4AEC(play, thisx, 50.0f);
    thisx->world.pos.y = MAX(thisx->floorHeight, pos.y);
    ActorShadow_DrawCircle(thisx, mapper, play);
    Math_Vec3f_Copy(&thisx->world.pos, &pos);
}

void func_80945A9C(EnGe1* this, PlayState* play) {
    s32 pad;
    Vec3s* point;
    Vec3f nextPoint;

    this->unk2B4 = 0;
    if (((this->picto.actor.params & 0xFC00) >> 0xA) != 0x3F) {
        this->unk2B0 = &play->setupPathList[(this->picto.actor.params & 0xFC00) >> 0xA];
        if (this->unk2B0 != NULL) {
            point = Lib_SegmentedToVirtual(this->unk2B0->points);
            Math_Vec3s_ToVec3f(&this->picto.actor.world.pos, point);
            this->unk2B4++;
            point++;
            Math_Vec3s_ToVec3f(&nextPoint, point);

            this->picto.actor.world.rot.y = Math_Vec3f_Yaw(&this->picto.actor.world.pos, &nextPoint);
            this->picto.actor.world.rot.x = Math_Vec3f_Pitch(&this->picto.actor.world.pos, &nextPoint);
            this->picto.actor.speedXZ = 15.0f;
        }
    } else {
        this->unk2B0 = NULL;
    }
}

s32 func_80945B60(EnGe1* this) {
    s32 pad;
    Path* path = this->unk2B0;
    Vec3s* points;
    Vec3f point;
    s16 yawTarget;
    s16 pitchTarget;

    if (path == NULL) {
        return true;
    }

    points = Lib_SegmentedToVirtual(this->unk2B0->points);
    points += this->unk2B4;

    Math_Vec3s_ToVec3f(&point, points);
    yawTarget = Math_Vec3f_Yaw(&this->picto.actor.world.pos, &point);
    pitchTarget = Math_Vec3f_Pitch(&this->picto.actor.world.pos, &point);
    Math_SmoothStepToS(&this->picto.actor.world.rot.y, yawTarget, 0xA, 0x3E8, 0x64);
    Math_SmoothStepToS(&this->picto.actor.world.rot.x, pitchTarget, 6, 0x7D0, 0xC8);
    Actor_MoveWithoutGravityReverse(&this->picto.actor);

    if (Math_Vec3f_DistXYZ(&this->picto.actor.world.pos, &point) < 40.0f) {
        return true;
    } else {
        return false;
    }
}

void func_80945C50(EnGe1* this) {
    if ((s32)Rand_ZeroFloat(2.0f) == 0) {
        Actor_PlaySfxAtPos(&this->picto.actor, 0x6918);
    } else {
        Actor_PlaySfxAtPos(&this->picto.actor, 0x6919);
    }
}

void func_80945CAC(EnGe1* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    func_80945924(this, play);
}

void func_80945CE4(EnGe1* this, PlayState* play) {
    s16 csAction;

    if (SkelAnime_Update(&this->skelAnime) && (this->unk2C0 == 3)) {
        func_809457EC(this, 4, 0, 0.0f);
    }

    if (Cutscene_CheckActorAction(play, 0x79)) {
        this->picto.actor.draw = EnGe1_Draw;
        csAction = play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x79)]->action;
        switch (csAction) {
            case 8:
                this->unk2BC &= ~8;
                break;

            case 9:
                this->unk2BC |= 8;
                break;

            default:
                this->unk2BC &= ~8;
                Cutscene_ActorTranslateAndYaw(&this->picto.actor, play, Cutscene_GetActorActionIndex(play, 0x79));
                break;
        }

        if (this->unk2C0 != csAction) {
            this->unk2C0 = csAction;

            switch (this->unk2C0) {
                case 1:
                    func_809457EC(this, 0, 0, 0.0f);
                    break;

                case 2:
                    func_809457EC(this, 2, 0, 0.0f);
                    break;

                case 3:
                    func_809457EC(this, 3, 2, 0.0f);
                    break;

                case 4:
                    func_809457EC(this, 5, 2, 0.0f);
                    break;

                case 5:
                    func_809457EC(this, 6, 0, 0.0f);
                    break;

                case 6:
                    func_809457EC(this, 7, 2, 0.0f);
                    break;

                case 7:
                    Actor_MarkForDeath(&this->picto.actor);
                    break;

                case 8:
                    func_809457EC(this, 8, 2, 0.0f);
                    break;

                case 9:
                    func_809457EC(this, 9, 2, 0.0f);
                    func_80945A9C(this, play);
                    this->unk2BC |= 8;
                    this->unk2C2 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
                    break;
            }

            SkelAnime_Update(&this->skelAnime);
        }

        if ((this->unk2BE == 5) &&
            (Animation_OnFrame(&this->skelAnime, 12.0f) || Animation_OnFrame(&this->skelAnime, 25.0f))) {
            Actor_PlaySfxAtPos(&this->picto.actor, 0x2971U);
        }

        if ((this->unk2BE == 7) && Animation_OnFrame(&this->skelAnime, 14.0f)) {
            Actor_PlaySfxAtPos(&this->picto.actor, 0x2971U);
        }
    } else {
        this->picto.actor.draw = NULL;
    }

    if (this->unk2C0 == 9) {
        if ((this->unk2B4 < this->unk2B0->count) && (func_80945B60(this) != 0)) {
            this->unk2B4++;
        }

        this->picto.actor.shape.rot.x += 0x3E8;
        this->picto.actor.shape.rot.y += 0x7D0;
        this->picto.actor.shape.rot.z += 0x1F4;

        if (this->unk2C2 > 0) {
            this->unk2C2--;
        } else {
            this->unk2C2 = (s32)(Rand_ZeroFloat(10.0f) + 20.0f);
            func_80945C50(this);
        }
    }
}

void EnGe1_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGe1* this = THIS;

    if (this->picto.actor.draw != NULL) {
        Collider_UpdateCylinder(&this->picto.actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
    if (!(this->unk2BC & 8)) {
        Actor_MoveWithGravity(&this->picto.actor);
    }
    Actor_UpdateBgCheckInfo(play, &this->picto.actor, 40.0f, 25.0f, 40.0f, 5);
    this->actionFunc(this, play);
    this->unk2AA.x = this->unk2AA.y = this->unk2AA.z = 0;

    if (DECR(this->unk2BA) == 0) {
        this->unk2BA = Rand_S16Offset(60, 60);
    }

    this->unk2B8 = this->unk2BA;
    if (this->unk2B8 >= 3) {
        this->unk2B8 = 0;
    }
}

s32 func_80946190(PlayState* play, Actor* thisx) {
    s32 ret = func_8013A530(play, thisx, 9, &thisx->focus.pos, &thisx->shape.rot, 10.0f, 400.0f, -1);

    ret |= func_8013A530(play, thisx, 11, &thisx->focus.pos, &thisx->shape.rot, 10.0f, 1200.0f, -1);

    return ret;
}

s32 func_80946238(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGe1* this = THIS;
    s32 temp_v1;

    if (limbIndex == 15) {
        rot->x += this->unk2A4.y;
        rot->z += this->unk2A4.x;
    }
    if ((this->unk2BE == 0) && ((limbIndex == 8) || (limbIndex == 10) || (limbIndex == 13))) {
        temp_v1 = limbIndex * 50;
        rot->y += (s16)(Math_SinS(play->state.frames * (temp_v1 + 0x814)) * 200.0f);
        rot->z += (s16)(Math_CosS(play->state.frames * (temp_v1 + 0x940)) * 200.0f);
    }
    return false;
}

void func_80946368(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Gfx* D_80946524[] = { 0x0600BB08, 0x0600BDA0, 0x0600C000 };
    static Vec3f D_80946530 = { 600.0f, 700.0f, 0.0f };
    static Vec3f D_8094653C = { 0.0f, 0.0f, 0.0f };
    EnGe1* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(&D_8094653C, &this->unk1D8);
            break;

        case 15:
            gSPDisplayList(POLY_OPA_DISP++, D_80946524[this->unk2C4]);
            Matrix_MultVec3f(&D_80946530, &thisx->focus.pos);
            break;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnGe1_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80946548[] = {
        0x06003078,
        0x06003878,
        0x06004078,
    };
    s32 pad;
    EnGe1* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80946548[this->unk2B8]));
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80946238, func_80946368, &this->picto.actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
