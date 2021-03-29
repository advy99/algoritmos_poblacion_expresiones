#ifndef EXPRESION_GAP_H_INCLUDED
#define EXPRESION_GAP_H_INCLUDED


#include "Expresion.hpp"
#include "aux_pg_algs.hpp"


namespace algoritmos_poblaciones {

class Expresion_GAP : public Expresion {
	private:
		/**
		  * @brief Array donde almacenaremos los valores de las constantes
		  * numéricas para aprenderlos
		  *
		  */

		double * cromosoma = nullptr;

		/**
		  * @brief Longitud del array cromosoma
		  *
		  */

		unsigned longitud_cromosoma;

		/**
		  * @brief Inicializar una expresión vacia.
		  *
		  * @pre La expresión no tiene memoria dinámica reservada.
		  *
		  * @post La expresión queda como una expresión vacia.
		  */

		void inicializarVacia() override;

		/**
		  * @brief Copiar datos de una expresión dada a la expresión.
		  *
		  * @param otra Expresión de donde copiar los datos.
		  *
		  * @pre La expresión está vacia: arbol == nullptr && cromosoma == nullptr
		  *
		  */

		void copiarDatos(const Expresion_GAP & otra);


		/**
		  * @brief Reservar memoria para un cromosoma de tamaño tam
		  *
		  * @param tam Tamaño a reservar para el cromosoma.
		  *
		  * @pre cromosoma == nullptr
		  *
		  */

		void reservarMemoriaCromosoma(const int tam);


		/**
		  * @brief Liberar la memoria dinámica utilizada por el cromosoma.
		  *
		  */

		void liberarMemoriaCromosoma();


		/**
		  * @brief Liberar la memoria dinámica utilizada y limpiar la expresión.
		  *
		  */

 	  	void liberarMemoria() override;


		/**
		 * @brief Inicializar el cromosoma de constantes asociadas a la Expresion.
		 *
		 *
		 */

		void inicializarCromosoma();

		/**
		 * @brief Copiar cromosoma dado al cromosoma de la Expresion actual
		 *
		 * @param otro_cromosoma Cromosoma a copiar
		 *
		 */

		void copiarCromosoma(const double * otro_cromosoma);


	 	/**
		  * @brief Función delta para la mutación no uniforme de GA
		  *
		  * @param generacion Generación en la que se aplica la mutación
		  * @param max_gen Número máximo de generaciones al entrenar.
		  * @param valor Valor del cromosoma al aplicar la mutación
		  *
		  * @return Valor a modificar el cromosoma con el valor dado
		  */


		double delta(const int generacion, const int max_gen, const double valor);


		double obtenerNumero(const Nodo & n) const override;


	public:
		/**
		  * @brief Constructor con un parámetro, genera una expresión vacia.
		  *
		  * @param prof_max Profundidad máxima de la expresión.
		  *
		  */

		Expresion_GAP(const unsigned prof_max = 10);

		/**
		  * @brief Constructor con un parámetro. Crear una expresion a partir del
		  * subarbol dado
		  *
		  * @param subarbol Subarbol para crear la expresion
		  * @param prof_max Profundidad máxima de la Expresion a crear
		  *
		  * @pre subarbol != nullptr
		  */

		Expresion_GAP(const Arbol subarbol, const unsigned prof_max = 10);



		/**
		  * @brief Constructor con dos parámetro, generar una expresión aleatoria.
		  *
		  * @param longitud_max Longitud de la expresión a generar.
		  * @param prob_variable Probabilidad de que un nodo sea una variable.
		  * @param num_vars Numero de variables que podrá usar la expresion
		  * @param prof_max Profundidad máxima de la Expresion a crear
		  *
		  */

		Expresion_GAP(const unsigned longitud_max, const double prob_variable,
					 	  const unsigned num_vars, const unsigned prof_max = 10);

		/**
		  * @brief Constructor de copia.
		  *
		  * @param otra Expresión a copiar.
		  *
		  */

		Expresion_GAP(const Expresion_GAP & otra);

		/**
		  * @brief Destructor de la expresión.
		  *
		  */

		~Expresion_GAP();

		/**
		  * @brief Generar la expresión de forma aleatoria.
		  *
		  * @param longitud_max Longitud máxima de la expresión aleatoria
		  * @param prob_variable Probabilidad de que un símbolo terminal
		  * sea una variable y no un número
		  * @param num_variables Número de varíables disponibles para usar
		  * en la expresión
		  *
		  * @return Booleano: True si ha conseguido generar la expresion
		  * correctamente, false en caso contrario
		  */

		bool generarExpresionAleatoria(const unsigned longitud_max,
			 									 const double prob_variable,
												 const unsigned num_variables) override;

		/**
 		  * @brief Consultar la longitud del cromosoma.
 		  *
 		  * @return Longitud del cromosoma.
 		  */

 		unsigned getLongitudCromosoma() const;


		/*
		 * @brief Dado un cromosoma, asignar dicho cromosoma a la expresion actual
		 *
		 * @param nuevo_cromosoma Cromosoma que formará la expresion
		 *
		 * @param longitud Longitud del nuevo cromosoma dado
		 *
		 */

		void asignarCromosoma(const double * nuevo_cromosoma, const unsigned longitud);

		/**
		  * @brief Operador de asignación de una expresión. Asignamos una
		  * expresión a otra.
		  *
		  * @param otra Expresión a copiar.
		  *
		  * @return Referencia a la expresion
		  */

		Expresion_GAP & operator= (const Expresion_GAP & otra);


		/**
		 * @brief Operador de cruce para los cromosomas de las expresiones.
		 * Al cruzar dos cromosomas obtendremos otros dos nuevos cromosomas.
		 *
		 * @param otra Expresion con la que cruzar el cromosoma.
		 * @param hijo1 Expresión donde se almacenará el resultado del cruce.
		 * @param hijo2 Expresión donde se almacenará el resultado del cruce.
		 * @param alfa Valor alfa del metodo BLX-alfa, posible extension del
		 * rango entre dos valores
		 *
		 */


		void cruceBLXalfa(const Expresion_GAP & otra, Expresion_GAP & hijo1, Expresion_GAP & hijo2, const double alfa = 0.3) const;


		/**
		 * @brief Obtener donde está almacenado el cromosoma
		 *
		 */

		double * getCromosoma() const;

		/**
		 *
		 *  @brief Mutación no uniforme de la parte de algoritmo genético (cromosoma)
		 *
		 *  @param generacion Generación en la que se aplica la mutación
		 *  @param max_gen Número máximo de generaciones al entrenar.
		 *
		 */

		void mutarGA(const int generacion, const int max_gen);

		/*
		 * @brief Operador para comparar si dos expresiones son iguales, tanto arbol como cromosoma
		 *
		 * @param otra Expresión a comparar con la actual
		 *
		 * @pre Los cromosomas son de la misma longitud
		 *
		 */

		bool totalmenteIguales(const Expresion_GAP & otra) const;


};



}



#endif
