#include <iostream>
#include "random.hpp"

int main(int argc, char ** argv){

	Random aleatorios;

	std::cout << aleatorios.getSeed() << std::endl;

	int aleatorio = aleatorios.getInt(20);
	std::cout << aleatorio << std::endl;

	for (int i = 0; i < aleatorio; i++){
		std::cout << aleatorios.getFloat() << std::endl;
	}

	return 0;

}
