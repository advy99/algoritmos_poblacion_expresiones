#include "GA_P.hpp"

#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <cstdlib>


GA_P::GA_P(const std::string fichero_datos, const char char_comentario, const char delimitador){

	bool lectura_correcta;

	lectura_correcta = leerDatos(fichero_datos, char_comentario);

	if (lectura_correcta){
		// inicilizamos poblacion


	}

}

bool GA_P::leerDatos(const std::string fichero_datos, const char char_comentario, const char delimitador){

	std::ifstream file(fichero_datos);
	bool resultado = true;

	if (!file){
		std::cerr << "Error al abrir " << fichero_datos << std::endl;
		resultado = false;

	} else {
		std::string linea;
		std::stringstream ss;

		std::getline(file, linea);

		while (!file.eof()){
			// si hemos leido una linea y no es un comentario, la procesamos
			if (linea.size() > 0 && linea[0] != char_comentario && !isblank(linea[0]) ) {

				std::vector<double> datos_linea;
				ss.str(linea);

				std::string str_valor;

				std::getline(ss, str_valor, delimitador);

				while (!ss.eof()){

					datos_linea.push_back(strtod(str_valor.c_str(), nullptr));
					std::getline(ss, str_valor, delimitador);

				}

				output_datos.push_back(strtod(str_valor.c_str(), nullptr));

				datos.push_back(datos_linea);



				ss.str("");
				ss.clear();

			}

			std::getline(file, linea);
		}



	}


	return resultado;
}




int GA_P::getNumDatos() {
	return datos.size();
}

int GA_P::getNumVariables() {
	return datos[0].size();
}

std::vector<std::vector<double> > GA_P::getDatos(){
	return datos;
}

std::vector<double> GA_P::getDato(const unsigned i){
	return datos[i];
}

std::vector<double> GA_P::getOutputDatos(){
	return output_datos;
}

double GA_P::getOutputDato(const unsigned indice){
	return output_datos[indice];
}

std::vector<std::vector<double>> GA_P::datos;
std::vector<double> GA_P::output_datos;
