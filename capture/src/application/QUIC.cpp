#include "HTTP.h"

void parseQUIC(const uint8_t* packet){
    Manager::currentPacketProtocol->setName("QUIC");
    return;
}