#include "QOptional.h"
#include "QException.h"

uintptr_t QUnwrap(QOptional optional) {
    if (optional.state == QOptional_None) {
        throw(ERROR, "Unexpectedly found `QOptional_None` when unwrapping optional value");
    }
    
    return optional.some_value;
}
