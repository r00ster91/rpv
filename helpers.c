#include <stdlib.h>
#include <stdio.h>

void panic(char *error) {
    fprintf(stderr, "panic: %s\n", error);
    exit(1);
}

void unreachable(void) {
    panic("unreachable");
}

// This may also be interesting:
// https://man7.org/linux/man-pages/man3/backtrace.3.html
