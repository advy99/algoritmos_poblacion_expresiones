/**
  * @file aux_gap.hpp
  * @brief Fichero con funciones auxiliares para el espacio de nombres GA_P
  *
  */

#ifndef AUX_GAP
#define AUX_GAP

#ifdef _OPENMP
	#include <omp.h>
#endif

#include <algorithm>
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



namespace GA_P {

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

}


#endif
