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
  *  @brief Clase GA_P
  *
  *  Una instancia del tipo GA_P representará un estimador para los datos dados, utilizando
  * una población de expresiones.
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
		  * Un objeto valido @e rep de la clase GA_P representa un conjunto de datos con sus respectivas etiquetas
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
		  * @brief Poblacion de expresiones con el que aplicaremos el algoritmo GA_P
		  */
		Poblacion poblacion;

		/**
		  * @brief Datos con los que ajustar el algoritmo
		  *
		  */
		static std::vector<std::vector<double> > datos;

		/**
		  * @brief Etiquetas para comprobar el error de la estimación.
		  */
		static std::vector<double> output_datos;

		/**
		  * @brief Leer datos de entrada para el algoritmo
		  *
		  * @param fichero_datos Fichero donde se almacenan los datos
		  * @param char_comentario Caracter que marca que una linea es un comentario y ha de ser ignorada
		  *
		  * @pre Los datos han sido preprocesados y los datos a leer vienen dadas separadas por comas. Cada dato es una linea.
		  *
		  */

		bool leerDatos(const std::string fichero_datos, const char char_comentario);

	public:

		/**
		  * @brief Constructor con dos parámetros
		  *
		  * @param fichero_datos Fichero donde se almacenan los datos
		  * @param char_comentario Caracter que marca que una linea es un comentario y ha de ser ignorada
		  *
		  */

		GA_P(const std::string fichero_datos, const char char_comentario);

		/**
		  * @brief Destructor
		  *
		  */

		~GA_P() = default;

		/**
		  * @brief Obtener el numero de variables de los datos
		  *
		  */

		static int getNumVariables();

		/**
		  * @brief Obtener el numero de datos
		  */

		static int getNumDatos();

		/**
		  * @brief Obtener los datos
		  */
		static std::vector<std::vector<double> > getDatos();

		/**
		  * @brief Obtener las etiquetas asociadas a los datos
		  */

		static std::vector<double> getOutputDatos();

};

#endif
