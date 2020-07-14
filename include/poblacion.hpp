
#ifndef POBLACION_H_INCLUDED
#defined POBLACION_H_INCLUDED

#include "expresion.hpp"

class Poblacion{
	private:
		Expresion * poblacion;
		unsigned tam_poblacion;
		Expresion mejor_individuo;

	public:
		Poblacion();
		~Poblacion();

		Expresion getMejorIndividuo() const;
		unsigned getTamPoblacion() const;
		Expresion getIndividuo(const unsigned indice) const;
		Expresion setIndividuo(const unsigned indice, const Expresion individuo);
}



#endif
