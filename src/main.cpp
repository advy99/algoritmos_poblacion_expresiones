#include <iostream>
#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"
#include "algoritmos_poblaciones/AlgoritmoPG.hpp"

#include <ctime>
#include "Random.hpp"
#include <chrono>

#ifdef _OPENMP
	#include <omp.h>
#endif


int main(int argc, char ** argv){

	if ( argc < 12 || argc > 14 ) {
		std::cerr << "Error en el número de parámetros\n"
					 << "\t Uso: " << argv[0] << " <fichero_datos> <tam_poblacion> <prob_variable> <profundidad_max> \n"
					 << "\t\t\t" << " <num_evaluaciones> <prob_cruce_gp> <prob_cruce_ga> <prob_mutacion_gp> <prob_mutacion_ga> <prob_cruce_intranicho> <tam_torneo> [num_trabajos] [semilla] "
					 << std::endl;
		exit(-1);
	}

	int semilla;

	if ( argc == 14 ){
		semilla = atoi(argv[13]);
	} else {
		semilla = std::time(nullptr);
	}

	int tam_pob = atoi(argv[2]);
	double prob_variable = atof(argv[3]);
	int prof_max_expr = atoi(argv[4]);
	int evaluaciones = atoi(argv[5]);
	double prob_cruce_gp = atof(argv[6]);
	double prob_cruce_ga = atof(argv[7]);
	double prob_muta_gp = atof(argv[8]);
	double prob_muta_ga = atof(argv[9]);
	double prob_cruce_intra = atof(argv[10]);
	int tam_torneo = atoi(argv[11]);

	int num_trabajos = atoi(argv[12]);

	algoritmos_poblacion_expresiones::Parametros parametros_ejecucion(evaluaciones, algoritmos_poblacion_expresiones::error_cuadratico_medio, prob_cruce_gp,
		 																	  prob_cruce_ga, prob_muta_gp,
																			  prob_muta_ga, prob_cruce_intra,
																			  tam_torneo, false);

	// si utilizamos openMP, establecemos el número de trabajos
	#ifdef _OPENMP
		omp_set_num_threads(num_trabajos);
	#endif

	int semilla_original = semilla;
	Random::setSeed(semilla);
	auto datos = algoritmos_poblacion_expresiones::leer_datos<double>(std::string(argv[1]), '@', ',');
	datos = algoritmos_poblacion_expresiones::reordenar_datos_aleatorio(datos.first, datos.second);
	auto train_test_split = algoritmos_poblacion_expresiones::separar_train_test(datos.first, datos.second);

	algoritmos_poblacion_expresiones::AlgoritmoGA_P myGAP (train_test_split.first.first, train_test_split.first.second, semilla, tam_pob, prof_max_expr, prob_variable);

	// vector con los errores utilizando el error cuadrático medio
	std::vector<double> errores_ecm_gap;

	// vector con los errores utilizando la raiz del error cuadrático medio
	std::vector<double> errores_recm_gap;

	double error_medio_ecm_gap = 0.0;
	double error_medio_recm_gap = 0.0;


	// ajustamos GAP midiendo tiempo
	auto tiempo_inicio = std::chrono::high_resolution_clock::now();

	// hacemos 5x2 cv
	for (unsigned i = 0; i < 5; i++) {
		auto error_fold = myGAP.ajustar_k_cross_validation(2, parametros_ejecucion);

		errores_ecm_gap.push_back(error_fold[0]);
		errores_ecm_gap.push_back(error_fold[1]);

		errores_recm_gap.push_back(std::sqrt(error_fold[0]));
		errores_recm_gap.push_back(std::sqrt(error_fold[1]));

	}

	auto tiempo_fin = std::chrono::high_resolution_clock::now();

	for ( unsigned i = 0; i < errores_ecm_gap.size(); i++) {
		error_medio_ecm_gap += errores_ecm_gap[i];
		error_medio_recm_gap += errores_recm_gap[i];
	}

	error_medio_ecm_gap /= errores_ecm_gap.size();
	error_medio_recm_gap /= errores_recm_gap.size();


	std::chrono::duration<double> t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	// mostramos el resultado
	std::cout << semilla_original << "\t"
				 << error_medio_ecm_gap << "\t"
				 << error_medio_recm_gap << "\t"
				 << myGAP.getMejorIndividuo() << "\t"
				 << t_ejecucion.count() << "\t GAP" << std::endl;

	// ahora con PG
	Random::setSeed(semilla_original);
	// hacemos lo mismo pero con PG
	algoritmos_poblacion_expresiones::AlgoritmoPG myPG (train_test_split.first.first, train_test_split.first.second, semilla, tam_pob, prof_max_expr, prob_variable);

	// vector con los errores utilizando el error cuadrático medio
	std::vector<double> errores_ecm_gp;

	// vector con los errores utilizando la raiz del error cuadrático medio
	std::vector<double> errores_recm_gp;

	double error_medio_ecm_gp = 0.0;
	double error_medio_recm_gp = 0.0;


	tiempo_inicio = std::chrono::high_resolution_clock::now();

	// hacemos 5x2 cv
	for (unsigned i = 0; i < 5; i++) {
		auto error_fold = myPG.ajustar_k_cross_validation(2, parametros_ejecucion);

		errores_ecm_gp.push_back(error_fold[0]);
		errores_ecm_gp.push_back(error_fold[1]);

		errores_recm_gp.push_back(std::sqrt(error_fold[0]));
		errores_recm_gp.push_back(std::sqrt(error_fold[1]));

	}


	tiempo_fin = std::chrono::high_resolution_clock::now();

	for ( unsigned i = 0; i < errores_ecm_gp.size(); i++) {
		error_medio_ecm_gp += errores_ecm_gp[i];
		error_medio_recm_gp += errores_recm_gp[i];
	}

	error_medio_ecm_gp /= errores_ecm_gp.size();
	error_medio_recm_gp /= errores_recm_gp.size();

	t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	std::cout << semilla_original << "\t"
				 << error_medio_ecm_gp << "\t"
				 << error_medio_recm_gp << "\t"
				 << myPG.getMejorIndividuo() << "\t"
				 << t_ejecucion.count() << "\t PG" << std::endl;

	return 0;

}
