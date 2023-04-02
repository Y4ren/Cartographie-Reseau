#pragma once

#include <string>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class Timestamp{
private:
    int startEpochtime;
    int endEpochtime;
    int occurence;

public:
    Timestamp(int epochtime);

    void update(int epochtime);

    int getLastEpochtime();

    string toJson(int tab);
};

class Destination{
private:
    string destination;
    list<Timestamp*> timestamps = {};  // list of timestamps and destination for the protocol

public:
    Destination(int epochtime, string destination);

    void update(int epochtime);

    string toJson(int tab);
};

class Protocol {
private:
    int port;
    string name;
    string version;
    string detail;
    map<string, Destination*> destinations = {};

public:
    int occurence = 0;  // number of occurrences of the protocol
    
    // Constructor for the Protocol class, which takes in the name of the protocol as an argument.
    Protocol(int _port);

    void setName(string _name);

    void setVersion(string _version);

    void addTimestamp(int epochtime, string destination);

    // This function converts the Protocol object to a JSON string.
    string toJson(int tab);
};

class OpenService{  
private:
    string name;
    int port;
    string banner;
    string state;
    vector<string> cpes;
public:
    OpenService(string _name, int _port, string _banner, string _state, vector<string> _cpes);
    string getName();
    string toJson(int tab);
};

class Node{
private:
    string MAC;
    vector<string> OS;
    int sentPacket;
    int distance;
    long long sentPacketSize;
    int receivedPacket;
    long long receivedPacketSize;
    string lastBoot;
    int uptime;
    map<string, string> IPv4 = {};
    map<string, string> IPv6 = {};
    map<int, Protocol*> protocols = {};  // map of Protocol objects for the edge
    map<string, OpenService*> services = {};

public:

    // Constructor that takes in a MAC address and initializes the other member variables
    Node(string _MAC);

    // Function for adding IP addresses to the IPv4 and IPv6 maps
    void addIPv4(string _IPv4);

    void addIPv6(string _IPv6);

    void addDistance(int distance);

    void addOS(string OS);

    void addBootInformation(string _lastBoot, int _uptime);

    Protocol* getProtocol(int port);

    void addService(OpenService* service);

    void addSentData(int dataSize);

    void addReceivedData(int dataSize);

    // Function for converting the node's data into a JSON string
    string toJson(int tab);
};