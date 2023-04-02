#include "TCP.h"

void parseTCP(const uint8_t* packet){
    const TCP *tcp = (TCP*)(packet); /* The TCP header */
    u_int tcp_size = ((tcp->offset_and_reserved&0xf0)>>4)*4;
    if (tcp_size < 20) {
        printf("* Invalid TCP header length: %u bytes\n", tcp_size);
        return;
    }

    if(!(tcp->flags&(TH_PUSH|TH_URG))){
        return;
    }
    
    int port = min(ntohs(tcp->source_port), ntohs(tcp->destination_port)); 
    if(port >= 8192) return;
    
    Manager::setProtocol(port);    
    switch(port){
        case PORT_SSH:
            Manager::currentPacketProtocol->setName("SSH");    
            break;
        case PORT_HTTP:
        case PORT_HTTP_ALT:
        case PORT_HTTP_ALT2:
            parseHTTP(packet + tcp_size);
            break;
        case PORT_HTTPS:
            Manager::currentPacketProtocol->setName("https");
            parseTLS(packet + tcp_size);
            break;
        case PORT_DNS:
            parseDNS(packet + tcp_size);
            break;
        case PORT_SMB:
            Manager::currentPacketProtocol->setName("SMB");
            parseSMB(packet + tcp_size);
            break;
        case PORT_RADIUS:
            Manager::currentPacketProtocol->setName("RADIUS");    
            break;
        case PORT_LLMNR:
            Manager::currentPacketProtocol->setName("LLMNR");    
            break;
        case PORT_NETBIOS_SESSION:
            Manager::currentPacketProtocol->setName("NetBIOS");    
            break;
        default:
            Manager::currentPacketProtocol->setName("TCP");
            break;
    }
}
