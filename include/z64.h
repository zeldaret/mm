#ifndef Z64_H
#define Z64_H

#include "libc/math.h"
#include "libc/stdarg.h"
#include "libc/stdbool.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "libc/stdlib.h"

#include "ultra64.h"

#include "irqmgr.h"
#include "padmgr.h"
#include "scheduler.h"

#include "color.h"
#include "ichain.h"
#include "sequence.h"
#include "seqcmd.h"
#include "sfx.h"
#include "message_data_static.h"

#include "gfx.h"
#include "gfxprint.h"
#include "padutils.h"
#include "sys_matrix.h"
#include "tha.h"
#include "thga.h"
#include "z64actor.h"
#include "z64animation.h"
#include "z64animation_legacy.h"
#include "z64audio.h"
#include "z64bgcheck.h"
#include "z64bombers_notebook.h"
#include "z64camera.h"
#include "z64collision_check.h"
#include "z64curve.h"
#include "z64cutscene.h"
#include "z64dma.h"
#include "z64eff_footmark.h"
#include "z64effect.h"
#include "z64environment.h"
#include "z64frameadvance.h"
#include "z64game_over.h"
#include "z64game.h"
#include "z64interface.h"
#include "z64item.h"
#include "z64light.h"
#include "z64map.h"
#include "z64math.h"
#include "z64message.h"
#include "z64object.h"
#include "z64ocarina.h"
#include "z64player.h"
#include "z64prerender.h"
#include "z64save.h"
#include "z64scene.h"
#include "z64schedule.h"
#include "z64skin.h"
#include "z64skybox.h"
#include "z64sound_source.h"
#include "z64subs.h"
#include "z64rumble.h"
#include "z64transition.h"
#include "z64view.h"
#include "regs.h"


typedef struct PauseContext {
    /* 0x000 */ View view;
    /* 0x168 */ u8* iconItemSegment;
    /* 0x16C */ u8* iconItem24Segment;
    /* 0x170 */ u8* iconItemAltSegment;
    /* 0x174 */ u8* iconItemLangSegment;
    /* 0x178 */ u8* nameSegment;
    /* 0x17C */ u8* iconItemVtxSegment;
    /* 0x180 */ Vtx* itemPageVtx;
    /* 0x184 */ Vtx* mapPageVtx;
    /* 0x188 */ Vtx* questPageVtx;
    /* 0x18C */ Vtx* maskPageVtx;
    /* 0x190 */ Vtx* itemVtx;
    /* 0x194 */ Vtx* mapVtx; // inferred
    /* 0x198 */ Vtx* questVtx;
    /* 0x19C */ Vtx* maskVtx;
    /* 0x1A0 */ Vtx* promptPageVtx;
    /* 0x1A4 */ Vtx* infoPanelVtx;
    /* 0x1A8 */ Vtx* cursorVtx;
    /* 0x1AC */ OcarinaStaff* ocarinaStaff;
    /* 0x1B0 */ UNK_TYPE1 unk_1B0[0x20];
    /* 0x1D0 */ OSMesgQueue loadQueue;
    /* 0x1E8 */ OSMesg loadMsg;
    /* 0x1EC */ u16 state;
    /* 0x1EE */ u16 debugEditor;
    /* 0x1F0 */ u8 bombersNotebookOpen;
    /* 0x1F4 */ Vec3f eye;
    /* 0x200 */ u16 mainState;
    /* 0x202 */ u16 nextPageMode; // (2 * prev pageIndex) + (scroll left ? 1 : 0)
    /* 0x204 */ u16 pageIndex;
    /* 0x206 */ u16 switchPageTimer;
    /* 0x208 */ u16 savePromptState;
    /* 0x20C */ f32 unk_20C; // set to 936.0f, unused remnant from OoT
    /* 0x210 */ f32 itemPageRoll; // rotation (-z) of the item page into the screen
    /* 0x214 */ f32 mapPageRoll; // rotation (+x) of the map page into the screen
    /* 0x218 */ f32 questPageRoll; // rotation (+z) of the quest page into the screen
    /* 0x21C */ f32 maskPageRoll; // rotation (-z) of the mask page into the screen
    /* 0x220 */ f32 roll;
    /* 0x224 */ u16 alpha;
    /* 0x226 */ s16 offsetY;
    /* 0x228 */ UNK_TYPE1 unk_228[0x8];
    /* 0x230 */ s32 stickAdjX;
    /* 0x234 */ s32 stickAdjY;
    /* 0x238 */ s16 cursorPoint[5];
    /* 0x242 */ s16 cursorXIndex[5];
    /* 0x24C */ s16 cursorYIndex[5];
    /* 0x256 */ s16 unk_256; // Uses DungeonItem enum
    /* 0x258 */ s16 cursorSpecialPos;
    /* 0x25A */ s16 pageSwitchInputTimer; // Used to introduce a delay before switching page when arriving on the "scroll left/right" positions while holding stick left/right.
    /* 0x25C */ u16 namedItem;
    /* 0x25E */ u16 cursorItem[5];
    /* 0x268 */ u16 cursorSlot[5];
    /* 0x272 */ u16 equipTargetItem;
    /* 0x274 */ u16 equipTargetSlot;
    /* 0x276 */ u16 equipTargetCBtn;
    /* 0x278 */ s16 equipAnimX;
    /* 0x27A */ s16 equipAnimY;
    /* 0x27C */ s16 equipAnimAlpha;
    /* 0x27E */ s16 infoPanelOffsetY;
    /* 0x280 */ u16 nameDisplayTimer;
    /* 0x282 */ u16 nameColorSet;
    /* 0x284 */ s16 cursorColorSet;
    /* 0x286 */ s16 cursorSpinPhase;
    /* 0x288 */ f32 cursorX;
    /* 0x28C */ f32 cursorY;
    /* 0x290 */ f32 cursorWidth;
    /* 0x294 */ f32 cursorHeight;
    /* 0x298 */ f32 cursorShrinkRate;
    /* 0x29C */ s16 promptChoice; // save/continue choice: 0 = yes; 4 = no
    /* 0x29E */ s16 promptAlpha;
    /* 0x2A0 */ s16 ocarinaSongIndex;
    /* 0x2A2 */ u8 worldMapPoints[20];
    /* 0x2B6 */ u8 unk_2B6; // unused red?
    /* 0x2B7 */ u8 unk_2B7; // unused green?
    /* 0x2B8 */ u8 unk_2B8; // unused blue?
    /* 0x2B9 */ u8 itemDescriptionOn; // helpful description of item given through a message box
    /* 0x2BA */ s16 equipAnimScale; // scale of item icon while moving being equipped to c-button
    /* 0x2BC */ s16 equipAnimShrinkRate; // rate the scale is shrinking for the item icon while moving being equipped to c-button
    /* 0x2BE */ s16 ocarinaButtonsY[5];
    /* 0x2C8 */ u16 unk_2C8; // Uses PauseMenuPage enum for Owl Warp. Never set.
    /* 0x2CA */ s16 unk_2CA; // Uses OwlWarpId enum for Owl Warp. Never set.
} PauseContext; // size = 0x2D0

