
namespace PG_ALGS {

template <class T>
PG<T> :: PG(const unsigned long seed) {
	Random::setSeed(seed);

	inicializarVacio();
}

template <class T>
PG<T> :: PG(const std::string fichero_datos, const char char_comentario,
		  const unsigned tam_poblacion, const double prob_var,
		  const unsigned long seed,
		  const char delimitador, const unsigned prof){

	bool lectura_correcta = false;

	inicializarVacio();

	lectura_correcta = leerDatos(fichero_datos, char_comentario, delimitador);
	prof_expresiones = prof;

	Random::setSeed(seed);

	if (lectura_correcta) {
		generarPoblacion(tam_poblacion, prof, prob_var, true);
	} else {
		// si no, mostramos un error
		std::cerr << "Error leyendo los datos de " << fichero_datos << std::endl;
	}

}

template <class T>
PG<T> :: ~PG() {

}

template <class T>
void PG<T> :: ajustar(const int num_eval, const double prob_cruce,
							const double prob_mutacion,
							const int tam_torneo,
							const bool mostrar_evolucion) {

	const int NUM_GENERACIONES = num_eval / static_cast<double>(poblacion.getTamPoblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion.evaluarPoblacion(datos, output_datos);

	Poblacion<T> poblacion_antigua = poblacion;
	Poblacion<T> poblacion_tmp;

	Expresion hijo1, hijo2;

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

			// cruce de la parte GP
			if ( Random::getFloat() < prob_cruce ) {
				// cruce de programacion genetica, se intercambian arboles

				poblacion[madre].cruceArbol(poblacion[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
			}

			// si no hay cruce, los hijos ya estaban con el valor de los padres

			auto resultado_mut_gp = aplicarMutacionesGP(hijo1, hijo2, prob_mutacion);

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


		aplicarElitismo(poblacion_antigua);


		// evaluamos
		poblacion.evaluarPoblacion(datos, output_datos);




		if ( mostrar_evolucion ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << poblacion.getMejorIndividuo().getFitness() << std::endl;
		}

		generacion++;
	}

}


}
