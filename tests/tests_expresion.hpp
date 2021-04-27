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

	exp2.asignarArbol(exp1.getArbol());

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, AsignarCromosoma) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2;

	exp2.asignarArbol(exp1.getArbol());

	EXPECT_EQ(exp1, exp2);
}

TEST (Expresion, MismaCadena) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generarExpresionAleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2(exp1);

	EXPECT_EQ(exp1.stringExpresion(), exp2.stringExpresion());

}

TEST (Expresion, EvaluarDato) {

	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp;
	arbol_tmp.resize(5);

	arbol_tmp[0].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].setValor(0);

	arbol_tmp[2].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].setValor(1);
	arbol_tmp[4].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	arbol_tmp[4].setValor(1);

	std::vector<double> cromosoma;
	cromosoma.resize(5);

	for ( int i = 0; i < 5; i++) {
		cromosoma[i] = 2.2;
	}

	exp1.asignarArbol(arbol_tmp);
	exp1.asignarCromosoma(cromosoma);

	std::vector<double> dato = {2.5, 3.2};

	double resultado = exp1.evaluarDato(dato);

	EXPECT_TRUE( algoritmos_poblacion_expresiones::comparar_reales(resultado, 9.54 ));

}


TEST (Expresion, ObtenerSurarbol) {

	algoritmos_poblacion_expresiones::Expresion exp1;

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp;
	arbol_tmp.resize(5);

	arbol_tmp[0].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].setValor(0);

	arbol_tmp[2].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].setValor(1);
	arbol_tmp[4].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[4].setValor(2);

	exp1.asignarArbol(arbol_tmp);

	std::vector<algoritmos_poblacion_expresiones::Nodo> subarbol = exp1.obtenerSubarbol(exp1.getArbol(), 2);

	std::vector<algoritmos_poblacion_expresiones::Nodo> subarbol_real;

	for ( unsigned i = 2; i < arbol_tmp.size(); i++) {
		subarbol_real.push_back(arbol_tmp[i]);
	}

	EXPECT_TRUE( subarbol == subarbol_real );

}
#include <iostream>

TEST (Expresion, CruzarArbol) {

	algoritmos_poblacion_expresiones::Expresion exp1;

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp;
	arbol_tmp.resize(5);

	arbol_tmp[0].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].setValor(0);

	arbol_tmp[2].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].setValor(1);
	arbol_tmp[4].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	arbol_tmp[4].setValorNumerico(1.2);

	std::vector<double> cromosoma;
	cromosoma.resize(5);

	for ( int i = 0; i < 5; i++) {
		cromosoma[i] = 2.2;
	}

	exp1.asignarArbol(arbol_tmp);

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp2;
	arbol_tmp2.resize(3);

	arbol_tmp2[0].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp2[1].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp2[1].setValor(0);

	arbol_tmp2[2].setTipoNodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	arbol_tmp2[2].setValorNumerico(1.45);

	algoritmos_poblacion_expresiones::Expresion exp2;
	exp2.asignarArbol(arbol_tmp2);

	algoritmos_poblacion_expresiones::Expresion hijo = exp1;
	algoritmos_poblacion_expresiones::Expresion hijo2 = exp1;


	exp1.intercambiarSubarbol(exp2, 4, 0, hijo);
	exp2.intercambiarSubarbol(exp1, 0, 4, hijo2);

	EXPECT_TRUE( hijo.getLongitudArbol() == 7 && hijo2.getLongitudArbol() == 1);

}

#endif
