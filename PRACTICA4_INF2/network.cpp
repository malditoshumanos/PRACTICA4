#include "network.h"

network::network()
{

}



// Adds a router. Only adds a new router if its ID didn´t exist previously. Returns wether the operation was successful.
bool network::addRouter(router newRouter){
    bool completed = false;

    int newID = newRouter.getID(); // ID of the new router
    std::vector<int> listID = listRouters(); // List the ID's of the current routers

    auto iter = std::find(listID.begin(), listID.end(), newID);
    if(iter == listID.end()){ // If the ID of the new router is not found on the list of ID's
        networkRouters.push_back(newRouter);
        completed = true;
    }
    return completed;
}



// Returns a vector containing the ID´s of the routes in the network
std::vector<int> network::listRouters(){
    std::vector<int> listID;
    for(auto it = networkRouters.begin(); it != networkRouters.end(); it++){
        listID.push_back(it->getID());
    }
    return listID;
}



// Returns the connections of a router given its ID
std::vector<std::pair<int, int>> network::getRouterConnections(int ID){
    for(auto it = networkRouters.begin(); it != networkRouters.end(); ++it){
        if(it->getID() == ID) return it->getConnections();
    }
    //TODO: implementar un return predeterminado si no se encuentra el ID
}

// Returns routing table of specified router
std::map<int, std::pair<int, int>> network::getRouterRoutRable(int ID){
    for(auto it = networkRouters.begin(); it != networkRouters.end(); ++it){
        if(it->getID() == ID) return it->getRoutingTable();
    }
    //TODO: implementar un return predeterminado si no se encuentra el ID
}



// Update or create the routing table for each router
void network::updateRoutingTables(){
    for(auto it = networkRouters.begin(); it != networkRouters.end(); ++it){
        it->setRoutingTable(dijkstras(*it));
    }
}



// Print information about each router
void network::printRouters(){
    for(auto it = networkRouters.begin(); it != networkRouters.end(); ++it){
        it->print();
    }
}



// Modify connection between two routers
bool network::modifyEdge(int startNode, int finalNode, int newWeight){
    bool cond1 = false;
    bool cond2 = false;
    for(auto it = networkRouters.begin(); it != networkRouters.end(); ++it){
        if(it->getID() == startNode){
            cond1 = it->modifyConnection(std::make_pair(finalNode, newWeight)); // Modify connection of startNode
        }
        if(it->getID() == finalNode){
            cond2 = it->modifyConnection(std::make_pair(startNode, newWeight)); // Modify connection of finalNode
        }
    }
    return (cond1 && cond2);
}



// Create edge between two nodes
bool network::createEdge(int startNode, int finalNode, int newWeight){
    bool cond1 = false;
    bool cond2 = false;
    for(auto it = networkRouters.begin(); it != networkRouters.end(); ++it){
        if(it->getID() == startNode){
            cond1 = it->addConnection(std::make_pair(finalNode, newWeight)); // Add connection to startNode (router)
        }
        if(it->getID() == finalNode){
            cond2 = it->addConnection(std::make_pair(startNode, newWeight)); // Add connection to finalNode (router)
        }
    }
    return (cond1 && cond2);
}







