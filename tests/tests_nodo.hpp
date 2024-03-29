#ifndef TESTS_NODO
#define TESTS_NODO

#include <gtest/gtest.h>
#include "algoritmos_poblaciones/Nodo.hpp"


TEST (Nodo, IgualElMismo) {
	algoritmos_poblacion_expresiones::Nodo nodo;

	EXPECT_EQ(nodo, nodo);
}

TEST (Nodo, ConstructorCopia) {
	algoritmos_poblacion_expresiones::Nodo nodo;
	algoritmos_poblacion_expresiones::Nodo otro(nodo);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, ConstructorDefecto) {
	algoritmos_poblacion_expresiones::Nodo nodo;
	algoritmos_poblacion_expresiones::Nodo otro;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, Asignacion) {
	algoritmos_poblacion_expresiones::Nodo nodo;
	nodo.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);

	algoritmos_poblacion_expresiones::Nodo otro;

	otro = nodo;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintosTipos) {
	algoritmos_poblacion_expresiones::Nodo nodo;
	nodo.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);

	algoritmos_poblacion_expresiones::Nodo otro;
	nodo.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);


	EXPECT_NE(nodo, otro);
}


TEST (Nodo, MismoTipoValorDistinto) {
	algoritmos_poblacion_expresiones::Nodo nodo;
	nodo.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	algoritmos_poblacion_expresiones::Nodo otro;
	otro.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::MAS);

	otro.set_valor(-23);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintoTipoValorIgual) {
	algoritmos_poblacion_expresiones::Nodo nodo;
	nodo.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::NUMERO);
	nodo.set_valor(1);

	algoritmos_poblacion_expresiones::Nodo otro;
	otro.set_tipo_nodo(algoritmos_poblacion_expresiones::TipoNodo::VARIABLE);

	otro.set_valor(1);

	EXPECT_NE(nodo, otro);
}

#endif
