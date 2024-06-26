#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include "address.h"
#include "host.h"
#include "service.h"
#include <iostream>

// send 함수를 호출하여 메시지를 전송할 수 있는 서비스
class MessageService : public Service {
  friend class MessageServiceInstaller;

private:
  // 목적지 주소
  Address destAddress_;
  // 목적지 포트
  short destPort_;

  MessageService(Host *host, short port, Address destAddress, short destPort)
      : Service(host, port), destAddress_(destAddress), destPort_(destPort) {}

public:
  ~MessageService() {}

  std::string name() {return "MessageService";}
  // 메시지를 전송한다
  void send(std::string message)
  {
    Packet* newPacket = new Packet(host_->address(), destAddress_, port_, destPort_, message);
    host_->send(newPacket);
  }

  void doService(Packet* packet)
  {
    std::cout << this->toString() << "\treceived \"" << packet->dataString() <<
    "\" from " << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;
  }

  void doService_(Packet* packet)
  {
    Simulator::schedule(Simulator::now(), [this, packet]
    (){this->doService(packet);
    delete packet;});
  }
};

#endif