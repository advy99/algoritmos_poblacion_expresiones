/**
  * \@file Nodo.hpp
  * @brief Fichero cabecera de la clase Nodo
  *
  */

#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "algoritmos_poblaciones/aux_pob_algs.hpp"

namespace algoritmos_poblacion_expresiones {

/**
  * @brief Posibles tipos de nodo que utilizaremos
  */

// aqui faltan tipos, tengo que revisar el paper + los que use
enum class TipoNodo {NUMERO, VARIABLE, MAS, MENOS, POR, ENTRE};

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
		  * @page repNodo Representación de la clase nodo
		  *
		  * @section faNodo Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase Nodo viene dado por un
		  * tipo de un nodo y su valor.
		  *
		  *
		  * rep.tipo_nodo_
		  * rep.valor_
		  * rep.valor_numerico_
		  *
		  */

		/**
		  * @brief Tipo de nodo
		  */
		TipoNodo tipo_nodo_;

		/**
		  * @brief Valor de la variable asociado al nodo
		  */

		int valor_;

		/**
		  * @brief Valor numerico asociado al nodo
		  */

		double valor_numerico_;

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


		void set_tipo_nodo_operador_aleatorio();

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

		void set_termino_aleatorio(const int num_numeros, const int num_variables);



		/**
		  * @brief Establecer el valor del nodo a un termino aleatorio.
		  *
		  * @param num_variables Cantidad de variables a tener en cuenta para
		  * escoger el valor.
		  *
		  * @pre tipo_nodo == TipoNodo::VARIABLE
		  */

		void set_termino_aleatorio(const int num_variables);

		/**
		 * @brief Obtener el tipo del nodo asociado al Nodo.
		 *
		 * @return Tipo del nodo.
		 *
		 */

		TipoNodo get_tipo_nodo() const;

		/**
		 * @brief Obtener el valor asociado al Nodo.
		 *
		 * @pre tipo_nodo == TipoNodo::VARIABLE
		 *
		 * @return Valor asociado al nodo
		 */

		int get_valor() const;

		/**
		 * @brief Obtener el valor numerico asociado al Nodo.
		 *
		 * @pre tipo_nodo == TipoNodo::NUMERO
		 *
		 * @return Valor numerico asociado al nodo
		 */

		double get_valor_numerico() const;


		/**
		 * @brief Establecer el valor numerico del Nodo.
		 *
		 * @pre tipo_nodo == TipoNodo::NUMERO
		 *
		 * @param valor Valor numerico a establecer en el Nodo.
		 *
		 */
		void set_valor_numerico(const double valor);


		/**
		 *
		 * @brief Establecer el tipo del Nodo.
		 *
		 * @param tipo Nuevo tipo del Nodo
		 *
		 *
		 */

		void set_tipo_nodo(const TipoNodo tipo);


		/**
		 * @brief Establecer el valor del Nodo.
		 *
		 * @pre tipo_nodo == TipoNodo::NUMERO
		 *
		 * @param val Valor a establecer en el Nodo.
		 *
		 */

		void set_valor(const int val);


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


} // namespace algoritmos_poblacion_expresiones

#endif
