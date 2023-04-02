#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>

#include "node.hpp"

using namespace std;

class Manager{
private:
    // Maps for storing nodes and edges.
    inline static map<string, Node*> Nodes;
    
public:
    inline static Node* currentPacketNode;
    inline static Protocol* currentPacketProtocol;
    inline static int currentPacketTime;
    inline static int currentPacketSize;
    inline static int currentPacketIndex;
    inline static string currentPacketDestination;
    inline static long long totalSizeProcessed = 0;
    inline static string interface;

    // Writes the nodes and edges to the appropriate JSON files.
    static void writeToFiles();

    static void setProtocol(int port);

    static int numberOfNodes();

    static string getSelfIPv4(string interface);

    static void setNode(string MAC);

    // Adds a node to the Nodes map.
    static Node* getNode(string MAC);

    // Returns a JSON string representation of the nodes.   
    static string nodeToJson();

};
