#ifndef HELPERS_H
#define HELPERS_H

__attribute__((noreturn)) void panic(char *error);
__attribute__((noreturn)) void unreachable(void);

struct Vector {
    signed x;
    signed y;
};

#endif /* HELPERS_H */
