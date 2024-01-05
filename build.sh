CC="gcc"
CFLAGS="-I $(pwd) -L $(pwd) -Wall -Wextra -pedantic"
DYLIB_CFLAGS="-dynamiclib"

set -ex

$CC $CFLAGS $DYLIB_CFLAGS -o libstd.dylib allocator.c resources.c log.c
