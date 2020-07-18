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

	return 0;

}
