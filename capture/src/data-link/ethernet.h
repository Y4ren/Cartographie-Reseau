#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../network/IPv4.h"
#include "../network/IPv6.h"
#include "../manager.hpp"

/* Ethernet addresses are 6 bytes */
#define ETHERNET_SIZE 14
#define ETHERNET_ADDRESS_LENGTH	6

#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IPV6 0x86DD

/* Ethernet header */
typedef struct sniff_ethernet {
	uint8_t ether_dhost[ETHERNET_ADDRESS_LENGTH]; /* Destination host address */
	uint8_t ether_shost[ETHERNET_ADDRESS_LENGTH]; /* Source host address */
	uint16_t type; /* IP? ARP? RARP? etc */
} Ethernet;


void parseEthernet(const uint8_t* packet);