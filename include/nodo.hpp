/**
  * @file nodo.hpp
  * @brief Fichero cabecera de la estructura Nodo
  *
  */

#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

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

struct {
	TipoNodo tipo_nodo;
	double valor;
} Nodo;

typedef Nodo * Arbol;

#endif
