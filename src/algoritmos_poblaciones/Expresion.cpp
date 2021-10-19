#include "algoritmos_poblaciones/Expresion.hpp"


namespace algoritmos_poblacion_expresiones {

Expresion :: Expresion(const unsigned prof_max){

	// establecemos la profundidad a la maxima dada
	profundidad_maxima_ = prof_max;

	// inicilizamos la expresion vacia
	inicializar_vacia();

}

Expresion :: Expresion(const std::vector<Nodo> & subarbol, const unsigned prof_max){

	// establecemos la profundidad maxima a la dada
	profundidad_maxima_ = prof_max;

	// inicializamos la expresion vacia
	inicializar_vacia();

	// obtenemos el subarbol
	(*this) = obtener_subarbol(subarbol, 0);

}

Expresion :: Expresion(const unsigned longitud_max, const double prob_variable,
							const unsigned num_vars, const unsigned prof_max){

	profundidad_maxima_ = prof_max;

	numero_variables_ = num_vars;

	inicializar_vacia();

	// generamos una expresion aleatoria
	generar_expresion_aleatoria(longitud_max, prob_variable, num_vars);
}


Expresion :: Expresion ( const std::string & nombre_archivo, const unsigned longitud_max, const unsigned num_variables) {

	profundidad_maxima_ = longitud_max;
	numero_variables_ = num_variables;

	std::ifstream is (nombre_archivo.c_str());

	if ( !is.is_open() ) {
		std::cerr << "ERROR: No se ha podido abrir " << nombre_archivo << std::endl;
	} else {
		std::string linea_expresion = "";

		std::getline(is, linea_expresion);

		std::vector<Nodo> pila_expresion;

		pila_expresion = obtener_expresion(linea_expresion);

		if ( pila_expresion.size() > profundidad_maxima_) {
			std::cerr << "ERROR: Expresion más grande del límite dado." << std::endl;
		} else {
			arbol_ = pila_expresion;
		}

	}

}

std::vector<Nodo> Expresion :: obtener_expresion(const std::string & linea_expresion) {

	std::istringstream buffer_exp (linea_expresion);

	std::string part;


	Nodo operador;
	TipoNodo tipo_operador = TipoNodo::NUMERO;

	std::vector<Nodo> parte_izquierda;
	std::vector<Nodo> parte_derecha;

	buffer_exp >> part;
	do {

		if ( part == "(" ) {
			std::string sub_string = obtener_string_parentesis(buffer_exp);
			parte_izquierda = obtener_expresion(sub_string);
		} else {
			if (part[0] == 'x') {
				// si es una variable
				Nodo var;
				var.set_tipo_nodo(TipoNodo::VARIABLE);
				// elimino la x
				part.erase(part.begin());
				var.set_valor(std::atoi(part.c_str()) );
				parte_izquierda.push_back(var);
			} else {
				// si es otra cosa: un numero
				Nodo num;
				num.set_tipo_nodo(TipoNodo::NUMERO);
				num.set_valor_numerico(std::atof(part.c_str()) );
				parte_izquierda.push_back(num);
			}
		}

		if ( !buffer_exp.eof() ) {
			buffer_exp >> part;

			// si he leido una parte, ahora leo el operador
			if (part == "+") {
				tipo_operador = TipoNodo::MAS;
			} else if ( part == "-" ) {
				tipo_operador = TipoNodo::MENOS;
			} else if ( part == "*" ) {
				// si es un operador
				tipo_operador = TipoNodo::POR;
			} else if ( part == "/" ) {
				// si es un operador
				tipo_operador = TipoNodo::ENTRE;
			}

			buffer_exp >> part;

			if ( part == "(" ) {
				std::string sub_string = obtener_string_parentesis(buffer_exp);
				parte_derecha = obtener_expresion(sub_string);
			} else {
				if (part[0] == 'x') {
					// si es una variable
					Nodo var;
					var.set_tipo_nodo(TipoNodo::VARIABLE);
					// elimino la x
					part.erase(part.begin());
					var.set_valor(std::atoi(part.c_str()));
					parte_derecha.push_back(var);
				} else {
					// si es otra cosa: un numero
					Nodo num;
					num.set_tipo_nodo(TipoNodo::NUMERO);
					num.set_valor_numerico(std::atof(part.c_str()));
					parte_derecha.push_back(num);
				}
			}

		}

		buffer_exp >> part;
	} while (!buffer_exp.eof());


	std::vector<Nodo> resultado;

	if (tipo_operador != TipoNodo::NUMERO) {
		// metemos el operador
		operador.set_tipo_nodo(tipo_operador);
		resultado.push_back(operador);

		// metemos la parte izquierda
		resultado.insert( resultado.end(), parte_izquierda.begin(), parte_izquierda.end() );

		// metemos la parte derecha
		resultado.insert( resultado.end(), parte_derecha.begin(), parte_derecha.end() );
	} else {
		resultado = parte_izquierda;
	}

	return resultado;

}

std::string Expresion :: obtener_string_parentesis(std::istringstream & buffer_exp) {
	// si es el comienzo de una parte
	int contador_parentesis = 1;

	std::string sub_string = "";
	std::string part = "";

	while ( contador_parentesis != 0) {
		buffer_exp >> part;
		if (part == ")") {
			contador_parentesis--;
		} else if (part == "(") {
			contador_parentesis++;
		}

		if ( contador_parentesis != 0) {
			sub_string += part + " ";
		}
	}

	return sub_string;
}


std::vector<Nodo> Expresion :: obtener_subarbol(const std::vector<Nodo> & arbol, int posicion) const{
	std::vector<Nodo> sol;

	if ( arbol.size() > 0) {
		// al principio comenzamos con un nodo
		unsigned ramas_libres = 1;

		// mientras tenga ramas que visitar
		while(ramas_libres > 0){
			// si no es ni un numero ni una variable
			if (arbol[posicion].get_tipo_nodo() != TipoNodo::NUMERO &&
				arbol[posicion].get_tipo_nodo() != TipoNodo::VARIABLE){
				// es un operador, tiene dos ramas
				ramas_libres += 2;
			}
			// en todo caso, he visitado ese nodo, y el tamaño se incrementa en uno
			ramas_libres--;
			sol.push_back(arbol[posicion]);
			posicion++;

		}

	}


	// y la devolvemos
	return sol;
}



void Expresion :: inicializar_vacia(){
	// una expresion vacia no tiene arbol
	arbol_ = std::vector<Nodo>();
	numero_variables_ = 0;
	deja_estar_evaluada();
}



void Expresion :: copiar_datos(const Expresion & otra){
	// copiamos todos los valores
	fitness_            = otra.fitness_;
	evaluada_           = otra.evaluada_;
	profundidad_maxima_ = otra.profundidad_maxima_;
	numero_variables_   = otra.numero_variables_;
	arbol_              = otra.arbol_;

}


Expresion :: Expresion(const Expresion & otra){
	// al inicializar vacia mantenemos la prfuncidad que queramos
	profundidad_maxima_ = otra.profundidad_maxima_;

	// inicializamos vacia para poner punteros a nullptr
	inicializar_vacia();

	// copiamos la otra con el operador = ya implementado
	(*this) = otra;
}

Expresion & Expresion :: operator= (const Expresion & otra){
	// si no es ella misma
	if (this != &otra){
		// copiamos los datos de la otra
		copiar_datos(otra);
	}

	// devolvemos el objeto actual
	return (*this);

}

bool Expresion :: generar_expresion_aleatoria(const unsigned longitud_maxima,
														const double prob_variable,
														const unsigned num_variables){

	profundidad_maxima_ = longitud_maxima;
	// si no tenemos espacio, redimensionamos
	arbol_ = std::vector<Nodo>();
	arbol_.resize(longitud_maxima);

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
			arbol_[i].set_tipo_nodo_operador_aleatorio();
			// tenemos una rama más libre, la actual que sería el
			// termino de la izquierda y una más para el termino de la derecha
			ramas_libres++;

		} else {
			// si es un simbolo terminal, generamos un aleatorio
			// para ver si es variable o numero
			if (Random::getFloat() < prob_variable){
				arbol_[i].set_tipo_nodo(TipoNodo::VARIABLE);
				arbol_[i].set_termino_aleatorio(num_variables);
			} else {
				arbol_[i].set_tipo_nodo(TipoNodo::NUMERO);
				arbol_[i].set_valor_numerico(Random::getFloat(-10.0, 10.0));
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
	arbol_.resize(i);

	deja_estar_evaluada();

	return exito;

}

double Expresion :: obtener_numero ( const Nodo & n) const {
	return n.get_valor_numerico();
}

double Expresion :: evaluar_dato(std::stack<Nodo> & pila,
										const std::vector<double> & dato) const {

	double resultado = 0.0;

	// si la pila esta vacia, devolvemos el valor
	if (pila.empty()){
		resultado = 0.0;

	} else if (pila.top().get_tipo_nodo() == TipoNodo::NUMERO){
		// si el tope de la pila es un nodo de tipo Numero, miramos su valor en la
		// posicion del cromosoma correspondiente
		resultado = obtener_numero(pila.top());

		// eliminamos de la pila, y lo devolvemos
		pila.pop();

	} else if (pila.top().get_tipo_nodo() == TipoNodo::VARIABLE){
		// si es una variable, la consultamos en el dato dado, eliminamos el nodo
		// de la pila y devolvemos el valor del dato
		resultado = dato[pila.top().get_valor()];
		pila.pop();

	} else {
		// si es un operador, guardamos la operacion
		TipoNodo operacion = pila.top().get_tipo_nodo();

		// la eliminamos de la pila
		pila.pop();

		// consultamos el valor de la rama izquierda y la derecha
		double valor_izda = evaluar_dato(pila, dato);
		double valor_dcha = evaluar_dato(pila, dato);

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

double Expresion :: evaluar_dato(const std::vector<double> & dato) const {
	double resultado;

	// pila donde almacenaremos la expresion
	std::stack<Nodo> pila;

	//volcamos la expresion en la pila
	for (int i = (int)get_longitud_arbol() - 1; i >= 0; i--){
		pila.push(arbol_[i]);
	}

	// la evaluamos para el dato i
	resultado = evaluar_dato(pila, dato);

	return resultado;

}


void Expresion :: evaluar_expresion(const std::vector<std::vector<double>> &datos,
											  const std::vector<double> & etiquetas,
										  	  funcion_evaluacion_t f_evaluacion,
										  	  const bool evaluar){

	// almacenamos como resultado el valor de fitness
	double resultado = fitness_;

	std::vector<double> valores_predecidos;
	valores_predecidos.resize(etiquetas.size());

	// si no esta evaluada y el arbol contiene una expresion
	if ( (!evaluada_ || evaluar) && arbol_.size() > 0){

		// para cada dato
		for (unsigned i = 0; i < datos.size(); i++){

			// la evaluamos para el dato i
			valores_predecidos[i] = evaluar_dato(datos[i]);
		}

		// hacemos la media de los cuadrados
		resultado = f_evaluacion(valores_predecidos, etiquetas);


	}
	// actualizamos el fitness y que esta evaluada y devolvemos el resultado
	fitness_ = resultado;
	evaluada_ = true;

}

bool Expresion :: esta_evaluada() const{
	return evaluada_;
}

double Expresion :: get_fitness() const{
	return fitness_;
}

unsigned Expresion :: get_longitud_arbol() const{
	return arbol_.size();
}



bool Expresion :: intercambiar_subarbol(const Expresion & otra, const unsigned pos,
													const unsigned cruce_padre,
												   Expresion & hijo) const {

	//Expresion madre_cortada((arbol_ + pos), profundidad_maxima_);

	std::vector<Nodo> madre_cortada = obtener_subarbol(arbol_, pos);

	//Expresion padre_cortado((otra.arbol_ + cruce_padre), otra.profundidad_maxima_);

	std::vector<Nodo> padre_cortado = obtener_subarbol(otra.get_arbol(), cruce_padre);

	// sumamos, la parte de la madre, la longitud de la parte del padre, y lo que nos queda de madre tras el cruce
	unsigned nueva_longitud = pos + padre_cortado.size() + (get_longitud_arbol() - madre_cortada.size() - pos);


	bool podido_cruzar = nueva_longitud <= profundidad_maxima_;


	if ( podido_cruzar) {
		// cruce
		std::vector<Nodo> arbol_hijo;
		arbol_hijo.resize(nueva_longitud);

		for ( unsigned i = 0; i < pos; i++) {
			arbol_hijo[i] = arbol_[i];
		}

		for ( unsigned i = 0; i < padre_cortado.size(); i++) {
			arbol_hijo[i + pos] = padre_cortado[i];
		}

		unsigned indice_hijo = 0;

		// i en este caso comienza en el punto donde acaba el arbol que hemos intercambiado
		for ( unsigned i = pos + madre_cortada.size(); i < get_longitud_arbol(); i++) {
			// nos ponemos donde habiamos dejado de copiar el padre
			indice_hijo = pos + padre_cortado.size() + (i - (pos + madre_cortada.size()) ) ;
			arbol_hijo[indice_hijo] = arbol_[i];
		}

		//hijo.asignar_cromosoma(cromosoma, longitud_cromosoma);
		hijo.asignar_arbol(arbol_hijo);
	}

	return podido_cruzar;

}



void Expresion :: cruce_arbol(const Expresion & otra, Expresion & hijo1, Expresion & hijo2) const {

	int punto_cruce_madre;
	int punto_cruce_padre;

	bool cruce_mal;

	// cruzamos mientras se cruce mal
	do {

		punto_cruce_madre = Random::getInt(get_longitud_arbol());
		punto_cruce_padre = Random::getInt(otra.get_longitud_arbol());

		cruce_mal = !(intercambiar_subarbol(otra, punto_cruce_madre, punto_cruce_padre, hijo1));

		if ( !cruce_mal ) {
			cruce_mal = !(otra.intercambiar_subarbol((*this), punto_cruce_padre, punto_cruce_madre, hijo2));
		}

	} while (cruce_mal);


}


void Expresion :: asignar_arbol (const std::vector<Nodo> & nuevo_arbol) {

	arbol_ = nuevo_arbol;

}


void Expresion :: deja_estar_evaluada(){
	// ponemos la flag a false y establecemos el fitness a NaN
	evaluada_ = false;
	fitness_ = std::numeric_limits<double>::infinity();
}


unsigned Expresion :: contar_niveles(std::stack<Nodo> & pila, unsigned nivel) const{
	// si la pila esta vacia, devolvemos el nivel actual
	if (pila.empty()){
		return nivel;
	} else if (pila.top().get_tipo_nodo() == TipoNodo::NUMERO ||
				  pila.top().get_tipo_nodo() == TipoNodo::VARIABLE) {
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
		niveles_izda = contar_niveles(pila, nivel);
		niveles_dcha = contar_niveles(pila, nivel);

		// nos quedamos con el nivel de la rama con mayor profundidad
		nivel = niveles_izda > niveles_dcha ? niveles_izda : niveles_dcha;

		return nivel;
	}
}

unsigned Expresion :: calcular_profundidad(const unsigned comienzo) const {

	unsigned profundidad = 0;
	std::stack<Nodo> pila;

	//volcamos la expresion en la pila
	for (int i = static_cast<int>(get_longitud_arbol() - 1); i >= static_cast<int>(comienzo); i--){
		pila.push(arbol_[i]);
	}
	// contamos los niveles de toda la pila
	profundidad = contar_niveles(pila, profundidad);


	return profundidad;

}




std::string Expresion :: obtener_string_expresion(std::stack<Nodo> & pila,
															 std::string resultado,
															 const bool izda) const{
	// si la pila esta vacia, devolvemos el resultado
	if (pila.empty()){
		return resultado;
	} else if (pila.top().get_tipo_nodo() == TipoNodo::NUMERO){
		// si es un numero, lo consultamos en el cromosoma
		// dependiendo de si estamos mirando el nodo de la izquierda o de
		// la derecha ponemos primero el numero y lo que llevamos
		// o lo que llevamos y el numero
		if (izda){
			// resultado = std::to_string(cromosoma[pila.top().get_valor()]) +
			resultado = std::to_string(obtener_numero(pila.top()) ) +
							" " + resultado;
		} else {
			resultado = resultado + " " +
							std::to_string(obtener_numero(pila.top()));
		}

		// eliminamos el nodo de la pila y devolvemos el resultado
		pila.pop();
		return resultado;

	} else if (pila.top().get_tipo_nodo() == TipoNodo::VARIABLE){
		// si es una variable, ponemos xN
		// de nuevo, dependiendo de si miramos el nodo de la izquierda o el
		// de la derecha lo ponemos aun ladou a otro
		if (izda){
			resultado = "x" + std::to_string(pila.top().get_valor()) +
							" " + resultado;
		} else {
			resultado = resultado + " x" +
							std::to_string(pila.top().get_valor());
		}

		// eliminamos el nodo y devolvemos el resultado
		pila.pop();
		return resultado;
	} else {

		// sies un operador, obtenemos el valor
		std::string valor;
		if (pila.top().get_tipo_nodo() == TipoNodo::MAS){
			valor = "+";
		} else if (pila.top().get_tipo_nodo() == TipoNodo::MENOS){
			valor = "-";
		} else if (pila.top().get_tipo_nodo() == TipoNodo::POR){
			valor = "*";
		} else if (pila.top().get_tipo_nodo() == TipoNodo::ENTRE){
			valor = "/";
		}


		// eliminamos su nodo
		pila.pop();
		std::string izquierda;
		std::string derecha;

		// miramos la expresion que tienen a la izquierda y a la derecha
		izquierda = obtener_string_expresion(pila, "", true) ;
		derecha = obtener_string_expresion(pila, "", false);

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



std::vector<Nodo> Expresion:: get_arbol () const {
	return arbol_;
}


std::string Expresion :: string_expresion() const {
	std::string resultado = "";

	std::stack<Nodo> pila;

	// volcamos la pila
	for (int i = (int)get_longitud_arbol() - 1; i >= 0; i--){
		pila.push(arbol_[i]);
	}

	// obtenemos el string de toda la pila
	resultado = obtener_string_expresion(pila, resultado, true);

	return resultado;
}

std::ostream & operator<< (std::ostream & os, const Expresion & exp){
	// obtenemos el string y lo sacamos por el flujo
	std::string exp_string = exp.string_expresion();

	os << exp_string;

	return os;
}



void Expresion :: mutar_GP (const int num_vars) {

	numero_variables_ = num_vars;
	int posicion = Random::getInt(arbol_.size());

	float aleatorio = Random::getFloat();

	if ( aleatorio < 0.5) {
		// primera opcion, cambiar un termino por otro
		TipoNodo tipo = arbol_[posicion].get_tipo_nodo();

		if ( tipo == TipoNodo::NUMERO || tipo == TipoNodo::VARIABLE){
			if ( Random::getFloat() < 0.5) {
				arbol_[posicion].set_tipo_nodo(TipoNodo::VARIABLE);
				arbol_[posicion].set_termino_aleatorio(num_vars);
			} else {
				arbol_[posicion].set_tipo_nodo(TipoNodo::NUMERO);
				arbol_[posicion].set_valor_numerico(Random::getFloat(-10.0, 10.0));
			}

		} else {
			arbol_[posicion].set_tipo_nodo_operador_aleatorio();
		}
	} else {
		// generamos un arbol aleatorio en la posicion

		bool cruce_mal;
		Expresion hijo = (*this);

		do {

			Expresion exp_aleatorio(profundidad_maxima_, 0.3, num_vars, profundidad_maxima_);

			cruce_mal = !(intercambiar_subarbol(exp_aleatorio, posicion, 0, hijo));

		} while (cruce_mal);

		asignar_arbol(hijo.arbol_);

	}

}


bool Expresion :: mismo_arbol( const Expresion & otra) const {
	bool resultado = arbol_.size() == otra.arbol_.size();

	for (unsigned i = 0; i < arbol_.size() && resultado; i++){
		resultado = arbol_[i] == otra.arbol_[i];
	}

	return resultado;
}

bool Expresion :: operator == ( const Expresion & otra) const {
	return mismo_arbol(otra);
}

bool Expresion :: operator != ( const Expresion & otra) const {
	return !(*this == otra);
}

bool Expresion :: mejor_fitness (const Expresion & otra) {
	return fitness_ < otra.get_fitness();
}

bool Expresion :: operator < (const Expresion & otra) {
	return mejor_fitness(otra);
}


} // namespace algoritmos_poblacion_expresiones
