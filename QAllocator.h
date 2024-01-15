#ifndef QALLOCATOR_H
#define QALLOCATOR_H

#include <stdlib.h>

#ifndef QALLOCATOR_INITIAL_SIZE
#define QALLOCATOR_INITIAL_SIZE 1024*1024 // 1 Mib
#endif

typedef struct {
    void** pool;
    size_t size, ptr;
} QAllocator;

QAllocator* QAllocator_init(void);
void* QAllocator_alloc(QAllocator* allocator, size_t size);
void QAllocator_deinit(QAllocator* allocator);

#endif /* QALLOCATOR_H */
