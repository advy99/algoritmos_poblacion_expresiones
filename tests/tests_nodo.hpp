#ifndef TESTS_NODO
#define TESTS_NODO

#include <gtest/gtest.h>
#include "nodo.hpp"


TEST (Nodo, IgualElMismo) {
	GA_P::Nodo nodo;

	EXPECT_EQ(nodo, nodo);
}


#endif
