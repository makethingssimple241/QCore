#include "allocator.h"

#include <stdio.h>
#include <stdlib.h>

Allocator* Allocator_init(void) {
    Allocator* allocator = malloc(sizeof(Allocator));
    
    allocator->pool = malloc(sizeof(uintptr_t) * ALLOCATOR_INITIAL_SIZE);
    allocator->size = ALLOCATOR_INITIAL_SIZE;
    allocator->ptr = 0;

    for (size_t i = 0; i < allocator->size; i++)
        allocator->pool[i] = 0;

    return allocator;
}

void* Allocator_alloc(Allocator* allocator, size_t size) {
    while (allocator->ptr * sizeof(uintptr_t) + size >= sizeof(uintptr_t) * allocator->size) {
        size_t original_size = allocator->size;
        allocator->size *= 2;
        void** new_pool = (void**)realloc(allocator->pool, allocator->size);
        
        if (new_pool == NULL) {
            fprintf(stderr, "[ ERROR ] Allocator_alloc failed to realloc allocator->pool\n");
            return NULL;
        }

        for (size_t i = original_size; i < allocator->size; i++)
            allocator->pool[i] = 0;
    }

    void* slot = allocator->pool[allocator->ptr++];
    void* block = malloc(size);
    
    if (block == NULL) {
        fprintf(stderr, "[ ERROR ] Allocator_alloca failed to malloc(%zu)\n", size);
        return NULL;
    }

    slot = block;
    return slot;
}

void Allocator_deinit(Allocator* allocator) {
    for (size_t i = 0; i < allocator->size; i++)
        free(allocator->pool[i]);

    free(allocator->pool);
    free(allocator);
}
