#include <iostream>
#include "GA_P.hpp"
#include "random.hpp"

int main(int argc, char ** argv){

	if ( argc != 2 ) {
		std::cerr << "Error en el número de parámetros: " << std::endl;
		exit(-1);
	}


	GA_P myGAP (argv[1], '@');

	for (int i = 0; i < GA_P::getNumDatos(); i++){
		for (int j = 0; j < GA_P::getNumVariables(); j++){
			std::cout << GA_P::getDatos()[i][j] << " ";
		}
		std::cout << "\t\t" << GA_P::getOutputDatos()[i];

		std::cout << std::endl;
	}

	Expresion miExpresion;

	miExpresion.generarExpresionAleatoria(10, 0.1);

	std::cout << std::endl << miExpresion.evaluarExpresion(GA_P::getDatosLectura(), GA_P::getOutputDatosLectura());


	Expresion miExpresion2;

	miExpresion2.generarExpresionAleatoria(10, 0.4);

	std::cout << std::endl;
	std::cout << "Arbol 1 antes de cruzar: " << std::endl << miExpresion << std::endl;
	std::cout << "Arbol 2 antes de cruzar: "<< std::endl << miExpresion2 << std::endl;

	int punto1 = Random::getInstance()->getInt(miExpresion.getLongitudArbol());
	int punto2 = Random::getInstance()->getInt(miExpresion2.getLongitudArbol());

	miExpresion.intercambiarSubarbol(punto1, miExpresion2, punto2);

	std::cout << "Arbol 1 despues de cruzar: " << std::endl << miExpresion << std::endl;
	std::cout << "Arbol 2 despues de cruzar: "<< std::endl << miExpresion2 << std::endl;

	return 0;

}
