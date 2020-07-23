#include "poblacion.hpp"
#include <cstring>


Poblacion::Poblacion(const unsigned prof_max){
	poblacion = nullptr;
	prof_individuos = prof_max;
}

Poblacion::Poblacion(const unsigned tam, const unsigned prof_max){
	prof_individuos = prof_max;
	poblacion = nullptr;

	liberarMemoria();

	reservarMemoria(tam);
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
