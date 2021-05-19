#include <ultra64.h>
#include <global.h>

#define FILL_ALLOCBLOCK (1 << 0)
#define FILL_FREEBLOCK (1 << 1)
#define CHECK_FREE_BLOCK (1 << 2)

#define NODE_MAGIC (0x7373)

#define BLOCK_UNINIT_MAGIC (0xAB)
#define BLOCK_UNINIT_MAGIC_32 (0xABABABAB)
#define BLOCK_ALLOC_MAGIC (0xCD)
#define BLOCK_ALLOC_MAGIC_32 (0xCDCDCDCD)
#define BLOCK_FREE_MAGIC (0xEF)
#define BLOCK_FREE_MAGIC_32 (0xEFEFEFEF)

extern OSMesg sArenaLockMsg[1];

void ArenaImpl_LockInit(Arena* arena) {
    osCreateMesgQueue(&arena->lock, sArenaLockMsg, ARRAY_COUNT(sArenaLockMsg));
}

void ArenaImpl_Lock(Arena* arena) {
    osSendMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

void ArenaImpl_Unlock(Arena* arena) {
    osRecvMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

ArenaNode* heap_get_tail(Arena* arena) {
    ArenaNode* last;
    ArenaNode* iter;

    last = arena->head;

    if (last != NULL) {
        iter = last->next;
        while (iter != NULL) {
            last = iter;
            iter = iter->next;
        }
    }
    return last;
}

void __osMallocInit(Arena* arena, void* start, u32 size) {
    bzero(arena, sizeof(*arena));
    ArenaImpl_LockInit(arena);
    __osMallocAddBlock(arena, start, size);
    arena->isInit = 1;
}

void __osMallocAddBlock(Arena* arena, void* start, s32 size) {
    s32 diff;
    s32 size2;
    ArenaNode* firstNode;
    ArenaNode* lastNode;

    if (start != NULL) {
        firstNode = (ArenaNode*)ALIGN16((u32)start);
        diff = (s32)firstNode - (s32)start;
        size2 = (size - diff) & ~0xF;

        if (size2 > (s32)sizeof(ArenaNode)) {
            firstNode->next = NULL;
            firstNode->prev = NULL;
            firstNode->size = size2 - sizeof(ArenaNode);
            firstNode->isFree = 1;
            firstNode->magic = NODE_MAGIC;
            ArenaImpl_Lock(arena);
            lastNode = heap_get_tail(arena);
            if (lastNode == NULL) {
                arena->head = firstNode;
                arena->start = start;
            } else {
                firstNode->prev = lastNode;
                lastNode->next = firstNode;
            }
            ArenaImpl_Unlock(arena);
        }
    }
}

void __osMallocCleanup(Arena* arena) {
    bzero(arena, sizeof(*arena));
}

u8 __osMallocIsInitalized(Arena* arena) {
    return arena->isInit;
}

void* __osMalloc(Arena* arena, u32 size) {
    ArenaNode* iter;
    ArenaNode* newNode;
    void* alloc;
    u32 blockSize;
    alloc = NULL;

    size = ALIGN16(size);
    ArenaImpl_Lock(arena);
    iter = arena->head;

    while (iter != NULL) {
        if (iter->isFree && iter->size >= size) {
            ArenaNode* next;
            blockSize = ALIGN16(size) + sizeof(ArenaNode);
            if (blockSize < iter->size) {
                newNode = (ArenaNode*)((u32)iter + blockSize);
                newNode->next = iter->next;
                newNode->prev = iter;
                newNode->size = iter->size - blockSize;
                newNode->isFree = 1;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size = size;
                next = newNode->next;
                if (next) {
                    next->prev = newNode;
                }
            }

            iter->isFree = 0;
            alloc = (void*)((u32)iter + sizeof(ArenaNode));
            break;
        }

        iter = iter->next;
    }
    ArenaImpl_Unlock(arena);

    return alloc;
}

void* __osMallocR(Arena* arena, u32 size) {
    ArenaNode* iter;
    ArenaNode* newNode;
    u32 blockSize;
    void* alloc = NULL;

    size = ALIGN16(size);
    ArenaImpl_Lock(arena);
    iter = heap_get_tail(arena);

    while (iter != NULL) {
        if (iter->isFree && iter->size >= size) {
            ArenaNode* next;
            blockSize = ALIGN16(size) + sizeof(ArenaNode);
            if (blockSize < iter->size) {
                newNode = (ArenaNode*)((u32)iter + (iter->size - size));
                newNode->next = iter->next;
                newNode->prev = iter;
                newNode->size = size;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size -= blockSize;
                next = newNode->next;
                if (next) {
                    next->prev = newNode;
                }
                iter = newNode;
            }

            iter->isFree = 0;
            alloc = (void*)((u32)iter + sizeof(ArenaNode));
            break;
        }
        iter = iter->prev;
    }
    ArenaImpl_Unlock(arena);

    return alloc;
}

void __osFree(Arena* arena, void* ptr) {
    ArenaNode* node;
    ArenaNode* next;
    ArenaNode* prev;
    ArenaNode* newNext;

    ArenaImpl_Lock(arena);
    node = (ArenaNode*)((u32)ptr - sizeof(ArenaNode));

    if (ptr == NULL || (node->magic != NODE_MAGIC) || node->isFree) {
        goto end;
    }

    next = node->next;
    prev = node->prev;
    node->isFree = 1;

    newNext = next;
    if ((u32)next == (u32)node + sizeof(ArenaNode) + node->size && next->isFree) {
        newNext = next->next;
        if (newNext != NULL) {
            newNext->prev = node;
        }

        node->size += next->size + sizeof(ArenaNode);

        node->next = newNext;
        next = newNext;
    }

    if (prev != NULL && prev->isFree && (u32)node == (u32)prev + sizeof(ArenaNode) + prev->size) {
        if (next) {
            next->prev = prev;
        }
        prev->next = next;
        prev->size += node->size + sizeof(ArenaNode);
    }

end:
    ArenaImpl_Unlock(arena);
}

#pragma GLOBAL_ASM("./asm/non_matchings/boot/__osMalloc/__osRealloc.asm")

void __osAnalyzeArena(Arena* arena, u32* outMaxFree, u32* outFree, u32* outAlloc) {
    ArenaNode* iter;

    ArenaImpl_Lock(arena);

    *outMaxFree = 0;
    *outFree = 0;
    *outAlloc = 0;

    iter = arena->head;
    while (iter != NULL) {
        if (iter->isFree) {
            *outFree += iter->size;
            if (*outMaxFree < iter->size) {
                *outMaxFree = iter->size;
            }
        } else {
            *outAlloc += iter->size;
        }

        iter = iter->next;
    }

    ArenaImpl_Unlock(arena);
}

#pragma GLOBAL_ASM("./asm/non_matchings/boot/__osMalloc/__osCheckArena.asm")
