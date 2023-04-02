#include "ethernet.h"

char* ether_ntoa(const uint8_t ether_dhost[ETHERNET_ADDRESS_LENGTH]){
    char *formated_ethernet = (char*)malloc(sizeof(char)*17);
    sprintf(formated_ethernet ,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", ether_dhost[0], ether_dhost[1], ether_dhost[2], ether_dhost[3], ether_dhost[4], ether_dhost[5]);
    return formated_ethernet;
}

void parseEthernet(const uint8_t* packet){
    const Ethernet *ethernet = (Ethernet*)packet;
    Manager::setNode(ether_ntoa(ethernet->ether_shost));
    Node* destinationNode = Manager::getNode(ether_ntoa(ethernet->ether_dhost));
    Manager::currentPacketNode->addSentData(Manager::currentPacketSize);
    Manager::currentPacketDestination = ether_ntoa(ethernet->ether_dhost);
    destinationNode->addReceivedData(Manager::currentPacketSize);
    
    switch(ntohs(ethernet->type)){
        case ETHERTYPE_IPV4:
            parseIPv4(packet + ETHERNET_SIZE);
            break;
        case ETHERTYPE_IPV6:
            parseIPv6(packet + ETHERNET_SIZE);
            break;
        case ETHERTYPE_ARP:
            Manager::setProtocol(-1);
            Manager::currentPacketProtocol->setName("ARP");
            break;
        default:
            // printf("%d : Protocol over ethernet 0x%.4x not yet implemented.\n", Manager::currentPacke    tIndex, ethernet->type);
            break;
    }

}
    