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

	GA_P::GA_P myGAP (argv[1], '@', 50, 0.3, semilla);

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

	std::cout << std::endl << miExpresion.evaluarExpresion(myGAP.getDatos(), myGAP.getOutputDatos());


	GA_P::Expresion miExpresion2;

	miExpresion2.generarExpresionAleatoria(10, 0.4, 2);

	std::cout << std::endl;
	std::cout << "Arbol 1 antes de cruzar: " << std::endl << miExpresion << std::endl;
	std::cout << "Arbol 2 antes de cruzar: "<< std::endl << miExpresion2 << std::endl;

	int punto1 = Random::getInt(miExpresion.getLongitudArbol());
	int punto2 = Random::getInt(miExpresion2.getLongitudArbol());

	GA_P::Expresion hijo1 = miExpresion;
	GA_P::Expresion hijo2 = miExpresion2;

	miExpresion.intercambiarSubarbol(punto1, miExpresion2, punto2, hijo1, hijo2);

	std::cout << "Arbol 1 despues de cruzar: " << std::endl << hijo1 << std::endl;
	std::cout << "Arbol 2 despues de cruzar: "<< std::endl << hijo2 << std::endl;

	return 0;

}
