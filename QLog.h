#ifndef QLOG_H
#define QLOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include "QAllocator.h"

#define QTRACEBACK_CAPACITY 1024

typedef struct {
    const char *name, *file;
    size_t line;
} QTrace;

typedef struct {
    QAllocator* data;
} QTraceback;

extern QTraceback* traceback;
extern FILE* QLogFile;

void QLog_init(FILE* file);
void QLog_deinit(void);
void QLog(const char *fmt, ...);
void QTraceback_register(QTrace* trace);
void QTraceback_unregister(void);
void QLog_traceback(void);

uintptr_t QReturnValue;

#ifdef QTRACEBACK
#define call(m_name, ...) QTrace* m_name ## _ = malloc(sizeof(QTrace)); \
                          m_name ## _->name = #m_name "()"; \
                          m_name ## _->file = __FILE__; \
                          m_name ## _->line = __LINE__; \
                          QTraceback_register(m_name ## _); \
                          QReturnValue = m_name(__VA_ARGS__); \
                          QTraceback_unregister()
#else
#define call(m_name, ...) QReturnValue = m_name(__VA_ARGS__)
#endif

#endif /* QLOG_H */
