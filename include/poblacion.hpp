/**
  * @file poblacion.hpp
  * @brief Fichero cabecera de la clase Poblacion
  *
  */

#ifndef POBLACION_H_INCLUDED
#define POBLACION_H_INCLUDED

#include "expresion.hpp"

/**
  *  @brief Clase Poblacion
  *
  *  Una instancia del tipo Poblacion representará un conjunto de individuos que serán expresiones,
  * también podrá indicar cual es el mejor individuo de la población.
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

class Poblacion{
	private:

		/**
		  * @page repPoblacion Representación de la clase Poblacion
		  *
		  * @section invExpresion Invariante de la representación
		  *
		  * El invariante es; tam_poblacion > 0
		  *
		  * @section faConjunto Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase Poblacion representa la poblacion en
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
		  * @brief Puntero donde almacenaremos los individuos de la poblacion.
		  *
		  */

		Expresion * poblacion;


		/**
		  * @brief Tamaño de elementos dentro de la población
		  *
		  *
		  */

		unsigned tam_poblacion;

		/**
		  * @brief Tamaño reservado en memoria para almacenar elementos
		  */

		unsigned tam_reservado;

		/**
		  * @brief Mejor individuo de la población
		  */
		int mejor_individuo;

		/**
		  * @brief Profundidad máxima de los individuos.
		  */
		unsigned prof_individuos;

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

	public:

		/**
		  * @brief Constructor con un parametro, generamos una poblacion vacia.
		  *
		  * @param prof_max Profundidad máxima de las expresiones de la poblacion.
		  */

		Poblacion(const unsigned prof_max = 10);

		/**
		  * @brief Constructor con un parámetro. Generar una población con tam elementos aleatorios.
		  *
		  * @param tam Número de individuos con el que generar la población.
		  * @param prof_max Profundidad máxima de las expresiones de la poblacion.
		  *
		  */

		Poblacion(const unsigned tam, const unsigned prof_max = 10);

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

		Expresion getMejorIndividuo() const;

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
		  * @return Mejor individuo de la población.
		  */

		Expresion getIndividuo(const unsigned indice) const;


		/**
		  * @brief Modificar el individuo en la posición indice de la poblacion por otro individuo.
		  *
		  * @param indice Posición del individuo a sustituir dentro de la población.
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

		void evaluarPoblacion();

};



#endif
