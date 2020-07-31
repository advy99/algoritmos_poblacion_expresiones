#include "nodo.hpp"

void Nodo::setTerminoAleatorio(const int num_numeros, const int num_variables){
	// si es un numero, escogemos un aleatorio entre todos los posibles valores dados
	if (tipo_nodo == TipoNodo::NUMERO){
		valor = Random::getInstance()->getInt(num_numeros);
	} else {
		// TO-DO
		// si no, escogemos un aleatorio entre las posibles variables
		valor = Random::getInstance()->getInt(num_variables);
	}
}

void Nodo::setTipoNodoOperadorAleatorio(){
	// obtenemos un aleatorio
	float aleatorio = Random::getInstance()->getFloat();

	// le damos la misma probabilidad a cada operador
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
