#include "TLS.h"

void parseTLS(const uint8_t* packet){
    TLS* tls = (TLS*)packet;
    switch(ntohs(tls->version)){
        case SSL_VERSION_3_0:
            Manager::currentPacketProtocol->setVersion("SSL3.0");
            break;       
        case TLS_VERSION_1_0:       
            Manager::currentPacketProtocol->setVersion("TLS1.0");
            break;       
        case TLS_VERSION_1_1:        
            Manager::currentPacketProtocol->setVersion("TLS1.1");
            break;       
        case TLS_VERSION_1_2:        
            Manager::currentPacketProtocol->setVersion("TLS1.2");
            break;       
        case TLS_VERSION_1_3:        
            Manager::currentPacketProtocol->setVersion("TLS1.3");
            break;       
    }
}