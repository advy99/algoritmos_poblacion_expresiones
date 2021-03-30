#include "algoritmos_poblaciones/aux_pg_algs.hpp"

namespace algoritmos_poblaciones {

bool comparar_reales(const double a, const double b, const double epsilon) {
	return fabs(a - b) < epsilon;
}


} // namespace algoritmos_poblaciones
