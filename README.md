# QCore

![build](https://github.com/makethingssimple241/QCore/actions/workflows/main.yml/badge.svg)

QCore (Quick C Core Library), is an extension of the C standard library to make writing C code easier.

## Example
```c
#include <stdlib.h>
#include "QLog.h"

int main(void) {
    QLog_init();
    // ...
    QLog_deinit();
    return EXIT_SUCCESS;
}
```

## Quick Start

> [!CAUTION]
> This library is in active development. Its API might change any time without any notice.

### Single compilation unit

1. Add `#include "QCore.c"` to the end to the main file, assuming that all `.c` and `.h` files of this library is availible in that same directory
2. Compile the main file and all auxilary files with a C compiler

### Generate a dynamic library (macOS/Clang)

```console
$ chmod +x ./build.sh
$ ./build.sh
```

After generating the `.dylib` file, you can link it with your programs.

<hr>

> [!NOTE]
> Development playlist: [https://youtube.com/playlist?list=PLuasihUCW_DeLkvCSoHB67_K4TAQj0E-Z&si=VJXQKrQqegm2MvZ1](https://youtube.com/playlist?list=PLuasihUCW_DeLkvCSoHB67_K4TAQj0E-Z&si=VJXQKrQqegm2MvZ1)
