#include "algoritmos_poblaciones/AlgoritmoPG.hpp"

namespace algoritmos_poblacion_expresiones {



AlgoritmoPG :: AlgoritmoPG(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
									const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var){
	inicializarVacio();
	cargarDatos(datos, etiquetas);
	inicializar(seed, tam_poblacion, prof, prob_var);

}



AlgoritmoPG :: AlgoritmoPG(const std::string fichero_datos, const char char_comentario,
		  const unsigned tam_poblacion, const double prob_var,
		  const unsigned long seed,
		  const char delimitador, const unsigned prof){

	inicializarVacio();
	leerDatos(fichero_datos, char_comentario, delimitador);

	inicializar(seed, tam_poblacion, prof, prob_var);

}


AlgoritmoPG :: ~AlgoritmoPG() {

}


void AlgoritmoPG :: ajustar(const Parametros & parametros) {

	const int NUM_GENERACIONES = parametros.getNumeroEvaluaciones() / static_cast<double>(poblacion_.getTamPoblacion());

	int generacion = 0;
	int padre, madre;
	bool modificado_hijo1;
	bool modificado_hijo2;

	// evaluo la poblacion al inicio
	poblacion_.evaluarPoblacion(datos_, output_datos_, parametros.getFuncionEvaluacion());

	Expresion mejor_individuo = poblacion_.getMejorIndividuo();

	Expresion hijo1, hijo2;

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

			// cruce de la parte GP
			if ( Random::getFloat() < parametros.getProbabilidadCruceGP() ) {
				// cruce de programacion genetica, se intercambian arboles

				poblacion_[madre].cruceArbol(poblacion_[padre], hijo1, hijo2);
				modificado_hijo1 = modificado_hijo2 = true;
			}

			// si no hay cruce, los hijos ya estaban con el valor de los padres

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


		// evaluamos
		poblacion_.evaluarPoblacion(datos_, output_datos_, parametros.getFuncionEvaluacion());

		mejor_individuo = poblacion_.getMejorIndividuo();

		if ( parametros.getMostrarEvaluacion() ) {
			// mostramos el mejor individuo
			std::cout << generacion << "\t" << mejor_individuo.getFitness() << std::endl;
		}

		generacion++;
	}

}


}
