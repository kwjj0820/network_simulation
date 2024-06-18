#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
public:
  std::string name() {return "PacketSinkService";}

  void doService(Packet* packet)
  {
    totalBytes += packet->data().size();
  }

private:
  int totalBytes;
  PacketSinkService(Host *host, short port)
  : Service(host, port), totalBytes(0) {};
};

#endif