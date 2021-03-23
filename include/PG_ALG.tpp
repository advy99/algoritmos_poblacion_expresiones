
namespace PG_ALGS {

template <class T>
PG_ALG<T> :: PG_ALG() {
	
}

template <class T>
void PG_ALG<T> :: cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas ) {
	datos = caracteristicas;
	output_datos = etiquetas;
}

template <class T>
bool PG_ALG<T> :: leerDatos(const std::string fichero_datos,
							const char char_comentario, const char delimitador){
	// abrimos el fichero de lectura
	std::ifstream file(fichero_datos);
	bool resultado = true;

	// mostramos un error si no podemos abrirlo
	if (!file){
		std::cerr << "Error al abrir " << fichero_datos << std::endl;
		resultado = false;

	} else {
		// leemos una linea
		std::string linea;
		std::stringstream ss;

		std::getline(file, linea);

		// mientras no encuentre el EOF
		while (!file.eof()){
			// si hemos leido una linea y no es un comentario, la procesamos
			if (linea.size() > 0 && linea[0] != char_comentario &&
				 !isblank(linea[0]) ) {
				// leemos por linea
				std::vector<double> datos_linea;
				ss.str(linea);

				std::string str_valor;

				std::getline(ss, str_valor, delimitador);

				// mientras queden valores en la linea
				while (!ss.eof()){
					// los metemos en ese dato
					datos_linea.push_back(strtod(str_valor.c_str(), nullptr));
					std::getline(ss, str_valor, delimitador);

				}

				// el ultimo dato no tiene separador, lo incluimos
				output_datos.push_back(strtod(str_valor.c_str(), nullptr));

				// introducimos el dato en la matriz final de datos
 				datos.push_back(datos_linea);


				// reseteamos el lector de strgin para leer la siguiente linea
				ss.str("");
				ss.clear();

			}

			std::getline(file, linea);
		}



	}


	return resultado;
}


template <class T>
int PG_ALG<T> :: getNumDatos() const {
	return datos.size();
}

template <class T>
void PG_ALG<T> :: generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp,
									 const double prob_var, const bool sustituir_actual) {
	if ( sustituir_actual ) {
		poblacion = Poblacion<T>(tam_poblacion, profundidad_exp, prob_var,
									 	 getNumVariables(), getMaxProfExpresiones());
	}

}



template <class T>
int PG_ALG<T> :: getNumVariables() const {
	return datos[0].size();
}

template <class T>
std::vector<std::vector<double> > PG_ALG<T> :: getDatos() const {
	return datos;
}

template <class T>
std::vector<double> PG_ALG<T> :: getDato(const unsigned i) const {
	return datos[i];
}

template <class T>
std::vector<double> PG_ALG<T> :: getOutputDatos() const {
	return output_datos;
}


template <class T>
double PG_ALG<T> :: getOutputDato(const unsigned indice) const {
	return output_datos[indice];
}

template <class T>
void PG_ALG<T> :: inicializarVacio() {
	prof_expresiones = 0;
	datos.clear();
	output_datos.clear();
}


template <class T>
Poblacion<T> PG_ALG<T> :: seleccionTorneo(const unsigned tam_torneo) {
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
T PG_ALG<T> :: getMejorIndividuo() const {
	return poblacion.getMejorIndividuo();
}

template <class T>
unsigned PG_ALG<T> :: getMaxProfExpresiones() const {
	return prof_expresiones;
}



template <class T>
void PG_ALG<T> :: aplicarElitismo(const Poblacion<T> & poblacion_antigua) {
	// elitismo
	bool mejor_encontrado = false;
	unsigned i = 0;

	while (i < poblacion.getTamPoblacion() && !mejor_encontrado) {
		mejor_encontrado = poblacion[i] == poblacion_antigua.getMejorIndividuo();
		i++;
	}



	// si no esta el mejor, aplico elitismo
	if ( !mejor_encontrado ){
		poblacion[poblacion.getTamPoblacion() - 1] = poblacion_antigua.getMejorIndividuo();
	}

}

template <class T>
std::pair<bool, bool> PG_ALG<T> :: aplicarMutacionesGP(T & hijo1, T & hijo2, const double prob_mutacion) {
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

} // namespace PG_ALGS
