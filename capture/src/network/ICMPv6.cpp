#include "ICMPv6.h"

void parseICMPv6(const uint8_t* packet){
    Manager::setProtocol(-3);
    Manager::currentPacketProtocol->setName("ICMPv6");
    // const ICMPv6 *icmpv6 = (ICMPv6*)(packet);
    // printf("\t\t\tICMPv6 type : %hd, code : %hd\n", icmpv6->type, icmpv6->code);
}
