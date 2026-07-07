#ifndef ARP_H
#define ARP_H

#include "netdev.h"

#define ARP_ETHERNET    0x0001
#define ARP_IPV4        0x0800
#define ARP_REQUEST     0x0001
#define ARP_REPLY       0x0002

#define ARP_CACHE_LEN   32
#define ARP_FREE        0
#define ARP_WAITING     1
#define ARP_RESOLVED    2

//header for address resolution protocol, for two devices communication via LAN, with known IP addresses, but unknown MAC addresses
struct arp_hdr{
   uint16_t hwtype; //hardware type
   uint16_t prototype; // self explanatory
   unsigned char hwsize; // hardware size
   unsigned char prosize; // prototype size 
   uint16_t opcode; //operation code 
   unsigned char data[]; //data payload, for IPv4 see struct down
} __attribute__((packed)); //disables GNU adding extra padding bytes, since arp payload is standard 

struct arp_ipv4{
   unsigned char smac; //sender MAC address
   uint32_t sip; //sender IP address
   unsigned char dmac; //destination/target MAC address
   uint32_t dip; //destination/target IP address
}__attribute__((packed)); //disables GNU adding extra padding bytes, since arp payload is standard 


struct arp_cache_entry{
   uint16_t hwtype;
   uint32_t sip;
   unsigned char smac;
   unsigned char state
};

/**
   @brief 
   @param args 
   @return
 **/
void arp_init();

/**
   @brief 
   @param args 
   @return
 **/
void arp_incoming(struct netdev * dev, struct eth_hdr * hdr);

/**
   @brief 
   @param args 
   @return
 **/
void arp_reply(struct netdev * dev, struct eth_hdr * hdr, struct arp_hdr * arphdr);

#endif /*ARP.H*/