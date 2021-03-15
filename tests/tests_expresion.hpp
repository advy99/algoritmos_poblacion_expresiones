#ifndef TESTS_EXPRESION
#define TESTS_EXPRESION

#include <gtest/gtest.h>
#include "expresion.hpp"
#include "aux_gap.hpp"

TEST (Expresion, IgualElMismo) {
	PG_ALGS::Expresion exp;

	EXPECT_EQ(exp, exp);
}

TEST (Expresion, IgualElMismoConDatos) {
	PG_ALGS::Expresion exp;

	exp.generarExpresionAleatoria(10, 0.3, 4);

	EXPECT_EQ(exp, exp);
}


TEST ( Expresion, ConstructorPorDefecto) {
	PG_ALGS::Expresion exp1;
	PG_ALGS::Expresion exp2;

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, ConstructorCopia) {
	PG_ALGS::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	PG_ALGS::Expresion exp2(exp1);

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, OperadorAsignacion) {
	PG_ALGS::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	PG_ALGS::Expresion exp2;
	exp2 = exp1;

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, TotalmenteIguales) {
	PG_ALGS::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	PG_ALGS::Expresion exp2;
	exp2 = exp1;

	EXPECT_TRUE(exp1.totalmenteIguales(exp2));
}


TEST ( Expresion, AsignarArbol) {
	PG_ALGS::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	PG_ALGS::Expresion exp2;

	exp2.asignarArbol(exp1.getArbol(), exp1.getLongitudArbol());

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, AsignarCromosoma) {
	PG_ALGS::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	PG_ALGS::Expresion exp2;

	exp2.asignarArbol(exp1.getArbol(), exp1.getLongitudArbol());

	EXPECT_EQ(exp1, exp2);
}

TEST (Expresion, MismaCadena) {
	PG_ALGS::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	PG_ALGS::Expresion exp2(exp1);

	EXPECT_EQ(exp1.stringExpresion(), exp2.stringExpresion());

}

TEST (Expresion, EvaluarDato) {

	PG_ALGS::Expresion exp1;

	PG_ALGS::Arbol arbol_tmp = new PG_ALGS::Nodo[5];

	arbol_tmp[0].setTipoNodo(PG_ALGS::TipoNodo::MAS);

	arbol_tmp[1].setTipoNodo(PG_ALGS::TipoNodo::VARIABLE);
	arbol_tmp[1].setValor(0);

	arbol_tmp[2].setTipoNodo(PG_ALGS::TipoNodo::POR);

	arbol_tmp[3].setTipoNodo(PG_ALGS::TipoNodo::VARIABLE);
	arbol_tmp[3].setValor(1);
	arbol_tmp[4].setTipoNodo(PG_ALGS::TipoNodo::NUMERO);
	arbol_tmp[4].setValor(1);

	double * n_cromosoma = new double[5];

	for ( int i = 0; i < 5; i++) {
		n_cromosoma[i] = 2.2;
	}

	exp1.asignarArbol(arbol_tmp, 5);
	exp1.asignarCromosoma(n_cromosoma, 5);

	delete [] arbol_tmp;
	delete [] n_cromosoma;

	std::vector<double> dato = {2.5, 3.2};

	double resultado = exp1.evaluarDato(dato);

	EXPECT_TRUE( PG_ALGS::comparar_reales(resultado, 9.54 ));

}

#endif
