#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"

namespace algoritmos_poblacion_expresiones {


AlgoritmoGA_P :: AlgoritmoGA_P(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
										 const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var) {
	inicializarVacio();
	cargarDatos(datos, etiquetas);
	inicializar(seed, tam_poblacion, prof, prob_var);

}



AlgoritmoGA_P :: AlgoritmoGA_P(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed, const char delimitador, const unsigned prof){


	// lemos los datos del fichero de entrada
	inicializarVacio();
	leerDatos(fichero_datos, char_comentario, delimitador);

	inicializar(seed, tam_poblacion, prof, prob_var);

}

void AlgoritmoGA_P :: ajustar(const Parametros & parametros) {


	// en cada generacion hacemos dos evaluaciones, así que si queremos cierto
	// numero de evaluaciones, las generaciones serán la mitad
	const int NUM_GENERACIONES = parametros.getNumeroEvaluaciones() / static_cast<double>(poblacion_.getTamPoblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion_.evaluarPoblacion(datos_, output_datos_, parametros.getFuncionEvaluacion());
	// poblacion_.ordenar();



	Expresion_GAP mejor_individuo = poblacion_.getMejorIndividuo();

	Expresion_GAP hijo1, hijo2;

	bool cruce_intra_nicho_posible = true;

	while ( generacion < NUM_GENERACIONES) {

		// seleccionamos la poblacion
		poblacion_ = seleccionTorneo(parametros.getTamanioTorneo());

		std::vector<bool> cruzados;
		cruzados.resize(poblacion_.getTamPoblacion(), false);
		int primero_sin_cruzar = 0;

		for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i += 2){

			madre = primero_sin_cruzar;
			++primero_sin_cruzar;
			cruzados[madre] = true;

			cruce_intra_nicho_posible = false;
			modificado_hijo1 = modificado_hijo2 = false;

			if ( parametros.getProbabilidadCruceIntranicho() < Random::getFloat() ){
				// cruce intra-nicho

				padre = seleccionIntraNicho(madre, cruzados);

				cruce_intra_nicho_posible = padre != -1;

				// aplicamos el cruce
				if ( cruce_intra_nicho_posible) {
					// ya he escogido a ese padre
					cruzados[padre] = true;
					if (padre == primero_sin_cruzar) {
						primero_sin_cruzar++;
					}

					hijo1 = poblacion_[madre];
					hijo2 = poblacion_[padre];

					// cruce de la parte GA
					if ( Random::getFloat() < parametros.getProbabilidadCruceGA() ) {
						// cruce del cromosoma utilizando BLX_alfa
						poblacion_[madre].cruceBLXalfa(poblacion_[padre], hijo1, hijo2);
						modificado_hijo1 = modificado_hijo2 = true;
					}


					if ( Random::getFloat() < parametros.getProbabilidadMutacionGA() ) {
						// mutacion GP en el primer hijo
						hijo1.mutarGA(generacion, NUM_GENERACIONES);
						modificado_hijo1 = true;
					}

					if ( Random::getFloat() < parametros.getProbabilidadMutacionGA() ) {
						// mutacion GP en el segundo hijo
						hijo2.mutarGA(generacion, NUM_GENERACIONES);
						modificado_hijo2 = true;
					}

				}

			}

			// si se escoge hacer cruce inter-nicho, o si no es posible aplicarlo
			if ( !cruce_intra_nicho_posible ) {
				// cruce inter-nicho
				padre = primero_sin_cruzar;
				primero_sin_cruzar++;
				cruzados[padre] = true;

				hijo1 = poblacion_[madre];
				hijo2 = poblacion_[padre];

				// cruce de la parte GP
				if ( Random::getFloat() <  parametros.getProbabilidadCruceGP() ) {
					// cruce de programacion genetica, se intercambian arboles

					poblacion_[madre].cruceArbol(poblacion_[padre], hijo1, hijo2);
					modificado_hijo1 = modificado_hijo2 = true;
				}

				// cruce de la parte GA
				if ( Random::getFloat() < parametros.getProbabilidadCruceGA() ) {
					// cruce del cromosoma utilizando BLX_alfa
					poblacion_[madre].cruceBLXalfa(poblacion_[padre], hijo1, hijo2);
					modificado_hijo1 = modificado_hijo2 = true;
				}

				// si no hay cruce, los hijos ya estaban con el valor de los padres
				if ( Random::getFloat() < parametros.getProbabilidadMutacionGA() ) {
					// mutacion GP en el primer hijo
					hijo1.mutarGA(generacion, NUM_GENERACIONES);
					modificado_hijo1 = true;
				}

				if ( Random::getFloat() < parametros.getProbabilidadMutacionGA() ) {
					// mutacion GP en el segundo hijo
					hijo2.mutarGA(generacion, NUM_GENERACIONES);
					modificado_hijo2 = true;
				}


				auto resultado_mut_gp = aplicarMutacionesGP(hijo1, hijo2, parametros.getProbabilidadMutacionGP());

				modificado_hijo1 = modificado_hijo1 || resultado_mut_gp.first;
				modificado_hijo2 = modificado_hijo2 || resultado_mut_gp.second;

			}


			if ( modificado_hijo1 ) {
				poblacion_[madre] = hijo1;
				poblacion_[madre].dejaEstarEvaluada();
			}

			if ( modificado_hijo2) {
				poblacion_[padre] = hijo2;
				poblacion_[padre].dejaEstarEvaluada();
			}

		}


		aplicarElitismo(mejor_individuo);
		poblacion_.evaluarPoblacion(datos_, output_datos_, parametros.getFuncionEvaluacion());
		poblacion_.ordenar();

		mejor_individuo = poblacion_[0];

		if ( parametros.getMostrarEvaluacion() ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.getFitness() << std::endl;
		}

		generacion++;

	}

}

int AlgoritmoGA_P :: seleccionIntraNicho(const int madre, const std::vector<bool> & escogidos) const{

	int padre = -1;


	unsigned i = 0;

	do {

		padre = i;

		// si no estan en el mismo nicho, o si ya lo hemos escogido antes
		if ( !poblacion_[madre].mismoNicho(poblacion_[padre]) || escogidos[padre] ) {
			padre = -1;
		}

		i++;

	} while ( padre == -1 && i < escogidos.size() );

	return padre;
}


} // namespace algoritmos_poblacion_expresiones
