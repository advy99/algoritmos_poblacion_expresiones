#ifndef TESTS_NODO
#define TESTS_NODO

#include <gtest/gtest.h>
#include "algoritmos_poblaciones/Nodo.hpp"


TEST (Nodo, IgualElMismo) {
	algoritmos_poblaciones::Nodo nodo;

	EXPECT_EQ(nodo, nodo);
}

TEST (Nodo, ConstructorCopia) {
	algoritmos_poblaciones::Nodo nodo;
	algoritmos_poblaciones::Nodo otro(nodo);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, ConstructorDefecto) {
	algoritmos_poblaciones::Nodo nodo;
	algoritmos_poblaciones::Nodo otro;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, Asignacion) {
	algoritmos_poblaciones::Nodo nodo;
	nodo.setTipoNodo(algoritmos_poblaciones::TipoNodo::NUMERO);

	algoritmos_poblaciones::Nodo otro;

	otro = nodo;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintosTipos) {
	algoritmos_poblaciones::Nodo nodo;
	nodo.setTipoNodo(algoritmos_poblaciones::TipoNodo::NUMERO);

	algoritmos_poblaciones::Nodo otro;
	nodo.setTipoNodo(algoritmos_poblaciones::TipoNodo::MAS);


	EXPECT_NE(nodo, otro);
}


TEST (Nodo, MismoTipoValorDistinto) {
	algoritmos_poblaciones::Nodo nodo;
	nodo.setTipoNodo(algoritmos_poblaciones::TipoNodo::MAS);

	algoritmos_poblaciones::Nodo otro;
	otro.setTipoNodo(algoritmos_poblaciones::TipoNodo::MAS);

	otro.setValor(-23);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintoTipoValorIgual) {
	algoritmos_poblaciones::Nodo nodo;
	nodo.setTipoNodo(algoritmos_poblaciones::TipoNodo::NUMERO);
	nodo.setValor(1);

	algoritmos_poblaciones::Nodo otro;
	otro.setTipoNodo(algoritmos_poblaciones::TipoNodo::VARIABLE);

	otro.setValor(1);

	EXPECT_NE(nodo, otro);
}

#endif
