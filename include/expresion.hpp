

#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED

#include <cmath>

// aqui faltan tipos, tengo que revisar el paper + los que use
enum class TipoNodo {Numero, Variable, Mas, Menos, Por, Entre};

struct {
	TipoNodo tipo_nodo;
	double valor;
} Nodo;

typedef Nodo * Arbol;

class Expresion{
	private:
		double fitness;
		bool evaluada;
		unsigned longitud_arbol;
		unsigned profundidad_maxima;
		Arbol arbol;

		void inicializarVacia();

		void copiarDatos(const Expresion & otra);
		void reservarMemoria(const unsigned tam);
		void liberarMemoria();

		void generarExpresionAleatoria(const unsigned longitud);

	public:
		Expresion(const unsigned prof_maxima);
		Expresion(const unsigned prof_maxima, const unsigned longitud);
		Expresion(const Expresion & otra);
		~Expresion();

		bool estaEvaluado() const;
		double getFitness() const;
		unsigned getLongitudArbol() const;

		double evaluar();

		void intercambiarSubarbol(const int posicion, const Arbol subarbol);


};


#endif
