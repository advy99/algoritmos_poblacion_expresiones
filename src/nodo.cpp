#include "nodo.hpp"
#include "GA_P.hpp"

void Nodo::setTerminoAleatorio(const int num_numeros, const int num_variables){
	if (tipo_nodo == TipoNodo::NUMERO){
		valor = Random::getInstance()->getInt(num_numeros);
	} else {
		// TO-DO
		valor = Random::getInstance()->getInt(num_variables);
	}
}

void Nodo::setTipoNodoOperadorAleatorio(){
	float aleatorio = Random::getInstance()->getFloat();

	if (aleatorio < 0.25){
		tipo_nodo = TipoNodo::MAS;
	} else if (aleatorio < 0.5) {
		tipo_nodo = TipoNodo::MENOS;
	} else if (aleatorio < 0.75) {
		tipo_nodo = TipoNodo::POR;
	} else {
		tipo_nodo = TipoNodo::ENTRE;
	}
}
