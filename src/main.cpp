#include <iostream>
#include "GA_P.hpp"
#include "random.hpp"

int main(int argc, char ** argv){

	if ( argc != 2 ) {
		std::cerr << "Error en el número de parámetros: " << std::endl;
		exit(-1);
	}


	GA_P::GA_P myGAP (argv[1], '@', 1);

	for (int i = 0; i < myGAP.getNumDatos(); i++){
		for (int j = 0; j < myGAP.getNumVariables(); j++){
			std::cout << myGAP.getDatos()[i][j] << " ";
		}
		std::cout << "\t\t" << myGAP.getOutputDatos()[i];

		std::cout << std::endl;
	}

	GA_P::Expresion miExpresion;

	miExpresion.generarExpresionAleatoria(20, 1, 20);

	std::cout << std::endl << miExpresion.evaluarExpresion(myGAP.getDatosLectura(), myGAP.getOutputDatosLectura());


	GA_P::Expresion miExpresion2;

	miExpresion2.generarExpresionAleatoria(10, 0.4, 2);

	std::cout << std::endl;
	std::cout << "Arbol 1 antes de cruzar: " << std::endl << miExpresion << std::endl;
	std::cout << "Arbol 2 antes de cruzar: "<< std::endl << miExpresion2 << std::endl;

	int punto1 = Random::getInt(miExpresion.getLongitudArbol());
	int punto2 = Random::getInt(miExpresion2.getLongitudArbol());

	miExpresion.intercambiarSubarbol(punto1, miExpresion2, punto2);

	std::cout << "Arbol 1 despues de cruzar: " << std::endl << miExpresion << std::endl;
	std::cout << "Arbol 2 despues de cruzar: "<< std::endl << miExpresion2 << std::endl;

	return 0;

}
