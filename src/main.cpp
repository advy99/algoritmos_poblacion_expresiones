#include <iostream>
#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"
#include "algoritmos_poblaciones/AlgoritmoPG.hpp"

#include <ctime>
#include "random.hpp"
#include <chrono>

#ifdef _OPENMP
	#include <omp.h>
#endif

#include <argparse/argparse.hpp>

int main(int argc, char ** argv){

	argparse::ArgumentParser program("Algoritmos poblacion expresiones");


	program.add_argument("--data_path")
			.help("Path to the data")
			.required();

	program.add_argument("--seed")
			.help("Random seed to use")
			.scan<'i', int>()
			.default_value(42);

	program.add_argument("--poblation_size")
			.help("Poblation size")
			.scan<'i', int>()
			.default_value(50);

	program.add_argument("--variable_prob")
			.help("Probability of a node to be a variable")
			.scan<'g', double>()
			.default_value(0.3);

	program.add_argument("--max_depth")
			.help("Max. depth for the tree")
			.scan<'i', int>()
			.default_value(20);

	program.add_argument("--max_evaluations")
			.help("Max. number of evaluations")
			.scan<'i', int>()
			.default_value(100000);

	program.add_argument("--gp_offspring_prob")
			.help("Probability of generate offspring from a pair of indidivuals in GP")
			.scan<'g', double>()
			.default_value(0.75);

	program.add_argument("--gap_offspring_prob")
			.help("Probability of generate offspring from a pair of indidivuals in GA-P")
			.scan<'g', double>()
			.default_value(0.75);

	program.add_argument("--gp_mutation_prob")
			.help("Probability of mutate an indidivual in GP")
			.scan<'g', double>()
			.default_value(0.05);

	program.add_argument("--gap_mutation_prob")
			.help("Probability of mutate an indidivual in GA-P")
			.scan<'g', double>()
			.default_value(0.05);

	program.add_argument("--in_niche_offspring_prob")
			.help("Probability for an offspring to be generated inside a niche")
			.scan<'g', double>()
			.default_value(0.3);

	program.add_argument("--tournament_size")
			.help("Tournament size")
			.scan<'i', int>()
			.default_value(100);

	program.add_argument("--num_threads")
			.help("Number of threads to use")
			.scan<'i', int>()
			.default_value(2);



	try {
		program.parse_args(argc, argv);
	}
		catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		return 1;
	}


	std::string data_path = program.get<std::string>("--data_path");

	int semilla = program.get<int>("--seed");

	int tam_pob = program.get<int>("--poblation_size");
	double prob_variable = program.get<double>("--variable_prob");
	int prof_max_expr = program.get<int>("--max_depth");
	int evaluaciones = program.get<int>("--max_evaluations");
	double prob_cruce_gp = program.get<double>("--gp_offspring_prob");
	double prob_cruce_ga = program.get<double>("--gap_offspring_prob");
	double prob_muta_gp = program.get<double>("--gp_mutation_prob");
	double prob_muta_ga = program.get<double>("--gap_mutation_prob");
	double prob_cruce_intra = program.get<double>("--in_niche_offspring_prob");
	int tam_torneo = program.get<int>("--tournament_size");

	int num_trabajos = program.get<int>("--num_threads");



	algoritmos_poblacion_expresiones::Parametros parametros_ejecucion(evaluaciones, algoritmos_poblacion_expresiones::error_cuadratico_medio, prob_cruce_gp,
		 																	  prob_cruce_ga, prob_muta_gp,
																			  prob_muta_ga, prob_cruce_intra,
																			  tam_torneo, false);

	parametros_ejecucion.add_funcion_error(algoritmos_poblacion_expresiones::raiz_error_cuadratico_medio);
	parametros_ejecucion.add_funcion_error(algoritmos_poblacion_expresiones::error_absoluto_medio);

	// si utilizamos openMP, establecemos el número de trabajos
	#ifdef _OPENMP
		omp_set_num_threads(num_trabajos);
	#endif

	int semilla_original = semilla;
	Random::set_seed(semilla);
	auto datos = algoritmos_poblacion_expresiones::preprocesado::leer_datos<double, double>(data_path, '@', ',');
	datos = algoritmos_poblacion_expresiones::preprocesado::reordenar_datos_aleatorio(datos.first, datos.second);
	auto train_test_split = algoritmos_poblacion_expresiones::preprocesado::separar_train_test(datos.first, datos.second);

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

		if ( resultado_cv.first.get_fitness() < mejor_expresion_gap.get_fitness()) {
			mejor_expresion_gap = resultado_cv.first;
		}

		for ( unsigned j = 0; j < num_cv; j++) {
			error_medio_ecm_gap += resultado_cv.second[0][j];
			error_medio_recm_gap += resultado_cv.second[1][j];
			error_medio_mae_gap += resultado_cv.second[2][j];
		}

	}

	error_medio_ecm_gap /= num_cv * num_it * 1.0;
	error_medio_recm_gap /= num_cv * num_it * 1.0;
	error_medio_mae_gap /= num_cv * num_it * 1.0;

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
	Random::set_seed(semilla_original);
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


		if ( resultado_cv.first.get_fitness() < mejor_expresion_pg.get_fitness()) {
			mejor_expresion_pg = resultado_cv.first;
		}

		for ( unsigned j = 0; j < num_cv; j++) {
			error_medio_ecm_gp += resultado_cv.second[0][j];
			error_medio_recm_gp += resultado_cv.second[1][j];
			error_medio_mae_gp += resultado_cv.second[2][j];
		}
	}

	error_medio_ecm_gp /= num_cv * num_it * 1.0;
	error_medio_recm_gp /= num_cv * num_it * 1.0;
	error_medio_mae_gp /= num_cv * num_it * 1.0;

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
