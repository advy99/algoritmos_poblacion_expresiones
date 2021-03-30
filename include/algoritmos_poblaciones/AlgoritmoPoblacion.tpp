
namespace algoritmos_poblaciones {

template <class T>
AlgoritmoPoblacion<T> :: AlgoritmoPoblacion() {

}

template <class T>
void AlgoritmoPoblacion<T> :: inicializar(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {

	// inicializamos la semilla
	Random::setSeed(seed);

	prof_expresiones = prof;
	generarPoblacion(tam_poblacion, prof, prob_var, true);

}


template <class T>
void AlgoritmoPoblacion<T> :: cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas ) {
	datos = caracteristicas;
	output_datos = etiquetas;
}

template <class T>
void AlgoritmoPoblacion<T> :: leerDatos(const std::string fichero_datos,
							const char char_comentario, const char delimitador){
	// abrimos el fichero de lectura
	auto resultado = leer_datos<double>(fichero_datos, char_comentario, delimitador);

	datos = resultado.first;
	output_datos = resultado.second;

}


template <class T>
int AlgoritmoPoblacion<T> :: getNumDatos() const {
	return datos.size();
}

template <class T>
void AlgoritmoPoblacion<T> :: generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp,
									 const double prob_var, const bool sustituir_actual) {
	if ( sustituir_actual ) {
		poblacion = Poblacion<T>(tam_poblacion, profundidad_exp, prob_var,
									 	 getNumVariables(), getMaxProfExpresiones());
	}

}



template <class T>
int AlgoritmoPoblacion<T> :: getNumVariables() const {
	return datos[0].size();
}

template <class T>
std::vector<std::vector<double> > AlgoritmoPoblacion<T> :: getDatos() const {
	return datos;
}

template <class T>
std::vector<double> AlgoritmoPoblacion<T> :: getDato(const unsigned i) const {
	return datos[i];
}

template <class T>
std::vector<double> AlgoritmoPoblacion<T> :: getOutputDatos() const {
	return output_datos;
}


template <class T>
double AlgoritmoPoblacion<T> :: getOutputDato(const unsigned indice) const {
	return output_datos[indice];
}

template <class T>
void AlgoritmoPoblacion<T> :: inicializarVacio() {
	prof_expresiones = 0;
	datos.clear();
	output_datos.clear();
}


template <class T>
Poblacion<T> AlgoritmoPoblacion<T> :: seleccionTorneo(const unsigned tam_torneo) {
	// partimos de una poblacion con el mismo tamaño que la actual
	Poblacion<T> resultado = poblacion;

	std::vector<int> ganadores_torneo;



	// escojo una nueva poblacion del mismo tamaño
	#pragma omp parallel for
	for ( unsigned i = 0; i < poblacion.getTamPoblacion(); i++) {

		std::vector<int> participantes_torneo;
		int nuevo_participante;
		int mejor_torneo;

		// generamos el inicial y lo insertamos en los generados
		mejor_torneo = Random::getInt(poblacion.getTamPoblacion());

		participantes_torneo.push_back(mejor_torneo);

		// insertamos participantes hasta llegar al tamaño indicado
		while ( tam_torneo > participantes_torneo.size()) {
			nuevo_participante = Random::getInt(poblacion.getTamPoblacion());

			auto encontrado = std::find(participantes_torneo.begin(), participantes_torneo.end(), nuevo_participante);

			// si no aparece como participante
			if ( encontrado != participantes_torneo.end() ) {
				participantes_torneo.push_back(nuevo_participante);
				// si este nuevo participante tiene mejor fitness, lo cojemos como mejor
				if ( poblacion[nuevo_participante].getFitness() < poblacion[mejor_torneo].getFitness() ) {
					mejor_torneo = nuevo_participante;
				}

			}
		}

		// el ganador del torneo i es el mejor del torneo
		#pragma omp critical
		ganadores_torneo.push_back(mejor_torneo);
	}

	// actualizamos el resultado con los ganadores del torneo
	for ( unsigned i = 0; i < poblacion.getTamPoblacion(); i++) {
		resultado[i] = poblacion[ganadores_torneo[i]];
	}

	return resultado;
}

template <class T>
T AlgoritmoPoblacion<T> :: getMejorIndividuo() const {
	return poblacion.getMejorIndividuo();
}

template <class T>
unsigned AlgoritmoPoblacion<T> :: getMaxProfExpresiones() const {
	return prof_expresiones;
}



template <class T>
void AlgoritmoPoblacion<T> :: aplicarElitismo(const T & mejor_ind_anterior) {
	// elitismo
	bool mejor_encontrado = false;
	unsigned i = 0;

	while (i < poblacion.getTamPoblacion() && !mejor_encontrado) {
		mejor_encontrado = poblacion[i] == mejor_ind_anterior;
		i++;
	}



	// si no esta el mejor, aplico elitismo
	if ( !mejor_encontrado ){
		poblacion[poblacion.getTamPoblacion() - 1] = mejor_ind_anterior;
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

} // namespace algoritmos_poblaciones
