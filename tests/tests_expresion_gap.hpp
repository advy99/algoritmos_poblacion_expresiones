#ifndef TESTS_EXPRESION_GAP
#define TESTS_EXPRESION_GAP

#include <gtest/gtest.h>
#include "algoritmos_poblaciones/Expresion.hpp"
#include "algoritmos_poblaciones/Expresion_GAP.hpp"

TEST (Expresion_GAP, IgualElMismo) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp;

	EXPECT_EQ(exp, exp);
}

TEST (Expresion_GAP, IgualElMismoConDatos) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp;

	exp.generar_expresion_aleatoria(10, 0.3, 4);

	EXPECT_EQ(exp, exp);
}


TEST ( Expresion_GAP, ConstructorPorDefecto) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp1;
	algoritmos_poblacion_expresiones::Expresion_GAP exp2;

	// el cromosoma es aleatorio, así que por asegurarnos que esta igual
	exp1.asignar_cromosoma(exp2.get_cromosoma());

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion_GAP, ConstructorCopia) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion_GAP exp2(exp1);

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion_GAP, OperadorAsignacion) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion_GAP exp2;
	exp2 = exp1;

	EXPECT_EQ(exp1, exp2);
}

// TEST ( Expresion, TotalmenteIguales) {
// 	algoritmos_poblacion_expresiones::Expresion exp1;
//
// 	exp1.generar_expresion_aleatoria(10, 0.3, 3);
//
// 	algoritmos_poblacion_expresiones::Expresion exp2;
// 	exp2 = exp1;
//
// 	EXPECT_TRUE(exp1.totalmenteIguales(exp2));
// }


TEST ( Expresion_GAP, asignar_cromosoma) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion_GAP exp2;

	exp2.asignar_arbol(exp1.get_arbol());
	exp2.asignar_cromosoma(exp1.get_cromosoma());

	EXPECT_EQ(exp1, exp2);
}

TEST (Expresion_GAP, MismaCadena) {
	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion_GAP exp2(exp1);

	EXPECT_EQ(exp1.string_expresion(), exp2.string_expresion());

}

TEST (Expresion_GAP, evaluar_dato) {

	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp;
	arbol_tmp.resize(5);

	arbol_tmp[0].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].set_valor(0);

	arbol_tmp[2].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].set_valor(1);
	arbol_tmp[4].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	arbol_tmp[4].set_valor(1);

	std::vector<double> cromosoma;
	cromosoma.resize(5);

	for ( int i = 0; i < 5; i++) {
		cromosoma[i] = 2.2;
	}

	exp1.asignar_arbol(arbol_tmp);
	exp1.asignar_cromosoma(cromosoma);

	std::vector<double> dato = {2.5, 3.2};

	double resultado = exp1.evaluar_dato(dato);

	EXPECT_TRUE( algoritmos_poblacion_expresiones::comparar_reales(resultado, 9.54 ));

}


TEST (Expresion_GAP, ObtenerSurarbol) {

	algoritmos_poblacion_expresiones::Expresion_GAP exp1;

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp;
	arbol_tmp.resize(5);

	arbol_tmp[0].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].set_valor(0);

	arbol_tmp[2].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].set_valor(1);
	arbol_tmp[4].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[4].set_valor(2);

	exp1.asignar_arbol(arbol_tmp);

	std::vector<algoritmos_poblacion_expresiones::Nodo> subarbol = exp1.obtener_subarbol(exp1.get_arbol(), 2);

	std::vector<algoritmos_poblacion_expresiones::Nodo> subarbol_real;

	for ( unsigned i = 2; i < arbol_tmp.size(); i++) {
		subarbol_real.push_back(arbol_tmp[i]);
	}

	EXPECT_TRUE( subarbol == subarbol_real );

}

#endif
