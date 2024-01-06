#include "log.h"

void init_log(FILE* file) {
    Allocator* allocator = Allocator_init();
    if (allocator == NULL)
        exit(EXIT_FAILURE);

    global_call_stack = malloc(sizeof(Call_Stack));
    global_call_stack->data = allocator;

    log_file = file;
}

void deinit_log(void) {
    Allocator_deinit(global_call_stack->data);
    free(global_call_stack);
    fclose(log_file);
}

void write_log(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vfprintf(log_file, fmt, arg);
    va_end(arg);
}

void register_call(Call_Stack_Element* function) {
    global_call_stack->data->pool[global_call_stack->data->ptr++] = function;
}

void register_ret(void) {
    global_call_stack->data->ptr--;
}

void dump_call_stack(void) {
    for (size_t i = global_call_stack->data->ptr; i > 0; i--) {
        Call_Stack_Element* element = global_call_stack->data->pool[i - 1];
        write_log("  %s:%zu, in `%s`\n", element->file, element->line, element->name);
    }
}
