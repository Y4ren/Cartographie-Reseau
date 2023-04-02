#include "IPv4.h"

void parseIPv4(const uint8_t* packet){
    const IPv4 *ipv4 = (IPv4*)(packet);
    uint32_t ip_size = IPv4_HL(ipv4)*4;

    if (ip_size < 20) {
        printf("* Invalid IP header length: %u bytes\n", ip_size);
        return;
    }
    char formated_ip_source[INET_ADDRSTRLEN];
    char formated_ip_destination[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ipv4->source), formated_ip_source, INET_ADDRSTRLEN); 
    inet_ntop(AF_INET, &(ipv4->destination), formated_ip_destination, INET_ADDRSTRLEN); 
    string selfIP = Manager::getSelfIPv4(Manager::interface);
    if(selfIP != ""){
        if(formated_ip_source == selfIP || formated_ip_destination == selfIP)
            return;
    }
    Manager::currentPacketNode->addIPv4(formated_ip_source);

    switch(ipv4->protocol){
        case IPV4_PROTOCOL_TCP:
            parseTCP(packet + ip_size);
            break;
        case IPV4_PROTOCOL_UDP:
            parseUDP(packet + ip_size);
            break;
        case IPV4_PROTOCOL_ICMP:
            Manager::setProtocol(-2);
            Manager::currentPacketProtocol->setName("ICMP");
            break;
        default:
            // printf("%d : Protocol over IPv4 0x%.2x not yet implemented.\n", Manager::currentPacketIndex, ipv4->protocol);
            break;
    }
}