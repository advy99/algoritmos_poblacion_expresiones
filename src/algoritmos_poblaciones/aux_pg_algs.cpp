#include "algoritmos_poblaciones/aux_pg_algs.hpp"

namespace algoritmos_poblaciones {

bool comparar_reales(const double a, const double b, const double epsilon) {
	return fabs(a - b) < epsilon;
}

double raiz_error_cuadratico_medio(const std::vector<double> & valores_predecidos,
											  const std::vector<double> & valores_reales) {
	double resultado = 0.0;
	for ( unsigned i = 0; i < valores_reales.size(); i++ ) {
		resultado += std::pow( valores_predecidos[i] - valores_reales[i] , 2.0);
	}

	resultado = resultado / static_cast<double>(valores_reales.size());

	// resultado = RMSE
	resultado = std::sqrt(resultado);

	return resultado;

}


} // namespace algoritmos_poblaciones
