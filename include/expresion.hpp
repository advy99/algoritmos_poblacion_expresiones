

#ifndef EXPRESION_H_INCLUDED
#define EXPRESION_H_INCLUDED

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
		bool evaluado;
		unsigned longitud_arbol;
		Arbol arbol;

	public:
		Expresion();
		~Expresion();

		bool estaEvaluado() const;
		double getFitness() const;
		unsigned getLongitudArbol() const;

		double evaluar();

		void intercambiarSubarbol(const int posicion, const Arbol subarbol);


};


#endif
