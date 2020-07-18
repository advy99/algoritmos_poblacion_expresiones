#include "GA_P.hpp"

#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>


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
		std::stringstream ss;

		std::getline(file, linea);

		while (!file.eof()){
			// si hemos leido una linea y no es un comentario, la procesamos
			if (linea.size() > 0 && linea[0] != char_comentario && !isblank(linea[0]) ) {

				std::vector<double> datos_linea;
				ss.str(linea);

				double valor;

				while (ss >> valor){
					datos_linea.push_back(valor);
				}

				output_datos.push_back(datos_linea.back());

				datos_linea.pop_back();
				datos.push_back(datos_linea);



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