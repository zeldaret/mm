#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "z64.h"

Actor* Item_DropCollectible(PlayState* play, Vec3f* spawnPos, u32 params);
Actor* Item_DropCollectible2(PlayState* play, Vec3f* spawnPos, s32 params);
void Item_DropCollectibleRandom(PlayState* play, Actor* fromActor, Vec3f* spawnPos, s16 params);
s32 func_800A8150(s32 index);
s32 func_800A817C(s32 index);
bool Item_CanDropBigFairy(PlayState* play, s32 index, s32 collectibleFlag);

// Ideally these two prototypes would be in z64actor.h, but they use PlayerItemAction which would require including z64player.h there.
s32 Actor_OfferTalkExchange(Actor* actor, struct PlayState* play, f32 xzRange, f32 yRange, PlayerItemAction exchangeItemAction);
s32 Actor_OfferTalkExchangeEquiCylinder(Actor* actor, struct PlayState* play, f32 radius, PlayerItemAction exchangeItemAction);

void GetItem_Draw(PlayState* play, s16 drawId);

void Room_Noop(PlayState* play, Room* room, Input* input, s32 arg3);
void Room_Init(PlayState* play, RoomContext* roomCtx);
size_t Room_SetupFirstRoom(PlayState* play, RoomContext* roomCtx);
s32 Room_RequestNewRoom(PlayState* play, RoomContext* roomCtx, s32 index);
s32 Room_ProcessRoomRequest(PlayState* play, RoomContext* roomCtx);
void Room_Draw(PlayState* play, Room* room, u32 flags);

void Room_FinishRoomChange(PlayState* play, RoomContext* roomCtx);

NORETURN void func_80183070(void);

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
