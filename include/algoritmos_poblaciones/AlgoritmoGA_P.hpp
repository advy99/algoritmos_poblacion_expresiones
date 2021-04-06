/**
  * @file AlgoritmoGA_P.hpp
  * @brief Fichero cabecera de la clase AlgoritmoGA_P
  *
  */

#ifndef GA_P_H_INCLUDED
#define GA_P_H_INCLUDED

#include "algoritmos_poblaciones/aux_pg_algs.hpp"
#include "algoritmos_poblaciones/Expresion.hpp"
#include "algoritmos_poblaciones/Poblacion.hpp"
#include "algoritmos_poblaciones/AlgoritmoPoblacion.hpp"
#include "algoritmos_poblaciones/Parametros.hpp"

#include "Random.hpp"

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

class AlgoritmoGA_P : public AlgoritmoPoblacion<Expresion_GAP> {
	private:
		using AlgoritmoPoblacion<Expresion_GAP>::poblacion_;
		using AlgoritmoPoblacion<Expresion_GAP>::datos_;
		using AlgoritmoPoblacion<Expresion_GAP>::output_datos_;
		using AlgoritmoPoblacion<Expresion_GAP>::prof_expresiones_;

		using AlgoritmoPoblacion<Expresion_GAP>::leerDatos;
		using AlgoritmoPoblacion<Expresion_GAP>::inicializarVacio;
		using AlgoritmoPoblacion<Expresion_GAP>::getNumVariables;
		using AlgoritmoPoblacion<Expresion_GAP>::getMaxProfExpresiones;
		using AlgoritmoPoblacion<Expresion_GAP>::seleccionTorneo;
		using AlgoritmoPoblacion<Expresion_GAP>::generarPoblacion;
		using AlgoritmoPoblacion<Expresion_GAP>::aplicarElitismo;
		using AlgoritmoPoblacion<Expresion_GAP>::aplicarMutacionesGP;
		using AlgoritmoPoblacion<Expresion_GAP>::inicializar;

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

		AlgoritmoGA_P(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
			 			  const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var);


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

		void ajustar(const Parametros & parametros) ;

};

} // namespace algoritmos_poblaciones


#endif
