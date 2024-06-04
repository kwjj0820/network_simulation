#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"

class Host;

class Service {
  friend class ServiceInstaller;

  public:
    virtual void doService(Packet* packet) = 0;
<<<<<<< HEAD
    virtual ~Service() {}
=======

>>>>>>> c5ef0a0e49537eeefef944047b395bafabbe43c7
    short getPort(){return port_;}

  protected:

    // 서비스가 설치된 호스트
    Host *host_;

    // 서비스가 사용하는 포트
    short port_;

    Service(Host *host, int port) : host_(host), port_(port) {}
};

#endif