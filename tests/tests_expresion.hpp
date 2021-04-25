#ifndef TESTS_EXPRESION
#define TESTS_EXPRESION

#include <gtest/gtest.h>
#include "algoritmos_poblaciones/Expresion.hpp"
#include "algoritmos_poblaciones/Expresion_GAP.hpp"

TEST (Expresion, IgualElMismo) {
	algoritmos_poblacion_expresiones::Expresion exp;

	EXPECT_EQ(exp, exp);
}

TEST (Expresion, IgualElMismoConDatos) {
	algoritmos_poblacion_expresiones::Expresion exp;

	exp.generarExpresionAleatoria(10, 0.3, 4);

	EXPECT_EQ(exp, exp);
}


TEST ( Expresion, ConstructorPorDefecto) {
	algoritmos_poblacion_expresiones::Expresion exp1;
	algoritmos_poblacion_expresiones::Expresion exp2;

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, ConstructorCopia) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2(exp1);

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, OperadorAsignacion) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2;
	exp2 = exp1;

	EXPECT_EQ(exp1, exp2);
}

// TEST ( Expresion, TotalmenteIguales) {
// 	algoritmos_poblacion_expresiones::Expresion exp1;
//
// 	exp1.generarExpresionAleatoria(10, 0.3, 3);
//
// 	algoritmos_poblacion_expresiones::Expresion exp2;
// 	exp2 = exp1;
//
// 	EXPECT_TRUE(exp1.totalmenteIguales(exp2));
// }


TEST ( Expresion, AsignarArbol) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2;

	exp2.asignarArbol(exp1.getArbol(), exp1.getLongitudArbol());

	EXPECT_EQ(exp1, exp2);
}
//
// TEST ( Expresion, AsignarCromosoma) {
// 	algoritmos_poblacion_expresiones::Expresion exp1;
//
// 	exp1.generarExpresionAleatoria(10, 0.3, 3);
//
// 	algoritmos_poblacion_expresiones::Expresion exp2;
//
// 	exp2.asignarArbol(exp1.getArbol(), exp1.getLongitudArbol());
//
// 	EXPECT_EQ(exp1, exp2);
// }

TEST (Expresion, MismaCadena) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2(exp1);

	EXPECT_EQ(exp1.stringExpresion(), exp2.stringExpresion());

}

TEST (Expresion, EvaluarDato) {

	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	algoritmos_poblacion_expresiones::Arbol arbol_tmp = new algoritmos_poblacion_expresiones::Nodo[5];

	arbol_tmp[0].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].setValor(0);

	arbol_tmp[2].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].setValor(1);
	arbol_tmp[4].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
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

	EXPECT_TRUE( algoritmos_poblacion_expresiones::comparar_reales(resultado, 9.54 ));

}

#endif
