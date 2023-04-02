#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include "../manager.hpp"

/* DNS header */
/*c'est une merde à faire ça bon courage*/
#define DNS_SIZE 12
#define MAX_DOMAIN_NAME_SIZE 256  // maximum size of a domain name
#define MAX_RECORD_DATA_SIZE 256  // maximum size of record data in a DNS packet
#define DNS_TYPE_CNAME 5
#define DNS_TYPE_A 1

typedef struct s_DNS {
	uint16_t id;
	uint16_t flags;
	uint16_t questions;
	uint16_t answer_RRs;
	uint16_t authority_RRs;
	uint16_t additional_RRs;
} DNS;

#define DNS_QUERY_SIZE 4

typedef struct s_DNS_query {
	uint16_t type;
	uint16_t classDNS;
}DNS_query;

#define DNS_ANSWER_SIZE 10

typedef struct s_DNS_answer {
	uint16_t type;
	uint16_t classDNS;
	uint32_t time_to_live;
	uint16_t data_length;
}DNS_answer;

void parseDNS(const uint8_t* packet);
size_t read_domain_name(const uint8_t* packet, int* offset, char* name);