#include "expresion.hpp"


void Expresion::Expresion inicializarVacia(){
	arbol = nullptr;
	longitud_arbol = 0;
	evaluada = false;
	fitness = std::numeric_limits<double>::quiet_NaN();
}

Expresion::Expresion(const unsigned prof_maxima){
	inicializarVacio();
	profundidad_maxima = prof_maxima;
}

Expresion::Expresion(const unsigned prof_maxima, const unsigned longitud){

	inicializarVacio();
	profundidad_maxima = prof_maxima;

	generarExpresionAleatoria(longitud);

}

void Expresion::liberarMemoria(){
	if (arbol != nullptr){
		delete [] arbol;
	}

	inicializarVacia();

}

void Expresion::reservarMemoria(const unsigned tam){
	arbol = new Nodo[tam];
}

void Expresion::copiarDatos(const Expresion & otra){
	fitness = otra.fitness;
	evaluada = otra.evaluada;
	longitud_arbol = otra.longitud_arbol;
	profundidad_maxima = otra.profundidad_maxima;

	for (unsigned i = 0; i < longitud_arbol; i++){
		arbol[i] = otra.arbol[i];
	}

}

void Expresion::Expresion(const Expresion & otra){
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
