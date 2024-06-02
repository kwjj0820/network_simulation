#ifndef SERVICE_INSTALLER_H
#define SERVICE_INSTALLER_H

#include "host.h"
#include "service.h"

// 서비스를 설치하는 역할
class ServiceInstaller {
protected:

  static int srcPort_;
  
  // 호스트와 서비스 서로간의 포인터를 저장한다.
  void install(Host *host, Service *service)
  {
    host->setService(service);
  }
};

#endif