#ifndef QOPTIONAL_H
#define QOPTIONAL_H

#include <stdlib.h>

typedef enum {
    QOptional_None,
    QOptional_Some
} QOptionalState;

typedef struct {
    QOptionalState state;
    uintptr_t some_value;
} QOptional;

uintptr_t QUnwrap(QOptional optional);

#endif /* QOPTIONAL_H */
