#ifndef LINK_H
#define LINK_H

#include "packet.h"
#include <cstdlib>
#include <iostream>
#include "object.h"

class Node;

class Link: Object {
  friend class LinkInstaller;

public:
  Node* a() const { return nodeA_;}
  Node* b() const { return nodeB_;}
  void received(Packet* packet, Node* node);
  ~Link() {}
  double delay() { return delay_; }

  Node *nodeA() { return nodeA_; }

  Node *nodeB() { return nodeB_; }

  std::string name() {return "Link";}

private:
    Link(Node *nodeA, Node *nodeB, double delay = 0.0)
      : nodeA_(nodeA), nodeB_(nodeB), delay_(delay) {}

  Node *nodeA_;
  Node *nodeB_;
  double delay_;
  
  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }
};

#endif
