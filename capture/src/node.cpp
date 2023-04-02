#include "node.hpp"

string getTab(int numberOfTab){
    string result = "";
    for(int i = 0; i < numberOfTab; i++)
        result += "\t";
    return result;
}

Timestamp::Timestamp(int epochtime){
    startEpochtime = epochtime;
    endEpochtime = epochtime;
    occurence = 0;
}

void Timestamp::update(int epochTime){
    endEpochtime = epochTime;
    occurence++;
}

int Timestamp::getLastEpochtime(){
    return endEpochtime;
}


string Timestamp::toJson(int tab){
    string json = getTab(tab) + "{\n";
    json += getTab(tab+1) + "\"start time\": \"" + to_string(startEpochtime) + "\",\n";
    json += getTab(tab+1) + "\"end time\": \"" + to_string(endEpochtime) + "\",\n";
    json += getTab(tab+1) + "\"occurence\": \"" + to_string(occurence) + "\"\n";
    json += getTab(tab) + "}";
    return json;
}

Destination::Destination(int epochtime, string _destination){
    destination = _destination;
    timestamps.push_back(new Timestamp(epochtime));
}

void Destination::update(int epochtime){
    Timestamp *lastTimestamp = timestamps.back();
    int lastEpochtime = lastTimestamp->getLastEpochtime();
    if(epochtime - lastEpochtime > 30){
        lastTimestamp = new Timestamp(epochtime);
        timestamps.push_back(lastTimestamp);
    }
    lastTimestamp->update(epochtime);
}

string Destination::toJson(int tab){
    string json = getTab(tab) + "{\n";
    json += getTab(tab+1) + "\"MAC\": \"" + destination + "\",\n";
    json += getTab(tab+1) + "\"timestamps\": [\n";
    for (const auto &timestamp : timestamps){
        json += timestamp->toJson(tab+2);
        if(timestamp != timestamps.back())
            json += ",";
        json += "\n";
    }
    json += getTab(tab+1) + "]\n";
    json += getTab(tab) + "}";
    return json;
}

Protocol::Protocol(int _port){
    port = _port;
}

void Protocol::setName(string _name){
    name = _name;
}

void Protocol::setVersion(string _version){
    version = _version;
}

void Protocol::addTimestamp(int epochtime, string destinationMAC){
    Destination *destination = destinations[destinationMAC];
    if(!destination){
        destination = new Destination(epochtime, destinationMAC);
        destinations[destinationMAC] = destination;
    }
    destination->update(epochtime);
}

// This function converts the Protocol object to a JSON string.
string Protocol::toJson(int tab){
    string json = getTab(tab) + "{\n";
    json += getTab(tab+1) + "\"name\": \"" + name + "\",\n";
    if(port > 0) json += getTab(tab+1) + "\"port\": \"" + to_string(port) + "\",\n";
    if(version != "")json += getTab(tab+1) + "\"version\": \"" + version + "\",\n";
    if(detail != "")json += getTab(tab+1) + "\"detail\": \"" + detail + "\",\n";
    json += getTab(tab+1) + "\"occurence\": " + to_string(occurence) + ",\n";
    
    json += getTab(tab+1) + "\"destinations\": [\n";
    for (const auto &destination : destinations){
        json += destination.second->toJson(tab+2);
        if(destination.first != destinations.rbegin()->first)
            json += ",";
        json += "\n";
    }
    json += getTab(tab+1) + "]\n";
    json += getTab(tab) + "}";
    
    return json;
}

OpenService::OpenService(string _name, int _port, string _banner, string _state, vector<string> _cpes){
    name = _name;
    port = _port;
    banner = _banner;
    state = _state;
    cpes = _cpes;
}

string OpenService::getName(){
    return name;
}

