#ifndef Z64_H
#define Z64_H

#include "ultra64.h"

#include "math.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"

#include "libc64/qrand.h"

#include "color.h"
#include "gfx.h"
#include "gfxprint.h"
#include "ichain.h"
#include "irqmgr.h"
#include "main.h"
#include "message_data_static.h"
#include "padmgr.h"
#include "padutils.h"
#include "regs.h"
#include "scheduler.h"
#include "sequence.h"
#include "seqcmd.h"
#include "sfx.h"
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
#include "z64inventory.h"
#include "z64item.h"
#include "z64keyframe.h"
#include "z64lib.h"
#include "z64light.h"
#include "z64map.h"
#include "z64math.h"
#include "z64message.h"
#include "z64msgevent.h"
#include "z64object.h"
#include "z64ocarina.h"
#include "z64pause_menu.h"
#include "z64player.h"
#include "z64prerender.h"
#include "z64save.h"
#include "z64scene.h"
#include "z64schedule.h"
#include "z64skin_matrix.h"
#include "z64skin.h"
#include "z64skybox.h"
#include "z64sound_source.h"
#include "z64subs.h"
#include "z64rumble.h"
#include "z64transition.h"
#include "z64view.h"


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
    /* 0x18760 */ TransitionActorList transitionActors;
    /* 0x18768 */ void (*playerInit)(Player* player, struct PlayState* play, FlexSkeletonHeader* skelHeader);
    /* 0x1876C */ void (*playerUpdate)(Player* player, struct PlayState* play, Input* input);
    /* 0x18770 */ void (*unk_18770)(struct PlayState* play, Player* player);
    /* 0x18774 */ s32 (*startPlayerFishing)(struct PlayState* play);
    /* 0x18778 */ s32 (*grabPlayer)(struct PlayState* play, Player* player);
    /* 0x1877C */ s32 (*tryPlayerCsAction)(struct PlayState* play, Player* player, PlayerCsAction csAction);
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

#endif
