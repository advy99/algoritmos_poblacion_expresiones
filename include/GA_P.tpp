namespace PG_ALGS {

template <class T>
GA_P<T> :: GA_P(const unsigned long seed) {

	// inicializamos la semilla
	Random::setSeed(seed);

	inicializarVacio();

}

template <class T>
GA_P<T> :: GA_P(const std::string fichero_datos, const char char_comentario,
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
		generarPoblacion(tam_poblacion, prof, prob_var, true);

	} else {
		// si no, mostramos un error
		std::cerr << "Error leyendo los datos de " << fichero_datos << std::endl;
	}

}


template <class T>
void GA_P<T> :: generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp,
									 const double prob_var, const bool sustituir_actual) {
	if ( sustituir_actual ) {
		poblacion = Poblacion<T>(tam_poblacion, profundidad_exp, prob_var,
									 	 getNumVariables(), getMaxProfExpresiones());
	}

}

template <class T>
GA_P<T> :: ~GA_P(){
}

template <class T>
void GA_P<T> :: ajustar(const int num_eval, const double prob_cruce_gp,
							const double prob_cruce_ga, const double prob_mutacion_gp,
							const double prob_mutacion_ga, const int tam_torneo,
							const bool mostrar_evolucion) {

	const int NUM_GENERACIONES = num_eval / (double) poblacion.getTamPoblacion();

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion.evaluarPoblacion(datos, output_datos);

	Poblacion<T> poblacion_antigua = poblacion;
	Poblacion<T> poblacion_tmp;

	Expresion_GAP hijo1, hijo2;

	bool cruce_ga;
	bool cruce_gp;

	while ( generacion < NUM_GENERACIONES) {


		// intercambio la poblacion antigua y la actual
		poblacion_tmp = poblacion_antigua;
		poblacion_antigua = poblacion;
		poblacion = poblacion_tmp;


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
				// mutacion GA en el primer hijo
				hijo1.mutarGA(generacion, NUM_GENERACIONES);
				modificado_hijo1 = true;
			}

			if ( Random::getFloat() < prob_mutacion_ga ) {
				// mutacion GA en el segundo hijo
				hijo2.mutarGA(generacion, NUM_GENERACIONES);
				modificado_hijo2 = true;
			}

			if ( Random::getFloat() < prob_mutacion_gp ) {
				// mutacion GP en el primer hijo
				hijo1.mutarGP(getNumVariables());
				modificado_hijo1 = true;
			}

			if ( Random::getFloat() < prob_mutacion_gp ) {
				// mutacion GP en el segundo hijo
				hijo2.mutarGP(getNumVariables());
				modificado_hijo2 = true;
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
		bool mejor_encontrado = false;
		unsigned i = 0;

		while (i < poblacion.getTamPoblacion() && !mejor_encontrado) {
			mejor_encontrado = poblacion[i].totalmenteIguales(poblacion_antigua.getMejorIndividuo());
			i++;
		}



		// si no esta el mejor, aplico elitismo
		if ( !mejor_encontrado ){
			poblacion[poblacion.getTamPoblacion() - 1] = poblacion_antigua.getMejorIndividuo();
		}

		// evaluamos
		poblacion.evaluarPoblacion(datos, output_datos);




		if ( mostrar_evolucion ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << poblacion.getMejorIndividuo().getFitness() << std::endl;
		}

		generacion++;
	}

}


} // namespace PG_ALGS
