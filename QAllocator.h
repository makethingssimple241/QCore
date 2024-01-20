#ifndef QALLOCATOR_H
#define QALLOCATOR_H

#include <stdlib.h>

#ifndef QALLOCATOR_INITIAL_SIZE
#define QALLOCATOR_INITIAL_SIZE 1024*1024 // number of pointers
#endif

typedef struct {
    void** pool;
    size_t size, ptr;
} QAllocator;

QAllocator* QAllocatorCreate(void);
void* QAllocatorAllocate(QAllocator* allocator, size_t size);
void* QAllocatorReallocate(QAllocator* allocator, void* block, size_t size);
void QAllocatorDeallocate(QAllocator* allocator, void* block);
void QAllocatorDestroy(QAllocator* allocator);

#endif /* QALLOCATOR_H */
