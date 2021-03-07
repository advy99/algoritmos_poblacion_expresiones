#include "aux_gap.hpp"

namespace GA_P {

bool comparar_reales(const double a, const double b, const double epsilon) {
	return fabs(a - b) < epsilon;
}


} // namespace GA_P
