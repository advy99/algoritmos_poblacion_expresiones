
namespace algoritmos_poblacion_expresiones {

template <class AlgType, class DataType, class ClassType>
AlgoritmoPoblacion<AlgType, DataType, ClassType> :: AlgoritmoPoblacion() {

}

template <class AlgType, class DataType, class ClassType>
void AlgoritmoPoblacion<AlgType, DataType, ClassType> :: inicializar(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {

	// inicializamos la semilla
	Random::set_seed(seed);

	prof_expresiones_ = prof;
	probabilidad_variable_ = prob_var;
	generar_poblacion(tam_poblacion, prof, prob_var, true);

}


template <class AlgType, class DataType, class ClassType>
void AlgoritmoPoblacion<AlgType, DataType, ClassType> :: cargar_datos(const std::vector< std::vector<DataType> > & caracteristicas, const std::vector<ClassType> & etiquetas ) {
	datos_ = caracteristicas;
	output_datos_ = etiquetas;
}

template <class AlgType, class DataType, class ClassType>
void AlgoritmoPoblacion<AlgType, DataType, ClassType> :: leer_datos(const std::string fichero_datos,
							const char char_comentario, const char delimitador){
	// abrimos el fichero de lectura
	auto resultado = preprocesado::leer_datos<DataType, ClassType>(fichero_datos, char_comentario, delimitador);

	datos_ = resultado.first;
	output_datos_ = resultado.second;

}


template <class AlgType, class DataType, class ClassType>
int AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_num_datos() const {
	return datos_.size();
}

template <class AlgType, class DataType, class ClassType>
void AlgoritmoPoblacion<AlgType, DataType, ClassType> :: generar_poblacion(const unsigned tam_poblacion, const unsigned profundidad_exp,
									 const double prob_var, const bool sustituir_actual) {
	if ( sustituir_actual ) {
		poblacion_ = Poblacion<AlgType>(tam_poblacion, profundidad_exp, prob_var,
									 	 get_num_variables(), get_max_prof_expresiones());
	}


}



template <class AlgType, class DataType, class ClassType>
int AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_num_variables() const {
	return datos_[0].size();
}

template <class AlgType, class DataType, class ClassType>
std::vector<std::vector<DataType> > AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_datos() const {
	return datos_;
}

template <class AlgType, class DataType, class ClassType>
std::vector<DataType> AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_dato(const unsigned i) const {
	return datos_[i];
}

template <class AlgType, class DataType, class ClassType>
std::vector<ClassType> AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_output_datos() const {
	return output_datos_;
}


template <class AlgType, class DataType, class ClassType>
ClassType AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_output_dato(const unsigned indice) const {
	return output_datos_[indice];
}

template <class AlgType, class DataType, class ClassType>
void AlgoritmoPoblacion<AlgType, DataType, ClassType> :: inicializar_vacio() {
	prof_expresiones_ = 0;
	datos_.clear();
	output_datos_.clear();
}


template <class AlgType, class DataType, class ClassType>
Poblacion<AlgType> AlgoritmoPoblacion<AlgType, DataType, ClassType> :: seleccion_torneo(const unsigned tam_torneo) const {
	// partimos de una poblacion con el mismo tamaño que la actual
	Poblacion<AlgType> resultado;

	std::vector<int> participantes_torneo;
	participantes_torneo.resize(poblacion_.get_tam_poblacion());

	for ( unsigned i = 0; i < poblacion_.get_tam_poblacion(); i++ ) {
		participantes_torneo[i] = i;
	}

	int mejor_torneo = 0;

	// escojo una nueva poblacion del mismo tamaño
	for ( unsigned i = 0; i < poblacion_.get_tam_poblacion(); i++) {


		std::shuffle(participantes_torneo.begin(), participantes_torneo.end(), Random::get_generator());

		mejor_torneo = participantes_torneo[0];

		// solo miro hasta tam_torneo, que son los escogidos aleatoriamente
		for ( unsigned i = 1; i < tam_torneo; i++) {
			if ( poblacion_[mejor_torneo].get_fitness() > poblacion_[participantes_torneo[i]].get_fitness()) {
				mejor_torneo = participantes_torneo[i];
			}
		}


		// el ganador del torneo i es el mejor del torneo
		resultado.insertar(poblacion_[mejor_torneo]);
	}

	return resultado;
}

template <class AlgType, class DataType, class ClassType>
AlgType AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_mejor_individuo() const {
	return poblacion_.get_mejor_individuo();
}

template <class AlgType, class DataType, class ClassType>
unsigned AlgoritmoPoblacion<AlgType, DataType, ClassType> :: get_max_prof_expresiones() const {
	return prof_expresiones_;
}



template <class AlgType, class DataType, class ClassType>
void AlgoritmoPoblacion<AlgType, DataType, ClassType> :: aplicar_elitismo(const AlgType & mejor_ind_anterior) {
	// elitismo
	bool mejor_encontrado = false;
	unsigned i = 0;

	while (i < poblacion_.get_tam_poblacion() && !mejor_encontrado) {
		mejor_encontrado = poblacion_[i] == mejor_ind_anterior;
		i++;
	}

	// si no esta el mejor, aplico elitismo
	if ( !mejor_encontrado ){
		poblacion_[poblacion_.get_tam_poblacion() - 1] = mejor_ind_anterior;

		if (poblacion_.get_mejor_individuo().get_fitness() > mejor_ind_anterior.get_fitness()) {
			poblacion_.set_mejor_individuo(poblacion_.get_tam_poblacion() - 1);
		}

	}

}

template <class AlgType, class DataType, class ClassType>
std::pair<bool, bool> AlgoritmoPoblacion<AlgType, DataType, ClassType> :: aplicar_mutaciones_GP(AlgType & hijo1, AlgType & hijo2, const double prob_mutacion) {
	std::pair<bool, bool> resultado = std::make_pair(false, false);

	if ( Random::next_double() < prob_mutacion ) {
		// mutacion GP en el primer hijo
		hijo1.mutar_GP(get_num_variables());
		resultado.first = true;
	}

	if ( Random::next_double() < prob_mutacion ) {
		// mutacion GP en el segundo hijo
		hijo2.mutar_GP(get_num_variables());
		resultado.second = true;
	}

	return resultado;
}

// TODO: Lo mismo esta función de predecir varia dependiendo del algoritmo y
// hay que revisarla
template <class AlgType, class DataType, class ClassType>
ClassType AlgoritmoPoblacion<AlgType, DataType, ClassType> :: predecir(const std::vector<DataType> & dato) const {
	ClassType resultado = poblacion_.get_mejor_individuo().evaluar_dato(dato);

	return resultado;
}

template <class AlgType, class DataType, class ClassType>
std::vector<ClassType> AlgoritmoPoblacion<AlgType, DataType, ClassType> :: predecir(const std::vector<std::vector<DataType> > & datos) const {

	std::vector<ClassType> resultado;

	resultado.resize(datos.size());

	#pragma omp parallel for
	for ( unsigned i = 0; i < datos.size(); i++) {
		resultado[i] = predecir(datos[i]);
	}

	return resultado;
}

template <class AlgType, class DataType, class ClassType>
std::pair<AlgType, std::vector<std::vector<double> > > AlgoritmoPoblacion<AlgType, DataType, ClassType> :: ajustar_k_cross_validation(const unsigned numero_val_cruzada,
				 									 const Parametros & parametros) {

	const std::vector<std::vector<DataType> > datos_originales = datos_;
	const std::vector<ClassType> etiquetas_originales = output_datos_;

	auto resultado_datos_aleatorios = preprocesado::reordenar_datos_aleatorio(datos_, output_datos_);

	const int NUM_DATOS_TEST_ITERACION = datos_.size() / numero_val_cruzada;

	std::vector<std::vector<double >> errores;
	errores.resize(parametros.get_num_funciones_error() + 1);

	for (unsigned i = 0; i < errores.size(); i++){
		errores[i].resize(numero_val_cruzada);
	}

	double error_mejor = std::numeric_limits<double>::infinity();
	AlgType mejor_expresion;

	// para cada iteracion de la validación cruzada;
	for ( unsigned i = 0; i < numero_val_cruzada; i++) {
		// tenemos que hacer la separacion en train/test para esta iteracion
		auto train_test_separado = preprocesado::separar_train_test<DataType, ClassType>(resultado_datos_aleatorios.first,
																				resultado_datos_aleatorios.second,
																				1.0/numero_val_cruzada,
																				NUM_DATOS_TEST_ITERACION * i);

		cargar_datos(train_test_separado.first.first, train_test_separado.first.second);

		// generamos una nueva población en cada iteración, para asegurarnos que cada fold es independiente
		generar_poblacion(poblacion_.get_tam_poblacion(), prof_expresiones_, probabilidad_variable_, true);

		// ajustamos para estos nuevos valores
		ajustar(parametros);

		// predecimos test para mirar el error
		auto predicciones = predecir(train_test_separado.second.first);

		// rellenamos el error de la función de evaluación con la que entrenamos
		errores[0][i] = parametros.get_funcion_evaluacion()(predicciones, train_test_separado.second.second);

		// calculamos todos los otros errores
		for (unsigned j = 0; j < parametros.get_num_funciones_error(); j++) {
			errores[j + 1][i] = parametros.get_funcion_error(j)(predicciones, train_test_separado.second.second);
		}

		if (errores[0][i] < error_mejor) {
			mejor_expresion = get_mejor_individuo();
		}

	}

	// reestablecer datos originales
	cargar_datos(datos_originales, etiquetas_originales);

	return std::make_pair(mejor_expresion, errores);

}



} // namespace algoritmos_poblacion_expresiones
