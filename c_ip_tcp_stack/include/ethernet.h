#ifndef ETHERNET_H
#define ETHERNET_H
#include <linux/if_ether.h>
#include <stdint.h>

//standard header type for communications across the LAN for ethernet
//project is based on automatic header standardization, hence the __attribute__((packed)), so GNU does not add byte paddings, alternatively, manual serialization/deserialization is accepted, but its redundant complexity 
struct eth_hdr{
   unsigned char smac[6];
   unsigned char dmac[6];
   uint16_t ethertype;
   unsigned char payload[];
}__attribute__((packed));


/**
   @brief initializes a header for ethernet communication across LAN
   @param args " "buf" as buffer
   @return eth_hdr pointer if successful
 **/

struct eth_hdr * init_eth_hdr(char * buf);

#endif /*ETHERNET.H*/