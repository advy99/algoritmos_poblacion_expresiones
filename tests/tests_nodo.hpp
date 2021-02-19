#ifndef TESTS_NODO
#define TESTS_NODO

#include <gtest/gtest.h>
#include "nodo.hpp"


TEST (Nodo, IgualElMismo) {
	GA_P::Nodo nodo;

	EXPECT_EQ(nodo, nodo);
}

TEST (Nodo, ConstructorCopia) {
	GA_P::Nodo nodo;
	GA_P::Nodo otro(nodo);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, ConstructorDefecto) {
	GA_P::Nodo nodo;
	GA_P::Nodo otro;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, Asignacion) {
	GA_P::Nodo nodo;
	nodo.setTipoNodo(GA_P::TipoNodo::NUMERO);

	GA_P::Nodo otro;

	otro = nodo;

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintosTipos) {
	GA_P::Nodo nodo;
	nodo.setTipoNodo(GA_P::TipoNodo::NUMERO);

	GA_P::Nodo otro;
	nodo.setTipoNodo(GA_P::TipoNodo::MAS);


	EXPECT_NE(nodo, otro);
}


TEST (Nodo, MismoTipoValorDistinto) {
	GA_P::Nodo nodo;
	nodo.setTipoNodo(GA_P::TipoNodo::MAS);

	GA_P::Nodo otro;
	otro.setTipoNodo(GA_P::TipoNodo::MAS);

	otro.setValor(-23);

	EXPECT_EQ(nodo, otro);
}

TEST (Nodo, DistintoTipoValorIgual) {
	GA_P::Nodo nodo;
	nodo.setTipoNodo(GA_P::TipoNodo::NUMERO);
	nodo.setValor(1);

	GA_P::Nodo otro;
	otro.setTipoNodo(GA_P::TipoNodo::VARIABLE);

	otro.setValor(1);

	EXPECT_EQ(nodo, otro);
}

#endif
