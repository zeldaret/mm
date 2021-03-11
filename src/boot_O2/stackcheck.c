#include <ultra64.h>
#include <global.h>

StackEntry* sStackInfoListStart = NULL;
StackEntry* sStackInfoListEnd = NULL;

void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace, const char* name) {
    StackEntry* iter;
    u32* addr;

    if (!entry) {
        sStackInfoListStart = NULL;
    } else {
        entry->head = (u32)stackTop;
        entry->tail = (u32)stackBottom;
        entry->initValue = initValue;
        entry->minSpace = minSpace;
        entry->name = name;
        iter = sStackInfoListStart;
        while (iter) {
            if (iter == entry) {
                return;
            }
            iter = iter->next;
        }

        entry->prev = sStackInfoListEnd;
        entry->next = NULL;

        if (sStackInfoListEnd) {
            sStackInfoListEnd->next = entry;
        }

        sStackInfoListEnd = entry;
        if (!sStackInfoListStart) {
            sStackInfoListStart = entry;
        }

        if (entry->minSpace != -1) {
            addr = (u32*)entry->head;
            while ((u32)addr < entry->tail) {
                *addr++ = entry->initValue;
            }
        }
    }
}

void StackCheck_Cleanup(StackEntry* entry) {
    u32 inconsistency = 0; // unused variable needed to match

    if (!entry->prev) {
        if (entry == sStackInfoListStart) {
            sStackInfoListStart = entry->next;
        } else {
            inconsistency = 1;
        }
    } else {
        entry->prev->next = entry->next;
    }

    if (!entry->next) {
        if (entry == sStackInfoListEnd) {
            sStackInfoListEnd = entry->prev;
        } else {
            inconsistency = 1;
        }
    }

    if (inconsistency) {}
}

#ifdef NON_MATCHING
// Missing useless move
s32 StackCheck_GetState(StackEntry* entry) {
    u32* last;
    u32 used;
    u32 free;
    s32 ret;

    for (last = (u32*)entry->head; (u32)last < entry->tail; last++) {
        if (entry->initValue != *last) {
            break;
        }
    }

    used = entry->tail - (u32)last;
    free = (u32)last - entry->head;

    if (free == 0) {
        return 2;
    }

    if (free < entry->minSpace && entry->minSpace != -1) {
        return 1;
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/boot/stackcheck/StackCheck_GetState.asm")
#endif

u32 StackCheck_CheckAll() {
    u32 ret = 0;

    StackEntry* iter = sStackInfoListStart;
    while(iter) {
        u32 state = StackCheck_GetState(iter);
        if (state) {
            ret = 1;
        }
        iter = iter->next;
    }

    return ret;
}

u32 StackCheck_Check(StackEntry* entry) {
    if (!entry) {
        return StackCheck_CheckAll();
    } else {
        return StackCheck_GetState(entry);
    }
}
