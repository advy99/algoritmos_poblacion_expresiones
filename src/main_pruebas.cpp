#include <iostream>
#include "GA_P.hpp"
#include "random.hpp"

int main(int argc, char ** argv){

	if ( argc != 2 ) {
		std::cerr << "Error en el número de parámetros: " << std::endl;
		exit(-1);
	}


	GA_P::GA_P myGAP (argv[1], '@', 23);

	// for (int i = 0; i < GA_P::GA_P::getNumDatos(); i++){
	// 	for (int j = 0; j < GA_P::GA_P::getNumVariables(); j++){
	// 		std::cout << GA_P::GA_P::getDatos()[i][j] << " ";
	// 	}
	// 	std::cout << "\t\t" << GA_P::GA_P::getOutputDatos()[i];
	//
	// 	std::cout << std::endl;
	// }

	GA_P::Expresion miExpresion;

	miExpresion.generarExpresionAleatoria(13, 0.3, 3);

	std::vector<double> dato_prueba;

	dato_prueba.push_back(3.23);
	dato_prueba.push_back(286.7835);
	dato_prueba.push_back(32.019);

	std::cout << "Expresión 1:" << miExpresion << std::endl;
	std::cout << std::endl << "Evaluacion del dato: x0 = 3.23 \t x1 = 286.7835 \t x2 = 32.019: "
				 << std::endl << miExpresion.evaluarDato(dato_prueba) << std::endl;

	std::cout << std::endl << miExpresion.evaluarExpresion(GA_P::GA_P::getDatosLectura(), GA_P::GA_P::getOutputDatosLectura());


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
