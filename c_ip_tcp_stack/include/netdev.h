#ifndef NETDEV_H
#define NETDEV_H

#include "ethernet.h"
#include "sys.h"

struct netdev{
   uint16_t addr;
   unsigned char hwaddr[6];
};

/**
   @brief 
   @param args 
   @return
 **/
struct netdev * netdev_init(struct netdev * dev, char * addr, char * hwaddr);

/**
   @brief 
   @param args 
   @return
 **/
void netdev_transmit(struct netdev * dev, struct eth_hdr * hdr, uint16_t ethertype, int len, unsigned char * dst);



#endif /*NETDEV.H*/