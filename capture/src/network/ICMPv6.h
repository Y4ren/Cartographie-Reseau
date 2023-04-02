#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "../manager.hpp"

/* ICMPv6 header */
typedef struct s_icmpv6 {
	uint8_t type;
    uint8_t code;
	uint16_t checksum;
	uint32_t message;
} ICMPv6;

void parseICMPv6(const uint8_t* packet);
