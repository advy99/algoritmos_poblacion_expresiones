/**
  * \@file ReglaClasificacion.hpp
  * @brief Fichero cabecera de la clase AlgoritmoPG
  *
  */


#ifndef REGLA_CLASIFICACION_H_INCLUDED
#define REGLA_CLASIFICACION_H_INCLUDED

#include <map>


namespace algoritmos_poblacion_expresiones {

/**
  *  @brief Clase ReglaClasificacion
  *
  *  Una instancia del tipo ReglaClasificacion representará una regla de tipo
  *  IF-THEN, donde se encuentra un conjunto de antecedentes asociados a una clase
  *
  *
  * @tparam DataType Tipo de dato utilizado por los datos que usará el algoritmo.
  * @tparam ClassType Tipo de dato utilizado para representar la clase asociada a una observación.
  *
  * @author Antonio David Villegas Yeguas
  * @date Febrero 2022
  */



class ReglaClasificacion {
	private:

		/**
		  * @brief Conjunto de antecedentes de la regla
		  */

		std::map<std::string, std::string> antecedentes_;

		/**
		  * @brief Clase asociada a la regla
		  */

		std::string clase_;

	public:

		/**
		  * @brief Constructor sin argumentos
		  */

		ReglaClasificacion() = default;


		/**
		  * @brief Constructor de copia
		  */

		ReglaClasificacion(const ReglaClasificacion & otra_regla) = default;

		/**
		  * @brief Operador de asignacion
		  */

		ReglaClasificacion & operator=(const ReglaClasificacion & otra_regla) = default;

		/**
		  * @brief Operador de igualdad
		  */

		bool operator== (const ReglaClasificacion & otra_regla) = default;

		/**
		  * @brief Consultar el número de antecedentes que conforma la regla
		  */

		std::size_t num_antecedentes() const;

		/**
		  * @brief Cambiar la clase asociada a la regla.
		  *
		  * @param nueva_clase String con la nueva clase asocada a la regla.
		  *
		  */

		void cambiar_clase(const std::string & nueva_clase);

		/**
		  * @brief Modificar un antecedente con un nuevo valor.
		  *
		  * @param clave Antecedente a modificar.
		  * @param valor Nuevo valor a asignar al antecedente.
		  *
		  */

		void modificar_antecedente(const std::string & clave, const std::string & valor);

		/**
		  * @brief Modificar un antecedente con un nuevo valor.
		  *
		  * @param antecedente Pareja de clave-valor, con la clave a modificar y el nuevo valor a asignar.
		  *
		  */

		void modificar_antecedente(const std::pair<std::string, std::string> & antecedente);

		/**
		  * @brief Eliminar un antecedente.
		  *
		  * @param clave Antecedente a eliminar.
		  *
		  */

		void eliminar_antecedente(const std::string & clave);


		/**
		  * @brief Consultar el valor de un antecedente.
		  *
		  * @param clave Antecedente a consultar.
		  *
		  */

		std::string consultar_antecedente(const std::string & clave);


		friend std::ostream & operator<< (std::ostream & os,
													 const ReglaClasificacion & exp);


}




} // namespace algoritmos_poblacion_expresiones

#enfif
