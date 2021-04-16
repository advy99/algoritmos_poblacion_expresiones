#include <iostream>

#include "algoritmos_poblaciones/preprocesado.hpp"

std::pair<std::vector<double>, std::vector<double> > preprocesar_fases(const matriz<std::string> & datos, const std::vector<std::string> etiquetas) {
	std::vector<double> datos_resultado;
	std::vector<double> etiquetas_resultado;

	datos_resultado.resize(datos.size());
	for(unsigned i = 0; i < datos.size(); i++) {
		datos_resultado[i] = 0.0;

		for ( unsigned j = 0; j < datos[i].size(); j++) {
			if ( datos[i][j] == "RegularPorosity" || datos[i][j] == "Absence" || datos[i][j] == "NotDefined"
				  || datos[i][j] == "Absent" ) {
				datos_resultado[i] += 1;
			} else if (  datos[i][j] == "RidgesFormation" || datos[i][j] == "Medium" || datos[i][j] == "Defined"
						||	 (datos[i][j] == "Present" && j != 7 ) || datos[i][j] == "InProcess" || datos[i][j] == "PartiallyFormed"  ) {
				datos_resultado[i] += 2;
			} else if (  datos[i][j] == "RidgesAndGrooves" || datos[i][j] == "Much" || datos[i][j] == "Present" || datos[i][j] == "FormedWithoutRarefactions"  ) {
				datos_resultado[i] += 3;
			} else if (  datos[i][j] == "GroovesShallow" || datos[i][j] == "FormedWitFewRarefactions"  ) {
				datos_resultado[i] += 4;
			} else if (  datos[i][j] == "GroovesRest" || datos[i][j] == "FormedWithLotRecessesAndProtrusions" ) {
				datos_resultado[i] += 5;
			} else if (  datos[i][j] == "NoGrooves" ) {
				datos_resultado[i] += 6;
			}
		}

	}

	etiquetas_resultado.resize(etiquetas.size());
	for ( unsigned i = 0; i < etiquetas.size() ; ++i) {
		if ( etiquetas[i] == "Ph01-19") {
			etiquetas_resultado[i] = 19.0;
		} else if ( etiquetas[i] == "Ph02-20-21") {
			etiquetas_resultado[i] = 20.5;
		} else if ( etiquetas[i] == "Ph03-22-24") {
			etiquetas_resultado[i] = 23.0;
		} else if ( etiquetas[i] == "Ph04-25-26") {
			etiquetas_resultado[i] = 25.5;
		} else if ( etiquetas[i] == "Ph05-27-30") {
			etiquetas_resultado[i] = 28.5;
		} else if ( etiquetas[i] == "Ph06-31-34") {
			etiquetas_resultado[i] = 32.5;
		} else if ( etiquetas[i] == "Ph07-35-39") {
			etiquetas_resultado[i] = 37.0;
		} else if ( etiquetas[i] == "Ph08-40-44") {
			etiquetas_resultado[i] = 42.0;
		} else if ( etiquetas[i] == "Ph09-45-49") {
			etiquetas_resultado[i] = 47.0;
		} else {
			etiquetas_resultado[i] = 55.0;
		}
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

	auto resultado = algoritmos_poblaciones::leer_datos<std::string>(fichero, comentario, separador);

	matriz<std::string> datos = resultado.first;
	std::vector<std::string> etiquetas = resultado.second;

	auto resultado_fases = preprocesar_fases(datos, etiquetas);

	std::vector<std::vector<double> > resultado_datos;
	resultado_datos.push_back(resultado_fases.first);

	algoritmos_poblaciones::escribir_datos(salida, resultado_datos, resultado_fases.second, separador);


}