string OpenService::toJson(int tab){
    string json = getTab(tab) + "{\n";
    json += getTab(tab+1) + "\"name\": \"" + name + "\",\n";
    json += getTab(tab+1) + "\"port\": \"" + to_string(port) + "\",\n";
    if(banner != "") json += getTab(tab+1) + "\"banner\": \"" + banner + "\",\n";
    json += getTab(tab+1) + "\"state\": \"" + state + "\",\n";

    json += getTab(tab+1) + "\"cpes\": [\n";
    for(auto cpe : cpes){
        json += getTab(tab+2) +  cpe;
        if(cpe != cpes.back()){
            json + ",";
        }
        json += "\n";
    }
    json += getTab(tab+1) + "]\n";
    json += getTab(tab) + "}";
    return json;
}

// Constructor that takes in a MAC address and initializes the other member variables
Node::Node(string _MAC){
    MAC = _MAC;
    sentPacket = 0;
    sentPacketSize = 0;
    receivedPacket = 0;
    receivedPacketSize = 0;
}

// Function for adding IP addresses to the IPv4 and IPv6 maps
void Node::addIPv4(string _IPv4){
    if(_IPv4 == "0.0.0.0" || _IPv4 == "") return;
    IPv4[_IPv4] = _IPv4;
}

void Node::addIPv6(string _IPv6){
    if(_IPv6 == "::" || _IPv6 == "") return;
    IPv6[_IPv6] = _IPv6;
}

void Node::addBootInformation(string _lastBoot, int _uptime){
    lastBoot = _lastBoot;
    uptime = _uptime;
}

void Node::addDistance(int _distance){
    distance = _distance;
}

void Node::addOS(string OSString){
    bool found = false;
    for(auto tmpOSString : OS){
        if(OSString == tmpOSString){
            found = true;    
            break;
        }
    }
    if(!found)
        OS.push_back(OSString);
}

Protocol* Node::getProtocol(int port){
    Protocol* protocol = protocols[port];
    if(!protocol){
        protocol = new Protocol(port);
        protocols[port] = protocol;
    }
    protocol->occurence++;
    return protocol;
}

void Node::addService(OpenService* service){
    services[service->getName()] = service;
}

void Node::addSentData(int dataSize){
    sentPacket++;
    sentPacketSize += dataSize;
}

void Node::addReceivedData(int dataSize){
    receivedPacket++;
    receivedPacketSize += dataSize;
}   

// Function for converting the node's data into a JSON string
string Node::toJson(int tab){
    string json = getTab(tab) + "{\n";
    json += getTab(tab+1) + "\"MAC\": \"" + MAC + "\",\n";
    json += getTab(tab+1) + "\"sentPacket\": " + to_string(sentPacket) + ",\n";
    json += getTab(tab+1) + "\"sentPacketSize\": " + to_string(sentPacketSize) + ",\n";
    json += getTab(tab+1) + "\"receivedPacket\": " + to_string(receivedPacket) + ",\n";
    json += getTab(tab+1) + "\"receivedPacketSize\": " + to_string(receivedPacketSize) + ",\n";
    if(!IPv4.empty()){
        json += getTab(tab+1) + "\"IPv4\": [\n";
        for (const auto &IP : IPv4){
            json += getTab(tab+1) + "\t\"" + IP.second + "\"";
            if(IP.second != IPv4.rbegin()->second)
                json += ",";
            json += "\n";
        }
        json += getTab(tab+1) + "],\n";
    }
    if(!IPv6.empty()){
        json += getTab(tab+1) + "\"IPv6\": [\n";
        for (const auto &IP : IPv6){
            json += getTab(tab+2) + "\"" + IP.second + "\"";
            if(IP.second != IPv6.rbegin()->second)
                json += ",";
            json += "\n";
        }
        json += getTab(tab+1) + "],\n";
    }
    json += getTab(tab+1) + "\"services\": [\n";
    for (const auto &service : services){
        json += service.second->toJson(tab+2);
        if(service.first != services.rbegin()->first)
            json += ",";
        json += "\n";
    }
    json += getTab(tab+1) + "],\n";
    json += getTab(tab+1) + "\"protocols\": [\n";
    for (const auto &protocol : protocols){
        json += protocol.second->toJson(tab+2);
        if(protocol.first != protocols.rbegin()->first)
            json += ",";
        json += "\n";
    }
    json += getTab(tab+1) + "]\n";
    json += getTab(tab) + "}";
    
    return json;
}