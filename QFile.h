#ifndef QFILE_H
#define QFILE_H

#include <stdio.h>
#include <stdbool.h>

bool QFile_open(const char* name, const char* mode, void(*fn)(FILE*));

#endif /* QFILE_H */
