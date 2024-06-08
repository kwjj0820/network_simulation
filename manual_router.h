#ifndef MANUAL_ROUTER_H
#define MANUAL_ROUTER_H

#include "address.h"
#include "router.h"
#include <iostream>

class ManualRouter : public Router {

public:
  int idx;
  std::vector<RoutingEntry*> entryPtr;
  ManualRouter()
  {
    idx = 0;
  }

  ~ManualRouter()
  {
    for(auto entry: entryPtr)
    {
      delete entry;
    }
  }

  std::string name() {return "ManualRouter";}

  // 목적지 주소에 따른 다음 링크를 설정한다.
  void addRoutingEntry(const Address &destination, Link *nextLink)
  {
    RoutingEntry* entry = new RoutingEntry(destination, nextLink);
    entryPtr.push_back(entry);
    routingTable_.push_back(*entry);
  }

  void received_(Packet* packet, Node* node)
  {
    Simulator::schedule(Simulator::now(), [this, packet, node]
    (){this->received(packet, node);});
  }

  void received(Packet* packet, Node* node)
  {
    // 패킷의 목적지 주소를 확인하여 라우팅 테이블에 존재하는지 확인합니다.
    bool found = false;
    int size = routingTable_.size();
    for (int i = 0; i < size; i++)
    {
      if (routingTable_[i].destination == packet->destAddress())
      {
        idx = i;
        found = true;
        break;
      }
    }

    // 라우팅 테이블에 목적지 주소가 없는 경우 메시지를 출력합니다.
    if (!found)
    {
      std::cout << this->toString() << "\t";
      std::cout << "Router #" << this->id() << ": no route for packet (from: "
      << packet->srcAddress().toString() << ", to: " << packet->destAddress().toString()
      << ", " << packet->dataString().length() << " bytes)" << std::endl;
    }
    else
    {
      std::cout << this->toString() << "\t";
      std::cout << "forwarding packet: "
      << packet->toString() << " to: " <<
      routingTable_[idx].nextLink->toString() << std::endl;
      routingTable_[idx].nextLink->received_(packet, node);
    }
  }
};

#endif