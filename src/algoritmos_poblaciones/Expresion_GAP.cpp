#include "algoritmos_poblaciones/Expresion_GAP.hpp"


namespace algoritmos_poblaciones {

Expresion_GAP :: Expresion_GAP(const unsigned prof_max){

	// establecemos la profundidad a la maxima dada
	profundidad_maxima_ = prof_max;

	// inicilizamos la expresion vacia
	inicializarVacia();

	// reservamos memoria para el cromosoma
	reservarMemoriaCromosoma(profundidad_maxima_);

	// inicializamos el cromosoma de forma aleatoria
	inicializarCromosoma();
}

Expresion_GAP :: Expresion_GAP(const Arbol subarbol, const unsigned prof_max){

	// establecemos la profundidad maxima a la dada
	profundidad_maxima_ = prof_max;

	// inicializamos la expresion vacia
	inicializarVacia();

	// obtenemos el subarbol
	(*this) = dynamic_cast<Expresion_GAP &>(obtenerSubarbol(subarbol));

	reservarMemoriaCromosoma(profundidad_maxima_);

	inicializarCromosoma();

}

Expresion_GAP :: ~Expresion_GAP(){
	liberarMemoria();
}


Expresion_GAP :: Expresion_GAP(const unsigned longitud_max, const double prob_variable,
							const unsigned num_vars, const unsigned prof_max){

	profundidad_maxima_ = prof_max;

	inicializarVacia();

	// reservamos la profundidad maxima
	reservarMemoriaCromosoma(profundidad_maxima_);

	// inicializamos el cromosoma el cromosoma
	inicializarCromosoma();

	// generamos una expresion aleatoria
	generarExpresionAleatoria(longitud_max, prob_variable, num_vars);
}


void Expresion_GAP :: inicializarCromosoma(){
	// para cada elemento escogemos un numero aleatorio en [-10, 10]
	for (unsigned i = 0; i < longitud_cromosoma_; i++){
		cromosoma_[i] = Random::getFloat(-10.0f, 10.0f);
	}

}

void Expresion_GAP :: inicializarVacia(){

	Expresion::inicializarVacia();

	cromosoma_          = nullptr;
	longitud_cromosoma_ = profundidad_maxima_;
}


void Expresion_GAP :: liberarMemoriaCromosoma() {
	// y lo mismo con el cromosoma
	if (cromosoma_ != nullptr){
		delete [] cromosoma_;
		cromosoma_ = nullptr;
	}
}


void Expresion_GAP :: liberarMemoria(){

	liberarMemoriaCromosoma();
	Expresion::liberarMemoria();

}


void Expresion_GAP :: copiarDatos(const Expresion_GAP & otra){

	Expresion::copiarDatos(otra);

	longitud_cromosoma_ = otra.longitud_cromosoma_;

	// copiamos el cromosoma de la otra expresion
	if ( otra.cromosoma_ == nullptr) {
		cromosoma_ = nullptr;
	} else {
		asignarCromosoma(otra.cromosoma_, otra.longitud_cromosoma_);
	}
}


Expresion_GAP :: Expresion_GAP(const Expresion_GAP & otra) : Expresion(otra){
	// al inicializar vacia mantenemos la prfuncidad que queramos
	profundidad_maxima_ = otra.profundidad_maxima_;

	// inicializamos vacia para poner punteros a nullptr
	inicializarVacia();

	// copiamos la otra con el operador = ya implementado
	(*this) = otra;
}



Expresion_GAP & Expresion_GAP :: operator= (const Expresion_GAP & otra){
	// si no es ella misma
	if (this != &otra){
		// liberamos la memoria de la actual
		liberarMemoria();

		// copiamos los datos de la otra
		copiarDatos(otra);
	}

	// devolvemos el objeto actual
	return (*this);

}


void Expresion_GAP :: reservarMemoriaCromosoma(const int tam){
	if (tam > 0){
		cromosoma_ = new double[tam];
		longitud_cromosoma_ = tam;
	}
}



bool Expresion_GAP :: generarExpresionAleatoria(const unsigned longitud_maxima,
														const double prob_variable,
														const unsigned num_variables){

	bool exito = Expresion::generarExpresionAleatoria(longitud_maxima, prob_variable, num_variables);

	for (unsigned i = 0; i < longitud_arbol_; i++) {
		if (arbol_[i].getTipoNodo() == TipoNodo::NUMERO) {
			arbol_[i].setTerminoAleatorio(longitud_cromosoma_, num_variables);
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

	int pos_mutacion = Random::getInt(longitud_cromosoma_);

	if ( Random::getFloat() < 0.5) {
		cromosoma_[pos_mutacion] += delta(generacion, max_generaciones, 1.0 - cromosoma_[pos_mutacion]);
	} else {
		cromosoma_[pos_mutacion] -= delta(generacion, max_generaciones, cromosoma_[pos_mutacion]);
	}
}


bool Expresion_GAP :: totalmenteIguales ( const Expresion_GAP & otra) const {

	// comprobamos si el arbol es igual
	bool resultado = (*this) == otra;

	// si el arbol coincide, comparamos el cromosoma
	if ( resultado ) {
		for ( unsigned i = 0; i < getLongitudCromosoma(); i++) {
			resultado = resultado && comparar_reales(cromosoma_[i], otra.cromosoma_[i], 0.00005);
		}
	}

	return resultado;

}


double * Expresion_GAP :: getCromosoma () const {
	return cromosoma_;
}


void Expresion_GAP :: cruceBLXalfa(const Expresion_GAP & otra, Expresion_GAP & hijo1, Expresion_GAP & hijo2, const double alfa) const{

	if ( otra.longitud_cromosoma_ != this->longitud_cromosoma_ ) {
		std::cerr << "Cruzando dos cromosomas de distinta longitud" << std::endl;
	}

	double * cromosoma_actual = new double[this->longitud_cromosoma_];
	double * cromosoma_otro = new double[otra.longitud_cromosoma_];

	double punto_padre, punto_madre, seccion;

	for ( unsigned i = 0; i < longitud_cromosoma_; i++){
		punto_madre = this->cromosoma_[i];
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


	hijo1.asignarCromosoma(cromosoma_actual, this->longitud_cromosoma_);
	hijo2.asignarCromosoma(cromosoma_otro, otra.longitud_cromosoma_);

	delete [] cromosoma_actual;
	delete [] cromosoma_otro;

}


unsigned Expresion_GAP :: getLongitudCromosoma() const{
	return longitud_cromosoma_;
}



void Expresion_GAP :: asignarCromosoma(const double * nuevo_cromosoma, const unsigned longitud){

	liberarMemoriaCromosoma();

	reservarMemoriaCromosoma(longitud);

	memcpy(cromosoma_, nuevo_cromosoma, longitud*sizeof(double));

	longitud_cromosoma_ = longitud;

}


}
