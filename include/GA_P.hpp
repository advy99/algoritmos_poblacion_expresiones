/**
  * @file GA_P.hpp
  * @brief Fichero cabecera de la clase GA_P
  *
  */

#ifndef GA_P_H_INCLUDED
#define GA_P_H_INCLUDED

#include <vector>
#include <string>
#include "random.hpp"
#include "expresion.hpp"
#include "poblacion.hpp"

/**
 * @brief Clases, definiciones y estructuras necesarias para el algoritmo GA_P
 *
 */


namespace GA_P {

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

class GA_P{
	private:

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

		/**
		  * @brief Poblacion de expresiones con el que aplicaremos el algoritmo
		  * GA_P
		  */
		Poblacion poblacion;

		/**
		  * @brief Datos con los que ajustar el algoritmo
		  *
		  */
		std::vector<std::vector<double> > datos;

		/**
		  * @brief Etiquetas para comprobar el error de la estimación.
		  */
		std::vector<double> output_datos;

		/**
		  * @brief Profundidad maxima de las expresiones utilizadas
		  *
		  */

		unsigned prof_expresiones;

		/**
		  * @brief Liberar la memoria dinámica utilizada por GA_P
		  */

		void liberarMemoria();

		/**
		  * @brief Inicializar GA_P vacio
		  *
		 */

		 void inicializarVacio();

		/**
		 *  @brief Selección de una nueva población por torneo a partir de
		 * la poblacion actual
		 * 
		 * @param tam_torneo Tamaño del torneo
		 * 
		 */

		 Poblacion seleccionTorneo(const unsigned tam_torneo);

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
			  const char delimitador = ',', const unsigned prof = 10);

		/**
		  * @brief Destructor
		  *
		  */

		~GA_P();

		/**
		  * @brief Leer datos de entrada para el algoritmo
		  *
		  * @param fichero_datos Fichero donde se almacenan los datos
		  * @param char_comentario Caracter que marca que una linea es un
		  * comentario y ha de ser ignorada
		  * @param delimitador Caracter que marca como están separados los
		  * datos de entrada
		  *
		  * @pre Los datos han sido preprocesados y los datos a leer vienen
		  * dados separados por delimitador. Cada dato es una linea.
		  *
		  */

		bool leerDatos(const std::string fichero_datos,
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
		 * @brief Obtener la profundidad máxima de las expresiones
		 *
		 * @return Profundidad máxima de las expresiones
		 */

		unsigned getMaxProfExpresiones() const;

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

}

#endif
