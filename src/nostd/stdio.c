#include "stdio.h"
#include "sys.h"
#include "string.h"

#define BUF_SIZE 128
#define STDOUT 1

inline static void flush(char *buf, int *pos) {
    if (*pos) {
        sys_write(STDOUT, buf, *pos);
        *pos = 0;
    }
}

static void putc(char c, char *buf, int *pos) {
    if (*pos == BUF_SIZE) flush(buf, pos);
    buf[(*pos)++] = c;
}

inline static void puts(const char *s, char *buf, int *pos) {
    while (*s) putc(*s++, buf, pos);
}

inline static void put_uint(unsigned long v, int base, char *buf, int *pos) {
    if (v >= (unsigned long)base) put_uint(v / base, base, buf, pos);
    putc("0123456789abcdef"[v % base], buf, pos);
}

inline static void put_int(long v, char *buf, int *pos) {
    unsigned long u = (v < 0) ? -(unsigned long)v : (unsigned long)v;
    if (v < 0) putc('-', buf, pos);
    put_uint(u, 10, buf, pos);
}

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type)   __builtin_va_arg(ap, type)
#define va_end(ap)         __builtin_va_end(ap)

void printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    char buf[BUF_SIZE];
    int pos = 0;

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            putc(*fmt, buf, &pos);
            continue;
        }

        fmt++;
        switch (*fmt) {
            case 's':
                puts(va_arg(ap, char *), buf, &pos);
                break;
            case 'd':
                put_int(va_arg(ap, int), buf, &pos);
                break;
            case 'x':
                put_uint(va_arg(ap, unsigned int), 16, buf, &pos);
                break;
            case '%':
                putc('%', buf, &pos);
                break;
            default:
                putc('?', buf, &pos);
        }
    }

    flush(buf, &pos);
    va_end(ap);
}
