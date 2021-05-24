/**
  * \@file AlgoritmoPoblacion.hpp
  * @brief Fichero cabecera de la clase AlgoritmoPoblacion
  *
  */


#ifndef ALGORITMO_POBLACION_H_INCLUDED
#define ALGORITMO_POBLACION_H_INCLUDED

#include "algoritmos_poblaciones/aux_pob_algs.hpp"
#include "algoritmos_poblaciones/Poblacion.hpp"
#include "algoritmos_poblaciones/Parametros.hpp"


/**
 * @brief Clases, definiciones y estructuras necesarias para el AlgoritmoPoblacion
 *
 */

namespace algoritmos_poblacion_expresiones {

/**
  *  @brief Clase AlgoritmoPoblacion
  *
  *  Una instancia del tipo AlgoritmoPoblacion representará un estimador para los datos
  *  dados, utilizando una poblacion del tipo dado.
  *
  * @tparam T Tipo de la población que utilizará el algoritmo
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Abril 2021
  */

template <class T>
class AlgoritmoPoblacion {
	protected:

		/**
		 *  @brief Constructor vacio
		 *
		 */

		AlgoritmoPoblacion ();

		/**
		 *  @brief Método para inicializar el algoritmo de poblacion
		 *
		 *  @param seed Semilla aleatoria a utilizar
		 *  @param tam_poblacion Tamaño de la poblacion del algoritmo
		 *  @param prof Profundidad máxima si la poblacion es de Expresiones
		 *  @param prob_var Probabilidad de que en la poblacion dada un Nodo sea una variable
		 */


		void inicializar(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var);


		/**
		  * @brief Datos con los que ajustar el algoritmo
		  *
		  */
		std::vector<std::vector<double> > datos_;

		/**
		  * @brief Etiquetas para comprobar el error de la estimación.
		  */
		std::vector<double> output_datos_;


		/**
		  * @brief Poblacion de expresiones con el que aplicaremos el algoritmo
		  *
		  */
		Poblacion<T> poblacion_;


		/**
		  * @brief Profundidad máxima de las expresiones si el algoritmo es de expresiones
		  *
		  */

		unsigned prof_expresiones_;

		/**
		  * @brief Probabilidad de que un nodo sea una variable
		  *
		  */

		double probabilidad_variable_;



		/**
		  * @brief Inicializar AlgoritmoPoblacion vacio
		  *
		 */

		void inicializarVacio();

		/**
		 *  @brief Selección de una nueva población por torneo a partir de
		 * la poblacion actual
		 *
		 * @param tam_torneo Tamaño del torneo
		 *
		 * @return Devuelve la poblacion con los T ganadores del torneo.
		 */

		Poblacion<T> seleccionTorneo(const unsigned tam_torneo);


		/**
		 *  @brief Aplicar una mutación en la poblacion si esta es de expresiones
		 *
		 * @param hijo1 Primer hijo al que aplicar la mutacion
		 * @param hijo2 Segundo hijo al que aplicar la mutacion
		 *
		 * @param prob_mutacion Probabilidad con la que aplicar a cada hijo una mutacion
		 *
		 * @return Devuelve una pareja de booleanos, verdadero si se ha aplicado la mutacion, falso si no, uno para cada hijo
		 */

		std::pair<bool, bool> aplicarMutacionesGP(T & hijo1, T & hijo2,
			 													 const double prob_mutacion);

	public:

		/**
		 *  @brief Método para leer los datos con los que entrenar de un fichero
		 *
		 * @param fichero_datos Ruta al fichero donde leer los datos
		 * @param char_comentario Caracter utilizado para comentarios en el fichero de datos
		 * @param delimitador Caracter delimitador entre los datos
		 *
		 *
		 */

		void leerDatos(const std::string fichero_datos,
							const char char_comentario, const char delimitador = ',');

		/**
		  * @brief Cargar vectores de datos y etiquetas en GA_P
		  *
		  * @param caracteristicas Matriz de caracteristicas de cada dato
		  *
		  * @param etiquetas Vector de etiquetas, asociadas a cada fila de la matriz de datos
		  *
		  *
		 */

