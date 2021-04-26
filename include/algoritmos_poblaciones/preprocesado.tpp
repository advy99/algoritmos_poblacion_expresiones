namespace algoritmos_poblacion_expresiones {


template <class T>
std::pair<matriz<T>, std::vector<T> > leer_datos(const std::string & fichero_datos,
												const char char_comentario, const char delimitador){
	// abrimos el fichero de lectura
	std::ifstream file(fichero_datos);

	matriz<T> datos;
	std::vector<T> output_datos;

	// mostramos un error si no podemos abrirlo
	if (!file){
		std::cerr << "Error al abrir " << fichero_datos << std::endl;
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
				std::vector<T> datos_linea;
				ss.str(linea);

				std::string str_valor;

				std::getline(ss, str_valor, delimitador);

				// mientras queden valores en la linea
				while (!ss.eof()){

					T dato_a_insertar;

					if constexpr ( std::is_same<T, double>::value ) {
						dato_a_insertar = strtod(str_valor.c_str(), nullptr);
					} else {
						dato_a_insertar = str_valor;
					}

					// los metemos en ese dato
					datos_linea.push_back(dato_a_insertar);
					std::getline(ss, str_valor, delimitador);

				}

				T dato_a_insertar;

				if constexpr ( std::is_same<T, double>::value ) {
					dato_a_insertar = strtod(str_valor.c_str(), nullptr);
				} else {
					dato_a_insertar = str_valor;
				}

				// el ultimo dato no tiene separador, lo incluimos
				output_datos.push_back(dato_a_insertar);

				// introducimos el dato en la matriz final de datos
 				datos.push_back(datos_linea);


				// reseteamos el lector de strgin para leer la siguiente linea
				ss.str("");
				ss.clear();

			}

			std::getline(file, linea);
		}



	}


	return std::make_pair(datos, output_datos);
}


template <class T>
std::pair<std::pair<matriz<T>, std::vector<T> >, std::pair<matriz<T>, std::vector<T> > >
	separar_train_test(matriz<T> datos, std::vector<T> etiquetas,
							 const double PORCENTAJE_TEST, const int COMIENZO) {


	matriz<T> datos_test;
	std::vector<T> etiquetas_test;

	const unsigned NUM_DATOS_TEST = datos.size() * PORCENTAJE_TEST;

	datos_test.resize(NUM_DATOS_TEST);
	etiquetas_test.resize(NUM_DATOS_TEST);

	bool aleatorio = COMIENZO == -1;
	int indice = COMIENZO;

	for ( unsigned i = 0; i < NUM_DATOS_TEST; i++) {

		if (aleatorio ) {
			indice = Random::getInt(0, datos.size());
		}

		datos_test[i] = datos[indice];
		etiquetas_test[i] = etiquetas[indice];

		auto it_datos = datos.begin() + indice;
		auto it_etiquetas = etiquetas.begin() + indice;

		datos.erase(it_datos);
		etiquetas.erase(it_etiquetas);

	}

	return std::make_pair(std::make_pair(datos, etiquetas), std::make_pair(datos_test, etiquetas_test));

}

template <class T>
void escribir_datos(const std::string & salida, const matriz<T> & datos, const std::vector<T> & etiquetas, const char DELIMITADOR) {
	std::ofstream salida_datos(salida);

	for ( unsigned i = 0; i < datos.size(); i++) {
		for ( unsigned j = 0; j < datos[i].size(); j++) {
			salida_datos << datos[i][j] << DELIMITADOR;
		}

		salida_datos << etiquetas[i] << std::endl;
	}

}



template <class T>
std::pair<matriz<T>, std::vector<T> > reordenar_datos_aleatorio (matriz<T> datos,
	 																				  std::vector<T> etiquetas) {
	matriz<T> datos_reordenados;
	std::vector<T> etiquetas_reordenados;

	datos_reordenados.resize(datos.size());
	etiquetas_reordenados.resize(etiquetas.size());

	const unsigned num_elementos = datos.size();

	for ( unsigned i = 0; i < num_elementos; i++) {
		int indice = Random::getInt(0, datos.size());

		datos_reordenados[i] = datos[indice];
		etiquetas_reordenados[i] = etiquetas[indice];

		auto it_datos = datos.begin() + indice;
		auto it_etiquetas = etiquetas.begin() + indice;

		datos.erase(it_datos);
		etiquetas.erase(it_etiquetas);

	}

	return std::make_pair(datos_reordenados, etiquetas_reordenados);

}

}
