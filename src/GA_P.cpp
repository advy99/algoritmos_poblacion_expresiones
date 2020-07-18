#include "GA_P.hpp"

#include <iostream>
#include <fstream>


GA_P::GA_P(const std::string fichero_datos, const char char_comentario){

	bool lectura_correcta;

	lectura_correcta = leerDatos(fichero_datos, char_comentario);

	if (lectura_correcta){
		// inicilizamos poblacion
	}

}

bool GA_P::leerDatos(const std::string fichero_datos, const char char_comentario){

	ifstream file(fichero_datos);
	bool resultado = true;

	if (!file){
		std::cerr << "Error al abrir " << fichero_datos << std::endl;
		resultado = false;

	} else {
		std::string linea;

		std::getline(file, linea);

		// si hemos leido una linea y no es un comentario, la procesamos
		if (linea.size() > 0 && linea[0] != char_comentario &&  ) {

		}

	}


	return resultado;
}
