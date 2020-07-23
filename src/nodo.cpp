#include "nodo.hpp"
#include "GA_P.hpp"

void Nodo::setTerminoAleatorio(){
	if (tipo_nodo == TipoNodo::NUMERO){
		valor = Random::getInstance()->getInt(GA_P::getMaxProfExpresiones());
	} else {
		// TO-DO
		valor = Random::getInstance()->getInt(GA_P::getNumVariables());
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
