#include "poblacion.hpp"
#include <cstring>


Poblacion::Poblacion(){
	// una poblacion vacia no tiene nada
	poblacion       = nullptr;
	tam_poblacion   = 0;
	tam_reservado   = 0;
	mejor_individuo = -1;
}


Poblacion::Poblacion(const unsigned tam, const unsigned lon_expre,
							const double prob_var, const unsigned num_vars,
							const unsigned prof_expre){
	// liberamos memoria para inicializar a vacio
	poblacion = nullptr;

	liberarMemoria();

	// reservamos memoria para tam individuos
	reservarMemoria(tam);
	tam_poblacion = tam;
	// inicializamos todas las expresiones de la poblacion
	for (unsigned i = 0; i < tam; i++){
		poblacion[i] = Expresion(lon_expre, prob_var, num_vars, prof_expre);
	}
}

Poblacion::~Poblacion(){
	liberarMemoria();
}

void Poblacion::liberarMemoria(){
	// si tiene asignada una direccion de memoria, liberamos la poblacion
	if (poblacion != nullptr){
		delete [] poblacion;
	}

	// establecemos los valores a nulos
	tam_reservado   = 0;
	tam_poblacion   = 0;
	mejor_individuo = -1;
	poblacion       = nullptr;

}

void Poblacion::reservarMemoria(const unsigned tam){
	poblacion     = new Expresion[tam];
	tam_reservado = tam;
}

void Poblacion::copiarDatos(const Poblacion & otra){
	// copiamos los atributos
	tam_poblacion = otra.tam_poblacion;
	mejor_individuo = otra.mejor_individuo;

	// copiamos los elementos de la poblacion
	// no podemos usar memcpy ya que estos elementos si que
	// utilizan memoria dinamica de forma interna
	for (unsigned i = 0; i < tam_poblacion; i++){
		poblacion[i] = otra.poblacion[i];

	}
}

void Poblacion::evaluarPoblacion(const std::vector<std::vector<double> > & datos,
											const std::vector<double> & etiquetas){
	// establecemos el mejor individuo al primero
	mejor_individuo = 0;
	double valor_mejor;
	double valor_evaluada;

	// evaluamos el mejor hasta ahora
	valor_mejor = poblacion[0].evaluarExpresion(datos, etiquetas);

	// evaluamos el resto de individuos
	for ( unsigned i = 1; i < tam_poblacion; i++){
		if (!poblacion[i].estaEvaluada()){
			valor_evaluada = poblacion[i].evaluarExpresion(datos, etiquetas);

			if (valor_evaluada < valor_mejor){
				mejor_individuo = i;
				valor_mejor = valor_evaluada;
			}
		}
	}
}


double Poblacion::sumaFitness() const {
	double suma = 0.0;

	for (unsigned i = 0; i < tam_poblacion; i++){
		suma += poblacion[i].getFitness();
	}

	return suma;
}

unsigned Poblacion::seleccionIndividuo() const {

	double * probabilidad = new double [tam_poblacion];

	double fitnessPoblacion = sumaFitness();

	probabilidad[0] = poblacion[0].getFitness() / fitnessPoblacion;

	for (unsigned i = 1; i < tam_poblacion; i++){
		probabilidad[i] = probabilidad[i-1] +
								(poblacion[i].getFitness() / fitnessPoblacion);
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
