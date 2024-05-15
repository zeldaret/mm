#include "gamealloc.h"

#include "libc64/malloc.h"

void GameAlloc_Log(GameAlloc* this) {
    GameAllocEntry* iter = this->base.next;

    while (iter != &this->base) {
        iter = iter->next;
    }
}

void* GameAlloc_Malloc(GameAlloc* this, size_t size) {
    GameAllocEntry* ptr = malloc(size + sizeof(GameAllocEntry));

    if (ptr != NULL) {
        ptr->size = size;
        ptr->prev = this->head;
        this->head->next = ptr;
        this->head = ptr;
        ptr->next = &this->base;
        this->base.prev = this->head;
        return ptr + 1;
    } else {
        return NULL;
    }
}

void GameAlloc_Free(GameAlloc* this, void* data) {
    GameAllocEntry* ptr;

    if (data != NULL) {
        ptr = &((GameAllocEntry*)data)[-1];
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        this->head = this->base.prev;
        free(ptr);
    }
}

void GameAlloc_Cleanup(GameAlloc* this) {
    GameAllocEntry* next = this->base.next;
    GameAllocEntry* cur;

    while (&this->base != next) {
        cur = next;
        next = next->next;
        free(cur);
    }

    this->head = &this->base;
    this->base.next = &this->base;
    this->base.prev = &this->base;
}

void GameAlloc_Init(GameAlloc* this) {
    this->head = &this->base;
    this->base.next = &this->base;
    this->base.prev = &this->base;
}
