#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "z64.h"

Actor* Item_DropCollectible(PlayState* play, Vec3f* spawnPos, u32 params);
Actor* Item_DropCollectible2(PlayState* play, Vec3f* spawnPos, s32 params);
void Item_DropCollectibleRandom(PlayState* play, Actor* fromActor, Vec3f* spawnPos, s16 params);
s32 func_800A8150(s32 index);
s32 func_800A817C(s32 index);
bool Item_CanDropBigFairy(PlayState* play, s32 index, s32 collectibleFlag);

void ActorShape_Init(ActorShape* actorShape, f32 yOffset, ActorShadowFunc shadowDraw, f32 shadowScale);
void ActorShadow_DrawCircle(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawSquare(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawWhiteCircle(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawHorse(Actor* actor, Lights* lights, PlayState* play);

void ActorShadow_DrawFeet(Actor* actor, Lights* mapper, PlayState* play);
void Actor_SetFeetPos(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex, Vec3f* rightFootPos);
void func_800B4AEC(PlayState* play, Actor* actor, f32 y);
void func_800B4B50(Actor* actor, Lights* mapper, PlayState* play);
void Actor_GetProjectedPos(PlayState* play, Vec3f* worldPos, Vec3f* projectedPos, f32* invW);

void Target_Draw(TargetContext* targetCtx, PlayState* play);

s32 Flags_GetSwitch(PlayState* play, s32 flag);
void Flags_SetSwitch(PlayState* play, s32 flag);
void Flags_UnsetSwitch(PlayState* play, s32 flag);
s32 Flags_GetTreasure(PlayState* play, s32 flag);
void Flags_SetTreasure(PlayState* play, s32 flag);
void Flags_SetAllTreasure(PlayState* play, s32 flag);
s32 Flags_GetAllTreasure(PlayState* play);
s32 Flags_GetClear(PlayState* play, s32 roomNumber);
void Flags_SetClear(PlayState* play, s32 roomNumber);
void Flags_UnsetClear(PlayState* play, s32 roomNumber);
s32 Flags_GetClearTemp(PlayState* play, s32 roomNumber);
void Flags_SetClearTemp(PlayState* play, s32 roomNumber);
void Flags_UnsetClearTemp(PlayState* play, s32 roomNumber);
s32 Flags_GetCollectible(PlayState* play, s32 flag);
void Flags_SetCollectible(PlayState* play, s32 flag);

void TitleCard_InitBossName(GameState* gameState, TitleCardContext* titleCtx, TexturePtr texture, s16 x, s16 y, u8 width, u8 height);

s32 Actor_SetPlayerImpact(PlayState* play, PlayerImpactType type, s32 timer, f32 dist, Vec3f* pos);
f32 Actor_GetPlayerImpact(PlayState* play, f32 range, Vec3f* pos, PlayerImpactType* type);
void* Actor_AddSharedMemoryEntry(PlayState* play, s16 id, void* ptr, size_t size);
void* Actor_FreeSharedMemoryEntry(PlayState* play, s16 id);
void* Actor_FindSharedMemoryEntry(PlayState* play, s16 id);
void Actor_Kill(Actor* actor);
void Actor_SetWorldToHome(Actor* actor);
void Actor_SetFocus(Actor* actor, f32 height);
void Actor_SetWorldRotToShape(Actor* actor);
void Actor_SetShapeRotToWorld(Actor* actor);
void Actor_SetScale(Actor* actor, f32 scale);
void Actor_SetObjectDependency(PlayState* play, Actor* actor);
void Actor_SetMovementScale(s32 scale);
void Actor_UpdatePos(Actor* actor);
void Actor_UpdateVelocityWithGravity(Actor* actor);
void Actor_MoveWithGravity(Actor* actor);
void Actor_UpdateVelocityWithoutGravity(Actor* actor);
void Actor_MoveWithoutGravity(Actor* actor);
void Actor_UpdateVelocityWithoutGravityReverse(Actor* actor);
void Actor_MoveWithoutGravityReverse(Actor* actor);
void Actor_SetSpeeds(Actor* actor, f32 speed);
s16 Actor_WorldYawTowardActor(Actor* actorA, Actor* actorB);
s16 Actor_FocusYawTowardActor(Actor* actorA, Actor* actorB);
s16 Actor_WorldYawTowardPoint(Actor* actor, Vec3f* refPoint);
s16 Actor_WorldPitchTowardActor(Actor* actorA, Actor* actorB);
s16 Actor_FocusPitchTowardActor(Actor* actorA, Actor* actorB);
s16 Actor_WorldPitchTowardPoint(Actor* actor, Vec3f* refPoint);
f32 Actor_WorldDistXYZToActor(Actor* actorA, Actor* actorB);
f32 Actor_WorldDistXYZToPoint(Actor* actor, Vec3f* refPoint);
f32 Actor_WorldDistXZToActor(Actor* actorA, Actor* actorB);
f32 Actor_WorldDistXZToPoint(Actor* actor, Vec3f* refPoint);
void Actor_WorldToActorCoords(Actor* actor, Vec3f* offset, Vec3f* point);
f32 Actor_HeightDiff(Actor* actor1, Actor* actor2);
void Actor_SetControlStickData(PlayState* play, Input* input, f32 controlStickMagnitude, s16 controlStickAngle);

void func_800B72F8(DynaPolyActor* dyna, f32 extraPushForce, s16 yRotation);

s32 Actor_ActorBIsFacingActorA(Actor* actorA, Actor* actorB, s16 maxAngleDiff);
s32 Actor_IsFacingPlayer(Actor* actor, s16 angle);
s32 Actor_ActorAIsFacingActorB(Actor* actorA, Actor* actorB, s16 maxAngleDiff);
s32 Actor_IsFacingAndNearPlayer(Actor* actor, f32 range, s16 maxAngleDiff);
s32 Actor_ActorAIsFacingAndNearActorB(Actor* actorA, Actor* actorB, f32 range, s16 maxAngleDiff);

void Actor_GetSlopeDirection(CollisionPoly* floorPoly, Vec3f* slopeNormal, s16* downwardSlopeYaw);
void Actor_UpdateBgCheckInfo(PlayState* play, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius, f32 ceilingCheckHeight, u32 updBgCheckInfoFlags);
Hilite* Hilite_DrawOpa(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx);
void func_800B8050(Actor* actor, PlayState* play, s32 flag);
void func_800B8118(Actor* actor, PlayState* play, s32 flag);
PosRot Actor_GetFocus(Actor* actor);
PosRot Actor_GetWorld(Actor* actor);
PosRot Actor_GetWorldPosShapeRot(Actor* actor);

s32 Target_OutsideLeashRange(Actor* actor, Player* player, s32 ignoreLeash);
s32 Actor_TalkOfferAccepted(Actor* actor, GameState* gameState);
s32 Actor_OfferTalkExchange(Actor* actor, PlayState* play, f32 xzRange, f32 yRange, PlayerItemAction exchangeItemAction);
s32 Actor_OfferTalkExchangeEquiCylinder(Actor* actor, PlayState* play, f32 radius, PlayerItemAction exchangeItemAction);
s32 Actor_OfferTalk(Actor* actor, PlayState* play, f32 radius);
s32 Actor_OfferTalkNearColChkInfoCylinder(Actor* actor, PlayState* play);
s32 Actor_TextboxIsClosing(Actor* actor, PlayState* play);
s32 Actor_ChangeFocus(Actor* actor1, PlayState* play, Actor* actor2);

s32 func_800B8718(Actor* actor, GameState* gameState);
s32 func_800B874C(Actor* actor, PlayState* play, f32 xzRange, f32 yRange);
s32 func_800B8804(Actor* actor, PlayState* play, f32 xzRange);
s32 func_800B886C(Actor* actor, PlayState* play);
void Actor_GetScreenPos(PlayState* play, Actor* actor, s16* posX, s16* posY);
bool Actor_OnScreen(PlayState* play, Actor* actor);
s32 Actor_HasParent(Actor* actor, PlayState* play);
s32 Actor_OfferGetItem(Actor* actor, PlayState* play, GetItemId getItemId, f32 xzRange, f32 yRange);
s32 Actor_OfferGetItemNearby(Actor* actor, PlayState* play, GetItemId getItemId);
s32 Actor_OfferCarry(Actor* actor, PlayState* play);
s32 Actor_OfferGetItemFar(Actor* actor, PlayState* play, GetItemId getItemId);
s32 Actor_HasNoParent(Actor* actor, PlayState* play);
void func_800B8C20(Actor* actorA, Actor* actorB, PlayState* play);
void Actor_SetClosestSecretDistance(Actor* actor, PlayState* play);
s32 Actor_HasRider(PlayState* play, Actor* horse);
s32 Actor_SetRideActor(PlayState* play, Actor* horse, s32 mountSide);
s32 Actor_HasNoRider(PlayState* play, Actor* horse);

void Actor_PlaySfx(Actor* actor, u16 sfxId);
void Actor_PlaySfx_SurfaceBomb(PlayState* play, Actor* actor);
void Actor_PlaySfx_FlaggedCentered1(Actor* actor, u16 sfxId);
void Actor_PlaySfx_FlaggedCentered2(Actor* actor, u16 sfxId);
void Actor_PlaySfx_FlaggedCentered3(Actor* actor, u16 sfxId);
void Actor_PlaySfx_Flagged(Actor* actor, u16 sfxId);
void Actor_PlaySfx_FlaggedTimer(Actor* actor, s32 timer);
void Actor_PlaySeq_FlaggedKamaroDance(Actor* actor);
void Actor_PlaySeq_FlaggedMusicBoxHouse(Actor* actor);
s32 func_800B90AC(PlayState* play, Actor* actor, CollisionPoly* polygon, s32 bgId, Vec3f* arg4);
void Actor_DeactivateLens(PlayState* play);
void Actor_InitHalfDaysBit(ActorContext* actorCtx);
void Actor_InitContext(PlayState* play, ActorContext* actorCtx, ActorEntry* actorEntry);
void Actor_UpdateAll(PlayState* play, ActorContext* actorCtx);
s32 Actor_AddToLensActors(PlayState* play, Actor* actor);
void Actor_DrawAll(PlayState* play, ActorContext* actorCtx);
void Actor_KillAllWithMissingObject(PlayState* play, ActorContext* actorCtx);
void func_800BA798(PlayState* play, ActorContext* actorCtx);
void Actor_CleanupContext(ActorContext* actorCtx, PlayState* play);
Actor* Actor_Spawn(ActorContext* actorCtx, PlayState* play, s16 actorId, f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params);
Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, PlayState* play, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s32 params, u32 csId, u32 halfDaysBits, Actor* parent);
Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, PlayState* play, s16 actorId, f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params);
void Actor_SpawnTransitionActors(PlayState* play, ActorContext* actorCtx);
void Enemy_StartFinishingBlow(PlayState* play, Actor* actor);
s16 func_800BBAC0(BlinkInfo* info, s16 arg1, s16 arg2, s16 arg3);
s16 func_800BBB74(BlinkInfo* info, s16 arg1, s16 arg2, s16 arg3);
s16 func_800BBC20(BlinkInfo* info, s16 arg1, s16 arg2, s16 arg3);
void Actor_SpawnBodyParts(Actor* actor, PlayState* play, s32 partParams, Gfx** dList);
void Actor_SpawnFloorDustRing(PlayState* play, Actor* actor, Vec3f* posXZ, f32 radius, s32 countMinusOne, f32 randAccelWeight, s16 scale, s16 scaleStep, u8 useLighting);
void func_800BBFB0(PlayState* play, Vec3f* position, f32 arg2, s32 arg3, s16 arg4, s16 scaleStep, u8 arg6);
void Actor_ChangeCategory(PlayState* play, ActorContext* actorCtx, Actor* actor, u8 actorCategory);
u32 Actor_GetArrowDmgFlags(s32 params);
Actor* func_800BC270(PlayState* play, Actor* actor, f32 distance, u32 dmgFlags);
Actor* func_800BC444(PlayState* play, Actor* actor, f32 distance);
s16 Actor_TestFloorInDirection(Actor* actor, PlayState* play, f32 distance, s16 angle);
s32 Actor_IsTargeted(PlayState* play, Actor* actor);
s32 Actor_OtherIsTargeted(PlayState* play, Actor* actor);
void func_800BC620(Vec3f* pos, Vec3f* scale, u8 alpha, PlayState* play);
void Actor_RequestQuake(PlayState* play, s16 y, s16 duration);
void Actor_RequestQuakeWithSpeed(PlayState* play, s16 y, s16 duration, s16 speed);
void Actor_RequestQuakeAndRumble(Actor* actor, PlayState* play, s16 quakeY, s16 quakeDuration);
void Actor_DrawDoorLock(PlayState* play, s32 frame, s32 type);
void Actor_SetColorFilter(Actor* actor, u16 colorFlag, u16 colorIntensityMax, u16 bufFlag, u16 duration);
Hilite* func_800BCBF4(Vec3f* arg0, PlayState* play);
Hilite* func_800BCC68(Vec3f* arg0, PlayState* play);
void Actor_GetClosestPosOnPath(Vec3s* points, s32 numPoints, Vec3f* srcPos, Vec3f* dstPos, s32 isPathLoop);
s32 Npc_UpdateTalking(PlayState* play, Actor* actor, s16* talkState, f32 interactRange, NpcGetTextIdFunc getTextId, NpcUpdateTalkStateFunc updateTalkState);
void Npc_TrackPoint(Actor* actor, NpcInteractInfo* interactInfo, s16 presetIndex, s16 trackingMode);
void func_800BD9E0(PlayState* play, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s16 alpha);
void func_800BDAA0(PlayState* play, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s16 alpha);
void Actor_ChangeAnimationByInfo(SkelAnime* skelAnime, AnimationInfo* animInfo, s32 animIndex);
void Actor_Noop(Actor* actor, PlayState* play);

Actor* Actor_FindNearby(PlayState* play, Actor* inActor, s16 actorId, u8 actorCategory, f32 distance);
s32 func_800BE184(PlayState* play, Actor* actor, f32 xzDist, s16 arg3, s16 arg4, s16 arg5);
u8 Actor_ApplyDamage(Actor* actor);
void Actor_SetDropFlag(Actor* actor, ColliderInfo* colInfo);
void Actor_SetDropFlagJntSph(Actor* actor, ColliderJntSph* jntSphere);
void func_800BE33C(Vec3f* arg0, Vec3f* arg1, Vec3s* dst, s32 arg3);
void func_800BE3D0(Actor* actor, s16 angle, Vec3s* arg2);
void func_800BE504(Actor* actor, ColliderCylinder* collider);
void func_800BE568(Actor* actor, ColliderSphere* collider);
void func_800BE5CC(Actor* actor, ColliderJntSph* collider, s32 colliderIndex);
s32 Actor_IsSmallChest(struct EnBox* chest);
void Actor_DrawDamageEffects(PlayState* play, Actor* actor, Vec3f bodyPartsPos[], s16 bodyPartsCount, f32 effectScale, f32 frozenSteamScale, f32 effectAlpha, u8 type);
void Actor_SpawnIceEffects(PlayState* play, Actor* actor, Vec3f bodyPartsPos[], s32 bodyPartsCount, s32 effectsPerBodyPart, f32 scale, f32 scaleRange);

void DynaPolyActor_UpdateCarriedActorPos(CollisionContext* colCtx, s32 bgId, Actor* carriedActor);
void DynaPolyActor_UpdateCarriedActorRotY(CollisionContext* colCtx, s32 bgId, Actor* carriedActor);
void DynaPolyActor_AttachCarriedActor(CollisionContext* colCtx, Actor* carriedActor, s32 bgId);
u32 DynaPolyActor_TransformCarriedActor(CollisionContext* colCtx, s32 bgId, Actor* carriedActor);
void DynaPolyActor_Init(DynaPolyActor* dynaActor, s32 transformFlags);
void DynaPolyActor_LoadMesh(PlayState* play, DynaPolyActor* dynaActor, CollisionHeader* meshHeader);
void DynaPolyActor_UnsetAllInteractFlags(DynaPolyActor* dynaActor);
void DynaPolyActor_SetActorOnTop(DynaPolyActor* dynaActor);
void DynaPolyActor_SetPlayerOnTop(DynaPolyActor* dynaActor);
void DynaPoly_SetPlayerOnTop(CollisionContext* colCtx, s32 bgId);
void DynaPolyActor_SetPlayerAbove(DynaPolyActor* dynaActor);
void DynaPoly_SetPlayerAbove(CollisionContext* colCtx, s32 bgId);
void DynaPolyActor_SetActorOnSwitch(DynaPolyActor* dynaActor);
void DynaPolyActor_SetActorOnHeavySwitch(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsActorOnTop(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsPlayerOnTop(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsPlayerAbove(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsSwitchPressed(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsHeavySwitchPressed(DynaPolyActor* dynaActor);
s32 DynaPolyActor_ValidateMove(PlayState* play, DynaPolyActor* dynaActor, s16 startRadius, s16 endRadius, s16 startHeight);

void Actor_ContinueText(PlayState* play, Actor* actor, u16 textId);
s32 Flags_GetEventChkInf(s32 flag);
void Flags_SetEventChkInf(s32 flag);
s32 Flags_GetInfTable(s32 flag);
void Flags_SetInfTable(s32 flag);
s32 Actor_TrackNone(Vec3s* headRot, Vec3s* torsoRot);
s32 Actor_TrackPoint(Actor* actor, Vec3f* target, Vec3s* headRot, Vec3s* torsoRot);
s32 Actor_TrackPlayerSetFocusHeight(PlayState* play, Actor* actor, Vec3s* headRot, Vec3s* torsoRot, f32 focusHeight);
s32 Actor_TrackPlayer(PlayState* play, Actor* actor, Vec3s* headRot, Vec3s* torsoRot, Vec3f focusPos);

void GetItem_Draw(PlayState* play, s16 drawId);

void Room_Noop(PlayState* play, Room* room, Input* input, s32 arg3);
void Room_Init(PlayState* play, RoomContext* roomCtx);
size_t Room_AllocateAndLoad(PlayState* play, RoomContext* roomCtx);
s32 Room_StartRoomTransition(PlayState* play, RoomContext* roomCtx, s32 index);
s32 Room_HandleLoadCallbacks(PlayState* play, RoomContext* roomCtx);
void Room_Draw(PlayState* play, Room* room, u32 flags);

void func_8012EBF8(PlayState* play, RoomContext* roomCtx);

void func_80183070(void);

AudioTask* AudioThread_Update(void);
void AudioThread_QueueCmdF32(u32 opArgs, f32 data);
void AudioThread_QueueCmdS32(u32 opArgs, s32 data);
void AudioThread_QueueCmdS8(u32 opArgs, s8 data);
void AudioThread_QueueCmdU16(u32 opArgs, u16 data);
s32 AudioThread_ScheduleProcessCmds(void);
u32 AudioThread_GetExternalLoadQueueMsg(u32* retMsg);
u8* AudioThread_GetFontsForSequence(s32 seqId, u32* outNumFonts);
s32 func_80193C5C(void);
s32 AudioThread_ResetAudioHeap(s32 specId);
void AudioThread_PreNMIInternal(void);
s32 AudioThread_GetEnabledNotesCount(void);
u32 AudioThread_NextRandom(void);
void AudioThread_InitMesgQueues(void);

void Audio_InvalDCache(void* buf, size_t size);
void Audio_WritebackDCache(void* buf, size_t size);

void func_8019AE40(s32 param_1, s32 param_2, u32 param_3, s32 param_4);
void func_8019AEC0(UNK_PTR param_1, UNK_PTR param_2);

void Audio_Init(void);
void Audio_InitSound(void);
void Audio_Update(void);
void Audio_ResetForAudioHeapStep3(void);
void Audio_ResetForAudioHeapStep2(void);
void Audio_ResetForAudioHeapStep1(s32 specId);
void Audio_PreNMI(void);

#endif
