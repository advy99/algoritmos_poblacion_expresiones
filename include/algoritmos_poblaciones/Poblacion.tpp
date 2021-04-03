namespace algoritmos_poblaciones {

template <class T>
Poblacion<T> :: Poblacion(){
	// una poblacion vacia no tiene nada
	expresiones_     = nullptr;
	tam_poblacion_   = 0;
	mejor_individuo_ = -1;
}

template <class T>
Poblacion<T> :: Poblacion(const unsigned tam, const unsigned lon_expre,
							const double prob_var, const unsigned num_vars,
							const unsigned prof_expre){
	// liberamos memoria para inicializar a vacio
	expresiones_ = nullptr;

	liberarMemoria();

	// reservamos memoria para tam individuos
	reservarMemoria(tam);
	tam_poblacion_ = tam;
	// inicializamos todas las expresiones de la poblacion

	// TODO : comprobar que T es Expresion o Expresion_GAP
	for (unsigned i = 0; i < tam; i++){
		expresiones_[i] = T(lon_expre, prob_var, num_vars, prof_expre);
	}
}

template <class T>
Poblacion<T> :: Poblacion ( const Poblacion & otra) {
	expresiones_ = nullptr;

	tam_poblacion_ = 0;

	(*this) = otra;
}

template <class T>
Poblacion<T> :: ~Poblacion(){
	liberarMemoria();
}

template <class T>
void Poblacion<T> :: liberarMemoria(){
	// si tiene asignada una direccion de memoria, liberamos la poblacion
	if (expresiones_ != nullptr){
		delete [] expresiones_;
	}

	// establecemos los valores a nulos

	tam_poblacion_   = 0;
	mejor_individuo_ = -1;
	expresiones_     = nullptr;

}

template <class T>
void Poblacion<T> :: reservarMemoria(const unsigned tam){
	expresiones_ = new T[tam];
	tam_poblacion_ = tam;
}

template <class T>
void Poblacion<T> :: copiarDatos(const Poblacion & otra){
	// copiamos los atributos
	tam_poblacion_ = otra.tam_poblacion_;
	mejor_individuo_ = otra.mejor_individuo_;

	// copiamos los elementos de la poblacion
	// no podemos usar memcpy ya que estos elementos si que
	// utilizan memoria dinamica de forma interna
	for (unsigned i = 0; i < tam_poblacion_; i++){
		expresiones_[i] = otra.expresiones_[i];
	}
}

template <class T>
void Poblacion<T> :: evaluarPoblacion(const std::vector<std::vector<double> > & datos,
											const std::vector<double> & etiquetas){
	// establecemos el mejor individuo al primero
	mejor_individuo_ = 0;

	if (!expresiones_[0].estaEvaluada()) {
		expresiones_[0].evaluarExpresion(datos, etiquetas);
	}

	// evaluamos el resto de individuos
	#pragma omp parallel for
	for ( unsigned i = 1; i < tam_poblacion_; i++){
		if (!expresiones_[i].estaEvaluada()){
			expresiones_[i].evaluarExpresion(datos, etiquetas);
		}

		#pragma omp critical
		{
			if (expresiones_[i].getFitness() < expresiones_[mejor_individuo_].getFitness()){
				mejor_individuo_ = i;
			}
		}

	}
}

template <class T>
double Poblacion<T> :: sumaFitness() const {
	double suma = 0.0;

	for (unsigned i = 0; i < tam_poblacion_; i++){
		suma += expresiones_[i].getFitness();
	}

	return suma;
}

template <class T>
unsigned Poblacion<T> :: seleccionIndividuo() const {

	double * probabilidad = new double [tam_poblacion_];

	double fitness_poblacion = sumaFitness();

	probabilidad[0] = expresiones_[0].getFitness() / fitness_poblacion;

	for (unsigned i = 1; i < tam_poblacion_; i++){
		probabilidad[i] = probabilidad[i-1] +
								(expresiones_[i].getFitness() / fitness_poblacion);
	}
	// evitamos errores de redondeo
	probabilidad[tam_poblacion_ - 1] = 1.0;

	double aleatorio = Random::getFloat();

	unsigned indice = 0;

	while (aleatorio > probabilidad[indice] && indice < tam_poblacion_){
		indice++;
	}


	delete [] probabilidad;

	return indice;


}

template <class T>
T Poblacion<T> :: getMejorIndividuo() const {
	return expresiones_[mejor_individuo_];
}

template <class T>
unsigned Poblacion<T> :: getIndiceMejorIndividuo() const {
	return mejor_individuo_;
}

template <class T>
unsigned Poblacion<T> :: getTamPoblacion() const {
	return tam_poblacion_;
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

	liberarMemoria();

	tam_poblacion_ = otra.tam_poblacion_;

	reservarMemoria(tam_poblacion_);

	for ( unsigned i = 0; i < tam_poblacion_; i++ ) {
		expresiones_[i] = otra.expresiones_[i];
	}

	mejor_individuo_ = otra.mejor_individuo_;

	return (*this);

}



} // namespace algoritmos_poblaciones
