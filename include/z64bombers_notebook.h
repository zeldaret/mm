#ifndef Z64BOMBERS_NOTEBOOK_H
#define Z64BOMBERS_NOTEBOOK_H

#include "ultra64.h"
#include "z64dma.h"

struct GraphicsContext;
struct Input;
struct PlayState;

#define DEFINE_PERSON(enum, _photo, _description, _metEnum, _metMessage, _metFlag) enum,
#define DEFINE_EVENT(enum, _icon, _colorFlag, _description, _completedMessage, _completedFlag)
typedef enum BombersNotebookPerson {
    #include "tables/notebook_table.h"
    /* 0x14 */ BOMBERS_NOTEBOOK_PERSON_MAX
} BombersNotebookPerson;

#undef DEFINE_PERSON
#undef DEFINE_EVENT

typedef enum BombersNotebookLoadState {
    /* 0 */ BOMBERS_NOTEBOOK_LOAD_STATE_NONE,
    /* 1 */ BOMBERS_NOTEBOOK_LOAD_STATE_STARTED,
    /* 2 */ BOMBERS_NOTEBOOK_LOAD_STATE_DONE
} BombersNotebookLoadState;

#define DEFINE_PERSON(_enum, _photo, _description, metEnum, _metMessage, _metFlag) metEnum,
#define DEFINE_EVENT(enum, _icon, _colorFlag, _description, _completedMessage, _completedFlag) enum,
typedef enum BombersNotebookEvent {
    #include "tables/notebook_table.h"
    /* 0x37 */ BOMBERS_NOTEBOOK_EVENT_MAX
} BombersNotebookEvent;

#undef DEFINE_PERSON
#undef DEFINE_EVENT

typedef struct BombersNotebook {
    /* 0x00 */ u8 loadState;
    /* 0x04 */ DmaRequest scheduleDmaDmaRequest;
    /* 0x24 */ OSMesgQueue scheduleDmaLoadQueue;
    /* 0x3C */ OSMesg scheduleDmaLoadMsg[1];
    /* 0x40 */ void* scheduleDmaSegment;
    /* 0x44 */ uintptr_t scheduleDmaSegmentStart;
    /* 0x48 */ size_t scheduleDmaSegmentSize;
    /* 0x4C */ DmaRequest scheduleDmaRequest;
    /* 0x6C */ OSMesgQueue scheduleLoadQueue;
    /* 0x84 */ OSMesg scheduleLoadMsg[1];
    /* 0x88 */ void* scheduleSegment;
    /* 0x8C */ uintptr_t scheduleSegmentStart;
    /* 0x90 */ size_t scheduleSegmentSize;
    /* 0x94 */ s32 cursorPageRow;
    /* 0x98 */ s32 cursorEntry; // Entries are 3 apart, see BOMBERS_NOTEBOOK_ENTRY_SIZE
    /* 0x9C */ s32 cursorPage;
    /* 0xA0 */ UNK_TYPE1 padA0[0x4];
    /* 0xA4 */ s32 scrollAmount;
    /* 0xA8 */ s32 scrollOffset;
} BombersNotebook; // size = 0xAC

void BombersNotebook_Draw(BombersNotebook* this, struct GraphicsContext* gfxCtx);
void BombersNotebook_Update(struct PlayState* play, BombersNotebook* this, struct Input* input);
void BombersNotebook_Init(BombersNotebook* this);
void BombersNotebook_Destroy(BombersNotebook* this);

#endif
