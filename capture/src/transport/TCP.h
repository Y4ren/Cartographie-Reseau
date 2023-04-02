#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

#include "../presentation/TLS.h"
#include "../application/HTTP.h"
#include "../application/DNS.h"
#include "../session/SMB.h"
#include "ports.h"
#include "../manager.hpp"

/* TCP header */
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

typedef struct s_TCP {
	uint16_t source_port;
	uint16_t destination_port;
	uint32_t sequence_number;
	uint32_t acknowledgment_number;
	uint8_t offset_and_reserved;
	uint8_t flags;
	uint16_t window_size;
	uint16_t checksum;
	uint16_t urgent_pointer;
} TCP;

void parseTCP(const uint8_t* packet);