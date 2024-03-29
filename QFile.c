#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "QFile.h"
#include "QException.h"

bool QFileOpen(const char* name, const char* mode, void(*fn)(FILE*)) {
    FILE* fd = fopen(name, mode);
    if (fd == 0) {
        throw(ERROR, strerror(errno));
        return false;
    }

    fn(fd);

    if (fclose(fd) != 0) {
        throw(ERROR, strerror(errno)); 
        return false;
    }

    return true;
}
