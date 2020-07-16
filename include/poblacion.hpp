
#ifndef POBLACION_H_INCLUDED
#defined POBLACION_H_INCLUDED

#include "expresion.hpp"

class Poblacion{
	private:
		Expresion * poblacion;
		unsigned tam_poblacion;
		unsigned tam_reservado;
		Expresion mejor_individuo;

		void reservarMemoria(const unsigned tam);
		void liberarMemoria();
		void copiarDatos(const Poblacion & otra);

	public:
		Poblacion();
		~Poblacion();

		Expresion getMejorIndividuo() const;
		unsigned getTamPoblacion() const;
		Expresion getIndividuo(const unsigned indice) const;
		Expresion setIndividuo(const unsigned indice, const Expresion individuo);

		void evaluarPoblacion();

}



#endif
