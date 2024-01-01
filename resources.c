#include <stdio.h>

#include "resources.h"

bool with_open(const char* name, const char* mode, void(*fn)(FILE*)) {
    FILE* fd = fopen(name, mode);
    if (fd == 0) {
        fprintf(stderr, "[ ERROR ] with_open failed to open %s\n", name);
        return false;
    }

    fn(fd);

    if (fclose(fd) != 0) {
        fprintf(stderr, "[ ERROR ] with_open failed to close the file descriptor of %s\n", name);
        return false;
    }

    return true;
}
