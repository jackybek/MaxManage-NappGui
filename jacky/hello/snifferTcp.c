#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <pcap/pcap.h>
#include <modbus/modbus.h>
#include <modbus/modbus-tcp.h>

#ifndef ETHERTYPE_POWERLINK
 #define ETHERTYPE_POWERLINK 0x88AB
#endif
#ifdef ETHERTYPE_POWERLINK
 #undef ETHERTYPE_POWERLINK
 #define ETHERTYPE_POWERLINK 0x88AB
#endif

#define HEX_2_DEC(c) \
	((c) >= '0' && (c) <= '9' ? (c) - '0' : \
	 (c) >= 'A' && (c) <= 'F' ? (c) - 'A' + 10 : \
	 (c) >= 'a' && (c) <= 'f' ? (c) - 'a' + 10 : 0)


int snifferTcp(char* protocol);
char* print_ip_mask(bpf_u_int32 ip);
void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
bool check_mqtt_header(const unsigned char *buffer);
bool check_ethernetIP_header(const unsigned char *buffer);
bool check_opcua_header(const unsigned char *buffer);
bool check_mbap_header(const unsigned char *buffer, struct pcap_pkthdr *header);


struct mbap_header {
	uint16_t transaction_id;
	uint16_t protocol_id;
	uint16_t length;
	uint8_t unit_id;
} mbap_header;

const char *mqtt_types[] = {
	"Reserved", "CONNECT", "CONNACK", "PUBLISH", "PUBACK",
	"PUBREC", "PUBREL", "PUBCOMP", "SUBSCRIBE", "SUBACK",
	"UNSUBSCRIBE", "UNSUBACK", "PINGREQ", "PINGRESP", "DISCONNECT", "Reserved"
};

pcap_if_t *allDevs, *device;

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    struct ether_header *eth_header = (struct ether_header *)packet;
    struct ip *ip_header;
    int ip_header_len;
    struct tcphdr *tcp_header;

    printf("Entering packet_handler() \n");

    // 1. Check if it's an IP packet
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
   	printf("received a ETHERTYPE_IP packet ...\n");
        ip_header = (struct ip *)(packet + sizeof(struct ether_header));

        // 2. Check if it's a TCP packet
        if (ip_header->ip_p == IPPROTO_TCP) {
            // IP header length is in 32-bit words, so multiply by 4
            ip_header_len = ip_header->ip_hl * 4;
            tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + ip_header_len);

            // 3. Extract info (ntohs converts network byte order to host order)
            printf("Source IP: %s | Port: %d\n", inet_ntoa(ip_header->ip_src), ntohs(tcp_header->source));
            printf("Dest IP:   %s | Port: %d\n", inet_ntoa(ip_header->ip_dst), ntohs(tcp_header->dest));
            printf("---------------------------\n");
        }
    }
    else
	printf("Not a ETHERTYPE_IP packet \n");
}

bool check_ethernetIP_header(const unsigned char *buffer)
{

	return true;
}

bool check_mqtt_header(const unsigned char *buffer)
{

	return true;
}

bool check_opcua_header(const unsigned char *buffer)
{
	return true;
}

bool check_mbap_header(const unsigned char *buffer, struct pcap_pkthdr *header)
{

	//unsigned int n ;
	//n = header->len;
	if ( (buffer[69] == 0) && (buffer[70] == 0) )	// protocol_id = 0000
	{
		if (buffer[71]*16 + buffer[72] > 0)	// length
			return true;
		else
			return false;
	}
	else
		return false;

#ifdef ERRPR
	// Extract fields using Big Endian conversion
	header->transaction_id 	= (buffer[0] << 8) | buffer[1];
	header->protocol_id 	= (buffer[2] << 8) | buffer[3];
	header->length 		= (buffer[4] << 8) | buffer[5];
	header->unit_id 	= buffer[6];

	if (header->protocol_id != 0x0000) {
		printf("invalid header->protocol_id : %0x04 \n", header->protocol_id);
		return false;
	}

	if (header->length < 2)
	{
		printf("invalid header->length : %d \n", header->length);
		return false;
	}
	return true;
#endif
#ifdef ERROR
	struct mbap_header *header = (struct mbap_header *)buffer;
	uint16_t tid = ntohs(header->transaction_id);
	uint16_t pid = ntohs(header->protocol_id);
	uint16_t remaining_len = ntohs(header->length);
	uint8_t uid = header->unit_id;

	uint8_t func_code = buffer[sizeof(struct mbap_header)];
	printf("Received -> TID: %u, PID: %u, UID: %u, FUNC: 0x%02X\n", tid, pid, uid, func_code);
	if (pid != 0x0000) {
                printf("invalid header->protocol_id : %d or %#x \n", ntohs(header->protocol_id), ntohs(header->protocol_id));
                return false;
              if ((remaining_len < 2) || (remaining_len > 253) ) {
                printf("invalid header->length : %d \n", ntohs(header->length));
                return false;
              }
        }
#endif


}


char* print_ip_mask(bpf_u_int32 ip) {
    struct in_addr addr;
    addr.s_addr = ip; // bpf_u_int32 is already in network byte order usually
    return inet_ntoa(addr);
    //printf("%s\n", inet_ntoa(addr));
}

