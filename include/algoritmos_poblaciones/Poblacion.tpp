namespace algoritmos_poblacion_expresiones {

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
	for (int i = 0; i < tam_poblacion_; i++){
		expresiones_[i] = otra.expresiones_[i];
	}
}

template <class T>
void Poblacion<T> :: evaluarPoblacion(const std::vector<std::vector<double> > & datos,
												  const std::vector<double> & etiquetas,
											  	  funcion_evaluacion_t f_evaluacion){
	// establecemos el mejor individuo al primero
	mejor_individuo_ = 0;

	if (!expresiones_[0].estaEvaluada()) {
		expresiones_[0].evaluarExpresion(datos, etiquetas, f_evaluacion);
	}

	// evaluamos el resto de individuos
	#pragma omp parallel for
	for ( int i = 1; i < tam_poblacion_; i++){
		if (!expresiones_[i].estaEvaluada()){
			expresiones_[i].evaluarExpresion(datos, etiquetas, f_evaluacion);
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

	for (int i = 0; i < tam_poblacion_; i++){
		suma += expresiones_[i].getFitness();
	}

	return suma;
}

template <class T>
unsigned Poblacion<T> :: seleccionIndividuo() const {

	double * probabilidad = new double [tam_poblacion_];

	double fitness_poblacion = sumaFitness();

	probabilidad[0] = expresiones_[0].getFitness() / fitness_poblacion;

	for (int i = 1; i < tam_poblacion_; i++){
		probabilidad[i] = probabilidad[i-1] +
								(expresiones_[i].getFitness() / fitness_poblacion);
	}
	// evitamos errores de redondeo
	probabilidad[tam_poblacion_ - 1] = 1.0;

	double aleatorio = Random::getFloat();

	int indice = 0;

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

	for ( int i = 0; i < tam_poblacion_; i++ ) {
		expresiones_[i] = otra.expresiones_[i];
	}

	mejor_individuo_ = otra.mejor_individuo_;

	return (*this);

}

template <class T>
void Poblacion<T> :: setIndividuo(const unsigned indice, const T & n_individuo) {
	expresiones_[indice] = n_individuo;
}

template <class T>
void Poblacion<T> :: redimensionar(const unsigned nuevo_tam) {
	if ( nuevo_tam == 0 ){
		liberarMemoria();
	} else {
		T * antigua_poblacion = expresiones_;
		int tam_antiguo = tam_poblacion_;

		reservarMemoria(nuevo_tam);

		int tam_a_copiar = std::min(static_cast<int>(nuevo_tam), tam_antiguo);

		for ( int i = 0; i < tam_a_copiar; i++) {
			expresiones_[i] = antigua_poblacion[i];
		}

		delete [] antigua_poblacion;
	}


}

template <class T>
void Poblacion<T> :: insertar(const T & nuevo_elemento) {
	redimensionar(tam_poblacion_ + 1);

	expresiones_[tam_poblacion_ - 1] = nuevo_elemento;

	if ( tam_poblacion_ == 1) {
		mejor_individuo_ = 0;
	} else if (expresiones_[mejor_individuo_].getFitness() > nuevo_elemento.getFitness()) {
		mejor_individuo_ = tam_poblacion_ - 1;
	}

}

template <class T>
void Poblacion<T> :: setMejorIndividuo(const int nuevo_mejor) {
	mejor_individuo_ = nuevo_mejor;
}

template <class T>
void Poblacion<T> :: buscarMejorIndividuo() {
	mejor_individuo_ = -1;

	if ( tam_poblacion_ > 0) {
		mejor_individuo_ = 0;

		for ( int i = 0; i < tam_poblacion_; i++) {
			if (expresiones_[i].getFitness() < expresiones_[mejor_individuo_].getFitness()) {
				mejor_individuo_ = i;
			}
		}
	}

}


template <class T>
void Poblacion<T> :: eliminar(const unsigned posicion) {

	T ultimo_elemento = expresiones_[tam_poblacion_ - 1];

	redimensionar(tam_poblacion_ - 1);

	for ( int i = posicion; i < tam_poblacion_ - 1; i++) {
		expresiones_[i] = expresiones_[i + 1];
	}

	if ( tam_poblacion_ > 0){
		expresiones_[tam_poblacion_ - 1] = ultimo_elemento;
		if ( static_cast<int>(posicion) == mejor_individuo_ ) {
			buscarMejorIndividuo();
		} else if (static_cast<int>(posicion) < mejor_individuo_){
			mejor_individuo_--;
		}

	} else {
		mejor_individuo_ = -1;
	}

}

template <class T>
void Poblacion<T> :: ordenar() {

	std::sort(expresiones_, expresiones_ + tam_poblacion_);
	mejor_individuo_ = 0;

}


} // namespace algoritmos_poblacion_expresiones
