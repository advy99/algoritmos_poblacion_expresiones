#include "algoritmos_poblaciones/Expresion.hpp"


namespace algoritmos_poblaciones {

Expresion :: Expresion(const unsigned prof_max){

	// establecemos la profundidad a la maxima dada
	profundidad_maxima_ = prof_max;

	// inicilizamos la expresion vacia
	inicializarVacia();

}

Expresion :: Expresion(const Arbol subarbol, const unsigned prof_max){

	// establecemos la profundidad maxima a la dada
	profundidad_maxima_ = prof_max;

	// inicializamos la expresion vacia
	inicializarVacia();

	// obtenemos el subarbol
	(*this) = obtenerSubarbol(subarbol);

}

Expresion :: Expresion(const unsigned longitud_max, const double prob_variable,
							const unsigned num_vars, const unsigned prof_max){

	profundidad_maxima_ = prof_max;

	numero_variables_ = num_vars;

	inicializarVacia();

	// generamos una expresion aleatoria
	generarExpresionAleatoria(longitud_max, prob_variable, num_vars);
}



Expresion Expresion :: obtenerSubarbol(const Arbol subarbol){
	Expresion sol;

	unsigned tam = 0;

	if ( subarbol == nullptr) {
		sol.arbol_ = nullptr;
	} else {
		// al principio comenzamos con un nodo
		unsigned ramas_libres = 1;

		// mientras tenga ramas que visitar
		while(ramas_libres > 0){
			// si no es ni un numero ni una variable
			if (subarbol[tam].getTipoNodo() != TipoNodo::NUMERO &&
				subarbol[tam].getTipoNodo() != TipoNodo::VARIABLE){
				// es un operador, tiene dos ramas
				ramas_libres += 2;
			}
			// en todo caso, he visitado ese nodo, y el tamaño se incrementa en uno
			ramas_libres--;
			tam++;
		}

		// una vez sabemos el tamaño, redimensionamos la solucion
		sol.liberarMemoriaArbol();

		sol.asignarArbol(subarbol, tam);

	}

	// actualizamos la longitud de la solucion
	sol.longitud_arbol_ = tam;

	// y la devolvemos
	return sol;
}



void Expresion :: inicializarVacia(){
	// una expresion vacia no tiene arbol
	arbol_              = nullptr;
	longitud_arbol_     = 0;
	numero_variables_ = 0;
	dejaEstarEvaluada();
}



Expresion :: ~Expresion(){
	liberarMemoria();
}

void Expresion :: liberarMemoriaArbol() {
	// si el arbol tiene asociado alguna direccion de memoria
	if (arbol_ != nullptr){
		// la liberamos
		delete [] arbol_;
		arbol_ = nullptr;
	}
}


void Expresion :: liberarMemoria(){

	liberarMemoriaArbol();

	// una vez esta liberada la memoria, la expresion esta vacia, luego
	// la ponemos a vacio
	inicializarVacia();

}

void Expresion :: reservarMemoriaArbol(const int tam){
	// en todo caso la longitud reservada es cero
	longitud_arbol_ = 0;

	// si el tamaño es mayor que 0, reservamos, si no se queda a cero
	if (tam > 0){
		arbol_ = new Nodo[tam];
		longitud_arbol_ = tam;
	}
}


void Expresion :: copiarDatos(const Expresion & otra){
	// copiamos todos los valores
	fitness_            = otra.fitness_;
	evaluada_           = otra.evaluada_;
	longitud_arbol_     = otra.longitud_arbol_;
	profundidad_maxima_ = otra.profundidad_maxima_;
	numero_variables_   = otra.numero_variables_;

	if ( otra.arbol_ == nullptr) {
		arbol_ = nullptr;
	} else {
		asignarArbol(otra.arbol_, otra.longitud_arbol_);
	}

}


Expresion :: Expresion(const Expresion & otra){
	// al inicializar vacia mantenemos la prfuncidad que queramos
	profundidad_maxima_ = otra.profundidad_maxima_;

	// inicializamos vacia para poner punteros a nullptr
	inicializarVacia();

	// copiamos la otra con el operador = ya implementado
	(*this) = otra;
}

Expresion & Expresion :: operator= (const Expresion & otra){
	// si no es ella misma
	if (this != &otra){
		// liberamos la memoria de la actual
		liberarMemoria();

		// copiamos los datos de la otra
		copiarDatos(otra);
	}

	// devolvemos el objeto actual
	return (*this);

}

bool Expresion :: generarExpresionAleatoria(const unsigned longitud_maxima,
														const double prob_variable,
														const unsigned num_variables){

	// si no tenemos espacio, redimensionamos
	if (longitud_maxima > longitud_arbol_){
		liberarMemoriaArbol();
		reservarMemoriaArbol(longitud_maxima);
	}


	// comenzamos con una rama libre
	int ramas_libres = 1;
	unsigned i = 0;

	// mientras tengamos longitud y tengamos ramas sueltas
	while (i < longitud_maxima && ramas_libres > 0){
		// obtenemos la probabilidad de que sea un operador
		float prob_operador = static_cast<float>(ramas_libres*ramas_libres+1) /
									 static_cast<float>(longitud_maxima-i);

		// si es un operador, lo generamos
		if (Random::getFloat() > prob_operador){
			arbol_[i].setTipoNodoOperadorAleatorio();
			// tenemos una rama más libre, la actual que sería el
			// termino de la izquierda y una más para el termino de la derecha
			ramas_libres++;

		} else {
			// si es un simbolo terminal, generamos un aleatorio
			// para ver si es variable o numero
			if (Random::getFloat() < prob_variable){
				arbol_[i].setTipoNodo(TipoNodo::VARIABLE);
				arbol_[i].setTerminoAleatorio(num_variables);
			} else {
				arbol_[i].setTipoNodo(TipoNodo::NUMERO);
				arbol_[i].setValorNumerico(Random::getFloat(-10.0, 10.0));
			}


			// al ser un terminal, esta rama ya no esta libre y quitamos una
			ramas_libres--;
		}

		// hemos rellenado un hueco del arbol
		i++;
	}

	// si lo hemos rellenado sin dejar ramas libres, esta bien
	bool exito = ramas_libres == 0;

	// si hemos dejado ramas, sacamos un error por la salida de error
	if (!exito){
		std::cerr << "Generación incorrecta de expresión aleatoria." << std::endl;
	}

	// la longitud del arbol es i, y la expresion no esta evaluada
	longitud_arbol_ = i;
	dejaEstarEvaluada();

	return exito;

}

double Expresion :: obtenerNumero ( const Nodo & n) const {
	return n.getValorNumerico();
}

double Expresion :: evaluarDato(std::stack<Nodo> & pila,
										const std::vector<double> & dato) const {

	double resultado = 0.0;

	// si la pila esta vacia, devolvemos el valor
	if (pila.empty()){
		resultado = 0.0;

	} else if (pila.top().getTipoNodo() == TipoNodo::NUMERO){
		// si el tope de la pila es un nodo de tipo Numero, miramos su valor en la
		// posicion del cromosoma correspondiente
		resultado = obtenerNumero(pila.top());

		// eliminamos de la pila, y lo devolvemos
		pila.pop();

	} else if (pila.top().getTipoNodo() == TipoNodo::VARIABLE){
		// si es una variable, la consultamos en el dato dado, eliminamos el nodo
		// de la pila y devolvemos el valor del dato
		resultado = dato[pila.top().getValor()];
		pila.pop();

	} else {
		// si es un operador, guardamos la operacion
		TipoNodo operacion = pila.top().getTipoNodo();

		// la eliminamos de la pila
		pila.pop();

		// consultamos el valor de la rama izquierda y la derecha
		double valor_izda = evaluarDato(pila, dato);
		double valor_dcha = evaluarDato(pila, dato);

		// aplicamos el operador con ambas ramas y devolvemos el resultado
		if (operacion == TipoNodo::MAS){
			resultado = valor_izda + valor_dcha;

		} else if (operacion == TipoNodo::MENOS){
			resultado = valor_izda - valor_dcha;

		} else if (operacion == TipoNodo::POR){
			resultado = valor_izda * valor_dcha;

		} else if (operacion == TipoNodo::ENTRE){
			if (!comparar_reales(valor_dcha, 0.0) ){
				resultado = valor_izda / valor_dcha;
			} else {
				resultado = 1.0f;
			}
		}

	}

	return resultado;

}

double Expresion :: evaluarDato(const std::vector<double> & dato) const {
	double resultado;

	// pila donde almacenaremos la expresion
	std::stack<Nodo> pila;

	//volcamos la expresion en la pila
	for (int i = (int)getLongitudArbol() - 1; i >= 0; i--){
		pila.push(arbol_[i]);
	}

	// la evaluamos para el dato i
	resultado = evaluarDato(pila, dato);

	return resultado;

}


void Expresion :: evaluarExpresion(const std::vector<std::vector<double>> &datos,
											  const std::vector<double> & etiquetas){

	// almacenamos como resultado el valor de fitness
	double resultado = fitness_;

	double valor = 0.0;
	double suma = 0.0;

	std::vector<double> valores_predecidos;
	valores_predecidos.resize(etiquetas.size());

	// si no esta evaluada y el arbol contiene una expresion
	if (!evaluada_ && arbol_ != nullptr){

		// para cada dato
		for (unsigned i = 0; i < datos.size(); i++){

			// la evaluamos para el dato i
			valores_predecidos[i] = evaluarDato(datos[i]);

		}

		// hacemos la media de los cuadrados
		resultado = raiz_error_cuadratico_medio(valores_predecidos, etiquetas);


	}

	// actualizamos el fitness y que esta evaluada y devolvemos el resultado
	fitness_ = resultado;
	evaluada_ = true;

}

bool Expresion :: estaEvaluada() const{
	return evaluada_;
}

double Expresion :: getFitness() const{
	return fitness_;
}

unsigned Expresion :: getLongitudArbol() const{
	return longitud_arbol_;
}



bool Expresion :: intercambiarSubarbol(const Expresion & otra, const unsigned pos,
													const unsigned cruce_padre,
												   Expresion & hijo) const {

	Expresion madre_cortada((arbol_ + pos), profundidad_maxima_);
	Expresion padre_cortado((otra.arbol_ + cruce_padre), otra.profundidad_maxima_);

	// sumamos, la parte de la madre, la longitud de la parte del padre, y lo que nos queda de madre tras el cruce
	unsigned nueva_longitud = pos + padre_cortado.getLongitudArbol() + (getLongitudArbol() - madre_cortada.getLongitudArbol() - pos);


	bool podido_cruzar = nueva_longitud <= profundidad_maxima_;

	if ( podido_cruzar) {
		// cruce
		hijo.liberarMemoria();
		hijo.reservarMemoriaArbol(nueva_longitud);

		for ( unsigned i = 0; i < pos; i++) {
			hijo.arbol_[i] = arbol_[i];
		}

		for ( unsigned i = 0; i < padre_cortado.getLongitudArbol(); i++) {
			hijo.arbol_[i + pos] = padre_cortado.arbol_[i];
		}

		unsigned indice_hijo = 0;

		// i en este caso comienza en el punto donde acaba el arbol que hemos intercambiado
		for ( unsigned i = pos + madre_cortada.getLongitudArbol(); i < getLongitudArbol(); i++) {
			// nos ponemos donde habiamos dejado de copiar el padre
			indice_hijo = pos + padre_cortado.getLongitudArbol() + (i - (pos + madre_cortada.getLongitudArbol()) ) ;
			hijo.arbol_[indice_hijo] = arbol_[i];
		}

		//hijo.asignarCromosoma(cromosoma, longitud_cromosoma);

	}

	return podido_cruzar;

}



void Expresion :: cruceArbol(const Expresion & otra, Expresion & hijo1, Expresion & hijo2) const {

	int punto_cruce_madre;
	int punto_cruce_padre;

	bool cruce_mal;

	// cruzamos mientras se cruce mal
	do {

		punto_cruce_madre = Random::getInt(getLongitudArbol());
		punto_cruce_padre = Random::getInt(otra.getLongitudArbol());

		cruce_mal = !(intercambiarSubarbol(otra, punto_cruce_madre, punto_cruce_padre, hijo1));

		if ( !cruce_mal ) {
			cruce_mal = !(otra.intercambiarSubarbol((*this), punto_cruce_padre, punto_cruce_madre, hijo2));
		}

	} while (cruce_mal);


}


void Expresion :: asignarArbol (const Arbol nuevo_arbol, const unsigned longitud_n_arbol) {

	liberarMemoriaArbol();

	reservarMemoriaArbol(longitud_n_arbol);

	memcpy(arbol_, nuevo_arbol, longitud_n_arbol*sizeof(Nodo));

	longitud_arbol_ = longitud_n_arbol;

}


void Expresion :: dejaEstarEvaluada(){
	// ponemos la flag a false y establecemos el fitness a NaN
	evaluada_ = false;
	fitness_ = std::numeric_limits<double>::infinity();
}


unsigned Expresion :: contarNiveles(std::stack<Nodo> & pila, unsigned nivel) const{
	// si la pila esta vacia, devolvemos el nivel actual
	if (pila.empty()){
		return nivel;
	} else if (pila.top().getTipoNodo() == TipoNodo::NUMERO ||
				  pila.top().getTipoNodo() == TipoNodo::VARIABLE) {
		// si en el tope hay un simbolo terminal, eso cuenta como un nivel,
		// eliminamos el nodo de la pila, y devolvemos ese valor del nivel
		nivel++;
		pila.pop();
		return nivel;
	} else {
		// es un operador
		nivel++;
		// eliminamos el nodo del operador
		pila.pop();
		unsigned niveles_izda = nivel;
		unsigned niveles_dcha = nivel;

		// miramos el numero de niveles a la derecha y a la izquierda
		niveles_izda = contarNiveles(pila, nivel);
		niveles_dcha = contarNiveles(pila, nivel);

		// nos quedamos con el nivel de la rama con mayor profundidad
		nivel = niveles_izda > niveles_dcha ? niveles_izda : niveles_dcha;

		return nivel;
	}
}

unsigned Expresion :: calcularProfundidad(const unsigned comienzo) const {

	unsigned profundidad = 0;
	std::stack<Nodo> pila;

	//volcamos la expresion en la pila
	for (int i = static_cast<int>(getLongitudArbol() - 1); i >= static_cast<int>(comienzo); i--){
		pila.push(arbol_[i]);
	}
	// contamos los niveles de toda la pila
	profundidad = contarNiveles(pila, profundidad);


	return profundidad;

}






bool Expresion :: mismoNicho(const Expresion & otra) const {
	return (*this == otra);
}

std::string Expresion :: obtenerStringExpresion(std::stack<Nodo> & pila,
															 std::string resultado,
															 const bool izda) const{
	// si la pila esta vacia, devolvemos el resultado
	if (pila.empty()){
		return resultado;
	} else if (pila.top().getTipoNodo() == TipoNodo::NUMERO){
		// si es un numero, lo consultamos en el cromosoma
		// dependiendo de si estamos mirando el nodo de la izquierda o de
		// la derecha ponemos primero el numero y lo que llevamos
		// o lo que llevamos y el numero
		if (izda){
			// resultado = std::to_string(cromosoma[pila.top().getValor()]) +
			resultado = std::to_string(obtenerNumero(pila.top()) ) +
							" " + resultado;
		} else {
			resultado = resultado + " " +
							std::to_string(obtenerNumero(pila.top()));
		}

		// eliminamos el nodo de la pila y devolvemos el resultado
		pila.pop();
		return resultado;

	} else if (pila.top().getTipoNodo() == TipoNodo::VARIABLE){
		// si es una variable, ponemos xN
		// de nuevo, dependiendo de si miramos el nodo de la izquierda o el
		// de la derecha lo ponemos aun ladou a otro
		if (izda){
			resultado = "x" + std::to_string(pila.top().getValor()) +
							" " + resultado;
		} else {
			resultado = resultado + " x" +
							std::to_string(pila.top().getValor());
		}

		// eliminamos el nodo y devolvemos el resultado
		pila.pop();
		return resultado;
	} else {

		// sies un operador, obtenemos el valor
		std::string valor;
		if (pila.top().getTipoNodo() == TipoNodo::MAS){
			valor = "+";
		} else if (pila.top().getTipoNodo() == TipoNodo::MENOS){
			valor = "-";
		} else if (pila.top().getTipoNodo() == TipoNodo::POR){
			valor = "*";
		} else if (pila.top().getTipoNodo() == TipoNodo::ENTRE){
			valor = "/";
		}


		// eliminamos su nodo
		pila.pop();
		std::string izquierda;
		std::string derecha;

		// miramos la expresion que tienen a la izquierda y a la derecha
		izquierda = obtenerStringExpresion(pila, "", true) ;
		derecha = obtenerStringExpresion(pila, "", false);

		// la concatenamos, lo que tiene a la izquierda, el operador, y lo de la
		// derecha, todo entre parentesis
		std::string total = "( " + izquierda + " " + valor + " " + derecha + " )";

		// y lo añadimos al resultado, dependiendo de si estamos a la izqda o no
		if (izda){
			resultado = total + resultado;
		} else {
			resultado = resultado + total;
		}

		return resultado;

	}



}



Arbol Expresion:: getArbol () const {
	return arbol_;
}


std::string Expresion :: stringExpresion() const {
	std::string resultado = "";

	std::stack<Nodo> pila;

	// volcamos la pila
	for (int i = (int)getLongitudArbol() - 1; i >= 0; i--){
		pila.push(arbol_[i]);
	}

	// obtenemos el string de toda la pila
	resultado = obtenerStringExpresion(pila, resultado, true);

	return resultado;
}

std::ostream & operator<< (std::ostream & os, const Expresion & exp){
	// obtenemos el string y lo sacamos por el flujo
	std::string exp_string = exp.stringExpresion();

	os << exp_string << std::endl;

	return os;
}



void Expresion :: mutarGP (const int num_vars) {


	int posicion = Random::getInt(longitud_arbol_);

	float aleatorio = Random::getFloat();

	if ( aleatorio < 0.5) {
		// primera opcion, cambiar un termino por otro
		TipoNodo tipo = arbol_[posicion].getTipoNodo();

		if ( tipo == TipoNodo::NUMERO || tipo == TipoNodo::VARIABLE){
			if ( Random::getFloat() < 0.5) {
				arbol_[posicion].setTipoNodo(TipoNodo::VARIABLE);
				arbol_[posicion].setTerminoAleatorio(num_vars);
			} else {
				arbol_[posicion].setTipoNodo(TipoNodo::NUMERO);
				arbol_[posicion].setValorNumerico(Random::getFloat(-10.0, 10.0));
			}

		} else {
			arbol_[posicion].setTipoNodoOperadorAleatorio();
		}
	} else {
		// generamos un arbol aleatorio en la posicion

		bool cruce_mal;
		Expresion hijo = (*this);

		do {

			Expresion exp_aleatorio(profundidad_maxima_, 0.3, numero_variables_, profundidad_maxima_);

			cruce_mal = !(intercambiarSubarbol(exp_aleatorio, posicion, 0, hijo));

		} while (cruce_mal);

		asignarArbol(hijo.arbol_, hijo.longitud_arbol_);

	}

}



bool Expresion :: operator == ( const Expresion & otra) const {

	bool resultado = longitud_arbol_ == otra.longitud_arbol_;

	for (unsigned i = 0; i < longitud_arbol_ && resultado; i++){
		resultado = arbol_[i] == otra.arbol_[i];
	}

	return resultado;
}

bool Expresion :: operator != ( const Expresion & otra) const {
	return !(*this == otra);
}

} // namespace algoritmos_poblaciones
