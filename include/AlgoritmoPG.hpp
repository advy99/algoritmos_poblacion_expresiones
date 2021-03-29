/**
  * @file GA_P.hpp
  * @brief Fichero cabecera de la clase AlgoritmoPG
  *
  */


#ifndef ALGORITMO_PG_H_INCLUDED
#define ALGORITMO_PG_H_INCLUDED

#include "aux_pg_algs.hpp"

#include "AlgoritmoPoblacion.hpp"


namespace algoritmos_poblaciones {

template <class T>
class AlgoritmoPG : public AlgoritmoPoblacion<T> {
	using AlgoritmoPoblacion<T>::poblacion;
	using AlgoritmoPoblacion<T>::datos;
	using AlgoritmoPoblacion<T>::output_datos;

	using AlgoritmoPoblacion<T>::leerDatos;
	using AlgoritmoPoblacion<T>::inicializarVacio;
	using AlgoritmoPoblacion<T>::prof_expresiones;
	using AlgoritmoPoblacion<T>::getNumVariables;
	using AlgoritmoPoblacion<T>::getMaxProfExpresiones;
	using AlgoritmoPoblacion<T>::seleccionTorneo;
	using AlgoritmoPoblacion<T>::generarPoblacion;
	using AlgoritmoPoblacion<T>::aplicarElitismo;
	using AlgoritmoPoblacion<T>::aplicarMutacionesGP;
	using AlgoritmoPoblacion<T>::inicializar;


	private:


	public:

		AlgoritmoPG(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var);

		AlgoritmoPG(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed = time(nullptr),
			  const char delimitador = ',', const unsigned prof = 20);

		~AlgoritmoPG();

		void ajustar(const int num_eval, const double prob_cruce,
						 const double prob_mutacion,
					 	 const int tam_torneo,
					 	 const bool mostrar_evolucion = true);

};

}

#include "AlgoritmoPG.tpp"


#endif
