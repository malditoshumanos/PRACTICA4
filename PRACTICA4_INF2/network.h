#ifndef NETWORK_H
#define NETWORK_H

#include "router.h"
#include <list>
#include <algorithm>

class network
{
private:
    // The routers are stored in a list. There is no two routers with the same ID.
    std::list<router> networkRouters;

public:
    network(); // Constructor
    bool addRouter(router); // Only adds a new router if its ID didn´t exist previously. Returns wether the operation was successful.
    std::vector<int> listRouters(); // Returns a vector containing the ID´s of the routes in the network.
    std::vector<std::pair<int, int>> getRouterConnections(int ID); // Returns the connections of a router given its ID

    // TODO: Print a router. Modify an edge. Delete routers. Upsate routing tables when the graph is modified.
    // Get router by id.
    // ALYAWS CHECK THAT YOU'RE NOT FUCKING UP THE GRAPH

    // Create routing table for a particular router. Returns routing table.
    std::map<int, std::pair<int, int>> dijkstras(router startRouter);
};

#endif // NETWORK_H
