/**
  * \@file preprocesado.hpp
  * @brief Fichero cabecera de las funciones de preprocesado
  *
  */

#ifndef PREPROCESADO_H_INCLUDED
#define PREPROCESADO_H_INCLUDED

#include "algoritmos_poblaciones/aux_pob_algs.hpp"


template <class T>
using matriz = std::vector<std::vector<T>>;


namespace algoritmos_poblacion_expresiones {

/**
 * @brief Separar unos datos y etiquetas dadas en dos conjuntos de entrenamiento y test,
 *  de forma aleatorio o no aleatoria, si COMIENZO != 1
 *
 * @tparam T tipo de los datos a separar
 * @param datos Características a separar
 * @param etiquetas Etiquetas de los datos a separar
 * @param PORCENTAJE_TEST Porcentaje de datos que formaran parte del conjunto de test, por defecto 0.2
 * @param COMIENZO Indice a partir de donde los datos pasaran a ser de test. Si vale -1, se escogeran los
 *  datos de test de forma aleatoria. Por defecto -1
 *
 * @return Pareja de entrenamiento y test. Cada uno de estos es una pareja de datos y etiquetas
 *
 */

template <class T>
std::pair<std::pair<matriz<T>, std::vector<T> >, std::pair<matriz<T>, std::vector<T> > >
	separar_train_test(matriz<T> datos, std::vector<T> etiquetas,
							 const double PORCENTAJE_TEST = 0.2, const int COMIENZO = -1);


/**
  * @brief Leer datos de entrada para el algoritmo
  *
  * @tparam T tipo de los datos a leer
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


/**
  * @brief Escribir datos en un fichero
  *
  * @tparam T tipo de los datos a escribir
  * @param salida Nombre del fichero donde escribir los datos
  * @param datos Datos a escribir
  * @param etiquetas Eiquetas asociadas a los datos dados
  * @param delimitador Caracter que marca como están separados los datos
  *
  */

template <class T>
void escribir_datos(const std::string & salida, const matriz<T> & datos, const std::vector<T> & etiquetas, const char delimitador = ',');


/**
  * @brief Reordenar de forma aleatoria los datos
  *
  * @tparam T tipo de los datos a escribir
  * @param datos Datos a reordenar
  * @param etiquetas Eiquetas asociadas a los datos dados
  *
  * @return Pareja de datos y etiquetas, reordenados de forma aleatoria
  */

template <class T>
std::pair<matriz<T>, std::vector<T> > reordenar_datos_aleatorio (matriz<T> datos, std::vector<T> etiquetas);


}

#include "preprocesado.tpp"

#endif
