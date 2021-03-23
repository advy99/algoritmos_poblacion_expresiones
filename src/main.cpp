#include <iostream>
#include "GA_P.hpp"
#include <ctime>
#include "random.hpp"
#include <chrono>

#ifdef _OPENMP
	#include <omp.h>
#endif


int main(int argc, char ** argv){

	if ( argc < 11 || argc > 13 ) {
		std::cerr << "Error en el número de parámetros\n"
					 << "\t Uso: " << argv[0] << " <fichero_datos> <tam_poblacion> <prob_variable> <profundidad_max> \n"
					 << "\t\t\t" << " <num_evaluaciones> <prob_cruce_gp> <prob_cruce_ga> <prob_mutacion_gp> <prob_mutacion_ga> <tam_torneo> [num_trabajos] [semilla] "
					 << std::endl;
		exit(-1);
	}

	int semilla;

	if ( argc == 13 ){
		semilla = atoi(argv[12]);
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
	int tam_torneo = atoi(argv[10]);

	int num_trabajos = atoi(argv[11]);


	// si utilizamos openMP, establecemos el número de trabajos
	#ifdef _OPENMP
		omp_set_num_threads(num_trabajos);
	#endif

	PG_ALGS::GA_P<PG_ALGS::Expresion_GAP> myGAP (std::string(argv[1]), '@', tam_pob, prob_variable, semilla, ',', prof_max_expr);

	auto tiempo_inicio = std::chrono::high_resolution_clock::now();

	myGAP.ajustar(evaluaciones, prob_cruce_gp, prob_cruce_ga, prob_muta_gp, prob_muta_ga, tam_torneo, false);

	auto tiempo_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	std::cout << "Tiempo de ejecución con " << num_trabajos << " hilos en una poblacion de " << tam_pob << " individuos con tamaño máximo "
				 << prof_max_expr << " cada individuo y " << evaluaciones << " evaluaciones: " << t_ejecucion.count() << std::endl;


	std::cout << "El mejor individuo es: " << std::endl;
	std::cout << myGAP.getMejorIndividuo() << std::endl;
	std::cout << "Con un ajuste de: " << myGAP.getMejorIndividuo().getFitness() << std::endl;

	return 0;

}
