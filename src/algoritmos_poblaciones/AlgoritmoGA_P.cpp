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



AlgoritmoGA_P :: ~AlgoritmoGA_P(){
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
	poblacion_.ordenar();

	Expresion_GAP mejor_individuo = poblacion_[0];

	Expresion_GAP hijo1, hijo2;

	bool cruce_ga;
	bool cruce_gp;

	bool cruce_intra_nicho_posible = true;

	while ( generacion < NUM_GENERACIONES) {

		Poblacion<Expresion_GAP> nueva_poblacion;

		for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i += 2){

			// seleccionamos el individuo a cruzar
			madre = poblacion_.seleccionIndividuo();

			cruce_intra_nicho_posible = false;
			modificado_hijo1 = modificado_hijo2 = false;
			cruce_ga = cruce_gp = false;

			if ( parametros.getProbabilidadCruceIntranicho() < Random::getFloat() ){
				// cruce intra-nicho

				padre = seleccionIntraNicho(madre);

				cruce_intra_nicho_posible = padre != -1;

				// aplicamos el cruce
				if ( cruce_intra_nicho_posible) {
					hijo1 = poblacion_[madre];
					hijo2 = poblacion_[padre];

					// cruce de la parte GA
					if ( Random::getFloat() < parametros.getProbabilidadCruceGA() ) {
						// cruce del cromosoma utilizando BLX_alfa
						poblacion_[madre].cruceBLXalfa(poblacion_[padre], hijo1, hijo2);
						modificado_hijo1 = modificado_hijo2 = true;
						cruce_ga = true;
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
				padre = poblacion_.seleccionIndividuo();

				hijo1 = poblacion_[madre];
				hijo2 = poblacion_[padre];


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

			}

			nueva_poblacion.insertar(hijo1);
			nueva_poblacion.insertar(hijo2);

		}

		poblacion_ = nueva_poblacion;

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

int AlgoritmoGA_P :: seleccionIntraNicho(const int madre) const{

	int padre = -1;

	std::vector<int> escogidos(poblacion_.getTamPoblacion(), 0);

	for ( unsigned i = 0; i < poblacion_.getTamPoblacion(); i++ ) {
		escogidos[i] = i;
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(escogidos.begin(), escogidos.end(), g);

	unsigned i = 0;

	do {

		padre = i;

		if ( !poblacion_[madre].mismoNicho(poblacion_[padre]) ) {
			padre = -1;
		}

		i++;

	} while ( padre == -1 && i < escogidos.size() );

	return padre;
}


} // namespace algoritmos_poblacion_expresiones
