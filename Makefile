# variables
CXX      := g++
HOME     := .
BIN      = $(HOME)/bin
INC	   = $(HOME)/include
SRC      = $(HOME)/src
OBJ      = $(HOME)/obj
DATOS	   = $(HOME)/datos
DOC      = $(HOME)/doc
GRAFICAS = $(HOME)/graficas

SRC_ALG_POB = $(SRC)/algoritmos_poblaciones
INC_ALG_POB = $(INC)/algoritmos_poblaciones


# flags de compilacion por defecto
MENSAJE := "Compilando\ usando\ C++17,\ sin\ optimización\ de\ máximo\ nivel\ y\ con\ todos\ los\ warnings\ activados"
OPTIMIZACION ?= 3
GPROF ?= 0
OPENMP ?= 1

ifeq ($(DEBUG), 1)
# target para debug (cambiamos flags y el mensaje)
OPTIMIZACION = g -g
OPENMP = 0
MENSAJE = "Compilando\ usando\ C++17,\ con\ optimización,\ con\ todos\ los\ warnings\ activados\ y\ con\ símbolos\ de\ depuración"
endif

ifeq ($(GPROF), 1)
F_GPROF = -pg
else
F_GPROF =
endif

ifeq ($(OPENMP), 1)
F_OPENMP = -fopenmp
else
F_OPENMP =
endif

O_LEVEL := -O$(strip $(OPTIMIZACION))

CXXFLAGS = -std=c++17 $(O_LEVEL) $(F_OPENMP) $(F_GPROF) -Wall -Wextra -Wfloat-equal -Wpedantic


# objetivo principal
OBJETIVO = $(BIN)/main
OBJETOS = $(OBJ)/main.o

