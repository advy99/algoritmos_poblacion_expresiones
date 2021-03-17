#ifndef PG_ALG_H_INCLUDED
#define PG_ALG_H_INCLUDED

#include "aux_gap.hpp"

namespace PG_ALGS {

class PG_ALG {
	protected:
		/**
		  * @brief Datos con los que ajustar el algoritmo
		  *
		  */
		std::vector<std::vector<double> > datos;

		/**
		  * @brief Etiquetas para comprobar el error de la estimación.
		  */
		std::vector<double> output_datos;

	public:

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

};



} // namespace PG_ALGS

#endif
