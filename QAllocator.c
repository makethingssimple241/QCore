#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "QAllocator.h"
#include "QOptional.h"
#include "QException.h"

QAllocator* QAllocatorCreate(void) {
    QAllocator* allocator = malloc(sizeof(QAllocator));

    if (allocator == NULL) {
        throw(ERROR, strerror(errno));
    }
    
    allocator->pool = malloc(sizeof(uintptr_t) * QALLOCATOR_INITIAL_SIZE);
    allocator->size = QALLOCATOR_INITIAL_SIZE;
    allocator->ptr = 0;
    memset(allocator->pool, 0, sizeof(uintptr_t) * allocator->size);

    return allocator;
}

QOptional QAllocatorIndexOf(QAllocator* allocator, void* block) {
    for (size_t i = 0; i <= allocator->ptr; i++) {
        if (allocator->pool[i] == block) {
            return (QOptional){
                .state = QOptional_Some,
                .some_value = i
            };
        }
    }

    return (QOptional){
        .state = QOptional_None
    };
}

void* QAllocatorAllocate(QAllocator* allocator, size_t size) {
    while (allocator->ptr * sizeof(uintptr_t) + size >= sizeof(uintptr_t) * allocator->size) {
        size_t original_size = allocator->size;
        allocator->size *= 2;
        void** new_pool = (void**)realloc(allocator->pool, allocator->size);
        
        if (new_pool == NULL) {
            throw(ERROR, strerror(errno));
        }

        memset(allocator->pool[original_size], 0, allocator->size / 2);
    }

    void* block = malloc(size);
    allocator->pool[allocator->ptr++] = block;
    
    if (block == NULL) {
        throw(ERROR, strerror(errno));
    }

    return block;
}

void* QAllocatorReallocate(QAllocator* allocator, void* block, size_t size) {
    size_t index = QUnwrap(QAllocatorIndexOf(allocator, block));
    void* new_element = realloc(block, size);
    if (new_element == NULL) {
        throw(ERROR, strerror(errno));
    }
    return (allocator->pool[index] = new_element);
}

void QAllocatorDeallocate(QAllocator* allocator, void* block) {
    size_t index = QUnwrap(QAllocatorIndexOf(allocator, block));
    free(block);

    if (allocator->ptr > 1) {
        memmove(allocator->pool[index], allocator->pool[index + 1], sizeof(uintptr_t) * ((allocator->ptr--) - index));
    } else {
        allocator->pool[0] = NULL;
    }
}

void QAllocatorDestroy(QAllocator* allocator) {
    for (size_t i = 0; i <= allocator->size; i++) {
        void* ip = allocator->pool[i];
        if (ip != NULL)
            free(allocator->pool[i]);
    }

    free(allocator->pool);
    free(allocator);
}
