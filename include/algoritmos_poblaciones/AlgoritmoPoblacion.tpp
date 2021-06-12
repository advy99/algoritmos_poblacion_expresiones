
namespace algoritmos_poblacion_expresiones {

template <class T>
AlgoritmoPoblacion<T> :: AlgoritmoPoblacion() {

}

template <class T>
void AlgoritmoPoblacion<T> :: inicializar(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {

	// inicializamos la semilla
	Random::setSeed(seed);

	prof_expresiones_ = prof;
	probabilidad_variable_ = prob_var;
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
	Poblacion<T> resultado;

	// escojo una nueva poblacion del mismo tamaño
	for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i++) {

		int mejor_torneo = 0;

		// generamos el inicial y lo insertamos en los generados
		mejor_torneo = Random::getInt(poblacion_.getTamPoblacion());

		std::vector<int> participantes_torneo;
		participantes_torneo.resize(poblacion_.getTamPoblacion());

		for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i++ ) {
			participantes_torneo[i] = i;
		}

		std::shuffle(participantes_torneo.begin(), participantes_torneo.end(), Random::getGenerador());

		mejor_torneo = participantes_torneo[0];

		// solo miro hasta tam_torneo, que son los escogidos aleatoriamente
		for ( unsigned i = 1; i < tam_torneo; i++) {
			if ( poblacion_[mejor_torneo].getFitness() > poblacion_[participantes_torneo[i]].getFitness()) {
				mejor_torneo = participantes_torneo[i];
			}
		}


		// el ganador del torneo i es el mejor del torneo
		resultado.insertar(poblacion_[mejor_torneo]);
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

		if (poblacion_.getMejorIndividuo().getFitness() > mejor_ind_anterior.getFitness()) {
			poblacion_.setMejorIndividuo(poblacion_.getTamPoblacion() - 1);
		}

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
std::pair<T, std::vector<std::vector<double> > > AlgoritmoPoblacion<T> :: ajustar_k_cross_validation(const unsigned numero_val_cruzada,
				 									 const Parametros & parametros) {

	const std::vector<std::vector<double> > datos_originales = datos_;
	const std::vector<double> etiquetas_originales = output_datos_;

	auto resultado_datos_aleatorios = reordenar_datos_aleatorio(datos_, output_datos_);

	const int NUM_DATOS_TEST_ITERACION = datos_.size() / numero_val_cruzada;

	std::vector<std::vector<double >> errores;
	errores.resize(parametros.getNumFuncionesError() + 1);

	for (unsigned i = 0; i < errores.size(); i++){
		errores[i].resize(numero_val_cruzada);
	}

	double error_mejor = std::numeric_limits<double>::infinity();
	T mejor_expresion;

	// para cada iteracion de la validación cruzada;
	for ( unsigned i = 0; i < numero_val_cruzada; i++) {
		// tenemos que hacer la separacion en train/test para esta iteracion
		auto train_test_separado = separar_train_test<double>(resultado_datos_aleatorios.first,
																				resultado_datos_aleatorios.second,
																				1.0/numero_val_cruzada,
																				NUM_DATOS_TEST_ITERACION * i);

		cargarDatos(train_test_separado.first.first, train_test_separado.first.second);

		// generamos una nueva población en cada iteración, para asegurarnos que cada fold es independiente
		generarPoblacion(poblacion_.getTamPoblacion(), prof_expresiones_, probabilidad_variable_, true);

		// ajustamos para estos nuevos valores
		ajustar(parametros);

		// predecimos test para mirar el error
		auto predicciones = predecir(train_test_separado.second.first);

		// rellenamos el error de la función de evaluación con la que entrenamos
		errores[0][i] = parametros.getFuncionEvaluacion()(predicciones, train_test_separado.second.second);

		// calculamos todos los otros errores
		for (unsigned i = 0; i < parametros.getNumFuncionesError(); i++) {
			errores[i + 1] = parametros.getFuncionError(i)(predicciones, train_test_separado.second.second);
		}

		if (errores[0][i] < error_mejor) {
			mejor_expresion = getMejorIndividuo();
		}

	}

	// reestablecer datos originales
	cargarDatos(datos_originales, etiquetas_originales);

	return std::make_pair(mejor_expresion, errores);

}



} // namespace algoritmos_poblacion_expresiones
