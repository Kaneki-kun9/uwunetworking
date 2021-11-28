#pragma once

#include <stdint.h>

/// The maximum size of an ethernet frame.
#define ETH_MTU 1518

struct eth_hdr {
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t ethertype;
    uint8_t payload[];
} __attribute__((packed));

/// Read an Ethernet frame.
///
/// Blocks until an entire frame can be read.
///
/// Buffer that's passed in must be at least `ETH_MTU` bytes large.
void eth_in(int tap_fd, uint8_t* buf);