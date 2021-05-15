#include <iostream>

#include "algoritmos_poblaciones/preprocesado.hpp"

std::pair<matriz<double>, std::vector<double> > preprocesar_regresion(const matriz<std::string> & datos, const std::vector<std::string> etiquetas) {
	matriz<double> datos_resultado;
	std::vector<double> etiquetas_resultado;

	datos_resultado.resize(datos.size());
	for(unsigned i = 0; i < datos.size(); i++) {
		datos_resultado[i].resize(datos[i].size());

		for ( unsigned j = 0; j < datos[i].size(); j++) {
			if ( datos[i][j] == "NoGrooves" || datos[i][j] == "Absence" || datos[i][j] == "NotDefined"
				  || datos[i][j] == "Absent" ) {
				datos_resultado[i][j] = 1;
			} else if (  datos[i][j] == "GroovesRest" || datos[i][j] == "Medium" || datos[i][j] == "Defined"
						||	 (datos[i][j] == "Present" && j != 7 ) || datos[i][j] == "InProcess" || datos[i][j] == "PartiallyFormed"  ) {
				datos_resultado[i][j] = 2;
			} else if (  datos[i][j] == "GroovesShallow" || datos[i][j] == "Much" || datos[i][j] == "Present" || datos[i][j] == "FormedWithoutRarefactions"  ) {
				datos_resultado[i][j] = 3;
			} else if (  datos[i][j] == "RidgesAndGrooves" || datos[i][j] == "FormedWitFewRarefactions"  ) {
				datos_resultado[i][j] = 4;
			} else if (  datos[i][j] == "RidgesFormation" || datos[i][j] == "FormedWithLotRecessesAndProtrusions" ) {
				datos_resultado[i][j] = 5;
			} else if (  datos[i][j] == "RegularPorosity" ) {
				datos_resultado[i][j] = 6;
			}
		}

	}

	etiquetas_resultado.resize(etiquetas.size());
	for ( unsigned i = 0; i < etiquetas.size() ; ++i) {
		etiquetas_resultado[i] = atof(etiquetas[i].c_str());
	}

	return std::make_pair(datos_resultado, etiquetas_resultado);

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

	auto resultado = algoritmos_poblacion_expresiones::leer_datos<std::string>(fichero, comentario, separador);

	matriz<std::string> datos = resultado.first;
	std::vector<std::string> etiquetas = resultado.second;

	auto resultado_fases = preprocesar_regresion(datos, etiquetas);

	algoritmos_poblacion_expresiones::escribir_datos(salida, resultado_fases.first, resultado_fases.second, separador);


}
