# variables
CXX      = g++
HOME     = .
BIN      = $(HOME)/bin
INC	   = $(HOME)/include
SRC      = $(HOME)/src
OBJ      = $(HOME)/obj
LIB      = $(HOME)/lib
DATOS	   = $(HOME)/datos
DOC      = $(HOME)/doc
GRAFICAS = $(HOME)/graficas/datos

# flags de compilacion por defecto
MENSAJE = "Compilando\ usando\ C++17,\ con\ optimización\ de\ máximo\ nivel\ y\ con\ todos\ los\ warnings\ activados"
OPTIMIZACION = -O3

ifeq ($(debug), 1)
# target para debug (cambiamos flags y el mensaje)
OPTIMIZACION = -g
MENSAJE = "Compilando\ usando\ C++17,\ sin\ optimización,\ con\ todos\ los\ warnings\ activados\ y\ con\ símbolos\ de\ depuración"
endif

CXXFLAGS = -std=c++17 $(OPTIMIZACION) -Wall -Wextra -Wfloat-equal -Wpedantic


# objetivo principal
OBJETIVO = $(BIN)/GA_P
OBJETOS = $(LIB)/libGA_P.a $(OBJ)/main.o

# objetivos de la biblioteca GA_P
OBJETOS_LIB_GAP = $(OBJ)/nodo.o $(OBJ)/expresion.o $(OBJ)/poblacion.o $(OBJ)/GA_P.o $(OBJ)/random.o $(OBJ)/aux_gap.o

GAP_INC_COMUNES = $(INC)/random.hpp $(INC)/aux_gap.hpp

# objetivos de los tests
OBJETIVO_TEST = $(BIN)/main_test
OBJETOS_TEST = $(OBJ)/main_test.o

# variables para el contador de reglas
N := $(shell echo $(OBJETIVO) $(OBJETOS) $(OBJETOS_LIB_GAP) $(OBJETIVO_TEST) $(OBJETOS_TEST) | wc -w )
X := 0
SUMA = $(eval X=$(shell echo $$(($(X)+1))))

# variables de GoogleTest --> https://github.com/google/googletest
gtest      = /usr/include/gtest/
gtestlibs  = /usr/lib/libgtest.so
gtestflags = -I$(gtest) $(gtestlibs)

# targets
.PHONY: all crear-carpetas debug INICIO FIN doc clean-doc mrproper help tests ejecutar-tests

# target por defecto
all: clean crear-carpetas INICIO ejecutar-tests $(OBJETIVO) doc FIN


# target para compilar solo los tests
tests: clean crear-carpetas INICIO $(OBJETIVO_TEST) ejecutar-tests FIN

# reglas para compilar y ejecutar los test
ejecutar-tests: $(OBJETIVO_TEST)
	@$(OBJETIVO_TEST) || (printf "\e[31mERROR: No se ha conseguido pasar todos los tests, abortando la compilación\n"; false)
	@printf "\n\e[32mTests ejecutados correctamente\n\n"



$(OBJETIVO_TEST): $(LIB)/libGA_P.a $(OBJETOS_TEST)
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO_TEST) a partir de $(OBJETOS_TEST)\n"
	@$(CXX) $(OBJETOS_TEST) -o $(OBJETIVO_TEST) $(gtestflags) -L$(LIB) -lGA_P
	@printf "\n\e[36mCompilación de $(OBJETIVO_TEST) finalizada con exito.\n\n"


# funcion para compilar un objeto
define compilar_objeto
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $(2) a partir de $(1)\n"
	@$(CXX) -c $(CXXFLAGS) $(1) -I$(INC) -I. -o $(2)
endef


# mensaje de inicio y compilacion del objetivo y objeros

INICIO:
	@printf "\n\e[36mComenzando compilación de $(BIN)/GA_P\n\n"
	@printf "\e[94mCompilador: $(CXX)\n"
	@printf "\e[94mFlags del compilador: $(CXXFLAGS)\n\n"
	@printf "\e[94m$(MENSAJE)\n\n"

$(OBJETIVO): $(OBJETOS)
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO) a partir de $(OBJETOS)\n"
	@$(CXX) $(OBJ)/main.o -o $@ -L$(LIB) -lGA_P
	@printf "\n\e[36mCompilación de $(OBJETIVO) finalizada con exito.\n\n"



$(OBJ)/nodo.o: $(SRC)/nodo.cpp $(INC)/nodo.hpp $(GAP_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/expresion.o: $(SRC)/expresion.cpp $(INC)/expresion.hpp $(INC)/nodo.hpp $(GAP_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/poblacion.o: $(SRC)/poblacion.cpp $(INC)/poblacion.hpp $(INC)/expresion.hpp $(INC)/nodo.hpp $(GAP_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/GA_P.o: $(SRC)/GA_P.cpp $(INC)/GA_P.hpp $(INC)/poblacion.hpp $(INC)/expresion.hpp $(INC)/nodo.hpp $(GAP_INC_COMUNES)
	$(call compilar_objeto,$<,$@)

$(OBJ)/aux_gap.o: $(SRC)/aux_gap.cpp $(INC)/aux_gap.hpp
	$(call compilar_objeto,$<,$@)



$(LIB)/libGA_P.a: $(OBJETOS_LIB_GAP)
	$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando la biblioteca $@ \n"
	@ar rs $@ $^

$(OBJ)/random.o: $(SRC)/random.cpp $(INC)/random.hpp
	$(call compilar_objeto,$<,$@)


$(OBJ)/main_pruebas.o: $(SRC)/main_pruebas.cpp $(INC)/GA_P.hpp $(INC)/random.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/main_test.o: $(SRC)/main_test.cpp $(INC)/GA_P.hpp $(INC)/random.hpp
	$(call compilar_objeto,$<,$@)

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/GA_P.hpp $(INC)/random.hpp
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
	-@mkdir $(LIB) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(LIB)\n"

# target para mostrar ayuda
help:
	@printf "\e[36mUso del Makefile:\n"
	@printf "\t\e[36mCompilar con optimización: \t     \e[94mmake\n"
	@printf "\t\e[36mCompilar con símbolos de depuración: \e[94mmake \e[0mdebug\n"
	@printf "\t\e[36mCompilar y ejecutar tests: \t     \e[94mmake \e[0mtests\n"
	@printf "\t\e[36mCompilar documentación: \t     \e[94mmake \e[0mdoc\n"
	@printf "\t\e[36mLimpiar binarios y objetos: \t     \e[94mmake \e[0mclean\n"
	@printf "\t\e[36mLimpiar documentación: \t\t     \e[94mmake \e[0mclean-doc\n"
	@printf "\t\e[36mLimpiar todo: \t\t\t     \e[94mmake \e[0mmrproper\n"
