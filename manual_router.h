#ifndef MANUAL_ROUTER_H
#define MANUAL_ROUTER_H

#include "address.h"
#include "router.h"
#include <iostream>

class ManualRouter : public Router {

public:
  // 목적지 주소에 따른 다음 링크를 설정한다.
  void addRoutingEntry(const Address &destination, Link *nextLink)
  {
    RoutingEntry* entry = new RoutingEntry(destination, nextLink);
    routingTable_.push_back(*entry);
  }

  void received(Packet* packet, Node* node)
  {
    std::cout << "Router #" << this->id() << ": forwarding packet (from: "\
    << packet->srcAddress().toString() << ", to: " << packet->destAddress().toString()\
    << ", " << packet->dataString().length() << " bytes" << std::endl;
    Link* linked = routingTable_[this->id()].nextLink;
    linked->linker(packet, linked->b());
  }
};

#endif