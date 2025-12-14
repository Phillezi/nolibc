#pragma once
#ifndef SYS_H
#define SYS_H

long sys_write(int fd, const void *buf, unsigned long len);

__attribute__((noreturn))
void sys_exit(int code);

#endif
