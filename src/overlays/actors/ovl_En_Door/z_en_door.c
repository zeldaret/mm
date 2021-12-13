/*
 * File: z_en_door.c
 * Overlay: ovl_En_Door
 * Description: Wooden Door
 */

#include "z_en_door.h"

#define FLAGS 0x00000010

#define THIS ((EnDoor*)thisx)

void EnDoor_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80866B20(EnDoor*, GlobalContext*); /* extern */
void func_8086704C(EnDoor*, GlobalContext*); /* extern */
void func_80866F94(EnDoor*, GlobalContext*);        /* extern */
void func_80867080(EnDoor*, GlobalContext*);        /* extern */
void func_80867144(EnDoor*, GlobalContext*);        /* extern */

#if 0
const ActorInit En_Door_InitVars = {
    ACTOR_EN_DOOR,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoor),
    (ActorFunc)EnDoor_Init,
    (ActorFunc)EnDoor_Destroy,
    (ActorFunc)EnDoor_Update,
    (ActorFunc)EnDoor_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80867954[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.x, 0, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.z, 0, ICHAIN_STOP),
};

#endif

typedef struct {
    /* 0x00 */ s16 sceneNum;
    /* 0x02 */ u8 dListIndex;
    /* 0x04 */ s16 objectId;
} EnDoorInfo;
#if 0
EnDoorInfo sObjInfo[] = {
    { SCENE_MITURIN, 0x01, OBJECT_NUMA_OBJ },
    { SCENE_TENMON_DAI, 0x02, OBJECT_DOR01 },
    { SCENE_00KEIKOKU, 0x02, OBJECT_DOR01 },
    { SCENE_30GYOSON, 0x02, OBJECT_DOR01 },
    { SCENE_LABO, 0x02, OBJECT_DOR01 },
    { SCENE_33ZORACITY, 0x03, OBJECT_DOR02 },
    { SCENE_UNSET_31, 0x03, OBJECT_DOR02 },
    { SCENE_BANDROOM, 0x03, OBJECT_DOR02 },
    { SCENE_20SICHITAI, 0x04, OBJECT_DOR03 },
    { SCENE_20SICHITAI2, 0x04, OBJECT_DOR03 },
    { SCENE_MAP_SHOP, 0x04, OBJECT_DOR03 },
    { SCENE_KAIZOKU, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_SYATEKI_MORI, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_TORIDE, 0x0B, OBJECT_KAIZOKU_OBJ },
    { SCENE_KINDAN2, 0x0C, OBJECT_KINSTA2_OBJ },
    { -1, 0x00, GAMEPLAY_KEEP }, //Split here?
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x07, OBJECT_WDOR02 },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x07, OBJECT_WDOR02 },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x09, OBJECT_WDOR04 },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x08, OBJECT_WDOR03 },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x06, OBJECT_WDOR01 },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x00, GAMEPLAY_KEEP },
    { -1, 0x0A, OBJECT_WDOR05 },
    { -1, 0x0D, GAMEPLAY_FIELD_KEEP },
    { -1, 0x05, OBJECT_DOR04 },
    { -1, 0x09, OBJECT_WDOR04 },
    { -1, 0x04, OBJECT_DOR03 },
};
#endif
extern InitChainEntry D_80867954[];
void func_80866A5C(EnDoor*, GlobalContext*); /* extern */
extern AnimationHeader D_04020658;
extern SkeletonHeader D_04022B28;
extern EnDoorInfo sObjInfo[16];
extern EnDoorInfo D_80867886[];
extern CollisionHeader D_04023100;
extern AnimationHeader* D_80867964[];
extern s32* D_8086778C[];
extern u8 D_80867BC0[0x10]; //BSS

