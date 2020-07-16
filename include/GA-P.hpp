#ifndef GA_P_H_INCLUDED
#define GA_P_H_INCLUDED

#include <vector>
#include "random.hpp"
#include "poblacion.hpp"


class GA_P{
	private:

		Random * generador_aleatorios;
		Poblacion poblacion;
		static int num_variables;

	public:
		GA_P();
		~GA_P();

		static int getNumVariables() const;


};

#endif
