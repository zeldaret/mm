#ifndef VARIABLES_H
#define VARIABLES_H

#include "z64.h"
#include "segment_symbols.h"
#include "macros.h"

// data
extern ActorOverlay gActorOverlayTable[ACTOR_ID_MAX];
extern ActorId gMaxActorId;

extern FlexSkeletonHeader* gPlayerSkeletons[PLAYER_FORM_MAX];
extern PlayerModelIndices gPlayerModelTypes[];
extern struct_80124618 D_801C03A0[];
extern struct_80124618 D_801C0490[];
extern Gfx gCullBackDList[];
extern Gfx gCullFrontDList[];

extern u32 gBitFlags[32];
extern u16 gEquipMasks[];
extern u16 gEquipNegMasks[];
extern u32 gUpgradeMasks[8];
extern u32 gUpgradeNegMasks[];
extern u8 gEquipShifts[];
extern u8 gUpgradeShifts[8];
extern u16 gUpgradeCapacities[][4];
extern u32 gGsFlagsMask[];
extern u32 gGsFlagsShift[];
extern TexturePtr gItemIcons[];
extern u8 gItemSlots[];
extern s16 gItemPrices[];
extern u16 gSceneIdsPerRegion[11][27];
extern u8 gPlayerFormItemRestrictions[PLAYER_FORM_MAX][114];

extern s16 gPlayerFormObjectIds[PLAYER_FORM_MAX];
extern ObjectId gObjectTableSize;
extern RomFile gObjectTable[OBJECT_ID_MAX];

extern SceneTableEntry gSceneTable[SCENE_MAX];
extern KaleidoMgrOverlay gKaleidoMgrOverlayTable[2];
extern KaleidoMgrOverlay* gKaleidoMgrCurOvl;

extern s32 gDbgCamEnabled;

extern Vec3f gZeroVec3f;
extern Vec3s gZeroVec3s;

extern s16 gLowPassFilterData[];
extern s16 gHighPassFilterData[];
extern s16 gBandStopFilterData[];
extern s16 gBandPassFilterData[];
extern s16* gWaveSamples[9];
extern f32 gBendPitchOneOctaveFrequencies[];
extern f32 gBendPitchTwoSemitonesFrequencies[];
extern f32 gPitchFrequencies[];
extern u8 gDefaultShortNoteVelocityTable[];
extern u8 gDefaultShortNoteGateTimeTable[];
extern EnvelopePoint gDefaultEnvelope[];
extern NoteSampleState gZeroedSampleState;
extern NoteSampleState gDefaultSampleState;
extern u16 gHaasEffectDelaySize[];
extern u16 gHaasEffectDelaySize[];
extern s16 gInvalidAdpcmCodeBook[];
extern f32 gHeadsetPanVolume[];
extern f32 gStereoPanVolume[];
extern f32 gDefaultPanVolume[];
extern s32 gAudioCtxInitalized;
extern u8 D_801D6200[0x400];

extern u8 gAudioSpecId;
extern u8 gAudioHeapResetState;
extern AudioSpec gAudioSpecs[21];

// rodata
extern TexturePtr gCircleTex[];

extern const u16 gAudioEnvironmentalSfx[];
extern const s16 gAudioTatumInit[];
extern const AudioHeapInitSizes gAudioHeapInitSizes;
extern u8 gSoundFontTable[];
extern u8 gSequenceFontTable[];
extern u8 gSequenceTable[];
extern u8 gSampleBankTable[];

// bss
extern s32 gTransitionTileState;
extern Color_RGBA8_u32 gVisMonoColor;

extern GfxMasterList* gGfxMasterDL;

extern u64* gAudioSPDataPtr;
extern u32 gAudioSPDataSize;

extern s32 D_801FD120;

extern u8 sResetAudioHeapTimer;
extern u16 sResetAudioHeapFadeReverbVolume;
extern u16 sResetAudioHeapFadeReverbVolumeStep;
extern AudioContext gAudioCtx; // at 0x80200C70
extern AudioCustomUpdateFunction gAudioCustomUpdateFunction;
extern AudioCustomSeqFunction gAudioCustomSeqFunction;
extern AudioCustomReverbFunction gAudioCustomReverbFunction;
extern AudioCustomSynthFunction gAudioCustomSynthFunction;

// other segments
extern Mtx D_01000000;
extern u16 D_0F000000[];


#endif
