#include <iostream>
#include "expresion.hpp"
#include <cstring>

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

double Expresion::evaluar(){

	double resultado = fitness;

	if (!evaluada){
		// TO-DO
		// implementar error cuadratico u otros metodos
	}

	fitness = resultado;
	evaluada = true;

	return resultado;
}

bool Expresion::estaEvaluada() const{
	return evaluada;
}
