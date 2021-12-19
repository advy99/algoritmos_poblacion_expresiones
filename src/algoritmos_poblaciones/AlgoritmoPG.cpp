#include "algoritmos_poblaciones/AlgoritmoPG.hpp"

namespace algoritmos_poblacion_expresiones {



AlgoritmoPG :: AlgoritmoPG(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
									const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var){
	inicializar_vacio();
	cargar_datos(datos, etiquetas);
	inicializar(seed, tam_poblacion, prof, prob_var);

}



AlgoritmoPG :: AlgoritmoPG(const std::string fichero_datos, const char char_comentario,
		  const unsigned tam_poblacion, const double prob_var,
		  const unsigned long seed,
		  const char delimitador, const unsigned prof){

	inicializar_vacio();
	leer_datos(fichero_datos, char_comentario, delimitador);

	inicializar(seed, tam_poblacion, prof, prob_var);

}


AlgoritmoPG :: ~AlgoritmoPG() {

}


void AlgoritmoPG :: ajustar(const Parametros & parametros) {

	const int NUM_GENERACIONES = parametros.get_numero_evaluaciones() / static_cast<double>(poblacion_.get_tam_poblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion_.evaluar_poblacion(datos_, output_datos_, parametros.get_funcion_evaluacion());

	Expresion mejor_individuo = poblacion_.get_mejor_individuo();

	Expresion hijo1, hijo2;

	while ( generacion < NUM_GENERACIONES) {

		// seleccionamos la poblacion a cruzar
		poblacion_ = seleccion_torneo(parametros.get_tamanio_torneo());

		// aplicamos los operadores geneticos
		for ( unsigned i = 0; i < poblacion_.get_tam_poblacion(); i += 2){

			madre = i;
			padre = i + 1;

			hijo1 = poblacion_[madre];
			hijo2 = poblacion_[padre];

			modificado_hijo1 = modificado_hijo2 = false;

			// cruce de la parte GP
			if ( Random::next_double() < parametros.get_probabilidad_cruce_GP() ) {
				// cruce de programacion genetica, se intercambian arboles

				poblacion_[madre].cruce_arbol(poblacion_[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
			}

			// si no hay cruce, los hijos ya estaban con el valor de los padres

			auto resultado_mut_gp = aplicar_mutaciones_GP(hijo1, hijo2, parametros.get_probabilidad_mutacion_GP());

			modificado_hijo1 = modificado_hijo1 || resultado_mut_gp.first;
			modificado_hijo2 = modificado_hijo2 || resultado_mut_gp.second;

			if ( modificado_hijo1 ) {
				poblacion_[madre] = hijo1;
				poblacion_[madre].deja_estar_evaluada();
			}

			if ( modificado_hijo2) {
				poblacion_[padre] = hijo2;
				poblacion_[padre].deja_estar_evaluada();
			}

		}


		aplicar_elitismo(mejor_individuo);


		// evaluamos
		poblacion_.evaluar_poblacion(datos_, output_datos_, parametros.get_funcion_evaluacion());

		mejor_individuo = poblacion_.get_mejor_individuo();

		if ( parametros.get_mostrar_evaluacion() ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.get_fitness() << std::endl;
		}

		generacion++;
	}

}


}
