
#include <iostream>

#include "algoritmos_poblaciones/preprocesado.hpp"


int main(int argc, char ** argv) {

	if ( argc < 3 ) {
		std::cerr << "ERROR: Se necesita al menos dos argumentos, la ruta al fichero y la salida." << std::endl;
		std::cerr << "\t Uso: " << argv[0] << " <fichero> <fichero_salida> [char_comentario] [char_separador]" << std::endl;
		exit(-1);
	}

	std::string fichero = argv[1];
	std::string salida = argv[2];
	char comentario = '@';
	char separador = ',';

	if (argc >= 4) {
		comentario = argv[3][0];
	}

	if (argc == 5) {
		separador = argv[4][0];
	}

	auto datos = algoritmos_poblaciones::leer_datos<double>(fichero, comentario, separador);

	algoritmos_poblaciones::conteo_clases(datos.second, salida);


}
