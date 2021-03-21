#include "aux_pg_algs.hpp"

namespace PG_ALGS {

bool comparar_reales(const double a, const double b, const double epsilon) {
	return fabs(a - b) < epsilon;
}


} // namespace PG_ALGS
