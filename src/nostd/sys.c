#include "sys.h"

#ifdef linux
#ifndef __x86_64__
    #error "unsupported architecture, only x86_64 is supported"
#endif
/* Linux x86_64 syscalls */
#define SYS_write 1
#define SYS_exit  60

#else
    #error "bad os choice tbh"
#endif

long sys_write(int fd, const void *buf, unsigned long len) {
    long ret;
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture, only x86_64 is supported"
        #endif
    __asm__ volatile (
        "syscall"
        : "=a"(ret)
        : "a"(SYS_write), "D"(fd), "S"(buf), "d"(len)
        : "rcx", "r11", "memory"
    );
    #else
        #error "bad os choice tbh"
    #endif
    return ret;
}

__attribute__((noreturn))
void sys_exit(int code) {
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture, only x86_64 is supported"
        #endif
    __asm__ volatile (
        "syscall"
        :
        : "a"(SYS_exit), "D"(code)
        : "rcx", "r11", "memory"
    );
    #else
        #error "bad os choice tbh"
    #endif
    __builtin_unreachable();
}
