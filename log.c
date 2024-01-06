#include "log.h"

void init(void) {
    Allocator* allocator = Allocator_init();

    // TODO: check if allocator == NULL

    global_call_stack = malloc(sizeof(call_stack));
    global_call_stack->data = allocator;
}

void register_call(call_stack_element function) {
    global_call_stack->data->pool[global_call_stack->data->ptr++] = &function;
}

void register_ret(void) {
    global_call_stack->data->ptr--;
}

void dump_call_stack(void) {
    for (size_t i = global_call_stack->data->ptr; i > 0; i--) {
        call_stack_element* element = (call_stack_element*)global_call_stack->data->pool[i - 1];
        printf("  %s:%zu, in `%s`\n", element->file, element->line, element->name);
    }
}
