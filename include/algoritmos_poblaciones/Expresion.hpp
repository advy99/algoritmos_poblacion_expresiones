/**
  * \@file Expresion.hpp
  * @brief Fichero cabecera de la clase Expresion
  *
  */

#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED

#include "algoritmos_poblaciones/Nodo.hpp"
#include "algoritmos_poblaciones/aux_pob_algs.hpp"


namespace algoritmos_poblacion_expresiones {

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
	protected:

		/**
		  * @page repExpresion Representación de la clase Expresion
		  *
		  * @section invExpresion Invariante de la representación
		  *
		  * El invariante es; profundidad_maxima > 0
		  *
		  * @section faExpresion Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase Expresion representa
		  * la expresion dada en
		  *
		  * rep.arbol_
		  *
		  * Así como su valor de ajuste en
		  *
		  * rep.fitness_
		  *
		  * Podemos saber si esta evaluada con
		  *
		  * rep.evaluada_
		  *
		  */

		/**
		  * @brief Valor de ajuste de la expresión con ciertos datos con los
		  * que se ha evaluado.
		  */

		double fitness_;

		/**
		  * @brief Atributo para comprobar si es necesario reevaluar la
		  * expresión de nuevo.
		  */

		bool evaluada_;


		/**
		  * @brief Profundidad máxima permitida para el árbol.
		  */
		unsigned profundidad_maxima_;

		/**
		  * @brief Conjunto de nodos que conformarán la expresión.
		  */
		std::vector<Nodo> arbol_;


		/**
		  * @brief Número de variables que puede tomar la expresion, que conforma el conjunto de datos.
		  */
		unsigned numero_variables_;

		/**
		  * @brief Inicializar una expresión vacia.
		  *
		  * @pre La expresión no tiene memoria dinámica reservada.
		  *
		  * @post La expresión queda como una expresión vacia.
		  */

		virtual void inicializarVacia();

		/**
		  * @brief Copiar datos de una expresión dada a la expresión.
		  *
		  * @param otra Expresión de donde copiar los datos.
		  *
		  * @pre La expresión está vacia: arbol == nullptr && cromosoma == nullptr
		  *
		  */

		void copiarDatos(const Expresion & otra);

		/**
		  * @brief Contar los niveles de un árbol de Expresion dado en una pila.
		  *
		  * @param pila Pila donde esta almacenada la Expresion
		  * @param nivel Nivel actual de la expresion
		  *
		  * @return Número de niveles de la expresión
		  */

		unsigned contarNiveles(std::stack<Nodo> & pila, unsigned nivel) const;

		/**
		  * @brief Evaluar la expresión con un dato dado con la pila que contendrá
		  * la expresión.
		  *
		  * @param pila Pila de la expresion por evaluar
		  * @param dato Dato a evaluar
		  *
		  * @return Valor estimado de la regresión para ese dato.
		  */

		double evaluarDato(std::stack<Nodo> & pila,
								 const std::vector<double> & dato) const;

		/**
		  * @brief Obtener el valor numerico del nodo dado
		  *
		  * @param n Nodo del que obtener el valor
		  *
		  * @return Valor numerico del Nodo dado
		  */

		virtual double obtenerNumero(const Nodo & n) const;

		public:

		/**
		  * @brief Constructor con un parámetro, genera una expresión vacia.
		  *
		  * @param prof_max Profundidad máxima de la expresión.
		  *
		  */

		Expresion(const unsigned prof_max = 10);

		/**
		  * @brief Constructor con un parámetro. Crear una expresion a partir del
		  * subarbol dado
		  *
		  * @param subarbol Subarbol para crear la expresion
		  * @param prof_max Profundidad máxima de la Expresion a crear
		  *
		  * @pre subarbol != nullptr
		  */

		Expresion(const std::vector<Nodo> & subarbol, const unsigned prof_max = 10);



		/**
		  * @brief Constructor con dos parámetro, generar una expresión aleatoria.
		  *
		  * @param longitud_max Longitud de la expresión a generar.
		  * @param prob_variable Probabilidad de que un nodo sea una variable.
		  * @param num_vars Numero de variables que podrá usar la expresion
		  * @param prof_max Profundidad máxima de la Expresion a crear
		  *
		  */

		Expresion(const unsigned longitud_max, const double prob_variable,
					 const unsigned num_vars, const unsigned prof_max = 10);

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

		~Expresion() = default;


		/**
		  * @brief Generar la expresión de forma aleatoria.
		  *
		  * @param longitud_max Longitud máxima de la expresión aleatoria
		  * @param prob_variable Probabilidad de que un símbolo terminal
		  * sea una variable y no un número
		  * @param num_variables Número de varíables disponibles para usar
		  * en la expresión
		  *
		  * @return Booleano: True si ha conseguido generar la expresion
		  * correctamente, false en caso contrario
		  */

		virtual bool generarExpresionAleatoria(const unsigned longitud_max,
					 									 	const double prob_variable,
														 	const unsigned num_variables);

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
		 * @brief Dado un arbol, asignar dicho arbol de nodos a la expresion actual
		 *
		 * @param nuevo_arbol Arbol que formará la expresion
		 *
		 *
		 */

		void asignarArbol ( const std::vector<Nodo> & nuevo_arbol);


		/**
		  * @brief Evaluar la expresión con los datos dados.
		  *
		  * @param datos Datos con los que evaluar la expresion
		  * @param etiquetas Etiquetas correspondientes a los datos para evaluar.
		  * @param f_evaluacion Funcion de evaluación a utilizar
		  *
		  * @post fitness = Valor de ajuste de la expresión.
		  */

