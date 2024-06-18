#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

class AutoRouter : public Router {
public:
    std::string name() { return "AutoRouter"; }
    std::vector<RoutingEntry*> entryPtr;

    void received_(Packet* packet, Node* node)
    {
      Simulator::schedule(Simulator::now(), [this, packet, node]
      (){this->received(packet, node);});
    }

    void received(Packet* packet, Node* node) {
        Address destAddress = packet->destAddress();
        if (routingTable_.find(destAddress) != routingTable_.end()) {
            Link *nextLink = routingTable_[destAddress];
            Node *nextNode = nextLink->other(node);
            std::cout << "Router " << this->toString() << " received packet destined for "
                      << destAddress.toString() << ". Forwarding to next hop: " 
                      << nextNode->toString() << std::endl;
            nextLink->received_(packet, nextNode);
        } else {
            std::cout << "Router " << this->toString() << " received packet destined for "
                      << destAddress.toString() << ". No route found." << std::endl;
        }
    }

    void calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links)
    {
      std::map<Node *, std::vector<std::pair<Node *, double>>> adjList;
      for (Link *link : links)
      {
        adjList[link->a()].emplace_back(link->b(), link->delay());
        adjList[link->b()].emplace_back(link->a(), link->delay());
      }

      for (Node *srcNode : nodes)
      {
        if (dynamic_cast<Host *>(srcNode) == nullptr) continue;

        std::map<Node *, double> dist;
        std::map<Node *, Node *> prev;
        std::set<std::pair<double, Node *>> pq;

        dist[srcNode] = 0;
        pq.emplace(0, srcNode);

        while (!pq.empty())
        {
          Node *u = pq.begin()->second;
          pq.erase(pq.begin());

          for (const auto &neighbor : adjList[u])
          {
            Node *v = neighbor.first;
            double weight = neighbor.second;

            if (dist.find(v) == dist.end() || dist[u] + weight < dist[v])
            {
              pq.erase({dist[v], v});
              dist[v] = dist[u] + weight;
              prev[v] = u;
              pq.emplace(dist[v], v);
            }
          }
        }

        for (Node *destNode : nodes)
        {
          if (destNode == srcNode || dynamic_cast<Host *>(destNode) == nullptr) continue;

          Node *current = destNode;
          Node *nextHop = nullptr;
          while (prev.find(current) != prev.end() && prev[current] != srcNode)
          {
            nextHop = current;
            current = prev[current];
          }
          if (prev[current] == srcNode)
          {
            nextHop = current;
          }

          if (nextHop)
          {
            Link *firstLink = findLinkBetween(srcNode, nextHop, links);
            addRoutingEntry(dynamic_cast<Host *>(destNode)->address(), firstLink);
            }
          }
      }
    }

private:
  void addRoutingEntry(const Address &destination, Link *nextLink)
  {
    RoutingEntry* entry = new RoutingEntry(destination, nextLink);
    entryPtr.push_back(entry);
    routingTable_.push_back(*entry);
  }
  Link *findLinkBetween(Node *a, Node *b, const std::vector<Link *> &links)
  {
    for (Link *link : links)
    {
      if ((link->a() == a && link->b() == b) || (link->a() == b && link->b() == a))
      {
        return link;
      }
    }
    return nullptr;
  }
};

#endif
