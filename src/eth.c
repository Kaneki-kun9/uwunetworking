#include "eth.h"

#include <linux/if_ether.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "tap.h"

struct eth_hdr {
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t ethertype;
    uint8_t payload[];
} __attribute__((packed));

void eth_in(int tap_fd, uint8_t *buf) {
    size_t idx = 0;
    // Read the header
    while (idx < sizeof(struct eth_hdr)) {
        int c = tap_read(tap_fd, buf, ETH_MTU);
        if (c < 0) {
            panicf("eth_in():Read from tun_fd: %s\n");
        } else {
            idx += c;
        }
    }

    struct eth_hdr *hdr = (struct eth_hdr *)buf;

    if (hdr->ethertype > 1536) {
        panic("eth_in(): Ethernet Frame exceeds limit");
    }

    printf("%p", buf);

    // TODO: Handling of Frames
    // Stop after reading all data the header told us to expect, even if it's < MTU
}