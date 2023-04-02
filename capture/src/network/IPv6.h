#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <netinet/in.h>

#include "ICMPv6.h"
#include "../transport/TCP.h"
#include "../transport/UDP.h"
#include "../manager.hpp"

#define IPV6_SIZE 40

#define IPV6_PROTOCOL_TCP 0x06
#define IPV6_PROTOCOL_UDP 0x11
#define IPV6_PROTOCOL_ICMPV6 0x3A

/* IP header */
typedef struct s_ipv6 {
	uint32_t version_traffic_flow;
    uint16_t payload_length;
	uint8_t protocol;
	uint8_t time_to_live;
	struct in6_addr source;
	struct in6_addr destination;
} IPv6;

void parseIPv6(const uint8_t* packet);
