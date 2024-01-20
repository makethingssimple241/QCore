#include "QAllocator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QAllocator* QAllocatorCreate(void) {
    QAllocator* allocator = malloc(sizeof(QAllocator));

    if (allocator == NULL) {
        fprintf(stderr, "[ ERROR ] Allocator_alloc failed to malloc allocator\n");
        return NULL;
    }
    
    allocator->pool = malloc(sizeof(uintptr_t) * QALLOCATOR_INITIAL_SIZE);
    allocator->size = QALLOCATOR_INITIAL_SIZE;
    allocator->ptr = 0;
    memset(allocator->pool, 0, sizeof(uintptr_t) * allocator->size);

    return allocator;
}

void* QAllocatorAllocate(QAllocator* allocator, size_t size) {
    while (allocator->ptr * sizeof(uintptr_t) + size >= sizeof(uintptr_t) * allocator->size) {
        size_t original_size = allocator->size;
        allocator->size *= 2;
        void** new_pool = (void**)realloc(allocator->pool, allocator->size);
        
        if (new_pool == NULL) {
            fprintf(stderr, "[ ERROR ] QAllocator_alloc failed to realloc allocator->pool\n");
            return NULL;
        }

        memset(allocator->pool[original_size], 0, allocator->size / 2);
    }

    void* block = malloc(size);
    allocator->pool[allocator->ptr++] = block;
    
    if (block == NULL) {
        fprintf(stderr, "[ ERROR ] Allocator_alloca failed to malloc(%zu)\n", size);
        return NULL;
    }

    return block;
}

void QAllocatorDestroy(QAllocator* allocator) {
    for (size_t i = 0; i < allocator->size; i++) {
        void* ip = allocator->pool[i];
        if (ip != NULL)
            free(allocator->pool[i]);
    }

    free(allocator->pool);
    free(allocator);
}
