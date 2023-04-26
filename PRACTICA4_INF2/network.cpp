#include "network.h"

network::network()
{

}

// Deletes the router if found. Returns wether the operation was successful.
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

std::vector<int> network::listRouters(){
    std::vector<int> listID;
    for(auto it = networkRouters.begin(); it != networkRouters.end(); it++){
        listID.push_back(it->getID());
    }
    return listID;
}
