namespace algoritmos_poblacion_expresiones {

template <class T>
Poblacion<T> :: Poblacion(){
	// una poblacion vacia no tiene nada
	expresiones_     = std::vector<T>();
	mejor_individuo_ = -1;
}

template <class T>
Poblacion<T> :: Poblacion(const unsigned tam, const unsigned lon_expre,
							const double prob_var, const unsigned num_vars,
							const unsigned prof_expre){
	// liberamos memoria para inicializar a vacio
	expresiones_ = std::vector<T>();


	// reservamos memoria para tam individuos
	expresiones_.resize(tam);
	// inicializamos todas las expresiones de la poblacion

	for (unsigned i = 0; i < tam; i++){
		expresiones_[i] = T(lon_expre, prob_var, num_vars, prof_expre);
	}

}

template <class T>
Poblacion<T> :: Poblacion ( const Poblacion & otra) {
	expresiones_ = std::vector<T>();

	(*this) = otra;
}

template <class T>
Poblacion<T> :: ~Poblacion(){
}

template <class T>
void Poblacion<T> :: copiar_datos(const Poblacion & otra){
	// copiamos los atributos
	mejor_individuo_ = otra.mejor_individuo_;

	expresiones_ = otra.expresiones_;
}

template <class T>
void Poblacion<T> :: evaluar_poblacion(const std::vector<std::vector<double> > & datos,
												  const std::vector<double> & etiquetas,
											  	  funcion_evaluacion_t f_evaluacion){
	// establecemos el mejor individuo al primero
	mejor_individuo_ = 0;

	if (!expresiones_[0].esta_evaluada()) {
		expresiones_[0].evaluar_expresion(datos, etiquetas, f_evaluacion);
	}

	// evaluamos el resto de individuos
	#pragma omp parallel for
	for ( unsigned i = 1; i < expresiones_.size(); i++){
		if (!expresiones_[i].esta_evaluada()){
			expresiones_[i].evaluar_expresion(datos, etiquetas, f_evaluacion);
		}

		#pragma omp critical
		{
			if (expresiones_[i].get_fitness() < expresiones_[mejor_individuo_].get_fitness()){
				mejor_individuo_ = i;
			}
		}

	}
}

template <class T>
double Poblacion<T> :: suma_fitness() const {
	double suma = 0.0;

	for (unsigned i = 0; i < expresiones_.size(); i++){
		suma += expresiones_[i].get_fitness();
	}

	return suma;
}

template <class T>
unsigned Poblacion<T> :: seleccion_individuo() const {

	std::vector<double> probabilidad;

	probabilidad.resize(expresiones_.size());

	double fitness_poblacion = suma_fitness();

	probabilidad[0] = expresiones_[0].get_fitness() / fitness_poblacion;

	for (unsigned i = 1; i < expresiones_.size(); i++){
		probabilidad[i] = probabilidad[i-1] +
								(expresiones_[i].get_fitness() / fitness_poblacion);
	}
	// evitamos errores de redondeo
	probabilidad[expresiones_.size() - 1] = 1.0;

	double aleatorio = Random::next_double();

	unsigned indice = 0;

	while (aleatorio > probabilidad[indice] && indice < expresiones_.size()){
		indice++;
	}

	return indice;


}

template <class T>
T Poblacion<T> :: get_mejor_individuo() const {
	return expresiones_[mejor_individuo_];
}

template <class T>
unsigned Poblacion<T> :: get_indice_mejor_individuo() const {
	return mejor_individuo_;
}

template <class T>
unsigned Poblacion<T> :: get_tam_poblacion() const {
	return expresiones_.size();
}

template <class T>
T & Poblacion<T> :: operator[] (const unsigned indice) {
	return expresiones_[indice];
}

template <class T>
const T & Poblacion<T> :: operator[] (const unsigned indice) const {
	return expresiones_[indice];
}

template <class T>
Poblacion<T> & Poblacion<T> :: operator= (const Poblacion & otra) {


	if (this != &otra){
		// copiamos los datos de la otra
		copiar_datos(otra);
	}

	return (*this);

}

template <class T>
void Poblacion<T> :: set_individuo(const unsigned indice, const T & n_individuo) {
	expresiones_[indice] = n_individuo;
}

template <class T>
void Poblacion<T> :: insertar(const T & nuevo_elemento) {
	expresiones_.push_back(nuevo_elemento);

	if ( expresiones_.size() == 1) {
		mejor_individuo_ = 0;
	} else if (expresiones_[mejor_individuo_].get_fitness() > nuevo_elemento.get_fitness()) {
		mejor_individuo_ = expresiones_.size() - 1;
	}
}

template <class T>
void Poblacion<T> :: set_mejor_individuo(const int nuevo_mejor) {
	mejor_individuo_ = nuevo_mejor;
}

template <class T>
void Poblacion<T> :: buscar_mejor_individuo() {
	mejor_individuo_ = -1;

	if ( expresiones_.size() > 0) {
		mejor_individuo_ = 0;

		for ( unsigned i = 0; i < expresiones_.size(); i++) {
			if (expresiones_[i].get_fitness() < expresiones_[mejor_individuo_].get_fitness()) {
				mejor_individuo_ = i;
			}
		}
	}

}


template <class T>
void Poblacion<T> :: eliminar(const unsigned posicion) {
	expresiones_.erase(expresiones_.begin() + posicion);
	buscar_mejor_individuo();
}

template <class T>
void Poblacion<T> :: ordenar() {

	std::sort(expresiones_.begin(), expresiones_.end());
	mejor_individuo_ = 0;

}


} // namespace algoritmos_poblacion_expresiones