typedef struct {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ uintptr_t vromStart;
    /* 0x08 */ uintptr_t vromEnd;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ uintptr_t offset; // loadedRamAddr - vramStart
    /* 0x18 */ const char* name;
} KaleidoMgrOverlay; // size = 0x1C

typedef enum {
    /* 0x00 */ KALEIDO_OVL_KALEIDO_SCOPE,
    /* 0x01 */ KALEIDO_OVL_PLAYER_ACTOR,
    /* 0x02 */ KALEID_OVL_MAX
} KaleidoMgrOverlayType;

typedef struct {
    /* 0x0 */ u8   seqId;
    /* 0x1 */ u8   ambienceId;
} SequenceContext; // size = 0x2

typedef struct PlayState {
    /* 0x00000 */ GameState state;
    /* 0x000A4 */ s16 sceneId;
    /* 0x000A6 */ u8 sceneConfig;
    /* 0x000A7 */ char unk_A7[0x9];
    /* 0x000B0 */ void* sceneSegment;
    /* 0x000B4 */ char unk_B4[0x4];
    /* 0x000B8 */ View view;
    /* 0x00220 */ Camera mainCamera;
    /* 0x00398 */ Camera subCameras[NUM_CAMS - CAM_ID_SUB_FIRST];
    /* 0x00800 */ Camera* cameraPtrs[NUM_CAMS];
    /* 0x00810 */ s16 activeCamId;
    /* 0x00812 */ s16 nextCamera;
    /* 0x00814 */ SequenceContext sequenceCtx;
    /* 0x00818 */ LightContext lightCtx;
    /* 0x00828 */ FrameAdvanceContext frameAdvCtx;
    /* 0x00830 */ CollisionContext colCtx;
    /* 0x01CA0 */ ActorContext actorCtx;
    /* 0x01F24 */ CutsceneContext csCtx;
    /* 0x01F78 */ SoundSource soundSources[SOUND_SOURCE_COUNT];
    /* 0x02138 */ EffFootmark footprintInfo[100];
    /* 0x046B8 */ SramContext sramCtx;
    /* 0x046E0 */ SkyboxContext skyboxCtx;
    /* 0x04908 */ MessageContext msgCtx;
    /* 0x169E8 */ InterfaceContext interfaceCtx;
    /* 0x16D30 */ PauseContext pauseCtx;
    /* 0x17000 */ GameOverContext gameOverCtx;
    /* 0x17004 */ EnvironmentContext envCtx;
    /* 0x17104 */ AnimationContext animationCtx;
    /* 0x17D88 */ ObjectContext objectCtx;
    /* 0x186E0 */ RoomContext roomCtx;
    /* 0x18760 */ DoorContext doorCtx;
    /* 0x18768 */ void (*playerInit)(Player* player, struct PlayState* play, FlexSkeletonHeader* skelHeader);
    /* 0x1876C */ void (*playerUpdate)(Player* player, struct PlayState* play, Input* input);
    /* 0x18770 */ void (*unk_18770)(struct PlayState* play, Player* player);
    /* 0x18774 */ s32 (*startPlayerFishing)(struct PlayState* play);
    /* 0x18778 */ s32 (*grabPlayer)(struct PlayState* play, Player* player);
    /* 0x1877C */ s32 (*startPlayerCutscene)(struct PlayState* play, Player* player, PlayerCsMode csMode);
    /* 0x18780 */ void (*func_18780)(Player* player, struct PlayState* play);
    /* 0x18784 */ s32 (*damagePlayer)(struct PlayState* play, s32 damage);
    /* 0x18788 */ void (*talkWithPlayer)(struct PlayState* play, Actor* actor);
    /* 0x1878C */ void (*unk_1878C)(struct PlayState* play);
    /* 0x18790 */ void (*unk_18790)(struct PlayState* play, s16 arg1);
    /* 0x18794 */ PlayerItemAction (*unk_18794)(struct PlayState* play, Player* player, ItemId itemId);
    /* 0x18798 */ s32 (*setPlayerTalkAnim)(struct PlayState* play, PlayerAnimationHeader* talkAnim, AnimationMode animMode);
    /* 0x1879C */ s16 playerCsIds[PLAYER_CS_ID_MAX];
    /* 0x187B0 */ MtxF viewProjectionMtxF;
    /* 0x187F0 */ Vec3f projectionMtxFDiagonal;
    /* 0x187FC */ MtxF billboardMtxF;
    /* 0x1883C */ Mtx* billboardMtx;
    /* 0x18840 */ u32 gameplayFrames;
    /* 0x18844 */ u8 unk_18844; // bool
    /* 0x18845 */ u8 haltAllActors;
    /* 0x18846 */ s16 numSetupActors;
    /* 0x18848 */ u8 numRooms;
    /* 0x1884C */ RomFile* roomList;
    /* 0x18850 */ ActorEntry* linkActorEntry;
    /* 0x18854 */ ActorEntry* setupActorList;
    /* 0x18858 */ ActorCsCamInfo* actorCsCamList;
    /* 0x1885C */ EntranceEntry* setupEntranceList;
    /* 0x18860 */ u16* setupExitList;
    /* 0x18864 */ Path* setupPathList;
    /* 0x18868 */ void* naviQuestHints; // leftover from OoT, system which processes this is removed
    /* 0x1886C */ AnimatedMaterial* sceneMaterialAnims;
    /* 0x18870 */ void* specialEffects;
    /* 0x18874 */ u8 skyboxId; // @see SkyboxId enum
    /* 0x18875 */ s8 transitionTrigger; // "fade_direction"
    /* 0x18876 */ s16 worldCoverAlpha;
    /* 0x18878 */ s16 bgCoverAlpha;
    /* 0x1887A */ u16 nextEntrance;
    /* 0x1887C */ s8 unk_1887C; // shootingGalleryStatus?
    /* 0x1887D */ s8 unk_1887D;
    /* 0x1887E */ s8 unk_1887E;
    /* 0x1887F */ u8 transitionType; // fadeTransition
    /* 0x18880 */ u8 unk_18880;
    /* 0x18884 */ CollisionCheckContext colChkCtx;
    /* 0x18B20 */ u16 cutsceneFlags[20];
    /* 0x18B48 */ u8 curSpawn;
    /* 0x18B49 */ u8 unk_18B49;
    /* 0x18B4A */ u8 transitionMode;
    /* 0x18B4C */ PreRender pauseBgPreRender;
    /* 0x18B9C */ char unk_18B9C[0x54];
    /* 0x18BF0 */ TransitionContext transitionCtx;
    /* 0x18E48 */ TransitionFade unk_18E48;
    /* 0x18E54 */ SceneTableEntry* loadedScene;
    /* 0x18E58 */ void* unk_18E58;
    /* 0x18E5C */ TexturePtr pictoPhotoI8;
    /* 0x18E60 */ void* unk_18E60;
    /* 0x18E64 */ void* unk_18E64;
    /* 0x18E68 */ void* unk_18E68; // framebuffer related to Lens of Truth
    /* 0x18E6C */ char unk_18E6C[0x3EC];
} PlayState; // size = 0x19258

typedef enum {
    /* 0 */ PICTO_PHOTO_STATE_OFF,
    /* 1 */ PICTO_PHOTO_STATE_SETUP,
    /* 2 */ PICTO_PHOTO_STATE_PROCESS,
    /* 3 */ PICTO_PHOTO_STATE_READY
} PictoPhotoState;

typedef struct {
    /* 0x00 */ u8 mode;
    /* 0x04 */ f32 scale;
    /* 0x08 */ f32 lodProportion; // expected to be between 0.0f and 1.0f
    /* 0x0C */ Color_RGBA8_u32 primColor;
    /* 0x10 */ Color_RGBA8_u32 envColor;
} Struct_80140E80; // size = 0x14

#endif