void EnDoor_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 objectBankIndex;
    EnDoorInfo* objectInfo;
    EnDoor* this = (EnDoor*)thisx;
    s32 i;

    objectInfo = sObjInfo;
    Actor_ProcessInitChain(&this->dyna.actor, D_80867954);

    this->unk1A4 = (thisx->params >> 7) & 7;

    this->switchFlag = this->dyna.actor.params & 0x7F;
    if ((this->unk1A4 == 7) && (this->switchFlag == 0)) {
        BcCheck3_BgActorInit((DynaPolyActor*)this, 0);
        BgCheck3_LoadMesh(globalCtx, (DynaPolyActor*)this, (CollisionHeader*)&D_04023100);
    }
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_04022B28, &D_04020658, this->limbTable, this->limbTable, 5);
    if (this->unk1A4 == 5) {
        objectInfo = &sObjInfo[17 + this->switchFlag];
    } else {
        for (i = 0; i < ARRAY_COUNT(sObjInfo) - 1; i++, objectInfo++) {
            if (globalCtx->sceneNum == objectInfo->sceneNum) {
                break;
            }
        }
        if ((i >= ARRAY_COUNT(sObjInfo) - 1) && (Object_GetIndex(&globalCtx->objectCtx, 2) >= 0)) {
            objectInfo++;
        }
    }

    this->dlIndex = objectInfo->dListIndex;
    objectBankIndex = Object_GetIndex(&globalCtx->objectCtx, objectInfo->objectId);
    if (objectBankIndex < 0) {
        objectInfo = &sObjInfo[15];
        objectBankIndex = Object_GetIndex(&globalCtx->objectCtx, objectInfo->objectId);
        if (objectBankIndex != 0) {
            Actor_MarkForDeath(&this->dyna.actor);
            return;
        }
    }
    this->requiredObjBankIndex = objectBankIndex;
    this->dlIndex = objectInfo->dListIndex;
    if (this->dyna.actor.objBankIndex == this->requiredObjBankIndex) {
        func_80866A5C(this, globalCtx);
    } else {
        this->actionFunc = func_80866A5C;
    }
    Actor_SetHeight(&this->dyna.actor, 35.0f);
}
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Destroy.s")

