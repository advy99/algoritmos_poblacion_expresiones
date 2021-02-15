#include "GA_P.hpp"

#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <cstdlib>

namespace GA_P{

GA_P::GA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed, const char delimitador, const unsigned prof){

	// al principio suponemos que se ha leido mal
	bool lectura_correcta = false;
	poblacion = nullptr;

	// lemos los datos del fichero de entrada
	lectura_correcta = leerDatos(fichero_datos, char_comentario, delimitador);
	prof_expresiones = prof;


	// inicializamos la semilla
	Random::setSeed(seed);

	// si se han leido bien, inicilizamos la poblacion
	if (lectura_correcta){
		// inicilizamos poblacion
		poblacion = new Poblacion(tam_poblacion, prof, prob_var, getNumVariables(),
										  getMaxProfExpresiones());

	} else {
		// si no, mostramos un error
		std::cerr << "Error leyendo los datos de " << fichero_datos << std::endl;
	}

}

GA_P::~GA_P(){
	liberarMemoria();
}

void GA_P::liberarMemoria(){
	// si la poblacion tiene una zona de memoria asignada, la liberamos
	if (poblacion != nullptr){
		delete poblacion;
	}

	poblacion = nullptr;
}


bool GA_P::leerDatos(const std::string fichero_datos,
							const char char_comentario, const char delimitador){
	// abrimos el fichero de lectura
	std::ifstream file(fichero_datos);
	bool resultado = true;

	// mostramos un error si no podemos abrirlo
	if (!file){
		std::cerr << "Error al abrir " << fichero_datos << std::endl;
		resultado = false;

	} else {
		// leemos una linea
		std::string linea;
		std::stringstream ss;

		std::getline(file, linea);

		// mientras no encuentre el EOF
		while (!file.eof()){
			// si hemos leido una linea y no es un comentario, la procesamos
			if (linea.size() > 0 && linea[0] != char_comentario &&
				 !isblank(linea[0]) ) {
				// leemos por linea
				std::vector<double> datos_linea;
				ss.str(linea);

				std::string str_valor;

				std::getline(ss, str_valor, delimitador);

				// mientras queden valores en la linea
				while (!ss.eof()){
					// los metemos en ese dato
					datos_linea.push_back(strtod(str_valor.c_str(), nullptr));
					std::getline(ss, str_valor, delimitador);

				}

				// el ultimo dato no tiene separador, lo incluimos
				output_datos.push_back(strtod(str_valor.c_str(), nullptr));

				// introducimos el dato en la matriz final de datos
 				datos.push_back(datos_linea);


				// reseteamos el lector de strgin para leer la siguiente linea
				ss.str("");
				ss.clear();

			}

			std::getline(file, linea);
		}



	}


	return resultado;
}




int GA_P::getNumDatos() const {
	return datos.size();
}

int GA_P::getNumVariables() const {
	return datos[0].size();
}

std::vector<std::vector<double> > GA_P::getDatos() const {
	return datos;
}

std::vector<double> GA_P::getDato(const unsigned i) const {
	return datos[i];
}

std::vector<double> GA_P::getOutputDatos() const {
	return output_datos;
}



double GA_P::getOutputDato(const unsigned indice) const {
	return output_datos[indice];
}

unsigned GA_P::getMaxProfExpresiones() const {
	return prof_expresiones;
}


}
