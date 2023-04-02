#include "UDP.h"

void parseUDP(const uint8_t* packet){
    const UDP *udp = (UDP*)(packet);
    
    int port = min(ntohs(udp->source_port), ntohs(udp->destination_port)); 
    if(port >= 8192) return;
    
    Manager::setProtocol(port);
    
    switch(port){
        case PORT_NTP:
            Manager::currentPacketProtocol->setName("NTP");    
            break;
        case PORT_NBNS:
            Manager::currentPacketProtocol->setName("NBNS");    
            break;
        case PORT_NETBIOS_DATAGRAM:
            Manager::currentPacketProtocol->setName("NetBIOS");    
            break;
        case PORT_DHCP:
            Manager::currentPacketProtocol->setName("DHCP");    
            break;
        case PORT_DHCPv6_CLIENT:
        case PORT_DHCPv6_SERVER:
            Manager::currentPacketProtocol->setName("DHCPv6");    
            break;
        case PORT_QUIC:
            parseQUIC(packet + UDP_SIZE);
            break;
        case PORT_DNS:
            parseDNS(packet + UDP_SIZE);
            break;
        case PORT_SKYPE_ENTREPRISE:
            Manager::currentPacketProtocol->setName("Skype Entreprise");    
            break;
        case PORT_LLMNR:
            Manager::currentPacketProtocol->setName("LLMNR");    
            break;
        case PORT_RADIUS:
            Manager::currentPacketProtocol->setName("RADIUS");    
            break;
        case PORT_MDNS:
            parseMDNS(packet + UDP_SIZE);
            break;
        default:
            Manager::currentPacketProtocol->setName("UDP");
            break;
    }
}
