/**
  * @file GA_P.hpp
  * @brief Fichero cabecera de la clase AlgoritmoPG
  *
  */


#ifndef ALGORITMO_PG_H_INCLUDED
#define ALGORITMO_PG_H_INCLUDED

#include "algoritmos_poblaciones/aux_pg_algs.hpp"

#include "algoritmos_poblaciones/AlgoritmoPoblacion.hpp"


namespace algoritmos_poblaciones {

class AlgoritmoPG : public AlgoritmoPoblacion<Expresion> {
	using AlgoritmoPoblacion<Expresion>::poblacion_;
	using AlgoritmoPoblacion<Expresion>::datos_;
	using AlgoritmoPoblacion<Expresion>::output_datos_;
	using AlgoritmoPoblacion<Expresion>::prof_expresiones_;

	using AlgoritmoPoblacion<Expresion>::leerDatos;
	using AlgoritmoPoblacion<Expresion>::inicializarVacio;
	using AlgoritmoPoblacion<Expresion>::getNumVariables;
	using AlgoritmoPoblacion<Expresion>::getMaxProfExpresiones;
	using AlgoritmoPoblacion<Expresion>::seleccionTorneo;
	using AlgoritmoPoblacion<Expresion>::generarPoblacion;
	using AlgoritmoPoblacion<Expresion>::aplicarElitismo;
	using AlgoritmoPoblacion<Expresion>::aplicarMutacionesGP;
	using AlgoritmoPoblacion<Expresion>::inicializar;


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



#endif
