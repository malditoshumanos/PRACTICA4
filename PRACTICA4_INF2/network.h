#ifndef NETWORK_H
#define NETWORK_H

#include "router.h"
#include <list>
#include <algorithm>

class network
{
private:

    std::list<router> networkRouters;
public:
    network(); // Constructor
    bool addRouter(router);
    std::vector<int> listRouters();
};

#endif // NETWORK_H
