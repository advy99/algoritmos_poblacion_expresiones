#include <iostream>
#include "expresion.hpp"
#include "GA_P.hpp"
#include <cstring>
#include <stack>

Expresion::Expresion(){
	// inicilizamos la expresion vacia
	inicializarVacia();

	// establecemos la profundidad a la maxima dada por GA_P
	profundidad_maxima = GA_P::getMaxProfExpresiones();

	// reservamos memoria para el cromosoma
	reservarMemoriaCromosoma(profundidad_maxima);

	// inicializamos el cromosoma de forma aleatoria
	inicializarCromosoma();
}

Expresion::Expresion(const Arbol subarbol){
	// inicializamos la expresion vacia
	inicializarVacia();

	// establecemos la profundidad maxima a la dada por GA_P
	profundidad_maxima = GA_P::getMaxProfExpresiones();

	// obtenemos el subarbol
	(*this) = obtenerSubarbol(subarbol);

}

Expresion::Expresion(const unsigned longitud_max, const double prob_variable){
	inicializarVacia();
	profundidad_maxima = GA_P::getMaxProfExpresiones();

	// reservamos la profundidad maxima
	reservarMemoriaCromosoma(profundidad_maxima);

	// inicializamos el cromosoma el cromosoma
	inicializarCromosoma();

	// generamos una expresion aleatoria
	generarExpresionAleatoria(longitud_max, prob_variable);
}

void Expresion::inicializarCromosoma(){
	// para cada elemento del cromosoma escogemos un numero aleatorio en [-10, 10]
	for (unsigned i = 0; i < longitud_cromosoma; i++){
		cromosoma[i] = Random::getInstance()->getFloat(-10.0f, 10.0f);
	}

}

Expresion Expresion::obtenerSubarbol(const Arbol subarbol){
	Expresion sol;

	unsigned tam = 0;

	// al principio comenzamos con un nodo
	unsigned ramas_libres = 1;

	// mientras tenga ramas que visitar
	while(ramas_libres > 0){
		// si no es ni un numero ni una variable
		if (subarbol[tam].tipo_nodo != TipoNodo::NUMERO &&
			 subarbol[tam].tipo_nodo != TipoNodo::VARIABLE){
			// es un operador, tiene dos ramas
			ramas_libres += 2;
		}
		// en todo caso, he visitado ese nodo, y el tamaño se incrementa en uno
		ramas_libres--;
		tam++;
	}

	// una vez sabemos el tamaño, redimensionamos la solucion
	sol.redimensionar(tam);

	// copiamos el subarbol
	for (unsigned i = 0; i < tam; i++){
		sol.arbol[i] = subarbol[i];
	}

	// actualizamos la longitud de la solucion
	sol.longitud_arbol = tam;

	// y la devolvemos
	return sol;
}



void Expresion::inicializarVacia(){
	// una expresion vacia no tiene arbol
	arbol              = nullptr;
	cromosoma          = 0;
	longitud_cromosoma = GA_P::getMaxProfExpresiones();
	longitud_arbol     = 0;
	longitud_reservada = 0;
	dejaEstarEvaluada();
}



Expresion::~Expresion(){
	liberarMemoria();
}


void Expresion::liberarMemoria(){
	// si el arbol tiene asociado alguna direccion de memoria
	if (arbol != nullptr){
		// la liberamos
		delete [] arbol;
	}

	// y lo mismo con el cromosoma
	if (cromosoma != nullptr){
		delete [] cromosoma;
	}

	// una vez esta liberada la memoria, la expresion esta vacia, luego
	// la ponemos a vacio
	inicializarVacia();

}

void Expresion::reservarMemoriaArbol(const int tam){
	// en todo caso la longitud reservada es cero
	longitud_reservada = 0;

	// si el tamaño es mayor que 0, reservamos, si no se queda a cero
	if (tam > 0){
		arbol = new Nodo[tam];
		longitud_reservada = tam;
	}
}

void Expresion::reservarMemoriaCromosoma(const int tam){
	if (tam > 0){
		cromosoma = new double[tam];
	}
	longitud_cromosoma = tam;
}

void Expresion::copiarDatos(const Expresion & otra){
	// copiamos todos los valores
	fitness            = otra.fitness;
	evaluada           = otra.evaluada;
	longitud_arbol     = otra.longitud_arbol;
	profundidad_maxima = otra.profundidad_maxima;
	longitud_cromosoma = otra.longitud_cromosoma;

	// el array, al ser de elementos basicos sin memoria dinamica, podemos usar memcpy
	memcpy(arbol, otra.arbol, longitud_arbol*sizeof(Nodo));

	// copiamos el cromosoma de la otra expresion
	copiarCromosoma(otra.cromosoma);
}

