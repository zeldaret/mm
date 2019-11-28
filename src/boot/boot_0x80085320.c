#include <ultra64.h>
#include <global.h>

void func_80085320(ThreadInfo* a0, UNK_PTR a1, UNK_PTR a2, UNK_TYPE a3, UNK_TYPE sp10, UNK_PTR sp14) {
    UNK_TYPE* i;
    ThreadInfo* v0;

    if (a0 == NULL) {
        ThreadInfoListHead = NULL;
        return;
    }

    a0->unk8 = a1;
    a0->unkC = a2;
    a0->unk10 = a3;
    a0->unk14 = sp10;
    a0->unk18 = sp14;

    v0 = ThreadInfoListHead;
    while (v0 != NULL) {
        if (v0 == a0) return;
        v0 = v0->next;
    }

    a0->prev = ThreadInfoListTail;
    a0->next = NULL;

    if (ThreadInfoListTail != NULL) {
        ThreadInfoListTail->next = a0;
    }

    ThreadInfoListTail = a0;

    if (ThreadInfoListHead == NULL) {
        ThreadInfoListHead = a0;
    }

    if (a0->unk14 != -1) {
        for (i = a0->unk8; i < a0->unkC; i++) {
            *i = a0->unk10;
        }
    }
}

UNK_RET func_800853F8(ThreadInfo* a0) {
    if (a0->prev == NULL) {
        if (ThreadInfoListHead == a0) {
            ThreadInfoListHead = a0->next;
        }
    } else {
        a0->prev->next = a0->next;
    }

    if (a0->next == NULL) {
        if (ThreadInfoListTail == a0) {
            ThreadInfoListTail = a0->prev;
        }
    }
}

UNK_TYPE func_80085468(ThreadInfo* a0) {
    UNK_TYPE* v1 = a0->unk8;
    UNK_TYPE* a1 = a0->unkC;
    UNK_TYPE* v0 = v1;
    u32 x; // ptr_diff

    while (v0 < a1) {
        if (*v0++ != a0->unk10) break;
        a1 = (UNK_TYPE*)((u32)v0 - (u32)v1);
    }

    x = v0 - v1;

    if (x == 0) {
        return 2;
    }

    if ((x < a0->unk14) && (a0->unk14 != -1)) {
        return 1;
    }

    return 0;
}

UNK_TYPE func_800854E0(UNK_ARGS) {
    ThreadInfo* s0 = ThreadInfoListHead;
    UNK_TYPE ret = 0;
    while (s0 != NULL) {
        if (func_80085468(s0) != 0) {
            ret = 1;
        }
        s0 = s0->next;
    }

    return ret;
}

UNK_RET func_80085538(ThreadInfo* a0) {
    if (a0 == NULL) {
        func_800854E0();
    } else {
        func_80085468(a0);
    }
}