void func_80866A5C(EnDoor* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->requiredObjBankIndex) != 0) {
        this->dyna.actor.objBankIndex = this->requiredObjBankIndex;
        this->actionFunc = func_80866B20;
        this->dyna.actor.world.rot.y = 0;
        if (this->unk1A4 == 1) {
            if (Flags_GetSwitch(globalCtx, this->switchFlag) == 0) {
                this->unk1A6 = 0xA;
            }
        } else if ((this->unk1A4 == 4) && (Actor_XZDistanceBetweenActors(
                                               &this->dyna.actor, globalCtx->actorCtx.actorList[2].first) > 120.0f)) {
            this->actionFunc = func_8086704C;
            this->dyna.actor.world.rot.y = -0x1800;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80866B20.s")
void func_80866B20(EnDoor* this, GlobalContext* globalCtx) {
    Player* player;
    Vec3f sp58;
    struct_80133038_arg2 sp30;
    
    s16 temp_a2;
    s16 yawDiff;
    s32 temp_a1_2;
    s32 temp_t0;
    u8 temp_a1;
    f32 animSpeed;
    s32 baseTextId;

    player = GET_PLAYER(globalCtx);
    if ((func_800B84D0(&this->dyna.actor, globalCtx) != 0) && (this->dyna.actor.textId == 0x1821)) {
        D_80867BC0[0] = 1;
    }
    if (this->unk1A1 != 0) {
        this->actionFunc = func_80867144;
        if ((player->stateFlags1 << 4) != 0) {
            animSpeed = 0.75f;
        } else {
            animSpeed = 1.5f;
        }
        Animation_PlayOnceSetSpeed(&this->skelAnime, D_80867964[this->animIndex], animSpeed);
        if (this->unk1A6 != 0) {
            //temp_t5 = gSaveContext.mapIndex;
            gSaveContext.inventory.dungeonKeys[gSaveContext.mapIndex] += -1;
            Actor_SetSwitchFlag(globalCtx, this->switchFlag);
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_CHAIN_KEY_UNLOCK);
            return;
        }
        /* Duplicate return node #55. Try simplifying control flow for better match */
        return;
    }
    if (this->unk_1A7 != 0) {
        this->actionFunc = func_80866F94;
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DOOR_OPEN);
        return;
    }
    if (func_801233E4(globalCtx) == 0) {
        Actor_CalcOffsetOrientedToDrawRotation(&this->dyna.actor, &sp58, &player->actor.world.pos);
        if ((D_80867BC0[0] != 0) || ((fabsf(sp58.y) < 20.0f) && (fabsf(sp58.x) < 20.0f) && (fabsf(sp58.z) < 50.0f))) {
            yawDiff = player->actor.shape.rot.y - this->dyna.actor.shape.rot.y;
            if (sp58.z > 0.0f) {
                yawDiff =  (0x8000 - yawDiff);
            }
            //phi_v1 = phi_v0;
            //if (phi_v0 < 0) {
            //    phi_v1 = -phi_v0;
            //}
            if (ABS(yawDiff) < 0x3000) {
                player->doorType = 1;
                if (sp58.z >= 0.0f) {
                    player->doorDirection =  1.0f;
                } else {
                    player->doorDirection =  -1.0f;
                }
                player->doorActor = &this->dyna.actor;
                if (this->unk1A6 != 0) {
                    if (gSaveContext.inventory.dungeonKeys[gSaveContext.mapIndex] <= 0) {
                        player->doorType = -1;
                        this->dyna.actor.textId = 0x1802;
                    } else {
                        player->doorTimer = 10;
                    }
                } else {
                    if (this->unk1A4 == 4) {
                        player->doorType = -1;
                        this->dyna.actor.textId = 0x1800;
                    } else if ((this->unk1A4 == 0) || (this->unk1A4 == 2) || (this->unk1A4 == 3)) {
                        temp_t0 = (globalCtx->actorCtx.unkC & 0x2AA) >> 1;
                        temp_a2 = D_801AED48[this->switchFlag & 7];
                        temp_a1_2 = globalCtx->actorCtx.unkC & 0x155;
                        if (((this->unk1A4 == 0) && (((temp_t0 | temp_a1_2) & temp_a2) == 0)) || ((this->unk1A4 == 2) && ((temp_a2 & temp_a1_2) == 0)) || ((this->unk1A4 == 3) && ((temp_a2 & temp_t0) == 0))) {
                            baseTextId = 0x182D;
                            if (this->unk1A4 == 3) {
                                baseTextId = 0x180D;
                            } else if (this->unk1A4 == 2) {
                                baseTextId = 0x181D;
                            }
                            player->doorType = -1;
                            this->dyna.actor.textId = baseTextId + ((this->switchFlag >> 3) & 0xF);
                        }
                    } else if ((this->unk1A4 == 5) && (sp58.z > 0.0f)) {
                        if (func_80133038(globalCtx, D_8086778C[this->switchFlag], &sp30) != 0) {
                            this->dyna.actor.textId = sp30.unk0 + 0x1800;
                            if ((this->dyna.actor.textId == 0x1821) && (D_80867BC0[0] != 0)) {
                                player->doorType = 5;
                            } else {
                                player->doorType = -1;
                            }
                        }
                    }
                }
                func_80122F28(player, globalCtx, &this->dyna.actor);
                return;
            }
            /* Duplicate return node #55. Try simplifying control flow for better match */
            return;
        }
        if (this->unk1A4 == 4) {
            if (this->dyna.actor.xzDistToPlayer > 240.0f) {
                Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_DOOR_OPEN);
                this->actionFunc = func_80867080;
            }
        }
        /* Duplicate return node #55. Try simplifying control flow for better match */
    }
}


#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80866F94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_8086704C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80867080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_808670F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80867144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/func_80867350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door/EnDoor_Draw.s")
