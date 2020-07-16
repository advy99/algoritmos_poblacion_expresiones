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

		/**
		  * @brief Valor de ajuste de la expresión con ciertos datos con los que se ha evaluado.
		  */

		double fitness;

		/**
		  * @brief Atributo para comprobar si es necesario reevaluar la expresión de nuevo.
		  */

		bool evaluada;

		/**
		  * @brief Longitud del árbol de la expresión.
		  */
		unsigned longitud_arbol;

		/**
		  * @brief Longitud reservada en memoria dinámica para el árbol.
		  */
		unsigned longitud_reservada;

		/**
		  * @brief Profundidad máxima permitida para el árbol.
		  */
		unsigned profundidad_maxima;

		/**
		  * @brief Conjunto de nodos que conformarán la expresión.
		  */
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
		  * @param longitud_max Longitud máxima de la expresión aleatoria a generar.
		  * @param prob_variable Probabilidad de que un símbolo terminal sea una variable y no un número
		  *
		  * @return Booleano: True si ha conseguido generar la expresion correctamente, false en caso contrario
		  */

		bool generarExpresionAleatoria(const unsigned longitud_max,
			 									 const unsigned prob_variable);



		/**
		  * @brief Redimensionar el tamaño de la expresión
		  *
		  * @param tam Nuevo tamaño reservado para la expresion
		  *
		  */
		void redimensionar(const unsigned tam);


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

		bool estaEvaluada() const;

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


		/**
		  * @brief Operador de asignación de una expresión. Asignamos una expresión a otra.
		  *
		  * @param otra Expresión a copiar.
		  *
		  */

		Expresion & operator= (const Expresion & otra);

};


#endif
