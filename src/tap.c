#include "tap.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"

int tap_alloc(char *dev) {
    struct ifreq ifr;
    int fd, err;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
        panicf("tap_alloc(): Cannot open TAP dev: %s \n", strerror(errno));
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
        panicf("tap_alloc(): Could not ioctl tun %s \n", strerror(errno));
        close(fd);
    }

    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    return fd;
}

ssize_t tap_read(int fd, uint8_t *buf, size_t buf_size) {
    ssize_t c = read(fd, buf, buf_size);
    return c;
}