
namespace algoritmos_poblaciones {

template <class T>
AlgoritmoPoblacion<T> :: AlgoritmoPoblacion() {

}

template <class T>
void AlgoritmoPoblacion<T> :: inicializar(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {

	inicializarVacio();

	// inicializamos la semilla
	Random::setSeed(seed);

	prof_expresiones_ = prof;
	generarPoblacion(tam_poblacion, prof, prob_var, true);

}


template <class T>
void AlgoritmoPoblacion<T> :: cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas ) {
	datos_ = caracteristicas;
	output_datos_ = etiquetas;
}

template <class T>
void AlgoritmoPoblacion<T> :: leerDatos(const std::string fichero_datos,
							const char char_comentario, const char delimitador){
	// abrimos el fichero de lectura
	auto resultado = leer_datos<double>(fichero_datos, char_comentario, delimitador);

	datos_ = resultado.first;
	output_datos_ = resultado.second;

}


template <class T>
int AlgoritmoPoblacion<T> :: getNumDatos() const {
	return datos_.size();
}

template <class T>
void AlgoritmoPoblacion<T> :: generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp,
									 const double prob_var, const bool sustituir_actual) {
	if ( sustituir_actual ) {
		poblacion_ = Poblacion<T>(tam_poblacion, profundidad_exp, prob_var,
									 	 getNumVariables(), getMaxProfExpresiones());
	}

}



template <class T>
int AlgoritmoPoblacion<T> :: getNumVariables() const {
	return datos_[0].size();
}

template <class T>
std::vector<std::vector<double> > AlgoritmoPoblacion<T> :: getDatos() const {
	return datos_;
}

template <class T>
std::vector<double> AlgoritmoPoblacion<T> :: getDato(const unsigned i) const {
	return datos_[i];
}

template <class T>
std::vector<double> AlgoritmoPoblacion<T> :: getOutputDatos() const {
	return output_datos_;
}


template <class T>
double AlgoritmoPoblacion<T> :: getOutputDato(const unsigned indice) const {
	return output_datos_[indice];
}

template <class T>
void AlgoritmoPoblacion<T> :: inicializarVacio() {
	prof_expresiones_ = 0;
	datos_.clear();
	output_datos_.clear();
}


template <class T>
Poblacion<T> AlgoritmoPoblacion<T> :: seleccionTorneo(const unsigned tam_torneo) {
	// partimos de una poblacion con el mismo tamaño que la actual
	Poblacion<T> resultado = poblacion_;

	std::vector<int> ganadores_torneo;



	// escojo una nueva poblacion del mismo tamaño
	for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i++) {

		std::vector<int> participantes_torneo;
		int nuevo_participante;
		int mejor_torneo;

		// generamos el inicial y lo insertamos en los generados
		mejor_torneo = Random::getInt(poblacion_.getTamPoblacion());

		participantes_torneo.push_back(mejor_torneo);

		// insertamos participantes hasta llegar al tamaño indicado
		while ( tam_torneo > participantes_torneo.size()) {
			nuevo_participante = Random::getInt(poblacion_.getTamPoblacion());

			auto encontrado = std::find(participantes_torneo.begin(), participantes_torneo.end(), nuevo_participante);

			// si no aparece como participante
			if ( encontrado != participantes_torneo.end() ) {
				participantes_torneo.push_back(nuevo_participante);
				// si este nuevo participante tiene mejor fitness, lo cojemos como mejor
				if ( poblacion_[nuevo_participante].getFitness() < poblacion_[mejor_torneo].getFitness() ) {
					mejor_torneo = nuevo_participante;
				}

			}
		}

		// el ganador del torneo i es el mejor del torneo
		ganadores_torneo.push_back(mejor_torneo);
	}

	// actualizamos el resultado con los ganadores del torneo
	for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i++) {
		resultado[i] = poblacion_[ganadores_torneo[i]];
	}

	return resultado;
}

template <class T>
T AlgoritmoPoblacion<T> :: getMejorIndividuo() const {
	return poblacion_.getMejorIndividuo();
}

template <class T>
unsigned AlgoritmoPoblacion<T> :: getMaxProfExpresiones() const {
	return prof_expresiones_;
}



template <class T>
void AlgoritmoPoblacion<T> :: aplicarElitismo(const T & mejor_ind_anterior) {
	// elitismo
	bool mejor_encontrado = false;
	unsigned i = 0;

	while (i < poblacion_.getTamPoblacion() && !mejor_encontrado) {
		mejor_encontrado = poblacion_[i] == mejor_ind_anterior;
		i++;
	}

	// si no esta el mejor, aplico elitismo
	if ( !mejor_encontrado ){
		poblacion_[poblacion_.getTamPoblacion() - 1] = mejor_ind_anterior;
	}

}

template <class T>
std::pair<bool, bool> AlgoritmoPoblacion<T> :: aplicarMutacionesGP(T & hijo1, T & hijo2, const double prob_mutacion) {
	std::pair<bool, bool> resultado = std::make_pair(false, false);

	if ( Random::getFloat() < prob_mutacion ) {
		// mutacion GP en el primer hijo
		hijo1.mutarGP(getNumVariables());
		resultado.first = true;
	}

	if ( Random::getFloat() < prob_mutacion ) {
		// mutacion GP en el segundo hijo
		hijo2.mutarGP(getNumVariables());
		resultado.second = true;
	}

	return resultado;
}


template <class T>
double AlgoritmoPoblacion<T> :: predecir(const std::vector<double> & dato) const {
	double resultado = poblacion_.getMejorIndividuo().evaluarDato(dato);

	return resultado;
}

template <class T>
std::vector<double> AlgoritmoPoblacion<T> :: predecir(const std::vector<std::vector<double> > & datos) const {

	std::vector<double> resultado;

	resultado.resize(datos.size());

	#pragma omp parallel for
	for ( unsigned i = 0; i < datos.size(); i++) {
		resultado[i] = predecir(datos[i]);
	}

	return resultado;
}

template <class T>
double AlgoritmoPoblacion<T> :: ajustar_k_cross_validation(const unsigned numero_val_cruzada,
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



} // namespace algoritmos_poblaciones
