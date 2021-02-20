#include "tests/tests_nodo.hpp"
#include "tests/tests_expresion.hpp"

#include <string>

int main(int argc, char ** argv) {

	bool encontrado = false;
	int i = 0;

	while ( i < argc && !encontrado ) {
		encontrado = std::string(argv[i]) == "--gtest_color=yes";
		i++;
	}


	if ( encontrado ) {
		testing::InitGoogleTest(&argc, argv);
	} else {
		char ** nuevo_argv;
		int nuevo_argc = argc + 1;

		nuevo_argv = new char * [nuevo_argc];

		for ( int i = 0; i < nuevo_argc; i++){
			nuevo_argv[i] = new char[256];
		}

		for ( int i = 0; i < argc; i++) {
			strcpy(nuevo_argv[i], argv[i]);
		}

		strcpy(nuevo_argv[argc], "--gtest_color=yes");

		testing::InitGoogleTest(&nuevo_argc, nuevo_argv);
	}


	return RUN_ALL_TESTS();
}
