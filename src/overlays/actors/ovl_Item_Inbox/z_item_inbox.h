#ifndef Z_ITEM_INBOX_H
#define Z_ITEM_INBOX_H

#include <global.h>

struct ItemInbox;

typedef struct ItemInbox {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ItemInbox; // size = 0x148

extern const ActorInit Item_Inbox_InitVars;

#endif // Z_ITEM_INBOX_H
