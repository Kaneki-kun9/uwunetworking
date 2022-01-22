#include "eth.h"

#include <linux/if_ether.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#include "arp.h"
#include "common.h"
#include "tap.h"

#define ETHERTYPE_ARP 2054
#define ETHERTYPE_IPV4 2048

void eth_in(int tap_fd, uint8_t *buf) {
    size_t idx = 0;
    // Read the header
    while (idx < sizeof(struct eth_hdr)) {
        ssize_t c = tap_read(tap_fd, buf, ETH_MTU);
        if (c < 0) {
            panicf("eth_in():Read from tun_fd: %s\n");
        } else {
            const size_t c_size = (size_t)c;
            idx += c_size;
        }
    }

    struct eth_hdr *hdr = (struct eth_hdr *)buf;

    printf("ethertype: %i\n", hdr->ethertype);
    switch (hdr->ethertype) {
        case ETHERTYPE_ARP:
            arp_incoming(hdr);
            break;

        case ETHERTYPE_IPV4:
        default:
            break;
    }

    // struct arp_hdr *arp_hdr = (struct arp_hdr *)hdr->payload;

    // TODO: Handling of Frames
    // Stop after reading all data the header told us to expect, even if it's < MTU
}