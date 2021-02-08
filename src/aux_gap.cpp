#include "aux_gap.hpp"
#include <cmath>

namespace GA_P {

bool comparar_reales(const double a, const double b, const double epsilon) {
	return fabs(a - b) < epsilon;
}


}
