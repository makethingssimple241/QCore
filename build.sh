CC="gcc"
CFLAGS="-I $(pwd) -L $(pwd) -Wall -Wextra -pedantic"
DYLIB_CFLAGS="-dynamiclib"

set -ex

$CC $CFLAGS $DYLIB_CFLAGS -o libstd.dylib QAllocator.c QFile.c QLog.c
