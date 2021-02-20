#ifndef TESTS_EXPRESION
#define TESTS_EXPRESION

#include <gtest/gtest.h>
#include "expresion.hpp"

TEST (Expresion, IgualElMismo) {
	GA_P::Expresion exp;

	EXPECT_EQ(exp, exp);
}

TEST (Expresion, IgualElMismoConDatos) {
	GA_P::Expresion exp;

	exp.generarExpresionAleatoria(10, 0.3, 4);

	EXPECT_EQ(exp, exp);
}


TEST ( Expresion, ConstructorPorDefecto) {
	GA_P::Expresion exp1;
	GA_P::Expresion exp2;

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, ConstructorCopia) {
	GA_P::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	GA_P::Expresion exp2(exp1);

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, OperadorAsignacion) {
	GA_P::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	GA_P::Expresion exp2;
	exp2 = exp1;

	EXPECT_EQ(exp1, exp2);
}

#endif
