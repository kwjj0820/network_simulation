#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>
#include <iostream>

class Host : public Node {
  friend class ServiceInstaller;      

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

  short port_;

  void setService(Service *service)
  {
      services_.push_back(service);
  }

public:
  Address address() { return address_; }
  Host(Address address) : address_(address), port_(1000){}

  ~Host()
  {
    for(auto iter: services_)
    {
      delete iter;
    }
  }

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize()
  {
  }

  short getPort() {return port_++;}

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet)
  {
    int randomIndex = rand() % links.size();
    Link* seleted = links[randomIndex];
    std::cout << "Host #" << this->id() << ": sending packet (from: " << packet->srcAddress().toString()\
    << ", to: " << packet->destAddress().toString() << ", " << packet->dataString().length() << " bytes)" << std::endl;
    seleted->received(packet, seleted->b());
  }

  void received(Packet *packet, Node *node)
  {
    int size = services_.size();
    for(int i = 0; i < size; i++)
    {
      if(services_[i]->getPort() == packet->destPort())
      {
        std::cout << "Host #" << this->id() << ": received packet, "\
        << "destination port: " << packet->destPort() << std::endl;
        services_[i]->doService(packet);
        return;
      }
    }
    std::cout << "Host #" << this->id() << ": no service for packet (from: "
    << packet->srcAddress().toString() << ", to: " << packet->destAddress().toString()
    << ", " << packet->dataString().length() << " bytes)" << std::endl;
  }

  std::string name() {return "Host";}
};
#endif