#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"

namespace algoritmos_poblacion_expresiones {


AlgoritmoGA_P :: AlgoritmoGA_P(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
										 const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {
	inicializar_vacio();
	cargar_datos(datos, etiquetas);
	inicializar(seed, tam_poblacion, prof, prob_var);

}



AlgoritmoGA_P :: AlgoritmoGA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed, const char delimitador, const unsigned prof){


	// lemos los datos del fichero de entrada
	inicializar_vacio();
	leer_datos(fichero_datos, char_comentario, delimitador);

	inicializar(seed, tam_poblacion, prof, prob_var);

}

void AlgoritmoGA_P :: ajustar(const Parametros & parametros) {


	// en cada generacion hacemos dos evaluaciones, así que si queremos cierto
	// numero de evaluaciones, las generaciones serán la mitad
	const int NUM_GENERACIONES = parametros.get_numero_evaluaciones() / static_cast<double>(poblacion_.get_tam_poblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion_.evaluar_poblacion(datos_, output_datos_, parametros.get_funcion_evaluacion());
	// poblacion_.ordenar();



	Expresion_GAP mejor_individuo = poblacion_.get_mejor_individuo();

	Expresion_GAP hijo1, hijo2;

	bool cruce_intra_nicho_posible = true;

	while ( generacion < NUM_GENERACIONES) {

		// seleccionamos la poblacion
		poblacion_ = seleccion_torneo(parametros.get_tamanio_torneo());

		std::vector<bool> cruzados;
		cruzados.resize(poblacion_.get_tam_poblacion(), false);
		int primero_sin_cruzar = 0;

		for ( unsigned i = 0; i < poblacion_.get_tam_poblacion(); i += 2){

			madre = primero_sin_cruzar;
			do {
				++primero_sin_cruzar;
			} while (cruzados[primero_sin_cruzar]);
			cruzados[madre] = true;

			cruce_intra_nicho_posible = false;
			modificado_hijo1 = modificado_hijo2 = false;

			if ( parametros.get_probabilidad_cruce_intranicho() < Random::getFloat() ){
				// cruce intra-nicho

				padre = seleccion_intra_nicho(madre, cruzados);

				cruce_intra_nicho_posible = padre != -1;

				// aplicamos el cruce
				if ( cruce_intra_nicho_posible) {
					// ya he escogido a ese padre
					cruzados[padre] = true;
					if (padre == primero_sin_cruzar) {
						do {
							++primero_sin_cruzar;
						} while (cruzados[primero_sin_cruzar]);

					}

					hijo1 = poblacion_[madre];
					hijo2 = poblacion_[padre];

					// cruce de la parte GA
					if ( Random::getFloat() < parametros.get_probabilidad_cruce_GA() ) {
						// cruce del cromosoma utilizando BLX_alfa
						poblacion_[madre].cruce_BLX_alfa(poblacion_[padre], hijo1, hijo2);
						modificado_hijo1 = modificado_hijo2 = true;
					}


					if ( Random::getFloat() < parametros.get_probabilidad_mutacion_GA() ) {
						// mutacion GP en el primer hijo
						hijo1.mutar_GA(generacion, NUM_GENERACIONES);
						modificado_hijo1 = true;
					}

					if ( Random::getFloat() < parametros.get_probabilidad_mutacion_GA() ) {
						// mutacion GP en el segundo hijo
						hijo2.mutar_GA(generacion, NUM_GENERACIONES);
						modificado_hijo2 = true;
					}

				}

			}

			// si se escoge hacer cruce inter-nicho, o si no es posible aplicarlo
			if ( !cruce_intra_nicho_posible ) {
				// cruce inter-nicho
				padre = primero_sin_cruzar;
				do {
					++primero_sin_cruzar;
				} while (cruzados[primero_sin_cruzar]);
				cruzados[padre] = true;

				hijo1 = poblacion_[madre];
				hijo2 = poblacion_[padre];

				// cruce de la parte GP
				if ( Random::getFloat() <  parametros.get_probabilidad_cruce_GP() ) {
					// cruce de programacion genetica, se intercambian arboles

					poblacion_[madre].cruce_arbol(poblacion_[padre], hijo1, hijo2);
					modificado_hijo1 = modificado_hijo2 = true;
				}

				// cruce de la parte GA
				if ( Random::getFloat() < parametros.get_probabilidad_cruce_GA() ) {
					// cruce del cromosoma utilizando BLX_alfa
					poblacion_[madre].cruce_BLX_alfa(poblacion_[padre], hijo1, hijo2);
					modificado_hijo1 = modificado_hijo2 = true;
				}

				// si no hay cruce, los hijos ya estaban con el valor de los padres
				if ( Random::getFloat() < parametros.get_probabilidad_mutacion_GA() ) {
					// mutacion GP en el primer hijo
					hijo1.mutar_GA(generacion, NUM_GENERACIONES);
					modificado_hijo1 = true;
				}

				if ( Random::getFloat() < parametros.get_probabilidad_mutacion_GA() ) {
					// mutacion GP en el segundo hijo
					hijo2.mutar_GA(generacion, NUM_GENERACIONES);
					modificado_hijo2 = true;
				}


				auto resultado_mut_gp = aplicar_mutaciones_GP(hijo1, hijo2, parametros.get_probabilidad_mutacion_GP());

				modificado_hijo1 = modificado_hijo1 || resultado_mut_gp.first;
				modificado_hijo2 = modificado_hijo2 || resultado_mut_gp.second;

			}


			if ( modificado_hijo1 ) {
				poblacion_[madre] = hijo1;
				poblacion_[madre].deja_estar_evaluada();
			}

			if ( modificado_hijo2) {
				poblacion_[padre] = hijo2;
				poblacion_[padre].deja_estar_evaluada();
			}

		}


		aplicar_elitismo(mejor_individuo);
		poblacion_.evaluar_poblacion(datos_, output_datos_, parametros.get_funcion_evaluacion());
		poblacion_.ordenar();

		mejor_individuo = poblacion_[0];

		if ( parametros.get_mostrar_evaluacion() ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.get_fitness() << std::endl;
		}

		generacion++;

	}

}

int AlgoritmoGA_P :: seleccion_intra_nicho(const int madre, const std::vector<bool> & escogidos) const{

	int padre = -1;


	unsigned i = 0;

	do {

		padre = i;

		// si no estan en el mismo nicho, o si ya lo hemos escogido antes
		if ( !poblacion_[madre].mismo_nicho(poblacion_[padre]) || escogidos[padre] ) {
			padre = -1;
		}

		i++;

	} while ( padre == -1 && i < escogidos.size() );

	return padre;
}


} // namespace algoritmos_poblacion_expresiones
