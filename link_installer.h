#ifndef LINK_INSTALLER_H
#define LINK_INSTALLER_H

#include "link.h"
#include "service.h"

class LinkInstaller {
public:
  // 노드 a, b 사이에 링크를 설치하고 반환한다.
  Link *install(Node *a, Node *b)
  {
    Link* newLink = new Link(a, b);
    a->addLink(newLink);
    b->addLink(newLink);
    return newLink;
  }
};

#endif