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

	exp.generar_expresion_aleatoria(20, 0.3, 4);

	EXPECT_EQ(exp, exp);
}


TEST ( Expresion, ConstructorPorDefecto) {
	algoritmos_poblacion_expresiones::Expresion exp1;
	algoritmos_poblacion_expresiones::Expresion exp2;

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, ConstructorCopia) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2(exp1);

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, OperadorAsignacion) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2;
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


TEST ( Expresion, asignar_arbol) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2;

	exp2.asignar_arbol(exp1.get_arbol());

	EXPECT_EQ(exp1, exp2);
}

TEST ( Expresion, asignar_cromosoma) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2;

	exp2.asignar_arbol(exp1.get_arbol());

	EXPECT_EQ(exp1, exp2);
}

TEST (Expresion, MismaCadena) {
	algoritmos_poblacion_expresiones::Expresion exp1;

	exp1.generar_expresion_aleatoria(10, 0.3, 3);

	algoritmos_poblacion_expresiones::Expresion exp2(exp1);

	EXPECT_EQ(exp1.string_expresion(), exp2.string_expresion());

}

TEST (Expresion, evaluar_dato) {

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


TEST (Expresion, ObtenerSurarbol) {

	algoritmos_poblacion_expresiones::Expresion exp1;

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

TEST (Expresion, CruzarArbol) {

	algoritmos_poblacion_expresiones::Expresion exp1;

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp;
	arbol_tmp.resize(5);

	arbol_tmp[0].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp[1].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[1].set_valor(0);

	arbol_tmp[2].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::POR);

	arbol_tmp[3].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp[3].set_valor(1);
	arbol_tmp[4].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	arbol_tmp[4].set_valor_numerico(1.2);

	std::vector<double> cromosoma;
	cromosoma.resize(5);

	for ( int i = 0; i < 5; i++) {
		cromosoma[i] = 2.2;
	}

	exp1.asignar_arbol(arbol_tmp);

	std::vector<algoritmos_poblacion_expresiones::Nodo> arbol_tmp2;
	arbol_tmp2.resize(3);

	arbol_tmp2[0].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	arbol_tmp2[1].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);
	arbol_tmp2[1].set_valor(0);

	arbol_tmp2[2].set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	arbol_tmp2[2].set_valor_numerico(1.45);

	algoritmos_poblacion_expresiones::Expresion exp2;
	exp2.asignar_arbol(arbol_tmp2);

	algoritmos_poblacion_expresiones::Expresion hijo = exp1;
	algoritmos_poblacion_expresiones::Expresion hijo2 = exp1;


	exp1.intercambiar_subarbol(exp2, 4, 0, hijo);
	exp2.intercambiar_subarbol(exp1, 0, 4, hijo2);

	EXPECT_TRUE( hijo.get_longitud_arbol() == 7 && hijo2.get_longitud_arbol() == 1);

}

TEST ( Expresion, LeerFichero) {

	algoritmos_poblacion_expresiones::Expresion exp1(std::string("tests/expresion_prueba.txt"), 20, 9);

	std::string solucion = exp1.string_expresion();

	EXPECT_EQ(solucion, std::string("( ( -0.188219  / ( x3  +  -1.088276 ) ) + ( ( -6.747766  -  9.194880 ) * ( -4.898098  * ( ( x3  /  9.770432 ) *  x0 ) ) ) )"));
}

#endif
