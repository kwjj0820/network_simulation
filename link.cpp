#include "Link.h"
#include "Node.h"

void Link::received(Packet* packet, Node* node)
{
    Node* linkedNode = other(node); 
    std::cout << "Link: forwarding packet from node #" <<\
    node->id() << ", to node #" << linkedNode->id() << std::endl;
    linkedNode->received(packet, linkedNode);
}
