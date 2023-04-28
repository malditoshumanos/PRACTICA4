#include "network.h"

int main()
{
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
                std::cout << '\n';
                red.updateRoutingTables();
                break;}
            case 'E':{
                //Eliminar enrutador de la red ----------------------------------------------------------------
                int deleteRouter;
                std::cout << "Ingrese ID del router a eliminar de la red: ";
                std::cin >> deleteRouter;
                if(red.deleteRouter(deleteRouter)) std::cout << "Router correctamente eliminado.\n\n" ;
                red.updateRoutingTables();
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
                    std::cout << "Enlace modificado! \n\n";
                }else if(red.createEdge(startRout, endRout, newWeight)){
                    std::cout << "Enlace creado! \n\n";
                }
                red.updateRoutingTables();
                break;}
            case 'B':{
                //Borrar enlace entre enrutadores ----------------------------------------------------------------
                int delConStart;
                int delConEnd;
                int delWeight;
                std::cout << "Ingrese los 2 routers entre los que quiere eliminar la conexion y el costo asociado a esta: \n";
                std::cin >> delConStart;
                std::cin >> delConEnd;
                std::cin >> delWeight;
                if( red.deleteEdge(delConStart, delConEnd, delWeight) ) std::cout << "Enlace correctamente eliminado. \n\n";
                red.updateRoutingTables();
                break;}
            case 'P':{
                //Mostrar los enrutadores y las conexiones entre ellos ----------------------------------------------------------------
                red.printRouters();
                std::cout << '\n';
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
                std::cout << "\n\n";

                break;}
        default:
            if(option != 'X' && option != 'x') std::cout << "Opcion invalida. Intentalo de nuevo." << std::endl;
            break;
        }
    }

    return 0;
}
