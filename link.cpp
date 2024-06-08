#include "Link.h"
#include "Node.h"

void Link::received(Packet* packet, Node* node)
{
    std::cout << this->toString() << "\t\t";
    Node* linkedNode = other(node); 
    std::cout << "packet in: " <<\
    packet->toString() << " from " << other(node)->toString() << std::endl;
    linkedNode->received_(packet, linkedNode);
}

void Link::received_(Packet* packet, Node* node)
{
    Simulator::schedule(Simulator::now() + delay(), [this, packet, node]
    (){this->received(packet, node);});
}