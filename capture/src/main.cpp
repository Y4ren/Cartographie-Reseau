#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <getopt.h>
#include <thread>

#include "data-link/ethernet.h"
#include "manager.hpp"
#include "UI.hpp"

#define SNAP_LEN 1518

void help(){
    cout << "main.exe -i <capture interface> | -f <pcap file>" << endl;
}

void writeToFiles(string path){
    ofstream nodeFile;
    nodeFile.open(path);
    nodeFile << Manager::nodeToJson();
    nodeFile.close();
}

void packetHandler(uint8_t *userData, const struct pcap_pkthdr* pkthdr, const uint8_t* packet) { 
    struct tm *nowtm;
    nowtm = localtime(&pkthdr->ts.tv_sec);

    Manager::currentPacketTime = mktime(nowtm);
    Manager::currentPacketSize = pkthdr->len;
    Manager::currentPacketIndex++;
    Manager::totalSizeProcessed += pkthdr->len;

    parseEthernet(packet);
}

void capture(pcap_t *handle){    
	if (pcap_loop(handle, -1, packetHandler, NULL) < 0) {
        fprintf(stderr, "\npcap_loop() failed: %s\n", pcap_geterr(handle));
        return;
    }
    return;
}
pcap_t *openInterface(char* interface){
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
	    fprintf(stderr, "Couldn't open device %s: %s\n", interface, errbuf);
    }

    return handle;
}

pcap_t *openFile(char* filePath){
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_offline(filePath, errbuf);
    if (handle == NULL) {
	    fprintf(stderr, "\npcap_open_offline() failed: %s\n", errbuf);
    }

    return handle;
}

int main(int argc, char **argv){
    if(argc <= 2 || argc >= 4){
        help();
        return EXIT_FAILURE;
    }

    // Set up options for the getopt_long function.
    option longopts[] = {
        {"interface", optional_argument, NULL, 'i'}, 
        {"file", optional_argument, NULL, 'f'}, {0}};
    
    int opt;
    thread UIThread;
    pcap_t *handle = NULL;

    // Parse command line arguments using getopt_long.
    while ((opt = getopt_long(argc, argv, "i:f:", longopts, 0)) != -1) {
        switch (opt) {
            case 'i':
                handle = openInterface(optarg);
                Manager::interface = optarg;
                if(!handle) return EXIT_FAILURE;
                UIThread = thread(&UI::realTimeCaptureInterface, optarg, handle);
                break;
            case 'f':
                handle = openFile(optarg);
                if(!handle) return EXIT_FAILURE;
                UIThread = thread(&UI::readPcapFileInterface, optarg);
                break;
        }
    }
    
    if(!handle){
        help();
        return EXIT_FAILURE;
    }

    capture(handle);
    UI::stop();
    UIThread.join();

    writeToFiles("./nodeFile.json");
    
    return EXIT_SUCCESS;
}

