#ifndef ECHO_SERVICE_H
#define ECHO_SERVICE_H

#include "host.h"
#include "service.h"
#include <iostream>
#include <string>

// 수신한 패킷을 전송자에게 다시 전송하는 서비스
class EchoService : public Service {
  friend class EchoServiceInstaller;

  public:
    ~EchoService() {}
    std::string name() {return "EchoService";}
    void doService(Packet* packet)
    {
      std::cout << "EchoService: received \"" << packet->dataString() << "\" from "\
      << packet->srcAddress().toString() << ":" << packet->srcPort() <<\
      ", send reply with same data" << std::endl;
      Packet* echoPacket = new Packet(packet->destAddress(), packet->srcAddress(),\
      packet->destPort(), packet->srcPort(), packet->data());
      host_->send(echoPacket);
      delete echoPacket;
    }

  private:
    EchoService(Host *host, short port) : Service(host, port) {}
};

#endif