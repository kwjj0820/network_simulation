#ifndef LINK_H
#define LINK_H

#include "packet.h"
#include <cstdlib>
#include <iostream>

class Node;

class Link {
  friend class LinkInstaller;

public:
  Node* a() const { return nodeA_;}
  Node* b() const { return nodeB_;}
  void linker(Packet* packet, Node* node)
  {
    Node* linkedNode = other(node); 
    std::cout << "Link: forwarding packet from node #" <<\
    node->id() << ", to node #" << linkedNode->id();
    linkedNode->received(packet, linkedNode);
  }

private:
  Link(Node *nodeA, Node *nodeB) : nodeA_(nodeA), nodeB_(nodeB) {}

  Node *nodeA_;
  Node *nodeB_;
  
  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }
};

#endif