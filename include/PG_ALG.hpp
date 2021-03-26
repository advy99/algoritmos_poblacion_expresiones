#ifndef PG_ALG_H_INCLUDED
#define PG_ALG_H_INCLUDED

#include "aux_pg_algs.hpp"
#include "poblacion.hpp"

namespace PG_ALGS {

template <class T>
class PG_ALG {
	protected:

		PG_ALG<T> ();

		/**
		  * @brief Datos con los que ajustar el algoritmo
		  *
		  */
		std::vector<std::vector<double> > datos;

		/**
		  * @brief Etiquetas para comprobar el error de la estimación.
		  */
		std::vector<double> output_datos;


		/**
		  * @brief Poblacion de expresiones con el que aplicaremos el algoritmo
		  * GA_P
		  */
		Poblacion<T> poblacion;


		/**
		  * @brief Profundidad maxima de las expresiones utilizadas
		  *
		  */

		unsigned prof_expresiones;


		/**
		  * @brief Inicializar GA_P vacio
		  *
		 */

		 void inicializarVacio();

		/**
		 *  @brief Selección de una nueva población por torneo a partir de
		 * la poblacion actual
		 *
		 * @param tam_torneo Tamaño del torneo
		 *
		 */

		 Poblacion<T> seleccionTorneo(const unsigned tam_torneo);



		 std::pair<bool, bool> aplicarMutacionesGP(T & hijo1, T & hijo2,
			 													 const double prob_mutacion);

	public:

		PG_ALG(const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var);

		void leerDatos(const std::string fichero_datos,
							const char char_comentario, const char delimitador = ',');

		/**
		  * @brief Cargar vectores de datos y etiquetas en GA_P
		  *
		  * @param caracteristicas Matriz de caracteristicas de cada dato
		  *
		  * @param etiquetas Vector de etiquetas, asociadas a cada fila de la matriz de datos
		  *
		  *
		 */

		void cargarDatos(const std::vector< std::vector<double> > & caracteristicas, const std::vector<double> & etiquetas );

		/**
		  * @brief Obtener el numero de variables de los datos
		  *
		  * @return Numero de variables del problema
		  */

		int getNumVariables() const ;

		/**
		  * @brief Obtener el numero de datos
		  *
		  * @return Numero de datos
		  */

		int getNumDatos() const;

		/**
		  * @brief Generar la población en base a los datos cargados
		  *
		  * @param tam_poblacion Tamaño de la poblacion a generar
		  *
		  * @param profundidad_exp Profundidad máxima de las expresiones de la población
		  *
		  * @param prob_var Probabilidad de que un nodo terminal sea una variable
		  *
		  * @param sustituir_actual Booleano para sustituir la población por una nueva, en caso de que ya exista una población
		  *
		  * @pre datos.size != 0
		  *
		  */

		void generarPoblacion(const unsigned tam_poblacion, const unsigned profundidad_exp, const double prob_var, const bool sustituir_actual = false);



		/**
		  * @brief Obtener los datos
		  *
		  * @return Datos.
		  */
		std::vector<std::vector<double> > getDatos() const;


		/**
		  * @brief Obtener el dato de la fila indice
		  *
		  * @param indice Indice del dato a obtener
		  *
		  * @pre indice >= 0 && indice < datos.size
		  *
		  * @return Dato de la columna indice.
		  */
		std::vector<double > getDato(const unsigned indice) const;


		/**
		  * @brief Obtener las etiquetas asociadas a los datos
		  *
		  * @return Etiquetas asociadas a los datos.
		  */

		std::vector<double> getOutputDatos() const;


		/**
		  * @brief Obtener la etiqueta asociada al dato indice
		  *
		  * @param indice Indice de la etiqueta a obtener
		  *
		  * @pre indice >= 0 && indice < output_datos.size
		  *
		  * @return Etiqueta asociada al dato indice.
		  */

		double getOutputDato(const unsigned indice) const ;

		/**
		  * @brief Obtener el mejor individuo de la poblacion.
		  *
		  * @return Mejor individuo de la población
		  */

		T getMejorIndividuo() const;

		/**
		 * @brief Obtener la profundidad máxima de las expresiones
		 *
		 * @return Profundidad máxima de las expresiones
		 */

		unsigned getMaxProfExpresiones() const;




		void aplicarElitismo(const Poblacion<T> & poblacion_antigua);

};



} // namespace PG_ALGS


#include "PG_ALG.tpp"


#endif
