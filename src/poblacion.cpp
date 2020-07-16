#include "poblacion.hpp"


void Poblacion::liberarMemoria(){
	if (poblacion != nullptr){
		delete poblacion;
	}

	tam_reservado = 0;
	tam_poblacion = 0;
	mejor_individuo = Expresion();

	poblacion = nullptr;

}

void Poblacion::reservarMemoria(const unsigned tam){
	poblacion = new Expresion[tam];
	tam_reservado = tam;
}

void Poblacion::copiarDatos(const Poblacion & otra){
	tam_poblacion = otra.tam_poblacion;
	mejor_individuo = otra.mejor_individuo;


	memcpy(poblacion, otra.poblacion, otra.tam_poblacion*sizeof(Expresion));

}

void Poblacion::evaluarPoblacion(){
	double valor_mejor = mejor_individuo.getFitness();
	double valor_evaluada;

	for ( unsigned i = 0; i < tam_poblacion; i++){
		if (!poblacion[i].estaEvaluada()){
			valor_evaluada = poblacion[i].evaluar();

			if (valor_evaluada < valor_mejor){
				mejor_individuo = poblacion[i];
				valor_mejor = valor_evaluada;
			}
		}
	}
}
