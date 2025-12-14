#include "sys.h"

#ifdef linux
#ifndef __x86_64__
    #error "unsupported architecture, only x86_64 is supported"
#endif
/* Linux x86_64 syscalls */
#define SYS_read        0
#define SYS_write       1
#define SYS_openat      257
#define SYS_close       3
#define SYS_execve      59
#define SYS_exit        60
#define SYS_fork        57
#define SYS_wait4       61
#define SYS_nanosleep   35

#else
    #error "bad os choice tbh"
#endif

static inline long __syscall0(long n) {
    long r;
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture for __syscall0, only x86_64 is supported"
        #endif
    __asm__ volatile ("syscall"
        : "=a"(r)
        : "a"(n)
        : "rcx", "r11", "memory");
    #else
        #error "unsupported os for __syscall0, only impl in linux"
    #endif
    return r;
}

static inline long __syscall1(long n, long a1) {
    long r;
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture for __syscall1, only x86_64 is supported"
        #endif
    __asm__ volatile ("syscall"
        : "=a"(r)
        : "a"(n), "D"(a1)
        : "rcx", "r11", "memory");
    #else
        #error "unsupported os for __syscall1, only impl in linux"
    #endif
    return r;
}

static inline long __syscall2(long n, long a1, long a2) {
    long r;
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture for __syscall2, only x86_64 is supported"
        #endif
    __asm__ volatile ("syscall"
        : "=a"(r)
        : "a"(n), "D"(a1), "S"(a2)
        : "rcx", "r11", "memory");
    #else
        #error "unsupported os for __syscall2, only impl in linux"
    #endif
    return r;
}

static inline long __syscall3(long n, long a1, long a2, long a3) {
    long r;
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture for __syscall3, only x86_64 is supported"
        #endif
    __asm__ volatile ("syscall"
        : "=a"(r)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3)
        : "rcx", "r11", "memory");
    #else
        #error "unsupported os for __syscall3, only impl in linux"
    #endif
    return r;
}

static inline long __syscall4(long n, long a1, long a2, long a3, long a4) {
    long r;
    #ifdef linux
        #ifndef __x86_64__
            #error "unsupported architecture for __syscall4, only x86_64 is supported"
        #endif
    register long r10 __asm__("r10") = a4;
    __asm__ volatile (
        "syscall"
        : "=a"(r)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
        : "rcx", "r11", "memory"
    );
    #else
        #error "unsupported os for __syscall4, only impl in linux"
    #endif
    return r;
}

long sys_read(int fd, void *buf, unsigned long len) {
    return __syscall3(SYS_read, fd, (long)buf, len);
}

long sys_write(int fd, const void *buf, unsigned long len) {
    return __syscall3(SYS_write, fd, (long)buf, len);
}

long sys_close(int fd) {
    return __syscall1(SYS_close, fd);
}

long sys_execve(
    const char *path,
    char *const argv[],
    char *const envp[]
) {
    return __syscall3(
        SYS_execve,
        (long)path,
        (long)argv,
        (long)envp
    );
}

#define AT_FDCWD -100

int sys_open(const char *path, int flags, int mode) {
    return __syscall4(
        SYS_openat,
        AT_FDCWD,
        (long)path,
        flags,
        mode
    );
}

long sys_fork(void) {
    return __syscall0(SYS_fork);
}

long sys_wait4(int pid, int *status) {
    return __syscall3(SYS_wait4, pid, (long)status, 0);
}

__attribute__((noreturn))
void sys_exit(int code) {
    __syscall1(SYS_exit, code);
    __builtin_unreachable();
}
