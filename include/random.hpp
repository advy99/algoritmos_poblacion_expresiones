/* GENERADOR DE NUMEROS ALEATORIOS */

#ifndef __RANDOM_PPIO_H
#define __RANDOM_PPIO_H

class Random{
	private:
		unsigned long SEED;
		const unsigned long int MASK = 2147483647;
		const unsigned long int PRIME = 65539;
		const double SCALE = 0.4656612875e-9;


	public:
		Random();
		Random(const unsigned long seed);

		unsigned long getSeed() const;

		float getFloat();
		float getFloat(const float LOW, const float HIGH);
		float getFloat(const float HIGH);


		int getInt(const int LOW, const int HIGH);
		int getInt(const int HIGH);

};

#endif
