#ifndef PREPROCESADO_H_INCLUDED
#define PREPROCESADO_H_INCLUDED

#include "algoritmos_poblaciones/aux_pg_algs.hpp"


template <class T>
using matriz = std::vector<std::vector<T>>;


namespace algoritmos_poblaciones {


template <class T>
std::pair<std::pair<matriz<T>, std::vector<T> >, std::pair<matriz<T>, std::vector<T> > >
	separar_train_test(matriz<T> datos, std::vector<T> etiquetas,
							 const double PORCENTAJE_TEST = 0.2, const int COMIENZO = -1);


/**
  * @brief Leer datos de entrada para el algoritmo
  *
  * @param fichero_datos Fichero donde se almacenan los datos
  * @param char_comentario Caracter que marca que una linea es un
  * comentario y ha de ser ignorada
  * @param delimitador Caracter que marca como están separados los
  * datos de entrada
  *
  * @pre Los datos a leer vienen dados separados por delimitador. Cada dato es una linea.
  *
  * @return Pareja de datos y etiquetas leidas
  *
  */

template <class T>
std::pair<matriz<T>, std::vector<T> >	leer_datos(const std::string & fichero_datos,
				  								  		  const char char_comentario, const char delimitador = ',');

template <class T>
void escribir_datos(const std::string & salida, const matriz<T> & datos, const std::vector<T> & etiquetas, const char delimitador = ',');

template <class T>
void conteo_clases (const std::vector<T> & etiquetas, const std::string & salida);

}

#include "preprocesado.tpp"

#endif
