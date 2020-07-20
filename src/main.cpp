#include <iostream>
#include "GA_P.hpp"
#include "random.hpp"

int main(int argc, char ** argv){

	GA_P myGAP ("datos/ele-1.dat", '@');

	for (int i = 0; i < GA_P::getNumDatos(); i++){
		for (int j = 0; j < GA_P::getNumVariables(); j++){
			std::cout << GA_P::getDatos()[i][j] << " ";
		}
		std::cout << "\t\t" << GA_P::getOutputDatos()[i];

		std::cout << std::endl;
	}

	Expresion miExpresion;

	miExpresion.generarExpresionAleatoria(10, 0.4);

	std::cout << std::endl << miExpresion.evaluarExpresion();


	Expresion miExpresion2;

	miExpresion2.generarExpresionAleatoria(10, 0.4);

	std::cout << std::endl << miExpresion2.evaluarExpresion();

	miExpresion.intercambiarSubarbol(Random::getInstance()->getInt(miExpresion.getLongitudArbol()), miExpresion2, Random::getInstance()->getInt(miExpresion2.getLongitudArbol()));

	std::cout << std::endl << std::endl << miExpresion.evaluarExpresion();

	std::cout << std::endl << miExpresion2.evaluarExpresion();



	std::cout << std::endl << "Profundidad: " << miExpresion.calcularProfundidad() << std::endl;


	return 0;

}
