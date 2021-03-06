// network.h
// simple wrappers around frame-based xbee_send functionality to simulate
// meshed network capabilities using XBees
// author: Christophe VG

#ifndef __NETWORK_H
#define __NETWORK_H

#include <stdint.h>

#include "moose/xbee.h"

#ifndef FORWARD_FAILURE_PCT
#define FORWARD_FAILURE_PCT 0
#endif

// network config
#define DESTINATION XB_COORDINATOR

void mesh_init(void);

bool mesh_child_connected(void);

// wrapper functions to add virtual routing through a meshed network, using
// broadcasting and 1-hop messages, to mimic promiscuous operation
void mesh_send(uint16_t from, uint16_t to, uint8_t size, uint8_t* payload);

// utility function wrapping mesh_send to enable broadcast messages
void mesh_broadcast(uint16_t from, uint8_t size, uint8_t* payload);
  
// this is a handler that can be passed to xbee_on_receive
void mesh_receive(xbee_rx_t* frame);

// it will call a handler passed to this module adhering to this signature
typedef void (*mesh_rx_handler_t)(uint16_t source,
                                  uint16_t from, uint16_t to, uint16_t hop,
                                  uint8_t  size, uint8_t* payload);
// and registered through ...
void mesh_on_receive(mesh_rx_handler_t handler);

// it is also possible to get a copy of all messages that are transmitted
typedef void (*mesh_tx_handler_t)(uint16_t from, uint16_t to, uint16_t hop,
                                  uint8_t  size, uint8_t* payload);

void mesh_on_transmit(mesh_tx_handler_t handler);

#endif
