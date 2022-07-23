/*
 * File: z_obj_taru.c
 * Overlay: ovl_Obj_Taru
 * Description: Wooden Barrel
 */

#include "z_obj_taru.h"
#include "overlays/actors/ovl_En_Sw/z_en_sw.h"
#include "overlays/effects/ovl_Effect_Ss_Kakera/z_eff_ss_kakera.h"

#define FLAGS 0x00000000

#define THIS ((ObjTaru*)thisx)

void ObjTaru_Init(Actor* thisx, PlayState* play);
void ObjTaru_Destroy(Actor* thisx, PlayState* play);
void ObjTaru_Update(Actor* thisx, PlayState* play);
void ObjTaru_Draw(Actor* thisx, PlayState* play);

void func_80B9C07C(ObjTaru* this, PlayState* play);
void func_80B9C174(ObjTaru* this, PlayState* play);
void func_80B9C1A0(ObjTaru* this, PlayState* play);

#if 0
const ActorInit Obj_Taru_InitVars = {
    ACTOR_OBJ_TARU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TARU,
    sizeof(ObjTaru),
    (ActorFunc)ObjTaru_Init,
    (ActorFunc)ObjTaru_Destroy,
    (ActorFunc)ObjTaru_Update,
    (ActorFunc)ObjTaru_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B9C340 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x80000508, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 30, 50, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9C36C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80B9C340;
extern InitChainEntry D_80B9C36C[];
extern CollisionHeader D_06000FC8;
extern Gfx* D_06000420;
extern UNK_TYPE D_06001040;
extern UNK_TYPE D_06001100;
extern UNK_TYPE D_06001CB0;
extern Gfx* D_06001140;
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9B6E0.s")

s32 func_80B9B6E0(ObjTaru* this, PlayState* play) {
    s32 chestFlag = -1;
    s32 skulltulaParams = (OBJ_TARU_P001F(&this->dyna.actor) * 4) | 0xFF01;
    s32 temp_v0_2;
    s32 phi_v0;

    if (ENSW_GETS_3(skulltulaParams)) {
        chestFlag = ENSW_GETS_3FC(skulltulaParams);
    }

    return (chestFlag < 0) == true || !Flags_GetTreasure(play, chestFlag);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9B74C.s")

void func_80B9B74C(ObjTaru* this, PlayState* play) {
    s32 pad[2];
    Vec3f* thisPos = &this->dyna.actor.world.pos;
    Vec3f pos;
    Vec3f velocity;
    s16 angle;
    s32 i;

    for (i = 0, angle = 0; i < 0x10; i++, angle += 0x4E20) {
        f32 sin = Math_SinS(angle);
        f32 cos = Math_CosS(angle);
        f32 tempRand = Rand_ZeroOne() * 30.0f;
        s32 phi_s0;

        pos.x = sin * tempRand;
        pos.y = (Rand_ZeroOne() * 10.0f) + 2.0f;
        pos.z = cos * tempRand;
        velocity.x = pos.x * 0.2f;
        velocity.y = (Rand_ZeroOne() * 10.0f) + 2.0f;
        velocity.z = pos.z * 0.2f;
        pos.x += thisPos->x;
        pos.y += thisPos->y;
        pos.z += thisPos->z;
        tempRand = Rand_ZeroOne();
        if (tempRand < 0.05f) {
            phi_s0 = 0x60;
        } else if (tempRand < 0.7f) {
            phi_s0 = 0x40;
        } else {
            phi_s0 = 0x20;
        }
        EffectSsKakera_Spawn(play, &pos, &velocity, &pos, -200, phi_s0, 28, 2, 0, (Rand_ZeroOne() * 30.0f) + 5.0f, 0, 0,
                             70, KAKERA_COLOR_NONE, OBJECT_KIBAKO2, &D_06001040);
    }
    func_800BBFB0(play, thisPos, 90.0f, 6, 100, 160, 1);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9B9C8.s")

void func_80B9B9C8(ObjTaru *this, PlayState *play) {
    s32 phi_s5;
    s32 i;
    s32 j;
    Vec3f spD8;
    Vec3f spCC;
    s32 pad[2];
    f32 spC0;
    f32 spBC;
    s32 phi_fp;
    Vec3f *temp_s1;
    f32 temp_fs0;
    f32 temp_fs1;


    spC0 = Math_SinS(this->dyna.actor.shape.rot.y);
    spBC = Math_CosS(this->dyna.actor.shape.rot.y);
    if ((this->dyna.actor.params & 0x100) != 0) {
        phi_fp = 0;
        phi_s5 = 8;
    } else {
        phi_fp = 2;
        phi_s5 = 6;
    }
            temp_s1 = &this->dyna.actor.world.pos;
    for (i = 0; i < 4; i++) {
            for (j = phi_fp; j < phi_s5; j++) {
                temp_fs0 = randPlusMinusPoint5Scaled(10.0f) + -105.0f + (j * 30.0f);
                temp_fs1 = randPlusMinusPoint5Scaled(4.0f);
                spD8.x = temp_fs0 * spBC;
                spD8.y = randPlusMinusPoint5Scaled(10.0f) + 15.0f + (i * 30.0f);
                spD8.z = temp_fs0 * spC0;
                spCC.x = (spD8.x * 0.05f) + (temp_fs1 * spC0);
                spCC.y = Rand_ZeroFloat(5.0f) + 2.0f;
                spCC.z = (spD8.z * 0.05f) + (temp_fs1 * spBC);
                spD8.x += temp_s1->x;
                spD8.y += temp_s1->y;
                spD8.z += temp_s1->z;
                EffectSsKakera_Spawn(play, &spD8, &spCC, &spD8, -0x64, 0x20, 0x1C, 4, 0, (s32) ((Rand_ZeroOne() * 30.0f) + 5.0f), 0, 0, 0x5A, -1, 0x133, (Gfx *) &D_06001100);
            }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BC64.s")

void func_80B9BC64(ObjTaru* this, PlayState* play) {
    s32 temp_v0;

    temp_v0 = func_800A8150(this->dyna.actor.params & 0x3F);
    if (temp_v0 >= 0) {
        Item_DropCollectible(play, &this->dyna.actor.world.pos,
                             ((((s16)this->dyna.actor.params >> 8) & 0x7F) << 8) | temp_v0);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BCBC.s")

void func_80B9BCBC(ObjTaru* this, PlayState* play) {
    s32 pad;
    s32 params;
    Actor* spawnedActor;
    s16 rotY;

    if (func_80B9B6E0(this, play) != 0) {
        params = ((this->dyna.actor.params & 0x1F) * 4) | 0xFF01;
        rotY = ((Rand_Next() >> 0x11) + this->dyna.actor.yawTowardsPlayer + 0xC000);
        spawnedActor = Actor_Spawn(&play->actorCtx, play, 0x50, this->dyna.actor.world.pos.x,
                                   this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0, rotY, 0, params);
        if (spawnedActor != NULL) {
            spawnedActor->parent = &this->dyna.actor;
            spawnedActor->velocity.y = 12.0f;
            spawnedActor->speedXZ = 2.0f;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BD84.s")

void func_80B9BD84(ObjTaru* this, PlayState* play) {
    if (!((this->dyna.actor.params >> 0xF) & 1)) {
        func_80B9BC64(this, play);
    } else {
        func_80B9BCBC(this, play);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Init.s")

void ObjTaru_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjTaru* this = THIS;
    s32 paramsF;

    DynaPolyActor_Init(&this->dyna, 0);
    Actor_ProcessInitChain(&this->dyna.actor, D_80B9C36C);
    if ((this->dyna.actor.params & 0x80) != 0) {
        if (Flags_GetSwitch(play, this->dyna.actor.params & 0x7F) != 0) {
            Actor_MarkForDeath(&this->dyna.actor);
        } else {
            DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06001CB0);
        }
        if ((this->dyna.actor.params & 0x100) != 0) {
            this->dyna.actor.scale.x = 0.2f;
        }
    } else {
        paramsF = (this->dyna.actor.params >> 0xF) & 1;
        DynaPolyActor_LoadMesh(play, &this->dyna, &D_06000FC8);
        Collider_InitAndSetCylinder(play, &this->collider, &this->dyna.actor, &D_80B9C340);
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        if (paramsF == 0) {
            if (Item_CanDropBigFairy(play, this->dyna.actor.params & 0x3F, (this->dyna.actor.params >> 8) & 0x7F) !=
                0) {
                this->unk1AC = 1;
                this->dyna.actor.flags |= 0x10;
            }
        }
        if ((paramsF != 1) || (func_80B9B6E0(this, play) == 0)) {
            this->unk1AD = -1;
        }
    }
    this->actionFunc = func_80B9C07C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Destroy.s")

void ObjTaru_Destroy(Actor* thisx, PlayState* play) {
    ObjTaru* this = THIS;

    if (!(this->dyna.actor.params & 0x80)) {
        Collider_DestroyCylinder(play, &this->collider);
    }
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9BF7C.s")

s32 func_80B9BF7C(ObjTaru* this) {
    s32 pad;
    s32 phi_a3 = 0;

    if ((!(this->dyna.actor.params & 0x80)) && ((this->collider.base.acFlags & 2))) {
        Actor* ac = this->collider.base.ac;

        this->collider.base.acFlags &= 0xFFFD;
        if (ac != NULL) {
            if (this->collider.info.acHitInfo->toucher.dmgFlags & 0x80000000) {
                phi_a3 = 0;
                if (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &ac->world.pos) < 25600.0f) {
                    phi_a3 = 1;
                }
            } else if (this->collider.info.acHitInfo->toucher.dmgFlags & 8) {
                if (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &ac->world.pos) < 10000.0f) {
                    phi_a3 = 1;
                }
            } else if (this->collider.info.acHitInfo->toucher.dmgFlags & 0x500) {
                phi_a3 = 1;
            }
        }
    } else if (this->dyna.actor.home.rot.z != 0) {
        phi_a3 = 1;
    }
    return phi_a3;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9C07C.s")

void func_80B9C07C(ObjTaru* this, PlayState* play) {
    if (func_80B9BF7C(this) != 0) {
        if ((this->dyna.actor.params & 0x80) == 0) {
            func_80B9B74C(this, play);
        } else {
            func_80B9B9C8(this, play);
        }
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 0x14U, 0x28AAU);
        if ((this->dyna.actor.params & 0x80) != 0) {
            this->actionFunc = func_80B9C1A0;
            return;
        }
        this->dyna.actor.flags |= 0x10;
        func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
        this->dyna.actor.draw = NULL;
        this->actionFunc = func_80B9C174;
        return;
    }
    if (this->dyna.actor.xzDistToPlayer < 600.0f) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9C174.s")

void func_80B9C174(ObjTaru* this, PlayState* play) {
    func_80B9BD84(this, play);
    Actor_MarkForDeath(&this->dyna.actor);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/func_80B9C1A0.s")

void func_80B9C1A0(ObjTaru* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        Flags_SetSwitch(play, this->dyna.actor.params & 0x7F);
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Update.s")

void ObjTaru_Update(Actor* thisx, PlayState* play) {
    ObjTaru* this = THIS;

    if (!(this->dyna.actor.params & 0x80)) {
        if (this->unk1AC != 0) {
            play->actorCtx.unk5 |= 8;
        }
        if (this->unk1AD >= 0) {
            switch (this->unk1AD) {
                case 0:
                    Actor_PlaySfxAtPos(&this->dyna.actor, 0x39DA);
                    if (Rand_ZeroOne() < 0.1f) {
                        this->unk1AD = Rand_S16Offset(0x28, 0x50);
                    } else {
                        this->unk1AD = 8;
                    }
                    break;
                default:
                    this->unk1AD--;
                    break;
            }
        }
    }
    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Taru/ObjTaru_Draw.s")

void ObjTaru_Draw(Actor* thisx, PlayState* play) {
    Gfx* dList;
    ObjTaru* this = THIS;

    if (this->dyna.actor.params & 0x80) {
        dList = &D_06001140;
    } else {
        dList = &D_06000420;
    }
    Gfx_DrawDListOpa(play, dList);
}
