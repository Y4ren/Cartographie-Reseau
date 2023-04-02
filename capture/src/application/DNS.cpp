#include "DNS.h"

size_t read_domain_name(const uint8_t* packet, int* offset, char* name) {
    size_t name_length = 0;
    unsigned char label_length = 0;

    // read labels from the packet until we reach the null label (0)
    while ((label_length = packet[*offset]) != 0) {
        // printf("ll : 0x%.2x\n", label_length);
        *offset += 1;

        // check the high-order two bits of the label length
        if ((label_length & 0xc0) == 0xc0) {
            // this is a pointer, so we need to follow it
            // the lower 14 bits of the label length contain the offset to the
            // actual label, which we need to read
            int label_offset = ((label_length & 0x3f) << 8) | packet[*offset];
            *offset += 1;

            int pointed_length = read_domain_name(packet, &label_offset, name + name_length);

            name_length += pointed_length;

            name[name_length++] = '.';
            break;
        } else {
            memcpy(&name[name_length], &packet[*offset], label_length);
            name_length += label_length;

            *offset += label_length;

            name[name_length++] = '.';
        }
    }

    name[name_length-1] = 0;

    return name_length;
}

void parseDNS(const uint8_t* packet){
    DNS* dns = (DNS*)(packet);
    Manager::currentPacketProtocol->setName("DNS");
    
    return;

    printf("\t\t\tDNS 0x%4x questions : %d, answers : %d\n", ntohs(dns->id), ntohs(dns->questions), ntohs(dns->answer_RRs));

    int offset = 0;

    offset += DNS_SIZE;

    for (int i = 0; i < ntohs(dns->questions); i++) {
        char domain_name[MAX_DOMAIN_NAME_SIZE];
        read_domain_name(packet, &offset, domain_name);
        // DNS_query* dns_query = (DNS_query*)(packet + offset);
        offset += DNS_QUERY_SIZE+1;
        
        printf("\t\t\tQuestion  %d : \n\t\t\t\tdomain name : %s\n", i+1, domain_name);
    }

    for (int i = 0; i < ntohs(dns->answer_RRs); i++) {
        char domain_name[MAX_DOMAIN_NAME_SIZE];
        read_domain_name(packet, &offset, domain_name);

        DNS_answer* dns_answer = (DNS_answer*)(packet + offset);
        offset += DNS_ANSWER_SIZE;

        char record[MAX_RECORD_DATA_SIZE];
        switch(ntohs(dns_answer->type)){
            case DNS_TYPE_CNAME:
                read_domain_name(packet, &offset, record);
                break;
            case DNS_TYPE_A:
                inet_ntop(AF_INET, (packet + offset), record, INET_ADDRSTRLEN); 
                offset += 4;
                break;
        }

        printf("\t\t\tAnswer %d :\n\t\t\t\tdomain name : %s\n\t\t\t\trecord : %s\n", i+1, domain_name, record);
    }
}