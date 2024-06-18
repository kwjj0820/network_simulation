#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

public:
  std::string name() {return "BulkSendServiceInstaller";}

  static double bulkTime;

  void doService_(Packet* packet)
  {
    if(Simulator::now() < stopTime_)
    {
      Simulator::schedule(Simulator::now() + delay_, [this, packet]
      (){this->doService(packet);});
    }
  }

  void doService(Packet* packet)
  {
    std::string data(PACKET_SIZE, 'A');
    Packet* bulkPacket = new Packet(host_->address(), destAddress_, port_, destPort_, data);
    host_->send_(bulkPacket);
  }
private:
  Address destAddress_;
  short destPort_;
  double delay_;
  double startTime_;
  double stopTime_;

 BulkSendService(Host *host,
                 short port,
                 Address destAddress,
                 short destPort,
                 double delay = 1.0,
                 double startTime = 0.0,
                 double stopTime = 10.0)
                 : Service(host, port),
                 destAddress_(destAddress),
                 destPort_(destPort), delay_(delay),
                 startTime_(startTime),
                 stopTime_(stopTime) {};
};

#endif