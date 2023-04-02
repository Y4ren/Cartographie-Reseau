#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../transport/TCP.h"
#include "../transport/UDP.h"
#include "../manager.hpp"

#define IPV4_PROTOCOL_TCP 0x06
#define IPV4_PROTOCOL_UDP 0x11
#define IPV4_PROTOCOL_ICMP 0x01

#define IP_RF 0x8000		/* reserved fragment flag */
#define IP_DF 0x4000		/* don't fragment flag */
#define IP_MF 0x2000		/* more fragments flag */
#define IP_OFFMASK 0x1fff	/* mask for fragmenting bits */

/* IP header */
typedef struct s_IPv4 {
	uint8_t version_header_length;		/* version << 4 | header length >> 2 */
	uint8_t type;		/* type of service */
	uint16_t length;		/* total length */
	uint16_t id;		/* identification */
	uint16_t offset;		/* fragment offset field */
	uint8_t time_to_live;		/* time to live */
	uint8_t protocol;		/* protocol */
	uint16_t checksum;		/* checksum */
	struct in_addr source;
	struct in_addr destination; /* source and dest address */
} IPv4;

#define IPv4_HL(ip)		(((ip)->version_header_length) & 0x0f)
#define IPv4_V(ip)		(((ip)->version_header_length) >> 4)

void parseIPv4(const uint8_t* packet);
