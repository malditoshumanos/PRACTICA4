#include "network.h"

int main()
{

    router rout1(57);
    rout1.addConnection(std::make_pair(3,3));
    rout1.addConnection(std::make_pair(4,3));
    rout1.addConnection(std::make_pair(5,3));
    rout1.print();

    bool bug = rout1.modifyConnection(std::make_pair(3,2));
    rout1.print();

    router r2(34);
    for(int i = 1; i<11; i++){
        r2.addConnection(std::make_pair(i, i+3));
    }
    r2.print();

    network red;
    red.addRouter(rout1);
    red.addRouter(r2);
    std::vector<int> listaDeRouters = red.listRouters();
    for(int i : listaDeRouters){
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    return 0;
}
