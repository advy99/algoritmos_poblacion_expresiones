
#include <iostream>

#include "algoritmos_poblaciones/preprocesado.hpp"


template <class T>
void conteo_clases (const std::vector<T> & etiquetas, const std::string & salida) {
	std::vector<int> elementos_cada_fase(10, 0);

	for ( auto it = etiquetas.begin(); it != etiquetas.end(); ++it) {
		if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 19.0) ) {
			elementos_cada_fase[0]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 20.5)) {
			elementos_cada_fase[1]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 23.0)) {
			elementos_cada_fase[2]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 25.5)) {
			elementos_cada_fase[3]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 28.5)) {
			elementos_cada_fase[4]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 32.5)) {
			elementos_cada_fase[5]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 37.0)) {
			elementos_cada_fase[6]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 42.0)) {
			elementos_cada_fase[7]++;
		} else if ( algoritmos_poblacion_expresiones::comparar_reales((*it), 47.0)) {
			elementos_cada_fase[8]++;
		} else {
			elementos_cada_fase[9]++;
		}
	}

	std::ofstream salida_conteo;
	salida_conteo.open(salida);

	for ( unsigned i = 0; i < elementos_cada_fase.size(); ++i) {
		salida_conteo << i + 1 << "\t" << elementos_cada_fase[i] << std::endl;
	}

	salida_conteo.close();

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

	auto datos = algoritmos_poblacion_expresiones::leer_datos<double>(fichero, comentario, separador);

	conteo_clases(datos.second, salida);


}
