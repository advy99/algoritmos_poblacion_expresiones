#include <iostream>
#include "expresion.hpp"
#include "GA_P.hpp"
#include <cstring>
#include <stack>

Expresion::Expresion(){
	inicializarVacia();
}

void Expresion::inicializarVacia(){
	arbol = nullptr;
	longitud_arbol = 0;
	longitud_reservada = 0;
	evaluada = false;
	fitness = std::numeric_limits<double>::quiet_NaN();
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
	arbol = new Nodo[tam];
	longitud_reservada = 0;
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
	reservarMemoria(tam);
	(*this) = otra;
	longitud_reservada = tam;

}

bool Expresion::generarExpresionAleatoria(const unsigned longitud_maxima,
														const unsigned prob_variable){

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

double Expresion::evaluarDato(std::stack<Nodo> & pila, const std::vector<double> & dato){

	// TO-DO funcion recursiva para evaluar
	double valor = 0.0d;

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
		pila.pop();
		double valor_izda = evaluarDato(pila, dato);
		double valor_dcha = evaluarDato(pila, dato);

		if (pila.top().tipo_nodo == TipoNodo::MAS){
			valor = valor_izda + valor_dcha;

		} else if (pila.top().tipo_nodo == TipoNodo::MENOS){
			valor = valor_izda - valor_dcha;

		} else if (pila.top().tipo_nodo == TipoNodo::POR){
			valor = valor_izda * valor_dcha;

		} else if (pila.top().tipo_nodo == TipoNodo::ENTRE){
			if (son_iguales(valor_dcha, 0.0d) ){
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

	if (!evaluada){
		// TO-DO
		// implementar error cuadratico


		std::stack<Nodo> pila_original;
		std::stack<Nodo> pila;

		// volcamos la expresion en la pila
		for (unsigned i = getLongitudArbol() - 1; i >= 0; i--){
			pila_original.push(arbol[i]);
		}


		for (int i = 0; i < GA_P::getNumDatos(); i++){
			pila = pila_original;
			valor = evaluarDato(pila, GA_P::getDatos()[i]);
			suma += std::pow( std::abs(GA_P::getOutputDatos()[i] - valor ) , 2.0);
		}

		resultado = suma / (double)(GA_P::getNumDatos()*2);
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
