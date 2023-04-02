#include "manager.hpp"

void Manager::writeToFiles(){
    ofstream nodeFile;
    nodeFile.open("/var/www/html/nodes.json");
    nodeFile << nodeToJson();
    nodeFile.close();
}

string Manager::getSelfIPv4(string interface){
    if(interface == "")
        return "";

    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    /* I want IP address attached to "eth0" */
    strncpy(ifr.ifr_name, interface.c_str(), IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);
    return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
}

void Manager::setProtocol(int port){
    currentPacketProtocol = currentPacketNode->getProtocol(port);
    currentPacketProtocol->addTimestamp(currentPacketTime, currentPacketDestination);
}

int Manager::numberOfNodes(){
    return Nodes.size();
}

void Manager::setNode(string MAC){
    currentPacketNode = getNode(MAC);
}

// Adds a node to the Nodes map.
Node* Manager::getNode(string MAC){
    // Check if the node already exists.
    Node* node = Nodes[MAC];
    if(!node){
        // if(MAC == "ff:ff:ff:ff:ff:ff") MAC = "Broadcast"; does a seg fault for some reason
        // If the node doesn't exist, create a new one.
        node = new Node(MAC);
        Nodes[MAC] = node;
    }
    return node;
}

// Returns a JSON string representation of the nodes.   
string Manager::nodeToJson(){
    string json = "[\n";
    for (auto node : Nodes){
        json += node.second->toJson(1);
        if(node.first != Nodes.rbegin()->first)
                json += ",";
        json += "\n";
    }
    json += "]";
    return json;
}
