#ifndef STD_LOG_H
#define STD_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "allocator.h"

/// If you would like the logger to display the call stack which contains all registered calls, define `STD_DUMP_CALL_STACK`

#define STD_CALL_STACK_CAPACITY 1024

typedef struct {
    const char *name, *file;
    size_t line;
} call_stack_element;

/*typedef struct {
    call_stack_element data[STD_CALL_STACK_CAPACITY];
    size_t sp;
} call_stack;*/

typedef struct {
    Allocator* data;
} call_stack;

//call_stack global_call_stack = { .sp = 0 };

call_stack* global_call_stack = NULL;

void init(void);
void register_call(call_stack_element function);
void register_ret(void);
void dump_call_stack(void);

uintptr_t std_ret;

#ifdef STD_DUMP_CALL_STACK
#define call(m_name, ...) call_stack_element m_name ## _; \
                          m_name ## _.name = #m_name "()"; \
                          m_name ## _.file = __FILE__; \
                          m_name ## _.line = __LINE__; \
                          register_call(m_name ## _); \
                          std_ret = m_name(__VA_ARGS__); \
                          register_ret()
#else
#define call(m_name, ...) std_ret = m_name(__VA_ARGS__)
#endif

#ifdef STD_DUMP_CALL_STACK
#define throw(m_exception, m_message) printf("\nTraceback (most recent call last):\n"); \
                                      dump_call_stack(); \
                                      printf("%s: %s\n", #m_exception, m_message); \
                                      exit(EXIT_FAILURE)
#else
#define throw(m_exception, m_message) printf("%s: %s\n", #m_exception, m_message); \
                                      exit(EXIT_FAILURE)
#endif

#endif /* STD_LOG_H */
