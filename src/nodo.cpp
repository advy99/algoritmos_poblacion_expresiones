#include "nodo.hpp"

Nodo::Nodo(){
	tipo_nodo = TipoNodo::NUMERO;
	valor = 0;
}

void Nodo::setTerminoAleatorio(const int num_numeros, const int num_variables){
	// si es un numero, escogemos un aleatorio entre todos los posibles valores dados
	if (tipo_nodo == TipoNodo::NUMERO){
		valor = Random::getInt(num_numeros);
	} else {
		// TO-DO
		// si no, escogemos un aleatorio entre las posibles variables
		valor = Random::getInt(num_variables);
	}
}

void Nodo::setTipoNodoOperadorAleatorio(){
	// obtenemos un aleatorio
	float aleatorio = Random::getFloat();

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


bool Nodo::operator==(const Nodo & otro) const {
	bool resultado = false;

	if (this->tipo_nodo == otro.tipo_nodo){
		if (this->tipo_nodo == TipoNodo::NUMERO ||
			 this->tipo_nodo == TipoNodo::VARIABLE){
			// si el tipo es el mismo y es un numero o variable, el valor ha de ser el mismo
			resultado = this->valor == otro.valor;
		} else {
			// si el tipo del nodo es el mismo y es un operador, nos da
			// igual el valor, es el mismo nodo
			resultado = true;
		}
	}
	// si no es el mismo tipo de nodo, no es el mismo nodo


	return resultado;

}
