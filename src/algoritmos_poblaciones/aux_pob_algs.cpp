#include "algoritmos_poblaciones/aux_pob_algs.hpp"

namespace algoritmos_poblacion_expresiones {

bool comparar_reales(const double a, const double b, const double epsilon) {
	return fabs(a - b) < epsilon;
}

double error_cuadratico_medio(const std::vector<double> & valores_predecidos,
										const std::vector<double> & valores_reales) {

	double resultado = 0.0;

	for ( unsigned i = 0; i < valores_reales.size(); i++ ) {
		resultado += std::pow( valores_predecidos[i] - valores_reales[i] , 2.0);
	}

	resultado = resultado / static_cast<double>(valores_reales.size());

	return resultado;

}

double raiz_error_cuadratico_medio(const std::vector<double> & valores_predecidos,
											  const std::vector<double> & valores_reales) {

	double resultado = error_cuadratico_medio(valores_predecidos, valores_reales);
	// resultado = RMSE
	resultado = std::sqrt(resultado);

	return resultado;

}

double error_absoluto_medio(const std::vector<double> & valores_predecidos,
									const std::vector<double> & valores_reales) {

	double resultado = 0.0;
	for ( unsigned i = 0; i < valores_reales.size(); i++ ) {
		resultado += std::abs(valores_predecidos[i] - valores_reales[i]);
	}

	resultado = resultado / static_cast<double>(valores_reales.size());

	return resultado;
}


} // namespace algoritmos_poblacion_expresiones
