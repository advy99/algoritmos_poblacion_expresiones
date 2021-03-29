/**
  * @file AlgoritmoGA_P.hpp
  * @brief Fichero cabecera de la clase AlgoritmoGA_P
  *
  */

#ifndef GA_P_H_INCLUDED
#define GA_P_H_INCLUDED

#include "aux_pg_algs.hpp"
#include "Random.hpp"
#include "Expresion.hpp"
#include "Poblacion.hpp"

#include "AlgoritmoPoblacion.hpp"

/**
 * @brief Clases, definiciones y estructuras necesarias para el algoritmo AlgoritmoGA_P
 *
 */


namespace algoritmos_poblaciones {

/**
  *  @brief Clase AlgoritmoGA_P
  *
  *  Una instancia del tipo AlgoritmoGA_P representará un estimador para los datos
  *  dados, utilizando una Poblacion, conjunto de Expresion.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

template <class T>
class AlgoritmoGA_P : public AlgoritmoPoblacion<T> {
	private:
		using AlgoritmoPoblacion<T>::poblacion;
		using AlgoritmoPoblacion<T>::datos;
		using AlgoritmoPoblacion<T>::output_datos;

		using AlgoritmoPoblacion<T>::leerDatos;
		using AlgoritmoPoblacion<T>::inicializarVacio;
		using AlgoritmoPoblacion<T>::prof_expresiones;
		using AlgoritmoPoblacion<T>::getNumVariables;
		using AlgoritmoPoblacion<T>::getMaxProfExpresiones;
		using AlgoritmoPoblacion<T>::seleccionTorneo;
		using AlgoritmoPoblacion<T>::generarPoblacion;
		using AlgoritmoPoblacion<T>::aplicarElitismo;
		using AlgoritmoPoblacion<T>::aplicarMutacionesGP;
		using AlgoritmoPoblacion<T>::inicializar;

		/**
		  * @page repGA_P Representación de la clase AlgoritmoGA_P
		  *
		  * @section invGA_P Invariante de la representación
		  *
		  * El invariante es; datos.size > 0 y output_datos.size == datos.size
		  *
		  * @section faConjunto Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase AlgoritmoGA_P representa un conjunto de
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

		AlgoritmoGA_P(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var);


		/**
		  * @brief Constructor con dos parámetros
		  *
		  * @param fichero_datos Fichero donde se almacenan los datos
		  *
		  * @param char_comentario Caracter que marca que una linea es un
		  * comentario y ha de ser ignorada.
		  *
		  * @param tam_poblacion Tamaño de la población que conformará el AlgoritmoGA_P
		  *
		  * @param prob_var Probabilidad de que en una expresión de la población
		  * un nodo hoja sea una variable.
		  *
		  * @param seed Semilla al utilizar en AlgoritmoGA_P. No tiene efecto si la
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

		AlgoritmoGA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed = time(nullptr),
			  const char delimitador = ',', const unsigned prof = 20);

		/**
		  * @brief Destructor
		  *
		  */

		~AlgoritmoGA_P();


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

} // namespace algoritmos_poblaciones


#include "AlgoritmoGA_P.tpp"

#endif
