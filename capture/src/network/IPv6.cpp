#include "IPv6.h"

void parseIPv6(const uint8_t* packet){
    const IPv6 *ipv6 = (IPv6*)(packet);

    char formated_ip_source[INET6_ADDRSTRLEN];
    char formated_ip_destination[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(ipv6->source), formated_ip_source, INET6_ADDRSTRLEN); 
    inet_ntop(AF_INET6, &(ipv6->destination), formated_ip_destination, INET6_ADDRSTRLEN); 

    Manager::currentPacketNode->addIPv6(formated_ip_source);
    
    switch(ipv6->protocol){
        case IPV6_PROTOCOL_TCP:
            parseTCP(packet + IPV6_SIZE);
            break;
        case IPV6_PROTOCOL_UDP:
            parseUDP(packet + IPV6_SIZE);
            break;
        case IPV6_PROTOCOL_ICMPV6:
            parseICMPv6(packet + IPV6_SIZE);
            break;
        default:
            // printf("%d : Protocol over IPv6 0x%.2x not yet implemented.\n", Manager::currentPacketIndex, ipv6->protocol);
            break;
    }
}