		void cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas );

		/**
		  * @brief Obtener el numero de variables de los datos
		  *
		  * @return Numero de variables del problema
		  */

		int getNumVariables() const ;

		/**
		  * @brief Obtener el numero de datos
		  *
		  * @return Numero de datos
		  */

		int getNumDatos() const;

		/**
		  * @brief Generar la población en base a los datos cargados
		  *
		  * @param tam_poblacion Tamaño de la poblacion a generar
		  *
		  * @param profundidad_exp Profundidad máxima de las expresiones de la población
		  *
		  * @param prob_var Probabilidad de que un nodo terminal sea una variable
		  *
		  * @param sustituir_actual Booleano para sustituir la población por una nueva, en caso de que ya exista una población
		  *
		  * @pre datos.size != 0
		  *
		  */

		void generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp, const double prob_var, const bool sustituir_actual = false);



		/**
		  * @brief Obtener los datos
		  *
		  * @return Datos.
		  */
		std::vector<std::vector<double> > getDatos() const;


		/**
		  * @brief Obtener el dato de la fila indice
		  *
		  * @param indice Indice del dato a obtener
		  *
		  * @pre indice >= 0 && indice < datos.size
		  *
		  * @return Dato de la columna indice.
		  */
		std::vector<double > getDato(const unsigned indice) const;


		/**
		  * @brief Obtener las etiquetas asociadas a los datos
		  *
		  * @return Etiquetas asociadas a los datos.
		  */

		std::vector<double> getOutputDatos() const;


		/**
		  * @brief Obtener la etiqueta asociada al dato indice
		  *
		  * @param indice Indice de la etiqueta a obtener
		  *
		  * @pre indice >= 0 && indice < output_datos.size
		  *
		  * @return Etiqueta asociada al dato indice.
		  */

		double getOutputDato(const unsigned indice) const ;

		/**
		  * @brief Obtener el mejor individuo de la poblacion.
		  *
		  * @return Mejor individuo de la población
		  */

		T getMejorIndividuo() const;

		/**
		 * @brief Obtener la profundidad máxima de las expresiones
		 *
		 * @return Profundidad máxima de las expresiones
		 */

		unsigned getMaxProfExpresiones() const;


		/**
		 *  @brief Aplicar el elitismo a la poblacion actual
		 *
		 * @param mejor_individuo_anterior Mejor individuo con el que comparar la Poblacion actual
		 *
		 *
		 */

		void aplicarElitismo(const T & mejor_individuo_anterior);

		/**
		 *  @brief Predecir un dato tras entrenar el algoritmo
		 *
		 * @param dato Dato a predecir
		 *
		 * @pre Se ha entrenado el algoritmo
		 *
		 * @return Valor predecido por el algoritmo
		 */

		double predecir(const std::vector<double> & dato) const ;

		/**
		 *  @brief Predecir un conjunto de datos tras entrenar el algoritmo
		 *
		 * @param datos Datos a predecir
		 *
		 * @pre Se ha entrenado el algoritmo
		 *
		 * @return Valores predecido por el algoritmo
		 */

		std::vector<double> predecir(const std::vector<std::vector<double> > & datos) const;

		/**
		 *  @brief Ajustar el algoritmo con unos parametros dados
		 *
		 * @param parametros Parametros con los que ajustar el algoritmo
		 *
		 */

		virtual void ajustar(const Parametros & parametros) = 0;

		/**
		 *  @brief Ajustar el algoritmo con unos parametros dados utilizando validación cruzada
		 *
		 * @param numero_val_cruzada Número de segmentos en los que dividir el conjunto de datos para aplicar validación cruzada
		 * @param parametros Parametros con los que ajustar el algoritmo
		 *
		 * @return Errores obtenido de los folds de validación cruzada
		 */


		std::pair<T, std::vector<double> > ajustar_k_cross_validation(const unsigned numero_val_cruzada, const Parametros & parametros);

};



} // namespace algoritmos_poblacion_expresiones


#include "algoritmos_poblaciones/AlgoritmoPoblacion.tpp"


#endif