		void evaluarExpresion(const std::vector<std::vector<double>> & datos,
									 const std::vector<double> & etiquetas,
								 	 funcion_evaluacion_t f_evaluacion);

		/**
		  * @brief Evaluar la expresión con un dato dado.
		  *
		  * @param dato Dato a evaluar
		  *
		  * @return Valor estimado de la regresión para ese dato.
		  */

		double evaluarDato(const std::vector<double> & dato) const ;

		/**
		  * @brief Intercambiar una parte de la expresión por otra dada.
		  *
		  * @param otra Expresion con la que intercambiar.
		  * @param pos Posición del árbol a intercambiar.
		  * @param longitud_cruce Posición de la expresión dada a intercambiar.
		  * @param hijo Expresión donde se almacenará el resultado del cruce.
		  *
		  * @pre otra No es una expresion vacia.
		  *
		  * @return Verdadero si se ha podido realizar el intercambio, falso si no.
		  */

		bool intercambiarSubarbol(const Expresion & otra, const unsigned pos,
										  const unsigned longitud_cruce,
										  Expresion & hijo) const;

		/**
		  * @brief Cruce del arbol entre dos expresiones.
		  *
		  * @param otra Expresion con la que intercambiar.
		  * @param hijo1 Expresión donde se almacenará el resultado del cruce.
		  * @param hijo2 Expresión donde se almacenará el resultado del cruce.
		  *
		  * @pre otra No es una expresion vacia.
		  */


		void cruceArbol(const Expresion & otra, Expresion & hijo1, Expresion & hijo2) const;

		/**
		  * @brief Metodo para marcar que la evaluación del fitness de una
		  * expresión ya no es valida.
		  *
		  */

		void dejaEstarEvaluada();

		/**
		  * @brief Operador de asignación de una expresión. Asignamos una
		  * expresión a otra.
		  *
		  * @param otra Expresión a copiar.
		  *
		  * @return Referencia a la expresion
		  */

		Expresion & operator= (const Expresion & otra);

		/**
		  * @brief Obtener el subarbol dado un punto de un árbol
		  *
		  * @param subarbol Inicio del subarbol a buscar
		  *
		  * @return Expresion con el subarbol
		  */

		std::vector<Nodo> obtenerSubarbol(const std::vector<Nodo> & subarbol, int posicion) const;

		/**
		  * @brief Calcular la profundidad de una expresión
		  *
		  * @param comienzo Nodo por el que comenzar a contar los niveles,
		  * para contar niveles de un subarbol
		  *
		  * @return Profundidad de la expresión a partir del nodo dado
		  */

		unsigned calcularProfundidad(const unsigned comienzo = 0) const;


		/**
		 * @brief Obtener donde está almacenado el arbol
		 *
		 * @return Arbol de la expresion
		 */

		std::vector<Nodo> getArbol() const;

		/**
		 * @brief Comprobar si esta Expresion tiene el mismo Arbol que otra.
		 *
		 * @param otra Expresion con la que comparar el árbol
		 *
		 * @return Verdadero si es el mismo árbol, falso en otro caso.
		 */

		bool mismoArbol( const Expresion & otra) const;


		/**
		  * @brief Funcion para obtener una expresión almacenada en una pila en
		  * preorder en forma de string
		  *
		  * @param pila Contenedor donde esta almacenada la expresión.
		  * @param resultado Resultado parcial al que añadir la nueva lectura de
		  * la pila
		  * @param izda Booleano true nos indica que estamos leyendo una rama
		  * izquierda (va a la parte izquierda del resultado actual)
		  * y en otro caso derecha
		  *
		  * @return Nuevo resultado tras leer la pila
		  */


		std::string obtenerStringExpresion(std::stack<Nodo> & pila,
													  std::string resultado,
													  const bool izda) const;

		/**
		  * @brief Devuelve la cadena asociada a la expresión.
		  *
		  * @return Cadena asociada a la expresión
		  */

		std::string stringExpresion() const;


		/**
		 *
		 *  @brief Mutación de la parte de programación genética (arbol)
		 *
		 *  @param num_vars Numero de variables que puede tomar el arbol
		 *
		 */

		void mutarGP(const int num_vars);


		/**
		 * @brief Operador para comparar si dos expresiones son iguales
		 *
		 * @param otra Expresión a comparar con la actual
		 *
		 * @return Verdadero si la expresion this es igual a otra
		 */

		bool operator== (const Expresion & otra) const;

		/**
		 * @brief Operador para comparar si dos expresiones son distintas
		 *
		 * @param otra Expresión a comparar con la actual
		 *
		 * @return Verdadero si la expresion this es distinta a otra
		 */

		bool operator!= (const Expresion & otra) const;

		/**
		  * @brief Salida por el operador <<
		  *
		  * @param os Flujo de salida por el que mostrar la expresion
		  * @param exp Expresión a mostrar
		  *
		  * @return Referencia al flujo de salida en caso de mostrar varias
		  * expresiones con el mismo flujo.
		  */

		friend std::ostream & operator<< (std::ostream & os,
													 const Expresion & exp);


		/**
		 *
		 * @brief Comprobar si una expresión es menor que otra (con respecto a su ajuste)
		 *
		 */

		 bool mejorFitness (const Expresion & otra);

		 /**
 		 *
 		 * @brief Comprobar si una expresión es menor que otra
 		 *
 		 */

		 bool operator < (const Expresion & otra);

};

} // namespace algoritmos_poblacion_expresiones

#endif
