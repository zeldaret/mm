#include "os_malloc.h"
#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "macros.h"
#include "functions.h"

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

OSMesg sArenaLockMsg[1];

void __osMallocAddBlock(Arena* arena, void* start, size_t size);

void ArenaImpl_LockInit(Arena* arena) {
    osCreateMesgQueue(&arena->lock, sArenaLockMsg, ARRAY_COUNT(sArenaLockMsg));
}

void ArenaImpl_Lock(Arena* arena) {
    osSendMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

void ArenaImpl_Unlock(Arena* arena) {
    osRecvMesg(&arena->lock, NULL, OS_MESG_BLOCK);
}

ArenaNode* ArenaImpl_GetLastBlock(Arena* arena) {
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

void __osMallocInit(Arena* arena, void* start, size_t size) {
    bzero(arena, sizeof(Arena));
    ArenaImpl_LockInit(arena);
    __osMallocAddBlock(arena, start, size);
    arena->isInit = true;
}

void __osMallocAddBlock(Arena* arena, void* start, size_t size) {
    ptrdiff_t diff;
    s32 alignedSize;
    ArenaNode* firstNode;
    ArenaNode* lastNode;

    if (start != NULL) {
        firstNode = (ArenaNode*)ALIGN16((uintptr_t)start);
        diff = (uintptr_t)firstNode - (uintptr_t)start;
        alignedSize = ((s32)size - diff) & ~0xF;

        if (alignedSize > (s32)sizeof(ArenaNode)) {
            firstNode->next = NULL;
            firstNode->prev = NULL;
            firstNode->size = alignedSize - sizeof(ArenaNode);
            firstNode->isFree = true;
            firstNode->magic = NODE_MAGIC;
            ArenaImpl_Lock(arena);
            lastNode = ArenaImpl_GetLastBlock(arena);

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
    bzero(arena, sizeof(Arena));
}

u8 __osMallocIsInitalized(Arena* arena) {
    return arena->isInit;
}

void* __osMalloc(Arena* arena, size_t size) {
    ArenaNode* iter;
    ArenaNode* newNode;
    void* alloc = NULL;

    size = ALIGN16(size);

    ArenaImpl_Lock(arena);
    iter = arena->head;

    while (iter != NULL) {
        if (iter->isFree && iter->size >= size) {
            size_t blockSize = ALIGN16(size) + sizeof(ArenaNode);

            if (blockSize < iter->size) {
                ArenaNode* next;

                newNode = (ArenaNode*)((uintptr_t)iter + blockSize);
                newNode->next = iter->next;
                newNode->prev = iter;
                newNode->size = iter->size - blockSize;
                newNode->isFree = true;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size = size;

                next = newNode->next;
                if (next != NULL) {
                    next->prev = newNode;
                }
            }

            iter->isFree = false;
            alloc = (void*)((uintptr_t)iter + sizeof(ArenaNode));
            break;
        }

        iter = iter->next;
    }

    ArenaImpl_Unlock(arena);

    return alloc;
}

void* __osMallocR(Arena* arena, size_t size) {
    ArenaNode* iter;
    ArenaNode* newNode;
    size_t blockSize;
    void* alloc = NULL;

    size = ALIGN16(size);

    ArenaImpl_Lock(arena);
    iter = ArenaImpl_GetLastBlock(arena);

    while (iter != NULL) {
        if (iter->isFree && iter->size >= size) {
            blockSize = ALIGN16(size) + sizeof(ArenaNode);
            if (blockSize < iter->size) {
                ArenaNode* next;

                newNode = (ArenaNode*)((uintptr_t)iter + (iter->size - size));
                newNode->next = iter->next;
                newNode->prev = iter;
                newNode->size = size;
                newNode->magic = NODE_MAGIC;

                iter->next = newNode;
                iter->size -= blockSize;

                next = newNode->next;
                if (next != NULL) {
                    next->prev = newNode;
                }
                iter = newNode;
            }

            iter->isFree = false;
            alloc = (void*)((uintptr_t)iter + sizeof(ArenaNode));
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

    ArenaImpl_Lock(arena);

    node = (ArenaNode*)((uintptr_t)ptr - sizeof(ArenaNode));

    if ((ptr != NULL && (node->magic == NODE_MAGIC) && !node->isFree)) {
        next = node->next;
        prev = node->prev;
        node->isFree = true;

        if ((uintptr_t)next == (uintptr_t)node + sizeof(ArenaNode) + node->size && next->isFree) {
            ArenaNode* newNext = next->next;

            if (newNext != NULL) {
                newNext->prev = node;
            }

            node->size += next->size + sizeof(ArenaNode);

            node->next = newNext;
            next = newNext;
        }

        if (prev != NULL && prev->isFree && (uintptr_t)node == (uintptr_t)prev + sizeof(ArenaNode) + prev->size) {
            if (next != NULL) {
                next->prev = prev;
            }

            prev->next = next;
            prev->size += node->size + sizeof(ArenaNode);
        }
    }

    ArenaImpl_Unlock(arena);
}

void* __osRealloc(Arena* arena, void* ptr, size_t newSize) {
    ArenaImpl_Lock(arena);

    (void)"__osRealloc(%08x, %d)\n";

    if (ptr == NULL) {
        ptr = __osMalloc(arena, newSize);
    } else if (newSize == 0) {
        __osFree(arena, ptr);
        ptr = NULL;
    } else {
        size_t diff;
        void* newPtr;
        ArenaNode* node;

        node = (uintptr_t)ptr - sizeof(ArenaNode);
        newSize = ALIGN16(newSize);
        if ((newSize != node->size) && (node->size < newSize)) {
            ArenaNode* next = node->next;

            diff = newSize - node->size;
            // Checks if the next node is contiguous to the current allocated node and it has enough space to fit the
            // new requested size
            if (((uintptr_t)next == (uintptr_t)node + node->size + sizeof(ArenaNode)) && (next->isFree) &&
                (next->size >= diff)) {
                ArenaNode* next2 = next->next;

                next->size = (next->size - diff);
                if (next2 != NULL) {
                    next2->prev = (void*)((uintptr_t)next + diff);
                }

                next2 = (uintptr_t)next + diff;
                node->next = next2;
                node->size = newSize;
                __osMemcpy(next2, next, sizeof(ArenaNode));
            } else {
                newPtr = __osMalloc(arena, newSize);
                if (newPtr != NULL) {
                    bcopy(newPtr, ptr, node->size);
                    __osFree(arena, ptr);
                }
                ptr = newPtr;
            }
        }
    }

    ArenaImpl_Unlock(arena);

    return ptr;
}

void __osAnalyzeArena(Arena* arena, size_t* outMaxFree, size_t* outFree, size_t* outAlloc) {
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

u32 __osCheckArena(Arena* heap) {
    ArenaNode* iter;
    u32 err = 0;

    ArenaImpl_Lock(heap);

    // "Checking the contents of the arena..."
    (void)"アリーナの内容をチェックしています．．． (%08x)\n";

    for (iter = heap->head; iter != NULL; iter = iter->next) {
        if (iter->magic != NODE_MAGIC) {
            // "Oops!!"
            (void)"おおっと！！ (%08x %08x)\n";

            err = 1;
            break;
        }
    }

    // "The arena still looks good"
    (void)"アリーナはまだ、いけそうです\n";

    ArenaImpl_Unlock(heap);

    return err;
}
