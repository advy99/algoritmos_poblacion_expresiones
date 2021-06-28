/**
  * \@file AlgoritmoPG.hpp
  * @brief Fichero cabecera de la clase AlgoritmoPG
  *
  */


#ifndef ALGORITMO_PG_H_INCLUDED
#define ALGORITMO_PG_H_INCLUDED


#include "algoritmos_poblaciones/AlgoritmoPoblacion.hpp"


namespace algoritmos_poblacion_expresiones {

/**
  *  @brief Clase AlgoritmoPG
  *
  *  Una instancia del tipo AlgoritmoPG representará un estimador para los datos
  *  dados, utilizando una Poblacion, conjunto de AlgoritmoPG.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Abril 2021
  */

class AlgoritmoPG : public AlgoritmoPoblacion<Expresion> {
	private:

		using AlgoritmoPoblacion<Expresion>::poblacion_;
		using AlgoritmoPoblacion<Expresion>::datos_;
		using AlgoritmoPoblacion<Expresion>::output_datos_;
		using AlgoritmoPoblacion<Expresion>::prof_expresiones_;

		using AlgoritmoPoblacion<Expresion>::leerDatos;
		using AlgoritmoPoblacion<Expresion>::inicializarVacio;
		using AlgoritmoPoblacion<Expresion>::getNumVariables;
		using AlgoritmoPoblacion<Expresion>::getMaxProfExpresiones;
		using AlgoritmoPoblacion<Expresion>::seleccionTorneo;
		using AlgoritmoPoblacion<Expresion>::generarPoblacion;
		using AlgoritmoPoblacion<Expresion>::aplicarElitismo;
		using AlgoritmoPoblacion<Expresion>::aplicarMutacionesGP;
		using AlgoritmoPoblacion<Expresion>::inicializar;




		/**
		  * @page repPG Representación de la clase AlgoritmoPG
		  *
		  * @section invPG Invariante de la representación
		  *
		  * El invariante es; datos.size > 0 y output_datos.size == datos.size
		  *
		  * @section faPG Función de abstracción
		  *
		  * Un objeto valido @e rep de la clase AlgoritmoPG representa un conjunto de
		  * datos con sus respectivas etiquetas
		  *
		  * rep.datos
		  * rep.output_datos
		  *
		  * Así como una poblacion de expresiones para estimar los datos.
		  *
		  * rep.poblacion
		  *
		  */


	public:

		/**
		 *  @brief Contructor con 6 parametros, para utilizar el AlgoritmoPG dados una serie de datos con sus etiquetas asociadas
		 *
		 *  @param datos Datos a utilizar para el ajuste
		 *  @param etiquetas Etiquetas asociadas a dichos datos
		 *  @param seed Semilla aleatoria a utilizar
		 *  @param tam_poblacion Tamaño de la poblacion del algoritmo
		 *  @param prof Profundidad máxima de las expresiones utilizadas
		 *  @param prob_var Probabilidad de que un Nodo sea una variable
		 *
		 */

		AlgoritmoPG(const std::vector<std::vector<double> > & datos, const std::vector<double> & etiquetas,
						const unsigned long seed, const unsigned tam_poblacion, const unsigned prof, const double prob_var);


		/**
		  * @brief Constructor con siete parámetros
		  *
		  * @param fichero_datos Fichero donde se almacenan los datos
		  *
		  * @param char_comentario Caracter que marca que una linea es un
		  * comentario y ha de ser ignorada.
		  *
		  * @param tam_poblacion Tamaño de la población que conformará el AlgoritmoGA_P
		  *
		  * @param prob_var Probabilidad de que en una expresión de la población
		  * un nodo hoja sea una variable.
		  *
		  * @param seed Semilla al utilizar en AlgoritmoGA_P. No tiene efecto si la
		  * la semilla ya ha sido inicializada antes
		  *
		  * @param delimitador Caracter que marca como están separados los
		  * datos de entrada. Por defecto ','
		  *
		  * @param prof Profundidad máxima de las expresiones con las que
		  * aprenderá el algoritmo. Por defecto 10
		  *
		  *
		  */

		AlgoritmoPG(const std::string fichero_datos, const char char_comentario,
			  const unsigned tam_poblacion, const double prob_var,
			  const unsigned long seed = time(nullptr),
			  const char delimitador = ',', const unsigned prof = 20);


		/**
		  * @brief Destructor
		  *
		  */

		~AlgoritmoPG();


		/**
		 *  @brief Ajustar la poblacion utilizando los datos actuales con los parametros dados
		 *
		 *  @param parametros Parametros a utilizar en el ajuste del algoritmo
		 *
		 **/

		void ajustar(const Parametros & parametros);

};

}



#endif
