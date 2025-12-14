#include "lib.h"

__attribute__((naked, noreturn))
void _start(void) {
    #ifdef linux
    #ifndef __x86_64__
        #error "unsupported architecture, only x86_64 is supported"
    #endif
    // System V Application Binary Interface
    // AMD64 Architecture Processor Supplement
    // https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf
    __asm__ volatile (
        "xor %rbp, %rbp\n"        /* ABI: clear frame pointer */

        "mov (%rsp), %rdi\n"      /* rdi = argc */
        "lea 8(%rsp), %rsi\n"     /* rsi = argv */

        "sub $8, %rsp\n"          /* align stack to 16 bytes */
        "call main\n"
        "add $8, %rsp\n"

        "mov %rax, %rdi\n"        /* exit code = main return */
        "mov $60, %rax\n"         /* SYS_exit */
        "syscall\n"
    );
    #else
        #error "bad os choice tbh"
    #endif
}
