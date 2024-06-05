#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;


  RoutingEntry(const Address &address_, Link* link): destination(address_), nextLink(link){}
};

class Router : public Node {
  protected:
    std::vector<RoutingEntry> routingTable_;
};

#endif