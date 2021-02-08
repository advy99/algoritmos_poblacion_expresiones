#include "nodo.hpp"
#include "aux_gap.hpp"

namespace GA_P {

Nodo::Nodo(){
	tipo_nodo = TipoNodo::NUMERO;
	valor = 0;
}

void Nodo::setTerminoAleatorio(const int num_numeros, const int num_variables){
	// si es un numero, escogemos un aleatorio entre todos los posibles valores
	if (tipo_nodo == TipoNodo::NUMERO){
		valor = Random::getFloat(num_numeros);
	} else {
		// si no, escogemos un aleatorio entre las posibles variables
		num_variable = Random::getInt(num_variables);
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


TipoNodo Nodo::getTipoNodo() const {
	return tipo_nodo;
}

int Nodo::getValor() const {
	return valor;
}

void Nodo::setTipoNodo(const TipoNodo tipo){
	tipo_nodo = tipo;
}

void Nodo::setValor(const double val){
	valor = val;
}

void Nodo::setNumVariable(const int n_var) {
	num_variable = n_var;
}

bool Nodo::operator==(const Nodo & otro) const {

	// si no son el mismo tipo, directamente es false
	bool resultado = this->tipo_nodo == otro.tipo_nodo;

	// si es el mismo tipo y es NUMERO comprobamos el valor
	if ( resultado && this->tipo_nodo == TipoNodo::NUMERO ) {
		resultado = comparar_reales(this->valor, otro.valor);

	// si es el mismo tipo y es VARIABLE comprobamos que el numero de variable
	// sea el mismo
	} else if ( resultado && this->tipo_nodo == TipoNodo::VARIABLE) {
		resultado = this->num_variable == otro.num_variable;
	}
	// si el tipo del nodo es el mismo y es un operador, nos da
	// igual el valor, es el mismo nodo

	return resultado;

}

}
