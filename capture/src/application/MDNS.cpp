#include "MDNS.h"

void parseMDNS(const uint8_t* packet){
    Manager::currentPacketProtocol->setName("MDNS");
    
    // MDNS* mdns = (MDNS*)packet;
    // printf("\t\t\tMDNS %x questions : %d, answers : %d\n", ntohs(mdns->id), ntohs(mdns->questions), ntohs(mdns->answer_RRs));
}