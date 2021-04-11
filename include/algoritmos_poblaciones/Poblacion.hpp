/**
  * @file poblacion.hpp
  * @brief Fichero cabecera de la clase Poblacion
  *
  */

#ifndef POBLACION_H_INCLUDED
#define POBLACION_H_INCLUDED

#include "algoritmos_poblaciones/aux_pob_algs.hpp"
#include "algoritmos_poblaciones/Expresion.hpp"
#include "algoritmos_poblaciones/Expresion_GAP.hpp"

namespace algoritmos_poblaciones {


/**
  *  @brief Clase Poblacion
  *
  *  Una instancia del tipo Poblacion representará un conjunto de individuos
  *  que serán expresiones, también podrá indicar cual es el mejor
  *  individuo de la población.
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

template <class T>
class Poblacion{
	private:

		/**
		  * @page repPoblacion Representación de la clase Poblacion
		  *
		  * @section invPoblacion Invariante de la representación
		  *
		  * El invariante es; tam_poblacion > 0
		  *
		  * @section faPoblacion Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase Poblacion representa la poblacion
		  *
		  * rep.poblacion
		  *
		  * Así como su mejor individuo en
		  *
		  * rep.mejor_individuo
		  *
		  * Podemos saber el tamaño de la poblacion con
		  *
		  * rep.tam_poblacion
		  *
		  */

		/**
		  * @brief Expresiones que conforman los individuos de la poblacion.
		  *
		  */

		T * expresiones_ = nullptr;


		/**
		  * @brief Tamaño de elementos dentro de la población
		  *
		  *
		  */

		unsigned tam_poblacion_;

		/**
		  * @brief Mejor individuo de la población
		  */
		int mejor_individuo_;

		/**
		  * @brief Reservar memoria para una población de tam individuos.
		  *
		  * @param tam Tamaño a reservar para la poblacion.
		  *
		  */

		void reservarMemoria(const unsigned tam);

		/**
		  * @brief Liberar la memoria dinámica utilizada y limpiar la poblacion.
		  *
		  */
		void liberarMemoria();

		/**
		  * @brief Copiar datos de una poblacion dada a la poblacion.
		  *
		  * @param otra Población de donde copiar los datos.
		  *
		  */

		void copiarDatos(const Poblacion & otra);


		/**
		 * @brief Obtener la suma del fitness de todos los individuos
		 *
		 * @return Sumatoria del fitness de todos los individuos
		 */

		double sumaFitness() const;

	public:

		/**
		  * @brief Constructor con sin parametros, generamos una poblacion vacia.
		  *
		  */

		Poblacion();

		/**
		  * @brief Constructor de copia.
		  *
		  */

		Poblacion(const Poblacion & otra);




		/**
		  * @brief Constructor con dos parámetros. Generar una población
		  * con tam elementos aleatorios.
		  *
		  * @param tam Número de individuos con el que generar la población.
		  * @param lon_expre Longitud máxima de las expresiones a generar
		  * @param prob_var Probabilidad de que un nodo de la expresión sea
		  * una variable.
		  * @param num_vars Número de variables que utilizarán las expresiones
		  * de la población
		  * @param prof_expre Profundidad máxima de las expresiones de
		  * la población
		  *
		  */


		Poblacion(const unsigned tam, const unsigned lon_expre,
					 const double prob_var, const unsigned num_vars,
					 const unsigned prof_expre);

		/**
		  * @brief Destructor de la Población
		  *
		  *
		  */

		~Poblacion();

		/**
		  * @brief Obtener el mejor individuo de la poblacion.
		  *
		  * @return Mejor individuo de la población
		  */

		T getMejorIndividuo() const;

		/**
		  * @brief Obtener el indice del mejor individuo de la poblacion.
		  *
		  * @return Indice del mejor individuo de la población
		  */

		unsigned getIndiceMejorIndividuo() const;

		/**
		  * @brief Obtener el tamaño de la poblacion.
		  *
		  * @return Tamaño de la población
		  */

		unsigned getTamPoblacion() const;

		/**
		  * @brief Obtener el individuo indice de la poblacion.
		  *
		  * @param indice Posición del individuo en la población.
		  *
		  * @return Individuo en la posicion indice de la población.
		  */

		T & operator [] (const unsigned indice);

		/**
		  * @brief Obtener el individuo indice de la poblacion.
		  *
		  * @param indice Posición del individuo en la población.
		  *
		  * @return Individuo en la posicion indice de la población.
		  */

		const T & operator [] (const unsigned indice) const;


		/**
		  * @brief Modificar el individuo en la posición indice de la poblacion
		  * por otro individuo.
		  *
		  * @param indice Posición del individuo a sustituir dentro de
		  * la población.
		  * @param n_individuo Nuevo individuo a introducir en la población.
		  *
		  */

		void setIndividuo(const unsigned indice, const Expresion n_individuo);

		/**
		  * @brief Evaluar todos los elementos de la población.
		  *
		  * @post El mejor individuo de la población se vera actualizado.
		  *
		  */

		void evaluarPoblacion(const std::vector<std::vector<double> > & datos,
									 const std::vector<double> & etiquetas);

		/**
		 * @brief Seleccionar un individuo de la población
		 *
		 *
		 */

		unsigned seleccionIndividuo() const;


		/**
		  * @brief Operador de asignación de una poblacion. Asignamos una
		  * poblacion a otra.
		  *
		  * @param otra Poblacion a copiar.
		  *
		  * @return Referencia a la poblacion.
		  */

		Poblacion & operator= (const Poblacion & otra);

};

} // namespace algoritmos_poblaciones

#include "algoritmos_poblaciones/Poblacion.tpp"



#endif
