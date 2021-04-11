#include "algoritmos_poblaciones/AlgoritmoGA_P.hpp"

namespace algoritmos_poblaciones {


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



AlgoritmoGA_P :: ~AlgoritmoGA_P(){
}


void AlgoritmoGA_P :: ajustar(const Parametros & parametros) {

	const int NUM_GENERACIONES = parametros.getNumeroEvaluaciones() / static_cast<double>(poblacion_.getTamPoblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion_.evaluarPoblacion(datos_, output_datos_);

	Expresion_GAP mejor_individuo = poblacion_.getMejorIndividuo();

	Expresion_GAP hijo1, hijo2;

	bool cruce_ga;
	bool cruce_gp;

	while ( generacion < NUM_GENERACIONES) {

		// seleccionamos la poblacion a cruzar
		poblacion_ = seleccionTorneo(parametros.getTamanioTorneo());

		// aplicamos los operadores geneticos
		for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i += 2){

			madre = i;
			padre = i + 1;

			hijo1 = poblacion_[madre];
			hijo2 = poblacion_[padre];

			modificado_hijo1 = modificado_hijo2 = false;
			cruce_ga = cruce_gp = false;

			// cruce de la parte GA
			if ( Random::getFloat() < parametros.getProbabilidadCruceGA() ) {
				// cruce del cromosoma utilizando BLX_alfa
				poblacion_[madre].cruceBLXalfa(poblacion_[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_ga = true;
			}

			// cruce de la parte GP
			if ( Random::getFloat() <  parametros.getProbabilidadCruceGP() ) {
				// cruce de programacion genetica, se intercambian arboles

				poblacion_[madre].cruceArbol(poblacion_[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
				cruce_gp = true;
			}

			if ( cruce_gp || cruce_ga ) {
				// si hay algun tipo de cruce
				if ( !cruce_gp ) {
					// no se ha cruzado el arbol
					hijo1.asignarArbol(poblacion_[madre].getArbol(), poblacion_[madre].getLongitudArbol());
					hijo2.asignarArbol(poblacion_[padre].getArbol(), poblacion_[padre].getLongitudArbol());
				} else {
					// no se ha cruzado el cromosoma
					hijo1.asignarCromosoma(poblacion_[madre].getCromosoma(), poblacion_[madre].getLongitudCromosoma());
					hijo2.asignarCromosoma(poblacion_[padre].getCromosoma(), poblacion_[padre].getLongitudCromosoma());

				}
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

		poblacion_.evaluarPoblacion(datos_, output_datos_);

		mejor_individuo = poblacion_.getMejorIndividuo();

		if ( parametros.getMostrarEvaluacion() ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.getFitness() << std::endl;
		}

		generacion++;
	}

}


} // namespace algoritmos_poblaciones
