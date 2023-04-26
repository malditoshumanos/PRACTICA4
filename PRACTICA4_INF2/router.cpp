#include "router.h"

router::router(int newID){ ID = newID;} // Constructor

// Adds a new connection to the router is it didn't exist previously. Returns wether the operion was succesful.
bool router::addConnection(std::pair<int, int> newConnection){
    bool completed = false;
    bool found = false;
    for(auto it = connections.begin(); it != connections.end(); ++it){
        if(it->first == newConnection.first){ // If we are connecting to a new router
            found  = true;
            completed = false;
        }
    }
    if(!found) connections.push_back(newConnection);
    return completed;
}

// Searchs for the pair to be deleted and if it is found, deletes it. Returns wether the operation was succesful.
bool router::deleteConnection(std::pair<int, int> conToDelete){
    bool completed = false;
    for(auto it = connections.begin(); it != connections.end(); ){
        if(it->first == conToDelete.first && it->second == conToDelete.second){
            it = connections.erase(it);
            completed = true;
        } else {
            it++;
        }
    }
    return completed;
}

// Modifies the connection if found. Returns wether the operation was succesful.
// The input parameter is a pair with ( connected node to modify connection with, new weight ).
bool router::modifyConnection(std::pair <int, int> conToMod){
// Note that it doesn´t ckeck if the new weight is actually different
    bool completed = 0;
    for(auto it = connections.begin(); it != connections.end(); ++it){
        if(it->first == conToMod.first){ // If the connection actually exists
            it->second = conToMod.second;
            completed = 1;
        }
    }
    return completed;
}

//Print information about the Router
void router::print(){
    std::cout << "Router " << ID << ":\n(Connected to, Weight)\n";
    for(std::pair p : connections){
        std::cout << '\t' << p.first << " , " << p.second << '\n';
    }
}


