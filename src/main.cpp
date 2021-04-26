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


	auto datos = algoritmos_poblacion_expresiones::leer_datos<double>(std::string(argv[1]), '@', ',');
	auto train_test_split = algoritmos_poblacion_expresiones::separar_train_test(datos.first, datos.second);

	algoritmos_poblacion_expresiones::AlgoritmoGA_P myGAP (train_test_split.first.first, train_test_split.first.second, semilla, tam_pob, prof_max_expr, prob_variable);

	// ajustamos GAP midiendo tiempo
	auto tiempo_inicio = std::chrono::high_resolution_clock::now();

	double error_cross_val = myGAP.ajustar_k_cross_validation(5, parametros_ejecucion);

	auto tiempo_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	// mostramos el resultado
	std::cout << "Tiempo de ejecución con " << num_trabajos << " hilos en una poblacion de " << tam_pob << " individuos con tamaño máximo "
				 << prof_max_expr << " cada individuo y " << evaluaciones << " evaluaciones: " << t_ejecucion.count() << std::endl;


	std::cout << "El mejor individuo de GA_P es: " << std::endl;
	std::cout << myGAP.getMejorIndividuo() << std::endl;
	std::cout << "Con un RMSE (Root Mean Square Error) en validacion cruzada de: " << error_cross_val << std::endl;

	auto predecidos_GAP = myGAP.predecir(train_test_split.second.first);

	double error_test_GAP = algoritmos_poblacion_expresiones::raiz_error_cuadratico_medio(predecidos_GAP, train_test_split.second.second);

	std::cout << "RMSE (Root Mean Square Error) de GA_P sobre el conjunto de test: " << error_test_GAP << std::endl << std::endl;


	// hacemos lo mismo pero con PG
	algoritmos_poblacion_expresiones::AlgoritmoPG myPG (train_test_split.first.first, train_test_split.first.second, semilla, tam_pob, prof_max_expr, prob_variable);

	tiempo_inicio = std::chrono::high_resolution_clock::now();

	error_cross_val = myPG.ajustar_k_cross_validation(5, parametros_ejecucion);

	tiempo_fin = std::chrono::high_resolution_clock::now();

	t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	std::cout << "Tiempo de ejecución con " << num_trabajos << " hilos en una poblacion de " << tam_pob << " individuos con tamaño máximo "
				 << prof_max_expr << " cada individuo y " << evaluaciones << " evaluaciones: " << t_ejecucion.count() << std::endl;


	std::cout << "El mejor individuo de PG es: " << std::endl;
	std::cout << myPG.getMejorIndividuo() << std::endl;
	std::cout << "Con un RMSE (Root Mean Square Error) en validacion cruzada de: " << error_cross_val << std::endl;

	auto predecidos_GP = myPG.predecir(train_test_split.second.first);

	double error_test_GP = algoritmos_poblacion_expresiones::raiz_error_cuadratico_medio(predecidos_GP, train_test_split.second.second);

	std::cout << "RMSE (Root Mean Square Error) de PG sobre el conjunto de test: " << error_test_GP << std::endl;



	return 0;

}
