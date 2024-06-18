#include "Link.h"
#include "Node.h"

void Link::received(Packet* packet, Node* node) {
    std::cout << this->toString() << " packet in: " << packet->toString() <<
    " from " << node->toString() << std::endl;
    send_(packet, node);
}

void Link::received_(Packet* packet, Node* node) {
    Simulator::schedule(Simulator::now(), [this, packet, node]() {
        this->received(packet, node);
    });
}

void Link::send(Packet* packet, Node* node) {
    std::cout << this->toString() << " packet out: " << packet->toString() << " to " << other(node)->toString() << std::endl;
    Node* linkedNode = other(node);
    linkedNode->received_(packet, linkedNode);
}

void Link::send_(Packet* packet, Node* node) {
    Simulator::schedule(Simulator::now() + delay(), [this, packet, node]() {
        this->send(packet, node);
    });
}
