#include "algoritmos_poblaciones/AlgoritmoPG.hpp"

namespace algoritmos_poblaciones {



AlgoritmoPG :: AlgoritmoPG(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
									const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var){
	cargarDatos(datos, etiquetas);
	inicializar(seed, tam_poblacion, prof, prob_var);

}



AlgoritmoPG :: AlgoritmoPG(const std::string fichero_datos, const char char_comentario,
		  const unsigned tam_poblacion, const double prob_var,
		  const unsigned long seed,
		  const char delimitador, const unsigned prof){

	inicializarVacio();

	leerDatos(fichero_datos, char_comentario, delimitador);
	prof_expresiones_ = prof;

	Random::setSeed(seed);

	generarPoblacion(tam_poblacion, prof, prob_var, true);

}


AlgoritmoPG :: ~AlgoritmoPG() {

}


double AlgoritmoPG :: ajustar(const unsigned numero_val_cruzada,
				 						const Parametros & parametros) {

	const std::vector<std::vector<double> > datos_originales = datos_;
	const std::vector<double> etiquetas_originales = output_datos_;

	auto resultado_datos_aleatorios = reordenar_datos_aleatorio(datos_, output_datos_);

	const int NUM_DATOS_TEST_ITERACION = datos_.size() / numero_val_cruzada;

	double media_error = 0.0;

	// para cada iteracion de la validación cruzada;
	for ( unsigned i = 0; i < numero_val_cruzada; i++) {
		// tenemos que hacer la separacion en train/test para esta iteracion
		auto train_test_separado = separar_train_test<double>(resultado_datos_aleatorios.first,
																				resultado_datos_aleatorios.second,
																				1.0/numero_val_cruzada,
																				NUM_DATOS_TEST_ITERACION * i);

		cargarDatos(train_test_separado.first.first, train_test_separado.first.second);

		// ajustamos para estos nuevos valores
		ajustar(parametros);

		// predecimos test para mirar el error
		auto predicciones = predecir(train_test_separado.second.first);

		media_error += raiz_error_cuadratico_medio(predicciones, train_test_separado.second.second);

	}

	media_error /= numero_val_cruzada;

	// reestablecer datos originales
	cargarDatos(datos_originales, etiquetas_originales);

	return media_error;

}

void AlgoritmoPG :: ajustar(const Parametros & parametros) {

	const int NUM_GENERACIONES = parametros.getNumeroEvaluaciones() / static_cast<double>(poblacion_.getTamPoblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion_.evaluarPoblacion(datos_, output_datos_);

	Expresion mejor_individuo = poblacion_.getMejorIndividuo();

	Expresion hijo1, hijo2;

	while ( generacion < NUM_GENERACIONES) {

		// seleccionamos la poblacion a cruzar
		poblacion_ = seleccionTorneo(parametros.getTamanioTorneo());

		// aplicamos los operadores geneticos
		for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i += 2){

			madre = i;
			padre = i + 1;

			hijo1 = poblacion_[madre];
			hijo2 = poblacion_[padre];

			modificado_hijo1 = modificado_hijo2 = false;

			// cruce de la parte GP
			if ( Random::getFloat() < parametros.getProbabilidadCruceGP() ) {
				// cruce de programacion genetica, se intercambian arboles

				poblacion_[madre].cruceArbol(poblacion_[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
			}

			// si no hay cruce, los hijos ya estaban con el valor de los padres

			auto resultado_mut_gp = aplicarMutacionesGP(hijo1, hijo2, parametros.getProbabilidadMutacionGP());

			modificado_hijo1 = modificado_hijo1 || resultado_mut_gp.first;
			modificado_hijo2 = modificado_hijo2 || resultado_mut_gp.second;

			if ( modificado_hijo1 ) {
				poblacion_[madre] = hijo1;
				poblacion_[madre].dejaEstarEvaluada();
			}

			if ( modificado_hijo2) {
				poblacion_[padre] = hijo2;
				poblacion_[padre].dejaEstarEvaluada();
			}

		}


		aplicarElitismo(mejor_individuo);


		// evaluamos
		poblacion_.evaluarPoblacion(datos_, output_datos_);

		mejor_individuo = poblacion_.getMejorIndividuo();

		if ( parametros.getMostrarEvaluacion() ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.getFitness() << std::endl;
		}

		generacion++;
	}

}


}
