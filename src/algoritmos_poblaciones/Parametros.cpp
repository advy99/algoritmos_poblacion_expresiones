#include "algoritmos_poblaciones/Parametros.hpp"


namespace algoritmos_poblaciones {


Parametros :: Parametros(const int N_EVALS,
								  const double PROB_CRUCE_GP,
								  const double PROB_CRUCE_GA,
								  const double PROB_MUTA_GP,
								  const double PROB_MUTA_GA,
								  const int TAM_TORNEO,
								  const bool MOSTRAR_EVOLUCION)
	:numero_evaluaciones_(N_EVALS), probabilidad_cruce_gp_(PROB_CRUCE_GP),
	 probabilidad_cruce_ga_(PROB_CRUCE_GA), probabilidad_mutacion_gp_(PROB_MUTA_GP),
	 probabilidad_mutacion_ga_(PROB_MUTA_GA), tamanio_torneo_(TAM_TORNEO),
	 mostrar_evolucion_(MOSTRAR_EVOLUCION)
	  {}



Parametros :: Parametros(const int N_EVALS,
								  const double PROB_CRUCE_GP,
								  const double PROB_MUTA_GP,
								  const int TAM_TORNEO,
								  const bool MOSTRAR_EVOLUCION)
	:Parametros(N_EVALS, PROB_CRUCE_GP, -1, PROB_MUTA_GP, -1, TAM_TORNEO, MOSTRAR_EVOLUCION)
	  {}



int Parametros :: getNumeroEvaluaciones() const {
	return numero_evaluaciones_;
}
double Parametros :: getProbabilidadCruceGP() const {
	return probabilidad_cruce_gp_;
}
double Parametros :: getProbabilidadCruceGA() const {
	return probabilidad_cruce_ga_;
}

double Parametros :: getProbabilidadMutacionGP() const {
	return probabilidad_mutacion_gp_;
}
double Parametros :: getProbabilidadMutacionGA() const {
	return probabilidad_mutacion_ga_;
}

int Parametros :: getTamanioTorneo() const {
	return tamanio_torneo_;
}
int Parametros :: getMostrarEvaluacion() const {
	return mostrar_evolucion_;
}

}
