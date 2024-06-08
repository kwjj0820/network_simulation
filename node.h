#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>
#include "object.h"

class Node: Object {
  friend class LinkInstaller;

private:
  std::string id_;

public:
  Node() : id_("") {}
  std::string id() const { return id_; }
  std::vector<Link*> links;
  virtual ~Node() {}
  void addLink(Link* link)
  {
    links.push_back(link);
  }
  virtual std::string name() {return "Node";}
  virtual void received(Packet* packet, Node *node) = 0;
  virtual void received_(Packet* pakcet, Node* node) = 0;
  std::string toString()
  {
    return Object::toString();
  }
};

#endif