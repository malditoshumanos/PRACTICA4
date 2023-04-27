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



    /*
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
    red.updateRoutingTables();
    red.printRouters();
    */

    //TODO: menú principal. En este menú se debe crear un router y tratar de añadirlo a la red. Eliminar routers. Recuerde actualizar la routing table.
    // Ofrecer la posibilidad de saber cuánto cuesta enviar un paquete desde un enrutador origen a uno destino.
    // Decir cúal es el camino que debe seguir un paquete para ser enviado de forma eficiente desde un enrutador origen a uno destino.


    std::cout << "Este programa simula una red de enrutadores. El programa inicia con un router de ID 1.\n";

    // Create network with one router
    network red;
    router rout1(1);
    red.addRouter(rout1);

    char option = 'F'; // I don't sanitize input
    while(option != 'X' && option != 'x'){
        std::cout << "*************************************************************\n";
        std::cout << "Ingrese la opcion deseada (X para salir):\n";
        std::cout << "  A --> Agregar enrutador a la red.\n";
        std::cout << "  E --> Eliminar enrutador de la red.\n";
        std::cout << "  M --> Modificar enlace entre enrutadores (si no existe lo crea).\n";
        std::cout << "  B --> Borrar enlace entre enrutadores.\n";
        std::cout << "  P --> Mostrar los enrutadores, las conexiones entre ellos y sus tablas de enrutamiento.\n";
        std::cout << "  C --> Calcular costo de envio entre dos enrutadores y camino optimo.\n";
        std::cout << "  >> ";

        std::cin >> option;
        switch(option){
            case 'A':{
                //Agregar enrutador a la red ----------------------------------------------------------------
                int idToADD;
                std::cout << "Ingrese ID del nuevo router: \n";
                std::cin >> idToADD;
                router routerToAdd(idToADD);
                if( red.addRouter(routerToAdd) ) std::cout << "Router agregado satisfactoriamente.\n";

                int x = 0;
                while(x != -1){
                    int w;
                    std::cout << "Ingrese nueva conexion del router... (-1 para no ingresar nuevas conexiones)\n";
                    std::cout << "Router para conectarse: \n";
                    std::cin >> x;
                    if(x == -1) break;
                    std::cout << "Costo de conexion: \n";
                    std::cin >> w;
                    // The connection is represented by a pair (node, weight)
                    red.createEdge(idToADD, x, w);
                }
                red.updateRoutingTables();
                break;}
            case 'E':{
                //Eliminar enrutador de la red ----------------------------------------------------------------

                break;}
            case 'M':{
                //Modificar o crear enlace entre enrutadores --------------------------------------------------------
                int startRout;
                int endRout;
                int newWeight;
                std::cout << "Ingrese los 2 routers entre los cuales quiere modificar o crear el enlace: \n";
                std::cin >> startRout;
                std::cin >> endRout;
                std::cout << "Ingrese el nuevo costo del enlace: \n";
                std::cin >> newWeight;
                if(red.modifyEdge(startRout, endRout, newWeight)){
                    std::cout << "Enlace modificado! \n";
                }else if(red.createEdge(startRout, endRout, newWeight)){
                    std::cout << "Enlace creado! \n";
                }
                red.updateRoutingTables();
                break;}
            case 'B':{
                //Borrar enlace entre enrutadores ----------------------------------------------------------------

                break;}
            case 'P':{
                //Mostrar los enrutadores y las conexiones entre ellos ----------------------------------------------------------------
                red.printRouters();
                break;}
            case 'C':{
                //Calcular costo de envío entre dos enrutadores y camino optimo ----------------------------------------------------------------
                int startR;
                int endR;
                std::cout << "Ingrese los 2 routers entre los cuales quiere saber el camino: \n";
                std::cin >> startR;
                std::cin >> endR;

                std::map<int, std::pair<int, int>> rTable = red.getRouterRoutRable(startR); // Routing table
                std::pair<int, int> auxPair =rTable[endR];
                std::cout << "La minima distancia entre los routers es " << auxPair.first << '\n';
                std::vector<int> path; // Path from start router (startR) to end router (endR)
                path.push_back(auxPair.second);

                //Iterate over the routing table finding the path between the two routers
                while(auxPair.second != startR){
                    for(auto const& [key, value] : rTable){
                        if(key == auxPair.second){
                            auxPair.second = value.second;
                            path.push_back(auxPair.second);
                        }
                    }
                }
                std::cout << "Los enrutadores por los que se debe ir son ";
                for (auto it = path.rbegin(); it != path.rend(); ++it) {
                        std::cout << *it << ", ";
                }
                std::cout << '\n';

                break;}
        default:
            if(option != 'X' && option != 'x') std::cout << "Opcion invalida. Intentalo de nuevo." << std::endl;
            break;
        }
    }




    // representar redes es solo una matriz 2*2 vector 2d?
    return 0;
}
