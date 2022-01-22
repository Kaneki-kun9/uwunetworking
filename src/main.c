#include <stdio.h>
#include <sys/types.h>

#include "eth.h"
#include "tap.h"

int main(int argc, char **argv) {
    int fd = tap_alloc("uwu0");
    printf("fd: %d \n", fd);
    u_int8_t buf[90000];

    eth_in(fd, buf);
}