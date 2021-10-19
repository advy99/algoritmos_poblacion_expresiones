#include "algoritmos_poblaciones/Nodo.hpp"

namespace algoritmos_poblacion_expresiones {

Nodo :: Nodo(){
	tipo_nodo_ = TipoNodo::NUMERO;
	valor_ = 0;
	valor_numerico_ = Random::getFloat(-10.0, 10.0);
}

void Nodo :: set_termino_aleatorio(const int num_numeros, const int num_variables){
	// si es un numero, escogemos un aleatorio entre todos los posibles valores
	if (tipo_nodo_ == TipoNodo::NUMERO){
		valor_ = Random::getInt(num_numeros);
	} else {
		// si no, escogemos un aleatorio entre las posibles variables
		valor_ = Random::getInt(num_variables);
	}
}


void Nodo :: set_termino_aleatorio(const int num_variables){
	// si no, escogemos un aleatorio entre las posibles variables
	valor_ = Random::getInt(num_variables);
}

void Nodo :: set_tipo_nodo_operador_aleatorio(){
	// obtenemos un aleatorio
	float aleatorio = Random::getFloat();

	// le damos la misma probabilidad a cada operador
	if (aleatorio < 1.0/4.0){
		tipo_nodo_ = TipoNodo::MAS;
	} else if (aleatorio < 2.0/4.0) {
		tipo_nodo_ = TipoNodo::MENOS;
	} else if (aleatorio < 3.0/4.0) {
		tipo_nodo_ = TipoNodo::POR;
	} else {
		tipo_nodo_ = TipoNodo::ENTRE;
	}
}


TipoNodo Nodo :: get_tipo_nodo() const {
	return tipo_nodo_;
}

int Nodo :: get_valor() const {
	return valor_;
}

double Nodo :: get_valor_numerico() const {
	return valor_numerico_;
}

void Nodo :: set_valor_numerico(const double valor) {
	valor_numerico_ = valor;
}


void Nodo :: set_tipo_nodo(const TipoNodo tipo){
	tipo_nodo_ = tipo;
}

void Nodo :: set_valor(const int val){
	valor_ = val;
}


bool Nodo :: operator==(const Nodo & otro) const {

	// si no son el mismo tipo, directamente es false
	bool resultado = this->tipo_nodo_ == otro.tipo_nodo_;

	// si es el mismo tipo y es NUMERO comprobamos el valor
	if ( resultado && (this->tipo_nodo_ == TipoNodo::NUMERO ||
	 	  this->tipo_nodo_ == TipoNodo::VARIABLE) ) {
		resultado = this->valor_ == otro.valor_;
	}
	// si el tipo del nodo es el mismo y es un operador, nos da
	// igual el valor, es el mismo nodo

	return resultado;

}

bool Nodo :: operator!=(const Nodo & otro) const {
	return !(*this == otro);
}


} // namespace algoritmos_poblacion_expresiones
