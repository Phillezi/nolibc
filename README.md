# static x86_64 linux program without any libc dependencies

A minimal freestanding binary built for Linux x86_64 with no standard library or dynamic linking.  
It includes a custom `_start` entry, direct syscalls for `write` and `exit`, and tiny utility functions like a subset of `printf` and `strlen`.

The [`main.c`](./src/main.c) compiles to a `1.6K` static ELF with both `gcc` and `make CC="zig cc"`

10x diff between a c program that links libc with `#include <stdio.h>` (with no extra compilation flags though)

```bash
-rwxr-xr-x 1 philip philip 1.6K Dec 14 01:00 ./nostdlib
-rwxr-xr-x 1 philip philip  16K Dec 14 01:00 ./wstdlib
./nostdlib:
        not a dynamic executable
./wstdlib:
        linux-vdso.so.1 (0x00007fd09c607000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007fd09c200000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007fd09c609000)
```
