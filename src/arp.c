#include "arp.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"
#include "eth.h"

#define ARP_ETHERNET 0x0001
#define ARP_PROTOCOL 0x0800
#define ARP_REQUEST 1
#define ARP_REPLY 2

struct arp_ipv4 {
    uint8_t smac[6];
    uint32_t sip;
    uint8_t dmac[6];
    uint32_t dip;
} __attribute__((packed));

void arp_incoming(struct eth_hdr *hdr) {
    struct arp_hdr *arp_hdr;
    struct arp_ipv4 *arp_ipv4;
    bool merge = false;

    arp_hdr = (struct arp_hdr *)hdr->payload;

    if (arp_hdr->hwtype != ARP_ETHERNET) {
        panic("arp_incoming():Hardware not supported");
    }

    if (arp_hdr->protype != ARP_PROTOCOL) {
        panic("arp_incoming():Protocol is not supported ");
    }

    if (arp_hdr->opcode == ARP_REQUEST) {
        uint8_t tmp[6];
        memcpy(tmp, hdr->dmac, sizeof(hdr->dmac));
        memcpy(hdr->dmac, hdr->smac, sizeof(hdr->smac));
        memcpy(hdr->smac, tmp, sizeof(tmp));

    } else {
        panic("arp_incoming(): No valid Opcode");
    }
}