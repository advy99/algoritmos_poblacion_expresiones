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
  * @tparam DataType Tipo de dato utilizado por los datos que usará el algoritmo.
  * @tparam ClassType Tipo de dato utilizado para representar la clase asociada a una observación.
  *
  * @author Antonio David Villegas Yeguas
  * @date Abril 2021
  */

template <class DataType, class ClassType>
class AlgoritmoPG : public AlgoritmoPoblacion<Expresion, DataType, ClassType> {
	private:

		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::poblacion_;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::datos_;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::output_datos_;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::prof_expresiones_;

		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::leer_datos;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::cargar_datos;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::inicializar_vacio;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::get_num_variables;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::get_max_prof_expresiones;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::seleccion_torneo;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::generar_poblacion;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::aplicar_elitismo;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::aplicar_mutaciones_GP;
		using AlgoritmoPoblacion<Expresion, DataType, ClassType>::inicializar;




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

		AlgoritmoPG(const std::vector<std::vector<DataType> > & datos, const std::vector<ClassType> & etiquetas,
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


#include "algoritmos_poblaciones/AlgoritmoPG.tpp"


#endif
