#ifndef GA_P_H_INCLUDED
#define GA_P_H_INCLUDED

#include <vector>
#include "random.hpp"
#include "poblacion.hpp"


class GA_P{
	private:

		Poblacion poblacion;
		static int num_variables;
		static int num_datos;

		static std::vector<std::vector<double> > datos;
		static std::vector<double> output_datos;

		bool leerDatos(const std::string fichero_datos, const char char_comentario);

	public:
		GA_P(const std::string fichero_datos, const char char_comentario);
		~GA_P() = default;

		static int getNumVariables() const;
		static int getNumDatos() const;
		static std::vector<std::vector<double> > getDatos() const;


};

#endif
