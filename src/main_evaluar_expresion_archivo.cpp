#include <iostream>
#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"
#include "algoritmos_poblaciones/AlgoritmoPG.hpp"

#include <ctime>
#include "random.hpp"
#include <chrono>

#ifdef _OPENMP
	#include <omp.h>
#endif


int main(int argc, char ** argv){

	if ( argc < 5 || argc > 6 ) {
		std::cerr << "Error en el número de parámetros\n"
					 << "\t Uso: " << argv[0] << " <fichero_datos> <fichero_expresion> <profundidad_max> <num_variables> [semilla] \n"
					 << std::endl;
		exit(-1);
	}

	std::string fichero_exp = std::string(argv[2]);
	unsigned longitud_max = atoi(argv[3]);
	int num_vars = atoi(argv[4]);
	int semilla;

	if ( argc == 6 ){
		semilla = atoi(argv[5]);
	} else {
		semilla = std::time(nullptr);
	}


	int num_trabajos = 2;
	// si utilizamos openMP, establecemos el número de trabajos
	#ifdef _OPENMP
		omp_set_num_threads(num_trabajos);
	#endif

	int semilla_original = semilla;
	Random::set_seed(semilla);
	auto datos = algoritmos_poblacion_expresiones::preprocesado::leer_datos<double>(std::string(argv[1]), '@', ',');
	datos = algoritmos_poblacion_expresiones::preprocesado::reordenar_datos_aleatorio(datos.first, datos.second);
	auto train_test_split = algoritmos_poblacion_expresiones::preprocesado::separar_train_test(datos.first, datos.second);

	algoritmos_poblacion_expresiones::Expresion expresion(fichero_exp, longitud_max, num_vars);

	expresion.evaluar_expresion(train_test_split.second.first, train_test_split.second.second, algoritmos_poblacion_expresiones::error_cuadratico_medio, true);
	double error_medio_ecm = expresion.get_fitness();

	expresion.evaluar_expresion(train_test_split.second.first, train_test_split.second.second, algoritmos_poblacion_expresiones::raiz_error_cuadratico_medio, true);
	double error_medio_recm = expresion.get_fitness();

	expresion.evaluar_expresion(train_test_split.second.first, train_test_split.second.second, algoritmos_poblacion_expresiones::error_absoluto_medio, true);
	double error_medio_mae = expresion.get_fitness();

	// mostramos el resultado
	std::cout << semilla_original << "\t"
				 << error_medio_ecm << "\t"
				 << error_medio_recm << "\t"
				 << error_medio_mae << std::endl;

	return 0;

}
