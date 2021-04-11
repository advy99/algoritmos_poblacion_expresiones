/**
  * \@file Parametros.hpp
  * @brief Fichero cabecera de la clase Parametros
  *
  */

#ifndef PARAMETROS_H_INCLUDED
#define PARAMETROS_H_INCLUDED


#include "algoritmos_poblaciones/aux_pob_algs.hpp"

namespace algoritmos_poblaciones {

class Parametros {
	private:
		int numero_evaluaciones_;
		double probabilidad_cruce_gp_;
		double probabilidad_cruce_ga_;
		double probabilidad_mutacion_gp_;
		double probabilidad_mutacion_ga_;
		int tamanio_torneo_;
		bool mostrar_evolucion_;

	public:

		Parametros(const int N_EVALS = 100000,
			 		  const double PROB_CRUCE_GP = 0.8,
					  const double PROB_CRUCE_GA = 0.8,
					  const double PROB_MUTA_GP = 0.1,
					  const double PROB_MUTA_GA = 0.1,
					  const int TAM_TORNEO = 15,
					  const bool MOSTRA_EVOLUCION = true);

		Parametros(const int N_EVALS = 100000,
			 		  const double PROB_CRUCE_GP = 0.8,
					  const double PROB_MUTA_GP = 0.1,
					  const int TAM_TORNEO = 15,
					  const bool MOSTRAR_EVOLUCION = false);

		int getNumeroEvaluaciones() const;
		double getProbabilidadCruceGP() const;
		double getProbabilidadCruceGA() const;

		double getProbabilidadMutacionGP() const;
		double getProbabilidadMutacionGA() const;

		int getTamanioTorneo() const;
		int getMostrarEvaluacion() const;

};

}

#endif
