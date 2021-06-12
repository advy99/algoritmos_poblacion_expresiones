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

	parametros_ejecucion.addFuncionError(algoritmos_poblacion_expresiones::raiz_error_cuadratico_medio);
	parametros_ejecucion.addFuncionError(algoritmos_poblacion_expresiones::error_absoluto_medio);


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


	double error_medio_ecm_gap = 0.0;
	double error_medio_recm_gap = 0.0;
	double error_medio_mae_gap = 0.0;


	std::vector<double> error_it;
	algoritmos_poblacion_expresiones::Expresion_GAP mejor_expresion_gap;

	// ajustamos GAP midiendo tiempo
	auto tiempo_inicio = std::chrono::high_resolution_clock::now();

	const unsigned num_cv = 2;
	const unsigned num_it = 5;

	// hacemos 5x2 cv
	for (unsigned i = 0; i < num_it; i++) {
		auto resultado_cv = myGAP.ajustar_k_cross_validation(num_cv, parametros_ejecucion);

		if ( resultado_cv.first.getFitness() < mejor_expresion_gap.getFitness()) {
			mejor_expresion_gap = resultado_cv.first;
		}

		for ( unsigned i = 0; i < num_cv; i++) {
			error_medio_ecm_gap += resultado_cv.second[0][i];
			error_medio_recm_gap += resultado_cv.second[1][i];
			error_medio_mae_gap += resultado_cv.second[2][i];
		}

	}

	error_medio_ecm_gap /= num_cv * num_it * 1.0;
	error_medio_recm_gap /= num_cv * num_it * 1.0;

	auto tiempo_fin = std::chrono::high_resolution_clock::now();


	std::chrono::duration<double> t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	// mostramos el resultado
	std::cout << semilla_original << "\t"
				 << error_medio_ecm_gap << "\t"
				 << error_medio_recm_gap << "\t"
				 << error_medio_mae_gap << "\t"
				 << mejor_expresion_gap << "\t"
				 << t_ejecucion.count() << "\t GAP" << std::endl;

	// ahora con PG
	Random::setSeed(semilla_original);
	// hacemos lo mismo pero con PG
	algoritmos_poblacion_expresiones::AlgoritmoPG myPG (train_test_split.first.first, train_test_split.first.second, semilla, tam_pob, prof_max_expr, prob_variable);

	double error_medio_ecm_gp = 0.0;
	double error_medio_recm_gp = 0.0;
	double error_medio_mae_gp = 0.0;

	algoritmos_poblacion_expresiones::Expresion mejor_expresion_pg;


	tiempo_inicio = std::chrono::high_resolution_clock::now();

	// hacemos 5x2 cv
	for (unsigned i = 0; i < num_it; i++) {
		auto resultado_cv = myPG.ajustar_k_cross_validation(num_cv, parametros_ejecucion);


		if ( resultado_cv.first.getFitness() < mejor_expresion_pg.getFitness()) {
			mejor_expresion_pg = resultado_cv.first;
		}

		for ( unsigned i = 0; i < num_cv; i++) {
			error_medio_ecm_gp += resultado_cv.second[0][i];
			error_medio_recm_gp += resultado_cv.second[1][i];
			error_medio_mae_gp += resultado_cv.second[2][i];
		}
	}

	error_medio_ecm_gp /= num_cv * num_it * 1.0;
	error_medio_recm_gp /= num_cv * num_it * 1.0;

	tiempo_fin = std::chrono::high_resolution_clock::now();

	t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	std::cout << semilla_original << "\t"
				 << error_medio_ecm_gp << "\t"
				 << error_medio_recm_gp << "\t"
				 << error_medio_mae_gp << "\t"
				 << mejor_expresion_pg << "\t"
				 << t_ejecucion.count() << "\t PG" << std::endl;

	return 0;

}
