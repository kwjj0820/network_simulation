#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }
  std::vector<Link*> links;
<<<<<<< HEAD
  virtual ~Node() {}
=======
>>>>>>> c5ef0a0e49537eeefef944047b395bafabbe43c7
  void addLink(Link* link)
  {
    links.push_back(link);
  }
  virtual void received(Packet* packet, Node *node) = 0;
};

#endif