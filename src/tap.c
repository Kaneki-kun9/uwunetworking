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
#include <unistd.h>

#include "common.h"

int tap_alloc(char *dev) {
    struct ifreq ifr;
    int fd, err;

    if ((fd = open("/dev/net/tap", O_RDWR)) < 0) {
        panic("Cannot open TAP dev");
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
        panicf("ERR: Could not ioctl tun %s", strerror(errno));
        close(fd);
    }

    strncpy(dev, ifr.ifr_name, IFNAMSIZ);
    return fd;
}

int tap_read(uint8_t *buf, size_t buf_size) { return -1; }