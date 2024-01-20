#include "QLog.h"

QTraceback* traceback = NULL;
FILE* QLogFile = NULL;

void QLog_init(FILE* file) {
    QAllocator* allocator = QAllocatorCreate();
    if (allocator == NULL)
        exit(EXIT_FAILURE);

    traceback = malloc(sizeof(QTraceback));
    traceback->data = allocator;

    QLogFile = file;
}

void QLog_deinit(void) {
    if (traceback != NULL) {
        QAllocatorDestroy(traceback->data);
        free(traceback);
    }

    if (QLogFile != NULL)
        fclose(QLogFile);
}

void QLog(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vfprintf(QLogFile, fmt, arg);
    va_end(arg);
}

void QTraceback_register(QTrace* trace) {
    QTrace* slot = QAllocatorAllocate(traceback->data, sizeof(QTrace)); 

    if (slot != NULL)
        *slot = *trace;
}

void QTraceback_unregister(void) {
    traceback->data->ptr--;
}

void QLog_traceback(void) {
    for (size_t i = 0; i < traceback->data->ptr; i++) {
        QTrace* element = traceback->data->pool[i];
        QLog("  %s:%zu, in `%s`\n", element->file, element->line, element->name);
    }
}
