#ifndef TESTS_EXPRESION
#define TESTS_EXPRESION

#include <gtest/gtest.h>
#include "expresion.hpp"
#include "aux_gap.hpp"

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

TEST (Expresion, MismaCadena) {
	GA_P::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	GA_P::Expresion exp2(exp1);

	EXPECT_EQ(exp1.stringExpresion(), exp2.stringExpresion());

}

TEST (Expresion, EvaluarDato) {

	GA_P::Expresion exp1;

	GA_P::Arbol arbol_tmp = new GA_P::Nodo[5];

	arbol_tmp[0].setTipoNodo(GA_P::TipoNodo::MAS);

	arbol_tmp[1].setTipoNodo(GA_P::TipoNodo::VARIABLE);
	arbol_tmp[1].setValor(0);

	arbol_tmp[2].setTipoNodo(GA_P::TipoNodo::POR);

	arbol_tmp[3].setTipoNodo(GA_P::TipoNodo::VARIABLE);
	arbol_tmp[3].setValor(1);
	arbol_tmp[4].setTipoNodo(GA_P::TipoNodo::NUMERO);
	arbol_tmp[4].setValor(1);

	double * n_cromosoma = new double[5];

	for ( int i = 0; i < 5; i++) {
		n_cromosoma[i] = 2.2;
	}

	exp1.asignarArbol(arbol_tmp, 5);
	exp1.asignarCromosoma(n_cromosoma, 5);

	std::vector<double> dato = {2.5, 3.2};

	double resultado = exp1.evaluarDato(dato);

	EXPECT_TRUE( GA_P::comparar_reales(resultado, 9.54 ));

}

#endif