# objetivos de la biblioteca AlgoritmoGA_P
OBJETOS_ALGS_POB = $(OBJ)/Parametros.o $(OBJ)/Nodo.o $(OBJ)/Expresion.o $(OBJ)/AlgoritmoPG.o $(OBJ)/Expresion_GAP.o $(OBJ)/AlgoritmoGA_P.o $(OBJ)/Random.o $(OBJ)/aux_pob_algs.o
CABECERAS_ALGS_POB = $(wildcard include/algoritmos_poblaciones/*.hpp)

ALGS_POB_INC_COMUNES = $(INC)/Random.hpp $(INC_ALG_POB)/aux_pob_algs.hpp

# objetivos de los tests
OBJETIVO_TEST = $(BIN)/main_test
OBJETOS_TEST = $(OBJ)/main_test.o

OBJETIVO_PREPROCESADO = $(BIN)/main_preprocesar
OBJETOS_PREPROCESADO = $(OBJ)/main_preprocesar.o

# variables para el contador de reglas
N := $(shell echo $(OBJETIVO) $(OBJETOS) $(OBJETOS_ALGS_POB) $(OBJETIVO_TEST) $(OBJETOS_TEST) $(OBJETIVO_PREPROCESADO) $(OBJETOS_PREPROCESADO) | wc -w )
X := 0
SUMA = $(eval X=$(shell echo $$(($(X)+1))))

# variables de GoogleTest --> https://github.com/google/googletest
gtest      = /usr/include/gtest/
gtestlibs  = /usr/lib/libgtest.so
gtestflags = -I$(gtest) $(gtestlibs)

# targets
.PHONY: all crear-carpetas debug INICIO FIN doc clean-doc mrproper help tests ejecutar-tests

# target por defecto
all: crear-carpetas INICIO ejecutar-tests $(OBJETIVO) $(OBJETIVO_PREPROCESADO) $(BIN)/main_conteo $(BIN)/main_suma_caracteristicas doc FIN


# target para compilar solo los tests
tests: clean crear-carpetas INICIO $(OBJETIVO_TEST) ejecutar-tests FIN

# reglas para compilar y ejecutar los test
ejecutar-tests: $(OBJETIVO_TEST)
	@$(OBJETIVO_TEST) --gtest_color=yes || (printf "\e[31mERROR: No se ha conseguido pasar todos los tests, abortando la compilación\n"; false)
	@printf "\n\e[32mTests ejecutados correctamente\n\n"



$(OBJETIVO_TEST): $(OBJETOS_ALGS_POB) $(CABECERAS_ALGS_POB)  $(OBJETOS_TEST)
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO_TEST) a partir de $(OBJETOS_TEST)\n"
	@$(CXX) $(OBJETOS_ALGS_POB) $(OBJETOS_TEST) -o $(OBJETIVO_TEST) $(F_OPENMP) $(gtestflags) -I$(INC)
	@printf "\n\e[36mCompilación de $(OBJETIVO_TEST) finalizada con exito.\e[0m\n\n"

$(OBJETIVO_PREPROCESADO): $(OBJETOS_ALGS_POB) $(CABECERAS_ALGS_POB)  $(OBJETOS_PREPROCESADO)
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO_PREPROCESADO) a partir de $(OBJETOS_PREPROCESADO)\n"
	@$(CXX) $(OBJETOS_ALGS_POB) $(OBJETOS_PREPROCESADO) -o $(OBJETIVO_PREPROCESADO) $(F_OPENMP) $(gtestflags) -I$(INC)
	@printf "\n\e[36mCompilación de $(OBJETIVO_PREPROCESADO) finalizada con exito.\e[0m\n\n"

$(BIN)/main_conteo : $(OBJETOS_ALGS_POB) $(CABECERAS_ALGS_POB) $(OBJ)/main_conteo.o
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(BIN)/main_conteo a partir de $(OBJ)/main_conteo.o\n"
	@$(CXX) $(OBJETOS_ALGS_POB) $(OBJ)/main_conteo.o -o $(BIN)/main_conteo $(F_OPENMP) $(gtestflags) -I$(INC)
	@printf "\n\e[36mCompilación de $(BIN)/main_conteo finalizada con exito.\e[0m\n\n"

$(BIN)/main_suma_caracteristicas : $(OBJETOS_ALGS_POB) $(CABECERAS_ALGS_POB) $(OBJ)/main_suma_caracteristicas.o
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(BIN)/main_suma_caracteristicas a partir de $(OBJ)/main_suma_caracteristicas.o\n"
	@$(CXX) $(OBJETOS_ALGS_POB) $(OBJ)/main_suma_caracteristicas.o -o $(BIN)/main_suma_caracteristicas $(F_OPENMP) $(gtestflags) -I$(INC)
	@printf "\n\e[36mCompilación de $(BIN)/main_suma_caracteristicas finalizada con exito.\e[0m\n\n"

# funcion para compilar un objeto
define compilar_objeto
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $(2) a partir de $(1)\n"
	@$(CXX) -c $(CXXFLAGS) $(1) -I$(INC) -I. -o $(2)
endef


# mensaje de inicio y compilacion del objetivo y objeros

INICIO:
	@printf "\n\e[36mComenzando compilación de $(BIN)/AlgoritmoGA_P\n\n"
	@printf "\e[94mCompilador: $(CXX)\n"
	@printf "\e[94mFlags del compilador: $(CXXFLAGS)\n\n"
	@printf "\e[94m$(MENSAJE)\n\n"

$(OBJETIVO): $(OBJETOS) $(OBJETOS_ALGS_POB) $(CABECERAS_ALGS_POB)
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO) a partir de $(OBJETOS)\n"
	@$(CXX) $(OBJETOS) $(OBJETOS_ALGS_POB) $(CXXFLAGS) -o $@ -I$(INC) $(F_OPENMP) $(F_GPROF)
	@printf "\n\e[36mCompilación de $(OBJETIVO) finalizada con exito.\n\n"


$(OBJ)/Parametros.o: $(SRC_ALG_POB)/Parametros.cpp $(INC_ALG_POB)/Parametros.hpp $(ALGS_POB_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/Nodo.o: $(SRC_ALG_POB)/Nodo.cpp $(INC_ALG_POB)/Nodo.hpp $(ALGS_POB_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/Expresion.o: $(SRC_ALG_POB)/Expresion.cpp $(INC_ALG_POB)/Expresion.hpp $(INC_ALG_POB)/Nodo.hpp $(ALGS_POB_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/Expresion_GAP.o: $(SRC_ALG_POB)/Expresion_GAP.cpp $(INC_ALG_POB)/Expresion_GAP.hpp $(INC_ALG_POB)/Expresion.hpp $(INC_ALG_POB)/Nodo.hpp $(ALGS_POB_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/AlgoritmoGA_P.o: $(SRC_ALG_POB)/AlgoritmoGA_P.cpp $(INC_ALG_POB)/AlgoritmoGA_P.hpp $(INC_ALG_POB)/Expresion_GAP.hpp $(INC_ALG_POB)/Expresion.hpp $(INC_ALG_POB)/Nodo.hpp $(ALGS_POB_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/AlgoritmoPG.o: $(SRC_ALG_POB)/AlgoritmoPG.cpp $(INC_ALG_POB)/AlgoritmoPG.hpp $(INC_ALG_POB)/Expresion.hpp $(INC_ALG_POB)/Nodo.hpp $(ALGS_POB_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/aux_pob_algs.o: $(SRC_ALG_POB)/aux_pob_algs.cpp $(INC_ALG_POB)/aux_pob_algs.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/Random.o: $(SRC)/Random.cpp $(INC)/Random.hpp
	$(call compilar_objeto,$<,$@)



$(OBJ)/main_test.o: $(SRC)/main_test.cpp $(INC_ALG_POB)/AlgoritmoGA_P.hpp $(INC)/Random.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/main.o: $(SRC)/main.cpp $(INC_ALG_POB)/AlgoritmoGA_P.hpp $(INC)/Random.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/main_preprocesar.o: $(SRC)/main_preprocesar.cpp $(INC_ALG_POB)/preprocesado.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/main_conteo.o: $(SRC)/main_conteo.cpp $(INC_ALG_POB)/preprocesado.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/main_suma_caracteristicas.o: $(SRC)/main_suma_caracteristicas.cpp $(INC_ALG_POB)/preprocesado.hpp
	$(call compilar_objeto,$<,$@)


# mensaje de fin
FIN:
	@printf "\n\e[36mCompilación finalizada con éxito\n"

# targets de limpieza
clean:
	@printf "\e[36mLimpiando el directorio $(OBJ)\n"
	-@rm $(OBJ)/*.o 2> /dev/null || printf "\t\e[33mEl directorio $(OBJ) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpiando el directorio $(BIN)\n"
	-@rm $(BIN)/* 2> /dev/null || printf "\t\e[33mEl directorio $(BIN) está vacio, nada que limpiar\n"
	@printf "\e[36mLimpieza completada\n"

clean-doc:
	@printf "\e[36mLimpiando la documentación\n"
	-@rm $(DOC)/html -r 2> /dev/null || printf "\t\e[33mNo existe documentación generada en HTML\n"
	-@rm $(DOC)/html -r 2> /dev/null || printf "\t\e[33mNo existe documentación generada en LaTeX\n"

mrproper: clean clean-doc


# target de documentacion
doc:
	@printf "\e[36mComenzando compilación de la documentación del proyecto\n\e[33m\n"
	@doxygen doc/doxys/Doxyfile
	@printf "\e[36mFinalizada compilación de la documentación. Puedes consultarla en doc/html/index.html\n"

# target para crear las carpetas necesarias
crear-carpetas:
	@printf "\e[36mCreando carpetas necesarias\e[0m\n"
	-@mkdir $(OBJ) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(OBJ)\n"
	-@mkdir $(BIN) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(BIN)\n"
	-@mkdir $(GRAFICAS) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(GRAFICAS)\n"
	-@mkdir $(GRAFICAS)/datos 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(GRAFICAS)/datos\n"


# target para mostrar ayuda
help:
	@printf "\e[33mUso del Makefile:\n"
	@printf "\t\e[36mCompilar con optimización: \t     \e[94mmake\n"
	@printf "\t\e[36mCompilar y ejecutar tests: \t     \e[94mmake \e[0mtests\n"
	@printf "\t\e[36mCompilar documentación: \t     \e[94mmake \e[0mdoc\n"
	@printf "\t\e[36mLimpiar binarios y objetos: \t     \e[94mmake \e[0mclean\n"
	@printf "\t\e[36mLimpiar documentación: \t\t     \e[94mmake \e[0mclean-doc\n"
	@printf "\t\e[36mLimpiar todo: \t\t\t     \e[94mmake \e[0mmrproper\n\n"
	@printf "\e[33mTambién tienes disponibles las siguientes variables:\n"
	@printf "\t\e[36mNivel optimizacion(0, 1, 2, 3, g):   \e[94mmake \e[0mOPTIMIZACION=3\n"
	@printf "\t\e[36mCompilar con OpenMP(0, 1): \t     \e[94mmake \e[0mOPENMP=1\n"
	@printf "\t\e[36mActivar símbolos depuracion(0, 1):   \e[94mmake \e[0mDEBUG=0\n"
	@printf "\t\e[36mCompilar para GPROF(0, 1): \t     \e[94mmake \e[0mGPROF=0\n"
