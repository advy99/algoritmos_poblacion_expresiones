#ifndef TESTS_NODO
#define TESTS_NODO

#include <gtest/gtest.h>
#include "Nodo.hpp"


TEST (Nodo, IgualElMismo) {
	PG_ALGS::Nodo nodo;

	EXPECT_EQ(nodo, nodo);
}

TEST (Nodo, ConstructorCopia) {
	PG_ALGS::Nodo nodo;
	PG_ALGS::Nodo otro(nodo);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, ConstructorDefecto) {
	PG_ALGS::Nodo nodo;
	PG_ALGS::Nodo otro;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, Asignacion) {
	PG_ALGS::Nodo nodo;
	nodo.setTipoNodo(PG_ALGS::TipoNodo::NUMERO);

	PG_ALGS::Nodo otro;

	otro = nodo;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintosTipos) {
	PG_ALGS::Nodo nodo;
	nodo.setTipoNodo(PG_ALGS::TipoNodo::NUMERO);

	PG_ALGS::Nodo otro;
	nodo.setTipoNodo(PG_ALGS::TipoNodo::MAS);


	EXPECT_NE(nodo, otro);
}


TEST (Nodo, MismoTipoValorDistinto) {
	PG_ALGS::Nodo nodo;
	nodo.setTipoNodo(PG_ALGS::TipoNodo::MAS);

	PG_ALGS::Nodo otro;
	otro.setTipoNodo(PG_ALGS::TipoNodo::MAS);

	otro.setValor(-23);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintoTipoValorIgual) {
	PG_ALGS::Nodo nodo;
	nodo.setTipoNodo(PG_ALGS::TipoNodo::NUMERO);
	nodo.setValor(1);

	PG_ALGS::Nodo otro;
	otro.setTipoNodo(PG_ALGS::TipoNodo::VARIABLE);

	otro.setValor(1);

	EXPECT_NE(nodo, otro);
}

#endif
