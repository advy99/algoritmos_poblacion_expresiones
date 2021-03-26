/**
  * @file GA_P.hpp
  * @brief Fichero cabecera de la clase PG
  *
  */


#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include "aux_pg_algs.hpp"

#include "PG_ALG.hpp"


namespace PG_ALGS {

template <class T>
class PG : public PG_ALG<T> {
	using PG_ALG<T>::poblacion;
	using PG_ALG<T>::datos;
	using PG_ALG<T>::output_datos;

	using PG_ALG<T>::leerDatos;
	using PG_ALG<T>::inicializarVacio;
	using PG_ALG<T>::prof_expresiones;
	using PG_ALG<T>::getNumVariables;
	using PG_ALG<T>::getMaxProfExpresiones;
	using PG_ALG<T>::seleccionTorneo;
	using PG_ALG<T>::generarPoblacion;
	using PG_ALG<T>::aplicarElitismo;
	using PG_ALG<T>::aplicarMutacionesGP;


	private:


	public:
		PG(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed = time(nullptr),
			  const char delimitador = ',', const unsigned prof = 20);

		~PG();

		void ajustar(const int num_eval, const double prob_cruce,
						 const double prob_mutacion,
					 	 const int tam_torneo,
					 	 const bool mostrar_evolucion = true);

};

}

#include "PG.tpp"


#endif