#include "poblacion.hpp"
#include "GA_P.hpp"
#include <cstring>


Poblacion::Poblacion(){
	poblacion = nullptr;
}

Poblacion::Poblacion(const unsigned tam):Poblacion(tam, 0.3){

}

Poblacion::Poblacion(const unsigned tam, const double prob_var){
	poblacion = nullptr;

	liberarMemoria();

	reservarMemoria(tam);
	tam_poblacion = tam;
	for (unsigned i = 0; i < tam; i++){
		poblacion[i] = Expresion(GA_P::getMaxProfExpresiones(), prob_var);
	}
}

Poblacion::~Poblacion(){
	liberarMemoria();
}

void Poblacion::liberarMemoria(){
	if (poblacion != nullptr){
		delete [] poblacion;
	}

	tam_reservado = 0;
	tam_poblacion = 0;
	mejor_individuo = -1;

	poblacion = nullptr;

}

void Poblacion::reservarMemoria(const unsigned tam){
	poblacion = new Expresion[tam];
	tam_reservado = tam;
}

void Poblacion::copiarDatos(const Poblacion & otra){
	tam_poblacion = otra.tam_poblacion;
	mejor_individuo = otra.mejor_individuo;

	for (unsigned i = 0; i < tam_poblacion; i++){
		poblacion[i] = otra.poblacion[i];
	}

}

void Poblacion::evaluarPoblacion(){
	mejor_individuo = 0;
	double valor_mejor = poblacion[mejor_individuo].getFitness();
	double valor_evaluada;

	for ( unsigned i = 0; i < tam_poblacion; i++){
		if (!poblacion[i].estaEvaluada()){
			valor_evaluada = poblacion[i].evaluarExpresion();

			if (valor_evaluada < valor_mejor){
				mejor_individuo = i;
				valor_mejor = valor_evaluada;
			}
		}
	}
}
