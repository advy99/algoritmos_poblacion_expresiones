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
		Poblacion * poblacion;

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
		  * @brief Liberar la memoria dinámica utilizada por GA_P
		  */

		void liberarMemoria();

	public:

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
		  * @param delimitador Caracter que marca como están separados los
		  * datos de entrada. Por defecto ','
		  *
		  * @param prof Profundidad máxima de las expresiones con las que
		  * aprenderá el algoritmo. Por defecto 10
		  *
		  * @param seed Semilla al utilizar en GA_P. No tiene efecto si la
		  * la semilla ya ha sido inicializada antes
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
		  * @brief Obtener el numero de variables de los datos
		  *
		  * @return Numero de variables del problema
		  */

		int getNumVariables();

		/**
		  * @brief Obtener el numero de datos
		  *
		  * @return Numero de datos
		  */

		int getNumDatos();

		/**
		  * @brief Obtener los datos
		  *
		  * @return Datos.
		  */
		std::vector<std::vector<double> > getDatos();

		/**
		 * @brief Obtener los datos para solo lectura.
		 *
		 * @return Referencia constante a los datos.
		 *
		 */

		const std::vector<std::vector<double>> & getDatosLectura();

		/**
		  * @brief Obtener el dato de la fila indice
		  *
		  * @param indice Indice del dato a obtener
		  *
		  * @pre indice >= 0 && indice < datos.size
		  *
		  * @return Dato de la columna indice.
		  */
		std::vector<double > getDato(const unsigned indice);


		/**
		 * @brief Obtener un dato para solo lectura.
		 *
		 * @param indice Indice del dato a leer
		 *
		 * @return Referencia constante al dato de la posicion indice.
		 *
		 */

		const std::vector<double > & getDatoLectura(const unsigned indice);



		/**
		  * @brief Obtener las etiquetas asociadas a los datos
		  *
		  * @return Etiquetas asociadas a los datos.
		  */

		std::vector<double> getOutputDatos();


		/**
		 * @brief Obtener las etiquetas para solo lectura.
		 *
		 * @return Referencia constante a las etiquetas.
		 *
		 */

		const std::vector<double> & getOutputDatosLectura();


		/**
		  * @brief Obtener la etiqueta asociada al dato indice
		  *
		  * @param indice Indice de la etiqueta a obtener
		  *
		  * @pre indice >= 0 && indice < output_datos.size
		  *
		  * @return Etiqueta asociada al dato indice.
		  */

		double getOutputDato(const unsigned indice);

		/**
		 * @brief Obtener la profundidad máxima de las expresiones
		 *
		 * @return Profundidad máxima de las expresiones
		 */

		unsigned getMaxProfExpresiones();

};

}

#endif
