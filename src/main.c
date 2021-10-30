#include <sys/types.h>

#include "eth.h"
#include "tap.h"
int main(int argc, char **argv) {
    int fd = tap_alloc("uwu0");

    u_int8_t buf[2000];

    eth_in(fd, buf);
}