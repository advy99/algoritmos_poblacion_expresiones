#include "GA_P.hpp"

#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <cstdlib>

namespace GA_P{

GA_P :: GA_P(const unsigned long seed) {

	// inicializamos la semilla
	Random::setSeed(seed);

	inicializarVacio();

}

void GA_P :: inicializarVacio() {
	prof_expresiones = 0;
	datos.clear();
	output_datos.clear();
}

GA_P :: GA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed, const char delimitador, const unsigned prof){

	// al principio suponemos que se ha leido mal
	bool lectura_correcta = false;

	inicializarVacio();

	// lemos los datos del fichero de entrada
	lectura_correcta = leerDatos(fichero_datos, char_comentario, delimitador);
	prof_expresiones = prof;


	// inicializamos la semilla
	Random::setSeed(seed);

	// si se han leido bien, inicilizamos la poblacion
	if (lectura_correcta){
		// inicilizamos poblacion
		generarPoblacion(tam_poblacion, prof, prob_var);

	} else {
		// si no, mostramos un error
		std::cerr << "Error leyendo los datos de " << fichero_datos << std::endl;
	}

}


void GA_P :: generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp,
									 const double prob_var, const bool sustituir_actual) {
	if ( sustituir_actual ) {
		poblacion = Poblacion(tam_poblacion, profundidad_exp, prob_var,
									 getNumVariables(), getMaxProfExpresiones());

	}

}

GA_P :: ~GA_P(){
}


void GA_P :: cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas ) {
	datos = caracteristicas;
	output_datos = etiquetas;
}

bool GA_P :: leerDatos(const std::string fichero_datos,
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


void GA_P :: ajustar(const int num_eval, const double prob_cruce_gp,
							const double prob_cruce_ga, const double prob_mutacion_gp, 
							const double prob_mutacion_ga, const bool mostrar_evolucion) {

	const int NUM_GENERACIONES = num_eval / (double) poblacion.getTamPoblacion();

	int eval_actual = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	Poblacion  poblacion_antigua = poblacion;
	Poblacion poblacion_tmp;

	Expresion hijo1, hijo2;

	bool cruce_ga;
	bool cruce_gp;

	while ( eval_actual < NUM_GENERACIONES) {

		// intercambio la poblacion antigua y la actual
		poblacion_tmp = poblacion_antigua;
		poblacion_antigua = poblacion;
		poblacion = poblacion_tmp;


		// seleccionamos la poblacion a cruzar
		// TODO: seleccion por torneo

		// aplicamos los operadores geneticos
		for ( unsigned i = 0; i < poblacion.getTamPoblacion(); i += 2){
			madre = i;
			padre = i + 1;

			modificado_hijo1 = modificado_hijo2 = false;
			cruce_ga = cruce_gp = false;

			// cruce de la parte GA
			if ( Random::getFloat() < prob_cruce_ga ) {
				// cruce del cromosoma utilizando BLX_alfa
				poblacion[madre].cruceBLXalfa(poblacion[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_ga = true;
			}

			// cruce de la parte GP
			if ( Random::getFloat() < prob_cruce_gp ) {
				// cruce de programacion genetica, se intercambian arboles

				int pos_cruce_madre = Random::getInt(poblacion[madre].getLongitudArbol());
				int pos_cruce_padre = Random::getInt(poblacion[padre].getLongitudArbol());


				poblacion[madre].intercambiarSubarbol(pos_cruce_madre, poblacion[padre], pos_cruce_padre, hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_gp = true;
			}

			if ( !cruce_gp && !cruce_ga ) {
				// si no hay ningun tipo de cruce, asignamos los hijos tal cual
				hijo1 = poblacion[madre];
				hijo2 = poblacion[padre];

			} else {
				if ( !cruce_gp ) {
					// no se ha cruzado el arbol
					hijo1.asignarArbol(poblacion[madre].getArbol(), poblacion[madre].getLongitudArbol());
					hijo2.asignarArbol(poblacion[padre].getArbol(), poblacion[padre].getLongitudArbol());
				} else {
					// no se ha cruzado el cromosoma
					hijo1.asignarCromosoma(poblacion[madre].getCromosoma(), poblacion[madre].getLongitudCromosoma());
					hijo2.asignarCromosoma(poblacion[padre].getCromosoma(), poblacion[padre].getLongitudCromosoma());

				}
			}

			if ( Random::getFloat() < prob_mutacion_ga ) {
				// mutacion GA en el primer hijo
			}

			if ( Random::getFloat() < prob_mutacion_ga ) {
				// mutacion GA en el segundo hijo
			}

			if ( Random::getFloat() < prob_mutacion_gp ) {
				// mutacion GP en el primer hijo
			}

			if ( Random::getFloat() < prob_mutacion_gp ) {
				// mutacion GP en el segundo hijo
			}

			if ( modificado_hijo1 ) {
				poblacion[madre] = hijo1;
				poblacion[madre].dejaEstarEvaluada();
			}

			if ( modificado_hijo2) {
				poblacion[padre] = hijo2;
				poblacion[padre].dejaEstarEvaluada();
			}

		}

		// elitismo


		// evaluamos




		eval_actual++;

		if ( mostrar_evolucion ) {
			// mostramos el mejor individuo
		}

	}

}



int GA_P :: getNumDatos() const {
	return datos.size();
}

int GA_P :: getNumVariables() const {
	return datos[0].size();
}

std::vector<std::vector<double> > GA_P :: getDatos() const {
	return datos;
}

std::vector<double> GA_P :: getDato(const unsigned i) const {
	return datos[i];
}

std::vector<double> GA_P :: getOutputDatos() const {
	return output_datos;
}



double GA_P :: getOutputDato(const unsigned indice) const {
	return output_datos[indice];
}

unsigned GA_P :: getMaxProfExpresiones() const {
	return prof_expresiones;
}


} // namespace GA_P
