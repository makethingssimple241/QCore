#include "log.h"

void register_call(call_stack_element function) {
    global_call_stack.data[global_call_stack.sp++] = function;
}

void register_ret(void) {
    global_call_stack.sp--;
}

void dump_call_stack(void) {
    for (size_t i = global_call_stack.sp; i > 0; i--) {
        call_stack_element element = global_call_stack.data[i - 1];
        printf("  %s:%zu, in `%s`\n", element.file, element.line, element.name);
    }
}
