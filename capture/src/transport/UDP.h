#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

#include "../presentation/TLS.h"
#include "../application/DNS.h"
#include "../application/MDNS.h"
#include "../application/QUIC.h"
#include "ports.h"
#include "../manager.hpp"

#define UDP_SIZE 8
/* UDP header */
typedef struct s_UDP {
	uint16_t source_port;
	uint16_t destination_port;
	uint16_t length;
	uint16_t checksum;
} UDP;

void parseUDP(const uint8_t* packet);