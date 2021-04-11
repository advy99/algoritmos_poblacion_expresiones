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
#include "Random.hpp"
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
#include <type_traits>


namespace algoritmos_poblaciones {

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

double error_cuadratico_medio(const std::vector<double> & valores_predecidos,
										const std::vector<double> & valores_reales);

double raiz_error_cuadratico_medio(const std::vector<double> & valores_predecidos,
											  const std::vector<double> & valores_reales);

}

#include "preprocesado.hpp"


#endif
