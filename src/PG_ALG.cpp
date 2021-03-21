#include "PG_ALG.hpp"

namespace PG_ALGS {


void PG_ALG :: cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas ) {
	datos = caracteristicas;
	output_datos = etiquetas;
}

bool PG_ALG :: leerDatos(const std::string fichero_datos,
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



int PG_ALG :: getNumDatos() const {
	return datos.size();
}

int PG_ALG :: getNumVariables() const {
	return datos[0].size();
}

std::vector<std::vector<double> > PG_ALG :: getDatos() const {
	return datos;
}

std::vector<double> PG_ALG :: getDato(const unsigned i) const {
	return datos[i];
}

std::vector<double> PG_ALG :: getOutputDatos() const {
	return output_datos;
}



double PG_ALG :: getOutputDato(const unsigned indice) const {
	return output_datos[indice];
}




} // namespace PG_ALGS
