#include <ultra64.h>
#include <global.h>

void* GameStateHeap_GetStart(TwoHeadArena* tha) {
    return tha->head;
}

void GameStateHeap_SetStart(TwoHeadArena* tha, void* start) {
    tha->head = start;
}

void* GameStateHeap_GetEnd(TwoHeadArena* tha) {
    return tha->tail;
}

void* GameStateHeap_Alloc(TwoHeadArena* tha, u32 size) {
    void* start = tha->head;

    tha->head = (u32)tha->head + size;
    return start;
}

void* GameStateHeap_AllocByte(TwoHeadArena* tha) {
    return GameStateHeap_Alloc(tha, 1);
}

void* GameStateHeap_AllocFromEndAlignedTo(TwoHeadArena* tha, u32 size) {
    u32 mask;

    if (size >= 0x10) {
        mask = ~0xF;
    } else if (size & 1) {
        mask = -1;
    } else if (size & 2) {
        mask = ~0x1;
    } else if (size & 4) {
        mask = ~0x3;
    } else {
        mask = (size & 8) ? ~0x7 : -1;
    }

    tha->tail = (((u32)tha->tail & mask) - size) & mask;
    return tha->tail;
}

void* GameStateHeap_AllocFromEnd(TwoHeadArena* tha, u32 size) {
    u32 mask = ~0xF;

    tha->tail = (((u32)tha->tail & mask) - size) & mask;
    return tha->tail;
}

void* GameStateHeap_AllocFromEndAligned(TwoHeadArena* tha, u32 size, u32 mask) {
    tha->tail = (((u32)tha->tail & mask) - size) & mask;
    return tha->tail;
}

s32 GameStateHeap_GetFreeSize(TwoHeadArena* tha) {
    return (u32)tha->tail - (u32)tha->head;
}

u32 GameStateHeap_GetHasOverflowed(TwoHeadArena* tha) {
    return GameStateHeap_GetFreeSize(tha) < 0;
}

void GameStateHeap_InitAppend(TwoHeadArena* tha) {
    tha->head = tha->bufp;
    tha->tail = (u32)tha->bufp + tha->size;
}

void GameStateHeap_Init(TwoHeadArena* tha, void* ptr, u32 size) {
    bzero(tha, sizeof(TwoHeadArena));
    tha->bufp = ptr;
    tha->size = size;
    GameStateHeap_InitAppend(tha);
}

void GameStateHeap_Clear(TwoHeadArena* tha) {
    bzero(tha, sizeof(TwoHeadArena));
}