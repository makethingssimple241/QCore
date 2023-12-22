#ifndef STD_ALLOCATOR_H
#define STD_ALLOCATOR_H

#include <stdlib.h>

#define ptr(type, name) type* name = (type*)Allocator_alloc(allocator, sizeof(type))

#ifndef ALLOCATOR_INITIAL_SIZE
#define ALLOCATOR_INITIAL_SIZE 1024*1024 // 1 Mib
#endif

typedef struct {
    void** pool;
    size_t size, ptr;
} Allocator;

Allocator* Allocator_init(void);
void* Allocator_alloc(Allocator* allocator, size_t size);
void Allocator_deinit(Allocator* allocator);

#endif
