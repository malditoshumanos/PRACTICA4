#include "network.h"

int main()
{

    /*
    router rout1(1);
    rout1.addConnection(std::make_pair(3,3));
    rout1.addConnection(std::make_pair(4,3));
    rout1.addConnection(std::make_pair(5,3));
    rout1.print();

    rout1.modifyConnection(std::make_pair(3,2));
    rout1.print();

    router r2(2);
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
    */
   router rout1(1);
    rout1.addConnection(std::make_pair(2,4));
    rout1.addConnection(std::make_pair(3,10));
    rout1.print();

    router rout2(2);
    rout2.addConnection(std::make_pair(1,4));
    rout2.addConnection(std::make_pair(4,1));
    rout2.print();

    router rout3(3);
    rout3.addConnection(std::make_pair(1,10));
    rout3.addConnection(std::make_pair(4,2));
    rout3.print();

    router rout4(4);
    rout4.addConnection(std::make_pair(2,1));
    rout4.addConnection(std::make_pair(3,2));
    rout4.print();

    network red;
    red.addRouter(rout1);
    red.addRouter(rout2);
    red.addRouter(rout3);
    red.addRouter(rout4);

    red.dijkstras(rout1);

    //TODO: menú principal. En este menú se debe crear un router y tratar de añadirlo a la red. Eliminar routers. Recuerde actualizar la routing table.
    // Ofrecer la posibilidad de saber cuánto cuesta enviar un paquete desde un enrutador origen a uno destino.
    // Decir cúal es el camino que debe seguir un paquete para ser enviado de forma eficiente desde un enrutador origen a uno destino.



    // representar redes es solo una matriz 2*2 vector 2d?
    return 0;
}
