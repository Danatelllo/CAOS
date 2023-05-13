#include <stdio.h>
#include <sys/syscall.h>

enum { BUF_SIZE = 4096 };

struct FileWriteState {
    int fd;
    unsigned char *buf;
    int bufsize;
    int pointer;
};

unsigned char tmp_buf[BUF_SIZE];
struct FileWriteState tmp_stout = {
    .fd = 1, .buf = tmp_buf, .bufsize = BUF_SIZE, .pointer = 0};
struct FileWriteState *stout = &tmp_stout;

void flush(struct FileWriteState *out) {
    __asm__("int $0x80" ::"a"(SYS_write), "b"(out->fd), "c"(out->buf),
            "d"(out->pointer));
    out->pointer = 0;
}

void writechar(int c, struct FileWriteState *out) {
    out->buf[out->pointer] = c;
    ++out->pointer;
    if (out->pointer == out->bufsize) {
        flush(out);
    }
}
