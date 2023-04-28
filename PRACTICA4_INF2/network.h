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
    std::map<int, std::pair<int, int>> getRouterRoutRable(int ID); // Returns routing table of specified router


    void updateRoutingTables(); // Update or create the routing table for each router
    void printRouters(); // Print information about each router
    bool modifyEdge(int startNode, int finalNode, int newWeight); // Modify connection between two routers
    bool createEdge(int startNode, int finalNode, int newWeight); // Create edge between two nodes
    bool deleteEdge(int startNode, int finalNode, int weight); // Delete connection between two nodes

    bool deleteRouter(int deleteID); // Delete router from the network.


    // Create routing table for a particular router. Returns routing table.
    std::map<int, std::pair<int, int>> dijkstras(router startRouter);
};

#endif // NETWORK_H
