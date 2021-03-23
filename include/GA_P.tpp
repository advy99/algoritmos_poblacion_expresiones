namespace PG_ALGS {

template <class T>
GA_P<T> :: GA_P(const unsigned long seed) {

	// inicializamos la semilla
	Random::setSeed(seed);

	this->inicializarVacio();

}

template <class T>
GA_P<T> :: GA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed, const char delimitador, const unsigned prof){

	// al principio suponemos que se ha leido mal
	bool lectura_correcta = false;

	this->inicializarVacio();

	// lemos los datos del fichero de entrada
	lectura_correcta = this->leerDatos(fichero_datos, char_comentario, delimitador);
	this->prof_expresiones = prof;


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
		this->poblacion = Poblacion<T>(tam_poblacion, profundidad_exp, prob_var,
									 	 		this->getNumVariables(), this->getMaxProfExpresiones());
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

	const int NUM_GENERACIONES = num_eval / (double) this->poblacion.getTamPoblacion();

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	this->poblacion.evaluarPoblacion(this->datos, this->output_datos);

	Poblacion<T> poblacion_antigua = this->poblacion;
	Poblacion<T> poblacion_tmp;

	Expresion_GAP hijo1, hijo2;

	bool cruce_ga;
	bool cruce_gp;

	while ( generacion < NUM_GENERACIONES) {


		// intercambio la poblacion antigua y la actual
		poblacion_tmp = poblacion_antigua;
		poblacion_antigua = this->poblacion;
		this->poblacion = poblacion_tmp;


		// seleccionamos la poblacion a cruzar
		this->poblacion = this->seleccionTorneo(tam_torneo);

		// aplicamos los operadores geneticos
		for ( unsigned i = 0; i < this->poblacion.getTamPoblacion(); i += 2){

			madre = i;
			padre = i + 1;

			hijo1 = this->poblacion[madre];
			hijo2 = this->poblacion[padre];

			modificado_hijo1 = modificado_hijo2 = false;
			cruce_ga = cruce_gp = false;

			// cruce de la parte GA
			if ( Random::getFloat() < prob_cruce_ga ) {
				// cruce del cromosoma utilizando BLX_alfa
				this->poblacion[madre].cruceBLXalfa(this->poblacion[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_ga = true;
			}

			// cruce de la parte GP
			if ( Random::getFloat() < prob_cruce_gp ) {
				// cruce de programacion genetica, se intercambian arboles

				this->poblacion[madre].cruceArbol(this->poblacion[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_gp = true;
			}

			if ( cruce_gp || cruce_ga ) {
				// si hay algun tipo de cruce
				if ( !cruce_gp ) {
					// no se ha cruzado el arbol
					hijo1.asignarArbol(this->poblacion[madre].getArbol(), this->poblacion[madre].getLongitudArbol());
					hijo2.asignarArbol(this->poblacion[padre].getArbol(), this->poblacion[padre].getLongitudArbol());
				} else {
					// no se ha cruzado el cromosoma
					hijo1.asignarCromosoma(this->poblacion[madre].getCromosoma(), this->poblacion[madre].getLongitudCromosoma());
					hijo2.asignarCromosoma(this->poblacion[padre].getCromosoma(), this->poblacion[padre].getLongitudCromosoma());

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
				hijo1.mutarGP(this->getNumVariables());
				modificado_hijo1 = true;
			}

			if ( Random::getFloat() < prob_mutacion_gp ) {
				// mutacion GP en el segundo hijo
				hijo2.mutarGP(this->getNumVariables());
				modificado_hijo2 = true;
			}

			if ( modificado_hijo1 ) {
				this->poblacion[madre] = hijo1;
				this->poblacion[madre].dejaEstarEvaluada();
			}

			if ( modificado_hijo2) {
				this->poblacion[padre] = hijo2;
				this->poblacion[padre].dejaEstarEvaluada();
			}

		}

		// elitismo
		bool mejor_encontrado = false;
		unsigned i = 0;

		while (i < this->poblacion.getTamPoblacion() && !mejor_encontrado) {
			mejor_encontrado = this->poblacion[i].totalmenteIguales(poblacion_antigua.getMejorIndividuo());
			i++;
		}



		// si no esta el mejor, aplico elitismo
		if ( !mejor_encontrado ){
			this->poblacion[this->poblacion.getTamPoblacion() - 1] = poblacion_antigua.getMejorIndividuo();
		}

		// evaluamos
		this->poblacion.evaluarPoblacion(this->datos, this->output_datos);




		if ( mostrar_evolucion ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << this->poblacion.getMejorIndividuo().getFitness() << std::endl;
		}

		generacion++;
	}

}


} // namespace PG_ALGS