void Expresion::copiarCromosoma(const double * otro_cromosoma){
	// el cromosoma, al ser reales, podemos copiarlo con memcpy
	memcpy(cromosoma, otro_cromosoma, longitud_cromosoma*sizeof(double));
}

Expresion::Expresion(const Expresion & otra){
	// inicializamos vacia
	inicializarVacia();

	// copiamos la otra con el operador = ya implementado
	(*this) = otra;
}

Expresion & Expresion::operator= (const Expresion & otra){
	// si no es ella misma
	if (this != &otra){
		// liberamos la memoria de la actual
		liberarMemoria();

		// reservamos memoria para el arbol y el cromosoma
		reservarMemoriaArbol(otra.longitud_arbol);
		reservarMemoriaCromosoma(otra.longitud_cromosoma);

		// copiamos los datos de la otra
		copiarDatos(otra);
	}

	// devolvemos el objeto actual
	return (*this);

}

void Expresion::redimensionar(const int tam){

	// guardamos la expresion actual
	Expresion otra = (*this);

	// liberamos la memoria
	liberarMemoria();

	// reservamos con el nuevo tamaño
	reservarMemoriaArbol(tam);
	reservarMemoriaCromosoma(otra.profundidad_maxima);

	// copiamos como estaba
	copiarDatos(otra);

	// y cambiamos la longitud reservada
	longitud_reservada = tam;

}

