#include <iostream>

#include <vector>
#include "algoritmos_poblaciones/preprocesado.hpp"

std::vector<double> suma_caracteristicas(const matriz<double> & datos) {
	std::vector<double> datos_resultado;
	std::vector<double> etiquetas_resultado;

	datos_resultado.resize(datos.size());
	for (unsigned i = 0; i < datos.size(); i++) {
		datos_resultado[i] = 0.0;

		for (unsigned j = 0; j < datos[i].size(); j++) {
			datos_resultado[i] += datos[i][j];
		}
	}

	return datos_resultado;

}


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

	auto resultado = algoritmos_poblaciones::leer_datos<double>(fichero, comentario, separador);

	matriz<double> datos = resultado.first;
	std::vector<double> etiquetas = resultado.second;

	std::vector<double> suma_c = suma_caracteristicas(datos);

	matriz<double> datos_finales;

	for ( unsigned i = 0; i < suma_c.size(); i++ ) {
		std::vector<double> tmp = {suma_c[i]};

		datos_finales.push_back(tmp);
	}


	algoritmos_poblaciones::escribir_datos(salida, datos_finales, etiquetas, separador);


}
