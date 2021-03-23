#include <ultra64.h>
#include <global.h>

void* THA_GetHead(TwoHeadArena* tha) {
    return tha->head;
}

void THA_SetHead(TwoHeadArena* tha, void* start) {
    tha->head = start;
}

void* THA_GetTail(TwoHeadArena* tha) {
    return tha->tail;
}

void* THA_AllocStart(TwoHeadArena* tha, u32 size) {
    void* start = tha->head;

    tha->head = (u32)tha->head + size;
    return start;
}

void* THA_AllocStart1(TwoHeadArena* tha) {
    return THA_AllocStart(tha, 1);
}

void* THA_AllocEnd(TwoHeadArena* tha, u32 size) {
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

void* THA_AllocEndAlign16(TwoHeadArena* tha, u32 size) {
    u32 mask = ~0xF;

    tha->tail = (((u32)tha->tail & mask) - size) & mask;
    return tha->tail;
}

void* THA_AllocEndAlign(TwoHeadArena* tha, u32 size, u32 mask) {
    tha->tail = (((u32)tha->tail & mask) - size) & mask;
    return tha->tail;
}

s32 THA_GetSize(TwoHeadArena* tha) {
    return (u32)tha->tail - (u32)tha->head;
}

u32 THA_IsCrash(TwoHeadArena* tha) {
    return THA_GetSize(tha) < 0;
}

void THA_Init(TwoHeadArena* tha) {
    tha->head = tha->bufp;
    tha->tail = (u32)tha->bufp + tha->size;
}

void THA_Ct(TwoHeadArena* tha, void* ptr, u32 size) {
    bzero(tha, sizeof(TwoHeadArena));
    tha->bufp = ptr;
    tha->size = size;
    THA_Init(tha);
}

void THA_Dt(TwoHeadArena* tha) {
    bzero(tha, sizeof(TwoHeadArena));
}