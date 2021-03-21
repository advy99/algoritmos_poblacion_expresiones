/**
  * @file nodo.hpp
  * @brief Fichero cabecera de la clase Nodo
  *
  */

#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "aux_pg_algs.hpp"

namespace PG_ALGS {

/**
  * @brief Posibles tipos de nodo que utilizaremos en el GA_P
  */

// aqui faltan tipos, tengo que revisar el paper + los que use
enum class TipoNodo {NUMERO, VARIABLE, MAS, MENOS, POR, ENTRE, ELEVADO};

/**
  *  @brief Clase Nodo
  *
  * Una instancia del tipo Nodo sera una representacion del tipo del nodo
  * y un valor de dicho nodo.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

class Nodo {
	private:
		/**
		  * @page repNodo Representación de la estructura nodo
		  *
		  * @section faConjunto Función de abstracción
		  *
		  * Un objeto valido @e rep de la estructura Nodo viene dado por un
		  * tipo de un nodo y su valor.
		  *
		  *
		  * rep.tipo_nodo
		  * rep.valor
		  *
		  */

		/**
		  * @brief Tipo de nodo
		  */
		TipoNodo tipo_nodo;

		/**
		  * @brief Valor asociado al nodo
		  */

		int valor;

	public:

		/**
		 * @brief Constructor sin argumentos. Creamos Nodo vacio.
		 *
		 *
		 */

		Nodo();

		/**
		  * @brief Establecer el tipo del nodo a un operador aleatorio entre los
		  * posibles operadores.
		  *
		  * @pre tipo_nodo != TipoNodo::NUMERO && tipo_nodo != TipoNodo::VARIABLE
		  */


		void setTipoNodoOperadorAleatorio();

		/**
		  * @brief Establecer el valor del nodo a un termino aleatorio.
		  *
		  * @param num_numeros Cantidad de numeros a tener en cuenta para
		  * escoger el valor
		  * @param num_variables Cantidad de variables a tener en cuenta para
		  * escoger el valor.
		  *
		  * @pre tipo_nodo == TipoNodo::NUMERO || tipo_nodo == TipoNodo::VARIABLE
		  */

		void setTerminoAleatorio(const int num_numeros, const int num_variables);

		/**
		 * @brief Obtener el tipo del nodo asociado al Nodo.
		 *
		 * @return Tipo del nodo.
		 *
		 */

		TipoNodo getTipoNodo() const;

		/**
		 * @brief Obtener el valor asociado al Nodo.
		 *
		 * @pre tipo_nodo == TipoNodo::NUMERO || tipo_nodo == TipoNodo::VARIABLE
		 *
		 * @return Valor asociado al nodo
		 */

		int getValor() const;


		/**
		 *
		 * @brief Establecer el tipo del Nodo.
		 *
		 * @param tipo Nuevo tipo del Nodo
		 *
		 *
		 */

		void setTipoNodo(const TipoNodo tipo);


		/**
		 * @brief Establecer el valor del Nodo.
		 *
		 * @pre tipo_nodo == TipoNodo::NUMERO
		 *
		 * @param val Valor a establecer en el Nodo.
		 *
		 */

		void setValor(const double val);


		/**
		 * @brief Operador de comparación con otro Nodo
		 *
		 * @param otro Nodo con el que comparar
		 *
		 * @return Verdadero si ambos objetos Nodo son iguales, falso en caso
		 * contrario
		 */

		bool operator==(const Nodo & otro) const;

		/**
		 * @brief Operador de comparación con otro Nodo
		 *
		 * @param otro Nodo con el que comparar
		 *
		 * @return Verdadero si ambos objetos Nodo son distintos, falso en caso
		 * contrario
		 */

		bool operator!=(const Nodo & otro) const;

};

typedef Nodo * Arbol;

} // namespace PG_ALGS

#endif
