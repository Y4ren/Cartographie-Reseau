#pragma once

#include <stdint.h>
#include <stdint.h>
#include <netinet/in.h>

#include "../manager.hpp"

#define NETBIOS_SESSION_SERVICE_LENGTH 4

typedef struct s_SMBHeader{
    uint32_t component;
    uint8_t command;
    uint32_t status;
    uint8_t flags;
    uint16_t flags2;
    uint16_t processIdHigh;
    uint64_t signature;
    uint16_t reserved;
    uint16_t treeId;
    uint16_t processId;
    uint16_t userId;
    uint16_t multiplexId;

} SMBHeader;

typedef struct s_SMB2Header{
    uint32_t protocolId;
    uint16_t headerLength;
    uint16_t creditCharge;
    uint16_t channelSequence;
    uint16_t reserved;
    uint16_t command;
    uint16_t creditRequested;
    uint32_t flags;
    uint32_t chainOffset;
    uint64_t messageId;
    uint32_t processId;
    uint32_t treeId;
    uint64_t sessionId;
    uint64_t signature1;
    uint64_t signature2;
} SMB2Header;

void parseSMB(const uint8_t* packet);