bool Expresion::generarExpresionAleatoria(const unsigned longitud_maxima,
														const double prob_variable){

	// si no tenemos espacio, redimensionamos
	if (longitud_maxima > longitud_reservada){
		redimensionar(longitud_maxima);
	}

	// obtenemos la instancia del generador de aleatorios
	Random * generador_aleatorios = Random::getInstance();

	// comenzamos con una rama libre
	int ramas_libres = 1;
	unsigned i = 0;

	// mientras tengamos longitud y tengamos ramas sueltas
	while (i < longitud_maxima && ramas_libres > 0){
		// obtenemos la probabilidad de que sea un operador
		float prob_operador = (float)(ramas_libres*ramas_libres+1)/(float)(longitud_maxima-i);

		// si es un operador, lo generamos
		if (generador_aleatorios->getFloat() > prob_operador){
			arbol[i].setTipoNodoOperadorAleatorio();
			// tenemos una rama más libre, la actual que sería el termino de la izquierda
			// y una más para el termino de la derecha
			ramas_libres++;

		} else {
			// si es un simbolo terminal, generamos un aleatorio para ver si es variable o numero
			if (generador_aleatorios->getFloat() < prob_variable){
				arbol[i].tipo_nodo = TipoNodo::VARIABLE;
			} else {
				arbol[i].tipo_nodo = TipoNodo::NUMERO;
			}

			// generamos el termino aleatorio entre los posibles valores, ya sean
			// una variable o un numero
			arbol[i].setTerminoAleatorio(longitud_cromosoma, GA_P::getNumVariables());

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
	longitud_arbol = i;
	dejaEstarEvaluada();

	return exito;



}

bool son_iguales(const double & a, const double & b, const double epsilon = 0.005){
    return (std::fabs(a - b) < epsilon);
}

double Expresion::evaluarDato(std::stack<Nodo> & pila, double & valor, const std::vector<double> & dato){

	// si la pila esta vacia, devolvemos el valor
	if (pila.empty()){
		return valor;

	} else if (pila.top().tipo_nodo == TipoNodo::NUMERO){
		// si el tope de la pila es un nodo de tipo Numero, miramos su valor en la
		// posicion del cromosoma correspondiente
		valor = cromosoma[pila.top().valor];

		// eliminamos de la pila, y lo devolvemos
		pila.pop();
		return valor;

	} else if (pila.top().tipo_nodo == TipoNodo::VARIABLE){
		// si es una variable, la consultamos en el dato dado, eliminamos el nodo
		// de la pila y devolvemos el valor del dato
		valor = dato[pila.top().valor];
		pila.pop();
		return valor;

	} else {
		// si es un operador, guardamos la operacion
		TipoNodo operacion = pila.top().tipo_nodo;

		// la eliminamos de la pila
		pila.pop();

		// consultamos el valor de la rama izquierda y la derecha
		double valor_izda = evaluarDato(pila, valor, dato);
		double valor_dcha = evaluarDato(pila, valor, dato);

		// aplicamos el operador con ambas ramas y devolvemos el resultado
		if (operacion == TipoNodo::MAS){
			valor = valor_izda + valor_dcha;

		} else if (operacion == TipoNodo::MENOS){
			valor = valor_izda - valor_dcha;

		} else if (operacion == TipoNodo::POR){
			valor = valor_izda * valor_dcha;

		} else if (operacion == TipoNodo::ENTRE){
			if (!son_iguales(valor_dcha, 0.0) ){
				valor = valor_izda / valor_dcha;
			} else {
				valor = 1.0f;
			}
		}

		return valor;

	}

}


double Expresion::evaluarExpresion(const std::vector<std::vector<double>> & datos, const std::vector<double> & etiquetas){

	// almacenamos como resultado el valor de fitness
	double resultado = fitness;

	double valor = 0.0;
	double suma = 0.0;

	// si no esta evaluada y el arbol contiene una expresion
	if (!evaluada && arbol != nullptr){
		// implementar error cuadratico

		// pilas donde almacenaremos la expresion
		std::stack<Nodo> pila_original;
		std::stack<Nodo> pila;

		//volcamos la expresion en la pila
		for (int i = (int)getLongitudArbol() - 1; i >= 0; i--){
			pila_original.push(arbol[i]);
		}

		// para cada dato
		for (unsigned i = 0; i < datos.size(); i++){
			// reseteamos la pila con la expresion
			pila = pila_original;

			// la evaluamos para el dato i
			evaluarDato(pila, valor, datos[i]);

			// lo sumamos al cuadrado
			suma += std::pow( etiquetas[i] - valor , 2.0);
		}

		// hacemos la media de los cuadrados
		resultado = suma / (double)datos.size();
	}

	// actualizamos el fitness y que esta evaluada y devolvemos el resultado
	fitness = resultado;
	evaluada = true;

	return resultado;
}

bool Expresion::estaEvaluada() const{
	return evaluada;
}

double Expresion::getFitness() const{
	return fitness;
}

unsigned Expresion::getLongitudArbol() const{
	return longitud_arbol;
}



void Expresion::intercambiarSubarbol(const unsigned pos, Expresion & otra, const unsigned pos_otra){

	// obtenemos el subarbol de la expresion actual
	Expresion subarbol(&arbol[pos]);

	// obtenemos el subarbol de la otra expresion
	Expresion subarbol_otra(&otra.arbol[pos_otra]);

	// copiamos los cromosomas para mantenerlos
	subarbol.copiarCromosoma(cromosoma);
	subarbol_otra.copiarCromosoma(cromosoma);


	// calculamos donde acaba cada subarbol en el arbol general
	int fin_subarbol = pos + subarbol.getLongitudArbol();
	int fin_otro_surbarbol = pos_otra + subarbol_otra.getLongitudArbol();

	// creamos la nueva expresion
	Expresion nueva;
	nueva.copiarCromosoma(cromosoma);


	// la nueva tendra dimension la actual, menos el subarbol que eliminamos más el subarbol que añadimos
	nueva.redimensionar(pos + subarbol_otra.getLongitudArbol() + (*this).getLongitudArbol() - fin_subarbol);


	// copiamos la parte que dejamos igual
	for (unsigned i = 0; i < pos; i++){
		nueva.arbol[i] = arbol[i];
	}

	// insertamos la parte del otro subarbol
	for (unsigned i = 0; i < subarbol_otra.getLongitudArbol(); i++){
		nueva.arbol[i + pos] = subarbol_otra.arbol[i];
	}

	// copiamos la parte final del arbol original
	unsigned pos_nuevo = pos + subarbol_otra.getLongitudArbol();
	for (unsigned i = fin_subarbol; i < (*this).getLongitudArbol(); i++){
		nueva.arbol[pos_nuevo] = arbol[i];
		pos_nuevo++;
	}


	// aplicamos lo mismo a la que nos pasan por referencia
	Expresion nueva_otra;
	nueva_otra.copiarCromosoma(otra.cromosoma);


	nueva_otra.redimensionar(pos_otra + subarbol.getLongitudArbol() + otra.getLongitudArbol() - fin_otro_surbarbol);

	// copiamos la parte que dejamos igual
	for (unsigned i = 0; i < pos_otra; i++){
		nueva_otra.arbol[i] = otra.arbol[i];
	}

	// insertamos la parte del otro subarbol
	for (unsigned i = 0; i < subarbol.getLongitudArbol(); i++){
		nueva_otra.arbol[i + pos_otra] = subarbol.arbol[i];
	}

	unsigned pos_otra_nuevo = pos_otra + subarbol.getLongitudArbol();
	for (unsigned i = fin_otro_surbarbol; i < otra.getLongitudArbol(); i++){
		nueva_otra.arbol[pos_otra_nuevo] = otra.arbol[i];
		pos_otra_nuevo++;
	}

	// los intercambiamos al final

	// actualizamos la longitud
	nueva.longitud_arbol = pos_nuevo;

	// nuestro arbol pasa a ser el antiguo
	(*this) = nueva;

	nueva_otra.longitud_arbol = pos_otra_nuevo;

	otra = nueva_otra;

	// ambas dejan de estar evaluadas
	dejaEstarEvaluada();
	otra.dejaEstarEvaluada();


}

void Expresion::dejaEstarEvaluada(){
	// ponemos la flag a false y establecemos el fitness a NaN
	evaluada = false;
	fitness = std::numeric_limits<double>::quiet_NaN();
}


unsigned Expresion::contarNiveles(std::stack<Nodo> & pila, unsigned nivel) const{
	// si la pila esta vacia, devolvemos el nivel actual
	if (pila.empty()){
		return nivel;
	} else if (pila.top().tipo_nodo == TipoNodo::NUMERO || pila.top().tipo_nodo == TipoNodo::VARIABLE) {
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

unsigned Expresion::calcularProfundidad(const unsigned comienzo) const {

	unsigned profundidad = 0;
	std::stack<Nodo> pila;

	//volcamos la expresion en la pila
	for (int i = (int)getLongitudArbol() - 1; i >= (int)comienzo; i--){
		pila.push(arbol[i]);
	}
	// contamos los niveles de toda la pila
	profundidad = contarNiveles(pila, profundidad);


	return profundidad;

}




void Expresion::cruceBLXalfa(Expresion & otra){

	if ( otra.longitud_cromosoma != this->longitud_cromosoma ) {
		std::cerr << "Cruzando dos cromosomas de distinta longitud" << std::endl;
	}

	double * cromosoma_actual = new double[this->longitud_cromosoma];
	double * cromosoma_otro = new double[otra.longitud_cromosoma];

	// TODO: Implementar el cruce BLX




	this->copiarCromosoma(cromosoma_actual);
	otra.copiarCromosoma(cromosoma_otro);

	delete [] cromosoma_actual;
	delete [] cromosoma_otro;
}



std::string Expresion::obtenerStringExpresion(std::stack<Nodo> & pila, std::string resultado, const bool izda) const{
	// si la pila esta vacia, devolvemos el resultado
	if (pila.empty()){
		return resultado;
	} else if (pila.top().tipo_nodo == TipoNodo::NUMERO){
		// si es un numero, lo consultamos en el cromosoma
		// dependiendo de si estamos mirando el nodo de la izquierda o de la derecha
		// ponemos primero el numero y lo que llevamos
		// o lo que llevamos y el numero
		if (izda){
			resultado = std::to_string(cromosoma[pila.top().valor]) + " " + resultado;
		} else {
			resultado = resultado + " " + std::to_string(cromosoma[pila.top().valor]);
		}

		// eliminamos el nodo de la pila y devolvemos el resultado
		pila.pop();
		return resultado;

	} else if (pila.top().tipo_nodo == TipoNodo::VARIABLE){
		// si es una variable, ponemos xN
		// de nuevo, dependiendo de si miramos el nodo de la izquierda o el de la derecha
		// lo ponemos aun ladou a otro
		if (izda){
			resultado = "x" + std::to_string((int)pila.top().valor) + " " + resultado;
		} else {
			resultado = resultado + " x" + std::to_string((int)pila.top().valor);
		}

		// eliminamos el nodo y devolvemos el resultado
		pila.pop();
		return resultado;
	} else {

		// sies un operador, obtenemos el valor
		std::string valor;
		if (pila.top().tipo_nodo == TipoNodo::MAS){
			valor = "+";
		} else if (pila.top().tipo_nodo == TipoNodo::MENOS){
			valor = "-";
		} else if (pila.top().tipo_nodo == TipoNodo::POR){
			valor = "*";
		} else if (pila.top().tipo_nodo == TipoNodo::ENTRE){
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

std::string Expresion::stringExpresion() const {
	std::string resultado = "";

	std::stack<Nodo> pila;

	// volcamos la pila
	for (int i = (int)getLongitudArbol() - 1; i >= 0; i--){
		pila.push(arbol[i]);
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
