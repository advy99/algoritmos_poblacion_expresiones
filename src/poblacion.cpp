#include "poblacion.hpp"

namespace GA_P {

Poblacion :: Poblacion(){
	// una poblacion vacia no tiene nada
	expresiones     = nullptr;
	tam_poblacion   = 0;
	mejor_individuo = -1;
}


Poblacion :: Poblacion(const unsigned tam, const unsigned lon_expre,
							const double prob_var, const unsigned num_vars,
							const unsigned prof_expre){
	// liberamos memoria para inicializar a vacio
	expresiones = nullptr;

	liberarMemoria();

	// reservamos memoria para tam individuos
	reservarMemoria(tam);
	tam_poblacion = tam;
	// inicializamos todas las expresiones de la poblacion
	for (unsigned i = 0; i < tam; i++){
		expresiones[i] = Expresion(lon_expre, prob_var, num_vars, prof_expre);
	}
}

Poblacion :: Poblacion ( const Poblacion & otra) {
	expresiones = nullptr;

	tam_poblacion = 0;


	(*this) = otra;
}


Poblacion :: ~Poblacion(){
	liberarMemoria();
}

void Poblacion :: liberarMemoria(){
	// si tiene asignada una direccion de memoria, liberamos la poblacion
	if (expresiones != nullptr){
		delete [] expresiones;
	}

	// establecemos los valores a nulos

	tam_poblacion   = 0;
	mejor_individuo = -1;
	expresiones     = nullptr;

}

void Poblacion :: reservarMemoria(const unsigned tam){
	expresiones   = new Expresion[tam];
	tam_poblacion = tam;
}

void Poblacion :: copiarDatos(const Poblacion & otra){
	// copiamos los atributos
	tam_poblacion = otra.tam_poblacion;
	mejor_individuo = otra.mejor_individuo;

	// copiamos los elementos de la poblacion
	// no podemos usar memcpy ya que estos elementos si que
	// utilizan memoria dinamica de forma interna
	for (unsigned i = 0; i < tam_poblacion; i++){
		expresiones[i] = otra.expresiones[i];

	}
}

void Poblacion :: evaluarPoblacion(const std::vector<std::vector<double> > & datos,
											const std::vector<double> & etiquetas){
	// establecemos el mejor individuo al primero
	mejor_individuo = 0;

	if (!expresiones[0].estaEvaluada()) {
		expresiones[0].evaluarExpresion(datos, etiquetas);
	}

	// evaluamos el resto de individuos
	#pragma omp parallel for
	for ( unsigned i = 1; i < tam_poblacion; i++){
		if (!expresiones[i].estaEvaluada()){
			expresiones[i].evaluarExpresion(datos, etiquetas);
		}

		#pragma omp critical 
		{
			if (expresiones[i].getFitness() < expresiones[mejor_individuo].getFitness()){
				mejor_individuo = i;
			}
		}
		
	}
}


double Poblacion :: sumaFitness() const {
	double suma = 0.0;

	for (unsigned i = 0; i < tam_poblacion; i++){
		suma += expresiones[i].getFitness();
	}

	return suma;
}

unsigned Poblacion :: seleccionIndividuo() const {

	double * probabilidad = new double [tam_poblacion];

	double fitnessPoblacion = sumaFitness();

	probabilidad[0] = expresiones[0].getFitness() / fitnessPoblacion;

	for (unsigned i = 1; i < tam_poblacion; i++){
		probabilidad[i] = probabilidad[i-1] +
								(expresiones[i].getFitness() / fitnessPoblacion);
	}
	// evitamos errores de redondeo
	probabilidad[tam_poblacion - 1] = 1.0;

	double aleatorio = Random::getFloat();

	unsigned indice = 0;

	while (aleatorio > probabilidad[indice] && indice < tam_poblacion){
		indice++;
	}


	delete [] probabilidad;

	return indice;


}

Expresion Poblacion :: getMejorIndividuo() const {
	return expresiones[mejor_individuo];
}

unsigned Poblacion :: getIndiceMejorIndividuo() const {
	return mejor_individuo;
}

unsigned Poblacion :: getTamPoblacion() const {
	return tam_poblacion;
}

Expresion & Poblacion :: operator[] (const unsigned indice) {
	return expresiones[indice];
}

const Expresion & Poblacion :: operator[] (const unsigned indice) const {
	return expresiones[indice];
}

Poblacion & Poblacion :: operator= (const Poblacion & otra) {

	liberarMemoria();

	tam_poblacion = otra.tam_poblacion;

	reservarMemoria(tam_poblacion);

	for ( unsigned i = 0; i < tam_poblacion; i++ ) {
		expresiones[i] = otra.expresiones[i];
	}

	mejor_individuo = otra.mejor_individuo;

	return (*this);

}



} // namespace GA_P
