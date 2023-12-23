#include "allocator.h"

#include <stdlib.h>

Allocator* Allocator_init() {
    Allocator* allocator = malloc(sizeof(Allocator));
    
    allocator->pool = malloc(ALLOCATOR_INITIAL_SIZE);
    allocator->size = ALLOCATOR_INITIAL_SIZE;
    allocator->ptr = 0;

    for (size_t i = 0; i < allocator->size; i++)
        allocator->pool[i] = 0;

    return allocator;
}

void* Allocator_alloc(Allocator* allocator, size_t size) {
    while (allocator->ptr + size >= allocator->size) {
        size_t original_size = allocator->size;
        allocator->size *= 2;
        void** new_pool = (void**)realloc(allocator->pool, allocator->size);
        
        if (new_pool == 0) return 0;

        for (size_t i = original_size; i < allocator->size; i++)
            allocator->pool[i] = 0;
    }

    void* slot = allocator->pool[allocator->ptr++];
    void* block = malloc(size);

    if (block == 0) return 0;

    slot = block;
    return slot;
}

void Allocator_deinit(Allocator* allocator) {
    for (size_t i = 0; i < allocator->size; i++)
        free(allocator->pool[i]);

    free(allocator->pool);
    free(allocator);
}
