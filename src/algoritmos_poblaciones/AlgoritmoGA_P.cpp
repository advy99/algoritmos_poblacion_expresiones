#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"

namespace algoritmos_poblaciones {


AlgoritmoGA_P :: AlgoritmoGA_P(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {
	inicializar(seed, tam_poblacion, prof, prob_var);

}



AlgoritmoGA_P :: AlgoritmoGA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed, const char delimitador, const unsigned prof){

	inicializarVacio();

	// lemos los datos del fichero de entrada
	leerDatos(fichero_datos, char_comentario, delimitador);
	prof_expresiones = prof;


	// inicializamos la semilla
	Random::setSeed(seed);


	generarPoblacion(tam_poblacion, prof, prob_var, true);

}



AlgoritmoGA_P :: ~AlgoritmoGA_P(){
}


void AlgoritmoGA_P :: ajustar(const int num_eval, const double prob_cruce_gp,
							const double prob_cruce_ga, const double prob_mutacion_gp,
							const double prob_mutacion_ga, const int tam_torneo,
							const bool mostrar_evolucion) {

	const int NUM_GENERACIONES = num_eval / static_cast<double>(poblacion.getTamPoblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion.evaluarPoblacion(datos, output_datos);

	Expresion_GAP mejor_individuo = poblacion.getMejorIndividuo();

	Expresion_GAP hijo1, hijo2;

	bool cruce_ga;
	bool cruce_gp;

	while ( generacion < NUM_GENERACIONES) {

		// seleccionamos la poblacion a cruzar
		poblacion = seleccionTorneo(tam_torneo);

		// aplicamos los operadores geneticos
		for ( unsigned i = 0; i < poblacion.getTamPoblacion(); i += 2){

			madre = i;
			padre = i + 1;

			hijo1 = poblacion[madre];
			hijo2 = poblacion[padre];

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

				poblacion[madre].cruceArbol(poblacion[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_gp = true;
			}

			if ( cruce_gp || cruce_ga ) {
				// si hay algun tipo de cruce
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
			// si no hay cruce, los hijos ya estaban con el valor de los padres
			if ( Random::getFloat() < prob_mutacion_ga ) {
				// mutacion GP en el primer hijo
				hijo1.mutarGA(generacion, NUM_GENERACIONES);
				modificado_hijo1 = true;
			}

			if ( Random::getFloat() < prob_mutacion_ga ) {
				// mutacion GP en el segundo hijo
				hijo2.mutarGA(generacion, NUM_GENERACIONES);
				modificado_hijo2 = true;
			}


			auto resultado_mut_gp = aplicarMutacionesGP(hijo1, hijo2, prob_mutacion_gp);

			modificado_hijo1 = modificado_hijo1 || resultado_mut_gp.first;
			modificado_hijo2 = modificado_hijo2 || resultado_mut_gp.second;

			if ( modificado_hijo1 ) {
				poblacion[madre] = hijo1;
				poblacion[madre].dejaEstarEvaluada();
			}

			if ( modificado_hijo2) {
				poblacion[padre] = hijo2;
				poblacion[padre].dejaEstarEvaluada();
			}

		}

		aplicarElitismo(mejor_individuo);

		poblacion.evaluarPoblacion(datos, output_datos);

		mejor_individuo = poblacion.getMejorIndividuo();

		if ( mostrar_evolucion ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.getFitness() << std::endl;
		}

		generacion++;
	}

}


} // namespace algoritmos_poblaciones
