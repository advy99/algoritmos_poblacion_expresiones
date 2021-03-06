#include <iostream>
#include "GA_P.hpp"
#include <ctime>
#include "random.hpp"



int main(int argc, char ** argv){

	if ( argc < 2 || argc > 3 ) {
		std::cerr << "Error en el número de parámetros\n"
					 << "\t Uso: " << argv[0] << " <fichero_datos> [semilla]"
					 << std::endl;
		exit(-1);
	}

	int semilla;

	if ( argc == 3 ){
		semilla = atoi(argv[2]);
	} else {
		semilla = std::time(nullptr);
	}

	GA_P::GA_P myGAP (std::string(argv[1]), '@', 50, 0.3, semilla, ',', 10);

	myGAP.ajustar(500000, 0.8, 0.8, 0.2, 0.2, 16);


	std::cout << myGAP.getMejorIndividuo() << std::endl;

	return 0;

}
