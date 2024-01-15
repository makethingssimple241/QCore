#include "QLog.h"

void QLog_init(FILE* file) {
    QAllocator* allocator = QAllocator_init();
    if (allocator == NULL)
        exit(EXIT_FAILURE);

    traceback = malloc(sizeof(QTraceback));
    traceback->data = allocator;

    QLogFile = file;
}

void QLog_deinit(void) {
    if (traceback != NULL) {
        QAllocator_deinit(traceback->data);
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
    traceback->data->pool[traceback->data->ptr++] = trace;
    //printf("Registering %s:%zu:%s\n", trace->file, trace->line, trace->name);
    //QTrace* slot = QAllocator_alloc(traceback->data, sizeof(QTrace)); 

    //if (slot != NULL)
    //    *slot = *trace;
    
    //traceback->data->pool[traceback->data->ptr++] = trace;

    //printf("Finish registering %s:%zu:%s\n", slot->file, slot->line, slot->name);
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
