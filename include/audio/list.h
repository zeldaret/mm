#ifndef AUDIO_LIST_H
#define AUDIO_LIST_H

#include "PR/ultratypes.h"

// A node in a circularly linked list. Each node is either a head or an item:
// - Items can be either detached (prev = NULL), or attached to a list.
//   'value' points to something of interest.
// - List heads are always attached; if a list is empty, its head points
//   to itself. 'count' contains the size of the list.
// If the list holds notes, 'pool' points back to the pool where it lives.
// Otherwise, that member is NULL.
typedef struct AudioListItem {
    /* 0x0 */ struct AudioListItem* prev;
    /* 0x4 */ struct AudioListItem* next;
    union {
        /* 0x8 */ void* value; // either Note* or SequenceLayer*
        /* 0x8 */ s32 count;
    } u;
    /* 0xC */ struct NotePool* pool;
} AudioListItem; // size = 0x10

typedef struct NotePool {
    /* 0x00 */ AudioListItem disabled;
    /* 0x10 */ AudioListItem decaying;
    /* 0x20 */ AudioListItem releasing;
    /* 0x30 */ AudioListItem active;
} NotePool; // size = 0x40

// playback.c functions

void AudioList_InitNoteLists(NotePool* pool);
void AudioList_InitNoteFreeList(void);
void AudioList_ClearNotePool(NotePool* pool);
void AudioList_FillNotePool(NotePool* pool, s32 count);
void AudioList_Remove(AudioListItem* item);

// seqplayer.c functions

void AudioList_PushBack(AudioListItem* list, AudioListItem* item);
void* AudioList_PopBack(AudioListItem* list);

#endif
