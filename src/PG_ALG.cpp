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

void PG_ALG :: inicializarVacio() {
	prof_expresiones = 0;
	datos.clear();
	output_datos.clear();
}



Poblacion PG_ALG :: seleccionTorneo(const unsigned tam_torneo) {
	// partimos de una poblacion con el mismo tamaño que la actual
	Poblacion resultado = poblacion;

	std::vector<int> ganadores_torneo;



	// escojo una nueva poblacion del mismo tamaño
	#pragma omp parallel for
	for ( unsigned i = 0; i < poblacion.getTamPoblacion(); i++) {

		std::vector<int> participantes_torneo;
		int nuevo_participante;
		int mejor_torneo;

		// generamos el inicial y lo insertamos en los generados
		mejor_torneo = Random::getInt(poblacion.getTamPoblacion());

		participantes_torneo.push_back(mejor_torneo);

		// insertamos participantes hasta llegar al tamaño indicado
		while ( tam_torneo > participantes_torneo.size()) {
			nuevo_participante = Random::getInt(poblacion.getTamPoblacion());

			auto encontrado = std::find(participantes_torneo.begin(), participantes_torneo.end(), nuevo_participante);

			// si no aparece como participante
			if ( encontrado != participantes_torneo.end() ) {
				participantes_torneo.push_back(nuevo_participante);
				// si este nuevo participante tiene mejor fitness, lo cojemos como mejor
				if ( poblacion[nuevo_participante].getFitness() < poblacion[mejor_torneo].getFitness() ) {
					mejor_torneo = nuevo_participante;
				}

			}
		}

		// el ganador del torneo i es el mejor del torneo
		#pragma omp critical
		ganadores_torneo.push_back(mejor_torneo);
	}

	// actualizamos el resultado con los ganadores del torneo
	for ( unsigned i = 0; i < poblacion.getTamPoblacion(); i++) {
		resultado[i] = poblacion[ganadores_torneo[i]];
	}

	return resultado;
}

Expresion PG_ALG :: getMejorIndividuo() const {
	return poblacion.getMejorIndividuo();
}


} // namespace PG_ALGS
