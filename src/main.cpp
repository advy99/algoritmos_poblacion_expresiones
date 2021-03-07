#include <iostream>
#include "GA_P.hpp"
#include <ctime>
#include "random.hpp"



int main(int argc, char ** argv){

	if ( argc < 11 || argc > 12 ) {
		std::cerr << "Error en el número de parámetros\n"
					 << "\t Uso: " << argv[0] << " <fichero_datos> <tam_poblacion> <prob_variable> <profundidad_max> \n" 
					 << "\t\t\t" << " <num_evaluaciones> <prob_cruce_gp> <prob_cruce_ga> <prob_mutacion_gp> <prob_mutacion_ga> <tam_torneo> [semilla]"
					 << std::endl;
		exit(-1);
	}

	int semilla;

	if ( argc == 12 ){
		semilla = atoi(argv[2]);
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


	GA_P::GA_P myGAP (std::string(argv[1]), '@', tam_pob, prob_variable, semilla, ',', prof_max_expr);

	

	myGAP.ajustar(evaluaciones, prob_cruce_gp, prob_cruce_ga, prob_muta_gp, prob_muta_ga, tam_torneo);


	std::cout << myGAP.getMejorIndividuo() << std::endl;

	return 0;

}
