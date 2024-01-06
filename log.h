#ifndef STD_LOG_H
#define STD_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include "allocator.h"

/// If you would like the logger to display the call stack which contains all registered calls, define `STD_DUMP_CALL_STACK`

#define STD_CALL_STACK_CAPACITY 1024

typedef struct {
    const char *name, *file;
    size_t line;
} Call_Stack_Element;

typedef struct {
    Allocator* data;
} Call_Stack;

Call_Stack* global_call_stack = NULL;
FILE* log_file = NULL;

void init_log(FILE* file);
void deinit_log(void);
void write_log(const char *fmt, ...);
void register_call(Call_Stack_Element* function);
void register_ret(void);
void dump_call_stack(void);

uintptr_t std_ret;

#ifdef STD_DUMP_CALL_STACK
#define call(m_name, ...) Call_Stack_Element m_name ## _; \
                          m_name ## _.name = #m_name "()"; \
                          m_name ## _.file = __FILE__; \
                          m_name ## _.line = __LINE__; \
                          register_call(&m_name ## _); \
                          std_ret = m_name(__VA_ARGS__); \
                          register_ret()
#else
#define call(m_name, ...) std_ret = m_name(__VA_ARGS__)
#endif

#ifdef STD_DUMP_CALL_STACK
#define throw(m_exception, m_message) write_log("Traceback (most recent call last):\n"); \
                                      dump_call_stack(); \
                                      write_log("%s: %s\n", #m_exception, m_message); \
                                      deinit_log(); \
                                      exit(EXIT_FAILURE)
#else
#define throw(m_exception, m_message) write_log("%s: %s\n", #m_exception, m_message); \
                                      deinit_log(); \
                                      exit(EXIT_FAILURE)
#endif

#endif /* STD_LOG_H */
