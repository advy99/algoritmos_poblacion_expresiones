/**
  * \@file Parametros.hpp
  * @brief Fichero cabecera de la clase Parametros
  *
  */

#ifndef PARAMETROS_H_INCLUDED
#define PARAMETROS_H_INCLUDED


#include "algoritmos_poblaciones/aux_pob_algs.hpp"

namespace algoritmos_poblacion_expresiones {



/**
  *  @brief Clase Parametros
  *
  * Una instancia del tipo Parametros representará los parametros que podemos utilzar
  * para ajustar un AlgoritmoPoblacion
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Abril 2021
  */

class Parametros {
	private:

		/**
		  * @page repParametros Representación de la clase Parametros
		  *
		  * @section faParametros Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase Parametros viene dado por:
		  *
		  *
		  * rep.numero_evaluaciones_
		  * rep.probabilidad_cruce_gp_
		  * rep/numero_evaluaciones_
		  * rep.probabilidad_cruce_gp_
		  * rep.probabilidad_cruce_ga_
		  * rep.probabilidad_mutacion_gp_
		  * rep.probabilidad_mutacion_ga_
		  * rep.tamanio_torneo_
		  * rep.mostrar_evolucion_
		  *
		  */


		/**
		 *
		 *  @brief Numero de evaluaciones con las que ajustar
		 *
		 */

		int numero_evaluaciones_;



		/**
		 *
		 *  @brief Probabilidad de aplicar un cruce en la parte de programación genetica
		 *
		 */

		double probabilidad_cruce_gp_;

		/**
		 *
		 *  @brief Probabilidad de aplicar un cruce en la parte de algoritmo genetico
		 *
		 * @pre Se utiliza el AlgoritmoGA_P
		 */

		double probabilidad_cruce_ga_;

		/**
		 *
		 *  @brief Probabilidad de aplicar una mutacion en la parte de programación genetica
		 *
		 */

		double probabilidad_mutacion_gp_;

		/**
		 *
		 *  @brief Probabilidad de aplicar una mutacion en la parte de algoritmo genetico
		 *
		 * @pre Se utiliza el AlgoritmoGA_P
		 */

		double probabilidad_mutacion_ga_;


		/**
		 *
		 * @brief Probabilidad de aplicar un cruce intra-nicho en GAP
		 *
		 */

		double probabilidad_cruce_intranicho_;

		/**
		 *
		 *  @brief Tamaño del torneo a la hora de ajustar la poblacion
		 *
		 */

		int tamanio_torneo_;

		/**
		 *
		 *  @brief Booleano con el que controlar si se muestra la evolucion del algoritmo
		 *
		 */
		bool mostrar_evolucion_;


		/**
		 *
		 * @brief Puntero a la función de evaluacion a utilizar
		 *
		 */

		 funcion_evaluacion_t funcion_evaluacion_;

	public:

		/**
		 *
		 *  @brief Constructor con siete parámetros
		 *
		 * @param N_EVALS Numero de evaluaciones, por defecto 100000
		 * @param PROB_CRUCE_GP Probabilidad de cruce en la parte de PG, por defecto 0.8
		 * @param PROB_CRUCE_GA Probabilidad de cruce en la parte de GA, por defecto 0.8
		 * @param PROB_MUTA_GP Probabilidad de mutacion en la parte de PG, por defecto 0.01
		 * @param PROB_MUTA_GA Probabilidad de mutacion en la parte de GA, por defecto 0.01
		 * @param PROB_CRUCE_INTRANICHO Probabilidad de cruce intranicho en GA-P, por defecto 0.4
		 * @param TAM_TORNEO Tamaño del torneo, por defecto 15
		 * @param MOSTRAR_EVOLUCION Mostrar evolucion del algoritmo, por defecto si.
		 *
		 */

		Parametros(const int N_EVALS = 100000,
					  funcion_evaluacion_t = algoritmos_poblacion_expresiones::error_cuadratico_medio,
			 		  const double PROB_CRUCE_GP = 0.8,
					  const double PROB_CRUCE_GA = 0.8,
					  const double PROB_MUTA_GP = 0.01,
					  const double PROB_MUTA_GA = 0.01,
					  const double PROB_CRUCE_INTRANICHO = 0.4,
					  const int TAM_TORNEO = 15,
					  const bool MOSTRAR_EVOLUCION = true);


		/**
		 *
		 *  @brief Constructor con cinco parámetros
		 *
		 * @param N_EVALS Numero de evaluaciones, por defecto 100000
		 * @param PROB_CRUCE_GP Probabilidad de cruce en la parte de PG, por defecto 0.8
		 * @param PROB_MUTA_GP Probabilidad de mutacion en la parte de PG, por defecto 0.01
		 * @param TAM_TORNEO Tamaño del torneo, por defecto 15
		 * @param MOSTRAR_EVOLUCION Mostrar evolucion del algoritmo, por defecto si.
		 *
		 */

		Parametros(const int N_EVALS = 100000,
					  funcion_evaluacion_t = algoritmos_poblacion_expresiones::error_cuadratico_medio,
			 		  const double PROB_CRUCE_GP = 0.8,
					  const double PROB_MUTA_GP = 0.1,
					  const int TAM_TORNEO = 15,
					  const bool MOSTRAR_EVOLUCION = false);


		/**
		 *  @brief Obtener el numero de evaluaciones con las que ajustar
		 *  @return Numero de evaluaciones con las que ajustar
		 */

		int getNumeroEvaluaciones() const;

		/**
		 *  @brief Obtener la probabilidad de cruzar la parte GP
		 *  @return Probabilidad de cruzar la parte GP
		 */
		double getProbabilidadCruceGP() const;

		/**
		 *  @brief Obtener la probabilidad de cruzar la parte GA
		 *  @return Probabilidad de cruzar la parte GA
		 */
		double getProbabilidadCruceGA() const;


		/**
		 *  @brief Obtener la probabilidad de mutar la parte GP
		 *  @return Probabilidad de mutar la parte GP
		 */
		double getProbabilidadMutacionGP() const;

		/**
		 *  @brief Obtener la probabilidad de mutar la parte GA
		 *  @return Probabilidad de mutar la parte GA
		 */
		double getProbabilidadMutacionGA() const;

		/**
		 *  @brief Obtener la probabilidad de realizar un cruce intranicho en GA-P
		 *  @return Probabilidad de realizar un cruce intranicho en GA-P
		 */
		double getProbabilidadCruceIntranicho() const;

		/**
		 *  @brief Obtener el tamaño del torneo
		 *  @return Tamaño del torneo
		 */
		int getTamanioTorneo() const;

		/**
		 *  @brief Obtener si se muestra la evolucion
		 *  @return Booleano: verdadero si se muestra la evolucion, falso si no
		 */
		bool getMostrarEvaluacion() const;

		/**
		 *  @brief Obtener la funcion de evaluacion
		 *  @return Puntero a la función de evaluacion a utilizar
		 */
		funcion_evaluacion_t getFuncionEvaluacion() const;

};

}

#endif
