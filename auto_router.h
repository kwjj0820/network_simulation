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

    void calculate(const std::vector<Node *> &nodes, const std::vector<Link *> &links)
    {
      //다익스트라를 돌린다.
      double matrix[9999][9999];
      for(int i = 0; i < nodes.size(); i++)
      {
        for(int j = 0; j < nodes.size(); j++)
        {
          matrix[i][j] = 9999999;
          Node* a = nodes[i];
          Node* b = nodes[j];
          for(int k = 0; k < links.size(); k++)
          {
            Link* l = links[k];
            if(l->nodeA() == a && l->nodeB() == b)
            {
              matrix[i][j] = l->delay();
            }
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
};

#endif
