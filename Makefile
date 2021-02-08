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

FLAGS = -std=c++17 -O3 -Wall -Wextra -Wfloat-equal -Wpedantic
MENSAJE = "Compilando\ usando\ C++17,\ con\ optimización\ de\ máximo\ nivel\ y\ con\ todos\ los\ warnings\ activados"

OBJETIVO = $(BIN)/GA_P
OBJETOS = $(LIB)/libGA_P.a $(OBJ)/main.o
OBJETOS_LIB_GAP = $(OBJ)/nodo.o $(OBJ)/expresion.o $(OBJ)/poblacion.o $(OBJ)/GA_P.o $(OBJ)/random.o

N := $(shell echo $(OBJETIVO) $(OBJETOS) $(OBJETOS_LIB_GAP) | wc -w )
X := 0
SUMA = $(eval X=$(shell echo $$(($(X)+1))))

.PHONY: all crear-carpetas debug INICIO FIN doc clean-doc mrproper help

all: clean crear-carpetas INICIO $(OBJETIVO) doc FIN

debug: FLAGS = -std=c++17 -g -Wall -Wextra -Wfloat-equal -Wpedantic
debug: MENSAJE = "Compilando\ usando\ C++17,\ sin\ optimización,\ con\ todos\ los\ warnings\ activados\ y\ con\ símbolos\ de\ depuración"
debug: all

define compilar_objeto
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el objeto $(2) a partir de $(1)\n"
	@$(CXX) -c $(FLAGS) $(1) -I$(INC) -o $(2)
endef





INICIO:
	@printf "\n\e[36mComenzando compilación de $(BIN)/GA_P\n\n"
	@printf "\e[94mCompilador: $(CXX)\n"
	@printf "\e[94mFlags del compilador: $(FLAGS)\n\n"
	@printf "\e[94m$(MENSAJE)\n\n"

$(OBJETIVO): $(OBJETOS)
	@$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando el binario $(OBJETIVO) a partir de $(OBJETOS)\n"
	@$(CXX) $(OBJ)/main.o -o $@ -L$(LIB) -lGA_P
	@printf "\n\e[36mCompilación de $(OBJETIVO) finalizada con exito.\n\n"

$(OBJ)/random.o: $(SRC)/random.cpp
	$(call compilar_objeto,$^,$@)

$(OBJ)/main.o: $(SRC)/main.cpp
	$(call compilar_objeto,$^,$@)

$(OBJ)/GA_P.o: $(SRC)/GA_P.cpp
	$(call compilar_objeto,$^,$@)

$(OBJ)/expresion.o: $(SRC)/expresion.cpp
	$(call compilar_objeto,$^,$@)

$(OBJ)/poblacion.o: $(SRC)/poblacion.cpp
	$(call compilar_objeto,$^,$@)

$(OBJ)/nodo.o: $(SRC)/nodo.cpp
	$(call compilar_objeto,$^,$@)

$(LIB)/libGA_P.a: $(OBJETOS_LIB_GAP)
	$(SUMA)
	@printf "\e[31m[$(X)/$(N)] \e[32mCreando la biblioteca $@ \n"
	@ar rs $@ $^



FIN:
	@printf "\n\e[36mCompilación finalizada con éxito\n"

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


doc:
	@printf "\e[36mComenzando compilación de la documentación del proyecto\n\e[33m\n"
	@doxygen doc/doxys/Doxyfile
	@printf "\e[36mFinalizada compilación de la documentación. Puedes consultarla en doc/html/index.html\n"

crear-carpetas:
	@printf "\e[36mCreando carpetas necesarias\e[0m\n"
	-@mkdir $(OBJ) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(OBJ)\n"
	-@mkdir $(BIN) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(BIN)\n"
	-@mkdir $(LIB) 2> /dev/null || printf "\t\e[33mYa existe la carpeta $(LIB)\n"


mrproper: clean clean-doc


help:
	@printf "\e[36mUso del Makefile:\n"
	@printf "\t\e[36mCompilar con optimización: \t     \e[94mmake\n"
	@printf "\t\e[36mCompilar con símbolos de depuración: \e[94mmake \e[0mdebug\n"
	@printf "\t\e[36mCompilar documentación: \t     \e[94mmake \e[0mdocumentacion\n"
	@printf "\t\e[36mLimpiar binarios y objetos: \t     \e[94mmake \e[0mclean\n"
	@printf "\t\e[36mLimpiar documentación: \t\t     \e[94mmake \e[0mclean-doc\n"
	@printf "\t\e[36mLimpiar todo: \t\t\t     \e[94mmake \e[0mmrproper\n"
