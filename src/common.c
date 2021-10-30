#include "common.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void panic(const char* const error) { panicf("%s\n", error); }

void panicf(const char* const fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    exit(1);
}
