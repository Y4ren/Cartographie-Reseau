#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdint.h>

#include "../manager.hpp"

/* DNS header */
/*c'est une merde à faire ça bon courage*/
#define MDNS_SIZE 12

typedef struct s_MDNS {
	uint16_t id;
	uint16_t flags;
	uint16_t questions;
	uint16_t answer_RRs;
	uint16_t authority_RRs;
	uint16_t additional_RRs;
} MDNS;

void parseMDNS(const uint8_t* packet);