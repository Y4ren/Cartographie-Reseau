#include "SMB.h"

void parseSMB(const uint8_t* packet){
    uint32_t * tmpSMB = (uint32_t *)(packet + NETBIOS_SESSION_SERVICE_LENGTH);
    switch (ntohl(*tmpSMB))
    {
        case 0xff534d42:
            Manager::currentPacketProtocol->setName("SMB");
            break;
        case 0xfe534d42:
            Manager::currentPacketProtocol->setName("SMB2");
            break;
    }
    return;
}