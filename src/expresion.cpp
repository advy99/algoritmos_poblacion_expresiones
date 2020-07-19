#include <iostream>
#include "expresion.hpp"
#include "GA_P.hpp"
#include <cstring>
#include <stack>

Expresion::Expresion(){
	inicializarVacia();
	profundidad_maxima = 10;
}

Expresion::Expresion(const Arbol subarbol){
	inicializarVacia();
	profundidad_maxima = 10;

	(*this) = obtenerSubarbol(subarbol);

}

Expresion Expresion::obtenerSubarbol(const Arbol subarbol){
	Expresion sol;

	unsigned tam = 0;
	unsigned ramas_libres = 1;

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

	sol.redimensionar(tam);
	for (unsigned i = 0; i < tam; i++){
		sol.arbol[i] = subarbol[i];
	}

	return sol;
}



void Expresion::inicializarVacia(){
	arbol = nullptr;
	longitud_arbol = 0;
	longitud_reservada = 0;
	dejaEstarEvaluada();
}

Expresion::Expresion(const unsigned prof_maxima){
	inicializarVacia();
	profundidad_maxima = prof_maxima;
}

Expresion::Expresion(const unsigned prof_maxima, const unsigned longitud){

	inicializarVacia();
	profundidad_maxima = prof_maxima;

	// la probabilidad es un placeholder
	generarExpresionAleatoria(longitud, 0.3);

}

Expresion::~Expresion(){
	liberarMemoria();
}


void Expresion::liberarMemoria(){
	if (arbol != nullptr){
		delete [] arbol;
	}

	inicializarVacia();

}

void Expresion::reservarMemoria(const unsigned tam){
	if (tam > 0){
		arbol = new Nodo[tam];
	}
	longitud_reservada = tam;
}

void Expresion::copiarDatos(const Expresion & otra){
	fitness = otra.fitness;
	evaluada = otra.evaluada;
	longitud_arbol = otra.longitud_arbol;
	profundidad_maxima = otra.profundidad_maxima;

	memcpy(arbol, otra.arbol, longitud_arbol*sizeof(Nodo));


}

Expresion::Expresion(const Expresion & otra){
	inicializarVacia();
	(*this) = otra;
}

Expresion & Expresion::operator= (const Expresion & otra){
	if (this != &otra){
		liberarMemoria();

		reservarMemoria(otra.longitud_arbol);

		copiarDatos(otra);
	}

	return (*this);

}

void Expresion::redimensionar(const unsigned tam){

	Expresion otra = (*this);
	liberarMemoria();
	reservarMemoria(tam);
	copiarDatos(otra);
	longitud_reservada = tam;

}

bool Expresion::generarExpresionAleatoria(const unsigned longitud_maxima,
														const double prob_variable){

	if (longitud_maxima > longitud_reservada){
		redimensionar(longitud_maxima);
	}

	Random * generador_aleatorios = Random::getInstance();

	unsigned ramas_libres = 1;
	unsigned i = 0;

	while (i < longitud_maxima && ramas_libres > 0){
		float prob_operador = (float)(ramas_libres*ramas_libres+1)/(float)(longitud_maxima-i);

		if (generador_aleatorios->getFloat() > prob_operador){
			arbol[i].setTipoNodoOperadorAleatorio();
			ramas_libres++;

		} else {
			if (generador_aleatorios->getFloat() < prob_variable){
				arbol[i].tipo_nodo = TipoNodo::VARIABLE;
			} else {
				arbol[i].tipo_nodo = TipoNodo::NUMERO;
			}

			arbol[i].setTerminoAleatorio();
			ramas_libres--;
		}
		i++;
	}

	bool exito = ramas_libres == 0;

	if (!exito){
		std::cerr << "Generación incorrecta de expresión aleatoria." << std::endl;
	}

	longitud_arbol = i;
	evaluada = false;
	fitness = std::numeric_limits<double>::quiet_NaN();

	return exito;



}