//TODO: Add explanation
std::map<int, std::pair<int, int>> network::dijkstras(router startRouter){
    // List that contains: ( nodeID, distanceToNode, viaWhichNode )
    std::list<std::array<int, 3>> distTable;

    //Create empty "distance table"
    std::vector<int> listID = listRouters();
    for(auto it = listID.begin(); it != listID.end(); ++it){
        distTable.push_back({*it, -7, -7}); // -7 means non-valid value.
    }

    // Set the distance of the origin router to 0 and move it to the begining of the list
    auto posTable = distTable.end();
    for(auto itr = distTable.begin(); itr != distTable.end(); ++itr){
        if((*itr)[0] == startRouter.getID()){ // If the ID of the startRouter is found
           posTable = itr;
           (*itr)[1] = 0; // The distance from a node to itself is 0
        }
    }
    distTable.splice(distTable.begin(), distTable, posTable);    

    // To store the results of the algorithm
    // The key is the router id. The pair contains (leght of path to router, via which router)
    std::map<int, std::pair<int, int>> routingTable;

    /* //FOR TESTING PURPOSES
    std::cout << "Distance table::::::::::::::::::::::::::::::::::::: " << std::endl;
    for(auto j : distTable){
        for(auto k : j){
            std::cout << k << " , ";
        }
        std::cout << std::endl;
    }
    std::cout << "Routing table for rout1::::::::::::::::::::::::::::::::::::: " << std::endl;
    for (auto const& [key, value] : routingTable) {
        std::cout << "Key: " << key << ", Value: (" << value.first << ", " << value.second << ")" << std::endl;
    }
    std::cout << "\n\n";
    */


    //LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP
    while(!distTable.empty()){
        auto currentPos = distTable.begin(); // The first element on distTable is taken
        int currentID = (*currentPos)[0];

        // Analyze the connections of the current router (currentID)
        std::vector<std::pair<int, int>> posCurrentConections = getRouterConnections(currentID);
        std::vector<std::pair<int, int>> currentConections;
        // Don't consider connections to routers that are already analyzed and inside routingTable
        for(auto j : posCurrentConections){
            bool inRoutTable = false;
            for(auto [key, val] : routingTable){
                if(key == j.first) inRoutTable = true;
            }
            if(!inRoutTable) currentConections.push_back(j);
        }

        // iterate over the connections of current router
        for(std::pair conn : currentConections){
            auto modDistTable = distTable.end(); // element to modify in distTable
            int evalID = conn.first; // ID of the router being analyzed in distTable

            // New distance obtained by analyzing the current router (currentID)
            // It is the lenght of the path to the current router (currentID) plus the weight of the link to the router (evalID)
            int newDist = ((*currentPos)[1]) + conn.second;

            int oldDist = 666; // So it isn´t a garbage value. The code should always change this value.
            for(auto itr = distTable.begin(); itr != distTable.end(); ++itr){
                if((*itr)[0] == evalID){
                    // Old distance is the distance that already existed on the distTable for evalID
                    oldDist = (*itr)[1];
                    modDistTable = itr; // Pointer to the element of distTable to modify (that represents evalID)
                }
            }

            if(newDist < oldDist || oldDist == -7){ // If the new distance found is les than the distance we had
                (*modDistTable)[1] = newDist; // New (shorter) distance found
                (*modDistTable)[2] = currentID; // The shortest path was found via the current router

                // Find the position of the first element with greater distance than newDist
                auto newPos = distTable.begin();
                while(newPos != distTable.end() && (*newPos)[1] <= newDist && (*newPos)[1] != -7){
                    ++newPos;
                }
                //If found, move the modified element modDistTable to a new position:
                // just before the first element that is a greater distance away
                if(newPos != distTable.end()){
                    distTable.splice(newPos, distTable, modDistTable);
                }
            }
        }

        // After iterating over the connections of the current router (currentID),
        // the router is done and we add it to the routing table
        routingTable.insert({currentID, {(*currentPos)[1], (*currentPos)[2]}}); // router, (lenghtToIT, viaWhichRouter)
        distTable.pop_front(); // Erase the fisrt router of distTable (currentID)

        /* //FOR TESTING PURPOSES
        std::cout << "Distance table::::::::::::::::::::::::::::::::::::: " << std::endl;
        for(auto j : distTable){
            for(auto k : j){
                std::cout << k << " , ";
            }
            std::cout << std::endl;
        }
        std::cout << "Routing table for rout1::::::::::::::::::::::::::::::::::::: " << std::endl;
        for (auto const& [key, value] : routingTable) {
            std::cout << "Key: " << key << ", Value: (" << value.first << ", " << value.second << ")" << std::endl;
        }
        std::cout << "\n\n";
        */
    }    

    return routingTable;
}


