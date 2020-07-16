/**
  * @file nodo.hpp
  * @brief Fichero cabecera de la estructura Nodo
  *
  */

#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED


#include "random.hpp"

// aqui faltan tipos, tengo que revisar el paper + los que use
enum class TipoNodo {NUMERO, VARIABLE, MAS, MENOS, POR, ENTRE};

/**
  *  @brief Estructura Nodo
  *
  * Una instancia del tipo Nodo sera una representacion del tipo del nodo y un valor de dicho nodo.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

struct Nodo {

	/**
	  * @page repNodo Representación de la estructura nodo
	  *
	  * @section faConjunto Función de abstracción
	  *
	  * Un objeto valido @e rep de la estructura Nodo viene dado por un tipo de un nodo y su valor.
	  *
	  *
	  * rep.tipo_nodo
	  * rep.valor
	  *
	  */

	TipoNodo tipo_nodo;
	double valor;

	/**
	  * @brief Establecer el tipo del nodo a un operador aleatorio entre los posibles operadores.
	  *
	  */


	void setTipoNodoOperadorAleatorio(){
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

	/**
	  * @brief Establecer el valor del nodo a un termino aleatorio.
	  *
	  * @pre tipo_nodo == TipoNodo::NUMERO || tipo_nodo == TipoNodo::VARIABLE
	  */

	void setTerminoAleatorio(){
		if (tipo_nodo == TipoNodo::NUMERO){
			valor = Random::getInstance()->getFloat(-10.0f, 10.0f);
		} else {
			// TO-DO
			valor = Random::getInstance()->getInt(GA_P::getNumVariables());
		}
	}

};

typedef Nodo * Arbol;

#endif