bool son_iguales(const double & a, const double & b, const double epsilon = 0.005d){
    return (std::fabs(a - b) < epsilon);
}

double Expresion::evaluarDato(std::stack<Nodo> & pila, double & valor, const std::vector<double> & dato){

	// TO-DO funcion recursiva para evaluar

	if (pila.empty()){
		return valor;

	} else if (pila.top().tipo_nodo == TipoNodo::NUMERO){
		valor = pila.top().valor;
		pila.pop();
		return valor;

	} else if (pila.top().tipo_nodo == TipoNodo::VARIABLE){
		valor = dato[pila.top().valor];
		pila.pop();
		return valor;

	} else {
		TipoNodo operacion = pila.top().tipo_nodo;

		pila.pop();
		double valor_izda = evaluarDato(pila, valor, dato);
		double valor_dcha = evaluarDato(pila, valor, dato);

		if (operacion == TipoNodo::MAS){
			valor = valor_izda + valor_dcha;

		} else if (operacion == TipoNodo::MENOS){
			valor = valor_izda - valor_dcha;

		} else if (operacion == TipoNodo::POR){
			valor = valor_izda * valor_dcha;

		} else if (operacion == TipoNodo::ENTRE){
			if (!son_iguales(valor_dcha, 0.0d) ){
				valor = valor_izda / valor_dcha;
			} else {
				valor = 1.0f;
			}
		}

		return valor;

	}

}


double Expresion::evaluarExpresion(){

	double resultado = fitness;

	double valor = 0.0d;
	double suma = 0.0d;

	if (!evaluada && arbol != nullptr){
		// TO-DO
		// implementar error cuadratico


		std::stack<Nodo> pila_original;
		std::stack<Nodo> pila;

		//volcamos la expresion en la pila
		for (int i = (int)getLongitudArbol() - 1; i >= 0; i--){
			pila_original.push(arbol[i]);
		}

		// Nodo n;
		//
		// n.tipo_nodo = TipoNodo::NUMERO;
		// n.valor = 5;
		//
		// pila_original.push(n);
		//
		// n.valor = 3;
		//
		// pila_original.push(n);
		//
		// n.tipo_nodo = TipoNodo::MAS;
		//
		// pila_original.push(n);
		//
		// n.tipo_nodo = TipoNodo::NUMERO;
		// n.valor = 20;
		//
		// pila_original.push(n);
		//
		// n.tipo_nodo = TipoNodo::MENOS;
		// pila_original.push(n);
		//
		// //Pila de prueba: 20 - (3 + 5)
		// pila = pila_original;
		// resultado = 0.0d;
		// evaluarDato(pila, resultado, GA_P::getDatos()[0]);

		for (int i = 0; i < GA_P::getNumDatos(); i++){
			pila = pila_original;
			evaluarDato(pila, valor, GA_P::getDato(i));
			suma += std::pow( GA_P::getOutputDato(i) - valor , 2.0);
		}

		resultado = suma / (double)GA_P::getNumDatos();
	}

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

	Expresion subarbol(&arbol[pos]);
	Expresion subarbol_otra(&otra.arbol[pos]);

	int fin_subarbol = pos + subarbol.getLongitudArbol();
	int fin_otro_surbarbol = pos_otra + subarbol_otra.getLongitudArbol();

	Expresion nueva;

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

	// actualizamos la longitud
	nueva.longitud_arbol = pos_nuevo;

	// nuestro arbol pasa a ser el antiguo
	(*this) = nueva;


	// aplicamos lo mismo a la que nos pasan por referencia
	Expresion nueva_otra;

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
		nueva_otra.arbol[pos_otra_nuevo] = arbol[i];
		pos_otra_nuevo++;
	}

	nueva_otra.longitud_arbol = pos_otra_nuevo;

	otra = nueva_otra;

	dejaEstarEvaluada();
	otra.dejaEstarEvaluada();


}

void Expresion::dejaEstarEvaluada(){
	evaluada = false;
	fitness = std::numeric_limits<double>::quiet_NaN();
}
