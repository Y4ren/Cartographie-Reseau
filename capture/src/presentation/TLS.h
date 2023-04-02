#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <arpa/inet.h>

#include "../manager.hpp"


/* TLS header */
#define TLS_SIZE 5
#define SSL_VERSION_3_0 0x0300
#define TLS_VERSION_1_0 0x0301
#define TLS_VERSION_1_1 0x0302
#define TLS_VERSION_1_2 0x0303
#define TLS_VERSION_1_3 0x0304

typedef struct __attribute__((packed)) s_TLS {
	uint8_t content_type;
	uint16_t version;
	uint16_t length;
} TLS;

void parseTLS(const uint8_t* packet);