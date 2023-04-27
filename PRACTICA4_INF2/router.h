#ifndef ROUTER_H
#define ROUTER_H

#include <vector> //TODO: Should this #include be above the ifndef statement?
#include <iostream>
#include <map>
#include <utility>

class router
{
private:
    int ID;
    // The edges of this vertex are represented by a vector of pairs (vertexThatIsConnectedTo, weightOfTheEdge)
    // The weight of an edge should never be 0 or less
    std::vector<std::pair<int, int>> connections;


    // TODO: include routing table. Method to find the cost and the path to a given router.


public:
    // The methods that have a bool return type return wether the operation was succesful.

    router(int ID); // Constructor

    bool addConnection(std::pair<int, int>); // Adds a new connection to the router is it didn't exist previously.
    bool deleteConnection(std::pair <int, int>); // Searchs for the pair to be deleted and if it is found, deletes it.
    // Modifies the connection if found.
    // The input parameter is a pair with ( connected node to modify connection with, new weight ).
    bool modifyConnection(std::pair <int, int>);
    bool isConnectedTo(int containsID); // Checks wether the router is connected to another router

    void print(); // Print ID and connections of the router

    int getID(){return ID;}
    std::vector<std::pair<int, int>> getConnections(){return connections;}
};

#endif // ROUTER_H
