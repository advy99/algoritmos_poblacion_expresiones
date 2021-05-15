#include "algoritmos_poblaciones/Expresion_GAP.hpp"


namespace algoritmos_poblacion_expresiones {

Expresion_GAP :: Expresion_GAP(const unsigned prof_max){

	// establecemos la profundidad a la maxima dada
	profundidad_maxima_ = prof_max;

	// inicilizamos la expresion vacia
	inicializarVacia();


	// inicializamos el cromosoma de forma aleatoria
	inicializarCromosoma(prof_max);
}

Expresion_GAP :: Expresion_GAP(const std::vector<Nodo> & subarbol, const unsigned prof_max){

	// establecemos la profundidad maxima a la dada
	profundidad_maxima_ = prof_max;

	// inicializamos la expresion vacia
	inicializarVacia();

	inicializarCromosoma(prof_max);

	// obtenemos el subarbol
	arbol_ = obtenerSubarbol(subarbol, 0);


}


Expresion_GAP :: Expresion_GAP(const unsigned longitud_max, const double prob_variable,
							const unsigned num_vars, const unsigned prof_max){

	profundidad_maxima_ = prof_max;

	inicializarVacia();

	// inicializamos el cromosoma el cromosoma
	inicializarCromosoma(prof_max);

	// generamos una expresion aleatoria
	generarExpresionAleatoria(longitud_max, prob_variable, num_vars);


}


void Expresion_GAP :: inicializarCromosoma(const unsigned longitud){
	cromosoma_.resize(longitud);
	// para cada elemento escogemos un numero aleatorio en [-10, 10]
	for (unsigned i = 0; i < cromosoma_.size(); i++){
		cromosoma_[i] = Random::getFloat(-10.0f, 10.0f);
	}

}

void Expresion_GAP :: inicializarVacia(){

	Expresion::inicializarVacia();

	cromosoma_ = std::vector<double>();
}



void Expresion_GAP :: copiarDatos(const Expresion_GAP & otra) {

	Expresion::copiarDatos(otra);

	cromosoma_ = otra.cromosoma_;
}


Expresion_GAP :: Expresion_GAP(const Expresion_GAP & otra) : Expresion(otra){

	cromosoma_ = otra.cromosoma_;

}



Expresion_GAP & Expresion_GAP :: operator= (const Expresion_GAP & otra){
	// si no es ella misma
	if (this != &otra){

		// copiamos los datos de la otra
		copiarDatos(otra);
	}

	// devolvemos el objeto actual
	return (*this);

}



bool Expresion_GAP :: generarExpresionAleatoria(const unsigned longitud_maxima,
														const double prob_variable,
														const unsigned num_variables){

	bool exito = Expresion::generarExpresionAleatoria(longitud_maxima, prob_variable, num_variables);

	for (unsigned i = 0; i < getLongitudArbol(); i++) {
		if (arbol_[i].getTipoNodo() == TipoNodo::NUMERO) {
			arbol_[i].setTerminoAleatorio(cromosoma_.size(), num_variables);
		}
	}

	return exito;

}


// en reemplazo de evaluarDato, usa la del padre paro llama a esta para obtener un NUMERO
double Expresion_GAP :: obtenerNumero ( const Nodo & n) const {
	return cromosoma_[n.getValor()];
}



double Expresion_GAP :: delta(const int generacion, const int max_generaciones, const double valor) {
	double aleatorio = Random::getFloat();

	double sub = 1.0 - ((double)generacion / (double)(max_generaciones));
	// TODO: parametrizar B
	double potencia = std::pow(sub, 5);
	double subtotal = std::pow(aleatorio, potencia);

	return (valor * (1.0 - subtotal));
}


void Expresion_GAP :: mutarGA(const int generacion, const int max_generaciones) {

	int pos_mutacion = Random::getInt(cromosoma_.size());

	if ( Random::getFloat() < 0.5) {
		cromosoma_[pos_mutacion] += delta(generacion, max_generaciones, 1.0 - cromosoma_[pos_mutacion]);
	} else {
		cromosoma_[pos_mutacion] -= delta(generacion, max_generaciones, cromosoma_[pos_mutacion]);
	}
}


bool Expresion_GAP :: mismoCromosoma ( const Expresion_GAP & otra) const {

	// comprobamos si el arbol es igual
	bool resultado = cromosoma_.size() == otra.getLongitudCromosoma();

	// si el arbol coincide, comparamos el cromosoma
	if ( resultado ) {
		for ( unsigned i = 0; i < getLongitudCromosoma(); i++) {
			resultado = resultado && comparar_reales(cromosoma_[i], otra.cromosoma_[i], 0.005);
		}
	}

	return resultado;

}


std::vector<double> Expresion_GAP :: getCromosoma () const {
	return cromosoma_;
}


void Expresion_GAP :: cruceBLXalfa(const Expresion_GAP & otra, Expresion_GAP & hijo1, Expresion_GAP & hijo2, const double alfa) const{

	if ( otra.cromosoma_.size() != cromosoma_.size() ) {
		std::cerr << "Cruzando dos cromosomas de distinta longitud" << std::endl;
	}

	std::vector<double> cromosoma_actual;
	cromosoma_actual.resize(cromosoma_.size());

	std::vector<double> cromosoma_otro;
	cromosoma_otro.resize(otra.cromosoma_.size());

	double punto_padre, punto_madre, seccion;

	for ( unsigned i = 0; i < cromosoma_.size(); i++){
		punto_madre = cromosoma_[i];
		punto_padre = otra.cromosoma_[i];

		if ( punto_madre > punto_padre ) {
			double intercamio = punto_madre;
			punto_madre = punto_padre;
			punto_padre = intercamio;
		}

		seccion = punto_padre - punto_madre;

		punto_madre = punto_madre - seccion * alfa;
		punto_padre = punto_padre + seccion * alfa;

		if ( punto_madre < 0.0) {
			punto_madre = 0.0;
		}

		if ( punto_padre > 1.0) {
			punto_padre = 1.0;
		}

		cromosoma_actual[i] = punto_madre + Random::getFloat() *
														(punto_padre - punto_madre);

		cromosoma_otro[i] = punto_madre + Random::getFloat() *
														(punto_padre - punto_madre);
	}


	hijo1.asignarCromosoma(cromosoma_actual);
	hijo2.asignarCromosoma(cromosoma_otro);


}


unsigned Expresion_GAP :: getLongitudCromosoma() const{
	return cromosoma_.size();
}



void Expresion_GAP :: asignarCromosoma(const std::vector<double> & nuevo_cromosoma){
	cromosoma_ = nuevo_cromosoma;
}

bool Expresion_GAP :: mismoNicho(const Expresion_GAP & otra) const {

	bool resultado = cromosoma_.size() == otra.getLongitudArbol();

	unsigned i = 0;
	while (resultado && i < cromosoma_.size()) {
		resultado = arbol_[i].getTipoNodo() == otra.getArbol()[i].getTipoNodo();
		i++;
	}

	return resultado;
}


bool Expresion_GAP :: operator== (const Expresion_GAP & otra) const {
	return mismoCromosoma(otra) && mismoArbol(otra);
}

}
