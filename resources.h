#ifndef STD_RESOURCES_H
#define STD_RESOURCES_H

#include <stdio.h>
#include <stdbool.h>

bool with_open(const char* name, const char* mode, void(*fn)(FILE*));

#endif /* STD_RESOURCES_H */
