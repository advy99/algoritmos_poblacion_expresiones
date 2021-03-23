/**
  * @file GA_P.hpp
  * @brief Fichero cabecera de la clase GA_P
  *
  */

#ifndef GA_P_H_INCLUDED
#define GA_P_H_INCLUDED

#include "aux_pg_algs.hpp"
#include "random.hpp"
#include "expresion.hpp"
#include "poblacion.hpp"

#include "PG_ALG.hpp"

/**
 * @brief Clases, definiciones y estructuras necesarias para el algoritmo GA_P
 *
 */


namespace PG_ALGS {

/**
  *  @brief Clase GA_P
  *
  *  Una instancia del tipo GA_P representará un estimador para los datos
  *  dados, utilizando una Poblacion, conjunto de Expresion.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

template <class T>
class GA_P : public PG_ALG<T> {
	private:
		using PG_ALG<T>::poblacion;
		using PG_ALG<T>::datos;
		using PG_ALG<T>::output_datos;

		using PG_ALG<T>::leerDatos;
		using PG_ALG<T>::inicializarVacio;
		using PG_ALG<T>::prof_expresiones;
		using PG_ALG<T>::getNumVariables;
		using PG_ALG<T>::getMaxProfExpresiones;
		using PG_ALG<T>::seleccionTorneo;
		using PG_ALG<T>::generarPoblacion;
		using PG_ALG<T>::aplicarElitismo;
		using PG_ALG<T>::aplicarMutacionesGP;

		/**
		  * @page repGA_P Representación de la clase GA_P
		  *
		  * @section invGA_P Invariante de la representación
		  *
		  * El invariante es; datos.size > 0 y output_datos.size == datos.size
		  *
		  * @section faConjunto Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase GA_P representa un conjunto de
		  * datos con sus respectivas etiquetas
		  *
		  * rep.datos
		  * rep.output_datos
		  *
		  * Así como una poblacion de expresiones para estimar los datos.
		  *
		  * rep.poblacion
		  *
		  */

	public:

		/**
		  * @brief Constructor con un parámetro
		  *
		  * @param seed Semilla al utilizar en GA_P. No tiene efecto si la
		  * la semilla ya ha sido inicializada antes
		  */

		GA_P(const unsigned long seed = time(nullptr));

		/**
		  * @brief Constructor con dos parámetros
		  *
		  * @param fichero_datos Fichero donde se almacenan los datos
		  *
		  * @param char_comentario Caracter que marca que una linea es un
		  * comentario y ha de ser ignorada.
		  *
		  * @param tam_poblacion Tamaño de la población que conformará el GA_P
		  *
		  * @param prob_var Probabilidad de que en una expresión de la población
		  * un nodo hoja sea una variable.
		  *
		  * @param seed Semilla al utilizar en GA_P. No tiene efecto si la
		  * la semilla ya ha sido inicializada antes
		  *
		  * @param delimitador Caracter que marca como están separados los
		  * datos de entrada. Por defecto ','
		  *
		  * @param prof Profundidad máxima de las expresiones con las que
		  * aprenderá el algoritmo. Por defecto 10
		  *
		  *
		  */

		GA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed = time(nullptr),
			  const char delimitador = ',', const unsigned prof = 20);

		/**
		  * @brief Destructor
		  *
		  */

		~GA_P();


		/**
		 *  @brief Ajustar la poblacion utilizando los datos actuales
		 *
		 *
		 **/

		void ajustar(const int num_eval, const double prob_cruce_gp,
						 const double prob_cruce_ga,
						 const double prob_mutacion_gp,
						 const double prob_mutacion_ga,
						 const int tam_torneo,
						 const bool mostrar_evolucion = true) ;

};

} // namespace PG_ALGS


#include "GA_P.tpp"

#endif
