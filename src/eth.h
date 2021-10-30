#pragma once

#include <stdint.h>

/// The maximum size of an ethernet frame.
#define ETH_MTU 1518

/// Read an Ethernet frame.
///
/// Blocks until an entire frame can be read.
///
/// Buffer that's passed in must be at least `ETH_MTU` bytes large.
void eth_in(int tap_fd, uint8_t* buf);