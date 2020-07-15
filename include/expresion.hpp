/**
  * @file expresion.hpp
  * @brief Fichero cabecera de la clase Expresion
  *
  */

#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED

#include <cmath>
#include "nodo.hpp"

/**
  *  @brief Clase Expresion
  *
  *  Una instancia del tipo Expresion representará una expresión matemática, así
  * como su fitness para unos datos dados.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */

class Expresion{
	private:

		/**
		  * @page repExpresion Representación de la clase Expresion
		  *
		  * @section invExpresion Invariante de la representación
		  *
		  * El invariante es; profundidad_maxima > 0
		  *
		  * @section faConjunto Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase Expresion representa la expresion dada en
		  *
		  * rep.arbol
		  *
		  * Así como su valor de ajuste en
		  *
		  * rep.fitness
		  *
		  * Podemos saber si esta evaluada con
		  *
		  * rep.evaluada
		  *
		  */

		double fitness;
		bool evaluada;
		unsigned longitud_arbol;
		unsigned profundidad_maxima;
		Arbol arbol;

		/**
		  * @brief Inicializar una expresión vacia.
		  *
		  * @pre La expresión no tiene memoria dinámica reservada.
		  *
		  * @post La expresión queda como una expresión vacia.
		  */

		void inicializarVacia();

		/**
		  * @brief Copiar datos de una expresión dada a la expresión.
		  *
		  * @param otra Expresión de donde copiar los datos.
		  *
		  */

		void copiarDatos(const Expresion & otra);


		/**
		  * @brief Reservar memoria para una expresión de tamaño tam
		  *
		  * @param tam Tamaño a reservar para la expresión.
		  *
		  */

		void reservarMemoria(const unsigned tam);

		/**
		  * @brief Liberar la memoria dinámica utilizada y limpiar la expresión.
		  *
		  */

		void liberarMemoria();

		/**
		  * @brief Generar la expresión de forma aleatoria.
		  *
		  * @param longitud Longitud de la expresión aleatoria a generar.
		  *
		  */

		void generarExpresionAleatoria(const unsigned longitud);

	public:

		/**
		  * @brief Constructor con un parámetro, genera una expresión vacia.
		  *
		  * @param prof_maxima Profundidad máxima de la expresión.
		  *
		  */

		Expresion(const unsigned prof_maxima);

		/**
		  * @brief Constructor con dos parámetro, para generar una expresión aleatoria.
		  *
		  * @param prof_maxima Profundidad máxima de la expresión.
		  * @param longitud Longitud de la expresión a generar.
		  *
		  */

		Expresion(const unsigned prof_maxima, const unsigned longitud);

		/**
		  * @brief Constructor de copia.
		  *
		  * @param otra Expresión a copiar.
		  *
		  */

		Expresion(const Expresion & otra);

		/**
		  * @brief Destructor de la expresión.
		  *
		  */

		~Expresion();

		/**
		  * @brief Consultar si la expresión ha sido evaluada tras ser modificada.
		  *
		  * @return Booleano: True si esta evaluada y false si no.
		  */

		bool estaEvaluado() const;

		/**
		  * @brief Obtener el valor de ajuste de la expresión.
		  *
		  * @return Valor de ajuste con los datos con los que se ha evaluado.
		  */

		double getFitness() const;


		/**
		  * @brief Consultar la longitud del árbol.
		  *
		  * @return Longitud del árbol.
		  */

		unsigned getLongitudArbol() const;

		/**
		  * @brief Evaluar la expresión con los datos dados.
		  *
		  * @return Valor de ajuste de la expresión.
		  */

		double evaluar();

		/**
		  * @brief Intercambiar una parte de la expresión por otra dada.
		  *
		  * @param posicion Posición del árbol a intercambiar.
		  * @param subarbol Subárbol a intercambiar.
		  *
		  * @pre subarbol No es un subárbol vacio.
		  */

		void intercambiarSubarbol(const int posicion, Arbol & subarbol);


};


#endif
