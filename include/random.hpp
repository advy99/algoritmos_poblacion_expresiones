/**
  * @file random.hpp
  * @brief Fichero cabecera de la clase Random
  *
  */

#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

/**
  *  @brief Clase Random
  *
  * Una instancia del tipo Random será un generador de números aleatorios.
  *
  *
  * @author Antonio David Villegas Yeguas
  * @date Julio 2020
  */


class Random{
	private:

		/**
		  * @page repRandom Representación de la clase Random
		  *
		  * @section invRandom Invariante de la representación
		  *
		  * El invariante es; SEED ha de estar inicializado
		  *
		  *
		  */

		static unsigned long SEED;
		static const unsigned long int MASK;
		static const unsigned long int PRIME;
		static const double SCALE;
		
		/**
		  * @brief Constructor sin parámetros que iniciliza la semilla a un valor aleatorio
		  */

		Random() = delete;



	public:

		/**
		 * @brief Inicializar la semilla
		 *
		 */

		static void setSeed(const unsigned long seed);



		/**
		  * @brief Destructor de la clase Random
		  *
		  */

		~Random();

		/**
		  * @brief Constructor de copia. ELIMINADO AL SER UNA CLASE SINGLETON
		  *
		  */


		Random(const Random & otro) = delete;

		/**
		  * @brief Operador =. ELIMINADO AL SER UNA CLASE SINGLETON
		  *
		  */
		Random & operator = (const Random & otro) = delete;

		/**
		  * @brief Obtener el valor de la semilla
		  *
		  * @return Valor actual de la semilla
		  */

		static unsigned long getSeed() ;


		/**
		  * @brief Generar un valor real aleatorio entre [0, 1[
		  *
		  * @return Número aleatorio entre [0, 1[
		  */

		static float getFloat();


		/**
		  * @brief Generar un valor real aleatorio entre dos valores dados
		  *
		  * @param LOW Límite inferior para el valor a generar
		  * @param HIGH Límite superior para el valor a generar
		  *
		  * @return Número real aleatorio entre [LOW, HIGH[
		  */

		static float getFloat(const float LOW, const float HIGH);

		/**
		  * @brief Generar un valor real aleatorio entre 0 y un valor dado
		  *
		  * @param HIGH Límite superior para el valor a generar
		  *
		  * @return Número real aleatorio entre [0, HIGH[
		  */

		static float getFloat(const float HIGH);


		/**
		  * @brief Generar un valor entero aleatorio entre dos valores dados
		  *
		  * @param LOW Límite inferior para el valor a generar
		  * @param HIGH Límite superior para el valor a generar
		  *
		  * @return Número entero aleatorio entre [LOW, HIGH[
		  */

		static int getInt(const int LOW, const int HIGH);

		/**
		  * @brief Generar un valor entero aleatorio entre 0 y un valor dado
		  *
		  * @param HIGH Límite superior para el valor a generar
		  *
		  * @return Número entero aleatorio entre [0, HIGH[
		  */

		static int getInt(const int HIGH);

};

#endif
