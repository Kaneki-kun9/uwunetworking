#include "eth.h"

#include <linux/if_ether.h>
#include <stdint.h>

struct eth_hdr {
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t ethertype;
    uint8_t payload[];
} __attribute__((packed));

void eth_in(int tap_fd) {}