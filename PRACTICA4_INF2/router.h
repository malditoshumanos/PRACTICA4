#ifndef ROUTER_H
#define ROUTER_H

#include <vector> //TODO: Should this #include be above the ifndef statement?
#include <iostream>

class router
{
private:
    int ID;
    // The edges of this vertex are represented by a vector of pairs (vertexThatIsConnectedTo, weightOfTheEdge)
    std::vector<std::pair<int, int>> connections;
    // TODO: include routing table


public:
    router(int ID); // Constructor
    bool addConnection(std::pair<int, int>);
    bool deleteConnection(std::pair <int, int>);
    bool modifyConnection(std::pair <int, int>);
    void print();


    int getID(){return ID;}
    std::vector<std::pair<int, int>> getConnections(){return connections;}
};

#endif // ROUTER_H
