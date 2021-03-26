#include <iostream>

#include "preprocesado.hpp"

std::pair<matriz<double>, std::vector<double> > preprocesar_fases(const matriz<std::string> & datos, const std::vector<std::string> etiquetas) {
	matriz<double> datos_resultado;
	std::vector<double> etiquetas_resultado;

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

	if ( argc < 2 ) {
		std::cerr << "ERROR: Se necesita al menos un argumento, la ruta al fichero." << std::endl;
		std::cerr << "\t Uso: " << argv[0] << " <fichero> [char_comentario] [char_separador]" << std::endl;
		exit(-1);
	}

	std::string fichero = argv[1];
	char comentario = '@';
	char separador = ',';

	if (argc >= 3) {
		comentario = argv[2][0];
	}

	if (argc == 4) {
		separador = argv[3][0];
	}

	auto resultado = PG_ALGS::leer_datos<std::string>(fichero, comentario, separador);

	matriz<std::string> datos = resultado.first;
	std::vector<std::string> etiquetas = resultado.second;

	auto resultado_fases = preprocesar_fases(datos, etiquetas);


	std::vector<int> elementos_cada_fase(10, 0);

	for ( auto it = resultado_fases.second.begin(); it != resultado_fases.second.end(); ++it) {
		if ( PG_ALGS::comparar_reales((*it), 19.0) ) {
			elementos_cada_fase[0]++;
		} else if ( PG_ALGS::comparar_reales((*it), 20.5)) {
			elementos_cada_fase[1]++;
		} else if ( PG_ALGS::comparar_reales((*it), 23.0)) {
			elementos_cada_fase[2]++;
		} else if ( PG_ALGS::comparar_reales((*it), 25.5)) {
			elementos_cada_fase[3]++;
		} else if ( PG_ALGS::comparar_reales((*it), 28.5)) {
			elementos_cada_fase[4]++;
		} else if ( PG_ALGS::comparar_reales((*it), 32.5)) {
			elementos_cada_fase[5]++;
		} else if ( PG_ALGS::comparar_reales((*it), 37.0)) {
			elementos_cada_fase[6]++;
		} else if ( PG_ALGS::comparar_reales((*it), 42.0)) {
			elementos_cada_fase[7]++;
		} else if ( PG_ALGS::comparar_reales((*it), 47.0)) {
			elementos_cada_fase[8]++;
		} else {
			elementos_cada_fase[9]++;
		}
	}

	std::ofstream salida_conteo;
	salida_conteo.open("graficas/datos/num_elementos_fase.dat");
	for ( unsigned i = 0; i < elementos_cada_fase.size(); ++i) {
		salida_conteo << i + 1 << "\t" << elementos_cada_fase[i] << std::endl;
	}



}
