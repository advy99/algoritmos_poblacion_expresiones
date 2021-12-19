/**
  * \@file aux_pob_algs.hpp
  * @brief Fichero con funciones auxiliares para el espacio de nombres GA_P
  *
  */

#ifndef AUX_PG_ALGS
#define AUX_PG_ALGS

#ifdef _OPENMP
	#include <omp.h>
#endif

#include <algorithm>
#include <random>
#include "random.hpp"
#include <cstring>
#include <stack>
#include <limits>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <set>
#include <type_traits>


namespace algoritmos_poblacion_expresiones {

/**
 * @brief Definicion del tipo de la función de evaluacion
 *
 */

typedef double (*funcion_evaluacion_t)(const std::vector<double> & datos, const std::vector<double> & etiquetas);


/**
  * @brief Comparar si dos números reales son iguales teniendo en cuenta la falta
  *   de precisión al representar números reales en C++
  *
  * @param a Número a comparar.
  * @param b Número a comparar.
  * @param epsilon Precisión con la que comparar. Por defecto 0.005
  *
  * @return Booleano: Verdadero si los dos reales son iguales con precisión epsilon
  * falso en otro caso.
  *
  */

bool comparar_reales(const double a, const double b, const double epsilon = 0.005);

/**
  * @brief Calcular el error cuadratico medio entre un conjunto de valores predecidos y valores reales
  *
  * @param valores_predecidos Valores predecidos.
  * @param valores_reales Valores reales.
  *
  * @return Error cuadratico medio entre los valres predecidos y los reales
  *
  */

double error_cuadratico_medio(const std::vector<double> & valores_predecidos,
										const std::vector<double> & valores_reales);

/**
  * @brief Calcular la raiz del error cuadratico medio entre un conjunto de valores predecidos y valores reales
  *
  * @param valores_predecidos Valores predecidos.
  * @param valores_reales Valores reales.
  *
  * @return Raiz del error cuadratico medio entre los valres predecidos y los reales
  *
  */

double raiz_error_cuadratico_medio(const std::vector<double> & valores_predecidos,
											  const std::vector<double> & valores_reales);

/**
 * @brief Calcular el error absoluto medio entre un conjunto de valores predecidos y valores reales
 *
 * @param valores_predecidos Valores predecidos.
 * @param valores_reales Valores reales.
 *
 * @return Error absoluto medio entre los valres predecidos y los reales
 *
 */

double error_absoluto_medio(const std::vector<double> & valores_predecidos,
									const std::vector<double> & valores_reales);


}

#include "preprocesado.hpp"


#endif