int snifferTcp(char* protocol)
{
	pcap_t *handle;			/* Session handle */
	const char *interface = "enp0s8";	/* The interface to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
	struct bpf_program fp;		/* The compiled filter */
	bpf_u_int32 mask;		/* Our netmask */
	bpf_u_int32 net;		/* Our IP */
	struct pcap_pkthdr header;	/* The header that pcap gives us */
	const u_char *packet_data;		/* The actual packet */
	int choice;
	FILE *fptr;
        struct ether_header *eth_header;


	/* Define the device */
	int results = pcap_findalldevs(&allDevs, errbuf);
	if (results == -1) {
		fprintf(stderr, "Couldn't find default interface: %d %s\n", results, errbuf);
		return(2);
	}


	if (strncmp(protocol, "ModbusTCP", 9) == 0) choice = 1;
	if (strncmp(protocol, "EtherNetIP", 10) == 0) choice = 2;
	if (strncmp(protocol, "ProfiNet", 8) == 0) choice = 3;
	if (strncmp(protocol, "EtherCAT", 8) == 0) choice = 4;
	if (strncmp(protocol, "PowerLink", 9) == 0) choice = 5;
	if (strncmp(protocol, "OPCUA", 5) == 0) choice = 6;
	if (strncmp(protocol, "MQTT", 4) == 0) choice = 7;
	if (strncmp(protocol, "TcpHL7", 6) == 0) choice = 8;

	fptr = fopen("snifferTcp.log", "w+");
	if (!fptr) {
		printf("Error creating log file <snifferTcp.log> \n");
		return (2);
	}

  for (device = allDevs; device != NULL; device = device->next) {
        //printf("interface: %s - %s\n", device->name, device->description ? device->description : "No description");

        device = allDevs;
        printf("------------------------------------\n");
        printf("Processing interface : %s %s\n", device->name, device->description);
        printf("------------------------------------\n");
	/* Find the properties for the interface */
	if (pcap_lookupnet(interface, &net, &mask, errbuf) == -1) {
		fprintf(stderr, "Couldn't get netmask for interface %s: %s\n", interface, errbuf);
		net = 0;
		mask = 0;
	}
	else {
		// prints the subnet and the mask : 192.168.1.0 and 255.255.255.0
		printf("subnet = %s \n", print_ip_mask(net));
		printf("mask   = %s \n", print_ip_mask(mask));
	}

	/* Open the session in promiscuous mode */
	handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open interface in promiscuous mode %s: %s\n", interface, errbuf);
		return(2);
	}
	else
		printf("Successfully open interface <%s> in promiscuous mode \n", interface);

	// pcap_loop(handle, 0, packet_handler, NULL);

	/* Grab a packet */;
	packet_data = pcap_next(handle, &header);
	printf("header.len = %d \n", header.len);

    eth_header = (struct ether_header *)packet_data;
    printf("Begin checking the packet header \n");
    printf("eth_header->ether_type = 0x%04x \n", ntohs(eth_header->ether_type));
    printf("--------------------------------------- \n");

    // 1. Check if it's an IP packet
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) { // 0x0800
	// --------can be Modbus/tcp or Ethernet/IP or MQTT or OPCUA

        struct ip *ip_header = (struct ip *)(packet_data + sizeof(struct ether_header));
	bool validHeader;

        // 2. Check if it's a TCP packet
	// ip_header->ip_p : 6 = TCP, 17 = UDP
	printf("checking if it is a TCP packet or UDP ... : %d \n", ip_header->ip_p);
        if ( (ip_header->ip_p == IPPROTO_TCP) ) {                //|| (ip_header->ip_p == IPPROTO_UDP) ) {
            // IP header length is in 32-bit words, so multiply by 4
            int ip_header_len = ip_header->ip_hl * 4;
            struct tcphdr *tcp_header = (struct tcphdr *)(packet_data + sizeof(struct ether_header) + ip_header_len);

	    #ifdef DEBUG
            // 3. Extract info (ntohs converts network byte order to host order)
            printf("Source IP: %s | Port: %d\n", inet_ntoa(ip_header->ip_src), ntohs(tcp_header->source));
            printf("Dest IP:   %s | Port: %d\n", inet_ntoa(ip_header->ip_dst), ntohs(tcp_header->dest));
            printf("---------------------------\n");
	    #endif

	    #ifdef NOTE
	    4.1 next check for MBAP header
            #endif

	    if (choice == 1) {
		#ifdef COMPILE_ERROR
	    		/* Compile and apply the filter */
	    		char filter_expModbus[] = "port 502";	/* The filter expression */
	    		if (pcap_compile(handle, &fp, filter_expModbus, 0, net) == -1) {
				fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_expModbus, pcap_geterr(handle));
				return(2);
	    		}
	    		else
				printf("Successfully parse filter <%s> <%s> \n", interface, filter_expModbus);

	    		if (pcap_setfilter(handle, &fp) == -1) {
				fprintf(stderr, "Couldn't install filter %s %s: %s\n", interface, filter_expModbus, pcap_geterr(handle));
				return(2);
	    		}
	    		else
				printf("Successfully install filter <%s> <%s> \n", interface, filter_expModbus);

	    		//struct iphdr *ip_header = (struct iphdr *)packet_data;
	    		//struct tcphdr *tcp_header = (struct tcphdr *)(packet_data + (ip_header->ihl * 4));

	    		validHeader = check_mbap_header(packet_data, &header);

	    		if (!validHeader)
				printf("Not a MBAP header \n");
	    		else {
	    			// 4.1.1 extract the info from MBAP
				//print the entire payload and extract the last 12 bytes ([67] to [77])
				printf("Modbus Master IP : %s | Port : %d \n", inet_ntoa(ip_header->ip_src), ntohs(tcp_header->source));
  	     			printf("Modbus Slave IP  : %s | Port : %d \n", inet_ntoa(ip_header->ip_dst), ntohs(tcp_header->dest));
				for (unsigned int i=0; i <  header.len; i++)
            			{
		        		if (tcp_header->dest == 502) {
		  				printf("This is a MBAP request \n");
	                			for (unsigned int i=0; i <  header.len; i++)
                				{
                        				if (i == 67) printf("transaction id   : %02X %02X [%d] \n", packet_data[i], packet_data[i+1], packet_data[i]*16+packet_data[i+1]);
                        				if (i == 69) printf("protocol id      : %02X %02X      \n", packet_data[i], packet_data[i+1]);
                        				if (i == 71) printf("length           : %02X %02X [%d] \n", packet_data[i], packet_data[i+1], packet_data[i]*16+packet_data[i+1]);
                        				if (i == 72) printf("slave id         : %02X      [%d] \n", packet_data[i], packet_data[i]);
                        				if (i == 73) printf("function code    : %02X      [%d] \n", packet_data[i], packet_data[i]);
                        				if (i == 74) printf("start address    : %02X %02X [%d] \n", packet_data[i], packet_data[i+1]+1, packet_data[i]*16+packet_data[i+1]+1);
                        				if (i == 76) printf("quantity         : %02X %02X [%d] \n", packet_data[i], packet_data[i+1], packet_data[i]*16+packet_data[i+1]);
                				}
					}
					else if (tcp_header->source == 502) {
						printf("This is a MBAP response \n");
						if (i == 67) printf("transaction id   : %02X %02X [%d] \n", packet_data[i], packet_data[i+1], packet_data[i]*16+packet_data[i+1]);

						const modbus_device_id_pdu *pdu = (const modbus_device_id_pdu *) (packet_data + sizeof(mbap_header));
						if (pdu->function_code != 0x2B || pdu->mei_type != 0x0E) {
							printf("[-] Active Frame Notification: Not a Read Device Identification frame (FC=%02X, MEI=%02X) \n",
							pdu->function_code, pdu->mei_type);
						}
						else {
							const uint8_t *object_ptr = pdu->payload;
							const uint8_t *buffer_end = packet_data + buffer_len;
							uint8_t obj_id;
							uint8_t obj_len;

							printf("[+] parsing Modbus DevID Response  [Transaction ID: %d\n", ntohs(tcp_header->sequence) );
							printf("    Objects Found: %d \n", pdu->num_objects);
							printf("------------------------------------------");

							for (int i=0; i < pdu->num_objects; i++) {
								if (object_ptr +2 > buffer_end) break;

								obj_id = object_ptr[0];
								obj_len = object_ptr[1];

								object_ptr += 2;
								if (object_ptr + obj_len > buffer_end) break;

								switch(obj_id) {
									case 0x00: printf("   [Make/Vendor]	: %.*s\n", obj_len, (const char*)object_ptr); break;
									case 0x01: printf("   [Device Model]	: %.*s\n", obj_len, (const char*)object_ptr); break;
									case 0x02: printf("   [Firmware Rev]	: %.*s\n", obj_len, (const char*)object_ptr); break;
									default: break;
								}
								object_ptr += obj_len;
							}
						}
					} // tcp_header->source == 502)
					goto NEXT;
				} // for (int i=0; i <  header.len; i++)
			} // if (!validHeader)
		#endif
	    } // if (choice == 1)
	    else if (choice == 2) {
	    	#ifdef NOTE
	    	// 4.2 check for Ethernet/ip header
            	#endif

	    	/* Compile and apply the filter */
	    	bool validHeader;
	    	char filter_expEtherIP[] = "port 44818";	// The filter expression
	    	if (pcap_compile(handle, &fp, filter_expEtherIP, 0, net) == -1) {
			fprintf(stderr, "Could not parse filter %s: %s\n", filter_expEtherIP, pcap_geterr(handle));
			return(2);
	    	}
	    	else
			printf("Successfully parse filter <%s> <%s>\n", interface, filter_expEtherIP);

	    	if (pcap_setfilter(handle, &fp) == -1) {
			fprintf(stderr, "Could not install filter %s %s: %s\n", interface, filter_expEtherIP, pcap_geterr(handle));
			return(2);
	    	}
	    	else
			printf("Successfully install filter <%s> <%s> \n", interface, filter_expEtherIP);

		validHeader = check_ethernetIP_header(packet_data);

	    	if (!validHeader)
			printf("Not a EtherNet/IP header \n");
	    	else
	    	{
			// 4.2.1 extract the info from EtherNet/IP

			goto NEXT;
	    	}
	    } // if (choice == 2)
	    else if (choice == 7) {
	    	#ifdef NOTE
	    	// 4.3 check for MQTT
	    	#endif
	    	struct ip *ip;
	    	int ip_hl; // IP header length
	    	struct tcphdr *tcp;
		int tcp_hl;
		bool validHeader;
		int multiplier, rem_len, len_bytes;
		u_char *ptr;
		int topic_len, qos, header_size;
		int payload_len, type;
	    	struct ether_header *eth;

		eth = (struct ether_header *)packet_data;

	    	if (ntohs(eth->ether_type) != ETHERTYPE_IP)
			goto NEXT;

	    	ip = (struct ip *)(packet_data + sizeof(struct ether_header));
	    	ip_hl = ip->ip_hl * 4; // IP header length

	    	tcp = (struct tcphdr *)((u_char *)ip + ip_hl);
	    	tcp_hl = tcp->doff * 4; // TCP header length

	    	validHeader = check_mqtt_header(packet_data);

	    	if (!validHeader)
			printf("Not a Mqtt header \n");
	    	else
	    	{
			// 4.3.1 extract the info from mqtt

			u_char *mqtt_payload = (u_char *)tcp + tcp_hl;
			payload_len = ntohs(ip->ip_len) - (ip_hl + tcp_hl);

			if (payload_len > 0)
			{
				u_char fixed_header = mqtt_payload[0];
				type = (fixed_header >> 4) & 0x0F;

				printf("--MQTT Packet Detected ---\n");
        	    		printf("Source IP    : %s | Port: %d\n", inet_ntoa(ip_header->ip_src), ntohs(tcp_header->source));
            			printf("Dest IP      : %s | Port: %d\n", inet_ntoa(ip_header->ip_dst), ntohs(tcp_header->dest));
				printf("Packet Type  : %s (%d)\n", mqtt_types[type], type);
				printf("Payload size : %d bytes \n", payload_len);

				// extract the topic name
				if (type == 3 && payload_len > 4)
				{
					topic_len = (mqtt_payload[2] << 0) | mqtt_payload[3];
					printf("Topic name: %.*s \n", topic_len, &mqtt_payload[4]);
				}

				// extract the payload
				multiplier = 1; rem_len = 0; len_bytes = 0;
				ptr = &mqtt_payload[1];
				do {
					rem_len += (*ptr & 127) * multiplier;
					multiplier *= 128;
					len_bytes++;
				} while ((*ptr++ & 128) !=0 && len_bytes < 4);

				ptr = &mqtt_payload[1 + len_bytes];
				topic_len = (ptr[0] << 8) | ptr[1];
				ptr += 2 + topic_len;

				qos = (mqtt_payload[0] >> 1) & 0x03;
				if (qos > 0) ptr +=2;

				header_size = (int)(ptr - mqtt_payload);
				payload_len = rem_len - (header_size - (1+len_bytes));
				if (payload_len > 0)
					printf("Payload (%d bytes) : %.*s \n", payload_len, payload_len, ptr);

				printf("\n");

				goto NEXT;
			}
	    	} // if (!validHeader)
	    } // if (choice == 7)
	    else if (choice == 6)
	    {
	    	#ifdef NOTE
	    	// 4.4 check for OPCUA
	    	#endif


		//int payload1, payload2, payload3, payload4, payload5, payload6, payload7, payload8;
		char messageType[4];
		const char *payload;
		unsigned int payload_len;
		unsigned long n7,n6,n5,n4,n3,n2,n1,n0;
	    	//struct ip *ip_header = (struct ip *)(packet_data + sizeof(struct ether_header));
	    	struct ip *ip_header = (struct ip *)(packet_data + 14);
	    	int ip_header_len = ip_header->ip_hl * 4; // IP header length

	    	struct tcphdr *tcp_header = (struct tcphdr *)(packet_data + 14 + ip_header_len);
	    	int tcp_header_len = tcp_header->doff * 4; // tcp header length

	    	bool validHeader = check_opcua_header(packet_data);
	    	if (!validHeader)
			printf("Not a OPCUA header \n");
	    	else {
			printf("in 4.4.1 section \n");
			// 4.4.1 extract the info from opcua
			payload = (const char *)(packet_data + 14 + ip_header_len + tcp_header_len);
			//const u_char *payload = packet_data + sizeof(struct ether_header) + ip_header_len + tcp_header_len;
			payload_len = (unsigned int)header.caplen - (unsigned int)(14 + ip_header_len + tcp_header_len);
			//unsigned long message_size = 0L;
			//unsigned long n15, n14, n13, n12, n11, n10, n9, n8;

			if (payload_len >= 3) {
				//unsigned long decimalValue=0L;
				#ifdef NOTE
				Header : Message Type (3 bytes), Chunk Type (1 byte), Message size (4 bytes), Body
				MSG = 0x4d 0x53 0x47
				#endif

				printf("payload = 0x%.2x 0x%.2x 0x%.2x, payload_len = %d \n", payload[0], payload[1], payload[2], payload_len);
				if ( (memcmp(payload, "HEL", (unsigned long) 3) == 0) || (memcmp(payload, "ACK", (unsigned long) 3) == 0) ||
				     (memcmp(payload, "MSG", (unsigned long) 3) == 0) || (memcmp(payload, "OPN", (unsigned long) 3) == 0) ||
				     (memcmp(payload, "CLO", (unsigned long) 3) == 0) || (memcmp(payload, "ERR", (unsigned long) 3) == 0) ||
				     (memcmp(payload, "RHE", (unsigned long) 3) == 0) ) {
					printf("--OPCUA Packet detected---\n");
					printf("Source IP	: %s | Port: %d \n", inet_ntoa(ip_header->ip_src), ntohs(tcp_header->source));
					printf("Dest IP		: %s | Port: %d \n", inet_ntoa(ip_header->ip_dst), ntohs(tcp_header->dest));
					printf("Length	   	: %d bytes \n", payload_len);
					fprintf(fptr, "--OPCUA Packet detected---\n");
					fprintf(fptr, "Source IP	: %s | Port: %d \n", inet_ntoa(ip_header->ip_src), ntohs(tcp_header->source));
					fprintf(fptr, "Dest IP		: %s | Port: %d \n", inet_ntoa(ip_header->ip_dst), ntohs(tcp_header->dest));
					fprintf(fptr, "Length	   	: %d bytes \n", payload_len);

					printf("Message Header \n");
					printf("-------------- \n");
					printf("Message Type 		: %.3s \n", payload);	// message type occupies payload[0-2]
					fprintf(fptr, "Message Header \n");
					fprintf(fptr, "-------------- \n");
					fprintf(fptr, "Message Type 		: %.3s \n", payload);	// message type occupies payload[0-2]

					strncpy(messageType, payload,3);	// save it for later use
					messageType[3] ='\0';
				}
					if (strncmp(messageType, "MSG", 3) == 0) {
						// --------compute Message_size
						unsigned long message_size=0L;
						unsigned long secureChannelId = 0L;
						unsigned long securityTokenId=0L;
						unsigned long requestId=0L;
						unsigned long sequenceNumber=0L;
						long long encodingMask=0L;
						unsigned long namespaceIndex=0L;
						unsigned long nodeId=0L;
						unsigned long ServiceDiagEncodingMask = 0L;
						unsigned long long timeStamp=0LL,t0=0LL, t1=0LL, t2=0LL, t3=0LL, t4=0LL, t5=0LL, t6=0LL;
						unsigned long long t7=0LL, t8=0LL, t9=0LL, t10=0LL, t11=0LL, t12=0LL, t13=0LL, t14=0LL, t15=0LL;
						unsigned long requestHandle = 0L;
						unsigned long serviceResults = 0L;
						char mystring[100];
			                        time_t raw_time = (time_t)timeStamp;
                        			struct tm *info;
			                        char time_str[26];


						printf("Caught a MSG header : %s \n", messageType);
						printf("Reserved (Chunk Type)	: %c \n", payload[3]);
						fprintf(fptr, "Caught a MSG header : %s \n", messageType);
						fprintf(fptr, "Reserved (Chunk Type)	: %c \n", payload[3]);

						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[4], payload[5], payload[6], payload[7]);
						printf("\tMessage size on the wire(hex) = %s \n", mystring);	// 55 00 00 00
						fprintf(fptr, "\tMessage size on the wire(hex) = %s \n", mystring);	// 55 00 00 00

						sprintf(mystring, "%.2x%.2x%.2x%.2x",
							payload[7], payload[6], payload[5], payload[4]);
						printf("\tmessage_size reorder (hex) = %s \n", mystring);		// 00 00 00 55
						printf("\tmessage component %c%c %c%c %c%c %c%c \n",
							mystring[0], mystring[1], mystring[2], mystring[3],
							mystring[4], mystring[5], mystring[6], mystring[7]);

						fprintf(fptr, "\tmessage_size reorder (hex) = %s \n", mystring);		// 00 00 00 55
						fprintf(fptr, "\tmessage component %c%c %c%c %c%c %c%c \n",
							mystring[0], mystring[1], mystring[2], mystring[3],
							mystring[4], mystring[5], mystring[6], mystring[7]);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC((char)mystring[0]) ); //printf("n7 = %lu \n", n7);
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC((char)mystring[1]) ); //printf("n6 = %lu \n", n6);
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC((char)mystring[2]) ); //printf("n5 = %lu \n", n5);
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC((char)mystring[3]) ); //printf("n4 = %lu \n", n4);
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC((char)mystring[4]) ); //printf("n3 = %lu \n", n3);
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC((char)mystring[5]) ); //printf("n2 = %lu \n", n2);
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC((char)mystring[6]) ); //printf("n1 = %lu \n", n1);
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC((char)mystring[7]) ); //printf("n0 = %lu \n", n0);
						message_size = n7+n6+n5+n4+n3+n2+n1+n0;

						//message_size = (mystring[0] << 24) | (mystring[1] << 16) | (mystring[2] << 8) | mystring[3];
						//decimalValue = strtol(mystring, NULL, 16);
						printf("Total Message size 		: %lu \n", message_size);
						printf("--------------------------------------\n");
						fprintf(fptr, "Total Message size 		: %lu \n", message_size);
						fprintf(fptr, "--------------------------------------\n");
						// -- finish compute Message_size

						// --------compute SecureChannelId
						//payload1=0; payload2=0; payload3=0; payload4=0;
						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[8], payload[9], payload[10], payload[11]);
						printf("\tSecureChannel Id on the wire(hex) = %s \n", mystring);
						fprintf(fptr ,"\tSecureChannel Id on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x",
							payload[11], payload[10], payload[9], payload[8]);
						printf("\tSecureChannel Id reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\tSecureChannel Id reorder (hex) = %s \n", mystring);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[0]) );
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[1]) );
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[2]) );
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[3]) );
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[4]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[5]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[6]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[7]) );
						secureChannelId = n7+n6+n5+n4+n3+n2+n1+n0;
						printf("SecureChannel Id	: %ld \n", secureChannelId);
						printf("------------------------------\n");
						fprintf(fptr, "SecureChannel Id	: %ld \n", secureChannelId);
						fprintf(fptr, "------------------------------\n");
						// -- finish compute SecureChannelId

						// -------compute security token Id
						//payload1=0; payload2=0; payload3=0; payload4=0;
						// order of byte : payload[15] payload[14] payload[13] payload[12]
						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[12], payload[13], payload[14], payload[15]);
						printf("\tsecurityTokenId on the wire(hex) = %s \n", mystring);
							fprintf(fptr, "\tsecurityTokenId on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x",
							payload[15], payload[14], payload[13], payload[12]);
						printf("\tsecurityToken reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\tsecurityToken reorder (hex) = %s \n", mystring);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[0]) );
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[1]) );
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[2]) );
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[3]) );
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[4]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[5]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[6]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[7]) );
						securityTokenId = n7+n6+n5+n4+n3+n2+n1+n0;
						printf("Security Token Id	: %ld \n", securityTokenId);
						printf("------------------------------\n");
						fprintf(fptr, "Security Token Id	: %ld \n", securityTokenId);
						fprintf(fptr, "------------------------------\n");
						// -- finish compute security token Id

						// -------compute sequence number
						//payload1=0; payload2=0; payload3=0; payload4=0;
						// order of byte : payload[19] payload[18] payload[17] payload[16]
						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[16], payload[17], payload[18], payload[19]);
						printf("\tSequence Number on the wire(hex) = %s \n", mystring);
						fprintf(fptr, "\tSequence Number on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x",
						payload[19], payload[18], payload[17], payload[16]); 	// 0x00 0x00 0x01 0x4f
						printf("\tSequence reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\tSequence reorder (hex) = %s \n", mystring);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[0]) );
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[1]) );
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[2]) );
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[3]) );
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[4]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[5]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[6]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[7]) );
						sequenceNumber = n7+n6+n5+n4+n3+n2+n1+n0;
						printf("Sequence Number		: %ld \n", sequenceNumber);
						printf("----------------------------- \n");
						fprintf(fptr, "Sequence Number		: %ld \n", sequenceNumber);
						fprintf(fptr, "----------------------------- \n");
						// --- finish compute sequence number

						// -- compute requestId
						//payload1=0; payload2=0; payload3=0; payload4=0;
						// order of byte : payload[23] payload[22] payload[21] payload[20]
						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[20], payload[21], payload[22], payload[23]);
						printf("\trequestId on the wire(hex) = %s \n", mystring);
						fprintf(fptr, "\trequestId on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x",
							payload[23], payload[22], payload[21], payload[20]);
						printf("\trequestId reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\trequestId reorder (hex) = %s \n", mystring);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[0]) );
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[1]) );
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[2]) );
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[3]) );
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[4]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[5]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[6]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[7]) );
						requestId = n7+n6+n5+n4+n3+n2+n1+n0;
						printf("RequestId		: %ld \n", requestId);
						printf("----------------------------- \n");
						fprintf(fptr, "RequestId		: %ld \n", requestId);
						fprintf(fptr, "----------------------------- \n");
						// --- finish compute requestId

						// -- compute NodeId : encoding mask
						sprintf(mystring, "%.2x", payload[24]);
						printf("\tNodeId : Encoding Mask on the wire	: %s \n",  mystring);
						fprintf(fptr, "\tNodeId : Encoding Mask on the wire	: %s \n",  mystring);

						sprintf(mystring, "%.2x", payload[24]);
						printf("\tNodeId : Encoding Mask reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\tNodeId : Encoding Mask reorder (hex) = %s \n", mystring);

						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[0]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[1]) );

						encodingMask = (long long)(n0 + n1);
						printf("NodeId Encoding Mask	: %lld \n", encodingMask);
						printf("----------------------------- \n");
						fprintf(fptr, "NodeId Encoding Mask	: %lld \n", encodingMask);
						fprintf(fptr, "----------------------------- \n");
						// --- finish compute NodeId Encoding Mask

						// -- compute NodeId : namespaceIndex
						sprintf(mystring, "%.2x", payload[25]);
						printf("\tNodeId : NameSpaceIndex	on the wire : %s \n",  mystring);
						fprintf(fptr, "\tNodeId : NameSpaceIndex	on the wire : %s \n",  mystring);

						sprintf(mystring, "%.2x", payload[25]);
						printf("\tNodeId : NameSpaceIndex reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\tNodeId : NameSpaceIndex reorder (hex) = %s \n", mystring);

						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(payload[25]) );
						namespaceIndex = n0;
						printf("namespaceIndex 		: %ld \n", namespaceIndex);
						printf("------------------------------\n");
						fprintf(fptr, "namespaceIndex 		: %ld \n", namespaceIndex);
						fprintf(fptr, "------------------------------\n");
						// --- finish compute namespaceIndex

						// -- compute NodeId : Identifier
						//payload1=0; payload2=0;
						// order of byte : payload[27] payload[26]
						sprintf(mystring, "%.2x %.2x", payload[26], payload[27]);
						printf("\tNodeId : Identifier on the wire(hex) : %s \n", mystring);
						fprintf(fptr, "\tNodeId : Identifier on the wire(hex) : %s \n", mystring);

						sprintf(mystring, "%.2x%.2x", payload[27], payload[26]);
						printf("\tnodeId : Identifier reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\tnodeId : Identifier reorder (hex) = %s \n", mystring);

						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[0]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[1]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[2]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[3]) );
						nodeId = n3+n2+n1+n0;

						printf("NodeId : Identifier	: %ld \n",  nodeId);
						printf("----------------------------- \n");
						fprintf(fptr, "NodeId : Identifier	: %ld \n",  nodeId);
						fprintf(fptr, "----------------------------- \n");
						// --- finish compute NodeId

						printf("ReadResponse Header \n");
						printf("------------------- \n");
						fprintf(fptr, "ReadResponse Header \n");
						fprintf(fptr, "------------------- \n");
						// compute Timestamp
						//payload1=0; payload2=0; payload3=0; payload4=0; payload5=0; payload6=0; payload7=0; payload8=0;
						// order of byte : payload[35] payload[34] payload[33] payload[32] payload[31] payload[30] payload[29] payload[28]
						sprintf(mystring, "%.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x",
							payload[28], payload[29], payload[30], payload[31], payload[32], payload[33], payload[34], payload[35]);
						printf("\ttimeStamp on the wire(hex) = %s \n", mystring);
						fprintf(fptr, "\ttimeStamp on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x",
							payload[35], payload[34], payload[33], payload[32], payload[31], payload[30], payload[29], payload[28]);
						printf("\ttimestamp reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\ttimestamp reorder (hex) = %s \n", mystring);

						t15 = (unsigned long)(pow(16,15) * HEX_2_DEC(mystring[0]) );
						t14 = (unsigned long)(pow(16,14) * HEX_2_DEC(mystring[1]) );
						t13 = (unsigned long)(pow(16,13) * HEX_2_DEC(mystring[2]) );
						t12 = (unsigned long)(pow(16,12) * HEX_2_DEC(mystring[3]) );
						t11 = (unsigned long)(pow(16,11) * HEX_2_DEC(mystring[4]) );
						t10 = (unsigned long)(pow(16,10) * HEX_2_DEC(mystring[5]) );
						t9 = (unsigned long)(pow(16,9) * HEX_2_DEC(mystring[6]) );
						t8 = (unsigned long)(pow(16,8) * HEX_2_DEC(mystring[7]) );
						t7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[8]) );
						t6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[9]) );
						t5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[10]) );
						t4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[11]) );
						t3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[12]) );
						t2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[13]) );
						t1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[14]) );
						t0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[15]) );
						timeStamp = t15+t14+t13+t12+t11+t10+t9+t8+t7+t6+t5+t4+t3+t2+t1+t0;
						printf("\ttimestamp reorder (unsigned long long) = %lld \n", timeStamp);
						fprintf(fptr, "\ttimestamp reorder (unsigned long long) = %lld \n", timeStamp);

						//#ifdef CRASH
						info = localtime(&raw_time);
						printf("local time is %s \n", asctime(info));
						fprintf(fptr, "local time is %s \n", asctime(info));
						//strftime(buffer, sizeof(buffer), "%A, %B %d, %Y %H:%M:%S", info);
						//printf("Timestamp		: %s \n", buffer);
						//printf("Timestamp (ctime) : %s\n", ctime(&raw_time));
						//#endif
						if (ctime_r(&raw_time, time_str) != NULL) {
							printf("Timestamp		: %s \n", time_str);
							fprintf(fptr, "Timestamp		: %s \n", time_str);
						}
						else {
							printf("ctime_r() failed \n");
							fprintf(fptr, "ctime_r() failed \n");
						}
						printf("---------------------------- \n");
						fprintf(fptr, "---------------------------- \n");
						// --- finish compute timeStamp

						// -- compute Request Handle
						//payload1=0; payload2=0; payload3=0; payload4=0;
						// order of byte : payload[39] payload[38] payload[37] payload[36]
						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[36], payload[37], payload[38], payload[39]);
						printf("\ttrequestHandle on the wire(hex) = %s \n", mystring);
						fprintf(fptr, "\ttrequestHandle on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x", payload[39], payload[38], payload[37], payload[36]);
						printf("\trequestHandle reorder (hex) = %s \n", mystring);
						fprintf(fptr, "\trequestHandle reorder (hex) = %s \n", mystring);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[0]) );
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[1]) );
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[2]) );
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[3]) );
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[4]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[5]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[6]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[7]) );
						requestHandle = n7+n6+n5+n4+n3+n2+n1+n0;
						printf("Request Handle		: %ld \n",  requestHandle);
						printf("----------------------------- \n");
						fprintf(fptr, "Request Handle		: %ld \n",  requestHandle);
						fprintf(fptr, "----------------------------- \n");
						// -- finish compute Reqquest Handle

						// -- compute Service Results
						//payload1=0; payload2=0; payload3=0; payload4=0;
						// order of byte : payload[43] payload[42] payload[41] payload[40]
						sprintf(mystring, "%.2x %.2x %.2x %.2x",
							payload[40], payload[41], payload[42], payload[43]);
						printf("\tService Results on the wire(hex) = %s \n", mystring);
						fprintf(fptr, "\tService Results on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x%.2x%.2x%.2x", payload[43], payload[42], payload[41], payload[40]);
						printf("\tService Results reorder(hex) = %s \n", mystring);
						fprintf(fptr, "\tService Results reorder(hex) = %s \n", mystring);

						n7 = (unsigned long)(pow(16,7) * HEX_2_DEC(mystring[0]) );
						n6 = (unsigned long)(pow(16,6) * HEX_2_DEC(mystring[1]) );
						n5 = (unsigned long)(pow(16,5) * HEX_2_DEC(mystring[2]) );
						n4 = (unsigned long)(pow(16,4) * HEX_2_DEC(mystring[3]) );
						n3 = (unsigned long)(pow(16,3) * HEX_2_DEC(mystring[4]) );
						n2 = (unsigned long)(pow(16,2) * HEX_2_DEC(mystring[5]) );
						n1 = (unsigned long)(pow(16,1) * HEX_2_DEC(mystring[6]) );
						n0 = (unsigned long)(pow(16,0) * HEX_2_DEC(mystring[7]) );
						serviceResults = n7+n6+n5+n4+n3+n2+n1+n0;
						printf("Service Results	[0=Good]: %ld \n", serviceResults);
						printf("----------------------------- \n");
						fprintf(fptr, "Service Results	[0=Good]: %ld \n", serviceResults);
						fprintf(fptr, "----------------------------- \n");
						// -- end compute Service Results

						// --- compute Encoding Mask
						//payload1=0; payload2=0; payload3=0; payload4=0;
						// order of byte : payload[44]
						sprintf(mystring, "%.2x", payload[44]);
						printf("\tService Diagnostic : Encoding Mask on the wire(hex) = %s \n", mystring);
						fprintf(fptr, "\tService Diagnostic : Encoding Mask on the wire(hex) = %s \n", mystring);

						sprintf(mystring, "%.2x",  payload[44]);
						printf("\tService Diagnostic : Encoding Mask reorder(hex) = %s \n", mystring);
						fprintf(fptr, "\tService Diagnostic : Encoding Mask reorder(hex) = %s \n", mystring);

						ServiceDiagEncodingMask = (unsigned long int) (pow(16,0) * HEX_2_DEC(payload[44]) );
						printf("Service Diagnostic : Encoding Mask 	: %ld \n", ServiceDiagEncodingMask);
						printf("--------------------------------------------- \n");
						fprintf(fptr, "Service Diagnostic : Encoding Mask 	: %ld \n", ServiceDiagEncodingMask);
						fprintf(fptr, "--------------------------------------------- \n");
					// --- end compute Encoding Mask

				} // if (strncmp(messageType, "MSG", 3) == 0)
				else if (memcmp(messageType, "HEL", (unsigned long) 3) == 0) {
					printf("Caught a HEL header : %s \n", messageType);
						fprintf(fptr, "Caught a HEL header : %s \n", messageType);
					// extract info from Body
					printf("ProtocolVersion (4 bytes) 	: %f \n",
						payload[8]*pow(16,3) +  payload[9]*pow(16,2) + payload[10]*pow(16,1) + payload[11]*pow(16,0));
						fprintf(fptr, "ProtocolVersion (4 bytes) 	: %f \n",
							payload[8]*pow(16,3) +  payload[9]*pow(16,2) + payload[10]*pow(16,1) + payload[11]*pow(16,0));
					printf("ReceiveBufferSize (4 bytes) 	: %f \n",
						payload[12]*pow(16,3) + payload[13]*pow(16,2) + payload[14]*pow(16,1) + payload[15]*pow(16,0));
						fprintf(fptr, "ReceiveBufferSize (4 bytes) 	: %f \n",
							payload[12]*pow(16,3) + payload[13]*pow(16,2) + payload[14]*pow(16,1) + payload[15]*pow(16,0));
					printf("SendBufferSize (4 bytes)	: %f \n",
						payload[16]*pow(16,3) + payload[17]*pow(16,2) + payload[18]*pow(16,1) + payload[19]*pow(16,0));
						fprintf(fptr, "SendBufferSize (4 bytes)	: %f \n",
							payload[16]*pow(16,3) + payload[17]*pow(16,2) + payload[18]*pow(16,1) + payload[19]*pow(16,0));
					printf("MaxMessageSize (4 bytes)	: %f \n",
						payload[20]*pow(16,3) + payload[21]*pow(16,2) + payload[22]*pow(16,1) + payload[23]*pow(16,0));
						fprintf(fptr, "MaxMessageSize (4 bytes)	: %f \n",
							payload[20]*pow(16,3) + payload[21]*pow(16,2) + payload[22]*pow(16,1) + payload[23]*pow(16,0));
					printf("MaxChunkCount (4 bytes)		: %f \n",
						payload[24]*pow(16,3) + payload[25]*pow(16,2) + payload[26]*pow(16,1) + payload[27]*pow(16,0));
						fprintf(fptr, "MaxChunkCount (4 bytes)		: %f \n",
							payload[24]*pow(16,3) + payload[25]*pow(16,2) + payload[26]*pow(16,1) + payload[27]*pow(16,0));
					printf("EndpointUrl			: %s \n", payload + 28);
						fprintf(fptr, "EndpointUrl			: %s \n", payload + 28);
				} // if (memcmp(messageType, "HEL", (unsigned long) 3) == 0)
				else if (memcmp(messageType, "ACK", (unsigned long) 3) == 0) {
					printf("Caught a ACK header : %s \n", messageType);
					// extract info from Body
					printf("ProtocolVersion (4 bytes) 	: %f \n",
						payload[8]*pow(16,3) +  payload[9]*pow(16,2) + payload[10]*pow(16,1) + payload[11]*pow(16,0));
						fprintf(fptr, "ProtocolVersion (4 bytes) 	: %f \n",
							payload[8]*pow(16,3) +  payload[9]*pow(16,2) + payload[10]*pow(16,1) + payload[11]*pow(16,0));
					printf("ReceiveBufferSize (4 bytes) 	: %f \n",
						payload[12]*pow(16,3) + payload[13]*pow(16,2) + payload[14]*pow(16,1) + payload[15]*pow(16,0));
						fprintf(fptr, "ReceiveBufferSize (4 bytes) 	: %f \n",
							payload[12]*pow(16,3) + payload[13]*pow(16,2) + payload[14]*pow(16,1) + payload[15]*pow(16,0));
					printf("SendBufferSize (4 bytes)	: %f \n",
						payload[16]*pow(16,3) + payload[17]*pow(16,2) + payload[18]*pow(16,1) + payload[19]*pow(16,0));
						fprintf(fptr, "SendBufferSize (4 bytes)	: %f \n",
							payload[16]*pow(16,3) + payload[17]*pow(16,2) + payload[18]*pow(16,1) + payload[19]*pow(16,0));
					printf("MaxMessageSize (4 bytes)	: %f \n",
						payload[20]*pow(16,3) + payload[21]*pow(16,2) + payload[22]*pow(16,1) + payload[23]*pow(16,0));
						fprintf(fptr, "MaxMessageSize (4 bytes)	: %f \n",
							payload[20]*pow(16,3) + payload[21]*pow(16,2) + payload[22]*pow(16,1) + payload[23]*pow(16,0));
					printf("MaxChunkCount (4 bytes)		: %f \n",
						payload[24]*pow(16,3) + payload[25]*pow(16,2) + payload[26]*pow(16,1) + payload[27]*pow(16,0));
						fprintf(fptr, "MaxChunkCount (4 bytes)		: %f \n",
							payload[24]*pow(16,3) + payload[25]*pow(16,2) + payload[26]*pow(16,1) + payload[27]*pow(16,0));
				}  // if (memcmp(messageType, "ACK", (unsigned long) 3) == 0)
				else if (memcmp(messageType, "ERR", (unsigned long) 3) == 0) {
					printf("Caught a ERR header : %s \n", messageType);
						fprintf(fptr, "Caught a ERR header : %s \n", messageType);
					// extract info from body
					printf("Error (4 bytes)			: %f \n",  payload[8]*pow(16,3) +  payload[9]*pow(16,2) + payload[10]*pow(16,1) + payload[11]*pow(16,0));
					fprintf(fptr, "Error (4 bytes)		: %f \n",  payload[8]*pow(16,3) +  payload[9]*pow(16,2) + payload[10]*pow(16,1) + payload[11]*pow(16,0));
					printf("Reason				: %s \n", payload + 12);
					fprintf(fptr, "Reason			: %s \n", payload + 12);
				} // if (memcmp(messageType, "ERR", (unsigned long) 3) == 0)
				else if (memcmp(payload+8, "RHE", (unsigned long) 3) == 0) {
					printf("Caught a RHE header : %s \n", messageType);
					fprintf(fptr, "Caught a RHE header : %s \n", messageType);
					// extract info from body
					printf("ServerUri			: %s \n", payload + 8);
					printf("EndpointUri			: %s \n", payload + 4096 + 8);
					fprintf(fptr, "ServerUri		: %s \n", payload + 8);
					fprintf(fptr, "EndpointUri		: %s \n", payload + 4096 + 8);
				} // if (memcmp(payload+8, "RHE", (unsigned long) 3) == 0)
			} // if payload not in (HEL, ACK, MSG, OPN, CLO, ERR, RHE)
			else {
				printf("Cannot match network payload to HEL, ACK, MSG, OPN, CLO, ERR, RHE\n");
			} // if (payload_len >= 3)
	    } // if (!validHeader)
	} // if (choice == 6)

	NEXT:

	    /* Print its length */
	    printf("Jacked a packet with length of [%d]\n", header.len);

        } // if ( (ip_header->ip_p == IPPROTO_TCP)
    	} // if (ntohs(eth_header->ether_type) == ETHERTYPE_IP)
   	else {
        	printf("Not a ETHERTYPE_IP packet 0x%04x \n", ntohs(eth_header->ether_type));

        	switch (ntohs(eth_header->ether_type)) {
			// sniff OPCUA		// 0x0806
			case 0x0806:
			{
				printf("In case 0x0806 \n");
				break;
			}
       	 		// sniff profiNet
 			case ETH_P_PROFINET : // 0x8892
			{
				break;
			}

       			// sniff etherCAT
       			case ETH_P_ETHERCAT :  // 0x88A4
			{


				break;
			}

       			case ETHERTYPE_POWERLINK : // 0x88AB
			{

				break;
			}

			default : break;
		} // switch
     	} // else

  printf("processing  next device \n"); sleep(2);
  fprintf(fptr, "\n");
  fflush(fptr);

  } // for loop

  /* And close the session */
  pcap_close(handle);
  fprintf(fptr, "\n");
  fflush(fptr);
  fclose(fptr);

  return 0;
}
