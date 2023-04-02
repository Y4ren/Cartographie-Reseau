#include "HTTP.h"

void parseHTTP(const uint8_t* packet){
    Manager::currentPacketProtocol->setName("http");
    return;
}