#pragma once
#ifndef SYS_H
#define SYS_H

long sys_read(int fd, void *buf, unsigned long len);

long sys_write(int fd, const void *buf, unsigned long len);

long sys_close(int fd);

long sys_execve(
    const char *path,
    char *const argv[],
    char *const envp[]
);

#define O_RDONLY 0
#define O_WRONLY 1
#define O_CREAT  64

int sys_open(const char *path, int flags, int mode);

long sys_fork(void);

long sys_wait4(int pid, int *status);

__attribute__((noreturn))
void sys_exit(int code);

#endif
